#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void afficherTable();
private slots:
    void on_pushButtonAddTable_clicked();
    void on_pushButtonSqlExecut_clicked();
    void on_listWidgetTablesList_itemClicked(QListWidgetItem *item);

    void on_pushButtonChangeDatabase_clicked();
    void on_pushButtonDeleteEntry_clicked();
    void on_pushButtonInsertExecut_clicked();

    void on_action_Close_triggered();
    void on_actionChange_Database_triggered();


    void on_pushButtonDeleteTable_clicked();

private:
    Ui::MainWindow *ui;

    int getColumnNumber();
};

#endif // MAINWINDOW_H
