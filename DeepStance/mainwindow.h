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

private slots:
    void on_scenesListView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    void refreshScenesList();
};

#endif // MAINWINDOW_H
