#include "stdafx.h"
#include "ITPushButton.h"

ITPushButton::ITPushButton(QWidget *parent)
	:QPushButton(parent)
{	
	status = NORMAL;
	mouse_press = false;
}

ITPushButton::~ITPushButton()
{

}


void ITPushButton::loadPixmap(QString pic_name)
{
	pixmap.load(pic_name);
	btn_width = pixmap.width()/4;
	btn_height = pixmap.height();
	setFixedSize(btn_width, btn_height);
}

void ITPushButton::CheckButtonState()
{
	if (status != NOSTATUS)
	{
		QPoint pt = mapFromGlobal(QCursor::pos());
		if (pt.x() < 0 || pt.x() > width() || pt.y() < 0 || pt.y() > height())
		{
			status = NORMAL;
		}
		else
		{
			status = ENTER;
		}
		update();
	}	
}

void ITPushButton::setBtnEnable(bool bStatus)
{
	if (!bStatus)
	{
		status = NOSTATUS;
		setEnabled(bStatus);
		update();
	}
	else
	{
		status = NORMAL;
		setEnabled(bStatus);
		update();
	}
}
void ITPushButton::enterEvent(QEvent *)
{
	if (status != NOSTATUS)
	{
		status = ENTER;
		update();
	}
}

void ITPushButton::mousePressEvent(QMouseEvent *event)
{
	if (status != NOSTATUS)
	{
		if(event->button() == Qt::LeftButton)
		{
			mouse_press = true;
			status = PRESS;
			PosPress.rx() = event->pos().rx()+this->pos().rx();
			PosPress.ry() = event->pos().ry()+this->pos().ry();
			PosBtnPress = this->pos();
			widthPress = this->width();
			heighPress =  this->height();
			update();
		}
	}
	//Èôµã»÷Êó±ê×ó¼ü

}

void ITPushButton::mouseReleaseEvent(QMouseEvent *event)
{
	if (status != NOSTATUS)
	{
		if(mouse_press)
		{
			mouse_press = false;
			status = ENTER;
			PosRealese.rx() = event->pos().rx()+this->pos().rx();
			PosRealese.ry() = event->pos().ry()+this->pos().ry();

			if ((PosRealese.rx()>=PosBtnPress.rx())&&(PosRealese.rx()<=PosBtnPress.rx()+widthPress)
				&&(PosRealese.ry()>=PosBtnPress.ry())&&(PosRealese.ry()<=PosBtnPress.ry()+heighPress))
			{
				emit clicked();
			}
			update();
			//emit clicked();
		}
	}
	//Èôµã»÷Êó±ê×ó¼ü
}

void ITPushButton::leaveEvent(QEvent *)
{
	if (status != NOSTATUS)
	{
		status = NORMAL;
		update();
	}

}

void ITPushButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));
}
