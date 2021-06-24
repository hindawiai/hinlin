<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * max14577.h - Driver क्रम the Maxim 14577/77836
 *
 * Copyright (C) 2014 Samsung Electrnoics
 * Chanwoo Choi <cw00.choi@samsung.com>
 * Krzysztof Kozlowski <krzk@kernel.org>
 *
 * This driver is based on max8997.h
 *
 * MAX14577 has MUIC, Charger devices.
 * The devices share the same I2C bus and पूर्णांकerrupt line
 * included in this mfd driver.
 *
 * MAX77836 has additional PMIC and Fuel-Gauge on dअगरferent I2C slave
 * addresses.
 */

#अगर_अघोषित __MAX14577_H__
#घोषणा __MAX14577_H__

#समावेश <linux/regulator/consumer.h>

/* MAX14577 regulator IDs */
क्रमागत max14577_regulators अणु
	MAX14577_SAFEOUT = 0,
	MAX14577_CHARGER,

	MAX14577_REGULATOR_NUM,
पूर्ण;

/* MAX77836 regulator IDs */
क्रमागत max77836_regulators अणु
	MAX77836_SAFEOUT = 0,
	MAX77836_CHARGER,
	MAX77836_LDO1,
	MAX77836_LDO2,

	MAX77836_REGULATOR_NUM,
पूर्ण;

काष्ठा max14577_regulator_platक्रमm_data अणु
	पूर्णांक id;
	काष्ठा regulator_init_data *initdata;
	काष्ठा device_node *of_node;
पूर्ण;

काष्ठा max14577_अक्षरger_platक्रमm_data अणु
	u32 स्थिरant_uvolt;
	u32 fast_अक्षरge_uamp;
	u32 eoc_uamp;
	u32 ovp_uvolt;
पूर्ण;

/*
 * MAX14577 MFD platक्रमm data
 */
काष्ठा max14577_platक्रमm_data अणु
	/* IRQ */
	पूर्णांक irq_base;

	/* current control GPIOs */
	पूर्णांक gpio_pogo_vbatt_en;
	पूर्णांक gpio_pogo_vbus_en;

	/* current control GPIO control function */
	पूर्णांक (*set_gpio_pogo_vbatt_en) (पूर्णांक gpio_val);
	पूर्णांक (*set_gpio_pogo_vbus_en) (पूर्णांक gpio_val);

	पूर्णांक (*set_gpio_pogo_cb) (पूर्णांक new_dev);

	काष्ठा max14577_regulator_platक्रमm_data *regulators;
पूर्ण;

/*
 * Valid limits of current क्रम max14577 and max77836 अक्षरgers.
 * They must correspond to MBCICHWRCL and MBCICHWRCH fields in CHGCTRL4
 * रेजिस्टर क्रम given chipset.
 */
काष्ठा maxim_अक्षरger_current अणु
	/* Minimal current, set in CHGCTRL4/MBCICHWRCL, uA */
	अचिन्हित पूर्णांक min;
	/*
	 * Minimal current when high setting is active,
	 * set in CHGCTRL4/MBCICHWRCH, uA
	 */
	अचिन्हित पूर्णांक high_start;
	/* Value of one step in high setting, uA */
	अचिन्हित पूर्णांक high_step;
	/* Maximum current of high setting, uA */
	अचिन्हित पूर्णांक max;
पूर्ण;

बाह्य स्थिर काष्ठा maxim_अक्षरger_current maxim_अक्षरger_currents[];
बाह्य पूर्णांक maxim_अक्षरger_calc_reg_current(स्थिर काष्ठा maxim_अक्षरger_current *limits,
		अचिन्हित पूर्णांक min_ua, अचिन्हित पूर्णांक max_ua, u8 *dst);

#पूर्ण_अगर /* __MAX14577_H__ */
