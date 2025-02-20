#pragma once

#include "base.hpp"

namespace pom {
    template <typename T> class Ref {
    public:
        Ref() : count(new usize(0))
        {
        }

        explicit Ref(T* ptr) : ptr(ptr), count(new usize(1))
        {
        }

        explicit Ref(T* ptr, usize* count) : ptr(ptr), count(count)
        {
            if (ptr) {
                incref();
            }
        }

        // TODO: a constructor that only does one alloc for the counter and control block

        ~Ref()
        {
            decref();
        }

        Ref(const Ref& other) noexcept
        {
            other.incref();
            ptr = other.ptr;
            count = other.count;
        }

        void free()
        {
            decref();
            count = nullptr;
            ptr = nullptr;
        }

        Ref& operator=(const Ref& other) noexcept
        {
            Ref(other).swap(*this);
            return *this;
        }

        Ref(Ref&& other) noexcept : ptr(other.ptr), count(other.count)
        {
            other.count = nullptr;
            other.ptr = nullptr;
        }

        Ref& operator=(Ref&& other) noexcept
        {
            Ref(std::move(other)).swap(*this);
            return *this;
        }

        void swap(Ref& other) noexcept
        {
            std::swap(ptr, other.ptr);
            std::swap(count, other.count);
        }

        [[nodiscard]] inline u32 getRefCount() const noexcept
        {
            return *count;
        }

        [[nodiscard]] inline T* get() const noexcept
        {
            return ptr;
        }

        inline T& operator*() const noexcept
        {
            return *get();
        }

        inline T* operator->() const noexcept
        {
            return get();
        }

        inline operator bool() const noexcept
        {
            return get() != nullptr;
        }

        inline operator T*() const noexcept
        {
            return get();
        }

        template <typename U> Ref<U> dynCast() const noexcept
        {
            return Ref<U>(dynamic_cast<U*>(get()), count);
        }

    private:
        template <typename U> friend class Ref;

        void incref() const
        {
            if (count) {
                (*count)++;
            }
        }

        void decref() const
        {
            if (count && --(*count) == 0) {
                delete ptr;
                delete count;
            }
        }

        T* ptr = nullptr;
        usize* count = nullptr;
    };
} // namespace pom