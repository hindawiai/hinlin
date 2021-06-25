<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Authors:  Sylwester Nawrocki <s.nawrocki@samsung.com>
 *	     Younghwan Joo <yhwan.joo@samsung.com>
 */
#अगर_अघोषित FIMC_IS_SENSOR_H_
#घोषणा FIMC_IS_SENSOR_H_

#समावेश <linux/of.h>
#समावेश <linux/types.h>

#घोषणा S5K6A3_OPEN_TIMEOUT		2000 /* ms */
#घोषणा S5K6A3_SENSOR_WIDTH		1392
#घोषणा S5K6A3_SENSOR_HEIGHT		1392

क्रमागत fimc_is_sensor_id अणु
	FIMC_IS_SENSOR_ID_S5K3H2 = 1,
	FIMC_IS_SENSOR_ID_S5K6A3,
	FIMC_IS_SENSOR_ID_S5K4E5,
	FIMC_IS_SENSOR_ID_S5K3H7,
	FIMC_IS_SENSOR_ID_CUSTOM,
	FIMC_IS_SENSOR_ID_END
पूर्ण;

#घोषणा IS_SENSOR_CTRL_BUS_I2C0		0
#घोषणा IS_SENSOR_CTRL_BUS_I2C1		1

काष्ठा sensor_drv_data अणु
	क्रमागत fimc_is_sensor_id id;
	/* sensor खोलो समयout in ms */
	अचिन्हित लघु खोलो_समयout;
पूर्ण;

/**
 * काष्ठा fimc_is_sensor - fimc-is sensor data काष्ठाure
 * @drvdata: a poपूर्णांकer to the sensor's parameters data काष्ठाure
 * @i2c_bus: ISP I2C bus index (0...1)
 * @test_pattern: true to enable video test pattern
 */
काष्ठा fimc_is_sensor अणु
	स्थिर काष्ठा sensor_drv_data *drvdata;
	अचिन्हित पूर्णांक i2c_bus;
	u8 test_pattern;
पूर्ण;

स्थिर काष्ठा sensor_drv_data *fimc_is_sensor_get_drvdata(
				काष्ठा device_node *node);

#पूर्ण_अगर /* FIMC_IS_SENSOR_H_ */
