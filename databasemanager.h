#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>


class DatabaseManager
{
public:
    // 构造函数，传入数据库文件名
    explicit DatabaseManager(const QString &dbName);
    ~DatabaseManager();

    // 初始化数据库并创建表
    bool initialize();

    // 获取表模型
    QSqlTableModel* getModel();

    // 增加1行
    bool addRow(int percentage, double powerFactor, int duration);

    // 批量插入多行数据
    void addMultipleRows(int numRows);

    // 分页加载数据
    void loadMoreData(int rowsPerPage, int currentPage);

    // 删除1行
    bool removeRow(int row);

    // 清空所有行
    bool clearRows();

    // 上移选中的行
    bool moveRowUp(int row);

    // 下移选中的行
    bool moveRowDown(int row);

    // 获取数据库错误信息
    QString lastError() const;

    void loadMoreData_2(int batchSize);
    int currentRowIndex = 0;  // 初始化加载起点


private:
    QSqlDatabase db;
    QSqlTableModel* model;
};

#endif // DATABASEMANAGER_H
