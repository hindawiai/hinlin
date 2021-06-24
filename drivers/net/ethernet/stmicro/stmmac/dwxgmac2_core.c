<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.
 * sपंचांगmac XGMAC support.
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/crc32.h>
#समावेश <linux/iopoll.h>
#समावेश "stmmac.h"
#समावेश "stmmac_ptp.h"
#समावेश "dwxlgmac2.h"
#समावेश "dwxgmac2.h"

अटल व्योम dwxgmac2_core_init(काष्ठा mac_device_info *hw,
			       काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 tx, rx;

	tx = पढ़ोl(ioaddr + XGMAC_TX_CONFIG);
	rx = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);

	tx |= XGMAC_CORE_INIT_TX;
	rx |= XGMAC_CORE_INIT_RX;

	अगर (hw->ps) अणु
		tx |= XGMAC_CONFIG_TE;
		tx &= ~hw->link.speed_mask;

		चयन (hw->ps) अणु
		हाल SPEED_10000:
			tx |= hw->link.xgmii.speed10000;
			अवरोध;
		हाल SPEED_2500:
			tx |= hw->link.speed2500;
			अवरोध;
		हाल SPEED_1000:
		शेष:
			tx |= hw->link.speed1000;
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोl(tx, ioaddr + XGMAC_TX_CONFIG);
	ग_लिखोl(rx, ioaddr + XGMAC_RX_CONFIG);
	ग_लिखोl(XGMAC_INT_DEFAULT_EN, ioaddr + XGMAC_INT_EN);
पूर्ण

अटल व्योम dwxgmac2_set_mac(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 tx = पढ़ोl(ioaddr + XGMAC_TX_CONFIG);
	u32 rx = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);

	अगर (enable) अणु
		tx |= XGMAC_CONFIG_TE;
		rx |= XGMAC_CONFIG_RE;
	पूर्ण अन्यथा अणु
		tx &= ~XGMAC_CONFIG_TE;
		rx &= ~XGMAC_CONFIG_RE;
	पूर्ण

	ग_लिखोl(tx, ioaddr + XGMAC_TX_CONFIG);
	ग_लिखोl(rx, ioaddr + XGMAC_RX_CONFIG);
पूर्ण

अटल पूर्णांक dwxgmac2_rx_ipc(काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);
	अगर (hw->rx_csum)
		value |= XGMAC_CONFIG_IPC;
	अन्यथा
		value &= ~XGMAC_CONFIG_IPC;
	ग_लिखोl(value, ioaddr + XGMAC_RX_CONFIG);

	वापस !!(पढ़ोl(ioaddr + XGMAC_RX_CONFIG) & XGMAC_CONFIG_IPC);
पूर्ण

अटल व्योम dwxgmac2_rx_queue_enable(काष्ठा mac_device_info *hw, u8 mode,
				     u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_RXQ_CTRL0) & ~XGMAC_RXQEN(queue);
	अगर (mode == MTL_QUEUE_AVB)
		value |= 0x1 << XGMAC_RXQEN_SHIFT(queue);
	अन्यथा अगर (mode == MTL_QUEUE_DCB)
		value |= 0x2 << XGMAC_RXQEN_SHIFT(queue);
	ग_लिखोl(value, ioaddr + XGMAC_RXQ_CTRL0);
पूर्ण

अटल व्योम dwxgmac2_rx_queue_prio(काष्ठा mac_device_info *hw, u32 prio,
				   u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value, reg;

	reg = (queue < 4) ? XGMAC_RXQ_CTRL2 : XGMAC_RXQ_CTRL3;
	अगर (queue >= 4)
		queue -= 4;

	value = पढ़ोl(ioaddr + reg);
	value &= ~XGMAC_PSRQ(queue);
	value |= (prio << XGMAC_PSRQ_SHIFT(queue)) & XGMAC_PSRQ(queue);

	ग_लिखोl(value, ioaddr + reg);
पूर्ण

अटल व्योम dwxgmac2_tx_queue_prio(काष्ठा mac_device_info *hw, u32 prio,
				   u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value, reg;

	reg = (queue < 4) ? XGMAC_TC_PRTY_MAP0 : XGMAC_TC_PRTY_MAP1;
	अगर (queue >= 4)
		queue -= 4;

	value = पढ़ोl(ioaddr + reg);
	value &= ~XGMAC_PSTC(queue);
	value |= (prio << XGMAC_PSTC_SHIFT(queue)) & XGMAC_PSTC(queue);

	ग_लिखोl(value, ioaddr + reg);
पूर्ण

अटल व्योम dwxgmac2_prog_mtl_rx_algorithms(काष्ठा mac_device_info *hw,
					    u32 rx_alg)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_MTL_OPMODE);
	value &= ~XGMAC_RAA;

	चयन (rx_alg) अणु
	हाल MTL_RX_ALGORITHM_SP:
		अवरोध;
	हाल MTL_RX_ALGORITHM_WSP:
		value |= XGMAC_RAA;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(value, ioaddr + XGMAC_MTL_OPMODE);
पूर्ण

अटल व्योम dwxgmac2_prog_mtl_tx_algorithms(काष्ठा mac_device_info *hw,
					    u32 tx_alg)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	bool ets = true;
	u32 value;
	पूर्णांक i;

	value = पढ़ोl(ioaddr + XGMAC_MTL_OPMODE);
	value &= ~XGMAC_ETSALG;

	चयन (tx_alg) अणु
	हाल MTL_TX_ALGORITHM_WRR:
		value |= XGMAC_WRR;
		अवरोध;
	हाल MTL_TX_ALGORITHM_WFQ:
		value |= XGMAC_WFQ;
		अवरोध;
	हाल MTL_TX_ALGORITHM_DWRR:
		value |= XGMAC_DWRR;
		अवरोध;
	शेष:
		ets = false;
		अवरोध;
	पूर्ण

	ग_लिखोl(value, ioaddr + XGMAC_MTL_OPMODE);

	/* Set ETS अगर desired */
	क्रम (i = 0; i < MTL_MAX_TX_QUEUES; i++) अणु
		value = पढ़ोl(ioaddr + XGMAC_MTL_TCx_ETS_CONTROL(i));
		value &= ~XGMAC_TSA;
		अगर (ets)
			value |= XGMAC_ETS;
		ग_लिखोl(value, ioaddr + XGMAC_MTL_TCx_ETS_CONTROL(i));
	पूर्ण
पूर्ण

अटल व्योम dwxgmac2_set_mtl_tx_queue_weight(काष्ठा mac_device_info *hw,
					     u32 weight, u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;

	ग_लिखोl(weight, ioaddr + XGMAC_MTL_TCx_QUANTUM_WEIGHT(queue));
पूर्ण

अटल व्योम dwxgmac2_map_mtl_to_dma(काष्ठा mac_device_info *hw, u32 queue,
				    u32 chan)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value, reg;

	reg = (queue < 4) ? XGMAC_MTL_RXQ_DMA_MAP0 : XGMAC_MTL_RXQ_DMA_MAP1;
	अगर (queue >= 4)
		queue -= 4;

	value = पढ़ोl(ioaddr + reg);
	value &= ~XGMAC_QxMDMACH(queue);
	value |= (chan << XGMAC_QxMDMACH_SHIFT(queue)) & XGMAC_QxMDMACH(queue);

	ग_लिखोl(value, ioaddr + reg);
पूर्ण

अटल व्योम dwxgmac2_config_cbs(काष्ठा mac_device_info *hw,
				u32 send_slope, u32 idle_slope,
				u32 high_credit, u32 low_credit, u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	ग_लिखोl(send_slope, ioaddr + XGMAC_MTL_TCx_SENDSLOPE(queue));
	ग_लिखोl(idle_slope, ioaddr + XGMAC_MTL_TCx_QUANTUM_WEIGHT(queue));
	ग_लिखोl(high_credit, ioaddr + XGMAC_MTL_TCx_HICREDIT(queue));
	ग_लिखोl(low_credit, ioaddr + XGMAC_MTL_TCx_LOCREDIT(queue));

	value = पढ़ोl(ioaddr + XGMAC_MTL_TCx_ETS_CONTROL(queue));
	value &= ~XGMAC_TSA;
	value |= XGMAC_CC | XGMAC_CBS;
	ग_लिखोl(value, ioaddr + XGMAC_MTL_TCx_ETS_CONTROL(queue));
पूर्ण

अटल व्योम dwxgmac2_dump_regs(काष्ठा mac_device_info *hw, u32 *reg_space)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	पूर्णांक i;

	क्रम (i = 0; i < XGMAC_MAC_REGSIZE; i++)
		reg_space[i] = पढ़ोl(ioaddr + i * 4);
पूर्ण

अटल पूर्णांक dwxgmac2_host_irq_status(काष्ठा mac_device_info *hw,
				    काष्ठा sपंचांगmac_extra_stats *x)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 stat, en;
	पूर्णांक ret = 0;

	en = पढ़ोl(ioaddr + XGMAC_INT_EN);
	stat = पढ़ोl(ioaddr + XGMAC_INT_STATUS);

	stat &= en;

	अगर (stat & XGMAC_PMTIS) अणु
		x->irq_receive_pmt_irq_n++;
		पढ़ोl(ioaddr + XGMAC_PMT);
	पूर्ण

	अगर (stat & XGMAC_LPIIS) अणु
		u32 lpi = पढ़ोl(ioaddr + XGMAC_LPI_CTRL);

		अगर (lpi & XGMAC_TLPIEN) अणु
			ret |= CORE_IRQ_TX_PATH_IN_LPI_MODE;
			x->irq_tx_path_in_lpi_mode_n++;
		पूर्ण
		अगर (lpi & XGMAC_TLPIEX) अणु
			ret |= CORE_IRQ_TX_PATH_EXIT_LPI_MODE;
			x->irq_tx_path_निकास_lpi_mode_n++;
		पूर्ण
		अगर (lpi & XGMAC_RLPIEN)
			x->irq_rx_path_in_lpi_mode_n++;
		अगर (lpi & XGMAC_RLPIEX)
			x->irq_rx_path_निकास_lpi_mode_n++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dwxgmac2_host_mtl_irq_status(काष्ठा mac_device_info *hw, u32 chan)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	पूर्णांक ret = 0;
	u32 status;

	status = पढ़ोl(ioaddr + XGMAC_MTL_INT_STATUS);
	अगर (status & BIT(chan)) अणु
		u32 chan_status = पढ़ोl(ioaddr + XGMAC_MTL_QINT_STATUS(chan));

		अगर (chan_status & XGMAC_RXOVFIS)
			ret |= CORE_IRQ_MTL_RX_OVERFLOW;

		ग_लिखोl(~0x0, ioaddr + XGMAC_MTL_QINT_STATUS(chan));
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dwxgmac2_flow_ctrl(काष्ठा mac_device_info *hw, अचिन्हित पूर्णांक duplex,
			       अचिन्हित पूर्णांक fc, अचिन्हित पूर्णांक छोड़ो_समय,
			       u32 tx_cnt)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 i;

	अगर (fc & FLOW_RX)
		ग_लिखोl(XGMAC_RFE, ioaddr + XGMAC_RX_FLOW_CTRL);
	अगर (fc & FLOW_TX) अणु
		क्रम (i = 0; i < tx_cnt; i++) अणु
			u32 value = XGMAC_TFE;

			अगर (duplex)
				value |= छोड़ो_समय << XGMAC_PT_SHIFT;

			ग_लिखोl(value, ioaddr + XGMAC_Qx_TX_FLOW_CTRL(i));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dwxgmac2_pmt(काष्ठा mac_device_info *hw, अचिन्हित दीर्घ mode)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 val = 0x0;

	अगर (mode & WAKE_MAGIC)
		val |= XGMAC_PWRDWN | XGMAC_MGKPKTEN;
	अगर (mode & WAKE_UCAST)
		val |= XGMAC_PWRDWN | XGMAC_GLBLUCAST | XGMAC_RWKPKTEN;
	अगर (val) अणु
		u32 cfg = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);
		cfg |= XGMAC_CONFIG_RE;
		ग_लिखोl(cfg, ioaddr + XGMAC_RX_CONFIG);
	पूर्ण

	ग_लिखोl(val, ioaddr + XGMAC_PMT);
पूर्ण

अटल व्योम dwxgmac2_set_umac_addr(काष्ठा mac_device_info *hw,
				   अचिन्हित अक्षर *addr, अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = (addr[5] << 8) | addr[4];
	ग_लिखोl(value | XGMAC_AE, ioaddr + XGMAC_ADDRx_HIGH(reg_n));

	value = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	ग_लिखोl(value, ioaddr + XGMAC_ADDRx_LOW(reg_n));
पूर्ण

अटल व्योम dwxgmac2_get_umac_addr(काष्ठा mac_device_info *hw,
				   अचिन्हित अक्षर *addr, अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 hi_addr, lo_addr;

	/* Read the MAC address from the hardware */
	hi_addr = पढ़ोl(ioaddr + XGMAC_ADDRx_HIGH(reg_n));
	lo_addr = पढ़ोl(ioaddr + XGMAC_ADDRx_LOW(reg_n));

	/* Extract the MAC address from the high and low words */
	addr[0] = lo_addr & 0xff;
	addr[1] = (lo_addr >> 8) & 0xff;
	addr[2] = (lo_addr >> 16) & 0xff;
	addr[3] = (lo_addr >> 24) & 0xff;
	addr[4] = hi_addr & 0xff;
	addr[5] = (hi_addr >> 8) & 0xff;
पूर्ण

अटल व्योम dwxgmac2_set_eee_mode(काष्ठा mac_device_info *hw,
				  bool en_tx_lpi_घड़ीgating)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_LPI_CTRL);

	value |= XGMAC_LPITXEN | XGMAC_LPITXA;
	अगर (en_tx_lpi_घड़ीgating)
		value |= XGMAC_TXCGE;

	ग_लिखोl(value, ioaddr + XGMAC_LPI_CTRL);
पूर्ण

अटल व्योम dwxgmac2_reset_eee_mode(काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_LPI_CTRL);
	value &= ~(XGMAC_LPITXEN | XGMAC_LPITXA | XGMAC_TXCGE);
	ग_लिखोl(value, ioaddr + XGMAC_LPI_CTRL);
पूर्ण

अटल व्योम dwxgmac2_set_eee_pls(काष्ठा mac_device_info *hw, पूर्णांक link)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_LPI_CTRL);
	अगर (link)
		value |= XGMAC_PLS;
	अन्यथा
		value &= ~XGMAC_PLS;
	ग_लिखोl(value, ioaddr + XGMAC_LPI_CTRL);
पूर्ण

अटल व्योम dwxgmac2_set_eee_समयr(काष्ठा mac_device_info *hw, पूर्णांक ls, पूर्णांक tw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = (tw & 0xffff) | ((ls & 0x3ff) << 16);
	ग_लिखोl(value, ioaddr + XGMAC_LPI_TIMER_CTRL);
पूर्ण

अटल व्योम dwxgmac2_set_mchash(व्योम __iomem *ioaddr, u32 *mcfilterbits,
				पूर्णांक mcbitslog2)
अणु
	पूर्णांक numhashregs, regs;

	चयन (mcbitslog2) अणु
	हाल 6:
		numhashregs = 2;
		अवरोध;
	हाल 7:
		numhashregs = 4;
		अवरोध;
	हाल 8:
		numhashregs = 8;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (regs = 0; regs < numhashregs; regs++)
		ग_लिखोl(mcfilterbits[regs], ioaddr + XGMAC_HASH_TABLE(regs));
पूर्ण

अटल व्योम dwxgmac2_set_filter(काष्ठा mac_device_info *hw,
				काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = (व्योम __iomem *)dev->base_addr;
	u32 value = पढ़ोl(ioaddr + XGMAC_PACKET_FILTER);
	पूर्णांक mcbitslog2 = hw->mcast_bits_log2;
	u32 mc_filter[8];
	पूर्णांक i;

	value &= ~(XGMAC_FILTER_PR | XGMAC_FILTER_HMC | XGMAC_FILTER_PM);
	value |= XGMAC_FILTER_HPF;

	स_रखो(mc_filter, 0, माप(mc_filter));

	अगर (dev->flags & IFF_PROMISC) अणु
		value |= XGMAC_FILTER_PR;
		value |= XGMAC_FILTER_PCF;
	पूर्ण अन्यथा अगर ((dev->flags & IFF_ALLMULTI) ||
		   (netdev_mc_count(dev) > hw->multicast_filter_bins)) अणु
		value |= XGMAC_FILTER_PM;

		क्रम (i = 0; i < XGMAC_MAX_HASH_TABLE; i++)
			ग_लिखोl(~0x0, ioaddr + XGMAC_HASH_TABLE(i));
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev) && (dev->flags & IFF_MULTICAST)) अणु
		काष्ठा netdev_hw_addr *ha;

		value |= XGMAC_FILTER_HMC;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u32 nr = (bitrev32(~crc32_le(~0, ha->addr, 6)) >>
					(32 - mcbitslog2));
			mc_filter[nr >> 5] |= (1 << (nr & 0x1F));
		पूर्ण
	पूर्ण

	dwxgmac2_set_mchash(ioaddr, mc_filter, mcbitslog2);

	/* Handle multiple unicast addresses */
	अगर (netdev_uc_count(dev) > hw->unicast_filter_entries) अणु
		value |= XGMAC_FILTER_PR;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक reg = 1;

		netdev_क्रम_each_uc_addr(ha, dev) अणु
			dwxgmac2_set_umac_addr(hw, ha->addr, reg);
			reg++;
		पूर्ण

		क्रम ( ; reg < XGMAC_ADDR_MAX; reg++) अणु
			ग_लिखोl(0, ioaddr + XGMAC_ADDRx_HIGH(reg));
			ग_लिखोl(0, ioaddr + XGMAC_ADDRx_LOW(reg));
		पूर्ण
	पूर्ण

	ग_लिखोl(value, ioaddr + XGMAC_PACKET_FILTER);
पूर्ण

अटल व्योम dwxgmac2_set_mac_loopback(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);

	अगर (enable)
		value |= XGMAC_CONFIG_LM;
	अन्यथा
		value &= ~XGMAC_CONFIG_LM;

	ग_लिखोl(value, ioaddr + XGMAC_RX_CONFIG);
पूर्ण

अटल पूर्णांक dwxgmac2_rss_ग_लिखो_reg(व्योम __iomem *ioaddr, bool is_key, पूर्णांक idx,
				  u32 val)
अणु
	u32 ctrl = 0;

	ग_लिखोl(val, ioaddr + XGMAC_RSS_DATA);
	ctrl |= idx << XGMAC_RSSIA_SHIFT;
	ctrl |= is_key ? XGMAC_ADDRT : 0x0;
	ctrl |= XGMAC_OB;
	ग_लिखोl(ctrl, ioaddr + XGMAC_RSS_ADDR);

	वापस पढ़ोl_poll_समयout(ioaddr + XGMAC_RSS_ADDR, ctrl,
				  !(ctrl & XGMAC_OB), 100, 10000);
पूर्ण

अटल पूर्णांक dwxgmac2_rss_configure(काष्ठा mac_device_info *hw,
				  काष्ठा sपंचांगmac_rss *cfg, u32 num_rxq)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value, *key;
	पूर्णांक i, ret;

	value = पढ़ोl(ioaddr + XGMAC_RSS_CTRL);
	अगर (!cfg || !cfg->enable) अणु
		value &= ~XGMAC_RSSE;
		ग_लिखोl(value, ioaddr + XGMAC_RSS_CTRL);
		वापस 0;
	पूर्ण

	key = (u32 *)cfg->key;
	क्रम (i = 0; i < (ARRAY_SIZE(cfg->key) / माप(u32)); i++) अणु
		ret = dwxgmac2_rss_ग_लिखो_reg(ioaddr, true, i, key[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cfg->table); i++) अणु
		ret = dwxgmac2_rss_ग_लिखो_reg(ioaddr, false, i, cfg->table[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < num_rxq; i++)
		dwxgmac2_map_mtl_to_dma(hw, i, XGMAC_QDDMACH);

	value |= XGMAC_UDP4TE | XGMAC_TCP4TE | XGMAC_IP2TE | XGMAC_RSSE;
	ग_लिखोl(value, ioaddr + XGMAC_RSS_CTRL);
	वापस 0;
पूर्ण

अटल व्योम dwxgmac2_update_vlan_hash(काष्ठा mac_device_info *hw, u32 hash,
				      __le16 perfect_match, bool is_द्विगुन)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;

	ग_लिखोl(hash, ioaddr + XGMAC_VLAN_HASH_TABLE);

	अगर (hash) अणु
		u32 value = पढ़ोl(ioaddr + XGMAC_PACKET_FILTER);

		value |= XGMAC_FILTER_VTFE;

		ग_लिखोl(value, ioaddr + XGMAC_PACKET_FILTER);

		value = पढ़ोl(ioaddr + XGMAC_VLAN_TAG);

		value |= XGMAC_VLAN_VTHM | XGMAC_VLAN_ETV;
		अगर (is_द्विगुन) अणु
			value |= XGMAC_VLAN_EDVLP;
			value |= XGMAC_VLAN_ESVL;
			value |= XGMAC_VLAN_DOVLTC;
		पूर्ण अन्यथा अणु
			value &= ~XGMAC_VLAN_EDVLP;
			value &= ~XGMAC_VLAN_ESVL;
			value &= ~XGMAC_VLAN_DOVLTC;
		पूर्ण

		value &= ~XGMAC_VLAN_VID;
		ग_लिखोl(value, ioaddr + XGMAC_VLAN_TAG);
	पूर्ण अन्यथा अगर (perfect_match) अणु
		u32 value = पढ़ोl(ioaddr + XGMAC_PACKET_FILTER);

		value |= XGMAC_FILTER_VTFE;

		ग_लिखोl(value, ioaddr + XGMAC_PACKET_FILTER);

		value = पढ़ोl(ioaddr + XGMAC_VLAN_TAG);

		value &= ~XGMAC_VLAN_VTHM;
		value |= XGMAC_VLAN_ETV;
		अगर (is_द्विगुन) अणु
			value |= XGMAC_VLAN_EDVLP;
			value |= XGMAC_VLAN_ESVL;
			value |= XGMAC_VLAN_DOVLTC;
		पूर्ण अन्यथा अणु
			value &= ~XGMAC_VLAN_EDVLP;
			value &= ~XGMAC_VLAN_ESVL;
			value &= ~XGMAC_VLAN_DOVLTC;
		पूर्ण

		value &= ~XGMAC_VLAN_VID;
		ग_लिखोl(value | perfect_match, ioaddr + XGMAC_VLAN_TAG);
	पूर्ण अन्यथा अणु
		u32 value = पढ़ोl(ioaddr + XGMAC_PACKET_FILTER);

		value &= ~XGMAC_FILTER_VTFE;

		ग_लिखोl(value, ioaddr + XGMAC_PACKET_FILTER);

		value = पढ़ोl(ioaddr + XGMAC_VLAN_TAG);

		value &= ~(XGMAC_VLAN_VTHM | XGMAC_VLAN_ETV);
		value &= ~(XGMAC_VLAN_EDVLP | XGMAC_VLAN_ESVL);
		value &= ~XGMAC_VLAN_DOVLTC;
		value &= ~XGMAC_VLAN_VID;

		ग_लिखोl(value, ioaddr + XGMAC_VLAN_TAG);
	पूर्ण
पूर्ण

काष्ठा dwxgmac3_error_desc अणु
	bool valid;
	स्थिर अक्षर *desc;
	स्थिर अक्षर *detailed_desc;
पूर्ण;

#घोषणा STAT_OFF(field)		दुरत्व(काष्ठा sपंचांगmac_safety_stats, field)

अटल व्योम dwxgmac3_log_error(काष्ठा net_device *ndev, u32 value, bool corr,
			       स्थिर अक्षर *module_name,
			       स्थिर काष्ठा dwxgmac3_error_desc *desc,
			       अचिन्हित दीर्घ field_offset,
			       काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	अचिन्हित दीर्घ loc, mask;
	u8 *bptr = (u8 *)stats;
	अचिन्हित दीर्घ *ptr;

	ptr = (अचिन्हित दीर्घ *)(bptr + field_offset);

	mask = value;
	क्रम_each_set_bit(loc, &mask, 32) अणु
		netdev_err(ndev, "Found %s error in %s: '%s: %s'\n", corr ?
				"correctable" : "uncorrectable", module_name,
				desc[loc].desc, desc[loc].detailed_desc);

		/* Update counters */
		ptr[loc]++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dwxgmac3_error_desc dwxgmac3_mac_errors[32]= अणु
	अणु true, "ATPES", "Application Transmit Interface Parity Check Error" पूर्ण,
	अणु true, "DPES", "Descriptor Cache Data Path Parity Check Error" पूर्ण,
	अणु true, "TPES", "TSO Data Path Parity Check Error" पूर्ण,
	अणु true, "TSOPES", "TSO Header Data Path Parity Check Error" पूर्ण,
	अणु true, "MTPES", "MTL Data Path Parity Check Error" पूर्ण,
	अणु true, "MTSPES", "MTL TX Status Data Path Parity Check Error" पूर्ण,
	अणु true, "MTBUPES", "MAC TBU Data Path Parity Check Error" पूर्ण,
	अणु true, "MTFCPES", "MAC TFC Data Path Parity Check Error" पूर्ण,
	अणु true, "ARPES", "Application Receive Interface Data Path Parity Check Error" पूर्ण,
	अणु true, "MRWCPES", "MTL RWC Data Path Parity Check Error" पूर्ण,
	अणु true, "MRRCPES", "MTL RCC Data Path Parity Check Error" पूर्ण,
	अणु true, "CWPES", "CSR Write Data Path Parity Check Error" पूर्ण,
	अणु true, "ASRPES", "AXI Slave Read Data Path Parity Check Error" पूर्ण,
	अणु true, "TTES", "TX FSM Timeout Error" पूर्ण,
	अणु true, "RTES", "RX FSM Timeout Error" पूर्ण,
	अणु true, "CTES", "CSR FSM Timeout Error" पूर्ण,
	अणु true, "ATES", "APP FSM Timeout Error" पूर्ण,
	अणु true, "PTES", "PTP FSM Timeout Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 18 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 19 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 20 */
	अणु true, "MSTTES", "Master Read/Write Timeout Error" पूर्ण,
	अणु true, "SLVTES", "Slave Read/Write Timeout Error" पूर्ण,
	अणु true, "ATITES", "Application Timeout on ATI Interface Error" पूर्ण,
	अणु true, "ARITES", "Application Timeout on ARI Interface Error" पूर्ण,
	अणु true, "FSMPES", "FSM State Parity Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 26 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 27 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 28 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 29 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 30 */
	अणु true, "CPI", "Control Register Parity Check Error" पूर्ण,
पूर्ण;

अटल व्योम dwxgmac3_handle_mac_err(काष्ठा net_device *ndev,
				    व्योम __iomem *ioaddr, bool correctable,
				    काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_MAC_DPP_FSM_INT_STATUS);
	ग_लिखोl(value, ioaddr + XGMAC_MAC_DPP_FSM_INT_STATUS);

	dwxgmac3_log_error(ndev, value, correctable, "MAC",
			   dwxgmac3_mac_errors, STAT_OFF(mac_errors), stats);
पूर्ण

अटल स्थिर काष्ठा dwxgmac3_error_desc dwxgmac3_mtl_errors[32]= अणु
	अणु true, "TXCES", "MTL TX Memory Error" पूर्ण,
	अणु true, "TXAMS", "MTL TX Memory Address Mismatch Error" पूर्ण,
	अणु true, "TXUES", "MTL TX Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 3 */
	अणु true, "RXCES", "MTL RX Memory Error" पूर्ण,
	अणु true, "RXAMS", "MTL RX Memory Address Mismatch Error" पूर्ण,
	अणु true, "RXUES", "MTL RX Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 7 */
	अणु true, "ECES", "MTL EST Memory Error" पूर्ण,
	अणु true, "EAMS", "MTL EST Memory Address Mismatch Error" पूर्ण,
	अणु true, "EUES", "MTL EST Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 11 */
	अणु true, "RPCES", "MTL RX Parser Memory Error" पूर्ण,
	अणु true, "RPAMS", "MTL RX Parser Memory Address Mismatch Error" पूर्ण,
	अणु true, "RPUES", "MTL RX Parser Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 15 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 16 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 17 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 18 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 19 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 20 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 21 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 22 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 23 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 24 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 25 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 26 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 27 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 28 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 29 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 30 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 31 */
पूर्ण;

अटल व्योम dwxgmac3_handle_mtl_err(काष्ठा net_device *ndev,
				    व्योम __iomem *ioaddr, bool correctable,
				    काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_MTL_ECC_INT_STATUS);
	ग_लिखोl(value, ioaddr + XGMAC_MTL_ECC_INT_STATUS);

	dwxgmac3_log_error(ndev, value, correctable, "MTL",
			   dwxgmac3_mtl_errors, STAT_OFF(mtl_errors), stats);
पूर्ण

अटल स्थिर काष्ठा dwxgmac3_error_desc dwxgmac3_dma_errors[32]= अणु
	अणु true, "TCES", "DMA TSO Memory Error" पूर्ण,
	अणु true, "TAMS", "DMA TSO Memory Address Mismatch Error" पूर्ण,
	अणु true, "TUES", "DMA TSO Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 3 */
	अणु true, "DCES", "DMA DCACHE Memory Error" पूर्ण,
	अणु true, "DAMS", "DMA DCACHE Address Mismatch Error" पूर्ण,
	अणु true, "DUES", "DMA DCACHE Memory Error" पूर्ण,
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 7 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 8 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 9 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 10 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 11 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 12 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 13 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 14 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 15 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 16 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 17 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 18 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 19 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 20 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 21 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 22 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 23 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 24 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 25 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 26 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 27 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 28 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 29 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 30 */
	अणु false, "UNKNOWN", "Unknown Error" पूर्ण, /* 31 */
पूर्ण;

अटल व्योम dwxgmac3_handle_dma_err(काष्ठा net_device *ndev,
				    व्योम __iomem *ioaddr, bool correctable,
				    काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_DMA_ECC_INT_STATUS);
	ग_लिखोl(value, ioaddr + XGMAC_DMA_ECC_INT_STATUS);

	dwxgmac3_log_error(ndev, value, correctable, "DMA",
			   dwxgmac3_dma_errors, STAT_OFF(dma_errors), stats);
पूर्ण

अटल पूर्णांक dwxgmac3_safety_feat_config(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक asp)
अणु
	u32 value;

	अगर (!asp)
		वापस -EINVAL;

	/* 1. Enable Safety Features */
	ग_लिखोl(0x0, ioaddr + XGMAC_MTL_ECC_CONTROL);

	/* 2. Enable MTL Safety Interrupts */
	value = पढ़ोl(ioaddr + XGMAC_MTL_ECC_INT_ENABLE);
	value |= XGMAC_RPCEIE; /* RX Parser Memory Correctable Error */
	value |= XGMAC_ECEIE; /* EST Memory Correctable Error */
	value |= XGMAC_RXCEIE; /* RX Memory Correctable Error */
	value |= XGMAC_TXCEIE; /* TX Memory Correctable Error */
	ग_लिखोl(value, ioaddr + XGMAC_MTL_ECC_INT_ENABLE);

	/* 3. Enable DMA Safety Interrupts */
	value = पढ़ोl(ioaddr + XGMAC_DMA_ECC_INT_ENABLE);
	value |= XGMAC_DCEIE; /* Descriptor Cache Memory Correctable Error */
	value |= XGMAC_TCEIE; /* TSO Memory Correctable Error */
	ग_लिखोl(value, ioaddr + XGMAC_DMA_ECC_INT_ENABLE);

	/* Only ECC Protection क्रम External Memory feature is selected */
	अगर (asp <= 0x1)
		वापस 0;

	/* 4. Enable Parity and Timeout क्रम FSM */
	value = पढ़ोl(ioaddr + XGMAC_MAC_FSM_CONTROL);
	value |= XGMAC_PRTYEN; /* FSM Parity Feature */
	value |= XGMAC_TMOUTEN; /* FSM Timeout Feature */
	ग_लिखोl(value, ioaddr + XGMAC_MAC_FSM_CONTROL);

	वापस 0;
पूर्ण

अटल पूर्णांक dwxgmac3_safety_feat_irq_status(काष्ठा net_device *ndev,
					   व्योम __iomem *ioaddr,
					   अचिन्हित पूर्णांक asp,
					   काष्ठा sपंचांगmac_safety_stats *stats)
अणु
	bool err, corr;
	u32 mtl, dma;
	पूर्णांक ret = 0;

	अगर (!asp)
		वापस -EINVAL;

	mtl = पढ़ोl(ioaddr + XGMAC_MTL_SAFETY_INT_STATUS);
	dma = पढ़ोl(ioaddr + XGMAC_DMA_SAFETY_INT_STATUS);

	err = (mtl & XGMAC_MCSIS) || (dma & XGMAC_MCSIS);
	corr = false;
	अगर (err) अणु
		dwxgmac3_handle_mac_err(ndev, ioaddr, corr, stats);
		ret |= !corr;
	पूर्ण

	err = (mtl & (XGMAC_MEUIS | XGMAC_MECIS)) ||
	      (dma & (XGMAC_MSUIS | XGMAC_MSCIS));
	corr = (mtl & XGMAC_MECIS) || (dma & XGMAC_MSCIS);
	अगर (err) अणु
		dwxgmac3_handle_mtl_err(ndev, ioaddr, corr, stats);
		ret |= !corr;
	पूर्ण

	err = dma & (XGMAC_DEUIS | XGMAC_DECIS);
	corr = dma & XGMAC_DECIS;
	अगर (err) अणु
		dwxgmac3_handle_dma_err(ndev, ioaddr, corr, stats);
		ret |= !corr;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dwxgmac3_error अणु
	स्थिर काष्ठा dwxgmac3_error_desc *desc;
पूर्ण dwxgmac3_all_errors[] = अणु
	अणु dwxgmac3_mac_errors पूर्ण,
	अणु dwxgmac3_mtl_errors पूर्ण,
	अणु dwxgmac3_dma_errors पूर्ण,
पूर्ण;

अटल पूर्णांक dwxgmac3_safety_feat_dump(काष्ठा sपंचांगmac_safety_stats *stats,
				     पूर्णांक index, अचिन्हित दीर्घ *count,
				     स्थिर अक्षर **desc)
अणु
	पूर्णांक module = index / 32, offset = index % 32;
	अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)stats;

	अगर (module >= ARRAY_SIZE(dwxgmac3_all_errors))
		वापस -EINVAL;
	अगर (!dwxgmac3_all_errors[module].desc[offset].valid)
		वापस -EINVAL;
	अगर (count)
		*count = *(ptr + index);
	अगर (desc)
		*desc = dwxgmac3_all_errors[module].desc[offset].desc;
	वापस 0;
पूर्ण

अटल पूर्णांक dwxgmac3_rxp_disable(व्योम __iomem *ioaddr)
अणु
	u32 val = पढ़ोl(ioaddr + XGMAC_MTL_OPMODE);

	val &= ~XGMAC_FRPE;
	ग_लिखोl(val, ioaddr + XGMAC_MTL_OPMODE);

	वापस 0;
पूर्ण

अटल व्योम dwxgmac3_rxp_enable(व्योम __iomem *ioaddr)
अणु
	u32 val;

	val = पढ़ोl(ioaddr + XGMAC_MTL_OPMODE);
	val |= XGMAC_FRPE;
	ग_लिखोl(val, ioaddr + XGMAC_MTL_OPMODE);
पूर्ण

अटल पूर्णांक dwxgmac3_rxp_update_single_entry(व्योम __iomem *ioaddr,
					    काष्ठा sपंचांगmac_tc_entry *entry,
					    पूर्णांक pos)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < (माप(entry->val) / माप(u32)); i++) अणु
		पूर्णांक real_pos = pos * (माप(entry->val) / माप(u32)) + i;
		u32 val;

		/* Wait क्रम पढ़ोy */
		ret = पढ़ोl_poll_समयout(ioaddr + XGMAC_MTL_RXP_IACC_CTRL_ST,
					 val, !(val & XGMAC_STARTBUSY), 1, 10000);
		अगर (ret)
			वापस ret;

		/* Write data */
		val = *((u32 *)&entry->val + i);
		ग_लिखोl(val, ioaddr + XGMAC_MTL_RXP_IACC_DATA);

		/* Write pos */
		val = real_pos & XGMAC_ADDR;
		ग_लिखोl(val, ioaddr + XGMAC_MTL_RXP_IACC_CTRL_ST);

		/* Write OP */
		val |= XGMAC_WRRDN;
		ग_लिखोl(val, ioaddr + XGMAC_MTL_RXP_IACC_CTRL_ST);

		/* Start Write */
		val |= XGMAC_STARTBUSY;
		ग_लिखोl(val, ioaddr + XGMAC_MTL_RXP_IACC_CTRL_ST);

		/* Wait क्रम करोne */
		ret = पढ़ोl_poll_समयout(ioaddr + XGMAC_MTL_RXP_IACC_CTRL_ST,
					 val, !(val & XGMAC_STARTBUSY), 1, 10000);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sपंचांगmac_tc_entry *
dwxgmac3_rxp_get_next_entry(काष्ठा sपंचांगmac_tc_entry *entries,
			    अचिन्हित पूर्णांक count, u32 curr_prio)
अणु
	काष्ठा sपंचांगmac_tc_entry *entry;
	u32 min_prio = ~0x0;
	पूर्णांक i, min_prio_idx;
	bool found = false;

	क्रम (i = count - 1; i >= 0; i--) अणु
		entry = &entries[i];

		/* Do not update unused entries */
		अगर (!entry->in_use)
			जारी;
		/* Do not update alपढ़ोy updated entries (i.e. fragments) */
		अगर (entry->in_hw)
			जारी;
		/* Let last entry be updated last */
		अगर (entry->is_last)
			जारी;
		/* Do not वापस fragments */
		अगर (entry->is_frag)
			जारी;
		/* Check अगर we alपढ़ोy checked this prio */
		अगर (entry->prio < curr_prio)
			जारी;
		/* Check अगर this is the minimum prio */
		अगर (entry->prio < min_prio) अणु
			min_prio = entry->prio;
			min_prio_idx = i;
			found = true;
		पूर्ण
	पूर्ण

	अगर (found)
		वापस &entries[min_prio_idx];
	वापस शून्य;
पूर्ण

अटल पूर्णांक dwxgmac3_rxp_config(व्योम __iomem *ioaddr,
			       काष्ठा sपंचांगmac_tc_entry *entries,
			       अचिन्हित पूर्णांक count)
अणु
	काष्ठा sपंचांगmac_tc_entry *entry, *frag;
	पूर्णांक i, ret, nve = 0;
	u32 curr_prio = 0;
	u32 old_val, val;

	/* Force disable RX */
	old_val = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);
	val = old_val & ~XGMAC_CONFIG_RE;
	ग_लिखोl(val, ioaddr + XGMAC_RX_CONFIG);

	/* Disable RX Parser */
	ret = dwxgmac3_rxp_disable(ioaddr);
	अगर (ret)
		जाओ re_enable;

	/* Set all entries as NOT in HW */
	क्रम (i = 0; i < count; i++) अणु
		entry = &entries[i];
		entry->in_hw = false;
	पूर्ण

	/* Update entries by reverse order */
	जबतक (1) अणु
		entry = dwxgmac3_rxp_get_next_entry(entries, count, curr_prio);
		अगर (!entry)
			अवरोध;

		curr_prio = entry->prio;
		frag = entry->frag_ptr;

		/* Set special fragment requirements */
		अगर (frag) अणु
			entry->val.af = 0;
			entry->val.rf = 0;
			entry->val.nc = 1;
			entry->val.ok_index = nve + 2;
		पूर्ण

		ret = dwxgmac3_rxp_update_single_entry(ioaddr, entry, nve);
		अगर (ret)
			जाओ re_enable;

		entry->table_pos = nve++;
		entry->in_hw = true;

		अगर (frag && !frag->in_hw) अणु
			ret = dwxgmac3_rxp_update_single_entry(ioaddr, frag, nve);
			अगर (ret)
				जाओ re_enable;
			frag->table_pos = nve++;
			frag->in_hw = true;
		पूर्ण
	पूर्ण

	अगर (!nve)
		जाओ re_enable;

	/* Update all pass entry */
	क्रम (i = 0; i < count; i++) अणु
		entry = &entries[i];
		अगर (!entry->is_last)
			जारी;

		ret = dwxgmac3_rxp_update_single_entry(ioaddr, entry, nve);
		अगर (ret)
			जाओ re_enable;

		entry->table_pos = nve++;
	पूर्ण

	/* Assume n. of parsable entries == n. of valid entries */
	val = (nve << 16) & XGMAC_NPE;
	val |= nve & XGMAC_NVE;
	ग_लिखोl(val, ioaddr + XGMAC_MTL_RXP_CONTROL_STATUS);

	/* Enable RX Parser */
	dwxgmac3_rxp_enable(ioaddr);

re_enable:
	/* Re-enable RX */
	ग_लिखोl(old_val, ioaddr + XGMAC_RX_CONFIG);
	वापस ret;
पूर्ण

अटल पूर्णांक dwxgmac2_get_mac_tx_बारtamp(काष्ठा mac_device_info *hw, u64 *ts)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	अगर (पढ़ोl_poll_समयout_atomic(ioaddr + XGMAC_TIMESTAMP_STATUS,
				      value, value & XGMAC_TXTSC, 100, 10000))
		वापस -EBUSY;

	*ts = पढ़ोl(ioaddr + XGMAC_TXTIMESTAMP_NSEC) & XGMAC_TXTSSTSLO;
	*ts += पढ़ोl(ioaddr + XGMAC_TXTIMESTAMP_SEC) * 1000000000ULL;
	वापस 0;
पूर्ण

अटल पूर्णांक dwxgmac2_flex_pps_config(व्योम __iomem *ioaddr, पूर्णांक index,
				    काष्ठा sपंचांगmac_pps_cfg *cfg, bool enable,
				    u32 sub_second_inc, u32 sysसमय_flags)
अणु
	u32 tnsec = पढ़ोl(ioaddr + XGMAC_PPSx_TARGET_TIME_NSEC(index));
	u32 val = पढ़ोl(ioaddr + XGMAC_PPS_CONTROL);
	u64 period;

	अगर (!cfg->available)
		वापस -EINVAL;
	अगर (tnsec & XGMAC_TRGTBUSY0)
		वापस -EBUSY;
	अगर (!sub_second_inc || !sysसमय_flags)
		वापस -EINVAL;

	val &= ~XGMAC_PPSx_MASK(index);

	अगर (!enable) अणु
		val |= XGMAC_PPSCMDx(index, XGMAC_PPSCMD_STOP);
		ग_लिखोl(val, ioaddr + XGMAC_PPS_CONTROL);
		वापस 0;
	पूर्ण

	val |= XGMAC_PPSCMDx(index, XGMAC_PPSCMD_START);
	val |= XGMAC_TRGTMODSELx(index, XGMAC_PPSCMD_START);
	val |= XGMAC_PPSEN0;

	ग_लिखोl(cfg->start.tv_sec, ioaddr + XGMAC_PPSx_TARGET_TIME_SEC(index));

	अगर (!(sysसमय_flags & PTP_TCR_TSCTRLSSR))
		cfg->start.tv_nsec = (cfg->start.tv_nsec * 1000) / 465;
	ग_लिखोl(cfg->start.tv_nsec, ioaddr + XGMAC_PPSx_TARGET_TIME_NSEC(index));

	period = cfg->period.tv_sec * 1000000000;
	period += cfg->period.tv_nsec;

	करो_भाग(period, sub_second_inc);

	अगर (period <= 1)
		वापस -EINVAL;

	ग_लिखोl(period - 1, ioaddr + XGMAC_PPSx_INTERVAL(index));

	period >>= 1;
	अगर (period <= 1)
		वापस -EINVAL;

	ग_लिखोl(period - 1, ioaddr + XGMAC_PPSx_WIDTH(index));

	/* Finally, activate it */
	ग_लिखोl(val, ioaddr + XGMAC_PPS_CONTROL);
	वापस 0;
पूर्ण

अटल व्योम dwxgmac2_sarc_configure(व्योम __iomem *ioaddr, पूर्णांक val)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_TX_CONFIG);

	value &= ~XGMAC_CONFIG_SARC;
	value |= val << XGMAC_CONFIG_SARC_SHIFT;

	ग_लिखोl(value, ioaddr + XGMAC_TX_CONFIG);
पूर्ण

अटल व्योम dwxgmac2_enable_vlan(काष्ठा mac_device_info *hw, u32 type)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_VLAN_INCL);
	value |= XGMAC_VLAN_VLTI;
	value |= XGMAC_VLAN_CSVL; /* Only use SVLAN */
	value &= ~XGMAC_VLAN_VLC;
	value |= (type << XGMAC_VLAN_VLC_SHIFT) & XGMAC_VLAN_VLC;
	ग_लिखोl(value, ioaddr + XGMAC_VLAN_INCL);
पूर्ण

अटल पूर्णांक dwxgmac2_filter_रुको(काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	अगर (पढ़ोl_poll_समयout(ioaddr + XGMAC_L3L4_ADDR_CTRL, value,
			       !(value & XGMAC_XB), 100, 10000))
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक dwxgmac2_filter_पढ़ो(काष्ठा mac_device_info *hw, u32 filter_no,
				u8 reg, u32 *data)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;
	पूर्णांक ret;

	ret = dwxgmac2_filter_रुको(hw);
	अगर (ret)
		वापस ret;

	value = ((filter_no << XGMAC_IDDR_FNUM) | reg) << XGMAC_IDDR_SHIFT;
	value |= XGMAC_TT | XGMAC_XB;
	ग_लिखोl(value, ioaddr + XGMAC_L3L4_ADDR_CTRL);

	ret = dwxgmac2_filter_रुको(hw);
	अगर (ret)
		वापस ret;

	*data = पढ़ोl(ioaddr + XGMAC_L3L4_DATA);
	वापस 0;
पूर्ण

अटल पूर्णांक dwxgmac2_filter_ग_लिखो(काष्ठा mac_device_info *hw, u32 filter_no,
				 u8 reg, u32 data)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;
	पूर्णांक ret;

	ret = dwxgmac2_filter_रुको(hw);
	अगर (ret)
		वापस ret;

	ग_लिखोl(data, ioaddr + XGMAC_L3L4_DATA);

	value = ((filter_no << XGMAC_IDDR_FNUM) | reg) << XGMAC_IDDR_SHIFT;
	value |= XGMAC_XB;
	ग_लिखोl(value, ioaddr + XGMAC_L3L4_ADDR_CTRL);

	वापस dwxgmac2_filter_रुको(hw);
पूर्ण

अटल पूर्णांक dwxgmac2_config_l3_filter(काष्ठा mac_device_info *hw, u32 filter_no,
				     bool en, bool ipv6, bool sa, bool inv,
				     u32 match)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;
	पूर्णांक ret;

	value = पढ़ोl(ioaddr + XGMAC_PACKET_FILTER);
	value |= XGMAC_FILTER_IPFE;
	ग_लिखोl(value, ioaddr + XGMAC_PACKET_FILTER);

	ret = dwxgmac2_filter_पढ़ो(hw, filter_no, XGMAC_L3L4_CTRL, &value);
	अगर (ret)
		वापस ret;

	/* For IPv6 not both SA/DA filters can be active */
	अगर (ipv6) अणु
		value |= XGMAC_L3PEN0;
		value &= ~(XGMAC_L3SAM0 | XGMAC_L3SAIM0);
		value &= ~(XGMAC_L3DAM0 | XGMAC_L3DAIM0);
		अगर (sa) अणु
			value |= XGMAC_L3SAM0;
			अगर (inv)
				value |= XGMAC_L3SAIM0;
		पूर्ण अन्यथा अणु
			value |= XGMAC_L3DAM0;
			अगर (inv)
				value |= XGMAC_L3DAIM0;
		पूर्ण
	पूर्ण अन्यथा अणु
		value &= ~XGMAC_L3PEN0;
		अगर (sa) अणु
			value |= XGMAC_L3SAM0;
			अगर (inv)
				value |= XGMAC_L3SAIM0;
		पूर्ण अन्यथा अणु
			value |= XGMAC_L3DAM0;
			अगर (inv)
				value |= XGMAC_L3DAIM0;
		पूर्ण
	पूर्ण

	ret = dwxgmac2_filter_ग_लिखो(hw, filter_no, XGMAC_L3L4_CTRL, value);
	अगर (ret)
		वापस ret;

	अगर (sa) अणु
		ret = dwxgmac2_filter_ग_लिखो(hw, filter_no, XGMAC_L3_ADDR0, match);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = dwxgmac2_filter_ग_लिखो(hw, filter_no, XGMAC_L3_ADDR1, match);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!en)
		वापस dwxgmac2_filter_ग_लिखो(hw, filter_no, XGMAC_L3L4_CTRL, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक dwxgmac2_config_l4_filter(काष्ठा mac_device_info *hw, u32 filter_no,
				     bool en, bool udp, bool sa, bool inv,
				     u32 match)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;
	पूर्णांक ret;

	value = पढ़ोl(ioaddr + XGMAC_PACKET_FILTER);
	value |= XGMAC_FILTER_IPFE;
	ग_लिखोl(value, ioaddr + XGMAC_PACKET_FILTER);

	ret = dwxgmac2_filter_पढ़ो(hw, filter_no, XGMAC_L3L4_CTRL, &value);
	अगर (ret)
		वापस ret;

	अगर (udp) अणु
		value |= XGMAC_L4PEN0;
	पूर्ण अन्यथा अणु
		value &= ~XGMAC_L4PEN0;
	पूर्ण

	value &= ~(XGMAC_L4SPM0 | XGMAC_L4SPIM0);
	value &= ~(XGMAC_L4DPM0 | XGMAC_L4DPIM0);
	अगर (sa) अणु
		value |= XGMAC_L4SPM0;
		अगर (inv)
			value |= XGMAC_L4SPIM0;
	पूर्ण अन्यथा अणु
		value |= XGMAC_L4DPM0;
		अगर (inv)
			value |= XGMAC_L4DPIM0;
	पूर्ण

	ret = dwxgmac2_filter_ग_लिखो(hw, filter_no, XGMAC_L3L4_CTRL, value);
	अगर (ret)
		वापस ret;

	अगर (sa) अणु
		value = match & XGMAC_L4SP0;

		ret = dwxgmac2_filter_ग_लिखो(hw, filter_no, XGMAC_L4_ADDR, value);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		value = (match << XGMAC_L4DP0_SHIFT) & XGMAC_L4DP0;

		ret = dwxgmac2_filter_ग_लिखो(hw, filter_no, XGMAC_L4_ADDR, value);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!en)
		वापस dwxgmac2_filter_ग_लिखो(hw, filter_no, XGMAC_L3L4_CTRL, 0);

	वापस 0;
पूर्ण

अटल व्योम dwxgmac2_set_arp_offload(काष्ठा mac_device_info *hw, bool en,
				     u32 addr)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	ग_लिखोl(addr, ioaddr + XGMAC_ARP_ADDR);

	value = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);
	अगर (en)
		value |= XGMAC_CONFIG_ARPEN;
	अन्यथा
		value &= ~XGMAC_CONFIG_ARPEN;
	ग_लिखोl(value, ioaddr + XGMAC_RX_CONFIG);
पूर्ण

अटल पूर्णांक dwxgmac3_est_ग_लिखो(व्योम __iomem *ioaddr, u32 reg, u32 val, bool gcl)
अणु
	u32 ctrl;

	ग_लिखोl(val, ioaddr + XGMAC_MTL_EST_GCL_DATA);

	ctrl = (reg << XGMAC_ADDR_SHIFT);
	ctrl |= gcl ? 0 : XGMAC_GCRR;

	ग_लिखोl(ctrl, ioaddr + XGMAC_MTL_EST_GCL_CONTROL);

	ctrl |= XGMAC_SRWO;
	ग_लिखोl(ctrl, ioaddr + XGMAC_MTL_EST_GCL_CONTROL);

	वापस पढ़ोl_poll_समयout_atomic(ioaddr + XGMAC_MTL_EST_GCL_CONTROL,
					 ctrl, !(ctrl & XGMAC_SRWO), 100, 5000);
पूर्ण

अटल पूर्णांक dwxgmac3_est_configure(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_est *cfg,
				  अचिन्हित पूर्णांक ptp_rate)
अणु
	पूर्णांक i, ret = 0x0;
	u32 ctrl;

	ret |= dwxgmac3_est_ग_लिखो(ioaddr, XGMAC_BTR_LOW, cfg->btr[0], false);
	ret |= dwxgmac3_est_ग_लिखो(ioaddr, XGMAC_BTR_HIGH, cfg->btr[1], false);
	ret |= dwxgmac3_est_ग_लिखो(ioaddr, XGMAC_TER, cfg->ter, false);
	ret |= dwxgmac3_est_ग_लिखो(ioaddr, XGMAC_LLR, cfg->gcl_size, false);
	ret |= dwxgmac3_est_ग_लिखो(ioaddr, XGMAC_CTR_LOW, cfg->ctr[0], false);
	ret |= dwxgmac3_est_ग_लिखो(ioaddr, XGMAC_CTR_HIGH, cfg->ctr[1], false);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < cfg->gcl_size; i++) अणु
		ret = dwxgmac3_est_ग_लिखो(ioaddr, i, cfg->gcl[i], true);
		अगर (ret)
			वापस ret;
	पूर्ण

	ctrl = पढ़ोl(ioaddr + XGMAC_MTL_EST_CONTROL);
	ctrl &= ~XGMAC_PTOV;
	ctrl |= ((1000000000 / ptp_rate) * 9) << XGMAC_PTOV_SHIFT;
	अगर (cfg->enable)
		ctrl |= XGMAC_EEST | XGMAC_SSWL;
	अन्यथा
		ctrl &= ~XGMAC_EEST;

	ग_लिखोl(ctrl, ioaddr + XGMAC_MTL_EST_CONTROL);
	वापस 0;
पूर्ण

अटल व्योम dwxgmac3_fpe_configure(व्योम __iomem *ioaddr, u32 num_txq,
				   u32 num_rxq, bool enable)
अणु
	u32 value;

	अगर (!enable) अणु
		value = पढ़ोl(ioaddr + XGMAC_FPE_CTRL_STS);

		value &= ~XGMAC_EFPE;

		ग_लिखोl(value, ioaddr + XGMAC_FPE_CTRL_STS);
		वापस;
	पूर्ण

	value = पढ़ोl(ioaddr + XGMAC_RXQ_CTRL1);
	value &= ~XGMAC_RQ;
	value |= (num_rxq - 1) << XGMAC_RQ_SHIFT;
	ग_लिखोl(value, ioaddr + XGMAC_RXQ_CTRL1);

	value = पढ़ोl(ioaddr + XGMAC_FPE_CTRL_STS);
	value |= XGMAC_EFPE;
	ग_लिखोl(value, ioaddr + XGMAC_FPE_CTRL_STS);
पूर्ण

स्थिर काष्ठा sपंचांगmac_ops dwxgmac210_ops = अणु
	.core_init = dwxgmac2_core_init,
	.set_mac = dwxgmac2_set_mac,
	.rx_ipc = dwxgmac2_rx_ipc,
	.rx_queue_enable = dwxgmac2_rx_queue_enable,
	.rx_queue_prio = dwxgmac2_rx_queue_prio,
	.tx_queue_prio = dwxgmac2_tx_queue_prio,
	.rx_queue_routing = शून्य,
	.prog_mtl_rx_algorithms = dwxgmac2_prog_mtl_rx_algorithms,
	.prog_mtl_tx_algorithms = dwxgmac2_prog_mtl_tx_algorithms,
	.set_mtl_tx_queue_weight = dwxgmac2_set_mtl_tx_queue_weight,
	.map_mtl_to_dma = dwxgmac2_map_mtl_to_dma,
	.config_cbs = dwxgmac2_config_cbs,
	.dump_regs = dwxgmac2_dump_regs,
	.host_irq_status = dwxgmac2_host_irq_status,
	.host_mtl_irq_status = dwxgmac2_host_mtl_irq_status,
	.flow_ctrl = dwxgmac2_flow_ctrl,
	.pmt = dwxgmac2_pmt,
	.set_umac_addr = dwxgmac2_set_umac_addr,
	.get_umac_addr = dwxgmac2_get_umac_addr,
	.set_eee_mode = dwxgmac2_set_eee_mode,
	.reset_eee_mode = dwxgmac2_reset_eee_mode,
	.set_eee_समयr = dwxgmac2_set_eee_समयr,
	.set_eee_pls = dwxgmac2_set_eee_pls,
	.pcs_ctrl_ane = शून्य,
	.pcs_rane = शून्य,
	.pcs_get_adv_lp = शून्य,
	.debug = शून्य,
	.set_filter = dwxgmac2_set_filter,
	.safety_feat_config = dwxgmac3_safety_feat_config,
	.safety_feat_irq_status = dwxgmac3_safety_feat_irq_status,
	.safety_feat_dump = dwxgmac3_safety_feat_dump,
	.set_mac_loopback = dwxgmac2_set_mac_loopback,
	.rss_configure = dwxgmac2_rss_configure,
	.update_vlan_hash = dwxgmac2_update_vlan_hash,
	.rxp_config = dwxgmac3_rxp_config,
	.get_mac_tx_बारtamp = dwxgmac2_get_mac_tx_बारtamp,
	.flex_pps_config = dwxgmac2_flex_pps_config,
	.sarc_configure = dwxgmac2_sarc_configure,
	.enable_vlan = dwxgmac2_enable_vlan,
	.config_l3_filter = dwxgmac2_config_l3_filter,
	.config_l4_filter = dwxgmac2_config_l4_filter,
	.set_arp_offload = dwxgmac2_set_arp_offload,
	.est_configure = dwxgmac3_est_configure,
	.fpe_configure = dwxgmac3_fpe_configure,
पूर्ण;

अटल व्योम dwxlgmac2_rx_queue_enable(काष्ठा mac_device_info *hw, u8 mode,
				      u32 queue)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 value;

	value = पढ़ोl(ioaddr + XLGMAC_RXQ_ENABLE_CTRL0) & ~XGMAC_RXQEN(queue);
	अगर (mode == MTL_QUEUE_AVB)
		value |= 0x1 << XGMAC_RXQEN_SHIFT(queue);
	अन्यथा अगर (mode == MTL_QUEUE_DCB)
		value |= 0x2 << XGMAC_RXQEN_SHIFT(queue);
	ग_लिखोl(value, ioaddr + XLGMAC_RXQ_ENABLE_CTRL0);
पूर्ण

स्थिर काष्ठा sपंचांगmac_ops dwxlgmac2_ops = अणु
	.core_init = dwxgmac2_core_init,
	.set_mac = dwxgmac2_set_mac,
	.rx_ipc = dwxgmac2_rx_ipc,
	.rx_queue_enable = dwxlgmac2_rx_queue_enable,
	.rx_queue_prio = dwxgmac2_rx_queue_prio,
	.tx_queue_prio = dwxgmac2_tx_queue_prio,
	.rx_queue_routing = शून्य,
	.prog_mtl_rx_algorithms = dwxgmac2_prog_mtl_rx_algorithms,
	.prog_mtl_tx_algorithms = dwxgmac2_prog_mtl_tx_algorithms,
	.set_mtl_tx_queue_weight = dwxgmac2_set_mtl_tx_queue_weight,
	.map_mtl_to_dma = dwxgmac2_map_mtl_to_dma,
	.config_cbs = dwxgmac2_config_cbs,
	.dump_regs = dwxgmac2_dump_regs,
	.host_irq_status = dwxgmac2_host_irq_status,
	.host_mtl_irq_status = dwxgmac2_host_mtl_irq_status,
	.flow_ctrl = dwxgmac2_flow_ctrl,
	.pmt = dwxgmac2_pmt,
	.set_umac_addr = dwxgmac2_set_umac_addr,
	.get_umac_addr = dwxgmac2_get_umac_addr,
	.set_eee_mode = dwxgmac2_set_eee_mode,
	.reset_eee_mode = dwxgmac2_reset_eee_mode,
	.set_eee_समयr = dwxgmac2_set_eee_समयr,
	.set_eee_pls = dwxgmac2_set_eee_pls,
	.pcs_ctrl_ane = शून्य,
	.pcs_rane = शून्य,
	.pcs_get_adv_lp = शून्य,
	.debug = शून्य,
	.set_filter = dwxgmac2_set_filter,
	.safety_feat_config = dwxgmac3_safety_feat_config,
	.safety_feat_irq_status = dwxgmac3_safety_feat_irq_status,
	.safety_feat_dump = dwxgmac3_safety_feat_dump,
	.set_mac_loopback = dwxgmac2_set_mac_loopback,
	.rss_configure = dwxgmac2_rss_configure,
	.update_vlan_hash = dwxgmac2_update_vlan_hash,
	.rxp_config = dwxgmac3_rxp_config,
	.get_mac_tx_बारtamp = dwxgmac2_get_mac_tx_बारtamp,
	.flex_pps_config = dwxgmac2_flex_pps_config,
	.sarc_configure = dwxgmac2_sarc_configure,
	.enable_vlan = dwxgmac2_enable_vlan,
	.config_l3_filter = dwxgmac2_config_l3_filter,
	.config_l4_filter = dwxgmac2_config_l4_filter,
	.set_arp_offload = dwxgmac2_set_arp_offload,
	.est_configure = dwxgmac3_est_configure,
	.fpe_configure = dwxgmac3_fpe_configure,
पूर्ण;

पूर्णांक dwxgmac2_setup(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा mac_device_info *mac = priv->hw;

	dev_info(priv->device, "\tXGMAC2\n");

	priv->dev->priv_flags |= IFF_UNICAST_FLT;
	mac->pcsr = priv->ioaddr;
	mac->multicast_filter_bins = priv->plat->multicast_filter_bins;
	mac->unicast_filter_entries = priv->plat->unicast_filter_entries;
	mac->mcast_bits_log2 = 0;

	अगर (mac->multicast_filter_bins)
		mac->mcast_bits_log2 = ilog2(mac->multicast_filter_bins);

	mac->link.duplex = 0;
	mac->link.speed10 = XGMAC_CONFIG_SS_10_MII;
	mac->link.speed100 = XGMAC_CONFIG_SS_100_MII;
	mac->link.speed1000 = XGMAC_CONFIG_SS_1000_GMII;
	mac->link.speed2500 = XGMAC_CONFIG_SS_2500_GMII;
	mac->link.xgmii.speed2500 = XGMAC_CONFIG_SS_2500;
	mac->link.xgmii.speed5000 = XGMAC_CONFIG_SS_5000;
	mac->link.xgmii.speed10000 = XGMAC_CONFIG_SS_10000;
	mac->link.speed_mask = XGMAC_CONFIG_SS_MASK;

	mac->mii.addr = XGMAC_MDIO_ADDR;
	mac->mii.data = XGMAC_MDIO_DATA;
	mac->mii.addr_shअगरt = 16;
	mac->mii.addr_mask = GENMASK(20, 16);
	mac->mii.reg_shअगरt = 0;
	mac->mii.reg_mask = GENMASK(15, 0);
	mac->mii.clk_csr_shअगरt = 19;
	mac->mii.clk_csr_mask = GENMASK(21, 19);

	वापस 0;
पूर्ण

पूर्णांक dwxlgmac2_setup(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा mac_device_info *mac = priv->hw;

	dev_info(priv->device, "\tXLGMAC\n");

	priv->dev->priv_flags |= IFF_UNICAST_FLT;
	mac->pcsr = priv->ioaddr;
	mac->multicast_filter_bins = priv->plat->multicast_filter_bins;
	mac->unicast_filter_entries = priv->plat->unicast_filter_entries;
	mac->mcast_bits_log2 = 0;

	अगर (mac->multicast_filter_bins)
		mac->mcast_bits_log2 = ilog2(mac->multicast_filter_bins);

	mac->link.duplex = 0;
	mac->link.speed1000 = XLGMAC_CONFIG_SS_1000;
	mac->link.speed2500 = XLGMAC_CONFIG_SS_2500;
	mac->link.xgmii.speed10000 = XLGMAC_CONFIG_SS_10G;
	mac->link.xlgmii.speed25000 = XLGMAC_CONFIG_SS_25G;
	mac->link.xlgmii.speed40000 = XLGMAC_CONFIG_SS_40G;
	mac->link.xlgmii.speed50000 = XLGMAC_CONFIG_SS_50G;
	mac->link.xlgmii.speed100000 = XLGMAC_CONFIG_SS_100G;
	mac->link.speed_mask = XLGMAC_CONFIG_SS;

	mac->mii.addr = XGMAC_MDIO_ADDR;
	mac->mii.data = XGMAC_MDIO_DATA;
	mac->mii.addr_shअगरt = 16;
	mac->mii.addr_mask = GENMASK(20, 16);
	mac->mii.reg_shअगरt = 0;
	mac->mii.reg_mask = GENMASK(15, 0);
	mac->mii.clk_csr_shअगरt = 19;
	mac->mii.clk_csr_mask = GENMASK(21, 19);

	वापस 0;
पूर्ण
