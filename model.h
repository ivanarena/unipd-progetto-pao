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

    DataTableModel(int c_rows = 4, int c_cols = 2, QObject *parent = 0); // overwrite necessario per definizione
    //explicit DataTableModel(QObject *parent, int, int, const vector<vector<double>>&, const vector<vector<string>>&);
    DataTableModel(const DataTableModel& model);

    int rowCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione
    int columnCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // overwrite necessario per definizione
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole);

    void insertRow();
    void removeRow();
    void insertColumn();
    void removeColumn();

    //double getXMax();
    //double getYMax();


    //vector<vector<double>> getValues();
    //vector<vector<string>> getHeaders();

private:
    vector<vector<double>> m_data;
    vector<QVariant> m_columnsHeaderData;
    vector<QVariant> m_rowsHeaderData;
    int m_rowCount;
    int m_columnCount;
};

#endif // MODEL_H
