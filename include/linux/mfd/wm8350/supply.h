<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * supply.h  --  Power Supply Driver क्रम Wolfson WM8350 PMIC
 *
 * Copyright 2007 Wolfson Microelectronics PLC
 */

#अगर_अघोषित __LINUX_MFD_WM8350_SUPPLY_H_
#घोषणा __LINUX_MFD_WM8350_SUPPLY_H_

#समावेश <linux/mutex.h>
#समावेश <linux/घातer_supply.h>

/*
 * Charger रेजिस्टरs
 */
#घोषणा WM8350_BATTERY_CHARGER_CONTROL_1        0xA8
#घोषणा WM8350_BATTERY_CHARGER_CONTROL_2        0xA9
#घोषणा WM8350_BATTERY_CHARGER_CONTROL_3        0xAA

/*
 * R168 (0xA8) - Battery Charger Control 1
 */
#घोषणा WM8350_CHG_ENA_R168                     0x8000
#घोषणा WM8350_CHG_THR                          0x2000
#घोषणा WM8350_CHG_EOC_SEL_MASK                 0x1C00
#घोषणा WM8350_CHG_TRICKLE_TEMP_CHOKE           0x0200
#घोषणा WM8350_CHG_TRICKLE_USB_CHOKE            0x0100
#घोषणा WM8350_CHG_RECOVER_T                    0x0080
#घोषणा WM8350_CHG_END_ACT                      0x0040
#घोषणा WM8350_CHG_FAST                         0x0020
#घोषणा WM8350_CHG_FAST_USB_THROTTLE            0x0010
#घोषणा WM8350_CHG_NTC_MON                      0x0008
#घोषणा WM8350_CHG_BATT_HOT_MON                 0x0004
#घोषणा WM8350_CHG_BATT_COLD_MON                0x0002
#घोषणा WM8350_CHG_CHIP_TEMP_MON                0x0001

/*
 * R169 (0xA9) - Battery Charger Control 2
 */
#घोषणा WM8350_CHG_ACTIVE                       0x8000
#घोषणा WM8350_CHG_PAUSE                        0x4000
#घोषणा WM8350_CHG_STS_MASK                     0x3000
#घोषणा WM8350_CHG_TIME_MASK                    0x0F00
#घोषणा WM8350_CHG_MASK_WALL_FB                 0x0080
#घोषणा WM8350_CHG_TRICKLE_SEL                  0x0040
#घोषणा WM8350_CHG_VSEL_MASK                    0x0030
#घोषणा WM8350_CHG_ISEL_MASK                    0x000F
#घोषणा WM8350_CHG_STS_OFF                      0x0000
#घोषणा WM8350_CHG_STS_TRICKLE                  0x1000
#घोषणा WM8350_CHG_STS_FAST                     0x2000

/*
 * R170 (0xAA) - Battery Charger Control 3
 */
#घोषणा WM8350_CHG_THROTTLE_T_MASK              0x0060
#घोषणा WM8350_CHG_SMART                        0x0010
#घोषणा WM8350_CHG_TIMER_ADJT_MASK              0x000F

/*
 * Charger Interrupts
 */
#घोषणा WM8350_IRQ_CHG_BAT_HOT			0
#घोषणा WM8350_IRQ_CHG_BAT_COLD			1
#घोषणा WM8350_IRQ_CHG_BAT_FAIL			2
#घोषणा WM8350_IRQ_CHG_TO			3
#घोषणा WM8350_IRQ_CHG_END			4
#घोषणा WM8350_IRQ_CHG_START			5
#घोषणा WM8350_IRQ_CHG_FAST_RDY			6
#घोषणा WM8350_IRQ_CHG_VBATT_LT_3P9		10
#घोषणा WM8350_IRQ_CHG_VBATT_LT_3P1		11
#घोषणा WM8350_IRQ_CHG_VBATT_LT_2P85		12

/*
 * Charger Policy
 */
#घोषणा WM8350_CHG_TRICKLE_50mA			(0 << 6)
#घोषणा WM8350_CHG_TRICKLE_100mA		(1 << 6)
#घोषणा WM8350_CHG_4_05V			(0 << 4)
#घोषणा WM8350_CHG_4_10V			(1 << 4)
#घोषणा WM8350_CHG_4_15V			(2 << 4)
#घोषणा WM8350_CHG_4_20V			(3 << 4)
#घोषणा WM8350_CHG_FAST_LIMIT_mA(x)		((x / 50) & 0xf)
#घोषणा WM8350_CHG_EOC_mA(x)			(((x - 10) & 0x7) << 10)
#घोषणा WM8350_CHG_TRICKLE_3_1V			(0 << 13)
#घोषणा WM8350_CHG_TRICKLE_3_9V			(1 << 13)

/*
 * Supply Registers.
 */
#घोषणा WM8350_USB_VOLTAGE_READBACK             0x9C
#घोषणा WM8350_LINE_VOLTAGE_READBACK            0x9D
#घोषणा WM8350_BATT_VOLTAGE_READBACK            0x9E

/*
 * Supply Interrupts.
 */
#घोषणा WM8350_IRQ_USB_LIMIT			15
#घोषणा WM8350_IRQ_EXT_USB_FB			36
#घोषणा WM8350_IRQ_EXT_WALL_FB			37
#घोषणा WM8350_IRQ_EXT_BAT_FB			38

/*
 * Policy to control अक्षरger state machine.
 */
काष्ठा wm8350_अक्षरger_policy अणु

	/* अक्षरger state machine policy  - set in machine driver */
	पूर्णांक eoc_mA;		/* end of अक्षरge current (mA)  */
	पूर्णांक अक्षरge_mV;		/* अक्षरge voltage */
	पूर्णांक fast_limit_mA;	/* fast अक्षरge current limit */
	पूर्णांक fast_limit_USB_mA;	/* USB fast अक्षरge current limit */
	पूर्णांक अक्षरge_समयout;	/* अक्षरge समयout (mins) */
	पूर्णांक trickle_start_mV;	/* trickle अक्षरge starts at mV */
	पूर्णांक trickle_अक्षरge_mA;	/* trickle अक्षरge current */
	पूर्णांक trickle_अक्षरge_USB_mA;	/* USB trickle अक्षरge current */
पूर्ण;

काष्ठा wm8350_घातer अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply *usb;
	काष्ठा घातer_supply *ac;
	काष्ठा wm8350_अक्षरger_policy *policy;

	पूर्णांक rev_g_coeff;
पूर्ण;

#पूर्ण_अगर
