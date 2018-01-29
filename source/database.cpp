#include "database.h"

//建立一个数据库连接
bool DataBase::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName(".//qtDb.db");
    if( !db.open())
    {
        qDebug() << "Failed to opne database";
        return false;
    }
    else
    {
        qDebug() << "Connect database";
    }
    return true;
}

//创建数据库表
bool DataBase::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);

    query.exec("drop table Student");
    query.exec("drop table Teacher");
    query.exec("drop table Course");
    query.exec("drop table CourseSelection");
    bool student = query.exec("create table Student("
                              "Id varchar(10) primary key not null,"
                              "Name varchar(10),"
                              "Sex varchar(3) not null,"
                              "EntranceAge int,"
                              "EntranceYear varchar(5),"
                              "Class varchar(20),"
                              "Password varchar(10),"
                              "check(sex in ('男','女')),"
                              "check(EntranceAge>10 and EntranceAge<50))");

    bool teacher = query.exec("create table Teacher("
                              "Id varchar(5) primary key not null,"
                              "Name varchar(10),"
                              "Course1 varchar(20),"
                              "Course2 varchar(20),"
                              "Course3 varchar(20),"
                              "Password varchar(10))");

    bool course = query.exec("create table  Course("
                             "Id varchar(7) primary key not null,"
                             "Name varchar(30),"
                             "CourseTeacherID varchar(5),"
                             "CourseCredit double,"
                             "CourseGrade varchar(5),"
                             "CourseCanceledYear varchar(10));");
    bool courseSelection = query.exec("create table CourseSelection("
                                      "StudentId varchar(10),"
                                      "CourseId varchar(7),"
                                      "TeacherId varchar(10),"
                                      "SelectionYear varchar(5),"
                                      "Grade double,"
                                      "Foreign key (StudentId) references Student(Id),"
                                      "Foreign key (TeacherId) references Teacher(Id),"
                                      "Foreign key (CourseId) references Course(Id));");

    if(!student||!course||!teacher||!courseSelection)
        {
            qDebug("table is error");
            return  false;
        }
    else
    {
        qDebug("table is sucess");
        return  true;
    }
}

//向数据库中插入记录
bool DataBase::insert()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("insert into Student values('0000000001','学生1','男',19,'2015','计算机科学与技术','student1')");
    query.exec("insert into Student values('0000000002','学生2','女',17,'2016','计算机联合班','student2')");
    query.exec("insert into Student values('0000000003','学生3','男',19,'2015','网络工程','student3')");
    query.exec("insert into Student values('0000000004','学生4','女',20,'2014','信息安全','student4')");
    query.exec("insert into Student values('0000000005','学生5','男',18,'2015','计算机科学与技术','student5')");
    query.exec("insert into Student values('0000000006','学生6','女',16,'2016','计算机联合班','student6')");
    query.exec("insert into Student values('0000000007','学生7','男',19,'2015','网络工程','student7')");
    query.exec("insert into Student values('0000000008','同名','女',20,'2014','信息安全','student8')");
    query.exec("insert into Student values('0000000009','同名','男',19,'2015','计算机创新班','student9')");
    query.exec("insert into Student values('0000000010','学生8','男',19,'2015','计算机科学与技术','student10')");
    query.exec("insert into Student values('0000000011','学生9','女',17,'2015','计算机联合班','student11')");
    query.exec("insert into Student values('0000000012','学生10','男',19,'2015','计算机联合班','student12')");
    query.exec("insert into Student values('0000000013','学生11','女',20,'2015','计算机联合班','student13')");
    query.exec("insert into Student values('0000000014','学生12','男',18,'2015','计算机联合班','student14')");
    query.exec("insert into Student values('0000000015','学生13','女',16,'2015','计算机联合班','student15')");
    query.exec("insert into Student values('0000000016','学生14','男',19,'2015','网络工程','student16')");
    query.exec("insert into Student values('0000000017','学生15','女',20,'2015','信息安全','student17')");
    query.exec("insert into Student values('0000000018','学生16','男',19,'2015','计算机创新班','student18')");

    query.exec("insert into Course  values('0145101','数据库','10001','3.5','2015','')");
    query.exec("insert into Course  values('0145102','人工智能','10002','2.5','2015','')");
    query.exec("insert into Course  values('0145103','机器学习','10002','1.0','2016','')");
    query.exec("insert into Course  values('0145104','数学分析','10004','3.5','2016','')");
    query.exec("insert into Course  values('0145105','离散数学','10003','2.5','2016','')");
    query.exec("insert into Course  values('0145106','c++程序设计','10002','3.0','2016','')");
    query.exec("insert into Course  values('0145107','数据结构','10003','4.0','2016','')");
    query.exec("insert into Course  values('0145108','计算机组织与结构','10005','3.5','2015','')");
    query.exec("insert into Course  values('0145109','编译原理','10006','2.5','2015','')");
    query.exec("insert into Course  values('0145110','算法设计与分析','10007','1.0','2015','')");
    query.exec("insert into Course  values('0145111','网球','10004','3.5','2015','')");

    query.exec("insert into Teacher values('10001','余志文','数据库','','','teacher1')");
    query.exec("insert into Teacher values('10002','吴永贤','人工智能','机器学习','','teacher2')");
    query.exec("insert into Teacher values('10003','陈百基','离散数学','数据结构','','teacher3')");
    query.exec("insert into Teacher values('10004','胡甦','数学分析','','','teacher4')");
    query.exec("insert into Teacher values('10005','毛爱华','计算机组织与结构','','','teacher5')");
    query.exec("insert into Teacher values('10006','刘欣欣','编译原理','','','teacher6')");
    query.exec("insert into Teacher values('10007','颜小洋','算法设计与分析','','','teacher7')");
    query.exec("insert into Teacher values('10008','李卫国','网球','','','teacher8')");

    query.exec("insert into courseSelection values('0000000001','0145101','10001','2015',99)");
    query.exec("insert into courseSelection values('0000000001','0145102','10002','2015',96)");
    query.exec("insert into courseSelection values('0000000002','0145101','10001','2015',89)");




    return  true;
}

//排序
bool DataBase::sortById()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    bool success=query.exec("select * from Student order by id desc");
    if(success)
    {
        qDebug() << QObject::tr("排序成功");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("排序失败！");
        return false;
    }
}
bool DataBase::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from Student");
    QSqlRecord recs = query.record();
    qDebug() << QObject::tr("Student 表字段数：" ) << recs.count();
    while(query.next())
    {
        qDebug() << query.value(0).toString() << " "
                 << query.value(1).toString() << " "
                 << query.value(2).toString() << " "
                 << query.value(3).toInt() << " "
                 << query.value(4).toString() << " "
                 << query.value(5).toString() << " "
                 << query.value(6).toString() << " ";
    }
    query.exec("select * from Teacher");
    QSqlRecord rect = query.record();
    qDebug() << QObject::tr("Teacher 表字段数：" ) << rect.count();
    while(query.next())
    {
        qDebug() << query.value(0).toString() << " "
                 << query.value(1).toString() << " "
                 << query.value(2).toString() << " "
                 << query.value(3).toString() << " "
                 << query.value(4).toString() << " "
                 << query.value(5).toString() << " ";
    }

    query.exec("select * from Course");
    QSqlRecord recc = query.record();
    qDebug() << QObject::tr("Course 表字段数：" ) << recc.count();
    while(query.next())
    {
        qDebug() << query.value(0).toString() << " "
                 << query.value(1).toString() << " "
                 << query.value(2).toString() << " "
                 << query.value(3).toString() << " "
                 << query.value(4).toString() << " "
                 << query.value(5).toString() << " ";
    }
    return true;
}
