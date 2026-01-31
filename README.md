# Bluetooth-Controlled Robotic Arm 🤖

A Bluetooth-enabled robotic arm developed using Arduino and embedded control logic.  
The project demonstrates smooth multi-axis motion, predefined gesture execution, and automated pick-and-place operations through wireless command input.

## 🔧 Project Highlights
- Wireless control using HC-06 Bluetooth module
- Coordinated control of 6 servo motors
- Smooth servo movement using incremental positioning
- Predefined gestures (Hello, Yes, No, Dance)
- Automated pick-and-place sequence
- Safe initialization with home positioning

## 🧠 Technologies & Components
- Arduino Uno
- Servo Motors (6 DOF)
- HC-06 Bluetooth Module
- External power supply for motors
- Embedded C (Arduino IDE)
- Serial & SoftwareSerial communication

## 📂 Repository Structure
code/ → Arduino source code (.ino file)
media/ → Project images and demo video
report/ → Project documentation (PDF)

## ▶️ How It Works
The robotic arm receives single-character commands via Bluetooth or serial communication.  
Each command triggers a predefined motion sequence or gesture, ensuring smooth and controlled movement across all joints.

### Command Reference
| Command | Action |
|-------|--------|
| 1 | Hello gesture |
| 2 | Dance gesture |
| 3 | Pick and place |
| 4 | Yes gesture |
| 5 | No gesture |
| 6 | Gripper test |

## ⚙️ Setup & Usage
1. Upload the Arduino `.ino` file using Arduino IDE  
2. Connect servo motors to external power (recommended)  
3. Pair HC-06 Bluetooth module with a serial terminal app  
4. Send commands (1–6) to control the arm  

## 📸 Demo
- 🎥 Demo video available in the `media` folder  
- 📷 Project images show the physical setup and arm configuration  

## 🚀 Future Improvements
- Mobile application-based control
- Sensor feedback for precision
- Inverse kinematics implementation
- Vision-based object detection
- AI-assisted gesture control

---

**Developed as an academic project for hands-on learning in embedded systems and robotics.**
