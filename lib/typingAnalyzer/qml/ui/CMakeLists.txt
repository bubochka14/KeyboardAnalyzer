set(QML_SOURCES
    "UILineEdit.qml"
    "UISlider.qml"
    "UIComboBox.qml"
)
set(QML_RESOURCES
)
set(CPP_SOURCES 
)
qt_add_library(ui STATIC)
QT_ADD_QML_MODULE(ui
    URI "components.ui"
    NO_PLUGIN
    RESOURCES 
        ${QML_RESOURCES}
    QML_FILES
        ${QML_SOURCES}
    DEPENDENCIES
        Quick
)
target_link_libraries(ui PRIVATE Qt::QmlPrivate Qt::QuickPrivate)
