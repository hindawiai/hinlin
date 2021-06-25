<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (C) 2014, Samsung Electronics Co. Ltd. All Rights Reserved.
 */
#अगर_अघोषित _SSP_SENSORS_H_
#घोषणा _SSP_SENSORS_H_

#समावेश <linux/iio/iपन.स>

#घोषणा SSP_TIME_SIZE				4
#घोषणा SSP_ACCELEROMETER_SIZE			6
#घोषणा SSP_GYROSCOPE_SIZE			6
#घोषणा SSP_BIO_HRM_RAW_SIZE			8
#घोषणा SSP_BIO_HRM_RAW_FAC_SIZE		36
#घोषणा SSP_BIO_HRM_LIB_SIZE			8

/**
 * क्रमागत ssp_sensor_type - SSP sensor type
 */
क्रमागत ssp_sensor_type अणु
	SSP_ACCELEROMETER_SENSOR = 0,
	SSP_GYROSCOPE_SENSOR,
	SSP_GEOMAGNETIC_UNCALIB_SENSOR,
	SSP_GEOMAGNETIC_RAW,
	SSP_GEOMAGNETIC_SENSOR,
	SSP_PRESSURE_SENSOR,
	SSP_GESTURE_SENSOR,
	SSP_PROXIMITY_SENSOR,
	SSP_TEMPERATURE_HUMIDITY_SENSOR,
	SSP_LIGHT_SENSOR,
	SSP_PROXIMITY_RAW,
	SSP_ORIENTATION_SENSOR,
	SSP_STEP_DETECTOR,
	SSP_SIG_MOTION_SENSOR,
	SSP_GYRO_UNCALIB_SENSOR,
	SSP_GAME_ROTATION_VECTOR,
	SSP_ROTATION_VECTOR,
	SSP_STEP_COUNTER,
	SSP_BIO_HRM_RAW,
	SSP_BIO_HRM_RAW_FAC,
	SSP_BIO_HRM_LIB,
	SSP_SENSOR_MAX,
पूर्ण;

काष्ठा ssp_data;

/**
 * काष्ठा ssp_sensor_data - Sensor object
 * @process_data:	Callback to feed sensor data.
 * @type:		Used sensor type.
 * @buffer:		Received data buffer.
 */
काष्ठा ssp_sensor_data अणु
	पूर्णांक (*process_data)(काष्ठा iio_dev *indio_dev, व्योम *buf,
			    पूर्णांक64_t बारtamp);
	क्रमागत ssp_sensor_type type;
	u8 *buffer;
पूर्ण;

व्योम ssp_रेजिस्टर_consumer(काष्ठा iio_dev *indio_dev,
			   क्रमागत ssp_sensor_type type);

पूर्णांक ssp_enable_sensor(काष्ठा ssp_data *data, क्रमागत ssp_sensor_type type,
		      u32 delay);

पूर्णांक ssp_disable_sensor(काष्ठा ssp_data *data, क्रमागत ssp_sensor_type type);

u32 ssp_get_sensor_delay(काष्ठा ssp_data *data, क्रमागत ssp_sensor_type);

पूर्णांक ssp_change_delay(काष्ठा ssp_data *data, क्रमागत ssp_sensor_type type,
		     u32 delay);
#पूर्ण_अगर /* _SSP_SENSORS_H_ */
