<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery and Power Management code क्रम the Sharp SL-C7xx
 *
 * Copyright (c) 2005 Riअक्षरd Purdie
 */

#समावेश <linux/module.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/apm-emulation.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>

#समावेश <mach/corgi.h>
#समावेश <mach/pxa2xx-regs.h>
#समावेश "sharpsl_pm.h"

#समावेश "generic.h"

#घोषणा SHARPSL_CHARGE_ON_VOLT         0x99  /* 2.9V */
#घोषणा SHARPSL_CHARGE_ON_TEMP         0xe0  /* 2.9V */
#घोषणा SHARPSL_CHARGE_ON_ACIN_HIGH    0x9b  /* 6V */
#घोषणा SHARPSL_CHARGE_ON_ACIN_LOW     0x34  /* 2V */
#घोषणा SHARPSL_FATAL_ACIN_VOLT        182   /* 3.45V */
#घोषणा SHARPSL_FATAL_NOACIN_VOLT      170   /* 3.40V */

अटल काष्ठा gpio अक्षरger_gpios[] = अणु
	अणु CORGI_GPIO_ADC_TEMP_ON, GPIOF_OUT_INIT_LOW, "ADC Temp On" पूर्ण,
	अणु CORGI_GPIO_CHRG_ON,	  GPIOF_OUT_INIT_LOW, "Charger On" पूर्ण,
	अणु CORGI_GPIO_CHRG_UKN,	  GPIOF_OUT_INIT_LOW, "Charger Unknown" पूर्ण,
	अणु CORGI_GPIO_AC_IN,	  GPIOF_IN, "Charger Detection" पूर्ण,
	अणु CORGI_GPIO_KEY_INT,	  GPIOF_IN, "Key Interrupt" पूर्ण,
	अणु CORGI_GPIO_WAKEUP,	  GPIOF_IN, "System wakeup notification" पूर्ण,
पूर्ण;

अटल व्योम corgi_अक्षरger_init(व्योम)
अणु
	gpio_request_array(ARRAY_AND_SIZE(अक्षरger_gpios));
पूर्ण

अटल व्योम corgi_measure_temp(पूर्णांक on)
अणु
	gpio_set_value(CORGI_GPIO_ADC_TEMP_ON, on);
पूर्ण

अटल व्योम corgi_अक्षरge(पूर्णांक on)
अणु
	अगर (on) अणु
		अगर (machine_is_corgi() && (sharpsl_pm.flags & SHARPSL_SUSPENDED)) अणु
			gpio_set_value(CORGI_GPIO_CHRG_ON, 0);
			gpio_set_value(CORGI_GPIO_CHRG_UKN, 1);
		पूर्ण अन्यथा अणु
			gpio_set_value(CORGI_GPIO_CHRG_ON, 1);
			gpio_set_value(CORGI_GPIO_CHRG_UKN, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		gpio_set_value(CORGI_GPIO_CHRG_ON, 0);
		gpio_set_value(CORGI_GPIO_CHRG_UKN, 0);
	पूर्ण
पूर्ण

अटल व्योम corgi_disअक्षरge(पूर्णांक on)
अणु
	gpio_set_value(CORGI_GPIO_DISCHARGE_ON, on);
पूर्ण

अटल व्योम corgi_presuspend(व्योम)
अणु
पूर्ण

अटल व्योम corgi_postsuspend(व्योम)
अणु
पूर्ण

/*
 * Check what brought us out of the suspend.
 * Return: 0 to sleep, otherwise wake
 */
अटल पूर्णांक corgi_should_wakeup(अचिन्हित पूर्णांक resume_on_alarm)
अणु
	पूर्णांक is_resume = 0;

	dev_dbg(sharpsl_pm.dev, "PEDR = %x, GPIO_AC_IN = %d, "
		"GPIO_CHRG_FULL = %d, GPIO_KEY_INT = %d, GPIO_WAKEUP = %d\n",
		PEDR, gpio_get_value(CORGI_GPIO_AC_IN),
		gpio_get_value(CORGI_GPIO_CHRG_FULL),
		gpio_get_value(CORGI_GPIO_KEY_INT),
		gpio_get_value(CORGI_GPIO_WAKEUP));

	अगर ((PEDR & GPIO_bit(CORGI_GPIO_AC_IN))) अणु
		अगर (sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_ACIN)) अणु
			/* अक्षरge on */
			dev_dbg(sharpsl_pm.dev, "ac insert\n");
			sharpsl_pm.flags |= SHARPSL_DO_OFFLINE_CHRG;
		पूर्ण अन्यथा अणु
			/* अक्षरge off */
			dev_dbg(sharpsl_pm.dev, "ac remove\n");
			sharpsl_pm_led(SHARPSL_LED_OFF);
			sharpsl_pm.machinfo->अक्षरge(0);
			sharpsl_pm.अक्षरge_mode = CHRG_OFF;
		पूर्ण
	पूर्ण

	अगर ((PEDR & GPIO_bit(CORGI_GPIO_CHRG_FULL)))
		dev_dbg(sharpsl_pm.dev, "Charge full interrupt\n");

	अगर (PEDR & GPIO_bit(CORGI_GPIO_KEY_INT))
		is_resume |= GPIO_bit(CORGI_GPIO_KEY_INT);

	अगर (PEDR & GPIO_bit(CORGI_GPIO_WAKEUP))
		is_resume |= GPIO_bit(CORGI_GPIO_WAKEUP);

	अगर (resume_on_alarm && (PEDR & PWER_RTC))
		is_resume |= PWER_RTC;

	dev_dbg(sharpsl_pm.dev, "is_resume: %x\n",is_resume);
	वापस is_resume;
पूर्ण

अटल bool corgi_अक्षरger_wakeup(व्योम)
अणु
	वापस !gpio_get_value(CORGI_GPIO_AC_IN) ||
		!gpio_get_value(CORGI_GPIO_KEY_INT) ||
		!gpio_get_value(CORGI_GPIO_WAKEUP);
पूर्ण

अचिन्हित दीर्घ corgipm_पढ़ो_devdata(पूर्णांक type)
अणु
	चयन(type) अणु
	हाल SHARPSL_STATUS_ACIN:
		वापस !gpio_get_value(CORGI_GPIO_AC_IN);
	हाल SHARPSL_STATUS_LOCK:
		वापस gpio_get_value(sharpsl_pm.machinfo->gpio_batlock);
	हाल SHARPSL_STATUS_CHRGFULL:
		वापस gpio_get_value(sharpsl_pm.machinfo->gpio_batfull);
	हाल SHARPSL_STATUS_FATAL:
		वापस gpio_get_value(sharpsl_pm.machinfo->gpio_fatal);
	हाल SHARPSL_ACIN_VOLT:
		वापस sharpsl_pm_pxa_पढ़ो_max1111(MAX1111_ACIN_VOLT);
	हाल SHARPSL_BATT_TEMP:
		वापस sharpsl_pm_pxa_पढ़ो_max1111(MAX1111_BATT_TEMP);
	हाल SHARPSL_BATT_VOLT:
	शेष:
		वापस sharpsl_pm_pxa_पढ़ो_max1111(MAX1111_BATT_VOLT);
	पूर्ण
पूर्ण

अटल काष्ठा sharpsl_अक्षरger_machinfo corgi_pm_machinfo = अणु
	.init            = corgi_अक्षरger_init,
	.निकास            = शून्य,
	.gpio_batlock    = CORGI_GPIO_BAT_COVER,
	.gpio_acin       = CORGI_GPIO_AC_IN,
	.gpio_batfull    = CORGI_GPIO_CHRG_FULL,
	.disअक्षरge       = corgi_disअक्षरge,
	.अक्षरge          = corgi_अक्षरge,
	.measure_temp    = corgi_measure_temp,
	.presuspend      = corgi_presuspend,
	.postsuspend     = corgi_postsuspend,
	.पढ़ो_devdata    = corgipm_पढ़ो_devdata,
	.अक्षरger_wakeup  = corgi_अक्षरger_wakeup,
	.should_wakeup   = corgi_should_wakeup,
#अगर defined(CONFIG_LCD_CORGI)
	.backlight_limit = corgi_lcd_limit_पूर्णांकensity,
#पूर्ण_अगर
	.अक्षरge_on_volt	  = SHARPSL_CHARGE_ON_VOLT,
	.अक्षरge_on_temp	  = SHARPSL_CHARGE_ON_TEMP,
	.अक्षरge_acin_high = SHARPSL_CHARGE_ON_ACIN_HIGH,
	.अक्षरge_acin_low  = SHARPSL_CHARGE_ON_ACIN_LOW,
	.fatal_acin_volt  = SHARPSL_FATAL_ACIN_VOLT,
	.fatal_noacin_volt= SHARPSL_FATAL_NOACIN_VOLT,
	.bat_levels       = 40,
	.bat_levels_noac  = sharpsl_battery_levels_noac,
	.bat_levels_acin  = sharpsl_battery_levels_acin,
	.status_high_acin = 188,
	.status_low_acin  = 178,
	.status_high_noac = 185,
	.status_low_noac  = 175,
पूर्ण;

अटल काष्ठा platक्रमm_device *corgipm_device;

अटल पूर्णांक corgipm_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_corgi() && !machine_is_shepherd()
			&& !machine_is_husky())
		वापस -ENODEV;

	corgipm_device = platक्रमm_device_alloc("sharpsl-pm", -1);
	अगर (!corgipm_device)
		वापस -ENOMEM;

	अगर (!machine_is_corgi())
	    corgi_pm_machinfo.batfull_irq = 1;

	corgipm_device->dev.platक्रमm_data = &corgi_pm_machinfo;
	ret = platक्रमm_device_add(corgipm_device);

	अगर (ret)
		platक्रमm_device_put(corgipm_device);

	वापस ret;
पूर्ण

अटल व्योम corgipm_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(corgipm_device);
पूर्ण

module_init(corgipm_init);
module_निकास(corgipm_निकास);
