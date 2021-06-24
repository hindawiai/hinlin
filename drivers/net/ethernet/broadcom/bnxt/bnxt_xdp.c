<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2016-2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/filter.h>
#समावेश <net/page_pool.h>
#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_xdp.h"

काष्ठा bnxt_sw_tx_bd *bnxt_xmit_bd(काष्ठा bnxt *bp,
				   काष्ठा bnxt_tx_ring_info *txr,
				   dma_addr_t mapping, u32 len)
अणु
	काष्ठा bnxt_sw_tx_bd *tx_buf;
	काष्ठा tx_bd *txbd;
	u32 flags;
	u16 prod;

	prod = txr->tx_prod;
	tx_buf = &txr->tx_buf_ring[prod];

	txbd = &txr->tx_desc_ring[TX_RING(prod)][TX_IDX(prod)];
	flags = (len << TX_BD_LEN_SHIFT) | (1 << TX_BD_FLAGS_BD_CNT_SHIFT) |
		TX_BD_FLAGS_PACKET_END | bnxt_lhपूर्णांक_arr[len >> 9];
	txbd->tx_bd_len_flags_type = cpu_to_le32(flags);
	txbd->tx_bd_opaque = prod;
	txbd->tx_bd_haddr = cpu_to_le64(mapping);

	prod = NEXT_TX(prod);
	txr->tx_prod = prod;
	वापस tx_buf;
पूर्ण

अटल व्योम __bnxt_xmit_xdp(काष्ठा bnxt *bp, काष्ठा bnxt_tx_ring_info *txr,
			    dma_addr_t mapping, u32 len, u16 rx_prod)
अणु
	काष्ठा bnxt_sw_tx_bd *tx_buf;

	tx_buf = bnxt_xmit_bd(bp, txr, mapping, len);
	tx_buf->rx_prod = rx_prod;
	tx_buf->action = XDP_TX;
पूर्ण

अटल व्योम __bnxt_xmit_xdp_redirect(काष्ठा bnxt *bp,
				     काष्ठा bnxt_tx_ring_info *txr,
				     dma_addr_t mapping, u32 len,
				     काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा bnxt_sw_tx_bd *tx_buf;

	tx_buf = bnxt_xmit_bd(bp, txr, mapping, len);
	tx_buf->action = XDP_REसूचीECT;
	tx_buf->xdpf = xdpf;
	dma_unmap_addr_set(tx_buf, mapping, mapping);
	dma_unmap_len_set(tx_buf, len, 0);
पूर्ण

व्योम bnxt_tx_पूर्णांक_xdp(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi, पूर्णांक nr_pkts)
अणु
	काष्ठा bnxt_tx_ring_info *txr = bnapi->tx_ring;
	काष्ठा bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	bool rx_करोorbell_needed = false;
	काष्ठा bnxt_sw_tx_bd *tx_buf;
	u16 tx_cons = txr->tx_cons;
	u16 last_tx_cons = tx_cons;
	पूर्णांक i;

	क्रम (i = 0; i < nr_pkts; i++) अणु
		tx_buf = &txr->tx_buf_ring[tx_cons];

		अगर (tx_buf->action == XDP_REसूचीECT) अणु
			काष्ठा pci_dev *pdev = bp->pdev;

			dma_unmap_single(&pdev->dev,
					 dma_unmap_addr(tx_buf, mapping),
					 dma_unmap_len(tx_buf, len),
					 PCI_DMA_TODEVICE);
			xdp_वापस_frame(tx_buf->xdpf);
			tx_buf->action = 0;
			tx_buf->xdpf = शून्य;
		पूर्ण अन्यथा अगर (tx_buf->action == XDP_TX) अणु
			rx_करोorbell_needed = true;
			last_tx_cons = tx_cons;
		पूर्ण
		tx_cons = NEXT_TX(tx_cons);
	पूर्ण
	txr->tx_cons = tx_cons;
	अगर (rx_करोorbell_needed) अणु
		tx_buf = &txr->tx_buf_ring[last_tx_cons];
		bnxt_db_ग_लिखो(bp, &rxr->rx_db, tx_buf->rx_prod);
	पूर्ण
पूर्ण

/* वापसs the following:
 * true    - packet consumed by XDP and new buffer is allocated.
 * false   - packet should be passed to the stack.
 */
bool bnxt_rx_xdp(काष्ठा bnxt *bp, काष्ठा bnxt_rx_ring_info *rxr, u16 cons,
		 काष्ठा page *page, u8 **data_ptr, अचिन्हित पूर्णांक *len, u8 *event)
अणु
	काष्ठा bpf_prog *xdp_prog = READ_ONCE(rxr->xdp_prog);
	काष्ठा bnxt_tx_ring_info *txr;
	काष्ठा bnxt_sw_rx_bd *rx_buf;
	काष्ठा pci_dev *pdev;
	काष्ठा xdp_buff xdp;
	dma_addr_t mapping;
	व्योम *orig_data;
	u32 tx_avail;
	u32 offset;
	u32 act;

	अगर (!xdp_prog)
		वापस false;

	pdev = bp->pdev;
	rx_buf = &rxr->rx_buf_ring[cons];
	offset = bp->rx_offset;

	mapping = rx_buf->mapping - bp->rx_dma_offset;
	dma_sync_single_क्रम_cpu(&pdev->dev, mapping + offset, *len, bp->rx_dir);

	txr = rxr->bnapi->tx_ring;
	/* BNXT_RX_PAGE_MODE(bp) when XDP enabled */
	xdp_init_buff(&xdp, PAGE_SIZE, &rxr->xdp_rxq);
	xdp_prepare_buff(&xdp, *data_ptr - offset, offset, *len, false);
	orig_data = xdp.data;

	rcu_पढ़ो_lock();
	act = bpf_prog_run_xdp(xdp_prog, &xdp);
	rcu_पढ़ो_unlock();

	tx_avail = bnxt_tx_avail(bp, txr);
	/* If the tx ring is not full, we must not update the rx producer yet
	 * because we may still be transmitting on some BDs.
	 */
	अगर (tx_avail != bp->tx_ring_size)
		*event &= ~BNXT_RX_EVENT;

	*len = xdp.data_end - xdp.data;
	अगर (orig_data != xdp.data) अणु
		offset = xdp.data - xdp.data_hard_start;
		*data_ptr = xdp.data_hard_start + offset;
	पूर्ण
	चयन (act) अणु
	हाल XDP_PASS:
		वापस false;

	हाल XDP_TX:
		अगर (tx_avail < 1) अणु
			trace_xdp_exception(bp->dev, xdp_prog, act);
			bnxt_reuse_rx_data(rxr, cons, page);
			वापस true;
		पूर्ण

		*event = BNXT_TX_EVENT;
		dma_sync_single_क्रम_device(&pdev->dev, mapping + offset, *len,
					   bp->rx_dir);
		__bnxt_xmit_xdp(bp, txr, mapping + offset, *len,
				NEXT_RX(rxr->rx_prod));
		bnxt_reuse_rx_data(rxr, cons, page);
		वापस true;
	हाल XDP_REसूचीECT:
		/* अगर we are calling this here then we know that the
		 * redirect is coming from a frame received by the
		 * bnxt_en driver.
		 */
		dma_unmap_page_attrs(&pdev->dev, mapping,
				     PAGE_SIZE, bp->rx_dir,
				     DMA_ATTR_WEAK_ORDERING);

		/* अगर we are unable to allocate a new buffer, पात and reuse */
		अगर (bnxt_alloc_rx_data(bp, rxr, rxr->rx_prod, GFP_ATOMIC)) अणु
			trace_xdp_exception(bp->dev, xdp_prog, act);
			bnxt_reuse_rx_data(rxr, cons, page);
			वापस true;
		पूर्ण

		अगर (xdp_करो_redirect(bp->dev, &xdp, xdp_prog)) अणु
			trace_xdp_exception(bp->dev, xdp_prog, act);
			page_pool_recycle_direct(rxr->page_pool, page);
			वापस true;
		पूर्ण

		*event |= BNXT_REसूचीECT_EVENT;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(bp->dev, xdp_prog, act);
		fallthrough;
	हाल XDP_DROP:
		bnxt_reuse_rx_data(rxr, cons, page);
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक bnxt_xdp_xmit(काष्ठा net_device *dev, पूर्णांक num_frames,
		  काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bpf_prog *xdp_prog = READ_ONCE(bp->xdp_prog);
	काष्ठा pci_dev *pdev = bp->pdev;
	काष्ठा bnxt_tx_ring_info *txr;
	dma_addr_t mapping;
	पूर्णांक nxmit = 0;
	पूर्णांक ring;
	पूर्णांक i;

	अगर (!test_bit(BNXT_STATE_OPEN, &bp->state) ||
	    !bp->tx_nr_rings_xdp ||
	    !xdp_prog)
		वापस -EINVAL;

	ring = smp_processor_id() % bp->tx_nr_rings_xdp;
	txr = &bp->tx_ring[ring];

	क्रम (i = 0; i < num_frames; i++) अणु
		काष्ठा xdp_frame *xdp = frames[i];

		अगर (!txr || !bnxt_tx_avail(bp, txr) ||
		    !(bp->bnapi[ring]->flags & BNXT_NAPI_FLAG_XDP))
			अवरोध;

		mapping = dma_map_single(&pdev->dev, xdp->data, xdp->len,
					 DMA_TO_DEVICE);

		अगर (dma_mapping_error(&pdev->dev, mapping))
			अवरोध;

		__bnxt_xmit_xdp_redirect(bp, txr, mapping, xdp->len, xdp);
		nxmit++;
	पूर्ण

	अगर (flags & XDP_XMIT_FLUSH) अणु
		/* Sync BD data beक्रमe updating करोorbell */
		wmb();
		bnxt_db_ग_लिखो(bp, &txr->tx_db, txr->tx_prod);
	पूर्ण

	वापस nxmit;
पूर्ण

/* Under rtnl_lock */
अटल पूर्णांक bnxt_xdp_set(काष्ठा bnxt *bp, काष्ठा bpf_prog *prog)
अणु
	काष्ठा net_device *dev = bp->dev;
	पूर्णांक tx_xdp = 0, rc, tc;
	काष्ठा bpf_prog *old;

	अगर (prog && bp->dev->mtu > BNXT_MAX_PAGE_MODE_MTU) अणु
		netdev_warn(dev, "MTU %d larger than largest XDP supported MTU %d.\n",
			    bp->dev->mtu, BNXT_MAX_PAGE_MODE_MTU);
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (!(bp->flags & BNXT_FLAG_SHARED_RINGS)) अणु
		netdev_warn(dev, "ethtool rx/tx channels must be combined to support XDP.\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (prog)
		tx_xdp = bp->rx_nr_rings;

	tc = netdev_get_num_tc(dev);
	अगर (!tc)
		tc = 1;
	rc = bnxt_check_rings(bp, bp->tx_nr_rings_per_tc, bp->rx_nr_rings,
			      true, tc, tx_xdp);
	अगर (rc) अणु
		netdev_warn(dev, "Unable to reserve enough TX rings to support XDP.\n");
		वापस rc;
	पूर्ण
	अगर (netअगर_running(dev))
		bnxt_बंद_nic(bp, true, false);

	old = xchg(&bp->xdp_prog, prog);
	अगर (old)
		bpf_prog_put(old);

	अगर (prog) अणु
		bnxt_set_rx_skb_mode(bp, true);
	पूर्ण अन्यथा अणु
		पूर्णांक rx, tx;

		bnxt_set_rx_skb_mode(bp, false);
		bnxt_get_max_rings(bp, &rx, &tx, true);
		अगर (rx > 1) अणु
			bp->flags &= ~BNXT_FLAG_NO_AGG_RINGS;
			bp->dev->hw_features |= NETIF_F_LRO;
		पूर्ण
	पूर्ण
	bp->tx_nr_rings_xdp = tx_xdp;
	bp->tx_nr_rings = bp->tx_nr_rings_per_tc * tc + tx_xdp;
	bp->cp_nr_rings = max_t(पूर्णांक, bp->tx_nr_rings, bp->rx_nr_rings);
	bnxt_set_tpa_flags(bp);
	bnxt_set_ring_params(bp);

	अगर (netअगर_running(dev))
		वापस bnxt_खोलो_nic(bp, true, false);

	वापस 0;
पूर्ण

पूर्णांक bnxt_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	पूर्णांक rc;

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		rc = bnxt_xdp_set(bp, xdp->prog);
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण
