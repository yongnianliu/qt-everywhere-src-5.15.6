TEMPLATE = aux
TARGET = dummy

CONFIG += single_arch
CONFIG -= qt android_install

javaresources.files = \
    $$PWD/res \
    $$PWD/src

javaresources.path = $$[QT_INSTALL_PREFIX]/src/android/java

INSTALLS += javaresources

!prefix_build:!equals(OUT_PWD, $$PWD) {
    COPIES += javaresources

    RETURN = $$escape_expand(\\n\\t)
    equals(QMAKE_HOST.os, Windows) {
        RETURN = $$escape_expand(\\r\\n\\t)
    }
    OUT_PATH = $$shell_path($$OUT_PWD)

    QMAKE_POST_LINK += \
        $${QMAKE_COPY_DIR} $$shell_path($$PWD/res) $$OUT_PATH $$RETURN \
        $${QMAKE_COPY_DIR} $$shell_path($$PWD/src) $$OUT_PATH
}
