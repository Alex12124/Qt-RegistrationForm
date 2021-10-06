#include "authwindow.h"

AuthWindow::AuthWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Authorization");
//------------------Building Window of Authorization-----------//
    QGroupBox* pgbx = new QGroupBox("Authorization form", this);
    QLabel* plbl_login = new QLabel("&Login:");
    pedt_login = new QLineEdit;
    plbl_login->setBuddy(pedt_login);
    QLabel* plbl_password = new QLabel("&Password:");
    pedt_password = new QLineEdit;
    plbl_password->setBuddy(pedt_password);
    pedt_password->setEchoMode(QLineEdit::Password);

    pbtnEnter = new QPushButton("Sign in");
    pbtnRegister = new QPushButton("Sign up");
    hint = new QLabel;
    QGridLayout* pbuttons = new QGridLayout;
    pbuttons->addWidget(pbtnEnter, 0, 0);
    pbuttons->addWidget(pbtnRegister, 0, 1);
    pbuttons->addWidget(hint, 1, 0, 2, 1);

    QGridLayout* pgrdLayout = new QGridLayout;
    QHBoxLayout* cphbxLayout = new QHBoxLayout;
    QVBoxLayout* cpvbxLayout = new QVBoxLayout;
    pgrdLayout->addWidget(plbl_login, 0, 0);
    pgrdLayout->addWidget(pedt_login, 0, 1);
    pgrdLayout->addWidget(plbl_password, 1, 0);
    pgrdLayout->addWidget(pedt_password, 1, 1);
    pgbx->setLayout(pgrdLayout);
    pgbx->resize(350, 250);

    cpvbxLayout->addStretch(1);
    cpvbxLayout->addWidget(pgbx);
    cpvbxLayout->addLayout(pbuttons);
    cpvbxLayout->addStretch(1);

    cphbxLayout->addStretch(1);
    cphbxLayout->addLayout(cpvbxLayout);
    cphbxLayout->addStretch(1);

    setLayout(cphbxLayout);
//------------------Connection of signals and slots---------------//
    SetConnection();

}

QString AuthWindow::GetLogin()
{
    return login;
}

QString AuthWindow::GetPassword()
{
    return password;
}

QLabel *AuthWindow::GetHint()
{
    return hint;
}

void AuthWindow::SetConnection()
{
    connect(pbtnEnter, SIGNAL(clicked()), SIGNAL(AuthEnterSignal()));
    connect(pbtnRegister, SIGNAL(clicked()), SIGNAL(AuthRegisterSignal()));
    connect(pedt_login, SIGNAL(textEdited(const QString &)),
            SLOT(SetLoginFromEdit(const QString &)));
    connect(pedt_password, SIGNAL(textEdited(const QString &)),
            SLOT(SetPasswordFromEdit(const QString &)));
}

void AuthWindow::SetLoginFromEdit(const QString & str)
{
    login = str;
}

void AuthWindow::SetPasswordFromEdit(const QString & str)
{
    password = str;
}



