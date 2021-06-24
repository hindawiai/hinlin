<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Diolan DLN-2 USB-ADC adapter
 *
 * Copyright (c) 2017 Jack Andersen
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/dln2.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>

#घोषणा DLN2_ADC_MOD_NAME "dln2-adc"

#घोषणा DLN2_ADC_ID             0x06

#घोषणा DLN2_ADC_GET_CHANNEL_COUNT	DLN2_CMD(0x01, DLN2_ADC_ID)
#घोषणा DLN2_ADC_ENABLE			DLN2_CMD(0x02, DLN2_ADC_ID)
#घोषणा DLN2_ADC_DISABLE		DLN2_CMD(0x03, DLN2_ADC_ID)
#घोषणा DLN2_ADC_CHANNEL_ENABLE		DLN2_CMD(0x05, DLN2_ADC_ID)
#घोषणा DLN2_ADC_CHANNEL_DISABLE	DLN2_CMD(0x06, DLN2_ADC_ID)
#घोषणा DLN2_ADC_SET_RESOLUTION		DLN2_CMD(0x08, DLN2_ADC_ID)
#घोषणा DLN2_ADC_CHANNEL_GET_VAL	DLN2_CMD(0x0A, DLN2_ADC_ID)
#घोषणा DLN2_ADC_CHANNEL_GET_ALL_VAL	DLN2_CMD(0x0B, DLN2_ADC_ID)
#घोषणा DLN2_ADC_CHANNEL_SET_CFG	DLN2_CMD(0x0C, DLN2_ADC_ID)
#घोषणा DLN2_ADC_CHANNEL_GET_CFG	DLN2_CMD(0x0D, DLN2_ADC_ID)
#घोषणा DLN2_ADC_CONDITION_MET_EV	DLN2_CMD(0x10, DLN2_ADC_ID)

#घोषणा DLN2_ADC_EVENT_NONE		0
#घोषणा DLN2_ADC_EVENT_BELOW		1
#घोषणा DLN2_ADC_EVENT_LEVEL_ABOVE	2
#घोषणा DLN2_ADC_EVENT_OUTSIDE		3
#घोषणा DLN2_ADC_EVENT_INSIDE		4
#घोषणा DLN2_ADC_EVENT_ALWAYS		5

#घोषणा DLN2_ADC_MAX_CHANNELS 8
#घोषणा DLN2_ADC_DATA_BITS 10

/*
 * Plays similar role to iio_demux_table in subप्रणाली core; except allocated
 * in a fixed 8-element array.
 */
काष्ठा dln2_adc_demux_table अणु
	अचिन्हित पूर्णांक from;
	अचिन्हित पूर्णांक to;
	अचिन्हित पूर्णांक length;
पूर्ण;

काष्ठा dln2_adc अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा iio_chan_spec iio_channels[DLN2_ADC_MAX_CHANNELS + 1];
	पूर्णांक port, trigger_chan;
	काष्ठा iio_trigger *trig;
	काष्ठा mutex mutex;
	/* Cached sample period in milliseconds */
	अचिन्हित पूर्णांक sample_period;
	/* Demux table */
	अचिन्हित पूर्णांक demux_count;
	काष्ठा dln2_adc_demux_table demux[DLN2_ADC_MAX_CHANNELS];
	/* Precomputed बारtamp padding offset and length */
	अचिन्हित पूर्णांक ts_pad_offset, ts_pad_length;
पूर्ण;

काष्ठा dln2_adc_port_chan अणु
	u8 port;
	u8 chan;
पूर्ण;

काष्ठा dln2_adc_get_all_vals अणु
	__le16 channel_mask;
	__le16 values[DLN2_ADC_MAX_CHANNELS];
पूर्ण;

अटल व्योम dln2_adc_add_demux(काष्ठा dln2_adc *dln2,
	अचिन्हित पूर्णांक in_loc, अचिन्हित पूर्णांक out_loc,
	अचिन्हित पूर्णांक length)
अणु
	काष्ठा dln2_adc_demux_table *p = dln2->demux_count ?
		&dln2->demux[dln2->demux_count - 1] : शून्य;

	अगर (p && p->from + p->length == in_loc &&
		p->to + p->length == out_loc) अणु
		p->length += length;
	पूर्ण अन्यथा अगर (dln2->demux_count < DLN2_ADC_MAX_CHANNELS) अणु
		p = &dln2->demux[dln2->demux_count++];
		p->from = in_loc;
		p->to = out_loc;
		p->length = length;
	पूर्ण
पूर्ण

अटल व्योम dln2_adc_update_demux(काष्ठा dln2_adc *dln2)
अणु
	पूर्णांक in_ind = -1, out_ind;
	अचिन्हित पूर्णांक in_loc = 0, out_loc = 0;
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(dln2->pdev);

	/* Clear out any old demux */
	dln2->demux_count = 0;

	/* Optimize all 8-channels हाल */
	अगर (indio_dev->masklength &&
	    (*indio_dev->active_scan_mask & 0xff) == 0xff) अणु
		dln2_adc_add_demux(dln2, 0, 0, 16);
		dln2->ts_pad_offset = 0;
		dln2->ts_pad_length = 0;
		वापस;
	पूर्ण

	/* Build demux table from fixed 8-channels to active_scan_mask */
	क्रम_each_set_bit(out_ind,
			 indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		/* Handle बारtamp separately */
		अगर (out_ind == DLN2_ADC_MAX_CHANNELS)
			अवरोध;
		क्रम (++in_ind; in_ind != out_ind; ++in_ind)
			in_loc += 2;
		dln2_adc_add_demux(dln2, in_loc, out_loc, 2);
		out_loc += 2;
		in_loc += 2;
	पूर्ण

	अगर (indio_dev->scan_बारtamp) अणु
		माप_प्रकार ts_offset = indio_dev->scan_bytes / माप(पूर्णांक64_t) - 1;

		dln2->ts_pad_offset = out_loc;
		dln2->ts_pad_length = ts_offset * माप(पूर्णांक64_t) - out_loc;
	पूर्ण अन्यथा अणु
		dln2->ts_pad_offset = 0;
		dln2->ts_pad_length = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक dln2_adc_get_chan_count(काष्ठा dln2_adc *dln2)
अणु
	पूर्णांक ret;
	u8 port = dln2->port;
	u8 count;
	पूर्णांक olen = माप(count);

	ret = dln2_transfer(dln2->pdev, DLN2_ADC_GET_CHANNEL_COUNT,
			    &port, माप(port), &count, &olen);
	अगर (ret < 0) अणु
		dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);
		वापस ret;
	पूर्ण
	अगर (olen < माप(count))
		वापस -EPROTO;

	वापस count;
पूर्ण

अटल पूर्णांक dln2_adc_set_port_resolution(काष्ठा dln2_adc *dln2)
अणु
	पूर्णांक ret;
	काष्ठा dln2_adc_port_chan port_chan = अणु
		.port = dln2->port,
		.chan = DLN2_ADC_DATA_BITS,
	पूर्ण;

	ret = dln2_transfer_tx(dln2->pdev, DLN2_ADC_SET_RESOLUTION,
			       &port_chan, माप(port_chan));
	अगर (ret < 0)
		dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_adc_set_chan_enabled(काष्ठा dln2_adc *dln2,
				     पूर्णांक channel, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा dln2_adc_port_chan port_chan = अणु
		.port = dln2->port,
		.chan = channel,
	पूर्ण;
	u16 cmd = enable ? DLN2_ADC_CHANNEL_ENABLE : DLN2_ADC_CHANNEL_DISABLE;

	ret = dln2_transfer_tx(dln2->pdev, cmd, &port_chan, माप(port_chan));
	अगर (ret < 0)
		dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_adc_set_port_enabled(काष्ठा dln2_adc *dln2, bool enable,
				     u16 *conflict_out)
अणु
	पूर्णांक ret;
	u8 port = dln2->port;
	__le16 conflict;
	पूर्णांक olen = माप(conflict);
	u16 cmd = enable ? DLN2_ADC_ENABLE : DLN2_ADC_DISABLE;

	अगर (conflict_out)
		*conflict_out = 0;

	ret = dln2_transfer(dln2->pdev, cmd, &port, माप(port),
			    &conflict, &olen);
	अगर (ret < 0) अणु
		dev_dbg(&dln2->pdev->dev, "Problem in %s(%d)\n",
			__func__, (पूर्णांक)enable);
		अगर (conflict_out && enable && olen >= माप(conflict))
			*conflict_out = le16_to_cpu(conflict);
		वापस ret;
	पूर्ण
	अगर (enable && olen < माप(conflict))
		वापस -EPROTO;

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_adc_set_chan_period(काष्ठा dln2_adc *dln2,
	अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक period)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		काष्ठा dln2_adc_port_chan port_chan;
		__u8 type;
		__le16 period;
		__le16 low;
		__le16 high;
	पूर्ण __packed set_cfg = अणु
		.port_chan.port = dln2->port,
		.port_chan.chan = channel,
		.type = period ? DLN2_ADC_EVENT_ALWAYS : DLN2_ADC_EVENT_NONE,
		.period = cpu_to_le16(period)
	पूर्ण;

	ret = dln2_transfer_tx(dln2->pdev, DLN2_ADC_CHANNEL_SET_CFG,
			       &set_cfg, माप(set_cfg));
	अगर (ret < 0)
		dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_adc_पढ़ो(काष्ठा dln2_adc *dln2, अचिन्हित पूर्णांक channel)
अणु
	पूर्णांक ret, i;
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(dln2->pdev);
	u16 conflict;
	__le16 value;
	पूर्णांक olen = माप(value);
	काष्ठा dln2_adc_port_chan port_chan = अणु
		.port = dln2->port,
		.chan = channel,
	पूर्ण;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = dln2_adc_set_chan_enabled(dln2, channel, true);
	अगर (ret < 0)
		जाओ release_direct;

	ret = dln2_adc_set_port_enabled(dln2, true, &conflict);
	अगर (ret < 0) अणु
		अगर (conflict) अणु
			dev_err(&dln2->pdev->dev,
				"ADC pins conflict with mask %04X\n",
				(पूर्णांक)conflict);
			ret = -EBUSY;
		पूर्ण
		जाओ disable_chan;
	पूर्ण

	/*
	 * Call GET_VAL twice due to initial zero-वापस immediately after
	 * enabling channel.
	 */
	क्रम (i = 0; i < 2; ++i) अणु
		ret = dln2_transfer(dln2->pdev, DLN2_ADC_CHANNEL_GET_VAL,
				    &port_chan, माप(port_chan),
				    &value, &olen);
		अगर (ret < 0) अणु
			dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);
			जाओ disable_port;
		पूर्ण
		अगर (olen < माप(value)) अणु
			ret = -EPROTO;
			जाओ disable_port;
		पूर्ण
	पूर्ण

	ret = le16_to_cpu(value);

disable_port:
	dln2_adc_set_port_enabled(dln2, false, शून्य);
disable_chan:
	dln2_adc_set_chan_enabled(dln2, channel, false);
release_direct:
	iio_device_release_direct_mode(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_adc_पढ़ो_all(काष्ठा dln2_adc *dln2,
			     काष्ठा dln2_adc_get_all_vals *get_all_vals)
अणु
	पूर्णांक ret;
	__u8 port = dln2->port;
	पूर्णांक olen = माप(*get_all_vals);

	ret = dln2_transfer(dln2->pdev, DLN2_ADC_CHANNEL_GET_ALL_VAL,
			    &port, माप(port), get_all_vals, &olen);
	अगर (ret < 0) अणु
		dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);
		वापस ret;
	पूर्ण
	अगर (olen < माप(*get_all_vals))
		वापस -EPROTO;

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val,
			     पूर्णांक *val2,
			     दीर्घ mask)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक microhertz;
	काष्ठा dln2_adc *dln2 = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&dln2->mutex);
		ret = dln2_adc_पढ़ो(dln2, chan->channel);
		mutex_unlock(&dln2->mutex);

		अगर (ret < 0)
			वापस ret;

		*val = ret;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		/*
		 * Voltage reference is fixed at 3.3v
		 *  3.3 / (1 << 10) * 1000000000
		 */
		*val = 0;
		*val2 = 3222656;
		वापस IIO_VAL_INT_PLUS_न_अंकO;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (dln2->sample_period) अणु
			microhertz = 1000000000 / dln2->sample_period;
			*val = microhertz / 1000000;
			*val2 = microhertz % 1000000;
		पूर्ण अन्यथा अणु
			*val = 0;
			*val2 = 0;
		पूर्ण

		वापस IIO_VAL_INT_PLUS_MICRO;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dln2_adc_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val,
			      पूर्णांक val2,
			      दीर्घ mask)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक microhertz;
	काष्ठा dln2_adc *dln2 = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		microhertz = 1000000 * val + val2;

		mutex_lock(&dln2->mutex);

		dln2->sample_period =
			microhertz ? 1000000000 / microhertz : अच_पूर्णांक_उच्च;
		अगर (dln2->sample_period > 65535) अणु
			dln2->sample_period = 65535;
			dev_warn(&dln2->pdev->dev,
				 "clamping period to 65535ms\n");
		पूर्ण

		/*
		 * The first requested channel is arbitrated as a shared
		 * trigger source, so only one event is रेजिस्टरed with the
		 * DLN. The event handler will then पढ़ो all enabled channel
		 * values using DLN2_ADC_CHANNEL_GET_ALL_VAL to मुख्यtain
		 * synchronization between ADC पढ़ोings.
		 */
		अगर (dln2->trigger_chan != -1)
			ret = dln2_adc_set_chan_period(dln2,
				dln2->trigger_chan, dln2->sample_period);
		अन्यथा
			ret = 0;

		mutex_unlock(&dln2->mutex);

		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dln2_update_scan_mode(काष्ठा iio_dev *indio_dev,
				 स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा dln2_adc *dln2 = iio_priv(indio_dev);
	पूर्णांक chan_count = indio_dev->num_channels - 1;
	पूर्णांक ret, i, j;

	mutex_lock(&dln2->mutex);

	क्रम (i = 0; i < chan_count; ++i) अणु
		ret = dln2_adc_set_chan_enabled(dln2, i,
						test_bit(i, scan_mask));
		अगर (ret < 0) अणु
			क्रम (j = 0; j < i; ++j)
				dln2_adc_set_chan_enabled(dln2, j, false);
			mutex_unlock(&dln2->mutex);
			dev_err(&dln2->pdev->dev,
				"Unable to enable ADC channel %d\n", i);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	dln2_adc_update_demux(dln2);

	mutex_unlock(&dln2->mutex);

	वापस 0;
पूर्ण

#घोषणा DLN2_ADC_CHAN(lval, idx) अणु					\
	lval.type = IIO_VOLTAGE;					\
	lval.channel = idx;						\
	lval.indexed = 1;						\
	lval.info_mask_separate = BIT(IIO_CHAN_INFO_RAW);		\
	lval.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SCALE) |	\
				       BIT(IIO_CHAN_INFO_SAMP_FREQ);	\
	lval.scan_index = idx;						\
	lval.scan_type.sign = 'u';					\
	lval.scan_type.realbits = DLN2_ADC_DATA_BITS;			\
	lval.scan_type.storagebits = 16;				\
	lval.scan_type.endianness = IIO_LE;				\
पूर्ण

/* Assignment version of IIO_CHAN_SOFT_TIMESTAMP */
#घोषणा IIO_CHAN_SOFT_TIMESTAMP_ASSIGN(lval, _si) अणु	\
	lval.type = IIO_TIMESTAMP;			\
	lval.channel = -1;				\
	lval.scan_index = _si;				\
	lval.scan_type.sign = 's';			\
	lval.scan_type.realbits = 64;			\
	lval.scan_type.storagebits = 64;		\
पूर्ण

अटल स्थिर काष्ठा iio_info dln2_adc_info = अणु
	.पढ़ो_raw = dln2_adc_पढ़ो_raw,
	.ग_लिखो_raw = dln2_adc_ग_लिखो_raw,
	.update_scan_mode = dln2_update_scan_mode,
पूर्ण;

अटल irqवापस_t dln2_adc_trigger_h(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा अणु
		__le16 values[DLN2_ADC_MAX_CHANNELS];
		पूर्णांक64_t बारtamp_space;
	पूर्ण data;
	काष्ठा dln2_adc_get_all_vals dev_data;
	काष्ठा dln2_adc *dln2 = iio_priv(indio_dev);
	स्थिर काष्ठा dln2_adc_demux_table *t;
	पूर्णांक ret, i;

	mutex_lock(&dln2->mutex);
	ret = dln2_adc_पढ़ो_all(dln2, &dev_data);
	mutex_unlock(&dln2->mutex);
	अगर (ret < 0)
		जाओ करोne;

	/* Demux operation */
	क्रम (i = 0; i < dln2->demux_count; ++i) अणु
		t = &dln2->demux[i];
		स_नकल((व्योम *)data.values + t->to,
		       (व्योम *)dev_data.values + t->from, t->length);
	पूर्ण

	/* Zero padding space between values and बारtamp */
	अगर (dln2->ts_pad_length)
		स_रखो((व्योम *)data.values + dln2->ts_pad_offset,
		       0, dln2->ts_pad_length);

	iio_push_to_buffers_with_बारtamp(indio_dev, &data,
					   iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dln2_adc_triggered_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा dln2_adc *dln2 = iio_priv(indio_dev);
	u16 conflict;
	अचिन्हित पूर्णांक trigger_chan;

	mutex_lock(&dln2->mutex);

	/* Enable ADC */
	ret = dln2_adc_set_port_enabled(dln2, true, &conflict);
	अगर (ret < 0) अणु
		mutex_unlock(&dln2->mutex);
		dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);
		अगर (conflict) अणु
			dev_err(&dln2->pdev->dev,
				"ADC pins conflict with mask %04X\n",
				(पूर्णांक)conflict);
			ret = -EBUSY;
		पूर्ण
		वापस ret;
	पूर्ण

	/* Assign trigger channel based on first enabled channel */
	trigger_chan = find_first_bit(indio_dev->active_scan_mask,
				      indio_dev->masklength);
	अगर (trigger_chan < DLN2_ADC_MAX_CHANNELS) अणु
		dln2->trigger_chan = trigger_chan;
		ret = dln2_adc_set_chan_period(dln2, dln2->trigger_chan,
					       dln2->sample_period);
		mutex_unlock(&dln2->mutex);
		अगर (ret < 0) अणु
			dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dln2->trigger_chan = -1;
		mutex_unlock(&dln2->mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_adc_triggered_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा dln2_adc *dln2 = iio_priv(indio_dev);

	mutex_lock(&dln2->mutex);

	/* Disable trigger channel */
	अगर (dln2->trigger_chan != -1) अणु
		dln2_adc_set_chan_period(dln2, dln2->trigger_chan, 0);
		dln2->trigger_chan = -1;
	पूर्ण

	/* Disable ADC */
	ret = dln2_adc_set_port_enabled(dln2, false, शून्य);

	mutex_unlock(&dln2->mutex);
	अगर (ret < 0)
		dev_dbg(&dln2->pdev->dev, "Problem in %s\n", __func__);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops dln2_adc_buffer_setup_ops = अणु
	.postenable = dln2_adc_triggered_buffer_postenable,
	.predisable = dln2_adc_triggered_buffer_predisable,
पूर्ण;

अटल व्योम dln2_adc_event(काष्ठा platक्रमm_device *pdev, u16 echo,
			   स्थिर व्योम *data, पूर्णांक len)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा dln2_adc *dln2 = iio_priv(indio_dev);

	/* Called via URB completion handler */
	iio_trigger_poll(dln2->trig);
पूर्ण

अटल पूर्णांक dln2_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dln2_adc *dln2;
	काष्ठा dln2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा iio_dev *indio_dev;
	पूर्णांक i, ret, chans;

	indio_dev = devm_iio_device_alloc(dev, माप(*dln2));
	अगर (!indio_dev) अणु
		dev_err(dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	dln2 = iio_priv(indio_dev);
	dln2->pdev = pdev;
	dln2->port = pdata->port;
	dln2->trigger_chan = -1;
	mutex_init(&dln2->mutex);

	platक्रमm_set_drvdata(pdev, indio_dev);

	ret = dln2_adc_set_port_resolution(dln2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set ADC resolution to 10 bits\n");
		वापस ret;
	पूर्ण

	chans = dln2_adc_get_chan_count(dln2);
	अगर (chans < 0) अणु
		dev_err(dev, "failed to get channel count: %d\n", chans);
		वापस chans;
	पूर्ण
	अगर (chans > DLN2_ADC_MAX_CHANNELS) अणु
		chans = DLN2_ADC_MAX_CHANNELS;
		dev_warn(dev, "clamping channels to %d\n",
			 DLN2_ADC_MAX_CHANNELS);
	पूर्ण

	क्रम (i = 0; i < chans; ++i)
		DLN2_ADC_CHAN(dln2->iio_channels[i], i)
	IIO_CHAN_SOFT_TIMESTAMP_ASSIGN(dln2->iio_channels[i], i);

	indio_dev->name = DLN2_ADC_MOD_NAME;
	indio_dev->info = &dln2_adc_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = dln2->iio_channels;
	indio_dev->num_channels = chans + 1;
	indio_dev->setup_ops = &dln2_adc_buffer_setup_ops;

	dln2->trig = devm_iio_trigger_alloc(dev, "%s-dev%d",
					    indio_dev->name, indio_dev->id);
	अगर (!dln2->trig) अणु
		dev_err(dev, "failed to allocate trigger\n");
		वापस -ENOMEM;
	पूर्ण
	iio_trigger_set_drvdata(dln2->trig, dln2);
	devm_iio_trigger_रेजिस्टर(dev, dln2->trig);
	iio_trigger_set_immutable(indio_dev, dln2->trig);

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, शून्य,
					      dln2_adc_trigger_h,
					      &dln2_adc_buffer_setup_ops);
	अगर (ret) अणु
		dev_err(dev, "failed to allocate triggered buffer: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = dln2_रेजिस्टर_event_cb(pdev, DLN2_ADC_CONDITION_MET_EV,
				     dln2_adc_event);
	अगर (ret) अणु
		dev_err(dev, "failed to setup DLN2 periodic event: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "failed to register iio device: %d\n", ret);
		जाओ unरेजिस्टर_event;
	पूर्ण

	वापस ret;

unरेजिस्टर_event:
	dln2_unरेजिस्टर_event_cb(pdev, DLN2_ADC_CONDITION_MET_EV);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);

	iio_device_unरेजिस्टर(indio_dev);
	dln2_unरेजिस्टर_event_cb(pdev, DLN2_ADC_CONDITION_MET_EV);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dln2_adc_driver = अणु
	.driver.name	= DLN2_ADC_MOD_NAME,
	.probe		= dln2_adc_probe,
	.हटाओ		= dln2_adc_हटाओ,
पूर्ण;

module_platक्रमm_driver(dln2_adc_driver);

MODULE_AUTHOR("Jack Andersen <jackoalan@gmail.com");
MODULE_DESCRIPTION("Driver for the Diolan DLN2 ADC interface");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dln2-adc");
