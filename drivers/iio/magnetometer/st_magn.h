<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics magnetometers driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 * v. 1.0.0
 */

#अगर_अघोषित ST_MAGN_H
#घोषणा ST_MAGN_H

#समावेश <linux/types.h>
#समावेश <linux/iio/common/st_sensors.h>

#घोषणा LSM303DLH_MAGN_DEV_NAME		"lsm303dlh_magn"
#घोषणा LSM303DLHC_MAGN_DEV_NAME	"lsm303dlhc_magn"
#घोषणा LSM303DLM_MAGN_DEV_NAME		"lsm303dlm_magn"
#घोषणा LIS3MDL_MAGN_DEV_NAME		"lis3mdl"
#घोषणा LSM303AGR_MAGN_DEV_NAME		"lsm303agr_magn"
#घोषणा LIS2MDL_MAGN_DEV_NAME		"lis2mdl"
#घोषणा LSM9DS1_MAGN_DEV_NAME		"lsm9ds1_magn"
#घोषणा IIS2MDC_MAGN_DEV_NAME		"iis2mdc"

स्थिर काष्ठा st_sensor_settings *st_magn_get_settings(स्थिर अक्षर *name);
पूर्णांक st_magn_common_probe(काष्ठा iio_dev *indio_dev);
व्योम st_magn_common_हटाओ(काष्ठा iio_dev *indio_dev);

#अगर_घोषित CONFIG_IIO_BUFFER
पूर्णांक st_magn_allocate_ring(काष्ठा iio_dev *indio_dev);
व्योम st_magn_deallocate_ring(काष्ठा iio_dev *indio_dev);
पूर्णांक st_magn_trig_set_state(काष्ठा iio_trigger *trig, bool state);
#घोषणा ST_MAGN_TRIGGER_SET_STATE (&st_magn_trig_set_state)
#अन्यथा /* CONFIG_IIO_BUFFER */
अटल अंतरभूत पूर्णांक st_magn_probe_trigger(काष्ठा iio_dev *indio_dev, पूर्णांक irq)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम st_magn_हटाओ_trigger(काष्ठा iio_dev *indio_dev, पूर्णांक irq)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक st_magn_allocate_ring(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम st_magn_deallocate_ring(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण
#घोषणा ST_MAGN_TRIGGER_SET_STATE शून्य
#पूर्ण_अगर /* CONFIG_IIO_BUFFER */

#पूर्ण_अगर /* ST_MAGN_H */
