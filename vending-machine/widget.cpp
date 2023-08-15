#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 초기 잔액 설정 (0원)
    money = 0;
    // 초기 버튼 활성화 설정
    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbMilk->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeMoney(int diff)
{
    money += diff;
    ui->lcdNumber->display(money);

    // 돈이 충분하면 음료 버튼 활성화
    if (money >= 100) {
        ui->pbCoffee->setEnabled(true);
    }
    if (money >= 150) {
        ui->pbTea->setEnabled(true);
    }
    if (money >= 200) {
        ui->pbMilk->setEnabled(true);
    }

    // 돈이 부족하면 음료 버튼 비활성화
    if (money < 100) {
        ui->pbCoffee->setEnabled(false);
    }
    if (money < 150) {
        ui->pbTea->setEnabled(false);
    }
    if (money < 200) {
        ui->pbMilk->setEnabled(false);
    }
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);
}

void Widget::on_pbTea_clicked()
{
    changeMoney(-150);
}

void Widget::on_pbMilk_clicked()
{
    changeMoney(-200);
}

void Widget::on_pbReset_clicked()
{
    // 잔돈 계산
    int change500 = money / 500;
    money = money % 500;
    int change100 = money / 100;
    money = money % 100;

    // 잔돈 정보 표시
    QString text = "500원: " + QString::number(change500) + "개\n"
                   "100원: " + QString::number(change100) + "개";
    QMessageBox::information(this, "잔돈", text);
}
