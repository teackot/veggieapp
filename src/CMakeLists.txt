include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/..)

add_executable(veggieapp
    main.cpp

    MainWindow.h
    MainWindow.cpp
    MainWindow.ui

    ConnectionDialog.h
    ConnectionDialog.cpp
    ConnectionDialog.ui
    AddDialog.h AddDialog.cpp AddDialog.ui
    ModifyDialog.h ModifyDialog.cpp ModifyDialog.ui
    PrintDialog.h PrintDialog.cpp PrintDialog.ui
)

target_link_libraries(veggieapp PRIVATE
    Qt::Widgets
    Qt::Sql
    Qt::PrintSupport
)

include(GNUInstallDirs)
install(TARGETS veggieapp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
