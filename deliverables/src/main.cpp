/**
 * main.cpp
 * Hospital Patient & Appointment Management System (HPAMS)
 * CST209 -- Object-Oriented Programming C++
 * Xiamen University Malaysia | Academic Session 2026/04
 *
 * Author      : [Your Name]
 * Student ID  : [Your Student ID]
 * Lecturer    : Danial Kafi Ahmad
 * Deadline    : 9 July 2026, 11:59 PM
 */

#include "../include/HospitalSystem.h"
#include <iostream>
#include <limits>
#include <stdexcept>

// =============================================================================
// UI HELPERS
// =============================================================================

void printMenu() {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "       HOSPITAL MANAGEMENT SYSTEM MENU" << std::endl;
    std::cout << std::string(55, '=') << std::endl;
    std::cout << "  1. Add New Patient" << std::endl;
    std::cout << "  2. Add New Doctor" << std::endl;
    std::cout << "  3. Add New Medical Service" << std::endl;
    std::cout << "  4. Schedule Appointment for Patient" << std::endl;
    std::cout << "  5. Update Appointment & Process Billing" << std::endl;
    std::cout << "  6. View All Personnel and Patients" << std::endl;
    std::cout << "  7. View Medical Services Catalog" << std::endl;
    std::cout << "  8. View Patient Medical Expenses" << std::endl;
    std::cout << "  9. View System Dashboard" << std::endl;
    std::cout << "  S. Save All Data to Files" << std::endl;
    std::cout << "  0. Exit System" << std::endl;
    std::cout << std::string(55, '-') << std::endl;
    std::cout << "  Enter choice: ";
}

// =============================================================================
// HANDLER FUNCTIONS
// =============================================================================

void handleAddPatient(HospitalSystem& sys) {
    std::string id, name, insurance;
    std::cout << "\n--- Add New Patient ---" << std::endl;
    std::cout << "  Enter Patient ID    : "; std::getline(std::cin, id);
    std::cout << "  Enter Patient Name  : "; std::getline(std::cin, name);
    std::cout << "  Enter Insurance     : "; std::getline(std::cin, insurance);

    if (id.empty() || name.empty())
        throw std::invalid_argument("Patient ID and Name cannot be empty.");
    if (insurance.empty()) insurance = "None";

    sys.addPatient(id, name, insurance);
}

void handleAddDoctor(HospitalSystem& sys) {
    std::string id, name, spec, clinic;
    std::cout << "\n--- Add New Doctor ---" << std::endl;
    std::cout << "  Enter Doctor ID         : "; std::getline(std::cin, id);
    std::cout << "  Enter Doctor Name       : "; std::getline(std::cin, name);
    std::cout << "  Enter Specialisation    : "; std::getline(std::cin, spec);
    std::cout << "  Enter Clinic Code       : "; std::getline(std::cin, clinic);

    if (id.empty() || name.empty() || spec.empty())
        throw std::invalid_argument("ID, Name, and Specialisation are required.");

    sys.addDoctor(id, name, spec, clinic.empty() ? "UNASSIGNED" : clinic);
}

void handleAddService(HospitalSystem& sys) {
    std::string code, name, feeStr;
    std::cout << "\n--- Add New Medical Service ---" << std::endl;
    std::cout << "  Enter Service Code  (e.g. SVC001) : "; std::getline(std::cin, code);
    std::cout << "  Enter Service Name               : "; std::getline(std::cin, name);
    std::cout << "  Enter Base Fee in RM (leave blank for RM 50.00 default): ";
    std::getline(std::cin, feeStr);

    if (code.empty() || name.empty())
        throw std::invalid_argument("Service Code and Name cannot be empty.");

    if (feeStr.empty()) {
        MedicalService svc(code, name);
        std::cout << "  [INFO] Using default fee: RM 50.00" << std::endl;
        sys.addMedicalService(svc);
    } else {
        try {
            double fee = std::stod(feeStr);
            MedicalService svc(code, name, fee);
            sys.addMedicalService(svc);
        } catch (const std::invalid_argument&) {
            throw std::invalid_argument("Fee must be a valid number (e.g. 120.50).");
        }
    }
}

void handleScheduleAppointment(HospitalSystem& sys) {
    std::string patientId, serviceCode;
    std::cout << "\n--- Schedule Appointment ---" << std::endl;
    std::cout << "  Enter Patient ID     : "; std::getline(std::cin, patientId);
    std::cout << "  Enter Service Code   : "; std::getline(std::cin, serviceCode);
    sys.scheduleAppointment(patientId, serviceCode);
}

void handleSetAppointmentStatus(HospitalSystem& sys) {
    std::string patientId, serviceCode, status, modifier;
    std::cout << "\n--- Update Appointment ---" << std::endl;
    std::cout << "  Enter Patient ID    : "; std::getline(std::cin, patientId);
    std::cout << "  Enter Service Code  : "; std::getline(std::cin, serviceCode);
    std::cout << "  Status [Scheduled/Completed/Cancelled/Emergency] : "; std::getline(std::cin, status);
    std::cout << "  Billing [Standard/Insured/Emergency]             : "; std::getline(std::cin, modifier);
    if (modifier.empty()) modifier = "Standard";
    sys.setAppointmentStatus(patientId, serviceCode, status, modifier);
}

void handleViewPatientExpenses(HospitalSystem& sys) {
    std::string id;
    std::cout << "\n--- View Patient Medical Expenses ---" << std::endl;
    std::cout << "  Enter Patient ID : "; std::getline(std::cin, id);
    sys.viewPatientExpenses(id);
}

// =============================================================================
// MAIN ENTRY POINT
// =============================================================================

int main() {
    // HospitalSystem constructor automatically loads saved data from files
    HospitalSystem system;

    std::string choice;
    bool running = true;

    std::cout << "\n  Welcome to the Hospital Patient & Appointment" << std::endl;
    std::cout << "  Management System (HPAMS)" << std::endl;

    while (running) {
        printMenu();
        std::getline(std::cin, choice);

        try {
            if (choice == "1") {
                handleAddPatient(system);
            } else if (choice == "2") {
                handleAddDoctor(system);
            } else if (choice == "3") {
                handleAddService(system);
            } else if (choice == "4") {
                handleScheduleAppointment(system);
            } else if (choice == "5") {
                handleSetAppointmentStatus(system);
            } else if (choice == "6") {
                system.viewAllUsers();
            } else if (choice == "7") {
                system.viewServicesCatalog();
            } else if (choice == "8") {
                handleViewPatientExpenses(system);
            } else if (choice == "9") {
                system.viewSystemStats();
            } else if (choice == "s" || choice == "S") {
                system.saveAllData();
            } else if (choice == "0") {
                system.saveAllData();       // Auto-save on exit
                std::cout << "\n  [SYSTEM] All data saved. Goodbye!" << std::endl;
                std::cout << "  Memory cleaned up by HospitalSystem destructor.\n" << std::endl;
                running = false;
            } else {
                throw std::invalid_argument("Invalid menu choice: '" + choice + "'");
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "\n  [INPUT ERROR]    " << e.what() << std::endl;
        } catch (const std::ios_base::failure& e) {
            std::cerr << "\n  [FILE ERROR]     " << e.what() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "\n  [SYSTEM ERROR]   " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "\n  [UNEXPECTED]     " << e.what() << std::endl;
        }
    }

    return 0;
}
