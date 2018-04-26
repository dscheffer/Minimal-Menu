project(plugins)

set(plasmoidplugin_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PlasmoidPlugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KSMClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QDBusConnectionWrapperImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ApplicationLauncher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/QProcessWrapperImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RecentlyUsedHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ActivityEntry.cpp
)

set(plasmoidplugin_DEPS
    Qt5::Quick KF5::Plasma Qt5::DBus KF5::ConfigCore KF5::ActivitiesStats
)

find_package(KF5ActivitiesStats)
find_package(KF5Config)

add_library(plasmoidplugin SHARED ${plasmoidplugin_SRCS})

target_link_libraries(plasmoidplugin ${plasmoidplugin_DEPS})

install(TARGETS plasmoidplugin DESTINATION ${QML_INSTALL_DIR}/dscheffer/minimalmenuplugin)

install(FILES qmldir DESTINATION ${QML_INSTALL_DIR}/dscheffer/minimalmenuplugin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(test_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tests/GTestWidget.cpp)

add_executable(applicationLauncherTest ${test_MAIN} ${CMAKE_CURRENT_SOURCE_DIR}/tests/ApplicationLauncherTest.cpp ${plasmoidplugin_SRCS})
target_link_libraries(applicationLauncherTest gmock ${Qt5Widgets_LIBRARIES} ${plasmoidplugin_DEPS} -lpthread -lm)

add_executable(recentlyUsedTest ${test_MAIN} ${CMAKE_CURRENT_SOURCE_DIR}/tests/RecentlyUsedHandlerTest.cpp ${plasmoidplugin_SRCS})
target_link_libraries(recentlyUsedTest gmock ${Qt5Widgets_LIBRARIES} ${plasmoidplugin_DEPS} -lpthread -lm)

add_executable(ksmClientTest ${test_MAIN} ${CMAKE_CURRENT_SOURCE_DIR}/tests/KSMClientTest.cpp ${plasmoidplugin_SRCS})
target_link_libraries(ksmClientTest gmock ${Qt5Widgets_LIBRARIES} ${plasmoidplugin_DEPS} -lpthread -lm)

add_test(ApplicationLauncherTest applicationLauncherTest)
add_test(RecentlyUsedHandlerTest recentlyUsedTest)
add_test(KSMClientTest ksmClientTest)