#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建数据库管理类实例，传入数据库文件名
    dbManager = new DatabaseManager("data.db");

    // 初始化数据库
    if (!dbManager->initialize()) {
        QMessageBox::critical(this, "Error", "Failed to initialize database: " + dbManager->lastError());
        return;
    }

    // 设置模型和视图
    setupModelAndView();

    // 连接信号槽
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addRow);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::removeRow);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::clearRows);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::moveRowUp);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::moveRowDown);
    // 连接按钮点击事件到 addMultipleRows() 槽
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::addMultipleRows);


    // 连接滚动条事件，后期有大数据需求再解开
//        connect(ui->tableView->verticalScrollBar(), &QScrollBar::valueChanged, this, &MainWindow::handleScroll);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbManager;  // 释放数据库管理类
}


void MainWindow::handleScroll(int value)
{
    int maxScrollValue = ui->tableView->verticalScrollBar()->maximum();

    // 如果滚动条已经到达底部
    if (value == maxScrollValue) {
        dbManager->loadMoreData_2(20);  // 每次加载20行数据
    }
}

void MainWindow::setupModelAndView()
{
    QSqlTableModel* model = dbManager->getModel();

    // 设置表头
    model->setHeaderData(1, Qt::Horizontal, tr("总功率百分比(%)"));
    model->setHeaderData(2, Qt::Horizontal, tr("功率因数"));
    model->setHeaderData(3, Qt::Horizontal, tr("持续时间"));

    // 设置QTableView
    ui->tableView->setModel(model);

    // 设置单行选中和不可编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}


// 一键增加批量数据
void MainWindow::addMultipleRows()
{
    dbManager->addMultipleRows(100);  // 调用DatabaseManager封装的addMultipleRows方法
}


void MainWindow::addRow()
{
    // 初始化随机数生成器（只需要一次）
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    // 生成模拟数据
    int percentage = rand() % 101;  // 生成0到100之间的随机整数（模拟百分比）
    double powerFactor = static_cast<double>(rand() % 101) / 100.0;  // 生成0.0到1.0之间的随机小数（模拟功率因数）
    int duration = rand() % 100 + 1;  // 生成1到100之间的随机整数（模拟持续时间）

    // 调用dbManager的addRow方法插入新行
    if (!dbManager->addRow(percentage, powerFactor, duration)) {
        QMessageBox::warning(this, "Error", "Failed to add row: " + dbManager->lastError());
    }
}

void MainWindow::removeRow()
{
    int row = ui->tableView->currentIndex().row();
    if (row >= 0) {
        if (!dbManager->removeRow(row)) {
            QMessageBox::warning(this, "Error", "Failed to remove row: " + dbManager->lastError());
        }
    }
}

void MainWindow::clearRows()
{
    if (!dbManager->clearRows()) {
        QMessageBox::warning(this, "Error", "Failed to clear rows: " + dbManager->lastError());
    }
}

void MainWindow::moveRowUp()
{
    int row = ui->tableView->currentIndex().row();
    if (row > 0) {
        if (!dbManager->moveRowUp(row)) {
            QMessageBox::warning(this, "Error", "Failed to move row up: " + dbManager->lastError());
        }
    }
}

void MainWindow::moveRowDown()
{
    int row = ui->tableView->currentIndex().row();
    if (row < dbManager->getModel()->rowCount() - 1) {
        if (!dbManager->moveRowDown(row)) {
            QMessageBox::warning(this, "Error", "Failed to move row down: " + dbManager->lastError());
        }
    }
}


