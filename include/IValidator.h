#ifndef IVALIDATOR_H
#define IVALIDATOR_H

#include <string>

// Interface for validators
template <typename T>
class IValidator
{
public:
    virtual ~IValidator() = default;
    virtual bool validate(const T& value, std::string& errorMessage) = 0;
};

#endif // IVALIDATOR_H