Example Description

This example describes how to use UART to communicate with PC.

Required Components:
    USBtoTTL adapter

Connect to PC
 - Connect Ground: connect to GND pin via USBtoTTL adapter
HS
 - Use UART1
	GPIOG_5 as UART1_RX connect to TX of USBtoTTL adapter
	GPIOG_4 as UART1_TX connect to RX of USBtoTTL adapter
LS
 - Use UART0
	GPIOA_7 as UART1_RX connect to TX of USBtoTTL adapter
	GPIOA_8 as UART1_TX connect to RX of USBtoTTL adapter

Open Super terminal or teraterm and 
set baud rate to 38400, 1 stopbit, no parity, no flow contorl.

This example shows:
User input will be received by demo board, and demo board will loopback the received character with a prompt string "8195a$".

