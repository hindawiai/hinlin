<शैली गुरु>
/*
 * Copyright (c) 2013 Johannes Berg <johannes@sipsolutions.net>
 *
 *  This file is मुक्त software: you may copy, redistribute and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This file is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
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
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/mdपन.स>
#समावेश "reg.h"
#समावेश "hw.h"

अटल अंतरभूत bool alx_is_rev_a(u8 rev)
अणु
	वापस rev == ALX_REV_A0 || rev == ALX_REV_A1;
पूर्ण

अटल पूर्णांक alx_रुको_mdio_idle(काष्ठा alx_hw *hw)
अणु
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ALX_MDIO_MAX_AC_TO; i++) अणु
		val = alx_पढ़ो_mem32(hw, ALX_MDIO);
		अगर (!(val & ALX_MDIO_BUSY))
			वापस 0;
		udelay(10);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक alx_पढ़ो_phy_core(काष्ठा alx_hw *hw, bool ext, u8 dev,
			     u16 reg, u16 *phy_data)
अणु
	u32 val, clk_sel;
	पूर्णांक err;

	*phy_data = 0;

	/* use slow घड़ी when it's in hibernation status */
	clk_sel = hw->link_speed != SPEED_UNKNOWN ?
			ALX_MDIO_CLK_SEL_25MD4 :
			ALX_MDIO_CLK_SEL_25MD128;

	अगर (ext) अणु
		val = dev << ALX_MDIO_EXTN_DEVAD_SHIFT |
		      reg << ALX_MDIO_EXTN_REG_SHIFT;
		alx_ग_लिखो_mem32(hw, ALX_MDIO_EXTN, val);

		val = ALX_MDIO_SPRES_PRMBL | ALX_MDIO_START |
		      ALX_MDIO_MODE_EXT | ALX_MDIO_OP_READ |
		      clk_sel << ALX_MDIO_CLK_SEL_SHIFT;
	पूर्ण अन्यथा अणु
		val = ALX_MDIO_SPRES_PRMBL |
		      clk_sel << ALX_MDIO_CLK_SEL_SHIFT |
		      reg << ALX_MDIO_REG_SHIFT |
		      ALX_MDIO_START | ALX_MDIO_OP_READ;
	पूर्ण
	alx_ग_लिखो_mem32(hw, ALX_MDIO, val);

	err = alx_रुको_mdio_idle(hw);
	अगर (err)
		वापस err;
	val = alx_पढ़ो_mem32(hw, ALX_MDIO);
	*phy_data = ALX_GET_FIELD(val, ALX_MDIO_DATA);
	वापस 0;
पूर्ण

अटल पूर्णांक alx_ग_लिखो_phy_core(काष्ठा alx_hw *hw, bool ext, u8 dev,
			      u16 reg, u16 phy_data)
अणु
	u32 val, clk_sel;

	/* use slow घड़ी when it's in hibernation status */
	clk_sel = hw->link_speed != SPEED_UNKNOWN ?
			ALX_MDIO_CLK_SEL_25MD4 :
			ALX_MDIO_CLK_SEL_25MD128;

	अगर (ext) अणु
		val = dev << ALX_MDIO_EXTN_DEVAD_SHIFT |
		      reg << ALX_MDIO_EXTN_REG_SHIFT;
		alx_ग_लिखो_mem32(hw, ALX_MDIO_EXTN, val);

		val = ALX_MDIO_SPRES_PRMBL |
		      clk_sel << ALX_MDIO_CLK_SEL_SHIFT |
		      phy_data << ALX_MDIO_DATA_SHIFT |
		      ALX_MDIO_START | ALX_MDIO_MODE_EXT;
	पूर्ण अन्यथा अणु
		val = ALX_MDIO_SPRES_PRMBL |
		      clk_sel << ALX_MDIO_CLK_SEL_SHIFT |
		      reg << ALX_MDIO_REG_SHIFT |
		      phy_data << ALX_MDIO_DATA_SHIFT |
		      ALX_MDIO_START;
	पूर्ण
	alx_ग_लिखो_mem32(hw, ALX_MDIO, val);

	वापस alx_रुको_mdio_idle(hw);
पूर्ण

अटल पूर्णांक __alx_पढ़ो_phy_reg(काष्ठा alx_hw *hw, u16 reg, u16 *phy_data)
अणु
	वापस alx_पढ़ो_phy_core(hw, false, 0, reg, phy_data);
पूर्ण

अटल पूर्णांक __alx_ग_लिखो_phy_reg(काष्ठा alx_hw *hw, u16 reg, u16 phy_data)
अणु
	वापस alx_ग_लिखो_phy_core(hw, false, 0, reg, phy_data);
पूर्ण

अटल पूर्णांक __alx_पढ़ो_phy_ext(काष्ठा alx_hw *hw, u8 dev, u16 reg, u16 *pdata)
अणु
	वापस alx_पढ़ो_phy_core(hw, true, dev, reg, pdata);
पूर्ण

अटल पूर्णांक __alx_ग_लिखो_phy_ext(काष्ठा alx_hw *hw, u8 dev, u16 reg, u16 data)
अणु
	वापस alx_ग_लिखो_phy_core(hw, true, dev, reg, data);
पूर्ण

अटल पूर्णांक __alx_पढ़ो_phy_dbg(काष्ठा alx_hw *hw, u16 reg, u16 *pdata)
अणु
	पूर्णांक err;

	err = __alx_ग_लिखो_phy_reg(hw, ALX_MII_DBG_ADDR, reg);
	अगर (err)
		वापस err;

	वापस __alx_पढ़ो_phy_reg(hw, ALX_MII_DBG_DATA, pdata);
पूर्ण

अटल पूर्णांक __alx_ग_लिखो_phy_dbg(काष्ठा alx_hw *hw, u16 reg, u16 data)
अणु
	पूर्णांक err;

	err = __alx_ग_लिखो_phy_reg(hw, ALX_MII_DBG_ADDR, reg);
	अगर (err)
		वापस err;

	वापस __alx_ग_लिखो_phy_reg(hw, ALX_MII_DBG_DATA, data);
पूर्ण

पूर्णांक alx_पढ़ो_phy_reg(काष्ठा alx_hw *hw, u16 reg, u16 *phy_data)
अणु
	पूर्णांक err;

	spin_lock(&hw->mdio_lock);
	err = __alx_पढ़ो_phy_reg(hw, reg, phy_data);
	spin_unlock(&hw->mdio_lock);

	वापस err;
पूर्ण

पूर्णांक alx_ग_लिखो_phy_reg(काष्ठा alx_hw *hw, u16 reg, u16 phy_data)
अणु
	पूर्णांक err;

	spin_lock(&hw->mdio_lock);
	err = __alx_ग_लिखो_phy_reg(hw, reg, phy_data);
	spin_unlock(&hw->mdio_lock);

	वापस err;
पूर्ण

पूर्णांक alx_पढ़ो_phy_ext(काष्ठा alx_hw *hw, u8 dev, u16 reg, u16 *pdata)
अणु
	पूर्णांक err;

	spin_lock(&hw->mdio_lock);
	err = __alx_पढ़ो_phy_ext(hw, dev, reg, pdata);
	spin_unlock(&hw->mdio_lock);

	वापस err;
पूर्ण

पूर्णांक alx_ग_लिखो_phy_ext(काष्ठा alx_hw *hw, u8 dev, u16 reg, u16 data)
अणु
	पूर्णांक err;

	spin_lock(&hw->mdio_lock);
	err = __alx_ग_लिखो_phy_ext(hw, dev, reg, data);
	spin_unlock(&hw->mdio_lock);

	वापस err;
पूर्ण

अटल पूर्णांक alx_पढ़ो_phy_dbg(काष्ठा alx_hw *hw, u16 reg, u16 *pdata)
अणु
	पूर्णांक err;

	spin_lock(&hw->mdio_lock);
	err = __alx_पढ़ो_phy_dbg(hw, reg, pdata);
	spin_unlock(&hw->mdio_lock);

	वापस err;
पूर्ण

अटल पूर्णांक alx_ग_लिखो_phy_dbg(काष्ठा alx_hw *hw, u16 reg, u16 data)
अणु
	पूर्णांक err;

	spin_lock(&hw->mdio_lock);
	err = __alx_ग_लिखो_phy_dbg(hw, reg, data);
	spin_unlock(&hw->mdio_lock);

	वापस err;
पूर्ण

अटल u16 alx_get_phy_config(काष्ठा alx_hw *hw)
अणु
	u32 val;
	u16 phy_val;

	val = alx_पढ़ो_mem32(hw, ALX_PHY_CTRL);
	/* phy in reset */
	अगर ((val & ALX_PHY_CTRL_DSPRST_OUT) == 0)
		वापस ALX_DRV_PHY_UNKNOWN;

	val = alx_पढ़ो_mem32(hw, ALX_DRV);
	val = ALX_GET_FIELD(val, ALX_DRV_PHY);
	अगर (ALX_DRV_PHY_UNKNOWN == val)
		वापस ALX_DRV_PHY_UNKNOWN;

	alx_पढ़ो_phy_reg(hw, ALX_MII_DBG_ADDR, &phy_val);
	अगर (ALX_PHY_INITED == phy_val)
		वापस val;

	वापस ALX_DRV_PHY_UNKNOWN;
पूर्ण

अटल bool alx_रुको_reg(काष्ठा alx_hw *hw, u32 reg, u32 रुको, u32 *val)
अणु
	u32 पढ़ो;
	पूर्णांक i;

	क्रम (i = 0; i < ALX_SLD_MAX_TO; i++) अणु
		पढ़ो = alx_पढ़ो_mem32(hw, reg);
		अगर ((पढ़ो & रुको) == 0) अणु
			अगर (val)
				*val = पढ़ो;
			वापस true;
		पूर्ण
		mdelay(1);
	पूर्ण

	वापस false;
पूर्ण

अटल bool alx_पढ़ो_macaddr(काष्ठा alx_hw *hw, u8 *addr)
अणु
	u32 mac0, mac1;

	mac0 = alx_पढ़ो_mem32(hw, ALX_STAD0);
	mac1 = alx_पढ़ो_mem32(hw, ALX_STAD1);

	/* addr should be big-endian */
	put_unaligned(cpu_to_be32(mac0), (__be32 *)(addr + 2));
	put_unaligned(cpu_to_be16(mac1), (__be16 *)addr);

	वापस is_valid_ether_addr(addr);
पूर्ण

पूर्णांक alx_get_perm_macaddr(काष्ठा alx_hw *hw, u8 *addr)
अणु
	u32 val;

	/* try to get it from रेजिस्टर first */
	अगर (alx_पढ़ो_macaddr(hw, addr))
		वापस 0;

	/* try to load from efuse */
	अगर (!alx_रुको_reg(hw, ALX_SLD, ALX_SLD_STAT | ALX_SLD_START, &val))
		वापस -EIO;
	alx_ग_लिखो_mem32(hw, ALX_SLD, val | ALX_SLD_START);
	अगर (!alx_रुको_reg(hw, ALX_SLD, ALX_SLD_START, शून्य))
		वापस -EIO;
	अगर (alx_पढ़ो_macaddr(hw, addr))
		वापस 0;

	/* try to load from flash/eeprom (अगर present) */
	val = alx_पढ़ो_mem32(hw, ALX_EFLD);
	अगर (val & (ALX_EFLD_F_EXIST | ALX_EFLD_E_EXIST)) अणु
		अगर (!alx_रुको_reg(hw, ALX_EFLD,
				  ALX_EFLD_STAT | ALX_EFLD_START, &val))
			वापस -EIO;
		alx_ग_लिखो_mem32(hw, ALX_EFLD, val | ALX_EFLD_START);
		अगर (!alx_रुको_reg(hw, ALX_EFLD, ALX_EFLD_START, शून्य))
			वापस -EIO;
		अगर (alx_पढ़ो_macaddr(hw, addr))
			वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

व्योम alx_set_macaddr(काष्ठा alx_hw *hw, स्थिर u8 *addr)
अणु
	u32 val;

	/* क्रम example: 00-0B-6A-F6-00-DC * STAD0=6AF600DC, STAD1=000B */
	val = be32_to_cpu(get_unaligned((__be32 *)(addr + 2)));
	alx_ग_लिखो_mem32(hw, ALX_STAD0, val);
	val = be16_to_cpu(get_unaligned((__be16 *)addr));
	alx_ग_लिखो_mem32(hw, ALX_STAD1, val);
पूर्ण

अटल व्योम alx_reset_osc(काष्ठा alx_hw *hw, u8 rev)
अणु
	u32 val, val2;

	/* clear Internal OSC settings, चयनing OSC by hw itself */
	val = alx_पढ़ो_mem32(hw, ALX_MISC3);
	alx_ग_लिखो_mem32(hw, ALX_MISC3,
			(val & ~ALX_MISC3_25M_BY_SW) |
			ALX_MISC3_25M_NOTO_INTNL);

	/* 25M clk from chipset may be unstable 1s after de-निश्चित of
	 * PERST, driver need re-calibrate beक्रमe enter Sleep क्रम WoL
	 */
	val = alx_पढ़ो_mem32(hw, ALX_MISC);
	अगर (rev >= ALX_REV_B0) अणु
		/* restore over current protection def-val,
		 * this val could be reset by MAC-RST
		 */
		ALX_SET_FIELD(val, ALX_MISC_PSW_OCP, ALX_MISC_PSW_OCP_DEF);
		/* a 0->1 change will update the पूर्णांकernal val of osc */
		val &= ~ALX_MISC_INTNLOSC_OPEN;
		alx_ग_लिखो_mem32(hw, ALX_MISC, val);
		alx_ग_लिखो_mem32(hw, ALX_MISC, val | ALX_MISC_INTNLOSC_OPEN);
		/* hw will स्वतःmatically dis OSC after cab. */
		val2 = alx_पढ़ो_mem32(hw, ALX_MSIC2);
		val2 &= ~ALX_MSIC2_CALB_START;
		alx_ग_लिखो_mem32(hw, ALX_MSIC2, val2);
		alx_ग_लिखो_mem32(hw, ALX_MSIC2, val2 | ALX_MSIC2_CALB_START);
	पूर्ण अन्यथा अणु
		val &= ~ALX_MISC_INTNLOSC_OPEN;
		/* disable isolate क्रम rev A devices */
		अगर (alx_is_rev_a(rev))
			val &= ~ALX_MISC_ISO_EN;

		alx_ग_लिखो_mem32(hw, ALX_MISC, val | ALX_MISC_INTNLOSC_OPEN);
		alx_ग_लिखो_mem32(hw, ALX_MISC, val);
	पूर्ण

	udelay(20);
पूर्ण

अटल पूर्णांक alx_stop_mac(काष्ठा alx_hw *hw)
अणु
	u32 rxq, txq, val;
	u16 i;

	rxq = alx_पढ़ो_mem32(hw, ALX_RXQ0);
	alx_ग_लिखो_mem32(hw, ALX_RXQ0, rxq & ~ALX_RXQ0_EN);
	txq = alx_पढ़ो_mem32(hw, ALX_TXQ0);
	alx_ग_लिखो_mem32(hw, ALX_TXQ0, txq & ~ALX_TXQ0_EN);

	udelay(40);

	hw->rx_ctrl &= ~(ALX_MAC_CTRL_RX_EN | ALX_MAC_CTRL_TX_EN);
	alx_ग_लिखो_mem32(hw, ALX_MAC_CTRL, hw->rx_ctrl);

	क्रम (i = 0; i < ALX_DMA_MAC_RST_TO; i++) अणु
		val = alx_पढ़ो_mem32(hw, ALX_MAC_STS);
		अगर (!(val & ALX_MAC_STS_IDLE))
			वापस 0;
		udelay(10);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

पूर्णांक alx_reset_mac(काष्ठा alx_hw *hw)
अणु
	u32 val, pmctrl;
	पूर्णांक i, ret;
	u8 rev;
	bool a_cr;

	pmctrl = 0;
	rev = alx_hw_revision(hw);
	a_cr = alx_is_rev_a(rev) && alx_hw_with_cr(hw);

	/* disable all पूर्णांकerrupts, RXQ/TXQ */
	alx_ग_लिखो_mem32(hw, ALX_MSIX_MASK, 0xFFFFFFFF);
	alx_ग_लिखो_mem32(hw, ALX_IMR, 0);
	alx_ग_लिखो_mem32(hw, ALX_ISR, ALX_ISR_DIS);

	ret = alx_stop_mac(hw);
	अगर (ret)
		वापस ret;

	/* mac reset workaroud */
	alx_ग_लिखो_mem32(hw, ALX_RFD_PIDX, 1);

	/* dis l0s/l1 beक्रमe mac reset */
	अगर (a_cr) अणु
		pmctrl = alx_पढ़ो_mem32(hw, ALX_PMCTRL);
		अगर (pmctrl & (ALX_PMCTRL_L1_EN | ALX_PMCTRL_L0S_EN))
			alx_ग_लिखो_mem32(hw, ALX_PMCTRL,
					pmctrl & ~(ALX_PMCTRL_L1_EN |
						   ALX_PMCTRL_L0S_EN));
	पूर्ण

	/* reset whole mac safely */
	val = alx_पढ़ो_mem32(hw, ALX_MASTER);
	alx_ग_लिखो_mem32(hw, ALX_MASTER,
			val | ALX_MASTER_DMA_MAC_RST | ALX_MASTER_OOB_DIS);

	/* make sure it's real idle */
	udelay(10);
	क्रम (i = 0; i < ALX_DMA_MAC_RST_TO; i++) अणु
		val = alx_पढ़ो_mem32(hw, ALX_RFD_PIDX);
		अगर (val == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	क्रम (; i < ALX_DMA_MAC_RST_TO; i++) अणु
		val = alx_पढ़ो_mem32(hw, ALX_MASTER);
		अगर ((val & ALX_MASTER_DMA_MAC_RST) == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i == ALX_DMA_MAC_RST_TO)
		वापस -EIO;
	udelay(10);

	अगर (a_cr) अणु
		alx_ग_लिखो_mem32(hw, ALX_MASTER, val | ALX_MASTER_PCLKSEL_SRDS);
		/* restore l0s / l1 */
		अगर (pmctrl & (ALX_PMCTRL_L1_EN | ALX_PMCTRL_L0S_EN))
			alx_ग_लिखो_mem32(hw, ALX_PMCTRL, pmctrl);
	पूर्ण

	alx_reset_osc(hw, rev);

	/* clear Internal OSC settings, चयनing OSC by hw itself,
	 * disable isolate क्रम rev A devices
	 */
	val = alx_पढ़ो_mem32(hw, ALX_MISC3);
	alx_ग_लिखो_mem32(hw, ALX_MISC3,
			(val & ~ALX_MISC3_25M_BY_SW) |
			ALX_MISC3_25M_NOTO_INTNL);
	val = alx_पढ़ो_mem32(hw, ALX_MISC);
	val &= ~ALX_MISC_INTNLOSC_OPEN;
	अगर (alx_is_rev_a(rev))
		val &= ~ALX_MISC_ISO_EN;
	alx_ग_लिखो_mem32(hw, ALX_MISC, val);
	udelay(20);

	/* driver control speed/duplex, hash-alg */
	alx_ग_लिखो_mem32(hw, ALX_MAC_CTRL, hw->rx_ctrl);

	val = alx_पढ़ो_mem32(hw, ALX_SERDES);
	alx_ग_लिखो_mem32(hw, ALX_SERDES,
			val | ALX_SERDES_MACCLK_SLWDWN |
			ALX_SERDES_PHYCLK_SLWDWN);

	वापस 0;
पूर्ण

व्योम alx_reset_phy(काष्ठा alx_hw *hw)
अणु
	पूर्णांक i;
	u32 val;
	u16 phy_val;

	/* (DSP)reset PHY core */
	val = alx_पढ़ो_mem32(hw, ALX_PHY_CTRL);
	val &= ~(ALX_PHY_CTRL_DSPRST_OUT | ALX_PHY_CTRL_IDDQ |
		 ALX_PHY_CTRL_GATE_25M | ALX_PHY_CTRL_POWER_DOWN |
		 ALX_PHY_CTRL_CLS);
	val |= ALX_PHY_CTRL_RST_ANALOG;

	val |= (ALX_PHY_CTRL_HIB_PULSE | ALX_PHY_CTRL_HIB_EN);
	alx_ग_लिखो_mem32(hw, ALX_PHY_CTRL, val);
	udelay(10);
	alx_ग_लिखो_mem32(hw, ALX_PHY_CTRL, val | ALX_PHY_CTRL_DSPRST_OUT);

	क्रम (i = 0; i < ALX_PHY_CTRL_DSPRST_TO; i++)
		udelay(10);

	/* phy घातer saving & hib */
	alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_LEGCYPS, ALX_LEGCYPS_DEF);
	alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_SYSMODCTRL,
			  ALX_SYSMODCTRL_IECHOADJ_DEF);
	alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_VDRVBIAS,
			  ALX_VDRVBIAS_DEF);

	/* EEE advertisement */
	val = alx_पढ़ो_mem32(hw, ALX_LPI_CTRL);
	alx_ग_लिखो_mem32(hw, ALX_LPI_CTRL, val & ~ALX_LPI_CTRL_EN);
	alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_LOCAL_EEEADV, 0);

	/* phy घातer saving */
	alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_TST10BTCFG, ALX_TST10BTCFG_DEF);
	alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_SRDSYSMOD, ALX_SRDSYSMOD_DEF);
	alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_TST100BTCFG, ALX_TST100BTCFG_DEF);
	alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_ANACTRL, ALX_ANACTRL_DEF);
	alx_पढ़ो_phy_dbg(hw, ALX_MIIDBG_GREENCFG2, &phy_val);
	alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_GREENCFG2,
			  phy_val & ~ALX_GREENCFG2_GATE_DFSE_EN);
	/* rtl8139c, 120m issue */
	alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_NLP78,
			  ALX_MIIEXT_NLP78_120M_DEF);
	alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_S3DIG10,
			  ALX_MIIEXT_S3DIG10_DEF);

	अगर (hw->lnk_patch) अणु
		/* Turn off half amplitude */
		alx_पढ़ो_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL3,
				 &phy_val);
		alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL3,
				  phy_val | ALX_CLDCTRL3_BP_CABLE1TH_DET_GT);
		/* Turn off Green feature */
		alx_पढ़ो_phy_dbg(hw, ALX_MIIDBG_GREENCFG2, &phy_val);
		alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_GREENCFG2,
				  phy_val | ALX_GREENCFG2_BP_GREEN);
		/* Turn off half Bias */
		alx_पढ़ो_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL5,
				 &phy_val);
		alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL5,
				  phy_val | ALX_CLDCTRL5_BP_VD_HLFBIAS);
	पूर्ण

	/* set phy पूर्णांकerrupt mask */
	alx_ग_लिखो_phy_reg(hw, ALX_MII_IER, ALX_IER_LINK_UP | ALX_IER_LINK_DOWN);
पूर्ण

#घोषणा ALX_PCI_CMD (PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY | PCI_COMMAND_IO)

व्योम alx_reset_pcie(काष्ठा alx_hw *hw)
अणु
	u8 rev = alx_hw_revision(hw);
	u32 val;
	u16 val16;

	/* Workaround क्रम PCI problem when BIOS sets MMRBC incorrectly. */
	pci_पढ़ो_config_word(hw->pdev, PCI_COMMAND, &val16);
	अगर (!(val16 & ALX_PCI_CMD) || (val16 & PCI_COMMAND_INTX_DISABLE)) अणु
		val16 = (val16 | ALX_PCI_CMD) & ~PCI_COMMAND_INTX_DISABLE;
		pci_ग_लिखो_config_word(hw->pdev, PCI_COMMAND, val16);
	पूर्ण

	/* clear WoL setting/status */
	val = alx_पढ़ो_mem32(hw, ALX_WOL0);
	alx_ग_लिखो_mem32(hw, ALX_WOL0, 0);

	val = alx_पढ़ो_mem32(hw, ALX_PDLL_TRNS1);
	alx_ग_लिखो_mem32(hw, ALX_PDLL_TRNS1, val & ~ALX_PDLL_TRNS1_D3PLLOFF_EN);

	/* mask some pcie error bits */
	val = alx_पढ़ो_mem32(hw, ALX_UE_SVRT);
	val &= ~(ALX_UE_SVRT_DLPROTERR | ALX_UE_SVRT_FCPROTERR);
	alx_ग_लिखो_mem32(hw, ALX_UE_SVRT, val);

	/* wol 25M & pclk */
	val = alx_पढ़ो_mem32(hw, ALX_MASTER);
	अगर (alx_is_rev_a(rev) && alx_hw_with_cr(hw)) अणु
		अगर ((val & ALX_MASTER_WAKEN_25M) == 0 ||
		    (val & ALX_MASTER_PCLKSEL_SRDS) == 0)
			alx_ग_लिखो_mem32(hw, ALX_MASTER,
					val | ALX_MASTER_PCLKSEL_SRDS |
					ALX_MASTER_WAKEN_25M);
	पूर्ण अन्यथा अणु
		अगर ((val & ALX_MASTER_WAKEN_25M) == 0 ||
		    (val & ALX_MASTER_PCLKSEL_SRDS) != 0)
			alx_ग_लिखो_mem32(hw, ALX_MASTER,
					(val & ~ALX_MASTER_PCLKSEL_SRDS) |
					ALX_MASTER_WAKEN_25M);
	पूर्ण

	/* ASPM setting */
	alx_enable_aspm(hw, true, true);

	udelay(10);
पूर्ण

व्योम alx_start_mac(काष्ठा alx_hw *hw)
अणु
	u32 mac, txq, rxq;

	rxq = alx_पढ़ो_mem32(hw, ALX_RXQ0);
	alx_ग_लिखो_mem32(hw, ALX_RXQ0, rxq | ALX_RXQ0_EN);
	txq = alx_पढ़ो_mem32(hw, ALX_TXQ0);
	alx_ग_लिखो_mem32(hw, ALX_TXQ0, txq | ALX_TXQ0_EN);

	mac = hw->rx_ctrl;
	अगर (hw->duplex == DUPLEX_FULL)
		mac |= ALX_MAC_CTRL_FULLD;
	अन्यथा
		mac &= ~ALX_MAC_CTRL_FULLD;
	ALX_SET_FIELD(mac, ALX_MAC_CTRL_SPEED,
		      hw->link_speed == SPEED_1000 ? ALX_MAC_CTRL_SPEED_1000 :
						     ALX_MAC_CTRL_SPEED_10_100);
	mac |= ALX_MAC_CTRL_TX_EN | ALX_MAC_CTRL_RX_EN;
	hw->rx_ctrl = mac;
	alx_ग_लिखो_mem32(hw, ALX_MAC_CTRL, mac);
पूर्ण

व्योम alx_cfg_mac_flowcontrol(काष्ठा alx_hw *hw, u8 fc)
अणु
	अगर (fc & ALX_FC_RX)
		hw->rx_ctrl |= ALX_MAC_CTRL_RXFC_EN;
	अन्यथा
		hw->rx_ctrl &= ~ALX_MAC_CTRL_RXFC_EN;

	अगर (fc & ALX_FC_TX)
		hw->rx_ctrl |= ALX_MAC_CTRL_TXFC_EN;
	अन्यथा
		hw->rx_ctrl &= ~ALX_MAC_CTRL_TXFC_EN;

	alx_ग_लिखो_mem32(hw, ALX_MAC_CTRL, hw->rx_ctrl);
पूर्ण

व्योम alx_enable_aspm(काष्ठा alx_hw *hw, bool l0s_en, bool l1_en)
अणु
	u32 pmctrl;
	u8 rev = alx_hw_revision(hw);

	pmctrl = alx_पढ़ो_mem32(hw, ALX_PMCTRL);

	ALX_SET_FIELD(pmctrl, ALX_PMCTRL_LCKDET_TIMER,
		      ALX_PMCTRL_LCKDET_TIMER_DEF);
	pmctrl |= ALX_PMCTRL_RCVR_WT_1US |
		  ALX_PMCTRL_L1_CLKSW_EN |
		  ALX_PMCTRL_L1_SRDSRX_PWD;
	ALX_SET_FIELD(pmctrl, ALX_PMCTRL_L1REQ_TO, ALX_PMCTRL_L1REG_TO_DEF);
	ALX_SET_FIELD(pmctrl, ALX_PMCTRL_L1_TIMER, ALX_PMCTRL_L1_TIMER_16US);
	pmctrl &= ~(ALX_PMCTRL_L1_SRDS_EN |
		    ALX_PMCTRL_L1_SRDSPLL_EN |
		    ALX_PMCTRL_L1_BUFSRX_EN |
		    ALX_PMCTRL_SADLY_EN |
		    ALX_PMCTRL_HOTRST_WTEN|
		    ALX_PMCTRL_L0S_EN |
		    ALX_PMCTRL_L1_EN |
		    ALX_PMCTRL_ASPM_FCEN |
		    ALX_PMCTRL_TXL1_AFTER_L0S |
		    ALX_PMCTRL_RXL1_AFTER_L0S);
	अगर (alx_is_rev_a(rev) && alx_hw_with_cr(hw))
		pmctrl |= ALX_PMCTRL_L1_SRDS_EN | ALX_PMCTRL_L1_SRDSPLL_EN;

	अगर (l0s_en)
		pmctrl |= (ALX_PMCTRL_L0S_EN | ALX_PMCTRL_ASPM_FCEN);
	अगर (l1_en)
		pmctrl |= (ALX_PMCTRL_L1_EN | ALX_PMCTRL_ASPM_FCEN);

	alx_ग_लिखो_mem32(hw, ALX_PMCTRL, pmctrl);
पूर्ण


अटल u32 ethadv_to_hw_cfg(काष्ठा alx_hw *hw, u32 ethadv_cfg)
अणु
	u32 cfg = 0;

	अगर (ethadv_cfg & ADVERTISED_Autoneg) अणु
		cfg |= ALX_DRV_PHY_AUTO;
		अगर (ethadv_cfg & ADVERTISED_10baseT_Half)
			cfg |= ALX_DRV_PHY_10;
		अगर (ethadv_cfg & ADVERTISED_10baseT_Full)
			cfg |= ALX_DRV_PHY_10 | ALX_DRV_PHY_DUPLEX;
		अगर (ethadv_cfg & ADVERTISED_100baseT_Half)
			cfg |= ALX_DRV_PHY_100;
		अगर (ethadv_cfg & ADVERTISED_100baseT_Full)
			cfg |= ALX_DRV_PHY_100 | ALX_DRV_PHY_DUPLEX;
		अगर (ethadv_cfg & ADVERTISED_1000baseT_Half)
			cfg |= ALX_DRV_PHY_1000;
		अगर (ethadv_cfg & ADVERTISED_1000baseT_Full)
			cfg |= ALX_DRV_PHY_100 | ALX_DRV_PHY_DUPLEX;
		अगर (ethadv_cfg & ADVERTISED_Pause)
			cfg |= ADVERTISE_PAUSE_CAP;
		अगर (ethadv_cfg & ADVERTISED_Asym_Pause)
			cfg |= ADVERTISE_PAUSE_ASYM;
	पूर्ण अन्यथा अणु
		चयन (ethadv_cfg) अणु
		हाल ADVERTISED_10baseT_Half:
			cfg |= ALX_DRV_PHY_10;
			अवरोध;
		हाल ADVERTISED_100baseT_Half:
			cfg |= ALX_DRV_PHY_100;
			अवरोध;
		हाल ADVERTISED_10baseT_Full:
			cfg |= ALX_DRV_PHY_10 | ALX_DRV_PHY_DUPLEX;
			अवरोध;
		हाल ADVERTISED_100baseT_Full:
			cfg |= ALX_DRV_PHY_100 | ALX_DRV_PHY_DUPLEX;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस cfg;
पूर्ण

पूर्णांक alx_setup_speed_duplex(काष्ठा alx_hw *hw, u32 ethadv, u8 flowctrl)
अणु
	u16 adv, giga, cr;
	u32 val;
	पूर्णांक err = 0;

	alx_ग_लिखो_phy_reg(hw, ALX_MII_DBG_ADDR, 0);
	val = alx_पढ़ो_mem32(hw, ALX_DRV);
	ALX_SET_FIELD(val, ALX_DRV_PHY, 0);

	अगर (ethadv & ADVERTISED_Autoneg) अणु
		adv = ADVERTISE_CSMA;
		adv |= ethtool_adv_to_mii_adv_t(ethadv);

		अगर (flowctrl & ALX_FC_ANEG) अणु
			अगर (flowctrl & ALX_FC_RX) अणु
				adv |= ADVERTISED_Pause;
				अगर (!(flowctrl & ALX_FC_TX))
					adv |= ADVERTISED_Asym_Pause;
			पूर्ण अन्यथा अगर (flowctrl & ALX_FC_TX) अणु
				adv |= ADVERTISED_Asym_Pause;
			पूर्ण
		पूर्ण
		giga = 0;
		अगर (alx_hw_giga(hw))
			giga = ethtool_adv_to_mii_ctrl1000_t(ethadv);

		cr = BMCR_RESET | BMCR_ANENABLE | BMCR_ANRESTART;

		अगर (alx_ग_लिखो_phy_reg(hw, MII_ADVERTISE, adv) ||
		    alx_ग_लिखो_phy_reg(hw, MII_CTRL1000, giga) ||
		    alx_ग_लिखो_phy_reg(hw, MII_BMCR, cr))
			err = -EBUSY;
	पूर्ण अन्यथा अणु
		cr = BMCR_RESET;
		अगर (ethadv == ADVERTISED_100baseT_Half ||
		    ethadv == ADVERTISED_100baseT_Full)
			cr |= BMCR_SPEED100;
		अगर (ethadv == ADVERTISED_10baseT_Full ||
		    ethadv == ADVERTISED_100baseT_Full)
			cr |= BMCR_FULLDPLX;

		err = alx_ग_लिखो_phy_reg(hw, MII_BMCR, cr);
	पूर्ण

	अगर (!err) अणु
		alx_ग_लिखो_phy_reg(hw, ALX_MII_DBG_ADDR, ALX_PHY_INITED);
		val |= ethadv_to_hw_cfg(hw, ethadv);
	पूर्ण

	alx_ग_लिखो_mem32(hw, ALX_DRV, val);

	वापस err;
पूर्ण


व्योम alx_post_phy_link(काष्ठा alx_hw *hw)
अणु
	u16 phy_val, len, agc;
	u8 revid = alx_hw_revision(hw);
	bool adj_th = revid == ALX_REV_B0;

	अगर (revid != ALX_REV_B0 && !alx_is_rev_a(revid))
		वापस;

	/* 1000BT/AZ, wrong cable length */
	अगर (hw->link_speed != SPEED_UNKNOWN) अणु
		alx_पढ़ो_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL6,
				 &phy_val);
		len = ALX_GET_FIELD(phy_val, ALX_CLDCTRL6_CAB_LEN);
		alx_पढ़ो_phy_dbg(hw, ALX_MIIDBG_AGC, &phy_val);
		agc = ALX_GET_FIELD(phy_val, ALX_AGC_2_VGA);

		अगर ((hw->link_speed == SPEED_1000 &&
		     (len > ALX_CLDCTRL6_CAB_LEN_SHORT1G ||
		      (len == 0 && agc > ALX_AGC_LONG1G_LIMT))) ||
		    (hw->link_speed == SPEED_100 &&
		     (len > ALX_CLDCTRL6_CAB_LEN_SHORT100M ||
		      (len == 0 && agc > ALX_AGC_LONG100M_LIMT)))) अणु
			alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_AZ_ANADECT,
					  ALX_AZ_ANADECT_LONG);
			alx_पढ़ो_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
					 &phy_val);
			alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
					  phy_val | ALX_AFE_10BT_100M_TH);
		पूर्ण अन्यथा अणु
			alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_AZ_ANADECT,
					  ALX_AZ_ANADECT_DEF);
			alx_पढ़ो_phy_ext(hw, ALX_MIIEXT_ANEG,
					 ALX_MIIEXT_AFE, &phy_val);
			alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
					  phy_val & ~ALX_AFE_10BT_100M_TH);
		पूर्ण

		/* threshold adjust */
		अगर (adj_th && hw->lnk_patch) अणु
			अगर (hw->link_speed == SPEED_100) अणु
				alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_MSE16DB,
						  ALX_MSE16DB_UP);
			पूर्ण अन्यथा अगर (hw->link_speed == SPEED_1000) अणु
				/*
				 * Giga link threshold, उठाओ the tolerance of
				 * noise 50%
				 */
				alx_पढ़ो_phy_dbg(hw, ALX_MIIDBG_MSE20DB,
						 &phy_val);
				ALX_SET_FIELD(phy_val, ALX_MSE20DB_TH,
					      ALX_MSE20DB_TH_HI);
				alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_MSE20DB,
						  phy_val);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		alx_पढ़ो_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
				 &phy_val);
		alx_ग_लिखो_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_AFE,
				  phy_val & ~ALX_AFE_10BT_100M_TH);

		अगर (adj_th && hw->lnk_patch) अणु
			alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_MSE16DB,
					  ALX_MSE16DB_DOWN);
			alx_पढ़ो_phy_dbg(hw, ALX_MIIDBG_MSE20DB, &phy_val);
			ALX_SET_FIELD(phy_val, ALX_MSE20DB_TH,
				      ALX_MSE20DB_TH_DEF);
			alx_ग_लिखो_phy_dbg(hw, ALX_MIIDBG_MSE20DB, phy_val);
		पूर्ण
	पूर्ण
पूर्ण

bool alx_phy_configured(काष्ठा alx_hw *hw)
अणु
	u32 cfg, hw_cfg;

	cfg = ethadv_to_hw_cfg(hw, hw->adv_cfg);
	cfg = ALX_GET_FIELD(cfg, ALX_DRV_PHY);
	hw_cfg = alx_get_phy_config(hw);

	अगर (hw_cfg == ALX_DRV_PHY_UNKNOWN)
		वापस false;

	वापस cfg == hw_cfg;
पूर्ण

पूर्णांक alx_पढ़ो_phy_link(काष्ठा alx_hw *hw)
अणु
	काष्ठा pci_dev *pdev = hw->pdev;
	u16 bmsr, giga;
	पूर्णांक err;

	err = alx_पढ़ो_phy_reg(hw, MII_BMSR, &bmsr);
	अगर (err)
		वापस err;

	err = alx_पढ़ो_phy_reg(hw, MII_BMSR, &bmsr);
	अगर (err)
		वापस err;

	अगर (!(bmsr & BMSR_LSTATUS)) अणु
		hw->link_speed = SPEED_UNKNOWN;
		hw->duplex = DUPLEX_UNKNOWN;
		वापस 0;
	पूर्ण

	/* speed/duplex result is saved in PHY Specअगरic Status Register */
	err = alx_पढ़ो_phy_reg(hw, ALX_MII_GIGA_PSSR, &giga);
	अगर (err)
		वापस err;

	अगर (!(giga & ALX_GIGA_PSSR_SPD_DPLX_RESOLVED))
		जाओ wrong_speed;

	चयन (giga & ALX_GIGA_PSSR_SPEED) अणु
	हाल ALX_GIGA_PSSR_1000MBS:
		hw->link_speed = SPEED_1000;
		अवरोध;
	हाल ALX_GIGA_PSSR_100MBS:
		hw->link_speed = SPEED_100;
		अवरोध;
	हाल ALX_GIGA_PSSR_10MBS:
		hw->link_speed = SPEED_10;
		अवरोध;
	शेष:
		जाओ wrong_speed;
	पूर्ण

	hw->duplex = (giga & ALX_GIGA_PSSR_DPLX) ? DUPLEX_FULL : DUPLEX_HALF;
	वापस 0;

wrong_speed:
	dev_err(&pdev->dev, "invalid PHY speed/duplex: 0x%x\n", giga);
	वापस -EINVAL;
पूर्ण

पूर्णांक alx_clear_phy_पूर्णांकr(काष्ठा alx_hw *hw)
अणु
	u16 isr;

	/* clear पूर्णांकerrupt status by पढ़ोing it */
	वापस alx_पढ़ो_phy_reg(hw, ALX_MII_ISR, &isr);
पूर्ण

व्योम alx_disable_rss(काष्ठा alx_hw *hw)
अणु
	u32 ctrl = alx_पढ़ो_mem32(hw, ALX_RXQ0);

	ctrl &= ~ALX_RXQ0_RSS_HASH_EN;
	alx_ग_लिखो_mem32(hw, ALX_RXQ0, ctrl);
पूर्ण

व्योम alx_configure_basic(काष्ठा alx_hw *hw)
अणु
	u32 val, raw_mtu, max_payload;
	u16 val16;
	u8 chip_rev = alx_hw_revision(hw);

	alx_set_macaddr(hw, hw->mac_addr);

	alx_ग_लिखो_mem32(hw, ALX_CLK_GATE, ALX_CLK_GATE_ALL);

	/* idle समयout to चयन clk_125M */
	अगर (chip_rev >= ALX_REV_B0)
		alx_ग_लिखो_mem32(hw, ALX_IDLE_DECISN_TIMER,
				ALX_IDLE_DECISN_TIMER_DEF);

	alx_ग_लिखो_mem32(hw, ALX_SMB_TIMER, hw->smb_समयr * 500UL);

	val = alx_पढ़ो_mem32(hw, ALX_MASTER);
	val |= ALX_MASTER_IRQMOD2_EN |
	       ALX_MASTER_IRQMOD1_EN |
	       ALX_MASTER_SYSALVTIMER_EN;
	alx_ग_लिखो_mem32(hw, ALX_MASTER, val);
	alx_ग_लिखो_mem32(hw, ALX_IRQ_MODU_TIMER,
			(hw->imt >> 1) << ALX_IRQ_MODU_TIMER1_SHIFT);
	/* पूर्णांकr re-trig समयout */
	alx_ग_लिखो_mem32(hw, ALX_INT_RETRIG, ALX_INT_RETRIG_TO);
	/* tpd threshold to trig पूर्णांक */
	alx_ग_लिखो_mem32(hw, ALX_TINT_TPD_THRSHLD, hw->ith_tpd);
	alx_ग_लिखो_mem32(hw, ALX_TINT_TIMER, hw->imt);

	raw_mtu = ALX_RAW_MTU(hw->mtu);
	alx_ग_लिखो_mem32(hw, ALX_MTU, raw_mtu);
	अगर (raw_mtu > (ALX_MTU_JUMBO_TH + ETH_FCS_LEN + VLAN_HLEN))
		hw->rx_ctrl &= ~ALX_MAC_CTRL_FAST_PAUSE;

	अगर (raw_mtu < ALX_TXQ1_JUMBO_TSO_TH)
		val = (raw_mtu + 7) >> 3;
	अन्यथा
		val = ALX_TXQ1_JUMBO_TSO_TH >> 3;
	alx_ग_लिखो_mem32(hw, ALX_TXQ1, val | ALX_TXQ1_ERRLGPKT_DROP_EN);

	max_payload = pcie_get_पढ़ोrq(hw->pdev) >> 8;
	/*
	 * अगर BIOS had changed the शेष dma पढ़ो max length,
	 * restore it to शेष value
	 */
	अगर (max_payload < ALX_DEV_CTRL_MAXRRS_MIN)
		pcie_set_पढ़ोrq(hw->pdev, 128 << ALX_DEV_CTRL_MAXRRS_MIN);

	val = ALX_TXQ_TPD_BURSTPREF_DEF << ALX_TXQ0_TPD_BURSTPREF_SHIFT |
	      ALX_TXQ0_MODE_ENHANCE | ALX_TXQ0_LSO_8023_EN |
	      ALX_TXQ0_SUPT_IPOPT |
	      ALX_TXQ_TXF_BURST_PREF_DEF << ALX_TXQ0_TXF_BURST_PREF_SHIFT;
	alx_ग_लिखो_mem32(hw, ALX_TXQ0, val);
	val = ALX_TXQ_TPD_BURSTPREF_DEF << ALX_HQTPD_Q1_NUMPREF_SHIFT |
	      ALX_TXQ_TPD_BURSTPREF_DEF << ALX_HQTPD_Q2_NUMPREF_SHIFT |
	      ALX_TXQ_TPD_BURSTPREF_DEF << ALX_HQTPD_Q3_NUMPREF_SHIFT |
	      ALX_HQTPD_BURST_EN;
	alx_ग_लिखो_mem32(hw, ALX_HQTPD, val);

	/* rxq, flow control */
	val = alx_पढ़ो_mem32(hw, ALX_SRAM5);
	val = ALX_GET_FIELD(val, ALX_SRAM_RXF_LEN) << 3;
	अगर (val > ALX_SRAM_RXF_LEN_8K) अणु
		val16 = ALX_MTU_STD_ALGN >> 3;
		val = (val - ALX_RXQ2_RXF_FLOW_CTRL_RSVD) >> 3;
	पूर्ण अन्यथा अणु
		val16 = ALX_MTU_STD_ALGN >> 3;
		val = (val - ALX_MTU_STD_ALGN) >> 3;
	पूर्ण
	alx_ग_लिखो_mem32(hw, ALX_RXQ2,
			val16 << ALX_RXQ2_RXF_XOFF_THRESH_SHIFT |
			val << ALX_RXQ2_RXF_XON_THRESH_SHIFT);
	val = ALX_RXQ0_NUM_RFD_PREF_DEF << ALX_RXQ0_NUM_RFD_PREF_SHIFT |
	      ALX_RXQ0_RSS_MODE_DIS << ALX_RXQ0_RSS_MODE_SHIFT |
	      ALX_RXQ0_IDT_TBL_SIZE_DEF << ALX_RXQ0_IDT_TBL_SIZE_SHIFT |
	      ALX_RXQ0_RSS_HSTYP_ALL | ALX_RXQ0_RSS_HASH_EN |
	      ALX_RXQ0_IPV6_PARSE_EN;

	अगर (alx_hw_giga(hw))
		ALX_SET_FIELD(val, ALX_RXQ0_ASPM_THRESH,
			      ALX_RXQ0_ASPM_THRESH_100M);

	alx_ग_लिखो_mem32(hw, ALX_RXQ0, val);

	val = alx_पढ़ो_mem32(hw, ALX_DMA);
	val = ALX_DMA_RORDER_MODE_OUT << ALX_DMA_RORDER_MODE_SHIFT |
	      ALX_DMA_RREQ_PRI_DATA |
	      max_payload << ALX_DMA_RREQ_BLEN_SHIFT |
	      ALX_DMA_WDLY_CNT_DEF << ALX_DMA_WDLY_CNT_SHIFT |
	      ALX_DMA_RDLY_CNT_DEF << ALX_DMA_RDLY_CNT_SHIFT |
	      (hw->dma_chnl - 1) << ALX_DMA_RCHNL_SEL_SHIFT;
	alx_ग_लिखो_mem32(hw, ALX_DMA, val);

	/* शेष multi-tx-q weights */
	val = ALX_WRR_PRI_RESTRICT_NONE << ALX_WRR_PRI_SHIFT |
	      4 << ALX_WRR_PRI0_SHIFT |
	      4 << ALX_WRR_PRI1_SHIFT |
	      4 << ALX_WRR_PRI2_SHIFT |
	      4 << ALX_WRR_PRI3_SHIFT;
	alx_ग_लिखो_mem32(hw, ALX_WRR, val);
पूर्ण

व्योम alx_mask_msix(काष्ठा alx_hw *hw, पूर्णांक index, bool mask)
अणु
	u32 reg, val;

	reg = ALX_MSIX_ENTRY_BASE + index * PCI_MSIX_ENTRY_SIZE +
		PCI_MSIX_ENTRY_VECTOR_CTRL;

	val = mask ? PCI_MSIX_ENTRY_CTRL_MASKBIT : 0;

	alx_ग_लिखो_mem32(hw, reg, val);
	alx_post_ग_लिखो(hw);
पूर्ण


bool alx_get_phy_info(काष्ठा alx_hw *hw)
अणु
	u16  devs1, devs2;

	अगर (alx_पढ़ो_phy_reg(hw, MII_PHYSID1, &hw->phy_id[0]) ||
	    alx_पढ़ो_phy_reg(hw, MII_PHYSID2, &hw->phy_id[1]))
		वापस false;

	/* since we haven't PMA/PMD status2 register, we can't
	 * use mdio45_probe function क्रम prtad and mmds.
	 * use fixed MMD3 to get mmds.
	 */
	अगर (alx_पढ़ो_phy_ext(hw, 3, MDIO_DEVS1, &devs1) ||
	    alx_पढ़ो_phy_ext(hw, 3, MDIO_DEVS2, &devs2))
		वापस false;
	hw->mdio.mmds = devs1 | devs2 << 16;

	वापस true;
पूर्ण

व्योम alx_update_hw_stats(काष्ठा alx_hw *hw)
अणु
	/* RX stats */
	hw->stats.rx_ok          += alx_पढ़ो_mem32(hw, ALX_MIB_RX_OK);
	hw->stats.rx_bcast       += alx_पढ़ो_mem32(hw, ALX_MIB_RX_BCAST);
	hw->stats.rx_mcast       += alx_पढ़ो_mem32(hw, ALX_MIB_RX_MCAST);
	hw->stats.rx_छोड़ो       += alx_पढ़ो_mem32(hw, ALX_MIB_RX_PAUSE);
	hw->stats.rx_ctrl        += alx_पढ़ो_mem32(hw, ALX_MIB_RX_CTRL);
	hw->stats.rx_fcs_err     += alx_पढ़ो_mem32(hw, ALX_MIB_RX_FCS_ERR);
	hw->stats.rx_len_err     += alx_पढ़ो_mem32(hw, ALX_MIB_RX_LEN_ERR);
	hw->stats.rx_byte_cnt    += alx_पढ़ो_mem32(hw, ALX_MIB_RX_BYTE_CNT);
	hw->stats.rx_runt        += alx_पढ़ो_mem32(hw, ALX_MIB_RX_RUNT);
	hw->stats.rx_frag        += alx_पढ़ो_mem32(hw, ALX_MIB_RX_FRAG);
	hw->stats.rx_sz_64B      += alx_पढ़ो_mem32(hw, ALX_MIB_RX_SZ_64B);
	hw->stats.rx_sz_127B     += alx_पढ़ो_mem32(hw, ALX_MIB_RX_SZ_127B);
	hw->stats.rx_sz_255B     += alx_पढ़ो_mem32(hw, ALX_MIB_RX_SZ_255B);
	hw->stats.rx_sz_511B     += alx_पढ़ो_mem32(hw, ALX_MIB_RX_SZ_511B);
	hw->stats.rx_sz_1023B    += alx_पढ़ो_mem32(hw, ALX_MIB_RX_SZ_1023B);
	hw->stats.rx_sz_1518B    += alx_पढ़ो_mem32(hw, ALX_MIB_RX_SZ_1518B);
	hw->stats.rx_sz_max      += alx_पढ़ो_mem32(hw, ALX_MIB_RX_SZ_MAX);
	hw->stats.rx_ov_sz       += alx_पढ़ो_mem32(hw, ALX_MIB_RX_OV_SZ);
	hw->stats.rx_ov_rxf      += alx_पढ़ो_mem32(hw, ALX_MIB_RX_OV_RXF);
	hw->stats.rx_ov_rrd      += alx_पढ़ो_mem32(hw, ALX_MIB_RX_OV_RRD);
	hw->stats.rx_align_err   += alx_पढ़ो_mem32(hw, ALX_MIB_RX_ALIGN_ERR);
	hw->stats.rx_bc_byte_cnt += alx_पढ़ो_mem32(hw, ALX_MIB_RX_BCCNT);
	hw->stats.rx_mc_byte_cnt += alx_पढ़ो_mem32(hw, ALX_MIB_RX_MCCNT);
	hw->stats.rx_err_addr    += alx_पढ़ो_mem32(hw, ALX_MIB_RX_ERRADDR);

	/* TX stats */
	hw->stats.tx_ok          += alx_पढ़ो_mem32(hw, ALX_MIB_TX_OK);
	hw->stats.tx_bcast       += alx_पढ़ो_mem32(hw, ALX_MIB_TX_BCAST);
	hw->stats.tx_mcast       += alx_पढ़ो_mem32(hw, ALX_MIB_TX_MCAST);
	hw->stats.tx_छोड़ो       += alx_पढ़ो_mem32(hw, ALX_MIB_TX_PAUSE);
	hw->stats.tx_exc_defer   += alx_पढ़ो_mem32(hw, ALX_MIB_TX_EXC_DEFER);
	hw->stats.tx_ctrl        += alx_पढ़ो_mem32(hw, ALX_MIB_TX_CTRL);
	hw->stats.tx_defer       += alx_पढ़ो_mem32(hw, ALX_MIB_TX_DEFER);
	hw->stats.tx_byte_cnt    += alx_पढ़ो_mem32(hw, ALX_MIB_TX_BYTE_CNT);
	hw->stats.tx_sz_64B      += alx_पढ़ो_mem32(hw, ALX_MIB_TX_SZ_64B);
	hw->stats.tx_sz_127B     += alx_पढ़ो_mem32(hw, ALX_MIB_TX_SZ_127B);
	hw->stats.tx_sz_255B     += alx_पढ़ो_mem32(hw, ALX_MIB_TX_SZ_255B);
	hw->stats.tx_sz_511B     += alx_पढ़ो_mem32(hw, ALX_MIB_TX_SZ_511B);
	hw->stats.tx_sz_1023B    += alx_पढ़ो_mem32(hw, ALX_MIB_TX_SZ_1023B);
	hw->stats.tx_sz_1518B    += alx_पढ़ो_mem32(hw, ALX_MIB_TX_SZ_1518B);
	hw->stats.tx_sz_max      += alx_पढ़ो_mem32(hw, ALX_MIB_TX_SZ_MAX);
	hw->stats.tx_single_col  += alx_पढ़ो_mem32(hw, ALX_MIB_TX_SINGLE_COL);
	hw->stats.tx_multi_col   += alx_पढ़ो_mem32(hw, ALX_MIB_TX_MULTI_COL);
	hw->stats.tx_late_col    += alx_पढ़ो_mem32(hw, ALX_MIB_TX_LATE_COL);
	hw->stats.tx_पात_col   += alx_पढ़ो_mem32(hw, ALX_MIB_TX_ABORT_COL);
	hw->stats.tx_underrun    += alx_पढ़ो_mem32(hw, ALX_MIB_TX_UNDERRUN);
	hw->stats.tx_trd_eop     += alx_पढ़ो_mem32(hw, ALX_MIB_TX_TRD_EOP);
	hw->stats.tx_len_err     += alx_पढ़ो_mem32(hw, ALX_MIB_TX_LEN_ERR);
	hw->stats.tx_trunc       += alx_पढ़ो_mem32(hw, ALX_MIB_TX_TRUNC);
	hw->stats.tx_bc_byte_cnt += alx_पढ़ो_mem32(hw, ALX_MIB_TX_BCCNT);
	hw->stats.tx_mc_byte_cnt += alx_पढ़ो_mem32(hw, ALX_MIB_TX_MCCNT);

	hw->stats.update         += alx_पढ़ो_mem32(hw, ALX_MIB_UPDATE);
पूर्ण
