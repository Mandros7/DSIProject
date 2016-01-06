#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

namespace Ui {
class GUI;
}

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUI(QWidget *parent = 0);
    ~GUI();

private slots:
    void setKp1();
    void setRef1();
    void actualizarTablasLazo1();
    void setKp2();
    void setRef2();
    void actualizarTablasLazo2();


private:
    Ui::GUI *ui;
};

#endif // GUI_H
