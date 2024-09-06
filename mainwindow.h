#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>
#include <QSqlRecord>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addRow();
    void removeRow();
    void clearRows();
    void moveRowUp();
    void moveRowDown();

    void addMultipleRows();



    void handleScroll(int value);

private:
    Ui::MainWindow *ui;
    DatabaseManager* dbManager;  // 数据库管理类指针

    int rowsPerPage = 50;        // 每次加载50行数据


    void setupModelAndView();
};

#endif // MAINWINDOW_H
