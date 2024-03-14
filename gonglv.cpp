#include "gonglv.h"
#include "ui_gonglv.h"

#define PI		3.1415926535897932384626433832795

gonglv::gonglv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gonglv)
{
    ui->setupUi(this);
}

gonglv::~gonglv()
{
    delete ui;
}
const double epsilon = 1e-9; // 可接受的误差范围，根据实际情况调整

bool isZeroPhaseDifference(double phaseDifference) {
    return std::abs(phaseDifference) < epsilon;
}

bool isMultipleOf90Degrees(double phaseDifference) {
    const double degrees90 = 90.0;
    return isZeroPhaseDifference(std::fmod(std::abs(phaseDifference), degrees90));
}

void gonglv::refreshallg(QWidget*w,QWidget*w3)
{
    if(w&&w3){
        int z =1 ;
        for (int i=1 ;i<=3;i=i+2) {
            QString comboBox1 = QString("comboBox_%1A").arg(i);
            QString comboBox2 = QString("comboBox_%1B").arg(i);
            QString comboBox3 = QString("comboBox_%1C").arg(i);

            QString comboBox4 = QString("comboBox_%1A").arg(i+1);
            QString comboBox5 = QString("comboBox_%1B").arg(i+1);
            QString comboBox6 = QString("comboBox_%1C").arg(i+1);

//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+comboBox1);
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+comboBox2);
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+comboBox3);
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+comboBox4);
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+comboBox5);
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+comboBox6);

            QComboBox* com1 = w3->findChild<QComboBox*>(comboBox1);
            QComboBox* com2 = w3->findChild<QComboBox*>(comboBox2);
            QComboBox* com3 = w3->findChild<QComboBox*>(comboBox3);
            QComboBox* com4 = w3->findChild<QComboBox*>(comboBox4);
            QComboBox* com5 = w3->findChild<QComboBox*>(comboBox5);
            QComboBox* com6 = w3->findChild<QComboBox*>(comboBox6);

            int a = com1->currentIndex();
            int b = com2->currentIndex();
            int c = com3->currentIndex();
            int a1 = com4->currentIndex();
            int b1 = com5->currentIndex();
            int c1 = com6->currentIndex();

//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+QString::number(a+1));
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+QString::number(b+1));
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+QString::number(c+1));
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+QString::number(a1+1));
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+QString::number(b1+1));
//            QMessageBox::warning(nullptr, "警告", "connect YES!: "+QString::number(c1+1));


            QString vdata1 = QString("lineEdit_%1_1").arg(a+1);
            QString vdata2 = QString("lineEdit_%1_1").arg(b+1);
            QString vdata3 = QString("lineEdit_%1_1").arg(c+1);
            QString vdata4 = QString("lineEdit_%1_1").arg(a1+1);
            QString vdata5 = QString("lineEdit_%1_1").arg(b1+1);
            QString vdata6 = QString("lineEdit_%1_1").arg(c1+1);

            QLineEdit* vcurrentLineEdit1 = w->findChild<QLineEdit*>(vdata1);
            QLineEdit* vcurrentLineEdit2 = w->findChild<QLineEdit*>(vdata2);
            QLineEdit* vcurrentLineEdit3 = w->findChild<QLineEdit*>(vdata3);
            QLineEdit* vcurrentLineEdit4 = w->findChild<QLineEdit*>(vdata4);
            QLineEdit* vcurrentLineEdit5 = w->findChild<QLineEdit*>(vdata5);
            QLineEdit* vcurrentLineEdit6 = w->findChild<QLineEdit*>(vdata6);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vdata1);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vdata2);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vdata3);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vdata4);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vdata5);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vdata6);

            QString vvdata1 = vcurrentLineEdit1->text();
            QString vvdata2 = vcurrentLineEdit2->text();
            QString vvdata3 = vcurrentLineEdit3->text();
            QString vvdata4 = vcurrentLineEdit4->text();
            QString vvdata5 = vcurrentLineEdit5->text();
            QString vvdata6 = vcurrentLineEdit6->text();

//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vvdata1);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vvdata2);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vvdata3);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vvdata4);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vvdata5);
//                        QMessageBox::warning(nullptr, "警告", "connect YES!: "+vvdata6);

            double  Udata1 = vvdata1.toDouble();
            double  Udata2 = vvdata2.toDouble();
            double  Udata3 = vvdata3.toDouble();
            double  Idata1 = vvdata4.toDouble();
            double  Idata2 = vvdata5.toDouble();
            double  Idata3 = vvdata6.toDouble();

//            QMessageBox::warning(nullptr, "警告", "connect YES!U1: "+QString::number(Udata1));
//            QMessageBox::warning(nullptr, "警告", "connect YES!U2: "+QString::number(Udata2));
//            QMessageBox::warning(nullptr, "警告", "connect YES!U3: "+QString::number(Udata3));
//            QMessageBox::warning(nullptr, "警告", "connect YES!I1: "+QString::number(Idata1));
//            QMessageBox::warning(nullptr, "警告", "connect YES!I2: "+QString::number(Idata2));
//            QMessageBox::warning(nullptr, "警告", "connect YES!I3: "+QString::number(Idata3));

            QString pdata1 = QString("lineEdit_%1_2").arg(a+1);
            QString pdata2 = QString("lineEdit_%1_2").arg(b+1);
            QString pdata3 = QString("lineEdit_%1_2").arg(c+1);
            QString pdata4 = QString("lineEdit_%1_2").arg(a1+1);
            QString pdata5 = QString("lineEdit_%1_2").arg(b1+1);
            QString pdata6 = QString("lineEdit_%1_2").arg(c1+1);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+pdata1);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+pdata2);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+pdata3);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+pdata4);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+pdata5);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+pdata6);

            QLineEdit* pcurrentLineEdit1 = w->findChild<QLineEdit*>(pdata1);
            QLineEdit* pcurrentLineEdit2 = w->findChild<QLineEdit*>(pdata2);
            QLineEdit* pcurrentLineEdit3 = w->findChild<QLineEdit*>(pdata3);
            QLineEdit* pcurrentLineEdit4 = w->findChild<QLineEdit*>(pdata4);
            QLineEdit* pcurrentLineEdit5 = w->findChild<QLineEdit*>(pdata5);
            QLineEdit* pcurrentLineEdit6 = w->findChild<QLineEdit*>(pdata6);


            QString ppdata1 = pcurrentLineEdit1->text();
            QString ppdata2 = pcurrentLineEdit2->text();
            QString ppdata3 = pcurrentLineEdit3->text();
            QString ppdata4 = pcurrentLineEdit4->text();
            QString ppdata5 = pcurrentLineEdit5->text();
            QString ppdata6 = pcurrentLineEdit6->text();

//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+ppdata1);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+ppdata2);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+ppdata3);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+ppdata4);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+ppdata5);
//                                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+ppdata6);

            double  UPdata1 = ppdata1.toDouble();
            double  UPdata2 = ppdata2.toDouble();
            double  UPdata3 = ppdata3.toDouble();
            double  IPdata1 = ppdata4.toDouble();
            double  IPdata2 = ppdata5.toDouble();
            double  IPdata3 = ppdata6.toDouble();




//            QMessageBox::warning(nullptr, "警告", "UP1: "+QString::number(UPdata1));
//            QMessageBox::warning(nullptr, "警告", "UP2: "+QString::number(UPdata2));
//            QMessageBox::warning(nullptr, "警告", "UP3: "+QString::number(UPdata3));
//            QMessageBox::warning(nullptr, "警告", "IP1: "+QString::number(IPdata1));
//            QMessageBox::warning(nullptr, "警告", "IP2: "+QString::number(IPdata2));
//            QMessageBox::warning(nullptr, "警告", "IP3: "+QString::number(IPdata3));
            double P1,P2,P3,Q1,Q2,Q3;
            double var1=0.0,var2=0.0,var3=0.0,var4=0.0,var5=0.0,var6=0.0;
            double x1 = UPdata1 - IPdata1;
            double x2 = UPdata2 - IPdata2;
            double x3 = UPdata3 - IPdata3;
            if(x1<0){
                x1+=360;
            }
            if(x2<0){
                x2+=360;
            }
            if(x3<0){
                x3+=360;
            }


            if(x1==0.0&&x1 == 360.0){
                var1 = 1.0;
                var4 = 0.0;

            }else if (x1 == 90.0) {
                var1 = 0.0;
                var4 = 1.0;
            }else if (x1 == 180.0) {
                var1 = -1.0;
                var4 = 0.0;
            }else if (x1 == 270.0) {
                var1 = 0.0;
                var4 = -1.0;
            }else{
                var1 =cos(x1* M_PI / 180);
                var4 =sin(x1* M_PI / 180);
            }

            if(x2==0.0){
                var2 = 1.0;
                var5 = 0.0;
            }else if (x2 == 90.0) {
                var2 = 0.0;
                var5 = 1.0;
            }else if (x2 == 180.0) {
                var2 = -1.0;
                var5 = 0.0;
            }else if (x2 == 270.0) {
                var2 = 0.0;
                var5 = -1.0;
            }else{
                var2 =cos(x2* PI / 180.0);
                var5 =sin(x2* PI / 180.0);
            }

            if(x3==0.0){
                var3 = 1.0;
                var6 = 0.0;
            }else if (x3 == 90.0) {
                var3 = 0.0;
                var6 = 1.0;
            }else if (x3 == 180.0) {
                var3 = -1.0;
                var6 = 0.0;
            }else if (x3 == 270.0) {
                var3 = 0.0;
                var6 = -1.0;
            }else{
                var3 =cos(x3* PI / 180.0);
                var6 =sin(x3* PI / 180.0);
            }
            // 判断相位差是否为0或90度的倍数
            P1 = Udata1*Idata1*var1;
            P2 = Udata2*Idata2*var2;
            P3 = Udata3*Idata3*var3;

            Q1 = Udata1*Idata1*var4;
            Q2 = Udata2*Idata2*var5;
            Q3 = Udata3*Idata3*var6;

            double meanP = (P1 + P2 + P3);
            double meanQ = (Q1 + Q2 + Q3);


//            QMessageBox::warning(nullptr, "警告", "Q1: "+QString::number(Q1));
//            QMessageBox::warning(nullptr, "警告", "Q2: "+QString::number(Q2));
//            QMessageBox::warning(nullptr, "警告", "Q3: "+QString::number(Q3));
//            QMessageBox::warning(nullptr, "警告", "MEANQ: "+QString::number(meanQ));

            double S1 = sqrt(pow(P1,2)+pow(Q1,2));
            double S2 = sqrt(pow(P2,2)+pow(Q2,2));
            double S3 = sqrt(pow(P3,2)+pow(Q3,2));
            double meanS = sqrt(pow(meanP,2)+pow(meanQ,2));
//            QMessageBox::warning(nullptr, "警告", "S1: "+QString::number(S1));
//            QMessageBox::warning(nullptr, "警告", "S2: "+QString::number(S2));
//            QMessageBox::warning(nullptr, "警告", "S3: "+QString::number(S3));
//            QMessageBox::warning(nullptr, "警告", "MEANS: "+QString::number(meanS));

            double fai1 = P1/S1;
            double fai2 = P2/S2;
            double fai3 = P3/S3;
            if(S1 == 0.0){
                fai1 = 0;
            }
            if(S2 == 0.0){
                fai2 = 0;
            }

            if(S3 == 0.0){
                fai3 = 0;
            }

            double meanfai = meanP/meanS;
            if(meanS == 0.0){
                meanfai = 0;
            }
//            QMessageBox::warning(nullptr, "警告", "FAI1: "+QString::number(fai1));
//            QMessageBox::warning(nullptr, "警告", "FAI2: "+QString::number(fai2));
//            QMessageBox::warning(nullptr, "警告", "FAI3: "+QString::number(fai3));
//            QMessageBox::warning(nullptr, "警告", "MEANFAI: "+QString::number(meanfai));





            for (int j =1;j <= 4 ;j++) {
                for (int k= 1;k <=4 ;k++) {

                    QString load = QString("lineEdit%1_%2_%3").arg(z).arg(j).arg(k);
                    QLineEdit* currentLineEdit = ui->widget->findChild<QLineEdit*>(load);
//                    QMessageBox::warning(nullptr, "警告", "connect YES!: "+load);
                    if(currentLineEdit){
                    if(j==1 && k==1)        {
                        currentLineEdit->setText(QString::number( P1));
                    }else if (j==1&&k==2)   {
                        currentLineEdit->setText(QString::number( P2));
                    }else if (j==1 && k==3) {
                        currentLineEdit->setText(QString::number( P3));
                    }else if (j==1 && k==4) {
                        currentLineEdit->setText(QString::number( meanP));
                    }else if(j==2 && k==1)  {
                        currentLineEdit->setText(QString::number( Q1));
                    }else if (j==2&&k==2)   {
                        currentLineEdit->setText(QString::number( Q2));
                    }else if (j==2 && k==3) {
                        currentLineEdit->setText(QString::number( Q3));
                    }else if (j==2 && k==4) {
                        currentLineEdit->setText(QString::number( meanQ));
                    }else if(j==3 && k==1)  {
                        currentLineEdit->setText(QString::number( fai1));
                    }else if (j==3&&k==2)   {
                        currentLineEdit->setText(QString::number( fai2));
                    }else if (j==3 && k==3) {
                        currentLineEdit->setText(QString::number( fai3));
                    }else if (j==3 && k==4) {
                        currentLineEdit->setText(QString::number( meanfai));
                    }else if(j==4 && k==1)  {
                        currentLineEdit->setText(QString::number( S1));
                    }else if (j==4&&k==2)   {
                        currentLineEdit->setText(QString::number( S2));
                    }else if (j==4 && k==3) {
                        currentLineEdit->setText(QString::number( S3));
                    }else if (j==4 && k==4) {
                        currentLineEdit->setText(QString::number( meanS));
                    }
                    }else                   {
                        QMessageBox::warning(nullptr, "警告", "NO!: " +load);
                    }
                }
            }
            z++;
        }

    }
}



