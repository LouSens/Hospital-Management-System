#include "../include/FileManager.h"
#include "../include/Patient.h"
#include "../include/Doctor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

bool FileManager::fileExists(const std::string& filename) {
    std::ifstream f(filename);
    return f.good();
}

void FileManager::saveServices(const std::vector<MedicalService>& services,
                                const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::ios_base::failure("Cannot open file: " + filename);
    for (const auto& svc : services)
        file << svc.toFileString() << "\n";
    file.close();
    std::cout << "[FILE] Services saved to " << filename << std::endl;
}

void FileManager::saveUsers(const std::vector<Person*>& users,
                             const std::string& userFile,
                             const std::string& appointFile) {
    std::ofstream uFile(userFile);
    std::ofstream aFile(appointFile);

    if (!uFile.is_open()) throw std::ios_base::failure("Cannot open: " + userFile);
    if (!aFile.is_open()) throw std::ios_base::failure("Cannot open: " + appointFile);

    for (const Person* p : users) {
        // Polymorphic write via getRoleType()
        uFile << p->toFileString() << "\n";

        if (p->getRoleType() == "Patient") {
            const Patient* pat = dynamic_cast<const Patient*>(p);
            if (pat) {
                for (const auto& appt : pat->getAppointments()) {
                    aFile << p->getId() << "|" << appt.toFileString() << "\n";
                }
            }
        }
    }
    std::cout << "[FILE] Users and Appointments saved." << std::endl;
}

std::vector<MedicalService> FileManager::loadServices(const std::string& filename) {
    std::vector<MedicalService> services;
    if (!fileExists(filename)) return services;
    std::ifstream file(filename);
    if (!file.is_open()) throw std::ios_base::failure("Cannot open: " + filename);
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comment lines (lines beginning with '#')
        if (line.empty() || line[0] == '#') continue;
        std::stringstream ss(line);
        std::string code, name, feeStr;
        if (std::getline(ss, code, '|') &&
            std::getline(ss, name, '|') &&
            std::getline(ss, feeStr)) {
            try {
                services.emplace_back(code, name, std::stod(feeStr));
            } catch (...) {
                // Skip malformed lines
            }
        }
    }
    return services;
}

void FileManager::loadUsers(std::vector<Person*>& users,
                             const std::string& pFile,
                             const std::string& dFile) {
    // Load Patients
    if (fileExists(pFile)) {
        std::ifstream pIn(pFile);
        std::string line;
        while (std::getline(pIn, line)) {
            // Skip empty lines and comment lines
            if (line.empty() || line[0] == '#') continue;
            std::stringstream ss(line);
            std::string id, name, insurance;
            if (std::getline(ss, id, '|') &&
                std::getline(ss, name, '|') &&
                std::getline(ss, insurance)) {
                users.push_back(new Patient(id, name, insurance));
            }
        }
    }
    // Load Doctors
    if (fileExists(dFile)) {
        std::ifstream dIn(dFile);
        std::string line;
        while (std::getline(dIn, line)) {
            // Skip empty lines and comment lines
            if (line.empty() || line[0] == '#') continue;
            std::stringstream ss(line);
            std::string id, name, spec, clinic;
            if (std::getline(ss, id, '|') &&
                std::getline(ss, name, '|') &&
                std::getline(ss, spec, '|') &&
                std::getline(ss, clinic)) {
                users.push_back(new Doctor(id, name, spec, clinic));
            }
        }
    }
    // Only announce loaded data when there is actually something to report
    if (!users.empty()) {
        std::cout << "[FILE] Data loaded. Total users: "
                  << users.size() << std::endl;
    }
}
