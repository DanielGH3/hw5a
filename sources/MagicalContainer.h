#pragma once 

#include <vector>
#include <set>

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
};

class AscendingIterator {
private:
    MagicalContainer& container;
    int currentIndex;
    int currentValue;

public:
    AscendingIterator(MagicalContainer& container);
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
    MagicalContainer& container;
    std::set<int> primes;
    int currentIndex;

public:
    PrimeIterator(MagicalContainer& container);
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
    MagicalContainer& container;
    int forwardIndex;
    int backwardIndex;
    bool turn;

public:
    SideCrossIterator(MagicalContainer& container);
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