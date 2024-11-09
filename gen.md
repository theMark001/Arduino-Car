# What i need to know to calculate needable power source to run scheme.

1. Current
  - Add Up the Total Current: Sum the current required by all components running at the same voltage. For instance, if you have four motors at 5V each drawing 120mA, the total current needed at 5V would be 480mA.
  - Add a Safety Margin: To ensure stable operation, add a buffer of about 10-20% to your current total. This accounts for startup spikes and any variations in load.

2. Voltage
  - Identify Voltage Requirements for Each Component: Check the operating voltage for every component in your circuit. For instance, motors might require 5V to 6V, an Arduino might need 5V, and some sensors or modules may need 3.3V.
  - Group Components by Voltage Levels: This allows you to determine if you’ll need multiple voltage levels or regulators in your setup. For example, if you have components that need 5V and others that need 3.3V, you’ll either need a dual-output power supply or a regulator for one of the voltages.

# Example 

- For a circuit with:
	•	Four motors requiring 5V and 120mA each.
	•	Arduino Nano requiring 5V and 50mA.
	•	Bluetooth module HC-05 at 5V and 40mA.

1. Voltage Requirements:
	•	All components need 5V, so a single 5V source is suitable.

2. Current Requirements:
	•	Motors:  4 \times 120 \text{mA} = 480 \text{mA} 
	•	Arduino: 50mA
	•	Bluetooth Module: 40mA
	•	Total Current: 480mA + 50mA + 40mA = 570mA
	•	With a 20% buffer:  570 \times 1.2 = 684 \text{mA} 

3. Power Requirement:
	•	 P = V \times I = 5V \times 684 \text{mA} = 3.42 \text{W} 

Power Source Choice:
	•	A 5V power source that can supply at least 700mA (rounded up) and 3.5W of power would be ideal. For a battery, consider one with at least 700mA continuous current capacity and sufficient mAh rating for desired run time.




# L298N
  - 5V pin from arduino to run logic of L298N

# Four TT motors:
  - Total Voltage Needed: 5V to 6V
  - Total Current Needed:  4 \times 120\text{mA} = 480\text{mA} , ideally with a buffer, so about 1A.

# HC-05
  - 5V pin from Arduino

# Arduino Nano
  - 1.8 V ~ 5.5V



--- 
# Mayble i will need to reorganize scheme like this 

5V Power Source:
5V output → L298N 12V pin (to power the motors at 5V) and GND.
5V output → Arduino Nano 5V pin and GND.
L298N Motor Driver:
Motors connected to the motor output pins as in your original setup.
Arduino Nano:
5V from power source → Nano 5V pin (also powering the Bluetooth module through the Nano).