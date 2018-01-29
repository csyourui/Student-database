#ifndef LOGINDIG_H
#define LOGINDIG_H

#include <QMainWindow>
#include <QDebug>
#include <QDialog>
#include <QPalette>
#include <QButtonGroup>
#include <QMessageBox>


namespace Ui {
class LoginDig;
}

class LoginDig : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginDig(QWidget *parent = 0);
    ~LoginDig();
    void clearAll();
    bool judgeEmpty();
private slots:


    void on_loginbtn_clicked();

    void loginbtnSetSlot(QString);
    void on_refreshbtn_clicked();

private:
    Ui::LoginDig *ui;
    QButtonGroup *radiogroup;

signals:
    void toStudentManage(QString,QString);
    void toTeacherManage(QString,QString);

};

#endif // LOGINDIG_H
