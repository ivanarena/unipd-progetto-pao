#include "model.h"

using namespace std;

DataTableModel::DataTableModel(QObject* parent, bool blank) : QAbstractTableModel(parent)
{

    if (blank)
    {
        m_rowCount = 0;
        m_columnCount = 0;
    }
    else
    {
        m_rowCount = 5;
        m_columnCount = 6;

//        vector<vector<double> *> dataVector(m_rowCount, new vector<double>(m_columnCount, 0));
        for (int i = 0; i < m_rowCount; i++)
            m_data.push_back(vector<double>(m_columnCount, 0));

        /*
        // m_data init
        for (int i = 0; i < m_rowCount; i++) // righe vettori grandi n colonne
        {
            vector<double> *dataVector = new vector<double>(m_columnCount, 0); // vettore grande x colonne che punta a valori
            for (vector<double>::iterator k = dataVector->begin(); k < dataVector->end(); k++) {
                *k = (i+1)*i;
            }
//            m_data.insert(m_data.end(), dataVector->begin(), dataVector->end()); // appendi alla lista di vettori
            m_data.at(i) = dataVector; // appendi alla lista di vettori
        }*/

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
        return m_data[index.row()].at(index.column()); // gets x,y
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
        m_data[index.row()].at(index.column()) = value.toDouble();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

/*bool setHeaderData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole)
{
    if (role == Qt::EditRole)
    {

        return true;
    }
    return false;
}
MI SA CHE NON SERVE A NIENTE */

void DataTableModel::addRow()
{
    m_rowCount++;
    m_data.push_back(vector<double>(m_columnCount, 0));
}


void DataTableModel::addColumn()
{
    m_columnCount++;
    for (int i = 0; i < m_rowCount; i++)
            m_data.at(i).push_back(0);

}

void DataTableModel::removeRow()
{
    m_rowCount--;
    m_data.pop_back();
}


void DataTableModel::removeColumn()
{
    m_columnCount--;
    for (int i = 0; i < m_rowCount; i++)
            m_data.at(i).pop_back();
}

/******** CONTINUA A BUILDARE *********/


