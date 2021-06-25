<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम AT91 USART
 *
 * Copyright (C) 2018 Microchip Technology
 *
 * Author: Radu Pirea <radu.pirea@microchip.com>
 *
 */

#समावेश <dt-bindings/mfd/at91-usart.h>

#समावेश <linux/module.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>

अटल स्थिर काष्ठा mfd_cell at91_usart_spi_subdev =
	MFD_CELL_NAME("at91_usart_spi");

अटल स्थिर काष्ठा mfd_cell at91_usart_serial_subdev =
	MFD_CELL_NAME("atmel_usart_serial");

अटल पूर्णांक at91_usart_mode_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell;
	u32 opmode = AT91_USART_MODE_SERIAL;

	device_property_पढ़ो_u32(&pdev->dev, "atmel,usart-mode", &opmode);

	चयन (opmode) अणु
	हाल AT91_USART_MODE_SPI:
		cell = &at91_usart_spi_subdev;
		अवरोध;
	हाल AT91_USART_MODE_SERIAL:
		cell = &at91_usart_serial_subdev;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "atmel,usart-mode has an invalid value %u\n",
			opmode);
		वापस -EINVAL;
	पूर्ण

	वापस devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_AUTO, cell, 1,
			      शून्य, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id at91_usart_mode_of_match[] = अणु
	अणु .compatible = "atmel,at91rm9200-usart" पूर्ण,
	अणु .compatible = "atmel,at91sam9260-usart" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, at91_usart_mode_of_match);

अटल काष्ठा platक्रमm_driver at91_usart_mfd = अणु
	.probe	= at91_usart_mode_probe,
	.driver	= अणु
		.name		= "at91_usart_mode",
		.of_match_table	= at91_usart_mode_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(at91_usart_mfd);

MODULE_AUTHOR("Radu Pirea <radu.pirea@microchip.com>");
MODULE_DESCRIPTION("AT91 USART MFD driver");
MODULE_LICENSE("GPL v2");
