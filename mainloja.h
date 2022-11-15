#ifndef MAINLOJA_H
#define MAINLOJA_H

#include <QMainWindow>
#include "loja.h"
#include "incluircd.h"
#include "incluirdvd.h"
#include "incluirlivro.h"

#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainLoja; }
QT_END_NAMESPACE

class MainLoja : public QMainWindow
{
    Q_OBJECT

public:
    MainLoja(QWidget *parent = nullptr);
    ~MainLoja();
    void mostrarLivros();
    void mostrarCDS();
    void mostrarDVDS();
    void totalItens();

private slots:
    void on_table_livros_cellDoubleClicked(int row, int column);

    void on_table_cds_cellDoubleClicked(int row, int column);

    void on_table_dvds_cellDoubleClicked(int row, int column);

    void on_actionLer_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void on_actionIncluir_Livro_triggered();

    void on_actionIncluir_CD_triggered();

    void on_actionIncluir_DVD_triggered();

    void slotIncluirLivro(QString nome, QString preco, QString autor);

    void slotIncluirCD(QString nome, QString preco, QString numfaixas);

    void slotIncluirDVD(QString nome, QString preco, QString duracao);



private:
    Ui::MainLoja *ui;

    //objeto tipo Loja:
    Loja X;

    //ponteiro qlabel =
    QLabel* total_itens;
    QLabel* prov;

    //PONTEIROS incluir:
    IncluirLivro* inclLivro;
    IncluirCD* inclCD;
    IncluirDVD* inclDVD;

};
#endif // MAINLOJA_H
