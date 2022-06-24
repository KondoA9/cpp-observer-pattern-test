#pragma once

#include <functional>
#include <optional>
#include <vector>

// Find the element from sorted vector by binary search and return its index.
template <class T>
std::optional<size_t> findElement(const std::vector<T>& vector,
                                  size_t key,
                                  const std::function<size_t(const T&)>& getValue) {
    if (vector.size() == 0) {
        return std::nullopt;
    }

    size_t left = 0, right = vector.size() - 1;

    while (right >= left) {
        const size_t mid = (left + right) / 2;
        const auto value = getValue(vector[mid]);

        if (value < key) {
            left = mid + 1;
        } else if (value > key) {
            right = mid - 1;
        } else {
            return mid;
        }
    }

    return std::nullopt;
}
