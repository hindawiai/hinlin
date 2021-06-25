<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7606 Parallel Interface ADC driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश <linux/iio/iपन.स>
#समावेश "ad7606.h"

अटल पूर्णांक ad7606_par16_पढ़ो_block(काष्ठा device *dev,
				   पूर्णांक count, व्योम *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	insw((अचिन्हित दीर्घ)st->base_address, buf, count);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ad7606_bus_ops ad7606_par16_bops = अणु
	.पढ़ो_block = ad7606_par16_पढ़ो_block,
पूर्ण;

अटल पूर्णांक ad7606_par8_पढ़ो_block(काष्ठा device *dev,
				  पूर्णांक count, व्योम *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	insb((अचिन्हित दीर्घ)st->base_address, buf, count * 2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ad7606_bus_ops ad7606_par8_bops = अणु
	.पढ़ो_block = ad7606_par8_पढ़ो_block,
पूर्ण;

अटल पूर्णांक ad7606_par_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	काष्ठा resource *res;
	व्योम __iomem *addr;
	resource_माप_प्रकार remap_size;
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);

	remap_size = resource_size(res);

	वापस ad7606_probe(&pdev->dev, irq, addr,
			    id->name, id->driver_data,
			    remap_size > 1 ? &ad7606_par16_bops :
			    &ad7606_par8_bops);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ad7606_driver_ids[] = अणु
	अणु .name	= "ad7605-4", .driver_data = ID_AD7605_4, पूर्ण,
	अणु .name	= "ad7606-4", .driver_data = ID_AD7606_4, पूर्ण,
	अणु .name	= "ad7606-6", .driver_data = ID_AD7606_6, पूर्ण,
	अणु .name	= "ad7606-8", .driver_data = ID_AD7606_8, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, ad7606_driver_ids);

अटल स्थिर काष्ठा of_device_id ad7606_of_match[] = अणु
	अणु .compatible = "adi,ad7605-4" पूर्ण,
	अणु .compatible = "adi,ad7606-4" पूर्ण,
	अणु .compatible = "adi,ad7606-6" पूर्ण,
	अणु .compatible = "adi,ad7606-8" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7606_of_match);

अटल काष्ठा platक्रमm_driver ad7606_driver = अणु
	.probe = ad7606_par_probe,
	.id_table = ad7606_driver_ids,
	.driver = अणु
		.name = "ad7606",
		.pm = AD7606_PM_OPS,
		.of_match_table = ad7606_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ad7606_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7606 ADC");
MODULE_LICENSE("GPL v2");
