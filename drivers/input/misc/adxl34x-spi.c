<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADLX345/346 Three-Axis Digital Accelerometers (SPI Interface)
 *
 * Enter bugs at http://blackfin.uclinux.org/
 *
 * Copyright (C) 2009 Michael Hennerich, Analog Devices Inc.
 */

#समावेश <linux/input.h>	/* BUS_SPI */
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/pm.h>
#समावेश <linux/types.h>
#समावेश "adxl34x.h"

#घोषणा MAX_SPI_FREQ_HZ		5000000
#घोषणा MAX_FREQ_NO_FIFODELAY	1500000
#घोषणा ADXL34X_CMD_MULTB	(1 << 6)
#घोषणा ADXL34X_CMD_READ	(1 << 7)
#घोषणा ADXL34X_WRITECMD(reg)	(reg & 0x3F)
#घोषणा ADXL34X_READCMD(reg)	(ADXL34X_CMD_READ | (reg & 0x3F))
#घोषणा ADXL34X_READMB_CMD(reg) (ADXL34X_CMD_READ | ADXL34X_CMD_MULTB \
					| (reg & 0x3F))

अटल पूर्णांक adxl34x_spi_पढ़ो(काष्ठा device *dev, अचिन्हित अक्षर reg)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर cmd;

	cmd = ADXL34X_READCMD(reg);

	वापस spi_w8r8(spi, cmd);
पूर्ण

अटल पूर्णांक adxl34x_spi_ग_लिखो(काष्ठा device *dev,
			     अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	अचिन्हित अक्षर buf[2];

	buf[0] = ADXL34X_WRITECMD(reg);
	buf[1] = val;

	वापस spi_ग_लिखो(spi, buf, माप(buf));
पूर्ण

अटल पूर्णांक adxl34x_spi_पढ़ो_block(काष्ठा device *dev,
				  अचिन्हित अक्षर reg, पूर्णांक count,
				  व्योम *buf)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	sमाप_प्रकार status;

	reg = ADXL34X_READMB_CMD(reg);
	status = spi_ग_लिखो_then_पढ़ो(spi, &reg, 1, buf, count);

	वापस (status < 0) ? status : 0;
पूर्ण

अटल स्थिर काष्ठा adxl34x_bus_ops adxl34x_spi_bops = अणु
	.bustype	= BUS_SPI,
	.ग_लिखो		= adxl34x_spi_ग_लिखो,
	.पढ़ो		= adxl34x_spi_पढ़ो,
	.पढ़ो_block	= adxl34x_spi_पढ़ो_block,
पूर्ण;

अटल पूर्णांक adxl34x_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा adxl34x *ac;

	/* करोn't exceed max specअगरied SPI CLK frequency */
	अगर (spi->max_speed_hz > MAX_SPI_FREQ_HZ) अणु
		dev_err(&spi->dev, "SPI CLK %d Hz too fast\n", spi->max_speed_hz);
		वापस -EINVAL;
	पूर्ण

	ac = adxl34x_probe(&spi->dev, spi->irq,
			   spi->max_speed_hz > MAX_FREQ_NO_FIFODELAY,
			   &adxl34x_spi_bops);

	अगर (IS_ERR(ac))
		वापस PTR_ERR(ac);

	spi_set_drvdata(spi, ac);

	वापस 0;
पूर्ण

अटल पूर्णांक adxl34x_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा adxl34x *ac = spi_get_drvdata(spi);

	वापस adxl34x_हटाओ(ac);
पूर्ण

अटल पूर्णांक __maybe_unused adxl34x_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा adxl34x *ac = spi_get_drvdata(spi);

	adxl34x_suspend(ac);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused adxl34x_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा adxl34x *ac = spi_get_drvdata(spi);

	adxl34x_resume(ac);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(adxl34x_spi_pm, adxl34x_spi_suspend,
			 adxl34x_spi_resume);

अटल काष्ठा spi_driver adxl34x_driver = अणु
	.driver = अणु
		.name = "adxl34x",
		.pm = &adxl34x_spi_pm,
	पूर्ण,
	.probe   = adxl34x_spi_probe,
	.हटाओ  = adxl34x_spi_हटाओ,
पूर्ण;

module_spi_driver(adxl34x_driver);

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("ADXL345/346 Three-Axis Digital Accelerometer SPI Bus Driver");
MODULE_LICENSE("GPL");
