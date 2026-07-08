# Hospital Management System - Comprehensive Demo Flow

This guide provides a comprehensive manual testing flow. Follow these steps to populate the system with multiple records, proving that all functionalities—including data persistence, polymorphism, static counts, and complex billing logic—work perfectly.

### 1. Starting the Application
Open your terminal (PowerShell) in the project directory and run the executable:
```powershell
.\hospital_system.exe
```

Upon starting, the application will display the welcome message and the main menu:

```text
  Welcome to the Hospital Patient & Appointment
  Management System (HPAMS) — CST209

=======================================================
       HOSPITAL MANAGEMENT SYSTEM MENU
=======================================================
  1. Add New Patient
  2. Add New Doctor
  3. Add New Medical Service
  4. Schedule Appointment for Patient
  5. Set Appointment Status / Bill Modifier
  6. View All Users
  7. View Medical Services Catalog
  8. View Patient Medical Expenses
  9. View System Statistics (Static Counts)
  S. Save All Data to Files
  0. Exit System
-------------------------------------------------------
  Enter choice: 
```

### 2. Comprehensive Data Entry Flow

Run through the following steps sequentially and take screenshots of the outputs.

#### **Step A: Add Multiple Patients (Option 1)**
We will add two patients to test different insurance types.
1. Type `1` and press Enter.
   - `Enter Patient ID    :` `P001`
   - `Enter Patient Name  :` `Alice Tan`
   - `Enter Insurance     :` `AIA Gold`
2. Type `1` again.
   - `Enter Patient ID    :` `P002`
   - `Enter Patient Name  :` `Bob Lee`
   - `Enter Insurance     :` `Prudential`

#### **Step B: Add Multiple Doctors (Option 2)**
We will add two doctors across different specializations.
1. Type `2` and press Enter.
   - `Enter Doctor ID         :` `D001`
   - `Enter Doctor Name       :` `Dr. Smith`
   - `Enter Specialisation    :` `Cardiology`
   - `Enter Clinic Code       :` `C-101`
2. Type `2` again.
   - `Enter Doctor ID         :` `D002`
   - `Enter Doctor Name       :` `Dr. Adams`
   - `Enter Specialisation    :` `Neurology`
   - `Enter Clinic Code       :` `N-202`

#### **Step C: Add Multiple Medical Services (Option 3)**
We will add two distinct medical services.
1. Type `3` and press Enter.
   - `Enter Service Code  (e.g. SVC001) :` `SVC001`
   - `Enter Service Name               :` `Blood Test`
   - `Enter Base Fee in RM (leave blank for RM 50.00 default):` `150.00`
2. Type `3` again.
   - `Enter Service Code  (e.g. SVC001) :` `SVC002`
   - `Enter Service Name               :` `MRI Scan`
   - `Enter Base Fee in RM (leave blank for RM 50.00 default):` `800.00`

#### **Step D: Schedule Appointments (Option 4)**
We will assign multiple services to different patients.
1. Type `4` and press Enter.
   - `Enter Patient ID     :` `P001`
   - `Enter Service Code   :` `SVC001`
2. Type `4` again.
   - `Enter Patient ID     :` `P002`
   - `Enter Service Code   :` `SVC002`
3. Type `4` again.
   - `Enter Patient ID     :` `P001`
   - `Enter Service Code   :` `SVC002` (Alice takes two services)

#### **Step E: Update Appointment Status & Billing (Option 5)**
We will test standard, emergency, and cancelled billing modifiers.
1. Type `5` and press Enter.
   - `Enter Patient ID    :` `P001`
   - `Enter Service Code  :` `SVC001`
   - `New Status          :` `Completed`
   - `Billing Modifier    :` `Insured`
2. Type `5` again.
   - `Enter Patient ID    :` `P002`
   - `Enter Service Code  :` `SVC002`
   - `New Status          :` `Emergency`
   - `Billing Modifier    :` `Emergency` (Tests the 1.5x fee multiplier)
3. Type `5` again.
   - `Enter Patient ID    :` `P001`
   - `Enter Service Code  :` `SVC002`
   - `New Status          :` `Cancelled`
   - `Billing Modifier    :` `Standard`

#### **Step F: View Output Information (Options 6, 7, 8, 9)**
These options prove the system dynamically processes data:
- Type `6` to **View All Users** (Will cleanly list Alice, Bob, Dr. Smith, and Dr. Adams using Polymorphism).
- Type `7` to **View Medical Services Catalog** (Will list Blood Test and MRI Scan).
- Type `8` to **View Patient Medical Expenses** for Alice.
  - `Enter Patient ID :` `P001` (Calculates bill for Completed Blood Test + Cancelled MRI).
- Type `8` again for Bob.
  - `Enter Patient ID :` `P002` (Calculates bill for the Emergency MRI with a 1.5x multiplier).
- Type `9` to **View System Statistics** (Proves the static counters accurately read 2 Patients, 2 Doctors, 4 Users).

#### **Step G: Verify Persistence (Options S and 0)**
1. Type `S` to test manual data serialization (Proves `patients.txt`, `doctors.txt`, and `appointments.txt` populate).
2. Type `0` and press Enter to auto-save and exit gracefully.

*Tip: After exiting, check the `data/` folder and read the `.txt` files to confirm the data is there. When you run `.\hospital_system.exe` again, Options 6, 7, 8, and 9 will immediately load and display this data!*
