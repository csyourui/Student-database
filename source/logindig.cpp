#include "logindig.h"
#include "ui_logindig.h"
#include "admin.h"
#include "student.h"
#include "teacher.h"
#include "database.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QVBoxLayout>
#include <QButtonGroup>

QString userID;
QString userName;
LoginDig::LoginDig(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginDig)
{

    ui->setupUi(this);
    //
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::white);

    //设置调色板,用于设置logindialog的背景
    this->setMaximumSize(462,340);
    this->setMinimumSize(462,340);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/login.jpg").scaled(this->size())));
    this->setPalette(palette);

    //设置登陆和重置的图标
    ui->loginbtn->setIcon(QIcon(":/login_in.gif"));
    ui->refreshbtn->setIcon(QIcon(":/login_res.gif"));

    //用户名旁边的图片
    QPixmap userlogo;
    userlogo.load(":/user.png");
    ui->user->setPixmap(userlogo);

    //密码旁边的图片
    QPixmap pwdlogo;
    pwdlogo.load(":/password.png");
    ui->pwd->setPixmap(pwdlogo);

    //设置登陆按钮不可用
    ui->loginbtn->setEnabled(false);
    //设置lineedit提示语句
    ui->userline->setPlaceholderText("请输入用户名");
    ui->passwordline->setPlaceholderText("请输入密码");
    ui->loginbtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->refreshbtn->setCursor(QCursor(Qt::PointingHandCursor));

    //设置密码输入框显示为密码模式
    ui->passwordline->setEchoMode(QLineEdit::Password);

    //设置登录按钮可用
    connect(ui->userline,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));
    connect(ui->passwordline,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));

    //选择
    radiogroup=new QButtonGroup(this);
    radiogroup->addButton(ui->studentradio,0);
    radiogroup->addButton(ui->teacherradio,1);

    connect(ui->passwordline, SIGNAL(returnPressed()), ui->loginbtn, SIGNAL(clicked()), Qt::UniqueConnection);
    connect(ui->userline, SIGNAL(returnPressed()), ui->loginbtn, SIGNAL(clicked()), Qt::UniqueConnection);


    //
    ui->userline->setText("admin");
    ui->passwordline->setText("admin");
}



LoginDig::~LoginDig()
{
    delete ui;
}

void LoginDig::on_loginbtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    userID = ui->userline->text();
    QString password = ui->passwordline->text();


    if(!this->judgeEmpty())
    {
        ui->passwordline->clear();
        return;
    }
    if(radiogroup->checkedId()==0)
    {
        QString Strs=QString("select * from Student where Id = '%1';").arg(userID);
        query.exec(Strs);
        query.first();
//        QString StudentId = query.value(0).toString();
        userName = query.value(1).toString();
//        int StudentSex = query.value(2).toInt();
//        int StudentEntranceAge = query.value(3).toInt();
//        QString StudentEntranceYear = query.value(4).toString();
//        QString StudentClass = query.value(5).toString();
        QString StudentPwd = query.value(6).toString();
        if(StudentPwd == password)
        {
            this->close();
            Student* s = new Student();
            s->show();
        }
        else
        {
             QMessageBox::warning(this,"警告","密码错误或不存在此用户");
        }
    }
    else if(radiogroup->checkedId()==1)
    {
        QString Strt=QString("select * from Teacher where Id = '%1';").arg(userID);
        query.exec(Strt);
        query.first();

//        QString TeacherId = query.value(0).toString();
        userName = query.value(1).toString();
        QString TeacherPwd = query.value(5).toString();

        if(TeacherPwd == password)
        {
//            QMessageBox::warning(this,"警告",userName);
            this->close();
            Teacher* s = new Teacher();
            s->show();
        }
        else
        {
             QMessageBox::warning(this,"警告","密码错误或不存在此用户");
        }
    }
    else if((ui->userline->text()=="admin")&&(ui->passwordline->text()=="admin"))
        {
            userID = "admin";
            userName = "管理员";
            this->close();
            Admin* a = new Admin();
            a->show();
        }

}

void LoginDig::on_refreshbtn_clicked()
{
    ui->userline->clear();
    ui->passwordline->clear();
}
void LoginDig::loginbtnSetSlot(QString)
{
    ui->loginbtn->setEnabled(true);
}
bool LoginDig::judgeEmpty()
{
    if(ui->userline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名不能为空");
        return false;
    }
    if(ui->passwordline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","密码不能为空");
        return false;
    }
    else
        return true;
}


