<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is the driver क्रम the GMAC on-chip Ethernet controller क्रम ST SoCs.
 * DWC Ether MAC version 4.00  has been used क्रम developing this code.
 *
 * This only implements the mac core functions क्रम this chip.
 *
 * Copyright (C) 2015  STMicroelectronics Ltd
 *
 * Author: Alexandre Torgue <alexandre.torgue@st.com>
 */

#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पन.स>
#समावेश <net/dsa.h>
#समावेश "stmmac.h"
#समावेश "stmmac_pcs.h"
#समावेश "dwmac4.h"
#समावेश "dwmac5.h"

अटल व्योम dwmac4_core_init(काष्ठा mac_device_info *hw,
			     काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + GMAC_CONFIG);

	value |= GMAC_CORE_INIT;

	अगर (hw->ps) अणु
		value |= GMAC_CONFIG_TE;

		value &= hw->link.speed_mask;
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

	ग_लिखोl(value, ioaddr + GMAC_CONFIG);

	/* Enable GMAC पूर्णांकerrupts */
	value = GMAC_INT_DEFAULT_ENABLE;

	अगर (hw->pcs)
		value |= GMAC_PCS_IRQ_DEFAULT;

	/* Enable FPE पूर्णांकerrupt */
	अगर ((GMAC_HW_FEAT_FPESEL & पढ़ोl(ioaddr + GMAC_HW_FEATURE3)) >> 26)
		value |= GMAC_INT_FPE_EN;

	ग_लिखोl(value, ioaddr + GMAC_INT_EN);
पूर्ण

अटल व्योम dwmac4_rx_queue_enable(काष्ठा mac_device_info *hw,
				   u8 mode, u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + GMAC_RXQ_CTRL0);

	value &= GMAC_RX_QUEUE_CLEAR(queue);
	अगर (mode == MTL_QUEUE_AVB)
		value |= GMAC_RX_AV_QUEUE_ENABLE(queue);
	अन्यथा अगर (mode == MTL_QUEUE_DCB)
		value |= GMAC_RX_DCB_QUEUE_ENABLE(queue);

	ग_लिखोl(value, ioaddr + GMAC_RXQ_CTRL0);
पूर्ण

अटल व्योम dwmac4_rx_queue_priority(काष्ठा mac_device_info *hw,
				     u32 prio, u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 base_रेजिस्टर;
	u32 value;

	base_रेजिस्टर = (queue < 4) ? GMAC_RXQ_CTRL2 : GMAC_RXQ_CTRL3;
	अगर (queue >= 4)
		queue -= 4;

	value = पढ़ोl(ioaddr + base_रेजिस्टर);

	value &= ~GMAC_RXQCTRL_PSRQX_MASK(queue);
	value |= (prio << GMAC_RXQCTRL_PSRQX_SHIFT(queue)) &
						GMAC_RXQCTRL_PSRQX_MASK(queue);
	ग_लिखोl(value, ioaddr + base_रेजिस्टर);
पूर्ण

अटल व्योम dwmac4_tx_queue_priority(काष्ठा mac_device_info *hw,
				     u32 prio, u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 base_रेजिस्टर;
	u32 value;

	base_रेजिस्टर = (queue < 4) ? GMAC_TXQ_PRTY_MAP0 : GMAC_TXQ_PRTY_MAP1;
	अगर (queue >= 4)
		queue -= 4;

	value = पढ़ोl(ioaddr + base_रेजिस्टर);

	value &= ~GMAC_TXQCTRL_PSTQX_MASK(queue);
	value |= (prio << GMAC_TXQCTRL_PSTQX_SHIFT(queue)) &
						GMAC_TXQCTRL_PSTQX_MASK(queue);

	ग_लिखोl(value, ioaddr + base_रेजिस्टर);
पूर्ण

अटल व्योम dwmac4_rx_queue_routing(काष्ठा mac_device_info *hw,
				    u8 packet, u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	अटल स्थिर काष्ठा sपंचांगmac_rx_routing route_possibilities[] = अणु
		अणु GMAC_RXQCTRL_AVCPQ_MASK, GMAC_RXQCTRL_AVCPQ_SHIFT पूर्ण,
		अणु GMAC_RXQCTRL_PTPQ_MASK, GMAC_RXQCTRL_PTPQ_SHIFT पूर्ण,
		अणु GMAC_RXQCTRL_DCBCPQ_MASK, GMAC_RXQCTRL_DCBCPQ_SHIFT पूर्ण,
		अणु GMAC_RXQCTRL_UPQ_MASK, GMAC_RXQCTRL_UPQ_SHIFT पूर्ण,
		अणु GMAC_RXQCTRL_MCBCQ_MASK, GMAC_RXQCTRL_MCBCQ_SHIFT पूर्ण,
	पूर्ण;

	value = पढ़ोl(ioaddr + GMAC_RXQ_CTRL1);

	/* routing configuration */
	value &= ~route_possibilities[packet - 1].reg_mask;
	value |= (queue << route_possibilities[packet-1].reg_shअगरt) &
		 route_possibilities[packet - 1].reg_mask;

	/* some packets require extra ops */
	अगर (packet == PACKET_AVCPQ) अणु
		value &= ~GMAC_RXQCTRL_TACPQE;
		value |= 0x1 << GMAC_RXQCTRL_TACPQE_SHIFT;
	पूर्ण अन्यथा अगर (packet == PACKET_MCBCQ) अणु
		value &= ~GMAC_RXQCTRL_MCBCQEN;
		value |= 0x1 << GMAC_RXQCTRL_MCBCQEN_SHIFT;
	पूर्ण

	ग_लिखोl(value, ioaddr + GMAC_RXQ_CTRL1);
पूर्ण

अटल व्योम dwmac4_prog_mtl_rx_algorithms(काष्ठा mac_device_info *hw,
					  u32 rx_alg)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + MTL_OPERATION_MODE);

	value &= ~MTL_OPERATION_RAA;
	चयन (rx_alg) अणु
	हाल MTL_RX_ALGORITHM_SP:
		value |= MTL_OPERATION_RAA_SP;
		अवरोध;
	हाल MTL_RX_ALGORITHM_WSP:
		value |= MTL_OPERATION_RAA_WSP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(value, ioaddr + MTL_OPERATION_MODE);
पूर्ण

अटल व्योम dwmac4_prog_mtl_tx_algorithms(काष्ठा mac_device_info *hw,
					  u32 tx_alg)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + MTL_OPERATION_MODE);

	value &= ~MTL_OPERATION_SCHALG_MASK;
	चयन (tx_alg) अणु
	हाल MTL_TX_ALGORITHM_WRR:
		value |= MTL_OPERATION_SCHALG_WRR;
		अवरोध;
	हाल MTL_TX_ALGORITHM_WFQ:
		value |= MTL_OPERATION_SCHALG_WFQ;
		अवरोध;
	हाल MTL_TX_ALGORITHM_DWRR:
		value |= MTL_OPERATION_SCHALG_DWRR;
		अवरोध;
	हाल MTL_TX_ALGORITHM_SP:
		value |= MTL_OPERATION_SCHALG_SP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(value, ioaddr + MTL_OPERATION_MODE);
पूर्ण

अटल व्योम dwmac4_set_mtl_tx_queue_weight(काष्ठा mac_device_info *hw,
					   u32 weight, u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + MTL_TXQX_WEIGHT_BASE_ADDR(queue));

	value &= ~MTL_TXQ_WEIGHT_ISCQW_MASK;
	value |= weight & MTL_TXQ_WEIGHT_ISCQW_MASK;
	ग_लिखोl(value, ioaddr + MTL_TXQX_WEIGHT_BASE_ADDR(queue));
पूर्ण

अटल व्योम dwmac4_map_mtl_dma(काष्ठा mac_device_info *hw, u32 queue, u32 chan)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	अगर (queue < 4)
		value = पढ़ोl(ioaddr + MTL_RXQ_DMA_MAP0);
	अन्यथा
		value = पढ़ोl(ioaddr + MTL_RXQ_DMA_MAP1);

	अगर (queue == 0 || queue == 4) अणु
		value &= ~MTL_RXQ_DMA_Q04MDMACH_MASK;
		value |= MTL_RXQ_DMA_Q04MDMACH(chan);
	पूर्ण अन्यथा अणु
		value &= ~MTL_RXQ_DMA_QXMDMACH_MASK(queue);
		value |= MTL_RXQ_DMA_QXMDMACH(chan, queue);
	पूर्ण

	अगर (queue < 4)
		ग_लिखोl(value, ioaddr + MTL_RXQ_DMA_MAP0);
	अन्यथा
		ग_लिखोl(value, ioaddr + MTL_RXQ_DMA_MAP1);
पूर्ण

अटल व्योम dwmac4_config_cbs(काष्ठा mac_device_info *hw,
			      u32 send_slope, u32 idle_slope,
			      u32 high_credit, u32 low_credit, u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	pr_debug("Queue %d configured as AVB. Parameters:\n", queue);
	pr_debug("\tsend_slope: 0x%08x\n", send_slope);
	pr_debug("\tidle_slope: 0x%08x\n", idle_slope);
	pr_debug("\thigh_credit: 0x%08x\n", high_credit);
	pr_debug("\tlow_credit: 0x%08x\n", low_credit);

	/* enable AV algorithm */
	value = पढ़ोl(ioaddr + MTL_ETSX_CTRL_BASE_ADDR(queue));
	value |= MTL_ETS_CTRL_AVALG;
	value |= MTL_ETS_CTRL_CC;
	ग_लिखोl(value, ioaddr + MTL_ETSX_CTRL_BASE_ADDR(queue));

	/* configure send slope */
	value = पढ़ोl(ioaddr + MTL_SEND_SLP_CREDX_BASE_ADDR(queue));
	value &= ~MTL_SEND_SLP_CRED_SSC_MASK;
	value |= send_slope & MTL_SEND_SLP_CRED_SSC_MASK;
	ग_लिखोl(value, ioaddr + MTL_SEND_SLP_CREDX_BASE_ADDR(queue));

	/* configure idle slope (same रेजिस्टर as tx weight) */
	dwmac4_set_mtl_tx_queue_weight(hw, idle_slope, queue);

	/* configure high credit */
	value = पढ़ोl(ioaddr + MTL_HIGH_CREDX_BASE_ADDR(queue));
	value &= ~MTL_HIGH_CRED_HC_MASK;
	value |= high_credit & MTL_HIGH_CRED_HC_MASK;
	ग_लिखोl(value, ioaddr + MTL_HIGH_CREDX_BASE_ADDR(queue));

	/* configure high credit */
	value = पढ़ोl(ioaddr + MTL_LOW_CREDX_BASE_ADDR(queue));
	value &= ~MTL_HIGH_CRED_LC_MASK;
	value |= low_credit & MTL_HIGH_CRED_LC_MASK;
	ग_लिखोl(value, ioaddr + MTL_LOW_CREDX_BASE_ADDR(queue));
पूर्ण

अटल व्योम dwmac4_dump_regs(काष्ठा mac_device_info *hw, u32 *reg_space)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	पूर्णांक i;

	क्रम (i = 0; i < GMAC_REG_NUM; i++)
		reg_space[i] = पढ़ोl(ioaddr + i * 4);
पूर्ण

अटल पूर्णांक dwmac4_rx_ipc_enable(काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value = पढ़ोl(ioaddr + GMAC_CONFIG);

	अगर (hw->rx_csum)
		value |= GMAC_CONFIG_IPC;
	अन्यथा
		value &= ~GMAC_CONFIG_IPC;

	ग_लिखोl(value, ioaddr + GMAC_CONFIG);

	value = पढ़ोl(ioaddr + GMAC_CONFIG);

	वापस !!(value & GMAC_CONFIG_IPC);
पूर्ण

अटल व्योम dwmac4_pmt(काष्ठा mac_device_info *hw, अचिन्हित दीर्घ mode)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	अचिन्हित पूर्णांक pmt = 0;
	u32 config;

	अगर (mode & WAKE_MAGIC) अणु
		pr_debug("GMAC: WOL Magic frame\n");
		pmt |= घातer_करोwn | magic_pkt_en;
	पूर्ण
	अगर (mode & WAKE_UCAST) अणु
		pr_debug("GMAC: WOL on global unicast\n");
		pmt |= घातer_करोwn | global_unicast | wake_up_frame_en;
	पूर्ण

	अगर (pmt) अणु
		/* The receiver must be enabled क्रम WOL beक्रमe घातering करोwn */
		config = पढ़ोl(ioaddr + GMAC_CONFIG);
		config |= GMAC_CONFIG_RE;
		ग_लिखोl(config, ioaddr + GMAC_CONFIG);
	पूर्ण
	ग_लिखोl(pmt, ioaddr + GMAC_PMT);
पूर्ण

अटल व्योम dwmac4_set_umac_addr(काष्ठा mac_device_info *hw,
				 अचिन्हित अक्षर *addr, अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;

	sपंचांगmac_dwmac4_set_mac_addr(ioaddr, addr, GMAC_ADDR_HIGH(reg_n),
				   GMAC_ADDR_LOW(reg_n));
पूर्ण

अटल व्योम dwmac4_get_umac_addr(काष्ठा mac_device_info *hw,
				 अचिन्हित अक्षर *addr, अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;

	sपंचांगmac_dwmac4_get_mac_addr(ioaddr, addr, GMAC_ADDR_HIGH(reg_n),
				   GMAC_ADDR_LOW(reg_n));
पूर्ण

अटल व्योम dwmac4_set_eee_mode(काष्ठा mac_device_info *hw,
				bool en_tx_lpi_घड़ीgating)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	/* Enable the link status receive on RGMII, SGMII ore SMII
	 * receive path and inकाष्ठा the transmit to enter in LPI
	 * state.
	 */
	value = पढ़ोl(ioaddr + GMAC4_LPI_CTRL_STATUS);
	value |= GMAC4_LPI_CTRL_STATUS_LPIEN | GMAC4_LPI_CTRL_STATUS_LPITXA;

	अगर (en_tx_lpi_घड़ीgating)
		value |= GMAC4_LPI_CTRL_STATUS_LPITCSE;

	ग_लिखोl(value, ioaddr + GMAC4_LPI_CTRL_STATUS);
पूर्ण

अटल व्योम dwmac4_reset_eee_mode(काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + GMAC4_LPI_CTRL_STATUS);
	value &= ~(GMAC4_LPI_CTRL_STATUS_LPIEN | GMAC4_LPI_CTRL_STATUS_LPITXA);
	ग_लिखोl(value, ioaddr + GMAC4_LPI_CTRL_STATUS);
पूर्ण

अटल व्योम dwmac4_set_eee_pls(काष्ठा mac_device_info *hw, पूर्णांक link)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + GMAC4_LPI_CTRL_STATUS);

	अगर (link)
		value |= GMAC4_LPI_CTRL_STATUS_PLS;
	अन्यथा
		value &= ~GMAC4_LPI_CTRL_STATUS_PLS;

	ग_लिखोl(value, ioaddr + GMAC4_LPI_CTRL_STATUS);
पूर्ण

अटल व्योम dwmac4_set_eee_lpi_entry_समयr(काष्ठा mac_device_info *hw, पूर्णांक et)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	पूर्णांक value = et & STMMAC_ET_MAX;
	पूर्णांक regval;

	/* Program LPI entry समयr value पूर्णांकo रेजिस्टर */
	ग_लिखोl(value, ioaddr + GMAC4_LPI_ENTRY_TIMER);

	/* Enable/disable LPI entry समयr */
	regval = पढ़ोl(ioaddr + GMAC4_LPI_CTRL_STATUS);
	regval |= GMAC4_LPI_CTRL_STATUS_LPIEN | GMAC4_LPI_CTRL_STATUS_LPITXA;

	अगर (et)
		regval |= GMAC4_LPI_CTRL_STATUS_LPIATE;
	अन्यथा
		regval &= ~GMAC4_LPI_CTRL_STATUS_LPIATE;

	ग_लिखोl(regval, ioaddr + GMAC4_LPI_CTRL_STATUS);
पूर्ण

अटल व्योम dwmac4_set_eee_समयr(काष्ठा mac_device_info *hw, पूर्णांक ls, पूर्णांक tw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	पूर्णांक value = ((tw & 0xffff)) | ((ls & 0x3ff) << 16);

	/* Program the समयrs in the LPI समयr control रेजिस्टर:
	 * LS: minimum समय (ms) क्रम which the link
	 *  status from PHY should be ok beक्रमe transmitting
	 *  the LPI pattern.
	 * TW: minimum समय (us) क्रम which the core रुकोs
	 *  after it has stopped transmitting the LPI pattern.
	 */
	ग_लिखोl(value, ioaddr + GMAC4_LPI_TIMER_CTRL);
पूर्ण

अटल व्योम dwmac4_ग_लिखो_single_vlan(काष्ठा net_device *dev, u16 vid)
अणु
	व्योम __iomem *ioaddr = (व्योम __iomem *)dev->base_addr;
	u32 val;

	val = पढ़ोl(ioaddr + GMAC_VLAN_TAG);
	val &= ~GMAC_VLAN_TAG_VID;
	val |= GMAC_VLAN_TAG_ETV | vid;

	ग_लिखोl(val, ioaddr + GMAC_VLAN_TAG);
पूर्ण

अटल पूर्णांक dwmac4_ग_लिखो_vlan_filter(काष्ठा net_device *dev,
				    काष्ठा mac_device_info *hw,
				    u8 index, u32 data)
अणु
	व्योम __iomem *ioaddr = (व्योम __iomem *)dev->base_addr;
	पूर्णांक i, समयout = 10;
	u32 val;

	अगर (index >= hw->num_vlan)
		वापस -EINVAL;

	ग_लिखोl(data, ioaddr + GMAC_VLAN_TAG_DATA);

	val = पढ़ोl(ioaddr + GMAC_VLAN_TAG);
	val &= ~(GMAC_VLAN_TAG_CTRL_OFS_MASK |
		GMAC_VLAN_TAG_CTRL_CT |
		GMAC_VLAN_TAG_CTRL_OB);
	val |= (index << GMAC_VLAN_TAG_CTRL_OFS_SHIFT) | GMAC_VLAN_TAG_CTRL_OB;

	ग_लिखोl(val, ioaddr + GMAC_VLAN_TAG);

	क्रम (i = 0; i < समयout; i++) अणु
		val = पढ़ोl(ioaddr + GMAC_VLAN_TAG);
		अगर (!(val & GMAC_VLAN_TAG_CTRL_OB))
			वापस 0;
		udelay(1);
	पूर्ण

	netdev_err(dev, "Timeout accessing MAC_VLAN_Tag_Filter\n");

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक dwmac4_add_hw_vlan_rx_fltr(काष्ठा net_device *dev,
				      काष्ठा mac_device_info *hw,
				      __be16 proto, u16 vid)
अणु
	पूर्णांक index = -1;
	u32 val = 0;
	पूर्णांक i, ret;

	अगर (vid > 4095)
		वापस -EINVAL;

	अगर (hw->promisc) अणु
		netdev_err(dev,
			   "Adding VLAN in promisc mode not supported\n");
		वापस -EPERM;
	पूर्ण

	/* Single Rx VLAN Filter */
	अगर (hw->num_vlan == 1) अणु
		/* For single VLAN filter, VID 0 means VLAN promiscuous */
		अगर (vid == 0) अणु
			netdev_warn(dev, "Adding VLAN ID 0 is not supported\n");
			वापस -EPERM;
		पूर्ण

		अगर (hw->vlan_filter[0] & GMAC_VLAN_TAG_VID) अणु
			netdev_err(dev, "Only single VLAN ID supported\n");
			वापस -EPERM;
		पूर्ण

		hw->vlan_filter[0] = vid;
		dwmac4_ग_लिखो_single_vlan(dev, vid);

		वापस 0;
	पूर्ण

	/* Extended Rx VLAN Filter Enable */
	val |= GMAC_VLAN_TAG_DATA_ETV | GMAC_VLAN_TAG_DATA_VEN | vid;

	क्रम (i = 0; i < hw->num_vlan; i++) अणु
		अगर (hw->vlan_filter[i] == val)
			वापस 0;
		अन्यथा अगर (!(hw->vlan_filter[i] & GMAC_VLAN_TAG_DATA_VEN))
			index = i;
	पूर्ण

	अगर (index == -1) अणु
		netdev_err(dev, "MAC_VLAN_Tag_Filter full (size: %0u)\n",
			   hw->num_vlan);
		वापस -EPERM;
	पूर्ण

	ret = dwmac4_ग_लिखो_vlan_filter(dev, hw, index, val);

	अगर (!ret)
		hw->vlan_filter[index] = val;

	वापस ret;
पूर्ण

अटल पूर्णांक dwmac4_del_hw_vlan_rx_fltr(काष्ठा net_device *dev,
				      काष्ठा mac_device_info *hw,
				      __be16 proto, u16 vid)
अणु
	पूर्णांक i, ret = 0;

	अगर (hw->promisc) अणु
		netdev_err(dev,
			   "Deleting VLAN in promisc mode not supported\n");
		वापस -EPERM;
	पूर्ण

	/* Single Rx VLAN Filter */
	अगर (hw->num_vlan == 1) अणु
		अगर ((hw->vlan_filter[0] & GMAC_VLAN_TAG_VID) == vid) अणु
			hw->vlan_filter[0] = 0;
			dwmac4_ग_लिखो_single_vlan(dev, 0);
		पूर्ण
		वापस 0;
	पूर्ण

	/* Extended Rx VLAN Filter Enable */
	क्रम (i = 0; i < hw->num_vlan; i++) अणु
		अगर ((hw->vlan_filter[i] & GMAC_VLAN_TAG_DATA_VID) == vid) अणु
			ret = dwmac4_ग_लिखो_vlan_filter(dev, hw, i, 0);

			अगर (!ret)
				hw->vlan_filter[i] = 0;
			अन्यथा
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dwmac4_vlan_promisc_enable(काष्ठा net_device *dev,
				       काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;
	u32 hash;
	u32 val;
	पूर्णांक i;

	/* Single Rx VLAN Filter */
	अगर (hw->num_vlan == 1) अणु
		dwmac4_ग_लिखो_single_vlan(dev, 0);
		वापस;
	पूर्ण

	/* Extended Rx VLAN Filter Enable */
	क्रम (i = 0; i < hw->num_vlan; i++) अणु
		अगर (hw->vlan_filter[i] & GMAC_VLAN_TAG_DATA_VEN) अणु
			val = hw->vlan_filter[i] & ~GMAC_VLAN_TAG_DATA_VEN;
			dwmac4_ग_लिखो_vlan_filter(dev, hw, i, val);
		पूर्ण
	पूर्ण

	hash = पढ़ोl(ioaddr + GMAC_VLAN_HASH_TABLE);
	अगर (hash & GMAC_VLAN_VLHT) अणु
		value = पढ़ोl(ioaddr + GMAC_VLAN_TAG);
		अगर (value & GMAC_VLAN_VTHM) अणु
			value &= ~GMAC_VLAN_VTHM;
			ग_लिखोl(value, ioaddr + GMAC_VLAN_TAG);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dwmac4_restore_hw_vlan_rx_fltr(काष्ठा net_device *dev,
					   काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;
	u32 hash;
	u32 val;
	पूर्णांक i;

	/* Single Rx VLAN Filter */
	अगर (hw->num_vlan == 1) अणु
		dwmac4_ग_लिखो_single_vlan(dev, hw->vlan_filter[0]);
		वापस;
	पूर्ण

	/* Extended Rx VLAN Filter Enable */
	क्रम (i = 0; i < hw->num_vlan; i++) अणु
		अगर (hw->vlan_filter[i] & GMAC_VLAN_TAG_DATA_VEN) अणु
			val = hw->vlan_filter[i];
			dwmac4_ग_लिखो_vlan_filter(dev, hw, i, val);
		पूर्ण
	पूर्ण

	hash = पढ़ोl(ioaddr + GMAC_VLAN_HASH_TABLE);
	अगर (hash & GMAC_VLAN_VLHT) अणु
		value = पढ़ोl(ioaddr + GMAC_VLAN_TAG);
		value |= GMAC_VLAN_VTHM;
		ग_लिखोl(value, ioaddr + GMAC_VLAN_TAG);
	पूर्ण
पूर्ण

अटल व्योम dwmac4_set_filter(काष्ठा mac_device_info *hw,
			      काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = (व्योम __iomem *)dev->base_addr;
	पूर्णांक numhashregs = (hw->multicast_filter_bins >> 5);
	पूर्णांक mcbitslog2 = hw->mcast_bits_log2;
	अचिन्हित पूर्णांक value;
	u32 mc_filter[8];
	पूर्णांक i;

	स_रखो(mc_filter, 0, माप(mc_filter));

	value = पढ़ोl(ioaddr + GMAC_PACKET_FILTER);
	value &= ~GMAC_PACKET_FILTER_HMC;
	value &= ~GMAC_PACKET_FILTER_HPF;
	value &= ~GMAC_PACKET_FILTER_PCF;
	value &= ~GMAC_PACKET_FILTER_PM;
	value &= ~GMAC_PACKET_FILTER_PR;
	value &= ~GMAC_PACKET_FILTER_RA;
	अगर (dev->flags & IFF_PROMISC) अणु
		/* VLAN Tag Filter Fail Packets Queuing */
		अगर (hw->vlan_fail_q_en) अणु
			value = पढ़ोl(ioaddr + GMAC_RXQ_CTRL4);
			value &= ~GMAC_RXQCTRL_VFFQ_MASK;
			value |= GMAC_RXQCTRL_VFFQE |
				 (hw->vlan_fail_q << GMAC_RXQCTRL_VFFQ_SHIFT);
			ग_लिखोl(value, ioaddr + GMAC_RXQ_CTRL4);
			value = GMAC_PACKET_FILTER_PR | GMAC_PACKET_FILTER_RA;
		पूर्ण अन्यथा अणु
			value = GMAC_PACKET_FILTER_PR | GMAC_PACKET_FILTER_PCF;
		पूर्ण

	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI) ||
		   (netdev_mc_count(dev) > hw->multicast_filter_bins)) अणु
		/* Pass all multi */
		value |= GMAC_PACKET_FILTER_PM;
		/* Set all the bits of the HASH tab */
		स_रखो(mc_filter, 0xff, माप(mc_filter));
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev) && (dev->flags & IFF_MULTICAST)) अणु
		काष्ठा netdev_hw_addr *ha;

		/* Hash filter क्रम multicast */
		value |= GMAC_PACKET_FILTER_HMC;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			/* The upper n bits of the calculated CRC are used to
			 * index the contents of the hash table. The number of
			 * bits used depends on the hardware configuration
			 * selected at core configuration समय.
			 */
			u32 bit_nr = bitrev32(~crc32_le(~0, ha->addr,
					ETH_ALEN)) >> (32 - mcbitslog2);
			/* The most signअगरicant bit determines the रेजिस्टर to
			 * use (H/L) जबतक the other 5 bits determine the bit
			 * within the रेजिस्टर.
			 */
			mc_filter[bit_nr >> 5] |= (1 << (bit_nr & 0x1f));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < numhashregs; i++)
		ग_लिखोl(mc_filter[i], ioaddr + GMAC_HASH_TAB(i));

	value |= GMAC_PACKET_FILTER_HPF;

	/* Handle multiple unicast addresses */
	अगर (netdev_uc_count(dev) > hw->unicast_filter_entries) अणु
		/* Switch to promiscuous mode अगर more than 128 addrs
		 * are required
		 */
		value |= GMAC_PACKET_FILTER_PR;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक reg = 1;

		netdev_क्रम_each_uc_addr(ha, dev) अणु
			dwmac4_set_umac_addr(hw, ha->addr, reg);
			reg++;
		पूर्ण

		जबतक (reg < GMAC_MAX_PERFECT_ADDRESSES) अणु
			ग_लिखोl(0, ioaddr + GMAC_ADDR_HIGH(reg));
			ग_लिखोl(0, ioaddr + GMAC_ADDR_LOW(reg));
			reg++;
		पूर्ण
	पूर्ण

	/* VLAN filtering */
	अगर (dev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
		value |= GMAC_PACKET_FILTER_VTFE;

	ग_लिखोl(value, ioaddr + GMAC_PACKET_FILTER);

	अगर (dev->flags & IFF_PROMISC && !hw->vlan_fail_q_en) अणु
		अगर (!hw->promisc) अणु
			hw->promisc = 1;
			dwmac4_vlan_promisc_enable(dev, hw);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hw->promisc) अणु
			hw->promisc = 0;
			dwmac4_restore_hw_vlan_rx_fltr(dev, hw);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dwmac4_flow_ctrl(काष्ठा mac_device_info *hw, अचिन्हित पूर्णांक duplex,
			     अचिन्हित पूर्णांक fc, अचिन्हित पूर्णांक छोड़ो_समय,
			     u32 tx_cnt)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	अचिन्हित पूर्णांक flow = 0;
	u32 queue = 0;

	pr_debug("GMAC Flow-Control:\n");
	अगर (fc & FLOW_RX) अणु
		pr_debug("\tReceive Flow-Control ON\n");
		flow |= GMAC_RX_FLOW_CTRL_RFE;
	पूर्ण
	ग_लिखोl(flow, ioaddr + GMAC_RX_FLOW_CTRL);

	अगर (fc & FLOW_TX) अणु
		pr_debug("\tTransmit Flow-Control ON\n");

		अगर (duplex)
			pr_debug("\tduplex mode: PAUSE %d\n", छोड़ो_समय);

		क्रम (queue = 0; queue < tx_cnt; queue++) अणु
			flow = GMAC_TX_FLOW_CTRL_TFE;

			अगर (duplex)
				flow |=
				(छोड़ो_समय << GMAC_TX_FLOW_CTRL_PT_SHIFT);

			ग_लिखोl(flow, ioaddr + GMAC_QX_TX_FLOW_CTRL(queue));
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (queue = 0; queue < tx_cnt; queue++)
			ग_लिखोl(0, ioaddr + GMAC_QX_TX_FLOW_CTRL(queue));
	पूर्ण
पूर्ण

अटल व्योम dwmac4_ctrl_ane(व्योम __iomem *ioaddr, bool ane, bool srgmi_ral,
			    bool loopback)
अणु
	dwmac_ctrl_ane(ioaddr, GMAC_PCS_BASE, ane, srgmi_ral, loopback);
पूर्ण

अटल व्योम dwmac4_rane(व्योम __iomem *ioaddr, bool restart)
अणु
	dwmac_rane(ioaddr, GMAC_PCS_BASE, restart);
पूर्ण

अटल व्योम dwmac4_get_adv_lp(व्योम __iomem *ioaddr, काष्ठा rgmii_adv *adv)
अणु
	dwmac_get_adv_lp(ioaddr, GMAC_PCS_BASE, adv);
पूर्ण

/* RGMII or SMII पूर्णांकerface */
अटल व्योम dwmac4_phystatus(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_extra_stats *x)
अणु
	u32 status;

	status = पढ़ोl(ioaddr + GMAC_PHYIF_CONTROL_STATUS);
	x->irq_rgmii_n++;

	/* Check the link status */
	अगर (status & GMAC_PHYIF_CTRLSTATUS_LNKSTS) अणु
		पूर्णांक speed_value;

		x->pcs_link = 1;

		speed_value = ((status & GMAC_PHYIF_CTRLSTATUS_SPEED) >>
			       GMAC_PHYIF_CTRLSTATUS_SPEED_SHIFT);
		अगर (speed_value == GMAC_PHYIF_CTRLSTATUS_SPEED_125)
			x->pcs_speed = SPEED_1000;
		अन्यथा अगर (speed_value == GMAC_PHYIF_CTRLSTATUS_SPEED_25)
			x->pcs_speed = SPEED_100;
		अन्यथा
			x->pcs_speed = SPEED_10;

		x->pcs_duplex = (status & GMAC_PHYIF_CTRLSTATUS_LNKMOD_MASK);

		pr_info("Link is Up - %d/%s\n", (पूर्णांक)x->pcs_speed,
			x->pcs_duplex ? "Full" : "Half");
	पूर्ण अन्यथा अणु
		x->pcs_link = 0;
		pr_info("Link is Down\n");
	पूर्ण
पूर्ण

अटल पूर्णांक dwmac4_irq_mtl_status(काष्ठा mac_device_info *hw, u32 chan)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 mtl_पूर्णांक_qx_status;
	पूर्णांक ret = 0;

	mtl_पूर्णांक_qx_status = पढ़ोl(ioaddr + MTL_INT_STATUS);

	/* Check MTL Interrupt */
	अगर (mtl_पूर्णांक_qx_status & MTL_INT_QX(chan)) अणु
		/* पढ़ो Queue x Interrupt status */
		u32 status = पढ़ोl(ioaddr + MTL_CHAN_INT_CTRL(chan));

		अगर (status & MTL_RX_OVERFLOW_INT) अणु
			/*  clear Interrupt */
			ग_लिखोl(status | MTL_RX_OVERFLOW_INT,
			       ioaddr + MTL_CHAN_INT_CTRL(chan));
			ret = CORE_IRQ_MTL_RX_OVERFLOW;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dwmac4_irq_status(काष्ठा mac_device_info *hw,
			     काष्ठा sपंचांगmac_extra_stats *x)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 पूर्णांकr_status = पढ़ोl(ioaddr + GMAC_INT_STATUS);
	u32 पूर्णांकr_enable = पढ़ोl(ioaddr + GMAC_INT_EN);
	पूर्णांक ret = 0;

	/* Discard disabled bits */
	पूर्णांकr_status &= पूर्णांकr_enable;

	/* Not used events (e.g. MMC पूर्णांकerrupts) are not handled. */
	अगर ((पूर्णांकr_status & mmc_tx_irq))
		x->mmc_tx_irq_n++;
	अगर (unlikely(पूर्णांकr_status & mmc_rx_irq))
		x->mmc_rx_irq_n++;
	अगर (unlikely(पूर्णांकr_status & mmc_rx_csum_offload_irq))
		x->mmc_rx_csum_offload_irq_n++;
	/* Clear the PMT bits 5 and 6 by पढ़ोing the PMT status reg */
	अगर (unlikely(पूर्णांकr_status & pmt_irq)) अणु
		पढ़ोl(ioaddr + GMAC_PMT);
		x->irq_receive_pmt_irq_n++;
	पूर्ण

	/* MAC tx/rx EEE LPI entry/निकास पूर्णांकerrupts */
	अगर (पूर्णांकr_status & lpi_irq) अणु
		/* Clear LPI पूर्णांकerrupt by पढ़ोing MAC_LPI_Control_Status */
		u32 status = पढ़ोl(ioaddr + GMAC4_LPI_CTRL_STATUS);

		अगर (status & GMAC4_LPI_CTRL_STATUS_TLPIEN) अणु
			ret |= CORE_IRQ_TX_PATH_IN_LPI_MODE;
			x->irq_tx_path_in_lpi_mode_n++;
		पूर्ण
		अगर (status & GMAC4_LPI_CTRL_STATUS_TLPIEX) अणु
			ret |= CORE_IRQ_TX_PATH_EXIT_LPI_MODE;
			x->irq_tx_path_निकास_lpi_mode_n++;
		पूर्ण
		अगर (status & GMAC4_LPI_CTRL_STATUS_RLPIEN)
			x->irq_rx_path_in_lpi_mode_n++;
		अगर (status & GMAC4_LPI_CTRL_STATUS_RLPIEX)
			x->irq_rx_path_निकास_lpi_mode_n++;
	पूर्ण

	dwmac_pcs_isr(ioaddr, GMAC_PCS_BASE, पूर्णांकr_status, x);
	अगर (पूर्णांकr_status & PCS_RGSMIIIS_IRQ)
		dwmac4_phystatus(ioaddr, x);

	वापस ret;
पूर्ण

अटल व्योम dwmac4_debug(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_extra_stats *x,
			 u32 rx_queues, u32 tx_queues)
अणु
	u32 value;
	u32 queue;

	क्रम (queue = 0; queue < tx_queues; queue++) अणु
		value = पढ़ोl(ioaddr + MTL_CHAN_TX_DEBUG(queue));

		अगर (value & MTL_DEBUG_TXSTSFSTS)
			x->mtl_tx_status_fअगरo_full++;
		अगर (value & MTL_DEBUG_TXFSTS)
			x->mtl_tx_fअगरo_not_empty++;
		अगर (value & MTL_DEBUG_TWCSTS)
			x->mmtl_fअगरo_ctrl++;
		अगर (value & MTL_DEBUG_TRCSTS_MASK) अणु
			u32 trcsts = (value & MTL_DEBUG_TRCSTS_MASK)
				     >> MTL_DEBUG_TRCSTS_SHIFT;
			अगर (trcsts == MTL_DEBUG_TRCSTS_WRITE)
				x->mtl_tx_fअगरo_पढ़ो_ctrl_ग_लिखो++;
			अन्यथा अगर (trcsts == MTL_DEBUG_TRCSTS_TXW)
				x->mtl_tx_fअगरo_पढ़ो_ctrl_रुको++;
			अन्यथा अगर (trcsts == MTL_DEBUG_TRCSTS_READ)
				x->mtl_tx_fअगरo_पढ़ो_ctrl_पढ़ो++;
			अन्यथा
				x->mtl_tx_fअगरo_पढ़ो_ctrl_idle++;
		पूर्ण
		अगर (value & MTL_DEBUG_TXPAUSED)
			x->mac_tx_in_छोड़ो++;
	पूर्ण

	क्रम (queue = 0; queue < rx_queues; queue++) अणु
		value = पढ़ोl(ioaddr + MTL_CHAN_RX_DEBUG(queue));

		अगर (value & MTL_DEBUG_RXFSTS_MASK) अणु
			u32 rxfsts = (value & MTL_DEBUG_RXFSTS_MASK)
				     >> MTL_DEBUG_RRCSTS_SHIFT;

			अगर (rxfsts == MTL_DEBUG_RXFSTS_FULL)
				x->mtl_rx_fअगरo_fill_level_full++;
			अन्यथा अगर (rxfsts == MTL_DEBUG_RXFSTS_AT)
				x->mtl_rx_fअगरo_fill_above_thresh++;
			अन्यथा अगर (rxfsts == MTL_DEBUG_RXFSTS_BT)
				x->mtl_rx_fअगरo_fill_below_thresh++;
			अन्यथा
				x->mtl_rx_fअगरo_fill_level_empty++;
		पूर्ण
		अगर (value & MTL_DEBUG_RRCSTS_MASK) अणु
			u32 rrcsts = (value & MTL_DEBUG_RRCSTS_MASK) >>
				     MTL_DEBUG_RRCSTS_SHIFT;

			अगर (rrcsts == MTL_DEBUG_RRCSTS_FLUSH)
				x->mtl_rx_fअगरo_पढ़ो_ctrl_flush++;
			अन्यथा अगर (rrcsts == MTL_DEBUG_RRCSTS_RSTAT)
				x->mtl_rx_fअगरo_पढ़ो_ctrl_पढ़ो_data++;
			अन्यथा अगर (rrcsts == MTL_DEBUG_RRCSTS_RDATA)
				x->mtl_rx_fअगरo_पढ़ो_ctrl_status++;
			अन्यथा
				x->mtl_rx_fअगरo_पढ़ो_ctrl_idle++;
		पूर्ण
		अगर (value & MTL_DEBUG_RWCSTS)
			x->mtl_rx_fअगरo_ctrl_active++;
	पूर्ण

	/* GMAC debug */
	value = पढ़ोl(ioaddr + GMAC_DEBUG);

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
	अगर (value & GMAC_DEBUG_RFCFCSTS_MASK)
		x->mac_rx_frame_ctrl_fअगरo = (value & GMAC_DEBUG_RFCFCSTS_MASK)
					    >> GMAC_DEBUG_RFCFCSTS_SHIFT;
	अगर (value & GMAC_DEBUG_RPESTS)
		x->mac_gmii_rx_proto_engine++;
पूर्ण

अटल व्योम dwmac4_set_mac_loopback(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 value = पढ़ोl(ioaddr + GMAC_CONFIG);

	अगर (enable)
		value |= GMAC_CONFIG_LM;
	अन्यथा
		value &= ~GMAC_CONFIG_LM;

	ग_लिखोl(value, ioaddr + GMAC_CONFIG);
पूर्ण

अटल व्योम dwmac4_update_vlan_hash(काष्ठा mac_device_info *hw, u32 hash,
				    __le16 perfect_match, bool is_द्विगुन)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	ग_लिखोl(hash, ioaddr + GMAC_VLAN_HASH_TABLE);

	value = पढ़ोl(ioaddr + GMAC_VLAN_TAG);

	अगर (hash) अणु
		value |= GMAC_VLAN_VTHM | GMAC_VLAN_ETV;
		अगर (is_द्विगुन) अणु
			value |= GMAC_VLAN_EDVLP;
			value |= GMAC_VLAN_ESVL;
			value |= GMAC_VLAN_DOVLTC;
		पूर्ण

		ग_लिखोl(value, ioaddr + GMAC_VLAN_TAG);
	पूर्ण अन्यथा अगर (perfect_match) अणु
		u32 value = GMAC_VLAN_ETV;

		अगर (is_द्विगुन) अणु
			value |= GMAC_VLAN_EDVLP;
			value |= GMAC_VLAN_ESVL;
			value |= GMAC_VLAN_DOVLTC;
		पूर्ण

		ग_लिखोl(value | perfect_match, ioaddr + GMAC_VLAN_TAG);
	पूर्ण अन्यथा अणु
		value &= ~(GMAC_VLAN_VTHM | GMAC_VLAN_ETV);
		value &= ~(GMAC_VLAN_EDVLP | GMAC_VLAN_ESVL);
		value &= ~GMAC_VLAN_DOVLTC;
		value &= ~GMAC_VLAN_VID;

		ग_लिखोl(value, ioaddr + GMAC_VLAN_TAG);
	पूर्ण
पूर्ण

अटल व्योम dwmac4_sarc_configure(व्योम __iomem *ioaddr, पूर्णांक val)
अणु
	u32 value = पढ़ोl(ioaddr + GMAC_CONFIG);

	value &= ~GMAC_CONFIG_SARC;
	value |= val << GMAC_CONFIG_SARC_SHIFT;

	ग_लिखोl(value, ioaddr + GMAC_CONFIG);
पूर्ण

अटल व्योम dwmac4_enable_vlan(काष्ठा mac_device_info *hw, u32 type)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + GMAC_VLAN_INCL);
	value |= GMAC_VLAN_VLTI;
	value |= GMAC_VLAN_CSVL; /* Only use SVLAN */
	value &= ~GMAC_VLAN_VLC;
	value |= (type << GMAC_VLAN_VLC_SHIFT) & GMAC_VLAN_VLC;
	ग_लिखोl(value, ioaddr + GMAC_VLAN_INCL);
पूर्ण

अटल व्योम dwmac4_set_arp_offload(काष्ठा mac_device_info *hw, bool en,
				   u32 addr)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	ग_लिखोl(addr, ioaddr + GMAC_ARP_ADDR);

	value = पढ़ोl(ioaddr + GMAC_CONFIG);
	अगर (en)
		value |= GMAC_CONFIG_ARPEN;
	अन्यथा
		value &= ~GMAC_CONFIG_ARPEN;
	ग_लिखोl(value, ioaddr + GMAC_CONFIG);
पूर्ण

अटल पूर्णांक dwmac4_config_l3_filter(काष्ठा mac_device_info *hw, u32 filter_no,
				   bool en, bool ipv6, bool sa, bool inv,
				   u32 match)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + GMAC_PACKET_FILTER);
	value |= GMAC_PACKET_FILTER_IPFE;
	ग_लिखोl(value, ioaddr + GMAC_PACKET_FILTER);

	value = पढ़ोl(ioaddr + GMAC_L3L4_CTRL(filter_no));

	/* For IPv6 not both SA/DA filters can be active */
	अगर (ipv6) अणु
		value |= GMAC_L3PEN0;
		value &= ~(GMAC_L3SAM0 | GMAC_L3SAIM0);
		value &= ~(GMAC_L3DAM0 | GMAC_L3DAIM0);
		अगर (sa) अणु
			value |= GMAC_L3SAM0;
			अगर (inv)
				value |= GMAC_L3SAIM0;
		पूर्ण अन्यथा अणु
			value |= GMAC_L3DAM0;
			अगर (inv)
				value |= GMAC_L3DAIM0;
		पूर्ण
	पूर्ण अन्यथा अणु
		value &= ~GMAC_L3PEN0;
		अगर (sa) अणु
			value |= GMAC_L3SAM0;
			अगर (inv)
				value |= GMAC_L3SAIM0;
		पूर्ण अन्यथा अणु
			value |= GMAC_L3DAM0;
			अगर (inv)
				value |= GMAC_L3DAIM0;
		पूर्ण
	पूर्ण

	ग_लिखोl(value, ioaddr + GMAC_L3L4_CTRL(filter_no));

	अगर (sa) अणु
		ग_लिखोl(match, ioaddr + GMAC_L3_ADDR0(filter_no));
	पूर्ण अन्यथा अणु
		ग_लिखोl(match, ioaddr + GMAC_L3_ADDR1(filter_no));
	पूर्ण

	अगर (!en)
		ग_लिखोl(0, ioaddr + GMAC_L3L4_CTRL(filter_no));

	वापस 0;
पूर्ण

अटल पूर्णांक dwmac4_config_l4_filter(काष्ठा mac_device_info *hw, u32 filter_no,
				   bool en, bool udp, bool sa, bool inv,
				   u32 match)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + GMAC_PACKET_FILTER);
	value |= GMAC_PACKET_FILTER_IPFE;
	ग_लिखोl(value, ioaddr + GMAC_PACKET_FILTER);

	value = पढ़ोl(ioaddr + GMAC_L3L4_CTRL(filter_no));
	अगर (udp) अणु
		value |= GMAC_L4PEN0;
	पूर्ण अन्यथा अणु
		value &= ~GMAC_L4PEN0;
	पूर्ण

	value &= ~(GMAC_L4SPM0 | GMAC_L4SPIM0);
	value &= ~(GMAC_L4DPM0 | GMAC_L4DPIM0);
	अगर (sa) अणु
		value |= GMAC_L4SPM0;
		अगर (inv)
			value |= GMAC_L4SPIM0;
	पूर्ण अन्यथा अणु
		value |= GMAC_L4DPM0;
		अगर (inv)
			value |= GMAC_L4DPIM0;
	पूर्ण

	ग_लिखोl(value, ioaddr + GMAC_L3L4_CTRL(filter_no));

	अगर (sa) अणु
		value = match & GMAC_L4SP0;
	पूर्ण अन्यथा अणु
		value = (match << GMAC_L4DP0_SHIFT) & GMAC_L4DP0;
	पूर्ण

	ग_लिखोl(value, ioaddr + GMAC_L4_ADDR(filter_no));

	अगर (!en)
		ग_लिखोl(0, ioaddr + GMAC_L3L4_CTRL(filter_no));

	वापस 0;
पूर्ण

स्थिर काष्ठा sपंचांगmac_ops dwmac4_ops = अणु
	.core_init = dwmac4_core_init,
	.set_mac = sपंचांगmac_set_mac,
	.rx_ipc = dwmac4_rx_ipc_enable,
	.rx_queue_enable = dwmac4_rx_queue_enable,
	.rx_queue_prio = dwmac4_rx_queue_priority,
	.tx_queue_prio = dwmac4_tx_queue_priority,
	.rx_queue_routing = dwmac4_rx_queue_routing,
	.prog_mtl_rx_algorithms = dwmac4_prog_mtl_rx_algorithms,
	.prog_mtl_tx_algorithms = dwmac4_prog_mtl_tx_algorithms,
	.set_mtl_tx_queue_weight = dwmac4_set_mtl_tx_queue_weight,
	.map_mtl_to_dma = dwmac4_map_mtl_dma,
	.config_cbs = dwmac4_config_cbs,
	.dump_regs = dwmac4_dump_regs,
	.host_irq_status = dwmac4_irq_status,
	.host_mtl_irq_status = dwmac4_irq_mtl_status,
	.flow_ctrl = dwmac4_flow_ctrl,
	.pmt = dwmac4_pmt,
	.set_umac_addr = dwmac4_set_umac_addr,
	.get_umac_addr = dwmac4_get_umac_addr,
	.set_eee_mode = dwmac4_set_eee_mode,
	.reset_eee_mode = dwmac4_reset_eee_mode,
	.set_eee_lpi_entry_समयr = dwmac4_set_eee_lpi_entry_समयr,
	.set_eee_समयr = dwmac4_set_eee_समयr,
	.set_eee_pls = dwmac4_set_eee_pls,
	.pcs_ctrl_ane = dwmac4_ctrl_ane,
	.pcs_rane = dwmac4_rane,
	.pcs_get_adv_lp = dwmac4_get_adv_lp,
	.debug = dwmac4_debug,
	.set_filter = dwmac4_set_filter,
	.set_mac_loopback = dwmac4_set_mac_loopback,
	.update_vlan_hash = dwmac4_update_vlan_hash,
	.sarc_configure = dwmac4_sarc_configure,
	.enable_vlan = dwmac4_enable_vlan,
	.set_arp_offload = dwmac4_set_arp_offload,
	.config_l3_filter = dwmac4_config_l3_filter,
	.config_l4_filter = dwmac4_config_l4_filter,
	.add_hw_vlan_rx_fltr = dwmac4_add_hw_vlan_rx_fltr,
	.del_hw_vlan_rx_fltr = dwmac4_del_hw_vlan_rx_fltr,
	.restore_hw_vlan_rx_fltr = dwmac4_restore_hw_vlan_rx_fltr,
पूर्ण;

स्थिर काष्ठा sपंचांगmac_ops dwmac410_ops = अणु
	.core_init = dwmac4_core_init,
	.set_mac = sपंचांगmac_dwmac4_set_mac,
	.rx_ipc = dwmac4_rx_ipc_enable,
	.rx_queue_enable = dwmac4_rx_queue_enable,
	.rx_queue_prio = dwmac4_rx_queue_priority,
	.tx_queue_prio = dwmac4_tx_queue_priority,
	.rx_queue_routing = dwmac4_rx_queue_routing,
	.prog_mtl_rx_algorithms = dwmac4_prog_mtl_rx_algorithms,
	.prog_mtl_tx_algorithms = dwmac4_prog_mtl_tx_algorithms,
	.set_mtl_tx_queue_weight = dwmac4_set_mtl_tx_queue_weight,
	.map_mtl_to_dma = dwmac4_map_mtl_dma,
	.config_cbs = dwmac4_config_cbs,
	.dump_regs = dwmac4_dump_regs,
	.host_irq_status = dwmac4_irq_status,
	.host_mtl_irq_status = dwmac4_irq_mtl_status,
	.flow_ctrl = dwmac4_flow_ctrl,
	.pmt = dwmac4_pmt,
	.set_umac_addr = dwmac4_set_umac_addr,
	.get_umac_addr = dwmac4_get_umac_addr,
	.set_eee_mode = dwmac4_set_eee_mode,
	.reset_eee_mode = dwmac4_reset_eee_mode,
	.set_eee_lpi_entry_समयr = dwmac4_set_eee_lpi_entry_समयr,
	.set_eee_समयr = dwmac4_set_eee_समयr,
	.set_eee_pls = dwmac4_set_eee_pls,
	.pcs_ctrl_ane = dwmac4_ctrl_ane,
	.pcs_rane = dwmac4_rane,
	.pcs_get_adv_lp = dwmac4_get_adv_lp,
	.debug = dwmac4_debug,
	.set_filter = dwmac4_set_filter,
	.flex_pps_config = dwmac5_flex_pps_config,
	.set_mac_loopback = dwmac4_set_mac_loopback,
	.update_vlan_hash = dwmac4_update_vlan_hash,
	.sarc_configure = dwmac4_sarc_configure,
	.enable_vlan = dwmac4_enable_vlan,
	.set_arp_offload = dwmac4_set_arp_offload,
	.config_l3_filter = dwmac4_config_l3_filter,
	.config_l4_filter = dwmac4_config_l4_filter,
	.est_configure = dwmac5_est_configure,
	.fpe_configure = dwmac5_fpe_configure,
	.fpe_send_mpacket = dwmac5_fpe_send_mpacket,
	.fpe_irq_status = dwmac5_fpe_irq_status,
	.add_hw_vlan_rx_fltr = dwmac4_add_hw_vlan_rx_fltr,
	.del_hw_vlan_rx_fltr = dwmac4_del_hw_vlan_rx_fltr,
	.restore_hw_vlan_rx_fltr = dwmac4_restore_hw_vlan_rx_fltr,
पूर्ण;

स्थिर काष्ठा sपंचांगmac_ops dwmac510_ops = अणु
	.core_init = dwmac4_core_init,
	.set_mac = sपंचांगmac_dwmac4_set_mac,
	.rx_ipc = dwmac4_rx_ipc_enable,
	.rx_queue_enable = dwmac4_rx_queue_enable,
	.rx_queue_prio = dwmac4_rx_queue_priority,
	.tx_queue_prio = dwmac4_tx_queue_priority,
	.rx_queue_routing = dwmac4_rx_queue_routing,
	.prog_mtl_rx_algorithms = dwmac4_prog_mtl_rx_algorithms,
	.prog_mtl_tx_algorithms = dwmac4_prog_mtl_tx_algorithms,
	.set_mtl_tx_queue_weight = dwmac4_set_mtl_tx_queue_weight,
	.map_mtl_to_dma = dwmac4_map_mtl_dma,
	.config_cbs = dwmac4_config_cbs,
	.dump_regs = dwmac4_dump_regs,
	.host_irq_status = dwmac4_irq_status,
	.host_mtl_irq_status = dwmac4_irq_mtl_status,
	.flow_ctrl = dwmac4_flow_ctrl,
	.pmt = dwmac4_pmt,
	.set_umac_addr = dwmac4_set_umac_addr,
	.get_umac_addr = dwmac4_get_umac_addr,
	.set_eee_mode = dwmac4_set_eee_mode,
	.reset_eee_mode = dwmac4_reset_eee_mode,
	.set_eee_lpi_entry_समयr = dwmac4_set_eee_lpi_entry_समयr,
	.set_eee_समयr = dwmac4_set_eee_समयr,
	.set_eee_pls = dwmac4_set_eee_pls,
	.pcs_ctrl_ane = dwmac4_ctrl_ane,
	.pcs_rane = dwmac4_rane,
	.pcs_get_adv_lp = dwmac4_get_adv_lp,
	.debug = dwmac4_debug,
	.set_filter = dwmac4_set_filter,
	.safety_feat_config = dwmac5_safety_feat_config,
	.safety_feat_irq_status = dwmac5_safety_feat_irq_status,
	.safety_feat_dump = dwmac5_safety_feat_dump,
	.rxp_config = dwmac5_rxp_config,
	.flex_pps_config = dwmac5_flex_pps_config,
	.set_mac_loopback = dwmac4_set_mac_loopback,
	.update_vlan_hash = dwmac4_update_vlan_hash,
	.sarc_configure = dwmac4_sarc_configure,
	.enable_vlan = dwmac4_enable_vlan,
	.set_arp_offload = dwmac4_set_arp_offload,
	.config_l3_filter = dwmac4_config_l3_filter,
	.config_l4_filter = dwmac4_config_l4_filter,
	.est_configure = dwmac5_est_configure,
	.fpe_configure = dwmac5_fpe_configure,
	.fpe_send_mpacket = dwmac5_fpe_send_mpacket,
	.fpe_irq_status = dwmac5_fpe_irq_status,
	.add_hw_vlan_rx_fltr = dwmac4_add_hw_vlan_rx_fltr,
	.del_hw_vlan_rx_fltr = dwmac4_del_hw_vlan_rx_fltr,
	.restore_hw_vlan_rx_fltr = dwmac4_restore_hw_vlan_rx_fltr,
पूर्ण;

अटल u32 dwmac4_get_num_vlan(व्योम __iomem *ioaddr)
अणु
	u32 val, num_vlan;

	val = पढ़ोl(ioaddr + GMAC_HW_FEATURE3);
	चयन (val & GMAC_HW_FEAT_NRVF) अणु
	हाल 0:
		num_vlan = 1;
		अवरोध;
	हाल 1:
		num_vlan = 4;
		अवरोध;
	हाल 2:
		num_vlan = 8;
		अवरोध;
	हाल 3:
		num_vlan = 16;
		अवरोध;
	हाल 4:
		num_vlan = 24;
		अवरोध;
	हाल 5:
		num_vlan = 32;
		अवरोध;
	शेष:
		num_vlan = 1;
	पूर्ण

	वापस num_vlan;
पूर्ण

पूर्णांक dwmac4_setup(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा mac_device_info *mac = priv->hw;

	dev_info(priv->device, "\tDWMAC4/5\n");

	priv->dev->priv_flags |= IFF_UNICAST_FLT;
	mac->pcsr = priv->ioaddr;
	mac->multicast_filter_bins = priv->plat->multicast_filter_bins;
	mac->unicast_filter_entries = priv->plat->unicast_filter_entries;
	mac->mcast_bits_log2 = 0;

	अगर (mac->multicast_filter_bins)
		mac->mcast_bits_log2 = ilog2(mac->multicast_filter_bins);

	mac->link.duplex = GMAC_CONFIG_DM;
	mac->link.speed10 = GMAC_CONFIG_PS;
	mac->link.speed100 = GMAC_CONFIG_FES | GMAC_CONFIG_PS;
	mac->link.speed1000 = 0;
	mac->link.speed_mask = GMAC_CONFIG_FES | GMAC_CONFIG_PS;
	mac->mii.addr = GMAC_MDIO_ADDR;
	mac->mii.data = GMAC_MDIO_DATA;
	mac->mii.addr_shअगरt = 21;
	mac->mii.addr_mask = GENMASK(25, 21);
	mac->mii.reg_shअगरt = 16;
	mac->mii.reg_mask = GENMASK(20, 16);
	mac->mii.clk_csr_shअगरt = 8;
	mac->mii.clk_csr_mask = GENMASK(11, 8);
	mac->num_vlan = dwmac4_get_num_vlan(priv->ioaddr);

	वापस 0;
पूर्ण
