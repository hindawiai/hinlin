<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MIOA701_H_
#घोषणा _MIOA701_H_

#घोषणा MIO_CFG_IN(pin, af)		\
	((MFP_CFG_DEFAULT & ~(MFP_AF_MASK | MFP_सूची_MASK)) |\
	 (MFP_PIN(pin) | MFP_##af | MFP_सूची_IN))

#घोषणा MIO_CFG_OUT(pin, af, state)	\
	((MFP_CFG_DEFAULT & ~(MFP_AF_MASK | MFP_सूची_MASK | MFP_LPM_STATE_MASK)) |\
	 (MFP_PIN(pin) | MFP_##af | MFP_सूची_OUT | MFP_LPM_##state))

/* Global GPIOs */
#घोषणा GPIO9_CHARGE_EN				9
#घोषणा GPIO18_POWEROFF				18
#घोषणा GPIO87_LCD_POWER			87
#घोषणा GPIO96_AC_DETECT			96
#घोषणा GPIO80_MAYBE_CHARGE_VDROP		80	/* Drop of 88mV */

/* USB */
#घोषणा GPIO13_nUSB_DETECT			13
#घोषणा GPIO22_USB_ENABLE			22

/* SDIO bits */
#घोषणा GPIO78_SDIO_RO				78
#घोषणा GPIO15_SDIO_INSERT			15
#घोषणा GPIO91_SDIO_EN				91

/* Bluetooth */
#घोषणा GPIO14_BT_nACTIVITY			14
#घोषणा GPIO83_BT_ON				83
#घोषणा GPIO77_BT_UNKNOWN1			77
#घोषणा GPIO86_BT_MAYBE_nRESET			86

/* GPS */
#घोषणा GPIO23_GPS_UNKNOWN1			23
#घोषणा GPIO26_GPS_ON				26
#घोषणा GPIO27_GPS_RESET			27
#घोषणा GPIO106_GPS_UNKNOWN2			106
#घोषणा GPIO107_GPS_UNKNOWN3			107

/* GSM */
#घोषणा GPIO24_GSM_MOD_RESET_CMD		24
#घोषणा GPIO88_GSM_nMOD_ON_CMD			88
#घोषणा GPIO90_GSM_nMOD_OFF_CMD			90
#घोषणा GPIO114_GSM_nMOD_DTE_UART_STATE 	114
#घोषणा GPIO25_GSM_MOD_ON_STATE			25
#घोषणा GPIO113_GSM_EVENT			113

/* SOUND */
#घोषणा GPIO12_HPJACK_INSERT			12

/* LEDS */
#घोषणा GPIO10_LED_nCharging			10
#घोषणा GPIO97_LED_nBlue			97
#घोषणा GPIO98_LED_nOrange			98
#घोषणा GPIO82_LED_nVibra			82
#घोषणा GPIO115_LED_nKeyboard			115

/* Keyboard */
#घोषणा GPIO0_KEY_POWER				0
#घोषणा GPIO93_KEY_VOLUME_UP			93
#घोषणा GPIO94_KEY_VOLUME_DOWN			94

/* Camera */
#घोषणा GPIO56_MT9M111_nOE			56

बाह्य काष्ठा input_dev *mioa701_evdev;
बाह्य व्योम mioa701_gpio_lpm_set(अचिन्हित दीर्घ mfp_pin);

/* Assembler बाह्यals mioa701_bootresume.S */
बाह्य u32 mioa701_bootstrap;
बाह्य u32 mioa701_jumpaddr;
बाह्य u32 mioa701_bootstrap_lg;

#पूर्ण_अगर /* _MIOA701_H */
