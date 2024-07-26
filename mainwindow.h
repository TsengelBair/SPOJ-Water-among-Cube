#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // UI
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QComboBox* comboBoxWidth;
    QComboBox* comboBoxHeight;
    QGridLayout* matrixLayout;
    QPushButton* viewBtn;

    int matrixWidth;
    int matrixHeight;
    QVector<QVector<int>> matrix;

    Scene* sceneWindow;

private slots:
    void updateMatrix();
    void showScene();
    void saveMatrix();
};

#endif // MAINWINDOW_H
