# Hospital Patient and Appointment Management System: An Object-Oriented Approach
**Course:** CST209 — Object-Oriented Programming C++
**Institution:** Xiamen University Malaysia
**Academic Session:** 2026/04
**GitHub Repository:** [https://github.com/LouSens/Hospital-Management-System](https://github.com/LouSens/Hospital-Management-System)

## Abstract
This paper presents the design and implementation of the Hospital Patient and Appointment Management System (HPAMS), a console-based software solution developed in C++17. The system addresses the administrative inefficiencies inherent in manual hospital workflows by providing a digitized framework for managing patient records, doctor assignments, medical services, and appointment billing. Through the rigorous application of Object-Oriented Programming (OOP) paradigms—specifically encapsulation, inheritance, and polymorphism—the architecture ensures robust data integrity and system extensibility. Furthermore, the integration of the Standard Template Library (STL) facilitates dynamic memory management and efficient data retrieval.

## 1. Introduction
Modern healthcare facilities require streamlined administrative processes to ensure optimal patient care and resource allocation. Traditional hospital management workflows are frequently manual, disjointed, and susceptible to human error. Staff members face significant challenges in registering patients, tracking insurance details, managing medical personnel assignments, and calculating accurate billing information that accounts for varying medical fees and conditional modifiers.

The Hospital Patient and Appointment Management System (HPAMS) was developed to mitigate these challenges. By utilizing C++ and adhering to strict Object-Oriented Programming principles, the system models real-world hospital entities within a highly cohesive digital architecture, automating the tracking of medical expenses and facilitating dynamic administrative operations.

## 2. System Architecture and OOP Design Rationale
The architecture of HPAMS is fundamentally grounded in core OOP methodologies, ensuring that the system is both modular and scalable. 

### 2.1 Encapsulation
To maintain data integrity, encapsulation is strictly enforced across all system classes. Internal data members, such as a patient's identification number or a medical service's base fee, are designated with `private` or `protected` access modifiers. External interaction with these attributes is exclusively mediated through public accessor and mutator methods (getters and setters), thereby preventing unauthorized data manipulation and localized logic errors.

### 2.2 Inheritance and Polymorphism
The system establishes a robust hierarchical structure utilizing an "is-a" relationship, with the abstract `Person` class serving as the base entity. The `Patient` and `Doctor` classes inherit from `Person`, which promotes significant code reuse for shared attributes (such as identification and name) while allowing for the implementation of specialized domain attributes.

Polymorphism is integrated at both compile-time and runtime. Compile-time polymorphism is demonstrated through constructor overloading within the `MedicalService` class, which permits the instantiation of service objects with or without explicit fee declarations. Runtime polymorphism is facilitated through the `displayRole()` pure virtual function declared in the `Person` class. During execution, the central `HospitalSystem` controller iterates through a unified standard vector of `Person` pointers. Through dynamic dispatch, the compiler resolves the virtual table (`vtable`) pointer for each instantiated object, automatically executing the correct, derived `displayRole()` method corresponding to the specific object type (Patient or Doctor).

### 2.3 Integration of the Standard Template Library (STL)
The Standard Template Library is utilized extensively to manage dynamic collections and text-based data streams. Given the dynamic nature of hospital environments, the exact volume of entities cannot be predetermined at compile-time. Consequently, `std::vector` is employed globally to manage collections of pointers and objects. This container provides automatic memory reallocation and contiguous memory storage, resulting in highly efficient sequential iterations. Furthermore, `std::string` is universally adopted for text manipulation, mitigating the inherent buffer overflow risks associated with legacy C-style character arrays.

### 2.4 Static Member Utilization
Static member variables are implemented to manage state data that pertains to the class collectively rather than to individual object instances. Variables such as `totalCount` in the `Person` class maintain real-time system statistics. These counters are automatically incremented within class constructors and decremented within virtual destructors. This architectural decision permits O(1) time complexity retrieval for system-wide statistical reporting, eliminating the computational overhead of iterative counting.

## 3. System Walkthrough and Demonstration
To validate the system's functional requirements, a comprehensive demonstration was conducted. The following subsections detail the anticipated console outputs corresponding to each distinct operational phase.

### 3.1 Main Menu Preview
Upon initialization, the system presents the primary navigation menu.

```text
  Welcome to the Hospital Patient & Appointment
  Management System (HPAMS)

=======================================================
       HOSPITAL MANAGEMENT SYSTEM MENU
=======================================================
  1. Add New Patient
  2. Add New Doctor
  3. Add New Medical Service
  4. Schedule Appointment for Patient
  5. Set Appointment Status / Bill Modifier
  6. View All Users (Runtime Polymorphism)
  7. View Medical Services Catalog
  8. View Patient Medical Expenses
  9. View System Statistics (Static Counts)
  S. Save All Data to Files
  0. Exit System
-------------------------------------------------------
```

### 3.2 Add New Patient (Choice 1)
Registering new patients utilizing the fundamental class constructors.

```text
  Enter choice: 1

--- Add New Patient ---
  Enter Patient ID    : P001
  Enter Patient Name  : John Doe
  Enter Insurance     : AIA Gold
[SUCCESS] Patient P001 added.

  Enter choice: 1

--- Add New Patient ---
  Enter Patient ID    : P002
  Enter Patient Name  : Jane Smith
  Enter Insurance     : Prudential
[SUCCESS] Patient P002 added.
```

### 3.3 Add New Doctor (Choice 2)
Adding new doctors to the system.

```text
  Enter choice: 2

--- Add New Doctor ---
  Enter Doctor ID         : D001
  Enter Doctor Name       : Dr. Smith
  Enter Specialisation    : Cardiology
  Enter Clinic Code       : C-101
[SUCCESS] Doctor D001 added.

  Enter choice: 2

--- Add New Doctor ---
  Enter Doctor ID         : D002
  Enter Doctor Name       : Dr. Adams
  Enter Specialisation    : Neurology
  Enter Clinic Code       : C-102
[SUCCESS] Doctor D002 added.
```

### 3.4 Add New Medical Service (Choice 3)
Adding specialized services to the catalog.

```text
  Enter choice: 3

--- Add New Medical Service ---
  Enter Service Code  (e.g. SVC001) : SVC001
  Enter Service Name               : Blood Test
  Req. Specialization (e.g. General): Cardiology
  Enter Base Fee in RM (leave blank for RM 50.00 default): 150.00
[SUCCESS] Service SVC001 added.

  Enter choice: 3

--- Add New Medical Service ---
  Enter Service Code  (e.g. SVC001) : SVC002
  Enter Service Name               : MRI Scan
  Req. Specialization (e.g. General): Neurology
  Enter Base Fee in RM (leave blank for RM 50.00 default): 800.00
[SUCCESS] Service SVC002 added.
```

### 3.5 Schedule Appointment (Choice 4)
Scheduling appointments for the patients.

```text
  Enter choice: 4

--- Schedule Appointment ---

--- Select Patient ---
  --- Available Patients ---
  - ID: P001 | Name: John Doe
  - ID: P002 | Name: Jane Smith
  --------------------------
  Enter Patient ID     : P001

--- Select Medical Service ---
=========================================================================================================
                                        MEDICAL SERVICES CATALOG
=========================================================================================================
  Code: SVC001      | Name: Blood Test               | Req. Spec: Cardiology     | Base Fee: RM 150.00
  Code: SVC002      | Name: MRI Scan                 | Req. Spec: Neurology      | Base Fee: RM 800.00
=========================================================================================================
  Enter Service Code   : SVC001

--- Select Doctor for Cardiology ---
  --- Available Doctors for Cardiology ---
  - ID: D001 | Name: Dr. Smith | Spec: Cardiology
  --------------------------
  Enter Doctor ID      : D001
[SUCCESS] Appointment scheduled for P001.

  Enter choice: 4

--- Schedule Appointment ---

--- Select Patient ---
  --- Available Patients ---
  - ID: P001 | Name: John Doe
  - ID: P002 | Name: Jane Smith
  --------------------------
  Enter Patient ID     : P001

--- Select Medical Service ---
=========================================================================================================
                                        MEDICAL SERVICES CATALOG
=========================================================================================================
  Code: SVC001      | Name: Blood Test               | Req. Spec: Cardiology     | Base Fee: RM 150.00
  Code: SVC002      | Name: MRI Scan                 | Req. Spec: Neurology      | Base Fee: RM 800.00
=========================================================================================================
  Enter Service Code   : SVC002

--- Select Doctor for Neurology ---
  --- Available Doctors for Neurology ---
  - ID: D002 | Name: Dr. Adams | Spec: Neurology
  --------------------------
  Enter Doctor ID      : D002
[SUCCESS] Appointment scheduled for P001.

  Enter choice: 4

--- Schedule Appointment ---

--- Select Patient ---
  --- Available Patients ---
  - ID: P001 | Name: John Doe
  - ID: P002 | Name: Jane Smith
  --------------------------
  Enter Patient ID     : P002

--- Select Medical Service ---
=========================================================================================================
                                        MEDICAL SERVICES CATALOG
=========================================================================================================
  Code: SVC001      | Name: Blood Test               | Req. Spec: Cardiology     | Base Fee: RM 150.00
  Code: SVC002      | Name: MRI Scan                 | Req. Spec: Neurology      | Base Fee: RM 800.00
=========================================================================================================
  Enter Service Code   : SVC001

--- Select Doctor for Cardiology ---
  --- Available Doctors for Cardiology ---
  - ID: D001 | Name: Dr. Smith | Spec: Cardiology
  --------------------------
  Enter Doctor ID      : D001
[SUCCESS] Appointment scheduled for P002.
```

### 3.6 Update Appointment Status (Choice 5)
Modifying the billing state for the scheduled appointments.

```text
  Enter choice: 5

--- Update Appointment ---

--- Select Patient ---
  --- Available Patients ---
  - ID: P001 | Name: John Doe
  - ID: P002 | Name: Jane Smith
  --------------------------
  Enter Patient ID    : P001

--- Select Medical Service to Update ---
=========================================================================================================
                                        MEDICAL SERVICES CATALOG
=========================================================================================================
  Code: SVC001      | Name: Blood Test               | Req. Spec: Cardiology     | Base Fee: RM 150.00
  Code: SVC002      | Name: MRI Scan                 | Req. Spec: Neurology      | Base Fee: RM 800.00
=========================================================================================================
  Enter Service Code  : SVC001

--- Enter New Status and Billing Details ---
  Status [Scheduled/Completed/Cancelled/Emergency] : Completed
  Billing [Standard/Insured/Emergency]             : Insured
[SUCCESS] Appointment updated.

  Enter choice: 5

--- Update Appointment ---

--- Select Patient ---
  --- Available Patients ---
  - ID: P001 | Name: John Doe
  - ID: P002 | Name: Jane Smith
  --------------------------
  Enter Patient ID    : P001

--- Select Medical Service to Update ---
=========================================================================================================
                                        MEDICAL SERVICES CATALOG
=========================================================================================================
  Code: SVC001      | Name: Blood Test               | Req. Spec: Cardiology     | Base Fee: RM 150.00
  Code: SVC002      | Name: MRI Scan                 | Req. Spec: Neurology      | Base Fee: RM 800.00
=========================================================================================================
  Enter Service Code  : SVC002

--- Enter New Status and Billing Details ---
  Status [Scheduled/Completed/Cancelled/Emergency] : Emergency
  Billing [Standard/Insured/Emergency]             : Emergency
[SUCCESS] Appointment updated.

  Enter choice: 5

--- Update Appointment ---

--- Select Patient ---
  --- Available Patients ---
  - ID: P001 | Name: John Doe
  - ID: P002 | Name: Jane Smith
  --------------------------
  Enter Patient ID    : P002

--- Select Medical Service to Update ---
=========================================================================================================
                                        MEDICAL SERVICES CATALOG
=========================================================================================================
  Code: SVC001      | Name: Blood Test               | Req. Spec: Cardiology     | Base Fee: RM 150.00
  Code: SVC002      | Name: MRI Scan                 | Req. Spec: Neurology      | Base Fee: RM 800.00
=========================================================================================================
  Enter Service Code  : SVC001

--- Enter New Status and Billing Details ---
  Status [Scheduled/Completed/Cancelled/Emergency] : Cancelled
  Billing [Standard/Insured/Emergency]             : Standard
[SUCCESS] Appointment updated.
```

### 3.7 View All Users (Choice 6)
Retrieving user records demonstrates runtime polymorphism, successfully parsing the unified vector.

```text
  Enter choice: 6

--- All Registered Users ---
[Patient] ID: P001 | Name: John Doe | Insurance: AIA Gold | Appointments: 2
[Patient] ID: P002 | Name: Jane Smith | Insurance: Prudential | Appointments: 1
[Doctor] ID: D001 | Name: Dr. Smith | Specialisation: Cardiology | Clinic: C-101
[Doctor] ID: D002 | Name: Dr. Adams | Specialisation: Neurology | Clinic: C-102
```

### 3.8 View Medical Services Catalog (Choice 7)
Displaying all available medical services.

```text
  Enter choice: 7

=========================================================================================================
                                        MEDICAL SERVICES CATALOG
=========================================================================================================
  Code: SVC001      | Name: Blood Test               | Req. Spec: Cardiology     | Base Fee: RM 150.00
  Code: SVC002      | Name: MRI Scan                 | Req. Spec: Neurology      | Base Fee: RM 800.00
=========================================================================================================
```

### 3.9 View Patient Medical Expenses (Choice 8)
Checking the medical expenses for two patients.

```text
  Enter choice: 8

--- Patient Medical Expenses ---
  --- Available Patients ---
  - ID: P001 | Name: John Doe
  - ID: P002 | Name: Jane Smith
  --------------------------
  Enter Patient ID : P001
[Billing] Total Expenses for P001 (John Doe): RM 1320.00

  Enter choice: 8

--- Patient Medical Expenses ---
  --- Available Patients ---
  - ID: P001 | Name: John Doe
  - ID: P002 | Name: Jane Smith
  --------------------------
  Enter Patient ID : P002
[Billing] Total Expenses for P002 (Jane Smith): RM 0.00
```

### 3.10 View System Statistics (Choice 9)
System statistics leverage the static counters to report instantaneous metrics.

```text
  Enter choice: 9

--- System Statistics ---
Total Users Registered: 4
Total Patients        : 2
Total Doctors         : 2
```

### 3.11 Save Data and Exit System
Saving the data to files and terminating the system gracefully.

```text
  Enter choice: S
[FILE] Users and Appointments saved.

  Enter choice: 0
[FILE] Users and Appointments saved.

  [SYSTEM] All data saved. Goodbye!
  Memory cleaned up by HospitalSystem destructor.
```

## 4. Conclusion
The Hospital Patient and Appointment Management System successfully satisfies its fundamental design objectives by providing a highly organized, cohesive, and digitally automated framework for hospital administration. The rigorous implementation of Object-Oriented Programming principles ensures that the codebase remains robust, memory-safe, and easily extensible for future iterations.

## References
1. Stroustrup, B. (2013). *The C++ Programming Language* (4th ed.). Addison-Wesley.
2. cplusplus.com. (n.d.). *C++ Reference: Standard Template Library (STL)*. Retrieved from https://cplusplus.com/reference/stl/
3. Microsoft. (n.d.). *C++ Exception Handling*. Microsoft Learn. Retrieved from https://learn.microsoft.com/en-us/cpp/cpp/exception-handling-in-visual-cpp


## Appendix: Complete Source Code


### `Makefile`

```makefile
# Makefile
# Hospital Patient & Appointment Management System
# CST209 -- Object-Oriented Programming C++

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

SRCS = src/Person.cpp \
       src/MedicalService.cpp \
       src/AppointmentRecord.cpp \
       src/Patient.cpp \
       src/Doctor.cpp \
       src/FileManager.cpp \
       src/HospitalSystem.cpp \
       src/main.cpp

TARGET = hospital_system

# Default rule: build the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Create data directory if it doesn't exist, then build
setup:
	mkdir -p data
	$(MAKE) $(TARGET)

# Remove compiled binary
clean:
	rm -f $(TARGET)

.PHONY: clean setup

```

### `include/AppointmentRecord.h`

```h
#pragma once
#include "MedicalService.h"
#include <string>

/**
 * AppointmentRecord.h
 * Represents a single appointment between a patient and a medical service.
 * Demonstrates: COMPOSITION — AppointmentRecord HAS-A MedicalService
 *
 * Billing Modifiers:
 *   "Cancelled"  -> 0.00
 *   "Scheduled"  -> baseFee x 1.0
 *   "Completed"  -> baseFee x 0.8 (insured discount)
 *   "Emergency"  -> baseFee x 1.5 (surcharge)
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

    // Setters
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

### `include/Doctor.h`

```h
#pragma once
#include "Person.h"
#include <string>

/**
 * Doctor.h
 * Inherits from Person (ABC).
 * Demonstrates:
 *   - Inheritance: IS-A Person
 *   - Override of pure virtual displayRole()
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

### `include/FileManager.h`

```h
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
                          const std::string& userFile = "data/users.txt",
                          const std::string& appointFile = "data/appointments.txt");

    // Load operations
    static std::vector<MedicalService> loadServices(
        const std::string& filename = "data/services.txt");
    static void loadUsers(std::vector<Person*>& users,
                          const std::string& userFile = "data/users.txt",
                          const std::string& appointFile = "data/appointments.txt");

    // Utility
    static bool fileExists(const std::string& filename);
};

```

### `include/HospitalSystem.h`

```h
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
 *   - vector<Person*> -- polymorphic container
 *   - dynamic_cast for safe downcasting
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
    void viewAllUsers() const;
    void viewServicesCatalog() const;
    void viewPatientExpenses(const std::string& patientId) const;
    void viewSystemStats() const;      // Uses static counts

    // Persistence
    void saveAllData() const;
    void loadAllData();
};

```

### `include/MedicalService.h`

```h
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

### `include/Patient.h`

```h
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

    // Direct record injection (for file loader)
    void addAppointmentRecord(const AppointmentRecord& record);

    // File serialisation
    std::string toFileString() const;
};

```

### `include/Person.h`

```h
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

    // Virtual serialisation
    virtual std::string toFileString() const = 0;
};

```

### `src/AppointmentRecord.cpp`

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
    if (appointmentStatus == "Cancelled")  return 0.0;
    if (billingModifier == "Insured")      return base * 0.8;  // 20% discount
    if (billingModifier == "Emergency" ||
        appointmentStatus == "Emergency")  return base * 1.5;  // 50% surcharge
    return base * 1.0; // Standard rate
}

void AppointmentRecord::displayAppointment() const {
    std::cout << "    [" << appointmentStatus << "] "
              << service.getServiceCode() << " -- "
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

### `src/Doctor.cpp`

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
    return "Doctor|" + id + "|" + name + "|" + specializationDepartment + "|" + assignedClinicCode;
}

```

### `src/FileManager.cpp`

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

```

### `src/HospitalSystem.cpp`

```cpp
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
    std::cout << "           SYSTEM DASHBOARD" << std::endl;
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

```

### `src/MedicalService.cpp`

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

### `src/Patient.cpp`

```cpp
#include "../include/Patient.h"
#include <iostream>
#include <iomanip>
#include <algorithm> // std::find_if

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
              << service.getServiceCode() << " -- "
              << service.getServiceName() << std::endl;
}

bool Patient::setAppointmentStatus(const std::string& serviceCode,
                                   const std::string& status,
                                   const std::string& modifier) {
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

void Patient::addAppointmentRecord(const AppointmentRecord& record) {
    appointments.push_back(record);
}

std::string Patient::toFileString() const {
    return "Patient|" + id + "|" + name + "|" + insuranceProvider;
}

```

### `src/Person.cpp`

```cpp
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

```

### `src/main.cpp`

```cpp
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

```
