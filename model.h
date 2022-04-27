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

    //friend void JsonParser::save(DataTableModel*, QFile&) const;
    explicit DataTableModel();
    explicit DataTableModel(int c_rows, int c_cols, QObject *parent); // overwrite necessario per definizione
    explicit DataTableModel(QObject *parent, int, int, const vector<vector<double>>&, const vector<QVariant>&, const vector<QVariant>&);
    DataTableModel(const DataTableModel& model);

    bool isEmpty() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione
    int columnCount(const QModelIndex &parent = QModelIndex()) const; // overwrite necessario per definizione

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // overwrite necessario per definizione
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole);

    void insertRow(const QString &, double);
    void removeRow();
    void insertColumn(const QString&, double);
    void removeColumn();
    void insertRowAndColumn(const QString&, const QString&, double); // only if 0 rows 0 cols

    double max();
    double min();

    vector<vector<double>> getData() const;
    vector<QVariant> getRowsHeaders() const;
    vector<QVariant> getColumnsHeaders() const;
    static bool is_number(const std::string& s);

private:
    int m_rowCount;
    int m_columnCount;
    vector<vector<double>> m_data;
    vector<QVariant> m_columnsHeaderData;
    vector<QVariant> m_rowsHeaderData;
    bool empty;
};

#endif // MODEL_H
