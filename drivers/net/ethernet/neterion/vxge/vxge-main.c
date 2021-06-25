<शैली गुरु>
/******************************************************************************
* This software may be used and distributed according to the terms of
* the GNU General Public License (GPL), incorporated herein by reference.
* Drivers based on or derived from this code fall under the GPL and must
* retain the authorship, copyright and license notice.  This file is not
* a complete program and may only be used when the entire operating
* प्रणाली is licensed under the GPL.
* See the file COPYING in this distribution क्रम more inक्रमmation.
*
* vxge-मुख्य.c: Driver क्रम Exar Corp's X3100 Series 10GbE PCIe I/O
*              Virtualized Server Adapter.
* Copyright(c) 2002-2010 Exar Corp.
*
* The module loadable parameters that are supported by the driver and a brief
* explanation of all the variables:
* vlan_tag_strip:
*	Strip VLAN Tag enable/disable. Inकाष्ठाs the device to हटाओ
*	the VLAN tag from all received tagged frames that are not
*	replicated at the पूर्णांकernal L2 चयन.
*		0 - Do not strip the VLAN tag.
*		1 - Strip the VLAN tag.
*
* addr_learn_en:
*	Enable learning the mac address of the guest OS पूर्णांकerface in
*	a भवization environment.
*		0 - DISABLE
*		1 - ENABLE
*
* max_config_port:
*	Maximum number of port to be supported.
*		MIN -1 and MAX - 2
*
* max_config_vpath:
*	This configures the maximum no of VPATH configures क्रम each
* 	device function.
*		MIN - 1 and MAX - 17
*
* max_config_dev:
*	This configures maximum no of Device function to be enabled.
*		MIN - 1 and MAX - 17
*
******************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>
#समावेश <net/ip.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/module.h>
#समावेश "vxge-main.h"
#समावेश "vxge-reg.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Neterion's X3100 Series 10GbE PCIe I/O"
	"Virtualized Server Adapter");

अटल स्थिर काष्ठा pci_device_id vxge_id_table[] = अणु
	अणुPCI_VENDOR_ID_S2IO, PCI_DEVICE_ID_TITAN_WIN, PCI_ANY_ID,
	PCI_ANY_IDपूर्ण,
	अणुPCI_VENDOR_ID_S2IO, PCI_DEVICE_ID_TITAN_UNI, PCI_ANY_ID,
	PCI_ANY_IDपूर्ण,
	अणु0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, vxge_id_table);

VXGE_MODULE_PARAM_INT(vlan_tag_strip, VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_ENABLE);
VXGE_MODULE_PARAM_INT(addr_learn_en, VXGE_HW_MAC_ADDR_LEARN_DEFAULT);
VXGE_MODULE_PARAM_INT(max_config_port, VXGE_MAX_CONFIG_PORT);
VXGE_MODULE_PARAM_INT(max_config_vpath, VXGE_USE_DEFAULT);
VXGE_MODULE_PARAM_INT(max_mac_vpath, VXGE_MAX_MAC_ADDR_COUNT);
VXGE_MODULE_PARAM_INT(max_config_dev, VXGE_MAX_CONFIG_DEV);

अटल u16 vpath_selector[VXGE_HW_MAX_VIRTUAL_PATHS] =
		अणु0, 1, 3, 3, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 31पूर्ण;
अटल अचिन्हित पूर्णांक bw_percentage[VXGE_HW_MAX_VIRTUAL_PATHS] =
	अणु[0 ...(VXGE_HW_MAX_VIRTUAL_PATHS - 1)] = 0xFFपूर्ण;
module_param_array(bw_percentage, uपूर्णांक, शून्य, 0);

अटल काष्ठा vxge_drv_config *driver_config;
अटल क्रमागत vxge_hw_status vxge_reset_all_vpaths(काष्ठा vxgedev *vdev);

अटल अंतरभूत पूर्णांक is_vxge_card_up(काष्ठा vxgedev *vdev)
अणु
	वापस test_bit(__VXGE_STATE_CARD_UP, &vdev->state);
पूर्ण

अटल अंतरभूत व्योम VXGE_COMPLETE_VPATH_TX(काष्ठा vxge_fअगरo *fअगरo)
अणु
	काष्ठा sk_buff **skb_ptr = शून्य;
	काष्ठा sk_buff **temp;
#घोषणा NR_SKB_COMPLETED 16
	काष्ठा sk_buff *completed[NR_SKB_COMPLETED];
	पूर्णांक more;

	करो अणु
		more = 0;
		skb_ptr = completed;

		अगर (__netअगर_tx_trylock(fअगरo->txq)) अणु
			vxge_hw_vpath_poll_tx(fअगरo->handle, &skb_ptr,
						NR_SKB_COMPLETED, &more);
			__netअगर_tx_unlock(fअगरo->txq);
		पूर्ण

		/* मुक्त SKBs */
		क्रम (temp = completed; temp != skb_ptr; temp++)
			dev_consume_skb_irq(*temp);
	पूर्ण जबतक (more);
पूर्ण

अटल अंतरभूत व्योम VXGE_COMPLETE_ALL_TX(काष्ठा vxgedev *vdev)
अणु
	पूर्णांक i;

	/* Complete all transmits */
	क्रम (i = 0; i < vdev->no_of_vpath; i++)
		VXGE_COMPLETE_VPATH_TX(&vdev->vpaths[i].fअगरo);
पूर्ण

अटल अंतरभूत व्योम VXGE_COMPLETE_ALL_RX(काष्ठा vxgedev *vdev)
अणु
	पूर्णांक i;
	काष्ठा vxge_ring *ring;

	/* Complete all receives*/
	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		ring = &vdev->vpaths[i].ring;
		vxge_hw_vpath_poll_rx(ring->handle);
	पूर्ण
पूर्ण

/*
 * vxge_callback_link_up
 *
 * This function is called during पूर्णांकerrupt context to notअगरy link up state
 * change.
 */
अटल व्योम vxge_callback_link_up(काष्ठा __vxge_hw_device *hldev)
अणु
	काष्ठा net_device *dev = hldev->ndev;
	काष्ठा vxgedev *vdev = netdev_priv(dev);

	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
		vdev->ndev->name, __func__, __LINE__);
	netdev_notice(vdev->ndev, "Link Up\n");
	vdev->stats.link_up++;

	netअगर_carrier_on(vdev->ndev);
	netअगर_tx_wake_all_queues(vdev->ndev);

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d Exiting...", vdev->ndev->name, __func__, __LINE__);
पूर्ण

/*
 * vxge_callback_link_करोwn
 *
 * This function is called during पूर्णांकerrupt context to notअगरy link करोwn state
 * change.
 */
अटल व्योम vxge_callback_link_करोwn(काष्ठा __vxge_hw_device *hldev)
अणु
	काष्ठा net_device *dev = hldev->ndev;
	काष्ठा vxgedev *vdev = netdev_priv(dev);

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d", vdev->ndev->name, __func__, __LINE__);
	netdev_notice(vdev->ndev, "Link Down\n");

	vdev->stats.link_करोwn++;
	netअगर_carrier_off(vdev->ndev);
	netअगर_tx_stop_all_queues(vdev->ndev);

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d Exiting...", vdev->ndev->name, __func__, __LINE__);
पूर्ण

/*
 * vxge_rx_alloc
 *
 * Allocate SKB.
 */
अटल काष्ठा sk_buff *
vxge_rx_alloc(व्योम *dtrh, काष्ठा vxge_ring *ring, स्थिर पूर्णांक skb_size)
अणु
	काष्ठा net_device    *dev;
	काष्ठा sk_buff       *skb;
	काष्ठा vxge_rx_priv *rx_priv;

	dev = ring->ndev;
	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
		ring->ndev->name, __func__, __LINE__);

	rx_priv = vxge_hw_ring_rxd_निजी_get(dtrh);

	/* try to allocate skb first. this one may fail */
	skb = netdev_alloc_skb(dev, skb_size +
	VXGE_HW_HEADER_ETHERNET_II_802_3_ALIGN);
	अगर (skb == शून्य) अणु
		vxge_debug_mem(VXGE_ERR,
			"%s: out of memory to allocate SKB", dev->name);
		ring->stats.skb_alloc_fail++;
		वापस शून्य;
	पूर्ण

	vxge_debug_mem(VXGE_TRACE,
		"%s: %s:%d  Skb : 0x%p", ring->ndev->name,
		__func__, __LINE__, skb);

	skb_reserve(skb, VXGE_HW_HEADER_ETHERNET_II_802_3_ALIGN);

	rx_priv->skb = skb;
	rx_priv->skb_data = शून्य;
	rx_priv->data_size = skb_size;
	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d Exiting...", ring->ndev->name, __func__, __LINE__);

	वापस skb;
पूर्ण

/*
 * vxge_rx_map
 */
अटल पूर्णांक vxge_rx_map(व्योम *dtrh, काष्ठा vxge_ring *ring)
अणु
	काष्ठा vxge_rx_priv *rx_priv;
	dma_addr_t dma_addr;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
		ring->ndev->name, __func__, __LINE__);
	rx_priv = vxge_hw_ring_rxd_निजी_get(dtrh);

	rx_priv->skb_data = rx_priv->skb->data;
	dma_addr = dma_map_single(&ring->pdev->dev, rx_priv->skb_data,
				  rx_priv->data_size, DMA_FROM_DEVICE);

	अगर (unlikely(dma_mapping_error(&ring->pdev->dev, dma_addr))) अणु
		ring->stats.pci_map_fail++;
		वापस -EIO;
	पूर्ण
	vxge_debug_mem(VXGE_TRACE,
		"%s: %s:%d  1 buffer mode dma_addr = 0x%llx",
		ring->ndev->name, __func__, __LINE__,
		(अचिन्हित दीर्घ दीर्घ)dma_addr);
	vxge_hw_ring_rxd_1b_set(dtrh, dma_addr, rx_priv->data_size);

	rx_priv->data_dma = dma_addr;
	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d Exiting...", ring->ndev->name, __func__, __LINE__);

	वापस 0;
पूर्ण

/*
 * vxge_rx_initial_replenish
 * Allocation of RxD as an initial replenish procedure.
 */
अटल क्रमागत vxge_hw_status
vxge_rx_initial_replenish(व्योम *dtrh, व्योम *userdata)
अणु
	काष्ठा vxge_ring *ring = (काष्ठा vxge_ring *)userdata;
	काष्ठा vxge_rx_priv *rx_priv;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
		ring->ndev->name, __func__, __LINE__);
	अगर (vxge_rx_alloc(dtrh, ring,
			  VXGE_LL_MAX_FRAME_SIZE(ring->ndev)) == शून्य)
		वापस VXGE_HW_FAIL;

	अगर (vxge_rx_map(dtrh, ring)) अणु
		rx_priv = vxge_hw_ring_rxd_निजी_get(dtrh);
		dev_kमुक्त_skb(rx_priv->skb);

		वापस VXGE_HW_FAIL;
	पूर्ण
	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d Exiting...", ring->ndev->name, __func__, __LINE__);

	वापस VXGE_HW_OK;
पूर्ण

अटल अंतरभूत व्योम
vxge_rx_complete(काष्ठा vxge_ring *ring, काष्ठा sk_buff *skb, u16 vlan,
		 पूर्णांक pkt_length, काष्ठा vxge_hw_ring_rxd_info *ext_info)
अणु

	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
			ring->ndev->name, __func__, __LINE__);
	skb_record_rx_queue(skb, ring->driver_id);
	skb->protocol = eth_type_trans(skb, ring->ndev);

	u64_stats_update_begin(&ring->stats.syncp);
	ring->stats.rx_frms++;
	ring->stats.rx_bytes += pkt_length;

	अगर (skb->pkt_type == PACKET_MULTICAST)
		ring->stats.rx_mcast++;
	u64_stats_update_end(&ring->stats.syncp);

	vxge_debug_rx(VXGE_TRACE,
		"%s: %s:%d  skb protocol = %d",
		ring->ndev->name, __func__, __LINE__, skb->protocol);

	अगर (ext_info->vlan &&
	    ring->vlan_tag_strip == VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_ENABLE)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ext_info->vlan);
	napi_gro_receive(ring->napi_p, skb);

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d Exiting...", ring->ndev->name, __func__, __LINE__);
पूर्ण

अटल अंतरभूत व्योम vxge_re_pre_post(व्योम *dtr, काष्ठा vxge_ring *ring,
				    काष्ठा vxge_rx_priv *rx_priv)
अणु
	dma_sync_single_क्रम_device(&ring->pdev->dev, rx_priv->data_dma,
				   rx_priv->data_size, DMA_FROM_DEVICE);

	vxge_hw_ring_rxd_1b_set(dtr, rx_priv->data_dma, rx_priv->data_size);
	vxge_hw_ring_rxd_pre_post(ring->handle, dtr);
पूर्ण

अटल अंतरभूत व्योम vxge_post(पूर्णांक *dtr_cnt, व्योम **first_dtr,
			     व्योम *post_dtr, काष्ठा __vxge_hw_ring *ringh)
अणु
	पूर्णांक dtr_count = *dtr_cnt;
	अगर ((*dtr_cnt % VXGE_HW_RXSYNC_FREQ_CNT) == 0) अणु
		अगर (*first_dtr)
			vxge_hw_ring_rxd_post_post_wmb(ringh, *first_dtr);
		*first_dtr = post_dtr;
	पूर्ण अन्यथा
		vxge_hw_ring_rxd_post_post(ringh, post_dtr);
	dtr_count++;
	*dtr_cnt = dtr_count;
पूर्ण

/*
 * vxge_rx_1b_compl
 *
 * If the पूर्णांकerrupt is because of a received frame or अगर the receive ring
 * contains fresh as yet un-processed frames, this function is called.
 */
अटल क्रमागत vxge_hw_status
vxge_rx_1b_compl(काष्ठा __vxge_hw_ring *ringh, व्योम *dtr,
		 u8 t_code, व्योम *userdata)
अणु
	काष्ठा vxge_ring *ring = (काष्ठा vxge_ring *)userdata;
	काष्ठा net_device *dev = ring->ndev;
	अचिन्हित पूर्णांक dma_sizes;
	व्योम *first_dtr = शून्य;
	पूर्णांक dtr_cnt = 0;
	पूर्णांक data_size;
	dma_addr_t data_dma;
	पूर्णांक pkt_length;
	काष्ठा sk_buff *skb;
	काष्ठा vxge_rx_priv *rx_priv;
	काष्ठा vxge_hw_ring_rxd_info ext_info;
	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
		ring->ndev->name, __func__, __LINE__);

	अगर (ring->budget <= 0)
		जाओ out;

	करो अणु
		prefetch((अक्षर *)dtr + L1_CACHE_BYTES);
		rx_priv = vxge_hw_ring_rxd_निजी_get(dtr);
		skb = rx_priv->skb;
		data_size = rx_priv->data_size;
		data_dma = rx_priv->data_dma;
		prefetch(rx_priv->skb_data);

		vxge_debug_rx(VXGE_TRACE,
			"%s: %s:%d  skb = 0x%p",
			ring->ndev->name, __func__, __LINE__, skb);

		vxge_hw_ring_rxd_1b_get(ringh, dtr, &dma_sizes);
		pkt_length = dma_sizes;

		pkt_length -= ETH_FCS_LEN;

		vxge_debug_rx(VXGE_TRACE,
			"%s: %s:%d  Packet Length = %d",
			ring->ndev->name, __func__, __LINE__, pkt_length);

		vxge_hw_ring_rxd_1b_info_get(ringh, dtr, &ext_info);

		/* check skb validity */
		vxge_निश्चित(skb);

		prefetch((अक्षर *)skb + L1_CACHE_BYTES);
		अगर (unlikely(t_code)) अणु
			अगर (vxge_hw_ring_handle_tcode(ringh, dtr, t_code) !=
				VXGE_HW_OK) अणु

				ring->stats.rx_errors++;
				vxge_debug_rx(VXGE_TRACE,
					"%s: %s :%d Rx T_code is %d",
					ring->ndev->name, __func__,
					__LINE__, t_code);

				/* If the t_code is not supported and अगर the
				 * t_code is other than 0x5 (unparseable packet
				 * such as unknown UPV6 header), Drop it !!!
				 */
				vxge_re_pre_post(dtr, ring, rx_priv);

				vxge_post(&dtr_cnt, &first_dtr, dtr, ringh);
				ring->stats.rx_dropped++;
				जारी;
			पूर्ण
		पूर्ण

		अगर (pkt_length > VXGE_LL_RX_COPY_THRESHOLD) अणु
			अगर (vxge_rx_alloc(dtr, ring, data_size) != शून्य) अणु
				अगर (!vxge_rx_map(dtr, ring)) अणु
					skb_put(skb, pkt_length);

					dma_unmap_single(&ring->pdev->dev,
							 data_dma, data_size,
							 DMA_FROM_DEVICE);

					vxge_hw_ring_rxd_pre_post(ringh, dtr);
					vxge_post(&dtr_cnt, &first_dtr, dtr,
						ringh);
				पूर्ण अन्यथा अणु
					dev_kमुक्त_skb(rx_priv->skb);
					rx_priv->skb = skb;
					rx_priv->data_size = data_size;
					vxge_re_pre_post(dtr, ring, rx_priv);

					vxge_post(&dtr_cnt, &first_dtr, dtr,
						ringh);
					ring->stats.rx_dropped++;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				vxge_re_pre_post(dtr, ring, rx_priv);

				vxge_post(&dtr_cnt, &first_dtr, dtr, ringh);
				ring->stats.rx_dropped++;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb_up;

			skb_up = netdev_alloc_skb(dev, pkt_length +
				VXGE_HW_HEADER_ETHERNET_II_802_3_ALIGN);
			अगर (skb_up != शून्य) अणु
				skb_reserve(skb_up,
				    VXGE_HW_HEADER_ETHERNET_II_802_3_ALIGN);

				dma_sync_single_क्रम_cpu(&ring->pdev->dev,
							data_dma, data_size,
							DMA_FROM_DEVICE);

				vxge_debug_mem(VXGE_TRACE,
					"%s: %s:%d  skb_up = %p",
					ring->ndev->name, __func__,
					__LINE__, skb);
				स_नकल(skb_up->data, skb->data, pkt_length);

				vxge_re_pre_post(dtr, ring, rx_priv);

				vxge_post(&dtr_cnt, &first_dtr, dtr,
					ringh);
				/* will netअगर_rx small SKB instead */
				skb = skb_up;
				skb_put(skb, pkt_length);
			पूर्ण अन्यथा अणु
				vxge_re_pre_post(dtr, ring, rx_priv);

				vxge_post(&dtr_cnt, &first_dtr, dtr, ringh);
				vxge_debug_rx(VXGE_ERR,
					"%s: vxge_rx_1b_compl: out of "
					"memory", dev->name);
				ring->stats.skb_alloc_fail++;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर ((ext_info.proto & VXGE_HW_FRAME_PROTO_TCP_OR_UDP) &&
		    !(ext_info.proto & VXGE_HW_FRAME_PROTO_IP_FRAG) &&
		    (dev->features & NETIF_F_RXCSUM) && /* Offload Rx side CSUM */
		    ext_info.l3_cksum == VXGE_HW_L3_CKSUM_OK &&
		    ext_info.l4_cksum == VXGE_HW_L4_CKSUM_OK)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अन्यथा
			skb_checksum_none_निश्चित(skb);


		अगर (ring->rx_hwts) अणु
			काष्ठा skb_shared_hwtstamps *skb_hwts;
			u32 ns = *(u32 *)(skb->head + pkt_length);

			skb_hwts = skb_hwtstamps(skb);
			skb_hwts->hwtstamp = ns_to_kसमय(ns);
		पूर्ण

		/* rth_hash_type and rth_it_hit are non-zero regardless of
		 * whether rss is enabled.  Only the rth_value is zero/non-zero
		 * अगर rss is disabled/enabled, so key off of that.
		 */
		अगर (ext_info.rth_value)
			skb_set_hash(skb, ext_info.rth_value,
				     PKT_HASH_TYPE_L3);

		vxge_rx_complete(ring, skb, ext_info.vlan,
			pkt_length, &ext_info);

		ring->budget--;
		ring->pkts_processed++;
		अगर (!ring->budget)
			अवरोध;

	पूर्ण जबतक (vxge_hw_ring_rxd_next_completed(ringh, &dtr,
		&t_code) == VXGE_HW_OK);

	अगर (first_dtr)
		vxge_hw_ring_rxd_post_post_wmb(ringh, first_dtr);

out:
	vxge_debug_entryनिकास(VXGE_TRACE,
				"%s:%d  Exiting...",
				__func__, __LINE__);
	वापस VXGE_HW_OK;
पूर्ण

/*
 * vxge_xmit_compl
 *
 * If an पूर्णांकerrupt was उठाओd to indicate DMA complete of the Tx packet,
 * this function is called. It identअगरies the last TxD whose buffer was
 * मुक्तd and मुक्तs all skbs whose data have alपढ़ोy DMA'ed पूर्णांकo the NICs
 * पूर्णांकernal memory.
 */
अटल क्रमागत vxge_hw_status
vxge_xmit_compl(काष्ठा __vxge_hw_fअगरo *fअगरo_hw, व्योम *dtr,
		क्रमागत vxge_hw_fअगरo_tcode t_code, व्योम *userdata,
		काष्ठा sk_buff ***skb_ptr, पूर्णांक nr_skb, पूर्णांक *more)
अणु
	काष्ठा vxge_fअगरo *fअगरo = (काष्ठा vxge_fअगरo *)userdata;
	काष्ठा sk_buff *skb, **करोne_skb = *skb_ptr;
	पूर्णांक pkt_cnt = 0;

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s:%d Entered....", __func__, __LINE__);

	करो अणु
		पूर्णांक frg_cnt;
		skb_frag_t *frag;
		पूर्णांक i = 0, j;
		काष्ठा vxge_tx_priv *txd_priv =
			vxge_hw_fअगरo_txdl_निजी_get(dtr);

		skb = txd_priv->skb;
		frg_cnt = skb_shinfo(skb)->nr_frags;
		frag = &skb_shinfo(skb)->frags[0];

		vxge_debug_tx(VXGE_TRACE,
				"%s: %s:%d fifo_hw = %p dtr = %p "
				"tcode = 0x%x", fअगरo->ndev->name, __func__,
				__LINE__, fअगरo_hw, dtr, t_code);
		/* check skb validity */
		vxge_निश्चित(skb);
		vxge_debug_tx(VXGE_TRACE,
			"%s: %s:%d skb = %p itxd_priv = %p frg_cnt = %d",
			fअगरo->ndev->name, __func__, __LINE__,
			skb, txd_priv, frg_cnt);
		अगर (unlikely(t_code)) अणु
			fअगरo->stats.tx_errors++;
			vxge_debug_tx(VXGE_ERR,
				"%s: tx: dtr %p completed due to "
				"error t_code %01x", fअगरo->ndev->name,
				dtr, t_code);
			vxge_hw_fअगरo_handle_tcode(fअगरo_hw, dtr, t_code);
		पूर्ण

		/*  क्रम unfragmented skb */
		dma_unmap_single(&fअगरo->pdev->dev, txd_priv->dma_buffers[i++],
				 skb_headlen(skb), DMA_TO_DEVICE);

		क्रम (j = 0; j < frg_cnt; j++) अणु
			dma_unmap_page(&fअगरo->pdev->dev,
				       txd_priv->dma_buffers[i++],
				       skb_frag_size(frag), DMA_TO_DEVICE);
			frag += 1;
		पूर्ण

		vxge_hw_fअगरo_txdl_मुक्त(fअगरo_hw, dtr);

		/* Updating the statistics block */
		u64_stats_update_begin(&fअगरo->stats.syncp);
		fअगरo->stats.tx_frms++;
		fअगरo->stats.tx_bytes += skb->len;
		u64_stats_update_end(&fअगरo->stats.syncp);

		*करोne_skb++ = skb;

		अगर (--nr_skb <= 0) अणु
			*more = 1;
			अवरोध;
		पूर्ण

		pkt_cnt++;
		अगर (pkt_cnt > fअगरo->indicate_max_pkts)
			अवरोध;

	पूर्ण जबतक (vxge_hw_fअगरo_txdl_next_completed(fअगरo_hw,
				&dtr, &t_code) == VXGE_HW_OK);

	*skb_ptr = करोne_skb;
	अगर (netअगर_tx_queue_stopped(fअगरo->txq))
		netअगर_tx_wake_queue(fअगरo->txq);

	vxge_debug_entryनिकास(VXGE_TRACE,
				"%s: %s:%d  Exiting...",
				fअगरo->ndev->name, __func__, __LINE__);
	वापस VXGE_HW_OK;
पूर्ण

/* select a vpath to transmit the packet */
अटल u32 vxge_get_vpath_no(काष्ठा vxgedev *vdev, काष्ठा sk_buff *skb)
अणु
	u16 queue_len, counter = 0;
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *ip;
		काष्ठा tcphdr *th;

		ip = ip_hdr(skb);

		अगर (!ip_is_fragment(ip)) अणु
			th = (काष्ठा tcphdr *)(((अचिन्हित अक्षर *)ip) +
					ip->ihl*4);

			queue_len = vdev->no_of_vpath;
			counter = (ntohs(th->source) +
				ntohs(th->dest)) &
				vdev->vpath_selector[queue_len - 1];
			अगर (counter >= queue_len)
				counter = queue_len - 1;
		पूर्ण
	पूर्ण
	वापस counter;
पूर्ण

अटल क्रमागत vxge_hw_status vxge_search_mac_addr_in_list(
	काष्ठा vxge_vpath *vpath, u64 del_mac)
अणु
	काष्ठा list_head *entry, *next;
	list_क्रम_each_safe(entry, next, &vpath->mac_addr_list) अणु
		अगर (((काष्ठा vxge_mac_addrs *)entry)->macaddr == del_mac)
			वापस TRUE;
	पूर्ण
	वापस FALSE;
पूर्ण

अटल पूर्णांक vxge_mac_list_add(काष्ठा vxge_vpath *vpath, काष्ठा macInfo *mac)
अणु
	काष्ठा vxge_mac_addrs *new_mac_entry;
	u8 *mac_address = शून्य;

	अगर (vpath->mac_addr_cnt >= VXGE_MAX_LEARN_MAC_ADDR_CNT)
		वापस TRUE;

	new_mac_entry = kzalloc(माप(काष्ठा vxge_mac_addrs), GFP_ATOMIC);
	अगर (!new_mac_entry) अणु
		vxge_debug_mem(VXGE_ERR,
			"%s: memory allocation failed",
			VXGE_DRIVER_NAME);
		वापस FALSE;
	पूर्ण

	list_add(&new_mac_entry->item, &vpath->mac_addr_list);

	/* Copy the new mac address to the list */
	mac_address = (u8 *)&new_mac_entry->macaddr;
	स_नकल(mac_address, mac->macaddr, ETH_ALEN);

	new_mac_entry->state = mac->state;
	vpath->mac_addr_cnt++;

	अगर (is_multicast_ether_addr(mac->macaddr))
		vpath->mcast_addr_cnt++;

	वापस TRUE;
पूर्ण

/* Add a mac address to DA table */
अटल क्रमागत vxge_hw_status
vxge_add_mac_addr(काष्ठा vxgedev *vdev, काष्ठा macInfo *mac)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_vpath *vpath;
	क्रमागत vxge_hw_vpath_mac_addr_add_mode duplicate_mode;

	अगर (is_multicast_ether_addr(mac->macaddr))
		duplicate_mode = VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE;
	अन्यथा
		duplicate_mode = VXGE_HW_VPATH_MAC_ADDR_REPLACE_DUPLICATE;

	vpath = &vdev->vpaths[mac->vpath_no];
	status = vxge_hw_vpath_mac_addr_add(vpath->handle, mac->macaddr,
						mac->macmask, duplicate_mode);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"DA config add entry failed for vpath:%d",
			vpath->device_id);
	पूर्ण अन्यथा
		अगर (FALSE == vxge_mac_list_add(vpath, mac))
			status = -EPERM;

	वापस status;
पूर्ण

अटल पूर्णांक vxge_learn_mac(काष्ठा vxgedev *vdev, u8 *mac_header)
अणु
	काष्ठा macInfo mac_info;
	u8 *mac_address = शून्य;
	u64 mac_addr = 0, vpath_vector = 0;
	पूर्णांक vpath_idx = 0;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_vpath *vpath = शून्य;

	mac_address = (u8 *)&mac_addr;
	स_नकल(mac_address, mac_header, ETH_ALEN);

	/* Is this mac address alपढ़ोy in the list? */
	क्रम (vpath_idx = 0; vpath_idx < vdev->no_of_vpath; vpath_idx++) अणु
		vpath = &vdev->vpaths[vpath_idx];
		अगर (vxge_search_mac_addr_in_list(vpath, mac_addr))
			वापस vpath_idx;
	पूर्ण

	स_रखो(&mac_info, 0, माप(काष्ठा macInfo));
	स_नकल(mac_info.macaddr, mac_header, ETH_ALEN);

	/* Any vpath has room to add mac address to its da table? */
	क्रम (vpath_idx = 0; vpath_idx < vdev->no_of_vpath; vpath_idx++) अणु
		vpath = &vdev->vpaths[vpath_idx];
		अगर (vpath->mac_addr_cnt < vpath->max_mac_addr_cnt) अणु
			/* Add this mac address to this vpath */
			mac_info.vpath_no = vpath_idx;
			mac_info.state = VXGE_LL_MAC_ADDR_IN_DA_TABLE;
			status = vxge_add_mac_addr(vdev, &mac_info);
			अगर (status != VXGE_HW_OK)
				वापस -EPERM;
			वापस vpath_idx;
		पूर्ण
	पूर्ण

	mac_info.state = VXGE_LL_MAC_ADDR_IN_LIST;
	vpath_idx = 0;
	mac_info.vpath_no = vpath_idx;
	/* Is the first vpath alपढ़ोy selected as catch-basin ? */
	vpath = &vdev->vpaths[vpath_idx];
	अगर (vpath->mac_addr_cnt > vpath->max_mac_addr_cnt) अणु
		/* Add this mac address to this vpath */
		अगर (FALSE == vxge_mac_list_add(vpath, &mac_info))
			वापस -EPERM;
		वापस vpath_idx;
	पूर्ण

	/* Select first vpath as catch-basin */
	vpath_vector = vxge_mBIT(vpath->device_id);
	status = vxge_hw_mgmt_reg_ग_लिखो(vpath->vdev->devh,
				vxge_hw_mgmt_reg_type_mrpcim,
				0,
				(uदीर्घ)दुरत्व(
					काष्ठा vxge_hw_mrpcim_reg,
					rts_mgr_cbasin_cfg),
				vpath_vector);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_tx(VXGE_ERR,
			"%s: Unable to set the vpath-%d in catch-basin mode",
			VXGE_DRIVER_NAME, vpath->device_id);
		वापस -EPERM;
	पूर्ण

	अगर (FALSE == vxge_mac_list_add(vpath, &mac_info))
		वापस -EPERM;

	वापस vpath_idx;
पूर्ण

/**
 * vxge_xmit
 * @skb : the socket buffer containing the Tx data.
 * @dev : device poपूर्णांकer.
 *
 * This function is the Tx entry poपूर्णांक of the driver. Neterion NIC supports
 * certain protocol assist features on Tx side, namely  CSO, S/G, LSO.
*/
अटल netdev_tx_t
vxge_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा vxge_fअगरo *fअगरo = शून्य;
	व्योम *dtr_priv;
	व्योम *dtr = शून्य;
	काष्ठा vxgedev *vdev = शून्य;
	क्रमागत vxge_hw_status status;
	पूर्णांक frg_cnt, first_frg_len;
	skb_frag_t *frag;
	पूर्णांक i = 0, j = 0, avail;
	u64 dma_poपूर्णांकer;
	काष्ठा vxge_tx_priv *txdl_priv = शून्य;
	काष्ठा __vxge_hw_fअगरo *fअगरo_hw;
	पूर्णांक offload_type;
	पूर्णांक vpath_no = 0;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
			dev->name, __func__, __LINE__);

	/* A buffer with no data will be dropped */
	अगर (unlikely(skb->len <= 0)) अणु
		vxge_debug_tx(VXGE_ERR,
			"%s: Buffer has no data..", dev->name);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	vdev = netdev_priv(dev);

	अगर (unlikely(!is_vxge_card_up(vdev))) अणु
		vxge_debug_tx(VXGE_ERR,
			"%s: vdev not initialized", dev->name);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (vdev->config.addr_learn_en) अणु
		vpath_no = vxge_learn_mac(vdev, skb->data + ETH_ALEN);
		अगर (vpath_no == -EPERM) अणु
			vxge_debug_tx(VXGE_ERR,
				"%s: Failed to store the mac address",
				dev->name);
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	अगर (vdev->config.tx_steering_type == TX_MULTIQ_STEERING)
		vpath_no = skb_get_queue_mapping(skb);
	अन्यथा अगर (vdev->config.tx_steering_type == TX_PORT_STEERING)
		vpath_no = vxge_get_vpath_no(vdev, skb);

	vxge_debug_tx(VXGE_TRACE, "%s: vpath_no= %d", dev->name, vpath_no);

	अगर (vpath_no >= vdev->no_of_vpath)
		vpath_no = 0;

	fअगरo = &vdev->vpaths[vpath_no].fअगरo;
	fअगरo_hw = fअगरo->handle;

	अगर (netअगर_tx_queue_stopped(fअगरo->txq))
		वापस NETDEV_TX_BUSY;

	avail = vxge_hw_fअगरo_मुक्त_txdl_count_get(fअगरo_hw);
	अगर (avail == 0) अणु
		vxge_debug_tx(VXGE_ERR,
			"%s: No free TXDs available", dev->name);
		fअगरo->stats.txd_not_मुक्त++;
		जाओ _निकास0;
	पूर्ण

	/* Last TXD?  Stop tx queue to aव्योम dropping packets.  TX
	 * completion will resume the queue.
	 */
	अगर (avail == 1)
		netअगर_tx_stop_queue(fअगरo->txq);

	status = vxge_hw_fअगरo_txdl_reserve(fअगरo_hw, &dtr, &dtr_priv);
	अगर (unlikely(status != VXGE_HW_OK)) अणु
		vxge_debug_tx(VXGE_ERR,
		   "%s: Out of descriptors .", dev->name);
		fअगरo->stats.txd_out_of_desc++;
		जाओ _निकास0;
	पूर्ण

	vxge_debug_tx(VXGE_TRACE,
		"%s: %s:%d fifo_hw = %p dtr = %p dtr_priv = %p",
		dev->name, __func__, __LINE__,
		fअगरo_hw, dtr, dtr_priv);

	अगर (skb_vlan_tag_present(skb)) अणु
		u16 vlan_tag = skb_vlan_tag_get(skb);
		vxge_hw_fअगरo_txdl_vlan_set(dtr, vlan_tag);
	पूर्ण

	first_frg_len = skb_headlen(skb);

	dma_poपूर्णांकer = dma_map_single(&fअगरo->pdev->dev, skb->data,
				     first_frg_len, DMA_TO_DEVICE);

	अगर (unlikely(dma_mapping_error(&fअगरo->pdev->dev, dma_poपूर्णांकer))) अणु
		vxge_hw_fअगरo_txdl_मुक्त(fअगरo_hw, dtr);
		fअगरo->stats.pci_map_fail++;
		जाओ _निकास0;
	पूर्ण

	txdl_priv = vxge_hw_fअगरo_txdl_निजी_get(dtr);
	txdl_priv->skb = skb;
	txdl_priv->dma_buffers[j] = dma_poपूर्णांकer;

	frg_cnt = skb_shinfo(skb)->nr_frags;
	vxge_debug_tx(VXGE_TRACE,
			"%s: %s:%d skb = %p txdl_priv = %p "
			"frag_cnt = %d dma_pointer = 0x%llx", dev->name,
			__func__, __LINE__, skb, txdl_priv,
			frg_cnt, (अचिन्हित दीर्घ दीर्घ)dma_poपूर्णांकer);

	vxge_hw_fअगरo_txdl_buffer_set(fअगरo_hw, dtr, j++, dma_poपूर्णांकer,
		first_frg_len);

	frag = &skb_shinfo(skb)->frags[0];
	क्रम (i = 0; i < frg_cnt; i++) अणु
		/* ignore 0 length fragment */
		अगर (!skb_frag_size(frag))
			जारी;

		dma_poपूर्णांकer = (u64)skb_frag_dma_map(&fअगरo->pdev->dev, frag,
						    0, skb_frag_size(frag),
						    DMA_TO_DEVICE);

		अगर (unlikely(dma_mapping_error(&fअगरo->pdev->dev, dma_poपूर्णांकer)))
			जाओ _निकास2;
		vxge_debug_tx(VXGE_TRACE,
			"%s: %s:%d frag = %d dma_pointer = 0x%llx",
				dev->name, __func__, __LINE__, i,
				(अचिन्हित दीर्घ दीर्घ)dma_poपूर्णांकer);

		txdl_priv->dma_buffers[j] = dma_poपूर्णांकer;
		vxge_hw_fअगरo_txdl_buffer_set(fअगरo_hw, dtr, j++, dma_poपूर्णांकer,
					skb_frag_size(frag));
		frag += 1;
	पूर्ण

	offload_type = vxge_offload_type(skb);

	अगर (offload_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) अणु
		पूर्णांक mss = vxge_tcp_mss(skb);
		अगर (mss) अणु
			vxge_debug_tx(VXGE_TRACE, "%s: %s:%d mss = %d",
				dev->name, __func__, __LINE__, mss);
			vxge_hw_fअगरo_txdl_mss_set(dtr, mss);
		पूर्ण अन्यथा अणु
			vxge_निश्चित(skb->len <=
				dev->mtu + VXGE_HW_MAC_HEADER_MAX_SIZE);
			vxge_निश्चित(0);
			जाओ _निकास1;
		पूर्ण
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		vxge_hw_fअगरo_txdl_cksum_set_bits(dtr,
					VXGE_HW_FIFO_TXD_TX_CKO_IPV4_EN |
					VXGE_HW_FIFO_TXD_TX_CKO_TCP_EN |
					VXGE_HW_FIFO_TXD_TX_CKO_UDP_EN);

	vxge_hw_fअगरo_txdl_post(fअगरo_hw, dtr);

	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d  Exiting...",
		dev->name, __func__, __LINE__);
	वापस NETDEV_TX_OK;

_निकास2:
	vxge_debug_tx(VXGE_TRACE, "%s: pci_map_page failed", dev->name);
_निकास1:
	j = 0;
	frag = &skb_shinfo(skb)->frags[0];

	dma_unmap_single(&fअगरo->pdev->dev, txdl_priv->dma_buffers[j++],
			 skb_headlen(skb), DMA_TO_DEVICE);

	क्रम (; j < i; j++) अणु
		dma_unmap_page(&fअगरo->pdev->dev, txdl_priv->dma_buffers[j],
			       skb_frag_size(frag), DMA_TO_DEVICE);
		frag += 1;
	पूर्ण

	vxge_hw_fअगरo_txdl_मुक्त(fअगरo_hw, dtr);
_निकास0:
	netअगर_tx_stop_queue(fअगरo->txq);
	dev_kमुक्त_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * vxge_rx_term
 *
 * Function will be called by hw function to पात all outstanding receive
 * descriptors.
 */
अटल व्योम
vxge_rx_term(व्योम *dtrh, क्रमागत vxge_hw_rxd_state state, व्योम *userdata)
अणु
	काष्ठा vxge_ring *ring = (काष्ठा vxge_ring *)userdata;
	काष्ठा vxge_rx_priv *rx_priv =
		vxge_hw_ring_rxd_निजी_get(dtrh);

	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
			ring->ndev->name, __func__, __LINE__);
	अगर (state != VXGE_HW_RXD_STATE_POSTED)
		वापस;

	dma_unmap_single(&ring->pdev->dev, rx_priv->data_dma,
			 rx_priv->data_size, DMA_FROM_DEVICE);

	dev_kमुक्त_skb(rx_priv->skb);
	rx_priv->skb_data = शून्य;

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d  Exiting...",
		ring->ndev->name, __func__, __LINE__);
पूर्ण

/*
 * vxge_tx_term
 *
 * Function will be called to पात all outstanding tx descriptors
 */
अटल व्योम
vxge_tx_term(व्योम *dtrh, क्रमागत vxge_hw_txdl_state state, व्योम *userdata)
अणु
	काष्ठा vxge_fअगरo *fअगरo = (काष्ठा vxge_fअगरo *)userdata;
	skb_frag_t *frag;
	पूर्णांक i = 0, j, frg_cnt;
	काष्ठा vxge_tx_priv *txd_priv = vxge_hw_fअगरo_txdl_निजी_get(dtrh);
	काष्ठा sk_buff *skb = txd_priv->skb;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s:%d", __func__, __LINE__);

	अगर (state != VXGE_HW_TXDL_STATE_POSTED)
		वापस;

	/* check skb validity */
	vxge_निश्चित(skb);
	frg_cnt = skb_shinfo(skb)->nr_frags;
	frag = &skb_shinfo(skb)->frags[0];

	/*  क्रम unfragmented skb */
	dma_unmap_single(&fअगरo->pdev->dev, txd_priv->dma_buffers[i++],
			 skb_headlen(skb), DMA_TO_DEVICE);

	क्रम (j = 0; j < frg_cnt; j++) अणु
		dma_unmap_page(&fअगरo->pdev->dev, txd_priv->dma_buffers[i++],
			       skb_frag_size(frag), DMA_TO_DEVICE);
		frag += 1;
	पूर्ण

	dev_kमुक्त_skb(skb);

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s:%d  Exiting...", __func__, __LINE__);
पूर्ण

अटल पूर्णांक vxge_mac_list_del(काष्ठा vxge_vpath *vpath, काष्ठा macInfo *mac)
अणु
	काष्ठा list_head *entry, *next;
	u64 del_mac = 0;
	u8 *mac_address = (u8 *) (&del_mac);

	/* Copy the mac address to delete from the list */
	स_नकल(mac_address, mac->macaddr, ETH_ALEN);

	list_क्रम_each_safe(entry, next, &vpath->mac_addr_list) अणु
		अगर (((काष्ठा vxge_mac_addrs *)entry)->macaddr == del_mac) अणु
			list_del(entry);
			kमुक्त(entry);
			vpath->mac_addr_cnt--;

			अगर (is_multicast_ether_addr(mac->macaddr))
				vpath->mcast_addr_cnt--;
			वापस TRUE;
		पूर्ण
	पूर्ण

	वापस FALSE;
पूर्ण

/* delete a mac address from DA table */
अटल क्रमागत vxge_hw_status
vxge_del_mac_addr(काष्ठा vxgedev *vdev, काष्ठा macInfo *mac)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_vpath *vpath;

	vpath = &vdev->vpaths[mac->vpath_no];
	status = vxge_hw_vpath_mac_addr_delete(vpath->handle, mac->macaddr,
						mac->macmask);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"DA config delete entry failed for vpath:%d",
			vpath->device_id);
	पूर्ण अन्यथा
		vxge_mac_list_del(vpath, mac);
	वापस status;
पूर्ण

/**
 * vxge_set_multicast
 * @dev: poपूर्णांकer to the device काष्ठाure
 *
 * Entry poपूर्णांक क्रम multicast address enable/disable
 * This function is a driver entry poपूर्णांक which माला_लो called by the kernel
 * whenever multicast addresses must be enabled/disabled. This also माला_लो
 * called to set/reset promiscuous mode. Depending on the deivce flag, we
 * determine, अगर multicast address must be enabled or अगर promiscuous mode
 * is to be disabled etc.
 */
अटल व्योम vxge_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	काष्ठा vxgedev *vdev;
	पूर्णांक i, mcast_cnt = 0;
	काष्ठा vxge_vpath *vpath;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा macInfo mac_info;
	पूर्णांक vpath_idx = 0;
	काष्ठा vxge_mac_addrs *mac_entry;
	काष्ठा list_head *list_head;
	काष्ठा list_head *entry, *next;
	u8 *mac_address = शून्य;

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s:%d", __func__, __LINE__);

	vdev = netdev_priv(dev);

	अगर (unlikely(!is_vxge_card_up(vdev)))
		वापस;

	अगर ((dev->flags & IFF_ALLMULTI) && (!vdev->all_multi_flg)) अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vpath = &vdev->vpaths[i];
			vxge_निश्चित(vpath->is_खोलो);
			status = vxge_hw_vpath_mcast_enable(vpath->handle);
			अगर (status != VXGE_HW_OK)
				vxge_debug_init(VXGE_ERR, "failed to enable "
						"multicast, status %d", status);
			vdev->all_multi_flg = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (!(dev->flags & IFF_ALLMULTI) && (vdev->all_multi_flg)) अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vpath = &vdev->vpaths[i];
			vxge_निश्चित(vpath->is_खोलो);
			status = vxge_hw_vpath_mcast_disable(vpath->handle);
			अगर (status != VXGE_HW_OK)
				vxge_debug_init(VXGE_ERR, "failed to disable "
						"multicast, status %d", status);
			vdev->all_multi_flg = 0;
		पूर्ण
	पूर्ण


	अगर (!vdev->config.addr_learn_en) अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vpath = &vdev->vpaths[i];
			vxge_निश्चित(vpath->is_खोलो);

			अगर (dev->flags & IFF_PROMISC)
				status = vxge_hw_vpath_promisc_enable(
					vpath->handle);
			अन्यथा
				status = vxge_hw_vpath_promisc_disable(
					vpath->handle);
			अगर (status != VXGE_HW_OK)
				vxge_debug_init(VXGE_ERR, "failed to %s promisc"
					", status %d", dev->flags&IFF_PROMISC ?
					"enable" : "disable", status);
		पूर्ण
	पूर्ण

	स_रखो(&mac_info, 0, माप(काष्ठा macInfo));
	/* Update inभागidual M_CAST address list */
	अगर ((!vdev->all_multi_flg) && netdev_mc_count(dev)) अणु
		mcast_cnt = vdev->vpaths[0].mcast_addr_cnt;
		list_head = &vdev->vpaths[0].mac_addr_list;
		अगर ((netdev_mc_count(dev) +
			(vdev->vpaths[0].mac_addr_cnt - mcast_cnt)) >
				vdev->vpaths[0].max_mac_addr_cnt)
			जाओ _set_all_mcast;

		/* Delete previous MC's */
		क्रम (i = 0; i < mcast_cnt; i++) अणु
			list_क्रम_each_safe(entry, next, list_head) अणु
				mac_entry = (काष्ठा vxge_mac_addrs *)entry;
				/* Copy the mac address to delete */
				mac_address = (u8 *)&mac_entry->macaddr;
				स_नकल(mac_info.macaddr, mac_address, ETH_ALEN);

				अगर (is_multicast_ether_addr(mac_info.macaddr)) अणु
					क्रम (vpath_idx = 0; vpath_idx <
						vdev->no_of_vpath;
						vpath_idx++) अणु
						mac_info.vpath_no = vpath_idx;
						status = vxge_del_mac_addr(
								vdev,
								&mac_info);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		/* Add new ones */
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			स_नकल(mac_info.macaddr, ha->addr, ETH_ALEN);
			क्रम (vpath_idx = 0; vpath_idx < vdev->no_of_vpath;
					vpath_idx++) अणु
				mac_info.vpath_no = vpath_idx;
				mac_info.state = VXGE_LL_MAC_ADDR_IN_DA_TABLE;
				status = vxge_add_mac_addr(vdev, &mac_info);
				अगर (status != VXGE_HW_OK) अणु
					vxge_debug_init(VXGE_ERR,
						"%s:%d Setting individual"
						"multicast address failed",
						__func__, __LINE__);
					जाओ _set_all_mcast;
				पूर्ण
			पूर्ण
		पूर्ण

		वापस;
_set_all_mcast:
		mcast_cnt = vdev->vpaths[0].mcast_addr_cnt;
		/* Delete previous MC's */
		क्रम (i = 0; i < mcast_cnt; i++) अणु
			list_क्रम_each_safe(entry, next, list_head) अणु
				mac_entry = (काष्ठा vxge_mac_addrs *)entry;
				/* Copy the mac address to delete */
				mac_address = (u8 *)&mac_entry->macaddr;
				स_नकल(mac_info.macaddr, mac_address, ETH_ALEN);

				अगर (is_multicast_ether_addr(mac_info.macaddr))
					अवरोध;
			पूर्ण

			क्रम (vpath_idx = 0; vpath_idx < vdev->no_of_vpath;
					vpath_idx++) अणु
				mac_info.vpath_no = vpath_idx;
				status = vxge_del_mac_addr(vdev, &mac_info);
			पूर्ण
		पूर्ण

		/* Enable all multicast */
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vpath = &vdev->vpaths[i];
			vxge_निश्चित(vpath->is_खोलो);

			status = vxge_hw_vpath_mcast_enable(vpath->handle);
			अगर (status != VXGE_HW_OK) अणु
				vxge_debug_init(VXGE_ERR,
					"%s:%d Enabling all multicasts failed",
					 __func__, __LINE__);
			पूर्ण
			vdev->all_multi_flg = 1;
		पूर्ण
		dev->flags |= IFF_ALLMULTI;
	पूर्ण

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s:%d  Exiting...", __func__, __LINE__);
पूर्ण

/**
 * vxge_set_mac_addr
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @p: socket info
 *
 * Update entry "0" (शेष MAC addr)
 */
अटल पूर्णांक vxge_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा vxgedev *vdev;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा macInfo mac_info_new, mac_info_old;
	पूर्णांक vpath_idx = 0;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s:%d", __func__, __LINE__);

	vdev = netdev_priv(dev);

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EINVAL;

	स_रखो(&mac_info_new, 0, माप(काष्ठा macInfo));
	स_रखो(&mac_info_old, 0, माप(काष्ठा macInfo));

	vxge_debug_entryनिकास(VXGE_TRACE, "%s:%d  Exiting...",
		__func__, __LINE__);

	/* Get the old address */
	स_नकल(mac_info_old.macaddr, dev->dev_addr, dev->addr_len);

	/* Copy the new address */
	स_नकल(mac_info_new.macaddr, addr->sa_data, dev->addr_len);

	/* First delete the old mac address from all the vpaths
	as we can't specअगरy the index जबतक adding new mac address */
	क्रम (vpath_idx = 0; vpath_idx < vdev->no_of_vpath; vpath_idx++) अणु
		काष्ठा vxge_vpath *vpath = &vdev->vpaths[vpath_idx];
		अगर (!vpath->is_खोलो) अणु
			/* This can happen when this पूर्णांकerface is added/हटाओd
			to the bonding पूर्णांकerface. Delete this station address
			from the linked list */
			vxge_mac_list_del(vpath, &mac_info_old);

			/* Add this new address to the linked list
			क्रम later restoring */
			vxge_mac_list_add(vpath, &mac_info_new);

			जारी;
		पूर्ण
		/* Delete the station address */
		mac_info_old.vpath_no = vpath_idx;
		status = vxge_del_mac_addr(vdev, &mac_info_old);
	पूर्ण

	अगर (unlikely(!is_vxge_card_up(vdev))) अणु
		स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
		वापस VXGE_HW_OK;
	पूर्ण

	/* Set this mac address to all the vpaths */
	क्रम (vpath_idx = 0; vpath_idx < vdev->no_of_vpath; vpath_idx++) अणु
		mac_info_new.vpath_no = vpath_idx;
		mac_info_new.state = VXGE_LL_MAC_ADDR_IN_DA_TABLE;
		status = vxge_add_mac_addr(vdev, &mac_info_new);
		अगर (status != VXGE_HW_OK)
			वापस -EINVAL;
	पूर्ण

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	वापस status;
पूर्ण

/*
 * vxge_vpath_पूर्णांकr_enable
 * @vdev: poपूर्णांकer to vdev
 * @vp_id: vpath क्रम which to enable the पूर्णांकerrupts
 *
 * Enables the पूर्णांकerrupts क्रम the vpath
*/
अटल व्योम vxge_vpath_पूर्णांकr_enable(काष्ठा vxgedev *vdev, पूर्णांक vp_id)
अणु
	काष्ठा vxge_vpath *vpath = &vdev->vpaths[vp_id];
	पूर्णांक msix_id = 0;
	पूर्णांक tim_msix_id[4] = अणु0, 1, 0, 0पूर्ण;
	पूर्णांक alarm_msix_id = VXGE_ALARM_MSIX_ID;

	vxge_hw_vpath_पूर्णांकr_enable(vpath->handle);

	अगर (vdev->config.पूर्णांकr_type == INTA)
		vxge_hw_vpath_पूर्णांकa_unmask_tx_rx(vpath->handle);
	अन्यथा अणु
		vxge_hw_vpath_msix_set(vpath->handle, tim_msix_id,
			alarm_msix_id);

		msix_id = vpath->device_id * VXGE_HW_VPATH_MSIX_ACTIVE;
		vxge_hw_vpath_msix_unmask(vpath->handle, msix_id);
		vxge_hw_vpath_msix_unmask(vpath->handle, msix_id + 1);

		/* enable the alarm vector */
		msix_id = (vpath->handle->vpath->hldev->first_vp_id *
			VXGE_HW_VPATH_MSIX_ACTIVE) + alarm_msix_id;
		vxge_hw_vpath_msix_unmask(vpath->handle, msix_id);
	पूर्ण
पूर्ण

/*
 * vxge_vpath_पूर्णांकr_disable
 * @vdev: poपूर्णांकer to vdev
 * @vp_id: vpath क्रम which to disable the पूर्णांकerrupts
 *
 * Disables the पूर्णांकerrupts क्रम the vpath
*/
अटल व्योम vxge_vpath_पूर्णांकr_disable(काष्ठा vxgedev *vdev, पूर्णांक vp_id)
अणु
	काष्ठा vxge_vpath *vpath = &vdev->vpaths[vp_id];
	काष्ठा __vxge_hw_device *hldev;
	पूर्णांक msix_id;

	hldev = pci_get_drvdata(vdev->pdev);

	vxge_hw_vpath_रुको_receive_idle(hldev, vpath->device_id);

	vxge_hw_vpath_पूर्णांकr_disable(vpath->handle);

	अगर (vdev->config.पूर्णांकr_type == INTA)
		vxge_hw_vpath_पूर्णांकa_mask_tx_rx(vpath->handle);
	अन्यथा अणु
		msix_id = vpath->device_id * VXGE_HW_VPATH_MSIX_ACTIVE;
		vxge_hw_vpath_msix_mask(vpath->handle, msix_id);
		vxge_hw_vpath_msix_mask(vpath->handle, msix_id + 1);

		/* disable the alarm vector */
		msix_id = (vpath->handle->vpath->hldev->first_vp_id *
			VXGE_HW_VPATH_MSIX_ACTIVE) + VXGE_ALARM_MSIX_ID;
		vxge_hw_vpath_msix_mask(vpath->handle, msix_id);
	पूर्ण
पूर्ण

/* list all mac addresses from DA table */
अटल क्रमागत vxge_hw_status
vxge_search_mac_addr_in_da_table(काष्ठा vxge_vpath *vpath, काष्ठा macInfo *mac)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	अचिन्हित अक्षर macmask[ETH_ALEN];
	अचिन्हित अक्षर macaddr[ETH_ALEN];

	status = vxge_hw_vpath_mac_addr_get(vpath->handle,
				macaddr, macmask);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"DA config list entry failed for vpath:%d",
			vpath->device_id);
		वापस status;
	पूर्ण

	जबतक (!ether_addr_equal(mac->macaddr, macaddr)) अणु
		status = vxge_hw_vpath_mac_addr_get_next(vpath->handle,
				macaddr, macmask);
		अगर (status != VXGE_HW_OK)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/* Store all mac addresses from the list to the DA table */
अटल क्रमागत vxge_hw_status vxge_restore_vpath_mac_addr(काष्ठा vxge_vpath *vpath)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा macInfo mac_info;
	u8 *mac_address = शून्य;
	काष्ठा list_head *entry, *next;

	स_रखो(&mac_info, 0, माप(काष्ठा macInfo));

	अगर (vpath->is_खोलो) अणु
		list_क्रम_each_safe(entry, next, &vpath->mac_addr_list) अणु
			mac_address =
				(u8 *)&
				((काष्ठा vxge_mac_addrs *)entry)->macaddr;
			स_नकल(mac_info.macaddr, mac_address, ETH_ALEN);
			((काष्ठा vxge_mac_addrs *)entry)->state =
				VXGE_LL_MAC_ADDR_IN_DA_TABLE;
			/* करोes this mac address alपढ़ोy exist in da table? */
			status = vxge_search_mac_addr_in_da_table(vpath,
				&mac_info);
			अगर (status != VXGE_HW_OK) अणु
				/* Add this mac address to the DA table */
				status = vxge_hw_vpath_mac_addr_add(
					vpath->handle, mac_info.macaddr,
					mac_info.macmask,
				    VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE);
				अगर (status != VXGE_HW_OK) अणु
					vxge_debug_init(VXGE_ERR,
					    "DA add entry failed for vpath:%d",
					    vpath->device_id);
					((काष्ठा vxge_mac_addrs *)entry)->state
						= VXGE_LL_MAC_ADDR_IN_LIST;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/* Store all vlan ids from the list to the vid table */
अटल क्रमागत vxge_hw_status
vxge_restore_vpath_vid_table(काष्ठा vxge_vpath *vpath)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxgedev *vdev = vpath->vdev;
	u16 vid;

	अगर (!vpath->is_खोलो)
		वापस status;

	क्रम_each_set_bit(vid, vdev->active_vlans, VLAN_N_VID)
		status = vxge_hw_vpath_vid_add(vpath->handle, vid);

	वापस status;
पूर्ण

/*
 * vxge_reset_vpath
 * @vdev: poपूर्णांकer to vdev
 * @vp_id: vpath to reset
 *
 * Resets the vpath
*/
अटल पूर्णांक vxge_reset_vpath(काष्ठा vxgedev *vdev, पूर्णांक vp_id)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_vpath *vpath = &vdev->vpaths[vp_id];
	पूर्णांक ret = 0;

	/* check अगर device is करोwn alपढ़ोy */
	अगर (unlikely(!is_vxge_card_up(vdev)))
		वापस 0;

	/* is device reset alपढ़ोy scheduled */
	अगर (test_bit(__VXGE_STATE_RESET_CARD, &vdev->state))
		वापस 0;

	अगर (vpath->handle) अणु
		अगर (vxge_hw_vpath_reset(vpath->handle) == VXGE_HW_OK) अणु
			अगर (is_vxge_card_up(vdev) &&
				vxge_hw_vpath_recover_from_reset(vpath->handle)
					!= VXGE_HW_OK) अणु
				vxge_debug_init(VXGE_ERR,
					"vxge_hw_vpath_recover_from_reset"
					"failed for vpath:%d", vp_id);
				वापस status;
			पूर्ण
		पूर्ण अन्यथा अणु
			vxge_debug_init(VXGE_ERR,
				"vxge_hw_vpath_reset failed for"
				"vpath:%d", vp_id);
			वापस status;
		पूर्ण
	पूर्ण अन्यथा
		वापस VXGE_HW_FAIL;

	vxge_restore_vpath_mac_addr(vpath);
	vxge_restore_vpath_vid_table(vpath);

	/* Enable all broadcast */
	vxge_hw_vpath_bcast_enable(vpath->handle);

	/* Enable all multicast */
	अगर (vdev->all_multi_flg) अणु
		status = vxge_hw_vpath_mcast_enable(vpath->handle);
		अगर (status != VXGE_HW_OK)
			vxge_debug_init(VXGE_ERR,
				"%s:%d Enabling multicast failed",
				__func__, __LINE__);
	पूर्ण

	/* Enable the पूर्णांकerrupts */
	vxge_vpath_पूर्णांकr_enable(vdev, vp_id);

	smp_wmb();

	/* Enable the flow of traffic through the vpath */
	vxge_hw_vpath_enable(vpath->handle);

	smp_wmb();
	vxge_hw_vpath_rx_करोorbell_init(vpath->handle);
	vpath->ring.last_status = VXGE_HW_OK;

	/* Vpath reset करोne */
	clear_bit(vp_id, &vdev->vp_reset);

	/* Start the vpath queue */
	अगर (netअगर_tx_queue_stopped(vpath->fअगरo.txq))
		netअगर_tx_wake_queue(vpath->fअगरo.txq);

	वापस ret;
पूर्ण

/* Configure CI */
अटल व्योम vxge_config_ci_क्रम_tti_rti(काष्ठा vxgedev *vdev)
अणु
	पूर्णांक i = 0;

	/* Enable CI क्रम RTI */
	अगर (vdev->config.पूर्णांकr_type == MSI_X) अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			काष्ठा __vxge_hw_ring *hw_ring;

			hw_ring = vdev->vpaths[i].ring.handle;
			vxge_hw_vpath_dynamic_rti_ci_set(hw_ring);
		पूर्ण
	पूर्ण

	/* Enable CI क्रम TTI */
	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		काष्ठा __vxge_hw_fअगरo *hw_fअगरo = vdev->vpaths[i].fअगरo.handle;
		vxge_hw_vpath_tti_ci_set(hw_fअगरo);
		/*
		 * For Inta (with or without napi), Set CI ON क्रम only one
		 * vpath. (Have only one मुक्त running समयr).
		 */
		अगर ((vdev->config.पूर्णांकr_type == INTA) && (i == 0))
			अवरोध;
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक करो_vxge_reset(काष्ठा vxgedev *vdev, पूर्णांक event)
अणु
	क्रमागत vxge_hw_status status;
	पूर्णांक ret = 0, vp_id, i;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s:%d", __func__, __LINE__);

	अगर ((event == VXGE_LL_FULL_RESET) || (event == VXGE_LL_START_RESET)) अणु
		/* check अगर device is करोwn alपढ़ोy */
		अगर (unlikely(!is_vxge_card_up(vdev)))
			वापस 0;

		/* is reset alपढ़ोy scheduled */
		अगर (test_and_set_bit(__VXGE_STATE_RESET_CARD, &vdev->state))
			वापस 0;
	पूर्ण

	अगर (event == VXGE_LL_FULL_RESET) अणु
		netअगर_carrier_off(vdev->ndev);

		/* रुको क्रम all the vpath reset to complete */
		क्रम (vp_id = 0; vp_id < vdev->no_of_vpath; vp_id++) अणु
			जबतक (test_bit(vp_id, &vdev->vp_reset))
				msleep(50);
		पूर्ण

		netअगर_carrier_on(vdev->ndev);

		/* अगर execution mode is set to debug, करोn't reset the adapter */
		अगर (unlikely(vdev->exec_mode)) अणु
			vxge_debug_init(VXGE_ERR,
				"%s: execution mode is debug, returning..",
				vdev->ndev->name);
			clear_bit(__VXGE_STATE_CARD_UP, &vdev->state);
			netअगर_tx_stop_all_queues(vdev->ndev);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (event == VXGE_LL_FULL_RESET) अणु
		vxge_hw_device_रुको_receive_idle(vdev->devh);
		vxge_hw_device_पूर्णांकr_disable(vdev->devh);

		चयन (vdev->cric_err_event) अणु
		हाल VXGE_HW_EVENT_UNKNOWN:
			netअगर_tx_stop_all_queues(vdev->ndev);
			vxge_debug_init(VXGE_ERR,
				"fatal: %s: Disabling device due to"
				"unknown error",
				vdev->ndev->name);
			ret = -EPERM;
			जाओ out;
		हाल VXGE_HW_EVENT_RESET_START:
			अवरोध;
		हाल VXGE_HW_EVENT_RESET_COMPLETE:
		हाल VXGE_HW_EVENT_LINK_DOWN:
		हाल VXGE_HW_EVENT_LINK_UP:
		हाल VXGE_HW_EVENT_ALARM_CLEARED:
		हाल VXGE_HW_EVENT_ECCERR:
		हाल VXGE_HW_EVENT_MRPCIM_ECCERR:
			ret = -EPERM;
			जाओ out;
		हाल VXGE_HW_EVENT_FIFO_ERR:
		हाल VXGE_HW_EVENT_VPATH_ERR:
			अवरोध;
		हाल VXGE_HW_EVENT_CRITICAL_ERR:
			netअगर_tx_stop_all_queues(vdev->ndev);
			vxge_debug_init(VXGE_ERR,
				"fatal: %s: Disabling device due to"
				"serious error",
				vdev->ndev->name);
			/* SOP or device reset required */
			/* This event is not currently used */
			ret = -EPERM;
			जाओ out;
		हाल VXGE_HW_EVENT_SERR:
			netअगर_tx_stop_all_queues(vdev->ndev);
			vxge_debug_init(VXGE_ERR,
				"fatal: %s: Disabling device due to"
				"serious error",
				vdev->ndev->name);
			ret = -EPERM;
			जाओ out;
		हाल VXGE_HW_EVENT_SRPCIM_SERR:
		हाल VXGE_HW_EVENT_MRPCIM_SERR:
			ret = -EPERM;
			जाओ out;
		हाल VXGE_HW_EVENT_SLOT_FREEZE:
			netअगर_tx_stop_all_queues(vdev->ndev);
			vxge_debug_init(VXGE_ERR,
				"fatal: %s: Disabling device due to"
				"slot freeze",
				vdev->ndev->name);
			ret = -EPERM;
			जाओ out;
		शेष:
			अवरोध;

		पूर्ण
	पूर्ण

	अगर ((event == VXGE_LL_FULL_RESET) || (event == VXGE_LL_START_RESET))
		netअगर_tx_stop_all_queues(vdev->ndev);

	अगर (event == VXGE_LL_FULL_RESET) अणु
		status = vxge_reset_all_vpaths(vdev);
		अगर (status != VXGE_HW_OK) अणु
			vxge_debug_init(VXGE_ERR,
				"fatal: %s: can not reset vpaths",
				vdev->ndev->name);
			ret = -EPERM;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (event == VXGE_LL_COMPL_RESET) अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++)
			अगर (vdev->vpaths[i].handle) अणु
				अगर (vxge_hw_vpath_recover_from_reset(
					vdev->vpaths[i].handle)
						!= VXGE_HW_OK) अणु
					vxge_debug_init(VXGE_ERR,
						"vxge_hw_vpath_recover_"
						"from_reset failed for vpath: "
						"%d", i);
					ret = -EPERM;
					जाओ out;
				पूर्ण
				पूर्ण अन्यथा अणु
					vxge_debug_init(VXGE_ERR,
					"vxge_hw_vpath_reset failed for "
						"vpath:%d", i);
					ret = -EPERM;
					जाओ out;
				पूर्ण
	पूर्ण

	अगर ((event == VXGE_LL_FULL_RESET) || (event == VXGE_LL_COMPL_RESET)) अणु
		/* Reprogram the DA table with populated mac addresses */
		क्रम (vp_id = 0; vp_id < vdev->no_of_vpath; vp_id++) अणु
			vxge_restore_vpath_mac_addr(&vdev->vpaths[vp_id]);
			vxge_restore_vpath_vid_table(&vdev->vpaths[vp_id]);
		पूर्ण

		/* enable vpath पूर्णांकerrupts */
		क्रम (i = 0; i < vdev->no_of_vpath; i++)
			vxge_vpath_पूर्णांकr_enable(vdev, i);

		vxge_hw_device_पूर्णांकr_enable(vdev->devh);

		smp_wmb();

		/* Indicate card up */
		set_bit(__VXGE_STATE_CARD_UP, &vdev->state);

		/* Get the traffic to flow through the vpaths */
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vxge_hw_vpath_enable(vdev->vpaths[i].handle);
			smp_wmb();
			vxge_hw_vpath_rx_करोorbell_init(vdev->vpaths[i].handle);
		पूर्ण

		netअगर_tx_wake_all_queues(vdev->ndev);
	पूर्ण

	/* configure CI */
	vxge_config_ci_क्रम_tti_rti(vdev);

out:
	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s:%d  Exiting...", __func__, __LINE__);

	/* Indicate reset करोne */
	अगर ((event == VXGE_LL_FULL_RESET) || (event == VXGE_LL_COMPL_RESET))
		clear_bit(__VXGE_STATE_RESET_CARD, &vdev->state);
	वापस ret;
पूर्ण

/*
 * vxge_reset
 * @vdev: poपूर्णांकer to ll device
 *
 * driver may reset the chip on events of serr, eccerr, etc
 */
अटल व्योम vxge_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vxgedev *vdev = container_of(work, काष्ठा vxgedev, reset_task);

	अगर (!netअगर_running(vdev->ndev))
		वापस;

	करो_vxge_reset(vdev, VXGE_LL_FULL_RESET);
पूर्ण

/**
 * vxge_poll - Receive handler when Receive Polling is used.
 * @napi: poपूर्णांकer to the napi काष्ठाure.
 * @budget: Number of packets budgeted to be processed in this iteration.
 *
 * This function comes पूर्णांकo picture only अगर Receive side is being handled
 * through polling (called NAPI in linux). It mostly करोes what the normal
 * Rx पूर्णांकerrupt handler करोes in terms of descriptor and packet processing
 * but not in an पूर्णांकerrupt context. Also it will process a specअगरied number
 * of packets at most in one iteration. This value is passed करोwn by the
 * kernel as the function argument 'budget'.
 */
अटल पूर्णांक vxge_poll_msix(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा vxge_ring *ring = container_of(napi, काष्ठा vxge_ring, napi);
	पूर्णांक pkts_processed;
	पूर्णांक budget_org = budget;

	ring->budget = budget;
	ring->pkts_processed = 0;
	vxge_hw_vpath_poll_rx(ring->handle);
	pkts_processed = ring->pkts_processed;

	अगर (pkts_processed < budget_org) अणु
		napi_complete_करोne(napi, pkts_processed);

		/* Re enable the Rx पूर्णांकerrupts क्रम the vpath */
		vxge_hw_channel_msix_unmask(
				(काष्ठा __vxge_hw_channel *)ring->handle,
				ring->rx_vector_no);
	पूर्ण

	/* We are copying and वापसing the local variable, in हाल अगर after
	 * clearing the msix पूर्णांकerrupt above, अगर the पूर्णांकerrupt fires right
	 * away which can preempt this NAPI thपढ़ो */
	वापस pkts_processed;
पूर्ण

अटल पूर्णांक vxge_poll_पूर्णांकa(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा vxgedev *vdev = container_of(napi, काष्ठा vxgedev, napi);
	पूर्णांक pkts_processed = 0;
	पूर्णांक i;
	पूर्णांक budget_org = budget;
	काष्ठा vxge_ring *ring;

	काष्ठा __vxge_hw_device *hldev = pci_get_drvdata(vdev->pdev);

	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		ring = &vdev->vpaths[i].ring;
		ring->budget = budget;
		ring->pkts_processed = 0;
		vxge_hw_vpath_poll_rx(ring->handle);
		pkts_processed += ring->pkts_processed;
		budget -= ring->pkts_processed;
		अगर (budget <= 0)
			अवरोध;
	पूर्ण

	VXGE_COMPLETE_ALL_TX(vdev);

	अगर (pkts_processed < budget_org) अणु
		napi_complete_करोne(napi, pkts_processed);
		/* Re enable the Rx पूर्णांकerrupts क्रम the ring */
		vxge_hw_device_unmask_all(hldev);
		vxge_hw_device_flush_io(hldev);
	पूर्ण

	वापस pkts_processed;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * vxge_netpoll - netpoll event handler entry poपूर्णांक
 * @dev : poपूर्णांकer to the device काष्ठाure.
 * Description:
 *      This function will be called by upper layer to check क्रम events on the
 * पूर्णांकerface in situations where पूर्णांकerrupts are disabled. It is used क्रम
 * specअगरic in-kernel networking tasks, such as remote consoles and kernel
 * debugging over the network (example netdump in RedHat).
 */
अटल व्योम vxge_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा pci_dev *pdev = vdev->pdev;
	काष्ठा __vxge_hw_device *hldev = pci_get_drvdata(pdev);
	स्थिर पूर्णांक irq = pdev->irq;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s:%d", __func__, __LINE__);

	अगर (pci_channel_offline(pdev))
		वापस;

	disable_irq(irq);
	vxge_hw_device_clear_tx_rx(hldev);

	vxge_hw_device_clear_tx_rx(hldev);
	VXGE_COMPLETE_ALL_RX(vdev);
	VXGE_COMPLETE_ALL_TX(vdev);

	enable_irq(irq);

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s:%d  Exiting...", __func__, __LINE__);
पूर्ण
#पूर्ण_अगर

/* RTH configuration */
अटल क्रमागत vxge_hw_status vxge_rth_configure(काष्ठा vxgedev *vdev)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_hw_rth_hash_types hash_types;
	u8 itable[256] = अणु0पूर्ण; /* indirection table */
	u8 mtable[256] = अणु0पूर्ण; /* CPU to vpath mapping  */
	पूर्णांक index;

	/*
	 * Filling
	 * 	- itable with bucket numbers
	 * 	- mtable with bucket-to-vpath mapping
	 */
	क्रम (index = 0; index < (1 << vdev->config.rth_bkt_sz); index++) अणु
		itable[index] = index;
		mtable[index] = index % vdev->no_of_vpath;
	पूर्ण

	/* set indirection table, bucket-to-vpath mapping */
	status = vxge_hw_vpath_rts_rth_itable_set(vdev->vp_handles,
						vdev->no_of_vpath,
						mtable, itable,
						vdev->config.rth_bkt_sz);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"RTH indirection table configuration failed "
			"for vpath:%d", vdev->vpaths[0].device_id);
		वापस status;
	पूर्ण

	/* Fill RTH hash types */
	hash_types.hash_type_tcpipv4_en   = vdev->config.rth_hash_type_tcpipv4;
	hash_types.hash_type_ipv4_en      = vdev->config.rth_hash_type_ipv4;
	hash_types.hash_type_tcpipv6_en   = vdev->config.rth_hash_type_tcpipv6;
	hash_types.hash_type_ipv6_en      = vdev->config.rth_hash_type_ipv6;
	hash_types.hash_type_tcpipv6ex_en =
					vdev->config.rth_hash_type_tcpipv6ex;
	hash_types.hash_type_ipv6ex_en    = vdev->config.rth_hash_type_ipv6ex;

	/*
	 * Because the itable_set() method uses the active_table field
	 * क्रम the target भव path the RTH config should be updated
	 * क्रम all VPATHs. The h/w only uses the lowest numbered VPATH
	 * when steering frames.
	 */
	क्रम (index = 0; index < vdev->no_of_vpath; index++) अणु
		status = vxge_hw_vpath_rts_rth_set(
				vdev->vpaths[index].handle,
				vdev->config.rth_algorithm,
				&hash_types,
				vdev->config.rth_bkt_sz);
		अगर (status != VXGE_HW_OK) अणु
			vxge_debug_init(VXGE_ERR,
				"RTH configuration failed for vpath:%d",
				vdev->vpaths[index].device_id);
			वापस status;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/* reset vpaths */
अटल क्रमागत vxge_hw_status vxge_reset_all_vpaths(काष्ठा vxgedev *vdev)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_vpath *vpath;
	पूर्णांक i;

	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		vpath = &vdev->vpaths[i];
		अगर (vpath->handle) अणु
			अगर (vxge_hw_vpath_reset(vpath->handle) == VXGE_HW_OK) अणु
				अगर (is_vxge_card_up(vdev) &&
					vxge_hw_vpath_recover_from_reset(
						vpath->handle) != VXGE_HW_OK) अणु
					vxge_debug_init(VXGE_ERR,
						"vxge_hw_vpath_recover_"
						"from_reset failed for vpath: "
						"%d", i);
					वापस status;
				पूर्ण
			पूर्ण अन्यथा अणु
				vxge_debug_init(VXGE_ERR,
					"vxge_hw_vpath_reset failed for "
					"vpath:%d", i);
				वापस status;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/* बंद vpaths */
अटल व्योम vxge_बंद_vpaths(काष्ठा vxgedev *vdev, पूर्णांक index)
अणु
	काष्ठा vxge_vpath *vpath;
	पूर्णांक i;

	क्रम (i = index; i < vdev->no_of_vpath; i++) अणु
		vpath = &vdev->vpaths[i];

		अगर (vpath->handle && vpath->is_खोलो) अणु
			vxge_hw_vpath_बंद(vpath->handle);
			vdev->stats.vpaths_खोलो--;
		पूर्ण
		vpath->is_खोलो = 0;
		vpath->handle = शून्य;
	पूर्ण
पूर्ण

/* खोलो vpaths */
अटल पूर्णांक vxge_खोलो_vpaths(काष्ठा vxgedev *vdev)
अणु
	काष्ठा vxge_hw_vpath_attr attr;
	क्रमागत vxge_hw_status status;
	काष्ठा vxge_vpath *vpath;
	u32 vp_id = 0;
	पूर्णांक i;

	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		vpath = &vdev->vpaths[i];
		vxge_निश्चित(vpath->is_configured);

		अगर (!vdev->titan1) अणु
			काष्ठा vxge_hw_vp_config *vcfg;
			vcfg = &vdev->devh->config.vp_config[vpath->device_id];

			vcfg->rti.urange_a = RTI_T1A_RX_URANGE_A;
			vcfg->rti.urange_b = RTI_T1A_RX_URANGE_B;
			vcfg->rti.urange_c = RTI_T1A_RX_URANGE_C;
			vcfg->tti.uec_a = TTI_T1A_TX_UFC_A;
			vcfg->tti.uec_b = TTI_T1A_TX_UFC_B;
			vcfg->tti.uec_c = TTI_T1A_TX_UFC_C(vdev->mtu);
			vcfg->tti.uec_d = TTI_T1A_TX_UFC_D(vdev->mtu);
			vcfg->tti.lसमयr_val = VXGE_T1A_TTI_LTIMER_VAL;
			vcfg->tti.rसमयr_val = VXGE_T1A_TTI_RTIMER_VAL;
		पूर्ण

		attr.vp_id = vpath->device_id;
		attr.fअगरo_attr.callback = vxge_xmit_compl;
		attr.fअगरo_attr.txdl_term = vxge_tx_term;
		attr.fअगरo_attr.per_txdl_space = माप(काष्ठा vxge_tx_priv);
		attr.fअगरo_attr.userdata = &vpath->fअगरo;

		attr.ring_attr.callback = vxge_rx_1b_compl;
		attr.ring_attr.rxd_init = vxge_rx_initial_replenish;
		attr.ring_attr.rxd_term = vxge_rx_term;
		attr.ring_attr.per_rxd_space = माप(काष्ठा vxge_rx_priv);
		attr.ring_attr.userdata = &vpath->ring;

		vpath->ring.ndev = vdev->ndev;
		vpath->ring.pdev = vdev->pdev;

		status = vxge_hw_vpath_खोलो(vdev->devh, &attr, &vpath->handle);
		अगर (status == VXGE_HW_OK) अणु
			vpath->fअगरo.handle =
			    (काष्ठा __vxge_hw_fअगरo *)attr.fअगरo_attr.userdata;
			vpath->ring.handle =
			    (काष्ठा __vxge_hw_ring *)attr.ring_attr.userdata;
			vpath->fअगरo.tx_steering_type =
				vdev->config.tx_steering_type;
			vpath->fअगरo.ndev = vdev->ndev;
			vpath->fअगरo.pdev = vdev->pdev;

			u64_stats_init(&vpath->fअगरo.stats.syncp);
			u64_stats_init(&vpath->ring.stats.syncp);

			अगर (vdev->config.tx_steering_type)
				vpath->fअगरo.txq =
					netdev_get_tx_queue(vdev->ndev, i);
			अन्यथा
				vpath->fअगरo.txq =
					netdev_get_tx_queue(vdev->ndev, 0);
			vpath->fअगरo.indicate_max_pkts =
				vdev->config.fअगरo_indicate_max_pkts;
			vpath->fअगरo.tx_vector_no = 0;
			vpath->ring.rx_vector_no = 0;
			vpath->ring.rx_hwts = vdev->rx_hwts;
			vpath->is_खोलो = 1;
			vdev->vp_handles[i] = vpath->handle;
			vpath->ring.vlan_tag_strip = vdev->vlan_tag_strip;
			vdev->stats.vpaths_खोलो++;
		पूर्ण अन्यथा अणु
			vdev->stats.vpath_खोलो_fail++;
			vxge_debug_init(VXGE_ERR, "%s: vpath: %d failed to "
					"open with status: %d",
					vdev->ndev->name, vpath->device_id,
					status);
			vxge_बंद_vpaths(vdev, 0);
			वापस -EPERM;
		पूर्ण

		vp_id = vpath->handle->vpath->vp_id;
		vdev->vpaths_deployed |= vxge_mBIT(vp_id);
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

/**
 *  adaptive_coalesce_tx_पूर्णांकerrupts - Changes the पूर्णांकerrupt coalescing
 *  अगर the पूर्णांकerrupts are not within a range
 *  @fअगरo: poपूर्णांकer to transmit fअगरo काष्ठाure
 *  Description: The function changes boundary समयr and restriction समयr
 *  value depends on the traffic
 *  Return Value: None
 */
अटल व्योम adaptive_coalesce_tx_पूर्णांकerrupts(काष्ठा vxge_fअगरo *fअगरo)
अणु
	fअगरo->पूर्णांकerrupt_count++;
	अगर (समय_beक्रमe(fअगरo->jअगरfies + HZ / 100, jअगरfies)) अणु
		काष्ठा __vxge_hw_fअगरo *hw_fअगरo = fअगरo->handle;

		fअगरo->jअगरfies = jअगरfies;
		अगर (fअगरo->पूर्णांकerrupt_count > VXGE_T1A_MAX_TX_INTERRUPT_COUNT &&
		    hw_fअगरo->rसमयr != VXGE_TTI_RTIMER_ADAPT_VAL) अणु
			hw_fअगरo->rसमयr = VXGE_TTI_RTIMER_ADAPT_VAL;
			vxge_hw_vpath_dynamic_tti_rसमयr_set(hw_fअगरo);
		पूर्ण अन्यथा अगर (hw_fअगरo->rसमयr != 0) अणु
			hw_fअगरo->rसमयr = 0;
			vxge_hw_vpath_dynamic_tti_rसमयr_set(hw_fअगरo);
		पूर्ण
		fअगरo->पूर्णांकerrupt_count = 0;
	पूर्ण
पूर्ण

/**
 *  adaptive_coalesce_rx_पूर्णांकerrupts - Changes the पूर्णांकerrupt coalescing
 *  अगर the पूर्णांकerrupts are not within a range
 *  @ring: poपूर्णांकer to receive ring काष्ठाure
 *  Description: The function increases of decreases the packet counts within
 *  the ranges of traffic utilization, अगर the पूर्णांकerrupts due to this ring are
 *  not within a fixed range.
 *  Return Value: Nothing
 */
अटल व्योम adaptive_coalesce_rx_पूर्णांकerrupts(काष्ठा vxge_ring *ring)
अणु
	ring->पूर्णांकerrupt_count++;
	अगर (समय_beक्रमe(ring->jअगरfies + HZ / 100, jअगरfies)) अणु
		काष्ठा __vxge_hw_ring *hw_ring = ring->handle;

		ring->jअगरfies = jअगरfies;
		अगर (ring->पूर्णांकerrupt_count > VXGE_T1A_MAX_INTERRUPT_COUNT &&
		    hw_ring->rसमयr != VXGE_RTI_RTIMER_ADAPT_VAL) अणु
			hw_ring->rसमयr = VXGE_RTI_RTIMER_ADAPT_VAL;
			vxge_hw_vpath_dynamic_rti_rसमयr_set(hw_ring);
		पूर्ण अन्यथा अगर (hw_ring->rसमयr != 0) अणु
			hw_ring->rसमयr = 0;
			vxge_hw_vpath_dynamic_rti_rसमयr_set(hw_ring);
		पूर्ण
		ring->पूर्णांकerrupt_count = 0;
	पूर्ण
पूर्ण

/*
 *  vxge_isr_napi
 *  @irq: the irq of the device.
 *  @dev_id: a व्योम poपूर्णांकer to the hldev काष्ठाure of the Titan device
 *  @ptregs: poपूर्णांकer to the रेजिस्टरs pushed on the stack.
 *
 *  This function is the ISR handler of the device when napi is enabled. It
 *  identअगरies the reason क्रम the पूर्णांकerrupt and calls the relevant service
 *  routines.
 */
अटल irqवापस_t vxge_isr_napi(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा __vxge_hw_device *hldev;
	u64 reason;
	क्रमागत vxge_hw_status status;
	काष्ठा vxgedev *vdev = (काष्ठा vxgedev *)dev_id;

	vxge_debug_पूर्णांकr(VXGE_TRACE, "%s:%d", __func__, __LINE__);

	hldev = pci_get_drvdata(vdev->pdev);

	अगर (pci_channel_offline(vdev->pdev))
		वापस IRQ_NONE;

	अगर (unlikely(!is_vxge_card_up(vdev)))
		वापस IRQ_HANDLED;

	status = vxge_hw_device_begin_irq(hldev, vdev->exec_mode, &reason);
	अगर (status == VXGE_HW_OK) अणु
		vxge_hw_device_mask_all(hldev);

		अगर (reason &
			VXGE_HW_TITAN_GENERAL_INT_STATUS_VPATH_TRAFFIC_INT(
			vdev->vpaths_deployed >>
			(64 - VXGE_HW_MAX_VIRTUAL_PATHS))) अणु

			vxge_hw_device_clear_tx_rx(hldev);
			napi_schedule(&vdev->napi);
			vxge_debug_पूर्णांकr(VXGE_TRACE,
				"%s:%d  Exiting...", __func__, __LINE__);
			वापस IRQ_HANDLED;
		पूर्ण अन्यथा
			vxge_hw_device_unmask_all(hldev);
	पूर्ण अन्यथा अगर (unlikely((status == VXGE_HW_ERR_VPATH) ||
		(status == VXGE_HW_ERR_CRITICAL) ||
		(status == VXGE_HW_ERR_FIFO))) अणु
		vxge_hw_device_mask_all(hldev);
		vxge_hw_device_flush_io(hldev);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (unlikely(status == VXGE_HW_ERR_SLOT_FREEZE))
		वापस IRQ_HANDLED;

	vxge_debug_पूर्णांकr(VXGE_TRACE, "%s:%d  Exiting...", __func__, __LINE__);
	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t vxge_tx_msix_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vxge_fअगरo *fअगरo = (काष्ठा vxge_fअगरo *)dev_id;

	adaptive_coalesce_tx_पूर्णांकerrupts(fअगरo);

	vxge_hw_channel_msix_mask((काष्ठा __vxge_hw_channel *)fअगरo->handle,
				  fअगरo->tx_vector_no);

	vxge_hw_channel_msix_clear((काष्ठा __vxge_hw_channel *)fअगरo->handle,
				   fअगरo->tx_vector_no);

	VXGE_COMPLETE_VPATH_TX(fअगरo);

	vxge_hw_channel_msix_unmask((काष्ठा __vxge_hw_channel *)fअगरo->handle,
				    fअगरo->tx_vector_no);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t vxge_rx_msix_napi_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vxge_ring *ring = (काष्ठा vxge_ring *)dev_id;

	adaptive_coalesce_rx_पूर्णांकerrupts(ring);

	vxge_hw_channel_msix_mask((काष्ठा __vxge_hw_channel *)ring->handle,
				  ring->rx_vector_no);

	vxge_hw_channel_msix_clear((काष्ठा __vxge_hw_channel *)ring->handle,
				   ring->rx_vector_no);

	napi_schedule(&ring->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
vxge_alarm_msix_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक i;
	क्रमागत vxge_hw_status status;
	काष्ठा vxge_vpath *vpath = (काष्ठा vxge_vpath *)dev_id;
	काष्ठा vxgedev *vdev = vpath->vdev;
	पूर्णांक msix_id = (vpath->handle->vpath->vp_id *
		VXGE_HW_VPATH_MSIX_ACTIVE) + VXGE_ALARM_MSIX_ID;

	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		/* Reduce the chance of losing alarm पूर्णांकerrupts by masking
		 * the vector. A pending bit will be set अगर an alarm is
		 * generated and on unmask the पूर्णांकerrupt will be fired.
		 */
		vxge_hw_vpath_msix_mask(vdev->vpaths[i].handle, msix_id);
		vxge_hw_vpath_msix_clear(vdev->vpaths[i].handle, msix_id);

		status = vxge_hw_vpath_alarm_process(vdev->vpaths[i].handle,
			vdev->exec_mode);
		अगर (status == VXGE_HW_OK) अणु
			vxge_hw_vpath_msix_unmask(vdev->vpaths[i].handle,
						  msix_id);
			जारी;
		पूर्ण
		vxge_debug_पूर्णांकr(VXGE_ERR,
			"%s: vxge_hw_vpath_alarm_process failed %x ",
			VXGE_DRIVER_NAME, status);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vxge_alloc_msix(काष्ठा vxgedev *vdev)
अणु
	पूर्णांक j, i, ret = 0;
	पूर्णांक msix_पूर्णांकr_vect = 0, temp;
	vdev->पूर्णांकr_cnt = 0;

start:
	/* Tx/Rx MSIX Vectors count */
	vdev->पूर्णांकr_cnt = vdev->no_of_vpath * 2;

	/* Alarm MSIX Vectors count */
	vdev->पूर्णांकr_cnt++;

	vdev->entries = kसुस्मृति(vdev->पूर्णांकr_cnt, माप(काष्ठा msix_entry),
				GFP_KERNEL);
	अगर (!vdev->entries) अणु
		vxge_debug_init(VXGE_ERR,
			"%s: memory allocation failed",
			VXGE_DRIVER_NAME);
		ret = -ENOMEM;
		जाओ alloc_entries_failed;
	पूर्ण

	vdev->vxge_entries = kसुस्मृति(vdev->पूर्णांकr_cnt,
				     माप(काष्ठा vxge_msix_entry),
				     GFP_KERNEL);
	अगर (!vdev->vxge_entries) अणु
		vxge_debug_init(VXGE_ERR, "%s: memory allocation failed",
			VXGE_DRIVER_NAME);
		ret = -ENOMEM;
		जाओ alloc_vxge_entries_failed;
	पूर्ण

	क्रम (i = 0, j = 0; i < vdev->no_of_vpath; i++) अणु

		msix_पूर्णांकr_vect = i * VXGE_HW_VPATH_MSIX_ACTIVE;

		/* Initialize the fअगरo vector */
		vdev->entries[j].entry = msix_पूर्णांकr_vect;
		vdev->vxge_entries[j].entry = msix_पूर्णांकr_vect;
		vdev->vxge_entries[j].in_use = 0;
		j++;

		/* Initialize the ring vector */
		vdev->entries[j].entry = msix_पूर्णांकr_vect + 1;
		vdev->vxge_entries[j].entry = msix_पूर्णांकr_vect + 1;
		vdev->vxge_entries[j].in_use = 0;
		j++;
	पूर्ण

	/* Initialize the alarm vector */
	vdev->entries[j].entry = VXGE_ALARM_MSIX_ID;
	vdev->vxge_entries[j].entry = VXGE_ALARM_MSIX_ID;
	vdev->vxge_entries[j].in_use = 0;

	ret = pci_enable_msix_range(vdev->pdev,
				    vdev->entries, 3, vdev->पूर्णांकr_cnt);
	अगर (ret < 0) अणु
		ret = -ENODEV;
		जाओ enable_msix_failed;
	पूर्ण अन्यथा अगर (ret < vdev->पूर्णांकr_cnt) अणु
		pci_disable_msix(vdev->pdev);

		vxge_debug_init(VXGE_ERR,
			"%s: MSI-X enable failed for %d vectors, ret: %d",
			VXGE_DRIVER_NAME, vdev->पूर्णांकr_cnt, ret);
		अगर (max_config_vpath != VXGE_USE_DEFAULT) अणु
			ret = -ENODEV;
			जाओ enable_msix_failed;
		पूर्ण

		kमुक्त(vdev->entries);
		kमुक्त(vdev->vxge_entries);
		vdev->entries = शून्य;
		vdev->vxge_entries = शून्य;
		/* Try with less no of vector by reducing no of vpaths count */
		temp = (ret - 1)/2;
		vxge_बंद_vpaths(vdev, temp);
		vdev->no_of_vpath = temp;
		जाओ start;
	पूर्ण
	वापस 0;

enable_msix_failed:
	kमुक्त(vdev->vxge_entries);
alloc_vxge_entries_failed:
	kमुक्त(vdev->entries);
alloc_entries_failed:
	वापस ret;
पूर्ण

अटल पूर्णांक vxge_enable_msix(काष्ठा vxgedev *vdev)
अणु

	पूर्णांक i, ret = 0;
	/* 0 - Tx, 1 - Rx  */
	पूर्णांक tim_msix_id[4] = अणु0, 1, 0, 0पूर्ण;

	vdev->पूर्णांकr_cnt = 0;

	/* allocate msix vectors */
	ret = vxge_alloc_msix(vdev);
	अगर (!ret) अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			काष्ठा vxge_vpath *vpath = &vdev->vpaths[i];

			/* If fअगरo or ring are not enabled, the MSIX vector क्रम
			 * it should be set to 0.
			 */
			vpath->ring.rx_vector_no = (vpath->device_id *
						VXGE_HW_VPATH_MSIX_ACTIVE) + 1;

			vpath->fअगरo.tx_vector_no = (vpath->device_id *
						VXGE_HW_VPATH_MSIX_ACTIVE);

			vxge_hw_vpath_msix_set(vpath->handle, tim_msix_id,
					       VXGE_ALARM_MSIX_ID);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vxge_rem_msix_isr(काष्ठा vxgedev *vdev)
अणु
	पूर्णांक पूर्णांकr_cnt;

	क्रम (पूर्णांकr_cnt = 0; पूर्णांकr_cnt < (vdev->no_of_vpath * 2 + 1);
		पूर्णांकr_cnt++) अणु
		अगर (vdev->vxge_entries[पूर्णांकr_cnt].in_use) अणु
			synchronize_irq(vdev->entries[पूर्णांकr_cnt].vector);
			मुक्त_irq(vdev->entries[पूर्णांकr_cnt].vector,
				vdev->vxge_entries[पूर्णांकr_cnt].arg);
			vdev->vxge_entries[पूर्णांकr_cnt].in_use = 0;
		पूर्ण
	पूर्ण

	kमुक्त(vdev->entries);
	kमुक्त(vdev->vxge_entries);
	vdev->entries = शून्य;
	vdev->vxge_entries = शून्य;

	अगर (vdev->config.पूर्णांकr_type == MSI_X)
		pci_disable_msix(vdev->pdev);
पूर्ण

अटल व्योम vxge_rem_isr(काष्ठा vxgedev *vdev)
अणु
	अगर (IS_ENABLED(CONFIG_PCI_MSI) &&
	    vdev->config.पूर्णांकr_type == MSI_X) अणु
		vxge_rem_msix_isr(vdev);
	पूर्ण अन्यथा अगर (vdev->config.पूर्णांकr_type == INTA) अणु
			synchronize_irq(vdev->pdev->irq);
			मुक्त_irq(vdev->pdev->irq, vdev);
	पूर्ण
पूर्ण

अटल पूर्णांक vxge_add_isr(काष्ठा vxgedev *vdev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक vp_idx = 0, पूर्णांकr_idx = 0, पूर्णांकr_cnt = 0, msix_idx = 0, irq_req = 0;
	पूर्णांक pci_fun = PCI_FUNC(vdev->pdev->devfn);

	अगर (IS_ENABLED(CONFIG_PCI_MSI) && vdev->config.पूर्णांकr_type == MSI_X)
		ret = vxge_enable_msix(vdev);

	अगर (ret) अणु
		vxge_debug_init(VXGE_ERR,
			"%s: Enabling MSI-X Failed", VXGE_DRIVER_NAME);
		vxge_debug_init(VXGE_ERR,
			"%s: Defaulting to INTA", VXGE_DRIVER_NAME);
		vdev->config.पूर्णांकr_type = INTA;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PCI_MSI) && vdev->config.पूर्णांकr_type == MSI_X) अणु
		क्रम (पूर्णांकr_idx = 0;
		     पूर्णांकr_idx < (vdev->no_of_vpath *
			VXGE_HW_VPATH_MSIX_ACTIVE); पूर्णांकr_idx++) अणु

			msix_idx = पूर्णांकr_idx % VXGE_HW_VPATH_MSIX_ACTIVE;
			irq_req = 0;

			चयन (msix_idx) अणु
			हाल 0:
				snम_लिखो(vdev->desc[पूर्णांकr_cnt], VXGE_INTR_STRLEN,
					"%s:vxge:MSI-X %d - Tx - fn:%d vpath:%d",
					vdev->ndev->name,
					vdev->entries[पूर्णांकr_cnt].entry,
					pci_fun, vp_idx);
				ret = request_irq(
					vdev->entries[पूर्णांकr_cnt].vector,
					vxge_tx_msix_handle, 0,
					vdev->desc[पूर्णांकr_cnt],
					&vdev->vpaths[vp_idx].fअगरo);
				vdev->vxge_entries[पूर्णांकr_cnt].arg =
						&vdev->vpaths[vp_idx].fअगरo;
				irq_req = 1;
				अवरोध;
			हाल 1:
				snम_लिखो(vdev->desc[पूर्णांकr_cnt], VXGE_INTR_STRLEN,
					"%s:vxge:MSI-X %d - Rx - fn:%d vpath:%d",
					vdev->ndev->name,
					vdev->entries[पूर्णांकr_cnt].entry,
					pci_fun, vp_idx);
				ret = request_irq(
					vdev->entries[पूर्णांकr_cnt].vector,
					vxge_rx_msix_napi_handle, 0,
					vdev->desc[पूर्णांकr_cnt],
					&vdev->vpaths[vp_idx].ring);
				vdev->vxge_entries[पूर्णांकr_cnt].arg =
						&vdev->vpaths[vp_idx].ring;
				irq_req = 1;
				अवरोध;
			पूर्ण

			अगर (ret) अणु
				vxge_debug_init(VXGE_ERR,
					"%s: MSIX - %d  Registration failed",
					vdev->ndev->name, पूर्णांकr_cnt);
				vxge_rem_msix_isr(vdev);
				vdev->config.पूर्णांकr_type = INTA;
				vxge_debug_init(VXGE_ERR,
					"%s: Defaulting to INTA",
					vdev->ndev->name);
				जाओ INTA_MODE;
			पूर्ण

			अगर (irq_req) अणु
				/* We requested क्रम this msix पूर्णांकerrupt */
				vdev->vxge_entries[पूर्णांकr_cnt].in_use = 1;
				msix_idx +=  vdev->vpaths[vp_idx].device_id *
					VXGE_HW_VPATH_MSIX_ACTIVE;
				vxge_hw_vpath_msix_unmask(
					vdev->vpaths[vp_idx].handle,
					msix_idx);
				पूर्णांकr_cnt++;
			पूर्ण

			/* Poपूर्णांक to next vpath handler */
			अगर (((पूर्णांकr_idx + 1) % VXGE_HW_VPATH_MSIX_ACTIVE == 0) &&
			    (vp_idx < (vdev->no_of_vpath - 1)))
				vp_idx++;
		पूर्ण

		पूर्णांकr_cnt = vdev->no_of_vpath * 2;
		snम_लिखो(vdev->desc[पूर्णांकr_cnt], VXGE_INTR_STRLEN,
			"%s:vxge:MSI-X %d - Alarm - fn:%d",
			vdev->ndev->name,
			vdev->entries[पूर्णांकr_cnt].entry,
			pci_fun);
		/* For Alarm पूर्णांकerrupts */
		ret = request_irq(vdev->entries[पूर्णांकr_cnt].vector,
					vxge_alarm_msix_handle, 0,
					vdev->desc[पूर्णांकr_cnt],
					&vdev->vpaths[0]);
		अगर (ret) अणु
			vxge_debug_init(VXGE_ERR,
				"%s: MSIX - %d Registration failed",
				vdev->ndev->name, पूर्णांकr_cnt);
			vxge_rem_msix_isr(vdev);
			vdev->config.पूर्णांकr_type = INTA;
			vxge_debug_init(VXGE_ERR,
				"%s: Defaulting to INTA",
				vdev->ndev->name);
			जाओ INTA_MODE;
		पूर्ण

		msix_idx = (vdev->vpaths[0].handle->vpath->vp_id *
			VXGE_HW_VPATH_MSIX_ACTIVE) + VXGE_ALARM_MSIX_ID;
		vxge_hw_vpath_msix_unmask(vdev->vpaths[vp_idx].handle,
					msix_idx);
		vdev->vxge_entries[पूर्णांकr_cnt].in_use = 1;
		vdev->vxge_entries[पूर्णांकr_cnt].arg = &vdev->vpaths[0];
	पूर्ण

INTA_MODE:
	अगर (vdev->config.पूर्णांकr_type == INTA) अणु
		snम_लिखो(vdev->desc[0], VXGE_INTR_STRLEN,
			"%s:vxge:INTA", vdev->ndev->name);
		vxge_hw_device_set_पूर्णांकr_type(vdev->devh,
			VXGE_HW_INTR_MODE_IRQLINE);

		vxge_hw_vpath_tti_ci_set(vdev->vpaths[0].fअगरo.handle);

		ret = request_irq((पूर्णांक) vdev->pdev->irq,
			vxge_isr_napi,
			IRQF_SHARED, vdev->desc[0], vdev);
		अगर (ret) अणु
			vxge_debug_init(VXGE_ERR,
				"%s %s-%d: ISR registration failed",
				VXGE_DRIVER_NAME, "IRQ", vdev->pdev->irq);
			वापस -ENODEV;
		पूर्ण
		vxge_debug_init(VXGE_TRACE,
			"new %s-%d line allocated",
			"IRQ", vdev->pdev->irq);
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

अटल व्योम vxge_poll_vp_reset(काष्ठा समयr_list *t)
अणु
	काष्ठा vxgedev *vdev = from_समयr(vdev, t, vp_reset_समयr);
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		अगर (test_bit(i, &vdev->vp_reset)) अणु
			vxge_reset_vpath(vdev, i);
			j++;
		पूर्ण
	पूर्ण
	अगर (j && (vdev->config.पूर्णांकr_type != MSI_X)) अणु
		vxge_hw_device_unmask_all(vdev->devh);
		vxge_hw_device_flush_io(vdev->devh);
	पूर्ण

	mod_समयr(&vdev->vp_reset_समयr, jअगरfies + HZ / 2);
पूर्ण

अटल व्योम vxge_poll_vp_lockup(काष्ठा समयr_list *t)
अणु
	काष्ठा vxgedev *vdev = from_समयr(vdev, t, vp_lockup_समयr);
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_vpath *vpath;
	काष्ठा vxge_ring *ring;
	पूर्णांक i;
	अचिन्हित दीर्घ rx_frms;

	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		ring = &vdev->vpaths[i].ring;

		/* Truncated to machine word size number of frames */
		rx_frms = READ_ONCE(ring->stats.rx_frms);

		/* Did this vpath received any packets */
		अगर (ring->stats.prev_rx_frms == rx_frms) अणु
			status = vxge_hw_vpath_check_leak(ring->handle);

			/* Did it received any packets last समय */
			अगर ((VXGE_HW_FAIL == status) &&
				(VXGE_HW_FAIL == ring->last_status)) अणु

				/* schedule vpath reset */
				अगर (!test_and_set_bit(i, &vdev->vp_reset)) अणु
					vpath = &vdev->vpaths[i];

					/* disable पूर्णांकerrupts क्रम this vpath */
					vxge_vpath_पूर्णांकr_disable(vdev, i);

					/* stop the queue क्रम this vpath */
					netअगर_tx_stop_queue(vpath->fअगरo.txq);
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण
		ring->stats.prev_rx_frms = rx_frms;
		ring->last_status = status;
	पूर्ण

	/* Check every 1 milli second */
	mod_समयr(&vdev->vp_lockup_समयr, jअगरfies + HZ / 1000);
पूर्ण

अटल netdev_features_t vxge_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	netdev_features_t changed = dev->features ^ features;

	/* Enabling RTH requires some of the logic in vxge_device_रेजिस्टर and a
	 * vpath reset.  Due to these restrictions, only allow modअगरication
	 * जबतक the पूर्णांकerface is करोwn.
	 */
	अगर ((changed & NETIF_F_RXHASH) && netअगर_running(dev))
		features ^= NETIF_F_RXHASH;

	वापस features;
पूर्ण

अटल पूर्णांक vxge_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	netdev_features_t changed = dev->features ^ features;

	अगर (!(changed & NETIF_F_RXHASH))
		वापस 0;

	/* !netअगर_running() ensured by vxge_fix_features() */

	vdev->devh->config.rth_en = !!(features & NETIF_F_RXHASH);
	अगर (vxge_reset_all_vpaths(vdev) != VXGE_HW_OK) अणु
		dev->features = features ^ NETIF_F_RXHASH;
		vdev->devh->config.rth_en = !!(dev->features & NETIF_F_RXHASH);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vxge_खोलो
 * @dev: poपूर्णांकer to the device काष्ठाure.
 *
 * This function is the खोलो entry poपूर्णांक of the driver. It मुख्यly calls a
 * function to allocate Rx buffers and inserts them पूर्णांकo the buffer
 * descriptors and then enables the Rx part of the NIC.
 * Return value: '0' on success and an appropriate (-)ve पूर्णांकeger as
 * defined in त्रुटिसं.स file on failure.
 */
अटल पूर्णांक vxge_खोलो(काष्ठा net_device *dev)
अणु
	क्रमागत vxge_hw_status status;
	काष्ठा vxgedev *vdev;
	काष्ठा __vxge_hw_device *hldev;
	काष्ठा vxge_vpath *vpath;
	पूर्णांक ret = 0;
	पूर्णांक i;
	u64 val64;

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d", dev->name, __func__, __LINE__);

	vdev = netdev_priv(dev);
	hldev = pci_get_drvdata(vdev->pdev);

	/* make sure you have link off by शेष every समय Nic is
	 * initialized */
	netअगर_carrier_off(dev);

	/* Open VPATHs */
	status = vxge_खोलो_vpaths(vdev);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"%s: fatal: Vpath open failed", vdev->ndev->name);
		ret = -EPERM;
		जाओ out0;
	पूर्ण

	vdev->mtu = dev->mtu;

	status = vxge_add_isr(vdev);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"%s: fatal: ISR add failed", dev->name);
		ret = -EPERM;
		जाओ out1;
	पूर्ण

	अगर (vdev->config.पूर्णांकr_type != MSI_X) अणु
		netअगर_napi_add(dev, &vdev->napi, vxge_poll_पूर्णांकa,
			vdev->config.napi_weight);
		napi_enable(&vdev->napi);
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vpath = &vdev->vpaths[i];
			vpath->ring.napi_p = &vdev->napi;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vpath = &vdev->vpaths[i];
			netअगर_napi_add(dev, &vpath->ring.napi,
			    vxge_poll_msix, vdev->config.napi_weight);
			napi_enable(&vpath->ring.napi);
			vpath->ring.napi_p = &vpath->ring.napi;
		पूर्ण
	पूर्ण

	/* configure RTH */
	अगर (vdev->config.rth_steering) अणु
		status = vxge_rth_configure(vdev);
		अगर (status != VXGE_HW_OK) अणु
			vxge_debug_init(VXGE_ERR,
				"%s: fatal: RTH configuration failed",
				dev->name);
			ret = -EPERM;
			जाओ out2;
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_INFO "%s: Receive Hashing Offload %s\n", dev->name,
	       hldev->config.rth_en ? "enabled" : "disabled");

	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		vpath = &vdev->vpaths[i];

		/* set initial mtu beक्रमe enabling the device */
		status = vxge_hw_vpath_mtu_set(vpath->handle, vdev->mtu);
		अगर (status != VXGE_HW_OK) अणु
			vxge_debug_init(VXGE_ERR,
				"%s: fatal: can not set new MTU", dev->name);
			ret = -EPERM;
			जाओ out2;
		पूर्ण
	पूर्ण

	VXGE_DEVICE_DEBUG_LEVEL_SET(VXGE_TRACE, VXGE_COMPONENT_LL, vdev);
	vxge_debug_init(vdev->level_trace,
		"%s: MTU is %d", vdev->ndev->name, vdev->mtu);
	VXGE_DEVICE_DEBUG_LEVEL_SET(VXGE_ERR, VXGE_COMPONENT_LL, vdev);

	/* Restore the DA, VID table and also multicast and promiscuous mode
	 * states
	 */
	अगर (vdev->all_multi_flg) अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vpath = &vdev->vpaths[i];
			vxge_restore_vpath_mac_addr(vpath);
			vxge_restore_vpath_vid_table(vpath);

			status = vxge_hw_vpath_mcast_enable(vpath->handle);
			अगर (status != VXGE_HW_OK)
				vxge_debug_init(VXGE_ERR,
					"%s:%d Enabling multicast failed",
					__func__, __LINE__);
		पूर्ण
	पूर्ण

	/* Enable vpath to snअगरf all unicast/multicast traffic that not
	 * addressed to them. We allow promiscuous mode क्रम PF only
	 */

	val64 = 0;
	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++)
		val64 |= VXGE_HW_RXMAC_AUTHORIZE_ALL_ADDR_VP(i);

	vxge_hw_mgmt_reg_ग_लिखो(vdev->devh,
		vxge_hw_mgmt_reg_type_mrpcim,
		0,
		(uदीर्घ)दुरत्व(काष्ठा vxge_hw_mrpcim_reg,
			rxmac_authorize_all_addr),
		val64);

	vxge_hw_mgmt_reg_ग_लिखो(vdev->devh,
		vxge_hw_mgmt_reg_type_mrpcim,
		0,
		(uदीर्घ)दुरत्व(काष्ठा vxge_hw_mrpcim_reg,
			rxmac_authorize_all_vid),
		val64);

	vxge_set_multicast(dev);

	/* Enabling Bcast and mcast क्रम all vpath */
	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		vpath = &vdev->vpaths[i];
		status = vxge_hw_vpath_bcast_enable(vpath->handle);
		अगर (status != VXGE_HW_OK)
			vxge_debug_init(VXGE_ERR,
				"%s : Can not enable bcast for vpath "
				"id %d", dev->name, i);
		अगर (vdev->config.addr_learn_en) अणु
			status = vxge_hw_vpath_mcast_enable(vpath->handle);
			अगर (status != VXGE_HW_OK)
				vxge_debug_init(VXGE_ERR,
					"%s : Can not enable mcast for vpath "
					"id %d", dev->name, i);
		पूर्ण
	पूर्ण

	vxge_hw_device_setछोड़ो_data(vdev->devh, 0,
		vdev->config.tx_छोड़ो_enable,
		vdev->config.rx_छोड़ो_enable);

	अगर (vdev->vp_reset_समयr.function == शून्य)
		vxge_os_समयr(&vdev->vp_reset_समयr, vxge_poll_vp_reset,
			      HZ / 2);

	/* There is no need to check क्रम RxD leak and RxD lookup on Titan1A */
	अगर (vdev->titan1 && vdev->vp_lockup_समयr.function == शून्य)
		vxge_os_समयr(&vdev->vp_lockup_समयr, vxge_poll_vp_lockup,
			      HZ / 2);

	set_bit(__VXGE_STATE_CARD_UP, &vdev->state);

	smp_wmb();

	अगर (vxge_hw_device_link_state_get(vdev->devh) == VXGE_HW_LINK_UP) अणु
		netअगर_carrier_on(vdev->ndev);
		netdev_notice(vdev->ndev, "Link Up\n");
		vdev->stats.link_up++;
	पूर्ण

	vxge_hw_device_पूर्णांकr_enable(vdev->devh);

	smp_wmb();

	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		vpath = &vdev->vpaths[i];

		vxge_hw_vpath_enable(vpath->handle);
		smp_wmb();
		vxge_hw_vpath_rx_करोorbell_init(vpath->handle);
	पूर्ण

	netअगर_tx_start_all_queues(vdev->ndev);

	/* configure CI */
	vxge_config_ci_क्रम_tti_rti(vdev);

	जाओ out0;

out2:
	vxge_rem_isr(vdev);

	/* Disable napi */
	अगर (vdev->config.पूर्णांकr_type != MSI_X)
		napi_disable(&vdev->napi);
	अन्यथा अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++)
			napi_disable(&vdev->vpaths[i].ring.napi);
	पूर्ण

out1:
	vxge_बंद_vpaths(vdev, 0);
out0:
	vxge_debug_entryनिकास(VXGE_TRACE,
				"%s: %s:%d  Exiting...",
				dev->name, __func__, __LINE__);
	वापस ret;
पूर्ण

/* Loop through the mac address list and delete all the entries */
अटल व्योम vxge_मुक्त_mac_add_list(काष्ठा vxge_vpath *vpath)
अणु

	काष्ठा list_head *entry, *next;
	अगर (list_empty(&vpath->mac_addr_list))
		वापस;

	list_क्रम_each_safe(entry, next, &vpath->mac_addr_list) अणु
		list_del(entry);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल व्योम vxge_napi_del_all(काष्ठा vxgedev *vdev)
अणु
	पूर्णांक i;
	अगर (vdev->config.पूर्णांकr_type != MSI_X)
		netअगर_napi_del(&vdev->napi);
	अन्यथा अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++)
			netअगर_napi_del(&vdev->vpaths[i].ring.napi);
	पूर्ण
पूर्ण

अटल पूर्णांक करो_vxge_बंद(काष्ठा net_device *dev, पूर्णांक करो_io)
अणु
	क्रमागत vxge_hw_status status;
	काष्ठा vxgedev *vdev;
	काष्ठा __vxge_hw_device *hldev;
	पूर्णांक i;
	u64 val64, vpath_vector;
	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d",
		dev->name, __func__, __LINE__);

	vdev = netdev_priv(dev);
	hldev = pci_get_drvdata(vdev->pdev);

	अगर (unlikely(!is_vxge_card_up(vdev)))
		वापस 0;

	/* If vxge_handle_crit_err task is executing,
	 * रुको till it completes. */
	जबतक (test_and_set_bit(__VXGE_STATE_RESET_CARD, &vdev->state))
		msleep(50);

	अगर (करो_io) अणु
		/* Put the vpath back in normal mode */
		vpath_vector = vxge_mBIT(vdev->vpaths[0].device_id);
		status = vxge_hw_mgmt_reg_पढ़ो(vdev->devh,
				vxge_hw_mgmt_reg_type_mrpcim,
				0,
				(uदीर्घ)दुरत्व(
					काष्ठा vxge_hw_mrpcim_reg,
					rts_mgr_cbasin_cfg),
				&val64);
		अगर (status == VXGE_HW_OK) अणु
			val64 &= ~vpath_vector;
			status = vxge_hw_mgmt_reg_ग_लिखो(vdev->devh,
					vxge_hw_mgmt_reg_type_mrpcim,
					0,
					(uदीर्घ)दुरत्व(
						काष्ठा vxge_hw_mrpcim_reg,
						rts_mgr_cbasin_cfg),
					val64);
		पूर्ण

		/* Remove the function 0 from promiscuous mode */
		vxge_hw_mgmt_reg_ग_लिखो(vdev->devh,
			vxge_hw_mgmt_reg_type_mrpcim,
			0,
			(uदीर्घ)दुरत्व(काष्ठा vxge_hw_mrpcim_reg,
				rxmac_authorize_all_addr),
			0);

		vxge_hw_mgmt_reg_ग_लिखो(vdev->devh,
			vxge_hw_mgmt_reg_type_mrpcim,
			0,
			(uदीर्घ)दुरत्व(काष्ठा vxge_hw_mrpcim_reg,
				rxmac_authorize_all_vid),
			0);

		smp_wmb();
	पूर्ण

	अगर (vdev->titan1)
		del_समयr_sync(&vdev->vp_lockup_समयr);

	del_समयr_sync(&vdev->vp_reset_समयr);

	अगर (करो_io)
		vxge_hw_device_रुको_receive_idle(hldev);

	clear_bit(__VXGE_STATE_CARD_UP, &vdev->state);

	/* Disable napi */
	अगर (vdev->config.पूर्णांकr_type != MSI_X)
		napi_disable(&vdev->napi);
	अन्यथा अणु
		क्रम (i = 0; i < vdev->no_of_vpath; i++)
			napi_disable(&vdev->vpaths[i].ring.napi);
	पूर्ण

	netअगर_carrier_off(vdev->ndev);
	netdev_notice(vdev->ndev, "Link Down\n");
	netअगर_tx_stop_all_queues(vdev->ndev);

	/* Note that at this poपूर्णांक xmit() is stopped by upper layer */
	अगर (करो_io)
		vxge_hw_device_पूर्णांकr_disable(vdev->devh);

	vxge_rem_isr(vdev);

	vxge_napi_del_all(vdev);

	अगर (करो_io)
		vxge_reset_all_vpaths(vdev);

	vxge_बंद_vpaths(vdev, 0);

	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s: %s:%d  Exiting...", dev->name, __func__, __LINE__);

	clear_bit(__VXGE_STATE_RESET_CARD, &vdev->state);

	वापस 0;
पूर्ण

/**
 * vxge_बंद
 * @dev: device poपूर्णांकer.
 *
 * This is the stop entry poपूर्णांक of the driver. It needs to unकरो exactly
 * whatever was करोne by the खोलो entry poपूर्णांक, thus it's usually referred to
 * as the बंद function.Among other things this function मुख्यly stops the
 * Rx side of the NIC and मुक्तs all the Rx buffers in the Rx rings.
 * Return value: '0' on success and an appropriate (-)ve पूर्णांकeger as
 * defined in त्रुटिसं.स file on failure.
 */
अटल पूर्णांक vxge_बंद(काष्ठा net_device *dev)
अणु
	करो_vxge_बंद(dev, 1);
	वापस 0;
पूर्ण

/**
 * vxge_change_mtu
 * @dev: net device poपूर्णांकer.
 * @new_mtu :the new MTU size क्रम the device.
 *
 * A driver entry poपूर्णांक to change MTU size क्रम the device. Beक्रमe changing
 * the MTU the device must be stopped.
 */
अटल पूर्णांक vxge_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);

	vxge_debug_entryनिकास(vdev->level_trace,
		"%s:%d", __func__, __LINE__);

	/* check अगर device is करोwn alपढ़ोy */
	अगर (unlikely(!is_vxge_card_up(vdev))) अणु
		/* just store new value, will use later on खोलो() */
		dev->mtu = new_mtu;
		vxge_debug_init(vdev->level_err,
			"%s", "device is down on MTU change");
		वापस 0;
	पूर्ण

	vxge_debug_init(vdev->level_trace,
		"trying to apply new MTU %d", new_mtu);

	अगर (vxge_बंद(dev))
		वापस -EIO;

	dev->mtu = new_mtu;
	vdev->mtu = new_mtu;

	अगर (vxge_खोलो(dev))
		वापस -EIO;

	vxge_debug_init(vdev->level_trace,
		"%s: MTU changed to %d", vdev->ndev->name, new_mtu);

	vxge_debug_entryनिकास(vdev->level_trace,
		"%s:%d  Exiting...", __func__, __LINE__);

	वापस 0;
पूर्ण

/**
 * vxge_get_stats64
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @net_stats: poपूर्णांकer to काष्ठा rtnl_link_stats64
 *
 */
अटल व्योम
vxge_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *net_stats)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	पूर्णांक k;

	/* net_stats alपढ़ोy zeroed by caller */
	क्रम (k = 0; k < vdev->no_of_vpath; k++) अणु
		काष्ठा vxge_ring_stats *rxstats = &vdev->vpaths[k].ring.stats;
		काष्ठा vxge_fअगरo_stats *txstats = &vdev->vpaths[k].fअगरo.stats;
		अचिन्हित पूर्णांक start;
		u64 packets, bytes, multicast;

		करो अणु
			start = u64_stats_fetch_begin_irq(&rxstats->syncp);

			packets   = rxstats->rx_frms;
			multicast = rxstats->rx_mcast;
			bytes     = rxstats->rx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rxstats->syncp, start));

		net_stats->rx_packets += packets;
		net_stats->rx_bytes += bytes;
		net_stats->multicast += multicast;

		net_stats->rx_errors += rxstats->rx_errors;
		net_stats->rx_dropped += rxstats->rx_dropped;

		करो अणु
			start = u64_stats_fetch_begin_irq(&txstats->syncp);

			packets = txstats->tx_frms;
			bytes   = txstats->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&txstats->syncp, start));

		net_stats->tx_packets += packets;
		net_stats->tx_bytes += bytes;
		net_stats->tx_errors += txstats->tx_errors;
	पूर्ण
पूर्ण

अटल क्रमागत vxge_hw_status vxge_बारtamp_config(काष्ठा __vxge_hw_device *devh)
अणु
	क्रमागत vxge_hw_status status;
	u64 val64;

	/* Timestamp is passed to the driver via the FCS, thereक्रमe we
	 * must disable the FCS stripping by the adapter.  Since this is
	 * required क्रम the driver to load (due to a hardware bug),
	 * there is no need to करो anything special here.
	 */
	val64 = VXGE_HW_XMAC_TIMESTAMP_EN |
		VXGE_HW_XMAC_TIMESTAMP_USE_LINK_ID(0) |
		VXGE_HW_XMAC_TIMESTAMP_INTERVAL(0);

	status = vxge_hw_mgmt_reg_ग_लिखो(devh,
					vxge_hw_mgmt_reg_type_mrpcim,
					0,
					दुरत्व(काष्ठा vxge_hw_mrpcim_reg,
						 xmac_बारtamp),
					val64);
	vxge_hw_device_flush_io(devh);
	devh->config.hwts_en = VXGE_HW_HWTS_ENABLE;
	वापस status;
पूर्ण

अटल पूर्णांक vxge_hwtstamp_set(काष्ठा vxgedev *vdev, व्योम __user *data)
अणु
	काष्ठा hwtstamp_config config;
	पूर्णांक i;

	अगर (copy_from_user(&config, data, माप(config)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (config.flags)
		वापस -EINVAL;

	/* Transmit HW Timestamp not supported */
	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		अवरोध;
	हाल HWTSTAMP_TX_ON:
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		vdev->rx_hwts = 0;
		config.rx_filter = HWTSTAMP_FILTER_NONE;
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
		अगर (vdev->devh->config.hwts_en != VXGE_HW_HWTS_ENABLE)
			वापस -EFAULT;

		vdev->rx_hwts = 1;
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;

	शेष:
		 वापस -दुस्फल;
	पूर्ण

	क्रम (i = 0; i < vdev->no_of_vpath; i++)
		vdev->vpaths[i].ring.rx_hwts = vdev->rx_hwts;

	अगर (copy_to_user(data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक vxge_hwtstamp_get(काष्ठा vxgedev *vdev, व्योम __user *data)
अणु
	काष्ठा hwtstamp_config config;

	config.flags = 0;
	config.tx_type = HWTSTAMP_TX_OFF;
	config.rx_filter = (vdev->rx_hwts ?
			    HWTSTAMP_FILTER_ALL : HWTSTAMP_FILTER_NONE);

	अगर (copy_to_user(data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/**
 * vxge_ioctl
 * @dev: Device poपूर्णांकer.
 * @rq: An IOCTL specअगरic काष्ठाure, that can contain a poपूर्णांकer to
 *       a proprietary काष्ठाure used to pass inक्रमmation to the driver.
 * @cmd: This is used to distinguish between the dअगरferent commands that
 *       can be passed to the IOCTL functions.
 *
 * Entry poपूर्णांक क्रम the Ioctl.
 */
अटल पूर्णांक vxge_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस vxge_hwtstamp_set(vdev, rq->अगरr_data);
	हाल SIOCGHWTSTAMP:
		वापस vxge_hwtstamp_get(vdev, rq->अगरr_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * vxge_tx_watchकरोg
 * @dev: poपूर्णांकer to net device काष्ठाure
 * @txqueue: index of the hanging queue
 *
 * Watchकरोg क्रम transmit side.
 * This function is triggered अगर the Tx Queue is stopped
 * क्रम a pre-defined amount of समय when the Interface is still up.
 */
अटल व्योम vxge_tx_watchकरोg(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा vxgedev *vdev;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s:%d", __func__, __LINE__);

	vdev = netdev_priv(dev);

	vdev->cric_err_event = VXGE_HW_EVENT_RESET_START;

	schedule_work(&vdev->reset_task);
	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s:%d  Exiting...", __func__, __LINE__);
पूर्ण

/**
 * vxge_vlan_rx_add_vid
 * @dev: net device poपूर्णांकer.
 * @proto: vlan protocol
 * @vid: vid
 *
 * Add the vlan id to the devices vlan id table
 */
अटल पूर्णांक
vxge_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा vxge_vpath *vpath;
	पूर्णांक vp_id;

	/* Add these vlan to the vid table */
	क्रम (vp_id = 0; vp_id < vdev->no_of_vpath; vp_id++) अणु
		vpath = &vdev->vpaths[vp_id];
		अगर (!vpath->is_खोलो)
			जारी;
		vxge_hw_vpath_vid_add(vpath->handle, vid);
	पूर्ण
	set_bit(vid, vdev->active_vlans);
	वापस 0;
पूर्ण

/**
 * vxge_vlan_rx_समाप्त_vid
 * @dev: net device poपूर्णांकer.
 * @proto: vlan protocol
 * @vid: vid
 *
 * Remove the vlan id from the device's vlan id table
 */
अटल पूर्णांक
vxge_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा vxge_vpath *vpath;
	पूर्णांक vp_id;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s:%d", __func__, __LINE__);

	/* Delete this vlan from the vid table */
	क्रम (vp_id = 0; vp_id < vdev->no_of_vpath; vp_id++) अणु
		vpath = &vdev->vpaths[vp_id];
		अगर (!vpath->is_खोलो)
			जारी;
		vxge_hw_vpath_vid_delete(vpath->handle, vid);
	पूर्ण
	vxge_debug_entryनिकास(VXGE_TRACE,
		"%s:%d  Exiting...", __func__, __LINE__);
	clear_bit(vid, vdev->active_vlans);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops vxge_netdev_ops = अणु
	.nकरो_खोलो               = vxge_खोलो,
	.nकरो_stop               = vxge_बंद,
	.nकरो_get_stats64        = vxge_get_stats64,
	.nकरो_start_xmit         = vxge_xmit,
	.nकरो_validate_addr      = eth_validate_addr,
	.nकरो_set_rx_mode	= vxge_set_multicast,
	.nकरो_करो_ioctl           = vxge_ioctl,
	.nकरो_set_mac_address    = vxge_set_mac_addr,
	.nकरो_change_mtu         = vxge_change_mtu,
	.nकरो_fix_features	= vxge_fix_features,
	.nकरो_set_features	= vxge_set_features,
	.nकरो_vlan_rx_समाप्त_vid   = vxge_vlan_rx_समाप्त_vid,
	.nकरो_vlan_rx_add_vid	= vxge_vlan_rx_add_vid,
	.nकरो_tx_समयout         = vxge_tx_watchकरोg,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller    = vxge_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक vxge_device_रेजिस्टर(काष्ठा __vxge_hw_device *hldev,
				काष्ठा vxge_config *config, पूर्णांक high_dma,
				पूर्णांक no_of_vpath, काष्ठा vxgedev **vdev_out)
अणु
	काष्ठा net_device *ndev;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxgedev *vdev;
	पूर्णांक ret = 0, no_of_queue = 1;
	u64 stat;

	*vdev_out = शून्य;
	अगर (config->tx_steering_type)
		no_of_queue = no_of_vpath;

	ndev = alloc_etherdev_mq(माप(काष्ठा vxgedev),
			no_of_queue);
	अगर (ndev == शून्य) अणु
		vxge_debug_init(
			vxge_hw_device_trace_level_get(hldev),
		"%s : device allocation failed", __func__);
		ret = -ENODEV;
		जाओ _out0;
	पूर्ण

	vxge_debug_entryनिकास(
		vxge_hw_device_trace_level_get(hldev),
		"%s: %s:%d  Entering...",
		ndev->name, __func__, __LINE__);

	vdev = netdev_priv(ndev);
	स_रखो(vdev, 0, माप(काष्ठा vxgedev));

	vdev->ndev = ndev;
	vdev->devh = hldev;
	vdev->pdev = hldev->pdev;
	स_नकल(&vdev->config, config, माप(काष्ठा vxge_config));
	vdev->rx_hwts = 0;
	vdev->titan1 = (vdev->pdev->revision == VXGE_HW_TITAN1_PCI_REVISION);

	SET_NETDEV_DEV(ndev, &vdev->pdev->dev);

	ndev->hw_features = NETIF_F_RXCSUM | NETIF_F_SG |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_HW_VLAN_CTAG_TX;
	अगर (vdev->config.rth_steering != NO_STEERING)
		ndev->hw_features |= NETIF_F_RXHASH;

	ndev->features |= ndev->hw_features |
		NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_CTAG_FILTER;


	ndev->netdev_ops = &vxge_netdev_ops;

	ndev->watchकरोg_समयo = VXGE_LL_WATCH_DOG_TIMEOUT;
	INIT_WORK(&vdev->reset_task, vxge_reset);

	vxge_initialize_ethtool_ops(ndev);

	/* Allocate memory क्रम vpath */
	vdev->vpaths = kसुस्मृति(no_of_vpath, माप(काष्ठा vxge_vpath),
			       GFP_KERNEL);
	अगर (!vdev->vpaths) अणु
		vxge_debug_init(VXGE_ERR,
			"%s: vpath memory allocation failed",
			vdev->ndev->name);
		ret = -ENOMEM;
		जाओ _out1;
	पूर्ण

	vxge_debug_init(vxge_hw_device_trace_level_get(hldev),
		"%s : checksumming enabled", __func__);

	अगर (high_dma) अणु
		ndev->features |= NETIF_F_HIGHDMA;
		vxge_debug_init(vxge_hw_device_trace_level_get(hldev),
			"%s : using High DMA", __func__);
	पूर्ण

	/* MTU range: 68 - 9600 */
	ndev->min_mtu = VXGE_HW_MIN_MTU;
	ndev->max_mtu = VXGE_HW_MAX_MTU;

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		vxge_debug_init(vxge_hw_device_trace_level_get(hldev),
			"%s: %s : device registration failed!",
			ndev->name, __func__);
		जाओ _out2;
	पूर्ण

	/*  Set the factory defined MAC address initially */
	ndev->addr_len = ETH_ALEN;

	/* Make Link state as off at this poपूर्णांक, when the Link change
	 * पूर्णांकerrupt comes the state will be स्वतःmatically changed to
	 * the right state.
	 */
	netअगर_carrier_off(ndev);

	vxge_debug_init(vxge_hw_device_trace_level_get(hldev),
		"%s: Ethernet device registered",
		ndev->name);

	hldev->ndev = ndev;
	*vdev_out = vdev;

	/* Resetting the Device stats */
	status = vxge_hw_mrpcim_stats_access(
				hldev,
				VXGE_HW_STATS_OP_CLEAR_ALL_STATS,
				0,
				0,
				&stat);

	अगर (status == VXGE_HW_ERR_PRIVILEGED_OPERATION)
		vxge_debug_init(
			vxge_hw_device_trace_level_get(hldev),
			"%s: device stats clear returns"
			"VXGE_HW_ERR_PRIVILEGED_OPERATION", ndev->name);

	vxge_debug_entryनिकास(vxge_hw_device_trace_level_get(hldev),
		"%s: %s:%d  Exiting...",
		ndev->name, __func__, __LINE__);

	वापस ret;
_out2:
	kमुक्त(vdev->vpaths);
_out1:
	मुक्त_netdev(ndev);
_out0:
	वापस ret;
पूर्ण

/*
 * vxge_device_unरेजिस्टर
 *
 * This function will unरेजिस्टर and मुक्त network device
 */
अटल व्योम vxge_device_unरेजिस्टर(काष्ठा __vxge_hw_device *hldev)
अणु
	काष्ठा vxgedev *vdev;
	काष्ठा net_device *dev;
	अक्षर buf[IFNAMSIZ];

	dev = hldev->ndev;
	vdev = netdev_priv(dev);

	vxge_debug_entryनिकास(vdev->level_trace,	"%s: %s:%d", vdev->ndev->name,
			     __func__, __LINE__);

	strlcpy(buf, dev->name, IFNAMSIZ);

	flush_work(&vdev->reset_task);

	/* in 2.6 will call stop() अगर device is up */
	unरेजिस्टर_netdev(dev);

	kमुक्त(vdev->vpaths);

	/* we are safe to मुक्त it now */
	मुक्त_netdev(dev);

	vxge_debug_init(vdev->level_trace, "%s: ethernet device unregistered",
			buf);
	vxge_debug_entryनिकास(vdev->level_trace,	"%s: %s:%d  Exiting...", buf,
			     __func__, __LINE__);
पूर्ण

/*
 * vxge_callback_crit_err
 *
 * This function is called by the alarm handler in पूर्णांकerrupt context.
 * Driver must analyze it based on the event type.
 */
अटल व्योम
vxge_callback_crit_err(काष्ठा __vxge_hw_device *hldev,
			क्रमागत vxge_hw_event type, u64 vp_id)
अणु
	काष्ठा net_device *dev = hldev->ndev;
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा vxge_vpath *vpath = शून्य;
	पूर्णांक vpath_idx;

	vxge_debug_entryनिकास(vdev->level_trace,
		"%s: %s:%d", vdev->ndev->name, __func__, __LINE__);

	/* Note: This event type should be used क्रम device wide
	 * indications only - Serious errors, Slot मुक्तze and critical errors
	 */
	vdev->cric_err_event = type;

	क्रम (vpath_idx = 0; vpath_idx < vdev->no_of_vpath; vpath_idx++) अणु
		vpath = &vdev->vpaths[vpath_idx];
		अगर (vpath->device_id == vp_id)
			अवरोध;
	पूर्ण

	अगर (!test_bit(__VXGE_STATE_RESET_CARD, &vdev->state)) अणु
		अगर (type == VXGE_HW_EVENT_SLOT_FREEZE) अणु
			vxge_debug_init(VXGE_ERR,
				"%s: Slot is frozen", vdev->ndev->name);
		पूर्ण अन्यथा अगर (type == VXGE_HW_EVENT_SERR) अणु
			vxge_debug_init(VXGE_ERR,
				"%s: Encountered Serious Error",
				vdev->ndev->name);
		पूर्ण अन्यथा अगर (type == VXGE_HW_EVENT_CRITICAL_ERR)
			vxge_debug_init(VXGE_ERR,
				"%s: Encountered Critical Error",
				vdev->ndev->name);
	पूर्ण

	अगर ((type == VXGE_HW_EVENT_SERR) ||
		(type == VXGE_HW_EVENT_SLOT_FREEZE)) अणु
		अगर (unlikely(vdev->exec_mode))
			clear_bit(__VXGE_STATE_CARD_UP, &vdev->state);
	पूर्ण अन्यथा अगर (type == VXGE_HW_EVENT_CRITICAL_ERR) अणु
		vxge_hw_device_mask_all(hldev);
		अगर (unlikely(vdev->exec_mode))
			clear_bit(__VXGE_STATE_CARD_UP, &vdev->state);
	पूर्ण अन्यथा अगर ((type == VXGE_HW_EVENT_FIFO_ERR) ||
		  (type == VXGE_HW_EVENT_VPATH_ERR)) अणु

		अगर (unlikely(vdev->exec_mode))
			clear_bit(__VXGE_STATE_CARD_UP, &vdev->state);
		अन्यथा अणु
			/* check अगर this vpath is alपढ़ोy set क्रम reset */
			अगर (!test_and_set_bit(vpath_idx, &vdev->vp_reset)) अणु

				/* disable पूर्णांकerrupts क्रम this vpath */
				vxge_vpath_पूर्णांकr_disable(vdev, vpath_idx);

				/* stop the queue क्रम this vpath */
				netअगर_tx_stop_queue(vpath->fअगरo.txq);
			पूर्ण
		पूर्ण
	पूर्ण

	vxge_debug_entryनिकास(vdev->level_trace,
		"%s: %s:%d  Exiting...",
		vdev->ndev->name, __func__, __LINE__);
पूर्ण

अटल व्योम verअगरy_bandwidth(व्योम)
अणु
	पूर्णांक i, band_width, total = 0, equal_priority = 0;

	/* 1. If user enters 0 क्रम some fअगरo, give equal priority to all */
	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (bw_percentage[i] == 0) अणु
			equal_priority = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!equal_priority) अणु
		/* 2. If sum exceeds 100, give equal priority to all */
		क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
			अगर (bw_percentage[i] == 0xFF)
				अवरोध;

			total += bw_percentage[i];
			अगर (total > VXGE_HW_VPATH_BANDWIDTH_MAX) अणु
				equal_priority = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!equal_priority) अणु
		/* Is all the bandwidth consumed? */
		अगर (total < VXGE_HW_VPATH_BANDWIDTH_MAX) अणु
			अगर (i < VXGE_HW_MAX_VIRTUAL_PATHS) अणु
				/* Split rest of bw equally among next VPs*/
				band_width =
				  (VXGE_HW_VPATH_BANDWIDTH_MAX  - total) /
					(VXGE_HW_MAX_VIRTUAL_PATHS - i);
				अगर (band_width < 2) /* min of 2% */
					equal_priority = 1;
				अन्यथा अणु
					क्रम (; i < VXGE_HW_MAX_VIRTUAL_PATHS;
						i++)
						bw_percentage[i] =
							band_width;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (i < VXGE_HW_MAX_VIRTUAL_PATHS)
			equal_priority = 1;
	पूर्ण

	अगर (equal_priority) अणु
		vxge_debug_init(VXGE_ERR,
			"%s: Assigning equal bandwidth to all the vpaths",
			VXGE_DRIVER_NAME);
		bw_percentage[0] = VXGE_HW_VPATH_BANDWIDTH_MAX /
					VXGE_HW_MAX_VIRTUAL_PATHS;
		क्रम (i = 1; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++)
			bw_percentage[i] = bw_percentage[0];
	पूर्ण
पूर्ण

/*
 * Vpath configuration
 */
अटल पूर्णांक vxge_config_vpaths(काष्ठा vxge_hw_device_config *device_config,
			      u64 vpath_mask, काष्ठा vxge_config *config_param)
अणु
	पूर्णांक i, no_of_vpaths = 0, शेष_no_vpath = 0, temp;
	u32 txdl_size, txdl_per_memblock;

	temp = driver_config->vpath_per_dev;
	अगर ((driver_config->vpath_per_dev == VXGE_USE_DEFAULT) &&
		(max_config_dev == VXGE_MAX_CONFIG_DEV)) अणु
		/* No more CPU. Return vpath number as zero.*/
		अगर (driver_config->g_no_cpus == -1)
			वापस 0;

		अगर (!driver_config->g_no_cpus)
			driver_config->g_no_cpus =
				netअगर_get_num_शेष_rss_queues();

		driver_config->vpath_per_dev = driver_config->g_no_cpus >> 1;
		अगर (!driver_config->vpath_per_dev)
			driver_config->vpath_per_dev = 1;

		क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++)
			अगर (!vxge_bVALn(vpath_mask, i, 1))
				जारी;
			अन्यथा
				शेष_no_vpath++;
		अगर (शेष_no_vpath < driver_config->vpath_per_dev)
			driver_config->vpath_per_dev = शेष_no_vpath;

		driver_config->g_no_cpus = driver_config->g_no_cpus -
				(driver_config->vpath_per_dev * 2);
		अगर (driver_config->g_no_cpus <= 0)
			driver_config->g_no_cpus = -1;
	पूर्ण

	अगर (driver_config->vpath_per_dev == 1) अणु
		vxge_debug_ll_config(VXGE_TRACE,
			"%s: Disable tx and rx steering, "
			"as single vpath is configured", VXGE_DRIVER_NAME);
		config_param->rth_steering = NO_STEERING;
		config_param->tx_steering_type = NO_STEERING;
		device_config->rth_en = 0;
	पूर्ण

	/* configure bandwidth */
	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++)
		device_config->vp_config[i].min_bandwidth = bw_percentage[i];

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		device_config->vp_config[i].vp_id = i;
		device_config->vp_config[i].mtu = VXGE_HW_DEFAULT_MTU;
		अगर (no_of_vpaths < driver_config->vpath_per_dev) अणु
			अगर (!vxge_bVALn(vpath_mask, i, 1)) अणु
				vxge_debug_ll_config(VXGE_TRACE,
					"%s: vpath: %d is not available",
					VXGE_DRIVER_NAME, i);
				जारी;
			पूर्ण अन्यथा अणु
				vxge_debug_ll_config(VXGE_TRACE,
					"%s: vpath: %d available",
					VXGE_DRIVER_NAME, i);
				no_of_vpaths++;
			पूर्ण
		पूर्ण अन्यथा अणु
			vxge_debug_ll_config(VXGE_TRACE,
				"%s: vpath: %d is not configured, "
				"max_config_vpath exceeded",
				VXGE_DRIVER_NAME, i);
			अवरोध;
		पूर्ण

		/* Configure Tx fअगरo's */
		device_config->vp_config[i].fअगरo.enable =
						VXGE_HW_FIFO_ENABLE;
		device_config->vp_config[i].fअगरo.max_frags =
				MAX_SKB_FRAGS + 1;
		device_config->vp_config[i].fअगरo.memblock_size =
			VXGE_HW_MIN_FIFO_MEMBLOCK_SIZE;

		txdl_size = device_config->vp_config[i].fअगरo.max_frags *
				माप(काष्ठा vxge_hw_fअगरo_txd);
		txdl_per_memblock = VXGE_HW_MIN_FIFO_MEMBLOCK_SIZE / txdl_size;

		device_config->vp_config[i].fअगरo.fअगरo_blocks =
			((VXGE_DEF_FIFO_LENGTH - 1) / txdl_per_memblock) + 1;

		device_config->vp_config[i].fअगरo.पूर्णांकr =
				VXGE_HW_FIFO_QUEUE_INTR_DISABLE;

		/* Configure tti properties */
		device_config->vp_config[i].tti.पूर्णांकr_enable =
					VXGE_HW_TIM_INTR_ENABLE;

		device_config->vp_config[i].tti.bसमयr_val =
			(VXGE_TTI_BTIMER_VAL * 1000) / 272;

		device_config->vp_config[i].tti.समयr_ac_en =
				VXGE_HW_TIM_TIMER_AC_ENABLE;

		/* For msi-x with napi (each vector has a handler of its own) -
		 * Set CI to OFF क्रम all vpaths
		 */
		device_config->vp_config[i].tti.समयr_ci_en =
			VXGE_HW_TIM_TIMER_CI_DISABLE;

		device_config->vp_config[i].tti.समयr_ri_en =
				VXGE_HW_TIM_TIMER_RI_DISABLE;

		device_config->vp_config[i].tti.util_sel =
			VXGE_HW_TIM_UTIL_SEL_LEGACY_TX_NET_UTIL;

		device_config->vp_config[i].tti.lसमयr_val =
			(VXGE_TTI_LTIMER_VAL * 1000) / 272;

		device_config->vp_config[i].tti.rसमयr_val =
			(VXGE_TTI_RTIMER_VAL * 1000) / 272;

		device_config->vp_config[i].tti.urange_a = TTI_TX_URANGE_A;
		device_config->vp_config[i].tti.urange_b = TTI_TX_URANGE_B;
		device_config->vp_config[i].tti.urange_c = TTI_TX_URANGE_C;
		device_config->vp_config[i].tti.uec_a = TTI_TX_UFC_A;
		device_config->vp_config[i].tti.uec_b = TTI_TX_UFC_B;
		device_config->vp_config[i].tti.uec_c = TTI_TX_UFC_C;
		device_config->vp_config[i].tti.uec_d = TTI_TX_UFC_D;

		/* Configure Rx rings */
		device_config->vp_config[i].ring.enable  =
						VXGE_HW_RING_ENABLE;

		device_config->vp_config[i].ring.ring_blocks  =
						VXGE_HW_DEF_RING_BLOCKS;

		device_config->vp_config[i].ring.buffer_mode =
			VXGE_HW_RING_RXD_BUFFER_MODE_1;

		device_config->vp_config[i].ring.rxds_limit  =
				VXGE_HW_DEF_RING_RXDS_LIMIT;

		device_config->vp_config[i].ring.scatter_mode =
					VXGE_HW_RING_SCATTER_MODE_A;

		/* Configure rti properties */
		device_config->vp_config[i].rti.पूर्णांकr_enable =
					VXGE_HW_TIM_INTR_ENABLE;

		device_config->vp_config[i].rti.bसमयr_val =
			(VXGE_RTI_BTIMER_VAL * 1000)/272;

		device_config->vp_config[i].rti.समयr_ac_en =
						VXGE_HW_TIM_TIMER_AC_ENABLE;

		device_config->vp_config[i].rti.समयr_ci_en =
						VXGE_HW_TIM_TIMER_CI_DISABLE;

		device_config->vp_config[i].rti.समयr_ri_en =
						VXGE_HW_TIM_TIMER_RI_DISABLE;

		device_config->vp_config[i].rti.util_sel =
				VXGE_HW_TIM_UTIL_SEL_LEGACY_RX_NET_UTIL;

		device_config->vp_config[i].rti.urange_a =
						RTI_RX_URANGE_A;
		device_config->vp_config[i].rti.urange_b =
						RTI_RX_URANGE_B;
		device_config->vp_config[i].rti.urange_c =
						RTI_RX_URANGE_C;
		device_config->vp_config[i].rti.uec_a = RTI_RX_UFC_A;
		device_config->vp_config[i].rti.uec_b = RTI_RX_UFC_B;
		device_config->vp_config[i].rti.uec_c = RTI_RX_UFC_C;
		device_config->vp_config[i].rti.uec_d = RTI_RX_UFC_D;

		device_config->vp_config[i].rti.rसमयr_val =
			(VXGE_RTI_RTIMER_VAL * 1000) / 272;

		device_config->vp_config[i].rti.lसमयr_val =
			(VXGE_RTI_LTIMER_VAL * 1000) / 272;

		device_config->vp_config[i].rpa_strip_vlan_tag =
			vlan_tag_strip;
	पूर्ण

	driver_config->vpath_per_dev = temp;
	वापस no_of_vpaths;
पूर्ण

/* initialize device configuratrions */
अटल व्योम vxge_device_config_init(काष्ठा vxge_hw_device_config *device_config,
				    पूर्णांक *पूर्णांकr_type)
अणु
	/* Used क्रम CQRQ/SRQ. */
	device_config->dma_blockpool_initial =
			VXGE_HW_INITIAL_DMA_BLOCK_POOL_SIZE;

	device_config->dma_blockpool_max =
			VXGE_HW_MAX_DMA_BLOCK_POOL_SIZE;

	अगर (max_mac_vpath > VXGE_MAX_MAC_ADDR_COUNT)
		max_mac_vpath = VXGE_MAX_MAC_ADDR_COUNT;

	अगर (!IS_ENABLED(CONFIG_PCI_MSI)) अणु
		vxge_debug_init(VXGE_ERR,
			"%s: This Kernel does not support "
			"MSI-X. Defaulting to INTA", VXGE_DRIVER_NAME);
		*पूर्णांकr_type = INTA;
	पूर्ण

	/* Configure whether MSI-X or IRQL. */
	चयन (*पूर्णांकr_type) अणु
	हाल INTA:
		device_config->पूर्णांकr_mode = VXGE_HW_INTR_MODE_IRQLINE;
		अवरोध;

	हाल MSI_X:
		device_config->पूर्णांकr_mode = VXGE_HW_INTR_MODE_MSIX_ONE_SHOT;
		अवरोध;
	पूर्ण

	/* Timer period between device poll */
	device_config->device_poll_millis = VXGE_TIMER_DELAY;

	/* Configure mac based steering. */
	device_config->rts_mac_en = addr_learn_en;

	/* Configure Vpaths */
	device_config->rth_it_type = VXGE_HW_RTH_IT_TYPE_MULTI_IT;

	vxge_debug_ll_config(VXGE_TRACE, "%s : Device Config Params ",
			__func__);
	vxge_debug_ll_config(VXGE_TRACE, "intr_mode : %d",
			device_config->पूर्णांकr_mode);
	vxge_debug_ll_config(VXGE_TRACE, "device_poll_millis : %d",
			device_config->device_poll_millis);
	vxge_debug_ll_config(VXGE_TRACE, "rth_en : %d",
			device_config->rth_en);
	vxge_debug_ll_config(VXGE_TRACE, "rth_it_type : %d",
			device_config->rth_it_type);
पूर्ण

अटल व्योम vxge_prपूर्णांक_parm(काष्ठा vxgedev *vdev, u64 vpath_mask)
अणु
	पूर्णांक i;

	vxge_debug_init(VXGE_TRACE,
		"%s: %d Vpath(s) opened",
		vdev->ndev->name, vdev->no_of_vpath);

	चयन (vdev->config.पूर्णांकr_type) अणु
	हाल INTA:
		vxge_debug_init(VXGE_TRACE,
			"%s: Interrupt type INTA", vdev->ndev->name);
		अवरोध;

	हाल MSI_X:
		vxge_debug_init(VXGE_TRACE,
			"%s: Interrupt type MSI-X", vdev->ndev->name);
		अवरोध;
	पूर्ण

	अगर (vdev->config.rth_steering) अणु
		vxge_debug_init(VXGE_TRACE,
			"%s: RTH steering enabled for TCP_IPV4",
			vdev->ndev->name);
	पूर्ण अन्यथा अणु
		vxge_debug_init(VXGE_TRACE,
			"%s: RTH steering disabled", vdev->ndev->name);
	पूर्ण

	चयन (vdev->config.tx_steering_type) अणु
	हाल NO_STEERING:
		vxge_debug_init(VXGE_TRACE,
			"%s: Tx steering disabled", vdev->ndev->name);
		अवरोध;
	हाल TX_PRIORITY_STEERING:
		vxge_debug_init(VXGE_TRACE,
			"%s: Unsupported tx steering option",
			vdev->ndev->name);
		vxge_debug_init(VXGE_TRACE,
			"%s: Tx steering disabled", vdev->ndev->name);
		vdev->config.tx_steering_type = 0;
		अवरोध;
	हाल TX_VLAN_STEERING:
		vxge_debug_init(VXGE_TRACE,
			"%s: Unsupported tx steering option",
			vdev->ndev->name);
		vxge_debug_init(VXGE_TRACE,
			"%s: Tx steering disabled", vdev->ndev->name);
		vdev->config.tx_steering_type = 0;
		अवरोध;
	हाल TX_MULTIQ_STEERING:
		vxge_debug_init(VXGE_TRACE,
			"%s: Tx multiqueue steering enabled",
			vdev->ndev->name);
		अवरोध;
	हाल TX_PORT_STEERING:
		vxge_debug_init(VXGE_TRACE,
			"%s: Tx port steering enabled",
			vdev->ndev->name);
		अवरोध;
	शेष:
		vxge_debug_init(VXGE_ERR,
			"%s: Unsupported tx steering type",
			vdev->ndev->name);
		vxge_debug_init(VXGE_TRACE,
			"%s: Tx steering disabled", vdev->ndev->name);
		vdev->config.tx_steering_type = 0;
	पूर्ण

	अगर (vdev->config.addr_learn_en)
		vxge_debug_init(VXGE_TRACE,
			"%s: MAC Address learning enabled", vdev->ndev->name);

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!vxge_bVALn(vpath_mask, i, 1))
			जारी;
		vxge_debug_ll_config(VXGE_TRACE,
			"%s: MTU size - %d", vdev->ndev->name,
			((vdev->devh))->
				config.vp_config[i].mtu);
		vxge_debug_init(VXGE_TRACE,
			"%s: VLAN tag stripping %s", vdev->ndev->name,
			((vdev->devh))->
				config.vp_config[i].rpa_strip_vlan_tag
			? "Enabled" : "Disabled");
		vxge_debug_ll_config(VXGE_TRACE,
			"%s: Max frags : %d", vdev->ndev->name,
			((vdev->devh))->
				config.vp_config[i].fअगरo.max_frags);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * vxge_pm_suspend - vxge घातer management suspend entry poपूर्णांक
 * @dev_d: device poपूर्णांकer
 *
 */
अटल पूर्णांक __maybe_unused vxge_pm_suspend(काष्ठा device *dev_d)
अणु
	वापस -ENOSYS;
पूर्ण
/**
 * vxge_pm_resume - vxge घातer management resume entry poपूर्णांक
 * @dev_d: device poपूर्णांकer
 *
 */
अटल पूर्णांक __maybe_unused vxge_pm_resume(काष्ठा device *dev_d)
अणु
	वापस -ENOSYS;
पूर्ण

/**
 * vxge_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t vxge_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा __vxge_hw_device *hldev = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = hldev->ndev;

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev)) अणु
		/* Bring करोwn the card, जबतक aव्योमing PCI I/O */
		करो_vxge_बंद(netdev, 0);
	पूर्ण

	pci_disable_device(pdev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * vxge_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 * At this poपूर्णांक, the card has exprienced a hard reset,
 * followed by fixups by BIOS, and has its config space
 * set up identically to what it was at cold boot.
 */
अटल pci_ers_result_t vxge_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा __vxge_hw_device *hldev = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = hldev->ndev;

	काष्ठा vxgedev *vdev = netdev_priv(netdev);

	अगर (pci_enable_device(pdev)) अणु
		netdev_err(netdev, "Cannot re-enable device after reset\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	pci_set_master(pdev);
	करो_vxge_reset(vdev, VXGE_LL_FULL_RESET);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * vxge_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells
 * us that its OK to resume normal operation.
 */
अटल व्योम vxge_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा __vxge_hw_device *hldev = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = hldev->ndev;

	अगर (netअगर_running(netdev)) अणु
		अगर (vxge_खोलो(netdev)) अणु
			netdev_err(netdev,
				   "Can't bring device back up after reset\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);
पूर्ण

अटल अंतरभूत u32 vxge_get_num_vfs(u64 function_mode)
अणु
	u32 num_functions = 0;

	चयन (function_mode) अणु
	हाल VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION:
	हाल VXGE_HW_FUNCTION_MODE_SRIOV_8:
		num_functions = 8;
		अवरोध;
	हाल VXGE_HW_FUNCTION_MODE_SINGLE_FUNCTION:
		num_functions = 1;
		अवरोध;
	हाल VXGE_HW_FUNCTION_MODE_SRIOV:
	हाल VXGE_HW_FUNCTION_MODE_MRIOV:
	हाल VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_17:
		num_functions = 17;
		अवरोध;
	हाल VXGE_HW_FUNCTION_MODE_SRIOV_4:
		num_functions = 4;
		अवरोध;
	हाल VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_2:
		num_functions = 2;
		अवरोध;
	हाल VXGE_HW_FUNCTION_MODE_MRIOV_8:
		num_functions = 8; /* TODO */
		अवरोध;
	पूर्ण
	वापस num_functions;
पूर्ण

पूर्णांक vxge_fw_upgrade(काष्ठा vxgedev *vdev, अक्षर *fw_name, पूर्णांक override)
अणु
	काष्ठा __vxge_hw_device *hldev = vdev->devh;
	u32 maj, min, bld, cmaj, cmin, cbld;
	क्रमागत vxge_hw_status status;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware(&fw, fw_name, &vdev->pdev->dev);
	अगर (ret) अणु
		vxge_debug_init(VXGE_ERR, "%s: Firmware file '%s' not found",
				VXGE_DRIVER_NAME, fw_name);
		जाओ out;
	पूर्ण

	/* Load the new firmware onto the adapter */
	status = vxge_update_fw_image(hldev, fw->data, fw->size);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
				"%s: FW image download to adapter failed '%s'.",
				VXGE_DRIVER_NAME, fw_name);
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Read the version of the new firmware */
	status = vxge_hw_upgrade_पढ़ो_version(hldev, &maj, &min, &bld);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
				"%s: Upgrade read version failed '%s'.",
				VXGE_DRIVER_NAME, fw_name);
		ret = -EIO;
		जाओ out;
	पूर्ण

	cmaj = vdev->config.device_hw_info.fw_version.major;
	cmin = vdev->config.device_hw_info.fw_version.minor;
	cbld = vdev->config.device_hw_info.fw_version.build;
	/* It's possible the version in /lib/firmware is not the latest version.
	 * If so, we could get पूर्णांकo a loop of trying to upgrade to the latest
	 * and flashing the older version.
	 */
	अगर (VXGE_FW_VER(maj, min, bld) == VXGE_FW_VER(cmaj, cmin, cbld) &&
	    !override) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE "Upgrade to firmware version %d.%d.%d commencing\n",
	       maj, min, bld);

	/* Flash the adapter with the new firmware */
	status = vxge_hw_flash_fw(hldev);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR, "%s: Upgrade commit failed '%s'.",
				VXGE_DRIVER_NAME, fw_name);
		ret = -EIO;
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE "Upgrade of firmware successful!  Adapter must be "
	       "hard reset before using, thus requiring a system reboot or a "
	       "hotplug event.\n");

out:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक vxge_probe_fw_update(काष्ठा vxgedev *vdev)
अणु
	u32 maj, min, bld;
	पूर्णांक ret, gpxe = 0;
	अक्षर *fw_name;

	maj = vdev->config.device_hw_info.fw_version.major;
	min = vdev->config.device_hw_info.fw_version.minor;
	bld = vdev->config.device_hw_info.fw_version.build;

	अगर (VXGE_FW_VER(maj, min, bld) == VXGE_CERT_FW_VER)
		वापस 0;

	/* Ignore the build number when determining अगर the current firmware is
	 * "too new" to load the driver
	 */
	अगर (VXGE_FW_VER(maj, min, 0) > VXGE_CERT_FW_VER) अणु
		vxge_debug_init(VXGE_ERR, "%s: Firmware newer than last known "
				"version, unable to load driver\n",
				VXGE_DRIVER_NAME);
		वापस -EINVAL;
	पूर्ण

	/* Firmware 1.4.4 and older cannot be upgraded, and is too ancient to
	 * work with this driver.
	 */
	अगर (VXGE_FW_VER(maj, min, bld) <= VXGE_FW_DEAD_VER) अणु
		vxge_debug_init(VXGE_ERR, "%s: Firmware %d.%d.%d cannot be "
				"upgraded\n", VXGE_DRIVER_NAME, maj, min, bld);
		वापस -EINVAL;
	पूर्ण

	/* If file not specअगरied, determine gPXE or not */
	अगर (VXGE_FW_VER(maj, min, bld) >= VXGE_EPROM_FW_VER) अणु
		पूर्णांक i;
		क्रम (i = 0; i < VXGE_HW_MAX_ROM_IMAGES; i++)
			अगर (vdev->devh->eprom_versions[i]) अणु
				gpxe = 1;
				अवरोध;
			पूर्ण
	पूर्ण
	अगर (gpxe)
		fw_name = "vxge/X3fw-pxe.ncf";
	अन्यथा
		fw_name = "vxge/X3fw.ncf";

	ret = vxge_fw_upgrade(vdev, fw_name, 0);
	/* -EINVAL and -ENOENT are not fatal errors क्रम flashing firmware on
	 * probe, so ignore them
	 */
	अगर (ret != -EINVAL && ret != -ENOENT)
		वापस -EIO;
	अन्यथा
		ret = 0;

	अगर (VXGE_FW_VER(VXGE_CERT_FW_VER_MAJOR, VXGE_CERT_FW_VER_MINOR, 0) >
	    VXGE_FW_VER(maj, min, 0)) अणु
		vxge_debug_init(VXGE_ERR, "%s: Firmware %d.%d.%d is too old to"
				" be used with this driver.",
				VXGE_DRIVER_NAME, maj, min, bld);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक is_sriov_initialized(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक pos;
	u16 ctrl;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	अगर (pos) अणु
		pci_पढ़ो_config_word(pdev, pos + PCI_SRIOV_CTRL, &ctrl);
		अगर (ctrl & PCI_SRIOV_CTRL_VFE)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vxge_hw_uld_cbs vxge_callbacks = अणु
	.link_up = vxge_callback_link_up,
	.link_करोwn = vxge_callback_link_करोwn,
	.crit_err = vxge_callback_crit_err,
पूर्ण;

/**
 * vxge_probe
 * @pdev : काष्ठाure containing the PCI related inक्रमmation of the device.
 * @pre: List of PCI devices supported by the driver listed in vxge_id_table.
 * Description:
 * This function is called when a new PCI device माला_लो detected and initializes
 * it.
 * Return value:
 * वापसs 0 on success and negative on failure.
 *
 */
अटल पूर्णांक
vxge_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *pre)
अणु
	काष्ठा __vxge_hw_device *hldev;
	क्रमागत vxge_hw_status status;
	पूर्णांक ret;
	पूर्णांक high_dma = 0;
	u64 vpath_mask = 0;
	काष्ठा vxgedev *vdev;
	काष्ठा vxge_config *ll_config = शून्य;
	काष्ठा vxge_hw_device_config *device_config = शून्य;
	काष्ठा vxge_hw_device_attr attr;
	पूर्णांक i, j, no_of_vpath = 0, max_vpath_supported = 0;
	u8 *macaddr;
	काष्ठा vxge_mac_addrs *entry;
	अटल पूर्णांक bus = -1, device = -1;
	u32 host_type;
	u8 new_device = 0;
	क्रमागत vxge_hw_status is_privileged;
	u32 function_mode;
	u32 num_vfs = 0;

	vxge_debug_entryनिकास(VXGE_TRACE, "%s:%d", __func__, __LINE__);
	attr.pdev = pdev;

	/* In SRIOV-17 mode, functions of the same adapter
	 * can be deployed on dअगरferent buses
	 */
	अगर (((bus != pdev->bus->number) || (device != PCI_SLOT(pdev->devfn))) &&
	    !pdev->is_virtfn)
		new_device = 1;

	bus = pdev->bus->number;
	device = PCI_SLOT(pdev->devfn);

	अगर (new_device) अणु
		अगर (driver_config->config_dev_cnt &&
		   (driver_config->config_dev_cnt !=
			driver_config->total_dev_cnt))
			vxge_debug_init(VXGE_ERR,
				"%s: Configured %d of %d devices",
				VXGE_DRIVER_NAME,
				driver_config->config_dev_cnt,
				driver_config->total_dev_cnt);
		driver_config->config_dev_cnt = 0;
		driver_config->total_dev_cnt = 0;
	पूर्ण

	/* Now making the CPU based no of vpath calculation
	 * applicable क्रम inभागidual functions as well.
	 */
	driver_config->g_no_cpus = 0;
	driver_config->vpath_per_dev = max_config_vpath;

	driver_config->total_dev_cnt++;
	अगर (++driver_config->config_dev_cnt > max_config_dev) अणु
		ret = 0;
		जाओ _निकास0;
	पूर्ण

	device_config = kzalloc(माप(काष्ठा vxge_hw_device_config),
		GFP_KERNEL);
	अगर (!device_config) अणु
		ret = -ENOMEM;
		vxge_debug_init(VXGE_ERR,
			"device_config : malloc failed %s %d",
			__खाता__, __LINE__);
		जाओ _निकास0;
	पूर्ण

	ll_config = kzalloc(माप(काष्ठा vxge_config), GFP_KERNEL);
	अगर (!ll_config) अणु
		ret = -ENOMEM;
		vxge_debug_init(VXGE_ERR,
			"device_config : malloc failed %s %d",
			__खाता__, __LINE__);
		जाओ _निकास0;
	पूर्ण
	ll_config->tx_steering_type = TX_MULTIQ_STEERING;
	ll_config->पूर्णांकr_type = MSI_X;
	ll_config->napi_weight = NEW_NAPI_WEIGHT;
	ll_config->rth_steering = RTH_STEERING;

	/* get the शेष configuration parameters */
	vxge_hw_device_config_शेष_get(device_config);

	/* initialize configuration parameters */
	vxge_device_config_init(device_config, &ll_config->पूर्णांकr_type);

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		vxge_debug_init(VXGE_ERR,
			"%s : can not enable PCI device", __func__);
		जाओ _निकास0;
	पूर्ण

	अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		vxge_debug_ll_config(VXGE_TRACE,
			"%s : using 64bit DMA", __func__);

		high_dma = 1;

		अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
			vxge_debug_init(VXGE_ERR,
				"%s : unable to obtain 64bit DMA for "
				"consistent allocations", __func__);
			ret = -ENOMEM;
			जाओ _निकास1;
		पूर्ण
	पूर्ण अन्यथा अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		vxge_debug_ll_config(VXGE_TRACE,
			"%s : using 32bit DMA", __func__);
	पूर्ण अन्यथा अणु
		ret = -ENOMEM;
		जाओ _निकास1;
	पूर्ण

	ret = pci_request_region(pdev, 0, VXGE_DRIVER_NAME);
	अगर (ret) अणु
		vxge_debug_init(VXGE_ERR,
			"%s : request regions failed", __func__);
		जाओ _निकास1;
	पूर्ण

	pci_set_master(pdev);

	attr.bar0 = pci_ioremap_bar(pdev, 0);
	अगर (!attr.bar0) अणु
		vxge_debug_init(VXGE_ERR,
			"%s : cannot remap io memory bar0", __func__);
		ret = -ENODEV;
		जाओ _निकास2;
	पूर्ण
	vxge_debug_ll_config(VXGE_TRACE,
		"pci ioremap bar0: %p:0x%llx",
		attr.bar0,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 0));

	status = vxge_hw_device_hw_info_get(attr.bar0,
			&ll_config->device_hw_info);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"%s: Reading of hardware info failed."
			"Please try upgrading the firmware.", VXGE_DRIVER_NAME);
		ret = -EINVAL;
		जाओ _निकास3;
	पूर्ण

	vpath_mask = ll_config->device_hw_info.vpath_mask;
	अगर (vpath_mask == 0) अणु
		vxge_debug_ll_config(VXGE_TRACE,
			"%s: No vpaths available in device", VXGE_DRIVER_NAME);
		ret = -EINVAL;
		जाओ _निकास3;
	पूर्ण

	vxge_debug_ll_config(VXGE_TRACE,
		"%s:%d  Vpath mask = %llx", __func__, __LINE__,
		(अचिन्हित दीर्घ दीर्घ)vpath_mask);

	function_mode = ll_config->device_hw_info.function_mode;
	host_type = ll_config->device_hw_info.host_type;
	is_privileged = __vxge_hw_device_is_privilaged(host_type,
		ll_config->device_hw_info.func_id);

	/* Check how many vpaths are available */
	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!((vpath_mask) & vxge_mBIT(i)))
			जारी;
		max_vpath_supported++;
	पूर्ण

	अगर (new_device)
		num_vfs = vxge_get_num_vfs(function_mode) - 1;

	/* Enable SRIOV mode, अगर firmware has SRIOV support and अगर it is a PF */
	अगर (is_sriov(function_mode) && !is_sriov_initialized(pdev) &&
	   (ll_config->पूर्णांकr_type != INTA)) अणु
		ret = pci_enable_sriov(pdev, num_vfs);
		अगर (ret)
			vxge_debug_ll_config(VXGE_ERR,
				"Failed in enabling SRIOV mode: %d\n", ret);
			/* No need to fail out, as an error here is non-fatal */
	पूर्ण

	/*
	 * Configure vpaths and get driver configured number of vpaths
	 * which is less than or equal to the maximum vpaths per function.
	 */
	no_of_vpath = vxge_config_vpaths(device_config, vpath_mask, ll_config);
	अगर (!no_of_vpath) अणु
		vxge_debug_ll_config(VXGE_ERR,
			"%s: No more vpaths to configure", VXGE_DRIVER_NAME);
		ret = 0;
		जाओ _निकास3;
	पूर्ण

	/* Setting driver callbacks */
	attr.uld_callbacks = &vxge_callbacks;

	status = vxge_hw_device_initialize(&hldev, &attr, device_config);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"Failed to initialize device (%d)", status);
		ret = -EINVAL;
		जाओ _निकास3;
	पूर्ण

	अगर (VXGE_FW_VER(ll_config->device_hw_info.fw_version.major,
			ll_config->device_hw_info.fw_version.minor,
			ll_config->device_hw_info.fw_version.build) >=
	    VXGE_EPROM_FW_VER) अणु
		काष्ठा eprom_image img[VXGE_HW_MAX_ROM_IMAGES];

		status = vxge_hw_vpath_eprom_img_ver_get(hldev, img);
		अगर (status != VXGE_HW_OK) अणु
			vxge_debug_init(VXGE_ERR, "%s: Reading of EPROM failed",
					VXGE_DRIVER_NAME);
			/* This is a non-fatal error, जारी */
		पूर्ण

		क्रम (i = 0; i < VXGE_HW_MAX_ROM_IMAGES; i++) अणु
			hldev->eprom_versions[i] = img[i].version;
			अगर (!img[i].is_valid)
				अवरोध;
			vxge_debug_init(VXGE_TRACE, "%s: EPROM %d, version "
					"%d.%d.%d.%d", VXGE_DRIVER_NAME, i,
					VXGE_EPROM_IMG_MAJOR(img[i].version),
					VXGE_EPROM_IMG_MINOR(img[i].version),
					VXGE_EPROM_IMG_FIX(img[i].version),
					VXGE_EPROM_IMG_BUILD(img[i].version));
		पूर्ण
	पूर्ण

	/* अगर FCS stripping is not disabled in MAC fail driver load */
	status = vxge_hw_vpath_strip_fcs_check(hldev, vpath_mask);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR, "%s: FCS stripping is enabled in MAC"
				" failing driver load", VXGE_DRIVER_NAME);
		ret = -EINVAL;
		जाओ _निकास4;
	पूर्ण

	/* Always enable HWTS.  This will always cause the FCS to be invalid,
	 * due to the fact that HWTS is using the FCS as the location of the
	 * बारtamp.  The HW FCS checking will still correctly determine अगर
	 * there is a valid checksum, and the FCS is being हटाओd by the driver
	 * anyway.  So no functionality is being lost.  Since it is always
	 * enabled, we now simply use the ioctl call to set whether or not the
	 * driver should be paying attention to the HWTS.
	 */
	अगर (is_privileged == VXGE_HW_OK) अणु
		status = vxge_बारtamp_config(hldev);
		अगर (status != VXGE_HW_OK) अणु
			vxge_debug_init(VXGE_ERR, "%s: HWTS enable failed",
					VXGE_DRIVER_NAME);
			ret = -EFAULT;
			जाओ _निकास4;
		पूर्ण
	पूर्ण

	vxge_hw_device_debug_set(hldev, VXGE_ERR, VXGE_COMPONENT_LL);

	/* set निजी device info */
	pci_set_drvdata(pdev, hldev);

	ll_config->fअगरo_indicate_max_pkts = VXGE_FIFO_INDICATE_MAX_PKTS;
	ll_config->addr_learn_en = addr_learn_en;
	ll_config->rth_algorithm = RTH_ALG_JENKINS;
	ll_config->rth_hash_type_tcpipv4 = 1;
	ll_config->rth_hash_type_ipv4 = 0;
	ll_config->rth_hash_type_tcpipv6 = 0;
	ll_config->rth_hash_type_ipv6 = 0;
	ll_config->rth_hash_type_tcpipv6ex = 0;
	ll_config->rth_hash_type_ipv6ex = 0;
	ll_config->rth_bkt_sz = RTH_BUCKET_SIZE;
	ll_config->tx_छोड़ो_enable = VXGE_PAUSE_CTRL_ENABLE;
	ll_config->rx_छोड़ो_enable = VXGE_PAUSE_CTRL_ENABLE;

	ret = vxge_device_रेजिस्टर(hldev, ll_config, high_dma, no_of_vpath,
				   &vdev);
	अगर (ret) अणु
		ret = -EINVAL;
		जाओ _निकास4;
	पूर्ण

	ret = vxge_probe_fw_update(vdev);
	अगर (ret)
		जाओ _निकास5;

	vxge_hw_device_debug_set(hldev, VXGE_TRACE, VXGE_COMPONENT_LL);
	VXGE_COPY_DEBUG_INFO_TO_LL(vdev, vxge_hw_device_error_level_get(hldev),
		vxge_hw_device_trace_level_get(hldev));

	/* set निजी HW device info */
	vdev->mtu = VXGE_HW_DEFAULT_MTU;
	vdev->bar0 = attr.bar0;
	vdev->max_vpath_supported = max_vpath_supported;
	vdev->no_of_vpath = no_of_vpath;

	/* Virtual Path count */
	क्रम (i = 0, j = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!vxge_bVALn(vpath_mask, i, 1))
			जारी;
		अगर (j >= vdev->no_of_vpath)
			अवरोध;

		vdev->vpaths[j].is_configured = 1;
		vdev->vpaths[j].device_id = i;
		vdev->vpaths[j].ring.driver_id = j;
		vdev->vpaths[j].vdev = vdev;
		vdev->vpaths[j].max_mac_addr_cnt = max_mac_vpath;
		स_नकल((u8 *)vdev->vpaths[j].macaddr,
				ll_config->device_hw_info.mac_addrs[i],
				ETH_ALEN);

		/* Initialize the mac address list header */
		INIT_LIST_HEAD(&vdev->vpaths[j].mac_addr_list);

		vdev->vpaths[j].mac_addr_cnt = 0;
		vdev->vpaths[j].mcast_addr_cnt = 0;
		j++;
	पूर्ण
	vdev->exec_mode = VXGE_EXEC_MODE_DISABLE;
	vdev->max_config_port = max_config_port;

	vdev->vlan_tag_strip = vlan_tag_strip;

	/* map the hashing selector table to the configured vpaths */
	क्रम (i = 0; i < vdev->no_of_vpath; i++)
		vdev->vpath_selector[i] = vpath_selector[i];

	macaddr = (u8 *)vdev->vpaths[0].macaddr;

	ll_config->device_hw_info.serial_number[VXGE_HW_INFO_LEN - 1] = '\0';
	ll_config->device_hw_info.product_desc[VXGE_HW_INFO_LEN - 1] = '\0';
	ll_config->device_hw_info.part_number[VXGE_HW_INFO_LEN - 1] = '\0';

	vxge_debug_init(VXGE_TRACE, "%s: SERIAL NUMBER: %s",
		vdev->ndev->name, ll_config->device_hw_info.serial_number);

	vxge_debug_init(VXGE_TRACE, "%s: PART NUMBER: %s",
		vdev->ndev->name, ll_config->device_hw_info.part_number);

	vxge_debug_init(VXGE_TRACE, "%s: Neterion %s Server Adapter",
		vdev->ndev->name, ll_config->device_hw_info.product_desc);

	vxge_debug_init(VXGE_TRACE, "%s: MAC ADDR: %pM",
		vdev->ndev->name, macaddr);

	vxge_debug_init(VXGE_TRACE, "%s: Link Width x%d",
		vdev->ndev->name, vxge_hw_device_link_width_get(hldev));

	vxge_debug_init(VXGE_TRACE,
		"%s: Firmware version : %s Date : %s", vdev->ndev->name,
		ll_config->device_hw_info.fw_version.version,
		ll_config->device_hw_info.fw_date.date);

	अगर (new_device) अणु
		चयन (ll_config->device_hw_info.function_mode) अणु
		हाल VXGE_HW_FUNCTION_MODE_SINGLE_FUNCTION:
			vxge_debug_init(VXGE_TRACE,
			"%s: Single Function Mode Enabled", vdev->ndev->name);
		अवरोध;
		हाल VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION:
			vxge_debug_init(VXGE_TRACE,
			"%s: Multi Function Mode Enabled", vdev->ndev->name);
		अवरोध;
		हाल VXGE_HW_FUNCTION_MODE_SRIOV:
			vxge_debug_init(VXGE_TRACE,
			"%s: Single Root IOV Mode Enabled", vdev->ndev->name);
		अवरोध;
		हाल VXGE_HW_FUNCTION_MODE_MRIOV:
			vxge_debug_init(VXGE_TRACE,
			"%s: Multi Root IOV Mode Enabled", vdev->ndev->name);
		अवरोध;
		पूर्ण
	पूर्ण

	vxge_prपूर्णांक_parm(vdev, vpath_mask);

	/* Store the fw version क्रम ethttool option */
	म_नकल(vdev->fw_version, ll_config->device_hw_info.fw_version.version);
	स_नकल(vdev->ndev->dev_addr, (u8 *)vdev->vpaths[0].macaddr, ETH_ALEN);

	/* Copy the station mac address to the list */
	क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
		entry =	kzalloc(माप(काष्ठा vxge_mac_addrs), GFP_KERNEL);
		अगर (शून्य == entry) अणु
			vxge_debug_init(VXGE_ERR,
				"%s: mac_addr_list : memory allocation failed",
				vdev->ndev->name);
			ret = -EPERM;
			जाओ _निकास6;
		पूर्ण
		macaddr = (u8 *)&entry->macaddr;
		स_नकल(macaddr, vdev->ndev->dev_addr, ETH_ALEN);
		list_add(&entry->item, &vdev->vpaths[i].mac_addr_list);
		vdev->vpaths[i].mac_addr_cnt = 1;
	पूर्ण

	kमुक्त(device_config);

	/*
	 * INTA is shared in multi-function mode. This is unlike the INTA
	 * implementation in MR mode, where each VH has its own INTA message.
	 * - INTA is masked (disabled) as दीर्घ as at least one function sets
	 * its TITAN_MASK_ALL_INT.ALARM bit.
	 * - INTA is unmasked (enabled) when all enabled functions have cleared
	 * their own TITAN_MASK_ALL_INT.ALARM bit.
	 * The TITAN_MASK_ALL_INT ALARM & TRAFFIC bits are cleared on घातer up.
	 * Though this driver leaves the top level पूर्णांकerrupts unmasked जबतक
	 * leaving the required module पूर्णांकerrupt bits masked on निकास, there
	 * could be a rougue driver around that करोes not follow this procedure
	 * resulting in a failure to generate पूर्णांकerrupts. The following code is
	 * present to prevent such a failure.
	 */

	अगर (ll_config->device_hw_info.function_mode ==
		VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION)
		अगर (vdev->config.पूर्णांकr_type == INTA)
			vxge_hw_device_unmask_all(hldev);

	vxge_debug_entryनिकास(VXGE_TRACE, "%s: %s:%d  Exiting...",
		vdev->ndev->name, __func__, __LINE__);

	vxge_hw_device_debug_set(hldev, VXGE_ERR, VXGE_COMPONENT_LL);
	VXGE_COPY_DEBUG_INFO_TO_LL(vdev, vxge_hw_device_error_level_get(hldev),
		vxge_hw_device_trace_level_get(hldev));

	kमुक्त(ll_config);
	वापस 0;

_निकास6:
	क्रम (i = 0; i < vdev->no_of_vpath; i++)
		vxge_मुक्त_mac_add_list(&vdev->vpaths[i]);
_निकास5:
	vxge_device_unरेजिस्टर(hldev);
_निकास4:
	vxge_hw_device_terminate(hldev);
	pci_disable_sriov(pdev);
_निकास3:
	iounmap(attr.bar0);
_निकास2:
	pci_release_region(pdev, 0);
_निकास1:
	pci_disable_device(pdev);
_निकास0:
	kमुक्त(ll_config);
	kमुक्त(device_config);
	driver_config->config_dev_cnt--;
	driver_config->total_dev_cnt--;
	वापस ret;
पूर्ण

/**
 * vxge_rem_nic - Free the PCI device
 * @pdev: काष्ठाure containing the PCI related inक्रमmation of the device.
 * Description: This function is called by the Pci subप्रणाली to release a
 * PCI device and मुक्त up all resource held up by the device.
 */
अटल व्योम vxge_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा __vxge_hw_device *hldev;
	काष्ठा vxgedev *vdev;
	पूर्णांक i;

	hldev = pci_get_drvdata(pdev);
	अगर (hldev == शून्य)
		वापस;

	vdev = netdev_priv(hldev->ndev);

	vxge_debug_entryनिकास(vdev->level_trace,	"%s:%d", __func__, __LINE__);
	vxge_debug_init(vdev->level_trace, "%s : removing PCI device...",
			__func__);

	क्रम (i = 0; i < vdev->no_of_vpath; i++)
		vxge_मुक्त_mac_add_list(&vdev->vpaths[i]);

	vxge_device_unरेजिस्टर(hldev);
	/* Do not call pci_disable_sriov here, as it will अवरोध child devices */
	vxge_hw_device_terminate(hldev);
	iounmap(vdev->bar0);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
	driver_config->config_dev_cnt--;
	driver_config->total_dev_cnt--;

	vxge_debug_init(vdev->level_trace, "%s:%d Device unregistered",
			__func__, __LINE__);
	vxge_debug_entryनिकास(vdev->level_trace,	"%s:%d  Exiting...", __func__,
			     __LINE__);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers vxge_err_handler = अणु
	.error_detected = vxge_io_error_detected,
	.slot_reset = vxge_io_slot_reset,
	.resume = vxge_io_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(vxge_pm_ops, vxge_pm_suspend, vxge_pm_resume);

अटल काष्ठा pci_driver vxge_driver = अणु
	.name = VXGE_DRIVER_NAME,
	.id_table = vxge_id_table,
	.probe = vxge_probe,
	.हटाओ = vxge_हटाओ,
	.driver.pm = &vxge_pm_ops,
	.err_handler = &vxge_err_handler,
पूर्ण;

अटल पूर्णांक __init
vxge_starter(व्योम)
अणु
	पूर्णांक ret = 0;

	pr_info("Copyright(c) 2002-2010 Exar Corp.\n");
	pr_info("Driver version: %s\n", DRV_VERSION);

	verअगरy_bandwidth();

	driver_config = kzalloc(माप(काष्ठा vxge_drv_config), GFP_KERNEL);
	अगर (!driver_config)
		वापस -ENOMEM;

	ret = pci_रेजिस्टर_driver(&vxge_driver);
	अगर (ret) अणु
		kमुक्त(driver_config);
		जाओ err;
	पूर्ण

	अगर (driver_config->config_dev_cnt &&
	   (driver_config->config_dev_cnt != driver_config->total_dev_cnt))
		vxge_debug_init(VXGE_ERR,
			"%s: Configured %d of %d devices",
			VXGE_DRIVER_NAME, driver_config->config_dev_cnt,
			driver_config->total_dev_cnt);
err:
	वापस ret;
पूर्ण

अटल व्योम __निकास
vxge_बंदr(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vxge_driver);
	kमुक्त(driver_config);
पूर्ण
module_init(vxge_starter);
module_निकास(vxge_बंदr);
