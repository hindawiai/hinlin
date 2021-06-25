<शैली गुरु>
/*
 * Copyright (c) 2005-2008 Chelsio, Inc. All rights reserved.
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

क्रमागत अणु
	AEL100X_TX_CONFIG1 = 0xc002,
	AEL1002_PWR_DOWN_HI = 0xc011,
	AEL1002_PWR_DOWN_LO = 0xc012,
	AEL1002_XFI_EQL = 0xc015,
	AEL1002_LB_EN = 0xc017,
	AEL_OPT_SETTINGS = 0xc017,
	AEL_I2C_CTRL = 0xc30a,
	AEL_I2C_DATA = 0xc30b,
	AEL_I2C_STAT = 0xc30c,
	AEL2005_GPIO_CTRL = 0xc214,
	AEL2005_GPIO_STAT = 0xc215,

	AEL2020_GPIO_INTR   = 0xc103,	/* Latch High (LH) */
	AEL2020_GPIO_CTRL   = 0xc108,	/* Store Clear (SC) */
	AEL2020_GPIO_STAT   = 0xc10c,	/* Read Only (RO) */
	AEL2020_GPIO_CFG    = 0xc110,	/* Read Write (RW) */

	AEL2020_GPIO_SDA    = 0,	/* IN: i2c serial data */
	AEL2020_GPIO_MODDET = 1,	/* IN: Module Detect */
	AEL2020_GPIO_0      = 3,	/* IN: unasचिन्हित */
	AEL2020_GPIO_1      = 2,	/* OUT: unasचिन्हित */
	AEL2020_GPIO_LSTAT  = AEL2020_GPIO_1, /* wired to link status LED */
पूर्ण;

क्रमागत अणु edc_none, edc_sr, edc_twinax पूर्ण;

/* PHY module I2C device address */
क्रमागत अणु
	MODULE_DEV_ADDR	= 0xa0,
	SFF_DEV_ADDR	= 0xa2,
पूर्ण;

/* PHY transceiver type */
क्रमागत अणु
	phy_transtype_unknown = 0,
	phy_transtype_sfp     = 3,
	phy_transtype_xfp     = 6,
पूर्ण;

#घोषणा AEL2005_MODDET_IRQ 4

काष्ठा reg_val अणु
	अचिन्हित लघु mmd_addr;
	अचिन्हित लघु reg_addr;
	अचिन्हित लघु clear_bits;
	अचिन्हित लघु set_bits;
पूर्ण;

अटल पूर्णांक set_phy_regs(काष्ठा cphy *phy, स्थिर काष्ठा reg_val *rv)
अणु
	पूर्णांक err;

	क्रम (err = 0; rv->mmd_addr && !err; rv++) अणु
		अगर (rv->clear_bits == 0xffff)
			err = t3_mdio_ग_लिखो(phy, rv->mmd_addr, rv->reg_addr,
					    rv->set_bits);
		अन्यथा
			err = t3_mdio_change_bits(phy, rv->mmd_addr,
						  rv->reg_addr, rv->clear_bits,
						  rv->set_bits);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम ael100x_txon(काष्ठा cphy *phy)
अणु
	पूर्णांक tx_on_gpio =
		phy->mdio.prtad == 0 ? F_GPIO7_OUT_VAL : F_GPIO2_OUT_VAL;

	msleep(100);
	t3_set_reg_field(phy->adapter, A_T3DBG_GPIO_EN, 0, tx_on_gpio);
	msleep(30);
पूर्ण

/*
 * Read an 8-bit word from a device attached to the PHY's i2c bus.
 */
अटल पूर्णांक ael_i2c_rd(काष्ठा cphy *phy, पूर्णांक dev_addr, पूर्णांक word_addr)
अणु
	पूर्णांक i, err;
	अचिन्हित पूर्णांक stat, data;

	err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL_I2C_CTRL,
			    (dev_addr << 8) | (1 << 8) | word_addr);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < 200; i++) अणु
		msleep(1);
		err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, AEL_I2C_STAT, &stat);
		अगर (err)
			वापस err;
		अगर ((stat & 3) == 1) अणु
			err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, AEL_I2C_DATA,
					   &data);
			अगर (err)
				वापस err;
			वापस data >> 8;
		पूर्ण
	पूर्ण
	CH_WARN(phy->adapter, "PHY %u i2c read of dev.addr %#x.%#x timed out\n",
		phy->mdio.prtad, dev_addr, word_addr);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ael1002_घातer_करोwn(काष्ठा cphy *phy, पूर्णांक enable)
अणु
	पूर्णांक err;

	err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, MDIO_PMA_TXDIS, !!enable);
	अगर (!err)
		err = mdio_set_flag(&phy->mdio, phy->mdio.prtad,
				    MDIO_MMD_PMAPMD, MDIO_CTRL1,
				    MDIO_CTRL1_LPOWER, enable);
	वापस err;
पूर्ण

अटल पूर्णांक ael1002_reset(काष्ठा cphy *phy, पूर्णांक रुको)
अणु
	पूर्णांक err;

	अगर ((err = ael1002_घातer_करोwn(phy, 0)) ||
	    (err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL100X_TX_CONFIG1, 1)) ||
	    (err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL1002_PWR_DOWN_HI, 0)) ||
	    (err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL1002_PWR_DOWN_LO, 0)) ||
	    (err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL1002_XFI_EQL, 0x18)) ||
	    (err = t3_mdio_change_bits(phy, MDIO_MMD_PMAPMD, AEL1002_LB_EN,
				       0, 1 << 5)))
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक ael1002_पूर्णांकr_noop(काष्ठा cphy *phy)
अणु
	वापस 0;
पूर्ण

/*
 * Get link status क्रम a 10GBASE-R device.
 */
अटल पूर्णांक get_link_status_r(काष्ठा cphy *phy, पूर्णांक *link_ok, पूर्णांक *speed,
			     पूर्णांक *duplex, पूर्णांक *fc)
अणु
	अगर (link_ok) अणु
		अचिन्हित पूर्णांक stat0, stat1, stat2;
		पूर्णांक err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD,
				       MDIO_PMA_RXDET, &stat0);

		अगर (!err)
			err = t3_mdio_पढ़ो(phy, MDIO_MMD_PCS,
					   MDIO_PCS_10GBRT_STAT1, &stat1);
		अगर (!err)
			err = t3_mdio_पढ़ो(phy, MDIO_MMD_PHYXS,
					   MDIO_PHYXS_LNSTAT, &stat2);
		अगर (err)
			वापस err;
		*link_ok = (stat0 & stat1 & (stat2 >> 12)) & 1;
	पूर्ण
	अगर (speed)
		*speed = SPEED_10000;
	अगर (duplex)
		*duplex = DUPLEX_FULL;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cphy_ops ael1002_ops = अणु
	.reset = ael1002_reset,
	.पूर्णांकr_enable = ael1002_पूर्णांकr_noop,
	.पूर्णांकr_disable = ael1002_पूर्णांकr_noop,
	.पूर्णांकr_clear = ael1002_पूर्णांकr_noop,
	.पूर्णांकr_handler = ael1002_पूर्णांकr_noop,
	.get_link_status = get_link_status_r,
	.घातer_करोwn = ael1002_घातer_करोwn,
	.mmds = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
पूर्ण;

पूर्णांक t3_ael1002_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	cphy_init(phy, adapter, phy_addr, &ael1002_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_FIBRE,
		   "10GBASE-R");
	ael100x_txon(phy);
	वापस 0;
पूर्ण

अटल पूर्णांक ael1006_reset(काष्ठा cphy *phy, पूर्णांक रुको)
अणु
	वापस t3_phy_reset(phy, MDIO_MMD_PMAPMD, रुको);
पूर्ण

अटल स्थिर काष्ठा cphy_ops ael1006_ops = अणु
	.reset = ael1006_reset,
	.पूर्णांकr_enable = t3_phy_lasi_पूर्णांकr_enable,
	.पूर्णांकr_disable = t3_phy_lasi_पूर्णांकr_disable,
	.पूर्णांकr_clear = t3_phy_lasi_पूर्णांकr_clear,
	.पूर्णांकr_handler = t3_phy_lasi_पूर्णांकr_handler,
	.get_link_status = get_link_status_r,
	.घातer_करोwn = ael1002_घातer_करोwn,
	.mmds = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
पूर्ण;

पूर्णांक t3_ael1006_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			     पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	cphy_init(phy, adapter, phy_addr, &ael1006_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_FIBRE,
		   "10GBASE-SR");
	ael100x_txon(phy);
	वापस 0;
पूर्ण

/*
 * Decode our module type.
 */
अटल पूर्णांक ael2xxx_get_module_type(काष्ठा cphy *phy, पूर्णांक delay_ms)
अणु
	पूर्णांक v;

	अगर (delay_ms)
		msleep(delay_ms);

	/* see SFF-8472 क्रम below */
	v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 3);
	अगर (v < 0)
		वापस v;

	अगर (v == 0x10)
		वापस phy_modtype_sr;
	अगर (v == 0x20)
		वापस phy_modtype_lr;
	अगर (v == 0x40)
		वापस phy_modtype_lrm;

	v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 6);
	अगर (v < 0)
		वापस v;
	अगर (v != 4)
		जाओ unknown;

	v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 10);
	अगर (v < 0)
		वापस v;

	अगर (v & 0x80) अणु
		v = ael_i2c_rd(phy, MODULE_DEV_ADDR, 0x12);
		अगर (v < 0)
			वापस v;
		वापस v > 10 ? phy_modtype_twinax_दीर्घ : phy_modtype_twinax;
	पूर्ण
unknown:
	वापस phy_modtype_unknown;
पूर्ण

/*
 * Code to support the Aeluros/NetLogic 2005 10Gb PHY.
 */
अटल पूर्णांक ael2005_setup_sr_edc(काष्ठा cphy *phy)
अणु
	अटल स्थिर काष्ठा reg_val regs[] = अणु
		अणु MDIO_MMD_PMAPMD, 0xc003, 0xffff, 0x181 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc010, 0xffff, 0x448a पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc04a, 0xffff, 0x5200 पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;

	पूर्णांक i, err;

	err = set_phy_regs(phy, regs);
	अगर (err)
		वापस err;

	msleep(50);

	अगर (phy->priv != edc_sr)
		err = t3_get_edc_fw(phy, EDC_OPT_AEL2005,
				    EDC_OPT_AEL2005_SIZE);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <  EDC_OPT_AEL2005_SIZE / माप(u16) && !err; i += 2)
		err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD,
				    phy->phy_cache[i],
				    phy->phy_cache[i + 1]);
	अगर (!err)
		phy->priv = edc_sr;
	वापस err;
पूर्ण

अटल पूर्णांक ael2005_setup_twinax_edc(काष्ठा cphy *phy, पूर्णांक modtype)
अणु
	अटल स्थिर काष्ठा reg_val regs[] = अणु
		अणु MDIO_MMD_PMAPMD, 0xc04a, 0xffff, 0x5a00 पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा reg_val preemphasis[] = अणु
		अणु MDIO_MMD_PMAPMD, 0xc014, 0xffff, 0xfe16 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc015, 0xffff, 0xa000 पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;
	पूर्णांक i, err;

	err = set_phy_regs(phy, regs);
	अगर (!err && modtype == phy_modtype_twinax_दीर्घ)
		err = set_phy_regs(phy, preemphasis);
	अगर (err)
		वापस err;

	msleep(50);

	अगर (phy->priv != edc_twinax)
		err = t3_get_edc_fw(phy, EDC_TWX_AEL2005,
				    EDC_TWX_AEL2005_SIZE);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <  EDC_TWX_AEL2005_SIZE / माप(u16) && !err; i += 2)
		err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD,
				    phy->phy_cache[i],
				    phy->phy_cache[i + 1]);
	अगर (!err)
		phy->priv = edc_twinax;
	वापस err;
पूर्ण

अटल पूर्णांक ael2005_get_module_type(काष्ठा cphy *phy, पूर्णांक delay_ms)
अणु
	पूर्णांक v;
	अचिन्हित पूर्णांक stat;

	v = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, AEL2005_GPIO_CTRL, &stat);
	अगर (v)
		वापस v;

	अगर (stat & (1 << 8))			/* module असलent */
		वापस phy_modtype_none;

	वापस ael2xxx_get_module_type(phy, delay_ms);
पूर्ण

अटल पूर्णांक ael2005_पूर्णांकr_enable(काष्ठा cphy *phy)
अणु
	पूर्णांक err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL2005_GPIO_CTRL, 0x200);
	वापस err ? err : t3_phy_lasi_पूर्णांकr_enable(phy);
पूर्ण

अटल पूर्णांक ael2005_पूर्णांकr_disable(काष्ठा cphy *phy)
अणु
	पूर्णांक err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL2005_GPIO_CTRL, 0x100);
	वापस err ? err : t3_phy_lasi_पूर्णांकr_disable(phy);
पूर्ण

अटल पूर्णांक ael2005_पूर्णांकr_clear(काष्ठा cphy *phy)
अणु
	पूर्णांक err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL2005_GPIO_CTRL, 0xd00);
	वापस err ? err : t3_phy_lasi_पूर्णांकr_clear(phy);
पूर्ण

अटल पूर्णांक ael2005_reset(काष्ठा cphy *phy, पूर्णांक रुको)
अणु
	अटल स्थिर काष्ठा reg_val regs0[] = अणु
		अणु MDIO_MMD_PMAPMD, 0xc001, 0, 1 << 5 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc017, 0, 1 << 5 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc013, 0xffff, 0xf341 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8000 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8100 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8000 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0 पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा reg_val regs1[] = अणु
		अणु MDIO_MMD_PMAPMD, 0xca00, 0xffff, 0x0080 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xca12, 0xffff, 0 पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;

	पूर्णांक err;
	अचिन्हित पूर्णांक lasi_ctrl;

	err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL,
			   &lasi_ctrl);
	अगर (err)
		वापस err;

	err = t3_phy_reset(phy, MDIO_MMD_PMAPMD, 0);
	अगर (err)
		वापस err;

	msleep(125);
	phy->priv = edc_none;
	err = set_phy_regs(phy, regs0);
	अगर (err)
		वापस err;

	msleep(50);

	err = ael2005_get_module_type(phy, 0);
	अगर (err < 0)
		वापस err;
	phy->modtype = err;

	अगर (err == phy_modtype_twinax || err == phy_modtype_twinax_दीर्घ)
		err = ael2005_setup_twinax_edc(phy, err);
	अन्यथा
		err = ael2005_setup_sr_edc(phy);
	अगर (err)
		वापस err;

	err = set_phy_regs(phy, regs1);
	अगर (err)
		वापस err;

	/* reset wipes out पूर्णांकerrupts, reenable them अगर they were on */
	अगर (lasi_ctrl & 1)
		err = ael2005_पूर्णांकr_enable(phy);
	वापस err;
पूर्ण

अटल पूर्णांक ael2005_पूर्णांकr_handler(काष्ठा cphy *phy)
अणु
	अचिन्हित पूर्णांक stat;
	पूर्णांक ret, edc_needed, cause = 0;

	ret = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, AEL2005_GPIO_STAT, &stat);
	अगर (ret)
		वापस ret;

	अगर (stat & AEL2005_MODDET_IRQ) अणु
		ret = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AEL2005_GPIO_CTRL,
				    0xd00);
		अगर (ret)
			वापस ret;

		/* modules have max 300 ms init समय after hot plug */
		ret = ael2005_get_module_type(phy, 300);
		अगर (ret < 0)
			वापस ret;

		phy->modtype = ret;
		अगर (ret == phy_modtype_none)
			edc_needed = phy->priv;       /* on unplug retain EDC */
		अन्यथा अगर (ret == phy_modtype_twinax ||
			 ret == phy_modtype_twinax_दीर्घ)
			edc_needed = edc_twinax;
		अन्यथा
			edc_needed = edc_sr;

		अगर (edc_needed != phy->priv) अणु
			ret = ael2005_reset(phy, 0);
			वापस ret ? ret : cphy_cause_module_change;
		पूर्ण
		cause = cphy_cause_module_change;
	पूर्ण

	ret = t3_phy_lasi_पूर्णांकr_handler(phy);
	अगर (ret < 0)
		वापस ret;

	ret |= cause;
	वापस ret ? ret : cphy_cause_link_change;
पूर्ण

अटल स्थिर काष्ठा cphy_ops ael2005_ops = अणु
	.reset           = ael2005_reset,
	.पूर्णांकr_enable     = ael2005_पूर्णांकr_enable,
	.पूर्णांकr_disable    = ael2005_पूर्णांकr_disable,
	.पूर्णांकr_clear      = ael2005_पूर्णांकr_clear,
	.पूर्णांकr_handler    = ael2005_पूर्णांकr_handler,
	.get_link_status = get_link_status_r,
	.घातer_करोwn      = ael1002_घातer_करोwn,
	.mmds            = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
पूर्ण;

पूर्णांक t3_ael2005_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	cphy_init(phy, adapter, phy_addr, &ael2005_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_FIBRE |
		  SUPPORTED_IRQ, "10GBASE-R");
	msleep(125);
	वापस t3_mdio_change_bits(phy, MDIO_MMD_PMAPMD, AEL_OPT_SETTINGS, 0,
				   1 << 5);
पूर्ण

/*
 * Setup EDC and other parameters क्रम operation with an optical module.
 */
अटल पूर्णांक ael2020_setup_sr_edc(काष्ठा cphy *phy)
अणु
	अटल स्थिर काष्ठा reg_val regs[] = अणु
		/* set CDR offset to 10 */
		अणु MDIO_MMD_PMAPMD, 0xcc01, 0xffff, 0x488a पूर्ण,

		/* adjust 10G RX bias current */
		अणु MDIO_MMD_PMAPMD, 0xcb1b, 0xffff, 0x0200 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xcb1c, 0xffff, 0x00f0 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xcc06, 0xffff, 0x00e0 पूर्ण,

		/* end */
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;
	पूर्णांक err;

	err = set_phy_regs(phy, regs);
	msleep(50);
	अगर (err)
		वापस err;

	phy->priv = edc_sr;
	वापस 0;
पूर्ण

/*
 * Setup EDC and other parameters क्रम operation with an TWINAX module.
 */
अटल पूर्णांक ael2020_setup_twinax_edc(काष्ठा cphy *phy, पूर्णांक modtype)
अणु
	/* set uC to 40MHz */
	अटल स्थिर काष्ठा reg_val uCघड़ी40MHz[] = अणु
		अणु MDIO_MMD_PMAPMD, 0xff28, 0xffff, 0x4001 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xff2a, 0xffff, 0x0002 पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;

	/* activate uC घड़ी */
	अटल स्थिर काष्ठा reg_val uCघड़ीActivate[] = अणु
		अणु MDIO_MMD_PMAPMD, 0xd000, 0xffff, 0x5200 पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;

	/* set PC to start of SRAM and activate uC */
	अटल स्थिर काष्ठा reg_val uCactivate[] = अणु
		अणु MDIO_MMD_PMAPMD, 0xd080, 0xffff, 0x0100 पूर्ण,
		अणु MDIO_MMD_PMAPMD, 0xd092, 0xffff, 0x0000 पूर्ण,
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;
	पूर्णांक i, err;

	/* set uC घड़ी and activate it */
	err = set_phy_regs(phy, uCघड़ी40MHz);
	msleep(500);
	अगर (err)
		वापस err;
	err = set_phy_regs(phy, uCघड़ीActivate);
	msleep(500);
	अगर (err)
		वापस err;

	अगर (phy->priv != edc_twinax)
		err = t3_get_edc_fw(phy, EDC_TWX_AEL2020,
				    EDC_TWX_AEL2020_SIZE);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <  EDC_TWX_AEL2020_SIZE / माप(u16) && !err; i += 2)
		err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD,
				    phy->phy_cache[i],
				    phy->phy_cache[i + 1]);
	/* activate uC */
	err = set_phy_regs(phy, uCactivate);
	अगर (!err)
		phy->priv = edc_twinax;
	वापस err;
पूर्ण

/*
 * Return Module Type.
 */
अटल पूर्णांक ael2020_get_module_type(काष्ठा cphy *phy, पूर्णांक delay_ms)
अणु
	पूर्णांक v;
	अचिन्हित पूर्णांक stat;

	v = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, AEL2020_GPIO_STAT, &stat);
	अगर (v)
		वापस v;

	अगर (stat & (0x1 << (AEL2020_GPIO_MODDET*4))) अणु
		/* module असलent */
		वापस phy_modtype_none;
	पूर्ण

	वापस ael2xxx_get_module_type(phy, delay_ms);
पूर्ण

/*
 * Enable PHY पूर्णांकerrupts.  We enable "Module Detection" पूर्णांकerrupts (on any
 * state transition) and then generic Link Alarm Status Interrupt (LASI).
 */
अटल पूर्णांक ael2020_पूर्णांकr_enable(काष्ठा cphy *phy)
अणु
	अटल स्थिर काष्ठा reg_val regs[] = अणु
		/* output Module's Loss Of Signal (LOS) to LED */
		अणु MDIO_MMD_PMAPMD, AEL2020_GPIO_CFG+AEL2020_GPIO_LSTAT,
			0xffff, 0x4 पूर्ण,
		अणु MDIO_MMD_PMAPMD, AEL2020_GPIO_CTRL,
			0xffff, 0x8 << (AEL2020_GPIO_LSTAT*4) पूर्ण,

		 /* enable module detect status change पूर्णांकerrupts */
		अणु MDIO_MMD_PMAPMD, AEL2020_GPIO_CTRL,
			0xffff, 0x2 << (AEL2020_GPIO_MODDET*4) पूर्ण,

		/* end */
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;
	पूर्णांक err, link_ok = 0;

	/* set up "link status" LED and enable module change पूर्णांकerrupts */
	err = set_phy_regs(phy, regs);
	अगर (err)
		वापस err;

	err = get_link_status_r(phy, &link_ok, शून्य, शून्य, शून्य);
	अगर (err)
		वापस err;
	अगर (link_ok)
		t3_link_changed(phy->adapter,
				phy2portid(phy));

	err = t3_phy_lasi_पूर्णांकr_enable(phy);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/*
 * Disable PHY पूर्णांकerrupts.  The mirror of the above ...
 */
अटल पूर्णांक ael2020_पूर्णांकr_disable(काष्ठा cphy *phy)
अणु
	अटल स्थिर काष्ठा reg_val regs[] = अणु
		/* reset "link status" LED to "off" */
		अणु MDIO_MMD_PMAPMD, AEL2020_GPIO_CTRL,
			0xffff, 0xb << (AEL2020_GPIO_LSTAT*4) पूर्ण,

		/* disable module detect status change पूर्णांकerrupts */
		अणु MDIO_MMD_PMAPMD, AEL2020_GPIO_CTRL,
			0xffff, 0x1 << (AEL2020_GPIO_MODDET*4) पूर्ण,

		/* end */
		अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;
	पूर्णांक err;

	/* turn off "link status" LED and disable module change पूर्णांकerrupts */
	err = set_phy_regs(phy, regs);
	अगर (err)
		वापस err;

	वापस t3_phy_lasi_पूर्णांकr_disable(phy);
पूर्ण

/*
 * Clear PHY पूर्णांकerrupt state.
 */
अटल पूर्णांक ael2020_पूर्णांकr_clear(काष्ठा cphy *phy)
अणु
	/*
	 * The GPIO Interrupt रेजिस्टर on the AEL2020 is a "Latching High"
	 * (LH) रेजिस्टर which is cleared to the current state when it's पढ़ो.
	 * Thus, we simply पढ़ो the रेजिस्टर and discard the result.
	 */
	अचिन्हित पूर्णांक stat;
	पूर्णांक err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, AEL2020_GPIO_INTR, &stat);
	वापस err ? err : t3_phy_lasi_पूर्णांकr_clear(phy);
पूर्ण

अटल स्थिर काष्ठा reg_val ael2020_reset_regs[] = अणु
	/* Erratum #2: CDRLOL निश्चितed, causing PMA link करोwn status */
	अणु MDIO_MMD_PMAPMD, 0xc003, 0xffff, 0x3101 पूर्ण,

	/* क्रमce XAUI to send LF when RX_LOS is निश्चितed */
	अणु MDIO_MMD_PMAPMD, 0xcd40, 0xffff, 0x0001 पूर्ण,

	/* allow ग_लिखोs to transceiver module EEPROM on i2c bus */
	अणु MDIO_MMD_PMAPMD, 0xff02, 0xffff, 0x0023 पूर्ण,
	अणु MDIO_MMD_PMAPMD, 0xff03, 0xffff, 0x0000 पूर्ण,
	अणु MDIO_MMD_PMAPMD, 0xff04, 0xffff, 0x0000 पूर्ण,

	/* end */
	अणु 0, 0, 0, 0 पूर्ण
पूर्ण;
/*
 * Reset the PHY and put it पूर्णांकo a canonical operating state.
 */
अटल पूर्णांक ael2020_reset(काष्ठा cphy *phy, पूर्णांक रुको)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक lasi_ctrl;

	/* grab current पूर्णांकerrupt state */
	err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL,
			   &lasi_ctrl);
	अगर (err)
		वापस err;

	err = t3_phy_reset(phy, MDIO_MMD_PMAPMD, 125);
	अगर (err)
		वापस err;
	msleep(100);

	/* basic initialization क्रम all module types */
	phy->priv = edc_none;
	err = set_phy_regs(phy, ael2020_reset_regs);
	अगर (err)
		वापस err;

	/* determine module type and perक्रमm appropriate initialization */
	err = ael2020_get_module_type(phy, 0);
	अगर (err < 0)
		वापस err;
	phy->modtype = (u8)err;
	अगर (err == phy_modtype_twinax || err == phy_modtype_twinax_दीर्घ)
		err = ael2020_setup_twinax_edc(phy, err);
	अन्यथा
		err = ael2020_setup_sr_edc(phy);
	अगर (err)
		वापस err;

	/* reset wipes out पूर्णांकerrupts, reenable them अगर they were on */
	अगर (lasi_ctrl & 1)
		err = ael2005_पूर्णांकr_enable(phy);
	वापस err;
पूर्ण

/*
 * Handle a PHY पूर्णांकerrupt.
 */
अटल पूर्णांक ael2020_पूर्णांकr_handler(काष्ठा cphy *phy)
अणु
	अचिन्हित पूर्णांक stat;
	पूर्णांक ret, edc_needed, cause = 0;

	ret = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, AEL2020_GPIO_INTR, &stat);
	अगर (ret)
		वापस ret;

	अगर (stat & (0x1 << AEL2020_GPIO_MODDET)) अणु
		/* modules have max 300 ms init समय after hot plug */
		ret = ael2020_get_module_type(phy, 300);
		अगर (ret < 0)
			वापस ret;

		phy->modtype = (u8)ret;
		अगर (ret == phy_modtype_none)
			edc_needed = phy->priv;       /* on unplug retain EDC */
		अन्यथा अगर (ret == phy_modtype_twinax ||
			 ret == phy_modtype_twinax_दीर्घ)
			edc_needed = edc_twinax;
		अन्यथा
			edc_needed = edc_sr;

		अगर (edc_needed != phy->priv) अणु
			ret = ael2020_reset(phy, 0);
			वापस ret ? ret : cphy_cause_module_change;
		पूर्ण
		cause = cphy_cause_module_change;
	पूर्ण

	ret = t3_phy_lasi_पूर्णांकr_handler(phy);
	अगर (ret < 0)
		वापस ret;

	ret |= cause;
	वापस ret ? ret : cphy_cause_link_change;
पूर्ण

अटल स्थिर काष्ठा cphy_ops ael2020_ops = अणु
	.reset           = ael2020_reset,
	.पूर्णांकr_enable     = ael2020_पूर्णांकr_enable,
	.पूर्णांकr_disable    = ael2020_पूर्णांकr_disable,
	.पूर्णांकr_clear      = ael2020_पूर्णांकr_clear,
	.पूर्णांकr_handler    = ael2020_पूर्णांकr_handler,
	.get_link_status = get_link_status_r,
	.घातer_करोwn      = ael1002_घातer_करोwn,
	.mmds		 = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
पूर्ण;

पूर्णांक t3_ael2020_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter, पूर्णांक phy_addr,
			स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	cphy_init(phy, adapter, phy_addr, &ael2020_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_FIBRE |
		  SUPPORTED_IRQ, "10GBASE-R");
	msleep(125);

	वापस set_phy_regs(phy, ael2020_reset_regs);
पूर्ण

/*
 * Get link status क्रम a 10GBASE-X device.
 */
अटल पूर्णांक get_link_status_x(काष्ठा cphy *phy, पूर्णांक *link_ok, पूर्णांक *speed,
			     पूर्णांक *duplex, पूर्णांक *fc)
अणु
	अगर (link_ok) अणु
		अचिन्हित पूर्णांक stat0, stat1, stat2;
		पूर्णांक err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD,
				       MDIO_PMA_RXDET, &stat0);

		अगर (!err)
			err = t3_mdio_पढ़ो(phy, MDIO_MMD_PCS,
					   MDIO_PCS_10GBX_STAT1, &stat1);
		अगर (!err)
			err = t3_mdio_पढ़ो(phy, MDIO_MMD_PHYXS,
					   MDIO_PHYXS_LNSTAT, &stat2);
		अगर (err)
			वापस err;
		*link_ok = (stat0 & (stat1 >> 12) & (stat2 >> 12)) & 1;
	पूर्ण
	अगर (speed)
		*speed = SPEED_10000;
	अगर (duplex)
		*duplex = DUPLEX_FULL;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cphy_ops qt2045_ops = अणु
	.reset = ael1006_reset,
	.पूर्णांकr_enable = t3_phy_lasi_पूर्णांकr_enable,
	.पूर्णांकr_disable = t3_phy_lasi_पूर्णांकr_disable,
	.पूर्णांकr_clear = t3_phy_lasi_पूर्णांकr_clear,
	.पूर्णांकr_handler = t3_phy_lasi_पूर्णांकr_handler,
	.get_link_status = get_link_status_x,
	.घातer_करोwn = ael1002_घातer_करोwn,
	.mmds = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
पूर्ण;

पूर्णांक t3_qt2045_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
		       पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	अचिन्हित पूर्णांक stat;

	cphy_init(phy, adapter, phy_addr, &qt2045_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_TP,
		  "10GBASE-CX4");

	/*
	 * Some cards where the PHY is supposed to be at address 0 actually
	 * have it at 1.
	 */
	अगर (!phy_addr &&
	    !t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, MDIO_STAT1, &stat) &&
	    stat == 0xffff)
		phy->mdio.prtad = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक xaui_direct_reset(काष्ठा cphy *phy, पूर्णांक रुको)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक xaui_direct_get_link_status(काष्ठा cphy *phy, पूर्णांक *link_ok,
				       पूर्णांक *speed, पूर्णांक *duplex, पूर्णांक *fc)
अणु
	अगर (link_ok) अणु
		अचिन्हित पूर्णांक status;
		पूर्णांक prtad = phy->mdio.prtad;

		status = t3_पढ़ो_reg(phy->adapter,
				     XGM_REG(A_XGM_SERDES_STAT0, prtad)) |
		    t3_पढ़ो_reg(phy->adapter,
				    XGM_REG(A_XGM_SERDES_STAT1, prtad)) |
		    t3_पढ़ो_reg(phy->adapter,
				XGM_REG(A_XGM_SERDES_STAT2, prtad)) |
		    t3_पढ़ो_reg(phy->adapter,
				XGM_REG(A_XGM_SERDES_STAT3, prtad));
		*link_ok = !(status & F_LOWSIG0);
	पूर्ण
	अगर (speed)
		*speed = SPEED_10000;
	अगर (duplex)
		*duplex = DUPLEX_FULL;
	वापस 0;
पूर्ण

अटल पूर्णांक xaui_direct_घातer_करोwn(काष्ठा cphy *phy, पूर्णांक enable)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cphy_ops xaui_direct_ops = अणु
	.reset = xaui_direct_reset,
	.पूर्णांकr_enable = ael1002_पूर्णांकr_noop,
	.पूर्णांकr_disable = ael1002_पूर्णांकr_noop,
	.पूर्णांकr_clear = ael1002_पूर्णांकr_noop,
	.पूर्णांकr_handler = ael1002_पूर्णांकr_noop,
	.get_link_status = xaui_direct_get_link_status,
	.घातer_करोwn = xaui_direct_घातer_करोwn,
पूर्ण;

पूर्णांक t3_xaui_direct_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			    पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	cphy_init(phy, adapter, phy_addr, &xaui_direct_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_TP,
		  "10GBASE-CX4");
	वापस 0;
पूर्ण
