<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Invensense, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>

#समावेश "inv_icm42600.h"
#समावेश "inv_icm42600_buffer.h"
#समावेश "inv_icm42600_timestamp.h"

अटल स्थिर काष्ठा regmap_range_cfg inv_icm42600_regmap_ranges[] = अणु
	अणु
		.name = "user banks",
		.range_min = 0x0000,
		.range_max = 0x4FFF,
		.selector_reg = INV_ICM42600_REG_BANK_SEL,
		.selector_mask = INV_ICM42600_BANK_SEL_MASK,
		.selector_shअगरt = 0,
		.winकरोw_start = 0,
		.winकरोw_len = 0x1000,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा regmap_config inv_icm42600_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x4FFF,
	.ranges = inv_icm42600_regmap_ranges,
	.num_ranges = ARRAY_SIZE(inv_icm42600_regmap_ranges),
पूर्ण;
EXPORT_SYMBOL_GPL(inv_icm42600_regmap_config);

काष्ठा inv_icm42600_hw अणु
	uपूर्णांक8_t whoami;
	स्थिर अक्षर *name;
	स्थिर काष्ठा inv_icm42600_conf *conf;
पूर्ण;

/* chip initial शेष configuration */
अटल स्थिर काष्ठा inv_icm42600_conf inv_icm42600_शेष_conf = अणु
	.gyro = अणु
		.mode = INV_ICM42600_SENSOR_MODE_OFF,
		.fs = INV_ICM42600_GYRO_FS_2000DPS,
		.odr = INV_ICM42600_ODR_50HZ,
		.filter = INV_ICM42600_FILTER_BW_ODR_DIV_2,
	पूर्ण,
	.accel = अणु
		.mode = INV_ICM42600_SENSOR_MODE_OFF,
		.fs = INV_ICM42600_ACCEL_FS_16G,
		.odr = INV_ICM42600_ODR_50HZ,
		.filter = INV_ICM42600_FILTER_BW_ODR_DIV_2,
	पूर्ण,
	.temp_en = false,
पूर्ण;

अटल स्थिर काष्ठा inv_icm42600_hw inv_icm42600_hw[INV_CHIP_NB] = अणु
	[INV_CHIP_ICM42600] = अणु
		.whoami = INV_ICM42600_WHOAMI_ICM42600,
		.name = "icm42600",
		.conf = &inv_icm42600_शेष_conf,
	पूर्ण,
	[INV_CHIP_ICM42602] = अणु
		.whoami = INV_ICM42600_WHOAMI_ICM42602,
		.name = "icm42602",
		.conf = &inv_icm42600_शेष_conf,
	पूर्ण,
	[INV_CHIP_ICM42605] = अणु
		.whoami = INV_ICM42600_WHOAMI_ICM42605,
		.name = "icm42605",
		.conf = &inv_icm42600_शेष_conf,
	पूर्ण,
	[INV_CHIP_ICM42622] = अणु
		.whoami = INV_ICM42600_WHOAMI_ICM42622,
		.name = "icm42622",
		.conf = &inv_icm42600_शेष_conf,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा iio_mount_matrix *
inv_icm42600_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan)
अणु
	स्थिर काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);

	वापस &st->orientation;
पूर्ण

uपूर्णांक32_t inv_icm42600_odr_to_period(क्रमागत inv_icm42600_odr odr)
अणु
	अटल uपूर्णांक32_t odr_periods[INV_ICM42600_ODR_NB] = अणु
		/* reserved values */
		0, 0, 0,
		/* 8kHz */
		125000,
		/* 4kHz */
		250000,
		/* 2kHz */
		500000,
		/* 1kHz */
		1000000,
		/* 200Hz */
		5000000,
		/* 100Hz */
		10000000,
		/* 50Hz */
		20000000,
		/* 25Hz */
		40000000,
		/* 12.5Hz */
		80000000,
		/* 6.25Hz */
		160000000,
		/* 3.125Hz */
		320000000,
		/* 1.5625Hz */
		640000000,
		/* 500Hz */
		2000000,
	पूर्ण;

	वापस odr_periods[odr];
पूर्ण

अटल पूर्णांक inv_icm42600_set_pwr_mgmt0(काष्ठा inv_icm42600_state *st,
				      क्रमागत inv_icm42600_sensor_mode gyro,
				      क्रमागत inv_icm42600_sensor_mode accel,
				      bool temp, अचिन्हित पूर्णांक *sleep_ms)
अणु
	क्रमागत inv_icm42600_sensor_mode oldgyro = st->conf.gyro.mode;
	क्रमागत inv_icm42600_sensor_mode oldaccel = st->conf.accel.mode;
	bool oldtemp = st->conf.temp_en;
	अचिन्हित पूर्णांक sleepval;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* अगर nothing changed, निकास */
	अगर (gyro == oldgyro && accel == oldaccel && temp == oldtemp)
		वापस 0;

	val = INV_ICM42600_PWR_MGMT0_GYRO(gyro) |
	      INV_ICM42600_PWR_MGMT0_ACCEL(accel);
	अगर (!temp)
		val |= INV_ICM42600_PWR_MGMT0_TEMP_DIS;
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_PWR_MGMT0, val);
	अगर (ret)
		वापस ret;

	st->conf.gyro.mode = gyro;
	st->conf.accel.mode = accel;
	st->conf.temp_en = temp;

	/* compute required रुको समय क्रम sensors to stabilize */
	sleepval = 0;
	/* temperature stabilization समय */
	अगर (temp && !oldtemp) अणु
		अगर (sleepval < INV_ICM42600_TEMP_STARTUP_TIME_MS)
			sleepval = INV_ICM42600_TEMP_STARTUP_TIME_MS;
	पूर्ण
	/* accel startup समय */
	अगर (accel != oldaccel && oldaccel == INV_ICM42600_SENSOR_MODE_OFF) अणु
		/* block any रेजिस्टर ग_लिखो क्रम at least 200 तगs */
		usleep_range(200, 300);
		अगर (sleepval < INV_ICM42600_ACCEL_STARTUP_TIME_MS)
			sleepval = INV_ICM42600_ACCEL_STARTUP_TIME_MS;
	पूर्ण
	अगर (gyro != oldgyro) अणु
		/* gyro startup समय */
		अगर (oldgyro == INV_ICM42600_SENSOR_MODE_OFF) अणु
			/* block any रेजिस्टर ग_लिखो क्रम at least 200 तगs */
			usleep_range(200, 300);
			अगर (sleepval < INV_ICM42600_GYRO_STARTUP_TIME_MS)
				sleepval = INV_ICM42600_GYRO_STARTUP_TIME_MS;
		/* gyro stop समय */
		पूर्ण अन्यथा अगर (gyro == INV_ICM42600_SENSOR_MODE_OFF) अणु
			अगर (sleepval < INV_ICM42600_GYRO_STOP_TIME_MS)
				sleepval =  INV_ICM42600_GYRO_STOP_TIME_MS;
		पूर्ण
	पूर्ण

	/* deferred sleep value अगर sleep poपूर्णांकer is provided or direct sleep */
	अगर (sleep_ms)
		*sleep_ms = sleepval;
	अन्यथा अगर (sleepval)
		msleep(sleepval);

	वापस 0;
पूर्ण

पूर्णांक inv_icm42600_set_accel_conf(काष्ठा inv_icm42600_state *st,
				काष्ठा inv_icm42600_sensor_conf *conf,
				अचिन्हित पूर्णांक *sleep_ms)
अणु
	काष्ठा inv_icm42600_sensor_conf *oldconf = &st->conf.accel;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Sanitize missing values with current values */
	अगर (conf->mode < 0)
		conf->mode = oldconf->mode;
	अगर (conf->fs < 0)
		conf->fs = oldconf->fs;
	अगर (conf->odr < 0)
		conf->odr = oldconf->odr;
	अगर (conf->filter < 0)
		conf->filter = oldconf->filter;

	/* set ACCEL_CONFIG0 रेजिस्टर (accel fullscale & odr) */
	अगर (conf->fs != oldconf->fs || conf->odr != oldconf->odr) अणु
		val = INV_ICM42600_ACCEL_CONFIG0_FS(conf->fs) |
		      INV_ICM42600_ACCEL_CONFIG0_ODR(conf->odr);
		ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_ACCEL_CONFIG0, val);
		अगर (ret)
			वापस ret;
		oldconf->fs = conf->fs;
		oldconf->odr = conf->odr;
	पूर्ण

	/* set GYRO_ACCEL_CONFIG0 रेजिस्टर (accel filter) */
	अगर (conf->filter != oldconf->filter) अणु
		val = INV_ICM42600_GYRO_ACCEL_CONFIG0_ACCEL_FILT(conf->filter) |
		      INV_ICM42600_GYRO_ACCEL_CONFIG0_GYRO_FILT(st->conf.gyro.filter);
		ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_GYRO_ACCEL_CONFIG0, val);
		अगर (ret)
			वापस ret;
		oldconf->filter = conf->filter;
	पूर्ण

	/* set PWR_MGMT0 रेजिस्टर (accel sensor mode) */
	वापस inv_icm42600_set_pwr_mgmt0(st, st->conf.gyro.mode, conf->mode,
					  st->conf.temp_en, sleep_ms);
पूर्ण

पूर्णांक inv_icm42600_set_gyro_conf(काष्ठा inv_icm42600_state *st,
			       काष्ठा inv_icm42600_sensor_conf *conf,
			       अचिन्हित पूर्णांक *sleep_ms)
अणु
	काष्ठा inv_icm42600_sensor_conf *oldconf = &st->conf.gyro;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* sanitize missing values with current values */
	अगर (conf->mode < 0)
		conf->mode = oldconf->mode;
	अगर (conf->fs < 0)
		conf->fs = oldconf->fs;
	अगर (conf->odr < 0)
		conf->odr = oldconf->odr;
	अगर (conf->filter < 0)
		conf->filter = oldconf->filter;

	/* set GYRO_CONFIG0 रेजिस्टर (gyro fullscale & odr) */
	अगर (conf->fs != oldconf->fs || conf->odr != oldconf->odr) अणु
		val = INV_ICM42600_GYRO_CONFIG0_FS(conf->fs) |
		      INV_ICM42600_GYRO_CONFIG0_ODR(conf->odr);
		ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_GYRO_CONFIG0, val);
		अगर (ret)
			वापस ret;
		oldconf->fs = conf->fs;
		oldconf->odr = conf->odr;
	पूर्ण

	/* set GYRO_ACCEL_CONFIG0 रेजिस्टर (gyro filter) */
	अगर (conf->filter != oldconf->filter) अणु
		val = INV_ICM42600_GYRO_ACCEL_CONFIG0_ACCEL_FILT(st->conf.accel.filter) |
		      INV_ICM42600_GYRO_ACCEL_CONFIG0_GYRO_FILT(conf->filter);
		ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_GYRO_ACCEL_CONFIG0, val);
		अगर (ret)
			वापस ret;
		oldconf->filter = conf->filter;
	पूर्ण

	/* set PWR_MGMT0 रेजिस्टर (gyro sensor mode) */
	वापस inv_icm42600_set_pwr_mgmt0(st, conf->mode, st->conf.accel.mode,
					  st->conf.temp_en, sleep_ms);

	वापस 0;
पूर्ण

पूर्णांक inv_icm42600_set_temp_conf(काष्ठा inv_icm42600_state *st, bool enable,
			       अचिन्हित पूर्णांक *sleep_ms)
अणु
	वापस inv_icm42600_set_pwr_mgmt0(st, st->conf.gyro.mode,
					  st->conf.accel.mode, enable,
					  sleep_ms);
पूर्ण

पूर्णांक inv_icm42600_debugfs_reg(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक ग_लिखोval, अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	अगर (पढ़ोval)
		ret = regmap_पढ़ो(st->map, reg, पढ़ोval);
	अन्यथा
		ret = regmap_ग_लिखो(st->map, reg, ग_लिखोval);

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक inv_icm42600_set_conf(काष्ठा inv_icm42600_state *st,
				 स्थिर काष्ठा inv_icm42600_conf *conf)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* set PWR_MGMT0 रेजिस्टर (gyro & accel sensor mode, temp enabled) */
	val = INV_ICM42600_PWR_MGMT0_GYRO(conf->gyro.mode) |
	      INV_ICM42600_PWR_MGMT0_ACCEL(conf->accel.mode);
	अगर (!conf->temp_en)
		val |= INV_ICM42600_PWR_MGMT0_TEMP_DIS;
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_PWR_MGMT0, val);
	अगर (ret)
		वापस ret;

	/* set GYRO_CONFIG0 रेजिस्टर (gyro fullscale & odr) */
	val = INV_ICM42600_GYRO_CONFIG0_FS(conf->gyro.fs) |
	      INV_ICM42600_GYRO_CONFIG0_ODR(conf->gyro.odr);
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_GYRO_CONFIG0, val);
	अगर (ret)
		वापस ret;

	/* set ACCEL_CONFIG0 रेजिस्टर (accel fullscale & odr) */
	val = INV_ICM42600_ACCEL_CONFIG0_FS(conf->accel.fs) |
	      INV_ICM42600_ACCEL_CONFIG0_ODR(conf->accel.odr);
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_ACCEL_CONFIG0, val);
	अगर (ret)
		वापस ret;

	/* set GYRO_ACCEL_CONFIG0 रेजिस्टर (gyro & accel filters) */
	val = INV_ICM42600_GYRO_ACCEL_CONFIG0_ACCEL_FILT(conf->accel.filter) |
	      INV_ICM42600_GYRO_ACCEL_CONFIG0_GYRO_FILT(conf->gyro.filter);
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_GYRO_ACCEL_CONFIG0, val);
	अगर (ret)
		वापस ret;

	/* update पूर्णांकernal conf */
	st->conf = *conf;

	वापस 0;
पूर्ण

/**
 *  inv_icm42600_setup() - check and setup chip
 *  @st:	driver पूर्णांकernal state
 *  @bus_setup:	callback क्रम setting up bus specअगरic रेजिस्टरs
 *
 *  Returns 0 on success, a negative error code otherwise.
 */
अटल पूर्णांक inv_icm42600_setup(काष्ठा inv_icm42600_state *st,
			      inv_icm42600_bus_setup bus_setup)
अणु
	स्थिर काष्ठा inv_icm42600_hw *hw = &inv_icm42600_hw[st->chip];
	स्थिर काष्ठा device *dev = regmap_get_device(st->map);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* check chip self-identअगरication value */
	ret = regmap_पढ़ो(st->map, INV_ICM42600_REG_WHOAMI, &val);
	अगर (ret)
		वापस ret;
	अगर (val != hw->whoami) अणु
		dev_err(dev, "invalid whoami %#02x expected %#02x (%s)\n",
			val, hw->whoami, hw->name);
		वापस -ENODEV;
	पूर्ण
	st->name = hw->name;

	/* reset to make sure previous state are not there */
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_DEVICE_CONFIG,
			   INV_ICM42600_DEVICE_CONFIG_SOFT_RESET);
	अगर (ret)
		वापस ret;
	msleep(INV_ICM42600_RESET_TIME_MS);

	ret = regmap_पढ़ो(st->map, INV_ICM42600_REG_INT_STATUS, &val);
	अगर (ret)
		वापस ret;
	अगर (!(val & INV_ICM42600_INT_STATUS_RESET_DONE)) अणु
		dev_err(dev, "reset error, reset done bit not set\n");
		वापस -ENODEV;
	पूर्ण

	/* set chip bus configuration */
	ret = bus_setup(st);
	अगर (ret)
		वापस ret;

	/* sensor data in big-endian (शेष) */
	ret = regmap_update_bits(st->map, INV_ICM42600_REG_INTF_CONFIG0,
				 INV_ICM42600_INTF_CONFIG0_SENSOR_DATA_ENDIAN,
				 INV_ICM42600_INTF_CONFIG0_SENSOR_DATA_ENDIAN);
	अगर (ret)
		वापस ret;

	वापस inv_icm42600_set_conf(st, hw->conf);
पूर्ण

अटल irqवापस_t inv_icm42600_irq_बारtamp(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा inv_icm42600_state *st = _data;

	st->बारtamp.gyro = iio_get_समय_ns(st->indio_gyro);
	st->बारtamp.accel = iio_get_समय_ns(st->indio_accel);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t inv_icm42600_irq_handler(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा inv_icm42600_state *st = _data;
	काष्ठा device *dev = regmap_get_device(st->map);
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	mutex_lock(&st->lock);

	ret = regmap_पढ़ो(st->map, INV_ICM42600_REG_INT_STATUS, &status);
	अगर (ret)
		जाओ out_unlock;

	/* FIFO full */
	अगर (status & INV_ICM42600_INT_STATUS_FIFO_FULL)
		dev_warn(dev, "FIFO full data lost!\n");

	/* FIFO threshold reached */
	अगर (status & INV_ICM42600_INT_STATUS_FIFO_THS) अणु
		ret = inv_icm42600_buffer_fअगरo_पढ़ो(st, 0);
		अगर (ret) अणु
			dev_err(dev, "FIFO read error %d\n", ret);
			जाओ out_unlock;
		पूर्ण
		ret = inv_icm42600_buffer_fअगरo_parse(st);
		अगर (ret)
			dev_err(dev, "FIFO parsing error %d\n", ret);
	पूर्ण

out_unlock:
	mutex_unlock(&st->lock);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * inv_icm42600_irq_init() - initialize पूर्णांक pin and पूर्णांकerrupt handler
 * @st:		driver पूर्णांकernal state
 * @irq:	irq number
 * @irq_type:	irq trigger type
 * @खोलो_drain:	true अगर irq is खोलो drain, false क्रम push-pull
 *
 * Returns 0 on success, a negative error code otherwise.
 */
अटल पूर्णांक inv_icm42600_irq_init(काष्ठा inv_icm42600_state *st, पूर्णांक irq,
				 पूर्णांक irq_type, bool खोलो_drain)
अणु
	काष्ठा device *dev = regmap_get_device(st->map);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* configure INT1 पूर्णांकerrupt: शेष is active low on edge */
	चयन (irq_type) अणु
	हाल IRQF_TRIGGER_RISING:
	हाल IRQF_TRIGGER_HIGH:
		val = INV_ICM42600_INT_CONFIG_INT1_ACTIVE_HIGH;
		अवरोध;
	शेष:
		val = INV_ICM42600_INT_CONFIG_INT1_ACTIVE_LOW;
		अवरोध;
	पूर्ण

	चयन (irq_type) अणु
	हाल IRQF_TRIGGER_LOW:
	हाल IRQF_TRIGGER_HIGH:
		val |= INV_ICM42600_INT_CONFIG_INT1_LATCHED;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!खोलो_drain)
		val |= INV_ICM42600_INT_CONFIG_INT1_PUSH_PULL;

	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_INT_CONFIG, val);
	अगर (ret)
		वापस ret;

	/* Deनिश्चित async reset क्रम proper INT pin operation (cf datasheet) */
	ret = regmap_update_bits(st->map, INV_ICM42600_REG_INT_CONFIG1,
				 INV_ICM42600_INT_CONFIG1_ASYNC_RESET, 0);
	अगर (ret)
		वापस ret;

	वापस devm_request_thपढ़ोed_irq(dev, irq, inv_icm42600_irq_बारtamp,
					 inv_icm42600_irq_handler, irq_type,
					 "inv_icm42600", st);
पूर्ण

अटल पूर्णांक inv_icm42600_enable_regulator_vddio(काष्ठा inv_icm42600_state *st)
अणु
	पूर्णांक ret;

	ret = regulator_enable(st->vddio_supply);
	अगर (ret)
		वापस ret;

	/* रुको a little क्रम supply ramp */
	usleep_range(3000, 4000);

	वापस 0;
पूर्ण

अटल व्योम inv_icm42600_disable_vdd_reg(व्योम *_data)
अणु
	काष्ठा inv_icm42600_state *st = _data;
	स्थिर काष्ठा device *dev = regmap_get_device(st->map);
	पूर्णांक ret;

	ret = regulator_disable(st->vdd_supply);
	अगर (ret)
		dev_err(dev, "failed to disable vdd error %d\n", ret);
पूर्ण

अटल व्योम inv_icm42600_disable_vddio_reg(व्योम *_data)
अणु
	काष्ठा inv_icm42600_state *st = _data;
	स्थिर काष्ठा device *dev = regmap_get_device(st->map);
	पूर्णांक ret;

	ret = regulator_disable(st->vddio_supply);
	अगर (ret)
		dev_err(dev, "failed to disable vddio error %d\n", ret);
पूर्ण

अटल व्योम inv_icm42600_disable_pm(व्योम *_data)
अणु
	काष्ठा device *dev = _data;

	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
पूर्ण

पूर्णांक inv_icm42600_core_probe(काष्ठा regmap *regmap, पूर्णांक chip, पूर्णांक irq,
			    inv_icm42600_bus_setup bus_setup)
अणु
	काष्ठा device *dev = regmap_get_device(regmap);
	काष्ठा inv_icm42600_state *st;
	काष्ठा irq_data *irq_desc;
	पूर्णांक irq_type;
	bool खोलो_drain;
	पूर्णांक ret;

	अगर (chip < 0 || chip >= INV_CHIP_NB) अणु
		dev_err(dev, "invalid chip = %d\n", chip);
		वापस -ENODEV;
	पूर्ण

	/* get irq properties, set trigger falling by शेष */
	irq_desc = irq_get_irq_data(irq);
	अगर (!irq_desc) अणु
		dev_err(dev, "could not find IRQ %d\n", irq);
		वापस -EINVAL;
	पूर्ण

	irq_type = irqd_get_trigger_type(irq_desc);
	अगर (!irq_type)
		irq_type = IRQF_TRIGGER_FALLING;

	खोलो_drain = device_property_पढ़ो_bool(dev, "drive-open-drain");

	st = devm_kzalloc(dev, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	dev_set_drvdata(dev, st);
	mutex_init(&st->lock);
	st->chip = chip;
	st->map = regmap;

	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix", &st->orientation);
	अगर (ret) अणु
		dev_err(dev, "failed to retrieve mounting matrix %d\n", ret);
		वापस ret;
	पूर्ण

	st->vdd_supply = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(st->vdd_supply))
		वापस PTR_ERR(st->vdd_supply);

	st->vddio_supply = devm_regulator_get(dev, "vddio");
	अगर (IS_ERR(st->vddio_supply))
		वापस PTR_ERR(st->vddio_supply);

	ret = regulator_enable(st->vdd_supply);
	अगर (ret)
		वापस ret;
	msleep(INV_ICM42600_POWER_UP_TIME_MS);

	ret = devm_add_action_or_reset(dev, inv_icm42600_disable_vdd_reg, st);
	अगर (ret)
		वापस ret;

	ret = inv_icm42600_enable_regulator_vddio(st);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, inv_icm42600_disable_vddio_reg, st);
	अगर (ret)
		वापस ret;

	/* setup chip रेजिस्टरs */
	ret = inv_icm42600_setup(st, bus_setup);
	अगर (ret)
		वापस ret;

	ret = inv_icm42600_बारtamp_setup(st);
	अगर (ret)
		वापस ret;

	ret = inv_icm42600_buffer_init(st);
	अगर (ret)
		वापस ret;

	st->indio_gyro = inv_icm42600_gyro_init(st);
	अगर (IS_ERR(st->indio_gyro))
		वापस PTR_ERR(st->indio_gyro);

	st->indio_accel = inv_icm42600_accel_init(st);
	अगर (IS_ERR(st->indio_accel))
		वापस PTR_ERR(st->indio_accel);

	ret = inv_icm42600_irq_init(st, irq, irq_type, खोलो_drain);
	अगर (ret)
		वापस ret;

	/* setup runसमय घातer management */
	ret = pm_runसमय_set_active(dev);
	अगर (ret)
		वापस ret;
	pm_runसमय_get_noresume(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, INV_ICM42600_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put(dev);

	वापस devm_add_action_or_reset(dev, inv_icm42600_disable_pm, dev);
पूर्ण
EXPORT_SYMBOL_GPL(inv_icm42600_core_probe);

/*
 * Suspend saves sensors state and turns everything off.
 * Check first अगर runसमय suspend has not alपढ़ोy करोne the job.
 */
अटल पूर्णांक __maybe_unused inv_icm42600_suspend(काष्ठा device *dev)
अणु
	काष्ठा inv_icm42600_state *st = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	st->suspended.gyro = st->conf.gyro.mode;
	st->suspended.accel = st->conf.accel.mode;
	st->suspended.temp = st->conf.temp_en;
	अगर (pm_runसमय_suspended(dev)) अणु
		ret = 0;
		जाओ out_unlock;
	पूर्ण

	/* disable FIFO data streaming */
	अगर (st->fअगरo.on) अणु
		ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_FIFO_CONFIG,
				   INV_ICM42600_FIFO_CONFIG_BYPASS);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	ret = inv_icm42600_set_pwr_mgmt0(st, INV_ICM42600_SENSOR_MODE_OFF,
					 INV_ICM42600_SENSOR_MODE_OFF, false,
					 शून्य);
	अगर (ret)
		जाओ out_unlock;

	regulator_disable(st->vddio_supply);

out_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

/*
 * System resume माला_लो the प्रणाली back on and restores the sensors state.
 * Manually put runसमय घातer management in प्रणाली active state.
 */
अटल पूर्णांक __maybe_unused inv_icm42600_resume(काष्ठा device *dev)
अणु
	काष्ठा inv_icm42600_state *st = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	ret = inv_icm42600_enable_regulator_vddio(st);
	अगर (ret)
		जाओ out_unlock;

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	/* restore sensors state */
	ret = inv_icm42600_set_pwr_mgmt0(st, st->suspended.gyro,
					 st->suspended.accel,
					 st->suspended.temp, शून्य);
	अगर (ret)
		जाओ out_unlock;

	/* restore FIFO data streaming */
	अगर (st->fअगरo.on)
		ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_FIFO_CONFIG,
				   INV_ICM42600_FIFO_CONFIG_STREAM);

out_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

/* Runसमय suspend will turn off sensors that are enabled by iio devices. */
अटल पूर्णांक __maybe_unused inv_icm42600_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा inv_icm42600_state *st = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	/* disable all sensors */
	ret = inv_icm42600_set_pwr_mgmt0(st, INV_ICM42600_SENSOR_MODE_OFF,
					 INV_ICM42600_SENSOR_MODE_OFF, false,
					 शून्य);
	अगर (ret)
		जाओ error_unlock;

	regulator_disable(st->vddio_supply);

error_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

/* Sensors are enabled by iio devices, no need to turn them back on here. */
अटल पूर्णांक __maybe_unused inv_icm42600_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा inv_icm42600_state *st = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	ret = inv_icm42600_enable_regulator_vddio(st);

	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

स्थिर काष्ठा dev_pm_ops inv_icm42600_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(inv_icm42600_suspend, inv_icm42600_resume)
	SET_RUNTIME_PM_OPS(inv_icm42600_runसमय_suspend,
			   inv_icm42600_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(inv_icm42600_pm_ops);

MODULE_AUTHOR("InvenSense, Inc.");
MODULE_DESCRIPTION("InvenSense ICM-426xx device driver");
MODULE_LICENSE("GPL");
