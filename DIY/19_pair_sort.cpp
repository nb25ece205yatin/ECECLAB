#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    int count;
    std::cout << "Enter the number of name-score pairs: ";
    if (!(std::cin >> count) || count < 0) {
        std::cerr << "Invalid number of pairs.\n";
        return 1;
    }

    std::vector<std::pair<std::string, int>> entries;
    entries.reserve(static_cast<std::size_t>(count));

    for (int i = 0; i < count; ++i) {
        std::string name;
        int score;
        std::cout << "Enter name and score for pair " << i + 1 << ": ";
        if (!(std::cin >> name >> score)) {
            std::cerr << "Invalid pair input.\n";
            return 1;
        }
        entries.emplace_back(name, score);
    }

    std::sort(entries.begin(), entries.end(),
              [](const std::pair<std::string, int>& left,
                 const std::pair<std::string, int>& right) {
                  if (left.second != right.second) {
                      return left.second < right.second;
                  }
                  return left.first < right.first;
              });

    std::cout << "Pairs sorted by score in ascending order:\n";
    for (const auto& entry : entries) {
        std::cout << entry.first << ' ' << entry.second << '\n';
    }
    return 0;
}
