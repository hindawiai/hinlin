<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenFirmware bindings क्रम the MMC-over-SPI driver
 *
 * Copyright (c) MontaVista Software, Inc. 2008.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/mmc_spi.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/host.h>

MODULE_LICENSE("GPL");

काष्ठा of_mmc_spi अणु
	पूर्णांक detect_irq;
	काष्ठा mmc_spi_platक्रमm_data pdata;
पूर्ण;

अटल काष्ठा of_mmc_spi *to_of_mmc_spi(काष्ठा device *dev)
अणु
	वापस container_of(dev->platक्रमm_data, काष्ठा of_mmc_spi, pdata);
पूर्ण

अटल पूर्णांक of_mmc_spi_init(काष्ठा device *dev,
			   irqवापस_t (*irqhandler)(पूर्णांक, व्योम *), व्योम *mmc)
अणु
	काष्ठा of_mmc_spi *oms = to_of_mmc_spi(dev);

	वापस request_thपढ़ोed_irq(oms->detect_irq, शून्य, irqhandler,
					IRQF_ONESHOT, dev_name(dev), mmc);
पूर्ण

अटल व्योम of_mmc_spi_निकास(काष्ठा device *dev, व्योम *mmc)
अणु
	काष्ठा of_mmc_spi *oms = to_of_mmc_spi(dev);

	मुक्त_irq(oms->detect_irq, mmc);
पूर्ण

काष्ठा mmc_spi_platक्रमm_data *mmc_spi_get_pdata(काष्ठा spi_device *spi)
अणु
	काष्ठा mmc_host *mmc = dev_get_drvdata(&spi->dev);
	काष्ठा device *dev = &spi->dev;
	काष्ठा of_mmc_spi *oms;

	अगर (dev->platक्रमm_data || !dev_fwnode(dev))
		वापस dev->platक्रमm_data;

	oms = kzalloc(माप(*oms), GFP_KERNEL);
	अगर (!oms)
		वापस शून्य;

	अगर (mmc_of_parse_voltage(mmc, &oms->pdata.ocr_mask) < 0)
		जाओ err_ocr;

	oms->detect_irq = spi->irq;
	अगर (oms->detect_irq > 0) अणु
		oms->pdata.init = of_mmc_spi_init;
		oms->pdata.निकास = of_mmc_spi_निकास;
	पूर्ण अन्यथा अणु
		oms->pdata.caps |= MMC_CAP_NEEDS_POLL;
	पूर्ण

	dev->platक्रमm_data = &oms->pdata;
	वापस dev->platक्रमm_data;
err_ocr:
	kमुक्त(oms);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mmc_spi_get_pdata);

व्योम mmc_spi_put_pdata(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा of_mmc_spi *oms = to_of_mmc_spi(dev);

	अगर (!dev->platक्रमm_data || !dev_fwnode(dev))
		वापस;

	kमुक्त(oms);
	dev->platक्रमm_data = शून्य;
पूर्ण
EXPORT_SYMBOL(mmc_spi_put_pdata);
