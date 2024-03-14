#include "fenliang3.h"
#include "ui_fenliang3.h"

fenliang3::fenliang3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fenliang3)
{
    ui->setupUi(this);
    ui->widget_1->setStyleSheet("QWidget { border: 1px solid #add8e6; border-radius: 1px; }"
                                "QLineEdit, QLabel { border: none; }");
    // 设置 widget_2 的边框颜色和内部部件边框颜色
    ui->widget_2->setStyleSheet("QWidget { border: 1px solid #add8e6; border-radius: 1px; }"
                                "QLineEdit, QLabel { border: none; }");

    // 设置 widget_3 的边框颜色和内部部件边框颜色
    ui->widget_3->setStyleSheet("QWidget { border: 1px solid #add8e6; border-radius: 1px; }"
                                "QLineEdit, QLabel { border: none; }");

    // 设置 widget_4 的边框颜色和内部部件边框颜色
    ui->widget_4->setStyleSheet("QWidget { border: 1px solid #add8e6; border-radius: 1px; }"
                                "QLineEdit, QLabel { border: none; }");

    // 设置 widget_5 的边框颜色和内部部件边框颜色
    ui->widget_5->setStyleSheet("QWidget { border: 1px solid #add8e6; border-radius: 1px; }"
                                "QLineEdit, QLabel { border: none; }");
}

fenliang3::~fenliang3()
{
    delete ui;
}

void fenliang3::refresh3(QWidget* w, int s, int a, int b, int c) {
    // 有效值

    QString x = QString("widget_%1").arg(s);
    QWidget* xw = ui->widget->findChild<QWidget*>(x);

    if (xw) {
        if (xw->isVisible()) {
            xw->hide();
        } else {
            xw->show();
        }
    }

    a++;b++;c++;
    if(a){
        QString vdata1 = QString("lineEdit_%1_1").arg(a);
        QString vdata2 = QString("lineEdit_%1_1").arg(b);
        QString vdata3 = QString("lineEdit_%1_1").arg(c);

        QLineEdit* currentLineEdit1 = w->findChild<QLineEdit*>(vdata1);
        QLineEdit* currentLineEdit2 = w->findChild<QLineEdit*>(vdata2);
        QLineEdit* currentLineEdit3 = w->findChild<QLineEdit*>(vdata3);

        QString vvdata1 = currentLineEdit1->text();
        QString vvdata2 = currentLineEdit2->text();
        QString vvdata3 = currentLineEdit3->text();
        double  vvvdata1 = vvdata1.toDouble();
        double  vvvdata2 = vvdata2.toDouble();
        double  vvvdata3 = vvdata3.toDouble();

        // 相位
        QString pdata1 = QString("lineEdit_%1_2").arg(a);
        QString pdata2 = QString("lineEdit_%1_2").arg(b);
        QString pdata3 = QString("lineEdit_%1_2").arg(c);

        QLineEdit* currentLineEdit4 = w->findChild<QLineEdit*>(pdata1);
        QLineEdit* currentLineEdit5 = w->findChild<QLineEdit*>(pdata2);
        QLineEdit* currentLineEdit6 = w->findChild<QLineEdit*>(pdata3);

        QString ppdata1 = currentLineEdit4->text();
        QString ppdata2 = currentLineEdit5->text();
        QString ppdata3 = currentLineEdit6->text();
        double  pppdata1 = ppdata1.toDouble();
        double  pppdata2 = ppdata2.toDouble();
        double  pppdata3 = ppdata3.toDouble();

        Vector2D v1{vvvdata1,pppdata1};
        Vector2D v2{vvvdata2,pppdata2};
        Vector2D v3{vvvdata3,pppdata3};
        Vector2D v4{vvvdata2,pppdata2};
        Vector2D v5{vvvdata3,pppdata3};




        Vector2D zeroSequence = (v1 + v2 + v3) ;
        Vector2D positiveSequence = (v1 + v2.rotate(120) + v3.rotate(-120)) / 3.0;
        Vector2D negativeSequence = (v1 + v4.rotate(-120) + v5.rotate(120)) / 3.0;

        for (int k = 1; k <= 3; k++) {

            QString load = QString("lineEdit_%1").arg(k + (s-1)*6);
            QLineEdit* currentLineEdit = ui->widget->findChild<QLineEdit*>(load);
            QString load1 = QString("lineEdit_%1").arg(k + 3+(s-1) *6);
            QLineEdit* currentLineEdit1 = ui->widget->findChild<QLineEdit*>(load1);
//            QMessageBox::warning(nullptr, "load", "YES!: "+load);
//            QMessageBox::warning(nullptr, "load1", "YES!: "+load1);
            switch (k) {
            case 1:
                currentLineEdit->setText(QString::number(  positiveSequence.x));
                currentLineEdit1->setText(QString::number( positiveSequence.y));
                break;
            case 2:
                currentLineEdit->setText(QString::number( negativeSequence.x));
                currentLineEdit1->setText(QString::number( negativeSequence.y));
                break;
            case 3:
                currentLineEdit->setText(QString::number( zeroSequence.x));
                currentLineEdit1->setText(QString::number( zeroSequence.y));
                break;
                // 其他 case ...
            }
        }
    }else {
        QMessageBox::warning(nullptr, "警告", "But No!");





        }


}
