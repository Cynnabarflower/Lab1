#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Acid.h"
#include "Protein.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addAcidLayout(const Acid *a, int pos);
public slots:
    void textChanged();
    void posChanged();

private:
    Protein protein;
    Ui::MainWindow *ui;
    void clearLayout(QLayout *layout);
    QVector<int> index = QVector<int>();
};
#endif // MAINWINDOW_H
