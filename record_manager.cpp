#include <QSettings>

#include "QDebug"

#include "record_manager.h"

#define KEY "records"

RecordManager::RecordManager()
{
    m_settings.reset(new QSettings("Evgeny Proydakov", "game_balls_refrigerator"));
    QVariant data = m_settings->value(KEY);
    QList<QVariant> list = data.toList();
    for (int i = 0; i < list.size(); i++) {
        const qint64 value = list.at(i).toInt();
        m_records.push_back(value);
    }
}

RecordManager::~RecordManager()
{
    qDebug() << "~RecordManager: " << this;

    QList<QVariant> list;
    for(size_t i = 0; i < m_records.size(); i++) {
        const qint64 value = m_records[i];
        list.push_back(QVariant(value));
    }
    QVariant data(list);
    m_settings->setValue(KEY, data);
}

void RecordManager::trySetRecord(qint64 time)
{
    if(time < 100) {
        // skip cheat =)
        return;
    }
    bool sort = false;
    if(m_records.size() < params::size) {
        m_records.push_back(time);
        sort = true;
    }
    else {
        const size_t last_index = params::size - 1;
        if(m_records[last_index] > time) {
            m_records[last_index] = time;
            sort = true;
        }
    }
    if(sort) {
        std::sort(m_records.begin(), m_records.end());
    }
}

const RecordManager::records& RecordManager::getRecords() const
{
    return m_records;
}
