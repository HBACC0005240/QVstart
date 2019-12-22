#ifndef ITMQUERYLINEEDIT_H
#define ITMQUERYLINEEDIT_H

#include <QLineEdit>
#include "Global.h"
#include "ITPushButton.h"

class ITQueryLineEdit :public QLineEdit
{
	Q_OBJECT
public:
	ITQueryLineEdit(QWidget* parent);
	~ITQueryLineEdit(void);
signals:
	void signalQuery();
	void signalClear();
private slots:
	void onSendQuery();
	void onSendClear();

private:
    ITPushButton* m_pBtnQuery;
    ITPushButton* m_pBtnClear;
};

#endif // ITMQUERYLINEEDIT_H
