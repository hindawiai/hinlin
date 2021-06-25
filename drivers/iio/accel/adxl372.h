<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * ADXL372 3-Axis Digital Accelerometer
 *
 * Copyright 2018 Analog Devices Inc.
 */

#अगर_अघोषित _ADXL372_H_
#घोषणा _ADXL372_H_

#घोषणा ADXL372_REVID	0x03

पूर्णांक adxl372_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		  पूर्णांक irq, स्थिर अक्षर *name);
bool adxl372_पढ़ोable_noinc_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg);

#पूर्ण_अगर /* _ADXL372_H_ */
