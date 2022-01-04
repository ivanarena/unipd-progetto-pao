#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class DataTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DataTableModel(QObject *parent = 0); // overwrite necessario per definizione
    DataTableModel(QObject *parent, bool blank); // overwrite necessario per definizione

    int rowCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione
    int columnCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // overwrite necessario per definizione
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);

private:
    // Da sostituire con std::vector
    QVector<QVector<qreal> *> m_data; //  vettori di vettori (?)
    QVector<QVector<qreal> *> m_headerData;
    int m_rowCount;
    int m_columnCount;
};

#endif // MODEL_H
