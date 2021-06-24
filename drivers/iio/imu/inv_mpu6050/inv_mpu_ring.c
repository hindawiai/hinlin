<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Copyright (C) 2012 Invensense, Inc.
*/

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/poll.h>
#समावेश <linux/math64.h>
#समावेश "inv_mpu_iio.h"

/**
 *  inv_mpu6050_update_period() - Update chip पूर्णांकernal period estimation
 *
 *  @st:		driver state
 *  @बारtamp:		the पूर्णांकerrupt बारtamp
 *  @nb:		number of data set in the fअगरo
 *
 *  This function uses पूर्णांकerrupt बारtamps to estimate the chip period and
 *  to choose the data बारtamp to come.
 */
अटल व्योम inv_mpu6050_update_period(काष्ठा inv_mpu6050_state *st,
				      s64 बारtamp, माप_प्रकार nb)
अणु
	/* Period boundaries क्रम accepting बारtamp */
	स्थिर s64 period_min =
		(NSEC_PER_MSEC * (100 - INV_MPU6050_TS_PERIOD_JITTER)) / 100;
	स्थिर s64 period_max =
		(NSEC_PER_MSEC * (100 + INV_MPU6050_TS_PERIOD_JITTER)) / 100;
	स्थिर s32 भागider = INV_MPU6050_FREQ_DIVIDER(st);
	s64 delta, पूर्णांकerval;
	bool use_it_बारtamp = false;

	अगर (st->it_बारtamp == 0) अणु
		/* not initialized, क्रमced to use it_बारtamp */
		use_it_बारtamp = true;
	पूर्ण अन्यथा अगर (nb == 1) अणु
		/*
		 * Validate the use of it बारtamp by checking अगर पूर्णांकerrupt
		 * has been delayed.
		 * nb > 1 means पूर्णांकerrupt was delayed क्रम more than 1 sample,
		 * so it's obviously not good.
		 * Compute the chip period between 2 पूर्णांकerrupts क्रम validating.
		 */
		delta = भाग_s64(बारtamp - st->it_बारtamp, भागider);
		अगर (delta > period_min && delta < period_max) अणु
			/* update chip period and use it बारtamp */
			st->chip_period = (st->chip_period + delta) / 2;
			use_it_बारtamp = true;
		पूर्ण
	पूर्ण

	अगर (use_it_बारtamp) अणु
		/*
		 * Manage हाल of multiple samples in the fअगरo (nb > 1):
		 * compute बारtamp corresponding to the first sample using
		 * estimated chip period.
		 */
		पूर्णांकerval = (nb - 1) * st->chip_period * भागider;
		st->data_बारtamp = बारtamp - पूर्णांकerval;
	पूर्ण

	/* save it बारtamp */
	st->it_बारtamp = बारtamp;
पूर्ण

/**
 *  inv_mpu6050_get_बारtamp() - Return the current data बारtamp
 *
 *  @st:		driver state
 *  @वापस:		current data बारtamp
 *
 *  This function वापसs the current data बारtamp and prepares क्रम next one.
 */
अटल s64 inv_mpu6050_get_बारtamp(काष्ठा inv_mpu6050_state *st)
अणु
	s64 ts;

	/* वापस current data बारtamp and increment */
	ts = st->data_बारtamp;
	st->data_बारtamp += st->chip_period * INV_MPU6050_FREQ_DIVIDER(st);

	वापस ts;
पूर्ण

अटल पूर्णांक inv_reset_fअगरo(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक result;
	काष्ठा inv_mpu6050_state  *st = iio_priv(indio_dev);

	/* disable fअगरo and reenable it */
	inv_mpu6050_prepare_fअगरo(st, false);
	result = inv_mpu6050_prepare_fअगरo(st, true);
	अगर (result)
		जाओ reset_fअगरo_fail;

	वापस 0;

reset_fअगरo_fail:
	dev_err(regmap_get_device(st->map), "reset fifo failed %d\n", result);
	result = regmap_ग_लिखो(st->map, st->reg->पूर्णांक_enable,
			      INV_MPU6050_BIT_DATA_RDY_EN);

	वापस result;
पूर्ण

/*
 * inv_mpu6050_पढ़ो_fअगरo() - Transfer data from hardware FIFO to KFIFO.
 */
irqवापस_t inv_mpu6050_पढ़ो_fअगरo(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा inv_mpu6050_state *st = iio_priv(indio_dev);
	माप_प्रकार bytes_per_datum;
	पूर्णांक result;
	u16 fअगरo_count;
	s64 बारtamp;
	पूर्णांक पूर्णांक_status;
	माप_प्रकार i, nb;

	mutex_lock(&st->lock);

	/* ack पूर्णांकerrupt and check status */
	result = regmap_पढ़ो(st->map, st->reg->पूर्णांक_status, &पूर्णांक_status);
	अगर (result) अणु
		dev_err(regmap_get_device(st->map),
			"failed to ack interrupt\n");
		जाओ flush_fअगरo;
	पूर्ण
	अगर (!(पूर्णांक_status & INV_MPU6050_BIT_RAW_DATA_RDY_INT))
		जाओ end_session;

	अगर (!(st->chip_config.accl_fअगरo_enable |
		st->chip_config.gyro_fअगरo_enable |
		st->chip_config.magn_fअगरo_enable))
		जाओ end_session;
	bytes_per_datum = 0;
	अगर (st->chip_config.accl_fअगरo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_3AXIS_SENSOR;

	अगर (st->chip_config.gyro_fअगरo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_3AXIS_SENSOR;

	अगर (st->chip_config.temp_fअगरo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_TEMP_SENSOR;

	अगर (st->chip_config.magn_fअगरo_enable)
		bytes_per_datum += INV_MPU9X50_BYTES_MAGN;

	/*
	 * पढ़ो fअगरo_count रेजिस्टर to know how many bytes are inside the FIFO
	 * right now
	 */
	result = regmap_bulk_पढ़ो(st->map, st->reg->fअगरo_count_h,
				  st->data, INV_MPU6050_FIFO_COUNT_BYTE);
	अगर (result)
		जाओ end_session;
	fअगरo_count = be16_to_cpup((__be16 *)&st->data[0]);

	/*
	 * Handle fअगरo overflow by resetting fअगरo.
	 * Reset अगर there is only 3 data set मुक्त reमुख्यing to mitigate
	 * possible delay between पढ़ोing fअगरo count and fअगरo data.
	 */
	nb = 3 * bytes_per_datum;
	अगर (fअगरo_count >= st->hw->fअगरo_size - nb) अणु
		dev_warn(regmap_get_device(st->map), "fifo overflow reset\n");
		जाओ flush_fअगरo;
	पूर्ण

	/* compute and process all complete datum */
	nb = fअगरo_count / bytes_per_datum;
	inv_mpu6050_update_period(st, pf->बारtamp, nb);
	क्रम (i = 0; i < nb; ++i) अणु
		result = regmap_noinc_पढ़ो(st->map, st->reg->fअगरo_r_w,
					   st->data, bytes_per_datum);
		अगर (result)
			जाओ flush_fअगरo;
		/* skip first samples अगर needed */
		अगर (st->skip_samples) अणु
			st->skip_samples--;
			जारी;
		पूर्ण
		बारtamp = inv_mpu6050_get_बारtamp(st);
		iio_push_to_buffers_with_बारtamp(indio_dev, st->data, बारtamp);
	पूर्ण

end_session:
	mutex_unlock(&st->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;

flush_fअगरo:
	/* Flush HW and SW FIFOs. */
	inv_reset_fअगरo(indio_dev);
	mutex_unlock(&st->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण
