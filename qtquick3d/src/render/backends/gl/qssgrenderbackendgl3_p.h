/****************************************************************************
**
** Copyright (C) 2008-2012 NVIDIA Corporation.
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick 3D.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSSG_RENDER_BACKEND_GL3_H
#define QSSG_RENDER_BACKEND_GL3_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

/// @file QSSGrenderbackendgl3.h
///       NVRender OpenGL 3 backend definition.

#include <QtQuick3DRender/private/qssgrenderbasetypes_p.h>
#include <QtQuick3DRender/private/qssgrenderbackendglbase_p.h>

#include <QtGui/QOpenGLExtraFunctions>

QT_BEGIN_NAMESPACE

///< forward declaration
class QSSGRenderBackendMiscStateGL;

#if defined(QT_OPENGL_ES_2)
    class QSSGOpenGLES2Extensions;
#else
    class QOpenGLExtension_ARB_timer_query;
    class QOpenGLExtension_ARB_tessellation_shader;
    class QOpenGLExtension_ARB_texture_multisample;
    class QSSGOpenGLExtensions;
#endif

namespace QSSGGlExtStrings {
QByteArray extsAstcHDR();
QByteArray extsAstcLDR();
}

class QSSGRenderBackendGL3Impl : public QSSGRenderBackendGLBase
{
public:
    /// constructor
    QSSGRenderBackendGL3Impl(const QSurfaceFormat &format);
    /// destructor
    ~QSSGRenderBackendGL3Impl() override;

    qint32 getDepthBits() const override;
    qint32 getStencilBits() const override;
    void generateMipMaps(QSSGRenderBackendTextureObject to,
                         QSSGRenderTextureTargetType target,
                         QSSGRenderHint genType) override;

    QByteArray getShadingLanguageVersion() override;
    QSSGRenderContextType getRenderContextType() const override;

    void setMultisampledTextureData2D(QSSGRenderBackendTextureObject to,
                                      QSSGRenderTextureTargetType target,
                                      qint32 samples,
                                      QSSGRenderTextureFormat internalFormat,
                                      qint32 width,
                                      qint32 height,
                                      bool fixedsamplelocations) override;

    void setTextureData3D(QSSGRenderBackendTextureObject to,
                          QSSGRenderTextureTargetType target,
                          qint32 level,
                          QSSGRenderTextureFormat internalFormat,
                          qint32 width,
                          qint32 height,
                          qint32 depth,
                          qint32 border,
                          QSSGRenderTextureFormat format,
                          QSSGByteView hostData) override;

    void updateSampler(QSSGRenderBackendSamplerObject so,
                       QSSGRenderTextureTargetType target,
                       QSSGRenderTextureMinifyingOp minFilter = QSSGRenderTextureMinifyingOp::Linear,
                       QSSGRenderTextureMagnifyingOp magFilter = QSSGRenderTextureMagnifyingOp::Linear,
                       QSSGRenderTextureCoordOp wrapS = QSSGRenderTextureCoordOp::ClampToEdge,
                       QSSGRenderTextureCoordOp wrapT = QSSGRenderTextureCoordOp::ClampToEdge,
                       QSSGRenderTextureCoordOp wrapR = QSSGRenderTextureCoordOp::ClampToEdge,
                       float minLod = -1000.0,
                       float maxLod = 1000.0,
                       float lodBias = 0.0,
                       QSSGRenderTextureCompareMode compareMode = QSSGRenderTextureCompareMode::NoCompare,
                       QSSGRenderTextureCompareOp compareFunc = QSSGRenderTextureCompareOp::LessThanOrEqual,
                       float anisotropy = 1.0,
                       float *borderColor = nullptr) override;

    void updateTextureObject(QSSGRenderBackendTextureObject to,
                             QSSGRenderTextureTargetType target,
                             qint32 baseLevel,
                             qint32 maxLevel) override;

    void updateTextureSwizzle(QSSGRenderBackendTextureObject to,
                              QSSGRenderTextureTargetType target,
                              QSSGRenderTextureSwizzleMode swizzleMode) override;

    bool setInputAssembler(QSSGRenderBackendInputAssemblerObject iao, QSSGRenderBackendShaderProgramObject po) override;

    void setDrawBuffers(QSSGRenderBackendRenderTargetObject rto, QSSGDataView<qint32> inDrawBufferSet) override;
    void setReadBuffer(QSSGRenderBackendRenderTargetObject rto, QSSGReadFace inReadFace) override;

    void renderTargetAttach(QSSGRenderBackendRenderTargetObject rto,
                            QSSGRenderFrameBufferAttachment attachment,
                            QSSGRenderBackendRenderbufferObject rbo) override
    {
        QSSGRenderBackendGLBase::renderTargetAttach(rto, attachment, rbo);
    }

    void renderTargetAttach(QSSGRenderBackendRenderTargetObject rto,
                            QSSGRenderFrameBufferAttachment attachment,
                            QSSGRenderBackendTextureObject to,
                            QSSGRenderTextureTargetType target = QSSGRenderTextureTargetType::Texture2D) override
    {
        QSSGRenderBackendGLBase::renderTargetAttach(rto, attachment, to, target);
    }

    void renderTargetAttach(QSSGRenderBackendRenderTargetObject rto,
                            QSSGRenderFrameBufferAttachment attachment,
                            QSSGRenderBackendTextureObject to,
                            qint32 level,
                            qint32 layer) override;
    void setReadTarget(QSSGRenderBackendRenderTargetObject rto) override;

    void blitFramebuffer(qint32 srcX0,
                         qint32 srcY0,
                         qint32 srcX1,
                         qint32 srcY1,
                         qint32 dstX0,
                         qint32 dstY0,
                         qint32 dstX1,
                         qint32 dstY1,
                         QSSGRenderClearFlags flags,
                         QSSGRenderTextureMagnifyingOp filter) override;
    void copyFramebufferTexture(qint32 srcX0,
                                qint32 srcY0,
                                qint32 width,
                                qint32 height,
                                qint32 dstX0,
                                qint32 dstY0,
                                QSSGRenderBackendTextureObject texture,
                                QSSGRenderTextureTargetType target) override;

    void *mapBuffer(QSSGRenderBackendBufferObject bo,
                    QSSGRenderBufferType bindFlags,
                    size_t offset,
                    size_t length,
                    QSSGRenderBufferAccessFlags accessFlags) override;
    bool unmapBuffer(QSSGRenderBackendBufferObject bo, QSSGRenderBufferType bindFlags) override;

    qint32 getConstantBufferCount(QSSGRenderBackendShaderProgramObject po) override;
    qint32 getConstantBufferInfoByID(QSSGRenderBackendShaderProgramObject po,
                                     quint32 id,
                                     quint32 nameBufSize,
                                     qint32 *paramCount,
                                     qint32 *bufferSize,
                                     qint32 *length,
                                     char *nameBuf) override;
    void getConstantBufferParamIndices(QSSGRenderBackendShaderProgramObject po, quint32 id, qint32 *indices) override;
    void getConstantBufferParamInfoByIndices(QSSGRenderBackendShaderProgramObject po,
                                             quint32 count,
                                             quint32 *indices,
                                             QSSGRenderShaderDataType *type,
                                             qint32 *size,
                                             qint32 *offset) override;
    void programSetConstantBlock(QSSGRenderBackendShaderProgramObject po, quint32 blockIndex, quint32 binding) override;
    void programSetConstantBuffer(quint32 index, QSSGRenderBackendBufferObject bo) override;

    QSSGRenderBackendQueryObject createQuery() override;
    void releaseQuery(QSSGRenderBackendQueryObject qo) override;
    void beginQuery(QSSGRenderBackendQueryObject qo, QSSGRenderQueryType type) override;
    void endQuery(QSSGRenderBackendQueryObject qo, QSSGRenderQueryType type) override;
    void getQueryResult(QSSGRenderBackendQueryObject qo, QSSGRenderQueryResultType resultType, quint32 *params) override;
    void getQueryResult(QSSGRenderBackendQueryObject qo, QSSGRenderQueryResultType resultType, quint64 *params) override;
    void setQueryTimer(QSSGRenderBackendQueryObject qo) override;

    QSSGRenderBackendSyncObject createSync(QSSGRenderSyncType tpye, QSSGRenderSyncFlags syncFlags) override;
    void releaseSync(QSSGRenderBackendSyncObject so) override;
    void waitSync(QSSGRenderBackendSyncObject so, QSSGRenderCommandFlushFlags syncFlags, quint64 timeout) override;

    void releaseInputAssembler(QSSGRenderBackendInputAssemblerObject iao) override;

protected:
    QSSGRenderBackendMiscStateGL *m_currentMiscState; ///< this holds the current misc state
#if defined(QT_OPENGL_ES_2)
    QSSGOpenGLES2Extensions *m_QSSGExtensions;
#else
    QOpenGLExtension_ARB_timer_query *m_timerExtension;
    QOpenGLExtension_ARB_tessellation_shader *m_tessellationShader;
    QOpenGLExtension_ARB_texture_multisample *m_multiSample;
    QSSGOpenGLExtensions *m_QSSGExtensions;
#endif
};

QT_END_NAMESPACE

#endif
