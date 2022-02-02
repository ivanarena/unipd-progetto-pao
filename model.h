#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

using namespace std;

class DataTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DataTableModel(QObject *parent = 0, bool blank = 0); // overwrite necessario per definizione
    int rowCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione
    int columnCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // overwrite necessario per definizione
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    // NON SERVE A NULLA CREDO bool setHeaderData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

//    void addRow(); // FUNZIONA QUI MA NON SU VIEW (IL CONNECT NON VA)
//    void addColumn(); // same per tutte ^^
//    void removeRow();
//    void removeColumn();

private:
    // Da sostituire con std::vector
    vector<vector<double>> m_data; //  vettori di vettori (?)
    vector<vector<double>> m_headerData;
    int m_rowCount;
    int m_columnCount;
};

#endif // MODEL_H
