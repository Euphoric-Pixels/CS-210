#include <iostream>
#include <string>


using namespace std;


// Function declarations
void addOneHour();
void addOneMinute();
void addOneSecond();
unsigned int getSecond();
void setSecond(unsigned int s);
unsigned int getMinute();
void setMinute(unsigned int m);
unsigned int getHour();
void setHour(unsigned int h);
string twoDigitString(unsigned int n);
string nCharString(size_t n, char c);
string formatTime24(unsigned int h, unsigned int m, unsigned int s);
string formatTime12(unsigned int h, unsigned int m, unsigned int s);
void printMenu(char* strings[], unsigned int numStrings, unsigned char width);
unsigned int getMenuChoice(unsigned int maxChoice);
void displayClocks(unsigned int h, unsigned int m, unsigned int s);
void mainMenu();


// Global clock state variables
unsigned int currentHour = 0;      // Current hour (0-23)
unsigned int currentMinute = 0;    // Current minute (0-59)
unsigned int currentSecond = 0;    // Current second (0-59)


/**
* Returns the current second value
* @return current second (0-59)
*/
unsigned int getSecond() {
    return currentSecond;
}


/**
* Sets the current second value
* @param s second value to set (0-59)
*/
void setSecond(unsigned int s) {
    currentSecond = s;
}


/**
* Returns the current minute value
* @return current minute (0-59)
*/
unsigned int getMinute() {
    return currentMinute;
}


/**
* Sets the current minute value
* @param m minute value to set (0-59)
*/
void setMinute(unsigned int m) {
    currentMinute = m;
}


/**
* Returns the current hour value
* @return current hour (0-23)
*/
unsigned int getHour() {
    return currentHour;
}


/**
* Sets the current hour value
* @param h hour value to set (0-23)
*/
void setHour(unsigned int h) {
    currentHour = h;
}


/**
* Formats a number as 2 digits, with a leading 0 if needed
* @param n number to format, assumed between 0 and 59, inclusive
* @return two digit string representation of number
*/
string twoDigitString(unsigned int n) {
    if (n <= 9) {
        return "0" + to_string(n);
    }
    return to_string(n);
}


/**
* Returns a string of length n, each character a c.
* For example, nCharString(5, '*') should return "*****"
* @param n string length, >=0
* @return string of n c's
*/
string nCharString(size_t n, char c) {
    return string(n, c);
}


/**
* Formats the time in military format
* @param h, hours 0 to 23
* @param m, minutes 0 to 59
* @param s, seconds 0 to 59
* @return hh:mm:ss
*/
string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
    return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s);
}


/**
* Formats the time in am/pm format
* @param h, hours 0 to 23
* @param m, minutes 0 to 59
* @param s, seconds 0 to 59
* @return hh:mm:ss A M or hh:mm:ss P M where hh is between 01 and 12, inclusive
*/
string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
    string time = (h >= 12) ? "P M" : "A M";
    h = h % 12;
    if (h == 0) h = 12; // Convert 0 to 12 for 12-hour format


    return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s) + " " + time;
}


/**
* Prints menu
* @param *strings[], nonempty array of choices
* @param width, width of each line, will be comfortably bigger than the longest string
*/
void printMenu(const char* strings[], unsigned int numStrings, unsigned char width) {
    // Print top border
    cout << nCharString(width, '*') << endl;


    // Print each menu item with proper formatting
    for (unsigned int i = 0; i < numStrings; ++i) {
        string menuItem = " " + to_string(i + 1) + " - " + strings[i];
        unsigned int spacesNeeded = width - menuItem.length() - 2; // Account for border stars

        cout << '*' << menuItem << nCharString(spacesNeeded, ' ') << '*' << endl;

        // Add spacing between menu items (except after last item)
        if (i < numStrings - 1) {
            cout << endl;
        }
    }

    // Print bottom border
    cout << nCharString(width, '*') << endl;
}


/**
* Gets menu choice 1 through maxChoice, inclusive
* @param maxChoice, maximum choice index, a number between 2 and 9, inclusive
* @return the first legal choice input, could be 1 through maxChoice, inclusive
*/
unsigned int getMenuChoice(unsigned int maxChoice) {
    unsigned int choice;

    // Continuously prompt until valid input is received
    while (true) {
        cin >> choice;
        if ((choice >= 1) && (choice <= maxChoice)) {
            return choice;
        }
        // Input validation happens silently (no error messages)
    }
}


/**
* Display the clocks
* @param h, hours 0 to 23
* @param m, minutes 0 to 59
* @param s, seconds 0 to 59
*/
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {
    // Print clock headers with borders
    cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
    cout << "*" << "      " << "12-HOUR CLOCK" << "      " << "*" << "   ";
    cout << "*" << "      " << "24-HOUR CLOCK" << "      " << "*" << endl;
    cout << endl;

    // Print formatted times with proper spacing
    cout << "*" << "      " << formatTime12(h, m, s) << "       " << "*" << "   ";
    cout << "*" << "        " << formatTime24(h, m, s) << "         " << "*" << endl;

    // Print bottom borders
    cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
}


/**
* Main menu loop - displays clocks and menu, processes user input
*/
void mainMenu() {
    const char* menuItems[] = { "Add One Hour", "Add One Minute", "Add One Second", "Exit Program" };


    while (true) {
        // Display current time
        displayClocks(getHour(), getMinute(), getSecond());

        // Display menu options
        printMenu(menuItems, 4, 26);


        // Process user choice
        switch (getMenuChoice(4)) {
        case 1:
            addOneHour();
            break;
        case 2:
            addOneMinute();
            break;
        case 3:
            addOneSecond();
            break;
        case 4:
            return; // Exit program
        }
    }
}


/**
* Increments the second value, handling rollover to minutes
*/
void addOneSecond() {
    if ((getSecond() >= 0) && (getSecond() <= 58)) {
        setSecond(getSecond() + 1);
    }
    else if (getSecond() == 59) {
        setSecond(0);
        addOneMinute(); // Handle minute rollover
    }
}


/**
* Increments the minute value, handling rollover to hours
*/
void addOneMinute() {
    if ((getMinute() >= 0) && (getMinute() <= 58)) {
        setMinute(getMinute() + 1);
    }
    else if (getMinute() == 59) {
        setMinute(0);
        addOneHour(); // Handle hour rollover
    }
}


/**
* Increments the hour value, handling rollover to 00
*/
void addOneHour() {
    if ((getHour() >= 0) && (getHour() <= 22)) {
        setHour(getHour() + 1);
    }
    else if (getHour() == 23) {
        setHour(0); // Roll over to 00
    }
}




int main() {
    // Initialize clock to 00:00:00
    setHour(0);
    setMinute(0);
    setSecond(0);


    // Enter main menu loop
    mainMenu();


    return 0;
}

