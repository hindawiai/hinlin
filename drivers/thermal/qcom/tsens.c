<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 * Copyright (c) 2019, 2020, Linaro Ltd.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>
#समावेश "tsens.h"

/**
 * काष्ठा tsens_irq_data - IRQ status and temperature violations
 * @up_viol:        upper threshold violated
 * @up_thresh:      upper threshold temperature value
 * @up_irq_mask:    mask रेजिस्टर क्रम upper threshold irqs
 * @up_irq_clear:   clear रेजिस्टर क्रम uppper threshold irqs
 * @low_viol:       lower threshold violated
 * @low_thresh:     lower threshold temperature value
 * @low_irq_mask:   mask रेजिस्टर क्रम lower threshold irqs
 * @low_irq_clear:  clear रेजिस्टर क्रम lower threshold irqs
 * @crit_viol:      critical threshold violated
 * @crit_thresh:    critical threshold temperature value
 * @crit_irq_mask:  mask रेजिस्टर क्रम critical threshold irqs
 * @crit_irq_clear: clear रेजिस्टर क्रम critical threshold irqs
 *
 * Structure containing data about temperature threshold settings and
 * irq status अगर they were violated.
 */
काष्ठा tsens_irq_data अणु
	u32 up_viol;
	पूर्णांक up_thresh;
	u32 up_irq_mask;
	u32 up_irq_clear;
	u32 low_viol;
	पूर्णांक low_thresh;
	u32 low_irq_mask;
	u32 low_irq_clear;
	u32 crit_viol;
	u32 crit_thresh;
	u32 crit_irq_mask;
	u32 crit_irq_clear;
पूर्ण;

अक्षर *qfprom_पढ़ो(काष्ठा device *dev, स्थिर अक्षर *cname)
अणु
	काष्ठा nvmem_cell *cell;
	sमाप_प्रकार data;
	अक्षर *ret;

	cell = nvmem_cell_get(dev, cname);
	अगर (IS_ERR(cell))
		वापस ERR_CAST(cell);

	ret = nvmem_cell_पढ़ो(cell, &data);
	nvmem_cell_put(cell);

	वापस ret;
पूर्ण

/*
 * Use this function on devices where slope and offset calculations
 * depend on calibration data पढ़ो from qfprom. On others the slope
 * and offset values are derived from tz->tzp->slope and tz->tzp->offset
 * resp.
 */
व्योम compute_पूर्णांकercept_slope(काष्ठा tsens_priv *priv, u32 *p1,
			     u32 *p2, u32 mode)
अणु
	पूर्णांक i;
	पूर्णांक num, den;

	क्रम (i = 0; i < priv->num_sensors; i++) अणु
		dev_dbg(priv->dev,
			"%s: sensor%d - data_point1:%#x data_point2:%#x\n",
			__func__, i, p1[i], p2[i]);

		अगर (!priv->sensor[i].slope)
			priv->sensor[i].slope = SLOPE_DEFAULT;
		अगर (mode == TWO_PT_CALIB) अणु
			/*
			 * slope (m) = adc_code2 - adc_code1 (y2 - y1)/
			 *	temp_120_degc - temp_30_degc (x2 - x1)
			 */
			num = p2[i] - p1[i];
			num *= SLOPE_FACTOR;
			den = CAL_DEGC_PT2 - CAL_DEGC_PT1;
			priv->sensor[i].slope = num / den;
		पूर्ण

		priv->sensor[i].offset = (p1[i] * SLOPE_FACTOR) -
				(CAL_DEGC_PT1 *
				priv->sensor[i].slope);
		dev_dbg(priv->dev, "%s: offset:%d\n", __func__,
			priv->sensor[i].offset);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 degc_to_code(पूर्णांक degc, स्थिर काष्ठा tsens_sensor *s)
अणु
	u64 code = भाग_u64(((u64)degc * s->slope + s->offset), SLOPE_FACTOR);

	pr_debug("%s: raw_code: 0x%llx, degc:%d\n", __func__, code, degc);
	वापस clamp_val(code, THRESHOLD_MIN_ADC_CODE, THRESHOLD_MAX_ADC_CODE);
पूर्ण

अटल अंतरभूत पूर्णांक code_to_degc(u32 adc_code, स्थिर काष्ठा tsens_sensor *s)
अणु
	पूर्णांक degc, num, den;

	num = (adc_code * SLOPE_FACTOR) - s->offset;
	den = s->slope;

	अगर (num > 0)
		degc = num + (den / 2);
	अन्यथा अगर (num < 0)
		degc = num - (den / 2);
	अन्यथा
		degc = num;

	degc /= den;

	वापस degc;
पूर्ण

/**
 * tsens_hw_to_mC - Return sign-extended temperature in mCelsius.
 * @s:     Poपूर्णांकer to sensor काष्ठा
 * @field: Index पूर्णांकo regmap_field array poपूर्णांकing to temperature data
 *
 * This function handles temperature वापसed in ADC code or deciCelsius
 * depending on IP version.
 *
 * Return: Temperature in milliCelsius on success, a negative त्रुटि_सं will
 * be वापसed in error हालs
 */
अटल पूर्णांक tsens_hw_to_mC(स्थिर काष्ठा tsens_sensor *s, पूर्णांक field)
अणु
	काष्ठा tsens_priv *priv = s->priv;
	u32 resolution;
	u32 temp = 0;
	पूर्णांक ret;

	resolution = priv->fields[LAST_TEMP_0].msb -
		priv->fields[LAST_TEMP_0].lsb;

	ret = regmap_field_पढ़ो(priv->rf[field], &temp);
	अगर (ret)
		वापस ret;

	/* Convert temperature from ADC code to milliCelsius */
	अगर (priv->feat->adc)
		वापस code_to_degc(temp, s) * 1000;

	/* deciCelsius -> milliCelsius aदीर्घ with sign extension */
	वापस sign_extend32(temp, resolution) * 100;
पूर्ण

/**
 * tsens_mC_to_hw - Convert temperature to hardware रेजिस्टर value
 * @s: Poपूर्णांकer to sensor काष्ठा
 * @temp: temperature in milliCelsius to be programmed to hardware
 *
 * This function outमाला_दो the value to be written to hardware in ADC code
 * or deciCelsius depending on IP version.
 *
 * Return: ADC code or temperature in deciCelsius.
 */
अटल पूर्णांक tsens_mC_to_hw(स्थिर काष्ठा tsens_sensor *s, पूर्णांक temp)
अणु
	काष्ठा tsens_priv *priv = s->priv;

	/* milliC to adc code */
	अगर (priv->feat->adc)
		वापस degc_to_code(temp / 1000, s);

	/* milliC to deciC */
	वापस temp / 100;
पूर्ण

अटल अंतरभूत क्रमागत tsens_ver tsens_version(काष्ठा tsens_priv *priv)
अणु
	वापस priv->feat->ver_major;
पूर्ण

अटल व्योम tsens_set_पूर्णांकerrupt_v1(काष्ठा tsens_priv *priv, u32 hw_id,
				   क्रमागत tsens_irq_type irq_type, bool enable)
अणु
	u32 index = 0;

	चयन (irq_type) अणु
	हाल UPPER:
		index = UP_INT_CLEAR_0 + hw_id;
		अवरोध;
	हाल LOWER:
		index = LOW_INT_CLEAR_0 + hw_id;
		अवरोध;
	हाल CRITICAL:
		/* No critical पूर्णांकerrupts beक्रमe v2 */
		वापस;
	पूर्ण
	regmap_field_ग_लिखो(priv->rf[index], enable ? 0 : 1);
पूर्ण

अटल व्योम tsens_set_पूर्णांकerrupt_v2(काष्ठा tsens_priv *priv, u32 hw_id,
				   क्रमागत tsens_irq_type irq_type, bool enable)
अणु
	u32 index_mask = 0, index_clear = 0;

	/*
	 * To enable the पूर्णांकerrupt flag क्रम a sensor:
	 *    - clear the mask bit
	 * To disable the पूर्णांकerrupt flag क्रम a sensor:
	 *    - Mask further पूर्णांकerrupts क्रम this sensor
	 *    - Write 1 followed by 0 to clear the पूर्णांकerrupt
	 */
	चयन (irq_type) अणु
	हाल UPPER:
		index_mask  = UP_INT_MASK_0 + hw_id;
		index_clear = UP_INT_CLEAR_0 + hw_id;
		अवरोध;
	हाल LOWER:
		index_mask  = LOW_INT_MASK_0 + hw_id;
		index_clear = LOW_INT_CLEAR_0 + hw_id;
		अवरोध;
	हाल CRITICAL:
		index_mask  = CRIT_INT_MASK_0 + hw_id;
		index_clear = CRIT_INT_CLEAR_0 + hw_id;
		अवरोध;
	पूर्ण

	अगर (enable) अणु
		regmap_field_ग_लिखो(priv->rf[index_mask], 0);
	पूर्ण अन्यथा अणु
		regmap_field_ग_लिखो(priv->rf[index_mask],  1);
		regmap_field_ग_लिखो(priv->rf[index_clear], 1);
		regmap_field_ग_लिखो(priv->rf[index_clear], 0);
	पूर्ण
पूर्ण

/**
 * tsens_set_पूर्णांकerrupt - Set state of an पूर्णांकerrupt
 * @priv: Poपूर्णांकer to tsens controller निजी data
 * @hw_id: Hardware ID aka. sensor number
 * @irq_type: irq_type from क्रमागत tsens_irq_type
 * @enable: false = disable, true = enable
 *
 * Call IP-specअगरic function to set state of an पूर्णांकerrupt
 *
 * Return: व्योम
 */
अटल व्योम tsens_set_पूर्णांकerrupt(काष्ठा tsens_priv *priv, u32 hw_id,
				क्रमागत tsens_irq_type irq_type, bool enable)
अणु
	dev_dbg(priv->dev, "[%u] %s: %s -> %s\n", hw_id, __func__,
		irq_type ? ((irq_type == 1) ? "UP" : "CRITICAL") : "LOW",
		enable ? "en" : "dis");
	अगर (tsens_version(priv) > VER_1_X)
		tsens_set_पूर्णांकerrupt_v2(priv, hw_id, irq_type, enable);
	अन्यथा
		tsens_set_पूर्णांकerrupt_v1(priv, hw_id, irq_type, enable);
पूर्ण

/**
 * tsens_threshold_violated - Check अगर a sensor temperature violated a preset threshold
 * @priv: Poपूर्णांकer to tsens controller निजी data
 * @hw_id: Hardware ID aka. sensor number
 * @d: Poपूर्णांकer to irq state data
 *
 * Return: 0 अगर threshold was not violated, 1 अगर it was violated and negative
 * त्रुटि_सं in हाल of errors
 */
अटल पूर्णांक tsens_threshold_violated(काष्ठा tsens_priv *priv, u32 hw_id,
				    काष्ठा tsens_irq_data *d)
अणु
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(priv->rf[UPPER_STATUS_0 + hw_id], &d->up_viol);
	अगर (ret)
		वापस ret;
	ret = regmap_field_पढ़ो(priv->rf[LOWER_STATUS_0 + hw_id], &d->low_viol);
	अगर (ret)
		वापस ret;

	अगर (priv->feat->crit_पूर्णांक) अणु
		ret = regmap_field_पढ़ो(priv->rf[CRITICAL_STATUS_0 + hw_id],
					&d->crit_viol);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (d->up_viol || d->low_viol || d->crit_viol)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक tsens_पढ़ो_irq_state(काष्ठा tsens_priv *priv, u32 hw_id,
				स्थिर काष्ठा tsens_sensor *s,
				काष्ठा tsens_irq_data *d)
अणु
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(priv->rf[UP_INT_CLEAR_0 + hw_id], &d->up_irq_clear);
	अगर (ret)
		वापस ret;
	ret = regmap_field_पढ़ो(priv->rf[LOW_INT_CLEAR_0 + hw_id], &d->low_irq_clear);
	अगर (ret)
		वापस ret;
	अगर (tsens_version(priv) > VER_1_X) अणु
		ret = regmap_field_पढ़ो(priv->rf[UP_INT_MASK_0 + hw_id], &d->up_irq_mask);
		अगर (ret)
			वापस ret;
		ret = regmap_field_पढ़ो(priv->rf[LOW_INT_MASK_0 + hw_id], &d->low_irq_mask);
		अगर (ret)
			वापस ret;
		ret = regmap_field_पढ़ो(priv->rf[CRIT_INT_CLEAR_0 + hw_id],
					&d->crit_irq_clear);
		अगर (ret)
			वापस ret;
		ret = regmap_field_पढ़ो(priv->rf[CRIT_INT_MASK_0 + hw_id],
					&d->crit_irq_mask);
		अगर (ret)
			वापस ret;

		d->crit_thresh = tsens_hw_to_mC(s, CRIT_THRESH_0 + hw_id);
	पूर्ण अन्यथा अणु
		/* No mask रेजिस्टर on older TSENS */
		d->up_irq_mask = 0;
		d->low_irq_mask = 0;
		d->crit_irq_clear = 0;
		d->crit_irq_mask = 0;
		d->crit_thresh = 0;
	पूर्ण

	d->up_thresh  = tsens_hw_to_mC(s, UP_THRESH_0 + hw_id);
	d->low_thresh = tsens_hw_to_mC(s, LOW_THRESH_0 + hw_id);

	dev_dbg(priv->dev, "[%u] %s%s: status(%u|%u|%u) | clr(%u|%u|%u) | mask(%u|%u|%u)\n",
		hw_id, __func__,
		(d->up_viol || d->low_viol || d->crit_viol) ? "(V)" : "",
		d->low_viol, d->up_viol, d->crit_viol,
		d->low_irq_clear, d->up_irq_clear, d->crit_irq_clear,
		d->low_irq_mask, d->up_irq_mask, d->crit_irq_mask);
	dev_dbg(priv->dev, "[%u] %s%s: thresh: (%d:%d:%d)\n", hw_id, __func__,
		(d->up_viol || d->low_viol || d->crit_viol) ? "(V)" : "",
		d->low_thresh, d->up_thresh, d->crit_thresh);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 masked_irq(u32 hw_id, u32 mask, क्रमागत tsens_ver ver)
अणु
	अगर (ver > VER_1_X)
		वापस mask & (1 << hw_id);

	/* v1, v0.1 करोn't have a irq mask रेजिस्टर */
	वापस 0;
पूर्ण

/**
 * tsens_critical_irq_thपढ़ो() - Thपढ़ोed handler क्रम critical पूर्णांकerrupts
 * @irq: irq number
 * @data: tsens controller निजी data
 *
 * Check FSM watchकरोg bark status and clear अगर needed.
 * Check all sensors to find ones that violated their critical threshold limits.
 * Clear and then re-enable the पूर्णांकerrupt.
 *
 * The level-triggered पूर्णांकerrupt might deनिश्चित अगर the temperature वापसed to
 * within the threshold limits by the समय the handler got scheduled. We
 * consider the irq to have been handled in that हाल.
 *
 * Return: IRQ_HANDLED
 */
अटल irqवापस_t tsens_critical_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tsens_priv *priv = data;
	काष्ठा tsens_irq_data d;
	पूर्णांक temp, ret, i;
	u32 wकरोg_status, wकरोg_count;

	अगर (priv->feat->has_watchकरोg) अणु
		ret = regmap_field_पढ़ो(priv->rf[WDOG_BARK_STATUS],
					&wकरोg_status);
		अगर (ret)
			वापस ret;

		अगर (wकरोg_status) अणु
			/* Clear WDOG पूर्णांकerrupt */
			regmap_field_ग_लिखो(priv->rf[WDOG_BARK_CLEAR], 1);
			regmap_field_ग_लिखो(priv->rf[WDOG_BARK_CLEAR], 0);
			ret = regmap_field_पढ़ो(priv->rf[WDOG_BARK_COUNT],
						&wकरोg_count);
			अगर (ret)
				वापस ret;
			अगर (wकरोg_count)
				dev_dbg(priv->dev, "%s: watchdog count: %d\n",
					__func__, wकरोg_count);

			/* Fall through to handle critical पूर्णांकerrupts अगर any */
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < priv->num_sensors; i++) अणु
		स्थिर काष्ठा tsens_sensor *s = &priv->sensor[i];
		u32 hw_id = s->hw_id;

		अगर (IS_ERR(s->tzd))
			जारी;
		अगर (!tsens_threshold_violated(priv, hw_id, &d))
			जारी;
		ret = get_temp_tsens_valid(s, &temp);
		अगर (ret) अणु
			dev_err(priv->dev, "[%u] %s: error reading sensor\n",
				hw_id, __func__);
			जारी;
		पूर्ण

		tsens_पढ़ो_irq_state(priv, hw_id, s, &d);
		अगर (d.crit_viol &&
		    !masked_irq(hw_id, d.crit_irq_mask, tsens_version(priv))) अणु
			/* Mask critical पूर्णांकerrupts, unused on Linux */
			tsens_set_पूर्णांकerrupt(priv, hw_id, CRITICAL, false);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * tsens_irq_thपढ़ो - Thपढ़ोed पूर्णांकerrupt handler क्रम uplow पूर्णांकerrupts
 * @irq: irq number
 * @data: tsens controller निजी data
 *
 * Check all sensors to find ones that violated their threshold limits. If the
 * temperature is still outside the limits, call thermal_zone_device_update() to
 * update the thresholds, अन्यथा re-enable the पूर्णांकerrupts.
 *
 * The level-triggered पूर्णांकerrupt might deनिश्चित अगर the temperature वापसed to
 * within the threshold limits by the समय the handler got scheduled. We
 * consider the irq to have been handled in that हाल.
 *
 * Return: IRQ_HANDLED
 */
अटल irqवापस_t tsens_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tsens_priv *priv = data;
	काष्ठा tsens_irq_data d;
	bool enable = true, disable = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक temp, ret, i;

	क्रम (i = 0; i < priv->num_sensors; i++) अणु
		bool trigger = false;
		स्थिर काष्ठा tsens_sensor *s = &priv->sensor[i];
		u32 hw_id = s->hw_id;

		अगर (IS_ERR(s->tzd))
			जारी;
		अगर (!tsens_threshold_violated(priv, hw_id, &d))
			जारी;
		ret = get_temp_tsens_valid(s, &temp);
		अगर (ret) अणु
			dev_err(priv->dev, "[%u] %s: error reading sensor\n",
				hw_id, __func__);
			जारी;
		पूर्ण

		spin_lock_irqsave(&priv->ul_lock, flags);

		tsens_पढ़ो_irq_state(priv, hw_id, s, &d);

		अगर (d.up_viol &&
		    !masked_irq(hw_id, d.up_irq_mask, tsens_version(priv))) अणु
			tsens_set_पूर्णांकerrupt(priv, hw_id, UPPER, disable);
			अगर (d.up_thresh > temp) अणु
				dev_dbg(priv->dev, "[%u] %s: re-arm upper\n",
					hw_id, __func__);
				tsens_set_पूर्णांकerrupt(priv, hw_id, UPPER, enable);
			पूर्ण अन्यथा अणु
				trigger = true;
				/* Keep irq masked */
			पूर्ण
		पूर्ण अन्यथा अगर (d.low_viol &&
			   !masked_irq(hw_id, d.low_irq_mask, tsens_version(priv))) अणु
			tsens_set_पूर्णांकerrupt(priv, hw_id, LOWER, disable);
			अगर (d.low_thresh < temp) अणु
				dev_dbg(priv->dev, "[%u] %s: re-arm low\n",
					hw_id, __func__);
				tsens_set_पूर्णांकerrupt(priv, hw_id, LOWER, enable);
			पूर्ण अन्यथा अणु
				trigger = true;
				/* Keep irq masked */
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&priv->ul_lock, flags);

		अगर (trigger) अणु
			dev_dbg(priv->dev, "[%u] %s: TZ update trigger (%d mC)\n",
				hw_id, __func__, temp);
			thermal_zone_device_update(s->tzd,
						   THERMAL_EVENT_UNSPECIFIED);
		पूर्ण अन्यथा अणु
			dev_dbg(priv->dev, "[%u] %s: no violation:  %d\n",
				hw_id, __func__, temp);
		पूर्ण

		अगर (tsens_version(priv) < VER_0_1) अणु
			/* Constraपूर्णांक: There is only 1 पूर्णांकerrupt control रेजिस्टर क्रम all
			 * 11 temperature sensor. So monitoring more than 1 sensor based
			 * on पूर्णांकerrupts will yield inconsistent result. To overcome this
			 * issue we will monitor only sensor 0 which is the master sensor.
			 */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tsens_set_trips(व्योम *_sensor, पूर्णांक low, पूर्णांक high)
अणु
	काष्ठा tsens_sensor *s = _sensor;
	काष्ठा tsens_priv *priv = s->priv;
	काष्ठा device *dev = priv->dev;
	काष्ठा tsens_irq_data d;
	अचिन्हित दीर्घ flags;
	पूर्णांक high_val, low_val, cl_high, cl_low;
	u32 hw_id = s->hw_id;

	अगर (tsens_version(priv) < VER_0_1) अणु
		/* Pre v0.1 IP had a single रेजिस्टर क्रम each type of पूर्णांकerrupt
		 * and thresholds
		 */
		hw_id = 0;
	पूर्ण

	dev_dbg(dev, "[%u] %s: proposed thresholds: (%d:%d)\n",
		hw_id, __func__, low, high);

	cl_high = clamp_val(high, -40000, 120000);
	cl_low  = clamp_val(low, -40000, 120000);

	high_val = tsens_mC_to_hw(s, cl_high);
	low_val  = tsens_mC_to_hw(s, cl_low);

	spin_lock_irqsave(&priv->ul_lock, flags);

	tsens_पढ़ो_irq_state(priv, hw_id, s, &d);

	/* Write the new thresholds and clear the status */
	regmap_field_ग_लिखो(priv->rf[LOW_THRESH_0 + hw_id], low_val);
	regmap_field_ग_लिखो(priv->rf[UP_THRESH_0 + hw_id], high_val);
	tsens_set_पूर्णांकerrupt(priv, hw_id, LOWER, true);
	tsens_set_पूर्णांकerrupt(priv, hw_id, UPPER, true);

	spin_unlock_irqrestore(&priv->ul_lock, flags);

	dev_dbg(dev, "[%u] %s: (%d:%d)->(%d:%d)\n",
		hw_id, __func__, d.low_thresh, d.up_thresh, cl_low, cl_high);

	वापस 0;
पूर्ण

अटल पूर्णांक tsens_enable_irq(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक ret;
	पूर्णांक val = tsens_version(priv) > VER_1_X ? 7 : 1;

	ret = regmap_field_ग_लिखो(priv->rf[INT_EN], val);
	अगर (ret < 0)
		dev_err(priv->dev, "%s: failed to enable interrupts\n",
			__func__);

	वापस ret;
पूर्ण

अटल व्योम tsens_disable_irq(काष्ठा tsens_priv *priv)
अणु
	regmap_field_ग_लिखो(priv->rf[INT_EN], 0);
पूर्ण

पूर्णांक get_temp_tsens_valid(स्थिर काष्ठा tsens_sensor *s, पूर्णांक *temp)
अणु
	काष्ठा tsens_priv *priv = s->priv;
	पूर्णांक hw_id = s->hw_id;
	u32 temp_idx = LAST_TEMP_0 + hw_id;
	u32 valid_idx = VALID_0 + hw_id;
	u32 valid;
	पूर्णांक ret;

	/* VER_0 करोesn't have VALID bit */
	अगर (tsens_version(priv) >= VER_0_1) अणु
		ret = regmap_field_पढ़ो(priv->rf[valid_idx], &valid);
		अगर (ret)
			वापस ret;
		जबतक (!valid) अणु
			/* Valid bit is 0 क्रम 6 AHB घड़ी cycles.
			 * At 19.2MHz, 1 AHB घड़ी is ~60ns.
			 * We should enter this loop very, very rarely.
			 */
			ndelay(400);
			ret = regmap_field_पढ़ो(priv->rf[valid_idx], &valid);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Valid bit is set, OK to पढ़ो the temperature */
	*temp = tsens_hw_to_mC(s, temp_idx);

	वापस 0;
पूर्ण

पूर्णांक get_temp_common(स्थिर काष्ठा tsens_sensor *s, पूर्णांक *temp)
अणु
	काष्ठा tsens_priv *priv = s->priv;
	पूर्णांक hw_id = s->hw_id;
	पूर्णांक last_temp = 0, ret, trdy;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + usecs_to_jअगरfies(TIMEOUT_US);
	करो अणु
		अगर (tsens_version(priv) == VER_0) अणु
			ret = regmap_field_पढ़ो(priv->rf[TRDY], &trdy);
			अगर (ret)
				वापस ret;
			अगर (!trdy)
				जारी;
		पूर्ण

		ret = regmap_field_पढ़ो(priv->rf[LAST_TEMP_0 + hw_id], &last_temp);
		अगर (ret)
			वापस ret;

		*temp = code_to_degc(last_temp, s) * 1000;

		वापस 0;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -ETIMEDOUT;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक dbg_sensors_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = s->निजी;
	काष्ठा tsens_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	seq_म_लिखो(s, "max: %2d\nnum: %2d\n\n",
		   priv->feat->max_sensors, priv->num_sensors);

	seq_माला_दो(s, "      id    slope   offset\n--------------------------\n");
	क्रम (i = 0;  i < priv->num_sensors; i++) अणु
		seq_म_लिखो(s, "%8d %8d %8d\n", priv->sensor[i].hw_id,
			   priv->sensor[i].slope, priv->sensor[i].offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dbg_version_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = s->निजी;
	काष्ठा tsens_priv *priv = platक्रमm_get_drvdata(pdev);
	u32 maj_ver, min_ver, step_ver;
	पूर्णांक ret;

	अगर (tsens_version(priv) > VER_0_1) अणु
		ret = regmap_field_पढ़ो(priv->rf[VER_MAJOR], &maj_ver);
		अगर (ret)
			वापस ret;
		ret = regmap_field_पढ़ो(priv->rf[VER_MINOR], &min_ver);
		अगर (ret)
			वापस ret;
		ret = regmap_field_पढ़ो(priv->rf[VER_STEP], &step_ver);
		अगर (ret)
			वापस ret;
		seq_म_लिखो(s, "%d.%d.%d\n", maj_ver, min_ver, step_ver);
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "0.1.0\n");
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dbg_version);
DEFINE_SHOW_ATTRIBUTE(dbg_sensors);

अटल व्योम tsens_debug_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tsens_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा dentry *root, *file;

	root = debugfs_lookup("tsens", शून्य);
	अगर (!root)
		priv->debug_root = debugfs_create_dir("tsens", शून्य);
	अन्यथा
		priv->debug_root = root;

	file = debugfs_lookup("version", priv->debug_root);
	अगर (!file)
		debugfs_create_file("version", 0444, priv->debug_root,
				    pdev, &dbg_version_fops);

	/* A directory क्रम each instance of the TSENS IP */
	priv->debug = debugfs_create_dir(dev_name(&pdev->dev), priv->debug_root);
	debugfs_create_file("sensors", 0444, priv->debug, pdev, &dbg_sensors_fops);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम tsens_debug_init(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा regmap_config tsens_config = अणु
	.name		= "tm",
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tsens_srot_config = अणु
	.name		= "srot",
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
पूर्ण;

पूर्णांक __init init_common(काष्ठा tsens_priv *priv)
अणु
	व्योम __iomem *पंचांग_base, *srot_base;
	काष्ठा device *dev = priv->dev;
	u32 ver_minor;
	काष्ठा resource *res;
	u32 enabled;
	पूर्णांक ret, i, j;
	काष्ठा platक्रमm_device *op = of_find_device_by_node(priv->dev->of_node);

	अगर (!op)
		वापस -EINVAL;

	अगर (op->num_resources > 1) अणु
		/* DT with separate SROT and TM address space */
		priv->पंचांग_offset = 0;
		res = platक्रमm_get_resource(op, IORESOURCE_MEM, 1);
		srot_base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(srot_base)) अणु
			ret = PTR_ERR(srot_base);
			जाओ err_put_device;
		पूर्ण

		priv->srot_map = devm_regmap_init_mmio(dev, srot_base,
						       &tsens_srot_config);
		अगर (IS_ERR(priv->srot_map)) अणु
			ret = PTR_ERR(priv->srot_map);
			जाओ err_put_device;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* old DTs where SROT and TM were in a contiguous 2K block */
		priv->पंचांग_offset = 0x1000;
	पूर्ण

	अगर (tsens_version(priv) >= VER_0_1) अणु
		res = platक्रमm_get_resource(op, IORESOURCE_MEM, 0);
		पंचांग_base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(पंचांग_base)) अणु
			ret = PTR_ERR(पंचांग_base);
			जाओ err_put_device;
		पूर्ण

		priv->पंचांग_map = devm_regmap_init_mmio(dev, पंचांग_base, &tsens_config);
	पूर्ण अन्यथा अणु /* VER_0 share the same gcc regs using a syscon */
		काष्ठा device *parent = priv->dev->parent;

		अगर (parent)
			priv->पंचांग_map = syscon_node_to_regmap(parent->of_node);
	पूर्ण

	अगर (IS_ERR_OR_शून्य(priv->पंचांग_map)) अणु
		अगर (!priv->पंचांग_map)
			ret = -ENODEV;
		अन्यथा
			ret = PTR_ERR(priv->पंचांग_map);
		जाओ err_put_device;
	पूर्ण

	/* VER_0 have only पंचांग_map */
	अगर (!priv->srot_map)
		priv->srot_map = priv->पंचांग_map;

	अगर (tsens_version(priv) > VER_0_1) अणु
		क्रम (i = VER_MAJOR; i <= VER_STEP; i++) अणु
			priv->rf[i] = devm_regmap_field_alloc(dev, priv->srot_map,
							      priv->fields[i]);
			अगर (IS_ERR(priv->rf[i])) अणु
				ret = PTR_ERR(priv->rf[i]);
				जाओ err_put_device;
			पूर्ण
		पूर्ण
		ret = regmap_field_पढ़ो(priv->rf[VER_MINOR], &ver_minor);
		अगर (ret)
			जाओ err_put_device;
	पूर्ण

	priv->rf[TSENS_EN] = devm_regmap_field_alloc(dev, priv->srot_map,
						     priv->fields[TSENS_EN]);
	अगर (IS_ERR(priv->rf[TSENS_EN])) अणु
		ret = PTR_ERR(priv->rf[TSENS_EN]);
		जाओ err_put_device;
	पूर्ण
	/* in VER_0 TSENS need to be explicitly enabled */
	अगर (tsens_version(priv) == VER_0)
		regmap_field_ग_लिखो(priv->rf[TSENS_EN], 1);

	ret = regmap_field_पढ़ो(priv->rf[TSENS_EN], &enabled);
	अगर (ret)
		जाओ err_put_device;
	अगर (!enabled) अणु
		dev_err(dev, "%s: device not enabled\n", __func__);
		ret = -ENODEV;
		जाओ err_put_device;
	पूर्ण

	priv->rf[SENSOR_EN] = devm_regmap_field_alloc(dev, priv->srot_map,
						      priv->fields[SENSOR_EN]);
	अगर (IS_ERR(priv->rf[SENSOR_EN])) अणु
		ret = PTR_ERR(priv->rf[SENSOR_EN]);
		जाओ err_put_device;
	पूर्ण
	priv->rf[INT_EN] = devm_regmap_field_alloc(dev, priv->पंचांग_map,
						   priv->fields[INT_EN]);
	अगर (IS_ERR(priv->rf[INT_EN])) अणु
		ret = PTR_ERR(priv->rf[INT_EN]);
		जाओ err_put_device;
	पूर्ण

	priv->rf[TSENS_SW_RST] =
		devm_regmap_field_alloc(dev, priv->srot_map, priv->fields[TSENS_SW_RST]);
	अगर (IS_ERR(priv->rf[TSENS_SW_RST])) अणु
		ret = PTR_ERR(priv->rf[TSENS_SW_RST]);
		जाओ err_put_device;
	पूर्ण

	priv->rf[TRDY] = devm_regmap_field_alloc(dev, priv->पंचांग_map, priv->fields[TRDY]);
	अगर (IS_ERR(priv->rf[TRDY])) अणु
		ret = PTR_ERR(priv->rf[TRDY]);
		जाओ err_put_device;
	पूर्ण

	/* This loop might need changes अगर क्रमागत regfield_ids is reordered */
	क्रम (j = LAST_TEMP_0; j <= UP_THRESH_15; j += 16) अणु
		क्रम (i = 0; i < priv->feat->max_sensors; i++) अणु
			पूर्णांक idx = j + i;

			priv->rf[idx] = devm_regmap_field_alloc(dev,
								priv->पंचांग_map,
								priv->fields[idx]);
			अगर (IS_ERR(priv->rf[idx])) अणु
				ret = PTR_ERR(priv->rf[idx]);
				जाओ err_put_device;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (priv->feat->crit_पूर्णांक || tsens_version(priv) < VER_0_1) अणु
		/* Loop might need changes अगर क्रमागत regfield_ids is reordered */
		क्रम (j = CRITICAL_STATUS_0; j <= CRIT_THRESH_15; j += 16) अणु
			क्रम (i = 0; i < priv->feat->max_sensors; i++) अणु
				पूर्णांक idx = j + i;

				priv->rf[idx] =
					devm_regmap_field_alloc(dev,
								priv->पंचांग_map,
								priv->fields[idx]);
				अगर (IS_ERR(priv->rf[idx])) अणु
					ret = PTR_ERR(priv->rf[idx]);
					जाओ err_put_device;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tsens_version(priv) > VER_1_X &&  ver_minor > 2) अणु
		/* Watchकरोg is present only on v2.3+ */
		priv->feat->has_watchकरोg = 1;
		क्रम (i = WDOG_BARK_STATUS; i <= CC_MON_MASK; i++) अणु
			priv->rf[i] = devm_regmap_field_alloc(dev, priv->पंचांग_map,
							      priv->fields[i]);
			अगर (IS_ERR(priv->rf[i])) अणु
				ret = PTR_ERR(priv->rf[i]);
				जाओ err_put_device;
			पूर्ण
		पूर्ण
		/*
		 * Watchकरोg is alपढ़ोy enabled, unmask the bark.
		 * Disable cycle completion monitoring
		 */
		regmap_field_ग_लिखो(priv->rf[WDOG_BARK_MASK], 0);
		regmap_field_ग_लिखो(priv->rf[CC_MON_MASK], 1);
	पूर्ण

	spin_lock_init(&priv->ul_lock);

	/* VER_0 पूर्णांकerrupt करोesn't need to be enabled */
	अगर (tsens_version(priv) >= VER_0_1)
		tsens_enable_irq(priv);

	tsens_debug_init(op);

err_put_device:
	put_device(&op->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tsens_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा tsens_sensor *s = data;
	काष्ठा tsens_priv *priv = s->priv;

	वापस priv->ops->get_temp(s, temp);
पूर्ण

अटल पूर्णांक tsens_get_trend(व्योम *data, पूर्णांक trip, क्रमागत thermal_trend *trend)
अणु
	काष्ठा tsens_sensor *s = data;
	काष्ठा tsens_priv *priv = s->priv;

	अगर (priv->ops->get_trend)
		वापस priv->ops->get_trend(s, trend);

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक  __maybe_unused tsens_suspend(काष्ठा device *dev)
अणु
	काष्ठा tsens_priv *priv = dev_get_drvdata(dev);

	अगर (priv->ops && priv->ops->suspend)
		वापस priv->ops->suspend(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tsens_resume(काष्ठा device *dev)
अणु
	काष्ठा tsens_priv *priv = dev_get_drvdata(dev);

	अगर (priv->ops && priv->ops->resume)
		वापस priv->ops->resume(priv);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tsens_pm_ops, tsens_suspend, tsens_resume);

अटल स्थिर काष्ठा of_device_id tsens_table[] = अणु
	अणु
		.compatible = "qcom,ipq8064-tsens",
		.data = &data_8960,
	पूर्ण, अणु
		.compatible = "qcom,mdm9607-tsens",
		.data = &data_9607,
	पूर्ण, अणु
		.compatible = "qcom,msm8916-tsens",
		.data = &data_8916,
	पूर्ण, अणु
		.compatible = "qcom,msm8939-tsens",
		.data = &data_8939,
	पूर्ण, अणु
		.compatible = "qcom,msm8974-tsens",
		.data = &data_8974,
	पूर्ण, अणु
		.compatible = "qcom,msm8976-tsens",
		.data = &data_8976,
	पूर्ण, अणु
		.compatible = "qcom,msm8996-tsens",
		.data = &data_8996,
	पूर्ण, अणु
		.compatible = "qcom,tsens-v1",
		.data = &data_tsens_v1,
	पूर्ण, अणु
		.compatible = "qcom,tsens-v2",
		.data = &data_tsens_v2,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tsens_table);

अटल स्थिर काष्ठा thermal_zone_of_device_ops tsens_of_ops = अणु
	.get_temp = tsens_get_temp,
	.get_trend = tsens_get_trend,
	.set_trips = tsens_set_trips,
पूर्ण;

अटल पूर्णांक tsens_रेजिस्टर_irq(काष्ठा tsens_priv *priv, अक्षर *irqname,
			      irq_handler_t thपढ़ो_fn)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret, irq;

	pdev = of_find_device_by_node(priv->dev->of_node);
	अगर (!pdev)
		वापस -ENODEV;

	irq = platक्रमm_get_irq_byname(pdev, irqname);
	अगर (irq < 0) अणु
		ret = irq;
		/* For old DTs with no IRQ defined */
		अगर (irq == -ENXIO)
			ret = 0;
	पूर्ण अन्यथा अणु
		/* VER_0 पूर्णांकerrupt is TRIGGER_RISING, VER_0_1 and up is ONESHOT */
		अगर (tsens_version(priv) == VER_0)
			ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
							thपढ़ो_fn, शून्य,
							IRQF_TRIGGER_RISING,
							dev_name(&pdev->dev),
							priv);
		अन्यथा
			ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
							thपढ़ो_fn, IRQF_ONESHOT,
							dev_name(&pdev->dev),
							priv);

		अगर (ret)
			dev_err(&pdev->dev, "%s: failed to get irq\n",
				__func__);
		अन्यथा
			enable_irq_wake(irq);
	पूर्ण

	put_device(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tsens_रेजिस्टर(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक i, ret;
	काष्ठा thermal_zone_device *tzd;

	क्रम (i = 0;  i < priv->num_sensors; i++) अणु
		priv->sensor[i].priv = priv;
		tzd = devm_thermal_zone_of_sensor_रेजिस्टर(priv->dev, priv->sensor[i].hw_id,
							   &priv->sensor[i],
							   &tsens_of_ops);
		अगर (IS_ERR(tzd))
			जारी;
		priv->sensor[i].tzd = tzd;
		अगर (priv->ops->enable)
			priv->ops->enable(priv, i);
	पूर्ण

	/* VER_0 require to set MIN and MAX THRESH
	 * These 2 regs are set using the:
	 * - CRIT_THRESH_0 क्रम MAX THRESH hardcoded to 120तओC
	 * - CRIT_THRESH_1 क्रम MIN THRESH hardcoded to   0तओC
	 */
	अगर (tsens_version(priv) < VER_0_1) अणु
		regmap_field_ग_लिखो(priv->rf[CRIT_THRESH_0],
				   tsens_mC_to_hw(priv->sensor, 120000));

		regmap_field_ग_लिखो(priv->rf[CRIT_THRESH_1],
				   tsens_mC_to_hw(priv->sensor, 0));
	पूर्ण

	ret = tsens_रेजिस्टर_irq(priv, "uplow", tsens_irq_thपढ़ो);
	अगर (ret < 0)
		वापस ret;

	अगर (priv->feat->crit_पूर्णांक)
		ret = tsens_रेजिस्टर_irq(priv, "critical",
					 tsens_critical_irq_thपढ़ो);

	वापस ret;
पूर्ण

अटल पूर्णांक tsens_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, i;
	काष्ठा device *dev;
	काष्ठा device_node *np;
	काष्ठा tsens_priv *priv;
	स्थिर काष्ठा tsens_plat_data *data;
	स्थिर काष्ठा of_device_id *id;
	u32 num_sensors;

	अगर (pdev->dev.of_node)
		dev = &pdev->dev;
	अन्यथा
		dev = pdev->dev.parent;

	np = dev->of_node;

	id = of_match_node(tsens_table, np);
	अगर (id)
		data = id->data;
	अन्यथा
		data = &data_8960;

	num_sensors = data->num_sensors;

	अगर (np)
		of_property_पढ़ो_u32(np, "#qcom,sensors", &num_sensors);

	अगर (num_sensors <= 0) अणु
		dev_err(dev, "%s: invalid number of sensors\n", __func__);
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(dev,
			     काष्ठा_size(priv, sensor, num_sensors),
			     GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->num_sensors = num_sensors;
	priv->ops = data->ops;
	क्रम (i = 0;  i < priv->num_sensors; i++) अणु
		अगर (data->hw_ids)
			priv->sensor[i].hw_id = data->hw_ids[i];
		अन्यथा
			priv->sensor[i].hw_id = i;
	पूर्ण
	priv->feat = data->feat;
	priv->fields = data->fields;

	platक्रमm_set_drvdata(pdev, priv);

	अगर (!priv->ops || !priv->ops->init || !priv->ops->get_temp)
		वापस -EINVAL;

	ret = priv->ops->init(priv);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: init failed\n", __func__);
		वापस ret;
	पूर्ण

	अगर (priv->ops->calibrate) अणु
		ret = priv->ops->calibrate(priv);
		अगर (ret < 0) अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "%s: calibration failed\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस tsens_रेजिस्टर(priv);
पूर्ण

अटल पूर्णांक tsens_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tsens_priv *priv = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(priv->debug_root);
	tsens_disable_irq(priv);
	अगर (priv->ops->disable)
		priv->ops->disable(priv);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tsens_driver = अणु
	.probe = tsens_probe,
	.हटाओ = tsens_हटाओ,
	.driver = अणु
		.name = "qcom-tsens",
		.pm	= &tsens_pm_ops,
		.of_match_table = tsens_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tsens_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("QCOM Temperature Sensor driver");
MODULE_ALIAS("platform:qcom-tsens");
