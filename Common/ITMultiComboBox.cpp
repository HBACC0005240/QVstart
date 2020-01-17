#include "stdafx.h"
#include "ITMultiComboBox.h"

ITMultiComboBox::ITMultiComboBox(QWidget *parent)
	: QComboBox(parent)
{
	m_pListWidget = new QListWidget(this);
	m_pListWidget->setFixedHeight(220);
	m_pLineEdit = new QLineEdit(this);
	m_pLineEdit->setFixedHeight(20);
	m_pLineEdit->setContentsMargins(0,2,0,2);
	m_pLineEdit->setReadOnly(true);

	setFixedWidth(150);
	setFixedHeight(22);
	setModel(m_pListWidget->model());
	setView(m_pListWidget);
	setLineEdit(m_pLineEdit);
	connect(m_pLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));
}

void ITMultiComboBox::stateChanged(int state)
{
	m_bSelect = true;
	m_sSelectedText.clear();

	for (int i = 0; i < m_pListWidget->count(); ++i)
	{
		QListWidgetItem *pItem = m_pListWidget->item(i);
		if (Qt::Checked == pItem->checkState())
		{
			QString strText = pItem->text();
			m_sSelectedText.append(strText).append(";");
		}
	}
	if (m_sSelectedText.endsWith(";"))
		m_sSelectedText.remove(m_sSelectedText.count() - 1, 1);
	m_pLineEdit->setText(m_sSelectedText);
	m_pLineEdit->setToolTip(m_sSelectedText);

	m_bSelect = false;
	emit signalStateChanged(state);
}

ITMultiComboBox::~ITMultiComboBox()
{}

void ITMultiComboBox::addItem(QVariant value,QString sText,bool bCheck)
{
	QListWidgetItem *pItem = new QListWidgetItem(sText, m_pListWidget);
	pItem->setSizeHint(QSize(22,22));
	pItem->setData(Qt::UserRole+1, value);
	pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
	pItem->setCheckState(true == bCheck ? Qt::Checked : Qt::Unchecked);
	m_pListWidget->addItem(pItem);
	m_pLineEdit->clear();
	stateChanged(bCheck);
}

QString ITMultiComboBox::selectText()
{
	return m_sSelectedText;
}

QVector<QVariant>& ITMultiComboBox::selectValue()
{
	m_vecSelect.clear();
	for (int i = 0; i < m_pListWidget->count(); ++i)
	{
		QListWidgetItem *pItem = m_pListWidget->item(i);
		if (Qt::Checked == pItem->checkState())
		{
			QVariant nData = pItem->data(Qt::UserRole + 1);
			m_vecSelect.push_back(nData);
		}
	}
	return m_vecSelect;
}

void ITMultiComboBox::textChanged(const QString &text)
{
	if (!m_bSelect)
		m_pLineEdit->setText(m_sSelectedText);
}

void ITMultiComboBox::hidePopup()
{
	int x = QCursor::pos().x() - mapToGlobal(geometry().topLeft()).x() + geometry().x();
	int y = QCursor::pos().y() - mapToGlobal(geometry().topLeft()).y() + geometry().y();
	if (x >= 0 && x <= width() && y > height())
	{
		int row = view()->selectionModel()->currentIndex().row();
		QListWidgetItem* item = m_pListWidget->item(row);
		if (nullptr != item)
		{
			if (Qt::Checked == item->checkState())
			{
				item->setCheckState(Qt::Unchecked);
				stateChanged(Qt::Unchecked);
			}
			else
			{
				item->setCheckState(Qt::Checked);
				stateChanged(Qt::Checked);
			}
		}
	}
	else
	{
		QComboBox::hidePopup();
	}
}

void ITMultiComboBox::clear()
{
	m_pListWidget->clear();
	m_pLineEdit->clear();
	m_sSelectedText.clear();
	m_vecSelect.clear();
	stateChanged(0);
}

QVector<QVariant> ITMultiComboBox::getVecSelect()
{
	return m_vecSelect;
}
