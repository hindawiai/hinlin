<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics accelerometers driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 * v. 1.0.0
 */

#अगर_अघोषित ST_ACCEL_H
#घोषणा ST_ACCEL_H

#समावेश <linux/types.h>
#समावेश <linux/iio/common/st_sensors.h>

क्रमागत st_accel_type अणु
	LSM303DLH,
	LSM303DLHC,
	LIS3DH,
	LSM330D,
	LSM330DL,
	LSM330DLC,
	LIS331DLH,
	LSM303DL,
	LSM303DLM,
	LSM330,
	LSM303AGR,
	LIS2DH12,
	LIS3L02DQ,
	LNG2DM,
	H3LIS331DL,
	LIS331DL,
	LIS3LV02DL,
	LIS2DW12,
	LIS3DHH,
	LIS2DE12,
	LIS2HH12,
	ST_ACCEL_MAX,
पूर्ण;

#घोषणा H3LIS331DL_ACCEL_DEV_NAME	"h3lis331dl_accel"
#घोषणा LIS3LV02DL_ACCEL_DEV_NAME	"lis3lv02dl_accel"
#घोषणा LSM303DLHC_ACCEL_DEV_NAME	"lsm303dlhc_accel"
#घोषणा LIS3DH_ACCEL_DEV_NAME		"lis3dh"
#घोषणा LSM330D_ACCEL_DEV_NAME		"lsm330d_accel"
#घोषणा LSM330DL_ACCEL_DEV_NAME		"lsm330dl_accel"
#घोषणा LSM330DLC_ACCEL_DEV_NAME	"lsm330dlc_accel"
#घोषणा LIS331DL_ACCEL_DEV_NAME		"lis331dl_accel"
#घोषणा LIS331DLH_ACCEL_DEV_NAME	"lis331dlh"
#घोषणा LSM303DL_ACCEL_DEV_NAME		"lsm303dl_accel"
#घोषणा LSM303DLH_ACCEL_DEV_NAME	"lsm303dlh_accel"
#घोषणा LSM303DLM_ACCEL_DEV_NAME	"lsm303dlm_accel"
#घोषणा LSM330_ACCEL_DEV_NAME		"lsm330_accel"
#घोषणा LSM303AGR_ACCEL_DEV_NAME	"lsm303agr_accel"
#घोषणा LIS2DH12_ACCEL_DEV_NAME		"lis2dh12_accel"
#घोषणा LIS3L02DQ_ACCEL_DEV_NAME	"lis3l02dq"
#घोषणा LNG2DM_ACCEL_DEV_NAME		"lng2dm"
#घोषणा LIS2DW12_ACCEL_DEV_NAME		"lis2dw12"
#घोषणा LIS3DHH_ACCEL_DEV_NAME		"lis3dhh"
#घोषणा LIS3DE_ACCEL_DEV_NAME		"lis3de"
#घोषणा LIS2DE12_ACCEL_DEV_NAME		"lis2de12"
#घोषणा LIS2HH12_ACCEL_DEV_NAME		"lis2hh12"

/**
* काष्ठा st_sensors_platक्रमm_data - शेष accel platक्रमm data
* @drdy_पूर्णांक_pin: शेष accel DRDY is available on INT1 pin.
*/
अटल __maybe_unused स्थिर काष्ठा st_sensors_platक्रमm_data शेष_accel_pdata = अणु
	.drdy_पूर्णांक_pin = 1,
पूर्ण;

स्थिर काष्ठा st_sensor_settings *st_accel_get_settings(स्थिर अक्षर *name);
पूर्णांक st_accel_common_probe(काष्ठा iio_dev *indio_dev);
व्योम st_accel_common_हटाओ(काष्ठा iio_dev *indio_dev);

#अगर_घोषित CONFIG_IIO_BUFFER
पूर्णांक st_accel_allocate_ring(काष्ठा iio_dev *indio_dev);
व्योम st_accel_deallocate_ring(काष्ठा iio_dev *indio_dev);
पूर्णांक st_accel_trig_set_state(काष्ठा iio_trigger *trig, bool state);
#घोषणा ST_ACCEL_TRIGGER_SET_STATE (&st_accel_trig_set_state)
#अन्यथा /* CONFIG_IIO_BUFFER */
अटल अंतरभूत पूर्णांक st_accel_allocate_ring(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम st_accel_deallocate_ring(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण
#घोषणा ST_ACCEL_TRIGGER_SET_STATE शून्य
#पूर्ण_अगर /* CONFIG_IIO_BUFFER */

#पूर्ण_अगर /* ST_ACCEL_H */
