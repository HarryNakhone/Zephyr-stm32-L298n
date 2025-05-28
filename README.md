# Motor Control on Zephyr RTOS

Here is how you can run a motor using Zephyr RTOS

## Required Tools 

STM32F4 Discovery
L298n Motor Driver
A couple of wheels (optional)
A power supply, I used 5v
Motors
Jumper wires


### Prerequisites
- List (Zephyr, Python, VsCode etc...). Visit the website for more info

### Installation
```bash
# Example of running commands

#build 
west build -p always -b stm32f4_disco

#flash 

west flash
