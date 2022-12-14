# LAB_5
Lab 5 Embedded 

##### By: Ronan Harkins, Zachary Bravo, Ike-Anyanwu Chinedu

### Objective
The objective of this lab is to see how different analog sensors can be used with the MSP430FR2355's on board ADC components. For the first analog device that was used was the built in temperature sensor and the second sensor that was used was a photoresistor. These sensors had to be used by the ADC and display values that make sense to the reader.

## Part 1
One sensor was used to obtain the data. The on-board temperature sensor was used as the first ADC sensor that the team used. The sensor was able to get data and display the result in both the memory and in a plotted format. The plot can be seen below. The results are going back and forth between the 27 degrees Celsius and 26 degrees Celsius. This is normal because the temperature could be changing, and the sensor could have a small amount of error.

#### CCS plot
![image](https://user-images.githubusercontent.com/98828696/206329761-ed707284-bb22-4f7b-a9b6-4a8ae41d4b44.png)

#### Block Diagrams 
<img width="703" alt="image" src="https://user-images.githubusercontent.com/98828696/206329985-41c78b67-c0e2-4726-8dac-049e4d2daa42.png">

### UML
<img width="442" alt="image" src="https://user-images.githubusercontent.com/98828696/206330022-c8c3ef9b-9765-4072-81d9-ed179da677df.png">

## Part 2
This part of the lab the group had to use two sensors at the same time and obtain the data from them. The first sensor was reused from part one and the second sensor that was used was a photoresist. This sensor has the ability to detect light, the results could be read at the same time within the code provided. This allowed for the ADC to be used on two sensor and displayed in both numerical and on the CCS plot as shown below. The first plot for the temperature sensor can be seen above for part 1 and the new plot can be seen in the figure below. For the photoresist the first input is the light of the room, then a finger was placed over the sensor which changed the value to a higher number. The reason for this is because if it is darker the number will increase as seen in the plot. After that the light was added back to the environment and the photoresist returns to the level it was previously at.    

#### CCS plot
![image](https://user-images.githubusercontent.com/98828696/206329809-0f9cb12e-567d-4d2e-8f3a-1448f6025de1.png)

#### Block Diagrams 
<img width="875" alt="image" src="https://user-images.githubusercontent.com/98828696/206330070-dab05f2b-d612-4416-be54-4ac9910c0b39.png">

### UML
<img width="375" alt="image" src="https://user-images.githubusercontent.com/98828696/206330086-453df6ec-6d2f-48fe-a538-21c11bcf85da.png">


![image](https://user-images.githubusercontent.com/98828696/206331137-d0bcb0c2-1382-477f-84d6-bebb49766f67.png)

