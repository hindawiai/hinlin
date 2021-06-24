<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * LP855x Backlight Driver
 *
 *			Copyright (C) 2011 Texas Instruments
 */

#अगर_अघोषित _LP855X_H
#घोषणा _LP855X_H

#घोषणा BL_CTL_SHFT	(0)
#घोषणा BRT_MODE_SHFT	(1)
#घोषणा BRT_MODE_MASK	(0x06)

/* Enable backlight. Only valid when BRT_MODE=10(I2C only) */
#घोषणा ENABLE_BL	(1)
#घोषणा DISABLE_BL	(0)

#घोषणा I2C_CONFIG(id)	id ## _I2C_CONFIG
#घोषणा PWM_CONFIG(id)	id ## _PWM_CONFIG

/* DEVICE CONTROL रेजिस्टर - LP8550 */
#घोषणा LP8550_PWM_CONFIG	(LP8550_PWM_ONLY << BRT_MODE_SHFT)
#घोषणा LP8550_I2C_CONFIG	((ENABLE_BL << BL_CTL_SHFT) | \
				(LP8550_I2C_ONLY << BRT_MODE_SHFT))

/* DEVICE CONTROL रेजिस्टर - LP8551 */
#घोषणा LP8551_PWM_CONFIG	LP8550_PWM_CONFIG
#घोषणा LP8551_I2C_CONFIG	LP8550_I2C_CONFIG

/* DEVICE CONTROL रेजिस्टर - LP8552 */
#घोषणा LP8552_PWM_CONFIG	LP8550_PWM_CONFIG
#घोषणा LP8552_I2C_CONFIG	LP8550_I2C_CONFIG

/* DEVICE CONTROL रेजिस्टर - LP8553 */
#घोषणा LP8553_PWM_CONFIG	LP8550_PWM_CONFIG
#घोषणा LP8553_I2C_CONFIG	LP8550_I2C_CONFIG

/* CONFIG रेजिस्टर - LP8555 */
#घोषणा LP8555_PWM_STANDBY	BIT(7)
#घोषणा LP8555_PWM_FILTER	BIT(6)
#घोषणा LP8555_RELOAD_EPROM	BIT(3)	/* use it अगर EPROMs should be reset
					   when the backlight turns on */
#घोषणा LP8555_OFF_OPENLEDS	BIT(2)
#घोषणा LP8555_PWM_CONFIG	LP8555_PWM_ONLY
#घोषणा LP8555_I2C_CONFIG	LP8555_I2C_ONLY
#घोषणा LP8555_COMB1_CONFIG	LP8555_COMBINED1
#घोषणा LP8555_COMB2_CONFIG	LP8555_COMBINED2

/* DEVICE CONTROL रेजिस्टर - LP8556 */
#घोषणा LP8556_PWM_CONFIG	(LP8556_PWM_ONLY << BRT_MODE_SHFT)
#घोषणा LP8556_COMB1_CONFIG	(LP8556_COMBINED1 << BRT_MODE_SHFT)
#घोषणा LP8556_I2C_CONFIG	((ENABLE_BL << BL_CTL_SHFT) | \
				(LP8556_I2C_ONLY << BRT_MODE_SHFT))
#घोषणा LP8556_COMB2_CONFIG	(LP8556_COMBINED2 << BRT_MODE_SHFT)
#घोषणा LP8556_FAST_CONFIG	BIT(7) /* use it अगर EPROMs should be मुख्यtained
					  when निकासing the low घातer mode */

/* CONFIG रेजिस्टर - LP8557 */
#घोषणा LP8557_PWM_STANDBY	BIT(7)
#घोषणा LP8557_PWM_FILTER	BIT(6)
#घोषणा LP8557_RELOAD_EPROM	BIT(3)	/* use it अगर EPROMs should be reset
					   when the backlight turns on */
#घोषणा LP8557_OFF_OPENLEDS	BIT(2)
#घोषणा LP8557_PWM_CONFIG	LP8557_PWM_ONLY
#घोषणा LP8557_I2C_CONFIG	LP8557_I2C_ONLY
#घोषणा LP8557_COMB1_CONFIG	LP8557_COMBINED1
#घोषणा LP8557_COMB2_CONFIG	LP8557_COMBINED2

क्रमागत lp855x_chip_id अणु
	LP8550,
	LP8551,
	LP8552,
	LP8553,
	LP8555,
	LP8556,
	LP8557,
पूर्ण;

क्रमागत lp8550_brighntess_source अणु
	LP8550_PWM_ONLY,
	LP8550_I2C_ONLY = 2,
पूर्ण;

क्रमागत lp8551_brighntess_source अणु
	LP8551_PWM_ONLY = LP8550_PWM_ONLY,
	LP8551_I2C_ONLY = LP8550_I2C_ONLY,
पूर्ण;

क्रमागत lp8552_brighntess_source अणु
	LP8552_PWM_ONLY = LP8550_PWM_ONLY,
	LP8552_I2C_ONLY = LP8550_I2C_ONLY,
पूर्ण;

क्रमागत lp8553_brighntess_source अणु
	LP8553_PWM_ONLY = LP8550_PWM_ONLY,
	LP8553_I2C_ONLY = LP8550_I2C_ONLY,
पूर्ण;

क्रमागत lp8555_brightness_source अणु
	LP8555_PWM_ONLY,
	LP8555_I2C_ONLY,
	LP8555_COMBINED1,	/* Brightness रेजिस्टर with shaped PWM */
	LP8555_COMBINED2,	/* PWM with shaped brightness रेजिस्टर */
पूर्ण;

क्रमागत lp8556_brightness_source अणु
	LP8556_PWM_ONLY,
	LP8556_COMBINED1,	/* pwm + i2c beक्रमe the shaper block */
	LP8556_I2C_ONLY,
	LP8556_COMBINED2,	/* pwm + i2c after the shaper block */
पूर्ण;

क्रमागत lp8557_brightness_source अणु
	LP8557_PWM_ONLY,
	LP8557_I2C_ONLY,
	LP8557_COMBINED1,	/* pwm + i2c after the shaper block */
	LP8557_COMBINED2,	/* pwm + i2c beक्रमe the shaper block */
पूर्ण;

काष्ठा lp855x_rom_data अणु
	u8 addr;
	u8 val;
पूर्ण;

/**
 * काष्ठा lp855x_platक्रमm_data
 * @name : Backlight driver name. If it is not defined, शेष name is set.
 * @device_control : value of DEVICE CONTROL रेजिस्टर
 * @initial_brightness : initial value of backlight brightness
 * @period_ns : platक्रमm specअगरic pwm period value. unit is nano.
		Only valid when mode is PWM_BASED.
 * @size_program : total size of lp855x_rom_data
 * @rom_data : list of new eeprom/eprom रेजिस्टरs
 */
काष्ठा lp855x_platक्रमm_data अणु
	स्थिर अक्षर *name;
	u8 device_control;
	u8 initial_brightness;
	अचिन्हित पूर्णांक period_ns;
	पूर्णांक size_program;
	काष्ठा lp855x_rom_data *rom_data;
पूर्ण;

#पूर्ण_अगर
