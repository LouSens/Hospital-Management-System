# 💻 COMPLETE CODE GENERATION GUIDE
## CST209 — Hospital Patient & Appointment Management System
### Step-by-Step C++ Implementation with Full Code

---

## ⚠️ BEFORE YOU START — RULES

1. Create folder structure exactly as defined in the Architecture doc
2. Every class: declaration in `.h`, implementation in `.cpp`
3. Use `#pragma once` or include guards in every header
4. Compile frequently to catch errors early
5. Test each feature before adding the next

---

## STEP 1 — `include/MedicalService.h`

```cpp
#pragma once
#include <string>
#include <iostream>
#include <iomanip>

/**
 * MedicalService.h
 * Represents a medical service or clinic offering in the hospital.
 * Demonstrates: Constructor Overloading (Compile-time Polymorphism)
 */
class MedicalService {
private:
    std::string serviceCode;
    std::string serviceName;
    double baseFee;

public:
    // Constructor 1: All parameters provided
    MedicalService(const std::string& code, const std::string& name, double fee);

    // Constructor 2: Default baseFee = 50.0 (overloaded constructor)
    MedicalService(const std::string& code, const std::string& name);

    // Default constructor for file loading
    MedicalService();

    // Getters
    std::string getServiceCode() const;
    std::string getServiceName() const;
    double getBaseFee() const;

    // Setters
    void setBaseFee(double fee);

    // Display service details
    void displayService() const;

    // Serialise to string for file storage
    std::string toFileString() const;
};
```

---

## STEP 2 — `src/MedicalService.cpp`

```cpp
#include "../include/MedicalService.h"
#include <stdexcept>

// Constructor 1: Full parameters
MedicalService::MedicalService(const std::string& code,
                               const std::string& name,
                               double fee)
    : serviceCode(code), serviceName(name), baseFee(fee) {
    if (fee < 0)
        throw std::invalid_argument("Base fee cannot be negative.");
}

// Constructor 2: Default fee = 50.0 (overloaded)
MedicalService::MedicalService(const std::string& code,
                               const std::string& name)
    : serviceCode(code), serviceName(name), baseFee(50.0) {}

// Default constructor
MedicalService::MedicalService()
    : serviceCode(""), serviceName(""), baseFee(50.0) {}

std::string MedicalService::getServiceCode() const { return serviceCode; }
std::string MedicalService::getServiceName() const { return serviceName; }
double MedicalService::getBaseFee() const { return baseFee; }

void MedicalService::setBaseFee(double fee) {
    if (fee < 0) throw std::invalid_argument("Fee cannot be negative.");
    baseFee = fee;
}

void MedicalService::displayService() const {
    std::cout << std::left
              << "  Code: " << std::setw(12) << serviceCode
              << "| Name: " << std::setw(25) << serviceName
              << "| Base Fee: RM " << std::fixed
              << std::setprecision(2) << baseFee << std::endl;
}

std::string MedicalService::toFileString() const {
    return serviceCode + "|" + serviceName + "|" + std::to_string(baseFee);
}
```

---

## STEP 3 — `include/AppointmentRecord.h`

```cpp
#pragma once
#include "MedicalService.h"
#include <string>

/**
 * AppointmentRecord.h
 * Represents a single appointment between a patient and a medical service.
 * Demonstrates: COMPOSITION — AppointmentRecord HAS-A MedicalService
 *
 * Billing Modifiers:
 *   "Cancelled"  → 0.00
 *   "Scheduled"  → baseFee × 1.0
 *   "Completed"  → baseFee × 0.8 (insured discount)
 *   "Emergency"  → baseFee × 1.5 (surcharge)
 */
class AppointmentRecord {
private:
    MedicalService service;        // COMPOSITION: has-a relationship
    std::string appointmentStatus; // "Scheduled", "Completed", "Cancelled", "Emergency"
    std::string billingModifier;   // "Standard", "Insured", "Emergency"

public:
    // Constructor: creates an appointment with default status "Scheduled"
    AppointmentRecord(const MedicalService& svc,
                      const std::string& status = "Scheduled",
                      const std::string& modifier = "Standard");

    // Getters
    std::string getServiceCode() const;
    std::string getServiceName() const;
    std::string getAppointmentStatus() const;
    std::string getBillingModifier() const;
    MedicalService getService() const;

    // Setter for status
    void setStatus(const std::string& status);
    void setBillingModifier(const std::string& modifier);

    // Calculate billing based on status and modifier
    double calculateBillingAmount() const;

    // Display full appointment detail
    void displayAppointment() const;

    // Serialise for file storage
    std::string toFileString() const;
};
```

---

## STEP 4 — `src/AppointmentRecord.cpp`

```cpp
#include "../include/AppointmentRecord.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

AppointmentRecord::AppointmentRecord(const MedicalService& svc,
                                     const std::string& status,
                                     const std::string& modifier)
    : service(svc), appointmentStatus(status), billingModifier(modifier) {}

std::string AppointmentRecord::getServiceCode() const {
    return service.getServiceCode();
}
std::string AppointmentRecord::getServiceName() const {
    return service.getServiceName();
}
std::string AppointmentRecord::getAppointmentStatus() const {
    return appointmentStatus;
}
std::string AppointmentRecord::getBillingModifier() const {
    return billingModifier;
}
MedicalService AppointmentRecord::getService() const { return service; }

void AppointmentRecord::setStatus(const std::string& status) {
    if (status != "Scheduled" && status != "Completed" &&
        status != "Cancelled" && status != "Emergency") {
        throw std::invalid_argument(
            "Invalid status. Use: Scheduled, Completed, Cancelled, Emergency.");
    }
    appointmentStatus = status;
}

void AppointmentRecord::setBillingModifier(const std::string& modifier) {
    if (modifier != "Standard" && modifier != "Insured" && modifier != "Emergency") {
        throw std::invalid_argument(
            "Invalid modifier. Use: Standard, Insured, Emergency.");
    }
    billingModifier = modifier;
}

double AppointmentRecord::calculateBillingAmount() const {
    double base = service.getBaseFee();
    if (appointmentStatus == "Cancelled") return 0.0;
    if (billingModifier == "Insured")    return base * 0.8;  // 20% discount
    if (billingModifier == "Emergency" ||
        appointmentStatus == "Emergency") return base * 1.5; // 50% surcharge
    return base * 1.0; // Standard rate
}

void AppointmentRecord::displayAppointment() const {
    std::cout << "    [" << appointmentStatus << "] "
              << service.getServiceCode() << " — "
              << service.getServiceName()
              << " | Modifier: " << billingModifier
              << " | Bill: RM " << std::fixed
              << std::setprecision(2) << calculateBillingAmount()
              << std::endl;
}

std::string AppointmentRecord::toFileString() const {
    return service.toFileString() + "|" + appointmentStatus + "|" + billingModifier;
}
```

---

## STEP 5 — `include/Person.h` (Abstract Base Class)

```cpp
#pragma once
#include <string>
#include <iostream>

/**
 * Person.h — Abstract Base Class (ABC)
 * Cannot be instantiated directly.
 * Defines the interface for all hospital users.
 *
 * Demonstrates:
 *   - Pure virtual function: displayRole() = 0
 *   - Virtual destructor (essential for polymorphic deletion)
 *   - Static member: totalCount tracks all Person instances
 */
class Person {
protected:
    std::string name;
    std::string id;

private:
    static int totalCount; // Tracks total users (patients + doctors)

public:
    // Base constructor
    Person(const std::string& personId, const std::string& personName);

    // Virtual destructor — CRITICAL for polymorphic delete
    virtual ~Person();

    // Getters
    std::string getName() const;
    std::string getId() const;

    // Static method — called without object: Person::getTotalCount()
    static int getTotalCount();

    // Pure virtual — MUST be overridden by derived classes
    virtual void displayRole() const = 0;

    // Virtual method with default (optional override)
    virtual std::string getRoleType() const = 0;
};
```

---

## STEP 6 — `src/Person.cpp`

```cpp
#include "../include/Person.h"

// Initialise static member outside class (required in exactly ONE .cpp)
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
```

---

## STEP 7 — `include/Patient.h`

```cpp
#pragma once
#include "Person.h"
#include "AppointmentRecord.h"
#include <vector>
#include <string>

/**
 * Patient.h
 * Inherits from Person (ABC).
 * Demonstrates:
 *   - Inheritance: IS-A Person
 *   - Override of pure virtual displayRole()
 *   - STL vector for appointments collection
 *   - Static member patientCount
 */
class Patient : public Person {
private:
    std::string insuranceProvider;
    std::vector<AppointmentRecord> appointments; // STL collection
    static int patientCount;

public:
    // Constructor
    Patient(const std::string& id,
            const std::string& name,
            const std::string& insurance);

    // Destructor
    ~Patient() override;

    // Override pure virtual
    void displayRole() const override;

    // Return role type string
    std::string getRoleType() const override;

    // Getters
    std::string getInsuranceProvider() const;
    const std::vector<AppointmentRecord>& getAppointments() const;

    // Appointment operations
    void scheduleAppointment(const MedicalService& service);
    bool setAppointmentStatus(const std::string& serviceCode,
                              const std::string& status,
                              const std::string& modifier = "Standard");

    // Billing
    double calculateTotalMedicalExpenses() const;

    // Static
    static int getPatientCount();

    // File serialisation
    std::string toFileString() const;
};
```

---

## STEP 8 — `src/Patient.cpp`

```cpp
#include "../include/Patient.h"
#include <iostream>
#include <iomanip>
#include <algorithm> // std::find_if

// Initialise static member
int Patient::patientCount = 0;

Patient::Patient(const std::string& id,
                 const std::string& name,
                 const std::string& insurance)
    : Person(id, name), insuranceProvider(insurance) {
    patientCount++;
}

Patient::~Patient() {
    patientCount--;
}

// Override pure virtual — RUNTIME POLYMORPHISM
void Patient::displayRole() const {
    std::cout << std::string(55, '-') << std::endl;
    std::cout << "  [PATIENT] ID: " << id
              << "  |  Name: " << name << std::endl;
    std::cout << "  Insurance: " << insuranceProvider
              << "  |  Appointments: " << appointments.size() << std::endl;
    if (!appointments.empty()) {
        std::cout << "  Appointment Records:" << std::endl;
        for (const auto& appt : appointments) {
            appt.displayAppointment();
        }
        std::cout << "  Total Expenses: RM " << std::fixed
                  << std::setprecision(2)
                  << calculateTotalMedicalExpenses() << std::endl;
    }
}

std::string Patient::getRoleType() const { return "Patient"; }

std::string Patient::getInsuranceProvider() const { return insuranceProvider; }

const std::vector<AppointmentRecord>& Patient::getAppointments() const {
    return appointments;
}

void Patient::scheduleAppointment(const MedicalService& service) {
    AppointmentRecord record(service); // Default status: "Scheduled"
    appointments.push_back(record);
    std::cout << "[OK] Appointment scheduled: "
              << service.getServiceCode() << " — "
              << service.getServiceName() << std::endl;
}

bool Patient::setAppointmentStatus(const std::string& serviceCode,
                                   const std::string& status,
                                   const std::string& modifier) {
    // Use std::find_if with lambda — idiomatic STL search
    auto it = std::find_if(appointments.begin(), appointments.end(),
        [&serviceCode](const AppointmentRecord& r) {
            return r.getServiceCode() == serviceCode;
        });

    if (it == appointments.end()) {
        return false; // Not found
    }
    it->setStatus(status);
    it->setBillingModifier(modifier);
    return true;
}

double Patient::calculateTotalMedicalExpenses() const {
    double total = 0.0;
    for (const auto& appt : appointments) {
        total += appt.calculateBillingAmount();
    }
    return total;
}

int Patient::getPatientCount() { return patientCount; }

std::string Patient::toFileString() const {
    return id + "|" + name + "|" + insuranceProvider;
}
```

---

## STEP 9 — `include/Doctor.h`

```cpp
#pragma once
#include "Person.h"
#include <string>

/**
 * Doctor.h
 * Inherits from Person (ABC).
 * Demonstrates:
 *   - Inheritance: IS-A Person
 *   - Override of pure virtual displayRole()
 *   - Static member doctorCount
 */
class Doctor : public Person {
private:
    std::string specializationDepartment;
    std::string assignedClinicCode;
    static int doctorCount;

public:
    Doctor(const std::string& id,
           const std::string& name,
           const std::string& specialization,
           const std::string& clinicCode = "UNASSIGNED");

    ~Doctor() override;

    // Override pure virtual
    void displayRole() const override;
    std::string getRoleType() const override;

    // Getters
    std::string getSpecialization() const;
    std::string getClinicCode() const;

    // Assign doctor to a clinic
    void assignToClinic(const std::string& code);

    // Static
    static int getDoctorCount();

    // File serialisation
    std::string toFileString() const;
};
```

---

## STEP 10 — `src/Doctor.cpp`

```cpp
#include "../include/Doctor.h"
#include <iostream>

int Doctor::doctorCount = 0;

Doctor::Doctor(const std::string& id,
               const std::string& name,
               const std::string& specialization,
               const std::string& clinicCode)
    : Person(id, name),
      specializationDepartment(specialization),
      assignedClinicCode(clinicCode) {
    doctorCount++;
}

Doctor::~Doctor() {
    doctorCount--;
}

// Override pure virtual — RUNTIME POLYMORPHISM
void Doctor::displayRole() const {
    std::cout << std::string(55, '-') << std::endl;
    std::cout << "  [DOCTOR]  ID: " << id
              << "  |  Name: " << name << std::endl;
    std::cout << "  Specialization: " << specializationDepartment
              << "  |  Clinic: " << assignedClinicCode << std::endl;
}

std::string Doctor::getRoleType() const { return "Doctor"; }

std::string Doctor::getSpecialization() const {
    return specializationDepartment;
}
std::string Doctor::getClinicCode() const { return assignedClinicCode; }

void Doctor::assignToClinic(const std::string& code) {
    assignedClinicCode = code;
    std::cout << "[OK] Doctor " << name
              << " assigned to clinic: " << code << std::endl;
}

int Doctor::getDoctorCount() { return doctorCount; }

std::string Doctor::toFileString() const {
    return id + "|" + name + "|" + specializationDepartment + "|" + assignedClinicCode;
}
```

---

## STEP 11 — `include/FileManager.h`

```cpp
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
```

---

## STEP 12 — `src/FileManager.cpp`

```cpp
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
                             const std::string& pFile,
                             const std::string& dFile) {
    std::ofstream pOut(pFile), dOut(dFile);
    if (!pOut.is_open()) throw std::ios_base::failure("Cannot open: " + pFile);
    if (!dOut.is_open()) throw std::ios_base::failure("Cannot open: " + dFile);

    for (const Person* p : users) {
        if (p->getRoleType() == "Patient") {
            const Patient* pat = dynamic_cast<const Patient*>(p);
            if (pat) pOut << pat->toFileString() << "\n";
        } else if (p->getRoleType() == "Doctor") {
            const Doctor* doc = dynamic_cast<const Doctor*>(p);
            if (doc) dOut << doc->toFileString() << "\n";
        }
    }
    std::cout << "[FILE] Users saved." << std::endl;
}

std::vector<MedicalService> FileManager::loadServices(const std::string& filename) {
    std::vector<MedicalService> services;
    if (!fileExists(filename)) return services;
    std::ifstream file(filename);
    if (!file.is_open()) throw std::ios_base::failure("Cannot open: " + filename);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string code, name, feeStr;
        if (std::getline(ss, code, '|') &&
            std::getline(ss, name, '|') &&
            std::getline(ss, feeStr)) {
            services.emplace_back(code, name, std::stod(feeStr));
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
    std::cout << "[FILE] Data loaded. Total users: "
              << users.size() << std::endl;
}
```

---

## STEP 13 — `include/HospitalSystem.h`

```cpp
#pragma once
#include "Patient.h"
#include "Doctor.h"
#include "MedicalService.h"
#include "FileManager.h"
#include <vector>
#include <string>

/**
 * HospitalSystem.h
 * Central controller. Aggregates all entities.
 * Demonstrates:
 *   - vector<Person*> — polymorphic container
 *   - dynamic_cast for safe downcasting
 *   - Runtime polymorphism via displayRole()
 */
class HospitalSystem {
private:
    std::vector<Person*> users;             // Polymorphic container
    std::vector<MedicalService> services;   // Service catalog

    // Helper: find patient by ID
    Patient* findPatient(const std::string& id);

    // Helper: find service by code
    const MedicalService* findService(const std::string& code) const;

public:
    HospitalSystem();
    ~HospitalSystem(); // Deletes all Person* to prevent memory leak

    // CRUD operations
    void addPatient(const std::string& id,
                    const std::string& name,
                    const std::string& insurance);

    void addDoctor(const std::string& id,
                   const std::string& name,
                   const std::string& specialization,
                   const std::string& clinicCode = "UNASSIGNED");

    void addMedicalService(const MedicalService& service);

    void scheduleAppointment(const std::string& patientId,
                             const std::string& serviceCode);

    void setAppointmentStatus(const std::string& patientId,
                              const std::string& serviceCode,
                              const std::string& status,
                              const std::string& modifier);

    // Display operations
    void viewAllUsers() const;         // Runtime polymorphism
    void viewServicesCatalog() const;
    void viewPatientExpenses(const std::string& patientId) const;
    void viewSystemStats() const;       // Uses static counts

    // Persistence
    void saveAllData() const;
    void loadAllData();
};
```

---

## STEP 14 — `src/HospitalSystem.cpp`

```cpp
#include "../include/HospitalSystem.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

HospitalSystem::HospitalSystem() {
    loadAllData(); // Auto-load on startup
}

// CRITICAL: Delete all dynamically allocated Person objects
HospitalSystem::~HospitalSystem() {
    for (Person* p : users) {
        delete p;  // Virtual destructor ensures correct derived dtor
        p = nullptr;
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
              << serviceCode << " → " << status << " (" << modifier << ")" << std::endl;
}

// VIEW ALL USERS — Runtime Polymorphism in action
void HospitalSystem::viewAllUsers() const {
    if (users.empty()) {
        std::cout << "  [INFO] No users registered." << std::endl;
        return;
    }
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "           ALL REGISTERED USERS" << std::endl;
    std::cout << std::string(55, '=') << std::endl;
    for (const Person* p : users) {
        p->displayRole(); // RUNTIME POLYMORPHISM: correct version called
    }
    std::cout << std::string(55, '=') << std::endl;
    std::cout << "  Total Users: " << Person::getTotalCount() << std::endl;
    std::cout << "  Patients: "    << Patient::getPatientCount() << std::endl;
    std::cout << "  Doctors: "     << Doctor::getDoctorCount() << std::endl;
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
                std::cout << "\n  Patient: " << pat->getName()
                          << " | Total Expenses: RM "
                          << std::fixed << std::setprecision(2)
                          << pat->calculateTotalMedicalExpenses() << std::endl;
            }
            return;
        }
    }
    throw std::runtime_error("Patient not found: " + patientId);
}

void HospitalSystem::viewSystemStats() const {
    std::cout << "\n--- System Statistics ---" << std::endl;
    std::cout << "  Total registered users : " << Person::getTotalCount() << std::endl;
    std::cout << "  Total patients         : " << Patient::getPatientCount() << std::endl;
    std::cout << "  Total doctors          : " << Doctor::getDoctorCount() << std::endl;
    std::cout << "  Total services         : " << services.size() << std::endl;
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
```

---

## STEP 15 — `src/main.cpp` (Entry Point + Menu)

```cpp
/**
 * main.cpp
 * Hospital Patient & Appointment Management System
 * CST209 — Object-Oriented Programming C++
 * Xiamen University Malaysia | 2026/04
 *
 * Author: [Your Name] | Student ID: [Your ID]
 */

#include "../include/HospitalSystem.h"
#include <iostream>
#include <limits>
#include <stdexcept>

// ─── UI Helpers ──────────────────────────────────────────────────────────────
void printHeader() {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "       HOSPITAL MANAGEMENT SYSTEM MENU" << std::endl;
    std::cout << std::string(55, '=') << std::endl;
    std::cout << "  1. Add New Patient" << std::endl;
    std::cout << "  2. Add New Doctor" << std::endl;
    std::cout << "  3. Add New Medical Service" << std::endl;
    std::cout << "  4. Schedule Appointment for Patient" << std::endl;
    std::cout << "  5. Set Appointment Status / Bill Modifier" << std::endl;
    std::cout << "  6. View All Users (Runtime Polymorphism)" << std::endl;
    std::cout << "  7. View Medical Services Catalog" << std::endl;
    std::cout << "  8. View Patient Medical Expenses" << std::endl;
    std::cout << "  9. View System Statistics (Static Counts)" << std::endl;
    std::cout << "  S. Save All Data to Files" << std::endl;
    std::cout << "  0. Exit System" << std::endl;
    std::cout << std::string(55, '-') << std::endl;
    std::cout << "  Enter choice: ";
}

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ─── Handler Functions ────────────────────────────────────────────────────────

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
    std::cout << "  Enter Service Code      : "; std::getline(std::cin, code);
    std::cout << "  Enter Service Name      : "; std::getline(std::cin, name);
    std::cout << "  Enter Base Fee (RM)     : "; std::getline(std::cin, feeStr);

    if (code.empty() || name.empty())
        throw std::invalid_argument("Service Code and Name cannot be empty.");

    if (feeStr.empty()) {
        // Use overloaded constructor (default fee = 50.0)
        MedicalService svc(code, name);
        std::cout << "  [INFO] Using default fee: RM 50.00" << std::endl;
        sys.addMedicalService(svc);
    } else {
        try {
            double fee = std::stod(feeStr);
            MedicalService svc(code, name, fee);
            sys.addMedicalService(svc);
        } catch (const std::invalid_argument&) {
            throw std::invalid_argument("Fee must be a valid number.");
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
    std::cout << "\n--- Set Appointment Status ---" << std::endl;
    std::cout << "  Enter Patient ID      : "; std::getline(std::cin, patientId);
    std::cout << "  Enter Service Code    : "; std::getline(std::cin, serviceCode);
    std::cout << "  New Status (Scheduled/Completed/Cancelled/Emergency): ";
    std::getline(std::cin, status);
    std::cout << "  Billing Modifier (Standard/Insured/Emergency): ";
    std::getline(std::cin, modifier);
    if (modifier.empty()) modifier = "Standard";
    sys.setAppointmentStatus(patientId, serviceCode, status, modifier);
}

void handleViewPatientExpenses(HospitalSystem& sys) {
    std::string id;
    std::cout << "\n--- View Patient Expenses ---" << std::endl;
    std::cout << "  Enter Patient ID : "; std::getline(std::cin, id);
    sys.viewPatientExpenses(id);
}

// ─── Main ────────────────────────────────────────────────────────────────────

int main() {
    HospitalSystem system; // Loads data from files on construction

    std::string choice;
    bool running = true;

    while (running) {
        printHeader();
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
                system.viewAllUsers(); // RUNTIME POLYMORPHISM
            } else if (choice == "7") {
                system.viewServicesCatalog();
            } else if (choice == "8") {
                handleViewPatientExpenses(system);
            } else if (choice == "9") {
                system.viewSystemStats(); // STATIC COUNTS
            } else if (choice == "s" || choice == "S") {
                system.saveAllData();
            } else if (choice == "0") {
                system.saveAllData(); // Auto-save on exit
                std::cout << "\n  [SYSTEM] Goodbye! Memory cleaned up.\n" << std::endl;
                running = false;
            } else {
                throw std::invalid_argument("Invalid menu choice: " + choice);
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "\n  [INPUT ERROR] " << e.what() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "\n  [SYSTEM ERROR] " << e.what() << std::endl;
        } catch (const std::ios_base::failure& e) {
            std::cerr << "\n  [FILE ERROR] " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "\n  [UNEXPECTED ERROR] " << e.what() << std::endl;
        }
    }

    // Destructor of HospitalSystem auto-deletes all Person* (no leak)
    return 0;
}
```

---

## STEP 16 — BUILD & TEST SEQUENCE

```bash
# 1. Create folders
mkdir -p HospitalManagement/src
mkdir -p HospitalManagement/include
mkdir -p HospitalManagement/data

# 2. Place all .h files in include/, all .cpp in src/

# 3. Compile (from HospitalManagement/ root)
g++ -std=c++17 -Wall -Wextra -I./include \
    src/Person.cpp \
    src/MedicalService.cpp \
    src/AppointmentRecord.cpp \
    src/Patient.cpp \
    src/Doctor.cpp \
    src/FileManager.cpp \
    src/HospitalSystem.cpp \
    src/main.cpp \
    -o hospital_system

# 4. Run
./hospital_system

# 5. Test checklist:
# ✅ Add patient → verify in View All Users
# ✅ Add doctor → verify in View All Users
# ✅ Add service with fee → verify in catalog
# ✅ Add service WITHOUT fee → verify default 50.0
# ✅ Schedule appointment → verify under patient
# ✅ Set status Completed/Insured → verify billing discount
# ✅ Set status Cancelled → verify 0.0 billing
# ✅ Set status Emergency → verify 1.5× billing
# ✅ View All Users → verify polymorphic output
# ✅ Save → exit → restart → verify data loaded
# ✅ Enter invalid menu option → verify exception caught
# ✅ Enter invalid patient ID → verify runtime_error caught
```

---

## STEP 17 — COMMON MISTAKES TO AVOID

| Mistake | Fix |
|---------|-----|
| Forgetting `virtual ~Person()` | Always add virtual destructor in ABC |
| `static int totalCount` not defined in `.cpp` | Define it exactly once in `Person.cpp` |
| Not calling `clearInputBuffer()` after `cin >>` | Use `std::getline` exclusively for consistency |
| Returning local reference to vector element | Use pointer or value return for `findService` |
| Not checking for duplicate IDs | Always loop through `users` before `push_back` |
| No `data/` folder at runtime | Create folder, or add check in FileManager |
| `dynamic_cast` returning `nullptr` unchecked | Always check `if (pat != nullptr)` after cast |
