<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xilinx XADC driver
 *
 * Copyright 2013 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/kernel.h>

#समावेश "xilinx-xadc.h"

अटल स्थिर काष्ठा iio_chan_spec *xadc_event_to_channel(
	काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक event)
अणु
	चयन (event) अणु
	हाल XADC_THRESHOLD_OT_MAX:
	हाल XADC_THRESHOLD_TEMP_MAX:
		वापस &indio_dev->channels[0];
	हाल XADC_THRESHOLD_VCCपूर्णांक_उच्च:
	हाल XADC_THRESHOLD_VCCAUX_MAX:
		वापस &indio_dev->channels[event];
	शेष:
		वापस &indio_dev->channels[event-1];
	पूर्ण
पूर्ण

अटल व्योम xadc_handle_event(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक event)
अणु
	स्थिर काष्ठा iio_chan_spec *chan;

	/* Temperature threshold error, we करोn't handle this yet */
	अगर (event == 0)
		वापस;

	chan = xadc_event_to_channel(indio_dev, event);

	अगर (chan->type == IIO_TEMP) अणु
		/*
		 * The temperature channel only supports over-temperature
		 * events.
		 */
		iio_push_event(indio_dev,
			IIO_UNMOD_EVENT_CODE(chan->type, chan->channel,
				IIO_EV_TYPE_THRESH, IIO_EV_सूची_RISING),
			iio_get_समय_ns(indio_dev));
	पूर्ण अन्यथा अणु
		/*
		 * For other channels we करोn't know whether it is a upper or
		 * lower threshold event. Userspace will have to check the
		 * channel value अगर it wants to know.
		 */
		iio_push_event(indio_dev,
			IIO_UNMOD_EVENT_CODE(chan->type, chan->channel,
				IIO_EV_TYPE_THRESH, IIO_EV_सूची_EITHER),
			iio_get_समय_ns(indio_dev));
	पूर्ण
पूर्ण

व्योम xadc_handle_events(काष्ठा iio_dev *indio_dev, अचिन्हित दीर्घ events)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_set_bit(i, &events, 8)
		xadc_handle_event(indio_dev, i);
पूर्ण

अटल अचिन्हित पूर्णांक xadc_get_threshold_offset(स्थिर काष्ठा iio_chan_spec *chan,
	क्रमागत iio_event_direction dir)
अणु
	अचिन्हित पूर्णांक offset;

	अगर (chan->type == IIO_TEMP) अणु
		offset = XADC_THRESHOLD_OT_MAX;
	पूर्ण अन्यथा अणु
		अगर (chan->channel < 2)
			offset = chan->channel + 1;
		अन्यथा
			offset = chan->channel + 6;
	पूर्ण

	अगर (dir == IIO_EV_सूची_FALLING)
		offset += 4;

	वापस offset;
पूर्ण

अटल अचिन्हित पूर्णांक xadc_get_alarm_mask(स्थिर काष्ठा iio_chan_spec *chan)
अणु
	अगर (chan->type == IIO_TEMP)
		वापस XADC_ALARM_OT_MASK;
	चयन (chan->channel) अणु
	हाल 0:
		वापस XADC_ALARM_VCCINT_MASK;
	हाल 1:
		वापस XADC_ALARM_VCCAUX_MASK;
	हाल 2:
		वापस XADC_ALARM_VCCBRAM_MASK;
	हाल 3:
		वापस XADC_ALARM_VCCPINT_MASK;
	हाल 4:
		वापस XADC_ALARM_VCCPAUX_MASK;
	हाल 5:
		वापस XADC_ALARM_VCCODDR_MASK;
	शेष:
		/* We will never get here */
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक xadc_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir)
अणु
	काष्ठा xadc *xadc = iio_priv(indio_dev);

	वापस (bool)(xadc->alarm_mask & xadc_get_alarm_mask(chan));
पूर्ण

पूर्णांक xadc_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	अचिन्हित पूर्णांक alarm = xadc_get_alarm_mask(chan);
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	uपूर्णांक16_t cfg, old_cfg;
	पूर्णांक ret;

	mutex_lock(&xadc->mutex);

	अगर (state)
		xadc->alarm_mask |= alarm;
	अन्यथा
		xadc->alarm_mask &= ~alarm;

	xadc->ops->update_alarm(xadc, xadc->alarm_mask);

	ret = _xadc_पढ़ो_adc_reg(xadc, XADC_REG_CONF1, &cfg);
	अगर (ret)
		जाओ err_out;

	old_cfg = cfg;
	cfg |= XADC_CONF1_ALARM_MASK;
	cfg &= ~((xadc->alarm_mask & 0xf0) << 4); /* bram, pपूर्णांक, paux, ddr */
	cfg &= ~((xadc->alarm_mask & 0x08) >> 3); /* ot */
	cfg &= ~((xadc->alarm_mask & 0x07) << 1); /* temp, vccपूर्णांक, vccaux */
	अगर (old_cfg != cfg)
		ret = _xadc_ग_लिखो_adc_reg(xadc, XADC_REG_CONF1, cfg);

err_out:
	mutex_unlock(&xadc->mutex);

	वापस ret;
पूर्ण

पूर्णांक xadc_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
	पूर्णांक *val, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक offset = xadc_get_threshold_offset(chan, dir);
	काष्ठा xadc *xadc = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		*val = xadc->threshold[offset];
		अवरोध;
	हाल IIO_EV_INFO_HYSTERESIS:
		*val = xadc->temp_hysteresis;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* MSB aligned */
	*val >>= 16 - chan->scan_type.realbits;

	वापस IIO_VAL_INT;
पूर्ण

पूर्णांक xadc_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
	पूर्णांक val, पूर्णांक val2)
अणु
	अचिन्हित पूर्णांक offset = xadc_get_threshold_offset(chan, dir);
	काष्ठा xadc *xadc = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	/* MSB aligned */
	val <<= 16 - chan->scan_type.realbits;

	अगर (val < 0 || val > 0xffff)
		वापस -EINVAL;

	mutex_lock(&xadc->mutex);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		xadc->threshold[offset] = val;
		अवरोध;
	हाल IIO_EV_INFO_HYSTERESIS:
		xadc->temp_hysteresis = val;
		अवरोध;
	शेष:
		mutex_unlock(&xadc->mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (chan->type == IIO_TEMP) अणु
		/*
		 * According to the datasheet we need to set the lower 4 bits to
		 * 0x3, otherwise 125 degree celsius will be used as the
		 * threshold.
		 */
		val |= 0x3;

		/*
		 * Since we store the hysteresis as relative (to the threshold)
		 * value, but the hardware expects an असलolute value we need to
		 * recalcualte this value whenever the hysteresis or the
		 * threshold changes.
		 */
		अगर (xadc->threshold[offset] < xadc->temp_hysteresis)
			xadc->threshold[offset + 4] = 0;
		अन्यथा
			xadc->threshold[offset + 4] = xadc->threshold[offset] -
					xadc->temp_hysteresis;
		ret = _xadc_ग_लिखो_adc_reg(xadc, XADC_REG_THRESHOLD(offset + 4),
			xadc->threshold[offset + 4]);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	अगर (info == IIO_EV_INFO_VALUE)
		ret = _xadc_ग_लिखो_adc_reg(xadc, XADC_REG_THRESHOLD(offset), val);

out_unlock:
	mutex_unlock(&xadc->mutex);

	वापस ret;
पूर्ण
