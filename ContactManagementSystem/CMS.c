#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"

struct Contact {
    char name[50];
    char phone[15];
    char group[10];
    int isFavourite;
    char email[40];
    struct Contact *next;
};

struct Contact *head = NULL;

struct Contact* createContact(char name[], char phone[], char group[], char email[]) {
    struct Contact *newContact = malloc(sizeof(struct Contact));
    if (newContact == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strncpy(newContact->name, name, sizeof(newContact->name) - 1);
    newContact->name[sizeof(newContact->name) - 1] = '\0';
    strncpy(newContact->phone, phone, sizeof(newContact->phone) - 1);
    newContact->phone[sizeof(newContact->phone) - 1] = '\0';
    strncpy(newContact->group, group, sizeof(newContact->group) - 1);
    newContact->group[sizeof(newContact->group) - 1] = '\0';
    strncpy(newContact->email, email, sizeof(newContact->email) - 1);
    newContact->email[sizeof(newContact->email) - 1] = '\0';

    newContact->isFavourite = 0;
    newContact->next = NULL;
    return newContact;
}

void addContact(char name[], char phone[], char group[], char email[]) {
    struct Contact *newContact = createContact(name, phone, group, email);
    if (head == NULL) {
        head = newContact;
    } else {
        struct Contact *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newContact;
    }
    printf(GREEN "\nContact added successfully!\n" RESET);
}

void displayContacts() {
    if (head == NULL) {
        printf(RED "\nNo contacts available.\n" RESET);
        return;
    }

    printf(CYAN "\n--- Contact List ---\n" RESET);
    struct Contact *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->group, "Friends") == 0) {
            printf(BLUE "Name: %s | Phone: %s | Email: %s | Group: %s\n" RESET,
                   temp->name, temp->phone, temp->email, temp->group);
        } else if (strcmp(temp->group, "Family") == 0) {
            printf(YELLOW "Name: %s | Phone: %s | Email: %s | Group: %s\n" RESET,
                   temp->name, temp->phone, temp->email, temp->group);
        } else {
            printf("Name: %s | Phone: %s | Email: %s | Group: %s\n",
                   temp->name, temp->phone, temp->email, temp->group);
        }
        temp = temp->next;
    }
}

void displayGroup(char group[]) {
    if (head == NULL) {
        printf(RED "\nNo contacts available.\n" RESET);
        return;
    }

    printf(CYAN "\n--- %s Contacts ---\n" RESET, group);
    struct Contact *temp = head;
    int found = 0;

    while (temp != NULL) {
        if (strcmp(temp->group, group) == 0) {
            found = 1;
            if (strcmp(group, "Friends") == 0)
                printf(BLUE "Name: %s | Phone: %s | Email: %s\n" RESET, temp->name, temp->phone, temp->email);
            else if (strcmp(group, "Family") == 0)
                printf(YELLOW "Name: %s | Phone: %s | Email: %s\n" RESET, temp->name, temp->phone, temp->email);
        }
        temp = temp->next;
    }

    if (!found)
        printf(RED "No contacts in this group.\n" RESET);
}

void searchContact(char name[]) {
    struct Contact *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf(GREEN "\nContact Found!\n" RESET);
            printf("Name: %s | Phone: %s | Email: %s | Group: %s\n",
                   temp->name, temp->phone, temp->email, temp->group);
            return;
        }
        temp = temp->next;
    }
    printf(RED "\nContact not found.\n" RESET);
}

void deleteContact(char name[]) {
    struct Contact *temp = head, *prev = NULL;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf(RED "\nContact not found.\n" RESET);
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf(GREEN "\nContact deleted successfully!\n" RESET);
}

void markFavourites() {
    char name[50];
    printf("Enter name to Mark/Unmark Favourite: ");
    scanf("%s", name);

    struct Contact *temp = head;
    while (temp != NULL && strcmp(temp->name, name) != 0)
        temp = temp->next;

    if (temp == NULL) {
        printf(RED "Contact not found!\n" RESET);
        return;
    }

    temp->isFavourite = !temp->isFavourite;
    printf(GREEN "Contact %s is now %s Favourite.\n" RESET,
           temp->name, temp->isFavourite ? "Marked as" : "Removed from");
}

void displayFavourites() {
    struct Contact *temp = head;
    int found = 0;

    printf(CYAN "\n--- Favourite Contacts ---\n" RESET);
    while (temp != NULL) {
        if (temp->isFavourite) {
            printf("Name: %s | Phone: %s | Email: %s\n",
                   temp->name, temp->phone, temp->email);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf(RED "No favourite contacts available.\n" RESET);
}

int main() {
    int choice;
    char name[50], phone[15], group[10], email[40];

    do {
        printf(CYAN "\n===== Contact Management System =====\n" RESET);
        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Display Friends\n");
        printf("4. Display Family\n");
        printf("5. Search Contact\n");
        printf("6. Delete Contact\n");
        printf("7. Mark/Unmark Favourite Contacts\n");
        printf("8. Display Favourite Contacts\n");
        printf("9. Exit\n");
        printf("0. Exit Immediately\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf(GREEN "\nExiting immediately... Goodbye!\n" RESET);
            break;
        }

        getchar();

        switch (choice) {
            case 1:
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Enter Phone: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = 0;

                printf("Enter Email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = 0;

                printf("Enter Group (Friends/Family): ");
                fgets(group, sizeof(group), stdin);
                group[strcspn(group, "\n")] = 0;

                addContact(name, phone, group, email);
                break;

            case 2:
                displayContacts();
                break;
            case 3:
                displayGroup("Friends");
                break;
            case 4:
                displayGroup("Family");
                break;
            case 5:
                printf("Enter name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                searchContact(name);
                break;
            case 6:
                printf("Enter name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                deleteContact(name);
                break;
            case 7:
                markFavourites();
                break;
            case 8:
                displayFavourites();
                break;
            case 9:
                printf(GREEN "\nExiting... Goodbye!\n" RESET);
                break;
            default:
                printf(RED "\nInvalid choice. Try again.\n" RESET);
        }
    } while (choice != 9);

    return 0;
}
