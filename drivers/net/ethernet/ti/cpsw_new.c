<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments Ethernet Switch Driver
 *
 * Copyright (C) 2019 Texas Instruments
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/delay.h>
#समावेश <linux/pinctrl/consumer.h>
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
#समावेश <net/pkt_cls.h>
#समावेश <net/devlink.h>

#समावेश "cpsw.h"
#समावेश "cpsw_ale.h"
#समावेश "cpsw_priv.h"
#समावेश "cpsw_sl.h"
#समावेश "cpsw_switchdev.h"
#समावेश "cpts.h"
#समावेश "davinci_cpdma.h"

#समावेश <net/pkt_sched.h>

अटल पूर्णांक debug_level;
अटल पूर्णांक ale_ageout = CPSW_ALE_AGEOUT_DEFAULT;
अटल पूर्णांक rx_packet_max = CPSW_MAX_PACKET_SIZE;
अटल पूर्णांक descs_pool_size = CPSW_CPDMA_DESCS_POOL_SIZE_DEFAULT;

काष्ठा cpsw_devlink अणु
	काष्ठा cpsw_common *cpsw;
पूर्ण;

क्रमागत cpsw_devlink_param_id अणु
	CPSW_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	CPSW_DL_PARAM_SWITCH_MODE,
	CPSW_DL_PARAM_ALE_BYPASS,
पूर्ण;

/* काष्ठा cpsw_common is not needed, kept here क्रम compatibility
 * reasons witrh the old driver
 */
अटल पूर्णांक cpsw_slave_index_priv(काष्ठा cpsw_common *cpsw,
				 काष्ठा cpsw_priv *priv)
अणु
	अगर (priv->emac_port == HOST_PORT_NUM)
		वापस -1;

	वापस priv->emac_port - 1;
पूर्ण

अटल bool cpsw_is_चयन_en(काष्ठा cpsw_common *cpsw)
अणु
	वापस !cpsw->data.dual_emac;
पूर्ण

अटल व्योम cpsw_set_promiscious(काष्ठा net_device *ndev, bool enable)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	bool enable_uni = false;
	पूर्णांक i;

	अगर (cpsw_is_चयन_en(cpsw))
		वापस;

	/* Enabling promiscuous mode क्रम one पूर्णांकerface will be
	 * common क्रम both the पूर्णांकerface as the पूर्णांकerface shares
	 * the same hardware resource.
	 */
	क्रम (i = 0; i < cpsw->data.slaves; i++)
		अगर (cpsw->slaves[i].ndev &&
		    (cpsw->slaves[i].ndev->flags & IFF_PROMISC))
			enable_uni = true;

	अगर (!enable && enable_uni) अणु
		enable = enable_uni;
		dev_dbg(cpsw->dev, "promiscuity not disabled as the other interface is still in promiscuity mode\n");
	पूर्ण

	अगर (enable) अणु
		/* Enable unknown unicast, reg/unreg mcast */
		cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM,
				     ALE_P0_UNI_FLOOD, 1);

		dev_dbg(cpsw->dev, "promiscuity enabled\n");
	पूर्ण अन्यथा अणु
		/* Disable unknown unicast */
		cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM,
				     ALE_P0_UNI_FLOOD, 0);
		dev_dbg(cpsw->dev, "promiscuity disabled\n");
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
	पूर्णांक mask, flags, ret, slave_no;

	slave_no = cpsw_slave_index(cpsw, priv);
	अगर (vid < 0)
		vid = cpsw->slaves[slave_no].port_vlan;

	mask =  ALE_PORT_HOST;
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

	अगर (ndev->flags & IFF_PROMISC) अणु
		/* Enable promiscuous mode */
		cpsw_set_promiscious(ndev, true);
		cpsw_ale_set_allmulti(cpsw->ale, IFF_ALLMULTI, priv->emac_port);
		वापस;
	पूर्ण

	/* Disable promiscuous mode */
	cpsw_set_promiscious(ndev, false);

	/* Restore allmulti on vlans अगर necessary */
	cpsw_ale_set_allmulti(cpsw->ale,
			      ndev->flags & IFF_ALLMULTI, priv->emac_port);

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
	काष्ठा page *new_page, *page = token;
	व्योम *pa = page_address(page);
	पूर्णांक headroom = CPSW_HEADROOM;
	काष्ठा cpsw_meta_xdp *xmeta;
	काष्ठा cpsw_common *cpsw;
	काष्ठा net_device *ndev;
	पूर्णांक port, ch, pkt_size;
	काष्ठा cpsw_priv *priv;
	काष्ठा page_pool *pool;
	काष्ठा sk_buff *skb;
	काष्ठा xdp_buff xdp;
	पूर्णांक ret = 0;
	dma_addr_t dma;

	xmeta = pa + CPSW_XMETA_OFFSET;
	cpsw = ndev_to_cpsw(xmeta->ndev);
	ndev = xmeta->ndev;
	pkt_size = cpsw->rx_packet_max;
	ch = xmeta->ch;

	अगर (status >= 0) अणु
		port = CPDMA_RX_SOURCE_PORT(status);
		अगर (port)
			ndev = cpsw->slaves[--port].ndev;
	पूर्ण

	priv = netdev_priv(ndev);
	pool = cpsw->page_pool[ch];

	अगर (unlikely(status < 0) || unlikely(!netअगर_running(ndev))) अणु
		/* In dual emac mode check क्रम all पूर्णांकerfaces */
		अगर (cpsw->usage_count && status >= 0) अणु
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

		ret = cpsw_run_xdp(priv, ch, &xdp, page, priv->emac_port, &len);
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

	skb->offload_fwd_mark = priv->offload_fwd_mark;
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

अटल पूर्णांक cpsw_add_vlan_ale_entry(काष्ठा cpsw_priv *priv,
				   अचिन्हित लघु vid)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक unreg_mcast_mask = 0;
	पूर्णांक mcast_mask;
	u32 port_mask;
	पूर्णांक ret;

	port_mask = (1 << priv->emac_port) | ALE_PORT_HOST;

	mcast_mask = ALE_PORT_HOST;
	अगर (priv->ndev->flags & IFF_ALLMULTI)
		unreg_mcast_mask = mcast_mask;

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
	पूर्णांक ret, i;

	अगर (cpsw_is_चयन_en(cpsw)) अणु
		dev_dbg(cpsw->dev, ".ndo_vlan_rx_add_vid called in switch mode\n");
		वापस 0;
	पूर्ण

	अगर (vid == cpsw->data.शेष_vlan)
		वापस 0;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	/* In dual EMAC, reserved VLAN id should not be used क्रम
	 * creating VLAN पूर्णांकerfaces as this can अवरोध the dual
	 * EMAC port separation
	 */
	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		अगर (cpsw->slaves[i].ndev &&
		    vid == cpsw->slaves[i].port_vlan) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	dev_dbg(priv->dev, "Adding vlanid %d to vlan filter\n", vid);
	ret = cpsw_add_vlan_ale_entry(priv, vid);
err:
	pm_runसमय_put(cpsw->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_restore_vlans(काष्ठा net_device *vdev, पूर्णांक vid, व्योम *arg)
अणु
	काष्ठा cpsw_priv *priv = arg;

	अगर (!vdev || !vid)
		वापस 0;

	cpsw_nकरो_vlan_rx_add_vid(priv->ndev, 0, vid);
	वापस 0;
पूर्ण

/* restore resources after port reset */
अटल व्योम cpsw_restore(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	/* restore vlan configurations */
	vlan_क्रम_each(priv->ndev, cpsw_restore_vlans, priv);

	/* restore MQPRIO offload */
	cpsw_mqprio_resume(&cpsw->slaves[priv->emac_port - 1], priv);

	/* restore CBS offload */
	cpsw_cbs_resume(&cpsw->slaves[priv->emac_port - 1], priv);
पूर्ण

अटल व्योम cpsw_init_stp_ale_entry(काष्ठा cpsw_common *cpsw)
अणु
	अक्षर stpa[] = अणु0x01, 0x80, 0xc2, 0x0, 0x0, 0x0पूर्ण;

	cpsw_ale_add_mcast(cpsw->ale, stpa,
			   ALE_PORT_HOST, ALE_SUPER, 0,
			   ALE_MCAST_BLOCK_LEARN_FWD);
पूर्ण

अटल व्योम cpsw_init_host_port_चयन(काष्ठा cpsw_common *cpsw)
अणु
	पूर्णांक vlan = cpsw->data.शेष_vlan;

	ग_लिखोl(CPSW_FIFO_NORMAL_MODE, &cpsw->host_port_regs->tx_in_ctl);

	ग_लिखोl(vlan, &cpsw->host_port_regs->port_vlan);

	cpsw_ale_add_vlan(cpsw->ale, vlan, ALE_ALL_PORTS,
			  ALE_ALL_PORTS, ALE_ALL_PORTS,
			  ALE_PORT_1 | ALE_PORT_2);

	cpsw_init_stp_ale_entry(cpsw);

	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_P0_UNI_FLOOD, 1);
	dev_dbg(cpsw->dev, "Set P0_UNI_FLOOD\n");
	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_PORT_NOLEARN, 0);
पूर्ण

अटल व्योम cpsw_init_host_port_dual_mac(काष्ठा cpsw_common *cpsw)
अणु
	पूर्णांक vlan = cpsw->data.शेष_vlan;

	ग_लिखोl(CPSW_FIFO_DUAL_MAC_MODE, &cpsw->host_port_regs->tx_in_ctl);

	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_P0_UNI_FLOOD, 0);
	dev_dbg(cpsw->dev, "unset P0_UNI_FLOOD\n");

	ग_लिखोl(vlan, &cpsw->host_port_regs->port_vlan);

	cpsw_ale_add_vlan(cpsw->ale, vlan, ALE_ALL_PORTS, ALE_ALL_PORTS, 0, 0);
	/* learning make no sense in dual_mac mode */
	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_PORT_NOLEARN, 1);
पूर्ण

अटल व्योम cpsw_init_host_port(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	u32 control_reg;

	/* soft reset the controller and initialize ale */
	soft_reset("cpsw", &cpsw->regs->soft_reset);
	cpsw_ale_start(cpsw->ale);

	/* चयन to vlan unaware mode */
	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM, ALE_VLAN_AWARE,
			     CPSW_ALE_VLAN_AWARE);
	control_reg = पढ़ोl(&cpsw->regs->control);
	control_reg |= CPSW_VLAN_AWARE | CPSW_RX_VLAN_ENCAP;
	ग_लिखोl(control_reg, &cpsw->regs->control);

	/* setup host port priority mapping */
	ग_लिखोl_relaxed(CPDMA_TX_PRIORITY_MAP,
		       &cpsw->host_port_regs->cpdma_tx_pri_map);
	ग_लिखोl_relaxed(0, &cpsw->host_port_regs->cpdma_rx_chan_map);

	/* disable priority elevation */
	ग_लिखोl_relaxed(0, &cpsw->regs->ptype);

	/* enable statistics collection only on all ports */
	ग_लिखोl_relaxed(0x7, &cpsw->regs->stat_port_en);

	/* Enable पूर्णांकernal fअगरo flow control */
	ग_लिखोl(0x7, &cpsw->regs->flow_control);

	अगर (cpsw_is_चयन_en(cpsw))
		cpsw_init_host_port_चयन(cpsw);
	अन्यथा
		cpsw_init_host_port_dual_mac(cpsw);

	cpsw_ale_control_set(cpsw->ale, HOST_PORT_NUM,
			     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);
पूर्ण

अटल व्योम cpsw_port_add_dual_emac_def_ale_entries(काष्ठा cpsw_priv *priv,
						    काष्ठा cpsw_slave *slave)
अणु
	u32 port_mask = 1 << priv->emac_port | ALE_PORT_HOST;
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	u32 reg;

	reg = (cpsw->version == CPSW_VERSION_1) ? CPSW1_PORT_VLAN :
	       CPSW2_PORT_VLAN;
	slave_ग_लिखो(slave, slave->port_vlan, reg);

	cpsw_ale_add_vlan(cpsw->ale, slave->port_vlan, port_mask,
			  port_mask, port_mask, 0);
	cpsw_ale_add_mcast(cpsw->ale, priv->ndev->broadcast,
			   ALE_PORT_HOST, ALE_VLAN, slave->port_vlan,
			   ALE_MCAST_FWD);
	cpsw_ale_add_ucast(cpsw->ale, priv->mac_addr,
			   HOST_PORT_NUM, ALE_VLAN |
			   ALE_SECURE, slave->port_vlan);
	cpsw_ale_control_set(cpsw->ale, priv->emac_port,
			     ALE_PORT_DROP_UNKNOWN_VLAN, 1);
	/* learning make no sense in dual_mac mode */
	cpsw_ale_control_set(cpsw->ale, priv->emac_port,
			     ALE_PORT_NOLEARN, 1);
पूर्ण

अटल व्योम cpsw_port_add_चयन_def_ale_entries(काष्ठा cpsw_priv *priv,
						 काष्ठा cpsw_slave *slave)
अणु
	u32 port_mask = 1 << priv->emac_port | ALE_PORT_HOST;
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	u32 reg;

	cpsw_ale_control_set(cpsw->ale, priv->emac_port,
			     ALE_PORT_DROP_UNKNOWN_VLAN, 0);
	cpsw_ale_control_set(cpsw->ale, priv->emac_port,
			     ALE_PORT_NOLEARN, 0);
	/* disabling SA_UPDATE required to make stp work, without this setting
	 * Host MAC addresses will jump between ports.
	 * As per TRM MAC address can be defined as unicast supervisory (super)
	 * by setting both (ALE_BLOCKED | ALE_SECURE) which should prevent
	 * SA_UPDATE, but HW seems works incorrectly and setting ALE_SECURE
	 * causes STP packets to be dropped due to ingress filter
	 *	अगर (source address found) and (secure) and
	 *	   (receive port number != port_number))
	 *	   then discard the packet
	 */
	cpsw_ale_control_set(cpsw->ale, priv->emac_port,
			     ALE_PORT_NO_SA_UPDATE, 1);

	cpsw_ale_add_mcast(cpsw->ale, priv->ndev->broadcast,
			   port_mask, ALE_VLAN, slave->port_vlan,
			   ALE_MCAST_FWD_2);
	cpsw_ale_add_ucast(cpsw->ale, priv->mac_addr,
			   HOST_PORT_NUM, ALE_VLAN, slave->port_vlan);

	reg = (cpsw->version == CPSW_VERSION_1) ? CPSW1_PORT_VLAN :
	       CPSW2_PORT_VLAN;
	slave_ग_लिखो(slave, slave->port_vlan, reg);
पूर्ण

अटल व्योम cpsw_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave;
	काष्ठा phy_device *phy;
	u32 mac_control = 0;

	slave = &cpsw->slaves[priv->emac_port - 1];
	phy = slave->phy;

	अगर (!phy)
		वापस;

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
		cpsw_ale_control_set(cpsw->ale, priv->emac_port,
				     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

		netअगर_tx_wake_all_queues(ndev);

		अगर (priv->shp_cfg_speed &&
		    priv->shp_cfg_speed != slave->phy->speed &&
		    !cpsw_shp_is_off(priv))
			dev_warn(priv->dev, "Speed was changed, CBS shaper speeds are changed!");
	पूर्ण अन्यथा अणु
		netअगर_tx_stop_all_queues(ndev);

		mac_control = 0;
		/* disable क्रमwarding */
		cpsw_ale_control_set(cpsw->ale, priv->emac_port,
				     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);

		cpsw_sl_रुको_क्रम_idle(slave->mac_sl, 100);

		cpsw_sl_ctl_reset(slave->mac_sl);
	पूर्ण

	अगर (mac_control != slave->mac_control)
		phy_prपूर्णांक_status(phy);

	slave->mac_control = mac_control;

	अगर (phy->link && cpsw_need_resplit(cpsw))
		cpsw_split_res(cpsw);
पूर्ण

अटल व्योम cpsw_slave_खोलो(काष्ठा cpsw_slave *slave, काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा phy_device *phy;

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

	अगर (cpsw_is_चयन_en(cpsw))
		cpsw_port_add_चयन_def_ale_entries(priv, slave);
	अन्यथा
		cpsw_port_add_dual_emac_def_ale_entries(priv, slave);

	अगर (!slave->data->phy_node)
		dev_err(priv->dev, "no phy found on slave %d\n",
			slave->slave_num);
	phy = of_phy_connect(priv->ndev, slave->data->phy_node,
			     &cpsw_adjust_link, 0, slave->data->phy_अगर);
	अगर (!phy) अणु
		dev_err(priv->dev, "phy \"%pOF\" not found on slave %d\n",
			slave->data->phy_node,
			slave->slave_num);
		वापस;
	पूर्ण
	slave->phy = phy;

	phy_attached_info(slave->phy);

	phy_start(slave->phy);

	/* Configure GMII_SEL रेजिस्टर */
	phy_set_mode_ext(slave->data->अगरphy, PHY_MODE_ETHERNET,
			 slave->data->phy_अगर);
पूर्ण

अटल पूर्णांक cpsw_nकरो_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	काष्ठा cpsw_slave *slave;

	cpsw_info(priv, अगरकरोwn, "shutting down ndev\n");
	slave = &cpsw->slaves[priv->emac_port - 1];
	अगर (slave->phy)
		phy_stop(slave->phy);

	netअगर_tx_stop_all_queues(priv->ndev);

	अगर (slave->phy) अणु
		phy_disconnect(slave->phy);
		slave->phy = शून्य;
	पूर्ण

	__hw_addr_ref_unsync_dev(&ndev->mc, ndev, cpsw_purge_all_mc);

	अगर (cpsw->usage_count <= 1) अणु
		napi_disable(&cpsw->napi_rx);
		napi_disable(&cpsw->napi_tx);
		cpts_unरेजिस्टर(cpsw->cpts);
		cpsw_पूर्णांकr_disable(cpsw);
		cpdma_ctlr_stop(cpsw->dma);
		cpsw_ale_stop(cpsw->ale);
		cpsw_destroy_xdp_rxqs(cpsw);
	पूर्ण

	अगर (cpsw_need_resplit(cpsw))
		cpsw_split_res(cpsw);

	cpsw->usage_count--;
	pm_runसमय_put_sync(cpsw->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_nकरो_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक ret;

	dev_info(priv->dev, "starting ndev. mode: %s\n",
		 cpsw_is_चयन_en(cpsw) ? "switch" : "dual_mac");
	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	/* Notअगरy the stack of the actual queue counts. */
	ret = netअगर_set_real_num_tx_queues(ndev, cpsw->tx_ch_num);
	अगर (ret) अणु
		dev_err(priv->dev, "cannot set real number of tx queues\n");
		जाओ pm_cleanup;
	पूर्ण

	ret = netअगर_set_real_num_rx_queues(ndev, cpsw->rx_ch_num);
	अगर (ret) अणु
		dev_err(priv->dev, "cannot set real number of rx queues\n");
		जाओ pm_cleanup;
	पूर्ण

	/* Initialize host and slave ports */
	अगर (!cpsw->usage_count)
		cpsw_init_host_port(priv);
	cpsw_slave_खोलो(&cpsw->slaves[priv->emac_port - 1], priv);

	/* initialize shared resources क्रम every ndev */
	अगर (!cpsw->usage_count) अणु
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
	cpsw_nकरो_stop(ndev);

pm_cleanup:
	pm_runसमय_put_sync(cpsw->dev);
	वापस ret;
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
				priv->emac_port);
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
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *)p;
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक ret, slave_no;
	पूर्णांक flags = 0;
	u16 vid = 0;

	slave_no = cpsw_slave_index(cpsw, priv);
	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	vid = cpsw->slaves[slave_no].port_vlan;
	flags = ALE_VLAN | ALE_SECURE;

	cpsw_ale_del_ucast(cpsw->ale, priv->mac_addr, HOST_PORT_NUM,
			   flags, vid);
	cpsw_ale_add_ucast(cpsw->ale, addr->sa_data, HOST_PORT_NUM,
			   flags, vid);

	ether_addr_copy(priv->mac_addr, addr->sa_data);
	ether_addr_copy(ndev->dev_addr, priv->mac_addr);
	cpsw_set_slave_mac(&cpsw->slaves[slave_no], priv);

	pm_runसमय_put(cpsw->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_nकरो_vlan_rx_समाप्त_vid(काष्ठा net_device *ndev,
				     __be16 proto, u16 vid)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (cpsw_is_चयन_en(cpsw)) अणु
		dev_dbg(cpsw->dev, "ndo del vlan is called in switch mode\n");
		वापस 0;
	पूर्ण

	अगर (vid == cpsw->data.शेष_vlan)
		वापस 0;

	ret = pm_runसमय_get_sync(cpsw->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(cpsw->dev);
		वापस ret;
	पूर्ण

	/* reset the वापस code as pm_runसमय_get_sync() can वापस
	 * non zero values as well.
	 */
	ret = 0;
	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		अगर (cpsw->slaves[i].ndev &&
		    vid == cpsw->slaves[i].port_vlan) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	dev_dbg(priv->dev, "removing vlanid %d from vlan filter\n", vid);
	ret = cpsw_ale_del_vlan(cpsw->ale, vid, 0);
	अगर (ret)
		dev_err(priv->dev, "cpsw_ale_del_vlan() failed: ret %d\n", ret);
	ret = cpsw_ale_del_ucast(cpsw->ale, priv->mac_addr,
				 HOST_PORT_NUM, ALE_VLAN, vid);
	अगर (ret)
		dev_err(priv->dev, "cpsw_ale_del_ucast() failed: ret %d\n",
			ret);
	ret = cpsw_ale_del_mcast(cpsw->ale, priv->ndev->broadcast,
				 0, ALE_VLAN, vid);
	अगर (ret)
		dev_err(priv->dev, "cpsw_ale_del_mcast failed. ret %d\n",
			ret);
	cpsw_ale_flush_multicast(cpsw->ale, ALE_PORT_HOST, vid);
	ret = 0;
err:
	pm_runसमय_put(cpsw->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_nकरो_get_phys_port_name(काष्ठा net_device *ndev, अक्षर *name,
				       माप_प्रकार len)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	पूर्णांक err;

	err = snम_लिखो(name, len, "p%d", priv->emac_port);

	अगर (err >= len)
		वापस -EINVAL;

	वापस 0;
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

अटल पूर्णांक cpsw_nकरो_xdp_xmit(काष्ठा net_device *ndev, पूर्णांक n,
			     काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा xdp_frame *xdpf;
	पूर्णांक i, nxmit = 0;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	क्रम (i = 0; i < n; i++) अणु
		xdpf = frames[i];
		अगर (xdpf->len < CPSW_MIN_PACKET_SIZE)
			अवरोध;

		अगर (cpsw_xdp_tx_frame(priv, xdpf, शून्य, priv->emac_port))
			अवरोध;
		nxmit++;
	पूर्ण

	वापस nxmit;
पूर्ण

अटल पूर्णांक cpsw_get_port_parent_id(काष्ठा net_device *ndev,
				   काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

	ppid->id_len = माप(cpsw->base_mac);
	स_नकल(&ppid->id, &cpsw->base_mac, ppid->id_len);

	वापस 0;
पूर्ण

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
	.nकरो_get_phys_port_name = cpsw_nकरो_get_phys_port_name,
	.nकरो_bpf		= cpsw_nकरो_bpf,
	.nकरो_xdp_xmit		= cpsw_nकरो_xdp_xmit,
	.nकरो_get_port_parent_id	= cpsw_get_port_parent_id,
पूर्ण;

अटल व्योम cpsw_get_drvinfo(काष्ठा net_device *ndev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	काष्ठा platक्रमm_device *pdev;

	pdev = to_platक्रमm_device(cpsw->dev);
	strlcpy(info->driver, "cpsw-switch", माप(info->driver));
	strlcpy(info->version, "2.0", माप(info->version));
	strlcpy(info->bus_info, pdev->name, माप(info->bus_info));
पूर्ण

अटल पूर्णांक cpsw_set_छोड़ोparam(काष्ठा net_device *ndev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	पूर्णांक slave_no;

	slave_no = cpsw_slave_index(cpsw, priv);
	अगर (!cpsw->slaves[slave_no].phy)
		वापस -EINVAL;

	अगर (!phy_validate_छोड़ो(cpsw->slaves[slave_no].phy, छोड़ो))
		वापस -EINVAL;

	priv->rx_छोड़ो = छोड़ो->rx_छोड़ो ? true : false;
	priv->tx_छोड़ो = छोड़ो->tx_छोड़ो ? true : false;

	phy_set_asym_छोड़ो(cpsw->slaves[slave_no].phy,
			   priv->rx_छोड़ो, priv->tx_छोड़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_set_channels(काष्ठा net_device *ndev,
			     काष्ठा ethtool_channels *chs)
अणु
	वापस cpsw_set_channels_common(ndev, chs, cpsw_rx_handler);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops cpsw_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS,
	.get_drvinfo		= cpsw_get_drvinfo,
	.get_msglevel		= cpsw_get_msglevel,
	.set_msglevel		= cpsw_set_msglevel,
	.get_link		= ethtool_op_get_link,
	.get_ts_info		= cpsw_get_ts_info,
	.get_coalesce		= cpsw_get_coalesce,
	.set_coalesce		= cpsw_set_coalesce,
	.get_sset_count		= cpsw_get_sset_count,
	.get_strings		= cpsw_get_strings,
	.get_ethtool_stats	= cpsw_get_ethtool_stats,
	.get_छोड़ोparam		= cpsw_get_छोड़ोparam,
	.set_छोड़ोparam		= cpsw_set_छोड़ोparam,
	.get_wol		= cpsw_get_wol,
	.set_wol		= cpsw_set_wol,
	.get_regs_len		= cpsw_get_regs_len,
	.get_regs		= cpsw_get_regs,
	.begin			= cpsw_ethtool_op_begin,
	.complete		= cpsw_ethtool_op_complete,
	.get_channels		= cpsw_get_channels,
	.set_channels		= cpsw_set_channels,
	.get_link_ksettings	= cpsw_get_link_ksettings,
	.set_link_ksettings	= cpsw_set_link_ksettings,
	.get_eee		= cpsw_get_eee,
	.set_eee		= cpsw_set_eee,
	.nway_reset		= cpsw_nway_reset,
	.get_ringparam		= cpsw_get_ringparam,
	.set_ringparam		= cpsw_set_ringparam,
पूर्ण;

अटल पूर्णांक cpsw_probe_dt(काष्ठा cpsw_common *cpsw)
अणु
	काष्ठा device_node *node = cpsw->dev->of_node, *पंचांगp_node, *port_np;
	काष्ठा cpsw_platक्रमm_data *data = &cpsw->data;
	काष्ठा device *dev = cpsw->dev;
	पूर्णांक ret;
	u32 prop;

	अगर (!node)
		वापस -EINVAL;

	पंचांगp_node = of_get_child_by_name(node, "ethernet-ports");
	अगर (!पंचांगp_node)
		वापस -ENOENT;
	data->slaves = of_get_child_count(पंचांगp_node);
	अगर (data->slaves != CPSW_SLAVE_PORTS_NUM) अणु
		of_node_put(पंचांगp_node);
		वापस -ENOENT;
	पूर्ण

	data->active_slave = 0;
	data->channels = CPSW_MAX_QUEUES;
	data->dual_emac = true;
	data->bd_ram_size = CPSW_BD_RAM_SIZE;
	data->mac_control = 0;

	data->slave_data = devm_kसुस्मृति(dev, CPSW_SLAVE_PORTS_NUM,
					माप(काष्ठा cpsw_slave_data),
					GFP_KERNEL);
	अगर (!data->slave_data)
		वापस -ENOMEM;

	/* Populate all the child nodes here...
	 */
	ret = devm_of_platक्रमm_populate(dev);
	/* We करो not want to क्रमce this, as in some हालs may not have child */
	अगर (ret)
		dev_warn(dev, "Doesn't have any child node\n");

	क्रम_each_child_of_node(पंचांगp_node, port_np) अणु
		काष्ठा cpsw_slave_data *slave_data;
		u32 port_id;

		ret = of_property_पढ़ो_u32(port_np, "reg", &port_id);
		अगर (ret < 0) अणु
			dev_err(dev, "%pOF error reading port_id %d\n",
				port_np, ret);
			जाओ err_node_put;
		पूर्ण

		अगर (!port_id || port_id > CPSW_SLAVE_PORTS_NUM) अणु
			dev_err(dev, "%pOF has invalid port_id %u\n",
				port_np, port_id);
			ret = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		slave_data = &data->slave_data[port_id - 1];

		slave_data->disabled = !of_device_is_available(port_np);
		अगर (slave_data->disabled)
			जारी;

		slave_data->slave_node = port_np;
		slave_data->अगरphy = devm_of_phy_get(dev, port_np, शून्य);
		अगर (IS_ERR(slave_data->अगरphy)) अणु
			ret = PTR_ERR(slave_data->अगरphy);
			dev_err(dev, "%pOF: Error retrieving port phy: %d\n",
				port_np, ret);
			जाओ err_node_put;
		पूर्ण

		अगर (of_phy_is_fixed_link(port_np)) अणु
			ret = of_phy_रेजिस्टर_fixed_link(port_np);
			अगर (ret) अणु
				अगर (ret != -EPROBE_DEFER)
					dev_err(dev, "%pOF failed to register fixed-link phy: %d\n",
						port_np, ret);
				जाओ err_node_put;
			पूर्ण
			slave_data->phy_node = of_node_get(port_np);
		पूर्ण अन्यथा अणु
			slave_data->phy_node =
				of_parse_phandle(port_np, "phy-handle", 0);
		पूर्ण

		अगर (!slave_data->phy_node) अणु
			dev_err(dev, "%pOF no phy found\n", port_np);
			ret = -ENODEV;
			जाओ err_node_put;
		पूर्ण

		ret = of_get_phy_mode(port_np, &slave_data->phy_अगर);
		अगर (ret) अणु
			dev_err(dev, "%pOF read phy-mode err %d\n",
				port_np, ret);
			जाओ err_node_put;
		पूर्ण

		ret = of_get_mac_address(port_np, slave_data->mac_addr);
		अगर (ret) अणु
			ret = ti_cm_get_macid(dev, port_id - 1,
					      slave_data->mac_addr);
			अगर (ret)
				जाओ err_node_put;
		पूर्ण

		अगर (of_property_पढ़ो_u32(port_np, "ti,dual-emac-pvid",
					 &prop)) अणु
			dev_err(dev, "%pOF Missing dual_emac_res_vlan in DT.\n",
				port_np);
			slave_data->dual_emac_res_vlan = port_id;
			dev_err(dev, "%pOF Using %d as Reserved VLAN\n",
				port_np, slave_data->dual_emac_res_vlan);
		पूर्ण अन्यथा अणु
			slave_data->dual_emac_res_vlan = prop;
		पूर्ण
	पूर्ण

	of_node_put(पंचांगp_node);
	वापस 0;

err_node_put:
	of_node_put(port_np);
	वापस ret;
पूर्ण

अटल व्योम cpsw_हटाओ_dt(काष्ठा cpsw_common *cpsw)
अणु
	काष्ठा cpsw_platक्रमm_data *data = &cpsw->data;
	पूर्णांक i = 0;

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		काष्ठा cpsw_slave_data *slave_data = &data->slave_data[i];
		काष्ठा device_node *port_np = slave_data->phy_node;

		अगर (port_np) अणु
			अगर (of_phy_is_fixed_link(port_np))
				of_phy_deरेजिस्टर_fixed_link(port_np);

			of_node_put(port_np);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cpsw_create_ports(काष्ठा cpsw_common *cpsw)
अणु
	काष्ठा cpsw_platक्रमm_data *data = &cpsw->data;
	काष्ठा net_device *ndev, *napi_ndev = शून्य;
	काष्ठा device *dev = cpsw->dev;
	काष्ठा cpsw_priv *priv;
	पूर्णांक ret = 0, i = 0;

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		काष्ठा cpsw_slave_data *slave_data = &data->slave_data[i];

		अगर (slave_data->disabled)
			जारी;

		ndev = devm_alloc_etherdev_mqs(dev, माप(काष्ठा cpsw_priv),
					       CPSW_MAX_QUEUES,
					       CPSW_MAX_QUEUES);
		अगर (!ndev) अणु
			dev_err(dev, "error allocating net_device\n");
			वापस -ENOMEM;
		पूर्ण

		priv = netdev_priv(ndev);
		priv->cpsw = cpsw;
		priv->ndev = ndev;
		priv->dev  = dev;
		priv->msg_enable = netअगर_msg_init(debug_level, CPSW_DEBUG);
		priv->emac_port = i + 1;

		अगर (is_valid_ether_addr(slave_data->mac_addr)) अणु
			ether_addr_copy(priv->mac_addr, slave_data->mac_addr);
			dev_info(cpsw->dev, "Detected MACID = %pM\n",
				 priv->mac_addr);
		पूर्ण अन्यथा अणु
			eth_अक्रमom_addr(slave_data->mac_addr);
			dev_info(cpsw->dev, "Random MACID = %pM\n",
				 priv->mac_addr);
		पूर्ण
		ether_addr_copy(ndev->dev_addr, slave_data->mac_addr);
		ether_addr_copy(priv->mac_addr, slave_data->mac_addr);

		cpsw->slaves[i].ndev = ndev;

		ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER |
				  NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_NETNS_LOCAL;

		ndev->netdev_ops = &cpsw_netdev_ops;
		ndev->ethtool_ops = &cpsw_ethtool_ops;
		SET_NETDEV_DEV(ndev, dev);

		अगर (!napi_ndev) अणु
			/* CPSW Host port CPDMA पूर्णांकerface is shared between
			 * ports and there is only one TX and one RX IRQs
			 * available क्रम all possible TX and RX channels
			 * accordingly.
			 */
			netअगर_napi_add(ndev, &cpsw->napi_rx,
				       cpsw->quirk_irq ?
				       cpsw_rx_poll : cpsw_rx_mq_poll,
				       CPSW_POLL_WEIGHT);
			netअगर_tx_napi_add(ndev, &cpsw->napi_tx,
					  cpsw->quirk_irq ?
					  cpsw_tx_poll : cpsw_tx_mq_poll,
					  CPSW_POLL_WEIGHT);
		पूर्ण

		napi_ndev = ndev;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cpsw_unरेजिस्टर_ports(काष्ठा cpsw_common *cpsw)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		अगर (!cpsw->slaves[i].ndev)
			जारी;

		unरेजिस्टर_netdev(cpsw->slaves[i].ndev);
	पूर्ण
पूर्ण

अटल पूर्णांक cpsw_रेजिस्टर_ports(काष्ठा cpsw_common *cpsw)
अणु
	पूर्णांक ret = 0, i = 0;

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		अगर (!cpsw->slaves[i].ndev)
			जारी;

		/* रेजिस्टर the network device */
		ret = रेजिस्टर_netdev(cpsw->slaves[i].ndev);
		अगर (ret) अणु
			dev_err(cpsw->dev,
				"cpsw: err registering net device%d\n", i);
			cpsw->slaves[i].ndev = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		cpsw_unरेजिस्टर_ports(cpsw);
	वापस ret;
पूर्ण

bool cpsw_port_dev_check(स्थिर काष्ठा net_device *ndev)
अणु
	अगर (ndev->netdev_ops == &cpsw_netdev_ops) अणु
		काष्ठा cpsw_common *cpsw = ndev_to_cpsw(ndev);

		वापस !cpsw->data.dual_emac;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम cpsw_port_offload_fwd_mark_update(काष्ठा cpsw_common *cpsw)
अणु
	पूर्णांक set_val = 0;
	पूर्णांक i;

	अगर (!cpsw->ale_bypass &&
	    (cpsw->br_members == (ALE_PORT_1 | ALE_PORT_2)))
		set_val = 1;

	dev_dbg(cpsw->dev, "set offload_fwd_mark %d\n", set_val);

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		काष्ठा net_device *sl_ndev = cpsw->slaves[i].ndev;
		काष्ठा cpsw_priv *priv = netdev_priv(sl_ndev);

		priv->offload_fwd_mark = set_val;
	पूर्ण
पूर्ण

अटल पूर्णांक cpsw_netdevice_port_link(काष्ठा net_device *ndev,
				    काष्ठा net_device *br_ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	अगर (!cpsw->br_members) अणु
		cpsw->hw_bridge_dev = br_ndev;
	पूर्ण अन्यथा अणु
		/* This is adding the port to a second bridge, this is
		 * unsupported
		 */
		अगर (cpsw->hw_bridge_dev != br_ndev)
			वापस -EOPNOTSUPP;
	पूर्ण

	cpsw->br_members |= BIT(priv->emac_port);

	cpsw_port_offload_fwd_mark_update(cpsw);

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम cpsw_netdevice_port_unlink(काष्ठा net_device *ndev)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	cpsw->br_members &= ~BIT(priv->emac_port);

	cpsw_port_offload_fwd_mark_update(cpsw);

	अगर (!cpsw->br_members)
		cpsw->hw_bridge_dev = शून्य;
पूर्ण

/* netdev notअगरier */
अटल पूर्णांक cpsw_netdevice_event(काष्ठा notअगरier_block *unused,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_changeupper_info *info;
	पूर्णांक ret = NOTIFY_DONE;

	अगर (!cpsw_port_dev_check(ndev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		info = ptr;

		अगर (netअगर_is_bridge_master(info->upper_dev)) अणु
			अगर (info->linking)
				ret = cpsw_netdevice_port_link(ndev,
							       info->upper_dev);
			अन्यथा
				cpsw_netdevice_port_unlink(ndev);
		पूर्ण
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल काष्ठा notअगरier_block cpsw_netdevice_nb __पढ़ो_mostly = अणु
	.notअगरier_call = cpsw_netdevice_event,
पूर्ण;

अटल पूर्णांक cpsw_रेजिस्टर_notअगरiers(काष्ठा cpsw_common *cpsw)
अणु
	पूर्णांक ret = 0;

	ret = रेजिस्टर_netdevice_notअगरier(&cpsw_netdevice_nb);
	अगर (ret) अणु
		dev_err(cpsw->dev, "can't register netdevice notifier\n");
		वापस ret;
	पूर्ण

	ret = cpsw_चयनdev_रेजिस्टर_notअगरiers(cpsw);
	अगर (ret)
		unरेजिस्टर_netdevice_notअगरier(&cpsw_netdevice_nb);

	वापस ret;
पूर्ण

अटल व्योम cpsw_unरेजिस्टर_notअगरiers(काष्ठा cpsw_common *cpsw)
अणु
	cpsw_चयनdev_unरेजिस्टर_notअगरiers(cpsw);
	unरेजिस्टर_netdevice_notअगरier(&cpsw_netdevice_nb);
पूर्ण

अटल स्थिर काष्ठा devlink_ops cpsw_devlink_ops = अणु
पूर्ण;

अटल पूर्णांक cpsw_dl_चयन_mode_get(काष्ठा devlink *dl, u32 id,
				   काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा cpsw_devlink *dl_priv = devlink_priv(dl);
	काष्ठा cpsw_common *cpsw = dl_priv->cpsw;

	dev_dbg(cpsw->dev, "%s id:%u\n", __func__, id);

	अगर (id != CPSW_DL_PARAM_SWITCH_MODE)
		वापस  -EOPNOTSUPP;

	ctx->val.vbool = !cpsw->data.dual_emac;

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_dl_चयन_mode_set(काष्ठा devlink *dl, u32 id,
				   काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा cpsw_devlink *dl_priv = devlink_priv(dl);
	काष्ठा cpsw_common *cpsw = dl_priv->cpsw;
	पूर्णांक vlan = cpsw->data.शेष_vlan;
	bool चयन_en = ctx->val.vbool;
	bool अगर_running = false;
	पूर्णांक i;

	dev_dbg(cpsw->dev, "%s id:%u\n", __func__, id);

	अगर (id != CPSW_DL_PARAM_SWITCH_MODE)
		वापस  -EOPNOTSUPP;

	अगर (चयन_en == !cpsw->data.dual_emac)
		वापस 0;

	अगर (!चयन_en && cpsw->br_members) अणु
		dev_err(cpsw->dev, "Remove ports from BR before disabling switch mode\n");
		वापस -EINVAL;
	पूर्ण

	rtnl_lock();

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		काष्ठा cpsw_slave *slave = &cpsw->slaves[i];
		काष्ठा net_device *sl_ndev = slave->ndev;

		अगर (!sl_ndev || !netअगर_running(sl_ndev))
			जारी;

		अगर_running = true;
	पूर्ण

	अगर (!अगर_running) अणु
		/* all ndevs are करोwn */
		cpsw->data.dual_emac = !चयन_en;
		क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
			काष्ठा cpsw_slave *slave = &cpsw->slaves[i];
			काष्ठा net_device *sl_ndev = slave->ndev;

			अगर (!sl_ndev)
				जारी;

			अगर (चयन_en)
				vlan = cpsw->data.शेष_vlan;
			अन्यथा
				vlan = slave->data->dual_emac_res_vlan;
			slave->port_vlan = vlan;
		पूर्ण
		जाओ निकास;
	पूर्ण

	अगर (चयन_en) अणु
		dev_info(cpsw->dev, "Enable switch mode\n");

		/* enable bypass - no क्रमwarding; all traffic goes to Host */
		cpsw_ale_control_set(cpsw->ale, 0, ALE_BYPASS, 1);

		/* clean up ALE table */
		cpsw_ale_control_set(cpsw->ale, 0, ALE_CLEAR, 1);
		cpsw_ale_control_get(cpsw->ale, 0, ALE_AGEOUT);

		cpsw_init_host_port_चयन(cpsw);

		क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
			काष्ठा cpsw_slave *slave = &cpsw->slaves[i];
			काष्ठा net_device *sl_ndev = slave->ndev;
			काष्ठा cpsw_priv *priv;

			अगर (!sl_ndev)
				जारी;

			priv = netdev_priv(sl_ndev);
			slave->port_vlan = vlan;
			अगर (netअगर_running(sl_ndev))
				cpsw_port_add_चयन_def_ale_entries(priv,
								     slave);
		पूर्ण

		cpsw_ale_control_set(cpsw->ale, 0, ALE_BYPASS, 0);
		cpsw->data.dual_emac = false;
	पूर्ण अन्यथा अणु
		dev_info(cpsw->dev, "Disable switch mode\n");

		/* enable bypass - no क्रमwarding; all traffic goes to Host */
		cpsw_ale_control_set(cpsw->ale, 0, ALE_BYPASS, 1);

		cpsw_ale_control_set(cpsw->ale, 0, ALE_CLEAR, 1);
		cpsw_ale_control_get(cpsw->ale, 0, ALE_AGEOUT);

		cpsw_init_host_port_dual_mac(cpsw);

		क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
			काष्ठा cpsw_slave *slave = &cpsw->slaves[i];
			काष्ठा net_device *sl_ndev = slave->ndev;
			काष्ठा cpsw_priv *priv;

			अगर (!sl_ndev)
				जारी;

			priv = netdev_priv(slave->ndev);
			slave->port_vlan = slave->data->dual_emac_res_vlan;
			cpsw_port_add_dual_emac_def_ale_entries(priv, slave);
		पूर्ण

		cpsw_ale_control_set(cpsw->ale, 0, ALE_BYPASS, 0);
		cpsw->data.dual_emac = true;
	पूर्ण
निकास:
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_dl_ale_ctrl_get(काष्ठा devlink *dl, u32 id,
				काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा cpsw_devlink *dl_priv = devlink_priv(dl);
	काष्ठा cpsw_common *cpsw = dl_priv->cpsw;

	dev_dbg(cpsw->dev, "%s id:%u\n", __func__, id);

	चयन (id) अणु
	हाल CPSW_DL_PARAM_ALE_BYPASS:
		ctx->val.vbool = cpsw_ale_control_get(cpsw->ale, 0, ALE_BYPASS);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_dl_ale_ctrl_set(काष्ठा devlink *dl, u32 id,
				काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा cpsw_devlink *dl_priv = devlink_priv(dl);
	काष्ठा cpsw_common *cpsw = dl_priv->cpsw;
	पूर्णांक ret = -EOPNOTSUPP;

	dev_dbg(cpsw->dev, "%s id:%u\n", __func__, id);

	चयन (id) अणु
	हाल CPSW_DL_PARAM_ALE_BYPASS:
		ret = cpsw_ale_control_set(cpsw->ale, 0, ALE_BYPASS,
					   ctx->val.vbool);
		अगर (!ret) अणु
			cpsw->ale_bypass = ctx->val.vbool;
			cpsw_port_offload_fwd_mark_update(cpsw);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_param cpsw_devlink_params[] = अणु
	DEVLINK_PARAM_DRIVER(CPSW_DL_PARAM_SWITCH_MODE,
			     "switch_mode", DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_RUNTIME),
			     cpsw_dl_चयन_mode_get, cpsw_dl_चयन_mode_set,
			     शून्य),
	DEVLINK_PARAM_DRIVER(CPSW_DL_PARAM_ALE_BYPASS,
			     "ale_bypass", DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_RUNTIME),
			     cpsw_dl_ale_ctrl_get, cpsw_dl_ale_ctrl_set, शून्य),
पूर्ण;

अटल पूर्णांक cpsw_रेजिस्टर_devlink(काष्ठा cpsw_common *cpsw)
अणु
	काष्ठा device *dev = cpsw->dev;
	काष्ठा cpsw_devlink *dl_priv;
	पूर्णांक ret = 0;

	cpsw->devlink = devlink_alloc(&cpsw_devlink_ops, माप(*dl_priv));
	अगर (!cpsw->devlink)
		वापस -ENOMEM;

	dl_priv = devlink_priv(cpsw->devlink);
	dl_priv->cpsw = cpsw;

	ret = devlink_रेजिस्टर(cpsw->devlink, dev);
	अगर (ret) अणु
		dev_err(dev, "DL reg fail ret:%d\n", ret);
		जाओ dl_मुक्त;
	पूर्ण

	ret = devlink_params_रेजिस्टर(cpsw->devlink, cpsw_devlink_params,
				      ARRAY_SIZE(cpsw_devlink_params));
	अगर (ret) अणु
		dev_err(dev, "DL params reg fail ret:%d\n", ret);
		जाओ dl_unreg;
	पूर्ण

	devlink_params_publish(cpsw->devlink);
	वापस ret;

dl_unreg:
	devlink_unरेजिस्टर(cpsw->devlink);
dl_मुक्त:
	devlink_मुक्त(cpsw->devlink);
	वापस ret;
पूर्ण

अटल व्योम cpsw_unरेजिस्टर_devlink(काष्ठा cpsw_common *cpsw)
अणु
	devlink_params_unpublish(cpsw->devlink);
	devlink_params_unरेजिस्टर(cpsw->devlink, cpsw_devlink_params,
				  ARRAY_SIZE(cpsw_devlink_params));
	devlink_unरेजिस्टर(cpsw->devlink);
	devlink_मुक्त(cpsw->devlink);
पूर्ण

अटल स्थिर काष्ठा of_device_id cpsw_of_mtable[] = अणु
	अणु .compatible = "ti,cpsw-switch"पूर्ण,
	अणु .compatible = "ti,am335x-cpsw-switch"पूर्ण,
	अणु .compatible = "ti,am4372-cpsw-switch"पूर्ण,
	अणु .compatible = "ti,dra7-cpsw-switch"पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpsw_of_mtable);

अटल स्थिर काष्ठा soc_device_attribute cpsw_soc_devices[] = अणु
	अणु .family = "AM33xx", .revision = "ES1.0"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक cpsw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा soc_device_attribute *soc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cpsw_common *cpsw;
	काष्ठा resource *ss_res;
	काष्ठा gpio_descs *mode;
	व्योम __iomem *ss_regs;
	पूर्णांक ret = 0, ch;
	काष्ठा clk *clk;
	पूर्णांक irq;

	cpsw = devm_kzalloc(dev, माप(काष्ठा cpsw_common), GFP_KERNEL);
	अगर (!cpsw)
		वापस -ENOMEM;

	cpsw_slave_index = cpsw_slave_index_priv;

	cpsw->dev = dev;

	cpsw->slaves = devm_kसुस्मृति(dev,
				    CPSW_SLAVE_PORTS_NUM,
				    माप(काष्ठा cpsw_slave),
				    GFP_KERNEL);
	अगर (!cpsw->slaves)
		वापस -ENOMEM;

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
	अगर (IS_ERR(ss_regs)) अणु
		ret = PTR_ERR(ss_regs);
		वापस ret;
	पूर्ण
	cpsw->regs = ss_regs;

	irq = platक्रमm_get_irq_byname(pdev, "rx");
	अगर (irq < 0)
		वापस irq;
	cpsw->irqs_table[0] = irq;

	irq = platक्रमm_get_irq_byname(pdev, "tx");
	अगर (irq < 0)
		वापस irq;
	cpsw->irqs_table[1] = irq;

	irq = platक्रमm_get_irq_byname(pdev, "misc");
	अगर (irq <= 0)
		वापस irq;
	cpsw->misc_irq = irq;

	platक्रमm_set_drvdata(pdev, cpsw);
	/* This may be required here क्रम child devices. */
	pm_runसमय_enable(dev);

	/* Need to enable घड़ीs with runसमय PM api to access module
	 * रेजिस्टरs
	 */
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		pm_runसमय_disable(dev);
		वापस ret;
	पूर्ण

	ret = cpsw_probe_dt(cpsw);
	अगर (ret)
		जाओ clean_dt_ret;

	soc = soc_device_match(cpsw_soc_devices);
	अगर (soc)
		cpsw->quirk_irq = true;

	cpsw->rx_packet_max = rx_packet_max;
	cpsw->descs_pool_size = descs_pool_size;
	eth_अक्रमom_addr(cpsw->base_mac);

	ret = cpsw_init_common(cpsw, ss_regs, ale_ageout,
			       (u32 __क्रमce)ss_res->start + CPSW2_BD_OFFSET,
			       descs_pool_size);
	अगर (ret)
		जाओ clean_dt_ret;

	cpsw->wr_regs = cpsw->version == CPSW_VERSION_1 ?
			ss_regs + CPSW1_WR_OFFSET :
			ss_regs + CPSW2_WR_OFFSET;

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

	/* setup netdevs */
	ret = cpsw_create_ports(cpsw);
	अगर (ret)
		जाओ clean_unरेजिस्टर_netdev;

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
		जाओ clean_unरेजिस्टर_netdev;
	पूर्ण

	ret = devm_request_irq(dev, cpsw->irqs_table[1], cpsw_tx_पूर्णांकerrupt,
			       0, dev_name(dev), cpsw);
	अगर (ret < 0) अणु
		dev_err(dev, "error attaching irq (%d)\n", ret);
		जाओ clean_unरेजिस्टर_netdev;
	पूर्ण

	अगर (!cpsw->cpts)
		जाओ skip_cpts;

	ret = devm_request_irq(dev, cpsw->misc_irq, cpsw_misc_पूर्णांकerrupt,
			       0, dev_name(&pdev->dev), cpsw);
	अगर (ret < 0) अणु
		dev_err(dev, "error attaching misc irq (%d)\n", ret);
		जाओ clean_unरेजिस्टर_netdev;
	पूर्ण

	/* Enable misc CPTS evnt_pend IRQ */
	cpts_set_irqpoll(cpsw->cpts, false);

skip_cpts:
	ret = cpsw_रेजिस्टर_notअगरiers(cpsw);
	अगर (ret)
		जाओ clean_unरेजिस्टर_netdev;

	ret = cpsw_रेजिस्टर_devlink(cpsw);
	अगर (ret)
		जाओ clean_unरेजिस्टर_notअगरiers;

	ret = cpsw_रेजिस्टर_ports(cpsw);
	अगर (ret)
		जाओ clean_unरेजिस्टर_notअगरiers;

	dev_notice(dev, "initialized (regs %pa, pool size %d) hw_ver:%08X %d.%d (%d)\n",
		   &ss_res->start, descs_pool_size,
		   cpsw->version, CPSW_MAJOR_VERSION(cpsw->version),
		   CPSW_MINOR_VERSION(cpsw->version),
		   CPSW_RTL_VERSION(cpsw->version));

	pm_runसमय_put(dev);

	वापस 0;

clean_unरेजिस्टर_notअगरiers:
	cpsw_unरेजिस्टर_notअगरiers(cpsw);
clean_unरेजिस्टर_netdev:
	cpsw_unरेजिस्टर_ports(cpsw);
clean_cpts:
	cpts_release(cpsw->cpts);
	cpdma_ctlr_destroy(cpsw->dma);
clean_dt_ret:
	cpsw_हटाओ_dt(cpsw);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpsw_common *cpsw = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		वापस ret;
	पूर्ण

	cpsw_unरेजिस्टर_notअगरiers(cpsw);
	cpsw_unरेजिस्टर_devlink(cpsw);
	cpsw_unरेजिस्टर_ports(cpsw);

	cpts_release(cpsw->cpts);
	cpdma_ctlr_destroy(cpsw->dma);
	cpsw_हटाओ_dt(cpsw);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cpsw_suspend(काष्ठा device *dev)
अणु
	काष्ठा cpsw_common *cpsw = dev_get_drvdata(dev);
	पूर्णांक i;

	rtnl_lock();

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		काष्ठा net_device *ndev = cpsw->slaves[i].ndev;

		अगर (!(ndev && netअगर_running(ndev)))
			जारी;

		cpsw_nकरो_stop(ndev);
	पूर्ण

	rtnl_unlock();

	/* Select sleep pin state */
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cpsw_resume(काष्ठा device *dev)
अणु
	काष्ठा cpsw_common *cpsw = dev_get_drvdata(dev);
	पूर्णांक i;

	/* Select शेष pin state */
	pinctrl_pm_select_शेष_state(dev);

	/* shut up ASSERT_RTNL() warning in netअगर_set_real_num_tx/rx_queues */
	rtnl_lock();

	क्रम (i = 0; i < cpsw->data.slaves; i++) अणु
		काष्ठा net_device *ndev = cpsw->slaves[i].ndev;

		अगर (!(ndev && netअगर_running(ndev)))
			जारी;

		cpsw_nकरो_खोलो(ndev);
	पूर्ण

	rtnl_unlock();

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cpsw_pm_ops, cpsw_suspend, cpsw_resume);

अटल काष्ठा platक्रमm_driver cpsw_driver = अणु
	.driver = अणु
		.name	 = "cpsw-switch",
		.pm	 = &cpsw_pm_ops,
		.of_match_table = cpsw_of_mtable,
	पूर्ण,
	.probe = cpsw_probe,
	.हटाओ = cpsw_हटाओ,
पूर्ण;

module_platक्रमm_driver(cpsw_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TI CPSW switchdev Ethernet driver");
