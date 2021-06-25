<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Copyright (C) 2012 Invensense, Inc.
*/

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "inv_mpu_iio.h"
#समावेश "inv_mpu_magn.h"

/*
 * this is the gyro scale translated from dynamic range plus/minus
 * अणु250, 500, 1000, 2000पूर्ण to rad/s
 */
अटल स्थिर पूर्णांक gyro_scale_6050[] = अणु133090, 266181, 532362, 1064724पूर्ण;

/*
 * this is the accel scale translated from dynamic range plus/minus
 * अणु2, 4, 8, 16पूर्ण to m/s^2
 */
अटल स्थिर पूर्णांक accel_scale[] = अणु598, 1196, 2392, 4785पूर्ण;

अटल स्थिर काष्ठा inv_mpu6050_reg_map reg_set_icm20602 = अणु
	.sample_rate_भाग	= INV_MPU6050_REG_SAMPLE_RATE_DIV,
	.lpf                    = INV_MPU6050_REG_CONFIG,
	.accel_lpf              = INV_MPU6500_REG_ACCEL_CONFIG_2,
	.user_ctrl              = INV_MPU6050_REG_USER_CTRL,
	.fअगरo_en                = INV_MPU6050_REG_FIFO_EN,
	.gyro_config            = INV_MPU6050_REG_GYRO_CONFIG,
	.accl_config            = INV_MPU6050_REG_ACCEL_CONFIG,
	.fअगरo_count_h           = INV_MPU6050_REG_FIFO_COUNT_H,
	.fअगरo_r_w               = INV_MPU6050_REG_FIFO_R_W,
	.raw_gyro               = INV_MPU6050_REG_RAW_GYRO,
	.raw_accl               = INV_MPU6050_REG_RAW_ACCEL,
	.temperature            = INV_MPU6050_REG_TEMPERATURE,
	.पूर्णांक_enable             = INV_MPU6050_REG_INT_ENABLE,
	.पूर्णांक_status             = INV_MPU6050_REG_INT_STATUS,
	.pwr_mgmt_1             = INV_MPU6050_REG_PWR_MGMT_1,
	.pwr_mgmt_2             = INV_MPU6050_REG_PWR_MGMT_2,
	.पूर्णांक_pin_cfg            = INV_MPU6050_REG_INT_PIN_CFG,
	.accl_offset            = INV_MPU6500_REG_ACCEL_OFFSET,
	.gyro_offset            = INV_MPU6050_REG_GYRO_OFFSET,
	.i2c_अगर                 = INV_ICM20602_REG_I2C_IF,
पूर्ण;

अटल स्थिर काष्ठा inv_mpu6050_reg_map reg_set_6500 = अणु
	.sample_rate_भाग	= INV_MPU6050_REG_SAMPLE_RATE_DIV,
	.lpf                    = INV_MPU6050_REG_CONFIG,
	.accel_lpf              = INV_MPU6500_REG_ACCEL_CONFIG_2,
	.user_ctrl              = INV_MPU6050_REG_USER_CTRL,
	.fअगरo_en                = INV_MPU6050_REG_FIFO_EN,
	.gyro_config            = INV_MPU6050_REG_GYRO_CONFIG,
	.accl_config            = INV_MPU6050_REG_ACCEL_CONFIG,
	.fअगरo_count_h           = INV_MPU6050_REG_FIFO_COUNT_H,
	.fअगरo_r_w               = INV_MPU6050_REG_FIFO_R_W,
	.raw_gyro               = INV_MPU6050_REG_RAW_GYRO,
	.raw_accl               = INV_MPU6050_REG_RAW_ACCEL,
	.temperature            = INV_MPU6050_REG_TEMPERATURE,
	.पूर्णांक_enable             = INV_MPU6050_REG_INT_ENABLE,
	.पूर्णांक_status             = INV_MPU6050_REG_INT_STATUS,
	.pwr_mgmt_1             = INV_MPU6050_REG_PWR_MGMT_1,
	.pwr_mgmt_2             = INV_MPU6050_REG_PWR_MGMT_2,
	.पूर्णांक_pin_cfg		= INV_MPU6050_REG_INT_PIN_CFG,
	.accl_offset		= INV_MPU6500_REG_ACCEL_OFFSET,
	.gyro_offset		= INV_MPU6050_REG_GYRO_OFFSET,
	.i2c_अगर                 = 0,
पूर्ण;

अटल स्थिर काष्ठा inv_mpu6050_reg_map reg_set_6050 = अणु
	.sample_rate_भाग	= INV_MPU6050_REG_SAMPLE_RATE_DIV,
	.lpf                    = INV_MPU6050_REG_CONFIG,
	.user_ctrl              = INV_MPU6050_REG_USER_CTRL,
	.fअगरo_en                = INV_MPU6050_REG_FIFO_EN,
	.gyro_config            = INV_MPU6050_REG_GYRO_CONFIG,
	.accl_config            = INV_MPU6050_REG_ACCEL_CONFIG,
	.fअगरo_count_h           = INV_MPU6050_REG_FIFO_COUNT_H,
	.fअगरo_r_w               = INV_MPU6050_REG_FIFO_R_W,
	.raw_gyro               = INV_MPU6050_REG_RAW_GYRO,
	.raw_accl               = INV_MPU6050_REG_RAW_ACCEL,
	.temperature            = INV_MPU6050_REG_TEMPERATURE,
	.पूर्णांक_enable             = INV_MPU6050_REG_INT_ENABLE,
	.pwr_mgmt_1             = INV_MPU6050_REG_PWR_MGMT_1,
	.pwr_mgmt_2             = INV_MPU6050_REG_PWR_MGMT_2,
	.पूर्णांक_pin_cfg		= INV_MPU6050_REG_INT_PIN_CFG,
	.accl_offset		= INV_MPU6050_REG_ACCEL_OFFSET,
	.gyro_offset		= INV_MPU6050_REG_GYRO_OFFSET,
	.i2c_अगर                 = 0,
पूर्ण;

अटल स्थिर काष्ठा inv_mpu6050_chip_config chip_config_6050 = अणु
	.clk = INV_CLK_INTERNAL,
	.fsr = INV_MPU6050_FSR_2000DPS,
	.lpf = INV_MPU6050_FILTER_20HZ,
	.भागider = INV_MPU6050_FIFO_RATE_TO_DIVIDER(50),
	.gyro_en = true,
	.accl_en = true,
	.temp_en = true,
	.magn_en = false,
	.gyro_fअगरo_enable = false,
	.accl_fअगरo_enable = false,
	.temp_fअगरo_enable = false,
	.magn_fअगरo_enable = false,
	.accl_fs = INV_MPU6050_FS_02G,
	.user_ctrl = 0,
पूर्ण;

अटल स्थिर काष्ठा inv_mpu6050_chip_config chip_config_6500 = अणु
	.clk = INV_CLK_PLL,
	.fsr = INV_MPU6050_FSR_2000DPS,
	.lpf = INV_MPU6050_FILTER_20HZ,
	.भागider = INV_MPU6050_FIFO_RATE_TO_DIVIDER(50),
	.gyro_en = true,
	.accl_en = true,
	.temp_en = true,
	.magn_en = false,
	.gyro_fअगरo_enable = false,
	.accl_fअगरo_enable = false,
	.temp_fअगरo_enable = false,
	.magn_fअगरo_enable = false,
	.accl_fs = INV_MPU6050_FS_02G,
	.user_ctrl = 0,
पूर्ण;

/* Indexed by क्रमागत inv_devices */
अटल स्थिर काष्ठा inv_mpu6050_hw hw_info[] = अणु
	अणु
		.whoami = INV_MPU6050_WHOAMI_VALUE,
		.name = "MPU6050",
		.reg = &reg_set_6050,
		.config = &chip_config_6050,
		.fअगरo_size = 1024,
		.temp = अणुINV_MPU6050_TEMP_OFFSET, INV_MPU6050_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_MPU6500_WHOAMI_VALUE,
		.name = "MPU6500",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 512,
		.temp = अणुINV_MPU6500_TEMP_OFFSET, INV_MPU6500_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_MPU6515_WHOAMI_VALUE,
		.name = "MPU6515",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 512,
		.temp = अणुINV_MPU6500_TEMP_OFFSET, INV_MPU6500_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_MPU6880_WHOAMI_VALUE,
		.name = "MPU6880",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 4096,
		.temp = अणुINV_MPU6500_TEMP_OFFSET, INV_MPU6500_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_MPU6000_WHOAMI_VALUE,
		.name = "MPU6000",
		.reg = &reg_set_6050,
		.config = &chip_config_6050,
		.fअगरo_size = 1024,
		.temp = अणुINV_MPU6050_TEMP_OFFSET, INV_MPU6050_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_MPU9150_WHOAMI_VALUE,
		.name = "MPU9150",
		.reg = &reg_set_6050,
		.config = &chip_config_6050,
		.fअगरo_size = 1024,
		.temp = अणुINV_MPU6050_TEMP_OFFSET, INV_MPU6050_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_MPU9250_WHOAMI_VALUE,
		.name = "MPU9250",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 512,
		.temp = अणुINV_MPU6500_TEMP_OFFSET, INV_MPU6500_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_MPU9255_WHOAMI_VALUE,
		.name = "MPU9255",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 512,
		.temp = अणुINV_MPU6500_TEMP_OFFSET, INV_MPU6500_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_ICM20608_WHOAMI_VALUE,
		.name = "ICM20608",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 512,
		.temp = अणुINV_ICM20608_TEMP_OFFSET, INV_ICM20608_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_ICM20609_WHOAMI_VALUE,
		.name = "ICM20609",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 4 * 1024,
		.temp = अणुINV_ICM20608_TEMP_OFFSET, INV_ICM20608_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_ICM20689_WHOAMI_VALUE,
		.name = "ICM20689",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 4 * 1024,
		.temp = अणुINV_ICM20608_TEMP_OFFSET, INV_ICM20608_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_ICM20602_WHOAMI_VALUE,
		.name = "ICM20602",
		.reg = &reg_set_icm20602,
		.config = &chip_config_6500,
		.fअगरo_size = 1008,
		.temp = अणुINV_ICM20608_TEMP_OFFSET, INV_ICM20608_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_ICM20690_WHOAMI_VALUE,
		.name = "ICM20690",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 1024,
		.temp = अणुINV_ICM20608_TEMP_OFFSET, INV_ICM20608_TEMP_SCALEपूर्ण,
	पूर्ण,
	अणु
		.whoami = INV_IAM20680_WHOAMI_VALUE,
		.name = "IAM20680",
		.reg = &reg_set_6500,
		.config = &chip_config_6500,
		.fअगरo_size = 512,
		.temp = अणुINV_ICM20608_TEMP_OFFSET, INV_ICM20608_TEMP_SCALEपूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक inv_mpu6050_pwr_mgmt_1_ग_लिखो(काष्ठा inv_mpu6050_state *st, bool sleep,
					पूर्णांक घड़ी, पूर्णांक temp_dis)
अणु
	u8 val;

	अगर (घड़ी < 0)
		घड़ी = st->chip_config.clk;
	अगर (temp_dis < 0)
		temp_dis = !st->chip_config.temp_en;

	val = घड़ी & INV_MPU6050_BIT_CLK_MASK;
	अगर (temp_dis)
		val |= INV_MPU6050_BIT_TEMP_DIS;
	अगर (sleep)
		val |= INV_MPU6050_BIT_SLEEP;

	dev_dbg(regmap_get_device(st->map), "pwr_mgmt_1: 0x%x\n", val);
	वापस regmap_ग_लिखो(st->map, st->reg->pwr_mgmt_1, val);
पूर्ण

अटल पूर्णांक inv_mpu6050_घड़ी_चयन(काष्ठा inv_mpu6050_state *st,
				    अचिन्हित पूर्णांक घड़ी)
अणु
	पूर्णांक ret;

	चयन (st->chip_type) अणु
	हाल INV_MPU6050:
	हाल INV_MPU6000:
	हाल INV_MPU9150:
		/* old chips: चयन घड़ी manually */
		ret = inv_mpu6050_pwr_mgmt_1_ग_लिखो(st, false, घड़ी, -1);
		अगर (ret)
			वापस ret;
		st->chip_config.clk = घड़ी;
		अवरोध;
	शेष:
		/* स्वतःmatic घड़ी चयनing, nothing to करो */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक inv_mpu6050_चयन_engine(काष्ठा inv_mpu6050_state *st, bool en,
			      अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक sleep;
	u8 pwr_mgmt2, user_ctrl;
	पूर्णांक ret;

	/* delete useless requests */
	अगर (mask & INV_MPU6050_SENSOR_ACCL && en == st->chip_config.accl_en)
		mask &= ~INV_MPU6050_SENSOR_ACCL;
	अगर (mask & INV_MPU6050_SENSOR_GYRO && en == st->chip_config.gyro_en)
		mask &= ~INV_MPU6050_SENSOR_GYRO;
	अगर (mask & INV_MPU6050_SENSOR_TEMP && en == st->chip_config.temp_en)
		mask &= ~INV_MPU6050_SENSOR_TEMP;
	अगर (mask & INV_MPU6050_SENSOR_MAGN && en == st->chip_config.magn_en)
		mask &= ~INV_MPU6050_SENSOR_MAGN;
	अगर (mask == 0)
		वापस 0;

	/* turn on/off temperature sensor */
	अगर (mask & INV_MPU6050_SENSOR_TEMP) अणु
		ret = inv_mpu6050_pwr_mgmt_1_ग_लिखो(st, false, -1, !en);
		अगर (ret)
			वापस ret;
		st->chip_config.temp_en = en;
	पूर्ण

	/* update user_crtl क्रम driving magnetometer */
	अगर (mask & INV_MPU6050_SENSOR_MAGN) अणु
		user_ctrl = st->chip_config.user_ctrl;
		अगर (en)
			user_ctrl |= INV_MPU6050_BIT_I2C_MST_EN;
		अन्यथा
			user_ctrl &= ~INV_MPU6050_BIT_I2C_MST_EN;
		ret = regmap_ग_लिखो(st->map, st->reg->user_ctrl, user_ctrl);
		अगर (ret)
			वापस ret;
		st->chip_config.user_ctrl = user_ctrl;
		st->chip_config.magn_en = en;
	पूर्ण

	/* manage accel & gyro engines */
	अगर (mask & (INV_MPU6050_SENSOR_ACCL | INV_MPU6050_SENSOR_GYRO)) अणु
		/* compute घातer management 2 current value */
		pwr_mgmt2 = 0;
		अगर (!st->chip_config.accl_en)
			pwr_mgmt2 |= INV_MPU6050_BIT_PWR_ACCL_STBY;
		अगर (!st->chip_config.gyro_en)
			pwr_mgmt2 |= INV_MPU6050_BIT_PWR_GYRO_STBY;

		/* update to new requested value */
		अगर (mask & INV_MPU6050_SENSOR_ACCL) अणु
			अगर (en)
				pwr_mgmt2 &= ~INV_MPU6050_BIT_PWR_ACCL_STBY;
			अन्यथा
				pwr_mgmt2 |= INV_MPU6050_BIT_PWR_ACCL_STBY;
		पूर्ण
		अगर (mask & INV_MPU6050_SENSOR_GYRO) अणु
			अगर (en)
				pwr_mgmt2 &= ~INV_MPU6050_BIT_PWR_GYRO_STBY;
			अन्यथा
				pwr_mgmt2 |= INV_MPU6050_BIT_PWR_GYRO_STBY;
		पूर्ण

		/* चयन घड़ी to पूर्णांकernal when turning gyro off */
		अगर (mask & INV_MPU6050_SENSOR_GYRO && !en) अणु
			ret = inv_mpu6050_घड़ी_चयन(st, INV_CLK_INTERNAL);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* update sensors engine */
		dev_dbg(regmap_get_device(st->map), "pwr_mgmt_2: 0x%x\n",
			pwr_mgmt2);
		ret = regmap_ग_लिखो(st->map, st->reg->pwr_mgmt_2, pwr_mgmt2);
		अगर (ret)
			वापस ret;
		अगर (mask & INV_MPU6050_SENSOR_ACCL)
			st->chip_config.accl_en = en;
		अगर (mask & INV_MPU6050_SENSOR_GYRO)
			st->chip_config.gyro_en = en;

		/* compute required समय to have sensors stabilized */
		sleep = 0;
		अगर (en) अणु
			अगर (mask & INV_MPU6050_SENSOR_ACCL) अणु
				अगर (sleep < INV_MPU6050_ACCEL_UP_TIME)
					sleep = INV_MPU6050_ACCEL_UP_TIME;
			पूर्ण
			अगर (mask & INV_MPU6050_SENSOR_GYRO) अणु
				अगर (sleep < INV_MPU6050_GYRO_UP_TIME)
					sleep = INV_MPU6050_GYRO_UP_TIME;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (mask & INV_MPU6050_SENSOR_GYRO) अणु
				अगर (sleep < INV_MPU6050_GYRO_DOWN_TIME)
					sleep = INV_MPU6050_GYRO_DOWN_TIME;
			पूर्ण
		पूर्ण
		अगर (sleep)
			msleep(sleep);

		/* चयन घड़ी to PLL when turning gyro on */
		अगर (mask & INV_MPU6050_SENSOR_GYRO && en) अणु
			ret = inv_mpu6050_घड़ी_चयन(st, INV_CLK_PLL);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inv_mpu6050_set_घातer_itg(काष्ठा inv_mpu6050_state *st,
				     bool घातer_on)
अणु
	पूर्णांक result;

	result = inv_mpu6050_pwr_mgmt_1_ग_लिखो(st, !घातer_on, -1, -1);
	अगर (result)
		वापस result;

	अगर (घातer_on)
		usleep_range(INV_MPU6050_REG_UP_TIME_MIN,
			     INV_MPU6050_REG_UP_TIME_MAX);

	वापस 0;
पूर्ण

अटल पूर्णांक inv_mpu6050_set_gyro_fsr(काष्ठा inv_mpu6050_state *st,
				    क्रमागत inv_mpu6050_fsr_e val)
अणु
	अचिन्हित पूर्णांक gyro_shअगरt;
	u8 data;

	चयन (st->chip_type) अणु
	हाल INV_ICM20690:
		gyro_shअगरt = INV_ICM20690_GYRO_CONFIG_FSR_SHIFT;
		अवरोध;
	शेष:
		gyro_shअगरt = INV_MPU6050_GYRO_CONFIG_FSR_SHIFT;
		अवरोध;
	पूर्ण

	data = val << gyro_shअगरt;
	वापस regmap_ग_लिखो(st->map, st->reg->gyro_config, data);
पूर्ण

/*
 *  inv_mpu6050_set_lpf_regs() - set low pass filter रेजिस्टरs, chip dependent
 *
 *  MPU60xx/MPU9150 use only 1 रेजिस्टर क्रम accelerometer + gyroscope
 *  MPU6500 and above have a dedicated रेजिस्टर क्रम accelerometer
 */
अटल पूर्णांक inv_mpu6050_set_lpf_regs(काष्ठा inv_mpu6050_state *st,
				    क्रमागत inv_mpu6050_filter_e val)
अणु
	पूर्णांक result;

	result = regmap_ग_लिखो(st->map, st->reg->lpf, val);
	अगर (result)
		वापस result;

	/* set accel lpf */
	चयन (st->chip_type) अणु
	हाल INV_MPU6050:
	हाल INV_MPU6000:
	हाल INV_MPU9150:
		/* old chips, nothing to करो */
		वापस 0;
	हाल INV_ICM20689:
	हाल INV_ICM20690:
		/* set FIFO size to maximum value */
		val |= INV_ICM20689_BITS_FIFO_SIZE_MAX;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस regmap_ग_लिखो(st->map, st->reg->accel_lpf, val);
पूर्ण

/*
 *  inv_mpu6050_init_config() - Initialize hardware, disable FIFO.
 *
 *  Initial configuration:
 *  FSR: तऔ 2000DPS
 *  DLPF: 20Hz
 *  FIFO rate: 50Hz
 *  Clock source: Gyro PLL
 */
अटल पूर्णांक inv_mpu6050_init_config(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक result;
	u8 d;
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);

	result = inv_mpu6050_set_gyro_fsr(st, st->chip_config.fsr);
	अगर (result)
		वापस result;

	result = inv_mpu6050_set_lpf_regs(st, st->chip_config.lpf);
	अगर (result)
		वापस result;

	d = st->chip_config.भागider;
	result = regmap_ग_लिखो(st->map, st->reg->sample_rate_भाग, d);
	अगर (result)
		वापस result;

	d = (st->chip_config.accl_fs << INV_MPU6050_ACCL_CONFIG_FSR_SHIFT);
	result = regmap_ग_लिखो(st->map, st->reg->accl_config, d);
	अगर (result)
		वापस result;

	result = regmap_ग_लिखो(st->map, st->reg->पूर्णांक_pin_cfg, st->irq_mask);
	अगर (result)
		वापस result;

	/*
	 * Internal chip period is 1ms (1kHz).
	 * Let's use at the beginning the theorical value beक्रमe measuring
	 * with पूर्णांकerrupt बारtamps.
	 */
	st->chip_period = NSEC_PER_MSEC;

	/* magn chip init, noop अगर not present in the chip */
	result = inv_mpu_magn_probe(st);
	अगर (result)
		वापस result;

	वापस 0;
पूर्ण

अटल पूर्णांक inv_mpu6050_sensor_set(काष्ठा inv_mpu6050_state  *st, पूर्णांक reg,
				पूर्णांक axis, पूर्णांक val)
अणु
	पूर्णांक ind, result;
	__be16 d = cpu_to_be16(val);

	ind = (axis - IIO_MOD_X) * 2;
	result = regmap_bulk_ग_लिखो(st->map, reg + ind, &d, माप(d));
	अगर (result)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक inv_mpu6050_sensor_show(काष्ठा inv_mpu6050_state  *st, पूर्णांक reg,
				   पूर्णांक axis, पूर्णांक *val)
अणु
	पूर्णांक ind, result;
	__be16 d;

	ind = (axis - IIO_MOD_X) * 2;
	result = regmap_bulk_पढ़ो(st->map, reg + ind, &d, माप(d));
	अगर (result)
		वापस -EINVAL;
	*val = (लघु)be16_to_cpup(&d);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक inv_mpu6050_पढ़ो_channel_data(काष्ठा iio_dev *indio_dev,
					 काष्ठा iio_chan_spec स्थिर *chan,
					 पूर्णांक *val)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	काष्ठा device *pdev = regmap_get_device(st->map);
	अचिन्हित पूर्णांक freq_hz, period_us, min_sleep_us, max_sleep_us;
	पूर्णांक result;
	पूर्णांक ret;

	/* compute sample period */
	freq_hz = INV_MPU6050_DIVIDER_TO_FIFO_RATE(st->chip_config.भागider);
	period_us = 1000000 / freq_hz;

	result = pm_runसमय_get_sync(pdev);
	अगर (result < 0) अणु
		pm_runसमय_put_noidle(pdev);
		वापस result;
	पूर्ण

	चयन (chan->type) अणु
	हाल IIO_ANGL_VEL:
		अगर (!st->chip_config.gyro_en) अणु
			result = inv_mpu6050_चयन_engine(st, true,
					INV_MPU6050_SENSOR_GYRO);
			अगर (result)
				जाओ error_घातer_off;
			/* need to रुको 2 periods to have first valid sample */
			min_sleep_us = 2 * period_us;
			max_sleep_us = 2 * (period_us + period_us / 2);
			usleep_range(min_sleep_us, max_sleep_us);
		पूर्ण
		ret = inv_mpu6050_sensor_show(st, st->reg->raw_gyro,
					      chan->channel2, val);
		अवरोध;
	हाल IIO_ACCEL:
		अगर (!st->chip_config.accl_en) अणु
			result = inv_mpu6050_चयन_engine(st, true,
					INV_MPU6050_SENSOR_ACCL);
			अगर (result)
				जाओ error_घातer_off;
			/* रुको 1 period क्रम first sample availability */
			min_sleep_us = period_us;
			max_sleep_us = period_us + period_us / 2;
			usleep_range(min_sleep_us, max_sleep_us);
		पूर्ण
		ret = inv_mpu6050_sensor_show(st, st->reg->raw_accl,
					      chan->channel2, val);
		अवरोध;
	हाल IIO_TEMP:
		/* temperature sensor work only with accel and/or gyro */
		अगर (!st->chip_config.accl_en && !st->chip_config.gyro_en) अणु
			result = -EBUSY;
			जाओ error_घातer_off;
		पूर्ण
		अगर (!st->chip_config.temp_en) अणु
			result = inv_mpu6050_चयन_engine(st, true,
					INV_MPU6050_SENSOR_TEMP);
			अगर (result)
				जाओ error_घातer_off;
			/* रुको 1 period क्रम first sample availability */
			min_sleep_us = period_us;
			max_sleep_us = period_us + period_us / 2;
			usleep_range(min_sleep_us, max_sleep_us);
		पूर्ण
		ret = inv_mpu6050_sensor_show(st, st->reg->temperature,
					      IIO_MOD_X, val);
		अवरोध;
	हाल IIO_MAGN:
		अगर (!st->chip_config.magn_en) अणु
			result = inv_mpu6050_चयन_engine(st, true,
					INV_MPU6050_SENSOR_MAGN);
			अगर (result)
				जाओ error_घातer_off;
			/* frequency is limited क्रम magnetometer */
			अगर (freq_hz > INV_MPU_MAGN_FREQ_HZ_MAX) अणु
				freq_hz = INV_MPU_MAGN_FREQ_HZ_MAX;
				period_us = 1000000 / freq_hz;
			पूर्ण
			/* need to रुको 2 periods to have first valid sample */
			min_sleep_us = 2 * period_us;
			max_sleep_us = 2 * (period_us + period_us / 2);
			usleep_range(min_sleep_us, max_sleep_us);
		पूर्ण
		ret = inv_mpu_magn_पढ़ो(st, chan->channel2, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(pdev);
	pm_runसमय_put_स्वतःsuspend(pdev);

	वापस ret;

error_घातer_off:
	pm_runसमय_put_स्वतःsuspend(pdev);
	वापस result;
पूर्ण

अटल पूर्णांक
inv_mpu6050_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		     काष्ठा iio_chan_spec स्थिर *chan,
		     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा inv_mpu6050_state  *st = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		mutex_lock(&st->lock);
		ret = inv_mpu6050_पढ़ो_channel_data(indio_dev, chan, val);
		mutex_unlock(&st->lock);
		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			mutex_lock(&st->lock);
			*val  = 0;
			*val2 = gyro_scale_6050[st->chip_config.fsr];
			mutex_unlock(&st->lock);

			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_ACCEL:
			mutex_lock(&st->lock);
			*val = 0;
			*val2 = accel_scale[st->chip_config.accl_fs];
			mutex_unlock(&st->lock);

			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = st->hw->temp.scale / 1000000;
			*val2 = st->hw->temp.scale % 1000000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_MAGN:
			वापस inv_mpu_magn_get_scale(st, chan, val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = st->hw->temp.offset;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_CALIBBIAS:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			mutex_lock(&st->lock);
			ret = inv_mpu6050_sensor_show(st, st->reg->gyro_offset,
						chan->channel2, val);
			mutex_unlock(&st->lock);
			वापस IIO_VAL_INT;
		हाल IIO_ACCEL:
			mutex_lock(&st->lock);
			ret = inv_mpu6050_sensor_show(st, st->reg->accl_offset,
						chan->channel2, val);
			mutex_unlock(&st->lock);
			वापस IIO_VAL_INT;

		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक inv_mpu6050_ग_लिखो_gyro_scale(काष्ठा inv_mpu6050_state *st, पूर्णांक val,
					पूर्णांक val2)
अणु
	पूर्णांक result, i;

	अगर (val != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(gyro_scale_6050); ++i) अणु
		अगर (gyro_scale_6050[i] == val2) अणु
			result = inv_mpu6050_set_gyro_fsr(st, i);
			अगर (result)
				वापस result;

			st->chip_config.fsr = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक inv_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		शेष:
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
	शेष:
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक inv_mpu6050_ग_लिखो_accel_scale(काष्ठा inv_mpu6050_state *st, पूर्णांक val,
					 पूर्णांक val2)
अणु
	पूर्णांक result, i;
	u8 d;

	अगर (val != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(accel_scale); ++i) अणु
		अगर (accel_scale[i] == val2) अणु
			d = (i << INV_MPU6050_ACCL_CONFIG_FSR_SHIFT);
			result = regmap_ग_लिखो(st->map, st->reg->accl_config, d);
			अगर (result)
				वापस result;

			st->chip_config.accl_fs = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक inv_mpu6050_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा inv_mpu6050_state  *st = iio_priv(indio_dev);
	काष्ठा device *pdev = regmap_get_device(st->map);
	पूर्णांक result;

	/*
	 * we should only update scale when the chip is disabled, i.e.
	 * not running
	 */
	result = iio_device_claim_direct_mode(indio_dev);
	अगर (result)
		वापस result;

	mutex_lock(&st->lock);
	result = pm_runसमय_get_sync(pdev);
	अगर (result < 0) अणु
		pm_runसमय_put_noidle(pdev);
		जाओ error_ग_लिखो_raw_unlock;
	पूर्ण

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			result = inv_mpu6050_ग_लिखो_gyro_scale(st, val, val2);
			अवरोध;
		हाल IIO_ACCEL:
			result = inv_mpu6050_ग_लिखो_accel_scale(st, val, val2);
			अवरोध;
		शेष:
			result = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			result = inv_mpu6050_sensor_set(st,
							st->reg->gyro_offset,
							chan->channel2, val);
			अवरोध;
		हाल IIO_ACCEL:
			result = inv_mpu6050_sensor_set(st,
							st->reg->accl_offset,
							chan->channel2, val);
			अवरोध;
		शेष:
			result = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(pdev);
	pm_runसमय_put_स्वतःsuspend(pdev);
error_ग_लिखो_raw_unlock:
	mutex_unlock(&st->lock);
	iio_device_release_direct_mode(indio_dev);

	वापस result;
पूर्ण

/*
 *  inv_mpu6050_set_lpf() - set low pass filer based on fअगरo rate.
 *
 *                  Based on the Nyquist principle, the bandwidth of the low
 *                  pass filter must not exceed the संकेत sampling rate भागided
 *                  by 2, or there would be aliasing.
 *                  This function basically search क्रम the correct low pass
 *                  parameters based on the fअगरo rate, e.g, sampling frequency.
 *
 *  lpf is set स्वतःmatically when setting sampling rate to aव्योम any aliases.
 */
अटल पूर्णांक inv_mpu6050_set_lpf(काष्ठा inv_mpu6050_state *st, पूर्णांक rate)
अणु
	अटल स्थिर पूर्णांक hz[] = अणु400, 200, 90, 40, 20, 10पूर्ण;
	अटल स्थिर पूर्णांक d[] = अणु
		INV_MPU6050_FILTER_200HZ, INV_MPU6050_FILTER_100HZ,
		INV_MPU6050_FILTER_45HZ, INV_MPU6050_FILTER_20HZ,
		INV_MPU6050_FILTER_10HZ, INV_MPU6050_FILTER_5HZ
	पूर्ण;
	पूर्णांक i, result;
	u8 data;

	data = INV_MPU6050_FILTER_5HZ;
	क्रम (i = 0; i < ARRAY_SIZE(hz); ++i) अणु
		अगर (rate >= hz[i]) अणु
			data = d[i];
			अवरोध;
		पूर्ण
	पूर्ण
	result = inv_mpu6050_set_lpf_regs(st, data);
	अगर (result)
		वापस result;
	st->chip_config.lpf = data;

	वापस 0;
पूर्ण

/*
 * inv_mpu6050_fअगरo_rate_store() - Set fअगरo rate.
 */
अटल sमाप_प्रकार
inv_mpu6050_fअगरo_rate_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक fअगरo_rate;
	u8 d;
	पूर्णांक result;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	काष्ठा device *pdev = regmap_get_device(st->map);

	अगर (kstrtoपूर्णांक(buf, 10, &fअगरo_rate))
		वापस -EINVAL;
	अगर (fअगरo_rate < INV_MPU6050_MIN_FIFO_RATE ||
	    fअगरo_rate > INV_MPU6050_MAX_FIFO_RATE)
		वापस -EINVAL;

	/* compute the chip sample rate भागider */
	d = INV_MPU6050_FIFO_RATE_TO_DIVIDER(fअगरo_rate);
	/* compute back the fअगरo rate to handle truncation हालs */
	fअगरo_rate = INV_MPU6050_DIVIDER_TO_FIFO_RATE(d);

	mutex_lock(&st->lock);
	अगर (d == st->chip_config.भागider) अणु
		result = 0;
		जाओ fअगरo_rate_fail_unlock;
	पूर्ण
	result = pm_runसमय_get_sync(pdev);
	अगर (result < 0) अणु
		pm_runसमय_put_noidle(pdev);
		जाओ fअगरo_rate_fail_unlock;
	पूर्ण

	result = regmap_ग_लिखो(st->map, st->reg->sample_rate_भाग, d);
	अगर (result)
		जाओ fअगरo_rate_fail_घातer_off;
	st->chip_config.भागider = d;

	result = inv_mpu6050_set_lpf(st, fअगरo_rate);
	अगर (result)
		जाओ fअगरo_rate_fail_घातer_off;

	/* update rate क्रम magn, noop अगर not present in chip */
	result = inv_mpu_magn_set_rate(st, fअगरo_rate);
	अगर (result)
		जाओ fअगरo_rate_fail_घातer_off;

	pm_runसमय_mark_last_busy(pdev);
fअगरo_rate_fail_घातer_off:
	pm_runसमय_put_स्वतःsuspend(pdev);
fअगरo_rate_fail_unlock:
	mutex_unlock(&st->lock);
	अगर (result)
		वापस result;

	वापस count;
पूर्ण

/*
 * inv_fअगरo_rate_show() - Get the current sampling rate.
 */
अटल sमाप_प्रकार
inv_fअगरo_rate_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   अक्षर *buf)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(dev_to_iio_dev(dev));
	अचिन्हित fअगरo_rate;

	mutex_lock(&st->lock);
	fअगरo_rate = INV_MPU6050_DIVIDER_TO_FIFO_RATE(st->chip_config.भागider);
	mutex_unlock(&st->lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", fअगरo_rate);
पूर्ण

/*
 * inv_attr_show() - calling this function will show current
 *                    parameters.
 *
 * Deprecated in favor of IIO mounting matrix API.
 *
 * See inv_get_mount_matrix()
 */
अटल sमाप_प्रकार inv_attr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(dev_to_iio_dev(dev));
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	s8 *m;

	चयन (this_attr->address) अणु
	/*
	 * In MPU6050, the two matrix are the same because gyro and accel
	 * are पूर्णांकegrated in one chip
	 */
	हाल ATTR_GYRO_MATRIX:
	हाल ATTR_ACCL_MATRIX:
		m = st->plat_data.orientation;

		वापस scnम_लिखो(buf, PAGE_SIZE,
			"%d, %d, %d; %d, %d, %d; %d, %d, %d\n",
			m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * inv_mpu6050_validate_trigger() - validate_trigger callback क्रम invensense
 *                                  MPU6050 device.
 * @indio_dev: The IIO device
 * @trig: The new trigger
 *
 * Returns: 0 अगर the 'trig' matches the trigger रेजिस्टरed by the MPU6050
 * device, -EINVAL otherwise.
 */
अटल पूर्णांक inv_mpu6050_validate_trigger(काष्ठा iio_dev *indio_dev,
					काष्ठा iio_trigger *trig)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);

	अगर (st->trig != trig)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
inv_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
		     स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा inv_mpu6050_state *data = iio_priv(indio_dev);
	स्थिर काष्ठा iio_mount_matrix *matrix;

	अगर (chan->type == IIO_MAGN)
		matrix = &data->magn_orient;
	अन्यथा
		matrix = &data->orientation;

	वापस matrix;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info inv_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_TYPE, inv_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

#घोषणा INV_MPU6050_CHAN(_type, _channel2, _index)                    \
	अणु                                                             \
		.type = _type,                                        \
		.modअगरied = 1,                                        \
		.channel2 = _channel2,                                \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	      \
				      BIT(IIO_CHAN_INFO_CALIBBIAS),   \
		.scan_index = _index,                                 \
		.scan_type = अणु                                        \
				.sign = 's',                          \
				.realbits = 16,                       \
				.storagebits = 16,                    \
				.shअगरt = 0,                           \
				.endianness = IIO_BE,                 \
			     पूर्ण,                                       \
		.ext_info = inv_ext_info,                             \
	पूर्ण

#घोषणा INV_MPU6050_TEMP_CHAN(_index)				\
	अणु							\
		.type = IIO_TEMP,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW)	\
				| BIT(IIO_CHAN_INFO_OFFSET)	\
				| BIT(IIO_CHAN_INFO_SCALE),	\
		.scan_index = _index,				\
		.scan_type = अणु					\
			.sign = 's',				\
			.realbits = 16,				\
			.storagebits = 16,			\
			.shअगरt = 0,				\
			.endianness = IIO_BE,			\
		पूर्ण,						\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec inv_mpu_channels[] = अणु
	IIO_CHAN_SOFT_TIMESTAMP(INV_MPU6050_SCAN_TIMESTAMP),

	INV_MPU6050_TEMP_CHAN(INV_MPU6050_SCAN_TEMP),

	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_X, INV_MPU6050_SCAN_GYRO_X),
	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_Y, INV_MPU6050_SCAN_GYRO_Y),
	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_Z, INV_MPU6050_SCAN_GYRO_Z),

	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_X, INV_MPU6050_SCAN_ACCL_X),
	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_Y, INV_MPU6050_SCAN_ACCL_Y),
	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_Z, INV_MPU6050_SCAN_ACCL_Z),
पूर्ण;

#घोषणा INV_MPU6050_SCAN_MASK_3AXIS_ACCEL	\
	(BIT(INV_MPU6050_SCAN_ACCL_X)		\
	| BIT(INV_MPU6050_SCAN_ACCL_Y)		\
	| BIT(INV_MPU6050_SCAN_ACCL_Z))

#घोषणा INV_MPU6050_SCAN_MASK_3AXIS_GYRO	\
	(BIT(INV_MPU6050_SCAN_GYRO_X)		\
	| BIT(INV_MPU6050_SCAN_GYRO_Y)		\
	| BIT(INV_MPU6050_SCAN_GYRO_Z))

#घोषणा INV_MPU6050_SCAN_MASK_TEMP		(BIT(INV_MPU6050_SCAN_TEMP))

अटल स्थिर अचिन्हित दीर्घ inv_mpu_scan_masks[] = अणु
	/* 3-axis accel */
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL,
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_TEMP,
	/* 3-axis gyro */
	INV_MPU6050_SCAN_MASK_3AXIS_GYRO,
	INV_MPU6050_SCAN_MASK_3AXIS_GYRO | INV_MPU6050_SCAN_MASK_TEMP,
	/* 6-axis accel + gyro */
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_3AXIS_GYRO,
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_3AXIS_GYRO
		| INV_MPU6050_SCAN_MASK_TEMP,
	0,
पूर्ण;

#घोषणा INV_MPU9X50_MAGN_CHAN(_chan2, _bits, _index)			\
	अणु								\
		.type = IIO_MAGN,					\
		.modअगरied = 1,						\
		.channel2 = _chan2,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_SCALE) |	\
				      BIT(IIO_CHAN_INFO_RAW),		\
		.scan_index = _index,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = _bits,				\
			.storagebits = 16,				\
			.shअगरt = 0,					\
			.endianness = IIO_BE,				\
		पूर्ण,							\
		.ext_info = inv_ext_info,				\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec inv_mpu9150_channels[] = अणु
	IIO_CHAN_SOFT_TIMESTAMP(INV_MPU9X50_SCAN_TIMESTAMP),

	INV_MPU6050_TEMP_CHAN(INV_MPU6050_SCAN_TEMP),

	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_X, INV_MPU6050_SCAN_GYRO_X),
	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_Y, INV_MPU6050_SCAN_GYRO_Y),
	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_Z, INV_MPU6050_SCAN_GYRO_Z),

	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_X, INV_MPU6050_SCAN_ACCL_X),
	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_Y, INV_MPU6050_SCAN_ACCL_Y),
	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_Z, INV_MPU6050_SCAN_ACCL_Z),

	/* Magnetometer resolution is 13 bits */
	INV_MPU9X50_MAGN_CHAN(IIO_MOD_X, 13, INV_MPU9X50_SCAN_MAGN_X),
	INV_MPU9X50_MAGN_CHAN(IIO_MOD_Y, 13, INV_MPU9X50_SCAN_MAGN_Y),
	INV_MPU9X50_MAGN_CHAN(IIO_MOD_Z, 13, INV_MPU9X50_SCAN_MAGN_Z),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec inv_mpu9250_channels[] = अणु
	IIO_CHAN_SOFT_TIMESTAMP(INV_MPU9X50_SCAN_TIMESTAMP),

	INV_MPU6050_TEMP_CHAN(INV_MPU6050_SCAN_TEMP),

	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_X, INV_MPU6050_SCAN_GYRO_X),
	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_Y, INV_MPU6050_SCAN_GYRO_Y),
	INV_MPU6050_CHAN(IIO_ANGL_VEL, IIO_MOD_Z, INV_MPU6050_SCAN_GYRO_Z),

	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_X, INV_MPU6050_SCAN_ACCL_X),
	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_Y, INV_MPU6050_SCAN_ACCL_Y),
	INV_MPU6050_CHAN(IIO_ACCEL, IIO_MOD_Z, INV_MPU6050_SCAN_ACCL_Z),

	/* Magnetometer resolution is 16 bits */
	INV_MPU9X50_MAGN_CHAN(IIO_MOD_X, 16, INV_MPU9X50_SCAN_MAGN_X),
	INV_MPU9X50_MAGN_CHAN(IIO_MOD_Y, 16, INV_MPU9X50_SCAN_MAGN_Y),
	INV_MPU9X50_MAGN_CHAN(IIO_MOD_Z, 16, INV_MPU9X50_SCAN_MAGN_Z),
पूर्ण;

#घोषणा INV_MPU9X50_SCAN_MASK_3AXIS_MAGN	\
	(BIT(INV_MPU9X50_SCAN_MAGN_X)		\
	| BIT(INV_MPU9X50_SCAN_MAGN_Y)		\
	| BIT(INV_MPU9X50_SCAN_MAGN_Z))

अटल स्थिर अचिन्हित दीर्घ inv_mpu9x50_scan_masks[] = अणु
	/* 3-axis accel */
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL,
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_TEMP,
	/* 3-axis gyro */
	INV_MPU6050_SCAN_MASK_3AXIS_GYRO,
	INV_MPU6050_SCAN_MASK_3AXIS_GYRO | INV_MPU6050_SCAN_MASK_TEMP,
	/* 3-axis magn */
	INV_MPU9X50_SCAN_MASK_3AXIS_MAGN,
	INV_MPU9X50_SCAN_MASK_3AXIS_MAGN | INV_MPU6050_SCAN_MASK_TEMP,
	/* 6-axis accel + gyro */
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_3AXIS_GYRO,
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_3AXIS_GYRO
		| INV_MPU6050_SCAN_MASK_TEMP,
	/* 6-axis accel + magn */
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU9X50_SCAN_MASK_3AXIS_MAGN,
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU9X50_SCAN_MASK_3AXIS_MAGN
		| INV_MPU6050_SCAN_MASK_TEMP,
	/* 6-axis gyro + magn */
	INV_MPU6050_SCAN_MASK_3AXIS_GYRO | INV_MPU9X50_SCAN_MASK_3AXIS_MAGN,
	INV_MPU6050_SCAN_MASK_3AXIS_GYRO | INV_MPU9X50_SCAN_MASK_3AXIS_MAGN
		| INV_MPU6050_SCAN_MASK_TEMP,
	/* 9-axis accel + gyro + magn */
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_3AXIS_GYRO
		| INV_MPU9X50_SCAN_MASK_3AXIS_MAGN,
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_3AXIS_GYRO
		| INV_MPU9X50_SCAN_MASK_3AXIS_MAGN
		| INV_MPU6050_SCAN_MASK_TEMP,
	0,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ inv_icm20602_scan_masks[] = अणु
	/* 3-axis accel + temp (mandatory) */
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_TEMP,
	/* 3-axis gyro + temp (mandatory) */
	INV_MPU6050_SCAN_MASK_3AXIS_GYRO | INV_MPU6050_SCAN_MASK_TEMP,
	/* 6-axis accel + gyro + temp (mandatory) */
	INV_MPU6050_SCAN_MASK_3AXIS_ACCEL | INV_MPU6050_SCAN_MASK_3AXIS_GYRO
		| INV_MPU6050_SCAN_MASK_TEMP,
	0,
पूर्ण;

/*
 * The user can choose any frequency between INV_MPU6050_MIN_FIFO_RATE and
 * INV_MPU6050_MAX_FIFO_RATE, but only these frequencies are matched by the
 * low-pass filter. Specअगरically, each of these sampling rates are about twice
 * the bandwidth of a corresponding low-pass filter, which should eliminate
 * aliasing following the Nyquist principle. By picking a frequency dअगरferent
 * from these, the user risks aliasing effects.
 */
अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("10 20 50 100 200 500");
अटल IIO_CONST_ATTR(in_anglvel_scale_available,
					  "0.000133090 0.000266181 0.000532362 0.001064724");
अटल IIO_CONST_ATTR(in_accel_scale_available,
					  "0.000598 0.001196 0.002392 0.004785");
अटल IIO_DEV_ATTR_SAMP_FREQ(S_IRUGO | S_IWUSR, inv_fअगरo_rate_show,
	inv_mpu6050_fअगरo_rate_store);

/* Deprecated: kept क्रम userspace backward compatibility. */
अटल IIO_DEVICE_ATTR(in_gyro_matrix, S_IRUGO, inv_attr_show, शून्य,
	ATTR_GYRO_MATRIX);
अटल IIO_DEVICE_ATTR(in_accel_matrix, S_IRUGO, inv_attr_show, शून्य,
	ATTR_ACCL_MATRIX);

अटल काष्ठा attribute *inv_attributes[] = अणु
	&iio_dev_attr_in_gyro_matrix.dev_attr.attr,  /* deprecated */
	&iio_dev_attr_in_accel_matrix.dev_attr.attr, /* deprecated */
	&iio_dev_attr_sampling_frequency.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_accel_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_anglvel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group inv_attribute_group = अणु
	.attrs = inv_attributes
पूर्ण;

अटल पूर्णांक inv_mpu6050_reg_access(काष्ठा iio_dev *indio_dev,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक ग_लिखोval,
				  अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	अगर (पढ़ोval)
		ret = regmap_पढ़ो(st->map, reg, पढ़ोval);
	अन्यथा
		ret = regmap_ग_लिखो(st->map, reg, ग_लिखोval);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info mpu_info = अणु
	.पढ़ो_raw = &inv_mpu6050_पढ़ो_raw,
	.ग_लिखो_raw = &inv_mpu6050_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = &inv_ग_लिखो_raw_get_fmt,
	.attrs = &inv_attribute_group,
	.validate_trigger = inv_mpu6050_validate_trigger,
	.debugfs_reg_access = &inv_mpu6050_reg_access,
पूर्ण;

/*
 *  inv_check_and_setup_chip() - check and setup chip.
 */
अटल पूर्णांक inv_check_and_setup_chip(काष्ठा inv_mpu6050_state *st)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक regval, mask;
	पूर्णांक i;

	st->hw  = &hw_info[st->chip_type];
	st->reg = hw_info[st->chip_type].reg;
	स_नकल(&st->chip_config, hw_info[st->chip_type].config,
	       माप(st->chip_config));

	/* check chip self-identअगरication */
	result = regmap_पढ़ो(st->map, INV_MPU6050_REG_WHOAMI, &regval);
	अगर (result)
		वापस result;
	अगर (regval != st->hw->whoami) अणु
		/* check whoami against all possible values */
		क्रम (i = 0; i < INV_NUM_PARTS; ++i) अणु
			अगर (regval == hw_info[i].whoami) अणु
				dev_warn(regmap_get_device(st->map),
					"whoami mismatch got %#02x (%s)"
					"expected %#02hhx (%s)\n",
					regval, hw_info[i].name,
					st->hw->whoami, st->hw->name);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i >= INV_NUM_PARTS) अणु
			dev_err(regmap_get_device(st->map),
				"invalid whoami %#02x expected %#02hhx (%s)\n",
				regval, st->hw->whoami, st->hw->name);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* reset to make sure previous state are not there */
	result = regmap_ग_लिखो(st->map, st->reg->pwr_mgmt_1,
			      INV_MPU6050_BIT_H_RESET);
	अगर (result)
		वापस result;
	msleep(INV_MPU6050_POWER_UP_TIME);
	चयन (st->chip_type) अणु
	हाल INV_MPU6000:
	हाल INV_MPU6500:
	हाल INV_MPU6515:
	हाल INV_MPU6880:
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		/* reset संकेत path (required क्रम spi connection) */
		regval = INV_MPU6050_BIT_TEMP_RST | INV_MPU6050_BIT_ACCEL_RST |
			 INV_MPU6050_BIT_GYRO_RST;
		result = regmap_ग_लिखो(st->map, INV_MPU6050_REG_SIGNAL_PATH_RESET,
				      regval);
		अगर (result)
			वापस result;
		msleep(INV_MPU6050_POWER_UP_TIME);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Turn घातer on. After reset, the sleep bit could be on
	 * or off depending on the OTP settings. Turning घातer on
	 * make it in a definite state as well as making the hardware
	 * state align with the software state
	 */
	result = inv_mpu6050_set_घातer_itg(st, true);
	अगर (result)
		वापस result;
	mask = INV_MPU6050_SENSOR_ACCL | INV_MPU6050_SENSOR_GYRO |
			INV_MPU6050_SENSOR_TEMP | INV_MPU6050_SENSOR_MAGN;
	result = inv_mpu6050_चयन_engine(st, false, mask);
	अगर (result)
		जाओ error_घातer_off;

	वापस 0;

error_घातer_off:
	inv_mpu6050_set_घातer_itg(st, false);
	वापस result;
पूर्ण

अटल पूर्णांक inv_mpu_core_enable_regulator_vddio(काष्ठा inv_mpu6050_state *st)
अणु
	पूर्णांक result;

	result = regulator_enable(st->vddio_supply);
	अगर (result) अणु
		dev_err(regmap_get_device(st->map),
			"Failed to enable vddio regulator: %d\n", result);
	पूर्ण अन्यथा अणु
		/* Give the device a little bit of समय to start up. */
		usleep_range(3000, 5000);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक inv_mpu_core_disable_regulator_vddio(काष्ठा inv_mpu6050_state *st)
अणु
	पूर्णांक result;

	result = regulator_disable(st->vddio_supply);
	अगर (result)
		dev_err(regmap_get_device(st->map),
			"Failed to disable vddio regulator: %d\n", result);

	वापस result;
पूर्ण

अटल व्योम inv_mpu_core_disable_regulator_action(व्योम *_data)
अणु
	काष्ठा inv_mpu6050_state *st = _data;
	पूर्णांक result;

	result = regulator_disable(st->vdd_supply);
	अगर (result)
		dev_err(regmap_get_device(st->map),
			"Failed to disable vdd regulator: %d\n", result);

	inv_mpu_core_disable_regulator_vddio(st);
पूर्ण

अटल व्योम inv_mpu_pm_disable(व्योम *data)
अणु
	काष्ठा device *dev = data;

	pm_runसमय_put_sync_suspend(dev);
	pm_runसमय_disable(dev);
पूर्ण

पूर्णांक inv_mpu_core_probe(काष्ठा regmap *regmap, पूर्णांक irq, स्थिर अक्षर *name,
		पूर्णांक (*inv_mpu_bus_setup)(काष्ठा iio_dev *), पूर्णांक chip_type)
अणु
	काष्ठा inv_mpu6050_state *st;
	काष्ठा iio_dev *indio_dev;
	काष्ठा inv_mpu6050_platक्रमm_data *pdata;
	काष्ठा device *dev = regmap_get_device(regmap);
	पूर्णांक result;
	काष्ठा irq_data *desc;
	पूर्णांक irq_type;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	BUILD_BUG_ON(ARRAY_SIZE(hw_info) != INV_NUM_PARTS);
	अगर (chip_type < 0 || chip_type >= INV_NUM_PARTS) अणु
		dev_err(dev, "Bad invensense chip_type=%d name=%s\n",
				chip_type, name);
		वापस -ENODEV;
	पूर्ण
	st = iio_priv(indio_dev);
	mutex_init(&st->lock);
	st->chip_type = chip_type;
	st->irq = irq;
	st->map = regmap;

	pdata = dev_get_platdata(dev);
	अगर (!pdata) अणु
		result = iio_पढ़ो_mount_matrix(dev, "mount-matrix",
					       &st->orientation);
		अगर (result) अणु
			dev_err(dev, "Failed to retrieve mounting matrix %d\n",
				result);
			वापस result;
		पूर्ण
	पूर्ण अन्यथा अणु
		st->plat_data = *pdata;
	पूर्ण

	अगर (irq > 0) अणु
		desc = irq_get_irq_data(irq);
		अगर (!desc) अणु
			dev_err(dev, "Could not find IRQ %d\n", irq);
			वापस -EINVAL;
		पूर्ण

		irq_type = irqd_get_trigger_type(desc);
		अगर (!irq_type)
			irq_type = IRQF_TRIGGER_RISING;
	पूर्ण अन्यथा अणु
		/* Doesn't really matter, use the शेष */
		irq_type = IRQF_TRIGGER_RISING;
	पूर्ण

	अगर (irq_type & IRQF_TRIGGER_RISING)	// rising or both-edge
		st->irq_mask = INV_MPU6050_ACTIVE_HIGH;
	अन्यथा अगर (irq_type == IRQF_TRIGGER_FALLING)
		st->irq_mask = INV_MPU6050_ACTIVE_LOW;
	अन्यथा अगर (irq_type == IRQF_TRIGGER_HIGH)
		st->irq_mask = INV_MPU6050_ACTIVE_HIGH |
			INV_MPU6050_LATCH_INT_EN;
	अन्यथा अगर (irq_type == IRQF_TRIGGER_LOW)
		st->irq_mask = INV_MPU6050_ACTIVE_LOW |
			INV_MPU6050_LATCH_INT_EN;
	अन्यथा अणु
		dev_err(dev, "Invalid interrupt type 0x%x specified\n",
			irq_type);
		वापस -EINVAL;
	पूर्ण

	st->vdd_supply = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(st->vdd_supply))
		वापस dev_err_probe(dev, PTR_ERR(st->vdd_supply),
				     "Failed to get vdd regulator\n");

	st->vddio_supply = devm_regulator_get(dev, "vddio");
	अगर (IS_ERR(st->vddio_supply))
		वापस dev_err_probe(dev, PTR_ERR(st->vddio_supply),
				     "Failed to get vddio regulator\n");

	result = regulator_enable(st->vdd_supply);
	अगर (result) अणु
		dev_err(dev, "Failed to enable vdd regulator: %d\n", result);
		वापस result;
	पूर्ण
	msleep(INV_MPU6050_POWER_UP_TIME);

	result = inv_mpu_core_enable_regulator_vddio(st);
	अगर (result) अणु
		regulator_disable(st->vdd_supply);
		वापस result;
	पूर्ण

	result = devm_add_action_or_reset(dev, inv_mpu_core_disable_regulator_action,
				 st);
	अगर (result) अणु
		dev_err(dev, "Failed to setup regulator cleanup action %d\n",
			result);
		वापस result;
	पूर्ण

	/* fill magnetometer orientation */
	result = inv_mpu_magn_set_orient(st);
	अगर (result)
		वापस result;

	/* घातer is turned on inside check chip type*/
	result = inv_check_and_setup_chip(st);
	अगर (result)
		वापस result;

	result = inv_mpu6050_init_config(indio_dev);
	अगर (result) अणु
		dev_err(dev, "Could not initialize device.\n");
		जाओ error_घातer_off;
	पूर्ण

	dev_set_drvdata(dev, indio_dev);
	/* name will be शून्य when क्रमागतerated via ACPI */
	अगर (name)
		indio_dev->name = name;
	अन्यथा
		indio_dev->name = dev_name(dev);

	/* requires parent device set in indio_dev */
	अगर (inv_mpu_bus_setup) अणु
		result = inv_mpu_bus_setup(indio_dev);
		अगर (result)
			जाओ error_घातer_off;
	पूर्ण

	/* chip init is करोne, turning on runसमय घातer management */
	result = pm_runसमय_set_active(dev);
	अगर (result)
		जाओ error_घातer_off;
	pm_runसमय_get_noresume(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, INV_MPU6050_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put(dev);
	result = devm_add_action_or_reset(dev, inv_mpu_pm_disable, dev);
	अगर (result)
		वापस result;

	चयन (chip_type) अणु
	हाल INV_MPU9150:
		indio_dev->channels = inv_mpu9150_channels;
		indio_dev->num_channels = ARRAY_SIZE(inv_mpu9150_channels);
		indio_dev->available_scan_masks = inv_mpu9x50_scan_masks;
		अवरोध;
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		indio_dev->channels = inv_mpu9250_channels;
		indio_dev->num_channels = ARRAY_SIZE(inv_mpu9250_channels);
		indio_dev->available_scan_masks = inv_mpu9x50_scan_masks;
		अवरोध;
	हाल INV_ICM20602:
		indio_dev->channels = inv_mpu_channels;
		indio_dev->num_channels = ARRAY_SIZE(inv_mpu_channels);
		indio_dev->available_scan_masks = inv_icm20602_scan_masks;
		अवरोध;
	शेष:
		indio_dev->channels = inv_mpu_channels;
		indio_dev->num_channels = ARRAY_SIZE(inv_mpu_channels);
		indio_dev->available_scan_masks = inv_mpu_scan_masks;
		अवरोध;
	पूर्ण
	/*
	 * Use magnetometer inside the chip only अगर there is no i2c
	 * auxiliary device in use. Otherwise Going back to 6-axis only.
	 */
	अगर (st->magn_disabled) अणु
		indio_dev->channels = inv_mpu_channels;
		indio_dev->num_channels = ARRAY_SIZE(inv_mpu_channels);
		indio_dev->available_scan_masks = inv_mpu_scan_masks;
	पूर्ण

	indio_dev->info = &mpu_info;

	अगर (irq > 0) अणु
		/*
		 * The driver currently only supports buffered capture with its
		 * own trigger. So no IRQ, no trigger, no buffer
		 */
		result = devm_iio_triggered_buffer_setup(dev, indio_dev,
							 iio_pollfunc_store_समय,
							 inv_mpu6050_पढ़ो_fअगरo,
							 शून्य);
		अगर (result) अणु
			dev_err(dev, "configure buffer fail %d\n", result);
			वापस result;
		पूर्ण

		result = inv_mpu6050_probe_trigger(indio_dev, irq_type);
		अगर (result) अणु
			dev_err(dev, "trigger probe fail %d\n", result);
			वापस result;
		पूर्ण
	पूर्ण

	result = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (result) अणु
		dev_err(dev, "IIO register fail %d\n", result);
		वापस result;
	पूर्ण

	वापस 0;

error_घातer_off:
	inv_mpu6050_set_घातer_itg(st, false);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(inv_mpu_core_probe);

अटल पूर्णांक __maybe_unused inv_mpu_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	पूर्णांक result;

	mutex_lock(&st->lock);
	result = inv_mpu_core_enable_regulator_vddio(st);
	अगर (result)
		जाओ out_unlock;

	result = inv_mpu6050_set_घातer_itg(st, true);
	अगर (result)
		जाओ out_unlock;

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	result = inv_mpu6050_चयन_engine(st, true, st->suspended_sensors);
	अगर (result)
		जाओ out_unlock;

	अगर (iio_buffer_enabled(indio_dev))
		result = inv_mpu6050_prepare_fअगरo(st, true);

out_unlock:
	mutex_unlock(&st->lock);

	वापस result;
पूर्ण

अटल पूर्णांक __maybe_unused inv_mpu_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	पूर्णांक result;

	mutex_lock(&st->lock);

	st->suspended_sensors = 0;
	अगर (pm_runसमय_suspended(dev)) अणु
		result = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (iio_buffer_enabled(indio_dev)) अणु
		result = inv_mpu6050_prepare_fअगरo(st, false);
		अगर (result)
			जाओ out_unlock;
	पूर्ण

	अगर (st->chip_config.accl_en)
		st->suspended_sensors |= INV_MPU6050_SENSOR_ACCL;
	अगर (st->chip_config.gyro_en)
		st->suspended_sensors |= INV_MPU6050_SENSOR_GYRO;
	अगर (st->chip_config.temp_en)
		st->suspended_sensors |= INV_MPU6050_SENSOR_TEMP;
	अगर (st->chip_config.magn_en)
		st->suspended_sensors |= INV_MPU6050_SENSOR_MAGN;
	result = inv_mpu6050_चयन_engine(st, false, st->suspended_sensors);
	अगर (result)
		जाओ out_unlock;

	result = inv_mpu6050_set_घातer_itg(st, false);
	अगर (result)
		जाओ out_unlock;

	inv_mpu_core_disable_regulator_vddio(st);
out_unlock:
	mutex_unlock(&st->lock);

	वापस result;
पूर्ण

अटल पूर्णांक __maybe_unused inv_mpu_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(dev_get_drvdata(dev));
	अचिन्हित पूर्णांक sensors;
	पूर्णांक ret;

	mutex_lock(&st->lock);

	sensors = INV_MPU6050_SENSOR_ACCL | INV_MPU6050_SENSOR_GYRO |
			INV_MPU6050_SENSOR_TEMP | INV_MPU6050_SENSOR_MAGN;
	ret = inv_mpu6050_चयन_engine(st, false, sensors);
	अगर (ret)
		जाओ out_unlock;

	ret = inv_mpu6050_set_घातer_itg(st, false);
	अगर (ret)
		जाओ out_unlock;

	inv_mpu_core_disable_regulator_vddio(st);

out_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused inv_mpu_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(dev_get_drvdata(dev));
	पूर्णांक ret;

	ret = inv_mpu_core_enable_regulator_vddio(st);
	अगर (ret)
		वापस ret;

	वापस inv_mpu6050_set_घातer_itg(st, true);
पूर्ण

स्थिर काष्ठा dev_pm_ops inv_mpu_pmops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(inv_mpu_suspend, inv_mpu_resume)
	SET_RUNTIME_PM_OPS(inv_mpu_runसमय_suspend, inv_mpu_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(inv_mpu_pmops);

MODULE_AUTHOR("Invensense Corporation");
MODULE_DESCRIPTION("Invensense device MPU6050 driver");
MODULE_LICENSE("GPL");
