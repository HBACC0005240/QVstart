#pragma once
#include <QComboBox>
#include <QListWidget>

class ITMultiComboBox : public QComboBox
{
	Q_OBJECT

public:
	ITMultiComboBox(QWidget *parent);
	~ITMultiComboBox();

	void addItem(QVariant value,QString sText,bool bCheck = false);
	QString selectText();
	QVector<QVariant>& selectValue();
	
	// жиди
	void hidePopup();
	void clear();
	QVector<QVariant> getVecSelect();

private slots:
	void stateChanged(int state);
	void textChanged(const QString &text);

signals:
	void signalStateChanged(int state);

private:
	QListWidget*         m_pListWidget;
	QLineEdit*           m_pLineEdit;
	QString              m_sSelectedText;
	QVector<QVariant>    m_vecSelect;
	bool                 m_bSelect;
};