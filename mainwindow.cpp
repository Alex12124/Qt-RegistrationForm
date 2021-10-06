#include "mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Application");
    if(!DbConnection()) {
        qDebug() << "Failed to connect DB";
    }
    QSqlQuery query;
    QString str_query = "CREATE TABLE IF NOT EXISTS users ( "
                        "id int PRIMARY KEY, "
                        "login varchar(50), "
                        "password varchar(50));";
    if(!query.exec(str_query))
    {
        qDebug() << "Unable to create table" << query.lastError()
                 << " : " << query.lastQuery();
    }

    connect(&reg, SIGNAL(RegRegisterSignal()), SLOT(RegisterUser()));
    connect(&auth, SIGNAL(AuthEnterSignal()), SLOT(AuthorizeUser()));
    connect(&auth, SIGNAL(AuthRegisterSignal()), SLOT(ShowRegisterWindow()));
}

MainWindow::~MainWindow()
{
    db.close();
}

void MainWindow::Display()
{
    auth.show();
}

bool MainWindow::DbConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("testdb");
    if(!db.open()) {
        qDebug() << db.lastError().text();
        return false;
    } else {
        qDebug() << "success";
        db.exec("PRAGMA locking_mode = EXCLUSIVE");
        return true;
    }
}



void MainWindow::ShowRegisterWindow()
{
    reg.show();
}

void MainWindow::AuthorizeUser()
{
    QString username = auth.GetLogin();
    QString userpass = auth.GetPassword();
    QString str_query = "SELECT password, login "
                        "FROM users "
                        "WHERE login = '%1';";
    str_query = str_query.arg(username);
    QSqlQuery query;
    QSqlRecord rec;

    if(!query.exec(str_query))
    {
        qDebug() << "Unable to execute query - exiting" << query.lastError()
                 << " : " << query.lastQuery();
    }
    rec = query.record();
    query.next();

    QString login = query.value(rec.indexOf("login")).toString();
    QString password = query.value(rec.indexOf("password")).toString();

    if(username == login && userpass == password) {
        auth.close();
        reg.close();
        show();
    } else {
        auth.GetHint()->setText("Incorrect login or password");
    }
}

void MainWindow::RegisterUser()
{
    QString username = reg.GetLogin();
    QString userpass = reg.GetPassword();

    QString str_query = "SELECT COUNT(login) AS count "
                        "FROM users "
                        "WHERE login = '%1';";

    str_query = str_query.arg(username);

    QSqlQuery query;
    QSqlRecord rec;

    if(!query.exec(str_query)) {
        qDebug() << "Unable to execute query - exiting" << query.lastError()
                 << " : " << query.lastQuery();
    }
    rec = query.record();
    query.next();

    int count = query.value(rec.indexOf("count")).toInt();

    //count = 0 это уникальность логина
    if(count == 0) {

        if(reg.Check()) { // Проверка потверждения пароля

            if(userpass.size() < 8) { // Проверка на длину пароля
                reg.GetHint()->setText("Password is too short");
                return;
            } else {
                QString str_query_count = "SELECT COUNT(*) AS COUNT "
                                          "FROM users";
                if(!query.exec(str_query_count)) {
                    qDebug() << "Unable to Count" << query.lastError()
                             << " : " << query.lastQuery();
                }
                query.next();
                rec = query.record();
                int total_count = query.value(rec.indexOf("count")).toInt();

                str_query = "INSERT INTO users(id, login, password) "
                            "VALUES "
                            "(%1,'%2', '%3')";
                str_query = str_query.arg(QString::number(total_count + 1), username, userpass);
                if(!query.exec(str_query)) {
                    qDebug() << "Unable to insert data" << query.lastError()
                             << " : " << query.lastQuery();
                }

                reg.close();
                auth.show();
            }

        } else {
            reg.GetHint()->setText("Your password confirmation is not correct");
        }
    } else {
        reg.GetHint()->setText("This login is busy");
    }
}
