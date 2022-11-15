#include "incluircd.h"
#include "ui_incluircd.h"

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}
void IncluirCD::clear(){
    ui->lineEdit_Cnome->clear();
    ui->lineEdit_Cpreco->clear();
    ui->lineEdit_Cnumfaixas->clear();
}
void IncluirCD::on_buttonBox_accepted(){
    QString nome = ui->lineEdit_Cnome->text();
    QString preco = ui->lineEdit_Cpreco->text();
    QString numfaixas = ui->lineEdit_Cnumfaixas->text();
    emit signIncluirCD(nome,preco,numfaixas);
}
