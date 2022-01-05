#include "model.h"

DataTableModel::DataTableModel(QObject* parent) : QAbstractTableModel(parent)
{

    m_rowCount = 5;
    m_columnCount = 6;

    // _data init
    for (int i = 0; i < m_rowCount; i++) // righe vettori grandi n colonne
    {
        QVector<qreal> *dataVector = new QVector<qreal>(m_columnCount); // vettore grande x colonne
        for (int k = 0; k < dataVector->size(); k++) {
            dataVector->replace(k, (k+1)*i);
        }
        m_data.append(dataVector); // appendi alla lista di vettori
    }


}

DataTableModel::DataTableModel(QObject* parent, bool blank) : QAbstractTableModel(parent)
{

    if (blank)
    {
        m_rowCount = 3;
        m_columnCount = 3;

        // _data init
        for (int i = 0; i < m_rowCount; i++) // righe vettori grandi n colonne
        {
            QVector<qreal> *dataVector = new QVector<qreal>(m_columnCount); // vettore grande x colonne
            for (int k = 0; k < dataVector->size(); k++) {
                dataVector->replace(k, 0);
            }
            m_data.append(dataVector); // appendi alla lista di vettori
        }

    }
    else
    {
        DataTableModel(parent);
    }


}

int DataTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent) // parent non è usato -- evita compilazioni inutili
    return m_rowCount;
}

int DataTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent) // parent non è usato -- evita compilazioni inutili
    return m_columnCount;
}

QVariant DataTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_data[index.row()]->at(index.column()); // gets x,y
    }
    return QVariant();
}

QVariant DataTableModel::headerData(int section, Qt::Orientation orientation, int role) const // edit header data
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    { // column headers
        //return m_headerData[0]
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
    if (index.isValid() && role == Qt::EditRole)
    {
        m_data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool setHeaderData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole)
{
    if (role == Qt::EditRole)
    {

        return true;
    }
    return false;
}



/******** CONTINUA A BUILDARE *********/
