<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Invensense, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>

#समावेश "inv_icm42600.h"
#समावेश "inv_icm42600_timestamp.h"
#समावेश "inv_icm42600_buffer.h"

/* FIFO header: 1 byte */
#घोषणा INV_ICM42600_FIFO_HEADER_MSG		BIT(7)
#घोषणा INV_ICM42600_FIFO_HEADER_ACCEL		BIT(6)
#घोषणा INV_ICM42600_FIFO_HEADER_GYRO		BIT(5)
#घोषणा INV_ICM42600_FIFO_HEADER_TMST_FSYNC	GENMASK(3, 2)
#घोषणा INV_ICM42600_FIFO_HEADER_ODR_ACCEL	BIT(1)
#घोषणा INV_ICM42600_FIFO_HEADER_ODR_GYRO	BIT(0)

काष्ठा inv_icm42600_fअगरo_1sensor_packet अणु
	uपूर्णांक8_t header;
	काष्ठा inv_icm42600_fअगरo_sensor_data data;
	पूर्णांक8_t temp;
पूर्ण __packed;
#घोषणा INV_ICM42600_FIFO_1SENSOR_PACKET_SIZE		8

काष्ठा inv_icm42600_fअगरo_2sensors_packet अणु
	uपूर्णांक8_t header;
	काष्ठा inv_icm42600_fअगरo_sensor_data accel;
	काष्ठा inv_icm42600_fअगरo_sensor_data gyro;
	पूर्णांक8_t temp;
	__be16 बारtamp;
पूर्ण __packed;
#घोषणा INV_ICM42600_FIFO_2SENSORS_PACKET_SIZE		16

sमाप_प्रकार inv_icm42600_fअगरo_decode_packet(स्थिर व्योम *packet, स्थिर व्योम **accel,
					स्थिर व्योम **gyro, स्थिर पूर्णांक8_t **temp,
					स्थिर व्योम **बारtamp, अचिन्हित पूर्णांक *odr)
अणु
	स्थिर काष्ठा inv_icm42600_fअगरo_1sensor_packet *pack1 = packet;
	स्थिर काष्ठा inv_icm42600_fअगरo_2sensors_packet *pack2 = packet;
	uपूर्णांक8_t header = *((स्थिर uपूर्णांक8_t *)packet);

	/* FIFO empty */
	अगर (header & INV_ICM42600_FIFO_HEADER_MSG) अणु
		*accel = शून्य;
		*gyro = शून्य;
		*temp = शून्य;
		*बारtamp = शून्य;
		*odr = 0;
		वापस 0;
	पूर्ण

	/* handle odr flags */
	*odr = 0;
	अगर (header & INV_ICM42600_FIFO_HEADER_ODR_GYRO)
		*odr |= INV_ICM42600_SENSOR_GYRO;
	अगर (header & INV_ICM42600_FIFO_HEADER_ODR_ACCEL)
		*odr |= INV_ICM42600_SENSOR_ACCEL;

	/* accel + gyro */
	अगर ((header & INV_ICM42600_FIFO_HEADER_ACCEL) &&
	    (header & INV_ICM42600_FIFO_HEADER_GYRO)) अणु
		*accel = &pack2->accel;
		*gyro = &pack2->gyro;
		*temp = &pack2->temp;
		*बारtamp = &pack2->बारtamp;
		वापस INV_ICM42600_FIFO_2SENSORS_PACKET_SIZE;
	पूर्ण

	/* accel only */
	अगर (header & INV_ICM42600_FIFO_HEADER_ACCEL) अणु
		*accel = &pack1->data;
		*gyro = शून्य;
		*temp = &pack1->temp;
		*बारtamp = शून्य;
		वापस INV_ICM42600_FIFO_1SENSOR_PACKET_SIZE;
	पूर्ण

	/* gyro only */
	अगर (header & INV_ICM42600_FIFO_HEADER_GYRO) अणु
		*accel = शून्य;
		*gyro = &pack1->data;
		*temp = &pack1->temp;
		*बारtamp = शून्य;
		वापस INV_ICM42600_FIFO_1SENSOR_PACKET_SIZE;
	पूर्ण

	/* invalid packet अगर here */
	वापस -EINVAL;
पूर्ण

व्योम inv_icm42600_buffer_update_fअगरo_period(काष्ठा inv_icm42600_state *st)
अणु
	uपूर्णांक32_t period_gyro, period_accel, period;

	अगर (st->fअगरo.en & INV_ICM42600_SENSOR_GYRO)
		period_gyro = inv_icm42600_odr_to_period(st->conf.gyro.odr);
	अन्यथा
		period_gyro = U32_MAX;

	अगर (st->fअगरo.en & INV_ICM42600_SENSOR_ACCEL)
		period_accel = inv_icm42600_odr_to_period(st->conf.accel.odr);
	अन्यथा
		period_accel = U32_MAX;

	अगर (period_gyro <= period_accel)
		period = period_gyro;
	अन्यथा
		period = period_accel;

	st->fअगरo.period = period;
पूर्ण

पूर्णांक inv_icm42600_buffer_set_fअगरo_en(काष्ठा inv_icm42600_state *st,
				    अचिन्हित पूर्णांक fअगरo_en)
अणु
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक ret;

	/* update only FIFO EN bits */
	mask = INV_ICM42600_FIFO_CONFIG1_TMST_FSYNC_EN |
		INV_ICM42600_FIFO_CONFIG1_TEMP_EN |
		INV_ICM42600_FIFO_CONFIG1_GYRO_EN |
		INV_ICM42600_FIFO_CONFIG1_ACCEL_EN;

	val = 0;
	अगर (fअगरo_en & INV_ICM42600_SENSOR_GYRO)
		val |= INV_ICM42600_FIFO_CONFIG1_GYRO_EN;
	अगर (fअगरo_en & INV_ICM42600_SENSOR_ACCEL)
		val |= INV_ICM42600_FIFO_CONFIG1_ACCEL_EN;
	अगर (fअगरo_en & INV_ICM42600_SENSOR_TEMP)
		val |= INV_ICM42600_FIFO_CONFIG1_TEMP_EN;

	ret = regmap_update_bits(st->map, INV_ICM42600_REG_FIFO_CONFIG1, mask, val);
	अगर (ret)
		वापस ret;

	st->fअगरo.en = fअगरo_en;
	inv_icm42600_buffer_update_fअगरo_period(st);

	वापस 0;
पूर्ण

अटल माप_प्रकार inv_icm42600_get_packet_size(अचिन्हित पूर्णांक fअगरo_en)
अणु
	माप_प्रकार packet_size;

	अगर ((fअगरo_en & INV_ICM42600_SENSOR_GYRO) &&
	    (fअगरo_en & INV_ICM42600_SENSOR_ACCEL))
		packet_size = INV_ICM42600_FIFO_2SENSORS_PACKET_SIZE;
	अन्यथा
		packet_size = INV_ICM42600_FIFO_1SENSOR_PACKET_SIZE;

	वापस packet_size;
पूर्ण

अटल अचिन्हित पूर्णांक inv_icm42600_wm_truncate(अचिन्हित पूर्णांक watermark,
					     माप_प्रकार packet_size)
अणु
	माप_प्रकार wm_size;
	अचिन्हित पूर्णांक wm;

	wm_size = watermark * packet_size;
	अगर (wm_size > INV_ICM42600_FIFO_WATERMARK_MAX)
		wm_size = INV_ICM42600_FIFO_WATERMARK_MAX;

	wm = wm_size / packet_size;

	वापस wm;
पूर्ण

/**
 * inv_icm42600_buffer_update_watermark - update watermark FIFO threshold
 * @st:	driver पूर्णांकernal state
 *
 * Returns 0 on success, a negative error code otherwise.
 *
 * FIFO watermark threshold is computed based on the required watermark values
 * set क्रम gyro and accel sensors. Since watermark is all about acceptable data
 * latency, use the smallest setting between the 2. It means choosing the
 * smallest latency but this is not as simple as choosing the smallest watermark
 * value. Latency depends on watermark and ODR. It requires several steps:
 * 1) compute gyro and accel latencies and choose the smallest value.
 * 2) adapt the choosen latency so that it is a multiple of both gyro and accel
 *    ones. Otherwise it is possible that you करोn't meet a requirement. (क्रम
 *    example with gyro @100Hz wm 4 and accel @100Hz with wm 6, choosing the
 *    value of 4 will not meet accel latency requirement because 6 is not a
 *    multiple of 4. You need to use the value 2.)
 * 3) Since all periods are multiple of each others, watermark is computed by
 *    भागiding this computed latency by the smallest period, which corresponds
 *    to the FIFO frequency. Beware that this is only true because we are not
 *    using 500Hz frequency which is not a multiple of the others.
 */
पूर्णांक inv_icm42600_buffer_update_watermark(काष्ठा inv_icm42600_state *st)
अणु
	माप_प्रकार packet_size, wm_size;
	अचिन्हित पूर्णांक wm_gyro, wm_accel, watermark;
	uपूर्णांक32_t period_gyro, period_accel, period;
	uपूर्णांक32_t latency_gyro, latency_accel, latency;
	bool restore;
	__le16 raw_wm;
	पूर्णांक ret;

	packet_size = inv_icm42600_get_packet_size(st->fअगरo.en);

	/* compute sensors latency, depending on sensor watermark and odr */
	wm_gyro = inv_icm42600_wm_truncate(st->fअगरo.watermark.gyro, packet_size);
	wm_accel = inv_icm42600_wm_truncate(st->fअगरo.watermark.accel, packet_size);
	/* use us क्रम odr to aव्योम overflow using 32 bits values */
	period_gyro = inv_icm42600_odr_to_period(st->conf.gyro.odr) / 1000UL;
	period_accel = inv_icm42600_odr_to_period(st->conf.accel.odr) / 1000UL;
	latency_gyro = period_gyro * wm_gyro;
	latency_accel = period_accel * wm_accel;

	/* 0 value क्रम watermark means that the sensor is turned off */
	अगर (latency_gyro == 0) अणु
		watermark = wm_accel;
	पूर्ण अन्यथा अगर (latency_accel == 0) अणु
		watermark = wm_gyro;
	पूर्ण अन्यथा अणु
		/* compute the smallest latency that is a multiple of both */
		अगर (latency_gyro <= latency_accel)
			latency = latency_gyro - (latency_accel % latency_gyro);
		अन्यथा
			latency = latency_accel - (latency_gyro % latency_accel);
		/* use the लघुest period */
		अगर (period_gyro <= period_accel)
			period = period_gyro;
		अन्यथा
			period = period_accel;
		/* all this works because periods are multiple of each others */
		watermark = latency / period;
		अगर (watermark < 1)
			watermark = 1;
	पूर्ण

	/* compute watermark value in bytes */
	wm_size = watermark * packet_size;

	/* changing FIFO watermark requires to turn off watermark पूर्णांकerrupt */
	ret = regmap_update_bits_check(st->map, INV_ICM42600_REG_INT_SOURCE0,
				       INV_ICM42600_INT_SOURCE0_FIFO_THS_INT1_EN,
				       0, &restore);
	अगर (ret)
		वापस ret;

	raw_wm = INV_ICM42600_FIFO_WATERMARK_VAL(wm_size);
	स_नकल(st->buffer, &raw_wm, माप(raw_wm));
	ret = regmap_bulk_ग_लिखो(st->map, INV_ICM42600_REG_FIFO_WATERMARK,
				st->buffer, माप(raw_wm));
	अगर (ret)
		वापस ret;

	/* restore watermark पूर्णांकerrupt */
	अगर (restore) अणु
		ret = regmap_update_bits(st->map, INV_ICM42600_REG_INT_SOURCE0,
					 INV_ICM42600_INT_SOURCE0_FIFO_THS_INT1_EN,
					 INV_ICM42600_INT_SOURCE0_FIFO_THS_INT1_EN);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inv_icm42600_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	काष्ठा device *dev = regmap_get_device(st->map);

	pm_runसमय_get_sync(dev);

	वापस 0;
पूर्ण

/*
 * update_scan_mode callback is turning sensors on and setting data FIFO enable
 * bits.
 */
अटल पूर्णांक inv_icm42600_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	/* निकास अगर FIFO is alपढ़ोy on */
	अगर (st->fअगरo.on) अणु
		ret = 0;
		जाओ out_on;
	पूर्ण

	/* set FIFO threshold पूर्णांकerrupt */
	ret = regmap_update_bits(st->map, INV_ICM42600_REG_INT_SOURCE0,
				 INV_ICM42600_INT_SOURCE0_FIFO_THS_INT1_EN,
				 INV_ICM42600_INT_SOURCE0_FIFO_THS_INT1_EN);
	अगर (ret)
		जाओ out_unlock;

	/* flush FIFO data */
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_SIGNAL_PATH_RESET,
			   INV_ICM42600_SIGNAL_PATH_RESET_FIFO_FLUSH);
	अगर (ret)
		जाओ out_unlock;

	/* set FIFO in streaming mode */
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_FIFO_CONFIG,
			   INV_ICM42600_FIFO_CONFIG_STREAM);
	अगर (ret)
		जाओ out_unlock;

	/* workaround: first पढ़ो of FIFO count after reset is always 0 */
	ret = regmap_bulk_पढ़ो(st->map, INV_ICM42600_REG_FIFO_COUNT, st->buffer, 2);
	अगर (ret)
		जाओ out_unlock;

out_on:
	/* increase FIFO on counter */
	st->fअगरo.on++;
out_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक inv_icm42600_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	/* निकास अगर there are several sensors using the FIFO */
	अगर (st->fअगरo.on > 1) अणु
		ret = 0;
		जाओ out_off;
	पूर्ण

	/* set FIFO in bypass mode */
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_FIFO_CONFIG,
			   INV_ICM42600_FIFO_CONFIG_BYPASS);
	अगर (ret)
		जाओ out_unlock;

	/* flush FIFO data */
	ret = regmap_ग_लिखो(st->map, INV_ICM42600_REG_SIGNAL_PATH_RESET,
			   INV_ICM42600_SIGNAL_PATH_RESET_FIFO_FLUSH);
	अगर (ret)
		जाओ out_unlock;

	/* disable FIFO threshold पूर्णांकerrupt */
	ret = regmap_update_bits(st->map, INV_ICM42600_REG_INT_SOURCE0,
				 INV_ICM42600_INT_SOURCE0_FIFO_THS_INT1_EN, 0);
	अगर (ret)
		जाओ out_unlock;

out_off:
	/* decrease FIFO on counter */
	st->fअगरo.on--;
out_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक inv_icm42600_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	काष्ठा device *dev = regmap_get_device(st->map);
	अचिन्हित पूर्णांक sensor;
	अचिन्हित पूर्णांक *watermark;
	काष्ठा inv_icm42600_बारtamp *ts;
	काष्ठा inv_icm42600_sensor_conf conf = INV_ICM42600_SENSOR_CONF_INIT;
	अचिन्हित पूर्णांक sleep_temp = 0;
	अचिन्हित पूर्णांक sleep_sensor = 0;
	अचिन्हित पूर्णांक sleep;
	पूर्णांक ret;

	अगर (indio_dev == st->indio_gyro) अणु
		sensor = INV_ICM42600_SENSOR_GYRO;
		watermark = &st->fअगरo.watermark.gyro;
		ts = iio_priv(st->indio_gyro);
	पूर्ण अन्यथा अगर (indio_dev == st->indio_accel) अणु
		sensor = INV_ICM42600_SENSOR_ACCEL;
		watermark = &st->fअगरo.watermark.accel;
		ts = iio_priv(st->indio_accel);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&st->lock);

	ret = inv_icm42600_buffer_set_fअगरo_en(st, st->fअगरo.en & ~sensor);
	अगर (ret)
		जाओ out_unlock;

	*watermark = 0;
	ret = inv_icm42600_buffer_update_watermark(st);
	अगर (ret)
		जाओ out_unlock;

	conf.mode = INV_ICM42600_SENSOR_MODE_OFF;
	अगर (sensor == INV_ICM42600_SENSOR_GYRO)
		ret = inv_icm42600_set_gyro_conf(st, &conf, &sleep_sensor);
	अन्यथा
		ret = inv_icm42600_set_accel_conf(st, &conf, &sleep_sensor);
	अगर (ret)
		जाओ out_unlock;

	/* अगर FIFO is off, turn temperature off */
	अगर (!st->fअगरo.on)
		ret = inv_icm42600_set_temp_conf(st, false, &sleep_temp);

	inv_icm42600_बारtamp_reset(ts);

out_unlock:
	mutex_unlock(&st->lock);

	/* sleep maximum required समय */
	अगर (sleep_sensor > sleep_temp)
		sleep = sleep_sensor;
	अन्यथा
		sleep = sleep_temp;
	अगर (sleep)
		msleep(sleep);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

स्थिर काष्ठा iio_buffer_setup_ops inv_icm42600_buffer_ops = अणु
	.preenable = inv_icm42600_buffer_preenable,
	.postenable = inv_icm42600_buffer_postenable,
	.predisable = inv_icm42600_buffer_predisable,
	.postdisable = inv_icm42600_buffer_postdisable,
पूर्ण;

पूर्णांक inv_icm42600_buffer_fअगरo_पढ़ो(काष्ठा inv_icm42600_state *st,
				  अचिन्हित पूर्णांक max)
अणु
	माप_प्रकार max_count;
	__be16 *raw_fअगरo_count;
	sमाप_प्रकार i, size;
	स्थिर व्योम *accel, *gyro, *बारtamp;
	स्थिर पूर्णांक8_t *temp;
	अचिन्हित पूर्णांक odr;
	पूर्णांक ret;

	/* reset all samples counters */
	st->fअगरo.count = 0;
	st->fअगरo.nb.gyro = 0;
	st->fअगरo.nb.accel = 0;
	st->fअगरo.nb.total = 0;

	/* compute maximum FIFO पढ़ो size */
	अगर (max == 0)
		max_count = माप(st->fअगरo.data);
	अन्यथा
		max_count = max * inv_icm42600_get_packet_size(st->fअगरo.en);

	/* पढ़ो FIFO count value */
	raw_fअगरo_count = (__be16 *)st->buffer;
	ret = regmap_bulk_पढ़ो(st->map, INV_ICM42600_REG_FIFO_COUNT,
			       raw_fअगरo_count, माप(*raw_fअगरo_count));
	अगर (ret)
		वापस ret;
	st->fअगरo.count = be16_to_cpup(raw_fअगरo_count);

	/* check and clamp FIFO count value */
	अगर (st->fअगरo.count == 0)
		वापस 0;
	अगर (st->fअगरo.count > max_count)
		st->fअगरo.count = max_count;

	/* पढ़ो all FIFO data in पूर्णांकernal buffer */
	ret = regmap_noinc_पढ़ो(st->map, INV_ICM42600_REG_FIFO_DATA,
				st->fअगरo.data, st->fअगरo.count);
	अगर (ret)
		वापस ret;

	/* compute number of samples क्रम each sensor */
	क्रम (i = 0; i < st->fअगरo.count; i += size) अणु
		size = inv_icm42600_fअगरo_decode_packet(&st->fअगरo.data[i],
				&accel, &gyro, &temp, &बारtamp, &odr);
		अगर (size <= 0)
			अवरोध;
		अगर (gyro != शून्य && inv_icm42600_fअगरo_is_data_valid(gyro))
			st->fअगरo.nb.gyro++;
		अगर (accel != शून्य && inv_icm42600_fअगरo_is_data_valid(accel))
			st->fअगरo.nb.accel++;
		st->fअगरo.nb.total++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक inv_icm42600_buffer_fअगरo_parse(काष्ठा inv_icm42600_state *st)
अणु
	काष्ठा inv_icm42600_बारtamp *ts;
	पूर्णांक ret;

	अगर (st->fअगरo.nb.total == 0)
		वापस 0;

	/* handle gyroscope बारtamp and FIFO data parsing */
	ts = iio_priv(st->indio_gyro);
	inv_icm42600_बारtamp_पूर्णांकerrupt(ts, st->fअगरo.period, st->fअगरo.nb.total,
					 st->fअगरo.nb.gyro, st->बारtamp.gyro);
	अगर (st->fअगरo.nb.gyro > 0) अणु
		ret = inv_icm42600_gyro_parse_fअगरo(st->indio_gyro);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* handle accelerometer बारtamp and FIFO data parsing */
	ts = iio_priv(st->indio_accel);
	inv_icm42600_बारtamp_पूर्णांकerrupt(ts, st->fअगरo.period, st->fअगरo.nb.total,
					 st->fअगरo.nb.accel, st->बारtamp.accel);
	अगर (st->fअगरo.nb.accel > 0) अणु
		ret = inv_icm42600_accel_parse_fअगरo(st->indio_accel);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक inv_icm42600_buffer_hwfअगरo_flush(काष्ठा inv_icm42600_state *st,
				     अचिन्हित पूर्णांक count)
अणु
	काष्ठा inv_icm42600_बारtamp *ts;
	पूर्णांक64_t gyro_ts, accel_ts;
	पूर्णांक ret;

	gyro_ts = iio_get_समय_ns(st->indio_gyro);
	accel_ts = iio_get_समय_ns(st->indio_accel);

	ret = inv_icm42600_buffer_fअगरo_पढ़ो(st, count);
	अगर (ret)
		वापस ret;

	अगर (st->fअगरo.nb.total == 0)
		वापस 0;

	अगर (st->fअगरo.nb.gyro > 0) अणु
		ts = iio_priv(st->indio_gyro);
		inv_icm42600_बारtamp_पूर्णांकerrupt(ts, st->fअगरo.period,
						 st->fअगरo.nb.total, st->fअगरo.nb.gyro,
						 gyro_ts);
		ret = inv_icm42600_gyro_parse_fअगरo(st->indio_gyro);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (st->fअगरo.nb.accel > 0) अणु
		ts = iio_priv(st->indio_accel);
		inv_icm42600_बारtamp_पूर्णांकerrupt(ts, st->fअगरo.period,
						 st->fअगरo.nb.total, st->fअगरo.nb.accel,
						 accel_ts);
		ret = inv_icm42600_accel_parse_fअगरo(st->indio_accel);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक inv_icm42600_buffer_init(काष्ठा inv_icm42600_state *st)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/*
	 * Default FIFO configuration (bits 7 to 5)
	 * - use invalid value
	 * - FIFO count in bytes
	 * - FIFO count in big endian
	 */
	val = INV_ICM42600_INTF_CONFIG0_FIFO_COUNT_ENDIAN;
	ret = regmap_update_bits(st->map, INV_ICM42600_REG_INTF_CONFIG0,
				 GENMASK(7, 5), val);
	अगर (ret)
		वापस ret;

	/*
	 * Enable FIFO partial पढ़ो and continuous watermark पूर्णांकerrupt.
	 * Disable all FIFO EN bits.
	 */
	val = INV_ICM42600_FIFO_CONFIG1_RESUME_PARTIAL_RD |
	      INV_ICM42600_FIFO_CONFIG1_WM_GT_TH;
	वापस regmap_update_bits(st->map, INV_ICM42600_REG_FIFO_CONFIG1,
				  GENMASK(6, 5) | GENMASK(3, 0), val);
पूर्ण
