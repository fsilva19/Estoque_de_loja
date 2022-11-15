#include "mainloja.h"
#include "ui_mainloja.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QDialog>

MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
    , X()
    , total_itens(nullptr)
    , inclLivro(nullptr)
    , inclCD(nullptr)
    , inclDVD(nullptr)
    , prov(nullptr)

{
    ui->setupUi(this);
    //ponteiro qlabel:
    ui->statusbar->insertWidget(0,new QLabel("Total de itens: "));
    total_itens = new QLabel(this);
    ui->statusbar->insertWidget(1,total_itens);
    total_itens->setText("-");

    //OBJETOS DE CADA CLASSE:
    inclLivro = new IncluirLivro(this);
    inclCD = new IncluirCD(this);
    inclDVD = new IncluirDVD(this);

    //FAZENDO AS CONEXÕES:
    connect(inclLivro, &IncluirLivro::signIncluirLivro, this, &MainLoja::slotIncluirLivro);
    connect(inclCD, &IncluirCD::signIncluirCD, this, &MainLoja::slotIncluirCD);
    connect(inclDVD, &IncluirDVD::signIncluirDVD, this, &MainLoja::slotIncluirDVD);


    //BACKGROUND LIGHTGRAY:
    //COLOCA BACKGROUND NAS TABELAS:
    ui->table_livros->setStyleSheet("background:lightgray;");
    ui->table_cds->setStyleSheet("background:lightgray;");
    ui->table_dvds->setStyleSheet("background:lightgray;");

    //COLOCA BACKGROUND NAS COLUNAS:
    ui->table_livros->setStyleSheet("QHeaderView::section{background-color:lightgray}");
    ui->table_cds->setStyleSheet("QHeaderView::section{background-color:lightgray}");
    ui->table_dvds->setStyleSheet("QHeaderView::section{background-color:lightgray}");

    //DIMENSIONA AS COLUNAS:
    //LIVROS:
    ui->table_livros->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->table_livros->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->table_livros->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    //CDS:
    ui->table_cds->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->table_cds->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->table_cds->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    //DVDS:
    ui->table_dvds->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->table_dvds->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->table_dvds->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);


}
MainLoja::~MainLoja()
{
    delete ui;
}
void MainLoja::mostrarLivros(){
    ui->table_livros->clearContents();
    ui->table_livros->setRowCount(X.getNumLivro());
    QLabel* prov;

    for(int i=0;i<X.getNumLivro();i++){
        for(int j=0;j<=2;j++){
            prov = new QLabel();
            Livro L = X.getLivro(i);
            if(j==0){
                QString nome = QString::fromStdString(L.getNome());
                prov->setText(nome);
                prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            }
            if(j==1){
                QString preco = QString::number(L.getPreco(),'f',2);
                prov->setText(preco);
                prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
            }
            if(j==2){
                QString autor = QString::fromStdString(L.getAutor());
                prov->setText(autor);
                prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            }
            ui->table_livros->setCellWidget(i,j,prov);
        }
    }
}
void MainLoja::mostrarCDS(){
    ui->table_cds->clearContents();
    ui->table_cds->setRowCount(X.getNumCD());
    QLabel* prov;

    for(int i=0;i<X.getNumCD();i++){
        for(int j=0;j<=2;j++){
            prov = new QLabel();
            CD C = X.getCD(i);
            if(j==0){
                QString nome = QString::fromStdString(C.getNome());
                prov->setText(nome);
                prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            }
            if(j==1){
                QString preco = QString::number(C.getPreco(),'f',2);
                prov->setText(preco);
                prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
            }
            if(j==2){
                QString numfaixas = QString::number(C.getNumFaixas());
                prov->setText(numfaixas);
                prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            }
            ui->table_cds->setCellWidget(i,j,prov);
        }
    }
}
void MainLoja::mostrarDVDS(){
    ui->table_dvds->clearContents();
    ui->table_dvds->setRowCount(X.getNumDVD());
    QLabel* prov;

    for(int i=0;i<X.getNumDVD();i++){
        for(int j=0;j<=2;j++){
            prov = new QLabel();
            DVD D = X.getDVD(i);
            if(j==0){
                QString nome = QString::fromStdString(D.getNome());
                prov->setText(nome);
                prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            }
            if(j==1){
                QString preco = QString::number(D.getPreco(),'f',2);
                prov->setText(preco);
                prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
            }
            if(j==2){
                QString duracao = QString::number(D.getDuracao());
                prov->setText(duracao);
                prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            }
            ui->table_dvds->setCellWidget(i,j,prov);
        }
    }
}
//FUNÇÃO PARA SABER O TOTAL DE ITENS:
void MainLoja::totalItens(){
    int total = X.getNumCD() + X.getNumDVD() + X.getNumLivro();
    total_itens->setText(QString::number(total));
}

//SLOTS para excluir um item:
void MainLoja::on_table_livros_cellDoubleClicked(int row, int column)
{
    X.excluirLivro(row);
    mostrarLivros();
    totalItens();
}

void MainLoja::on_table_cds_cellDoubleClicked(int row, int column)
{
    X.excluirCD(row);
    mostrarCDS();
    totalItens();
}

void MainLoja::on_table_dvds_cellDoubleClicked(int row, int column)
{
    X.excluirDVD(row);
    mostrarDVDS();
    totalItens();
}

void MainLoja::on_actionLer_triggered()
{
    QString fileName = QFileDialog::
          getOpenFileName(this,
                          "Ler estoque",
                          QString(),
                          "Text Files (*.txt);");
    bool teste_valido = X.ler(fileName.toStdString());
    if(!teste_valido){
        QMessageBox::critical(this,
                              tr("Erro!"),
                              tr("Erro na leitura do arquivo selecionado!"));
    }
    mostrarLivros();
    mostrarCDS();
    mostrarDVDS();
    totalItens();
}

void MainLoja::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::
          getSaveFileName(this,
                          "Salvar estoque",
                          QString(),
                          "Text Files (*.txt);");
    bool teste_valido = X.salvar(fileName.toStdString());
    if(!teste_valido){
        QMessageBox::critical(this,
                              tr("Erro!"),
                              tr("Erro na leitura do arquivo selecionado!"));
    }
}


void MainLoja::on_actionSair_triggered()
{
    QCoreApplication::quit();
}


void MainLoja::on_actionIncluir_Livro_triggered()
{
    inclLivro->clear();
    inclLivro->show();
}
void MainLoja::on_actionIncluir_CD_triggered()
{
    inclCD->clear();
    inclCD->show();
}
void MainLoja::on_actionIncluir_DVD_triggered()
{
    inclDVD->clear();
    inclDVD->show();
}


void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor)
{
    Livro L;
    L = Livro(nome.toStdString(), round(preco.toFloat() * 100.0), autor.toStdString());

    X.incluirLivro(L);
    mostrarLivros();
    totalItens();
}

void MainLoja::slotIncluirCD(QString nome, QString preco, QString numfaixas)
{
    CD C;
    C = CD(nome.toStdString(), round(preco.toFloat() * 100.0), numfaixas.toInt());

    X.incluirCD(C);
    mostrarCDS();
    totalItens();
}

void MainLoja::slotIncluirDVD(QString nome, QString preco, QString duracao)
{
    DVD D;
    D = DVD(nome.toStdString(), round(preco.toFloat() * 100.0), duracao.toInt());

    X.incluirDVD(D);
    mostrarDVDS();
    totalItens();
}
