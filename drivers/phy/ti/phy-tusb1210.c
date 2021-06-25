<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * tusb1210.c - TUSB1210 USB ULPI PHY driver
 *
 * Copyright (C) 2015 Intel Corporation
 *
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/ulpi/driver.h>
#समावेश <linux/ulpi/regs.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/phy/ulpi_phy.h>

#घोषणा TUSB1210_VENDOR_SPECIFIC2		0x80
#घोषणा TUSB1210_VENDOR_SPECIFIC2_IHSTX_MASK	GENMASK(3, 0)
#घोषणा TUSB1210_VENDOR_SPECIFIC2_ZHSDRV_MASK	GENMASK(5, 4)
#घोषणा TUSB1210_VENDOR_SPECIFIC2_DP_MASK	BIT(6)

काष्ठा tusb1210 अणु
	काष्ठा ulpi *ulpi;
	काष्ठा phy *phy;
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा gpio_desc *gpio_cs;
	u8 venकरोr_specअगरic2;
पूर्ण;

अटल पूर्णांक tusb1210_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tusb1210 *tusb = phy_get_drvdata(phy);

	gpiod_set_value_cansleep(tusb->gpio_reset, 1);
	gpiod_set_value_cansleep(tusb->gpio_cs, 1);

	/* Restore the optional eye diagram optimization value */
	अगर (tusb->venकरोr_specअगरic2)
		ulpi_ग_लिखो(tusb->ulpi, TUSB1210_VENDOR_SPECIFIC2,
			   tusb->venकरोr_specअगरic2);

	वापस 0;
पूर्ण

अटल पूर्णांक tusb1210_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tusb1210 *tusb = phy_get_drvdata(phy);

	gpiod_set_value_cansleep(tusb->gpio_reset, 0);
	gpiod_set_value_cansleep(tusb->gpio_cs, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tusb1210_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा tusb1210 *tusb = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = ulpi_पढ़ो(tusb->ulpi, ULPI_OTG_CTRL);
	अगर (ret < 0)
		वापस ret;

	चयन (mode) अणु
	हाल PHY_MODE_USB_HOST:
		ret |= (ULPI_OTG_CTRL_DRVVBUS_EXT
			| ULPI_OTG_CTRL_ID_PULLUP
			| ULPI_OTG_CTRL_DP_PULLDOWN
			| ULPI_OTG_CTRL_DM_PULLDOWN);
		ulpi_ग_लिखो(tusb->ulpi, ULPI_OTG_CTRL, ret);
		ret |= ULPI_OTG_CTRL_DRVVBUS;
		अवरोध;
	हाल PHY_MODE_USB_DEVICE:
		ret &= ~(ULPI_OTG_CTRL_DRVVBUS
			 | ULPI_OTG_CTRL_DP_PULLDOWN
			 | ULPI_OTG_CTRL_DM_PULLDOWN);
		ulpi_ग_लिखो(tusb->ulpi, ULPI_OTG_CTRL, ret);
		ret &= ~ULPI_OTG_CTRL_DRVVBUS_EXT;
		अवरोध;
	शेष:
		/* nothing */
		वापस 0;
	पूर्ण

	वापस ulpi_ग_लिखो(tusb->ulpi, ULPI_OTG_CTRL, ret);
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_ops = अणु
	.घातer_on = tusb1210_घातer_on,
	.घातer_off = tusb1210_घातer_off,
	.set_mode = tusb1210_set_mode,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक tusb1210_probe(काष्ठा ulpi *ulpi)
अणु
	काष्ठा tusb1210 *tusb;
	u8 val, reg;

	tusb = devm_kzalloc(&ulpi->dev, माप(*tusb), GFP_KERNEL);
	अगर (!tusb)
		वापस -ENOMEM;

	tusb->gpio_reset = devm_gpiod_get_optional(&ulpi->dev, "reset",
						   GPIOD_OUT_LOW);
	अगर (IS_ERR(tusb->gpio_reset))
		वापस PTR_ERR(tusb->gpio_reset);

	gpiod_set_value_cansleep(tusb->gpio_reset, 1);

	tusb->gpio_cs = devm_gpiod_get_optional(&ulpi->dev, "cs",
						GPIOD_OUT_LOW);
	अगर (IS_ERR(tusb->gpio_cs))
		वापस PTR_ERR(tusb->gpio_cs);

	gpiod_set_value_cansleep(tusb->gpio_cs, 1);

	/*
	 * VENDOR_SPECIFIC2 रेजिस्टर in TUSB1210 can be used क्रम configuring eye
	 * diagram optimization and DP/DM swap.
	 */

	reg = ulpi_पढ़ो(ulpi, TUSB1210_VENDOR_SPECIFIC2);

	/* High speed output drive strength configuration */
	अगर (!device_property_पढ़ो_u8(&ulpi->dev, "ihstx", &val))
		u8p_replace_bits(&reg, val, (u8)TUSB1210_VENDOR_SPECIFIC2_IHSTX_MASK);

	/* High speed output impedance configuration */
	अगर (!device_property_पढ़ो_u8(&ulpi->dev, "zhsdrv", &val))
		u8p_replace_bits(&reg, val, (u8)TUSB1210_VENDOR_SPECIFIC2_ZHSDRV_MASK);

	/* DP/DM swap control */
	अगर (!device_property_पढ़ो_u8(&ulpi->dev, "datapolarity", &val))
		u8p_replace_bits(&reg, val, (u8)TUSB1210_VENDOR_SPECIFIC2_DP_MASK);

	ulpi_ग_लिखो(ulpi, TUSB1210_VENDOR_SPECIFIC2, reg);
	tusb->venकरोr_specअगरic2 = reg;

	tusb->phy = ulpi_phy_create(ulpi, &phy_ops);
	अगर (IS_ERR(tusb->phy))
		वापस PTR_ERR(tusb->phy);

	tusb->ulpi = ulpi;

	phy_set_drvdata(tusb->phy, tusb);
	ulpi_set_drvdata(ulpi, tusb);
	वापस 0;
पूर्ण

अटल व्योम tusb1210_हटाओ(काष्ठा ulpi *ulpi)
अणु
	काष्ठा tusb1210 *tusb = ulpi_get_drvdata(ulpi);

	ulpi_phy_destroy(ulpi, tusb->phy);
पूर्ण

#घोषणा TI_VENDOR_ID 0x0451

अटल स्थिर काष्ठा ulpi_device_id tusb1210_ulpi_id[] = अणु
	अणु TI_VENDOR_ID, 0x1507, पूर्ण,  /* TUSB1210 */
	अणु TI_VENDOR_ID, 0x1508, पूर्ण,  /* TUSB1211 */
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ulpi, tusb1210_ulpi_id);

अटल काष्ठा ulpi_driver tusb1210_driver = अणु
	.id_table = tusb1210_ulpi_id,
	.probe = tusb1210_probe,
	.हटाओ = tusb1210_हटाओ,
	.driver = अणु
		.name = "tusb1210",
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

module_ulpi_driver(tusb1210_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TUSB1210 ULPI PHY driver");
