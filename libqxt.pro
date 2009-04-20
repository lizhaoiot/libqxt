#
# Qxt main project file
#
# Do not edit this file.
# Use config.pri to specify compile options.
#
unix:!macx:include(features/unix/qxtbuild.prf)
win32:include(features/win32/qxtbuild.prf)
macx:include(features/macx/qxtbuild.prf)

TEMPLATE = subdirs
DESTDIR  = deploy/libs

#check Qt version
QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0)
QT_VER_MIN = $$member(QT_VERSION, 1)

lessThan(QT_VER_MAJ, 4) | lessThan(QT_VER_MIN, 2) {
   error(LibQxt requires Qt 4.2 or newer but Qt $$[QT_VERSION] was detected.)
}

docs.files = deploy/docs/*
#docs.commands = assistant -addContentFile $${docs.path}/index.dcf
docs.commands = $$qxtNativeSeparators(tools/doqsy/doqsy)

features.path = $$[QT_INSTALL_DATA]/mkspecs/features
features.files = deploy/qt/qxt.prf

docs.path = $${QXTINSTALLDIR}/docs
docs.CONFIG = no_default_install

INSTALLS += features docs

SUBDIRS += tools/doqsy
QMAKE_EXTRA_TARGETS += docs

exists( modules.prf ) {
    unix:system(rm -f modules.prf)
    win32:system(del modules.prf)
}

contains( QXT_BUILD, core ){
    message( building core module )
    sub_core.subdir = src/core
    SUBDIRS += sub_core
    system(echo QXT_MODULES+=core >> modules.prf)
}

contains( QXT_BUILD, gui ){
    message( building gui module )
    sub_gui.subdir = src/gui
    sub_gui.depends = sub_core
    SUBDIRS += sub_gui
    system(echo QXT_MODULES+=gui >> modules.prf)
    contains( QXT_BUILD, designer ){
        sub_designer.subdir = src/designer
        sub_designer.depends = sub_core sub_gui
        SUBDIRS += sub_designer
        system(echo QXT_MODULES+=designer >> modules.prf)
    }
}

contains( QXT_BUILD, network ){
    message( building network module )
    sub_network.subdir = src/network
    sub_network.depends = sub_core
    SUBDIRS += sub_network
    system(echo QXT_MODULES+=network >> modules.prf)
}

contains( QXT_BUILD, sql ){
    message( building sql module )
    sub_sql.subdir = src/sql
    sub_sql.depends = sub_core
    SUBDIRS += sub_sql
    system(echo QXT_MODULES+=sql >> modules.prf)
}

contains(DEFINES,HAVE_DB){
contains( QXT_BUILD, berkeley ){
    message( building berkeley module )
    sub_berkeley.subdir = src/berkeley
    sub_berkeley.depends = sub_core
    SUBDIRS += sub_berkeley
    system(echo QXT_MODULES+=berkeley >> modules.prf)
}
}

contains( QXT_BUILD, web ){
    message( building web module )
    sub_web.subdir = src/web
    sub_web.depends = sub_core sub_network
    SUBDIRS += sub_web
    system(echo QXT_MODULES+=web >> modules.prf)
}

contains( QXT_BUILD, crypto ){
    message( building crypto module )
    sub_crypto.subdir = src/crypto
    sub_crypto.depends = sub_core
    SUBDIRS += sub_crypto
    system(echo QXT_MODULES+=crypto >> modules.prf)
}

#write the paths to prf file
unix:system((echo QXTbase=$${QXTINSTALLDIR}; echo QXTinclude=$${include.path}; echo QXTbin=$${bin.path}; echo QXTlib=$${target.path}; cat modules.prf; cat deploy/qt/qxt.prf.m) > deploy/qt/qxt.prf)

#windows supports similar syntax
win32:system((echo QXTbase=$${QXTINSTALLDIR}& echo QXTinclude=$${include.path} & echo QXTbin=$${bin.path} & echo QXTlib=$${target.path} & type modules.prf & type deploy\qt\qxt.prf.m) > deploy\qt\qxt.prf)

style.CONFIG = recursive
style.recurse = $$SUBDIRS
style.recurse -= tools/doqsy
style.recurse_target = astyle
QMAKE_EXTRA_TARGETS += style

sub-examples.commands += cd examples && $(QMAKE) examples.pro && $(MAKE)
QMAKE_EXTRA_TARGETS += sub-examples

sub-tests.commands += cd tests && $(QMAKE) tests.pro && $(MAKE)
QMAKE_EXTRA_TARGETS += sub-tests

runtests.depends += sub-tests
runtests.commands += cd tests && $(MAKE) test
QMAKE_EXTRA_TARGETS += runtests

cov_zerocounters.CONFIG += recursive
cov_zerocounters.recurse = $$SUBDIRS
cov_zerocounters.recurse -= tools/doqsy sub_designer
cov_zerocounters.recurse_target = zerocounters
QMAKE_EXTRA_UNIX_TARGETS += cov_zerocounters

cov_capture.CONFIG += recursive
cov_capture.recurse = $$SUBDIRS
cov_capture.recurse -= tools/doqsy sub_designer
cov_capture.recurse -= sub_sql sub_crypto # TODO: write unit tests for these!
cov_capture.recurse_target = capture
QMAKE_EXTRA_UNIX_TARGETS += cov_capture

cov_genhtml.CONFIG += recursive
cov_genhtml.recurse = $$SUBDIRS
cov_genhtml.recurse -= tools/doqsy sub_designer
cov_genhtml.recurse -= sub_sql sub_crypto # TODO: write unit tests for these!
cov_genhtml.recurse_target = genhtml
QMAKE_EXTRA_UNIX_TARGETS += cov_genhtml

coverage.depends += first cov_zerocounters runtests cov_capture cov_genhtml
QMAKE_EXTRA_UNIX_TARGETS += coverage
