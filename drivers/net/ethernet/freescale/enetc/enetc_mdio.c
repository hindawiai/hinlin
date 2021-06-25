<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2019 NXP */

#समावेश <linux/fsl/enetc_mdपन.स>
#समावेश <linux/mdपन.स>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>

#समावेश "enetc_pf.h"

#घोषणा	ENETC_MDIO_CFG	0x0	/* MDIO configuration and status */
#घोषणा	ENETC_MDIO_CTL	0x4	/* MDIO control */
#घोषणा	ENETC_MDIO_DATA	0x8	/* MDIO data */
#घोषणा	ENETC_MDIO_ADDR	0xc	/* MDIO address */

#घोषणा MDIO_CFG_CLKDIV(x)	((((x) >> 1) & 0xff) << 8)
#घोषणा MDIO_CFG_BSY		BIT(0)
#घोषणा MDIO_CFG_RD_ER		BIT(1)
#घोषणा MDIO_CFG_HOLD(x)	(((x) << 2) & GENMASK(4, 2))
#घोषणा MDIO_CFG_ENC45		BIT(6)
 /* बाह्यal MDIO only - driven on neg MDC edge */
#घोषणा MDIO_CFG_NEG		BIT(23)

#घोषणा ENETC_EMDIO_CFG \
	(MDIO_CFG_HOLD(2) | \
	 MDIO_CFG_CLKDIV(258) | \
	 MDIO_CFG_NEG)

#घोषणा MDIO_CTL_DEV_ADDR(x)	((x) & 0x1f)
#घोषणा MDIO_CTL_PORT_ADDR(x)	(((x) & 0x1f) << 5)
#घोषणा MDIO_CTL_READ		BIT(15)

अटल अंतरभूत u32 enetc_mdio_rd(काष्ठा enetc_mdio_priv *mdio_priv, पूर्णांक off)
अणु
	वापस enetc_port_rd_mdio(mdio_priv->hw, mdio_priv->mdio_base + off);
पूर्ण

अटल अंतरभूत व्योम enetc_mdio_wr(काष्ठा enetc_mdio_priv *mdio_priv, पूर्णांक off,
				 u32 val)
अणु
	enetc_port_wr_mdio(mdio_priv->hw, mdio_priv->mdio_base + off, val);
पूर्ण

अटल bool enetc_mdio_is_busy(काष्ठा enetc_mdio_priv *mdio_priv)
अणु
	वापस enetc_mdio_rd(mdio_priv, ENETC_MDIO_CFG) & MDIO_CFG_BSY;
पूर्ण

अटल पूर्णांक enetc_mdio_रुको_complete(काष्ठा enetc_mdio_priv *mdio_priv)
अणु
	bool is_busy;

	वापस पढ़ोx_poll_समयout(enetc_mdio_is_busy, mdio_priv,
				  is_busy, !is_busy, 10, 10 * 1000);
पूर्ण

पूर्णांक enetc_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum, u16 value)
अणु
	काष्ठा enetc_mdio_priv *mdio_priv = bus->priv;
	u32 mdio_ctl, mdio_cfg;
	u16 dev_addr;
	पूर्णांक ret;

	mdio_cfg = ENETC_EMDIO_CFG;
	अगर (regnum & MII_ADDR_C45) अणु
		dev_addr = (regnum >> 16) & 0x1f;
		mdio_cfg |= MDIO_CFG_ENC45;
	पूर्ण अन्यथा अणु
		/* clause 22 (ie 1G) */
		dev_addr = regnum & 0x1f;
		mdio_cfg &= ~MDIO_CFG_ENC45;
	पूर्ण

	enetc_mdio_wr(mdio_priv, ENETC_MDIO_CFG, mdio_cfg);

	ret = enetc_mdio_रुको_complete(mdio_priv);
	अगर (ret)
		वापस ret;

	/* set port and dev addr */
	mdio_ctl = MDIO_CTL_PORT_ADDR(phy_id) | MDIO_CTL_DEV_ADDR(dev_addr);
	enetc_mdio_wr(mdio_priv, ENETC_MDIO_CTL, mdio_ctl);

	/* set the रेजिस्टर address */
	अगर (regnum & MII_ADDR_C45) अणु
		enetc_mdio_wr(mdio_priv, ENETC_MDIO_ADDR, regnum & 0xffff);

		ret = enetc_mdio_रुको_complete(mdio_priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* ग_लिखो the value */
	enetc_mdio_wr(mdio_priv, ENETC_MDIO_DATA, value);

	ret = enetc_mdio_रुको_complete(mdio_priv);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(enetc_mdio_ग_लिखो);

पूर्णांक enetc_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	काष्ठा enetc_mdio_priv *mdio_priv = bus->priv;
	u32 mdio_ctl, mdio_cfg;
	u16 dev_addr, value;
	पूर्णांक ret;

	mdio_cfg = ENETC_EMDIO_CFG;
	अगर (regnum & MII_ADDR_C45) अणु
		dev_addr = (regnum >> 16) & 0x1f;
		mdio_cfg |= MDIO_CFG_ENC45;
	पूर्ण अन्यथा अणु
		dev_addr = regnum & 0x1f;
		mdio_cfg &= ~MDIO_CFG_ENC45;
	पूर्ण

	enetc_mdio_wr(mdio_priv, ENETC_MDIO_CFG, mdio_cfg);

	ret = enetc_mdio_रुको_complete(mdio_priv);
	अगर (ret)
		वापस ret;

	/* set port and device addr */
	mdio_ctl = MDIO_CTL_PORT_ADDR(phy_id) | MDIO_CTL_DEV_ADDR(dev_addr);
	enetc_mdio_wr(mdio_priv, ENETC_MDIO_CTL, mdio_ctl);

	/* set the रेजिस्टर address */
	अगर (regnum & MII_ADDR_C45) अणु
		enetc_mdio_wr(mdio_priv, ENETC_MDIO_ADDR, regnum & 0xffff);

		ret = enetc_mdio_रुको_complete(mdio_priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* initiate the पढ़ो */
	enetc_mdio_wr(mdio_priv, ENETC_MDIO_CTL, mdio_ctl | MDIO_CTL_READ);

	ret = enetc_mdio_रुको_complete(mdio_priv);
	अगर (ret)
		वापस ret;

	/* वापस all Fs अगर nothing was there */
	अगर (enetc_mdio_rd(mdio_priv, ENETC_MDIO_CFG) & MDIO_CFG_RD_ER) अणु
		dev_dbg(&bus->dev,
			"Error while reading PHY%d reg at %d.%hhu\n",
			phy_id, dev_addr, regnum);
		वापस 0xffff;
	पूर्ण

	value = enetc_mdio_rd(mdio_priv, ENETC_MDIO_DATA) & 0xffff;

	वापस value;
पूर्ण
EXPORT_SYMBOL_GPL(enetc_mdio_पढ़ो);

काष्ठा enetc_hw *enetc_hw_alloc(काष्ठा device *dev, व्योम __iomem *port_regs)
अणु
	काष्ठा enetc_hw *hw;

	hw = devm_kzalloc(dev, माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस ERR_PTR(-ENOMEM);

	hw->port = port_regs;

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(enetc_hw_alloc);

/* Lock क्रम MDIO access errata on LS1028A */
DEFINE_RWLOCK(enetc_mdio_lock);
EXPORT_SYMBOL_GPL(enetc_mdio_lock);
