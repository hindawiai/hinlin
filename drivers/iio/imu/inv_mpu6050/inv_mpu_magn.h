<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 TDK-InvenSense, Inc.
 */

#अगर_अघोषित INV_MPU_MAGN_H_
#घोषणा INV_MPU_MAGN_H_

#समावेश <linux/kernel.h>

#समावेश "inv_mpu_iio.h"

/* Magnetometer maximum frequency */
#घोषणा INV_MPU_MAGN_FREQ_HZ_MAX	50

पूर्णांक inv_mpu_magn_probe(काष्ठा inv_mpu6050_state *st);

/**
 * inv_mpu_magn_get_scale() - get magnetometer scale value
 * @st: driver पूर्णांकernal state
 *
 * Returns IIO data क्रमmat.
 */
अटल अंतरभूत पूर्णांक inv_mpu_magn_get_scale(स्थिर काष्ठा inv_mpu6050_state *st,
					 स्थिर काष्ठा iio_chan_spec *chan,
					 पूर्णांक *val, पूर्णांक *val2)
अणु
	*val = 0;
	*val2 = st->magn_raw_to_gauss[chan->address];
	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

पूर्णांक inv_mpu_magn_set_rate(स्थिर काष्ठा inv_mpu6050_state *st, पूर्णांक fअगरo_rate);

पूर्णांक inv_mpu_magn_set_orient(काष्ठा inv_mpu6050_state *st);

पूर्णांक inv_mpu_magn_पढ़ो(काष्ठा inv_mpu6050_state *st, पूर्णांक axis, पूर्णांक *val);

#पूर्ण_अगर		/* INV_MPU_MAGN_H_ */
