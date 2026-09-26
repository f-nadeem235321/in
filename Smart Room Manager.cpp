#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Device {
private:
    string name;
    bool isOn;
    int brightness;

public:
    Device() {
        name = "Unknown";
        isOn = false;
        brightness = 50;
    }

    Device(string n, bool status, int b) {
        name = n;
        isOn = status;
        if (b >= 0 && b <= 100)
            brightness = b;
        else
            brightness = 50;
    }

    // Destructor 
    ~Device() {}

    void setName(string n) { name = n; }
    string getName() const { return name; }

    void setBrightness(int b) {
        if (b >= 0 && b <= 100)
            brightness = b;
        else
            cout << "Invalid brightness! Must be between 0 and 100." << endl;
    }

    int getBrightness() const { return brightness; }

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    bool getStatus() const { return isOn; }

    void showInfo() const {
        cout << "Name: " << name
            << ", Status: " << (isOn ? "ON" : "OFF")
            << ", Brightness: " << brightness << endl;
    }
};

// ================= ROOM CLASS =================

class Room {
private:
    string roomName;
    Device devices[10];
    int count;

public:
    Room(string name) {
        roomName = name;
        count = 0;
        loadFromFile();
    }

    ~Room() {
        saveToFile();
        cout << "Room " << roomName << " manager closed." << endl;
    }

    void addDevice(const Device& d) {
        if (count < 10) {
            devices[count] = d;
            count++;
            cout << "Device added successfully." << endl;
        }
        else {
            cout << "Room is full! Cannot add more devices." << endl;
        }
    }

    void showAllDevices() const {
        if (count == 0) {
            cout << "No devices in the room." << endl;
            return;
        }

        for (int i = 0; i < count; i++)
            devices[i].showInfo();
    }

    int findDevice(string name) {
        for (int i = 0; i < count; i++) {
            if (devices[i].getName() == name)
                return i;
        }
        return -1;
    }

    void toggleDevice(string name) {
        int index = findDevice(name);

        if (index == -1) {
            cout << "Device not found." << endl;
            return;
        }

        if (devices[index].getStatus())
            devices[index].turnOff();
        else
            devices[index].turnOn();

        cout << "Device toggled successfully." << endl;
    }

    void setDeviceBrightness(string name, int b) {
        int index = findDevice(name);

        if (index == -1) {
            cout << "Device not found." << endl;
            return;
        }

        devices[index].setBrightness(b);
    }

    // ================= FILE HANDLING =================

    void saveToFile() {
        ofstream file("devices.txt");

        if (!file)
            return;

        file << count << endl;

        for (int i = 0; i < count; i++) {
            file << devices[i].getName() << endl;
            file << devices[i].getStatus() << endl;
            file << devices[i].getBrightness() << endl;
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("devices.txt");

        if (!file)
            return;

        file >> count;
        file.ignore();

        for (int i = 0; i < count && i < 10; i++) {
            string name;
            bool status;
            int brightness;

            getline(file, name);
            file >> status;
            file >> brightness;
            file.ignore();

            devices[i] = Device(name, status, brightness);
        }

        file.close();
    }
};

// ================= MAIN FUNCTION =================

int main() {

    string roomName;
    cout << "Enter Room Name: ";
    getline(cin, roomName);

    Room room(roomName);

    int choice;

    do {
        cout << " Smart Room Manager " << endl;
        cout << "1. Add a Device" << endl;
        cout << "2. Show All Devices" << endl;
        cout << "3. Turn Device ON/OFF" << endl;
        cout << "4. Change Brightness" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter number only.\n";
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            string name;
            int statusInput;
            int brightness;

            cout << "Enter device name: ";
            getline(cin, name);

            cout << "Enter status (1 for ON, 0 for OFF): ";
            cin >> statusInput;

            cout << "Enter brightness (0-100): ";
            cin >> brightness;
            cin.ignore();

            bool status = (statusInput == 1);

            Device d(name, status, brightness);
            room.addDevice(d);
        }

        else if (choice == 2) {
            room.showAllDevices();
        }

        else if (choice == 3) {
            string name;
            cout << "Enter device name to toggle: ";
            getline(cin, name);
            room.toggleDevice(name);
        }

        else if (choice == 4) {
            string name;
            int b;

            cout << "Enter device name: ";
            getline(cin, name);

            cout << "Enter new brightness (0-100): ";
            cin >> b;
            cin.ignore();

            room.setDeviceBrightness(name, b);
        }

        else if (choice == 5) {
            cout << "Saving data and exiting..." << endl;
        }

        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}