#include "bianbi.h"
#include "ui_bianbi.h"

bianbi::bianbi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bianbi)
{



    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::clicked, [=](QAbstractButton *button){
        if (QPushButton *pushButton = dynamic_cast<QPushButton *>(button)) {
            if (pushButton == ui->buttonBox->button(QDialogButtonBox::Yes)) {
                // 用户点击了"Yes"按钮的处理逻辑
            } else if (pushButton == ui->buttonBox->button(QDialogButtonBox::No)) {
                // 用户点击了"No"按钮的处理逻辑
            } else if (pushButton == ui->buttonBox->button(QDialogButtonBox::Cancel)) {
                // 用户点击了"Cancel"按钮的处理逻辑
            } else if (pushButton == ui->buttonBox->button(QDialogButtonBox::Ok)) {
                // 用户点击了"Ok"按钮的处理逻辑
            } else {
                // 其他按钮的处理逻辑
            }
        }
    });



}

bianbi::~bianbi()
{
    delete ui;
}

qfloat16 bianbi::cal() {
    // 假设 num1 和 num2 是该类的成员变量，并且已经被正确初始化
    float result = num1.toFloat() / num2.toFloat();
    // 假设 qfloat16 类有一个构造函数，可以接受一个浮点数，并将其转换为 qfloat16 类型
    qfloat16 resultQFloat16(result);
    return resultQFloat16;
}
