EESchema Schematic File Version 5
EELAYER 36 0
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
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Connection ~ 4150 2500
Connection ~ 4850 4250
Connection ~ 5350 2500
Connection ~ 5350 3250
Connection ~ 5350 4250
Connection ~ 5350 4550
Connection ~ 5700 4550
Wire Wire Line
	4150 2500 4150 2750
Wire Wire Line
	4150 2500 5350 2500
Wire Wire Line
	4750 3650 5600 3650
Wire Wire Line
	4750 3750 6300 3750
Wire Wire Line
	4750 4250 4850 4250
Wire Wire Line
	4850 3250 4750 3250
Wire Wire Line
	4850 4250 4950 4250
Wire Wire Line
	4900 2800 4900 3050
Wire Wire Line
	4900 3050 4750 3050
Wire Wire Line
	5200 2800 4900 2800
Wire Wire Line
	5250 3250 5350 3250
Wire Wire Line
	5350 2500 5350 2650
Wire Wire Line
	5350 2500 6800 2500
Wire Wire Line
	5350 2950 5350 3250
Wire Wire Line
	5350 3250 5350 4250
Wire Wire Line
	5350 4250 5350 4550
Wire Wire Line
	5350 4550 4150 4550
Wire Wire Line
	5600 3650 5600 3050
Wire Wire Line
	5700 4550 5350 4550
Wire Wire Line
	5900 3050 6300 3050
Wire Wire Line
	6300 3750 6300 3250
Wire Wire Line
	6800 2500 6800 2850
Wire Wire Line
	6800 4050 6800 4550
Wire Wire Line
	6800 4550 5700 4550
Wire Wire Line
	7300 3350 8650 3350
Wire Wire Line
	7300 3550 8650 3550
Wire Wire Line
	8650 3350 8650 3400
Wire Wire Line
	8650 3550 8650 3500
$Comp
L power:+5V #PWR?
U 1 1 6294B4B7
P 4150 2500
F 0 "#PWR?" H 4150 2350 50  0001 C CNN
F 1 "+5V" H 4165 2673 50  0000 C CNN
F 2 "" H 4150 2500 50  0001 C CNN
F 3 "" H 4150 2500 50  0001 C CNN
	1    4150 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62950A8F
P 4850 3950
F 0 "#PWR?" H 4850 3800 50  0001 C CNN
F 1 "+5V" H 4865 4123 50  0000 C CNN
F 2 "" H 4850 3950 50  0001 C CNN
F 3 "" H 4850 3950 50  0001 C CNN
	1    4850 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6295080E
P 5700 4550
F 0 "#PWR?" H 5700 4300 50  0001 C CNN
F 1 "GND" H 5705 4377 50  0000 C CNN
F 2 "" H 5700 4550 50  0001 C CNN
F 3 "" H 5700 4550 50  0001 C CNN
	1    5700 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 62931335
P 4850 4100
F 0 "R2" H 4920 4146 50  0000 L CNN
F 1 "10K" H 4920 4055 50  0000 L CNN
F 2 "" V 4780 4100 50  0001 C CNN
F 3 "~" H 4850 4100 50  0001 C CNN
	1    4850 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 62929649
P 5750 3050
F 0 "R1" V 5543 3050 50  0000 C CNN
F 1 "1K" V 5634 3050 50  0000 C CNN
F 2 "" V 5680 3050 50  0001 C CNN
F 3 "~" H 5750 3050 50  0001 C CNN
	1    5750 3050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 6292BF86
P 5050 3250
F 0 "SW1" H 5050 3535 50  0000 C CNN
F 1 "Pause" H 5050 3444 50  0000 C CNN
F 2 "" H 5050 3450 50  0001 C CNN
F 3 "~" H 5050 3450 50  0001 C CNN
	1    5050 3250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 62930A90
P 5150 4250
F 0 "SW2" H 5150 4535 50  0000 C CNN
F 1 "Reset" H 5150 4444 50  0000 C CNN
F 2 "" H 5150 4450 50  0001 C CNN
F 3 "~" H 5150 4450 50  0001 C CNN
	1    5150 4250
	1    0    0    -1  
$EndComp
$Comp
L dplayer_swift-rescue:R_POT_TRIM-Device RV1(Volume)
U 1 1 6292A1D4
P 5350 2800
F 0 "RV1(Volume)" H 5280 2754 50  0000 R CNN
F 1 "10K" H 5280 2845 50  0000 R CNN
F 2 "" H 5350 2800 50  0001 C CNN
F 3 "~" H 5350 2800 50  0001 C CNN
	1    5350 2800
	-1   0    0    1   
$EndComp
$Comp
L Device:Speaker LS?
U 1 1 62922A2A
P 8850 3400
F 0 "LS?" H 9020 3396 50  0000 L CNN
F 1 "Speaker" H 9020 3305 50  0000 L CNN
F 2 "" H 8850 3200 50  0001 C CNN
F 3 "~" H 8840 3350 50  0001 C CNN
	1    8850 3400
	1    0    0    -1  
$EndComp
$Comp
L dplayer_swift-rescue:dfplayer-dfplayer U?
U 1 1 62910F78
P 6800 3450
F 0 "U?" H 6800 4231 50  0000 C CNN
F 1 "dfplayer" H 6800 4140 50  0000 C CNN
F 2 "DFPlayer" H 6800 3450 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpa5050.pdf" H 6800 3450 50  0001 C CNN
	1    6800 3450
	1    0    0    -1  
$EndComp
$Comp
L dplayer_swift-rescue:ATtiny84A-PU-MCU_Microchip_ATtiny U?
U 1 1 6290B3DF
P 4150 3650
F 0 "U?" H 3621 3696 50  0000 R CNN
F 1 "ATtiny84A-PU" H 3621 3605 50  0000 R CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 4150 3650 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc8183.pdf" H 4150 3650 50  0001 C CNN
	1    4150 3650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
