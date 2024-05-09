set(QML_SOURCES
    "SettingsPage.qml"
    "MainWindow.qml"
    "WPMChart.qml"
    "Main.qml"
    "MyHeader.qml"
    "Typewriter.qml"
    "MenuButton.qml"
    "ImageButton.qml"
    "TimeFocusPage.qml"
)
set(QML_RESOURCES
    "icons/menu.png"
    "icons/chart.svg"
    "icons/settings.svg"
    "pics/typewriter.png"
    "pics/coffee.svg"
    "pics/completed.svg"
)
set(CPP_SOURCES 
)
add_subdirectory(ui)
QT_ADD_QML_MODULE(qml STATIC
    PLUGIN_TARGET qml
    URI qml
    RESOURCES 
        ${QML_RESOURCES}
    QML_FILES
        ${QML_SOURCES}
    SOURCES
        ${CPP_SOURCES}
    DEPENDENCIES
        Quick
        ui
        QML_FILES PageSelector.qml
        QML_FILES FreeModePage.qml
        QML_FILES WpmStatistics.qml
        QML_FILES TimeFocusPanel.qml
        QML_FILES StatisticsDialog.qml
        QML_FILES TimeField.qml
    IMPORT_PATH "${QT_QML_OUTPUT_DIRECTORY}/qml/ui"


)
target_link_libraries(qml PRIVATE Qt::QmlPrivate Qt::QuickPrivate ui)
