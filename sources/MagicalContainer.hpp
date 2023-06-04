#pragma once 

#include <vector>
#include <set>

namespace ariel{
    class MagicalContainer {
    private:
        std::vector<int> elements;

    public:
        void addElement(int element);
        void removeElement(int element);
        int size() const;
        int getElementAt(int index) const;
        void sort();
        void clear();

        bool operator!=(const MagicalContainer& other) const;


        class AscendingIterator {
        private:
            class MagicalContainer& container;
            int currentIndex;
            int currentValue;

        public:
            AscendingIterator(class MagicalContainer& container);
            AscendingIterator(const AscendingIterator& other);
            AscendingIterator& operator=(const AscendingIterator& other);
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
            int operator*() const;
            AscendingIterator& operator++();
            AscendingIterator begin();
            AscendingIterator end();
        };

        class PrimeIterator {
        private:
            class MagicalContainer& container;
            std::set<int> primes;
            int currentIndex;

        public:
            PrimeIterator(class MagicalContainer& container);
            PrimeIterator(const PrimeIterator& other);
            PrimeIterator& operator=(const PrimeIterator& other);
            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
            int operator*() const;
            PrimeIterator& operator++();
            PrimeIterator begin();
            PrimeIterator end();
            static bool isPrime(int n);
        };

        class SideCrossIterator {
        private:
            class MagicalContainer& container;
            int forwardIndex;
            int backwardIndex;
            bool turn;

        public:
            SideCrossIterator(class MagicalContainer& container);
            SideCrossIterator(const SideCrossIterator& other);
            SideCrossIterator& operator=(const SideCrossIterator& other);
            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
            int operator*() const;
            SideCrossIterator& operator++();
            SideCrossIterator begin();
            SideCrossIterator end();
        };
    };
}