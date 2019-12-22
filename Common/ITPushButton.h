/**
*  ITPushButton�������С������󻯡��رա����˵��Ȱ�ť����Ч
*/

#ifndef CS_CSVIEW_ITPushButton_H
#define CS_CSVIEW_ITPushButton_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
/**
* ��Ҫ���ð�ť��ʽ����Ч
**/

enum ITButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};

class ITPushButton : public QPushButton
{
	Q_OBJECT

public:	
	explicit ITPushButton(QWidget *parent = 0);	
	~ITPushButton();

	/**
	*	 ����ͼ��	QString pic_name ͼ������	
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

	//ö�ٰ�ť�ļ���״̬

	ITButtonStatus status;
	QPixmap pixmap; 

	int btn_width; //��ť���
	int btn_height; //��ť�߶�
	bool mouse_press; //��ť����Ƿ���

	QPoint PosPress;  //���µ���������
	QPoint PosBtnPress;   //���µ����λ�ô�PUSHBUTTON������
	int widthPress;   //���µ����λ�ô�PUSHBUTTON ���
	int heighPress;   //���µ����λ�ô�PUSHBUTTON �߶�
	QPoint PosRealese;
};

#endif //CS_CSVIEW_ITPushButton_H
