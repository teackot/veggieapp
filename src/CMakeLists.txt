include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/..
)

add_executable(veggieapp
    main.cpp

    MainWindow.h
    MainWindow.cpp

    ConnectionDialog.h
    ConnectionDialog.cpp

    AddDialog.h
    AddDialog.cpp

    ModifyDialog.h
    ModifyDialog.cpp

    PrintDialog.h
    PrintDialog.cpp

    ui/MainWindow.ui
    ui/ConnectionDialog.ui
    ui/AddDialog.ui
    ui/ModifyDialog.ui
    ui/PrintDialog.ui
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
