#ifndef SELECTIONFIELD_H
#define SELECTIONFIELD_H

#include "FieldBase.h"
#include <vector>
#include <algorithm>

// Field specialization for selection from predefined options
class SelectionField : public Field<std::string>
{
private:
    std::vector<std::string> options;
    std::vector<bool> selected;
    bool multiSelect;

public:
    SelectionField(const std::string& label, const std::vector<std::string>& options, bool multiSelect = false)
        : Field<std::string>(label), options(options), multiSelect(multiSelect)
    {
        selected.resize(options.size(), false);
    }

    bool toggleOption(size_t index)
    {
        if (index >= options.size()) return false;

        if (!multiSelect) {
            // Single select mode - deselect all others
            std::fill(selected.begin(), selected.end(), false);
        }

        selected[index] = !selected[index];
        updateValue();
        return true;
    }

    bool setOption(size_t index, bool state) {
        if (index >= options.size()) return false;

        if (!multiSelect && state) {
            // Single select mode - deselect all others
            std::fill(selected.begin(), selected.end(), false);
        }

        selected[index] = state;
        updateValue();
        return true;
    }

    void updateValue() {
        std::string result;
        for (size_t i = 0; i < options.size(); ++i) {
            if (selected[i]) {
                if (!result.empty()) result += "| ";
                result += options[i];
            }
        }
        setValue(result);
    }

    const std::vector<std::string>& getOptions() const {
        return options;
    }

    const std::vector<bool>& getSelectedStates() const {
        return selected;
    }

    bool isMultiSelect() const {
        return multiSelect;
    }
};

#endif // SELECTIONFIELD_H