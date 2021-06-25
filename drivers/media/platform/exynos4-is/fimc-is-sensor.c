<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश "fimc-is-sensor.h"

अटल स्थिर काष्ठा sensor_drv_data s5k6a3_drvdata = अणु
	.id		= FIMC_IS_SENSOR_ID_S5K6A3,
	.खोलो_समयout	= S5K6A3_OPEN_TIMEOUT,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fimc_is_sensor_of_ids[] = अणु
	अणु
		.compatible	= "samsung,s5k6a3",
		.data		= &s5k6a3_drvdata,
	पूर्ण,
	अणु  पूर्ण
पूर्ण;

स्थिर काष्ठा sensor_drv_data *fimc_is_sensor_get_drvdata(
			काष्ठा device_node *node)
अणु
	स्थिर काष्ठा of_device_id *of_id;

	of_id = of_match_node(fimc_is_sensor_of_ids, node);
	वापस of_id ? of_id->data : शून्य;
पूर्ण
