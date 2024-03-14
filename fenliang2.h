#ifndef FENLIANG2_H
#define FENLIANG2_H
#include <QMessageBox>
#include <QWidget>
#include <iostream>
#include <math.h>
#include <QComboBox>
namespace Ui {
class fenliang2;
}

struct Vector2D {
    double x;
    double y;

    Vector2D(double mag, double dir) : x(mag), y(dir) {}

    Vector2D operator-(const Vector2D& other) const {
        double resultX = x * cos(y * M_PI / 180) - other.x * cos(other.y * M_PI / 180);
        double resultY = x * sin(y * M_PI / 180) - other.x * sin(other.y * M_PI / 180);

        double resultMagnitude = sqrt(resultX * resultX + resultY * resultY);
        double resultDirection = atan2(resultY, resultX) * 180.0 / M_PI;

        // 将方向转换为度数，确保结果在 [-180, 180) 范围内
        resultDirection = fmod(resultDirection + 180, 360) - 180;

        return Vector2D(resultMagnitude, resultDirection);
    }

    // 旋转复数
    Vector2D rotate(double angle) const {
           double newAngle = fmod(y + angle, 360); // 直接在原有的角度上增加旋转角度，并确保在 [0, 360) 范围内
           return Vector2D(x, newAngle);
       }

    // 重载 + 运算符
    Vector2D operator+(const Vector2D& other) const {
        double resultX = x * cos(y * M_PI / 180) + other.x * cos(other.y * M_PI / 180);
        double resultY = x * sin(y * M_PI / 180) + other.x * sin(other.y * M_PI / 180);

        double resultMagnitude = sqrt(resultX * resultX + resultY * resultY);
        double resultDirection = atan2(resultY, resultX) * 180.0 / M_PI;

        // 将方向转换为度数，确保结果在 [-180, 180) 范围内
        resultDirection = fmod(resultDirection + 180, 360) - 180;

        return Vector2D(resultMagnitude, resultDirection);
    }

    // 重载 / 运算符
    Vector2D operator/(double scalar) const {
        if (scalar == 0.0) {
            // 处理除零错误，这里可以根据实际情况选择适当的处理方式
            std::cerr << "Error: Division by zero\n";
            return *this; // 返回原向量
        }

        return Vector2D(x / scalar, y);
    }
};

class fenliang2 : public QWidget
{
    Q_OBJECT

public:
    explicit fenliang2(QWidget *parent = nullptr);

    ~fenliang2();
    Vector2D calculateVectorSum(const Vector2D& v1, const Vector2D& v2);
    void refresh2(QWidget* ,int s, int a,int b,int c);
    void refreshall2(QWidget*,QWidget*);
private:
    Ui::fenliang2 *ui;

};

#endif // FENLIANG2_H
