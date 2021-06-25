<शैली गुरु>
/*
 * Copyright (c) 2003-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश "common.h"
#समावेश "regs.h"
#समावेश "sge_defs.h"
#समावेश "firmware_exports.h"

अटल व्योम t3_port_पूर्णांकr_clear(काष्ठा adapter *adapter, पूर्णांक idx);

/**
 *	t3_रुको_op_करोne_val - रुको until an operation is completed
 *	@adapter: the adapter perक्रमming the operation
 *	@reg: the रेजिस्टर to check क्रम completion
 *	@mask: a single-bit field within @reg that indicates completion
 *	@polarity: the value of the field when the operation is completed
 *	@attempts: number of check iterations
 *	@delay: delay in usecs between iterations
 *	@valp: where to store the value of the रेजिस्टर at completion समय
 *
 *	Wait until an operation is completed by checking a bit in a रेजिस्टर
 *	up to @attempts बार.  If @valp is not शून्य the value of the रेजिस्टर
 *	at the समय it indicated completion is stored there.  Returns 0 अगर the
 *	operation completes and -EAGAIN otherwise.
 */

पूर्णांक t3_रुको_op_करोne_val(काष्ठा adapter *adapter, पूर्णांक reg, u32 mask,
			पूर्णांक polarity, पूर्णांक attempts, पूर्णांक delay, u32 *valp)
अणु
	जबतक (1) अणु
		u32 val = t3_पढ़ो_reg(adapter, reg);

		अगर (!!(val & mask) == polarity) अणु
			अगर (valp)
				*valp = val;
			वापस 0;
		पूर्ण
		अगर (--attempts == 0)
			वापस -EAGAIN;
		अगर (delay)
			udelay(delay);
	पूर्ण
पूर्ण

/**
 *	t3_ग_लिखो_regs - ग_लिखो a bunch of रेजिस्टरs
 *	@adapter: the adapter to program
 *	@p: an array of रेजिस्टर address/रेजिस्टर value pairs
 *	@n: the number of address/value pairs
 *	@offset: रेजिस्टर address offset
 *
 *	Takes an array of रेजिस्टर address/रेजिस्टर value pairs and ग_लिखोs each
 *	value to the corresponding रेजिस्टर.  Register addresses are adjusted
 *	by the supplied offset.
 */
व्योम t3_ग_लिखो_regs(काष्ठा adapter *adapter, स्थिर काष्ठा addr_val_pair *p,
		   पूर्णांक n, अचिन्हित पूर्णांक offset)
अणु
	जबतक (n--) अणु
		t3_ग_लिखो_reg(adapter, p->reg_addr + offset, p->val);
		p++;
	पूर्ण
पूर्ण

/**
 *	t3_set_reg_field - set a रेजिस्टर field to a value
 *	@adapter: the adapter to program
 *	@addr: the रेजिस्टर address
 *	@mask: specअगरies the portion of the रेजिस्टर to modअगरy
 *	@val: the new value क्रम the रेजिस्टर field
 *
 *	Sets a रेजिस्टर field specअगरied by the supplied mask to the
 *	given value.
 */
व्योम t3_set_reg_field(काष्ठा adapter *adapter, अचिन्हित पूर्णांक addr, u32 mask,
		      u32 val)
अणु
	u32 v = t3_पढ़ो_reg(adapter, addr) & ~mask;

	t3_ग_लिखो_reg(adapter, addr, v | val);
	t3_पढ़ो_reg(adapter, addr);	/* flush */
पूर्ण

/**
 *	t3_पढ़ो_indirect - पढ़ो indirectly addressed रेजिस्टरs
 *	@adap: the adapter
 *	@addr_reg: रेजिस्टर holding the indirect address
 *	@data_reg: रेजिस्टर holding the value of the indirect रेजिस्टर
 *	@vals: where the पढ़ो रेजिस्टर values are stored
 *	@start_idx: index of first indirect रेजिस्टर to पढ़ो
 *	@nregs: how many indirect रेजिस्टरs to पढ़ो
 *
 *	Reads रेजिस्टरs that are accessed indirectly through an address/data
 *	रेजिस्टर pair.
 */
अटल व्योम t3_पढ़ो_indirect(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr_reg,
			     अचिन्हित पूर्णांक data_reg, u32 *vals,
			     अचिन्हित पूर्णांक nregs, अचिन्हित पूर्णांक start_idx)
अणु
	जबतक (nregs--) अणु
		t3_ग_लिखो_reg(adap, addr_reg, start_idx);
		*vals++ = t3_पढ़ो_reg(adap, data_reg);
		start_idx++;
	पूर्ण
पूर्ण

/**
 *	t3_mc7_bd_पढ़ो - पढ़ो from MC7 through backकरोor accesses
 *	@mc7: identअगरies MC7 to पढ़ो from
 *	@start: index of first 64-bit word to पढ़ो
 *	@n: number of 64-bit words to पढ़ो
 *	@buf: where to store the पढ़ो result
 *
 *	Read n 64-bit words from MC7 starting at word start, using backकरोor
 *	accesses.
 */
पूर्णांक t3_mc7_bd_पढ़ो(काष्ठा mc7 *mc7, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक n,
		   u64 *buf)
अणु
	अटल स्थिर पूर्णांक shअगरt[] = अणु 0, 0, 16, 24 पूर्ण;
	अटल स्थिर पूर्णांक step[] = अणु 0, 32, 16, 8 पूर्ण;

	अचिन्हित पूर्णांक size64 = mc7->size / 8;	/* # of 64-bit words */
	काष्ठा adapter *adap = mc7->adapter;

	अगर (start >= size64 || start + n > size64)
		वापस -EINVAL;

	start *= (8 << mc7->width);
	जबतक (n--) अणु
		पूर्णांक i;
		u64 val64 = 0;

		क्रम (i = (1 << mc7->width) - 1; i >= 0; --i) अणु
			पूर्णांक attempts = 10;
			u32 val;

			t3_ग_लिखो_reg(adap, mc7->offset + A_MC7_BD_ADDR, start);
			t3_ग_लिखो_reg(adap, mc7->offset + A_MC7_BD_OP, 0);
			val = t3_पढ़ो_reg(adap, mc7->offset + A_MC7_BD_OP);
			जबतक ((val & F_BUSY) && attempts--)
				val = t3_पढ़ो_reg(adap,
						  mc7->offset + A_MC7_BD_OP);
			अगर (val & F_BUSY)
				वापस -EIO;

			val = t3_पढ़ो_reg(adap, mc7->offset + A_MC7_BD_DATA1);
			अगर (mc7->width == 0) अणु
				val64 = t3_पढ़ो_reg(adap,
						    mc7->offset +
						    A_MC7_BD_DATA0);
				val64 |= (u64) val << 32;
			पूर्ण अन्यथा अणु
				अगर (mc7->width > 1)
					val >>= shअगरt[mc7->width];
				val64 |= (u64) val << (step[mc7->width] * i);
			पूर्ण
			start += 8;
		पूर्ण
		*buf++ = val64;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Initialize MI1.
 */
अटल व्योम mi1_init(काष्ठा adapter *adap, स्थिर काष्ठा adapter_info *ai)
अणु
	u32 clkभाग = adap->params.vpd.cclk / (2 * adap->params.vpd.mdc) - 1;
	u32 val = F_PREEN | V_CLKDIV(clkभाग);

	t3_ग_लिखो_reg(adap, A_MI1_CFG, val);
पूर्ण

#घोषणा MDIO_ATTEMPTS 20

/*
 * MI1 पढ़ो/ग_लिखो operations क्रम clause 22 PHYs.
 */
अटल पूर्णांक t3_mi1_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
		       u16 reg_addr)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;
	u32 addr = V_REGADDR(reg_addr) | V_PHYADDR(phy_addr);

	mutex_lock(&adapter->mdio_lock);
	t3_set_reg_field(adapter, A_MI1_CFG, V_ST(M_ST), V_ST(1));
	t3_ग_लिखो_reg(adapter, A_MI1_ADDR, addr);
	t3_ग_लिखो_reg(adapter, A_MI1_OP, V_MDI_OP(2));
	ret = t3_रुको_op_करोne(adapter, A_MI1_OP, F_BUSY, 0, MDIO_ATTEMPTS, 10);
	अगर (!ret)
		ret = t3_पढ़ो_reg(adapter, A_MI1_DATA);
	mutex_unlock(&adapter->mdio_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक t3_mi1_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
			u16 reg_addr, u16 val)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;
	u32 addr = V_REGADDR(reg_addr) | V_PHYADDR(phy_addr);

	mutex_lock(&adapter->mdio_lock);
	t3_set_reg_field(adapter, A_MI1_CFG, V_ST(M_ST), V_ST(1));
	t3_ग_लिखो_reg(adapter, A_MI1_ADDR, addr);
	t3_ग_लिखो_reg(adapter, A_MI1_DATA, val);
	t3_ग_लिखो_reg(adapter, A_MI1_OP, V_MDI_OP(1));
	ret = t3_रुको_op_करोne(adapter, A_MI1_OP, F_BUSY, 0, MDIO_ATTEMPTS, 10);
	mutex_unlock(&adapter->mdio_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mdio_ops mi1_mdio_ops = अणु
	.पढ़ो = t3_mi1_पढ़ो,
	.ग_लिखो = t3_mi1_ग_लिखो,
	.mode_support = MDIO_SUPPORTS_C22
पूर्ण;

/*
 * Perक्रमms the address cycle क्रम clause 45 PHYs.
 * Must be called with the MDIO_LOCK held.
 */
अटल पूर्णांक mi1_wr_addr(काष्ठा adapter *adapter, पूर्णांक phy_addr, पूर्णांक mmd_addr,
		       पूर्णांक reg_addr)
अणु
	u32 addr = V_REGADDR(mmd_addr) | V_PHYADDR(phy_addr);

	t3_set_reg_field(adapter, A_MI1_CFG, V_ST(M_ST), 0);
	t3_ग_लिखो_reg(adapter, A_MI1_ADDR, addr);
	t3_ग_लिखो_reg(adapter, A_MI1_DATA, reg_addr);
	t3_ग_लिखो_reg(adapter, A_MI1_OP, V_MDI_OP(0));
	वापस t3_रुको_op_करोne(adapter, A_MI1_OP, F_BUSY, 0,
			       MDIO_ATTEMPTS, 10);
पूर्ण

/*
 * MI1 पढ़ो/ग_लिखो operations क्रम indirect-addressed PHYs.
 */
अटल पूर्णांक mi1_ext_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
			u16 reg_addr)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;

	mutex_lock(&adapter->mdio_lock);
	ret = mi1_wr_addr(adapter, phy_addr, mmd_addr, reg_addr);
	अगर (!ret) अणु
		t3_ग_लिखो_reg(adapter, A_MI1_OP, V_MDI_OP(3));
		ret = t3_रुको_op_करोne(adapter, A_MI1_OP, F_BUSY, 0,
				      MDIO_ATTEMPTS, 10);
		अगर (!ret)
			ret = t3_पढ़ो_reg(adapter, A_MI1_DATA);
	पूर्ण
	mutex_unlock(&adapter->mdio_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mi1_ext_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक mmd_addr,
			 u16 reg_addr, u16 val)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;

	mutex_lock(&adapter->mdio_lock);
	ret = mi1_wr_addr(adapter, phy_addr, mmd_addr, reg_addr);
	अगर (!ret) अणु
		t3_ग_लिखो_reg(adapter, A_MI1_DATA, val);
		t3_ग_लिखो_reg(adapter, A_MI1_OP, V_MDI_OP(1));
		ret = t3_रुको_op_करोne(adapter, A_MI1_OP, F_BUSY, 0,
				      MDIO_ATTEMPTS, 10);
	पूर्ण
	mutex_unlock(&adapter->mdio_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mdio_ops mi1_mdio_ext_ops = अणु
	.पढ़ो = mi1_ext_पढ़ो,
	.ग_लिखो = mi1_ext_ग_लिखो,
	.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22
पूर्ण;

/**
 *	t3_mdio_change_bits - modअगरy the value of a PHY रेजिस्टर
 *	@phy: the PHY to operate on
 *	@mmd: the device address
 *	@reg: the रेजिस्टर address
 *	@clear: what part of the रेजिस्टर value to mask off
 *	@set: what part of the रेजिस्टर value to set
 *
 *	Changes the value of a PHY रेजिस्टर by applying a mask to its current
 *	value and ORing the result with a new value.
 */
पूर्णांक t3_mdio_change_bits(काष्ठा cphy *phy, पूर्णांक mmd, पूर्णांक reg, अचिन्हित पूर्णांक clear,
			अचिन्हित पूर्णांक set)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = t3_mdio_पढ़ो(phy, mmd, reg, &val);
	अगर (!ret) अणु
		val &= ~clear;
		ret = t3_mdio_ग_लिखो(phy, mmd, reg, val | set);
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	t3_phy_reset - reset a PHY block
 *	@phy: the PHY to operate on
 *	@mmd: the device address of the PHY block to reset
 *	@रुको: how दीर्घ to रुको क्रम the reset to complete in 1ms increments
 *
 *	Resets a PHY block and optionally रुकोs क्रम the reset to complete.
 *	@mmd should be 0 क्रम 10/100/1000 PHYs and the device address to reset
 *	क्रम 10G PHYs.
 */
पूर्णांक t3_phy_reset(काष्ठा cphy *phy, पूर्णांक mmd, पूर्णांक रुको)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक ctl;

	err = t3_mdio_change_bits(phy, mmd, MDIO_CTRL1, MDIO_CTRL1_LPOWER,
				  MDIO_CTRL1_RESET);
	अगर (err || !रुको)
		वापस err;

	करो अणु
		err = t3_mdio_पढ़ो(phy, mmd, MDIO_CTRL1, &ctl);
		अगर (err)
			वापस err;
		ctl &= MDIO_CTRL1_RESET;
		अगर (ctl)
			msleep(1);
	पूर्ण जबतक (ctl && --रुको);

	वापस ctl ? -1 : 0;
पूर्ण

/**
 *	t3_phy_advertise - set the PHY advertisement रेजिस्टरs क्रम स्वतःneg
 *	@phy: the PHY to operate on
 *	@advert: biपंचांगap of capabilities the PHY should advertise
 *
 *	Sets a 10/100/1000 PHY's advertisement रेजिस्टरs to advertise the
 *	requested capabilities.
 */
पूर्णांक t3_phy_advertise(काष्ठा cphy *phy, अचिन्हित पूर्णांक advert)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक val = 0;

	err = t3_mdio_पढ़ो(phy, MDIO_DEVAD_NONE, MII_CTRL1000, &val);
	अगर (err)
		वापस err;

	val &= ~(ADVERTISE_1000HALF | ADVERTISE_1000FULL);
	अगर (advert & ADVERTISED_1000baseT_Half)
		val |= ADVERTISE_1000HALF;
	अगर (advert & ADVERTISED_1000baseT_Full)
		val |= ADVERTISE_1000FULL;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, MII_CTRL1000, val);
	अगर (err)
		वापस err;

	val = 1;
	अगर (advert & ADVERTISED_10baseT_Half)
		val |= ADVERTISE_10HALF;
	अगर (advert & ADVERTISED_10baseT_Full)
		val |= ADVERTISE_10FULL;
	अगर (advert & ADVERTISED_100baseT_Half)
		val |= ADVERTISE_100HALF;
	अगर (advert & ADVERTISED_100baseT_Full)
		val |= ADVERTISE_100FULL;
	अगर (advert & ADVERTISED_Pause)
		val |= ADVERTISE_PAUSE_CAP;
	अगर (advert & ADVERTISED_Asym_Pause)
		val |= ADVERTISE_PAUSE_ASYM;
	वापस t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, MII_ADVERTISE, val);
पूर्ण

/**
 *	t3_phy_advertise_fiber - set fiber PHY advertisement रेजिस्टर
 *	@phy: the PHY to operate on
 *	@advert: biपंचांगap of capabilities the PHY should advertise
 *
 *	Sets a fiber PHY's advertisement रेजिस्टर to advertise the
 *	requested capabilities.
 */
पूर्णांक t3_phy_advertise_fiber(काष्ठा cphy *phy, अचिन्हित पूर्णांक advert)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (advert & ADVERTISED_1000baseT_Half)
		val |= ADVERTISE_1000XHALF;
	अगर (advert & ADVERTISED_1000baseT_Full)
		val |= ADVERTISE_1000XFULL;
	अगर (advert & ADVERTISED_Pause)
		val |= ADVERTISE_1000XPAUSE;
	अगर (advert & ADVERTISED_Asym_Pause)
		val |= ADVERTISE_1000XPSE_ASYM;
	वापस t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, MII_ADVERTISE, val);
पूर्ण

/**
 *	t3_set_phy_speed_duplex - क्रमce PHY speed and duplex
 *	@phy: the PHY to operate on
 *	@speed: requested PHY speed
 *	@duplex: requested PHY duplex
 *
 *	Force a 10/100/1000 PHY's speed and duplex.  This also disables
 *	स्वतः-negotiation except क्रम GigE, where स्वतः-negotiation is mandatory.
 */
पूर्णांक t3_set_phy_speed_duplex(काष्ठा cphy *phy, पूर्णांक speed, पूर्णांक duplex)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक ctl;

	err = t3_mdio_पढ़ो(phy, MDIO_DEVAD_NONE, MII_BMCR, &ctl);
	अगर (err)
		वापस err;

	अगर (speed >= 0) अणु
		ctl &= ~(BMCR_SPEED100 | BMCR_SPEED1000 | BMCR_ANENABLE);
		अगर (speed == SPEED_100)
			ctl |= BMCR_SPEED100;
		अन्यथा अगर (speed == SPEED_1000)
			ctl |= BMCR_SPEED1000;
	पूर्ण
	अगर (duplex >= 0) अणु
		ctl &= ~(BMCR_FULLDPLX | BMCR_ANENABLE);
		अगर (duplex == DUPLEX_FULL)
			ctl |= BMCR_FULLDPLX;
	पूर्ण
	अगर (ctl & BMCR_SPEED1000) /* स्वतः-negotiation required क्रम GigE */
		ctl |= BMCR_ANENABLE;
	वापस t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, MII_BMCR, ctl);
पूर्ण

पूर्णांक t3_phy_lasi_पूर्णांकr_enable(काष्ठा cphy *phy)
अणु
	वापस t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL,
			     MDIO_PMA_LASI_LSALARM);
पूर्ण

पूर्णांक t3_phy_lasi_पूर्णांकr_disable(काष्ठा cphy *phy)
अणु
	वापस t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL, 0);
पूर्ण

पूर्णांक t3_phy_lasi_पूर्णांकr_clear(काष्ठा cphy *phy)
अणु
	u32 val;

	वापस t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_STAT, &val);
पूर्ण

पूर्णांक t3_phy_lasi_पूर्णांकr_handler(काष्ठा cphy *phy)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_STAT,
			       &status);

	अगर (err)
		वापस err;
	वापस (status & MDIO_PMA_LASI_LSALARM) ? cphy_cause_link_change : 0;
पूर्ण

अटल स्थिर काष्ठा adapter_info t3_adap_info[] = अणु
	अणु1, 1, 0,
	 F_GPIO2_OEN | F_GPIO4_OEN |
	 F_GPIO2_OUT_VAL | F_GPIO4_OUT_VAL, अणु S_GPIO3, S_GPIO5 पूर्ण, 0,
	 &mi1_mdio_ops, "Chelsio PE9000"पूर्ण,
	अणु1, 1, 0,
	 F_GPIO2_OEN | F_GPIO4_OEN |
	 F_GPIO2_OUT_VAL | F_GPIO4_OUT_VAL, अणु S_GPIO3, S_GPIO5 पूर्ण, 0,
	 &mi1_mdio_ops, "Chelsio T302"पूर्ण,
	अणु1, 0, 0,
	 F_GPIO1_OEN | F_GPIO6_OEN | F_GPIO7_OEN | F_GPIO10_OEN |
	 F_GPIO11_OEN | F_GPIO1_OUT_VAL | F_GPIO6_OUT_VAL | F_GPIO10_OUT_VAL,
	 अणु 0 पूर्ण, SUPPORTED_10000baseT_Full | SUPPORTED_AUI,
	 &mi1_mdio_ext_ops, "Chelsio T310"पूर्ण,
	अणु1, 1, 0,
	 F_GPIO1_OEN | F_GPIO2_OEN | F_GPIO4_OEN | F_GPIO5_OEN | F_GPIO6_OEN |
	 F_GPIO7_OEN | F_GPIO10_OEN | F_GPIO11_OEN | F_GPIO1_OUT_VAL |
	 F_GPIO5_OUT_VAL | F_GPIO6_OUT_VAL | F_GPIO10_OUT_VAL,
	 अणु S_GPIO9, S_GPIO3 पूर्ण, SUPPORTED_10000baseT_Full | SUPPORTED_AUI,
	 &mi1_mdio_ext_ops, "Chelsio T320"पूर्ण,
	अणुपूर्ण,
	अणुपूर्ण,
	अणु1, 0, 0,
	 F_GPIO1_OEN | F_GPIO2_OEN | F_GPIO4_OEN | F_GPIO6_OEN | F_GPIO7_OEN |
	 F_GPIO10_OEN | F_GPIO1_OUT_VAL | F_GPIO6_OUT_VAL | F_GPIO10_OUT_VAL,
	 अणु S_GPIO9 पूर्ण, SUPPORTED_10000baseT_Full | SUPPORTED_AUI,
	 &mi1_mdio_ext_ops, "Chelsio T310" पूर्ण,
	अणु1, 0, 0,
	 F_GPIO1_OEN | F_GPIO6_OEN | F_GPIO7_OEN |
	 F_GPIO1_OUT_VAL | F_GPIO6_OUT_VAL,
	 अणु S_GPIO9 पूर्ण, SUPPORTED_10000baseT_Full | SUPPORTED_AUI,
	 &mi1_mdio_ext_ops, "Chelsio N320E-G2" पूर्ण,
पूर्ण;

/*
 * Return the adapter_info काष्ठाure with a given index.  Out-of-range indices
 * वापस शून्य.
 */
स्थिर काष्ठा adapter_info *t3_get_adapter_info(अचिन्हित पूर्णांक id)
अणु
	वापस id < ARRAY_SIZE(t3_adap_info) ? &t3_adap_info[id] : शून्य;
पूर्ण

काष्ठा port_type_info अणु
	पूर्णांक (*phy_prep)(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *ops);
पूर्ण;

अटल स्थिर काष्ठा port_type_info port_types[] = अणु
	अणु शून्य पूर्ण,
	अणु t3_ael1002_phy_prep पूर्ण,
	अणु t3_vsc8211_phy_prep पूर्ण,
	अणु शून्यपूर्ण,
	अणु t3_xaui_direct_phy_prep पूर्ण,
	अणु t3_ael2005_phy_prep पूर्ण,
	अणु t3_qt2045_phy_prep पूर्ण,
	अणु t3_ael1006_phy_prep पूर्ण,
	अणु शून्य पूर्ण,
	अणु t3_aq100x_phy_prep पूर्ण,
	अणु t3_ael2020_phy_prep पूर्ण,
पूर्ण;

#घोषणा VPD_ENTRY(name, len) \
	u8 name##_kword[2]; u8 name##_len; u8 name##_data[len]

/*
 * Partial EEPROM Vital Product Data काष्ठाure.  Includes only the ID and
 * VPD-R sections.
 */
काष्ठा t3_vpd अणु
	u8 id_tag;
	u8 id_len[2];
	u8 id_data[16];
	u8 vpdr_tag;
	u8 vpdr_len[2];
	VPD_ENTRY(pn, 16);	/* part number */
	VPD_ENTRY(ec, 16);	/* EC level */
	VPD_ENTRY(sn, SERNUM_LEN); /* serial number */
	VPD_ENTRY(na, 12);	/* MAC address base */
	VPD_ENTRY(cclk, 6);	/* core घड़ी */
	VPD_ENTRY(mclk, 6);	/* mem घड़ी */
	VPD_ENTRY(uclk, 6);	/* uP clk */
	VPD_ENTRY(mdc, 6);	/* MDIO clk */
	VPD_ENTRY(mt, 2);	/* mem timing */
	VPD_ENTRY(xaui0cfg, 6);	/* XAUI0 config */
	VPD_ENTRY(xaui1cfg, 6);	/* XAUI1 config */
	VPD_ENTRY(port0, 2);	/* PHY0 complex */
	VPD_ENTRY(port1, 2);	/* PHY1 complex */
	VPD_ENTRY(port2, 2);	/* PHY2 complex */
	VPD_ENTRY(port3, 2);	/* PHY3 complex */
	VPD_ENTRY(rv, 1);	/* csum */
	u32 pad;		/* क्रम multiple-of-4 sizing and alignment */
पूर्ण;

#घोषणा EEPROM_MAX_POLL   40
#घोषणा EEPROM_STAT_ADDR  0x4000
#घोषणा VPD_BASE          0xc00

/**
 *	t3_seeprom_पढ़ो - पढ़ो a VPD EEPROM location
 *	@adapter: adapter to पढ़ो
 *	@addr: EEPROM address
 *	@data: where to store the पढ़ो data
 *
 *	Read a 32-bit word from a location in VPD EEPROM using the card's PCI
 *	VPD ROM capability.  A zero is written to the flag bit when the
 *	address is written to the control रेजिस्टर.  The hardware device will
 *	set the flag to 1 when 4 bytes have been पढ़ो पूर्णांकo the data रेजिस्टर.
 */
पूर्णांक t3_seeprom_पढ़ो(काष्ठा adapter *adapter, u32 addr, __le32 *data)
अणु
	u16 val;
	पूर्णांक attempts = EEPROM_MAX_POLL;
	u32 v;
	अचिन्हित पूर्णांक base = adapter->params.pci.vpd_cap_addr;

	अगर ((addr >= EEPROMSIZE && addr != EEPROM_STAT_ADDR) || (addr & 3))
		वापस -EINVAL;

	pci_ग_लिखो_config_word(adapter->pdev, base + PCI_VPD_ADDR, addr);
	करो अणु
		udelay(10);
		pci_पढ़ो_config_word(adapter->pdev, base + PCI_VPD_ADDR, &val);
	पूर्ण जबतक (!(val & PCI_VPD_ADDR_F) && --attempts);

	अगर (!(val & PCI_VPD_ADDR_F)) अणु
		CH_ERR(adapter, "reading EEPROM address 0x%x failed\n", addr);
		वापस -EIO;
	पूर्ण
	pci_पढ़ो_config_dword(adapter->pdev, base + PCI_VPD_DATA, &v);
	*data = cpu_to_le32(v);
	वापस 0;
पूर्ण

/**
 *	t3_seeprom_ग_लिखो - ग_लिखो a VPD EEPROM location
 *	@adapter: adapter to ग_लिखो
 *	@addr: EEPROM address
 *	@data: value to ग_लिखो
 *
 *	Write a 32-bit word to a location in VPD EEPROM using the card's PCI
 *	VPD ROM capability.
 */
पूर्णांक t3_seeprom_ग_लिखो(काष्ठा adapter *adapter, u32 addr, __le32 data)
अणु
	u16 val;
	पूर्णांक attempts = EEPROM_MAX_POLL;
	अचिन्हित पूर्णांक base = adapter->params.pci.vpd_cap_addr;

	अगर ((addr >= EEPROMSIZE && addr != EEPROM_STAT_ADDR) || (addr & 3))
		वापस -EINVAL;

	pci_ग_लिखो_config_dword(adapter->pdev, base + PCI_VPD_DATA,
			       le32_to_cpu(data));
	pci_ग_लिखो_config_word(adapter->pdev,base + PCI_VPD_ADDR,
			      addr | PCI_VPD_ADDR_F);
	करो अणु
		msleep(1);
		pci_पढ़ो_config_word(adapter->pdev, base + PCI_VPD_ADDR, &val);
	पूर्ण जबतक ((val & PCI_VPD_ADDR_F) && --attempts);

	अगर (val & PCI_VPD_ADDR_F) अणु
		CH_ERR(adapter, "write to EEPROM address 0x%x failed\n", addr);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t3_seeprom_wp - enable/disable EEPROM ग_लिखो protection
 *	@adapter: the adapter
 *	@enable: 1 to enable ग_लिखो protection, 0 to disable it
 *
 *	Enables or disables ग_लिखो protection on the serial EEPROM.
 */
पूर्णांक t3_seeprom_wp(काष्ठा adapter *adapter, पूर्णांक enable)
अणु
	वापस t3_seeprom_ग_लिखो(adapter, EEPROM_STAT_ADDR, enable ? 0xc : 0);
पूर्ण

अटल पूर्णांक vpdstrtouपूर्णांक(अक्षर *s, u8 len, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक *val)
अणु
	अक्षर tok[256];

	स_नकल(tok, s, len);
	tok[len] = 0;
	वापस kstrtouपूर्णांक(strim(tok), base, val);
पूर्ण

अटल पूर्णांक vpdstrtou16(अक्षर *s, u8 len, अचिन्हित पूर्णांक base, u16 *val)
अणु
	अक्षर tok[256];

	स_नकल(tok, s, len);
	tok[len] = 0;
	वापस kstrtou16(strim(tok), base, val);
पूर्ण

/**
 *	get_vpd_params - पढ़ो VPD parameters from VPD EEPROM
 *	@adapter: adapter to पढ़ो
 *	@p: where to store the parameters
 *
 *	Reads card parameters stored in VPD EEPROM.
 */
अटल पूर्णांक get_vpd_params(काष्ठा adapter *adapter, काष्ठा vpd_params *p)
अणु
	पूर्णांक i, addr, ret;
	काष्ठा t3_vpd vpd;

	/*
	 * Card inक्रमmation is normally at VPD_BASE but some early cards had
	 * it at 0.
	 */
	ret = t3_seeprom_पढ़ो(adapter, VPD_BASE, (__le32 *)&vpd);
	अगर (ret)
		वापस ret;
	addr = vpd.id_tag == 0x82 ? VPD_BASE : 0;

	क्रम (i = 0; i < माप(vpd); i += 4) अणु
		ret = t3_seeprom_पढ़ो(adapter, addr + i,
				      (__le32 *)((u8 *)&vpd + i));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = vpdstrtouपूर्णांक(vpd.cclk_data, vpd.cclk_len, 10, &p->cclk);
	अगर (ret)
		वापस ret;
	ret = vpdstrtouपूर्णांक(vpd.mclk_data, vpd.mclk_len, 10, &p->mclk);
	अगर (ret)
		वापस ret;
	ret = vpdstrtouपूर्णांक(vpd.uclk_data, vpd.uclk_len, 10, &p->uclk);
	अगर (ret)
		वापस ret;
	ret = vpdstrtouपूर्णांक(vpd.mdc_data, vpd.mdc_len, 10, &p->mdc);
	अगर (ret)
		वापस ret;
	ret = vpdstrtouपूर्णांक(vpd.mt_data, vpd.mt_len, 10, &p->mem_timing);
	अगर (ret)
		वापस ret;
	स_नकल(p->sn, vpd.sn_data, SERNUM_LEN);

	/* Old eeproms didn't have port inक्रमmation */
	अगर (adapter->params.rev == 0 && !vpd.port0_data[0]) अणु
		p->port_type[0] = uses_xaui(adapter) ? 1 : 2;
		p->port_type[1] = uses_xaui(adapter) ? 6 : 2;
	पूर्ण अन्यथा अणु
		p->port_type[0] = hex_to_bin(vpd.port0_data[0]);
		p->port_type[1] = hex_to_bin(vpd.port1_data[0]);
		ret = vpdstrtou16(vpd.xaui0cfg_data, vpd.xaui0cfg_len, 16,
				  &p->xauicfg[0]);
		अगर (ret)
			वापस ret;
		ret = vpdstrtou16(vpd.xaui1cfg_data, vpd.xaui1cfg_len, 16,
				  &p->xauicfg[1]);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hex2bin(p->eth_base, vpd.na_data, 6);
	अगर (ret < 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/* serial flash and firmware स्थिरants */
क्रमागत अणु
	SF_ATTEMPTS = 5,	/* max retries क्रम SF1 operations */
	SF_SEC_SIZE = 64 * 1024,	/* serial flash sector size */
	SF_SIZE = SF_SEC_SIZE * 8,	/* serial flash size */

	/* flash command opcodes */
	SF_PROG_PAGE = 2,	/* program page */
	SF_WR_DISABLE = 4,	/* disable ग_लिखोs */
	SF_RD_STATUS = 5,	/* पढ़ो status रेजिस्टर */
	SF_WR_ENABLE = 6,	/* enable ग_लिखोs */
	SF_RD_DATA_FAST = 0xb,	/* पढ़ो flash */
	SF_ERASE_SECTOR = 0xd8,	/* erase sector */

	FW_FLASH_BOOT_ADDR = 0x70000,	/* start address of FW in flash */
	FW_VERS_ADDR = 0x7fffc,    /* flash address holding FW version */
	FW_MIN_SIZE = 8            /* at least version and csum */
पूर्ण;

/**
 *	sf1_पढ़ो - पढ़ो data from the serial flash
 *	@adapter: the adapter
 *	@byte_cnt: number of bytes to पढ़ो
 *	@cont: whether another operation will be chained
 *	@valp: where to store the पढ़ो data
 *
 *	Reads up to 4 bytes of data from the serial flash.  The location of
 *	the पढ़ो needs to be specअगरied prior to calling this by issuing the
 *	appropriate commands to the serial flash.
 */
अटल पूर्णांक sf1_पढ़ो(काष्ठा adapter *adapter, अचिन्हित पूर्णांक byte_cnt, पूर्णांक cont,
		    u32 *valp)
अणु
	पूर्णांक ret;

	अगर (!byte_cnt || byte_cnt > 4)
		वापस -EINVAL;
	अगर (t3_पढ़ो_reg(adapter, A_SF_OP) & F_BUSY)
		वापस -EBUSY;
	t3_ग_लिखो_reg(adapter, A_SF_OP, V_CONT(cont) | V_BYTECNT(byte_cnt - 1));
	ret = t3_रुको_op_करोne(adapter, A_SF_OP, F_BUSY, 0, SF_ATTEMPTS, 10);
	अगर (!ret)
		*valp = t3_पढ़ो_reg(adapter, A_SF_DATA);
	वापस ret;
पूर्ण

/**
 *	sf1_ग_लिखो - ग_लिखो data to the serial flash
 *	@adapter: the adapter
 *	@byte_cnt: number of bytes to ग_लिखो
 *	@cont: whether another operation will be chained
 *	@val: value to ग_लिखो
 *
 *	Writes up to 4 bytes of data to the serial flash.  The location of
 *	the ग_लिखो needs to be specअगरied prior to calling this by issuing the
 *	appropriate commands to the serial flash.
 */
अटल पूर्णांक sf1_ग_लिखो(काष्ठा adapter *adapter, अचिन्हित पूर्णांक byte_cnt, पूर्णांक cont,
		     u32 val)
अणु
	अगर (!byte_cnt || byte_cnt > 4)
		वापस -EINVAL;
	अगर (t3_पढ़ो_reg(adapter, A_SF_OP) & F_BUSY)
		वापस -EBUSY;
	t3_ग_लिखो_reg(adapter, A_SF_DATA, val);
	t3_ग_लिखो_reg(adapter, A_SF_OP,
		     V_CONT(cont) | V_BYTECNT(byte_cnt - 1) | V_OP(1));
	वापस t3_रुको_op_करोne(adapter, A_SF_OP, F_BUSY, 0, SF_ATTEMPTS, 10);
पूर्ण

/**
 *	flash_रुको_op - रुको क्रम a flash operation to complete
 *	@adapter: the adapter
 *	@attempts: max number of polls of the status रेजिस्टर
 *	@delay: delay between polls in ms
 *
 *	Wait क्रम a flash operation to complete by polling the status रेजिस्टर.
 */
अटल पूर्णांक flash_रुको_op(काष्ठा adapter *adapter, पूर्णांक attempts, पूर्णांक delay)
अणु
	पूर्णांक ret;
	u32 status;

	जबतक (1) अणु
		अगर ((ret = sf1_ग_लिखो(adapter, 1, 1, SF_RD_STATUS)) != 0 ||
		    (ret = sf1_पढ़ो(adapter, 1, 0, &status)) != 0)
			वापस ret;
		अगर (!(status & 1))
			वापस 0;
		अगर (--attempts == 0)
			वापस -EAGAIN;
		अगर (delay)
			msleep(delay);
	पूर्ण
पूर्ण

/**
 *	t3_पढ़ो_flash - पढ़ो words from serial flash
 *	@adapter: the adapter
 *	@addr: the start address क्रम the पढ़ो
 *	@nwords: how many 32-bit words to पढ़ो
 *	@data: where to store the पढ़ो data
 *	@byte_oriented: whether to store data as bytes or as words
 *
 *	Read the specअगरied number of 32-bit words from the serial flash.
 *	If @byte_oriented is set the पढ़ो data is stored as a byte array
 *	(i.e., big-endian), otherwise as 32-bit words in the platक्रमm's
 *	natural endianness.
 */
अटल पूर्णांक t3_पढ़ो_flash(काष्ठा adapter *adapter, अचिन्हित पूर्णांक addr,
			 अचिन्हित पूर्णांक nwords, u32 *data, पूर्णांक byte_oriented)
अणु
	पूर्णांक ret;

	अगर (addr + nwords * माप(u32) > SF_SIZE || (addr & 3))
		वापस -EINVAL;

	addr = swab32(addr) | SF_RD_DATA_FAST;

	अगर ((ret = sf1_ग_लिखो(adapter, 4, 1, addr)) != 0 ||
	    (ret = sf1_पढ़ो(adapter, 1, 1, data)) != 0)
		वापस ret;

	क्रम (; nwords; nwords--, data++) अणु
		ret = sf1_पढ़ो(adapter, 4, nwords > 1, data);
		अगर (ret)
			वापस ret;
		अगर (byte_oriented)
			*data = htonl(*data);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t3_ग_लिखो_flash - ग_लिखो up to a page of data to the serial flash
 *	@adapter: the adapter
 *	@addr: the start address to ग_लिखो
 *	@n: length of data to ग_लिखो
 *	@data: the data to ग_लिखो
 *
 *	Writes up to a page of data (256 bytes) to the serial flash starting
 *	at the given address.
 */
अटल पूर्णांक t3_ग_लिखो_flash(काष्ठा adapter *adapter, अचिन्हित पूर्णांक addr,
			  अचिन्हित पूर्णांक n, स्थिर u8 *data)
अणु
	पूर्णांक ret;
	u32 buf[64];
	अचिन्हित पूर्णांक i, c, left, val, offset = addr & 0xff;

	अगर (addr + n > SF_SIZE || offset + n > 256)
		वापस -EINVAL;

	val = swab32(addr) | SF_PROG_PAGE;

	अगर ((ret = sf1_ग_लिखो(adapter, 1, 0, SF_WR_ENABLE)) != 0 ||
	    (ret = sf1_ग_लिखो(adapter, 4, 1, val)) != 0)
		वापस ret;

	क्रम (left = n; left; left -= c) अणु
		c = min(left, 4U);
		क्रम (val = 0, i = 0; i < c; ++i)
			val = (val << 8) + *data++;

		ret = sf1_ग_लिखो(adapter, c, c != left, val);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर ((ret = flash_रुको_op(adapter, 5, 1)) != 0)
		वापस ret;

	/* Read the page to verअगरy the ग_लिखो succeeded */
	ret = t3_पढ़ो_flash(adapter, addr & ~0xff, ARRAY_SIZE(buf), buf, 1);
	अगर (ret)
		वापस ret;

	अगर (स_भेद(data - n, (u8 *) buf + offset, n))
		वापस -EIO;
	वापस 0;
पूर्ण

/**
 *	t3_get_tp_version - पढ़ो the tp sram version
 *	@adapter: the adapter
 *	@vers: where to place the version
 *
 *	Reads the protocol sram version from sram.
 */
पूर्णांक t3_get_tp_version(काष्ठा adapter *adapter, u32 *vers)
अणु
	पूर्णांक ret;

	/* Get version loaded in SRAM */
	t3_ग_लिखो_reg(adapter, A_TP_EMBED_OP_FIELD0, 0);
	ret = t3_रुको_op_करोne(adapter, A_TP_EMBED_OP_FIELD0,
			      1, 1, 5, 1);
	अगर (ret)
		वापस ret;

	*vers = t3_पढ़ो_reg(adapter, A_TP_EMBED_OP_FIELD1);

	वापस 0;
पूर्ण

/**
 *	t3_check_tpsram_version - पढ़ो the tp sram version
 *	@adapter: the adapter
 *
 *	Reads the protocol sram version from flash.
 */
पूर्णांक t3_check_tpsram_version(काष्ठा adapter *adapter)
अणु
	पूर्णांक ret;
	u32 vers;
	अचिन्हित पूर्णांक major, minor;

	अगर (adapter->params.rev == T3_REV_A)
		वापस 0;


	ret = t3_get_tp_version(adapter, &vers);
	अगर (ret)
		वापस ret;

	major = G_TP_VERSION_MAJOR(vers);
	minor = G_TP_VERSION_MINOR(vers);

	अगर (major == TP_VERSION_MAJOR && minor == TP_VERSION_MINOR)
		वापस 0;
	अन्यथा अणु
		CH_ERR(adapter, "found wrong TP version (%u.%u), "
		       "driver compiled for version %d.%d\n", major, minor,
		       TP_VERSION_MAJOR, TP_VERSION_MINOR);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 *	t3_check_tpsram - check अगर provided protocol SRAM
 *			  is compatible with this driver
 *	@adapter: the adapter
 *	@tp_sram: the firmware image to ग_लिखो
 *	@size: image size
 *
 *	Checks अगर an adapter's tp sram is compatible with the driver.
 *	Returns 0 अगर the versions are compatible, a negative error otherwise.
 */
पूर्णांक t3_check_tpsram(काष्ठा adapter *adapter, स्थिर u8 *tp_sram,
		    अचिन्हित पूर्णांक size)
अणु
	u32 csum;
	अचिन्हित पूर्णांक i;
	स्थिर __be32 *p = (स्थिर __be32 *)tp_sram;

	/* Verअगरy checksum */
	क्रम (csum = 0, i = 0; i < size / माप(csum); i++)
		csum += ntohl(p[i]);
	अगर (csum != 0xffffffff) अणु
		CH_ERR(adapter, "corrupted protocol SRAM image, checksum %u\n",
		       csum);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत fw_version_type अणु
	FW_VERSION_N3,
	FW_VERSION_T3
पूर्ण;

/**
 *	t3_get_fw_version - पढ़ो the firmware version
 *	@adapter: the adapter
 *	@vers: where to place the version
 *
 *	Reads the FW version from flash.
 */
पूर्णांक t3_get_fw_version(काष्ठा adapter *adapter, u32 *vers)
अणु
	वापस t3_पढ़ो_flash(adapter, FW_VERS_ADDR, 1, vers, 0);
पूर्ण

/**
 *	t3_check_fw_version - check अगर the FW is compatible with this driver
 *	@adapter: the adapter
 *
 *	Checks अगर an adapter's FW is compatible with the driver.  Returns 0
 *	अगर the versions are compatible, a negative error otherwise.
 */
पूर्णांक t3_check_fw_version(काष्ठा adapter *adapter)
अणु
	पूर्णांक ret;
	u32 vers;
	अचिन्हित पूर्णांक type, major, minor;

	ret = t3_get_fw_version(adapter, &vers);
	अगर (ret)
		वापस ret;

	type = G_FW_VERSION_TYPE(vers);
	major = G_FW_VERSION_MAJOR(vers);
	minor = G_FW_VERSION_MINOR(vers);

	अगर (type == FW_VERSION_T3 && major == FW_VERSION_MAJOR &&
	    minor == FW_VERSION_MINOR)
		वापस 0;
	अन्यथा अगर (major != FW_VERSION_MAJOR || minor < FW_VERSION_MINOR)
		CH_WARN(adapter, "found old FW minor version(%u.%u), "
		        "driver compiled for version %u.%u\n", major, minor,
			FW_VERSION_MAJOR, FW_VERSION_MINOR);
	अन्यथा अणु
		CH_WARN(adapter, "found newer FW version(%u.%u), "
		        "driver compiled for version %u.%u\n", major, minor,
			FW_VERSION_MAJOR, FW_VERSION_MINOR);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 *	t3_flash_erase_sectors - erase a range of flash sectors
 *	@adapter: the adapter
 *	@start: the first sector to erase
 *	@end: the last sector to erase
 *
 *	Erases the sectors in the given range.
 */
अटल पूर्णांक t3_flash_erase_sectors(काष्ठा adapter *adapter, पूर्णांक start, पूर्णांक end)
अणु
	जबतक (start <= end) अणु
		पूर्णांक ret;

		अगर ((ret = sf1_ग_लिखो(adapter, 1, 0, SF_WR_ENABLE)) != 0 ||
		    (ret = sf1_ग_लिखो(adapter, 4, 0,
				     SF_ERASE_SECTOR | (start << 8))) != 0 ||
		    (ret = flash_रुको_op(adapter, 5, 500)) != 0)
			वापस ret;
		start++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t3_load_fw - करोwnload firmware
 *	@adapter: the adapter
 *	@fw_data: the firmware image to ग_लिखो
 *	@size: image size
 *
 *	Write the supplied firmware image to the card's serial flash.
 *	The FW image has the following sections: @size - 8 bytes of code and
 *	data, followed by 4 bytes of FW version, followed by the 32-bit
 *	1's complement checksum of the whole image.
 */
पूर्णांक t3_load_fw(काष्ठा adapter *adapter, स्थिर u8 *fw_data, अचिन्हित पूर्णांक size)
अणु
	u32 csum;
	अचिन्हित पूर्णांक i;
	स्थिर __be32 *p = (स्थिर __be32 *)fw_data;
	पूर्णांक ret, addr, fw_sector = FW_FLASH_BOOT_ADDR >> 16;

	अगर ((size & 3) || size < FW_MIN_SIZE)
		वापस -EINVAL;
	अगर (size > FW_VERS_ADDR + 8 - FW_FLASH_BOOT_ADDR)
		वापस -EFBIG;

	क्रम (csum = 0, i = 0; i < size / माप(csum); i++)
		csum += ntohl(p[i]);
	अगर (csum != 0xffffffff) अणु
		CH_ERR(adapter, "corrupted firmware image, checksum %u\n",
		       csum);
		वापस -EINVAL;
	पूर्ण

	ret = t3_flash_erase_sectors(adapter, fw_sector, fw_sector);
	अगर (ret)
		जाओ out;

	size -= 8;		/* trim off version and checksum */
	क्रम (addr = FW_FLASH_BOOT_ADDR; size;) अणु
		अचिन्हित पूर्णांक chunk_size = min(size, 256U);

		ret = t3_ग_लिखो_flash(adapter, addr, chunk_size, fw_data);
		अगर (ret)
			जाओ out;

		addr += chunk_size;
		fw_data += chunk_size;
		size -= chunk_size;
	पूर्ण

	ret = t3_ग_लिखो_flash(adapter, FW_VERS_ADDR, 4, fw_data);
out:
	अगर (ret)
		CH_ERR(adapter, "firmware download failed, error %d\n", ret);
	वापस ret;
पूर्ण

#घोषणा CIM_CTL_BASE 0x2000

/**
 *      t3_cim_ctl_blk_पढ़ो - पढ़ो a block from CIM control region
 *
 *      @adap: the adapter
 *      @addr: the start address within the CIM control region
 *      @n: number of words to पढ़ो
 *      @valp: where to store the result
 *
 *      Reads a block of 4-byte words from the CIM control region.
 */
पूर्णांक t3_cim_ctl_blk_पढ़ो(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr,
			अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक *valp)
अणु
	पूर्णांक ret = 0;

	अगर (t3_पढ़ो_reg(adap, A_CIM_HOST_ACC_CTRL) & F_HOSTBUSY)
		वापस -EBUSY;

	क्रम ( ; !ret && n--; addr += 4) अणु
		t3_ग_लिखो_reg(adap, A_CIM_HOST_ACC_CTRL, CIM_CTL_BASE + addr);
		ret = t3_रुको_op_करोne(adap, A_CIM_HOST_ACC_CTRL, F_HOSTBUSY,
				      0, 5, 2);
		अगर (!ret)
			*valp++ = t3_पढ़ो_reg(adap, A_CIM_HOST_ACC_DATA);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम t3_gate_rx_traffic(काष्ठा cmac *mac, u32 *rx_cfg,
			       u32 *rx_hash_high, u32 *rx_hash_low)
अणु
	/* stop Rx unicast traffic */
	t3_mac_disable_exact_filters(mac);

	/* stop broadcast, multicast, promiscuous mode traffic */
	*rx_cfg = t3_पढ़ो_reg(mac->adapter, A_XGM_RX_CFG);
	t3_set_reg_field(mac->adapter, A_XGM_RX_CFG,
			 F_ENHASHMCAST | F_DISBCAST | F_COPYALLFRAMES,
			 F_DISBCAST);

	*rx_hash_high = t3_पढ़ो_reg(mac->adapter, A_XGM_RX_HASH_HIGH);
	t3_ग_लिखो_reg(mac->adapter, A_XGM_RX_HASH_HIGH, 0);

	*rx_hash_low = t3_पढ़ो_reg(mac->adapter, A_XGM_RX_HASH_LOW);
	t3_ग_लिखो_reg(mac->adapter, A_XGM_RX_HASH_LOW, 0);

	/* Leave समय to drain max RX fअगरo */
	msleep(1);
पूर्ण

अटल व्योम t3_खोलो_rx_traffic(काष्ठा cmac *mac, u32 rx_cfg,
			       u32 rx_hash_high, u32 rx_hash_low)
अणु
	t3_mac_enable_exact_filters(mac);
	t3_set_reg_field(mac->adapter, A_XGM_RX_CFG,
			 F_ENHASHMCAST | F_DISBCAST | F_COPYALLFRAMES,
			 rx_cfg);
	t3_ग_लिखो_reg(mac->adapter, A_XGM_RX_HASH_HIGH, rx_hash_high);
	t3_ग_लिखो_reg(mac->adapter, A_XGM_RX_HASH_LOW, rx_hash_low);
पूर्ण

/**
 *	t3_link_changed - handle पूर्णांकerface link changes
 *	@adapter: the adapter
 *	@port_id: the port index that changed link state
 *
 *	Called when a port's link settings change to propagate the new values
 *	to the associated PHY and MAC.  After perक्रमming the common tasks it
 *	invokes an OS-specअगरic handler.
 */
व्योम t3_link_changed(काष्ठा adapter *adapter, पूर्णांक port_id)
अणु
	पूर्णांक link_ok, speed, duplex, fc;
	काष्ठा port_info *pi = adap2pinfo(adapter, port_id);
	काष्ठा cphy *phy = &pi->phy;
	काष्ठा cmac *mac = &pi->mac;
	काष्ठा link_config *lc = &pi->link_config;

	phy->ops->get_link_status(phy, &link_ok, &speed, &duplex, &fc);

	अगर (!lc->link_ok && link_ok) अणु
		u32 rx_cfg, rx_hash_high, rx_hash_low;
		u32 status;

		t3_xgm_पूर्णांकr_enable(adapter, port_id);
		t3_gate_rx_traffic(mac, &rx_cfg, &rx_hash_high, &rx_hash_low);
		t3_ग_लिखो_reg(adapter, A_XGM_RX_CTRL + mac->offset, 0);
		t3_mac_enable(mac, MAC_सूचीECTION_RX);

		status = t3_पढ़ो_reg(adapter, A_XGM_INT_STATUS + mac->offset);
		अगर (status & F_LINKFAULTCHANGE) अणु
			mac->stats.link_faults++;
			pi->link_fault = 1;
		पूर्ण
		t3_खोलो_rx_traffic(mac, rx_cfg, rx_hash_high, rx_hash_low);
	पूर्ण

	अगर (lc->requested_fc & PAUSE_AUTONEG)
		fc &= lc->requested_fc;
	अन्यथा
		fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);

	अगर (link_ok == lc->link_ok && speed == lc->speed &&
	    duplex == lc->duplex && fc == lc->fc)
		वापस;                            /* nothing changed */

	अगर (link_ok != lc->link_ok && adapter->params.rev > 0 &&
	    uses_xaui(adapter)) अणु
		अगर (link_ok)
			t3b_pcs_reset(mac);
		t3_ग_लिखो_reg(adapter, A_XGM_XAUI_ACT_CTRL + mac->offset,
			     link_ok ? F_TXACTENABLE | F_RXEN : 0);
	पूर्ण
	lc->link_ok = link_ok;
	lc->speed = speed < 0 ? SPEED_INVALID : speed;
	lc->duplex = duplex < 0 ? DUPLEX_INVALID : duplex;

	अगर (link_ok && speed >= 0 && lc->स्वतःneg == AUTONEG_ENABLE) अणु
		/* Set MAC speed, duplex, and flow control to match PHY. */
		t3_mac_set_speed_duplex_fc(mac, speed, duplex, fc);
		lc->fc = fc;
	पूर्ण

	t3_os_link_changed(adapter, port_id, link_ok && !pi->link_fault,
			   speed, duplex, fc);
पूर्ण

व्योम t3_link_fault(काष्ठा adapter *adapter, पूर्णांक port_id)
अणु
	काष्ठा port_info *pi = adap2pinfo(adapter, port_id);
	काष्ठा cmac *mac = &pi->mac;
	काष्ठा cphy *phy = &pi->phy;
	काष्ठा link_config *lc = &pi->link_config;
	पूर्णांक link_ok, speed, duplex, fc, link_fault;
	u32 rx_cfg, rx_hash_high, rx_hash_low;

	t3_gate_rx_traffic(mac, &rx_cfg, &rx_hash_high, &rx_hash_low);

	अगर (adapter->params.rev > 0 && uses_xaui(adapter))
		t3_ग_लिखो_reg(adapter, A_XGM_XAUI_ACT_CTRL + mac->offset, 0);

	t3_ग_लिखो_reg(adapter, A_XGM_RX_CTRL + mac->offset, 0);
	t3_mac_enable(mac, MAC_सूचीECTION_RX);

	t3_खोलो_rx_traffic(mac, rx_cfg, rx_hash_high, rx_hash_low);

	link_fault = t3_पढ़ो_reg(adapter,
				 A_XGM_INT_STATUS + mac->offset);
	link_fault &= F_LINKFAULTCHANGE;

	link_ok = lc->link_ok;
	speed = lc->speed;
	duplex = lc->duplex;
	fc = lc->fc;

	phy->ops->get_link_status(phy, &link_ok, &speed, &duplex, &fc);

	अगर (link_fault) अणु
		lc->link_ok = 0;
		lc->speed = SPEED_INVALID;
		lc->duplex = DUPLEX_INVALID;

		t3_os_link_fault(adapter, port_id, 0);

		/* Account link faults only when the phy reports a link up */
		अगर (link_ok)
			mac->stats.link_faults++;
	पूर्ण अन्यथा अणु
		अगर (link_ok)
			t3_ग_लिखो_reg(adapter, A_XGM_XAUI_ACT_CTRL + mac->offset,
				     F_TXACTENABLE | F_RXEN);

		pi->link_fault = 0;
		lc->link_ok = (अचिन्हित अक्षर)link_ok;
		lc->speed = speed < 0 ? SPEED_INVALID : speed;
		lc->duplex = duplex < 0 ? DUPLEX_INVALID : duplex;
		t3_os_link_fault(adapter, port_id, link_ok);
	पूर्ण
पूर्ण

/**
 *	t3_link_start - apply link configuration to MAC/PHY
 *	@phy: the PHY to setup
 *	@mac: the MAC to setup
 *	@lc: the requested link configuration
 *
 *	Set up a port's MAC and PHY according to a desired link configuration.
 *	- If the PHY can स्वतः-negotiate first decide what to advertise, then
 *	  enable/disable स्वतः-negotiation as desired, and reset.
 *	- If the PHY करोes not स्वतः-negotiate just reset it.
 *	- If स्वतः-negotiation is off set the MAC to the proper speed/duplex/FC,
 *	  otherwise करो it later based on the outcome of स्वतः-negotiation.
 */
पूर्णांक t3_link_start(काष्ठा cphy *phy, काष्ठा cmac *mac, काष्ठा link_config *lc)
अणु
	अचिन्हित पूर्णांक fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);

	lc->link_ok = 0;
	अगर (lc->supported & SUPPORTED_Autoneg) अणु
		lc->advertising &= ~(ADVERTISED_Asym_Pause | ADVERTISED_Pause);
		अगर (fc) अणु
			lc->advertising |= ADVERTISED_Asym_Pause;
			अगर (fc & PAUSE_RX)
				lc->advertising |= ADVERTISED_Pause;
		पूर्ण
		phy->ops->advertise(phy, lc->advertising);

		अगर (lc->स्वतःneg == AUTONEG_DISABLE) अणु
			lc->speed = lc->requested_speed;
			lc->duplex = lc->requested_duplex;
			lc->fc = (अचिन्हित अक्षर)fc;
			t3_mac_set_speed_duplex_fc(mac, lc->speed, lc->duplex,
						   fc);
			/* Also disables स्वतःneg */
			phy->ops->set_speed_duplex(phy, lc->speed, lc->duplex);
		पूर्ण अन्यथा
			phy->ops->स्वतःneg_enable(phy);
	पूर्ण अन्यथा अणु
		t3_mac_set_speed_duplex_fc(mac, -1, -1, fc);
		lc->fc = (अचिन्हित अक्षर)fc;
		phy->ops->reset(phy, 0);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t3_set_vlan_accel - control HW VLAN extraction
 *	@adapter: the adapter
 *	@ports: biपंचांगap of adapter ports to operate on
 *	@on: enable (1) or disable (0) HW VLAN extraction
 *
 *	Enables or disables HW extraction of VLAN tags क्रम the given port.
 */
व्योम t3_set_vlan_accel(काष्ठा adapter *adapter, अचिन्हित पूर्णांक ports, पूर्णांक on)
अणु
	t3_set_reg_field(adapter, A_TP_OUT_CONFIG,
			 ports << S_VLANEXTRACTIONENABLE,
			 on ? (ports << S_VLANEXTRACTIONENABLE) : 0);
पूर्ण

काष्ठा पूर्णांकr_info अणु
	अचिन्हित पूर्णांक mask;	/* bits to check in पूर्णांकerrupt status */
	स्थिर अक्षर *msg;	/* message to prपूर्णांक or शून्य */
	लघु stat_idx;		/* stat counter to increment or -1 */
	अचिन्हित लघु fatal;	/* whether the condition reported is fatal */
पूर्ण;

/**
 *	t3_handle_पूर्णांकr_status - table driven पूर्णांकerrupt handler
 *	@adapter: the adapter that generated the पूर्णांकerrupt
 *	@reg: the पूर्णांकerrupt status रेजिस्टर to process
 *	@mask: a mask to apply to the पूर्णांकerrupt status
 *	@acts: table of पूर्णांकerrupt actions
 *	@stats: statistics counters tracking पूर्णांकerrupt occurrences
 *
 *	A table driven पूर्णांकerrupt handler that applies a set of masks to an
 *	पूर्णांकerrupt status word and perक्रमms the corresponding actions अगर the
 *	पूर्णांकerrupts described by the mask have occurred.  The actions include
 *	optionally prपूर्णांकing a warning or alert message, and optionally
 *	incrementing a stat counter.  The table is terminated by an entry
 *	specअगरying mask 0.  Returns the number of fatal पूर्णांकerrupt conditions.
 */
अटल पूर्णांक t3_handle_पूर्णांकr_status(काष्ठा adapter *adapter, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक mask,
				 स्थिर काष्ठा पूर्णांकr_info *acts,
				 अचिन्हित दीर्घ *stats)
अणु
	पूर्णांक fatal = 0;
	अचिन्हित पूर्णांक status = t3_पढ़ो_reg(adapter, reg) & mask;

	क्रम (; acts->mask; ++acts) अणु
		अगर (!(status & acts->mask))
			जारी;
		अगर (acts->fatal) अणु
			fatal++;
			CH_ALERT(adapter, "%s (0x%x)\n",
				 acts->msg, status & acts->mask);
			status &= ~acts->mask;
		पूर्ण अन्यथा अगर (acts->msg)
			CH_WARN(adapter, "%s (0x%x)\n",
				acts->msg, status & acts->mask);
		अगर (acts->stat_idx >= 0)
			stats[acts->stat_idx]++;
	पूर्ण
	अगर (status)		/* clear processed पूर्णांकerrupts */
		t3_ग_लिखो_reg(adapter, reg, status);
	वापस fatal;
पूर्ण

#घोषणा SGE_INTR_MASK (F_RSPQDISABLED | \
		       F_UC_REQ_FRAMINGERROR | F_R_REQ_FRAMINGERROR | \
		       F_CPPARITYERROR | F_OCPARITYERROR | F_RCPARITYERROR | \
		       F_IRPARITYERROR | V_ITPARITYERROR(M_ITPARITYERROR) | \
		       V_FLPARITYERROR(M_FLPARITYERROR) | F_LODRBPARITYERROR | \
		       F_HIDRBPARITYERROR | F_LORCQPARITYERROR | \
		       F_HIRCQPARITYERROR | F_LOPRIORITYDBFULL | \
		       F_HIPRIORITYDBFULL | F_LOPRIORITYDBEMPTY | \
		       F_HIPRIORITYDBEMPTY | F_HIPIODRBDROPERR | \
		       F_LOPIODRBDROPERR)
#घोषणा MC5_INTR_MASK (F_PARITYERR | F_ACTRGNFULL | F_UNKNOWNCMD | \
		       F_REQQPARERR | F_DISPQPARERR | F_DELACTEMPTY | \
		       F_NFASRCHFAIL)
#घोषणा MC7_INTR_MASK (F_AE | F_UE | F_CE | V_PE(M_PE))
#घोषणा XGM_INTR_MASK (V_TXFIFO_PRTY_ERR(M_TXFIFO_PRTY_ERR) | \
		       V_RXFIFO_PRTY_ERR(M_RXFIFO_PRTY_ERR) | \
		       F_TXFIFO_UNDERRUN)
#घोषणा PCIX_INTR_MASK (F_MSTDETPARERR | F_SIGTARABT | F_RCVTARABT | \
			F_RCVMSTABT | F_SIGSYSERR | F_DETPARERR | \
			F_SPLCMPDIS | F_UNXSPLCMP | F_RCVSPLCMPERR | \
			F_DETCORECCERR | F_DETUNCECCERR | F_PIOPARERR | \
			V_WFPARERR(M_WFPARERR) | V_RFPARERR(M_RFPARERR) | \
			V_CFPARERR(M_CFPARERR) /* | V_MSIXPARERR(M_MSIXPARERR) */)
#घोषणा PCIE_INTR_MASK (F_UNXSPLCPLERRR | F_UNXSPLCPLERRC | F_PCIE_PIOPARERR |\
			F_PCIE_WFPARERR | F_PCIE_RFPARERR | F_PCIE_CFPARERR | \
			/* V_PCIE_MSIXPARERR(M_PCIE_MSIXPARERR) | */ \
			F_RETRYBUFPARERR | F_RETRYLUTPARERR | F_RXPARERR | \
			F_TXPARERR | V_BISTERR(M_BISTERR))
#घोषणा ULPRX_INTR_MASK (F_PARERRDATA | F_PARERRPCMD | F_ARBPF1PERR | \
			 F_ARBPF0PERR | F_ARBFPERR | F_PCMDMUXPERR | \
			 F_DATASELFRAMEERR1 | F_DATASELFRAMEERR0)
#घोषणा ULPTX_INTR_MASK 0xfc
#घोषणा CPLSW_INTR_MASK (F_CIM_OP_MAP_PERR | F_TP_FRAMING_ERROR | \
			 F_SGE_FRAMING_ERROR | F_CIM_FRAMING_ERROR | \
			 F_ZERO_SWITCH_ERROR)
#घोषणा CIM_INTR_MASK (F_BLKWRPLINT | F_BLKRDPLINT | F_BLKWRCTLINT | \
		       F_BLKRDCTLINT | F_BLKWRFLASHINT | F_BLKRDFLASHINT | \
		       F_SGLWRFLASHINT | F_WRBLKFLASHINT | F_BLKWRBOOTINT | \
	 	       F_FLASHRANGEINT | F_SDRAMRANGEINT | F_RSVDSPACEINT | \
		       F_DRAMPARERR | F_ICACHEPARERR | F_DCACHEPARERR | \
		       F_OBQSGEPARERR | F_OBQULPHIPARERR | F_OBQULPLOPARERR | \
		       F_IBQSGELOPARERR | F_IBQSGEHIPARERR | F_IBQULPPARERR | \
		       F_IBQTPPARERR | F_ITAGPARERR | F_DTAGPARERR)
#घोषणा PMTX_INTR_MASK (F_ZERO_C_CMD_ERROR | ICSPI_FRM_ERR | OESPI_FRM_ERR | \
			V_ICSPI_PAR_ERROR(M_ICSPI_PAR_ERROR) | \
			V_OESPI_PAR_ERROR(M_OESPI_PAR_ERROR))
#घोषणा PMRX_INTR_MASK (F_ZERO_E_CMD_ERROR | IESPI_FRM_ERR | OCSPI_FRM_ERR | \
			V_IESPI_PAR_ERROR(M_IESPI_PAR_ERROR) | \
			V_OCSPI_PAR_ERROR(M_OCSPI_PAR_ERROR))
#घोषणा MPS_INTR_MASK (V_TX0TPPARERRENB(M_TX0TPPARERRENB) | \
		       V_TX1TPPARERRENB(M_TX1TPPARERRENB) | \
		       V_RXTPPARERRENB(M_RXTPPARERRENB) | \
		       V_MCAPARERRENB(M_MCAPARERRENB))
#घोषणा XGM_EXTRA_INTR_MASK (F_LINKFAULTCHANGE)
#घोषणा PL_INTR_MASK (F_T3DBG | F_XGMAC0_0 | F_XGMAC0_1 | F_MC5A | F_PM1_TX | \
		      F_PM1_RX | F_ULP2_TX | F_ULP2_RX | F_TP1 | F_CIM | \
		      F_MC7_CM | F_MC7_PMTX | F_MC7_PMRX | F_SGE3 | F_PCIM0 | \
		      F_MPS0 | F_CPL_SWITCH)
/*
 * Interrupt handler क्रम the PCIX1 module.
 */
अटल व्योम pci_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info pcix1_पूर्णांकr_info[] = अणु
		अणुF_MSTDETPARERR, "PCI master detected parity error", -1, 1पूर्ण,
		अणुF_SIGTARABT, "PCI signaled target abort", -1, 1पूर्ण,
		अणुF_RCVTARABT, "PCI received target abort", -1, 1पूर्ण,
		अणुF_RCVMSTABT, "PCI received master abort", -1, 1पूर्ण,
		अणुF_SIGSYSERR, "PCI signaled system error", -1, 1पूर्ण,
		अणुF_DETPARERR, "PCI detected parity error", -1, 1पूर्ण,
		अणुF_SPLCMPDIS, "PCI split completion discarded", -1, 1पूर्ण,
		अणुF_UNXSPLCMP, "PCI unexpected split completion error", -1, 1पूर्ण,
		अणुF_RCVSPLCMPERR, "PCI received split completion error", -1,
		 1पूर्ण,
		अणुF_DETCORECCERR, "PCI correctable ECC error",
		 STAT_PCI_CORR_ECC, 0पूर्ण,
		अणुF_DETUNCECCERR, "PCI uncorrectable ECC error", -1, 1पूर्ण,
		अणुF_PIOPARERR, "PCI PIO FIFO parity error", -1, 1पूर्ण,
		अणुV_WFPARERR(M_WFPARERR), "PCI write FIFO parity error", -1,
		 1पूर्ण,
		अणुV_RFPARERR(M_RFPARERR), "PCI read FIFO parity error", -1,
		 1पूर्ण,
		अणुV_CFPARERR(M_CFPARERR), "PCI command FIFO parity error", -1,
		 1पूर्ण,
		अणुV_MSIXPARERR(M_MSIXPARERR), "PCI MSI-X table/PBA parity "
		 "error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_PCIX_INT_CAUSE, PCIX_INTR_MASK,
				  pcix1_पूर्णांकr_info, adapter->irq_stats))
		t3_fatal_err(adapter);
पूर्ण

/*
 * Interrupt handler क्रम the PCIE module.
 */
अटल व्योम pcie_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info pcie_पूर्णांकr_info[] = अणु
		अणुF_PEXERR, "PCI PEX error", -1, 1पूर्ण,
		अणुF_UNXSPLCPLERRR,
		 "PCI unexpected split completion DMA read error", -1, 1पूर्ण,
		अणुF_UNXSPLCPLERRC,
		 "PCI unexpected split completion DMA command error", -1, 1पूर्ण,
		अणुF_PCIE_PIOPARERR, "PCI PIO FIFO parity error", -1, 1पूर्ण,
		अणुF_PCIE_WFPARERR, "PCI write FIFO parity error", -1, 1पूर्ण,
		अणुF_PCIE_RFPARERR, "PCI read FIFO parity error", -1, 1पूर्ण,
		अणुF_PCIE_CFPARERR, "PCI command FIFO parity error", -1, 1पूर्ण,
		अणुV_PCIE_MSIXPARERR(M_PCIE_MSIXPARERR),
		 "PCI MSI-X table/PBA parity error", -1, 1पूर्ण,
		अणुF_RETRYBUFPARERR, "PCI retry buffer parity error", -1, 1पूर्ण,
		अणुF_RETRYLUTPARERR, "PCI retry LUT parity error", -1, 1पूर्ण,
		अणुF_RXPARERR, "PCI Rx parity error", -1, 1पूर्ण,
		अणुF_TXPARERR, "PCI Tx parity error", -1, 1पूर्ण,
		अणुV_BISTERR(M_BISTERR), "PCI BIST error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_पढ़ो_reg(adapter, A_PCIE_INT_CAUSE) & F_PEXERR)
		CH_ALERT(adapter, "PEX error code 0x%x\n",
			 t3_पढ़ो_reg(adapter, A_PCIE_PEX_ERR));

	अगर (t3_handle_पूर्णांकr_status(adapter, A_PCIE_INT_CAUSE, PCIE_INTR_MASK,
				  pcie_पूर्णांकr_info, adapter->irq_stats))
		t3_fatal_err(adapter);
पूर्ण

/*
 * TP पूर्णांकerrupt handler.
 */
अटल व्योम tp_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info tp_पूर्णांकr_info[] = अणु
		अणु0xffffff, "TP parity error", -1, 1पूर्ण,
		अणु0x1000000, "TP out of Rx pages", -1, 1पूर्ण,
		अणु0x2000000, "TP out of Tx pages", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अटल स्थिर काष्ठा पूर्णांकr_info tp_पूर्णांकr_info_t3c[] = अणु
		अणु0x1fffffff, "TP parity error", -1, 1पूर्ण,
		अणुF_FLMRXFLSTEMPTY, "TP out of Rx pages", -1, 1पूर्ण,
		अणुF_FLMTXFLSTEMPTY, "TP out of Tx pages", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_TP_INT_CAUSE, 0xffffffff,
				  adapter->params.rev < T3_REV_C ?
				  tp_पूर्णांकr_info : tp_पूर्णांकr_info_t3c, शून्य))
		t3_fatal_err(adapter);
पूर्ण

/*
 * CIM पूर्णांकerrupt handler.
 */
अटल व्योम cim_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info cim_पूर्णांकr_info[] = अणु
		अणुF_RSVDSPACEINT, "CIM reserved space write", -1, 1पूर्ण,
		अणुF_SDRAMRANGEINT, "CIM SDRAM address out of range", -1, 1पूर्ण,
		अणुF_FLASHRANGEINT, "CIM flash address out of range", -1, 1पूर्ण,
		अणुF_BLKWRBOOTINT, "CIM block write to boot space", -1, 1पूर्ण,
		अणुF_WRBLKFLASHINT, "CIM write to cached flash space", -1, 1पूर्ण,
		अणुF_SGLWRFLASHINT, "CIM single write to flash space", -1, 1पूर्ण,
		अणुF_BLKRDFLASHINT, "CIM block read from flash space", -1, 1पूर्ण,
		अणुF_BLKWRFLASHINT, "CIM block write to flash space", -1, 1पूर्ण,
		अणुF_BLKRDCTLINT, "CIM block read from CTL space", -1, 1पूर्ण,
		अणुF_BLKWRCTLINT, "CIM block write to CTL space", -1, 1पूर्ण,
		अणुF_BLKRDPLINT, "CIM block read from PL space", -1, 1पूर्ण,
		अणुF_BLKWRPLINT, "CIM block write to PL space", -1, 1पूर्ण,
		अणुF_DRAMPARERR, "CIM DRAM parity error", -1, 1पूर्ण,
		अणुF_ICACHEPARERR, "CIM icache parity error", -1, 1पूर्ण,
		अणुF_DCACHEPARERR, "CIM dcache parity error", -1, 1पूर्ण,
		अणुF_OBQSGEPARERR, "CIM OBQ SGE parity error", -1, 1पूर्ण,
		अणुF_OBQULPHIPARERR, "CIM OBQ ULPHI parity error", -1, 1पूर्ण,
		अणुF_OBQULPLOPARERR, "CIM OBQ ULPLO parity error", -1, 1पूर्ण,
		अणुF_IBQSGELOPARERR, "CIM IBQ SGELO parity error", -1, 1पूर्ण,
		अणुF_IBQSGEHIPARERR, "CIM IBQ SGEHI parity error", -1, 1पूर्ण,
		अणुF_IBQULPPARERR, "CIM IBQ ULP parity error", -1, 1पूर्ण,
		अणुF_IBQTPPARERR, "CIM IBQ TP parity error", -1, 1पूर्ण,
		अणुF_ITAGPARERR, "CIM itag parity error", -1, 1पूर्ण,
		अणुF_DTAGPARERR, "CIM dtag parity error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_CIM_HOST_INT_CAUSE, 0xffffffff,
				  cim_पूर्णांकr_info, शून्य))
		t3_fatal_err(adapter);
पूर्ण

/*
 * ULP RX पूर्णांकerrupt handler.
 */
अटल व्योम ulprx_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info ulprx_पूर्णांकr_info[] = अणु
		अणुF_PARERRDATA, "ULP RX data parity error", -1, 1पूर्ण,
		अणुF_PARERRPCMD, "ULP RX command parity error", -1, 1पूर्ण,
		अणुF_ARBPF1PERR, "ULP RX ArbPF1 parity error", -1, 1पूर्ण,
		अणुF_ARBPF0PERR, "ULP RX ArbPF0 parity error", -1, 1पूर्ण,
		अणुF_ARBFPERR, "ULP RX ArbF parity error", -1, 1पूर्ण,
		अणुF_PCMDMUXPERR, "ULP RX PCMDMUX parity error", -1, 1पूर्ण,
		अणुF_DATASELFRAMEERR1, "ULP RX frame error", -1, 1पूर्ण,
		अणुF_DATASELFRAMEERR0, "ULP RX frame error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_ULPRX_INT_CAUSE, 0xffffffff,
				  ulprx_पूर्णांकr_info, शून्य))
		t3_fatal_err(adapter);
पूर्ण

/*
 * ULP TX पूर्णांकerrupt handler.
 */
अटल व्योम ulptx_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info ulptx_पूर्णांकr_info[] = अणु
		अणुF_PBL_BOUND_ERR_CH0, "ULP TX channel 0 PBL out of bounds",
		 STAT_ULP_CH0_PBL_OOB, 0पूर्ण,
		अणुF_PBL_BOUND_ERR_CH1, "ULP TX channel 1 PBL out of bounds",
		 STAT_ULP_CH1_PBL_OOB, 0पूर्ण,
		अणु0xfc, "ULP TX parity error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_ULPTX_INT_CAUSE, 0xffffffff,
				  ulptx_पूर्णांकr_info, adapter->irq_stats))
		t3_fatal_err(adapter);
पूर्ण

#घोषणा ICSPI_FRM_ERR (F_ICSPI0_FIFO2X_RX_FRAMING_ERROR | \
	F_ICSPI1_FIFO2X_RX_FRAMING_ERROR | F_ICSPI0_RX_FRAMING_ERROR | \
	F_ICSPI1_RX_FRAMING_ERROR | F_ICSPI0_TX_FRAMING_ERROR | \
	F_ICSPI1_TX_FRAMING_ERROR)
#घोषणा OESPI_FRM_ERR (F_OESPI0_RX_FRAMING_ERROR | \
	F_OESPI1_RX_FRAMING_ERROR | F_OESPI0_TX_FRAMING_ERROR | \
	F_OESPI1_TX_FRAMING_ERROR | F_OESPI0_OFIFO2X_TX_FRAMING_ERROR | \
	F_OESPI1_OFIFO2X_TX_FRAMING_ERROR)

/*
 * PM TX पूर्णांकerrupt handler.
 */
अटल व्योम pmtx_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info pmtx_पूर्णांकr_info[] = अणु
		अणुF_ZERO_C_CMD_ERROR, "PMTX 0-length pcmd", -1, 1पूर्ण,
		अणुICSPI_FRM_ERR, "PMTX ispi framing error", -1, 1पूर्ण,
		अणुOESPI_FRM_ERR, "PMTX ospi framing error", -1, 1पूर्ण,
		अणुV_ICSPI_PAR_ERROR(M_ICSPI_PAR_ERROR),
		 "PMTX ispi parity error", -1, 1पूर्ण,
		अणुV_OESPI_PAR_ERROR(M_OESPI_PAR_ERROR),
		 "PMTX ospi parity error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_PM1_TX_INT_CAUSE, 0xffffffff,
				  pmtx_पूर्णांकr_info, शून्य))
		t3_fatal_err(adapter);
पूर्ण

#घोषणा IESPI_FRM_ERR (F_IESPI0_FIFO2X_RX_FRAMING_ERROR | \
	F_IESPI1_FIFO2X_RX_FRAMING_ERROR | F_IESPI0_RX_FRAMING_ERROR | \
	F_IESPI1_RX_FRAMING_ERROR | F_IESPI0_TX_FRAMING_ERROR | \
	F_IESPI1_TX_FRAMING_ERROR)
#घोषणा OCSPI_FRM_ERR (F_OCSPI0_RX_FRAMING_ERROR | \
	F_OCSPI1_RX_FRAMING_ERROR | F_OCSPI0_TX_FRAMING_ERROR | \
	F_OCSPI1_TX_FRAMING_ERROR | F_OCSPI0_OFIFO2X_TX_FRAMING_ERROR | \
	F_OCSPI1_OFIFO2X_TX_FRAMING_ERROR)

/*
 * PM RX पूर्णांकerrupt handler.
 */
अटल व्योम pmrx_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info pmrx_पूर्णांकr_info[] = अणु
		अणुF_ZERO_E_CMD_ERROR, "PMRX 0-length pcmd", -1, 1पूर्ण,
		अणुIESPI_FRM_ERR, "PMRX ispi framing error", -1, 1पूर्ण,
		अणुOCSPI_FRM_ERR, "PMRX ospi framing error", -1, 1पूर्ण,
		अणुV_IESPI_PAR_ERROR(M_IESPI_PAR_ERROR),
		 "PMRX ispi parity error", -1, 1पूर्ण,
		अणुV_OCSPI_PAR_ERROR(M_OCSPI_PAR_ERROR),
		 "PMRX ospi parity error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_PM1_RX_INT_CAUSE, 0xffffffff,
				  pmrx_पूर्णांकr_info, शून्य))
		t3_fatal_err(adapter);
पूर्ण

/*
 * CPL चयन पूर्णांकerrupt handler.
 */
अटल व्योम cplsw_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info cplsw_पूर्णांकr_info[] = अणु
		अणुF_CIM_OP_MAP_PERR, "CPL switch CIM parity error", -1, 1पूर्ण,
		अणुF_CIM_OVFL_ERROR, "CPL switch CIM overflow", -1, 1पूर्ण,
		अणुF_TP_FRAMING_ERROR, "CPL switch TP framing error", -1, 1पूर्ण,
		अणुF_SGE_FRAMING_ERROR, "CPL switch SGE framing error", -1, 1पूर्ण,
		अणुF_CIM_FRAMING_ERROR, "CPL switch CIM framing error", -1, 1पूर्ण,
		अणुF_ZERO_SWITCH_ERROR, "CPL switch no-switch error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_CPL_INTR_CAUSE, 0xffffffff,
				  cplsw_पूर्णांकr_info, शून्य))
		t3_fatal_err(adapter);
पूर्ण

/*
 * MPS पूर्णांकerrupt handler.
 */
अटल व्योम mps_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा पूर्णांकr_info mps_पूर्णांकr_info[] = अणु
		अणु0x1ff, "MPS parity error", -1, 1पूर्ण,
		अणु0पूर्ण
	पूर्ण;

	अगर (t3_handle_पूर्णांकr_status(adapter, A_MPS_INT_CAUSE, 0xffffffff,
				  mps_पूर्णांकr_info, शून्य))
		t3_fatal_err(adapter);
पूर्ण

#घोषणा MC7_INTR_FATAL (F_UE | V_PE(M_PE) | F_AE)

/*
 * MC7 पूर्णांकerrupt handler.
 */
अटल व्योम mc7_पूर्णांकr_handler(काष्ठा mc7 *mc7)
अणु
	काष्ठा adapter *adapter = mc7->adapter;
	u32 cause = t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_INT_CAUSE);

	अगर (cause & F_CE) अणु
		mc7->stats.corr_err++;
		CH_WARN(adapter, "%s MC7 correctable error at addr 0x%x, "
			"data 0x%x 0x%x 0x%x\n", mc7->name,
			t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CE_ADDR),
			t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CE_DATA0),
			t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CE_DATA1),
			t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CE_DATA2));
	पूर्ण

	अगर (cause & F_UE) अणु
		mc7->stats.uncorr_err++;
		CH_ALERT(adapter, "%s MC7 uncorrectable error at addr 0x%x, "
			 "data 0x%x 0x%x 0x%x\n", mc7->name,
			 t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_UE_ADDR),
			 t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_UE_DATA0),
			 t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_UE_DATA1),
			 t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_UE_DATA2));
	पूर्ण

	अगर (G_PE(cause)) अणु
		mc7->stats.parity_err++;
		CH_ALERT(adapter, "%s MC7 parity error 0x%x\n",
			 mc7->name, G_PE(cause));
	पूर्ण

	अगर (cause & F_AE) अणु
		u32 addr = 0;

		अगर (adapter->params.rev > 0)
			addr = t3_पढ़ो_reg(adapter,
					   mc7->offset + A_MC7_ERR_ADDR);
		mc7->stats.addr_err++;
		CH_ALERT(adapter, "%s MC7 address error: 0x%x\n",
			 mc7->name, addr);
	पूर्ण

	अगर (cause & MC7_INTR_FATAL)
		t3_fatal_err(adapter);

	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_INT_CAUSE, cause);
पूर्ण

#घोषणा XGM_INTR_FATAL (V_TXFIFO_PRTY_ERR(M_TXFIFO_PRTY_ERR) | \
			V_RXFIFO_PRTY_ERR(M_RXFIFO_PRTY_ERR))
/*
 * XGMAC पूर्णांकerrupt handler.
 */
अटल पूर्णांक mac_पूर्णांकr_handler(काष्ठा adapter *adap, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा cmac *mac = &adap2pinfo(adap, idx)->mac;
	/*
	 * We mask out पूर्णांकerrupt causes क्रम which we're not taking पूर्णांकerrupts.
	 * This allows us to use polling logic to monitor some of the other
	 * conditions when taking पूर्णांकerrupts would impose too much load on the
	 * प्रणाली.
	 */
	u32 cause = t3_पढ़ो_reg(adap, A_XGM_INT_CAUSE + mac->offset) &
		    ~F_RXFIFO_OVERFLOW;

	अगर (cause & V_TXFIFO_PRTY_ERR(M_TXFIFO_PRTY_ERR)) अणु
		mac->stats.tx_fअगरo_parity_err++;
		CH_ALERT(adap, "port%d: MAC TX FIFO parity error\n", idx);
	पूर्ण
	अगर (cause & V_RXFIFO_PRTY_ERR(M_RXFIFO_PRTY_ERR)) अणु
		mac->stats.rx_fअगरo_parity_err++;
		CH_ALERT(adap, "port%d: MAC RX FIFO parity error\n", idx);
	पूर्ण
	अगर (cause & F_TXFIFO_UNDERRUN)
		mac->stats.tx_fअगरo_urun++;
	अगर (cause & F_RXFIFO_OVERFLOW)
		mac->stats.rx_fअगरo_ovfl++;
	अगर (cause & V_SERDES_LOS(M_SERDES_LOS))
		mac->stats.serdes_संकेत_loss++;
	अगर (cause & F_XAUIPCSCTCERR)
		mac->stats.xaui_pcs_ctc_err++;
	अगर (cause & F_XAUIPCSALIGNCHANGE)
		mac->stats.xaui_pcs_align_change++;
	अगर (cause & F_XGM_INT) अणु
		t3_set_reg_field(adap,
				 A_XGM_INT_ENABLE + mac->offset,
				 F_XGM_INT, 0);
		mac->stats.link_faults++;

		t3_os_link_fault_handler(adap, idx);
	पूर्ण

	अगर (cause & XGM_INTR_FATAL)
		t3_fatal_err(adap);

	t3_ग_लिखो_reg(adap, A_XGM_INT_CAUSE + mac->offset, cause);
	वापस cause != 0;
पूर्ण

/*
 * Interrupt handler क्रम PHY events.
 */
पूर्णांक t3_phy_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	u32 i, cause = t3_पढ़ो_reg(adapter, A_T3DBG_INT_CAUSE);

	क्रम_each_port(adapter, i) अणु
		काष्ठा port_info *p = adap2pinfo(adapter, i);

		अगर (!(p->phy.caps & SUPPORTED_IRQ))
			जारी;

		अगर (cause & (1 << adapter_info(adapter)->gpio_पूर्णांकr[i])) अणु
			पूर्णांक phy_cause = p->phy.ops->पूर्णांकr_handler(&p->phy);

			अगर (phy_cause & cphy_cause_link_change)
				t3_link_changed(adapter, i);
			अगर (phy_cause & cphy_cause_fअगरo_error)
				p->phy.fअगरo_errors++;
			अगर (phy_cause & cphy_cause_module_change)
				t3_os_phymod_changed(adapter, i);
		पूर्ण
	पूर्ण

	t3_ग_लिखो_reg(adapter, A_T3DBG_INT_CAUSE, cause);
	वापस 0;
पूर्ण

/*
 * T3 slow path (non-data) पूर्णांकerrupt handler.
 */
पूर्णांक t3_slow_पूर्णांकr_handler(काष्ठा adapter *adapter)
अणु
	u32 cause = t3_पढ़ो_reg(adapter, A_PL_INT_CAUSE0);

	cause &= adapter->slow_पूर्णांकr_mask;
	अगर (!cause)
		वापस 0;
	अगर (cause & F_PCIM0) अणु
		अगर (is_pcie(adapter))
			pcie_पूर्णांकr_handler(adapter);
		अन्यथा
			pci_पूर्णांकr_handler(adapter);
	पूर्ण
	अगर (cause & F_SGE3)
		t3_sge_err_पूर्णांकr_handler(adapter);
	अगर (cause & F_MC7_PMRX)
		mc7_पूर्णांकr_handler(&adapter->pmrx);
	अगर (cause & F_MC7_PMTX)
		mc7_पूर्णांकr_handler(&adapter->pmtx);
	अगर (cause & F_MC7_CM)
		mc7_पूर्णांकr_handler(&adapter->cm);
	अगर (cause & F_CIM)
		cim_पूर्णांकr_handler(adapter);
	अगर (cause & F_TP1)
		tp_पूर्णांकr_handler(adapter);
	अगर (cause & F_ULP2_RX)
		ulprx_पूर्णांकr_handler(adapter);
	अगर (cause & F_ULP2_TX)
		ulptx_पूर्णांकr_handler(adapter);
	अगर (cause & F_PM1_RX)
		pmrx_पूर्णांकr_handler(adapter);
	अगर (cause & F_PM1_TX)
		pmtx_पूर्णांकr_handler(adapter);
	अगर (cause & F_CPL_SWITCH)
		cplsw_पूर्णांकr_handler(adapter);
	अगर (cause & F_MPS0)
		mps_पूर्णांकr_handler(adapter);
	अगर (cause & F_MC5A)
		t3_mc5_पूर्णांकr_handler(&adapter->mc5);
	अगर (cause & F_XGMAC0_0)
		mac_पूर्णांकr_handler(adapter, 0);
	अगर (cause & F_XGMAC0_1)
		mac_पूर्णांकr_handler(adapter, 1);
	अगर (cause & F_T3DBG)
		t3_os_ext_पूर्णांकr_handler(adapter);

	/* Clear the पूर्णांकerrupts just processed. */
	t3_ग_लिखो_reg(adapter, A_PL_INT_CAUSE0, cause);
	t3_पढ़ो_reg(adapter, A_PL_INT_CAUSE0);	/* flush */
	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक calc_gpio_पूर्णांकr(काष्ठा adapter *adap)
अणु
	अचिन्हित पूर्णांक i, gpi_पूर्णांकr = 0;

	क्रम_each_port(adap, i)
		अगर ((adap2pinfo(adap, i)->phy.caps & SUPPORTED_IRQ) &&
		    adapter_info(adap)->gpio_पूर्णांकr[i])
			gpi_पूर्णांकr |= 1 << adapter_info(adap)->gpio_पूर्णांकr[i];
	वापस gpi_पूर्णांकr;
पूर्ण

/**
 *	t3_पूर्णांकr_enable - enable पूर्णांकerrupts
 *	@adapter: the adapter whose पूर्णांकerrupts should be enabled
 *
 *	Enable पूर्णांकerrupts by setting the पूर्णांकerrupt enable रेजिस्टरs of the
 *	various HW modules and then enabling the top-level पूर्णांकerrupt
 *	concentrator.
 */
व्योम t3_पूर्णांकr_enable(काष्ठा adapter *adapter)
अणु
	अटल स्थिर काष्ठा addr_val_pair पूर्णांकr_en_avp[] = अणु
		अणुA_SG_INT_ENABLE, SGE_INTR_MASKपूर्ण,
		अणुA_MC7_INT_ENABLE, MC7_INTR_MASKपूर्ण,
		अणुA_MC7_INT_ENABLE - MC7_PMRX_BASE_ADDR + MC7_PMTX_BASE_ADDR,
		 MC7_INTR_MASKपूर्ण,
		अणुA_MC7_INT_ENABLE - MC7_PMRX_BASE_ADDR + MC7_CM_BASE_ADDR,
		 MC7_INTR_MASKपूर्ण,
		अणुA_MC5_DB_INT_ENABLE, MC5_INTR_MASKपूर्ण,
		अणुA_ULPRX_INT_ENABLE, ULPRX_INTR_MASKपूर्ण,
		अणुA_PM1_TX_INT_ENABLE, PMTX_INTR_MASKपूर्ण,
		अणुA_PM1_RX_INT_ENABLE, PMRX_INTR_MASKपूर्ण,
		अणुA_CIM_HOST_INT_ENABLE, CIM_INTR_MASKपूर्ण,
		अणुA_MPS_INT_ENABLE, MPS_INTR_MASKपूर्ण,
	पूर्ण;

	adapter->slow_पूर्णांकr_mask = PL_INTR_MASK;

	t3_ग_लिखो_regs(adapter, पूर्णांकr_en_avp, ARRAY_SIZE(पूर्णांकr_en_avp), 0);
	t3_ग_लिखो_reg(adapter, A_TP_INT_ENABLE,
		     adapter->params.rev >= T3_REV_C ? 0x2bfffff : 0x3bfffff);

	अगर (adapter->params.rev > 0) अणु
		t3_ग_लिखो_reg(adapter, A_CPL_INTR_ENABLE,
			     CPLSW_INTR_MASK | F_CIM_OVFL_ERROR);
		t3_ग_लिखो_reg(adapter, A_ULPTX_INT_ENABLE,
			     ULPTX_INTR_MASK | F_PBL_BOUND_ERR_CH0 |
			     F_PBL_BOUND_ERR_CH1);
	पूर्ण अन्यथा अणु
		t3_ग_लिखो_reg(adapter, A_CPL_INTR_ENABLE, CPLSW_INTR_MASK);
		t3_ग_लिखो_reg(adapter, A_ULPTX_INT_ENABLE, ULPTX_INTR_MASK);
	पूर्ण

	t3_ग_लिखो_reg(adapter, A_T3DBG_INT_ENABLE, calc_gpio_पूर्णांकr(adapter));

	अगर (is_pcie(adapter))
		t3_ग_लिखो_reg(adapter, A_PCIE_INT_ENABLE, PCIE_INTR_MASK);
	अन्यथा
		t3_ग_लिखो_reg(adapter, A_PCIX_INT_ENABLE, PCIX_INTR_MASK);
	t3_ग_लिखो_reg(adapter, A_PL_INT_ENABLE0, adapter->slow_पूर्णांकr_mask);
	t3_पढ़ो_reg(adapter, A_PL_INT_ENABLE0);	/* flush */
पूर्ण

/**
 *	t3_पूर्णांकr_disable - disable a card's पूर्णांकerrupts
 *	@adapter: the adapter whose पूर्णांकerrupts should be disabled
 *
 *	Disable पूर्णांकerrupts.  We only disable the top-level पूर्णांकerrupt
 *	concentrator and the SGE data पूर्णांकerrupts.
 */
व्योम t3_पूर्णांकr_disable(काष्ठा adapter *adapter)
अणु
	t3_ग_लिखो_reg(adapter, A_PL_INT_ENABLE0, 0);
	t3_पढ़ो_reg(adapter, A_PL_INT_ENABLE0);	/* flush */
	adapter->slow_पूर्णांकr_mask = 0;
पूर्ण

/**
 *	t3_पूर्णांकr_clear - clear all पूर्णांकerrupts
 *	@adapter: the adapter whose पूर्णांकerrupts should be cleared
 *
 *	Clears all पूर्णांकerrupts.
 */
व्योम t3_पूर्णांकr_clear(काष्ठा adapter *adapter)
अणु
	अटल स्थिर अचिन्हित पूर्णांक cause_reg_addr[] = अणु
		A_SG_INT_CAUSE,
		A_SG_RSPQ_FL_STATUS,
		A_PCIX_INT_CAUSE,
		A_MC7_INT_CAUSE,
		A_MC7_INT_CAUSE - MC7_PMRX_BASE_ADDR + MC7_PMTX_BASE_ADDR,
		A_MC7_INT_CAUSE - MC7_PMRX_BASE_ADDR + MC7_CM_BASE_ADDR,
		A_CIM_HOST_INT_CAUSE,
		A_TP_INT_CAUSE,
		A_MC5_DB_INT_CAUSE,
		A_ULPRX_INT_CAUSE,
		A_ULPTX_INT_CAUSE,
		A_CPL_INTR_CAUSE,
		A_PM1_TX_INT_CAUSE,
		A_PM1_RX_INT_CAUSE,
		A_MPS_INT_CAUSE,
		A_T3DBG_INT_CAUSE,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	/* Clear PHY and MAC पूर्णांकerrupts क्रम each port. */
	क्रम_each_port(adapter, i)
	    t3_port_पूर्णांकr_clear(adapter, i);

	क्रम (i = 0; i < ARRAY_SIZE(cause_reg_addr); ++i)
		t3_ग_लिखो_reg(adapter, cause_reg_addr[i], 0xffffffff);

	अगर (is_pcie(adapter))
		t3_ग_लिखो_reg(adapter, A_PCIE_PEX_ERR, 0xffffffff);
	t3_ग_लिखो_reg(adapter, A_PL_INT_CAUSE0, 0xffffffff);
	t3_पढ़ो_reg(adapter, A_PL_INT_CAUSE0);	/* flush */
पूर्ण

व्योम t3_xgm_पूर्णांकr_enable(काष्ठा adapter *adapter, पूर्णांक idx)
अणु
	काष्ठा port_info *pi = adap2pinfo(adapter, idx);

	t3_ग_लिखो_reg(adapter, A_XGM_XGM_INT_ENABLE + pi->mac.offset,
		     XGM_EXTRA_INTR_MASK);
पूर्ण

व्योम t3_xgm_पूर्णांकr_disable(काष्ठा adapter *adapter, पूर्णांक idx)
अणु
	काष्ठा port_info *pi = adap2pinfo(adapter, idx);

	t3_ग_लिखो_reg(adapter, A_XGM_XGM_INT_DISABLE + pi->mac.offset,
		     0x7ff);
पूर्ण

/**
 *	t3_port_पूर्णांकr_enable - enable port-specअगरic पूर्णांकerrupts
 *	@adapter: associated adapter
 *	@idx: index of port whose पूर्णांकerrupts should be enabled
 *
 *	Enable port-specअगरic (i.e., MAC and PHY) पूर्णांकerrupts क्रम the given
 *	adapter port.
 */
व्योम t3_port_पूर्णांकr_enable(काष्ठा adapter *adapter, पूर्णांक idx)
अणु
	काष्ठा cphy *phy = &adap2pinfo(adapter, idx)->phy;

	t3_ग_लिखो_reg(adapter, XGM_REG(A_XGM_INT_ENABLE, idx), XGM_INTR_MASK);
	t3_पढ़ो_reg(adapter, XGM_REG(A_XGM_INT_ENABLE, idx)); /* flush */
	phy->ops->पूर्णांकr_enable(phy);
पूर्ण

/**
 *	t3_port_पूर्णांकr_disable - disable port-specअगरic पूर्णांकerrupts
 *	@adapter: associated adapter
 *	@idx: index of port whose पूर्णांकerrupts should be disabled
 *
 *	Disable port-specअगरic (i.e., MAC and PHY) पूर्णांकerrupts क्रम the given
 *	adapter port.
 */
व्योम t3_port_पूर्णांकr_disable(काष्ठा adapter *adapter, पूर्णांक idx)
अणु
	काष्ठा cphy *phy = &adap2pinfo(adapter, idx)->phy;

	t3_ग_लिखो_reg(adapter, XGM_REG(A_XGM_INT_ENABLE, idx), 0);
	t3_पढ़ो_reg(adapter, XGM_REG(A_XGM_INT_ENABLE, idx)); /* flush */
	phy->ops->पूर्णांकr_disable(phy);
पूर्ण

/**
 *	t3_port_पूर्णांकr_clear - clear port-specअगरic पूर्णांकerrupts
 *	@adapter: associated adapter
 *	@idx: index of port whose पूर्णांकerrupts to clear
 *
 *	Clear port-specअगरic (i.e., MAC and PHY) पूर्णांकerrupts क्रम the given
 *	adapter port.
 */
अटल व्योम t3_port_पूर्णांकr_clear(काष्ठा adapter *adapter, पूर्णांक idx)
अणु
	काष्ठा cphy *phy = &adap2pinfo(adapter, idx)->phy;

	t3_ग_लिखो_reg(adapter, XGM_REG(A_XGM_INT_CAUSE, idx), 0xffffffff);
	t3_पढ़ो_reg(adapter, XGM_REG(A_XGM_INT_CAUSE, idx)); /* flush */
	phy->ops->पूर्णांकr_clear(phy);
पूर्ण

#घोषणा SG_CONTEXT_CMD_ATTEMPTS 100

/**
 * 	t3_sge_ग_लिखो_context - ग_लिखो an SGE context
 * 	@adapter: the adapter
 * 	@id: the context id
 * 	@type: the context type
 *
 * 	Program an SGE context with the values alपढ़ोy loaded in the
 * 	CONTEXT_DATA? रेजिस्टरs.
 */
अटल पूर्णांक t3_sge_ग_लिखो_context(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक type)
अणु
	अगर (type == F_RESPONSEQ) अणु
		/*
		 * Can't ग_लिखो the Response Queue Context bits क्रम
		 * Interrupt Armed or the Reserve bits after the chip
		 * has been initialized out of reset.  Writing to these
		 * bits can confuse the hardware.
		 */
		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK0, 0xffffffff);
		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK1, 0xffffffff);
		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK2, 0x17ffffff);
		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK3, 0xffffffff);
	पूर्ण अन्यथा अणु
		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK0, 0xffffffff);
		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK1, 0xffffffff);
		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK2, 0xffffffff);
		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK3, 0xffffffff);
	पूर्ण
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | type | V_CONTEXT(id));
	वापस t3_रुको_op_करोne(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
पूर्ण

/**
 *	clear_sge_ctxt - completely clear an SGE context
 *	@adap: the adapter
 *	@id: the context id
 *	@type: the context type
 *
 *	Completely clear an SGE context.  Used preकरोminantly at post-reset
 *	initialization.  Note in particular that we करोn't skip writing to any
 *	"sensitive bits" in the contexts the way that t3_sge_ग_लिखो_context()
 *	करोes ...
 */
अटल पूर्णांक clear_sge_ctxt(काष्ठा adapter *adap, अचिन्हित पूर्णांक id,
			  अचिन्हित पूर्णांक type)
अणु
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_DATA0, 0);
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_DATA1, 0);
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_DATA2, 0);
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_DATA3, 0);
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_MASK0, 0xffffffff);
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_MASK1, 0xffffffff);
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_MASK2, 0xffffffff);
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_MASK3, 0xffffffff);
	t3_ग_लिखो_reg(adap, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | type | V_CONTEXT(id));
	वापस t3_रुको_op_करोne(adap, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
पूर्ण

/**
 *	t3_sge_init_ecntxt - initialize an SGE egress context
 *	@adapter: the adapter to configure
 *	@id: the context id
 *	@gts_enable: whether to enable GTS क्रम the context
 *	@type: the egress context type
 *	@respq: associated response queue
 *	@base_addr: base address of queue
 *	@size: number of queue entries
 *	@token: uP token
 *	@gen: initial generation value क्रम the context
 *	@cidx: consumer poपूर्णांकer
 *
 *	Initialize an SGE egress context and make it पढ़ोy क्रम use.  If the
 *	platक्रमm allows concurrent context operations, the caller is
 *	responsible क्रम appropriate locking.
 */
पूर्णांक t3_sge_init_ecntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, पूर्णांक gts_enable,
		       क्रमागत sge_context_type type, पूर्णांक respq, u64 base_addr,
		       अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक token, पूर्णांक gen,
		       अचिन्हित पूर्णांक cidx)
अणु
	अचिन्हित पूर्णांक credits = type == SGE_CNTXT_OFLD ? 0 : FW_WR_NUM;

	अगर (base_addr & 0xfff)	/* must be 4K aligned */
		वापस -EINVAL;
	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	base_addr >>= 12;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA0, V_EC_INDEX(cidx) |
		     V_EC_CREDITS(credits) | V_EC_GTS(gts_enable));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA1, V_EC_SIZE(size) |
		     V_EC_BASE_LO(base_addr & 0xffff));
	base_addr >>= 16;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA2, base_addr);
	base_addr >>= 32;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA3,
		     V_EC_BASE_HI(base_addr & 0xf) | V_EC_RESPQ(respq) |
		     V_EC_TYPE(type) | V_EC_GEN(gen) | V_EC_UP_TOKEN(token) |
		     F_EC_VALID);
	वापस t3_sge_ग_लिखो_context(adapter, id, F_EGRESS);
पूर्ण

/**
 *	t3_sge_init_flcntxt - initialize an SGE मुक्त-buffer list context
 *	@adapter: the adapter to configure
 *	@id: the context id
 *	@gts_enable: whether to enable GTS क्रम the context
 *	@base_addr: base address of queue
 *	@size: number of queue entries
 *	@bsize: size of each buffer क्रम this queue
 *	@cong_thres: threshold to संकेत congestion to upstream producers
 *	@gen: initial generation value क्रम the context
 *	@cidx: consumer poपूर्णांकer
 *
 *	Initialize an SGE मुक्त list context and make it पढ़ोy क्रम use.  The
 *	caller is responsible क्रम ensuring only one context operation occurs
 *	at a समय.
 */
पूर्णांक t3_sge_init_flcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id,
			पूर्णांक gts_enable, u64 base_addr, अचिन्हित पूर्णांक size,
			अचिन्हित पूर्णांक bsize, अचिन्हित पूर्णांक cong_thres, पूर्णांक gen,
			अचिन्हित पूर्णांक cidx)
अणु
	अगर (base_addr & 0xfff)	/* must be 4K aligned */
		वापस -EINVAL;
	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	base_addr >>= 12;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA0, base_addr);
	base_addr >>= 32;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA1,
		     V_FL_BASE_HI((u32) base_addr) |
		     V_FL_INDEX_LO(cidx & M_FL_INDEX_LO));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA2, V_FL_SIZE(size) |
		     V_FL_GEN(gen) | V_FL_INDEX_HI(cidx >> 12) |
		     V_FL_ENTRY_SIZE_LO(bsize & M_FL_ENTRY_SIZE_LO));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA3,
		     V_FL_ENTRY_SIZE_HI(bsize >> (32 - S_FL_ENTRY_SIZE_LO)) |
		     V_FL_CONG_THRES(cong_thres) | V_FL_GTS(gts_enable));
	वापस t3_sge_ग_लिखो_context(adapter, id, F_FREELIST);
पूर्ण

/**
 *	t3_sge_init_rspcntxt - initialize an SGE response queue context
 *	@adapter: the adapter to configure
 *	@id: the context id
 *	@irq_vec_idx: MSI-X पूर्णांकerrupt vector index, 0 अगर no MSI-X, -1 अगर no IRQ
 *	@base_addr: base address of queue
 *	@size: number of queue entries
 *	@fl_thres: threshold क्रम selecting the normal or jumbo मुक्त list
 *	@gen: initial generation value क्रम the context
 *	@cidx: consumer poपूर्णांकer
 *
 *	Initialize an SGE response queue context and make it पढ़ोy क्रम use.
 *	The caller is responsible क्रम ensuring only one context operation
 *	occurs at a समय.
 */
पूर्णांक t3_sge_init_rspcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id,
			 पूर्णांक irq_vec_idx, u64 base_addr, अचिन्हित पूर्णांक size,
			 अचिन्हित पूर्णांक fl_thres, पूर्णांक gen, अचिन्हित पूर्णांक cidx)
अणु
	अचिन्हित पूर्णांक पूर्णांकr = 0;

	अगर (base_addr & 0xfff)	/* must be 4K aligned */
		वापस -EINVAL;
	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	base_addr >>= 12;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA0, V_CQ_SIZE(size) |
		     V_CQ_INDEX(cidx));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA1, base_addr);
	base_addr >>= 32;
	अगर (irq_vec_idx >= 0)
		पूर्णांकr = V_RQ_MSI_VEC(irq_vec_idx) | F_RQ_INTR_EN;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA2,
		     V_CQ_BASE_HI((u32) base_addr) | पूर्णांकr | V_RQ_GEN(gen));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA3, fl_thres);
	वापस t3_sge_ग_लिखो_context(adapter, id, F_RESPONSEQ);
पूर्ण

/**
 *	t3_sge_init_cqcntxt - initialize an SGE completion queue context
 *	@adapter: the adapter to configure
 *	@id: the context id
 *	@base_addr: base address of queue
 *	@size: number of queue entries
 *	@rspq: response queue क्रम async notअगरications
 *	@ovfl_mode: CQ overflow mode
 *	@credits: completion queue credits
 *	@credit_thres: the credit threshold
 *
 *	Initialize an SGE completion queue context and make it पढ़ोy क्रम use.
 *	The caller is responsible क्रम ensuring only one context operation
 *	occurs at a समय.
 */
पूर्णांक t3_sge_init_cqcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, u64 base_addr,
			अचिन्हित पूर्णांक size, पूर्णांक rspq, पूर्णांक ovfl_mode,
			अचिन्हित पूर्णांक credits, अचिन्हित पूर्णांक credit_thres)
अणु
	अगर (base_addr & 0xfff)	/* must be 4K aligned */
		वापस -EINVAL;
	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	base_addr >>= 12;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA0, V_CQ_SIZE(size));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA1, base_addr);
	base_addr >>= 32;
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA2,
		     V_CQ_BASE_HI((u32) base_addr) | V_CQ_RSPQ(rspq) |
		     V_CQ_GEN(1) | V_CQ_OVERFLOW_MODE(ovfl_mode) |
		     V_CQ_ERR(ovfl_mode));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA3, V_CQ_CREDITS(credits) |
		     V_CQ_CREDIT_THRES(credit_thres));
	वापस t3_sge_ग_लिखो_context(adapter, id, F_CQ);
पूर्ण

/**
 *	t3_sge_enable_ecntxt - enable/disable an SGE egress context
 *	@adapter: the adapter
 *	@id: the egress context id
 *	@enable: enable (1) or disable (0) the context
 *
 *	Enable or disable an SGE egress context.  The caller is responsible क्रम
 *	ensuring only one context operation occurs at a समय.
 */
पूर्णांक t3_sge_enable_ecntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, पूर्णांक enable)
अणु
	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK0, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK1, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK2, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK3, F_EC_VALID);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA3, V_EC_VALID(enable));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_EGRESS | V_CONTEXT(id));
	वापस t3_रुको_op_करोne(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
पूर्ण

/**
 *	t3_sge_disable_fl - disable an SGE मुक्त-buffer list
 *	@adapter: the adapter
 *	@id: the मुक्त list context id
 *
 *	Disable an SGE मुक्त-buffer list.  The caller is responsible क्रम
 *	ensuring only one context operation occurs at a समय.
 */
पूर्णांक t3_sge_disable_fl(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id)
अणु
	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK0, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK1, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK2, V_FL_SIZE(M_FL_SIZE));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK3, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA2, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_FREELIST | V_CONTEXT(id));
	वापस t3_रुको_op_करोne(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
पूर्ण

/**
 *	t3_sge_disable_rspcntxt - disable an SGE response queue
 *	@adapter: the adapter
 *	@id: the response queue context id
 *
 *	Disable an SGE response queue.  The caller is responsible क्रम
 *	ensuring only one context operation occurs at a समय.
 */
पूर्णांक t3_sge_disable_rspcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id)
अणु
	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK0, V_CQ_SIZE(M_CQ_SIZE));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK1, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK2, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK3, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA0, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_RESPONSEQ | V_CONTEXT(id));
	वापस t3_रुको_op_करोne(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
पूर्ण

/**
 *	t3_sge_disable_cqcntxt - disable an SGE completion queue
 *	@adapter: the adapter
 *	@id: the completion queue context id
 *
 *	Disable an SGE completion queue.  The caller is responsible क्रम
 *	ensuring only one context operation occurs at a समय.
 */
पूर्णांक t3_sge_disable_cqcntxt(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id)
अणु
	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK0, V_CQ_SIZE(M_CQ_SIZE));
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK1, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK2, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_MASK3, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA0, 0);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_CQ | V_CONTEXT(id));
	वापस t3_रुको_op_करोne(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
पूर्ण

/**
 *	t3_sge_cqcntxt_op - perक्रमm an operation on a completion queue context
 *	@adapter: the adapter
 *	@id: the context id
 *	@op: the operation to perक्रमm
 *	@credits: credit value to ग_लिखो
 *
 *	Perक्रमm the selected operation on an SGE completion queue context.
 *	The caller is responsible क्रम ensuring only one context operation
 *	occurs at a समय.
 */
पूर्णांक t3_sge_cqcntxt_op(काष्ठा adapter *adapter, अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक op,
		      अचिन्हित पूर्णांक credits)
अणु
	u32 val;

	अगर (t3_पढ़ो_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_DATA0, credits << 16);
	t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_CMD, V_CONTEXT_CMD_OPCODE(op) |
		     V_CONTEXT(id) | F_CQ);
	अगर (t3_रुको_op_करोne_val(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
				0, SG_CONTEXT_CMD_ATTEMPTS, 1, &val))
		वापस -EIO;

	अगर (op >= 2 && op < 7) अणु
		अगर (adapter->params.rev > 0)
			वापस G_CQ_INDEX(val);

		t3_ग_लिखो_reg(adapter, A_SG_CONTEXT_CMD,
			     V_CONTEXT_CMD_OPCODE(0) | F_CQ | V_CONTEXT(id));
		अगर (t3_रुको_op_करोne(adapter, A_SG_CONTEXT_CMD,
				    F_CONTEXT_CMD_BUSY, 0,
				    SG_CONTEXT_CMD_ATTEMPTS, 1))
			वापस -EIO;
		वापस G_CQ_INDEX(t3_पढ़ो_reg(adapter, A_SG_CONTEXT_DATA0));
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	t3_config_rss - configure Rx packet steering
 *	@adapter: the adapter
 *	@rss_config: RSS settings (written to TP_RSS_CONFIG)
 *	@cpus: values क्रम the CPU lookup table (0xff terminated)
 *	@rspq: values क्रम the response queue lookup table (0xffff terminated)
 *
 *	Programs the receive packet steering logic.  @cpus and @rspq provide
 *	the values क्रम the CPU and response queue lookup tables.  If they
 *	provide fewer values than the size of the tables the supplied values
 *	are used repeatedly until the tables are fully populated.
 */
व्योम t3_config_rss(काष्ठा adapter *adapter, अचिन्हित पूर्णांक rss_config,
		   स्थिर u8 * cpus, स्थिर u16 *rspq)
अणु
	पूर्णांक i, j, cpu_idx = 0, q_idx = 0;

	अगर (cpus)
		क्रम (i = 0; i < RSS_TABLE_SIZE; ++i) अणु
			u32 val = i << 16;

			क्रम (j = 0; j < 2; ++j) अणु
				val |= (cpus[cpu_idx++] & 0x3f) << (8 * j);
				अगर (cpus[cpu_idx] == 0xff)
					cpu_idx = 0;
			पूर्ण
			t3_ग_लिखो_reg(adapter, A_TP_RSS_LKP_TABLE, val);
		पूर्ण

	अगर (rspq)
		क्रम (i = 0; i < RSS_TABLE_SIZE; ++i) अणु
			t3_ग_लिखो_reg(adapter, A_TP_RSS_MAP_TABLE,
				     (i << 16) | rspq[q_idx++]);
			अगर (rspq[q_idx] == 0xffff)
				q_idx = 0;
		पूर्ण

	t3_ग_लिखो_reg(adapter, A_TP_RSS_CONFIG, rss_config);
पूर्ण

/**
 *	t3_tp_set_offload_mode - put TP in NIC/offload mode
 *	@adap: the adapter
 *	@enable: 1 to select offload mode, 0 क्रम regular NIC
 *
 *	Switches TP to NIC/offload mode.
 */
व्योम t3_tp_set_offload_mode(काष्ठा adapter *adap, पूर्णांक enable)
अणु
	अगर (is_offload(adap) || !enable)
		t3_set_reg_field(adap, A_TP_IN_CONFIG, F_NICMODE,
				 V_NICMODE(!enable));
पूर्ण

/**
 *	pm_num_pages - calculate the number of pages of the payload memory
 *	@mem_size: the size of the payload memory
 *	@pg_size: the size of each payload memory page
 *
 *	Calculate the number of pages, each of the given size, that fit in a
 *	memory of the specअगरied size, respecting the HW requirement that the
 *	number of pages must be a multiple of 24.
 */
अटल अंतरभूत अचिन्हित पूर्णांक pm_num_pages(अचिन्हित पूर्णांक mem_size,
					अचिन्हित पूर्णांक pg_size)
अणु
	अचिन्हित पूर्णांक n = mem_size / pg_size;

	वापस n - n % 24;
पूर्ण

#घोषणा mem_region(adap, start, size, reg) \
	t3_ग_लिखो_reg((adap), A_ ## reg, (start)); \
	start += size

/**
 *	partition_mem - partition memory and configure TP memory settings
 *	@adap: the adapter
 *	@p: the TP parameters
 *
 *	Partitions context and payload memory and configures TP's memory
 *	रेजिस्टरs.
 */
अटल व्योम partition_mem(काष्ठा adapter *adap, स्थिर काष्ठा tp_params *p)
अणु
	अचिन्हित पूर्णांक m, pकाष्ठाs, tids = t3_mc5_size(&adap->mc5);
	अचिन्हित पूर्णांक समयrs = 0, समयrs_shअगरt = 22;

	अगर (adap->params.rev > 0) अणु
		अगर (tids <= 16 * 1024) अणु
			समयrs = 1;
			समयrs_shअगरt = 16;
		पूर्ण अन्यथा अगर (tids <= 64 * 1024) अणु
			समयrs = 2;
			समयrs_shअगरt = 18;
		पूर्ण अन्यथा अगर (tids <= 256 * 1024) अणु
			समयrs = 3;
			समयrs_shअगरt = 20;
		पूर्ण
	पूर्ण

	t3_ग_लिखो_reg(adap, A_TP_PMM_SIZE,
		     p->chan_rx_size | (p->chan_tx_size >> 16));

	t3_ग_लिखो_reg(adap, A_TP_PMM_TX_BASE, 0);
	t3_ग_लिखो_reg(adap, A_TP_PMM_TX_PAGE_SIZE, p->tx_pg_size);
	t3_ग_लिखो_reg(adap, A_TP_PMM_TX_MAX_PAGE, p->tx_num_pgs);
	t3_set_reg_field(adap, A_TP_PARA_REG3, V_TXDATAACKIDX(M_TXDATAACKIDX),
			 V_TXDATAACKIDX(fls(p->tx_pg_size) - 12));

	t3_ग_लिखो_reg(adap, A_TP_PMM_RX_BASE, 0);
	t3_ग_लिखो_reg(adap, A_TP_PMM_RX_PAGE_SIZE, p->rx_pg_size);
	t3_ग_लिखो_reg(adap, A_TP_PMM_RX_MAX_PAGE, p->rx_num_pgs);

	pकाष्ठाs = p->rx_num_pgs + p->tx_num_pgs;
	/* Add a bit of headroom and make multiple of 24 */
	pकाष्ठाs += 48;
	pकाष्ठाs -= pकाष्ठाs % 24;
	t3_ग_लिखो_reg(adap, A_TP_CMM_MM_MAX_PSTRUCT, pकाष्ठाs);

	m = tids * TCB_SIZE;
	mem_region(adap, m, (64 << 10) * 64, SG_EGR_CNTX_BADDR);
	mem_region(adap, m, (64 << 10) * 64, SG_CQ_CONTEXT_BADDR);
	t3_ग_लिखो_reg(adap, A_TP_CMM_TIMER_BASE, V_CMTIMERMAXNUM(समयrs) | m);
	m += ((p->nसमयr_qs - 1) << समयrs_shअगरt) + (1 << 22);
	mem_region(adap, m, pकाष्ठाs * 64, TP_CMM_MM_BASE);
	mem_region(adap, m, 64 * (pकाष्ठाs / 24), TP_CMM_MM_PS_FLST_BASE);
	mem_region(adap, m, 64 * (p->rx_num_pgs / 24), TP_CMM_MM_RX_FLST_BASE);
	mem_region(adap, m, 64 * (p->tx_num_pgs / 24), TP_CMM_MM_TX_FLST_BASE);

	m = (m + 4095) & ~0xfff;
	t3_ग_लिखो_reg(adap, A_CIM_SDRAM_BASE_ADDR, m);
	t3_ग_लिखो_reg(adap, A_CIM_SDRAM_ADDR_SIZE, p->cm_size - m);

	tids = (p->cm_size - m - (3 << 20)) / 3072 - 32;
	m = t3_mc5_size(&adap->mc5) - adap->params.mc5.nservers -
	    adap->params.mc5.nfilters - adap->params.mc5.nroutes;
	अगर (tids < m)
		adap->params.mc5.nservers += m - tids;
पूर्ण

अटल अंतरभूत व्योम tp_wr_indirect(काष्ठा adapter *adap, अचिन्हित पूर्णांक addr,
				  u32 val)
अणु
	t3_ग_लिखो_reg(adap, A_TP_PIO_ADDR, addr);
	t3_ग_लिखो_reg(adap, A_TP_PIO_DATA, val);
पूर्ण

अटल व्योम tp_config(काष्ठा adapter *adap, स्थिर काष्ठा tp_params *p)
अणु
	t3_ग_लिखो_reg(adap, A_TP_GLOBAL_CONFIG, F_TXPACINGENABLE | F_PATHMTU |
		     F_IPCHECKSUMOFFLOAD | F_UDPCHECKSUMOFFLOAD |
		     F_TCPCHECKSUMOFFLOAD | V_IPTTL(64));
	t3_ग_लिखो_reg(adap, A_TP_TCP_OPTIONS, V_MTUDEFAULT(576) |
		     F_MTUENABLE | V_WINDOWSCALEMODE(1) |
		     V_TIMESTAMPSMODE(1) | V_SACKMODE(1) | V_SACKRX(1));
	t3_ग_लिखो_reg(adap, A_TP_DACK_CONFIG, V_AUTOSTATE3(1) |
		     V_AUTOSTATE2(1) | V_AUTOSTATE1(0) |
		     V_BYTETHRESHOLD(26880) | V_MSSTHRESHOLD(2) |
		     F_AUTOCAREFUL | F_AUTOENABLE | V_DACK_MODE(1));
	t3_set_reg_field(adap, A_TP_IN_CONFIG, F_RXFBARBPRIO | F_TXFBARBPRIO,
			 F_IPV6ENABLE | F_NICMODE);
	t3_ग_लिखो_reg(adap, A_TP_TX_RESOURCE_LIMIT, 0x18141814);
	t3_ग_लिखो_reg(adap, A_TP_PARA_REG4, 0x5050105);
	t3_set_reg_field(adap, A_TP_PARA_REG6, 0,
			 adap->params.rev > 0 ? F_ENABLEESND :
			 F_T3A_ENABLEESND);

	t3_set_reg_field(adap, A_TP_PC_CONFIG,
			 F_ENABLEEPCMDAFULL,
			 F_ENABLEOCSPIFULL |F_TXDEFERENABLE | F_HEARBEATDACK |
			 F_TXCONGESTIONMODE | F_RXCONGESTIONMODE);
	t3_set_reg_field(adap, A_TP_PC_CONFIG2, F_CHDRAFULL,
			 F_ENABLEIPV6RSS | F_ENABLENONOFDTNLSYN |
			 F_ENABLEARPMISS | F_DISBLEDAPARBIT0);
	t3_ग_लिखो_reg(adap, A_TP_PROXY_FLOW_CNTL, 1080);
	t3_ग_लिखो_reg(adap, A_TP_PROXY_FLOW_CNTL, 1000);

	अगर (adap->params.rev > 0) अणु
		tp_wr_indirect(adap, A_TP_EGRESS_CONFIG, F_REWRITEFORCETOSIZE);
		t3_set_reg_field(adap, A_TP_PARA_REG3, F_TXPACEAUTO,
				 F_TXPACEAUTO);
		t3_set_reg_field(adap, A_TP_PC_CONFIG, F_LOCKTID, F_LOCKTID);
		t3_set_reg_field(adap, A_TP_PARA_REG3, 0, F_TXPACEAUTOSTRICT);
	पूर्ण अन्यथा
		t3_set_reg_field(adap, A_TP_PARA_REG3, 0, F_TXPACEFIXED);

	अगर (adap->params.rev == T3_REV_C)
		t3_set_reg_field(adap, A_TP_PC_CONFIG,
				 V_TABLELATENCYDELTA(M_TABLELATENCYDELTA),
				 V_TABLELATENCYDELTA(4));

	t3_ग_लिखो_reg(adap, A_TP_TX_MOD_QUEUE_WEIGHT1, 0);
	t3_ग_लिखो_reg(adap, A_TP_TX_MOD_QUEUE_WEIGHT0, 0);
	t3_ग_लिखो_reg(adap, A_TP_MOD_CHANNEL_WEIGHT, 0);
	t3_ग_लिखो_reg(adap, A_TP_MOD_RATE_LIMIT, 0xf2200000);
पूर्ण

/* Desired TP समयr resolution in usec */
#घोषणा TP_TMR_RES 50

/* TCP समयr values in ms */
#घोषणा TP_DACK_TIMER 50
#घोषणा TP_RTO_MIN    250

/**
 *	tp_set_समयrs - set TP timing parameters
 *	@adap: the adapter to set
 *	@core_clk: the core घड़ी frequency in Hz
 *
 *	Set TP's timing parameters, such as the various समयr resolutions and
 *	the TCP समयr values.
 */
अटल व्योम tp_set_समयrs(काष्ठा adapter *adap, अचिन्हित पूर्णांक core_clk)
अणु
	अचिन्हित पूर्णांक tre = fls(core_clk / (1000000 / TP_TMR_RES)) - 1;
	अचिन्हित पूर्णांक dack_re = fls(core_clk / 5000) - 1;	/* 200us */
	अचिन्हित पूर्णांक tstamp_re = fls(core_clk / 1000);	/* 1ms, at least */
	अचिन्हित पूर्णांक tps = core_clk >> tre;

	t3_ग_लिखो_reg(adap, A_TP_TIMER_RESOLUTION, V_TIMERRESOLUTION(tre) |
		     V_DELAYEDACKRESOLUTION(dack_re) |
		     V_TIMESTAMPRESOLUTION(tstamp_re));
	t3_ग_लिखो_reg(adap, A_TP_DACK_TIMER,
		     (core_clk >> dack_re) / (1000 / TP_DACK_TIMER));
	t3_ग_लिखो_reg(adap, A_TP_TCP_BACKOFF_REG0, 0x3020100);
	t3_ग_लिखो_reg(adap, A_TP_TCP_BACKOFF_REG1, 0x7060504);
	t3_ग_लिखो_reg(adap, A_TP_TCP_BACKOFF_REG2, 0xb0a0908);
	t3_ग_लिखो_reg(adap, A_TP_TCP_BACKOFF_REG3, 0xf0e0d0c);
	t3_ग_लिखो_reg(adap, A_TP_SHIFT_CNT, V_SYNSHIFTMAX(6) |
		     V_RXTSHIFTMAXR1(4) | V_RXTSHIFTMAXR2(15) |
		     V_PERSHIFTBACKOFFMAX(8) | V_PERSHIFTMAX(8) |
		     V_KEEPALIVEMAX(9));

#घोषणा SECONDS * tps

	t3_ग_लिखो_reg(adap, A_TP_MSL, adap->params.rev > 0 ? 0 : 2 SECONDS);
	t3_ग_लिखो_reg(adap, A_TP_RXT_MIN, tps / (1000 / TP_RTO_MIN));
	t3_ग_लिखो_reg(adap, A_TP_RXT_MAX, 64 SECONDS);
	t3_ग_लिखो_reg(adap, A_TP_PERS_MIN, 5 SECONDS);
	t3_ग_लिखो_reg(adap, A_TP_PERS_MAX, 64 SECONDS);
	t3_ग_लिखो_reg(adap, A_TP_KEEP_IDLE, 7200 SECONDS);
	t3_ग_लिखो_reg(adap, A_TP_KEEP_INTVL, 75 SECONDS);
	t3_ग_लिखो_reg(adap, A_TP_INIT_SRTT, 3 SECONDS);
	t3_ग_लिखो_reg(adap, A_TP_FINWAIT2_TIMER, 600 SECONDS);

#अघोषित SECONDS
पूर्ण

/**
 *	t3_tp_set_coalescing_size - set receive coalescing size
 *	@adap: the adapter
 *	@size: the receive coalescing size
 *	@psh: whether a set PSH bit should deliver coalesced data
 *
 *	Set the receive coalescing size and PSH bit handling.
 */
अटल पूर्णांक t3_tp_set_coalescing_size(काष्ठा adapter *adap,
				     अचिन्हित पूर्णांक size, पूर्णांक psh)
अणु
	u32 val;

	अगर (size > MAX_RX_COALESCING_LEN)
		वापस -EINVAL;

	val = t3_पढ़ो_reg(adap, A_TP_PARA_REG3);
	val &= ~(F_RXCOALESCEENABLE | F_RXCOALESCEPSHEN);

	अगर (size) अणु
		val |= F_RXCOALESCEENABLE;
		अगर (psh)
			val |= F_RXCOALESCEPSHEN;
		size = min(MAX_RX_COALESCING_LEN, size);
		t3_ग_लिखो_reg(adap, A_TP_PARA_REG2, V_RXCOALESCESIZE(size) |
			     V_MAXRXDATA(MAX_RX_COALESCING_LEN));
	पूर्ण
	t3_ग_लिखो_reg(adap, A_TP_PARA_REG3, val);
	वापस 0;
पूर्ण

/**
 *	t3_tp_set_max_rxsize - set the max receive size
 *	@adap: the adapter
 *	@size: the max receive size
 *
 *	Set TP's max receive size.  This is the limit that applies when
 *	receive coalescing is disabled.
 */
अटल व्योम t3_tp_set_max_rxsize(काष्ठा adapter *adap, अचिन्हित पूर्णांक size)
अणु
	t3_ग_लिखो_reg(adap, A_TP_PARA_REG7,
		     V_PMMAXXFERLEN0(size) | V_PMMAXXFERLEN1(size));
पूर्ण

अटल व्योम init_mtus(अचिन्हित लघु mtus[])
अणु
	/*
	 * See draft-mathis-plpmtud-00.txt क्रम the values.  The min is 88 so
	 * it can accommodate max size TCP/IP headers when SACK and बारtamps
	 * are enabled and still have at least 8 bytes of payload.
	 */
	mtus[0] = 88;
	mtus[1] = 88;
	mtus[2] = 256;
	mtus[3] = 512;
	mtus[4] = 576;
	mtus[5] = 1024;
	mtus[6] = 1280;
	mtus[7] = 1492;
	mtus[8] = 1500;
	mtus[9] = 2002;
	mtus[10] = 2048;
	mtus[11] = 4096;
	mtus[12] = 4352;
	mtus[13] = 8192;
	mtus[14] = 9000;
	mtus[15] = 9600;
पूर्ण

/*
 * Initial congestion control parameters.
 */
अटल व्योम init_cong_ctrl(अचिन्हित लघु *a, अचिन्हित लघु *b)
अणु
	a[0] = a[1] = a[2] = a[3] = a[4] = a[5] = a[6] = a[7] = a[8] = 1;
	a[9] = 2;
	a[10] = 3;
	a[11] = 4;
	a[12] = 5;
	a[13] = 6;
	a[14] = 7;
	a[15] = 8;
	a[16] = 9;
	a[17] = 10;
	a[18] = 14;
	a[19] = 17;
	a[20] = 21;
	a[21] = 25;
	a[22] = 30;
	a[23] = 35;
	a[24] = 45;
	a[25] = 60;
	a[26] = 80;
	a[27] = 100;
	a[28] = 200;
	a[29] = 300;
	a[30] = 400;
	a[31] = 500;

	b[0] = b[1] = b[2] = b[3] = b[4] = b[5] = b[6] = b[7] = b[8] = 0;
	b[9] = b[10] = 1;
	b[11] = b[12] = 2;
	b[13] = b[14] = b[15] = b[16] = 3;
	b[17] = b[18] = b[19] = b[20] = b[21] = 4;
	b[22] = b[23] = b[24] = b[25] = b[26] = b[27] = 5;
	b[28] = b[29] = 6;
	b[30] = b[31] = 7;
पूर्ण

/* The minimum additive increment value क्रम the congestion control table */
#घोषणा CC_MIN_INCR 2U

/**
 *	t3_load_mtus - ग_लिखो the MTU and congestion control HW tables
 *	@adap: the adapter
 *	@mtus: the unrestricted values क्रम the MTU table
 *	@alpha: the values क्रम the congestion control alpha parameter
 *	@beta: the values क्रम the congestion control beta parameter
 *	@mtu_cap: the maximum permitted effective MTU
 *
 *	Write the MTU table with the supplied MTUs capping each at &mtu_cap.
 *	Update the high-speed congestion control table with the supplied alpha,
 * 	beta, and MTUs.
 */
व्योम t3_load_mtus(काष्ठा adapter *adap, अचिन्हित लघु mtus[NMTUS],
		  अचिन्हित लघु alpha[NCCTRL_WIN],
		  अचिन्हित लघु beta[NCCTRL_WIN], अचिन्हित लघु mtu_cap)
अणु
	अटल स्थिर अचिन्हित पूर्णांक avg_pkts[NCCTRL_WIN] = अणु
		2, 6, 10, 14, 20, 28, 40, 56, 80, 112, 160, 224, 320, 448, 640,
		896, 1281, 1792, 2560, 3584, 5120, 7168, 10240, 14336, 20480,
		28672, 40960, 57344, 81920, 114688, 163840, 229376
	पूर्ण;

	अचिन्हित पूर्णांक i, w;

	क्रम (i = 0; i < NMTUS; ++i) अणु
		अचिन्हित पूर्णांक mtu = min(mtus[i], mtu_cap);
		अचिन्हित पूर्णांक log2 = fls(mtu);

		अगर (!(mtu & ((1 << log2) >> 2)))	/* round */
			log2--;
		t3_ग_लिखो_reg(adap, A_TP_MTU_TABLE,
			     (i << 24) | (log2 << 16) | mtu);

		क्रम (w = 0; w < NCCTRL_WIN; ++w) अणु
			अचिन्हित पूर्णांक inc;

			inc = max(((mtu - 40) * alpha[w]) / avg_pkts[w],
				  CC_MIN_INCR);

			t3_ग_लिखो_reg(adap, A_TP_CCTRL_TABLE, (i << 21) |
				     (w << 16) | (beta[w] << 13) | inc);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	t3_tp_get_mib_stats - पढ़ो TP's MIB counters
 *	@adap: the adapter
 *	@tps: holds the वापसed counter values
 *
 *	Returns the values of TP's MIB counters.
 */
व्योम t3_tp_get_mib_stats(काष्ठा adapter *adap, काष्ठा tp_mib_stats *tps)
अणु
	t3_पढ़ो_indirect(adap, A_TP_MIB_INDEX, A_TP_MIB_RDATA, (u32 *) tps,
			 माप(*tps) / माप(u32), 0);
पूर्ण

#घोषणा ulp_region(adap, name, start, len) \
	t3_ग_लिखो_reg((adap), A_ULPRX_ ## name ## _LLIMIT, (start)); \
	t3_ग_लिखो_reg((adap), A_ULPRX_ ## name ## _ULIMIT, \
		     (start) + (len) - 1); \
	start += len

#घोषणा ulptx_region(adap, name, start, len) \
	t3_ग_लिखो_reg((adap), A_ULPTX_ ## name ## _LLIMIT, (start)); \
	t3_ग_लिखो_reg((adap), A_ULPTX_ ## name ## _ULIMIT, \
		     (start) + (len) - 1)

अटल व्योम ulp_config(काष्ठा adapter *adap, स्थिर काष्ठा tp_params *p)
अणु
	अचिन्हित पूर्णांक m = p->chan_rx_size;

	ulp_region(adap, ISCSI, m, p->chan_rx_size / 8);
	ulp_region(adap, TDDP, m, p->chan_rx_size / 8);
	ulptx_region(adap, TPT, m, p->chan_rx_size / 4);
	ulp_region(adap, STAG, m, p->chan_rx_size / 4);
	ulp_region(adap, RQ, m, p->chan_rx_size / 4);
	ulptx_region(adap, PBL, m, p->chan_rx_size / 4);
	ulp_region(adap, PBL, m, p->chan_rx_size / 4);
	t3_ग_लिखो_reg(adap, A_ULPRX_TDDP_TAGMASK, 0xffffffff);
पूर्ण

/**
 *	t3_set_proto_sram - set the contents of the protocol sram
 *	@adap: the adapter
 *	@data: the protocol image
 *
 *	Write the contents of the protocol SRAM.
 */
पूर्णांक t3_set_proto_sram(काष्ठा adapter *adap, स्थिर u8 *data)
अणु
	पूर्णांक i;
	स्थिर __be32 *buf = (स्थिर __be32 *)data;

	क्रम (i = 0; i < PROTO_SRAM_LINES; i++) अणु
		t3_ग_लिखो_reg(adap, A_TP_EMBED_OP_FIELD5, be32_to_cpu(*buf++));
		t3_ग_लिखो_reg(adap, A_TP_EMBED_OP_FIELD4, be32_to_cpu(*buf++));
		t3_ग_लिखो_reg(adap, A_TP_EMBED_OP_FIELD3, be32_to_cpu(*buf++));
		t3_ग_लिखो_reg(adap, A_TP_EMBED_OP_FIELD2, be32_to_cpu(*buf++));
		t3_ग_लिखो_reg(adap, A_TP_EMBED_OP_FIELD1, be32_to_cpu(*buf++));

		t3_ग_लिखो_reg(adap, A_TP_EMBED_OP_FIELD0, i << 1 | 1 << 31);
		अगर (t3_रुको_op_करोne(adap, A_TP_EMBED_OP_FIELD0, 1, 1, 5, 1))
			वापस -EIO;
	पूर्ण
	t3_ग_लिखो_reg(adap, A_TP_EMBED_OP_FIELD0, 0);

	वापस 0;
पूर्ण

व्योम t3_config_trace_filter(काष्ठा adapter *adapter,
			    स्थिर काष्ठा trace_params *tp, पूर्णांक filter_index,
			    पूर्णांक invert, पूर्णांक enable)
अणु
	u32 addr, key[4], mask[4];

	key[0] = tp->sport | (tp->sip << 16);
	key[1] = (tp->sip >> 16) | (tp->dport << 16);
	key[2] = tp->dip;
	key[3] = tp->proto | (tp->vlan << 8) | (tp->पूर्णांकf << 20);

	mask[0] = tp->sport_mask | (tp->sip_mask << 16);
	mask[1] = (tp->sip_mask >> 16) | (tp->dport_mask << 16);
	mask[2] = tp->dip_mask;
	mask[3] = tp->proto_mask | (tp->vlan_mask << 8) | (tp->पूर्णांकf_mask << 20);

	अगर (invert)
		key[3] |= (1 << 29);
	अगर (enable)
		key[3] |= (1 << 28);

	addr = filter_index ? A_TP_RX_TRC_KEY0 : A_TP_TX_TRC_KEY0;
	tp_wr_indirect(adapter, addr++, key[0]);
	tp_wr_indirect(adapter, addr++, mask[0]);
	tp_wr_indirect(adapter, addr++, key[1]);
	tp_wr_indirect(adapter, addr++, mask[1]);
	tp_wr_indirect(adapter, addr++, key[2]);
	tp_wr_indirect(adapter, addr++, mask[2]);
	tp_wr_indirect(adapter, addr++, key[3]);
	tp_wr_indirect(adapter, addr, mask[3]);
	t3_पढ़ो_reg(adapter, A_TP_PIO_DATA);
पूर्ण

/**
 *	t3_config_sched - configure a HW traffic scheduler
 *	@adap: the adapter
 *	@kbps: target rate in Kbps
 *	@sched: the scheduler index
 *
 *	Configure a HW scheduler क्रम the target rate
 */
पूर्णांक t3_config_sched(काष्ठा adapter *adap, अचिन्हित पूर्णांक kbps, पूर्णांक sched)
अणु
	अचिन्हित पूर्णांक v, tps, cpt, bpt, delta, mindelta = ~0;
	अचिन्हित पूर्णांक clk = adap->params.vpd.cclk * 1000;
	अचिन्हित पूर्णांक selected_cpt = 0, selected_bpt = 0;

	अगर (kbps > 0) अणु
		kbps *= 125;	/* -> bytes */
		क्रम (cpt = 1; cpt <= 255; cpt++) अणु
			tps = clk / cpt;
			bpt = (kbps + tps / 2) / tps;
			अगर (bpt > 0 && bpt <= 255) अणु
				v = bpt * tps;
				delta = v >= kbps ? v - kbps : kbps - v;
				अगर (delta <= mindelta) अणु
					mindelta = delta;
					selected_cpt = cpt;
					selected_bpt = bpt;
				पूर्ण
			पूर्ण अन्यथा अगर (selected_cpt)
				अवरोध;
		पूर्ण
		अगर (!selected_cpt)
			वापस -EINVAL;
	पूर्ण
	t3_ग_लिखो_reg(adap, A_TP_TM_PIO_ADDR,
		     A_TP_TX_MOD_Q1_Q0_RATE_LIMIT - sched / 2);
	v = t3_पढ़ो_reg(adap, A_TP_TM_PIO_DATA);
	अगर (sched & 1)
		v = (v & 0xffff) | (selected_cpt << 16) | (selected_bpt << 24);
	अन्यथा
		v = (v & 0xffff0000) | selected_cpt | (selected_bpt << 8);
	t3_ग_लिखो_reg(adap, A_TP_TM_PIO_DATA, v);
	वापस 0;
पूर्ण

अटल पूर्णांक tp_init(काष्ठा adapter *adap, स्थिर काष्ठा tp_params *p)
अणु
	पूर्णांक busy = 0;

	tp_config(adap, p);
	t3_set_vlan_accel(adap, 3, 0);

	अगर (is_offload(adap)) अणु
		tp_set_समयrs(adap, adap->params.vpd.cclk * 1000);
		t3_ग_लिखो_reg(adap, A_TP_RESET, F_FLSTINITENABLE);
		busy = t3_रुको_op_करोne(adap, A_TP_RESET, F_FLSTINITENABLE,
				       0, 1000, 5);
		अगर (busy)
			CH_ERR(adap, "TP initialization timed out\n");
	पूर्ण

	अगर (!busy)
		t3_ग_लिखो_reg(adap, A_TP_RESET, F_TPRESET);
	वापस busy;
पूर्ण

/*
 * Perक्रमm the bits of HW initialization that are dependent on the Tx
 * channels being used.
 */
अटल व्योम chan_init_hw(काष्ठा adapter *adap, अचिन्हित पूर्णांक chan_map)
अणु
	पूर्णांक i;

	अगर (chan_map != 3) अणु                                 /* one channel */
		t3_set_reg_field(adap, A_ULPRX_CTL, F_ROUND_ROBIN, 0);
		t3_set_reg_field(adap, A_ULPTX_CONFIG, F_CFG_RR_ARB, 0);
		t3_ग_लिखो_reg(adap, A_MPS_CFG, F_TPRXPORTEN | F_ENFORCEPKT |
			     (chan_map == 1 ? F_TPTXPORT0EN | F_PORT0ACTIVE :
					      F_TPTXPORT1EN | F_PORT1ACTIVE));
		t3_ग_लिखो_reg(adap, A_PM1_TX_CFG,
			     chan_map == 1 ? 0xffffffff : 0);
	पूर्ण अन्यथा अणु                                             /* two channels */
		t3_set_reg_field(adap, A_ULPRX_CTL, 0, F_ROUND_ROBIN);
		t3_set_reg_field(adap, A_ULPTX_CONFIG, 0, F_CFG_RR_ARB);
		t3_ग_लिखो_reg(adap, A_ULPTX_DMA_WEIGHT,
			     V_D1_WEIGHT(16) | V_D0_WEIGHT(16));
		t3_ग_लिखो_reg(adap, A_MPS_CFG, F_TPTXPORT0EN | F_TPTXPORT1EN |
			     F_TPRXPORTEN | F_PORT0ACTIVE | F_PORT1ACTIVE |
			     F_ENFORCEPKT);
		t3_ग_लिखो_reg(adap, A_PM1_TX_CFG, 0x80008000);
		t3_set_reg_field(adap, A_TP_PC_CONFIG, 0, F_TXTOSQUEUEMAPMODE);
		t3_ग_लिखो_reg(adap, A_TP_TX_MOD_QUEUE_REQ_MAP,
			     V_TX_MOD_QUEUE_REQ_MAP(0xaa));
		क्रम (i = 0; i < 16; i++)
			t3_ग_लिखो_reg(adap, A_TP_TX_MOD_QUE_TABLE,
				     (i << 16) | 0x1010);
	पूर्ण
पूर्ण

अटल पूर्णांक calibrate_xgm(काष्ठा adapter *adapter)
अणु
	अगर (uses_xaui(adapter)) अणु
		अचिन्हित पूर्णांक v, i;

		क्रम (i = 0; i < 5; ++i) अणु
			t3_ग_लिखो_reg(adapter, A_XGM_XAUI_IMP, 0);
			t3_पढ़ो_reg(adapter, A_XGM_XAUI_IMP);
			msleep(1);
			v = t3_पढ़ो_reg(adapter, A_XGM_XAUI_IMP);
			अगर (!(v & (F_XGM_CALFAULT | F_CALBUSY))) अणु
				t3_ग_लिखो_reg(adapter, A_XGM_XAUI_IMP,
					     V_XAUIIMP(G_CALIMP(v) >> 2));
				वापस 0;
			पूर्ण
		पूर्ण
		CH_ERR(adapter, "MAC calibration failed\n");
		वापस -1;
	पूर्ण अन्यथा अणु
		t3_ग_लिखो_reg(adapter, A_XGM_RGMII_IMP,
			     V_RGMIIIMPPD(2) | V_RGMIIIMPPU(3));
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, F_XGM_IMPSETUPDATE,
				 F_XGM_IMPSETUPDATE);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम calibrate_xgm_t3b(काष्ठा adapter *adapter)
अणु
	अगर (!uses_xaui(adapter)) अणु
		t3_ग_लिखो_reg(adapter, A_XGM_RGMII_IMP, F_CALRESET |
			     F_CALUPDATE | V_RGMIIIMPPD(2) | V_RGMIIIMPPU(3));
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, F_CALRESET, 0);
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, 0,
				 F_XGM_IMPSETUPDATE);
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, F_XGM_IMPSETUPDATE,
				 0);
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, F_CALUPDATE, 0);
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, 0, F_CALUPDATE);
	पूर्ण
पूर्ण

काष्ठा mc7_timing_params अणु
	अचिन्हित अक्षर ActToPreDly;
	अचिन्हित अक्षर ActToRdWrDly;
	अचिन्हित अक्षर PreCyc;
	अचिन्हित अक्षर RefCyc[5];
	अचिन्हित अक्षर BkCyc;
	अचिन्हित अक्षर WrToRdDly;
	अचिन्हित अक्षर RdToWrDly;
पूर्ण;

/*
 * Write a value to a रेजिस्टर and check that the ग_लिखो completed.  These
 * ग_लिखोs normally complete in a cycle or two, so one पढ़ो should suffice.
 * The very first पढ़ो exists to flush the posted ग_लिखो to the device.
 */
अटल पूर्णांक wrreg_रुको(काष्ठा adapter *adapter, अचिन्हित पूर्णांक addr, u32 val)
अणु
	t3_ग_लिखो_reg(adapter, addr, val);
	t3_पढ़ो_reg(adapter, addr);	/* flush */
	अगर (!(t3_पढ़ो_reg(adapter, addr) & F_BUSY))
		वापस 0;
	CH_ERR(adapter, "write to MC7 register 0x%x timed out\n", addr);
	वापस -EIO;
पूर्ण

अटल पूर्णांक mc7_init(काष्ठा mc7 *mc7, अचिन्हित पूर्णांक mc7_घड़ी, पूर्णांक mem_type)
अणु
	अटल स्थिर अचिन्हित पूर्णांक mc7_mode[] = अणु
		0x632, 0x642, 0x652, 0x432, 0x442
	पूर्ण;
	अटल स्थिर काष्ठा mc7_timing_params mc7_timings[] = अणु
		अणु12, 3, 4, अणु20, 28, 34, 52, 0पूर्ण, 15, 6, 4पूर्ण,
		अणु12, 4, 5, अणु20, 28, 34, 52, 0पूर्ण, 16, 7, 4पूर्ण,
		अणु12, 5, 6, अणु20, 28, 34, 52, 0पूर्ण, 17, 8, 4पूर्ण,
		अणु9, 3, 4, अणु15, 21, 26, 39, 0पूर्ण, 12, 6, 4पूर्ण,
		अणु9, 4, 5, अणु15, 21, 26, 39, 0पूर्ण, 13, 7, 4पूर्ण
	पूर्ण;

	u32 val;
	अचिन्हित पूर्णांक width, density, slow, attempts;
	काष्ठा adapter *adapter = mc7->adapter;
	स्थिर काष्ठा mc7_timing_params *p = &mc7_timings[mem_type];

	अगर (!mc7->size)
		वापस 0;

	val = t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CFG);
	slow = val & F_SLOW;
	width = G_WIDTH(val);
	density = G_DEN(val);

	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_CFG, val | F_IFEN);
	val = t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CFG);	/* flush */
	msleep(1);

	अगर (!slow) अणु
		t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_CAL, F_SGL_CAL_EN);
		t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CAL);
		msleep(1);
		अगर (t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CAL) &
		    (F_BUSY | F_SGL_CAL_EN | F_CAL_FAULT)) अणु
			CH_ERR(adapter, "%s MC7 calibration timed out\n",
			       mc7->name);
			जाओ out_fail;
		पूर्ण
	पूर्ण

	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_PARM,
		     V_ACTTOPREDLY(p->ActToPreDly) |
		     V_ACTTORDWRDLY(p->ActToRdWrDly) | V_PRECYC(p->PreCyc) |
		     V_REFCYC(p->RefCyc[density]) | V_BKCYC(p->BkCyc) |
		     V_WRTORDDLY(p->WrToRdDly) | V_RDTOWRDLY(p->RdToWrDly));

	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_CFG,
		     val | F_CLKEN | F_TERM150);
	t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CFG);	/* flush */

	अगर (!slow)
		t3_set_reg_field(adapter, mc7->offset + A_MC7_DLL, F_DLLENB,
				 F_DLLENB);
	udelay(1);

	val = slow ? 3 : 6;
	अगर (wrreg_रुको(adapter, mc7->offset + A_MC7_PRE, 0) ||
	    wrreg_रुको(adapter, mc7->offset + A_MC7_EXT_MODE2, 0) ||
	    wrreg_रुको(adapter, mc7->offset + A_MC7_EXT_MODE3, 0) ||
	    wrreg_रुको(adapter, mc7->offset + A_MC7_EXT_MODE1, val))
		जाओ out_fail;

	अगर (!slow) अणु
		t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_MODE, 0x100);
		t3_set_reg_field(adapter, mc7->offset + A_MC7_DLL, F_DLLRST, 0);
		udelay(5);
	पूर्ण

	अगर (wrreg_रुको(adapter, mc7->offset + A_MC7_PRE, 0) ||
	    wrreg_रुको(adapter, mc7->offset + A_MC7_REF, 0) ||
	    wrreg_रुको(adapter, mc7->offset + A_MC7_REF, 0) ||
	    wrreg_रुको(adapter, mc7->offset + A_MC7_MODE,
		       mc7_mode[mem_type]) ||
	    wrreg_रुको(adapter, mc7->offset + A_MC7_EXT_MODE1, val | 0x380) ||
	    wrreg_रुको(adapter, mc7->offset + A_MC7_EXT_MODE1, val))
		जाओ out_fail;

	/* घड़ी value is in KHz */
	mc7_घड़ी = mc7_घड़ी * 7812 + mc7_घड़ी / 2;	/* ns */
	mc7_घड़ी /= 1000000;	/* KHz->MHz, ns->us */

	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_REF,
		     F_PERREFEN | V_PREREFDIV(mc7_घड़ी));
	t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_REF);	/* flush */

	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_ECC, F_ECCGENEN | F_ECCCHKEN);
	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_BIST_DATA, 0);
	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_BIST_ADDR_BEG, 0);
	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_BIST_ADDR_END,
		     (mc7->size << width) - 1);
	t3_ग_लिखो_reg(adapter, mc7->offset + A_MC7_BIST_OP, V_OP(1));
	t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_BIST_OP);	/* flush */

	attempts = 50;
	करो अणु
		msleep(250);
		val = t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_BIST_OP);
	पूर्ण जबतक ((val & F_BUSY) && --attempts);
	अगर (val & F_BUSY) अणु
		CH_ERR(adapter, "%s MC7 BIST timed out\n", mc7->name);
		जाओ out_fail;
	पूर्ण

	/* Enable normal memory accesses. */
	t3_set_reg_field(adapter, mc7->offset + A_MC7_CFG, 0, F_RDY);
	वापस 0;

out_fail:
	वापस -1;
पूर्ण

अटल व्योम config_pcie(काष्ठा adapter *adap)
अणु
	अटल स्थिर u16 ack_lat[4][6] = अणु
		अणु237, 416, 559, 1071, 2095, 4143पूर्ण,
		अणु128, 217, 289, 545, 1057, 2081पूर्ण,
		अणु73, 118, 154, 282, 538, 1050पूर्ण,
		अणु67, 107, 86, 150, 278, 534पूर्ण
	पूर्ण;
	अटल स्थिर u16 rpl_पंचांगr[4][6] = अणु
		अणु711, 1248, 1677, 3213, 6285, 12429पूर्ण,
		अणु384, 651, 867, 1635, 3171, 6243पूर्ण,
		अणु219, 354, 462, 846, 1614, 3150पूर्ण,
		अणु201, 321, 258, 450, 834, 1602पूर्ण
	पूर्ण;

	u16 val, devid;
	अचिन्हित पूर्णांक log2_width, pldsize;
	अचिन्हित पूर्णांक fst_trn_rx, fst_trn_tx, acklat, rpllmt;

	pcie_capability_पढ़ो_word(adap->pdev, PCI_EXP_DEVCTL, &val);
	pldsize = (val & PCI_EXP_DEVCTL_PAYLOAD) >> 5;

	pci_पढ़ो_config_word(adap->pdev, 0x2, &devid);
	अगर (devid == 0x37) अणु
		pcie_capability_ग_लिखो_word(adap->pdev, PCI_EXP_DEVCTL,
					   val & ~PCI_EXP_DEVCTL_READRQ &
					   ~PCI_EXP_DEVCTL_PAYLOAD);
		pldsize = 0;
	पूर्ण

	pcie_capability_पढ़ो_word(adap->pdev, PCI_EXP_LNKCTL, &val);

	fst_trn_tx = G_NUMFSTTRNSEQ(t3_पढ़ो_reg(adap, A_PCIE_PEX_CTRL0));
	fst_trn_rx = adap->params.rev == 0 ? fst_trn_tx :
	    G_NUMFSTTRNSEQRX(t3_पढ़ो_reg(adap, A_PCIE_MODE));
	log2_width = fls(adap->params.pci.width) - 1;
	acklat = ack_lat[log2_width][pldsize];
	अगर (val & PCI_EXP_LNKCTL_ASPM_L0S)	/* check LOsEnable */
		acklat += fst_trn_tx * 4;
	rpllmt = rpl_पंचांगr[log2_width][pldsize] + fst_trn_rx * 4;

	अगर (adap->params.rev == 0)
		t3_set_reg_field(adap, A_PCIE_PEX_CTRL1,
				 V_T3A_ACKLAT(M_T3A_ACKLAT),
				 V_T3A_ACKLAT(acklat));
	अन्यथा
		t3_set_reg_field(adap, A_PCIE_PEX_CTRL1, V_ACKLAT(M_ACKLAT),
				 V_ACKLAT(acklat));

	t3_set_reg_field(adap, A_PCIE_PEX_CTRL0, V_REPLAYLMT(M_REPLAYLMT),
			 V_REPLAYLMT(rpllmt));

	t3_ग_लिखो_reg(adap, A_PCIE_PEX_ERR, 0xffffffff);
	t3_set_reg_field(adap, A_PCIE_CFG, 0,
			 F_ENABLELINKDWNDRST | F_ENABLELINKDOWNRST |
			 F_PCIE_DMASTOPEN | F_PCIE_CLIDECEN);
पूर्ण

/*
 * Initialize and configure T3 HW modules.  This perक्रमms the
 * initialization steps that need to be करोne once after a card is reset.
 * MAC and PHY initialization is handled separarely whenever a port is enabled.
 *
 * fw_params are passed to FW and their value is platक्रमm dependent.  Only the
 * top 8 bits are available क्रम use, the rest must be 0.
 */
पूर्णांक t3_init_hw(काष्ठा adapter *adapter, u32 fw_params)
अणु
	पूर्णांक err = -EIO, attempts, i;
	स्थिर काष्ठा vpd_params *vpd = &adapter->params.vpd;

	अगर (adapter->params.rev > 0)
		calibrate_xgm_t3b(adapter);
	अन्यथा अगर (calibrate_xgm(adapter))
		जाओ out_err;

	अगर (vpd->mclk) अणु
		partition_mem(adapter, &adapter->params.tp);

		अगर (mc7_init(&adapter->pmrx, vpd->mclk, vpd->mem_timing) ||
		    mc7_init(&adapter->pmtx, vpd->mclk, vpd->mem_timing) ||
		    mc7_init(&adapter->cm, vpd->mclk, vpd->mem_timing) ||
		    t3_mc5_init(&adapter->mc5, adapter->params.mc5.nservers,
				adapter->params.mc5.nfilters,
				adapter->params.mc5.nroutes))
			जाओ out_err;

		क्रम (i = 0; i < 32; i++)
			अगर (clear_sge_ctxt(adapter, i, F_CQ))
				जाओ out_err;
	पूर्ण

	अगर (tp_init(adapter, &adapter->params.tp))
		जाओ out_err;

	t3_tp_set_coalescing_size(adapter,
				  min(adapter->params.sge.max_pkt_size,
				      MAX_RX_COALESCING_LEN), 1);
	t3_tp_set_max_rxsize(adapter,
			     min(adapter->params.sge.max_pkt_size, 16384U));
	ulp_config(adapter, &adapter->params.tp);

	अगर (is_pcie(adapter))
		config_pcie(adapter);
	अन्यथा
		t3_set_reg_field(adapter, A_PCIX_CFG, 0,
				 F_DMASTOPEN | F_CLIDECEN);

	अगर (adapter->params.rev == T3_REV_C)
		t3_set_reg_field(adapter, A_ULPTX_CONFIG, 0,
				 F_CFG_CQE_SOP_MASK);

	t3_ग_लिखो_reg(adapter, A_PM1_RX_CFG, 0xffffffff);
	t3_ग_लिखो_reg(adapter, A_PM1_RX_MODE, 0);
	t3_ग_लिखो_reg(adapter, A_PM1_TX_MODE, 0);
	chan_init_hw(adapter, adapter->params.chan_map);
	t3_sge_init(adapter, &adapter->params.sge);
	t3_set_reg_field(adapter, A_PL_RST, 0, F_FATALPERREN);

	t3_ग_लिखो_reg(adapter, A_T3DBG_GPIO_ACT_LOW, calc_gpio_पूर्णांकr(adapter));

	t3_ग_लिखो_reg(adapter, A_CIM_HOST_ACC_DATA, vpd->uclk | fw_params);
	t3_ग_लिखो_reg(adapter, A_CIM_BOOT_CFG,
		     V_BOOTADDR(FW_FLASH_BOOT_ADDR >> 2));
	t3_पढ़ो_reg(adapter, A_CIM_BOOT_CFG);	/* flush */

	attempts = 100;
	करो अणु			/* रुको क्रम uP to initialize */
		msleep(20);
	पूर्ण जबतक (t3_पढ़ो_reg(adapter, A_CIM_HOST_ACC_DATA) && --attempts);
	अगर (!attempts) अणु
		CH_ERR(adapter, "uP initialization timed out\n");
		जाओ out_err;
	पूर्ण

	err = 0;
out_err:
	वापस err;
पूर्ण

/**
 *	get_pci_mode - determine a card's PCI mode
 *	@adapter: the adapter
 *	@p: where to store the PCI settings
 *
 *	Determines a card's PCI mode and associated parameters, such as speed
 *	and width.
 */
अटल व्योम get_pci_mode(काष्ठा adapter *adapter, काष्ठा pci_params *p)
अणु
	अटल अचिन्हित लघु speed_map[] = अणु 33, 66, 100, 133 पूर्ण;
	u32 pci_mode;

	अगर (pci_is_pcie(adapter->pdev)) अणु
		u16 val;

		p->variant = PCI_VARIANT_PCIE;
		pcie_capability_पढ़ो_word(adapter->pdev, PCI_EXP_LNKSTA, &val);
		p->width = (val >> 4) & 0x3f;
		वापस;
	पूर्ण

	pci_mode = t3_पढ़ो_reg(adapter, A_PCIX_MODE);
	p->speed = speed_map[G_PCLKRANGE(pci_mode)];
	p->width = (pci_mode & F_64BIT) ? 64 : 32;
	pci_mode = G_PCIXINITPAT(pci_mode);
	अगर (pci_mode == 0)
		p->variant = PCI_VARIANT_PCI;
	अन्यथा अगर (pci_mode < 4)
		p->variant = PCI_VARIANT_PCIX_MODE1_PARITY;
	अन्यथा अगर (pci_mode < 8)
		p->variant = PCI_VARIANT_PCIX_MODE1_ECC;
	अन्यथा
		p->variant = PCI_VARIANT_PCIX_266_MODE2;
पूर्ण

/**
 *	init_link_config - initialize a link's SW state
 *	@lc: काष्ठाure holding the link state
 *	@caps: inक्रमmation about the current card
 *
 *	Initializes the SW state मुख्यtained क्रम each link, including the link's
 *	capabilities and शेष speed/duplex/flow-control/स्वतःnegotiation
 *	settings.
 */
अटल व्योम init_link_config(काष्ठा link_config *lc, अचिन्हित पूर्णांक caps)
अणु
	lc->supported = caps;
	lc->requested_speed = lc->speed = SPEED_INVALID;
	lc->requested_duplex = lc->duplex = DUPLEX_INVALID;
	lc->requested_fc = lc->fc = PAUSE_RX | PAUSE_TX;
	अगर (lc->supported & SUPPORTED_Autoneg) अणु
		lc->advertising = lc->supported;
		lc->स्वतःneg = AUTONEG_ENABLE;
		lc->requested_fc |= PAUSE_AUTONEG;
	पूर्ण अन्यथा अणु
		lc->advertising = 0;
		lc->स्वतःneg = AUTONEG_DISABLE;
	पूर्ण
पूर्ण

/**
 *	mc7_calc_size - calculate MC7 memory size
 *	@cfg: the MC7 configuration
 *
 *	Calculates the size of an MC7 memory in bytes from the value of its
 *	configuration रेजिस्टर.
 */
अटल अचिन्हित पूर्णांक mc7_calc_size(u32 cfg)
अणु
	अचिन्हित पूर्णांक width = G_WIDTH(cfg);
	अचिन्हित पूर्णांक banks = !!(cfg & F_BKS) + 1;
	अचिन्हित पूर्णांक org = !!(cfg & F_ORG) + 1;
	अचिन्हित पूर्णांक density = G_DEN(cfg);
	अचिन्हित पूर्णांक MBs = ((256 << density) * banks) / (org << width);

	वापस MBs << 20;
पूर्ण

अटल व्योम mc7_prep(काष्ठा adapter *adapter, काष्ठा mc7 *mc7,
		     अचिन्हित पूर्णांक base_addr, स्थिर अक्षर *name)
अणु
	u32 cfg;

	mc7->adapter = adapter;
	mc7->name = name;
	mc7->offset = base_addr - MC7_PMRX_BASE_ADDR;
	cfg = t3_पढ़ो_reg(adapter, mc7->offset + A_MC7_CFG);
	mc7->size = G_DEN(cfg) == M_DEN ? 0 : mc7_calc_size(cfg);
	mc7->width = G_WIDTH(cfg);
पूर्ण

अटल व्योम mac_prep(काष्ठा cmac *mac, काष्ठा adapter *adapter, पूर्णांक index)
अणु
	u16 devid;

	mac->adapter = adapter;
	pci_पढ़ो_config_word(adapter->pdev, 0x2, &devid);

	अगर (devid == 0x37 && !adapter->params.vpd.xauicfg[1])
		index = 0;
	mac->offset = (XGMAC0_1_BASE_ADDR - XGMAC0_0_BASE_ADDR) * index;
	mac->nucast = 1;

	अगर (adapter->params.rev == 0 && uses_xaui(adapter)) अणु
		t3_ग_लिखो_reg(adapter, A_XGM_SERDES_CTRL + mac->offset,
			     is_10G(adapter) ? 0x2901c04 : 0x2301c04);
		t3_set_reg_field(adapter, A_XGM_PORT_CFG + mac->offset,
				 F_ENRGMII, 0);
	पूर्ण
पूर्ण

अटल व्योम early_hw_init(काष्ठा adapter *adapter,
			  स्थिर काष्ठा adapter_info *ai)
अणु
	u32 val = V_PORTSPEED(is_10G(adapter) ? 3 : 2);

	mi1_init(adapter, ai);
	t3_ग_लिखो_reg(adapter, A_I2C_CFG,	/* set क्रम 80KHz */
		     V_I2C_CLKDIV(adapter->params.vpd.cclk / 80 - 1));
	t3_ग_लिखो_reg(adapter, A_T3DBG_GPIO_EN,
		     ai->gpio_out | F_GPIO0_OEN | F_GPIO0_OUT_VAL);
	t3_ग_लिखो_reg(adapter, A_MC5_DB_SERVER_INDEX, 0);
	t3_ग_लिखो_reg(adapter, A_SG_OCO_BASE, V_BASE1(0xfff));

	अगर (adapter->params.rev == 0 || !uses_xaui(adapter))
		val |= F_ENRGMII;

	/* Enable MAC घड़ीs so we can access the रेजिस्टरs */
	t3_ग_लिखो_reg(adapter, A_XGM_PORT_CFG, val);
	t3_पढ़ो_reg(adapter, A_XGM_PORT_CFG);

	val |= F_CLKDIVRESET_;
	t3_ग_लिखो_reg(adapter, A_XGM_PORT_CFG, val);
	t3_पढ़ो_reg(adapter, A_XGM_PORT_CFG);
	t3_ग_लिखो_reg(adapter, XGM_REG(A_XGM_PORT_CFG, 1), val);
	t3_पढ़ो_reg(adapter, A_XGM_PORT_CFG);
पूर्ण

/*
 * Reset the adapter.
 * Older PCIe cards lose their config space during reset, PCI-X
 * ones करोn't.
 */
पूर्णांक t3_reset_adapter(काष्ठा adapter *adapter)
अणु
	पूर्णांक i, save_and_restore_pcie =
	    adapter->params.rev < T3_REV_B2 && is_pcie(adapter);
	uपूर्णांक16_t devid = 0;

	अगर (save_and_restore_pcie)
		pci_save_state(adapter->pdev);
	t3_ग_लिखो_reg(adapter, A_PL_RST, F_CRSTWRM | F_CRSTWRMMODE);

	/*
	 * Delay. Give Some समय to device to reset fully.
	 * XXX The delay समय should be modअगरied.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		msleep(50);
		pci_पढ़ो_config_word(adapter->pdev, 0x00, &devid);
		अगर (devid == 0x1425)
			अवरोध;
	पूर्ण

	अगर (devid != 0x1425)
		वापस -1;

	अगर (save_and_restore_pcie)
		pci_restore_state(adapter->pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक init_parity(काष्ठा adapter *adap)
अणु
	पूर्णांक i, err, addr;

	अगर (t3_पढ़ो_reg(adap, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		वापस -EBUSY;

	क्रम (err = i = 0; !err && i < 16; i++)
		err = clear_sge_ctxt(adap, i, F_EGRESS);
	क्रम (i = 0xfff0; !err && i <= 0xffff; i++)
		err = clear_sge_ctxt(adap, i, F_EGRESS);
	क्रम (i = 0; !err && i < SGE_QSETS; i++)
		err = clear_sge_ctxt(adap, i, F_RESPONSEQ);
	अगर (err)
		वापस err;

	t3_ग_लिखो_reg(adap, A_CIM_IBQ_DBG_DATA, 0);
	क्रम (i = 0; i < 4; i++)
		क्रम (addr = 0; addr <= M_IBQDBGADDR; addr++) अणु
			t3_ग_लिखो_reg(adap, A_CIM_IBQ_DBG_CFG, F_IBQDBGEN |
				     F_IBQDBGWR | V_IBQDBGQID(i) |
				     V_IBQDBGADDR(addr));
			err = t3_रुको_op_करोne(adap, A_CIM_IBQ_DBG_CFG,
					      F_IBQDBGBUSY, 0, 2, 1);
			अगर (err)
				वापस err;
		पूर्ण
	वापस 0;
पूर्ण

/*
 * Initialize adapter SW state क्रम the various HW modules, set initial values
 * क्रम some adapter tunables, take PHYs out of reset, and initialize the MDIO
 * पूर्णांकerface.
 */
पूर्णांक t3_prep_adapter(काष्ठा adapter *adapter, स्थिर काष्ठा adapter_info *ai,
		    पूर्णांक reset)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक i, j = -1;

	get_pci_mode(adapter, &adapter->params.pci);

	adapter->params.info = ai;
	adapter->params.nports = ai->nports0 + ai->nports1;
	adapter->params.chan_map = (!!ai->nports0) | (!!ai->nports1 << 1);
	adapter->params.rev = t3_पढ़ो_reg(adapter, A_PL_REV);
	/*
	 * We used to only run the "adapter check task" once a second अगर
	 * we had PHYs which didn't support पूर्णांकerrupts (we would check
	 * their link status once a second).  Now we check other conditions
	 * in that routine which could potentially impose a very high
	 * पूर्णांकerrupt load on the प्रणाली.  As such, we now always scan the
	 * adapter state once a second ...
	 */
	adapter->params.linkpoll_period = 10;
	adapter->params.stats_update_period = is_10G(adapter) ?
	    MAC_STATS_ACCUM_SECS : (MAC_STATS_ACCUM_SECS * 10);
	adapter->params.pci.vpd_cap_addr =
	    pci_find_capability(adapter->pdev, PCI_CAP_ID_VPD);
	ret = get_vpd_params(adapter, &adapter->params.vpd);
	अगर (ret < 0)
		वापस ret;

	अगर (reset && t3_reset_adapter(adapter))
		वापस -1;

	t3_sge_prep(adapter, &adapter->params.sge);

	अगर (adapter->params.vpd.mclk) अणु
		काष्ठा tp_params *p = &adapter->params.tp;

		mc7_prep(adapter, &adapter->pmrx, MC7_PMRX_BASE_ADDR, "PMRX");
		mc7_prep(adapter, &adapter->pmtx, MC7_PMTX_BASE_ADDR, "PMTX");
		mc7_prep(adapter, &adapter->cm, MC7_CM_BASE_ADDR, "CM");

		p->nchan = adapter->params.chan_map == 3 ? 2 : 1;
		p->pmrx_size = t3_mc7_size(&adapter->pmrx);
		p->pmtx_size = t3_mc7_size(&adapter->pmtx);
		p->cm_size = t3_mc7_size(&adapter->cm);
		p->chan_rx_size = p->pmrx_size / 2;	/* only 1 Rx channel */
		p->chan_tx_size = p->pmtx_size / p->nchan;
		p->rx_pg_size = 64 * 1024;
		p->tx_pg_size = is_10G(adapter) ? 64 * 1024 : 16 * 1024;
		p->rx_num_pgs = pm_num_pages(p->chan_rx_size, p->rx_pg_size);
		p->tx_num_pgs = pm_num_pages(p->chan_tx_size, p->tx_pg_size);
		p->nसमयr_qs = p->cm_size >= (128 << 20) ||
		    adapter->params.rev > 0 ? 12 : 6;
	पूर्ण

	adapter->params.offload = t3_mc7_size(&adapter->pmrx) &&
				  t3_mc7_size(&adapter->pmtx) &&
				  t3_mc7_size(&adapter->cm);

	अगर (is_offload(adapter)) अणु
		adapter->params.mc5.nservers = DEFAULT_NSERVERS;
		adapter->params.mc5.nfilters = adapter->params.rev > 0 ?
		    DEFAULT_NFILTERS : 0;
		adapter->params.mc5.nroutes = 0;
		t3_mc5_prep(adapter, &adapter->mc5, MC5_MODE_144_BIT);

		init_mtus(adapter->params.mtus);
		init_cong_ctrl(adapter->params.a_wnd, adapter->params.b_wnd);
	पूर्ण

	early_hw_init(adapter, ai);
	ret = init_parity(adapter);
	अगर (ret)
		वापस ret;

	क्रम_each_port(adapter, i) अणु
		u8 hw_addr[6];
		स्थिर काष्ठा port_type_info *pti;
		काष्ठा port_info *p = adap2pinfo(adapter, i);

		जबतक (!adapter->params.vpd.port_type[++j])
			;

		pti = &port_types[adapter->params.vpd.port_type[j]];
		अगर (!pti->phy_prep) अणु
			CH_ALERT(adapter, "Invalid port type index %d\n",
				 adapter->params.vpd.port_type[j]);
			वापस -EINVAL;
		पूर्ण

		p->phy.mdio.dev = adapter->port[i];
		ret = pti->phy_prep(&p->phy, adapter, ai->phy_base_addr + j,
				    ai->mdio_ops);
		अगर (ret)
			वापस ret;
		mac_prep(&p->mac, adapter, j);

		/*
		 * The VPD EEPROM stores the base Ethernet address क्रम the
		 * card.  A port's address is derived from the base by adding
		 * the port's index to the base's low octet.
		 */
		स_नकल(hw_addr, adapter->params.vpd.eth_base, 5);
		hw_addr[5] = adapter->params.vpd.eth_base[5] + i;

		स_नकल(adapter->port[i]->dev_addr, hw_addr,
		       ETH_ALEN);
		init_link_config(&p->link_config, p->phy.caps);
		p->phy.ops->घातer_करोwn(&p->phy, 1);

		/*
		 * If the PHY करोesn't support पूर्णांकerrupts क्रम link status
		 * changes, schedule a scan of the adapter links at least
		 * once a second.
		 */
		अगर (!(p->phy.caps & SUPPORTED_IRQ) &&
		    adapter->params.linkpoll_period > 10)
			adapter->params.linkpoll_period = 10;
	पूर्ण

	वापस 0;
पूर्ण

व्योम t3_led_पढ़ोy(काष्ठा adapter *adapter)
अणु
	t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, F_GPIO0_OUT_VAL,
			 F_GPIO0_OUT_VAL);
पूर्ण

पूर्णांक t3_replay_prep_adapter(काष्ठा adapter *adapter)
अणु
	स्थिर काष्ठा adapter_info *ai = adapter->params.info;
	अचिन्हित पूर्णांक i, j = -1;
	पूर्णांक ret;

	early_hw_init(adapter, ai);
	ret = init_parity(adapter);
	अगर (ret)
		वापस ret;

	क्रम_each_port(adapter, i) अणु
		स्थिर काष्ठा port_type_info *pti;
		काष्ठा port_info *p = adap2pinfo(adapter, i);

		जबतक (!adapter->params.vpd.port_type[++j])
			;

		pti = &port_types[adapter->params.vpd.port_type[j]];
		ret = pti->phy_prep(&p->phy, adapter, p->phy.mdio.prtad, शून्य);
		अगर (ret)
			वापस ret;
		p->phy.ops->घातer_करोwn(&p->phy, 1);
	पूर्ण

	वापस 0;
पूर्ण

