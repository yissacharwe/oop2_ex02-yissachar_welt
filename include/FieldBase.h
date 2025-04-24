#ifndef FIELDBASE_H
#define FIELDBASE_H

#include <string>
#include <memory>
#include <vector>

// Forward declaration
template <typename T>
class IValidator;

// Abstract base class for all types
class FieldBase
{
public:
	virtual ~FieldBase() = default;
	virtual bool validate() = 0;
	virtual std::string getDisplayValue() const = 0;
	virtual std::string getLabel() const = 0;
	virtual std::string getErrorMessage() const = 0;
	virtual bool isValid() const = 0;
	virtual void setDisplayValue(const std::string& displayValue) = 0;
};

// Template class for fields of different types
template <typename T>
class Field : public FieldBase
{
private:
	std::string label;
	T value;
	bool valid = true;
	std::string errorMessage;
	std::vector<std::shared_ptr><IValidator<T>> validators;

public:
	Field(const std::string& label)
		: label(label) {}

	bool validate() override
	{
		valid = true;
		errorMessage.clear();

		for (const auto& validator : validators)
		{
			std::string tempErrorMsg;
			if (!validator->validate(value, tempErrorMessage))
			{
				valid = false;
				errorMessage = tempErrorMsg;
				return false;
			}
		}

		return true;
	}

	void setValue(const T& newValue)
	{
		value = newValue;
		valid = true; // Reset validation status
		errorMessage.clear();
	}

	const T& getValue() const
	{
		return value;
	}

	std::string getDisplayValue() const override
	{
		// Default implementation for string conversion
		if constexpr (std::is_same_v<T, std::string>)
		{
			return value;
		}
		else
		{
			return std::to_string(value);
		}
	}

	void setDisplayValue(const std::string& displayValue) override
	{
		// This will be overriden by specialized implementations
		// Default implementation for numeric types
		if constexpr (std::is_integral_v<T>)
		{
			try {
				value = static_cast<T>(std::stoi(displayValue));
			}
			catch (...) {
				// Handle conversion error
			}
		}
		else
		{
			// For string types
			value = displayValue;
		}
	}

	std::string getLabel() const override
	{
		return label;
	}

	std::string getErrorMessage() const override
	{
		return errorMessage;
	}

	bool isValid() const override
	{
		return valid;
	}

	void addValidator(std::shared_ptr<IValidator<T>> validator)
	{
		validators.push_back(validator);
	}
};

#endif // FIELDBASE_H