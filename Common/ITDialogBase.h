/*************************************************
 //  ������ק�ƶ�����ק���Ŵ�С��ITDialogBase����
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
	bool m_isMove;	//��¼��굱ǰ״̬�Ƿ�Ϊ�ƶ�
	bool m_isMoveAble;	//���ô����Ƿ�����ƶ�����
	bool m_isResizeAble;	//������С����
	QPoint m_dragPoint;
	QPoint m_dragPosition;   
	Direction m_dir;
	QWidget* m_pTitleWid;

};

#endif // ITDialogBase_H
