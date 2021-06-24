<शैली गुरु>
/*
 * Copyright(c) 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * This file contains OPA Virtual Network Interface Controller (VNIC) driver
 * netdev functionality.
 */

#समावेश <linux/module.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crc32.h>

#समावेश "opa_vnic_internal.h"

#घोषणा OPA_TX_TIMEOUT_MS 1000

#घोषणा OPA_VNIC_SKB_HEADROOM  \
			ALIGN((OPA_VNIC_HDR_LEN + OPA_VNIC_SKB_MDATA_LEN), 8)

/* This function is overloaded क्रम opa_vnic specअगरic implementation */
अटल व्योम opa_vnic_get_stats64(काष्ठा net_device *netdev,
				 काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	काष्ठा opa_vnic_stats vstats;

	स_रखो(&vstats, 0, माप(vstats));
	spin_lock(&adapter->stats_lock);
	adapter->rn_ops->nकरो_get_stats64(netdev, &vstats.netstats);
	spin_unlock(&adapter->stats_lock);
	स_नकल(stats, &vstats.netstats, माप(*stats));
पूर्ण

/* opa_netdev_start_xmit - transmit function */
अटल netdev_tx_t opa_netdev_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *netdev)
अणु
	काष्ठा opa_vnic_adapter *adapter = opa_vnic_priv(netdev);

	v_dbg("xmit: queue %d skb len %d\n", skb->queue_mapping, skb->len);
	/* pad to ensure mininum ethernet packet length */
	अगर (unlikely(skb->len < ETH_ZLEN)) अणु
		अगर (skb_padto(skb, ETH_ZLEN))
			वापस NETDEV_TX_OK;

		skb_put(skb, ETH_ZLEN - skb->len);
	पूर्ण

	opa_vnic_encap_skb(adapter, skb);
	वापस adapter->rn_ops->nकरो_start_xmit(skb, netdev);
पूर्ण

अटल u16 opa_vnic_select_queue(काष्ठा net_device *netdev, काष्ठा sk_buff *skb,
				 काष्ठा net_device *sb_dev)
अणु
	काष्ठा opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	काष्ठा opa_vnic_skb_mdata *mdata;
	पूर्णांक rc;

	/* pass entropy and vl as metadata in skb */
	mdata = skb_push(skb, माप(*mdata));
	mdata->entropy = opa_vnic_calc_entropy(skb);
	mdata->vl = opa_vnic_get_vl(adapter, skb);
	rc = adapter->rn_ops->nकरो_select_queue(netdev, skb, sb_dev);
	skb_pull(skb, माप(*mdata));
	वापस rc;
पूर्ण

अटल व्योम opa_vnic_update_state(काष्ठा opa_vnic_adapter *adapter, bool up)
अणु
	काष्ठा __opa_veswport_info *info = &adapter->info;

	mutex_lock(&adapter->lock);
	/* Operational state can only be DROP_ALL or FORWARDING */
	अगर ((info->vport.config_state == OPA_VNIC_STATE_FORWARDING) && up) अणु
		info->vport.oper_state = OPA_VNIC_STATE_FORWARDING;
		info->vport.eth_link_status = OPA_VNIC_ETH_LINK_UP;
	पूर्ण अन्यथा अणु
		info->vport.oper_state = OPA_VNIC_STATE_DROP_ALL;
		info->vport.eth_link_status = OPA_VNIC_ETH_LINK_DOWN;
	पूर्ण

	अगर (info->vport.config_state == OPA_VNIC_STATE_FORWARDING)
		netअगर_करोrmant_off(adapter->netdev);
	अन्यथा
		netअगर_करोrmant_on(adapter->netdev);
	mutex_unlock(&adapter->lock);
पूर्ण

/* opa_vnic_process_vema_config - process vema configuration updates */
व्योम opa_vnic_process_vema_config(काष्ठा opa_vnic_adapter *adapter)
अणु
	काष्ठा __opa_veswport_info *info = &adapter->info;
	काष्ठा rdma_netdev *rn = netdev_priv(adapter->netdev);
	u8 port_num[OPA_VESW_MAX_NUM_DEF_PORT] = अणु 0 पूर्ण;
	काष्ठा net_device *netdev = adapter->netdev;
	u8 i, port_count = 0;
	u16 port_mask;

	/* If the base_mac_addr is changed, update the पूर्णांकerface mac address */
	अगर (स_भेद(info->vport.base_mac_addr, adapter->vema_mac_addr,
		   ARRAY_SIZE(info->vport.base_mac_addr))) अणु
		काष्ठा sockaddr saddr;

		स_नकल(saddr.sa_data, info->vport.base_mac_addr,
		       ARRAY_SIZE(info->vport.base_mac_addr));
		mutex_lock(&adapter->lock);
		eth_commit_mac_addr_change(netdev, &saddr);
		स_नकल(adapter->vema_mac_addr,
		       info->vport.base_mac_addr, ETH_ALEN);
		mutex_unlock(&adapter->lock);
	पूर्ण

	rn->set_id(netdev, info->vesw.vesw_id);

	/* Handle MTU limit change */
	rtnl_lock();
	netdev->max_mtu = max_t(अचिन्हित पूर्णांक, info->vesw.eth_mtu,
				netdev->min_mtu);
	अगर (netdev->mtu > netdev->max_mtu)
		dev_set_mtu(netdev, netdev->max_mtu);
	rtnl_unlock();

	/* Update flow to शेष port redirection table */
	port_mask = info->vesw.def_port_mask;
	क्रम (i = 0; i < OPA_VESW_MAX_NUM_DEF_PORT; i++) अणु
		अगर (port_mask & 1)
			port_num[port_count++] = i;
		port_mask >>= 1;
	पूर्ण

	/*
	 * Build the flow table. Flow table is required when destination LID
	 * is not available. Up to OPA_VNIC_FLOW_TBL_SIZE flows supported.
	 * Each flow need a शेष port number to get its dlid from the
	 * u_ucast_dlid array.
	 */
	क्रम (i = 0; i < OPA_VNIC_FLOW_TBL_SIZE; i++)
		adapter->flow_tbl[i] = port_count ? port_num[i % port_count] :
						    OPA_VNIC_INVALID_PORT;

	/* update state */
	opa_vnic_update_state(adapter, !!(netdev->flags & IFF_UP));
पूर्ण

/*
 * Set the घातer on शेष values in adapter's vema पूर्णांकerface काष्ठाure.
 */
अटल अंतरभूत व्योम opa_vnic_set_pod_values(काष्ठा opa_vnic_adapter *adapter)
अणु
	adapter->info.vport.max_mac_tbl_ent = OPA_VNIC_MAC_TBL_MAX_ENTRIES;
	adapter->info.vport.max_smac_ent = OPA_VNIC_MAX_SMAC_LIMIT;
	adapter->info.vport.config_state = OPA_VNIC_STATE_DROP_ALL;
	adapter->info.vport.eth_link_status = OPA_VNIC_ETH_LINK_DOWN;
	adapter->info.vesw.eth_mtu = ETH_DATA_LEN;
पूर्ण

/* opa_vnic_set_mac_addr - change mac address */
अटल पूर्णांक opa_vnic_set_mac_addr(काष्ठा net_device *netdev, व्योम *addr)
अणु
	काष्ठा opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	काष्ठा sockaddr *sa = addr;
	पूर्णांक rc;

	अगर (!स_भेद(netdev->dev_addr, sa->sa_data, ETH_ALEN))
		वापस 0;

	mutex_lock(&adapter->lock);
	rc = eth_mac_addr(netdev, addr);
	mutex_unlock(&adapter->lock);
	अगर (rc)
		वापस rc;

	adapter->info.vport.uc_macs_gen_count++;
	opa_vnic_vema_report_event(adapter,
				   OPA_VESWPORT_TRAP_IFACE_UCAST_MAC_CHANGE);
	वापस 0;
पूर्ण

/*
 * opa_vnic_mac_send_event - post event on possible mac list exchange
 *  Send trap when digest from uc/mc mac list dअगरfers from previous run.
 *  Digest is evaluated similar to how cksum करोes.
 */
अटल व्योम opa_vnic_mac_send_event(काष्ठा net_device *netdev, u8 event)
अणु
	काष्ठा opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	काष्ठा netdev_hw_addr *ha;
	काष्ठा netdev_hw_addr_list *hw_list;
	u32 *ref_crc;
	u32 l, crc = 0;

	चयन (event) अणु
	हाल OPA_VESWPORT_TRAP_IFACE_UCAST_MAC_CHANGE:
		hw_list = &netdev->uc;
		adapter->info.vport.uc_macs_gen_count++;
		ref_crc = &adapter->umac_hash;
		अवरोध;
	हाल OPA_VESWPORT_TRAP_IFACE_MCAST_MAC_CHANGE:
		hw_list = &netdev->mc;
		adapter->info.vport.mc_macs_gen_count++;
		ref_crc = &adapter->mmac_hash;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	netdev_hw_addr_list_क्रम_each(ha, hw_list) अणु
		crc = crc32_le(crc, ha->addr, ETH_ALEN);
	पूर्ण
	l = netdev_hw_addr_list_count(hw_list) * ETH_ALEN;
	crc = ~crc32_le(crc, (व्योम *)&l, माप(l));

	अगर (crc != *ref_crc) अणु
		*ref_crc = crc;
		opa_vnic_vema_report_event(adapter, event);
	पूर्ण
पूर्ण

/* opa_vnic_set_rx_mode - handle uc/mc mac list change */
अटल व्योम opa_vnic_set_rx_mode(काष्ठा net_device *netdev)
अणु
	opa_vnic_mac_send_event(netdev,
				OPA_VESWPORT_TRAP_IFACE_UCAST_MAC_CHANGE);

	opa_vnic_mac_send_event(netdev,
				OPA_VESWPORT_TRAP_IFACE_MCAST_MAC_CHANGE);
पूर्ण

/* opa_netdev_खोलो - activate network पूर्णांकerface */
अटल पूर्णांक opa_netdev_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	पूर्णांक rc;

	rc = adapter->rn_ops->nकरो_खोलो(adapter->netdev);
	अगर (rc) अणु
		v_dbg("open failed %d\n", rc);
		वापस rc;
	पूर्ण

	/* Update status and send trap */
	opa_vnic_update_state(adapter, true);
	opa_vnic_vema_report_event(adapter,
				   OPA_VESWPORT_TRAP_ETH_LINK_STATUS_CHANGE);
	वापस 0;
पूर्ण

/* opa_netdev_बंद - disable network पूर्णांकerface */
अटल पूर्णांक opa_netdev_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	पूर्णांक rc;

	rc = adapter->rn_ops->nकरो_stop(adapter->netdev);
	अगर (rc) अणु
		v_dbg("close failed %d\n", rc);
		वापस rc;
	पूर्ण

	/* Update status and send trap */
	opa_vnic_update_state(adapter, false);
	opa_vnic_vema_report_event(adapter,
				   OPA_VESWPORT_TRAP_ETH_LINK_STATUS_CHANGE);
	वापस 0;
पूर्ण

/* netdev ops */
अटल स्थिर काष्ठा net_device_ops opa_netdev_ops = अणु
	.nकरो_खोलो = opa_netdev_खोलो,
	.nकरो_stop = opa_netdev_बंद,
	.nकरो_start_xmit = opa_netdev_start_xmit,
	.nकरो_get_stats64 = opa_vnic_get_stats64,
	.nकरो_set_rx_mode = opa_vnic_set_rx_mode,
	.nकरो_select_queue = opa_vnic_select_queue,
	.nकरो_set_mac_address = opa_vnic_set_mac_addr,
पूर्ण;

/* opa_vnic_add_netdev - create vnic netdev पूर्णांकerface */
काष्ठा opa_vnic_adapter *opa_vnic_add_netdev(काष्ठा ib_device *ibdev,
					     u8 port_num, u8 vport_num)
अणु
	काष्ठा opa_vnic_adapter *adapter;
	काष्ठा net_device *netdev;
	काष्ठा rdma_netdev *rn;
	पूर्णांक rc;

	netdev = ibdev->ops.alloc_rdma_netdev(ibdev, port_num,
					      RDMA_NETDEV_OPA_VNIC,
					      "veth%d", NET_NAME_UNKNOWN,
					      ether_setup);
	अगर (!netdev)
		वापस ERR_PTR(-ENOMEM);
	अन्यथा अगर (IS_ERR(netdev))
		वापस ERR_CAST(netdev);

	rn = netdev_priv(netdev);
	adapter = kzalloc(माप(*adapter), GFP_KERNEL);
	अगर (!adapter) अणु
		rc = -ENOMEM;
		जाओ adapter_err;
	पूर्ण

	rn->clnt_priv = adapter;
	rn->hca = ibdev;
	rn->port_num = port_num;
	adapter->netdev = netdev;
	adapter->ibdev = ibdev;
	adapter->port_num = port_num;
	adapter->vport_num = vport_num;
	adapter->rn_ops = netdev->netdev_ops;

	netdev->netdev_ops = &opa_netdev_ops;
	netdev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	netdev->hard_header_len += OPA_VNIC_SKB_HEADROOM;
	mutex_init(&adapter->lock);
	mutex_init(&adapter->mactbl_lock);
	spin_lock_init(&adapter->stats_lock);

	SET_NETDEV_DEV(netdev, ibdev->dev.parent);

	opa_vnic_set_ethtool_ops(netdev);

	opa_vnic_set_pod_values(adapter);

	rc = रेजिस्टर_netdev(netdev);
	अगर (rc)
		जाओ netdev_err;

	netअगर_carrier_off(netdev);
	netअगर_करोrmant_on(netdev);
	v_info("initialized\n");

	वापस adapter;
netdev_err:
	mutex_destroy(&adapter->lock);
	mutex_destroy(&adapter->mactbl_lock);
	kमुक्त(adapter);
adapter_err:
	rn->मुक्त_rdma_netdev(netdev);

	वापस ERR_PTR(rc);
पूर्ण

/* opa_vnic_rem_netdev - हटाओ vnic netdev पूर्णांकerface */
व्योम opa_vnic_rem_netdev(काष्ठा opa_vnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा rdma_netdev *rn = netdev_priv(netdev);

	v_info("removing\n");
	unरेजिस्टर_netdev(netdev);
	opa_vnic_release_mac_tbl(adapter);
	mutex_destroy(&adapter->lock);
	mutex_destroy(&adapter->mactbl_lock);
	kमुक्त(adapter);
	rn->मुक्त_rdma_netdev(netdev);
पूर्ण
