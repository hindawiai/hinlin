<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This is the driver क्रम the GMAC on-chip Ethernet controller क्रम ST SoCs.
  DWC Ether MAC 10/100/1000 Universal version 3.41a  has been used क्रम
  developing this code.

  This only implements the mac core functions क्रम this chip.

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <linux/ethtool.h>
#समावेश <net/dsa.h>
#समावेश <यंत्र/पन.स>
#समावेश "stmmac.h"
#समावेश "stmmac_pcs.h"
#समावेश "dwmac1000.h"

अटल व्योम dwmac1000_core_init(काष्ठा mac_device_info *hw,
				काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + GMAC_CONTROL);
	पूर्णांक mtu = dev->mtu;

	/* Configure GMAC core */
	value |= GMAC_CORE_INIT;

	/* Clear ACS bit because Ethernet चयन tagging क्रमmats such as
	 * Broadcom tags can look like invalid LLC/SNAP packets and cause the
	 * hardware to truncate packets on reception.
	 */
	अगर (netdev_uses_dsa(dev) || !priv->plat->enh_desc)
		value &= ~GMAC_CONTROL_ACS;

	अगर (mtu > 1500)
		value |= GMAC_CONTROL_2K;
	अगर (mtu > 2000)
		value |= GMAC_CONTROL_JE;

	अगर (hw->ps) अणु
		value |= GMAC_CONTROL_TE;

		value &= ~hw->link.speed_mask;
		चयन (hw->ps) अणु
		हाल SPEED_1000:
			value |= hw->link.speed1000;
			अवरोध;
		हाल SPEED_100:
			value |= hw->link.speed100;
			अवरोध;
		हाल SPEED_10:
			value |= hw->link.speed10;
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोl(value, ioaddr + GMAC_CONTROL);

	/* Mask GMAC पूर्णांकerrupts */
	value = GMAC_INT_DEFAULT_MASK;

	अगर (hw->pcs)
		value &= ~GMAC_INT_DISABLE_PCS;

	ग_लिखोl(value, ioaddr + GMAC_INT_MASK);

#अगर_घोषित STMMAC_VLAN_TAG_USED
	/* Tag detection without filtering */
	ग_लिखोl(0x0, ioaddr + GMAC_VLAN_TAG);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक dwmac1000_rx_ipc_enable(काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + GMAC_CONTROL);

	अगर (hw->rx_csum)
		value |= GMAC_CONTROL_IPC;
	अन्यथा
		value &= ~GMAC_CONTROL_IPC;

	ग_लिखोl(value, ioaddr + GMAC_CONTROL);

	value = पढ़ोl(ioaddr + GMAC_CONTROL);

	वापस !!(value & GMAC_CONTROL_IPC);
पूर्ण

अटल व्योम dwmac1000_dump_regs(काष्ठा mac_device_info *hw, u32 *reg_space)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	पूर्णांक i;

	क्रम (i = 0; i < 55; i++)
		reg_space[i] = पढ़ोl(ioaddr + i * 4);
पूर्ण

अटल व्योम dwmac1000_set_umac_addr(काष्ठा mac_device_info *hw,
				    अचिन्हित अक्षर *addr,
				    अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	sपंचांगmac_set_mac_addr(ioaddr, addr, GMAC_ADDR_HIGH(reg_n),
			    GMAC_ADDR_LOW(reg_n));
पूर्ण

अटल व्योम dwmac1000_get_umac_addr(काष्ठा mac_device_info *hw,
				    अचिन्हित अक्षर *addr,
				    अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	sपंचांगmac_get_mac_addr(ioaddr, addr, GMAC_ADDR_HIGH(reg_n),
			    GMAC_ADDR_LOW(reg_n));
पूर्ण

अटल व्योम dwmac1000_set_mchash(व्योम __iomem *ioaddr, u32 *mcfilterbits,
				 पूर्णांक mcbitslog2)
अणु
	पूर्णांक numhashregs, regs;

	चयन (mcbitslog2) अणु
	हाल 6:
		ग_लिखोl(mcfilterbits[0], ioaddr + GMAC_HASH_LOW);
		ग_लिखोl(mcfilterbits[1], ioaddr + GMAC_HASH_HIGH);
		वापस;
	हाल 7:
		numhashregs = 4;
		अवरोध;
	हाल 8:
		numhashregs = 8;
		अवरोध;
	शेष:
		pr_debug("STMMAC: err in setting multicast filter\n");
		वापस;
	पूर्ण
	क्रम (regs = 0; regs < numhashregs; regs++)
		ग_लिखोl(mcfilterbits[regs],
		       ioaddr + GMAC_EXTHASH_BASE + regs * 4);
पूर्ण

अटल व्योम dwmac1000_set_filter(काष्ठा mac_device_info *hw,
				 काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = (व्योम __iomem *)dev->base_addr;
	अचिन्हित पूर्णांक value = 0;
	अचिन्हित पूर्णांक perfect_addr_number = hw->unicast_filter_entries;
	u32 mc_filter[8];
	पूर्णांक mcbitslog2 = hw->mcast_bits_log2;

	pr_debug("%s: # mcasts %d, # unicast %d\n", __func__,
		 netdev_mc_count(dev), netdev_uc_count(dev));

	स_रखो(mc_filter, 0, माप(mc_filter));

	अगर (dev->flags & IFF_PROMISC) अणु
		value = GMAC_FRAME_FILTER_PR | GMAC_FRAME_FILTER_PCF;
	पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI) अणु
		value = GMAC_FRAME_FILTER_PM;	/* pass all multi */
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev) && (mcbitslog2 == 0)) अणु
		/* Fall back to all multicast अगर we've no filter */
		value = GMAC_FRAME_FILTER_PM;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;

		/* Hash filter क्रम multicast */
		value = GMAC_FRAME_FILTER_HMC;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			/* The upper n bits of the calculated CRC are used to
			 * index the contents of the hash table. The number of
			 * bits used depends on the hardware configuration
			 * selected at core configuration समय.
			 */
			पूर्णांक bit_nr = bitrev32(~crc32_le(~0, ha->addr,
					      ETH_ALEN)) >>
					      (32 - mcbitslog2);
			/* The most signअगरicant bit determines the रेजिस्टर to
			 * use (H/L) जबतक the other 5 bits determine the bit
			 * within the रेजिस्टर.
			 */
			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
		पूर्ण
	पूर्ण

	value |= GMAC_FRAME_FILTER_HPF;
	dwmac1000_set_mchash(ioaddr, mc_filter, mcbitslog2);

	/* Handle multiple unicast addresses (perfect filtering) */
	अगर (netdev_uc_count(dev) > perfect_addr_number)
		/* Switch to promiscuous mode अगर more than unicast
		 * addresses are requested than supported by hardware.
		 */
		value |= GMAC_FRAME_FILTER_PR;
	अन्यथा अणु
		पूर्णांक reg = 1;
		काष्ठा netdev_hw_addr *ha;

		netdev_क्रम_each_uc_addr(ha, dev) अणु
			sपंचांगmac_set_mac_addr(ioaddr, ha->addr,
					    GMAC_ADDR_HIGH(reg),
					    GMAC_ADDR_LOW(reg));
			reg++;
		पूर्ण

		जबतक (reg < perfect_addr_number) अणु
			ग_लिखोl(0, ioaddr + GMAC_ADDR_HIGH(reg));
			ग_लिखोl(0, ioaddr + GMAC_ADDR_LOW(reg));
			reg++;
		पूर्ण
	पूर्ण

#अगर_घोषित FRAME_FILTER_DEBUG
	/* Enable Receive all mode (to debug filtering_fail errors) */
	value |= GMAC_FRAME_FILTER_RA;
#पूर्ण_अगर
	ग_लिखोl(value, ioaddr + GMAC_FRAME_FILTER);
पूर्ण


अटल व्योम dwmac1000_flow_ctrl(काष्ठा mac_device_info *hw, अचिन्हित पूर्णांक duplex,
				अचिन्हित पूर्णांक fc, अचिन्हित पूर्णांक छोड़ो_समय,
				u32 tx_cnt)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	/* Set flow such that DZPQ in Mac Register 6 is 0,
	 * and unicast छोड़ो detect is enabled.
	 */
	अचिन्हित पूर्णांक flow = GMAC_FLOW_CTRL_UP;

	pr_debug("GMAC Flow-Control:\n");
	अगर (fc & FLOW_RX) अणु
		pr_debug("\tReceive Flow-Control ON\n");
		flow |= GMAC_FLOW_CTRL_RFE;
	पूर्ण
	अगर (fc & FLOW_TX) अणु
		pr_debug("\tTransmit Flow-Control ON\n");
		flow |= GMAC_FLOW_CTRL_TFE;
	पूर्ण

	अगर (duplex) अणु
		pr_debug("\tduplex mode: PAUSE %d\n", छोड़ो_समय);
		flow |= (छोड़ो_समय << GMAC_FLOW_CTRL_PT_SHIFT);
	पूर्ण

	ग_लिखोl(flow, ioaddr + GMAC_FLOW_CTRL);
पूर्ण

अटल व्योम dwmac1000_pmt(काष्ठा mac_device_info *hw, अचिन्हित दीर्घ mode)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	अचिन्हित पूर्णांक pmt = 0;

	अगर (mode & WAKE_MAGIC) अणु
		pr_debug("GMAC: WOL Magic frame\n");
		pmt |= घातer_करोwn | magic_pkt_en;
	पूर्ण
	अगर (mode & WAKE_UCAST) अणु
		pr_debug("GMAC: WOL on global unicast\n");
		pmt |= घातer_करोwn | global_unicast | wake_up_frame_en;
	पूर्ण

	ग_लिखोl(pmt, ioaddr + GMAC_PMT);
पूर्ण

/* RGMII or SMII पूर्णांकerface */
अटल व्योम dwmac1000_rgsmii(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_extra_stats *x)
अणु
	u32 status;

	status = पढ़ोl(ioaddr + GMAC_RGSMIIIS);
	x->irq_rgmii_n++;

	/* Check the link status */
	अगर (status & GMAC_RGSMIIIS_LNKSTS) अणु
		पूर्णांक speed_value;

		x->pcs_link = 1;

		speed_value = ((status & GMAC_RGSMIIIS_SPEED) >>
			       GMAC_RGSMIIIS_SPEED_SHIFT);
		अगर (speed_value == GMAC_RGSMIIIS_SPEED_125)
			x->pcs_speed = SPEED_1000;
		अन्यथा अगर (speed_value == GMAC_RGSMIIIS_SPEED_25)
			x->pcs_speed = SPEED_100;
		अन्यथा
			x->pcs_speed = SPEED_10;

		x->pcs_duplex = (status & GMAC_RGSMIIIS_LNKMOD_MASK);

		pr_info("Link is Up - %d/%s\n", (पूर्णांक)x->pcs_speed,
			x->pcs_duplex ? "Full" : "Half");
	पूर्ण अन्यथा अणु
		x->pcs_link = 0;
		pr_info("Link is Down\n");
	पूर्ण
पूर्ण

अटल पूर्णांक dwmac1000_irq_status(काष्ठा mac_device_info *hw,
				काष्ठा sपंचांगmac_extra_stats *x)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 पूर्णांकr_status = पढ़ोl(ioaddr + GMAC_INT_STATUS);
	u32 पूर्णांकr_mask = पढ़ोl(ioaddr + GMAC_INT_MASK);
	पूर्णांक ret = 0;

	/* Discard masked bits */
	पूर्णांकr_status &= ~पूर्णांकr_mask;

	/* Not used events (e.g. MMC पूर्णांकerrupts) are not handled. */
	अगर ((पूर्णांकr_status & GMAC_INT_STATUS_MMCTIS))
		x->mmc_tx_irq_n++;
	अगर (unlikely(पूर्णांकr_status & GMAC_INT_STATUS_MMCRIS))
		x->mmc_rx_irq_n++;
	अगर (unlikely(पूर्णांकr_status & GMAC_INT_STATUS_MMCCSUM))
		x->mmc_rx_csum_offload_irq_n++;
	अगर (unlikely(पूर्णांकr_status & GMAC_INT_DISABLE_PMT)) अणु
		/* clear the PMT bits 5 and 6 by पढ़ोing the PMT status reg */
		पढ़ोl(ioaddr + GMAC_PMT);
		x->irq_receive_pmt_irq_n++;
	पूर्ण

	/* MAC tx/rx EEE LPI entry/निकास पूर्णांकerrupts */
	अगर (पूर्णांकr_status & GMAC_INT_STATUS_LPIIS) अणु
		/* Clean LPI पूर्णांकerrupt by पढ़ोing the Reg 12 */
		ret = पढ़ोl(ioaddr + LPI_CTRL_STATUS);

		अगर (ret & LPI_CTRL_STATUS_TLPIEN)
			x->irq_tx_path_in_lpi_mode_n++;
		अगर (ret & LPI_CTRL_STATUS_TLPIEX)
			x->irq_tx_path_निकास_lpi_mode_n++;
		अगर (ret & LPI_CTRL_STATUS_RLPIEN)
			x->irq_rx_path_in_lpi_mode_n++;
		अगर (ret & LPI_CTRL_STATUS_RLPIEX)
			x->irq_rx_path_निकास_lpi_mode_n++;
	पूर्ण

	dwmac_pcs_isr(ioaddr, GMAC_PCS_BASE, पूर्णांकr_status, x);

	अगर (पूर्णांकr_status & PCS_RGSMIIIS_IRQ)
		dwmac1000_rgsmii(ioaddr, x);

	वापस ret;
पूर्ण

अटल व्योम dwmac1000_set_eee_mode(काष्ठा mac_device_info *hw,
				   bool en_tx_lpi_घड़ीgating)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	/*TODO - en_tx_lpi_घड़ीgating treaपंचांगent */

	/* Enable the link status receive on RGMII, SGMII ore SMII
	 * receive path and inकाष्ठा the transmit to enter in LPI
	 * state.
	 */
	value = पढ़ोl(ioaddr + LPI_CTRL_STATUS);
	value |= LPI_CTRL_STATUS_LPIEN | LPI_CTRL_STATUS_LPITXA;
	ग_लिखोl(value, ioaddr + LPI_CTRL_STATUS);
पूर्ण

अटल व्योम dwmac1000_reset_eee_mode(काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + LPI_CTRL_STATUS);
	value &= ~(LPI_CTRL_STATUS_LPIEN | LPI_CTRL_STATUS_LPITXA);
	ग_लिखोl(value, ioaddr + LPI_CTRL_STATUS);
पूर्ण

अटल व्योम dwmac1000_set_eee_pls(काष्ठा mac_device_info *hw, पूर्णांक link)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + LPI_CTRL_STATUS);

	अगर (link)
		value |= LPI_CTRL_STATUS_PLS;
	अन्यथा
		value &= ~LPI_CTRL_STATUS_PLS;

	ग_लिखोl(value, ioaddr + LPI_CTRL_STATUS);
पूर्ण

अटल व्योम dwmac1000_set_eee_समयr(काष्ठा mac_device_info *hw, पूर्णांक ls, पूर्णांक tw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	पूर्णांक value = ((tw & 0xffff)) | ((ls & 0x7ff) << 16);

	/* Program the समयrs in the LPI समयr control रेजिस्टर:
	 * LS: minimum समय (ms) क्रम which the link
	 *  status from PHY should be ok beक्रमe transmitting
	 *  the LPI pattern.
	 * TW: minimum समय (us) क्रम which the core रुकोs
	 *  after it has stopped transmitting the LPI pattern.
	 */
	ग_लिखोl(value, ioaddr + LPI_TIMER_CTRL);
पूर्ण

अटल व्योम dwmac1000_ctrl_ane(व्योम __iomem *ioaddr, bool ane, bool srgmi_ral,
			       bool loopback)
अणु
	dwmac_ctrl_ane(ioaddr, GMAC_PCS_BASE, ane, srgmi_ral, loopback);
पूर्ण

अटल व्योम dwmac1000_rane(व्योम __iomem *ioaddr, bool restart)
अणु
	dwmac_rane(ioaddr, GMAC_PCS_BASE, restart);
पूर्ण

अटल व्योम dwmac1000_get_adv_lp(व्योम __iomem *ioaddr, काष्ठा rgmii_adv *adv)
अणु
	dwmac_get_adv_lp(ioaddr, GMAC_PCS_BASE, adv);
पूर्ण

अटल व्योम dwmac1000_debug(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_extra_stats *x,
			    u32 rx_queues, u32 tx_queues)
अणु
	u32 value = पढ़ोl(ioaddr + GMAC_DEBUG);

	अगर (value & GMAC_DEBUG_TXSTSFSTS)
		x->mtl_tx_status_fअगरo_full++;
	अगर (value & GMAC_DEBUG_TXFSTS)
		x->mtl_tx_fअगरo_not_empty++;
	अगर (value & GMAC_DEBUG_TWCSTS)
		x->mmtl_fअगरo_ctrl++;
	अगर (value & GMAC_DEBUG_TRCSTS_MASK) अणु
		u32 trcsts = (value & GMAC_DEBUG_TRCSTS_MASK)
			     >> GMAC_DEBUG_TRCSTS_SHIFT;
		अगर (trcsts == GMAC_DEBUG_TRCSTS_WRITE)
			x->mtl_tx_fअगरo_पढ़ो_ctrl_ग_लिखो++;
		अन्यथा अगर (trcsts == GMAC_DEBUG_TRCSTS_TXW)
			x->mtl_tx_fअगरo_पढ़ो_ctrl_रुको++;
		अन्यथा अगर (trcsts == GMAC_DEBUG_TRCSTS_READ)
			x->mtl_tx_fअगरo_पढ़ो_ctrl_पढ़ो++;
		अन्यथा
			x->mtl_tx_fअगरo_पढ़ो_ctrl_idle++;
	पूर्ण
	अगर (value & GMAC_DEBUG_TXPAUSED)
		x->mac_tx_in_छोड़ो++;
	अगर (value & GMAC_DEBUG_TFCSTS_MASK) अणु
		u32 tfcsts = (value & GMAC_DEBUG_TFCSTS_MASK)
			      >> GMAC_DEBUG_TFCSTS_SHIFT;

		अगर (tfcsts == GMAC_DEBUG_TFCSTS_XFER)
			x->mac_tx_frame_ctrl_xfer++;
		अन्यथा अगर (tfcsts == GMAC_DEBUG_TFCSTS_GEN_PAUSE)
			x->mac_tx_frame_ctrl_छोड़ो++;
		अन्यथा अगर (tfcsts == GMAC_DEBUG_TFCSTS_WAIT)
			x->mac_tx_frame_ctrl_रुको++;
		अन्यथा
			x->mac_tx_frame_ctrl_idle++;
	पूर्ण
	अगर (value & GMAC_DEBUG_TPESTS)
		x->mac_gmii_tx_proto_engine++;
	अगर (value & GMAC_DEBUG_RXFSTS_MASK) अणु
		u32 rxfsts = (value & GMAC_DEBUG_RXFSTS_MASK)
			     >> GMAC_DEBUG_RRCSTS_SHIFT;

		अगर (rxfsts == GMAC_DEBUG_RXFSTS_FULL)
			x->mtl_rx_fअगरo_fill_level_full++;
		अन्यथा अगर (rxfsts == GMAC_DEBUG_RXFSTS_AT)
			x->mtl_rx_fअगरo_fill_above_thresh++;
		अन्यथा अगर (rxfsts == GMAC_DEBUG_RXFSTS_BT)
			x->mtl_rx_fअगरo_fill_below_thresh++;
		अन्यथा
			x->mtl_rx_fअगरo_fill_level_empty++;
	पूर्ण
	अगर (value & GMAC_DEBUG_RRCSTS_MASK) अणु
		u32 rrcsts = (value & GMAC_DEBUG_RRCSTS_MASK) >>
			     GMAC_DEBUG_RRCSTS_SHIFT;

		अगर (rrcsts == GMAC_DEBUG_RRCSTS_FLUSH)
			x->mtl_rx_fअगरo_पढ़ो_ctrl_flush++;
		अन्यथा अगर (rrcsts == GMAC_DEBUG_RRCSTS_RSTAT)
			x->mtl_rx_fअगरo_पढ़ो_ctrl_पढ़ो_data++;
		अन्यथा अगर (rrcsts == GMAC_DEBUG_RRCSTS_RDATA)
			x->mtl_rx_fअगरo_पढ़ो_ctrl_status++;
		अन्यथा
			x->mtl_rx_fअगरo_पढ़ो_ctrl_idle++;
	पूर्ण
	अगर (value & GMAC_DEBUG_RWCSTS)
		x->mtl_rx_fअगरo_ctrl_active++;
	अगर (value & GMAC_DEBUG_RFCFCSTS_MASK)
		x->mac_rx_frame_ctrl_fअगरo = (value & GMAC_DEBUG_RFCFCSTS_MASK)
					    >> GMAC_DEBUG_RFCFCSTS_SHIFT;
	अगर (value & GMAC_DEBUG_RPESTS)
		x->mac_gmii_rx_proto_engine++;
पूर्ण

अटल व्योम dwmac1000_set_mac_loopback(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 value = पढ़ोl(ioaddr + GMAC_CONTROL);

	अगर (enable)
		value |= GMAC_CONTROL_LM;
	अन्यथा
		value &= ~GMAC_CONTROL_LM;

	ग_लिखोl(value, ioaddr + GMAC_CONTROL);
पूर्ण

स्थिर काष्ठा sपंचांगmac_ops dwmac1000_ops = अणु
	.core_init = dwmac1000_core_init,
	.set_mac = sपंचांगmac_set_mac,
	.rx_ipc = dwmac1000_rx_ipc_enable,
	.dump_regs = dwmac1000_dump_regs,
	.host_irq_status = dwmac1000_irq_status,
	.set_filter = dwmac1000_set_filter,
	.flow_ctrl = dwmac1000_flow_ctrl,
	.pmt = dwmac1000_pmt,
	.set_umac_addr = dwmac1000_set_umac_addr,
	.get_umac_addr = dwmac1000_get_umac_addr,
	.set_eee_mode = dwmac1000_set_eee_mode,
	.reset_eee_mode = dwmac1000_reset_eee_mode,
	.set_eee_समयr = dwmac1000_set_eee_समयr,
	.set_eee_pls = dwmac1000_set_eee_pls,
	.debug = dwmac1000_debug,
	.pcs_ctrl_ane = dwmac1000_ctrl_ane,
	.pcs_rane = dwmac1000_rane,
	.pcs_get_adv_lp = dwmac1000_get_adv_lp,
	.set_mac_loopback = dwmac1000_set_mac_loopback,
पूर्ण;

पूर्णांक dwmac1000_setup(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा mac_device_info *mac = priv->hw;

	dev_info(priv->device, "\tDWMAC1000\n");

	priv->dev->priv_flags |= IFF_UNICAST_FLT;
	mac->pcsr = priv->ioaddr;
	mac->multicast_filter_bins = priv->plat->multicast_filter_bins;
	mac->unicast_filter_entries = priv->plat->unicast_filter_entries;
	mac->mcast_bits_log2 = 0;

	अगर (mac->multicast_filter_bins)
		mac->mcast_bits_log2 = ilog2(mac->multicast_filter_bins);

	mac->link.duplex = GMAC_CONTROL_DM;
	mac->link.speed10 = GMAC_CONTROL_PS;
	mac->link.speed100 = GMAC_CONTROL_PS | GMAC_CONTROL_FES;
	mac->link.speed1000 = 0;
	mac->link.speed_mask = GMAC_CONTROL_PS | GMAC_CONTROL_FES;
	mac->mii.addr = GMAC_MII_ADDR;
	mac->mii.data = GMAC_MII_DATA;
	mac->mii.addr_shअगरt = 11;
	mac->mii.addr_mask = 0x0000F800;
	mac->mii.reg_shअगरt = 6;
	mac->mii.reg_mask = 0x000007C0;
	mac->mii.clk_csr_shअगरt = 2;
	mac->mii.clk_csr_mask = GENMASK(5, 2);

	वापस 0;
पूर्ण
