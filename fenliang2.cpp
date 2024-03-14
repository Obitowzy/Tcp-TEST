#include "fenliang2.h"
#include "ui_fenliang2.h"

fenliang2::fenliang2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fenliang2)
{
    ui->setupUi(this);
}

fenliang2::~fenliang2()
{
    delete ui;
}
Vector2D fenliang2::calculateVectorSum(const Vector2D& v1, const Vector2D& v2) {

    return v1 - v2;
}
void fenliang2::refresh2(QWidget* w, int s, int a, int b, int c) {
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

        struct Vector2D v1{vvvdata1,pppdata1};
        struct Vector2D v2{vvvdata2,pppdata2};
        struct Vector2D v3{vvvdata3,pppdata3};
        struct Vector2D result1{0,0} ;
        struct Vector2D result2{0,0} ;
        struct Vector2D result3{0,0} ;

        if(s==1||s==2){
            result1 = v1-v2;
            result2 = v2-v3;
            result3 = v3-v1;
        }else {
            result1 = v1+v2;
            result2 = v2+v3;
            result3 = v3+v1;
        }




        if (result1.y < 0) {
                result1.y += 360.0;
            }
            if (result2.y < 0) {
                result2.y += 360.0;
            }
            if (result3.y < 0) {
                result3.y += 360.0;
            }

        for (int k = 1; k <= 3; k++) {

            QString load = QString("lineEdit_%1").arg(k + (s-1)*6);
            QLineEdit* currentLineEdit = ui->widget->findChild<QLineEdit*>(load);
            QString load1 = QString("lineEdit_%1").arg(k + 3+(s-1) *6);
            QLineEdit* currentLineEdit1 = ui->widget->findChild<QLineEdit*>(load1);
            //            QMessageBox::warning(nullptr, "load", "YES!: "+load);
            //            QMessageBox::warning(nullptr, "load1", "YES!: "+load1);
            switch (k) {
            case 1:
                currentLineEdit->setText(QString::number( result1.x));
                currentLineEdit1->setText(QString::number( result1.y));
                break;
            case 2:
                currentLineEdit->setText(QString::number( result2.x));
                currentLineEdit1->setText(QString::number( result2.y));
                break;
            case 3:
                currentLineEdit->setText(QString::number( result3.x));
                currentLineEdit1->setText(QString::number( result3.y));
                break;
                // 其他 case ...
            }
        }
    }else {
        QMessageBox::warning(nullptr, "警告", "But No!");

    }

}



void fenliang2::refreshall2(QWidget* w,QWidget* w3){


    if(w && w3){

        for (int j = 1 ;j <= 4; j++) {
            QString comboBox1 = QString("comboBox_%1A").arg(j);
            QString comboBox2 = QString("comboBox_%1B").arg(j);
            QString comboBox3 = QString("comboBox_%1C").arg(j);
//            QMessageBox::warning(nullptr, "警告","index:!"+comboBox1);
//            QMessageBox::warning(nullptr, "警告","index:!"+comboBox2);
//            QMessageBox::warning(nullptr, "警告","index:!"+comboBox3);
            QComboBox * com1 = w3->findChild<QComboBox*>(comboBox1);
            QComboBox* com2 = w3->findChild<QComboBox*>(comboBox2);
            QComboBox* com3 = w3->findChild<QComboBox*>(comboBox3);

            int a = com1->currentIndex();
            int b = com2->currentIndex();
            int c = com3->currentIndex();
//            QMessageBox::warning(nullptr, "警告","index:!"+QString::number( a));
//            QMessageBox::warning(nullptr, "警告","index:!"+QString::number( b));
//            QMessageBox::warning(nullptr, "警告","index:!"+QString::number( c));
            //以上逻辑无问题

        QString vdata1 = QString("lineEdit_%1_1").arg(a+1);
        QString vdata2 = QString("lineEdit_%1_1").arg(b+1);
        QString vdata3 = QString("lineEdit_%1_1").arg(c+1);

        QLineEdit* currentLineEdit1 = w->findChild<QLineEdit*>(vdata1);
        QLineEdit* currentLineEdit2 = w->findChild<QLineEdit*>(vdata2);
        QLineEdit* currentLineEdit3 = w->findChild<QLineEdit*>(vdata3);

//        QMessageBox::warning(nullptr, "警告", "YES!: "+vdata1);
//        QMessageBox::warning(nullptr, "警告", "YES!: "+vdata2);
//        QMessageBox::warning(nullptr, "警告", "YES!: "+vdata3);

        QString vvdata1 = currentLineEdit1->text();
        QString vvdata2 = currentLineEdit2->text();
        QString vvdata3 = currentLineEdit3->text();
        double  vvvdata1 = vvdata1.toDouble();
        double  vvvdata2 = vvdata2.toDouble();
        double  vvvdata3 = vvdata3.toDouble();

//        QMessageBox::warning(nullptr, "警告", "YES!: "+vvdata1);
//        QMessageBox::warning(nullptr, "警告", "YES!: "+vvdata2);
//        QMessageBox::warning(nullptr, "警告", "YES!: "+vvdata3);

        // 相位
        QString pdata1 = QString("lineEdit_%1_2").arg(a+1);
        QString pdata2 = QString("lineEdit_%1_2").arg(b+1);
        QString pdata3 = QString("lineEdit_%1_2").arg(c+1);

//        QMessageBox::warning(nullptr, "警告", "YES!: "+pdata1);
//        QMessageBox::warning(nullptr, "警告", "YES!: "+pdata2);
//        QMessageBox::warning(nullptr, "警告", "YES!: "+pdata3);

        QLineEdit* currentLineEdit4 = w->findChild<QLineEdit*>(pdata1);
        QLineEdit* currentLineEdit5 = w->findChild<QLineEdit*>(pdata2);
        QLineEdit* currentLineEdit6 = w->findChild<QLineEdit*>(pdata3);

        QString ppdata1 = currentLineEdit4->text();
        QString ppdata2 = currentLineEdit5->text();
        QString ppdata3 = currentLineEdit6->text();
        double  pppdata1 = ppdata1.toDouble();
        double  pppdata2 = ppdata2.toDouble();
        double  pppdata3 = ppdata3.toDouble();

//        QMessageBox::warning(nullptr, "警告", "YES!: "+ppdata1);
//        QMessageBox::warning(nullptr, "警告", "YES!: "+ppdata2);
//        QMessageBox::warning(nullptr, "警告", "YES!: "+ppdata3);
        struct Vector2D v1{vvvdata1,pppdata1};
        struct Vector2D v2{vvvdata2,pppdata2};
        struct Vector2D v3{vvvdata3,pppdata3};
        struct Vector2D result1{0,0} ;
        struct Vector2D result2{0,0} ;
        struct Vector2D result3{0,0} ;

        if(j==1||j==2){
            result1 = v1-v2;
            result2 = v2-v3;
            result3 = v3-v1;
        }else {
            result1 = v1+v2;
            result2 = v2+v3;
            result3 = v3+v1;
        }



        if (result1.y < 0) {
                result1.y += 360.0;
            }
            if (result2.y < 0) {
                result2.y += 360.0;
            }
            if (result3.y < 0) {
                result3.y += 360.0;
            }



        for (int k = 1; k <= 3; k++) {

            QString load = QString("lineEdit_%1").arg(k + (j-1)*6);
            QLineEdit* currentLineEdit = ui->widget->findChild<QLineEdit*>(load);
            QString load1 = QString("lineEdit_%1").arg(k + 3+(j-1) *6);
            QLineEdit* currentLineEdit1 = ui->widget->findChild<QLineEdit*>(load1);
            //            QMessageBox::warning(nullptr, "load", "YES!: "+load);
            //            QMessageBox::warning(nullptr, "load1", "YES!: "+load1);
            switch (k) {
            case 1:
                currentLineEdit->setText(QString::number( result1.x));
                currentLineEdit1->setText(QString::number( result1.y));
                break;
            case 2:
                currentLineEdit->setText(QString::number( result2.x));
                currentLineEdit1->setText(QString::number( result2.y));
                break;
            case 3:
                currentLineEdit->setText(QString::number( result3.x));
                currentLineEdit1->setText(QString::number( result3.y));
                break;
                // 其他 case ...
            }
        }


    }
    }
};
