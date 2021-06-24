<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics pressures driver
 *
 * Copyright 2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 * v. 1.0.0
 */

#अगर_अघोषित ST_PRESS_H
#घोषणा ST_PRESS_H

#समावेश <linux/types.h>
#समावेश <linux/iio/common/st_sensors.h>

क्रमागत st_press_type अणु
	LPS001WP,
	LPS25H,
	LPS331AP,
	LPS22HB,
	LPS33HW,
	LPS35HW,
	LPS22HH,
	ST_PRESS_MAX,
पूर्ण;

#घोषणा LPS001WP_PRESS_DEV_NAME		"lps001wp"
#घोषणा LPS25H_PRESS_DEV_NAME		"lps25h"
#घोषणा LPS331AP_PRESS_DEV_NAME		"lps331ap"
#घोषणा LPS22HB_PRESS_DEV_NAME		"lps22hb"
#घोषणा LPS33HW_PRESS_DEV_NAME		"lps33hw"
#घोषणा LPS35HW_PRESS_DEV_NAME		"lps35hw"
#घोषणा LPS22HH_PRESS_DEV_NAME		"lps22hh"

/**
 * काष्ठा st_sensors_platक्रमm_data - शेष press platक्रमm data
 * @drdy_पूर्णांक_pin: शेष press DRDY is available on INT1 pin.
 */
अटल __maybe_unused स्थिर काष्ठा st_sensors_platक्रमm_data शेष_press_pdata = अणु
	.drdy_पूर्णांक_pin = 1,
पूर्ण;

स्थिर काष्ठा st_sensor_settings *st_press_get_settings(स्थिर अक्षर *name);
पूर्णांक st_press_common_probe(काष्ठा iio_dev *indio_dev);
व्योम st_press_common_हटाओ(काष्ठा iio_dev *indio_dev);

#अगर_घोषित CONFIG_IIO_BUFFER
पूर्णांक st_press_allocate_ring(काष्ठा iio_dev *indio_dev);
व्योम st_press_deallocate_ring(काष्ठा iio_dev *indio_dev);
पूर्णांक st_press_trig_set_state(काष्ठा iio_trigger *trig, bool state);
#घोषणा ST_PRESS_TRIGGER_SET_STATE (&st_press_trig_set_state)
#अन्यथा /* CONFIG_IIO_BUFFER */
अटल अंतरभूत पूर्णांक st_press_allocate_ring(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम st_press_deallocate_ring(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण
#घोषणा ST_PRESS_TRIGGER_SET_STATE शून्य
#पूर्ण_अगर /* CONFIG_IIO_BUFFER */

#पूर्ण_अगर /* ST_PRESS_H */
