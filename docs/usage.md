# User Guide for Arduino-ALEX Microcontroller

The microcontroller features five tactile buttons labeled **A**, **U1**, **U2**, **D1**, and **D2**, along with an LCD monitor that changes color based on the system's status:

- **White**: State 0 (non-functioning/continuous laser mode)
- **Green**: State 1 (active mode, waiting for camera trigger)
- **Red**: State 2 (alternating laser procedure ongoing)

## Microcontroller States

- **State 0 (White Background)**:  
  The controller does not generate TTL output for the lasers in this state. This state allows continuous laser operation.

- **State 1 (Green Background)**:  
  The controller is in active mode, waiting for the camera's **FIRE** output to trigger one laser or the other. Use this state to run **ALEX**.

- **State 2 (Red Background)**:  
  The controller switches automatically to this state when the alternating laser procedure is ongoing.

## Button Functionalities

- **Button A**:  
  Toggles between **State 0** (white) and **State 1** (green).

- **Button U1**:  
  Increases the _on-time_ by 100 µs.

- **Button D1**:  
  Decreases the _on-time_ by 100 µs.

- **Button U2**:  
  Increases the _on-time_ by 1000 µs.

- **Button D2**:  
  Decreases the _on-time_ by 1000 µs.

## Adjusting _on-time_

Let's take Andor iXon DU 860 as an example. For **EMCCD cameras** operating in frame transfer mode, the _on-time_ should correspond to the exposure time. For instance, if the frame transfer rate is 0.45 µs/line and the camera has 128 lines, the total frame time would be around 2.06 ms, so the _on-time_ should be set to **2 ms**.

For **sCMOS cameras** with a rolling shutter, determining the _on-time_ is more complex. The _on-time_ should match the period during which all pixels are exposed simultaneously (pseudo-global-shutter).

**Note**: Due to the 16 MHz clock speed limitation of the Arduino Nano controller, subtract **100 µs** from the desired _on-time_ to ensure that neither laser is activated simultaneously.

## ALEX mode (step-by-step)

Follow these steps to run the alternating laser excitation mode:

1. Set the microcontroller to **State 0** (white background) to adjust the correct _on-time_. The unit is in µs.
2. Ensure both lasers are set to operate in **digital modulation mode**, waiting for signals from the microcontroller.
3. Switch the microcontroller to **State 1** (green background). In this mode, the microcontroller waits for the camera's signal.
4. Start the camera's acquisition process. The microcontroller should switch to **State 2** (red background), indicating the laser is being alternately turned on and off.
5. Once the required frames are collected, stop the camera. The microcontroller will revert to **State 1** (green background) and be ready for the next acquisition.

## Continuous mode (step-by-step)

Follow these steps to run continuous laser mode:

1. Ensure both lasers are set to operate in **continuous mode**, no longer relying on microcontroller signals.
2. Set the microcontroller to **State 0** (white background).
3. If you plan to run experiments in continuous mode only, disconnect the microcontroller and detach the coaxial cable connecting the camera to the microcontroller.

By following these steps, you can run both the alternating and continuous laser modes on the Arduino-ALEX microcontroller.
