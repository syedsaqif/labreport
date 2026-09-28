#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head = NULL;

int readInt(void)
{
    int x, r, c;

    while ((r = scanf("%d", &x)) != 1) {
        if (r == EOF) {
            printf("\nInput ended. Exiting program.\n");
            exit(0);
        }
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("Invalid input! Please enter an integer: ");
    }
    return x;
}

struct node *newNode(int value)
{
    struct node *n = (struct node *)malloc(sizeof(struct node));

    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    n->data = value;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

void addFirst(int value)
{
    struct node *n = newNode(value);

    n->next = head;
    if (head != NULL)
        head->prev = n;
    head = n;
}

void addAfter(struct node *p, int value)
{
    struct node *n = newNode(value);

    n->prev = p;
    n->next = p->next;
    if (p->next != NULL)
        p->next->prev = n;
    p->next = n;
}

void addLast(int value)
{
    struct node *temp = head;

    if (head == NULL) {
        addFirst(value);
        return;
    }
    while (temp->next != NULL)
        temp = temp->next;
    addAfter(temp, value);
}

void removeNode(struct node *p)
{
    if (p->prev != NULL)
        p->prev->next = p->next;
    else
        head = p->next;

    if (p->next != NULL)
        p->next->prev = p->prev;

    free(p);
}

int countNodes(void)
{
    struct node *temp = head;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

struct node *getNodeAt(int pos)
{
    struct node *temp = head;
    int i;

    if (pos < 1)
        return NULL;
    for (i = 1; i < pos && temp != NULL; i++)
        temp = temp->next;
    return temp;
}

struct node *findNode(int key)
{
    struct node *temp = head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;
    return temp;
}

void freeList(void)
{
    struct node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void createList(void)
{
    int n, i, value;

    if (head != NULL) {
        freeList();
        printf("Old list deleted.\n");
    }

    printf("How many nodes do you want to create? ");
    n = readInt();

    if (n <= 0) {
        printf("Nothing created. The list is empty.\n");
        return;
    }

    for (i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        value = readInt();
        addLast(value);
    }
    printf("New list created with %d node(s).\n", n);
}

void printList(void)
{
    struct node *temp = head;

    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("List: NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insertAtFirst(void)
{
    int value;

    printf("Enter data to insert: ");
    value = readInt();
    addFirst(value);
    printf("%d inserted at the first node.\n", value);
}

void insertAtLast(void)
{
    int value;

    printf("Enter data to insert: ");
    value = readInt();
    addLast(value);
    printf("%d inserted at the last node.\n", value);
}

void insertAtPosition(void)
{
    int pos, value;
    int n = countNodes();

    printf("Enter position (1 to %d): ", n + 1);
    pos = readInt();

    if (pos < 1 || pos > n + 1) {
        printf("Invalid position! Valid positions are 1 to %d.\n", n + 1);
        return;
    }

    printf("Enter data to insert: ");
    value = readInt();

    if (pos == 1)
        addFirst(value);
    else
        addAfter(getNodeAt(pos - 1), value);

    printf("%d inserted at position %d.\n", value, pos);
}

void insertAfterData(void)
{
    int key, value;
    struct node *p;

    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("Enter the data after which you want to insert: ");
    key = readInt();

    p = findNode(key);
    if (p == NULL) {
        printf("%d not found in the list.\n", key);
        return;
    }

    printf("Enter new data to insert: ");
    value = readInt();
    addAfter(p, value);
    printf("%d inserted after %d.\n", value, key);
}

void deleteFirst(void)
{
    if (head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }
    printf("Deleted first node: %d\n", head->data);
    removeNode(head);
}

void deleteLast(void)
{
    struct node *temp = head;

    if (head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }
    while (temp->next != NULL)
        temp = temp->next;

    printf("Deleted last node: %d\n", temp->data);
    removeNode(temp);
}

void deleteAtPosition(void)
{
    int pos;
    int n = countNodes();
    struct node *p;

    if (head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }

    printf("Enter position to delete (1 to %d): ", n);
    pos = readInt();

    if (pos < 1 || pos > n) {
        printf("Invalid position! Valid positions are 1 to %d.\n", n);
        return;
    }

    p = getNodeAt(pos);
    printf("Deleted %d from position %d.\n", p->data, pos);
    removeNode(p);
}

void deleteData(void)
{
    int key;
    struct node *p;

    if (head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }

    printf("Enter the data to delete: ");
    key = readInt();

    p = findNode(key);
    if (p == NULL) {
        printf("%d not found in the list.\n", key);
        return;
    }

    removeNode(p);
    printf("Deleted %d (first occurrence) from the list.\n", key);
}

void countElements(void)
{
    printf("Number of elements in the list = %d\n", countNodes());
}

void searchPresence(void)
{
    int key;

    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("Enter the data to search: ");
    key = readInt();

    if (findNode(key) != NULL)
        printf("%d is present in the list.\n", key);
    else
        printf("%d is NOT present in the list.\n", key);
}

void searchPosition(void)
{
    struct node *temp = head;
    int key, pos = 1, found = 0;

    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("Enter the data to search: ");
    key = readInt();

    while (temp != NULL) {
        if (temp->data == key) {
            if (found)
                printf(", ");
            else
                printf("%d found at position(s): ", key);
            printf("%d", pos);
            found = 1;
        }
        temp = temp->next;
        pos++;
    }

    if (found)
        printf("\n");
    else
        printf("%d not found in the list.\n", key);
}

void searchCount(void)
{
    struct node *temp = head;
    int key, count = 0;

    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("Enter the data to search: ");
    key = readInt();

    while (temp != NULL) {
        if (temp->data == key)
            count++;
        temp = temp->next;
    }
    printf("%d is present %d time(s) in the list.\n", key, count);
}

void sortList(void)
{
    struct node *i, *end = NULL;
    int swapped, temp;

    if (head == NULL || head->next == NULL) {
        printf("Nothing to sort (list has less than 2 elements).\n");
        return;
    }

    do {
        swapped = 0;
        for (i = head; i->next != end; i = i->next) {
            if (i->data > i->next->data) {
                temp = i->data;
                i->data = i->next->data;
                i->next->data = temp;
                swapped = 1;
            }
        }
        end = i;
    } while (swapped);

    printf("List sorted in ascending order.\n");
}

void reverseList(void)
{
    struct node *current = head, *nextNode, *newHead = NULL;

    if (head == NULL || head->next == NULL) {
        printf("Nothing to reverse (list has less than 2 elements).\n");
        return;
    }

    while (current != NULL) {
        nextNode = current->next;
        current->next = current->prev;
        current->prev = nextNode;
        newHead = current;
        current = nextNode;
    }
    head = newHead;

    printf("List reversed.\n");
}

void showMenu(void)
{
    printf("\n=========== DOUBLY LINKED LIST ===========\n");
    printf(" 1. Create a new list\n");
    printf(" 2. Print the list\n");
    printf(" 3. Insert at the first node\n");
    printf(" 4. Insert at the last node\n");
    printf(" 5. Insert into a given position\n");
    printf(" 6. Insert after a given data\n");
    printf(" 7. Delete the first node\n");
    printf(" 8. Delete the last node\n");
    printf(" 9. Delete from a given position\n");
    printf("10. Delete a given data\n");
    printf("11. Count the number of elements\n");
    printf("12. Search to detect presence of a data\n");
    printf("13. Search to find the position of a data\n");
    printf("14. Search to find how many times a data is present\n");
    printf("15. Sort the list\n");
    printf("16. Reverse the list\n");
    printf("17. Exit\n");
    printf("==========================================\n");
}

int main(void)
{
    int choice;

    do {
        showMenu();
        printf("Enter your choice: ");
        choice = readInt();
        printf("\n");

        switch (choice) {
            case 1:  createList();          break;
            case 2:  printList();           break;
            case 3:  insertAtFirst();       break;
            case 4:  insertAtLast();        break;
            case 5:  insertAtPosition();    break;
            case 6:  insertAfterData();     break;
            case 7:  deleteFirst();         break;
            case 8:  deleteLast();          break;
            case 9:  deleteAtPosition();    break;
            case 10: deleteData();          break;
            case 11: countElements();       break;
            case 12: searchPresence();      break;
            case 13: searchPosition();      break;
            case 14: searchCount();         break;
            case 15: sortList();            break;
            case 16: reverseList();         break;
            case 17:
                freeList();
                printf("Program ended. Bye!\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 17.\n");
        }
    } while (choice != 17);

    return 0;
}



// ------------------------------ binary search -----------------------------------------------------


#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int readInt(void)
{
    int x, r, c;
    while ((r = scanf("%d", &x)) != 1)
    {
        if (r == EOF)
            exit(0);
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("Invalid input. Enter an integer: ");
    }
    return x;
}

int isSorted(int a[], int n)
{
    int i;
    for (i = 1; i < n; i++)
    {
        if (a[i - 1] > a[i])
            return 0;
    }
    return 1;
}

int createArray(int a[])
{
    int n, i;
    printf("Enter number of elements (1 to %d): ", MAX);
    n = readInt();
    if (n < 1 || n > MAX)
    {
        printf("Invalid size. Array not created.\n");
        return 0;
    }
    printf("Enter %d elements in ascending order:\n", n);
    for (i = 0; i < n; i++)
        a[i] = readInt();
    if (!isSorted(a, n))
    {
        printf("Elements are not in ascending order. Array not created.\n");
        return 0;
    }
    printf("Array created.\n");
    return n;
}

void display(int a[], int n)
{
    int i;
    if (n == 0)
    {
        printf("Array is empty.\n");
        return;
    }
    printf("Array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int binarySearch(int a[], int n, int key)
{
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (a[mid] == key)
            return mid;
        else if (key < a[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int main()
{
    int a[MAX], n = 0, choice, key, pos;
    while (1)
    {
        printf("\n===== BINARY SEARCH MENU =====\n");
        printf("1. Create sorted array\n");
        printf("2. Display array\n");
        printf("3. Binary search\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        choice = readInt();
        switch (choice)
        {
        case 1:
            n = createArray(a);
            break;
        case 2:
            display(a, n);
            break;
        case 3:
            if (n == 0)
            {
                printf("Create the array first.\n");
                break;
            }
            printf("Enter element to search: ");
            key = readInt();
            pos = binarySearch(a, n, key);
            if (pos == -1)
                printf("%d not found in the array.\n", key);
            else
                printf("%d found at index %d (position %d).\n", key, pos, pos + 1);
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}


//---------------------------  sorting   --------------------------------------



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int readInt(void)
{
    int x, r, c;
    while ((r = scanf("%d", &x)) != 1)
    {
        if (r == EOF)
            exit(0);
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("Invalid input. Enter an integer: ");
    }
    return x;
}

int readArray(int a[])
{
    int n, i;
    printf("Enter number of elements (1 to %d): ", MAX);
    n = readInt();
    if (n < 1 || n > MAX)
    {
        printf("Invalid size.\n");
        return 0;
    }
    printf("Enter %d elements:\n", n);
    for (i = 1; i <= n; i++)
        a[i] = readInt();
    return n;
}

void display(int a[], int n)
{
    int i;
    for (i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int modifiedBubbleSort(int a[], int n)
{
    int i, j, temp, swapped, passes = 0;
    for (i = 1; i < n; i++)
    {
        swapped = 0;
        passes++;
        for (j = 1; j <= n - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
    return passes;
}

void insertionSortWithSentinel(int a[], int n)
{
    int i, j, key;
    a[0] = INT_MIN;
    for (i = 2; i <= n; i++)
    {
        key = a[i];
        j = i - 1;
        while (a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void shellSort(int a[], int n)
{
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (i = gap + 1; i <= n; i++)
        {
            temp = a[i];
            for (j = i; j > gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];
            a[j] = temp;
        }
    }
}

int main()
{
    int a[MAX + 1], n, choice, passes = 0;
    while (1)
    {
        printf("\n===== SORTING MENU =====\n");
        printf("1. Modified Bubble Sort\n");
        printf("2. Insertion Sort using Sentinel\n");
        printf("3. Shell Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        choice = readInt();
        if (choice == 4)
            break;
        if (choice < 1 || choice > 3)
        {
            printf("Invalid choice. Try again.\n");
            continue;
        }
        n = readArray(a);
        if (n == 0)
            continue;
        printf("\nBefore sorting: ");
        display(a, n);
        switch (choice)
        {
        case 1:
            passes = modifiedBubbleSort(a, n);
            break;
        case 2:
            insertionSortWithSentinel(a, n);
            break;
        case 3:
            shellSort(a, n);
            break;
        }
        printf("After sorting : ");
        display(a, n);
        if (choice == 1)
            printf("Passes taken  : %d\n", passes);
    }
    return 0;
}


//---------------------------------------Quick merge -------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int readInt(void)
{
    int x, r, c;
    while ((r = scanf("%d", &x)) != 1)
    {
        if (r == EOF)
            exit(0);
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("Invalid input. Enter an integer: ");
    }
    return x;
}

int readArray(int a[])
{
    int n, i;
    printf("Enter number of elements (1 to %d): ", MAX);
    n = readInt();
    if (n < 1 || n > MAX)
    {
        printf("Invalid size.\n");
        return 0;
    }
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
        a[i] = readInt();
    return n;
}

void display(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int hasNegative(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (a[i] < 0)
            return 1;
    }
    return 0;
}

int partition(int a[], int low, int high)
{
    int pivot = a[low], i = low + 1, j = high, temp;
    while (1)
    {
        while (i <= high && a[i] <= pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i < j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        else
            break;
    }
    temp = a[low];
    a[low] = a[j];
    a[j] = temp;
    return j;
}

void quickSort(int a[], int low, int high)
{
    int p;
    if (low < high)
    {
        p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

void merge(int a[], int low, int mid, int high)
{
    int b[MAX], i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        b[k] = a[i];
        i++;
        k++;
    }
    while (j <= high)
    {
        b[k] = a[j];
        j++;
        k++;
    }
    for (k = low; k <= high; k++)
        a[k] = b[k];
}

void mergeSort(int a[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

int getMax(int a[], int n)
{
    int i, max = a[0];
    for (i = 1; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

void countingSortByDigit(int a[], int n, long long place)
{
    int output[MAX], count[10], i, digit;
    for (i = 0; i < 10; i++)
        count[i] = 0;
    for (i = 0; i < n; i++)
    {
        digit = (a[i] / place) % 10;
        count[digit]++;
    }
    for (i = 1; i < 10; i++)
        count[i] = count[i] + count[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        digit = (a[i] / place) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }
    for (i = 0; i < n; i++)
        a[i] = output[i];
}

void radixSort(int a[], int n)
{
    int max = getMax(a, n);
    long long place;
    for (place = 1; max / place > 0; place *= 10)
    {
        countingSortByDigit(a, n, place);
        printf("After sorting on digit place %lld: ", place);
        display(a, n);
    }
}

int main()
{
    int a[MAX], n, choice;
    while (1)
    {
        printf("\n===== SORTING MENU =====\n");
        printf("1. Quick Sort\n");
        printf("2. Merge Sort\n");
        printf("3. Radix Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        choice = readInt();
        if (choice == 4)
            break;
        if (choice < 1 || choice > 3)
        {
            printf("Invalid choice. Try again.\n");
            continue;
        }
        if (choice == 3)
            printf("Radix sort accepts only non-negative integers.\n");
        n = readArray(a);
        if (n == 0)
            continue;
        if (choice == 3 && hasNegative(a, n))
        {
            printf("Negative number found. Radix sort not performed.\n");
            continue;
        }
        printf("\nBefore sorting: ");
        display(a, n);
        switch (choice)
        {
        case 1:
            quickSort(a, 0, n - 1);
            break;
        case 2:
            mergeSort(a, 0, n - 1);
            break;
        case 3:
            radixSort(a, n);
            break;
        }
        printf("After sorting : ");
        display(a, n);
    }
    return 0;
}
