#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H

#include <vector>
#include <memory>

#include <QtGlobal>

class QSettings;

class RecordManager
{
public:
    enum params { size = 10 };

    typedef std::vector<qint64> records;

public:
    RecordManager();
    ~RecordManager();

    void trySetRecord(qint64 time);

    const records& getRecords() const;

private:
    void save();

private:
    std::unique_ptr<QSettings> m_settings;
    records m_records;
};

#endif // RECORD_MANAGER_H
