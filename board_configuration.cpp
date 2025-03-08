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
	engineConfiguration->clt.config = {-10, 60, 120, 160310, 7700, 1180, 2700};
	engineConfiguration->iat.config = {-10, 60, 120, 160310, 7700, 1180, 2700};

	engineConfiguration->tpsMin = 100;
	engineConfiguration->tpsMax = 750;

	engineConfiguration->enableSoftwareKnock = true;
	engineConfiguration->cylindersCount = 4;
	engineConfiguration->firingOrder = FO_1_3_4_2;

	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	engineConfiguration->injectionMode = IM_SEQUENTIAL;
	engineConfiguration->trigger.type = trigger_type_e::TT_TOOTHED_WHEEL_36_1;
	engineConfiguration->globalTriggerAngleOffset = -85;
	engineConfiguration->displacement = 1.596;
	engineConfiguration->cylinderBore = 79;
	engineConfiguration->vehicleWeight = 1035;
	engineConfiguration->compressionRatio = 11.0;
	engineConfiguration->injector.flow = 165;
        engineConfiguration->cranking.baseFuel = 25;
	engineConfiguration->cranking.rpm = 400;
	engineConfiguration->crankingTimingAngle = 13;
	engineConfiguration->rpmHardLimit = 6800;

	engineConfiguration->driveWheelRevPerKm = 552;
	engineConfiguration->finalGearRatio = 3.62;
	engineConfiguration->tachPulsePerRev = 2;
	
//Digital Input
	engineConfiguration->acSwitch = Gpio::E7;
	engineConfiguration->clutchDownPin = Gpio::E4;
	engineConfiguration->clutchDownPinMode = PI_PULLDOWN;
	engineConfiguration->launchActivationMode = CLUTCH_INPUT_LAUNCH;
	engineConfiguration->malfunctionIndicatorPin = Gpio::D8;
	
//Low Side Outputs 
	engineConfiguration->fuelPumpPin = Gpio::E3;
	engineConfiguration->fanPin = Gpio::E6;
	engineConfiguration->fanOffTemperature = 95;
	engineConfiguration->fanOnTemperature = 99;
	engineConfiguration->fan2Pin = Gpio::D15;
	engineConfiguration->tachOutputPin = Gpio::C13;
	engineConfiguration->mainRelayPin = Gpio::Unassigned;
	engineConfiguration->acRelayPin = Gpio::Unassigned;
        engineConfiguration->boostControlPin = Gpio::Unassigned;
	engineConfiguration->vvtPins[0] = Gpio::Unassigned;
	engineConfiguration->vvtPins[1] = Gpio::Unassigned;
	
// GPPWM0: PWM CLT Gauge 
	engineConfiguration->gppwm[0].pin = Gpio::Unassigned;
	engineConfiguration->gppwm[0].pwmFrequency = 100;
	engineConfiguration->gppwm[0].loadAxis = GPPWM_Clt;
	engineConfiguration->gppwm[0].onAboveDuty = 60;
	engineConfiguration->gppwm[0].offBelowDuty = 40;
	strcpy(engineConfiguration->gpPwmNote[0], "CLTGauge");
	copyArray(engineConfiguration->gppwm[0].rpmBins, { 0, 1000, 2000, 2500, 3500, 5500, 6500, 7000 });
	for (size_t i = 0; i < efi::size(engineConfiguration->gppwm[0].table); i++)
	{
		// Set the 3500 and 5500 rpm columns to 100
		engineConfiguration->gppwm[0].table[i][4] = 100;
		engineConfiguration->gppwm[0].table[i][5] = 100;
	}

//Idle configuration
	engineConfiguration->useStepperIdle = false;
	engineConfiguration->isDoubleSolenoidIdle = false;
	engineConfiguration->idle.solenoidPin = Gpio::C6;
	engineConfiguration->idle.solenoidFrequency = 500;
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

// Disable ETBs
	engineConfiguration->etbFunctions[0] = dc_function_e::DC_None;
	engineConfiguration->etbFunctions[1] = dc_function_e::DC_None;
}
