#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>

class AuthWindow : public QWidget
{
    Q_OBJECT
public:
    AuthWindow(QWidget* parent = 0);
    QString GetLogin();
    QString GetPassword();
    QLabel *GetHint();
private:
//------------Widgets-----------------//
    QPushButton* pbtnEnter;
    QPushButton* pbtnRegister;
    QLineEdit* pedt_login;
    QLineEdit* pedt_password;
    QLabel* hint;
//------------Connection Method-------//
    void SetConnection();
//------------Local variables---------//
    QString login;
    QString password;

private slots:
    void SetLoginFromEdit(const QString &);
    void SetPasswordFromEdit(const QString &);

signals:
    void AuthEnterSignal();
    void AuthRegisterSignal();
};

#endif // AUTHWINDOW_H
