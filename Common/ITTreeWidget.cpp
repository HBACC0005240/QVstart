#include "ITTreeWidget.h"
#include <QAction>

ITTreeWidget::ITTreeWidget(QWidget* parent)
	: QTreeWidget(parent)
	, m_pacSelectAll(new QAction(QStringLiteral("全部勾选"), this))
	, m_pacDeSelectAll(new QAction(QStringLiteral("全部取消"), this))
	, m_pacExpandAll(new QAction(QStringLiteral("全部展开"), this))
	, m_pacCollapseAll(new QAction(QStringLiteral("全部折叠"), this))
{
	setHeaderHidden(true);
	setDragEnabled(false);
	setContextMenuPolicy(Qt::ActionsContextMenu);
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	addAction(m_pacSelectAll);
	addAction(m_pacDeSelectAll);
	addAction(m_pacExpandAll);
	addAction(m_pacCollapseAll);

	connect(this, &ITTreeWidget::itemChanged, this, &ITTreeWidget::slotItemChanged);
	connect(m_pacSelectAll, &QAction::triggered, this, &ITTreeWidget::slotSelectAll);
	connect(m_pacDeSelectAll, &QAction::triggered, this, &ITTreeWidget::slotDeSelectAll);
	connect(m_pacExpandAll, &QAction::triggered, this, &ITTreeWidget::slotExpandAll);
	connect(m_pacCollapseAll, &QAction::triggered, this, &ITTreeWidget::slotCollapseAll);

}

ITTreeWidget::~ITTreeWidget()
{
}

void ITTreeWidget::checkedAll()
{
	for each(QTreeWidgetItem* item in m_pRootList)
	{
		item->setCheckState(0, Qt::Checked);
		updateChildren(item);
	}
}

void ITTreeWidget::unCheckedAll()
{
	for each(QTreeWidgetItem* item in m_pRootList)
	{
		item->setCheckState(0, Qt::Unchecked);
		updateChildren(item);
	}
}

void ITTreeWidget::buildTree(const QVector<ItemData>& dataVec, Qt::CheckState state)
{
	blockSignals(true);
	QTreeWidgetItem* topItem = nullptr;
	for each (ItemData data in dataVec)
	{
		topItem = new QTreeWidgetItem;
		addTopLevelItem(topItem);

		topItem->setText(0, data.Name);
		topItem->setData(0, Qt::UserRole, data.ID);
		topItem->setCheckState(0, state);
		buildTree(topItem, data.Children);
		m_pRootList.append(topItem);
	}
	blockSignals(false);
}

void ITTreeWidget::buildTree(QTreeWidgetItem* itemGroup, const QVector<ItemData>& dataVec)
{
	for each(ItemData data in dataVec)
	{
		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setText(0, data.Name);
		if (data.ID != -1)//节点中没有id时，将其设为-1
		{
			item->setData(0, Qt::UserRole, data.ID);
		}
		else
		{
			item->setData(0, Qt::UserRole, data.UserData);
		}
		item->setCheckState(0, itemGroup->checkState(0));
		itemGroup->addChild(item);
		if (!data.Children.isEmpty())
		{
			buildTree(item, data.Children);
		}
	}
}

void ITTreeWidget::getItemChildID(QTreeWidgetItem* itemParent, QSet<size_t>& childIDSet)
{
	int count = itemParent->childCount();
	for (int i = 0; i < count; i++)
	{
		QTreeWidgetItem* item = itemParent->child(i);
		if (item->checkState(0) == Qt::Checked)
		{
			QString strName = item->text(0);
			size_t theID = item->data(0, Qt::UserRole).toULongLong();
			childIDSet.insert(theID);
		}
		getItemChildID(item, childIDSet);
	}
}

void ITTreeWidget::slotItemChanged(QTreeWidgetItem* item, int column)
{
	blockSignals(true);
	updateChildren(item);
	updateParents(item);
	blockSignals(false);
	emit itemCheckedChange(getCheckedIDSet());
}

void ITTreeWidget::slotSelectAll()
{
	checkedAll();
}

void ITTreeWidget::slotDeSelectAll()
{
	unCheckedAll();
}

void ITTreeWidget::slotExpandAll()
{
	expandAll();
}

void ITTreeWidget::slotCollapseAll()
{
	collapseAll();
}

void ITTreeWidget::itemChecked(QTreeWidgetItem* itemParent, QSet<size_t>& ids)
{
	int count = itemParent->childCount();
	for (int i = 0; i < count; i++)
	{
		QTreeWidgetItem* item = itemParent->child(i);
		size_t theID = item->data(0, Qt::UserRole).toULongLong();
		ids.contains(theID) ? item->setCheckState(0, Qt::Checked)
			: item->setCheckState(0, Qt::Unchecked);
		itemChecked(item, ids);
	}
}

QSet<size_t> ITTreeWidget::getLeafIDs()
{
	QSet<size_t> idSet;
	for each (QTreeWidgetItem* itemRoot in m_pRootList)
	{
		getItemChildID(itemRoot, idSet);
	}
	return idSet;
}

QSet<size_t> ITTreeWidget::getCheckedIDSet()
{
	QSet<size_t> idSet;
	for each (QTreeWidgetItem* itemRoot in m_pRootList)
	{
		int count = itemRoot->childCount();
		if (count > 0)
		{
			getItemChildID(itemRoot, idSet);
		}
		else
		{
			if (itemRoot->checkState(0) == Qt::Checked)
			{
				size_t theID = itemRoot->data(0, Qt::UserRole).toULongLong();
				idSet.insert(theID);
			}
		}
	}
	return idSet;
}

void ITTreeWidget::setCheckedID(QSet<size_t>& ids)
{
	for each (QTreeWidgetItem* itemRoot in m_pRootList)
	{
		int count = itemRoot->childCount();
		if (count > 0)
		{
			itemChecked(itemRoot, ids);
		}
		else
		{
			size_t theID = itemRoot->data(0, Qt::UserRole).toULongLong();
			ids.contains(theID) ? itemRoot->setCheckState(0, Qt::Checked)
				: itemRoot->setCheckState(0, Qt::Unchecked);
		}
	}
}

void ITTreeWidget::clear()
{
	QTreeWidget::clear();
	m_pRootList.clear();
	m_checkedIdSet.clear();
}

void ITTreeWidget::updateParents(QTreeWidgetItem* item)
{
	QTreeWidgetItem *parent = item->parent();
	if (parent)
	{
		int checkedCount = 0;
		int patiallyCount = 0;
		int itemCount = parent->childCount();
		for (int i = 0; i < itemCount; i++)
		{
			QTreeWidgetItem *item = parent->child(i);
			if (Qt::Checked == item->checkState(0))
				checkedCount++;
			else if (Qt::PartiallyChecked == item->checkState(0))
				patiallyCount++;
		}

		if (checkedCount <= 0)
		{
			if (patiallyCount > 0)
				goto Partially;
			else
			{
				parent->setCheckState(0, Qt::Unchecked);
			}
		}
		else if (checkedCount > 0 && checkedCount < itemCount)
		{
		Partially:
			parent->setCheckState(0, Qt::PartiallyChecked);
			setParentsPartiallyChecked(parent);
			return;
		}
		else if (checkedCount > 0 && checkedCount == itemCount)
		{
			parent->setCheckState(0, Qt::Checked);
		}
		updateParents(parent);
	}

}

void ITTreeWidget::updateChildren(QTreeWidgetItem* item)
{
	int childCount = item->childCount();
	if (childCount > 0)
	{
		for (int i = 0; i < childCount; i++)
		{
			item->child(i)->setCheckState(0, item->checkState(0));
			if (item->child(i)->childCount() > 0)
				updateChildren(item->child(i));
		}
	}

}

void ITTreeWidget::setParentsPartiallyChecked(QTreeWidgetItem* item)
{
	QTreeWidgetItem *parent = item->parent();
	if (parent)
	{
		parent->setCheckState(0, Qt::PartiallyChecked);
		setParentsPartiallyChecked(parent);
	}
}
