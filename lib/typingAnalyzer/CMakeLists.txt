# CMakeList.txt: проект CMake для TypingAnalyzer; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта

set(QML_SOURCES 

)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qml)

set (CPP_SOURCES 
	"wordcounter.h" 
	"wordcounter.cpp" 
	"typewriterSP.h" 
	"typewritersp.cpp"
	"timefocusmodel.cpp"
	"timefocusmodel.h"
	"applicationsettings.h"
	"applicationsettings.cpp"
	"soundinterfaces.h"
	"soundinterfaces.cpp"
    "pageapplication.h"
    "pageapplication.cpp"
	"customkbproducer.h" 
	"customkbproducer.cpp" 
	"apppage.h" 
	"namedobject.h" 
	"slidersetting.h"
	"slidersetting.cpp"
	"timefocuspage.h" 
	"apppage.cpp" 
	"timefocuspage.cpp"
	"settingslist.h"
	"timefocusexecutable.h" 
	"timefocusexecutable.cpp" 
	"executable.h"  
	"settingspage.h" 
	"namedobject.cpp" 
	"settingspage.cpp" 
	"executable.cpp" 
    "typingmeter.h"
	"customperiodproducer.h"
	"customperiodproducer.cpp"
	"aconfigurable.h"
	"aconfigurable.cpp"
    "typingmeter.cpp"
	"freemodepage.h" 
	"freemodepage.cpp" 
	"typingrate.h" 
	"typingrate.cpp" 
	"appsetting.h" 
	"iqmlcontent.h" 
	"appsetting.cpp" 
	"listsetting.h" 
	"listsetting.cpp" 
	"contentbuilder.h" 
	"contentbuilder.cpp" 
	"executablekbproducer.h" 
	"executablekbproducer.cpp" 
	"application.h" 
    "application.cpp"
	"executableholder.h" 
	"executableholder.cpp"
)
QT_ADD_QML_MODULE(TypingAnalyzer STATIC
	URI "TypingAnalyzer"
	SOURCES ${CPP_SOURCES}
	QML_FILES ${QML_SOURCES}
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET TypingAnalyzer PROPERTY CXX_STANDARD 20)
endif()
target_link_libraries(TypingAnalyzer PRIVATE 
	Qt6::Core 
	Qt6::Qml 
    Qt6::Gui
	Qt6::Charts
	Qt6::Multimedia
	Qt6::Quick 
	KeyboardWatcher
    components
)

add_subdirectory(qml)
