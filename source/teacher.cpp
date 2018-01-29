#include "teacher.h"
#include "ui_teacher.h"
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

double Aver_CourseGrade;
double Aver_ClassGrade;
extern QString userID;
extern QString userName;
QString table_teacher;
QString Course1,Course2,Course3;
QString CourseId1,CourseId2,CourseId3;

bool add_teacher=true;

Teacher::Teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teacher)
{


    ui->setupUi(this);
    //LOGO
    QPixmap schoollogo;
    schoollogo.load(":/logo_school.png");
    ui->label_logo->setPixmap(schoollogo);
    ui->label_name->setText(userName);

    ui->label_name->setText(userName);
    //设置为不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->setSortingEnabled(true);
    //设置按行选择，单行选择
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    Teacher::on_pushButton_course1_clicked();
    //修改按钮上的信息
//    table_teacher = "Teacher";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(tr("SELECT Course1,Course2,Course3 FROM Teacher where ID='%1'").arg(userID),db);
    Course1 = model->data(model->index(0, 0)).toString();
    Course2 = model->data(model->index(0, 1)).toString();
    Course3 = model->data(model->index(0, 2)).toString();
    ui->pushButton_course1->setText(Course1);
    ui->pushButton_course2->setText(Course2);
    ui->pushButton_course3->setText(Course3);
    //找到课程Id
//    table_teacher = "Course";
//    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
//    QSqlQueryModel* model = new QSqlQueryModel();
    model->clear();
    model->setQuery(tr("SELECT Id FROM Course where Name='%1'").arg(Course1),db);
    CourseId1 = model->data(model->index(0, 0)).toString();
    model->setQuery(tr("SELECT Id FROM Course where Name='%1'").arg(Course2),db);
    CourseId2 = model->data(model->index(0, 0)).toString();
    model->setQuery(tr("SELECT Id FROM Course where Name='%1'").arg(Course3),db);
    CourseId3 = model->data(model->index(0, 0)).toString();
    setID(CourseId1,CourseId2, CourseId3);
//    Course2 = model->data(model->index(0, 1)).toString();
//    Course3 = model->data(model->index(0, 2)).toString();
//    ui->pushButton_course1->setText(CourseId1);//成功得到
//    ui->pushButton_course2->setText(Course2);
//    ui->pushButton_course3->setText(Course3);
    Teacher::on_pushButton_course1_clicked();
    //background
      QPixmap background;
      background.load(":/backg.jpg");
      QPalette palette = this->palette();
      palette.setBrush(backgroundRole(), QBrush(background));
      setPalette(palette);
}

Teacher::~Teacher()
{
    delete ui;
}

void Teacher::setID(QString CID1, QString CID2,QString CID3)
{
    ID1= CID1;
    ID2= CID2;
    ID3= CID3;
}

QString Teacher::getID(int i )
{
    if (i = 1) return ID1;
    if (i = 2) return ID2;
    if (i = 3) return ID3;
}
void Teacher::computeCourseAver(QString ID)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    Aver_CourseGrade=0;
    QString find = QString("SELECT Grade FROM CourseSelection where CourseId = '%1'").arg(ID);
    query.exec(find);
    int i = 0;
    while (query.next())
    {
        Aver_CourseGrade += query.value(0).toDouble();
        i++;
    }
   if(i)
        Aver_CourseGrade=  Aver_CourseGrade/i;
   QString AverT = QString::number(Aver_CourseGrade);
   ui->Aver_Course->setText(AverT );
}



void Teacher::on_pushButton_course1_clicked()
{
    table_teacher = "CourseSelection1";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT * FROM CourseSelection where CourseId='%1'").arg(CourseId1),db);

    model->setHeaderData(0, Qt::Horizontal, tr("学生学号"));
    model->setHeaderData(1, Qt::Horizontal, tr("课程编号"));
    model->setHeaderData(2, Qt::Horizontal, tr("教师编号"));
    model->setHeaderData(3, Qt::Horizontal, tr("选课年份"));
    model->setHeaderData(4, Qt::Horizontal, tr("成绩"));

    ui->tableView->setModel(model);
    ui->tableView->show();

   computeCourseAver(getID(1));
}

void Teacher::on_pushButton_course2_clicked()
{
    table_teacher = "CourseSelection2";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT * FROM CourseSelection where CourseId='%1'").arg(CourseId2),db);

    model->setHeaderData(0, Qt::Horizontal, tr("学生学号"));
    model->setHeaderData(1, Qt::Horizontal, tr("课程编号"));
    model->setHeaderData(2, Qt::Horizontal, tr("教师编号"));
    model->setHeaderData(3, Qt::Horizontal, tr("选课年份"));
    model->setHeaderData(4, Qt::Horizontal, tr("成绩"));

    ui->tableView->setModel(model);
    ui->tableView->show();
    computeCourseAver(getID(2));
}

void Teacher::on_pushButton_course3_clicked()
{
    table_teacher = "CourseSelection3";
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(tr("SELECT * FROM CourseSelection where CourseId='%1'").arg(CourseId3),db);

    model->setHeaderData(0, Qt::Horizontal, tr("学生学号"));
    model->setHeaderData(1, Qt::Horizontal, tr("课程编号"));
    model->setHeaderData(2, Qt::Horizontal, tr("教师编号"));
    model->setHeaderData(3, Qt::Horizontal, tr("选课年份"));
    model->setHeaderData(4, Qt::Horizontal, tr("成绩"));

    ui->tableView->setModel(model);
    ui->tableView->show();
    computeCourseAver(getID(3));
}

void Teacher::on_pushButton_change_clicked()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowTitle(tr("修改 %1 信息").arg(table_teacher));

    QGroupBox *box  = new QGroupBox(this);
    QPushButton *submitBtn = new QPushButton(tr("确认"));
    QPushButton *cancelBtn = new QPushButton(tr("取消"));
    connect(submitBtn,SIGNAL(clicked(bool)),this,SLOT(addNewToTable()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(cancelBtnSlot()));

    QModelIndexList select =ui->tableView->selectionModel()->selectedRows(0);
    if(!select.empty()){
        QModelIndex idIndex = select.at(0);
        QString sid1 =idIndex.sibling(idIndex.row(),0).data().toString();
        QString cid1 =idIndex.sibling(idIndex.row(),1).data().toString();
        QString tid =idIndex.sibling(idIndex.row(),2).data().toString();
        QString year1 =idIndex.sibling(idIndex.row(),3).data().toString();
        QString grade1 =idIndex.sibling(idIndex.row(),4).data().toString();
    //copy change
    //    Admin::on_pushButton_add_clicked();

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

        studentIdLineEdit->setEnabled(false);
        courseIdLineEdit->setEnabled(false);
        teacherIdLineEdit->setEnabled(false);
        selectionYearLineEdit->setEnabled(false);

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

        courseIdLineEdit->setText(cid1);
        teacherIdLineEdit->setText(tid);
        studentIdLineEdit->setText(sid1);
        gradeLineEdit->setText(grade1);
        selectionYearLineEdit->setText(year1);
    }
}

bool Teacher::addNewToTable(){
    bool update = false;
    QString studentId = studentIdLineEdit->text();
    QString courseId = courseIdLineEdit->text();
    QString teacherId = teacherIdLineEdit->text();
    QString selectionYear = selectionYearLineEdit->text();
    QString grade = gradeLineEdit->text();
    bool success=false;

    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);

    QString find = QString("select * from CourseSelection where StudentId = '%1' and CourseId = '%2'").arg(studentId).arg(courseId);
    query.exec(find);
    query.first();
    update = (query.value(0).toString()==studentId)&&(query.value(1).toString()==courseId);
    if(update){
        qDebug()<<"update";
        QString update=QString("update CourseSelection set teacherId='%1',selectionYear='%2',grade='%3' where studentId = '%4' and courseId = '%5';"
                            ).arg(teacherId).arg(selectionYear).arg(grade).arg(studentId).arg(courseId);
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
//            Teacher::on_pushButton_selection_clicked();
            if(table_teacher=="CourseSelection1"){
                Teacher::on_pushButton_course1_clicked();
            }else if(table_teacher=="CourseSelection2"){
                Teacher::on_pushButton_course2_clicked();
            }else if(table_teacher=="CourseSelection3"){
                Teacher::on_pushButton_course3_clicked();
            }else{Teacher::on_pushButton_course3_clicked();
            };
            QMessageBox::information(this,"修改","信息修改成功");
        }
        if(!update){
            qDebug() << QObject::tr("添加成功");
            if(table_teacher=="CourseSelection1"){
                Teacher::on_pushButton_course1_clicked();
            }else if(table_teacher=="CourseSelection2"){
                Teacher::on_pushButton_course2_clicked();
            }else if(table_teacher=="CourseSelection3"){
                Teacher::on_pushButton_course3_clicked();
            }else{Teacher::on_pushButton_course3_clicked();
            };
//            Teacher::on_pushButton_selection_clicked();
            QMessageBox::information(this,"添加","信息添加成功");
        }
        Teacher::clearSlot();
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
            Teacher::clearSlot();
            return false;
        }
    }
}


void Teacher::cancelBtnSlot()
{
    clearSlot();
}
void Teacher::clearSlot()
{
    courseIdLineEdit->clear();
    teacherIdLineEdit->clear();
    studentIdLineEdit->clear();
    gradeLineEdit->clear();
    selectionYearLineEdit->clear();
}
