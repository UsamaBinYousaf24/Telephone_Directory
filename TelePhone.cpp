#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define PINK "\033[38;5;206m"
#define ORANGE "\033[38;5;208m"
#define PURPLE "\033[38;5;165m"

using namespace std;

class nodeHistory
{
public:
    string data;
    nodeHistory *next;
    nodeHistory(string op)
    {
        data = op;
        next = NULL;
    }
};

class StackHistory
{
    nodeHistory *top;

public:
    StackHistory()
    {
        top = NULL;
    }
    void push(string val)
    {
        nodeHistory *n = new nodeHistory(val);
        if (top == NULL)
        {
            top = n;
            return;
        }
        n->next = top;
        top = n;
    }
    //
    string pop()
    {
        string temp = top->data;
        top = top->next;
        return temp;
    }

    void displayStack()
    {
        nodeHistory *temp = top;
        int i = 1;
        cout << PURPLE << "HISTORY of recent action" << RESET << endl;
        while (temp != NULL)
        {
            cout << PINK << i++ << ". " << YELLOW << temp->data << RESET << endl;
            temp = temp->next;
        }
        cout << RED << "Thats all till  now" << RESET << endl;
    }
};

class Contact
{
public:
    string name;
    string phoneNumber;
    string email;

    // Default constructor
    Contact() : name(""), phoneNumber(""), email("") {}

    // Parameterized constructor
    Contact(string n, string phone, string e)
        : name(n), phoneNumber(phone), email(e) {}
};

class Node
{
public:
    Contact data;
    Node *next;

    Node(Contact contact) : data(contact), next(NULL) {}
};

class Queue
{
    Node *front;
    Node *rear;

public:
    Queue(Node *f = NULL, Node *r = NULL) : front(f), rear(r) {}

    void Enqueue(Contact contact)
    {
        Node *n = new Node(contact);
        if (front == NULL && rear == NULL)
        {
            front = rear = n;
        }
        else
        {
            rear->next = n;
            rear = n;
        }
    }

    bool Dequeue(Contact &dequeued)
    {
        if (front == NULL)
        {
            return false;
        }
        Node *temp = front;
        dequeued = temp->data;
        front = front->next;
        delete temp;
        if (front == NULL)
        {
            rear = NULL;
        }
        return true;
    }

    bool IsEmpty()
    {
        return front == NULL;
    }
};

class Stack
{
    Node *top;

public:
    Stack() : top(NULL) {}

    void Push(Contact contact)
    {
        Node *n = new Node(contact);
        if (top == NULL)
        {
            top = n;
        }
        else
        {
            n->next = top;
            top = n;
        }
    }

    bool Pop(Contact &popped)
    {
        if (top == NULL)
        {
            return false;
        }
        Node *temp = top;
        popped = temp->data;
        top = top->next;
        delete temp;
        return true;
    }

    bool IsEmpty()
    {
        return top == NULL;
    }

    void display()
    {
        Node *temp = top;
        while (temp != NULL)
        {
            cout << temp->data.name << " " << temp->data.phoneNumber << endl;
            temp = temp->next;
        }
        cout << endl;
    }
};

class AddressBook
{
private:
    Node *head;
    Contact lastOperation;
    Stack operationHistoryStack; // Stack to keep track of history of operations
    Queue recentlyAddedContactsQueue;

public:
    AddressBook() : head(NULL) {}

    ~AddressBook()
    {
        while (head != NULL)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addContact(Contact &contact)
    {
        Node *newNode = new Node(contact);
        newNode->next = head;
        head = newNode;

        // Add to the recently added contacts queue
        recentlyAddedContactsQueue.Enqueue(contact);

        // Clear the undo stack when a new contact is added
        // while (!undoStack.IsEmpty())
        // {
        //     Contact tempContact;
        //     undoStack.Pop(tempContact);
        // }

        // Push the add operation to the operation history stack
        operationHistoryStack.Push(contact);
    }

    
    Contact getLastOperation()
    {
        // Check if the operation history stack is not empty
        if (!operationHistoryStack.IsEmpty())
        {
            // Create a temporary variable to store the last operation
            Contact lastOperation;

            // Pop the top of the operation history stack to get the last operation
            operationHistoryStack.Pop(lastOperation);

            // Push it back to maintain the original stack state
            operationHistoryStack.Push(lastOperation);

            // Return the last operation
            return lastOperation;
        }
        else
        {
        
            return Contact();
        }
    }

    void displayRecentlyAddedContacts()
    {
        cout << BLUE << "\nRecently Added Contacts:" << RESET << endl;

        while (!recentlyAddedContactsQueue.IsEmpty())
        {
            Contact recentContact;
            recentlyAddedContactsQueue.Dequeue(recentContact);

            cout << "Name: " << recentContact.name << endl;
            cout << "Phone: " << recentContact.phoneNumber << endl;
            cout << "Email: " << recentContact.email << endl;
            cout << "-------------------------" << endl;
        }
    }

    void displayOperationHistory()
    {
        Stack tempStack;

        // Display the operations in the original order
        cout << ORANGE << "Operation History:" << RESET << endl;

        while (!operationHistoryStack.IsEmpty())
        {
            Contact operation;
            operationHistoryStack.Pop(operation);
            tempStack.Push(operation);

            // Display details of each operation (customize this part based on your needs)
            cout << "Operation Type: ";
            if (operation.name == "" && operation.phoneNumber == "" && operation.email == "")
            {
                cout << "Undo or Display" << endl;
            }
            else if (operation.name == "")
            {
                cout << "Delete" << endl;
            }
            else if (operation.phoneNumber == "" && operation.email == "")
            {
                cout << "Sorting or Modification" << endl;
            }
            else
            {
                cout << "Add" << endl;
            }

            if (operation.name != "")
            {
                // Display contact details for add operation
                cout << "Contact Details:" << endl;
                cout << "Name: " << operation.name << endl;
                cout << "Phone: " << operation.phoneNumber << endl;
                cout << "Email: " << operation.email << endl;
            }

            if (operation.name == "" && operation.phoneNumber == "" && operation.email == "")
            {
                // Additional information for undo and display operations
                if (operationHistoryStack.IsEmpty())
                {
                    cout << "Additional Information: No more operations to undo" << endl;
                }
                else
                {
                    cout << "Additional Information: Undo operation" << endl;
                }
            }
            else if (operation.name == "" && operation.phoneNumber == "" && operation.email == "" && tempStack.IsEmpty())
            {
                cout << "Additional Information: Display operation" << endl;
            }

            // Display additional information for sorting or modification
            if (operation.name == "" && operation.phoneNumber == "" && operation.email == "")
            {
                if (operation.phoneNumber == "")
                {
                    cout << "Additional Information: Sorting" << endl;
                }
                else
                {
                    cout << "Additional Information: Modification" << endl;
                }
            }

            cout << "-------------------------" << endl;
        }

        // Restore the original order by pushing elements back to operationHistoryStack
        while (!tempStack.IsEmpty())
        {
            Contact operation;
            tempStack.Pop(operation);
            operationHistoryStack.Push(operation);
        }
    }

    Contact *searchContact(string name)
    {
        Node *current = head;
        while (current != NULL)
        {
            if (current->data.name == name)
            {
                return &(current->data);
            }
            current = current->next;
        }
        return NULL;
    }

    void deleteContact(string name)
    {
        Node *current = head;
        Node *prev = NULL;

        while (current != NULL && current->data.name != name)
        {
            prev = current;
            current = current->next;
        }

        if (current != NULL)
        {
            if (prev != NULL)
            {
                prev->next = current->next;
            }
            else
            {
                head = current->next;
            }

            delete current;
            cout << PURPLE << "Contact deleted successfully." << RESET << endl;

            // Push the delete operation to the undo stack
            Contact deletedContact(name, current->data.phoneNumber, current->data.email);
            //undoStack.Push(deletedContact);
        }
        else
        {
            cout << RED << "Contact not found." << RESET << endl;
        }
    }

    void sortContacts()
    {
        if (head == NULL || head->next == NULL)
        {
            return;
        }

        bool swapped;
        Node *ptr1;
        Node *lptr = NULL;

        do
        {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr)
            {
                if (ptr1->data.name > ptr1->next->data.name)
                {
                    Contact temp = ptr1->data;
                    ptr1->data = ptr1->next->data;
                    ptr1->next->data = temp;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        cout << GREEN << "Contacts sorted alphabetically." << RESET << endl;
    }

    void displayContacts()
    {
        Node *current = head;
        while (current != NULL)
        {
            cout << BLUE << "Name: " << current->data.name << RESET << endl;
            cout << CYAN << "Phone: " << current->data.phoneNumber << RESET << endl;
            cout << PURPLE << "Email: " << current->data.email << RESET << endl;
            cout << "-------------------------" << endl;
            current = current->next;
        }
    }

    void modifyContact(string name)
    {
        Node *current = head;
        while (current != NULL)
        {
            if (current->data.name == name)
            {
                cout << MAGENTA << "Enter new name:" << RESET;
                cin.ignore();

                getline(cin, current->data.name);

                cout << MAGENTA << "Enter new phone number: " << RESET;
                cin >> current->data.phoneNumber;

                cout << MAGENTA << "Enter new email: " << RESET;
                cin >> current->data.email;

                cout << GREEN << "Contact modified successfully." << RESET << endl;

                // Push the modification operation to the undo stack
                Contact originalContact(name, current->data.phoneNumber, current->data.email);
                //undoStack.Push(originalContact);

                return;
            }
            current = current->next;
        }
        cout << RED << "Contact not found." << RESET << endl;
    }
};

class BaseInterface
{
protected:
    AddressBook &addressBook;

public:
    BaseInterface(AddressBook &book) : addressBook(book) {}

    virtual void execute() = 0;
    virtual void displayOperationHistory() = 0;
};

class User : public BaseInterface
{

    Stack operationHistoryStack;

public:
    User(AddressBook &book) : BaseInterface(book) {}
    void displayOperationHistory() override
    {
        // Display the operation history stack
        operationHistoryStack.display();
    }

    void execute() override
    {
        int choice;
        string name, phone, email;
        Contact contact;
        Contact *foundContact = NULL;
        StackHistory stack;
        bool state = true;

        while (state)
        {
            cout << ORANGE << "\nUser Interface Menu:" << RESET << endl;
            cout << CYAN << "1. Add Contact" << endl;
            cout << "2. Search Contact" << endl;
            cout << "3. Display Contacts" << endl;
            cout << "4. Modify Contact" << endl;
            cout << "5. Sort Contact" << endl;
            cout << "6. Display Recently Added Contacts" << endl;
            cout << "7. Display Operation History" << endl; // Added display recently added contacts option
            cout << "8. Exit to Main Menu" << RESET << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            system("cls");

            switch (choice)
            {
            case 1:
                // for history
                {
                    stack.push("Added Contact...");
                    cout << BLUE << "Enter name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter phone number: ";
                    cin >> phone;
                    cout << "Enter email: ";
                    cin >> email;

                    contact = Contact(name, phone, email);
                    addressBook.addContact(contact);
                    operationHistoryStack.Push(contact); // Push the add operation to the user's operation history stack

                    cout << GREEN << "Contact added successfully." << RESET << endl;
                    break;
                }

            case 2:
            {
                stack.push("Searched Contact...");
                string name;
                cout << YELLOW << "Enter name to search: ";
                cin.ignore();
                getline(cin, name);
                Contact *foundContact = addressBook.searchContact(name);

                if (foundContact != NULL)
                {
                    cout << GREEN << "Contact found:" << endl;
                    cout << "Name: " << foundContact->name << endl;
                    cout << "Phone: " << foundContact->phoneNumber << endl;
                    cout << "Email: " << foundContact->email << RESET << endl;
                }
                else
                {
                    cout << RED << "Contact not found." << RESET << endl;
                }
                break;
            }

            case 3:
                stack.push("Displayed Contact...");
                cout << GREEN << "\nAll Contacts:" << RESET << endl;
                addressBook.displayContacts();
                break;

            case 4:
                stack.push("Modified Contact...");
                cout << PURPLE << "Enter name to modify: ";
                cin.ignore();
                getline(cin, name);

                addressBook.modifyContact(name);
                operationHistoryStack.Push(contact); // Push the modification operation to the user's operation history stack

                break;

            case 5:
                stack.push("Sorted Contact...");
                cout << BLUE << "\nAll Contacts (sorted alphabetically):" << RESET << endl;
                addressBook.sortContacts();
                addressBook.displayContacts();
                break;

        
            case 6:
                stack.push("Displayed Recently added  Contacts...");
                cout << BLUE << "\nRecently Added Contacts:" << RESET << endl;
                addressBook.displayRecentlyAddedContacts();
                break;

            case 7:
                stack.displayStack();
                break;

            case 8:
                cout << WHITE << "Exiting the user Interface. Returning to Main Menu." << RESET << endl;
                state = false;
                break;

            default:
                cout << RED << "Invalid choice. Please enter a valid option." << RESET << endl;
            }
        }
        system("cls");
    }
};

class Admin : public BaseInterface
{
private:
    const string adminPassword = "admin123";
    Stack operationHistoryStack;
    Contact lastOperation; // Keep track of the last operation

public:
    Admin(AddressBook &book) : BaseInterface(book) {}

    void displayOperationHistory() override
    {
        // Display the operation history stack
        operationHistoryStack.display();
    }

    void execute() override
    {
        string password;
        StackHistory history;
        cout << GREEN << "Enter Admin Password: ";
        char ch;
        int i = 0;
        while (1)
        {
            ch = _getch();
            if (ch == 13)
                break;
            cout << '*';
            password.push_back(ch);
            i++;
        }

        if (password != adminPassword)
        {
            cout << RED << "\nIncorrect password. Access denied." << RESET << endl;
            return;
        }
        system("cls");
        // string fileName;
        int choice;

        do
        {
            cout << ORANGE << "\nAdmin Interface Menu:" << RESET << endl;
            cout << CYAN << "1. Add Contact" << endl;
            cout << "2. Search Contact" << endl;
            cout << "3. Delete Contact" << endl;
            cout << "4. Display Contacts" << endl;
            cout << "5. Modify Contact" << endl;
            cout << "6. Sort Contacts" << endl;
            cout << "7. Display Recently Added Contacts" << endl;
            cout << "8. Display Operation History" << endl;
            cout << "9. Exit to Main Menu" << RESET << endl;
            cout << GREEN << "Enter your choice: " << RESET;
            cin >> choice;
            system("cls");

            switch (choice)
            {
            case 1:
            {
                history.push("Added Contact...");
                string name, phone, email;
                cout << GREEN << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone number: ";
                cin >> phone;
                cout << "Enter email: ";
                cin >> email;

                Contact newContact(name, phone, email);
                addressBook.addContact(newContact);
                // operationHistoryStack.Push(newContact);
                cout << GREEN << "Contact added successfully." << RESET << endl;
                break;
            }

            case 2:
            {
                history.push("Searched Contact...");
                string searchName;
                cout << YELLOW << "Enter name to search: " << RESET;
                cin.ignore();
                getline(cin, searchName);

                Contact *foundContact = addressBook.searchContact(searchName);

                if (foundContact != NULL)
                {
                    cout << GREEN << "Contact found:" << endl;
                    cout << "Name: " << foundContact->name << endl;
                    cout << "Phone: " << foundContact->phoneNumber << endl;
                    cout << "Email: " << foundContact->email << RESET << endl;
                }
                else
                {
                    cout << RED << "Contact not found." << RESET << endl;
                }
                break;
            }

            case 3:
            {
                history.push("Deleted Contact...");
                string deleteName;
                cout << RED << "Enter name to delete: " << RESET;
                cin.ignore();
                getline(cin, deleteName);

                addressBook.deleteContact(deleteName);
                break;
            }

            case 4:
                history.push("Displayed Contact...");
                cout << GREEN << "\nAll Contacts:" << RESET << endl;
                addressBook.displayContacts();
                break;

            case 5:
            {
                history.push("Modified Contact...");
                string modifyName;
                cout << PURPLE << "Enter name to modify: " << RESET;
                cin.ignore();
                getline(cin, modifyName);

                addressBook.modifyContact(modifyName);
                break;
            }

            case 6:
                history.push("Sorted");
                cout << BLUE << "\nAll Contacts (sorted alphabetically):" << RESET << endl;
                addressBook.sortContacts();
                addressBook.displayContacts();
                break;


            case 7:
            {
                // Display recently added contacts
                history.push("Displayed recently Added");
                addressBook.displayRecentlyAddedContacts();
                break;
            }

            case 8:
                history.displayStack();
                break;

            case 9:
                cout << WHITE << "Exiting the Admin Interface. Returning to Main Menu." << RESET << endl;
                break;

            default:
                cout << RED << "Invalid choice. Please enter a valid option." << RESET << endl;
            }
        } while (choice != 9); // Corrected the closing parenthesis location
        system("cls");
    }
};

void loadingScreen()
{
    cout << YELLOW << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tA PROGRAM FOR BEGINNERS" << RESET;
    Sleep(3000);
    system("cls");
    for (int i = 1; i <= 100; ++i)
    {
        Sleep(5);
        system("cls");
        cout << RED << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tLOADING " << i << "%" << RESET << endl;
        if (i == 100)
            Sleep(2000);
    }
    system("PAUSE");
    system("cls");
}


int main()
{
    AddressBook myAddressBook;
    User userInterface(myAddressBook);
    Admin adminInterface(myAddressBook);

    int userType;
    loadingScreen();
    do
    {
        cout << BLUE << "Select User Type:" << RESET << endl;
        cout << GREEN << "1. User" << endl;
        cout << "2. Admin" << endl;
        cout << "3. Exit" << RESET << endl;
        cout << YELLOW << "Enter your choice: " << RESET;
        cin >> userType;
        BaseInterface *Interface;

        switch (userType)
        {
        case 1:
            Interface = new User(myAddressBook); // Pass myAddressBook to User constructor
            break;
        case 2:
            Interface = new Admin(myAddressBook); // Pass myAddressBook to Admin constructor
            break;
        case 3:
            cout << GREEN << "Exiting the program. Goodbye!" << RESET << endl;
            return 0;
        default:
            cout << RED << "Invalid user type. Please enter a valid option." << RESET << endl;
            continue;
        }
        system("cls");

        Interface->execute();

        delete Interface;

        if (userType == 1)
        {
            cout << BLUE << "Do you want to switch to the main menu? (1: Yes, 2: No): " << RESET;
            int switchOption;
            cin >> switchOption;

            if (switchOption == 1)
            {
                userType = 2; // Switch to Admin Interface
            }
            else
            {
                userType = 3; // Exit
            }
        }
    } while (userType != 3);
    system("cls");

    return 0;
}