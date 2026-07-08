# 🏗️ SYSTEM ARCHITECTURE & DESIGN
## Hospital Patient & Appointment Management System (HPAMS)
### CST209 — Object-Oriented Programming C++

---

## 1. ARCHITECTURAL OVERVIEW

```
┌─────────────────────────────────────────────────────────────────────────┐
│                    HPAMS — LAYERED ARCHITECTURE                         │
├─────────────────────────────────────────────────────────────────────────┤
│  PRESENTATION LAYER (main.cpp)                                          │
│  └── Console Menu UI │ User Input Handler │ Output Formatter            │
├─────────────────────────────────────────────────────────────────────────┤
│  BUSINESS LOGIC LAYER                                                   │
│  ├── HospitalSystem.h/.cpp  (System Controller)                         │
│  ├── Patient.h/.cpp         (Patient Logic)                             │
│  ├── Doctor.h/.cpp          (Doctor Logic)                              │
│  └── AppointmentRecord.h/.cpp (Billing & Status Logic)                  │
├─────────────────────────────────────────────────────────────────────────┤
│  DOMAIN MODEL LAYER                                                     │
│  ├── Person.h               (Abstract Base Class)                       │
│  ├── MedicalService.h/.cpp  (Service Entity)                            │
│  └── BillingCalculator.h    (Billing Strategy)                          │
├─────────────────────────────────────────────────────────────────────────┤
│  PERSISTENCE LAYER (FileManager.h/.cpp)                                 │
│  └── patients.txt │ doctors.txt │ services.txt │ appointments.txt        │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 2. FILE STRUCTURE

```
HospitalManagement/
│
├── src/
│   ├── main.cpp                  ← Entry point; main menu loop
│   ├── HospitalSystem.cpp        ← System controller (aggregates all)
│   ├── Person.cpp                ← Person static member definitions
│   ├── Patient.cpp               ← Patient method implementations
│   ├── Doctor.cpp                ← Doctor method implementations
│   ├── MedicalService.cpp        ← MedicalService implementations
│   ├── AppointmentRecord.cpp     ← AppointmentRecord implementations
│   └── FileManager.cpp           ← File I/O implementations
│
├── include/
│   ├── Person.h                  ← Abstract Base Class (ABC)
│   ├── Patient.h                 ← Patient class declaration
│   ├── Doctor.h                  ← Doctor class declaration
│   ├── MedicalService.h          ← MedicalService class declaration
│   ├── AppointmentRecord.h       ← AppointmentRecord class declaration
│   ├── HospitalSystem.h          ← System manager class declaration
│   └── FileManager.h             ← File manager class declaration
│
├── data/
│   ├── patients.txt              ← Persisted patient records
│   ├── doctors.txt               ← Persisted doctor records
│   ├── services.txt              ← Persisted service catalog
│   └── appointments.txt          ← Persisted appointment records
│
├── report/
│   └── report.docx               ← Final project report
│
└── README.md                     ← Build instructions
```

---

## 3. CLASS DIAGRAM

```
                    ┌───────────────────────────┐
                    │         <<ABC>>           │
                    │           Person          │
                    ├───────────────────────────┤
                    │ # name: string            │
                    │ # id: string              │
                    │ - static totalCount: int  │
                    ├───────────────────────────┤
                    │ + Person(string, string)  │
                    │ + ~Person() [virtual]     │
                    │ + getName(): string       │
                    │ + getId(): string         │
                    │ + getTotalCount(): int    │ ← static
                    │ + displayRole() = 0       │ ← pure virtual
                    └─────────────┬─────────────┘
                                  │ inherits
               ┌──────────────────┼──────────────────┐
               ▼                                     ▼
┌──────────────────────────┐       ┌──────────────────────────────┐
│         Patient          │       │            Doctor            │
├──────────────────────────┤       ├──────────────────────────────┤
│ - insuranceProvider:str  │       │ - specializationDept: string │
│ - appointments: vector<> │       │ - assignedClinicCode: string │
│ - static patientCount:int│       │ - static doctorCount: int    │
├──────────────────────────┤       ├──────────────────────────────┤
│ + Patient(str,str,str)   │       │ + Doctor(str,str,str)        │
│ + displayRole() override │       │ + displayRole() override     │
│ + scheduleAppointment()  │       │ + assignToClinic(string)     │
│ + getPatientCount(): int │←static│ + getPatientCount(): int     │ ←static
│ + calculateTotal(): dbl  │       │ + getDoctorCount(): int      │ ←static
│ + ~Patient()             │       │ + ~Doctor()                  │
└──────────────────────────┘       └──────────────────────────────┘
         │ has many
         ▼
┌──────────────────────────┐          ┌──────────────────────────┐
│    AppointmentRecord     │ composes │      MedicalService      │
├──────────────────────────┤◄─────────├──────────────────────────┤
│ - service: MedicalService│          │ - serviceCode: string    │
│ - appointmentStatus: str │          │ - serviceName: string    │
├──────────────────────────┤          │ - baseFee: double        │
│ + AppointmentRecord()    │          ├──────────────────────────┤
│ + getServiceCode(): str  │          │ + MedicalService(s,n,f)  │ ← ctor 1
│ + getStatus(): string    │          │ + MedicalService(s,n)    │ ← ctor 2
│ + calculateBilling(): dbl│          │ + displayService()       │
│ + setStatus(string)      │          │ + getCode(): string      │
└──────────────────────────┘          │ + getName(): string      │
                                      │ + getFee(): double       │
                                      └──────────────────────────┘


┌─────────────────────────────────────────┐
│           HospitalSystem                │
├─────────────────────────────────────────┤
│ - users: vector<Person*>                │ ← polymorphic container
│ - services: vector<MedicalService>      │
├─────────────────────────────────────────┤
│ + addPatient()                          │
│ + addDoctor()                           │
│ + addMedicalService()                   │
│ + scheduleAppointment()                 │
│ + setAppointmentStatus()                │
│ + viewAllUsers()                        │ ← runtime polymorphism
│ + viewServicesCatalog()                 │
│ + viewPatientExpenses()                 │
│ + saveAllData()                         │
│ + loadAllData()                         │
│ + ~HospitalSystem()                     │ ← cleanup: delete all Person*
└─────────────────────────────────────────┘
```

---

## 4. INHERITANCE & POLYMORPHISM DESIGN

### 4.1 Inheritance Chain

```
         Person (ABC — cannot be instantiated directly)
           │
           ├──► Patient  (concrete — CAN be instantiated)
           │
           └──► Doctor   (concrete — CAN be instantiated)
```

**Why Abstract Base Class (ABC)?**
- `Person` defines the INTERFACE for all hospital users
- `displayRole()` is declared `= 0` → forces every subclass to implement its own version
- Prevents accidentally creating a generic "Person" object (which has no role)

### 4.2 Virtual Dispatch Table (vtable) — Runtime Polymorphism

```
vector<Person*> users;
users.push_back(new Patient("P001", "Alice", "Prudential"));
users.push_back(new Doctor("D001", "Dr. Smith", "Cardiology"));

for (Person* p : users) {
    p->displayRole();   // ← C++ resolves the correct version AT RUNTIME
}
//  Alice → calls Patient::displayRole()
//  Dr. Smith → calls Doctor::displayRole()
```

### 4.3 Composition vs Inheritance

```
AppointmentRecord  ──has-a──►  MedicalService   [COMPOSITION]
Patient            ──is-a───►  Person           [INHERITANCE]
Doctor             ──is-a───►  Person           [INHERITANCE]
```

**Why Composition for AppointmentRecord?**
- An appointment CONTAINS a service (not IS a service)
- MedicalService can exist independently without AppointmentRecord
- Follows the OOP principle: "Favour composition over inheritance"

---

## 5. BILLING CALCULATION STRATEGY

```
┌─────────────────────────────────────────────────────────┐
│               BILLING MODIFIER LOGIC                    │
├─────────────────────────┬───────────────────────────────┤
│ Status / Condition      │ Billing Formula               │
├─────────────────────────┼───────────────────────────────┤
│ "Cancelled"             │ 0.00 (no charge)              │
│ "Scheduled" (standard)  │ baseFee × 1.0                 │
│ "Completed" (insured)   │ baseFee × 0.8 (20% discount)  │
│ "Emergency"             │ baseFee × 1.5 (50% surcharge) │
└─────────────────────────┴───────────────────────────────┘
```

---

## 6. DATA FLOW DIAGRAM

```
┌──────────┐   input    ┌──────────────┐   calls    ┌──────────────┐
│   User   │──────────►│   main.cpp   │───────────►│HospitalSystem│
│(console) │           │  (menu loop) │            │  Controller  │
└──────────┘           └──────────────┘            └──────┬───────┘
                                                          │
                           ┌──────────────────────────────┤
                           │              │               │
                      ┌────▼────┐   ┌────▼────┐   ┌──────▼──────┐
                      │ Patient │   │ Doctor  │   │MedicalService│
                      │ objects │   │ objects │   │  catalog    │
                      └────┬────┘   └────┬────┘   └─────────────┘
                           │             │
                    ┌──────▼─────────────▼──────┐
                    │       FileManager          │
                    │  patients.txt, doctors.txt │
                    │  services.txt              │
                    │  appointments.txt          │
                    └───────────────────────────┘
```

---

## 7. MEMORY MANAGEMENT STRATEGY

```
ALLOCATION:
  Person* p = new Patient(...)    // allocated on heap
  users.push_back(p)              // stored in vector

CLEANUP (in HospitalSystem destructor):
  ~HospitalSystem() {
      for (Person* p : users) {
          delete p;               // calls virtual destructor
          p = nullptr;
      }
      users.clear();
  }

VIRTUAL DESTRUCTOR (critical!):
  class Person {
      virtual ~Person() {}        // ensures derived dtor is called
  };
```

---

## 8. STL SELECTION RATIONALE

| STL Container/Feature | Where Used | Justification |
|-----------------------|------------|---------------|
| `std::vector<Person*>` | `HospitalSystem::users` | Dynamic size; supports polymorphism via pointers; random access |
| `std::vector<AppointmentRecord>` | `Patient::appointments` | Each patient has variable number of appointments |
| `std::vector<MedicalService>` | `HospitalSystem::services` | Catalog of services; grows at runtime |
| `std::string` | All attributes | Safe, managed strings vs raw `char[]` |
| `std::fstream` | `FileManager` | File read/write for persistence |
| `std::iomanip` (setw, left) | Menu display | Professional, aligned console output |
| `std::find_if` + lambda | Appointment search | Clean, idiomatic search in `vector` |

---

## 9. EXCEPTION HANDLING ARCHITECTURE

```
┌────────────────────────────────────────────────────────────┐
│                  EXCEPTION HIERARCHY                       │
├────────────────────────────────────────────────────────────┤
│  std::exception                                            │
│    ├── std::invalid_argument  → invalid menu / bad input   │
│    ├── std::runtime_error     → patient/service not found  │
│    ├── std::out_of_range      → vector index out of bounds │
│    └── std::ios_base::failure → file open/read failure     │
└────────────────────────────────────────────────────────────┘

PATTERN used in every menu handler:
  try {
      // read and validate input
      // call system function
  } catch (const std::invalid_argument& e) {
      std::cerr << "[INPUT ERROR] " << e.what() << std::endl;
  } catch (const std::runtime_error& e) {
      std::cerr << "[SYSTEM ERROR] " << e.what() << std::endl;
  } catch (const std::exception& e) {
      std::cerr << "[UNEXPECTED ERROR] " << e.what() << std::endl;
  }
```

---

## 10. STATIC MEMBER DESIGN

```
class Person {
    static int totalCount;          // shared across ALL Person instances
public:
    static int getTotalCount();
    Person(...)  { totalCount++; }  // increment on creation
    ~Person()    { totalCount--; }  // decrement on deletion
};

class Patient : public Person {
    static int patientCount;
public:
    static int getPatientCount();
    Patient(...) : Person(...) { patientCount++; }
    ~Patient() { patientCount--; }
};

class Doctor : public Person {
    static int doctorCount;
    // same pattern
};
```

**Why static?**
- Belongs to the CLASS, not any object instance
- Persists across all objects; tracks system-wide counts
- Accessed as `Patient::getPatientCount()` without needing an object

---

## 11. BUILD CONFIGURATION

```makefile
# Makefile (optional but recommended)
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

SRCS = src/main.cpp \
       src/Person.cpp \
       src/Patient.cpp \
       src/Doctor.cpp \
       src/MedicalService.cpp \
       src/AppointmentRecord.cpp \
       src/HospitalSystem.cpp \
       src/FileManager.cpp

TARGET = hospital_system

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
```

**Manual compile (one-liner):**
```bash
g++ -std=c++17 -Wall -I./include src/*.cpp -o hospital_system
```

---

## 12. RUNTIME SEQUENCE (View All Users)

```
main()
  │
  ├── input: 6 (View All Users)
  │
  └── HospitalSystem::viewAllUsers()
          │
          ├── for (Person* p : users)
          │       │
          │       ├── if p is Patient* → Patient::displayRole()
          │       │       prints: [PATIENT] ID, Name, Insurance, #Appts
          │       │
          │       └── if p is Doctor* → Doctor::displayRole()
          │               prints: [DOCTOR] ID, Name, Dept, Clinic
          │
          └── (vtable resolves at runtime — no if/else needed!)
```
