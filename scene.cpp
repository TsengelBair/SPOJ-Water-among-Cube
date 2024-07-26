#include "scene.h"
#include "solution.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QMessageBox>

Scene::Scene(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("View");
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    sceneLayout = new QVBoxLayout(this);
    sceneLayout->addWidget(view);

    resultLabel = new QLabel(this);
    solutionBtn = new QPushButton("Найти", this);
    sceneLayout->addWidget(solutionBtn);
    sceneLayout->addWidget(resultLabel);
    setLayout(sceneLayout);

    connect(solutionBtn, &QPushButton::clicked, this, &Scene::onSolutionBtnClicked);
}

Scene::~Scene() {}

void Scene::onSolutionBtnClicked()
{
    Solution solution;
    int waterTrapped = solution.trapRainWater(matrix);
    resultLabel->setText("Количество воды: " + QString::number(waterTrapped));
}

void Scene::draw(const QVector<QVector<int>>& matrix)
{
    scene->clear();

    // Сохраняем матрицу
    this->matrix = matrix;

    // Дефолтный размер каждой ячейки (квадрата)
    int rectSize = 50;

    for (int row = 0; row < matrix.size(); ++row) {
        for (int col = 0; col < matrix[row].size(); ++col) {
            int value = matrix[row][col];

            QGraphicsRectItem* rectItem = new QGraphicsRectItem(col * rectSize, row * rectSize, rectSize, rectSize);
            rectItem->setBrush(Qt::white);
            rectItem->setPen(QPen(Qt::black));
            scene->addItem(rectItem);

            QGraphicsTextItem* textItem = new QGraphicsTextItem(QString::number(value));
            textItem->setDefaultTextColor(Qt::black);
            textItem->setFont(QFont("Arial", 14));
            textItem->setPos(col * rectSize + rectSize / 2 - textItem->boundingRect().width() / 2,
                             row * rectSize + rectSize / 2 - textItem->boundingRect().height() / 2);

            scene->addItem(textItem);
        }
    }
}
