#ifndef TIMEFOCUSMODEL_H
#define TIMEFOCUSMODEL_H

#include <QAbstractListModel>
#include <QTime>
#include "soundinterfaces.h"
#include <qloggingcategory.h>
#include <KeyboardInterceptor.h>
#include <qqmlengine.h>
#include <qvariant.h>
#include "typingrate.h"
Q_DECLARE_LOGGING_CATEGORY(LC_TimeFocusModel);
// Duration and RemainingTime is msec counter
struct TimeFocusData
{
    Q_GADGET
public:
    qint64 duration;
    qint64 remainingTime;
    bool completed;
    PeriodInfo::PeriodType type;
    RateList rates;

};
class TimeFocusModel : public QAbstractListModel
{
    Q_OBJECT;
    QML_ELEMENT
    QML_SINGLETON
public:
    enum Roles
    {
        Duration = Qt::UserRole,
        RemainingTime,
        Completed,
        Rates,
        Type
    }; Q_ENUM(Roles)
    explicit TimeFocusModel(QObject* parent = nullptr);

    Q_INVOKABLE bool clear();
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;	
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
private:

    inline static TimeFocusModel* _p_inst = nullptr;
    QVector<TimeFocusData> _data;
    static QHash<int, QByteArray> _roles;
};

#endif // TIMEFOCUSMODEL_H
