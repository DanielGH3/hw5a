#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include<iostream>
#include<cstdlib>

bool seedset = false;
using namespace ariel;

MagicalContainer createContainer(bool random = false, int size = 10){
    if(!seedset){
        srand((unsigned) time(NULL));
        seedset = true;
    }

    MagicalContainer container;
    if(!random){
        for(int i = 0; i < size; i++){
            container.addElement(i);
        }
    }else{
        for(int i = 0; i < size; i++){
            container.addElement(rand() % (size * 10));
        }
    }
    
    return container;
}

bool isPrime(int n){
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

TEST_CASE("1. MagicalContainer adding elements"){
    MagicalContainer mc = MagicalContainer();
    mc.addElement(10);
    mc.addElement(100);
    mc.addElement(1);
    mc.addElement(25);
    mc.addElement(92);

    CHECK_EQ(mc.size(), 5);
}

TEST_CASE("1.5. MagicalContainer sorting elements"){
    MagicalContainer mc = createContainer();

    for(int i = 1; i < mc.size(); i++){
        CHECK(mc.getElementAt(i - 1) < mc.getElementAt(i));
    }
}

TEST_CASE("2. MagicalContainer removing"){
    MagicalContainer mc = createContainer();

    CHECK_EQ(mc.size(), 10);

    mc.removeElement(5);
    CHECK_EQ(mc.size(), 9);
    CHECK_EQ(mc.getElementAt(5), 6);

    mc.clear();
    CHECK_EQ(mc.size(), 0);
}

TEST_CASE("3. MagicalContainer::AscendingIterator iteration"){
    MagicalContainer mc = createContainer();
    MagicalContainer::AscendingIterator ai(mc);

    int cnt = 0;
    for(auto it = ai.begin(); it != ai.end(); ++it){
        CHECK_EQ(*it, cnt++);
    }
}

TEST_CASE("4. MagicalContainer::SideCrossIterator iteration"){
    MagicalContainer mc = createContainer();
    MagicalContainer::SideCrossIterator sci(mc);

    int cnt = 0;
    int values[] = {0, 9, 1, 8, 2, 7, 3, 6, 4, 5};

    for(auto it = sci.begin(); it != sci.end(); ++it){
        CHECK_EQ(*it, values[cnt++]);
    }
}

TEST_CASE("5. MagicalContainer::PrimeIterator iteration"){
    MagicalContainer mc = createContainer();
    MagicalContainer::PrimeIterator pi(mc);

    int cnt = 0;
    int values[] = {2, 3, 5, 7};

    for(auto it = pi.begin(); it != pi.end(); ++it){
        CHECK_EQ(*it, values[cnt++]);
    }
}


TEST_CASE("6. Empty Iteration"){
    MagicalContainer mc = MagicalContainer();
    MagicalContainer::AscendingIterator ai(mc);
    MagicalContainer::SideCrossIterator sci(mc);
    MagicalContainer::PrimeIterator pi(mc);

    CHECK_EQ(mc.size(), 0);

    int cnt = 0;
    for(auto it = ai.begin(); it != ai.end(); ++it){
        cnt++;
    }
    for(auto it = sci.begin(); it != sci.end(); ++it){
        cnt++;
    }
    for(auto it = pi.begin(); it != pi.end(); ++it){
        cnt++;
    }

    CHECK_EQ(cnt, 0);
}

TEST_CASE("7. Empty Container"){
    MagicalContainer mc = createContainer();

    CHECK_EQ(mc.size(), 10);

    CHECK_NOTHROW(mc.getElementAt(0));
    CHECK_NOTHROW(mc.clear());
    CHECK_NOTHROW(mc.removeElement(100));
}

TEST_CASE("8. O1 Space complexty"){
    MagicalContainer mc = createContainer();

    MagicalContainer::AscendingIterator ai(mc);
    int cnt = 0;
    for(auto it = ai.begin(); it != ai.end(); ++it){
        CHECK_EQ(*it, cnt++);
    }

    MagicalContainer::SideCrossIterator sci(mc);
    cnt = 0;
    int values1[] = {0, 9, 1, 8, 2, 7, 3, 6, 4, 5};
    for(auto it = sci.begin(); it != sci.end(); ++it){
        CHECK_EQ(*it, values1[cnt++]);
    }

    MagicalContainer::PrimeIterator pi(mc);
    cnt = 0;
    int values2[] = {2, 3, 5, 7};
    for(auto it = pi.begin(); it != pi.end(); ++it){
        CHECK_EQ(*it, values2[cnt++]);
    }

    mc.clear();
    CHECK_EQ(mc.size(), 0);

    cnt = 0;
    for(auto it = ai.begin(); it != ai.end(); ++it){
        cnt++;
    }
    for(auto it = sci.begin(); it != sci.end(); ++it){
        cnt++;
    }
    for(auto it = pi.begin(); it != pi.end(); ++it){
        cnt++;
    }

    CHECK_EQ(cnt, 0);
}

TEST_CASE("9. Changing MagicalContainer::AscendingIterator mid iteration"){
    MagicalContainer mc = createContainer();
    MagicalContainer::AscendingIterator ai(mc);

    mc.removeElement(3);
    CHECK_EQ(mc.size(), 9);

    auto it = ai.begin();
    mc.addElement(3);
    mc.addElement(10);

    int cnt = 0;
    for(; it != ai.end(); ++it){
        CHECK_EQ(*it, cnt++);
    }
}

TEST_CASE("10. Changing MagicalContainer::SideCrossIterator mid iteration"){
    MagicalContainer mc = createContainer();
    MagicalContainer::SideCrossIterator sci(mc);

    mc.removeElement(3);
    CHECK_EQ(mc.size(), 9);

    auto it = sci.begin();
    mc.addElement(3);
    mc.addElement(10);

    int cnt = 0;
    int values1[] = {0, 10, 1, 9, 2, 8, 3, 7, 4, 6, 5};
    for(auto it = sci.begin(); it != sci.end(); ++it){
        CHECK_EQ(*it, values1[cnt++]);
    }
}

TEST_CASE("11. Changing MagicalContainer::SideCrossIterator mid iteration"){
    MagicalContainer mc = createContainer();
    MagicalContainer::PrimeIterator pi(mc);

    mc.removeElement(3);
    CHECK_EQ(mc.size(), 9);

    auto it = pi.begin();
    mc.addElement(11);

    int cnt = 0;
    int values2[] = {2, 5, 7, 11};
    for(auto it = pi.begin(); it != pi.end(); ++it){
        CHECK_EQ(*it, values2[cnt++]);
    }
}

TEST_CASE("12. MagicalContainer::AscendingIterator comparisons"){
    MagicalContainer mc = createContainer();
    MagicalContainer::AscendingIterator iter1(mc);
    MagicalContainer::AscendingIterator iter2(mc);
    
    auto it1 = iter1.begin();
    auto it2 = iter2.begin();

    CHECK_EQ(it1, it2);

    ++it1;
    CHECK(it1 > it2);
    CHECK_NE(it1, it2);

    ++it2; ++it2;
    CHECK(it1 < it2);

    while(it1 != iter1.end()) ++it1;

    CHECK(it1 > it2);

    mc.clear();
    it1 = iter1.begin();
    it2 = iter2.begin();

    ++it1;
    CHECK_FALSE(it1 > it2);
}

TEST_CASE("13. MagicalContainer::SideCrossIterator comparisons"){
    MagicalContainer mc = createContainer();
    MagicalContainer::SideCrossIterator iter1(mc);
    MagicalContainer::SideCrossIterator iter2(mc);
    
    auto it1 = iter1.begin();
    auto it2 = iter2.begin();

    CHECK_EQ(it1, it2);

    ++it1;
    CHECK(it1 > it2);
    CHECK_NE(it1, it2);

    ++it2; ++it2;
    CHECK(it1 < it2);

    while(it1 != iter1.end()) ++it1;

    CHECK(it1 > it2);

    mc.clear();
    it1 = iter1.begin();
    it2 = iter2.begin();

    ++it1;
    CHECK_FALSE(it1 > it2);
}

TEST_CASE("14. MagicalContainer::PrimeIterator comparisons"){
    MagicalContainer mc = createContainer();
    MagicalContainer::PrimeIterator iter1(mc);
    MagicalContainer::PrimeIterator iter2(mc);
    
    auto it1 = iter1.begin();
    auto it2 = iter2.begin();

    CHECK_EQ(it1, it2);

    ++it1;
    CHECK(it1 > it2);
    CHECK_NE(it1, it2);

    ++it2; ++it2;
    CHECK(it1 < it2);

    while(it1 != iter1.end()) ++it1;

    CHECK(it1 > it2);

    mc.clear();
    it1 = iter1.begin();
    it2 = iter2.begin();

    ++it1;
    CHECK_FALSE(it1 > it2);
}

TEST_CASE("15. Different Containers MagicalContainer::AscendingIterator comparisons"){
    MagicalContainer mc1 = createContainer();
    MagicalContainer mc2 = createContainer();
    MagicalContainer::AscendingIterator iter1(mc1);
    MagicalContainer::AscendingIterator iter2(mc2);
    
    auto it1 = iter1.begin();
    auto it2 = iter2.begin();

    bool b = false;

    CHECK_THROWS(b = it1 == it2);

    ++it1;
    CHECK_THROWS(b = it1 > it2);
    CHECK_THROWS(b = it1 != it2);

    ++it2; ++it2;
    CHECK_THROWS(b = it1 < it2);

    while(it1 != iter1.end()) ++it1;

    CHECK_THROWS(b = it1 > it2);

    mc1.clear();
    mc2.clear();
    it1 = iter1.begin();
    it2 = iter2.begin();

    ++it1;
    CHECK_THROWS(b = it1 > it2);
}

TEST_CASE("16. Different Containers MagicalContainer::SideCrossIterator comparisons"){
    MagicalContainer mc1 = createContainer();
    MagicalContainer mc2 = createContainer();
    MagicalContainer::SideCrossIterator iter1(mc1);
    MagicalContainer::SideCrossIterator iter2(mc2);
    
    auto it1 = iter1.begin();
    auto it2 = iter2.begin();

    bool b = false;

    CHECK_THROWS(b = it1 == it2);

    ++it1;
    CHECK_THROWS(b = it1 > it2);
    CHECK_THROWS(b = it1 != it2);

    ++it2; ++it2;
    CHECK_THROWS(b = it1 < it2);

    while(it1 != iter1.end()) ++it1;

    CHECK_THROWS(b = it1 > it2);

    mc1.clear();
    mc2.clear();
    it1 = iter1.begin();
    it2 = iter2.begin();

    ++it1;
    CHECK_THROWS(b = it1 > it2);
}

TEST_CASE("17. Different Containers MagicalContainer::PrimeIterator comparisons"){
    MagicalContainer mc1 = createContainer();
    MagicalContainer mc2 = createContainer();
    MagicalContainer::PrimeIterator iter1(mc1);
    MagicalContainer::PrimeIterator iter2(mc2);
    
    auto it1 = iter1.begin();
    auto it2 = iter2.begin();

    bool b = false;

    CHECK_THROWS(b = it1 == it2);

    ++it1;
    CHECK_THROWS(b = it1 > it2);
    CHECK_THROWS(b = it1 != it2);

    ++it2; ++it2;
    CHECK_THROWS(b = it1 < it2);

    while(it1 != iter1.end()) ++it1;

    CHECK_THROWS(b = it1 > it2);

    mc1.clear();
    mc2.clear();
    it1 = iter1.begin();
    it2 = iter2.begin();

    ++it1;
    CHECK_THROWS(b = it1 > it2);
}

TEST_CASE("18. MagicalContainer::PrimeIterator only primes"){
    int size = 1000;

    MagicalContainer mc = createContainer(true, size);
    MagicalContainer::PrimeIterator iter(mc);

    for(auto it = iter.begin(); it != iter.end(); ++it){
        CHECK(isPrime(*it));
    }
}

TEST_CASE("19. Different Constructors"){
    MagicalContainer mc = createContainer();

    MagicalContainer::PrimeIterator pi1(mc);
    MagicalContainer::PrimeIterator pi2(pi1);
    MagicalContainer::PrimeIterator pi3 = pi2;

    for(auto it = pi3.begin(); it != pi3.end(); ++it){
        CHECK(isPrime(*it));
    }

    MagicalContainer::SideCrossIterator sci1(mc);
    MagicalContainer::SideCrossIterator sci2(sci1);
    MagicalContainer::SideCrossIterator sci3 = sci2;

    int cnt = 0;
    int values1[] = {0, 9, 1, 8, 2, 7, 3, 6, 4, 5};
    for(auto it = sci3.begin(); it != sci3.end(); ++it){
        CHECK_EQ(*it, values1[cnt++]);
    }

    MagicalContainer::AscendingIterator ai1(mc);
    MagicalContainer::AscendingIterator ai2(ai1);
    MagicalContainer::AscendingIterator ai3 = ai2;

    cnt = 0;
    for(auto it = ai2.begin(); it != ai2.end(); ++it){
        CHECK_EQ(*it, cnt++);
    }
}

//TESTS COUNT : 1-19 [INCLUDING 1.5] = 20