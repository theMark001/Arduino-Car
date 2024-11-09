# H-Bridge
  - An H-bridge is a circuit configuration that allows a motor to rotate in both directions (forward and reverse) by controlling the current flow through the motor.

# Double H-Bridge
  - Since the L298N has two H-bridges, it can independently control two motors. This means each motor can rotate forward, reverse, or stop, and their speeds can be adjusted separately.

# Characteristic

1. Logic Voltage: 5V
  -	This is the voltage needed for the logic circuit inside the L298N to operate.

2. Voltage for Motor(s): 5V-35V
  - This is the range of voltages that the module can supply to the motors.

3. Logic Current: up to 36mA
  - This is the amount of current drawn by the L298N’s internal logic circuitry from the 5V logic supply. The current is minimal and easily handled by most microcontrollers.

4. Current per Channel: 2A (MAX)
  - The module can supply up to 2 amps of current per motor channel. Since the L298N has two channels (A and B), it can drive two motors with up to 2A each. However, sustained currents at this maximum limit may require cooling to prevent overheating.

5. Max Power: 25W
  - This is the maximum power the module can handle across both channels, based on the voltage and current. Power is calculated as  \text{Power (W)} = \text{Voltage (V)} \times \text{Current (A)} . For example, at 12V, the maximum current draw per channel would be around 2A, resulting in 24W (12V × 2A = 24W).

# Battery to power it 

  - Stats to power all motors(based on volts and ampers)
  - 5V pin from arduino to run logic of L298N