/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qlibrary.h>
#include <qoperatingsystemversion.h>
#include <qsysinfo.h>
#include <qt_windows.h>
#include <TlHelp32.h>
#include "../3rdparty/chromium/sandbox/win/src/process_mitigations.h"
#include "../3rdparty/chromium/sandbox/win/src/sandbox_factory.h"

#ifndef NDEBUG
#include "../3rdparty/chromium/base/command_line.h"
#include "../3rdparty/chromium/base/logging.h"
#endif

class User32DLL {
public:
    User32DLL()
        : setProcessDPIAware(0)
    {
        library.setFileName(QStringLiteral("User32"));
        if (!library.load())
            return;
        setProcessDPIAware = (SetProcessDPIAware)library.resolve("SetProcessDPIAware");
    }

    bool isValid() const
    {
        return setProcessDPIAware;
    }

    typedef BOOL (WINAPI *SetProcessDPIAware)();

    // Windows Vista onwards
    SetProcessDPIAware setProcessDPIAware;

private:
    QLibrary library;
};

// This must match PROCESS_DPI_AWARENESS in ShellScalingApi.h
enum DpiAwareness {
    PROCESS_PER_UNAWARE = 0,
    PROCESS_PER_SYSTEM_DPI_AWARE = 1,
    PROCESS_PER_MONITOR_DPI_AWARE = 2
};

// Shell scaling library (Windows 8.1 onwards)
class ShcoreDLL {
public:
    ShcoreDLL()
        : getProcessDpiAwareness(0), setProcessDpiAwareness(0)
    {
        if (QOperatingSystemVersion::current() < QOperatingSystemVersion::Windows8_1)
            return;
        library.setFileName(QStringLiteral("SHCore"));
        if (!library.load())
            return;
        getProcessDpiAwareness = (GetProcessDpiAwareness)library.resolve("GetProcessDpiAwareness");
        setProcessDpiAwareness = (SetProcessDpiAwareness)library.resolve("SetProcessDpiAwareness");
    }

    bool isValid() const
    {
        return getProcessDpiAwareness && setProcessDpiAwareness;
    }

    typedef HRESULT (WINAPI *GetProcessDpiAwareness)(HANDLE, DpiAwareness *);
    typedef HRESULT (WINAPI *SetProcessDpiAwareness)(DpiAwareness);

    GetProcessDpiAwareness getProcessDpiAwareness;
    SetProcessDpiAwareness setProcessDpiAwareness;

private:
    QLibrary library;
};


static DWORD getParentProcessId()
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        qErrnoWarning(GetLastError(), "CreateToolhelp32Snapshot failed.");
        return NULL;
    }

    PROCESSENTRY32 pe = {0};
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &pe)) {
        qWarning("Cannot retrieve parent process handle.");
        return NULL;
    }

    DWORD parentPid = NULL;
    const DWORD pid = GetCurrentProcessId();
    do {
        if (pe.th32ProcessID == pid) {
            parentPid = pe.th32ParentProcessID;
            break;
        }
    } while (Process32Next(hSnapshot, &pe));
    CloseHandle(hSnapshot);
    return parentPid;
}

namespace QtWebEngineCore {
extern __declspec(dllimport) sandbox::SandboxInterfaceInfo *staticSandboxInterfaceInfo(sandbox::SandboxInterfaceInfo *info = nullptr);
}

namespace QtWebEngineProcess {

// A duplicate of the function by same name in startup_helper_win.cc
static void InitializeSandboxInfo(sandbox::SandboxInterfaceInfo *info)
{
    info->broker_services = sandbox::SandboxFactory::GetBrokerServices();
    if (!info->broker_services) {
        info->target_services = sandbox::SandboxFactory::GetTargetServices();
    } else {
        // Ensure the proper mitigations are enforced for the browser process.
        sandbox::ApplyProcessMitigationsToCurrentProcess(
            sandbox::MITIGATION_DEP | sandbox::MITIGATION_DEP_NO_ATL_THUNK |
            sandbox::MITIGATION_HARDEN_TOKEN_IL_POLICY);
        // Note: these mitigations are "post-startup".  Some mitigations that need
        // to be enabled sooner (e.g. MITIGATION_EXTENSION_POINT_DISABLE) are done
        // so in Chrome_ELF.
    }
}

// Initializes the staticlib copy of //base and //sandbox used for Windows sandboxing
void initializeStaticCopy(int argc, const char **argv)
{
#ifndef NDEBUG
    // Initialize //base for debugging
    base::CommandLine::Init(argc, argv);
    logging::LoggingSettings settings;
    settings.logging_dest = logging::LOG_TO_SYSTEM_DEBUG_LOG;
    logging::InitLogging(settings);
#endif
    sandbox::SandboxInterfaceInfo *info = new sandbox::SandboxInterfaceInfo();
    memset(info, 0, sizeof(sandbox::SandboxInterfaceInfo));
    InitializeSandboxInfo(info);
    QtWebEngineCore::staticSandboxInterfaceInfo(info);
}

void initDpiAwareness()
{
    ShcoreDLL shcore;
    if (shcore.isValid()) {
        DpiAwareness dpiAwareness = PROCESS_PER_MONITOR_DPI_AWARE;
        const DWORD pid = getParentProcessId();
        if (pid) {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
            DpiAwareness parentDpiAwareness;
            HRESULT hr = shcore.getProcessDpiAwareness(hProcess, &parentDpiAwareness);
            CloseHandle(hProcess);
            if (hr == S_OK)
                dpiAwareness = parentDpiAwareness;
        }
        if (shcore.setProcessDpiAwareness(dpiAwareness) != S_OK)
            qErrnoWarning(GetLastError(), "SetProcessDPIAwareness failed.");
    } else {
        // Fallback. Use SetProcessDPIAware unconditionally.
        User32DLL user32;
        if (user32.isValid())
            user32.setProcessDPIAware();
    }
}

} // namespace QtWebEngineProcess
