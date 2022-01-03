#include "model.h"

DataTableModel::DataTableModel(QObject* parent) : QAbstractTableModel(parent) {

    _rowCount = 5;
    _columnCount = 6;

    // _data init
    for (int i = 0; i < _rowCount; i++) // righe vettori grandi n colonne
    {
        QVector<qreal> *dataVector = new QVector<qreal>(_columnCount); // vettore grande x colonne
        for (int k = 0; k < dataVector->size(); k++) {
            dataVector->replace(k, (k+1)*i);
        }
        _data.append(dataVector); // appendi alla lista di vettori
    }
}

DataTableModel::DataTableModel(QObject* parent, bool blank) : QAbstractTableModel(parent) {

    if (blank)
    {
        _rowCount = 3;
        _columnCount = 3;

        // _data init
        for (int i = 0; i < _rowCount; i++) // righe vettori grandi n colonne
        {
            QVector<qreal> *dataVector = new QVector<qreal>(_columnCount); // vettore grande x colonne
            for (int k = 0; k < dataVector->size(); k++) {
                dataVector->replace(k, 0);
            }
            _data.append(dataVector); // appendi alla lista di vettori
        }

    }
    else
    {
        DataTableModel(parent);
    }


}

int DataTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent) // parent non è usato -- evita compilazioni inutili
    return _rowCount;
}

int DataTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent) // parent non è usato -- evita compilazioni inutili
    return _columnCount;
}

QVariant DataTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return _data[index.row()]->at(index.column()); // gets x,y
    }
    return QVariant();
}

QVariant DataTableModel::headerData(int section, Qt::Orientation orientation, int role) const // edit header data
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) { // column headers
        return QString("%1").arg(section + 1);
    } else { // Qt::Vertical -- rows headers
        return QString("%1").arg(section + 1);
    }
}

Qt::ItemFlags DataTableModel::flags(const QModelIndex &index) const // rende modificabili le celle
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool DataTableModel::setData(const QModelIndex &index, const QVariant &value, int role) // modifica effettivamente le celle
{
    if (index.isValid() && role == Qt::EditRole) {
        _data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool setHeaderData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole)
{
    return false;
}



/******** CONTINUA A BUILDARE *********/
