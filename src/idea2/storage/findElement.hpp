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
        const size_t mid = left + (right - left) / 2;

        if (const auto value = getValue(vector[mid]); value == key) {
            return mid;
        } else if (value > key) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return std::nullopt;
}
