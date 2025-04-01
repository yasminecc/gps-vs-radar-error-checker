# GPS vs RADAR Error Checker

This C++ application compares GPS sensor data with RADAR tracking data to detect inconsistencies. If the distance between corresponding coordinates in both data sets exceeds a user-defined tolerance, the timestamp and error are logged in `ERR.LOG`.

---

## 📌 Features

- Menu-driven CLI to:
  - Calculate error between GPS and RADAR inputs.
  - Display logged discrepancies.
  - Exit the program.
- Distance computation using 3D Euclidean distance.
- File validation and user input handling.
- Outputs detailed error log with timestamped entries.

---

## 💡 Use Case

Useful for air traffic control simulation, sensor fusion validation, or autonomous systems where sensor reliability must be verified.

---

## 🛠️ How to Compile

Use any C++ compiler. Example using `g++`:

```bash
g++ -o gps_error_checker main.cpp
./gps_error_checker
