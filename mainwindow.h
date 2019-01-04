#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBlock>
#include <QMessageBox>
#include "grammar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_grammarCompleteBtn_clicked();

    void on_codeCompleteBtn_clicked();

private:
    Ui::MainWindow *ui;
    grammar g;
};

#endif // MAINWINDOW_H
