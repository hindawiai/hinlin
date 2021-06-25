<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * max8998.h - Voltage regulator driver क्रम the Maxim 8998
 *
 *  Copyright (C) 2009-2010 Samsung Electrnoics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *  Marek Szyprowski <m.szyprowski@samsung.com>
 */

#अगर_अघोषित __LINUX_MFD_MAX8998_H
#घोषणा __LINUX_MFD_MAX8998_H

#समावेश <linux/regulator/machine.h>

/* MAX 8998 regulator ids */
क्रमागत अणु
	MAX8998_LDO2 = 2,
	MAX8998_LDO3,
	MAX8998_LDO4,
	MAX8998_LDO5,
	MAX8998_LDO6,
	MAX8998_LDO7,
	MAX8998_LDO8,
	MAX8998_LDO9,
	MAX8998_LDO10,
	MAX8998_LDO11,
	MAX8998_LDO12,
	MAX8998_LDO13,
	MAX8998_LDO14,
	MAX8998_LDO15,
	MAX8998_LDO16,
	MAX8998_LDO17,
	MAX8998_BUCK1,
	MAX8998_BUCK2,
	MAX8998_BUCK3,
	MAX8998_BUCK4,
	MAX8998_EN32KHZ_AP,
	MAX8998_EN32KHZ_CP,
	MAX8998_ENVICHG,
	MAX8998_ESAFEOUT1,
	MAX8998_ESAFEOUT2,
	MAX8998_CHARGER,
पूर्ण;

/**
 * max8998_regulator_data - regulator data
 * @id: regulator id
 * @initdata: regulator init data (contraपूर्णांकs, supplies, ...)
 * @reg_node: DT node of regulator (unused on non-DT platक्रमms)
 */
काष्ठा max8998_regulator_data अणु
	पूर्णांक				id;
	काष्ठा regulator_init_data	*initdata;
	काष्ठा device_node		*reg_node;
पूर्ण;

/**
 * काष्ठा max8998_board - packages regulator init data
 * @regulators: array of defined regulators
 * @num_regulators: number of regulators used
 * @irq_base: base IRQ number क्रम max8998, required क्रम IRQs
 * @ono: घातer onoff IRQ number क्रम max8998
 * @buck_voltage_lock: Do NOT change the values of the following six
 *   रेजिस्टरs set by buck?_voltage?. The voltage of BUCK1/2 cannot
 *   be other than the preset values.
 * @buck1_voltage: BUCK1 DVS mode 1 voltage रेजिस्टरs
 * @buck2_voltage: BUCK2 DVS mode 2 voltage रेजिस्टरs
 * @buck1_set1: BUCK1 gpio pin 1 to set output voltage
 * @buck1_set2: BUCK1 gpio pin 2 to set output voltage
 * @buck1_शेष_idx: Default क्रम BUCK1 gpio pin 1, 2
 * @buck2_set3: BUCK2 gpio pin to set output voltage
 * @buck2_शेष_idx: Default क्रम BUCK2 gpio pin.
 * @wakeup: Allow to wake up from suspend
 * @rtc_delay: LP3974 RTC chip bug that requires delay after a रेजिस्टर
 * ग_लिखो beक्रमe पढ़ोing it.
 * @eoc: End of Charge Level in percent: 10% ~ 45% by 5% step
 *   If it equals 0, leave it unchanged.
 *   Otherwise, it is a invalid value.
 * @restart: Restart Level in mV: 100, 150, 200, and -1 क्रम disable.
 *   If it equals 0, leave it unchanged.
 *   Otherwise, it is a invalid value.
 * @समयout: Full Timeout in hours: 5, 6, 7, and -1 क्रम disable.
 *   If it equals 0, leave it unchanged.
 *   Otherwise, leave it unchanged.
 */
काष्ठा max8998_platक्रमm_data अणु
	काष्ठा max8998_regulator_data	*regulators;
	पूर्णांक				num_regulators;
	अचिन्हित पूर्णांक			irq_base;
	पूर्णांक				ono;
	bool				buck_voltage_lock;
	पूर्णांक				buck1_voltage[4];
	पूर्णांक				buck2_voltage[2];
	पूर्णांक				buck1_set1;
	पूर्णांक				buck1_set2;
	पूर्णांक				buck1_शेष_idx;
	पूर्णांक				buck2_set3;
	पूर्णांक				buck2_शेष_idx;
	bool				wakeup;
	bool				rtc_delay;
	पूर्णांक				eoc;
	पूर्णांक				restart;
	पूर्णांक				समयout;
पूर्ण;

#पूर्ण_अगर /*  __LINUX_MFD_MAX8998_H */
