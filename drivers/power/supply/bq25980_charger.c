<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// BQ25980 Battery Charger Driver
// Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>

#समावेश "bq25980_charger.h"

काष्ठा bq25980_state अणु
	bool dischg;
	bool ovp;
	bool ocp;
	bool wdt;
	bool tflt;
	bool online;
	bool ce;
	bool hiz;
	bool bypass;

	u32 vbat_adc;
	u32 vsys_adc;
	u32 ibat_adc;
पूर्ण;

क्रमागत bq25980_id अणु
	BQ25980,
	BQ25975,
	BQ25960,
पूर्ण;

काष्ठा bq25980_chip_info अणु

	पूर्णांक model_id;

	स्थिर काष्ठा regmap_config *regmap_config;

	पूर्णांक busocp_def;
	पूर्णांक busocp_sc_max;
	पूर्णांक busocp_byp_max;
	पूर्णांक busocp_sc_min;
	पूर्णांक busocp_byp_min;

	पूर्णांक busovp_sc_def;
	पूर्णांक busovp_byp_def;
	पूर्णांक busovp_sc_step;

	पूर्णांक busovp_sc_offset;
	पूर्णांक busovp_byp_step;
	पूर्णांक busovp_byp_offset;
	पूर्णांक busovp_sc_min;
	पूर्णांक busovp_sc_max;
	पूर्णांक busovp_byp_min;
	पूर्णांक busovp_byp_max;

	पूर्णांक batovp_def;
	पूर्णांक batovp_max;
	पूर्णांक batovp_min;
	पूर्णांक batovp_step;
	पूर्णांक batovp_offset;

	पूर्णांक batocp_def;
	पूर्णांक batocp_max;
पूर्ण;

काष्ठा bq25980_init_data अणु
	u32 ichg;
	u32 bypass_ilim;
	u32 sc_ilim;
	u32 vreg;
	u32 iterm;
	u32 iprechg;
	u32 bypass_vlim;
	u32 sc_vlim;
	u32 ichg_max;
	u32 vreg_max;
पूर्ण;

काष्ठा bq25980_device अणु
	काष्ठा i2c_client *client;
	काष्ठा device *dev;
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा घातer_supply *battery;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;

	अक्षर model_name[I2C_NAME_SIZE];

	काष्ठा bq25980_init_data init_data;
	स्थिर काष्ठा bq25980_chip_info *chip_info;
	काष्ठा bq25980_state state;
	पूर्णांक watchकरोg_समयr;
पूर्ण;

अटल काष्ठा reg_शेष bq25980_reg_defs[] = अणु
	अणुBQ25980_BATOVP, 0x5Aपूर्ण,
	अणुBQ25980_BATOVP_ALM, 0x46पूर्ण,
	अणुBQ25980_BATOCP, 0x51पूर्ण,
	अणुBQ25980_BATOCP_ALM, 0x50पूर्ण,
	अणुBQ25980_BATUCP_ALM, 0x28पूर्ण,
	अणुBQ25980_CHRGR_CTRL_1, 0x0पूर्ण,
	अणुBQ25980_BUSOVP, 0x26पूर्ण,
	अणुBQ25980_BUSOVP_ALM, 0x22पूर्ण,
	अणुBQ25980_BUSOCP, 0xDपूर्ण,
	अणुBQ25980_BUSOCP_ALM, 0xCपूर्ण,
	अणुBQ25980_TEMP_CONTROL, 0x30पूर्ण,
	अणुBQ25980_TDIE_ALM, 0xC8पूर्ण,
	अणुBQ25980_TSBUS_FLT, 0x15पूर्ण,
	अणुBQ25980_TSBAT_FLG, 0x15पूर्ण,
	अणुBQ25980_VAC_CONTROL, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_2, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_3, 0x20पूर्ण,
	अणुBQ25980_CHRGR_CTRL_4, 0x1Dपूर्ण,
	अणुBQ25980_CHRGR_CTRL_5, 0x18पूर्ण,
	अणुBQ25980_STAT1, 0x0पूर्ण,
	अणुBQ25980_STAT2, 0x0पूर्ण,
	अणुBQ25980_STAT3, 0x0पूर्ण,
	अणुBQ25980_STAT4, 0x0पूर्ण,
	अणुBQ25980_STAT5, 0x0पूर्ण,
	अणुBQ25980_FLAG1, 0x0पूर्ण,
	अणुBQ25980_FLAG2, 0x0पूर्ण,
	अणुBQ25980_FLAG3, 0x0पूर्ण,
	अणुBQ25980_FLAG4, 0x0पूर्ण,
	अणुBQ25980_FLAG5, 0x0पूर्ण,
	अणुBQ25980_MASK1, 0x0पूर्ण,
	अणुBQ25980_MASK2, 0x0पूर्ण,
	अणुBQ25980_MASK3, 0x0पूर्ण,
	अणुBQ25980_MASK4, 0x0पूर्ण,
	अणुBQ25980_MASK5, 0x0पूर्ण,
	अणुBQ25980_DEVICE_INFO, 0x8पूर्ण,
	अणुBQ25980_ADC_CONTROL1, 0x0पूर्ण,
	अणुBQ25980_ADC_CONTROL2, 0x0पूर्ण,
	अणुBQ25980_IBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_IBUS_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_VBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VBUS_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_VAC1_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VAC2_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VOUT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_IBAT_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_IBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TSBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TSBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TDIE_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_DEGLITCH_TIME, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_6, 0x0पूर्ण,
पूर्ण;

अटल काष्ठा reg_शेष bq25975_reg_defs[] = अणु
	अणुBQ25980_BATOVP, 0x5Aपूर्ण,
	अणुBQ25980_BATOVP_ALM, 0x46पूर्ण,
	अणुBQ25980_BATOCP, 0x51पूर्ण,
	अणुBQ25980_BATOCP_ALM, 0x50पूर्ण,
	अणुBQ25980_BATUCP_ALM, 0x28पूर्ण,
	अणुBQ25980_CHRGR_CTRL_1, 0x0पूर्ण,
	अणुBQ25980_BUSOVP, 0x26पूर्ण,
	अणुBQ25980_BUSOVP_ALM, 0x22पूर्ण,
	अणुBQ25980_BUSOCP, 0xDपूर्ण,
	अणुBQ25980_BUSOCP_ALM, 0xCपूर्ण,
	अणुBQ25980_TEMP_CONTROL, 0x30पूर्ण,
	अणुBQ25980_TDIE_ALM, 0xC8पूर्ण,
	अणुBQ25980_TSBUS_FLT, 0x15पूर्ण,
	अणुBQ25980_TSBAT_FLG, 0x15पूर्ण,
	अणुBQ25980_VAC_CONTROL, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_2, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_3, 0x20पूर्ण,
	अणुBQ25980_CHRGR_CTRL_4, 0x1Dपूर्ण,
	अणुBQ25980_CHRGR_CTRL_5, 0x18पूर्ण,
	अणुBQ25980_STAT1, 0x0पूर्ण,
	अणुBQ25980_STAT2, 0x0पूर्ण,
	अणुBQ25980_STAT3, 0x0पूर्ण,
	अणुBQ25980_STAT4, 0x0पूर्ण,
	अणुBQ25980_STAT5, 0x0पूर्ण,
	अणुBQ25980_FLAG1, 0x0पूर्ण,
	अणुBQ25980_FLAG2, 0x0पूर्ण,
	अणुBQ25980_FLAG3, 0x0पूर्ण,
	अणुBQ25980_FLAG4, 0x0पूर्ण,
	अणुBQ25980_FLAG5, 0x0पूर्ण,
	अणुBQ25980_MASK1, 0x0पूर्ण,
	अणुBQ25980_MASK2, 0x0पूर्ण,
	अणुBQ25980_MASK3, 0x0पूर्ण,
	अणुBQ25980_MASK4, 0x0पूर्ण,
	अणुBQ25980_MASK5, 0x0पूर्ण,
	अणुBQ25980_DEVICE_INFO, 0x8पूर्ण,
	अणुBQ25980_ADC_CONTROL1, 0x0पूर्ण,
	अणुBQ25980_ADC_CONTROL2, 0x0पूर्ण,
	अणुBQ25980_IBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_IBUS_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_VBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VBUS_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_VAC1_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VAC2_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VOUT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_IBAT_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_IBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TSBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TSBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TDIE_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_DEGLITCH_TIME, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_6, 0x0पूर्ण,
पूर्ण;

अटल काष्ठा reg_शेष bq25960_reg_defs[] = अणु
	अणुBQ25980_BATOVP, 0x5Aपूर्ण,
	अणुBQ25980_BATOVP_ALM, 0x46पूर्ण,
	अणुBQ25980_BATOCP, 0x51पूर्ण,
	अणुBQ25980_BATOCP_ALM, 0x50पूर्ण,
	अणुBQ25980_BATUCP_ALM, 0x28पूर्ण,
	अणुBQ25980_CHRGR_CTRL_1, 0x0पूर्ण,
	अणुBQ25980_BUSOVP, 0x26पूर्ण,
	अणुBQ25980_BUSOVP_ALM, 0x22पूर्ण,
	अणुBQ25980_BUSOCP, 0xDपूर्ण,
	अणुBQ25980_BUSOCP_ALM, 0xCपूर्ण,
	अणुBQ25980_TEMP_CONTROL, 0x30पूर्ण,
	अणुBQ25980_TDIE_ALM, 0xC8पूर्ण,
	अणुBQ25980_TSBUS_FLT, 0x15पूर्ण,
	अणुBQ25980_TSBAT_FLG, 0x15पूर्ण,
	अणुBQ25980_VAC_CONTROL, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_2, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_3, 0x20पूर्ण,
	अणुBQ25980_CHRGR_CTRL_4, 0x1Dपूर्ण,
	अणुBQ25980_CHRGR_CTRL_5, 0x18पूर्ण,
	अणुBQ25980_STAT1, 0x0पूर्ण,
	अणुBQ25980_STAT2, 0x0पूर्ण,
	अणुBQ25980_STAT3, 0x0पूर्ण,
	अणुBQ25980_STAT4, 0x0पूर्ण,
	अणुBQ25980_STAT5, 0x0पूर्ण,
	अणुBQ25980_FLAG1, 0x0पूर्ण,
	अणुBQ25980_FLAG2, 0x0पूर्ण,
	अणुBQ25980_FLAG3, 0x0पूर्ण,
	अणुBQ25980_FLAG4, 0x0पूर्ण,
	अणुBQ25980_FLAG5, 0x0पूर्ण,
	अणुBQ25980_MASK1, 0x0पूर्ण,
	अणुBQ25980_MASK2, 0x0पूर्ण,
	अणुBQ25980_MASK3, 0x0पूर्ण,
	अणुBQ25980_MASK4, 0x0पूर्ण,
	अणुBQ25980_MASK5, 0x0पूर्ण,
	अणुBQ25980_DEVICE_INFO, 0x8पूर्ण,
	अणुBQ25980_ADC_CONTROL1, 0x0पूर्ण,
	अणुBQ25980_ADC_CONTROL2, 0x0पूर्ण,
	अणुBQ25980_IBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_IBUS_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_VBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VBUS_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_VAC1_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VAC2_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VOUT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_VBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_IBAT_ADC_MSB, 0x0पूर्ण,
	अणुBQ25980_IBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TSBUS_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TSBAT_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_TDIE_ADC_LSB, 0x0पूर्ण,
	अणुBQ25980_DEGLITCH_TIME, 0x0पूर्ण,
	अणुBQ25980_CHRGR_CTRL_6, 0x0पूर्ण,
पूर्ण;

अटल पूर्णांक bq25980_watchकरोg_समय[BQ25980_NUM_WD_VAL] = अणु5000, 10000, 50000,
							300000पूर्ण;

अटल पूर्णांक bq25980_get_input_curr_lim(काष्ठा bq25980_device *bq)
अणु
	अचिन्हित पूर्णांक busocp_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_BUSOCP, &busocp_reg_code);
	अगर (ret)
		वापस ret;

	वापस (busocp_reg_code * BQ25980_BUSOCP_STEP_uA) + BQ25980_BUSOCP_OFFSET_uA;
पूर्ण

अटल पूर्णांक bq25980_set_hiz(काष्ठा bq25980_device *bq, पूर्णांक setting)
अणु
	वापस regmap_update_bits(bq->regmap, BQ25980_CHRGR_CTRL_2,
			BQ25980_EN_HIZ, setting);
पूर्ण

अटल पूर्णांक bq25980_set_input_curr_lim(काष्ठा bq25980_device *bq, पूर्णांक busocp)
अणु
	अचिन्हित पूर्णांक busocp_reg_code;
	पूर्णांक ret;

	अगर (!busocp)
		वापस bq25980_set_hiz(bq, BQ25980_ENABLE_HIZ);

	bq25980_set_hiz(bq, BQ25980_DISABLE_HIZ);

	अगर (busocp < BQ25980_BUSOCP_MIN_uA)
		busocp = BQ25980_BUSOCP_MIN_uA;

	अगर (bq->state.bypass)
		busocp = min(busocp, bq->chip_info->busocp_sc_max);
	अन्यथा
		busocp = min(busocp, bq->chip_info->busocp_byp_max);

	busocp_reg_code = (busocp - BQ25980_BUSOCP_OFFSET_uA)
						/ BQ25980_BUSOCP_STEP_uA;

	ret = regmap_ग_लिखो(bq->regmap, BQ25980_BUSOCP, busocp_reg_code);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(bq->regmap, BQ25980_BUSOCP_ALM, busocp_reg_code);
पूर्ण

अटल पूर्णांक bq25980_get_input_volt_lim(काष्ठा bq25980_device *bq)
अणु
	अचिन्हित पूर्णांक busovp_reg_code;
	अचिन्हित पूर्णांक busovp_offset;
	अचिन्हित पूर्णांक busovp_step;
	पूर्णांक ret;

	अगर (bq->state.bypass) अणु
		busovp_step = bq->chip_info->busovp_byp_step;
		busovp_offset = bq->chip_info->busovp_byp_offset;
	पूर्ण अन्यथा अणु
		busovp_step = bq->chip_info->busovp_sc_step;
		busovp_offset = bq->chip_info->busovp_sc_offset;
	पूर्ण

	ret = regmap_पढ़ो(bq->regmap, BQ25980_BUSOVP, &busovp_reg_code);
	अगर (ret)
		वापस ret;

	वापस (busovp_reg_code * busovp_step) + busovp_offset;
पूर्ण

अटल पूर्णांक bq25980_set_input_volt_lim(काष्ठा bq25980_device *bq, पूर्णांक busovp)
अणु
	अचिन्हित पूर्णांक busovp_reg_code;
	अचिन्हित पूर्णांक busovp_step;
	अचिन्हित पूर्णांक busovp_offset;
	पूर्णांक ret;

	अगर (bq->state.bypass) अणु
		busovp_step = bq->chip_info->busovp_byp_step;
		busovp_offset = bq->chip_info->busovp_byp_offset;
		अगर (busovp > bq->chip_info->busovp_byp_max)
			busovp = bq->chip_info->busovp_byp_max;
		अन्यथा अगर (busovp < bq->chip_info->busovp_byp_min)
			busovp = bq->chip_info->busovp_byp_min;
	पूर्ण अन्यथा अणु
		busovp_step = bq->chip_info->busovp_sc_step;
		busovp_offset = bq->chip_info->busovp_sc_offset;
		अगर (busovp > bq->chip_info->busovp_sc_max)
			busovp = bq->chip_info->busovp_sc_max;
		अन्यथा अगर (busovp < bq->chip_info->busovp_sc_min)
			busovp = bq->chip_info->busovp_sc_min;
	पूर्ण

	busovp_reg_code = (busovp - busovp_offset) / busovp_step;

	ret = regmap_ग_लिखो(bq->regmap, BQ25980_BUSOVP, busovp_reg_code);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(bq->regmap, BQ25980_BUSOVP_ALM, busovp_reg_code);
पूर्ण

अटल पूर्णांक bq25980_get_स्थिर_अक्षरge_curr(काष्ठा bq25980_device *bq)
अणु
	अचिन्हित पूर्णांक batocp_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_BATOCP, &batocp_reg_code);
	अगर (ret)
		वापस ret;

	वापस (batocp_reg_code & BQ25980_BATOCP_MASK) *
						BQ25980_BATOCP_STEP_uA;
पूर्ण

अटल पूर्णांक bq25980_set_स्थिर_अक्षरge_curr(काष्ठा bq25980_device *bq, पूर्णांक batocp)
अणु
	अचिन्हित पूर्णांक batocp_reg_code;
	पूर्णांक ret;

	batocp = max(batocp, BQ25980_BATOCP_MIN_uA);
	batocp = min(batocp, bq->chip_info->batocp_max);

	batocp_reg_code = batocp / BQ25980_BATOCP_STEP_uA;

	ret = regmap_update_bits(bq->regmap, BQ25980_BATOCP,
				BQ25980_BATOCP_MASK, batocp_reg_code);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(bq->regmap, BQ25980_BATOCP_ALM,
				BQ25980_BATOCP_MASK, batocp_reg_code);
पूर्ण

अटल पूर्णांक bq25980_get_स्थिर_अक्षरge_volt(काष्ठा bq25980_device *bq)
अणु
	अचिन्हित पूर्णांक batovp_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_BATOVP, &batovp_reg_code);
	अगर (ret)
		वापस ret;

	वापस ((batovp_reg_code * bq->chip_info->batovp_step) +
			bq->chip_info->batovp_offset);
पूर्ण

अटल पूर्णांक bq25980_set_स्थिर_अक्षरge_volt(काष्ठा bq25980_device *bq, पूर्णांक batovp)
अणु
	अचिन्हित पूर्णांक batovp_reg_code;
	पूर्णांक ret;

	अगर (batovp < bq->chip_info->batovp_min)
		batovp = bq->chip_info->batovp_min;

	अगर (batovp > bq->chip_info->batovp_max)
		batovp = bq->chip_info->batovp_max;

	batovp_reg_code = (batovp - bq->chip_info->batovp_offset) /
						bq->chip_info->batovp_step;

	ret = regmap_ग_लिखो(bq->regmap, BQ25980_BATOVP, batovp_reg_code);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(bq->regmap, BQ25980_BATOVP_ALM, batovp_reg_code);
पूर्ण

अटल पूर्णांक bq25980_set_bypass(काष्ठा bq25980_device *bq, bool en_bypass)
अणु
	पूर्णांक ret;

	अगर (en_bypass)
		ret = regmap_update_bits(bq->regmap, BQ25980_CHRGR_CTRL_2,
					BQ25980_EN_BYPASS, BQ25980_EN_BYPASS);
	अन्यथा
		ret = regmap_update_bits(bq->regmap, BQ25980_CHRGR_CTRL_2,
					BQ25980_EN_BYPASS, en_bypass);
	अगर (ret)
		वापस ret;

	bq->state.bypass = en_bypass;

	वापस bq->state.bypass;
पूर्ण

अटल पूर्णांक bq25980_set_chg_en(काष्ठा bq25980_device *bq, bool en_chg)
अणु
	पूर्णांक ret;

	अगर (en_chg)
		ret = regmap_update_bits(bq->regmap, BQ25980_CHRGR_CTRL_2,
					BQ25980_CHG_EN, BQ25980_CHG_EN);
	अन्यथा
		ret = regmap_update_bits(bq->regmap, BQ25980_CHRGR_CTRL_2,
					BQ25980_CHG_EN, en_chg);
	अगर (ret)
		वापस ret;

	bq->state.ce = en_chg;

	वापस 0;
पूर्ण

अटल पूर्णांक bq25980_get_adc_ibus(काष्ठा bq25980_device *bq)
अणु
	पूर्णांक ibus_adc_lsb, ibus_adc_msb;
	u16 ibus_adc;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_IBUS_ADC_MSB, &ibus_adc_msb);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_IBUS_ADC_LSB, &ibus_adc_lsb);
	अगर (ret)
		वापस ret;

	ibus_adc = (ibus_adc_msb << 8) | ibus_adc_lsb;

	अगर (ibus_adc_msb & BQ25980_ADC_POLARITY_BIT)
		वापस ((ibus_adc ^ 0xffff) + 1) * BQ25980_ADC_CURR_STEP_uA;

	वापस ibus_adc * BQ25980_ADC_CURR_STEP_uA;
पूर्ण

अटल पूर्णांक bq25980_get_adc_vbus(काष्ठा bq25980_device *bq)
अणु
	पूर्णांक vbus_adc_lsb, vbus_adc_msb;
	u16 vbus_adc;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_VBUS_ADC_MSB, &vbus_adc_msb);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_VBUS_ADC_LSB, &vbus_adc_lsb);
	अगर (ret)
		वापस ret;

	vbus_adc = (vbus_adc_msb << 8) | vbus_adc_lsb;

	वापस vbus_adc * BQ25980_ADC_VOLT_STEP_uV;
पूर्ण

अटल पूर्णांक bq25980_get_ibat_adc(काष्ठा bq25980_device *bq)
अणु
	पूर्णांक ret;
	पूर्णांक ibat_adc_lsb, ibat_adc_msb;
	पूर्णांक ibat_adc;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_IBAT_ADC_MSB, &ibat_adc_msb);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_IBAT_ADC_LSB, &ibat_adc_lsb);
	अगर (ret)
		वापस ret;

	ibat_adc = (ibat_adc_msb << 8) | ibat_adc_lsb;

	अगर (ibat_adc_msb & BQ25980_ADC_POLARITY_BIT)
		वापस ((ibat_adc ^ 0xffff) + 1) * BQ25980_ADC_CURR_STEP_uA;

	वापस ibat_adc * BQ25980_ADC_CURR_STEP_uA;
पूर्ण

अटल पूर्णांक bq25980_get_adc_vbat(काष्ठा bq25980_device *bq)
अणु
	पूर्णांक vsys_adc_lsb, vsys_adc_msb;
	u16 vsys_adc;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_VBAT_ADC_MSB, &vsys_adc_msb);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_VBAT_ADC_LSB, &vsys_adc_lsb);
	अगर (ret)
		वापस ret;

	vsys_adc = (vsys_adc_msb << 8) | vsys_adc_lsb;

	वापस vsys_adc * BQ25980_ADC_VOLT_STEP_uV;
पूर्ण

अटल पूर्णांक bq25980_get_state(काष्ठा bq25980_device *bq,
				काष्ठा bq25980_state *state)
अणु
	अचिन्हित पूर्णांक chg_ctrl_2;
	अचिन्हित पूर्णांक stat1;
	अचिन्हित पूर्णांक stat2;
	अचिन्हित पूर्णांक stat3;
	अचिन्हित पूर्णांक stat4;
	अचिन्हित पूर्णांक ibat_adc_msb;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_STAT1, &stat1);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_STAT2, &stat2);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_STAT3, &stat3);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_STAT4, &stat4);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_CHRGR_CTRL_2, &chg_ctrl_2);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ25980_IBAT_ADC_MSB, &ibat_adc_msb);
	अगर (ret)
		वापस ret;

	state->dischg = ibat_adc_msb & BQ25980_ADC_POLARITY_BIT;
	state->ovp = (stat1 & BQ25980_STAT1_OVP_MASK) |
		(stat3 & BQ25980_STAT3_OVP_MASK);
	state->ocp = (stat1 & BQ25980_STAT1_OCP_MASK) |
		(stat2 & BQ25980_STAT2_OCP_MASK);
	state->tflt = stat4 & BQ25980_STAT4_TFLT_MASK;
	state->wdt = stat4 & BQ25980_WD_STAT;
	state->online = stat3 & BQ25980_PRESENT_MASK;
	state->ce = chg_ctrl_2 & BQ25980_CHG_EN;
	state->hiz = chg_ctrl_2 & BQ25980_EN_HIZ;
	state->bypass = chg_ctrl_2 & BQ25980_EN_BYPASS;

	वापस 0;
पूर्ण

अटल पूर्णांक bq25980_get_battery_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq25980_device *bq = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->पूर्णांकval = bq->init_data.ichg_max;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->पूर्णांकval = bq->init_data.vreg_max;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = bq25980_get_ibat_adc(bq);
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = bq25980_get_adc_vbat(bq);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bq25980_set_अक्षरger_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property prop,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq25980_device *bq = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = -EINVAL;

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq25980_set_input_curr_lim(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		ret = bq25980_set_input_volt_lim(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = bq25980_set_bypass(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		ret = bq25980_set_chg_en(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq25980_set_स्थिर_अक्षरge_curr(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq25980_set_स्थिर_अक्षरge_volt(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bq25980_get_अक्षरger_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq25980_device *bq = घातer_supply_get_drvdata(psy);
	काष्ठा bq25980_state state;
	पूर्णांक ret = 0;

	mutex_lock(&bq->lock);
	ret = bq25980_get_state(bq, &state);
	mutex_unlock(&bq->lock);
	अगर (ret)
		वापस ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ25980_MANUFACTURER;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bq->model_name;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = state.online;
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		ret = bq25980_get_input_volt_lim(bq);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq25980_get_input_curr_lim(bq);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;

		अगर (state.tflt)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा अगर (state.ovp)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अन्यथा अगर (state.ocp)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERCURRENT;
		अन्यथा अगर (state.wdt)
			val->पूर्णांकval =
				POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE;
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;

		अगर ((state.ce) && (!state.hiz))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा अगर (state.dischg)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (!state.ce)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;

		अगर (!state.ce)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अन्यथा अगर (state.bypass)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अन्यथा अगर (!state.bypass)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_STANDARD;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = bq25980_get_adc_ibus(bq);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = bq25980_get_adc_vbus(bq);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq25980_get_स्थिर_अक्षरge_curr(bq);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq25980_get_स्थिर_अक्षरge_volt(bq);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool bq25980_state_changed(काष्ठा bq25980_device *bq,
				  काष्ठा bq25980_state *new_state)
अणु
	काष्ठा bq25980_state old_state;

	mutex_lock(&bq->lock);
	old_state = bq->state;
	mutex_unlock(&bq->lock);

	वापस (old_state.dischg != new_state->dischg ||
		old_state.ovp != new_state->ovp ||
		old_state.ocp != new_state->ocp ||
		old_state.online != new_state->online ||
		old_state.wdt != new_state->wdt ||
		old_state.tflt != new_state->tflt ||
		old_state.ce != new_state->ce ||
		old_state.hiz != new_state->hiz ||
		old_state.bypass != new_state->bypass);
पूर्ण

अटल irqवापस_t bq25980_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा bq25980_device *bq = निजी;
	काष्ठा bq25980_state state;
	पूर्णांक ret;

	ret = bq25980_get_state(bq, &state);
	अगर (ret < 0)
		जाओ irq_out;

	अगर (!bq25980_state_changed(bq, &state))
		जाओ irq_out;

	mutex_lock(&bq->lock);
	bq->state = state;
	mutex_unlock(&bq->lock);

	घातer_supply_changed(bq->अक्षरger);

irq_out:
	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत घातer_supply_property bq25980_घातer_supply_props[] = अणु
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

अटल क्रमागत घातer_supply_property bq25980_battery_props[] = अणु
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

अटल अक्षर *bq25980_अक्षरger_supplied_to[] = अणु
	"main-battery",
पूर्ण;

अटल पूर्णांक bq25980_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property prop)
अणु
	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
	हाल POWER_SUPPLY_PROP_STATUS:
	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc bq25980_घातer_supply_desc = अणु
	.name = "bq25980-charger",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = bq25980_घातer_supply_props,
	.num_properties = ARRAY_SIZE(bq25980_घातer_supply_props),
	.get_property = bq25980_get_अक्षरger_property,
	.set_property = bq25980_set_अक्षरger_property,
	.property_is_ग_लिखोable = bq25980_property_is_ग_लिखोable,
पूर्ण;

अटल काष्ठा घातer_supply_desc bq25980_battery_desc = अणु
	.name			= "bq25980-battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.get_property		= bq25980_get_battery_property,
	.properties		= bq25980_battery_props,
	.num_properties		= ARRAY_SIZE(bq25980_battery_props),
	.property_is_ग_लिखोable	= bq25980_property_is_ग_लिखोable,
पूर्ण;


अटल bool bq25980_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BQ25980_CHRGR_CTRL_2:
	हाल BQ25980_STAT1...BQ25980_FLAG5:
	हाल BQ25980_ADC_CONTROL1...BQ25980_TDIE_ADC_LSB:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config bq25980_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BQ25980_CHRGR_CTRL_6,
	.reg_शेषs	= bq25980_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(bq25980_reg_defs),
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = bq25980_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bq25975_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BQ25980_CHRGR_CTRL_6,
	.reg_शेषs	= bq25975_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(bq25975_reg_defs),
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = bq25980_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bq25960_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BQ25980_CHRGR_CTRL_6,
	.reg_शेषs	= bq25960_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(bq25960_reg_defs),
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = bq25980_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा bq25980_chip_info bq25980_chip_info_tbl[] = अणु
	[BQ25980] = अणु
		.model_id = BQ25980,
		.regmap_config = &bq25980_regmap_config,

		.busocp_def = BQ25980_BUSOCP_DFLT_uA,
		.busocp_sc_min = BQ25960_BUSOCP_SC_MAX_uA,
		.busocp_sc_max = BQ25980_BUSOCP_SC_MAX_uA,
		.busocp_byp_max = BQ25980_BUSOCP_BYP_MAX_uA,
		.busocp_byp_min = BQ25980_BUSOCP_MIN_uA,

		.busovp_sc_def = BQ25980_BUSOVP_DFLT_uV,
		.busovp_byp_def = BQ25980_BUSOVP_BYPASS_DFLT_uV,
		.busovp_sc_step = BQ25980_BUSOVP_SC_STEP_uV,
		.busovp_sc_offset = BQ25980_BUSOVP_SC_OFFSET_uV,
		.busovp_byp_step = BQ25980_BUSOVP_BYP_STEP_uV,
		.busovp_byp_offset = BQ25980_BUSOVP_BYP_OFFSET_uV,
		.busovp_sc_min = BQ25980_BUSOVP_SC_MIN_uV,
		.busovp_sc_max = BQ25980_BUSOVP_SC_MAX_uV,
		.busovp_byp_min = BQ25980_BUSOVP_BYP_MIN_uV,
		.busovp_byp_max = BQ25980_BUSOVP_BYP_MAX_uV,

		.batovp_def = BQ25980_BATOVP_DFLT_uV,
		.batovp_max = BQ25980_BATOVP_MAX_uV,
		.batovp_min = BQ25980_BATOVP_MIN_uV,
		.batovp_step = BQ25980_BATOVP_STEP_uV,
		.batovp_offset = BQ25980_BATOVP_OFFSET_uV,

		.batocp_def = BQ25980_BATOCP_DFLT_uA,
		.batocp_max = BQ25980_BATOCP_MAX_uA,
	पूर्ण,

	[BQ25975] = अणु
		.model_id = BQ25975,
		.regmap_config = &bq25975_regmap_config,

		.busocp_def = BQ25975_BUSOCP_DFLT_uA,
		.busocp_sc_min = BQ25975_BUSOCP_SC_MAX_uA,
		.busocp_sc_max = BQ25975_BUSOCP_SC_MAX_uA,
		.busocp_byp_min = BQ25980_BUSOCP_MIN_uA,
		.busocp_byp_max = BQ25975_BUSOCP_BYP_MAX_uA,

		.busovp_sc_def = BQ25975_BUSOVP_DFLT_uV,
		.busovp_byp_def = BQ25975_BUSOVP_BYPASS_DFLT_uV,
		.busovp_sc_step = BQ25975_BUSOVP_SC_STEP_uV,
		.busovp_sc_offset = BQ25975_BUSOVP_SC_OFFSET_uV,
		.busovp_byp_step = BQ25975_BUSOVP_BYP_STEP_uV,
		.busovp_byp_offset = BQ25975_BUSOVP_BYP_OFFSET_uV,
		.busovp_sc_min = BQ25975_BUSOVP_SC_MIN_uV,
		.busovp_sc_max = BQ25975_BUSOVP_SC_MAX_uV,
		.busovp_byp_min = BQ25975_BUSOVP_BYP_MIN_uV,
		.busovp_byp_max = BQ25975_BUSOVP_BYP_MAX_uV,

		.batovp_def = BQ25975_BATOVP_DFLT_uV,
		.batovp_max = BQ25975_BATOVP_MAX_uV,
		.batovp_min = BQ25975_BATOVP_MIN_uV,
		.batovp_step = BQ25975_BATOVP_STEP_uV,
		.batovp_offset = BQ25975_BATOVP_OFFSET_uV,

		.batocp_def = BQ25980_BATOCP_DFLT_uA,
		.batocp_max = BQ25980_BATOCP_MAX_uA,
	पूर्ण,

	[BQ25960] = अणु
		.model_id = BQ25960,
		.regmap_config = &bq25960_regmap_config,

		.busocp_def = BQ25960_BUSOCP_DFLT_uA,
		.busocp_sc_min = BQ25960_BUSOCP_SC_MAX_uA,
		.busocp_sc_max = BQ25960_BUSOCP_SC_MAX_uA,
		.busocp_byp_min = BQ25960_BUSOCP_SC_MAX_uA,
		.busocp_byp_max = BQ25960_BUSOCP_BYP_MAX_uA,

		.busovp_sc_def = BQ25975_BUSOVP_DFLT_uV,
		.busovp_byp_def = BQ25975_BUSOVP_BYPASS_DFLT_uV,
		.busovp_sc_step = BQ25960_BUSOVP_SC_STEP_uV,
		.busovp_sc_offset = BQ25960_BUSOVP_SC_OFFSET_uV,
		.busovp_byp_step = BQ25960_BUSOVP_BYP_STEP_uV,
		.busovp_byp_offset = BQ25960_BUSOVP_BYP_OFFSET_uV,
		.busovp_sc_min = BQ25960_BUSOVP_SC_MIN_uV,
		.busovp_sc_max = BQ25960_BUSOVP_SC_MAX_uV,
		.busovp_byp_min = BQ25960_BUSOVP_BYP_MIN_uV,
		.busovp_byp_max = BQ25960_BUSOVP_BYP_MAX_uV,

		.batovp_def = BQ25960_BATOVP_DFLT_uV,
		.batovp_max = BQ25960_BATOVP_MAX_uV,
		.batovp_min = BQ25960_BATOVP_MIN_uV,
		.batovp_step = BQ25960_BATOVP_STEP_uV,
		.batovp_offset = BQ25960_BATOVP_OFFSET_uV,

		.batocp_def = BQ25960_BATOCP_DFLT_uA,
		.batocp_max = BQ25960_BATOCP_MAX_uA,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bq25980_घातer_supply_init(काष्ठा bq25980_device *bq,
							काष्ठा device *dev)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = bq,
						.of_node = dev->of_node, पूर्ण;

	psy_cfg.supplied_to = bq25980_अक्षरger_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(bq25980_अक्षरger_supplied_to);

	bq->अक्षरger = devm_घातer_supply_रेजिस्टर(bq->dev,
						 &bq25980_घातer_supply_desc,
						 &psy_cfg);
	अगर (IS_ERR(bq->अक्षरger))
		वापस -EINVAL;

	bq->battery = devm_घातer_supply_रेजिस्टर(bq->dev,
						      &bq25980_battery_desc,
						      &psy_cfg);
	अगर (IS_ERR(bq->battery))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक bq25980_hw_init(काष्ठा bq25980_device *bq)
अणु
	काष्ठा घातer_supply_battery_info bat_info = अणु पूर्ण;
	पूर्णांक wd_reg_val = BQ25980_WATCHDOG_DIS;
	पूर्णांक wd_max_val = BQ25980_NUM_WD_VAL - 1;
	पूर्णांक ret = 0;
	पूर्णांक curr_val;
	पूर्णांक volt_val;
	पूर्णांक i;

	अगर (bq->watchकरोg_समयr) अणु
		अगर (bq->watchकरोg_समयr >= bq25980_watchकरोg_समय[wd_max_val])
			wd_reg_val = wd_max_val;
		अन्यथा अणु
			क्रम (i = 0; i < wd_max_val; i++) अणु
				अगर (bq->watchकरोg_समयr > bq25980_watchकरोg_समय[i] &&
				    bq->watchकरोg_समयr < bq25980_watchकरोg_समय[i + 1]) अणु
					wd_reg_val = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ret = regmap_update_bits(bq->regmap, BQ25980_CHRGR_CTRL_3,
				 BQ25980_WATCHDOG_MASK, wd_reg_val);
	अगर (ret)
		वापस ret;

	ret = घातer_supply_get_battery_info(bq->अक्षरger, &bat_info);
	अगर (ret) अणु
		dev_warn(bq->dev, "battery info missing\n");
		वापस -EINVAL;
	पूर्ण

	bq->init_data.ichg_max = bat_info.स्थिरant_अक्षरge_current_max_ua;
	bq->init_data.vreg_max = bat_info.स्थिरant_अक्षरge_voltage_max_uv;

	अगर (bq->state.bypass) अणु
		ret = regmap_update_bits(bq->regmap, BQ25980_CHRGR_CTRL_2,
					BQ25980_EN_BYPASS, BQ25980_EN_BYPASS);
		अगर (ret)
			वापस ret;

		curr_val = bq->init_data.bypass_ilim;
		volt_val = bq->init_data.bypass_vlim;
	पूर्ण अन्यथा अणु
		curr_val = bq->init_data.sc_ilim;
		volt_val = bq->init_data.sc_vlim;
	पूर्ण

	ret = bq25980_set_input_curr_lim(bq, curr_val);
	अगर (ret)
		वापस ret;

	ret = bq25980_set_input_volt_lim(bq, volt_val);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(bq->regmap, BQ25980_ADC_CONTROL1,
				 BQ25980_ADC_EN, BQ25980_ADC_EN);
पूर्ण

अटल पूर्णांक bq25980_parse_dt(काष्ठा bq25980_device *bq)
अणु
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(bq->dev, "ti,watchdog-timeout-ms",
				       &bq->watchकरोg_समयr);
	अगर (ret)
		bq->watchकरोg_समयr = BQ25980_WATCHDOG_MIN;

	अगर (bq->watchकरोg_समयr > BQ25980_WATCHDOG_MAX ||
	    bq->watchकरोg_समयr < BQ25980_WATCHDOG_MIN)
		वापस -EINVAL;

	ret = device_property_पढ़ो_u32(bq->dev,
				       "ti,sc-ovp-limit-microvolt",
				       &bq->init_data.sc_vlim);
	अगर (ret)
		bq->init_data.sc_vlim = bq->chip_info->busovp_sc_def;

	अगर (bq->init_data.sc_vlim > bq->chip_info->busovp_sc_max ||
	    bq->init_data.sc_vlim < bq->chip_info->busovp_sc_min) अणु
		dev_err(bq->dev, "SC ovp limit is out of range\n");
		वापस -EINVAL;
	पूर्ण

	ret = device_property_पढ़ो_u32(bq->dev,
				       "ti,sc-ocp-limit-microamp",
				       &bq->init_data.sc_ilim);
	अगर (ret)
		bq->init_data.sc_ilim = bq->chip_info->busocp_def;

	अगर (bq->init_data.sc_ilim > bq->chip_info->busocp_sc_max ||
	    bq->init_data.sc_ilim < bq->chip_info->busocp_sc_min) अणु
		dev_err(bq->dev, "SC ocp limit is out of range\n");
		वापस -EINVAL;
	पूर्ण

	ret = device_property_पढ़ो_u32(bq->dev,
				       "ti,bypass-ovp-limit-microvolt",
				       &bq->init_data.bypass_vlim);
	अगर (ret)
		bq->init_data.bypass_vlim = bq->chip_info->busovp_byp_def;

	अगर (bq->init_data.bypass_vlim > bq->chip_info->busovp_byp_max ||
	    bq->init_data.bypass_vlim < bq->chip_info->busovp_byp_min) अणु
		dev_err(bq->dev, "Bypass ovp limit is out of range\n");
		वापस -EINVAL;
	पूर्ण

	ret = device_property_पढ़ो_u32(bq->dev,
				       "ti,bypass-ocp-limit-microamp",
				       &bq->init_data.bypass_ilim);
	अगर (ret)
		bq->init_data.bypass_ilim = bq->chip_info->busocp_def;

	अगर (bq->init_data.bypass_ilim > bq->chip_info->busocp_byp_max ||
	    bq->init_data.bypass_ilim < bq->chip_info->busocp_byp_min) अणु
		dev_err(bq->dev, "Bypass ocp limit is out of range\n");
		वापस -EINVAL;
	पूर्ण


	bq->state.bypass = device_property_पढ़ो_bool(bq->dev,
						      "ti,bypass-enable");
	वापस 0;
पूर्ण

अटल पूर्णांक bq25980_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा bq25980_device *bq;
	पूर्णांक ret;

	bq = devm_kzalloc(dev, माप(*bq), GFP_KERNEL);
	अगर (!bq)
		वापस -ENOMEM;

	bq->client = client;
	bq->dev = dev;

	mutex_init(&bq->lock);

	म_नकलन(bq->model_name, id->name, I2C_NAME_SIZE);
	bq->chip_info = &bq25980_chip_info_tbl[id->driver_data];

	bq->regmap = devm_regmap_init_i2c(client,
					  bq->chip_info->regmap_config);
	अगर (IS_ERR(bq->regmap)) अणु
		dev_err(dev, "Failed to allocate register map\n");
		वापस PTR_ERR(bq->regmap);
	पूर्ण

	i2c_set_clientdata(client, bq);

	ret = bq25980_parse_dt(bq);
	अगर (ret) अणु
		dev_err(dev, "Failed to read device tree properties%d\n", ret);
		वापस ret;
	पूर्ण

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						bq25980_irq_handler_thपढ़ो,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						dev_name(&client->dev), bq);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = bq25980_घातer_supply_init(bq, dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register power supply\n");
		वापस ret;
	पूर्ण

	ret = bq25980_hw_init(bq);
	अगर (ret) अणु
		dev_err(dev, "Cannot initialize the chip.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bq25980_i2c_ids[] = अणु
	अणु "bq25980", BQ25980 पूर्ण,
	अणु "bq25975", BQ25975 पूर्ण,
	अणु "bq25960", BQ25960 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq25980_i2c_ids);

अटल स्थिर काष्ठा of_device_id bq25980_of_match[] = अणु
	अणु .compatible = "ti,bq25980", .data = (व्योम *)BQ25980 पूर्ण,
	अणु .compatible = "ti,bq25975", .data = (व्योम *)BQ25975 पूर्ण,
	अणु .compatible = "ti,bq25960", .data = (व्योम *)BQ25960 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bq25980_of_match);

अटल काष्ठा i2c_driver bq25980_driver = अणु
	.driver = अणु
		.name = "bq25980-charger",
		.of_match_table = bq25980_of_match,
	पूर्ण,
	.probe = bq25980_probe,
	.id_table = bq25980_i2c_ids,
पूर्ण;
module_i2c_driver(bq25980_driver);

MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_AUTHOR("Ricardo Rivera-Matos <r-rivera-matos@ti.com>");
MODULE_DESCRIPTION("bq25980 charger driver");
MODULE_LICENSE("GPL v2");
