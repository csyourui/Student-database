#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QSqlTableModel>
#include <QLineEdit>
namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();

private slots:
    void on_pushButton_exit_clicked();


    void compute_all();
    void avg (QString);

    void on_pushButton_student_clicked();

    void on_pushButton_teacher_clicked();

    void on_pushButton_course_clicked();

    void on_pushButton_add_clicked();

    bool addNewToTable();

    void cancelBtnSlot();

    void clearSlot();

    void onChanged(int index);

    bool on_pushButton_delete_clicked();

    void on_pushButton_modify_clicked();

    void on_pushButton_selection_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_grade_clicked();
private:
    Ui::Admin *ui;
    QDialog *dialog;

    QSqlTableModel *model;
    //注册用户名、Id、密码
    QLineEdit *idLineEdit;
    QLineEdit *nameLineEdit;
    QLineEdit *pwdLineEdit;
    //注册学生其它信息
    QLineEdit *sexLineEdit;
    QLineEdit *eaLineEdit;
    QLineEdit *eyLineEdit;
    QLineEdit *classLineEdit;
    //注册教师其它信息
    QLineEdit *course1LineEdit;
    QLineEdit *course2LineEdit;
    QLineEdit *course3LineEdit;
    //注册课程其它信息
    QLineEdit *courseTeacherLineEdit;
    QLineEdit *courseCreditLineEdit;
    QLineEdit *courseGradeLineEdit;
    QLineEdit *cancelYearLineEdit;
    //添加选课信息
    QLineEdit *courseIdLineEdit;
    QLineEdit *teacherIdLineEdit;
    QLineEdit *studentIdLineEdit;
    QLineEdit *gradeLineEdit;
    QLineEdit *selectionYearLineEdit;

};

#endif // ADMIN_H
