#include "incluirlivro.h"
#include "ui_incluirlivro.h"

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}
void IncluirLivro::clear(){
    ui->lineEdit_Lnome->clear();
    ui->lineEdit_Lpreco->clear();
    ui->lineEdit_Lautor->clear();
}
void IncluirLivro::on_buttonBox_accepted(){
    QString nome = ui->lineEdit_Lnome->text();
    QString preco = ui->lineEdit_Lpreco->text();
    QString autor = ui->lineEdit_Lautor->text();
    emit signIncluirLivro(nome,preco,autor);
}
