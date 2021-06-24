<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery and Power Management code क्रम the Sharp SL-Cxx00
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

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>

#समावेश <mach/spitz.h>
#समावेश "pxa27x.h"
#समावेश "sharpsl_pm.h"

#समावेश "generic.h"

#घोषणा SHARPSL_CHARGE_ON_VOLT         0x99  /* 2.9V */
#घोषणा SHARPSL_CHARGE_ON_TEMP         0xe0  /* 2.9V */
#घोषणा SHARPSL_CHARGE_ON_ACIN_HIGH    0x9b  /* 6V */
#घोषणा SHARPSL_CHARGE_ON_ACIN_LOW     0x34  /* 2V */
#घोषणा SHARPSL_FATAL_ACIN_VOLT        182   /* 3.45V */
#घोषणा SHARPSL_FATAL_NOACIN_VOLT      170   /* 3.40V */

अटल पूर्णांक spitz_last_ac_status;

अटल काष्ठा gpio spitz_अक्षरger_gpios[] = अणु
	अणु SPITZ_GPIO_KEY_INT,	GPIOF_IN, "Keyboard Interrupt" पूर्ण,
	अणु SPITZ_GPIO_SYNC,	GPIOF_IN, "Sync" पूर्ण,
	अणु SPITZ_GPIO_AC_IN,     GPIOF_IN, "Charger Detection" पूर्ण,
	अणु SPITZ_GPIO_ADC_TEMP_ON, GPIOF_OUT_INIT_LOW, "ADC Temp On" पूर्ण,
	अणु SPITZ_GPIO_JK_B,	  GPIOF_OUT_INIT_LOW, "JK B" पूर्ण,
	अणु SPITZ_GPIO_CHRG_ON,	  GPIOF_OUT_INIT_LOW, "Charger On" पूर्ण,
पूर्ण;

अटल व्योम spitz_अक्षरger_init(व्योम)
अणु
	gpio_request_array(ARRAY_AND_SIZE(spitz_अक्षरger_gpios));
पूर्ण

अटल व्योम spitz_measure_temp(पूर्णांक on)
अणु
	gpio_set_value(SPITZ_GPIO_ADC_TEMP_ON, on);
पूर्ण

अटल व्योम spitz_अक्षरge(पूर्णांक on)
अणु
	अगर (on) अणु
		अगर (sharpsl_pm.flags & SHARPSL_SUSPENDED) अणु
			gpio_set_value(SPITZ_GPIO_JK_B, 1);
			gpio_set_value(SPITZ_GPIO_CHRG_ON, 0);
		पूर्ण अन्यथा अणु
			gpio_set_value(SPITZ_GPIO_JK_B, 0);
			gpio_set_value(SPITZ_GPIO_CHRG_ON, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		gpio_set_value(SPITZ_GPIO_JK_B, 0);
		gpio_set_value(SPITZ_GPIO_CHRG_ON, 1);
	पूर्ण
पूर्ण

अटल व्योम spitz_disअक्षरge(पूर्णांक on)
अणु
	gpio_set_value(SPITZ_GPIO_JK_A, on);
पूर्ण

/* HACK - For unknown reasons, accurate voltage पढ़ोings are only made with a load
   on the घातer bus which the green led on spitz provides */
अटल व्योम spitz_disअक्षरge1(पूर्णांक on)
अणु
	gpio_set_value(SPITZ_GPIO_LED_GREEN, on);
पूर्ण

अटल अचिन्हित दीर्घ gpio18_config = GPIO18_GPIO;

अटल व्योम spitz_presuspend(व्योम)
अणु
	spitz_last_ac_status = sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_ACIN);

	/* GPIO Sleep Register */
	PGSR0 = 0x00144018;
	PGSR1 = 0x00EF0000;
	अगर (machine_is_akita()) अणु
		PGSR2 = 0x2121C000;
		PGSR3 = 0x00600400;
	पूर्ण अन्यथा अणु
		PGSR2 = 0x0121C000;
		PGSR3 = 0x00600000;
	पूर्ण

	PGSR0 &= ~SPITZ_GPIO_G0_STROBE_BIT;
	PGSR1 &= ~SPITZ_GPIO_G1_STROBE_BIT;
	PGSR2 &= ~SPITZ_GPIO_G2_STROBE_BIT;
	PGSR3 &= ~SPITZ_GPIO_G3_STROBE_BIT;
	PGSR2 |= GPIO_bit(SPITZ_GPIO_KEY_STROBE0);

	pxa2xx_mfp_config(&gpio18_config, 1);
	gpio_request_one(18, GPIOF_OUT_INIT_HIGH, "Unknown");
	gpio_मुक्त(18);

	PRER = GPIO_bit(SPITZ_GPIO_KEY_INT);
	PFER = GPIO_bit(SPITZ_GPIO_KEY_INT) | GPIO_bit(SPITZ_GPIO_RESET);
	PWER = GPIO_bit(SPITZ_GPIO_KEY_INT) | GPIO_bit(SPITZ_GPIO_RESET) | PWER_RTC;
	PKWR = GPIO_bit(SPITZ_GPIO_SYNC) | GPIO_bit(SPITZ_GPIO_KEY_INT) | GPIO_bit(SPITZ_GPIO_RESET);
	PKSR = 0xffffffff; /* clear */

	/* nRESET_OUT Disable */
	PSLR |= PSLR_SL_ROD;

	/* Stop 3.6MHz and drive HIGH to PCMCIA and CS */
	PCFR = PCFR_GPR_EN | PCFR_OPDE;
पूर्ण

अटल व्योम spitz_postsuspend(व्योम)
अणु
पूर्ण

अटल पूर्णांक spitz_should_wakeup(अचिन्हित पूर्णांक resume_on_alarm)
अणु
	पूर्णांक is_resume = 0;
	पूर्णांक acin = sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_ACIN);

	अगर (spitz_last_ac_status != acin) अणु
		अगर (acin) अणु
			/* अक्षरge on */
			sharpsl_pm.flags |= SHARPSL_DO_OFFLINE_CHRG;
			dev_dbg(sharpsl_pm.dev, "AC Inserted\n");
		पूर्ण अन्यथा अणु
			/* अक्षरge off */
			dev_dbg(sharpsl_pm.dev, "AC Removed\n");
			sharpsl_pm_led(SHARPSL_LED_OFF);
			sharpsl_pm.machinfo->अक्षरge(0);
			sharpsl_pm.अक्षरge_mode = CHRG_OFF;
		पूर्ण
		spitz_last_ac_status = acin;
		/* Return to suspend as this must be what we were woken क्रम */
		वापस 0;
	पूर्ण

	अगर (PEDR & GPIO_bit(SPITZ_GPIO_KEY_INT))
		is_resume |= GPIO_bit(SPITZ_GPIO_KEY_INT);

	अगर (PKSR & GPIO_bit(SPITZ_GPIO_SYNC))
		is_resume |= GPIO_bit(SPITZ_GPIO_SYNC);

	अगर (resume_on_alarm && (PEDR & PWER_RTC))
		is_resume |= PWER_RTC;

	dev_dbg(sharpsl_pm.dev, "is_resume: %x\n", is_resume);
	वापस is_resume;
पूर्ण

अटल bool spitz_अक्षरger_wakeup(व्योम)
अणु
	वापस !gpio_get_value(SPITZ_GPIO_KEY_INT) ||
		gpio_get_value(SPITZ_GPIO_SYNC);
पूर्ण

अचिन्हित दीर्घ spitzpm_पढ़ो_devdata(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल SHARPSL_STATUS_ACIN:
		वापस !gpio_get_value(SPITZ_GPIO_AC_IN);
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

काष्ठा sharpsl_अक्षरger_machinfo spitz_pm_machinfo = अणु
	.init             = spitz_अक्षरger_init,
	.निकास             = शून्य,
	.gpio_batlock     = SPITZ_GPIO_BAT_COVER,
	.gpio_acin        = SPITZ_GPIO_AC_IN,
	.gpio_batfull     = SPITZ_GPIO_CHRG_FULL,
	.batfull_irq	  = 1,
	.gpio_fatal       = SPITZ_GPIO_FATAL_BAT,
	.disअक्षरge        = spitz_disअक्षरge,
	.disअक्षरge1       = spitz_disअक्षरge1,
	.अक्षरge           = spitz_अक्षरge,
	.measure_temp     = spitz_measure_temp,
	.presuspend       = spitz_presuspend,
	.postsuspend      = spitz_postsuspend,
	.पढ़ो_devdata     = spitzpm_पढ़ो_devdata,
	.अक्षरger_wakeup   = spitz_अक्षरger_wakeup,
	.should_wakeup    = spitz_should_wakeup,
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

अटल काष्ठा platक्रमm_device *spitzpm_device;

अटल पूर्णांक spitzpm_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_spitz() && !machine_is_akita()
			&& !machine_is_borzoi())
		वापस -ENODEV;

	spitzpm_device = platक्रमm_device_alloc("sharpsl-pm", -1);
	अगर (!spitzpm_device)
		वापस -ENOMEM;

	spitzpm_device->dev.platक्रमm_data = &spitz_pm_machinfo;
	ret = platक्रमm_device_add(spitzpm_device);

	अगर (ret)
		platक्रमm_device_put(spitzpm_device);

	वापस ret;
पूर्ण

अटल व्योम spitzpm_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(spitzpm_device);
पूर्ण

module_init(spitzpm_init);
module_निकास(spitzpm_निकास);
