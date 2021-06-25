<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Author: Olof Johansson, PA Semi
 *
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 *
 * Based on drivers/net/fs_enet/mii-bitbang.c.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/phy.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>

#घोषणा DELAY 1

अटल व्योम __iomem *gpio_regs;

काष्ठा gpio_priv अणु
	पूर्णांक mdc_pin;
	पूर्णांक mdio_pin;
पूर्ण;

#घोषणा MDC_PIN(bus)	(((काष्ठा gpio_priv *)bus->priv)->mdc_pin)
#घोषणा MDIO_PIN(bus)	(((काष्ठा gpio_priv *)bus->priv)->mdio_pin)

अटल अंतरभूत व्योम mdio_lo(काष्ठा mii_bus *bus)
अणु
	out_le32(gpio_regs+0x10, 1 << MDIO_PIN(bus));
पूर्ण

अटल अंतरभूत व्योम mdio_hi(काष्ठा mii_bus *bus)
अणु
	out_le32(gpio_regs, 1 << MDIO_PIN(bus));
पूर्ण

अटल अंतरभूत व्योम mdc_lo(काष्ठा mii_bus *bus)
अणु
	out_le32(gpio_regs+0x10, 1 << MDC_PIN(bus));
पूर्ण

अटल अंतरभूत व्योम mdc_hi(काष्ठा mii_bus *bus)
अणु
	out_le32(gpio_regs, 1 << MDC_PIN(bus));
पूर्ण

अटल अंतरभूत व्योम mdio_active(काष्ठा mii_bus *bus)
अणु
	out_le32(gpio_regs+0x20, (1 << MDC_PIN(bus)) | (1 << MDIO_PIN(bus)));
पूर्ण

अटल अंतरभूत व्योम mdio_tristate(काष्ठा mii_bus *bus)
अणु
	out_le32(gpio_regs+0x30, (1 << MDIO_PIN(bus)));
पूर्ण

अटल अंतरभूत पूर्णांक mdio_पढ़ो(काष्ठा mii_bus *bus)
अणु
	वापस !!(in_le32(gpio_regs+0x40) & (1 << MDIO_PIN(bus)));
पूर्ण

अटल व्योम घड़ी_out(काष्ठा mii_bus *bus, पूर्णांक bit)
अणु
	अगर (bit)
		mdio_hi(bus);
	अन्यथा
		mdio_lo(bus);
	udelay(DELAY);
	mdc_hi(bus);
	udelay(DELAY);
	mdc_lo(bus);
पूर्ण

/* Utility to send the preamble, address, and रेजिस्टर (common to पढ़ो and ग_लिखो). */
अटल व्योम bitbang_pre(काष्ठा mii_bus *bus, पूर्णांक पढ़ो, u8 addr, u8 reg)
अणु
	पूर्णांक i;

	/* CFE uses a really दीर्घ preamble (40 bits). We'll करो the same. */
	mdio_active(bus);
	क्रम (i = 0; i < 40; i++) अणु
		घड़ी_out(bus, 1);
	पूर्ण

	/* send the start bit (01) and the पढ़ो opcode (10) or ग_लिखो (10) */
	घड़ी_out(bus, 0);
	घड़ी_out(bus, 1);

	घड़ी_out(bus, पढ़ो);
	घड़ी_out(bus, !पढ़ो);

	/* send the PHY address */
	क्रम (i = 0; i < 5; i++) अणु
		घड़ी_out(bus, (addr & 0x10) != 0);
		addr <<= 1;
	पूर्ण

	/* send the रेजिस्टर address */
	क्रम (i = 0; i < 5; i++) अणु
		घड़ी_out(bus, (reg & 0x10) != 0);
		reg <<= 1;
	पूर्ण
पूर्ण

अटल पूर्णांक gpio_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक location)
अणु
	u16 rdreg;
	पूर्णांक ret, i;
	u8 addr = phy_id & 0xff;
	u8 reg = location & 0xff;

	bitbang_pre(bus, 1, addr, reg);

	/* tri-state our MDIO I/O pin so we can पढ़ो */
	mdio_tristate(bus);
	udelay(DELAY);
	mdc_hi(bus);
	udelay(DELAY);
	mdc_lo(bus);

	/* पढ़ो 16 bits of रेजिस्टर data, MSB first */
	rdreg = 0;
	क्रम (i = 0; i < 16; i++) अणु
		mdc_lo(bus);
		udelay(DELAY);
		mdc_hi(bus);
		udelay(DELAY);
		mdc_lo(bus);
		udelay(DELAY);
		rdreg <<= 1;
		rdreg |= mdio_पढ़ो(bus);
	पूर्ण

	mdc_hi(bus);
	udelay(DELAY);
	mdc_lo(bus);
	udelay(DELAY);

	ret = rdreg;

	वापस ret;
पूर्ण

अटल पूर्णांक gpio_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक location, u16 val)
अणु
	पूर्णांक i;

	u8 addr = phy_id & 0xff;
	u8 reg = location & 0xff;
	u16 value = val & 0xffff;

	bitbang_pre(bus, 0, addr, reg);

	/* send the turnaround (10) */
	mdc_lo(bus);
	mdio_hi(bus);
	udelay(DELAY);
	mdc_hi(bus);
	udelay(DELAY);
	mdc_lo(bus);
	mdio_lo(bus);
	udelay(DELAY);
	mdc_hi(bus);
	udelay(DELAY);

	/* ग_लिखो 16 bits of रेजिस्टर data, MSB first */
	क्रम (i = 0; i < 16; i++) अणु
		mdc_lo(bus);
		अगर (value & 0x8000)
			mdio_hi(bus);
		अन्यथा
			mdio_lo(bus);
		udelay(DELAY);
		mdc_hi(bus);
		udelay(DELAY);
		value <<= 1;
	पूर्ण

	/*
	 * Tri-state the MDIO line.
	 */
	mdio_tristate(bus);
	mdc_lo(bus);
	udelay(DELAY);
	mdc_hi(bus);
	udelay(DELAY);
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_mdio_reset(काष्ठा mii_bus *bus)
अणु
	/*nothing here - dunno how to reset it*/
	वापस 0;
पूर्ण


अटल पूर्णांक gpio_mdio_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा mii_bus *new_bus;
	काष्ठा gpio_priv *priv;
	स्थिर अचिन्हित पूर्णांक *prop;
	पूर्णांक err;

	err = -ENOMEM;
	priv = kzalloc(माप(काष्ठा gpio_priv), GFP_KERNEL);
	अगर (!priv)
		जाओ out;

	new_bus = mdiobus_alloc();

	अगर (!new_bus)
		जाओ out_मुक्त_priv;

	new_bus->name = "pasemi gpio mdio bus";
	new_bus->पढ़ो = &gpio_mdio_पढ़ो;
	new_bus->ग_लिखो = &gpio_mdio_ग_लिखो;
	new_bus->reset = &gpio_mdio_reset;

	prop = of_get_property(np, "reg", शून्य);
	snम_लिखो(new_bus->id, MII_BUS_ID_SIZE, "%x", *prop);
	new_bus->priv = priv;

	prop = of_get_property(np, "mdc-pin", शून्य);
	priv->mdc_pin = *prop;

	prop = of_get_property(np, "mdio-pin", शून्य);
	priv->mdio_pin = *prop;

	new_bus->parent = dev;
	dev_set_drvdata(dev, new_bus);

	err = of_mdiobus_रेजिस्टर(new_bus, np);

	अगर (err != 0) अणु
		pr_err("%s: Cannot register as MDIO bus, err %d\n",
				new_bus->name, err);
		जाओ out_मुक्त_irq;
	पूर्ण

	वापस 0;

out_मुक्त_irq:
	kमुक्त(new_bus);
out_मुक्त_priv:
	kमुक्त(priv);
out:
	वापस err;
पूर्ण


अटल पूर्णांक gpio_mdio_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mii_bus *bus = dev_get_drvdata(&dev->dev);

	mdiobus_unरेजिस्टर(bus);

	dev_set_drvdata(&dev->dev, शून्य);

	kमुक्त(bus->priv);
	bus->priv = शून्य;
	mdiobus_मुक्त(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gpio_mdio_match[] =
अणु
	अणु
		.compatible      = "gpio-mdio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_mdio_match);

अटल काष्ठा platक्रमm_driver gpio_mdio_driver =
अणु
	.probe		= gpio_mdio_probe,
	.हटाओ		= gpio_mdio_हटाओ,
	.driver = अणु
		.name = "gpio-mdio-bitbang",
		.of_match_table = gpio_mdio_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक gpio_mdio_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "1682m-gpio");
	अगर (!np)
		np = of_find_compatible_node(शून्य, शून्य,
					     "pasemi,pwrficient-gpio");
	अगर (!np)
		वापस -ENODEV;
	gpio_regs = of_iomap(np, 0);
	of_node_put(np);

	अगर (!gpio_regs)
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&gpio_mdio_driver);
पूर्ण
module_init(gpio_mdio_init);

अटल व्योम gpio_mdio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gpio_mdio_driver);
	अगर (gpio_regs)
		iounmap(gpio_regs);
पूर्ण
module_निकास(gpio_mdio_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Olof Johansson <olof@lixom.net>");
MODULE_DESCRIPTION("Driver for MDIO over GPIO on PA Semi PWRficient-based boards");
