#ifndef INTFIELD_H
#define INTFIELD_H

#include "FieldBase.h"

// Field specialization for integer values
class IntField : public Field<int>
{
public:
    IntField(const std::string& label)
        : Field<int>(label)
    {
    }

    void setDisplayValue(const std::string& displayValue) override
    {
        try {
            setValue(std::stoi(displayValue));
        }
        catch (...) {
            // Handle conversion error - set to 0 or another default
            setValue(0);
        }
    }
};

#endif // INTFIELD_H