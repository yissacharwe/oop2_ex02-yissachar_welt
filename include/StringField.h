#ifndef STRINGFIELD_H
#define STRINGFIELD_H

#include "FieldBase.h"

// Field specialization for string values
class StringField : public Field<std::string>
{
public:
    StringField(const std::string& label) : Field<std::string>(label) {}

    // String-specific implementations can be added here if needed
};

#endif // STRINGFIELD_H