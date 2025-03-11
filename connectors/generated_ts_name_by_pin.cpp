//DO NOT EDIT MANUALLY, let automation work hard.

// auto-generated by PinoutLogic.java based on ../../../connectors/custom_firmware.yaml
#include "pch.h"

// see comments at declaration in pin_repository.h
const char * getBoardSpecificPinName(brain_pin_e brainPin) {
	switch(brainPin) {
		case Gpio::A5: return "VSS (PA5)";
		case Gpio::A8: return "VESW (PA8)";
		case Gpio::B12: return "SPI2 CS (B12)";
		case Gpio::B13: return "SPI2 SCK (B13)";
		case Gpio::B14: return "SPI2 MISO (B14)";
		case Gpio::B15: return "SPI2 MOSI (B15)";
		case Gpio::B6: return "PB6";
		case Gpio::B7: return "PB7";
		case Gpio::B8: return "PB8";
		case Gpio::B9: return "PB9";
		case Gpio::C13: return "TACHO (PC13)";
		case Gpio::C6: return "IDLE (PC6)";
		case Gpio::C7: return "O2 HEATER (PC7)";
		case Gpio::D0: return "CAN 1 RX (D0)";
		case Gpio::D1: return "CAN 1 TX (D1)";
		case Gpio::D10: return "INJ4 (PD10)";
		case Gpio::D11: return "INJ3 (PD11)";
		case Gpio::D12: return "INJ2 (PD12)";
		case Gpio::D13: return "INJ1 (PD13)";
		case Gpio::D14: return "AC RELAY (PD14)";
		case Gpio::D15: return "FAN2 (PD15)";
		case Gpio::D4: return "FLEX (PD4)";
		case Gpio::D5: return "TX3 (PD5)";
		case Gpio::D6: return "RX3 (PD6)";
		case Gpio::D7: return "CLT GAUGE (PD7)";
		case Gpio::D8: return "CHECK (PD8)";
		case Gpio::D9: return "LED (PD9)";
		case Gpio::E0: return "CKP (PE0)";
		case Gpio::E1: return "CMP (PE1)";
		case Gpio::E10: return "IGN3  (PE10)";
		case Gpio::E11: return "IGN4 (PE11)";
		case Gpio::E12: return "PE12";
		case Gpio::E13: return "PE13";
		case Gpio::E14: return "PE14";
		case Gpio::E15: return "PE15";
		case Gpio::E2: return "ACPRESS (PE2)";
		case Gpio::E3: return "PUMP (PE3)";
		case Gpio::E4: return "CLUTCH (PE4)";
		case Gpio::E5: return "PSP (PE5)";
		case Gpio::E6: return "FAN (PE6)";
		case Gpio::E7: return "ACSW (PE7)";
		case Gpio::E8: return "IGN1 (PE8)";
		case Gpio::E9: return "IGN2 (PE9)";
		default: return nullptr;
	}
	return nullptr;
}
