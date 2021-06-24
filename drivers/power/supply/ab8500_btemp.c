<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Battery temperature driver क्रम AB8500
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
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/iio/consumer.h>

#समावेश "ab8500-bm.h"

#घोषणा VTVOUT_V			1800

#घोषणा BTEMP_THERMAL_LOW_LIMIT		-10
#घोषणा BTEMP_THERMAL_MED_LIMIT		0
#घोषणा BTEMP_THERMAL_HIGH_LIMIT_52	52
#घोषणा BTEMP_THERMAL_HIGH_LIMIT_57	57
#घोषणा BTEMP_THERMAL_HIGH_LIMIT_62	62

#घोषणा BTEMP_BATCTRL_CURR_SRC_7UA	7
#घोषणा BTEMP_BATCTRL_CURR_SRC_20UA	20

#घोषणा BTEMP_BATCTRL_CURR_SRC_16UA	16
#घोषणा BTEMP_BATCTRL_CURR_SRC_18UA	18

#घोषणा BTEMP_BATCTRL_CURR_SRC_60UA	60
#घोषणा BTEMP_BATCTRL_CURR_SRC_120UA	120

/**
 * काष्ठा ab8500_btemp_पूर्णांकerrupts - ab8500 पूर्णांकerrupts
 * @name:	name of the पूर्णांकerrupt
 * @isr		function poपूर्णांकer to the isr
 */
काष्ठा ab8500_btemp_पूर्णांकerrupts अणु
	अक्षर *name;
	irqवापस_t (*isr)(पूर्णांक irq, व्योम *data);
पूर्ण;

काष्ठा ab8500_btemp_events अणु
	bool batt_rem;
	bool btemp_high;
	bool btemp_medhigh;
	bool btemp_lowmed;
	bool btemp_low;
	bool ac_conn;
	bool usb_conn;
पूर्ण;

काष्ठा ab8500_btemp_ranges अणु
	पूर्णांक btemp_high_limit;
	पूर्णांक btemp_med_limit;
	पूर्णांक btemp_low_limit;
पूर्ण;

/**
 * काष्ठा ab8500_btemp - ab8500 BTEMP device inक्रमmation
 * @dev:		Poपूर्णांकer to the काष्ठाure device
 * @node:		List of AB8500 BTEMPs, hence prepared क्रम reentrance
 * @curr_source:	What current source we use, in uA
 * @bat_temp:		Dispatched battery temperature in degree Celsius
 * @prev_bat_temp	Last measured battery temperature in degree Celsius
 * @parent:		Poपूर्णांकer to the काष्ठा ab8500
 * @adc_btemp_ball:	ADC channel क्रम the battery ball temperature
 * @adc_bat_ctrl:	ADC channel क्रम the battery control
 * @fg:			Poपूर्णांकer to the काष्ठा fg
 * @bm:           	Platक्रमm specअगरic battery management inक्रमmation
 * @btemp_psy:		Structure क्रम BTEMP specअगरic battery properties
 * @events:		Structure क्रम inक्रमmation about events triggered
 * @btemp_ranges:	Battery temperature range काष्ठाure
 * @btemp_wq:		Work queue क्रम measuring the temperature periodically
 * @btemp_periodic_work:	Work क्रम measuring the temperature periodically
 * @initialized:	True अगर battery id पढ़ो.
 */
काष्ठा ab8500_btemp अणु
	काष्ठा device *dev;
	काष्ठा list_head node;
	पूर्णांक curr_source;
	पूर्णांक bat_temp;
	पूर्णांक prev_bat_temp;
	काष्ठा ab8500 *parent;
	काष्ठा iio_channel *btemp_ball;
	काष्ठा iio_channel *bat_ctrl;
	काष्ठा ab8500_fg *fg;
	काष्ठा abx500_bm_data *bm;
	काष्ठा घातer_supply *btemp_psy;
	काष्ठा ab8500_btemp_events events;
	काष्ठा ab8500_btemp_ranges btemp_ranges;
	काष्ठा workqueue_काष्ठा *btemp_wq;
	काष्ठा delayed_work btemp_periodic_work;
	bool initialized;
पूर्ण;

/* BTEMP घातer supply properties */
अटल क्रमागत घातer_supply_property ab8500_btemp_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल LIST_HEAD(ab8500_btemp_list);

/**
 * ab8500_btemp_batctrl_volt_to_res() - convert batctrl voltage to resistance
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 * @v_batctrl:	measured batctrl voltage
 * @inst_curr:	measured instant current
 *
 * This function वापसs the battery resistance that is
 * derived from the BATCTRL voltage.
 * Returns value in Ohms.
 */
अटल पूर्णांक ab8500_btemp_batctrl_volt_to_res(काष्ठा ab8500_btemp *di,
	पूर्णांक v_batctrl, पूर्णांक inst_curr)
अणु
	पूर्णांक rbs;

	अगर (is_ab8500_1p1_or_earlier(di->parent)) अणु
		/*
		 * For ABB cut1.0 and 1.1 BAT_CTRL is पूर्णांकernally
		 * connected to 1.8V through a 450k resistor
		 */
		वापस (450000 * (v_batctrl)) / (1800 - v_batctrl);
	पूर्ण

	अगर (di->bm->adc_therm == ABx500_ADC_THERM_BATCTRL) अणु
		/*
		 * If the battery has पूर्णांकernal NTC, we use the current
		 * source to calculate the resistance.
		 */
		rbs = (v_batctrl * 1000
		       - di->bm->gnd_lअगरt_resistance * inst_curr)
		      / di->curr_source;
	पूर्ण अन्यथा अणु
		/*
		 * BAT_CTRL is पूर्णांकernally
		 * connected to 1.8V through a 80k resistor
		 */
		rbs = (80000 * (v_batctrl)) / (1800 - v_batctrl);
	पूर्ण

	वापस rbs;
पूर्ण

/**
 * ab8500_btemp_पढ़ो_batctrl_voltage() - measure batctrl voltage
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 *
 * This function वापसs the voltage on BATCTRL. Returns value in mV.
 */
अटल पूर्णांक ab8500_btemp_पढ़ो_batctrl_voltage(काष्ठा ab8500_btemp *di)
अणु
	पूर्णांक vbtemp, ret;
	अटल पूर्णांक prev;

	ret = iio_पढ़ो_channel_processed(di->bat_ctrl, &vbtemp);
	अगर (ret < 0) अणु
		dev_err(di->dev,
			"%s ADC conversion failed, using previous value",
			__func__);
		वापस prev;
	पूर्ण
	prev = vbtemp;
	वापस vbtemp;
पूर्ण

/**
 * ab8500_btemp_curr_source_enable() - enable/disable batctrl current source
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 * @enable:	enable or disable the current source
 *
 * Enable or disable the current sources क्रम the BatCtrl AD channel
 */
अटल पूर्णांक ab8500_btemp_curr_source_enable(काष्ठा ab8500_btemp *di,
	bool enable)
अणु
	पूर्णांक curr;
	पूर्णांक ret = 0;

	/*
	 * BATCTRL current sources are included on AB8500 cut2.0
	 * and future versions
	 */
	अगर (is_ab8500_1p1_or_earlier(di->parent))
		वापस 0;

	/* Only करो this क्रम batteries with पूर्णांकernal NTC */
	अगर (di->bm->adc_therm == ABx500_ADC_THERM_BATCTRL && enable) अणु

		अगर (di->curr_source == BTEMP_BATCTRL_CURR_SRC_7UA)
			curr = BAT_CTRL_7U_ENA;
		अन्यथा
			curr = BAT_CTRL_20U_ENA;

		dev_dbg(di->dev, "Set BATCTRL %duA\n", di->curr_source);

		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER, AB8500_BAT_CTRL_CURRENT_SOURCE,
			FORCE_BAT_CTRL_CMP_HIGH, FORCE_BAT_CTRL_CMP_HIGH);
		अगर (ret) अणु
			dev_err(di->dev, "%s failed setting cmp_force\n",
				__func__);
			वापस ret;
		पूर्ण

		/*
		 * We have to रुको one 32kHz cycle beक्रमe enabling
		 * the current source, since ForceBatCtrlCmpHigh needs
		 * to be written in a separate cycle
		 */
		udelay(32);

		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER, AB8500_BAT_CTRL_CURRENT_SOURCE,
			FORCE_BAT_CTRL_CMP_HIGH | curr);
		अगर (ret) अणु
			dev_err(di->dev, "%s failed enabling current source\n",
				__func__);
			जाओ disable_curr_source;
		पूर्ण
	पूर्ण अन्यथा अगर (di->bm->adc_therm == ABx500_ADC_THERM_BATCTRL && !enable) अणु
		dev_dbg(di->dev, "Disable BATCTRL curr source\n");

		/* Write 0 to the curr bits */
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(
			di->dev,
			AB8500_CHARGER, AB8500_BAT_CTRL_CURRENT_SOURCE,
			BAT_CTRL_7U_ENA | BAT_CTRL_20U_ENA,
			~(BAT_CTRL_7U_ENA | BAT_CTRL_20U_ENA));

		अगर (ret) अणु
			dev_err(di->dev, "%s failed disabling current source\n",
				__func__);
			जाओ disable_curr_source;
		पूर्ण

		/* Enable Pull-Up and comparator */
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER,	AB8500_BAT_CTRL_CURRENT_SOURCE,
			BAT_CTRL_PULL_UP_ENA | BAT_CTRL_CMP_ENA,
			BAT_CTRL_PULL_UP_ENA | BAT_CTRL_CMP_ENA);
		अगर (ret) अणु
			dev_err(di->dev, "%s failed enabling PU and comp\n",
				__func__);
			जाओ enable_pu_comp;
		पूर्ण

		/*
		 * We have to रुको one 32kHz cycle beक्रमe disabling
		 * ForceBatCtrlCmpHigh since this needs to be written
		 * in a separate cycle
		 */
		udelay(32);

		/* Disable 'force comparator' */
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER, AB8500_BAT_CTRL_CURRENT_SOURCE,
			FORCE_BAT_CTRL_CMP_HIGH, ~FORCE_BAT_CTRL_CMP_HIGH);
		अगर (ret) अणु
			dev_err(di->dev, "%s failed disabling force comp\n",
				__func__);
			जाओ disable_क्रमce_comp;
		पूर्ण
	पूर्ण
	वापस ret;

	/*
	 * We have to try unsetting FORCE_BAT_CTRL_CMP_HIGH one more समय
	 * अगर we got an error above
	 */
disable_curr_source:
	/* Write 0 to the curr bits */
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER, AB8500_BAT_CTRL_CURRENT_SOURCE,
		BAT_CTRL_7U_ENA | BAT_CTRL_20U_ENA,
		~(BAT_CTRL_7U_ENA | BAT_CTRL_20U_ENA));

	अगर (ret) अणु
		dev_err(di->dev, "%s failed disabling current source\n",
			__func__);
		वापस ret;
	पूर्ण
enable_pu_comp:
	/* Enable Pull-Up and comparator */
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER,	AB8500_BAT_CTRL_CURRENT_SOURCE,
		BAT_CTRL_PULL_UP_ENA | BAT_CTRL_CMP_ENA,
		BAT_CTRL_PULL_UP_ENA | BAT_CTRL_CMP_ENA);
	अगर (ret) अणु
		dev_err(di->dev, "%s failed enabling PU and comp\n",
			__func__);
		वापस ret;
	पूर्ण

disable_क्रमce_comp:
	/*
	 * We have to रुको one 32kHz cycle beक्रमe disabling
	 * ForceBatCtrlCmpHigh since this needs to be written
	 * in a separate cycle
	 */
	udelay(32);

	/* Disable 'force comparator' */
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER, AB8500_BAT_CTRL_CURRENT_SOURCE,
		FORCE_BAT_CTRL_CMP_HIGH, ~FORCE_BAT_CTRL_CMP_HIGH);
	अगर (ret) अणु
		dev_err(di->dev, "%s failed disabling force comp\n",
			__func__);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ab8500_btemp_get_batctrl_res() - get battery resistance
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 *
 * This function वापसs the battery pack identअगरication resistance.
 * Returns value in Ohms.
 */
अटल पूर्णांक ab8500_btemp_get_batctrl_res(काष्ठा ab8500_btemp *di)
अणु
	पूर्णांक ret;
	पूर्णांक batctrl = 0;
	पूर्णांक res;
	पूर्णांक inst_curr;
	पूर्णांक i;

	/*
	 * BATCTRL current sources are included on AB8500 cut2.0
	 * and future versions
	 */
	ret = ab8500_btemp_curr_source_enable(di, true);
	अगर (ret) अणु
		dev_err(di->dev, "%s curr source enabled failed\n", __func__);
		वापस ret;
	पूर्ण

	अगर (!di->fg)
		di->fg = ab8500_fg_get();
	अगर (!di->fg) अणु
		dev_err(di->dev, "No fg found\n");
		वापस -EINVAL;
	पूर्ण

	ret = ab8500_fg_inst_curr_start(di->fg);

	अगर (ret) अणु
		dev_err(di->dev, "Failed to start current measurement\n");
		वापस ret;
	पूर्ण

	करो अणु
		msleep(20);
	पूर्ण जबतक (!ab8500_fg_inst_curr_started(di->fg));

	i = 0;

	करो अणु
		batctrl += ab8500_btemp_पढ़ो_batctrl_voltage(di);
		i++;
		msleep(20);
	पूर्ण जबतक (!ab8500_fg_inst_curr_करोne(di->fg));
	batctrl /= i;

	ret = ab8500_fg_inst_curr_finalize(di->fg, &inst_curr);
	अगर (ret) अणु
		dev_err(di->dev, "Failed to finalize current measurement\n");
		वापस ret;
	पूर्ण

	res = ab8500_btemp_batctrl_volt_to_res(di, batctrl, inst_curr);

	ret = ab8500_btemp_curr_source_enable(di, false);
	अगर (ret) अणु
		dev_err(di->dev, "%s curr source disable failed\n", __func__);
		वापस ret;
	पूर्ण

	dev_dbg(di->dev, "%s batctrl: %d res: %d inst_curr: %d samples: %d\n",
		__func__, batctrl, res, inst_curr, i);

	वापस res;
पूर्ण

/**
 * ab8500_btemp_res_to_temp() - resistance to temperature
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 * @tbl:	poपूर्णांकer to the resiatance to temperature table
 * @tbl_size:	size of the resistance to temperature table
 * @res:	resistance to calculate the temperature from
 *
 * This function वापसs the battery temperature in degrees Celsius
 * based on the NTC resistance.
 */
अटल पूर्णांक ab8500_btemp_res_to_temp(काष्ठा ab8500_btemp *di,
	स्थिर काष्ठा abx500_res_to_temp *tbl, पूर्णांक tbl_size, पूर्णांक res)
अणु
	पूर्णांक i;
	/*
	 * Calculate the क्रमmula क्रम the straight line
	 * Simple पूर्णांकerpolation अगर we are within
	 * the resistance table limits, extrapolate
	 * अगर resistance is outside the limits.
	 */
	अगर (res > tbl[0].resist)
		i = 0;
	अन्यथा अगर (res <= tbl[tbl_size - 1].resist)
		i = tbl_size - 2;
	अन्यथा अणु
		i = 0;
		जबतक (!(res <= tbl[i].resist &&
			res > tbl[i + 1].resist))
			i++;
	पूर्ण

	वापस tbl[i].temp + ((tbl[i + 1].temp - tbl[i].temp) *
		(res - tbl[i].resist)) / (tbl[i + 1].resist - tbl[i].resist);
पूर्ण

/**
 * ab8500_btemp_measure_temp() - measure battery temperature
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 *
 * Returns battery temperature (on success) अन्यथा the previous temperature
 */
अटल पूर्णांक ab8500_btemp_measure_temp(काष्ठा ab8500_btemp *di)
अणु
	पूर्णांक temp, ret;
	अटल पूर्णांक prev;
	पूर्णांक rbat, rntc, vntc;
	u8 id;

	id = di->bm->batt_id;

	अगर (di->bm->adc_therm == ABx500_ADC_THERM_BATCTRL &&
			id != BATTERY_UNKNOWN) अणु

		rbat = ab8500_btemp_get_batctrl_res(di);
		अगर (rbat < 0) अणु
			dev_err(di->dev, "%s get batctrl res failed\n",
				__func__);
			/*
			 * Return out-of-range temperature so that
			 * अक्षरging is stopped
			 */
			वापस BTEMP_THERMAL_LOW_LIMIT;
		पूर्ण

		temp = ab8500_btemp_res_to_temp(di,
			di->bm->bat_type[id].r_to_t_tbl,
			di->bm->bat_type[id].n_temp_tbl_elements, rbat);
	पूर्ण अन्यथा अणु
		ret = iio_पढ़ो_channel_processed(di->btemp_ball, &vntc);
		अगर (ret < 0) अणु
			dev_err(di->dev,
				"%s ADC conversion failed,"
				" using previous value\n", __func__);
			वापस prev;
		पूर्ण
		/*
		 * The PCB NTC is sourced from VTVOUT via a 230kOhm
		 * resistor.
		 */
		rntc = 230000 * vntc / (VTVOUT_V - vntc);

		temp = ab8500_btemp_res_to_temp(di,
			di->bm->bat_type[id].r_to_t_tbl,
			di->bm->bat_type[id].n_temp_tbl_elements, rntc);
		prev = temp;
	पूर्ण
	dev_dbg(di->dev, "Battery temperature is %d\n", temp);
	वापस temp;
पूर्ण

/**
 * ab8500_btemp_id() - Identअगरy the connected battery
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 *
 * This function will try to identअगरy the battery by पढ़ोing the ID
 * resistor. Some bअक्रमs use a combined ID resistor with a NTC resistor to
 * both be able to identअगरy and to पढ़ो the temperature of it.
 */
अटल पूर्णांक ab8500_btemp_id(काष्ठा ab8500_btemp *di)
अणु
	पूर्णांक res;
	u8 i;

	di->curr_source = BTEMP_BATCTRL_CURR_SRC_7UA;
	di->bm->batt_id = BATTERY_UNKNOWN;

	res =  ab8500_btemp_get_batctrl_res(di);
	अगर (res < 0) अणु
		dev_err(di->dev, "%s get batctrl res failed\n", __func__);
		वापस -ENXIO;
	पूर्ण

	/* BATTERY_UNKNOWN is defined on position 0, skip it! */
	क्रम (i = BATTERY_UNKNOWN + 1; i < di->bm->n_btypes; i++) अणु
		अगर ((res <= di->bm->bat_type[i].resis_high) &&
			(res >= di->bm->bat_type[i].resis_low)) अणु
			dev_dbg(di->dev, "Battery detected on %s"
				" low %d < res %d < high: %d"
				" index: %d\n",
				di->bm->adc_therm == ABx500_ADC_THERM_BATCTRL ?
				"BATCTRL" : "BATTEMP",
				di->bm->bat_type[i].resis_low, res,
				di->bm->bat_type[i].resis_high, i);

			di->bm->batt_id = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (di->bm->batt_id == BATTERY_UNKNOWN) अणु
		dev_warn(di->dev, "Battery identified as unknown"
			", resistance %d Ohm\n", res);
		वापस -ENXIO;
	पूर्ण

	/*
	 * We only have to change current source अगर the
	 * detected type is Type 1.
	 */
	अगर (di->bm->adc_therm == ABx500_ADC_THERM_BATCTRL &&
	    di->bm->batt_id == 1) अणु
		dev_dbg(di->dev, "Set BATCTRL current source to 20uA\n");
		di->curr_source = BTEMP_BATCTRL_CURR_SRC_20UA;
	पूर्ण

	वापस di->bm->batt_id;
पूर्ण

/**
 * ab8500_btemp_periodic_work() - Measuring the temperature periodically
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work function क्रम measuring the temperature periodically
 */
अटल व्योम ab8500_btemp_periodic_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक पूर्णांकerval;
	पूर्णांक bat_temp;
	काष्ठा ab8500_btemp *di = container_of(work,
		काष्ठा ab8500_btemp, btemp_periodic_work.work);

	अगर (!di->initialized) अणु
		/* Identअगरy the battery */
		अगर (ab8500_btemp_id(di) < 0)
			dev_warn(di->dev, "failed to identify the battery\n");
	पूर्ण

	bat_temp = ab8500_btemp_measure_temp(di);
	/*
	 * Filter battery temperature.
	 * Allow direct updates on temperature only अगर two samples result in
	 * same temperature. Else only allow 1 degree change from previous
	 * reported value in the direction of the new measurement.
	 */
	अगर ((bat_temp == di->prev_bat_temp) || !di->initialized) अणु
		अगर ((di->bat_temp != di->prev_bat_temp) || !di->initialized) अणु
			di->initialized = true;
			di->bat_temp = bat_temp;
			घातer_supply_changed(di->btemp_psy);
		पूर्ण
	पूर्ण अन्यथा अगर (bat_temp < di->prev_bat_temp) अणु
		di->bat_temp--;
		घातer_supply_changed(di->btemp_psy);
	पूर्ण अन्यथा अगर (bat_temp > di->prev_bat_temp) अणु
		di->bat_temp++;
		घातer_supply_changed(di->btemp_psy);
	पूर्ण
	di->prev_bat_temp = bat_temp;

	अगर (di->events.ac_conn || di->events.usb_conn)
		पूर्णांकerval = di->bm->temp_पूर्णांकerval_chg;
	अन्यथा
		पूर्णांकerval = di->bm->temp_पूर्णांकerval_nochg;

	/* Schedule a new measurement */
	queue_delayed_work(di->btemp_wq,
		&di->btemp_periodic_work,
		round_jअगरfies(पूर्णांकerval * HZ));
पूर्ण

/**
 * ab8500_btemp_batctrlindb_handler() - battery removal detected
 * @irq:       पूर्णांकerrupt number
 * @_di:       व्योम poपूर्णांकer that has to address of ab8500_btemp
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_btemp_batctrlindb_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_btemp *di = _di;
	dev_err(di->dev, "Battery removal detected!\n");

	di->events.batt_rem = true;
	घातer_supply_changed(di->btemp_psy);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_btemp_templow_handler() - battery temp lower than 10 degrees
 * @irq:       पूर्णांकerrupt number
 * @_di:       व्योम poपूर्णांकer that has to address of ab8500_btemp
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_btemp_templow_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_btemp *di = _di;

	अगर (is_ab8500_3p3_or_earlier(di->parent)) अणु
		dev_dbg(di->dev, "Ignore false btemp low irq"
			" for ABB cut 1.0, 1.1, 2.0 and 3.3\n");
	पूर्ण अन्यथा अणु
		dev_crit(di->dev, "Battery temperature lower than -10deg c\n");

		di->events.btemp_low = true;
		di->events.btemp_high = false;
		di->events.btemp_medhigh = false;
		di->events.btemp_lowmed = false;
		घातer_supply_changed(di->btemp_psy);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_btemp_temphigh_handler() - battery temp higher than max temp
 * @irq:       पूर्णांकerrupt number
 * @_di:       व्योम poपूर्णांकer that has to address of ab8500_btemp
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_btemp_temphigh_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_btemp *di = _di;

	dev_crit(di->dev, "Battery temperature is higher than MAX temp\n");

	di->events.btemp_high = true;
	di->events.btemp_medhigh = false;
	di->events.btemp_lowmed = false;
	di->events.btemp_low = false;
	घातer_supply_changed(di->btemp_psy);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_btemp_lowmed_handler() - battery temp between low and medium
 * @irq:       पूर्णांकerrupt number
 * @_di:       व्योम poपूर्णांकer that has to address of ab8500_btemp
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_btemp_lowmed_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_btemp *di = _di;

	dev_dbg(di->dev, "Battery temperature is between low and medium\n");

	di->events.btemp_lowmed = true;
	di->events.btemp_medhigh = false;
	di->events.btemp_high = false;
	di->events.btemp_low = false;
	घातer_supply_changed(di->btemp_psy);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_btemp_medhigh_handler() - battery temp between medium and high
 * @irq:       पूर्णांकerrupt number
 * @_di:       व्योम poपूर्णांकer that has to address of ab8500_btemp
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_btemp_medhigh_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_btemp *di = _di;

	dev_dbg(di->dev, "Battery temperature is between medium and high\n");

	di->events.btemp_medhigh = true;
	di->events.btemp_lowmed = false;
	di->events.btemp_high = false;
	di->events.btemp_low = false;
	घातer_supply_changed(di->btemp_psy);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_btemp_periodic() - Periodic temperature measurements
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 * @enable:	enable or disable periodic temperature measurements
 *
 * Starts of stops periodic temperature measurements. Periodic measurements
 * should only be करोne when a अक्षरger is connected.
 */
अटल व्योम ab8500_btemp_periodic(काष्ठा ab8500_btemp *di,
	bool enable)
अणु
	dev_dbg(di->dev, "Enable periodic temperature measurements: %d\n",
		enable);
	/*
	 * Make sure a new measurement is करोne directly by cancelling
	 * any pending work
	 */
	cancel_delayed_work_sync(&di->btemp_periodic_work);

	अगर (enable)
		queue_delayed_work(di->btemp_wq, &di->btemp_periodic_work, 0);
पूर्ण

/**
 * ab8500_btemp_get_temp() - get battery temperature
 * @di:		poपूर्णांकer to the ab8500_btemp काष्ठाure
 *
 * Returns battery temperature
 */
अटल पूर्णांक ab8500_btemp_get_temp(काष्ठा ab8500_btemp *di)
अणु
	पूर्णांक temp = 0;

	/*
	 * The BTEMP events are not reliabe on AB8500 cut3.3
	 * and prior versions
	 */
	अगर (is_ab8500_3p3_or_earlier(di->parent)) अणु
		temp = di->bat_temp * 10;
	पूर्ण अन्यथा अणु
		अगर (di->events.btemp_low) अणु
			अगर (temp > di->btemp_ranges.btemp_low_limit)
				temp = di->btemp_ranges.btemp_low_limit * 10;
			अन्यथा
				temp = di->bat_temp * 10;
		पूर्ण अन्यथा अगर (di->events.btemp_high) अणु
			अगर (temp < di->btemp_ranges.btemp_high_limit)
				temp = di->btemp_ranges.btemp_high_limit * 10;
			अन्यथा
				temp = di->bat_temp * 10;
		पूर्ण अन्यथा अगर (di->events.btemp_lowmed) अणु
			अगर (temp > di->btemp_ranges.btemp_med_limit)
				temp = di->btemp_ranges.btemp_med_limit * 10;
			अन्यथा
				temp = di->bat_temp * 10;
		पूर्ण अन्यथा अगर (di->events.btemp_medhigh) अणु
			अगर (temp < di->btemp_ranges.btemp_med_limit)
				temp = di->btemp_ranges.btemp_med_limit * 10;
			अन्यथा
				temp = di->bat_temp * 10;
		पूर्ण अन्यथा
			temp = di->bat_temp * 10;
	पूर्ण
	वापस temp;
पूर्ण

/**
 * ab8500_btemp_get_property() - get the btemp properties
 * @psy:        poपूर्णांकer to the घातer_supply काष्ठाure
 * @psp:        poपूर्णांकer to the घातer_supply_property काष्ठाure
 * @val:        poपूर्णांकer to the घातer_supply_propval जोड़
 *
 * This function माला_लो called when an application tries to get the btemp
 * properties by पढ़ोing the sysfs files.
 * online:	presence of the battery
 * present:	presence of the battery
 * technology:	battery technology
 * temp:	battery temperature
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_btemp_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ab8500_btemp *di = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
	हाल POWER_SUPPLY_PROP_ONLINE:
		अगर (di->events.batt_rem)
			val->पूर्णांकval = 0;
		अन्यथा
			val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = di->bm->bat_type[di->bm->batt_id].name;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = ab8500_btemp_get_temp(di);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_btemp_get_ext_psy_data(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply *ext = dev_get_drvdata(dev);
	स्थिर अक्षर **supplicants = (स्थिर अक्षर **)ext->supplied_to;
	काष्ठा ab8500_btemp *di;
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
		हाल POWER_SUPPLY_PROP_PRESENT:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_MAINS:
				/* AC disconnected */
				अगर (!ret.पूर्णांकval && di->events.ac_conn) अणु
					di->events.ac_conn = false;
				पूर्ण
				/* AC connected */
				अन्यथा अगर (ret.पूर्णांकval && !di->events.ac_conn) अणु
					di->events.ac_conn = true;
					अगर (!di->events.usb_conn)
						ab8500_btemp_periodic(di, true);
				पूर्ण
				अवरोध;
			हाल POWER_SUPPLY_TYPE_USB:
				/* USB disconnected */
				अगर (!ret.पूर्णांकval && di->events.usb_conn) अणु
					di->events.usb_conn = false;
				पूर्ण
				/* USB connected */
				अन्यथा अगर (ret.पूर्णांकval && !di->events.usb_conn) अणु
					di->events.usb_conn = true;
					अगर (!di->events.ac_conn)
						ab8500_btemp_periodic(di, true);
				पूर्ण
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
 * ab8500_btemp_बाह्यal_घातer_changed() - callback क्रम घातer supply changes
 * @psy:       poपूर्णांकer to the काष्ठाure घातer_supply
 *
 * This function is poपूर्णांकing to the function poपूर्णांकer बाह्यal_घातer_changed
 * of the काष्ठाure घातer_supply.
 * This function माला_लो executed when there is a change in the बाह्यal घातer
 * supply to the btemp.
 */
अटल व्योम ab8500_btemp_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा ab8500_btemp *di = घातer_supply_get_drvdata(psy);

	class_क्रम_each_device(घातer_supply_class, शून्य,
		di->btemp_psy, ab8500_btemp_get_ext_psy_data);
पूर्ण

/* ab8500 btemp driver पूर्णांकerrupts and their respective isr */
अटल काष्ठा ab8500_btemp_पूर्णांकerrupts ab8500_btemp_irq[] = अणु
	अणु"BAT_CTRL_INDB", ab8500_btemp_batctrlindb_handlerपूर्ण,
	अणु"BTEMP_LOW", ab8500_btemp_templow_handlerपूर्ण,
	अणु"BTEMP_HIGH", ab8500_btemp_temphigh_handlerपूर्ण,
	अणु"BTEMP_LOW_MEDIUM", ab8500_btemp_lowmed_handlerपूर्ण,
	अणु"BTEMP_MEDIUM_HIGH", ab8500_btemp_medhigh_handlerपूर्ण,
पूर्ण;

अटल पूर्णांक __maybe_unused ab8500_btemp_resume(काष्ठा device *dev)
अणु
	काष्ठा ab8500_btemp *di = dev_get_drvdata(dev);

	ab8500_btemp_periodic(di, true);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ab8500_btemp_suspend(काष्ठा device *dev)
अणु
	काष्ठा ab8500_btemp *di = dev_get_drvdata(dev);

	ab8500_btemp_periodic(di, false);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_btemp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500_btemp *di = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, irq;

	/* Disable पूर्णांकerrupts */
	क्रम (i = 0; i < ARRAY_SIZE(ab8500_btemp_irq); i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, ab8500_btemp_irq[i].name);
		मुक्त_irq(irq, di);
	पूर्ण

	/* Delete the work queue */
	destroy_workqueue(di->btemp_wq);

	flush_scheduled_work();
	घातer_supply_unरेजिस्टर(di->btemp_psy);

	वापस 0;
पूर्ण

अटल अक्षर *supply_पूर्णांकerface[] = अणु
	"ab8500_chargalg",
	"ab8500_fg",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc ab8500_btemp_desc = अणु
	.name			= "ab8500_btemp",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= ab8500_btemp_props,
	.num_properties		= ARRAY_SIZE(ab8500_btemp_props),
	.get_property		= ab8500_btemp_get_property,
	.बाह्यal_घातer_changed	= ab8500_btemp_बाह्यal_घातer_changed,
पूर्ण;

अटल पूर्णांक ab8500_btemp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ab8500_btemp *di;
	पूर्णांक irq, i, ret = 0;
	u8 val;

	di = devm_kzalloc(dev, माप(*di), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	di->bm = &ab8500_bm_data;

	ret = ab8500_bm_of_probe(dev, np, di->bm);
	अगर (ret) अणु
		dev_err(dev, "failed to get battery information\n");
		वापस ret;
	पूर्ण

	/* get parent data */
	di->dev = dev;
	di->parent = dev_get_drvdata(pdev->dev.parent);

	/* Get ADC channels */
	di->btemp_ball = devm_iio_channel_get(dev, "btemp_ball");
	अगर (IS_ERR(di->btemp_ball)) अणु
		ret = dev_err_probe(dev, PTR_ERR(di->btemp_ball),
				    "failed to get BTEMP BALL ADC channel\n");
		वापस ret;
	पूर्ण
	di->bat_ctrl = devm_iio_channel_get(dev, "bat_ctrl");
	अगर (IS_ERR(di->bat_ctrl)) अणु
		ret = dev_err_probe(dev, PTR_ERR(di->bat_ctrl),
				    "failed to get BAT CTRL ADC channel\n");
		वापस ret;
	पूर्ण

	di->initialized = false;

	psy_cfg.supplied_to = supply_पूर्णांकerface;
	psy_cfg.num_supplicants = ARRAY_SIZE(supply_पूर्णांकerface);
	psy_cfg.drv_data = di;

	/* Create a work queue क्रम the btemp */
	di->btemp_wq =
		alloc_workqueue("ab8500_btemp_wq", WQ_MEM_RECLAIM, 0);
	अगर (di->btemp_wq == शून्य) अणु
		dev_err(dev, "failed to create work queue\n");
		वापस -ENOMEM;
	पूर्ण

	/* Init work क्रम measuring temperature periodically */
	INIT_DEFERRABLE_WORK(&di->btemp_periodic_work,
		ab8500_btemp_periodic_work);

	/* Set BTEMP thermal limits. Low and Med are fixed */
	di->btemp_ranges.btemp_low_limit = BTEMP_THERMAL_LOW_LIMIT;
	di->btemp_ranges.btemp_med_limit = BTEMP_THERMAL_MED_LIMIT;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_CHARGER,
		AB8500_BTEMP_HIGH_TH, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "%s ab8500 read failed\n", __func__);
		जाओ मुक्त_btemp_wq;
	पूर्ण
	चयन (val) अणु
	हाल BTEMP_HIGH_TH_57_0:
	हाल BTEMP_HIGH_TH_57_1:
		di->btemp_ranges.btemp_high_limit =
			BTEMP_THERMAL_HIGH_LIMIT_57;
		अवरोध;
	हाल BTEMP_HIGH_TH_52:
		di->btemp_ranges.btemp_high_limit =
			BTEMP_THERMAL_HIGH_LIMIT_52;
		अवरोध;
	हाल BTEMP_HIGH_TH_62:
		di->btemp_ranges.btemp_high_limit =
			BTEMP_THERMAL_HIGH_LIMIT_62;
		अवरोध;
	पूर्ण

	/* Register BTEMP घातer supply class */
	di->btemp_psy = घातer_supply_रेजिस्टर(dev, &ab8500_btemp_desc,
					      &psy_cfg);
	अगर (IS_ERR(di->btemp_psy)) अणु
		dev_err(dev, "failed to register BTEMP psy\n");
		ret = PTR_ERR(di->btemp_psy);
		जाओ मुक्त_btemp_wq;
	पूर्ण

	/* Register पूर्णांकerrupts */
	क्रम (i = 0; i < ARRAY_SIZE(ab8500_btemp_irq); i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, ab8500_btemp_irq[i].name);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ मुक्त_irq;
		पूर्ण

		ret = request_thपढ़ोed_irq(irq, शून्य, ab8500_btemp_irq[i].isr,
			IRQF_SHARED | IRQF_NO_SUSPEND | IRQF_ONESHOT,
			ab8500_btemp_irq[i].name, di);

		अगर (ret) अणु
			dev_err(dev, "failed to request %s IRQ %d: %d\n"
				, ab8500_btemp_irq[i].name, irq, ret);
			जाओ मुक्त_irq;
		पूर्ण
		dev_dbg(dev, "Requested %s IRQ %d: %d\n",
			ab8500_btemp_irq[i].name, irq, ret);
	पूर्ण

	platक्रमm_set_drvdata(pdev, di);

	/* Kick off periodic temperature measurements */
	ab8500_btemp_periodic(di, true);
	list_add_tail(&di->node, &ab8500_btemp_list);

	वापस ret;

मुक्त_irq:
	/* We also have to मुक्त all successfully रेजिस्टरed irqs */
	क्रम (i = i - 1; i >= 0; i--) अणु
		irq = platक्रमm_get_irq_byname(pdev, ab8500_btemp_irq[i].name);
		मुक्त_irq(irq, di);
	पूर्ण

	घातer_supply_unरेजिस्टर(di->btemp_psy);
मुक्त_btemp_wq:
	destroy_workqueue(di->btemp_wq);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ab8500_btemp_pm_ops, ab8500_btemp_suspend, ab8500_btemp_resume);

अटल स्थिर काष्ठा of_device_id ab8500_btemp_match[] = अणु
	अणु .compatible = "stericsson,ab8500-btemp", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ab8500_btemp_driver = अणु
	.probe = ab8500_btemp_probe,
	.हटाओ = ab8500_btemp_हटाओ,
	.driver = अणु
		.name = "ab8500-btemp",
		.of_match_table = ab8500_btemp_match,
		.pm = &ab8500_btemp_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ab8500_btemp_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ab8500_btemp_driver);
पूर्ण

अटल व्योम __निकास ab8500_btemp_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ab8500_btemp_driver);
पूर्ण

device_initcall(ab8500_btemp_init);
module_निकास(ab8500_btemp_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Johan Palsson, Karl Komierowski, Arun R Murthy");
MODULE_ALIAS("platform:ab8500-btemp");
MODULE_DESCRIPTION("AB8500 battery temperature driver");
