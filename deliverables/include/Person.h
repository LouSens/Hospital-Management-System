#pragma once
#include <string>
#include <iostream>

/**
 * Person.h -- Abstract Base Class (ABC)
 * Cannot be instantiated directly.
 * Defines the interface for all hospital users.
 *
 * Demonstrates:
 *   - Pure virtual function: displayRole() = 0
 *   - Virtual destructor (essential for polymorphic deletion)
 */
class Person {
protected:
    std::string id;
    std::string name;

private:
    static int totalCount; // Tracks total users (patients + doctors)

public:
    // Base constructor
    Person(const std::string& personId, const std::string& personName);

    // Virtual destructor -- CRITICAL for polymorphic delete
    virtual ~Person();

    // Getters
    std::string getName() const;
    std::string getId() const;

    // Static method -- called without object: Person::getTotalCount()
    static int getTotalCount();

    // Pure virtual -- MUST be overridden by derived classes
    virtual void displayRole() const = 0;

    // Pure virtual role type identifier
    virtual std::string getRoleType() const = 0;
};
