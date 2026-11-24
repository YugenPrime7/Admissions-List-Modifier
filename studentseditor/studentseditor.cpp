
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Student {
  string name;
  int math, russian, informatics, total;
};

int main() {
  SetConsoleOutputCP(CP_UTF8);

  ifstream input("students.txt");
  vector<Student> students;

  Student s;
  string surname, initials;

  double math = 0, russian = 0, informatics = 0;

  // Чтение данных
  while (input >> surname >> initials
    >> s.math >> s.russian >> s.informatics) {

    s.name = surname + " " + initials;
    s.total = s.math + s.russian + s.informatics;

    students.push_back(s);

    math += s.math;
    russian += s.russian;
    informatics += s.informatics;
  }

  input.close();

  if (students.empty()) {
    cout << "Список пуст!" << endl;
    return 1;
  }

  // Поиск лучшего и худшего
  int best = 0, worst = 0;

  for (int i = 1; i < students.size(); i++) {
    if (students[i].total > students[best].total)
      best = i;

    if (students[i].total < students[worst].total)
      worst = i;
  }

  // Создание результата в UTF-8
  ofstream output("result.txt", ios::binary);

  const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
  output.write(reinterpret_cast<const char*>(bom), 3);

  output << "ЛУЧШИЙ: " << students[best].name
    << " | Баллы: " << students[best].total << '\n';

  output << "ХУДШИЙ: " << students[worst].name
    << " | Баллы: " << students[worst].total << '\n';

  output << "\nСПИСОК ПОСТУПАЮЩИХ\n";

  output << "ФИО\t\tМатематика\tРусский\tИнформатика\tИтого\n";

  output << string(75, '-') << '\n';

  for (const Student& s : students) {
    output << s.name << "\t"
      << s.math << "\t\t"
      << s.russian << "\t"
      << s.informatics << "\t\t"
      << s.total << '\n';
  }

  // Средние баллы
  int n = students.size();

  output << "\nСРЕДНИЕ БАЛЛЫ\n";
  output << fixed << setprecision(2);

  output << "Математика: " << math / n << '\n';
  output << "Русский: " << russian / n << '\n';
  output << "Информатика: " << informatics / n << '\n';

  output.close();

  cout << "Готово! Результат сохранён в result.txt" << endl;

  return 0;
}
