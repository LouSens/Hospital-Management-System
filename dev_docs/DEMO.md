# Hospital Management System - Terminal User Flow

You can follow these steps to manually input the data and trigger all the core functionalities of the system. 

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
  6. View All Users (Runtime Polymorphism)
  7. View Medical Services Catalog
  8. View Patient Medical Expenses
  9. View System Statistics (Static Counts)
  S. Save All Data to Files
  0. Exit System
-------------------------------------------------------
  Enter choice: 
```

### 2. Manual Flow for Screenshots

Take your screenshots during and after each of these steps:

#### **Step A: Add a New Patient (Option 1)**
1. Type `1` and press Enter.
2. The system will prompt you for the patient details:
   - `Enter Patient ID    :` (type `P001`)
   - `Enter Patient Name  :` (type `John Doe`)
   - `Enter Insurance     :` (type `AIA Gold`)

#### **Step B: Add a New Doctor (Option 2)**
1. Type `2` and press Enter.
2. The system will prompt you for the doctor details:
   - `Enter Doctor ID         :` (type `D001`)
   - `Enter Doctor Name       :` (type `Dr. Smith`)
   - `Enter Specialisation    :` (type `Cardiology`)
   - `Enter Clinic Code       :` (type `C-101`)

#### **Step C: Add a New Medical Service (Option 3)**
1. Type `3` and press Enter.
2. The system will prompt you for the service details:
   - `Enter Service Code  (e.g. SVC001) :` (type `SVC001`)
   - `Enter Service Name               :` (type `Blood Test`)
   - `Enter Base Fee in RM (leave blank for RM 50.00 default):` (type `150.00`)

#### **Step D: Schedule an Appointment (Option 4)**
1. Type `4` and press Enter.
2. The system will prompt you to link a patient to a service:
   - `Enter Patient ID     :` (type `P001`)
   - `Enter Service Code   :` (type `SVC001`)

#### **Step E: Update Appointment Status & Billing (Option 5)**
1. Type `5` and press Enter.
2. The system will prompt you to update the appointment details:
   - `Enter Patient ID    :` (type `P001`)
   - `Enter Service Code  :` (type `SVC001`)
   - `New Status          :` (type `Completed`)
   - `Billing Modifier    :` (type `Insured`)

#### **Step F: View Information (Options 6, 7, 8, 9)**
You can trigger these options sequentially to show data being retrieved:
- Type `6` to **View All Users** (Shows the patient and doctor you added).
- Type `7` to **View Medical Services Catalog** (Shows the `SVC001` service you added).
- Type `8` to **View Patient Medical Expenses**. 
  - `Enter Patient ID :` (type `P001`). This will calculate and display their bill based on the "Completed" appointment.
- Type `9` to **View System Statistics** (Shows total static counts of classes).

#### **Step G: Save and Exit (Option 0)**
1. Type `0` and press Enter to automatically save all data and exit the system. 
2. The terminal will display the memory cleanup and goodbye messages.
