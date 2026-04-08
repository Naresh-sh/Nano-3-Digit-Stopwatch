# Nano-3-Digit-Stopwatch
Arduino Nano based 3-digit stopwatch (M.SS format) using multiplexed 7-segment displays and one-button control.


🚀 Features

• Displays time in format → M.SS
• Range → 0.00 to 9.59
• Single button control
• Smooth multiplex display (no flicker)
• Adjustable brightness
• Uses internal pullup (no extra resistor for button)
• Efficient millis() timing (no delay lag)



🎮 Button Controls

Press Count	Function
1   press	Start
2   press	Pause
3   press	Reset to 000


🔌 Hardware Required

Component	Quantity

1. Arduino Nano	1
2. 7 Segment Display (Common Anode)	3
3. Push Button	1
4. 220Ω resistors	8
5. Breadboard	1
6. Jumper wires	as needed



Segment Pins


Segment	Arduino Pin
a	   D2
b	   D3
c    D4
d    D5
e	   D6
f	   D7
g	   D8
dp   D13

Digit Pins

Digit Position	Arduino Pin

Left	D9
Middle	D10
Right	D12


Button Connection


A2 → Button → GND

Uses Arduino internal pullup resistor.


🖥️ Display Format

Example counting:

0.01
0.02
0.03
...
0.59
1.00
1.01
...
9.59


