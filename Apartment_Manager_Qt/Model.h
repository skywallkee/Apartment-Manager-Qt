#include <QAbstractTableModel>
#include <QFont>
#include <QBrush>
#include <vector>
#include "Locatar.h"
#pragma once

class Model : public QAbstractTableModel {
	Q_OBJECT;
	std::vector<Locatar> l;
	std::vector<int> sortat;
	std::map<int, QColor> map;
public:
	Model(const std::vector<Locatar>& v, QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				if (section == 0) {
					return QString("Apartament");
				}
				else if (section == 1) {
					return QString("Nume");
				}
				else if (section == 2) {
					return QString("Tip apartament");
				}
				else if (section == 3) {
					return QString("Suprafata (m^2)");
				}
				//return QVariant();
			}
			//return QVariant();
		}
		return QVariant();
	}
	void timerTikTak(std::vector<Locatar>& v); 
};