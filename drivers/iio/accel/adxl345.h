<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ADXL345 3-Axis Digital Accelerometer
 *
 * Copyright (c) 2017 Eva Rachel Retuya <eraretuya@gmail.com>
 */

#अगर_अघोषित _ADXL345_H_
#घोषणा _ADXL345_H_

क्रमागत adxl345_device_type अणु
	ADXL345,
	ADXL375,
पूर्ण;

पूर्णांक adxl345_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		       क्रमागत adxl345_device_type type, स्थिर अक्षर *name);
पूर्णांक adxl345_core_हटाओ(काष्ठा device *dev);

#पूर्ण_अगर /* _ADXL345_H_ */
