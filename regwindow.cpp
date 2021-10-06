#include "regwindow.h"

RegWindow::RegWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Registration");
//------------------Building Window of Registration-----------//
    QGroupBox* pgbx = new QGroupBox("Registration form", this);
    QLabel* plbl_login = new QLabel("&Login:");
    pedt_login = new QLineEdit;
    plbl_login->setBuddy(pedt_login);
    QLabel* plbl_password = new QLabel("&Password:");
    pedt_password = new QLineEdit;
    plbl_password->setBuddy(pedt_password);
    pedt_password->setEchoMode(QLineEdit::Password);
    QLabel* plbl_confirm = new QLabel("&Confirm:");
    pedt_confirm = new QLineEdit;
    plbl_confirm->setBuddy(pedt_password);
    pedt_confirm->setEchoMode(QLineEdit::Password);
    pbtnRegister = new QPushButton("Register");

    QGridLayout* pgrd = new QGridLayout;
    pgrd->addWidget(pedt_login, 0, 1);
    pgrd->addWidget(pedt_password, 1, 1);
    pgrd->addWidget(pedt_confirm, 2, 1);
    pgrd->addWidget(plbl_login, 0, 0);
    pgrd->addWidget(plbl_password, 1, 0);
    pgrd->addWidget(plbl_confirm, 2, 0);
    pgrd->addWidget(pbtnRegister, 3, 0, 1, 2);
    pgbx->setLayout(pgrd);

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    QHBoxLayout* phbxLayout = new QHBoxLayout;
    hint = new QLabel;

    pvbxLayout->addStretch(1);
    pvbxLayout->addWidget(pgbx);
    pvbxLayout->addWidget(hint);
    pvbxLayout->addStretch(1);

    phbxLayout->addStretch(1);
    phbxLayout->addLayout(pvbxLayout);
    phbxLayout->addStretch(1);

    setLayout(phbxLayout);
//------------------Connection of signals and slots---------------//
    SetConnection();
}

QString RegWindow::GetLogin()
{
    return login;
}

QString RegWindow::GetPassword()
{
    return password;
}

bool RegWindow::Check()
{
    return password == confirm;
}

QLabel *RegWindow::GetHint()
{
    return hint;
}

void RegWindow::SetLoginFromEdit(const QString & str)
{
    login = str;
}

void RegWindow::SetPasswordFromEdit(const QString & str)
{
    password = str;
}

void RegWindow::SetConfirmFromEdit(const QString & str)
{
    confirm = str;
}


void RegWindow::SetConnection()
{
    connect(pbtnRegister, SIGNAL(clicked()), SIGNAL(RegRegisterSignal()));
    connect(pedt_login, SIGNAL(textEdited(const QString &)),
            SLOT(SetLoginFromEdit(const QString &)));
    connect(pedt_password, SIGNAL(textEdited(const QString &)),
            SLOT(SetPasswordFromEdit(const QString &)));
    connect(pedt_confirm, SIGNAL(textEdited(const QString &)),
            SLOT(SetConfirmFromEdit(const QString &)));

}
