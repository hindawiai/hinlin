<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// BQ2515X Battery Charger Driver
// Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com/

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

#घोषणा BQ2515X_MANUFACTURER "Texas Instruments"

#घोषणा BQ2515X_STAT0		0x00
#घोषणा BQ2515X_STAT1		0x01
#घोषणा BQ2515X_STAT2		0x02
#घोषणा BQ2515X_FLAG0		0x03
#घोषणा BQ2515X_FLAG1		0x04
#घोषणा BQ2515X_FLAG2		0x05
#घोषणा BQ2515X_FLAG3		0x06
#घोषणा BQ2515X_MASK0		0x07
#घोषणा BQ2515X_MASK1		0x08
#घोषणा BQ2515X_MASK2		0x09
#घोषणा BQ2515X_MASK3		0x0a
#घोषणा BQ2515X_VBAT_CTRL	0x12
#घोषणा BQ2515X_ICHG_CTRL	0x13
#घोषणा BQ2515X_PCHRGCTRL	0x14
#घोषणा BQ2515X_TERMCTRL	0x15
#घोषणा BQ2515X_BUVLO		0x16
#घोषणा BQ2515X_CHARGERCTRL0	0x17
#घोषणा BQ2515X_CHARGERCTRL1	0x18
#घोषणा BQ2515X_ILIMCTRL	0x19
#घोषणा BQ2515X_LDOCTRL		0x1d
#घोषणा BQ2515X_MRCTRL		0x30
#घोषणा BQ2515X_ICCTRL0		0x35
#घोषणा BQ2515X_ICCTRL1		0x36
#घोषणा BQ2515X_ICCTRL2		0x37
#घोषणा BQ2515X_ADCCTRL0	0x40
#घोषणा BQ2515X_ADCCTRL1	0x41
#घोषणा BQ2515X_ADC_VBAT_M	0x42
#घोषणा BQ2515X_ADC_VBAT_L	0x43
#घोषणा BQ2515X_ADC_TS_M	0x44
#घोषणा BQ2515X_ADC_TS_L	0x45
#घोषणा BQ2515X_ADC_ICHG_M	0x46
#घोषणा BQ2515X_ADC_ICHG_L	0x47
#घोषणा BQ2515X_ADC_ADCIN_M	0x48
#घोषणा BQ2515X_ADC_ADCIN_L	0x49
#घोषणा BQ2515X_ADC_VIN_M	0x4a
#घोषणा BQ2515X_ADC_VIN_L	0x4b
#घोषणा BQ2515X_ADC_PMID_M	0x4c
#घोषणा BQ2515X_ADC_PMID_L	0x4d
#घोषणा BQ2515X_ADC_IIN_M	0x4e
#घोषणा BQ2515X_ADC_IIN_L	0x4f
#घोषणा BQ2515X_ADC_COMP1_M	0x52
#घोषणा BQ2515X_ADC_COMP1_L	0X53
#घोषणा BQ2515X_ADC_COMP2_M	0X54
#घोषणा BQ2515X_ADC_COMP2_L	0x55
#घोषणा BQ2515X_ADC_COMP3_M	0x56
#घोषणा BQ2515X_ADC_COMP3_L	0x57
#घोषणा BQ2515X_ADC_READ_EN	0x58
#घोषणा BQ2515X_TS_FASTCHGCTRL	0x61
#घोषणा BQ2515X_TS_COLD		0x62
#घोषणा BQ2515X_TS_COOL		0x63
#घोषणा BQ2515X_TS_WARM		0x64
#घोषणा BQ2515X_TS_HOT		0x65
#घोषणा BQ2515X_DEVICE_ID	0x6f

#घोषणा BQ2515X_DEFAULT_ICHG_UA		10000
#घोषणा BQ25150_DEFAULT_ILIM_UA		100000
#घोषणा BQ25155_DEFAULT_ILIM_UA		500000
#घोषणा BQ2515X_DEFAULT_VBAT_REG_UV	4200000
#घोषणा BQ2515X_DEFAULT_IPRECHARGE_UA	2500

#घोषणा BQ2515X_DIVISOR				65536
#घोषणा BQ2515X_VBAT_BASE_VOLT			3600000
#घोषणा BQ2515X_VBAT_REG_MAX			4600000
#घोषणा BQ2515X_VBAT_REG_MIN			3600000
#घोषणा BQ2515X_VBAT_STEP_UV			10000
#घोषणा BQ2515X_UV_FACTOR			1000000
#घोषणा BQ2515X_VBAT_MULTIPLIER			6
#घोषणा BQ2515X_ICHG_DIVISOR			52429
#घोषणा BQ2515X_ICHG_CURR_STEP_THRESH_UA	318750
#घोषणा BQ2515X_ICHG_MIN_UA			0
#घोषणा BQ2515X_ICHG_MAX_UA			500000
#घोषणा BQ2515X_ICHG_RNG_1B0_UA			1250
#घोषणा BQ2515X_ICHG_RNG_1B1_UA			2500
#घोषणा BQ2515X_VLOWV_SEL_1B0_UV		3000000
#घोषणा BQ2515X_VLOWV_SEL_1B1_UV		2800000
#घोषणा BQ2515X_PRECHRG_ICHRG_RNGE_1875_UA	18750
#घोषणा BQ2515X_PRECHRG_ICHRG_RNGE_3750_UA	37500
#घोषणा BQ2515X_TWAKE2_MIN_US			1700000
#घोषणा BQ2515X_TWAKE2_MAX_US			2300000

#घोषणा BQ2515X_ILIM_150MA	0x2
#घोषणा BQ2515X_ILIM_MASK	0x7
#घोषणा BQ2515X_ILIM_MIN	50000
#घोषणा BQ2515X_ILIM_MAX	600000
#घोषणा BQ2515X_HEALTH_MASK	0xf
#घोषणा BQ2515X_ICHGRNG_MASK	0x80
#घोषणा BQ2515X_STAT0_MASK	0x0f
#घोषणा BQ2515X_STAT1_MASK	0x1f
#घोषणा BQ2515X_PRECHARGE_MASK	0x1f

#घोषणा BQ2515X_TS_HOT_STAT		BIT(0)
#घोषणा BQ2515X_TS_WARM_STAT		BIT(1)
#घोषणा BQ2515X_TS_COOL_STAT		BIT(2)
#घोषणा BQ2515X_TS_COLD_STAT		BIT(3)
#घोषणा BQ2515X_SAFETY_TIMER_EXP	BIT(5)

#घोषणा BQ2515X_EN_VBAT_READ		BIT(3)
#घोषणा BQ2515X_EN_ICHG_READ		BIT(5)

#घोषणा BQ2515X_VIN_GOOD		BIT(0)
#घोषणा BQ2515X_CHRG_DONE		BIT(5)
#घोषणा BQ2515X_CV_CHRG_MODE		BIT(6)

#घोषणा BQ2515X_VIN_OVP_FAULT_STAT	BIT(7)

#घोषणा BQ2515X_WATCHDOG_DISABLE	BIT(4)

#घोषणा BQ2515X_ICHARGE_RANGE		BIT(7)

#घोषणा BQ2515X_VLOWV_SEL		BIT(5)

#घोषणा BQ2515X_CHARGER_DISABLE		BIT(0)

#घोषणा BQ2515X_HWRESET_14S_WD		BIT(1)

अटल स्थिर पूर्णांक bq2515x_ilim_lvl_values[] = अणु
	50000, 100000, 150000, 200000, 300000, 400000, 500000, 600000
पूर्ण;

/**
 * काष्ठा bq2515x_init_data -
 * @ilim: input current limit
 * @ichg: fast अक्षरge current
 * @vbatreg: battery regulation voltage
 * @iprechg: preअक्षरge current
 */
काष्ठा bq2515x_init_data अणु
	पूर्णांक ilim;
	पूर्णांक ichg;
	पूर्णांक vbatreg;
	पूर्णांक iprechg;
पूर्ण;

क्रमागत bq2515x_id अणु
	BQ25150,
	BQ25155,
पूर्ण;

/**
 * काष्ठा bq2515x_device -
 * @मुख्यs: मुख्यs properties
 * @battery: battery properties
 * @regmap: रेजिस्टर map काष्ठाure
 * @dev: device काष्ठाure
 *
 * @reset_gpio: manual reset (MR) pin
 * @घातerकरोwn_gpio: low घातer mode pin
 * @ac_detect_gpio: घातer good (PG) pin
 * @ce_gpio: अक्षरge enable (CE) pin
 *
 * @model_name: string value describing device model
 * @device_id: value of device_id
 * @मुख्यs_online: boolean value indicating घातer supply online
 *
 * @init_data: अक्षरger initialization data काष्ठाure
 */
काष्ठा bq2515x_device अणु
	काष्ठा घातer_supply *मुख्यs;
	काष्ठा घातer_supply *battery;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;

	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *घातerकरोwn_gpio;
	काष्ठा gpio_desc *ac_detect_gpio;
	काष्ठा gpio_desc *ce_gpio;

	अक्षर model_name[I2C_NAME_SIZE];
	पूर्णांक device_id;
	bool मुख्यs_online;

	काष्ठा bq2515x_init_data init_data;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष bq25150_reg_शेषs[] = अणु
	अणुBQ2515X_FLAG0, 0x0पूर्ण,
	अणुBQ2515X_FLAG1, 0x0पूर्ण,
	अणुBQ2515X_FLAG2, 0x0पूर्ण,
	अणुBQ2515X_FLAG3, 0x0पूर्ण,
	अणुBQ2515X_MASK0, 0x0पूर्ण,
	अणुBQ2515X_MASK1, 0x0पूर्ण,
	अणुBQ2515X_MASK2, 0x71पूर्ण,
	अणुBQ2515X_MASK3, 0x0पूर्ण,
	अणुBQ2515X_VBAT_CTRL, 0x3Cपूर्ण,
	अणुBQ2515X_ICHG_CTRL, 0x8पूर्ण,
	अणुBQ2515X_PCHRGCTRL, 0x2पूर्ण,
	अणुBQ2515X_TERMCTRL, 0x14पूर्ण,
	अणुBQ2515X_BUVLO, 0x0पूर्ण,
	अणुBQ2515X_CHARGERCTRL0, 0x82पूर्ण,
	अणुBQ2515X_CHARGERCTRL1, 0x42पूर्ण,
	अणुBQ2515X_ILIMCTRL, 0x1पूर्ण,
	अणुBQ2515X_LDOCTRL, 0xB0पूर्ण,
	अणुBQ2515X_MRCTRL, 0x2Aपूर्ण,
	अणुBQ2515X_ICCTRL0, 0x10पूर्ण,
	अणुBQ2515X_ICCTRL1, 0x0पूर्ण,
	अणुBQ2515X_ICCTRL2, 0x0पूर्ण,
	अणुBQ2515X_ADCCTRL0, 0x2पूर्ण,
	अणुBQ2515X_ADCCTRL1, 0x40पूर्ण,
	अणुBQ2515X_ADC_COMP1_M, 0x23पूर्ण,
	अणुBQ2515X_ADC_COMP1_L, 0x20पूर्ण,
	अणुBQ2515X_ADC_COMP2_M, 0x38पूर्ण,
	अणुBQ2515X_ADC_COMP2_L, 0x90पूर्ण,
	अणुBQ2515X_ADC_COMP3_M, 0x0पूर्ण,
	अणुBQ2515X_ADC_COMP3_L, 0x0पूर्ण,
	अणुBQ2515X_ADC_READ_EN, 0x0पूर्ण,
	अणुBQ2515X_TS_FASTCHGCTRL, 0x34पूर्ण,
	अणुBQ2515X_TS_COLD, 0x7Cपूर्ण,
	अणुBQ2515X_TS_COOL, 0x6Dपूर्ण,
	अणुBQ2515X_TS_WARM, 0x38पूर्ण,
	अणुBQ2515X_TS_HOT, 0x27पूर्ण,
	अणुBQ2515X_DEVICE_ID, 0x20पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष bq25155_reg_शेषs[] = अणु
	अणुBQ2515X_FLAG0, 0x0पूर्ण,
	अणुBQ2515X_FLAG1, 0x0पूर्ण,
	अणुBQ2515X_FLAG2, 0x0पूर्ण,
	अणुBQ2515X_FLAG3, 0x0पूर्ण,
	अणुBQ2515X_MASK0, 0x0पूर्ण,
	अणुBQ2515X_MASK1, 0x0पूर्ण,
	अणुBQ2515X_MASK2, 0x71पूर्ण,
	अणुBQ2515X_MASK3, 0x0पूर्ण,
	अणुBQ2515X_VBAT_CTRL, 0x3Cपूर्ण,
	अणुBQ2515X_ICHG_CTRL, 0x8पूर्ण,
	अणुBQ2515X_PCHRGCTRL, 0x2पूर्ण,
	अणुBQ2515X_TERMCTRL, 0x14पूर्ण,
	अणुBQ2515X_BUVLO, 0x0पूर्ण,
	अणुBQ2515X_CHARGERCTRL0, 0x82पूर्ण,
	अणुBQ2515X_CHARGERCTRL1, 0xC2पूर्ण,
	अणुBQ2515X_ILIMCTRL, 0x6पूर्ण,
	अणुBQ2515X_LDOCTRL, 0xB0पूर्ण,
	अणुBQ2515X_MRCTRL, 0x2Aपूर्ण,
	अणुBQ2515X_ICCTRL0, 0x10पूर्ण,
	अणुBQ2515X_ICCTRL1, 0x0पूर्ण,
	अणुBQ2515X_ICCTRL2, 0x40पूर्ण,
	अणुBQ2515X_ADCCTRL0, 0x2पूर्ण,
	अणुBQ2515X_ADCCTRL1, 0x40पूर्ण,
	अणुBQ2515X_ADC_COMP1_M, 0x23पूर्ण,
	अणुBQ2515X_ADC_COMP1_L, 0x20पूर्ण,
	अणुBQ2515X_ADC_COMP2_M, 0x38पूर्ण,
	अणुBQ2515X_ADC_COMP2_L, 0x90पूर्ण,
	अणुBQ2515X_ADC_COMP3_M, 0x0पूर्ण,
	अणुBQ2515X_ADC_COMP3_L, 0x0पूर्ण,
	अणुBQ2515X_ADC_READ_EN, 0x0पूर्ण,
	अणुBQ2515X_TS_FASTCHGCTRL, 0x34पूर्ण,
	अणुBQ2515X_TS_COLD, 0x7Cपूर्ण,
	अणुBQ2515X_TS_COOL, 0x6Dपूर्ण,
	अणुBQ2515X_TS_WARM, 0x38पूर्ण,
	अणुBQ2515X_TS_HOT, 0x27पूर्ण,
	अणुBQ2515X_DEVICE_ID, 0x35पूर्ण,
पूर्ण;

अटल पूर्णांक bq2515x_wake_up(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;
	पूर्णांक val;

	/* Read the STAT रेजिस्टर अगर we can पढ़ो it then the device is out
	 * of ship mode.  If the रेजिस्टर cannot be पढ़ो then attempt to wake
	 * it up and enable the ADC.
	 */
	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_STAT0, &val);
	अगर (ret)
		वापस ret;

	/* Need to toggle LP and bring device out of ship mode. The device
	 * will निकास the ship mode when the MR pin is held low क्रम at least
	 * t_WAKE2 as shown in section 8.3.7.1 of the datasheet.
	 */
	gpiod_set_value_cansleep(bq2515x->घातerकरोwn_gpio, 0);

	gpiod_set_value_cansleep(bq2515x->reset_gpio, 0);
	usleep_range(BQ2515X_TWAKE2_MIN_US, BQ2515X_TWAKE2_MAX_US);
	gpiod_set_value_cansleep(bq2515x->reset_gpio, 1);

	वापस regmap_ग_लिखो(bq2515x->regmap, BQ2515X_ADC_READ_EN,
				(BQ2515X_EN_VBAT_READ | BQ2515X_EN_ICHG_READ));
पूर्ण

अटल पूर्णांक bq2515x_update_ps_status(काष्ठा bq2515x_device *bq2515x)
अणु
	bool dc = false;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (bq2515x->ac_detect_gpio)
		val = gpiod_get_value_cansleep(bq2515x->ac_detect_gpio);
	अन्यथा अणु
		ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_STAT0, &val);
		अगर (ret)
			वापस ret;
	पूर्ण

	dc = val & BQ2515X_VIN_GOOD;

	ret = bq2515x->मुख्यs_online != dc;

	bq2515x->मुख्यs_online = dc;

	वापस ret;
पूर्ण

अटल पूर्णांक bq2515x_disable_watchकरोg_समयrs(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(bq2515x->regmap, BQ2515X_CHARGERCTRL0,
			BQ2515X_WATCHDOG_DISABLE, BQ2515X_WATCHDOG_DISABLE);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(bq2515x->regmap, BQ2515X_ICCTRL2,
						BQ2515X_HWRESET_14S_WD, 0);
पूर्ण

अटल पूर्णांक bq2515x_get_battery_voltage_now(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;
	पूर्णांक vbat_msb;
	पूर्णांक vbat_lsb;
	uपूर्णांक32_t vbat_measurement;

	अगर (!bq2515x->मुख्यs_online)
		bq2515x_wake_up(bq2515x);

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_ADC_VBAT_M, &vbat_msb);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_ADC_VBAT_L, &vbat_lsb);
	अगर (ret)
		वापस ret;

	vbat_measurement = (vbat_msb << 8) | vbat_lsb;

	वापस vbat_measurement * (BQ2515X_UV_FACTOR / BQ2515X_DIVISOR) *
						BQ2515X_VBAT_MULTIPLIER;
पूर्ण

अटल पूर्णांक bq2515x_get_battery_current_now(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;
	पूर्णांक ichg_msb;
	पूर्णांक ichg_lsb;
	uपूर्णांक32_t ichg_measurement;
	u16 ichg_multiplier = BQ2515X_ICHG_RNG_1B0_UA;
	अचिन्हित पूर्णांक ichg_reg_code, reg_code;
	अचिन्हित पूर्णांक iअक्षरge_range = 0, pchrgctrl;
	अचिन्हित पूर्णांक buvlo, vlowv_sel, vlowv = BQ2515X_VLOWV_SEL_1B0_UV;

	अगर (!bq2515x->मुख्यs_online)
		वापस -ENODATA;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_ADC_ICHG_M, &ichg_msb);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_ADC_ICHG_L, &ichg_lsb);
	अगर (ret)
		वापस ret;

	ichg_measurement = (ichg_msb << 8) | ichg_lsb;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_BUVLO, &buvlo);
	अगर (ret)
		वापस ret;

	vlowv_sel = buvlo & BQ2515X_VLOWV_SEL;

	अगर (vlowv_sel)
		vlowv = BQ2515X_VLOWV_SEL_1B1_UV;

	अगर (bq2515x_get_battery_voltage_now(bq2515x) < vlowv) अणु
		ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_PCHRGCTRL,
								&pchrgctrl);
		अगर (ret)
			वापस ret;

		reg_code = pchrgctrl & BQ2515X_PRECHARGE_MASK;
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_ICHG_CTRL,
							&ichg_reg_code);
		अगर (ret)
			वापस ret;

		reg_code = ichg_reg_code;
	पूर्ण

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_PCHRGCTRL, &pchrgctrl);
	अगर (ret)
		वापस ret;

	iअक्षरge_range = pchrgctrl & BQ2515X_ICHARGE_RANGE;

	अगर (iअक्षरge_range)
		ichg_multiplier = BQ2515X_ICHG_RNG_1B1_UA;

	वापस reg_code * (ichg_multiplier * ichg_measurement /
							BQ2515X_ICHG_DIVISOR);
पूर्ण

अटल bool bq2515x_get_अक्षरge_disable(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;
	पूर्णांक ce_pin;
	पूर्णांक icctrl2;
	पूर्णांक अक्षरger_disable;

	ce_pin = gpiod_get_value_cansleep(bq2515x->ce_gpio);

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_ICCTRL2, &icctrl2);
	अगर (ret)
		वापस ret;

	अक्षरger_disable = icctrl2 & BQ2515X_CHARGER_DISABLE;

	अगर (अक्षरger_disable || ce_pin)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक bq2515x_set_अक्षरge_disable(काष्ठा bq2515x_device *bq2515x, पूर्णांक val)
अणु
	gpiod_set_value_cansleep(bq2515x->ce_gpio, val);

	वापस regmap_update_bits(bq2515x->regmap, BQ2515X_ICCTRL2,
					BQ2515X_CHARGER_DISABLE, val);
पूर्ण

अटल पूर्णांक bq2515x_get_स्थिर_अक्षरge_current(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;
	u16 ichg_multiplier = BQ2515X_ICHG_RNG_1B0_UA;
	अचिन्हित पूर्णांक ichg_reg_code;
	अचिन्हित पूर्णांक pchrgctrl;
	अचिन्हित पूर्णांक iअक्षरge_range;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_ICHG_CTRL, &ichg_reg_code);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_PCHRGCTRL, &pchrgctrl);
	अगर (ret)
		वापस ret;

	iअक्षरge_range = pchrgctrl & BQ2515X_ICHARGE_RANGE;

	अगर (iअक्षरge_range)
		ichg_multiplier = BQ2515X_ICHG_RNG_1B1_UA;

	वापस ichg_reg_code * ichg_multiplier;
पूर्ण

अटल पूर्णांक bq2515x_set_स्थिर_अक्षरge_current(काष्ठा bq2515x_device *bq2515x,
								पूर्णांक val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ichg_reg_code;
	u16 ichg_multiplier = BQ2515X_ICHG_RNG_1B0_UA;
	अचिन्हित पूर्णांक iअक्षरge_range = 0;

	अगर (val > BQ2515X_ICHG_MAX_UA || val < BQ2515X_ICHG_MIN_UA)
		वापस -EINVAL;

	अगर (val > BQ2515X_ICHG_CURR_STEP_THRESH_UA) अणु
		ichg_multiplier = BQ2515X_ICHG_RNG_1B1_UA;
		iअक्षरge_range = BQ2515X_ICHARGE_RANGE;
	पूर्ण

	bq2515x_set_अक्षरge_disable(bq2515x, 1);

	ret = regmap_update_bits(bq2515x->regmap, BQ2515X_PCHRGCTRL,
					BQ2515X_ICHARGE_RANGE, iअक्षरge_range);
	अगर (ret)
		वापस ret;

	ichg_reg_code = val / ichg_multiplier;

	ret = regmap_ग_लिखो(bq2515x->regmap, BQ2515X_ICHG_CTRL, ichg_reg_code);
	अगर (ret)
		वापस ret;

	वापस bq2515x_set_अक्षरge_disable(bq2515x, 0);
पूर्ण

अटल पूर्णांक bq2515x_get_preअक्षरge_current(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pchrgctrl;
	अचिन्हित पूर्णांक iअक्षरge_range;
	u16 preअक्षरge_multiplier = BQ2515X_ICHG_RNG_1B0_UA;
	अचिन्हित पूर्णांक preअक्षरge_reg_code;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_PCHRGCTRL, &pchrgctrl);
	अगर (ret)
		वापस ret;

	iअक्षरge_range = pchrgctrl & BQ2515X_ICHARGE_RANGE;

	अगर (iअक्षरge_range)
		preअक्षरge_multiplier = BQ2515X_ICHG_RNG_1B1_UA;

	preअक्षरge_reg_code = pchrgctrl & BQ2515X_PRECHARGE_MASK;

	वापस preअक्षरge_reg_code * preअक्षरge_multiplier;
पूर्ण

अटल पूर्णांक bq2515x_set_preअक्षरge_current(काष्ठा bq2515x_device *bq2515x,
					पूर्णांक val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pchrgctrl;
	अचिन्हित पूर्णांक iअक्षरge_range;
	अचिन्हित पूर्णांक preअक्षरge_reg_code;
	अचिन्हित पूर्णांक preअक्षरge_multiplier = BQ2515X_ICHG_RNG_1B0_UA;
	अचिन्हित पूर्णांक preअक्षरge_max_ua = BQ2515X_PRECHRG_ICHRG_RNGE_1875_UA;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_PCHRGCTRL, &pchrgctrl);
	अगर (ret)
		वापस ret;

	iअक्षरge_range = pchrgctrl & BQ2515X_ICHARGE_RANGE;

	अगर (iअक्षरge_range) अणु
		preअक्षरge_max_ua = BQ2515X_PRECHRG_ICHRG_RNGE_3750_UA;
		preअक्षरge_multiplier = BQ2515X_ICHG_RNG_1B1_UA;
	पूर्ण अन्यथा अणु
		preअक्षरge_max_ua = BQ2515X_PRECHRG_ICHRG_RNGE_1875_UA;
		preअक्षरge_multiplier = BQ2515X_ICHG_RNG_1B0_UA;
	पूर्ण
	अगर (val > preअक्षरge_max_ua || val < BQ2515X_ICHG_MIN_UA)
		वापस -EINVAL;

	preअक्षरge_reg_code = val / preअक्षरge_multiplier;

	ret = bq2515x_set_अक्षरge_disable(bq2515x, 1);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(bq2515x->regmap, BQ2515X_PCHRGCTRL,
				BQ2515X_PRECHARGE_MASK, preअक्षरge_reg_code);
	अगर (ret)
		वापस ret;

	वापस bq2515x_set_अक्षरge_disable(bq2515x, 0);
पूर्ण

अटल पूर्णांक bq2515x_अक्षरging_status(काष्ठा bq2515x_device *bq2515x,
				   जोड़ घातer_supply_propval *val)
अणु
	bool status0_no_fault;
	bool status1_no_fault;
	bool ce_status;
	bool अक्षरge_करोne;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	अगर (!bq2515x->मुख्यs_online) अणु
		val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		वापस 0;
	पूर्ण

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_STAT0, &status);
	अगर (ret)
		वापस ret;

	/*
	 * The code block below is used to determine अगर any faults from the
	 * STAT0 रेजिस्टर are disbaling अक्षरging or अगर the अक्षरge has completed
	 * according to the CHARGE_DONE_STAT bit.
	 */
	अगर (((status & BQ2515X_STAT0_MASK) == true) &
			((status & BQ2515X_CHRG_DONE) == false)) अणु
		status0_no_fault = true;
		अक्षरge_करोne = false;
	पूर्ण अन्यथा अगर (status & BQ2515X_CHRG_DONE) अणु
		अक्षरge_करोne = true;
		status0_no_fault = false;
	पूर्ण अन्यथा अणु
		status0_no_fault = false;
		अक्षरge_करोne = false;
	पूर्ण

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_STAT1, &status);
	अगर (ret)
		वापस ret;
	/*
	 * The code block below is used to determine अगर any faults from the
	 * STAT1 रेजिस्टर are disbaling अक्षरging
	 */
	अगर ((status & BQ2515X_STAT1_MASK) == false)
		status1_no_fault = true;
	अन्यथा
		status1_no_fault = false;

	ce_status = (!bq2515x_get_अक्षरge_disable(bq2515x));

	/*
	 * If there are no faults and अक्षरging is enabled, then status is
	 * अक्षरging. Otherwise, अगर अक्षरging is complete, then status is full.
	 * Otherwise, अगर a fault exists or अक्षरging is disabled, then status is
	 * not अक्षरging
	 */
	अगर (status0_no_fault & status1_no_fault & ce_status)
		val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
	अन्यथा अगर (अक्षरge_करोne)
		val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
	अन्यथा अगर (!(status0_no_fault & status1_no_fault & ce_status))
		val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;

	वापस 0;
पूर्ण

अटल पूर्णांक bq2515x_get_batt_reg(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक vbat_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_VBAT_CTRL, &vbat_reg_code);
	अगर (ret)
		वापस ret;

	वापस BQ2515X_VBAT_BASE_VOLT + vbat_reg_code * BQ2515X_VBAT_STEP_UV;
पूर्ण

अटल पूर्णांक bq2515x_set_batt_reg(काष्ठा bq2515x_device *bq2515x, पूर्णांक val)
अणु
	पूर्णांक vbat_reg_code;

	अगर (val > BQ2515X_VBAT_REG_MAX || val < BQ2515X_VBAT_REG_MIN)
		वापस -EINVAL;

	vbat_reg_code = (val - BQ2515X_VBAT_BASE_VOLT) / BQ2515X_VBAT_STEP_UV;

	वापस regmap_ग_लिखो(bq2515x->regmap, BQ2515X_VBAT_CTRL, vbat_reg_code);
पूर्ण

अटल पूर्णांक bq2515x_get_ilim_lvl(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;
	पूर्णांक ilimctrl;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_ILIMCTRL, &ilimctrl);
	अगर (ret)
		वापस ret;

	वापस bq2515x_ilim_lvl_values[ilimctrl & BQ2515X_ILIM_MASK];
पूर्ण

अटल पूर्णांक bq2515x_set_ilim_lvl(काष्ठा bq2515x_device *bq2515x, पूर्णांक val)
अणु
	पूर्णांक i = 0;
	अचिन्हित पूर्णांक array_size = ARRAY_SIZE(bq2515x_ilim_lvl_values);

	क्रम (i = array_size - 1; i > 0; i--) अणु
		अगर (val >= bq2515x_ilim_lvl_values[i])
			अवरोध;
	पूर्ण
	वापस regmap_ग_लिखो(bq2515x->regmap, BQ2515X_ILIMCTRL, i);
पूर्ण

अटल पूर्णांक bq2515x_घातer_supply_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property prop)
अणु
	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक bq2515x_अक्षरger_get_health(काष्ठा bq2515x_device *bq2515x,
				      जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक health = POWER_SUPPLY_HEALTH_GOOD;
	पूर्णांक ret;
	अचिन्हित पूर्णांक stat1;
	अचिन्हित पूर्णांक flag3;

	अगर (!bq2515x->मुख्यs_online)
		bq2515x_wake_up(bq2515x);

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_FLAG3, &flag3);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq2515x->regmap, BQ2515X_STAT1, &stat1);
	अगर (ret)
		वापस ret;

	अगर (stat1 & BQ2515X_HEALTH_MASK) अणु
		चयन (stat1 & BQ2515X_HEALTH_MASK) अणु
		हाल BQ2515X_TS_HOT_STAT:
			health = POWER_SUPPLY_HEALTH_HOT;
			अवरोध;
		हाल BQ2515X_TS_WARM_STAT:
			health = POWER_SUPPLY_HEALTH_WARM;
			अवरोध;
		हाल BQ2515X_TS_COOL_STAT:
			health = POWER_SUPPLY_HEALTH_COOL;
			अवरोध;
		हाल BQ2515X_TS_COLD_STAT:
			health = POWER_SUPPLY_HEALTH_COLD;
			अवरोध;
		शेष:
			health = POWER_SUPPLY_HEALTH_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stat1 & BQ2515X_VIN_OVP_FAULT_STAT)
		health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;

	अगर (flag3 & BQ2515X_SAFETY_TIMER_EXP)
		health = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;

	val->पूर्णांकval = health;
	वापस 0;
पूर्ण

अटल पूर्णांक bq2515x_मुख्यs_set_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property prop,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq2515x_device *bq2515x = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq2515x_set_batt_reg(bq2515x, val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq2515x_set_स्थिर_अक्षरge_current(bq2515x, val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq2515x_set_ilim_lvl(bq2515x, val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		ret = bq2515x_set_preअक्षरge_current(bq2515x, val->पूर्णांकval);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bq2515x_मुख्यs_get_property(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property prop,
				     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq2515x_device *bq2515x = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (prop) अणु

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq2515x_get_स्थिर_अक्षरge_current(bq2515x);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq2515x_get_batt_reg(bq2515x);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		ret = bq2515x_get_preअक्षरge_current(bq2515x);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = bq2515x->मुख्यs_online;
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = bq2515x_अक्षरger_get_health(bq2515x, val);
		अगर (ret)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNKNOWN;
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq2515x_get_ilim_lvl(bq2515x);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bq2515x->model_name;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ2515X_MANUFACTURER;
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		ret = bq2515x_अक्षरging_status(bq2515x, val);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bq2515x_battery_get_property(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property prop,
				       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq2515x_device *bq2515x = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	ret = bq2515x_update_ps_status(bq2515x);
	अगर (ret)
		वापस ret;

	चयन (prop) अणु

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		ret = bq2515x->init_data.vbatreg;
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		ret = bq2515x->init_data.ichg;
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = bq2515x_get_battery_voltage_now(bq2515x);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = bq2515x_get_battery_current_now(bq2515x);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर क्रमागत घातer_supply_property bq2515x_battery_properties[] = अणु
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
पूर्ण;

अटल स्थिर क्रमागत घातer_supply_property bq2515x_मुख्यs_properties[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc bq2515x_मुख्यs_desc = अणु
	.name			= "bq2515x-mains",
	.type			= POWER_SUPPLY_TYPE_MAINS,
	.get_property		= bq2515x_मुख्यs_get_property,
	.set_property		= bq2515x_मुख्यs_set_property,
	.properties		= bq2515x_मुख्यs_properties,
	.num_properties		= ARRAY_SIZE(bq2515x_मुख्यs_properties),
	.property_is_ग_लिखोable	= bq2515x_घातer_supply_property_is_ग_लिखोable,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc bq2515x_battery_desc = अणु
	.name			= "bq2515x-battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.get_property		= bq2515x_battery_get_property,
	.properties		= bq2515x_battery_properties,
	.num_properties		= ARRAY_SIZE(bq2515x_battery_properties),
	.property_is_ग_लिखोable	= bq2515x_घातer_supply_property_is_ग_लिखोable,
पूर्ण;

अटल पूर्णांक bq2515x_घातer_supply_रेजिस्टर(काष्ठा bq2515x_device *bq2515x,
		काष्ठा device *dev, काष्ठा घातer_supply_config psy_cfg)
अणु
	bq2515x->मुख्यs = devm_घातer_supply_रेजिस्टर(bq2515x->dev,
						    &bq2515x_मुख्यs_desc,
						    &psy_cfg);
	अगर (IS_ERR(bq2515x->मुख्यs))
		वापस -EINVAL;

	bq2515x->battery = devm_घातer_supply_रेजिस्टर(bq2515x->dev,
						      &bq2515x_battery_desc,
						      &psy_cfg);
	अगर (IS_ERR(bq2515x->battery))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक bq2515x_hw_init(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;
	काष्ठा घातer_supply_battery_info bat_info = अणु पूर्ण;

	ret = bq2515x_disable_watchकरोg_समयrs(bq2515x);
	अगर (ret)
		वापस ret;

	अगर (bq2515x->init_data.ilim) अणु
		ret = bq2515x_set_ilim_lvl(bq2515x, bq2515x->init_data.ilim);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = घातer_supply_get_battery_info(bq2515x->मुख्यs, &bat_info);
	अगर (ret) अणु
		dev_warn(bq2515x->dev, "battery info missing, default values will be applied\n");

		bq2515x->init_data.ichg = BQ2515X_DEFAULT_ICHG_UA;

		bq2515x->init_data.vbatreg = BQ2515X_DEFAULT_VBAT_REG_UV;

		bq2515x->init_data.iprechg = BQ2515X_DEFAULT_IPRECHARGE_UA;

	पूर्ण अन्यथा अणु
		bq2515x->init_data.ichg =
				bat_info.स्थिरant_अक्षरge_current_max_ua;

		bq2515x->init_data.vbatreg =
				bat_info.स्थिरant_अक्षरge_voltage_max_uv;

		bq2515x->init_data.iprechg =
				bat_info.preअक्षरge_current_ua;
	पूर्ण

	ret = bq2515x_set_स्थिर_अक्षरge_current(bq2515x,
						bq2515x->init_data.ichg);
	अगर (ret)
		वापस ret;

	ret = bq2515x_set_batt_reg(bq2515x, bq2515x->init_data.vbatreg);
	अगर (ret)
		वापस ret;

	वापस bq2515x_set_preअक्षरge_current(bq2515x,
						bq2515x->init_data.iprechg);
पूर्ण

अटल पूर्णांक bq2515x_पढ़ो_properties(काष्ठा bq2515x_device *bq2515x)
अणु
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(bq2515x->dev,
				      "input-current-limit-microamp",
				      &bq2515x->init_data.ilim);
	अगर (ret) अणु
		चयन (bq2515x->device_id) अणु
		हाल BQ25150:
			bq2515x->init_data.ilim = BQ25150_DEFAULT_ILIM_UA;
			अवरोध;
		हाल BQ25155:
			bq2515x->init_data.ilim = BQ25155_DEFAULT_ILIM_UA;
			अवरोध;
		पूर्ण
	पूर्ण

	bq2515x->ac_detect_gpio = devm_gpiod_get_optional(bq2515x->dev,
						   "ac-detect", GPIOD_IN);
	अगर (IS_ERR(bq2515x->ac_detect_gpio)) अणु
		ret = PTR_ERR(bq2515x->ac_detect_gpio);
		dev_err(bq2515x->dev, "Failed to get ac detect");
		वापस ret;
	पूर्ण

	bq2515x->reset_gpio = devm_gpiod_get_optional(bq2515x->dev,
						   "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(bq2515x->reset_gpio)) अणु
		ret = PTR_ERR(bq2515x->reset_gpio);
		dev_err(bq2515x->dev, "Failed to get reset");
		वापस ret;
	पूर्ण

	bq2515x->घातerकरोwn_gpio = devm_gpiod_get_optional(bq2515x->dev,
						"powerdown", GPIOD_OUT_LOW);
	अगर (IS_ERR(bq2515x->घातerकरोwn_gpio)) अणु
		ret = PTR_ERR(bq2515x->घातerकरोwn_gpio);
		dev_err(bq2515x->dev, "Failed to get powerdown");
		वापस ret;
	पूर्ण

	bq2515x->ce_gpio = devm_gpiod_get_optional(bq2515x->dev,
						   "charge-enable",
						   GPIOD_OUT_LOW);
	अगर (IS_ERR(bq2515x->ce_gpio)) अणु
		ret = PTR_ERR(bq2515x->ce_gpio);
		dev_err(bq2515x->dev, "Failed to get ce");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool bq2515x_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BQ2515X_STAT0 ... BQ2515X_FLAG3:
	हाल BQ2515X_ADC_VBAT_M ... BQ2515X_ADC_IIN_L:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config bq25150_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर		= BQ2515X_DEVICE_ID,
	.reg_शेषs		= bq25150_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(bq25150_reg_शेषs),
	.cache_type		= REGCACHE_RBTREE,
	.अस्थिर_reg		= bq2515x_अस्थिर_रेजिस्टर,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bq25155_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर		= BQ2515X_DEVICE_ID,
	.reg_शेषs		= bq25155_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(bq25155_reg_शेषs),
	.cache_type		= REGCACHE_RBTREE,
	.अस्थिर_reg		= bq2515x_अस्थिर_रेजिस्टर,
पूर्ण;

अटल पूर्णांक bq2515x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा bq2515x_device *bq2515x;
	काष्ठा घातer_supply_config अक्षरger_cfg = अणुपूर्ण;
	पूर्णांक ret;

	bq2515x = devm_kzalloc(dev, माप(*bq2515x), GFP_KERNEL);
	अगर (!bq2515x)
		वापस -ENOMEM;

	bq2515x->dev = dev;

	म_नकलन(bq2515x->model_name, id->name, I2C_NAME_SIZE);

	bq2515x->device_id = id->driver_data;

	चयन (bq2515x->device_id) अणु
	हाल BQ25150:
		bq2515x->regmap = devm_regmap_init_i2c(client,
						&bq25150_regmap_config);
		अवरोध;
	हाल BQ25155:
		bq2515x->regmap = devm_regmap_init_i2c(client,
						&bq25155_regmap_config);
		अवरोध;
	पूर्ण

	अगर (IS_ERR(bq2515x->regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(bq2515x->regmap);
	पूर्ण

	i2c_set_clientdata(client, bq2515x);

	अक्षरger_cfg.drv_data = bq2515x;
	अक्षरger_cfg.of_node = dev->of_node;

	ret = bq2515x_पढ़ो_properties(bq2515x);
	अगर (ret) अणु
		dev_err(dev, "Failed to read device tree properties %d\n",
									ret);
		वापस ret;
	पूर्ण

	ret = bq2515x_घातer_supply_रेजिस्टर(bq2515x, dev, अक्षरger_cfg);
	अगर (ret) अणु
		dev_err(dev, "failed to register power supply\n");
		वापस ret;
	पूर्ण

	ret = bq2515x_hw_init(bq2515x);
	अगर (ret) अणु
		dev_err(dev, "Cannot initialize the chip\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bq2515x_i2c_ids[] = अणु
	अणु "bq25150", BQ25150, पूर्ण,
	अणु "bq25155", BQ25155, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq2515x_i2c_ids);

अटल स्थिर काष्ठा of_device_id bq2515x_of_match[] = अणु
	अणु .compatible = "ti,bq25150", पूर्ण,
	अणु .compatible = "ti,bq25155", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bq2515x_of_match);

अटल काष्ठा i2c_driver bq2515x_driver = अणु
	.driver = अणु
		.name = "bq2515x-charger",
		.of_match_table = bq2515x_of_match,
	पूर्ण,
	.probe = bq2515x_probe,
	.id_table = bq2515x_i2c_ids,
पूर्ण;
module_i2c_driver(bq2515x_driver);

MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_AUTHOR("Ricardo Rivera-Matos <r-rivera-matos@ti.com>");
MODULE_DESCRIPTION("BQ2515X charger driver");
MODULE_LICENSE("GPL v2");
