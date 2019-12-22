#pragma once
#include <QTreeWidget>

struct ItemData
{
	size_t ID;
	QString Name;
	QString UserData;
	QVector<ItemData> Children;

	ItemData()
	{
		ID = 0;
		Name = "";
		UserData = "";
		Children.clear();
	}
	ItemData(size_t id, QString name)
	{
		ID = id;
		Name = name;
		UserData = "";
		Children.clear();
	}
};

class ITTreeWidget : public QTreeWidget
{
	Q_OBJECT
	
public:
	ITTreeWidget(QWidget* parent);
	~ITTreeWidget();

	void checkedAll();

	void unCheckedAll();

	void buildTree(const QVector<ItemData>& dataVec, Qt::CheckState state = Qt::Unchecked);

	QSet<size_t> getLeafIDs();
	QSet<size_t> getCheckedIDSet();
	void setCheckedID(QSet<size_t>& ids);

	void clear();

private slots:
	void slotItemChanged(QTreeWidgetItem* item, int column);
	void slotSelectAll();
	void slotDeSelectAll();
	void slotExpandAll();
	void slotCollapseAll();

signals:
	void itemCheckedChange(const QSet<size_t>& floorIDs);

private:
	void updateParents(QTreeWidgetItem* item);
	void updateChildren(QTreeWidgetItem* item);
	void buildTree(QTreeWidgetItem* itemGroup, const QVector<ItemData>& dataVec);
	void getItemChildID(QTreeWidgetItem* item, QSet<size_t>& childIDSet);
	void itemChecked(QTreeWidgetItem* item, QSet<size_t>& ids);

	void setParentsPartiallyChecked(QTreeWidgetItem* item);

protected:
	QList<QTreeWidgetItem*> m_pRootList;
	QAction* m_pacSelectAll;
	QAction* m_pacDeSelectAll;
	QAction* m_pacExpandAll;
	QAction* m_pacCollapseAll;
	QSet<size_t> m_checkedIdSet;
};
