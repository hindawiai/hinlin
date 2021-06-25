<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * KB3310B Embedded Controller
 *
 *  Copyright (C) 2008 Lemote Inc.
 *  Author: liujl <liujl@lemote.com>, 2008-03-14
 */

#अगर_अघोषित _EC_KB3310B_H
#घोषणा _EC_KB3310B_H

बाह्य अचिन्हित अक्षर ec_पढ़ो(अचिन्हित लघु addr);
बाह्य व्योम ec_ग_लिखो(अचिन्हित लघु addr, अचिन्हित अक्षर val);
बाह्य पूर्णांक ec_query_seq(अचिन्हित अक्षर cmd);
बाह्य पूर्णांक ec_query_event_num(व्योम);
बाह्य पूर्णांक ec_get_event_num(व्योम);

प्रकार पूर्णांक (*sci_handler) (पूर्णांक status);
बाह्य sci_handler yeeloong_report_lid_status;

#घोषणा SCI_IRQ_NUM 0x0A

/*
 * The following रेजिस्टरs are determined by the EC index configuration.
 * 1, fill the PORT_HIGH as EC रेजिस्टर high part.
 * 2, fill the PORT_LOW as EC रेजिस्टर low part.
 * 3, fill the PORT_DATA as EC रेजिस्टर ग_लिखो data or get the data from it.
 */
#घोषणा EC_IO_PORT_HIGH 0x0381
#घोषणा EC_IO_PORT_LOW	0x0382
#घोषणा EC_IO_PORT_DATA 0x0383

/*
 * EC delay समय is 500us क्रम रेजिस्टर and status access
 */
#घोषणा EC_REG_DELAY	500	/* unit : us */
#घोषणा EC_CMD_TIMEOUT	0x1000

/*
 * EC access port क्रम SCI communication
 */
#घोषणा EC_CMD_PORT		0x66
#घोषणा EC_STS_PORT		0x66
#घोषणा EC_DAT_PORT		0x62
#घोषणा CMD_INIT_IDLE_MODE	0xdd
#घोषणा CMD_EXIT_IDLE_MODE	0xdf
#घोषणा CMD_INIT_RESET_MODE	0xd8
#घोषणा CMD_REBOOT_SYSTEM	0x8c
#घोषणा CMD_GET_EVENT_NUM	0x84
#घोषणा CMD_PROGRAM_PIECE	0xda

/* temperature & fan रेजिस्टरs */
#घोषणा REG_TEMPERATURE_VALUE	0xF458
#घोषणा REG_FAN_AUTO_MAN_SWITCH 0xF459
#घोषणा BIT_FAN_AUTO		0
#घोषणा BIT_FAN_MANUAL		1
#घोषणा REG_FAN_CONTROL		0xF4D2
#घोषणा BIT_FAN_CONTROL_ON	(1 << 0)
#घोषणा BIT_FAN_CONTROL_OFF	(0 << 0)
#घोषणा REG_FAN_STATUS		0xF4DA
#घोषणा BIT_FAN_STATUS_ON	(1 << 0)
#घोषणा BIT_FAN_STATUS_OFF	(0 << 0)
#घोषणा REG_FAN_SPEED_HIGH	0xFE22
#घोषणा REG_FAN_SPEED_LOW	0xFE23
#घोषणा REG_FAN_SPEED_LEVEL	0xF4CC
/* fan speed भागider */
#घोषणा FAN_SPEED_DIVIDER	480000	/* (60*1000*1000/62.5/2)*/

/* battery रेजिस्टरs */
#घोषणा REG_BAT_DESIGN_CAP_HIGH		0xF77D
#घोषणा REG_BAT_DESIGN_CAP_LOW		0xF77E
#घोषणा REG_BAT_FULLCHG_CAP_HIGH	0xF780
#घोषणा REG_BAT_FULLCHG_CAP_LOW		0xF781
#घोषणा REG_BAT_DESIGN_VOL_HIGH		0xF782
#घोषणा REG_BAT_DESIGN_VOL_LOW		0xF783
#घोषणा REG_BAT_CURRENT_HIGH		0xF784
#घोषणा REG_BAT_CURRENT_LOW		0xF785
#घोषणा REG_BAT_VOLTAGE_HIGH		0xF786
#घोषणा REG_BAT_VOLTAGE_LOW		0xF787
#घोषणा REG_BAT_TEMPERATURE_HIGH	0xF788
#घोषणा REG_BAT_TEMPERATURE_LOW		0xF789
#घोषणा REG_BAT_RELATIVE_CAP_HIGH	0xF492
#घोषणा REG_BAT_RELATIVE_CAP_LOW	0xF493
#घोषणा REG_BAT_VENDOR			0xF4C4
#घोषणा FLAG_BAT_VENDOR_SANYO		0x01
#घोषणा FLAG_BAT_VENDOR_SIMPLO		0x02
#घोषणा REG_BAT_CELL_COUNT		0xF4C6
#घोषणा FLAG_BAT_CELL_3S1P		0x03
#घोषणा FLAG_BAT_CELL_3S2P		0x06
#घोषणा REG_BAT_CHARGE			0xF4A2
#घोषणा FLAG_BAT_CHARGE_DISCHARGE	0x01
#घोषणा FLAG_BAT_CHARGE_CHARGE		0x02
#घोषणा FLAG_BAT_CHARGE_ACPOWER		0x00
#घोषणा REG_BAT_STATUS			0xF4B0
#घोषणा BIT_BAT_STATUS_LOW		(1 << 5)
#घोषणा BIT_BAT_STATUS_DESTROY		(1 << 2)
#घोषणा BIT_BAT_STATUS_FULL		(1 << 1)
#घोषणा BIT_BAT_STATUS_IN		(1 << 0)
#घोषणा REG_BAT_CHARGE_STATUS		0xF4B1
#घोषणा BIT_BAT_CHARGE_STATUS_OVERTEMP	(1 << 2)
#घोषणा BIT_BAT_CHARGE_STATUS_PRECHG	(1 << 1)
#घोषणा REG_BAT_STATE			0xF482
#घोषणा BIT_BAT_STATE_CHARGING		(1 << 1)
#घोषणा BIT_BAT_STATE_DISCHARGING	(1 << 0)
#घोषणा REG_BAT_POWER			0xF440
#घोषणा BIT_BAT_POWER_S3		(1 << 2)
#घोषणा BIT_BAT_POWER_ON		(1 << 1)
#घोषणा BIT_BAT_POWER_ACIN		(1 << 0)

/* other रेजिस्टरs */
/* Audio: rd/wr */
#घोषणा REG_AUDIO_VOLUME	0xF46C
#घोषणा REG_AUDIO_MUTE		0xF4E7
#घोषणा REG_AUDIO_BEEP		0xF4D0
/* USB port घातer or not: rd/wr */
#घोषणा REG_USB0_FLAG		0xF461
#घोषणा REG_USB1_FLAG		0xF462
#घोषणा REG_USB2_FLAG		0xF463
#घोषणा BIT_USB_FLAG_ON		1
#घोषणा BIT_USB_FLAG_OFF	0
/* LID */
#घोषणा REG_LID_DETECT		0xF4BD
#घोषणा BIT_LID_DETECT_ON	1
#घोषणा BIT_LID_DETECT_OFF	0
/* CRT */
#घोषणा REG_CRT_DETECT		0xF4AD
#घोषणा BIT_CRT_DETECT_PLUG	1
#घोषणा BIT_CRT_DETECT_UNPLUG	0
/* LCD backlight brightness adjust: 9 levels */
#घोषणा REG_DISPLAY_BRIGHTNESS	0xF4F5
/* Black screen Status */
#घोषणा BIT_DISPLAY_LCD_ON	1
#घोषणा BIT_DISPLAY_LCD_OFF	0
/* LCD backlight control: off/restore */
#घोषणा REG_BACKLIGHT_CTRL	0xF7BD
#घोषणा BIT_BACKLIGHT_ON	1
#घोषणा BIT_BACKLIGHT_OFF	0
/* Reset the machine स्वतः-clear: rd/wr */
#घोषणा REG_RESET		0xF4EC
#घोषणा BIT_RESET_ON		1
/* Light the led: rd/wr */
#घोषणा REG_LED			0xF4C8
#घोषणा BIT_LED_RED_POWER	(1 << 0)
#घोषणा BIT_LED_ORANGE_POWER	(1 << 1)
#घोषणा BIT_LED_GREEN_CHARGE	(1 << 2)
#घोषणा BIT_LED_RED_CHARGE	(1 << 3)
#घोषणा BIT_LED_NUMLOCK		(1 << 4)
/* Test led mode, all led on/off */
#घोषणा REG_LED_TEST		0xF4C2
#घोषणा BIT_LED_TEST_IN		1
#घोषणा BIT_LED_TEST_OUT	0
/* Camera on/off */
#घोषणा REG_CAMERA_STATUS	0xF46A
#घोषणा BIT_CAMERA_STATUS_ON	1
#घोषणा BIT_CAMERA_STATUS_OFF	0
#घोषणा REG_CAMERA_CONTROL	0xF7B7
#घोषणा BIT_CAMERA_CONTROL_OFF	0
#घोषणा BIT_CAMERA_CONTROL_ON	1
/* Wlan Status */
#घोषणा REG_WLAN		0xF4FA
#घोषणा BIT_WLAN_ON		1
#घोषणा BIT_WLAN_OFF		0
#घोषणा REG_DISPLAY_LCD		0xF79F

/* SCI Event Number from EC */
क्रमागत अणु
	EVENT_LID = 0x23,	/*  LID खोलो/बंद */
	EVENT_DISPLAY_TOGGLE,	/*  Fn+F3 क्रम display चयन */
	EVENT_SLEEP,		/*  Fn+F1 क्रम entering sleep mode */
	EVENT_OVERTEMP,		/*  Over-temperature happened */
	EVENT_CRT_DETECT,	/*  CRT is connected */
	EVENT_CAMERA,		/*  Camera on/off */
	EVENT_USB_OC2,		/*  USB2 Over Current occurred */
	EVENT_USB_OC0,		/*  USB0 Over Current occurred */
	EVENT_BLACK_SCREEN,	/*  Turn on/off backlight */
	EVENT_AUDIO_MUTE,	/*  Mute on/off */
	EVENT_DISPLAY_BRIGHTNESS,/* LCD backlight brightness adjust */
	EVENT_AC_BAT,		/*  AC & Battery relative issue */
	EVENT_AUDIO_VOLUME,	/*  Volume adjust */
	EVENT_WLAN,		/*  Wlan on/off */
	EVENT_END
पूर्ण;

#पूर्ण_अगर /* !_EC_KB3310B_H */
