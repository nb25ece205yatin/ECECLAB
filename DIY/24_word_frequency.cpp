#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
    std::unordered_map<std::string, std::size_t> counts;
    std::string word;

    std::cout << "Enter words separated by whitespace, then end input "
                 "(Ctrl+Z on Windows or Ctrl+D on Unix):\n";
    while (std::cin >> word) {
        ++counts[word];
    }

    if (counts.empty()) {
        std::cout << "No words were entered.\n";
        return 0;
    }

    std::vector<std::pair<std::string, std::size_t>> sortedCounts(
        counts.begin(), counts.end());
    std::sort(sortedCounts.begin(), sortedCounts.end(),
              [](const std::pair<std::string, std::size_t>& left,
                 const std::pair<std::string, std::size_t>& right) {
                  return left.first < right.first;
              });

    std::cout << "Word counts (case-sensitive):\n";
    for (const auto& entry : sortedCounts) {
        std::cout << entry.first << ": " << entry.second << '\n';
    }

    const auto mostFrequent = std::max_element(
        sortedCounts.begin(), sortedCounts.end(),
        [](const std::pair<std::string, std::size_t>& left,
           const std::pair<std::string, std::size_t>& right) {
            if (left.second != right.second) {
                return left.second < right.second;
            }
            return left.first > right.first;
        });
    std::cout << "Most frequent word: " << mostFrequent->first << " ("
              << mostFrequent->second << " occurrences)\n";
    return 0;
}
