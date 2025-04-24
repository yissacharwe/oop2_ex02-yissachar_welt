#ifndef DATEFIELD_H
#define DATEFIELD_H

#include "FieldBase.h"

// Field specialization for date values (stored as string with special validation)
class DateField : public Field<std::string>
{
public:
    DateField(const std::string& label) : Field<std::string>(label)
    {
        // Initialize with current date
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        std::string dateStr =
            std::to_string(ltm.tm_mday) + "-" +
            std::to_string(1 + ltm.tm_mon) + "-" +
            std::to_string(1900 + ltm.tm_year);

        setValue(dateStr);
    }
};

#endif // DATEFIELD_H