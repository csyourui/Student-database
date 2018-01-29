#include "student.h"
#include "ui_student.h"
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
#include <QSqlField>

double Aver_Grade;
extern QString userID;
extern QString userName;
QString currentView;
Student::Student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    //LOGO
    QPixmap schoollogo;
    schoollogo.load(":/logo_school.png");
    ui->label_logo->setPixmap(schoollogo);
    ui->label_name->setText(userName);
    //设置为不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(true);
    //设置按行选择，单行选择
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    Student::on_pushButton_finish_clicked();

    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();

     model->setQuery(tr("SELECT CourseId, TeacherId, SelectionYear,Grade FROM CourseSelection where StudentId='%1'").arg(userID),db);
     Student::on_pushButton_finish_clicked();
     //background
       QPixmap background;
       background.load(":/backg.jpg");
       QPalette palette = this->palette();
       palette.setBrush(backgroundRole(), QBrush(background));
       setPalette(palette);

     Student::computeAver();
     QString AverT = QString::number(Aver_Grade);
     ui->label_grade->setText(AverT );
}

Student::~Student()
{
    delete ui;
}
void Student::computeAver()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    Aver_Grade=0;
    QString find = QString("SELECT Grade FROM CourseSelection where StudentId = '%1'").arg(userID);
    query.exec(find);
    int i = 0;
    while (query.next())
    {
        Aver_Grade += query.value(0).toDouble();
        i++;
    }
   if(i)
        Aver_Grade=  Aver_Grade/i;
}


void Student::on_pushButton_exit_clicked()
{
    this->close();
}

void Student::on_pushButton_finish_clicked()
{
    currentView = "已选课程";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT CourseId, TeacherId, SelectionYear,Grade FROM CourseSelection where StudentId='%1'").arg(userID),db);

    model->setHeaderData(0, Qt::Horizontal, tr("课程编号"));
    model->setHeaderData(1, Qt::Horizontal, tr("教师编号"));
    model->setHeaderData(2, Qt::Horizontal, tr("选课年份"));
    model->setHeaderData(3, Qt::Horizontal, tr("成绩"));
    ui->tableView->setModel(model);
    ui->tableView->show();
}

void Student::on_pushButton_other_clicked()
{
    currentView = "所有课程";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT * FROM Course"),db);

    model->setHeaderData(0, Qt::Horizontal, tr("课程编号"));
    model->setHeaderData(1, Qt::Horizontal, tr("课程名字"));
    model->setHeaderData(2, Qt::Horizontal, tr("老师编号"));
    model->setHeaderData(3, Qt::Horizontal, tr("课程学分"));
    model->setHeaderData(4, Qt::Horizontal, tr("选课年级"));
    model->setHeaderData(5, Qt::Horizontal, tr("取消年限"));
    ui->tableView->setModel(model);
    ui->tableView->show();
}

void Student::on_chooseCourse_clicked()
{
    if (currentView == "所有课程"){
        QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        QSqlQuery query2(db);
        QString find = QString("SELECT * FROM Student where Id='%1'").arg(userID);
        query.exec(find);
        query.next();
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString sex = query.value(2).toString();
        int ea = query.value(3).toInt();
        int grade = query.value(4).toInt();
        QString cls = query.value(5).toString();
        QString pwd = query.value(6).toString();


        QModelIndexList select =ui->tableView->selectionModel()->selectedRows(0);
        if(!select.empty()){
            QModelIndex idIndex = select.at(0);
            QString csId =idIndex.sibling(idIndex.row(),0).data().toString();
            QString teaId =idIndex.sibling(idIndex.row(),2).data().toString();
            QString gra =idIndex.sibling(idIndex.row(),4).data().toString();
            int grade2 = gra.toInt();

            if (grade > grade2){
                QMessageBox::information(this,"提示", "用户年级低于选课规定年级");
            }
            else {
                bool hasChoosedCourse = false;
                QString sel = QString("SELECT CourseId FROM CourseSelection where StudentId='%1'").arg(userID);
                query2.exec(sel);
                while(query2.next()){
                    QString tempCourseId = query2.value(0).toString();
                    if (tempCourseId == csId){
                        hasChoosedCourse = true;
                    }
                }
                if (hasChoosedCourse == false){
                    QString add=QString("insert into CourseSelection values('%1','%2','%3',%4,'%5')"
                                    ).arg(userID).arg(csId).arg(teaId).arg(gra).arg("");
                     bool success = query.exec(add);
                     if (success){
                         QMessageBox::information(this,"提示","选课成功");
                     }
                }
                else {
                    QMessageBox::information(this,"提示","该门课已选过");
                }

            }
        }
    }
    else{
        QMessageBox::information(this,"提示","请到选课界面选课");
    }
}
