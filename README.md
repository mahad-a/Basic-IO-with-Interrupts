# Basic I/O with Interrupts

## Overview

This project demonstrates basic Input/Output operations using interrupts on the MSP432P401R microcontroller. The main focus is on configuring switches and LEDs, handling interrupts, and implementing Interrupt Service Routines (ISRs). The project involves configuring switch interrupts, performing bitwise manipulations for LED control, and ensuring proper operation with debouncing. Project was built using Keil IDE.

## Development Setup

### Keil IDE Setup

1. **Download and Install Keil IDE:**
   - Visit the [Keil website](https://www.keil.com/download/) and download the latest version of the Keil MDK (Microcontroller Development Kit).
   - Follow the installation instructions to install the IDE on your system.

2. **Create a New Project:**
   - Open Keil IDE and select **Project** > **New Project** from the menu.
   - Choose a directory and name your project, then select **Save**.

3. **Select Microcontroller:**
   - In the **Select Device for Target** dialog, choose **Texas Instruments** from the list of manufacturers.
   - Select **MSP432P401R** as the microcontroller and click **OK**.

4. **Configure Project:**
   - Go to **Project** > **Options for Target** and configure the necessary settings, including clock configuration and memory settings.
   - Add the `msp.h` file to your project for peripheral device register definitions.

5. **Add Source Files:**
   - Right-click on **Source Group 1** in the **Project** window and select **Add New Item** to include your source files.

6. **Build and Debug:**
   - Click **Build** > **Build Target** to compile the project.
   - Use **Debug** > **Start/Stop Debug Session** to test and debug your code on the MSP432P401R microcontroller.

## Project Structure

The project involves the following key components:

1. **Switch and LED Configuration**
   - Configures two switches for input and four LEDs for output.
   - Switches and LEDs are connected to specific ports with appropriate settings.

2. **Interrupt Configuration**
   - Configures interrupts for the switches to handle input events.
   - Implements ISRs to manage LED behavior based on switch inputs.

3. **Bitwise Operations**
   - Uses bitwise operations for toggling and setting LED states.
   - Ensures correct manipulation of bits without affecting unintended bits.

4. **Debouncing**
   - Implements switch debouncing to avoid multiple triggers from a single press.

## System Behavior

### Initialization

- **Watchdog Timer:** Disabled to prevent unintended resets during development.
- **Switch Configuration:** 
  - **P1.1 and P1.4** are configured as inputs with internal pull-up resistors.
  - Switch interrupts are configured at the port level, NVIC, and CPU level.
- **LED Configuration:**
  - **P1.0, P2.0, P2.1, and P2.2** are configured as outputs.
  - All LEDs are initialized to be turned off.
- **Main Loop:** An infinite loop (`while (1)`) is used to keep the program running and handle interrupts.

### Operation Modes

1. **Switch Handling:**
   - **Button 1** toggles between selecting the RED LED and the RGB LED.
   - **Button 2** changes the state of the currently selected LED.

2. **LED Behavior:**
   - **RED LED:** Toggles between ON and OFF states, staying in each state for approximately 5 seconds.
   - **RGB LED:** Cycles through 8 states (off and 7 colors), staying in each state for approximately 5 seconds.

### Interrupt Service Routines (ISRs)

1. **Button 1 ISR:**
   - Changes the active LED between RED and RGB.

2. **Button 2 ISR:**
   - For the RED LED, toggles between ON and OFF states.
   - For the RGB LED, cycles through color combinations.

### Implementation Details

1. **Include File:**
   - Ensure to include `msp.h` for peripheral device register definitions.

2. **Configuration Steps:**
   - Disable the Watchdog timer.
   - Set up port configurations for switches and LEDs.
   - Configure interrupts at the port, NVIC, and CPU levels.
   - Implement ISRs for switch events, with and without debouncing.

3. **Bitwise Operations:**
   - Perform bitwise toggling for the RED LED.
   - Perform bitwise clearing and setting for the RGB LED.

4. **Debouncing:**
   - Implement switch debouncing to prevent multiple ISR triggers from a single button press.
