#include "QT6TEST/inc/qt6_test.hpp"
#include <QApplication>
#include <QWidget>
#include "ui_mywidget.h"

int qt6_test(int argc,char **argv)
{
    QApplication app(argc, argv);

    // 创建主窗口和 UI 对象
    QWidget mainWindow;
    Ui::MyWidget ui;        // Ui 命名空间中的类名与 .ui 文件中的 class 属性一致
    ui.setupUi(&mainWindow);

    // 设置窗口标题
    mainWindow.setWindowTitle("Hello Qt6!");

    // 显示窗口
    mainWindow.show();

    return app.exec();
}