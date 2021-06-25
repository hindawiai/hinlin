<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 */

/* Qualcomm Technologies, Inc. EMAC Gigabit Ethernet Driver */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश "emac.h"
#समावेश "emac-mac.h"
#समावेश "emac-phy.h"
#समावेश "emac-sgmii.h"

#घोषणा EMAC_MSG_DEFAULT (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK |  \
		NETIF_MSG_TIMER | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP)

#घोषणा EMAC_RRD_SIZE					     4
/* The RRD size अगर बारtamping is enabled: */
#घोषणा EMAC_TS_RRD_SIZE				     6
#घोषणा EMAC_TPD_SIZE					     4
#घोषणा EMAC_RFD_SIZE					     2

#घोषणा REG_MAC_RX_STATUS_BIN		 EMAC_RXMAC_STATC_REG0
#घोषणा REG_MAC_RX_STATUS_END		EMAC_RXMAC_STATC_REG22
#घोषणा REG_MAC_TX_STATUS_BIN		 EMAC_TXMAC_STATC_REG0
#घोषणा REG_MAC_TX_STATUS_END		EMAC_TXMAC_STATC_REG24

#घोषणा RXQ0_NUM_RFD_PREF_DEF				     8
#घोषणा TXQ0_NUM_TPD_PREF_DEF				     5

#घोषणा EMAC_PREAMBLE_DEF				     7

#घोषणा DMAR_DLY_CNT_DEF				    15
#घोषणा DMAW_DLY_CNT_DEF				     4

#घोषणा IMR_NORMAL_MASK		(ISR_ERROR | ISR_OVER | ISR_TX_PKT)

#घोषणा ISR_TX_PKT      (\
	TX_PKT_INT      |\
	TX_PKT_INT1     |\
	TX_PKT_INT2     |\
	TX_PKT_INT3)

#घोषणा ISR_OVER        (\
	RFD0_UR_INT     |\
	RFD1_UR_INT     |\
	RFD2_UR_INT     |\
	RFD3_UR_INT     |\
	RFD4_UR_INT     |\
	RXF_OF_INT      |\
	TXF_UR_INT)

#घोषणा ISR_ERROR       (\
	DMAR_TO_INT     |\
	DMAW_TO_INT     |\
	TXQ_TO_INT)

/* in sync with क्रमागत emac_clk_id */
अटल स्थिर अक्षर * स्थिर emac_clk_name[] = अणु
	"axi_clk", "cfg_ahb_clk", "high_speed_clk", "mdio_clk", "tx_clk",
	"rx_clk", "sys_clk"
पूर्ण;

व्योम emac_reg_update32(व्योम __iomem *addr, u32 mask, u32 val)
अणु
	u32 data = पढ़ोl(addr);

	ग_लिखोl(((data & ~mask) | val), addr);
पूर्ण

/* reinitialize */
पूर्णांक emac_reinit_locked(काष्ठा emac_adapter *adpt)
अणु
	पूर्णांक ret;

	mutex_lock(&adpt->reset_lock);

	emac_mac_करोwn(adpt);
	emac_sgmii_reset(adpt);
	ret = emac_mac_up(adpt);

	mutex_unlock(&adpt->reset_lock);

	वापस ret;
पूर्ण

/* NAPI */
अटल पूर्णांक emac_napi_rtx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा emac_rx_queue *rx_q =
		container_of(napi, काष्ठा emac_rx_queue, napi);
	काष्ठा emac_adapter *adpt = netdev_priv(rx_q->netdev);
	काष्ठा emac_irq *irq = rx_q->irq;
	पूर्णांक work_करोne = 0;

	emac_mac_rx_process(adpt, rx_q, &work_करोne, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);

		irq->mask |= rx_q->पूर्णांकr;
		ग_लिखोl(irq->mask, adpt->base + EMAC_INT_MASK);
	पूर्ण

	वापस work_करोne;
पूर्ण

/* Transmit the packet */
अटल netdev_tx_t emac_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *netdev)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	वापस emac_mac_tx_buf_send(adpt, &adpt->tx_q, skb);
पूर्ण

अटल irqवापस_t emac_isr(पूर्णांक _irq, व्योम *data)
अणु
	काष्ठा emac_irq *irq = data;
	काष्ठा emac_adapter *adpt =
		container_of(irq, काष्ठा emac_adapter, irq);
	काष्ठा emac_rx_queue *rx_q = &adpt->rx_q;
	u32 isr, status;

	/* disable the पूर्णांकerrupt */
	ग_लिखोl(0, adpt->base + EMAC_INT_MASK);

	isr = पढ़ोl_relaxed(adpt->base + EMAC_INT_STATUS);

	status = isr & irq->mask;
	अगर (status == 0)
		जाओ निकास;

	अगर (status & ISR_ERROR) अणु
		net_err_ratelimited("%s: error interrupt 0x%lx\n",
				    adpt->netdev->name, status & ISR_ERROR);
		/* reset MAC */
		schedule_work(&adpt->work_thपढ़ो);
	पूर्ण

	/* Schedule the napi क्रम receive queue with पूर्णांकerrupt
	 * status bit set
	 */
	अगर (status & rx_q->पूर्णांकr) अणु
		अगर (napi_schedule_prep(&rx_q->napi)) अणु
			irq->mask &= ~rx_q->पूर्णांकr;
			__napi_schedule(&rx_q->napi);
		पूर्ण
	पूर्ण

	अगर (status & TX_PKT_INT)
		emac_mac_tx_process(adpt, &adpt->tx_q);

	अगर (status & ISR_OVER)
		net_warn_ratelimited("%s: TX/RX overflow interrupt\n",
				     adpt->netdev->name);

निकास:
	/* enable the पूर्णांकerrupt */
	ग_लिखोl(irq->mask, adpt->base + EMAC_INT_MASK);

	वापस IRQ_HANDLED;
पूर्ण

/* Configure VLAN tag strip/insert feature */
अटल पूर्णांक emac_set_features(काष्ठा net_device *netdev,
			     netdev_features_t features)
अणु
	netdev_features_t changed = features ^ netdev->features;
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	/* We only need to reprogram the hardware अगर the VLAN tag features
	 * have changed, and अगर it's alपढ़ोy running.
	 */
	अगर (!(changed & (NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX)))
		वापस 0;

	अगर (!netअगर_running(netdev))
		वापस 0;

	/* emac_mac_mode_config() uses netdev->features to configure the EMAC,
	 * so make sure it's set first.
	 */
	netdev->features = features;

	वापस emac_reinit_locked(adpt);
पूर्ण

/* Configure Multicast and Promiscuous modes */
अटल व्योम emac_rx_mode_set(काष्ठा net_device *netdev)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);
	काष्ठा netdev_hw_addr *ha;

	emac_mac_mode_config(adpt);

	/* update multicast address filtering */
	emac_mac_multicast_addr_clear(adpt);
	netdev_क्रम_each_mc_addr(ha, netdev)
		emac_mac_multicast_addr_set(adpt, ha->addr);
पूर्ण

/* Change the Maximum Transfer Unit (MTU) */
अटल पूर्णांक emac_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	netअगर_dbg(adpt, hw, adpt->netdev,
		  "changing MTU from %d to %d\n", netdev->mtu,
		  new_mtu);
	netdev->mtu = new_mtu;

	अगर (netअगर_running(netdev))
		वापस emac_reinit_locked(adpt);

	वापस 0;
पूर्ण

/* Called when the network पूर्णांकerface is made active */
अटल पूर्णांक emac_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);
	काष्ठा emac_irq	*irq = &adpt->irq;
	पूर्णांक ret;

	ret = request_irq(irq->irq, emac_isr, 0, "emac-core0", irq);
	अगर (ret) अणु
		netdev_err(adpt->netdev, "could not request emac-core0 irq\n");
		वापस ret;
	पूर्ण

	/* allocate rx/tx dma buffer & descriptors */
	ret = emac_mac_rx_tx_rings_alloc_all(adpt);
	अगर (ret) अणु
		netdev_err(adpt->netdev, "error allocating rx/tx rings\n");
		मुक्त_irq(irq->irq, irq);
		वापस ret;
	पूर्ण

	ret = emac_sgmii_खोलो(adpt);
	अगर (ret) अणु
		emac_mac_rx_tx_rings_मुक्त_all(adpt);
		मुक्त_irq(irq->irq, irq);
		वापस ret;
	पूर्ण

	ret = emac_mac_up(adpt);
	अगर (ret) अणु
		emac_mac_rx_tx_rings_मुक्त_all(adpt);
		मुक्त_irq(irq->irq, irq);
		emac_sgmii_बंद(adpt);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Called when the network पूर्णांकerface is disabled */
अटल पूर्णांक emac_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	mutex_lock(&adpt->reset_lock);

	emac_sgmii_बंद(adpt);
	emac_mac_करोwn(adpt);
	emac_mac_rx_tx_rings_मुक्त_all(adpt);

	मुक्त_irq(adpt->irq.irq, &adpt->irq);

	mutex_unlock(&adpt->reset_lock);

	वापस 0;
पूर्ण

/* Respond to a TX hang */
अटल व्योम emac_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	schedule_work(&adpt->work_thपढ़ो);
पूर्ण

/**
 * emac_update_hw_stats - पढ़ो the EMAC stat रेजिस्टरs
 * @adpt: poपूर्णांकer to adapter काष्ठा
 *
 * Reads the stats रेजिस्टरs and ग_लिखो the values to adpt->stats.
 *
 * adpt->stats.lock must be held जबतक calling this function,
 * and जबतक पढ़ोing from adpt->stats.
 */
व्योम emac_update_hw_stats(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_stats *stats = &adpt->stats;
	u64 *stats_itr = &adpt->stats.rx_ok;
	व्योम __iomem *base = adpt->base;
	अचिन्हित पूर्णांक addr;

	addr = REG_MAC_RX_STATUS_BIN;
	जबतक (addr <= REG_MAC_RX_STATUS_END) अणु
		*stats_itr += पढ़ोl_relaxed(base + addr);
		stats_itr++;
		addr += माप(u32);
	पूर्ण

	/* additional rx status */
	stats->rx_crc_align += पढ़ोl_relaxed(base + EMAC_RXMAC_STATC_REG23);
	stats->rx_jabbers += पढ़ोl_relaxed(base + EMAC_RXMAC_STATC_REG24);

	/* update tx status */
	addr = REG_MAC_TX_STATUS_BIN;
	stats_itr = &stats->tx_ok;

	जबतक (addr <= REG_MAC_TX_STATUS_END) अणु
		*stats_itr += पढ़ोl_relaxed(base + addr);
		stats_itr++;
		addr += माप(u32);
	पूर्ण

	/* additional tx status */
	stats->tx_col += पढ़ोl_relaxed(base + EMAC_TXMAC_STATC_REG25);
पूर्ण

/* Provide network statistics info क्रम the पूर्णांकerface */
अटल व्योम emac_get_stats64(काष्ठा net_device *netdev,
			     काष्ठा rtnl_link_stats64 *net_stats)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);
	काष्ठा emac_stats *stats = &adpt->stats;

	spin_lock(&stats->lock);

	emac_update_hw_stats(adpt);

	/* वापस parsed statistics */
	net_stats->rx_packets = stats->rx_ok;
	net_stats->tx_packets = stats->tx_ok;
	net_stats->rx_bytes = stats->rx_byte_cnt;
	net_stats->tx_bytes = stats->tx_byte_cnt;
	net_stats->multicast = stats->rx_mcast;
	net_stats->collisions = stats->tx_1_col + stats->tx_2_col * 2 +
				stats->tx_late_col + stats->tx_पात_col;

	net_stats->rx_errors = stats->rx_frag + stats->rx_fcs_err +
			       stats->rx_len_err + stats->rx_sz_ov +
			       stats->rx_align_err;
	net_stats->rx_fअगरo_errors = stats->rx_rxf_ov;
	net_stats->rx_length_errors = stats->rx_len_err;
	net_stats->rx_crc_errors = stats->rx_fcs_err;
	net_stats->rx_frame_errors = stats->rx_align_err;
	net_stats->rx_over_errors = stats->rx_rxf_ov;
	net_stats->rx_missed_errors = stats->rx_rxf_ov;

	net_stats->tx_errors = stats->tx_late_col + stats->tx_पात_col +
			       stats->tx_underrun + stats->tx_trunc;
	net_stats->tx_fअगरo_errors = stats->tx_underrun;
	net_stats->tx_पातed_errors = stats->tx_पात_col;
	net_stats->tx_winकरोw_errors = stats->tx_late_col;

	spin_unlock(&stats->lock);
पूर्ण

अटल स्थिर काष्ठा net_device_ops emac_netdev_ops = अणु
	.nकरो_खोलो		= emac_खोलो,
	.nकरो_stop		= emac_बंद,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_start_xmit		= emac_start_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_change_mtu		= emac_change_mtu,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_tx_समयout		= emac_tx_समयout,
	.nकरो_get_stats64	= emac_get_stats64,
	.nकरो_set_features       = emac_set_features,
	.nकरो_set_rx_mode        = emac_rx_mode_set,
पूर्ण;

/* Watchकरोg task routine, called to reinitialize the EMAC */
अटल व्योम emac_work_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा emac_adapter *adpt =
		container_of(work, काष्ठा emac_adapter, work_thपढ़ो);

	emac_reinit_locked(adpt);
पूर्ण

/* Initialize various data काष्ठाures  */
अटल व्योम emac_init_adapter(काष्ठा emac_adapter *adpt)
अणु
	u32 reg;

	adpt->rrd_size = EMAC_RRD_SIZE;
	adpt->tpd_size = EMAC_TPD_SIZE;
	adpt->rfd_size = EMAC_RFD_SIZE;

	/* descriptors */
	adpt->tx_desc_cnt = EMAC_DEF_TX_DESCS;
	adpt->rx_desc_cnt = EMAC_DEF_RX_DESCS;

	/* dma */
	adpt->dma_order = emac_dma_ord_out;
	adpt->dmar_block = emac_dma_req_4096;
	adpt->dmaw_block = emac_dma_req_128;
	adpt->dmar_dly_cnt = DMAR_DLY_CNT_DEF;
	adpt->dmaw_dly_cnt = DMAW_DLY_CNT_DEF;
	adpt->tpd_burst = TXQ0_NUM_TPD_PREF_DEF;
	adpt->rfd_burst = RXQ0_NUM_RFD_PREF_DEF;

	/* irq moderator */
	reg = ((EMAC_DEF_RX_IRQ_MOD >> 1) << IRQ_MODERATOR2_INIT_SHFT) |
	      ((EMAC_DEF_TX_IRQ_MOD >> 1) << IRQ_MODERATOR_INIT_SHFT);
	adpt->irq_mod = reg;

	/* others */
	adpt->preamble = EMAC_PREAMBLE_DEF;

	/* शेष to स्वतःmatic flow control */
	adpt->स्वतःmatic = true;

	/* Disable single-छोड़ो-frame mode by शेष */
	adpt->single_छोड़ो_mode = false;
पूर्ण

/* Get the घड़ी */
अटल पूर्णांक emac_clks_get(काष्ठा platक्रमm_device *pdev,
			 काष्ठा emac_adapter *adpt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < EMAC_CLK_CNT; i++) अणु
		काष्ठा clk *clk = devm_clk_get(&pdev->dev, emac_clk_name[i]);

		अगर (IS_ERR(clk)) अणु
			dev_err(&pdev->dev,
				"could not claim clock %s (error=%li)\n",
				emac_clk_name[i], PTR_ERR(clk));

			वापस PTR_ERR(clk);
		पूर्ण

		adpt->clk[i] = clk;
	पूर्ण

	वापस 0;
पूर्ण

/* Initialize घड़ीs */
अटल पूर्णांक emac_clks_phase1_init(काष्ठा platक्रमm_device *pdev,
				 काष्ठा emac_adapter *adpt)
अणु
	पूर्णांक ret;

	/* On ACPI platक्रमms, घड़ीs are controlled by firmware and/or
	 * ACPI, not by drivers.
	 */
	अगर (has_acpi_companion(&pdev->dev))
		वापस 0;

	ret = emac_clks_get(pdev, adpt);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(adpt->clk[EMAC_CLK_AXI]);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(adpt->clk[EMAC_CLK_CFG_AHB]);
	अगर (ret)
		जाओ disable_clk_axi;

	ret = clk_set_rate(adpt->clk[EMAC_CLK_HIGH_SPEED], 19200000);
	अगर (ret)
		जाओ disable_clk_cfg_ahb;

	ret = clk_prepare_enable(adpt->clk[EMAC_CLK_HIGH_SPEED]);
	अगर (ret)
		जाओ disable_clk_cfg_ahb;

	वापस 0;

disable_clk_cfg_ahb:
	clk_disable_unprepare(adpt->clk[EMAC_CLK_CFG_AHB]);
disable_clk_axi:
	clk_disable_unprepare(adpt->clk[EMAC_CLK_AXI]);

	वापस ret;
पूर्ण

/* Enable घड़ीs; needs emac_clks_phase1_init to be called beक्रमe */
अटल पूर्णांक emac_clks_phase2_init(काष्ठा platक्रमm_device *pdev,
				 काष्ठा emac_adapter *adpt)
अणु
	पूर्णांक ret;

	अगर (has_acpi_companion(&pdev->dev))
		वापस 0;

	ret = clk_set_rate(adpt->clk[EMAC_CLK_TX], 125000000);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(adpt->clk[EMAC_CLK_TX]);
	अगर (ret)
		वापस ret;

	ret = clk_set_rate(adpt->clk[EMAC_CLK_HIGH_SPEED], 125000000);
	अगर (ret)
		वापस ret;

	ret = clk_set_rate(adpt->clk[EMAC_CLK_MDIO], 25000000);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(adpt->clk[EMAC_CLK_MDIO]);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(adpt->clk[EMAC_CLK_RX]);
	अगर (ret)
		वापस ret;

	वापस clk_prepare_enable(adpt->clk[EMAC_CLK_SYS]);
पूर्ण

अटल व्योम emac_clks_tearकरोwn(काष्ठा emac_adapter *adpt)
अणु

	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < EMAC_CLK_CNT; i++)
		clk_disable_unprepare(adpt->clk[i]);
पूर्ण

/* Get the resources */
अटल पूर्णांक emac_probe_resources(काष्ठा platक्रमm_device *pdev,
				काष्ठा emac_adapter *adpt)
अणु
	काष्ठा net_device *netdev = adpt->netdev;
	अक्षर maddr[ETH_ALEN];
	पूर्णांक ret = 0;

	/* get mac address */
	अगर (device_get_mac_address(&pdev->dev, maddr, ETH_ALEN))
		ether_addr_copy(netdev->dev_addr, maddr);
	अन्यथा
		eth_hw_addr_अक्रमom(netdev);

	/* Core 0 पूर्णांकerrupt */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	adpt->irq.irq = ret;

	/* base रेजिस्टर address */
	adpt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(adpt->base))
		वापस PTR_ERR(adpt->base);

	/* CSR रेजिस्टर address */
	adpt->csr = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(adpt->csr))
		वापस PTR_ERR(adpt->csr);

	netdev->base_addr = (अचिन्हित दीर्घ)adpt->base;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id emac_dt_match[] = अणु
	अणु
		.compatible = "qcom,fsm9900-emac",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, emac_dt_match);

#अगर IS_ENABLED(CONFIG_ACPI)
अटल स्थिर काष्ठा acpi_device_id emac_acpi_match[] = अणु
	अणु
		.id = "QCOM8070",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, emac_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक emac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev;
	काष्ठा emac_adapter *adpt;
	काष्ठा emac_sgmii *phy;
	u16 devid, revid;
	u32 reg;
	पूर्णांक ret;

	/* The TPD buffer address is limited to:
	 * 1. PTP:	45bits. (Driver करोesn't support yet.)
	 * 2. NON-PTP:	46bits.
	 */
	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(46));
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not set DMA mask\n");
		वापस ret;
	पूर्ण

	netdev = alloc_etherdev(माप(काष्ठा emac_adapter));
	अगर (!netdev)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, netdev);
	SET_NETDEV_DEV(netdev, &pdev->dev);
	emac_set_ethtool_ops(netdev);

	adpt = netdev_priv(netdev);
	adpt->netdev = netdev;
	adpt->msg_enable = EMAC_MSG_DEFAULT;

	phy = &adpt->phy;
	atomic_set(&phy->decode_error_count, 0);

	mutex_init(&adpt->reset_lock);
	spin_lock_init(&adpt->stats.lock);

	adpt->irq.mask = RX_PKT_INT0 | IMR_NORMAL_MASK;

	ret = emac_probe_resources(pdev, adpt);
	अगर (ret)
		जाओ err_unकरो_netdev;

	/* initialize घड़ीs */
	ret = emac_clks_phase1_init(pdev, adpt);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not initialize clocks\n");
		जाओ err_unकरो_netdev;
	पूर्ण

	netdev->watchकरोg_समयo = EMAC_WATCHDOG_TIME;
	netdev->irq = adpt->irq.irq;

	netdev->netdev_ops = &emac_netdev_ops;

	emac_init_adapter(adpt);

	/* init बाह्यal phy */
	ret = emac_phy_config(pdev, adpt);
	अगर (ret)
		जाओ err_unकरो_घड़ीs;

	/* init पूर्णांकernal sgmii phy */
	ret = emac_sgmii_config(pdev, adpt);
	अगर (ret)
		जाओ err_unकरो_mdiobus;

	/* enable घड़ीs */
	ret = emac_clks_phase2_init(pdev, adpt);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not initialize clocks\n");
		जाओ err_unकरो_mdiobus;
	पूर्ण

	/* set hw features */
	netdev->features = NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_RXCSUM |
			NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_HW_VLAN_CTAG_RX |
			NETIF_F_HW_VLAN_CTAG_TX;
	netdev->hw_features = netdev->features;

	netdev->vlan_features |= NETIF_F_SG | NETIF_F_HW_CSUM |
				 NETIF_F_TSO | NETIF_F_TSO6;

	/* MTU range: 46 - 9194 */
	netdev->min_mtu = EMAC_MIN_ETH_FRAME_SIZE -
			  (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);
	netdev->max_mtu = EMAC_MAX_ETH_FRAME_SIZE -
			  (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);

	INIT_WORK(&adpt->work_thपढ़ो, emac_work_thपढ़ो);

	/* Initialize queues */
	emac_mac_rx_tx_ring_init_all(pdev, adpt);

	netअगर_napi_add(netdev, &adpt->rx_q.napi, emac_napi_rtx,
		       NAPI_POLL_WEIGHT);

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register net device\n");
		जाओ err_unकरो_napi;
	पूर्ण

	reg =  पढ़ोl_relaxed(adpt->base + EMAC_DMA_MAS_CTRL);
	devid = (reg & DEV_ID_NUM_BMSK)  >> DEV_ID_NUM_SHFT;
	revid = (reg & DEV_REV_NUM_BMSK) >> DEV_REV_NUM_SHFT;
	reg = पढ़ोl_relaxed(adpt->base + EMAC_CORE_HW_VERSION);

	netअगर_info(adpt, probe, netdev,
		   "hardware id %d.%d, hardware version %d.%d.%d\n",
		   devid, revid,
		   (reg & MAJOR_BMSK) >> MAJOR_SHFT,
		   (reg & MINOR_BMSK) >> MINOR_SHFT,
		   (reg & STEP_BMSK)  >> STEP_SHFT);

	वापस 0;

err_unकरो_napi:
	netअगर_napi_del(&adpt->rx_q.napi);
err_unकरो_mdiobus:
	put_device(&adpt->phydev->mdio.dev);
	mdiobus_unरेजिस्टर(adpt->mii_bus);
err_unकरो_घड़ीs:
	emac_clks_tearकरोwn(adpt);
err_unकरो_netdev:
	मुक्त_netdev(netdev);

	वापस ret;
पूर्ण

अटल पूर्णांक emac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(&pdev->dev);
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	unरेजिस्टर_netdev(netdev);
	netअगर_napi_del(&adpt->rx_q.napi);

	emac_clks_tearकरोwn(adpt);

	put_device(&adpt->phydev->mdio.dev);
	mdiobus_unरेजिस्टर(adpt->mii_bus);
	मुक्त_netdev(netdev);

	अगर (adpt->phy.digital)
		iounmap(adpt->phy.digital);
	iounmap(adpt->phy.base);

	वापस 0;
पूर्ण

अटल व्योम emac_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(&pdev->dev);
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);

	अगर (netdev->flags & IFF_UP) अणु
		/* Closing the SGMII turns off its पूर्णांकerrupts */
		emac_sgmii_बंद(adpt);

		/* Resetting the MAC turns off all DMA and its पूर्णांकerrupts */
		emac_mac_reset(adpt);
	पूर्ण
पूर्ण

अटल काष्ठा platक्रमm_driver emac_platक्रमm_driver = अणु
	.probe	= emac_probe,
	.हटाओ	= emac_हटाओ,
	.driver = अणु
		.name		= "qcom-emac",
		.of_match_table = emac_dt_match,
		.acpi_match_table = ACPI_PTR(emac_acpi_match),
	पूर्ण,
	.shutकरोwn = emac_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(emac_platक्रमm_driver);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:qcom-emac");
