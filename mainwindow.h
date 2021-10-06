#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include "authwindow.h"
#include "regwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Display();
private:
    AuthWindow auth;
    RegWindow reg;
    QSqlDatabase db;

private:
    bool DbConnection();

signals:

public slots:
    void ShowRegisterWindow();
    void AuthorizeUser();
    void RegisterUser();

};

#endif // MAINWINDOW_H
