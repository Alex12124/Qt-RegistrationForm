#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>

class RegWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RegWindow(QWidget *parent = nullptr);
    QString GetLogin();
    QString GetPassword();
    bool Check();
    QLabel *GetHint();

public slots:
    void SetLoginFromEdit(const QString &);
    void SetPasswordFromEdit(const QString &);
    void SetConfirmFromEdit(const QString &);

signals:
    void RegRegisterSignal();
private:
//------------Widgets-----------------//
    QPushButton* pbtnRegister;
    QLineEdit* pedt_login;
    QLineEdit* pedt_password;
    QLineEdit* pedt_confirm;
    QLabel* hint;
//------------Connection Method-------//
    void SetConnection();
//------------Local variables---------//
    QString login;
    QString password;
    QString confirm;
};

#endif // REGWINDOW_H
