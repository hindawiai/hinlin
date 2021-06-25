<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics gyroscopes driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 * v. 1.0.0
 */

#अगर_अघोषित ST_GYRO_H
#घोषणा ST_GYRO_H

#समावेश <linux/types.h>
#समावेश <linux/iio/common/st_sensors.h>

#घोषणा L3G4200D_GYRO_DEV_NAME		"l3g4200d"
#घोषणा LSM330D_GYRO_DEV_NAME		"lsm330d_gyro"
#घोषणा LSM330DL_GYRO_DEV_NAME		"lsm330dl_gyro"
#घोषणा LSM330DLC_GYRO_DEV_NAME		"lsm330dlc_gyro"
#घोषणा L3GD20_GYRO_DEV_NAME		"l3gd20"
#घोषणा L3GD20H_GYRO_DEV_NAME		"l3gd20h"
#घोषणा L3G4IS_GYRO_DEV_NAME		"l3g4is_ui"
#घोषणा LSM330_GYRO_DEV_NAME		"lsm330_gyro"
#घोषणा LSM9DS0_GYRO_DEV_NAME		"lsm9ds0_gyro"

/**
 * काष्ठा st_sensors_platक्रमm_data - gyro platक्रमm data
 * @drdy_पूर्णांक_pin: DRDY on gyros is available only on INT2 pin.
 */
अटल __maybe_unused स्थिर काष्ठा st_sensors_platक्रमm_data gyro_pdata = अणु
	.drdy_पूर्णांक_pin = 2,
पूर्ण;

स्थिर काष्ठा st_sensor_settings *st_gyro_get_settings(स्थिर अक्षर *name);
पूर्णांक st_gyro_common_probe(काष्ठा iio_dev *indio_dev);
व्योम st_gyro_common_हटाओ(काष्ठा iio_dev *indio_dev);

#अगर_घोषित CONFIG_IIO_BUFFER
पूर्णांक st_gyro_allocate_ring(काष्ठा iio_dev *indio_dev);
व्योम st_gyro_deallocate_ring(काष्ठा iio_dev *indio_dev);
पूर्णांक st_gyro_trig_set_state(काष्ठा iio_trigger *trig, bool state);
#घोषणा ST_GYRO_TRIGGER_SET_STATE (&st_gyro_trig_set_state)
#अन्यथा /* CONFIG_IIO_BUFFER */
अटल अंतरभूत पूर्णांक st_gyro_allocate_ring(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम st_gyro_deallocate_ring(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण
#घोषणा ST_GYRO_TRIGGER_SET_STATE शून्य
#पूर्ण_अगर /* CONFIG_IIO_BUFFER */

#पूर्ण_अगर /* ST_GYRO_H */
