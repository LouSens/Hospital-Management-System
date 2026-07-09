# Hospital Patient & Appointment Management System (HPAMS)
### CST209 — Object-Oriented Programming C++ | Xiamen University Malaysia 2026/04

**GitHub Repository:** [https://github.com/LouSens/Hospital-Management-System](https://github.com/LouSens/Hospital-Management-System)

---

## Build Instructions

### Prerequisites
- GCC with C++17 support (`g++ --version`)
- Windows: MinGW / MSYS2 or WSL

### Compile (one-liner)
```bash
g++ -std=c++17 -Wall -Wextra -I./include src/Person.cpp src/MedicalService.cpp src/AppointmentRecord.cpp src/Patient.cpp src/Doctor.cpp src/FileManager.cpp src/HospitalSystem.cpp src/main.cpp -o hospital_system
```

### Using Makefile (Linux/macOS/WSL)
```bash
make setup   # creates data/ folder and builds
make         # rebuild only
make clean   # remove binary
```

### Run
```bash
./hospital_system        # Linux / macOS / WSL
hospital_system.exe      # Windows CMD
```

---

## Project Structure

```
Hospital-Management-System/
├── include/              <- Header files (.h)
│   ├── Person.h
│   ├── Patient.h
│   ├── Doctor.h
│   ├── MedicalService.h
│   ├── AppointmentRecord.h
│   ├── HospitalSystem.h
│   └── FileManager.h
├── src/                  <- Source files (.cpp)
│   ├── main.cpp
│   ├── Person.cpp
│   ├── Patient.cpp
│   ├── Doctor.cpp
│   ├── MedicalService.cpp
│   ├── AppointmentRecord.cpp
│   ├── HospitalSystem.cpp
│   └── FileManager.cpp
├── data/                 <- Runtime data files (auto-created)
│   ├── patients.txt
│   ├── doctors.txt
│   ├── services.txt
│   └── appointments.txt
├── report/               <- Project report
│   └── report.docx
├── Makefile
└── README.md
```

---

## OOP Concepts Demonstrated

| Concept | Where |
|---------|-------|
| Abstract Base Class | `Person` — `displayRole()` pure virtual |
| Inheritance | `Patient`, `Doctor` inherit `Person` |
| Runtime Polymorphism | `viewAllUsers()` — `vector<Person*>` |
| Constructor Overloading | `MedicalService` — 2 constructors |
| Composition | `AppointmentRecord` HAS-A `MedicalService` |
| Static Members | `totalCount`, `patientCount`, `doctorCount` |
| STL | `vector`, `string`, `find_if`, `fstream` |
| Exception Handling | `try/catch` across all menu handlers |
| Memory Safety | `delete` in `~HospitalSystem()` |

---

## Diagrams

### 1. UML Class Diagram

```mermaid
classDiagram
    class Person {
        <<abstract>>
        #id: string
        #name: string
        +Person(id, name)
        +getId(): string
        +getName(): string
        +displayRole()* void
        +toFileString()* string
    }

    class Patient {
        -insuranceProvider: string
        +Patient(id, name, insurance)
        +getInsuranceProvider(): string
        +displayRole() void
        +toFileString() string
        +scheduleAppointment(service)
        +addAppointmentRecord(record)
        +calculateTotalMedicalExpenses(): double
    }

    class Doctor {
        -specialisation: string
        -clinicCode: string
        +Doctor(id, name, spec, clinic)
        +getSpecialisation(): string
        +getClinicCode(): string
        +displayRole() void
        +toFileString() string
    }

    Person <|-- Patient
    Person <|-- Doctor

    class MedicalService {
        -serviceCode: string
        -serviceName: string
        -requiredSpecialization: string
        -baseFee: double
        +MedicalService(code, name, spec, fee)
        +MedicalService(code, name, spec)
        +getServiceCode(): string
        +getServiceName(): string
        +getRequiredSpecialization(): string
        +getBaseFee(): double
        +toFileString(): string
    }

    class AppointmentRecord {
        -patientId: string
        -assignedDoctorId: string
        -assignedDoctorName: string
        -service: MedicalService
        -status: string
        -billingModifier: string
        +AppointmentRecord(...)
        +getPatientId(): string
        +getStatus(): string
        +calculateFinalFee(): double
        +toFileString(): string
    }

    AppointmentRecord *-- MedicalService : composition

    class HospitalSystem {
        -users: vector~Person*~
        -services: vector~MedicalService~
        +addPatient(...)
        +addDoctor(...)
        +addMedicalService(...)
        +scheduleAppointment(...)
        +viewAllUsers()
    }

    class FileManager {
        +loadUsers(...)
        +saveUsers(...)
        +loadServices(...)
        +saveServices(...)
    }

    HospitalSystem --> Person : manages (polymorphism)
    HospitalSystem --> MedicalService : manages
    HospitalSystem --> AppointmentRecord : manages
    HospitalSystem --> FileManager : uses for persistence
```

### 2. System Architecture

```mermaid
graph TD
    UI[Terminal CLI / main.cpp] --> |User Input & Commands| HS[HospitalSystem]
    HS --> |CRUD Operations| M[Data Models: Person, MedicalService, AppointmentRecord]
    HS --> |Save / Load triggers| FM[FileManager]
    FM --> |File I/O Read & Write| FS[(Text Files: .txt)]
    FS --> |Data parsing| FM
```

### 3. User Flow Diagram

```mermaid
flowchart TD
    Start([Start Program]) --> Menu{Main Menu}
    
    Menu -->|Choice 1| AddP[Add New Patient]
    Menu -->|Choice 2| AddD[Add New Doctor]
    Menu -->|Choice 3| AddS[Add Medical Service]
    Menu -->|Choice 4| Sched[Schedule Appointment]
    Menu -->|Choice 5| SetStatus[Set Appointment Status]
    Menu -->|Choice 6| ViewU[View All Users]
    Menu -->|Choice 7| ViewS[View Medical Services Catalog]
    Menu -->|Choice 8| ViewE[View Patient Expenses]
    Menu -->|Choice 9| ViewStats[View System Statistics]
    Menu -->|Choice S| Save[Save All Data]
    Menu -->|Choice 0| Exit([Save & Exit])

    AddP --> Menu
    AddD --> Menu
    AddS --> Menu
    Sched --> Menu
    SetStatus --> Menu
    ViewU --> Menu
    ViewS --> Menu
    ViewE --> Menu
    ViewStats --> Menu
    Save --> Menu
```

### 4. VTable (Dynamic Dispatch) Diagram

```mermaid
flowchart LR
    subgraph Vectors
        users["vector&lt;Person*&gt; users"]
    end

    subgraph Memory Heap
        P1["Patient Object\n- id: P001\n- __vptr"]
        D1["Doctor Object\n- id: D001\n- __vptr"]
    end

    subgraph Virtual Tables
        VT_P["Patient vtable\n1. Patient::~Patient()\n2. Patient::displayRole()"]
        VT_D["Doctor vtable\n1. Doctor::~Doctor()\n2. Doctor::displayRole()"]
    end

    users -->|users[0]| P1
    users -->|users[1]| D1

    P1 -->|__vptr| VT_P
    D1 -->|__vptr| VT_D
```
