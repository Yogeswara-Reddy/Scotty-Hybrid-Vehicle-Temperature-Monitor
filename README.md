# 🛵 Design and Transformation of IC Engine Motorcycle into Hybrid Vehicle
### Real-Time Temperature Monitoring System for Dashboard Display

> 🏆 **Funded & Approved by Karnataka State Council for Science and Technology (KSCST)**
> Student Project Programme — 47th Series | Project Ref: **47S_BE_3083** | Year: 2023-2024
> Sanctioned Amount: **₹ 5,500**

## 📰 Publication

This project was published in **IEEE Xplore**:

> **"Design and Transformation of IC Engine Motorcycle into Hybrid Vehicle"**
> IEEE Conference Publication

🔗 [Read on IEEE Xplore](https://ieeexplore.ieee.org/document/10960245)

---

## 🏫 Project Details

| Field | Details |
|---|---|
| **University** | Reva University, Bengaluru |
| **Department** | School of Electrical and Electronics Engineering |
| **Degree** | Bachelor of Technology (B.Tech) |
| **Academic Year** | 2023 - 2024 |
| **Guide** | Mr. Pavan B., Assistant Professor, School of EEE |
| **Students** | K Yogeswara Reddy (R21EM808), Mala C S (R20EM048), Hema Rekha R (R20EM038), Sumanth A (R21EM818) |
| **Approved by** | Dr. U. T. Vijay, Executive Secretary, KSCST |

---

## 📋 Project Abstract

This project involves the design and transformation of an IC engine motorcycle (Scotty) into a fully hybrid vehicle. The hybrid system integrates a BLDC hub motor directly fitted on the rear wheel with the existing IC engine, allowing the vehicle to run on either electric power or petrol independently.

As part of the Dashboard system, a real-time temperature monitoring system was developed using an STM32 microcontroller to continuously monitor motor and battery temperatures and display live readings on a Nextion display over RS485/Modbus RTU communication — ensuring safe operation of the hybrid drivetrain.

---

## 🛵 i-Hybrid Vehicle Specifications

### Motor
| Parameter | Value |
|---|---|
| Motor Type | BLDC Hub Motor (rear wheel mounted) |
| Nominal Power | 1.6 kW |
| Max Power | 2.4 kW |
| Maximum Torque | 110 N-m |
| Maximum Speed | 55 - 60 kmph |
| IP Protection | IP67 |

### Controller
| Parameter | Value |
|---|---|
| Controller Type | Field Oriented Control (FOC) |
| Maximum Phase Current | 150 Amps |
| IP Protection | IP66 |

### Battery
| Parameter | Value |
|---|---|
| Battery Type | Lithium-Ion |
| Chemistry | NMC (Nickel Manganese Cobalt) |
| Operating Voltage | 40 - 58 V |
| Capacity | 35 Ah / 1.81 kWh |
| Weight | 13.5 kg |

### Charger
| Parameter | Value |
|---|---|
| Charger Type | DC Charger |
| Rating | 58.8V / 10 Amps |
| Input Voltage | 170VAC - 300VAC |
| Charging Time | Up to 4.5 Hours |
| Cut-off Voltage | 58.8V |

### Range
| Parameter | Value |
|---|---|
| On Road Range | Up to 60 km |

---

## 🌡️ Temperature Monitoring System

### ✨ Features
- Real-time motor and battery temperature monitoring (updates every 1 second)
- RS485 communication with Modbus RTU protocol (noise-resistant, automotive grade)
- Motor warning triggered above **140°C**
- Battery warning triggered above **45°C**
- CRC error detection on all data frames
- Zero data mixing — each sensor on dedicated GPIO pin and Modbus address
- Sensor fault detection — displays Sensor Error if disconnected


---

## 🔧 Hardware Components

| Component | Details |
|---|---|
| Microcontroller | STM32F103C8T6 (Blue Pill) — ARM Cortex-M3, 72MHz |
| Temperature Sensors | DS18B20 x2 (1-Wire protocol) |
| RS485 Transceiver | MAX485 module |
| Display | Nextion UART display |
| Resistors | 4.7kΩ pullup x2 |

---

## 📌 Pin Configuration

| STM32 Pin | Function |
|---|---|
| PA0 | Motor DS18B20 sensor data |
| PA1 | Battery DS18B20 sensor data |
| PA2 | UART1 TX → MAX485 DI |
| PA3 | UART1 RX → MAX485 RO |
| PA4 | RS485 Direction control |

---

## 📊 Firmware Specifications

| Metric | Value |
|---|---|
| Flash usage | 24,736 bytes (39% of 64KB) |
| RAM usage | 2,448 bytes (12% of 20KB) |
| CPU clock | 72 MHz |
| UART baud rate | 9600 bps |
| Temperature update rate | 1 second |
| Modbus motor address | 0x01 |
| Modbus battery address | 0x02 |

---

## 🛠️ Development Environment

- **IDE:** STM32CubeIDE v2.1.1
- **Language:** Embedded C (GNU C11)
- **Toolchain:** GNU Tools for STM32 (arm-none-eabi-gcc)
- **Target:** STM32F103C8T6

---

## 🏆 Recognition

This project was **selected and funded** by the **Karnataka State Council for Science and Technology (KSCST)** — an autonomous organisation under the Department of Science and Technology, Government of Karnataka.

- **Funding Body:** KSCST, Indian Institute of Science Campus, Bengaluru
- **Programme:** Student Project Programme — 47th Series
- **Project Ref No:** 47S_BE_3083
- **Sanctioned Amount:** ₹ 5,500
- **Approved by:** Dr. U. T. Vijay, Executive Secretary, KSCST

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

### 🖥️ Display Output

**Normal operation:**
