#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Amino.h"
#include "NonStandartAcid.h"

#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->radioButton, &QRadioButton::clicked, this, [this](){
               ui->lineEdit_2->setEnabled(true);
           });
    connect(ui->radioButton_2, &QRadioButton::clicked, this, [this](){
               ui->lineEdit_2->setEnabled(false);
           });

    connect(ui->pushButton_3, &QPushButton::clicked, this, [this](){
        QString fname = QFileDialog::getSaveFileName(nullptr, "filename", ".", "Text files (*.txt)" );
        if (fname.isEmpty()) {
            return;
        }
        protein.saveToFile(fname.toUtf8().begin());
    });

    connect(ui->pushButton_4, &QPushButton::clicked, this, [this](){
        QString fname = QFileDialog::getOpenFileName(nullptr, "filename", ".", "Text files (*.txt)" );
        if (fname.isEmpty()) {
            return;
        }
        Protein protein2 = Protein();
        protein2.loadFromFile(fname.toUtf8().begin());
        protein = protein + protein2;
        ui->pushButton_2->setEnabled(protein.size() > 0 && ui->spinBox->value() <= protein.size());

        clearLayout(ui->verticalLayout_3);

        int i = 0;
        for (auto a : protein) {
            addAcidLayout(a, i);
            i++;
        }
    });

    connect(ui->pushButton_5, &QPushButton::clicked, this, [this](){
        protein.clear();
        clearLayout(ui->verticalLayout_3);
    });

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(posChanged()));

    connect(ui->pushButton_2, &QPushButton::clicked, this, [this](){
        protein.remove(ui->spinBox->value() - 1);
        auto c = ui->verticalLayout_3->takeAt(ui->spinBox->value() - 1)->layout();
        ui->spinBox->setMaximum(protein.size()+1);
        ui->pushButton_2->setEnabled(protein.size() > 0 && ui->spinBox->value() <= protein.size());

        QLayoutItem *item;
        QWidget *widget;
        while ((item = c->takeAt(0))) {
            if ((widget = item->widget()) != 0) {
                widget->hide(); delete widget;
            }
            else {
                delete item;
            }
        }
           });

    connect(ui->pushButton, &QRadioButton::clicked, this, [this](){
        QString fullname = ui->lineEdit->text();
        QString shortname = ui->lineEdit_2->text();
        int pos = ui->spinBox->value() - 1;

        Acid *a;
        if (ui->radioButton->isChecked()) {
            a = new Amino(fullname.toUtf8().constData(), shortname.front().cell());
        } else {
            a = new NonStandartAcid(fullname.toUtf8().constData());
        }
        try {
            protein.insert(a, pos);
            ui->spinBox->setMaximum(protein.size()+1);
        } catch (_exception) {
            QMessageBox msgBox;
            msgBox.setText("Incorrect position");
            msgBox.exec();
            return;

        }

        ui->pushButton_2->setEnabled(protein.size() > 0 && ui->spinBox->value() <= protein.size());
        addAcidLayout(a, pos);

   });

}

void MainWindow::clearLayout(QLayout *layout) {
    while (layout->count() > 1)
    {
      auto c = ui->verticalLayout_3->takeAt(0)->layout();
        QLayoutItem *item;
        QWidget *widget;
        ui->verticalLayout_3->removeItem(c);
        while ((item = c->takeAt(0))) {
            if ((widget = item->widget()) != 0) {
                widget->hide(); delete widget;
            }
            else {
                delete item;
            }
        }
    }
}

void MainWindow::textChanged()
{
    ui->pushButton->setEnabled(!ui->lineEdit->text().isEmpty());
}

void MainWindow::posChanged()
{
    ui->pushButton_2->setEnabled(protein.size() > 0 && ui->spinBox->value() <= protein.size());
}

void MainWindow::addAcidLayout(const Acid *a, int pos) {
    auto c = new QHBoxLayout();
    auto label = new QLabel();
    auto remove = new QPushButton();
    label->setText(QString::fromStdString(&(a->toString()[1])));
    remove->setText("-");
    remove->setVisible(false);
    index.append(ui->verticalLayout_3->count());
    connect(remove, &QPushButton::clicked, this, [this, a, c](){
        ui->pushButton_2->setEnabled(protein.size() > 0 && ui->spinBox->value() <= protein.size());
        ui->spinBox->setMaximum(protein.size()+1);
        QLayoutItem *item;
        QWidget *widget;
        ui->verticalLayout_3->removeItem(c);
        while ((item = c->takeAt(0))) {
            if ((widget = item->widget()) != 0) {
                widget->hide(); delete widget;
            }
            else {
                delete item;
            }
        }
    });

    c->addWidget(label);
    c->addStretch();
    c->addWidget(remove);
    ui->verticalLayout_3->insertLayout(pos, c);
}


MainWindow::~MainWindow()
{
    delete ui;
}

