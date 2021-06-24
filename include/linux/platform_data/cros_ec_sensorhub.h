<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Chrome OS EC MEMS Sensor Hub driver.
 *
 * Copyright 2019 Google LLC
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_CROS_EC_SENSORHUB_H
#घोषणा __LINUX_PLATFORM_DATA_CROS_EC_SENSORHUB_H

#समावेश <linux/kसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>

काष्ठा iio_dev;

/**
 * काष्ठा cros_ec_sensor_platक्रमm - ChromeOS EC sensor platक्रमm inक्रमmation.
 * @sensor_num: Id of the sensor, as reported by the EC.
 */
काष्ठा cros_ec_sensor_platक्रमm अणु
	u8 sensor_num;
पूर्ण;

/**
 * प्रकार cros_ec_sensorhub_push_data_cb_t - Callback function to send datum
 *					      to specअगरic sensors.
 *
 * @indio_dev: The IIO device that will process the sample.
 * @data: Vector array of the ring sample.
 * @बारtamp: Timestamp in host बारpace when the sample was acquired by
 *             the EC.
 */
प्रकार पूर्णांक (*cros_ec_sensorhub_push_data_cb_t)(काष्ठा iio_dev *indio_dev,
						s16 *data,
						s64 बारtamp);

काष्ठा cros_ec_sensorhub_sensor_push_data अणु
	काष्ठा iio_dev *indio_dev;
	cros_ec_sensorhub_push_data_cb_t push_data_cb;
पूर्ण;

क्रमागत अणु
	CROS_EC_SENSOR_LAST_TS,
	CROS_EC_SENSOR_NEW_TS,
	CROS_EC_SENSOR_ALL_TS
पूर्ण;

काष्ठा cros_ec_sensors_ring_sample अणु
	u8  sensor_id;
	u8  flag;
	s16 vector[3];
	s64 बारtamp;
पूर्ण __packed;

/* State used क्रम cros_ec_ring_fix_overflow */
काष्ठा cros_ec_sensors_ec_overflow_state अणु
	s64 offset;
	s64 last;
पूर्ण;

/* Length of the filter, how दीर्घ to remember entries क्रम */
#घोषणा CROS_EC_SENSORHUB_TS_HISTORY_SIZE 64

/**
 * काष्ठा cros_ec_sensors_ts_filter_state - Timestamp filetr state.
 *
 * @x_offset: x is EC पूर्णांकerrupt समय. x_offset its last value.
 * @y_offset: y is the dअगरference between AP and EC समय, y_offset its last
 *            value.
 * @x_history: The past history of x, relative to x_offset.
 * @y_history: The past history of y, relative to y_offset.
 * @m_history: rate between y and x.
 * @history_len: Amount of valid historic data in the arrays.
 * @temp_buf: Temporary buffer used when updating the filter.
 * @median_m: median value of m_history
 * @median_error: final error to apply to AP पूर्णांकerrupt बारtamp to get the
 *                "true timestamp" the event occurred.
 */
काष्ठा cros_ec_sensors_ts_filter_state अणु
	s64 x_offset, y_offset;
	s64 x_history[CROS_EC_SENSORHUB_TS_HISTORY_SIZE];
	s64 y_history[CROS_EC_SENSORHUB_TS_HISTORY_SIZE];
	s64 m_history[CROS_EC_SENSORHUB_TS_HISTORY_SIZE];
	पूर्णांक history_len;

	s64 temp_buf[CROS_EC_SENSORHUB_TS_HISTORY_SIZE];

	s64 median_m;
	s64 median_error;
पूर्ण;

/* काष्ठा cros_ec_sensors_ts_batch_state - State of batch of a single sensor.
 *
 * Use to store inक्रमmation to batch data using median fileter inक्रमmation.
 *
 * @penul_ts: last but one batch बारtamp (penultimate बारtamp).
 *	      Used क्रम बारtamp spपढ़ोing calculations
 *	      when a batch shows up.
 * @penul_len: last but one batch length.
 * @last_ts: Last batch बारtam.
 * @last_len: Last batch length.
 * @newest_sensor_event: Last sensor बारtamp.
 */
काष्ठा cros_ec_sensors_ts_batch_state अणु
	s64 penul_ts;
	पूर्णांक penul_len;
	s64 last_ts;
	पूर्णांक last_len;
	s64 newest_sensor_event;
पूर्ण;

/*
 * काष्ठा cros_ec_sensorhub - Sensor Hub device data.
 *
 * @dev: Device object, mostly used क्रम logging.
 * @ec: Embedded Controller where the hub is located.
 * @sensor_num: Number of MEMS sensors present in the EC.
 * @msg: Structure to send FIFO requests.
 * @params: Poपूर्णांकer to parameters in msg.
 * @resp: Poपूर्णांकer to responses in msg.
 * @cmd_lock : Lock क्रम sending msg.
 * @notअगरier: Notअगरier to kick the FIFO पूर्णांकerrupt.
 * @ring: Preprocessed ring to store events.
 * @fअगरo_बारtamp: Array क्रम event बारtamp and spपढ़ोing.
 * @fअगरo_info: Copy of FIFO inक्रमmation coming from the EC.
 * @fअगरo_size: Size of the ring.
 * @batch_state: Per sensor inक्रमmation of the last batches received.
 * @overflow_a: For handling बारtamp overflow क्रम a समय (sensor events)
 * @overflow_b: For handling बारtamp overflow क्रम b समय (ec पूर्णांकerrupts)
 * @filter: Medium fileter काष्ठाure.
 * @tight_बारtamps: Set to truen when EC support tight बारtamping:
 *		      The बारtamps reported from the EC have low jitter.
 *		      Timestamps also come beक्रमe every sample. Set either
 *		      by feature bits coming from the EC or userspace.
 * @future_बारtamp_count: Statistics used to compute shaved समय.
 *			    This occurs when बारtamp पूर्णांकerpolation from EC
 *			    समय to AP समय accidentally माला_दो बारtamps in
 *			    the future. These बारtamps are clamped to
 *			    `now` and these count/total_ns मुख्यtain the
 *			    statistics क्रम how much समय was हटाओd in a
 *			    given period.
 * @future_बारtamp_total_ns: Total amount of समय shaved.
 * @push_data: Array of callback to send datums to iio sensor object.
 */
काष्ठा cros_ec_sensorhub अणु
	काष्ठा device *dev;
	काष्ठा cros_ec_dev *ec;
	पूर्णांक sensor_num;

	काष्ठा cros_ec_command *msg;
	काष्ठा ec_params_motion_sense *params;
	काष्ठा ec_response_motion_sense *resp;
	काष्ठा mutex cmd_lock;  /* Lock क्रम protecting msg काष्ठाure. */

	काष्ठा notअगरier_block notअगरier;

	काष्ठा cros_ec_sensors_ring_sample *ring;

	kसमय_प्रकार fअगरo_बारtamp[CROS_EC_SENSOR_ALL_TS];
	काष्ठा ec_response_motion_sense_fअगरo_info *fअगरo_info;
	पूर्णांक fअगरo_size;

	काष्ठा cros_ec_sensors_ts_batch_state *batch_state;

	काष्ठा cros_ec_sensors_ec_overflow_state overflow_a;
	काष्ठा cros_ec_sensors_ec_overflow_state overflow_b;

	काष्ठा cros_ec_sensors_ts_filter_state filter;

	पूर्णांक tight_बारtamps;

	s32 future_बारtamp_count;
	s64 future_बारtamp_total_ns;

	काष्ठा cros_ec_sensorhub_sensor_push_data *push_data;
पूर्ण;

पूर्णांक cros_ec_sensorhub_रेजिस्टर_push_data(काष्ठा cros_ec_sensorhub *sensorhub,
					 u8 sensor_num,
					 काष्ठा iio_dev *indio_dev,
					 cros_ec_sensorhub_push_data_cb_t cb);

व्योम cros_ec_sensorhub_unरेजिस्टर_push_data(काष्ठा cros_ec_sensorhub *sensorhub,
					    u8 sensor_num);

पूर्णांक cros_ec_sensorhub_ring_allocate(काष्ठा cros_ec_sensorhub *sensorhub);
पूर्णांक cros_ec_sensorhub_ring_add(काष्ठा cros_ec_sensorhub *sensorhub);
व्योम cros_ec_sensorhub_ring_हटाओ(व्योम *arg);
पूर्णांक cros_ec_sensorhub_ring_fअगरo_enable(काष्ठा cros_ec_sensorhub *sensorhub,
				       bool on);

#पूर्ण_अगर   /* __LINUX_PLATFORM_DATA_CROS_EC_SENSORHUB_H */
