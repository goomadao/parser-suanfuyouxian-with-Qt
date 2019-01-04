#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Parser"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_grammarCompleteBtn_clicked()
{
    g.clear();
    QTextDocument *document = ui->grammarEdit->document();
    QTextBlock textBlock;
    bool flag=0;
    for (textBlock=document->begin();textBlock!=document->end();textBlock=textBlock.next())
    {
        int bs=g.get_grammar(textBlock.text().simplified().toStdString());
        if (bs==0)
        {
            QString msg="There are some errors in the grammar.Please type in again.";
            QMessageBox::warning(this,
                                 tr("Error"),
                                 msg,
                                 QMessageBox::Yes);
            g.clear();
            return;
        }
        else if (bs==-1)
        {
            flag=1;
        }
    }
    if (flag)
    {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("There are repeated grammars and they have been removed."),
                             QMessageBox::Yes);
    }
    g.get_firstvt();
    g.get_lastvt();
    g.get_relation();
    g.get_find();
    string s="1234\n5678";
    ui->vtBrowser->setText(QString::fromStdString(g.print_vt_to_qt()));
    ui->vnBrowser->setText(QString::fromStdString(g.print_vn_to_qt()));
    ui->firstvtBrowser->setText(QString::fromStdString(g.print_firstvt_to_qt()));
    ui->lastvtBrowser->setText(QString::fromStdString(g.print_lastvt_to_qt()));
    ui->relationBrowser->setText(QString::fromStdString(g.print_relation_to_qt()));
    //g.fill_relation();
}

void MainWindow::on_codeCompleteBtn_clicked()
{
//    qDebug()<<tr("Yes\n");
    g.parsed_clear();


    if (g.grammarMapEmpty())
    {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Please input correct grammar fitst"),
                             QMessageBox::Yes);
        return;
    }

    ui->parsingWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //ui->parsingWidget->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Stretch);
    ui->parsingWidget->verticalHeader()->setResizeContentsPrecision(QHeaderView::Stretch);
    ui->parsingWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->parsingWidget->setRowCount(0);
    QTextDocument *document = ui->codeEdit->document();
    QTextBlock textBlock;
    for (textBlock=document->begin();textBlock!=document->end();textBlock=textBlock.next())
    {
        if (!g.get_code(textBlock.text().simplified().toStdString()))
        {
            QMessageBox::warning(this,
                                 tr("Error"),
                                 tr("There may be undefined symbols, please check"),
                                 QMessageBox::Yes);

            g.parsed_clear();
            return;
        }
    }
//    qDebug()<<QString::fromStdString(g.code_to_string());
    if (g.code_to_string().empty())
    {
        return;
    }
//    qDebug()<<tr("11\n");
    g.parsing_to_qt();
    int rowCount;
    for (int i=0;i<g.rtq.size();++i)
    {
        rowCount=ui->parsingWidget->rowCount();
        ui->parsingWidget->setRowCount(rowCount+1);
//        qDebug()<<tr("Yes1\n");
        string old;
        while (!g.rtq[i].old.empty())
        {
            old=g.rtq[i].old.top()+old;
            g.rtq[i].old.pop();
        }
//        qDebug()<<tr("Yes2\n");
        string code;
        while (!g.rtq[i].code.empty())
        {
            code+=g.rtq[i].code.front();
            g.rtq[i].code.pop();
        }
//        qDebug()<<tr("Yes3\n");
        string nnew;
        while (!g.rtq[i].nnew.empty())
        {
            nnew=g.rtq[i].nnew.top()+nnew;
            g.rtq[i].nnew.pop();
        }
        QTableWidgetItem *i1=new QTableWidgetItem(QString::fromStdString(old));
        QTableWidgetItem *i2=new QTableWidgetItem(QString::fromStdString(code));
        QTableWidgetItem *i3=new QTableWidgetItem(QString::fromStdString(g.rtq[i].relation));
        QTableWidgetItem *i4=new QTableWidgetItem(QString::fromStdString(g.rtq[i].action));
        QTableWidgetItem *i5=new QTableWidgetItem(QString::fromStdString(nnew));
        ui->parsingWidget->setItem(rowCount,0,i1);
        ui->parsingWidget->setItem(rowCount,1,i2);
        ui->parsingWidget->setItem(rowCount,2,i3);
        ui->parsingWidget->setItem(rowCount,3,i4);
        ui->parsingWidget->setItem(rowCount,4,i5);
    }
    if (!g.errMsg.empty())
    {
        //string msg="There is no grammar for the reduction of \""+g.errSub+"\"";
        QMessageBox::warning(this,
                             tr("Error"),
                             QString::fromStdString(g.errMsg),
                             QMessageBox::Yes);
        g.errMsg="";
        g.errSub="";
        g.parsed_clear();
        return;
    }
//    rowCount=ui->parsingWidget->rowCount();
//    ui->parsingWidget->setRowCount(rowCount+1);
//    ui->parsingWidget->setRowHeight(rowCount,24);
//    QTableWidgetItem *i1 = new QTableWidgetItem(tr("1"));
//    QTableWidgetItem *i2 = new QTableWidgetItem(tr("12"));
//    QTableWidgetItem *i3 = new QTableWidgetItem(tr("123"));
//    QTableWidgetItem *i4 = new QTableWidgetItem(tr("1234"));
//    QTableWidgetItem *i5 = new QTableWidgetItem(tr("12345"));
//    ui->parsingWidget->setItem(rowCount,0,i1);
//    ui->parsingWidget->setItem(rowCount,1,i2);
//    ui->parsingWidget->setItem(rowCount,2,i3);
//    ui->parsingWidget->setItem(rowCount,3,i4);
//    ui->parsingWidget->setItem(rowCount,4,i5);
}
