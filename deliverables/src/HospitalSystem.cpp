#include "../include/HospitalSystem.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

HospitalSystem::HospitalSystem() {
    loadAllData(); // Auto-load on startup
}

HospitalSystem::~HospitalSystem() {
    for (Person* p : users) {
        delete p;
    }
    users.clear();
}

Patient* HospitalSystem::findPatient(const std::string& id) {
    for (Person* p : users) {
        if (p->getId() == id && p->getRoleType() == "Patient") {
            return dynamic_cast<Patient*>(p);
        }
    }
    return nullptr;
}

const MedicalService* HospitalSystem::findService(const std::string& code) const {
    for (const auto& svc : services) {
        if (svc.getServiceCode() == code) return &svc;
    }
    return nullptr;
}

void HospitalSystem::addPatient(const std::string& id,
                                const std::string& name,
                                const std::string& insurance) {
    // Check duplicate ID
    for (const Person* p : users) {
        if (p->getId() == id)
            throw std::runtime_error("User with ID " + id + " already exists.");
    }
    users.push_back(new Patient(id, name, insurance));
    std::cout << "[OK] Patient added: " << name << " (ID: " << id << ")" << std::endl;
}

void HospitalSystem::addDoctor(const std::string& id,
                               const std::string& name,
                               const std::string& specialization,
                               const std::string& clinicCode) {
    for (const Person* p : users) {
        if (p->getId() == id)
            throw std::runtime_error("User with ID " + id + " already exists.");
    }
    users.push_back(new Doctor(id, name, specialization, clinicCode));
    std::cout << "[OK] Doctor added: " << name << " (ID: " << id << ")" << std::endl;
}

void HospitalSystem::addMedicalService(const MedicalService& service) {
    for (const auto& s : services) {
        if (s.getServiceCode() == service.getServiceCode())
            throw std::runtime_error("Service code " +
                service.getServiceCode() + " already exists.");
    }
    services.push_back(service);
    std::cout << "[OK] Service added: " << service.getServiceName() << std::endl;
}

void HospitalSystem::scheduleAppointment(const std::string& patientId,
                                         const std::string& serviceCode) {
    Patient* pat = findPatient(patientId);
    if (!pat) throw std::runtime_error("Patient ID not found: " + patientId);

    const MedicalService* svc = findService(serviceCode);
    if (!svc) throw std::runtime_error("Service code not found: " + serviceCode);

    pat->scheduleAppointment(*svc);
}

void HospitalSystem::setAppointmentStatus(const std::string& patientId,
                                           const std::string& serviceCode,
                                           const std::string& status,
                                           const std::string& modifier) {
    Patient* pat = findPatient(patientId);
    if (!pat) throw std::runtime_error("Patient ID not found: " + patientId);

    if (!pat->setAppointmentStatus(serviceCode, status, modifier)) {
        throw std::runtime_error("Appointment with service code " +
            serviceCode + " not found for this patient.");
    }
    std::cout << "[OK] Appointment updated: "
              << serviceCode << " -> " << status << " (" << modifier << ")" << std::endl;
}

void HospitalSystem::viewAllUsers() const {
    if (users.empty()) {
        std::cout << "  [INFO] No users registered." << std::endl;
        return;
    }
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "           ALL REGISTERED USERS" << std::endl;
    std::cout << std::string(55, '=') << std::endl;
    for (const Person* p : users) {
        p->displayRole();
    }
    std::cout << std::string(55, '=') << std::endl;
    std::cout << "  Total Users : " << Person::getTotalCount()    << std::endl;
    std::cout << "  Patients    : " << Patient::getPatientCount() << std::endl;
    std::cout << "  Doctors     : " << Doctor::getDoctorCount()   << std::endl;
}

void HospitalSystem::viewServicesCatalog() const {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "           MEDICAL SERVICES CATALOG" << std::endl;
    std::cout << std::string(55, '=') << std::endl;
    if (services.empty()) {
        std::cout << "  [INFO] No services available." << std::endl;
        return;
    }
    for (const auto& svc : services) svc.displayService();
    std::cout << std::string(55, '=') << std::endl;
}

void HospitalSystem::viewPatientExpenses(const std::string& patientId) const {
    for (const Person* p : users) {
        if (p->getId() == patientId && p->getRoleType() == "Patient") {
            const Patient* pat = dynamic_cast<const Patient*>(p);
            if (pat) {
                std::cout << "\n  Patient : " << pat->getName() << std::endl;
                std::cout << "  Total Expenses: RM "
                          << std::fixed << std::setprecision(2)
                          << pat->calculateTotalMedicalExpenses() << std::endl;
            }
            return;
        }
    }
    throw std::runtime_error("Patient not found: " + patientId);
}

void HospitalSystem::viewSystemStats() const {
    std::cout << "\n" << std::string(55, '-') << std::endl;
    std::cout << "           SYSTEM STATISTICS" << std::endl;
    std::cout << std::string(55, '-') << std::endl;
    std::cout << "  Total registered users : " << Person::getTotalCount()    << std::endl;
    std::cout << "  Total patients         : " << Patient::getPatientCount() << std::endl;
    std::cout << "  Total doctors          : " << Doctor::getDoctorCount()   << std::endl;
    std::cout << "  Total services         : " << services.size()            << std::endl;
    std::cout << std::string(55, '-') << std::endl;
}

void HospitalSystem::saveAllData() const {
    try {
        FileManager::saveServices(services);
        FileManager::saveUsers(users);
        std::cout << "[OK] All data saved successfully." << std::endl;
    } catch (const std::ios_base::failure& e) {
        std::cerr << "[FILE ERROR] " << e.what() << std::endl;
    }
}

void HospitalSystem::loadAllData() {
    try {
        services = FileManager::loadServices();
        FileManager::loadUsers(users);
    } catch (const std::ios_base::failure& e) {
        std::cerr << "[FILE ERROR on load] " << e.what() << std::endl;
    }
}
