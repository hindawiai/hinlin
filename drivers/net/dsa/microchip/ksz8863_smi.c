<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip KSZ8863 series रेजिस्टर access through SMI
 *
 * Copyright (C) 2019 Pengutronix, Michael Grzeschik <kernel@pengutronix.de>
 */

#समावेश "ksz8.h"
#समावेश "ksz_common.h"

/* Serial Management Interface (SMI) uses the following frame क्रमmat:
 *
 *       preamble|start|Read/Write|  PHY   |  REG  |TA|   Data bits      | Idle
 *               |frame| OP code  |address |address|  |                  |
 * पढ़ो | 32x1तखs | 01  |    00    | 1xRRR  | RRRRR |Z0| 00000000DDDDDDDD |  Z
 * ग_लिखो| 32x1तखs | 01  |    00    | 0xRRR  | RRRRR |10| xxxxxxxxDDDDDDDD |  Z
 *
 */

#घोषणा SMI_KSZ88XX_READ_PHY	BIT(4)

अटल पूर्णांक ksz8863_mdio_पढ़ो(व्योम *ctx, स्थिर व्योम *reg_buf, माप_प्रकार reg_len,
			     व्योम *val_buf, माप_प्रकार val_len)
अणु
	काष्ठा ksz_device *dev = ctx;
	काष्ठा mdio_device *mdev;
	u8 reg = *(u8 *)reg_buf;
	u8 *val = val_buf;
	काष्ठा ksz8 *ksz8;
	पूर्णांक i, ret = 0;

	ksz8 = dev->priv;
	mdev = ksz8->priv;

	mutex_lock_nested(&mdev->bus->mdio_lock, MDIO_MUTEX_NESTED);
	क्रम (i = 0; i < val_len; i++) अणु
		पूर्णांक पंचांगp = reg + i;

		ret = __mdiobus_पढ़ो(mdev->bus, ((पंचांगp & 0xE0) >> 5) |
				     SMI_KSZ88XX_READ_PHY, पंचांगp);
		अगर (ret < 0)
			जाओ out;

		val[i] = ret;
	पूर्ण
	ret = 0;

 out:
	mutex_unlock(&mdev->bus->mdio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ksz8863_mdio_ग_लिखो(व्योम *ctx, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा ksz_device *dev = ctx;
	काष्ठा mdio_device *mdev;
	काष्ठा ksz8 *ksz8;
	पूर्णांक i, ret = 0;
	u32 reg;
	u8 *val;

	ksz8 = dev->priv;
	mdev = ksz8->priv;

	val = (u8 *)(data + 4);
	reg = *(u32 *)data;

	mutex_lock_nested(&mdev->bus->mdio_lock, MDIO_MUTEX_NESTED);
	क्रम (i = 0; i < (count - 4); i++) अणु
		पूर्णांक पंचांगp = reg + i;

		ret = __mdiobus_ग_लिखो(mdev->bus, ((पंचांगp & 0xE0) >> 5),
				      पंचांगp, val[i]);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

 out:
	mutex_unlock(&mdev->bus->mdio_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_smi[] = अणु
	अणु
		.पढ़ो = ksz8863_mdio_पढ़ो,
		.ग_लिखो = ksz8863_mdio_ग_लिखो,
		.max_raw_पढ़ो = 1,
		.max_raw_ग_लिखो = 1,
	पूर्ण,
	अणु
		.पढ़ो = ksz8863_mdio_पढ़ो,
		.ग_लिखो = ksz8863_mdio_ग_लिखो,
		.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
		.max_raw_पढ़ो = 2,
		.max_raw_ग_लिखो = 2,
	पूर्ण,
	अणु
		.पढ़ो = ksz8863_mdio_पढ़ो,
		.ग_लिखो = ksz8863_mdio_ग_लिखो,
		.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
		.max_raw_पढ़ो = 4,
		.max_raw_ग_लिखो = 4,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_config ksz8863_regmap_config[] = अणु
	अणु
		.name = "#8",
		.reg_bits = 8,
		.pad_bits = 24,
		.val_bits = 8,
		.cache_type = REGCACHE_NONE,
		.use_single_पढ़ो = 1,
		.lock = ksz_regmap_lock,
		.unlock = ksz_regmap_unlock,
	पूर्ण,
	अणु
		.name = "#16",
		.reg_bits = 8,
		.pad_bits = 24,
		.val_bits = 16,
		.cache_type = REGCACHE_NONE,
		.use_single_पढ़ो = 1,
		.lock = ksz_regmap_lock,
		.unlock = ksz_regmap_unlock,
	पूर्ण,
	अणु
		.name = "#32",
		.reg_bits = 8,
		.pad_bits = 24,
		.val_bits = 32,
		.cache_type = REGCACHE_NONE,
		.use_single_पढ़ो = 1,
		.lock = ksz_regmap_lock,
		.unlock = ksz_regmap_unlock,
	पूर्ण
पूर्ण;

अटल पूर्णांक ksz8863_smi_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा regmap_config rc;
	काष्ठा ksz_device *dev;
	काष्ठा ksz8 *ksz8;
	पूर्णांक ret;
	पूर्णांक i;

	ksz8 = devm_kzalloc(&mdiodev->dev, माप(काष्ठा ksz8), GFP_KERNEL);
	अगर (!ksz8)
		वापस -ENOMEM;

	ksz8->priv = mdiodev;

	dev = ksz_चयन_alloc(&mdiodev->dev, ksz8);
	अगर (!dev)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(ksz8863_regmap_config); i++) अणु
		rc = ksz8863_regmap_config[i];
		rc.lock_arg = &dev->regmap_mutex;
		dev->regmap[i] = devm_regmap_init(&mdiodev->dev,
						  &regmap_smi[i], dev,
						  &rc);
		अगर (IS_ERR(dev->regmap[i])) अणु
			ret = PTR_ERR(dev->regmap[i]);
			dev_err(&mdiodev->dev,
				"Failed to initialize regmap%i: %d\n",
				ksz8863_regmap_config[i].val_bits, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (mdiodev->dev.platक्रमm_data)
		dev->pdata = mdiodev->dev.platक्रमm_data;

	ret = ksz8_चयन_रेजिस्टर(dev);

	/* Main DSA driver may not be started yet. */
	अगर (ret)
		वापस ret;

	dev_set_drvdata(&mdiodev->dev, dev);

	वापस 0;
पूर्ण

अटल व्योम ksz8863_smi_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा ksz_device *dev = dev_get_drvdata(&mdiodev->dev);

	अगर (dev)
		ksz_चयन_हटाओ(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ksz8863_dt_ids[] = अणु
	अणु .compatible = "microchip,ksz8863" पूर्ण,
	अणु .compatible = "microchip,ksz8873" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ksz8863_dt_ids);

अटल काष्ठा mdio_driver ksz8863_driver = अणु
	.probe	= ksz8863_smi_probe,
	.हटाओ	= ksz8863_smi_हटाओ,
	.mdiodrv.driver = अणु
		.name	= "ksz8863-switch",
		.of_match_table = ksz8863_dt_ids,
	पूर्ण,
पूर्ण;

mdio_module_driver(ksz8863_driver);

MODULE_AUTHOR("Michael Grzeschik <m.grzeschik@pengutronix.de>");
MODULE_DESCRIPTION("Microchip KSZ8863 SMI Switch driver");
MODULE_LICENSE("GPL v2");
