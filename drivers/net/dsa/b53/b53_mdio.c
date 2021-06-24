<शैली गुरु>
/*
 * B53 रेजिस्टर access through MII रेजिस्टरs
 *
 * Copyright (C) 2011-2013 Jonas Gorski <jogo@खोलोwrt.org>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/phy.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/dsa.h>

#समावेश "b53_priv.h"

/* MII रेजिस्टरs */
#घोषणा REG_MII_PAGE    0x10    /* MII Page रेजिस्टर */
#घोषणा REG_MII_ADDR    0x11    /* MII Address रेजिस्टर */
#घोषणा REG_MII_DATA0   0x18    /* MII Data रेजिस्टर 0 */
#घोषणा REG_MII_DATA1   0x19    /* MII Data रेजिस्टर 1 */
#घोषणा REG_MII_DATA2   0x1a    /* MII Data रेजिस्टर 2 */
#घोषणा REG_MII_DATA3   0x1b    /* MII Data रेजिस्टर 3 */

#घोषणा REG_MII_PAGE_ENABLE     BIT(0)
#घोषणा REG_MII_ADDR_WRITE      BIT(0)
#घोषणा REG_MII_ADDR_READ       BIT(1)

अटल पूर्णांक b53_mdio_op(काष्ठा b53_device *dev, u8 page, u8 reg, u16 op)
अणु
	पूर्णांक i;
	u16 v;
	पूर्णांक ret;
	काष्ठा mii_bus *bus = dev->priv;

	अगर (dev->current_page != page) अणु
		/* set page number */
		v = (page << 8) | REG_MII_PAGE_ENABLE;
		ret = mdiobus_ग_लिखो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
					   REG_MII_PAGE, v);
		अगर (ret)
			वापस ret;
		dev->current_page = page;
	पूर्ण

	/* set रेजिस्टर address */
	v = (reg << 8) | op;
	ret = mdiobus_ग_लिखो_nested(bus, BRCM_PSEUDO_PHY_ADDR, REG_MII_ADDR, v);
	अगर (ret)
		वापस ret;

	/* check अगर operation completed */
	क्रम (i = 0; i < 5; ++i) अणु
		v = mdiobus_पढ़ो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
					REG_MII_ADDR);
		अगर (!(v & (REG_MII_ADDR_WRITE | REG_MII_ADDR_READ)))
			अवरोध;
		usleep_range(10, 100);
	पूर्ण

	अगर (WARN_ON(i == 5))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mdio_पढ़ो8(काष्ठा b53_device *dev, u8 page, u8 reg, u8 *val)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	पूर्णांक ret;

	ret = b53_mdio_op(dev, page, reg, REG_MII_ADDR_READ);
	अगर (ret)
		वापस ret;

	*val = mdiobus_पढ़ो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
				   REG_MII_DATA0) & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mdio_पढ़ो16(काष्ठा b53_device *dev, u8 page, u8 reg, u16 *val)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	पूर्णांक ret;

	ret = b53_mdio_op(dev, page, reg, REG_MII_ADDR_READ);
	अगर (ret)
		वापस ret;

	*val = mdiobus_पढ़ो_nested(bus, BRCM_PSEUDO_PHY_ADDR, REG_MII_DATA0);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mdio_पढ़ो32(काष्ठा b53_device *dev, u8 page, u8 reg, u32 *val)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	पूर्णांक ret;

	ret = b53_mdio_op(dev, page, reg, REG_MII_ADDR_READ);
	अगर (ret)
		वापस ret;

	*val = mdiobus_पढ़ो_nested(bus, BRCM_PSEUDO_PHY_ADDR, REG_MII_DATA0);
	*val |= mdiobus_पढ़ो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
				    REG_MII_DATA1) << 16;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mdio_पढ़ो48(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *val)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	u64 temp = 0;
	पूर्णांक i;
	पूर्णांक ret;

	ret = b53_mdio_op(dev, page, reg, REG_MII_ADDR_READ);
	अगर (ret)
		वापस ret;

	क्रम (i = 2; i >= 0; i--) अणु
		temp <<= 16;
		temp |= mdiobus_पढ़ो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
				     REG_MII_DATA0 + i);
	पूर्ण

	*val = temp;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mdio_पढ़ो64(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *val)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	u64 temp = 0;
	पूर्णांक i;
	पूर्णांक ret;

	ret = b53_mdio_op(dev, page, reg, REG_MII_ADDR_READ);
	अगर (ret)
		वापस ret;

	क्रम (i = 3; i >= 0; i--) अणु
		temp <<= 16;
		temp |= mdiobus_पढ़ो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
					    REG_MII_DATA0 + i);
	पूर्ण

	*val = temp;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mdio_ग_लिखो8(काष्ठा b53_device *dev, u8 page, u8 reg, u8 value)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	पूर्णांक ret;

	ret = mdiobus_ग_लिखो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
				   REG_MII_DATA0, value);
	अगर (ret)
		वापस ret;

	वापस b53_mdio_op(dev, page, reg, REG_MII_ADDR_WRITE);
पूर्ण

अटल पूर्णांक b53_mdio_ग_लिखो16(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u16 value)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	पूर्णांक ret;

	ret = mdiobus_ग_लिखो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
				   REG_MII_DATA0, value);
	अगर (ret)
		वापस ret;

	वापस b53_mdio_op(dev, page, reg, REG_MII_ADDR_WRITE);
पूर्ण

अटल पूर्णांक b53_mdio_ग_लिखो32(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u32 value)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	अचिन्हित पूर्णांक i;
	u32 temp = value;

	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक ret = mdiobus_ग_लिखो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
					       REG_MII_DATA0 + i,
					       temp & 0xffff);
		अगर (ret)
			वापस ret;
		temp >>= 16;
	पूर्ण

	वापस b53_mdio_op(dev, page, reg, REG_MII_ADDR_WRITE);
पूर्ण

अटल पूर्णांक b53_mdio_ग_लिखो48(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u64 value)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	अचिन्हित पूर्णांक i;
	u64 temp = value;

	क्रम (i = 0; i < 3; i++) अणु
		पूर्णांक ret = mdiobus_ग_लिखो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
					       REG_MII_DATA0 + i,
					       temp & 0xffff);
		अगर (ret)
			वापस ret;
		temp >>= 16;
	पूर्ण

	वापस b53_mdio_op(dev, page, reg, REG_MII_ADDR_WRITE);
पूर्ण

अटल पूर्णांक b53_mdio_ग_लिखो64(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u64 value)
अणु
	काष्ठा mii_bus *bus = dev->priv;
	अचिन्हित पूर्णांक i;
	u64 temp = value;

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक ret = mdiobus_ग_लिखो_nested(bus, BRCM_PSEUDO_PHY_ADDR,
					       REG_MII_DATA0 + i,
					       temp & 0xffff);
		अगर (ret)
			वापस ret;
		temp >>= 16;
	पूर्ण

	वापस b53_mdio_op(dev, page, reg, REG_MII_ADDR_WRITE);
पूर्ण

अटल पूर्णांक b53_mdio_phy_पढ़ो16(काष्ठा b53_device *dev, पूर्णांक addr, पूर्णांक reg,
			       u16 *value)
अणु
	काष्ठा mii_bus *bus = dev->priv;

	*value = mdiobus_पढ़ो_nested(bus, addr, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mdio_phy_ग_लिखो16(काष्ठा b53_device *dev, पूर्णांक addr, पूर्णांक reg,
				u16 value)
अणु
	काष्ठा mii_bus *bus = dev->bus;

	वापस mdiobus_ग_लिखो_nested(bus, addr, reg, value);
पूर्ण

अटल स्थिर काष्ठा b53_io_ops b53_mdio_ops = अणु
	.पढ़ो8 = b53_mdio_पढ़ो8,
	.पढ़ो16 = b53_mdio_पढ़ो16,
	.पढ़ो32 = b53_mdio_पढ़ो32,
	.पढ़ो48 = b53_mdio_पढ़ो48,
	.पढ़ो64 = b53_mdio_पढ़ो64,
	.ग_लिखो8 = b53_mdio_ग_लिखो8,
	.ग_लिखो16 = b53_mdio_ग_लिखो16,
	.ग_लिखो32 = b53_mdio_ग_लिखो32,
	.ग_लिखो48 = b53_mdio_ग_लिखो48,
	.ग_लिखो64 = b53_mdio_ग_लिखो64,
	.phy_पढ़ो16 = b53_mdio_phy_पढ़ो16,
	.phy_ग_लिखो16 = b53_mdio_phy_ग_लिखो16,
पूर्ण;

#घोषणा B53_BRCM_OUI_1	0x0143bc00
#घोषणा B53_BRCM_OUI_2	0x03625c00
#घोषणा B53_BRCM_OUI_3	0x00406000
#घोषणा B53_BRCM_OUI_4	0x01410c00

अटल पूर्णांक b53_mdio_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा b53_device *dev;
	u32 phy_id;
	पूर्णांक ret;

	/* allow the generic PHY driver to take over the non-management MDIO
	 * addresses
	 */
	अगर (mdiodev->addr != BRCM_PSEUDO_PHY_ADDR && mdiodev->addr != 0) अणु
		dev_err(&mdiodev->dev, "leaving address %d to PHY\n",
			mdiodev->addr);
		वापस -ENODEV;
	पूर्ण

	/* पढ़ो the first port's id */
	phy_id = mdiobus_पढ़ो(mdiodev->bus, 0, 2) << 16;
	phy_id |= mdiobus_पढ़ो(mdiodev->bus, 0, 3);

	/* BCM5325, BCM539x (OUI_1)
	 * BCM53125, BCM53128 (OUI_2)
	 * BCM5365 (OUI_3)
	 */
	अगर ((phy_id & 0xfffffc00) != B53_BRCM_OUI_1 &&
	    (phy_id & 0xfffffc00) != B53_BRCM_OUI_2 &&
	    (phy_id & 0xfffffc00) != B53_BRCM_OUI_3 &&
	    (phy_id & 0xfffffc00) != B53_BRCM_OUI_4) अणु
		dev_err(&mdiodev->dev, "Unsupported device: 0x%08x\n", phy_id);
		वापस -ENODEV;
	पूर्ण

	/* First probe will come from SWITCH_MDIO controller on the 7445D0
	 * चयन, which will conflict with the 7445 पूर्णांकegrated चयन
	 * pseuकरो-phy (we end-up programming both). In that हाल, we वापस
	 * -EPROBE_DEFER क्रम the first समय we get here, and रुको until we come
	 * back with the slave MDIO bus which has the correct indirection
	 * layer setup
	 */
	अगर (of_machine_is_compatible("brcm,bcm7445d0") &&
	    म_भेद(mdiodev->bus->name, "sf2 slave mii"))
		वापस -EPROBE_DEFER;

	dev = b53_चयन_alloc(&mdiodev->dev, &b53_mdio_ops, mdiodev->bus);
	अगर (!dev)
		वापस -ENOMEM;

	/* we करोn't use page 0xff, so क्रमce a page set */
	dev->current_page = 0xff;
	dev->bus = mdiodev->bus;

	dev_set_drvdata(&mdiodev->dev, dev);

	ret = b53_चयन_रेजिस्टर(dev);
	अगर (ret) अणु
		dev_err(&mdiodev->dev, "failed to register switch: %i\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम b53_mdio_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा b53_device *dev = dev_get_drvdata(&mdiodev->dev);
	काष्ठा dsa_चयन *ds = dev->ds;

	dsa_unरेजिस्टर_चयन(ds);
पूर्ण

अटल स्थिर काष्ठा of_device_id b53_of_match[] = अणु
	अणु .compatible = "brcm,bcm5325" पूर्ण,
	अणु .compatible = "brcm,bcm53115" पूर्ण,
	अणु .compatible = "brcm,bcm53125" पूर्ण,
	अणु .compatible = "brcm,bcm53128" पूर्ण,
	अणु .compatible = "brcm,bcm5365" पूर्ण,
	अणु .compatible = "brcm,bcm5389" पूर्ण,
	अणु .compatible = "brcm,bcm5395" पूर्ण,
	अणु .compatible = "brcm,bcm5397" पूर्ण,
	अणु .compatible = "brcm,bcm5398" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, b53_of_match);

अटल काष्ठा mdio_driver b53_mdio_driver = अणु
	.probe	= b53_mdio_probe,
	.हटाओ	= b53_mdio_हटाओ,
	.mdiodrv.driver = अणु
		.name = "bcm53xx",
		.of_match_table = b53_of_match,
	पूर्ण,
पूर्ण;
mdio_module_driver(b53_mdio_driver);

MODULE_DESCRIPTION("B53 MDIO access driver");
MODULE_LICENSE("Dual BSD/GPL");
