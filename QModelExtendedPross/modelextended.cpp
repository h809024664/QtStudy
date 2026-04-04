#include "modelextended.h"

ModelExtended::ModelExtended(QObject *parent)
    : QAbstractTableModel{parent}
{
    empno[1] = "2022001";
    empno[2] = "2022002";
    empno[3] = "2022003";
    empno[4] = "2022004";
    empno[5] = "2022005";

    empname[1] = "张三";
    empname[2] = "李四";
    empname[3] = "王五";
    empname[4] = "张平";
    empname[5] = "周发";

    ModelFunc();
}

int ModelExtended::rowCount(const QModelIndex &parent) const
{
    return empindex.size();//表视图行
}

int ModelExtended::columnCount(const QModelIndex &parent) const
{
    return 3;//表视图列
}

QVariant ModelExtended::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();//QVariant类：QBrush QColor QRect QSize等
    }
    if(role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            return empno[empindex[index.row()]];
            break;
        case 1:
            return empname[empnameindex[index.row()]];
            break;
            case 2:
            return empdepartment[index.row()];
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant ModelExtended::headerData(int section, Qt::Orientation orientateion, int role) const
{
    if(role == Qt::DisplayRole && orientateion==Qt::Horizontal)
    {
        return viewListtittle[section];
    }
    return QAbstractItemModel::headerData(section, orientateion,role);
}

void ModelExtended::ModelFunc()
{
    viewListtittle<<"员工编号"<<"员工姓名"<<"所在部门";
    empindex<<1<<2<<3<<4<<5;
    empnameindex<<1<<2<<3<<4<<5;
    empdepartment<<"营销部"<<"财务部"<<"研发部"<<"董事会"<<"后勤部";
}
