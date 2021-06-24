<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IBM TrackPoपूर्णांक PS/2 mouse driver
 *
 * Stephen Evanchik <evanchsa@gmail.com>
 */

#अगर_अघोषित _TRACKPOINT_H
#घोषणा _TRACKPOINT_H

/*
 * These स्थिरants are from the TrackPoपूर्णांक System
 * Engineering करोcumentation Version 4 from IBM Watson
 * research:
 *	http://wwwcssrv.almaden.ibm.com/trackpoपूर्णांक/करोwnload.hपंचांगl
 */

#घोषणा TP_COMMAND		0xE2	/* Commands start with this */

#घोषणा TP_READ_ID		0xE1	/* Sent क्रम device identअगरication */

/*
 * Valid first byte responses to the "Read Secondary ID" (0xE1) command.
 * 0x01 was the original IBM trackpoपूर्णांक, others implement very limited
 * subset of trackpoपूर्णांक features.
 */
#घोषणा TP_VARIANT_IBM			0x01
#घोषणा TP_VARIANT_ALPS			0x02
#घोषणा TP_VARIANT_ELAN			0x03
#घोषणा TP_VARIANT_NXP			0x04
#घोषणा TP_VARIANT_JYT_SYNAPTICS	0x05
#घोषणा TP_VARIANT_SYNAPTICS		0x06

/*
 * Commands
 */
#घोषणा TP_RECALIB		0x51	/* Recalibrate */
#घोषणा TP_POWER_DOWN		0x44	/* Can only be unकरोne through HW reset */
#घोषणा TP_EXT_DEV		0x21	/* Determines अगर बाह्यal device is connected (RO) */
#घोषणा TP_EXT_BTN		0x4B	/* Read extended button status */
#घोषणा TP_POR			0x7F	/* Execute Power on Reset */
#घोषणा TP_POR_RESULTS		0x25	/* Read Power on Self test results */
#घोषणा TP_DISABLE_EXT		0x40	/* Disable बाह्यal poपूर्णांकing device */
#घोषणा TP_ENABLE_EXT		0x41	/* Enable बाह्यal poपूर्णांकing device */

/*
 * Mode manipulation
 */
#घोषणा TP_SET_SOFT_TRANS	0x4E	/* Set mode */
#घोषणा TP_CANCEL_SOFT_TRANS	0xB9	/* Cancel mode */
#घोषणा TP_SET_HARD_TRANS	0x45	/* Mode can only be set */


/*
 * Register oriented commands/properties
 */
#घोषणा TP_WRITE_MEM		0x81
#घोषणा TP_READ_MEM		0x80	/* Not used in this implementation */

/*
* RAM Locations क्रम properties
 */
#घोषणा TP_SENS			0x4A	/* Sensitivity */
#घोषणा TP_MB			0x4C	/* Read Middle Button Status (RO) */
#घोषणा TP_INERTIA		0x4D	/* Negative Inertia */
#घोषणा TP_SPEED		0x60	/* Speed of TP Cursor */
#घोषणा TP_REACH		0x57	/* Backup क्रम Z-axis press */
#घोषणा TP_DRAGHYS		0x58	/* Drag Hysteresis */
					/* (how hard it is to drag */
					/* with Z-axis pressed) */

#घोषणा TP_MINDRAG		0x59	/* Minimum amount of क्रमce needed */
					/* to trigger dragging */

#घोषणा TP_THRESH		0x5C	/* Minimum value क्रम a Z-axis press */
#घोषणा TP_UP_THRESH		0x5A	/* Used to generate a 'click' on Z-axis */
#घोषणा TP_Z_TIME		0x5E	/* How sharp of a press */
#घोषणा TP_JENKS_CURV		0x5D	/* Minimum curvature क्रम द्विगुन click */
#घोषणा TP_DRIFT_TIME		0x5F	/* How दीर्घ a 'hands off' condition */
					/* must last (x*107ms) क्रम drअगरt */
					/* correction to occur */

/*
 * Toggling Flag bits
 */
#घोषणा TP_TOGGLE		0x47	/* Toggle command */

#घोषणा TP_TOGGLE_MB		0x23	/* Disable/Enable Middle Button */
#घोषणा TP_MASK_MB			0x01
#घोषणा TP_TOGGLE_EXT_DEV	0x23	/* Disable बाह्यal device */
#घोषणा TP_MASK_EXT_DEV			0x02
#घोषणा TP_TOGGLE_DRIFT		0x23	/* Drअगरt Correction */
#घोषणा TP_MASK_DRIFT			0x80
#घोषणा TP_TOGGLE_BURST		0x28	/* Burst Mode */
#घोषणा TP_MASK_BURST			0x80
#घोषणा TP_TOGGLE_PTSON		0x2C	/* Press to Select */
#घोषणा TP_MASK_PTSON			0x01
#घोषणा TP_TOGGLE_HARD_TRANS	0x2C	/* Alternate method to set Hard Transparency */
#घोषणा TP_MASK_HARD_TRANS		0x80
#घोषणा TP_TOGGLE_TWOHAND	0x2D	/* Two handed */
#घोषणा TP_MASK_TWOHAND			0x01
#घोषणा TP_TOGGLE_STICKY_TWO	0x2D	/* Sticky two handed */
#घोषणा TP_MASK_STICKY_TWO		0x04
#घोषणा TP_TOGGLE_SKIPBACK	0x2D	/* Suppress movement after drag release */
#घोषणा TP_MASK_SKIPBACK		0x08
#घोषणा TP_TOGGLE_SOURCE_TAG	0x20	/* Bit 3 of the first packet will be set to
					   to the origin of the packet (बाह्यal or TP) */
#घोषणा TP_MASK_SOURCE_TAG		0x80
#घोषणा TP_TOGGLE_EXT_TAG	0x22	/* Bit 3 of the first packet coming from the
					   बाह्यal device will be क्रमced to 1 */
#घोषणा TP_MASK_EXT_TAG			0x04


/* Power on Self Test Results */
#घोषणा TP_POR_SUCCESS		0x3B

/*
 * Default घातer on values
 */
#घोषणा TP_DEF_SENS		0x80
#घोषणा TP_DEF_INERTIA		0x06
#घोषणा TP_DEF_SPEED		0x61
#घोषणा TP_DEF_REACH		0x0A

#घोषणा TP_DEF_DRAGHYS		0xFF
#घोषणा TP_DEF_MINDRAG		0x14

#घोषणा TP_DEF_THRESH		0x08
#घोषणा TP_DEF_UP_THRESH	0xFF
#घोषणा TP_DEF_Z_TIME		0x26
#घोषणा TP_DEF_JENKS_CURV	0x87
#घोषणा TP_DEF_DRIFT_TIME	0x05

/* Toggles */
#घोषणा TP_DEF_MB		0x00
#घोषणा TP_DEF_PTSON		0x00
#घोषणा TP_DEF_SKIPBACK		0x00
#घोषणा TP_DEF_EXT_DEV		0x00	/* 0 means enabled */
#घोषणा TP_DEF_TWOHAND		0x00
#घोषणा TP_DEF_SOURCE_TAG	0x00

#घोषणा MAKE_PS2_CMD(params, results, cmd) ((params<<12) | (results<<8) | (cmd))

काष्ठा trackpoपूर्णांक_data अणु
	u8 variant_id;
	u8 firmware_id;

	u8 sensitivity, speed, inertia, reach;
	u8 draghys, mindrag;
	u8 thresh, upthresh;
	u8 zसमय, jenks;
	u8 drअगरt_समय;

	/* toggles */
	bool press_to_select;
	bool skipback;
	bool ext_dev;
पूर्ण;

पूर्णांक trackpoपूर्णांक_detect(काष्ठा psmouse *psmouse, bool set_properties);

#पूर्ण_अगर /* _TRACKPOINT_H */
