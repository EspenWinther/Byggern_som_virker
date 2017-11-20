################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ADC_test.c \
../Buzz.c \
../Byggern.c \
../CAN.c \
../eeprom.c \
../Game_play.c \
../Joysick.c \
../MCP2515.c \
../OLED.c \
../SPI.c \
../SRAM_test.c \
../UART.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC_test.o \
Buzz.o \
Byggern.o \
CAN.o \
eeprom.o \
Game_play.o \
Joysick.o \
MCP2515.o \
OLED.o \
SPI.o \
SRAM_test.o \
UART.o

OBJS_AS_ARGS +=  \
ADC_test.o \
Buzz.o \
Byggern.o \
CAN.o \
eeprom.o \
Game_play.o \
Joysick.o \
MCP2515.o \
OLED.o \
SPI.o \
SRAM_test.o \
UART.o

C_DEPS +=  \
ADC_test.d \
Buzz.d \
Byggern.d \
CAN.d \
eeprom.d \
Game_play.d \
Joysick.d \
MCP2515.d \
OLED.d \
SPI.d \
SRAM_test.d \
UART.d

C_DEPS_AS_ARGS +=  \
ADC_test.d \
Buzz.d \
Byggern.d \
CAN.d \
eeprom.d \
Game_play.d \
Joysick.d \
MCP2515.d \
OLED.d \
SPI.d \
SRAM_test.d \
UART.d

OUTPUT_FILE_PATH +=Byggern.elf

OUTPUT_FILE_PATH_AS_ARGS +=Byggern.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler

























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=4915200UL  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega162 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Byggern.map" -Wl,--start-group  -Wl,--end-group -Wl,-L"C:\Users\gautevn\Byggern\Byggern" -Wl,-L"C:\Users\gautevn\Byggern\Byggern\Byggern" -Wl,-L"C:\Users\runarao\Downloads\Byggern-master\Byggern-master\Byggern\Byggern"  -Wl,--gc-sections -mmcu=atmega162  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Byggern.elf" "Byggern.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Byggern.elf" "Byggern.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Byggern.elf" > "Byggern.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Byggern.elf" "Byggern.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-size.exe" "Byggern.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Byggern.elf" "Byggern.a" "Byggern.hex" "Byggern.lss" "Byggern.eep" "Byggern.map" "Byggern.srec" "Byggern.usersignatures"
	