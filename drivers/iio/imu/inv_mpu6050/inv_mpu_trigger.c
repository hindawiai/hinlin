<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Copyright (C) 2012 Invensense, Inc.
*/

#समावेश <linux/pm_runसमय.स>
#समावेश "inv_mpu_iio.h"

अटल अचिन्हित पूर्णांक inv_scan_query_mpu6050(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_mpu6050_state  *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mask;

	/*
	 * If the MPU6050 is just used as a trigger, then the scan mask
	 * is not allocated so we simply enable the temperature channel
	 * as a dummy and bail out.
	 */
	अगर (!indio_dev->active_scan_mask) अणु
		st->chip_config.temp_fअगरo_enable = true;
		वापस INV_MPU6050_SENSOR_TEMP;
	पूर्ण

	st->chip_config.gyro_fअगरo_enable =
		test_bit(INV_MPU6050_SCAN_GYRO_X,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU6050_SCAN_GYRO_Y,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU6050_SCAN_GYRO_Z,
			 indio_dev->active_scan_mask);

	st->chip_config.accl_fअगरo_enable =
		test_bit(INV_MPU6050_SCAN_ACCL_X,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU6050_SCAN_ACCL_Y,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU6050_SCAN_ACCL_Z,
			 indio_dev->active_scan_mask);

	st->chip_config.temp_fअगरo_enable =
		test_bit(INV_MPU6050_SCAN_TEMP, indio_dev->active_scan_mask);

	mask = 0;
	अगर (st->chip_config.gyro_fअगरo_enable)
		mask |= INV_MPU6050_SENSOR_GYRO;
	अगर (st->chip_config.accl_fअगरo_enable)
		mask |= INV_MPU6050_SENSOR_ACCL;
	अगर (st->chip_config.temp_fअगरo_enable)
		mask |= INV_MPU6050_SENSOR_TEMP;

	वापस mask;
पूर्ण

अटल अचिन्हित पूर्णांक inv_scan_query_mpu9x50(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mask;

	mask = inv_scan_query_mpu6050(indio_dev);

	/* no magnetometer अगर i2c auxiliary bus is used */
	अगर (st->magn_disabled)
		वापस mask;

	st->chip_config.magn_fअगरo_enable =
		test_bit(INV_MPU9X50_SCAN_MAGN_X,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU9X50_SCAN_MAGN_Y,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU9X50_SCAN_MAGN_Z,
			 indio_dev->active_scan_mask);
	अगर (st->chip_config.magn_fअगरo_enable)
		mask |= INV_MPU6050_SENSOR_MAGN;

	वापस mask;
पूर्ण

अटल अचिन्हित पूर्णांक inv_scan_query(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);

	चयन (st->chip_type) अणु
	हाल INV_MPU9150:
	हाल INV_MPU9250:
	हाल INV_MPU9255:
		वापस inv_scan_query_mpu9x50(indio_dev);
	शेष:
		वापस inv_scan_query_mpu6050(indio_dev);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक inv_compute_skip_samples(स्थिर काष्ठा inv_mpu6050_state *st)
अणु
	अचिन्हित पूर्णांक gyro_skip = 0;
	अचिन्हित पूर्णांक magn_skip = 0;
	अचिन्हित पूर्णांक skip_samples;

	/* gyro first sample is out of specs, skip it */
	अगर (st->chip_config.gyro_fअगरo_enable)
		gyro_skip = 1;

	/* mag first sample is always not पढ़ोy, skip it */
	अगर (st->chip_config.magn_fअगरo_enable)
		magn_skip = 1;

	/* compute first samples to skip */
	skip_samples = gyro_skip;
	अगर (magn_skip > skip_samples)
		skip_samples = magn_skip;

	वापस skip_samples;
पूर्ण

पूर्णांक inv_mpu6050_prepare_fअगरo(काष्ठा inv_mpu6050_state *st, bool enable)
अणु
	uपूर्णांक8_t d;
	पूर्णांक ret;

	अगर (enable) अणु
		st->it_बारtamp = 0;
		/* reset FIFO */
		d = st->chip_config.user_ctrl | INV_MPU6050_BIT_FIFO_RST;
		ret = regmap_ग_लिखो(st->map, st->reg->user_ctrl, d);
		अगर (ret)
			वापस ret;
		/* enable sensor output to FIFO */
		d = 0;
		अगर (st->chip_config.gyro_fअगरo_enable)
			d |= INV_MPU6050_BITS_GYRO_OUT;
		अगर (st->chip_config.accl_fअगरo_enable)
			d |= INV_MPU6050_BIT_ACCEL_OUT;
		अगर (st->chip_config.temp_fअगरo_enable)
			d |= INV_MPU6050_BIT_TEMP_OUT;
		अगर (st->chip_config.magn_fअगरo_enable)
			d |= INV_MPU6050_BIT_SLAVE_0;
		ret = regmap_ग_लिखो(st->map, st->reg->fअगरo_en, d);
		अगर (ret)
			वापस ret;
		/* enable FIFO पढ़ोing */
		d = st->chip_config.user_ctrl | INV_MPU6050_BIT_FIFO_EN;
		ret = regmap_ग_लिखो(st->map, st->reg->user_ctrl, d);
		अगर (ret)
			वापस ret;
		/* enable पूर्णांकerrupt */
		ret = regmap_ग_लिखो(st->map, st->reg->पूर्णांक_enable,
				   INV_MPU6050_BIT_DATA_RDY_EN);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(st->map, st->reg->पूर्णांक_enable, 0);
		अगर (ret)
			वापस ret;
		ret = regmap_ग_लिखो(st->map, st->reg->fअगरo_en, 0);
		अगर (ret)
			वापस ret;
		/* restore user_ctrl क्रम disabling FIFO पढ़ोing */
		ret = regmap_ग_लिखो(st->map, st->reg->user_ctrl,
				   st->chip_config.user_ctrl);
	पूर्ण

	वापस ret;
पूर्ण

/**
 *  inv_mpu6050_set_enable() - enable chip functions.
 *  @indio_dev:	Device driver instance.
 *  @enable: enable/disable
 */
अटल पूर्णांक inv_mpu6050_set_enable(काष्ठा iio_dev *indio_dev, bool enable)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	काष्ठा device *pdev = regmap_get_device(st->map);
	अचिन्हित पूर्णांक scan;
	पूर्णांक result;

	अगर (enable) अणु
		scan = inv_scan_query(indio_dev);
		result = pm_runसमय_get_sync(pdev);
		अगर (result < 0) अणु
			pm_runसमय_put_noidle(pdev);
			वापस result;
		पूर्ण
		/*
		 * In हाल स्वतःsuspend didn't trigger, turn off first not
		 * required sensors.
		 */
		result = inv_mpu6050_चयन_engine(st, false, ~scan);
		अगर (result)
			जाओ error_घातer_off;
		result = inv_mpu6050_चयन_engine(st, true, scan);
		अगर (result)
			जाओ error_घातer_off;
		st->skip_samples = inv_compute_skip_samples(st);
		result = inv_mpu6050_prepare_fअगरo(st, true);
		अगर (result)
			जाओ error_घातer_off;
	पूर्ण अन्यथा अणु
		result = inv_mpu6050_prepare_fअगरo(st, false);
		अगर (result)
			जाओ error_घातer_off;
		pm_runसमय_mark_last_busy(pdev);
		pm_runसमय_put_स्वतःsuspend(pdev);
	पूर्ण

	वापस 0;

error_घातer_off:
	pm_runसमय_put_स्वतःsuspend(pdev);
	वापस result;
पूर्ण

/**
 * inv_mpu_data_rdy_trigger_set_state() - set data पढ़ोy पूर्णांकerrupt state
 * @trig: Trigger instance
 * @state: Desired trigger state
 */
अटल पूर्णांक inv_mpu_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
					      bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	पूर्णांक result;

	mutex_lock(&st->lock);
	result = inv_mpu6050_set_enable(indio_dev, state);
	mutex_unlock(&st->lock);

	वापस result;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops inv_mpu_trigger_ops = अणु
	.set_trigger_state = &inv_mpu_data_rdy_trigger_set_state,
पूर्ण;

पूर्णांक inv_mpu6050_probe_trigger(काष्ठा iio_dev *indio_dev, पूर्णांक irq_type)
अणु
	पूर्णांक ret;
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);

	st->trig = devm_iio_trigger_alloc(&indio_dev->dev,
					  "%s-dev%d",
					  indio_dev->name,
					  indio_dev->id);
	अगर (!st->trig)
		वापस -ENOMEM;

	ret = devm_request_irq(&indio_dev->dev, st->irq,
			       &iio_trigger_generic_data_rdy_poll,
			       irq_type,
			       "inv_mpu",
			       st->trig);
	अगर (ret)
		वापस ret;

	st->trig->dev.parent = regmap_get_device(st->map);
	st->trig->ops = &inv_mpu_trigger_ops;
	iio_trigger_set_drvdata(st->trig, indio_dev);

	ret = devm_iio_trigger_रेजिस्टर(&indio_dev->dev, st->trig);
	अगर (ret)
		वापस ret;

	indio_dev->trig = iio_trigger_get(st->trig);

	वापस 0;
पूर्ण
