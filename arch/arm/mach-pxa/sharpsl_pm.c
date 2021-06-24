<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery and Power Management code क्रम the Sharp SL-C7xx and SL-Cxx00
 * series of PDAs
 *
 * Copyright (c) 2004-2005 Riअक्षरd Purdie
 *
 * Based on code written by Sharp क्रम 2.4 kernels
 */

#अघोषित DEBUG

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/apm-emulation.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/leds.h>
#समावेश <linux/suspend.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach-types.h>
#समावेश "pm.h"
#समावेश <mach/pxa2xx-regs.h>
#समावेश "regs-rtc.h"
#समावेश "sharpsl_pm.h"

/*
 * Constants
 */
#घोषणा SHARPSL_CHARGE_ON_TIME_INTERVAL        (msecs_to_jअगरfies(1*60*1000))  /* 1 min */
#घोषणा SHARPSL_CHARGE_FINISH_TIME             (msecs_to_jअगरfies(10*60*1000)) /* 10 min */
#घोषणा SHARPSL_BATCHK_TIME                    (msecs_to_jअगरfies(15*1000))    /* 15 sec */
#घोषणा SHARPSL_BATCHK_TIME_SUSPEND            (60*10)                        /* 10 min */

#घोषणा SHARPSL_WAIT_CO_TIME                   15  /* 15 sec */
#घोषणा SHARPSL_WAIT_DISCHARGE_ON              100 /* 100 msec */
#घोषणा SHARPSL_CHECK_BATTERY_WAIT_TIME_TEMP   10  /* 10 msec */
#घोषणा SHARPSL_CHECK_BATTERY_WAIT_TIME_VOLT   10  /* 10 msec */
#घोषणा SHARPSL_CHECK_BATTERY_WAIT_TIME_ACIN   10  /* 10 msec */
#घोषणा SHARPSL_CHARGE_WAIT_TIME               15  /* 15 msec */
#घोषणा SHARPSL_CHARGE_CO_CHECK_TIME           5   /* 5 msec */
#घोषणा SHARPSL_CHARGE_RETRY_CNT               1   /* eqv. 10 min */

/*
 * Prototypes
 */
#अगर_घोषित CONFIG_PM
अटल पूर्णांक sharpsl_off_अक्षरge_battery(व्योम);
अटल पूर्णांक sharpsl_check_battery_voltage(व्योम);
#पूर्ण_अगर
अटल पूर्णांक sharpsl_check_battery_temp(व्योम);
अटल पूर्णांक sharpsl_ac_check(व्योम);
अटल पूर्णांक sharpsl_average_value(पूर्णांक ad);
अटल व्योम sharpsl_average_clear(व्योम);
अटल व्योम sharpsl_अक्षरge_toggle(काष्ठा work_काष्ठा *निजी_);
अटल व्योम sharpsl_battery_thपढ़ो(काष्ठा work_काष्ठा *निजी_);


/*
 * Variables
 */
काष्ठा sharpsl_pm_status sharpsl_pm;
अटल DECLARE_DELAYED_WORK(toggle_अक्षरger, sharpsl_अक्षरge_toggle);
अटल DECLARE_DELAYED_WORK(sharpsl_bat, sharpsl_battery_thपढ़ो);
DEFINE_LED_TRIGGER(sharpsl_अक्षरge_led_trigger);



काष्ठा battery_thresh sharpsl_battery_levels_acin[] = अणु
	अणु 213, 100पूर्ण,
	अणु 212,  98पूर्ण,
	अणु 211,  95पूर्ण,
	अणु 210,  93पूर्ण,
	अणु 209,  90पूर्ण,
	अणु 208,  88पूर्ण,
	अणु 207,  85पूर्ण,
	अणु 206,  83पूर्ण,
	अणु 205,  80पूर्ण,
	अणु 204,  78पूर्ण,
	अणु 203,  75पूर्ण,
	अणु 202,  73पूर्ण,
	अणु 201,  70पूर्ण,
	अणु 200,  68पूर्ण,
	अणु 199,  65पूर्ण,
	अणु 198,  63पूर्ण,
	अणु 197,  60पूर्ण,
	अणु 196,  58पूर्ण,
	अणु 195,  55पूर्ण,
	अणु 194,  53पूर्ण,
	अणु 193,  50पूर्ण,
	अणु 192,  48पूर्ण,
	अणु 192,  45पूर्ण,
	अणु 191,  43पूर्ण,
	अणु 191,  40पूर्ण,
	अणु 190,  38पूर्ण,
	अणु 190,  35पूर्ण,
	अणु 189,  33पूर्ण,
	अणु 188,  30पूर्ण,
	अणु 187,  28पूर्ण,
	अणु 186,  25पूर्ण,
	अणु 185,  23पूर्ण,
	अणु 184,  20पूर्ण,
	अणु 183,  18पूर्ण,
	अणु 182,  15पूर्ण,
	अणु 181,  13पूर्ण,
	अणु 180,  10पूर्ण,
	अणु 179,   8पूर्ण,
	अणु 178,   5पूर्ण,
	अणु   0,   0पूर्ण,
पूर्ण;

काष्ठा battery_thresh sharpsl_battery_levels_noac[] = अणु
	अणु 213, 100पूर्ण,
	अणु 212,  98पूर्ण,
	अणु 211,  95पूर्ण,
	अणु 210,  93पूर्ण,
	अणु 209,  90पूर्ण,
	अणु 208,  88पूर्ण,
	अणु 207,  85पूर्ण,
	अणु 206,  83पूर्ण,
	अणु 205,  80पूर्ण,
	अणु 204,  78पूर्ण,
	अणु 203,  75पूर्ण,
	अणु 202,  73पूर्ण,
	अणु 201,  70पूर्ण,
	अणु 200,  68पूर्ण,
	अणु 199,  65पूर्ण,
	अणु 198,  63पूर्ण,
	अणु 197,  60पूर्ण,
	अणु 196,  58पूर्ण,
	अणु 195,  55पूर्ण,
	अणु 194,  53पूर्ण,
	अणु 193,  50पूर्ण,
	अणु 192,  48पूर्ण,
	अणु 191,  45पूर्ण,
	अणु 190,  43पूर्ण,
	अणु 189,  40पूर्ण,
	अणु 188,  38पूर्ण,
	अणु 187,  35पूर्ण,
	अणु 186,  33पूर्ण,
	अणु 185,  30पूर्ण,
	अणु 184,  28पूर्ण,
	अणु 183,  25पूर्ण,
	अणु 182,  23पूर्ण,
	अणु 181,  20पूर्ण,
	अणु 180,  18पूर्ण,
	अणु 179,  15पूर्ण,
	अणु 178,  13पूर्ण,
	अणु 177,  10पूर्ण,
	अणु 176,   8पूर्ण,
	अणु 175,   5पूर्ण,
	अणु   0,   0पूर्ण,
पूर्ण;

/* MAX1111 Commands */
#घोषणा MAXCTRL_PD0      (1u << 0)
#घोषणा MAXCTRL_PD1      (1u << 1)
#घोषणा MAXCTRL_SGL      (1u << 2)
#घोषणा MAXCTRL_UNI      (1u << 3)
#घोषणा MAXCTRL_SEL_SH   4
#घोषणा MAXCTRL_STR      (1u << 7)

बाह्य पूर्णांक max1111_पढ़ो_channel(पूर्णांक);
/*
 * Read MAX1111 ADC
 */
पूर्णांक sharpsl_pm_pxa_पढ़ो_max1111(पूर्णांक channel)
अणु
	/* Ugly, better move this function पूर्णांकo another module */
	अगर (machine_is_tosa())
	    वापस 0;

	/* max1111 accepts channels from 0-3, however,
	 * it is encoded from 0-7 here in the code.
	 */
	वापस max1111_पढ़ो_channel(channel >> 1);
पूर्ण

अटल पूर्णांक get_percentage(पूर्णांक voltage)
अणु
	पूर्णांक i = sharpsl_pm.machinfo->bat_levels - 1;
	पूर्णांक bl_status = sharpsl_pm.machinfo->backlight_get_status ? sharpsl_pm.machinfo->backlight_get_status() : 0;
	काष्ठा battery_thresh *thresh;

	अगर (sharpsl_pm.अक्षरge_mode == CHRG_ON)
		thresh = bl_status ? sharpsl_pm.machinfo->bat_levels_acin_bl : sharpsl_pm.machinfo->bat_levels_acin;
	अन्यथा
		thresh = bl_status ? sharpsl_pm.machinfo->bat_levels_noac_bl : sharpsl_pm.machinfo->bat_levels_noac;

	जबतक (i > 0 && (voltage > thresh[i].voltage))
		i--;

	वापस thresh[i].percentage;
पूर्ण

अटल पूर्णांक get_apm_status(पूर्णांक voltage)
अणु
	पूर्णांक low_thresh, high_thresh;

	अगर (sharpsl_pm.अक्षरge_mode == CHRG_ON) अणु
		high_thresh = sharpsl_pm.machinfo->status_high_acin;
		low_thresh = sharpsl_pm.machinfo->status_low_acin;
	पूर्ण अन्यथा अणु
		high_thresh = sharpsl_pm.machinfo->status_high_noac;
		low_thresh = sharpsl_pm.machinfo->status_low_noac;
	पूर्ण

	अगर (voltage >= high_thresh)
		वापस APM_BATTERY_STATUS_HIGH;
	अगर (voltage >= low_thresh)
		वापस APM_BATTERY_STATUS_LOW;
	वापस APM_BATTERY_STATUS_CRITICAL;
पूर्ण

व्योम sharpsl_battery_kick(व्योम)
अणु
	schedule_delayed_work(&sharpsl_bat, msecs_to_jअगरfies(125));
पूर्ण
EXPORT_SYMBOL(sharpsl_battery_kick);


अटल व्योम sharpsl_battery_thपढ़ो(काष्ठा work_काष्ठा *निजी_)
अणु
	पूर्णांक voltage, percent, apm_status, i;

	अगर (!sharpsl_pm.machinfo)
		वापस;

	sharpsl_pm.battstat.ac_status = (sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_ACIN) ? APM_AC_ONLINE : APM_AC_OFFLINE);

	/* Corgi cannot confirm when battery fully अक्षरged so periodically kick! */
	अगर (!sharpsl_pm.machinfo->batfull_irq && (sharpsl_pm.अक्षरge_mode == CHRG_ON)
			&& समय_after(jअगरfies, sharpsl_pm.अक्षरge_start_समय +  SHARPSL_CHARGE_ON_TIME_INTERVAL))
		schedule_delayed_work(&toggle_अक्षरger, 0);

	क्रम (i = 0; i < 5; i++) अणु
		voltage = sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_BATT_VOLT);
		अगर (voltage > 0)
			अवरोध;
	पूर्ण
	अगर (voltage <= 0) अणु
		voltage = sharpsl_pm.machinfo->bat_levels_noac[0].voltage;
		dev_warn(sharpsl_pm.dev, "Warning: Cannot read main battery!\n");
	पूर्ण

	voltage = sharpsl_average_value(voltage);
	apm_status = get_apm_status(voltage);
	percent = get_percentage(voltage);

	/* At low battery voltages, the voltage has a tendency to start
	   creeping back up so we try to aव्योम this here */
	अगर ((sharpsl_pm.battstat.ac_status == APM_AC_ONLINE)
	    || (apm_status == APM_BATTERY_STATUS_HIGH)
	    || percent <= sharpsl_pm.battstat.मुख्यbat_percent) अणु
		sharpsl_pm.battstat.मुख्यbat_voltage = voltage;
		sharpsl_pm.battstat.मुख्यbat_status = apm_status;
		sharpsl_pm.battstat.मुख्यbat_percent = percent;
	पूर्ण

	dev_dbg(sharpsl_pm.dev, "Battery: voltage: %d, status: %d, percentage: %d, time: %ld\n", voltage,
			sharpsl_pm.battstat.मुख्यbat_status, sharpsl_pm.battstat.मुख्यbat_percent, jअगरfies);

	/* Suspend अगर critical battery level */
	अगर ((sharpsl_pm.battstat.ac_status != APM_AC_ONLINE)
	     && (sharpsl_pm.battstat.मुख्यbat_status == APM_BATTERY_STATUS_CRITICAL)
	     && !(sharpsl_pm.flags & SHARPSL_APM_QUEUED)) अणु
		sharpsl_pm.flags |= SHARPSL_APM_QUEUED;
		dev_err(sharpsl_pm.dev, "Fatal Off\n");
		apm_queue_event(APM_CRITICAL_SUSPEND);
	पूर्ण

	schedule_delayed_work(&sharpsl_bat, SHARPSL_BATCHK_TIME);
पूर्ण

व्योम sharpsl_pm_led(पूर्णांक val)
अणु
	अगर (val == SHARPSL_LED_ERROR) अणु
		dev_err(sharpsl_pm.dev, "Charging Error!\n");
	पूर्ण अन्यथा अगर (val == SHARPSL_LED_ON) अणु
		dev_dbg(sharpsl_pm.dev, "Charge LED On\n");
		led_trigger_event(sharpsl_अक्षरge_led_trigger, LED_FULL);
	पूर्ण अन्यथा अणु
		dev_dbg(sharpsl_pm.dev, "Charge LED Off\n");
		led_trigger_event(sharpsl_अक्षरge_led_trigger, LED_OFF);
	पूर्ण
पूर्ण

अटल व्योम sharpsl_अक्षरge_on(व्योम)
अणु
	dev_dbg(sharpsl_pm.dev, "Turning Charger On\n");

	sharpsl_pm.full_count = 0;
	sharpsl_pm.अक्षरge_mode = CHRG_ON;
	schedule_delayed_work(&toggle_अक्षरger, msecs_to_jअगरfies(250));
	schedule_delayed_work(&sharpsl_bat, msecs_to_jअगरfies(500));
पूर्ण

अटल व्योम sharpsl_अक्षरge_off(व्योम)
अणु
	dev_dbg(sharpsl_pm.dev, "Turning Charger Off\n");

	sharpsl_pm.machinfo->अक्षरge(0);
	sharpsl_pm_led(SHARPSL_LED_OFF);
	sharpsl_pm.अक्षरge_mode = CHRG_OFF;

	schedule_delayed_work(&sharpsl_bat, 0);
पूर्ण

अटल व्योम sharpsl_अक्षरge_error(व्योम)
अणु
	sharpsl_pm_led(SHARPSL_LED_ERROR);
	sharpsl_pm.machinfo->अक्षरge(0);
	sharpsl_pm.अक्षरge_mode = CHRG_ERROR;
पूर्ण

अटल व्योम sharpsl_अक्षरge_toggle(काष्ठा work_काष्ठा *निजी_)
अणु
	dev_dbg(sharpsl_pm.dev, "Toggling Charger at time: %lx\n", jअगरfies);

	अगर (!sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_ACIN)) अणु
		sharpsl_अक्षरge_off();
		वापस;
	पूर्ण अन्यथा अगर ((sharpsl_check_battery_temp() < 0) || (sharpsl_ac_check() < 0)) अणु
		sharpsl_अक्षरge_error();
		वापस;
	पूर्ण

	sharpsl_pm_led(SHARPSL_LED_ON);
	sharpsl_pm.machinfo->अक्षरge(0);
	mdelay(SHARPSL_CHARGE_WAIT_TIME);
	sharpsl_pm.machinfo->अक्षरge(1);

	sharpsl_pm.अक्षरge_start_समय = jअगरfies;
पूर्ण

अटल व्योम sharpsl_ac_समयr(काष्ठा समयr_list *unused)
अणु
	पूर्णांक acin = sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_ACIN);

	dev_dbg(sharpsl_pm.dev, "AC Status: %d\n", acin);

	sharpsl_average_clear();
	अगर (acin && (sharpsl_pm.अक्षरge_mode != CHRG_ON))
		sharpsl_अक्षरge_on();
	अन्यथा अगर (sharpsl_pm.अक्षरge_mode == CHRG_ON)
		sharpsl_अक्षरge_off();

	schedule_delayed_work(&sharpsl_bat, 0);
पूर्ण


अटल irqवापस_t sharpsl_ac_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	/* Delay the event slightly to debounce */
	/* Must be a smaller delay than the chrg_full_isr below */
	mod_समयr(&sharpsl_pm.ac_समयr, jअगरfies + msecs_to_jअगरfies(250));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sharpsl_chrg_full_समयr(काष्ठा समयr_list *unused)
अणु
	dev_dbg(sharpsl_pm.dev, "Charge Full at time: %lx\n", jअगरfies);

	sharpsl_pm.full_count++;

	अगर (!sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_ACIN)) अणु
		dev_dbg(sharpsl_pm.dev, "Charge Full: AC removed - stop charging!\n");
		अगर (sharpsl_pm.अक्षरge_mode == CHRG_ON)
			sharpsl_अक्षरge_off();
	पूर्ण अन्यथा अगर (sharpsl_pm.full_count < 2) अणु
		dev_dbg(sharpsl_pm.dev, "Charge Full: Count too low\n");
		schedule_delayed_work(&toggle_अक्षरger, 0);
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, sharpsl_pm.अक्षरge_start_समय + SHARPSL_CHARGE_FINISH_TIME)) अणु
		dev_dbg(sharpsl_pm.dev, "Charge Full: Interrupt generated too slowly - retry.\n");
		schedule_delayed_work(&toggle_अक्षरger, 0);
	पूर्ण अन्यथा अणु
		sharpsl_अक्षरge_off();
		sharpsl_pm.अक्षरge_mode = CHRG_DONE;
		dev_dbg(sharpsl_pm.dev, "Charge Full: Charging Finished\n");
	पूर्ण
पूर्ण

/* Charging Finished Interrupt (Not present on Corgi) */
/* Can trigger at the same समय as an AC status change so
   delay until after that has been processed */
अटल irqवापस_t sharpsl_chrg_full_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	अगर (sharpsl_pm.flags & SHARPSL_SUSPENDED)
		वापस IRQ_HANDLED;

	/* delay until after any ac पूर्णांकerrupt */
	mod_समयr(&sharpsl_pm.chrg_full_समयr, jअगरfies + msecs_to_jअगरfies(500));

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sharpsl_fatal_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक is_fatal = 0;

	अगर (!sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_LOCK)) अणु
		dev_err(sharpsl_pm.dev, "Battery now Unlocked! Suspending.\n");
		is_fatal = 1;
	पूर्ण

	अगर (!sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_FATAL)) अणु
		dev_err(sharpsl_pm.dev, "Fatal Batt Error! Suspending.\n");
		is_fatal = 1;
	पूर्ण

	अगर (!(sharpsl_pm.flags & SHARPSL_APM_QUEUED) && is_fatal) अणु
		sharpsl_pm.flags |= SHARPSL_APM_QUEUED;
		apm_queue_event(APM_CRITICAL_SUSPEND);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Maपूर्णांकain an average of the last 10 पढ़ोings
 */
#घोषणा SHARPSL_CNV_VALUE_NUM    10
अटल पूर्णांक sharpsl_ad_index;

अटल व्योम sharpsl_average_clear(व्योम)
अणु
	sharpsl_ad_index = 0;
पूर्ण

अटल पूर्णांक sharpsl_average_value(पूर्णांक ad)
अणु
	पूर्णांक i, ad_val = 0;
	अटल पूर्णांक sharpsl_ad[SHARPSL_CNV_VALUE_NUM+1];

	अगर (sharpsl_pm.battstat.मुख्यbat_status != APM_BATTERY_STATUS_HIGH) अणु
		sharpsl_ad_index = 0;
		वापस ad;
	पूर्ण

	sharpsl_ad[sharpsl_ad_index] = ad;
	sharpsl_ad_index++;
	अगर (sharpsl_ad_index >= SHARPSL_CNV_VALUE_NUM) अणु
		क्रम (i = 0; i < (SHARPSL_CNV_VALUE_NUM-1); i++)
			sharpsl_ad[i] = sharpsl_ad[i+1];
		sharpsl_ad_index = SHARPSL_CNV_VALUE_NUM - 1;
	पूर्ण
	क्रम (i = 0; i < sharpsl_ad_index; i++)
		ad_val += sharpsl_ad[i];

	वापस ad_val / sharpsl_ad_index;
पूर्ण

/*
 * Take an array of 5 पूर्णांकegers, हटाओ the maximum and minimum values
 * and वापस the average.
 */
अटल पूर्णांक get_select_val(पूर्णांक *val)
अणु
	पूर्णांक i, j, k, temp, sum = 0;

	/* Find MAX val */
	temp = val[0];
	j = 0;
	क्रम (i = 1; i < 5; i++) अणु
		अगर (temp < val[i]) अणु
			temp = val[i];
			j = i;
		पूर्ण
	पूर्ण

	/* Find MIN val */
	temp = val[4];
	k = 4;
	क्रम (i = 3; i >= 0; i--) अणु
		अगर (temp > val[i]) अणु
			temp = val[i];
			k = i;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 5; i++)
		अगर (i != j && i != k)
			sum += val[i];

	dev_dbg(sharpsl_pm.dev, "Average: %d from values: %d, %d, %d, %d, %d\n", sum/3, val[0], val[1], val[2], val[3], val[4]);

	वापस sum/3;
पूर्ण

अटल पूर्णांक sharpsl_check_battery_temp(व्योम)
अणु
	पूर्णांक val, i, buff[5];

	/* Check battery temperature */
	क्रम (i = 0; i < 5; i++) अणु
		mdelay(SHARPSL_CHECK_BATTERY_WAIT_TIME_TEMP);
		sharpsl_pm.machinfo->measure_temp(1);
		mdelay(SHARPSL_CHECK_BATTERY_WAIT_TIME_TEMP);
		buff[i] = sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_BATT_TEMP);
		sharpsl_pm.machinfo->measure_temp(0);
	पूर्ण

	val = get_select_val(buff);

	dev_dbg(sharpsl_pm.dev, "Temperature: %d\n", val);
	अगर (val > sharpsl_pm.machinfo->अक्षरge_on_temp) अणु
		prपूर्णांकk(KERN_WARNING "Not charging: temperature out of limits.\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sharpsl_check_battery_voltage(व्योम)
अणु
	पूर्णांक val, i, buff[5];

	/* disable अक्षरge, enable disअक्षरge */
	sharpsl_pm.machinfo->अक्षरge(0);
	sharpsl_pm.machinfo->disअक्षरge(1);
	mdelay(SHARPSL_WAIT_DISCHARGE_ON);

	अगर (sharpsl_pm.machinfo->disअक्षरge1)
		sharpsl_pm.machinfo->disअक्षरge1(1);

	/* Check battery voltage */
	क्रम (i = 0; i < 5; i++) अणु
		buff[i] = sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_BATT_VOLT);
		mdelay(SHARPSL_CHECK_BATTERY_WAIT_TIME_VOLT);
	पूर्ण

	अगर (sharpsl_pm.machinfo->disअक्षरge1)
		sharpsl_pm.machinfo->disअक्षरge1(0);

	sharpsl_pm.machinfo->disअक्षरge(0);

	val = get_select_val(buff);
	dev_dbg(sharpsl_pm.dev, "Battery Voltage: %d\n", val);

	अगर (val < sharpsl_pm.machinfo->अक्षरge_on_volt)
		वापस -1;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sharpsl_ac_check(व्योम)
अणु
	पूर्णांक temp, i, buff[5];

	क्रम (i = 0; i < 5; i++) अणु
		buff[i] = sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_ACIN_VOLT);
		mdelay(SHARPSL_CHECK_BATTERY_WAIT_TIME_ACIN);
	पूर्ण

	temp = get_select_val(buff);
	dev_dbg(sharpsl_pm.dev, "AC Voltage: %d\n", temp);

	अगर ((temp > sharpsl_pm.machinfo->अक्षरge_acin_high) || (temp < sharpsl_pm.machinfo->अक्षरge_acin_low)) अणु
		dev_err(sharpsl_pm.dev, "Error: AC check failed: voltage %d.\n", temp);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sharpsl_pm_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	sharpsl_pm.flags |= SHARPSL_SUSPENDED;
	flush_delayed_work(&toggle_अक्षरger);
	flush_delayed_work(&sharpsl_bat);

	अगर (sharpsl_pm.अक्षरge_mode == CHRG_ON)
		sharpsl_pm.flags |= SHARPSL_DO_OFFLINE_CHRG;
	अन्यथा
		sharpsl_pm.flags &= ~SHARPSL_DO_OFFLINE_CHRG;

	वापस 0;
पूर्ण

अटल पूर्णांक sharpsl_pm_resume(काष्ठा platक्रमm_device *pdev)
अणु
	/* Clear the reset source indicators as they अवरोध the bootloader upon reboot */
	RCSR = 0x0f;
	sharpsl_average_clear();
	sharpsl_pm.flags &= ~SHARPSL_APM_QUEUED;
	sharpsl_pm.flags &= ~SHARPSL_SUSPENDED;

	वापस 0;
पूर्ण

अटल व्योम corgi_जाओ_sleep(अचिन्हित दीर्घ alarm_समय, अचिन्हित पूर्णांक alarm_enable, suspend_state_t state)
अणु
	dev_dbg(sharpsl_pm.dev, "Time is: %08x\n", RCNR);

	dev_dbg(sharpsl_pm.dev, "Offline Charge Activate = %d\n", sharpsl_pm.flags & SHARPSL_DO_OFFLINE_CHRG);
	/* not अक्षरging and AC-IN! */

	अगर ((sharpsl_pm.flags & SHARPSL_DO_OFFLINE_CHRG) && (sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_ACIN))) अणु
		dev_dbg(sharpsl_pm.dev, "Activating Offline Charger...\n");
		sharpsl_pm.अक्षरge_mode = CHRG_OFF;
		sharpsl_pm.flags &= ~SHARPSL_DO_OFFLINE_CHRG;
		sharpsl_off_अक्षरge_battery();
	पूर्ण

	sharpsl_pm.machinfo->presuspend();

	PEDR = 0xffffffff; /* clear it */

	sharpsl_pm.flags &= ~SHARPSL_ALARM_ACTIVE;
	अगर ((sharpsl_pm.अक्षरge_mode == CHRG_ON) && ((alarm_enable && ((alarm_समय - RCNR) > (SHARPSL_BATCHK_TIME_SUSPEND + 30))) || !alarm_enable)) अणु
		RTSR &= RTSR_ALE;
		RTAR = RCNR + SHARPSL_BATCHK_TIME_SUSPEND;
		dev_dbg(sharpsl_pm.dev, "Charging alarm at: %08x\n", RTAR);
		sharpsl_pm.flags |= SHARPSL_ALARM_ACTIVE;
	पूर्ण अन्यथा अगर (alarm_enable) अणु
		RTSR &= RTSR_ALE;
		RTAR = alarm_समय;
		dev_dbg(sharpsl_pm.dev, "User alarm at: %08x\n", RTAR);
	पूर्ण अन्यथा अणु
		dev_dbg(sharpsl_pm.dev, "No alarms set.\n");
	पूर्ण

	pxa_pm_enter(state);

	sharpsl_pm.machinfo->postsuspend();

	dev_dbg(sharpsl_pm.dev, "Corgi woken up from suspend: %08x\n", PEDR);
पूर्ण

अटल पूर्णांक corgi_enter_suspend(अचिन्हित दीर्घ alarm_समय, अचिन्हित पूर्णांक alarm_enable, suspend_state_t state)
अणु
	अगर (!sharpsl_pm.machinfo->should_wakeup(!(sharpsl_pm.flags & SHARPSL_ALARM_ACTIVE) && alarm_enable)) अणु
		अगर (!(sharpsl_pm.flags & SHARPSL_ALARM_ACTIVE)) अणु
			dev_dbg(sharpsl_pm.dev, "No user triggered wakeup events and not charging. Strange. Suspend.\n");
			corgi_जाओ_sleep(alarm_समय, alarm_enable, state);
			वापस 1;
		पूर्ण
		अगर (sharpsl_off_अक्षरge_battery()) अणु
			dev_dbg(sharpsl_pm.dev, "Charging. Suspend...\n");
			corgi_जाओ_sleep(alarm_समय, alarm_enable, state);
			वापस 1;
		पूर्ण
		dev_dbg(sharpsl_pm.dev, "User triggered wakeup in offline charger.\n");
	पूर्ण

	अगर ((!sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_LOCK)) ||
	    (!sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_FATAL)))	अणु
		dev_err(sharpsl_pm.dev, "Fatal condition. Suspend.\n");
		corgi_जाओ_sleep(alarm_समय, alarm_enable, state);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक corgi_pxa_pm_enter(suspend_state_t state)
अणु
	अचिन्हित दीर्घ alarm_समय = RTAR;
	अचिन्हित पूर्णांक alarm_status = ((RTSR & RTSR_ALE) != 0);

	dev_dbg(sharpsl_pm.dev, "SharpSL suspending for first time.\n");

	corgi_जाओ_sleep(alarm_समय, alarm_status, state);

	जबतक (corgi_enter_suspend(alarm_समय, alarm_status, state))
		अणुपूर्ण

	अगर (sharpsl_pm.machinfo->earlyresume)
		sharpsl_pm.machinfo->earlyresume();

	dev_dbg(sharpsl_pm.dev, "SharpSL resuming...\n");

	वापस 0;
पूर्ण

अटल पूर्णांक sharpsl_off_अक्षरge_error(व्योम)
अणु
	dev_err(sharpsl_pm.dev, "Offline Charger: Error occurred.\n");
	sharpsl_pm.machinfo->अक्षरge(0);
	sharpsl_pm_led(SHARPSL_LED_ERROR);
	sharpsl_pm.अक्षरge_mode = CHRG_ERROR;
	वापस 1;
पूर्ण

/*
 * Charging Control जबतक suspended
 * Return 1 - go straight to sleep
 * Return 0 - sleep or wakeup depending on other factors
 */
अटल पूर्णांक sharpsl_off_अक्षरge_battery(व्योम)
अणु
	पूर्णांक समय;

	dev_dbg(sharpsl_pm.dev, "Charge Mode: %d\n", sharpsl_pm.अक्षरge_mode);

	अगर (sharpsl_pm.अक्षरge_mode == CHRG_OFF) अणु
		dev_dbg(sharpsl_pm.dev, "Offline Charger: Step 1\n");

		/* AC Check */
		अगर ((sharpsl_ac_check() < 0) || (sharpsl_check_battery_temp() < 0))
			वापस sharpsl_off_अक्षरge_error();

		/* Start Charging */
		sharpsl_pm_led(SHARPSL_LED_ON);
		sharpsl_pm.machinfo->अक्षरge(0);
		mdelay(SHARPSL_CHARGE_WAIT_TIME);
		sharpsl_pm.machinfo->अक्षरge(1);

		sharpsl_pm.अक्षरge_mode = CHRG_ON;
		sharpsl_pm.full_count = 0;

		वापस 1;
	पूर्ण अन्यथा अगर (sharpsl_pm.अक्षरge_mode != CHRG_ON) अणु
		वापस 1;
	पूर्ण

	अगर (sharpsl_pm.full_count == 0) अणु
		पूर्णांक समय;

		dev_dbg(sharpsl_pm.dev, "Offline Charger: Step 2\n");

		अगर ((sharpsl_check_battery_temp() < 0) || (sharpsl_check_battery_voltage() < 0))
			वापस sharpsl_off_अक्षरge_error();

		sharpsl_pm.machinfo->अक्षरge(0);
		mdelay(SHARPSL_CHARGE_WAIT_TIME);
		sharpsl_pm.machinfo->अक्षरge(1);
		sharpsl_pm.अक्षरge_mode = CHRG_ON;

		mdelay(SHARPSL_CHARGE_CO_CHECK_TIME);

		समय = RCNR;
		जबतक (1) अणु
			/* Check अगर any wakeup event had occurred */
			अगर (sharpsl_pm.machinfo->अक्षरger_wakeup())
				वापस 0;
			/* Check क्रम समयout */
			अगर ((RCNR - समय) > SHARPSL_WAIT_CO_TIME)
				वापस 1;
			अगर (sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_CHRGFULL)) अणु
				dev_dbg(sharpsl_pm.dev, "Offline Charger: Charge full occurred. Retrying to check\n");
				sharpsl_pm.full_count++;
				sharpsl_pm.machinfo->अक्षरge(0);
				mdelay(SHARPSL_CHARGE_WAIT_TIME);
				sharpsl_pm.machinfo->अक्षरge(1);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_dbg(sharpsl_pm.dev, "Offline Charger: Step 3\n");

	mdelay(SHARPSL_CHARGE_CO_CHECK_TIME);

	समय = RCNR;
	जबतक (1) अणु
		/* Check अगर any wakeup event had occurred */
		अगर (sharpsl_pm.machinfo->अक्षरger_wakeup())
			वापस 0;
		/* Check क्रम समयout */
		अगर ((RCNR-समय) > SHARPSL_WAIT_CO_TIME) अणु
			अगर (sharpsl_pm.full_count > SHARPSL_CHARGE_RETRY_CNT) अणु
				dev_dbg(sharpsl_pm.dev, "Offline Charger: Not charged sufficiently. Retrying.\n");
				sharpsl_pm.full_count = 0;
			पूर्ण
			sharpsl_pm.full_count++;
			वापस 1;
		पूर्ण
		अगर (sharpsl_pm.machinfo->पढ़ो_devdata(SHARPSL_STATUS_CHRGFULL)) अणु
			dev_dbg(sharpsl_pm.dev, "Offline Charger: Charging complete.\n");
			sharpsl_pm_led(SHARPSL_LED_OFF);
			sharpsl_pm.machinfo->अक्षरge(0);
			sharpsl_pm.अक्षरge_mode = CHRG_DONE;
			वापस 1;
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा sharpsl_pm_suspend	शून्य
#घोषणा sharpsl_pm_resume	शून्य
#पूर्ण_अगर

अटल sमाप_प्रकार battery_percentage_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", sharpsl_pm.battstat.मुख्यbat_percent);
पूर्ण

अटल sमाप_प्रकार battery_voltage_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", sharpsl_pm.battstat.मुख्यbat_voltage);
पूर्ण

अटल DEVICE_ATTR_RO(battery_percentage);
अटल DEVICE_ATTR_RO(battery_voltage);

बाह्य व्योम (*apm_get_घातer_status)(काष्ठा apm_घातer_info *);

अटल व्योम sharpsl_apm_get_घातer_status(काष्ठा apm_घातer_info *info)
अणु
	info->ac_line_status = sharpsl_pm.battstat.ac_status;

	अगर (sharpsl_pm.अक्षरge_mode == CHRG_ON)
		info->battery_status = APM_BATTERY_STATUS_CHARGING;
	अन्यथा
		info->battery_status = sharpsl_pm.battstat.मुख्यbat_status;

	info->battery_flag = (1 << info->battery_status);
	info->battery_lअगरe = sharpsl_pm.battstat.मुख्यbat_percent;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा platक्रमm_suspend_ops sharpsl_pm_ops = अणु
	.prepare	= pxa_pm_prepare,
	.finish		= pxa_pm_finish,
	.enter		= corgi_pxa_pm_enter,
	.valid		= suspend_valid_only_mem,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक sharpsl_pm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, irq;

	अगर (!pdev->dev.platक्रमm_data)
		वापस -EINVAL;

	sharpsl_pm.dev = &pdev->dev;
	sharpsl_pm.machinfo = pdev->dev.platक्रमm_data;
	sharpsl_pm.अक्षरge_mode = CHRG_OFF;
	sharpsl_pm.flags = 0;

	समयr_setup(&sharpsl_pm.ac_समयr, sharpsl_ac_समयr, 0);

	समयr_setup(&sharpsl_pm.chrg_full_समयr, sharpsl_chrg_full_समयr, 0);

	led_trigger_रेजिस्टर_simple("sharpsl-charge", &sharpsl_अक्षरge_led_trigger);

	sharpsl_pm.machinfo->init();

	gpio_request(sharpsl_pm.machinfo->gpio_acin, "AC IN");
	gpio_direction_input(sharpsl_pm.machinfo->gpio_acin);
	gpio_request(sharpsl_pm.machinfo->gpio_batfull, "Battery Full");
	gpio_direction_input(sharpsl_pm.machinfo->gpio_batfull);
	gpio_request(sharpsl_pm.machinfo->gpio_batlock, "Battery Lock");
	gpio_direction_input(sharpsl_pm.machinfo->gpio_batlock);

	/* Register पूर्णांकerrupt handlers */
	irq = gpio_to_irq(sharpsl_pm.machinfo->gpio_acin);
	अगर (request_irq(irq, sharpsl_ac_isr, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "AC Input Detect", sharpsl_ac_isr)) अणु
		dev_err(sharpsl_pm.dev, "Could not get irq %d.\n", irq);
	पूर्ण

	irq = gpio_to_irq(sharpsl_pm.machinfo->gpio_batlock);
	अगर (request_irq(irq, sharpsl_fatal_isr, IRQF_TRIGGER_FALLING, "Battery Cover", sharpsl_fatal_isr)) अणु
		dev_err(sharpsl_pm.dev, "Could not get irq %d.\n", irq);
	पूर्ण

	अगर (sharpsl_pm.machinfo->gpio_fatal) अणु
		irq = gpio_to_irq(sharpsl_pm.machinfo->gpio_fatal);
		अगर (request_irq(irq, sharpsl_fatal_isr, IRQF_TRIGGER_FALLING, "Fatal Battery", sharpsl_fatal_isr)) अणु
			dev_err(sharpsl_pm.dev, "Could not get irq %d.\n", irq);
		पूर्ण
	पूर्ण

	अगर (sharpsl_pm.machinfo->batfull_irq) अणु
		/* Register पूर्णांकerrupt handler. */
		irq = gpio_to_irq(sharpsl_pm.machinfo->gpio_batfull);
		अगर (request_irq(irq, sharpsl_chrg_full_isr, IRQF_TRIGGER_RISING, "CO", sharpsl_chrg_full_isr)) अणु
			dev_err(sharpsl_pm.dev, "Could not get irq %d.\n", irq);
		पूर्ण
	पूर्ण

	ret = device_create_file(&pdev->dev, &dev_attr_battery_percentage);
	ret |= device_create_file(&pdev->dev, &dev_attr_battery_voltage);
	अगर (ret != 0)
		dev_warn(&pdev->dev, "Failed to register attributes (%d)\n", ret);

	apm_get_घातer_status = sharpsl_apm_get_घातer_status;

#अगर_घोषित CONFIG_PM
	suspend_set_ops(&sharpsl_pm_ops);
#पूर्ण_अगर

	mod_समयr(&sharpsl_pm.ac_समयr, jअगरfies + msecs_to_jअगरfies(250));

	वापस 0;
पूर्ण

अटल पूर्णांक sharpsl_pm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	suspend_set_ops(शून्य);

	device_हटाओ_file(&pdev->dev, &dev_attr_battery_percentage);
	device_हटाओ_file(&pdev->dev, &dev_attr_battery_voltage);

	led_trigger_unरेजिस्टर_simple(sharpsl_अक्षरge_led_trigger);

	मुक्त_irq(gpio_to_irq(sharpsl_pm.machinfo->gpio_acin), sharpsl_ac_isr);
	मुक्त_irq(gpio_to_irq(sharpsl_pm.machinfo->gpio_batlock), sharpsl_fatal_isr);

	अगर (sharpsl_pm.machinfo->gpio_fatal)
		मुक्त_irq(gpio_to_irq(sharpsl_pm.machinfo->gpio_fatal), sharpsl_fatal_isr);

	अगर (sharpsl_pm.machinfo->batfull_irq)
		मुक्त_irq(gpio_to_irq(sharpsl_pm.machinfo->gpio_batfull), sharpsl_chrg_full_isr);

	gpio_मुक्त(sharpsl_pm.machinfo->gpio_batlock);
	gpio_मुक्त(sharpsl_pm.machinfo->gpio_batfull);
	gpio_मुक्त(sharpsl_pm.machinfo->gpio_acin);

	अगर (sharpsl_pm.machinfo->निकास)
		sharpsl_pm.machinfo->निकास();

	del_समयr_sync(&sharpsl_pm.chrg_full_समयr);
	del_समयr_sync(&sharpsl_pm.ac_समयr);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sharpsl_pm_driver = अणु
	.probe		= sharpsl_pm_probe,
	.हटाओ		= sharpsl_pm_हटाओ,
	.suspend	= sharpsl_pm_suspend,
	.resume		= sharpsl_pm_resume,
	.driver		= अणु
		.name		= "sharpsl-pm",
	पूर्ण,
पूर्ण;

अटल पूर्णांक sharpsl_pm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sharpsl_pm_driver);
पूर्ण

अटल व्योम sharpsl_pm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sharpsl_pm_driver);
पूर्ण

late_initcall(sharpsl_pm_init);
module_निकास(sharpsl_pm_निकास);
