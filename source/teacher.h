#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QSqlTableModel>
#include <QLineEdit>
namespace Ui {
class Teacher;
}

class Teacher : public QWidget
{
    Q_OBJECT

public:
    explicit Teacher(QWidget *parent = 0);
    ~Teacher();


private slots:
    void on_pushButton_course1_clicked();

    void on_pushButton_course2_clicked();

    void on_pushButton_course3_clicked();

    void on_pushButton_change_clicked();

    bool addNewToTable();

    void cancelBtnSlot();

    void clearSlot();

    void setID(QString,QString, QString);
    QString getID(int);


    void computeCourseAver(QString);

   // void computeClassAver(int);
private:
    Ui::Teacher *ui;
    QSqlTableModel *model;
    //注册用户名、Id、密码
    QString ID1, ID2,ID3;
    //添加选课信息
    QLineEdit *courseIdLineEdit;
    QLineEdit *teacherIdLineEdit;
    QLineEdit *studentIdLineEdit;
    QLineEdit *gradeLineEdit;
    QLineEdit *selectionYearLineEdit;
};

#endif // TEACHER_H
