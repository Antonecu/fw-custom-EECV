#include "pch.h"

Gpio getCommsLedPin() {
	return Gpio::Unassigned;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::D9;
}

static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = Gpio::D13;
	engineConfiguration->injectionPins[1] = Gpio::D12;
	engineConfiguration->injectionPins[2] = Gpio::D11;
	engineConfiguration->injectionPins[3] = Gpio::D10;
}

static void setIgnitionPins() {
	engineConfiguration->ignitionPins[0] = Gpio::E8;
	engineConfiguration->ignitionPins[1] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[2] = Gpio::E9;
	engineConfiguration->ignitionPins[3] = Gpio::Unassigned;
}

static void setSensorPins() {
	engineConfiguration->clt.adcChannel = EFI_ADC_10;
	engineConfiguration->iat.adcChannel = EFI_ADC_7;
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_11;
	engineConfiguration->afr.hwChannel = EFI_ADC_2;
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_12;
        engineConfiguration->map.sensor.type = MT_MPX4250;
	engineConfiguration->mafAdcChannel = EFI_ADC_9;
	engineConfiguration->maf2AdcChannel = EFI_ADC_15;
	engineConfiguration->triggerInputPins[0] = Gpio::E0;
	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;
        engineConfiguration->camInputs[0] = Gpio::E1;
	engineConfiguration->camInputs[1] = Gpio::Unassigned;
	engineConfiguration->vehicleSpeedSensorInputPin = Gpio::A5;
	engineConfiguration->lps25BaroSensorScl = Gpio::B10;
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;
//	engineConfiguration->baroSensor.type = MT_MPXH6400;
//    	engineConfiguration->baroSensor.hwChannel = EFI_ADC_8;
}

static void setupVbatt() {
	// 470 high side/ 910 low side
	engineConfiguration->analogInputDividerCoefficient = 1.55f;
	
	// 6.34k high side/ 1k low side
	engineConfiguration->vbattDividerCoeff = (6.34 + 1) / 1; 

	// Battery sense on PC3
	engineConfiguration->vbattAdcChannel = EFI_ADC_13;

	engineConfiguration->adcVcc = 3.3f;
}

//Board-specific configuration setup
void setBoardDefaultConfiguration() {
	setInjectorPins();
	setIgnitionPins();
	setSensorPins();
	setupVbatt();
	
	engineConfiguration->clt.config.bias_resistor = 2490;
	engineConfiguration->iat.config.bias_resistor = 2490;

	engineConfiguration->enableSoftwareKnock = true;
	engineConfiguration->cylindersCount = 4;
	engineConfiguration->firingOrder = FO_1_3_4_2;

	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	engineConfiguration->injectionMode = IM_SEQUENTIAL;
	engineConfiguration->globalTriggerAngleOffset = 0;
	engineConfiguration->displacement = 1.596;
	engineConfiguration->injector.flow = 165;
        engineConfiguration->cranking.baseFuel = 25;
	engineConfiguration->cranking.rpm = 400;
	
//Digital Input
	engineConfiguration->acSwitch = Gpio::E7;
	engineConfiguration->clutchDownPin = Gpio::E4;
	engineConfiguration->clutchDownPinMode = PI_PULLDOWN;
	engineConfiguration->launchActivationMode = CLUTCH_INPUT_LAUNCH;
	engineConfiguration->malfunctionIndicatorPin = Gpio::D8;
	
//Low Side Outputs 
	engineConfiguration->fuelPumpPin = Gpio::E3;
	engineConfiguration->fanPin = Gpio::E6;
	engineConfiguration->fan2Pin = Gpio::D15;
	engineConfiguration->tachOutputPin = Gpio::C13;
	engineConfiguration->mainRelayPin = Gpio::Unassigned;
	engineConfiguration->acRelayPin = Gpio::Unassigned;
        engineConfiguration->boostControlPin = Gpio::Unassigned;
	engineConfiguration->vvtPins[0] = Gpio::Unassigned;
	engineConfiguration->vvtPins[1] = Gpio::Unassigned;

//Idle configuration
	engineConfiguration->useStepperIdle = false;
	engineConfiguration->isDoubleSolenoidIdle = false;
	engineConfiguration->idle.solenoidPin = Gpio::C6;
	engineConfiguration->secondSolenoidPin = Gpio::Unassigned;
	
//CAN 1 bus overwrites
	engineConfiguration->canRxPin = Gpio::D0;
	engineConfiguration->canTxPin = Gpio::D1;
	engineConfiguration->canWriteEnabled = true;
	engineConfiguration->canReadEnabled = true;
	engineConfiguration->canSleepPeriodMs = 50;
	engineConfiguration->canBaudRate = B500KBPS;

//SPI2 for on-board EGT
	engineConfiguration->is_enabled_spi_2 = true;
	// MOSI not needed, we have one-way communication here
	engineConfiguration->spi2misoPin = Gpio::B14;
	engineConfiguration->spi2sckPin = Gpio::B13;
	engineConfiguration->max31855_cs[0] = Gpio::B12;
	engineConfiguration->max31855spiDevice = SPI_DEVICE_2;

//SD card is located on SDIO interface
	engineConfiguration->isSdCardEnabled = true;
}
