<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * s3c24xx/s3c64xx SoC series Camera Interface (CAMIF) driver
 *
 * Copyright (C) 2012 Sylwester Nawrocki <sylvester.nawrocki@gmail.com>
*/

#अगर_अघोषित MEDIA_S3C_CAMIF_
#घोषणा MEDIA_S3C_CAMIF_

#समावेश <linux/i2c.h>
#समावेश <media/v4l2-mediabus.h>

/**
 * काष्ठा s3c_camअगर_sensor_info - an image sensor description
 * @i2c_board_info: poपूर्णांकer to an I2C sensor subdevice board info
 * @घड़ी_frequency: frequency of the घड़ी the host provides to a sensor
 * @mbus_type: media bus type
 * @i2c_bus_num: i2c control bus id the sensor is attached to
 * @flags: the parallel bus flags defining संकेतs polarity (V4L2_MBUS_*)
 * @use_field: 1 अगर parallel bus FIELD संकेत is used (only s3c64xx)
 */
काष्ठा s3c_camअगर_sensor_info अणु
	काष्ठा i2c_board_info i2c_board_info;
	अचिन्हित दीर्घ घड़ी_frequency;
	क्रमागत v4l2_mbus_type mbus_type;
	u16 i2c_bus_num;
	u16 flags;
	u8 use_field;
पूर्ण;

काष्ठा s3c_camअगर_plat_data अणु
	काष्ठा s3c_camअगर_sensor_info sensor;
	पूर्णांक (*gpio_get)(व्योम);
	पूर्णांक (*gpio_put)(व्योम);
पूर्ण;

#पूर्ण_अगर /* MEDIA_S3C_CAMIF_ */
