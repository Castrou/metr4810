EESchema Schematic File Version 4
EELAYER 30 0
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
Text Notes 1350 1600 0    118  ~ 24
STM32 F303RE Interface
Wire Notes Line
	4500 1650 4500 4250
Wire Notes Line
	1300 4250 1300 1650
Wire Notes Line
	1300 1650 4500 1650
Wire Notes Line
	1300 4250 4500 4250
Text Label 3250 3850 0    50   ~ 0
D1
Text Label 3250 3950 0    50   ~ 0
D0
Wire Wire Line
	3400 3950 3250 3950
Wire Wire Line
	3250 3850 3400 3850
$Comp
L Connector_Generic:Conn_02x19_Odd_Even J?
U 1 1 5ED7D386
P 3600 3050
F 0 "J?" H 3650 4167 50  0000 C CNN
F 1 "Conn_02x19_Odd_Even" H 3650 4076 50  0000 C CNN
F 2 "" H 3600 3050 50  0001 C CNN
F 3 "~" H 3600 3050 50  0001 C CNN
	1    3600 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x19_Odd_Even J?
U 1 1 5ED85F25
P 2050 3050
F 0 "J?" H 2100 4167 50  0000 C CNN
F 1 "Conn_02x19_Odd_Even" H 2100 4076 50  0000 C CNN
F 2 "" H 2050 3050 50  0001 C CNN
F 3 "~" H 2050 3050 50  0001 C CNN
	1    2050 3050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
