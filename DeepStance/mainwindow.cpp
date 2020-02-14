#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scenesListModel_ = new QStringListModel();

    isPlaying_ = false;

    ui->setupUi(this);
    ui->scenesListView->setModel(scenesListModel_);

    QTimer *refreshTimer = new QTimer(this);
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(readVideoNextFrame()));
    refreshTimer->start(1/12);

    refreshScenesList();
    loadSampleData();
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

void MainWindow::loadSampleData()
{
    std::ifstream sample("../db/test/v1.0-mini/sample_data.json");
    sample >> SampleData_;
}

void MainWindow::findFirstImage(std::string token)
{
    currentIndex_ = 0;
    qDebug() << SampleData_.size();
    for(size_t i = 0; i < SampleData_.size(); i++) {
        if(SampleData_[i]["sample_token"] == token) {
            std::string fname = SampleData_[i]["filename"];
            if(SampleData_[i]["fileformat"] == "jpg" && fname.find("CAM_FRONT")!= std::string::npos) {
                currentIndex_ = i;
                break;
            }
        }
    }
}

void MainWindow::findNext()
{
    std::string nextToken = SampleData_[currentIndex_]["next"];

    size_t ci = currentIndex_;

    if(nextToken != "") {
        for(size_t i = 0; i < SampleData_.size(); i++) {
            std::string currToken = SampleData_[i]["token"];
            if(currToken == nextToken) {
                currentIndex_ = i;
                break;
            }
        }
    }

    if(currentIndex_ == ci)
        ui->sfmlView->setPause(true);
}

void MainWindow::setCurrentFrame()
{
    std::string fname = SampleData_[currentIndex_]["filename"];
    ui->sfmlView->setBackgroundTexture("../db/test/" + fname);
}

void MainWindow::on_scenesListView_clicked(const QModelIndex &index)
{
    ui->scenesDescriptionLabel->setText(QString::fromStdString(ScenesData_[index.row()]["description"]));
    findFirstImage(ScenesData_[index.row()]["first_sample_token"]);
    setCurrentFrame();
    isPlaying_ = true;
    ui->sfmlView->setPause(false);
}

void MainWindow::readVideoNextFrame()
{
    if(isPlaying_) {
        findNext();
        setCurrentFrame();
    }
}

void MainWindow::on_pushButton_clicked()
{
    isPlaying_ = !isPlaying_;
    ui->sfmlView->setPause();
}

void MainWindow::on_classifierComboBox_currentIndexChanged(int index)
{
    ui->sfmlView->setMethod(index);
}
