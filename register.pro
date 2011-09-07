 HEADERS     = RegistrationForm.h
 FORMS       = RegistrationForm.ui
 SOURCES     = RegistrationForm.cpp \
               main.cpp

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/designer/RegistrationForm
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro
 sources.path = $$[QT_INSTALL_EXAMPLES]/designer/RegistrationForm
 INSTALLS += target sources

 symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
