#pragma once
#include <vector>
#include <string>
#include "MedicalService.h"

// Forward declarations
class Person;

/**
 * FileManager.h
 * Handles all file I/O for data persistence.
 * Demonstrates: STL fstream, file serialisation/deserialisation
 */
class FileManager {
public:
    // Save operations
    static void saveServices(const std::vector<MedicalService>& services,
                             const std::string& filename = "data/services.txt");
    static void saveUsers(const std::vector<Person*>& users,
                          const std::string& pFile = "data/patients.txt",
                          const std::string& dFile = "data/doctors.txt");

    // Load operations
    static std::vector<MedicalService> loadServices(
        const std::string& filename = "data/services.txt");
    static void loadUsers(std::vector<Person*>& users,
                          const std::string& pFile = "data/patients.txt",
                          const std::string& dFile = "data/doctors.txt");

    // Utility
    static bool fileExists(const std::string& filename);
};
