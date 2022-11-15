#include "incluirdvd.h"
#include "ui_incluirdvd.h"

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}
void IncluirDVD::clear(){
    ui->lineEdit_Dnome->clear();
    ui->lineEdit_Dpreco->clear();
    ui->lineEdit_Dduracao->clear();
}
void IncluirDVD::on_buttonBox_accepted(){
    QString nome = ui->lineEdit_Dnome->text();
    QString preco = ui->lineEdit_Dpreco->text();
    QString duracao = ui->lineEdit_Dduracao->text();
    emit signIncluirDVD(nome,preco,duracao);
}
