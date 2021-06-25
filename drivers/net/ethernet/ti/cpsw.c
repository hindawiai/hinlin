<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments Ethernet Switch Driver
 *
 * Copyright (C) 2012 Texas Instruments
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_device.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/sys_soc.h>
#समावेश <net/page_pool.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>

#समावेश <linux/pinctrl/consumer.h>
#समावेश <net/pkt_cls.h>

#समावेश "cpsw.h"
#समावेश "cpsw_ale.h"
#समावेश "cpsw_priv.h"
#समावेश "cpsw_sl.h"
#समावेश "cpts.h"
#समावेश "davinci_cpdma.h"

#समावेश <net/pkt_sched.h>

अटल पूर्णांक debug_level;
module_param(debug_level, पूर्णांक, 0);
MODULE_PARM_DESC(debug_level, "cpsw debug level (NETIF_MSG bits)");

अटल पूर्णांक ale_ageout = 10;
module_param(ale_ageout, पूर्णांक, 0);
MODULE_PARM_DESC(ale_ageout, "cpsw ale ageout interval (seconds)");

अटल पूर्णांक rx_packet_max = CPSW_MAX_PACKET_SIZE;
module_param(rx_packet_max, पूर्णांक, 0);
MODULE_PARM_DESC(rx_packet_max, "maximum receive packet size (bytes)");

अटल पूर्णांक descs_pool_size = CPSW_CPDMA_DESCS_POOL_SIZE_DEFAULT;
module_param(descs_pool_size, पूर्णांक, 0444);
MODULE_PARM_DESC(descs_pool_size, "Number of CPDMA CPPI descriptors in pool");

#घोषणा क्रम_each_slave(priv, func, arg...)				\
	करो अणु								\
		काष्ठा cpsw_slave *slave;				\
		काष्ठा cpsw_common *cpsw = (priv)->cpsw;		\
		पूर्णांक n;							\
		अगर (cpsw->data.dual_emac)				\
			(func)((cpsw)->slaves + priv->emac_port, ##arg);\
		अन्यथा							\
			क्रम (n = cpsw->data.slaves,			\
					slave = cpsw->slaves;		\
					n; n--)				\
				(func)(slave++, ##arg);			\
	पूर्ण जबतक (0)

अटल पूर्णांक cpsw_slave_index_priv(काष्ठा cpsw_common *cpsw,
				 काष्ठा cpsw_priv *priv)
अणु
	वापस cpsw->data.dual_emac ? priv->emac_port : cpsw->data.active_slave;
पूर्ण

अटल पूर्णांक cpsw_get_slave_port(u32 slave_num)
अणु
	वापस slave_num + 1;
पूर्ण

अटल पूर्णांक cpsw_nकरो_vlan_rx_add_vid(काष्ठा net_device *ndev,
				    __be16 proto, u16 vid);

अटल व्योम cpsw_set_promiscious(काष्ठा net_device *ndev, bool enable)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	काष्ठा cpsw_ale *ale = cpsw->ale;
	पूर्णांक i;

	अगर (cpsw->data.dual_emac) अणु
		bool flag = false;

		/* Enabling promiscuous mode क्रम one पूर्णांकerface will be
		 * common क्रम both the पूर्णांकerface as the पूर्णांकerface shares
		 * the same hardware resource.
		 */
		क्रम (i = 0; i < cpsw->data.slaves; i++)
			अगर (cpsw->slaves[i].ndev->flags & IFF_PROMISC)
				flag = true;

		अगर (!enable && flag) अणु
			enable = true;
			dev_err(&ndev->dev, "promiscuity not disabled as the other interface is still in promiscuity mode\n");
		पूर्ण

		अगर (enable) अणु
			/* Enable Bypass */
			cpsw_ale_control_set(ale, 0, ALE_BYPASS, 1);

			dev_dbg(&ndev->dev, "promiscuity enabled\n");
		पूर्ण अन्यथा अणु
			/* Disable Bypass */
			cpsw_ale_control_set(ale, 0, ALE_BYPASS, 0);
			dev_dbg(&ndev->dev, "promiscuity disabled\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (enable) अणु
			अचिन्हित दीर्घ समयout = jअगरfies + HZ;

			/* Disable Learn क्रम all ports (host is port 0 and slaves are port 1 and up */
			क्रम (i = 0; i <= cpsw->data.slaves; i++) अणु
				cpsw_ale_control_set(ale, i,
						     ALE_PORT_NOLEARN, 1);
				cpsw_ale_control_set(ale, i,
						     ALE_PORT_NO_SA_UPDATE, 1);
			पूर्ण

			/* Clear All Untouched entries */
			cpsw_ale_control_set(ale, 0, ALE_AGEOUT, 1);
			करो अणु
				cpu_relax();
				अगर (cpsw_ale_control_get(ale, 0, ALE_AGEOUT))
					अवरोध;
			पूर्ण जबतक (समय_after(समयout, jअगरfies));
			cpsw_ale_control_set(ale, 0, ALE_AGEOUT, 1);

			/* Clear all mcast from ALE */
			cpsw_ale_flush_multicast(ale, ALE_ALL_PORTS, -1);
			__hw_addr_ref_unsync_dev(&ndev->mc, ndev, शून्य);

			/* Flood All Unicast Packets to Host port */
			cpsw_ale_control_set(ale, 0, ALE_P0_UNI_FLOOD, 1);
			dev_dbg(&ndev->dev, "promiscuity enabled\n");
		पूर्ण अन्यथा अणु
			/* Don't Flood All Unicast Packets to Host port */
			cpsw_ale_control_set(ale, 0, ALE_P0_UNI_FLOOD, 0);

			/* Enable Learn क्रम all ports (host is port 0 and slaves are port 1 and up */
			क्रम (i = 0; i <= cpsw->data.slaves; i++) अणु
				cpsw_ale_control_set(ale, i,
						     ALE_PORT_NOLEARN, 0);
				cpsw_ale_control_set(ale, i,
						     ALE_PORT_NO_SA_UPDATE, 0);
			पूर्ण
			dev_dbg(&ndev->dev, "promiscuity disabled\n");
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cpsw_set_mc - adds multicast entry to the table अगर it's not added or deletes
 * अगर it's not deleted
 * @ndev: device to sync
 * @addr: address to be added or deleted
 * @vid: vlan id, अगर vid < 0 set/unset address क्रम real device
 * @add: add address अगर the flag is set or हटाओ otherwise
 */
अटल पूर्णांक cpsw_set_mc(काष्ठा net_device *ndev, स्थिर u8 *addr,
		       पूर्णांक vid, पूर्णांक add)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक mask, flags, ret;

	अगर (vid < 0) अणु
		अगर (cpsw->data.dual_emac)
			vid = cpsw->slaves[priv->emac_port].port_vlan;
		अन्यथा
			vid = 0;
	पूर्ण

	mask = cpsw->data.dual_emac ? ALE_PORT_HOST : ALE_ALL_PORTS;
	flags = vid ? ALE_VLAN : 0;

	अगर (add)
		ret = cpsw_ale_add_mcast(cpsw->ale, addr, mask, flags, vid, 0);
	अन्यथा
		ret = cpsw_ale_del_mcast(cpsw->ale, addr, 0, flags, vid);

	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_update_vlan_mc(काष्ठा net_device *vdev, पूर्णांक vid, व्योम *ctx)
अणु
	काष्ठा addr_sync_ctx *sync_ctx = ctx;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक found = 0, ret = 0;

	अगर (!vdev || !(vdev->flags & IFF_UP))
		वापस 0;

	/* vlan address is relevant अगर its sync_cnt != 0 */
	netdev_क्रम_each_mc_addr(ha, vdev) अणु
		अगर (ether_addr_equal(ha->addr, sync_ctx->addr)) अणु
			found = ha->sync_cnt;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found)
		sync_ctx->consumed++;

	अगर (sync_ctx->flush) अणु
		अगर (!found)
			cpsw_set_mc(sync_ctx->ndev, sync_ctx->addr, vid, 0);
		वापस 0;
	पूर्ण

	अगर (found)
		ret = cpsw_set_mc(sync_ctx->ndev, sync_ctx->addr, vid, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_add_mc_addr(काष्ठा net_device *ndev, स्थिर u8 *addr, पूर्णांक num)
अणु
	काष्ठा addr_sync_ctx sync_ctx;
	पूर्णांक ret;

	sync_ctx.consumed = 0;
	sync_ctx.addr = addr;
	sync_ctx.ndev = ndev;
	sync_ctx.flush = 0;

	ret = vlan_क्रम_each(ndev, cpsw_update_vlan_mc, &sync_ctx);
	अगर (sync_ctx.consumed < num && !ret)
		ret = cpsw_set_mc(ndev, addr, -1, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_del_mc_addr(काष्ठा net_device *ndev, स्थिर u8 *addr, पूर्णांक num)
अणु
	काष्ठा addr_sync_ctx sync_ctx;

	sync_ctx.consumed = 0;
	sync_ctx.addr = addr;
	sync_ctx.ndev = ndev;
	sync_ctx.flush = 1;

	vlan_क्रम_each(ndev, cpsw_update_vlan_mc, &sync_ctx);
	अगर (sync_ctx.consumed == num)
		cpsw_set_mc(ndev, addr, -1, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_purge_vlan_mc(काष्ठा net_device *vdev, पूर्णांक vid, व्योम *ctx)
अणु
	काष्ठा addr_sync_ctx *sync_ctx = ctx;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक found = 0;

	अगर (!vdev || !(vdev->flags & IFF_UP))
		वापस 0;

	/* vlan address is relevant अगर its sync_cnt != 0 */
	netdev_क्रम_each_mc_addr(ha, vdev) अणु
		अगर (ether_addr_equal(ha->addr, sync_ctx->addr)) अणु
			found = ha->sync_cnt;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस 0;

	sync_ctx->consumed++;
	cpsw_set_mc(sync_ctx->ndev, sync_ctx->addr, vid, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_purge_all_mc(काष्ठा net_device *ndev, स्थिर u8 *addr, पूर्णांक num)
अणु
	काष्ठा addr_sync_ctx sync_ctx;

	sync_ctx.addr = addr;
	sync_ctx.ndev = ndev;
	sync_ctx.consumed = 0;

	vlan_क्रम_each(ndev, cpsw_purge_vlan_mc, &sync_ctx);
	अगर (sync_ctx.consumed < num)
		cpsw_set_mc(ndev, addr, -1, 0);

	वापस 0;
पूर्ण

अटल व्योम cpsw_nकरो_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक slave_port = -1;

	अगर (cpsw->data.dual_emac)
		slave_port = priv->emac_port + 1;

	अगर (ndev->flags & IFF_PROMISC) अणु
		/* Enable promiscuous mode */
		cpsw_set_promiscious(ndev, true);
		cpsw_ale_set_allmulti(cpsw->ale, IFF_ALLMULTI, slave_port);
		वापस;
	पूर्ण अन्यथा अणु
		/* Disable promiscuous mode */
		cpsw_set_promiscious(ndev, false);
	पूर्ण

	/* Restore allmulti on vlans अगर necessary */
	cpsw_ale_set_allmulti(cpsw->ale,
			      ndev->flags & IFF_ALLMULTI, slave_port);

	/* add/हटाओ mcast address either क्रम real netdev or क्रम vlan */
	__hw_addr_ref_sync_dev(&ndev->mc, ndev, cpsw_add_mc_addr,
			       cpsw_del_mc_addr);
पूर्ण

अटल अचिन्हित पूर्णांक cpsw_rxbuf_total_len(अचिन्हित पूर्णांक len)
अणु
	len += CPSW_HEADROOM;
	len += SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	वापस SKB_DATA_ALIGN(len);
पूर्ण

अटल व्योम cpsw_rx_handler(व्योम *token, पूर्णांक len, पूर्णांक status)
अणु
	काष्ठा page		*new_page, *page = token;
	व्योम			*pa = page_address(page);
	काष्ठा cpsw_meta_xdp	*xmeta = pa + CPSW_XMETA_OFFSET;
	काष्ठा cpsw_common	*cpsw = ndev_to_cpsw(xmeta->ndev);
	पूर्णांक			pkt_size = cpsw->rx_packet_max;
	पूर्णांक			ret = 0, port, ch = xmeta->ch;
	पूर्णांक			headroom = CPSW_HEADROOM;
	काष्ठा net_device	*ndev = xmeta->ndev;
	काष्ठा cpsw_priv	*priv;
	काष्ठा page_pool	*pool;
	काष्ठा sk_buff		*skb;
	काष्ठा xdp_buff		xdp;
	dma_addr_t		dma;

	अगर (cpsw->data.dual_emac && status >= 0) अणु
		port = CPDMA_RX_SOURCE_PORT(status);
		अगर (port)
			ndev = cpsw->slaves[--port].ndev;
	पूर्ण

	priv = netdev_priv(ndev);
	pool = cpsw->page_pool[ch];
	अगर (unlikely(status < 0) || unlikely(!netअगर_running(ndev))) अणु
		/* In dual emac mode check क्रम all पूर्णांकerfaces */
		अगर (cpsw->data.dual_emac && cpsw->usage_count &&
		    (status >= 0)) अणु
			/* The packet received is क्रम the पूर्णांकerface which
			 * is alपढ़ोy करोwn and the other पूर्णांकerface is up
			 * and running, instead of मुक्तing which results
			 * in reducing of the number of rx descriptor in
			 * DMA engine, requeue page back to cpdma.
			 */
			new_page = page;
			जाओ requeue;
		पूर्ण

		/* the पूर्णांकerface is going करोwn, pages are purged */
		page_pool_recycle_direct(pool, page);
		वापस;
	पूर्ण

	new_page = page_pool_dev_alloc_pages(pool);
	अगर (unlikely(!new_page)) अणु
		new_page = page;
		ndev->stats.rx_dropped++;
		जाओ requeue;
	पूर्ण

	अगर (priv->xdp_prog) अणु
		पूर्णांक headroom = CPSW_HEADROOM, size = len;

		xdp_init_buff(&xdp, PAGE_SIZE, &priv->xdp_rxq[ch]);
		अगर (status & CPDMA_RX_VLAN_ENCAP) अणु
			headroom += CPSW_RX_VLAN_ENCAP_HDR_SIZE;
			size -= CPSW_RX_VLAN_ENCAP_HDR_SIZE;
		पूर्ण

		xdp_prepare_buff(&xdp, pa, headroom, size, false);

		port = priv->emac_port + cpsw->data.dual_emac;
		ret = cpsw_run_xdp(priv, ch, &xdp, page, port, &len);
		अगर (ret != CPSW_XDP_PASS)
			जाओ requeue;

		headroom = xdp.data - xdp.data_hard_start;

		/* XDP prog can modअगरy vlan tag, so can't use encap header */
		status &= ~CPDMA_RX_VLAN_ENCAP;
	पूर्ण

	/* pass skb to netstack अगर no XDP prog or वापसed XDP_PASS */
	skb = build_skb(pa, cpsw_rxbuf_total_len(pkt_size));
	अगर (!skb) अणु
		ndev->stats.rx_dropped++;
		page_pool_recycle_direct(pool, page);
		जाओ requeue;
	पूर्ण

	skb_reserve(skb, headroom);
	skb_put(skb, len);
	skb->dev = ndev;
	अगर (status & CPDMA_RX_VLAN_ENCAP)
		cpsw_rx_vlan_encap(skb);
	अगर (priv->rx_ts_enabled)
		cpts_rx_बारtamp(cpsw->cpts, skb);
	skb->protocol = eth_type_trans(skb, ndev);

	/* unmap page as no netstack skb page recycling */
	page_pool_release_page(pool, page);
	netअगर_receive_skb(skb);

	ndev->stats.rx_bytes += len;
	ndev->stats.rx_packets++;

requeue:
	xmeta = page_address(new_page) + CPSW_XMETA_OFFSET;
	xmeta->ndev = ndev;
	xmeta->ch = ch;

	dma = page_pool_get_dma_addr(new_page) + CPSW_HEADROOM;
	ret = cpdma_chan_submit_mapped(cpsw->rxv[ch].ch, new_page, dma,
				       pkt_size, 0);
	अगर (ret < 0) अणु
		WARN_ON(ret == -ENOMEM);
		page_pool_recycle_direct(pool, new_page);
	पूर्ण
पूर्ण

अटल व्योम _cpsw_adjust_link(काष्ठा cpsw_slave *slave,
			      काष्ठा cpsw_priv *priv, bool *link)
अणु
	काष्ठा phy_device	*phy = slave->phy;
	u32			mac_control = 0;
	u32			slave_port;
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	अगर (!phy)
		वापस;

	slave_port = cpsw_get_slave_port(slave->slave_num);

	अगर (phy->link) अणु
		mac_control = CPSW_SL_CTL_GMII_EN;

		अगर (phy->speed == 1000)
			mac_control |= CPSW_SL_CTL_GIG;
		अगर (phy->duplex)
			mac_control |= CPSW_SL_CTL_FULLDUPLEX;

		/* set speed_in input in हाल RMII mode is used in 100Mbps */
		अगर (phy->speed == 100)
			mac_control |= CPSW_SL_CTL_IFCTL_A;
		/* in band mode only works in 10Mbps RGMII mode */
		अन्यथा अगर ((phy->speed == 10) && phy_पूर्णांकerface_is_rgmii(phy))
			mac_control |= CPSW_SL_CTL_EXT_EN; /* In Band mode */

		अगर (priv->rx_छोड़ो)
			mac_control |= CPSW_SL_CTL_RX_FLOW_EN;

		अगर (priv->tx_छोड़ो)
			mac_control |= CPSW_SL_CTL_TX_FLOW_EN;

		अगर (mac_control != slave->mac_control)
			cpsw_sl_ctl_set(slave->mac_sl, mac_control);

		/* enable क्रमwarding */
		cpsw_ale_control_set(cpsw->ale, slave_port,
				     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

		*link = true;

		अगर (priv->shp_cfg_speed &&
		    priv->shp_cfg_speed != slave->phy->speed &&
		    !cpsw_shp_is_off(priv))
			dev_warn(priv->dev,
				 "Speed was changed, CBS shaper speeds are changed!");
	पूर्ण अन्यथा अणु
		mac_control = 0;
		/* disable क्रमwarding */
		cpsw_ale_control_set(cpsw->ale, slave_port,
				     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);

		cpsw_sl_रुको_क्रम_idle(slave->mac_sl, 100);

		cpsw_sl_ctl_reset(slave->mac_sl);
	पूर्ण

	अगर (mac_control != slave->mac_control)
		phy_prपूर्णांक_status(phy);

	slave->mac_control = mac_control;
पूर्ण

अटल व्योम cpsw_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv	*priv = netdev_priv(ndev);
	काष्ठा cpsw_common	*cpsw = priv->cpsw;
	bool			link = false;

	क्रम_each_slave(priv, _cpsw_adjust_link, priv, &link);

	अगर (link) अणु
		अगर (cpsw_need_resplit(cpsw))
			cpsw_split_res(cpsw);

		netअगर_carrier_on(ndev);
		अगर (netअगर_running(ndev))
			netअगर_tx_wake_all_queues(ndev);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(ndev);
		netअगर_tx_stop_all_queues(ndev);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpsw_add_dual_emac_def_ale_entries(
		काष्ठा cpsw_priv *priv, काष्ठा cpsw_slave *slave,
		u32 slave_port)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	u32 port_mask = 1 << slave_port | ALE_PORT_HOST;

	अगर (cpsw->version == CPSW_VERSION_1)
		slave_ग_लिखो(slave, slave->port_vlan, CPSW1_PORT_VLAN);
	अन्यथा
		slave_ग_लिखो(slave, slave->port_vlan, CPSW2_PORT_VLAN);
	cpsw_ale_add_vlan(cpsw->ale, slave->port_vlan, port_mask,
			  port_mask, port_mask, 0);
	cpsw_ale_add_mcast(cpsw->ale, priv->ndev->broadcast,
			   ALE_PORT_HOST, ALE_VLAN, slave->port_vlan, 0);
	cpsw_ale_add_ucast(cpsw->ale, priv->mac_addr,
			   HOST_PORT_NUM, ALE_VLAN |
			   ALE_SECURE, slave->port_vlan);
	cpsw_ale_control_set(cpsw->ale, slave_port,
			     ALE_PORT_DROP_UNKNOWN_VLAN, 1);
पूर्ण

अटल व्योम cpsw_slave_खोलो(काष्ठा cpsw_slave *slave, काष्ठा cpsw_priv *priv)
अणु
	u32 slave_port;
	काष्ठा phy_device *phy;
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	cpsw_sl_reset(slave->mac_sl, 100);
	cpsw_sl_ctl_reset(slave->mac_sl);

	/* setup priority mapping */
	cpsw_sl_reg_ग_लिखो(slave->mac_sl, CPSW_SL_RX_PRI_MAP,
			  RX_PRIORITY_MAPPING);

	चयन (cpsw->version) अणु
	हाल CPSW_VERSION_1:
		slave_ग_लिखो(slave, TX_PRIORITY_MAPPING, CPSW1_TX_PRI_MAP);
		/* Increase RX FIFO size to 5 क्रम supporting fullduplex
		 * flow control mode
		 */
		slave_ग_लिखो(slave,
			    (CPSW_MAX_BLKS_TX << CPSW_MAX_BLKS_TX_SHIFT) |
			    CPSW_MAX_BLKS_RX, CPSW1_MAX_BLKS);
		अवरोध;
	हाल CPSW_VERSION_2:
	हाल CPSW_VERSION_3:
	हाल CPSW_VERSION_4:
		slave_ग_लिखो(slave, TX_PRIORITY_MAPPING, CPSW2_TX_PRI_MAP);
		/* Increase RX FIFO size to 5 क्रम supporting fullduplex
		 * flow control mode
		 */
		slave_ग_लिखो(slave,
			    (CPSW_MAX_BLKS_TX << CPSW_MAX_BLKS_TX_SHIFT) |
			    CPSW_MAX_BLKS_RX, CPSW2_MAX_BLKS);
		अवरोध;
	पूर्ण

	/* setup max packet size, and mac address */
	cpsw_sl_reg_ग_लिखो(slave->mac_sl, CPSW_SL_RX_MAXLEN,
			  cpsw->rx_packet_max);
	cpsw_set_slave_mac(slave, priv);

	slave->mac_control = 0;	/* no link yet */

	slave_port = cpsw_get_slave_port(slave->slave_num);

	अगर (cpsw->data.dual_emac)
		cpsw_add_dual_emac_def_ale_entries(priv, slave, slave_port);
	अन्यथा
		cpsw_ale_add_mcast(cpsw->ale, priv->ndev->broadcast,
				   1 << slave_port, 0, 0, ALE_MCAST_FWD_2);

	अगर (slave->data->phy_node) अणु
		phy = of_phy_connect(priv->ndev, slave->data->phy_node,
				 &cpsw_adjust_link, 0, slave->data->phy_अगर);
		अगर (!phy) अणु
			dev_err(priv->dev, "phy \"%pOF\" not found on slave %d\n",
				slave->data->phy_node,
				slave->slave_num);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		phy = phy_connect(priv->ndev, slave->data->phy_id,
				 &cpsw_adjust_link, slave->data->phy_अगर);
		अगर (IS_ERR(phy)) अणु
			dev_err(priv->dev,
				"phy \"%s\" not found on slave %d, err %ld\n",
				slave->data->phy_id, slave->slave_num,
				PTR_ERR(phy));
			वापस;
		पूर्ण
	पूर्ण

	slave->phy = phy;

	phy_attached_info(slave->phy);

	phy_start(slave->phy);

	/* Configure GMII_SEL रेजिस्टर */
	अगर (!IS_ERR(slave->data->अगरphy))
		phy_set_mode_ext(slave->data->अगरphy, PHY_MODE_ETHERNET,
				 slave->data->phy_अगर);
	अन्यथा
		cpsw_phy_sel(cpsw->dev, slave->phy->पूर्णांकerface,
			     slave->slave_num);
पूर्ण

अटल अंतरभूत व्योम cpsw_add_शेष_vlan(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	स्थिर पूर्णांक vlan = cpsw->data.शेष_vlan;
	u32 reg;
	पूर्णांक i;
	पूर्णांक unreg_mcast_mask;

	reg = (cpsw->version == CPSW_VERSION_1) ? CPSW1_PORT_VLAN :
	       CPSW2_PORT_VLAN;

	ग_लिखोl(vlan, &cpsw->host_port_regs->port_vlan);

	क्रम (i = 0; i < cpsw->data.slaves; i++)
		slave_ग_लिखो(cpsw->slaves + i, vlan, reg);

	अगर (priv->ndev->flags & IFF_ALLMULTI)
		unreg_mcast_mask = ALE_ALL_PORTS;
	अन्यथा
		unreg_mcast_mask = ALE_PORT_1 | ALE_PORT_2;

	cpsw_ale_add_vlan(cpsw->ale, vlan, ALE_ALL_PORTS,
			  ALE_ALL_PORTS, ALE_ALL_PORTS,
			  unreg_mcast_mask);
पूर्ण

अटल व्योम cpsw_init_host_port(काष्ठा cpsw_priv *priv)
अणु
	u32 fअगरo_mode;
	u32 control_reg;
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	/* soft reset the controller and initialize ale */
	soft_reset("cpsw", &cpsw->regs->soft_reset);
	cpsw_ale_start(cpsw->ale);

	/* चयन to vlan unaware mode */
	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_VLAN_AWARE,
			     CPSW_ALE_VLAN_AWARE);
	control_reg = पढ़ोl(&cpsw->regs->control);
	control_reg |= CPSW_VLAN_AWARE | CPSW_RX_VLAN_ENCAP;
	ग_लिखोl(control_reg, &cpsw->regs->control);
	fअगरo_mode = (cpsw->data.dual_emac) ? CPSW_FIFO_DUAL_MAC_MODE :
		     CPSW_FIFO_NORMAL_MODE;
	ग_लिखोl(fअगरo_mode, &cpsw->host_port_regs->tx_in_ctl);

	/* setup host port priority mapping */
	ग_लिखोl_relaxed(CPDMA_TX_PRIORITY_MAP,
		       &cpsw->host_port_regs->cpdma_tx_pri_map);
	ग_लिखोl_relaxed(0, &cpsw->host_port_regs->cpdma_rx_chan_map);

	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM,
			     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

	अगर (!cpsw->data.dual_emac) अणु
		cpsw_ale_add_ucast(cpsw->ale, priv->mac_addr, HOST_PORT_NUM,
				   0, 0);
		cpsw_ale_add_mcast(cpsw->ale, priv->ndev->broadcast,
				   ALE_PORT_HOST, 0, 0, ALE_MCAST_FWD_2);
	पूर्ण
पूर्ण

अटल व्योम cpsw_slave_stop(काष्ठा cpsw_slave *slave, काष्ठा cpsw_common *cpsw)
अणु
	u32 slave_port;

	slave_port = cpsw_get_slave_port(slave->slave_num);

	अगर (!slave->phy)
		वापस;
	phy_stop(slave->phy);
	phy_disconnect(slave->phy);
	slave->phy = शून्य;
	cpsw_ale_control_set(cpsw->ale, slave_port,
			     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);
	cpsw_sl_reset(slave->mac_sl, 100);
	cpsw_sl_ctl_reset(slave->mac_sl);
पूर्ण

अटल पूर्णांक cpsw_restore_vlans(काष्ठा net_device *vdev, पूर्णांक vid, व्योम *arg)
अणु
	काष्ठा cpsw_priv *priv = arg;

	अगर (!vdev)
		वापस 0;

	cpsw_nकरो_vlan_rx_add_vid(priv->ndev, 0, vid);
	वापस 0;
पूर्ण

/* restore resources after port reset */
अटल व्योम cpsw_restore(काष्ठा cpsw_priv *priv)
अणु
	/* restore vlan configurations */
	vlan_क्रम_each(priv->ndev, cpsw_restore_vlans, priv);

	/* restore MQPRIO offload */
	क्रम_each_slave(priv, cpsw_mqprio_resume, priv);

	/* restore CBS offload */
	क्रम_each_slave(priv, cpsw_cbs_resume, priv);
पूर्ण

अटल पूर्णांक cpsw_nकरो_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक ret;
	u32 reg;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	netअगर_carrier_off(ndev);

	/* Notअगरy the stack of the actual queue counts. */
	ret = netअगर_set_real_num_tx_queues(ndev, cpsw->tx_ch_num);
	अगर (ret) अणु
		dev_err(priv->dev, "cannot set real number of tx queues\n");
		जाओ err_cleanup;
	पूर्ण

	ret = netअगर_set_real_num_rx_queues(ndev, cpsw->rx_ch_num);
	अगर (ret) अणु
		dev_err(priv->dev, "cannot set real number of rx queues\n");
		जाओ err_cleanup;
	पूर्ण

	reg = cpsw->version;

	dev_info(priv->dev, "initializing cpsw version %d.%d (%d)\n",
		 CPSW_MAJOR_VERSION(reg), CPSW_MINOR_VERSION(reg),
		 CPSW_RTL_VERSION(reg));

	/* Initialize host and slave ports */
	अगर (!cpsw->usage_count)
		cpsw_init_host_port(priv);
	क्रम_each_slave(priv, cpsw_slave_खोलो, priv);

	/* Add शेष VLAN */
	अगर (!cpsw->data.dual_emac)
		cpsw_add_शेष_vlan(priv);
	अन्यथा
		cpsw_ale_add_vlan(cpsw->ale, cpsw->data.शेष_vlan,
				  ALE_ALL_PORTS, ALE_ALL_PORTS, 0, 0);

	/* initialize shared resources क्रम every ndev */
	अगर (!cpsw->usage_count) अणु
		/* disable priority elevation */
		ग_लिखोl_relaxed(0, &cpsw->regs->ptype);

		/* enable statistics collection only on all ports */
		ग_लिखोl_relaxed(0x7, &cpsw->regs->stat_port_en);

		/* Enable पूर्णांकernal fअगरo flow control */
		ग_लिखोl(0x7, &cpsw->regs->flow_control);

		napi_enable(&cpsw->napi_rx);
		napi_enable(&cpsw->napi_tx);

		अगर (cpsw->tx_irq_disabled) अणु
			cpsw->tx_irq_disabled = false;
			enable_irq(cpsw->irqs_table[1]);
		पूर्ण

		अगर (cpsw->rx_irq_disabled) अणु
			cpsw->rx_irq_disabled = false;
			enable_irq(cpsw->irqs_table[0]);
		पूर्ण

		/* create rxqs क्रम both infs in dual mac as they use same pool
		 * and must be destroyed together when no users.
		 */
		ret = cpsw_create_xdp_rxqs(cpsw);
		अगर (ret < 0)
			जाओ err_cleanup;

		ret = cpsw_fill_rx_channels(priv);
		अगर (ret < 0)
			जाओ err_cleanup;

		अगर (cpsw->cpts) अणु
			अगर (cpts_रेजिस्टर(cpsw->cpts))
				dev_err(priv->dev, "error registering cpts device\n");
			अन्यथा
				ग_लिखोl(0x10, &cpsw->wr_regs->misc_en);
		पूर्ण
	पूर्ण

	cpsw_restore(priv);

	/* Enable Interrupt pacing अगर configured */
	अगर (cpsw->coal_पूर्णांकvl != 0) अणु
		काष्ठा ethtool_coalesce coal;

		coal.rx_coalesce_usecs = cpsw->coal_पूर्णांकvl;
		cpsw_set_coalesce(ndev, &coal);
	पूर्ण

	cpdma_ctlr_start(cpsw->dma);
	cpsw_पूर्णांकr_enable(cpsw);
	cpsw->usage_count++;

	वापस 0;

err_cleanup:
	अगर (!cpsw->usage_count) अणु
		cpdma_ctlr_stop(cpsw->dma);
		cpsw_destroy_xdp_rxqs(cpsw);
	पूर्ण

	क्रम_each_slave(priv, cpsw_slave_stop, cpsw);
	pm_runसमय_put_sync(cpsw->dev);
	netअगर_carrier_off(priv->ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_nकरो_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	cpsw_info(priv, अगरकरोwn, "shutting down cpsw device\n");
	__hw_addr_ref_unsync_dev(&ndev->mc, ndev, cpsw_purge_all_mc);
	netअगर_tx_stop_all_queues(priv->ndev);
	netअगर_carrier_off(priv->ndev);

	अगर (cpsw->usage_count <= 1) अणु
		napi_disable(&cpsw->napi_rx);
		napi_disable(&cpsw->napi_tx);
		cpts_unरेजिस्टर(cpsw->cpts);
		cpsw_पूर्णांकr_disable(cpsw);
		cpdma_ctlr_stop(cpsw->dma);
		cpsw_ale_stop(cpsw->ale);
		cpsw_destroy_xdp_rxqs(cpsw);
	पूर्ण
	क्रम_each_slave(priv, cpsw_slave_stop, cpsw);

	अगर (cpsw_need_resplit(cpsw))
		cpsw_split_res(cpsw);

	cpsw->usage_count--;
	pm_runसमय_put_sync(cpsw->dev);
	वापस 0;
पूर्ण

अटल netdev_tx_t cpsw_nकरो_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpts *cpts = cpsw->cpts;
	काष्ठा netdev_queue *txq;
	काष्ठा cpdma_chan *txch;
	पूर्णांक ret, q_idx;

	अगर (skb_padto(skb, CPSW_MIN_PACKET_SIZE)) अणु
		cpsw_err(priv, tx_err, "packet pad failed\n");
		ndev->stats.tx_dropped++;
		वापस NET_XMIT_DROP;
	पूर्ण

	अगर (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP &&
	    priv->tx_ts_enabled && cpts_can_बारtamp(cpts, skb))
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	q_idx = skb_get_queue_mapping(skb);
	अगर (q_idx >= cpsw->tx_ch_num)
		q_idx = q_idx % cpsw->tx_ch_num;

	txch = cpsw->txv[q_idx].ch;
	txq = netdev_get_tx_queue(ndev, q_idx);
	skb_tx_बारtamp(skb);
	ret = cpdma_chan_submit(txch, skb, skb->data, skb->len,
				priv->emac_port + cpsw->data.dual_emac);
	अगर (unlikely(ret != 0)) अणु
		cpsw_err(priv, tx_err, "desc submit failed\n");
		जाओ fail;
	पूर्ण

	/* If there is no more tx desc left मुक्त then we need to
	 * tell the kernel to stop sending us tx frames.
	 */
	अगर (unlikely(!cpdma_check_मुक्त_tx_desc(txch))) अणु
		netअगर_tx_stop_queue(txq);

		/* Barrier, so that stop_queue visible to other cpus */
		smp_mb__after_atomic();

		अगर (cpdma_check_मुक्त_tx_desc(txch))
			netअगर_tx_wake_queue(txq);
	पूर्ण

	वापस NETDEV_TX_OK;
fail:
	ndev->stats.tx_dropped++;
	netअगर_tx_stop_queue(txq);

	/* Barrier, so that stop_queue visible to other cpus */
	smp_mb__after_atomic();

	अगर (cpdma_check_मुक्त_tx_desc(txch))
		netअगर_tx_wake_queue(txq);

	वापस NETDEV_TX_BUSY;
पूर्ण

अटल पूर्णांक cpsw_nकरो_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)p;
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक flags = 0;
	u16 vid = 0;
	पूर्णांक ret;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	अगर (cpsw->data.dual_emac) अणु
		vid = cpsw->slaves[priv->emac_port].port_vlan;
		flags = ALE_VLAN;
	पूर्ण

	cpsw_ale_del_ucast(cpsw->ale, priv->mac_addr, HOST_PORT_NUM,
			   flags, vid);
	cpsw_ale_add_ucast(cpsw->ale, addr->sa_data, HOST_PORT_NUM,
			   flags, vid);

	स_नकल(priv->mac_addr, addr->sa_data, ETH_ALEN);
	स_नकल(ndev->dev_addr, priv->mac_addr, ETH_ALEN);
	क्रम_each_slave(priv, cpsw_set_slave_mac, priv);

	pm_runसमय_put(cpsw->dev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpsw_add_vlan_ale_entry(काष्ठा cpsw_priv *priv,
				अचिन्हित लघु vid)
अणु
	पूर्णांक ret;
	पूर्णांक unreg_mcast_mask = 0;
	पूर्णांक mcast_mask;
	u32 port_mask;
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	अगर (cpsw->data.dual_emac) अणु
		port_mask = (1 << (priv->emac_port + 1)) | ALE_PORT_HOST;

		mcast_mask = ALE_PORT_HOST;
		अगर (priv->ndev->flags & IFF_ALLMULTI)
			unreg_mcast_mask = mcast_mask;
	पूर्ण अन्यथा अणु
		port_mask = ALE_ALL_PORTS;
		mcast_mask = port_mask;

		अगर (priv->ndev->flags & IFF_ALLMULTI)
			unreg_mcast_mask = ALE_ALL_PORTS;
		अन्यथा
			unreg_mcast_mask = ALE_PORT_1 | ALE_PORT_2;
	पूर्ण

	ret = cpsw_ale_add_vlan(cpsw->ale, vid, port_mask, 0, port_mask,
				unreg_mcast_mask);
	अगर (ret != 0)
		वापस ret;

	ret = cpsw_ale_add_ucast(cpsw->ale, priv->mac_addr,
				 HOST_PORT_NUM, ALE_VLAN, vid);
	अगर (ret != 0)
		जाओ clean_vid;

	ret = cpsw_ale_add_mcast(cpsw->ale, priv->ndev->broadcast,
				 mcast_mask, ALE_VLAN, vid, 0);
	अगर (ret != 0)
		जाओ clean_vlan_ucast;
	वापस 0;

clean_vlan_ucast:
	cpsw_ale_del_ucast(cpsw->ale, priv->mac_addr,
			   HOST_PORT_NUM, ALE_VLAN, vid);
clean_vid:
	cpsw_ale_del_vlan(cpsw->ale, vid, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_nकरो_vlan_rx_add_vid(काष्ठा net_device *ndev,
				    __be16 proto, u16 vid)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक ret;

	अगर (vid == cpsw->data.शेष_vlan)
		वापस 0;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	अगर (cpsw->data.dual_emac) अणु
		/* In dual EMAC, reserved VLAN id should not be used क्रम
		 * creating VLAN पूर्णांकerfaces as this can अवरोध the dual
		 * EMAC port separation
		 */
		पूर्णांक i;

		क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
			अगर (vid == cpsw->slaves[i].port_vlan) अणु
				ret = -EINVAL;
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_info(priv->dev, "Adding vlanid %d to vlan filter\n", vid);
	ret = cpsw_add_vlan_ale_entry(priv, vid);
err:
	pm_runसमय_put(cpsw->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_nकरो_vlan_rx_समाप्त_vid(काष्ठा net_device *ndev,
				     __be16 proto, u16 vid)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक ret;

	अगर (vid == cpsw->data.शेष_vlan)
		वापस 0;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	अगर (cpsw->data.dual_emac) अणु
		पूर्णांक i;

		क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
			अगर (vid == cpsw->slaves[i].port_vlan)
				जाओ err;
		पूर्ण
	पूर्ण

	dev_info(priv->dev, "removing vlanid %d from vlan filter\n", vid);
	ret = cpsw_ale_del_vlan(cpsw->ale, vid, 0);
	ret |= cpsw_ale_del_ucast(cpsw->ale, priv->mac_addr,
				  HOST_PORT_NUM, ALE_VLAN, vid);
	ret |= cpsw_ale_del_mcast(cpsw->ale, priv->ndev->broadcast,
				  0, ALE_VLAN, vid);
	ret |= cpsw_ale_flush_multicast(cpsw->ale, ALE_PORT_HOST, vid);
err:
	pm_runसमय_put(cpsw->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_nकरो_xdp_xmit(काष्ठा net_device *ndev, पूर्णांक n,
			     काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा xdp_frame *xdpf;
	पूर्णांक i, nxmit = 0, port;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	क्रम (i = 0; i < n; i++) अणु
		xdpf = frames[i];
		अगर (xdpf->len < CPSW_MIN_PACKET_SIZE)
			अवरोध;

		port = priv->emac_port + cpsw->data.dual_emac;
		अगर (cpsw_xdp_tx_frame(priv, xdpf, शून्य, port))
			अवरोध;
		nxmit++;
	पूर्ण

	वापस nxmit;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम cpsw_nकरो_poll_controller(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

	cpsw_पूर्णांकr_disable(cpsw);
	cpsw_rx_पूर्णांकerrupt(cpsw->irqs_table[0], cpsw);
	cpsw_tx_पूर्णांकerrupt(cpsw->irqs_table[1], cpsw);
	cpsw_पूर्णांकr_enable(cpsw);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops cpsw_netdev_ops = अणु
	.nकरो_खोलो		= cpsw_nकरो_खोलो,
	.nकरो_stop		= cpsw_nकरो_stop,
	.nकरो_start_xmit		= cpsw_nकरो_start_xmit,
	.nकरो_set_mac_address	= cpsw_nकरो_set_mac_address,
	.nकरो_करो_ioctl		= cpsw_nकरो_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= cpsw_nकरो_tx_समयout,
	.nकरो_set_rx_mode	= cpsw_nकरो_set_rx_mode,
	.nकरो_set_tx_maxrate	= cpsw_nकरो_set_tx_maxrate,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cpsw_nकरो_poll_controller,
#पूर्ण_अगर
	.nकरो_vlan_rx_add_vid	= cpsw_nकरो_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= cpsw_nकरो_vlan_rx_समाप्त_vid,
	.nकरो_setup_tc           = cpsw_nकरो_setup_tc,
	.nकरो_bpf		= cpsw_nकरो_bpf,
	.nकरो_xdp_xmit		= cpsw_nकरो_xdp_xmit,
पूर्ण;

अटल व्योम cpsw_get_drvinfo(काष्ठा net_device *ndev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	काष्ठा platक्रमm_device	*pdev = to_platक्रमm_device(cpsw->dev);

	strlcpy(info->driver, "cpsw", माप(info->driver));
	strlcpy(info->version, "1.0", माप(info->version));
	strlcpy(info->bus_info, pdev->name, माप(info->bus_info));
पूर्ण

अटल पूर्णांक cpsw_set_छोड़ोparam(काष्ठा net_device *ndev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	bool link;

	priv->rx_छोड़ो = छोड़ो->rx_छोड़ो ? true : false;
	priv->tx_छोड़ो = छोड़ो->tx_छोड़ो ? true : false;

	क्रम_each_slave(priv, _cpsw_adjust_link, priv, &link);
	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_set_channels(काष्ठा net_device *ndev,
			     काष्ठा ethtool_channels *chs)
अणु
	वापस cpsw_set_channels_common(ndev, chs, cpsw_rx_handler);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops cpsw_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS,
	.get_drvinfo	= cpsw_get_drvinfo,
	.get_msglevel	= cpsw_get_msglevel,
	.set_msglevel	= cpsw_set_msglevel,
	.get_link	= ethtool_op_get_link,
	.get_ts_info	= cpsw_get_ts_info,
	.get_coalesce	= cpsw_get_coalesce,
	.set_coalesce	= cpsw_set_coalesce,
	.get_sset_count		= cpsw_get_sset_count,
	.get_strings		= cpsw_get_strings,
	.get_ethtool_stats	= cpsw_get_ethtool_stats,
	.get_छोड़ोparam		= cpsw_get_छोड़ोparam,
	.set_छोड़ोparam		= cpsw_set_छोड़ोparam,
	.get_wol	= cpsw_get_wol,
	.set_wol	= cpsw_set_wol,
	.get_regs_len	= cpsw_get_regs_len,
	.get_regs	= cpsw_get_regs,
	.begin		= cpsw_ethtool_op_begin,
	.complete	= cpsw_ethtool_op_complete,
	.get_channels	= cpsw_get_channels,
	.set_channels	= cpsw_set_channels,
	.get_link_ksettings	= cpsw_get_link_ksettings,
	.set_link_ksettings	= cpsw_set_link_ksettings,
	.get_eee	= cpsw_get_eee,
	.set_eee	= cpsw_set_eee,
	.nway_reset	= cpsw_nway_reset,
	.get_ringparam = cpsw_get_ringparam,
	.set_ringparam = cpsw_set_ringparam,
पूर्ण;

अटल पूर्णांक cpsw_probe_dt(काष्ठा cpsw_platक्रमm_data *data,
			 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *slave_node;
	पूर्णांक i = 0, ret;
	u32 prop;

	अगर (!node)
		वापस -EINVAL;

	अगर (of_property_पढ़ो_u32(node, "slaves", &prop)) अणु
		dev_err(&pdev->dev, "Missing slaves property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	data->slaves = prop;

	अगर (of_property_पढ़ो_u32(node, "active_slave", &prop)) अणु
		dev_err(&pdev->dev, "Missing active_slave property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	data->active_slave = prop;

	data->slave_data = devm_kसुस्मृति(&pdev->dev,
					data->slaves,
					माप(काष्ठा cpsw_slave_data),
					GFP_KERNEL);
	अगर (!data->slave_data)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(node, "cpdma_channels", &prop)) अणु
		dev_err(&pdev->dev, "Missing cpdma_channels property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	data->channels = prop;

	अगर (of_property_पढ़ो_u32(node, "bd_ram_size", &prop)) अणु
		dev_err(&pdev->dev, "Missing bd_ram_size property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	data->bd_ram_size = prop;

	अगर (of_property_पढ़ो_u32(node, "mac_control", &prop)) अणु
		dev_err(&pdev->dev, "Missing mac_control property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	data->mac_control = prop;

	अगर (of_property_पढ़ो_bool(node, "dual_emac"))
		data->dual_emac = true;

	/*
	 * Populate all the child nodes here...
	 */
	ret = of_platक्रमm_populate(node, शून्य, शून्य, &pdev->dev);
	/* We करो not want to क्रमce this, as in some हालs may not have child */
	अगर (ret)
		dev_warn(&pdev->dev, "Doesn't have any child node\n");

	क्रम_each_available_child_of_node(node, slave_node) अणु
		काष्ठा cpsw_slave_data *slave_data = data->slave_data + i;
		पूर्णांक lenp;
		स्थिर __be32 *parp;

		/* This is no slave child node, जारी */
		अगर (!of_node_name_eq(slave_node, "slave"))
			जारी;

		slave_data->अगरphy = devm_of_phy_get(&pdev->dev, slave_node,
						    शून्य);
		अगर (!IS_ENABLED(CONFIG_TI_CPSW_PHY_SEL) &&
		    IS_ERR(slave_data->अगरphy)) अणु
			ret = PTR_ERR(slave_data->अगरphy);
			dev_err(&pdev->dev,
				"%d: Error retrieving port phy: %d\n", i, ret);
			जाओ err_node_put;
		पूर्ण

		slave_data->slave_node = slave_node;
		slave_data->phy_node = of_parse_phandle(slave_node,
							"phy-handle", 0);
		parp = of_get_property(slave_node, "phy_id", &lenp);
		अगर (slave_data->phy_node) अणु
			dev_dbg(&pdev->dev,
				"slave[%d] using phy-handle=\"%pOF\"\n",
				i, slave_data->phy_node);
		पूर्ण अन्यथा अगर (of_phy_is_fixed_link(slave_node)) अणु
			/* In the हाल of a fixed PHY, the DT node associated
			 * to the PHY is the Ethernet MAC DT node.
			 */
			ret = of_phy_रेजिस्टर_fixed_link(slave_node);
			अगर (ret) अणु
				अगर (ret != -EPROBE_DEFER)
					dev_err(&pdev->dev, "failed to register fixed-link phy: %d\n", ret);
				जाओ err_node_put;
			पूर्ण
			slave_data->phy_node = of_node_get(slave_node);
		पूर्ण अन्यथा अगर (parp) अणु
			u32 phyid;
			काष्ठा device_node *mdio_node;
			काष्ठा platक्रमm_device *mdio;

			अगर (lenp != (माप(__be32) * 2)) अणु
				dev_err(&pdev->dev, "Invalid slave[%d] phy_id property\n", i);
				जाओ no_phy_slave;
			पूर्ण
			mdio_node = of_find_node_by_phandle(be32_to_cpup(parp));
			phyid = be32_to_cpup(parp+1);
			mdio = of_find_device_by_node(mdio_node);
			of_node_put(mdio_node);
			अगर (!mdio) अणु
				dev_err(&pdev->dev, "Missing mdio platform device\n");
				ret = -EINVAL;
				जाओ err_node_put;
			पूर्ण
			snम_लिखो(slave_data->phy_id, माप(slave_data->phy_id),
				 PHY_ID_FMT, mdio->name, phyid);
			put_device(&mdio->dev);
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev,
				"No slave[%d] phy_id, phy-handle, or fixed-link property\n",
				i);
			जाओ no_phy_slave;
		पूर्ण
		ret = of_get_phy_mode(slave_node, &slave_data->phy_अगर);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Missing or malformed slave[%d] phy-mode property\n",
				i);
			जाओ err_node_put;
		पूर्ण

no_phy_slave:
		ret = of_get_mac_address(slave_node, slave_data->mac_addr);
		अगर (ret) अणु
			ret = ti_cm_get_macid(&pdev->dev, i,
					      slave_data->mac_addr);
			अगर (ret)
				जाओ err_node_put;
		पूर्ण
		अगर (data->dual_emac) अणु
			अगर (of_property_पढ़ो_u32(slave_node, "dual_emac_res_vlan",
						 &prop)) अणु
				dev_err(&pdev->dev, "Missing dual_emac_res_vlan in DT.\n");
				slave_data->dual_emac_res_vlan = i+1;
				dev_err(&pdev->dev, "Using %d as Reserved VLAN for %d slave\n",
					slave_data->dual_emac_res_vlan, i);
			पूर्ण अन्यथा अणु
				slave_data->dual_emac_res_vlan = prop;
			पूर्ण
		पूर्ण

		i++;
		अगर (i == data->slaves) अणु
			ret = 0;
			जाओ err_node_put;
		पूर्ण
	पूर्ण

	वापस 0;

err_node_put:
	of_node_put(slave_node);
	वापस ret;
पूर्ण

अटल व्योम cpsw_हटाओ_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpsw_common *cpsw = platक्रमm_get_drvdata(pdev);
	काष्ठा cpsw_platक्रमm_data *data = &cpsw->data;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *slave_node;
	पूर्णांक i = 0;

	क्रम_each_available_child_of_node(node, slave_node) अणु
		काष्ठा cpsw_slave_data *slave_data = &data->slave_data[i];

		अगर (!of_node_name_eq(slave_node, "slave"))
			जारी;

		अगर (of_phy_is_fixed_link(slave_node))
			of_phy_deरेजिस्टर_fixed_link(slave_node);

		of_node_put(slave_data->phy_node);

		i++;
		अगर (i == data->slaves) अणु
			of_node_put(slave_node);
			अवरोध;
		पूर्ण
	पूर्ण

	of_platक्रमm_depopulate(&pdev->dev);
पूर्ण

अटल पूर्णांक cpsw_probe_dual_emac(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common		*cpsw = priv->cpsw;
	काष्ठा cpsw_platक्रमm_data	*data = &cpsw->data;
	काष्ठा net_device		*ndev;
	काष्ठा cpsw_priv		*priv_sl2;
	पूर्णांक ret = 0;

	ndev = devm_alloc_etherdev_mqs(cpsw->dev, माप(काष्ठा cpsw_priv),
				       CPSW_MAX_QUEUES, CPSW_MAX_QUEUES);
	अगर (!ndev) अणु
		dev_err(cpsw->dev, "cpsw: error allocating net_device\n");
		वापस -ENOMEM;
	पूर्ण

	priv_sl2 = netdev_priv(ndev);
	priv_sl2->cpsw = cpsw;
	priv_sl2->ndev = ndev;
	priv_sl2->dev  = &ndev->dev;
	priv_sl2->msg_enable = netअगर_msg_init(debug_level, CPSW_DEBUG);

	अगर (is_valid_ether_addr(data->slave_data[1].mac_addr)) अणु
		स_नकल(priv_sl2->mac_addr, data->slave_data[1].mac_addr,
			ETH_ALEN);
		dev_info(cpsw->dev, "cpsw: Detected MACID = %pM\n",
			 priv_sl2->mac_addr);
	पूर्ण अन्यथा अणु
		eth_अक्रमom_addr(priv_sl2->mac_addr);
		dev_info(cpsw->dev, "cpsw: Random MACID = %pM\n",
			 priv_sl2->mac_addr);
	पूर्ण
	स_नकल(ndev->dev_addr, priv_sl2->mac_addr, ETH_ALEN);

	priv_sl2->emac_port = 1;
	cpsw->slaves[1].ndev = ndev;
	ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_VLAN_CTAG_RX;

	ndev->netdev_ops = &cpsw_netdev_ops;
	ndev->ethtool_ops = &cpsw_ethtool_ops;

	/* रेजिस्टर the network device */
	SET_NETDEV_DEV(ndev, cpsw->dev);
	ndev->dev.of_node = cpsw->slaves[1].data->slave_node;
	ret = रेजिस्टर_netdev(ndev);
	अगर (ret)
		dev_err(cpsw->dev, "cpsw: error registering net device\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id cpsw_of_mtable[] = अणु
	अणु .compatible = "ti,cpsw"पूर्ण,
	अणु .compatible = "ti,am335x-cpsw"पूर्ण,
	अणु .compatible = "ti,am4372-cpsw"पूर्ण,
	अणु .compatible = "ti,dra7-cpsw"पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpsw_of_mtable);

अटल स्थिर काष्ठा soc_device_attribute cpsw_soc_devices[] = अणु
	अणु .family = "AM33xx", .revision = "ES1.0"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक cpsw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device			*dev = &pdev->dev;
	काष्ठा clk			*clk;
	काष्ठा cpsw_platक्रमm_data	*data;
	काष्ठा net_device		*ndev;
	काष्ठा cpsw_priv		*priv;
	व्योम __iomem			*ss_regs;
	काष्ठा resource			*ss_res;
	काष्ठा gpio_descs		*mode;
	स्थिर काष्ठा soc_device_attribute *soc;
	काष्ठा cpsw_common		*cpsw;
	पूर्णांक ret = 0, ch;
	पूर्णांक irq;

	cpsw = devm_kzalloc(dev, माप(काष्ठा cpsw_common), GFP_KERNEL);
	अगर (!cpsw)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, cpsw);
	cpsw_slave_index = cpsw_slave_index_priv;

	cpsw->dev = dev;

	mode = devm_gpiod_get_array_optional(dev, "mode", GPIOD_OUT_LOW);
	अगर (IS_ERR(mode)) अणु
		ret = PTR_ERR(mode);
		dev_err(dev, "gpio request failed, ret %d\n", ret);
		वापस ret;
	पूर्ण

	clk = devm_clk_get(dev, "fck");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		dev_err(dev, "fck is not found %d\n", ret);
		वापस ret;
	पूर्ण
	cpsw->bus_freq_mhz = clk_get_rate(clk) / 1000000;

	ss_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ss_regs = devm_ioremap_resource(dev, ss_res);
	अगर (IS_ERR(ss_regs))
		वापस PTR_ERR(ss_regs);
	cpsw->regs = ss_regs;

	cpsw->wr_regs = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(cpsw->wr_regs))
		वापस PTR_ERR(cpsw->wr_regs);

	/* RX IRQ */
	irq = platक्रमm_get_irq(pdev, 1);
	अगर (irq < 0)
		वापस irq;
	cpsw->irqs_table[0] = irq;

	/* TX IRQ */
	irq = platक्रमm_get_irq(pdev, 2);
	अगर (irq < 0)
		वापस irq;
	cpsw->irqs_table[1] = irq;

	/* get misc irq*/
	irq = platक्रमm_get_irq(pdev, 3);
	अगर (irq <= 0)
		वापस irq;
	cpsw->misc_irq = irq;

	/*
	 * This may be required here क्रम child devices.
	 */
	pm_runसमय_enable(dev);

	/* Need to enable घड़ीs with runसमय PM api to access module
	 * रेजिस्टरs
	 */
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ clean_runसमय_disable_ret;
	पूर्ण

	ret = cpsw_probe_dt(&cpsw->data, pdev);
	अगर (ret)
		जाओ clean_dt_ret;

	soc = soc_device_match(cpsw_soc_devices);
	अगर (soc)
		cpsw->quirk_irq = true;

	data = &cpsw->data;
	cpsw->slaves = devm_kसुस्मृति(dev,
				    data->slaves, माप(काष्ठा cpsw_slave),
				    GFP_KERNEL);
	अगर (!cpsw->slaves) अणु
		ret = -ENOMEM;
		जाओ clean_dt_ret;
	पूर्ण

	cpsw->rx_packet_max = max(rx_packet_max, CPSW_MAX_PACKET_SIZE);
	cpsw->descs_pool_size = descs_pool_size;

	ret = cpsw_init_common(cpsw, ss_regs, ale_ageout,
			       ss_res->start + CPSW2_BD_OFFSET,
			       descs_pool_size);
	अगर (ret)
		जाओ clean_dt_ret;

	ch = cpsw->quirk_irq ? 0 : 7;
	cpsw->txv[0].ch = cpdma_chan_create(cpsw->dma, ch, cpsw_tx_handler, 0);
	अगर (IS_ERR(cpsw->txv[0].ch)) अणु
		dev_err(dev, "error initializing tx dma channel\n");
		ret = PTR_ERR(cpsw->txv[0].ch);
		जाओ clean_cpts;
	पूर्ण

	cpsw->rxv[0].ch = cpdma_chan_create(cpsw->dma, 0, cpsw_rx_handler, 1);
	अगर (IS_ERR(cpsw->rxv[0].ch)) अणु
		dev_err(dev, "error initializing rx dma channel\n");
		ret = PTR_ERR(cpsw->rxv[0].ch);
		जाओ clean_cpts;
	पूर्ण
	cpsw_split_res(cpsw);

	/* setup netdev */
	ndev = devm_alloc_etherdev_mqs(dev, माप(काष्ठा cpsw_priv),
				       CPSW_MAX_QUEUES, CPSW_MAX_QUEUES);
	अगर (!ndev) अणु
		dev_err(dev, "error allocating net_device\n");
		ret = -ENOMEM;
		जाओ clean_cpts;
	पूर्ण

	priv = netdev_priv(ndev);
	priv->cpsw = cpsw;
	priv->ndev = ndev;
	priv->dev  = dev;
	priv->msg_enable = netअगर_msg_init(debug_level, CPSW_DEBUG);
	priv->emac_port = 0;

	अगर (is_valid_ether_addr(data->slave_data[0].mac_addr)) अणु
		स_नकल(priv->mac_addr, data->slave_data[0].mac_addr, ETH_ALEN);
		dev_info(dev, "Detected MACID = %pM\n", priv->mac_addr);
	पूर्ण अन्यथा अणु
		eth_अक्रमom_addr(priv->mac_addr);
		dev_info(dev, "Random MACID = %pM\n", priv->mac_addr);
	पूर्ण

	स_नकल(ndev->dev_addr, priv->mac_addr, ETH_ALEN);

	cpsw->slaves[0].ndev = ndev;

	ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_VLAN_CTAG_RX;

	ndev->netdev_ops = &cpsw_netdev_ops;
	ndev->ethtool_ops = &cpsw_ethtool_ops;
	netअगर_napi_add(ndev, &cpsw->napi_rx,
		       cpsw->quirk_irq ? cpsw_rx_poll : cpsw_rx_mq_poll,
		       CPSW_POLL_WEIGHT);
	netअगर_tx_napi_add(ndev, &cpsw->napi_tx,
			  cpsw->quirk_irq ? cpsw_tx_poll : cpsw_tx_mq_poll,
			  CPSW_POLL_WEIGHT);

	/* रेजिस्टर the network device */
	SET_NETDEV_DEV(ndev, dev);
	ndev->dev.of_node = cpsw->slaves[0].data->slave_node;
	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		dev_err(dev, "error registering net device\n");
		ret = -ENODEV;
		जाओ clean_cpts;
	पूर्ण

	अगर (cpsw->data.dual_emac) अणु
		ret = cpsw_probe_dual_emac(priv);
		अगर (ret) अणु
			cpsw_err(priv, probe, "error probe slave 2 emac interface\n");
			जाओ clean_unरेजिस्टर_netdev_ret;
		पूर्ण
	पूर्ण

	/* Grab RX and TX IRQs. Note that we also have RX_THRESHOLD and
	 * MISC IRQs which are always kept disabled with this driver so
	 * we will not request them.
	 *
	 * If anyone wants to implement support क्रम those, make sure to
	 * first request and append them to irqs_table array.
	 */
	ret = devm_request_irq(dev, cpsw->irqs_table[0], cpsw_rx_पूर्णांकerrupt,
			       0, dev_name(dev), cpsw);
	अगर (ret < 0) अणु
		dev_err(dev, "error attaching irq (%d)\n", ret);
		जाओ clean_unरेजिस्टर_netdev_ret;
	पूर्ण


	ret = devm_request_irq(dev, cpsw->irqs_table[1], cpsw_tx_पूर्णांकerrupt,
			       0, dev_name(&pdev->dev), cpsw);
	अगर (ret < 0) अणु
		dev_err(dev, "error attaching irq (%d)\n", ret);
		जाओ clean_unरेजिस्टर_netdev_ret;
	पूर्ण

	अगर (!cpsw->cpts)
		जाओ skip_cpts;

	ret = devm_request_irq(&pdev->dev, cpsw->misc_irq, cpsw_misc_पूर्णांकerrupt,
			       0, dev_name(&pdev->dev), cpsw);
	अगर (ret < 0) अणु
		dev_err(dev, "error attaching misc irq (%d)\n", ret);
		जाओ clean_unरेजिस्टर_netdev_ret;
	पूर्ण

	/* Enable misc CPTS evnt_pend IRQ */
	cpts_set_irqpoll(cpsw->cpts, false);

skip_cpts:
	cpsw_notice(priv, probe,
		    "initialized device (regs %pa, irq %d, pool size %d)\n",
		    &ss_res->start, cpsw->irqs_table[0], descs_pool_size);

	pm_runसमय_put(&pdev->dev);

	वापस 0;

clean_unरेजिस्टर_netdev_ret:
	unरेजिस्टर_netdev(ndev);
clean_cpts:
	cpts_release(cpsw->cpts);
	cpdma_ctlr_destroy(cpsw->dma);
clean_dt_ret:
	cpsw_हटाओ_dt(pdev);
	pm_runसमय_put_sync(&pdev->dev);
clean_runसमय_disable_ret:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpsw_common *cpsw = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, ret;

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < cpsw->data.slaves; i++)
		अगर (cpsw->slaves[i].ndev)
			unरेजिस्टर_netdev(cpsw->slaves[i].ndev);

	cpts_release(cpsw->cpts);
	cpdma_ctlr_destroy(cpsw->dma);
	cpsw_हटाओ_dt(pdev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cpsw_suspend(काष्ठा device *dev)
अणु
	काष्ठा cpsw_common *cpsw = dev_get_drvdata(dev);
	पूर्णांक i;

	rtnl_lock();

	क्रम (i = 0; i < cpsw->data.slaves; i++)
		अगर (cpsw->slaves[i].ndev)
			अगर (netअगर_running(cpsw->slaves[i].ndev))
				cpsw_nकरो_stop(cpsw->slaves[i].ndev);

	rtnl_unlock();

	/* Select sleep pin state */
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_resume(काष्ठा device *dev)
अणु
	काष्ठा cpsw_common *cpsw = dev_get_drvdata(dev);
	पूर्णांक i;

	/* Select शेष pin state */
	pinctrl_pm_select_शेष_state(dev);

	/* shut up ASSERT_RTNL() warning in netअगर_set_real_num_tx/rx_queues */
	rtnl_lock();

	क्रम (i = 0; i < cpsw->data.slaves; i++)
		अगर (cpsw->slaves[i].ndev)
			अगर (netअगर_running(cpsw->slaves[i].ndev))
				cpsw_nकरो_खोलो(cpsw->slaves[i].ndev);

	rtnl_unlock();

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cpsw_pm_ops, cpsw_suspend, cpsw_resume);

अटल काष्ठा platक्रमm_driver cpsw_driver = अणु
	.driver = अणु
		.name	 = "cpsw",
		.pm	 = &cpsw_pm_ops,
		.of_match_table = cpsw_of_mtable,
	पूर्ण,
	.probe = cpsw_probe,
	.हटाओ = cpsw_हटाओ,
पूर्ण;

module_platक्रमm_driver(cpsw_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cyril Chemparathy <cyril@ti.com>");
MODULE_AUTHOR("Mugunthan V N <mugunthanvnm@ti.com>");
MODULE_DESCRIPTION("TI CPSW Ethernet driver");
