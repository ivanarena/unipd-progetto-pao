#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
//#include "parser.h"
//#include "jsonparser.h"

using namespace std;

class DataTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    //friend void JsonParser::save(DataTableModel*, QFile&) const;

    DataTableModel(int c_rows = 5, int c_cols = 6, QObject *parent = 0); // overwrite necessario per definizione
    explicit DataTableModel(QObject *parent, int, int, const vector<vector<double>>&, const vector<vector<string>>&);
    DataTableModel(const DataTableModel& model);

    int rowCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione
    int columnCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // overwrite necessario per definizione
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    // NON SERVE A NULLA CREDO bool setHeaderData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);

//    bool insertRows(int row, int count, const QModelIndex& parent);

    void insertRow(); // FUNZIONA!!!!!!!!!
//    void insertColumn(); // same per tutte ^^
//    void removeRow();
//    void removeColumn();
    vector<vector<double>> getValues();
    vector<vector<string>> getHeaders();

private:
    // Da sostituire con std::vector
    vector<vector<double>> m_data; //  vettori di vettori (?)
    vector<vector<string>> m_headerData;
    int m_rowCount;
    int m_columnCount;
};

#endif // MODEL_H
