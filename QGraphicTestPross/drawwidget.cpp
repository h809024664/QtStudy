#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent)
    : QWidget{parent}
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    pix = new QPixmap(size());
    pix->fill(Qt::white);

    setMouseTracking(true);

    setMinimumSize(600,400);
}

void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    startpos = e->pos();
}

void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(!(e->buttons() & Qt::LeftButton))
        return;

    QPainter painter;
    QPen pen;
    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(widthss);
    pen.setColor(color);

    painter.begin(pix);
    painter.setPen(pen);
    painter.drawLine(startpos,e->pos());

    startpos = e->pos();
    update();

}

void DrawWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.drawPixmap(QPoint(0,0),*pix);
}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    if(height()> pix->height() || width()>pix->width() )
    {
        QPixmap *newPix = new QPixmap(size());
        newPix->fill(Qt::white);

        QPainter ps(newPix);
        ps.drawPixmap(QPoint(0,0),*pix);
        pix = newPix;
    }
    QWidget::resizeEvent(event);
}

void DrawWidget::setStyle(int s)
{
    style = s;
}

void DrawWidget::setWidth(int w)
{
    widthss = w;
}

void DrawWidget::setColor(QColor c)
{
    color = c;
}

void DrawWidget::clearFunc()
{
    QPixmap *cPix = new QPixmap(size());
    cPix->fill(Qt::white);
    pix = cPix;
    update();
}
