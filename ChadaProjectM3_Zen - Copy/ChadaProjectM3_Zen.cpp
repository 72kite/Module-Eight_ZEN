// ChadaProjectM3_Zen.cpp
// Author: Zen (Zion K.)
// Polished version with enhanced modularity and best practices

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <random>
#include <chrono>
#include <thread>

const std::string PROGRAM_NAME = "Chada Project_OP_Beta";

// Clock class encapsulates time in 24-hour format
class Clock {
private:
    int hour;
    int minute;
    int second;

public:
    Clock(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s) {}

    void addHour() {
        hour = (hour + 1) % 24;
    }

    void addMinute() {
        minute = (minute + 1) % 60;
        if (minute == 0) addHour();
    }

    void addSecond() {
        second = (second + 1) % 60;
        if (second == 0) addMinute();
    }

    void setTime(int h, int m, int s) {
        hour = h % 24;
        minute = m % 60;
        second = s % 60;
    }

    // Display time as 12-hour format with AM/PM
    void display12HourClock() const {
        int displayHour = hour % 12;
        if (displayHour == 0) displayHour = 12;
        std::string period = (hour >= 12) ? "PM" : "AM";

        std::cout << std::setw(2) << std::setfill('0') << displayHour << ":"
            << std::setw(2) << std::setfill('0') << minute << ":"
            << std::setw(2) << std::setfill('0') << second << " " << period;
    }

    // Display time as 24-hour format
    void display24HourClock() const {
        std::cout << std::setw(2) << std::setfill('0') << hour << ":"
            << std::setw(2) << std::setfill('0') << minute << ":"
            << std::setw(2) << std::setfill('0') << second;
    }
};

// Initialize program and display welcome messages with a random ID
void initializeProgram() {
    std::cout << "Welcome to " << PROGRAM_NAME << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1000000, 9999999);
    int randomNumber = distrib(gen);

    std::string zen_sware_id = "z" + std::to_string(randomNumber) + "n";
    std::cout << PROGRAM_NAME << " Zen_SWARE_ID: " << zen_sware_id << std::endl;
    std::cout << "Author: Zen (Zion K.)" << std::endl;
    std::cout << "\nLoading dependencies..." << std::endl;
    std::cout << "Waiting for authorization from the Zen Sub80 Network..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Authorization successful.\n" << std::endl;
}

// Display splash screen
void displaySplashScreen() {
    std::cout << "========================================\n";
    std::cout << "          Chada Technologies\n";
    std::cout << "          This is Zen Product\n";
    std::cout << "          Created by Zen (Zion K.)\n";
    std::cout << "========================================\n\n";
}

// Display both clocks side by side
void displayClocks(const Clock& clock12, const Clock& clock24) {
    std::cout << "************************** **************************\n";
    std::cout << "* 12-Hour Clock       * * 24-Hour Clock        *\n";
    std::cout << "* ";
    clock12.display12HourClock();
    std::cout << "       * * ";
    clock24.display24HourClock();
    std::cout << "         *\n";
    std::cout << "************************** **************************\n\n";
}

// Display menu options
void displayMenu() {
    std::cout << "Menu Options:\n";
    std::cout << "1 - Add One Hour\n";
    std::cout << "2 - Add One Minute\n";
    std::cout << "3 - Add One Second\n";
    std::cout << "4 - Reset Time\n";
    std::cout << "5 - Exit Program\n";
}

// Get validated integer input between minVal and maxVal inclusive
int getValidatedInput(const std::string& prompt, int minVal, int maxVal, std::ofstream& logFile) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || input < minVal || input > maxVal) {
            logFile << "[ERROR] Invalid input: " << input << " for prompt: " << prompt << std::endl;
            std::cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear trailing input
            return input;
        }
    }
}

// Process user menu choice and update clocks accordingly
bool processUserChoice(int choice, Clock& clock12, Clock& clock24, std::ofstream& logFile) {
    switch (choice) {
    case 1:
        clock12.addHour();
        clock24.addHour();
        logFile << "[INFO] Added one hour to both clocks." << std::endl;
        break;
    case 2:
        clock12.addMinute();
        clock24.addMinute();
        logFile << "[INFO] Added one minute to both clocks." << std::endl;
        break;
    case 3:
        clock12.addSecond();
        clock24.addSecond();
        logFile << "[INFO] Added one second to both clocks." << std::endl;
        break;
    case 4: {
        int h = getValidatedInput("Enter hour (0-23): ", 0, 23, logFile);
        int m = getValidatedInput("Enter minute (0-59): ", 0, 59, logFile);
        int s = getValidatedInput("Enter second (0-59): ", 0, 59, logFile);
        clock12.setTime(h, m, s);
        clock24.setTime(h, m, s);
        logFile << "[INFO] Time reset to " << h << ":" << m << ":" << s << std::endl;
        break;
    }
    case 5: {
        std::string confirm;
        std::cout << "Are you sure you want to exit? (Y/N): ";
        std::getline(std::cin, confirm);
        if (!confirm.empty() && (confirm[0] == 'Y' || confirm[0] == 'y')) {
            logFile << "[INFO] Program exited by user." << std::endl;
            std::cout << "Exiting program. Thank you!\n";
            return false; // Signal to exit
        }
        break;
    }
    default:
        std::cout << "Invalid choice. Please select a valid option.\n";
        logFile << "[WARNING] Invalid menu choice entered: " << choice << std::endl;
    }
    return true; // Continue running
}

int main() {
    std::ofstream logFile("chada_log.txt", std::ios::app);
    initializeProgram();
    displaySplashScreen();
    logFile << "[INFO] Application started.\n";

    // Get initial time from user
    int h = getValidatedInput("Enter initial hour (0-23): ", 0, 23, logFile);
    int m = getValidatedInput("Enter initial minute (0-59): ", 0, 59, logFile);
    int s = getValidatedInput("Enter initial second (0-59): ", 0, 59, logFile);

    // Initialize two Clock objects
    Clock clock12(h, m, s);
    Clock clock24(h, m, s);

    bool running = true;
    while (running) {
        displayClocks(clock12, clock24);
        displayMenu();

        int choice = getValidatedInput("Enter your choice: ", 1, 5, logFile);
        running = processUserChoice(choice, clock12, clock24, logFile);
    }

    logFile.close();
    return 0;
}
