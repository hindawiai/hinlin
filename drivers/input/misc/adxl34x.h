<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ADXL345/346 Three-Axis Digital Accelerometers (I2C/SPI Interface)
 *
 * Enter bugs at http://blackfin.uclinux.org/
 *
 * Copyright (C) 2009 Michael Hennerich, Analog Devices Inc.
 */

#अगर_अघोषित _ADXL34X_H_
#घोषणा _ADXL34X_H_

काष्ठा device;
काष्ठा adxl34x;

काष्ठा adxl34x_bus_ops अणु
	u16 bustype;
	पूर्णांक (*पढ़ो)(काष्ठा device *, अचिन्हित अक्षर);
	पूर्णांक (*पढ़ो_block)(काष्ठा device *, अचिन्हित अक्षर, पूर्णांक, व्योम *);
	पूर्णांक (*ग_लिखो)(काष्ठा device *, अचिन्हित अक्षर, अचिन्हित अक्षर);
पूर्ण;

व्योम adxl34x_suspend(काष्ठा adxl34x *ac);
व्योम adxl34x_resume(काष्ठा adxl34x *ac);
काष्ठा adxl34x *adxl34x_probe(काष्ठा device *dev, पूर्णांक irq,
			      bool fअगरo_delay_शेष,
			      स्थिर काष्ठा adxl34x_bus_ops *bops);
पूर्णांक adxl34x_हटाओ(काष्ठा adxl34x *ac);

#पूर्ण_अगर
