/**
* @�ļ���   push_button.h
* @�汾��Ϣ copyright  2012-2013 Sugon. All rights reserved.
* @��������
*           ITPushButton�������С������󻯡��رա����˵��Ȱ�ť����Ч
* @����     ����<wangliang@sugon.com>
* @����     2012-01-06
*/

#ifndef CS_CSVIEW_ITPushButton_H
#define CS_CSVIEW_ITPushButton_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
/**
* @��������   ��Ҫ���ð�ť��ʽ����Ч
* @����  ���� <wangliang@sugon.com>
**/

enum ITButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};

class ITPushButton : public QPushButton
{
	Q_OBJECT

public:

	/**
	*
	* ����˵��
	*    ���캯��
	*
	* ����˵��
	*     QWidget *parent = 0    ������
	*
	* ����ֵ
	*     ��
	*
	*/
	explicit ITPushButton(QWidget *parent = 0);

	/**
	*
	* ����˵��
	*    ��������
	*
	* ����˵��
	*     ��
	*
	* ����ֵ
	*     ��
	*
	*/
	~ITPushButton();

	/**
	*
	* ����˵��
	*	 ����ͼ��
	*
	* ����˵��
	*     QString pic_name ͼ������
	*
	* ����ֵ
	*     ��
	*
	*/
	void loadPixmap(QString pic_name);

	void CheckButtonState();

	void setBtnEnable(bool bStatus);
protected:

	/**
	*
	* ����˵��
	*    ����ƽ��¼�
	*
	* ����˵��
	*     QEvent * event    �¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void enterEvent(QEvent *);

	/**
	*
	* ����˵��
	*     ����Ƴ��¼�
	*
	* ����˵��
	*     QEvent * event    �¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void leaveEvent(QEvent *);

	/**
	*
	* ����˵��
	*     ��갴���¼�
	*
	* ����˵��
	*     QMouseEvent *event    ����¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void mousePressEvent(QMouseEvent *event);

	/**
	*
	* ����˵��
	*     ����ͷ��¼�
	*
	* ����˵��
	*     QMouseEvent *event    ����¼�
	*
	* ����ֵ
	*     ��
	*
	*/
	void mouseReleaseEvent(QMouseEvent *event);

	/**
	*
	* ����˵��
	*     ��ͼ�¼�
	*
	* ����˵��
	*     QPaintEvent * event    ��ͼ�¼�
	*
	* ����ֵ
	*     ��
	*
	*/
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
