<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2020 Invensense, Inc.
 */

#अगर_अघोषित INV_ICM42600_BUFFER_H_
#घोषणा INV_ICM42600_BUFFER_H_

#समावेश <linux/kernel.h>
#समावेश <linux/bits.h>

काष्ठा inv_icm42600_state;

#घोषणा INV_ICM42600_SENSOR_GYRO	BIT(0)
#घोषणा INV_ICM42600_SENSOR_ACCEL	BIT(1)
#घोषणा INV_ICM42600_SENSOR_TEMP	BIT(2)

/**
 * काष्ठा inv_icm42600_fअगरo - FIFO state variables
 * @on:		reference counter क्रम FIFO on.
 * @en:		bits field of INV_ICM42600_SENSOR_* क्रम FIFO EN bits.
 * @period:	FIFO पूर्णांकernal period.
 * @watermark:	watermark configuration values क्रम accel and gyro.
 * @count:	number of bytes in the FIFO data buffer.
 * @nb:		gyro, accel and total samples in the FIFO data buffer.
 * @data:	FIFO data buffer aligned क्रम DMA (2kB + 32 bytes of पढ़ो cache).
 */
काष्ठा inv_icm42600_fअगरo अणु
	अचिन्हित पूर्णांक on;
	अचिन्हित पूर्णांक en;
	uपूर्णांक32_t period;
	काष्ठा अणु
		अचिन्हित पूर्णांक gyro;
		अचिन्हित पूर्णांक accel;
	पूर्ण watermark;
	माप_प्रकार count;
	काष्ठा अणु
		माप_प्रकार gyro;
		माप_प्रकार accel;
		माप_प्रकार total;
	पूर्ण nb;
	uपूर्णांक8_t data[2080] ____cacheline_aligned;
पूर्ण;

/* FIFO data packet */
काष्ठा inv_icm42600_fअगरo_sensor_data अणु
	__be16 x;
	__be16 y;
	__be16 z;
पूर्ण __packed;
#घोषणा INV_ICM42600_FIFO_DATA_INVALID		-32768

अटल अंतरभूत पूर्णांक16_t inv_icm42600_fअगरo_get_sensor_data(__be16 d)
अणु
	वापस be16_to_cpu(d);
पूर्ण

अटल अंतरभूत bool
inv_icm42600_fअगरo_is_data_valid(स्थिर काष्ठा inv_icm42600_fअगरo_sensor_data *s)
अणु
	पूर्णांक16_t x, y, z;

	x = inv_icm42600_fअगरo_get_sensor_data(s->x);
	y = inv_icm42600_fअगरo_get_sensor_data(s->y);
	z = inv_icm42600_fअगरo_get_sensor_data(s->z);

	अगर (x == INV_ICM42600_FIFO_DATA_INVALID &&
	    y == INV_ICM42600_FIFO_DATA_INVALID &&
	    z == INV_ICM42600_FIFO_DATA_INVALID)
		वापस false;

	वापस true;
पूर्ण

sमाप_प्रकार inv_icm42600_fअगरo_decode_packet(स्थिर व्योम *packet, स्थिर व्योम **accel,
					स्थिर व्योम **gyro, स्थिर पूर्णांक8_t **temp,
					स्थिर व्योम **बारtamp, अचिन्हित पूर्णांक *odr);

बाह्य स्थिर काष्ठा iio_buffer_setup_ops inv_icm42600_buffer_ops;

पूर्णांक inv_icm42600_buffer_init(काष्ठा inv_icm42600_state *st);

व्योम inv_icm42600_buffer_update_fअगरo_period(काष्ठा inv_icm42600_state *st);

पूर्णांक inv_icm42600_buffer_set_fअगरo_en(काष्ठा inv_icm42600_state *st,
				    अचिन्हित पूर्णांक fअगरo_en);

पूर्णांक inv_icm42600_buffer_update_watermark(काष्ठा inv_icm42600_state *st);

पूर्णांक inv_icm42600_buffer_fअगरo_पढ़ो(काष्ठा inv_icm42600_state *st,
				  अचिन्हित पूर्णांक max);

पूर्णांक inv_icm42600_buffer_fअगरo_parse(काष्ठा inv_icm42600_state *st);

पूर्णांक inv_icm42600_buffer_hwfअगरo_flush(काष्ठा inv_icm42600_state *st,
				     अचिन्हित पूर्णांक count);

#पूर्ण_अगर
