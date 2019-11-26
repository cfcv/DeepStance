#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scenesListModel_ = new QStringListModel();

    ui->setupUi(this);
    ui->scenesListView->setModel(scenesListModel_);

    refreshScenesList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshScenesList()
{
    std::ifstream scenes("../db/test/v1.0-mini/scene.json");
    QStringList sceneList;
    scenes >> ScenesData_;
    scenes.close();

    for(unsigned int i = 0; i < ScenesData_.size(); i++){
        sceneList << QString::fromStdString(ScenesData_[i]["name"]);
    }

    scenesListModel_->setStringList(sceneList);
}

void MainWindow::on_scenesListView_clicked(const QModelIndex &index)
{
    ui->scenesDescriptionLabel->setText(QString::fromStdString(ScenesData_[index.row()]["description"]));
}
