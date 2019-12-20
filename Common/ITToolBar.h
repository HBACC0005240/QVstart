#ifndef ITToolBar_H
#define ITToolBar_H

#include <QToolBar>
#include <QToolButton>
class ITToolBar : public QToolBar
{
	Q_OBJECT

public:
	explicit ITToolBar(const QString &title, QWidget *parent = 0);
	explicit ITToolBar(QWidget *parent = 0);

	~ITToolBar();

private:
};

class ITToolButton : public QToolButton
{
	Q_OBJECT

public:
	explicit ITToolButton(const QString &title, const QString &Icon,QWidget *parent = 0);

	~ITToolButton();

private:
	QFontMetrics* m_fmTitle;

};

#endif // ITToolBar_H
