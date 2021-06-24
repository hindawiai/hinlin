<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Bosch BME680 - Temperature, Pressure, Humidity & Gas Sensor
 *
 * Copyright (C) 2017 - 2018 Bosch Sensortec GmbH
 * Copyright (C) 2018 Himanshu Jha <himanshujha199640@gmail.com>
 *
 * Datasheet:
 * https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME680-DS001-00.pdf
 */
#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/log2.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश "bme680.h"

काष्ठा bme680_calib अणु
	u16 par_t1;
	s16 par_t2;
	s8  par_t3;
	u16 par_p1;
	s16 par_p2;
	s8  par_p3;
	s16 par_p4;
	s16 par_p5;
	s8  par_p6;
	s8  par_p7;
	s16 par_p8;
	s16 par_p9;
	u8  par_p10;
	u16 par_h1;
	u16 par_h2;
	s8  par_h3;
	s8  par_h4;
	s8  par_h5;
	s8  par_h6;
	s8  par_h7;
	s8  par_gh1;
	s16 par_gh2;
	s8  par_gh3;
	u8  res_heat_range;
	s8  res_heat_val;
	s8  range_sw_err;
पूर्ण;

काष्ठा bme680_data अणु
	काष्ठा regmap *regmap;
	काष्ठा bme680_calib bme680;
	u8 oversampling_temp;
	u8 oversampling_press;
	u8 oversampling_humid;
	u16 heater_dur;
	u16 heater_temp;
	/*
	 * Carryover value from temperature conversion, used in pressure
	 * and humidity compensation calculations.
	 */
	s32 t_fine;
पूर्ण;

अटल स्थिर काष्ठा regmap_range bme680_अस्थिर_ranges[] = अणु
	regmap_reg_range(BME680_REG_MEAS_STAT_0, BME680_REG_GAS_R_LSB),
	regmap_reg_range(BME680_REG_STATUS, BME680_REG_STATUS),
	regmap_reg_range(BME680_T2_LSB_REG, BME680_GH3_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bme680_अस्थिर_table = अणु
	.yes_ranges	= bme680_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(bme680_अस्थिर_ranges),
पूर्ण;

स्थिर काष्ठा regmap_config bme680_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xef,
	.अस्थिर_table = &bme680_अस्थिर_table,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL(bme680_regmap_config);

अटल स्थिर काष्ठा iio_chan_spec bme680_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण,
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण,
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण,
	अणु
		.type = IIO_RESISTANCE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
पूर्ण;

अटल पूर्णांक bme680_पढ़ो_calib(काष्ठा bme680_data *data,
			     काष्ठा bme680_calib *calib)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	अचिन्हित पूर्णांक पंचांगp, पंचांगp_msb, पंचांगp_lsb;
	पूर्णांक ret;
	__le16 buf;

	/* Temperature related coefficients */
	ret = regmap_bulk_पढ़ो(data->regmap, BME680_T1_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_T1_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_t1 = le16_to_cpu(buf);

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_T2_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_T2_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_t2 = le16_to_cpu(buf);

	ret = regmap_पढ़ो(data->regmap, BME680_T3_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_T3_REG\n");
		वापस ret;
	पूर्ण
	calib->par_t3 = पंचांगp;

	/* Pressure related coefficients */
	ret = regmap_bulk_पढ़ो(data->regmap, BME680_P1_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P1_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p1 = le16_to_cpu(buf);

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_P2_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P2_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p2 = le16_to_cpu(buf);

	ret = regmap_पढ़ो(data->regmap, BME680_P3_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P3_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p3 = पंचांगp;

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_P4_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P4_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p4 = le16_to_cpu(buf);

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_P5_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P5_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p5 = le16_to_cpu(buf);

	ret = regmap_पढ़ो(data->regmap, BME680_P6_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P6_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p6 = पंचांगp;

	ret = regmap_पढ़ो(data->regmap, BME680_P7_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P7_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p7 = पंचांगp;

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_P8_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P8_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p8 = le16_to_cpu(buf);

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_P9_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P9_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p9 = le16_to_cpu(buf);

	ret = regmap_पढ़ो(data->regmap, BME680_P10_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_P10_REG\n");
		वापस ret;
	पूर्ण
	calib->par_p10 = पंचांगp;

	/* Humidity related coefficients */
	ret = regmap_पढ़ो(data->regmap, BME680_H1_MSB_REG, &पंचांगp_msb);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H1_MSB_REG\n");
		वापस ret;
	पूर्ण
	ret = regmap_पढ़ो(data->regmap, BME680_H1_LSB_REG, &पंचांगp_lsb);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H1_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_h1 = (पंचांगp_msb << BME680_HUM_REG_SHIFT_VAL) |
			(पंचांगp_lsb & BME680_BIT_H1_DATA_MASK);

	ret = regmap_पढ़ो(data->regmap, BME680_H2_MSB_REG, &पंचांगp_msb);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H2_MSB_REG\n");
		वापस ret;
	पूर्ण
	ret = regmap_पढ़ो(data->regmap, BME680_H2_LSB_REG, &पंचांगp_lsb);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H2_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_h2 = (पंचांगp_msb << BME680_HUM_REG_SHIFT_VAL) |
			(पंचांगp_lsb >> BME680_HUM_REG_SHIFT_VAL);

	ret = regmap_पढ़ो(data->regmap, BME680_H3_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H3_REG\n");
		वापस ret;
	पूर्ण
	calib->par_h3 = पंचांगp;

	ret = regmap_पढ़ो(data->regmap, BME680_H4_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H4_REG\n");
		वापस ret;
	पूर्ण
	calib->par_h4 = पंचांगp;

	ret = regmap_पढ़ो(data->regmap, BME680_H5_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H5_REG\n");
		वापस ret;
	पूर्ण
	calib->par_h5 = पंचांगp;

	ret = regmap_पढ़ो(data->regmap, BME680_H6_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H6_REG\n");
		वापस ret;
	पूर्ण
	calib->par_h6 = पंचांगp;

	ret = regmap_पढ़ो(data->regmap, BME680_H7_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_H7_REG\n");
		वापस ret;
	पूर्ण
	calib->par_h7 = पंचांगp;

	/* Gas heater related coefficients */
	ret = regmap_पढ़ो(data->regmap, BME680_GH1_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_GH1_REG\n");
		वापस ret;
	पूर्ण
	calib->par_gh1 = पंचांगp;

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_GH2_LSB_REG,
			       &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_GH2_LSB_REG\n");
		वापस ret;
	पूर्ण
	calib->par_gh2 = le16_to_cpu(buf);

	ret = regmap_पढ़ो(data->regmap, BME680_GH3_REG, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read BME680_GH3_REG\n");
		वापस ret;
	पूर्ण
	calib->par_gh3 = पंचांगp;

	/* Other coefficients */
	ret = regmap_पढ़ो(data->regmap, BME680_REG_RES_HEAT_RANGE, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read resistance heat range\n");
		वापस ret;
	पूर्ण
	calib->res_heat_range = FIELD_GET(BME680_RHRANGE_MASK, पंचांगp);

	ret = regmap_पढ़ो(data->regmap, BME680_REG_RES_HEAT_VAL, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read resistance heat value\n");
		वापस ret;
	पूर्ण
	calib->res_heat_val = पंचांगp;

	ret = regmap_पढ़ो(data->regmap, BME680_REG_RANGE_SW_ERR, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read range software error\n");
		वापस ret;
	पूर्ण
	calib->range_sw_err = FIELD_GET(BME680_RSERROR_MASK, पंचांगp);

	वापस 0;
पूर्ण

/*
 * Taken from Bosch BME680 API:
 * https://github.com/BoschSensortec/BME680_driver/blob/63bb5336/bme680.c#L876
 *
 * Returns temperature measurement in DegC, resolutions is 0.01 DegC. Thereक्रमe,
 * output value of "3233" represents 32.33 DegC.
 */
अटल s16 bme680_compensate_temp(काष्ठा bme680_data *data,
				  s32 adc_temp)
अणु
	काष्ठा bme680_calib *calib = &data->bme680;
	s64 var1, var2, var3;
	s16 calc_temp;

	/* If the calibration is invalid, attempt to reload it */
	अगर (!calib->par_t2)
		bme680_पढ़ो_calib(data, calib);

	var1 = (adc_temp >> 3) - (calib->par_t1 << 1);
	var2 = (var1 * calib->par_t2) >> 11;
	var3 = ((var1 >> 1) * (var1 >> 1)) >> 12;
	var3 = (var3 * (calib->par_t3 << 4)) >> 14;
	data->t_fine = var2 + var3;
	calc_temp = (data->t_fine * 5 + 128) >> 8;

	वापस calc_temp;
पूर्ण

/*
 * Taken from Bosch BME680 API:
 * https://github.com/BoschSensortec/BME680_driver/blob/63bb5336/bme680.c#L896
 *
 * Returns pressure measurement in Pa. Output value of "97356" represents
 * 97356 Pa = 973.56 hPa.
 */
अटल u32 bme680_compensate_press(काष्ठा bme680_data *data,
				   u32 adc_press)
अणु
	काष्ठा bme680_calib *calib = &data->bme680;
	s32 var1, var2, var3, press_comp;

	var1 = (data->t_fine >> 1) - 64000;
	var2 = ((((var1 >> 2) * (var1 >> 2)) >> 11) * calib->par_p6) >> 2;
	var2 = var2 + (var1 * calib->par_p5 << 1);
	var2 = (var2 >> 2) + (calib->par_p4 << 16);
	var1 = (((((var1 >> 2) * (var1 >> 2)) >> 13) *
			(calib->par_p3 << 5)) >> 3) +
			((calib->par_p2 * var1) >> 1);
	var1 = var1 >> 18;
	var1 = ((32768 + var1) * calib->par_p1) >> 15;
	press_comp = 1048576 - adc_press;
	press_comp = ((press_comp - (var2 >> 12)) * 3125);

	अगर (press_comp >= BME680_MAX_OVERFLOW_VAL)
		press_comp = ((press_comp / (u32)var1) << 1);
	अन्यथा
		press_comp = ((press_comp << 1) / (u32)var1);

	var1 = (calib->par_p9 * (((press_comp >> 3) *
			(press_comp >> 3)) >> 13)) >> 12;
	var2 = ((press_comp >> 2) * calib->par_p8) >> 13;
	var3 = ((press_comp >> 8) * (press_comp >> 8) *
			(press_comp >> 8) * calib->par_p10) >> 17;

	press_comp += (var1 + var2 + var3 + (calib->par_p7 << 7)) >> 4;

	वापस press_comp;
पूर्ण

/*
 * Taken from Bosch BME680 API:
 * https://github.com/BoschSensortec/BME680_driver/blob/63bb5336/bme680.c#L937
 *
 * Returns humidity measurement in percent, resolution is 0.001 percent. Output
 * value of "43215" represents 43.215 %rH.
 */
अटल u32 bme680_compensate_humid(काष्ठा bme680_data *data,
				   u16 adc_humid)
अणु
	काष्ठा bme680_calib *calib = &data->bme680;
	s32 var1, var2, var3, var4, var5, var6, temp_scaled, calc_hum;

	temp_scaled = (data->t_fine * 5 + 128) >> 8;
	var1 = (adc_humid - ((s32) ((s32) calib->par_h1 * 16))) -
		(((temp_scaled * (s32) calib->par_h3) / 100) >> 1);
	var2 = ((s32) calib->par_h2 *
		(((temp_scaled * calib->par_h4) / 100) +
		 (((temp_scaled * ((temp_scaled * calib->par_h5) / 100))
		   >> 6) / 100) + (1 << 14))) >> 10;
	var3 = var1 * var2;
	var4 = calib->par_h6 << 7;
	var4 = (var4 + ((temp_scaled * calib->par_h7) / 100)) >> 4;
	var5 = ((var3 >> 14) * (var3 >> 14)) >> 10;
	var6 = (var4 * var5) >> 1;
	calc_hum = (((var3 + var6) >> 10) * 1000) >> 12;

	calc_hum = clamp(calc_hum, 0, 100000); /* clamp between 0-100 %rH */

	वापस calc_hum;
पूर्ण

/*
 * Taken from Bosch BME680 API:
 * https://github.com/BoschSensortec/BME680_driver/blob/63bb5336/bme680.c#L973
 *
 * Returns gas measurement in Ohm. Output value of "82986" represent 82986 ohms.
 */
अटल u32 bme680_compensate_gas(काष्ठा bme680_data *data, u16 gas_res_adc,
				 u8 gas_range)
अणु
	काष्ठा bme680_calib *calib = &data->bme680;
	s64 var1;
	u64 var2;
	s64 var3;
	u32 calc_gas_res;

	/* Look up table क्रम the possible gas range values */
	स्थिर u32 lookupTable[16] = अणु2147483647u, 2147483647u,
				2147483647u, 2147483647u, 2147483647u,
				2126008810u, 2147483647u, 2130303777u,
				2147483647u, 2147483647u, 2143188679u,
				2136746228u, 2147483647u, 2126008810u,
				2147483647u, 2147483647uपूर्ण;

	var1 = ((1340 + (5 * (s64) calib->range_sw_err)) *
			((s64) lookupTable[gas_range])) >> 16;
	var2 = ((gas_res_adc << 15) - 16777216) + var1;
	var3 = ((125000 << (15 - gas_range)) * var1) >> 9;
	var3 += (var2 >> 1);
	calc_gas_res = भाग64_s64(var3, (s64) var2);

	वापस calc_gas_res;
पूर्ण

/*
 * Taken from Bosch BME680 API:
 * https://github.com/BoschSensortec/BME680_driver/blob/63bb5336/bme680.c#L1002
 */
अटल u8 bme680_calc_heater_res(काष्ठा bme680_data *data, u16 temp)
अणु
	काष्ठा bme680_calib *calib = &data->bme680;
	s32 var1, var2, var3, var4, var5, heatr_res_x100;
	u8 heatr_res;

	अगर (temp > 400) /* Cap temperature */
		temp = 400;

	var1 = (((s32) BME680_AMB_TEMP * calib->par_gh3) / 1000) * 256;
	var2 = (calib->par_gh1 + 784) * (((((calib->par_gh2 + 154009) *
						temp * 5) / 100)
						+ 3276800) / 10);
	var3 = var1 + (var2 / 2);
	var4 = (var3 / (calib->res_heat_range + 4));
	var5 = 131 * calib->res_heat_val + 65536;
	heatr_res_x100 = ((var4 / var5) - 250) * 34;
	heatr_res = DIV_ROUND_CLOSEST(heatr_res_x100, 100);

	वापस heatr_res;
पूर्ण

/*
 * Taken from Bosch BME680 API:
 * https://github.com/BoschSensortec/BME680_driver/blob/63bb5336/bme680.c#L1188
 */
अटल u8 bme680_calc_heater_dur(u16 dur)
अणु
	u8 durval, factor = 0;

	अगर (dur >= 0xfc0) अणु
		durval = 0xff; /* Max duration */
	पूर्ण अन्यथा अणु
		जबतक (dur > 0x3F) अणु
			dur = dur / 4;
			factor += 1;
		पूर्ण
		durval = dur + (factor * 64);
	पूर्ण

	वापस durval;
पूर्ण

अटल पूर्णांक bme680_set_mode(काष्ठा bme680_data *data, bool mode)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	अगर (mode) अणु
		ret = regmap_ग_लिखो_bits(data->regmap, BME680_REG_CTRL_MEAS,
					BME680_MODE_MASK, BME680_MODE_FORCED);
		अगर (ret < 0)
			dev_err(dev, "failed to set forced mode\n");

	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो_bits(data->regmap, BME680_REG_CTRL_MEAS,
					BME680_MODE_MASK, BME680_MODE_SLEEP);
		अगर (ret < 0)
			dev_err(dev, "failed to set sleep mode\n");

	पूर्ण

	वापस ret;
पूर्ण

अटल u8 bme680_oversampling_to_reg(u8 val)
अणु
	वापस ilog2(val) + 1;
पूर्ण

अटल पूर्णांक bme680_chip_config(काष्ठा bme680_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	u8 osrs;

	osrs = FIELD_PREP(
		BME680_OSRS_HUMIDITY_MASK,
		bme680_oversampling_to_reg(data->oversampling_humid));
	/*
	 * Highly recommended to set oversampling of humidity beक्रमe
	 * temperature/pressure oversampling.
	 */
	ret = regmap_update_bits(data->regmap, BME680_REG_CTRL_HUMIDITY,
				 BME680_OSRS_HUMIDITY_MASK, osrs);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to write ctrl_hum register\n");
		वापस ret;
	पूर्ण

	/* IIR filter settings */
	ret = regmap_update_bits(data->regmap, BME680_REG_CONFIG,
				 BME680_FILTER_MASK,
				 BME680_FILTER_COEFF_VAL);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to write config register\n");
		वापस ret;
	पूर्ण

	osrs = FIELD_PREP(BME680_OSRS_TEMP_MASK,
			  bme680_oversampling_to_reg(data->oversampling_temp)) |
	       FIELD_PREP(BME680_OSRS_PRESS_MASK,
			  bme680_oversampling_to_reg(data->oversampling_press));
	ret = regmap_ग_लिखो_bits(data->regmap, BME680_REG_CTRL_MEAS,
				BME680_OSRS_TEMP_MASK | BME680_OSRS_PRESS_MASK,
				osrs);
	अगर (ret < 0)
		dev_err(dev, "failed to write ctrl_meas register\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bme680_gas_config(काष्ठा bme680_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	u8 heatr_res, heatr_dur;

	heatr_res = bme680_calc_heater_res(data, data->heater_temp);

	/* set target heater temperature */
	ret = regmap_ग_लिखो(data->regmap, BME680_REG_RES_HEAT_0, heatr_res);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to write res_heat_0 register\n");
		वापस ret;
	पूर्ण

	heatr_dur = bme680_calc_heater_dur(data->heater_dur);

	/* set target heating duration */
	ret = regmap_ग_लिखो(data->regmap, BME680_REG_GAS_WAIT_0, heatr_dur);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to write gas_wait_0 register\n");
		वापस ret;
	पूर्ण

	/* Enable the gas sensor and select heater profile set-poपूर्णांक 0 */
	ret = regmap_update_bits(data->regmap, BME680_REG_CTRL_GAS_1,
				 BME680_RUN_GAS_MASK | BME680_NB_CONV_MASK,
				 FIELD_PREP(BME680_RUN_GAS_MASK, 1) |
				 FIELD_PREP(BME680_NB_CONV_MASK, 0));
	अगर (ret < 0)
		dev_err(dev, "failed to write ctrl_gas_1 register\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bme680_पढ़ो_temp(काष्ठा bme680_data *data, पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	__be32 पंचांगp = 0;
	s32 adc_temp;
	s16 comp_temp;

	/* set क्रमced mode to trigger measurement */
	ret = bme680_set_mode(data, true);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_REG_TEMP_MSB,
			       &पंचांगp, 3);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read temperature\n");
		वापस ret;
	पूर्ण

	adc_temp = be32_to_cpu(पंचांगp) >> 12;
	अगर (adc_temp == BME680_MEAS_SKIPPED) अणु
		/* पढ़ोing was skipped */
		dev_err(dev, "reading temperature skipped\n");
		वापस -EINVAL;
	पूर्ण
	comp_temp = bme680_compensate_temp(data, adc_temp);
	/*
	 * val might be शून्य अगर we're called by the पढ़ो_press/पढ़ो_humid
	 * routine which is callled to get t_fine value used in
	 * compensate_press/compensate_humid to get compensated
	 * pressure/humidity पढ़ोings.
	 */
	अगर (val) अणु
		*val = comp_temp * 10; /* Centidegrees to millidegrees */
		वापस IIO_VAL_INT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bme680_पढ़ो_press(काष्ठा bme680_data *data,
			     पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	__be32 पंचांगp = 0;
	s32 adc_press;

	/* Read and compensate temperature to get a पढ़ोing of t_fine */
	ret = bme680_पढ़ो_temp(data, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_REG_PRESS_MSB,
			       &पंचांगp, 3);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read pressure\n");
		वापस ret;
	पूर्ण

	adc_press = be32_to_cpu(पंचांगp) >> 12;
	अगर (adc_press == BME680_MEAS_SKIPPED) अणु
		/* पढ़ोing was skipped */
		dev_err(dev, "reading pressure skipped\n");
		वापस -EINVAL;
	पूर्ण

	*val = bme680_compensate_press(data, adc_press);
	*val2 = 100;
	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल पूर्णांक bme680_पढ़ो_humid(काष्ठा bme680_data *data,
			     पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	__be16 पंचांगp = 0;
	s32 adc_humidity;
	u32 comp_humidity;

	/* Read and compensate temperature to get a पढ़ोing of t_fine */
	ret = bme680_पढ़ो_temp(data, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, BM6880_REG_HUMIDITY_MSB,
			       &पंचांगp, माप(पंचांगp));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read humidity\n");
		वापस ret;
	पूर्ण

	adc_humidity = be16_to_cpu(पंचांगp);
	अगर (adc_humidity == BME680_MEAS_SKIPPED) अणु
		/* पढ़ोing was skipped */
		dev_err(dev, "reading humidity skipped\n");
		वापस -EINVAL;
	पूर्ण
	comp_humidity = bme680_compensate_humid(data, adc_humidity);

	*val = comp_humidity;
	*val2 = 1000;
	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल पूर्णांक bme680_पढ़ो_gas(काष्ठा bme680_data *data,
			   पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	__be16 पंचांगp = 0;
	अचिन्हित पूर्णांक check;
	u16 adc_gas_res;
	u8 gas_range;

	/* Set heater settings */
	ret = bme680_gas_config(data);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set gas config\n");
		वापस ret;
	पूर्ण

	/* set क्रमced mode to trigger measurement */
	ret = bme680_set_mode(data, true);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(data->regmap, BME680_REG_MEAS_STAT_0, &check);
	अगर (check & BME680_GAS_MEAS_BIT) अणु
		dev_err(dev, "gas measurement incomplete\n");
		वापस -EBUSY;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, BME680_REG_GAS_R_LSB, &check);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read gas_r_lsb register\n");
		वापस ret;
	पूर्ण

	/*
	 * occurs अगर either the gas heating duration was insuffient
	 * to reach the target heater temperature or the target
	 * heater temperature was too high क्रम the heater sink to
	 * reach.
	 */
	अगर ((check & BME680_GAS_STAB_BIT) == 0) अणु
		dev_err(dev, "heater failed to reach the target temperature\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_bulk_पढ़ो(data->regmap, BME680_REG_GAS_MSB,
			       &पंचांगp, माप(पंचांगp));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read gas resistance\n");
		वापस ret;
	पूर्ण

	gas_range = check & BME680_GAS_RANGE_MASK;
	adc_gas_res = be16_to_cpu(पंचांगp) >> BME680_ADC_GAS_RES_SHIFT;

	*val = bme680_compensate_gas(data, adc_gas_res, gas_range);
	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bme680_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा bme680_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			वापस bme680_पढ़ो_temp(data, val);
		हाल IIO_PRESSURE:
			वापस bme680_पढ़ो_press(data, val, val2);
		हाल IIO_HUMIDITYRELATIVE:
			वापस bme680_पढ़ो_humid(data, val, val2);
		हाल IIO_RESISTANCE:
			वापस bme680_पढ़ो_gas(data, val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = data->oversampling_temp;
			वापस IIO_VAL_INT;
		हाल IIO_PRESSURE:
			*val = data->oversampling_press;
			वापस IIO_VAL_INT;
		हाल IIO_HUMIDITYRELATIVE:
			*val = data->oversampling_humid;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल bool bme680_is_valid_oversampling(पूर्णांक rate)
अणु
	वापस (rate > 0 && rate <= 16 && is_घातer_of_2(rate));
पूर्ण

अटल पूर्णांक bme680_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा bme680_data *data = iio_priv(indio_dev);

	अगर (val2 != 0)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
	अणु
		अगर (!bme680_is_valid_oversampling(val))
			वापस -EINVAL;

		चयन (chan->type) अणु
		हाल IIO_TEMP:
			data->oversampling_temp = val;
			अवरोध;
		हाल IIO_PRESSURE:
			data->oversampling_press = val;
			अवरोध;
		हाल IIO_HUMIDITYRELATIVE:
			data->oversampling_humid = val;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		वापस bme680_chip_config(data);
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर bme680_oversampling_ratio_show[] = "1 2 4 8 16";

अटल IIO_CONST_ATTR(oversampling_ratio_available,
		      bme680_oversampling_ratio_show);

अटल काष्ठा attribute *bme680_attributes[] = अणु
	&iio_स्थिर_attr_oversampling_ratio_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bme680_attribute_group = अणु
	.attrs = bme680_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info bme680_info = अणु
	.पढ़ो_raw = &bme680_पढ़ो_raw,
	.ग_लिखो_raw = &bme680_ग_लिखो_raw,
	.attrs = &bme680_attribute_group,
पूर्ण;

अटल स्थिर अक्षर *bme680_match_acpi_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;

	वापस dev_name(dev);
पूर्ण

पूर्णांक bme680_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		      स्थिर अक्षर *name)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा bme680_data *data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, BME680_REG_SOFT_RESET,
			   BME680_CMD_SOFTRESET);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to reset chip\n");
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(regmap, BME680_REG_CHIP_ID, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading chip ID\n");
		वापस ret;
	पूर्ण

	अगर (val != BME680_CHIP_ID_VAL) अणु
		dev_err(dev, "Wrong chip ID, got %x expected %x\n",
				val, BME680_CHIP_ID_VAL);
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	अगर (!name && ACPI_HANDLE(dev))
		name = bme680_match_acpi_device(dev);

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;
	indio_dev->name = name;
	indio_dev->channels = bme680_channels;
	indio_dev->num_channels = ARRAY_SIZE(bme680_channels);
	indio_dev->info = &bme680_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	/* शेष values क्रम the sensor */
	data->oversampling_humid = 2; /* 2X oversampling rate */
	data->oversampling_press = 4; /* 4X oversampling rate */
	data->oversampling_temp = 8;  /* 8X oversampling rate */
	data->heater_temp = 320; /* degree Celsius */
	data->heater_dur = 150;  /* milliseconds */

	ret = bme680_chip_config(data);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set chip_config data\n");
		वापस ret;
	पूर्ण

	ret = bme680_gas_config(data);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set gas config data\n");
		वापस ret;
	पूर्ण

	ret = bme680_पढ़ो_calib(data, &data->bme680);
	अगर (ret < 0) अणु
		dev_err(dev,
			"failed to read calibration coefficients at probe\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(bme680_core_probe);

MODULE_AUTHOR("Himanshu Jha <himanshujha199640@gmail.com>");
MODULE_DESCRIPTION("Bosch BME680 Driver");
MODULE_LICENSE("GPL v2");
