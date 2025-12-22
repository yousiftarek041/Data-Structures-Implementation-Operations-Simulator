#include <iostream>
#include <string>
using namespace std;

struct Grade
{
    string course;
    float degree;
    int hours;
};

struct node
{
    int id;
    string name;
    int Age;
    float gpa;
    node* next;
    Grade* grade;
    int course_count;
};

class linked_list
{
private:
    node* head;

public:
    linked_list()
    {
        head = nullptr;
    }
    ~linked_list() {
        node* ptr = head;
        while (ptr) {
            node* temp = ptr;
            ptr = ptr->next;
            delete[] temp->grade;
            delete temp;
        }
    }
    bool id_exists(int id) {
        node* ptr = head;
        while (ptr != nullptr) {
            if (ptr->id == id)
                return true;
            ptr = ptr->next;
        }
        return false;
    }

    void insert_stud(int id, string name, int age, Grade* grade, int course_count)
    {
        node* new_stud = new node;

        new_stud->id = id;
        new_stud->name = name;
        new_stud->Age = age;
        new_stud->next = nullptr;
        new_stud->course_count = course_count;
        new_stud->grade = new Grade[course_count];

        float total_points = 0;
        int total_hours = 0;

        for (int i = 0; i < course_count; i++)
        {
            new_stud->grade[i] = grade[i];
            total_points += grade[i].degree * grade[i].hours;
            total_hours += grade[i].hours;
        }

        float gpa_value = 0;

        if (total_hours > 0) {
            gpa_value = total_points / total_hours;
        }
        else {
            gpa_value = 0;
        }

        new_stud->gpa = ((gpa_value) / 100) * 4;

        if (head == nullptr)
        {
            head = new_stud;
        }
        else
        {
            node* ptr = head;
            while (ptr->next != nullptr)
            {
                ptr = ptr->next;
            }
            ptr->next = new_stud;
        }
    }

    void display()
    {
        node* ptr = head;

        while (ptr != nullptr)
        {
            cout << "\n----------------------\n";
            cout << "ID: " << ptr->id << endl;
            cout << "Name: " << ptr->name << endl;
            cout << "Age: " << ptr->Age << endl;
            cout << "GPA: " << ptr->gpa << endl;
            cout << "Grades:\n";

            for (int i = 0; i < ptr->course_count; i++)
            {
                cout << ptr->grade[i].course
                    << " = " << ptr->grade[i].degree
                    << " (" << ptr->grade[i].hours << " hours)" << endl;
            }

            ptr = ptr->next;
        }

        cout << "\n----------------------\n";
    }

    void search_stud()
    {
        node* ptr = head;

        if (head == nullptr)
        {
            cout << "No student added\n";
        }
        else
        {
            int id;

            while (true) {
                cout << "Enter ID: ";
                cin >> id;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid number. Try again: ";
                }
                else {
                    break;
                }
            }
            int flag = -1;

            while (ptr != nullptr)
            {
                if (ptr->id == id)
                {
                    cout << "\n----------------------\n";
                    cout << "ID: " << ptr->id << endl;
                    cout << "Name: " << ptr->name << endl;
                    cout << "Age: " << ptr->Age << endl;
                    cout << "GPA: " << ptr->gpa << endl;
                    cout << "Grades:\n";

                    for (int i = 0; i < ptr->course_count; i++)
                    {
                        cout << ptr->grade[i].course
                            << " = " << ptr->grade[i].degree
                            << " (" << ptr->grade[i].hours << " hours)" << endl;
                    }

                    flag = 1;
                    break;
                }
                ptr = ptr->next;
            }

            if (flag == -1)
            {
                cout << "The student not found\n";
            }
        }
    }

    void delete_student()
    {
        node* ptr = head;
        node* del = nullptr;
        int flage = -1;
        int id;

        if (head == nullptr)
        {
            cout << "No student added\n";
            return;
        }

        while (true) {
            cout << "Enter ID: ";
            cin >> id;
            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore();
                cout << "Invalid number. Try again: ";
            }
            else {
                break;
            }
        }
        if (head->id == id)
        {

            del = head;
            head = head->next;
            delete[] del->grade;
            delete del;
            cout << "Deleted successfully.\n";
            return;
        }
        else
        {

            while (ptr->next != nullptr)
            {
                if (ptr->next->id == id)
                {
                    del = ptr->next;
                    ptr->next = ptr->next->next;
                    flage = 1;
                    break;
                }
                ptr = ptr->next;
            }
        }

        if (flage == -1)
        {
            cout << "Student not found\n";
        }
        else
        {
            delete[] del->grade;
            delete del;
            cout << "Deleted successfully.\n";
        }
    }

    void update_student() {
        if (head == nullptr) {
            cout << "No student added\n";
            return;
        }

        int id;
        cout << "Enter student ID: ";
        cin >> id;

        node* ptr = head;

        while (ptr != nullptr) {
            if (ptr->id == id) {
                cout << "\nWhat do you want to update?\n";
                cout << "1- Name\n";
                cout << "2- Age\n";
                cout << "3- Update a course\n";
                cout << "4- Update all courses\n";
                cout << "Choose: ";

                int choice;
                cin >> choice;

                switch (choice) {
                case 1:

                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, ptr->name);
                    cout << "Name updated successfully!\n";
                    break;

                case 2:
                    cout << "Enter new age: ";
                    while (true) {
                        cin >> ptr->Age;
                        if (cin.fail() || ptr->Age < 0) {
                            cin.clear();
                            cin.ignore();
                            cout << "Invalid number. Try again: ";
                        }
                        else {
                            cout << "Age updated successfully!\n";
                            break;
                        }
                    }
                    break;

                case 3: {
                    if (ptr->course_count == 0) {
                        cout << "No courses found!\n";
                        break;
                    }
                    cout << "\nCourses:\n";
                    for (int i = 0; i < ptr->course_count; i++)
                        cout << i + 1 << "- " << ptr->grade[i].course
                        << " = " << ptr->grade[i].degree
                        << " (" << ptr->grade[i].hours << " hours)\n";

                    int c;
                    while (true) {
                        cout << "Choose course number to update: ";
                        cin >> c;
                        if (cin.fail() || c < 1 || c > ptr->course_count) {
                            cin.clear();
                            cin.ignore();
                            cout << "Invalid number. Try again: ";
                        }
                        else {
                            break;
                        }
                    }
                    while (true) {
                        cout << "Enter new grade: ";
                        cin >> ptr->grade[c - 1].degree;
                        if (cin.fail() || ptr->grade[c - 1].degree < 0 || ptr->grade[c - 1].degree > 100) {
                            cin.clear();
                            cin.ignore();
                            cout << "Invalid grade (0-100). Try again: ";
                        }
                        else {
                            break;
                        }
                    }
                    while (true) {
                        cout << "Enter new hours: ";
                        cin >> ptr->grade[c - 1].hours;
                        if (cin.fail() || ptr->grade[c - 1].hours < 0) {
                            cin.clear();
                            cin.ignore();
                            cout << "Invalid hours. Try again: ";
                        }
                        else {
                            break;
                        }
                    }
                    break;
                }

                case 4: {
                    if (ptr->course_count == 0) {
                        cout << "No courses found!\n";
                        break;
                    }
                    for (int i = 0; i < ptr->course_count; i++) {
                        cout << "Course: " << ptr->grade[i].course << endl;
                        while (true) {
                            cout << "Enter new grade: ";
                            cin >> ptr->grade[i].degree;
                            if (cin.fail() || ptr->grade[i].degree < 0 || ptr->grade[i].degree > 100) {
                                cin.clear();
                                cin.ignore();
                                cout << "Invalid grade (0-100). Try again: ";
                            }
                            else {
                                break;
                            }
                        }
                        while (true) {
                            cout << "Enter new hours: ";
                            cin >> ptr->grade[i].hours;
                            if (cin.fail() || ptr->grade[i].hours < 0) {
                                cin.clear();
                                cin.ignore();
                                cout << "Invalid hours. Try again: ";
                            }
                            else {
                                break;
                            }
                        }
                    }
                    break;
                }

                default:
                    cout << "Invalid choice!\n";
                    return;
                }

                float total_points = 0;
                int total_hours = 0;
                for (int i = 0; i < ptr->course_count; i++) {
                    total_points += ptr->grade[i].degree * ptr->grade[i].hours;
                    total_hours += ptr->grade[i].hours;
                }
                if (total_hours > 0)
                    ptr->gpa = (total_points / total_hours) * 4 / 100;
                else
                    ptr->gpa = 0;

                cout << "Update completed! New GPA: " << ptr->gpa << "\n";
                return;
            }
            ptr = ptr->next;
        }

        cout << "Student not found!\n";
    }

    void swap_nodes(node* a, node* b) {
        swap(a->id, b->id);
        swap(a->name, b->name);
        swap(a->Age, b->Age);
        swap(a->gpa, b->gpa);
        swap(a->course_count, b->course_count);
        swap(a->grade, b->grade);
    }

    void sort_students() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Not enough students to sort.\n";
            return;
        }

        cout << "Sort by:\n";
        cout << "1- Name (ascending)\n";
        cout << "2- GPA (ascending)\n";
        cout << "3- Age (ascending)\n";
        cout << "4- ID (ascending)\n";
        cout << "Choose: ";
        int sort_by;
        while (true) {
            cin >> sort_by;
            if (cin.fail() || sort_by < 1 || sort_by > 4) {
                cin.clear();
                cin.ignore();
                cout << "Invalid choice. Try again: ";
            }
            else {
                break;
            }
        }

        bool swapped;
        do {
            swapped = false;
            node* ptr = head;
            while (ptr->next != nullptr) {
                bool should_swap = false;
                if (sort_by == 1) {
                    if (ptr->name > ptr->next->name) should_swap = true;
                }
                else if (sort_by == 2) {
                    if (ptr->gpa > ptr->next->gpa) should_swap = true;
                }
                else if (sort_by == 3) {
                    if (ptr->Age > ptr->next->Age) should_swap = true;
                }
                else if (sort_by == 4) {
                    if (ptr->id > ptr->next->id) should_swap = true;
                }
                if (should_swap) {
                    swap_nodes(ptr, ptr->next);
                    swapped = true;
                }
                ptr = ptr->next;
            }
        } while (swapped);

        cout << "Students sorted successfully!\n";
    }

};

linked_list list1;

void add()
{
    int id, Age, course_count;
    string name;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    while (true) {
        cout << "Enter ID: ";
        cin >> id;
        if (cin.fail() || id < 0) {
            cin.clear();
            cin.ignore();
            cout << "Invalid number. Try again: ";
        }
        else {
            break;
        }
    }
    if (list1.id_exists(id)) {
        cout << "Warning: This ID already exists! Student not added.\n";
        return add();
    }
    while (true) {
        cout << "Enter Age: ";
        cin >> Age;
        if (cin.fail() || Age < 0) {
            cin.clear();
            cin.ignore();
            cout << "Invalid number. Try again: ";
        }
        else {
            break;
        }
    }
    while (true) {
        cout << "How many grades? ";
        cin >> course_count;
        if (cin.fail() || course_count < 0) {
            cin.clear();
            cin.ignore();
            cout << "Invalid number. Try again: ";
        }
        else {
            break;
        }
    }
    Grade* grade = new Grade[course_count];
    for (int i = 0; i < course_count; i++)
    {
        cout << "Enter course name: ";
        cin.ignore();
        getline(cin, grade[i].course);
        while (true) {
            cout << "Enter grade degree: ";
            cin >> grade[i].degree;
            if (cin.fail() || grade[i].degree < 0 || grade[i].degree > 100) {
                cin.clear();
                cin.ignore();
                cout << "Invalid grade (0-100). Try again: ";
            }
            else {
                break;
            }
        }
        while (true) {
            cout << "Enter course hours: ";
            cin >> grade[i].hours;
            if (cin.fail() || grade[i].hours < 0) {
                cin.clear();
                cin.ignore();
                cout << "Invalid hours. Try again: ";
            }
            else {
                break;
            }
        }
    }
    list1.insert_stud(id, name, Age, grade, course_count);
    delete[] grade;
    cout << "Student Added Successfully!\n";
}

int main()
{
    int choice = 0;

    while (choice != 7)
    {
        cout << "1: Add student\n";
        cout << "2: Search student\n";
        cout << "3: Delete student\n";
        cout << "4: Display all student\n";
        cout << "5: Update student\n";
        cout << "6: Sort students\n";
        cout << "7: Exit\n";
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout << "Invalid number. Try again: ";
            }
            else {
                break;
            }
        }

        switch (choice)
        {
        case 1:
        {
            char a = 'y';
            while (a != 'n')
            {
                add();
                cout << "If you want to add more (y), if not (n): ";
                cin >> a;
            }
            break;
        }
        case 2:
            list1.search_stud();
            break;
        case 3:
            list1.delete_student();
            break;
        case 4:
            list1.display();
            break;
        case 5:
            list1.update_student();
            break;
        case 6:
            list1.sort_students();
            break;
        case 7:
            cout << "Exit........\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
