#ifndef UI_H
#define	UI_H

#include "synth.h"

enum uiDigitInput_e {diSynth,diLoadDecadeDigit,diStoreDecadeDigit,diLoadUnitDigit,diStoreUnitDigit};
enum uiParamType_e {ptCont,ptStep,ptCust};

struct uiParam_s
{
	enum uiParamType_e type;
	int8_t number;
	const char * name;
	const char * values[4];
};

struct ui_s
{
	enum uiDigitInput_e digitInput;
	int8_t presetAwaitingNumber;
	int8_t presetModified;

	p600Pot_t lastActivePot;
	uint8_t manualActivePotValue;
	
	int32_t previousData;
	int8_t activeParamIdx;
};

extern struct ui_s ui;

void ui_init(void);
void ui_dataPotChanged(void);
void ui_handleButton(p600Button_t button, int pressed);
void ui_setPresetModified(int8_t modified);
int8_t ui_isPresetModified(void);

#endif	/* UI_H */

