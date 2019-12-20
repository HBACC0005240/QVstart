#ifndef _ITProgressBar_H
#define _ITProgressBar_H

#include <QProgressBar>

#define  CTotalSteps  100  //���������µĲ���


class ITProgressBar :public QProgressBar
{
  Q_OBJECT   
public:
    ITProgressBar(QWidget * parent = 0, int minRange = 0, int maxRange = 30, int nWidth = 450, int nHeight = 30);
	virtual ~ITProgressBar();

	//ע�⣬��Ҫ���̵߳���
	Q_INVOKABLE void UpdateProgress(int APos);
	Q_INVOKABLE void GotoNextPos();
	Q_INVOKABLE void GotoNextStep();   //ǰ��һ��
	Q_INVOKABLE void UpdatePrompt(QString qsText);
	Q_INVOKABLE void SetMaxRange(int maxRange);
	Q_INVOKABLE void ShowImmediately();        //��ʾ������(����ˢ�²�������ֹ������������)
	int getMaxRange() { return m_nMaxRange; }
	int getCurPos() { return m_nCurrentPos * CTotalSteps / m_nMaxRange; }

protected:
	virtual void showEvent(QShowEvent *e) override;
	virtual void hideEvent(QHideEvent *e) override;

private:
	int m_nOneStepValue;
	int m_nCurrentStep;
	int m_nCurrentPos;
	int m_nCount;
	int m_nMaxRange;
};

#endif