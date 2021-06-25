<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Marvell 88PM860x Interface
 *
 * Copyright (C) 2009 Marvell International Ltd.
 * 	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#अगर_अघोषित __LINUX_MFD_88PM860X_H
#घोषणा __LINUX_MFD_88PM860X_H

#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा MFD_NAME_SIZE		(40)

क्रमागत अणु
	CHIP_INVALID = 0,
	CHIP_PM8606,
	CHIP_PM8607,
	CHIP_MAX,
पूर्ण;

क्रमागत अणु
	PM8606_ID_INVALID,
	PM8606_ID_BACKLIGHT,
	PM8606_ID_LED,
	PM8606_ID_VIBRATOR,
	PM8606_ID_TOUCH,
	PM8606_ID_SOUND,
	PM8606_ID_CHARGER,
	PM8606_ID_MAX,
पूर्ण;


/* 8606 Registers */
#घोषणा PM8606_DCM_BOOST		(0x00)
#घोषणा PM8606_PWM			(0x01)

#घोषणा PM8607_MISC2			(0x42)

/* Power Up Log Register */
#घोषणा PM8607_POWER_UP_LOG		(0x3F)

/* Charger Control Registers */
#घोषणा PM8607_CCNT			(0x47)
#घोषणा PM8607_CHG_CTRL1		(0x48)
#घोषणा PM8607_CHG_CTRL2		(0x49)
#घोषणा PM8607_CHG_CTRL3		(0x4A)
#घोषणा PM8607_CHG_CTRL4		(0x4B)
#घोषणा PM8607_CHG_CTRL5		(0x4C)
#घोषणा PM8607_CHG_CTRL6		(0x4D)
#घोषणा PM8607_CHG_CTRL7		(0x4E)

/* Backlight Registers */
#घोषणा PM8606_WLED1A			(0x02)
#घोषणा PM8606_WLED1B			(0x03)
#घोषणा PM8606_WLED2A			(0x04)
#घोषणा PM8606_WLED2B			(0x05)
#घोषणा PM8606_WLED3A			(0x06)
#घोषणा PM8606_WLED3B			(0x07)

/* LED Registers */
#घोषणा PM8606_RGB2A			(0x08)
#घोषणा PM8606_RGB2B			(0x09)
#घोषणा PM8606_RGB2C			(0x0A)
#घोषणा PM8606_RGB2D			(0x0B)
#घोषणा PM8606_RGB1A			(0x0C)
#घोषणा PM8606_RGB1B			(0x0D)
#घोषणा PM8606_RGB1C			(0x0E)
#घोषणा PM8606_RGB1D			(0x0F)

#घोषणा PM8606_PREREGULATORA		(0x10)
#घोषणा PM8606_PREREGULATORB		(0x11)
#घोषणा PM8606_VIBRATORA		(0x12)
#घोषणा PM8606_VIBRATORB		(0x13)
#घोषणा PM8606_VCHG			(0x14)
#घोषणा PM8606_VSYS			(0x15)
#घोषणा PM8606_MISC			(0x16)
#घोषणा PM8606_CHIP_ID			(0x17)
#घोषणा PM8606_STATUS			(0x18)
#घोषणा PM8606_FLAGS			(0x19)
#घोषणा PM8606_PROTECTA			(0x1A)
#घोषणा PM8606_PROTECTB			(0x1B)
#घोषणा PM8606_PROTECTC			(0x1C)

/* Bit definitions of PM8606 रेजिस्टरs */
#घोषणा PM8606_DCM_500MA		(0x0)	/* current limit */
#घोषणा PM8606_DCM_750MA		(0x1)
#घोषणा PM8606_DCM_1000MA		(0x2)
#घोषणा PM8606_DCM_1250MA		(0x3)
#घोषणा PM8606_DCM_250MV		(0x0 << 2)
#घोषणा PM8606_DCM_300MV		(0x1 << 2)
#घोषणा PM8606_DCM_350MV		(0x2 << 2)
#घोषणा PM8606_DCM_400MV		(0x3 << 2)

#घोषणा PM8606_PWM_31200HZ		(0x0)
#घोषणा PM8606_PWM_15600HZ		(0x1)
#घोषणा PM8606_PWM_7800HZ		(0x2)
#घोषणा PM8606_PWM_3900HZ		(0x3)
#घोषणा PM8606_PWM_1950HZ		(0x4)
#घोषणा PM8606_PWM_976HZ		(0x5)
#घोषणा PM8606_PWM_488HZ		(0x6)
#घोषणा PM8606_PWM_244HZ		(0x7)
#घोषणा PM8606_PWM_FREQ_MASK		(0x7)

#घोषणा PM8606_WLED_ON			(1 << 0)
#घोषणा PM8606_WLED_CURRENT(x)		((x & 0x1F) << 1)

#घोषणा PM8606_LED_CURRENT(x)		(((x >> 2) & 0x07) << 5)

#घोषणा PM8606_VSYS_EN			(1 << 1)

#घोषणा PM8606_MISC_OSC_EN		(1 << 4)

क्रमागत अणु
	PM8607_ID_BUCK1 = 0,
	PM8607_ID_BUCK2,
	PM8607_ID_BUCK3,

	PM8607_ID_LDO1,
	PM8607_ID_LDO2,
	PM8607_ID_LDO3,
	PM8607_ID_LDO4,
	PM8607_ID_LDO5,
	PM8607_ID_LDO6,
	PM8607_ID_LDO7,
	PM8607_ID_LDO8,
	PM8607_ID_LDO9,
	PM8607_ID_LDO10,
	PM8607_ID_LDO11,
	PM8607_ID_LDO12,
	PM8607_ID_LDO13,
	PM8607_ID_LDO14,
	PM8607_ID_LDO15,
	PM8606_ID_PREG,

	PM8607_ID_RG_MAX,
पूर्ण;

/* 8607 chip ID is 0x40 or 0x50 */
#घोषणा PM8607_VERSION_MASK		(0xF0)	/* 8607 chip ID mask */

/* Interrupt Registers */
#घोषणा PM8607_STATUS_1			(0x01)
#घोषणा PM8607_STATUS_2			(0x02)
#घोषणा PM8607_INT_STATUS1		(0x03)
#घोषणा PM8607_INT_STATUS2		(0x04)
#घोषणा PM8607_INT_STATUS3		(0x05)
#घोषणा PM8607_INT_MASK_1		(0x06)
#घोषणा PM8607_INT_MASK_2		(0x07)
#घोषणा PM8607_INT_MASK_3		(0x08)

/* Regulator Control Registers */
#घोषणा PM8607_LDO1			(0x10)
#घोषणा PM8607_LDO2			(0x11)
#घोषणा PM8607_LDO3			(0x12)
#घोषणा PM8607_LDO4			(0x13)
#घोषणा PM8607_LDO5			(0x14)
#घोषणा PM8607_LDO6			(0x15)
#घोषणा PM8607_LDO7			(0x16)
#घोषणा PM8607_LDO8			(0x17)
#घोषणा PM8607_LDO9			(0x18)
#घोषणा PM8607_LDO10			(0x19)
#घोषणा PM8607_LDO12			(0x1A)
#घोषणा PM8607_LDO14			(0x1B)
#घोषणा PM8607_SLEEP_MODE1		(0x1C)
#घोषणा PM8607_SLEEP_MODE2		(0x1D)
#घोषणा PM8607_SLEEP_MODE3		(0x1E)
#घोषणा PM8607_SLEEP_MODE4		(0x1F)
#घोषणा PM8607_GO			(0x20)
#घोषणा PM8607_SLEEP_BUCK1		(0x21)
#घोषणा PM8607_SLEEP_BUCK2		(0x22)
#घोषणा PM8607_SLEEP_BUCK3		(0x23)
#घोषणा PM8607_BUCK1			(0x24)
#घोषणा PM8607_BUCK2			(0x25)
#घोषणा PM8607_BUCK3			(0x26)
#घोषणा PM8607_BUCK_CONTROLS		(0x27)
#घोषणा PM8607_SUPPLIES_EN11		(0x2B)
#घोषणा PM8607_SUPPLIES_EN12		(0x2C)
#घोषणा PM8607_GROUP1			(0x2D)
#घोषणा PM8607_GROUP2			(0x2E)
#घोषणा PM8607_GROUP3			(0x2F)
#घोषणा PM8607_GROUP4			(0x30)
#घोषणा PM8607_GROUP5			(0x31)
#घोषणा PM8607_GROUP6			(0x32)
#घोषणा PM8607_SUPPLIES_EN21		(0x33)
#घोषणा PM8607_SUPPLIES_EN22		(0x34)

/* Vibrator Control Registers */
#घोषणा PM8607_VIBRATOR_SET		(0x28)
#घोषणा PM8607_VIBRATOR_PWM		(0x29)

/* GPADC Registers */
#घोषणा PM8607_GP_BIAS1			(0x4F)
#घोषणा PM8607_MEAS_EN1			(0x50)
#घोषणा PM8607_MEAS_EN2			(0x51)
#घोषणा PM8607_MEAS_EN3			(0x52)
#घोषणा PM8607_MEAS_OFF_TIME1		(0x53)
#घोषणा PM8607_MEAS_OFF_TIME2		(0x54)
#घोषणा PM8607_TSI_PREBIAS		(0x55)	/* prebias समय */
#घोषणा PM8607_PD_PREBIAS		(0x56)	/* prebias समय */
#घोषणा PM8607_GPADC_MISC1		(0x57)

/* bit definitions of  MEAS_EN1*/
#घोषणा PM8607_MEAS_EN1_VBAT		(1 << 0)
#घोषणा PM8607_MEAS_EN1_VCHG		(1 << 1)
#घोषणा PM8607_MEAS_EN1_VSYS		(1 << 2)
#घोषणा PM8607_MEAS_EN1_TINT		(1 << 3)
#घोषणा PM8607_MEAS_EN1_RFTMP		(1 << 4)
#घोषणा PM8607_MEAS_EN1_TBAT		(1 << 5)
#घोषणा PM8607_MEAS_EN1_GPADC2		(1 << 6)
#घोषणा PM8607_MEAS_EN1_GPADC3		(1 << 7)

/* Battery Monitor Registers */
#घोषणा PM8607_GP_BIAS2			(0x5A)
#घोषणा PM8607_VBAT_LOWTH		(0x5B)
#घोषणा PM8607_VCHG_LOWTH		(0x5C)
#घोषणा PM8607_VSYS_LOWTH		(0x5D)
#घोषणा PM8607_TINT_LOWTH		(0x5E)
#घोषणा PM8607_GPADC0_LOWTH		(0x5F)
#घोषणा PM8607_GPADC1_LOWTH		(0x60)
#घोषणा PM8607_GPADC2_LOWTH		(0x61)
#घोषणा PM8607_GPADC3_LOWTH		(0x62)
#घोषणा PM8607_VBAT_HIGHTH		(0x63)
#घोषणा PM8607_VCHG_HIGHTH		(0x64)
#घोषणा PM8607_VSYS_HIGHTH		(0x65)
#घोषणा PM8607_TINT_HIGHTH		(0x66)
#घोषणा PM8607_GPADC0_HIGHTH		(0x67)
#घोषणा PM8607_GPADC1_HIGHTH		(0x68)
#घोषणा PM8607_GPADC2_HIGHTH		(0x69)
#घोषणा PM8607_GPADC3_HIGHTH		(0x6A)
#घोषणा PM8607_IBAT_MEAS1		(0x6B)
#घोषणा PM8607_IBAT_MEAS2		(0x6C)
#घोषणा PM8607_VBAT_MEAS1		(0x6D)
#घोषणा PM8607_VBAT_MEAS2		(0x6E)
#घोषणा PM8607_VCHG_MEAS1		(0x6F)
#घोषणा PM8607_VCHG_MEAS2		(0x70)
#घोषणा PM8607_VSYS_MEAS1		(0x71)
#घोषणा PM8607_VSYS_MEAS2		(0x72)
#घोषणा PM8607_TINT_MEAS1		(0x73)
#घोषणा PM8607_TINT_MEAS2		(0x74)
#घोषणा PM8607_GPADC0_MEAS1		(0x75)
#घोषणा PM8607_GPADC0_MEAS2		(0x76)
#घोषणा PM8607_GPADC1_MEAS1		(0x77)
#घोषणा PM8607_GPADC1_MEAS2		(0x78)
#घोषणा PM8607_GPADC2_MEAS1		(0x79)
#घोषणा PM8607_GPADC2_MEAS2		(0x7A)
#घोषणा PM8607_GPADC3_MEAS1		(0x7B)
#घोषणा PM8607_GPADC3_MEAS2		(0x7C)
#घोषणा PM8607_CCNT_MEAS1		(0x95)
#घोषणा PM8607_CCNT_MEAS2		(0x96)
#घोषणा PM8607_VBAT_AVG			(0x97)
#घोषणा PM8607_VCHG_AVG			(0x98)
#घोषणा PM8607_VSYS_AVG			(0x99)
#घोषणा PM8607_VBAT_MIN			(0x9A)
#घोषणा PM8607_VCHG_MIN			(0x9B)
#घोषणा PM8607_VSYS_MIN			(0x9C)
#घोषणा PM8607_VBAT_MAX			(0x9D)
#घोषणा PM8607_VCHG_MAX			(0x9E)
#घोषणा PM8607_VSYS_MAX			(0x9F)

#घोषणा PM8607_GPADC_MISC2		(0x59)
#घोषणा PM8607_GPADC0_GP_BIAS_A0	(1 << 0)
#घोषणा PM8607_GPADC1_GP_BIAS_A1	(1 << 1)
#घोषणा PM8607_GPADC2_GP_BIAS_A2	(1 << 2)
#घोषणा PM8607_GPADC3_GP_BIAS_A3	(1 << 3)
#घोषणा PM8607_GPADC2_GP_BIAS_OUT2	(1 << 6)

/* RTC Control Registers */
#घोषणा PM8607_RTC1			(0xA0)
#घोषणा PM8607_RTC_COUNTER1		(0xA1)
#घोषणा PM8607_RTC_COUNTER2		(0xA2)
#घोषणा PM8607_RTC_COUNTER3		(0xA3)
#घोषणा PM8607_RTC_COUNTER4		(0xA4)
#घोषणा PM8607_RTC_EXPIRE1		(0xA5)
#घोषणा PM8607_RTC_EXPIRE2		(0xA6)
#घोषणा PM8607_RTC_EXPIRE3		(0xA7)
#घोषणा PM8607_RTC_EXPIRE4		(0xA8)
#घोषणा PM8607_RTC_TRIM1		(0xA9)
#घोषणा PM8607_RTC_TRIM2		(0xAA)
#घोषणा PM8607_RTC_TRIM3		(0xAB)
#घोषणा PM8607_RTC_TRIM4		(0xAC)
#घोषणा PM8607_RTC_MISC1		(0xAD)
#घोषणा PM8607_RTC_MISC2		(0xAE)
#घोषणा PM8607_RTC_MISC3		(0xAF)

/* Misc Registers */
#घोषणा PM8607_CHIP_ID			(0x00)
#घोषणा PM8607_B0_MISC1			(0x0C)
#घोषणा PM8607_LDO1			(0x10)
#घोषणा PM8607_DVC3			(0x26)
#घोषणा PM8607_A1_MISC1			(0x40)

/* bit definitions of Status Query Interface */
#घोषणा PM8607_STATUS_CC		(1 << 3)
#घोषणा PM8607_STATUS_PEN		(1 << 4)
#घोषणा PM8607_STATUS_HEADSET		(1 << 5)
#घोषणा PM8607_STATUS_HOOK		(1 << 6)
#घोषणा PM8607_STATUS_MICIN		(1 << 7)
#घोषणा PM8607_STATUS_ONKEY		(1 << 8)
#घोषणा PM8607_STATUS_EXTON		(1 << 9)
#घोषणा PM8607_STATUS_CHG		(1 << 10)
#घोषणा PM8607_STATUS_BAT		(1 << 11)
#घोषणा PM8607_STATUS_VBUS		(1 << 12)
#घोषणा PM8607_STATUS_OV		(1 << 13)

/* bit definitions of BUCK3 */
#घोषणा PM8607_BUCK3_DOUBLE		(1 << 6)

/* bit definitions of Misc1 */
#घोषणा PM8607_A1_MISC1_PI2C		(1 << 0)
#घोषणा PM8607_B0_MISC1_INV_INT		(1 << 0)
#घोषणा PM8607_B0_MISC1_INT_CLEAR	(1 << 1)
#घोषणा PM8607_B0_MISC1_INT_MASK	(1 << 2)
#घोषणा PM8607_B0_MISC1_PI2C		(1 << 3)
#घोषणा PM8607_B0_MISC1_RESET		(1 << 6)

/* bits definitions of GPADC */
#घोषणा PM8607_GPADC_EN			(1 << 0)
#घोषणा PM8607_GPADC_PREBIAS_MASK	(3 << 1)
#घोषणा PM8607_GPADC_SLOT_CYCLE_MASK	(3 << 3)	/* slow mode */
#घोषणा PM8607_GPADC_OFF_SCALE_MASK	(3 << 5)	/* GP sleep mode */
#घोषणा PM8607_GPADC_SW_CAL_MASK	(1 << 7)

#घोषणा PM8607_PD_PREBIAS_MASK		(0x1F << 0)
#घोषणा PM8607_PD_PRECHG_MASK		(7 << 5)

#घोषणा PM8606_REF_GP_OSC_OFF         0
#घोषणा PM8606_REF_GP_OSC_ON          1
#घोषणा PM8606_REF_GP_OSC_UNKNOWN     2

/* Clients of reference group and 8MHz oscillator in 88PM8606 */
क्रमागत pm8606_ref_gp_and_osc_clients अणु
	REF_GP_NO_CLIENTS       = 0,
	WLED1_DUTY              = (1<<0), /*PF 0x02.7:0*/
	WLED2_DUTY              = (1<<1), /*PF 0x04.7:0*/
	WLED3_DUTY              = (1<<2), /*PF 0x06.7:0*/
	RGB1_ENABLE             = (1<<3), /*PF 0x07.1*/
	RGB2_ENABLE             = (1<<4), /*PF 0x07.2*/
	LDO_VBR_EN              = (1<<5), /*PF 0x12.0*/
	REF_GP_MAX_CLIENT       = 0xFFFF
पूर्ण;

/* Interrupt Number in 88PM8607 */
क्रमागत अणु
	PM8607_IRQ_ONKEY,
	PM8607_IRQ_EXTON,
	PM8607_IRQ_CHG,
	PM8607_IRQ_BAT,
	PM8607_IRQ_RTC,
	PM8607_IRQ_CC,
	PM8607_IRQ_VBAT,
	PM8607_IRQ_VCHG,
	PM8607_IRQ_VSYS,
	PM8607_IRQ_TINT,
	PM8607_IRQ_GPADC0,
	PM8607_IRQ_GPADC1,
	PM8607_IRQ_GPADC2,
	PM8607_IRQ_GPADC3,
	PM8607_IRQ_AUDIO_SHORT,
	PM8607_IRQ_PEN,
	PM8607_IRQ_HEADSET,
	PM8607_IRQ_HOOK,
	PM8607_IRQ_MICIN,
	PM8607_IRQ_CHG_FAIL,
	PM8607_IRQ_CHG_DONE,
	PM8607_IRQ_CHG_FAULT,
पूर्ण;

क्रमागत अणु
	PM8607_CHIP_A0 = 0x40,
	PM8607_CHIP_A1 = 0x41,
	PM8607_CHIP_B0 = 0x48,
पूर्ण;

काष्ठा pm860x_chip अणु
	काष्ठा device		*dev;
	काष्ठा mutex		irq_lock;
	काष्ठा mutex		osc_lock;
	काष्ठा i2c_client	*client;
	काष्ठा i2c_client	*companion;	/* companion chip client */
	काष्ठा regmap           *regmap;
	काष्ठा regmap           *regmap_companion;

	पूर्णांक			buck3_द्विगुन;	/* DVC ramp slope द्विगुन */
	पूर्णांक			companion_addr;
	अचिन्हित लघु		osc_vote;
	पूर्णांक			id;
	पूर्णांक			irq_mode;
	पूर्णांक			irq_base;
	पूर्णांक			core_irq;
	अचिन्हित अक्षर		chip_version;
	अचिन्हित अक्षर		osc_status;

	अचिन्हित पूर्णांक            wakeup_flag;
पूर्ण;

क्रमागत अणु
	GI2C_PORT = 0,
	PI2C_PORT,
पूर्ण;

काष्ठा pm860x_backlight_pdata अणु
	पूर्णांक		pwm;
	पूर्णांक		iset;
पूर्ण;

काष्ठा pm860x_led_pdata अणु
	पूर्णांक		iset;
पूर्ण;

काष्ठा pm860x_rtc_pdata अणु
	पूर्णांक		(*sync)(अचिन्हित पूर्णांक ticks);
	पूर्णांक		vrtc;
पूर्ण;

काष्ठा pm860x_touch_pdata अणु
	पूर्णांक		gpadc_prebias;
	पूर्णांक		slot_cycle;
	पूर्णांक		off_scale;
	पूर्णांक		sw_cal;
	पूर्णांक		tsi_prebias;	/* समय, slot */
	पूर्णांक		pen_prebias;	/* समय, slot */
	पूर्णांक		pen_prechg;	/* समय, slot */
	पूर्णांक		res_x;		/* resistor of Xplate */
	अचिन्हित दीर्घ	flags;
पूर्ण;

काष्ठा pm860x_घातer_pdata अणु
	पूर्णांक		max_capacity;
	पूर्णांक		resistor;
पूर्ण;

काष्ठा pm860x_platक्रमm_data अणु
	काष्ठा pm860x_backlight_pdata	*backlight;
	काष्ठा pm860x_led_pdata		*led;
	काष्ठा pm860x_rtc_pdata		*rtc;
	काष्ठा pm860x_touch_pdata	*touch;
	काष्ठा pm860x_घातer_pdata	*घातer;
	काष्ठा regulator_init_data	*buck1;
	काष्ठा regulator_init_data	*buck2;
	काष्ठा regulator_init_data	*buck3;
	काष्ठा regulator_init_data	*lकरो1;
	काष्ठा regulator_init_data	*lकरो2;
	काष्ठा regulator_init_data	*lकरो3;
	काष्ठा regulator_init_data	*lकरो4;
	काष्ठा regulator_init_data	*lकरो5;
	काष्ठा regulator_init_data	*lकरो6;
	काष्ठा regulator_init_data	*lकरो7;
	काष्ठा regulator_init_data	*lकरो8;
	काष्ठा regulator_init_data	*lकरो9;
	काष्ठा regulator_init_data	*lकरो10;
	काष्ठा regulator_init_data	*lकरो12;
	काष्ठा regulator_init_data	*lकरो_vibrator;
	काष्ठा regulator_init_data	*lकरो14;
	काष्ठा अक्षरger_desc		*chg_desc;

	पूर्णांक 		companion_addr;	/* I2C address of companion chip */
	पूर्णांक		i2c_port;	/* Controlled by GI2C or PI2C */
	पूर्णांक		irq_mode;	/* Clear पूर्णांकerrupt by पढ़ो/ग_लिखो(0/1) */
	पूर्णांक		irq_base;	/* IRQ base number of 88pm860x */
	पूर्णांक		num_leds;
	पूर्णांक		num_backlights;
पूर्ण;

बाह्य पूर्णांक pm8606_osc_enable(काष्ठा pm860x_chip *, अचिन्हित लघु);
बाह्य पूर्णांक pm8606_osc_disable(काष्ठा pm860x_chip *, अचिन्हित लघु);

बाह्य पूर्णांक pm860x_reg_पढ़ो(काष्ठा i2c_client *, पूर्णांक);
बाह्य पूर्णांक pm860x_reg_ग_लिखो(काष्ठा i2c_client *, पूर्णांक, अचिन्हित अक्षर);
बाह्य पूर्णांक pm860x_bulk_पढ़ो(काष्ठा i2c_client *, पूर्णांक, पूर्णांक, अचिन्हित अक्षर *);
बाह्य पूर्णांक pm860x_bulk_ग_लिखो(काष्ठा i2c_client *, पूर्णांक, पूर्णांक, अचिन्हित अक्षर *);
बाह्य पूर्णांक pm860x_set_bits(काष्ठा i2c_client *, पूर्णांक, अचिन्हित अक्षर,
			   अचिन्हित अक्षर);
बाह्य पूर्णांक pm860x_page_reg_पढ़ो(काष्ठा i2c_client *, पूर्णांक);
बाह्य पूर्णांक pm860x_page_reg_ग_लिखो(काष्ठा i2c_client *, पूर्णांक, अचिन्हित अक्षर);
बाह्य पूर्णांक pm860x_page_bulk_पढ़ो(काष्ठा i2c_client *, पूर्णांक, पूर्णांक,
				 अचिन्हित अक्षर *);
बाह्य पूर्णांक pm860x_page_bulk_ग_लिखो(काष्ठा i2c_client *, पूर्णांक, पूर्णांक,
				  अचिन्हित अक्षर *);
बाह्य पूर्णांक pm860x_page_set_bits(काष्ठा i2c_client *, पूर्णांक, अचिन्हित अक्षर,
				अचिन्हित अक्षर);

#पूर्ण_अगर /* __LINUX_MFD_88PM860X_H */
