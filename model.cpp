#include "model.h"
using namespace std;

DataTableModel::DataTableModel(int c_rows, int c_cols, QObject* parent) : QAbstractTableModel(parent)
{
    Q_UNUSED(parent)

    m_rowCount = c_rows;
    m_columnCount = c_cols;


    for (int i = 0; i < m_rowCount; i++) m_rowsHeaderData.push_back(QVariant(i));
    for (int i = 0; i < m_columnCount; i++) m_columnsHeaderData.push_back(QVariant(i));


    vector<double> firstRow;
    for (int i = 0; i < m_columnCount; i++) firstRow.push_back(i);
    m_data.push_back(firstRow);

    for (int i = 1; i < m_rowCount; i++) m_data.push_back(vector<double>(m_columnCount, i+1));
}

/*DataTableModel::DataTableModel(QObject* parent, int row, int col, const vector<vector<double>>& values, const vector<vector<string>>& headers)
    : QAbstractTableModel(parent), m_data(values), m_headerData(headers), m_rowCount(row), m_columnCount(col) {}*/

DataTableModel::DataTableModel(const DataTableModel& model)
    : m_data(model.m_data), m_columnsHeaderData(model.m_columnsHeaderData), m_rowsHeaderData(model.m_rowsHeaderData), m_rowCount(model.m_rowCount), m_columnCount(model.m_columnCount) {}

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
        return m_columnsHeaderData[section];
        //return QString("%1").arg(section + 1);
    } else { // Qt::Vertical -- rows headers
        return m_rowsHeaderData[section];
        //return QString("%1").arg(section + 1);
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

bool DataTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (orientation == Qt::Horizontal)
        {
            m_columnsHeaderData.at(section) = value.toString();
        }
        else
        {
            m_rowsHeaderData.at(section) = value.toString();
        }
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

void DataTableModel::insertRow()
{
    beginResetModel();
    m_rowsHeaderData.push_back(m_rowCount); // NON FUNZIONA TROVARE LA SOLUZIONE
    m_rowCount++;
    m_data.push_back(vector<double>(m_columnCount, 0));
    endResetModel();
}

void DataTableModel::removeRow()
{
    if (m_rowCount)
    {
        beginResetModel();
        m_rowCount--;
        m_data.pop_back();
        endResetModel();
    }
    else throw QString("There are no more rows to remove.");
}


void DataTableModel::insertColumn()
{
    beginResetModel();
    m_columnsHeaderData.push_back(m_columnCount); // NON FUNZIONA TROVARE LA SOLUZIONE
    m_columnCount++;
    for (int i = 0; i < m_rowCount; i++)
            m_data.at(i).push_back(0);
    endResetModel();
}

void DataTableModel::removeColumn()
{
    if (m_columnCount)
    {
        beginResetModel();
        m_columnCount--;
        for (int i = 0; i < m_rowCount; i++)
                m_data.at(i).pop_back();
        endResetModel();
    }
    else throw QString("There are no more columns to remove.");
}

/*
double DataTableModel::getXMax()
{
    auto it = max_element(begin(m_data), end(m_data));
    return 0;
}

double DataTableModel::getYMax()
{
    return 0;
}*/


/******** CONTINUA A BUILDARE *********/
/*
vector<vector<double>> DataTableModel::getValues(){
    return m_data;
}
*/

vector<QVariant> DataTableModel::getRowsHeaders(){
    return m_rowsHeaderData;
}

vector<QVariant> DataTableModel::getColumnsHeaders(){
    return m_columnsHeaderData;
}
