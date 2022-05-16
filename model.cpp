#include "model.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool DataTableModel::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

DataTableModel::DataTableModel(): empty(true) {}

DataTableModel::DataTableModel(int c_rows, int c_cols, QObject* parent) : QAbstractTableModel(parent)
{
    Q_UNUSED(parent)

    m_rowCount = c_rows;
    m_columnCount = c_cols;
    empty = false;

    for (int i = 0; i < m_rowCount; i++) m_rowsHeaderData.push_back(QVariant(i));
    for (int i = 0; i < m_columnCount; i++) m_columnsHeaderData.push_back(QVariant(i));


    vector<double> firstRow;
    for (int i = 0; i < m_columnCount; i++) firstRow.push_back(i);
    m_data.push_back(firstRow);

    for (int i = 1; i < m_rowCount; i++) m_data.push_back(vector<double>(m_columnCount, i+1));
}

DataTableModel::DataTableModel(QObject* parent, int row, int col, const vector<vector<double>>& values, const vector<QVariant>& columnHeaders, const vector<QVariant>& rowHeaders)
    : QAbstractTableModel(parent), m_data(values), m_columnsHeaderData(columnHeaders), m_rowsHeaderData(rowHeaders),m_rowCount(row), m_columnCount(col), empty(false) {}

DataTableModel::DataTableModel(const DataTableModel& model)
    : m_data(model.m_data), m_columnsHeaderData(model.m_columnsHeaderData), m_rowsHeaderData(model.m_rowsHeaderData), m_rowCount(model.m_rowCount), m_columnCount(model.m_columnCount), empty(false) {}

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
    {
        return m_columnsHeaderData[section];
    } else {
        return m_rowsHeaderData[section];
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
        if (orientation == Qt::Vertical)
        {
            m_rowsHeaderData.at(section) = value.toString();
        }
        else
        {
            m_columnsHeaderData.at(section) = value.toString();
        }
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

void DataTableModel::insertRow(const QString& label, double d_value)
{    
    beginResetModel();
    m_rowsHeaderData.push_back(label);
    m_rowCount++;
    m_data.push_back(vector<double>(m_columnCount, d_value));
    endResetModel();
}

void DataTableModel::removeRow()
{
    beginResetModel();
    m_rowsHeaderData.pop_back();
    m_rowCount--;
    m_data.pop_back();
    endResetModel();
}


void DataTableModel::insertColumn(const QString& label , double d_value)
{
    beginResetModel();
    m_columnsHeaderData.push_back(label);
    m_columnCount++;
    for (int i = 0; i < m_rowCount; i++)
            m_data.at(i).push_back(d_value);
    endResetModel();
}

void DataTableModel::removeColumn()
{
    beginResetModel();
    m_columnsHeaderData.pop_back();
    m_columnCount--;
    for (int i = 0; i < m_rowCount; i++)
            m_data.at(i).pop_back();
    endResetModel();
}

void DataTableModel::insertRowAndColumn(const QString& rowLabel, const QString& columnLabel, double d_value)
{
    beginResetModel();
    m_rowsHeaderData.push_back(rowLabel);
    m_columnsHeaderData.push_back(columnLabel);
    m_rowCount++;
    m_columnCount++;
    m_data.push_back(vector<double>(m_columnCount, d_value));
    endResetModel();
}


double DataTableModel::max()
{
    double maxValue = -__DBL_MAX__;
    for (auto it = m_data.begin(); it != m_data.end(); it++)
    {
        double rowMax = *max_element(it->begin(), it->end());
        if (rowMax > maxValue) maxValue = rowMax;
    }
    if (maxValue != -__DBL_MAX__) return maxValue;
    else return 0;
}

double DataTableModel::min()
{
    double minValue = __DBL_MAX__;
    for (auto it = m_data.begin(); it != m_data.end(); it++)
    {
        double rowMin = *min_element(it->begin(), it->end());
        if (rowMin < minValue) minValue = rowMin;
    }
    if (minValue != __DBL_MAX__) return minValue;
    else return 0;
}


/******** CONTINUA A BUILDARE *********/

vector<vector<double>> DataTableModel::getData() const
{
    return m_data;
}


vector<QVariant> DataTableModel::getRowsHeaders() const
{
    return m_rowsHeaderData;
}

vector<QVariant> DataTableModel::getColumnsHeaders() const
{
    return m_columnsHeaderData;
}
