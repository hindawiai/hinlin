<शैली गुरु>
/*
 * Driver क्रम (BCM4706)? GBit MAC core on BCMA bus.
 *
 * Copyright (C) 2012 Rafaध Miधecki <zajec5@gmail.com>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/brcmphy.h>
#समावेश "bgmac.h"

अटल bool bcma_mdio_रुको_value(काष्ठा bcma_device *core, u16 reg, u32 mask,
				 u32 value, पूर्णांक समयout)
अणु
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < समयout / 10; i++) अणु
		val = bcma_पढ़ो32(core, reg);
		अगर ((val & mask) == value)
			वापस true;
		udelay(10);
	पूर्ण
	dev_err(&core->dev, "Timeout waiting for reg 0x%X\n", reg);
	वापस false;
पूर्ण

/**************************************************
 * PHY ops
 **************************************************/

अटल u16 bcma_mdio_phy_पढ़ो(काष्ठा bgmac *bgmac, u8 phyaddr, u8 reg)
अणु
	काष्ठा bcma_device *core;
	u16 phy_access_addr;
	u16 phy_ctl_addr;
	u32 पंचांगp;

	BUILD_BUG_ON(BGMAC_PA_DATA_MASK != BCMA_GMAC_CMN_PA_DATA_MASK);
	BUILD_BUG_ON(BGMAC_PA_ADDR_MASK != BCMA_GMAC_CMN_PA_ADDR_MASK);
	BUILD_BUG_ON(BGMAC_PA_ADDR_SHIFT != BCMA_GMAC_CMN_PA_ADDR_SHIFT);
	BUILD_BUG_ON(BGMAC_PA_REG_MASK != BCMA_GMAC_CMN_PA_REG_MASK);
	BUILD_BUG_ON(BGMAC_PA_REG_SHIFT != BCMA_GMAC_CMN_PA_REG_SHIFT);
	BUILD_BUG_ON(BGMAC_PA_WRITE != BCMA_GMAC_CMN_PA_WRITE);
	BUILD_BUG_ON(BGMAC_PA_START != BCMA_GMAC_CMN_PA_START);
	BUILD_BUG_ON(BGMAC_PC_EPA_MASK != BCMA_GMAC_CMN_PC_EPA_MASK);
	BUILD_BUG_ON(BGMAC_PC_MCT_MASK != BCMA_GMAC_CMN_PC_MCT_MASK);
	BUILD_BUG_ON(BGMAC_PC_MCT_SHIFT != BCMA_GMAC_CMN_PC_MCT_SHIFT);
	BUILD_BUG_ON(BGMAC_PC_MTE != BCMA_GMAC_CMN_PC_MTE);

	अगर (bgmac->bcma.core->id.id == BCMA_CORE_4706_MAC_GBIT) अणु
		core = bgmac->bcma.core->bus->drv_gmac_cmn.core;
		phy_access_addr = BCMA_GMAC_CMN_PHY_ACCESS;
		phy_ctl_addr = BCMA_GMAC_CMN_PHY_CTL;
	पूर्ण अन्यथा अणु
		core = bgmac->bcma.core;
		phy_access_addr = BGMAC_PHY_ACCESS;
		phy_ctl_addr = BGMAC_PHY_CNTL;
	पूर्ण

	पंचांगp = bcma_पढ़ो32(core, phy_ctl_addr);
	पंचांगp &= ~BGMAC_PC_EPA_MASK;
	पंचांगp |= phyaddr;
	bcma_ग_लिखो32(core, phy_ctl_addr, पंचांगp);

	पंचांगp = BGMAC_PA_START;
	पंचांगp |= phyaddr << BGMAC_PA_ADDR_SHIFT;
	पंचांगp |= reg << BGMAC_PA_REG_SHIFT;
	bcma_ग_लिखो32(core, phy_access_addr, पंचांगp);

	अगर (!bcma_mdio_रुको_value(core, phy_access_addr, BGMAC_PA_START, 0,
				  1000)) अणु
		dev_err(&core->dev, "Reading PHY %d register 0x%X failed\n",
			phyaddr, reg);
		वापस 0xffff;
	पूर्ण

	वापस bcma_पढ़ो32(core, phy_access_addr) & BGMAC_PA_DATA_MASK;
पूर्ण

/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/chipphywr */
अटल पूर्णांक bcma_mdio_phy_ग_लिखो(काष्ठा bgmac *bgmac, u8 phyaddr, u8 reg,
			       u16 value)
अणु
	काष्ठा bcma_device *core;
	u16 phy_access_addr;
	u16 phy_ctl_addr;
	u32 पंचांगp;

	अगर (bgmac->bcma.core->id.id == BCMA_CORE_4706_MAC_GBIT) अणु
		core = bgmac->bcma.core->bus->drv_gmac_cmn.core;
		phy_access_addr = BCMA_GMAC_CMN_PHY_ACCESS;
		phy_ctl_addr = BCMA_GMAC_CMN_PHY_CTL;
	पूर्ण अन्यथा अणु
		core = bgmac->bcma.core;
		phy_access_addr = BGMAC_PHY_ACCESS;
		phy_ctl_addr = BGMAC_PHY_CNTL;
	पूर्ण

	पंचांगp = bcma_पढ़ो32(core, phy_ctl_addr);
	पंचांगp &= ~BGMAC_PC_EPA_MASK;
	पंचांगp |= phyaddr;
	bcma_ग_लिखो32(core, phy_ctl_addr, पंचांगp);

	bcma_ग_लिखो32(bgmac->bcma.core, BGMAC_INT_STATUS, BGMAC_IS_MDIO);
	अगर (bcma_पढ़ो32(bgmac->bcma.core, BGMAC_INT_STATUS) & BGMAC_IS_MDIO)
		dev_warn(&core->dev, "Error setting MDIO int\n");

	पंचांगp = BGMAC_PA_START;
	पंचांगp |= BGMAC_PA_WRITE;
	पंचांगp |= phyaddr << BGMAC_PA_ADDR_SHIFT;
	पंचांगp |= reg << BGMAC_PA_REG_SHIFT;
	पंचांगp |= value;
	bcma_ग_लिखो32(core, phy_access_addr, पंचांगp);

	अगर (!bcma_mdio_रुको_value(core, phy_access_addr, BGMAC_PA_START, 0,
				  1000)) अणु
		dev_err(&core->dev, "Writing to PHY %d register 0x%X failed\n",
			phyaddr, reg);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/chipphyinit */
अटल व्योम bcma_mdio_phy_init(काष्ठा bgmac *bgmac)
अणु
	काष्ठा bcma_chipinfo *ci = &bgmac->bcma.core->bus->chipinfo;
	u8 i;

	/* For some legacy hardware we करो chipset-based PHY initialization here
	 * without even detecting PHY ID. It's hacky and should be cleaned as
	 * soon as someone can test it.
	 */
	अगर (ci->id == BCMA_CHIP_ID_BCM5356) अणु
		क्रम (i = 0; i < 5; i++) अणु
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x1f, 0x008b);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x15, 0x0100);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x12, 0x2aaa);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x1f, 0x000b);
		पूर्ण
		वापस;
	पूर्ण
	अगर ((ci->id == BCMA_CHIP_ID_BCM5357 && ci->pkg != 10) ||
	    (ci->id == BCMA_CHIP_ID_BCM4749 && ci->pkg != 10) ||
	    (ci->id == BCMA_CHIP_ID_BCM53572 && ci->pkg != 9)) अणु
		काष्ठा bcma_drv_cc *cc = &bgmac->bcma.core->bus->drv_cc;

		bcma_chipco_chipctl_maskset(cc, 2, ~0xc0000000, 0);
		bcma_chipco_chipctl_maskset(cc, 4, ~0x80000000, 0);
		क्रम (i = 0; i < 5; i++) अणु
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x16, 0x5284);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x1f, 0x000b);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x17, 0x0010);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x16, 0x5296);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x17, 0x1073);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x17, 0x9073);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x16, 0x52b6);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x17, 0x9273);
			bcma_mdio_phy_ग_लिखो(bgmac, i, 0x1f, 0x000b);
		पूर्ण
		वापस;
	पूर्ण

	/* For all other hw करो initialization using PHY subप्रणाली. */
	अगर (bgmac->net_dev && bgmac->net_dev->phydev)
		phy_init_hw(bgmac->net_dev->phydev);
पूर्ण

/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/chipphyreset */
अटल पूर्णांक bcma_mdio_phy_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा bgmac *bgmac = bus->priv;
	u8 phyaddr = bgmac->phyaddr;

	अगर (phyaddr == BGMAC_PHY_NOREGS)
		वापस 0;

	bcma_mdio_phy_ग_लिखो(bgmac, phyaddr, MII_BMCR, BMCR_RESET);
	udelay(100);
	अगर (bcma_mdio_phy_पढ़ो(bgmac, phyaddr, MII_BMCR) & BMCR_RESET)
		dev_err(bgmac->dev, "PHY reset failed\n");
	bcma_mdio_phy_init(bgmac);

	वापस 0;
पूर्ण

/**************************************************
 * MII
 **************************************************/

अटल पूर्णांक bcma_mdio_mii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	वापस bcma_mdio_phy_पढ़ो(bus->priv, mii_id, regnum);
पूर्ण

अटल पूर्णांक bcma_mdio_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum,
			       u16 value)
अणु
	वापस bcma_mdio_phy_ग_लिखो(bus->priv, mii_id, regnum, value);
पूर्ण

काष्ठा mii_bus *bcma_mdio_mii_रेजिस्टर(काष्ठा bgmac *bgmac)
अणु
	काष्ठा bcma_device *core = bgmac->bcma.core;
	काष्ठा mii_bus *mii_bus;
	पूर्णांक err;

	mii_bus = mdiobus_alloc();
	अगर (!mii_bus) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	mii_bus->name = "bcma_mdio mii bus";
	प्र_लिखो(mii_bus->id, "%s-%d-%d", "bcma_mdio", core->bus->num,
		core->core_unit);
	mii_bus->priv = bgmac;
	mii_bus->पढ़ो = bcma_mdio_mii_पढ़ो;
	mii_bus->ग_लिखो = bcma_mdio_mii_ग_लिखो;
	mii_bus->reset = bcma_mdio_phy_reset;
	mii_bus->parent = &core->dev;
	mii_bus->phy_mask = ~(1 << bgmac->phyaddr);

	err = mdiobus_रेजिस्टर(mii_bus);
	अगर (err) अणु
		dev_err(&core->dev, "Registration of mii bus failed\n");
		जाओ err_मुक्त_bus;
	पूर्ण

	वापस mii_bus;

err_मुक्त_bus:
	mdiobus_मुक्त(mii_bus);
err:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_mdio_mii_रेजिस्टर);

व्योम bcma_mdio_mii_unरेजिस्टर(काष्ठा mii_bus *mii_bus)
अणु
	अगर (!mii_bus)
		वापस;

	mdiobus_unरेजिस्टर(mii_bus);
	mdiobus_मुक्त(mii_bus);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_mdio_mii_unरेजिस्टर);

MODULE_AUTHOR("Rafaध Miधecki");
MODULE_LICENSE("GPL");
