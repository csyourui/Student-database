#include "admin.h"
#include "ui_admin.h"
#include "logindig.h"
#include "database.h"
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QAbstractItemView>
#include <QLabel>
#include <QSqlRecord>
#include <QModelIndexList>
#include <QMessageBox>
#include <QtDebug>
#include <QStringList>
#include <QDialog>
#include <QComboBox>
double Aver_Grade_ad;
extern QString userID;
extern QString userName;
QString table="Student";
bool add=true;

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{  
    ui->setupUi(this);
    //LOGO
    QPixmap schoollogo;
    schoollogo.load(":/logo_school.png");
    ui->label_logo->setPixmap(schoollogo);
    ui->pushButton_student->setIcon(QIcon(":/button.png"));
    ui->pushButton_teacher->setIcon(QIcon(":/button.png"));
    ui->label_name->setText(userName);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onChanged(int)));

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    Admin::on_pushButton_student_clicked();
    //background
      QPixmap background;
      background.load(":/backg.jpg");
      QPalette palette = this->palette();
      palette.setBrush(backgroundRole(), QBrush(background));
      setPalette(palette);


}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_exit_clicked()
{
    this->close();
}

void Admin::compute_all()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    Aver_Grade_ad=0;
    QString find = QString("SELECT Grade FROM CourseSelection");
    query.exec(find);
    int i = 0;
    while (query.next())
    {
        Aver_Grade_ad += query.value(0).toDouble();
        i++;
    }
   if(i)
        Aver_Grade_ad=  Aver_Grade_ad/i;
   QString AverT = QString::number(Aver_Grade_ad);
   ui->label_grade->setText(AverT );

}
void Admin::avg (QString Class){
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    QString find = QString("SELECT CourseSelection.grade "
                         "From Student, CourseSelection "
                         "Where Student.Id = CourseSelection.StudentId "
                         "And Student.Class=='%1'").arg(Class);
    query.exec(find);
    Aver_Grade_ad=0;
    query.exec(find);
    int i = 0;
    while (query.next())
    {
        Aver_Grade_ad += query.value(0).toDouble();
        i++;
    }
   if(i)
        Aver_Grade_ad=  Aver_Grade_ad/i;
    QString AverT = QString::number(Aver_Grade_ad);
    ui->label_grade->setText(AverT );
}
void Admin::onChanged(int )
{
    if(ui->comboBox->currentText()=="所有班级"){
        Admin::compute_all();
        ui->label_avg->setText("所有同学平均成绩：");
    }
    else
    {
        Admin::avg(ui->comboBox->currentText());
        ui->label_avg->setText("该班平均成绩：");
    }

}
void Admin::on_pushButton_grade_clicked()
{
    table = "Grade";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(tr("SELECT Student.EntranceYear, Course.Name, Student.Class, Student.Name, CourseSelection.grade "
                       "From Student, Course, CourseSelection "
                       "Where Student.Id = CourseSelection.StudentId And Course.Id = CourseSelection.CourseId"
                       ""),db);
    model->setHeaderData(0, Qt::Horizontal, tr("年级"));
    model->setHeaderData(1, Qt::Horizontal, tr("课程"));
    model->setHeaderData(2, Qt::Horizontal, tr("班级"));
    model->setHeaderData(3, Qt::Horizontal, tr("学生"));
    model->setHeaderData(4, Qt::Horizontal, tr("成绩"));
    ui->tableView->setModel(model);
    ui->tableView->show();
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_avg->setVisible(true);
    ui->label_grade->setVisible(true);
    ui->pushButton_back->setVisible(false);
    ui->pushButton_search->setVisible(false);
    ui->name->setVisible(false);
    ui->id->setVisible(false);
    ui->coursename->setVisible(false);
    ui->courseid->setVisible(false);
    ui->comboBox->setVisible(true);
    ui->label_class->setVisible(true);
    ui->comboBox->addItem("所有班级");
    QSqlQuery query(db);
    QString serachclass=QString("select distinct Student.Class "
                                "from Student,CourseSelection "
                                "Where Student.Id = CourseSelection.StudentId;").arg(userID);
    query.exec(serachclass);
    while (query.next()) {
         ui->comboBox->addItem(query.value(0).toString());
    }
}



void Admin::on_pushButton_student_clicked()
{
    table = "Student";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT Id,Name,Sex,EntranceAge,EntranceYear,Class FROM Student"),db);
    model->setHeaderData(0, Qt::Horizontal, tr("学号"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("性别"));
    model->setHeaderData(3, Qt::Horizontal, tr("入学年龄"));
    model->setHeaderData(4, Qt::Horizontal, tr("入学年份"));
    model->setHeaderData(5, Qt::Horizontal, tr("班级"));
    ui->tableView->setModel(model);
    ui->tableView->show();
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->pushButton_back->setVisible(true);
    ui->pushButton_search->setVisible(true);
    ui->name->setVisible(true);
    ui->id->setVisible(true);
    ui->coursename->setVisible(false);
    ui->courseid->setVisible(false);
    ui->label_avg->setVisible(false);
    ui->label_grade->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->label_class->setVisible(false);

}

void Admin::on_pushButton_teacher_clicked()
{
    table = "Teacher";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT Id,Name,Course1,Course2,Course3 FROM Teacher"),db);

    model->setHeaderData(0, Qt::Horizontal, tr("教师号"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("课程1"));
    model->setHeaderData(3, Qt::Horizontal, tr("课程2"));
    model->setHeaderData(4, Qt::Horizontal, tr("课程3"));
    ui->tableView->setModel(model);
    ui->tableView->show();
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->pushButton_back->setVisible(true);
    ui->pushButton_search->setVisible(true);
    ui->name->setVisible(true);
    ui->id->setVisible(true);
    ui->coursename->setVisible(false);
    ui->courseid->setVisible(false);
    ui->label_avg->setVisible(false);
    ui->label_grade->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->label_class->setVisible(false);

}

void Admin::on_pushButton_course_clicked()
{
    table = "Course";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT * FROM Course"),db);

    model->setHeaderData(0, Qt::Horizontal, tr("课程编号"));
    model->setHeaderData(1, Qt::Horizontal, tr("课程"));
    model->setHeaderData(2, Qt::Horizontal, tr("教师号"));
    model->setHeaderData(3, Qt::Horizontal, tr("学分"));
    model->setHeaderData(4, Qt::Horizontal, tr("适合年级"));
    model->setHeaderData(5, Qt::Horizontal, tr("结课年份"));

    ui->tableView->setModel(model);
    ui->tableView->show();
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->pushButton_back->setVisible(true);
    ui->pushButton_search->setVisible(true);
    ui->name->setVisible(false);
    ui->id->setVisible(false);
    ui->coursename->setVisible(true);
    ui->courseid->setVisible(true);
    ui->label_avg->setVisible(false);
    ui->label_grade->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->label_class->setVisible(false);

}


void Admin::on_pushButton_selection_clicked()
{
    table = "CourseSelection";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT * FROM CourseSelection"),db);

    model->setHeaderData(0, Qt::Horizontal, tr("学生学号"));
    model->setHeaderData(1, Qt::Horizontal, tr("课程编号"));
    model->setHeaderData(2, Qt::Horizontal, tr("教师编号"));
    model->setHeaderData(3, Qt::Horizontal, tr("选课年份"));
    model->setHeaderData(4, Qt::Horizontal, tr("成绩"));

    ui->tableView->setModel(model);
    ui->tableView->show();

    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->pushButton_back->setVisible(true);
    ui->pushButton_search->setVisible(true);
    ui->name->setVisible(true);
    ui->id->setVisible(true);
    ui->coursename->setVisible(true);
    ui->courseid->setVisible(true);
    ui->label_avg->setVisible(false);
    ui->label_grade->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->label_class->setVisible(false);

}
void Admin::on_pushButton_add_clicked()
{
    dialog = new QDialog();
    if(add == true)
        dialog->setWindowTitle(tr("添加 %1 信息").arg(table));
    else if (add == false)
        dialog->setWindowTitle(tr("修改 %1 信息").arg(table));
    QGroupBox *box  = new QGroupBox(this);
    QPushButton *submitBtn = new QPushButton(tr("确认"));
    QPushButton *cancelBtn = new QPushButton(tr("取消"));
    connect(submitBtn,SIGNAL(clicked(bool)),this,SLOT(addNewToTable()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelBtnSlot()));
    if(table =="Student"){
        QLabel *idLabel  = new QLabel(tr("学号："));
        QLabel *nameLabel = new QLabel(tr("姓名："));
        QLabel *sexLabel  = new QLabel(tr("性别："));
        QLabel *eaLabel = new QLabel(tr("入学年龄:"));
        QLabel *eyLabel = new QLabel(tr("入学年份:"));
        QLabel *classLabel = new QLabel(tr("班级："));
        QLabel *pwdlabel = new QLabel(tr("密码："));
        //idLineEdit= new QLineEdit;
        idLineEdit = new QLineEdit;
        nameLineEdit = new QLineEdit;
        sexLineEdit = new QLineEdit;
        eaLineEdit = new QLineEdit;
        eyLineEdit = new QLineEdit;
        classLineEdit = new QLineEdit;
        pwdLineEdit  = new QLineEdit;
        pwdLineEdit->setEchoMode(QLineEdit::Password);

        QGridLayout *layout = new QGridLayout;
        layout->addWidget(idLabel,0,0,1,1);
        layout->addWidget(idLineEdit,0,1,1,1);
        layout->addWidget(nameLabel,1,0,1,1);
        layout->addWidget(nameLineEdit,1,1,1,1);
        layout->addWidget(sexLabel,2,0,1,1);
        layout->addWidget(sexLineEdit,2,1,1,1);
        layout->addWidget(eaLabel,3,0,1,1);
        layout->addWidget(eaLineEdit,3,1,1,1);
        layout->addWidget(eyLabel,4,0,1,1);
        layout->addWidget(eyLineEdit,4,1,1,1);
        layout->addWidget(classLabel,5,0,1,1);
        layout->addWidget(classLineEdit,5,1,1,1);
        layout->addWidget(pwdlabel,6,0,1,1);
        layout->addWidget(pwdLineEdit,6,1,1,1);
        layout->addWidget(submitBtn,7,0,1,1,Qt::AlignHCenter);
        layout->addWidget(cancelBtn,7,1,1,1,Qt::AlignHCenter);

        box->setLayout(layout);
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(box);
        dialog->setLayout(mainLayout);
        dialog->show();
    }
    if(table == "Teacher"){
        QLabel *idLabel  = new QLabel(tr("教师号："));
        QLabel *nameLabel = new QLabel(tr("姓名："));
        QLabel *course1Label  = new QLabel(tr("课程："));
        QLabel *course2Label = new QLabel(tr("课程:"));
        QLabel *course3Label = new QLabel(tr("课程:"));
        QLabel *pwdlabel = new QLabel(tr("密码："));

        idLineEdit = new QLineEdit;
        nameLineEdit = new QLineEdit;
        course1LineEdit = new QLineEdit;
        course2LineEdit = new QLineEdit;
        course3LineEdit = new QLineEdit;
        pwdLineEdit  = new QLineEdit;
        pwdLineEdit->setEchoMode(QLineEdit::Password);

        QGridLayout *layout = new QGridLayout;
        layout->addWidget(idLabel,0,0,1,1);
        layout->addWidget(idLineEdit,0,1,1,1);
        layout->addWidget(nameLabel,1,0,1,1);
        layout->addWidget(nameLineEdit,1,1,1,1);
        layout->addWidget(course1Label,2,0,1,1);
        layout->addWidget(course1LineEdit,2,1,1,1);
        layout->addWidget(course2Label,3,0,1,1);
        layout->addWidget(course2LineEdit,3,1,1,1);
        layout->addWidget(course3Label,4,0,1,1);
        layout->addWidget(course3LineEdit,4,1,1,1);
        layout->addWidget(pwdlabel,5,0,1,1);
        layout->addWidget(pwdLineEdit,5,1,1,1);
        layout->addWidget(submitBtn,6,0,1,1,Qt::AlignHCenter);
        layout->addWidget(cancelBtn,6,1,1,1,Qt::AlignHCenter);
        box->setLayout(layout);
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(box);
        dialog->setLayout(mainLayout);
        dialog->show();
    }
    if(table == "Course"){
        QLabel *idLabel  = new QLabel(tr("课程编号："));
        QLabel *nameLabel = new QLabel(tr("课程名称："));
        QLabel *courseTeacherLabel  = new QLabel(tr("授课教师编号："));
        QLabel *courseCreditLabel = new QLabel(tr("学分:"));
        QLabel *courseGradeLabel = new QLabel(tr("课程适合年级:"));
        QLabel *cancelYearlabel = new QLabel(tr("取消年份："));

        idLineEdit = new QLineEdit;
        nameLineEdit = new QLineEdit;

        courseTeacherLineEdit = new QLineEdit;
        courseCreditLineEdit = new QLineEdit;
        courseGradeLineEdit = new QLineEdit;
        cancelYearLineEdit  = new QLineEdit;

        QGridLayout *layout = new QGridLayout;
        layout->addWidget(idLabel,0,0,1,1);
        layout->addWidget(idLineEdit,0,1,1,1);
        layout->addWidget(nameLabel,1,0,1,1);
        layout->addWidget(nameLineEdit,1,1,1,1);
        layout->addWidget(courseTeacherLabel,2,0,1,1);
        layout->addWidget(courseTeacherLineEdit,2,1,1,1);
        layout->addWidget(courseCreditLabel,3,0,1,1);
        layout->addWidget(courseCreditLineEdit,3,1,1,1);
        layout->addWidget(courseGradeLabel,4,0,1,1);
        layout->addWidget(courseGradeLineEdit,4,1,1,1);
        layout->addWidget(cancelYearlabel,5,0,1,1);
        layout->addWidget(cancelYearLineEdit,5,1,1,1);
        layout->addWidget(submitBtn,6,0,1,1,Qt::AlignHCenter);
        layout->addWidget(cancelBtn,6,1,1,1,Qt::AlignHCenter);
        box->setLayout(layout);
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(box);
        dialog->setLayout(mainLayout);
        dialog->show();
    }
    if(table == "CourseSelection"){
        QLabel *studentIdLabel  = new QLabel(tr("学生学号："));
        QLabel *courseIdLabel = new QLabel(tr("课程编号："));
        QLabel *teacherIdLabel  = new QLabel(tr("教师编号："));
        QLabel *selectionYearLabel = new QLabel(tr("选课年份:"));
        QLabel *gradeLabel = new QLabel(tr("成绩:"));

        studentIdLineEdit = new QLineEdit;
        courseIdLineEdit = new QLineEdit;
        teacherIdLineEdit = new QLineEdit;
        selectionYearLineEdit  = new QLineEdit;
        gradeLineEdit  = new QLineEdit;
        gradeLineEdit->setEnabled(false);

        QGridLayout *layout = new QGridLayout;
        layout->addWidget(studentIdLabel,0,0,1,1);
        layout->addWidget(studentIdLineEdit,0,1,1,1);
        layout->addWidget(courseIdLabel,1,0,1,1);
        layout->addWidget(courseIdLineEdit,1,1,1,1);
        layout->addWidget(teacherIdLabel,2,0,1,1);
        layout->addWidget(teacherIdLineEdit,2,1,1,1);
        layout->addWidget(selectionYearLabel,3,0,1,1);
        layout->addWidget(selectionYearLineEdit,3,1,1,1);
        layout->addWidget(gradeLabel,4,0,1,1);
        layout->addWidget(gradeLineEdit,4,1,1,1);
        layout->addWidget(submitBtn,5,0,1,1,Qt::AlignHCenter);
        layout->addWidget(cancelBtn,5,1,1,1,Qt::AlignHCenter);
        box->setLayout(layout);
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(box);
        dialog->setLayout(mainLayout);
        dialog->show();

    }
}

bool Admin::addNewToTable()
{
    bool update =false;
    if(table == "Student"){
        QString id = idLineEdit->text();
        QString name = nameLineEdit->text();
        QString sex =sexLineEdit->text();
        int ea = eaLineEdit->text().toInt();
        QString ey = eyLineEdit->text();
        QString cls = classLineEdit->text();
        QString pwd = pwdLineEdit->text();

        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        bool success=false;
        QString find = QString("select * from Student where id = '%1'").arg(id);
        query.exec(find);
        query.first();
        update = query.value(0).toString()==id;
        if(update){
            qDebug()<<"update";
            QString update=QString("update Student set Name='%1',Sex='%2',EntranceAge='%3',EntranceYear= %4,Class ='%5', Password ='%6' where Id = '%7';"
                                ).arg(name).arg(sex).arg(ea).arg(ey).arg(cls).arg(pwd).arg(id);
            success = query.exec(update);
        }

        else {
            qDebug()<<"add";
            qDebug()<<"New student"<<id<<name<<sex<<ea<<ey<<cls<<pwd;
            QString add=QString("insert into Student values('%1','%2','%3',%4,'%5','%6','%7')"
                            ).arg(id).arg(name).arg(sex).arg(ea).arg(ey).arg(cls).arg(pwd);
            success = query.exec(add);
        }


        if(success)
        {
            if(!update){
                qDebug() << QObject::tr("添加成功");
                Admin::on_pushButton_student_clicked();
                QMessageBox::information(this,"添加","信息添加成功");

            }
            else if(update){
                qDebug() << QObject::tr("修改成功");
                Admin::on_pushButton_student_clicked();
                QMessageBox::information(this,"修改","信息修改成功");
            }
            dialog->close();
            Admin::clearSlot();
            return true;
        }
        else
        {
            if(!update)
                qDebug() << QObject::tr("添加失败");

            else if(update)
                qDebug() << QObject::tr("修改失败");

            if(id==""||name==""||sex==""||ea== 0||ey== ""||cls== ""||pwd== ""){
                QMessageBox::warning(this,"警告","请填写所有信息");
                Admin::clearSlot();
                return false;
            }
            else if(sex!="男"&&sex!="女"){
                 QMessageBox::warning(this,"警告","性别只能是(男或女)");
                 Admin::clearSlot();
                 return false;
            }
            else if(ea<10||ea>50)
                 QMessageBox::warning(this,"警告","入学年龄范围10—50");
            Admin::clearSlot();
            return false;
        }


    }
    else if(table=="Teacher"){
        QString id = idLineEdit->text();
        QString name = nameLineEdit->text();
        QString course1 = course1LineEdit->text();
        QString course2 = course2LineEdit->text();
        QString course3 = course3LineEdit->text();
        QString pwd = pwdLineEdit->text();
        bool success=false;
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);

        QString find = QString("select * from Teacher where id = '%1'").arg(id);
        query.exec(find);
        query.first();
        update = query.value(0).toString()==id;
        if(update){
            qDebug()<<"update";
            QString update=QString("update Teacher set Name='%1',Course1='%2',Course2='%3',Course3='%4', Password ='%5' where Id = '%6';"
                                ).arg(name).arg(course1).arg(course2).arg(course3).arg(pwd).arg(id);
            success = query.exec(update);
        }

        else {
            qDebug()<<"add";
            qDebug()<<"New teacher"<<id<<name<<course1<<course2<<course3<<pwd;
            QString add=QString("insert into Teacher values('%1','%2','%3','%4','%5','%6')"
                            ).arg(id).arg(name).arg(course1).arg(course2).arg(course3).arg(pwd);
         success = query.exec(add);
        }
        if(success)
        {
            if(update){
                qDebug() << QObject::tr("修改成功");
                Admin::on_pushButton_teacher_clicked();
                QMessageBox::information(this,"修改","信息修改成功");

            }
            if(!update){
                qDebug() << QObject::tr("添加成功");
                Admin::on_pushButton_teacher_clicked();
                QMessageBox::information(this,"添加","信息添加成功");

            }
            dialog->close();
            Admin::clearSlot();
            return true;
        }
        else
        {   
            if(!update)
                qDebug() << QObject::tr("添加失败");

            else if(update)
                qDebug() << QObject::tr("修改失败");

            if(id==""||name==""||pwd== ""){
                QMessageBox::warning(this,"警告","请填写教师号、姓名、密码");
                Admin::clearSlot();
                return false;
            }
        }
    }
    else if(table=="Course"){
        QString id = idLineEdit->text();
        QString name = nameLineEdit->text();
        QString courseTeacher = courseTeacherLineEdit->text();
        double courseCredit = courseCreditLineEdit->text().toDouble();
        QString courseGrade = courseGradeLineEdit->text();
        QString cancelYear = cancelYearLineEdit->text();
        bool success = false;
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QString find = QString("select * from Course where id = '%1'").arg(id);
        query.exec(find);
        query.first();
        update = query.value(0).toString()==id;
        if(update){
            qDebug()<<"update";
            QString update=QString("update Course set name='%1',CourseTeacherID='%2',CourseCredit= %3,CourseGrade='%4', CourseCanceledYear ='%5' where Id = '%6';"
                                ).arg(name).arg(courseTeacher).arg(courseCredit).arg(courseGrade).arg(cancelYear).arg(id);
            success = query.exec(update);
        }

        else{
            qDebug()<<"New course"<<id<<name<<courseTeacher<<courseCredit<<courseGrade<<cancelYear;

            QString add=QString("insert into Course values('%1','%2','%3',%4,'%5','%6')"
                                ).arg(id).arg(name).arg(courseTeacher).arg(courseCredit).arg(courseGrade).arg(cancelYear);
            success = query.exec(add);
        }
        if(success)
        {
            if(update){
                qDebug() << QObject::tr("修改成功");
                Admin::on_pushButton_course_clicked();
                QMessageBox::information(this,"修改","信息修改成功");

            }
            if(!update){
                qDebug() << QObject::tr("添加成功");
                Admin::on_pushButton_course_clicked();
                QMessageBox::information(this,"添加","信息添加成功");
            }
            Admin::clearSlot();
            return true;
        }
        else
        {
            qDebug() << QObject::tr("添加失败！");
            if(id==""||name==""||courseTeacher== ""||courseCredit== 0.0||courseGrade== ""){
                QMessageBox::warning(this,"警告","除取消年份外其余均需填写");
                Admin::clearSlot();
                return false;
            }
        }
    }

    else if(table=="CourseSelection"){
        QString studentId = studentIdLineEdit->text();
        QString courseId = courseIdLineEdit->text();
        QString teacherId = teacherIdLineEdit->text();
        QString selectionYear = selectionYearLineEdit->text();
        QString grade = gradeLineEdit->text();
        bool success=false;

        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);

        QString find = QString("select * from CourseSelection where TeacherId = '%1' and CourseId = '%2'").arg(teacherId).arg(courseId);
        query.exec(find);
        query.first();
        update = (query.value(2).toString()==teacherId)&&(query.value(1).toString()==courseId);
        if(update){
            qDebug()<<"update";
            QString update=QString("update CourseSelection set studentId='%1',selectionYear='%2',grade='%3' where TeacherId = '%4' and CourseId = '%5';"
                                ).arg(studentId).arg(selectionYear).arg(grade).arg(teacherId).arg(courseId);
            success = query.exec(update);
        }

        else {
            qDebug()<<"add";
            QString add=QString("insert into CourseSelection values('%1','%2','%3','%4',%5)"
                            ).arg(studentId).arg(courseId).arg(teacherId).arg(selectionYear).arg(grade);
         success = query.exec(add);
        }
        if(success)
        {
            if(update){
                qDebug() << QObject::tr("修改成功");
                Admin::on_pushButton_selection_clicked();
                QMessageBox::information(this,"修改","信息修改成功");
            }
            if(!update){
                qDebug() << QObject::tr("添加成功");
                Admin::on_pushButton_selection_clicked();
                QMessageBox::information(this,"添加","信息添加成功");
            }
            Admin::clearSlot();
            return true;
        }
        else
        {
            if(!update)
                qDebug() << QObject::tr("添加失败");

            else if(update)
                qDebug() << QObject::tr("修改失败");

            if(studentId==""||courseId==""||teacherId== ""){
                QMessageBox::warning(this,"警告","请填写教师号、姓名、密码");
                Admin::clearSlot();
                return false;
            }
        }
    }

    return false;
}

bool Admin::on_pushButton_delete_clicked()
{
    if(table==""){
        return false;
    }
    QModelIndexList select =ui->tableView->selectionModel()->selectedRows(0);
    if(!select.empty()){
        QModelIndex idIndex = select.at(0);
        QString Name =idIndex.sibling(idIndex.row(),1).data().toString();
        QString Id =idIndex.sibling(idIndex.row(),0).data().toString();
        QMessageBox::StandardButton button;
        if(table=="CourseSelection"){
            button=QMessageBox::question(this,tr("删除信息"),QString (tr("确定删除该条信息吗？")),QMessageBox::Yes|QMessageBox::No);

        }
        else
            button=QMessageBox::question(this,tr("删除信息"),QString (tr("确定从 %1列表 删除'%2'的用户信息吗？").arg(table).arg(Name)),QMessageBox::Yes|QMessageBox::No);
        if(button==QMessageBox::Yes){
            QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
            QSqlQuery query(db);
            QString del;
            if(table=="CourseSelection"){
                del=QString("delete from %1 where CourseId ='%2' and StudentId = '%3'").arg(table).arg(Name).arg(Id);

            }
            else
                del=QString("delete from %1 where Name ='%2' and Id = '%3'").arg(table).arg(Name).arg(Id);

            bool success = query.exec(del);
            if(success)
            {
                qDebug() << QObject::tr("删除成功");
                if(table=="Student"){
                    Admin::on_pushButton_student_clicked();
                }
                else if(table=="Teacher"){
                    Admin::on_pushButton_teacher_clicked();
                }
                else if(table == "Course" ){
                    Admin::on_pushButton_course_clicked();
                }
                else if(table == "CourseSelection" ){
                    Admin::on_pushButton_selection_clicked();
                }
                QMessageBox::information(this,"添加","信息删除成功");
                return true;
            }
            else
            {
                qDebug() << QObject::tr("删除失败！");
                return false;
            }
        }
        else{
            QMessageBox::information(this,tr("删除学生信息"),tr("请选择要删除的学生信息！"));
        }
    }
    else{
        QMessageBox::information(this,"警告","请选择条目");
    }
    return false;
}
void Admin::on_pushButton_modify_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    add = false;
    QModelIndexList select =ui->tableView->selectionModel()->selectedRows(0);
    if(!select.empty()){
        if(table=="Student"){

            QModelIndex idIndex = select.at(0);
            QString id1 =idIndex.sibling(idIndex.row(),0).data().toString();
            QString name1 =idIndex.sibling(idIndex.row(),1).data().toString();
            QString sex1 =idIndex.sibling(idIndex.row(),2).data().toString();
            QString ea1 =idIndex.sibling(idIndex.row(),3).data().toString();
            QString ey1 =idIndex.sibling(idIndex.row(),4).data().toString();
            QString cls1 =idIndex.sibling(idIndex.row(),5).data().toString();
            QString Strs=QString("select * from Student where Id = '%1';").arg(id1);
            query.exec(Strs);
            query.first();
            QString pwd1 = query.value(6).toString();
            Admin::on_pushButton_add_clicked();

            idLineEdit->setText(id1);
            idLineEdit->setEnabled(false);

            nameLineEdit->setText(name1);
            sexLineEdit->setText(sex1);
            eaLineEdit->setText(ea1);
            eyLineEdit->setText(ey1);
            classLineEdit->setText(cls1);
            pwdLineEdit->setEchoMode(QLineEdit::Password);
            pwdLineEdit->setText(pwd1);

        }
        if(table=="Teacher"){
            QModelIndex idIndex = select.at(0);
            QString id1 =idIndex.sibling(idIndex.row(),0).data().toString();
            QString name1 =idIndex.sibling(idIndex.row(),1).data().toString();
            QString course1 =idIndex.sibling(idIndex.row(),2).data().toString();
            QString course2 =idIndex.sibling(idIndex.row(),3).data().toString();
            QString course3 =idIndex.sibling(idIndex.row(),4).data().toString();
            QString pwd1 =idIndex.sibling(idIndex.row(),5).data().toString();
            Admin::on_pushButton_add_clicked();
            idLineEdit->setText(id1);
            idLineEdit->setEnabled(false);
            nameLineEdit->setText(name1);
            course1LineEdit->setText(course1);
            course2LineEdit->setText(course2);
            course3LineEdit->setText(course3);
            pwdLineEdit->setText(pwd1);
        }
        if(table=="Course"){
            QModelIndex idIndex = select.at(0);
            QString id1 =idIndex.sibling(idIndex.row(),0).data().toString();
            QString name1 =idIndex.sibling(idIndex.row(),1).data().toString();
            QString courseteacher1 =idIndex.sibling(idIndex.row(),2).data().toString();
            QString coursecredit2 =idIndex.sibling(idIndex.row(),3).data().toString();
            QString coursegrade3 =idIndex.sibling(idIndex.row(),4).data().toString();
            QString coursecancel =idIndex.sibling(idIndex.row(),5).data().toString();
            Admin::on_pushButton_add_clicked();
            idLineEdit->setText(id1);
            idLineEdit->setEnabled(false);

            nameLineEdit->setText(name1);
            courseTeacherLineEdit->setText(courseteacher1);
            courseCreditLineEdit->setText(coursecredit2);
            courseGradeLineEdit->setText(coursegrade3);
            cancelYearLineEdit->setText(coursecancel);
        }
        if(table=="CourseSelection"){
            QModelIndex idIndex = select.at(0);
            QString sid1 =idIndex.sibling(idIndex.row(),0).data().toString();
            QString cid1 =idIndex.sibling(idIndex.row(),1).data().toString();
            QString tid =idIndex.sibling(idIndex.row(),2).data().toString();
            QString year1 =idIndex.sibling(idIndex.row(),3).data().toString();
            QString grade1 =idIndex.sibling(idIndex.row(),4).data().toString();

            Admin::on_pushButton_add_clicked();
            courseIdLineEdit->setText(cid1);
            teacherIdLineEdit->setText(tid);
            teacherIdLineEdit->setEnabled(false);
            courseIdLineEdit->setEnabled(false);

            studentIdLineEdit->setText(sid1);
            gradeLineEdit->setText(grade1);
            selectionYearLineEdit->setText(year1);
        }
    }
}
//查询
void Admin::on_pushButton_search_clicked()
{
    QString name=  ui->name->text();
    QString id=  ui->id->text();
    QString Courseid=  ui->courseid->text();
    QString Coursename=  ui->coursename->text();
    if(table=="Student"){
         QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
         QSqlQueryModel* model = new QSqlQueryModel();
         if(!name.isEmpty())
            model->setQuery(tr("SELECT Id,Name,Sex,EntranceAge,EntranceYear,Class FROM Student where Name='%1'").arg(name),db);
         if(!id.isEmpty())
            model->setQuery(tr("SELECT Id,Name,Sex,EntranceAge,EntranceYear,Class FROM Student where Id='%1'").arg(id),db);
         model->setHeaderData(0, Qt::Horizontal, tr("学号"));
         model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
         model->setHeaderData(2, Qt::Horizontal, tr("性别"));
         model->setHeaderData(3, Qt::Horizontal, tr("入学年龄"));
         model->setHeaderData(4, Qt::Horizontal, tr("入学年份"));
         model->setHeaderData(5, Qt::Horizontal, tr("班级"));
         ui->tableView->setModel(model);
         ui->tableView->show();
    }
    if(table=="Teacher"){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQueryModel* model = new QSqlQueryModel();
        if(!name.isEmpty())
            model->setQuery(tr("SELECT Id,Name,Course1,Course2,Course3 FROM Teacher where Name ='%1'").arg(name),db);
        if(!id.isEmpty())
            model->setQuery(tr("SELECT Id,Name,Course1,Course2,Course3 FROM Teacher where Id='%1'").arg(id),db);
        model->setHeaderData(0, Qt::Horizontal, tr("教师号"));
        model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        model->setHeaderData(2, Qt::Horizontal, tr("课程1"));
        model->setHeaderData(3, Qt::Horizontal, tr("课程2"));
        model->setHeaderData(4, Qt::Horizontal, tr("课程3"));
        ui->tableView->setModel(model);
        ui->tableView->show();
    }
    if(table=="CourseSelection"){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQueryModel* model = new QSqlQueryModel();
        if(!name.isEmpty())
        {
            model->setQuery(tr("SELECT Student.Name, Student.Id, Course.Name, CourseSelection.Grade "
                               "From Student, Course, CourseSelection "
                               "Where Student.Id = CourseSelection.StudentId And Course.Id= CourseSelection.CourseId And Student.Name ='%1';"
                              ).arg(name),db);
        }
        if(!id.isEmpty())
        {
            model->setQuery(tr("SELECT Student.Name, Student.Id, Course.Name, CourseSelection.Grade "
                               "From Student, Course, CourseSelection "
                               "Where Student.Id = CourseSelection.StudentId And Course.Id= CourseSelection.CourseId And Student.Id ='%1';"
                              ).arg(id),db);
        }
        if(!Courseid.isEmpty())
        {
            model->setQuery(tr("SELECT Student.Name, Student.Id, Course.Name, CourseSelection.Grade "
                               "From Student, Course, CourseSelection "
                               "Where Student.Id = CourseSelection.StudentId And Course.Id= CourseSelection.CourseId And Course.Id ='%1';"
                              ).arg(Courseid),db);
        }
        if(!Coursename.isEmpty())
        {
            model->setQuery(tr("SELECT Student.Name, Student.Id, Course.Name, CourseSelection.Grade "
                               "From Student, Course, CourseSelection "
                               "Where Student.Id = CourseSelection.StudentId And Course.Id= CourseSelection.CourseId And Course.Name ='%1';"
                              ).arg(Coursename),db);
        }

        if(!name.isEmpty()&&!Coursename.isEmpty())
        {
            model->setQuery(tr("SELECT Student.Name, Student.Id, Course.Name, CourseSelection.Grade "
                               "From Student, Course, CourseSelection "
                               "Where Student.Id = CourseSelection.StudentId And Course.Id= CourseSelection.CourseId And Student.Name ='%1'And "
                               "Course.Name ='%2';"
                              ).arg(name).arg(Coursename),db);
        }
        if(!id.isEmpty()&&!Coursename.isEmpty())
        {
            model->setQuery(tr("SELECT Student.Name, Student.Id, Course.Name, CourseSelection.Grade "
                               "From Student, Course, CourseSelection "
                               "Where Student.Id = CourseSelection.StudentId And Course.Id= CourseSelection.CourseId "
                               "And Student.Id ='%1'And Course.Name='%2';"
                              ).arg(id).arg(Coursename),db);
        }
        if(!id.isEmpty()&&!Courseid.isEmpty())
        {
            model->setQuery(tr("SELECT Student.Name, Student.Id, Course.Name, CourseSelection.Grade "
                               "From Student, Course, CourseSelection "
                               "Where Student.Id = CourseSelection.StudentId And Course.Id= CourseSelection.CourseId "
                               "And Student.Id ='%1'And Course.Id='%2';"
                              ).arg(id).arg(Courseid),db);
        }
        if(!name.isEmpty()&&!Courseid.isEmpty())
        {
            model->setQuery(tr("SELECT Student.Name, Student.Id, Course.Name, CourseSelection.Grade "
                               "From Student, Course, CourseSelection "
                               "Where Student.Id = CourseSelection.StudentId And Course.Id= CourseSelection.CourseId "
                               "And Student.Name ='%1' And Course.Id='%2';"
                              ).arg(name).arg(Courseid),db);
        }
        //model->setQuery(tr("SELECT Id,Name,Course1,Course2,Course3 FROM Teacher where Id='%1'").arg(id),db);
        model->setHeaderData(0, Qt::Horizontal, tr("学生姓名"));
        model->setHeaderData(1, Qt::Horizontal, tr("学号"));
        model->setHeaderData(2, Qt::Horizontal, tr("课程名称"));
        model->setHeaderData(3, Qt::Horizontal, tr("课程成绩"));
        ui->tableView->setModel(model);
        ui->tableView->show();
    }
    if(table=="Course"){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQueryModel* model = new QSqlQueryModel();
        if(!Coursename.isEmpty())
            model->setQuery(tr("SELECT * FROM Course where Name ='%1'").arg(Coursename),db);
        if(!Courseid.isEmpty())
            model->setQuery(tr("SELECT * FROM Course where Id ='%1'").arg(Courseid),db);
        if(!Coursename.isEmpty()&&!Courseid.isEmpty())
            model->setQuery(tr("SELECT * FROM Course where Id ='%1' And Name ='%2'").arg(Courseid).arg(Coursename),db);
        model->setHeaderData(0, Qt::Horizontal, tr("课程编号"));
        model->setHeaderData(1, Qt::Horizontal, tr("课程"));
        model->setHeaderData(2, Qt::Horizontal, tr("教师号"));
        model->setHeaderData(3, Qt::Horizontal, tr("学分"));
        model->setHeaderData(4, Qt::Horizontal, tr("适合年级"));
        model->setHeaderData(5, Qt::Horizontal, tr("结课年份"));
        ui->tableView->setModel(model);
        ui->tableView->show();
    }
}
void Admin::on_pushButton_back_clicked()
{
    ui->name->clear();
    ui->id->clear();
    ui->courseid->clear();
    ui->coursename->clear();

    if(table=="Student")
        Admin::on_pushButton_student_clicked();
    if(table=="Teacher")
        Admin::on_pushButton_teacher_clicked();
    if(table=="Course")
        Admin::on_pushButton_course_clicked();
    if(table=="CourseSelection")
        Admin::on_pushButton_selection_clicked();
}



void Admin::cancelBtnSlot()
{
    clearSlot();
}
void Admin::clearSlot()
{
    if(table == "CourseSelection"){
        courseIdLineEdit->clear();
        teacherIdLineEdit->clear();
        studentIdLineEdit->clear();
        gradeLineEdit->clear();
        selectionYearLineEdit->clear();
    }
    else {
        idLineEdit->clear();
        nameLineEdit->clear();
        if(table == "Student"){
            pwdLineEdit->clear();
            sexLineEdit->clear();
            eaLineEdit->clear();
            eyLineEdit->clear();
            classLineEdit->clear();
        }
        else if(table == "Teacher"){
            pwdLineEdit->clear();
            course1LineEdit->clear();
            course2LineEdit->clear();
            course3LineEdit->clear();
        }
        else if(table == "Course"){
            courseTeacherLineEdit->clear();
            courseCreditLineEdit->clear();
            courseGradeLineEdit->clear();
            cancelYearLineEdit->clear();
        }
    }

}







