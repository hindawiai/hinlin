<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 TDK-InvenSense, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>

#समावेश "inv_mpu_aux.h"
#समावेश "inv_mpu_iio.h"

/*
 * i2c master auxiliary bus transfer function.
 * Requires the i2c operations to be correctly setup beक्रमe.
 */
अटल पूर्णांक inv_mpu_i2c_master_xfer(स्थिर काष्ठा inv_mpu6050_state *st)
अणु
	/* use 50hz frequency क्रम xfer */
	स्थिर अचिन्हित पूर्णांक freq = 50;
	स्थिर अचिन्हित पूर्णांक period_ms = 1000 / freq;
	uपूर्णांक8_t d;
	अचिन्हित पूर्णांक user_ctrl;
	पूर्णांक ret;

	/* set sample rate */
	d = INV_MPU6050_FIFO_RATE_TO_DIVIDER(freq);
	ret = regmap_ग_लिखो(st->map, st->reg->sample_rate_भाग, d);
	अगर (ret)
		वापस ret;

	/* start i2c master */
	user_ctrl = st->chip_config.user_ctrl | INV_MPU6050_BIT_I2C_MST_EN;
	ret = regmap_ग_लिखो(st->map, st->reg->user_ctrl, user_ctrl);
	अगर (ret)
		जाओ error_restore_rate;

	/* रुको क्रम xfer: 1 period + half-period margin */
	msleep(period_ms + period_ms / 2);

	/* stop i2c master */
	user_ctrl = st->chip_config.user_ctrl;
	ret = regmap_ग_लिखो(st->map, st->reg->user_ctrl, user_ctrl);
	अगर (ret)
		जाओ error_stop_i2c;

	/* restore sample rate */
	d = st->chip_config.भागider;
	ret = regmap_ग_लिखो(st->map, st->reg->sample_rate_भाग, d);
	अगर (ret)
		जाओ error_restore_rate;

	वापस 0;

error_stop_i2c:
	regmap_ग_लिखो(st->map, st->reg->user_ctrl, st->chip_config.user_ctrl);
error_restore_rate:
	regmap_ग_लिखो(st->map, st->reg->sample_rate_भाग, st->chip_config.भागider);
	वापस ret;
पूर्ण

/**
 * inv_mpu_aux_init() - init i2c auxiliary bus
 * @st: driver पूर्णांकernal state
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक inv_mpu_aux_init(स्थिर काष्ठा inv_mpu6050_state *st)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* configure i2c master */
	val = INV_MPU6050_BITS_I2C_MST_CLK_400KHZ |
			INV_MPU6050_BIT_WAIT_FOR_ES;
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_MST_CTRL, val);
	अगर (ret)
		वापस ret;

	/* configure i2c master delay */
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV4_CTRL, 0);
	अगर (ret)
		वापस ret;

	val = INV_MPU6050_BIT_I2C_SLV0_DLY_EN |
			INV_MPU6050_BIT_I2C_SLV1_DLY_EN |
			INV_MPU6050_BIT_I2C_SLV2_DLY_EN |
			INV_MPU6050_BIT_I2C_SLV3_DLY_EN |
			INV_MPU6050_BIT_DELAY_ES_SHADOW;
	वापस regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_MST_DELAY_CTRL, val);
पूर्ण

/**
 * inv_mpu_aux_पढ़ो() - पढ़ो रेजिस्टर function क्रम i2c auxiliary bus
 * @st: driver पूर्णांकernal state.
 * @addr: chip i2c Address
 * @reg: chip रेजिस्टर address
 * @val: buffer क्रम storing पढ़ो bytes
 * @size: number of bytes to पढ़ो
 *
 *  Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक inv_mpu_aux_पढ़ो(स्थिर काष्ठा inv_mpu6050_state *st, uपूर्णांक8_t addr,
		     uपूर्णांक8_t reg, uपूर्णांक8_t *val, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	अगर (size > 0x0F)
		वापस -EINVAL;

	/* setup i2c SLV0 control: i2c addr, रेजिस्टर, enable + size */
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_ADDR(0),
			   INV_MPU6050_BIT_I2C_SLV_RNW | addr);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_REG(0), reg);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_CTRL(0),
			   INV_MPU6050_BIT_SLV_EN | size);
	अगर (ret)
		वापस ret;

	/* करो i2c xfer */
	ret = inv_mpu_i2c_master_xfer(st);
	अगर (ret)
		जाओ error_disable_i2c;

	/* disable i2c slave */
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_CTRL(0), 0);
	अगर (ret)
		जाओ error_disable_i2c;

	/* check i2c status */
	ret = regmap_पढ़ो(st->map, INV_MPU6050_REG_I2C_MST_STATUS, &status);
	अगर (ret)
		वापस ret;
	अगर (status & INV_MPU6050_BIT_I2C_SLV0_NACK)
		वापस -EIO;

	/* पढ़ो data in रेजिस्टरs */
	वापस regmap_bulk_पढ़ो(st->map, INV_MPU6050_REG_EXT_SENS_DATA,
				val, size);

error_disable_i2c:
	regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_CTRL(0), 0);
	वापस ret;
पूर्ण

/**
 * inv_mpu_aux_ग_लिखो() - ग_लिखो रेजिस्टर function क्रम i2c auxiliary bus
 * @st: driver पूर्णांकernal state.
 * @addr: chip i2c Address
 * @reg: chip रेजिस्टर address
 * @val: 1 byte value to ग_लिखो
 *
 *  Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक inv_mpu_aux_ग_लिखो(स्थिर काष्ठा inv_mpu6050_state *st, uपूर्णांक8_t addr,
		      uपूर्णांक8_t reg, uपूर्णांक8_t val)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	/* setup i2c SLV0 control: i2c addr, रेजिस्टर, value, enable + size */
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_ADDR(0), addr);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_REG(0), reg);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_DO(0), val);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_CTRL(0),
			   INV_MPU6050_BIT_SLV_EN | 1);
	अगर (ret)
		वापस ret;

	/* करो i2c xfer */
	ret = inv_mpu_i2c_master_xfer(st);
	अगर (ret)
		जाओ error_disable_i2c;

	/* disable i2c slave */
	ret = regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_CTRL(0), 0);
	अगर (ret)
		जाओ error_disable_i2c;

	/* check i2c status */
	ret = regmap_पढ़ो(st->map, INV_MPU6050_REG_I2C_MST_STATUS, &status);
	अगर (ret)
		वापस ret;
	अगर (status & INV_MPU6050_BIT_I2C_SLV0_NACK)
		वापस -EIO;

	वापस 0;

error_disable_i2c:
	regmap_ग_लिखो(st->map, INV_MPU6050_REG_I2C_SLV_CTRL(0), 0);
	वापस ret;
पूर्ण
