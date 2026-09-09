#include <iostream>
#include <string>
using namespace std;

// Struct to represent an activity
struct Activity {
    int priority;         // Priority of the activity
    string course;        // Course name
    string description;   // Description of the activity
    Activity* next;       // Pointer to the next activity in the list

    // Constructor to initialize an activity
    Activity(int priority, string course, string description)
        : priority(priority), course(course), description(description), next(nullptr) {}
};

// Class to represent a priority queue
class PriorityQueue {
public:
    // Constructor to initialize the priority queue
    PriorityQueue() : front(nullptr) {}

    // Function to add an activity to the priority queue
    void enqueue(Activity* activity) {
        // If the queue is empty or the new activity has higher priority, insert at the front
        if (!front || activity->priority < front->priority) {
            activity->next = front;
            front = activity;
        } else {
            // Traverse the list to find the correct position for the new activity
            Activity* temp = front;
            while (temp->next && temp->next->priority <= activity->priority) {
                temp = temp->next;
            }
            activity->next = temp->next;
            temp->next = activity;
        }
    }

    // Function to remove the activity with the highest priority (front of the queue)
    void dequeue() {
        if (!front) return;  // If the queue is empty, do nothing
        Activity* temp = front;  // Store the front activity
        front = front->next;  // Move the front to the next activity
        delete temp;  // Delete the old front activity
    }

    // Function to display all activities in the queue in priority order
    void displayActivities() const {
        Activity* temp = front;
        while (temp) {
            cout << "Priority: " << temp->priority << ", Course: " << temp->course
                 << ", Description: " << temp->description << endl;
            temp = temp->next;
        }
    }

    // Function to check if the queue is empty
    bool isEmpty() const {
        return front == nullptr;
    }

private:
    Activity* front;  // Pointer to the front of the priority queue
};

int main() {
    PriorityQueue activityQueue;  // Create an instance of the PriorityQueue class
    int choice;  // Variable to store user's menu choice

    do {
        // Display menu options
        cout << "\nMenu:\n";
        cout << "1. Add Activity\n";
        cout << "2. Delete Activity\n";
        cout << "3. Display Activities\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore the newline character after entering choice

        if (choice == 1) {
            // Add an activity
            int priority;
            string course, description;
            cout << "Enter priority: ";
            cin >> priority;
            cin.ignore();  // Ignore the newline character after entering priority
            cout << "Enter course: ";
            getline(cin, course);  // Get the course name
            cout << "Enter description: ";
            getline(cin, description);  // Get the description
            activityQueue.enqueue(new Activity(priority, course, description));  // Add the new activity to the queue
        } else if (choice == 2) {
            // Delete an activity
            activityQueue.dequeue();  // Remove the activity with the highest priority
        } else if (choice == 3) {
            // Display activities
            cout << "Activities List:\n";
            activityQueue.displayActivities();  // Display all activities in the queue
        } else if (choice == 4) {
            // Exit the program
            cout << "Exiting...\n";
        } else {
            // Invalid choice
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);  // Continue until the user chooses to exit

    return 0;
}
