include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/..)

add_executable(veggieapp
    main.cpp

    MainWindow.h
    MainWindow.cpp
    MainWindow.ui

    ConnectionDialog.h
    ConnectionDialog.cpp
    ConnectionDialog.ui
)

target_link_libraries(veggieapp PRIVATE
    Qt::Widgets
    Qt::Sql
)

include(GNUInstallDirs)
install(TARGETS veggieapp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
