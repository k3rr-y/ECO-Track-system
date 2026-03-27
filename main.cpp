#include <iostream>
#include <string>
using namespace std;

// BASE CLASS
class Activity {
protected:
    string name;
public:
    Activity(string n) { name = n; }
    virtual float calculateEmission() = 0; // pure virtual
};

// DERIVED CLASS 1
class Transport : public Activity {
private:
    float distance;
public:
    Transport(string n, float d) : Activity(n) {
        distance = d;
    }

    float calculateEmission() {
        return distance * 0.21;
    }
};

// DERIVED CLASS 2
class Electricity : public Activity {
private:
    float units;
public:
    Electricity(string n, float u) : Activity(n) {
        units = u;
    }

    float calculateEmission() {
        return units * 0.5;
    }
};

// USER CLASS
class User {
private:
    string name;
    float totalEmission;
    Activity* activities[10]; // pointer array
    int count;

public:
    User(string n) {
        name = n;
        totalEmission = 0;
        count = 0;
    }

    void addActivity(Activity* act) {
        activities[count++] = act;
    }

    void calculateTotal() {
        totalEmission = 0;
        for (int i = 0; i < count; i++) {
            totalEmission += activities[i]->calculateEmission();
        }
    }

    void display() {
        cout << "\nUser: " << name << endl;
        cout << "Total Carbon Emission: " << totalEmission << " kg CO2\n";
    }

    float getEmission() {
        return totalEmission;
    }

    // Operator Overloading
    bool operator>(User u) {
        return totalEmission > u.totalEmission;
    }

    ~User() {
        cout << "\nSystem closing...\n";
    }
};

// FUNCTION OVERLOADING
void addActivity(User &u, float distance) {
    u.addActivity(new Transport("Car", distance));
}

void addActivity(User &u, float units, int type) {
    u.addActivity(new Electricity("Electricity", units));
}

// EXCEPTION HANDLING
void inputDistance(float &d) {
    cout << "Enter distance (km): ";
    cin >> d;

    if (d < 0) {
        throw "Distance cannot be negative!";
    }
}

// MAIN FUNCTION
int main() {
    User user("Ker");

    int choice;
    float value;

    do {
        cout << "\n===== EcoTrack Menu =====\n";
        cout << "1. Add Transport\n";
        cout << "2. Add Electricity\n";
        cout << "3. Calculate Emission\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        try {
            switch(choice) {
                case 1:
                    inputDistance(value);
                    addActivity(user, value);
                    break;

                case 2:
                    cout << "Enter electricity units: ";
                    cin >> value;
                    if (value < 0) throw "Invalid units!";
                    addActivity(user, value, 1);
                    break;

                case 3:
                    user.calculateTotal();
                    user.display();

                    // Conditional operator
                    (user.getEmission() > 50) ?
                        cout << "⚠️ Reduce usage!\n" :
                        cout << "✅ Eco-friendly!\n";
                    break;

                case 4:
                    cout << "Exiting...\n";
                    break;

                default:
                    cout << "Invalid choice\n";
            }
        }
        catch (const char* msg) {
            cout << "Error: " << msg << endl;
        }

    } while(choice != 4);

    return 0;
}