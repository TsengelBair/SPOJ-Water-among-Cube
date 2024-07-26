#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVector>

class Scene : public QWidget
{
    Q_OBJECT
public:
    Scene(QWidget* parent = nullptr);
    ~Scene();

    void draw(const QVector<QVector<int>>& matrix);

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QVBoxLayout* sceneLayout;
    QPushButton* solutionBtn;
    QLabel* resultLabel;

    QVector<QVector<int>> matrix;

private slots:
    void onSolutionBtnClicked();
};

#endif // SCENE_H
