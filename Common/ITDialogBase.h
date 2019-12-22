/*************************************************
 //  可以拖拽移动和拖拽缩放大小的ITDialogBase基类
 *************************************************/
#ifndef ITDialogBase_H
#define ITDialogBase_H

#include <QDialog>
#include <QMouseEvent>
#include <QLayout>
#include <QGridLayout>

#define PADDING 4

class ITDialogBase : public QDialog
{
	Q_OBJECT

public:
	ITDialogBase( QWidget *parent=0);
	~ITDialogBase();

	enum Direction 
	{ 
		UP = 0, 
		DOWN = 1, 
		LEFT, 
		RIGHT, 
		LEFTTOP, 
		LEFTBOTTOM, 
		RIGHTBOTTOM, 
		RIGHTTOP, 
		NONE
	};

	void setMoveEanable(bool isMove = true);

protected:
	virtual void mousePressEvent(QMouseEvent* e);
	virtual void mouseMoveEvent(QMouseEvent* e);
	virtual void mouseReleaseEvent(QMouseEvent* e);
	virtual void keyPressEvent(QKeyEvent * e);

private:
	void region(const QPoint &cursorGlobalPoint);

	virtual void leaveEvent(QEvent *);

	void initTitle();

private:
	bool m_isMove;	//记录鼠标当前状态是否为移动
	bool m_isMoveAble;	//设置窗口是否具有移动功能
	bool m_isResizeAble;	//调整大小功能
	QPoint m_dragPoint;
	QPoint m_dragPosition;   
	Direction m_dir;
	QWidget* m_pTitleWid;

};

#endif // ITDialogBase_H
