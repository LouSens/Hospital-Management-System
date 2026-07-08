# 📋 PRODUCT REQUIREMENTS DOCUMENT (PRD)
## Hospital Patient & Appointment Management System
### Course: CST209 – Object-Oriented Programming C++
### Xiamen University Malaysia | Academic Session: 2026/04

---

## 1. EXECUTIVE SUMMARY

| Field              | Value                                                         |
|--------------------|---------------------------------------------------------------|
| Product Name       | Hospital Patient & Appointment Management System (HPAMS)      |
| Version            | 1.0.0                                                         |
| Course Code        | CST209*                                                       |
| Lecturer           | Danial Kafi Ahmad                                             |
| Deadline           | 9 July 2026, 11:59 PM                                         |
| Language           | C++ (C++17 Standard)                                          |
| Total Marks        | 100 (Part I: 70, Part II: 30)                                 |

---

## 2. PROBLEM STATEMENT

Hospital management requires a digitised, structured system to:
- Register and track patients with insurance details
- Manage doctor specialisations and clinic assignments
- Schedule, track, and bill medical appointments
- Apply billing modifiers (insurance tiers, emergency surcharges)
- Provide a unified view of all users via runtime polymorphism

---

## 3. GOALS & SUCCESS CRITERIA

| Goal | Success Criterion |
|------|-------------------|
| Demonstrate OOP Mastery | At least 3 classes with encapsulation, 1 ABC, 2 derived classes |
| Inheritance Hierarchy | `Person → Patient`, `Person → Doctor` working correctly |
| Runtime Polymorphism | `displayRole()` dispatched correctly via `vector<Person*>` |
| STL Usage | `std::vector`, `std::string`, `std::map` (or `std::unordered_map`) used appropriately |
| File Persistence | Data saved to and loaded from `.txt` or `.csv` files |
| Exception Handling | All invalid inputs caught, no crashes |
| Memory Safety | All `new` allocations matched with `delete`; no memory leaks |
| Quality Code | Separated header (`.h`) and implementation (`.cpp`) files |

---

## 4. FUNCTIONAL REQUIREMENTS

### FR-01: Patient Management
- **FR-01.1** System shall allow adding a new patient with: Patient ID, Name, Insurance Provider.
- **FR-01.2** System shall store patients using dynamic allocation (`new Patient(...)`).
- **FR-01.3** System shall allow scheduling an appointment for a patient linked to a `MedicalService`.
- **FR-01.4** System shall allow updating appointment status (Scheduled → Completed / Cancelled).
- **FR-01.5** System shall calculate total medical expenses for a patient across all appointments.

### FR-02: Doctor Management
- **FR-02.1** System shall allow adding a new doctor with: Doctor ID, Name, Specialisation Department.
- **FR-02.2** System shall allow assigning a doctor to a clinic using a clinic code.
- **FR-02.3** Doctor objects stored in the same `vector<Person*>` as patients.

### FR-03: Medical Service Management
- **FR-03.1** System shall allow adding a new medical service with: Service Code, Service Name, Base Fee.
- **FR-03.2** `MedicalService` shall have two overloaded constructors:
  - Constructor 1: `MedicalService(string code, string name, double fee)`
  - Constructor 2: `MedicalService(string code, string name)` — defaults `baseFee = 50.0`
- **FR-03.3** System shall display all available medical services.

### FR-04: Appointment Management
- **FR-04.1** `AppointmentRecord` shall compose a `MedicalService` (not inherit).
- **FR-04.2** Default status upon creation: `"Scheduled"`.
- **FR-04.3** System shall support three statuses: `"Scheduled"`, `"Completed"`, `"Cancelled"`.
- **FR-04.4** Billing calculation shall apply:
  - Standard: base fee × 1.0
  - Insurance modifier: base fee × 0.8 (20% discount if insured)
  - Emergency surcharge: base fee × 1.5
  - Cancelled: 0.0

### FR-05: Polymorphic Display
- **FR-05.1** "View All Users" menu option shall iterate `vector<Person*>` and call `displayRole()` for each.
- **FR-05.2** Patient's `displayRole()` shall print: ID, Name, Insurance, appointment count.
- **FR-05.3** Doctor's `displayRole()` shall print: ID, Name, Specialisation, Assigned Clinic.

### FR-06: File Persistence
- **FR-06.1** Patient data saved to `patients.txt`.
- **FR-06.2** Doctor data saved to `doctors.txt`.
- **FR-06.3** Medical services saved to `services.txt`.
- **FR-06.4** Appointment records saved to `appointments.txt`.
- **FR-06.5** On startup, system loads all data from files if they exist.

### FR-07: Static Members
- **FR-07.1** `Person` class shall have a `static int totalCount` to track all users (patients + doctors).
- **FR-07.2** `Patient` class shall have a `static int patientCount`.
- **FR-07.3** `Doctor` class shall have a `static int doctorCount`.
- **FR-07.4** Static members auto-increment in constructors; auto-decrement in destructors.

### FR-08: Exception Handling
- **FR-08.1** Invalid menu choices shall throw and catch `std::invalid_argument`.
- **FR-08.2** Scheduling appointment for non-existent patient/service shall throw `std::runtime_error`.
- **FR-08.3** Invalid fee input (non-numeric) shall be caught with `std::invalid_argument`.
- **FR-08.4** File I/O errors shall be caught with `std::ios_base::failure`.

---

## 5. NON-FUNCTIONAL REQUIREMENTS

| ID    | Requirement |
|-------|-------------|
| NFR-01 | Code must compile with `g++ -std=c++17` without warnings |
| NFR-02 | Source must be split across at minimum 4 `.h` and corresponding `.cpp` files |
| NFR-03 | UI must display a formatted menu (using `setw`, `=` borders) |
| NFR-04 | All class specifications in `.h` files; implementations in `.cpp` files |
| NFR-05 | No raw arrays for dynamic collections; `std::vector` required |
| NFR-06 | All `new` allocations must be `delete`d before program exit |
| NFR-07 | Code must include comments explaining key logic blocks |

---

## 6. SYSTEM ENTITIES (Domain Model)

```
┌─────────────────────────────────────────────────────────────────┐
│                         DOMAIN MODEL                            │
├──────────────┬──────────────────┬──────────────────────────────┤
│   Entity     │   Key Attributes │      Relationships           │
├──────────────┼──────────────────┼──────────────────────────────┤
│ Person (ABC) │ id, name         │ Base for Patient & Doctor    │
│ Patient      │ insuranceProvider│ Inherits Person              │
│              │ appointments[]   │ Has many AppointmentRecords  │
│ Doctor       │ specialization   │ Inherits Person              │
│              │ clinicCode       │ Assigned to MedicalService   │
│ MedicalSvc   │ code, name, fee  │ Composed in AppointmentRec   │
│ AppointRec   │ status, service  │ Has a MedicalService         │
└──────────────┴──────────────────┴──────────────────────────────┘
```

---

## 7. MENU STRUCTURE (User Stories)

```
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
 9. Save All Data to Files
 0. Exit System
=======================================================
```

---

## 8. EVALUATION CHECKLIST

### Part I (70 Marks)
- [ ] **Classes & Objects (20%)** — `MedicalService`, `AppointmentRecord`, `Person`, `Patient`, `Doctor` all implemented with proper encapsulation
- [ ] **Inheritance (10%)** — `Patient` and `Doctor` inherit from abstract `Person`
- [ ] **Polymorphism (10%)** — `displayRole()` pure virtual, overridden in both derived; overloaded constructors in `MedicalService`
- [ ] **STL/Files (10%)** — `vector<Person*>`, `vector<AppointmentRecord>`, file I/O with `fstream`
- [ ] **Exception Handling (5%)** — `try/catch` blocks for all error-prone inputs and operations
- [ ] **Quality (15%)** — Multi-file structure, formatted UI, named files appropriately, no crashes

### Part II (30 Marks)
- [ ] **STL Explanation (5%)** — Why `vector` and `string` suit this project
- [ ] **Inheritance & Polymorphism (20%)** — Rationale for hierarchy, explanation of virtual dispatch
- [ ] **Static Functions (5%)** — Why static members for counting; any extra advanced features

---

## 9. DELIVERABLES

| Deliverable | Format | Submission |
|-------------|--------|------------|
| Source Code | `.h` + `.cpp` files zipped | Moodle |
| Report | `.docx` Word format | Inside zip |
| Complete code included in report | Appendix section | Inside report |
| References/Citations | In-code comments + report reference list | Both |

---

## 10. CONSTRAINTS & ASSUMPTIONS

- Only standard C++ STL is allowed (no Boost, Qt, or third-party libs)
- Program must be a console application (no GUI)
- Must run on standard `g++` (GCC) or MSVC compiler
- No AI-generated code submission (university policy)
- Data persisted as plain text files (no SQLite or databases)
