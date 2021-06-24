<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Chrome OS EC Sensor hub FIFO.
 *
 * Copyright 2020 Google LLC
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_data/cros_ec_sensorhub.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>

/* Precision of fixed poपूर्णांक क्रम the m values from the filter */
#घोषणा M_PRECISION BIT(23)

/* Only activate the filter once we have at least this many elements. */
#घोषणा TS_HISTORY_THRESHOLD 8

/*
 * If we करोn't have any history entries क्रम this दीर्घ, empty the filter to
 * make sure there are no big discontinuities.
 */
#घोषणा TS_HISTORY_BORED_US 500000

/* To measure by how much the filter is overshooting, अगर it happens. */
#घोषणा FUTURE_TS_ANALYTICS_COUNT_MAX 100

अटल अंतरभूत पूर्णांक
cros_sensorhub_send_sample(काष्ठा cros_ec_sensorhub *sensorhub,
			   काष्ठा cros_ec_sensors_ring_sample *sample)
अणु
	cros_ec_sensorhub_push_data_cb_t cb;
	पूर्णांक id = sample->sensor_id;
	काष्ठा iio_dev *indio_dev;

	अगर (id >= sensorhub->sensor_num)
		वापस -EINVAL;

	cb = sensorhub->push_data[id].push_data_cb;
	अगर (!cb)
		वापस 0;

	indio_dev = sensorhub->push_data[id].indio_dev;

	अगर (sample->flag & MOTIONSENSE_SENSOR_FLAG_FLUSH)
		वापस 0;

	वापस cb(indio_dev, sample->vector, sample->बारtamp);
पूर्ण

/**
 * cros_ec_sensorhub_रेजिस्टर_push_data() - रेजिस्टर the callback to the hub.
 *
 * @sensorhub : Sensor Hub object
 * @sensor_num : The sensor the caller is पूर्णांकerested in.
 * @indio_dev : The iio device to use when a sample arrives.
 * @cb : The callback to call when a sample arrives.
 *
 * The callback cb will be used by cros_ec_sensorhub_ring to distribute events
 * from the EC.
 *
 * Return: 0 when callback is रेजिस्टरed.
 *         EINVAL is the sensor number is invalid or the slot alपढ़ोy used.
 */
पूर्णांक cros_ec_sensorhub_रेजिस्टर_push_data(काष्ठा cros_ec_sensorhub *sensorhub,
					 u8 sensor_num,
					 काष्ठा iio_dev *indio_dev,
					 cros_ec_sensorhub_push_data_cb_t cb)
अणु
	अगर (sensor_num >= sensorhub->sensor_num)
		वापस -EINVAL;
	अगर (sensorhub->push_data[sensor_num].indio_dev)
		वापस -EINVAL;

	sensorhub->push_data[sensor_num].indio_dev = indio_dev;
	sensorhub->push_data[sensor_num].push_data_cb = cb;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensorhub_रेजिस्टर_push_data);

व्योम cros_ec_sensorhub_unरेजिस्टर_push_data(काष्ठा cros_ec_sensorhub *sensorhub,
					    u8 sensor_num)
अणु
	sensorhub->push_data[sensor_num].indio_dev = शून्य;
	sensorhub->push_data[sensor_num].push_data_cb = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensorhub_unरेजिस्टर_push_data);

/**
 * cros_ec_sensorhub_ring_fअगरo_enable() - Enable or disable पूर्णांकerrupt generation
 *					  क्रम FIFO events.
 * @sensorhub: Sensor Hub object
 * @on: true when events are requested.
 *
 * To be called beक्रमe sleeping or when noone is listening.
 * Return: 0 on success, or an error when we can not communicate with the EC.
 *
 */
पूर्णांक cros_ec_sensorhub_ring_fअगरo_enable(काष्ठा cros_ec_sensorhub *sensorhub,
				       bool on)
अणु
	पूर्णांक ret, i;

	mutex_lock(&sensorhub->cmd_lock);
	अगर (sensorhub->tight_बारtamps)
		क्रम (i = 0; i < sensorhub->sensor_num; i++)
			sensorhub->batch_state[i].last_len = 0;

	sensorhub->params->cmd = MOTIONSENSE_CMD_FIFO_INT_ENABLE;
	sensorhub->params->fअगरo_पूर्णांक_enable.enable = on;

	sensorhub->msg->outsize = माप(काष्ठा ec_params_motion_sense);
	sensorhub->msg->insize = माप(काष्ठा ec_response_motion_sense);

	ret = cros_ec_cmd_xfer_status(sensorhub->ec->ec_dev, sensorhub->msg);
	mutex_unlock(&sensorhub->cmd_lock);

	/* We expect to receive a payload of 4 bytes, ignore. */
	अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_sensor_ring_median_cmp(स्थिर व्योम *pv1, स्थिर व्योम *pv2)
अणु
	s64 v1 = *(s64 *)pv1;
	s64 v2 = *(s64 *)pv2;

	अगर (v1 > v2)
		वापस 1;
	अन्यथा अगर (v1 < v2)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * cros_ec_sensor_ring_median: Gets median of an array of numbers
 *
 * For now it's implemented using an inefficient > O(n) sort then वापस
 * the middle element. A more optimal method would be something like
 * quickselect, but given that n = 64 we can probably live with it in the
 * name of clarity.
 *
 * Warning: the input array माला_लो modअगरied (sorted)!
 */
अटल s64 cros_ec_sensor_ring_median(s64 *array, माप_प्रकार length)
अणु
	sort(array, length, माप(s64), cros_ec_sensor_ring_median_cmp, शून्य);
	वापस array[length / 2];
पूर्ण

/*
 * IRQ Timestamp Filtering
 *
 * Lower करोwn in cros_ec_sensor_ring_process_event(), क्रम each sensor event
 * we have to calculate it's बारtamp in the AP समयbase. There are 3 समय
 * poपूर्णांकs:
 *   a - EC समयbase, sensor event
 *   b - EC समयbase, IRQ
 *   c - AP समयbase, IRQ
 *   a' - what we want: sensor even in AP समयbase
 *
 * While a and b are recorded at accurate बार (due to the EC real समय
 * nature); c is pretty untrustworthy, even though it's recorded the
 * first thing in ec_irq_handler(). There is a very good change we'll get
 * added lantency due to:
 *   other irqs
 *   ddrfreq
 *   cpuidle
 *
 * Normally a' = c - b + a, but अगर we करो that naive math any jitter in c
 * will get coupled in a', which we don't want. We want a function
 * a' = cros_ec_sensor_ring_ts_filter(a) which will filter out outliers in c.
 *
 * Think of a graph of AP समय(b) on the y axis vs EC समय(c) on the x axis.
 * The slope of the line won't be exactly 1, there will be some घड़ी drअगरt
 * between the 2 chips क्रम various reasons (mechanical stress, temperature,
 * voltage). We need to extrapolate values क्रम a future x, without trusting
 * recent y values too much.
 *
 * We use a median filter क्रम the slope, then another median filter क्रम the
 * y-पूर्णांकercept to calculate this function:
 *   dx[n] = x[n-1] - x[n]
 *   dy[n] = x[n-1] - x[n]
 *   m[n] = dy[n] / dx[n]
 *   median_m = median(m[n-k:n])
 *   error[i] = y[n-i] - median_m * x[n-i]
 *   median_error = median(error[:k])
 *   predicted_y = median_m * x + median_error
 *
 * Implementation dअगरferences from above:
 * - Redefined y to be actually c - b, this gives us a lot more precision
 * to करो the math. (c-b)/b variations are more obvious than c/b variations.
 * - Since we करोn't have भग्नing poपूर्णांक, any operations involving slope are
 * करोne using fixed poपूर्णांक math (*M_PRECISION)
 * - Since x and y grow with समय, we keep zeroing the graph (relative to
 * the last sample), this way math involving *x[n-i] will not overflow
 * - EC बारtamps are kept in us, it improves the slope calculation precision
 */

/**
 * cros_ec_sensor_ring_ts_filter_update() - Update filter history.
 *
 * @state: Filter inक्रमmation.
 * @b: IRQ बारtamp, EC समयbase (us)
 * @c: IRQ बारtamp, AP समयbase (ns)
 *
 * Given a new IRQ बारtamp pair (EC and AP समयbases), add it to the filter
 * history.
 */
अटल व्योम
cros_ec_sensor_ring_ts_filter_update(काष्ठा cros_ec_sensors_ts_filter_state
				     *state,
				     s64 b, s64 c)
अणु
	s64 x, y;
	s64 dx, dy;
	s64 m; /* stored as *M_PRECISION */
	s64 *m_history_copy = state->temp_buf;
	s64 *error = state->temp_buf;
	पूर्णांक i;

	/* we trust b the most, that'll be our independent variable */
	x = b;
	/* y is the offset between AP and EC बार, in ns */
	y = c - b * 1000;

	dx = (state->x_history[0] + state->x_offset) - x;
	अगर (dx == 0)
		वापस; /* we alपढ़ोy have this irq in the history */
	dy = (state->y_history[0] + state->y_offset) - y;
	m = भाग64_s64(dy * M_PRECISION, dx);

	/* Empty filter अगर we haven't seen any action in a जबतक. */
	अगर (-dx > TS_HISTORY_BORED_US)
		state->history_len = 0;

	/* Move everything over, also update offset to all असलolute coords .*/
	क्रम (i = state->history_len - 1; i >= 1; i--) अणु
		state->x_history[i] = state->x_history[i - 1] + dx;
		state->y_history[i] = state->y_history[i - 1] + dy;

		state->m_history[i] = state->m_history[i - 1];
		/*
		 * Also use the same loop to copy m_history क्रम future
		 * median extraction.
		 */
		m_history_copy[i] = state->m_history[i - 1];
	पूर्ण

	/* Store the x and y, but remember offset is actually last sample. */
	state->x_offset = x;
	state->y_offset = y;
	state->x_history[0] = 0;
	state->y_history[0] = 0;

	state->m_history[0] = m;
	m_history_copy[0] = m;

	अगर (state->history_len < CROS_EC_SENSORHUB_TS_HISTORY_SIZE)
		state->history_len++;

	/* Precalculate things क्रम the filter. */
	अगर (state->history_len > TS_HISTORY_THRESHOLD) अणु
		state->median_m =
		    cros_ec_sensor_ring_median(m_history_copy,
					       state->history_len - 1);

		/*
		 * Calculate y-पूर्णांकercepts as अगर m_median is the slope and
		 * poपूर्णांकs in the history are on the line. median_error will
		 * still be in the offset coordinate प्रणाली.
		 */
		क्रम (i = 0; i < state->history_len; i++)
			error[i] = state->y_history[i] -
				भाग_s64(state->median_m * state->x_history[i],
					M_PRECISION);
		state->median_error =
			cros_ec_sensor_ring_median(error, state->history_len);
	पूर्ण अन्यथा अणु
		state->median_m = 0;
		state->median_error = 0;
	पूर्ण
पूर्ण

/**
 * cros_ec_sensor_ring_ts_filter() - Translate EC समयbase बारtamp to AP
 *                                   समयbase
 *
 * @state: filter inक्रमmation.
 * @x: any ec बारtamp (us):
 *
 * cros_ec_sensor_ring_ts_filter(a) => a' event बारtamp, AP समयbase
 * cros_ec_sensor_ring_ts_filter(b) => calculated बारtamp when the EC IRQ
 *                           should have happened on the AP, with low jitter
 *
 * Note: The filter will only activate once state->history_len goes
 * over TS_HISTORY_THRESHOLD. Otherwise it'll just करो the naive c - b + a
 * transक्रमm.
 *
 * How to derive the क्रमmula, starting from:
 *   f(x) = median_m * x + median_error
 * That's the calculated AP - EC offset (at the x poपूर्णांक in समय)
 * Unकरो the coordinate प्रणाली transक्रमm:
 *   f(x) = median_m * (x - x_offset) + median_error + y_offset
 * Remember to unकरो the "y = c - b * 1000" modअगरication:
 *   f(x) = median_m * (x - x_offset) + median_error + y_offset + x * 1000
 *
 * Return: बारtamp in AP समयbase (ns)
 */
अटल s64
cros_ec_sensor_ring_ts_filter(काष्ठा cros_ec_sensors_ts_filter_state *state,
			      s64 x)
अणु
	वापस भाग_s64(state->median_m * (x - state->x_offset), M_PRECISION)
	       + state->median_error + state->y_offset + x * 1000;
पूर्ण

/*
 * Since a and b were originally 32 bit values from the EC,
 * they overflow relatively often, casting is not enough, so we need to
 * add an offset.
 */
अटल व्योम
cros_ec_sensor_ring_fix_overflow(s64 *ts,
				 स्थिर s64 overflow_period,
				 काष्ठा cros_ec_sensors_ec_overflow_state
				 *state)
अणु
	s64 adjust;

	*ts += state->offset;
	अगर (असल(state->last - *ts) > (overflow_period / 2)) अणु
		adjust = state->last > *ts ? overflow_period : -overflow_period;
		state->offset += adjust;
		*ts += adjust;
	पूर्ण
	state->last = *ts;
पूर्ण

अटल व्योम
cros_ec_sensor_ring_check_क्रम_past_बारtamp(काष्ठा cros_ec_sensorhub
					     *sensorhub,
					     काष्ठा cros_ec_sensors_ring_sample
					     *sample)
अणु
	स्थिर u8 sensor_id = sample->sensor_id;

	/* If this event is earlier than one we saw beक्रमe... */
	अगर (sensorhub->batch_state[sensor_id].newest_sensor_event >
	    sample->बारtamp)
		/* mark it क्रम spपढ़ोing. */
		sample->बारtamp =
			sensorhub->batch_state[sensor_id].last_ts;
	अन्यथा
		sensorhub->batch_state[sensor_id].newest_sensor_event =
			sample->बारtamp;
पूर्ण

/**
 * cros_ec_sensor_ring_process_event() - Process one EC FIFO event
 *
 * @sensorhub: Sensor Hub object.
 * @fअगरo_info: FIFO inक्रमmation from the EC (includes b poपूर्णांक, EC समयbase).
 * @fअगरo_बारtamp: EC IRQ, kernel समयbase (aka c).
 * @current_बारtamp: calculated event बारtamp, kernel समयbase (aka a').
 * @in: incoming FIFO event from EC (includes a poपूर्णांक, EC समयbase).
 * @out: outgoing event to user space (includes a').
 *
 * Process one EC event, add it in the ring अगर necessary.
 *
 * Return: true अगर out event has been populated.
 */
अटल bool
cros_ec_sensor_ring_process_event(काष्ठा cros_ec_sensorhub *sensorhub,
				स्थिर काष्ठा ec_response_motion_sense_fअगरo_info
				*fअगरo_info,
				स्थिर kसमय_प्रकार fअगरo_बारtamp,
				kसमय_प्रकार *current_बारtamp,
				काष्ठा ec_response_motion_sensor_data *in,
				काष्ठा cros_ec_sensors_ring_sample *out)
अणु
	स्थिर s64 now = cros_ec_get_समय_ns();
	पूर्णांक axis, async_flags;

	/* Do not populate the filter based on asynchronous events. */
	async_flags = in->flags &
		(MOTIONSENSE_SENSOR_FLAG_ODR | MOTIONSENSE_SENSOR_FLAG_FLUSH);

	अगर (in->flags & MOTIONSENSE_SENSOR_FLAG_TIMESTAMP && !async_flags) अणु
		s64 a = in->बारtamp;
		s64 b = fअगरo_info->बारtamp;
		s64 c = fअगरo_बारtamp;

		cros_ec_sensor_ring_fix_overflow(&a, 1LL << 32,
					  &sensorhub->overflow_a);
		cros_ec_sensor_ring_fix_overflow(&b, 1LL << 32,
					  &sensorhub->overflow_b);

		अगर (sensorhub->tight_बारtamps) अणु
			cros_ec_sensor_ring_ts_filter_update(
					&sensorhub->filter, b, c);
			*current_बारtamp = cros_ec_sensor_ring_ts_filter(
					&sensorhub->filter, a);
		पूर्ण अन्यथा अणु
			s64 new_बारtamp;

			/*
			 * Disable filtering since we might add more jitter
			 * अगर b is in a अक्रमom poपूर्णांक in समय.
			 */
			new_बारtamp = c - b * 1000 + a * 1000;
			/*
			 * The बारtamp can be stale अगर we had to use the fअगरo
			 * info बारtamp.
			 */
			अगर (new_बारtamp - *current_बारtamp > 0)
				*current_बारtamp = new_बारtamp;
		पूर्ण
	पूर्ण

	अगर (in->flags & MOTIONSENSE_SENSOR_FLAG_ODR) अणु
		अगर (sensorhub->tight_बारtamps) अणु
			sensorhub->batch_state[in->sensor_num].last_len = 0;
			sensorhub->batch_state[in->sensor_num].penul_len = 0;
		पूर्ण
		/*
		 * ODR change is only useful क्रम the sensor_ring, it करोes not
		 * convey inक्रमmation to clients.
		 */
		वापस false;
	पूर्ण

	अगर (in->flags & MOTIONSENSE_SENSOR_FLAG_FLUSH) अणु
		out->sensor_id = in->sensor_num;
		out->बारtamp = *current_बारtamp;
		out->flag = in->flags;
		अगर (sensorhub->tight_बारtamps)
			sensorhub->batch_state[out->sensor_id].last_len = 0;
		/*
		 * No other payload inक्रमmation provided with
		 * flush ack.
		 */
		वापस true;
	पूर्ण

	अगर (in->flags & MOTIONSENSE_SENSOR_FLAG_TIMESTAMP)
		/* If we just have a बारtamp, skip this entry. */
		वापस false;

	/* Regular sample */
	out->sensor_id = in->sensor_num;
	अगर (*current_बारtamp - now > 0) अणु
		/*
		 * This fix is needed to overcome the बारtamp filter putting
		 * events in the future.
		 */
		sensorhub->future_बारtamp_total_ns +=
			*current_बारtamp - now;
		अगर (++sensorhub->future_बारtamp_count ==
				FUTURE_TS_ANALYTICS_COUNT_MAX) अणु
			s64 avg = भाग_s64(sensorhub->future_बारtamp_total_ns,
					sensorhub->future_बारtamp_count);
			dev_warn_ratelimited(sensorhub->dev,
					     "100 timestamps in the future, %lldns shaved on average\n",
					     avg);
			sensorhub->future_बारtamp_count = 0;
			sensorhub->future_बारtamp_total_ns = 0;
		पूर्ण
		out->बारtamp = now;
	पूर्ण अन्यथा अणु
		out->बारtamp = *current_बारtamp;
	पूर्ण

	out->flag = in->flags;
	क्रम (axis = 0; axis < 3; axis++)
		out->vector[axis] = in->data[axis];

	अगर (sensorhub->tight_बारtamps)
		cros_ec_sensor_ring_check_क्रम_past_बारtamp(sensorhub, out);
	वापस true;
पूर्ण

/*
 * cros_ec_sensor_ring_spपढ़ो_add: Calculate proper बारtamps then add to
 *                                 ringbuffer.
 *
 * This is the new spपढ़ोing code, assumes every sample's बारtamp
 * preceeds the sample. Run अगर tight_बारtamps == true.
 *
 * Someबार the EC receives only one पूर्णांकerrupt (hence बारtamp) क्रम
 * a batch of samples. Only the first sample will have the correct
 * बारtamp. So we must पूर्णांकerpolate the other samples.
 * We use the previous batch बारtamp and our current batch बारtamp
 * as a way to calculate period, then spपढ़ो the samples evenly.
 *
 * s0 पूर्णांक, 0ms
 * s1 पूर्णांक, 10ms
 * s2 पूर्णांक, 20ms
 * 30ms poपूर्णांक goes by, no पूर्णांकerrupt, previous one is still निश्चितed
 * करोwnloading s2 and s3
 * s3 sample, 20ms (incorrect बारtamp)
 * s4 पूर्णांक, 40ms
 *
 * The batches are [(s0), (s1), (s2, s3), (s4)]. Since the 3rd batch
 * has 2 samples in them, we adjust the बारtamp of s3.
 * s2 - s1 = 10ms, so s3 must be s2 + 10ms => 20ms. If s1 would have
 * been part of a bigger batch things would have gotten a little
 * more complicated.
 *
 * Note: we also assume another sensor sample करोesn't अवरोध up a batch
 * in 2 or more partitions. Example, there can't ever be a sync sensor
 * in between S2 and S3. This simplअगरies the following code.
 */
अटल व्योम
cros_ec_sensor_ring_spपढ़ो_add(काष्ठा cros_ec_sensorhub *sensorhub,
			       अचिन्हित दीर्घ sensor_mask,
			       काष्ठा cros_ec_sensors_ring_sample *last_out)
अणु
	काष्ठा cros_ec_sensors_ring_sample *batch_start, *next_batch_start;
	पूर्णांक id;

	क्रम_each_set_bit(id, &sensor_mask, sensorhub->sensor_num) अणु
		क्रम (batch_start = sensorhub->ring; batch_start < last_out;
		     batch_start = next_batch_start) अणु
			/*
			 * For each batch (where all samples have the same
			 * बारtamp).
			 */
			पूर्णांक batch_len, sample_idx;
			काष्ठा cros_ec_sensors_ring_sample *batch_end =
				batch_start;
			काष्ठा cros_ec_sensors_ring_sample *s;
			s64 batch_बारtamp = batch_start->बारtamp;
			s64 sample_period;

			/*
			 * Skip over batches that start with the sensor types
			 * we're not looking at right now.
			 */
			अगर (batch_start->sensor_id != id) अणु
				next_batch_start = batch_start + 1;
				जारी;
			पूर्ण

			/*
			 * Do not start a batch
			 * from a flush, as it happens asynchronously to the
			 * regular flow of events.
			 */
			अगर (batch_start->flag & MOTIONSENSE_SENSOR_FLAG_FLUSH) अणु
				cros_sensorhub_send_sample(sensorhub,
							   batch_start);
				next_batch_start = batch_start + 1;
				जारी;
			पूर्ण

			अगर (batch_start->बारtamp <=
			    sensorhub->batch_state[id].last_ts) अणु
				batch_बारtamp =
					sensorhub->batch_state[id].last_ts;
				batch_len = sensorhub->batch_state[id].last_len;

				sample_idx = batch_len;

				sensorhub->batch_state[id].last_ts =
				  sensorhub->batch_state[id].penul_ts;
				sensorhub->batch_state[id].last_len =
				  sensorhub->batch_state[id].penul_len;
			पूर्ण अन्यथा अणु
				/*
				 * Push first sample in the batch to the,
				 * kअगरo, it's guaranteed to be correct, the
				 * rest will follow later on.
				 */
				sample_idx = 1;
				batch_len = 1;
				cros_sensorhub_send_sample(sensorhub,
							   batch_start);
				batch_start++;
			पूर्ण

			/* Find all samples have the same बारtamp. */
			क्रम (s = batch_start; s < last_out; s++) अणु
				अगर (s->sensor_id != id)
					/*
					 * Skip over other sensor types that
					 * are पूर्णांकerleaved, करोn't count them.
					 */
					जारी;
				अगर (s->बारtamp != batch_बारtamp)
					/* we discovered the next batch */
					अवरोध;
				अगर (s->flag & MOTIONSENSE_SENSOR_FLAG_FLUSH)
					/* अवरोध on flush packets */
					अवरोध;
				batch_end = s;
				batch_len++;
			पूर्ण

			अगर (batch_len == 1)
				जाओ करोne_with_this_batch;

			/* Can we calculate period? */
			अगर (sensorhub->batch_state[id].last_len == 0) अणु
				dev_warn(sensorhub->dev, "Sensor %d: lost %d samples when spreading\n",
					 id, batch_len - 1);
				जाओ करोne_with_this_batch;
				/*
				 * Note: we're dropping the rest of the samples
				 * in this batch since we have no idea where
				 * they're supposed to go without a period
				 * calculation.
				 */
			पूर्ण

			sample_period = भाग_s64(batch_बारtamp -
				sensorhub->batch_state[id].last_ts,
				sensorhub->batch_state[id].last_len);
			dev_dbg(sensorhub->dev,
				"Adjusting %d samples, sensor %d last_batch @%lld (%d samples) batch_timestamp=%lld => period=%lld\n",
				batch_len, id,
				sensorhub->batch_state[id].last_ts,
				sensorhub->batch_state[id].last_len,
				batch_बारtamp,
				sample_period);

			/*
			 * Adjust बारtamps of the samples then push them to
			 * kfअगरo.
			 */
			क्रम (s = batch_start; s <= batch_end; s++) अणु
				अगर (s->sensor_id != id)
					/*
					 * Skip over other sensor types that
					 * are पूर्णांकerleaved, करोn't change them.
					 */
					जारी;

				s->बारtamp = batch_बारtamp +
					sample_period * sample_idx;
				sample_idx++;

				cros_sensorhub_send_sample(sensorhub, s);
			पूर्ण

करोne_with_this_batch:
			sensorhub->batch_state[id].penul_ts =
				sensorhub->batch_state[id].last_ts;
			sensorhub->batch_state[id].penul_len =
				sensorhub->batch_state[id].last_len;

			sensorhub->batch_state[id].last_ts =
				batch_बारtamp;
			sensorhub->batch_state[id].last_len = batch_len;

			next_batch_start = batch_end + 1;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * cros_ec_sensor_ring_spपढ़ो_add_legacy: Calculate proper बारtamps then
 * add to ringbuffer (legacy).
 *
 * Note: This assumes we're running old firmware, where बारtamp
 * is inserted after its sample(s)e. There can be several samples between
 * बारtamps, so several samples can have the same बारtamp.
 *
 *                        बारtamp | count
 *                        -----------------
 *          1st sample --> TS1      | 1
 *                         TS2      | 2
 *                         TS2      | 3
 *                         TS3      | 4
 *           last_out -->
 *
 *
 * We spपढ़ो समय क्रम the samples using perod p = (current - TS1)/4.
 * between TS1 and TS2: [TS1+p/4, TS1+2p/4, TS1+3p/4, current_बारtamp].
 *
 */
अटल व्योम
cros_ec_sensor_ring_spपढ़ो_add_legacy(काष्ठा cros_ec_sensorhub *sensorhub,
				      अचिन्हित दीर्घ sensor_mask,
				      s64 current_बारtamp,
				      काष्ठा cros_ec_sensors_ring_sample
				      *last_out)
अणु
	काष्ठा cros_ec_sensors_ring_sample *out;
	पूर्णांक i;

	क्रम_each_set_bit(i, &sensor_mask, sensorhub->sensor_num) अणु
		s64 बारtamp;
		पूर्णांक count = 0;
		s64 समय_period;

		क्रम (out = sensorhub->ring; out < last_out; out++) अणु
			अगर (out->sensor_id != i)
				जारी;

			/* Timestamp to start with */
			बारtamp = out->बारtamp;
			out++;
			count = 1;
			अवरोध;
		पूर्ण
		क्रम (; out < last_out; out++) अणु
			/* Find last sample. */
			अगर (out->sensor_id != i)
				जारी;
			count++;
		पूर्ण
		अगर (count == 0)
			जारी;

		/* Spपढ़ो unअगरormly between the first and last samples. */
		समय_period = भाग_s64(current_बारtamp - बारtamp, count);

		क्रम (out = sensorhub->ring; out < last_out; out++) अणु
			अगर (out->sensor_id != i)
				जारी;
			बारtamp += समय_period;
			out->बारtamp = बारtamp;
		पूर्ण
	पूर्ण

	/* Push the event पूर्णांकo the kfअगरo */
	क्रम (out = sensorhub->ring; out < last_out; out++)
		cros_sensorhub_send_sample(sensorhub, out);
पूर्ण

/**
 * cros_ec_sensorhub_ring_handler() - The trigger handler function
 *
 * @sensorhub: Sensor Hub object.
 *
 * Called by the notअगरier, process the EC sensor FIFO queue.
 */
अटल व्योम cros_ec_sensorhub_ring_handler(काष्ठा cros_ec_sensorhub *sensorhub)
अणु
	काष्ठा ec_response_motion_sense_fअगरo_info *fअगरo_info =
		sensorhub->fअगरo_info;
	काष्ठा cros_ec_dev *ec = sensorhub->ec;
	kसमय_प्रकार fअगरo_बारtamp, current_बारtamp;
	पूर्णांक i, j, number_data, ret;
	अचिन्हित दीर्घ sensor_mask = 0;
	काष्ठा ec_response_motion_sensor_data *in;
	काष्ठा cros_ec_sensors_ring_sample *out, *last_out;

	mutex_lock(&sensorhub->cmd_lock);

	/* Get FIFO inक्रमmation अगर there are lost vectors. */
	अगर (fअगरo_info->total_lost) अणु
		पूर्णांक fअगरo_info_length =
			माप(काष्ठा ec_response_motion_sense_fअगरo_info) +
			माप(u16) * sensorhub->sensor_num;

		/* Need to retrieve the number of lost vectors per sensor */
		sensorhub->params->cmd = MOTIONSENSE_CMD_FIFO_INFO;
		sensorhub->msg->outsize = 1;
		sensorhub->msg->insize = fअगरo_info_length;

		अगर (cros_ec_cmd_xfer_status(ec->ec_dev, sensorhub->msg) < 0)
			जाओ error;

		स_नकल(fअगरo_info, &sensorhub->resp->fअगरo_info,
		       fअगरo_info_length);

		/*
		 * Update collection समय, will not be as precise as the
		 * non-error हाल.
		 */
		fअगरo_बारtamp = cros_ec_get_समय_ns();
	पूर्ण अन्यथा अणु
		fअगरo_बारtamp = sensorhub->fअगरo_बारtamp[
			CROS_EC_SENSOR_NEW_TS];
	पूर्ण

	अगर (fअगरo_info->count > sensorhub->fअगरo_size ||
	    fअगरo_info->size != sensorhub->fअगरo_size) अणु
		dev_warn(sensorhub->dev,
			 "Mismatch EC data: count %d, size %d - expected %d\n",
			 fअगरo_info->count, fअगरo_info->size,
			 sensorhub->fअगरo_size);
		जाओ error;
	पूर्ण

	/* Copy elements in the मुख्य fअगरo */
	current_बारtamp = sensorhub->fअगरo_बारtamp[CROS_EC_SENSOR_LAST_TS];
	out = sensorhub->ring;
	क्रम (i = 0; i < fअगरo_info->count; i += number_data) अणु
		sensorhub->params->cmd = MOTIONSENSE_CMD_FIFO_READ;
		sensorhub->params->fअगरo_पढ़ो.max_data_vector =
			fअगरo_info->count - i;
		sensorhub->msg->outsize =
			माप(काष्ठा ec_params_motion_sense);
		sensorhub->msg->insize =
			माप(sensorhub->resp->fअगरo_पढ़ो) +
			sensorhub->params->fअगरo_पढ़ो.max_data_vector *
			  माप(काष्ठा ec_response_motion_sensor_data);
		ret = cros_ec_cmd_xfer_status(ec->ec_dev, sensorhub->msg);
		अगर (ret < 0) अणु
			dev_warn(sensorhub->dev, "Fifo error: %d\n", ret);
			अवरोध;
		पूर्ण
		number_data = sensorhub->resp->fअगरo_पढ़ो.number_data;
		अगर (number_data == 0) अणु
			dev_dbg(sensorhub->dev, "Unexpected empty FIFO\n");
			अवरोध;
		पूर्ण
		अगर (number_data > fअगरo_info->count - i) अणु
			dev_warn(sensorhub->dev,
				 "Invalid EC data: too many entry received: %d, expected %d\n",
				 number_data, fअगरo_info->count - i);
			अवरोध;
		पूर्ण
		अगर (out + number_data >
		    sensorhub->ring + fअगरo_info->count) अणु
			dev_warn(sensorhub->dev,
				 "Too many samples: %d (%zd data) to %d entries for expected %d entries\n",
				 i, out - sensorhub->ring, i + number_data,
				 fअगरo_info->count);
			अवरोध;
		पूर्ण

		क्रम (in = sensorhub->resp->fअगरo_पढ़ो.data, j = 0;
		     j < number_data; j++, in++) अणु
			अगर (cros_ec_sensor_ring_process_event(
						sensorhub, fअगरo_info,
						fअगरo_बारtamp,
						&current_बारtamp,
						in, out)) अणु
				sensor_mask |= BIT(in->sensor_num);
				out++;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&sensorhub->cmd_lock);
	last_out = out;

	अगर (out == sensorhub->ring)
		/* Unexpected empty FIFO. */
		जाओ ring_handler_end;

	/*
	 * Check अगर current_बारtamp is ahead of the last sample. Normally,
	 * the EC appends a बारtamp after the last sample, but अगर the AP
	 * is slow to respond to the IRQ, the EC may have added new samples.
	 * Use the FIFO info बारtamp as last बारtamp then.
	 */
	अगर (!sensorhub->tight_बारtamps &&
	    (last_out - 1)->बारtamp == current_बारtamp)
		current_बारtamp = fअगरo_बारtamp;

	/* Warn on lost samples. */
	अगर (fअगरo_info->total_lost)
		क्रम (i = 0; i < sensorhub->sensor_num; i++) अणु
			अगर (fअगरo_info->lost[i]) अणु
				dev_warn_ratelimited(sensorhub->dev,
						     "Sensor %d: lost: %d out of %d\n",
						     i, fअगरo_info->lost[i],
						     fअगरo_info->total_lost);
				अगर (sensorhub->tight_बारtamps)
					sensorhub->batch_state[i].last_len = 0;
			पूर्ण
		पूर्ण

	/*
	 * Spपढ़ो samples in हाल of batching, then add them to the
	 * ringbuffer.
	 */
	अगर (sensorhub->tight_बारtamps)
		cros_ec_sensor_ring_spपढ़ो_add(sensorhub, sensor_mask,
					       last_out);
	अन्यथा
		cros_ec_sensor_ring_spपढ़ो_add_legacy(sensorhub, sensor_mask,
						      current_बारtamp,
						      last_out);

ring_handler_end:
	sensorhub->fअगरo_बारtamp[CROS_EC_SENSOR_LAST_TS] = current_बारtamp;
	वापस;

error:
	mutex_unlock(&sensorhub->cmd_lock);
पूर्ण

अटल पूर्णांक cros_ec_sensorhub_event(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ queued_during_suspend,
				   व्योम *_notअगरy)
अणु
	काष्ठा cros_ec_sensorhub *sensorhub;
	काष्ठा cros_ec_device *ec_dev;

	sensorhub = container_of(nb, काष्ठा cros_ec_sensorhub, notअगरier);
	ec_dev = sensorhub->ec->ec_dev;

	अगर (ec_dev->event_data.event_type != EC_MKBP_EVENT_SENSOR_FIFO)
		वापस NOTIFY_DONE;

	अगर (ec_dev->event_size != माप(ec_dev->event_data.data.sensor_fअगरo)) अणु
		dev_warn(ec_dev->dev, "Invalid fifo info size\n");
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (queued_during_suspend)
		वापस NOTIFY_OK;

	स_नकल(sensorhub->fअगरo_info, &ec_dev->event_data.data.sensor_fअगरo.info,
	       माप(*sensorhub->fअगरo_info));
	sensorhub->fअगरo_बारtamp[CROS_EC_SENSOR_NEW_TS] =
		ec_dev->last_event_समय;
	cros_ec_sensorhub_ring_handler(sensorhub);

	वापस NOTIFY_OK;
पूर्ण

/**
 * cros_ec_sensorhub_ring_allocate() - Prepare the FIFO functionality अगर the EC
 *				       supports it.
 *
 * @sensorhub : Sensor Hub object.
 *
 * Return: 0 on success.
 */
पूर्णांक cros_ec_sensorhub_ring_allocate(काष्ठा cros_ec_sensorhub *sensorhub)
अणु
	पूर्णांक fअगरo_info_length =
		माप(काष्ठा ec_response_motion_sense_fअगरo_info) +
		माप(u16) * sensorhub->sensor_num;

	/* Allocate the array क्रम lost events. */
	sensorhub->fअगरo_info = devm_kzalloc(sensorhub->dev, fअगरo_info_length,
					    GFP_KERNEL);
	अगर (!sensorhub->fअगरo_info)
		वापस -ENOMEM;

	/*
	 * Allocate the callback area based on the number of sensors.
	 * Add one क्रम the sensor ring.
	 */
	sensorhub->push_data = devm_kसुस्मृति(sensorhub->dev,
			sensorhub->sensor_num,
			माप(*sensorhub->push_data),
			GFP_KERNEL);
	अगर (!sensorhub->push_data)
		वापस -ENOMEM;

	sensorhub->tight_बारtamps = cros_ec_check_features(
			sensorhub->ec,
			EC_FEATURE_MOTION_SENSE_TIGHT_TIMESTAMPS);

	अगर (sensorhub->tight_बारtamps) अणु
		sensorhub->batch_state = devm_kसुस्मृति(sensorhub->dev,
				sensorhub->sensor_num,
				माप(*sensorhub->batch_state),
				GFP_KERNEL);
		अगर (!sensorhub->batch_state)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cros_ec_sensorhub_ring_add() - Add the FIFO functionality अगर the EC
 *				  supports it.
 *
 * @sensorhub : Sensor Hub object.
 *
 * Return: 0 on success.
 */
पूर्णांक cros_ec_sensorhub_ring_add(काष्ठा cros_ec_sensorhub *sensorhub)
अणु
	काष्ठा cros_ec_dev *ec = sensorhub->ec;
	पूर्णांक ret;
	पूर्णांक fअगरo_info_length =
		माप(काष्ठा ec_response_motion_sense_fअगरo_info) +
		माप(u16) * sensorhub->sensor_num;

	/* Retrieve FIFO inक्रमmation */
	sensorhub->msg->version = 2;
	sensorhub->params->cmd = MOTIONSENSE_CMD_FIFO_INFO;
	sensorhub->msg->outsize = 1;
	sensorhub->msg->insize = fअगरo_info_length;

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, sensorhub->msg);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Allocate the full fअगरo. We need to copy the whole FIFO to set
	 * बारtamps properly.
	 */
	sensorhub->fअगरo_size = sensorhub->resp->fअगरo_info.size;
	sensorhub->ring = devm_kसुस्मृति(sensorhub->dev, sensorhub->fअगरo_size,
				       माप(*sensorhub->ring), GFP_KERNEL);
	अगर (!sensorhub->ring)
		वापस -ENOMEM;

	sensorhub->fअगरo_बारtamp[CROS_EC_SENSOR_LAST_TS] =
		cros_ec_get_समय_ns();

	/* Register the notअगरier that will act as a top half पूर्णांकerrupt. */
	sensorhub->notअगरier.notअगरier_call = cros_ec_sensorhub_event;
	ret = blocking_notअगरier_chain_रेजिस्टर(&ec->ec_dev->event_notअगरier,
					       &sensorhub->notअगरier);
	अगर (ret < 0)
		वापस ret;

	/* Start collection samples. */
	वापस cros_ec_sensorhub_ring_fअगरo_enable(sensorhub, true);
पूर्ण

व्योम cros_ec_sensorhub_ring_हटाओ(व्योम *arg)
अणु
	काष्ठा cros_ec_sensorhub *sensorhub = arg;
	काष्ठा cros_ec_device *ec_dev = sensorhub->ec->ec_dev;

	/* Disable the ring, prevent EC पूर्णांकerrupt to the AP क्रम nothing. */
	cros_ec_sensorhub_ring_fअगरo_enable(sensorhub, false);
	blocking_notअगरier_chain_unरेजिस्टर(&ec_dev->event_notअगरier,
					   &sensorhub->notअगरier);
पूर्ण
