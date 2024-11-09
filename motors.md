# DC motor 
  - A direct current (DC) motor is a type of electric machine that converts electrical energy into mechanical energy. DC motors take electrical power through direct current, and convert this energy into mechanical rotation.

# TT motor
  - A TT motor is a type of DC motor that has a gearbox attached to it. The gearbox reduces the speed of the motor and increases its torque.

##   Gearbox
  - In a TT motor, the gearbox is attached directly to the motor shaft inside the yellow housing, typically at the end opposite the motor terminals. The gearbox contains a series of gears (often plastic or metal) that are arranged in stages to reduce the speed of the motor’s rotation while increasing its torque.

# Characteristics

1. Power Supply
  - The motor can be powered with different DC voltages—3V, 5V, or 6V. The performance of the motor varies based on the voltage supplied.

2. Current: The amount of current the motor draws at each specified voltage:
  -	At 3V, it draws 100 mA.
  -	At 5V, it draws 100 mA.
  - At 6V, it draws 120 mA.

3. Transfer
  - The gear ratio of the motor is 48:1. This means the motor output shaft rotates once for every 48 rotations of the motor’s internal shaft, allowing for more torque at a reduced speed.

4. Output Speed: The rotational speed of the motor’s output shaft depends on the input voltage:
  - At 3V, it rotates at 114 RPM.
  - At 5V, it rotates at 197 RPM.
  - At 6V, it rotates at 240 RPM.

5.  Torque: At 3V, the motor produces a torque of 800 g/cm
  -  meaning it can exert a force strong enough to lift 800 grams at a distance of 1 cm from the center of the shaft.

# Battery to power it 
  - Voltage (V): 5V to 6V.
    - 5V is a good middle ground, providing enough speed and torque without overstressing the motors.
    - If you use 6V, the motors will perform at their maximum rated speed and torque.
  - Current (A): At least 0.5A (500mA), ideally 1A (1000mA) to provide a safe margin.
    - Each motor draws approximately 100 mA at 5V or 120 mA at 6V.
    - For four motors, the minimum continuous current supply should be 500 mA, but having a 1A capacity allows for smoother performance and any brief surges in current.

- Each TT motor:
  - Voltage: 3-6V (optimal 5V)
  - Current: 100mA (up to 120mA at higher loads)

- For four motors:
  - Total Voltage Needed: 5V to 6V
  - Total Current Needed:  4 \times 120\text{mA} = 480\text{mA} , ideally with a buffer, so about 1A.