<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Realtek Simple Management Interface (SMI) driver
 * It can be discussed how "simple" this पूर्णांकerface is.
 *
 * The SMI protocol piggy-backs the MDIO MDC and MDIO संकेतs levels
 * but the protocol is not MDIO at all. Instead it is a Realtek
 * pecularity that need to bit-bang the lines in a special way to
 * communicate with the चयन.
 *
 * ASICs we पूर्णांकend to support with this driver:
 *
 * RTL8366   - The original version, apparently
 * RTL8369   - Similar enough to have the same datsheet as RTL8366
 * RTL8366RB - Probably पढ़ोs out "RTL8366 revision B", has a quite
 *             dअगरferent रेजिस्टर layout from the other two
 * RTL8366S  - Is this "RTL8366 super"?
 * RTL8367   - Has an OpenWRT driver as well
 * RTL8368S  - Seems to be an alternative name क्रम RTL8366RB
 * RTL8370   - Also uses SMI
 *
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 * Copyright (C) 2010 Antti Seppथअlथअ <a.seppala@gmail.com>
 * Copyright (C) 2010 Roman Yeryomin <roman@advem.lv>
 * Copyright (C) 2011 Colin Leitner <colin.leitner@googlemail.com>
 * Copyright (C) 2009-2010 Gabor Juhos <juhosg@खोलोwrt.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_bridge.h>

#समावेश "realtek-smi-core.h"

#घोषणा REALTEK_SMI_ACK_RETRY_COUNT		5
#घोषणा REALTEK_SMI_HW_STOP_DELAY		25	/* msecs */
#घोषणा REALTEK_SMI_HW_START_DELAY		100	/* msecs */

अटल अंतरभूत व्योम realtek_smi_clk_delay(काष्ठा realtek_smi *smi)
अणु
	ndelay(smi->clk_delay);
पूर्ण

अटल व्योम realtek_smi_start(काष्ठा realtek_smi *smi)
अणु
	/* Set GPIO pins to output mode, with initial state:
	 * SCK = 0, SDA = 1
	 */
	gpiod_direction_output(smi->mdc, 0);
	gpiod_direction_output(smi->mdio, 1);
	realtek_smi_clk_delay(smi);

	/* CLK 1: 0 -> 1, 1 -> 0 */
	gpiod_set_value(smi->mdc, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 0);
	realtek_smi_clk_delay(smi);

	/* CLK 2: */
	gpiod_set_value(smi->mdc, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdio, 0);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 0);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdio, 1);
पूर्ण

अटल व्योम realtek_smi_stop(काष्ठा realtek_smi *smi)
अणु
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdio, 0);
	gpiod_set_value(smi->mdc, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdio, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 1);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 0);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 1);

	/* Add a click */
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 0);
	realtek_smi_clk_delay(smi);
	gpiod_set_value(smi->mdc, 1);

	/* Set GPIO pins to input mode */
	gpiod_direction_input(smi->mdio);
	gpiod_direction_input(smi->mdc);
पूर्ण

अटल व्योम realtek_smi_ग_लिखो_bits(काष्ठा realtek_smi *smi, u32 data, u32 len)
अणु
	क्रम (; len > 0; len--) अणु
		realtek_smi_clk_delay(smi);

		/* Prepare data */
		gpiod_set_value(smi->mdio, !!(data & (1 << (len - 1))));
		realtek_smi_clk_delay(smi);

		/* Clocking */
		gpiod_set_value(smi->mdc, 1);
		realtek_smi_clk_delay(smi);
		gpiod_set_value(smi->mdc, 0);
	पूर्ण
पूर्ण

अटल व्योम realtek_smi_पढ़ो_bits(काष्ठा realtek_smi *smi, u32 len, u32 *data)
अणु
	gpiod_direction_input(smi->mdio);

	क्रम (*data = 0; len > 0; len--) अणु
		u32 u;

		realtek_smi_clk_delay(smi);

		/* Clocking */
		gpiod_set_value(smi->mdc, 1);
		realtek_smi_clk_delay(smi);
		u = !!gpiod_get_value(smi->mdio);
		gpiod_set_value(smi->mdc, 0);

		*data |= (u << (len - 1));
	पूर्ण

	gpiod_direction_output(smi->mdio, 0);
पूर्ण

अटल पूर्णांक realtek_smi_रुको_क्रम_ack(काष्ठा realtek_smi *smi)
अणु
	पूर्णांक retry_cnt;

	retry_cnt = 0;
	करो अणु
		u32 ack;

		realtek_smi_पढ़ो_bits(smi, 1, &ack);
		अगर (ack == 0)
			अवरोध;

		अगर (++retry_cnt > REALTEK_SMI_ACK_RETRY_COUNT) अणु
			dev_err(smi->dev, "ACK timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल पूर्णांक realtek_smi_ग_लिखो_byte(काष्ठा realtek_smi *smi, u8 data)
अणु
	realtek_smi_ग_लिखो_bits(smi, data, 8);
	वापस realtek_smi_रुको_क्रम_ack(smi);
पूर्ण

अटल पूर्णांक realtek_smi_ग_लिखो_byte_noack(काष्ठा realtek_smi *smi, u8 data)
अणु
	realtek_smi_ग_लिखो_bits(smi, data, 8);
	वापस 0;
पूर्ण

अटल पूर्णांक realtek_smi_पढ़ो_byte0(काष्ठा realtek_smi *smi, u8 *data)
अणु
	u32 t;

	/* Read data */
	realtek_smi_पढ़ो_bits(smi, 8, &t);
	*data = (t & 0xff);

	/* Send an ACK */
	realtek_smi_ग_लिखो_bits(smi, 0x00, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक realtek_smi_पढ़ो_byte1(काष्ठा realtek_smi *smi, u8 *data)
अणु
	u32 t;

	/* Read data */
	realtek_smi_पढ़ो_bits(smi, 8, &t);
	*data = (t & 0xff);

	/* Send an ACK */
	realtek_smi_ग_लिखो_bits(smi, 0x01, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक realtek_smi_पढ़ो_reg(काष्ठा realtek_smi *smi, u32 addr, u32 *data)
अणु
	अचिन्हित दीर्घ flags;
	u8 lo = 0;
	u8 hi = 0;
	पूर्णांक ret;

	spin_lock_irqsave(&smi->lock, flags);

	realtek_smi_start(smi);

	/* Send READ command */
	ret = realtek_smi_ग_लिखो_byte(smi, smi->cmd_पढ़ो);
	अगर (ret)
		जाओ out;

	/* Set ADDR[7:0] */
	ret = realtek_smi_ग_लिखो_byte(smi, addr & 0xff);
	अगर (ret)
		जाओ out;

	/* Set ADDR[15:8] */
	ret = realtek_smi_ग_लिखो_byte(smi, addr >> 8);
	अगर (ret)
		जाओ out;

	/* Read DATA[7:0] */
	realtek_smi_पढ़ो_byte0(smi, &lo);
	/* Read DATA[15:8] */
	realtek_smi_पढ़ो_byte1(smi, &hi);

	*data = ((u32)lo) | (((u32)hi) << 8);

	ret = 0;

 out:
	realtek_smi_stop(smi);
	spin_unlock_irqrestore(&smi->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक realtek_smi_ग_लिखो_reg(काष्ठा realtek_smi *smi,
				 u32 addr, u32 data, bool ack)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&smi->lock, flags);

	realtek_smi_start(smi);

	/* Send WRITE command */
	ret = realtek_smi_ग_लिखो_byte(smi, smi->cmd_ग_लिखो);
	अगर (ret)
		जाओ out;

	/* Set ADDR[7:0] */
	ret = realtek_smi_ग_लिखो_byte(smi, addr & 0xff);
	अगर (ret)
		जाओ out;

	/* Set ADDR[15:8] */
	ret = realtek_smi_ग_लिखो_byte(smi, addr >> 8);
	अगर (ret)
		जाओ out;

	/* Write DATA[7:0] */
	ret = realtek_smi_ग_लिखो_byte(smi, data & 0xff);
	अगर (ret)
		जाओ out;

	/* Write DATA[15:8] */
	अगर (ack)
		ret = realtek_smi_ग_लिखो_byte(smi, data >> 8);
	अन्यथा
		ret = realtek_smi_ग_लिखो_byte_noack(smi, data >> 8);
	अगर (ret)
		जाओ out;

	ret = 0;

 out:
	realtek_smi_stop(smi);
	spin_unlock_irqrestore(&smi->lock, flags);

	वापस ret;
पूर्ण

/* There is one single हाल when we need to use this accessor and that
 * is when issueing soft reset. Since the device reset as soon as we ग_लिखो
 * that bit, no ACK will come back क्रम natural reasons.
 */
पूर्णांक realtek_smi_ग_लिखो_reg_noack(काष्ठा realtek_smi *smi, u32 addr,
				u32 data)
अणु
	वापस realtek_smi_ग_लिखो_reg(smi, addr, data, false);
पूर्ण
EXPORT_SYMBOL_GPL(realtek_smi_ग_लिखो_reg_noack);

/* Regmap accessors */

अटल पूर्णांक realtek_smi_ग_लिखो(व्योम *ctx, u32 reg, u32 val)
अणु
	काष्ठा realtek_smi *smi = ctx;

	वापस realtek_smi_ग_लिखो_reg(smi, reg, val, true);
पूर्ण

अटल पूर्णांक realtek_smi_पढ़ो(व्योम *ctx, u32 reg, u32 *val)
अणु
	काष्ठा realtek_smi *smi = ctx;

	वापस realtek_smi_पढ़ो_reg(smi, reg, val);
पूर्ण

अटल स्थिर काष्ठा regmap_config realtek_smi_mdio_regmap_config = अणु
	.reg_bits = 10, /* A4..A0 R4..R0 */
	.val_bits = 16,
	.reg_stride = 1,
	/* PHY regs are at 0x8000 */
	.max_रेजिस्टर = 0xffff,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.reg_पढ़ो = realtek_smi_पढ़ो,
	.reg_ग_लिखो = realtek_smi_ग_लिखो,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक realtek_smi_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum)
अणु
	काष्ठा realtek_smi *smi = bus->priv;

	वापस smi->ops->phy_पढ़ो(smi, addr, regnum);
पूर्ण

अटल पूर्णांक realtek_smi_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum,
				  u16 val)
अणु
	काष्ठा realtek_smi *smi = bus->priv;

	वापस smi->ops->phy_ग_लिखो(smi, addr, regnum, val);
पूर्ण

पूर्णांक realtek_smi_setup_mdio(काष्ठा realtek_smi *smi)
अणु
	काष्ठा device_node *mdio_np;
	पूर्णांक ret;

	mdio_np = of_get_compatible_child(smi->dev->of_node, "realtek,smi-mdio");
	अगर (!mdio_np) अणु
		dev_err(smi->dev, "no MDIO bus node\n");
		वापस -ENODEV;
	पूर्ण

	smi->slave_mii_bus = devm_mdiobus_alloc(smi->dev);
	अगर (!smi->slave_mii_bus) अणु
		ret = -ENOMEM;
		जाओ err_put_node;
	पूर्ण
	smi->slave_mii_bus->priv = smi;
	smi->slave_mii_bus->name = "SMI slave MII";
	smi->slave_mii_bus->पढ़ो = realtek_smi_mdio_पढ़ो;
	smi->slave_mii_bus->ग_लिखो = realtek_smi_mdio_ग_लिखो;
	snम_लिखो(smi->slave_mii_bus->id, MII_BUS_ID_SIZE, "SMI-%d",
		 smi->ds->index);
	smi->slave_mii_bus->dev.of_node = mdio_np;
	smi->slave_mii_bus->parent = smi->dev;
	smi->ds->slave_mii_bus = smi->slave_mii_bus;

	ret = of_mdiobus_रेजिस्टर(smi->slave_mii_bus, mdio_np);
	अगर (ret) अणु
		dev_err(smi->dev, "unable to register MDIO bus %s\n",
			smi->slave_mii_bus->id);
		जाओ err_put_node;
	पूर्ण

	वापस 0;

err_put_node:
	of_node_put(mdio_np);

	वापस ret;
पूर्ण

अटल पूर्णांक realtek_smi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा realtek_smi_variant *var;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा realtek_smi *smi;
	काष्ठा device_node *np;
	पूर्णांक ret;

	var = of_device_get_match_data(dev);
	np = dev->of_node;

	smi = devm_kzalloc(dev, माप(*smi) + var->chip_data_sz, GFP_KERNEL);
	अगर (!smi)
		वापस -ENOMEM;
	smi->chip_data = (व्योम *)smi + माप(*smi);
	smi->map = devm_regmap_init(dev, शून्य, smi,
				    &realtek_smi_mdio_regmap_config);
	अगर (IS_ERR(smi->map)) अणु
		ret = PTR_ERR(smi->map);
		dev_err(dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Link क्रमward and backward */
	smi->dev = dev;
	smi->clk_delay = var->clk_delay;
	smi->cmd_पढ़ो = var->cmd_पढ़ो;
	smi->cmd_ग_लिखो = var->cmd_ग_लिखो;
	smi->ops = var->ops;

	dev_set_drvdata(dev, smi);
	spin_lock_init(&smi->lock);

	/* TODO: अगर घातer is software controlled, set up any regulators here */

	/* Assert then deनिश्चित RESET */
	smi->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(smi->reset)) अणु
		dev_err(dev, "failed to get RESET GPIO\n");
		वापस PTR_ERR(smi->reset);
	पूर्ण
	msleep(REALTEK_SMI_HW_STOP_DELAY);
	gpiod_set_value(smi->reset, 0);
	msleep(REALTEK_SMI_HW_START_DELAY);
	dev_info(dev, "deasserted RESET\n");

	/* Fetch MDIO pins */
	smi->mdc = devm_gpiod_get_optional(dev, "mdc", GPIOD_OUT_LOW);
	अगर (IS_ERR(smi->mdc))
		वापस PTR_ERR(smi->mdc);
	smi->mdio = devm_gpiod_get_optional(dev, "mdio", GPIOD_OUT_LOW);
	अगर (IS_ERR(smi->mdio))
		वापस PTR_ERR(smi->mdio);

	smi->leds_disabled = of_property_पढ़ो_bool(np, "realtek,disable-leds");

	ret = smi->ops->detect(smi);
	अगर (ret) अणु
		dev_err(dev, "unable to detect switch\n");
		वापस ret;
	पूर्ण

	smi->ds = devm_kzalloc(dev, माप(*smi->ds), GFP_KERNEL);
	अगर (!smi->ds)
		वापस -ENOMEM;

	smi->ds->dev = dev;
	smi->ds->num_ports = smi->num_ports;
	smi->ds->priv = smi;

	smi->ds->ops = var->ds_ops;
	ret = dsa_रेजिस्टर_चयन(smi->ds);
	अगर (ret) अणु
		dev_err(dev, "unable to register switch ret = %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक realtek_smi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा realtek_smi *smi = dev_get_drvdata(&pdev->dev);

	dsa_unरेजिस्टर_चयन(smi->ds);
	अगर (smi->slave_mii_bus)
		of_node_put(smi->slave_mii_bus->dev.of_node);
	gpiod_set_value(smi->reset, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id realtek_smi_of_match[] = अणु
	अणु
		.compatible = "realtek,rtl8366rb",
		.data = &rtl8366rb_variant,
	पूर्ण,
	अणु
		/* FIXME: add support क्रम RTL8366S and more */
		.compatible = "realtek,rtl8366s",
		.data = शून्य,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, realtek_smi_of_match);

अटल काष्ठा platक्रमm_driver realtek_smi_driver = अणु
	.driver = अणु
		.name = "realtek-smi",
		.of_match_table = of_match_ptr(realtek_smi_of_match),
	पूर्ण,
	.probe  = realtek_smi_probe,
	.हटाओ = realtek_smi_हटाओ,
पूर्ण;
module_platक्रमm_driver(realtek_smi_driver);

MODULE_LICENSE("GPL");
