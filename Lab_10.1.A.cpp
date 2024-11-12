#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Otsinka { ZADOVILNO = 3, DOBRE, VIDMINNO };
enum Specialnist { KN, IT, ME, MF, FI };
string otsinkaStr[] = { "задовільно", "добре", "відмінно" };
string specialnistStr[] = { "Комп'ютерні науки", "Інженерія програмного забезпечення", "Математика", "Фізика", "Філологія" };

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
    cout << "Введіть кількість студентів N: "; cin >> N;

    Student* students = new Student[N];

    int menuItem;
    do {
        cout << "\nВиберіть дію:\n";
        cout << " [1] - введення даних про студентів\n";
        cout << " [2] - вивід даних про студентів\n";
        cout << " [3] - обчислення відсотка відмінників з фізики, математики та інформатики\n";
        cout << " [4] - сортування студентів за прізвищем\n";
        cout << " [5] - пошук студента за прізвищем\n";
        cout << " [0] - вихід\n";
        cout << "Введіть значення: "; cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(students, N);
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            cout << "Відсоток студентів, які мають 'відмінно' з фізики: "
                << CalculateExcellentPercentage(students, N, 1) << "%" << endl;
            cout << "Відсоток студентів, які мають 'відмінно' з математики: "
                << CalculateExcellentPercentage(students, N, 2) << "%" << endl;
            cout << "Відсоток студентів, які мають 'відмінно' з інформатики: "
                << CalculateExcellentPercentage(students, N, 3) << "%" << endl;
            break;
        case 4:
            SortBySurname(students, N);
            cout << "Студентів відсортовано за прізвищем.\n";
            Print(students, N); // Додаємо вивід для перевірки
            break;
        case 5:
        {
            SortBySurname(students, N); // Сортування перед пошуком
            string surname;
            cin.ignore();
            cout << "Введіть прізвище для пошуку: ";
            getline(cin, surname);
            int index = BinarySearchBySurname(students, N, surname);
            if (index != -1) {
                cout << "Студента знайдено:\n";
                cout << "| " << setw(15) << left << students[index].prizv
                    << "| " << setw(8) << right << students[index].kurs << " ";
                cout << "| " << setw(20) << left << specialnistStr[students[index].specialnist] << " ";
                cout << "| " << setw(8) << students[index].fizyka << " ";
                cout << "| " << setw(10) << students[index].matematika << " ";
                cout << "| " << setw(11) << students[index].informatika << " |\n";
            }
            else {
                cout << "Студента з таким прізвищем не знайдено.\n";
            }
        }
        break;
        case 0:
            break;
        default:
            cout << "Ви ввели неправильне значення! Слід ввести номер пункту меню.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    return 0;
}

void Create(Student* students, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":\n";
        cin.ignore();
        cout << " Прізвище: "; getline(cin, students[i].prizv);
        cout << " Курс: "; cin >> students[i].kurs;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Інженерія програмного забезпечення, 2 - Математика, 3 - Фізика, 4 - Філологія): ";
        cin >> specialnist;
        students[i].specialnist = static_cast<Specialnist>(specialnist);
        cout << " Оцінка з фізики: "; cin >> students[i].fizyka;
        cout << " Оцінка з математики: "; cin >> students[i].matematika;
        cout << " Оцінка з інформатики: "; cin >> students[i].informatika;
        cout << endl;
    }
}

void Print(const Student* students, const int N) {
    cout << "===================================================================================================================\n";
    cout << "| №  | Прізвище        | Курс | Спеціальність                 | Фізика | Математика | Інформатика |\n";
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
