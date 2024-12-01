# Student Management System

A simple **Student Management System** in **C** that allows teachers and students to manage and view student records.

## Features

### Teacher:
- Add, edit, or delete student records.
- View all student records.

### Student:
- Search and view personal records by name and ID.

## Input Validation
Ensures valid data entry for attendance (0-100) and marks (0-100).

## File Handling
Student data is stored in `studs.txt`, which can be updated or deleted as needed.

## Usage
1. Compile:
   ```bash
   gcc student_management.c -o student_management
   ```
2. Run:
   ```bash
   ./student_management
   ```
3. Choose "Teacher" or "Student" to perform actions.

---
