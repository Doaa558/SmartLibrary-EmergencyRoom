/*
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Patient
{
    int id;
    string name;
    int severity;
    int arrivalTime;
};

// Comparator
struct Compare
{
    bool operator()(Patient a, Patient b)
    {
       
        if (a.severity != b.severity)
            return a.severity < b.severity;

        
        return a.arrivalTime > b.arrivalTime;
    }
};

class EmergencyRoom
{
private:
    priority_queue<Patient, vector<Patient>, Compare> pq;

public:

    // Insert Patient
    void insertPatient(int id, string name,
        int severity, int arrivalTime)
    {
        Patient p;

        p.id = id;
        p.name = name;
        p.severity = severity;
        p.arrivalTime = arrivalTime;

        pq.push(p);

        cout << "Patient added successfully.\n";
    }

    // View Next Patient
    void viewNextPatient()
    {
        if (pq.empty())
        {
            cout << "No patients in emergency room.\n";
            return;
        }

        Patient p = pq.top();

        cout << "\nNext Patient:\n";
        cout << "ID: " << p.id << endl;
        cout << "Name: " << p.name << endl;
        cout << "Severity: " << p.severity << endl;
        cout << "Arrival Time: " << p.arrivalTime << endl;
    }

    // Treat Next Patient
    void treatNextPatient()
    {
        if (pq.empty())
        {
            cout << "No patients to treat.\n";
            return;
        }

        Patient treated = pq.top();

        cout << "\nTreating Patient:\n";
        cout << "ID: " << treated.id << endl;
        cout << "Name: " << treated.name << endl;

        pq.pop();
    }
};

int main()
{
    EmergencyRoom er;

    er.insertPatient(1, "Ali", 8, 1);
    er.insertPatient(2, "Mona", 5, 2);
    er.insertPatient(3, "Ahmed", 9, 3);
    er.insertPatient(4, "Sara", 7, 4);

    er.viewNextPatient();

    er.treatNextPatient();

    er.viewNextPatient();

    return 0;
} */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Patient
{
    int id;
    string name;
    int severity;
    int arrivalTime;
};

class EmergencyRoom
{
private:
    vector<Patient> heap;

    // Priority Comprasion
    bool higherPriority(Patient a, Patient b)
    {
        // severity
        if (a.severity != b.severity)
            return a.severity > b.severity;

    
        return a.arrivalTime < b.arrivalTime;
    }

    // Heapify Up
    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (higherPriority(heap[index], heap[parent]))
            {
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    // Heapify Down
    void heapifyDown(int index)
    {
        int size = heap.size();

        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size &&
                higherPriority(heap[left], heap[largest]))
            {
                largest = left;
            }

            if (right < size &&
                higherPriority(heap[right], heap[largest]))
            {
                largest = right;
            }

            if (largest != index)
            {
                swap(heap[index], heap[largest]);
                index = largest;
            }
            else
            {
                break;
            }
        }
    }

public:

    // Insert Patient
    void insertPatient(int id, string name,
        int severity, int arrivalTime)
    {
        Patient p;
        p.id = id;
        p.name = name;
        p.severity = severity;
        p.arrivalTime = arrivalTime;

        heap.push_back(p);

        heapifyUp(heap.size() - 1);

        cout << "Patient added successfully.\n";
    }

    // View Next Patient
    void viewNextPatient()
    {
        if (heap.empty())
        {
            cout << "No patients in emergency room.\n";
            return;
        }

        Patient p = heap[0];

        cout << "\nNext Patient:\n";
        cout << "ID: " << p.id << endl;
        cout << "Name: " << p.name << endl;
        cout << "Severity: " << p.severity << endl;
        cout << "Arrival Time: " << p.arrivalTime << endl;
    }

    // Treat Next Patient
    void treatNextPatient()
    {
        if (heap.empty())
        {
            cout << "No patients to treat.\n";
            return;
        }

        Patient treated = heap[0];

        cout << "\nTreating Patient:\n";
        cout << "ID: " << treated.id << endl;
        cout << "Name: " << treated.name << endl;

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);
    }

    // Update Severity
    void updateSeverity(int id, int newSeverity)
    {
        bool found = false;

        for (int i = 0; i < heap.size(); i++)
        {
            if (heap[i].id == id)
            {
                int oldSeverity = heap[i].severity;

                heap[i].severity = newSeverity;

                // لو severity زادت -> heapify up
                if (newSeverity > oldSeverity)
                    heapifyUp(i);

               
                else
                    heapifyDown(i);

                found = true;

                cout << "Severity updated successfully.\n";
                break;
            }
        }

        if (!found)
        {
            cout << "Patient not found.\n";
        }
    }

    // Display All Patients
    void displayPatients()
    {
        if (heap.empty())
        {
            cout << "No patients.\n";
            return;
        }

        cout << "\nAll Patients (Level Order):\n";

        for (int i = 0; i < heap.size(); i++)
        {
            cout << "ID: " << heap[i].id
                << " | Name: " << heap[i].name
                << " | Severity: " << heap[i].severity
                << " | Arrival: " << heap[i].arrivalTime
                << endl;
        }
    }
};

int main()
{
    EmergencyRoom er;

    er.insertPatient(1, "Ali", 8, 1);
    er.insertPatient(2, "Mona", 5, 2);
    er.insertPatient(3, "Ahmed", 9, 3);
    er.insertPatient(4, "Sara", 7, 4);
    er.insertPatient(5, "Omar", 10, 5);
    er.insertPatient(6, "Nour", 6, 6);
    er.insertPatient(7, "Youssef", 4, 7);
    er.insertPatient(8, "Laila", 9, 8);
    er.insertPatient(9, "Hassan", 3, 9);
    er.insertPatient(10, "Mariam", 8, 10);

    er.insertPatient(11, "Khaled", 2, 11);
    er.insertPatient(12, "Nada", 1, 12);
    er.insertPatient(13, "Tamer", 7, 13);
    er.insertPatient(14, "Heba", 6, 14);
    er.insertPatient(15, "Mostafa", 5, 15);
    er.insertPatient(16, "Aya", 10, 16);
    er.insertPatient(17, "Salma", 9, 17);
    er.insertPatient(18, "Adel", 8, 18);
    er.insertPatient(19, "Karim", 7, 19);
    er.insertPatient(20, "Fatma", 4, 20);

    // Display
    er.displayPatients();

    // View next patient
    er.viewNextPatient();

    // Treat patient
    er.treatNextPatient();

    // Display again
    er.displayPatients();

    // Update severity
    er.updateSeverity(2, 10);

    // Display after update
    er.displayPatients();

    // View next patient again
    er.viewNextPatient();

    return 0;
}
