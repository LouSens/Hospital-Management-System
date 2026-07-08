#include "../include/Person.h"

int Person::totalCount = 0;

Person::Person(const std::string& personId, const std::string& personName)
    : id(personId), name(personName) {
    totalCount++; // Increment on each construction
}

Person::~Person() {
    totalCount--; // Decrement on each destruction
}

std::string Person::getName() const { return name; }
std::string Person::getId() const { return id; }

int Person::getTotalCount() {
    return totalCount;
}
