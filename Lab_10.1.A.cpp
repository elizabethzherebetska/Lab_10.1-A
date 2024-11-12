#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Otsinka { ZADOVILNO = 3, DOBRE, VIDMINNO };
enum Specialnist { KN, IT, ME, MF, FI };
string otsinkaStr[] = { "���������", "�����", "������" };
string specialnistStr[] = { "����'����� �����", "�������� ����������� ������������", "����������", "Գ����", "Գ������" };

struct Student {
    string prizv;
    unsigned kurs;
    Specialnist specialnist;
    int fizyka;
    int matematika;
    int informatika;
};

void Create(Student* students, const int N);
void Print(const Student* students, const int N);
double CalculateExcellentPercentage(const Student* students, const int N, int predmet);
void SortBySurname(Student* students, const int N);
int BinarySearchBySurname(const Student* students, const int N, const string& surname);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� �������� N: "; cin >> N;

    Student* students = new Student[N];

    int menuItem;
    do {
        cout << "\n������� ��:\n";
        cout << " [1] - �������� ����� ��� ��������\n";
        cout << " [2] - ���� ����� ��� ��������\n";
        cout << " [3] - ���������� ������� �������� � ������, ���������� �� �����������\n";
        cout << " [4] - ���������� �������� �� ��������\n";
        cout << " [5] - ����� �������� �� ��������\n";
        cout << " [0] - �����\n";
        cout << "������ ��������: "; cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(students, N);
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            cout << "³������ ��������, �� ����� '������' � ������: "
                << CalculateExcellentPercentage(students, N, 1) << "%" << endl;
            cout << "³������ ��������, �� ����� '������' � ����������: "
                << CalculateExcellentPercentage(students, N, 2) << "%" << endl;
            cout << "³������ ��������, �� ����� '������' � �����������: "
                << CalculateExcellentPercentage(students, N, 3) << "%" << endl;
            break;
        case 4:
            SortBySurname(students, N);
            cout << "�������� ����������� �� ��������.\n";
            Print(students, N); // ������ ���� ��� ��������
            break;
        case 5:
        {
            SortBySurname(students, N); // ���������� ����� �������
            string surname;
            cin.ignore();
            cout << "������ ������� ��� ������: ";
            getline(cin, surname);
            int index = BinarySearchBySurname(students, N, surname);
            if (index != -1) {
                cout << "�������� ��������:\n";
                cout << "| " << setw(15) << left << students[index].prizv
                    << "| " << setw(8) << right << students[index].kurs << " ";
                cout << "| " << setw(20) << left << specialnistStr[students[index].specialnist] << " ";
                cout << "| " << setw(8) << students[index].fizyka << " ";
                cout << "| " << setw(10) << students[index].matematika << " ";
                cout << "| " << setw(11) << students[index].informatika << " |\n";
            }
            else {
                cout << "�������� � ����� �������� �� ��������.\n";
            }
        }
        break;
        case 0:
            break;
        default:
            cout << "�� ����� ����������� ��������! ��� ������ ����� ������ ����.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    return 0;
}

void Create(Student* students, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":\n";
        cin.ignore();
        cout << " �������: "; getline(cin, students[i].prizv);
        cout << " ����: "; cin >> students[i].kurs;
        cout << " ������������ (0 - ����'����� �����, 1 - �������� ����������� ������������, 2 - ����������, 3 - Գ����, 4 - Գ������): ";
        cin >> specialnist;
        students[i].specialnist = static_cast<Specialnist>(specialnist);
        cout << " ������ � ������: "; cin >> students[i].fizyka;
        cout << " ������ � ����������: "; cin >> students[i].matematika;
        cout << " ������ � �����������: "; cin >> students[i].informatika;
        cout << endl;
    }
}

void Print(const Student* students, const int N) {
    cout << "===================================================================================================================\n";
    cout << "| �  | �������        | ���� | ������������                 | Գ���� | ���������� | ����������� |\n";
    cout << "-------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << i + 1 << " ";
        cout << "| " << setw(15) << left << students[i].prizv
            << "| " << setw(4) << right << students[i].kurs << " ";
        cout << "| " << setw(25) << left << specialnistStr[students[i].specialnist] << " ";
        cout << "| " << setw(6) << students[i].fizyka << " ";
        cout << "| " << setw(10) << students[i].matematika << " ";
        cout << "| " << setw(11) << students[i].informatika << " |\n";
    }
    cout << "===================================================================================================================\n";
}

double CalculateExcellentPercentage(const Student* students, const int N, int predmet) {
    int excellentCount = 0;
    for (int i = 0; i < N; i++) {
        if ((predmet == 1 && students[i].fizyka == 5) ||
            (predmet == 2 && students[i].matematika == 5) ||
            (predmet == 3 && students[i].informatika == 5)) {
            excellentCount++;
        }
    }
    return 100.0 * excellentCount / N;
}

void SortBySurname(Student* students, const int N) {
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - i - 1; j++)
            if (students[j].prizv > students[j + 1].prizv)
                swap(students[j], students[j + 1]);
}

int BinarySearchBySurname(const Student* students, const int N, const string& surname) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].prizv == surname)
            return mid;
        else if (students[mid].prizv < surname)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
