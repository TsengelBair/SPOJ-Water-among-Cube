#include "mainwindow.h"

#include <QVector>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), matrixWidth(3), matrixHeight(3), sceneWindow(nullptr) // По дефолту 3х3
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);

    comboBoxWidth = new QComboBox(this);
    comboBoxHeight = new QComboBox(this);
    for (int i = 1; i <= 10; ++i) {
        comboBoxWidth->addItem(QString::number(i));
        comboBoxHeight->addItem(QString::number(i));
    }

    comboBoxWidth->setCurrentText(QString::number(matrixWidth));
    comboBoxHeight->setCurrentText(QString::number(matrixHeight));

    viewBtn = new QPushButton("Построить", this);

    QLabel* matrixWidthLabel = new QLabel("Ширина поля:");
    QLabel* matrixHeightLabel = new QLabel("Высота поля:");

    mainLayout->addWidget(matrixWidthLabel);
    mainLayout->addWidget(comboBoxWidth);
    mainLayout->addWidget(matrixHeightLabel);
    mainLayout->addWidget(comboBoxHeight);

    matrixLayout = new QGridLayout();
    mainLayout->addLayout(matrixLayout);

    mainLayout->addWidget(viewBtn);

    connect(comboBoxWidth, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateMatrix);
    connect(comboBoxHeight, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateMatrix);
    connect(viewBtn, &QPushButton::clicked, this, &MainWindow::showScene);

    updateMatrix();
}

MainWindow::~MainWindow() {}

// Динамически обновляем отображение матрицы, при смене цифр в комбобоксах
void MainWindow::updateMatrix()
{
    QLayoutItem *item;
    while ((item = matrixLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    matrixWidth = comboBoxWidth->currentText().toInt();
    matrixHeight = comboBoxHeight->currentText().toInt();

    for (int row = 0; row < matrixHeight; ++row) {
        for (int col = 0; col < matrixWidth; ++col) {
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setAlignment(Qt::AlignCenter);
            matrixLayout->addWidget(lineEdit, row, col);
        }
    }
}

// Перед отрисовкой сохраняем матрицу
void MainWindow::saveMatrix()
{
    matrix.clear();
    matrix.resize(matrixHeight);

    for (int row = 0; row < matrixHeight; ++row) {
        matrix[row].resize(matrixWidth);
        for (int col = 0; col < matrixWidth; ++col) {
            QLineEdit* lineEdit = qobject_cast<QLineEdit*>(matrixLayout->itemAtPosition(row, col)->widget());
            if (lineEdit) {
                bool ok;
                int value = lineEdit->text().toInt(&ok);
                if (ok) {
                    matrix[row][col] = value;
                } else {
                    matrix[row][col] = 0;
                }
            }
        }
    }
}

void MainWindow::showScene()
{
    // Сначала сохраняем матрицу
    saveMatrix();
    sceneWindow = new Scene();
    sceneWindow->draw(matrix);
    sceneWindow->show();
}
