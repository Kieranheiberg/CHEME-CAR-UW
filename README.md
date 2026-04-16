# UW CHEM E CAR
University of Washington organization that designs and builds a car that is both chemically powered and stopped. 2025-26' car utilized Li-ion coin cells manufactured at UW CEI Testbeds for propulsion and an iodine clok reaction as a stopping mechanism. This repo contains all Arduino Code and testing scripts for UW ChemE Car team 2025-26. 

## Competition Code
ChemE_Car_Script.ino was used during the regional competition where UW placed 2nd. This Arduino script uses TEMT6000 photosensor attached to iodine clock reaction vessel to monitor stopping mechanism process. Photosensor ouputs a analog voltage that is proportional to amount of light incident on the sensor. Clear solution = high voltage, dark opaque solution = low voltage. Cutoff voltage to determine if reaction had occurred qualitatively set at Voltage < 0.1 V. Photosensor and a LED light source were placed on opposite ends of reaction vessel to get better data resolution. When cutoff threshold breached Arduino Pro Micro would turn off 5V relay and thus cut power between Li-ion battery packs and motor, stopping the car.

## Electronics Schematic
<img width="1285" height="959" alt="SmallUpdatedElectronicsDiagram" src="https://github.com/user-attachments/assets/fd2a3593-302c-4350-9b75-15ce87442c0c" />


Components connected to Arduino:
- TEMT6000 photosensor ouputted analog signal voltage
- 5V relay allowed arduino to control power flow between batteries and motor
- 2x SG90 Servos hydrallically injected reactants into reaction vessel at the start of the competition trial
- Capacitor helped balance high current draw when starting motor
- Emergency toggle switch acted as safety cutoff in case car failed or spilled chemicals
- Button started script; actuated servo 1 and 2 then turned on power flow from battery pack to motor via 5V relay. Activated by digital pin on Arduino board
- Computer fan was retroffitted with neodynium magnets to act as DIY stirring mechanism for reaction beaker in conjunction with ceramic pill stir bar

## Car Pictures
<img width="975" height="731" alt="image" src="https://github.com/user-attachments/assets/ba549cec-5ed2-44db-8df2-cff0c93c7b05" />
<img width="975" height="731" alt="image" src="https://github.com/user-attachments/assets/abecc2df-3991-45a3-8e52-955f7a03cdc2" />
<img width="975" height="1300" alt="image" src="https://github.com/user-attachments/assets/9439dadd-3cf5-43db-8701-18987d174d7a" />
<img width="975" height="1300" alt="image" src="https://github.com/user-attachments/assets/1b86a1c0-544c-46ce-9a5e-4538d5edf690" />
<img width="975" height="1300" alt="image" src="https://github.com/user-attachments/assets/9557a0b3-c5eb-44bd-b038-8b9f32dfae75" />




