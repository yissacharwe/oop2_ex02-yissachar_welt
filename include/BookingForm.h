﻿#ifndef BOOKINGFORM_H
#define BOOKINGFORM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <array>
class DialogueManager;

struct PersonalInfo {
    std::string name;
    std::string id;
    std::string address;
    std::string email;
};

class BookingForm {
protected:
    std::vector<std::string> fieldLabels;
    std::vector<std::string> userInput;
    std::size_t activeField = 0;
    sf::Clock cursorTimer;
    bool showCursor = true;

    sf::RenderWindow& window;
    DialogueManager* formManager;
    PersonalInfo personalInfo;

    virtual void setDefaultValues()=0 ;
    void openConfirmationWindow();

public:
    BookingForm(sf::RenderWindow& win, DialogueManager* manager);
    virtual ~BookingForm() = default;
    virtual std::string getFormType() const = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void handleInput(sf::Event event) = 0;
};

#endif // BOOKINGFORM_H
