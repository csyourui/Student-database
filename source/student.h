#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>

namespace Ui {
class Student;
}

class Student : public QWidget
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = 0);
    ~Student();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_finish_clicked();

    void on_pushButton_other_clicked();

    void on_chooseCourse_clicked();

    void computeAver();
private:
    Ui::Student *ui;
};

#endif // STUDENT_H
