<शैली गुरु>
/*
 * Battery driver क्रम CPCAP PMIC
 *
 * Copyright (C) 2017 Tony Lindgren <tony@atomide.com>
 *
 * Some parts of the code based on earlier Motorola mapphone Linux kernel
 * drivers:
 *
 * Copyright (C) 2009-2010 Motorola, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.

 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/mfd/motorola-cpcap.h>

/*
 * Register bit defines क्रम CPCAP_REG_BPEOL. Some of these seem to
 * map to MC13783UG.pdf "Table 5-19. Register 13, Power Control 0"
 * to enable BATTDETEN, LOBAT and EOL features. We currently use
 * LOBAT पूर्णांकerrupts instead of EOL.
 */
#घोषणा CPCAP_REG_BPEOL_BIT_EOL9	BIT(9)	/* Set क्रम EOL irq */
#घोषणा CPCAP_REG_BPEOL_BIT_EOL8	BIT(8)	/* Set क्रम EOL irq */
#घोषणा CPCAP_REG_BPEOL_BIT_UNKNOWN7	BIT(7)
#घोषणा CPCAP_REG_BPEOL_BIT_UNKNOWN6	BIT(6)
#घोषणा CPCAP_REG_BPEOL_BIT_UNKNOWN5	BIT(5)
#घोषणा CPCAP_REG_BPEOL_BIT_EOL_MULTI	BIT(4)	/* Set क्रम multiple EOL irqs */
#घोषणा CPCAP_REG_BPEOL_BIT_UNKNOWN3	BIT(3)
#घोषणा CPCAP_REG_BPEOL_BIT_UNKNOWN2	BIT(2)
#घोषणा CPCAP_REG_BPEOL_BIT_BATTDETEN	BIT(1)	/* Enable battery detect */
#घोषणा CPCAP_REG_BPEOL_BIT_EOLSEL	BIT(0)	/* BPDET = 0, EOL = 1 */

/*
 * Register bit defines क्रम CPCAP_REG_CCC1. These seem similar to the twl6030
 * coulomb counter रेजिस्टरs rather than the mc13892 रेजिस्टरs. Both twl6030
 * and mc13892 set bits 2 and 1 to reset and clear रेजिस्टरs. But mc13892
 * sets bit 0 to start the coulomb counter जबतक twl6030 sets bit 0 to stop
 * the coulomb counter like cpcap करोes. So क्रम now, we use the twl6030 style
 * naming क्रम the रेजिस्टरs.
 */
#घोषणा CPCAP_REG_CCC1_ACTIVE_MODE1	BIT(4)	/* Update rate */
#घोषणा CPCAP_REG_CCC1_ACTIVE_MODE0	BIT(3)	/* Update rate */
#घोषणा CPCAP_REG_CCC1_AUTOCLEAR	BIT(2)	/* Resets sample रेजिस्टरs */
#घोषणा CPCAP_REG_CCC1_CAL_EN		BIT(1)	/* Clears after ग_लिखो in 1s */
#घोषणा CPCAP_REG_CCC1_PAUSE		BIT(0)	/* Stop counters, allow ग_लिखो */
#घोषणा CPCAP_REG_CCC1_RESET_MASK	(CPCAP_REG_CCC1_AUTOCLEAR | \
					 CPCAP_REG_CCC1_CAL_EN)

#घोषणा CPCAP_REG_CCCC2_RATE1		BIT(5)
#घोषणा CPCAP_REG_CCCC2_RATE0		BIT(4)
#घोषणा CPCAP_REG_CCCC2_ENABLE		BIT(3)

#घोषणा CPCAP_BATTERY_CC_SAMPLE_PERIOD_MS	250

क्रमागत अणु
	CPCAP_BATTERY_IIO_BATTDET,
	CPCAP_BATTERY_IIO_VOLTAGE,
	CPCAP_BATTERY_IIO_CHRG_CURRENT,
	CPCAP_BATTERY_IIO_BATT_CURRENT,
	CPCAP_BATTERY_IIO_NR,
पूर्ण;

क्रमागत cpcap_battery_irq_action अणु
	CPCAP_BATTERY_IRQ_ACTION_NONE,
	CPCAP_BATTERY_IRQ_ACTION_CC_CAL_DONE,
	CPCAP_BATTERY_IRQ_ACTION_BATTERY_LOW,
	CPCAP_BATTERY_IRQ_ACTION_POWEROFF,
पूर्ण;

काष्ठा cpcap_पूर्णांकerrupt_desc अणु
	स्थिर अक्षर *name;
	काष्ठा list_head node;
	पूर्णांक irq;
	क्रमागत cpcap_battery_irq_action action;
पूर्ण;

काष्ठा cpcap_battery_config अणु
	पूर्णांक cd_factor;
	काष्ठा घातer_supply_info info;
	काष्ठा घातer_supply_battery_info bat;
पूर्ण;

काष्ठा cpcap_coulomb_counter_data अणु
	s32 sample;		/* 24 or 32 bits */
	s32 accumulator;
	s16 offset;		/* 9 bits */
	s16 पूर्णांकegrator;		/* 13 or 16 bits */
पूर्ण;

क्रमागत cpcap_battery_state अणु
	CPCAP_BATTERY_STATE_PREVIOUS,
	CPCAP_BATTERY_STATE_LATEST,
	CPCAP_BATTERY_STATE_EMPTY,
	CPCAP_BATTERY_STATE_FULL,
	CPCAP_BATTERY_STATE_NR,
पूर्ण;

काष्ठा cpcap_battery_state_data अणु
	पूर्णांक voltage;
	पूर्णांक current_ua;
	पूर्णांक counter_uah;
	पूर्णांक temperature;
	kसमय_प्रकार समय;
	काष्ठा cpcap_coulomb_counter_data cc;
पूर्ण;

काष्ठा cpcap_battery_ddata अणु
	काष्ठा device *dev;
	काष्ठा regmap *reg;
	काष्ठा list_head irq_list;
	काष्ठा iio_channel *channels[CPCAP_BATTERY_IIO_NR];
	काष्ठा घातer_supply *psy;
	काष्ठा cpcap_battery_config config;
	काष्ठा cpcap_battery_state_data state[CPCAP_BATTERY_STATE_NR];
	u32 cc_lsb;		/* NञAms per LSB */
	atomic_t active;
	पूर्णांक अक्षरge_full;
	पूर्णांक status;
	u16 venकरोr;
	अचिन्हित पूर्णांक is_full:1;
पूर्ण;

#घोषणा CPCAP_NO_BATTERY	-400

अटल bool ignore_temperature_probe;
module_param(ignore_temperature_probe, bool, 0660);

अटल काष्ठा cpcap_battery_state_data *
cpcap_battery_get_state(काष्ठा cpcap_battery_ddata *ddata,
			क्रमागत cpcap_battery_state state)
अणु
	अगर (state >= CPCAP_BATTERY_STATE_NR)
		वापस शून्य;

	वापस &ddata->state[state];
पूर्ण

अटल काष्ठा cpcap_battery_state_data *
cpcap_battery_latest(काष्ठा cpcap_battery_ddata *ddata)
अणु
	वापस cpcap_battery_get_state(ddata, CPCAP_BATTERY_STATE_LATEST);
पूर्ण

अटल काष्ठा cpcap_battery_state_data *
cpcap_battery_previous(काष्ठा cpcap_battery_ddata *ddata)
अणु
	वापस cpcap_battery_get_state(ddata, CPCAP_BATTERY_STATE_PREVIOUS);
पूर्ण

अटल काष्ठा cpcap_battery_state_data *
cpcap_battery_get_empty(काष्ठा cpcap_battery_ddata *ddata)
अणु
	वापस cpcap_battery_get_state(ddata, CPCAP_BATTERY_STATE_EMPTY);
पूर्ण

अटल काष्ठा cpcap_battery_state_data *
cpcap_battery_get_full(काष्ठा cpcap_battery_ddata *ddata)
अणु
	वापस cpcap_battery_get_state(ddata, CPCAP_BATTERY_STATE_FULL);
पूर्ण

अटल पूर्णांक cpcap_अक्षरger_battery_temperature(काष्ठा cpcap_battery_ddata *ddata,
					     पूर्णांक *value)
अणु
	काष्ठा iio_channel *channel;
	पूर्णांक error;

	channel = ddata->channels[CPCAP_BATTERY_IIO_BATTDET];
	error = iio_पढ़ो_channel_processed(channel, value);
	अगर (error < 0) अणु
		अगर (!ignore_temperature_probe)
			dev_warn(ddata->dev, "%s failed: %i\n", __func__, error);
		*value = CPCAP_NO_BATTERY;

		वापस error;
	पूर्ण

	*value /= 100;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_battery_get_voltage(काष्ठा cpcap_battery_ddata *ddata)
अणु
	काष्ठा iio_channel *channel;
	पूर्णांक error, value = 0;

	channel = ddata->channels[CPCAP_BATTERY_IIO_VOLTAGE];
	error = iio_पढ़ो_channel_processed(channel, &value);
	अगर (error < 0) अणु
		dev_warn(ddata->dev, "%s failed: %i\n", __func__, error);

		वापस 0;
	पूर्ण

	वापस value * 1000;
पूर्ण

अटल पूर्णांक cpcap_battery_get_current(काष्ठा cpcap_battery_ddata *ddata)
अणु
	काष्ठा iio_channel *channel;
	पूर्णांक error, value = 0;

	channel = ddata->channels[CPCAP_BATTERY_IIO_BATT_CURRENT];
	error = iio_पढ़ो_channel_processed(channel, &value);
	अगर (error < 0) अणु
		dev_warn(ddata->dev, "%s failed: %i\n", __func__, error);

		वापस 0;
	पूर्ण

	वापस value * 1000;
पूर्ण

/**
 * cpcap_battery_cc_raw_भाग - calculate and भागide coulomb counter NञAms values
 * @ddata: device driver data
 * @sample: coulomb counter sample value
 * @accumulator: coulomb counter पूर्णांकegrator value
 * @offset: coulomb counter offset value
 * @भागider: conversion भागider
 *
 * Note that cc_lsb and cc_dur values are from Motorola Linux kernel
 * function data_get_avg_curr_ua() and seem to be based on measured test
 * results. It also has the following comment:
 *
 * Adjusपंचांगent factors are applied here as a temp solution per the test
 * results. Need to work out a क्रमmal solution क्रम this adjusपंचांगent.
 *
 * A coulomb counter क्रम similar hardware seems to be करोcumented in
 * "TWL6030 Gas Gauging Basics (Rev. A)" swca095a.pdf in chapter
 * "10 Calculating Accumulated Current". We however follow what the
 * Motorola mapphone Linux kernel is करोing as there may be either a
 * TI or ST coulomb counter in the PMIC.
 */
अटल पूर्णांक cpcap_battery_cc_raw_भाग(काष्ठा cpcap_battery_ddata *ddata,
				    s32 sample, s32 accumulator,
				    s16 offset, u32 भागider)
अणु
	s64 acc;

	अगर (!भागider)
		वापस 0;

	acc = accumulator;
	acc -= (s64)sample * offset;
	acc *= ddata->cc_lsb;
	acc *= -1;
	acc = भाग_s64(acc, भागider);

	वापस acc;
पूर्ण

/* 3600000NञAms = 1NञAh */
अटल पूर्णांक cpcap_battery_cc_to_uah(काष्ठा cpcap_battery_ddata *ddata,
				   s32 sample, s32 accumulator,
				   s16 offset)
अणु
	वापस cpcap_battery_cc_raw_भाग(ddata, sample,
					accumulator, offset,
					3600000);
पूर्ण

अटल पूर्णांक cpcap_battery_cc_to_ua(काष्ठा cpcap_battery_ddata *ddata,
				  s32 sample, s32 accumulator,
				  s16 offset)
अणु
	वापस cpcap_battery_cc_raw_भाग(ddata, sample,
					accumulator, offset,
					sample *
					CPCAP_BATTERY_CC_SAMPLE_PERIOD_MS);
पूर्ण

/**
 * cpcap_battery_पढ़ो_accumulated - पढ़ोs cpcap coulomb counter
 * @ddata: device driver data
 * @ccd: coulomb counter values
 *
 * Based on Motorola mapphone kernel function data_पढ़ो_regs().
 * Looking at the रेजिस्टरs, the coulomb counter seems similar to
 * the coulomb counter in TWL6030. See "TWL6030 Gas Gauging Basics
 * (Rev. A) swca095a.pdf क्रम "10 Calculating Accumulated Current".
 *
 * Note that swca095a.pdf inकाष्ठाs to stop the coulomb counter
 * beक्रमe पढ़ोing to aव्योम values changing. Motorola mapphone
 * Linux kernel करोes not करो it, so let's assume they've verअगरied
 * the data produced is correct.
 */
अटल पूर्णांक
cpcap_battery_पढ़ो_accumulated(काष्ठा cpcap_battery_ddata *ddata,
			       काष्ठा cpcap_coulomb_counter_data *ccd)
अणु
	u16 buf[7];	/* CPCAP_REG_CCS1 to CCI */
	पूर्णांक error;

	ccd->sample = 0;
	ccd->accumulator = 0;
	ccd->offset = 0;
	ccd->पूर्णांकegrator = 0;

	/* Read coulomb counter रेजिस्टर range */
	error = regmap_bulk_पढ़ो(ddata->reg, CPCAP_REG_CCS1,
				 buf, ARRAY_SIZE(buf));
	अगर (error)
		वापस 0;

	/* Sample value CPCAP_REG_CCS1 & 2 */
	ccd->sample = (buf[1] & 0x0fff) << 16;
	ccd->sample |= buf[0];
	अगर (ddata->venकरोr == CPCAP_VENDOR_TI)
		ccd->sample = sign_extend32(24, ccd->sample);

	/* Accumulator value CPCAP_REG_CCA1 & 2 */
	ccd->accumulator = ((s16)buf[3]) << 16;
	ccd->accumulator |= buf[2];

	/*
	 * Coulomb counter calibration offset is CPCAP_REG_CCM,
	 * REG_CCO seems unused
	 */
	ccd->offset = buf[4];
	ccd->offset = sign_extend32(ccd->offset, 9);

	/* Integrator रेजिस्टर CPCAP_REG_CCI */
	अगर (ddata->venकरोr == CPCAP_VENDOR_TI)
		ccd->पूर्णांकegrator = sign_extend32(buf[6], 13);
	अन्यथा
		ccd->पूर्णांकegrator = (s16)buf[6];

	वापस cpcap_battery_cc_to_uah(ddata,
				       ccd->sample,
				       ccd->accumulator,
				       ccd->offset);
पूर्ण

/**
 * cpcap_battery_cc_get_avg_current - पढ़ो cpcap coulumb counter
 * @ddata: cpcap battery driver device data
 */
अटल पूर्णांक cpcap_battery_cc_get_avg_current(काष्ठा cpcap_battery_ddata *ddata)
अणु
	पूर्णांक value, acc, error;
	s32 sample;
	s16 offset;

	/* Coulomb counter पूर्णांकegrator */
	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_CCI, &value);
	अगर (error)
		वापस error;

	अगर (ddata->venकरोr == CPCAP_VENDOR_TI) अणु
		acc = sign_extend32(value, 13);
		sample = 1;
	पूर्ण अन्यथा अणु
		acc = (s16)value;
		sample = 4;
	पूर्ण

	/* Coulomb counter calibration offset  */
	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_CCM, &value);
	अगर (error)
		वापस error;

	offset = sign_extend32(value, 9);

	वापस cpcap_battery_cc_to_ua(ddata, sample, acc, offset);
पूर्ण

अटल पूर्णांक cpcap_battery_get_अक्षरger_status(काष्ठा cpcap_battery_ddata *ddata,
					    पूर्णांक *val)
अणु
	जोड़ घातer_supply_propval prop;
	काष्ठा घातer_supply *अक्षरger;
	पूर्णांक error;

	अक्षरger = घातer_supply_get_by_name("usb");
	अगर (!अक्षरger)
		वापस -ENODEV;

	error = घातer_supply_get_property(अक्षरger, POWER_SUPPLY_PROP_STATUS,
					  &prop);
	अगर (error)
		*val = POWER_SUPPLY_STATUS_UNKNOWN;
	अन्यथा
		*val = prop.पूर्णांकval;

	घातer_supply_put(अक्षरger);

	वापस error;
पूर्ण

अटल bool cpcap_battery_full(काष्ठा cpcap_battery_ddata *ddata)
अणु
	काष्ठा cpcap_battery_state_data *state = cpcap_battery_latest(ddata);
	अचिन्हित पूर्णांक vfull;
	पूर्णांक error, val;

	error = cpcap_battery_get_अक्षरger_status(ddata, &val);
	अगर (!error) अणु
		चयन (val) अणु
		हाल POWER_SUPPLY_STATUS_DISCHARGING:
			dev_dbg(ddata->dev, "charger disconnected\n");
			ddata->is_full = 0;
			अवरोध;
		हाल POWER_SUPPLY_STATUS_FULL:
			dev_dbg(ddata->dev, "charger full status\n");
			ddata->is_full = 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * The full battery voltage here can be inaccurate, it's used just to
	 * filter out any trickle अक्षरging events. We clear the is_full status
	 * on अक्षरger disconnect above anyways.
	 */
	vfull = ddata->config.bat.स्थिरant_अक्षरge_voltage_max_uv - 120000;

	अगर (ddata->is_full && state->voltage < vfull)
		ddata->is_full = 0;

	वापस ddata->is_full;
पूर्ण

अटल bool cpcap_battery_low(काष्ठा cpcap_battery_ddata *ddata)
अणु
	काष्ठा cpcap_battery_state_data *state = cpcap_battery_latest(ddata);
	अटल bool is_low;

	अगर (state->current_ua > 0 && (state->voltage <= 3350000 || is_low))
		is_low = true;
	अन्यथा
		is_low = false;

	वापस is_low;
पूर्ण

अटल पूर्णांक cpcap_battery_update_status(काष्ठा cpcap_battery_ddata *ddata)
अणु
	काष्ठा cpcap_battery_state_data state, *latest, *previous,
					*empty, *full;
	kसमय_प्रकार now;
	पूर्णांक error;

	स_रखो(&state, 0, माप(state));
	now = kसमय_get();

	latest = cpcap_battery_latest(ddata);
	अगर (latest) अणु
		s64 delta_ms = kसमय_प्रकारo_ms(kसमय_sub(now, latest->समय));

		अगर (delta_ms < CPCAP_BATTERY_CC_SAMPLE_PERIOD_MS)
			वापस delta_ms;
	पूर्ण

	state.समय = now;
	state.voltage = cpcap_battery_get_voltage(ddata);
	state.current_ua = cpcap_battery_get_current(ddata);
	state.counter_uah = cpcap_battery_पढ़ो_accumulated(ddata, &state.cc);

	error = cpcap_अक्षरger_battery_temperature(ddata,
						  &state.temperature);
	अगर (error)
		वापस error;

	previous = cpcap_battery_previous(ddata);
	स_नकल(previous, latest, माप(*previous));
	स_नकल(latest, &state, माप(*latest));

	अगर (cpcap_battery_full(ddata)) अणु
		full = cpcap_battery_get_full(ddata);
		स_नकल(full, latest, माप(*full));

		empty = cpcap_battery_get_empty(ddata);
		अगर (empty->voltage && empty->voltage != -1) अणु
			empty->voltage = -1;
			ddata->अक्षरge_full =
				empty->counter_uah - full->counter_uah;
		पूर्ण अन्यथा अगर (ddata->अक्षरge_full) अणु
			empty->voltage = -1;
			empty->counter_uah =
				full->counter_uah + ddata->अक्षरge_full;
		पूर्ण
	पूर्ण अन्यथा अगर (cpcap_battery_low(ddata)) अणु
		empty = cpcap_battery_get_empty(ddata);
		स_नकल(empty, latest, माप(*empty));

		full = cpcap_battery_get_full(ddata);
		अगर (full->voltage) अणु
			full->voltage = 0;
			ddata->अक्षरge_full =
				empty->counter_uah - full->counter_uah;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Update battery status when cpcap-अक्षरger calls घातer_supply_changed().
 * This allows us to detect battery full condition beक्रमe the अक्षरger
 * disconnects.
 */
अटल व्योम cpcap_battery_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	जोड़ घातer_supply_propval prop;

	घातer_supply_get_property(psy, POWER_SUPPLY_PROP_STATUS, &prop);
पूर्ण

अटल क्रमागत घातer_supply_property cpcap_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_POWER_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल पूर्णांक cpcap_battery_get_property(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp,
				      जोड़ घातer_supply_propval *val)
अणु
	काष्ठा cpcap_battery_ddata *ddata = घातer_supply_get_drvdata(psy);
	काष्ठा cpcap_battery_state_data *latest, *previous, *empty;
	u32 sample;
	s32 accumulator;
	पूर्णांक cached;
	s64 पंचांगp;

	cached = cpcap_battery_update_status(ddata);
	अगर (cached < 0)
		वापस cached;

	latest = cpcap_battery_latest(ddata);
	previous = cpcap_battery_previous(ddata);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		अगर (latest->temperature > CPCAP_NO_BATTERY || ignore_temperature_probe)
			val->पूर्णांकval = 1;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (cpcap_battery_full(ddata)) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
			अवरोध;
		पूर्ण
		अगर (cpcap_battery_cc_get_avg_current(ddata) < 0)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = ddata->config.info.technology;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = cpcap_battery_get_voltage(ddata);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = ddata->config.info.voltage_max_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = ddata->config.info.voltage_min_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		val->पूर्णांकval = ddata->config.bat.स्थिरant_अक्षरge_voltage_max_uv;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		sample = latest->cc.sample - previous->cc.sample;
		अगर (!sample) अणु
			val->पूर्णांकval = cpcap_battery_cc_get_avg_current(ddata);
			अवरोध;
		पूर्ण
		accumulator = latest->cc.accumulator - previous->cc.accumulator;
		val->पूर्णांकval = cpcap_battery_cc_to_ua(ddata, sample,
						     accumulator,
						     latest->cc.offset);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = latest->current_ua;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
		val->पूर्णांकval = latest->counter_uah;
		अवरोध;
	हाल POWER_SUPPLY_PROP_POWER_NOW:
		पंचांगp = (latest->voltage / 10000) * latest->current_ua;
		val->पूर्णांकval = भाग64_s64(पंचांगp, 100);
		अवरोध;
	हाल POWER_SUPPLY_PROP_POWER_AVG:
		sample = latest->cc.sample - previous->cc.sample;
		अगर (!sample) अणु
			पंचांगp = cpcap_battery_cc_get_avg_current(ddata);
			पंचांगp *= (latest->voltage / 10000);
			val->पूर्णांकval = भाग64_s64(पंचांगp, 100);
			अवरोध;
		पूर्ण
		accumulator = latest->cc.accumulator - previous->cc.accumulator;
		पंचांगp = cpcap_battery_cc_to_ua(ddata, sample, accumulator,
					     latest->cc.offset);
		पंचांगp *= ((latest->voltage + previous->voltage) / 20000);
		val->पूर्णांकval = भाग64_s64(पंचांगp, 100);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		empty = cpcap_battery_get_empty(ddata);
		अगर (!empty->voltage || !ddata->अक्षरge_full)
			वापस -ENODATA;
		/* (ddata->अक्षरge_full / 200) is needed क्रम rounding */
		val->पूर्णांकval = empty->counter_uah - latest->counter_uah +
			ddata->अक्षरge_full / 200;
		val->पूर्णांकval = clamp(val->पूर्णांकval, 0, ddata->अक्षरge_full);
		val->पूर्णांकval = val->पूर्णांकval * 100 / ddata->अक्षरge_full;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		अगर (cpcap_battery_full(ddata))
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		अन्यथा अगर (latest->voltage >= 3750000)
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_HIGH;
		अन्यथा अगर (latest->voltage >= 3300000)
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		अन्यथा अगर (latest->voltage > 3100000)
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अन्यथा अगर (latest->voltage <= 3100000)
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		empty = cpcap_battery_get_empty(ddata);
		अगर (!empty->voltage)
			वापस -ENODATA;
		val->पूर्णांकval = empty->counter_uah - latest->counter_uah;
		अगर (val->पूर्णांकval < 0)
			val->पूर्णांकval = 0;
		अन्यथा अगर (ddata->अक्षरge_full && ddata->अक्षरge_full < val->पूर्णांकval)
			val->पूर्णांकval = ddata->अक्षरge_full;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		अगर (!ddata->अक्षरge_full)
			वापस -ENODATA;
		val->पूर्णांकval = ddata->अक्षरge_full;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval = ddata->config.info.अक्षरge_full_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_SYSTEM;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		अगर (ignore_temperature_probe)
			वापस -ENODATA;
		val->पूर्णांकval = latest->temperature;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_battery_update_अक्षरger(काष्ठा cpcap_battery_ddata *ddata,
					पूर्णांक स्थिर_अक्षरge_voltage)
अणु
	जोड़ घातer_supply_propval prop;
	जोड़ घातer_supply_propval val;
	काष्ठा घातer_supply *अक्षरger;
	पूर्णांक error;

	अक्षरger = घातer_supply_get_by_name("usb");
	अगर (!अक्षरger)
		वापस -ENODEV;

	error = घातer_supply_get_property(अक्षरger,
				POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
				&prop);
	अगर (error)
		जाओ out_put;

	/* Allow अक्षरger स्थिर voltage lower than battery स्थिर voltage */
	अगर (स्थिर_अक्षरge_voltage > prop.पूर्णांकval)
		जाओ out_put;

	val.पूर्णांकval = स्थिर_अक्षरge_voltage;

	error = घातer_supply_set_property(अक्षरger,
			POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
			&val);
out_put:
	घातer_supply_put(अक्षरger);

	वापस error;
पूर्ण

अटल पूर्णांक cpcap_battery_set_property(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp,
				      स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा cpcap_battery_ddata *ddata = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		अगर (val->पूर्णांकval < ddata->config.info.voltage_min_design)
			वापस -EINVAL;
		अगर (val->पूर्णांकval > ddata->config.info.voltage_max_design)
			वापस -EINVAL;

		ddata->config.bat.स्थिरant_अक्षरge_voltage_max_uv = val->पूर्णांकval;

		वापस cpcap_battery_update_अक्षरger(ddata, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		अगर (val->पूर्णांकval < 0)
			वापस -EINVAL;
		अगर (val->पूर्णांकval > ddata->config.info.अक्षरge_full_design)
			वापस -EINVAL;

		ddata->अक्षरge_full = val->पूर्णांकval;

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_battery_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					       क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल irqवापस_t cpcap_battery_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cpcap_battery_ddata *ddata = data;
	काष्ठा cpcap_battery_state_data *latest;
	काष्ठा cpcap_पूर्णांकerrupt_desc *d;

	अगर (!atomic_पढ़ो(&ddata->active))
		वापस IRQ_NONE;

	list_क्रम_each_entry(d, &ddata->irq_list, node) अणु
		अगर (irq == d->irq)
			अवरोध;
	पूर्ण

	अगर (list_entry_is_head(d, &ddata->irq_list, node))
		वापस IRQ_NONE;

	latest = cpcap_battery_latest(ddata);

	चयन (d->action) अणु
	हाल CPCAP_BATTERY_IRQ_ACTION_CC_CAL_DONE:
		dev_info(ddata->dev, "Coulomb counter calibration done\n");
		अवरोध;
	हाल CPCAP_BATTERY_IRQ_ACTION_BATTERY_LOW:
		अगर (latest->current_ua >= 0)
			dev_warn(ddata->dev, "Battery low at %imV!\n",
				latest->voltage / 1000);
		अवरोध;
	हाल CPCAP_BATTERY_IRQ_ACTION_POWEROFF:
		अगर (latest->current_ua >= 0 && latest->voltage <= 3200000) अणु
			dev_emerg(ddata->dev,
				  "Battery empty at %imV, powering off\n",
				  latest->voltage / 1000);
			orderly_घातeroff(true);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	घातer_supply_changed(ddata->psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cpcap_battery_init_irq(काष्ठा platक्रमm_device *pdev,
				  काष्ठा cpcap_battery_ddata *ddata,
				  स्थिर अक्षर *name)
अणु
	काष्ठा cpcap_पूर्णांकerrupt_desc *d;
	पूर्णांक irq, error;

	irq = platक्रमm_get_irq_byname(pdev, name);
	अगर (irq < 0)
		वापस irq;

	error = devm_request_thपढ़ोed_irq(ddata->dev, irq, शून्य,
					  cpcap_battery_irq_thपढ़ो,
					  IRQF_SHARED | IRQF_ONESHOT,
					  name, ddata);
	अगर (error) अणु
		dev_err(ddata->dev, "could not get irq %s: %i\n",
			name, error);

		वापस error;
	पूर्ण

	d = devm_kzalloc(ddata->dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	d->name = name;
	d->irq = irq;

	अगर (!म_भेदन(name, "cccal", 5))
		d->action = CPCAP_BATTERY_IRQ_ACTION_CC_CAL_DONE;
	अन्यथा अगर (!म_भेदन(name, "lowbph", 6))
		d->action = CPCAP_BATTERY_IRQ_ACTION_BATTERY_LOW;
	अन्यथा अगर (!म_भेदन(name, "lowbpl", 6))
		d->action = CPCAP_BATTERY_IRQ_ACTION_POWEROFF;

	list_add(&d->node, &ddata->irq_list);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_battery_init_पूर्णांकerrupts(काष्ठा platक्रमm_device *pdev,
					 काष्ठा cpcap_battery_ddata *ddata)
अणु
	अटल स्थिर अक्षर * स्थिर cpcap_battery_irqs[] = अणु
		"eol", "lowbph", "lowbpl",
		"chrgcurr1", "battdetb"
	पूर्ण;
	पूर्णांक i, error;

	क्रम (i = 0; i < ARRAY_SIZE(cpcap_battery_irqs); i++) अणु
		error = cpcap_battery_init_irq(pdev, ddata,
					       cpcap_battery_irqs[i]);
		अगर (error)
			वापस error;
	पूर्ण

	/* Enable calibration पूर्णांकerrupt अगर alपढ़ोy available in dts */
	cpcap_battery_init_irq(pdev, ddata, "cccal");

	/* Enable low battery पूर्णांकerrupts क्रम 3.3V high and 3.1V low */
	error = regmap_update_bits(ddata->reg, CPCAP_REG_BPEOL,
				   0xffff,
				   CPCAP_REG_BPEOL_BIT_BATTDETEN);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_battery_init_iio(काष्ठा cpcap_battery_ddata *ddata)
अणु
	स्थिर अक्षर * स्थिर names[CPCAP_BATTERY_IIO_NR] = अणु
		"battdetb", "battp", "chg_isense", "batti",
	पूर्ण;
	पूर्णांक error, i;

	क्रम (i = 0; i < CPCAP_BATTERY_IIO_NR; i++) अणु
		ddata->channels[i] = devm_iio_channel_get(ddata->dev,
							  names[i]);
		अगर (IS_ERR(ddata->channels[i])) अणु
			error = PTR_ERR(ddata->channels[i]);
			जाओ out_err;
		पूर्ण

		अगर (!ddata->channels[i]->indio_dev) अणु
			error = -ENXIO;
			जाओ out_err;
		पूर्ण
	पूर्ण

	वापस 0;

out_err:
	वापस dev_err_probe(ddata->dev, error,
			     "could not initialize VBUS or ID IIO\n");
पूर्ण

/* Calibrate coulomb counter */
अटल पूर्णांक cpcap_battery_calibrate(काष्ठा cpcap_battery_ddata *ddata)
अणु
	पूर्णांक error, ccc1, value;
	अचिन्हित दीर्घ समयout;

	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_CCC1, &ccc1);
	अगर (error)
		वापस error;

	समयout = jअगरfies + msecs_to_jअगरfies(6000);

	/* Start calibration */
	error = regmap_update_bits(ddata->reg, CPCAP_REG_CCC1,
				   0xffff,
				   CPCAP_REG_CCC1_CAL_EN);
	अगर (error)
		जाओ restore;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		error = regmap_पढ़ो(ddata->reg, CPCAP_REG_CCC1, &value);
		अगर (error)
			जाओ restore;

		अगर (!(value & CPCAP_REG_CCC1_CAL_EN))
			अवरोध;

		error = regmap_पढ़ो(ddata->reg, CPCAP_REG_CCM, &value);
		अगर (error)
			जाओ restore;

		msleep(300);
	पूर्ण

	/* Read calibration offset from CCM */
	error = regmap_पढ़ो(ddata->reg, CPCAP_REG_CCM, &value);
	अगर (error)
		जाओ restore;

	dev_info(ddata->dev, "calibration done: 0x%04x\n", value);

restore:
	अगर (error)
		dev_err(ddata->dev, "%s: error %i\n", __func__, error);

	error = regmap_update_bits(ddata->reg, CPCAP_REG_CCC1,
				   0xffff, ccc1);
	अगर (error)
		dev_err(ddata->dev, "%s: restore error %i\n",
			__func__, error);

	वापस error;
पूर्ण

/*
 * Based on the values from Motorola mapphone Linux kernel. In the
 * the Motorola mapphone Linux kernel tree the value क्रम pm_cd_factor
 * is passed to the kernel via device tree. If it turns out to be
 * something device specअगरic we can consider that too later.
 *
 * And looking at the battery full and shutकरोwn values क्रम the stock
 * kernel on droid 4, full is 4351000 and software initiates shutकरोwn
 * at 3078000. The device will die around 2743000.
 */
अटल स्थिर काष्ठा cpcap_battery_config cpcap_battery_शेष_data = अणु
	.cd_factor = 0x3cc,
	.info.technology = POWER_SUPPLY_TECHNOLOGY_LION,
	.info.voltage_max_design = 4351000,
	.info.voltage_min_design = 3100000,
	.info.अक्षरge_full_design = 1740000,
	.bat.स्थिरant_अक्षरge_voltage_max_uv = 4200000,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cpcap_battery_id_table[] = अणु
	अणु
		.compatible = "motorola,cpcap-battery",
		.data = &cpcap_battery_शेष_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_battery_id_table);
#पूर्ण_अगर

अटल स्थिर काष्ठा घातer_supply_desc cpcap_अक्षरger_battery_desc = अणु
	.name		= "battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= cpcap_battery_props,
	.num_properties	= ARRAY_SIZE(cpcap_battery_props),
	.get_property	= cpcap_battery_get_property,
	.set_property	= cpcap_battery_set_property,
	.property_is_ग_लिखोable = cpcap_battery_property_is_ग_लिखोable,
	.बाह्यal_घातer_changed = cpcap_battery_बाह्यal_घातer_changed,
पूर्ण;

अटल पूर्णांक cpcap_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_battery_ddata *ddata;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक error;

	match = of_match_device(of_match_ptr(cpcap_battery_id_table),
				&pdev->dev);
	अगर (!match)
		वापस -EINVAL;

	अगर (!match->data) अणु
		dev_err(&pdev->dev, "no configuration data found\n");

		वापस -ENODEV;
	पूर्ण

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ddata->irq_list);
	ddata->dev = &pdev->dev;
	स_नकल(&ddata->config, match->data, माप(ddata->config));

	ddata->reg = dev_get_regmap(ddata->dev->parent, शून्य);
	अगर (!ddata->reg)
		वापस -ENODEV;

	error = cpcap_get_venकरोr(ddata->dev, ddata->reg, &ddata->venकरोr);
	अगर (error)
		वापस error;

	चयन (ddata->venकरोr) अणु
	हाल CPCAP_VENDOR_ST:
		ddata->cc_lsb = 95374;	/* NञAms per LSB */
		अवरोध;
	हाल CPCAP_VENDOR_TI:
		ddata->cc_lsb = 91501;	/* NञAms per LSB */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ddata->cc_lsb = (ddata->cc_lsb * ddata->config.cd_factor) / 1000;

	platक्रमm_set_drvdata(pdev, ddata);

	error = cpcap_battery_init_पूर्णांकerrupts(pdev, ddata);
	अगर (error)
		वापस error;

	error = cpcap_battery_init_iio(ddata);
	अगर (error)
		वापस error;

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = ddata;

	ddata->psy = devm_घातer_supply_रेजिस्टर(ddata->dev,
						&cpcap_अक्षरger_battery_desc,
						&psy_cfg);
	error = PTR_ERR_OR_ZERO(ddata->psy);
	अगर (error) अणु
		dev_err(ddata->dev, "failed to register power supply\n");
		वापस error;
	पूर्ण

	atomic_set(&ddata->active, 1);

	error = cpcap_battery_calibrate(ddata);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_battery_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_battery_ddata *ddata = platक्रमm_get_drvdata(pdev);
	पूर्णांक error;

	atomic_set(&ddata->active, 0);
	error = regmap_update_bits(ddata->reg, CPCAP_REG_BPEOL,
				   0xffff, 0);
	अगर (error)
		dev_err(&pdev->dev, "could not disable: %i\n", error);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpcap_battery_driver = अणु
	.driver	= अणु
		.name		= "cpcap_battery",
		.of_match_table = of_match_ptr(cpcap_battery_id_table),
	पूर्ण,
	.probe	= cpcap_battery_probe,
	.हटाओ = cpcap_battery_हटाओ,
पूर्ण;
module_platक्रमm_driver(cpcap_battery_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("CPCAP PMIC Battery Driver");
