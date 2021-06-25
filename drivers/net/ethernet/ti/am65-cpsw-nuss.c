<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Texas Instruments K3 AM65 Ethernet Switch SubSystem Driver
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/dma/ti-cppi5.h>
#समावेश <linux/dma/k3-udma-glue.h>

#समावेश "cpsw_ale.h"
#समावेश "cpsw_sl.h"
#समावेश "am65-cpsw-nuss.h"
#समावेश "am65-cpsw-switchdev.h"
#समावेश "k3-cppi-desc-pool.h"
#समावेश "am65-cpts.h"

#घोषणा AM65_CPSW_SS_BASE	0x0
#घोषणा AM65_CPSW_SGMII_BASE	0x100
#घोषणा AM65_CPSW_XGMII_BASE	0x2100
#घोषणा AM65_CPSW_CPSW_NU_BASE	0x20000
#घोषणा AM65_CPSW_NU_PORTS_BASE	0x1000
#घोषणा AM65_CPSW_NU_FRAM_BASE	0x12000
#घोषणा AM65_CPSW_NU_STATS_BASE	0x1a000
#घोषणा AM65_CPSW_NU_ALE_BASE	0x1e000
#घोषणा AM65_CPSW_NU_CPTS_BASE	0x1d000

#घोषणा AM65_CPSW_NU_PORTS_OFFSET	0x1000
#घोषणा AM65_CPSW_NU_STATS_PORT_OFFSET	0x200
#घोषणा AM65_CPSW_NU_FRAM_PORT_OFFSET	0x200

#घोषणा AM65_CPSW_MAX_PORTS	8

#घोषणा AM65_CPSW_MIN_PACKET_SIZE	VLAN_ETH_ZLEN
#घोषणा AM65_CPSW_MAX_PACKET_SIZE	(VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)

#घोषणा AM65_CPSW_REG_CTL		0x004
#घोषणा AM65_CPSW_REG_STAT_PORT_EN	0x014
#घोषणा AM65_CPSW_REG_PTYPE		0x018

#घोषणा AM65_CPSW_P0_REG_CTL			0x004
#घोषणा AM65_CPSW_PORT0_REG_FLOW_ID_OFFSET	0x008

#घोषणा AM65_CPSW_PORT_REG_PRI_CTL		0x01c
#घोषणा AM65_CPSW_PORT_REG_RX_PRI_MAP		0x020
#घोषणा AM65_CPSW_PORT_REG_RX_MAXLEN		0x024

#घोषणा AM65_CPSW_PORTN_REG_SA_L		0x308
#घोषणा AM65_CPSW_PORTN_REG_SA_H		0x30c
#घोषणा AM65_CPSW_PORTN_REG_TS_CTL              0x310
#घोषणा AM65_CPSW_PORTN_REG_TS_SEQ_LTYPE_REG	0x314
#घोषणा AM65_CPSW_PORTN_REG_TS_VLAN_LTYPE_REG	0x318
#घोषणा AM65_CPSW_PORTN_REG_TS_CTL_LTYPE2       0x31C

#घोषणा AM65_CPSW_CTL_VLAN_AWARE		BIT(1)
#घोषणा AM65_CPSW_CTL_P0_ENABLE			BIT(2)
#घोषणा AM65_CPSW_CTL_P0_TX_CRC_REMOVE		BIT(13)
#घोषणा AM65_CPSW_CTL_P0_RX_PAD			BIT(14)

/* AM65_CPSW_P0_REG_CTL */
#घोषणा AM65_CPSW_P0_REG_CTL_RX_CHECKSUM_EN	BIT(0)

/* AM65_CPSW_PORT_REG_PRI_CTL */
#घोषणा AM65_CPSW_PORT_REG_PRI_CTL_RX_PTYPE_RROBIN	BIT(8)

/* AM65_CPSW_PN_TS_CTL रेजिस्टर fields */
#घोषणा AM65_CPSW_PN_TS_CTL_TX_ANX_F_EN		BIT(4)
#घोषणा AM65_CPSW_PN_TS_CTL_TX_VLAN_LT1_EN	BIT(5)
#घोषणा AM65_CPSW_PN_TS_CTL_TX_VLAN_LT2_EN	BIT(6)
#घोषणा AM65_CPSW_PN_TS_CTL_TX_ANX_D_EN		BIT(7)
#घोषणा AM65_CPSW_PN_TS_CTL_TX_ANX_E_EN		BIT(10)
#घोषणा AM65_CPSW_PN_TS_CTL_TX_HOST_TS_EN	BIT(11)
#घोषणा AM65_CPSW_PN_TS_CTL_MSG_TYPE_EN_SHIFT	16

/* AM65_CPSW_PORTN_REG_TS_SEQ_LTYPE_REG रेजिस्टर fields */
#घोषणा AM65_CPSW_PN_TS_SEQ_ID_OFFSET_SHIFT	16

/* AM65_CPSW_PORTN_REG_TS_CTL_LTYPE2 */
#घोषणा AM65_CPSW_PN_TS_CTL_LTYPE2_TS_107	BIT(16)
#घोषणा AM65_CPSW_PN_TS_CTL_LTYPE2_TS_129	BIT(17)
#घोषणा AM65_CPSW_PN_TS_CTL_LTYPE2_TS_130	BIT(18)
#घोषणा AM65_CPSW_PN_TS_CTL_LTYPE2_TS_131	BIT(19)
#घोषणा AM65_CPSW_PN_TS_CTL_LTYPE2_TS_132	BIT(20)
#घोषणा AM65_CPSW_PN_TS_CTL_LTYPE2_TS_319	BIT(21)
#घोषणा AM65_CPSW_PN_TS_CTL_LTYPE2_TS_320	BIT(22)
#घोषणा AM65_CPSW_PN_TS_CTL_LTYPE2_TS_TTL_NONZERO BIT(23)

/* The PTP event messages - Sync, Delay_Req, Pdelay_Req, and Pdelay_Resp. */
#घोषणा AM65_CPSW_TS_EVENT_MSG_TYPE_BITS (BIT(0) | BIT(1) | BIT(2) | BIT(3))

#घोषणा AM65_CPSW_TS_SEQ_ID_OFFSET (0x1e)

#घोषणा AM65_CPSW_TS_TX_ANX_ALL_EN		\
	(AM65_CPSW_PN_TS_CTL_TX_ANX_D_EN |	\
	 AM65_CPSW_PN_TS_CTL_TX_ANX_E_EN |	\
	 AM65_CPSW_PN_TS_CTL_TX_ANX_F_EN)

#घोषणा AM65_CPSW_ALE_AGEOUT_DEFAULT	30
/* Number of TX/RX descriptors */
#घोषणा AM65_CPSW_MAX_TX_DESC	500
#घोषणा AM65_CPSW_MAX_RX_DESC	500

#घोषणा AM65_CPSW_NAV_PS_DATA_SIZE 16
#घोषणा AM65_CPSW_NAV_SW_DATA_SIZE 16

#घोषणा AM65_CPSW_DEBUG	(NETIF_MSG_HW | NETIF_MSG_DRV | NETIF_MSG_LINK | \
			 NETIF_MSG_IFUP	| NETIF_MSG_PROBE | NETIF_MSG_IFDOWN | \
			 NETIF_MSG_RX_ERR | NETIF_MSG_TX_ERR)

अटल व्योम am65_cpsw_port_set_sl_mac(काष्ठा am65_cpsw_port *slave,
				      स्थिर u8 *dev_addr)
अणु
	u32 mac_hi = (dev_addr[0] << 0) | (dev_addr[1] << 8) |
		     (dev_addr[2] << 16) | (dev_addr[3] << 24);
	u32 mac_lo = (dev_addr[4] << 0) | (dev_addr[5] << 8);

	ग_लिखोl(mac_hi, slave->port_base + AM65_CPSW_PORTN_REG_SA_H);
	ग_लिखोl(mac_lo, slave->port_base + AM65_CPSW_PORTN_REG_SA_L);
पूर्ण

अटल व्योम am65_cpsw_sl_ctl_reset(काष्ठा am65_cpsw_port *port)
अणु
	cpsw_sl_reset(port->slave.mac_sl, 100);
	/* Max length रेजिस्टर has to be restored after MAC SL reset */
	ग_लिखोl(AM65_CPSW_MAX_PACKET_SIZE,
	       port->port_base + AM65_CPSW_PORT_REG_RX_MAXLEN);
पूर्ण

अटल व्योम am65_cpsw_nuss_get_ver(काष्ठा am65_cpsw_common *common)
अणु
	common->nuss_ver = पढ़ोl(common->ss_base);
	common->cpsw_ver = पढ़ोl(common->cpsw_base);
	dev_info(common->dev,
		 "initializing am65 cpsw nuss version 0x%08X, cpsw version 0x%08X Ports: %u quirks:%08x\n",
		common->nuss_ver,
		common->cpsw_ver,
		common->port_num + 1,
		common->pdata.quirks);
पूर्ण

व्योम am65_cpsw_nuss_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा phy_device *phy = port->slave.phy;
	u32 mac_control = 0;

	अगर (!phy)
		वापस;

	अगर (phy->link) अणु
		mac_control = CPSW_SL_CTL_GMII_EN;

		अगर (phy->speed == 1000)
			mac_control |= CPSW_SL_CTL_GIG;
		अगर (phy->speed == 10 && phy_पूर्णांकerface_is_rgmii(phy))
			/* Can be used with in band mode only */
			mac_control |= CPSW_SL_CTL_EXT_EN;
		अगर (phy->speed == 100 && phy->पूर्णांकerface == PHY_INTERFACE_MODE_RMII)
			mac_control |= CPSW_SL_CTL_IFCTL_A;
		अगर (phy->duplex)
			mac_control |= CPSW_SL_CTL_FULLDUPLEX;

		/* RGMII speed is 100M अगर !CPSW_SL_CTL_GIG*/

		/* rx_छोड़ो/tx_छोड़ो */
		अगर (port->slave.rx_छोड़ो)
			mac_control |= CPSW_SL_CTL_RX_FLOW_EN;

		अगर (port->slave.tx_छोड़ो)
			mac_control |= CPSW_SL_CTL_TX_FLOW_EN;

		cpsw_sl_ctl_set(port->slave.mac_sl, mac_control);

		/* enable क्रमwarding */
		cpsw_ale_control_set(common->ale, port->port_id,
				     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

		am65_cpsw_qos_link_up(ndev, phy->speed);
		netअगर_tx_wake_all_queues(ndev);
	पूर्ण अन्यथा अणु
		पूर्णांक पंचांगo;

		/* disable क्रमwarding */
		cpsw_ale_control_set(common->ale, port->port_id,
				     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);

		cpsw_sl_ctl_set(port->slave.mac_sl, CPSW_SL_CTL_CMD_IDLE);

		पंचांगo = cpsw_sl_रुको_क्रम_idle(port->slave.mac_sl, 100);
		dev_dbg(common->dev, "donw msc_sl %08x tmo %d\n",
			cpsw_sl_reg_पढ़ो(port->slave.mac_sl, CPSW_SL_MACSTATUS),
			पंचांगo);

		cpsw_sl_ctl_reset(port->slave.mac_sl);

		am65_cpsw_qos_link_करोwn(ndev);
		netअगर_tx_stop_all_queues(ndev);
	पूर्ण

	phy_prपूर्णांक_status(phy);
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_nकरो_slave_add_vid(काष्ठा net_device *ndev,
					    __be16 proto, u16 vid)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	u32 port_mask, unreg_mcast = 0;
	पूर्णांक ret;

	अगर (!common->is_emac_mode)
		वापस 0;

	अगर (!netअगर_running(ndev) || !vid)
		वापस 0;

	ret = pm_runसमय_get_sync(common->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(common->dev);
		वापस ret;
	पूर्ण

	port_mask = BIT(port->port_id) | ALE_PORT_HOST;
	अगर (!vid)
		unreg_mcast = port_mask;
	dev_info(common->dev, "Adding vlan %d to vlan filter\n", vid);
	ret = cpsw_ale_vlan_add_modअगरy(common->ale, vid, port_mask,
				       unreg_mcast, port_mask, 0);

	pm_runसमय_put(common->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_nकरो_slave_समाप्त_vid(काष्ठा net_device *ndev,
					     __be16 proto, u16 vid)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	पूर्णांक ret;

	अगर (!common->is_emac_mode)
		वापस 0;

	अगर (!netअगर_running(ndev) || !vid)
		वापस 0;

	ret = pm_runसमय_get_sync(common->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(common->dev);
		वापस ret;
	पूर्ण

	dev_info(common->dev, "Removing vlan %d from vlan filter\n", vid);
	ret = cpsw_ale_del_vlan(common->ale, vid,
				BIT(port->port_id) | ALE_PORT_HOST);

	pm_runसमय_put(common->dev);
	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_slave_set_promisc(काष्ठा am65_cpsw_port *port,
					bool promisc)
अणु
	काष्ठा am65_cpsw_common *common = port->common;

	अगर (promisc && !common->is_emac_mode) अणु
		dev_dbg(common->dev, "promisc mode requested in switch mode");
		वापस;
	पूर्ण

	अगर (promisc) अणु
		/* Enable promiscuous mode */
		cpsw_ale_control_set(common->ale, port->port_id,
				     ALE_PORT_MACONLY_CAF, 1);
		dev_dbg(common->dev, "promisc enabled\n");
	पूर्ण अन्यथा अणु
		/* Disable promiscuous mode */
		cpsw_ale_control_set(common->ale, port->port_id,
				     ALE_PORT_MACONLY_CAF, 0);
		dev_dbg(common->dev, "promisc disabled\n");
	पूर्ण
पूर्ण

अटल व्योम am65_cpsw_nuss_nकरो_slave_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	u32 port_mask;
	bool promisc;

	promisc = !!(ndev->flags & IFF_PROMISC);
	am65_cpsw_slave_set_promisc(port, promisc);

	अगर (promisc)
		वापस;

	/* Restore allmulti on vlans अगर necessary */
	cpsw_ale_set_allmulti(common->ale,
			      ndev->flags & IFF_ALLMULTI, port->port_id);

	port_mask = ALE_PORT_HOST;
	/* Clear all mcast from ALE */
	cpsw_ale_flush_multicast(common->ale, port_mask, -1);

	अगर (!netdev_mc_empty(ndev)) अणु
		काष्ठा netdev_hw_addr *ha;

		/* program multicast address list पूर्णांकo ALE रेजिस्टर */
		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			cpsw_ale_add_mcast(common->ale, ha->addr,
					   port_mask, 0, 0, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम am65_cpsw_nuss_nकरो_host_tx_समयout(काष्ठा net_device *ndev,
					       अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_tx_chn *tx_chn;
	काष्ठा netdev_queue *netअगर_txq;
	अचिन्हित दीर्घ trans_start;

	netअगर_txq = netdev_get_tx_queue(ndev, txqueue);
	tx_chn = &common->tx_chns[txqueue];
	trans_start = netअगर_txq->trans_start;

	netdev_err(ndev, "txq:%d DRV_XOFF:%d tmo:%u dql_avail:%d free_desc:%zu\n",
		   txqueue,
		   netअगर_tx_queue_stopped(netअगर_txq),
		   jअगरfies_to_msecs(jअगरfies - trans_start),
		   dql_avail(&netअगर_txq->dql),
		   k3_cppi_desc_pool_avail(tx_chn->desc_pool));

	अगर (netअगर_tx_queue_stopped(netअगर_txq)) अणु
		/* try recover अगर stopped by us */
		txq_trans_update(netअगर_txq);
		netअगर_tx_wake_queue(netअगर_txq);
	पूर्ण
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_rx_push(काष्ठा am65_cpsw_common *common,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा am65_cpsw_rx_chn *rx_chn = &common->rx_chns;
	काष्ठा cppi5_host_desc_t *desc_rx;
	काष्ठा device *dev = common->dev;
	u32 pkt_len = skb_tailroom(skb);
	dma_addr_t desc_dma;
	dma_addr_t buf_dma;
	व्योम *swdata;

	desc_rx = k3_cppi_desc_pool_alloc(rx_chn->desc_pool);
	अगर (!desc_rx) अणु
		dev_err(dev, "Failed to allocate RXFDQ descriptor\n");
		वापस -ENOMEM;
	पूर्ण
	desc_dma = k3_cppi_desc_pool_virt2dma(rx_chn->desc_pool, desc_rx);

	buf_dma = dma_map_single(rx_chn->dma_dev, skb->data, pkt_len,
				 DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(rx_chn->dma_dev, buf_dma))) अणु
		k3_cppi_desc_pool_मुक्त(rx_chn->desc_pool, desc_rx);
		dev_err(dev, "Failed to map rx skb buffer\n");
		वापस -EINVAL;
	पूर्ण

	cppi5_hdesc_init(desc_rx, CPPI5_INFO0_HDESC_EPIB_PRESENT,
			 AM65_CPSW_NAV_PS_DATA_SIZE);
	k3_udma_glue_rx_dma_to_cppi5_addr(rx_chn->rx_chn, &buf_dma);
	cppi5_hdesc_attach_buf(desc_rx, buf_dma, skb_tailroom(skb), buf_dma, skb_tailroom(skb));
	swdata = cppi5_hdesc_get_swdata(desc_rx);
	*((व्योम **)swdata) = skb;

	वापस k3_udma_glue_push_rx_chn(rx_chn->rx_chn, 0, desc_rx, desc_dma);
पूर्ण

व्योम am65_cpsw_nuss_set_p0_ptype(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा am65_cpsw_host *host_p = am65_common_get_host(common);
	u32 val, pri_map;

	/* P0 set Receive Priority Type */
	val = पढ़ोl(host_p->port_base + AM65_CPSW_PORT_REG_PRI_CTL);

	अगर (common->pf_p0_rx_ptype_rrobin) अणु
		val |= AM65_CPSW_PORT_REG_PRI_CTL_RX_PTYPE_RROBIN;
		/* Enet Ports fअगरos works in fixed priority mode only, so
		 * reset P0_Rx_Pri_Map so all packet will go in Enet fअगरo 0
		 */
		pri_map = 0x0;
	पूर्ण अन्यथा अणु
		val &= ~AM65_CPSW_PORT_REG_PRI_CTL_RX_PTYPE_RROBIN;
		/* restore P0_Rx_Pri_Map */
		pri_map = 0x76543210;
	पूर्ण

	ग_लिखोl(pri_map, host_p->port_base + AM65_CPSW_PORT_REG_RX_PRI_MAP);
	ग_लिखोl(val, host_p->port_base + AM65_CPSW_PORT_REG_PRI_CTL);
पूर्ण

अटल व्योम am65_cpsw_init_host_port_चयन(काष्ठा am65_cpsw_common *common);
अटल व्योम am65_cpsw_init_host_port_emac(काष्ठा am65_cpsw_common *common);
अटल व्योम am65_cpsw_init_port_चयन_ale(काष्ठा am65_cpsw_port *port);
अटल व्योम am65_cpsw_init_port_emac_ale(काष्ठा am65_cpsw_port *port);

अटल पूर्णांक am65_cpsw_nuss_common_खोलो(काष्ठा am65_cpsw_common *common,
				      netdev_features_t features)
अणु
	काष्ठा am65_cpsw_host *host_p = am65_common_get_host(common);
	पूर्णांक port_idx, i, ret;
	काष्ठा sk_buff *skb;
	u32 val, port_mask;

	अगर (common->usage_count)
		वापस 0;

	/* Control रेजिस्टर */
	ग_लिखोl(AM65_CPSW_CTL_P0_ENABLE | AM65_CPSW_CTL_P0_TX_CRC_REMOVE |
	       AM65_CPSW_CTL_VLAN_AWARE | AM65_CPSW_CTL_P0_RX_PAD,
	       common->cpsw_base + AM65_CPSW_REG_CTL);
	/* Max length रेजिस्टर */
	ग_लिखोl(AM65_CPSW_MAX_PACKET_SIZE,
	       host_p->port_base + AM65_CPSW_PORT_REG_RX_MAXLEN);
	/* set base flow_id */
	ग_लिखोl(common->rx_flow_id_base,
	       host_p->port_base + AM65_CPSW_PORT0_REG_FLOW_ID_OFFSET);
	/* en tx crc offload */
	ग_लिखोl(AM65_CPSW_P0_REG_CTL_RX_CHECKSUM_EN, host_p->port_base + AM65_CPSW_P0_REG_CTL);

	am65_cpsw_nuss_set_p0_ptype(common);

	/* enable statistic */
	val = BIT(HOST_PORT_NUM);
	क्रम (port_idx = 0; port_idx < common->port_num; port_idx++) अणु
		काष्ठा am65_cpsw_port *port = &common->ports[port_idx];

		अगर (!port->disabled)
			val |=  BIT(port->port_id);
	पूर्ण
	ग_लिखोl(val, common->cpsw_base + AM65_CPSW_REG_STAT_PORT_EN);

	/* disable priority elevation */
	ग_लिखोl(0, common->cpsw_base + AM65_CPSW_REG_PTYPE);

	cpsw_ale_start(common->ale);

	/* limit to one RX flow only */
	cpsw_ale_control_set(common->ale, HOST_PORT_NUM,
			     ALE_DEFAULT_THREAD_ID, 0);
	cpsw_ale_control_set(common->ale, HOST_PORT_NUM,
			     ALE_DEFAULT_THREAD_ENABLE, 1);
	/* चयन to vlan unaware mode */
	cpsw_ale_control_set(common->ale, HOST_PORT_NUM, ALE_VLAN_AWARE, 1);
	cpsw_ale_control_set(common->ale, HOST_PORT_NUM,
			     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

	/* शेष vlan cfg: create mask based on enabled ports */
	port_mask = GENMASK(common->port_num, 0) &
		    ~common->disabled_ports_mask;

	cpsw_ale_add_vlan(common->ale, 0, port_mask,
			  port_mask, port_mask,
			  port_mask & ~ALE_PORT_HOST);

	अगर (common->is_emac_mode)
		am65_cpsw_init_host_port_emac(common);
	अन्यथा
		am65_cpsw_init_host_port_चयन(common);

	क्रम (i = 0; i < common->rx_chns.descs_num; i++) अणु
		skb = __netdev_alloc_skb_ip_align(शून्य,
						  AM65_CPSW_MAX_PACKET_SIZE,
						  GFP_KERNEL);
		अगर (!skb) अणु
			dev_err(common->dev, "cannot allocate skb\n");
			वापस -ENOMEM;
		पूर्ण

		ret = am65_cpsw_nuss_rx_push(common, skb);
		अगर (ret < 0) अणु
			dev_err(common->dev,
				"cannot submit skb to channel rx, error %d\n",
				ret);
			kमुक्त_skb(skb);
			वापस ret;
		पूर्ण
		kmemleak_not_leak(skb);
	पूर्ण
	k3_udma_glue_enable_rx_chn(common->rx_chns.rx_chn);

	क्रम (i = 0; i < common->tx_ch_num; i++) अणु
		ret = k3_udma_glue_enable_tx_chn(common->tx_chns[i].tx_chn);
		अगर (ret)
			वापस ret;
		napi_enable(&common->tx_chns[i].napi_tx);
	पूर्ण

	napi_enable(&common->napi_rx);

	dev_dbg(common->dev, "cpsw_nuss started\n");
	वापस 0;
पूर्ण

अटल व्योम am65_cpsw_nuss_tx_cleanup(व्योम *data, dma_addr_t desc_dma);
अटल व्योम am65_cpsw_nuss_rx_cleanup(व्योम *data, dma_addr_t desc_dma);

अटल पूर्णांक am65_cpsw_nuss_common_stop(काष्ठा am65_cpsw_common *common)
अणु
	पूर्णांक i;

	अगर (common->usage_count != 1)
		वापस 0;

	cpsw_ale_control_set(common->ale, HOST_PORT_NUM,
			     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);

	/* shutकरोwn tx channels */
	atomic_set(&common->tकरोwn_cnt, common->tx_ch_num);
	/* ensure new tकरोwn_cnt value is visible */
	smp_mb__after_atomic();
	reinit_completion(&common->tकरोwn_complete);

	क्रम (i = 0; i < common->tx_ch_num; i++)
		k3_udma_glue_tकरोwn_tx_chn(common->tx_chns[i].tx_chn, false);

	i = रुको_क्रम_completion_समयout(&common->tकरोwn_complete,
					msecs_to_jअगरfies(1000));
	अगर (!i)
		dev_err(common->dev, "tx timeout\n");
	क्रम (i = 0; i < common->tx_ch_num; i++)
		napi_disable(&common->tx_chns[i].napi_tx);

	क्रम (i = 0; i < common->tx_ch_num; i++) अणु
		k3_udma_glue_reset_tx_chn(common->tx_chns[i].tx_chn,
					  &common->tx_chns[i],
					  am65_cpsw_nuss_tx_cleanup);
		k3_udma_glue_disable_tx_chn(common->tx_chns[i].tx_chn);
	पूर्ण

	k3_udma_glue_tकरोwn_rx_chn(common->rx_chns.rx_chn, true);
	napi_disable(&common->napi_rx);

	क्रम (i = 0; i < AM65_CPSW_MAX_RX_FLOWS; i++)
		k3_udma_glue_reset_rx_chn(common->rx_chns.rx_chn, i,
					  &common->rx_chns,
					  am65_cpsw_nuss_rx_cleanup, !!i);

	k3_udma_glue_disable_rx_chn(common->rx_chns.rx_chn);

	cpsw_ale_stop(common->ale);

	ग_लिखोl(0, common->cpsw_base + AM65_CPSW_REG_CTL);
	ग_लिखोl(0, common->cpsw_base + AM65_CPSW_REG_STAT_PORT_EN);

	dev_dbg(common->dev, "cpsw_nuss stopped\n");
	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_nकरो_slave_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	पूर्णांक ret;

	अगर (port->slave.phy)
		phy_stop(port->slave.phy);

	netअगर_tx_stop_all_queues(ndev);

	अगर (port->slave.phy) अणु
		phy_disconnect(port->slave.phy);
		port->slave.phy = शून्य;
	पूर्ण

	ret = am65_cpsw_nuss_common_stop(common);
	अगर (ret)
		वापस ret;

	common->usage_count--;
	pm_runसमय_put(common->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_restore_vlans(काष्ठा net_device *vdev, पूर्णांक vid, व्योम *arg)
अणु
	काष्ठा am65_cpsw_port *port = arg;

	अगर (!vdev)
		वापस 0;

	वापस am65_cpsw_nuss_nकरो_slave_add_vid(port->ndev, 0, vid);
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_nकरो_slave_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	पूर्णांक ret, i;

	ret = pm_runसमय_get_sync(common->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(common->dev);
		वापस ret;
	पूर्ण

	/* Notअगरy the stack of the actual queue counts. */
	ret = netअगर_set_real_num_tx_queues(ndev, common->tx_ch_num);
	अगर (ret) अणु
		dev_err(common->dev, "cannot set real number of tx queues\n");
		वापस ret;
	पूर्ण

	ret = netअगर_set_real_num_rx_queues(ndev, AM65_CPSW_MAX_RX_QUEUES);
	अगर (ret) अणु
		dev_err(common->dev, "cannot set real number of rx queues\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < common->tx_ch_num; i++)
		netdev_tx_reset_queue(netdev_get_tx_queue(ndev, i));

	ret = am65_cpsw_nuss_common_खोलो(common, ndev->features);
	अगर (ret)
		वापस ret;

	common->usage_count++;

	am65_cpsw_port_set_sl_mac(port, ndev->dev_addr);

	अगर (common->is_emac_mode)
		am65_cpsw_init_port_emac_ale(port);
	अन्यथा
		am65_cpsw_init_port_चयन_ale(port);

	/* mac_sl should be configured via phy-link पूर्णांकerface */
	am65_cpsw_sl_ctl_reset(port);

	ret = phy_set_mode_ext(port->slave.अगरphy, PHY_MODE_ETHERNET,
			       port->slave.phy_अगर);
	अगर (ret)
		जाओ error_cleanup;

	अगर (port->slave.phy_node) अणु
		port->slave.phy = of_phy_connect(ndev,
						 port->slave.phy_node,
						 &am65_cpsw_nuss_adjust_link,
						 0, port->slave.phy_अगर);
		अगर (!port->slave.phy) अणु
			dev_err(common->dev, "phy %pOF not found on slave %d\n",
				port->slave.phy_node,
				port->port_id);
			ret = -ENODEV;
			जाओ error_cleanup;
		पूर्ण
	पूर्ण

	/* restore vlan configurations */
	vlan_क्रम_each(ndev, cpsw_restore_vlans, port);

	phy_attached_info(port->slave.phy);
	phy_start(port->slave.phy);

	वापस 0;

error_cleanup:
	am65_cpsw_nuss_nकरो_slave_stop(ndev);
	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_nuss_rx_cleanup(व्योम *data, dma_addr_t desc_dma)
अणु
	काष्ठा am65_cpsw_rx_chn *rx_chn = data;
	काष्ठा cppi5_host_desc_t *desc_rx;
	काष्ठा sk_buff *skb;
	dma_addr_t buf_dma;
	u32 buf_dma_len;
	व्योम **swdata;

	desc_rx = k3_cppi_desc_pool_dma2virt(rx_chn->desc_pool, desc_dma);
	swdata = cppi5_hdesc_get_swdata(desc_rx);
	skb = *swdata;
	cppi5_hdesc_get_obuf(desc_rx, &buf_dma, &buf_dma_len);
	k3_udma_glue_rx_cppi5_to_dma_addr(rx_chn->rx_chn, &buf_dma);

	dma_unmap_single(rx_chn->dma_dev, buf_dma, buf_dma_len, DMA_FROM_DEVICE);
	k3_cppi_desc_pool_मुक्त(rx_chn->desc_pool, desc_rx);

	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल व्योम am65_cpsw_nuss_rx_ts(काष्ठा sk_buff *skb, u32 *psdata)
अणु
	काष्ठा skb_shared_hwtstamps *ssh;
	u64 ns;

	ns = ((u64)psdata[1] << 32) | psdata[0];

	ssh = skb_hwtstamps(skb);
	स_रखो(ssh, 0, माप(*ssh));
	ssh->hwtstamp = ns_to_kसमय(ns);
पूर्ण

/* RX psdata[2] word क्रमmat - checksum inक्रमmation */
#घोषणा AM65_CPSW_RX_PSD_CSUM_ADD	GENMASK(15, 0)
#घोषणा AM65_CPSW_RX_PSD_CSUM_ERR	BIT(16)
#घोषणा AM65_CPSW_RX_PSD_IS_FRAGMENT	BIT(17)
#घोषणा AM65_CPSW_RX_PSD_IS_TCP		BIT(18)
#घोषणा AM65_CPSW_RX_PSD_IPV6_VALID	BIT(19)
#घोषणा AM65_CPSW_RX_PSD_IPV4_VALID	BIT(20)

अटल व्योम am65_cpsw_nuss_rx_csum(काष्ठा sk_buff *skb, u32 csum_info)
अणु
	/* HW can verअगरy IPv4/IPv6 TCP/UDP packets checksum
	 * csum inक्रमmation provides in psdata[2] word:
	 * AM65_CPSW_RX_PSD_CSUM_ERR bit - indicates csum error
	 * AM65_CPSW_RX_PSD_IPV6_VALID and AM65_CPSW_RX_PSD_IPV4_VALID
	 * bits - indicates IPv4/IPv6 packet
	 * AM65_CPSW_RX_PSD_IS_FRAGMENT bit - indicates fragmented packet
	 * AM65_CPSW_RX_PSD_CSUM_ADD has value 0xFFFF क्रम non fragmented packets
	 * or csum value क्रम fragmented packets अगर !AM65_CPSW_RX_PSD_CSUM_ERR
	 */
	skb_checksum_none_निश्चित(skb);

	अगर (unlikely(!(skb->dev->features & NETIF_F_RXCSUM)))
		वापस;

	अगर ((csum_info & (AM65_CPSW_RX_PSD_IPV6_VALID |
			  AM65_CPSW_RX_PSD_IPV4_VALID)) &&
			  !(csum_info & AM65_CPSW_RX_PSD_CSUM_ERR)) अणु
		/* csum क्रम fragmented packets is unsupported */
		अगर (!(csum_info & AM65_CPSW_RX_PSD_IS_FRAGMENT))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_rx_packets(काष्ठा am65_cpsw_common *common,
				     u32 flow_idx)
अणु
	काष्ठा am65_cpsw_rx_chn *rx_chn = &common->rx_chns;
	u32 buf_dma_len, pkt_len, port_id = 0, csum_info;
	काष्ठा am65_cpsw_ndev_priv *ndev_priv;
	काष्ठा am65_cpsw_ndev_stats *stats;
	काष्ठा cppi5_host_desc_t *desc_rx;
	काष्ठा device *dev = common->dev;
	काष्ठा sk_buff *skb, *new_skb;
	dma_addr_t desc_dma, buf_dma;
	काष्ठा am65_cpsw_port *port;
	काष्ठा net_device *ndev;
	व्योम **swdata;
	u32 *psdata;
	पूर्णांक ret = 0;

	ret = k3_udma_glue_pop_rx_chn(rx_chn->rx_chn, flow_idx, &desc_dma);
	अगर (ret) अणु
		अगर (ret != -ENODATA)
			dev_err(dev, "RX: pop chn fail %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (cppi5_desc_is_tdcm(desc_dma)) अणु
		dev_dbg(dev, "%s RX tdown flow: %u\n", __func__, flow_idx);
		वापस 0;
	पूर्ण

	desc_rx = k3_cppi_desc_pool_dma2virt(rx_chn->desc_pool, desc_dma);
	dev_dbg(dev, "%s flow_idx: %u desc %pad\n",
		__func__, flow_idx, &desc_dma);

	swdata = cppi5_hdesc_get_swdata(desc_rx);
	skb = *swdata;
	cppi5_hdesc_get_obuf(desc_rx, &buf_dma, &buf_dma_len);
	k3_udma_glue_rx_cppi5_to_dma_addr(rx_chn->rx_chn, &buf_dma);
	pkt_len = cppi5_hdesc_get_pktlen(desc_rx);
	cppi5_desc_get_tags_ids(&desc_rx->hdr, &port_id, शून्य);
	dev_dbg(dev, "%s rx port_id:%d\n", __func__, port_id);
	port = am65_common_get_port(common, port_id);
	ndev = port->ndev;
	skb->dev = ndev;

	psdata = cppi5_hdesc_get_psdata(desc_rx);
	/* add RX बारtamp */
	अगर (port->rx_ts_enabled)
		am65_cpsw_nuss_rx_ts(skb, psdata);
	csum_info = psdata[2];
	dev_dbg(dev, "%s rx csum_info:%#x\n", __func__, csum_info);

	dma_unmap_single(rx_chn->dma_dev, buf_dma, buf_dma_len, DMA_FROM_DEVICE);

	k3_cppi_desc_pool_मुक्त(rx_chn->desc_pool, desc_rx);

	new_skb = netdev_alloc_skb_ip_align(ndev, AM65_CPSW_MAX_PACKET_SIZE);
	अगर (new_skb) अणु
		ndev_priv = netdev_priv(ndev);
		am65_cpsw_nuss_set_offload_fwd_mark(skb, ndev_priv->offload_fwd_mark);
		skb_put(skb, pkt_len);
		skb->protocol = eth_type_trans(skb, ndev);
		am65_cpsw_nuss_rx_csum(skb, csum_info);
		napi_gro_receive(&common->napi_rx, skb);

		stats = this_cpu_ptr(ndev_priv->stats);

		u64_stats_update_begin(&stats->syncp);
		stats->rx_packets++;
		stats->rx_bytes += pkt_len;
		u64_stats_update_end(&stats->syncp);
		kmemleak_not_leak(new_skb);
	पूर्ण अन्यथा अणु
		ndev->stats.rx_dropped++;
		new_skb = skb;
	पूर्ण

	अगर (netअगर_करोrmant(ndev)) अणु
		dev_kमुक्त_skb_any(new_skb);
		ndev->stats.rx_dropped++;
		वापस 0;
	पूर्ण

	ret = am65_cpsw_nuss_rx_push(common, new_skb);
	अगर (WARN_ON(ret < 0)) अणु
		dev_kमुक्त_skb_any(new_skb);
		ndev->stats.rx_errors++;
		ndev->stats.rx_dropped++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_rx_poll(काष्ठा napi_काष्ठा *napi_rx, पूर्णांक budget)
अणु
	काष्ठा am65_cpsw_common *common = am65_cpsw_napi_to_common(napi_rx);
	पूर्णांक flow = AM65_CPSW_MAX_RX_FLOWS;
	पूर्णांक cur_budget, ret;
	पूर्णांक num_rx = 0;

	/* process every flow */
	जबतक (flow--) अणु
		cur_budget = budget - num_rx;

		जबतक (cur_budget--) अणु
			ret = am65_cpsw_nuss_rx_packets(common, flow);
			अगर (ret)
				अवरोध;
			num_rx++;
		पूर्ण

		अगर (num_rx >= budget)
			अवरोध;
	पूर्ण

	dev_dbg(common->dev, "%s num_rx:%d %d\n", __func__, num_rx, budget);

	अगर (num_rx < budget && napi_complete_करोne(napi_rx, num_rx))
		enable_irq(common->rx_chns.irq);

	वापस num_rx;
पूर्ण

अटल व्योम am65_cpsw_nuss_xmit_मुक्त(काष्ठा am65_cpsw_tx_chn *tx_chn,
				     काष्ठा cppi5_host_desc_t *desc)
अणु
	काष्ठा cppi5_host_desc_t *first_desc, *next_desc;
	dma_addr_t buf_dma, next_desc_dma;
	u32 buf_dma_len;

	first_desc = desc;
	next_desc = first_desc;

	cppi5_hdesc_get_obuf(first_desc, &buf_dma, &buf_dma_len);
	k3_udma_glue_tx_cppi5_to_dma_addr(tx_chn->tx_chn, &buf_dma);

	dma_unmap_single(tx_chn->dma_dev, buf_dma, buf_dma_len, DMA_TO_DEVICE);

	next_desc_dma = cppi5_hdesc_get_next_hbdesc(first_desc);
	k3_udma_glue_tx_cppi5_to_dma_addr(tx_chn->tx_chn, &next_desc_dma);
	जबतक (next_desc_dma) अणु
		next_desc = k3_cppi_desc_pool_dma2virt(tx_chn->desc_pool,
						       next_desc_dma);
		cppi5_hdesc_get_obuf(next_desc, &buf_dma, &buf_dma_len);
		k3_udma_glue_tx_cppi5_to_dma_addr(tx_chn->tx_chn, &buf_dma);

		dma_unmap_page(tx_chn->dma_dev, buf_dma, buf_dma_len,
			       DMA_TO_DEVICE);

		next_desc_dma = cppi5_hdesc_get_next_hbdesc(next_desc);
		k3_udma_glue_tx_cppi5_to_dma_addr(tx_chn->tx_chn, &next_desc_dma);

		k3_cppi_desc_pool_मुक्त(tx_chn->desc_pool, next_desc);
	पूर्ण

	k3_cppi_desc_pool_मुक्त(tx_chn->desc_pool, first_desc);
पूर्ण

अटल व्योम am65_cpsw_nuss_tx_cleanup(व्योम *data, dma_addr_t desc_dma)
अणु
	काष्ठा am65_cpsw_tx_chn *tx_chn = data;
	काष्ठा cppi5_host_desc_t *desc_tx;
	काष्ठा sk_buff *skb;
	व्योम **swdata;

	desc_tx = k3_cppi_desc_pool_dma2virt(tx_chn->desc_pool, desc_dma);
	swdata = cppi5_hdesc_get_swdata(desc_tx);
	skb = *(swdata);
	am65_cpsw_nuss_xmit_मुक्त(tx_chn, desc_tx);

	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल काष्ठा sk_buff *
am65_cpsw_nuss_tx_compl_packet(काष्ठा am65_cpsw_tx_chn *tx_chn,
			       dma_addr_t desc_dma)
अणु
	काष्ठा am65_cpsw_ndev_priv *ndev_priv;
	काष्ठा am65_cpsw_ndev_stats *stats;
	काष्ठा cppi5_host_desc_t *desc_tx;
	काष्ठा net_device *ndev;
	काष्ठा sk_buff *skb;
	व्योम **swdata;

	desc_tx = k3_cppi_desc_pool_dma2virt(tx_chn->desc_pool,
					     desc_dma);
	swdata = cppi5_hdesc_get_swdata(desc_tx);
	skb = *(swdata);
	am65_cpsw_nuss_xmit_मुक्त(tx_chn, desc_tx);

	ndev = skb->dev;

	am65_cpts_tx_बारtamp(tx_chn->common->cpts, skb);

	ndev_priv = netdev_priv(ndev);
	stats = this_cpu_ptr(ndev_priv->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->tx_packets++;
	stats->tx_bytes += skb->len;
	u64_stats_update_end(&stats->syncp);

	वापस skb;
पूर्ण

अटल व्योम am65_cpsw_nuss_tx_wake(काष्ठा am65_cpsw_tx_chn *tx_chn, काष्ठा net_device *ndev,
				   काष्ठा netdev_queue *netअगर_txq)
अणु
	अगर (netअगर_tx_queue_stopped(netअगर_txq)) अणु
		/* Check whether the queue is stopped due to stalled
		 * tx dma, अगर the queue is stopped then wake the queue
		 * as we have मुक्त desc क्रम tx
		 */
		__netअगर_tx_lock(netअगर_txq, smp_processor_id());
		अगर (netअगर_running(ndev) &&
		    (k3_cppi_desc_pool_avail(tx_chn->desc_pool) >= MAX_SKB_FRAGS))
			netअगर_tx_wake_queue(netअगर_txq);

		__netअगर_tx_unlock(netअगर_txq);
	पूर्ण
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_tx_compl_packets(काष्ठा am65_cpsw_common *common,
					   पूर्णांक chn, अचिन्हित पूर्णांक budget)
अणु
	काष्ठा device *dev = common->dev;
	काष्ठा am65_cpsw_tx_chn *tx_chn;
	काष्ठा netdev_queue *netअगर_txq;
	अचिन्हित पूर्णांक total_bytes = 0;
	काष्ठा net_device *ndev;
	काष्ठा sk_buff *skb;
	dma_addr_t desc_dma;
	पूर्णांक res, num_tx = 0;

	tx_chn = &common->tx_chns[chn];

	जबतक (true) अणु
		spin_lock(&tx_chn->lock);
		res = k3_udma_glue_pop_tx_chn(tx_chn->tx_chn, &desc_dma);
		spin_unlock(&tx_chn->lock);
		अगर (res == -ENODATA)
			अवरोध;

		अगर (cppi5_desc_is_tdcm(desc_dma)) अणु
			अगर (atomic_dec_and_test(&common->tकरोwn_cnt))
				complete(&common->tकरोwn_complete);
			अवरोध;
		पूर्ण

		skb = am65_cpsw_nuss_tx_compl_packet(tx_chn, desc_dma);
		total_bytes = skb->len;
		ndev = skb->dev;
		napi_consume_skb(skb, budget);
		num_tx++;

		netअगर_txq = netdev_get_tx_queue(ndev, chn);

		netdev_tx_completed_queue(netअगर_txq, num_tx, total_bytes);

		am65_cpsw_nuss_tx_wake(tx_chn, ndev, netअगर_txq);
	पूर्ण

	dev_dbg(dev, "%s:%u pkt:%d\n", __func__, chn, num_tx);

	वापस num_tx;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_tx_compl_packets_2g(काष्ठा am65_cpsw_common *common,
					      पूर्णांक chn, अचिन्हित पूर्णांक budget)
अणु
	काष्ठा device *dev = common->dev;
	काष्ठा am65_cpsw_tx_chn *tx_chn;
	काष्ठा netdev_queue *netअगर_txq;
	अचिन्हित पूर्णांक total_bytes = 0;
	काष्ठा net_device *ndev;
	काष्ठा sk_buff *skb;
	dma_addr_t desc_dma;
	पूर्णांक res, num_tx = 0;

	tx_chn = &common->tx_chns[chn];

	जबतक (true) अणु
		res = k3_udma_glue_pop_tx_chn(tx_chn->tx_chn, &desc_dma);
		अगर (res == -ENODATA)
			अवरोध;

		अगर (cppi5_desc_is_tdcm(desc_dma)) अणु
			अगर (atomic_dec_and_test(&common->tकरोwn_cnt))
				complete(&common->tकरोwn_complete);
			अवरोध;
		पूर्ण

		skb = am65_cpsw_nuss_tx_compl_packet(tx_chn, desc_dma);

		ndev = skb->dev;
		total_bytes += skb->len;
		napi_consume_skb(skb, budget);
		num_tx++;
	पूर्ण

	अगर (!num_tx)
		वापस 0;

	netअगर_txq = netdev_get_tx_queue(ndev, chn);

	netdev_tx_completed_queue(netअगर_txq, num_tx, total_bytes);

	am65_cpsw_nuss_tx_wake(tx_chn, ndev, netअगर_txq);

	dev_dbg(dev, "%s:%u pkt:%d\n", __func__, chn, num_tx);

	वापस num_tx;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_tx_poll(काष्ठा napi_काष्ठा *napi_tx, पूर्णांक budget)
अणु
	काष्ठा am65_cpsw_tx_chn *tx_chn = am65_cpsw_napi_to_tx_chn(napi_tx);
	पूर्णांक num_tx;

	अगर (AM65_CPSW_IS_CPSW2G(tx_chn->common))
		num_tx = am65_cpsw_nuss_tx_compl_packets_2g(tx_chn->common, tx_chn->id, budget);
	अन्यथा
		num_tx = am65_cpsw_nuss_tx_compl_packets(tx_chn->common, tx_chn->id, budget);

	num_tx = min(num_tx, budget);
	अगर (num_tx < budget) अणु
		napi_complete(napi_tx);
		enable_irq(tx_chn->irq);
	पूर्ण

	वापस num_tx;
पूर्ण

अटल irqवापस_t am65_cpsw_nuss_rx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा am65_cpsw_common *common = dev_id;

	disable_irq_nosync(irq);
	napi_schedule(&common->napi_rx);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t am65_cpsw_nuss_tx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा am65_cpsw_tx_chn *tx_chn = dev_id;

	disable_irq_nosync(irq);
	napi_schedule(&tx_chn->napi_tx);

	वापस IRQ_HANDLED;
पूर्ण

अटल netdev_tx_t am65_cpsw_nuss_nकरो_slave_xmit(काष्ठा sk_buff *skb,
						 काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा cppi5_host_desc_t *first_desc, *next_desc, *cur_desc;
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा device *dev = common->dev;
	काष्ठा am65_cpsw_tx_chn *tx_chn;
	काष्ठा netdev_queue *netअगर_txq;
	dma_addr_t desc_dma, buf_dma;
	पूर्णांक ret, q_idx, i;
	व्योम **swdata;
	u32 *psdata;
	u32 pkt_len;

	/* padding enabled in hw */
	pkt_len = skb_headlen(skb);

	/* SKB TX बारtamp */
	अगर (port->tx_ts_enabled)
		am65_cpts_prep_tx_बारtamp(common->cpts, skb);

	q_idx = skb_get_queue_mapping(skb);
	dev_dbg(dev, "%s skb_queue:%d\n", __func__, q_idx);

	tx_chn = &common->tx_chns[q_idx];
	netअगर_txq = netdev_get_tx_queue(ndev, q_idx);

	/* Map the linear buffer */
	buf_dma = dma_map_single(tx_chn->dma_dev, skb->data, pkt_len,
				 DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(tx_chn->dma_dev, buf_dma))) अणु
		dev_err(dev, "Failed to map tx skb buffer\n");
		ndev->stats.tx_errors++;
		जाओ err_मुक्त_skb;
	पूर्ण

	first_desc = k3_cppi_desc_pool_alloc(tx_chn->desc_pool);
	अगर (!first_desc) अणु
		dev_dbg(dev, "Failed to allocate descriptor\n");
		dma_unmap_single(tx_chn->dma_dev, buf_dma, pkt_len,
				 DMA_TO_DEVICE);
		जाओ busy_stop_q;
	पूर्ण

	cppi5_hdesc_init(first_desc, CPPI5_INFO0_HDESC_EPIB_PRESENT,
			 AM65_CPSW_NAV_PS_DATA_SIZE);
	cppi5_desc_set_pktids(&first_desc->hdr, 0, 0x3FFF);
	cppi5_hdesc_set_pkttype(first_desc, 0x7);
	cppi5_desc_set_tags_ids(&first_desc->hdr, 0, port->port_id);

	k3_udma_glue_tx_dma_to_cppi5_addr(tx_chn->tx_chn, &buf_dma);
	cppi5_hdesc_attach_buf(first_desc, buf_dma, pkt_len, buf_dma, pkt_len);
	swdata = cppi5_hdesc_get_swdata(first_desc);
	*(swdata) = skb;
	psdata = cppi5_hdesc_get_psdata(first_desc);

	/* HW csum offload अगर enabled */
	psdata[2] = 0;
	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		अचिन्हित पूर्णांक cs_start, cs_offset;

		cs_start = skb_transport_offset(skb);
		cs_offset = cs_start + skb->csum_offset;
		/* HW numerates bytes starting from 1 */
		psdata[2] = ((cs_offset + 1) << 24) |
			    ((cs_start + 1) << 16) | (skb->len - cs_start);
		dev_dbg(dev, "%s tx psdata:%#x\n", __func__, psdata[2]);
	पूर्ण

	अगर (!skb_is_nonlinear(skb))
		जाओ करोne_tx;

	dev_dbg(dev, "fragmented SKB\n");

	/* Handle the हाल where skb is fragmented in pages */
	cur_desc = first_desc;
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		u32 frag_size = skb_frag_size(frag);

		next_desc = k3_cppi_desc_pool_alloc(tx_chn->desc_pool);
		अगर (!next_desc) अणु
			dev_err(dev, "Failed to allocate descriptor\n");
			जाओ busy_मुक्त_descs;
		पूर्ण

		buf_dma = skb_frag_dma_map(tx_chn->dma_dev, frag, 0, frag_size,
					   DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(tx_chn->dma_dev, buf_dma))) अणु
			dev_err(dev, "Failed to map tx skb page\n");
			k3_cppi_desc_pool_मुक्त(tx_chn->desc_pool, next_desc);
			ndev->stats.tx_errors++;
			जाओ err_मुक्त_descs;
		पूर्ण

		cppi5_hdesc_reset_hbdesc(next_desc);
		k3_udma_glue_tx_dma_to_cppi5_addr(tx_chn->tx_chn, &buf_dma);
		cppi5_hdesc_attach_buf(next_desc,
				       buf_dma, frag_size, buf_dma, frag_size);

		desc_dma = k3_cppi_desc_pool_virt2dma(tx_chn->desc_pool,
						      next_desc);
		k3_udma_glue_tx_dma_to_cppi5_addr(tx_chn->tx_chn, &desc_dma);
		cppi5_hdesc_link_hbdesc(cur_desc, desc_dma);

		pkt_len += frag_size;
		cur_desc = next_desc;
	पूर्ण
	WARN_ON(pkt_len != skb->len);

करोne_tx:
	skb_tx_बारtamp(skb);

	/* report bql beक्रमe sending packet */
	netdev_tx_sent_queue(netअगर_txq, pkt_len);

	cppi5_hdesc_set_pktlen(first_desc, pkt_len);
	desc_dma = k3_cppi_desc_pool_virt2dma(tx_chn->desc_pool, first_desc);
	अगर (AM65_CPSW_IS_CPSW2G(common)) अणु
		ret = k3_udma_glue_push_tx_chn(tx_chn->tx_chn, first_desc, desc_dma);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&tx_chn->lock);
		ret = k3_udma_glue_push_tx_chn(tx_chn->tx_chn, first_desc, desc_dma);
		spin_unlock_bh(&tx_chn->lock);
	पूर्ण
	अगर (ret) अणु
		dev_err(dev, "can't push desc %d\n", ret);
		/* inक्रमm bql */
		netdev_tx_completed_queue(netअगर_txq, 1, pkt_len);
		ndev->stats.tx_errors++;
		जाओ err_मुक्त_descs;
	पूर्ण

	अगर (k3_cppi_desc_pool_avail(tx_chn->desc_pool) < MAX_SKB_FRAGS) अणु
		netअगर_tx_stop_queue(netअगर_txq);
		/* Barrier, so that stop_queue visible to other cpus */
		smp_mb__after_atomic();
		dev_dbg(dev, "netif_tx_stop_queue %d\n", q_idx);

		/* re-check क्रम smp */
		अगर (k3_cppi_desc_pool_avail(tx_chn->desc_pool) >=
		    MAX_SKB_FRAGS) अणु
			netअगर_tx_wake_queue(netअगर_txq);
			dev_dbg(dev, "netif_tx_wake_queue %d\n", q_idx);
		पूर्ण
	पूर्ण

	वापस NETDEV_TX_OK;

err_मुक्त_descs:
	am65_cpsw_nuss_xmit_मुक्त(tx_chn, first_desc);
err_मुक्त_skb:
	ndev->stats.tx_dropped++;
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;

busy_मुक्त_descs:
	am65_cpsw_nuss_xmit_मुक्त(tx_chn, first_desc);
busy_stop_q:
	netअगर_tx_stop_queue(netअगर_txq);
	वापस NETDEV_TX_BUSY;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_nकरो_slave_set_mac_address(काष्ठा net_device *ndev,
						    व्योम *addr)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा sockaddr *sockaddr = (काष्ठा sockaddr *)addr;
	पूर्णांक ret;

	ret = eth_prepare_mac_addr_change(ndev, addr);
	अगर (ret < 0)
		वापस ret;

	ret = pm_runसमय_get_sync(common->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(common->dev);
		वापस ret;
	पूर्ण

	cpsw_ale_del_ucast(common->ale, ndev->dev_addr,
			   HOST_PORT_NUM, 0, 0);
	cpsw_ale_add_ucast(common->ale, sockaddr->sa_data,
			   HOST_PORT_NUM, ALE_SECURE, 0);

	am65_cpsw_port_set_sl_mac(port, addr);
	eth_commit_mac_addr_change(ndev, sockaddr);

	pm_runसमय_put(common->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_hwtstamp_set(काष्ठा net_device *ndev,
				       काष्ठा अगरreq *अगरr)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	u32 ts_ctrl, seq_id, ts_ctrl_ltype2, ts_vlan_ltype;
	काष्ठा hwtstamp_config cfg;

	अगर (!IS_ENABLED(CONFIG_TI_K3_AM65_CPTS))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	/* TX HW बारtamp */
	चयन (cfg.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		port->rx_ts_enabled = false;
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		port->rx_ts_enabled = true;
		cfg.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	port->tx_ts_enabled = (cfg.tx_type == HWTSTAMP_TX_ON);

	/* cfg TX बारtamp */
	seq_id = (AM65_CPSW_TS_SEQ_ID_OFFSET <<
		  AM65_CPSW_PN_TS_SEQ_ID_OFFSET_SHIFT) | ETH_P_1588;

	ts_vlan_ltype = ETH_P_8021Q;

	ts_ctrl_ltype2 = ETH_P_1588 |
			 AM65_CPSW_PN_TS_CTL_LTYPE2_TS_107 |
			 AM65_CPSW_PN_TS_CTL_LTYPE2_TS_129 |
			 AM65_CPSW_PN_TS_CTL_LTYPE2_TS_130 |
			 AM65_CPSW_PN_TS_CTL_LTYPE2_TS_131 |
			 AM65_CPSW_PN_TS_CTL_LTYPE2_TS_132 |
			 AM65_CPSW_PN_TS_CTL_LTYPE2_TS_319 |
			 AM65_CPSW_PN_TS_CTL_LTYPE2_TS_320 |
			 AM65_CPSW_PN_TS_CTL_LTYPE2_TS_TTL_NONZERO;

	ts_ctrl = AM65_CPSW_TS_EVENT_MSG_TYPE_BITS <<
		  AM65_CPSW_PN_TS_CTL_MSG_TYPE_EN_SHIFT;

	अगर (port->tx_ts_enabled)
		ts_ctrl |= AM65_CPSW_TS_TX_ANX_ALL_EN |
			   AM65_CPSW_PN_TS_CTL_TX_VLAN_LT1_EN;

	ग_लिखोl(seq_id, port->port_base + AM65_CPSW_PORTN_REG_TS_SEQ_LTYPE_REG);
	ग_लिखोl(ts_vlan_ltype, port->port_base +
	       AM65_CPSW_PORTN_REG_TS_VLAN_LTYPE_REG);
	ग_लिखोl(ts_ctrl_ltype2, port->port_base +
	       AM65_CPSW_PORTN_REG_TS_CTL_LTYPE2);
	ग_लिखोl(ts_ctrl, port->port_base + AM65_CPSW_PORTN_REG_TS_CTL);

	/* en/dis RX बारtamp */
	am65_cpts_rx_enable(common->cpts, port->rx_ts_enabled);

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_hwtstamp_get(काष्ठा net_device *ndev,
				       काष्ठा अगरreq *अगरr)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा hwtstamp_config cfg;

	अगर (!IS_ENABLED(CONFIG_TI_K3_AM65_CPTS))
		वापस -EOPNOTSUPP;

	cfg.flags = 0;
	cfg.tx_type = port->tx_ts_enabled ?
		      HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	cfg.rx_filter = port->rx_ts_enabled ?
			HWTSTAMP_FILTER_ALL : HWTSTAMP_FILTER_NONE;

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_nकरो_slave_ioctl(काष्ठा net_device *ndev,
					  काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);

	अगर (!netअगर_running(ndev))
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस am65_cpsw_nuss_hwtstamp_set(ndev, req);
	हाल SIOCGHWTSTAMP:
		वापस am65_cpsw_nuss_hwtstamp_get(ndev, req);
	पूर्ण

	अगर (!port->slave.phy)
		वापस -EOPNOTSUPP;

	वापस phy_mii_ioctl(port->slave.phy, req, cmd);
पूर्ण

अटल व्योम am65_cpsw_nuss_nकरो_get_stats(काष्ठा net_device *dev,
					 काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा am65_cpsw_ndev_priv *ndev_priv = netdev_priv(dev);
	अचिन्हित पूर्णांक start;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा am65_cpsw_ndev_stats *cpu_stats;
		u64 rx_packets;
		u64 rx_bytes;
		u64 tx_packets;
		u64 tx_bytes;

		cpu_stats = per_cpu_ptr(ndev_priv->stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			rx_packets = cpu_stats->rx_packets;
			rx_bytes   = cpu_stats->rx_bytes;
			tx_packets = cpu_stats->tx_packets;
			tx_bytes   = cpu_stats->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		stats->rx_packets += rx_packets;
		stats->rx_bytes   += rx_bytes;
		stats->tx_packets += tx_packets;
		stats->tx_bytes   += tx_bytes;
	पूर्ण

	stats->rx_errors	= dev->stats.rx_errors;
	stats->rx_dropped	= dev->stats.rx_dropped;
	stats->tx_dropped	= dev->stats.tx_dropped;
पूर्ण

अटल काष्ठा devlink_port *am65_cpsw_nकरो_get_devlink_port(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);

	वापस &port->devlink_port;
पूर्ण

अटल स्थिर काष्ठा net_device_ops am65_cpsw_nuss_netdev_ops = अणु
	.nकरो_खोलो		= am65_cpsw_nuss_nकरो_slave_खोलो,
	.nकरो_stop		= am65_cpsw_nuss_nकरो_slave_stop,
	.nकरो_start_xmit		= am65_cpsw_nuss_nकरो_slave_xmit,
	.nकरो_set_rx_mode	= am65_cpsw_nuss_nकरो_slave_set_rx_mode,
	.nकरो_get_stats64        = am65_cpsw_nuss_nकरो_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= am65_cpsw_nuss_nकरो_slave_set_mac_address,
	.nकरो_tx_समयout		= am65_cpsw_nuss_nकरो_host_tx_समयout,
	.nकरो_vlan_rx_add_vid	= am65_cpsw_nuss_nकरो_slave_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= am65_cpsw_nuss_nकरो_slave_समाप्त_vid,
	.nकरो_करो_ioctl		= am65_cpsw_nuss_nकरो_slave_ioctl,
	.nकरो_setup_tc           = am65_cpsw_qos_nकरो_setup_tc,
	.nकरो_get_devlink_port   = am65_cpsw_nकरो_get_devlink_port,
पूर्ण;

अटल व्योम am65_cpsw_nuss_slave_disable_unused(काष्ठा am65_cpsw_port *port)
अणु
	काष्ठा am65_cpsw_common *common = port->common;

	अगर (!port->disabled)
		वापस;

	cpsw_ale_control_set(common->ale, port->port_id,
			     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);

	cpsw_sl_reset(port->slave.mac_sl, 100);
	cpsw_sl_ctl_reset(port->slave.mac_sl);
पूर्ण

अटल व्योम am65_cpsw_nuss_मुक्त_tx_chns(व्योम *data)
अणु
	काष्ठा am65_cpsw_common *common = data;
	पूर्णांक i;

	क्रम (i = 0; i < common->tx_ch_num; i++) अणु
		काष्ठा am65_cpsw_tx_chn *tx_chn = &common->tx_chns[i];

		अगर (!IS_ERR_OR_शून्य(tx_chn->tx_chn))
			k3_udma_glue_release_tx_chn(tx_chn->tx_chn);

		अगर (!IS_ERR_OR_शून्य(tx_chn->desc_pool))
			k3_cppi_desc_pool_destroy(tx_chn->desc_pool);

		स_रखो(tx_chn, 0, माप(*tx_chn));
	पूर्ण
पूर्ण

व्योम am65_cpsw_nuss_हटाओ_tx_chns(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा device *dev = common->dev;
	पूर्णांक i;

	devm_हटाओ_action(dev, am65_cpsw_nuss_मुक्त_tx_chns, common);

	क्रम (i = 0; i < common->tx_ch_num; i++) अणु
		काष्ठा am65_cpsw_tx_chn *tx_chn = &common->tx_chns[i];

		अगर (tx_chn->irq)
			devm_मुक्त_irq(dev, tx_chn->irq, tx_chn);

		netअगर_napi_del(&tx_chn->napi_tx);

		अगर (!IS_ERR_OR_शून्य(tx_chn->tx_chn))
			k3_udma_glue_release_tx_chn(tx_chn->tx_chn);

		अगर (!IS_ERR_OR_शून्य(tx_chn->desc_pool))
			k3_cppi_desc_pool_destroy(tx_chn->desc_pool);

		स_रखो(tx_chn, 0, माप(*tx_chn));
	पूर्ण
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_init_tx_chns(काष्ठा am65_cpsw_common *common)
अणु
	u32  max_desc_num = ALIGN(AM65_CPSW_MAX_TX_DESC, MAX_SKB_FRAGS);
	काष्ठा k3_udma_glue_tx_channel_cfg tx_cfg = अणु 0 पूर्ण;
	काष्ठा device *dev = common->dev;
	काष्ठा k3_ring_cfg ring_cfg = अणु
		.elm_size = K3_RINGACC_RING_ELSIZE_8,
		.mode = K3_RINGACC_RING_MODE_RING,
		.flags = 0
	पूर्ण;
	u32 hdesc_size;
	पूर्णांक i, ret = 0;

	hdesc_size = cppi5_hdesc_calc_size(true, AM65_CPSW_NAV_PS_DATA_SIZE,
					   AM65_CPSW_NAV_SW_DATA_SIZE);

	tx_cfg.swdata_size = AM65_CPSW_NAV_SW_DATA_SIZE;
	tx_cfg.tx_cfg = ring_cfg;
	tx_cfg.txcq_cfg = ring_cfg;
	tx_cfg.tx_cfg.size = max_desc_num;
	tx_cfg.txcq_cfg.size = max_desc_num;

	क्रम (i = 0; i < common->tx_ch_num; i++) अणु
		काष्ठा am65_cpsw_tx_chn *tx_chn = &common->tx_chns[i];

		snम_लिखो(tx_chn->tx_chn_name,
			 माप(tx_chn->tx_chn_name), "tx%d", i);

		spin_lock_init(&tx_chn->lock);
		tx_chn->common = common;
		tx_chn->id = i;
		tx_chn->descs_num = max_desc_num;

		tx_chn->tx_chn =
			k3_udma_glue_request_tx_chn(dev,
						    tx_chn->tx_chn_name,
						    &tx_cfg);
		अगर (IS_ERR(tx_chn->tx_chn)) अणु
			ret = dev_err_probe(dev, PTR_ERR(tx_chn->tx_chn),
					    "Failed to request tx dma channel\n");
			जाओ err;
		पूर्ण
		tx_chn->dma_dev = k3_udma_glue_tx_get_dma_device(tx_chn->tx_chn);

		tx_chn->desc_pool = k3_cppi_desc_pool_create_name(tx_chn->dma_dev,
								  tx_chn->descs_num,
								  hdesc_size,
								  tx_chn->tx_chn_name);
		अगर (IS_ERR(tx_chn->desc_pool)) अणु
			ret = PTR_ERR(tx_chn->desc_pool);
			dev_err(dev, "Failed to create poll %d\n", ret);
			जाओ err;
		पूर्ण

		tx_chn->irq = k3_udma_glue_tx_get_irq(tx_chn->tx_chn);
		अगर (tx_chn->irq <= 0) अणु
			dev_err(dev, "Failed to get tx dma irq %d\n",
				tx_chn->irq);
			जाओ err;
		पूर्ण

		snम_लिखो(tx_chn->tx_chn_name,
			 माप(tx_chn->tx_chn_name), "%s-tx%d",
			 dev_name(dev), tx_chn->id);
	पूर्ण

err:
	i = devm_add_action(dev, am65_cpsw_nuss_मुक्त_tx_chns, common);
	अगर (i) अणु
		dev_err(dev, "Failed to add free_tx_chns action %d\n", i);
		वापस i;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_nuss_मुक्त_rx_chns(व्योम *data)
अणु
	काष्ठा am65_cpsw_common *common = data;
	काष्ठा am65_cpsw_rx_chn *rx_chn;

	rx_chn = &common->rx_chns;

	अगर (!IS_ERR_OR_शून्य(rx_chn->rx_chn))
		k3_udma_glue_release_rx_chn(rx_chn->rx_chn);

	अगर (!IS_ERR_OR_शून्य(rx_chn->desc_pool))
		k3_cppi_desc_pool_destroy(rx_chn->desc_pool);
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_init_rx_chns(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा am65_cpsw_rx_chn *rx_chn = &common->rx_chns;
	काष्ठा k3_udma_glue_rx_channel_cfg rx_cfg = अणु 0 पूर्ण;
	u32  max_desc_num = AM65_CPSW_MAX_RX_DESC;
	काष्ठा device *dev = common->dev;
	u32 hdesc_size;
	u32 fdqring_id;
	पूर्णांक i, ret = 0;

	hdesc_size = cppi5_hdesc_calc_size(true, AM65_CPSW_NAV_PS_DATA_SIZE,
					   AM65_CPSW_NAV_SW_DATA_SIZE);

	rx_cfg.swdata_size = AM65_CPSW_NAV_SW_DATA_SIZE;
	rx_cfg.flow_id_num = AM65_CPSW_MAX_RX_FLOWS;
	rx_cfg.flow_id_base = common->rx_flow_id_base;

	/* init all flows */
	rx_chn->dev = dev;
	rx_chn->descs_num = max_desc_num;

	rx_chn->rx_chn = k3_udma_glue_request_rx_chn(dev, "rx", &rx_cfg);
	अगर (IS_ERR(rx_chn->rx_chn)) अणु
		ret = dev_err_probe(dev, PTR_ERR(rx_chn->rx_chn),
				    "Failed to request rx dma channel\n");
		जाओ err;
	पूर्ण
	rx_chn->dma_dev = k3_udma_glue_rx_get_dma_device(rx_chn->rx_chn);

	rx_chn->desc_pool = k3_cppi_desc_pool_create_name(rx_chn->dma_dev,
							  rx_chn->descs_num,
							  hdesc_size, "rx");
	अगर (IS_ERR(rx_chn->desc_pool)) अणु
		ret = PTR_ERR(rx_chn->desc_pool);
		dev_err(dev, "Failed to create rx poll %d\n", ret);
		जाओ err;
	पूर्ण

	common->rx_flow_id_base =
			k3_udma_glue_rx_get_flow_id_base(rx_chn->rx_chn);
	dev_info(dev, "set new flow-id-base %u\n", common->rx_flow_id_base);

	fdqring_id = K3_RINGACC_RING_ID_ANY;
	क्रम (i = 0; i < rx_cfg.flow_id_num; i++) अणु
		काष्ठा k3_ring_cfg rxring_cfg = अणु
			.elm_size = K3_RINGACC_RING_ELSIZE_8,
			.mode = K3_RINGACC_RING_MODE_RING,
			.flags = 0,
		पूर्ण;
		काष्ठा k3_ring_cfg fdqring_cfg = अणु
			.elm_size = K3_RINGACC_RING_ELSIZE_8,
			.flags = K3_RINGACC_RING_SHARED,
		पूर्ण;
		काष्ठा k3_udma_glue_rx_flow_cfg rx_flow_cfg = अणु
			.rx_cfg = rxring_cfg,
			.rxfdq_cfg = fdqring_cfg,
			.ring_rxq_id = K3_RINGACC_RING_ID_ANY,
			.src_tag_lo_sel =
				K3_UDMA_GLUE_SRC_TAG_LO_USE_REMOTE_SRC_TAG,
		पूर्ण;

		rx_flow_cfg.ring_rxfdq0_id = fdqring_id;
		rx_flow_cfg.rx_cfg.size = max_desc_num;
		rx_flow_cfg.rxfdq_cfg.size = max_desc_num;
		rx_flow_cfg.rxfdq_cfg.mode = common->pdata.fdqring_mode;

		ret = k3_udma_glue_rx_flow_init(rx_chn->rx_chn,
						i, &rx_flow_cfg);
		अगर (ret) अणु
			dev_err(dev, "Failed to init rx flow%d %d\n", i, ret);
			जाओ err;
		पूर्ण
		अगर (!i)
			fdqring_id =
				k3_udma_glue_rx_flow_get_fdq_id(rx_chn->rx_chn,
								i);

		rx_chn->irq = k3_udma_glue_rx_get_irq(rx_chn->rx_chn, i);

		अगर (rx_chn->irq <= 0) अणु
			dev_err(dev, "Failed to get rx dma irq %d\n",
				rx_chn->irq);
			ret = -ENXIO;
			जाओ err;
		पूर्ण
	पूर्ण

err:
	i = devm_add_action(dev, am65_cpsw_nuss_मुक्त_rx_chns, common);
	अगर (i) अणु
		dev_err(dev, "Failed to add free_rx_chns action %d\n", i);
		वापस i;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_init_host_p(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा am65_cpsw_host *host_p = am65_common_get_host(common);

	host_p->common = common;
	host_p->port_base = common->cpsw_base + AM65_CPSW_NU_PORTS_BASE;
	host_p->stat_base = common->cpsw_base + AM65_CPSW_NU_STATS_BASE;

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpsw_am654_get_efuse_macid(काष्ठा device_node *of_node,
					   पूर्णांक slave, u8 *mac_addr)
अणु
	u32 mac_lo, mac_hi, offset;
	काष्ठा regmap *syscon;
	पूर्णांक ret;

	syscon = syscon_regmap_lookup_by_phandle(of_node, "ti,syscon-efuse");
	अगर (IS_ERR(syscon)) अणु
		अगर (PTR_ERR(syscon) == -ENODEV)
			वापस 0;
		वापस PTR_ERR(syscon);
	पूर्ण

	ret = of_property_पढ़ो_u32_index(of_node, "ti,syscon-efuse", 1,
					 &offset);
	अगर (ret)
		वापस ret;

	regmap_पढ़ो(syscon, offset, &mac_lo);
	regmap_पढ़ो(syscon, offset + 4, &mac_hi);

	mac_addr[0] = (mac_hi >> 8) & 0xff;
	mac_addr[1] = mac_hi & 0xff;
	mac_addr[2] = (mac_lo >> 24) & 0xff;
	mac_addr[3] = (mac_lo >> 16) & 0xff;
	mac_addr[4] = (mac_lo >> 8) & 0xff;
	mac_addr[5] = mac_lo & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpsw_init_cpts(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा device *dev = common->dev;
	काष्ठा device_node *node;
	काष्ठा am65_cpts *cpts;
	व्योम __iomem *reg_base;

	अगर (!IS_ENABLED(CONFIG_TI_K3_AM65_CPTS))
		वापस 0;

	node = of_get_child_by_name(dev->of_node, "cpts");
	अगर (!node) अणु
		dev_err(dev, "%s cpts not found\n", __func__);
		वापस -ENOENT;
	पूर्ण

	reg_base = common->cpsw_base + AM65_CPSW_NU_CPTS_BASE;
	cpts = am65_cpts_create(dev, reg_base, node);
	अगर (IS_ERR(cpts)) अणु
		पूर्णांक ret = PTR_ERR(cpts);

		अगर (ret == -EOPNOTSUPP) अणु
			dev_info(dev, "cpts disabled\n");
			वापस 0;
		पूर्ण

		dev_err(dev, "cpts create err %d\n", ret);
		वापस ret;
	पूर्ण
	common->cpts = cpts;
	/* Forbid PM runसमय अगर CPTS is running.
	 * K3 CPSWxG modules may completely lose context during ON->OFF
	 * transitions depending on पूर्णांकegration.
	 * AM65x/J721E MCU CPSW2G: false
	 * J721E MAIN_CPSW9G: true
	 */
	pm_runसमय_क्रमbid(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_init_slave_ports(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा device_node *node, *port_np;
	काष्ठा device *dev = common->dev;
	पूर्णांक ret;

	node = of_get_child_by_name(dev->of_node, "ethernet-ports");
	अगर (!node)
		वापस -ENOENT;

	क्रम_each_child_of_node(node, port_np) अणु
		काष्ठा am65_cpsw_port *port;
		u32 port_id;

		/* it is not a slave port node, जारी */
		अगर (म_भेद(port_np->name, "port"))
			जारी;

		ret = of_property_पढ़ो_u32(port_np, "reg", &port_id);
		अगर (ret < 0) अणु
			dev_err(dev, "%pOF error reading port_id %d\n",
				port_np, ret);
			वापस ret;
		पूर्ण

		अगर (!port_id || port_id > common->port_num) अणु
			dev_err(dev, "%pOF has invalid port_id %u %s\n",
				port_np, port_id, port_np->name);
			वापस -EINVAL;
		पूर्ण

		port = am65_common_get_port(common, port_id);
		port->port_id = port_id;
		port->common = common;
		port->port_base = common->cpsw_base + AM65_CPSW_NU_PORTS_BASE +
				  AM65_CPSW_NU_PORTS_OFFSET * (port_id);
		port->stat_base = common->cpsw_base + AM65_CPSW_NU_STATS_BASE +
				  (AM65_CPSW_NU_STATS_PORT_OFFSET * port_id);
		port->name = of_get_property(port_np, "label", शून्य);
		port->fetch_ram_base =
				common->cpsw_base + AM65_CPSW_NU_FRAM_BASE +
				(AM65_CPSW_NU_FRAM_PORT_OFFSET * (port_id - 1));

		port->slave.mac_sl = cpsw_sl_get("am65", dev, port->port_base);
		अगर (IS_ERR(port->slave.mac_sl))
			वापस PTR_ERR(port->slave.mac_sl);

		port->disabled = !of_device_is_available(port_np);
		अगर (port->disabled) अणु
			common->disabled_ports_mask |= BIT(port->port_id);
			जारी;
		पूर्ण

		port->slave.अगरphy = devm_of_phy_get(dev, port_np, शून्य);
		अगर (IS_ERR(port->slave.अगरphy)) अणु
			ret = PTR_ERR(port->slave.अगरphy);
			dev_err(dev, "%pOF error retrieving port phy: %d\n",
				port_np, ret);
			वापस ret;
		पूर्ण

		port->slave.mac_only =
				of_property_पढ़ो_bool(port_np, "ti,mac-only");

		/* get phy/link info */
		अगर (of_phy_is_fixed_link(port_np)) अणु
			ret = of_phy_रेजिस्टर_fixed_link(port_np);
			अगर (ret)
				वापस dev_err_probe(dev, ret,
						     "failed to register fixed-link phy %pOF\n",
						     port_np);
			port->slave.phy_node = of_node_get(port_np);
		पूर्ण अन्यथा अणु
			port->slave.phy_node =
				of_parse_phandle(port_np, "phy-handle", 0);
		पूर्ण

		अगर (!port->slave.phy_node) अणु
			dev_err(dev,
				"slave[%d] no phy found\n", port_id);
			वापस -ENODEV;
		पूर्ण

		ret = of_get_phy_mode(port_np, &port->slave.phy_अगर);
		अगर (ret) अणु
			dev_err(dev, "%pOF read phy-mode err %d\n",
				port_np, ret);
			वापस ret;
		पूर्ण

		ret = of_get_mac_address(port_np, port->slave.mac_addr);
		अगर (ret) अणु
			am65_cpsw_am654_get_efuse_macid(port_np,
							port->port_id,
							port->slave.mac_addr);
			अगर (!is_valid_ether_addr(port->slave.mac_addr)) अणु
				अक्रमom_ether_addr(port->slave.mac_addr);
				dev_err(dev, "Use random MAC address\n");
			पूर्ण
		पूर्ण
	पूर्ण
	of_node_put(node);

	/* is there at least one ext.port */
	अगर (!(~common->disabled_ports_mask & GENMASK(common->port_num, 1))) अणु
		dev_err(dev, "No Ext. port are available\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम am65_cpsw_pcpu_stats_मुक्त(व्योम *data)
अणु
	काष्ठा am65_cpsw_ndev_stats __percpu *stats = data;

	मुक्त_percpu(stats);
पूर्ण

अटल पूर्णांक
am65_cpsw_nuss_init_port_ndev(काष्ठा am65_cpsw_common *common, u32 port_idx)
अणु
	काष्ठा am65_cpsw_ndev_priv *ndev_priv;
	काष्ठा device *dev = common->dev;
	काष्ठा am65_cpsw_port *port;
	पूर्णांक ret;

	port = &common->ports[port_idx];

	अगर (port->disabled)
		वापस 0;

	/* alloc netdev */
	port->ndev = devm_alloc_etherdev_mqs(common->dev,
					     माप(काष्ठा am65_cpsw_ndev_priv),
					     AM65_CPSW_MAX_TX_QUEUES,
					     AM65_CPSW_MAX_RX_QUEUES);
	अगर (!port->ndev) अणु
		dev_err(dev, "error allocating slave net_device %u\n",
			port->port_id);
		वापस -ENOMEM;
	पूर्ण

	ndev_priv = netdev_priv(port->ndev);
	ndev_priv->port = port;
	ndev_priv->msg_enable = AM65_CPSW_DEBUG;
	SET_NETDEV_DEV(port->ndev, dev);

	ether_addr_copy(port->ndev->dev_addr, port->slave.mac_addr);

	port->ndev->min_mtu = AM65_CPSW_MIN_PACKET_SIZE;
	port->ndev->max_mtu = AM65_CPSW_MAX_PACKET_SIZE;
	port->ndev->hw_features = NETIF_F_SG |
				  NETIF_F_RXCSUM |
				  NETIF_F_HW_CSUM |
				  NETIF_F_HW_TC;
	port->ndev->features = port->ndev->hw_features |
			       NETIF_F_HW_VLAN_CTAG_FILTER;
	port->ndev->vlan_features |=  NETIF_F_SG;
	port->ndev->netdev_ops = &am65_cpsw_nuss_netdev_ops;
	port->ndev->ethtool_ops = &am65_cpsw_ethtool_ops_slave;

	/* Disable TX checksum offload by शेष due to HW bug */
	अगर (common->pdata.quirks & AM65_CPSW_QUIRK_I2027_NO_TX_CSUM)
		port->ndev->features &= ~NETIF_F_HW_CSUM;

	ndev_priv->stats = netdev_alloc_pcpu_stats(काष्ठा am65_cpsw_ndev_stats);
	अगर (!ndev_priv->stats)
		वापस -ENOMEM;

	ret = devm_add_action_or_reset(dev, am65_cpsw_pcpu_stats_मुक्त,
				       ndev_priv->stats);
	अगर (ret)
		dev_err(dev, "failed to add percpu stat free action %d\n", ret);

	अगर (!common->dma_ndev)
		common->dma_ndev = port->ndev;

	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_init_ndevs(काष्ठा am65_cpsw_common *common)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < common->port_num; i++) अणु
		ret = am65_cpsw_nuss_init_port_ndev(common, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	netअगर_napi_add(common->dma_ndev, &common->napi_rx,
		       am65_cpsw_nuss_rx_poll, NAPI_POLL_WEIGHT);

	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_ndev_add_tx_napi(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा device *dev = common->dev;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < common->tx_ch_num; i++) अणु
		काष्ठा am65_cpsw_tx_chn *tx_chn = &common->tx_chns[i];

		netअगर_tx_napi_add(common->dma_ndev, &tx_chn->napi_tx,
				  am65_cpsw_nuss_tx_poll, NAPI_POLL_WEIGHT);

		ret = devm_request_irq(dev, tx_chn->irq,
				       am65_cpsw_nuss_tx_irq,
				       IRQF_TRIGGER_HIGH,
				       tx_chn->tx_chn_name, tx_chn);
		अगर (ret) अणु
			dev_err(dev, "failure requesting tx%u irq %u, %d\n",
				tx_chn->id, tx_chn->irq, ret);
			जाओ err;
		पूर्ण
	पूर्ण

err:
	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_nuss_cleanup_ndev(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा am65_cpsw_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < common->port_num; i++) अणु
		port = &common->ports[i];
		अगर (port->ndev)
			unरेजिस्टर_netdev(port->ndev);
	पूर्ण
पूर्ण

अटल व्योम am65_cpsw_port_offload_fwd_mark_update(काष्ठा am65_cpsw_common *common)
अणु
	पूर्णांक set_val = 0;
	पूर्णांक i;

	अगर (common->br_members == (GENMASK(common->port_num, 1) & ~common->disabled_ports_mask))
		set_val = 1;

	dev_dbg(common->dev, "set offload_fwd_mark %d\n", set_val);

	क्रम (i = 1; i <= common->port_num; i++) अणु
		काष्ठा am65_cpsw_port *port = am65_common_get_port(common, i);
		काष्ठा am65_cpsw_ndev_priv *priv = am65_ndev_to_priv(port->ndev);

		priv->offload_fwd_mark = set_val;
	पूर्ण
पूर्ण

bool am65_cpsw_port_dev_check(स्थिर काष्ठा net_device *ndev)
अणु
	अगर (ndev->netdev_ops == &am65_cpsw_nuss_netdev_ops) अणु
		काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);

		वापस !common->is_emac_mode;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक am65_cpsw_netdevice_port_link(काष्ठा net_device *ndev, काष्ठा net_device *br_ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_ndev_priv *priv = am65_ndev_to_priv(ndev);

	अगर (!common->br_members) अणु
		common->hw_bridge_dev = br_ndev;
	पूर्ण अन्यथा अणु
		/* This is adding the port to a second bridge, this is
		 * unsupported
		 */
		अगर (common->hw_bridge_dev != br_ndev)
			वापस -EOPNOTSUPP;
	पूर्ण

	common->br_members |= BIT(priv->port->port_id);

	am65_cpsw_port_offload_fwd_mark_update(common);

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम am65_cpsw_netdevice_port_unlink(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	काष्ठा am65_cpsw_ndev_priv *priv = am65_ndev_to_priv(ndev);

	common->br_members &= ~BIT(priv->port->port_id);

	am65_cpsw_port_offload_fwd_mark_update(common);

	अगर (!common->br_members)
		common->hw_bridge_dev = शून्य;
पूर्ण

/* netdev notअगरier */
अटल पूर्णांक am65_cpsw_netdevice_event(काष्ठा notअगरier_block *unused,
				     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_changeupper_info *info;
	पूर्णांक ret = NOTIFY_DONE;

	अगर (!am65_cpsw_port_dev_check(ndev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		info = ptr;

		अगर (netअगर_is_bridge_master(info->upper_dev)) अणु
			अगर (info->linking)
				ret = am65_cpsw_netdevice_port_link(ndev, info->upper_dev);
			अन्यथा
				am65_cpsw_netdevice_port_unlink(ndev);
		पूर्ण
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल पूर्णांक am65_cpsw_रेजिस्टर_notअगरiers(काष्ठा am65_cpsw_common *cpsw)
अणु
	पूर्णांक ret = 0;

	अगर (AM65_CPSW_IS_CPSW2G(cpsw) ||
	    !IS_REACHABLE(CONFIG_TI_K3_AM65_CPSW_SWITCHDEV))
		वापस 0;

	cpsw->am65_cpsw_netdevice_nb.notअगरier_call = &am65_cpsw_netdevice_event;
	ret = रेजिस्टर_netdevice_notअगरier(&cpsw->am65_cpsw_netdevice_nb);
	अगर (ret) अणु
		dev_err(cpsw->dev, "can't register netdevice notifier\n");
		वापस ret;
	पूर्ण

	ret = am65_cpsw_चयनdev_रेजिस्टर_notअगरiers(cpsw);
	अगर (ret)
		unरेजिस्टर_netdevice_notअगरier(&cpsw->am65_cpsw_netdevice_nb);

	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_unरेजिस्टर_notअगरiers(काष्ठा am65_cpsw_common *cpsw)
अणु
	अगर (AM65_CPSW_IS_CPSW2G(cpsw) ||
	    !IS_REACHABLE(CONFIG_TI_K3_AM65_CPSW_SWITCHDEV))
		वापस;

	am65_cpsw_चयनdev_unरेजिस्टर_notअगरiers(cpsw);
	unरेजिस्टर_netdevice_notअगरier(&cpsw->am65_cpsw_netdevice_nb);
पूर्ण

अटल स्थिर काष्ठा devlink_ops am65_cpsw_devlink_ops = अणुपूर्ण;

अटल व्योम am65_cpsw_init_stp_ale_entry(काष्ठा am65_cpsw_common *cpsw)
अणु
	cpsw_ale_add_mcast(cpsw->ale, eth_stp_addr, ALE_PORT_HOST, ALE_SUPER, 0,
			   ALE_MCAST_BLOCK_LEARN_FWD);
पूर्ण

अटल व्योम am65_cpsw_init_host_port_चयन(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा am65_cpsw_host *host = am65_common_get_host(common);

	ग_लिखोl(common->शेष_vlan, host->port_base + AM65_CPSW_PORT_VLAN_REG_OFFSET);

	am65_cpsw_init_stp_ale_entry(common);

	cpsw_ale_control_set(common->ale, HOST_PORT_NUM, ALE_P0_UNI_FLOOD, 1);
	dev_dbg(common->dev, "Set P0_UNI_FLOOD\n");
	cpsw_ale_control_set(common->ale, HOST_PORT_NUM, ALE_PORT_NOLEARN, 0);
पूर्ण

अटल व्योम am65_cpsw_init_host_port_emac(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा am65_cpsw_host *host = am65_common_get_host(common);

	ग_लिखोl(0, host->port_base + AM65_CPSW_PORT_VLAN_REG_OFFSET);

	cpsw_ale_control_set(common->ale, HOST_PORT_NUM, ALE_P0_UNI_FLOOD, 0);
	dev_dbg(common->dev, "unset P0_UNI_FLOOD\n");

	/* learning make no sense in multi-mac mode */
	cpsw_ale_control_set(common->ale, HOST_PORT_NUM, ALE_PORT_NOLEARN, 1);
पूर्ण

अटल पूर्णांक am65_cpsw_dl_चयन_mode_get(काष्ठा devlink *dl, u32 id,
					काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा am65_cpsw_devlink *dl_priv = devlink_priv(dl);
	काष्ठा am65_cpsw_common *common = dl_priv->common;

	dev_dbg(common->dev, "%s id:%u\n", __func__, id);

	अगर (id != AM65_CPSW_DL_PARAM_SWITCH_MODE)
		वापस -EOPNOTSUPP;

	ctx->val.vbool = !common->is_emac_mode;

	वापस 0;
पूर्ण

अटल व्योम am65_cpsw_init_port_emac_ale(काष्ठा  am65_cpsw_port *port)
अणु
	काष्ठा am65_cpsw_slave_data *slave = &port->slave;
	काष्ठा am65_cpsw_common *common = port->common;
	u32 port_mask;

	ग_लिखोl(slave->port_vlan, port->port_base + AM65_CPSW_PORT_VLAN_REG_OFFSET);

	अगर (slave->mac_only)
		/* enable mac-only mode on port */
		cpsw_ale_control_set(common->ale, port->port_id,
				     ALE_PORT_MACONLY, 1);

	cpsw_ale_control_set(common->ale, port->port_id, ALE_PORT_NOLEARN, 1);

	port_mask = BIT(port->port_id) | ALE_PORT_HOST;

	cpsw_ale_add_ucast(common->ale, port->ndev->dev_addr,
			   HOST_PORT_NUM, ALE_SECURE, slave->port_vlan);
	cpsw_ale_add_mcast(common->ale, port->ndev->broadcast,
			   port_mask, ALE_VLAN, slave->port_vlan, ALE_MCAST_FWD_2);
पूर्ण

अटल व्योम am65_cpsw_init_port_चयन_ale(काष्ठा am65_cpsw_port *port)
अणु
	काष्ठा am65_cpsw_slave_data *slave = &port->slave;
	काष्ठा am65_cpsw_common *cpsw = port->common;
	u32 port_mask;

	cpsw_ale_control_set(cpsw->ale, port->port_id,
			     ALE_PORT_NOLEARN, 0);

	cpsw_ale_add_ucast(cpsw->ale, port->ndev->dev_addr,
			   HOST_PORT_NUM, ALE_SECURE | ALE_BLOCKED | ALE_VLAN,
			   slave->port_vlan);

	port_mask = BIT(port->port_id) | ALE_PORT_HOST;

	cpsw_ale_add_mcast(cpsw->ale, port->ndev->broadcast,
			   port_mask, ALE_VLAN, slave->port_vlan,
			   ALE_MCAST_FWD_2);

	ग_लिखोl(slave->port_vlan, port->port_base + AM65_CPSW_PORT_VLAN_REG_OFFSET);

	cpsw_ale_control_set(cpsw->ale, port->port_id,
			     ALE_PORT_MACONLY, 0);
पूर्ण

अटल पूर्णांक am65_cpsw_dl_चयन_mode_set(काष्ठा devlink *dl, u32 id,
					काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा am65_cpsw_devlink *dl_priv = devlink_priv(dl);
	काष्ठा am65_cpsw_common *cpsw = dl_priv->common;
	bool चयन_en = ctx->val.vbool;
	bool अगर_running = false;
	पूर्णांक i;

	dev_dbg(cpsw->dev, "%s id:%u\n", __func__, id);

	अगर (id != AM65_CPSW_DL_PARAM_SWITCH_MODE)
		वापस -EOPNOTSUPP;

	अगर (चयन_en == !cpsw->is_emac_mode)
		वापस 0;

	अगर (!चयन_en && cpsw->br_members) अणु
		dev_err(cpsw->dev, "Remove ports from bridge before disabling switch mode\n");
		वापस -EINVAL;
	पूर्ण

	rtnl_lock();

	cpsw->is_emac_mode = !चयन_en;

	क्रम (i = 0; i < cpsw->port_num; i++) अणु
		काष्ठा net_device *sl_ndev = cpsw->ports[i].ndev;

		अगर (!sl_ndev || !netअगर_running(sl_ndev))
			जारी;

		अगर_running = true;
	पूर्ण

	अगर (!अगर_running) अणु
		/* all ndevs are करोwn */
		क्रम (i = 0; i < cpsw->port_num; i++) अणु
			काष्ठा net_device *sl_ndev = cpsw->ports[i].ndev;
			काष्ठा am65_cpsw_slave_data *slave;

			अगर (!sl_ndev)
				जारी;

			slave = am65_ndev_to_slave(sl_ndev);
			अगर (चयन_en)
				slave->port_vlan = cpsw->शेष_vlan;
			अन्यथा
				slave->port_vlan = 0;
		पूर्ण

		जाओ निकास;
	पूर्ण

	cpsw_ale_control_set(cpsw->ale, 0, ALE_BYPASS, 1);
	/* clean up ALE table */
	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_CLEAR, 1);
	cpsw_ale_control_get(cpsw->ale, HOST_PORT_NUM, ALE_AGEOUT);

	अगर (चयन_en) अणु
		dev_info(cpsw->dev, "Enable switch mode\n");

		am65_cpsw_init_host_port_चयन(cpsw);

		क्रम (i = 0; i < cpsw->port_num; i++) अणु
			काष्ठा net_device *sl_ndev = cpsw->ports[i].ndev;
			काष्ठा am65_cpsw_slave_data *slave;
			काष्ठा am65_cpsw_port *port;

			अगर (!sl_ndev)
				जारी;

			port = am65_ndev_to_port(sl_ndev);
			slave = am65_ndev_to_slave(sl_ndev);
			slave->port_vlan = cpsw->शेष_vlan;

			अगर (netअगर_running(sl_ndev))
				am65_cpsw_init_port_चयन_ale(port);
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_info(cpsw->dev, "Disable switch mode\n");

		am65_cpsw_init_host_port_emac(cpsw);

		क्रम (i = 0; i < cpsw->port_num; i++) अणु
			काष्ठा net_device *sl_ndev = cpsw->ports[i].ndev;
			काष्ठा am65_cpsw_port *port;

			अगर (!sl_ndev)
				जारी;

			port = am65_ndev_to_port(sl_ndev);
			port->slave.port_vlan = 0;
			अगर (netअगर_running(sl_ndev))
				am65_cpsw_init_port_emac_ale(port);
		पूर्ण
	पूर्ण
	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_BYPASS, 0);
निकास:
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_param am65_cpsw_devlink_params[] = अणु
	DEVLINK_PARAM_DRIVER(AM65_CPSW_DL_PARAM_SWITCH_MODE, "switch_mode",
			     DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_RUNTIME),
			     am65_cpsw_dl_चयन_mode_get,
			     am65_cpsw_dl_चयन_mode_set, शून्य),
पूर्ण;

अटल व्योम am65_cpsw_unरेजिस्टर_devlink_ports(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा devlink_port *dl_port;
	काष्ठा am65_cpsw_port *port;
	पूर्णांक i;

	क्रम (i = 1; i <= common->port_num; i++) अणु
		port = am65_common_get_port(common, i);
		dl_port = &port->devlink_port;

		अगर (dl_port->रेजिस्टरed)
			devlink_port_unरेजिस्टर(dl_port);
	पूर्ण
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_रेजिस्टर_devlink(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	काष्ठा am65_cpsw_devlink *dl_priv;
	काष्ठा device *dev = common->dev;
	काष्ठा devlink_port *dl_port;
	काष्ठा am65_cpsw_port *port;
	पूर्णांक ret = 0;
	पूर्णांक i;

	common->devlink =
		devlink_alloc(&am65_cpsw_devlink_ops, माप(*dl_priv));
	अगर (!common->devlink)
		वापस -ENOMEM;

	dl_priv = devlink_priv(common->devlink);
	dl_priv->common = common;

	ret = devlink_रेजिस्टर(common->devlink, dev);
	अगर (ret) अणु
		dev_err(dev, "devlink reg fail ret:%d\n", ret);
		जाओ dl_मुक्त;
	पूर्ण

	/* Provide devlink hook to चयन mode when multiple बाह्यal ports
	 * are present NUSS चयनdev driver is enabled.
	 */
	अगर (!AM65_CPSW_IS_CPSW2G(common) &&
	    IS_ENABLED(CONFIG_TI_K3_AM65_CPSW_SWITCHDEV)) अणु
		ret = devlink_params_रेजिस्टर(common->devlink,
					      am65_cpsw_devlink_params,
					      ARRAY_SIZE(am65_cpsw_devlink_params));
		अगर (ret) अणु
			dev_err(dev, "devlink params reg fail ret:%d\n", ret);
			जाओ dl_unreg;
		पूर्ण
		devlink_params_publish(common->devlink);
	पूर्ण

	क्रम (i = 1; i <= common->port_num; i++) अणु
		port = am65_common_get_port(common, i);
		dl_port = &port->devlink_port;

		attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
		attrs.phys.port_number = port->port_id;
		attrs.चयन_id.id_len = माप(resource_माप_प्रकार);
		स_नकल(attrs.चयन_id.id, common->चयन_id, attrs.चयन_id.id_len);
		devlink_port_attrs_set(dl_port, &attrs);

		ret = devlink_port_रेजिस्टर(common->devlink, dl_port, port->port_id);
		अगर (ret) अणु
			dev_err(dev, "devlink_port reg fail for port %d, ret:%d\n",
				port->port_id, ret);
			जाओ dl_port_unreg;
		पूर्ण
		devlink_port_type_eth_set(dl_port, port->ndev);
	पूर्ण

	वापस ret;

dl_port_unreg:
	am65_cpsw_unरेजिस्टर_devlink_ports(common);
dl_unreg:
	devlink_unरेजिस्टर(common->devlink);
dl_मुक्त:
	devlink_मुक्त(common->devlink);

	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_unरेजिस्टर_devlink(काष्ठा am65_cpsw_common *common)
अणु
	अगर (!AM65_CPSW_IS_CPSW2G(common) &&
	    IS_ENABLED(CONFIG_TI_K3_AM65_CPSW_SWITCHDEV)) अणु
		devlink_params_unpublish(common->devlink);
		devlink_params_unरेजिस्टर(common->devlink, am65_cpsw_devlink_params,
					  ARRAY_SIZE(am65_cpsw_devlink_params));
	पूर्ण

	am65_cpsw_unरेजिस्टर_devlink_ports(common);
	devlink_unरेजिस्टर(common->devlink);
	devlink_मुक्त(common->devlink);
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_रेजिस्टर_ndevs(काष्ठा am65_cpsw_common *common)
अणु
	काष्ठा device *dev = common->dev;
	काष्ठा am65_cpsw_port *port;
	पूर्णांक ret = 0, i;

	ret = am65_cpsw_nuss_ndev_add_tx_napi(common);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(dev, common->rx_chns.irq,
			       am65_cpsw_nuss_rx_irq,
			       IRQF_TRIGGER_HIGH, dev_name(dev), common);
	अगर (ret) अणु
		dev_err(dev, "failure requesting rx irq %u, %d\n",
			common->rx_chns.irq, ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < common->port_num; i++) अणु
		port = &common->ports[i];

		अगर (!port->ndev)
			जारी;

		ret = रेजिस्टर_netdev(port->ndev);
		अगर (ret) अणु
			dev_err(dev, "error registering slave net device%i %d\n",
				i, ret);
			जाओ err_cleanup_ndev;
		पूर्ण
	पूर्ण

	ret = am65_cpsw_रेजिस्टर_notअगरiers(common);
	अगर (ret)
		जाओ err_cleanup_ndev;

	ret = am65_cpsw_nuss_रेजिस्टर_devlink(common);
	अगर (ret)
		जाओ clean_unरेजिस्टर_notअगरiers;

	/* can't स्वतः unरेजिस्टर ndev using devm_add_action() due to
	 * devres release sequence in DD core क्रम DMA
	 */

	वापस 0;
clean_unरेजिस्टर_notअगरiers:
	am65_cpsw_unरेजिस्टर_notअगरiers(common);
err_cleanup_ndev:
	am65_cpsw_nuss_cleanup_ndev(common);

	वापस ret;
पूर्ण

पूर्णांक am65_cpsw_nuss_update_tx_chns(काष्ठा am65_cpsw_common *common, पूर्णांक num_tx)
अणु
	पूर्णांक ret;

	common->tx_ch_num = num_tx;
	ret = am65_cpsw_nuss_init_tx_chns(common);
	अगर (ret)
		वापस ret;

	वापस am65_cpsw_nuss_ndev_add_tx_napi(common);
पूर्ण

काष्ठा am65_cpsw_soc_pdata अणु
	u32	quirks_dis;
पूर्ण;

अटल स्थिर काष्ठा am65_cpsw_soc_pdata am65x_soc_sr2_0 = अणु
	.quirks_dis = AM65_CPSW_QUIRK_I2027_NO_TX_CSUM,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute am65_cpsw_socinfo[] = अणु
	अणु .family = "AM65X",
	  .revision = "SR2.0",
	  .data = &am65x_soc_sr2_0
	पूर्ण,
	अणु/* sentinel */पूर्ण
पूर्ण;

अटल स्थिर काष्ठा am65_cpsw_pdata am65x_sr1_0 = अणु
	.quirks = AM65_CPSW_QUIRK_I2027_NO_TX_CSUM,
	.ale_dev_id = "am65x-cpsw2g",
	.fdqring_mode = K3_RINGACC_RING_MODE_MESSAGE,
पूर्ण;

अटल स्थिर काष्ठा am65_cpsw_pdata j721e_pdata = अणु
	.quirks = 0,
	.ale_dev_id = "am65x-cpsw2g",
	.fdqring_mode = K3_RINGACC_RING_MODE_MESSAGE,
पूर्ण;

अटल स्थिर काष्ठा am65_cpsw_pdata am64x_cpswxg_pdata = अणु
	.quirks = 0,
	.ale_dev_id = "am64-cpswxg",
	.fdqring_mode = K3_RINGACC_RING_MODE_RING,
पूर्ण;

अटल स्थिर काष्ठा of_device_id am65_cpsw_nuss_of_mtable[] = अणु
	अणु .compatible = "ti,am654-cpsw-nuss", .data = &am65x_sr1_0पूर्ण,
	अणु .compatible = "ti,j721e-cpsw-nuss", .data = &j721e_pdataपूर्ण,
	अणु .compatible = "ti,am642-cpsw-nuss", .data = &am64x_cpswxg_pdataपूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, am65_cpsw_nuss_of_mtable);

अटल व्योम am65_cpsw_nuss_apply_socinfo(काष्ठा am65_cpsw_common *common)
अणु
	स्थिर काष्ठा soc_device_attribute *soc;

	soc = soc_device_match(am65_cpsw_socinfo);
	अगर (soc && soc->data) अणु
		स्थिर काष्ठा am65_cpsw_soc_pdata *socdata = soc->data;

		/* disable quirks */
		common->pdata.quirks &= ~socdata->quirks_dis;
	पूर्ण
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpsw_ale_params ale_params = अणु 0 पूर्ण;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा am65_cpsw_common *common;
	काष्ठा device_node *node;
	काष्ठा resource *res;
	काष्ठा clk *clk;
	u64 id_temp;
	पूर्णांक ret, i;

	common = devm_kzalloc(dev, माप(काष्ठा am65_cpsw_common), GFP_KERNEL);
	अगर (!common)
		वापस -ENOMEM;
	common->dev = dev;

	of_id = of_match_device(am65_cpsw_nuss_of_mtable, dev);
	अगर (!of_id)
		वापस -EINVAL;
	common->pdata = *(स्थिर काष्ठा am65_cpsw_pdata *)of_id->data;

	am65_cpsw_nuss_apply_socinfo(common);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cpsw_nuss");
	common->ss_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(common->ss_base))
		वापस PTR_ERR(common->ss_base);
	common->cpsw_base = common->ss_base + AM65_CPSW_CPSW_NU_BASE;
	/* Use device's physical base address as चयन id */
	id_temp = cpu_to_be64(res->start);
	स_नकल(common->चयन_id, &id_temp, माप(res->start));

	node = of_get_child_by_name(dev->of_node, "ethernet-ports");
	अगर (!node)
		वापस -ENOENT;
	common->port_num = of_get_child_count(node);
	अगर (common->port_num < 1 || common->port_num > AM65_CPSW_MAX_PORTS)
		वापस -ENOENT;
	of_node_put(node);

	common->rx_flow_id_base = -1;
	init_completion(&common->tकरोwn_complete);
	common->tx_ch_num = 1;
	common->pf_p0_rx_ptype_rrobin = false;
	common->शेष_vlan = 1;

	common->ports = devm_kसुस्मृति(dev, common->port_num,
				     माप(*common->ports),
				     GFP_KERNEL);
	अगर (!common->ports)
		वापस -ENOMEM;

	clk = devm_clk_get(dev, "fck");
	अगर (IS_ERR(clk))
		वापस dev_err_probe(dev, PTR_ERR(clk), "getting fck clock\n");
	common->bus_freq = clk_get_rate(clk);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		pm_runसमय_disable(dev);
		वापस ret;
	पूर्ण

	node = of_get_child_by_name(dev->of_node, "mdio");
	अगर (!node) अणु
		dev_warn(dev, "MDIO node not found\n");
	पूर्ण अन्यथा अगर (of_device_is_available(node)) अणु
		काष्ठा platक्रमm_device *mdio_pdev;

		mdio_pdev = of_platक्रमm_device_create(node, शून्य, dev);
		अगर (!mdio_pdev) अणु
			ret = -ENODEV;
			जाओ err_pm_clear;
		पूर्ण

		common->mdio_dev =  &mdio_pdev->dev;
	पूर्ण
	of_node_put(node);

	am65_cpsw_nuss_get_ver(common);

	/* init tx channels */
	ret = am65_cpsw_nuss_init_tx_chns(common);
	अगर (ret)
		जाओ err_of_clear;
	ret = am65_cpsw_nuss_init_rx_chns(common);
	अगर (ret)
		जाओ err_of_clear;

	ret = am65_cpsw_nuss_init_host_p(common);
	अगर (ret)
		जाओ err_of_clear;

	ret = am65_cpsw_nuss_init_slave_ports(common);
	अगर (ret)
		जाओ err_of_clear;

	/* init common data */
	ale_params.dev = dev;
	ale_params.ale_ageout = AM65_CPSW_ALE_AGEOUT_DEFAULT;
	ale_params.ale_ports = common->port_num + 1;
	ale_params.ale_regs = common->cpsw_base + AM65_CPSW_NU_ALE_BASE;
	ale_params.dev_id = common->pdata.ale_dev_id;
	ale_params.bus_freq = common->bus_freq;

	common->ale = cpsw_ale_create(&ale_params);
	अगर (IS_ERR(common->ale)) अणु
		dev_err(dev, "error initializing ale engine\n");
		ret = PTR_ERR(common->ale);
		जाओ err_of_clear;
	पूर्ण

	ret = am65_cpsw_init_cpts(common);
	अगर (ret)
		जाओ err_of_clear;

	/* init ports */
	क्रम (i = 0; i < common->port_num; i++)
		am65_cpsw_nuss_slave_disable_unused(&common->ports[i]);

	dev_set_drvdata(dev, common);

	common->is_emac_mode = true;

	ret = am65_cpsw_nuss_init_ndevs(common);
	अगर (ret)
		जाओ err_of_clear;

	ret = am65_cpsw_nuss_रेजिस्टर_ndevs(common);
	अगर (ret)
		जाओ err_of_clear;

	pm_runसमय_put(dev);
	वापस 0;

err_of_clear:
	of_platक्रमm_device_destroy(common->mdio_dev, शून्य);
err_pm_clear:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_nuss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा am65_cpsw_common *common;
	पूर्णांक ret;

	common = dev_get_drvdata(dev);

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		वापस ret;
	पूर्ण

	am65_cpsw_unरेजिस्टर_devlink(common);
	am65_cpsw_unरेजिस्टर_notअगरiers(common);

	/* must unरेजिस्टर ndevs here because DD release_driver routine calls
	 * dma_deconfigure(dev) beक्रमe devres_release_all(dev)
	 */
	am65_cpsw_nuss_cleanup_ndev(common);

	of_platक्रमm_device_destroy(common->mdio_dev, शून्य);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver am65_cpsw_nuss_driver = अणु
	.driver = अणु
		.name	 = AM65_CPSW_DRV_NAME,
		.of_match_table = am65_cpsw_nuss_of_mtable,
	पूर्ण,
	.probe = am65_cpsw_nuss_probe,
	.हटाओ = am65_cpsw_nuss_हटाओ,
पूर्ण;

module_platक्रमm_driver(am65_cpsw_nuss_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Grygorii Strashko <grygorii.strashko@ti.com>");
MODULE_DESCRIPTION("TI AM65 CPSW Ethernet driver");
