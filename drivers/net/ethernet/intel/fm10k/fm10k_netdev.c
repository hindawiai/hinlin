<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश "fm10k.h"
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/udp_tunnel.h>
#समावेश <linux/अगर_macvlan.h>

/**
 * fm10k_setup_tx_resources - allocate Tx resources (Descriptors)
 * @tx_ring:    tx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Return 0 on success, negative on failure
 **/
पूर्णांक fm10k_setup_tx_resources(काष्ठा fm10k_ring *tx_ring)
अणु
	काष्ठा device *dev = tx_ring->dev;
	पूर्णांक size;

	size = माप(काष्ठा fm10k_tx_buffer) * tx_ring->count;

	tx_ring->tx_buffer = vzalloc(size);
	अगर (!tx_ring->tx_buffer)
		जाओ err;

	u64_stats_init(&tx_ring->syncp);

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(काष्ठा fm10k_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	tx_ring->desc = dma_alloc_coherent(dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc)
		जाओ err;

	वापस 0;

err:
	vमुक्त(tx_ring->tx_buffer);
	tx_ring->tx_buffer = शून्य;
	वापस -ENOMEM;
पूर्ण

/**
 * fm10k_setup_all_tx_resources - allocate all queues Tx resources
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक fm10k_setup_all_tx_resources(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++) अणु
		err = fm10k_setup_tx_resources(पूर्णांकerface->tx_ring[i]);
		अगर (!err)
			जारी;

		netअगर_err(पूर्णांकerface, probe, पूर्णांकerface->netdev,
			  "Allocation for Tx Queue %u failed\n", i);
		जाओ err_setup_tx;
	पूर्ण

	वापस 0;
err_setup_tx:
	/* शुरुआत the index मुक्तing the rings as we go */
	जबतक (i--)
		fm10k_मुक्त_tx_resources(पूर्णांकerface->tx_ring[i]);
	वापस err;
पूर्ण

/**
 * fm10k_setup_rx_resources - allocate Rx resources (Descriptors)
 * @rx_ring:    rx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Returns 0 on success, negative on failure
 **/
पूर्णांक fm10k_setup_rx_resources(काष्ठा fm10k_ring *rx_ring)
अणु
	काष्ठा device *dev = rx_ring->dev;
	पूर्णांक size;

	size = माप(काष्ठा fm10k_rx_buffer) * rx_ring->count;

	rx_ring->rx_buffer = vzalloc(size);
	अगर (!rx_ring->rx_buffer)
		जाओ err;

	u64_stats_init(&rx_ring->syncp);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * माप(जोड़ fm10k_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	rx_ring->desc = dma_alloc_coherent(dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);
	अगर (!rx_ring->desc)
		जाओ err;

	वापस 0;
err:
	vमुक्त(rx_ring->rx_buffer);
	rx_ring->rx_buffer = शून्य;
	वापस -ENOMEM;
पूर्ण

/**
 * fm10k_setup_all_rx_resources - allocate all queues Rx resources
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक fm10k_setup_all_rx_resources(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++) अणु
		err = fm10k_setup_rx_resources(पूर्णांकerface->rx_ring[i]);
		अगर (!err)
			जारी;

		netअगर_err(पूर्णांकerface, probe, पूर्णांकerface->netdev,
			  "Allocation for Rx Queue %u failed\n", i);
		जाओ err_setup_rx;
	पूर्ण

	वापस 0;
err_setup_rx:
	/* शुरुआत the index मुक्तing the rings as we go */
	जबतक (i--)
		fm10k_मुक्त_rx_resources(पूर्णांकerface->rx_ring[i]);
	वापस err;
पूर्ण

व्योम fm10k_unmap_and_मुक्त_tx_resource(काष्ठा fm10k_ring *ring,
				      काष्ठा fm10k_tx_buffer *tx_buffer)
अणु
	अगर (tx_buffer->skb) अणु
		dev_kमुक्त_skb_any(tx_buffer->skb);
		अगर (dma_unmap_len(tx_buffer, len))
			dma_unmap_single(ring->dev,
					 dma_unmap_addr(tx_buffer, dma),
					 dma_unmap_len(tx_buffer, len),
					 DMA_TO_DEVICE);
	पूर्ण अन्यथा अगर (dma_unmap_len(tx_buffer, len)) अणु
		dma_unmap_page(ring->dev,
			       dma_unmap_addr(tx_buffer, dma),
			       dma_unmap_len(tx_buffer, len),
			       DMA_TO_DEVICE);
	पूर्ण
	tx_buffer->next_to_watch = शून्य;
	tx_buffer->skb = शून्य;
	dma_unmap_len_set(tx_buffer, len, 0);
	/* tx_buffer must be completely set up in the transmit path */
पूर्ण

/**
 * fm10k_clean_tx_ring - Free Tx Buffers
 * @tx_ring: ring to be cleaned
 **/
अटल व्योम fm10k_clean_tx_ring(काष्ठा fm10k_ring *tx_ring)
अणु
	अचिन्हित दीर्घ size;
	u16 i;

	/* ring alपढ़ोy cleared, nothing to करो */
	अगर (!tx_ring->tx_buffer)
		वापस;

	/* Free all the Tx ring sk_buffs */
	क्रम (i = 0; i < tx_ring->count; i++) अणु
		काष्ठा fm10k_tx_buffer *tx_buffer = &tx_ring->tx_buffer[i];

		fm10k_unmap_and_मुक्त_tx_resource(tx_ring, tx_buffer);
	पूर्ण

	/* reset BQL values */
	netdev_tx_reset_queue(txring_txq(tx_ring));

	size = माप(काष्ठा fm10k_tx_buffer) * tx_ring->count;
	स_रखो(tx_ring->tx_buffer, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(tx_ring->desc, 0, tx_ring->size);
पूर्ण

/**
 * fm10k_मुक्त_tx_resources - Free Tx Resources per Queue
 * @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 * Free all transmit software resources
 **/
व्योम fm10k_मुक्त_tx_resources(काष्ठा fm10k_ring *tx_ring)
अणु
	fm10k_clean_tx_ring(tx_ring);

	vमुक्त(tx_ring->tx_buffer);
	tx_ring->tx_buffer = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!tx_ring->desc)
		वापस;

	dma_मुक्त_coherent(tx_ring->dev, tx_ring->size,
			  tx_ring->desc, tx_ring->dma);
	tx_ring->desc = शून्य;
पूर्ण

/**
 * fm10k_clean_all_tx_rings - Free Tx Buffers क्रम all queues
 * @पूर्णांकerface: board निजी काष्ठाure
 **/
व्योम fm10k_clean_all_tx_rings(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++)
		fm10k_clean_tx_ring(पूर्णांकerface->tx_ring[i]);
पूर्ण

/**
 * fm10k_मुक्त_all_tx_resources - Free Tx Resources क्रम All Queues
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Free all transmit software resources
 **/
अटल व्योम fm10k_मुक्त_all_tx_resources(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i = पूर्णांकerface->num_tx_queues;

	जबतक (i--)
		fm10k_मुक्त_tx_resources(पूर्णांकerface->tx_ring[i]);
पूर्ण

/**
 * fm10k_clean_rx_ring - Free Rx Buffers per Queue
 * @rx_ring: ring to मुक्त buffers from
 **/
अटल व्योम fm10k_clean_rx_ring(काष्ठा fm10k_ring *rx_ring)
अणु
	अचिन्हित दीर्घ size;
	u16 i;

	अगर (!rx_ring->rx_buffer)
		वापस;

	dev_kमुक्त_skb(rx_ring->skb);
	rx_ring->skb = शून्य;

	/* Free all the Rx ring sk_buffs */
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		काष्ठा fm10k_rx_buffer *buffer = &rx_ring->rx_buffer[i];
		/* clean-up will only set page poपूर्णांकer to शून्य */
		अगर (!buffer->page)
			जारी;

		dma_unmap_page(rx_ring->dev, buffer->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
		__मुक्त_page(buffer->page);

		buffer->page = शून्य;
	पूर्ण

	size = माप(काष्ठा fm10k_rx_buffer) * rx_ring->count;
	स_रखो(rx_ring->rx_buffer, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
पूर्ण

/**
 * fm10k_मुक्त_rx_resources - Free Rx Resources
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 **/
व्योम fm10k_मुक्त_rx_resources(काष्ठा fm10k_ring *rx_ring)
अणु
	fm10k_clean_rx_ring(rx_ring);

	vमुक्त(rx_ring->rx_buffer);
	rx_ring->rx_buffer = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!rx_ring->desc)
		वापस;

	dma_मुक्त_coherent(rx_ring->dev, rx_ring->size,
			  rx_ring->desc, rx_ring->dma);

	rx_ring->desc = शून्य;
पूर्ण

/**
 * fm10k_clean_all_rx_rings - Free Rx Buffers क्रम all queues
 * @पूर्णांकerface: board निजी काष्ठाure
 **/
व्योम fm10k_clean_all_rx_rings(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++)
		fm10k_clean_rx_ring(पूर्णांकerface->rx_ring[i]);
पूर्ण

/**
 * fm10k_मुक्त_all_rx_resources - Free Rx Resources क्रम All Queues
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * Free all receive software resources
 **/
अटल व्योम fm10k_मुक्त_all_rx_resources(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i = पूर्णांकerface->num_rx_queues;

	जबतक (i--)
		fm10k_मुक्त_rx_resources(पूर्णांकerface->rx_ring[i]);
पूर्ण

/**
 * fm10k_request_glort_range - Request GLORTs क्रम use in configuring rules
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * This function allocates a range of glorts क्रम this पूर्णांकerface to use.
 **/
अटल व्योम fm10k_request_glort_range(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u16 mask = (~hw->mac.dglort_map) >> FM10K_DGLORTMAP_MASK_SHIFT;

	/* establish GLORT base */
	पूर्णांकerface->glort = hw->mac.dglort_map & FM10K_DGLORTMAP_NONE;
	पूर्णांकerface->glort_count = 0;

	/* nothing we can करो until mask is allocated */
	अगर (hw->mac.dglort_map == FM10K_DGLORTMAP_NONE)
		वापस;

	/* we support 3 possible GLORT configurations.
	 * 1: VFs consume all but the last 1
	 * 2: VFs and PF split glorts with possible gap between
	 * 3: VFs allocated first 64, all others beदीर्घ to PF
	 */
	अगर (mask <= hw->iov.total_vfs) अणु
		पूर्णांकerface->glort_count = 1;
		पूर्णांकerface->glort += mask;
	पूर्ण अन्यथा अगर (mask < 64) अणु
		पूर्णांकerface->glort_count = (mask + 1) / 2;
		पूर्णांकerface->glort += पूर्णांकerface->glort_count;
	पूर्ण अन्यथा अणु
		पूर्णांकerface->glort_count = mask - 63;
		पूर्णांकerface->glort += 64;
	पूर्ण
पूर्ण

/**
 * fm10k_restore_udp_port_info
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * This function restores the value in the tunnel_cfg रेजिस्टर(s) after reset
 **/
अटल व्योम fm10k_restore_udp_port_info(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	/* only the PF supports configuring tunnels */
	अगर (hw->mac.type != fm10k_mac_pf)
		वापस;

	/* restore tunnel configuration रेजिस्टर */
	fm10k_ग_लिखो_reg(hw, FM10K_TUNNEL_CFG,
			ntohs(पूर्णांकerface->vxlan_port) |
			(ETH_P_TEB << FM10K_TUNNEL_CFG_NVGRE_SHIFT));

	/* restore Geneve tunnel configuration रेजिस्टर */
	fm10k_ग_लिखो_reg(hw, FM10K_TUNNEL_CFG_GENEVE,
			ntohs(पूर्णांकerface->geneve_port));
पूर्ण

/**
 * fm10k_udp_tunnel_sync - Called when UDP tunnel ports change
 * @dev: network पूर्णांकerface device काष्ठाure
 * @table: Tunnel table (according to tables of @fm10k_udp_tunnels)
 *
 * This function is called when a new UDP tunnel port is added or deleted.
 * Due to hardware restrictions, only one port per type can be offloaded at
 * once. Core will send to the driver a port of its choice.
 **/
अटल पूर्णांक fm10k_udp_tunnel_sync(काष्ठा net_device *dev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा udp_tunnel_info ti;

	udp_tunnel_nic_get_port(dev, table, 0, &ti);
	अगर (!table)
		पूर्णांकerface->vxlan_port = ti.port;
	अन्यथा
		पूर्णांकerface->geneve_port = ti.port;

	fm10k_restore_udp_port_info(पूर्णांकerface);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info fm10k_udp_tunnels = अणु
	.sync_table	= fm10k_udp_tunnel_sync,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN,  पूर्ण,
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_GENEVE, पूर्ण,
	पूर्ण,
पूर्ण;

/**
 * fm10k_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
पूर्णांक fm10k_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	पूर्णांक err;

	/* allocate transmit descriptors */
	err = fm10k_setup_all_tx_resources(पूर्णांकerface);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = fm10k_setup_all_rx_resources(पूर्णांकerface);
	अगर (err)
		जाओ err_setup_rx;

	/* allocate पूर्णांकerrupt resources */
	err = fm10k_qv_request_irq(पूर्णांकerface);
	अगर (err)
		जाओ err_req_irq;

	/* setup GLORT assignment क्रम this port */
	fm10k_request_glort_range(पूर्णांकerface);

	/* Notअगरy the stack of the actual queue counts */
	err = netअगर_set_real_num_tx_queues(netdev,
					   पूर्णांकerface->num_tx_queues);
	अगर (err)
		जाओ err_set_queues;

	err = netअगर_set_real_num_rx_queues(netdev,
					   पूर्णांकerface->num_rx_queues);
	अगर (err)
		जाओ err_set_queues;

	fm10k_up(पूर्णांकerface);

	वापस 0;

err_set_queues:
	fm10k_qv_मुक्त_irq(पूर्णांकerface);
err_req_irq:
	fm10k_मुक्त_all_rx_resources(पूर्णांकerface);
err_setup_rx:
	fm10k_मुक्त_all_tx_resources(पूर्णांकerface);
err_setup_tx:
	वापस err;
पूर्ण

/**
 * fm10k_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 **/
पूर्णांक fm10k_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);

	fm10k_करोwn(पूर्णांकerface);

	fm10k_qv_मुक्त_irq(पूर्णांकerface);

	fm10k_मुक्त_all_tx_resources(पूर्णांकerface);
	fm10k_मुक्त_all_rx_resources(पूर्णांकerface);

	वापस 0;
पूर्ण

अटल netdev_tx_t fm10k_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	पूर्णांक num_tx_queues = READ_ONCE(पूर्णांकerface->num_tx_queues);
	अचिन्हित पूर्णांक r_idx = skb->queue_mapping;
	पूर्णांक err;

	अगर (!num_tx_queues)
		वापस NETDEV_TX_BUSY;

	अगर ((skb->protocol == htons(ETH_P_8021Q)) &&
	    !skb_vlan_tag_present(skb)) अणु
		/* FM10K only supports hardware tagging, any tags in frame
		 * are considered 2nd level or "outer" tags
		 */
		काष्ठा vlan_hdr *vhdr;
		__be16 proto;

		/* make sure skb is not shared */
		skb = skb_share_check(skb, GFP_ATOMIC);
		अगर (!skb)
			वापस NETDEV_TX_OK;

		/* make sure there is enough room to move the ethernet header */
		अगर (unlikely(!pskb_may_pull(skb, VLAN_ETH_HLEN)))
			वापस NETDEV_TX_OK;

		/* verअगरy the skb head is not shared */
		err = skb_cow_head(skb, 0);
		अगर (err) अणु
			dev_kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण

		/* locate VLAN header */
		vhdr = (काष्ठा vlan_hdr *)(skb->data + ETH_HLEN);

		/* pull the 2 key pieces of data out of it */
		__vlan_hwaccel_put_tag(skb,
				       htons(ETH_P_8021Q),
				       ntohs(vhdr->h_vlan_TCI));
		proto = vhdr->h_vlan_encapsulated_proto;
		skb->protocol = (ntohs(proto) >= 1536) ? proto :
							 htons(ETH_P_802_2);

		/* squash it by moving the ethernet addresses up 4 bytes */
		स_हटाओ(skb->data + VLAN_HLEN, skb->data, 12);
		__skb_pull(skb, VLAN_HLEN);
		skb_reset_mac_header(skb);
	पूर्ण

	/* The minimum packet size क्रम a single buffer is 17B so pad the skb
	 * in order to meet this minimum size requirement.
	 */
	अगर (unlikely(skb->len < 17)) अणु
		पूर्णांक pad_len = 17 - skb->len;

		अगर (skb_pad(skb, pad_len))
			वापस NETDEV_TX_OK;
		__skb_put(skb, pad_len);
	पूर्ण

	अगर (r_idx >= num_tx_queues)
		r_idx %= num_tx_queues;

	err = fm10k_xmit_frame_ring(skb, पूर्णांकerface->tx_ring[r_idx]);

	वापस err;
पूर्ण

/**
 * fm10k_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: the index of the Tx queue that समयd out
 **/
अटल व्योम fm10k_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_ring *tx_ring;
	bool real_tx_hang = false;

	अगर (txqueue >= पूर्णांकerface->num_tx_queues) अणु
		WARN(1, "invalid Tx queue index %d", txqueue);
		वापस;
	पूर्ण

	tx_ring = पूर्णांकerface->tx_ring[txqueue];
	अगर (check_क्रम_tx_hang(tx_ring) && fm10k_check_tx_hang(tx_ring))
		real_tx_hang = true;

#घोषणा TX_TIMEO_LIMIT 16000
	अगर (real_tx_hang) अणु
		fm10k_tx_समयout_reset(पूर्णांकerface);
	पूर्ण अन्यथा अणु
		netअगर_info(पूर्णांकerface, drv, netdev,
			   "Fake Tx hang detected with timeout of %d seconds\n",
			   netdev->watchकरोg_समयo / HZ);

		/* fake Tx hang - increase the kernel समयout */
		अगर (netdev->watchकरोg_समयo < TX_TIMEO_LIMIT)
			netdev->watchकरोg_समयo *= 2;
	पूर्ण
पूर्ण

/**
 * fm10k_host_mbx_पढ़ोy - Check PF पूर्णांकerface's mailbox पढ़ोiness
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * This function checks अगर the PF पूर्णांकerface's mailbox is पढ़ोy beक्रमe queueing
 * mailbox messages क्रम transmission. This will prevent filling the TX mailbox
 * queue when the receiver is not पढ़ोy. VF पूर्णांकerfaces are exempt from this
 * check since it will block all PF-VF mailbox messages from being sent from
 * the VF to the PF at initialization.
 **/
अटल bool fm10k_host_mbx_पढ़ोy(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	वापस (hw->mac.type == fm10k_mac_vf || पूर्णांकerface->host_पढ़ोy);
पूर्ण

/**
 * fm10k_queue_vlan_request - Queue a VLAN update request
 * @पूर्णांकerface: the fm10k पूर्णांकerface काष्ठाure
 * @vid: the VLAN vid
 * @vsi: VSI index number
 * @set: whether to set or clear
 *
 * This function queues up a VLAN update. For VFs, this must be sent to the
 * managing PF over the mailbox. For PFs, we'll use the same handling so that
 * it's similar to the VF. This aव्योमs storming the PF<->VF mailbox with too
 * many VLAN updates during reset.
 */
पूर्णांक fm10k_queue_vlan_request(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
			     u32 vid, u8 vsi, bool set)
अणु
	काष्ठा fm10k_macvlan_request *request;
	अचिन्हित दीर्घ flags;

	/* This must be atomic since we may be called जबतक the netdev
	 * addr_list_lock is held
	 */
	request = kzalloc(माप(*request), GFP_ATOMIC);
	अगर (!request)
		वापस -ENOMEM;

	request->type = FM10K_VLAN_REQUEST;
	request->vlan.vid = vid;
	request->vlan.vsi = vsi;
	request->set = set;

	spin_lock_irqsave(&पूर्णांकerface->macvlan_lock, flags);
	list_add_tail(&request->list, &पूर्णांकerface->macvlan_requests);
	spin_unlock_irqrestore(&पूर्णांकerface->macvlan_lock, flags);

	fm10k_macvlan_schedule(पूर्णांकerface);

	वापस 0;
पूर्ण

/**
 * fm10k_queue_mac_request - Queue a MAC update request
 * @पूर्णांकerface: the fm10k पूर्णांकerface काष्ठाure
 * @glort: the target glort क्रम this update
 * @addr: the address to update
 * @vid: the vid to update
 * @set: whether to add or हटाओ
 *
 * This function queues up a MAC request क्रम sending to the चयन manager.
 * A separate thपढ़ो monitors the queue and sends updates to the चयन
 * manager. Return 0 on success, and negative error code on failure.
 **/
पूर्णांक fm10k_queue_mac_request(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u16 glort,
			    स्थिर अचिन्हित अक्षर *addr, u16 vid, bool set)
अणु
	काष्ठा fm10k_macvlan_request *request;
	अचिन्हित दीर्घ flags;

	/* This must be atomic since we may be called जबतक the netdev
	 * addr_list_lock is held
	 */
	request = kzalloc(माप(*request), GFP_ATOMIC);
	अगर (!request)
		वापस -ENOMEM;

	अगर (is_multicast_ether_addr(addr))
		request->type = FM10K_MC_MAC_REQUEST;
	अन्यथा
		request->type = FM10K_UC_MAC_REQUEST;

	ether_addr_copy(request->mac.addr, addr);
	request->mac.glort = glort;
	request->mac.vid = vid;
	request->set = set;

	spin_lock_irqsave(&पूर्णांकerface->macvlan_lock, flags);
	list_add_tail(&request->list, &पूर्णांकerface->macvlan_requests);
	spin_unlock_irqrestore(&पूर्णांकerface->macvlan_lock, flags);

	fm10k_macvlan_schedule(पूर्णांकerface);

	वापस 0;
पूर्ण

/**
 * fm10k_clear_macvlan_queue - Cancel pending updates क्रम a given glort
 * @पूर्णांकerface: the fm10k पूर्णांकerface काष्ठाure
 * @glort: the target glort to clear
 * @vlans: true to clear VLAN messages, false to ignore them
 *
 * Cancel any outstanding MAC/VLAN requests क्रम a given glort. This is
 * expected to be called when a logical port goes करोwn.
 **/
व्योम fm10k_clear_macvlan_queue(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
			       u16 glort, bool vlans)

अणु
	काष्ठा fm10k_macvlan_request *r, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पूर्णांकerface->macvlan_lock, flags);

	/* Free any outstanding MAC/VLAN requests क्रम this पूर्णांकerface */
	list_क्रम_each_entry_safe(r, पंचांगp, &पूर्णांकerface->macvlan_requests, list) अणु
		चयन (r->type) अणु
		हाल FM10K_MC_MAC_REQUEST:
		हाल FM10K_UC_MAC_REQUEST:
			/* Don't मुक्त requests क्रम other पूर्णांकerfaces */
			अगर (r->mac.glort != glort)
				अवरोध;
			fallthrough;
		हाल FM10K_VLAN_REQUEST:
			अगर (vlans) अणु
				list_del(&r->list);
				kमुक्त(r);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&पूर्णांकerface->macvlan_lock, flags);
पूर्ण

अटल पूर्णांक fm10k_uc_vlan_unsync(काष्ठा net_device *netdev,
				स्थिर अचिन्हित अक्षर *uc_addr)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	u16 glort = पूर्णांकerface->glort;
	u16 vid = पूर्णांकerface->vid;
	bool set = !!(vid / VLAN_N_VID);
	पूर्णांक err;

	/* drop any leading bits on the VLAN ID */
	vid &= VLAN_N_VID - 1;

	err = fm10k_queue_mac_request(पूर्णांकerface, glort, uc_addr, vid, set);
	अगर (err)
		वापस err;

	/* वापस non-zero value as we are only करोing a partial sync/unsync */
	वापस 1;
पूर्ण

अटल पूर्णांक fm10k_mc_vlan_unsync(काष्ठा net_device *netdev,
				स्थिर अचिन्हित अक्षर *mc_addr)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	u16 glort = पूर्णांकerface->glort;
	u16 vid = पूर्णांकerface->vid;
	bool set = !!(vid / VLAN_N_VID);
	पूर्णांक err;

	/* drop any leading bits on the VLAN ID */
	vid &= VLAN_N_VID - 1;

	err = fm10k_queue_mac_request(पूर्णांकerface, glort, mc_addr, vid, set);
	अगर (err)
		वापस err;

	/* वापस non-zero value as we are only करोing a partial sync/unsync */
	वापस 1;
पूर्ण

अटल पूर्णांक fm10k_update_vid(काष्ठा net_device *netdev, u16 vid, bool set)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_l2_accel *l2_accel = पूर्णांकerface->l2_accel;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u16 glort;
	s32 err;
	पूर्णांक i;

	/* updates करो not apply to VLAN 0 */
	अगर (!vid)
		वापस 0;

	अगर (vid >= VLAN_N_VID)
		वापस -EINVAL;

	/* Verअगरy that we have permission to add VLANs. If this is a request
	 * to हटाओ a VLAN, we still want to allow the user to हटाओ the
	 * VLAN device. In that हाल, we need to clear the bit in the
	 * active_vlans biपंचांगask.
	 */
	अगर (set && hw->mac.vlan_override)
		वापस -EACCES;

	/* update active_vlans biपंचांगask */
	set_bit(vid, पूर्णांकerface->active_vlans);
	अगर (!set)
		clear_bit(vid, पूर्णांकerface->active_vlans);

	/* disable the शेष VLAN ID on ring अगर we have an active VLAN */
	क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++) अणु
		काष्ठा fm10k_ring *rx_ring = पूर्णांकerface->rx_ring[i];
		u16 rx_vid = rx_ring->vid & (VLAN_N_VID - 1);

		अगर (test_bit(rx_vid, पूर्णांकerface->active_vlans))
			rx_ring->vid |= FM10K_VLAN_CLEAR;
		अन्यथा
			rx_ring->vid &= ~FM10K_VLAN_CLEAR;
	पूर्ण

	/* If our VLAN has been overridden, there is no reason to send VLAN
	 * removal requests as they will be silently ignored.
	 */
	अगर (hw->mac.vlan_override)
		वापस 0;

	/* Do not हटाओ शेष VLAN ID related entries from VLAN and MAC
	 * tables
	 */
	अगर (!set && vid == hw->mac.शेष_vid)
		वापस 0;

	/* Do not throw an error अगर the पूर्णांकerface is करोwn. We will sync once
	 * we come up
	 */
	अगर (test_bit(__FM10K_DOWN, पूर्णांकerface->state))
		वापस 0;

	fm10k_mbx_lock(पूर्णांकerface);

	/* only need to update the VLAN अगर not in promiscuous mode */
	अगर (!(netdev->flags & IFF_PROMISC)) अणु
		err = fm10k_queue_vlan_request(पूर्णांकerface, vid, 0, set);
		अगर (err)
			जाओ err_out;
	पूर्ण

	/* Update our base MAC address */
	err = fm10k_queue_mac_request(पूर्णांकerface, पूर्णांकerface->glort,
				      hw->mac.addr, vid, set);
	अगर (err)
		जाओ err_out;

	/* Update L2 accelerated macvlan addresses */
	अगर (l2_accel) अणु
		क्रम (i = 0; i < l2_accel->size; i++) अणु
			काष्ठा net_device *sdev = l2_accel->macvlan[i];

			अगर (!sdev)
				जारी;

			glort = l2_accel->dglort + 1 + i;

			fm10k_queue_mac_request(पूर्णांकerface, glort,
						sdev->dev_addr,
						vid, set);
		पूर्ण
	पूर्ण

	/* set VLAN ID prior to syncing/unsyncing the VLAN */
	पूर्णांकerface->vid = vid + (set ? VLAN_N_VID : 0);

	/* Update the unicast and multicast address list to add/drop VLAN */
	__dev_uc_unsync(netdev, fm10k_uc_vlan_unsync);
	__dev_mc_unsync(netdev, fm10k_mc_vlan_unsync);

err_out:
	fm10k_mbx_unlock(पूर्णांकerface);

	वापस err;
पूर्ण

अटल पूर्णांक fm10k_vlan_rx_add_vid(काष्ठा net_device *netdev,
				 __always_unused __be16 proto, u16 vid)
अणु
	/* update VLAN and address table based on changes */
	वापस fm10k_update_vid(netdev, vid, true);
पूर्ण

अटल पूर्णांक fm10k_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				  __always_unused __be16 proto, u16 vid)
अणु
	/* update VLAN and address table based on changes */
	वापस fm10k_update_vid(netdev, vid, false);
पूर्ण

अटल u16 fm10k_find_next_vlan(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u16 vid)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u16 शेष_vid = hw->mac.शेष_vid;
	u16 vid_limit = vid < शेष_vid ? शेष_vid : VLAN_N_VID;

	vid = find_next_bit(पूर्णांकerface->active_vlans, vid_limit, ++vid);

	वापस vid;
पूर्ण

अटल व्योम fm10k_clear_unused_vlans(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	u32 vid, prev_vid;

	/* loop through and find any gaps in the table */
	क्रम (vid = 0, prev_vid = 0;
	     prev_vid < VLAN_N_VID;
	     prev_vid = vid + 1, vid = fm10k_find_next_vlan(पूर्णांकerface, vid)) अणु
		अगर (prev_vid == vid)
			जारी;

		/* send request to clear multiple bits at a समय */
		prev_vid += (vid - prev_vid - 1) << FM10K_VLAN_LENGTH_SHIFT;
		fm10k_queue_vlan_request(पूर्णांकerface, prev_vid, 0, false);
	पूर्ण
पूर्ण

अटल पूर्णांक __fm10k_uc_sync(काष्ठा net_device *dev,
			   स्थिर अचिन्हित अक्षर *addr, bool sync)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	u16 vid, glort = पूर्णांकerface->glort;
	s32 err;

	अगर (!is_valid_ether_addr(addr))
		वापस -EADDRNOTAVAIL;

	क्रम (vid = fm10k_find_next_vlan(पूर्णांकerface, 0);
	     vid < VLAN_N_VID;
	     vid = fm10k_find_next_vlan(पूर्णांकerface, vid)) अणु
		err = fm10k_queue_mac_request(पूर्णांकerface, glort,
					      addr, vid, sync);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_uc_sync(काष्ठा net_device *dev,
			 स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस __fm10k_uc_sync(dev, addr, true);
पूर्ण

अटल पूर्णांक fm10k_uc_unsync(काष्ठा net_device *dev,
			   स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस __fm10k_uc_sync(dev, addr, false);
पूर्ण

अटल पूर्णांक fm10k_set_mac(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा sockaddr *addr = p;
	s32 err = 0;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (dev->flags & IFF_UP) अणु
		/* setting MAC address requires mailbox */
		fm10k_mbx_lock(पूर्णांकerface);

		err = fm10k_uc_sync(dev, addr->sa_data);
		अगर (!err)
			fm10k_uc_unsync(dev, hw->mac.addr);

		fm10k_mbx_unlock(पूर्णांकerface);
	पूर्ण

	अगर (!err) अणु
		ether_addr_copy(dev->dev_addr, addr->sa_data);
		ether_addr_copy(hw->mac.addr, addr->sa_data);
		dev->addr_assign_type &= ~NET_ADDR_RANDOM;
	पूर्ण

	/* अगर we had a mailbox error suggest trying again */
	वापस err ? -EAGAIN : 0;
पूर्ण

अटल पूर्णांक __fm10k_mc_sync(काष्ठा net_device *dev,
			   स्थिर अचिन्हित अक्षर *addr, bool sync)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	u16 vid, glort = पूर्णांकerface->glort;
	s32 err;

	अगर (!is_multicast_ether_addr(addr))
		वापस -EADDRNOTAVAIL;

	क्रम (vid = fm10k_find_next_vlan(पूर्णांकerface, 0);
	     vid < VLAN_N_VID;
	     vid = fm10k_find_next_vlan(पूर्णांकerface, vid)) अणु
		err = fm10k_queue_mac_request(पूर्णांकerface, glort,
					      addr, vid, sync);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fm10k_mc_sync(काष्ठा net_device *dev,
			 स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस __fm10k_mc_sync(dev, addr, true);
पूर्ण

अटल पूर्णांक fm10k_mc_unsync(काष्ठा net_device *dev,
			   स्थिर अचिन्हित अक्षर *addr)
अणु
	वापस __fm10k_mc_sync(dev, addr, false);
पूर्ण

अटल व्योम fm10k_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक xcast_mode;

	/* no need to update the harwdare अगर we are not running */
	अगर (!(dev->flags & IFF_UP))
		वापस;

	/* determine new mode based on flags */
	xcast_mode = (dev->flags & IFF_PROMISC) ? FM10K_XCAST_MODE_PROMISC :
		     (dev->flags & IFF_ALLMULTI) ? FM10K_XCAST_MODE_ALLMULTI :
		     (dev->flags & (IFF_BROADCAST | IFF_MULTICAST)) ?
		     FM10K_XCAST_MODE_MULTI : FM10K_XCAST_MODE_NONE;

	fm10k_mbx_lock(पूर्णांकerface);

	/* update xcast mode first, but only अगर it changed */
	अगर (पूर्णांकerface->xcast_mode != xcast_mode) अणु
		/* update VLAN table when entering promiscuous mode */
		अगर (xcast_mode == FM10K_XCAST_MODE_PROMISC)
			fm10k_queue_vlan_request(पूर्णांकerface, FM10K_VLAN_ALL,
						 0, true);

		/* clear VLAN table when निकासing promiscuous mode */
		अगर (पूर्णांकerface->xcast_mode == FM10K_XCAST_MODE_PROMISC)
			fm10k_clear_unused_vlans(पूर्णांकerface);

		/* update xcast mode अगर host's mailbox is पढ़ोy */
		अगर (fm10k_host_mbx_पढ़ोy(पूर्णांकerface))
			hw->mac.ops.update_xcast_mode(hw, पूर्णांकerface->glort,
						      xcast_mode);

		/* record updated xcast mode state */
		पूर्णांकerface->xcast_mode = xcast_mode;
	पूर्ण

	/* synchronize all of the addresses */
	__dev_uc_sync(dev, fm10k_uc_sync, fm10k_uc_unsync);
	__dev_mc_sync(dev, fm10k_mc_sync, fm10k_mc_unsync);

	fm10k_mbx_unlock(पूर्णांकerface);
पूर्ण

व्योम fm10k_restore_rx_state(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_l2_accel *l2_accel = पूर्णांकerface->l2_accel;
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक xcast_mode, i;
	u16 vid, glort;

	/* record glort क्रम this पूर्णांकerface */
	glort = पूर्णांकerface->glort;

	/* convert पूर्णांकerface flags to xcast mode */
	अगर (netdev->flags & IFF_PROMISC)
		xcast_mode = FM10K_XCAST_MODE_PROMISC;
	अन्यथा अगर (netdev->flags & IFF_ALLMULTI)
		xcast_mode = FM10K_XCAST_MODE_ALLMULTI;
	अन्यथा अगर (netdev->flags & (IFF_BROADCAST | IFF_MULTICAST))
		xcast_mode = FM10K_XCAST_MODE_MULTI;
	अन्यथा
		xcast_mode = FM10K_XCAST_MODE_NONE;

	fm10k_mbx_lock(पूर्णांकerface);

	/* Enable logical port अगर host's mailbox is पढ़ोy */
	अगर (fm10k_host_mbx_पढ़ोy(पूर्णांकerface))
		hw->mac.ops.update_lport_state(hw, glort,
					       पूर्णांकerface->glort_count, true);

	/* update VLAN table */
	fm10k_queue_vlan_request(पूर्णांकerface, FM10K_VLAN_ALL, 0,
				 xcast_mode == FM10K_XCAST_MODE_PROMISC);

	/* update table with current entries */
	क्रम (vid = fm10k_find_next_vlan(पूर्णांकerface, 0);
	     vid < VLAN_N_VID;
	     vid = fm10k_find_next_vlan(पूर्णांकerface, vid)) अणु
		fm10k_queue_vlan_request(पूर्णांकerface, vid, 0, true);

		fm10k_queue_mac_request(पूर्णांकerface, glort,
					hw->mac.addr, vid, true);

		/* synchronize macvlan addresses */
		अगर (l2_accel) अणु
			क्रम (i = 0; i < l2_accel->size; i++) अणु
				काष्ठा net_device *sdev = l2_accel->macvlan[i];

				अगर (!sdev)
					जारी;

				glort = l2_accel->dglort + 1 + i;

				fm10k_queue_mac_request(पूर्णांकerface, glort,
							sdev->dev_addr,
							vid, true);
			पूर्ण
		पूर्ण
	पूर्ण

	/* update xcast mode beक्रमe synchronizing addresses अगर host's mailbox
	 * is पढ़ोy
	 */
	अगर (fm10k_host_mbx_पढ़ोy(पूर्णांकerface))
		hw->mac.ops.update_xcast_mode(hw, glort, xcast_mode);

	/* synchronize all of the addresses */
	__dev_uc_sync(netdev, fm10k_uc_sync, fm10k_uc_unsync);
	__dev_mc_sync(netdev, fm10k_mc_sync, fm10k_mc_unsync);

	/* synchronize macvlan addresses */
	अगर (l2_accel) अणु
		क्रम (i = 0; i < l2_accel->size; i++) अणु
			काष्ठा net_device *sdev = l2_accel->macvlan[i];

			अगर (!sdev)
				जारी;

			glort = l2_accel->dglort + 1 + i;

			hw->mac.ops.update_xcast_mode(hw, glort,
						      FM10K_XCAST_MODE_NONE);
			fm10k_queue_mac_request(पूर्णांकerface, glort,
						sdev->dev_addr,
						hw->mac.शेष_vid, true);
		पूर्ण
	पूर्ण

	fm10k_mbx_unlock(पूर्णांकerface);

	/* record updated xcast mode state */
	पूर्णांकerface->xcast_mode = xcast_mode;

	/* Restore tunnel configuration */
	fm10k_restore_udp_port_info(पूर्णांकerface);
पूर्ण

व्योम fm10k_reset_rx_state(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	/* Wait क्रम MAC/VLAN work to finish */
	जबतक (test_bit(__FM10K_MACVLAN_SCHED, पूर्णांकerface->state))
		usleep_range(1000, 2000);

	/* Cancel pending MAC/VLAN requests */
	fm10k_clear_macvlan_queue(पूर्णांकerface, पूर्णांकerface->glort, true);

	fm10k_mbx_lock(पूर्णांकerface);

	/* clear the logical port state on lower device अगर host's mailbox is
	 * पढ़ोy
	 */
	अगर (fm10k_host_mbx_पढ़ोy(पूर्णांकerface))
		hw->mac.ops.update_lport_state(hw, पूर्णांकerface->glort,
					       पूर्णांकerface->glort_count, false);

	fm10k_mbx_unlock(पूर्णांकerface);

	/* reset flags to शेष state */
	पूर्णांकerface->xcast_mode = FM10K_XCAST_MODE_NONE;

	/* clear the sync flag since the lport has been dropped */
	__dev_uc_unsync(netdev, शून्य);
	__dev_mc_unsync(netdev, शून्य);
पूर्ण

/**
 * fm10k_get_stats64 - Get System Network Statistics
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @stats: storage space क्रम 64bit statistics
 *
 * Obtain 64bit statistics in a way that is safe क्रम both 32bit and 64bit
 * architectures.
 */
अटल व्योम fm10k_get_stats64(काष्ठा net_device *netdev,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(netdev);
	काष्ठा fm10k_ring *ring;
	अचिन्हित पूर्णांक start, i;
	u64 bytes, packets;

	rcu_पढ़ो_lock();

	क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++) अणु
		ring = READ_ONCE(पूर्णांकerface->rx_ring[i]);

		अगर (!ring)
			जारी;

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			packets = ring->stats.packets;
			bytes   = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));

		stats->rx_packets += packets;
		stats->rx_bytes   += bytes;
	पूर्ण

	क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++) अणु
		ring = READ_ONCE(पूर्णांकerface->tx_ring[i]);

		अगर (!ring)
			जारी;

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			packets = ring->stats.packets;
			bytes   = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));

		stats->tx_packets += packets;
		stats->tx_bytes   += bytes;
	पूर्ण

	rcu_पढ़ो_unlock();

	/* following stats updated by fm10k_service_task() */
	stats->rx_missed_errors	= netdev->stats.rx_missed_errors;
पूर्ण

पूर्णांक fm10k_setup_tc(काष्ठा net_device *dev, u8 tc)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	पूर्णांक err;

	/* Currently only the PF supports priority classes */
	अगर (tc && (पूर्णांकerface->hw.mac.type != fm10k_mac_pf))
		वापस -EINVAL;

	/* Hardware supports up to 8 traffic classes */
	अगर (tc > 8)
		वापस -EINVAL;

	/* Hardware has to reinitialize queues to match packet
	 * buffer alignment. Unक्रमtunately, the hardware is not
	 * flexible enough to करो this dynamically.
	 */
	अगर (netअगर_running(dev))
		fm10k_बंद(dev);

	fm10k_mbx_मुक्त_irq(पूर्णांकerface);

	fm10k_clear_queueing_scheme(पूर्णांकerface);

	/* we expect the prio_tc map to be repopulated later */
	netdev_reset_tc(dev);
	netdev_set_num_tc(dev, tc);

	err = fm10k_init_queueing_scheme(पूर्णांकerface);
	अगर (err)
		जाओ err_queueing_scheme;

	err = fm10k_mbx_request_irq(पूर्णांकerface);
	अगर (err)
		जाओ err_mbx_irq;

	err = netअगर_running(dev) ? fm10k_खोलो(dev) : 0;
	अगर (err)
		जाओ err_खोलो;

	/* flag to indicate SWPRI has yet to be updated */
	set_bit(FM10K_FLAG_SWPRI_CONFIG, पूर्णांकerface->flags);

	वापस 0;
err_खोलो:
	fm10k_mbx_मुक्त_irq(पूर्णांकerface);
err_mbx_irq:
	fm10k_clear_queueing_scheme(पूर्णांकerface);
err_queueing_scheme:
	netअगर_device_detach(dev);

	वापस err;
पूर्ण

अटल पूर्णांक __fm10k_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			    व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt *mqprio = type_data;

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

	वापस fm10k_setup_tc(dev, mqprio->num_tc);
पूर्ण

अटल व्योम fm10k_assign_l2_accel(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
				  काष्ठा fm10k_l2_accel *l2_accel)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++) अणु
		काष्ठा fm10k_ring *ring = पूर्णांकerface->rx_ring[i];

		rcu_assign_poपूर्णांकer(ring->l2_accel, l2_accel);
	पूर्ण

	पूर्णांकerface->l2_accel = l2_accel;
पूर्ण

अटल व्योम *fm10k_dfwd_add_station(काष्ठा net_device *dev,
				    काष्ठा net_device *sdev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा fm10k_l2_accel *l2_accel = पूर्णांकerface->l2_accel;
	काष्ठा fm10k_l2_accel *old_l2_accel = शून्य;
	काष्ठा fm10k_dglort_cfg dglort = अणु 0 पूर्ण;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक size, i;
	u16 vid, glort;

	/* The hardware supported by fm10k only filters on the destination MAC
	 * address. In order to aव्योम issues we only support offloading modes
	 * where the hardware can actually provide the functionality.
	 */
	अगर (!macvlan_supports_dest_filter(sdev))
		वापस ERR_PTR(-EMEDIUMTYPE);

	/* allocate l2 accel काष्ठाure अगर it is not available */
	अगर (!l2_accel) अणु
		/* verअगरy there is enough मुक्त GLORTs to support l2_accel */
		अगर (पूर्णांकerface->glort_count < 7)
			वापस ERR_PTR(-EBUSY);

		size = दुरत्व(काष्ठा fm10k_l2_accel, macvlan[7]);
		l2_accel = kzalloc(size, GFP_KERNEL);
		अगर (!l2_accel)
			वापस ERR_PTR(-ENOMEM);

		l2_accel->size = 7;
		l2_accel->dglort = पूर्णांकerface->glort;

		/* update poपूर्णांकers */
		fm10k_assign_l2_accel(पूर्णांकerface, l2_accel);
	/* करो not expand अगर we are at our limit */
	पूर्ण अन्यथा अगर ((l2_accel->count == FM10K_MAX_STATIONS) ||
		   (l2_accel->count == (पूर्णांकerface->glort_count - 1))) अणु
		वापस ERR_PTR(-EBUSY);
	/* expand अगर we have hit the size limit */
	पूर्ण अन्यथा अगर (l2_accel->count == l2_accel->size) अणु
		old_l2_accel = l2_accel;
		size = दुरत्व(काष्ठा fm10k_l2_accel,
				macvlan[(l2_accel->size * 2) + 1]);
		l2_accel = kzalloc(size, GFP_KERNEL);
		अगर (!l2_accel)
			वापस ERR_PTR(-ENOMEM);

		स_नकल(l2_accel, old_l2_accel,
		       दुरत्व(काष्ठा fm10k_l2_accel,
				macvlan[old_l2_accel->size]));

		l2_accel->size = (old_l2_accel->size * 2) + 1;

		/* update poपूर्णांकers */
		fm10k_assign_l2_accel(पूर्णांकerface, l2_accel);
		kमुक्त_rcu(old_l2_accel, rcu);
	पूर्ण

	/* add macvlan to accel table, and record GLORT क्रम position */
	क्रम (i = 0; i < l2_accel->size; i++) अणु
		अगर (!l2_accel->macvlan[i])
			अवरोध;
	पूर्ण

	/* record station */
	l2_accel->macvlan[i] = sdev;
	l2_accel->count++;

	/* configure शेष DGLORT mapping क्रम RSS/DCB */
	dglort.idx = fm10k_dglort_pf_rss;
	dglort.inner_rss = 1;
	dglort.rss_l = fls(पूर्णांकerface->ring_feature[RING_F_RSS].mask);
	dglort.pc_l = fls(पूर्णांकerface->ring_feature[RING_F_QOS].mask);
	dglort.glort = पूर्णांकerface->glort;
	dglort.shared_l = fls(l2_accel->size);
	hw->mac.ops.configure_dglort_map(hw, &dglort);

	/* Add rules क्रम this specअगरic dglort to the चयन */
	fm10k_mbx_lock(पूर्णांकerface);

	glort = l2_accel->dglort + 1 + i;

	अगर (fm10k_host_mbx_पढ़ोy(पूर्णांकerface))
		hw->mac.ops.update_xcast_mode(hw, glort,
					      FM10K_XCAST_MODE_NONE);

	fm10k_queue_mac_request(पूर्णांकerface, glort, sdev->dev_addr,
				hw->mac.शेष_vid, true);

	क्रम (vid = fm10k_find_next_vlan(पूर्णांकerface, 0);
	     vid < VLAN_N_VID;
	     vid = fm10k_find_next_vlan(पूर्णांकerface, vid))
		fm10k_queue_mac_request(पूर्णांकerface, glort, sdev->dev_addr,
					vid, true);

	fm10k_mbx_unlock(पूर्णांकerface);

	वापस sdev;
पूर्ण

अटल व्योम fm10k_dfwd_del_station(काष्ठा net_device *dev, व्योम *priv)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा fm10k_l2_accel *l2_accel = READ_ONCE(पूर्णांकerface->l2_accel);
	काष्ठा fm10k_dglort_cfg dglort = अणु 0 पूर्ण;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	काष्ठा net_device *sdev = priv;
	u16 vid, glort;
	पूर्णांक i;

	अगर (!l2_accel)
		वापस;

	/* search table क्रम matching पूर्णांकerface */
	क्रम (i = 0; i < l2_accel->size; i++) अणु
		अगर (l2_accel->macvlan[i] == sdev)
			अवरोध;
	पूर्ण

	/* निकास अगर macvlan not found */
	अगर (i == l2_accel->size)
		वापस;

	/* Remove any rules specअगरic to this dglort */
	fm10k_mbx_lock(पूर्णांकerface);

	glort = l2_accel->dglort + 1 + i;

	अगर (fm10k_host_mbx_पढ़ोy(पूर्णांकerface))
		hw->mac.ops.update_xcast_mode(hw, glort,
					      FM10K_XCAST_MODE_NONE);

	fm10k_queue_mac_request(पूर्णांकerface, glort, sdev->dev_addr,
				hw->mac.शेष_vid, false);

	क्रम (vid = fm10k_find_next_vlan(पूर्णांकerface, 0);
	     vid < VLAN_N_VID;
	     vid = fm10k_find_next_vlan(पूर्णांकerface, vid))
		fm10k_queue_mac_request(पूर्णांकerface, glort, sdev->dev_addr,
					vid, false);

	fm10k_mbx_unlock(पूर्णांकerface);

	/* record removal */
	l2_accel->macvlan[i] = शून्य;
	l2_accel->count--;

	/* configure शेष DGLORT mapping क्रम RSS/DCB */
	dglort.idx = fm10k_dglort_pf_rss;
	dglort.inner_rss = 1;
	dglort.rss_l = fls(पूर्णांकerface->ring_feature[RING_F_RSS].mask);
	dglort.pc_l = fls(पूर्णांकerface->ring_feature[RING_F_QOS].mask);
	dglort.glort = पूर्णांकerface->glort;
	dglort.shared_l = fls(l2_accel->size);
	hw->mac.ops.configure_dglort_map(hw, &dglort);

	/* If table is empty हटाओ it */
	अगर (l2_accel->count == 0) अणु
		fm10k_assign_l2_accel(पूर्णांकerface, शून्य);
		kमुक्त_rcu(l2_accel, rcu);
	पूर्ण
पूर्ण

अटल netdev_features_t fm10k_features_check(काष्ठा sk_buff *skb,
					      काष्ठा net_device *dev,
					      netdev_features_t features)
अणु
	अगर (!skb->encapsulation || fm10k_tx_encap_offload(skb))
		वापस features;

	वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
पूर्ण

अटल स्थिर काष्ठा net_device_ops fm10k_netdev_ops = अणु
	.nकरो_खोलो		= fm10k_खोलो,
	.nकरो_stop		= fm10k_बंद,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_start_xmit		= fm10k_xmit_frame,
	.nकरो_set_mac_address	= fm10k_set_mac,
	.nकरो_tx_समयout		= fm10k_tx_समयout,
	.nकरो_vlan_rx_add_vid	= fm10k_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= fm10k_vlan_rx_समाप्त_vid,
	.nकरो_set_rx_mode	= fm10k_set_rx_mode,
	.nकरो_get_stats64	= fm10k_get_stats64,
	.nकरो_setup_tc		= __fm10k_setup_tc,
	.nकरो_set_vf_mac		= fm10k_nकरो_set_vf_mac,
	.nकरो_set_vf_vlan	= fm10k_nकरो_set_vf_vlan,
	.nकरो_set_vf_rate	= fm10k_nकरो_set_vf_bw,
	.nकरो_get_vf_config	= fm10k_nकरो_get_vf_config,
	.nकरो_get_vf_stats	= fm10k_nकरो_get_vf_stats,
	.nकरो_dfwd_add_station	= fm10k_dfwd_add_station,
	.nकरो_dfwd_del_station	= fm10k_dfwd_del_station,
	.nकरो_features_check	= fm10k_features_check,
पूर्ण;

#घोषणा DEFAULT_DEBUG_LEVEL_SHIFT 3

काष्ठा net_device *fm10k_alloc_netdev(स्थिर काष्ठा fm10k_info *info)
अणु
	netdev_features_t hw_features;
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;
	काष्ठा net_device *dev;

	dev = alloc_etherdev_mq(माप(काष्ठा fm10k_पूर्णांकfc), MAX_QUEUES);
	अगर (!dev)
		वापस शून्य;

	/* set net device and ethtool ops */
	dev->netdev_ops = &fm10k_netdev_ops;
	fm10k_set_ethtool_ops(dev);

	/* configure शेष debug level */
	पूर्णांकerface = netdev_priv(dev);
	पूर्णांकerface->msg_enable = BIT(DEFAULT_DEBUG_LEVEL_SHIFT) - 1;

	/* configure शेष features */
	dev->features |= NETIF_F_IP_CSUM |
			 NETIF_F_IPV6_CSUM |
			 NETIF_F_SG |
			 NETIF_F_TSO |
			 NETIF_F_TSO6 |
			 NETIF_F_TSO_ECN |
			 NETIF_F_RXHASH |
			 NETIF_F_RXCSUM;

	/* Only the PF can support VXLAN and NVGRE tunnel offloads */
	अगर (info->mac == fm10k_mac_pf) अणु
		dev->hw_enc_features = NETIF_F_IP_CSUM |
				       NETIF_F_TSO |
				       NETIF_F_TSO6 |
				       NETIF_F_TSO_ECN |
				       NETIF_F_GSO_UDP_TUNNEL |
				       NETIF_F_IPV6_CSUM |
				       NETIF_F_SG;

		dev->features |= NETIF_F_GSO_UDP_TUNNEL;

		dev->udp_tunnel_nic_info = &fm10k_udp_tunnels;
	पूर्ण

	/* all features defined to this poपूर्णांक should be changeable */
	hw_features = dev->features;

	/* allow user to enable L2 क्रमwarding acceleration */
	hw_features |= NETIF_F_HW_L2FW_DOFFLOAD;

	/* configure VLAN features */
	dev->vlan_features |= dev->features;

	/* we want to leave these both on as we cannot disable VLAN tag
	 * insertion or stripping on the hardware since it is contained
	 * in the FTAG and not in the frame itself.
	 */
	dev->features |= NETIF_F_HW_VLAN_CTAG_TX |
			 NETIF_F_HW_VLAN_CTAG_RX |
			 NETIF_F_HW_VLAN_CTAG_FILTER;

	dev->priv_flags |= IFF_UNICAST_FLT;

	dev->hw_features |= hw_features;

	/* MTU range: 68 - 15342 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = FM10K_MAX_JUMBO_FRAME_SIZE;

	वापस dev;
पूर्ण
