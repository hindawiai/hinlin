<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Spपढ़ोtrum Communications Inc.

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* PMIC global control रेजिस्टरs definition */
#घोषणा SC27XX_MODULE_EN0		0xc08
#घोषणा SC27XX_CLK_EN0			0xc18
#घोषणा SC27XX_FGU_EN			BIT(7)
#घोषणा SC27XX_FGU_RTC_EN		BIT(6)

/* FGU रेजिस्टरs definition */
#घोषणा SC27XX_FGU_START		0x0
#घोषणा SC27XX_FGU_CONFIG		0x4
#घोषणा SC27XX_FGU_ADC_CONFIG		0x8
#घोषणा SC27XX_FGU_STATUS		0xc
#घोषणा SC27XX_FGU_INT_EN		0x10
#घोषणा SC27XX_FGU_INT_CLR		0x14
#घोषणा SC27XX_FGU_INT_STS		0x1c
#घोषणा SC27XX_FGU_VOLTAGE		0x20
#घोषणा SC27XX_FGU_OCV			0x24
#घोषणा SC27XX_FGU_POCV			0x28
#घोषणा SC27XX_FGU_CURRENT		0x2c
#घोषणा SC27XX_FGU_LOW_OVERLOAD		0x34
#घोषणा SC27XX_FGU_CLBCNT_SETH		0x50
#घोषणा SC27XX_FGU_CLBCNT_SETL		0x54
#घोषणा SC27XX_FGU_CLBCNT_DELTH		0x58
#घोषणा SC27XX_FGU_CLBCNT_DELTL		0x5c
#घोषणा SC27XX_FGU_CLBCNT_VALH		0x68
#घोषणा SC27XX_FGU_CLBCNT_VALL		0x6c
#घोषणा SC27XX_FGU_CLBCNT_QMAXL		0x74
#घोषणा SC27XX_FGU_USER_AREA_SET	0xa0
#घोषणा SC27XX_FGU_USER_AREA_CLEAR	0xa4
#घोषणा SC27XX_FGU_USER_AREA_STATUS	0xa8
#घोषणा SC27XX_FGU_VOLTAGE_BUF		0xd0
#घोषणा SC27XX_FGU_CURRENT_BUF		0xf0

#घोषणा SC27XX_WRITE_SELCLB_EN		BIT(0)
#घोषणा SC27XX_FGU_CLBCNT_MASK		GENMASK(15, 0)
#घोषणा SC27XX_FGU_CLBCNT_SHIFT		16
#घोषणा SC27XX_FGU_LOW_OVERLOAD_MASK	GENMASK(12, 0)

#घोषणा SC27XX_FGU_INT_MASK		GENMASK(9, 0)
#घोषणा SC27XX_FGU_LOW_OVERLOAD_INT	BIT(0)
#घोषणा SC27XX_FGU_CLBCNT_DELTA_INT	BIT(2)

#घोषणा SC27XX_FGU_MODE_AREA_MASK	GENMASK(15, 12)
#घोषणा SC27XX_FGU_CAP_AREA_MASK	GENMASK(11, 0)
#घोषणा SC27XX_FGU_MODE_AREA_SHIFT	12

#घोषणा SC27XX_FGU_FIRST_POWERTON	GENMASK(3, 0)
#घोषणा SC27XX_FGU_DEFAULT_CAP		GENMASK(11, 0)
#घोषणा SC27XX_FGU_NORMAIL_POWERTON	0x5

#घोषणा SC27XX_FGU_CUR_BASIC_ADC	8192
#घोषणा SC27XX_FGU_SAMPLE_HZ		2
/* micro Ohms */
#घोषणा SC27XX_FGU_IDEAL_RESISTANCE	20000

/*
 * काष्ठा sc27xx_fgu_data: describe the FGU device
 * @regmap: regmap क्रम रेजिस्टर access
 * @dev: platक्रमm device
 * @battery: battery घातer supply
 * @base: the base offset क्रम the controller
 * @lock: protect the काष्ठाure
 * @gpiod: GPIO क्रम battery detection
 * @channel: IIO channel to get battery temperature
 * @अक्षरge_chan: IIO channel to get अक्षरge voltage
 * @पूर्णांकernal_resist: the battery पूर्णांकernal resistance in mOhm
 * @total_cap: the total capacity of the battery in mAh
 * @init_cap: the initial capacity of the battery in mAh
 * @alarm_cap: the alarm capacity
 * @init_clbcnt: the initial coulomb counter
 * @max_volt: the maximum स्थिरant input voltage in millivolt
 * @min_volt: the minimum drained battery voltage in microvolt
 * @boot_volt: the voltage measured during boot in microvolt
 * @table_len: the capacity table length
 * @resist_table_len: the resistance table length
 * @cur_1000ma_adc: ADC value corresponding to 1000 mA
 * @vol_1000mv_adc: ADC value corresponding to 1000 mV
 * @calib_resist: the real resistance of coulomb counter chip in uOhm
 * @cap_table: capacity table with corresponding ocv
 * @resist_table: resistance percent table with corresponding temperature
 */
काष्ठा sc27xx_fgu_data अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा घातer_supply *battery;
	u32 base;
	काष्ठा mutex lock;
	काष्ठा gpio_desc *gpiod;
	काष्ठा iio_channel *channel;
	काष्ठा iio_channel *अक्षरge_chan;
	bool bat_present;
	पूर्णांक पूर्णांकernal_resist;
	पूर्णांक total_cap;
	पूर्णांक init_cap;
	पूर्णांक alarm_cap;
	पूर्णांक init_clbcnt;
	पूर्णांक max_volt;
	पूर्णांक min_volt;
	पूर्णांक boot_volt;
	पूर्णांक table_len;
	पूर्णांक resist_table_len;
	पूर्णांक cur_1000ma_adc;
	पूर्णांक vol_1000mv_adc;
	पूर्णांक calib_resist;
	काष्ठा घातer_supply_battery_ocv_table *cap_table;
	काष्ठा घातer_supply_resistance_temp_table *resist_table;
पूर्ण;

अटल पूर्णांक sc27xx_fgu_cap_to_clbcnt(काष्ठा sc27xx_fgu_data *data, पूर्णांक capacity);
अटल व्योम sc27xx_fgu_capacity_calibration(काष्ठा sc27xx_fgu_data *data,
					    पूर्णांक cap, bool पूर्णांक_mode);
अटल व्योम sc27xx_fgu_adjust_cap(काष्ठा sc27xx_fgu_data *data, पूर्णांक cap);
अटल पूर्णांक sc27xx_fgu_get_temp(काष्ठा sc27xx_fgu_data *data, पूर्णांक *temp);

अटल स्थिर अक्षर * स्थिर sc27xx_अक्षरger_supply_name[] = अणु
	"sc2731_charger",
	"sc2720_charger",
	"sc2721_charger",
	"sc2723_charger",
पूर्ण;

अटल पूर्णांक sc27xx_fgu_adc_to_current(काष्ठा sc27xx_fgu_data *data, s64 adc)
अणु
	वापस DIV_S64_ROUND_CLOSEST(adc * 1000, data->cur_1000ma_adc);
पूर्ण

अटल पूर्णांक sc27xx_fgu_adc_to_voltage(काष्ठा sc27xx_fgu_data *data, s64 adc)
अणु
	वापस DIV_S64_ROUND_CLOSEST(adc * 1000, data->vol_1000mv_adc);
पूर्ण

अटल पूर्णांक sc27xx_fgu_voltage_to_adc(काष्ठा sc27xx_fgu_data *data, पूर्णांक vol)
अणु
	वापस DIV_ROUND_CLOSEST(vol * data->vol_1000mv_adc, 1000);
पूर्ण

अटल bool sc27xx_fgu_is_first_घातeron(काष्ठा sc27xx_fgu_data *data)
अणु
	पूर्णांक ret, status, cap, mode;

	ret = regmap_पढ़ो(data->regmap,
			  data->base + SC27XX_FGU_USER_AREA_STATUS, &status);
	अगर (ret)
		वापस false;

	/*
	 * We use low 4 bits to save the last battery capacity and high 12 bits
	 * to save the प्रणाली boot mode.
	 */
	mode = (status & SC27XX_FGU_MODE_AREA_MASK) >> SC27XX_FGU_MODE_AREA_SHIFT;
	cap = status & SC27XX_FGU_CAP_AREA_MASK;

	/*
	 * When FGU has been घातered करोwn, the user area रेजिस्टरs became
	 * शेष value (0xffff), which can be used to valid अगर the प्रणाली is
	 * first घातer on or not.
	 */
	अगर (mode == SC27XX_FGU_FIRST_POWERTON || cap == SC27XX_FGU_DEFAULT_CAP)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक sc27xx_fgu_save_boot_mode(काष्ठा sc27xx_fgu_data *data,
				     पूर्णांक boot_mode)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap,
				 data->base + SC27XX_FGU_USER_AREA_CLEAR,
				 SC27XX_FGU_MODE_AREA_MASK,
				 SC27XX_FGU_MODE_AREA_MASK);
	अगर (ret)
		वापस ret;

	/*
	 * Since the user area रेजिस्टरs are put on घातer always-on region,
	 * then these रेजिस्टरs changing समय will be a little दीर्घ. Thus
	 * here we should delay 200us to रुको until values are updated
	 * successfully according to the datasheet.
	 */
	udelay(200);

	ret = regmap_update_bits(data->regmap,
				 data->base + SC27XX_FGU_USER_AREA_SET,
				 SC27XX_FGU_MODE_AREA_MASK,
				 boot_mode << SC27XX_FGU_MODE_AREA_SHIFT);
	अगर (ret)
		वापस ret;

	/*
	 * Since the user area रेजिस्टरs are put on घातer always-on region,
	 * then these रेजिस्टरs changing समय will be a little दीर्घ. Thus
	 * here we should delay 200us to रुको until values are updated
	 * successfully according to the datasheet.
	 */
	udelay(200);

	/*
	 * According to the datasheet, we should set the USER_AREA_CLEAR to 0 to
	 * make the user area data available, otherwise we can not save the user
	 * area data.
	 */
	वापस regmap_update_bits(data->regmap,
				  data->base + SC27XX_FGU_USER_AREA_CLEAR,
				  SC27XX_FGU_MODE_AREA_MASK, 0);
पूर्ण

अटल पूर्णांक sc27xx_fgu_save_last_cap(काष्ठा sc27xx_fgu_data *data, पूर्णांक cap)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap,
				 data->base + SC27XX_FGU_USER_AREA_CLEAR,
				 SC27XX_FGU_CAP_AREA_MASK,
				 SC27XX_FGU_CAP_AREA_MASK);
	अगर (ret)
		वापस ret;

	/*
	 * Since the user area रेजिस्टरs are put on घातer always-on region,
	 * then these रेजिस्टरs changing समय will be a little दीर्घ. Thus
	 * here we should delay 200us to रुको until values are updated
	 * successfully according to the datasheet.
	 */
	udelay(200);

	ret = regmap_update_bits(data->regmap,
				 data->base + SC27XX_FGU_USER_AREA_SET,
				 SC27XX_FGU_CAP_AREA_MASK, cap);
	अगर (ret)
		वापस ret;

	/*
	 * Since the user area रेजिस्टरs are put on घातer always-on region,
	 * then these रेजिस्टरs changing समय will be a little दीर्घ. Thus
	 * here we should delay 200us to रुको until values are updated
	 * successfully according to the datasheet.
	 */
	udelay(200);

	/*
	 * According to the datasheet, we should set the USER_AREA_CLEAR to 0 to
	 * make the user area data available, otherwise we can not save the user
	 * area data.
	 */
	वापस regmap_update_bits(data->regmap,
				  data->base + SC27XX_FGU_USER_AREA_CLEAR,
				  SC27XX_FGU_CAP_AREA_MASK, 0);
पूर्ण

अटल पूर्णांक sc27xx_fgu_पढ़ो_last_cap(काष्ठा sc27xx_fgu_data *data, पूर्णांक *cap)
अणु
	पूर्णांक ret, value;

	ret = regmap_पढ़ो(data->regmap,
			  data->base + SC27XX_FGU_USER_AREA_STATUS, &value);
	अगर (ret)
		वापस ret;

	*cap = value & SC27XX_FGU_CAP_AREA_MASK;
	वापस 0;
पूर्ण

/*
 * When प्रणाली boots on, we can not पढ़ो battery capacity from coulomb
 * रेजिस्टरs, since now the coulomb रेजिस्टरs are invalid. So we should
 * calculate the battery खोलो circuit voltage, and get current battery
 * capacity according to the capacity table.
 */
अटल पूर्णांक sc27xx_fgu_get_boot_capacity(काष्ठा sc27xx_fgu_data *data, पूर्णांक *cap)
अणु
	पूर्णांक volt, cur, oci, ocv, ret;
	bool is_first_घातeron = sc27xx_fgu_is_first_घातeron(data);

	/*
	 * If प्रणाली is not the first घातer on, we should use the last saved
	 * battery capacity as the initial battery capacity. Otherwise we should
	 * re-calculate the initial battery capacity.
	 */
	अगर (!is_first_घातeron) अणु
		ret = sc27xx_fgu_पढ़ो_last_cap(data, cap);
		अगर (ret)
			वापस ret;

		वापस sc27xx_fgu_save_boot_mode(data, SC27XX_FGU_NORMAIL_POWERTON);
	पूर्ण

	/*
	 * After प्रणाली booting on, the SC27XX_FGU_CLBCNT_QMAXL रेजिस्टर saved
	 * the first sampled खोलो circuit current.
	 */
	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_CLBCNT_QMAXL,
			  &cur);
	अगर (ret)
		वापस ret;

	cur <<= 1;
	oci = sc27xx_fgu_adc_to_current(data, cur - SC27XX_FGU_CUR_BASIC_ADC);

	/*
	 * Should get the OCV from SC27XX_FGU_POCV रेजिस्टर at the प्रणाली
	 * beginning. It is ADC values पढ़ोing from रेजिस्टरs which need to
	 * convert the corresponding voltage.
	 */
	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_POCV, &volt);
	अगर (ret)
		वापस ret;

	volt = sc27xx_fgu_adc_to_voltage(data, volt);
	ocv = volt * 1000 - oci * data->पूर्णांकernal_resist;
	data->boot_volt = ocv;

	/*
	 * Parse the capacity table to look up the correct capacity percent
	 * according to current battery's corresponding OCV values.
	 */
	*cap = घातer_supply_ocv2cap_simple(data->cap_table, data->table_len,
					   ocv);

	ret = sc27xx_fgu_save_last_cap(data, *cap);
	अगर (ret)
		वापस ret;

	वापस sc27xx_fgu_save_boot_mode(data, SC27XX_FGU_NORMAIL_POWERTON);
पूर्ण

अटल पूर्णांक sc27xx_fgu_set_clbcnt(काष्ठा sc27xx_fgu_data *data, पूर्णांक clbcnt)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap,
				 data->base + SC27XX_FGU_CLBCNT_SETL,
				 SC27XX_FGU_CLBCNT_MASK, clbcnt);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(data->regmap,
				 data->base + SC27XX_FGU_CLBCNT_SETH,
				 SC27XX_FGU_CLBCNT_MASK,
				 clbcnt >> SC27XX_FGU_CLBCNT_SHIFT);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(data->regmap, data->base + SC27XX_FGU_START,
				 SC27XX_WRITE_SELCLB_EN,
				 SC27XX_WRITE_SELCLB_EN);
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_clbcnt(काष्ठा sc27xx_fgu_data *data, पूर्णांक *clb_cnt)
अणु
	पूर्णांक ccl, cch, ret;

	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_CLBCNT_VALL,
			  &ccl);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_CLBCNT_VALH,
			  &cch);
	अगर (ret)
		वापस ret;

	*clb_cnt = ccl & SC27XX_FGU_CLBCNT_MASK;
	*clb_cnt |= (cch & SC27XX_FGU_CLBCNT_MASK) << SC27XX_FGU_CLBCNT_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_vol_now(काष्ठा sc27xx_fgu_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	u32 vol;

	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_VOLTAGE_BUF,
			  &vol);
	अगर (ret)
		वापस ret;

	/*
	 * It is ADC values पढ़ोing from रेजिस्टरs which need to convert to
	 * corresponding voltage values.
	 */
	*val = sc27xx_fgu_adc_to_voltage(data, vol);

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_cur_now(काष्ठा sc27xx_fgu_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	u32 cur;

	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_CURRENT_BUF,
			  &cur);
	अगर (ret)
		वापस ret;

	/*
	 * It is ADC values पढ़ोing from रेजिस्टरs which need to convert to
	 * corresponding current values.
	 */
	*val = sc27xx_fgu_adc_to_current(data, cur - SC27XX_FGU_CUR_BASIC_ADC);

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_capacity(काष्ठा sc27xx_fgu_data *data, पूर्णांक *cap)
अणु
	पूर्णांक ret, cur_clbcnt, delta_clbcnt, delta_cap, temp;

	/* Get current coulomb counters firstly */
	ret = sc27xx_fgu_get_clbcnt(data, &cur_clbcnt);
	अगर (ret)
		वापस ret;

	delta_clbcnt = cur_clbcnt - data->init_clbcnt;

	/*
	 * Convert coulomb counter to delta capacity (mAh), and set multiplier
	 * as 10 to improve the precision.
	 */
	temp = DIV_ROUND_CLOSEST(delta_clbcnt * 10, 36 * SC27XX_FGU_SAMPLE_HZ);
	temp = sc27xx_fgu_adc_to_current(data, temp / 1000);

	/*
	 * Convert to capacity percent of the battery total capacity,
	 * and multiplier is 100 too.
	 */
	delta_cap = DIV_ROUND_CLOSEST(temp * 100, data->total_cap);
	*cap = delta_cap + data->init_cap;

	/* Calibrate the battery capacity in a normal range. */
	sc27xx_fgu_capacity_calibration(data, *cap, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_vbat_vol(काष्ठा sc27xx_fgu_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret, vol;

	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_VOLTAGE, &vol);
	अगर (ret)
		वापस ret;

	/*
	 * It is ADC values पढ़ोing from रेजिस्टरs which need to convert to
	 * corresponding voltage values.
	 */
	*val = sc27xx_fgu_adc_to_voltage(data, vol);

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_current(काष्ठा sc27xx_fgu_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret, cur;

	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_CURRENT, &cur);
	अगर (ret)
		वापस ret;

	/*
	 * It is ADC values पढ़ोing from रेजिस्टरs which need to convert to
	 * corresponding current values.
	 */
	*val = sc27xx_fgu_adc_to_current(data, cur - SC27XX_FGU_CUR_BASIC_ADC);

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_vbat_ocv(काष्ठा sc27xx_fgu_data *data, पूर्णांक *val)
अणु
	पूर्णांक vol, cur, ret, temp, resistance;

	ret = sc27xx_fgu_get_vbat_vol(data, &vol);
	अगर (ret)
		वापस ret;

	ret = sc27xx_fgu_get_current(data, &cur);
	अगर (ret)
		वापस ret;

	resistance = data->पूर्णांकernal_resist;
	अगर (data->resist_table_len > 0) अणु
		ret = sc27xx_fgu_get_temp(data, &temp);
		अगर (ret)
			वापस ret;

		resistance = घातer_supply_temp2resist_simple(data->resist_table,
						data->resist_table_len, temp);
		resistance = data->पूर्णांकernal_resist * resistance / 100;
	पूर्ण

	/* Return the battery OCV in micro volts. */
	*val = vol * 1000 - cur * resistance;

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_अक्षरge_vol(काष्ठा sc27xx_fgu_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret, vol;

	ret = iio_पढ़ो_channel_processed(data->अक्षरge_chan, &vol);
	अगर (ret < 0)
		वापस ret;

	*val = vol * 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_temp(काष्ठा sc27xx_fgu_data *data, पूर्णांक *temp)
अणु
	वापस iio_पढ़ो_channel_processed(data->channel, temp);
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_health(काष्ठा sc27xx_fgu_data *data, पूर्णांक *health)
अणु
	पूर्णांक ret, vol;

	ret = sc27xx_fgu_get_vbat_vol(data, &vol);
	अगर (ret)
		वापस ret;

	अगर (vol > data->max_volt)
		*health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	अन्यथा
		*health = POWER_SUPPLY_HEALTH_GOOD;

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_status(काष्ठा sc27xx_fgu_data *data, पूर्णांक *status)
अणु
	जोड़ घातer_supply_propval val;
	काष्ठा घातer_supply *psy;
	पूर्णांक i, ret = -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(sc27xx_अक्षरger_supply_name); i++) अणु
		psy = घातer_supply_get_by_name(sc27xx_अक्षरger_supply_name[i]);
		अगर (!psy)
			जारी;

		ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_STATUS,
						&val);
		घातer_supply_put(psy);
		अगर (ret)
			वापस ret;

		*status = val.पूर्णांकval;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sc27xx_fgu_get_property(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sc27xx_fgu_data *data = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;
	पूर्णांक value;

	mutex_lock(&data->lock);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = sc27xx_fgu_get_status(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value;
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = sc27xx_fgu_get_health(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value;
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = data->bat_present;
		अवरोध;

	हाल POWER_SUPPLY_PROP_TEMP:
		ret = sc27xx_fgu_get_temp(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value;
		अवरोध;

	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = sc27xx_fgu_get_capacity(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		ret = sc27xx_fgu_get_vbat_vol(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_OCV:
		ret = sc27xx_fgu_get_vbat_ocv(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = sc27xx_fgu_get_अक्षरge_vol(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = sc27xx_fgu_get_current(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		val->पूर्णांकval = data->total_cap * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = sc27xx_fgu_get_clbcnt(data, &value);
		अगर (ret)
			जाओ error;

		value = DIV_ROUND_CLOSEST(value * 10,
					  36 * SC27XX_FGU_SAMPLE_HZ);
		val->पूर्णांकval = sc27xx_fgu_adc_to_current(data, value);

		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = sc27xx_fgu_get_vol_now(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = sc27xx_fgu_get_cur_now(data, &value);
		अगर (ret)
			जाओ error;

		val->पूर्णांकval = value * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_BOOT:
		val->पूर्णांकval = data->boot_volt;
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

error:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sc27xx_fgu_set_property(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sc27xx_fgu_data *data = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	mutex_lock(&data->lock);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = sc27xx_fgu_save_last_cap(data, val->पूर्णांकval);
		अगर (ret < 0)
			dev_err(data->dev, "failed to save battery capacity\n");
		अवरोध;

	हाल POWER_SUPPLY_PROP_CALIBRATE:
		sc27xx_fgu_adjust_cap(data, val->पूर्णांकval);
		ret = 0;
		अवरोध;

	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		data->total_cap = val->पूर्णांकval / 1000;
		ret = 0;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल व्योम sc27xx_fgu_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा sc27xx_fgu_data *data = घातer_supply_get_drvdata(psy);

	घातer_supply_changed(data->battery);
पूर्ण

अटल पूर्णांक sc27xx_fgu_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					    क्रमागत घातer_supply_property psp)
अणु
	वापस psp == POWER_SUPPLY_PROP_CAPACITY ||
		psp == POWER_SUPPLY_PROP_CALIBRATE ||
		psp == POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN;
पूर्ण

अटल क्रमागत घातer_supply_property sc27xx_fgu_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_OCV,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_BOOT,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN,
	POWER_SUPPLY_PROP_CALIBRATE,
	POWER_SUPPLY_PROP_CHARGE_NOW
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc sc27xx_fgu_desc = अणु
	.name			= "sc27xx-fgu",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= sc27xx_fgu_props,
	.num_properties		= ARRAY_SIZE(sc27xx_fgu_props),
	.get_property		= sc27xx_fgu_get_property,
	.set_property		= sc27xx_fgu_set_property,
	.बाह्यal_घातer_changed	= sc27xx_fgu_बाह्यal_घातer_changed,
	.property_is_ग_लिखोable	= sc27xx_fgu_property_is_ग_लिखोable,
	.no_thermal		= true,
पूर्ण;

अटल व्योम sc27xx_fgu_adjust_cap(काष्ठा sc27xx_fgu_data *data, पूर्णांक cap)
अणु
	पूर्णांक ret;

	data->init_cap = cap;
	ret = sc27xx_fgu_get_clbcnt(data, &data->init_clbcnt);
	अगर (ret)
		dev_err(data->dev, "failed to get init coulomb counter\n");
पूर्ण

अटल व्योम sc27xx_fgu_capacity_calibration(काष्ठा sc27xx_fgu_data *data,
					    पूर्णांक cap, bool पूर्णांक_mode)
अणु
	पूर्णांक ret, ocv, chg_sts, adc;

	ret = sc27xx_fgu_get_vbat_ocv(data, &ocv);
	अगर (ret) अणु
		dev_err(data->dev, "get battery ocv error.\n");
		वापस;
	पूर्ण

	ret = sc27xx_fgu_get_status(data, &chg_sts);
	अगर (ret) अणु
		dev_err(data->dev, "get charger status error.\n");
		वापस;
	पूर्ण

	/*
	 * If we are in अक्षरging mode, then we करो not need to calibrate the
	 * lower capacity.
	 */
	अगर (chg_sts == POWER_SUPPLY_STATUS_CHARGING)
		वापस;

	अगर ((ocv > data->cap_table[0].ocv && cap < 100) || cap > 100) अणु
		/*
		 * If current OCV value is larger than the max OCV value in
		 * OCV table, or the current capacity is larger than 100,
		 * we should क्रमce the inititial capacity to 100.
		 */
		sc27xx_fgu_adjust_cap(data, 100);
	पूर्ण अन्यथा अगर (ocv <= data->cap_table[data->table_len - 1].ocv) अणु
		/*
		 * If current OCV value is leass than the minimum OCV value in
		 * OCV table, we should क्रमce the inititial capacity to 0.
		 */
		sc27xx_fgu_adjust_cap(data, 0);
	पूर्ण अन्यथा अगर ((ocv > data->cap_table[data->table_len - 1].ocv && cap <= 0) ||
		   (ocv > data->min_volt && cap <= data->alarm_cap)) अणु
		/*
		 * If current OCV value is not matchable with current capacity,
		 * we should re-calculate current capacity by looking up the
		 * OCV table.
		 */
		पूर्णांक cur_cap = घातer_supply_ocv2cap_simple(data->cap_table,
							  data->table_len, ocv);

		sc27xx_fgu_adjust_cap(data, cur_cap);
	पूर्ण अन्यथा अगर (ocv <= data->min_volt) अणु
		/*
		 * If current OCV value is less than the low alarm voltage, but
		 * current capacity is larger than the alarm capacity, we should
		 * adjust the inititial capacity to alarm capacity.
		 */
		अगर (cap > data->alarm_cap) अणु
			sc27xx_fgu_adjust_cap(data, data->alarm_cap);
		पूर्ण अन्यथा अणु
			पूर्णांक cur_cap;

			/*
			 * If current capacity is equal with 0 or less than 0
			 * (some error occurs), we should adjust inititial
			 * capacity to the capacity corresponding to current OCV
			 * value.
			 */
			cur_cap = घातer_supply_ocv2cap_simple(data->cap_table,
							      data->table_len,
							      ocv);
			sc27xx_fgu_adjust_cap(data, cur_cap);
		पूर्ण

		अगर (!पूर्णांक_mode)
			वापस;

		/*
		 * After adjusting the battery capacity, we should set the
		 * lowest alarm voltage instead.
		 */
		data->min_volt = data->cap_table[data->table_len - 1].ocv;
		data->alarm_cap = घातer_supply_ocv2cap_simple(data->cap_table,
							      data->table_len,
							      data->min_volt);

		adc = sc27xx_fgu_voltage_to_adc(data, data->min_volt / 1000);
		regmap_update_bits(data->regmap,
				   data->base + SC27XX_FGU_LOW_OVERLOAD,
				   SC27XX_FGU_LOW_OVERLOAD_MASK, adc);
	पूर्ण
पूर्ण

अटल irqवापस_t sc27xx_fgu_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sc27xx_fgu_data *data = dev_id;
	पूर्णांक ret, cap;
	u32 status;

	mutex_lock(&data->lock);

	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_FGU_INT_STS,
			  &status);
	अगर (ret)
		जाओ out;

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_INT_CLR,
				 status, status);
	अगर (ret)
		जाओ out;

	/*
	 * When low overload voltage पूर्णांकerrupt happens, we should calibrate the
	 * battery capacity in lower voltage stage.
	 */
	अगर (!(status & SC27XX_FGU_LOW_OVERLOAD_INT))
		जाओ out;

	ret = sc27xx_fgu_get_capacity(data, &cap);
	अगर (ret)
		जाओ out;

	sc27xx_fgu_capacity_calibration(data, cap, true);

out:
	mutex_unlock(&data->lock);

	घातer_supply_changed(data->battery);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sc27xx_fgu_bat_detection(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sc27xx_fgu_data *data = dev_id;
	पूर्णांक state;

	mutex_lock(&data->lock);

	state = gpiod_get_value_cansleep(data->gpiod);
	अगर (state < 0) अणु
		dev_err(data->dev, "failed to get gpio state\n");
		mutex_unlock(&data->lock);
		वापस IRQ_RETVAL(state);
	पूर्ण

	data->bat_present = !!state;

	mutex_unlock(&data->lock);

	घातer_supply_changed(data->battery);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sc27xx_fgu_disable(व्योम *_data)
अणु
	काष्ठा sc27xx_fgu_data *data = _data;

	regmap_update_bits(data->regmap, SC27XX_CLK_EN0, SC27XX_FGU_RTC_EN, 0);
	regmap_update_bits(data->regmap, SC27XX_MODULE_EN0, SC27XX_FGU_EN, 0);
पूर्ण

अटल पूर्णांक sc27xx_fgu_cap_to_clbcnt(काष्ठा sc27xx_fgu_data *data, पूर्णांक capacity)
अणु
	/*
	 * Get current capacity (mAh) = battery total capacity (mAh) *
	 * current capacity percent (capacity / 100).
	 */
	पूर्णांक cur_cap = DIV_ROUND_CLOSEST(data->total_cap * capacity, 100);

	/*
	 * Convert current capacity (mAh) to coulomb counter according to the
	 * क्रमmula: 1 mAh =3.6 coulomb.
	 */
	वापस DIV_ROUND_CLOSEST(cur_cap * 36 * data->cur_1000ma_adc * SC27XX_FGU_SAMPLE_HZ, 10);
पूर्ण

अटल पूर्णांक sc27xx_fgu_calibration(काष्ठा sc27xx_fgu_data *data)
अणु
	काष्ठा nvmem_cell *cell;
	पूर्णांक calib_data, cal_4200mv;
	व्योम *buf;
	माप_प्रकार len;

	cell = nvmem_cell_get(data->dev, "fgu_calib");
	अगर (IS_ERR(cell))
		वापस PTR_ERR(cell);

	buf = nvmem_cell_पढ़ो(cell, &len);
	nvmem_cell_put(cell);

	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	स_नकल(&calib_data, buf, min(len, माप(u32)));

	/*
	 * Get the ADC value corresponding to 4200 mV from eFuse controller
	 * according to below क्रमmula. Then convert to ADC values corresponding
	 * to 1000 mV and 1000 mA.
	 */
	cal_4200mv = (calib_data & 0x1ff) + 6963 - 4096 - 256;
	data->vol_1000mv_adc = DIV_ROUND_CLOSEST(cal_4200mv * 10, 42);
	data->cur_1000ma_adc =
		DIV_ROUND_CLOSEST(data->vol_1000mv_adc * 4 * data->calib_resist,
				  SC27XX_FGU_IDEAL_RESISTANCE);

	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_hw_init(काष्ठा sc27xx_fgu_data *data)
अणु
	काष्ठा घातer_supply_battery_info info = अणु पूर्ण;
	काष्ठा घातer_supply_battery_ocv_table *table;
	पूर्णांक ret, delta_clbcnt, alarm_adc;

	ret = घातer_supply_get_battery_info(data->battery, &info);
	अगर (ret) अणु
		dev_err(data->dev, "failed to get battery information\n");
		वापस ret;
	पूर्ण

	data->total_cap = info.अक्षरge_full_design_uah / 1000;
	data->max_volt = info.स्थिरant_अक्षरge_voltage_max_uv / 1000;
	data->पूर्णांकernal_resist = info.factory_पूर्णांकernal_resistance_uohm / 1000;
	data->min_volt = info.voltage_min_design_uv;

	/*
	 * For SC27XX fuel gauge device, we only use one ocv-capacity
	 * table in normal temperature 20 Celsius.
	 */
	table = घातer_supply_find_ocv2cap_table(&info, 20, &data->table_len);
	अगर (!table)
		वापस -EINVAL;

	data->cap_table = devm_kmemdup(data->dev, table,
				       data->table_len * माप(*table),
				       GFP_KERNEL);
	अगर (!data->cap_table) अणु
		घातer_supply_put_battery_info(data->battery, &info);
		वापस -ENOMEM;
	पूर्ण

	data->alarm_cap = घातer_supply_ocv2cap_simple(data->cap_table,
						      data->table_len,
						      data->min_volt);
	अगर (!data->alarm_cap)
		data->alarm_cap += 1;

	data->resist_table_len = info.resist_table_size;
	अगर (data->resist_table_len > 0) अणु
		data->resist_table = devm_kmemdup(data->dev, info.resist_table,
						  data->resist_table_len *
						  माप(काष्ठा घातer_supply_resistance_temp_table),
						  GFP_KERNEL);
		अगर (!data->resist_table) अणु
			घातer_supply_put_battery_info(data->battery, &info);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	घातer_supply_put_battery_info(data->battery, &info);

	ret = sc27xx_fgu_calibration(data);
	अगर (ret)
		वापस ret;

	/* Enable the FGU module */
	ret = regmap_update_bits(data->regmap, SC27XX_MODULE_EN0,
				 SC27XX_FGU_EN, SC27XX_FGU_EN);
	अगर (ret) अणु
		dev_err(data->dev, "failed to enable fgu\n");
		वापस ret;
	पूर्ण

	/* Enable the FGU RTC घड़ी to make it work */
	ret = regmap_update_bits(data->regmap, SC27XX_CLK_EN0,
				 SC27XX_FGU_RTC_EN, SC27XX_FGU_RTC_EN);
	अगर (ret) अणु
		dev_err(data->dev, "failed to enable fgu RTC clock\n");
		जाओ disable_fgu;
	पूर्ण

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_INT_CLR,
				 SC27XX_FGU_INT_MASK, SC27XX_FGU_INT_MASK);
	अगर (ret) अणु
		dev_err(data->dev, "failed to clear interrupt status\n");
		जाओ disable_clk;
	पूर्ण

	/*
	 * Set the voltage low overload threshold, which means when the battery
	 * voltage is lower than this threshold, the controller will generate
	 * one पूर्णांकerrupt to notअगरy.
	 */
	alarm_adc = sc27xx_fgu_voltage_to_adc(data, data->min_volt / 1000);
	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_LOW_OVERLOAD,
				 SC27XX_FGU_LOW_OVERLOAD_MASK, alarm_adc);
	अगर (ret) अणु
		dev_err(data->dev, "failed to set fgu low overload\n");
		जाओ disable_clk;
	पूर्ण

	/*
	 * Set the coulomb counter delta threshold, that means when the coulomb
	 * counter change is multiples of the delta threshold, the controller
	 * will generate one पूर्णांकerrupt to notअगरy the users to update the battery
	 * capacity. Now we set the delta threshold as a counter value of 1%
	 * capacity.
	 */
	delta_clbcnt = sc27xx_fgu_cap_to_clbcnt(data, 1);

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_CLBCNT_DELTL,
				 SC27XX_FGU_CLBCNT_MASK, delta_clbcnt);
	अगर (ret) अणु
		dev_err(data->dev, "failed to set low delta coulomb counter\n");
		जाओ disable_clk;
	पूर्ण

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_CLBCNT_DELTH,
				 SC27XX_FGU_CLBCNT_MASK,
				 delta_clbcnt >> SC27XX_FGU_CLBCNT_SHIFT);
	अगर (ret) अणु
		dev_err(data->dev, "failed to set high delta coulomb counter\n");
		जाओ disable_clk;
	पूर्ण

	/*
	 * Get the boot battery capacity when प्रणाली घातers on, which is used to
	 * initialize the coulomb counter. After that, we can पढ़ो the coulomb
	 * counter to measure the battery capacity.
	 */
	ret = sc27xx_fgu_get_boot_capacity(data, &data->init_cap);
	अगर (ret) अणु
		dev_err(data->dev, "failed to get boot capacity\n");
		जाओ disable_clk;
	पूर्ण

	/*
	 * Convert battery capacity to the corresponding initial coulomb counter
	 * and set पूर्णांकo coulomb counter रेजिस्टरs.
	 */
	data->init_clbcnt = sc27xx_fgu_cap_to_clbcnt(data, data->init_cap);
	ret = sc27xx_fgu_set_clbcnt(data, data->init_clbcnt);
	अगर (ret) अणु
		dev_err(data->dev, "failed to initialize coulomb counter\n");
		जाओ disable_clk;
	पूर्ण

	वापस 0;

disable_clk:
	regmap_update_bits(data->regmap, SC27XX_CLK_EN0, SC27XX_FGU_RTC_EN, 0);
disable_fgu:
	regmap_update_bits(data->regmap, SC27XX_MODULE_EN0, SC27XX_FGU_EN, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक sc27xx_fgu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा घातer_supply_config fgu_cfg = अणु पूर्ण;
	काष्ठा sc27xx_fgu_data *data;
	पूर्णांक ret, irq;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!data->regmap) अणु
		dev_err(dev, "failed to get regmap\n");
		वापस -ENODEV;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "reg", &data->base);
	अगर (ret) अणु
		dev_err(dev, "failed to get fgu address\n");
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(&pdev->dev,
				       "sprd,calib-resistance-micro-ohms",
				       &data->calib_resist);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to get fgu calibration resistance\n");
		वापस ret;
	पूर्ण

	data->channel = devm_iio_channel_get(dev, "bat-temp");
	अगर (IS_ERR(data->channel)) अणु
		dev_err(dev, "failed to get IIO channel\n");
		वापस PTR_ERR(data->channel);
	पूर्ण

	data->अक्षरge_chan = devm_iio_channel_get(dev, "charge-vol");
	अगर (IS_ERR(data->अक्षरge_chan)) अणु
		dev_err(dev, "failed to get charge IIO channel\n");
		वापस PTR_ERR(data->अक्षरge_chan);
	पूर्ण

	data->gpiod = devm_gpiod_get(dev, "bat-detect", GPIOD_IN);
	अगर (IS_ERR(data->gpiod)) अणु
		dev_err(dev, "failed to get battery detection GPIO\n");
		वापस PTR_ERR(data->gpiod);
	पूर्ण

	ret = gpiod_get_value_cansleep(data->gpiod);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get gpio state\n");
		वापस ret;
	पूर्ण

	data->bat_present = !!ret;
	mutex_init(&data->lock);
	data->dev = dev;
	platक्रमm_set_drvdata(pdev, data);

	fgu_cfg.drv_data = data;
	fgu_cfg.of_node = np;
	data->battery = devm_घातer_supply_रेजिस्टर(dev, &sc27xx_fgu_desc,
						   &fgu_cfg);
	अगर (IS_ERR(data->battery)) अणु
		dev_err(dev, "failed to register power supply\n");
		वापस PTR_ERR(data->battery);
	पूर्ण

	ret = sc27xx_fgu_hw_init(data);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize fgu hardware\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, sc27xx_fgu_disable, data);
	अगर (ret) अणु
		dev_err(dev, "failed to add fgu disable action\n");
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(dev, "no irq resource specified\n");
		वापस irq;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(data->dev, irq, शून्य,
					sc27xx_fgu_पूर्णांकerrupt,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					pdev->name, data);
	अगर (ret) अणु
		dev_err(data->dev, "failed to request fgu IRQ\n");
		वापस ret;
	पूर्ण

	irq = gpiod_to_irq(data->gpiod);
	अगर (irq < 0) अणु
		dev_err(dev, "failed to translate GPIO to IRQ\n");
		वापस irq;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					sc27xx_fgu_bat_detection,
					IRQF_ONESHOT | IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING,
					pdev->name, data);
	अगर (ret) अणु
		dev_err(dev, "failed to request IRQ\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sc27xx_fgu_resume(काष्ठा device *dev)
अणु
	काष्ठा sc27xx_fgu_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_INT_EN,
				 SC27XX_FGU_LOW_OVERLOAD_INT |
				 SC27XX_FGU_CLBCNT_DELTA_INT, 0);
	अगर (ret) अणु
		dev_err(data->dev, "failed to disable fgu interrupts\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_fgu_suspend(काष्ठा device *dev)
अणु
	काष्ठा sc27xx_fgu_data *data = dev_get_drvdata(dev);
	पूर्णांक ret, status, ocv;

	ret = sc27xx_fgu_get_status(data, &status);
	अगर (ret)
		वापस ret;

	/*
	 * If we are अक्षरging, then no need to enable the FGU पूर्णांकerrupts to
	 * adjust the battery capacity.
	 */
	अगर (status != POWER_SUPPLY_STATUS_NOT_CHARGING &&
	    status != POWER_SUPPLY_STATUS_DISCHARGING)
		वापस 0;

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_INT_EN,
				 SC27XX_FGU_LOW_OVERLOAD_INT,
				 SC27XX_FGU_LOW_OVERLOAD_INT);
	अगर (ret) अणु
		dev_err(data->dev, "failed to enable low voltage interrupt\n");
		वापस ret;
	पूर्ण

	ret = sc27xx_fgu_get_vbat_ocv(data, &ocv);
	अगर (ret)
		जाओ disable_पूर्णांक;

	/*
	 * If current OCV is less than the minimum voltage, we should enable the
	 * coulomb counter threshold पूर्णांकerrupt to notअगरy events to adjust the
	 * battery capacity.
	 */
	अगर (ocv < data->min_volt) अणु
		ret = regmap_update_bits(data->regmap,
					 data->base + SC27XX_FGU_INT_EN,
					 SC27XX_FGU_CLBCNT_DELTA_INT,
					 SC27XX_FGU_CLBCNT_DELTA_INT);
		अगर (ret) अणु
			dev_err(data->dev,
				"failed to enable coulomb threshold int\n");
			जाओ disable_पूर्णांक;
		पूर्ण
	पूर्ण

	वापस 0;

disable_पूर्णांक:
	regmap_update_bits(data->regmap, data->base + SC27XX_FGU_INT_EN,
			   SC27XX_FGU_LOW_OVERLOAD_INT, 0);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sc27xx_fgu_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sc27xx_fgu_suspend, sc27xx_fgu_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sc27xx_fgu_of_match[] = अणु
	अणु .compatible = "sprd,sc2731-fgu", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sc27xx_fgu_driver = अणु
	.probe = sc27xx_fgu_probe,
	.driver = अणु
		.name = "sc27xx-fgu",
		.of_match_table = sc27xx_fgu_of_match,
		.pm = &sc27xx_fgu_pm_ops,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(sc27xx_fgu_driver);

MODULE_DESCRIPTION("Spreadtrum SC27XX PMICs Fual Gauge Unit Driver");
MODULE_LICENSE("GPL v2");
