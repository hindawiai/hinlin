<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ChromeOS EC sensor hub
 *
 * Copyright (C) 2016 Google, Inc
 */

#अगर_अघोषित __CROS_EC_SENSORS_CORE_H
#घोषणा __CROS_EC_SENSORS_CORE_H

#समावेश <linux/iio/iपन.स>
#समावेश <linux/irqवापस.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_data/cros_ec_sensorhub.h>

क्रमागत अणु
	CROS_EC_SENSOR_X,
	CROS_EC_SENSOR_Y,
	CROS_EC_SENSOR_Z,
	CROS_EC_SENSOR_MAX_AXIS,
पूर्ण;

/* EC वापसs sensor values using चिन्हित 16 bit रेजिस्टरs */
#घोषणा CROS_EC_SENSOR_BITS 16

/*
 * 4 16 bit channels are allowed.
 * Good enough क्रम current sensors, they use up to 3 16 bit vectors.
 */
#घोषणा CROS_EC_SAMPLE_SIZE  (माप(s64) * 2)

प्रकार irqवापस_t (*cros_ec_sensors_capture_t)(पूर्णांक irq, व्योम *p);

/**
 * काष्ठा cros_ec_sensors_core_state - state data क्रम EC sensors IIO driver
 * @ec:				cros EC device काष्ठाure
 * @cmd_lock:			lock used to prevent simultaneous access to the
 *				commands.
 * @msg:			cros EC command काष्ठाure
 * @param:			motion sensor parameters काष्ठाure
 * @resp:			motion sensor response काष्ठाure
 * @type:			type of motion sensor
 * @loc:			location where the motion sensor is placed
 * @range_updated:		True अगर the range of the sensor has been
 *				updated.
 * @curr_range:			If updated, the current range value.
 *				It will be reapplied at every resume.
 * @calib:			calibration parameters. Note that trigger
 *				captured data will always provide the calibrated
 *				data
 * @samples:			अटल array to hold data from a single capture.
 *				For each channel we need 2 bytes, except क्रम
 *				the बारtamp. The बारtamp is always last and
 *				is always 8-byte aligned.
 * @पढ़ो_ec_sensors_data:	function used क्रम accessing sensors values
 * @fअगरo_max_event_count:	Size of the EC sensor FIFO
 * @frequencies:		Table of known available frequencies:
 *				0, Min and Max in mHz
 */
काष्ठा cros_ec_sensors_core_state अणु
	काष्ठा cros_ec_device *ec;
	काष्ठा mutex cmd_lock;

	काष्ठा cros_ec_command *msg;
	काष्ठा ec_params_motion_sense param;
	काष्ठा ec_response_motion_sense *resp;

	क्रमागत motionsensor_type type;
	क्रमागत motionsensor_location loc;

	bool range_updated;
	पूर्णांक curr_range;

	काष्ठा calib_data अणु
		s16 offset;
		u16 scale;
	पूर्ण calib[CROS_EC_SENSOR_MAX_AXIS];
	s8 sign[CROS_EC_SENSOR_MAX_AXIS];
	u8 samples[CROS_EC_SAMPLE_SIZE];

	पूर्णांक (*पढ़ो_ec_sensors_data)(काष्ठा iio_dev *indio_dev,
				    अचिन्हित दीर्घ scan_mask, s16 *data);

	u32 fअगरo_max_event_count;
	पूर्णांक frequencies[6];
पूर्ण;

पूर्णांक cros_ec_sensors_पढ़ो_lpc(काष्ठा iio_dev *indio_dev, अचिन्हित दीर्घ scan_mask,
			     s16 *data);

पूर्णांक cros_ec_sensors_पढ़ो_cmd(काष्ठा iio_dev *indio_dev, अचिन्हित दीर्घ scan_mask,
			     s16 *data);

काष्ठा platक्रमm_device;
पूर्णांक cros_ec_sensors_core_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा iio_dev *indio_dev, bool physical_device,
			      cros_ec_sensors_capture_t trigger_capture,
			      cros_ec_sensorhub_push_data_cb_t push_data);

irqवापस_t cros_ec_sensors_capture(पूर्णांक irq, व्योम *p);
पूर्णांक cros_ec_sensors_push_data(काष्ठा iio_dev *indio_dev,
			      s16 *data,
			      s64 बारtamp);

पूर्णांक cros_ec_motion_send_host_cmd(काष्ठा cros_ec_sensors_core_state *st,
				 u16 opt_length);

पूर्णांक cros_ec_sensors_core_पढ़ो(काष्ठा cros_ec_sensors_core_state *st,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2, दीर्घ mask);

पूर्णांक cros_ec_sensors_core_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan,
				    स्थिर पूर्णांक **vals,
				    पूर्णांक *type,
				    पूर्णांक *length,
				    दीर्घ mask);

पूर्णांक cros_ec_sensors_core_ग_लिखो(काष्ठा cros_ec_sensors_core_state *st,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask);

बाह्य स्थिर काष्ठा dev_pm_ops cros_ec_sensors_pm_ops;

/* List of extended channel specअगरication क्रम all sensors. */
बाह्य स्थिर काष्ठा iio_chan_spec_ext_info cros_ec_sensors_ext_info[];

#पूर्ण_अगर  /* __CROS_EC_SENSORS_CORE_H */
