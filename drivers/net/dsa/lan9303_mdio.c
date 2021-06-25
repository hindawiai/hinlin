<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Pengutronix, Juergen Borleis <kernel@pengutronix.de>
 *
 * Partially based on a patch from
 * Copyright (c) 2014 Stefan Roese <sr@denx.de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>

#समावेश "lan9303.h"

/* Generate phy-addr and -reg from the input address */
#घोषणा PHY_ADDR(x) ((((x) >> 6) + 0x10) & 0x1f)
#घोषणा PHY_REG(x) (((x) >> 1) & 0x1f)

काष्ठा lan9303_mdio अणु
	काष्ठा mdio_device *device;
	काष्ठा lan9303 chip;
पूर्ण;

अटल व्योम lan9303_mdio_real_ग_लिखो(काष्ठा mdio_device *mdio, पूर्णांक reg, u16 val)
अणु
	mdio->bus->ग_लिखो(mdio->bus, PHY_ADDR(reg), PHY_REG(reg), val);
पूर्ण

अटल पूर्णांक lan9303_mdio_ग_लिखो(व्योम *ctx, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा lan9303_mdio *sw_dev = (काष्ठा lan9303_mdio *)ctx;

	reg <<= 2; /* reg num to offset */
	mutex_lock(&sw_dev->device->bus->mdio_lock);
	lan9303_mdio_real_ग_लिखो(sw_dev->device, reg, val & 0xffff);
	lan9303_mdio_real_ग_लिखो(sw_dev->device, reg + 2, (val >> 16) & 0xffff);
	mutex_unlock(&sw_dev->device->bus->mdio_lock);

	वापस 0;
पूर्ण

अटल u16 lan9303_mdio_real_पढ़ो(काष्ठा mdio_device *mdio, पूर्णांक reg)
अणु
	वापस mdio->bus->पढ़ो(mdio->bus, PHY_ADDR(reg), PHY_REG(reg));
पूर्ण

अटल पूर्णांक lan9303_mdio_पढ़ो(व्योम *ctx, uपूर्णांक32_t reg, uपूर्णांक32_t *val)
अणु
	काष्ठा lan9303_mdio *sw_dev = (काष्ठा lan9303_mdio *)ctx;

	reg <<= 2; /* reg num to offset */
	mutex_lock(&sw_dev->device->bus->mdio_lock);
	*val = lan9303_mdio_real_पढ़ो(sw_dev->device, reg);
	*val |= (lan9303_mdio_real_पढ़ो(sw_dev->device, reg + 2) << 16);
	mutex_unlock(&sw_dev->device->bus->mdio_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lan9303_mdio_phy_ग_लिखो(काष्ठा lan9303 *chip, पूर्णांक phy, पूर्णांक reg,
				  u16 val)
अणु
	काष्ठा lan9303_mdio *sw_dev = dev_get_drvdata(chip->dev);

	वापस mdiobus_ग_लिखो_nested(sw_dev->device->bus, phy, reg, val);
पूर्ण

अटल पूर्णांक lan9303_mdio_phy_पढ़ो(काष्ठा lan9303 *chip, पूर्णांक phy,  पूर्णांक reg)
अणु
	काष्ठा lan9303_mdio *sw_dev = dev_get_drvdata(chip->dev);

	वापस mdiobus_पढ़ो_nested(sw_dev->device->bus, phy, reg);
पूर्ण

अटल स्थिर काष्ठा lan9303_phy_ops lan9303_mdio_phy_ops = अणु
	.phy_पढ़ो = lan9303_mdio_phy_पढ़ो,
	.phy_ग_लिखो = lan9303_mdio_phy_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lan9303_mdio_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 1,
	.can_multi_ग_लिखो = true,
	.max_रेजिस्टर = 0x0ff, /* address bits 0..1 are not used */
	.reg_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,

	.अस्थिर_table = &lan9303_रेजिस्टर_set,
	.wr_table = &lan9303_रेजिस्टर_set,
	.rd_table = &lan9303_रेजिस्टर_set,

	.reg_पढ़ो = lan9303_mdio_पढ़ो,
	.reg_ग_लिखो = lan9303_mdio_ग_लिखो,

	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक lan9303_mdio_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा lan9303_mdio *sw_dev;
	पूर्णांक ret;

	sw_dev = devm_kzalloc(&mdiodev->dev, माप(काष्ठा lan9303_mdio),
			      GFP_KERNEL);
	अगर (!sw_dev)
		वापस -ENOMEM;

	sw_dev->chip.regmap = devm_regmap_init(&mdiodev->dev, शून्य, sw_dev,
					       &lan9303_mdio_regmap_config);
	अगर (IS_ERR(sw_dev->chip.regmap)) अणु
		ret = PTR_ERR(sw_dev->chip.regmap);
		dev_err(&mdiodev->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* link क्रमward and backward */
	sw_dev->device = mdiodev;
	dev_set_drvdata(&mdiodev->dev, sw_dev);
	sw_dev->chip.dev = &mdiodev->dev;

	sw_dev->chip.ops = &lan9303_mdio_phy_ops;

	ret = lan9303_probe(&sw_dev->chip, mdiodev->dev.of_node);
	अगर (ret != 0)
		वापस ret;

	dev_info(&mdiodev->dev, "LAN9303 MDIO driver loaded successfully\n");

	वापस 0;
पूर्ण

अटल व्योम lan9303_mdio_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा lan9303_mdio *sw_dev = dev_get_drvdata(&mdiodev->dev);

	अगर (!sw_dev)
		वापस;

	lan9303_हटाओ(&sw_dev->chip);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा of_device_id lan9303_mdio_of_match[] = अणु
	अणु .compatible = "smsc,lan9303-mdio" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lan9303_mdio_of_match);

अटल काष्ठा mdio_driver lan9303_mdio_driver = अणु
	.mdiodrv.driver = अणु
		.name = "LAN9303_MDIO",
		.of_match_table = of_match_ptr(lan9303_mdio_of_match),
	पूर्ण,
	.probe  = lan9303_mdio_probe,
	.हटाओ = lan9303_mdio_हटाओ,
पूर्ण;
mdio_module_driver(lan9303_mdio_driver);

MODULE_AUTHOR("Stefan Roese <sr@denx.de>, Juergen Borleis <kernel@pengutronix.de>");
MODULE_DESCRIPTION("Driver for SMSC/Microchip LAN9303 three port ethernet switch in MDIO managed mode");
MODULE_LICENSE("GPL v2");
