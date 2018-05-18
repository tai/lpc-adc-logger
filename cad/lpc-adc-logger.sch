EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:nxp_armmcu
LIBS:mbed
LIBS:switches
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L mbed_LPC1114FN28 U?
U 1 1 5AFE1CD9
P 5350 3900
F 0 "U?" H 5350 4700 60  0000 C CNN
F 1 "mbed_LPC1114FN28" H 5350 3150 60  0000 C CNN
F 2 "" H 5850 3250 60  0000 C CNN
F 3 "" H 5850 3250 60  0000 C CNN
	1    5350 3900
	1    0    0    -1  
$EndComp
$Comp
L SD_Card J?
U 1 1 5AFE1DAC
P 7400 1850
F 0 "J?" H 6750 2400 50  0000 C CNN
F 1 "SD_Card" H 8000 1300 50  0000 C CNN
F 2 "10067847-001" H 7600 2200 50  0001 C CNN
F 3 "" H 7400 1850 50  0001 C CNN
	1    7400 1850
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW?
U 1 1 5AFE1E24
P 1700 5550
F 0 "SW?" H 1750 5650 50  0000 L CNN
F 1 "SW_Push" H 1700 5490 50  0000 C CNN
F 2 "" H 1700 5750 50  0001 C CNN
F 3 "" H 1700 5750 50  0001 C CNN
	1    1700 5550
	1    0    0    -1  
$EndComp
$Comp
L LED D?
U 1 1 5AFE1E57
P 1700 6050
F 0 "D?" H 1700 6150 50  0000 C CNN
F 1 "LED" H 1700 5950 50  0000 C CNN
F 2 "" H 1700 6050 50  0001 C CNN
F 3 "" H 1700 6050 50  0001 C CNN
	1    1700 6050
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J?
U 1 1 5AFE1EA1
P 1550 1750
F 0 "J?" H 1550 1950 50  0000 C CNN
F 1 "Conn_01x04" H 1550 1450 50  0000 C CNN
F 2 "" H 1550 1750 50  0001 C CNN
F 3 "" H 1550 1750 50  0001 C CNN
	1    1550 1750
	1    0    0    -1  
$EndComp
$Comp
L Audio-Jack-4 J?
U 1 1 5AFE1F19
P 1550 2450
F 0 "J?" H 1500 2530 50  0000 C CNN
F 1 "Audio-Jack-4" H 1670 2080 50  0000 C CNN
F 2 "" H 1800 2550 50  0001 C CNN
F 3 "" H 1800 2550 50  0001 C CNN
	1    1550 2450
	1    0    0    -1  
$EndComp
$Comp
L Conn_Coaxial_Power J?
U 1 1 5AFE1FD0
P 1500 3600
F 0 "J?" V 1300 3550 50  0000 C CNN
F 1 "Conn_Coaxial_Power" V 1375 3550 50  0000 C CNN
F 2 "" H 1500 3550 50  0001 C CNN
F 3 "" H 1500 3550 50  0001 C CNN
	1    1500 3600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
