#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

#include <json.hpp>
using json = nlohmann::json;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStringListModel *scenesListModel_;
    json ScenesData_;
    json SampleData_;

    bool isPlaying_;

    size_t currentIndex_;

private slots:
    void on_scenesListView_clicked(const QModelIndex &index);
    void readVideoNextFrame();

    void on_pushButton_clicked();

    void on_classifierComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    void refreshScenesList();
    void loadSampleData();
    void findFirstImage(std::string token);
    void findNext();
    void setCurrentFrame();
};

#endif // MAINWINDOW_H
