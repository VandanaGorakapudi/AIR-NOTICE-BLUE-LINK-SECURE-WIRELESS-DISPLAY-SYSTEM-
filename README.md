# AIR-NOTICE-BLUE-LINK-SECURE-WIRELESS-DISPLAY-SYSTEM-
📢 AIRNOTICE BLUELINK – SECURE WIRELESS DISPLAY SYSTEM

📌 Project Overview

AirNotice BlueLink – Secure Wireless Display System is a modern electronic notice board designed as an alternative to traditional notice boards.

The system allows an authorized user to send a notice from an Android smartphone through Bluetooth. The HC-05 Bluetooth module receives the message and sends it to the LPC2148 ARM7 microcontroller.

The microcontroller verifies the predefined security passkey, extracts the actual notice message, stores the message in AT25LC512 EEPROM, and displays it on four 8×8 dot-matrix LED displays with a scrolling effect.

This system can be useful in:

- 🏫 Schools and Colleges
- 🏢 Offices
- 🏭 Industries
- 🏥 Public information areas
- 📢 Announcement systems

---

🎯 Aim

To develop a secure wireless electronic notice board that receives messages through Bluetooth, verifies an authorized passkey, stores the message in EEPROM, and displays the message on a scrolling dot-matrix LED display.

---

⭐ Key Features

- 📱 Android smartphone-based message transmission
- 📶 Wireless communication using Bluetooth
- 🔐 Passkey-based message authentication
- 🧠 LPC2148 ARM7 microcontroller
- 💾 AT25LC512 EEPROM for message storage
- 🔢 Four 8×8 dot-matrix LED displays
- 🔄 Scrolling text display
- ⚡ UART-based communication
- 🔌 74HC164 shift registers for column control
- 🔲 74HC573 latch for row control
- ⏳ Displays "Waiting for message" when no message is stored

---

🏗️ System Block Diagram

```mermaid
flowchart LR
    A[📱 Android Smartphone] -->|Bluetooth Message| B[📶 HC-05 Bluetooth]
    B -->|UART| C[🧠 LPC2148 ARM7]
    C -->|Verify Passkey| D{🔐 Authorized?}
    D -->|Yes| E[💾 AT25LC512 EEPROM]
    E --> C
    C --> F[74HC164 Shift Registers]
    C --> G[74HC573 Latch]
    F --> H[🔢 4 x 8×8 Dot Matrix]
    G --> H
    H --> I[📢 Scrolling Notice Display]
    D -->|No| J[❌ Ignore Message]
```

🔄 Working Principle

```mermaid
flowchart TD
    A[Start] --> B[Initialize Peripherals]
    B --> C[Read Message from EEPROM]
    C --> D[Display Stored Message]
    D --> E{New Bluetooth Message?}

    E -->|No| D
    E -->|Yes| F[Receive Message through UART]
    F --> G[Check Security Passkey]
    G --> H{Passkey Valid?}

    H -->|No| I[Reject Message]
    I --> E

    H -->|Yes| J[Extract Notice Text]
    J --> K[Store New Message in EEPROM]
    K --> L[Stop Previous Scrolling]
    L --> M[Display New Message]
    M --> E
```
---

🔐 Security Mechanism

The system does not directly display every message received through Bluetooth.

The sender must provide a predefined passkey/security code along with the message.

Example

Input received from Bluetooth:

$$789Vector India$$

The LPC2148 verifies the passkey and extracts:

Vector India

Only the extracted authorized message is displayed on the dot-matrix LED.

```mermaid
flowchart LR
    A[Bluetooth Input] -->B["$$789Vector India$$"]
    B --> C[LPC2148]
    C --> D{Passkey Valid?}
    D -->|YES| E["Extract: Vector India"]
    E --> F[EEPROM]
    F --> G[Dot Matrix Display]
    D -->|NO| H[Reject Message]
```
---

🧰 Hardware Requirements

| Component | Purpose |
|---|---|
| LPC2148 | Main ARM7 microcontroller |
| 4 × 8×8 Dot Matrix Displays | Displays scrolling notice |
| 74HC164 | Serial-in parallel-out shift register for column control |
| 74HC573 | Octal D-type latch for row control |
| AT25LC512 EEPROM | Stores notice messages |
| HC-05 Bluetooth Module | Wireless communication |
| DB-9 Cable / USB-UART Converter | UART/PC interface |

💻 Software Requirements

- Embedded C
- Keil C Compiler
- Flash Magic
- Android Bluetooth Terminal application

The original project documentation specifies Keil C Compiler, Embedded C and Flash Magic.

---

🔌 Hardware Connections

### LPC2148 UART / Bluetooth Connection

| LPC2148 Pin | Connected Module |
|---|---|
| P0.0 / TxD0 | HC-05 Rx |
| P0.1 / RxD0 | HC-05 Tx |
---

### 74HC573 – Dot Matrix Row Control

The 74HC573 latch is used to control the dot-matrix row data.

| 74HC573 Data Pin | LPC2148 |
|---|---|
| D0 | P0.16 |
| D1 | P0.17 |
| D2 | P0.18 |
| D3 | P0.19 |
| D4 | P0.20 |
| D5 | P0.21 |
| D6 | P0.22 |
| D7 | P0.23 |

The 74HC573 outputs are connected to the row lines of the dot-matrix displays.
---
### AT25LC512 EEPROM – SPI Connection

| AT25LC512 Signal | LPC2148 |
|---|---|
| SCK | P0.4 |
| MISO | P0.5 |
| MOSI | P0.6 |
| CS | P0.7 |
---
### 74HC164 – Dot Matrix Column Control

| Display | SIN Pin | CP Pin |
|---|---|---|
| Display 1 | P0.8 | P0.9 |
| Display 2 | P0.10 | P0.11 |
| Display 3 | P0.12 | P0.13 |
| Display 4 | P0.14 | P0.15 |


### Actual Hardware Connections
![Actual Hardware Connections](hardware_setup.jpeg)

---

🧩 System Architecture

```mermaid
flowchart TB
    subgraph INPUT["📱 INPUT"]
        A[Android Phone]
        B[HC-05 Bluetooth]
    end

    subgraph CONTROL["🧠 CONTROL"]
        C[LPC2148 ARM7]
        D[UART]
        E[Security Verification]
    end

    subgraph STORAGE["💾 STORAGE"]
        F[AT25LC512 EEPROM]
    end

    subgraph DISPLAY["📺 DISPLAY"]
        G[74HC573 Latch]
        H[74HC164 Shift Registers]
        I[4 × 8×8 Dot Matrix]
    end

    A --> B
    B --> D
    D --> C
    C --> E
    E --> F
    F --> C
    C --> G
    C --> H
    G --> I
    H --> I
```
---


📲 Message Communication

The communication process is:

```mermaid
flowchart TD
    A[📱 Android Phone] --> B[📶 HC-05 Bluetooth]
    B --> C[UART]
    C --> D[🧠 LPC2148]
    D --> E[🔐 Security Verification]
    E --> F[💾 AT25LC512 EEPROM]
    F --> D
    D --> G[74HC573 + 74HC164]
    G --> H[4 × 8×8 Dot Matrix]
    H --> I[📢 Scrolling Notice]
```
---

💾 EEPROM Operation

The AT25LC512 EEPROM is used to store the latest notice message.

The project implementation includes:

1. Writing bytes to EEPROM
2. Reading bytes from EEPROM
3. Storing a user-defined string
4. Reading the stored string
5. Displaying the stored string on the dot-matrix LED

The project documentation specifies byte/page write and read operations for EEPROM.
### EEPROM Write and Read Operations

The AT25LC512 EEPROM is accessed through SPI communication.

The project implementation supports:

- Byte write using `ByteWrite_25LC512()`
- Byte read using `ByteRead_25LC512()`
- Page write using `PageWrite_25LC512()`
- Write Enable (WREN) before write operations
- Write Disable (WRDI) after write operations

---

📡 Bluetooth Communication

The HC-05 Bluetooth module is used for wireless communication between the Android phone and LPC2148.

Communication Flow

```mermaid
sequenceDiagram
    participant User as 📱 Android User
    participant BT as 📶 HC-05
    participant MCU as 🧠 LPC2148
    participant EEPROM as 💾 EEPROM
    participant LED as 📺 Dot Matrix

    User->>BT: Send secured message
    BT->>MCU: UART data
    MCU->>MCU: Verify passkey

    alt Valid passkey
        MCU->>EEPROM: Store new message
        EEPROM-->>MCU: Message stored
        MCU->>LED: Display & scroll message
    else Invalid passkey
        MCU-->>BT: Reject message
    end
```

📺 Display Operation

The system uses four 8×8 dot-matrix displays to create a larger scrolling display area.

### Power ON
![Power ON](power_on.jpeg)

The display is controlled using:

- 74HC164 → Column control
- 74HC573 → Row control
- LPC2148 → Main display control

### Initial Display Output – HELP
![HELP Output](help_output.jpeg)

Example:

```text
+--------+--------+--------+--------+
|  8×8   |  8×8   |  8×8   |  8×8   |
| Matrix | Matrix | Matrix | Matrix |
+--------+--------+--------+--------+

        ← SCROLLING MESSAGE →

```

### Scrolling Message Output
![Scrolling Output](scrolling_output.jpeg)

---

🔁 Message Update Logic

The LPC2148 continuously checks for a new Bluetooth message.

When a new authorized message is received:

```mermaid
flowchart TD
    A[📩 New Message Received] --> B[🔐 Verify Passkey]
    B --> C[✂️ Extract Message]
    C --> D[💾 Store in EEPROM]
    D --> E[⏹️ Stop Previous Message]
    E --> F[📺 Display New Message]
    F --> G[🔄 Continue Scrolling]
```
---
### Step 8 – Complete Integration

The final system integrates all major modules:

```mermaid
flowchart LR
    A[📱 Bluetooth] --> B[⚡ UART]
    B --> C[🧠 LPC2148]
    C --> D[🔐 Security]
    D --> E[💾 EEPROM]
    E --> C
    C --> F[📺 Dot Matrix]
```
---

⏳ Default Display

If there is no message stored in EEPROM, the system displays:

WAITING FOR MESSAGE

A message-status memory location is used to identify whether a valid message is available.

---

🧪 Implementation Steps

The project was designed to be implemented in stages:

Step 1 – Single Character

Display one character on a single dot-matrix LED.

Step 2 – Four Character Display

Display a four-character string.

Example:

HELP

Step 3 – Scrolling Text

Display a string containing more than 10 characters.

Example:

PROJECT SUCCESSFULLY COMPLETED

Step 4 – EEPROM

Write and read data from EEPROM.

Step 5 – EEPROM String

Store and retrieve a user-defined string.

Step 6 – UART

Test:

- Character transmission
- String transmission
- String reception
- UART interrupt

Step 7 – Bluetooth

Pair the Android phone with HC-05 and send data wirelessly.


The staged implementation sequence is based directly on the supplied project documentation.

---

🛠️ Project Workflow

```mermaid
flowchart TD
    A[Android Application] --> B[HC-05 Bluetooth]
    B --> C[UART Communication]
    C --> D[LPC2148]
    D --> E[Security Passkey]
    E --> F{Valid?}
    F -->|No| G[Message Rejected]
    F -->|Yes| H[Extract Notice]
    H --> I[AT25LC512 EEPROM]
    I --> J[Read Latest Message]
    J --> K[Scrolling Algorithm]
    K --> L[74HC164]
    K --> M[74HC573]
    L --> N[4 × 8×8 Dot Matrix]
    M --> N
    N --> O[Display Notice]
```
---
### Project Demo Video

[▶️ Watch Project Demo](project_demo.mp4)

---

📁 Suggested GitHub Folder Structure

```text
AIRNOTICE-BLUELINK-SECURE-WIRELESS-DISPLAY-SYSTEM/
│
├── README.md
│
├── Source_Code/
│   ├── main.c
│   ├── mainspi.c
│   ├── 74LS164.c
│   ├── 74LS164.h
│   ├── defines.h
│   ├── delay.c
│   ├── delay.h
│   ├── delays.c
│   ├── delays.h
│   ├── dml.c
│   ├── dml.h
│   ├── lcd.c
│   ├── lcd.h
│   ├── spi.c
│   ├── spi.h
│   ├── spi_defines.h
│   ├── spi_eeprom.c
│   ├── spi_eeprom.h
│   ├── spi_eeprom_defines.h
│   ├── UART_INT.c
│   ├── types.h
│   └── startup.s
│
└── project_demo.mp4
```
---

📌 Applications

- 🏫 College Notice Boards
- 🏢 Office Announcements
- 🏭 Industrial Information Display
- 🏥 Hospital Announcements
- 🚉 Public Information Systems
- 📢 Event Announcements
- 🏫 School Communication Systems

---

🚀 Future Enhancements

Possible future improvements include:

- Wi-Fi-based communication
- IoT cloud integration
- Web-based notice management
- Mobile application with login authentication
- Multiple display-board support
- Remote monitoring
- Admin dashboard
- Real-time message scheduling

---

👩‍💻 Technologies Used

```text
Microcontroller : LPC2148 ARM7
Programming     : Embedded C
Compiler        : Keil C
Communication   : Bluetooth / UART
Bluetooth       : HC-05
Memory          : AT25LC512 EEPROM
Display         : 8×8 Dot Matrix LED
Shift Register  : 74HC164
Latch           : 74HC573
Programming Tool: Flash Magic
```
---

🎓 Project Type

Academic / Embedded Systems Project

Domain

Embedded Systems | ARM7 | Bluetooth Communication | LED Display

---

📜 Conclusion

AirNotice BlueLink provides a secure and convenient method for displaying electronic notices wirelessly.

By combining LPC2148, HC-05 Bluetooth, UART, AT25LC512 EEPROM, 74HC164, 74HC573 and dot-matrix LED displays, the system can receive, authenticate, store and display messages without requiring a traditional manually updated notice board.

The security passkey ensures that only authorized messages are displayed on the electronic notice board.

---

⭐ Project Highlights

```text
📱 Wireless Message
       ↓
📶 Bluetooth
       ↓
🧠 LPC2148
       ↓
🔐 Security Verification
       ↓
💾 EEPROM Storage
       ↓
🔄 Scrolling
       ↓
📺 Dot Matrix Display
```

«Secure • Wireless • Flexible • Real-Time Electronic Notice Display»
