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
#समावेश <linux/iio/iपन.स>

#समावेश "inv_icm42600.h"
#समावेश "inv_icm42600_temp.h"

अटल पूर्णांक inv_icm42600_temp_पढ़ो(काष्ठा inv_icm42600_state *st, पूर्णांक16_t *temp)
अणु
	काष्ठा device *dev = regmap_get_device(st->map);
	__be16 *raw;
	पूर्णांक ret;

	pm_runसमय_get_sync(dev);
	mutex_lock(&st->lock);

	ret = inv_icm42600_set_temp_conf(st, true, शून्य);
	अगर (ret)
		जाओ निकास;

	raw = (__be16 *)&st->buffer[0];
	ret = regmap_bulk_पढ़ो(st->map, INV_ICM42600_REG_TEMP_DATA, raw, माप(*raw));
	अगर (ret)
		जाओ निकास;

	*temp = (पूर्णांक16_t)be16_to_cpup(raw);
	अगर (*temp == INV_ICM42600_DATA_INVALID)
		ret = -EINVAL;

निकास:
	mutex_unlock(&st->lock);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

पूर्णांक inv_icm42600_temp_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	पूर्णांक16_t temp;
	पूर्णांक ret;

	अगर (chan->type != IIO_TEMP)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = inv_icm42600_temp_पढ़ो(st, &temp);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		*val = temp;
		वापस IIO_VAL_INT;
	/*
	 * TतओC = (temp / 132.48) + 25
	 * TmतओC = 1000 * ((temp * 100 / 13248) + 25)
	 * scale: 100000 / 13248 ~= 7.548309
	 * offset: 25000
	 */
	हाल IIO_CHAN_INFO_SCALE:
		*val = 7;
		*val2 = 548309;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = 25000;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
