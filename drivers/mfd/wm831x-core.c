<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm831x-core.c  --  Device access क्रम Wolfson WM831x PMICs
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/mfd/wm831x/irq.h>
#समावेश <linux/mfd/wm831x/auxadc.h>
#समावेश <linux/mfd/wm831x/otp.h>
#समावेश <linux/mfd/wm831x/pmu.h>
#समावेश <linux/mfd/wm831x/regulator.h>

/* Current settings - values are 2*2^(reg_val/4) microamps.  These are
 * exported since they are used by multiple drivers.
 */
स्थिर अचिन्हित पूर्णांक wm831x_isinkv_values[WM831X_ISINK_MAX_ISEL + 1] = अणु
	2,
	2,
	3,
	3,
	4,
	5,
	6,
	7,
	8,
	10,
	11,
	13,
	16,
	19,
	23,
	27,
	32,
	38,
	45,
	54,
	64,
	76,
	91,
	108,
	128,
	152,
	181,
	215,
	256,
	304,
	362,
	431,
	512,
	609,
	724,
	861,
	1024,
	1218,
	1448,
	1722,
	2048,
	2435,
	2896,
	3444,
	4096,
	4871,
	5793,
	6889,
	8192,
	9742,
	11585,
	13777,
	16384,
	19484,
	23170,
	27554,
पूर्ण;
EXPORT_SYMBOL_GPL(wm831x_isinkv_values);

अटल पूर्णांक wm831x_reg_locked(काष्ठा wm831x *wm831x, अचिन्हित लघु reg)
अणु
	अगर (!wm831x->locked)
		वापस 0;

	चयन (reg) अणु
	हाल WM831X_WATCHDOG:
	हाल WM831X_DC4_CONTROL:
	हाल WM831X_ON_PIN_CONTROL:
	हाल WM831X_BACKUP_CHARGER_CONTROL:
	हाल WM831X_CHARGER_CONTROL_1:
	हाल WM831X_CHARGER_CONTROL_2:
		वापस 1;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/**
 * wm831x_reg_unlock: Unlock user keyed रेजिस्टरs
 *
 * The WM831x has a user key preventing ग_लिखोs to particularly
 * critical रेजिस्टरs.  This function locks those रेजिस्टरs,
 * allowing ग_लिखोs to them.
 *
 * @wm831x: poपूर्णांकer to local driver data काष्ठाure
 */
व्योम wm831x_reg_lock(काष्ठा wm831x *wm831x)
अणु
	पूर्णांक ret;

	ret = wm831x_reg_ग_लिखो(wm831x, WM831X_SECURITY_KEY, 0);
	अगर (ret == 0) अणु
		dev_vdbg(wm831x->dev, "Registers locked\n");

		mutex_lock(&wm831x->io_lock);
		WARN_ON(wm831x->locked);
		wm831x->locked = 1;
		mutex_unlock(&wm831x->io_lock);
	पूर्ण अन्यथा अणु
		dev_err(wm831x->dev, "Failed to lock registers: %d\n", ret);
	पूर्ण

पूर्ण
EXPORT_SYMBOL_GPL(wm831x_reg_lock);

/**
 * wm831x_reg_unlock: Unlock user keyed रेजिस्टरs
 *
 * The WM831x has a user key preventing ग_लिखोs to particularly
 * critical रेजिस्टरs.  This function locks those रेजिस्टरs,
 * preventing spurious ग_लिखोs.
 *
 * @wm831x: poपूर्णांकer to local driver data काष्ठाure
 */
पूर्णांक wm831x_reg_unlock(काष्ठा wm831x *wm831x)
अणु
	पूर्णांक ret;

	/* 0x9716 is the value required to unlock the रेजिस्टरs */
	ret = wm831x_reg_ग_लिखो(wm831x, WM831X_SECURITY_KEY, 0x9716);
	अगर (ret == 0) अणु
		dev_vdbg(wm831x->dev, "Registers unlocked\n");

		mutex_lock(&wm831x->io_lock);
		WARN_ON(!wm831x->locked);
		wm831x->locked = 0;
		mutex_unlock(&wm831x->io_lock);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm831x_reg_unlock);

अटल bool wm831x_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM831X_RESET_ID:
	हाल WM831X_REVISION:
	हाल WM831X_PARENT_ID:
	हाल WM831X_SYSVDD_CONTROL:
	हाल WM831X_THERMAL_MONITORING:
	हाल WM831X_POWER_STATE:
	हाल WM831X_WATCHDOG:
	हाल WM831X_ON_PIN_CONTROL:
	हाल WM831X_RESET_CONTROL:
	हाल WM831X_CONTROL_INTERFACE:
	हाल WM831X_SECURITY_KEY:
	हाल WM831X_SOFTWARE_SCRATCH:
	हाल WM831X_OTP_CONTROL:
	हाल WM831X_GPIO_LEVEL:
	हाल WM831X_SYSTEM_STATUS:
	हाल WM831X_ON_SOURCE:
	हाल WM831X_OFF_SOURCE:
	हाल WM831X_SYSTEM_INTERRUPTS:
	हाल WM831X_INTERRUPT_STATUS_1:
	हाल WM831X_INTERRUPT_STATUS_2:
	हाल WM831X_INTERRUPT_STATUS_3:
	हाल WM831X_INTERRUPT_STATUS_4:
	हाल WM831X_INTERRUPT_STATUS_5:
	हाल WM831X_IRQ_CONFIG:
	हाल WM831X_SYSTEM_INTERRUPTS_MASK:
	हाल WM831X_INTERRUPT_STATUS_1_MASK:
	हाल WM831X_INTERRUPT_STATUS_2_MASK:
	हाल WM831X_INTERRUPT_STATUS_3_MASK:
	हाल WM831X_INTERRUPT_STATUS_4_MASK:
	हाल WM831X_INTERRUPT_STATUS_5_MASK:
	हाल WM831X_RTC_WRITE_COUNTER:
	हाल WM831X_RTC_TIME_1:
	हाल WM831X_RTC_TIME_2:
	हाल WM831X_RTC_ALARM_1:
	हाल WM831X_RTC_ALARM_2:
	हाल WM831X_RTC_CONTROL:
	हाल WM831X_RTC_TRIM:
	हाल WM831X_TOUCH_CONTROL_1:
	हाल WM831X_TOUCH_CONTROL_2:
	हाल WM831X_TOUCH_DATA_X:
	हाल WM831X_TOUCH_DATA_Y:
	हाल WM831X_TOUCH_DATA_Z:
	हाल WM831X_AUXADC_DATA:
	हाल WM831X_AUXADC_CONTROL:
	हाल WM831X_AUXADC_SOURCE:
	हाल WM831X_COMPARATOR_CONTROL:
	हाल WM831X_COMPARATOR_1:
	हाल WM831X_COMPARATOR_2:
	हाल WM831X_COMPARATOR_3:
	हाल WM831X_COMPARATOR_4:
	हाल WM831X_GPIO1_CONTROL:
	हाल WM831X_GPIO2_CONTROL:
	हाल WM831X_GPIO3_CONTROL:
	हाल WM831X_GPIO4_CONTROL:
	हाल WM831X_GPIO5_CONTROL:
	हाल WM831X_GPIO6_CONTROL:
	हाल WM831X_GPIO7_CONTROL:
	हाल WM831X_GPIO8_CONTROL:
	हाल WM831X_GPIO9_CONTROL:
	हाल WM831X_GPIO10_CONTROL:
	हाल WM831X_GPIO11_CONTROL:
	हाल WM831X_GPIO12_CONTROL:
	हाल WM831X_GPIO13_CONTROL:
	हाल WM831X_GPIO14_CONTROL:
	हाल WM831X_GPIO15_CONTROL:
	हाल WM831X_GPIO16_CONTROL:
	हाल WM831X_CHARGER_CONTROL_1:
	हाल WM831X_CHARGER_CONTROL_2:
	हाल WM831X_CHARGER_STATUS:
	हाल WM831X_BACKUP_CHARGER_CONTROL:
	हाल WM831X_STATUS_LED_1:
	हाल WM831X_STATUS_LED_2:
	हाल WM831X_CURRENT_SINK_1:
	हाल WM831X_CURRENT_SINK_2:
	हाल WM831X_DCDC_ENABLE:
	हाल WM831X_LDO_ENABLE:
	हाल WM831X_DCDC_STATUS:
	हाल WM831X_LDO_STATUS:
	हाल WM831X_DCDC_UV_STATUS:
	हाल WM831X_LDO_UV_STATUS:
	हाल WM831X_DC1_CONTROL_1:
	हाल WM831X_DC1_CONTROL_2:
	हाल WM831X_DC1_ON_CONFIG:
	हाल WM831X_DC1_SLEEP_CONTROL:
	हाल WM831X_DC1_DVS_CONTROL:
	हाल WM831X_DC2_CONTROL_1:
	हाल WM831X_DC2_CONTROL_2:
	हाल WM831X_DC2_ON_CONFIG:
	हाल WM831X_DC2_SLEEP_CONTROL:
	हाल WM831X_DC2_DVS_CONTROL:
	हाल WM831X_DC3_CONTROL_1:
	हाल WM831X_DC3_CONTROL_2:
	हाल WM831X_DC3_ON_CONFIG:
	हाल WM831X_DC3_SLEEP_CONTROL:
	हाल WM831X_DC4_CONTROL:
	हाल WM831X_DC4_SLEEP_CONTROL:
	हाल WM831X_EPE1_CONTROL:
	हाल WM831X_EPE2_CONTROL:
	हाल WM831X_LDO1_CONTROL:
	हाल WM831X_LDO1_ON_CONTROL:
	हाल WM831X_LDO1_SLEEP_CONTROL:
	हाल WM831X_LDO2_CONTROL:
	हाल WM831X_LDO2_ON_CONTROL:
	हाल WM831X_LDO2_SLEEP_CONTROL:
	हाल WM831X_LDO3_CONTROL:
	हाल WM831X_LDO3_ON_CONTROL:
	हाल WM831X_LDO3_SLEEP_CONTROL:
	हाल WM831X_LDO4_CONTROL:
	हाल WM831X_LDO4_ON_CONTROL:
	हाल WM831X_LDO4_SLEEP_CONTROL:
	हाल WM831X_LDO5_CONTROL:
	हाल WM831X_LDO5_ON_CONTROL:
	हाल WM831X_LDO5_SLEEP_CONTROL:
	हाल WM831X_LDO6_CONTROL:
	हाल WM831X_LDO6_ON_CONTROL:
	हाल WM831X_LDO6_SLEEP_CONTROL:
	हाल WM831X_LDO7_CONTROL:
	हाल WM831X_LDO7_ON_CONTROL:
	हाल WM831X_LDO7_SLEEP_CONTROL:
	हाल WM831X_LDO8_CONTROL:
	हाल WM831X_LDO8_ON_CONTROL:
	हाल WM831X_LDO8_SLEEP_CONTROL:
	हाल WM831X_LDO9_CONTROL:
	हाल WM831X_LDO9_ON_CONTROL:
	हाल WM831X_LDO9_SLEEP_CONTROL:
	हाल WM831X_LDO10_CONTROL:
	हाल WM831X_LDO10_ON_CONTROL:
	हाल WM831X_LDO10_SLEEP_CONTROL:
	हाल WM831X_LDO11_ON_CONTROL:
	हाल WM831X_LDO11_SLEEP_CONTROL:
	हाल WM831X_POWER_GOOD_SOURCE_1:
	हाल WM831X_POWER_GOOD_SOURCE_2:
	हाल WM831X_CLOCK_CONTROL_1:
	हाल WM831X_CLOCK_CONTROL_2:
	हाल WM831X_FLL_CONTROL_1:
	हाल WM831X_FLL_CONTROL_2:
	हाल WM831X_FLL_CONTROL_3:
	हाल WM831X_FLL_CONTROL_4:
	हाल WM831X_FLL_CONTROL_5:
	हाल WM831X_UNIQUE_ID_1:
	हाल WM831X_UNIQUE_ID_2:
	हाल WM831X_UNIQUE_ID_3:
	हाल WM831X_UNIQUE_ID_4:
	हाल WM831X_UNIQUE_ID_5:
	हाल WM831X_UNIQUE_ID_6:
	हाल WM831X_UNIQUE_ID_7:
	हाल WM831X_UNIQUE_ID_8:
	हाल WM831X_FACTORY_OTP_ID:
	हाल WM831X_FACTORY_OTP_1:
	हाल WM831X_FACTORY_OTP_2:
	हाल WM831X_FACTORY_OTP_3:
	हाल WM831X_FACTORY_OTP_4:
	हाल WM831X_FACTORY_OTP_5:
	हाल WM831X_CUSTOMER_OTP_ID:
	हाल WM831X_DC1_OTP_CONTROL:
	हाल WM831X_DC2_OTP_CONTROL:
	हाल WM831X_DC3_OTP_CONTROL:
	हाल WM831X_LDO1_2_OTP_CONTROL:
	हाल WM831X_LDO3_4_OTP_CONTROL:
	हाल WM831X_LDO5_6_OTP_CONTROL:
	हाल WM831X_LDO7_8_OTP_CONTROL:
	हाल WM831X_LDO9_10_OTP_CONTROL:
	हाल WM831X_LDO11_EPE_CONTROL:
	हाल WM831X_GPIO1_OTP_CONTROL:
	हाल WM831X_GPIO2_OTP_CONTROL:
	हाल WM831X_GPIO3_OTP_CONTROL:
	हाल WM831X_GPIO4_OTP_CONTROL:
	हाल WM831X_GPIO5_OTP_CONTROL:
	हाल WM831X_GPIO6_OTP_CONTROL:
	हाल WM831X_DBE_CHECK_DATA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm831x_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(dev);

	अगर (wm831x_reg_locked(wm831x, reg))
		वापस false;

	चयन (reg) अणु
	हाल WM831X_SYSVDD_CONTROL:
	हाल WM831X_THERMAL_MONITORING:
	हाल WM831X_POWER_STATE:
	हाल WM831X_WATCHDOG:
	हाल WM831X_ON_PIN_CONTROL:
	हाल WM831X_RESET_CONTROL:
	हाल WM831X_CONTROL_INTERFACE:
	हाल WM831X_SECURITY_KEY:
	हाल WM831X_SOFTWARE_SCRATCH:
	हाल WM831X_OTP_CONTROL:
	हाल WM831X_GPIO_LEVEL:
	हाल WM831X_INTERRUPT_STATUS_1:
	हाल WM831X_INTERRUPT_STATUS_2:
	हाल WM831X_INTERRUPT_STATUS_3:
	हाल WM831X_INTERRUPT_STATUS_4:
	हाल WM831X_INTERRUPT_STATUS_5:
	हाल WM831X_IRQ_CONFIG:
	हाल WM831X_SYSTEM_INTERRUPTS_MASK:
	हाल WM831X_INTERRUPT_STATUS_1_MASK:
	हाल WM831X_INTERRUPT_STATUS_2_MASK:
	हाल WM831X_INTERRUPT_STATUS_3_MASK:
	हाल WM831X_INTERRUPT_STATUS_4_MASK:
	हाल WM831X_INTERRUPT_STATUS_5_MASK:
	हाल WM831X_RTC_TIME_1:
	हाल WM831X_RTC_TIME_2:
	हाल WM831X_RTC_ALARM_1:
	हाल WM831X_RTC_ALARM_2:
	हाल WM831X_RTC_CONTROL:
	हाल WM831X_RTC_TRIM:
	हाल WM831X_TOUCH_CONTROL_1:
	हाल WM831X_TOUCH_CONTROL_2:
	हाल WM831X_AUXADC_CONTROL:
	हाल WM831X_AUXADC_SOURCE:
	हाल WM831X_COMPARATOR_CONTROL:
	हाल WM831X_COMPARATOR_1:
	हाल WM831X_COMPARATOR_2:
	हाल WM831X_COMPARATOR_3:
	हाल WM831X_COMPARATOR_4:
	हाल WM831X_GPIO1_CONTROL:
	हाल WM831X_GPIO2_CONTROL:
	हाल WM831X_GPIO3_CONTROL:
	हाल WM831X_GPIO4_CONTROL:
	हाल WM831X_GPIO5_CONTROL:
	हाल WM831X_GPIO6_CONTROL:
	हाल WM831X_GPIO7_CONTROL:
	हाल WM831X_GPIO8_CONTROL:
	हाल WM831X_GPIO9_CONTROL:
	हाल WM831X_GPIO10_CONTROL:
	हाल WM831X_GPIO11_CONTROL:
	हाल WM831X_GPIO12_CONTROL:
	हाल WM831X_GPIO13_CONTROL:
	हाल WM831X_GPIO14_CONTROL:
	हाल WM831X_GPIO15_CONTROL:
	हाल WM831X_GPIO16_CONTROL:
	हाल WM831X_CHARGER_CONTROL_1:
	हाल WM831X_CHARGER_CONTROL_2:
	हाल WM831X_CHARGER_STATUS:
	हाल WM831X_BACKUP_CHARGER_CONTROL:
	हाल WM831X_STATUS_LED_1:
	हाल WM831X_STATUS_LED_2:
	हाल WM831X_CURRENT_SINK_1:
	हाल WM831X_CURRENT_SINK_2:
	हाल WM831X_DCDC_ENABLE:
	हाल WM831X_LDO_ENABLE:
	हाल WM831X_DC1_CONTROL_1:
	हाल WM831X_DC1_CONTROL_2:
	हाल WM831X_DC1_ON_CONFIG:
	हाल WM831X_DC1_SLEEP_CONTROL:
	हाल WM831X_DC1_DVS_CONTROL:
	हाल WM831X_DC2_CONTROL_1:
	हाल WM831X_DC2_CONTROL_2:
	हाल WM831X_DC2_ON_CONFIG:
	हाल WM831X_DC2_SLEEP_CONTROL:
	हाल WM831X_DC2_DVS_CONTROL:
	हाल WM831X_DC3_CONTROL_1:
	हाल WM831X_DC3_CONTROL_2:
	हाल WM831X_DC3_ON_CONFIG:
	हाल WM831X_DC3_SLEEP_CONTROL:
	हाल WM831X_DC4_CONTROL:
	हाल WM831X_DC4_SLEEP_CONTROL:
	हाल WM831X_EPE1_CONTROL:
	हाल WM831X_EPE2_CONTROL:
	हाल WM831X_LDO1_CONTROL:
	हाल WM831X_LDO1_ON_CONTROL:
	हाल WM831X_LDO1_SLEEP_CONTROL:
	हाल WM831X_LDO2_CONTROL:
	हाल WM831X_LDO2_ON_CONTROL:
	हाल WM831X_LDO2_SLEEP_CONTROL:
	हाल WM831X_LDO3_CONTROL:
	हाल WM831X_LDO3_ON_CONTROL:
	हाल WM831X_LDO3_SLEEP_CONTROL:
	हाल WM831X_LDO4_CONTROL:
	हाल WM831X_LDO4_ON_CONTROL:
	हाल WM831X_LDO4_SLEEP_CONTROL:
	हाल WM831X_LDO5_CONTROL:
	हाल WM831X_LDO5_ON_CONTROL:
	हाल WM831X_LDO5_SLEEP_CONTROL:
	हाल WM831X_LDO6_CONTROL:
	हाल WM831X_LDO6_ON_CONTROL:
	हाल WM831X_LDO6_SLEEP_CONTROL:
	हाल WM831X_LDO7_CONTROL:
	हाल WM831X_LDO7_ON_CONTROL:
	हाल WM831X_LDO7_SLEEP_CONTROL:
	हाल WM831X_LDO8_CONTROL:
	हाल WM831X_LDO8_ON_CONTROL:
	हाल WM831X_LDO8_SLEEP_CONTROL:
	हाल WM831X_LDO9_CONTROL:
	हाल WM831X_LDO9_ON_CONTROL:
	हाल WM831X_LDO9_SLEEP_CONTROL:
	हाल WM831X_LDO10_CONTROL:
	हाल WM831X_LDO10_ON_CONTROL:
	हाल WM831X_LDO10_SLEEP_CONTROL:
	हाल WM831X_LDO11_ON_CONTROL:
	हाल WM831X_LDO11_SLEEP_CONTROL:
	हाल WM831X_POWER_GOOD_SOURCE_1:
	हाल WM831X_POWER_GOOD_SOURCE_2:
	हाल WM831X_CLOCK_CONTROL_1:
	हाल WM831X_CLOCK_CONTROL_2:
	हाल WM831X_FLL_CONTROL_1:
	हाल WM831X_FLL_CONTROL_2:
	हाल WM831X_FLL_CONTROL_3:
	हाल WM831X_FLL_CONTROL_4:
	हाल WM831X_FLL_CONTROL_5:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm831x_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM831X_SYSTEM_STATUS:
	हाल WM831X_ON_SOURCE:
	हाल WM831X_OFF_SOURCE:
	हाल WM831X_GPIO_LEVEL:
	हाल WM831X_SYSTEM_INTERRUPTS:
	हाल WM831X_INTERRUPT_STATUS_1:
	हाल WM831X_INTERRUPT_STATUS_2:
	हाल WM831X_INTERRUPT_STATUS_3:
	हाल WM831X_INTERRUPT_STATUS_4:
	हाल WM831X_INTERRUPT_STATUS_5:
	हाल WM831X_RTC_TIME_1:
	हाल WM831X_RTC_TIME_2:
	हाल WM831X_TOUCH_DATA_X:
	हाल WM831X_TOUCH_DATA_Y:
	हाल WM831X_TOUCH_DATA_Z:
	हाल WM831X_AUXADC_DATA:
	हाल WM831X_CHARGER_STATUS:
	हाल WM831X_DCDC_STATUS:
	हाल WM831X_LDO_STATUS:
	हाल WM831X_DCDC_UV_STATUS:
	हाल WM831X_LDO_UV_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * wm831x_reg_पढ़ो: Read a single WM831x रेजिस्टर.
 *
 * @wm831x: Device to पढ़ो from.
 * @reg: Register to पढ़ो.
 */
पूर्णांक wm831x_reg_पढ़ो(काष्ठा wm831x *wm831x, अचिन्हित लघु reg)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wm831x->regmap, reg, &val);

	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(wm831x_reg_पढ़ो);

/**
 * wm831x_bulk_पढ़ो: Read multiple WM831x रेजिस्टरs
 *
 * @wm831x: Device to पढ़ो from
 * @reg: First रेजिस्टर
 * @count: Number of रेजिस्टरs
 * @buf: Buffer to fill.
 */
पूर्णांक wm831x_bulk_पढ़ो(काष्ठा wm831x *wm831x, अचिन्हित लघु reg,
		     पूर्णांक count, u16 *buf)
अणु
	वापस regmap_bulk_पढ़ो(wm831x->regmap, reg, buf, count);
पूर्ण
EXPORT_SYMBOL_GPL(wm831x_bulk_पढ़ो);

अटल पूर्णांक wm831x_ग_लिखो(काष्ठा wm831x *wm831x, अचिन्हित लघु reg,
			पूर्णांक bytes, व्योम *src)
अणु
	u16 *buf = src;
	पूर्णांक i, ret;

	BUG_ON(bytes % 2);
	BUG_ON(bytes <= 0);

	क्रम (i = 0; i < bytes / 2; i++) अणु
		अगर (wm831x_reg_locked(wm831x, reg))
			वापस -EPERM;

		dev_vdbg(wm831x->dev, "Write %04x to R%d(0x%x)\n",
			 buf[i], reg + i, reg + i);
		ret = regmap_ग_लिखो(wm831x->regmap, reg + i, buf[i]);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wm831x_reg_ग_लिखो: Write a single WM831x रेजिस्टर.
 *
 * @wm831x: Device to ग_लिखो to.
 * @reg: Register to ग_लिखो to.
 * @val: Value to ग_लिखो.
 */
पूर्णांक wm831x_reg_ग_लिखो(काष्ठा wm831x *wm831x, अचिन्हित लघु reg,
		     अचिन्हित लघु val)
अणु
	पूर्णांक ret;

	mutex_lock(&wm831x->io_lock);

	ret = wm831x_ग_लिखो(wm831x, reg, 2, &val);

	mutex_unlock(&wm831x->io_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm831x_reg_ग_लिखो);

/**
 * wm831x_set_bits: Set the value of a bitfield in a WM831x रेजिस्टर
 *
 * @wm831x: Device to ग_लिखो to.
 * @reg: Register to ग_लिखो to.
 * @mask: Mask of bits to set.
 * @val: Value to set (unshअगरted)
 */
पूर्णांक wm831x_set_bits(काष्ठा wm831x *wm831x, अचिन्हित लघु reg,
		    अचिन्हित लघु mask, अचिन्हित लघु val)
अणु
	पूर्णांक ret;

	mutex_lock(&wm831x->io_lock);

	अगर (!wm831x_reg_locked(wm831x, reg))
		ret = regmap_update_bits(wm831x->regmap, reg, mask, val);
	अन्यथा
		ret = -EPERM;

	mutex_unlock(&wm831x->io_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm831x_set_bits);

अटल स्थिर काष्ठा resource wm831x_dcdc1_resources[] = अणु
	अणु
		.start = WM831X_DC1_CONTROL_1,
		.end   = WM831X_DC1_DVS_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_DC1,
		.end   = WM831X_IRQ_UV_DC1,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name  = "HC",
		.start = WM831X_IRQ_HC_DC1,
		.end   = WM831X_IRQ_HC_DC1,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा resource wm831x_dcdc2_resources[] = अणु
	अणु
		.start = WM831X_DC2_CONTROL_1,
		.end   = WM831X_DC2_DVS_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_DC2,
		.end   = WM831X_IRQ_UV_DC2,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name  = "HC",
		.start = WM831X_IRQ_HC_DC2,
		.end   = WM831X_IRQ_HC_DC2,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_dcdc3_resources[] = अणु
	अणु
		.start = WM831X_DC3_CONTROL_1,
		.end   = WM831X_DC3_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_DC3,
		.end   = WM831X_IRQ_UV_DC3,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_dcdc4_resources[] = अणु
	अणु
		.start = WM831X_DC4_CONTROL,
		.end   = WM831X_DC4_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_DC4,
		.end   = WM831X_IRQ_UV_DC4,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm8320_dcdc4_buck_resources[] = अणु
	अणु
		.start = WM831X_DC4_CONTROL,
		.end   = WM832X_DC4_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_DC4,
		.end   = WM831X_IRQ_UV_DC4,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_gpio_resources[] = अणु
	अणु
		.start = WM831X_IRQ_GPIO_1,
		.end   = WM831X_IRQ_GPIO_16,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_isink1_resources[] = अणु
	अणु
		.start = WM831X_CURRENT_SINK_1,
		.end   = WM831X_CURRENT_SINK_1,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.start = WM831X_IRQ_CS1,
		.end   = WM831X_IRQ_CS1,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_isink2_resources[] = अणु
	अणु
		.start = WM831X_CURRENT_SINK_2,
		.end   = WM831X_CURRENT_SINK_2,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.start = WM831X_IRQ_CS2,
		.end   = WM831X_IRQ_CS2,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो1_resources[] = अणु
	अणु
		.start = WM831X_LDO1_CONTROL,
		.end   = WM831X_LDO1_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO1,
		.end   = WM831X_IRQ_UV_LDO1,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो2_resources[] = अणु
	अणु
		.start = WM831X_LDO2_CONTROL,
		.end   = WM831X_LDO2_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO2,
		.end   = WM831X_IRQ_UV_LDO2,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो3_resources[] = अणु
	अणु
		.start = WM831X_LDO3_CONTROL,
		.end   = WM831X_LDO3_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO3,
		.end   = WM831X_IRQ_UV_LDO3,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो4_resources[] = अणु
	अणु
		.start = WM831X_LDO4_CONTROL,
		.end   = WM831X_LDO4_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO4,
		.end   = WM831X_IRQ_UV_LDO4,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो5_resources[] = अणु
	अणु
		.start = WM831X_LDO5_CONTROL,
		.end   = WM831X_LDO5_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO5,
		.end   = WM831X_IRQ_UV_LDO5,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो6_resources[] = अणु
	अणु
		.start = WM831X_LDO6_CONTROL,
		.end   = WM831X_LDO6_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO6,
		.end   = WM831X_IRQ_UV_LDO6,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो7_resources[] = अणु
	अणु
		.start = WM831X_LDO7_CONTROL,
		.end   = WM831X_LDO7_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO7,
		.end   = WM831X_IRQ_UV_LDO7,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो8_resources[] = अणु
	अणु
		.start = WM831X_LDO8_CONTROL,
		.end   = WM831X_LDO8_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO8,
		.end   = WM831X_IRQ_UV_LDO8,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो9_resources[] = अणु
	अणु
		.start = WM831X_LDO9_CONTROL,
		.end   = WM831X_LDO9_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO9,
		.end   = WM831X_IRQ_UV_LDO9,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो10_resources[] = अणु
	अणु
		.start = WM831X_LDO10_CONTROL,
		.end   = WM831X_LDO10_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
	अणु
		.name  = "UV",
		.start = WM831X_IRQ_UV_LDO10,
		.end   = WM831X_IRQ_UV_LDO10,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_lकरो11_resources[] = अणु
	अणु
		.start = WM831X_LDO11_ON_CONTROL,
		.end   = WM831X_LDO11_SLEEP_CONTROL,
		.flags = IORESOURCE_REG,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_on_resources[] = अणु
	अणु
		.start = WM831X_IRQ_ON,
		.end   = WM831X_IRQ_ON,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा resource wm831x_घातer_resources[] = अणु
	अणु
		.name = "SYSLO",
		.start = WM831X_IRQ_PPM_SYSLO,
		.end   = WM831X_IRQ_PPM_SYSLO,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "PWR SRC",
		.start = WM831X_IRQ_PPM_PWR_SRC,
		.end   = WM831X_IRQ_PPM_PWR_SRC,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "USB CURR",
		.start = WM831X_IRQ_PPM_USB_CURR,
		.end   = WM831X_IRQ_PPM_USB_CURR,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "BATT HOT",
		.start = WM831X_IRQ_CHG_BATT_HOT,
		.end   = WM831X_IRQ_CHG_BATT_HOT,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "BATT COLD",
		.start = WM831X_IRQ_CHG_BATT_COLD,
		.end   = WM831X_IRQ_CHG_BATT_COLD,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "BATT FAIL",
		.start = WM831X_IRQ_CHG_BATT_FAIL,
		.end   = WM831X_IRQ_CHG_BATT_FAIL,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "OV",
		.start = WM831X_IRQ_CHG_OV,
		.end   = WM831X_IRQ_CHG_OV,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "END",
		.start = WM831X_IRQ_CHG_END,
		.end   = WM831X_IRQ_CHG_END,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "TO",
		.start = WM831X_IRQ_CHG_TO,
		.end   = WM831X_IRQ_CHG_TO,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "MODE",
		.start = WM831X_IRQ_CHG_MODE,
		.end   = WM831X_IRQ_CHG_MODE,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "START",
		.start = WM831X_IRQ_CHG_START,
		.end   = WM831X_IRQ_CHG_START,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_rtc_resources[] = अणु
	अणु
		.name = "PER",
		.start = WM831X_IRQ_RTC_PER,
		.end   = WM831X_IRQ_RTC_PER,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "ALM",
		.start = WM831X_IRQ_RTC_ALM,
		.end   = WM831X_IRQ_RTC_ALM,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_status1_resources[] = अणु
	अणु
		.start = WM831X_STATUS_LED_1,
		.end   = WM831X_STATUS_LED_1,
		.flags = IORESOURCE_REG,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_status2_resources[] = अणु
	अणु
		.start = WM831X_STATUS_LED_2,
		.end   = WM831X_STATUS_LED_2,
		.flags = IORESOURCE_REG,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_touch_resources[] = अणु
	अणु
		.name = "TCHPD",
		.start = WM831X_IRQ_TCHPD,
		.end   = WM831X_IRQ_TCHPD,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "TCHDATA",
		.start = WM831X_IRQ_TCHDATA,
		.end   = WM831X_IRQ_TCHDATA,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource wm831x_wdt_resources[] = अणु
	अणु
		.start = WM831X_IRQ_WDOG_TO,
		.end   = WM831X_IRQ_WDOG_TO,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm8310_devs[] = अणु
	अणु
		.name = "wm831x-backup",
	पूर्ण,
	अणु
		.name = "wm831x-buckv",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_dcdc1_resources),
		.resources = wm831x_dcdc1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckv",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_dcdc2_resources),
		.resources = wm831x_dcdc2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckp",
		.id = 3,
		.num_resources = ARRAY_SIZE(wm831x_dcdc3_resources),
		.resources = wm831x_dcdc3_resources,
	पूर्ण,
	अणु
		.name = "wm831x-boostp",
		.id = 4,
		.num_resources = ARRAY_SIZE(wm831x_dcdc4_resources),
		.resources = wm831x_dcdc4_resources,
	पूर्ण,
	अणु
		.name = "wm831x-clk",
	पूर्ण,
	अणु
		.name = "wm831x-epe",
		.id = 1,
	पूर्ण,
	अणु
		.name = "wm831x-epe",
		.id = 2,
	पूर्ण,
	अणु
		.name = "wm831x-gpio",
		.num_resources = ARRAY_SIZE(wm831x_gpio_resources),
		.resources = wm831x_gpio_resources,
	पूर्ण,
	अणु
		.name = "wm831x-hwmon",
	पूर्ण,
	अणु
		.name = "wm831x-isink",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_isink1_resources),
		.resources = wm831x_isink1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-isink",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_isink2_resources),
		.resources = wm831x_isink2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_lकरो1_resources),
		.resources = wm831x_lकरो1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_lकरो2_resources),
		.resources = wm831x_lकरो2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 3,
		.num_resources = ARRAY_SIZE(wm831x_lकरो3_resources),
		.resources = wm831x_lकरो3_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 4,
		.num_resources = ARRAY_SIZE(wm831x_lकरो4_resources),
		.resources = wm831x_lकरो4_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 5,
		.num_resources = ARRAY_SIZE(wm831x_lकरो5_resources),
		.resources = wm831x_lकरो5_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 6,
		.num_resources = ARRAY_SIZE(wm831x_lकरो6_resources),
		.resources = wm831x_lकरो6_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 7,
		.num_resources = ARRAY_SIZE(wm831x_lकरो7_resources),
		.resources = wm831x_lकरो7_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 8,
		.num_resources = ARRAY_SIZE(wm831x_lकरो8_resources),
		.resources = wm831x_lकरो8_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 9,
		.num_resources = ARRAY_SIZE(wm831x_lकरो9_resources),
		.resources = wm831x_lकरो9_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 10,
		.num_resources = ARRAY_SIZE(wm831x_lकरो10_resources),
		.resources = wm831x_lकरो10_resources,
	पूर्ण,
	अणु
		.name = "wm831x-alive-ldo",
		.id = 11,
		.num_resources = ARRAY_SIZE(wm831x_lकरो11_resources),
		.resources = wm831x_lकरो11_resources,
	पूर्ण,
	अणु
		.name = "wm831x-on",
		.num_resources = ARRAY_SIZE(wm831x_on_resources),
		.resources = wm831x_on_resources,
	पूर्ण,
	अणु
		.name = "wm831x-power",
		.num_resources = ARRAY_SIZE(wm831x_घातer_resources),
		.resources = wm831x_घातer_resources,
	पूर्ण,
	अणु
		.name = "wm831x-status",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_status1_resources),
		.resources = wm831x_status1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-status",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_status2_resources),
		.resources = wm831x_status2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-watchdog",
		.num_resources = ARRAY_SIZE(wm831x_wdt_resources),
		.resources = wm831x_wdt_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm8311_devs[] = अणु
	अणु
		.name = "wm831x-backup",
	पूर्ण,
	अणु
		.name = "wm831x-buckv",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_dcdc1_resources),
		.resources = wm831x_dcdc1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckv",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_dcdc2_resources),
		.resources = wm831x_dcdc2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckp",
		.id = 3,
		.num_resources = ARRAY_SIZE(wm831x_dcdc3_resources),
		.resources = wm831x_dcdc3_resources,
	पूर्ण,
	अणु
		.name = "wm831x-boostp",
		.id = 4,
		.num_resources = ARRAY_SIZE(wm831x_dcdc4_resources),
		.resources = wm831x_dcdc4_resources,
	पूर्ण,
	अणु
		.name = "wm831x-clk",
	पूर्ण,
	अणु
		.name = "wm831x-epe",
		.id = 1,
	पूर्ण,
	अणु
		.name = "wm831x-epe",
		.id = 2,
	पूर्ण,
	अणु
		.name = "wm831x-gpio",
		.num_resources = ARRAY_SIZE(wm831x_gpio_resources),
		.resources = wm831x_gpio_resources,
	पूर्ण,
	अणु
		.name = "wm831x-hwmon",
	पूर्ण,
	अणु
		.name = "wm831x-isink",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_isink1_resources),
		.resources = wm831x_isink1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-isink",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_isink2_resources),
		.resources = wm831x_isink2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_lकरो1_resources),
		.resources = wm831x_lकरो1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_lकरो2_resources),
		.resources = wm831x_lकरो2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 3,
		.num_resources = ARRAY_SIZE(wm831x_lकरो3_resources),
		.resources = wm831x_lकरो3_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 4,
		.num_resources = ARRAY_SIZE(wm831x_lकरो4_resources),
		.resources = wm831x_lकरो4_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 5,
		.num_resources = ARRAY_SIZE(wm831x_lकरो5_resources),
		.resources = wm831x_lकरो5_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 7,
		.num_resources = ARRAY_SIZE(wm831x_lकरो7_resources),
		.resources = wm831x_lकरो7_resources,
	पूर्ण,
	अणु
		.name = "wm831x-alive-ldo",
		.id = 11,
		.num_resources = ARRAY_SIZE(wm831x_lकरो11_resources),
		.resources = wm831x_lकरो11_resources,
	पूर्ण,
	अणु
		.name = "wm831x-on",
		.num_resources = ARRAY_SIZE(wm831x_on_resources),
		.resources = wm831x_on_resources,
	पूर्ण,
	अणु
		.name = "wm831x-power",
		.num_resources = ARRAY_SIZE(wm831x_घातer_resources),
		.resources = wm831x_घातer_resources,
	पूर्ण,
	अणु
		.name = "wm831x-status",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_status1_resources),
		.resources = wm831x_status1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-status",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_status2_resources),
		.resources = wm831x_status2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-watchdog",
		.num_resources = ARRAY_SIZE(wm831x_wdt_resources),
		.resources = wm831x_wdt_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm8312_devs[] = अणु
	अणु
		.name = "wm831x-backup",
	पूर्ण,
	अणु
		.name = "wm831x-buckv",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_dcdc1_resources),
		.resources = wm831x_dcdc1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckv",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_dcdc2_resources),
		.resources = wm831x_dcdc2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckp",
		.id = 3,
		.num_resources = ARRAY_SIZE(wm831x_dcdc3_resources),
		.resources = wm831x_dcdc3_resources,
	पूर्ण,
	अणु
		.name = "wm831x-boostp",
		.id = 4,
		.num_resources = ARRAY_SIZE(wm831x_dcdc4_resources),
		.resources = wm831x_dcdc4_resources,
	पूर्ण,
	अणु
		.name = "wm831x-clk",
	पूर्ण,
	अणु
		.name = "wm831x-epe",
		.id = 1,
	पूर्ण,
	अणु
		.name = "wm831x-epe",
		.id = 2,
	पूर्ण,
	अणु
		.name = "wm831x-gpio",
		.num_resources = ARRAY_SIZE(wm831x_gpio_resources),
		.resources = wm831x_gpio_resources,
	पूर्ण,
	अणु
		.name = "wm831x-hwmon",
	पूर्ण,
	अणु
		.name = "wm831x-isink",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_isink1_resources),
		.resources = wm831x_isink1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-isink",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_isink2_resources),
		.resources = wm831x_isink2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_lकरो1_resources),
		.resources = wm831x_lकरो1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_lकरो2_resources),
		.resources = wm831x_lकरो2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 3,
		.num_resources = ARRAY_SIZE(wm831x_lकरो3_resources),
		.resources = wm831x_lकरो3_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 4,
		.num_resources = ARRAY_SIZE(wm831x_lकरो4_resources),
		.resources = wm831x_lकरो4_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 5,
		.num_resources = ARRAY_SIZE(wm831x_lकरो5_resources),
		.resources = wm831x_lकरो5_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 6,
		.num_resources = ARRAY_SIZE(wm831x_lकरो6_resources),
		.resources = wm831x_lकरो6_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 7,
		.num_resources = ARRAY_SIZE(wm831x_lकरो7_resources),
		.resources = wm831x_lकरो7_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 8,
		.num_resources = ARRAY_SIZE(wm831x_lकरो8_resources),
		.resources = wm831x_lकरो8_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 9,
		.num_resources = ARRAY_SIZE(wm831x_lकरो9_resources),
		.resources = wm831x_lकरो9_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 10,
		.num_resources = ARRAY_SIZE(wm831x_lकरो10_resources),
		.resources = wm831x_lकरो10_resources,
	पूर्ण,
	अणु
		.name = "wm831x-alive-ldo",
		.id = 11,
		.num_resources = ARRAY_SIZE(wm831x_lकरो11_resources),
		.resources = wm831x_lकरो11_resources,
	पूर्ण,
	अणु
		.name = "wm831x-on",
		.num_resources = ARRAY_SIZE(wm831x_on_resources),
		.resources = wm831x_on_resources,
	पूर्ण,
	अणु
		.name = "wm831x-power",
		.num_resources = ARRAY_SIZE(wm831x_घातer_resources),
		.resources = wm831x_घातer_resources,
	पूर्ण,
	अणु
		.name = "wm831x-status",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_status1_resources),
		.resources = wm831x_status1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-status",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_status2_resources),
		.resources = wm831x_status2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-watchdog",
		.num_resources = ARRAY_SIZE(wm831x_wdt_resources),
		.resources = wm831x_wdt_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell wm8320_devs[] = अणु
	अणु
		.name = "wm831x-backup",
	पूर्ण,
	अणु
		.name = "wm831x-buckv",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_dcdc1_resources),
		.resources = wm831x_dcdc1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckv",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_dcdc2_resources),
		.resources = wm831x_dcdc2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckp",
		.id = 3,
		.num_resources = ARRAY_SIZE(wm831x_dcdc3_resources),
		.resources = wm831x_dcdc3_resources,
	पूर्ण,
	अणु
		.name = "wm831x-buckp",
		.id = 4,
		.num_resources = ARRAY_SIZE(wm8320_dcdc4_buck_resources),
		.resources = wm8320_dcdc4_buck_resources,
	पूर्ण,
	अणु
		.name = "wm831x-clk",
	पूर्ण,
	अणु
		.name = "wm831x-gpio",
		.num_resources = ARRAY_SIZE(wm831x_gpio_resources),
		.resources = wm831x_gpio_resources,
	पूर्ण,
	अणु
		.name = "wm831x-hwmon",
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_lकरो1_resources),
		.resources = wm831x_lकरो1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_lकरो2_resources),
		.resources = wm831x_lकरो2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 3,
		.num_resources = ARRAY_SIZE(wm831x_lकरो3_resources),
		.resources = wm831x_lकरो3_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 4,
		.num_resources = ARRAY_SIZE(wm831x_lकरो4_resources),
		.resources = wm831x_lकरो4_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 5,
		.num_resources = ARRAY_SIZE(wm831x_lकरो5_resources),
		.resources = wm831x_lकरो5_resources,
	पूर्ण,
	अणु
		.name = "wm831x-ldo",
		.id = 6,
		.num_resources = ARRAY_SIZE(wm831x_lकरो6_resources),
		.resources = wm831x_lकरो6_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 7,
		.num_resources = ARRAY_SIZE(wm831x_lकरो7_resources),
		.resources = wm831x_lकरो7_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 8,
		.num_resources = ARRAY_SIZE(wm831x_lकरो8_resources),
		.resources = wm831x_lकरो8_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 9,
		.num_resources = ARRAY_SIZE(wm831x_lकरो9_resources),
		.resources = wm831x_lकरो9_resources,
	पूर्ण,
	अणु
		.name = "wm831x-aldo",
		.id = 10,
		.num_resources = ARRAY_SIZE(wm831x_lकरो10_resources),
		.resources = wm831x_lकरो10_resources,
	पूर्ण,
	अणु
		.name = "wm831x-alive-ldo",
		.id = 11,
		.num_resources = ARRAY_SIZE(wm831x_lकरो11_resources),
		.resources = wm831x_lकरो11_resources,
	पूर्ण,
	अणु
		.name = "wm831x-on",
		.num_resources = ARRAY_SIZE(wm831x_on_resources),
		.resources = wm831x_on_resources,
	पूर्ण,
	अणु
		.name = "wm831x-status",
		.id = 1,
		.num_resources = ARRAY_SIZE(wm831x_status1_resources),
		.resources = wm831x_status1_resources,
	पूर्ण,
	अणु
		.name = "wm831x-status",
		.id = 2,
		.num_resources = ARRAY_SIZE(wm831x_status2_resources),
		.resources = wm831x_status2_resources,
	पूर्ण,
	अणु
		.name = "wm831x-watchdog",
		.num_resources = ARRAY_SIZE(wm831x_wdt_resources),
		.resources = wm831x_wdt_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell touch_devs[] = अणु
	अणु
		.name = "wm831x-touch",
		.num_resources = ARRAY_SIZE(wm831x_touch_resources),
		.resources = wm831x_touch_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell rtc_devs[] = अणु
	अणु
		.name = "wm831x-rtc",
		.num_resources = ARRAY_SIZE(wm831x_rtc_resources),
		.resources = wm831x_rtc_resources,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell backlight_devs[] = अणु
	अणु
		.name = "wm831x-backlight",
	पूर्ण,
पूर्ण;

काष्ठा regmap_config wm831x_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.cache_type = REGCACHE_RBTREE,

	.max_रेजिस्टर = WM831X_DBE_CHECK_DATA,
	.पढ़ोable_reg = wm831x_reg_पढ़ोable,
	.ग_लिखोable_reg = wm831x_reg_ग_लिखोable,
	.अस्थिर_reg = wm831x_reg_अस्थिर,
पूर्ण;
EXPORT_SYMBOL_GPL(wm831x_regmap_config);

स्थिर काष्ठा of_device_id wm831x_of_match[] = अणु
	अणु .compatible = "wlf,wm8310", .data = (व्योम *)WM8310 पूर्ण,
	अणु .compatible = "wlf,wm8311", .data = (व्योम *)WM8311 पूर्ण,
	अणु .compatible = "wlf,wm8312", .data = (व्योम *)WM8312 पूर्ण,
	अणु .compatible = "wlf,wm8320", .data = (व्योम *)WM8320 पूर्ण,
	अणु .compatible = "wlf,wm8321", .data = (व्योम *)WM8321 पूर्ण,
	अणु .compatible = "wlf,wm8325", .data = (व्योम *)WM8325 पूर्ण,
	अणु .compatible = "wlf,wm8326", .data = (व्योम *)WM8326 पूर्ण,
	अणु पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(wm831x_of_match);

/*
 * Instantiate the generic non-control parts of the device.
 */
पूर्णांक wm831x_device_init(काष्ठा wm831x *wm831x, पूर्णांक irq)
अणु
	काष्ठा wm831x_pdata *pdata = &wm831x->pdata;
	पूर्णांक rev, wm831x_num;
	क्रमागत wm831x_parent parent;
	पूर्णांक ret, i;

	mutex_init(&wm831x->io_lock);
	mutex_init(&wm831x->key_lock);
	dev_set_drvdata(wm831x->dev, wm831x);

	wm831x->soft_shutकरोwn = pdata->soft_shutकरोwn;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_PARENT_ID);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to read parent ID: %d\n", ret);
		जाओ err;
	पूर्ण
	चयन (ret) अणु
	हाल 0x6204:
	हाल 0x6246:
		अवरोध;
	शेष:
		dev_err(wm831x->dev, "Device is not a WM831x: ID %x\n", ret);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_REVISION);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to read revision: %d\n", ret);
		जाओ err;
	पूर्ण
	rev = (ret & WM831X_PARENT_REV_MASK) >> WM831X_PARENT_REV_SHIFT;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_RESET_ID);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to read device ID: %d\n", ret);
		जाओ err;
	पूर्ण

	/* Some engineering samples करो not have the ID set, rely on
	 * the device being रेजिस्टरed correctly.
	 */
	अगर (ret == 0) अणु
		dev_info(wm831x->dev, "Device is an engineering sample\n");
		ret = wm831x->type;
	पूर्ण

	चयन (ret) अणु
	हाल WM8310:
		parent = WM8310;
		wm831x->num_gpio = 16;
		wm831x->अक्षरger_irq_wake = 1;
		अगर (rev > 0) अणु
			wm831x->has_gpio_ena = 1;
			wm831x->has_cs_sts = 1;
		पूर्ण

		dev_info(wm831x->dev, "WM8310 revision %c\n", 'A' + rev);
		अवरोध;

	हाल WM8311:
		parent = WM8311;
		wm831x->num_gpio = 16;
		wm831x->अक्षरger_irq_wake = 1;
		अगर (rev > 0) अणु
			wm831x->has_gpio_ena = 1;
			wm831x->has_cs_sts = 1;
		पूर्ण

		dev_info(wm831x->dev, "WM8311 revision %c\n", 'A' + rev);
		अवरोध;

	हाल WM8312:
		parent = WM8312;
		wm831x->num_gpio = 16;
		wm831x->अक्षरger_irq_wake = 1;
		अगर (rev > 0) अणु
			wm831x->has_gpio_ena = 1;
			wm831x->has_cs_sts = 1;
		पूर्ण

		dev_info(wm831x->dev, "WM8312 revision %c\n", 'A' + rev);
		अवरोध;

	हाल WM8320:
		parent = WM8320;
		wm831x->num_gpio = 12;
		dev_info(wm831x->dev, "WM8320 revision %c\n", 'A' + rev);
		अवरोध;

	हाल WM8321:
		parent = WM8321;
		wm831x->num_gpio = 12;
		dev_info(wm831x->dev, "WM8321 revision %c\n", 'A' + rev);
		अवरोध;

	हाल WM8325:
		parent = WM8325;
		wm831x->num_gpio = 12;
		dev_info(wm831x->dev, "WM8325 revision %c\n", 'A' + rev);
		अवरोध;

	हाल WM8326:
		parent = WM8326;
		wm831x->num_gpio = 12;
		dev_info(wm831x->dev, "WM8326 revision %c\n", 'A' + rev);
		अवरोध;

	शेष:
		dev_err(wm831x->dev, "Unknown WM831x device %04x\n", ret);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* This will need revisiting in future but is OK क्रम all
	 * current parts.
	 */
	अगर (parent != wm831x->type)
		dev_warn(wm831x->dev, "Device was registered as a WM%x\n",
			 wm831x->type);

	/* Bootstrap the user key */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_SECURITY_KEY);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to read security key: %d\n", ret);
		जाओ err;
	पूर्ण
	अगर (ret != 0) अणु
		dev_warn(wm831x->dev, "Security key had non-zero value %x\n",
			 ret);
		wm831x_reg_ग_लिखो(wm831x, WM831X_SECURITY_KEY, 0);
	पूर्ण
	wm831x->locked = 1;

	अगर (pdata->pre_init) अणु
		ret = pdata->pre_init(wm831x);
		अगर (ret != 0) अणु
			dev_err(wm831x->dev, "pre_init() failed: %d\n", ret);
			जाओ err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pdata->gpio_शेषs); i++) अणु
		अगर (!pdata->gpio_शेषs[i])
			जारी;

		wm831x_reg_ग_लिखो(wm831x,
				 WM831X_GPIO1_CONTROL + i,
				 pdata->gpio_शेषs[i] & 0xffff);
	पूर्ण

	/* Multiply by 10 as we have many subdevices of the same type */
	अगर (pdata->wm831x_num)
		wm831x_num = pdata->wm831x_num * 10;
	अन्यथा
		wm831x_num = -1;

	ret = wm831x_irq_init(wm831x, irq);
	अगर (ret != 0)
		जाओ err;

	wm831x_auxadc_init(wm831x);

	/* The core device is up, instantiate the subdevices. */
	चयन (parent) अणु
	हाल WM8310:
		ret = mfd_add_devices(wm831x->dev, wm831x_num,
				      wm8310_devs, ARRAY_SIZE(wm8310_devs),
				      शून्य, 0, शून्य);
		अवरोध;

	हाल WM8311:
		ret = mfd_add_devices(wm831x->dev, wm831x_num,
				      wm8311_devs, ARRAY_SIZE(wm8311_devs),
				      शून्य, 0, शून्य);
		अगर (!pdata->disable_touch)
			mfd_add_devices(wm831x->dev, wm831x_num,
					touch_devs, ARRAY_SIZE(touch_devs),
					शून्य, 0, शून्य);
		अवरोध;

	हाल WM8312:
		ret = mfd_add_devices(wm831x->dev, wm831x_num,
				      wm8312_devs, ARRAY_SIZE(wm8312_devs),
				      शून्य, 0, शून्य);
		अगर (!pdata->disable_touch)
			mfd_add_devices(wm831x->dev, wm831x_num,
					touch_devs, ARRAY_SIZE(touch_devs),
					शून्य, 0, शून्य);
		अवरोध;

	हाल WM8320:
	हाल WM8321:
	हाल WM8325:
	हाल WM8326:
		ret = mfd_add_devices(wm831x->dev, wm831x_num,
				      wm8320_devs, ARRAY_SIZE(wm8320_devs),
				      शून्य, 0, शून्य);
		अवरोध;

	शेष:
		/* If this happens the bus probe function is buggy */
		BUG();
	पूर्ण

	अगर (ret != 0) अणु
		dev_err(wm831x->dev, "Failed to add children\n");
		जाओ err_irq;
	पूर्ण

	/* The RTC can only be used अगर the 32.768kHz crystal is
	 * enabled; this can't be controlled by software at runसमय.
	 */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CLOCK_CONTROL_2);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to read clock status: %d\n", ret);
		जाओ err_irq;
	पूर्ण

	अगर (ret & WM831X_XTAL_ENA) अणु
		ret = mfd_add_devices(wm831x->dev, wm831x_num,
				      rtc_devs, ARRAY_SIZE(rtc_devs),
				      शून्य, 0, शून्य);
		अगर (ret != 0) अणु
			dev_err(wm831x->dev, "Failed to add RTC: %d\n", ret);
			जाओ err_irq;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(wm831x->dev, "32.768kHz clock disabled, no RTC\n");
	पूर्ण

	अगर (pdata->backlight) अणु
		/* Treat errors as non-critical */
		ret = mfd_add_devices(wm831x->dev, wm831x_num, backlight_devs,
				      ARRAY_SIZE(backlight_devs), शून्य,
				      0, शून्य);
		अगर (ret < 0)
			dev_err(wm831x->dev, "Failed to add backlight: %d\n",
				ret);
	पूर्ण

	wm831x_otp_init(wm831x);

	अगर (pdata->post_init) अणु
		ret = pdata->post_init(wm831x);
		अगर (ret != 0) अणु
			dev_err(wm831x->dev, "post_init() failed: %d\n", ret);
			जाओ err_irq;
		पूर्ण
	पूर्ण

	वापस 0;

err_irq:
	wm831x_irq_निकास(wm831x);
err:
	mfd_हटाओ_devices(wm831x->dev);
	वापस ret;
पूर्ण

पूर्णांक wm831x_device_suspend(काष्ठा wm831x *wm831x)
अणु
	पूर्णांक reg, mask;

	/* If the अक्षरger IRQs are a wake source then make sure we ack
	 * them even अगर they're not actively being used (eg, no घातer
	 * driver or no IRQ line wired up) then acknowledge the
	 * पूर्णांकerrupts otherwise suspend won't last very दीर्घ.
	 */
	अगर (wm831x->अक्षरger_irq_wake) अणु
		reg = wm831x_reg_पढ़ो(wm831x, WM831X_INTERRUPT_STATUS_2_MASK);

		mask = WM831X_CHG_BATT_HOT_EINT |
			WM831X_CHG_BATT_COLD_EINT |
			WM831X_CHG_BATT_FAIL_EINT |
			WM831X_CHG_OV_EINT | WM831X_CHG_END_EINT |
			WM831X_CHG_TO_EINT | WM831X_CHG_MODE_EINT |
			WM831X_CHG_START_EINT;

		/* If any of the पूर्णांकerrupts are masked पढ़ो the statuses */
		अगर (reg & mask)
			reg = wm831x_reg_पढ़ो(wm831x,
					      WM831X_INTERRUPT_STATUS_2);

		अगर (reg & mask) अणु
			dev_info(wm831x->dev,
				 "Acknowledging masked charger IRQs: %x\n",
				 reg & mask);
			wm831x_reg_ग_लिखो(wm831x, WM831X_INTERRUPT_STATUS_2,
					 reg & mask);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम wm831x_device_shutकरोwn(काष्ठा wm831x *wm831x)
अणु
	अगर (wm831x->soft_shutकरोwn) अणु
		dev_info(wm831x->dev, "Initiating shutdown...\n");
		wm831x_set_bits(wm831x, WM831X_POWER_STATE, WM831X_CHIP_ON, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wm831x_device_shutकरोwn);
