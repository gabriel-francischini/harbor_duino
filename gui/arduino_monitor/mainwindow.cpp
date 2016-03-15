#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui_area = new QWidget;
    createMenuBar();


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);

    editor = new QTextEdit;
    editor->setCursorWidth(7);
    mainLayout->addWidget(editor);
    setCentralWidget(ui_area);
    ui_area->setLayout(mainLayout);
    setWindowTitle(tr("Monitor de Arduino"));
}

MainWindow::~MainWindow()
{

}


void MainWindow::createMenuBar(){
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&Arquivo"),this);
    exit = fileMenu->addAction(tr("&Sair"));
    menuBar->addMenu(fileMenu);

    connect(exit, SIGNAL(triggered()), this, SLOT(close()));

}
