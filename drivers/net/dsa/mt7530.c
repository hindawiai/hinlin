<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mediatek MT7530 DSA Switch driver
 * Copyright (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phylink.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <net/dsa.h>

#समावेश "mt7530.h"

/* String, offset, and रेजिस्टर size in bytes अगर dअगरferent from 4 bytes */
अटल स्थिर काष्ठा mt7530_mib_desc mt7530_mib[] = अणु
	MIB_DESC(1, 0x00, "TxDrop"),
	MIB_DESC(1, 0x04, "TxCrcErr"),
	MIB_DESC(1, 0x08, "TxUnicast"),
	MIB_DESC(1, 0x0c, "TxMulticast"),
	MIB_DESC(1, 0x10, "TxBroadcast"),
	MIB_DESC(1, 0x14, "TxCollision"),
	MIB_DESC(1, 0x18, "TxSingleCollision"),
	MIB_DESC(1, 0x1c, "TxMultipleCollision"),
	MIB_DESC(1, 0x20, "TxDeferred"),
	MIB_DESC(1, 0x24, "TxLateCollision"),
	MIB_DESC(1, 0x28, "TxExcessiveCollistion"),
	MIB_DESC(1, 0x2c, "TxPause"),
	MIB_DESC(1, 0x30, "TxPktSz64"),
	MIB_DESC(1, 0x34, "TxPktSz65To127"),
	MIB_DESC(1, 0x38, "TxPktSz128To255"),
	MIB_DESC(1, 0x3c, "TxPktSz256To511"),
	MIB_DESC(1, 0x40, "TxPktSz512To1023"),
	MIB_DESC(1, 0x44, "Tx1024ToMax"),
	MIB_DESC(2, 0x48, "TxBytes"),
	MIB_DESC(1, 0x60, "RxDrop"),
	MIB_DESC(1, 0x64, "RxFiltering"),
	MIB_DESC(1, 0x6c, "RxMulticast"),
	MIB_DESC(1, 0x70, "RxBroadcast"),
	MIB_DESC(1, 0x74, "RxAlignErr"),
	MIB_DESC(1, 0x78, "RxCrcErr"),
	MIB_DESC(1, 0x7c, "RxUnderSizeErr"),
	MIB_DESC(1, 0x80, "RxFragErr"),
	MIB_DESC(1, 0x84, "RxOverSzErr"),
	MIB_DESC(1, 0x88, "RxJabberErr"),
	MIB_DESC(1, 0x8c, "RxPause"),
	MIB_DESC(1, 0x90, "RxPktSz64"),
	MIB_DESC(1, 0x94, "RxPktSz65To127"),
	MIB_DESC(1, 0x98, "RxPktSz128To255"),
	MIB_DESC(1, 0x9c, "RxPktSz256To511"),
	MIB_DESC(1, 0xa0, "RxPktSz512To1023"),
	MIB_DESC(1, 0xa4, "RxPktSz1024ToMax"),
	MIB_DESC(2, 0xa8, "RxBytes"),
	MIB_DESC(1, 0xb0, "RxCtrlDrop"),
	MIB_DESC(1, 0xb4, "RxIngressDrop"),
	MIB_DESC(1, 0xb8, "RxArlDrop"),
पूर्ण;

/* Since phy_device has not yet been created and
 * phy_अणुपढ़ो,ग_लिखोपूर्ण_mmd_indirect is not available, we provide our own
 * core_अणुपढ़ो,ग_लिखोपूर्ण_mmd_indirect with core_अणुclear,ग_लिखो,setपूर्ण wrappers
 * to complete this function.
 */
अटल पूर्णांक
core_पढ़ो_mmd_indirect(काष्ठा mt7530_priv *priv, पूर्णांक prtad, पूर्णांक devad)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	पूर्णांक value, ret;

	/* Write the desired MMD Devad */
	ret = bus->ग_लिखो(bus, 0, MII_MMD_CTRL, devad);
	अगर (ret < 0)
		जाओ err;

	/* Write the desired MMD रेजिस्टर address */
	ret = bus->ग_लिखो(bus, 0, MII_MMD_DATA, prtad);
	अगर (ret < 0)
		जाओ err;

	/* Select the Function : DATA with no post increment */
	ret = bus->ग_लिखो(bus, 0, MII_MMD_CTRL, (devad | MII_MMD_CTRL_NOINCR));
	अगर (ret < 0)
		जाओ err;

	/* Read the content of the MMD's selected रेजिस्टर */
	value = bus->पढ़ो(bus, 0, MII_MMD_DATA);

	वापस value;
err:
	dev_err(&bus->dev,  "failed to read mmd register\n");

	वापस ret;
पूर्ण

अटल पूर्णांक
core_ग_लिखो_mmd_indirect(काष्ठा mt7530_priv *priv, पूर्णांक prtad,
			पूर्णांक devad, u32 data)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	पूर्णांक ret;

	/* Write the desired MMD Devad */
	ret = bus->ग_लिखो(bus, 0, MII_MMD_CTRL, devad);
	अगर (ret < 0)
		जाओ err;

	/* Write the desired MMD रेजिस्टर address */
	ret = bus->ग_लिखो(bus, 0, MII_MMD_DATA, prtad);
	अगर (ret < 0)
		जाओ err;

	/* Select the Function : DATA with no post increment */
	ret = bus->ग_लिखो(bus, 0, MII_MMD_CTRL, (devad | MII_MMD_CTRL_NOINCR));
	अगर (ret < 0)
		जाओ err;

	/* Write the data पूर्णांकo MMD's selected रेजिस्टर */
	ret = bus->ग_लिखो(bus, 0, MII_MMD_DATA, data);
err:
	अगर (ret < 0)
		dev_err(&bus->dev,
			"failed to write mmd register\n");
	वापस ret;
पूर्ण

अटल व्योम
core_ग_लिखो(काष्ठा mt7530_priv *priv, u32 reg, u32 val)
अणु
	काष्ठा mii_bus *bus = priv->bus;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	core_ग_लिखो_mmd_indirect(priv, reg, MDIO_MMD_VEND2, val);

	mutex_unlock(&bus->mdio_lock);
पूर्ण

अटल व्योम
core_rmw(काष्ठा mt7530_priv *priv, u32 reg, u32 mask, u32 set)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	u32 val;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	val = core_पढ़ो_mmd_indirect(priv, reg, MDIO_MMD_VEND2);
	val &= ~mask;
	val |= set;
	core_ग_लिखो_mmd_indirect(priv, reg, MDIO_MMD_VEND2, val);

	mutex_unlock(&bus->mdio_lock);
पूर्ण

अटल व्योम
core_set(काष्ठा mt7530_priv *priv, u32 reg, u32 val)
अणु
	core_rmw(priv, reg, 0, val);
पूर्ण

अटल व्योम
core_clear(काष्ठा mt7530_priv *priv, u32 reg, u32 val)
अणु
	core_rmw(priv, reg, val, 0);
पूर्ण

अटल पूर्णांक
mt7530_mii_ग_लिखो(काष्ठा mt7530_priv *priv, u32 reg, u32 val)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	u16 page, r, lo, hi;
	पूर्णांक ret;

	page = (reg >> 6) & 0x3ff;
	r  = (reg >> 2) & 0xf;
	lo = val & 0xffff;
	hi = val >> 16;

	/* MT7530 uses 31 as the pseuकरो port */
	ret = bus->ग_लिखो(bus, 0x1f, 0x1f, page);
	अगर (ret < 0)
		जाओ err;

	ret = bus->ग_लिखो(bus, 0x1f, r,  lo);
	अगर (ret < 0)
		जाओ err;

	ret = bus->ग_लिखो(bus, 0x1f, 0x10, hi);
err:
	अगर (ret < 0)
		dev_err(&bus->dev,
			"failed to write mt7530 register\n");
	वापस ret;
पूर्ण

अटल u32
mt7530_mii_पढ़ो(काष्ठा mt7530_priv *priv, u32 reg)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	u16 page, r, lo, hi;
	पूर्णांक ret;

	page = (reg >> 6) & 0x3ff;
	r = (reg >> 2) & 0xf;

	/* MT7530 uses 31 as the pseuकरो port */
	ret = bus->ग_लिखो(bus, 0x1f, 0x1f, page);
	अगर (ret < 0) अणु
		dev_err(&bus->dev,
			"failed to read mt7530 register\n");
		वापस ret;
	पूर्ण

	lo = bus->पढ़ो(bus, 0x1f, r);
	hi = bus->पढ़ो(bus, 0x1f, 0x10);

	वापस (hi << 16) | (lo & 0xffff);
पूर्ण

अटल व्योम
mt7530_ग_लिखो(काष्ठा mt7530_priv *priv, u32 reg, u32 val)
अणु
	काष्ठा mii_bus *bus = priv->bus;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	mt7530_mii_ग_लिखो(priv, reg, val);

	mutex_unlock(&bus->mdio_lock);
पूर्ण

अटल u32
_mt7530_unlocked_पढ़ो(काष्ठा mt7530_dummy_poll *p)
अणु
	वापस mt7530_mii_पढ़ो(p->priv, p->reg);
पूर्ण

अटल u32
_mt7530_पढ़ो(काष्ठा mt7530_dummy_poll *p)
अणु
	काष्ठा mii_bus		*bus = p->priv->bus;
	u32 val;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	val = mt7530_mii_पढ़ो(p->priv, p->reg);

	mutex_unlock(&bus->mdio_lock);

	वापस val;
पूर्ण

अटल u32
mt7530_पढ़ो(काष्ठा mt7530_priv *priv, u32 reg)
अणु
	काष्ठा mt7530_dummy_poll p;

	INIT_MT7530_DUMMY_POLL(&p, priv, reg);
	वापस _mt7530_पढ़ो(&p);
पूर्ण

अटल व्योम
mt7530_rmw(काष्ठा mt7530_priv *priv, u32 reg,
	   u32 mask, u32 set)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	u32 val;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	val = mt7530_mii_पढ़ो(priv, reg);
	val &= ~mask;
	val |= set;
	mt7530_mii_ग_लिखो(priv, reg, val);

	mutex_unlock(&bus->mdio_lock);
पूर्ण

अटल व्योम
mt7530_set(काष्ठा mt7530_priv *priv, u32 reg, u32 val)
अणु
	mt7530_rmw(priv, reg, 0, val);
पूर्ण

अटल व्योम
mt7530_clear(काष्ठा mt7530_priv *priv, u32 reg, u32 val)
अणु
	mt7530_rmw(priv, reg, val, 0);
पूर्ण

अटल पूर्णांक
mt7530_fdb_cmd(काष्ठा mt7530_priv *priv, क्रमागत mt7530_fdb_cmd cmd, u32 *rsp)
अणु
	u32 val;
	पूर्णांक ret;
	काष्ठा mt7530_dummy_poll p;

	/* Set the command operating upon the MAC address entries */
	val = ATC_BUSY | ATC_MAT(0) | cmd;
	mt7530_ग_लिखो(priv, MT7530_ATC, val);

	INIT_MT7530_DUMMY_POLL(&p, priv, MT7530_ATC);
	ret = पढ़ोx_poll_समयout(_mt7530_पढ़ो, &p, val,
				 !(val & ATC_BUSY), 20, 20000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "reset timeout\n");
		वापस ret;
	पूर्ण

	/* Additional sanity क्रम पढ़ो command अगर the specअगरied
	 * entry is invalid
	 */
	val = mt7530_पढ़ो(priv, MT7530_ATC);
	अगर ((cmd == MT7530_FDB_READ) && (val & ATC_INVALID))
		वापस -EINVAL;

	अगर (rsp)
		*rsp = val;

	वापस 0;
पूर्ण

अटल व्योम
mt7530_fdb_पढ़ो(काष्ठा mt7530_priv *priv, काष्ठा mt7530_fdb *fdb)
अणु
	u32 reg[3];
	पूर्णांक i;

	/* Read from ARL table पूर्णांकo an array */
	क्रम (i = 0; i < 3; i++) अणु
		reg[i] = mt7530_पढ़ो(priv, MT7530_TSRA1 + (i * 4));

		dev_dbg(priv->dev, "%s(%d) reg[%d]=0x%x\n",
			__func__, __LINE__, i, reg[i]);
	पूर्ण

	fdb->vid = (reg[1] >> CVID) & CVID_MASK;
	fdb->aging = (reg[2] >> AGE_TIMER) & AGE_TIMER_MASK;
	fdb->port_mask = (reg[2] >> PORT_MAP) & PORT_MAP_MASK;
	fdb->mac[0] = (reg[0] >> MAC_BYTE_0) & MAC_BYTE_MASK;
	fdb->mac[1] = (reg[0] >> MAC_BYTE_1) & MAC_BYTE_MASK;
	fdb->mac[2] = (reg[0] >> MAC_BYTE_2) & MAC_BYTE_MASK;
	fdb->mac[3] = (reg[0] >> MAC_BYTE_3) & MAC_BYTE_MASK;
	fdb->mac[4] = (reg[1] >> MAC_BYTE_4) & MAC_BYTE_MASK;
	fdb->mac[5] = (reg[1] >> MAC_BYTE_5) & MAC_BYTE_MASK;
	fdb->noarp = ((reg[2] >> ENT_STATUS) & ENT_STATUS_MASK) == STATIC_ENT;
पूर्ण

अटल व्योम
mt7530_fdb_ग_लिखो(काष्ठा mt7530_priv *priv, u16 vid,
		 u8 port_mask, स्थिर u8 *mac,
		 u8 aging, u8 type)
अणु
	u32 reg[3] = अणु 0 पूर्ण;
	पूर्णांक i;

	reg[1] |= vid & CVID_MASK;
	reg[2] |= (aging & AGE_TIMER_MASK) << AGE_TIMER;
	reg[2] |= (port_mask & PORT_MAP_MASK) << PORT_MAP;
	/* STATIC_ENT indicate that entry is अटल wouldn't
	 * be aged out and STATIC_EMP specअगरied as erasing an
	 * entry
	 */
	reg[2] |= (type & ENT_STATUS_MASK) << ENT_STATUS;
	reg[1] |= mac[5] << MAC_BYTE_5;
	reg[1] |= mac[4] << MAC_BYTE_4;
	reg[0] |= mac[3] << MAC_BYTE_3;
	reg[0] |= mac[2] << MAC_BYTE_2;
	reg[0] |= mac[1] << MAC_BYTE_1;
	reg[0] |= mac[0] << MAC_BYTE_0;

	/* Write array पूर्णांकo the ARL table */
	क्रम (i = 0; i < 3; i++)
		mt7530_ग_लिखो(priv, MT7530_ATA1 + (i * 4), reg[i]);
पूर्ण

/* Setup TX circuit including relevant PAD and driving */
अटल पूर्णांक
mt7530_pad_clk_setup(काष्ठा dsa_चयन *ds, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 ncpo1, ssc_delta, trgपूर्णांक, i, xtal;

	xtal = mt7530_पढ़ो(priv, MT7530_MHWTRAP) & HWTRAP_XTAL_MASK;

	अगर (xtal == HWTRAP_XTAL_20MHZ) अणु
		dev_err(priv->dev,
			"%s: MT7530 with a 20MHz XTAL is not supported!\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		trgपूर्णांक = 0;
		/* PLL frequency: 125MHz */
		ncpo1 = 0x0c80;
		अवरोध;
	हाल PHY_INTERFACE_MODE_TRGMII:
		trgपूर्णांक = 1;
		अगर (priv->id == ID_MT7621) अणु
			/* PLL frequency: 150MHz: 1.2GBit */
			अगर (xtal == HWTRAP_XTAL_40MHZ)
				ncpo1 = 0x0780;
			अगर (xtal == HWTRAP_XTAL_25MHZ)
				ncpo1 = 0x0a00;
		पूर्ण अन्यथा अणु /* PLL frequency: 250MHz: 2.0Gbit */
			अगर (xtal == HWTRAP_XTAL_40MHZ)
				ncpo1 = 0x0c80;
			अगर (xtal == HWTRAP_XTAL_25MHZ)
				ncpo1 = 0x1400;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(priv->dev, "xMII interface %d not supported\n",
			पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	अगर (xtal == HWTRAP_XTAL_25MHZ)
		ssc_delta = 0x57;
	अन्यथा
		ssc_delta = 0x87;

	mt7530_rmw(priv, MT7530_P6ECR, P6_INTF_MODE_MASK,
		   P6_INTF_MODE(trgपूर्णांक));

	/* Lower Tx Driving क्रम TRGMII path */
	क्रम (i = 0 ; i < NUM_TRGMII_CTRL ; i++)
		mt7530_ग_लिखो(priv, MT7530_TRGMII_TD_ODT(i),
			     TD_DM_DRVP(8) | TD_DM_DRVN(8));

	/* Disable MT7530 core and TRGMII Tx घड़ीs */
	core_clear(priv, CORE_TRGMII_GSW_CLK_CG,
		   REG_GSWCK_EN | REG_TRGMIICK_EN);

	/* Setup core घड़ी क्रम MT7530 */
	/* Disable PLL */
	core_ग_लिखो(priv, CORE_GSWPLL_GRP1, 0);

	/* Set core घड़ी पूर्णांकo 500Mhz */
	core_ग_लिखो(priv, CORE_GSWPLL_GRP2,
		   RG_GSWPLL_POSDIV_500M(1) |
		   RG_GSWPLL_FBKDIV_500M(25));

	/* Enable PLL */
	core_ग_लिखो(priv, CORE_GSWPLL_GRP1,
		   RG_GSWPLL_EN_PRE |
		   RG_GSWPLL_POSDIV_200M(2) |
		   RG_GSWPLL_FBKDIV_200M(32));

	/* Setup the MT7530 TRGMII Tx Clock */
	core_ग_लिखो(priv, CORE_PLL_GROUP5, RG_LCDDS_PCW_NCPO1(ncpo1));
	core_ग_लिखो(priv, CORE_PLL_GROUP6, RG_LCDDS_PCW_NCPO0(0));
	core_ग_लिखो(priv, CORE_PLL_GROUP10, RG_LCDDS_SSC_DELTA(ssc_delta));
	core_ग_लिखो(priv, CORE_PLL_GROUP11, RG_LCDDS_SSC_DELTA1(ssc_delta));
	core_ग_लिखो(priv, CORE_PLL_GROUP4,
		   RG_SYSPLL_DDSFBK_EN | RG_SYSPLL_BIAS_EN |
		   RG_SYSPLL_BIAS_LPF_EN);
	core_ग_लिखो(priv, CORE_PLL_GROUP2,
		   RG_SYSPLL_EN_NORMAL | RG_SYSPLL_VODEN |
		   RG_SYSPLL_POSDIV(1));
	core_ग_लिखो(priv, CORE_PLL_GROUP7,
		   RG_LCDDS_PCW_NCPO_CHG | RG_LCCDS_C(3) |
		   RG_LCDDS_PWDB | RG_LCDDS_ISO_EN);

	/* Enable MT7530 core and TRGMII Tx घड़ीs */
	core_set(priv, CORE_TRGMII_GSW_CLK_CG,
		 REG_GSWCK_EN | REG_TRGMIICK_EN);

	अगर (!trgपूर्णांक)
		क्रम (i = 0 ; i < NUM_TRGMII_CTRL; i++)
			mt7530_rmw(priv, MT7530_TRGMII_RD(i),
				   RD_TAP_MASK, RD_TAP(16));
	वापस 0;
पूर्ण

अटल bool mt7531_dual_sgmii_supported(काष्ठा mt7530_priv *priv)
अणु
	u32 val;

	val = mt7530_पढ़ो(priv, MT7531_TOP_SIG_SR);

	वापस (val & PAD_DUAL_SGMII_EN) != 0;
पूर्ण

अटल पूर्णांक
mt7531_pad_setup(काष्ठा dsa_चयन *ds, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 top_sig;
	u32 hwstrap;
	u32 xtal;
	u32 val;

	अगर (mt7531_dual_sgmii_supported(priv))
		वापस 0;

	val = mt7530_पढ़ो(priv, MT7531_CREV);
	top_sig = mt7530_पढ़ो(priv, MT7531_TOP_SIG_SR);
	hwstrap = mt7530_पढ़ो(priv, MT7531_HWTRAP);
	अगर ((val & CHIP_REV_M) > 0)
		xtal = (top_sig & PAD_MCM_SMI_EN) ? HWTRAP_XTAL_FSEL_40MHZ :
						    HWTRAP_XTAL_FSEL_25MHZ;
	अन्यथा
		xtal = hwstrap & HWTRAP_XTAL_FSEL_MASK;

	/* Step 1 : Disable MT7531 COREPLL */
	val = mt7530_पढ़ो(priv, MT7531_PLLGP_EN);
	val &= ~EN_COREPLL;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_EN, val);

	/* Step 2: चयन to XTAL output */
	val = mt7530_पढ़ो(priv, MT7531_PLLGP_EN);
	val |= SW_CLKSW;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_EN, val);

	val = mt7530_पढ़ो(priv, MT7531_PLLGP_CR0);
	val &= ~RG_COREPLL_EN;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_CR0, val);

	/* Step 3: disable PLLGP and enable program PLLGP */
	val = mt7530_पढ़ो(priv, MT7531_PLLGP_EN);
	val |= SW_PLLGP;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_EN, val);

	/* Step 4: program COREPLL output frequency to 500MHz */
	val = mt7530_पढ़ो(priv, MT7531_PLLGP_CR0);
	val &= ~RG_COREPLL_POSDIV_M;
	val |= 2 << RG_COREPLL_POSDIV_S;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_CR0, val);
	usleep_range(25, 35);

	चयन (xtal) अणु
	हाल HWTRAP_XTAL_FSEL_25MHZ:
		val = mt7530_पढ़ो(priv, MT7531_PLLGP_CR0);
		val &= ~RG_COREPLL_SDM_PCW_M;
		val |= 0x140000 << RG_COREPLL_SDM_PCW_S;
		mt7530_ग_लिखो(priv, MT7531_PLLGP_CR0, val);
		अवरोध;
	हाल HWTRAP_XTAL_FSEL_40MHZ:
		val = mt7530_पढ़ो(priv, MT7531_PLLGP_CR0);
		val &= ~RG_COREPLL_SDM_PCW_M;
		val |= 0x190000 << RG_COREPLL_SDM_PCW_S;
		mt7530_ग_लिखो(priv, MT7531_PLLGP_CR0, val);
		अवरोध;
	पूर्ण

	/* Set feedback भागide ratio update संकेत to high */
	val = mt7530_पढ़ो(priv, MT7531_PLLGP_CR0);
	val |= RG_COREPLL_SDM_PCW_CHG;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_CR0, val);
	/* Wait क्रम at least 16 XTAL घड़ीs */
	usleep_range(10, 20);

	/* Step 5: set feedback भागide ratio update संकेत to low */
	val = mt7530_पढ़ो(priv, MT7531_PLLGP_CR0);
	val &= ~RG_COREPLL_SDM_PCW_CHG;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_CR0, val);

	/* Enable 325M घड़ी क्रम SGMII */
	mt7530_ग_लिखो(priv, MT7531_ANA_PLLGP_CR5, 0xad0000);

	/* Enable 250SSC घड़ी क्रम RGMII */
	mt7530_ग_लिखो(priv, MT7531_ANA_PLLGP_CR2, 0x4f40000);

	/* Step 6: Enable MT7531 PLL */
	val = mt7530_पढ़ो(priv, MT7531_PLLGP_CR0);
	val |= RG_COREPLL_EN;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_CR0, val);

	val = mt7530_पढ़ो(priv, MT7531_PLLGP_EN);
	val |= EN_COREPLL;
	mt7530_ग_लिखो(priv, MT7531_PLLGP_EN, val);
	usleep_range(25, 35);

	वापस 0;
पूर्ण

अटल व्योम
mt7530_mib_reset(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	mt7530_ग_लिखो(priv, MT7530_MIB_CCR, CCR_MIB_FLUSH);
	mt7530_ग_लिखो(priv, MT7530_MIB_CCR, CCR_MIB_ACTIVATE);
पूर्ण

अटल पूर्णांक mt7530_phy_पढ़ो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस mdiobus_पढ़ो_nested(priv->bus, port, regnum);
पूर्ण

अटल पूर्णांक mt7530_phy_ग_लिखो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum,
			    u16 val)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस mdiobus_ग_लिखो_nested(priv->bus, port, regnum, val);
पूर्ण

अटल पूर्णांक
mt7531_ind_c45_phy_पढ़ो(काष्ठा mt7530_priv *priv, पूर्णांक port, पूर्णांक devad,
			पूर्णांक regnum)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	काष्ठा mt7530_dummy_poll p;
	u32 reg, val;
	पूर्णांक ret;

	INIT_MT7530_DUMMY_POLL(&p, priv, MT7531_PHY_IAC);

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, val,
				 !(val & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

	reg = MT7531_MDIO_CL45_ADDR | MT7531_MDIO_PHY_ADDR(port) |
	      MT7531_MDIO_DEV_ADDR(devad) | regnum;
	mt7530_mii_ग_लिखो(priv, MT7531_PHY_IAC, reg | MT7531_PHY_ACS_ST);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, val,
				 !(val & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

	reg = MT7531_MDIO_CL45_READ | MT7531_MDIO_PHY_ADDR(port) |
	      MT7531_MDIO_DEV_ADDR(devad);
	mt7530_mii_ग_लिखो(priv, MT7531_PHY_IAC, reg | MT7531_PHY_ACS_ST);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, val,
				 !(val & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

	ret = val & MT7531_MDIO_RW_DATA_MASK;
out:
	mutex_unlock(&bus->mdio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7531_ind_c45_phy_ग_लिखो(काष्ठा mt7530_priv *priv, पूर्णांक port, पूर्णांक devad,
			 पूर्णांक regnum, u32 data)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	काष्ठा mt7530_dummy_poll p;
	u32 val, reg;
	पूर्णांक ret;

	INIT_MT7530_DUMMY_POLL(&p, priv, MT7531_PHY_IAC);

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, val,
				 !(val & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

	reg = MT7531_MDIO_CL45_ADDR | MT7531_MDIO_PHY_ADDR(port) |
	      MT7531_MDIO_DEV_ADDR(devad) | regnum;
	mt7530_mii_ग_लिखो(priv, MT7531_PHY_IAC, reg | MT7531_PHY_ACS_ST);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, val,
				 !(val & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

	reg = MT7531_MDIO_CL45_WRITE | MT7531_MDIO_PHY_ADDR(port) |
	      MT7531_MDIO_DEV_ADDR(devad) | data;
	mt7530_mii_ग_लिखो(priv, MT7531_PHY_IAC, reg | MT7531_PHY_ACS_ST);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, val,
				 !(val & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&bus->mdio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7531_ind_c22_phy_पढ़ो(काष्ठा mt7530_priv *priv, पूर्णांक port, पूर्णांक regnum)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	काष्ठा mt7530_dummy_poll p;
	पूर्णांक ret;
	u32 val;

	INIT_MT7530_DUMMY_POLL(&p, priv, MT7531_PHY_IAC);

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, val,
				 !(val & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

	val = MT7531_MDIO_CL22_READ | MT7531_MDIO_PHY_ADDR(port) |
	      MT7531_MDIO_REG_ADDR(regnum);

	mt7530_mii_ग_लिखो(priv, MT7531_PHY_IAC, val | MT7531_PHY_ACS_ST);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, val,
				 !(val & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

	ret = val & MT7531_MDIO_RW_DATA_MASK;
out:
	mutex_unlock(&bus->mdio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7531_ind_c22_phy_ग_लिखो(काष्ठा mt7530_priv *priv, पूर्णांक port, पूर्णांक regnum,
			 u16 data)
अणु
	काष्ठा mii_bus *bus = priv->bus;
	काष्ठा mt7530_dummy_poll p;
	पूर्णांक ret;
	u32 reg;

	INIT_MT7530_DUMMY_POLL(&p, priv, MT7531_PHY_IAC);

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, reg,
				 !(reg & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

	reg = MT7531_MDIO_CL22_WRITE | MT7531_MDIO_PHY_ADDR(port) |
	      MT7531_MDIO_REG_ADDR(regnum) | data;

	mt7530_mii_ग_लिखो(priv, MT7531_PHY_IAC, reg | MT7531_PHY_ACS_ST);

	ret = पढ़ोx_poll_समयout(_mt7530_unlocked_पढ़ो, &p, reg,
				 !(reg & MT7531_PHY_ACS_ST), 20, 100000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&bus->mdio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7531_ind_phy_पढ़ो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	पूर्णांक devad;
	पूर्णांक ret;

	अगर (regnum & MII_ADDR_C45) अणु
		devad = (regnum >> MII_DEVADDR_C45_SHIFT) & 0x1f;
		ret = mt7531_ind_c45_phy_पढ़ो(priv, port, devad,
					      regnum & MII_REGADDR_C45_MASK);
	पूर्ण अन्यथा अणु
		ret = mt7531_ind_c22_phy_पढ़ो(priv, port, regnum);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7531_ind_phy_ग_लिखो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum,
		     u16 data)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	पूर्णांक devad;
	पूर्णांक ret;

	अगर (regnum & MII_ADDR_C45) अणु
		devad = (regnum >> MII_DEVADDR_C45_SHIFT) & 0x1f;
		ret = mt7531_ind_c45_phy_ग_लिखो(priv, port, devad,
					       regnum & MII_REGADDR_C45_MASK,
					       data);
	पूर्ण अन्यथा अणु
		ret = mt7531_ind_c22_phy_ग_लिखो(priv, port, regnum, data);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
mt7530_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port, u32 stringset,
		   uपूर्णांक8_t *data)
अणु
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(mt7530_mib); i++)
		म_नकलन(data + i * ETH_GSTRING_LEN, mt7530_mib[i].name,
			ETH_GSTRING_LEN);
पूर्ण

अटल व्योम
mt7530_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 uपूर्णांक64_t *data)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	स्थिर काष्ठा mt7530_mib_desc *mib;
	u32 reg, i;
	u64 hi;

	क्रम (i = 0; i < ARRAY_SIZE(mt7530_mib); i++) अणु
		mib = &mt7530_mib[i];
		reg = MT7530_PORT_MIB_COUNTER(port) + mib->offset;

		data[i] = mt7530_पढ़ो(priv, reg);
		अगर (mib->size == 2) अणु
			hi = mt7530_पढ़ो(priv, reg + 4);
			data[i] |= hi << 32;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
mt7530_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS)
		वापस 0;

	वापस ARRAY_SIZE(mt7530_mib);
पूर्ण

अटल पूर्णांक
mt7530_set_ageing_समय(काष्ठा dsa_चयन *ds, अचिन्हित पूर्णांक msecs)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	अचिन्हित पूर्णांक secs = msecs / 1000;
	अचिन्हित पूर्णांक पंचांगp_age_count;
	अचिन्हित पूर्णांक error = -1;
	अचिन्हित पूर्णांक age_count;
	अचिन्हित पूर्णांक age_unit;

	/* Applied समयr is (AGE_CNT + 1) * (AGE_UNIT + 1) seconds */
	अगर (secs < 1 || secs > (AGE_CNT_MAX + 1) * (AGE_UNIT_MAX + 1))
		वापस -दुस्फल;

	/* iterate through all possible age_count to find the बंदst pair */
	क्रम (पंचांगp_age_count = 0; पंचांगp_age_count <= AGE_CNT_MAX; ++पंचांगp_age_count) अणु
		अचिन्हित पूर्णांक पंचांगp_age_unit = secs / (पंचांगp_age_count + 1) - 1;

		अगर (पंचांगp_age_unit <= AGE_UNIT_MAX) अणु
			अचिन्हित पूर्णांक पंचांगp_error = secs -
				(पंचांगp_age_count + 1) * (पंचांगp_age_unit + 1);

			/* found a बंदr pair */
			अगर (error > पंचांगp_error) अणु
				error = पंचांगp_error;
				age_count = पंचांगp_age_count;
				age_unit = पंचांगp_age_unit;
			पूर्ण

			/* found the exact match, so अवरोध the loop */
			अगर (!error)
				अवरोध;
		पूर्ण
	पूर्ण

	mt7530_ग_लिखो(priv, MT7530_AAC, AGE_CNT(age_count) | AGE_UNIT(age_unit));

	वापस 0;
पूर्ण

अटल व्योम mt7530_setup_port5(काष्ठा dsa_चयन *ds, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u8 tx_delay = 0;
	पूर्णांक val;

	mutex_lock(&priv->reg_mutex);

	val = mt7530_पढ़ो(priv, MT7530_MHWTRAP);

	val |= MHWTRAP_MANUAL | MHWTRAP_P5_MAC_SEL | MHWTRAP_P5_DIS;
	val &= ~MHWTRAP_P5_RGMII_MODE & ~MHWTRAP_PHY0_SEL;

	चयन (priv->p5_पूर्णांकf_sel) अणु
	हाल P5_INTF_SEL_PHY_P0:
		/* MT7530_P5_MODE_GPHY_P0: 2nd GMAC -> P5 -> P0 */
		val |= MHWTRAP_PHY0_SEL;
		fallthrough;
	हाल P5_INTF_SEL_PHY_P4:
		/* MT7530_P5_MODE_GPHY_P4: 2nd GMAC -> P5 -> P4 */
		val &= ~MHWTRAP_P5_MAC_SEL & ~MHWTRAP_P5_DIS;

		/* Setup the MAC by शेष क्रम the cpu port */
		mt7530_ग_लिखो(priv, MT7530_PMCR_P(5), 0x56300);
		अवरोध;
	हाल P5_INTF_SEL_GMAC5:
		/* MT7530_P5_MODE_GMAC: P5 -> External phy or 2nd GMAC */
		val &= ~MHWTRAP_P5_DIS;
		अवरोध;
	हाल P5_DISABLED:
		पूर्णांकerface = PHY_INTERFACE_MODE_NA;
		अवरोध;
	शेष:
		dev_err(ds->dev, "Unsupported p5_intf_sel %d\n",
			priv->p5_पूर्णांकf_sel);
		जाओ unlock_निकास;
	पूर्ण

	/* Setup RGMII settings */
	अगर (phy_पूर्णांकerface_mode_is_rgmii(पूर्णांकerface)) अणु
		val |= MHWTRAP_P5_RGMII_MODE;

		/* P5 RGMII RX Clock Control: delay setting क्रम 1000M */
		mt7530_ग_लिखो(priv, MT7530_P5RGMIIRXCR, CSR_RGMII_EDGE_ALIGN);

		/* Don't set delay in DSA mode */
		अगर (!dsa_is_dsa_port(priv->ds, 5) &&
		    (पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID ||
		     पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID))
			tx_delay = 4; /* n * 0.5 ns */

		/* P5 RGMII TX Clock Control: delay x */
		mt7530_ग_लिखो(priv, MT7530_P5RGMIITXCR,
			     CSR_RGMII_TXC_CFG(0x10 + tx_delay));

		/* reduce P5 RGMII Tx driving, 8mA */
		mt7530_ग_लिखो(priv, MT7530_IO_DRV_CR,
			     P5_IO_CLK_DRV(1) | P5_IO_DATA_DRV(1));
	पूर्ण

	mt7530_ग_लिखो(priv, MT7530_MHWTRAP, val);

	dev_dbg(ds->dev, "Setup P5, HWTRAP=0x%x, intf_sel=%s, phy-mode=%s\n",
		val, p5_पूर्णांकf_modes(priv->p5_पूर्णांकf_sel), phy_modes(पूर्णांकerface));

	priv->p5_पूर्णांकerface = पूर्णांकerface;

unlock_निकास:
	mutex_unlock(&priv->reg_mutex);
पूर्ण

अटल पूर्णांक
mt753x_cpu_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	पूर्णांक ret;

	/* Setup max capability of CPU port at first */
	अगर (priv->info->cpu_port_config) अणु
		ret = priv->info->cpu_port_config(ds, port);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Enable Mediatek header mode on the cpu port */
	mt7530_ग_लिखो(priv, MT7530_PVC_P(port),
		     PORT_SPEC_TAG);

	/* Disable flooding by शेष */
	mt7530_rmw(priv, MT7530_MFC, BC_FFP_MASK | UNM_FFP_MASK | UNU_FFP_MASK,
		   BC_FFP(BIT(port)) | UNM_FFP(BIT(port)) | UNU_FFP(BIT(port)));

	/* Set CPU port number */
	अगर (priv->id == ID_MT7621)
		mt7530_rmw(priv, MT7530_MFC, CPU_MASK, CPU_EN | CPU_PORT(port));

	/* CPU port माला_लो connected to all user ports of
	 * the चयन.
	 */
	mt7530_ग_लिखो(priv, MT7530_PCR_P(port),
		     PCR_MATRIX(dsa_user_ports(priv->ds)));

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
		   काष्ठा phy_device *phy)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	अगर (!dsa_is_user_port(ds, port))
		वापस 0;

	mutex_lock(&priv->reg_mutex);

	/* Allow the user port माला_लो connected to the cpu port and also
	 * restore the port matrix अगर the port is the member of a certain
	 * bridge.
	 */
	priv->ports[port].pm |= PCR_MATRIX(BIT(MT7530_CPU_PORT));
	priv->ports[port].enable = true;
	mt7530_rmw(priv, MT7530_PCR_P(port), PCR_MATRIX_MASK,
		   priv->ports[port].pm);
	mt7530_clear(priv, MT7530_PMCR_P(port), PMCR_LINK_SETTINGS_MASK);

	mutex_unlock(&priv->reg_mutex);

	वापस 0;
पूर्ण

अटल व्योम
mt7530_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	अगर (!dsa_is_user_port(ds, port))
		वापस;

	mutex_lock(&priv->reg_mutex);

	/* Clear up all port matrix which could be restored in the next
	 * enablement क्रम the port.
	 */
	priv->ports[port].enable = false;
	mt7530_rmw(priv, MT7530_PCR_P(port), PCR_MATRIX_MASK,
		   PCR_MATRIX_CLR);
	mt7530_clear(priv, MT7530_PMCR_P(port), PMCR_LINK_SETTINGS_MASK);

	mutex_unlock(&priv->reg_mutex);
पूर्ण

अटल पूर्णांक
mt7530_port_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक new_mtu)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	काष्ठा mii_bus *bus = priv->bus;
	पूर्णांक length;
	u32 val;

	/* When a new MTU is set, DSA always set the CPU port's MTU to the
	 * largest MTU of the slave ports. Because the चयन only has a global
	 * RX length रेजिस्टर, only allowing CPU port here is enough.
	 */
	अगर (!dsa_is_cpu_port(ds, port))
		वापस 0;

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);

	val = mt7530_mii_पढ़ो(priv, MT7530_GMACCR);
	val &= ~MAX_RX_PKT_LEN_MASK;

	/* RX length also includes Ethernet header, MTK tag, and FCS length */
	length = new_mtu + ETH_HLEN + MTK_HDR_LEN + ETH_FCS_LEN;
	अगर (length <= 1522) अणु
		val |= MAX_RX_PKT_LEN_1522;
	पूर्ण अन्यथा अगर (length <= 1536) अणु
		val |= MAX_RX_PKT_LEN_1536;
	पूर्ण अन्यथा अगर (length <= 1552) अणु
		val |= MAX_RX_PKT_LEN_1552;
	पूर्ण अन्यथा अणु
		val &= ~MAX_RX_JUMBO_MASK;
		val |= MAX_RX_JUMBO(DIV_ROUND_UP(length, 1024));
		val |= MAX_RX_PKT_LEN_JUMBO;
	पूर्ण

	mt7530_mii_ग_लिखो(priv, MT7530_GMACCR, val);

	mutex_unlock(&bus->mdio_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_port_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस MT7530_MAX_MTU;
पूर्ण

अटल व्योम
mt7530_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port, u8 state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 stp_state;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		stp_state = MT7530_STP_DISABLED;
		अवरोध;
	हाल BR_STATE_BLOCKING:
		stp_state = MT7530_STP_BLOCKING;
		अवरोध;
	हाल BR_STATE_LISTENING:
		stp_state = MT7530_STP_LISTENING;
		अवरोध;
	हाल BR_STATE_LEARNING:
		stp_state = MT7530_STP_LEARNING;
		अवरोध;
	हाल BR_STATE_FORWARDING:
	शेष:
		stp_state = MT7530_STP_FORWARDING;
		अवरोध;
	पूर्ण

	mt7530_rmw(priv, MT7530_SSP_P(port), FID_PST_MASK, stp_state);
पूर्ण

अटल पूर्णांक
mt7530_port_pre_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा चयनdev_brport_flags flags,
			     काष्ठा netlink_ext_ack *extack)
अणु
	अगर (flags.mask & ~(BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD |
			   BR_BCAST_FLOOD))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_port_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 काष्ठा चयनdev_brport_flags flags,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	अगर (flags.mask & BR_LEARNING)
		mt7530_rmw(priv, MT7530_PSC_P(port), SA_DIS,
			   flags.val & BR_LEARNING ? 0 : SA_DIS);

	अगर (flags.mask & BR_FLOOD)
		mt7530_rmw(priv, MT7530_MFC, UNU_FFP(BIT(port)),
			   flags.val & BR_FLOOD ? UNU_FFP(BIT(port)) : 0);

	अगर (flags.mask & BR_MCAST_FLOOD)
		mt7530_rmw(priv, MT7530_MFC, UNM_FFP(BIT(port)),
			   flags.val & BR_MCAST_FLOOD ? UNM_FFP(BIT(port)) : 0);

	अगर (flags.mask & BR_BCAST_FLOOD)
		mt7530_rmw(priv, MT7530_MFC, BC_FFP(BIT(port)),
			   flags.val & BR_BCAST_FLOOD ? BC_FFP(BIT(port)) : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_port_set_mrouter(काष्ठा dsa_चयन *ds, पूर्णांक port, bool mrouter,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	mt7530_rmw(priv, MT7530_MFC, UNM_FFP(BIT(port)),
		   mrouter ? UNM_FFP(BIT(port)) : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
			काष्ठा net_device *bridge)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 port_biपंचांगap = BIT(MT7530_CPU_PORT);
	पूर्णांक i;

	mutex_lock(&priv->reg_mutex);

	क्रम (i = 0; i < MT7530_NUM_PORTS; i++) अणु
		/* Add this port to the port matrix of the other ports in the
		 * same bridge. If the port is disabled, port matrix is kept
		 * and not being setup until the port becomes enabled.
		 */
		अगर (dsa_is_user_port(ds, i) && i != port) अणु
			अगर (dsa_to_port(ds, i)->bridge_dev != bridge)
				जारी;
			अगर (priv->ports[i].enable)
				mt7530_set(priv, MT7530_PCR_P(i),
					   PCR_MATRIX(BIT(port)));
			priv->ports[i].pm |= PCR_MATRIX(BIT(port));

			port_biपंचांगap |= BIT(i);
		पूर्ण
	पूर्ण

	/* Add the all other ports to this port matrix. */
	अगर (priv->ports[port].enable)
		mt7530_rmw(priv, MT7530_PCR_P(port),
			   PCR_MATRIX_MASK, PCR_MATRIX(port_biपंचांगap));
	priv->ports[port].pm |= PCR_MATRIX(port_biपंचांगap);

	mutex_unlock(&priv->reg_mutex);

	वापस 0;
पूर्ण

अटल व्योम
mt7530_port_set_vlan_unaware(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	bool all_user_ports_हटाओd = true;
	पूर्णांक i;

	/* When a port is हटाओd from the bridge, the port would be set up
	 * back to the शेष as is at initial boot which is a VLAN-unaware
	 * port.
	 */
	mt7530_rmw(priv, MT7530_PCR_P(port), PCR_PORT_VLAN_MASK,
		   MT7530_PORT_MATRIX_MODE);
	mt7530_rmw(priv, MT7530_PVC_P(port), VLAN_ATTR_MASK | PVC_EG_TAG_MASK,
		   VLAN_ATTR(MT7530_VLAN_TRANSPARENT) |
		   PVC_EG_TAG(MT7530_VLAN_EG_CONSISTENT));

	क्रम (i = 0; i < MT7530_NUM_PORTS; i++) अणु
		अगर (dsa_is_user_port(ds, i) &&
		    dsa_port_is_vlan_filtering(dsa_to_port(ds, i))) अणु
			all_user_ports_हटाओd = false;
			अवरोध;
		पूर्ण
	पूर्ण

	/* CPU port also करोes the same thing until all user ports beदीर्घing to
	 * the CPU port get out of VLAN filtering mode.
	 */
	अगर (all_user_ports_हटाओd) अणु
		mt7530_ग_लिखो(priv, MT7530_PCR_P(MT7530_CPU_PORT),
			     PCR_MATRIX(dsa_user_ports(priv->ds)));
		mt7530_ग_लिखो(priv, MT7530_PVC_P(MT7530_CPU_PORT), PORT_SPEC_TAG
			     | PVC_EG_TAG(MT7530_VLAN_EG_CONSISTENT));
	पूर्ण
पूर्ण

अटल व्योम
mt7530_port_set_vlan_aware(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	/* Trapped पूर्णांकo security mode allows packet क्रमwarding through VLAN
	 * table lookup. CPU port is set to fallback mode to let untagged
	 * frames pass through.
	 */
	अगर (dsa_is_cpu_port(ds, port))
		mt7530_rmw(priv, MT7530_PCR_P(port), PCR_PORT_VLAN_MASK,
			   MT7530_PORT_FALLBACK_MODE);
	अन्यथा
		mt7530_rmw(priv, MT7530_PCR_P(port), PCR_PORT_VLAN_MASK,
			   MT7530_PORT_SECURITY_MODE);

	/* Set the port as a user port which is to be able to recognize VID
	 * from incoming packets beक्रमe fetching entry within the VLAN table.
	 */
	mt7530_rmw(priv, MT7530_PVC_P(port), VLAN_ATTR_MASK | PVC_EG_TAG_MASK,
		   VLAN_ATTR(MT7530_VLAN_USER) |
		   PVC_EG_TAG(MT7530_VLAN_EG_DISABLED));
पूर्ण

अटल व्योम
mt7530_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 काष्ठा net_device *bridge)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	पूर्णांक i;

	mutex_lock(&priv->reg_mutex);

	क्रम (i = 0; i < MT7530_NUM_PORTS; i++) अणु
		/* Remove this port from the port matrix of the other ports
		 * in the same bridge. If the port is disabled, port matrix
		 * is kept and not being setup until the port becomes enabled.
		 * And the other port's port matrix cannot be broken when the
		 * other port is still a VLAN-aware port.
		 */
		अगर (dsa_is_user_port(ds, i) && i != port &&
		   !dsa_port_is_vlan_filtering(dsa_to_port(ds, i))) अणु
			अगर (dsa_to_port(ds, i)->bridge_dev != bridge)
				जारी;
			अगर (priv->ports[i].enable)
				mt7530_clear(priv, MT7530_PCR_P(i),
					     PCR_MATRIX(BIT(port)));
			priv->ports[i].pm &= ~PCR_MATRIX(BIT(port));
		पूर्ण
	पूर्ण

	/* Set the cpu port to be the only one in the port matrix of
	 * this port.
	 */
	अगर (priv->ports[port].enable)
		mt7530_rmw(priv, MT7530_PCR_P(port), PCR_MATRIX_MASK,
			   PCR_MATRIX(BIT(MT7530_CPU_PORT)));
	priv->ports[port].pm = PCR_MATRIX(BIT(MT7530_CPU_PORT));

	mutex_unlock(&priv->reg_mutex);
पूर्ण

अटल पूर्णांक
mt7530_port_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	पूर्णांक ret;
	u8 port_mask = BIT(port);

	mutex_lock(&priv->reg_mutex);
	mt7530_fdb_ग_लिखो(priv, vid, port_mask, addr, -1, STATIC_ENT);
	ret = mt7530_fdb_cmd(priv, MT7530_FDB_WRITE, शून्य);
	mutex_unlock(&priv->reg_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7530_port_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	पूर्णांक ret;
	u8 port_mask = BIT(port);

	mutex_lock(&priv->reg_mutex);
	mt7530_fdb_ग_लिखो(priv, vid, port_mask, addr, -1, STATIC_EMP);
	ret = mt7530_fdb_cmd(priv, MT7530_FDB_WRITE, शून्य);
	mutex_unlock(&priv->reg_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7530_port_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	काष्ठा mt7530_fdb _fdb = अणु 0 पूर्ण;
	पूर्णांक cnt = MT7530_NUM_FDB_RECORDS;
	पूर्णांक ret = 0;
	u32 rsp = 0;

	mutex_lock(&priv->reg_mutex);

	ret = mt7530_fdb_cmd(priv, MT7530_FDB_START, &rsp);
	अगर (ret < 0)
		जाओ err;

	करो अणु
		अगर (rsp & ATC_SRCH_HIT) अणु
			mt7530_fdb_पढ़ो(priv, &_fdb);
			अगर (_fdb.port_mask & BIT(port)) अणु
				ret = cb(_fdb.mac, _fdb.vid, _fdb.noarp,
					 data);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (--cnt &&
		 !(rsp & ATC_SRCH_END) &&
		 !mt7530_fdb_cmd(priv, MT7530_FDB_NEXT, &rsp));
err:
	mutex_unlock(&priv->reg_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_port_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	स्थिर u8 *addr = mdb->addr;
	u16 vid = mdb->vid;
	u8 port_mask = 0;
	पूर्णांक ret;

	mutex_lock(&priv->reg_mutex);

	mt7530_fdb_ग_लिखो(priv, vid, 0, addr, 0, STATIC_EMP);
	अगर (!mt7530_fdb_cmd(priv, MT7530_FDB_READ, शून्य))
		port_mask = (mt7530_पढ़ो(priv, MT7530_ATRD) >> PORT_MAP)
			    & PORT_MAP_MASK;

	port_mask |= BIT(port);
	mt7530_fdb_ग_लिखो(priv, vid, port_mask, addr, -1, STATIC_ENT);
	ret = mt7530_fdb_cmd(priv, MT7530_FDB_WRITE, शून्य);

	mutex_unlock(&priv->reg_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7530_port_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	स्थिर u8 *addr = mdb->addr;
	u16 vid = mdb->vid;
	u8 port_mask = 0;
	पूर्णांक ret;

	mutex_lock(&priv->reg_mutex);

	mt7530_fdb_ग_लिखो(priv, vid, 0, addr, 0, STATIC_EMP);
	अगर (!mt7530_fdb_cmd(priv, MT7530_FDB_READ, शून्य))
		port_mask = (mt7530_पढ़ो(priv, MT7530_ATRD) >> PORT_MAP)
			    & PORT_MAP_MASK;

	port_mask &= ~BIT(port);
	mt7530_fdb_ग_लिखो(priv, vid, port_mask, addr, -1,
			 port_mask ? STATIC_ENT : STATIC_EMP);
	ret = mt7530_fdb_cmd(priv, MT7530_FDB_WRITE, शून्य);

	mutex_unlock(&priv->reg_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7530_vlan_cmd(काष्ठा mt7530_priv *priv, क्रमागत mt7530_vlan_cmd cmd, u16 vid)
अणु
	काष्ठा mt7530_dummy_poll p;
	u32 val;
	पूर्णांक ret;

	val = VTCR_BUSY | VTCR_FUNC(cmd) | vid;
	mt7530_ग_लिखो(priv, MT7530_VTCR, val);

	INIT_MT7530_DUMMY_POLL(&p, priv, MT7530_VTCR);
	ret = पढ़ोx_poll_समयout(_mt7530_पढ़ो, &p, val,
				 !(val & VTCR_BUSY), 20, 20000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "poll timeout\n");
		वापस ret;
	पूर्ण

	val = mt7530_पढ़ो(priv, MT7530_VTCR);
	अगर (val & VTCR_INVALID) अणु
		dev_err(priv->dev, "read VTCR invalid\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_port_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool vlan_filtering,
			   काष्ठा netlink_ext_ack *extack)
अणु
	अगर (vlan_filtering) अणु
		/* The port is being kept as VLAN-unaware port when bridge is
		 * set up with vlan_filtering not being set, Otherwise, the
		 * port and the corresponding CPU port is required the setup
		 * क्रम becoming a VLAN-aware port.
		 */
		mt7530_port_set_vlan_aware(ds, port);
		mt7530_port_set_vlan_aware(ds, MT7530_CPU_PORT);
	पूर्ण अन्यथा अणु
		mt7530_port_set_vlan_unaware(ds, port);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mt7530_hw_vlan_add(काष्ठा mt7530_priv *priv,
		   काष्ठा mt7530_hw_vlan_entry *entry)
अणु
	u8 new_members;
	u32 val;

	new_members = entry->old_members | BIT(entry->port) |
		      BIT(MT7530_CPU_PORT);

	/* Validate the entry with independent learning, create egress tag per
	 * VLAN and joining the port as one of the port members.
	 */
	val = IVL_MAC | VTAG_EN | PORT_MEM(new_members) | VLAN_VALID;
	mt7530_ग_लिखो(priv, MT7530_VAWD1, val);

	/* Decide whether adding tag or not क्रम those outgoing packets from the
	 * port inside the VLAN.
	 */
	val = entry->untagged ? MT7530_VLAN_EGRESS_UNTAG :
				MT7530_VLAN_EGRESS_TAG;
	mt7530_rmw(priv, MT7530_VAWD2,
		   ETAG_CTRL_P_MASK(entry->port),
		   ETAG_CTRL_P(entry->port, val));

	/* CPU port is always taken as a tagged port क्रम serving more than one
	 * VLANs across and also being applied with egress type stack mode क्रम
	 * that VLAN tags would be appended after hardware special tag used as
	 * DSA tag.
	 */
	mt7530_rmw(priv, MT7530_VAWD2,
		   ETAG_CTRL_P_MASK(MT7530_CPU_PORT),
		   ETAG_CTRL_P(MT7530_CPU_PORT,
			       MT7530_VLAN_EGRESS_STACK));
पूर्ण

अटल व्योम
mt7530_hw_vlan_del(काष्ठा mt7530_priv *priv,
		   काष्ठा mt7530_hw_vlan_entry *entry)
अणु
	u8 new_members;
	u32 val;

	new_members = entry->old_members & ~BIT(entry->port);

	val = mt7530_पढ़ो(priv, MT7530_VAWD1);
	अगर (!(val & VLAN_VALID)) अणु
		dev_err(priv->dev,
			"Cannot be deleted due to invalid entry\n");
		वापस;
	पूर्ण

	/* If certain member apart from CPU port is still alive in the VLAN,
	 * the entry would be kept valid. Otherwise, the entry is got to be
	 * disabled.
	 */
	अगर (new_members && new_members != BIT(MT7530_CPU_PORT)) अणु
		val = IVL_MAC | VTAG_EN | PORT_MEM(new_members) |
		      VLAN_VALID;
		mt7530_ग_लिखो(priv, MT7530_VAWD1, val);
	पूर्ण अन्यथा अणु
		mt7530_ग_लिखो(priv, MT7530_VAWD1, 0);
		mt7530_ग_लिखो(priv, MT7530_VAWD2, 0);
	पूर्ण
पूर्ण

अटल व्योम
mt7530_hw_vlan_update(काष्ठा mt7530_priv *priv, u16 vid,
		      काष्ठा mt7530_hw_vlan_entry *entry,
		      mt7530_vlan_op vlan_op)
अणु
	u32 val;

	/* Fetch entry */
	mt7530_vlan_cmd(priv, MT7530_VTCR_RD_VID, vid);

	val = mt7530_पढ़ो(priv, MT7530_VAWD1);

	entry->old_members = (val >> PORT_MEM_SHFT) & PORT_MEM_MASK;

	/* Manipulate entry */
	vlan_op(priv, entry);

	/* Flush result to hardware */
	mt7530_vlan_cmd(priv, MT7530_VTCR_WR_VID, vid);
पूर्ण

अटल पूर्णांक
mt7530_port_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
		     काष्ठा netlink_ext_ack *extack)
अणु
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा mt7530_hw_vlan_entry new_entry;
	काष्ठा mt7530_priv *priv = ds->priv;

	mutex_lock(&priv->reg_mutex);

	mt7530_hw_vlan_entry_init(&new_entry, port, untagged);
	mt7530_hw_vlan_update(priv, vlan->vid, &new_entry, mt7530_hw_vlan_add);

	अगर (pvid) अणु
		mt7530_rmw(priv, MT7530_PPBV1_P(port), G0_PORT_VID_MASK,
			   G0_PORT_VID(vlan->vid));
		priv->ports[port].pvid = vlan->vid;
	पूर्ण

	mutex_unlock(&priv->reg_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_port_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा mt7530_hw_vlan_entry target_entry;
	काष्ठा mt7530_priv *priv = ds->priv;
	u16 pvid;

	mutex_lock(&priv->reg_mutex);

	pvid = priv->ports[port].pvid;
	mt7530_hw_vlan_entry_init(&target_entry, port, 0);
	mt7530_hw_vlan_update(priv, vlan->vid, &target_entry,
			      mt7530_hw_vlan_del);

	/* PVID is being restored to the शेष whenever the PVID port
	 * is being हटाओd from the VLAN.
	 */
	अगर (pvid == vlan->vid)
		pvid = G0_PORT_VID_DEF;

	mt7530_rmw(priv, MT7530_PPBV1_P(port), G0_PORT_VID_MASK, pvid);
	priv->ports[port].pvid = pvid;

	mutex_unlock(&priv->reg_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक mt753x_mirror_port_get(अचिन्हित पूर्णांक id, u32 val)
अणु
	वापस (id == ID_MT7531) ? MT7531_MIRROR_PORT_GET(val) :
				   MIRROR_PORT(val);
पूर्ण

अटल पूर्णांक mt753x_mirror_port_set(अचिन्हित पूर्णांक id, u32 val)
अणु
	वापस (id == ID_MT7531) ? MT7531_MIRROR_PORT_SET(val) :
				   MIRROR_PORT(val);
पूर्ण

अटल पूर्णांक mt753x_port_mirror_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा dsa_mall_mirror_tc_entry *mirror,
				  bool ingress)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	पूर्णांक monitor_port;
	u32 val;

	/* Check क्रम existent entry */
	अगर ((ingress ? priv->mirror_rx : priv->mirror_tx) & BIT(port))
		वापस -EEXIST;

	val = mt7530_पढ़ो(priv, MT753X_MIRROR_REG(priv->id));

	/* MT7530 only supports one monitor port */
	monitor_port = mt753x_mirror_port_get(priv->id, val);
	अगर (val & MT753X_MIRROR_EN(priv->id) &&
	    monitor_port != mirror->to_local_port)
		वापस -EEXIST;

	val |= MT753X_MIRROR_EN(priv->id);
	val &= ~MT753X_MIRROR_MASK(priv->id);
	val |= mt753x_mirror_port_set(priv->id, mirror->to_local_port);
	mt7530_ग_लिखो(priv, MT753X_MIRROR_REG(priv->id), val);

	val = mt7530_पढ़ो(priv, MT7530_PCR_P(port));
	अगर (ingress) अणु
		val |= PORT_RX_MIR;
		priv->mirror_rx |= BIT(port);
	पूर्ण अन्यथा अणु
		val |= PORT_TX_MIR;
		priv->mirror_tx |= BIT(port);
	पूर्ण
	mt7530_ग_लिखो(priv, MT7530_PCR_P(port), val);

	वापस 0;
पूर्ण

अटल व्योम mt753x_port_mirror_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   काष्ठा dsa_mall_mirror_tc_entry *mirror)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 val;

	val = mt7530_पढ़ो(priv, MT7530_PCR_P(port));
	अगर (mirror->ingress) अणु
		val &= ~PORT_RX_MIR;
		priv->mirror_rx &= ~BIT(port);
	पूर्ण अन्यथा अणु
		val &= ~PORT_TX_MIR;
		priv->mirror_tx &= ~BIT(port);
	पूर्ण
	mt7530_ग_लिखो(priv, MT7530_PCR_P(port), val);

	अगर (!priv->mirror_rx && !priv->mirror_tx) अणु
		val = mt7530_पढ़ो(priv, MT753X_MIRROR_REG(priv->id));
		val &= ~MT753X_MIRROR_EN(priv->id);
		mt7530_ग_लिखो(priv, MT753X_MIRROR_REG(priv->id), val);
	पूर्ण
पूर्ण

अटल क्रमागत dsa_tag_protocol
mtk_get_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     क्रमागत dsa_tag_protocol mp)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	अगर (port != MT7530_CPU_PORT) अणु
		dev_warn(priv->dev,
			 "port not matched with tagging CPU port\n");
		वापस DSA_TAG_PROTO_NONE;
	पूर्ण अन्यथा अणु
		वापस DSA_TAG_PROTO_MTK;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल अंतरभूत u32
mt7530_gpio_to_bit(अचिन्हित पूर्णांक offset)
अणु
	/* Map GPIO offset to रेजिस्टर bit
	 * [ 2: 0]  port 0 LED 0..2 as GPIO 0..2
	 * [ 6: 4]  port 1 LED 0..2 as GPIO 3..5
	 * [10: 8]  port 2 LED 0..2 as GPIO 6..8
	 * [14:12]  port 3 LED 0..2 as GPIO 9..11
	 * [18:16]  port 4 LED 0..2 as GPIO 12..14
	 */
	वापस BIT(offset + offset / 3);
पूर्ण

अटल पूर्णांक
mt7530_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mt7530_priv *priv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	वापस !!(mt7530_पढ़ो(priv, MT7530_LED_GPIO_DATA) & bit);
पूर्ण

अटल व्योम
mt7530_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा mt7530_priv *priv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	अगर (value)
		mt7530_set(priv, MT7530_LED_GPIO_DATA, bit);
	अन्यथा
		mt7530_clear(priv, MT7530_LED_GPIO_DATA, bit);
पूर्ण

अटल पूर्णांक
mt7530_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mt7530_priv *priv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	वापस (mt7530_पढ़ो(priv, MT7530_LED_GPIO_सूची) & bit) ?
		GPIO_LINE_सूचीECTION_OUT : GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक
mt7530_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mt7530_priv *priv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	mt7530_clear(priv, MT7530_LED_GPIO_OE, bit);
	mt7530_clear(priv, MT7530_LED_GPIO_सूची, bit);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_gpio_direction_output(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा mt7530_priv *priv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	mt7530_set(priv, MT7530_LED_GPIO_सूची, bit);

	अगर (value)
		mt7530_set(priv, MT7530_LED_GPIO_DATA, bit);
	अन्यथा
		mt7530_clear(priv, MT7530_LED_GPIO_DATA, bit);

	mt7530_set(priv, MT7530_LED_GPIO_OE, bit);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7530_setup_gpio(काष्ठा mt7530_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा gpio_chip *gc;

	gc = devm_kzalloc(dev, माप(*gc), GFP_KERNEL);
	अगर (!gc)
		वापस -ENOMEM;

	mt7530_ग_लिखो(priv, MT7530_LED_GPIO_OE, 0);
	mt7530_ग_लिखो(priv, MT7530_LED_GPIO_सूची, 0);
	mt7530_ग_लिखो(priv, MT7530_LED_IO_MODE, 0);

	gc->label = "mt7530";
	gc->parent = dev;
	gc->owner = THIS_MODULE;
	gc->get_direction = mt7530_gpio_get_direction;
	gc->direction_input = mt7530_gpio_direction_input;
	gc->direction_output = mt7530_gpio_direction_output;
	gc->get = mt7530_gpio_get;
	gc->set = mt7530_gpio_set;
	gc->base = -1;
	gc->ngpio = 15;
	gc->can_sleep = true;

	वापस devm_gpiochip_add_data(dev, gc, priv);
पूर्ण
#पूर्ण_अगर /* CONFIG_GPIOLIB */

अटल पूर्णांक
mt7530_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	काष्ठा device_node *phy_node;
	काष्ठा device_node *mac_np;
	काष्ठा mt7530_dummy_poll p;
	phy_पूर्णांकerface_t पूर्णांकerface;
	काष्ठा device_node *dn;
	u32 id, val;
	पूर्णांक ret, i;

	/* The parent node of master netdev which holds the common प्रणाली
	 * controller also is the container क्रम two GMACs nodes representing
	 * as two netdev instances.
	 */
	dn = dsa_to_port(ds, MT7530_CPU_PORT)->master->dev.of_node->parent;
	ds->mtu_enक्रमcement_ingress = true;

	अगर (priv->id == ID_MT7530) अणु
		regulator_set_voltage(priv->core_pwr, 1000000, 1000000);
		ret = regulator_enable(priv->core_pwr);
		अगर (ret < 0) अणु
			dev_err(priv->dev,
				"Failed to enable core power: %d\n", ret);
			वापस ret;
		पूर्ण

		regulator_set_voltage(priv->io_pwr, 3300000, 3300000);
		ret = regulator_enable(priv->io_pwr);
		अगर (ret < 0) अणु
			dev_err(priv->dev, "Failed to enable io pwr: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Reset whole chip through gpio pin or memory-mapped रेजिस्टरs क्रम
	 * dअगरferent type of hardware
	 */
	अगर (priv->mcm) अणु
		reset_control_निश्चित(priv->rstc);
		usleep_range(1000, 1100);
		reset_control_deनिश्चित(priv->rstc);
	पूर्ण अन्यथा अणु
		gpiod_set_value_cansleep(priv->reset, 0);
		usleep_range(1000, 1100);
		gpiod_set_value_cansleep(priv->reset, 1);
	पूर्ण

	/* Waiting क्रम MT7530 got to stable */
	INIT_MT7530_DUMMY_POLL(&p, priv, MT7530_HWTRAP);
	ret = पढ़ोx_poll_समयout(_mt7530_पढ़ो, &p, val, val != 0,
				 20, 1000000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "reset timeout\n");
		वापस ret;
	पूर्ण

	id = mt7530_पढ़ो(priv, MT7530_CREV);
	id >>= CHIP_NAME_SHIFT;
	अगर (id != MT7530_ID) अणु
		dev_err(priv->dev, "chip %x can't be supported\n", id);
		वापस -ENODEV;
	पूर्ण

	/* Reset the चयन through पूर्णांकernal reset */
	mt7530_ग_लिखो(priv, MT7530_SYS_CTRL,
		     SYS_CTRL_PHY_RST | SYS_CTRL_SW_RST |
		     SYS_CTRL_REG_RST);

	/* Enable Port 6 only; P5 as GMAC5 which currently is not supported */
	val = mt7530_पढ़ो(priv, MT7530_MHWTRAP);
	val &= ~MHWTRAP_P6_DIS & ~MHWTRAP_PHY_ACCESS;
	val |= MHWTRAP_MANUAL;
	mt7530_ग_लिखो(priv, MT7530_MHWTRAP, val);

	priv->p6_पूर्णांकerface = PHY_INTERFACE_MODE_NA;

	/* Enable and reset MIB counters */
	mt7530_mib_reset(ds);

	क्रम (i = 0; i < MT7530_NUM_PORTS; i++) अणु
		/* Disable क्रमwarding by शेष on all ports */
		mt7530_rmw(priv, MT7530_PCR_P(i), PCR_MATRIX_MASK,
			   PCR_MATRIX_CLR);

		अगर (dsa_is_cpu_port(ds, i)) अणु
			ret = mt753x_cpu_port_enable(ds, i);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			mt7530_port_disable(ds, i);

			/* Disable learning by शेष on all user ports */
			mt7530_set(priv, MT7530_PSC_P(i), SA_DIS);
		पूर्ण
		/* Enable consistent egress tag */
		mt7530_rmw(priv, MT7530_PVC_P(i), PVC_EG_TAG_MASK,
			   PVC_EG_TAG(MT7530_VLAN_EG_CONSISTENT));
	पूर्ण

	/* Setup port 5 */
	priv->p5_पूर्णांकf_sel = P5_DISABLED;
	पूर्णांकerface = PHY_INTERFACE_MODE_NA;

	अगर (!dsa_is_unused_port(ds, 5)) अणु
		priv->p5_पूर्णांकf_sel = P5_INTF_SEL_GMAC5;
		ret = of_get_phy_mode(dsa_to_port(ds, 5)->dn, &पूर्णांकerface);
		अगर (ret && ret != -ENODEV)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Scan the ethernet nodes. look क्रम GMAC1, lookup used phy */
		क्रम_each_child_of_node(dn, mac_np) अणु
			अगर (!of_device_is_compatible(mac_np,
						     "mediatek,eth-mac"))
				जारी;

			ret = of_property_पढ़ो_u32(mac_np, "reg", &id);
			अगर (ret < 0 || id != 1)
				जारी;

			phy_node = of_parse_phandle(mac_np, "phy-handle", 0);
			अगर (!phy_node)
				जारी;

			अगर (phy_node->parent == priv->dev->of_node->parent) अणु
				ret = of_get_phy_mode(mac_np, &पूर्णांकerface);
				अगर (ret && ret != -ENODEV) अणु
					of_node_put(mac_np);
					वापस ret;
				पूर्ण
				id = of_mdio_parse_addr(ds->dev, phy_node);
				अगर (id == 0)
					priv->p5_पूर्णांकf_sel = P5_INTF_SEL_PHY_P0;
				अगर (id == 4)
					priv->p5_पूर्णांकf_sel = P5_INTF_SEL_PHY_P4;
			पूर्ण
			of_node_put(mac_np);
			of_node_put(phy_node);
			अवरोध;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
	अगर (of_property_पढ़ो_bool(priv->dev->of_node, "gpio-controller")) अणु
		ret = mt7530_setup_gpio(priv);
		अगर (ret)
			वापस ret;
	पूर्ण
#पूर्ण_अगर /* CONFIG_GPIOLIB */

	mt7530_setup_port5(ds, पूर्णांकerface);

	/* Flush the FDB table */
	ret = mt7530_fdb_cmd(priv, MT7530_FDB_FLUSH, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7531_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	काष्ठा mt7530_dummy_poll p;
	u32 val, id;
	पूर्णांक ret, i;

	/* Reset whole chip through gpio pin or memory-mapped रेजिस्टरs क्रम
	 * dअगरferent type of hardware
	 */
	अगर (priv->mcm) अणु
		reset_control_निश्चित(priv->rstc);
		usleep_range(1000, 1100);
		reset_control_deनिश्चित(priv->rstc);
	पूर्ण अन्यथा अणु
		gpiod_set_value_cansleep(priv->reset, 0);
		usleep_range(1000, 1100);
		gpiod_set_value_cansleep(priv->reset, 1);
	पूर्ण

	/* Waiting क्रम MT7530 got to stable */
	INIT_MT7530_DUMMY_POLL(&p, priv, MT7530_HWTRAP);
	ret = पढ़ोx_poll_समयout(_mt7530_पढ़ो, &p, val, val != 0,
				 20, 1000000);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "reset timeout\n");
		वापस ret;
	पूर्ण

	id = mt7530_पढ़ो(priv, MT7531_CREV);
	id >>= CHIP_NAME_SHIFT;

	अगर (id != MT7531_ID) अणु
		dev_err(priv->dev, "chip %x can't be supported\n", id);
		वापस -ENODEV;
	पूर्ण

	/* Reset the चयन through पूर्णांकernal reset */
	mt7530_ग_लिखो(priv, MT7530_SYS_CTRL,
		     SYS_CTRL_PHY_RST | SYS_CTRL_SW_RST |
		     SYS_CTRL_REG_RST);

	अगर (mt7531_dual_sgmii_supported(priv)) अणु
		priv->p5_पूर्णांकf_sel = P5_INTF_SEL_GMAC5_SGMII;

		/* Let ds->slave_mii_bus be able to access बाह्यal phy. */
		mt7530_rmw(priv, MT7531_GPIO_MODE1, MT7531_GPIO11_RG_RXD2_MASK,
			   MT7531_EXT_P_MDC_11);
		mt7530_rmw(priv, MT7531_GPIO_MODE1, MT7531_GPIO12_RG_RXD3_MASK,
			   MT7531_EXT_P_MDIO_12);
	पूर्ण अन्यथा अणु
		priv->p5_पूर्णांकf_sel = P5_INTF_SEL_GMAC5;
	पूर्ण
	dev_dbg(ds->dev, "P5 support %s interface\n",
		p5_पूर्णांकf_modes(priv->p5_पूर्णांकf_sel));

	mt7530_rmw(priv, MT7531_GPIO_MODE0, MT7531_GPIO0_MASK,
		   MT7531_GPIO0_INTERRUPT);

	/* Let phylink decide the पूर्णांकerface later. */
	priv->p5_पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	priv->p6_पूर्णांकerface = PHY_INTERFACE_MODE_NA;

	/* Enable PHY core PLL, since phy_device has not yet been created
	 * provided क्रम phy_[पढ़ो,ग_लिखो]_mmd_indirect is called, we provide
	 * our own mt7531_ind_mmd_phy_[पढ़ो,ग_लिखो] to complete this
	 * function.
	 */
	val = mt7531_ind_c45_phy_पढ़ो(priv, MT753X_CTRL_PHY_ADDR,
				      MDIO_MMD_VEND2, CORE_PLL_GROUP4);
	val |= MT7531_PHY_PLL_BYPASS_MODE;
	val &= ~MT7531_PHY_PLL_OFF;
	mt7531_ind_c45_phy_ग_लिखो(priv, MT753X_CTRL_PHY_ADDR, MDIO_MMD_VEND2,
				 CORE_PLL_GROUP4, val);

	/* BPDU to CPU port */
	mt7530_rmw(priv, MT7531_CFC, MT7531_CPU_PMAP_MASK,
		   BIT(MT7530_CPU_PORT));
	mt7530_rmw(priv, MT753X_BPC, MT753X_BPDU_PORT_FW_MASK,
		   MT753X_BPDU_CPU_ONLY);

	/* Enable and reset MIB counters */
	mt7530_mib_reset(ds);

	क्रम (i = 0; i < MT7530_NUM_PORTS; i++) अणु
		/* Disable क्रमwarding by शेष on all ports */
		mt7530_rmw(priv, MT7530_PCR_P(i), PCR_MATRIX_MASK,
			   PCR_MATRIX_CLR);

		mt7530_set(priv, MT7531_DBG_CNT(i), MT7531_DIS_CLR);

		अगर (dsa_is_cpu_port(ds, i)) अणु
			ret = mt753x_cpu_port_enable(ds, i);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			mt7530_port_disable(ds, i);

			/* Disable learning by शेष on all user ports */
			mt7530_set(priv, MT7530_PSC_P(i), SA_DIS);
		पूर्ण

		/* Enable consistent egress tag */
		mt7530_rmw(priv, MT7530_PVC_P(i), PVC_EG_TAG_MASK,
			   PVC_EG_TAG(MT7530_VLAN_EG_CONSISTENT));
	पूर्ण

	ds->mtu_enक्रमcement_ingress = true;

	/* Flush the FDB table */
	ret = mt7530_fdb_cmd(priv, MT7530_FDB_FLUSH, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल bool
mt7530_phy_mode_supported(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	चयन (port) अणु
	हाल 0 ... 4: /* Internal phy */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII)
			वापस false;
		अवरोध;
	हाल 5: /* 2nd cpu port with phy of port 0 or 4 / बाह्यal phy */
		अगर (!phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface) &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_MII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII)
			वापस false;
		अवरोध;
	हाल 6: /* 1st cpu port */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII &&
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_TRGMII)
			वापस false;
		अवरोध;
	शेष:
		dev_err(priv->dev, "%s: unsupported port: %i\n", __func__,
			port);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool mt7531_is_rgmii_port(काष्ठा mt7530_priv *priv, u32 port)
अणु
	वापस (port == 5) && (priv->p5_पूर्णांकf_sel != P5_INTF_SEL_GMAC5_SGMII);
पूर्ण

अटल bool
mt7531_phy_mode_supported(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	चयन (port) अणु
	हाल 0 ... 4: /* Internal phy */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII)
			वापस false;
		अवरोध;
	हाल 5: /* 2nd cpu port supports either rgmii or sgmii/8023z */
		अगर (mt7531_is_rgmii_port(priv, port))
			वापस phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface);
		fallthrough;
	हाल 6: /* 1st cpu port supports sgmii/8023z only */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
		    !phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface))
			वापस false;
		अवरोध;
	शेष:
		dev_err(priv->dev, "%s: unsupported port: %i\n", __func__,
			port);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool
mt753x_phy_mode_supported(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस priv->info->phy_mode_supported(ds, port, state);
पूर्ण

अटल पूर्णांक
mt753x_pad_setup(काष्ठा dsa_चयन *ds, स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस priv->info->pad_setup(ds, state->पूर्णांकerface);
पूर्ण

अटल पूर्णांक
mt7530_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
		  phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	/* Only need to setup port5. */
	अगर (port != 5)
		वापस 0;

	mt7530_setup_port5(priv->ds, पूर्णांकerface);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7531_rgmii_setup(काष्ठा mt7530_priv *priv, u32 port,
			      phy_पूर्णांकerface_t पूर्णांकerface,
			      काष्ठा phy_device *phydev)
अणु
	u32 val;

	अगर (!mt7531_is_rgmii_port(priv, port)) अणु
		dev_err(priv->dev, "RGMII mode is not available for port %d\n",
			port);
		वापस -EINVAL;
	पूर्ण

	val = mt7530_पढ़ो(priv, MT7531_CLKGEN_CTRL);
	val |= GP_CLK_EN;
	val &= ~GP_MODE_MASK;
	val |= GP_MODE(MT7531_GP_MODE_RGMII);
	val &= ~CLK_SKEW_IN_MASK;
	val |= CLK_SKEW_IN(MT7531_CLK_SKEW_NO_CHG);
	val &= ~CLK_SKEW_OUT_MASK;
	val |= CLK_SKEW_OUT(MT7531_CLK_SKEW_NO_CHG);
	val |= TXCLK_NO_REVERSE | RXCLK_NO_DELAY;

	/* Do not adjust rgmii delay when venकरोr phy driver presents. */
	अगर (!phydev || phy_driver_is_genphy(phydev)) अणु
		val &= ~(TXCLK_NO_REVERSE | RXCLK_NO_DELAY);
		चयन (पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_RGMII:
			val |= TXCLK_NO_REVERSE;
			val |= RXCLK_NO_DELAY;
			अवरोध;
		हाल PHY_INTERFACE_MODE_RGMII_RXID:
			val |= TXCLK_NO_REVERSE;
			अवरोध;
		हाल PHY_INTERFACE_MODE_RGMII_TXID:
			val |= RXCLK_NO_DELAY;
			अवरोध;
		हाल PHY_INTERFACE_MODE_RGMII_ID:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	mt7530_ग_लिखो(priv, MT7531_CLKGEN_CTRL, val);

	वापस 0;
पूर्ण

अटल व्योम mt7531_sgmii_validate(काष्ठा mt7530_priv *priv, पूर्णांक port,
				  अचिन्हित दीर्घ *supported)
अणु
	/* Port5 supports ethier RGMII or SGMII.
	 * Port6 supports SGMII only.
	 */
	चयन (port) अणु
	हाल 5:
		अगर (mt7531_is_rgmii_port(priv, port))
			अवरोध;
		fallthrough;
	हाल 6:
		phylink_set(supported, 1000baseX_Full);
		phylink_set(supported, 2500baseX_Full);
		phylink_set(supported, 2500baseT_Full);
	पूर्ण
पूर्ण

अटल व्योम
mt7531_sgmii_link_up_क्रमce(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
			   पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	अचिन्हित पूर्णांक val;

	/* For adjusting speed and duplex of SGMII क्रमce mode. */
	अगर (पूर्णांकerface != PHY_INTERFACE_MODE_SGMII ||
	    phylink_स्वतःneg_inband(mode))
		वापस;

	/* SGMII क्रमce mode setting */
	val = mt7530_पढ़ो(priv, MT7531_SGMII_MODE(port));
	val &= ~MT7531_SGMII_IF_MODE_MASK;

	चयन (speed) अणु
	हाल SPEED_10:
		val |= MT7531_SGMII_FORCE_SPEED_10;
		अवरोध;
	हाल SPEED_100:
		val |= MT7531_SGMII_FORCE_SPEED_100;
		अवरोध;
	हाल SPEED_1000:
		val |= MT7531_SGMII_FORCE_SPEED_1000;
		अवरोध;
	पूर्ण

	/* MT7531 SGMII 1G क्रमce mode can only work in full duplex mode,
	 * no matter MT7531_SGMII_FORCE_HALF_DUPLEX is set or not.
	 */
	अगर ((speed == SPEED_10 || speed == SPEED_100) &&
	    duplex != DUPLEX_FULL)
		val |= MT7531_SGMII_FORCE_HALF_DUPLEX;

	mt7530_ग_लिखो(priv, MT7531_SGMII_MODE(port), val);
पूर्ण

अटल bool mt753x_is_mac_port(u32 port)
अणु
	वापस (port == 5 || port == 6);
पूर्ण

अटल पूर्णांक mt7531_sgmii_setup_mode_क्रमce(काष्ठा mt7530_priv *priv, u32 port,
					 phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	u32 val;

	अगर (!mt753x_is_mac_port(port))
		वापस -EINVAL;

	mt7530_set(priv, MT7531_QPHY_PWR_STATE_CTRL(port),
		   MT7531_SGMII_PHYA_PWD);

	val = mt7530_पढ़ो(priv, MT7531_PHYA_CTRL_SIGNAL3(port));
	val &= ~MT7531_RG_TPHY_SPEED_MASK;
	/* Setup 2.5 बार faster घड़ी क्रम 2.5Gbps data speeds with 10B/8B
	 * encoding.
	 */
	val |= (पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX) ?
		MT7531_RG_TPHY_SPEED_3_125G : MT7531_RG_TPHY_SPEED_1_25G;
	mt7530_ग_लिखो(priv, MT7531_PHYA_CTRL_SIGNAL3(port), val);

	mt7530_clear(priv, MT7531_PCS_CONTROL_1(port), MT7531_SGMII_AN_ENABLE);

	/* MT7531 SGMII 1G and 2.5G क्रमce mode can only work in full duplex
	 * mode, no matter MT7531_SGMII_FORCE_HALF_DUPLEX is set or not.
	 */
	mt7530_rmw(priv, MT7531_SGMII_MODE(port),
		   MT7531_SGMII_IF_MODE_MASK | MT7531_SGMII_REMOTE_FAULT_DIS,
		   MT7531_SGMII_FORCE_SPEED_1000);

	mt7530_ग_लिखो(priv, MT7531_QPHY_PWR_STATE_CTRL(port), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7531_sgmii_setup_mode_an(काष्ठा mt7530_priv *priv, पूर्णांक port,
				      phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	अगर (!mt753x_is_mac_port(port))
		वापस -EINVAL;

	mt7530_set(priv, MT7531_QPHY_PWR_STATE_CTRL(port),
		   MT7531_SGMII_PHYA_PWD);

	mt7530_rmw(priv, MT7531_PHYA_CTRL_SIGNAL3(port),
		   MT7531_RG_TPHY_SPEED_MASK, MT7531_RG_TPHY_SPEED_1_25G);

	mt7530_set(priv, MT7531_SGMII_MODE(port),
		   MT7531_SGMII_REMOTE_FAULT_DIS |
		   MT7531_SGMII_SPEED_DUPLEX_AN);

	mt7530_rmw(priv, MT7531_PCS_SPEED_ABILITY(port),
		   MT7531_SGMII_TX_CONFIG_MASK, 1);

	mt7530_set(priv, MT7531_PCS_CONTROL_1(port), MT7531_SGMII_AN_ENABLE);

	mt7530_set(priv, MT7531_PCS_CONTROL_1(port), MT7531_SGMII_AN_RESTART);

	mt7530_ग_लिखो(priv, MT7531_QPHY_PWR_STATE_CTRL(port), 0);

	वापस 0;
पूर्ण

अटल व्योम mt7531_sgmii_restart_an(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 val;

	/* Only restart AN when AN is enabled */
	val = mt7530_पढ़ो(priv, MT7531_PCS_CONTROL_1(port));
	अगर (val & MT7531_SGMII_AN_ENABLE) अणु
		val |= MT7531_SGMII_AN_RESTART;
		mt7530_ग_लिखो(priv, MT7531_PCS_CONTROL_1(port), val);
	पूर्ण
पूर्ण

अटल पूर्णांक
mt7531_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
		  phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	काष्ठा phy_device *phydev;
	काष्ठा dsa_port *dp;

	अगर (!mt753x_is_mac_port(port)) अणु
		dev_err(priv->dev, "port %d is not a MAC port\n", port);
		वापस -EINVAL;
	पूर्ण

	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		dp = dsa_to_port(ds, port);
		phydev = dp->slave->phydev;
		वापस mt7531_rgmii_setup(priv, port, पूर्णांकerface, phydev);
	हाल PHY_INTERFACE_MODE_SGMII:
		वापस mt7531_sgmii_setup_mode_an(priv, port, पूर्णांकerface);
	हाल PHY_INTERFACE_MODE_NA:
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		अगर (phylink_स्वतःneg_inband(mode))
			वापस -EINVAL;

		वापस mt7531_sgmii_setup_mode_क्रमce(priv, port, पूर्णांकerface);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
mt753x_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
		  स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस priv->info->mac_port_config(ds, port, mode, state->पूर्णांकerface);
पूर्ण

अटल व्योम
mt753x_phylink_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
			  स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 mcr_cur, mcr_new;

	अगर (!mt753x_phy_mode_supported(ds, port, state))
		जाओ unsupported;

	चयन (port) अणु
	हाल 0 ... 4: /* Internal phy */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII)
			जाओ unsupported;
		अवरोध;
	हाल 5: /* 2nd cpu port with phy of port 0 or 4 / बाह्यal phy */
		अगर (priv->p5_पूर्णांकerface == state->पूर्णांकerface)
			अवरोध;

		अगर (mt753x_mac_config(ds, port, mode, state) < 0)
			जाओ unsupported;

		अगर (priv->p5_पूर्णांकf_sel != P5_DISABLED)
			priv->p5_पूर्णांकerface = state->पूर्णांकerface;
		अवरोध;
	हाल 6: /* 1st cpu port */
		अगर (priv->p6_पूर्णांकerface == state->पूर्णांकerface)
			अवरोध;

		mt753x_pad_setup(ds, state);

		अगर (mt753x_mac_config(ds, port, mode, state) < 0)
			जाओ unsupported;

		priv->p6_पूर्णांकerface = state->पूर्णांकerface;
		अवरोध;
	शेष:
unsupported:
		dev_err(ds->dev, "%s: unsupported %s port: %i\n",
			__func__, phy_modes(state->पूर्णांकerface), port);
		वापस;
	पूर्ण

	अगर (phylink_स्वतःneg_inband(mode) &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII) अणु
		dev_err(ds->dev, "%s: in-band negotiation unsupported\n",
			__func__);
		वापस;
	पूर्ण

	mcr_cur = mt7530_पढ़ो(priv, MT7530_PMCR_P(port));
	mcr_new = mcr_cur;
	mcr_new &= ~PMCR_LINK_SETTINGS_MASK;
	mcr_new |= PMCR_IFG_XMIT(1) | PMCR_MAC_MODE | PMCR_BACKOFF_EN |
		   PMCR_BACKPR_EN | PMCR_FORCE_MODE_ID(priv->id);

	/* Are we connected to बाह्यal phy */
	अगर (port == 5 && dsa_is_user_port(ds, 5))
		mcr_new |= PMCR_EXT_PHY;

	अगर (mcr_new != mcr_cur)
		mt7530_ग_लिखो(priv, MT7530_PMCR_P(port), mcr_new);
पूर्ण

अटल व्योम
mt753x_phylink_mac_an_restart(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	अगर (!priv->info->mac_pcs_an_restart)
		वापस;

	priv->info->mac_pcs_an_restart(ds, port);
पूर्ण

अटल व्योम mt753x_phylink_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 अचिन्हित पूर्णांक mode,
					 phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	mt7530_clear(priv, MT7530_PMCR_P(port), PMCR_LINK_SETTINGS_MASK);
पूर्ण

अटल व्योम mt753x_mac_pcs_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
				   पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	अगर (!priv->info->mac_pcs_link_up)
		वापस;

	priv->info->mac_pcs_link_up(ds, port, mode, पूर्णांकerface, speed, duplex);
पूर्ण

अटल व्योम mt753x_phylink_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       अचिन्हित पूर्णांक mode,
				       phy_पूर्णांकerface_t पूर्णांकerface,
				       काष्ठा phy_device *phydev,
				       पूर्णांक speed, पूर्णांक duplex,
				       bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 mcr;

	mt753x_mac_pcs_link_up(ds, port, mode, पूर्णांकerface, speed, duplex);

	mcr = PMCR_RX_EN | PMCR_TX_EN | PMCR_FORCE_LNK;

	/* MT753x MAC works in 1G full duplex mode क्रम all up-घड़ीed
	 * variants.
	 */
	अगर (पूर्णांकerface == PHY_INTERFACE_MODE_TRGMII ||
	    (phy_पूर्णांकerface_mode_is_8023z(पूर्णांकerface))) अणु
		speed = SPEED_1000;
		duplex = DUPLEX_FULL;
	पूर्ण

	चयन (speed) अणु
	हाल SPEED_1000:
		mcr |= PMCR_FORCE_SPEED_1000;
		अवरोध;
	हाल SPEED_100:
		mcr |= PMCR_FORCE_SPEED_100;
		अवरोध;
	पूर्ण
	अगर (duplex == DUPLEX_FULL) अणु
		mcr |= PMCR_FORCE_FDX;
		अगर (tx_छोड़ो)
			mcr |= PMCR_TX_FC_EN;
		अगर (rx_छोड़ो)
			mcr |= PMCR_RX_FC_EN;
	पूर्ण

	अगर (mode == MLO_AN_PHY && phydev && phy_init_eee(phydev, 0) >= 0) अणु
		चयन (speed) अणु
		हाल SPEED_1000:
			mcr |= PMCR_FORCE_EEE1G;
			अवरोध;
		हाल SPEED_100:
			mcr |= PMCR_FORCE_EEE100;
			अवरोध;
		पूर्ण
	पूर्ण

	mt7530_set(priv, MT7530_PMCR_P(port), mcr);
पूर्ण

अटल पूर्णांक
mt7531_cpu_port_config(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	phy_पूर्णांकerface_t पूर्णांकerface;
	पूर्णांक speed;
	पूर्णांक ret;

	चयन (port) अणु
	हाल 5:
		अगर (mt7531_is_rgmii_port(priv, port))
			पूर्णांकerface = PHY_INTERFACE_MODE_RGMII;
		अन्यथा
			पूर्णांकerface = PHY_INTERFACE_MODE_2500BASEX;

		priv->p5_पूर्णांकerface = पूर्णांकerface;
		अवरोध;
	हाल 6:
		पूर्णांकerface = PHY_INTERFACE_MODE_2500BASEX;

		mt7531_pad_setup(ds, पूर्णांकerface);

		priv->p6_पूर्णांकerface = पूर्णांकerface;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX)
		speed = SPEED_2500;
	अन्यथा
		speed = SPEED_1000;

	ret = mt7531_mac_config(ds, port, MLO_AN_FIXED, पूर्णांकerface);
	अगर (ret)
		वापस ret;
	mt7530_ग_लिखो(priv, MT7530_PMCR_P(port),
		     PMCR_CPU_PORT_SETTING(priv->id));
	mt753x_phylink_mac_link_up(ds, port, MLO_AN_FIXED, पूर्णांकerface, शून्य,
				   speed, DUPLEX_FULL, true, true);

	वापस 0;
पूर्ण

अटल व्योम
mt7530_mac_port_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 अचिन्हित दीर्घ *supported)
अणु
	अगर (port == 5)
		phylink_set(supported, 1000baseX_Full);
पूर्ण

अटल व्योम mt7531_mac_port_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     अचिन्हित दीर्घ *supported)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	mt7531_sgmii_validate(priv, port, supported);
पूर्ण

अटल व्योम
mt753x_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
			अचिन्हित दीर्घ *supported,
			काष्ठा phylink_link_state *state)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा mt7530_priv *priv = ds->priv;

	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
	    !mt753x_phy_mode_supported(ds, port, state)) अणु
		linkmode_zero(supported);
		वापस;
	पूर्ण

	phylink_set_port_modes(mask);

	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_TRGMII ||
	    !phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)) अणु
		phylink_set(mask, 10baseT_Half);
		phylink_set(mask, 10baseT_Full);
		phylink_set(mask, 100baseT_Half);
		phylink_set(mask, 100baseT_Full);
		phylink_set(mask, Autoneg);
	पूर्ण

	/* This चयन only supports 1G full-duplex. */
	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_MII)
		phylink_set(mask, 1000baseT_Full);

	priv->info->mac_port_validate(ds, port, mask);

	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);

	linkmode_and(supported, supported, mask);
	linkmode_and(state->advertising, state->advertising, mask);

	/* We can only operate at 2500BaseX or 1000BaseX.  If requested
	 * to advertise both, only report advertising at 2500BaseX.
	 */
	phylink_helper_basex_speed(state);
पूर्ण

अटल पूर्णांक
mt7530_phylink_mac_link_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 pmsr;

	अगर (port < 0 || port >= MT7530_NUM_PORTS)
		वापस -EINVAL;

	pmsr = mt7530_पढ़ो(priv, MT7530_PMSR_P(port));

	state->link = (pmsr & PMSR_LINK);
	state->an_complete = state->link;
	state->duplex = !!(pmsr & PMSR_DPX);

	चयन (pmsr & PMSR_SPEED_MASK) अणु
	हाल PMSR_SPEED_10:
		state->speed = SPEED_10;
		अवरोध;
	हाल PMSR_SPEED_100:
		state->speed = SPEED_100;
		अवरोध;
	हाल PMSR_SPEED_1000:
		state->speed = SPEED_1000;
		अवरोध;
	शेष:
		state->speed = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	state->छोड़ो &= ~(MLO_PAUSE_RX | MLO_PAUSE_TX);
	अगर (pmsr & PMSR_RX_FC)
		state->छोड़ो |= MLO_PAUSE_RX;
	अगर (pmsr & PMSR_TX_FC)
		state->छोड़ो |= MLO_PAUSE_TX;

	वापस 1;
पूर्ण

अटल पूर्णांक
mt7531_sgmii_pcs_get_state_an(काष्ठा mt7530_priv *priv, पूर्णांक port,
			      काष्ठा phylink_link_state *state)
अणु
	u32 status, val;
	u16 config_reg;

	status = mt7530_पढ़ो(priv, MT7531_PCS_CONTROL_1(port));
	state->link = !!(status & MT7531_SGMII_LINK_STATUS);
	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII &&
	    (status & MT7531_SGMII_AN_ENABLE)) अणु
		val = mt7530_पढ़ो(priv, MT7531_PCS_SPEED_ABILITY(port));
		config_reg = val >> 16;

		चयन (config_reg & LPA_SGMII_SPD_MASK) अणु
		हाल LPA_SGMII_1000:
			state->speed = SPEED_1000;
			अवरोध;
		हाल LPA_SGMII_100:
			state->speed = SPEED_100;
			अवरोध;
		हाल LPA_SGMII_10:
			state->speed = SPEED_10;
			अवरोध;
		शेष:
			dev_err(priv->dev, "invalid sgmii PHY speed\n");
			state->link = false;
			वापस -EINVAL;
		पूर्ण

		अगर (config_reg & LPA_SGMII_FULL_DUPLEX)
			state->duplex = DUPLEX_FULL;
		अन्यथा
			state->duplex = DUPLEX_HALF;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7531_phylink_mac_link_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		वापस mt7531_sgmii_pcs_get_state_an(priv, port, state);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
mt753x_phylink_mac_link_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा phylink_link_state *state)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस priv->info->mac_port_get_state(ds, port, state);
पूर्ण

अटल पूर्णांक
mt753x_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस priv->info->sw_setup(ds);
पूर्ण

अटल पूर्णांक
mt753x_phy_पढ़ो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस priv->info->phy_पढ़ो(ds, port, regnum);
पूर्ण

अटल पूर्णांक
mt753x_phy_ग_लिखो(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum, u16 val)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;

	वापस priv->info->phy_ग_लिखो(ds, port, regnum, val);
पूर्ण

अटल पूर्णांक mt753x_get_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा ethtool_eee *e)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 eeecr = mt7530_पढ़ो(priv, MT7530_PMEEECR_P(port));

	e->tx_lpi_enabled = !(eeecr & LPI_MODE_EN);
	e->tx_lpi_समयr = GET_LPI_THRESH(eeecr);

	वापस 0;
पूर्ण

अटल पूर्णांक mt753x_set_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा ethtool_eee *e)
अणु
	काष्ठा mt7530_priv *priv = ds->priv;
	u32 set, mask = LPI_THRESH_MASK | LPI_MODE_EN;

	अगर (e->tx_lpi_समयr > 0xFFF)
		वापस -EINVAL;

	set = SET_LPI_THRESH(e->tx_lpi_समयr);
	अगर (!e->tx_lpi_enabled)
		/* Force LPI Mode without a delay */
		set |= LPI_MODE_EN;
	mt7530_rmw(priv, MT7530_PMEEECR_P(port), mask, set);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops mt7530_चयन_ops = अणु
	.get_tag_protocol	= mtk_get_tag_protocol,
	.setup			= mt753x_setup,
	.get_strings		= mt7530_get_strings,
	.phy_पढ़ो		= mt753x_phy_पढ़ो,
	.phy_ग_लिखो		= mt753x_phy_ग_लिखो,
	.get_ethtool_stats	= mt7530_get_ethtool_stats,
	.get_sset_count		= mt7530_get_sset_count,
	.set_ageing_समय	= mt7530_set_ageing_समय,
	.port_enable		= mt7530_port_enable,
	.port_disable		= mt7530_port_disable,
	.port_change_mtu	= mt7530_port_change_mtu,
	.port_max_mtu		= mt7530_port_max_mtu,
	.port_stp_state_set	= mt7530_stp_state_set,
	.port_pre_bridge_flags	= mt7530_port_pre_bridge_flags,
	.port_bridge_flags	= mt7530_port_bridge_flags,
	.port_set_mrouter	= mt7530_port_set_mrouter,
	.port_bridge_join	= mt7530_port_bridge_join,
	.port_bridge_leave	= mt7530_port_bridge_leave,
	.port_fdb_add		= mt7530_port_fdb_add,
	.port_fdb_del		= mt7530_port_fdb_del,
	.port_fdb_dump		= mt7530_port_fdb_dump,
	.port_mdb_add		= mt7530_port_mdb_add,
	.port_mdb_del		= mt7530_port_mdb_del,
	.port_vlan_filtering	= mt7530_port_vlan_filtering,
	.port_vlan_add		= mt7530_port_vlan_add,
	.port_vlan_del		= mt7530_port_vlan_del,
	.port_mirror_add	= mt753x_port_mirror_add,
	.port_mirror_del	= mt753x_port_mirror_del,
	.phylink_validate	= mt753x_phylink_validate,
	.phylink_mac_link_state	= mt753x_phylink_mac_link_state,
	.phylink_mac_config	= mt753x_phylink_mac_config,
	.phylink_mac_an_restart	= mt753x_phylink_mac_an_restart,
	.phylink_mac_link_करोwn	= mt753x_phylink_mac_link_करोwn,
	.phylink_mac_link_up	= mt753x_phylink_mac_link_up,
	.get_mac_eee		= mt753x_get_mac_eee,
	.set_mac_eee		= mt753x_set_mac_eee,
पूर्ण;

अटल स्थिर काष्ठा mt753x_info mt753x_table[] = अणु
	[ID_MT7621] = अणु
		.id = ID_MT7621,
		.sw_setup = mt7530_setup,
		.phy_पढ़ो = mt7530_phy_पढ़ो,
		.phy_ग_लिखो = mt7530_phy_ग_लिखो,
		.pad_setup = mt7530_pad_clk_setup,
		.phy_mode_supported = mt7530_phy_mode_supported,
		.mac_port_validate = mt7530_mac_port_validate,
		.mac_port_get_state = mt7530_phylink_mac_link_state,
		.mac_port_config = mt7530_mac_config,
	पूर्ण,
	[ID_MT7530] = अणु
		.id = ID_MT7530,
		.sw_setup = mt7530_setup,
		.phy_पढ़ो = mt7530_phy_पढ़ो,
		.phy_ग_लिखो = mt7530_phy_ग_लिखो,
		.pad_setup = mt7530_pad_clk_setup,
		.phy_mode_supported = mt7530_phy_mode_supported,
		.mac_port_validate = mt7530_mac_port_validate,
		.mac_port_get_state = mt7530_phylink_mac_link_state,
		.mac_port_config = mt7530_mac_config,
	पूर्ण,
	[ID_MT7531] = अणु
		.id = ID_MT7531,
		.sw_setup = mt7531_setup,
		.phy_पढ़ो = mt7531_ind_phy_पढ़ो,
		.phy_ग_लिखो = mt7531_ind_phy_ग_लिखो,
		.pad_setup = mt7531_pad_setup,
		.cpu_port_config = mt7531_cpu_port_config,
		.phy_mode_supported = mt7531_phy_mode_supported,
		.mac_port_validate = mt7531_mac_port_validate,
		.mac_port_get_state = mt7531_phylink_mac_link_state,
		.mac_port_config = mt7531_mac_config,
		.mac_pcs_an_restart = mt7531_sgmii_restart_an,
		.mac_pcs_link_up = mt7531_sgmii_link_up_क्रमce,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mt7530_of_match[] = अणु
	अणु .compatible = "mediatek,mt7621", .data = &mt753x_table[ID_MT7621], पूर्ण,
	अणु .compatible = "mediatek,mt7530", .data = &mt753x_table[ID_MT7530], पूर्ण,
	अणु .compatible = "mediatek,mt7531", .data = &mt753x_table[ID_MT7531], पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt7530_of_match);

अटल पूर्णांक
mt7530_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा mt7530_priv *priv;
	काष्ठा device_node *dn;

	dn = mdiodev->dev.of_node;

	priv = devm_kzalloc(&mdiodev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->ds = devm_kzalloc(&mdiodev->dev, माप(*priv->ds), GFP_KERNEL);
	अगर (!priv->ds)
		वापस -ENOMEM;

	priv->ds->dev = &mdiodev->dev;
	priv->ds->num_ports = DSA_MAX_PORTS;

	/* Use medatek,mcm property to distinguish hardware type that would
	 * casues a little bit dअगरferences on घातer-on sequence.
	 */
	priv->mcm = of_property_पढ़ो_bool(dn, "mediatek,mcm");
	अगर (priv->mcm) अणु
		dev_info(&mdiodev->dev, "MT7530 adapts as multi-chip module\n");

		priv->rstc = devm_reset_control_get(&mdiodev->dev, "mcm");
		अगर (IS_ERR(priv->rstc)) अणु
			dev_err(&mdiodev->dev, "Couldn't get our reset line\n");
			वापस PTR_ERR(priv->rstc);
		पूर्ण
	पूर्ण

	/* Get the hardware identअगरier from the devicetree node.
	 * We will need it क्रम some of the घड़ी and regulator setup.
	 */
	priv->info = of_device_get_match_data(&mdiodev->dev);
	अगर (!priv->info)
		वापस -EINVAL;

	/* Sanity check अगर these required device operations are filled
	 * properly.
	 */
	अगर (!priv->info->sw_setup || !priv->info->pad_setup ||
	    !priv->info->phy_पढ़ो || !priv->info->phy_ग_लिखो ||
	    !priv->info->phy_mode_supported ||
	    !priv->info->mac_port_validate ||
	    !priv->info->mac_port_get_state || !priv->info->mac_port_config)
		वापस -EINVAL;

	priv->id = priv->info->id;

	अगर (priv->id == ID_MT7530) अणु
		priv->core_pwr = devm_regulator_get(&mdiodev->dev, "core");
		अगर (IS_ERR(priv->core_pwr))
			वापस PTR_ERR(priv->core_pwr);

		priv->io_pwr = devm_regulator_get(&mdiodev->dev, "io");
		अगर (IS_ERR(priv->io_pwr))
			वापस PTR_ERR(priv->io_pwr);
	पूर्ण

	/* Not MCM that indicates चयन works as the remote standalone
	 * पूर्णांकegrated circuit so the GPIO pin would be used to complete
	 * the reset, otherwise memory-mapped रेजिस्टर accessing used
	 * through syscon provides in the हाल of MCM.
	 */
	अगर (!priv->mcm) अणु
		priv->reset = devm_gpiod_get_optional(&mdiodev->dev, "reset",
						      GPIOD_OUT_LOW);
		अगर (IS_ERR(priv->reset)) अणु
			dev_err(&mdiodev->dev, "Couldn't get our reset line\n");
			वापस PTR_ERR(priv->reset);
		पूर्ण
	पूर्ण

	priv->bus = mdiodev->bus;
	priv->dev = &mdiodev->dev;
	priv->ds->priv = priv;
	priv->ds->ops = &mt7530_चयन_ops;
	mutex_init(&priv->reg_mutex);
	dev_set_drvdata(&mdiodev->dev, priv);

	वापस dsa_रेजिस्टर_चयन(priv->ds);
पूर्ण

अटल व्योम
mt7530_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा mt7530_priv *priv = dev_get_drvdata(&mdiodev->dev);
	पूर्णांक ret = 0;

	ret = regulator_disable(priv->core_pwr);
	अगर (ret < 0)
		dev_err(priv->dev,
			"Failed to disable core power: %d\n", ret);

	ret = regulator_disable(priv->io_pwr);
	अगर (ret < 0)
		dev_err(priv->dev, "Failed to disable io pwr: %d\n",
			ret);

	dsa_unरेजिस्टर_चयन(priv->ds);
	mutex_destroy(&priv->reg_mutex);
पूर्ण

अटल काष्ठा mdio_driver mt7530_mdio_driver = अणु
	.probe  = mt7530_probe,
	.हटाओ = mt7530_हटाओ,
	.mdiodrv.driver = अणु
		.name = "mt7530",
		.of_match_table = mt7530_of_match,
	पूर्ण,
पूर्ण;

mdio_module_driver(mt7530_mdio_driver);

MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_DESCRIPTION("Driver for Mediatek MT7530 Switch");
MODULE_LICENSE("GPL");
