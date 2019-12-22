/**
*  ITPushButton类包含最小化、最大化、关闭、主菜单等按钮的特效
*/

#ifndef CS_CSVIEW_ITPushButton_H
#define CS_CSVIEW_ITPushButton_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
/**
* 主要设置按钮样式、特效
**/

enum ITButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};

class ITPushButton : public QPushButton
{
	Q_OBJECT

public:	
	explicit ITPushButton(QWidget *parent = 0);	
	~ITPushButton();

	/**
	*	 加载图标	QString pic_name 图标名称	
	*/
	void loadPixmap(QString pic_name);

	void CheckButtonState();

	void setBtnEnable(bool bStatus);
protected:

	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);	
	void paintEvent(QPaintEvent *);

private:

	//枚举按钮的几种状态

	ITButtonStatus status;
	QPixmap pixmap; 

	int btn_width; //按钮宽度
	int btn_height; //按钮高度
	bool mouse_press; //按钮左键是否按下

	QPoint PosPress;  //按下的鼠标点坐标
	QPoint PosBtnPress;   //按下的鼠标位置处PUSHBUTTON的坐标
	int widthPress;   //按下的鼠标位置处PUSHBUTTON 宽度
	int heighPress;   //按下的鼠标位置处PUSHBUTTON 高度
	QPoint PosRealese;
};

#endif //CS_CSVIEW_ITPushButton_H
