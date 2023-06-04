#include "MagicalContainer.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace ariel;

void MagicalContainer::addElement(int element){
    int i = elements.size() - 1;
    for(; i >= 0 && element < elements[(std::size_t)i]; i--);
    
    elements.insert(elements.begin() + i + 1, element);   
}

void MagicalContainer::removeElement(int element){
    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
}

int MagicalContainer::size() const{
    return elements.size();
}

int MagicalContainer::getElementAt(int index) const{
    return elements[(std::size_t)index];
}

void MagicalContainer::sort()
{
    std::sort(elements.begin(), elements.end());
}

void MagicalContainer::clear()
{
    elements.clear();
}

bool MagicalContainer::operator!=(const MagicalContainer &other) const
{
    return !(this == &other);
}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
    : container(container), currentIndex(0){}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : container(other.container), currentIndex(other.currentIndex){}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other){
    if(this->container != other.container) throw std::runtime_error("");
    if (this != &other){
        currentIndex = other.currentIndex;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return currentIndex > other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return currentIndex < other.currentIndex;
}

int MagicalContainer::AscendingIterator::operator*() const{
    return container.getElementAt(currentIndex);
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
    if(currentIndex < container.size()) ++currentIndex;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin(){
    return AscendingIterator(container);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end(){
    AscendingIterator iterator(container);
    iterator.currentIndex = container.size();
    return iterator;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
    : container(container){
        int i = 0;
        while(i < container.size() && !isPrime(container.getElementAt(i))){
            i++;
        }
        currentIndex = i;
    }

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : container(other.container), primes(other.primes), currentIndex(other.currentIndex){}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other){
    if (this != &other){
        primes = other.primes;
        currentIndex = other.currentIndex;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return currentIndex == other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return currentIndex > other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return currentIndex < other.currentIndex;
}

int MagicalContainer::PrimeIterator::operator*() const{
    return container.getElementAt(currentIndex);
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
    while(currentIndex < container.size()){
        currentIndex++;
        if(!isPrime(container.getElementAt(currentIndex))) continue;
        break;
    }
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin(){
    return PrimeIterator(container);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end(){
    PrimeIterator iterator(container);
    iterator.currentIndex = container.size();
    return iterator;
}

bool MagicalContainer::PrimeIterator::isPrime(int n)
{   
    if(n <= 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;

    for (int i = 3; i * i <= n; i += 2){
        if (n % i == 0){
            return false;
        }
    }

    return true;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
    : container(container), forwardIndex(0), backwardIndex(container.size() - 1), turn(true){}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : container(other.container), forwardIndex(other.forwardIndex), backwardIndex(other.backwardIndex), turn(true){}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other){
    if (this != &other){
        forwardIndex = other.forwardIndex;
        backwardIndex = other.backwardIndex;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return forwardIndex == other.forwardIndex && backwardIndex == other.backwardIndex;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return forwardIndex + (container.size() - 1 - backwardIndex) > other.forwardIndex + (other.container.size() - 1 - other.backwardIndex);
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const{
    if(this->container != other.container) throw std::runtime_error("");
    return forwardIndex + (container.size() - 1 - backwardIndex) < other.forwardIndex + (other.container.size() - 1 - other.backwardIndex);
}

int MagicalContainer::SideCrossIterator::operator*() const{
    if (turn){
        return container.getElementAt(forwardIndex);
    } else{
        return container.getElementAt(backwardIndex);
    }
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
    if(container.size() == 0) return *this;
    if(turn){
        forwardIndex++;
    }else{
        backwardIndex--;
    }
    turn = !turn;
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin(){
    return SideCrossIterator(container);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end(){
    SideCrossIterator iterator(container);

    iterator.forwardIndex = ceil((double)container.size() / 2);
    iterator.backwardIndex = ceil((double)container.size() / 2) - 1;
    return iterator;
}