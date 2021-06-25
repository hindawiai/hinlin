<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mlx90632.c - Melexis MLX90632 contactless IR temperature sensor
 *
 * Copyright (c) 2017 Melexis <cmo@melexis.com>
 *
 * Driver क्रम the Melexis MLX90632 I2C 16-bit IR thermopile sensor
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/math64.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/* Memory sections addresses */
#घोषणा MLX90632_ADDR_RAM	0x4000 /* Start address of ram */
#घोषणा MLX90632_ADDR_EEPROM	0x2480 /* Start address of user eeprom */

/* EEPROM addresses - used at startup */
#घोषणा MLX90632_EE_CTRL	0x24d4 /* Control रेजिस्टर initial value */
#घोषणा MLX90632_EE_I2C_ADDR	0x24d5 /* I2C address रेजिस्टर initial value */
#घोषणा MLX90632_EE_VERSION	0x240b /* EEPROM version reg address */
#घोषणा MLX90632_EE_P_R		0x240c /* P_R calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_P_G		0x240e /* P_G calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_P_T		0x2410 /* P_T calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_P_O		0x2412 /* P_O calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Aa		0x2414 /* Aa calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Ab		0x2416 /* Ab calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Ba		0x2418 /* Ba calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Bb		0x241a /* Bb calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Ca		0x241c /* Ca calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Cb		0x241e /* Cb calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Da		0x2420 /* Da calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Db		0x2422 /* Db calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Ea		0x2424 /* Ea calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Eb		0x2426 /* Eb calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Fa		0x2428 /* Fa calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Fb		0x242a /* Fb calibration रेजिस्टर 32bit */
#घोषणा MLX90632_EE_Ga		0x242c /* Ga calibration रेजिस्टर 32bit */

#घोषणा MLX90632_EE_Gb		0x242e /* Gb calibration रेजिस्टर 16bit */
#घोषणा MLX90632_EE_Ka		0x242f /* Ka calibration रेजिस्टर 16bit */

#घोषणा MLX90632_EE_Ha		0x2481 /* Ha customer calib value reg 16bit */
#घोषणा MLX90632_EE_Hb		0x2482 /* Hb customer calib value reg 16bit */

/* Register addresses - अस्थिर */
#घोषणा MLX90632_REG_I2C_ADDR	0x3000 /* Chip I2C address रेजिस्टर */

/* Control रेजिस्टर address - अस्थिर */
#घोषणा MLX90632_REG_CONTROL	0x3001 /* Control Register address */
#घोषणा   MLX90632_CFG_PWR_MASK		GENMASK(2, 1) /* PowerMode Mask */
#घोषणा   MLX90632_CFG_MTYP_MASK		GENMASK(8, 4) /* Meas select Mask */

/* PowerModes statuses */
#घोषणा MLX90632_PWR_STATUS(ctrl_val) (ctrl_val << 1)
#घोषणा MLX90632_PWR_STATUS_HALT MLX90632_PWR_STATUS(0) /* hold */
#घोषणा MLX90632_PWR_STATUS_SLEEP_STEP MLX90632_PWR_STATUS(1) /* sleep step*/
#घोषणा MLX90632_PWR_STATUS_STEP MLX90632_PWR_STATUS(2) /* step */
#घोषणा MLX90632_PWR_STATUS_CONTINUOUS MLX90632_PWR_STATUS(3) /* continuous*/

/* Measurement types */
#घोषणा MLX90632_MTYP_MEDICAL 0
#घोषणा MLX90632_MTYP_EXTENDED 17

/* Measurement type select*/
#घोषणा MLX90632_MTYP_STATUS(ctrl_val) (ctrl_val << 4)
#घोषणा MLX90632_MTYP_STATUS_MEDICAL MLX90632_MTYP_STATUS(MLX90632_MTYP_MEDICAL)
#घोषणा MLX90632_MTYP_STATUS_EXTENDED MLX90632_MTYP_STATUS(MLX90632_MTYP_EXTENDED)

/* I2C command रेजिस्टर - अस्थिर */
#घोषणा MLX90632_REG_I2C_CMD    0x3005 /* I2C command Register address */

/* Device status रेजिस्टर - अस्थिर */
#घोषणा MLX90632_REG_STATUS	0x3fff /* Device status रेजिस्टर */
#घोषणा   MLX90632_STAT_BUSY		BIT(10) /* Device busy indicator */
#घोषणा   MLX90632_STAT_EE_BUSY		BIT(9) /* EEPROM busy indicator */
#घोषणा   MLX90632_STAT_BRST		BIT(8) /* Brown out reset indicator */
#घोषणा   MLX90632_STAT_CYCLE_POS	GENMASK(6, 2) /* Data position */
#घोषणा   MLX90632_STAT_DATA_RDY	BIT(0) /* Data पढ़ोy indicator */

/* RAM_MEAS address-es क्रम each channel */
#घोषणा MLX90632_RAM_1(meas_num)	(MLX90632_ADDR_RAM + 3 * meas_num)
#घोषणा MLX90632_RAM_2(meas_num)	(MLX90632_ADDR_RAM + 3 * meas_num + 1)
#घोषणा MLX90632_RAM_3(meas_num)	(MLX90632_ADDR_RAM + 3 * meas_num + 2)

/* Name important RAM_MEAS channels */
#घोषणा MLX90632_RAM_DSP5_EXTENDED_AMBIENT_1 MLX90632_RAM_3(17)
#घोषणा MLX90632_RAM_DSP5_EXTENDED_AMBIENT_2 MLX90632_RAM_3(18)
#घोषणा MLX90632_RAM_DSP5_EXTENDED_OBJECT_1 MLX90632_RAM_1(17)
#घोषणा MLX90632_RAM_DSP5_EXTENDED_OBJECT_2 MLX90632_RAM_2(17)
#घोषणा MLX90632_RAM_DSP5_EXTENDED_OBJECT_3 MLX90632_RAM_1(18)
#घोषणा MLX90632_RAM_DSP5_EXTENDED_OBJECT_4 MLX90632_RAM_2(18)
#घोषणा MLX90632_RAM_DSP5_EXTENDED_OBJECT_5 MLX90632_RAM_1(19)
#घोषणा MLX90632_RAM_DSP5_EXTENDED_OBJECT_6 MLX90632_RAM_2(19)

/* Magic स्थिरants */
#घोषणा MLX90632_ID_MEDICAL	0x0105 /* EEPROM DSPv5 Medical device id */
#घोषणा MLX90632_ID_CONSUMER	0x0205 /* EEPROM DSPv5 Consumer device id */
#घोषणा MLX90632_ID_EXTENDED	0x0505 /* EEPROM DSPv5 Extended range device id */
#घोषणा MLX90632_ID_MASK	GENMASK(14, 0) /* DSP version and device ID in EE_VERSION */
#घोषणा MLX90632_DSP_VERSION	5 /* DSP version */
#घोषणा MLX90632_DSP_MASK	GENMASK(7, 0) /* DSP version in EE_VERSION */
#घोषणा MLX90632_RESET_CMD	0x0006 /* Reset sensor (address or global) */
#घोषणा MLX90632_REF_12 	12LL /* ResCtrlRef value of Ch 1 or Ch 2 */
#घोषणा MLX90632_REF_3		12LL /* ResCtrlRef value of Channel 3 */
#घोषणा MLX90632_MAX_MEAS_NUM	31 /* Maximum measurements in list */
#घोषणा MLX90632_SLEEP_DELAY_MS 3000 /* Autosleep delay */
#घोषणा MLX90632_EXTENDED_LIMIT 27000 /* Extended mode raw value limit */

/**
 * काष्ठा mlx90632_data - निजी data क्रम the MLX90632 device
 * @client: I2C client of the device
 * @lock: Internal mutex क्रम multiple पढ़ोs क्रम single measurement
 * @regmap: Regmap of the device
 * @emissivity: Object emissivity from 0 to 1000 where 1000 = 1.
 * @mtyp: Measurement type physical sensor configuration क्रम extended range
 *        calculations
 * @object_ambient_temperature: Ambient temperature at object (might dअगरfer of
 *                              the ambient temperature of sensor.
 */
काष्ठा mlx90632_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;
	u16 emissivity;
	u8 mtyp;
	u32 object_ambient_temperature;
पूर्ण;

अटल स्थिर काष्ठा regmap_range mlx90632_अस्थिर_reg_range[] = अणु
	regmap_reg_range(MLX90632_REG_I2C_ADDR, MLX90632_REG_CONTROL),
	regmap_reg_range(MLX90632_REG_I2C_CMD, MLX90632_REG_I2C_CMD),
	regmap_reg_range(MLX90632_REG_STATUS, MLX90632_REG_STATUS),
	regmap_reg_range(MLX90632_RAM_1(0),
			 MLX90632_RAM_3(MLX90632_MAX_MEAS_NUM)),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mlx90632_अस्थिर_regs_tbl = अणु
	.yes_ranges = mlx90632_अस्थिर_reg_range,
	.n_yes_ranges = ARRAY_SIZE(mlx90632_अस्थिर_reg_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_range mlx90632_पढ़ो_reg_range[] = अणु
	regmap_reg_range(MLX90632_EE_VERSION, MLX90632_EE_Ka),
	regmap_reg_range(MLX90632_EE_CTRL, MLX90632_EE_I2C_ADDR),
	regmap_reg_range(MLX90632_EE_Ha, MLX90632_EE_Hb),
	regmap_reg_range(MLX90632_REG_I2C_ADDR, MLX90632_REG_CONTROL),
	regmap_reg_range(MLX90632_REG_I2C_CMD, MLX90632_REG_I2C_CMD),
	regmap_reg_range(MLX90632_REG_STATUS, MLX90632_REG_STATUS),
	regmap_reg_range(MLX90632_RAM_1(0),
			 MLX90632_RAM_3(MLX90632_MAX_MEAS_NUM)),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mlx90632_पढ़ोable_regs_tbl = अणु
	.yes_ranges = mlx90632_पढ़ो_reg_range,
	.n_yes_ranges = ARRAY_SIZE(mlx90632_पढ़ो_reg_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_range mlx90632_no_ग_लिखो_reg_range[] = अणु
	regmap_reg_range(MLX90632_EE_VERSION, MLX90632_EE_Ka),
	regmap_reg_range(MLX90632_RAM_1(0),
			 MLX90632_RAM_3(MLX90632_MAX_MEAS_NUM)),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mlx90632_ग_लिखोable_regs_tbl = अणु
	.no_ranges = mlx90632_no_ग_लिखो_reg_range,
	.n_no_ranges = ARRAY_SIZE(mlx90632_no_ग_लिखो_reg_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_config mlx90632_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,

	.अस्थिर_table = &mlx90632_अस्थिर_regs_tbl,
	.rd_table = &mlx90632_पढ़ोable_regs_tbl,
	.wr_table = &mlx90632_ग_लिखोable_regs_tbl,

	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल s32 mlx90632_pwr_set_sleep_step(काष्ठा regmap *regmap)
अणु
	वापस regmap_update_bits(regmap, MLX90632_REG_CONTROL,
				  MLX90632_CFG_PWR_MASK,
				  MLX90632_PWR_STATUS_SLEEP_STEP);
पूर्ण

अटल s32 mlx90632_pwr_continuous(काष्ठा regmap *regmap)
अणु
	वापस regmap_update_bits(regmap, MLX90632_REG_CONTROL,
				  MLX90632_CFG_PWR_MASK,
				  MLX90632_PWR_STATUS_CONTINUOUS);
पूर्ण

/**
 * mlx90632_perक्रमm_measurement() - Trigger and retrieve current measurement cycle
 * @data: poपूर्णांकer to mlx90632_data object containing regmap inक्रमmation
 *
 * Perक्रमm a measurement and वापस latest measurement cycle position reported
 * by sensor. This is a blocking function क्रम 500ms, as that is शेष sensor
 * refresh rate.
 */
अटल पूर्णांक mlx90632_perक्रमm_measurement(काष्ठा mlx90632_data *data)
अणु
	अचिन्हित पूर्णांक reg_status;
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, MLX90632_REG_STATUS,
				 MLX90632_STAT_DATA_RDY, 0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो_poll_समयout(data->regmap, MLX90632_REG_STATUS, reg_status,
				       !(reg_status & MLX90632_STAT_DATA_RDY), 10000,
				       100 * 10000);

	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "data not ready");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस (reg_status & MLX90632_STAT_CYCLE_POS) >> 2;
पूर्ण

अटल पूर्णांक mlx90632_set_meas_type(काष्ठा regmap *regmap, u8 type)
अणु
	पूर्णांक ret;

	अगर ((type != MLX90632_MTYP_MEDICAL) && (type != MLX90632_MTYP_EXTENDED))
		वापस -EINVAL;

	ret = regmap_ग_लिखो(regmap, MLX90632_REG_I2C_CMD, MLX90632_RESET_CMD);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Give the mlx90632 some समय to reset properly beक्रमe sending a new I2C command
	 * अगर this is not करोne, the following I2C command(s) will not be accepted.
	 */
	usleep_range(150, 200);

	ret = regmap_ग_लिखो_bits(regmap, MLX90632_REG_CONTROL,
				 (MLX90632_CFG_MTYP_MASK | MLX90632_CFG_PWR_MASK),
				 (MLX90632_MTYP_STATUS(type) | MLX90632_PWR_STATUS_HALT));
	अगर (ret < 0)
		वापस ret;

	वापस mlx90632_pwr_continuous(regmap);
पूर्ण

अटल पूर्णांक mlx90632_channel_new_select(पूर्णांक perक्रमm_ret, uपूर्णांक8_t *channel_new,
				       uपूर्णांक8_t *channel_old)
अणु
	चयन (perक्रमm_ret) अणु
	हाल 1:
		*channel_new = 1;
		*channel_old = 2;
		अवरोध;
	हाल 2:
		*channel_new = 2;
		*channel_old = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx90632_पढ़ो_ambient_raw(काष्ठा regmap *regmap,
				     s16 *ambient_new_raw, s16 *ambient_old_raw)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_3(1), &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	*ambient_new_raw = (s16)पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_3(2), &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	*ambient_old_raw = (s16)पढ़ो_पंचांगp;

	वापस ret;
पूर्ण

अटल पूर्णांक mlx90632_पढ़ो_object_raw(काष्ठा regmap *regmap,
				    पूर्णांक perक्रमm_measurement_ret,
				    s16 *object_new_raw, s16 *object_old_raw)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पढ़ो_पंचांगp;
	s16 पढ़ो;
	u8 channel = 0;
	u8 channel_old = 0;

	ret = mlx90632_channel_new_select(perक्रमm_measurement_ret, &channel,
					  &channel_old);
	अगर (ret != 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_2(channel), &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;

	पढ़ो = (s16)पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_1(channel), &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	*object_new_raw = (पढ़ो + (s16)पढ़ो_पंचांगp) / 2;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_2(channel_old), &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	पढ़ो = (s16)पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_1(channel_old), &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	*object_old_raw = (पढ़ो + (s16)पढ़ो_पंचांगp) / 2;

	वापस ret;
पूर्ण

अटल पूर्णांक mlx90632_पढ़ो_all_channel(काष्ठा mlx90632_data *data,
				     s16 *ambient_new_raw, s16 *ambient_old_raw,
				     s16 *object_new_raw, s16 *object_old_raw)
अणु
	s32 ret, measurement;

	mutex_lock(&data->lock);
	measurement = mlx90632_perक्रमm_measurement(data);
	अगर (measurement < 0) अणु
		ret = measurement;
		जाओ पढ़ो_unlock;
	पूर्ण
	ret = mlx90632_पढ़ो_ambient_raw(data->regmap, ambient_new_raw,
					ambient_old_raw);
	अगर (ret < 0)
		जाओ पढ़ो_unlock;

	ret = mlx90632_पढ़ो_object_raw(data->regmap, measurement,
				       object_new_raw, object_old_raw);
पढ़ो_unlock:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx90632_पढ़ो_ambient_raw_extended(काष्ठा regmap *regmap,
					      s16 *ambient_new_raw, s16 *ambient_old_raw)
अणु
	अचिन्हित पूर्णांक पढ़ो_पंचांगp;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_DSP5_EXTENDED_AMBIENT_1, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	*ambient_new_raw = (s16)पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_DSP5_EXTENDED_AMBIENT_2, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	*ambient_old_raw = (s16)पढ़ो_पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx90632_पढ़ो_object_raw_extended(काष्ठा regmap *regmap, s16 *object_new_raw)
अणु
	अचिन्हित पूर्णांक पढ़ो_पंचांगp;
	s32 पढ़ो;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_DSP5_EXTENDED_OBJECT_1, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	पढ़ो = (s16)पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_DSP5_EXTENDED_OBJECT_2, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	पढ़ो = पढ़ो - (s16)पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_DSP5_EXTENDED_OBJECT_3, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	पढ़ो = पढ़ो - (s16)पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_DSP5_EXTENDED_OBJECT_4, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	पढ़ो = (पढ़ो + (s16)पढ़ो_पंचांगp) / 2;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_DSP5_EXTENDED_OBJECT_5, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	पढ़ो = पढ़ो + (s16)पढ़ो_पंचांगp;

	ret = regmap_पढ़ो(regmap, MLX90632_RAM_DSP5_EXTENDED_OBJECT_6, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	पढ़ो = पढ़ो + (s16)पढ़ो_पंचांगp;

	अगर (पढ़ो > S16_MAX || पढ़ो < S16_MIN)
		वापस -दुस्फल;

	*object_new_raw = पढ़ो;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx90632_पढ़ो_all_channel_extended(काष्ठा mlx90632_data *data, s16 *object_new_raw,
					      s16 *ambient_new_raw, s16 *ambient_old_raw)
अणु
	s32 ret, meas;

	mutex_lock(&data->lock);
	ret = mlx90632_set_meas_type(data->regmap, MLX90632_MTYP_EXTENDED);
	अगर (ret < 0)
		जाओ पढ़ो_unlock;

	ret = पढ़ो_poll_समयout(mlx90632_perक्रमm_measurement, meas, meas == 19,
				50000, 800000, false, data);
	अगर (ret != 0)
		जाओ पढ़ो_unlock;

	ret = mlx90632_पढ़ो_object_raw_extended(data->regmap, object_new_raw);
	अगर (ret < 0)
		जाओ पढ़ो_unlock;

	ret = mlx90632_पढ़ो_ambient_raw_extended(data->regmap, ambient_new_raw, ambient_old_raw);

पढ़ो_unlock:
	(व्योम) mlx90632_set_meas_type(data->regmap, MLX90632_MTYP_MEDICAL);

	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx90632_पढ़ो_ee_रेजिस्टर(काष्ठा regmap *regmap, u16 reg_lsb,
				     s32 *reg_value)
अणु
	s32 ret;
	अचिन्हित पूर्णांक पढ़ो;
	u32 value;

	ret = regmap_पढ़ो(regmap, reg_lsb, &पढ़ो);
	अगर (ret < 0)
		वापस ret;

	value = पढ़ो;

	ret = regmap_पढ़ो(regmap, reg_lsb + 1, &पढ़ो);
	अगर (ret < 0)
		वापस ret;

	*reg_value = (पढ़ो << 16) | (value & 0xffff);

	वापस 0;
पूर्ण

अटल s64 mlx90632_preprocess_temp_amb(s16 ambient_new_raw,
					s16 ambient_old_raw, s16 Gb)
अणु
	s64 VR_Ta, kGb, पंचांगp;

	kGb = ((s64)Gb * 1000LL) >> 10ULL;
	VR_Ta = (s64)ambient_old_raw * 1000000LL +
		kGb * भाग64_s64(((s64)ambient_new_raw * 1000LL),
			(MLX90632_REF_3));
	पंचांगp = भाग64_s64(
			 भाग64_s64(((s64)ambient_new_raw * 1000000000000LL),
				   (MLX90632_REF_3)), VR_Ta);
	वापस भाग64_s64(पंचांगp << 19ULL, 1000LL);
पूर्ण

अटल s64 mlx90632_preprocess_temp_obj(s16 object_new_raw, s16 object_old_raw,
					s16 ambient_new_raw,
					s16 ambient_old_raw, s16 Ka)
अणु
	s64 VR_IR, kKa, पंचांगp;

	kKa = ((s64)Ka * 1000LL) >> 10ULL;
	VR_IR = (s64)ambient_old_raw * 1000000LL +
		kKa * भाग64_s64(((s64)ambient_new_raw * 1000LL),
			(MLX90632_REF_3));
	पंचांगp = भाग64_s64(
			भाग64_s64(((s64)((object_new_raw + object_old_raw) / 2)
				   * 1000000000000LL), (MLX90632_REF_12)),
			VR_IR);
	वापस भाग64_s64((पंचांगp << 19ULL), 1000LL);
पूर्ण

अटल s64 mlx90632_preprocess_temp_obj_extended(s16 object_new_raw, s16 ambient_new_raw,
						 s16 ambient_old_raw, s16 Ka)
अणु
	s64 VR_IR, kKa, पंचांगp;

	kKa = ((s64)Ka * 1000LL) >> 10ULL;
	VR_IR = (s64)ambient_old_raw * 1000000LL +
		kKa * भाग64_s64((s64)ambient_new_raw * 1000LL,
				MLX90632_REF_3);
	पंचांगp = भाग64_s64(
			भाग64_s64((s64) object_new_raw * 1000000000000LL, MLX90632_REF_12),
			VR_IR);
	वापस भाग64_s64(पंचांगp << 19ULL, 1000LL);
पूर्ण

अटल s32 mlx90632_calc_temp_ambient(s16 ambient_new_raw, s16 ambient_old_raw,
				      s32 P_T, s32 P_R, s32 P_G, s32 P_O, s16 Gb)
अणु
	s64 Asub, Bsub, Ablock, Bblock, Cblock, AMB, sum;

	AMB = mlx90632_preprocess_temp_amb(ambient_new_raw, ambient_old_raw,
					   Gb);
	Asub = ((s64)P_T * 10000000000LL) >> 44ULL;
	Bsub = AMB - (((s64)P_R * 1000LL) >> 8ULL);
	Ablock = Asub * (Bsub * Bsub);
	Bblock = (भाग64_s64(Bsub * 10000000LL, P_G)) << 20ULL;
	Cblock = ((s64)P_O * 10000000000LL) >> 8ULL;

	sum = भाग64_s64(Ablock, 1000000LL) + Bblock + Cblock;

	वापस भाग64_s64(sum, 10000000LL);
पूर्ण

अटल s32 mlx90632_calc_temp_object_iteration(s32 prev_object_temp, s64 object,
					       s64 TAdut, s64 TAdut4, s32 Fa, s32 Fb,
					       s32 Ga, s16 Ha, s16 Hb,
					       u16 emissivity)
अणु
	s64 calcedKsTO, calcedKsTA, ir_Alpha, Alpha_corr;
	s64 Ha_customer, Hb_customer;

	Ha_customer = ((s64)Ha * 1000000LL) >> 14ULL;
	Hb_customer = ((s64)Hb * 100) >> 10ULL;

	calcedKsTO = ((s64)((s64)Ga * (prev_object_temp - 25 * 1000LL)
			     * 1000LL)) >> 36LL;
	calcedKsTA = ((s64)(Fb * (TAdut - 25 * 1000000LL))) >> 36LL;
	Alpha_corr = भाग64_s64((((s64)(Fa * 10000000000LL) >> 46LL)
				* Ha_customer), 1000LL);
	Alpha_corr *= ((s64)(1 * 1000000LL + calcedKsTO + calcedKsTA));
	Alpha_corr = emissivity * भाग64_s64(Alpha_corr, 100000LL);
	Alpha_corr = भाग64_s64(Alpha_corr, 1000LL);
	ir_Alpha = भाग64_s64((s64)object * 10000000LL, Alpha_corr);

	वापस (पूर्णांक_वर्ग_मूल64(पूर्णांक_वर्ग_मूल64(ir_Alpha * 1000000000000LL + TAdut4))
		- 27315 - Hb_customer) * 10;
पूर्ण

अटल s64 mlx90632_calc_ta4(s64 TAdut, s64 scale)
अणु
	वापस (भाग64_s64(TAdut, scale) + 27315) *
		(भाग64_s64(TAdut, scale) + 27315) *
		(भाग64_s64(TAdut, scale) + 27315) *
		(भाग64_s64(TAdut, scale) + 27315);
पूर्ण

अटल s32 mlx90632_calc_temp_object(s64 object, s64 ambient, s32 Ea, s32 Eb,
				     s32 Fa, s32 Fb, s32 Ga, s16 Ha, s16 Hb,
				     u16 पंचांगp_emi)
अणु
	s64 kTA, kTA0, TAdut, TAdut4;
	s64 temp = 25000;
	s8 i;

	kTA = (Ea * 1000LL) >> 16LL;
	kTA0 = (Eb * 1000LL) >> 8LL;
	TAdut = भाग64_s64(((ambient - kTA0) * 1000000LL), kTA) + 25 * 1000000LL;
	TAdut4 = mlx90632_calc_ta4(TAdut, 10000LL);

	/* Iterations of calculation as described in datasheet */
	क्रम (i = 0; i < 5; ++i) अणु
		temp = mlx90632_calc_temp_object_iteration(temp, object, TAdut, TAdut4,
							   Fa, Fb, Ga, Ha, Hb,
							   पंचांगp_emi);
	पूर्ण
	वापस temp;
पूर्ण

अटल s32 mlx90632_calc_temp_object_extended(s64 object, s64 ambient, s64 reflected,
					      s32 Ea, s32 Eb, s32 Fa, s32 Fb, s32 Ga,
					      s16 Ha, s16 Hb, u16 पंचांगp_emi)
अणु
	s64 kTA, kTA0, TAdut, TAdut4, Tr4, TaTr4;
	s64 temp = 25000;
	s8 i;

	kTA = (Ea * 1000LL) >> 16LL;
	kTA0 = (Eb * 1000LL) >> 8LL;
	TAdut = भाग64_s64((ambient - kTA0) * 1000000LL, kTA) + 25 * 1000000LL;
	Tr4 = mlx90632_calc_ta4(reflected, 10);
	TAdut4 = mlx90632_calc_ta4(TAdut, 10000LL);
	TaTr4 = Tr4 - भाग64_s64(Tr4 - TAdut4, पंचांगp_emi) * 1000;

	/* Iterations of calculation as described in datasheet */
	क्रम (i = 0; i < 5; ++i) अणु
		temp = mlx90632_calc_temp_object_iteration(temp, object, TAdut, TaTr4,
							   Fa / 2, Fb, Ga, Ha, Hb,
							   पंचांगp_emi);
	पूर्ण

	वापस temp;
पूर्ण

अटल पूर्णांक mlx90632_calc_object_dsp105(काष्ठा mlx90632_data *data, पूर्णांक *val)
अणु
	s32 ret;
	s32 Ea, Eb, Fa, Fb, Ga;
	अचिन्हित पूर्णांक पढ़ो_पंचांगp;
	s16 Ha, Hb, Gb, Ka;
	s16 ambient_new_raw, ambient_old_raw, object_new_raw, object_old_raw;
	s64 object, ambient;

	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_Ea, &Ea);
	अगर (ret < 0)
		वापस ret;
	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_Eb, &Eb);
	अगर (ret < 0)
		वापस ret;
	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_Fa, &Fa);
	अगर (ret < 0)
		वापस ret;
	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_Fb, &Fb);
	अगर (ret < 0)
		वापस ret;
	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_Ga, &Ga);
	अगर (ret < 0)
		वापस ret;
	ret = regmap_पढ़ो(data->regmap, MLX90632_EE_Ha, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	Ha = (s16)पढ़ो_पंचांगp;
	ret = regmap_पढ़ो(data->regmap, MLX90632_EE_Hb, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	Hb = (s16)पढ़ो_पंचांगp;
	ret = regmap_पढ़ो(data->regmap, MLX90632_EE_Gb, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	Gb = (s16)पढ़ो_पंचांगp;
	ret = regmap_पढ़ो(data->regmap, MLX90632_EE_Ka, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	Ka = (s16)पढ़ो_पंचांगp;

	ret = mlx90632_पढ़ो_all_channel(data,
					&ambient_new_raw, &ambient_old_raw,
					&object_new_raw, &object_old_raw);
	अगर (ret < 0)
		वापस ret;

	अगर (object_new_raw > MLX90632_EXTENDED_LIMIT &&
	    data->mtyp == MLX90632_MTYP_EXTENDED) अणु
		ret = mlx90632_पढ़ो_all_channel_extended(data, &object_new_raw,
							 &ambient_new_raw, &ambient_old_raw);
		अगर (ret < 0)
			वापस ret;

		/* Use extended mode calculations */
		ambient = mlx90632_preprocess_temp_amb(ambient_new_raw,
						       ambient_old_raw, Gb);
		object = mlx90632_preprocess_temp_obj_extended(object_new_raw,
							       ambient_new_raw,
							       ambient_old_raw, Ka);
		*val = mlx90632_calc_temp_object_extended(object, ambient,
							  data->object_ambient_temperature,
							  Ea, Eb, Fa, Fb, Ga,
							  Ha, Hb, data->emissivity);
		वापस 0;
	पूर्ण

	ambient = mlx90632_preprocess_temp_amb(ambient_new_raw,
					       ambient_old_raw, Gb);
	object = mlx90632_preprocess_temp_obj(object_new_raw,
					      object_old_raw,
					      ambient_new_raw,
					      ambient_old_raw, Ka);

	*val = mlx90632_calc_temp_object(object, ambient, Ea, Eb, Fa, Fb, Ga,
					 Ha, Hb, data->emissivity);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx90632_calc_ambient_dsp105(काष्ठा mlx90632_data *data, पूर्णांक *val)
अणु
	s32 ret;
	अचिन्हित पूर्णांक पढ़ो_पंचांगp;
	s32 PT, PR, PG, PO;
	s16 Gb;
	s16 ambient_new_raw, ambient_old_raw;

	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_P_R, &PR);
	अगर (ret < 0)
		वापस ret;
	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_P_G, &PG);
	अगर (ret < 0)
		वापस ret;
	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_P_T, &PT);
	अगर (ret < 0)
		वापस ret;
	ret = mlx90632_पढ़ो_ee_रेजिस्टर(data->regmap, MLX90632_EE_P_O, &PO);
	अगर (ret < 0)
		वापस ret;
	ret = regmap_पढ़ो(data->regmap, MLX90632_EE_Gb, &पढ़ो_पंचांगp);
	अगर (ret < 0)
		वापस ret;
	Gb = (s16)पढ़ो_पंचांगp;

	ret = mlx90632_पढ़ो_ambient_raw(data->regmap, &ambient_new_raw,
					&ambient_old_raw);
	अगर (ret < 0)
		वापस ret;
	*val = mlx90632_calc_temp_ambient(ambient_new_raw, ambient_old_raw,
					  PT, PR, PG, PO, Gb);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx90632_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mlx90632_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (channel->channel2) अणु
		हाल IIO_MOD_TEMP_AMBIENT:
			ret = mlx90632_calc_ambient_dsp105(data, val);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT;
		हाल IIO_MOD_TEMP_OBJECT:
			ret = mlx90632_calc_object_dsp105(data, val);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_CALIBEMISSIVITY:
		अगर (data->emissivity == 1000) अणु
			*val = 1;
			*val2 = 0;
		पूर्ण अन्यथा अणु
			*val = 0;
			*val2 = data->emissivity * 1000;
		पूर्ण
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_CALIBAMBIENT:
		*val = data->object_ambient_temperature;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx90632_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक val,
			      पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mlx90632_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBEMISSIVITY:
		/* Confirm we are within 0 and 1.0 */
		अगर (val < 0 || val2 < 0 || val > 1 ||
		    (val == 1 && val2 != 0))
			वापस -EINVAL;
		data->emissivity = val * 1000 + val2 / 1000;
		वापस 0;
	हाल IIO_CHAN_INFO_CALIBAMBIENT:
		data->object_ambient_temperature = val;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mlx90632_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.modअगरied = 1,
		.channel2 = IIO_MOD_TEMP_AMBIENT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.modअगरied = 1,
		.channel2 = IIO_MOD_TEMP_OBJECT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
			BIT(IIO_CHAN_INFO_CALIBEMISSIVITY) | BIT(IIO_CHAN_INFO_CALIBAMBIENT),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info mlx90632_info = अणु
	.पढ़ो_raw = mlx90632_पढ़ो_raw,
	.ग_लिखो_raw = mlx90632_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक mlx90632_sleep(काष्ठा mlx90632_data *data)
अणु
	regcache_mark_dirty(data->regmap);

	dev_dbg(&data->client->dev, "Requesting sleep");
	वापस mlx90632_pwr_set_sleep_step(data->regmap);
पूर्ण

अटल पूर्णांक mlx90632_wakeup(काष्ठा mlx90632_data *data)
अणु
	पूर्णांक ret;

	ret = regcache_sync(data->regmap);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"Failed to sync regmap registers: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_dbg(&data->client->dev, "Requesting wake-up\n");
	वापस mlx90632_pwr_continuous(data->regmap);
पूर्ण

अटल पूर्णांक mlx90632_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mlx90632_data *mlx90632;
	काष्ठा regmap *regmap;
	पूर्णांक ret;
	अचिन्हित पूर्णांक पढ़ो;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*mlx90632));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "Failed to allocate device\n");
		वापस -ENOMEM;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, &mlx90632_regmap);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	mlx90632 = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	mlx90632->client = client;
	mlx90632->regmap = regmap;
	mlx90632->mtyp = MLX90632_MTYP_MEDICAL;

	mutex_init(&mlx90632->lock);
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mlx90632_info;
	indio_dev->channels = mlx90632_channels;
	indio_dev->num_channels = ARRAY_SIZE(mlx90632_channels);

	ret = mlx90632_wakeup(mlx90632);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Wakeup failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(mlx90632->regmap, MLX90632_EE_VERSION, &पढ़ो);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "read of version failed: %d\n", ret);
		वापस ret;
	पूर्ण
	पढ़ो = पढ़ो & MLX90632_ID_MASK;
	अगर (पढ़ो == MLX90632_ID_MEDICAL) अणु
		dev_dbg(&client->dev,
			"Detected Medical EEPROM calibration %x\n", पढ़ो);
	पूर्ण अन्यथा अगर (पढ़ो == MLX90632_ID_CONSUMER) अणु
		dev_dbg(&client->dev,
			"Detected Consumer EEPROM calibration %x\n", पढ़ो);
	पूर्ण अन्यथा अगर (पढ़ो == MLX90632_ID_EXTENDED) अणु
		dev_dbg(&client->dev,
			"Detected Extended range EEPROM calibration %x\n", पढ़ो);
		mlx90632->mtyp = MLX90632_MTYP_EXTENDED;
	पूर्ण अन्यथा अगर ((पढ़ो & MLX90632_DSP_MASK) == MLX90632_DSP_VERSION) अणु
		dev_dbg(&client->dev,
			"Detected Unknown EEPROM calibration %x\n", पढ़ो);
	पूर्ण अन्यथा अणु
		dev_err(&client->dev,
			"Wrong DSP version %x (expected %x)\n",
			पढ़ो, MLX90632_DSP_VERSION);
		वापस -EPROTONOSUPPORT;
	पूर्ण

	mlx90632->emissivity = 1000;
	mlx90632->object_ambient_temperature = 25000; /* 25 degrees milliCelsius */

	pm_runसमय_disable(&client->dev);
	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0) अणु
		mlx90632_sleep(mlx90632);
		वापस ret;
	पूर्ण
	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, MLX90632_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक mlx90632_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा mlx90632_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	mlx90632_sleep(data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mlx90632_id[] = अणु
	अणु "mlx90632", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mlx90632_id);

अटल स्थिर काष्ठा of_device_id mlx90632_of_match[] = अणु
	अणु .compatible = "melexis,mlx90632" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mlx90632_of_match);

अटल पूर्णांक __maybe_unused mlx90632_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mlx90632_data *data = iio_priv(indio_dev);

	वापस mlx90632_sleep(data);
पूर्ण

अटल पूर्णांक __maybe_unused mlx90632_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mlx90632_data *data = iio_priv(indio_dev);

	वापस mlx90632_wakeup(data);
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(mlx90632_pm_ops, mlx90632_pm_suspend,
			    mlx90632_pm_resume, शून्य);

अटल काष्ठा i2c_driver mlx90632_driver = अणु
	.driver = अणु
		.name	= "mlx90632",
		.of_match_table = mlx90632_of_match,
		.pm	= &mlx90632_pm_ops,
	पूर्ण,
	.probe = mlx90632_probe,
	.हटाओ = mlx90632_हटाओ,
	.id_table = mlx90632_id,
पूर्ण;
module_i2c_driver(mlx90632_driver);

MODULE_AUTHOR("Crt Mori <cmo@melexis.com>");
MODULE_DESCRIPTION("Melexis MLX90632 contactless Infra Red temperature sensor driver");
MODULE_LICENSE("GPL v2");
