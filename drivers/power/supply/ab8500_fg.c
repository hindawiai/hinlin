<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2012
 *
 * Main and Back-up battery management driver.
 *
 * Note: Backup battery management is required in हाल of Li-Ion battery and not
 * क्रम capacitive battery. HREF boards have capacitive battery and hence backup
 * battery management is not used and the supported code is available in this
 * driver.
 *
 * Author:
 *	Johan Palsson <johan.palsson@stericsson.com>
 *	Karl Komierowski <karl.komierowski@stericsson.com>
 *	Arun R Murthy <arun.murthy@stericsson.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>
#समावेश <linux/समय64.h>
#समावेश <linux/of.h>
#समावेश <linux/completion.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/kernel.h>

#समावेश "ab8500-bm.h"

#घोषणा MILLI_TO_MICRO			1000
#घोषणा FG_LSB_IN_MA			1627
#घोषणा QLSB_न_अंकO_AMP_HOURS_X10		1071
#घोषणा INS_CURR_TIMEOUT		(3 * HZ)

#घोषणा SEC_TO_SAMPLE(S)		(S * 4)

#घोषणा NBR_AVG_SAMPLES			20

#घोषणा LOW_BAT_CHECK_INTERVAL		(HZ / 16) /* 62.5 ms */

#घोषणा VALID_CAPACITY_SEC		(45 * 60) /* 45 minutes */
#घोषणा BATT_OK_MIN			2360 /* mV */
#घोषणा BATT_OK_INCREMENT		50 /* mV */
#घोषणा BATT_OK_MAX_NR_INCREMENTS	0xE

/* FG स्थिरants */
#घोषणा BATT_OVV			0x01

#घोषणा पूर्णांकerpolate(x, x1, y1, x2, y2) \
	((y1) + ((((y2) - (y1)) * ((x) - (x1))) / ((x2) - (x1))));

/**
 * काष्ठा ab8500_fg_पूर्णांकerrupts - ab8500 fg पूर्णांकerupts
 * @name:	name of the पूर्णांकerrupt
 * @isr		function poपूर्णांकer to the isr
 */
काष्ठा ab8500_fg_पूर्णांकerrupts अणु
	अक्षर *name;
	irqवापस_t (*isr)(पूर्णांक irq, व्योम *data);
पूर्ण;

क्रमागत ab8500_fg_disअक्षरge_state अणु
	AB8500_FG_DISCHARGE_INIT,
	AB8500_FG_DISCHARGE_INITMEASURING,
	AB8500_FG_DISCHARGE_INIT_RECOVERY,
	AB8500_FG_DISCHARGE_RECOVERY,
	AB8500_FG_DISCHARGE_READOUT_INIT,
	AB8500_FG_DISCHARGE_READOUT,
	AB8500_FG_DISCHARGE_WAKEUP,
पूर्ण;

अटल अक्षर *disअक्षरge_state[] = अणु
	"DISCHARGE_INIT",
	"DISCHARGE_INITMEASURING",
	"DISCHARGE_INIT_RECOVERY",
	"DISCHARGE_RECOVERY",
	"DISCHARGE_READOUT_INIT",
	"DISCHARGE_READOUT",
	"DISCHARGE_WAKEUP",
पूर्ण;

क्रमागत ab8500_fg_अक्षरge_state अणु
	AB8500_FG_CHARGE_INIT,
	AB8500_FG_CHARGE_READOUT,
पूर्ण;

अटल अक्षर *अक्षरge_state[] = अणु
	"CHARGE_INIT",
	"CHARGE_READOUT",
पूर्ण;

क्रमागत ab8500_fg_calibration_state अणु
	AB8500_FG_CALIB_INIT,
	AB8500_FG_CALIB_WAIT,
	AB8500_FG_CALIB_END,
पूर्ण;

काष्ठा ab8500_fg_avg_cap अणु
	पूर्णांक avg;
	पूर्णांक samples[NBR_AVG_SAMPLES];
	समय64_t समय_stamps[NBR_AVG_SAMPLES];
	पूर्णांक pos;
	पूर्णांक nbr_samples;
	पूर्णांक sum;
पूर्ण;

काष्ठा ab8500_fg_cap_scaling अणु
	bool enable;
	पूर्णांक cap_to_scale[2];
	पूर्णांक disable_cap_level;
	पूर्णांक scaled_cap;
पूर्ण;

काष्ठा ab8500_fg_battery_capacity अणु
	पूर्णांक max_mah_design;
	पूर्णांक max_mah;
	पूर्णांक mah;
	पूर्णांक permille;
	पूर्णांक level;
	पूर्णांक prev_mah;
	पूर्णांक prev_percent;
	पूर्णांक prev_level;
	पूर्णांक user_mah;
	काष्ठा ab8500_fg_cap_scaling cap_scale;
पूर्ण;

काष्ठा ab8500_fg_flags अणु
	bool fg_enabled;
	bool conv_करोne;
	bool अक्षरging;
	bool fully_अक्षरged;
	bool क्रमce_full;
	bool low_bat_delay;
	bool low_bat;
	bool bat_ovv;
	bool batt_unknown;
	bool calibrate;
	bool user_cap;
	bool batt_id_received;
पूर्ण;

काष्ठा inst_curr_result_list अणु
	काष्ठा list_head list;
	पूर्णांक *result;
पूर्ण;

/**
 * काष्ठा ab8500_fg - ab8500 FG device inक्रमmation
 * @dev:		Poपूर्णांकer to the काष्ठाure device
 * @node:		a list of AB8500 FGs, hence prepared क्रम reentrance
 * @irq			holds the CCEOC पूर्णांकerrupt number
 * @vbat:		Battery voltage in mV
 * @vbat_nom:		Nominal battery voltage in mV
 * @inst_curr:		Instantenous battery current in mA
 * @avg_curr:		Average battery current in mA
 * @bat_temp		battery temperature
 * @fg_samples:		Number of samples used in the FG accumulation
 * @accu_अक्षरge:	Accumulated अक्षरge from the last conversion
 * @recovery_cnt:	Counter क्रम recovery mode
 * @high_curr_cnt:	Counter क्रम high current mode
 * @init_cnt:		Counter क्रम init mode
 * @low_bat_cnt		Counter क्रम number of consecutive low battery measures
 * @nbr_cceoc_irq_cnt	Counter क्रम number of CCEOC irqs received since enabled
 * @recovery_needed:	Indicate अगर recovery is needed
 * @high_curr_mode:	Indicate अगर we're in high current mode
 * @init_capacity:	Indicate अगर initial capacity measuring should be करोne
 * @turn_off_fg:	True अगर fg was off beक्रमe current measurement
 * @calib_state		State during offset calibration
 * @disअक्षरge_state:	Current disअक्षरge state
 * @अक्षरge_state:	Current अक्षरge state
 * @ab8500_fg_started	Completion काष्ठा used क्रम the instant current start
 * @ab8500_fg_complete	Completion काष्ठा used क्रम the instant current पढ़ोing
 * @flags:		Structure क्रम inक्रमmation about events triggered
 * @bat_cap:		Structure क्रम battery capacity specअगरic parameters
 * @avg_cap:		Average capacity filter
 * @parent:		Poपूर्णांकer to the काष्ठा ab8500
 * @मुख्य_bat_v:		ADC channel क्रम the मुख्य battery voltage
 * @bm:           	Platक्रमm specअगरic battery management inक्रमmation
 * @fg_psy:		Structure that holds the FG specअगरic battery properties
 * @fg_wq:		Work queue क्रम running the FG algorithm
 * @fg_periodic_work:	Work to run the FG algorithm periodically
 * @fg_low_bat_work:	Work to check low bat condition
 * @fg_reinit_work	Work used to reset and reinitialise the FG algorithm
 * @fg_work:		Work to run the FG algorithm instantly
 * @fg_acc_cur_work:	Work to पढ़ो the FG accumulator
 * @fg_check_hw_failure_work:	Work क्रम checking HW state
 * @cc_lock:		Mutex क्रम locking the CC
 * @fg_kobject:		Structure of type kobject
 */
काष्ठा ab8500_fg अणु
	काष्ठा device *dev;
	काष्ठा list_head node;
	पूर्णांक irq;
	पूर्णांक vbat;
	पूर्णांक vbat_nom;
	पूर्णांक inst_curr;
	पूर्णांक avg_curr;
	पूर्णांक bat_temp;
	पूर्णांक fg_samples;
	पूर्णांक accu_अक्षरge;
	पूर्णांक recovery_cnt;
	पूर्णांक high_curr_cnt;
	पूर्णांक init_cnt;
	पूर्णांक low_bat_cnt;
	पूर्णांक nbr_cceoc_irq_cnt;
	bool recovery_needed;
	bool high_curr_mode;
	bool init_capacity;
	bool turn_off_fg;
	क्रमागत ab8500_fg_calibration_state calib_state;
	क्रमागत ab8500_fg_disअक्षरge_state disअक्षरge_state;
	क्रमागत ab8500_fg_अक्षरge_state अक्षरge_state;
	काष्ठा completion ab8500_fg_started;
	काष्ठा completion ab8500_fg_complete;
	काष्ठा ab8500_fg_flags flags;
	काष्ठा ab8500_fg_battery_capacity bat_cap;
	काष्ठा ab8500_fg_avg_cap avg_cap;
	काष्ठा ab8500 *parent;
	काष्ठा iio_channel *मुख्य_bat_v;
	काष्ठा abx500_bm_data *bm;
	काष्ठा घातer_supply *fg_psy;
	काष्ठा workqueue_काष्ठा *fg_wq;
	काष्ठा delayed_work fg_periodic_work;
	काष्ठा delayed_work fg_low_bat_work;
	काष्ठा delayed_work fg_reinit_work;
	काष्ठा work_काष्ठा fg_work;
	काष्ठा work_काष्ठा fg_acc_cur_work;
	काष्ठा delayed_work fg_check_hw_failure_work;
	काष्ठा mutex cc_lock;
	काष्ठा kobject fg_kobject;
पूर्ण;
अटल LIST_HEAD(ab8500_fg_list);

/**
 * ab8500_fg_get() - वापसs a reference to the primary AB8500 fuel gauge
 * (i.e. the first fuel gauge in the instance list)
 */
काष्ठा ab8500_fg *ab8500_fg_get(व्योम)
अणु
	वापस list_first_entry_or_null(&ab8500_fg_list, काष्ठा ab8500_fg,
					node);
पूर्ण

/* Main battery properties */
अटल क्रमागत घातer_supply_property ab8500_fg_props[] = अणु
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_FULL,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
पूर्ण;

/*
 * This array maps the raw hex value to lowbat voltage used by the AB8500
 * Values taken from the UM0836
 */
अटल पूर्णांक ab8500_fg_lowbat_voltage_map[] = अणु
	2300 ,
	2325 ,
	2350 ,
	2375 ,
	2400 ,
	2425 ,
	2450 ,
	2475 ,
	2500 ,
	2525 ,
	2550 ,
	2575 ,
	2600 ,
	2625 ,
	2650 ,
	2675 ,
	2700 ,
	2725 ,
	2750 ,
	2775 ,
	2800 ,
	2825 ,
	2850 ,
	2875 ,
	2900 ,
	2925 ,
	2950 ,
	2975 ,
	3000 ,
	3025 ,
	3050 ,
	3075 ,
	3100 ,
	3125 ,
	3150 ,
	3175 ,
	3200 ,
	3225 ,
	3250 ,
	3275 ,
	3300 ,
	3325 ,
	3350 ,
	3375 ,
	3400 ,
	3425 ,
	3450 ,
	3475 ,
	3500 ,
	3525 ,
	3550 ,
	3575 ,
	3600 ,
	3625 ,
	3650 ,
	3675 ,
	3700 ,
	3725 ,
	3750 ,
	3775 ,
	3800 ,
	3825 ,
	3850 ,
	3850 ,
पूर्ण;

अटल u8 ab8500_volt_to_regval(पूर्णांक voltage)
अणु
	पूर्णांक i;

	अगर (voltage < ab8500_fg_lowbat_voltage_map[0])
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(ab8500_fg_lowbat_voltage_map); i++) अणु
		अगर (voltage < ab8500_fg_lowbat_voltage_map[i])
			वापस (u8) i - 1;
	पूर्ण

	/* If not captured above, वापस index of last element */
	वापस (u8) ARRAY_SIZE(ab8500_fg_lowbat_voltage_map) - 1;
पूर्ण

/**
 * ab8500_fg_is_low_curr() - Low or high current mode
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @curr:	the current to base or our decision on
 *
 * Low current mode अगर the current consumption is below a certain threshold
 */
अटल पूर्णांक ab8500_fg_is_low_curr(काष्ठा ab8500_fg *di, पूर्णांक curr)
अणु
	/*
	 * We want to know अगर we're in low current mode
	 */
	अगर (curr > -di->bm->fg_params->high_curr_threshold)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * ab8500_fg_add_cap_sample() - Add capacity to average filter
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @sample:	the capacity in mAh to add to the filter
 *
 * A capacity is added to the filter and a new mean capacity is calculated and
 * वापसed
 */
अटल पूर्णांक ab8500_fg_add_cap_sample(काष्ठा ab8500_fg *di, पूर्णांक sample)
अणु
	समय64_t now = kसमय_get_bootसमय_seconds();
	काष्ठा ab8500_fg_avg_cap *avg = &di->avg_cap;

	करो अणु
		avg->sum += sample - avg->samples[avg->pos];
		avg->samples[avg->pos] = sample;
		avg->समय_stamps[avg->pos] = now;
		avg->pos++;

		अगर (avg->pos == NBR_AVG_SAMPLES)
			avg->pos = 0;

		अगर (avg->nbr_samples < NBR_AVG_SAMPLES)
			avg->nbr_samples++;

		/*
		 * Check the समय stamp क्रम each sample. If too old,
		 * replace with latest sample
		 */
	पूर्ण जबतक (now - VALID_CAPACITY_SEC > avg->समय_stamps[avg->pos]);

	avg->avg = avg->sum / avg->nbr_samples;

	वापस avg->avg;
पूर्ण

/**
 * ab8500_fg_clear_cap_samples() - Clear average filter
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * The capacity filter is is reset to zero.
 */
अटल व्योम ab8500_fg_clear_cap_samples(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक i;
	काष्ठा ab8500_fg_avg_cap *avg = &di->avg_cap;

	avg->pos = 0;
	avg->nbr_samples = 0;
	avg->sum = 0;
	avg->avg = 0;

	क्रम (i = 0; i < NBR_AVG_SAMPLES; i++) अणु
		avg->samples[i] = 0;
		avg->समय_stamps[i] = 0;
	पूर्ण
पूर्ण

/**
 * ab8500_fg_fill_cap_sample() - Fill average filter
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @sample:	the capacity in mAh to fill the filter with
 *
 * The capacity filter is filled with a capacity in mAh
 */
अटल व्योम ab8500_fg_fill_cap_sample(काष्ठा ab8500_fg *di, पूर्णांक sample)
अणु
	पूर्णांक i;
	समय64_t now;
	काष्ठा ab8500_fg_avg_cap *avg = &di->avg_cap;

	now = kसमय_get_bootसमय_seconds();

	क्रम (i = 0; i < NBR_AVG_SAMPLES; i++) अणु
		avg->samples[i] = sample;
		avg->समय_stamps[i] = now;
	पूर्ण

	avg->pos = 0;
	avg->nbr_samples = NBR_AVG_SAMPLES;
	avg->sum = sample * NBR_AVG_SAMPLES;
	avg->avg = sample;
पूर्ण

/**
 * ab8500_fg_coulomb_counter() - enable coulomb counter
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @enable:	enable/disable
 *
 * Enable/Disable coulomb counter.
 * On failure वापसs negative value.
 */
अटल पूर्णांक ab8500_fg_coulomb_counter(काष्ठा ab8500_fg *di, bool enable)
अणु
	पूर्णांक ret = 0;
	mutex_lock(&di->cc_lock);
	अगर (enable) अणु
		/* To be able to reprogram the number of samples, we have to
		 * first stop the CC and then enable it again */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8500_RTC_CC_CONF_REG, 0x00);
		अगर (ret)
			जाओ cc_err;

		/* Program the samples */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_NCOV_ACCU,
			di->fg_samples);
		अगर (ret)
			जाओ cc_err;

		/* Start the CC */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8500_RTC_CC_CONF_REG,
			(CC_DEEP_SLEEP_ENA | CC_PWR_UP_ENA));
		अगर (ret)
			जाओ cc_err;

		di->flags.fg_enabled = true;
	पूर्ण अन्यथा अणु
		/* Clear any pending पढ़ो requests */
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG,
			(RESET_ACCU | READ_REQ), 0);
		अगर (ret)
			जाओ cc_err;

		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_NCOV_ACCU_CTRL, 0);
		अगर (ret)
			जाओ cc_err;

		/* Stop the CC */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8500_RTC_CC_CONF_REG, 0);
		अगर (ret)
			जाओ cc_err;

		di->flags.fg_enabled = false;

	पूर्ण
	dev_dbg(di->dev, " CC enabled: %d Samples: %d\n",
		enable, di->fg_samples);

	mutex_unlock(&di->cc_lock);

	वापस ret;
cc_err:
	dev_err(di->dev, "%s Enabling coulomb counter failed\n", __func__);
	mutex_unlock(&di->cc_lock);
	वापस ret;
पूर्ण

/**
 * ab8500_fg_inst_curr_start() - start battery instantaneous current
 * @di:         poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns 0 or error code
 * Note: This is part "one" and has to be called beक्रमe
 * ab8500_fg_inst_curr_finalize()
 */
पूर्णांक ab8500_fg_inst_curr_start(काष्ठा ab8500_fg *di)
अणु
	u8 reg_val;
	पूर्णांक ret;

	mutex_lock(&di->cc_lock);

	di->nbr_cceoc_irq_cnt = 0;
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
		AB8500_RTC_CC_CONF_REG, &reg_val);
	अगर (ret < 0)
		जाओ fail;

	अगर (!(reg_val & CC_PWR_UP_ENA)) अणु
		dev_dbg(di->dev, "%s Enable FG\n", __func__);
		di->turn_off_fg = true;

		/* Program the samples */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_NCOV_ACCU,
			SEC_TO_SAMPLE(10));
		अगर (ret)
			जाओ fail;

		/* Start the CC */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8500_RTC_CC_CONF_REG,
			(CC_DEEP_SLEEP_ENA | CC_PWR_UP_ENA));
		अगर (ret)
			जाओ fail;
	पूर्ण अन्यथा अणु
		di->turn_off_fg = false;
	पूर्ण

	/* Return and WFI */
	reinit_completion(&di->ab8500_fg_started);
	reinit_completion(&di->ab8500_fg_complete);
	enable_irq(di->irq);

	/* Note: cc_lock is still locked */
	वापस 0;
fail:
	mutex_unlock(&di->cc_lock);
	वापस ret;
पूर्ण

/**
 * ab8500_fg_inst_curr_started() - check अगर fg conversion has started
 * @di:         poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns 1 अगर conversion started, 0 अगर still रुकोing
 */
पूर्णांक ab8500_fg_inst_curr_started(काष्ठा ab8500_fg *di)
अणु
	वापस completion_करोne(&di->ab8500_fg_started);
पूर्ण

/**
 * ab8500_fg_inst_curr_करोne() - check अगर fg conversion is करोne
 * @di:         poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns 1 अगर conversion करोne, 0 अगर still रुकोing
 */
पूर्णांक ab8500_fg_inst_curr_करोne(काष्ठा ab8500_fg *di)
अणु
	वापस completion_करोne(&di->ab8500_fg_complete);
पूर्ण

/**
 * ab8500_fg_inst_curr_finalize() - battery instantaneous current
 * @di:         poपूर्णांकer to the ab8500_fg काष्ठाure
 * @res:	battery instantenous current(on success)
 *
 * Returns 0 or an error code
 * Note: This is part "two" and has to be called at earliest 250 ms
 * after ab8500_fg_inst_curr_start()
 */
पूर्णांक ab8500_fg_inst_curr_finalize(काष्ठा ab8500_fg *di, पूर्णांक *res)
अणु
	u8 low, high;
	पूर्णांक val;
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;

	अगर (!completion_करोne(&di->ab8500_fg_complete)) अणु
		समयout = रुको_क्रम_completion_समयout(
			&di->ab8500_fg_complete,
			INS_CURR_TIMEOUT);
		dev_dbg(di->dev, "Finalize time: %d ms\n",
			jअगरfies_to_msecs(INS_CURR_TIMEOUT - समयout));
		अगर (!समयout) अणु
			ret = -ETIME;
			disable_irq(di->irq);
			di->nbr_cceoc_irq_cnt = 0;
			dev_err(di->dev, "completion timed out [%d]\n",
				__LINE__);
			जाओ fail;
		पूर्ण
	पूर्ण

	disable_irq(di->irq);
	di->nbr_cceoc_irq_cnt = 0;

	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG,
			READ_REQ, READ_REQ);

	/* 100uS between पढ़ो request and पढ़ो is needed */
	usleep_range(100, 100);

	/* Read CC Sample conversion value Low and high */
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_GAS_GAUGE,
		AB8500_GASG_CC_SMPL_CNVL_REG,  &low);
	अगर (ret < 0)
		जाओ fail;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_GAS_GAUGE,
		AB8500_GASG_CC_SMPL_CNVH_REG,  &high);
	अगर (ret < 0)
		जाओ fail;

	/*
	 * negative value क्रम Disअक्षरging
	 * convert 2's complement पूर्णांकo decimal
	 */
	अगर (high & 0x10)
		val = (low | (high << 8) | 0xFFFFE000);
	अन्यथा
		val = (low | (high << 8));

	/*
	 * Convert to unit value in mA
	 * Full scale input voltage is
	 * 63.160mV => LSB = 63.160mV/(4096*res) = 1.542mA
	 * Given a 250ms conversion cycle समय the LSB corresponds
	 * to 107.1 nAh. Convert to current by भागiding by the conversion
	 * समय in hours (250ms = 1 / (3600 * 4)h)
	 * 107.1nAh assumes 10mOhm, but fg_res is in 0.1mOhm
	 */
	val = (val * QLSB_न_अंकO_AMP_HOURS_X10 * 36 * 4) /
		(1000 * di->bm->fg_res);

	अगर (di->turn_off_fg) अणु
		dev_dbg(di->dev, "%s Disable FG\n", __func__);

		/* Clear any pending पढ़ो requests */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG, 0);
		अगर (ret)
			जाओ fail;

		/* Stop the CC */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8500_RTC_CC_CONF_REG, 0);
		अगर (ret)
			जाओ fail;
	पूर्ण
	mutex_unlock(&di->cc_lock);
	(*res) = val;

	वापस 0;
fail:
	mutex_unlock(&di->cc_lock);
	वापस ret;
पूर्ण

/**
 * ab8500_fg_inst_curr_blocking() - battery instantaneous current
 * @di:         poपूर्णांकer to the ab8500_fg काष्ठाure
 * @res:	battery instantenous current(on success)
 *
 * Returns 0 अन्यथा error code
 */
पूर्णांक ab8500_fg_inst_curr_blocking(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	पूर्णांक res = 0;

	ret = ab8500_fg_inst_curr_start(di);
	अगर (ret) अणु
		dev_err(di->dev, "Failed to initialize fg_inst\n");
		वापस 0;
	पूर्ण

	/* Wait क्रम CC to actually start */
	अगर (!completion_करोne(&di->ab8500_fg_started)) अणु
		समयout = रुको_क्रम_completion_समयout(
			&di->ab8500_fg_started,
			INS_CURR_TIMEOUT);
		dev_dbg(di->dev, "Start time: %d ms\n",
			jअगरfies_to_msecs(INS_CURR_TIMEOUT - समयout));
		अगर (!समयout) अणु
			ret = -ETIME;
			dev_err(di->dev, "completion timed out [%d]\n",
				__LINE__);
			जाओ fail;
		पूर्ण
	पूर्ण

	ret = ab8500_fg_inst_curr_finalize(di, &res);
	अगर (ret) अणु
		dev_err(di->dev, "Failed to finalize fg_inst\n");
		वापस 0;
	पूर्ण

	dev_dbg(di->dev, "%s instant current: %d", __func__, res);
	वापस res;
fail:
	disable_irq(di->irq);
	mutex_unlock(&di->cc_lock);
	वापस ret;
पूर्ण

/**
 * ab8500_fg_acc_cur_work() - average battery current
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Updated the average battery current obtained from the
 * coulomb counter.
 */
अटल व्योम ab8500_fg_acc_cur_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक val;
	पूर्णांक ret;
	u8 low, med, high;

	काष्ठा ab8500_fg *di = container_of(work,
		काष्ठा ab8500_fg, fg_acc_cur_work);

	mutex_lock(&di->cc_lock);
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_GAS_GAUGE,
		AB8500_GASG_CC_NCOV_ACCU_CTRL, RD_NCONV_ACCU_REQ);
	अगर (ret)
		जाओ निकास;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_GAS_GAUGE,
		AB8500_GASG_CC_NCOV_ACCU_LOW,  &low);
	अगर (ret < 0)
		जाओ निकास;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_GAS_GAUGE,
		AB8500_GASG_CC_NCOV_ACCU_MED,  &med);
	अगर (ret < 0)
		जाओ निकास;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_GAS_GAUGE,
		AB8500_GASG_CC_NCOV_ACCU_HIGH, &high);
	अगर (ret < 0)
		जाओ निकास;

	/* Check क्रम sign bit in हाल of negative value, 2's complement */
	अगर (high & 0x10)
		val = (low | (med << 8) | (high << 16) | 0xFFE00000);
	अन्यथा
		val = (low | (med << 8) | (high << 16));

	/*
	 * Convert to uAh
	 * Given a 250ms conversion cycle समय the LSB corresponds
	 * to 112.9 nAh.
	 * 112.9nAh assumes 10mOhm, but fg_res is in 0.1mOhm
	 */
	di->accu_अक्षरge = (val * QLSB_न_अंकO_AMP_HOURS_X10) /
		(100 * di->bm->fg_res);

	/*
	 * Convert to unit value in mA
	 * by भागiding by the conversion
	 * समय in hours (= samples / (3600 * 4)h)
	 * and multiply with 1000
	 */
	di->avg_curr = (val * QLSB_न_अंकO_AMP_HOURS_X10 * 36) /
		(1000 * di->bm->fg_res * (di->fg_samples / 4));

	di->flags.conv_करोne = true;

	mutex_unlock(&di->cc_lock);

	queue_work(di->fg_wq, &di->fg_work);

	dev_dbg(di->dev, "fg_res: %d, fg_samples: %d, gasg: %d, accu_charge: %d \n",
				di->bm->fg_res, di->fg_samples, val, di->accu_अक्षरge);
	वापस;
निकास:
	dev_err(di->dev,
		"Failed to read or write gas gauge registers\n");
	mutex_unlock(&di->cc_lock);
	queue_work(di->fg_wq, &di->fg_work);
पूर्ण

/**
 * ab8500_fg_bat_voltage() - get battery voltage
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns battery voltage(on success) अन्यथा error code
 */
अटल पूर्णांक ab8500_fg_bat_voltage(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक vbat, ret;
	अटल पूर्णांक prev;

	ret = iio_पढ़ो_channel_processed(di->मुख्य_bat_v, &vbat);
	अगर (ret < 0) अणु
		dev_err(di->dev,
			"%s ADC conversion failed, using previous value\n",
			__func__);
		वापस prev;
	पूर्ण

	prev = vbat;
	वापस vbat;
पूर्ण

/**
 * ab8500_fg_volt_to_capacity() - Voltage based capacity
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @voltage:	The voltage to convert to a capacity
 *
 * Returns battery capacity in per mille based on voltage
 */
अटल पूर्णांक ab8500_fg_volt_to_capacity(काष्ठा ab8500_fg *di, पूर्णांक voltage)
अणु
	पूर्णांक i, tbl_size;
	स्थिर काष्ठा abx500_v_to_cap *tbl;
	पूर्णांक cap = 0;

	tbl = di->bm->bat_type[di->bm->batt_id].v_to_cap_tbl;
	tbl_size = di->bm->bat_type[di->bm->batt_id].n_v_cap_tbl_elements;

	क्रम (i = 0; i < tbl_size; ++i) अणु
		अगर (voltage > tbl[i].voltage)
			अवरोध;
	पूर्ण

	अगर ((i > 0) && (i < tbl_size)) अणु
		cap = पूर्णांकerpolate(voltage,
			tbl[i].voltage,
			tbl[i].capacity * 10,
			tbl[i-1].voltage,
			tbl[i-1].capacity * 10);
	पूर्ण अन्यथा अगर (i == 0) अणु
		cap = 1000;
	पूर्ण अन्यथा अणु
		cap = 0;
	पूर्ण

	dev_dbg(di->dev, "%s Vbat: %d, Cap: %d per mille",
		__func__, voltage, cap);

	वापस cap;
पूर्ण

/**
 * ab8500_fg_uncomp_volt_to_capacity() - Uncompensated voltage based capacity
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns battery capacity based on battery voltage that is not compensated
 * क्रम the voltage drop due to the load
 */
अटल पूर्णांक ab8500_fg_uncomp_volt_to_capacity(काष्ठा ab8500_fg *di)
अणु
	di->vbat = ab8500_fg_bat_voltage(di);
	वापस ab8500_fg_volt_to_capacity(di, di->vbat);
पूर्ण

/**
 * ab8500_fg_battery_resistance() - Returns the battery inner resistance
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns battery inner resistance added with the fuel gauge resistor value
 * to get the total resistance in the whole link from gnd to bat+ node.
 */
अटल पूर्णांक ab8500_fg_battery_resistance(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक i, tbl_size;
	स्थिर काष्ठा batres_vs_temp *tbl;
	पूर्णांक resist = 0;

	tbl = di->bm->bat_type[di->bm->batt_id].batres_tbl;
	tbl_size = di->bm->bat_type[di->bm->batt_id].n_batres_tbl_elements;

	क्रम (i = 0; i < tbl_size; ++i) अणु
		अगर (di->bat_temp / 10 > tbl[i].temp)
			अवरोध;
	पूर्ण

	अगर ((i > 0) && (i < tbl_size)) अणु
		resist = पूर्णांकerpolate(di->bat_temp / 10,
			tbl[i].temp,
			tbl[i].resist,
			tbl[i-1].temp,
			tbl[i-1].resist);
	पूर्ण अन्यथा अगर (i == 0) अणु
		resist = tbl[0].resist;
	पूर्ण अन्यथा अणु
		resist = tbl[tbl_size - 1].resist;
	पूर्ण

	dev_dbg(di->dev, "%s Temp: %d battery internal resistance: %d"
	    " fg resistance %d, total: %d (mOhm)\n",
		__func__, di->bat_temp, resist, di->bm->fg_res / 10,
		(di->bm->fg_res / 10) + resist);

	/* fg_res variable is in 0.1mOhm */
	resist += di->bm->fg_res / 10;

	वापस resist;
पूर्ण

/**
 * ab8500_fg_load_comp_volt_to_capacity() - Load compensated voltage based capacity
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns battery capacity based on battery voltage that is load compensated
 * क्रम the voltage drop
 */
अटल पूर्णांक ab8500_fg_load_comp_volt_to_capacity(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक vbat_comp, res;
	पूर्णांक i = 0;
	पूर्णांक vbat = 0;

	ab8500_fg_inst_curr_start(di);

	करो अणु
		vbat += ab8500_fg_bat_voltage(di);
		i++;
		usleep_range(5000, 6000);
	पूर्ण जबतक (!ab8500_fg_inst_curr_करोne(di));

	ab8500_fg_inst_curr_finalize(di, &di->inst_curr);

	di->vbat = vbat / i;
	res = ab8500_fg_battery_resistance(di);

	/* Use Ohms law to get the load compensated voltage */
	vbat_comp = di->vbat - (di->inst_curr * res) / 1000;

	dev_dbg(di->dev, "%s Measured Vbat: %dmV,Compensated Vbat %dmV, "
		"R: %dmOhm, Current: %dmA Vbat Samples: %d\n",
		__func__, di->vbat, vbat_comp, res, di->inst_curr, i);

	वापस ab8500_fg_volt_to_capacity(di, vbat_comp);
पूर्ण

/**
 * ab8500_fg_convert_mah_to_permille() - Capacity in mAh to permille
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @cap_mah:	capacity in mAh
 *
 * Converts capacity in mAh to capacity in permille
 */
अटल पूर्णांक ab8500_fg_convert_mah_to_permille(काष्ठा ab8500_fg *di, पूर्णांक cap_mah)
अणु
	वापस (cap_mah * 1000) / di->bat_cap.max_mah_design;
पूर्ण

/**
 * ab8500_fg_convert_permille_to_mah() - Capacity in permille to mAh
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @cap_pm:	capacity in permille
 *
 * Converts capacity in permille to capacity in mAh
 */
अटल पूर्णांक ab8500_fg_convert_permille_to_mah(काष्ठा ab8500_fg *di, पूर्णांक cap_pm)
अणु
	वापस cap_pm * di->bat_cap.max_mah_design / 1000;
पूर्ण

/**
 * ab8500_fg_convert_mah_to_uwh() - Capacity in mAh to uWh
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @cap_mah:	capacity in mAh
 *
 * Converts capacity in mAh to capacity in uWh
 */
अटल पूर्णांक ab8500_fg_convert_mah_to_uwh(काष्ठा ab8500_fg *di, पूर्णांक cap_mah)
अणु
	u64 भाग_res;
	u32 भाग_rem;

	भाग_res = ((u64) cap_mah) * ((u64) di->vbat_nom);
	भाग_rem = करो_भाग(भाग_res, 1000);

	/* Make sure to round upwards अगर necessary */
	अगर (भाग_rem >= 1000 / 2)
		भाग_res++;

	वापस (पूर्णांक) भाग_res;
पूर्ण

/**
 * ab8500_fg_calc_cap_अक्षरging() - Calculate reमुख्यing capacity जबतक अक्षरging
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Return the capacity in mAh based on previous calculated capcity and the FG
 * accumulator रेजिस्टर value. The filter is filled with this capacity
 */
अटल पूर्णांक ab8500_fg_calc_cap_अक्षरging(काष्ठा ab8500_fg *di)
अणु
	dev_dbg(di->dev, "%s cap_mah %d accu_charge %d\n",
		__func__,
		di->bat_cap.mah,
		di->accu_अक्षरge);

	/* Capacity should not be less than 0 */
	अगर (di->bat_cap.mah + di->accu_अक्षरge > 0)
		di->bat_cap.mah += di->accu_अक्षरge;
	अन्यथा
		di->bat_cap.mah = 0;
	/*
	 * We क्रमce capacity to 100% once when the algorithm
	 * reports that it's full.
	 */
	अगर (di->bat_cap.mah >= di->bat_cap.max_mah_design ||
		di->flags.क्रमce_full) अणु
		di->bat_cap.mah = di->bat_cap.max_mah_design;
	पूर्ण

	ab8500_fg_fill_cap_sample(di, di->bat_cap.mah);
	di->bat_cap.permille =
		ab8500_fg_convert_mah_to_permille(di, di->bat_cap.mah);

	/* We need to update battery voltage and inst current when अक्षरging */
	di->vbat = ab8500_fg_bat_voltage(di);
	di->inst_curr = ab8500_fg_inst_curr_blocking(di);

	वापस di->bat_cap.mah;
पूर्ण

/**
 * ab8500_fg_calc_cap_disअक्षरge_voltage() - Capacity in disअक्षरge with voltage
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @comp:	अगर voltage should be load compensated beक्रमe capacity calc
 *
 * Return the capacity in mAh based on the battery voltage. The voltage can
 * either be load compensated or not. This value is added to the filter and a
 * new mean value is calculated and वापसed.
 */
अटल पूर्णांक ab8500_fg_calc_cap_disअक्षरge_voltage(काष्ठा ab8500_fg *di, bool comp)
अणु
	पूर्णांक permille, mah;

	अगर (comp)
		permille = ab8500_fg_load_comp_volt_to_capacity(di);
	अन्यथा
		permille = ab8500_fg_uncomp_volt_to_capacity(di);

	mah = ab8500_fg_convert_permille_to_mah(di, permille);

	di->bat_cap.mah = ab8500_fg_add_cap_sample(di, mah);
	di->bat_cap.permille =
		ab8500_fg_convert_mah_to_permille(di, di->bat_cap.mah);

	वापस di->bat_cap.mah;
पूर्ण

/**
 * ab8500_fg_calc_cap_disअक्षरge_fg() - Capacity in disअक्षरge with FG
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Return the capacity in mAh based on previous calculated capcity and the FG
 * accumulator रेजिस्टर value. This value is added to the filter and a
 * new mean value is calculated and वापसed.
 */
अटल पूर्णांक ab8500_fg_calc_cap_disअक्षरge_fg(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक permille_volt, permille;

	dev_dbg(di->dev, "%s cap_mah %d accu_charge %d\n",
		__func__,
		di->bat_cap.mah,
		di->accu_अक्षरge);

	/* Capacity should not be less than 0 */
	अगर (di->bat_cap.mah + di->accu_अक्षरge > 0)
		di->bat_cap.mah += di->accu_अक्षरge;
	अन्यथा
		di->bat_cap.mah = 0;

	अगर (di->bat_cap.mah >= di->bat_cap.max_mah_design)
		di->bat_cap.mah = di->bat_cap.max_mah_design;

	/*
	 * Check against voltage based capacity. It can not be lower
	 * than what the uncompensated voltage says
	 */
	permille = ab8500_fg_convert_mah_to_permille(di, di->bat_cap.mah);
	permille_volt = ab8500_fg_uncomp_volt_to_capacity(di);

	अगर (permille < permille_volt) अणु
		di->bat_cap.permille = permille_volt;
		di->bat_cap.mah = ab8500_fg_convert_permille_to_mah(di,
			di->bat_cap.permille);

		dev_dbg(di->dev, "%s voltage based: perm %d perm_volt %d\n",
			__func__,
			permille,
			permille_volt);

		ab8500_fg_fill_cap_sample(di, di->bat_cap.mah);
	पूर्ण अन्यथा अणु
		ab8500_fg_fill_cap_sample(di, di->bat_cap.mah);
		di->bat_cap.permille =
			ab8500_fg_convert_mah_to_permille(di, di->bat_cap.mah);
	पूर्ण

	वापस di->bat_cap.mah;
पूर्ण

/**
 * ab8500_fg_capacity_level() - Get the battery capacity level
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Get the battery capacity level based on the capacity in percent
 */
अटल पूर्णांक ab8500_fg_capacity_level(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक ret, percent;

	percent = DIV_ROUND_CLOSEST(di->bat_cap.permille, 10);

	अगर (percent <= di->bm->cap_levels->critical ||
		di->flags.low_bat)
		ret = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
	अन्यथा अगर (percent <= di->bm->cap_levels->low)
		ret = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
	अन्यथा अगर (percent <= di->bm->cap_levels->normal)
		ret = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
	अन्यथा अगर (percent <= di->bm->cap_levels->high)
		ret = POWER_SUPPLY_CAPACITY_LEVEL_HIGH;
	अन्यथा
		ret = POWER_SUPPLY_CAPACITY_LEVEL_FULL;

	वापस ret;
पूर्ण

/**
 * ab8500_fg_calculate_scaled_capacity() - Capacity scaling
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Calculates the capacity to be shown to upper layers. Scales the capacity
 * to have 100% as a reference from the actual capacity upon removal of अक्षरger
 * when अक्षरging is in मुख्यtenance mode.
 */
अटल पूर्णांक ab8500_fg_calculate_scaled_capacity(काष्ठा ab8500_fg *di)
अणु
	काष्ठा ab8500_fg_cap_scaling *cs = &di->bat_cap.cap_scale;
	पूर्णांक capacity = di->bat_cap.prev_percent;

	अगर (!cs->enable)
		वापस capacity;

	/*
	 * As दीर्घ as we are in fully अक्षरge mode scale the capacity
	 * to show 100%.
	 */
	अगर (di->flags.fully_अक्षरged) अणु
		cs->cap_to_scale[0] = 100;
		cs->cap_to_scale[1] =
			max(capacity, di->bm->fg_params->मुख्यt_thres);
		dev_dbg(di->dev, "Scale cap with %d/%d\n",
			 cs->cap_to_scale[0], cs->cap_to_scale[1]);
	पूर्ण

	/* Calculates the scaled capacity. */
	अगर ((cs->cap_to_scale[0] != cs->cap_to_scale[1])
					&& (cs->cap_to_scale[1] > 0))
		capacity = min(100,
				 DIV_ROUND_CLOSEST(di->bat_cap.prev_percent *
						 cs->cap_to_scale[0],
						 cs->cap_to_scale[1]));

	अगर (di->flags.अक्षरging) अणु
		अगर (capacity < cs->disable_cap_level) अणु
			cs->disable_cap_level = capacity;
			dev_dbg(di->dev, "Cap to stop scale lowered %d%%\n",
				cs->disable_cap_level);
		पूर्ण अन्यथा अगर (!di->flags.fully_अक्षरged) अणु
			अगर (di->bat_cap.prev_percent >=
			    cs->disable_cap_level) अणु
				dev_dbg(di->dev, "Disabling scaled capacity\n");
				cs->enable = false;
				capacity = di->bat_cap.prev_percent;
			पूर्ण अन्यथा अणु
				dev_dbg(di->dev,
					"Waiting in cap to level %d%%\n",
					cs->disable_cap_level);
				capacity = cs->disable_cap_level;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस capacity;
पूर्ण

/**
 * ab8500_fg_update_cap_scalers() - Capacity scaling
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * To be called when state change from अक्षरge<->disअक्षरge to update
 * the capacity scalers.
 */
अटल व्योम ab8500_fg_update_cap_scalers(काष्ठा ab8500_fg *di)
अणु
	काष्ठा ab8500_fg_cap_scaling *cs = &di->bat_cap.cap_scale;

	अगर (!cs->enable)
		वापस;
	अगर (di->flags.अक्षरging) अणु
		di->bat_cap.cap_scale.disable_cap_level =
			di->bat_cap.cap_scale.scaled_cap;
		dev_dbg(di->dev, "Cap to stop scale at charge %d%%\n",
				di->bat_cap.cap_scale.disable_cap_level);
	पूर्ण अन्यथा अणु
		अगर (cs->scaled_cap != 100) अणु
			cs->cap_to_scale[0] = cs->scaled_cap;
			cs->cap_to_scale[1] = di->bat_cap.prev_percent;
		पूर्ण अन्यथा अणु
			cs->cap_to_scale[0] = 100;
			cs->cap_to_scale[1] =
				max(di->bat_cap.prev_percent,
				    di->bm->fg_params->मुख्यt_thres);
		पूर्ण

		dev_dbg(di->dev, "Cap to scale at discharge %d/%d\n",
				cs->cap_to_scale[0], cs->cap_to_scale[1]);
	पूर्ण
पूर्ण

/**
 * ab8500_fg_check_capacity_limits() - Check अगर capacity has changed
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 * @init:	capacity is allowed to go up in init mode
 *
 * Check अगर capacity or capacity limit has changed and notअगरy the प्रणाली
 * about it using the घातer_supply framework
 */
अटल व्योम ab8500_fg_check_capacity_limits(काष्ठा ab8500_fg *di, bool init)
अणु
	bool changed = false;
	पूर्णांक percent = DIV_ROUND_CLOSEST(di->bat_cap.permille, 10);

	di->bat_cap.level = ab8500_fg_capacity_level(di);

	अगर (di->bat_cap.level != di->bat_cap.prev_level) अणु
		/*
		 * We करो not allow reported capacity level to go up
		 * unless we're charging or if we're in init
		 */
		अगर (!(!di->flags.अक्षरging && di->bat_cap.level >
			di->bat_cap.prev_level) || init) अणु
			dev_dbg(di->dev, "level changed from %d to %d\n",
				di->bat_cap.prev_level,
				di->bat_cap.level);
			di->bat_cap.prev_level = di->bat_cap.level;
			changed = true;
		पूर्ण अन्यथा अणु
			dev_dbg(di->dev, "level not allowed to go up "
				"since no charger is connected: %d to %d\n",
				di->bat_cap.prev_level,
				di->bat_cap.level);
		पूर्ण
	पूर्ण

	/*
	 * If we have received the LOW_BAT IRQ, set capacity to 0 to initiate
	 * shutकरोwn
	 */
	अगर (di->flags.low_bat) अणु
		dev_dbg(di->dev, "Battery low, set capacity to 0\n");
		di->bat_cap.prev_percent = 0;
		di->bat_cap.permille = 0;
		percent = 0;
		di->bat_cap.prev_mah = 0;
		di->bat_cap.mah = 0;
		changed = true;
	पूर्ण अन्यथा अगर (di->flags.fully_अक्षरged) अणु
		/*
		 * We report 100% अगर algorithm reported fully अक्षरged
		 * and show 100% during मुख्यtenance अक्षरging (scaling).
		 */
		अगर (di->flags.क्रमce_full) अणु
			di->bat_cap.prev_percent = percent;
			di->bat_cap.prev_mah = di->bat_cap.mah;

			changed = true;

			अगर (!di->bat_cap.cap_scale.enable &&
						di->bm->capacity_scaling) अणु
				di->bat_cap.cap_scale.enable = true;
				di->bat_cap.cap_scale.cap_to_scale[0] = 100;
				di->bat_cap.cap_scale.cap_to_scale[1] =
						di->bat_cap.prev_percent;
				di->bat_cap.cap_scale.disable_cap_level = 100;
			पूर्ण
		पूर्ण अन्यथा अगर (di->bat_cap.prev_percent != percent) अणु
			dev_dbg(di->dev,
				"battery reported full "
				"but capacity dropping: %d\n",
				percent);
			di->bat_cap.prev_percent = percent;
			di->bat_cap.prev_mah = di->bat_cap.mah;

			changed = true;
		पूर्ण
	पूर्ण अन्यथा अगर (di->bat_cap.prev_percent != percent) अणु
		अगर (percent == 0) अणु
			/*
			 * We will not report 0% unless we've got
			 * the LOW_BAT IRQ, no matter what the FG
			 * algorithm says.
			 */
			di->bat_cap.prev_percent = 1;
			percent = 1;

			changed = true;
		पूर्ण अन्यथा अगर (!(!di->flags.अक्षरging &&
			percent > di->bat_cap.prev_percent) || init) अणु
			/*
			 * We करो not allow reported capacity to go up
			 * unless we're charging or if we're in init
			 */
			dev_dbg(di->dev,
				"capacity changed from %d to %d (%d)\n",
				di->bat_cap.prev_percent,
				percent,
				di->bat_cap.permille);
			di->bat_cap.prev_percent = percent;
			di->bat_cap.prev_mah = di->bat_cap.mah;

			changed = true;
		पूर्ण अन्यथा अणु
			dev_dbg(di->dev, "capacity not allowed to go up since "
				"no charger is connected: %d to %d (%d)\n",
				di->bat_cap.prev_percent,
				percent,
				di->bat_cap.permille);
		पूर्ण
	पूर्ण

	अगर (changed) अणु
		अगर (di->bm->capacity_scaling) अणु
			di->bat_cap.cap_scale.scaled_cap =
				ab8500_fg_calculate_scaled_capacity(di);

			dev_info(di->dev, "capacity=%d (%d)\n",
				di->bat_cap.prev_percent,
				di->bat_cap.cap_scale.scaled_cap);
		पूर्ण
		घातer_supply_changed(di->fg_psy);
		अगर (di->flags.fully_अक्षरged && di->flags.क्रमce_full) अणु
			dev_dbg(di->dev, "Battery full, notifying.\n");
			di->flags.क्रमce_full = false;
			sysfs_notअगरy(&di->fg_kobject, शून्य, "charge_full");
		पूर्ण
		sysfs_notअगरy(&di->fg_kobject, शून्य, "charge_now");
	पूर्ण
पूर्ण

अटल व्योम ab8500_fg_अक्षरge_state_to(काष्ठा ab8500_fg *di,
	क्रमागत ab8500_fg_अक्षरge_state new_state)
अणु
	dev_dbg(di->dev, "Charge state from %d [%s] to %d [%s]\n",
		di->अक्षरge_state,
		अक्षरge_state[di->अक्षरge_state],
		new_state,
		अक्षरge_state[new_state]);

	di->अक्षरge_state = new_state;
पूर्ण

अटल व्योम ab8500_fg_disअक्षरge_state_to(काष्ठा ab8500_fg *di,
	क्रमागत ab8500_fg_disअक्षरge_state new_state)
अणु
	dev_dbg(di->dev, "Discharge state from %d [%s] to %d [%s]\n",
		di->disअक्षरge_state,
		disअक्षरge_state[di->disअक्षरge_state],
		new_state,
		disअक्षरge_state[new_state]);

	di->disअक्षरge_state = new_state;
पूर्ण

/**
 * ab8500_fg_algorithm_अक्षरging() - FG algorithm क्रम when अक्षरging
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Battery capacity calculation state machine क्रम when we're अक्षरging
 */
अटल व्योम ab8500_fg_algorithm_अक्षरging(काष्ठा ab8500_fg *di)
अणु
	/*
	 * If we change to disअक्षरge mode
	 * we should start with recovery
	 */
	अगर (di->disअक्षरge_state != AB8500_FG_DISCHARGE_INIT_RECOVERY)
		ab8500_fg_disअक्षरge_state_to(di,
			AB8500_FG_DISCHARGE_INIT_RECOVERY);

	चयन (di->अक्षरge_state) अणु
	हाल AB8500_FG_CHARGE_INIT:
		di->fg_samples = SEC_TO_SAMPLE(
			di->bm->fg_params->accu_अक्षरging);

		ab8500_fg_coulomb_counter(di, true);
		ab8500_fg_अक्षरge_state_to(di, AB8500_FG_CHARGE_READOUT);

		अवरोध;

	हाल AB8500_FG_CHARGE_READOUT:
		/*
		 * Read the FG and calculate the new capacity
		 */
		mutex_lock(&di->cc_lock);
		अगर (!di->flags.conv_करोne && !di->flags.क्रमce_full) अणु
			/* Wasn't the CC IRQ that got us here */
			mutex_unlock(&di->cc_lock);
			dev_dbg(di->dev, "%s CC conv not done\n",
				__func__);

			अवरोध;
		पूर्ण
		di->flags.conv_करोne = false;
		mutex_unlock(&di->cc_lock);

		ab8500_fg_calc_cap_अक्षरging(di);

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Check capacity limits */
	ab8500_fg_check_capacity_limits(di, false);
पूर्ण

अटल व्योम क्रमce_capacity(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक cap;

	ab8500_fg_clear_cap_samples(di);
	cap = di->bat_cap.user_mah;
	अगर (cap > di->bat_cap.max_mah_design) अणु
		dev_dbg(di->dev, "Remaining cap %d can't be bigger than total"
			" %d\n", cap, di->bat_cap.max_mah_design);
		cap = di->bat_cap.max_mah_design;
	पूर्ण
	ab8500_fg_fill_cap_sample(di, di->bat_cap.user_mah);
	di->bat_cap.permille = ab8500_fg_convert_mah_to_permille(di, cap);
	di->bat_cap.mah = cap;
	ab8500_fg_check_capacity_limits(di, true);
पूर्ण

अटल bool check_sysfs_capacity(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक cap, lower, upper;
	पूर्णांक cap_permille;

	cap = di->bat_cap.user_mah;

	cap_permille = ab8500_fg_convert_mah_to_permille(di,
		di->bat_cap.user_mah);

	lower = di->bat_cap.permille - di->bm->fg_params->user_cap_limit * 10;
	upper = di->bat_cap.permille + di->bm->fg_params->user_cap_limit * 10;

	अगर (lower < 0)
		lower = 0;
	/* 1000 is permille, -> 100 percent */
	अगर (upper > 1000)
		upper = 1000;

	dev_dbg(di->dev, "Capacity limits:"
		" (Lower: %d User: %d Upper: %d) [user: %d, was: %d]\n",
		lower, cap_permille, upper, cap, di->bat_cap.mah);

	/* If within limits, use the saved capacity and निकास estimation...*/
	अगर (cap_permille > lower && cap_permille < upper) अणु
		dev_dbg(di->dev, "OK! Using users cap %d uAh now\n", cap);
		क्रमce_capacity(di);
		वापस true;
	पूर्ण
	dev_dbg(di->dev, "Capacity from user out of limits, ignoring");
	वापस false;
पूर्ण

/**
 * ab8500_fg_algorithm_disअक्षरging() - FG algorithm क्रम when disअक्षरging
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Battery capacity calculation state machine क्रम when we're disअक्षरging
 */
अटल व्योम ab8500_fg_algorithm_disअक्षरging(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक sleep_समय;

	/* If we change to अक्षरge mode we should start with init */
	अगर (di->अक्षरge_state != AB8500_FG_CHARGE_INIT)
		ab8500_fg_अक्षरge_state_to(di, AB8500_FG_CHARGE_INIT);

	चयन (di->disअक्षरge_state) अणु
	हाल AB8500_FG_DISCHARGE_INIT:
		/* We use the FG IRQ to work on */
		di->init_cnt = 0;
		di->fg_samples = SEC_TO_SAMPLE(di->bm->fg_params->init_समयr);
		ab8500_fg_coulomb_counter(di, true);
		ab8500_fg_disअक्षरge_state_to(di,
			AB8500_FG_DISCHARGE_INITMEASURING);

		fallthrough;
	हाल AB8500_FG_DISCHARGE_INITMEASURING:
		/*
		 * Discard a number of samples during startup.
		 * After that, use compensated voltage क्रम a few
		 * samples to get an initial capacity.
		 * Then go to READOUT
		 */
		sleep_समय = di->bm->fg_params->init_समयr;

		/* Discard the first [x] seconds */
		अगर (di->init_cnt > di->bm->fg_params->init_discard_समय) अणु
			ab8500_fg_calc_cap_disअक्षरge_voltage(di, true);

			ab8500_fg_check_capacity_limits(di, true);
		पूर्ण

		di->init_cnt += sleep_समय;
		अगर (di->init_cnt > di->bm->fg_params->init_total_समय)
			ab8500_fg_disअक्षरge_state_to(di,
				AB8500_FG_DISCHARGE_READOUT_INIT);

		अवरोध;

	हाल AB8500_FG_DISCHARGE_INIT_RECOVERY:
		di->recovery_cnt = 0;
		di->recovery_needed = true;
		ab8500_fg_disअक्षरge_state_to(di,
			AB8500_FG_DISCHARGE_RECOVERY);

		fallthrough;

	हाल AB8500_FG_DISCHARGE_RECOVERY:
		sleep_समय = di->bm->fg_params->recovery_sleep_समयr;

		/*
		 * We should check the घातer consumption
		 * If low, go to READOUT (after x min) or
		 * RECOVERY_SLEEP अगर समय left.
		 * If high, go to READOUT
		 */
		di->inst_curr = ab8500_fg_inst_curr_blocking(di);

		अगर (ab8500_fg_is_low_curr(di, di->inst_curr)) अणु
			अगर (di->recovery_cnt >
				di->bm->fg_params->recovery_total_समय) अणु
				di->fg_samples = SEC_TO_SAMPLE(
					di->bm->fg_params->accu_high_curr);
				ab8500_fg_coulomb_counter(di, true);
				ab8500_fg_disअक्षरge_state_to(di,
					AB8500_FG_DISCHARGE_READOUT);
				di->recovery_needed = false;
			पूर्ण अन्यथा अणु
				queue_delayed_work(di->fg_wq,
					&di->fg_periodic_work,
					sleep_समय * HZ);
			पूर्ण
			di->recovery_cnt += sleep_समय;
		पूर्ण अन्यथा अणु
			di->fg_samples = SEC_TO_SAMPLE(
				di->bm->fg_params->accu_high_curr);
			ab8500_fg_coulomb_counter(di, true);
			ab8500_fg_disअक्षरge_state_to(di,
				AB8500_FG_DISCHARGE_READOUT);
		पूर्ण
		अवरोध;

	हाल AB8500_FG_DISCHARGE_READOUT_INIT:
		di->fg_samples = SEC_TO_SAMPLE(
			di->bm->fg_params->accu_high_curr);
		ab8500_fg_coulomb_counter(di, true);
		ab8500_fg_disअक्षरge_state_to(di,
				AB8500_FG_DISCHARGE_READOUT);
		अवरोध;

	हाल AB8500_FG_DISCHARGE_READOUT:
		di->inst_curr = ab8500_fg_inst_curr_blocking(di);

		अगर (ab8500_fg_is_low_curr(di, di->inst_curr)) अणु
			/* Detect mode change */
			अगर (di->high_curr_mode) अणु
				di->high_curr_mode = false;
				di->high_curr_cnt = 0;
			पूर्ण

			अगर (di->recovery_needed) अणु
				ab8500_fg_disअक्षरge_state_to(di,
					AB8500_FG_DISCHARGE_INIT_RECOVERY);

				queue_delayed_work(di->fg_wq,
					&di->fg_periodic_work, 0);

				अवरोध;
			पूर्ण

			ab8500_fg_calc_cap_disअक्षरge_voltage(di, true);
		पूर्ण अन्यथा अणु
			mutex_lock(&di->cc_lock);
			अगर (!di->flags.conv_करोne) अणु
				/* Wasn't the CC IRQ that got us here */
				mutex_unlock(&di->cc_lock);
				dev_dbg(di->dev, "%s CC conv not done\n",
					__func__);

				अवरोध;
			पूर्ण
			di->flags.conv_करोne = false;
			mutex_unlock(&di->cc_lock);

			/* Detect mode change */
			अगर (!di->high_curr_mode) अणु
				di->high_curr_mode = true;
				di->high_curr_cnt = 0;
			पूर्ण

			di->high_curr_cnt +=
				di->bm->fg_params->accu_high_curr;
			अगर (di->high_curr_cnt >
				di->bm->fg_params->high_curr_समय)
				di->recovery_needed = true;

			ab8500_fg_calc_cap_disअक्षरge_fg(di);
		पूर्ण

		ab8500_fg_check_capacity_limits(di, false);

		अवरोध;

	हाल AB8500_FG_DISCHARGE_WAKEUP:
		ab8500_fg_calc_cap_disअक्षरge_voltage(di, true);

		di->fg_samples = SEC_TO_SAMPLE(
			di->bm->fg_params->accu_high_curr);
		ab8500_fg_coulomb_counter(di, true);
		ab8500_fg_disअक्षरge_state_to(di,
				AB8500_FG_DISCHARGE_READOUT);

		ab8500_fg_check_capacity_limits(di, false);

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ab8500_fg_algorithm_calibrate() - Internal columb counter offset calibration
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 */
अटल व्योम ab8500_fg_algorithm_calibrate(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक ret;

	चयन (di->calib_state) अणु
	हाल AB8500_FG_CALIB_INIT:
		dev_dbg(di->dev, "Calibration ongoing...\n");

		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG,
			CC_INT_CAL_N_AVG_MASK, CC_INT_CAL_SAMPLES_8);
		अगर (ret < 0)
			जाओ err;

		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG,
			CC_INTAVGOFFSET_ENA, CC_INTAVGOFFSET_ENA);
		अगर (ret < 0)
			जाओ err;
		di->calib_state = AB8500_FG_CALIB_WAIT;
		अवरोध;
	हाल AB8500_FG_CALIB_END:
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_GAS_GAUGE, AB8500_GASG_CC_CTRL_REG,
			CC_MUXOFFSET, CC_MUXOFFSET);
		अगर (ret < 0)
			जाओ err;
		di->flags.calibrate = false;
		dev_dbg(di->dev, "Calibration done...\n");
		queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
		अवरोध;
	हाल AB8500_FG_CALIB_WAIT:
		dev_dbg(di->dev, "Calibration WFI\n");
	शेष:
		अवरोध;
	पूर्ण
	वापस;
err:
	/* Something went wrong, करोn't calibrate then */
	dev_err(di->dev, "failed to calibrate the CC\n");
	di->flags.calibrate = false;
	di->calib_state = AB8500_FG_CALIB_INIT;
	queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
पूर्ण

/**
 * ab8500_fg_algorithm() - Entry poपूर्णांक क्रम the FG algorithm
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Entry poपूर्णांक क्रम the battery capacity calculation state machine
 */
अटल व्योम ab8500_fg_algorithm(काष्ठा ab8500_fg *di)
अणु
	अगर (di->flags.calibrate)
		ab8500_fg_algorithm_calibrate(di);
	अन्यथा अणु
		अगर (di->flags.अक्षरging)
			ab8500_fg_algorithm_अक्षरging(di);
		अन्यथा
			ab8500_fg_algorithm_disअक्षरging(di);
	पूर्ण

	dev_dbg(di->dev, "[FG_DATA] %d %d %d %d %d %d %d %d %d %d "
		"%d %d %d %d %d %d %d\n",
		di->bat_cap.max_mah_design,
		di->bat_cap.max_mah,
		di->bat_cap.mah,
		di->bat_cap.permille,
		di->bat_cap.level,
		di->bat_cap.prev_mah,
		di->bat_cap.prev_percent,
		di->bat_cap.prev_level,
		di->vbat,
		di->inst_curr,
		di->avg_curr,
		di->accu_अक्षरge,
		di->flags.अक्षरging,
		di->अक्षरge_state,
		di->disअक्षरge_state,
		di->high_curr_mode,
		di->recovery_needed);
पूर्ण

/**
 * ab8500_fg_periodic_work() - Run the FG state machine periodically
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम periodic work
 */
अटल व्योम ab8500_fg_periodic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ab8500_fg *di = container_of(work, काष्ठा ab8500_fg,
		fg_periodic_work.work);

	अगर (di->init_capacity) अणु
		/* Get an initial capacity calculation */
		ab8500_fg_calc_cap_disअक्षरge_voltage(di, true);
		ab8500_fg_check_capacity_limits(di, true);
		di->init_capacity = false;

		queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
	पूर्ण अन्यथा अगर (di->flags.user_cap) अणु
		अगर (check_sysfs_capacity(di)) अणु
			ab8500_fg_check_capacity_limits(di, true);
			अगर (di->flags.अक्षरging)
				ab8500_fg_अक्षरge_state_to(di,
					AB8500_FG_CHARGE_INIT);
			अन्यथा
				ab8500_fg_disअक्षरge_state_to(di,
					AB8500_FG_DISCHARGE_READOUT_INIT);
		पूर्ण
		di->flags.user_cap = false;
		queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
	पूर्ण अन्यथा
		ab8500_fg_algorithm(di);

पूर्ण

/**
 * ab8500_fg_check_hw_failure_work() - Check OVV_BAT condition
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम checking the OVV_BAT condition
 */
अटल व्योम ab8500_fg_check_hw_failure_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	u8 reg_value;

	काष्ठा ab8500_fg *di = container_of(work, काष्ठा ab8500_fg,
		fg_check_hw_failure_work.work);

	/*
	 * If we have had a battery over-voltage situation,
	 * check ovv-bit to see अगर it should be reset.
	 */
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER, AB8500_CH_STAT_REG,
		&reg_value);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s ab8500 read failed\n", __func__);
		वापस;
	पूर्ण
	अगर ((reg_value & BATT_OVV) == BATT_OVV) अणु
		अगर (!di->flags.bat_ovv) अणु
			dev_dbg(di->dev, "Battery OVV\n");
			di->flags.bat_ovv = true;
			घातer_supply_changed(di->fg_psy);
		पूर्ण
		/* Not yet recovered from ovv, reschedule this test */
		queue_delayed_work(di->fg_wq, &di->fg_check_hw_failure_work,
				   HZ);
		पूर्ण अन्यथा अणु
			dev_dbg(di->dev, "Battery recovered from OVV\n");
			di->flags.bat_ovv = false;
			घातer_supply_changed(di->fg_psy);
	पूर्ण
पूर्ण

/**
 * ab8500_fg_low_bat_work() - Check LOW_BAT condition
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम checking the LOW_BAT condition
 */
अटल व्योम ab8500_fg_low_bat_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक vbat;

	काष्ठा ab8500_fg *di = container_of(work, काष्ठा ab8500_fg,
		fg_low_bat_work.work);

	vbat = ab8500_fg_bat_voltage(di);

	/* Check अगर LOW_BAT still fulfilled */
	अगर (vbat < di->bm->fg_params->lowbat_threshold) अणु
		/* Is it समय to shut करोwn? */
		अगर (di->low_bat_cnt < 1) अणु
			di->flags.low_bat = true;
			dev_warn(di->dev, "Shut down pending...\n");
		पूर्ण अन्यथा अणु
			/*
			* Else we need to re-schedule this check to be able to detect
			* अगर the voltage increases again during अक्षरging or
			* due to decreasing load.
			*/
			di->low_bat_cnt--;
			dev_warn(di->dev, "Battery voltage still LOW\n");
			queue_delayed_work(di->fg_wq, &di->fg_low_bat_work,
				round_jअगरfies(LOW_BAT_CHECK_INTERVAL));
		पूर्ण
	पूर्ण अन्यथा अणु
		di->flags.low_bat_delay = false;
		di->low_bat_cnt = 10;
		dev_warn(di->dev, "Battery voltage OK again\n");
	पूर्ण

	/* This is needed to dispatch LOW_BAT */
	ab8500_fg_check_capacity_limits(di, false);
पूर्ण

/**
 * ab8500_fg_battok_calc - calculate the bit pattern corresponding
 * to the target voltage.
 * @di:       poपूर्णांकer to the ab8500_fg काष्ठाure
 * @target:   target voltage
 *
 * Returns bit pattern बंदst to the target voltage
 * valid वापस values are 0-14. (0-BATT_OK_MAX_NR_INCREMENTS)
 */

अटल पूर्णांक ab8500_fg_battok_calc(काष्ठा ab8500_fg *di, पूर्णांक target)
अणु
	अगर (target > BATT_OK_MIN +
		(BATT_OK_INCREMENT * BATT_OK_MAX_NR_INCREMENTS))
		वापस BATT_OK_MAX_NR_INCREMENTS;
	अगर (target < BATT_OK_MIN)
		वापस 0;
	वापस (target - BATT_OK_MIN) / BATT_OK_INCREMENT;
पूर्ण

/**
 * ab8500_fg_battok_init_hw_रेजिस्टर - init battok levels
 * @di:       poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 */

अटल पूर्णांक ab8500_fg_battok_init_hw_रेजिस्टर(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक selected;
	पूर्णांक sel0;
	पूर्णांक sel1;
	पूर्णांक cbp_sel0;
	पूर्णांक cbp_sel1;
	पूर्णांक ret;
	पूर्णांक new_val;

	sel0 = di->bm->fg_params->battok_falling_th_sel0;
	sel1 = di->bm->fg_params->battok_raising_th_sel1;

	cbp_sel0 = ab8500_fg_battok_calc(di, sel0);
	cbp_sel1 = ab8500_fg_battok_calc(di, sel1);

	selected = BATT_OK_MIN + cbp_sel0 * BATT_OK_INCREMENT;

	अगर (selected != sel0)
		dev_warn(di->dev, "Invalid voltage step:%d, using %d %d\n",
			sel0, selected, cbp_sel0);

	selected = BATT_OK_MIN + cbp_sel1 * BATT_OK_INCREMENT;

	अगर (selected != sel1)
		dev_warn(di->dev, "Invalid voltage step:%d, using %d %d\n",
			sel1, selected, cbp_sel1);

	new_val = cbp_sel0 | (cbp_sel1 << 4);

	dev_dbg(di->dev, "using: %x %d %d\n", new_val, cbp_sel0, cbp_sel1);
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_SYS_CTRL2_BLOCK,
		AB8500_BATT_OK_REG, new_val);
	वापस ret;
पूर्ण

/**
 * ab8500_fg_instant_work() - Run the FG state machine instantly
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम instant work
 */
अटल व्योम ab8500_fg_instant_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ab8500_fg *di = container_of(work, काष्ठा ab8500_fg, fg_work);

	ab8500_fg_algorithm(di);
पूर्ण

/**
 * ab8500_fg_cc_data_end_handler() - end of data conversion isr.
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_fg_cc_data_end_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_fg *di = _di;
	अगर (!di->nbr_cceoc_irq_cnt) अणु
		di->nbr_cceoc_irq_cnt++;
		complete(&di->ab8500_fg_started);
	पूर्ण अन्यथा अणु
		di->nbr_cceoc_irq_cnt = 0;
		complete(&di->ab8500_fg_complete);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_fg_cc_पूर्णांक_calib_handler () - end of calibration isr.
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_fg_cc_पूर्णांक_calib_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_fg *di = _di;
	di->calib_state = AB8500_FG_CALIB_END;
	queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_fg_cc_convend_handler() - isr to get battery avg current.
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_fg_cc_convend_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_fg *di = _di;

	queue_work(di->fg_wq, &di->fg_acc_cur_work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_fg_batt_ovv_handler() - Battery OVV occured
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_fg_batt_ovv_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_fg *di = _di;

	dev_dbg(di->dev, "Battery OVV\n");

	/* Schedule a new HW failure check */
	queue_delayed_work(di->fg_wq, &di->fg_check_hw_failure_work, 0);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_fg_lowbatf_handler() - Battery voltage is below LOW threshold
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_fg_lowbatf_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_fg *di = _di;

	/* Initiate handling in ab8500_fg_low_bat_work() अगर not alपढ़ोy initiated. */
	अगर (!di->flags.low_bat_delay) अणु
		dev_warn(di->dev, "Battery voltage is below LOW threshold\n");
		di->flags.low_bat_delay = true;
		/*
		 * Start a समयr to check LOW_BAT again after some समय
		 * This is करोne to aव्योम shutकरोwn on single voltage dips
		 */
		queue_delayed_work(di->fg_wq, &di->fg_low_bat_work,
			round_jअगरfies(LOW_BAT_CHECK_INTERVAL));
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_fg_get_property() - get the fg properties
 * @psy:	poपूर्णांकer to the घातer_supply काष्ठाure
 * @psp:	poपूर्णांकer to the घातer_supply_property काष्ठाure
 * @val:	poपूर्णांकer to the घातer_supply_propval जोड़
 *
 * This function माला_लो called when an application tries to get the
 * fg properties by पढ़ोing the sysfs files.
 * voltage_now:		battery voltage
 * current_now:		battery instant current
 * current_avg:		battery average current
 * अक्षरge_full_design:	capacity where battery is considered full
 * अक्षरge_now:		battery capacity in nAh
 * capacity:		capacity in percent
 * capacity_level:	capacity level
 *
 * Returns error code in हाल of failure अन्यथा 0 on success
 */
अटल पूर्णांक ab8500_fg_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	/*
	 * If battery is identअगरied as unknown and अक्षरging of unknown
	 * batteries is disabled, we always report 100% capacity and
	 * capacity level UNKNOWN, since we can't calculate
	 * reमुख्यing capacity
	 */

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (di->flags.bat_ovv)
			val->पूर्णांकval = BATT_OVV_VALUE * 1000;
		अन्यथा
			val->पूर्णांकval = di->vbat * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = di->inst_curr * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		val->पूर्णांकval = di->avg_curr * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		val->पूर्णांकval = ab8500_fg_convert_mah_to_uwh(di,
				di->bat_cap.max_mah_design);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ENERGY_FULL:
		val->पूर्णांकval = ab8500_fg_convert_mah_to_uwh(di,
				di->bat_cap.max_mah);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ENERGY_NOW:
		अगर (di->flags.batt_unknown && !di->bm->chg_unknown_bat &&
				di->flags.batt_id_received)
			val->पूर्णांकval = ab8500_fg_convert_mah_to_uwh(di,
					di->bat_cap.max_mah);
		अन्यथा
			val->पूर्णांकval = ab8500_fg_convert_mah_to_uwh(di,
					di->bat_cap.prev_mah);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval = di->bat_cap.max_mah_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		val->पूर्णांकval = di->bat_cap.max_mah;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		अगर (di->flags.batt_unknown && !di->bm->chg_unknown_bat &&
				di->flags.batt_id_received)
			val->पूर्णांकval = di->bat_cap.max_mah;
		अन्यथा
			val->पूर्णांकval = di->bat_cap.prev_mah;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		अगर (di->flags.batt_unknown && !di->bm->chg_unknown_bat &&
				di->flags.batt_id_received)
			val->पूर्णांकval = 100;
		अन्यथा
			val->पूर्णांकval = di->bat_cap.prev_percent;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		अगर (di->flags.batt_unknown && !di->bm->chg_unknown_bat &&
				di->flags.batt_id_received)
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
		अन्यथा
			val->पूर्णांकval = di->bat_cap.prev_level;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_fg_get_ext_psy_data(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply *ext = dev_get_drvdata(dev);
	स्थिर अक्षर **supplicants = (स्थिर अक्षर **)ext->supplied_to;
	काष्ठा ab8500_fg *di;
	जोड़ घातer_supply_propval ret;
	पूर्णांक j;

	psy = (काष्ठा घातer_supply *)data;
	di = घातer_supply_get_drvdata(psy);

	/*
	 * For all psy where the name of your driver
	 * appears in any supplied_to
	 */
	j = match_string(supplicants, ext->num_supplicants, psy->desc->name);
	अगर (j < 0)
		वापस 0;

	/* Go through all properties क्रम the psy */
	क्रम (j = 0; j < ext->desc->num_properties; j++) अणु
		क्रमागत घातer_supply_property prop;
		prop = ext->desc->properties[j];

		अगर (घातer_supply_get_property(ext, prop, &ret))
			जारी;

		चयन (prop) अणु
		हाल POWER_SUPPLY_PROP_STATUS:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				चयन (ret.पूर्णांकval) अणु
				हाल POWER_SUPPLY_STATUS_UNKNOWN:
				हाल POWER_SUPPLY_STATUS_DISCHARGING:
				हाल POWER_SUPPLY_STATUS_NOT_CHARGING:
					अगर (!di->flags.अक्षरging)
						अवरोध;
					di->flags.अक्षरging = false;
					di->flags.fully_अक्षरged = false;
					अगर (di->bm->capacity_scaling)
						ab8500_fg_update_cap_scalers(di);
					queue_work(di->fg_wq, &di->fg_work);
					अवरोध;
				हाल POWER_SUPPLY_STATUS_FULL:
					अगर (di->flags.fully_अक्षरged)
						अवरोध;
					di->flags.fully_अक्षरged = true;
					di->flags.क्रमce_full = true;
					/* Save current capacity as maximum */
					di->bat_cap.max_mah = di->bat_cap.mah;
					queue_work(di->fg_wq, &di->fg_work);
					अवरोध;
				हाल POWER_SUPPLY_STATUS_CHARGING:
					अगर (di->flags.अक्षरging &&
						!di->flags.fully_अक्षरged)
						अवरोध;
					di->flags.अक्षरging = true;
					di->flags.fully_अक्षरged = false;
					अगर (di->bm->capacity_scaling)
						ab8500_fg_update_cap_scalers(di);
					queue_work(di->fg_wq, &di->fg_work);
					अवरोध;
				पूर्ण
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल POWER_SUPPLY_PROP_TECHNOLOGY:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				अगर (!di->flags.batt_id_received &&
				    di->bm->batt_id != BATTERY_UNKNOWN) अणु
					स्थिर काष्ठा abx500_battery_type *b;

					b = &(di->bm->bat_type[di->bm->batt_id]);

					di->flags.batt_id_received = true;

					di->bat_cap.max_mah_design =
						MILLI_TO_MICRO *
						b->अक्षरge_full_design;

					di->bat_cap.max_mah =
						di->bat_cap.max_mah_design;

					di->vbat_nom = b->nominal_voltage;
				पूर्ण

				अगर (ret.पूर्णांकval)
					di->flags.batt_unknown = false;
				अन्यथा
					di->flags.batt_unknown = true;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल POWER_SUPPLY_PROP_TEMP:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				अगर (di->flags.batt_id_received)
					di->bat_temp = ret.पूर्णांकval;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ab8500_fg_init_hw_रेजिस्टरs() - Set up FG related रेजिस्टरs
 * @di:		poपूर्णांकer to the ab8500_fg काष्ठाure
 *
 * Set up battery OVV, low battery voltage रेजिस्टरs
 */
अटल पूर्णांक ab8500_fg_init_hw_रेजिस्टरs(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक ret;

	/* Set VBAT OVV threshold */
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER,
		AB8500_BATT_OVV,
		BATT_OVV_TH_4P75,
		BATT_OVV_TH_4P75);
	अगर (ret) अणु
		dev_err(di->dev, "failed to set BATT_OVV\n");
		जाओ out;
	पूर्ण

	/* Enable VBAT OVV detection */
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER,
		AB8500_BATT_OVV,
		BATT_OVV_ENA,
		BATT_OVV_ENA);
	अगर (ret) अणु
		dev_err(di->dev, "failed to enable BATT_OVV\n");
		जाओ out;
	पूर्ण

	/* Low Battery Voltage */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_SYS_CTRL2_BLOCK,
		AB8500_LOW_BAT_REG,
		ab8500_volt_to_regval(
			di->bm->fg_params->lowbat_threshold) << 1 |
		LOW_BAT_ENABLE);
	अगर (ret) अणु
		dev_err(di->dev, "%s write failed\n", __func__);
		जाओ out;
	पूर्ण

	/* Battery OK threshold */
	ret = ab8500_fg_battok_init_hw_रेजिस्टर(di);
	अगर (ret) अणु
		dev_err(di->dev, "BattOk init write failed.\n");
		जाओ out;
	पूर्ण

	अगर (is_ab8505(di->parent)) अणु
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8505_RTC_PCUT_MAX_TIME_REG, di->bm->fg_params->pcut_max_समय);

		अगर (ret) अणु
			dev_err(di->dev, "%s write failed AB8505_RTC_PCUT_MAX_TIME_REG\n", __func__);
			जाओ out;
		पूर्ण

		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8505_RTC_PCUT_FLAG_TIME_REG, di->bm->fg_params->pcut_flag_समय);

		अगर (ret) अणु
			dev_err(di->dev, "%s write failed AB8505_RTC_PCUT_FLAG_TIME_REG\n", __func__);
			जाओ out;
		पूर्ण

		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8505_RTC_PCUT_RESTART_REG, di->bm->fg_params->pcut_max_restart);

		अगर (ret) अणु
			dev_err(di->dev, "%s write failed AB8505_RTC_PCUT_RESTART_REG\n", __func__);
			जाओ out;
		पूर्ण

		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8505_RTC_PCUT_DEBOUNCE_REG, di->bm->fg_params->pcut_debounce_समय);

		अगर (ret) अणु
			dev_err(di->dev, "%s write failed AB8505_RTC_PCUT_DEBOUNCE_REG\n", __func__);
			जाओ out;
		पूर्ण

		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
			AB8505_RTC_PCUT_CTL_STATUS_REG, di->bm->fg_params->pcut_enable);

		अगर (ret) अणु
			dev_err(di->dev, "%s write failed AB8505_RTC_PCUT_CTL_STATUS_REG\n", __func__);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

/**
 * ab8500_fg_बाह्यal_घातer_changed() - callback क्रम घातer supply changes
 * @psy:       poपूर्णांकer to the काष्ठाure घातer_supply
 *
 * This function is the entry poपूर्णांक of the poपूर्णांकer बाह्यal_घातer_changed
 * of the काष्ठाure घातer_supply.
 * This function माला_लो executed when there is a change in any बाह्यal घातer
 * supply that this driver needs to be notअगरied of.
 */
अटल व्योम ab8500_fg_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	class_क्रम_each_device(घातer_supply_class, शून्य,
		di->fg_psy, ab8500_fg_get_ext_psy_data);
पूर्ण

/**
 * ab8500_fg_reinit_work() - work to reset the FG algorithm
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Used to reset the current battery capacity to be able to
 * retrigger a new voltage base capacity calculation. For
 * test and verअगरication purpose.
 */
अटल व्योम ab8500_fg_reinit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ab8500_fg *di = container_of(work, काष्ठा ab8500_fg,
		fg_reinit_work.work);

	अगर (!di->flags.calibrate) अणु
		dev_dbg(di->dev, "Resetting FG state machine to init.\n");
		ab8500_fg_clear_cap_samples(di);
		ab8500_fg_calc_cap_disअक्षरge_voltage(di, true);
		ab8500_fg_अक्षरge_state_to(di, AB8500_FG_CHARGE_INIT);
		ab8500_fg_disअक्षरge_state_to(di, AB8500_FG_DISCHARGE_INIT);
		queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);

	पूर्ण अन्यथा अणु
		dev_err(di->dev, "Residual offset calibration ongoing "
			"retrying..\n");
		/* Wait one second until next try*/
		queue_delayed_work(di->fg_wq, &di->fg_reinit_work,
			round_jअगरfies(1));
	पूर्ण
पूर्ण

/* Exposure to the sysfs पूर्णांकerface */

काष्ठा ab8500_fg_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा ab8500_fg *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा ab8500_fg *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार अक्षरge_full_show(काष्ठा ab8500_fg *di, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", di->bat_cap.max_mah);
पूर्ण

अटल sमाप_प्रकार अक्षरge_full_store(काष्ठा ab8500_fg *di, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	अचिन्हित दीर्घ अक्षरge_full;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &अक्षरge_full);
	अगर (ret)
		वापस ret;

	di->bat_cap.max_mah = (पूर्णांक) अक्षरge_full;
	वापस count;
पूर्ण

अटल sमाप_प्रकार अक्षरge_now_show(काष्ठा ab8500_fg *di, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", di->bat_cap.prev_mah);
पूर्ण

अटल sमाप_प्रकार अक्षरge_now_store(काष्ठा ab8500_fg *di, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	अचिन्हित दीर्घ अक्षरge_now;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &अक्षरge_now);
	अगर (ret)
		वापस ret;

	di->bat_cap.user_mah = (पूर्णांक) अक्षरge_now;
	di->flags.user_cap = true;
	queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);
	वापस count;
पूर्ण

अटल काष्ठा ab8500_fg_sysfs_entry अक्षरge_full_attr =
	__ATTR(अक्षरge_full, 0644, अक्षरge_full_show, अक्षरge_full_store);

अटल काष्ठा ab8500_fg_sysfs_entry अक्षरge_now_attr =
	__ATTR(अक्षरge_now, 0644, अक्षरge_now_show, अक्षरge_now_store);

अटल sमाप_प्रकार
ab8500_fg_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा ab8500_fg_sysfs_entry *entry;
	काष्ठा ab8500_fg *di;

	entry = container_of(attr, काष्ठा ab8500_fg_sysfs_entry, attr);
	di = container_of(kobj, काष्ठा ab8500_fg, fg_kobject);

	अगर (!entry->show)
		वापस -EIO;

	वापस entry->show(di, buf);
पूर्ण
अटल sमाप_प्रकार
ab8500_fg_store(काष्ठा kobject *kobj, काष्ठा attribute *attr, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा ab8500_fg_sysfs_entry *entry;
	काष्ठा ab8500_fg *di;

	entry = container_of(attr, काष्ठा ab8500_fg_sysfs_entry, attr);
	di = container_of(kobj, काष्ठा ab8500_fg, fg_kobject);

	अगर (!entry->store)
		वापस -EIO;

	वापस entry->store(di, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops ab8500_fg_sysfs_ops = अणु
	.show = ab8500_fg_show,
	.store = ab8500_fg_store,
पूर्ण;

अटल काष्ठा attribute *ab8500_fg_attrs[] = अणु
	&अक्षरge_full_attr.attr,
	&अक्षरge_now_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type ab8500_fg_ktype = अणु
	.sysfs_ops = &ab8500_fg_sysfs_ops,
	.शेष_attrs = ab8500_fg_attrs,
पूर्ण;

/**
 * ab8500_fg_sysfs_निकास() - de-init of sysfs entry
 * @di:                poपूर्णांकer to the काष्ठा ab8500_अक्षरgalg
 *
 * This function हटाओs the entry in sysfs.
 */
अटल व्योम ab8500_fg_sysfs_निकास(काष्ठा ab8500_fg *di)
अणु
	kobject_del(&di->fg_kobject);
पूर्ण

/**
 * ab8500_fg_sysfs_init() - init of sysfs entry
 * @di:                poपूर्णांकer to the काष्ठा ab8500_अक्षरgalg
 *
 * This function adds an entry in sysfs.
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_fg_sysfs_init(काष्ठा ab8500_fg *di)
अणु
	पूर्णांक ret = 0;

	ret = kobject_init_and_add(&di->fg_kobject,
		&ab8500_fg_ktype,
		शून्य, "battery");
	अगर (ret < 0)
		dev_err(di->dev, "failed to create sysfs entry\n");

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_flagसमय_पढ़ो(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
		AB8505_RTC_PCUT_FLAG_TIME_REG, &reg_value);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_FLAG_TIME_REG\n");
		जाओ fail;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (reg_value & 0x7F));

fail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_flagसमय_ग_लिखो(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	पूर्णांक reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	अगर (kstrtoपूर्णांक(buf, 10, &reg_value))
		जाओ fail;

	अगर (reg_value > 0x7F) अणु
		dev_err(dev, "Incorrect parameter, echo 0 (1.98s) - 127 (15.625ms) for flagtime\n");
		जाओ fail;
	पूर्ण

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
		AB8505_RTC_PCUT_FLAG_TIME_REG, (u8)reg_value);

	अगर (ret < 0)
		dev_err(dev, "Failed to set AB8505_RTC_PCUT_FLAG_TIME_REG\n");

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_maxसमय_पढ़ो(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
		AB8505_RTC_PCUT_MAX_TIME_REG, &reg_value);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_MAX_TIME_REG\n");
		जाओ fail;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (reg_value & 0x7F));

fail:
	वापस ret;

पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_maxसमय_ग_लिखो(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	पूर्णांक reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	अगर (kstrtoपूर्णांक(buf, 10, &reg_value))
		जाओ fail;

	अगर (reg_value > 0x7F) अणु
		dev_err(dev, "Incorrect parameter, echo 0 (0.0s) - 127 (1.98s) for maxtime\n");
		जाओ fail;
	पूर्ण

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
		AB8505_RTC_PCUT_MAX_TIME_REG, (u8)reg_value);

	अगर (ret < 0)
		dev_err(dev, "Failed to set AB8505_RTC_PCUT_MAX_TIME_REG\n");

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_restart_पढ़ो(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
		AB8505_RTC_PCUT_RESTART_REG, &reg_value);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_RESTART_REG\n");
		जाओ fail;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (reg_value & 0xF));

fail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_restart_ग_लिखो(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	पूर्णांक reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	अगर (kstrtoपूर्णांक(buf, 10, &reg_value))
		जाओ fail;

	अगर (reg_value > 0xF) अणु
		dev_err(dev, "Incorrect parameter, echo 0 - 15 for number of restart\n");
		जाओ fail;
	पूर्ण

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_RESTART_REG, (u8)reg_value);

	अगर (ret < 0)
		dev_err(dev, "Failed to set AB8505_RTC_PCUT_RESTART_REG\n");

fail:
	वापस count;

पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_समयr_पढ़ो(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_TIME_REG, &reg_value);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_TIME_REG\n");
		जाओ fail;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (reg_value & 0x7F));

fail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_restart_counter_पढ़ो(काष्ठा device *dev,
						    काष्ठा device_attribute *attr,
						    अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_RESTART_REG, &reg_value);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_RESTART_REG\n");
		जाओ fail;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (reg_value & 0xF0) >> 4);

fail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_पढ़ो(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_CTL_STATUS_REG, &reg_value);

	अगर (ret < 0)
		जाओ fail;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (reg_value & 0x1));

fail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_ग_लिखो(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	पूर्णांक reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	अगर (kstrtoपूर्णांक(buf, 10, &reg_value))
		जाओ fail;

	अगर (reg_value > 0x1) अणु
		dev_err(dev, "Incorrect parameter, echo 0/1 to disable/enable Pcut feature\n");
		जाओ fail;
	पूर्ण

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_CTL_STATUS_REG, (u8)reg_value);

	अगर (ret < 0)
		dev_err(dev, "Failed to set AB8505_RTC_PCUT_CTL_STATUS_REG\n");

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_flag_पढ़ो(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु

	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_CTL_STATUS_REG,  &reg_value);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_CTL_STATUS_REG\n");
		जाओ fail;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ((reg_value & 0x10) >> 4));

fail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_debounce_पढ़ो(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_DEBOUNCE_REG,  &reg_value);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_DEBOUNCE_REG\n");
		जाओ fail;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (reg_value & 0x7));

fail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_debounce_ग_लिखो(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	पूर्णांक reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	अगर (kstrtoपूर्णांक(buf, 10, &reg_value))
		जाओ fail;

	अगर (reg_value > 0x7) अणु
		dev_err(dev, "Incorrect parameter, echo 0 to 7 for debounce setting\n");
		जाओ fail;
	पूर्ण

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_DEBOUNCE_REG, (u8)reg_value);

	अगर (ret < 0)
		dev_err(dev, "Failed to set AB8505_RTC_PCUT_DEBOUNCE_REG\n");

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार ab8505_घातercut_enable_status_पढ़ो(काष्ठा device *dev,
						  काष्ठा device_attribute *attr,
						  अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 reg_value;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा ab8500_fg *di = घातer_supply_get_drvdata(psy);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_CTL_STATUS_REG, &reg_value);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_CTL_STATUS_REG\n");
		जाओ fail;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ((reg_value & 0x20) >> 5));

fail:
	वापस ret;
पूर्ण

अटल काष्ठा device_attribute ab8505_fg_sysfs_psy_attrs[] = अणु
	__ATTR(घातercut_flagसमय, (S_IRUGO | S_IWUSR | S_IWGRP),
		ab8505_घातercut_flagसमय_पढ़ो, ab8505_घातercut_flagसमय_ग_लिखो),
	__ATTR(घातercut_maxसमय, (S_IRUGO | S_IWUSR | S_IWGRP),
		ab8505_घातercut_maxसमय_पढ़ो, ab8505_घातercut_maxसमय_ग_लिखो),
	__ATTR(घातercut_restart_max, (S_IRUGO | S_IWUSR | S_IWGRP),
		ab8505_घातercut_restart_पढ़ो, ab8505_घातercut_restart_ग_लिखो),
	__ATTR(घातercut_समयr, S_IRUGO, ab8505_घातercut_समयr_पढ़ो, शून्य),
	__ATTR(घातercut_restart_counter, S_IRUGO,
		ab8505_घातercut_restart_counter_पढ़ो, शून्य),
	__ATTR(घातercut_enable, (S_IRUGO | S_IWUSR | S_IWGRP),
		ab8505_घातercut_पढ़ो, ab8505_घातercut_ग_लिखो),
	__ATTR(घातercut_flag, S_IRUGO, ab8505_घातercut_flag_पढ़ो, शून्य),
	__ATTR(घातercut_debounce_समय, (S_IRUGO | S_IWUSR | S_IWGRP),
		ab8505_घातercut_debounce_पढ़ो, ab8505_घातercut_debounce_ग_लिखो),
	__ATTR(घातercut_enable_status, S_IRUGO,
		ab8505_घातercut_enable_status_पढ़ो, शून्य),
पूर्ण;

अटल पूर्णांक ab8500_fg_sysfs_psy_create_attrs(काष्ठा ab8500_fg *di)
अणु
	अचिन्हित पूर्णांक i;

	अगर (is_ab8505(di->parent)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ab8505_fg_sysfs_psy_attrs); i++)
			अगर (device_create_file(&di->fg_psy->dev,
					       &ab8505_fg_sysfs_psy_attrs[i]))
				जाओ sysfs_psy_create_attrs_failed_ab8505;
	पूर्ण
	वापस 0;
sysfs_psy_create_attrs_failed_ab8505:
	dev_err(&di->fg_psy->dev, "Failed creating sysfs psy attrs for ab8505.\n");
	जबतक (i--)
		device_हटाओ_file(&di->fg_psy->dev,
				   &ab8505_fg_sysfs_psy_attrs[i]);

	वापस -EIO;
पूर्ण

अटल व्योम ab8500_fg_sysfs_psy_हटाओ_attrs(काष्ठा ab8500_fg *di)
अणु
	अचिन्हित पूर्णांक i;

	अगर (is_ab8505(di->parent)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ab8505_fg_sysfs_psy_attrs); i++)
			(व्योम)device_हटाओ_file(&di->fg_psy->dev,
						 &ab8505_fg_sysfs_psy_attrs[i]);
	पूर्ण
पूर्ण

/* Exposure to the sysfs पूर्णांकerface <<END>> */

अटल पूर्णांक __maybe_unused ab8500_fg_resume(काष्ठा device *dev)
अणु
	काष्ठा ab8500_fg *di = dev_get_drvdata(dev);

	/*
	 * Change state अगर we're not charging. If we're अक्षरging we will wake
	 * up on the FG IRQ
	 */
	अगर (!di->flags.अक्षरging) अणु
		ab8500_fg_disअक्षरge_state_to(di, AB8500_FG_DISCHARGE_WAKEUP);
		queue_work(di->fg_wq, &di->fg_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ab8500_fg_suspend(काष्ठा device *dev)
अणु
	काष्ठा ab8500_fg *di = dev_get_drvdata(dev);

	flush_delayed_work(&di->fg_periodic_work);
	flush_work(&di->fg_work);
	flush_work(&di->fg_acc_cur_work);
	flush_delayed_work(&di->fg_reinit_work);
	flush_delayed_work(&di->fg_low_bat_work);
	flush_delayed_work(&di->fg_check_hw_failure_work);

	/*
	 * If the FG is enabled we will disable it beक्रमe going to suspend
	 * only अगर we're not अक्षरging
	 */
	अगर (di->flags.fg_enabled && !di->flags.अक्षरging)
		ab8500_fg_coulomb_counter(di, false);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_fg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा ab8500_fg *di = platक्रमm_get_drvdata(pdev);

	list_del(&di->node);

	/* Disable coulomb counter */
	ret = ab8500_fg_coulomb_counter(di, false);
	अगर (ret)
		dev_err(di->dev, "failed to disable coulomb counter\n");

	destroy_workqueue(di->fg_wq);
	ab8500_fg_sysfs_निकास(di);

	flush_scheduled_work();
	ab8500_fg_sysfs_psy_हटाओ_attrs(di);
	घातer_supply_unरेजिस्टर(di->fg_psy);
	वापस ret;
पूर्ण

/* ab8500 fg driver पूर्णांकerrupts and their respective isr */
अटल काष्ठा ab8500_fg_पूर्णांकerrupts ab8500_fg_irq[] = अणु
	अणु"NCONV_ACCU", ab8500_fg_cc_convend_handlerपूर्ण,
	अणु"BATT_OVV", ab8500_fg_batt_ovv_handlerपूर्ण,
	अणु"LOW_BAT_F", ab8500_fg_lowbatf_handlerपूर्ण,
	अणु"CC_INT_CALIB", ab8500_fg_cc_पूर्णांक_calib_handlerपूर्ण,
	अणु"CCEOC", ab8500_fg_cc_data_end_handlerपूर्ण,
पूर्ण;

अटल अक्षर *supply_पूर्णांकerface[] = अणु
	"ab8500_chargalg",
	"ab8500_usb",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc ab8500_fg_desc = अणु
	.name			= "ab8500_fg",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= ab8500_fg_props,
	.num_properties		= ARRAY_SIZE(ab8500_fg_props),
	.get_property		= ab8500_fg_get_property,
	.बाह्यal_घातer_changed	= ab8500_fg_बाह्यal_घातer_changed,
पूर्ण;

अटल पूर्णांक ab8500_fg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ab8500_fg *di;
	पूर्णांक i, irq;
	पूर्णांक ret = 0;

	di = devm_kzalloc(dev, माप(*di), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	di->bm = &ab8500_bm_data;

	ret = ab8500_bm_of_probe(dev, np, di->bm);
	अगर (ret) अणु
		dev_err(dev, "failed to get battery information\n");
		वापस ret;
	पूर्ण

	mutex_init(&di->cc_lock);

	/* get parent data */
	di->dev = dev;
	di->parent = dev_get_drvdata(pdev->dev.parent);

	di->मुख्य_bat_v = devm_iio_channel_get(dev, "main_bat_v");
	अगर (IS_ERR(di->मुख्य_bat_v)) अणु
		ret = dev_err_probe(dev, PTR_ERR(di->मुख्य_bat_v),
				    "failed to get main battery ADC channel\n");
		वापस ret;
	पूर्ण

	psy_cfg.supplied_to = supply_पूर्णांकerface;
	psy_cfg.num_supplicants = ARRAY_SIZE(supply_पूर्णांकerface);
	psy_cfg.drv_data = di;

	di->bat_cap.max_mah_design = MILLI_TO_MICRO *
		di->bm->bat_type[di->bm->batt_id].अक्षरge_full_design;

	di->bat_cap.max_mah = di->bat_cap.max_mah_design;

	di->vbat_nom = di->bm->bat_type[di->bm->batt_id].nominal_voltage;

	di->init_capacity = true;

	ab8500_fg_अक्षरge_state_to(di, AB8500_FG_CHARGE_INIT);
	ab8500_fg_disअक्षरge_state_to(di, AB8500_FG_DISCHARGE_INIT);

	/* Create a work queue क्रम running the FG algorithm */
	di->fg_wq = alloc_ordered_workqueue("ab8500_fg_wq", WQ_MEM_RECLAIM);
	अगर (di->fg_wq == शून्य) अणु
		dev_err(dev, "failed to create work queue\n");
		वापस -ENOMEM;
	पूर्ण

	/* Init work क्रम running the fg algorithm instantly */
	INIT_WORK(&di->fg_work, ab8500_fg_instant_work);

	/* Init work क्रम getting the battery accumulated current */
	INIT_WORK(&di->fg_acc_cur_work, ab8500_fg_acc_cur_work);

	/* Init work क्रम reinitialising the fg algorithm */
	INIT_DEFERRABLE_WORK(&di->fg_reinit_work,
		ab8500_fg_reinit_work);

	/* Work delayed Queue to run the state machine */
	INIT_DEFERRABLE_WORK(&di->fg_periodic_work,
		ab8500_fg_periodic_work);

	/* Work to check low battery condition */
	INIT_DEFERRABLE_WORK(&di->fg_low_bat_work,
		ab8500_fg_low_bat_work);

	/* Init work क्रम HW failure check */
	INIT_DEFERRABLE_WORK(&di->fg_check_hw_failure_work,
		ab8500_fg_check_hw_failure_work);

	/* Reset battery low voltage flag */
	di->flags.low_bat = false;

	/* Initialize low battery counter */
	di->low_bat_cnt = 10;

	/* Initialize OVV, and other रेजिस्टरs */
	ret = ab8500_fg_init_hw_रेजिस्टरs(di);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize registers\n");
		जाओ मुक्त_inst_curr_wq;
	पूर्ण

	/* Consider battery unknown until we're inक्रमmed otherwise */
	di->flags.batt_unknown = true;
	di->flags.batt_id_received = false;

	/* Register FG घातer supply class */
	di->fg_psy = घातer_supply_रेजिस्टर(dev, &ab8500_fg_desc, &psy_cfg);
	अगर (IS_ERR(di->fg_psy)) अणु
		dev_err(dev, "failed to register FG psy\n");
		ret = PTR_ERR(di->fg_psy);
		जाओ मुक्त_inst_curr_wq;
	पूर्ण

	di->fg_samples = SEC_TO_SAMPLE(di->bm->fg_params->init_समयr);
	ab8500_fg_coulomb_counter(di, true);

	/*
	 * Initialize completion used to notअगरy completion and start
	 * of inst current
	 */
	init_completion(&di->ab8500_fg_started);
	init_completion(&di->ab8500_fg_complete);

	/* Register primary पूर्णांकerrupt handlers */
	क्रम (i = 0; i < ARRAY_SIZE(ab8500_fg_irq); i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, ab8500_fg_irq[i].name);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ मुक्त_irq;
		पूर्ण

		ret = request_thपढ़ोed_irq(irq, शून्य, ab8500_fg_irq[i].isr,
				  IRQF_SHARED | IRQF_NO_SUSPEND | IRQF_ONESHOT,
				  ab8500_fg_irq[i].name, di);

		अगर (ret != 0) अणु
			dev_err(dev, "failed to request %s IRQ %d: %d\n",
				ab8500_fg_irq[i].name, irq, ret);
			जाओ मुक्त_irq;
		पूर्ण
		dev_dbg(dev, "Requested %s IRQ %d: %d\n",
			ab8500_fg_irq[i].name, irq, ret);
	पूर्ण

	di->irq = platक्रमm_get_irq_byname(pdev, "CCEOC");
	disable_irq(di->irq);
	di->nbr_cceoc_irq_cnt = 0;

	platक्रमm_set_drvdata(pdev, di);

	ret = ab8500_fg_sysfs_init(di);
	अगर (ret) अणु
		dev_err(dev, "failed to create sysfs entry\n");
		जाओ मुक्त_irq;
	पूर्ण

	ret = ab8500_fg_sysfs_psy_create_attrs(di);
	अगर (ret) अणु
		dev_err(dev, "failed to create FG psy\n");
		ab8500_fg_sysfs_निकास(di);
		जाओ मुक्त_irq;
	पूर्ण

	/* Calibrate the fg first समय */
	di->flags.calibrate = true;
	di->calib_state = AB8500_FG_CALIB_INIT;

	/* Use room temp as शेष value until we get an update from driver. */
	di->bat_temp = 210;

	/* Run the FG algorithm */
	queue_delayed_work(di->fg_wq, &di->fg_periodic_work, 0);

	list_add_tail(&di->node, &ab8500_fg_list);

	वापस ret;

मुक्त_irq:
	/* We also have to मुक्त all रेजिस्टरed irqs */
	जबतक (--i >= 0) अणु
		/* Last assignment of i from primary पूर्णांकerrupt handlers */
		irq = platक्रमm_get_irq_byname(pdev, ab8500_fg_irq[i].name);
		मुक्त_irq(irq, di);
	पूर्ण

	घातer_supply_unरेजिस्टर(di->fg_psy);
मुक्त_inst_curr_wq:
	destroy_workqueue(di->fg_wq);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ab8500_fg_pm_ops, ab8500_fg_suspend, ab8500_fg_resume);

अटल स्थिर काष्ठा of_device_id ab8500_fg_match[] = अणु
	अणु .compatible = "stericsson,ab8500-fg", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ab8500_fg_driver = अणु
	.probe = ab8500_fg_probe,
	.हटाओ = ab8500_fg_हटाओ,
	.driver = अणु
		.name = "ab8500-fg",
		.of_match_table = ab8500_fg_match,
		.pm = &ab8500_fg_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ab8500_fg_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ab8500_fg_driver);
पूर्ण

अटल व्योम __निकास ab8500_fg_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ab8500_fg_driver);
पूर्ण

subsys_initcall_sync(ab8500_fg_init);
module_निकास(ab8500_fg_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Johan Palsson, Karl Komierowski");
MODULE_ALIAS("platform:ab8500-fg");
MODULE_DESCRIPTION("AB8500 Fuel Gauge driver");
