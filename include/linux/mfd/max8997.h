<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * max8997.h - Driver क्रम the Maxim 8997/8966
 *
 *  Copyright (C) 2009-2010 Samsung Electrnoics
 *  MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This driver is based on max8998.h
 *
 * MAX8997 has PMIC, MUIC, HAPTIC, RTC, FLASH, and Fuel Gauge devices.
 * Except Fuel Gauge, every device shares the same I2C bus and included in
 * this mfd driver. Although the fuel gauge is included in the chip, it is
 * excluded from the driver because a) it has a dअगरferent I2C bus from
 * others and b) it can be enabled simply by using MAX17042 driver.
 */

#अगर_अघोषित __LINUX_MFD_MAX8997_H
#घोषणा __LINUX_MFD_MAX8997_H

#समावेश <linux/regulator/consumer.h>

/* MAX8997/8966 regulator IDs */
क्रमागत max8997_regulators अणु
	MAX8997_LDO1 = 0,
	MAX8997_LDO2,
	MAX8997_LDO3,
	MAX8997_LDO4,
	MAX8997_LDO5,
	MAX8997_LDO6,
	MAX8997_LDO7,
	MAX8997_LDO8,
	MAX8997_LDO9,
	MAX8997_LDO10,
	MAX8997_LDO11,
	MAX8997_LDO12,
	MAX8997_LDO13,
	MAX8997_LDO14,
	MAX8997_LDO15,
	MAX8997_LDO16,
	MAX8997_LDO17,
	MAX8997_LDO18,
	MAX8997_LDO21,
	MAX8997_BUCK1,
	MAX8997_BUCK2,
	MAX8997_BUCK3,
	MAX8997_BUCK4,
	MAX8997_BUCK5,
	MAX8997_BUCK6,
	MAX8997_BUCK7,
	MAX8997_EN32KHZ_AP,
	MAX8997_EN32KHZ_CP,
	MAX8997_ENVICHG,
	MAX8997_ESAFEOUT1,
	MAX8997_ESAFEOUT2,
	MAX8997_CHARGER_CV, /* control MBCCV of MBCCTRL3 */
	MAX8997_CHARGER, /* अक्षरger current, MBCCTRL4 */
	MAX8997_CHARGER_TOPOFF, /* MBCCTRL5 */

	MAX8997_REG_MAX,
पूर्ण;

काष्ठा max8997_regulator_data अणु
	पूर्णांक id;
	काष्ठा regulator_init_data *initdata;
	काष्ठा device_node *reg_node;
पूर्ण;

काष्ठा max8997_muic_reg_data अणु
	u8 addr;
	u8 data;
पूर्ण;

/**
 * काष्ठा max8997_muic_platक्रमm_data
 * @init_data: array of max8997_muic_reg_data
 *	       used क्रम initializing रेजिस्टरs of MAX8997 MUIC device
 * @num_init_data: array size of init_data
 */
काष्ठा max8997_muic_platक्रमm_data अणु
	काष्ठा max8997_muic_reg_data *init_data;
	पूर्णांक num_init_data;

	/* Check cable state after certain delay */
	पूर्णांक detcable_delay_ms;

	/*
	 * Default usb/uart path whether UART/USB or AUX_UART/AUX_USB
	 * h/w path of COMP2/COMN1 on CONTROL1 रेजिस्टर.
	 */
	पूर्णांक path_usb;
	पूर्णांक path_uart;
पूर्ण;

क्रमागत max8997_haptic_motor_type अणु
	MAX8997_HAPTIC_ERM,
	MAX8997_HAPTIC_LRA,
पूर्ण;

क्रमागत max8997_haptic_pulse_mode अणु
	MAX8997_EXTERNAL_MODE,
	MAX8997_INTERNAL_MODE,
पूर्ण;

क्रमागत max8997_haptic_pwm_भागisor अणु
	MAX8997_PWM_DIVISOR_32,
	MAX8997_PWM_DIVISOR_64,
	MAX8997_PWM_DIVISOR_128,
	MAX8997_PWM_DIVISOR_256,
पूर्ण;

/**
 * max8997_haptic_platक्रमm_data
 * @pwm_channel_id: channel number of PWM device
 *		    valid क्रम MAX8997_EXTERNAL_MODE
 * @pwm_period: period in nano second क्रम PWM device
 *		valid क्रम MAX8997_EXTERNAL_MODE
 * @type: motor type
 * @mode: pulse mode
 *     MAX8997_EXTERNAL_MODE: बाह्यal PWM device is used to control motor
 *     MAX8997_INTERNAL_MODE: पूर्णांकernal pulse generator is used to control motor
 * @pwm_भागisor: भागisor क्रम बाह्यal PWM device
 * @पूर्णांकernal_mode_pattern: पूर्णांकernal mode pattern क्रम पूर्णांकernal mode
 *     [0 - 3]: valid pattern number
 * @pattern_cycle: the number of cycles of the waveक्रमm
 *		   क्रम the पूर्णांकernal mode pattern
 *     [0 - 15]: available cycles
 * @pattern_संकेत_period: period of the waveक्रमm क्रम the पूर्णांकernal mode pattern
 *     [0 - 255]: available period
 */
काष्ठा max8997_haptic_platक्रमm_data अणु
	अचिन्हित पूर्णांक pwm_channel_id;
	अचिन्हित पूर्णांक pwm_period;

	क्रमागत max8997_haptic_motor_type type;
	क्रमागत max8997_haptic_pulse_mode mode;
	क्रमागत max8997_haptic_pwm_भागisor pwm_भागisor;

	अचिन्हित पूर्णांक पूर्णांकernal_mode_pattern;
	अचिन्हित पूर्णांक pattern_cycle;
	अचिन्हित पूर्णांक pattern_संकेत_period;
पूर्ण;

क्रमागत max8997_led_mode अणु
	MAX8997_NONE,
	MAX8997_FLASH_MODE,
	MAX8997_MOVIE_MODE,
	MAX8997_FLASH_PIN_CONTROL_MODE,
	MAX8997_MOVIE_PIN_CONTROL_MODE,
पूर्ण;

/**
 *  काष्ठा max8997_led_platक्रमm_data
 *  The number of LED devices क्रम MAX8997 is two
 *  @mode: LED mode क्रम each LED device
 *  @brightness: initial brightness क्रम each LED device
 *	range:
 *	[0 - 31]: MAX8997_FLASH_MODE and MAX8997_FLASH_PIN_CONTROL_MODE
 *	[0 - 15]: MAX8997_MOVIE_MODE and MAX8997_MOVIE_PIN_CONTROL_MODE
 */
काष्ठा max8997_led_platक्रमm_data अणु
	क्रमागत max8997_led_mode mode[2];
	u8 brightness[2];
पूर्ण;

काष्ठा max8997_platक्रमm_data अणु
	/* IRQ */
	पूर्णांक ono;

	/* ---- PMIC ---- */
	काष्ठा max8997_regulator_data *regulators;
	पूर्णांक num_regulators;

	/*
	 * SET1~3 DVS GPIOs control Buck1, 2, and 5 simultaneously. Thereक्रमe,
	 * With buckx_gpiodvs enabled, the buckx cannot be controlled
	 * independently. To control buckx (of 1, 2, and 5) independently,
	 * disable buckx_gpiodvs and control with BUCKxDVS1 रेजिस्टर.
	 *
	 * When buckx_gpiodvs and bucky_gpiodvs are both enabled, set_voltage
	 * on buckx will change the voltage of bucky at the same समय.
	 *
	 */
	bool ignore_gpiodvs_side_effect;
	पूर्णांक buck125_gpios[3]; /* GPIO of [0]SET1, [1]SET2, [2]SET3 */
	पूर्णांक buck125_शेष_idx; /* Default value of SET1, 2, 3 */
	अचिन्हित पूर्णांक buck1_voltage[8]; /* buckx_voltage in uV */
	bool buck1_gpiodvs;
	अचिन्हित पूर्णांक buck2_voltage[8];
	bool buck2_gpiodvs;
	अचिन्हित पूर्णांक buck5_voltage[8];
	bool buck5_gpiodvs;

	/* ---- Charger control ---- */
	/* eoc stands क्रम 'end of charge' */
	पूर्णांक eoc_mA; /* 50 ~ 200mA by 10mA step */
	/* अक्षरge Full Timeout */
	पूर्णांक समयout; /* 0 (no समयout), 5, 6, 7 hours */

	/* ---- MUIC ---- */
	काष्ठा max8997_muic_platक्रमm_data *muic_pdata;

	/* ---- HAPTIC ---- */
	काष्ठा max8997_haptic_platक्रमm_data *haptic_pdata;

	/* RTC: Not implemented */
	/* ---- LED ---- */
	काष्ठा max8997_led_platक्रमm_data *led_pdata;
पूर्ण;

#पूर्ण_अगर /* __LINUX_MFD_MAX8997_H */
