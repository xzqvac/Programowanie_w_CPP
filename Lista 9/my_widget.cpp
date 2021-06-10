#include "my_widget.h"

#include <QPainter>
#include <QDebug>

MyWidget::MyWidget(QWidget* parent)  //
    : QWidget(parent), timer(this)
{
    timer.start(timer_interval);
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timer()));
}

void MyWidget::paintEvent(QPaintEvent* event)
{

     QPainter painter(this);

     QRadialGradient radialGrad(QPointF(35,75),15);
     radialGrad.setColorAt(0.1, Qt::magenta);
     radialGrad.setColorAt(0.7, QColor(211,211,211));
     painter.setBrush(QBrush(radialGrad));

    QLineF horizontalLine(rect().width() / 2.0 - 10, rect().height() / 2.0, rect().width() / 2.0 + 10, rect().height() / 2.0);
    painter.drawLine(horizontalLine);

    QLineF verticalLine(rect().width() / 2.0, rect().height() / 2.0 - 10, rect().width() / 2.0, rect().height() / 2.0 + 10);
    painter.drawLine(verticalLine);

    painter.translate(rect().width() / 2.0, rect().height() / 2.0);
    auto side = std::min(rect().width(), rect().height());
    painter.scale(side / 200.0, side / 200.0);
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < num_disks; i++)
    {
        if (i != hidden)
        {
            QRect rect(20,60,30,30);
            painter.fillRect(rect,radialGrad);
        }
        painter.rotate(360.0 / num_disks);
    }

}

void MyWidget::on_timer()
{
    hidden = (hidden + 1) % num_disks;
    update();
}

void MyWidget::toggle_animation()
{
    if (timer.isActive())
    {
        timer.stop();
    }
    else
        timer.start(timer_interval);
}
