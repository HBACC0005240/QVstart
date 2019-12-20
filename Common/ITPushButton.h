/**
* @文件名   push_button.h
* @版本信息 copyright  2012-2013 Sugon. All rights reserved.
* @功能描述
*           ITPushButton类包含最小化、最大化、关闭、主菜单等按钮的特效
* @作者     王亮<wangliang@sugon.com>
* @日期     2012-01-06
*/

#ifndef CS_CSVIEW_ITPushButton_H
#define CS_CSVIEW_ITPushButton_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
/**
* @功能描述   主要设置按钮样式、特效
* @作者  王亮 <wangliang@sugon.com>
**/

enum ITButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};

class ITPushButton : public QPushButton
{
	Q_OBJECT

public:

	/**
	*
	* 功能说明
	*    构造函数
	*
	* 参数说明
	*     QWidget *parent = 0    父窗体
	*
	* 返回值
	*     无
	*
	*/
	explicit ITPushButton(QWidget *parent = 0);

	/**
	*
	* 功能说明
	*    析构函数
	*
	* 参数说明
	*     无
	*
	* 返回值
	*     无
	*
	*/
	~ITPushButton();

	/**
	*
	* 功能说明
	*	 加载图标
	*
	* 参数说明
	*     QString pic_name 图标名称
	*
	* 返回值
	*     无
	*
	*/
	void loadPixmap(QString pic_name);

	void CheckButtonState();

	void setBtnEnable(bool bStatus);
protected:

	/**
	*
	* 功能说明
	*    鼠标移进事件
	*
	* 参数说明
	*     QEvent * event    事件
	*
	* 返回值
	*     无
	*
	*/
	void enterEvent(QEvent *);

	/**
	*
	* 功能说明
	*     鼠标移出事件
	*
	* 参数说明
	*     QEvent * event    事件
	*
	* 返回值
	*     无
	*
	*/
	void leaveEvent(QEvent *);

	/**
	*
	* 功能说明
	*     鼠标按下事件
	*
	* 参数说明
	*     QMouseEvent *event    鼠标事件
	*
	* 返回值
	*     无
	*
	*/
	void mousePressEvent(QMouseEvent *event);

	/**
	*
	* 功能说明
	*     鼠标释放事件
	*
	* 参数说明
	*     QMouseEvent *event    鼠标事件
	*
	* 返回值
	*     无
	*
	*/
	void mouseReleaseEvent(QMouseEvent *event);

	/**
	*
	* 功能说明
	*     绘图事件
	*
	* 参数说明
	*     QPaintEvent * event    绘图事件
	*
	* 返回值
	*     无
	*
	*/
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
