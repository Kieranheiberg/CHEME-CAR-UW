Arduino Code and testing scripts for UW ChemE Car team 2025-26. CHEME CAR SCRIPT.ino was used during the competition. Script reads analog output of TEMT6000 attached to iodine clock reaction vessel.
Photosensor ouputs analog voltage proportional to amount of light incident on the sensor. Clear solution = high voltage, dark opaque solution = low voltage. Cutoff voltage to determine if
reaction had occurred set as Voltage < 0.1 V. Photosensor and a LED light source were placed on opposite ends of reaction vessel to get better resolution. When cutoff threshold breached Arduino would turn off
5V relay and thus cut power between Li-ion battery packs and motor. 

Schematic of electronics circuit board is below:
<img width="1373" height="763" alt="ChemE Car E Schematic" src="https://github.com/user-attachments/assets/819ef2da-d77f-4d21-a528-2b4e6a23e466" />


Components connected to Arduino:
- TEMT6000 photosensor ouputted analog signal voltage
- 5V relay allowed arduino to control power flow between batteries and motor
- 2x SG90 Servos hydrallically injected reactants into reaction vessel at the start of the competition trial
- Capacitor helped balance high current draw when starting motor
- Emergency toggle switch acted as safety cutoff in case car failed or spilled chemicals
- Button started script; actuated servo 1 and 2 then turned on power flow from battery pack to motor via 5V relay. Activated by digital pin on Arduino board
- Computer fan was retroffitted with neodynium magnets to act as DIY stirring mechanism for reaction beaker in conjugtion with ceramic pill stir bar
