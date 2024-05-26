qt_add_library(KeyboardWatcher STATIC 	
	"src/keyboardInterceptor.cpp"
	"src/winkeyboardinterceptor.cpp"  
	"include/keyboardInterceptor.h"
	"include/keyevent.h"
	"include/akeyboardInterceptor.h"
	"src/akeyboardInterceptor.cpp"
)
target_include_directories(KeyboardWatcher
    PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_sources(KeyboardWatcher PRIVATE "src/winkeyboardinterceptor.h" "src/keyboardinterceptor_private.h")
target_compile_definitions(KeyboardWatcher PRIVATE SHARED=false)
#install(TARGETS winKeyboardCapture
#  LIBRARY DESTINATION ${APP_BUILD}
#  RUNTIME DESTINATION ${APP_BUILD})

target_link_libraries(KeyboardWatcher PRIVATE 
	Qt6::Core 
	Qt6::Gui
	Qt6::Qml 
	Qt6::Quick 
)