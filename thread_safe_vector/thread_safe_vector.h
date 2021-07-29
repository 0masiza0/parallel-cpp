#pragma once

#include <atomic>
#include <vector>
#include <shared_mutex>

template <typename T>
class ThreadSafeVector {
public:
    ThreadSafeVector() {
    }

    T operator[](size_t index) const {
        std::shared_lock sh_data(sh_data_);
        return vector_[index];
    }

    size_t Size() const {
        std::shared_lock sh_sz(sh_sz_);
        return vector_.size();
    }

    void PushBack(const T& value) {
        std::unique_lock sz_lock(sh_sz_);

        if (vector_.size() == vector_.capacity()) {
            std::unique_lock data_lock(sh_data_);
            vector_.push_back(value);
        } else {
            vector_.push_back(value);
        }

    }

private:
    mutable std::shared_mutex sh_data_, sh_sz_;
    std::vector<T> vector_;
};
