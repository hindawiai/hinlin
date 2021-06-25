<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2020 NXP
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/of_net.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/msi.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/iommu.h>
#समावेश <linux/fsl/mc.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/fsl/ptp_qoriq.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/sock.h>

#समावेश "dpaa2-eth.h"

/* CREATE_TRACE_POINTS only needs to be defined once. Other dpa files
 * using trace events only need to #समावेश <trace/events/sched.h>
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "dpaa2-eth-trace.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Freescale Semiconductor, Inc");
MODULE_DESCRIPTION("Freescale DPAA2 Ethernet Driver");

काष्ठा ptp_qoriq *dpaa2_ptp;
EXPORT_SYMBOL(dpaa2_ptp);

अटल व्योम *dpaa2_iova_to_virt(काष्ठा iommu_करोमुख्य *करोमुख्य,
				dma_addr_t iova_addr)
अणु
	phys_addr_t phys_addr;

	phys_addr = करोमुख्य ? iommu_iova_to_phys(करोमुख्य, iova_addr) : iova_addr;

	वापस phys_to_virt(phys_addr);
पूर्ण

अटल व्योम dpaa2_eth_validate_rx_csum(काष्ठा dpaa2_eth_priv *priv,
				       u32 fd_status,
				       काष्ठा sk_buff *skb)
अणु
	skb_checksum_none_निश्चित(skb);

	/* HW checksum validation is disabled, nothing to करो here */
	अगर (!(priv->net_dev->features & NETIF_F_RXCSUM))
		वापस;

	/* Read checksum validation bits */
	अगर (!((fd_status & DPAA2_FAS_L3CV) &&
	      (fd_status & DPAA2_FAS_L4CV)))
		वापस;

	/* Inक्रमm the stack there's no need to compute L3/L4 csum anymore */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

/* Free a received FD.
 * Not to be used क्रम Tx conf FDs or on any other paths.
 */
अटल व्योम dpaa2_eth_मुक्त_rx_fd(काष्ठा dpaa2_eth_priv *priv,
				 स्थिर काष्ठा dpaa2_fd *fd,
				 व्योम *vaddr)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	dma_addr_t addr = dpaa2_fd_get_addr(fd);
	u8 fd_क्रमmat = dpaa2_fd_get_क्रमmat(fd);
	काष्ठा dpaa2_sg_entry *sgt;
	व्योम *sg_vaddr;
	पूर्णांक i;

	/* If single buffer frame, just मुक्त the data buffer */
	अगर (fd_क्रमmat == dpaa2_fd_single)
		जाओ मुक्त_buf;
	अन्यथा अगर (fd_क्रमmat != dpaa2_fd_sg)
		/* We करोn't support any other क्रमmat */
		वापस;

	/* For S/G frames, we first need to मुक्त all SG entries
	 * except the first one, which was taken care of alपढ़ोy
	 */
	sgt = vaddr + dpaa2_fd_get_offset(fd);
	क्रम (i = 1; i < DPAA2_ETH_MAX_SG_ENTRIES; i++) अणु
		addr = dpaa2_sg_get_addr(&sgt[i]);
		sg_vaddr = dpaa2_iova_to_virt(priv->iommu_करोमुख्य, addr);
		dma_unmap_page(dev, addr, priv->rx_buf_size,
			       DMA_BIसूचीECTIONAL);

		मुक्त_pages((अचिन्हित दीर्घ)sg_vaddr, 0);
		अगर (dpaa2_sg_is_final(&sgt[i]))
			अवरोध;
	पूर्ण

मुक्त_buf:
	मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
पूर्ण

/* Build a linear skb based on a single-buffer frame descriptor */
अटल काष्ठा sk_buff *dpaa2_eth_build_linear_skb(काष्ठा dpaa2_eth_channel *ch,
						  स्थिर काष्ठा dpaa2_fd *fd,
						  व्योम *fd_vaddr)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u16 fd_offset = dpaa2_fd_get_offset(fd);
	u32 fd_length = dpaa2_fd_get_len(fd);

	ch->buf_count--;

	skb = build_skb(fd_vaddr, DPAA2_ETH_RX_BUF_RAW_SIZE);
	अगर (unlikely(!skb))
		वापस शून्य;

	skb_reserve(skb, fd_offset);
	skb_put(skb, fd_length);

	वापस skb;
पूर्ण

/* Build a non linear (fragmented) skb based on a S/G table */
अटल काष्ठा sk_buff *dpaa2_eth_build_frag_skb(काष्ठा dpaa2_eth_priv *priv,
						काष्ठा dpaa2_eth_channel *ch,
						काष्ठा dpaa2_sg_entry *sgt)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा device *dev = priv->net_dev->dev.parent;
	व्योम *sg_vaddr;
	dma_addr_t sg_addr;
	u16 sg_offset;
	u32 sg_length;
	काष्ठा page *page, *head_page;
	पूर्णांक page_offset;
	पूर्णांक i;

	क्रम (i = 0; i < DPAA2_ETH_MAX_SG_ENTRIES; i++) अणु
		काष्ठा dpaa2_sg_entry *sge = &sgt[i];

		/* NOTE: We only support SG entries in dpaa2_sg_single क्रमmat,
		 * but this is the only क्रमmat we may receive from HW anyway
		 */

		/* Get the address and length from the S/G entry */
		sg_addr = dpaa2_sg_get_addr(sge);
		sg_vaddr = dpaa2_iova_to_virt(priv->iommu_करोमुख्य, sg_addr);
		dma_unmap_page(dev, sg_addr, priv->rx_buf_size,
			       DMA_BIसूचीECTIONAL);

		sg_length = dpaa2_sg_get_len(sge);

		अगर (i == 0) अणु
			/* We build the skb around the first data buffer */
			skb = build_skb(sg_vaddr, DPAA2_ETH_RX_BUF_RAW_SIZE);
			अगर (unlikely(!skb)) अणु
				/* Free the first SG entry now, since we alपढ़ोy
				 * unmapped it and obtained the भव address
				 */
				मुक्त_pages((अचिन्हित दीर्घ)sg_vaddr, 0);

				/* We still need to subtract the buffers used
				 * by this FD from our software counter
				 */
				जबतक (!dpaa2_sg_is_final(&sgt[i]) &&
				       i < DPAA2_ETH_MAX_SG_ENTRIES)
					i++;
				अवरोध;
			पूर्ण

			sg_offset = dpaa2_sg_get_offset(sge);
			skb_reserve(skb, sg_offset);
			skb_put(skb, sg_length);
		पूर्ण अन्यथा अणु
			/* Rest of the data buffers are stored as skb frags */
			page = virt_to_page(sg_vaddr);
			head_page = virt_to_head_page(sg_vaddr);

			/* Offset in page (which may be compound).
			 * Data in subsequent SG entries is stored from the
			 * beginning of the buffer, so we करोn't need to add the
			 * sg_offset.
			 */
			page_offset = ((अचिन्हित दीर्घ)sg_vaddr &
				(PAGE_SIZE - 1)) +
				(page_address(page) - page_address(head_page));

			skb_add_rx_frag(skb, i - 1, head_page, page_offset,
					sg_length, priv->rx_buf_size);
		पूर्ण

		अगर (dpaa2_sg_is_final(sge))
			अवरोध;
	पूर्ण

	WARN_ONCE(i == DPAA2_ETH_MAX_SG_ENTRIES, "Final bit not set in SGT");

	/* Count all data buffers + SG table buffer */
	ch->buf_count -= i + 2;

	वापस skb;
पूर्ण

/* Free buffers acquired from the buffer pool or which were meant to
 * be released in the pool
 */
अटल व्योम dpaa2_eth_मुक्त_bufs(काष्ठा dpaa2_eth_priv *priv, u64 *buf_array,
				पूर्णांक count)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	व्योम *vaddr;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		vaddr = dpaa2_iova_to_virt(priv->iommu_करोमुख्य, buf_array[i]);
		dma_unmap_page(dev, buf_array[i], priv->rx_buf_size,
			       DMA_BIसूचीECTIONAL);
		मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
	पूर्ण
पूर्ण

अटल व्योम dpaa2_eth_recycle_buf(काष्ठा dpaa2_eth_priv *priv,
				  काष्ठा dpaa2_eth_channel *ch,
				  dma_addr_t addr)
अणु
	पूर्णांक retries = 0;
	पूर्णांक err;

	ch->recycled_bufs[ch->recycled_bufs_cnt++] = addr;
	अगर (ch->recycled_bufs_cnt < DPAA2_ETH_BUFS_PER_CMD)
		वापस;

	जबतक ((err = dpaa2_io_service_release(ch->dpio, priv->bpid,
					       ch->recycled_bufs,
					       ch->recycled_bufs_cnt)) == -EBUSY) अणु
		अगर (retries++ >= DPAA2_ETH_SWP_BUSY_RETRIES)
			अवरोध;
		cpu_relax();
	पूर्ण

	अगर (err) अणु
		dpaa2_eth_मुक्त_bufs(priv, ch->recycled_bufs, ch->recycled_bufs_cnt);
		ch->buf_count -= ch->recycled_bufs_cnt;
	पूर्ण

	ch->recycled_bufs_cnt = 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_xdp_flush(काष्ठा dpaa2_eth_priv *priv,
			       काष्ठा dpaa2_eth_fq *fq,
			       काष्ठा dpaa2_eth_xdp_fds *xdp_fds)
अणु
	पूर्णांक total_enqueued = 0, retries = 0, enqueued;
	काष्ठा dpaa2_eth_drv_stats *percpu_extras;
	पूर्णांक num_fds, err, max_retries;
	काष्ठा dpaa2_fd *fds;

	percpu_extras = this_cpu_ptr(priv->percpu_extras);

	/* try to enqueue all the FDs until the max number of retries is hit */
	fds = xdp_fds->fds;
	num_fds = xdp_fds->num;
	max_retries = num_fds * DPAA2_ETH_ENQUEUE_RETRIES;
	जबतक (total_enqueued < num_fds && retries < max_retries) अणु
		err = priv->enqueue(priv, fq, &fds[total_enqueued],
				    0, num_fds - total_enqueued, &enqueued);
		अगर (err == -EBUSY) अणु
			percpu_extras->tx_portal_busy += ++retries;
			जारी;
		पूर्ण
		total_enqueued += enqueued;
	पूर्ण
	xdp_fds->num = 0;

	वापस total_enqueued;
पूर्ण

अटल व्योम dpaa2_eth_xdp_tx_flush(काष्ठा dpaa2_eth_priv *priv,
				   काष्ठा dpaa2_eth_channel *ch,
				   काष्ठा dpaa2_eth_fq *fq)
अणु
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa2_fd *fds;
	पूर्णांक enqueued, i;

	percpu_stats = this_cpu_ptr(priv->percpu_stats);

	// enqueue the array of XDP_TX frames
	enqueued = dpaa2_eth_xdp_flush(priv, fq, &fq->xdp_tx_fds);

	/* update statistics */
	percpu_stats->tx_packets += enqueued;
	fds = fq->xdp_tx_fds.fds;
	क्रम (i = 0; i < enqueued; i++) अणु
		percpu_stats->tx_bytes += dpaa2_fd_get_len(&fds[i]);
		ch->stats.xdp_tx++;
	पूर्ण
	क्रम (i = enqueued; i < fq->xdp_tx_fds.num; i++) अणु
		dpaa2_eth_recycle_buf(priv, ch, dpaa2_fd_get_addr(&fds[i]));
		percpu_stats->tx_errors++;
		ch->stats.xdp_tx_err++;
	पूर्ण
	fq->xdp_tx_fds.num = 0;
पूर्ण

अटल व्योम dpaa2_eth_xdp_enqueue(काष्ठा dpaa2_eth_priv *priv,
				  काष्ठा dpaa2_eth_channel *ch,
				  काष्ठा dpaa2_fd *fd,
				  व्योम *buf_start, u16 queue_id)
अणु
	काष्ठा dpaa2_faead *faead;
	काष्ठा dpaa2_fd *dest_fd;
	काष्ठा dpaa2_eth_fq *fq;
	u32 ctrl, frc;

	/* Mark the egress frame hardware annotation area as valid */
	frc = dpaa2_fd_get_frc(fd);
	dpaa2_fd_set_frc(fd, frc | DPAA2_FD_FRC_FAEADV);
	dpaa2_fd_set_ctrl(fd, DPAA2_FD_CTRL_ASAL);

	/* Inकाष्ठा hardware to release the FD buffer directly पूर्णांकo
	 * the buffer pool once transmission is completed, instead of
	 * sending a Tx confirmation frame to us
	 */
	ctrl = DPAA2_FAEAD_A4V | DPAA2_FAEAD_A2V | DPAA2_FAEAD_EBDDV;
	faead = dpaa2_get_faead(buf_start, false);
	faead->ctrl = cpu_to_le32(ctrl);
	faead->conf_fqid = 0;

	fq = &priv->fq[queue_id];
	dest_fd = &fq->xdp_tx_fds.fds[fq->xdp_tx_fds.num++];
	स_नकल(dest_fd, fd, माप(*dest_fd));

	अगर (fq->xdp_tx_fds.num < DEV_MAP_BULK_SIZE)
		वापस;

	dpaa2_eth_xdp_tx_flush(priv, ch, fq);
पूर्ण

अटल u32 dpaa2_eth_run_xdp(काष्ठा dpaa2_eth_priv *priv,
			     काष्ठा dpaa2_eth_channel *ch,
			     काष्ठा dpaa2_eth_fq *rx_fq,
			     काष्ठा dpaa2_fd *fd, व्योम *vaddr)
अणु
	dma_addr_t addr = dpaa2_fd_get_addr(fd);
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xdp_buff xdp;
	u32 xdp_act = XDP_PASS;
	पूर्णांक err, offset;

	rcu_पढ़ो_lock();

	xdp_prog = READ_ONCE(ch->xdp.prog);
	अगर (!xdp_prog)
		जाओ out;

	offset = dpaa2_fd_get_offset(fd) - XDP_PACKET_HEADROOM;
	xdp_init_buff(&xdp, DPAA2_ETH_RX_BUF_RAW_SIZE - offset, &ch->xdp_rxq);
	xdp_prepare_buff(&xdp, vaddr + offset, XDP_PACKET_HEADROOM,
			 dpaa2_fd_get_len(fd), false);

	xdp_act = bpf_prog_run_xdp(xdp_prog, &xdp);

	/* xdp.data poपूर्णांकer may have changed */
	dpaa2_fd_set_offset(fd, xdp.data - vaddr);
	dpaa2_fd_set_len(fd, xdp.data_end - xdp.data);

	चयन (xdp_act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		dpaa2_eth_xdp_enqueue(priv, ch, fd, vaddr, rx_fq->flowid);
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(xdp_act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(priv->net_dev, xdp_prog, xdp_act);
		fallthrough;
	हाल XDP_DROP:
		dpaa2_eth_recycle_buf(priv, ch, addr);
		ch->stats.xdp_drop++;
		अवरोध;
	हाल XDP_REसूचीECT:
		dma_unmap_page(priv->net_dev->dev.parent, addr,
			       priv->rx_buf_size, DMA_BIसूचीECTIONAL);
		ch->buf_count--;

		/* Allow redirect use of full headroom */
		xdp.data_hard_start = vaddr;
		xdp.frame_sz = DPAA2_ETH_RX_BUF_RAW_SIZE;

		err = xdp_करो_redirect(priv->net_dev, &xdp, xdp_prog);
		अगर (unlikely(err)) अणु
			addr = dma_map_page(priv->net_dev->dev.parent,
					    virt_to_page(vaddr), 0,
					    priv->rx_buf_size, DMA_BIसूचीECTIONAL);
			अगर (unlikely(dma_mapping_error(priv->net_dev->dev.parent, addr))) अणु
				मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
			पूर्ण अन्यथा अणु
				ch->buf_count++;
				dpaa2_eth_recycle_buf(priv, ch, addr);
			पूर्ण
			ch->stats.xdp_drop++;
		पूर्ण अन्यथा अणु
			ch->stats.xdp_redirect++;
		पूर्ण
		अवरोध;
	पूर्ण

	ch->xdp.res |= xdp_act;
out:
	rcu_पढ़ो_unlock();
	वापस xdp_act;
पूर्ण

अटल काष्ठा sk_buff *dpaa2_eth_copyअवरोध(काष्ठा dpaa2_eth_channel *ch,
					   स्थिर काष्ठा dpaa2_fd *fd,
					   व्योम *fd_vaddr)
अणु
	u16 fd_offset = dpaa2_fd_get_offset(fd);
	काष्ठा dpaa2_eth_priv *priv = ch->priv;
	u32 fd_length = dpaa2_fd_get_len(fd);
	काष्ठा sk_buff *skb = शून्य;
	अचिन्हित पूर्णांक skb_len;

	अगर (fd_length > priv->rx_copyअवरोध)
		वापस शून्य;

	skb_len = fd_length + dpaa2_eth_needed_headroom(शून्य);

	skb = napi_alloc_skb(&ch->napi, skb_len);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, dpaa2_eth_needed_headroom(शून्य));
	skb_put(skb, fd_length);

	स_नकल(skb->data, fd_vaddr + fd_offset, fd_length);

	dpaa2_eth_recycle_buf(priv, ch, dpaa2_fd_get_addr(fd));

	वापस skb;
पूर्ण

/* Main Rx frame processing routine */
अटल व्योम dpaa2_eth_rx(काष्ठा dpaa2_eth_priv *priv,
			 काष्ठा dpaa2_eth_channel *ch,
			 स्थिर काष्ठा dpaa2_fd *fd,
			 काष्ठा dpaa2_eth_fq *fq)
अणु
	dma_addr_t addr = dpaa2_fd_get_addr(fd);
	u8 fd_क्रमmat = dpaa2_fd_get_क्रमmat(fd);
	व्योम *vaddr;
	काष्ठा sk_buff *skb;
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa2_eth_drv_stats *percpu_extras;
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpaa2_fas *fas;
	व्योम *buf_data;
	u32 status = 0;
	u32 xdp_act;

	/* Tracing poपूर्णांक */
	trace_dpaa2_rx_fd(priv->net_dev, fd);

	vaddr = dpaa2_iova_to_virt(priv->iommu_करोमुख्य, addr);
	dma_sync_single_क्रम_cpu(dev, addr, priv->rx_buf_size,
				DMA_BIसूचीECTIONAL);

	fas = dpaa2_get_fas(vaddr, false);
	prefetch(fas);
	buf_data = vaddr + dpaa2_fd_get_offset(fd);
	prefetch(buf_data);

	percpu_stats = this_cpu_ptr(priv->percpu_stats);
	percpu_extras = this_cpu_ptr(priv->percpu_extras);

	अगर (fd_क्रमmat == dpaa2_fd_single) अणु
		xdp_act = dpaa2_eth_run_xdp(priv, ch, fq, (काष्ठा dpaa2_fd *)fd, vaddr);
		अगर (xdp_act != XDP_PASS) अणु
			percpu_stats->rx_packets++;
			percpu_stats->rx_bytes += dpaa2_fd_get_len(fd);
			वापस;
		पूर्ण

		skb = dpaa2_eth_copyअवरोध(ch, fd, vaddr);
		अगर (!skb) अणु
			dma_unmap_page(dev, addr, priv->rx_buf_size,
				       DMA_BIसूचीECTIONAL);
			skb = dpaa2_eth_build_linear_skb(ch, fd, vaddr);
		पूर्ण
	पूर्ण अन्यथा अगर (fd_क्रमmat == dpaa2_fd_sg) अणु
		WARN_ON(priv->xdp_prog);

		dma_unmap_page(dev, addr, priv->rx_buf_size,
			       DMA_BIसूचीECTIONAL);
		skb = dpaa2_eth_build_frag_skb(priv, ch, buf_data);
		मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
		percpu_extras->rx_sg_frames++;
		percpu_extras->rx_sg_bytes += dpaa2_fd_get_len(fd);
	पूर्ण अन्यथा अणु
		/* We करोn't support any other क्रमmat */
		जाओ err_frame_क्रमmat;
	पूर्ण

	अगर (unlikely(!skb))
		जाओ err_build_skb;

	prefetch(skb->data);

	/* Get the बारtamp value */
	अगर (priv->rx_tstamp) अणु
		काष्ठा skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
		__le64 *ts = dpaa2_get_ts(vaddr, false);
		u64 ns;

		स_रखो(shhwtstamps, 0, माप(*shhwtstamps));

		ns = DPAA2_PTP_CLK_PERIOD_NS * le64_to_cpup(ts);
		shhwtstamps->hwtstamp = ns_to_kसमय(ns);
	पूर्ण

	/* Check अगर we need to validate the L4 csum */
	अगर (likely(dpaa2_fd_get_frc(fd) & DPAA2_FD_FRC_FASV)) अणु
		status = le32_to_cpu(fas->status);
		dpaa2_eth_validate_rx_csum(priv, status, skb);
	पूर्ण

	skb->protocol = eth_type_trans(skb, priv->net_dev);
	skb_record_rx_queue(skb, fq->flowid);

	percpu_stats->rx_packets++;
	percpu_stats->rx_bytes += dpaa2_fd_get_len(fd);

	list_add_tail(&skb->list, ch->rx_list);

	वापस;

err_build_skb:
	dpaa2_eth_मुक्त_rx_fd(priv, fd, vaddr);
err_frame_क्रमmat:
	percpu_stats->rx_dropped++;
पूर्ण

/* Processing of Rx frames received on the error FQ
 * We check and prपूर्णांक the error bits and then मुक्त the frame
 */
अटल व्योम dpaa2_eth_rx_err(काष्ठा dpaa2_eth_priv *priv,
			     काष्ठा dpaa2_eth_channel *ch,
			     स्थिर काष्ठा dpaa2_fd *fd,
			     काष्ठा dpaa2_eth_fq *fq __always_unused)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	dma_addr_t addr = dpaa2_fd_get_addr(fd);
	u8 fd_क्रमmat = dpaa2_fd_get_क्रमmat(fd);
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa2_eth_trap_item *trap_item;
	काष्ठा dpaa2_fapr *fapr;
	काष्ठा sk_buff *skb;
	व्योम *buf_data;
	व्योम *vaddr;

	vaddr = dpaa2_iova_to_virt(priv->iommu_करोमुख्य, addr);
	dma_sync_single_क्रम_cpu(dev, addr, priv->rx_buf_size,
				DMA_BIसूचीECTIONAL);

	buf_data = vaddr + dpaa2_fd_get_offset(fd);

	अगर (fd_क्रमmat == dpaa2_fd_single) अणु
		dma_unmap_page(dev, addr, priv->rx_buf_size,
			       DMA_BIसूचीECTIONAL);
		skb = dpaa2_eth_build_linear_skb(ch, fd, vaddr);
	पूर्ण अन्यथा अगर (fd_क्रमmat == dpaa2_fd_sg) अणु
		dma_unmap_page(dev, addr, priv->rx_buf_size,
			       DMA_BIसूचीECTIONAL);
		skb = dpaa2_eth_build_frag_skb(priv, ch, buf_data);
		मुक्त_pages((अचिन्हित दीर्घ)vaddr, 0);
	पूर्ण अन्यथा अणु
		/* We करोn't support any other क्रमmat */
		dpaa2_eth_मुक्त_rx_fd(priv, fd, vaddr);
		जाओ err_frame_क्रमmat;
	पूर्ण

	fapr = dpaa2_get_fapr(vaddr, false);
	trap_item = dpaa2_eth_dl_get_trap(priv, fapr);
	अगर (trap_item)
		devlink_trap_report(priv->devlink, skb, trap_item->trap_ctx,
				    &priv->devlink_port, शून्य);
	consume_skb(skb);

err_frame_क्रमmat:
	percpu_stats = this_cpu_ptr(priv->percpu_stats);
	percpu_stats->rx_errors++;
	ch->buf_count--;
पूर्ण

/* Consume all frames pull-dequeued पूर्णांकo the store. This is the simplest way to
 * make sure we करोn't accidentally issue another अस्थिर dequeue which would
 * overग_लिखो (leak) frames alपढ़ोy in the store.
 *
 * Observance of NAPI budget is not our concern, leaving that to the caller.
 */
अटल पूर्णांक dpaa2_eth_consume_frames(काष्ठा dpaa2_eth_channel *ch,
				    काष्ठा dpaa2_eth_fq **src)
अणु
	काष्ठा dpaa2_eth_priv *priv = ch->priv;
	काष्ठा dpaa2_eth_fq *fq = शून्य;
	काष्ठा dpaa2_dq *dq;
	स्थिर काष्ठा dpaa2_fd *fd;
	पूर्णांक cleaned = 0, retries = 0;
	पूर्णांक is_last;

	करो अणु
		dq = dpaa2_io_store_next(ch->store, &is_last);
		अगर (unlikely(!dq)) अणु
			/* If we're here, we *must* have placed a
			 * अस्थिर dequeue comnmand, so keep पढ़ोing through
			 * the store until we get some sort of valid response
			 * token (either a valid frame or an "empty dequeue")
			 */
			अगर (retries++ >= DPAA2_ETH_SWP_BUSY_RETRIES) अणु
				netdev_err_once(priv->net_dev,
						"Unable to read a valid dequeue response\n");
				वापस -ETIMEDOUT;
			पूर्ण
			जारी;
		पूर्ण

		fd = dpaa2_dq_fd(dq);
		fq = (काष्ठा dpaa2_eth_fq *)(uपूर्णांकptr_t)dpaa2_dq_fqd_ctx(dq);

		fq->consume(priv, ch, fd, fq);
		cleaned++;
		retries = 0;
	पूर्ण जबतक (!is_last);

	अगर (!cleaned)
		वापस 0;

	fq->stats.frames += cleaned;
	ch->stats.frames += cleaned;

	/* A dequeue operation only pulls frames from a single queue
	 * पूर्णांकo the store. Return the frame queue as an out param.
	 */
	अगर (src)
		*src = fq;

	वापस cleaned;
पूर्ण

अटल पूर्णांक dpaa2_eth_ptp_parse(काष्ठा sk_buff *skb,
			       u8 *msgtype, u8 *twostep, u8 *udp,
			       u16 *correction_offset,
			       u16 *origपूर्णांकimestamp_offset)
अणु
	अचिन्हित पूर्णांक ptp_class;
	काष्ठा ptp_header *hdr;
	अचिन्हित पूर्णांक type;
	u8 *base;

	ptp_class = ptp_classअगरy_raw(skb);
	अगर (ptp_class == PTP_CLASS_NONE)
		वापस -EINVAL;

	hdr = ptp_parse_header(skb, ptp_class);
	अगर (!hdr)
		वापस -EINVAL;

	*msgtype = ptp_get_msgtype(hdr, ptp_class);
	*twostep = hdr->flag_field[0] & 0x2;

	type = ptp_class & PTP_CLASS_PMASK;
	अगर (type == PTP_CLASS_IPV4 ||
	    type == PTP_CLASS_IPV6)
		*udp = 1;
	अन्यथा
		*udp = 0;

	base = skb_mac_header(skb);
	*correction_offset = (u8 *)&hdr->correction - base;
	*origपूर्णांकimestamp_offset = (u8 *)hdr + माप(काष्ठा ptp_header) - base;

	वापस 0;
पूर्ण

/* Configure the egress frame annotation क्रम बारtamp update */
अटल व्योम dpaa2_eth_enable_tx_tstamp(काष्ठा dpaa2_eth_priv *priv,
				       काष्ठा dpaa2_fd *fd,
				       व्योम *buf_start,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ptp_tstamp origin_बारtamp;
	काष्ठा dpni_single_step_cfg cfg;
	u8 msgtype, twostep, udp;
	काष्ठा dpaa2_faead *faead;
	काष्ठा dpaa2_fas *fas;
	काष्ठा बारpec64 ts;
	u16 offset1, offset2;
	u32 ctrl, frc;
	__le64 *ns;
	u8 *data;

	/* Mark the egress frame annotation area as valid */
	frc = dpaa2_fd_get_frc(fd);
	dpaa2_fd_set_frc(fd, frc | DPAA2_FD_FRC_FAEADV);

	/* Set hardware annotation size */
	ctrl = dpaa2_fd_get_ctrl(fd);
	dpaa2_fd_set_ctrl(fd, ctrl | DPAA2_FD_CTRL_ASAL);

	/* enable UPD (update prepanded data) bit in FAEAD field of
	 * hardware frame annotation area
	 */
	ctrl = DPAA2_FAEAD_A2V | DPAA2_FAEAD_UPDV | DPAA2_FAEAD_UPD;
	faead = dpaa2_get_faead(buf_start, true);
	faead->ctrl = cpu_to_le32(ctrl);

	अगर (skb->cb[0] == TX_TSTAMP_ONESTEP_SYNC) अणु
		अगर (dpaa2_eth_ptp_parse(skb, &msgtype, &twostep, &udp,
					&offset1, &offset2) ||
		    msgtype != PTP_MSGTYPE_SYNC || twostep) अणु
			WARN_ONCE(1, "Bad packet for one-step timestamping\n");
			वापस;
		पूर्ण

		/* Mark the frame annotation status as valid */
		frc = dpaa2_fd_get_frc(fd);
		dpaa2_fd_set_frc(fd, frc | DPAA2_FD_FRC_FASV);

		/* Mark the PTP flag क्रम one step बारtamping */
		fas = dpaa2_get_fas(buf_start, true);
		fas->status = cpu_to_le32(DPAA2_FAS_PTP);

		dpaa2_ptp->caps.समय_लो64(&dpaa2_ptp->caps, &ts);
		ns = dpaa2_get_ts(buf_start, true);
		*ns = cpu_to_le64(बारpec64_to_ns(&ts) /
				  DPAA2_PTP_CLK_PERIOD_NS);

		/* Update current समय to PTP message originTimestamp field */
		ns_to_ptp_tstamp(&origin_बारtamp, le64_to_cpup(ns));
		data = skb_mac_header(skb);
		*(__be16 *)(data + offset2) = htons(origin_बारtamp.sec_msb);
		*(__be32 *)(data + offset2 + 2) =
			htonl(origin_बारtamp.sec_lsb);
		*(__be32 *)(data + offset2 + 6) = htonl(origin_बारtamp.nsec);

		cfg.en = 1;
		cfg.ch_update = udp;
		cfg.offset = offset1;
		cfg.peer_delay = 0;

		अगर (dpni_set_single_step_cfg(priv->mc_io, 0, priv->mc_token,
					     &cfg))
			WARN_ONCE(1, "Failed to set single step register");
	पूर्ण
पूर्ण

/* Create a frame descriptor based on a fragmented skb */
अटल पूर्णांक dpaa2_eth_build_sg_fd(काष्ठा dpaa2_eth_priv *priv,
				 काष्ठा sk_buff *skb,
				 काष्ठा dpaa2_fd *fd,
				 व्योम **swa_addr)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	व्योम *sgt_buf = शून्य;
	dma_addr_t addr;
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	काष्ठा dpaa2_sg_entry *sgt;
	पूर्णांक i, err;
	पूर्णांक sgt_buf_size;
	काष्ठा scatterlist *scl, *crt_scl;
	पूर्णांक num_sg;
	पूर्णांक num_dma_bufs;
	काष्ठा dpaa2_eth_swa *swa;

	/* Create and map scatterlist.
	 * We करोn't advertise NETIF_F_FRAGLIST, so skb_to_sgvec() will not have
	 * to go beyond nr_frags+1.
	 * Note: We करोn't support chained scatterlists
	 */
	अगर (unlikely(PAGE_SIZE / माप(काष्ठा scatterlist) < nr_frags + 1))
		वापस -EINVAL;

	scl = kदो_स्मृति_array(nr_frags + 1, माप(काष्ठा scatterlist), GFP_ATOMIC);
	अगर (unlikely(!scl))
		वापस -ENOMEM;

	sg_init_table(scl, nr_frags + 1);
	num_sg = skb_to_sgvec(skb, scl, 0, skb->len);
	अगर (unlikely(num_sg < 0)) अणु
		err = -ENOMEM;
		जाओ dma_map_sg_failed;
	पूर्ण
	num_dma_bufs = dma_map_sg(dev, scl, num_sg, DMA_BIसूचीECTIONAL);
	अगर (unlikely(!num_dma_bufs)) अणु
		err = -ENOMEM;
		जाओ dma_map_sg_failed;
	पूर्ण

	/* Prepare the HW SGT काष्ठाure */
	sgt_buf_size = priv->tx_data_offset +
		       माप(काष्ठा dpaa2_sg_entry) *  num_dma_bufs;
	sgt_buf = napi_alloc_frag_align(sgt_buf_size, DPAA2_ETH_TX_BUF_ALIGN);
	अगर (unlikely(!sgt_buf)) अणु
		err = -ENOMEM;
		जाओ sgt_buf_alloc_failed;
	पूर्ण
	स_रखो(sgt_buf, 0, sgt_buf_size);

	sgt = (काष्ठा dpaa2_sg_entry *)(sgt_buf + priv->tx_data_offset);

	/* Fill in the HW SGT काष्ठाure.
	 *
	 * sgt_buf is zeroed out, so the following fields are implicit
	 * in all sgt entries:
	 *   - offset is 0
	 *   - क्रमmat is 'dpaa2_sg_single'
	 */
	क्रम_each_sg(scl, crt_scl, num_dma_bufs, i) अणु
		dpaa2_sg_set_addr(&sgt[i], sg_dma_address(crt_scl));
		dpaa2_sg_set_len(&sgt[i], sg_dma_len(crt_scl));
	पूर्ण
	dpaa2_sg_set_final(&sgt[i - 1], true);

	/* Store the skb backpoपूर्णांकer in the SGT buffer.
	 * Fit the scatterlist and the number of buffers aदीर्घside the
	 * skb backpoपूर्णांकer in the software annotation area. We'll need
	 * all of them on Tx Conf.
	 */
	*swa_addr = (व्योम *)sgt_buf;
	swa = (काष्ठा dpaa2_eth_swa *)sgt_buf;
	swa->type = DPAA2_ETH_SWA_SG;
	swa->sg.skb = skb;
	swa->sg.scl = scl;
	swa->sg.num_sg = num_sg;
	swa->sg.sgt_size = sgt_buf_size;

	/* Separately map the SGT buffer */
	addr = dma_map_single(dev, sgt_buf, sgt_buf_size, DMA_BIसूचीECTIONAL);
	अगर (unlikely(dma_mapping_error(dev, addr))) अणु
		err = -ENOMEM;
		जाओ dma_map_single_failed;
	पूर्ण
	dpaa2_fd_set_offset(fd, priv->tx_data_offset);
	dpaa2_fd_set_क्रमmat(fd, dpaa2_fd_sg);
	dpaa2_fd_set_addr(fd, addr);
	dpaa2_fd_set_len(fd, skb->len);
	dpaa2_fd_set_ctrl(fd, FD_CTRL_PTA);

	वापस 0;

dma_map_single_failed:
	skb_मुक्त_frag(sgt_buf);
sgt_buf_alloc_failed:
	dma_unmap_sg(dev, scl, num_sg, DMA_BIसूचीECTIONAL);
dma_map_sg_failed:
	kमुक्त(scl);
	वापस err;
पूर्ण

/* Create a SG frame descriptor based on a linear skb.
 *
 * This function is used on the Tx path when the skb headroom is not large
 * enough क्रम the HW requirements, thus instead of पुनः_स्मृति-ing the skb we
 * create a SG frame descriptor with only one entry.
 */
अटल पूर्णांक dpaa2_eth_build_sg_fd_single_buf(काष्ठा dpaa2_eth_priv *priv,
					    काष्ठा sk_buff *skb,
					    काष्ठा dpaa2_fd *fd,
					    व्योम **swa_addr)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpaa2_eth_sgt_cache *sgt_cache;
	काष्ठा dpaa2_sg_entry *sgt;
	काष्ठा dpaa2_eth_swa *swa;
	dma_addr_t addr, sgt_addr;
	व्योम *sgt_buf = शून्य;
	पूर्णांक sgt_buf_size;
	पूर्णांक err;

	/* Prepare the HW SGT काष्ठाure */
	sgt_cache = this_cpu_ptr(priv->sgt_cache);
	sgt_buf_size = priv->tx_data_offset + माप(काष्ठा dpaa2_sg_entry);

	अगर (sgt_cache->count == 0)
		sgt_buf = kzalloc(sgt_buf_size + DPAA2_ETH_TX_BUF_ALIGN,
				  GFP_ATOMIC);
	अन्यथा
		sgt_buf = sgt_cache->buf[--sgt_cache->count];
	अगर (unlikely(!sgt_buf))
		वापस -ENOMEM;

	sgt_buf = PTR_ALIGN(sgt_buf, DPAA2_ETH_TX_BUF_ALIGN);
	sgt = (काष्ठा dpaa2_sg_entry *)(sgt_buf + priv->tx_data_offset);

	addr = dma_map_single(dev, skb->data, skb->len, DMA_BIसूचीECTIONAL);
	अगर (unlikely(dma_mapping_error(dev, addr))) अणु
		err = -ENOMEM;
		जाओ data_map_failed;
	पूर्ण

	/* Fill in the HW SGT काष्ठाure */
	dpaa2_sg_set_addr(sgt, addr);
	dpaa2_sg_set_len(sgt, skb->len);
	dpaa2_sg_set_final(sgt, true);

	/* Store the skb backpoपूर्णांकer in the SGT buffer */
	*swa_addr = (व्योम *)sgt_buf;
	swa = (काष्ठा dpaa2_eth_swa *)sgt_buf;
	swa->type = DPAA2_ETH_SWA_SINGLE;
	swa->single.skb = skb;
	swa->single.sgt_size = sgt_buf_size;

	/* Separately map the SGT buffer */
	sgt_addr = dma_map_single(dev, sgt_buf, sgt_buf_size, DMA_BIसूचीECTIONAL);
	अगर (unlikely(dma_mapping_error(dev, sgt_addr))) अणु
		err = -ENOMEM;
		जाओ sgt_map_failed;
	पूर्ण

	dpaa2_fd_set_offset(fd, priv->tx_data_offset);
	dpaa2_fd_set_क्रमmat(fd, dpaa2_fd_sg);
	dpaa2_fd_set_addr(fd, sgt_addr);
	dpaa2_fd_set_len(fd, skb->len);
	dpaa2_fd_set_ctrl(fd, FD_CTRL_PTA);

	वापस 0;

sgt_map_failed:
	dma_unmap_single(dev, addr, skb->len, DMA_BIसूचीECTIONAL);
data_map_failed:
	अगर (sgt_cache->count >= DPAA2_ETH_SGT_CACHE_SIZE)
		kमुक्त(sgt_buf);
	अन्यथा
		sgt_cache->buf[sgt_cache->count++] = sgt_buf;

	वापस err;
पूर्ण

/* Create a frame descriptor based on a linear skb */
अटल पूर्णांक dpaa2_eth_build_single_fd(काष्ठा dpaa2_eth_priv *priv,
				     काष्ठा sk_buff *skb,
				     काष्ठा dpaa2_fd *fd,
				     व्योम **swa_addr)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	u8 *buffer_start, *aligned_start;
	काष्ठा dpaa2_eth_swa *swa;
	dma_addr_t addr;

	buffer_start = skb->data - dpaa2_eth_needed_headroom(skb);

	/* If there's enough room to align the FD address, करो it.
	 * It will help hardware optimize accesses.
	 */
	aligned_start = PTR_ALIGN(buffer_start - DPAA2_ETH_TX_BUF_ALIGN,
				  DPAA2_ETH_TX_BUF_ALIGN);
	अगर (aligned_start >= skb->head)
		buffer_start = aligned_start;

	/* Store a backpoपूर्णांकer to the skb at the beginning of the buffer
	 * (in the निजी data area) such that we can release it
	 * on Tx confirm
	 */
	*swa_addr = (व्योम *)buffer_start;
	swa = (काष्ठा dpaa2_eth_swa *)buffer_start;
	swa->type = DPAA2_ETH_SWA_SINGLE;
	swa->single.skb = skb;

	addr = dma_map_single(dev, buffer_start,
			      skb_tail_poपूर्णांकer(skb) - buffer_start,
			      DMA_BIसूचीECTIONAL);
	अगर (unlikely(dma_mapping_error(dev, addr)))
		वापस -ENOMEM;

	dpaa2_fd_set_addr(fd, addr);
	dpaa2_fd_set_offset(fd, (u16)(skb->data - buffer_start));
	dpaa2_fd_set_len(fd, skb->len);
	dpaa2_fd_set_क्रमmat(fd, dpaa2_fd_single);
	dpaa2_fd_set_ctrl(fd, FD_CTRL_PTA);

	वापस 0;
पूर्ण

/* FD मुक्तing routine on the Tx path
 *
 * DMA-unmap and मुक्त FD and possibly SGT buffer allocated on Tx. The skb
 * back-poपूर्णांकed to is also मुक्तd.
 * This can be called either from dpaa2_eth_tx_conf() or on the error path of
 * dpaa2_eth_tx().
 */
अटल व्योम dpaa2_eth_मुक्त_tx_fd(काष्ठा dpaa2_eth_priv *priv,
				 काष्ठा dpaa2_eth_fq *fq,
				 स्थिर काष्ठा dpaa2_fd *fd, bool in_napi)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	dma_addr_t fd_addr, sg_addr;
	काष्ठा sk_buff *skb = शून्य;
	अचिन्हित अक्षर *buffer_start;
	काष्ठा dpaa2_eth_swa *swa;
	u8 fd_क्रमmat = dpaa2_fd_get_क्रमmat(fd);
	u32 fd_len = dpaa2_fd_get_len(fd);

	काष्ठा dpaa2_eth_sgt_cache *sgt_cache;
	काष्ठा dpaa2_sg_entry *sgt;

	fd_addr = dpaa2_fd_get_addr(fd);
	buffer_start = dpaa2_iova_to_virt(priv->iommu_करोमुख्य, fd_addr);
	swa = (काष्ठा dpaa2_eth_swa *)buffer_start;

	अगर (fd_क्रमmat == dpaa2_fd_single) अणु
		अगर (swa->type == DPAA2_ETH_SWA_SINGLE) अणु
			skb = swa->single.skb;
			/* Accessing the skb buffer is safe beक्रमe dma unmap,
			 * because we didn't map the actual skb shell.
			 */
			dma_unmap_single(dev, fd_addr,
					 skb_tail_poपूर्णांकer(skb) - buffer_start,
					 DMA_BIसूचीECTIONAL);
		पूर्ण अन्यथा अणु
			WARN_ONCE(swa->type != DPAA2_ETH_SWA_XDP, "Wrong SWA type");
			dma_unmap_single(dev, fd_addr, swa->xdp.dma_size,
					 DMA_BIसूचीECTIONAL);
		पूर्ण
	पूर्ण अन्यथा अगर (fd_क्रमmat == dpaa2_fd_sg) अणु
		अगर (swa->type == DPAA2_ETH_SWA_SG) अणु
			skb = swa->sg.skb;

			/* Unmap the scatterlist */
			dma_unmap_sg(dev, swa->sg.scl, swa->sg.num_sg,
				     DMA_BIसूचीECTIONAL);
			kमुक्त(swa->sg.scl);

			/* Unmap the SGT buffer */
			dma_unmap_single(dev, fd_addr, swa->sg.sgt_size,
					 DMA_BIसूचीECTIONAL);
		पूर्ण अन्यथा अणु
			skb = swa->single.skb;

			/* Unmap the SGT Buffer */
			dma_unmap_single(dev, fd_addr, swa->single.sgt_size,
					 DMA_BIसूचीECTIONAL);

			sgt = (काष्ठा dpaa2_sg_entry *)(buffer_start +
							priv->tx_data_offset);
			sg_addr = dpaa2_sg_get_addr(sgt);
			dma_unmap_single(dev, sg_addr, skb->len, DMA_BIसूचीECTIONAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_dbg(priv->net_dev, "Invalid FD format\n");
		वापस;
	पूर्ण

	अगर (swa->type != DPAA2_ETH_SWA_XDP && in_napi) अणु
		fq->dq_frames++;
		fq->dq_bytes += fd_len;
	पूर्ण

	अगर (swa->type == DPAA2_ETH_SWA_XDP) अणु
		xdp_वापस_frame(swa->xdp.xdpf);
		वापस;
	पूर्ण

	/* Get the बारtamp value */
	अगर (skb->cb[0] == TX_TSTAMP) अणु
		काष्ठा skb_shared_hwtstamps shhwtstamps;
		__le64 *ts = dpaa2_get_ts(buffer_start, true);
		u64 ns;

		स_रखो(&shhwtstamps, 0, माप(shhwtstamps));

		ns = DPAA2_PTP_CLK_PERIOD_NS * le64_to_cpup(ts);
		shhwtstamps.hwtstamp = ns_to_kसमय(ns);
		skb_tstamp_tx(skb, &shhwtstamps);
	पूर्ण अन्यथा अगर (skb->cb[0] == TX_TSTAMP_ONESTEP_SYNC) अणु
		mutex_unlock(&priv->onestep_tstamp_lock);
	पूर्ण

	/* Free SGT buffer allocated on tx */
	अगर (fd_क्रमmat != dpaa2_fd_single) अणु
		sgt_cache = this_cpu_ptr(priv->sgt_cache);
		अगर (swa->type == DPAA2_ETH_SWA_SG) अणु
			skb_मुक्त_frag(buffer_start);
		पूर्ण अन्यथा अणु
			अगर (sgt_cache->count >= DPAA2_ETH_SGT_CACHE_SIZE)
				kमुक्त(buffer_start);
			अन्यथा
				sgt_cache->buf[sgt_cache->count++] = buffer_start;
		पूर्ण
	पूर्ण

	/* Move on with skb release */
	napi_consume_skb(skb, in_napi);
पूर्ण

अटल netdev_tx_t __dpaa2_eth_tx(काष्ठा sk_buff *skb,
				  काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा dpaa2_fd fd;
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa2_eth_drv_stats *percpu_extras;
	काष्ठा dpaa2_eth_fq *fq;
	काष्ठा netdev_queue *nq;
	u16 queue_mapping;
	अचिन्हित पूर्णांक needed_headroom;
	u32 fd_len;
	u8 prio = 0;
	पूर्णांक err, i;
	व्योम *swa;

	percpu_stats = this_cpu_ptr(priv->percpu_stats);
	percpu_extras = this_cpu_ptr(priv->percpu_extras);

	needed_headroom = dpaa2_eth_needed_headroom(skb);

	/* We'll be holding a back-reference to the skb until Tx Confirmation;
	 * we करोn't want that overwritten by a concurrent Tx with a cloned skb.
	 */
	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (unlikely(!skb)) अणु
		/* skb_unshare() has alपढ़ोy मुक्तd the skb */
		percpu_stats->tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Setup the FD fields */
	स_रखो(&fd, 0, माप(fd));

	अगर (skb_is_nonlinear(skb)) अणु
		err = dpaa2_eth_build_sg_fd(priv, skb, &fd, &swa);
		percpu_extras->tx_sg_frames++;
		percpu_extras->tx_sg_bytes += skb->len;
	पूर्ण अन्यथा अगर (skb_headroom(skb) < needed_headroom) अणु
		err = dpaa2_eth_build_sg_fd_single_buf(priv, skb, &fd, &swa);
		percpu_extras->tx_sg_frames++;
		percpu_extras->tx_sg_bytes += skb->len;
		percpu_extras->tx_converted_sg_frames++;
		percpu_extras->tx_converted_sg_bytes += skb->len;
	पूर्ण अन्यथा अणु
		err = dpaa2_eth_build_single_fd(priv, skb, &fd, &swa);
	पूर्ण

	अगर (unlikely(err)) अणु
		percpu_stats->tx_dropped++;
		जाओ err_build_fd;
	पूर्ण

	अगर (skb->cb[0])
		dpaa2_eth_enable_tx_tstamp(priv, &fd, swa, skb);

	/* Tracing poपूर्णांक */
	trace_dpaa2_tx_fd(net_dev, &fd);

	/* TxConf FQ selection relies on queue id from the stack.
	 * In हाल of a क्रमwarded frame from another DPNI पूर्णांकerface, we choose
	 * a queue affined to the same core that processed the Rx frame
	 */
	queue_mapping = skb_get_queue_mapping(skb);

	अगर (net_dev->num_tc) अणु
		prio = netdev_txq_to_tc(net_dev, queue_mapping);
		/* Hardware पूर्णांकerprets priority level 0 as being the highest,
		 * so we need to करो a reverse mapping to the netdev tc index
		 */
		prio = net_dev->num_tc - prio - 1;
		/* We have only one FQ array entry क्रम all Tx hardware queues
		 * with the same flow id (but dअगरferent priority levels)
		 */
		queue_mapping %= dpaa2_eth_queue_count(priv);
	पूर्ण
	fq = &priv->fq[queue_mapping];

	fd_len = dpaa2_fd_get_len(&fd);
	nq = netdev_get_tx_queue(net_dev, queue_mapping);
	netdev_tx_sent_queue(nq, fd_len);

	/* Everything that happens after this enqueues might race with
	 * the Tx confirmation callback क्रम this frame
	 */
	क्रम (i = 0; i < DPAA2_ETH_ENQUEUE_RETRIES; i++) अणु
		err = priv->enqueue(priv, fq, &fd, prio, 1, शून्य);
		अगर (err != -EBUSY)
			अवरोध;
	पूर्ण
	percpu_extras->tx_portal_busy += i;
	अगर (unlikely(err < 0)) अणु
		percpu_stats->tx_errors++;
		/* Clean up everything, including मुक्तing the skb */
		dpaa2_eth_मुक्त_tx_fd(priv, fq, &fd, false);
		netdev_tx_completed_queue(nq, 1, fd_len);
	पूर्ण अन्यथा अणु
		percpu_stats->tx_packets++;
		percpu_stats->tx_bytes += fd_len;
	पूर्ण

	वापस NETDEV_TX_OK;

err_build_fd:
	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम dpaa2_eth_tx_onestep_tstamp(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dpaa2_eth_priv *priv = container_of(work, काष्ठा dpaa2_eth_priv,
						   tx_onestep_tstamp);
	काष्ठा sk_buff *skb;

	जबतक (true) अणु
		skb = skb_dequeue(&priv->tx_skbs);
		अगर (!skb)
			वापस;

		/* Lock just beक्रमe TX one-step बारtamping packet,
		 * and release the lock in dpaa2_eth_मुक्त_tx_fd when
		 * confirm the packet has been sent on hardware, or
		 * when clean up during transmit failure.
		 */
		mutex_lock(&priv->onestep_tstamp_lock);
		__dpaa2_eth_tx(skb, priv->net_dev);
	पूर्ण
पूर्ण

अटल netdev_tx_t dpaa2_eth_tx(काष्ठा sk_buff *skb, काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u8 msgtype, twostep, udp;
	u16 offset1, offset2;

	/* Utilize skb->cb[0] क्रम बारtamping request per skb */
	skb->cb[0] = 0;

	अगर ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) && dpaa2_ptp) अणु
		अगर (priv->tx_tstamp_type == HWTSTAMP_TX_ON)
			skb->cb[0] = TX_TSTAMP;
		अन्यथा अगर (priv->tx_tstamp_type == HWTSTAMP_TX_ONESTEP_SYNC)
			skb->cb[0] = TX_TSTAMP_ONESTEP_SYNC;
	पूर्ण

	/* TX क्रम one-step बारtamping PTP Sync packet */
	अगर (skb->cb[0] == TX_TSTAMP_ONESTEP_SYNC) अणु
		अगर (!dpaa2_eth_ptp_parse(skb, &msgtype, &twostep, &udp,
					 &offset1, &offset2))
			अगर (msgtype == PTP_MSGTYPE_SYNC && twostep == 0) अणु
				skb_queue_tail(&priv->tx_skbs, skb);
				queue_work(priv->dpaa2_ptp_wq,
					   &priv->tx_onestep_tstamp);
				वापस NETDEV_TX_OK;
			पूर्ण
		/* Use two-step बारtamping अगर not one-step बारtamping
		 * PTP Sync packet
		 */
		skb->cb[0] = TX_TSTAMP;
	पूर्ण

	/* TX क्रम other packets */
	वापस __dpaa2_eth_tx(skb, net_dev);
पूर्ण

/* Tx confirmation frame processing routine */
अटल व्योम dpaa2_eth_tx_conf(काष्ठा dpaa2_eth_priv *priv,
			      काष्ठा dpaa2_eth_channel *ch __always_unused,
			      स्थिर काष्ठा dpaa2_fd *fd,
			      काष्ठा dpaa2_eth_fq *fq)
अणु
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa2_eth_drv_stats *percpu_extras;
	u32 fd_len = dpaa2_fd_get_len(fd);
	u32 fd_errors;

	/* Tracing poपूर्णांक */
	trace_dpaa2_tx_conf_fd(priv->net_dev, fd);

	percpu_extras = this_cpu_ptr(priv->percpu_extras);
	percpu_extras->tx_conf_frames++;
	percpu_extras->tx_conf_bytes += fd_len;

	/* Check frame errors in the FD field */
	fd_errors = dpaa2_fd_get_ctrl(fd) & DPAA2_FD_TX_ERR_MASK;
	dpaa2_eth_मुक्त_tx_fd(priv, fq, fd, true);

	अगर (likely(!fd_errors))
		वापस;

	अगर (net_ratelimit())
		netdev_dbg(priv->net_dev, "TX frame FD error: 0x%08x\n",
			   fd_errors);

	percpu_stats = this_cpu_ptr(priv->percpu_stats);
	/* Tx-conf logically pertains to the egress path. */
	percpu_stats->tx_errors++;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_rx_vlan_filtering(काष्ठा dpaa2_eth_priv *priv,
					   bool enable)
अणु
	पूर्णांक err;

	err = dpni_enable_vlan_filter(priv->mc_io, 0, priv->mc_token, enable);

	अगर (err) अणु
		netdev_err(priv->net_dev,
			   "dpni_enable_vlan_filter failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_rx_csum(काष्ठा dpaa2_eth_priv *priv, bool enable)
अणु
	पूर्णांक err;

	err = dpni_set_offload(priv->mc_io, 0, priv->mc_token,
			       DPNI_OFF_RX_L3_CSUM, enable);
	अगर (err) अणु
		netdev_err(priv->net_dev,
			   "dpni_set_offload(RX_L3_CSUM) failed\n");
		वापस err;
	पूर्ण

	err = dpni_set_offload(priv->mc_io, 0, priv->mc_token,
			       DPNI_OFF_RX_L4_CSUM, enable);
	अगर (err) अणु
		netdev_err(priv->net_dev,
			   "dpni_set_offload(RX_L4_CSUM) failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_tx_csum(काष्ठा dpaa2_eth_priv *priv, bool enable)
अणु
	पूर्णांक err;

	err = dpni_set_offload(priv->mc_io, 0, priv->mc_token,
			       DPNI_OFF_TX_L3_CSUM, enable);
	अगर (err) अणु
		netdev_err(priv->net_dev, "dpni_set_offload(TX_L3_CSUM) failed\n");
		वापस err;
	पूर्ण

	err = dpni_set_offload(priv->mc_io, 0, priv->mc_token,
			       DPNI_OFF_TX_L4_CSUM, enable);
	अगर (err) अणु
		netdev_err(priv->net_dev, "dpni_set_offload(TX_L4_CSUM) failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Perक्रमm a single release command to add buffers
 * to the specअगरied buffer pool
 */
अटल पूर्णांक dpaa2_eth_add_bufs(काष्ठा dpaa2_eth_priv *priv,
			      काष्ठा dpaa2_eth_channel *ch, u16 bpid)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	u64 buf_array[DPAA2_ETH_BUFS_PER_CMD];
	काष्ठा page *page;
	dma_addr_t addr;
	पूर्णांक retries = 0;
	पूर्णांक i, err;

	क्रम (i = 0; i < DPAA2_ETH_BUFS_PER_CMD; i++) अणु
		/* Allocate buffer visible to WRIOP + skb shared info +
		 * alignment padding
		 */
		/* allocate one page क्रम each Rx buffer. WRIOP sees
		 * the entire page except क्रम a tailroom reserved क्रम
		 * skb shared info
		 */
		page = dev_alloc_pages(0);
		अगर (!page)
			जाओ err_alloc;

		addr = dma_map_page(dev, page, 0, priv->rx_buf_size,
				    DMA_BIसूचीECTIONAL);
		अगर (unlikely(dma_mapping_error(dev, addr)))
			जाओ err_map;

		buf_array[i] = addr;

		/* tracing poपूर्णांक */
		trace_dpaa2_eth_buf_seed(priv->net_dev,
					 page, DPAA2_ETH_RX_BUF_RAW_SIZE,
					 addr, priv->rx_buf_size,
					 bpid);
	पूर्ण

release_bufs:
	/* In हाल the portal is busy, retry until successful */
	जबतक ((err = dpaa2_io_service_release(ch->dpio, bpid,
					       buf_array, i)) == -EBUSY) अणु
		अगर (retries++ >= DPAA2_ETH_SWP_BUSY_RETRIES)
			अवरोध;
		cpu_relax();
	पूर्ण

	/* If release command failed, clean up and bail out;
	 * not much अन्यथा we can करो about it
	 */
	अगर (err) अणु
		dpaa2_eth_मुक्त_bufs(priv, buf_array, i);
		वापस 0;
	पूर्ण

	वापस i;

err_map:
	__मुक्त_pages(page, 0);
err_alloc:
	/* If we managed to allocate at least some buffers,
	 * release them to hardware
	 */
	अगर (i)
		जाओ release_bufs;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_seed_pool(काष्ठा dpaa2_eth_priv *priv, u16 bpid)
अणु
	पूर्णांक i, j;
	पूर्णांक new_count;

	क्रम (j = 0; j < priv->num_channels; j++) अणु
		क्रम (i = 0; i < DPAA2_ETH_NUM_BUFS;
		     i += DPAA2_ETH_BUFS_PER_CMD) अणु
			new_count = dpaa2_eth_add_bufs(priv, priv->channel[j], bpid);
			priv->channel[j]->buf_count += new_count;

			अगर (new_count < DPAA2_ETH_BUFS_PER_CMD) अणु
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Drain the specअगरied number of buffers from the DPNI's निजी buffer pool.
 * @count must not exceeed DPAA2_ETH_BUFS_PER_CMD
 */
अटल व्योम dpaa2_eth_drain_bufs(काष्ठा dpaa2_eth_priv *priv, पूर्णांक count)
अणु
	u64 buf_array[DPAA2_ETH_BUFS_PER_CMD];
	पूर्णांक retries = 0;
	पूर्णांक ret;

	करो अणु
		ret = dpaa2_io_service_acquire(शून्य, priv->bpid,
					       buf_array, count);
		अगर (ret < 0) अणु
			अगर (ret == -EBUSY &&
			    retries++ < DPAA2_ETH_SWP_BUSY_RETRIES)
				जारी;
			netdev_err(priv->net_dev, "dpaa2_io_service_acquire() failed\n");
			वापस;
		पूर्ण
		dpaa2_eth_मुक्त_bufs(priv, buf_array, ret);
		retries = 0;
	पूर्ण जबतक (ret);
पूर्ण

अटल व्योम dpaa2_eth_drain_pool(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक i;

	dpaa2_eth_drain_bufs(priv, DPAA2_ETH_BUFS_PER_CMD);
	dpaa2_eth_drain_bufs(priv, 1);

	क्रम (i = 0; i < priv->num_channels; i++)
		priv->channel[i]->buf_count = 0;
पूर्ण

/* Function is called from softirq context only, so we करोn't need to guard
 * the access to percpu count
 */
अटल पूर्णांक dpaa2_eth_refill_pool(काष्ठा dpaa2_eth_priv *priv,
				 काष्ठा dpaa2_eth_channel *ch,
				 u16 bpid)
अणु
	पूर्णांक new_count;

	अगर (likely(ch->buf_count >= DPAA2_ETH_REFILL_THRESH))
		वापस 0;

	करो अणु
		new_count = dpaa2_eth_add_bufs(priv, ch, bpid);
		अगर (unlikely(!new_count)) अणु
			/* Out of memory; पात क्रम now, we'll try later on */
			अवरोध;
		पूर्ण
		ch->buf_count += new_count;
	पूर्ण जबतक (ch->buf_count < DPAA2_ETH_NUM_BUFS);

	अगर (unlikely(ch->buf_count < DPAA2_ETH_NUM_BUFS))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम dpaa2_eth_sgt_cache_drain(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpaa2_eth_sgt_cache *sgt_cache;
	u16 count;
	पूर्णांक k, i;

	क्रम_each_possible_cpu(k) अणु
		sgt_cache = per_cpu_ptr(priv->sgt_cache, k);
		count = sgt_cache->count;

		क्रम (i = 0; i < count; i++)
			kमुक्त(sgt_cache->buf[i]);
		sgt_cache->count = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_eth_pull_channel(काष्ठा dpaa2_eth_channel *ch)
अणु
	पूर्णांक err;
	पूर्णांक dequeues = -1;

	/* Retry जबतक portal is busy */
	करो अणु
		err = dpaa2_io_service_pull_channel(ch->dpio, ch->ch_id,
						    ch->store);
		dequeues++;
		cpu_relax();
	पूर्ण जबतक (err == -EBUSY && dequeues < DPAA2_ETH_SWP_BUSY_RETRIES);

	ch->stats.dequeue_portal_busy += dequeues;
	अगर (unlikely(err))
		ch->stats.pull_err++;

	वापस err;
पूर्ण

/* NAPI poll routine
 *
 * Frames are dequeued from the QMan channel associated with this NAPI context.
 * Rx, Tx confirmation and (अगर configured) Rx error frames all count
 * towards the NAPI budget.
 */
अटल पूर्णांक dpaa2_eth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा dpaa2_eth_channel *ch;
	काष्ठा dpaa2_eth_priv *priv;
	पूर्णांक rx_cleaned = 0, txconf_cleaned = 0;
	काष्ठा dpaa2_eth_fq *fq, *txc_fq = शून्य;
	काष्ठा netdev_queue *nq;
	पूर्णांक store_cleaned, work_करोne;
	काष्ठा list_head rx_list;
	पूर्णांक retries = 0;
	u16 flowid;
	पूर्णांक err;

	ch = container_of(napi, काष्ठा dpaa2_eth_channel, napi);
	ch->xdp.res = 0;
	priv = ch->priv;

	INIT_LIST_HEAD(&rx_list);
	ch->rx_list = &rx_list;

	करो अणु
		err = dpaa2_eth_pull_channel(ch);
		अगर (unlikely(err))
			अवरोध;

		/* Refill pool अगर appropriate */
		dpaa2_eth_refill_pool(priv, ch, priv->bpid);

		store_cleaned = dpaa2_eth_consume_frames(ch, &fq);
		अगर (store_cleaned <= 0)
			अवरोध;
		अगर (fq->type == DPAA2_RX_FQ) अणु
			rx_cleaned += store_cleaned;
			flowid = fq->flowid;
		पूर्ण अन्यथा अणु
			txconf_cleaned += store_cleaned;
			/* We have a single Tx conf FQ on this channel */
			txc_fq = fq;
		पूर्ण

		/* If we either consumed the whole NAPI budget with Rx frames
		 * or we reached the Tx confirmations threshold, we're करोne.
		 */
		अगर (rx_cleaned >= budget ||
		    txconf_cleaned >= DPAA2_ETH_TXCONF_PER_NAPI) अणु
			work_करोne = budget;
			जाओ out;
		पूर्ण
	पूर्ण जबतक (store_cleaned);

	/* We didn't consume the entire budget, so finish napi and
	 * re-enable data availability notअगरications
	 */
	napi_complete_करोne(napi, rx_cleaned);
	करो अणु
		err = dpaa2_io_service_rearm(ch->dpio, &ch->nctx);
		cpu_relax();
	पूर्ण जबतक (err == -EBUSY && retries++ < DPAA2_ETH_SWP_BUSY_RETRIES);
	WARN_ONCE(err, "CDAN notifications rearm failed on core %d",
		  ch->nctx.desired_cpu);

	work_करोne = max(rx_cleaned, 1);

out:
	netअगर_receive_skb_list(ch->rx_list);

	अगर (txc_fq && txc_fq->dq_frames) अणु
		nq = netdev_get_tx_queue(priv->net_dev, txc_fq->flowid);
		netdev_tx_completed_queue(nq, txc_fq->dq_frames,
					  txc_fq->dq_bytes);
		txc_fq->dq_frames = 0;
		txc_fq->dq_bytes = 0;
	पूर्ण

	अगर (ch->xdp.res & XDP_REसूचीECT)
		xdp_करो_flush_map();
	अन्यथा अगर (rx_cleaned && ch->xdp.res & XDP_TX)
		dpaa2_eth_xdp_tx_flush(priv, ch, &priv->fq[flowid]);

	वापस work_करोne;
पूर्ण

अटल व्योम dpaa2_eth_enable_ch_napi(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpaa2_eth_channel *ch;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		ch = priv->channel[i];
		napi_enable(&ch->napi);
	पूर्ण
पूर्ण

अटल व्योम dpaa2_eth_disable_ch_napi(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpaa2_eth_channel *ch;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		ch = priv->channel[i];
		napi_disable(&ch->napi);
	पूर्ण
पूर्ण

व्योम dpaa2_eth_set_rx_taildrop(काष्ठा dpaa2_eth_priv *priv,
			       bool tx_छोड़ो, bool pfc)
अणु
	काष्ठा dpni_taildrop td = अणु0पूर्ण;
	काष्ठा dpaa2_eth_fq *fq;
	पूर्णांक i, err;

	/* FQ taildrop: threshold is in bytes, per frame queue. Enabled अगर
	 * flow control is disabled (as it might पूर्णांकerfere with either the
	 * buffer pool depletion trigger क्रम छोड़ो frames or with the group
	 * congestion trigger क्रम PFC frames)
	 */
	td.enable = !tx_छोड़ो;
	अगर (priv->rx_fqtd_enabled == td.enable)
		जाओ set_cgtd;

	td.threshold = DPAA2_ETH_FQ_TAILDROP_THRESH;
	td.units = DPNI_CONGESTION_UNIT_BYTES;

	क्रम (i = 0; i < priv->num_fqs; i++) अणु
		fq = &priv->fq[i];
		अगर (fq->type != DPAA2_RX_FQ)
			जारी;
		err = dpni_set_taildrop(priv->mc_io, 0, priv->mc_token,
					DPNI_CP_QUEUE, DPNI_QUEUE_RX,
					fq->tc, fq->flowid, &td);
		अगर (err) अणु
			netdev_err(priv->net_dev,
				   "dpni_set_taildrop(FQ) failed\n");
			वापस;
		पूर्ण
	पूर्ण

	priv->rx_fqtd_enabled = td.enable;

set_cgtd:
	/* Congestion group taildrop: threshold is in frames, per group
	 * of FQs beदीर्घing to the same traffic class
	 * Enabled अगर general Tx छोड़ो disabled or अगर PFCs are enabled
	 * (congestion group threhsold क्रम PFC generation is lower than the
	 * CG taildrop threshold, so it won't पूर्णांकerfere with it; we also
	 * want frames in non-PFC enabled traffic classes to be kept in check)
	 */
	td.enable = !tx_छोड़ो || pfc;
	अगर (priv->rx_cgtd_enabled == td.enable)
		वापस;

	td.threshold = DPAA2_ETH_CG_TAILDROP_THRESH(priv);
	td.units = DPNI_CONGESTION_UNIT_FRAMES;
	क्रम (i = 0; i < dpaa2_eth_tc_count(priv); i++) अणु
		err = dpni_set_taildrop(priv->mc_io, 0, priv->mc_token,
					DPNI_CP_GROUP, DPNI_QUEUE_RX,
					i, 0, &td);
		अगर (err) अणु
			netdev_err(priv->net_dev,
				   "dpni_set_taildrop(CG) failed\n");
			वापस;
		पूर्ण
	पूर्ण

	priv->rx_cgtd_enabled = td.enable;
पूर्ण

अटल पूर्णांक dpaa2_eth_link_state_update(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpni_link_state state = अणु0पूर्ण;
	bool tx_छोड़ो;
	पूर्णांक err;

	err = dpni_get_link_state(priv->mc_io, 0, priv->mc_token, &state);
	अगर (unlikely(err)) अणु
		netdev_err(priv->net_dev,
			   "dpni_get_link_state() failed\n");
		वापस err;
	पूर्ण

	/* If Tx छोड़ो frame settings have changed, we need to update
	 * Rx FQ taildrop configuration as well. We configure taildrop
	 * only when छोड़ो frame generation is disabled.
	 */
	tx_छोड़ो = dpaa2_eth_tx_छोड़ो_enabled(state.options);
	dpaa2_eth_set_rx_taildrop(priv, tx_छोड़ो, priv->pfc_enabled);

	/* When we manage the MAC/PHY using phylink there is no need
	 * to manually update the netअगर_carrier.
	 */
	अगर (dpaa2_eth_is_type_phy(priv))
		जाओ out;

	/* Chech link state; speed / duplex changes are not treated yet */
	अगर (priv->link_state.up == state.up)
		जाओ out;

	अगर (state.up) अणु
		netअगर_carrier_on(priv->net_dev);
		netअगर_tx_start_all_queues(priv->net_dev);
	पूर्ण अन्यथा अणु
		netअगर_tx_stop_all_queues(priv->net_dev);
		netअगर_carrier_off(priv->net_dev);
	पूर्ण

	netdev_info(priv->net_dev, "Link Event: state %s\n",
		    state.up ? "up" : "down");

out:
	priv->link_state = state;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक err;

	err = dpaa2_eth_seed_pool(priv, priv->bpid);
	अगर (err) अणु
		/* Not much to करो; the buffer pool, though not filled up,
		 * may still contain some buffers which would enable us
		 * to limp on.
		 */
		netdev_err(net_dev, "Buffer seeding failed for DPBP %d (bpid=%d)\n",
			   priv->dpbp_dev->obj_desc.id, priv->bpid);
	पूर्ण

	अगर (!dpaa2_eth_is_type_phy(priv)) अणु
		/* We'll only start the txqs when the link is actually पढ़ोy;
		 * make sure we करोn't race against the link up notअगरication,
		 * which may come immediately after dpni_enable();
		 */
		netअगर_tx_stop_all_queues(net_dev);

		/* Also, explicitly set carrier off, otherwise
		 * netअगर_carrier_ok() will वापस true and cause 'ip link show'
		 * to report the LOWER_UP flag, even though the link
		 * notअगरication wasn't even received.
		 */
		netअगर_carrier_off(net_dev);
	पूर्ण
	dpaa2_eth_enable_ch_napi(priv);

	err = dpni_enable(priv->mc_io, 0, priv->mc_token);
	अगर (err < 0) अणु
		netdev_err(net_dev, "dpni_enable() failed\n");
		जाओ enable_err;
	पूर्ण

	अगर (dpaa2_eth_is_type_phy(priv))
		phylink_start(priv->mac->phylink);

	वापस 0;

enable_err:
	dpaa2_eth_disable_ch_napi(priv);
	dpaa2_eth_drain_pool(priv);
	वापस err;
पूर्ण

/* Total number of in-flight frames on ingress queues */
अटल u32 dpaa2_eth_ingress_fq_count(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpaa2_eth_fq *fq;
	u32 fcnt = 0, bcnt = 0, total = 0;
	पूर्णांक i, err;

	क्रम (i = 0; i < priv->num_fqs; i++) अणु
		fq = &priv->fq[i];
		err = dpaa2_io_query_fq_count(शून्य, fq->fqid, &fcnt, &bcnt);
		अगर (err) अणु
			netdev_warn(priv->net_dev, "query_fq_count failed");
			अवरोध;
		पूर्ण
		total += fcnt;
	पूर्ण

	वापस total;
पूर्ण

अटल व्योम dpaa2_eth_रुको_क्रम_ingress_fq_empty(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक retries = 10;
	u32 pending;

	करो अणु
		pending = dpaa2_eth_ingress_fq_count(priv);
		अगर (pending)
			msleep(100);
	पूर्ण जबतक (pending && --retries);
पूर्ण

#घोषणा DPNI_TX_PENDING_VER_MAJOR	7
#घोषणा DPNI_TX_PENDING_VER_MINOR	13
अटल व्योम dpaa2_eth_रुको_क्रम_egress_fq_empty(काष्ठा dpaa2_eth_priv *priv)
अणु
	जोड़ dpni_statistics stats;
	पूर्णांक retries = 10;
	पूर्णांक err;

	अगर (dpaa2_eth_cmp_dpni_ver(priv, DPNI_TX_PENDING_VER_MAJOR,
				   DPNI_TX_PENDING_VER_MINOR) < 0)
		जाओ out;

	करो अणु
		err = dpni_get_statistics(priv->mc_io, 0, priv->mc_token, 6,
					  &stats);
		अगर (err)
			जाओ out;
		अगर (stats.page_6.tx_pending_frames == 0)
			वापस;
	पूर्ण जबतक (--retries);

out:
	msleep(500);
पूर्ण

अटल पूर्णांक dpaa2_eth_stop(काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक dpni_enabled = 0;
	पूर्णांक retries = 10;

	अगर (dpaa2_eth_is_type_phy(priv)) अणु
		phylink_stop(priv->mac->phylink);
	पूर्ण अन्यथा अणु
		netअगर_tx_stop_all_queues(net_dev);
		netअगर_carrier_off(net_dev);
	पूर्ण

	/* On dpni_disable(), the MC firmware will:
	 * - stop MAC Rx and रुको क्रम all Rx frames to be enqueued to software
	 * - cut off WRIOP dequeues from egress FQs and रुको until transmission
	 * of all in flight Tx frames is finished (and corresponding Tx conf
	 * frames are enqueued back to software)
	 *
	 * Beक्रमe calling dpni_disable(), we रुको क्रम all Tx frames to arrive
	 * on WRIOP. After it finishes, रुको until all reमुख्यing frames on Rx
	 * and Tx conf queues are consumed on NAPI poll.
	 */
	dpaa2_eth_रुको_क्रम_egress_fq_empty(priv);

	करो अणु
		dpni_disable(priv->mc_io, 0, priv->mc_token);
		dpni_is_enabled(priv->mc_io, 0, priv->mc_token, &dpni_enabled);
		अगर (dpni_enabled)
			/* Allow the hardware some slack */
			msleep(100);
	पूर्ण जबतक (dpni_enabled && --retries);
	अगर (!retries) अणु
		netdev_warn(net_dev, "Retry count exceeded disabling DPNI\n");
		/* Must go on and disable NAPI nonetheless, so we करोn't crash at
		 * the next "ifconfig up"
		 */
	पूर्ण

	dpaa2_eth_रुको_क्रम_ingress_fq_empty(priv);
	dpaa2_eth_disable_ch_napi(priv);

	/* Empty the buffer pool */
	dpaa2_eth_drain_pool(priv);

	/* Empty the Scatter-Gather Buffer cache */
	dpaa2_eth_sgt_cache_drain(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_addr(काष्ठा net_device *net_dev, व्योम *addr)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा device *dev = net_dev->dev.parent;
	पूर्णांक err;

	err = eth_mac_addr(net_dev, addr);
	अगर (err < 0) अणु
		dev_err(dev, "eth_mac_addr() failed (%d)\n", err);
		वापस err;
	पूर्ण

	err = dpni_set_primary_mac_addr(priv->mc_io, 0, priv->mc_token,
					net_dev->dev_addr);
	अगर (err) अणु
		dev_err(dev, "dpni_set_primary_mac_addr() failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/** Fill in counters मुख्यtained by the GPP driver. These may be dअगरferent from
 * the hardware counters obtained by ethtool.
 */
अटल व्योम dpaa2_eth_get_stats(काष्ठा net_device *net_dev,
				काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा rtnl_link_stats64 *percpu_stats;
	u64 *cpustats;
	u64 *netstats = (u64 *)stats;
	पूर्णांक i, j;
	पूर्णांक num = माप(काष्ठा rtnl_link_stats64) / माप(u64);

	क्रम_each_possible_cpu(i) अणु
		percpu_stats = per_cpu_ptr(priv->percpu_stats, i);
		cpustats = (u64 *)percpu_stats;
		क्रम (j = 0; j < num; j++)
			netstats[j] += cpustats[j];
	पूर्ण
पूर्ण

/* Copy mac unicast addresses from @net_dev to @priv.
 * Its sole purpose is to make dpaa2_eth_set_rx_mode() more पढ़ोable.
 */
अटल व्योम dpaa2_eth_add_uc_hw_addr(स्थिर काष्ठा net_device *net_dev,
				     काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक err;

	netdev_क्रम_each_uc_addr(ha, net_dev) अणु
		err = dpni_add_mac_addr(priv->mc_io, 0, priv->mc_token,
					ha->addr);
		अगर (err)
			netdev_warn(priv->net_dev,
				    "Could not add ucast MAC %pM to the filtering table (err %d)\n",
				    ha->addr, err);
	पूर्ण
पूर्ण

/* Copy mac multicast addresses from @net_dev to @priv
 * Its sole purpose is to make dpaa2_eth_set_rx_mode() more पढ़ोable.
 */
अटल व्योम dpaa2_eth_add_mc_hw_addr(स्थिर काष्ठा net_device *net_dev,
				     काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक err;

	netdev_क्रम_each_mc_addr(ha, net_dev) अणु
		err = dpni_add_mac_addr(priv->mc_io, 0, priv->mc_token,
					ha->addr);
		अगर (err)
			netdev_warn(priv->net_dev,
				    "Could not add mcast MAC %pM to the filtering table (err %d)\n",
				    ha->addr, err);
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_eth_rx_add_vid(काष्ठा net_device *net_dev,
				__be16 vlan_proto, u16 vid)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक err;

	err = dpni_add_vlan_id(priv->mc_io, 0, priv->mc_token,
			       vid, 0, 0, 0);

	अगर (err) अणु
		netdev_warn(priv->net_dev,
			    "Could not add the vlan id %u\n",
			    vid);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_rx_समाप्त_vid(काष्ठा net_device *net_dev,
				 __be16 vlan_proto, u16 vid)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक err;

	err = dpni_हटाओ_vlan_id(priv->mc_io, 0, priv->mc_token, vid);

	अगर (err) अणु
		netdev_warn(priv->net_dev,
			    "Could not remove the vlan id %u\n",
			    vid);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpaa2_eth_set_rx_mode(काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक uc_count = netdev_uc_count(net_dev);
	पूर्णांक mc_count = netdev_mc_count(net_dev);
	u8 max_mac = priv->dpni_attrs.mac_filter_entries;
	u32 options = priv->dpni_attrs.options;
	u16 mc_token = priv->mc_token;
	काष्ठा fsl_mc_io *mc_io = priv->mc_io;
	पूर्णांक err;

	/* Basic sanity checks; these probably indicate a misconfiguration */
	अगर (options & DPNI_OPT_NO_MAC_FILTER && max_mac != 0)
		netdev_info(net_dev,
			    "mac_filter_entries=%d, DPNI_OPT_NO_MAC_FILTER option must be disabled\n",
			    max_mac);

	/* Force promiscuous अगर the uc or mc counts exceed our capabilities. */
	अगर (uc_count > max_mac) अणु
		netdev_info(net_dev,
			    "Unicast addr count reached %d, max allowed is %d; forcing promisc\n",
			    uc_count, max_mac);
		जाओ क्रमce_promisc;
	पूर्ण
	अगर (mc_count + uc_count > max_mac) अणु
		netdev_info(net_dev,
			    "Unicast + multicast addr count reached %d, max allowed is %d; forcing promisc\n",
			    uc_count + mc_count, max_mac);
		जाओ क्रमce_mc_promisc;
	पूर्ण

	/* Adjust promisc settings due to flag combinations */
	अगर (net_dev->flags & IFF_PROMISC)
		जाओ क्रमce_promisc;
	अगर (net_dev->flags & IFF_ALLMULTI) अणु
		/* First, rebuild unicast filtering table. This should be करोne
		 * in promisc mode, in order to aव्योम frame loss जबतक we
		 * progressively add entries to the table.
		 * We करोn't know whether we had been in promisc alपढ़ोy, and
		 * making an MC call to find out is expensive; so set uc promisc
		 * nonetheless.
		 */
		err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 1);
		अगर (err)
			netdev_warn(net_dev, "Can't set uc promisc\n");

		/* Actual uc table reस्थिरruction. */
		err = dpni_clear_mac_filters(mc_io, 0, mc_token, 1, 0);
		अगर (err)
			netdev_warn(net_dev, "Can't clear uc filters\n");
		dpaa2_eth_add_uc_hw_addr(net_dev, priv);

		/* Finally, clear uc promisc and set mc promisc as requested. */
		err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 0);
		अगर (err)
			netdev_warn(net_dev, "Can't clear uc promisc\n");
		जाओ क्रमce_mc_promisc;
	पूर्ण

	/* Neither unicast, nor multicast promisc will be on... eventually.
	 * For now, rebuild mac filtering tables जबतक क्रमcing both of them on.
	 */
	err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 1);
	अगर (err)
		netdev_warn(net_dev, "Can't set uc promisc (%d)\n", err);
	err = dpni_set_multicast_promisc(mc_io, 0, mc_token, 1);
	अगर (err)
		netdev_warn(net_dev, "Can't set mc promisc (%d)\n", err);

	/* Actual mac filtering tables reस्थिरruction */
	err = dpni_clear_mac_filters(mc_io, 0, mc_token, 1, 1);
	अगर (err)
		netdev_warn(net_dev, "Can't clear mac filters\n");
	dpaa2_eth_add_mc_hw_addr(net_dev, priv);
	dpaa2_eth_add_uc_hw_addr(net_dev, priv);

	/* Now we can clear both ucast and mcast promisc, without risking
	 * to drop legitimate frames anymore.
	 */
	err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 0);
	अगर (err)
		netdev_warn(net_dev, "Can't clear ucast promisc\n");
	err = dpni_set_multicast_promisc(mc_io, 0, mc_token, 0);
	अगर (err)
		netdev_warn(net_dev, "Can't clear mcast promisc\n");

	वापस;

क्रमce_promisc:
	err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 1);
	अगर (err)
		netdev_warn(net_dev, "Can't set ucast promisc\n");
क्रमce_mc_promisc:
	err = dpni_set_multicast_promisc(mc_io, 0, mc_token, 1);
	अगर (err)
		netdev_warn(net_dev, "Can't set mcast promisc\n");
पूर्ण

अटल पूर्णांक dpaa2_eth_set_features(काष्ठा net_device *net_dev,
				  netdev_features_t features)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	netdev_features_t changed = features ^ net_dev->features;
	bool enable;
	पूर्णांक err;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
		enable = !!(features & NETIF_F_HW_VLAN_CTAG_FILTER);
		err = dpaa2_eth_set_rx_vlan_filtering(priv, enable);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (changed & NETIF_F_RXCSUM) अणु
		enable = !!(features & NETIF_F_RXCSUM);
		err = dpaa2_eth_set_rx_csum(priv, enable);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (changed & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) अणु
		enable = !!(features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM));
		err = dpaa2_eth_set_tx_csum(priv, enable);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_ts_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(dev);
	काष्ठा hwtstamp_config config;

	अगर (!dpaa2_ptp)
		वापस -EINVAL;

	अगर (copy_from_user(&config, rq->अगरr_data, माप(config)))
		वापस -EFAULT;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
	हाल HWTSTAMP_TX_ON:
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
		priv->tx_tstamp_type = config.tx_type;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	अगर (config.rx_filter == HWTSTAMP_FILTER_NONE) अणु
		priv->rx_tstamp = false;
	पूर्ण अन्यथा अणु
		priv->rx_tstamp = true;
		/* TS is set क्रम all frame types, not only those requested */
		config.rx_filter = HWTSTAMP_FILTER_ALL;
	पूर्ण

	वापस copy_to_user(rq->अगरr_data, &config, माप(config)) ?
			-EFAULT : 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(dev);

	अगर (cmd == SIOCSHWTSTAMP)
		वापस dpaa2_eth_ts_ioctl(dev, rq, cmd);

	अगर (dpaa2_eth_is_type_phy(priv))
		वापस phylink_mii_ioctl(priv->mac->phylink, rq, cmd);

	वापस -EOPNOTSUPP;
पूर्ण

अटल bool xdp_mtu_valid(काष्ठा dpaa2_eth_priv *priv, पूर्णांक mtu)
अणु
	पूर्णांक mfl, linear_mfl;

	mfl = DPAA2_ETH_L2_MAX_FRM(mtu);
	linear_mfl = priv->rx_buf_size - DPAA2_ETH_RX_HWA_SIZE -
		     dpaa2_eth_rx_head_room(priv) - XDP_PACKET_HEADROOM;

	अगर (mfl > linear_mfl) अणु
		netdev_warn(priv->net_dev, "Maximum MTU for XDP is %d\n",
			    linear_mfl - VLAN_ETH_HLEN);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_rx_mfl(काष्ठा dpaa2_eth_priv *priv, पूर्णांक mtu, bool has_xdp)
अणु
	पूर्णांक mfl, err;

	/* We enक्रमce a maximum Rx frame length based on MTU only अगर we have
	 * an XDP program attached (in order to aव्योम Rx S/G frames).
	 * Otherwise, we accept all incoming frames as दीर्घ as they are not
	 * larger than maximum size supported in hardware
	 */
	अगर (has_xdp)
		mfl = DPAA2_ETH_L2_MAX_FRM(mtu);
	अन्यथा
		mfl = DPAA2_ETH_MFL;

	err = dpni_set_max_frame_length(priv->mc_io, 0, priv->mc_token, mfl);
	अगर (err) अणु
		netdev_err(priv->net_dev, "dpni_set_max_frame_length failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	अगर (!priv->xdp_prog)
		जाओ out;

	अगर (!xdp_mtu_valid(priv, new_mtu))
		वापस -EINVAL;

	err = dpaa2_eth_set_rx_mfl(priv, new_mtu, true);
	अगर (err)
		वापस err;

out:
	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_update_rx_buffer_headroom(काष्ठा dpaa2_eth_priv *priv, bool has_xdp)
अणु
	काष्ठा dpni_buffer_layout buf_layout = अणु0पूर्ण;
	पूर्णांक err;

	err = dpni_get_buffer_layout(priv->mc_io, 0, priv->mc_token,
				     DPNI_QUEUE_RX, &buf_layout);
	अगर (err) अणु
		netdev_err(priv->net_dev, "dpni_get_buffer_layout failed\n");
		वापस err;
	पूर्ण

	/* Reserve extra headroom क्रम XDP header size changes */
	buf_layout.data_head_room = dpaa2_eth_rx_head_room(priv) +
				    (has_xdp ? XDP_PACKET_HEADROOM : 0);
	buf_layout.options = DPNI_BUF_LAYOUT_OPT_DATA_HEAD_ROOM;
	err = dpni_set_buffer_layout(priv->mc_io, 0, priv->mc_token,
				     DPNI_QUEUE_RX, &buf_layout);
	अगर (err) अणु
		netdev_err(priv->net_dev, "dpni_set_buffer_layout failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_setup_xdp(काष्ठा net_device *dev, काष्ठा bpf_prog *prog)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(dev);
	काष्ठा dpaa2_eth_channel *ch;
	काष्ठा bpf_prog *old;
	bool up, need_update;
	पूर्णांक i, err;

	अगर (prog && !xdp_mtu_valid(priv, dev->mtu))
		वापस -EINVAL;

	अगर (prog)
		bpf_prog_add(prog, priv->num_channels);

	up = netअगर_running(dev);
	need_update = (!!priv->xdp_prog != !!prog);

	अगर (up)
		dpaa2_eth_stop(dev);

	/* While in xdp mode, enक्रमce a maximum Rx frame size based on MTU.
	 * Also, when चयनing between xdp/non-xdp modes we need to reconfigure
	 * our Rx buffer layout. Buffer pool was drained on dpaa2_eth_stop,
	 * so we are sure no old क्रमmat buffers will be used from now on.
	 */
	अगर (need_update) अणु
		err = dpaa2_eth_set_rx_mfl(priv, dev->mtu, !!prog);
		अगर (err)
			जाओ out_err;
		err = dpaa2_eth_update_rx_buffer_headroom(priv, !!prog);
		अगर (err)
			जाओ out_err;
	पूर्ण

	old = xchg(&priv->xdp_prog, prog);
	अगर (old)
		bpf_prog_put(old);

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		ch = priv->channel[i];
		old = xchg(&ch->xdp.prog, prog);
		अगर (old)
			bpf_prog_put(old);
	पूर्ण

	अगर (up) अणु
		err = dpaa2_eth_खोलो(dev);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;

out_err:
	अगर (prog)
		bpf_prog_sub(prog, priv->num_channels);
	अगर (up)
		dpaa2_eth_खोलो(dev);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_eth_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस dpaa2_eth_setup_xdp(dev, xdp->prog);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_xdp_create_fd(काष्ठा net_device *net_dev,
				   काष्ठा xdp_frame *xdpf,
				   काष्ठा dpaa2_fd *fd)
अणु
	काष्ठा device *dev = net_dev->dev.parent;
	अचिन्हित पूर्णांक needed_headroom;
	काष्ठा dpaa2_eth_swa *swa;
	व्योम *buffer_start, *aligned_start;
	dma_addr_t addr;

	/* We require a minimum headroom to be able to transmit the frame.
	 * Otherwise वापस an error and let the original net_device handle it
	 */
	needed_headroom = dpaa2_eth_needed_headroom(शून्य);
	अगर (xdpf->headroom < needed_headroom)
		वापस -EINVAL;

	/* Setup the FD fields */
	स_रखो(fd, 0, माप(*fd));

	/* Align FD address, अगर possible */
	buffer_start = xdpf->data - needed_headroom;
	aligned_start = PTR_ALIGN(buffer_start - DPAA2_ETH_TX_BUF_ALIGN,
				  DPAA2_ETH_TX_BUF_ALIGN);
	अगर (aligned_start >= xdpf->data - xdpf->headroom)
		buffer_start = aligned_start;

	swa = (काष्ठा dpaa2_eth_swa *)buffer_start;
	/* fill in necessary fields here */
	swa->type = DPAA2_ETH_SWA_XDP;
	swa->xdp.dma_size = xdpf->data + xdpf->len - buffer_start;
	swa->xdp.xdpf = xdpf;

	addr = dma_map_single(dev, buffer_start,
			      swa->xdp.dma_size,
			      DMA_BIसूचीECTIONAL);
	अगर (unlikely(dma_mapping_error(dev, addr)))
		वापस -ENOMEM;

	dpaa2_fd_set_addr(fd, addr);
	dpaa2_fd_set_offset(fd, xdpf->data - buffer_start);
	dpaa2_fd_set_len(fd, xdpf->len);
	dpaa2_fd_set_क्रमmat(fd, dpaa2_fd_single);
	dpaa2_fd_set_ctrl(fd, FD_CTRL_PTA);

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_xdp_xmit(काष्ठा net_device *net_dev, पूर्णांक n,
			      काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा dpaa2_eth_xdp_fds *xdp_redirect_fds;
	काष्ठा rtnl_link_stats64 *percpu_stats;
	काष्ठा dpaa2_eth_fq *fq;
	काष्ठा dpaa2_fd *fds;
	पूर्णांक enqueued, i, err;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	अगर (!netअगर_running(net_dev))
		वापस -ENETDOWN;

	fq = &priv->fq[smp_processor_id()];
	xdp_redirect_fds = &fq->xdp_redirect_fds;
	fds = xdp_redirect_fds->fds;

	percpu_stats = this_cpu_ptr(priv->percpu_stats);

	/* create a FD क्रम each xdp_frame in the list received */
	क्रम (i = 0; i < n; i++) अणु
		err = dpaa2_eth_xdp_create_fd(net_dev, frames[i], &fds[i]);
		अगर (err)
			अवरोध;
	पूर्ण
	xdp_redirect_fds->num = i;

	/* enqueue all the frame descriptors */
	enqueued = dpaa2_eth_xdp_flush(priv, fq, xdp_redirect_fds);

	/* update statistics */
	percpu_stats->tx_packets += enqueued;
	क्रम (i = 0; i < enqueued; i++)
		percpu_stats->tx_bytes += dpaa2_fd_get_len(&fds[i]);

	वापस enqueued;
पूर्ण

अटल पूर्णांक update_xps(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा net_device *net_dev = priv->net_dev;
	काष्ठा cpumask xps_mask;
	काष्ठा dpaa2_eth_fq *fq;
	पूर्णांक i, num_queues, netdev_queues;
	पूर्णांक err = 0;

	num_queues = dpaa2_eth_queue_count(priv);
	netdev_queues = (net_dev->num_tc ? : 1) * num_queues;

	/* The first <num_queues> entries in priv->fq array are Tx/Tx conf
	 * queues, so only process those
	 */
	क्रम (i = 0; i < netdev_queues; i++) अणु
		fq = &priv->fq[i % num_queues];

		cpumask_clear(&xps_mask);
		cpumask_set_cpu(fq->target_cpu, &xps_mask);

		err = netअगर_set_xps_queue(net_dev, &xps_mask, i);
		अगर (err) अणु
			netdev_warn_once(net_dev, "Error setting XPS queue\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_eth_setup_mqprio(काष्ठा net_device *net_dev,
				  काष्ठा tc_mqprio_qopt *mqprio)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u8 num_tc, num_queues;
	पूर्णांक i;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	num_queues = dpaa2_eth_queue_count(priv);
	num_tc = mqprio->num_tc;

	अगर (num_tc == net_dev->num_tc)
		वापस 0;

	अगर (num_tc  > dpaa2_eth_tc_count(priv)) अणु
		netdev_err(net_dev, "Max %d traffic classes supported\n",
			   dpaa2_eth_tc_count(priv));
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!num_tc) अणु
		netdev_reset_tc(net_dev);
		netअगर_set_real_num_tx_queues(net_dev, num_queues);
		जाओ out;
	पूर्ण

	netdev_set_num_tc(net_dev, num_tc);
	netअगर_set_real_num_tx_queues(net_dev, num_tc * num_queues);

	क्रम (i = 0; i < num_tc; i++)
		netdev_set_tc_queue(net_dev, i, num_queues, i * num_queues);

out:
	update_xps(priv);

	वापस 0;
पूर्ण

#घोषणा bps_to_mbits(rate) (भाग_u64((rate), 1000000) * 8)

अटल पूर्णांक dpaa2_eth_setup_tbf(काष्ठा net_device *net_dev, काष्ठा tc_tbf_qopt_offload *p)
अणु
	काष्ठा tc_tbf_qopt_offload_replace_params *cfg = &p->replace_params;
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा dpni_tx_shaping_cfg tx_cr_shaper = अणु 0 पूर्ण;
	काष्ठा dpni_tx_shaping_cfg tx_er_shaper = अणु 0 पूर्ण;
	पूर्णांक err;

	अगर (p->command == TC_TBF_STATS)
		वापस -EOPNOTSUPP;

	/* Only per port Tx shaping */
	अगर (p->parent != TC_H_ROOT)
		वापस -EOPNOTSUPP;

	अगर (p->command == TC_TBF_REPLACE) अणु
		अगर (cfg->max_size > DPAA2_ETH_MAX_BURST_SIZE) अणु
			netdev_err(net_dev, "burst size cannot be greater than %d\n",
				   DPAA2_ETH_MAX_BURST_SIZE);
			वापस -EINVAL;
		पूर्ण

		tx_cr_shaper.max_burst_size = cfg->max_size;
		/* The TBF पूर्णांकerface is in bytes/s, whereas DPAA2 expects the
		 * rate in Mbits/s
		 */
		tx_cr_shaper.rate_limit = bps_to_mbits(cfg->rate.rate_bytes_ps);
	पूर्ण

	err = dpni_set_tx_shaping(priv->mc_io, 0, priv->mc_token, &tx_cr_shaper,
				  &tx_er_shaper, 0);
	अगर (err) अणु
		netdev_err(net_dev, "dpni_set_tx_shaping() = %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_setup_tc(काष्ठा net_device *net_dev,
			      क्रमागत tc_setup_type type, व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_QDISC_MQPRIO:
		वापस dpaa2_eth_setup_mqprio(net_dev, type_data);
	हाल TC_SETUP_QDISC_TBF:
		वापस dpaa2_eth_setup_tbf(net_dev, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops dpaa2_eth_ops = अणु
	.nकरो_खोलो = dpaa2_eth_खोलो,
	.nकरो_start_xmit = dpaa2_eth_tx,
	.nकरो_stop = dpaa2_eth_stop,
	.nकरो_set_mac_address = dpaa2_eth_set_addr,
	.nकरो_get_stats64 = dpaa2_eth_get_stats,
	.nकरो_set_rx_mode = dpaa2_eth_set_rx_mode,
	.nकरो_set_features = dpaa2_eth_set_features,
	.nकरो_करो_ioctl = dpaa2_eth_ioctl,
	.nकरो_change_mtu = dpaa2_eth_change_mtu,
	.nकरो_bpf = dpaa2_eth_xdp,
	.nकरो_xdp_xmit = dpaa2_eth_xdp_xmit,
	.nकरो_setup_tc = dpaa2_eth_setup_tc,
	.nकरो_vlan_rx_add_vid = dpaa2_eth_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = dpaa2_eth_rx_समाप्त_vid
पूर्ण;

अटल व्योम dpaa2_eth_cdan_cb(काष्ठा dpaa2_io_notअगरication_ctx *ctx)
अणु
	काष्ठा dpaa2_eth_channel *ch;

	ch = container_of(ctx, काष्ठा dpaa2_eth_channel, nctx);

	/* Update NAPI statistics */
	ch->stats.cdan++;

	napi_schedule(&ch->napi);
पूर्ण

/* Allocate and configure a DPCON object */
अटल काष्ठा fsl_mc_device *dpaa2_eth_setup_dpcon(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा fsl_mc_device *dpcon;
	काष्ठा device *dev = priv->net_dev->dev.parent;
	पूर्णांक err;

	err = fsl_mc_object_allocate(to_fsl_mc_device(dev),
				     FSL_MC_POOL_DPCON, &dpcon);
	अगर (err) अणु
		अगर (err == -ENXIO)
			err = -EPROBE_DEFER;
		अन्यथा
			dev_info(dev, "Not enough DPCONs, will go on as-is\n");
		वापस ERR_PTR(err);
	पूर्ण

	err = dpcon_खोलो(priv->mc_io, 0, dpcon->obj_desc.id, &dpcon->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpcon_open() failed\n");
		जाओ मुक्त;
	पूर्ण

	err = dpcon_reset(priv->mc_io, 0, dpcon->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpcon_reset() failed\n");
		जाओ बंद;
	पूर्ण

	err = dpcon_enable(priv->mc_io, 0, dpcon->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpcon_enable() failed\n");
		जाओ बंद;
	पूर्ण

	वापस dpcon;

बंद:
	dpcon_बंद(priv->mc_io, 0, dpcon->mc_handle);
मुक्त:
	fsl_mc_object_मुक्त(dpcon);

	वापस ERR_PTR(err);
पूर्ण

अटल व्योम dpaa2_eth_मुक्त_dpcon(काष्ठा dpaa2_eth_priv *priv,
				 काष्ठा fsl_mc_device *dpcon)
अणु
	dpcon_disable(priv->mc_io, 0, dpcon->mc_handle);
	dpcon_बंद(priv->mc_io, 0, dpcon->mc_handle);
	fsl_mc_object_मुक्त(dpcon);
पूर्ण

अटल काष्ठा dpaa2_eth_channel *dpaa2_eth_alloc_channel(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpaa2_eth_channel *channel;
	काष्ठा dpcon_attr attr;
	काष्ठा device *dev = priv->net_dev->dev.parent;
	पूर्णांक err;

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस शून्य;

	channel->dpcon = dpaa2_eth_setup_dpcon(priv);
	अगर (IS_ERR(channel->dpcon)) अणु
		err = PTR_ERR(channel->dpcon);
		जाओ err_setup;
	पूर्ण

	err = dpcon_get_attributes(priv->mc_io, 0, channel->dpcon->mc_handle,
				   &attr);
	अगर (err) अणु
		dev_err(dev, "dpcon_get_attributes() failed\n");
		जाओ err_get_attr;
	पूर्ण

	channel->dpcon_id = attr.id;
	channel->ch_id = attr.qbman_ch_id;
	channel->priv = priv;

	वापस channel;

err_get_attr:
	dpaa2_eth_मुक्त_dpcon(priv, channel->dpcon);
err_setup:
	kमुक्त(channel);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम dpaa2_eth_मुक्त_channel(काष्ठा dpaa2_eth_priv *priv,
				   काष्ठा dpaa2_eth_channel *channel)
अणु
	dpaa2_eth_मुक्त_dpcon(priv, channel->dpcon);
	kमुक्त(channel);
पूर्ण

/* DPIO setup: allocate and configure QBMan channels, setup core affinity
 * and रेजिस्टर data availability notअगरications
 */
अटल पूर्णांक dpaa2_eth_setup_dpio(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpaa2_io_notअगरication_ctx *nctx;
	काष्ठा dpaa2_eth_channel *channel;
	काष्ठा dpcon_notअगरication_cfg dpcon_notअगर_cfg;
	काष्ठा device *dev = priv->net_dev->dev.parent;
	पूर्णांक i, err;

	/* We want the ability to spपढ़ो ingress traffic (RX, TX conf) to as
	 * many cores as possible, so we need one channel क्रम each core
	 * (unless there's fewer queues than cores, in which हाल the extra
	 * channels would be wasted).
	 * Allocate one channel per core and रेजिस्टर it to the core's
	 * affine DPIO. If not enough channels are available क्रम all cores
	 * or अगर some cores करोn't have an affine DPIO, there will be no
	 * ingress frame processing on those cores.
	 */
	cpumask_clear(&priv->dpio_cpumask);
	क्रम_each_online_cpu(i) अणु
		/* Try to allocate a channel */
		channel = dpaa2_eth_alloc_channel(priv);
		अगर (IS_ERR_OR_शून्य(channel)) अणु
			err = PTR_ERR_OR_ZERO(channel);
			अगर (err != -EPROBE_DEFER)
				dev_info(dev,
					 "No affine channel for cpu %d and above\n", i);
			जाओ err_alloc_ch;
		पूर्ण

		priv->channel[priv->num_channels] = channel;

		nctx = &channel->nctx;
		nctx->is_cdan = 1;
		nctx->cb = dpaa2_eth_cdan_cb;
		nctx->id = channel->ch_id;
		nctx->desired_cpu = i;

		/* Register the new context */
		channel->dpio = dpaa2_io_service_select(i);
		err = dpaa2_io_service_रेजिस्टर(channel->dpio, nctx, dev);
		अगर (err) अणु
			dev_dbg(dev, "No affine DPIO for cpu %d\n", i);
			/* If no affine DPIO क्रम this core, there's probably
			 * none available क्रम next cores either. Signal we want
			 * to retry later, in हाल the DPIO devices weren't
			 * probed yet.
			 */
			err = -EPROBE_DEFER;
			जाओ err_service_reg;
		पूर्ण

		/* Register DPCON notअगरication with MC */
		dpcon_notअगर_cfg.dpio_id = nctx->dpio_id;
		dpcon_notअगर_cfg.priority = 0;
		dpcon_notअगर_cfg.user_ctx = nctx->qman64;
		err = dpcon_set_notअगरication(priv->mc_io, 0,
					     channel->dpcon->mc_handle,
					     &dpcon_notअगर_cfg);
		अगर (err) अणु
			dev_err(dev, "dpcon_set_notification failed()\n");
			जाओ err_set_cdan;
		पूर्ण

		/* If we managed to allocate a channel and also found an affine
		 * DPIO क्रम this core, add it to the final mask
		 */
		cpumask_set_cpu(i, &priv->dpio_cpumask);
		priv->num_channels++;

		/* Stop अगर we alपढ़ोy have enough channels to accommodate all
		 * RX and TX conf queues
		 */
		अगर (priv->num_channels == priv->dpni_attrs.num_queues)
			अवरोध;
	पूर्ण

	वापस 0;

err_set_cdan:
	dpaa2_io_service_deरेजिस्टर(channel->dpio, nctx, dev);
err_service_reg:
	dpaa2_eth_मुक्त_channel(priv, channel);
err_alloc_ch:
	अगर (err == -EPROBE_DEFER) अणु
		क्रम (i = 0; i < priv->num_channels; i++) अणु
			channel = priv->channel[i];
			nctx = &channel->nctx;
			dpaa2_io_service_deरेजिस्टर(channel->dpio, nctx, dev);
			dpaa2_eth_मुक्त_channel(priv, channel);
		पूर्ण
		priv->num_channels = 0;
		वापस err;
	पूर्ण

	अगर (cpumask_empty(&priv->dpio_cpumask)) अणु
		dev_err(dev, "No cpu with an affine DPIO/DPCON\n");
		वापस -ENODEV;
	पूर्ण

	dev_info(dev, "Cores %*pbl available for processing ingress traffic\n",
		 cpumask_pr_args(&priv->dpio_cpumask));

	वापस 0;
पूर्ण

अटल व्योम dpaa2_eth_मुक्त_dpio(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpaa2_eth_channel *ch;
	पूर्णांक i;

	/* deरेजिस्टर CDAN notअगरications and मुक्त channels */
	क्रम (i = 0; i < priv->num_channels; i++) अणु
		ch = priv->channel[i];
		dpaa2_io_service_deरेजिस्टर(ch->dpio, &ch->nctx, dev);
		dpaa2_eth_मुक्त_channel(priv, ch);
	पूर्ण
पूर्ण

अटल काष्ठा dpaa2_eth_channel *dpaa2_eth_get_affine_channel(काष्ठा dpaa2_eth_priv *priv,
							      पूर्णांक cpu)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_channels; i++)
		अगर (priv->channel[i]->nctx.desired_cpu == cpu)
			वापस priv->channel[i];

	/* We should never get here. Issue a warning and वापस
	 * the first channel, because it's still better than nothing
	 */
	dev_warn(dev, "No affine channel found for cpu %d\n", cpu);

	वापस priv->channel[0];
पूर्ण

अटल व्योम dpaa2_eth_set_fq_affinity(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpaa2_eth_fq *fq;
	पूर्णांक rx_cpu, txc_cpu;
	पूर्णांक i;

	/* For each FQ, pick one channel/CPU to deliver frames to.
	 * This may well change at runसमय, either through irqbalance or
	 * through direct user पूर्णांकervention.
	 */
	rx_cpu = txc_cpu = cpumask_first(&priv->dpio_cpumask);

	क्रम (i = 0; i < priv->num_fqs; i++) अणु
		fq = &priv->fq[i];
		चयन (fq->type) अणु
		हाल DPAA2_RX_FQ:
		हाल DPAA2_RX_ERR_FQ:
			fq->target_cpu = rx_cpu;
			rx_cpu = cpumask_next(rx_cpu, &priv->dpio_cpumask);
			अगर (rx_cpu >= nr_cpu_ids)
				rx_cpu = cpumask_first(&priv->dpio_cpumask);
			अवरोध;
		हाल DPAA2_TX_CONF_FQ:
			fq->target_cpu = txc_cpu;
			txc_cpu = cpumask_next(txc_cpu, &priv->dpio_cpumask);
			अगर (txc_cpu >= nr_cpu_ids)
				txc_cpu = cpumask_first(&priv->dpio_cpumask);
			अवरोध;
		शेष:
			dev_err(dev, "Unknown FQ type: %d\n", fq->type);
		पूर्ण
		fq->channel = dpaa2_eth_get_affine_channel(priv, fq->target_cpu);
	पूर्ण

	update_xps(priv);
पूर्ण

अटल व्योम dpaa2_eth_setup_fqs(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक i, j;

	/* We have one TxConf FQ per Tx flow.
	 * The number of Tx and Rx queues is the same.
	 * Tx queues come first in the fq array.
	 */
	क्रम (i = 0; i < dpaa2_eth_queue_count(priv); i++) अणु
		priv->fq[priv->num_fqs].type = DPAA2_TX_CONF_FQ;
		priv->fq[priv->num_fqs].consume = dpaa2_eth_tx_conf;
		priv->fq[priv->num_fqs++].flowid = (u16)i;
	पूर्ण

	क्रम (j = 0; j < dpaa2_eth_tc_count(priv); j++) अणु
		क्रम (i = 0; i < dpaa2_eth_queue_count(priv); i++) अणु
			priv->fq[priv->num_fqs].type = DPAA2_RX_FQ;
			priv->fq[priv->num_fqs].consume = dpaa2_eth_rx;
			priv->fq[priv->num_fqs].tc = (u8)j;
			priv->fq[priv->num_fqs++].flowid = (u16)i;
		पूर्ण
	पूर्ण

	/* We have exactly one Rx error queue per DPNI */
	priv->fq[priv->num_fqs].type = DPAA2_RX_ERR_FQ;
	priv->fq[priv->num_fqs++].consume = dpaa2_eth_rx_err;

	/* For each FQ, decide on which core to process incoming frames */
	dpaa2_eth_set_fq_affinity(priv);
पूर्ण

/* Allocate and configure one buffer pool क्रम each पूर्णांकerface */
अटल पूर्णांक dpaa2_eth_setup_dpbp(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक err;
	काष्ठा fsl_mc_device *dpbp_dev;
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpbp_attr dpbp_attrs;

	err = fsl_mc_object_allocate(to_fsl_mc_device(dev), FSL_MC_POOL_DPBP,
				     &dpbp_dev);
	अगर (err) अणु
		अगर (err == -ENXIO)
			err = -EPROBE_DEFER;
		अन्यथा
			dev_err(dev, "DPBP device allocation failed\n");
		वापस err;
	पूर्ण

	priv->dpbp_dev = dpbp_dev;

	err = dpbp_खोलो(priv->mc_io, 0, priv->dpbp_dev->obj_desc.id,
			&dpbp_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpbp_open() failed\n");
		जाओ err_खोलो;
	पूर्ण

	err = dpbp_reset(priv->mc_io, 0, dpbp_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpbp_reset() failed\n");
		जाओ err_reset;
	पूर्ण

	err = dpbp_enable(priv->mc_io, 0, dpbp_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpbp_enable() failed\n");
		जाओ err_enable;
	पूर्ण

	err = dpbp_get_attributes(priv->mc_io, 0, dpbp_dev->mc_handle,
				  &dpbp_attrs);
	अगर (err) अणु
		dev_err(dev, "dpbp_get_attributes() failed\n");
		जाओ err_get_attr;
	पूर्ण
	priv->bpid = dpbp_attrs.bpid;

	वापस 0;

err_get_attr:
	dpbp_disable(priv->mc_io, 0, dpbp_dev->mc_handle);
err_enable:
err_reset:
	dpbp_बंद(priv->mc_io, 0, dpbp_dev->mc_handle);
err_खोलो:
	fsl_mc_object_मुक्त(dpbp_dev);

	वापस err;
पूर्ण

अटल व्योम dpaa2_eth_मुक्त_dpbp(काष्ठा dpaa2_eth_priv *priv)
अणु
	dpaa2_eth_drain_pool(priv);
	dpbp_disable(priv->mc_io, 0, priv->dpbp_dev->mc_handle);
	dpbp_बंद(priv->mc_io, 0, priv->dpbp_dev->mc_handle);
	fsl_mc_object_मुक्त(priv->dpbp_dev);
पूर्ण

अटल पूर्णांक dpaa2_eth_set_buffer_layout(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpni_buffer_layout buf_layout = अणु0पूर्ण;
	u16 rx_buf_align;
	पूर्णांक err;

	/* We need to check क्रम WRIOP version 1.0.0, but depending on the MC
	 * version, this number is not always provided correctly on rev1.
	 * We need to check क्रम both alternatives in this situation.
	 */
	अगर (priv->dpni_attrs.wriop_version == DPAA2_WRIOP_VERSION(0, 0, 0) ||
	    priv->dpni_attrs.wriop_version == DPAA2_WRIOP_VERSION(1, 0, 0))
		rx_buf_align = DPAA2_ETH_RX_BUF_ALIGN_REV1;
	अन्यथा
		rx_buf_align = DPAA2_ETH_RX_BUF_ALIGN;

	/* We need to ensure that the buffer size seen by WRIOP is a multiple
	 * of 64 or 256 bytes depending on the WRIOP version.
	 */
	priv->rx_buf_size = ALIGN_DOWN(DPAA2_ETH_RX_BUF_SIZE, rx_buf_align);

	/* tx buffer */
	buf_layout.निजी_data_size = DPAA2_ETH_SWA_SIZE;
	buf_layout.pass_बारtamp = true;
	buf_layout.pass_frame_status = true;
	buf_layout.options = DPNI_BUF_LAYOUT_OPT_PRIVATE_DATA_SIZE |
			     DPNI_BUF_LAYOUT_OPT_TIMESTAMP |
			     DPNI_BUF_LAYOUT_OPT_FRAME_STATUS;
	err = dpni_set_buffer_layout(priv->mc_io, 0, priv->mc_token,
				     DPNI_QUEUE_TX, &buf_layout);
	अगर (err) अणु
		dev_err(dev, "dpni_set_buffer_layout(TX) failed\n");
		वापस err;
	पूर्ण

	/* tx-confirm buffer */
	buf_layout.options = DPNI_BUF_LAYOUT_OPT_TIMESTAMP |
			     DPNI_BUF_LAYOUT_OPT_FRAME_STATUS;
	err = dpni_set_buffer_layout(priv->mc_io, 0, priv->mc_token,
				     DPNI_QUEUE_TX_CONFIRM, &buf_layout);
	अगर (err) अणु
		dev_err(dev, "dpni_set_buffer_layout(TX_CONF) failed\n");
		वापस err;
	पूर्ण

	/* Now that we've set our tx buffer layout, retrieve the minimum
	 * required tx data offset.
	 */
	err = dpni_get_tx_data_offset(priv->mc_io, 0, priv->mc_token,
				      &priv->tx_data_offset);
	अगर (err) अणु
		dev_err(dev, "dpni_get_tx_data_offset() failed\n");
		वापस err;
	पूर्ण

	अगर ((priv->tx_data_offset % 64) != 0)
		dev_warn(dev, "Tx data offset (%d) not a multiple of 64B\n",
			 priv->tx_data_offset);

	/* rx buffer */
	buf_layout.pass_frame_status = true;
	buf_layout.pass_parser_result = true;
	buf_layout.data_align = rx_buf_align;
	buf_layout.data_head_room = dpaa2_eth_rx_head_room(priv);
	buf_layout.निजी_data_size = 0;
	buf_layout.options = DPNI_BUF_LAYOUT_OPT_PARSER_RESULT |
			     DPNI_BUF_LAYOUT_OPT_FRAME_STATUS |
			     DPNI_BUF_LAYOUT_OPT_DATA_ALIGN |
			     DPNI_BUF_LAYOUT_OPT_DATA_HEAD_ROOM |
			     DPNI_BUF_LAYOUT_OPT_TIMESTAMP;
	err = dpni_set_buffer_layout(priv->mc_io, 0, priv->mc_token,
				     DPNI_QUEUE_RX, &buf_layout);
	अगर (err) अणु
		dev_err(dev, "dpni_set_buffer_layout(RX) failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DPNI_ENQUEUE_FQID_VER_MAJOR	7
#घोषणा DPNI_ENQUEUE_FQID_VER_MINOR	9

अटल अंतरभूत पूर्णांक dpaa2_eth_enqueue_qd(काष्ठा dpaa2_eth_priv *priv,
				       काष्ठा dpaa2_eth_fq *fq,
				       काष्ठा dpaa2_fd *fd, u8 prio,
				       u32 num_frames __always_unused,
				       पूर्णांक *frames_enqueued)
अणु
	पूर्णांक err;

	err = dpaa2_io_service_enqueue_qd(fq->channel->dpio,
					  priv->tx_qdid, prio,
					  fq->tx_qdbin, fd);
	अगर (!err && frames_enqueued)
		*frames_enqueued = 1;
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक dpaa2_eth_enqueue_fq_multiple(काष्ठा dpaa2_eth_priv *priv,
						काष्ठा dpaa2_eth_fq *fq,
						काष्ठा dpaa2_fd *fd,
						u8 prio, u32 num_frames,
						पूर्णांक *frames_enqueued)
अणु
	पूर्णांक err;

	err = dpaa2_io_service_enqueue_multiple_fq(fq->channel->dpio,
						   fq->tx_fqid[prio],
						   fd, num_frames);

	अगर (err == 0)
		वापस -EBUSY;

	अगर (frames_enqueued)
		*frames_enqueued = err;
	वापस 0;
पूर्ण

अटल व्योम dpaa2_eth_set_enqueue_mode(काष्ठा dpaa2_eth_priv *priv)
अणु
	अगर (dpaa2_eth_cmp_dpni_ver(priv, DPNI_ENQUEUE_FQID_VER_MAJOR,
				   DPNI_ENQUEUE_FQID_VER_MINOR) < 0)
		priv->enqueue = dpaa2_eth_enqueue_qd;
	अन्यथा
		priv->enqueue = dpaa2_eth_enqueue_fq_multiple;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_छोड़ो(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpni_link_cfg link_cfg = अणु0पूर्ण;
	पूर्णांक err;

	/* Get the शेष link options so we करोn't override other flags */
	err = dpni_get_link_cfg(priv->mc_io, 0, priv->mc_token, &link_cfg);
	अगर (err) अणु
		dev_err(dev, "dpni_get_link_cfg() failed\n");
		वापस err;
	पूर्ण

	/* By शेष, enable both Rx and Tx छोड़ो frames */
	link_cfg.options |= DPNI_LINK_OPT_PAUSE;
	link_cfg.options &= ~DPNI_LINK_OPT_ASYM_PAUSE;
	err = dpni_set_link_cfg(priv->mc_io, 0, priv->mc_token, &link_cfg);
	अगर (err) अणु
		dev_err(dev, "dpni_set_link_cfg() failed\n");
		वापस err;
	पूर्ण

	priv->link_state.options = link_cfg.options;

	वापस 0;
पूर्ण

अटल व्योम dpaa2_eth_update_tx_fqids(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा dpni_queue_id qid = अणु0पूर्ण;
	काष्ठा dpaa2_eth_fq *fq;
	काष्ठा dpni_queue queue;
	पूर्णांक i, j, err;

	/* We only use Tx FQIDs क्रम FQID-based enqueue, so check
	 * अगर DPNI version supports it beक्रमe updating FQIDs
	 */
	अगर (dpaa2_eth_cmp_dpni_ver(priv, DPNI_ENQUEUE_FQID_VER_MAJOR,
				   DPNI_ENQUEUE_FQID_VER_MINOR) < 0)
		वापस;

	क्रम (i = 0; i < priv->num_fqs; i++) अणु
		fq = &priv->fq[i];
		अगर (fq->type != DPAA2_TX_CONF_FQ)
			जारी;
		क्रम (j = 0; j < dpaa2_eth_tc_count(priv); j++) अणु
			err = dpni_get_queue(priv->mc_io, 0, priv->mc_token,
					     DPNI_QUEUE_TX, j, fq->flowid,
					     &queue, &qid);
			अगर (err)
				जाओ out_err;

			fq->tx_fqid[j] = qid.fqid;
			अगर (fq->tx_fqid[j] == 0)
				जाओ out_err;
		पूर्ण
	पूर्ण

	priv->enqueue = dpaa2_eth_enqueue_fq_multiple;

	वापस;

out_err:
	netdev_info(priv->net_dev,
		    "Error reading Tx FQID, fallback to QDID-based enqueue\n");
	priv->enqueue = dpaa2_eth_enqueue_qd;
पूर्ण

/* Configure ingress classअगरication based on VLAN PCP */
अटल पूर्णांक dpaa2_eth_set_vlan_qos(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpkg_profile_cfg kg_cfg = अणु0पूर्ण;
	काष्ठा dpni_qos_tbl_cfg qos_cfg = अणु0पूर्ण;
	काष्ठा dpni_rule_cfg key_params;
	व्योम *dma_mem, *key, *mask;
	u8 key_size = 2;	/* VLAN TCI field */
	पूर्णांक i, pcp, err;

	/* VLAN-based classअगरication only makes sense अगर we have multiple
	 * traffic classes.
	 * Also, we need to extract just the 3-bit PCP field from the VLAN
	 * header and we can only करो that by using a mask
	 */
	अगर (dpaa2_eth_tc_count(priv) == 1 || !dpaa2_eth_fs_mask_enabled(priv)) अणु
		dev_dbg(dev, "VLAN-based QoS classification not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	dma_mem = kzalloc(DPAA2_CLASSIFIER_DMA_SIZE, GFP_KERNEL);
	अगर (!dma_mem)
		वापस -ENOMEM;

	kg_cfg.num_extracts = 1;
	kg_cfg.extracts[0].type = DPKG_EXTRACT_FROM_HDR;
	kg_cfg.extracts[0].extract.from_hdr.prot = NET_PROT_VLAN;
	kg_cfg.extracts[0].extract.from_hdr.type = DPKG_FULL_FIELD;
	kg_cfg.extracts[0].extract.from_hdr.field = NH_FLD_VLAN_TCI;

	err = dpni_prepare_key_cfg(&kg_cfg, dma_mem);
	अगर (err) अणु
		dev_err(dev, "dpni_prepare_key_cfg failed\n");
		जाओ out_मुक्त_tbl;
	पूर्ण

	/* set QoS table */
	qos_cfg.शेष_tc = 0;
	qos_cfg.discard_on_miss = 0;
	qos_cfg.key_cfg_iova = dma_map_single(dev, dma_mem,
					      DPAA2_CLASSIFIER_DMA_SIZE,
					      DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, qos_cfg.key_cfg_iova)) अणु
		dev_err(dev, "QoS table DMA mapping failed\n");
		err = -ENOMEM;
		जाओ out_मुक्त_tbl;
	पूर्ण

	err = dpni_set_qos_table(priv->mc_io, 0, priv->mc_token, &qos_cfg);
	अगर (err) अणु
		dev_err(dev, "dpni_set_qos_table failed\n");
		जाओ out_unmap_tbl;
	पूर्ण

	/* Add QoS table entries */
	key = kzalloc(key_size * 2, GFP_KERNEL);
	अगर (!key) अणु
		err = -ENOMEM;
		जाओ out_unmap_tbl;
	पूर्ण
	mask = key + key_size;
	*(__be16 *)mask = cpu_to_be16(VLAN_PRIO_MASK);

	key_params.key_iova = dma_map_single(dev, key, key_size * 2,
					     DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, key_params.key_iova)) अणु
		dev_err(dev, "Qos table entry DMA mapping failed\n");
		err = -ENOMEM;
		जाओ out_मुक्त_key;
	पूर्ण

	key_params.mask_iova = key_params.key_iova + key_size;
	key_params.key_size = key_size;

	/* We add rules क्रम PCP-based distribution starting with highest
	 * priority (VLAN PCP = 7). If this DPNI करोesn't have enough traffic
	 * classes to accommodate all priority levels, the lowest ones end up
	 * on TC 0 which was configured as शेष
	 */
	क्रम (i = dpaa2_eth_tc_count(priv) - 1, pcp = 7; i >= 0; i--, pcp--) अणु
		*(__be16 *)key = cpu_to_be16(pcp << VLAN_PRIO_SHIFT);
		dma_sync_single_क्रम_device(dev, key_params.key_iova,
					   key_size * 2, DMA_TO_DEVICE);

		err = dpni_add_qos_entry(priv->mc_io, 0, priv->mc_token,
					 &key_params, i, i);
		अगर (err) अणु
			dev_err(dev, "dpni_add_qos_entry failed\n");
			dpni_clear_qos_table(priv->mc_io, 0, priv->mc_token);
			जाओ out_unmap_key;
		पूर्ण
	पूर्ण

	priv->vlan_cls_enabled = true;

	/* Table and key memory is not persistent, clean everything up after
	 * configuration is finished
	 */
out_unmap_key:
	dma_unmap_single(dev, key_params.key_iova, key_size * 2, DMA_TO_DEVICE);
out_मुक्त_key:
	kमुक्त(key);
out_unmap_tbl:
	dma_unmap_single(dev, qos_cfg.key_cfg_iova, DPAA2_CLASSIFIER_DMA_SIZE,
			 DMA_TO_DEVICE);
out_मुक्त_tbl:
	kमुक्त(dma_mem);

	वापस err;
पूर्ण

/* Configure the DPNI object this पूर्णांकerface is associated with */
अटल पूर्णांक dpaa2_eth_setup_dpni(काष्ठा fsl_mc_device *ls_dev)
अणु
	काष्ठा device *dev = &ls_dev->dev;
	काष्ठा dpaa2_eth_priv *priv;
	काष्ठा net_device *net_dev;
	पूर्णांक err;

	net_dev = dev_get_drvdata(dev);
	priv = netdev_priv(net_dev);

	/* get a handle क्रम the DPNI object */
	err = dpni_खोलो(priv->mc_io, 0, ls_dev->obj_desc.id, &priv->mc_token);
	अगर (err) अणु
		dev_err(dev, "dpni_open() failed\n");
		वापस err;
	पूर्ण

	/* Check अगर we can work with this DPNI object */
	err = dpni_get_api_version(priv->mc_io, 0, &priv->dpni_ver_major,
				   &priv->dpni_ver_minor);
	अगर (err) अणु
		dev_err(dev, "dpni_get_api_version() failed\n");
		जाओ बंद;
	पूर्ण
	अगर (dpaa2_eth_cmp_dpni_ver(priv, DPNI_VER_MAJOR, DPNI_VER_MINOR) < 0) अणु
		dev_err(dev, "DPNI version %u.%u not supported, need >= %u.%u\n",
			priv->dpni_ver_major, priv->dpni_ver_minor,
			DPNI_VER_MAJOR, DPNI_VER_MINOR);
		err = -ENOTSUPP;
		जाओ बंद;
	पूर्ण

	ls_dev->mc_io = priv->mc_io;
	ls_dev->mc_handle = priv->mc_token;

	err = dpni_reset(priv->mc_io, 0, priv->mc_token);
	अगर (err) अणु
		dev_err(dev, "dpni_reset() failed\n");
		जाओ बंद;
	पूर्ण

	err = dpni_get_attributes(priv->mc_io, 0, priv->mc_token,
				  &priv->dpni_attrs);
	अगर (err) अणु
		dev_err(dev, "dpni_get_attributes() failed (err=%d)\n", err);
		जाओ बंद;
	पूर्ण

	err = dpaa2_eth_set_buffer_layout(priv);
	अगर (err)
		जाओ बंद;

	dpaa2_eth_set_enqueue_mode(priv);

	/* Enable छोड़ो frame support */
	अगर (dpaa2_eth_has_छोड़ो_support(priv)) अणु
		err = dpaa2_eth_set_छोड़ो(priv);
		अगर (err)
			जाओ बंद;
	पूर्ण

	err = dpaa2_eth_set_vlan_qos(priv);
	अगर (err && err != -EOPNOTSUPP)
		जाओ बंद;

	priv->cls_rules = devm_kसुस्मृति(dev, dpaa2_eth_fs_count(priv),
				       माप(काष्ठा dpaa2_eth_cls_rule),
				       GFP_KERNEL);
	अगर (!priv->cls_rules) अणु
		err = -ENOMEM;
		जाओ बंद;
	पूर्ण

	वापस 0;

बंद:
	dpni_बंद(priv->mc_io, 0, priv->mc_token);

	वापस err;
पूर्ण

अटल व्योम dpaa2_eth_मुक्त_dpni(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक err;

	err = dpni_reset(priv->mc_io, 0, priv->mc_token);
	अगर (err)
		netdev_warn(priv->net_dev, "dpni_reset() failed (err %d)\n",
			    err);

	dpni_बंद(priv->mc_io, 0, priv->mc_token);
पूर्ण

अटल पूर्णांक dpaa2_eth_setup_rx_flow(काष्ठा dpaa2_eth_priv *priv,
				   काष्ठा dpaa2_eth_fq *fq)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpni_queue queue;
	काष्ठा dpni_queue_id qid;
	पूर्णांक err;

	err = dpni_get_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_RX, fq->tc, fq->flowid, &queue, &qid);
	अगर (err) अणु
		dev_err(dev, "dpni_get_queue(RX) failed\n");
		वापस err;
	पूर्ण

	fq->fqid = qid.fqid;

	queue.destination.id = fq->channel->dpcon_id;
	queue.destination.type = DPNI_DEST_DPCON;
	queue.destination.priority = 1;
	queue.user_context = (u64)(uपूर्णांकptr_t)fq;
	err = dpni_set_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_RX, fq->tc, fq->flowid,
			     DPNI_QUEUE_OPT_USER_CTX | DPNI_QUEUE_OPT_DEST,
			     &queue);
	अगर (err) अणु
		dev_err(dev, "dpni_set_queue(RX) failed\n");
		वापस err;
	पूर्ण

	/* xdp_rxq setup */
	/* only once क्रम each channel */
	अगर (fq->tc > 0)
		वापस 0;

	err = xdp_rxq_info_reg(&fq->channel->xdp_rxq, priv->net_dev,
			       fq->flowid, 0);
	अगर (err) अणु
		dev_err(dev, "xdp_rxq_info_reg failed\n");
		वापस err;
	पूर्ण

	err = xdp_rxq_info_reg_mem_model(&fq->channel->xdp_rxq,
					 MEM_TYPE_PAGE_ORDER0, शून्य);
	अगर (err) अणु
		dev_err(dev, "xdp_rxq_info_reg_mem_model failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_setup_tx_flow(काष्ठा dpaa2_eth_priv *priv,
				   काष्ठा dpaa2_eth_fq *fq)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpni_queue queue;
	काष्ठा dpni_queue_id qid;
	पूर्णांक i, err;

	क्रम (i = 0; i < dpaa2_eth_tc_count(priv); i++) अणु
		err = dpni_get_queue(priv->mc_io, 0, priv->mc_token,
				     DPNI_QUEUE_TX, i, fq->flowid,
				     &queue, &qid);
		अगर (err) अणु
			dev_err(dev, "dpni_get_queue(TX) failed\n");
			वापस err;
		पूर्ण
		fq->tx_fqid[i] = qid.fqid;
	पूर्ण

	/* All Tx queues beदीर्घing to the same flowid have the same qdbin */
	fq->tx_qdbin = qid.qdbin;

	err = dpni_get_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_TX_CONFIRM, 0, fq->flowid,
			     &queue, &qid);
	अगर (err) अणु
		dev_err(dev, "dpni_get_queue(TX_CONF) failed\n");
		वापस err;
	पूर्ण

	fq->fqid = qid.fqid;

	queue.destination.id = fq->channel->dpcon_id;
	queue.destination.type = DPNI_DEST_DPCON;
	queue.destination.priority = 0;
	queue.user_context = (u64)(uपूर्णांकptr_t)fq;
	err = dpni_set_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_TX_CONFIRM, 0, fq->flowid,
			     DPNI_QUEUE_OPT_USER_CTX | DPNI_QUEUE_OPT_DEST,
			     &queue);
	अगर (err) अणु
		dev_err(dev, "dpni_set_queue(TX_CONF) failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_rx_err_flow(काष्ठा dpaa2_eth_priv *priv,
			     काष्ठा dpaa2_eth_fq *fq)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpni_queue q = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा dpni_queue_id qid;
	u8 q_opt = DPNI_QUEUE_OPT_USER_CTX | DPNI_QUEUE_OPT_DEST;
	पूर्णांक err;

	err = dpni_get_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_RX_ERR, 0, 0, &q, &qid);
	अगर (err) अणु
		dev_err(dev, "dpni_get_queue() failed (%d)\n", err);
		वापस err;
	पूर्ण

	fq->fqid = qid.fqid;

	q.destination.id = fq->channel->dpcon_id;
	q.destination.type = DPNI_DEST_DPCON;
	q.destination.priority = 1;
	q.user_context = (u64)(uपूर्णांकptr_t)fq;
	err = dpni_set_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_RX_ERR, 0, 0, q_opt, &q);
	अगर (err) अणु
		dev_err(dev, "dpni_set_queue() failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Supported header fields क्रम Rx hash distribution key */
अटल स्थिर काष्ठा dpaa2_eth_dist_fields dist_fields[] = अणु
	अणु
		/* L2 header */
		.rxnfc_field = RXH_L2DA,
		.cls_prot = NET_PROT_ETH,
		.cls_field = NH_FLD_ETH_DA,
		.id = DPAA2_ETH_DIST_ETHDST,
		.size = 6,
	पूर्ण, अणु
		.cls_prot = NET_PROT_ETH,
		.cls_field = NH_FLD_ETH_SA,
		.id = DPAA2_ETH_DIST_ETHSRC,
		.size = 6,
	पूर्ण, अणु
		/* This is the last ethertype field parsed:
		 * depending on frame क्रमmat, it can be the MAC ethertype
		 * or the VLAN etype.
		 */
		.cls_prot = NET_PROT_ETH,
		.cls_field = NH_FLD_ETH_TYPE,
		.id = DPAA2_ETH_DIST_ETHTYPE,
		.size = 2,
	पूर्ण, अणु
		/* VLAN header */
		.rxnfc_field = RXH_VLAN,
		.cls_prot = NET_PROT_VLAN,
		.cls_field = NH_FLD_VLAN_TCI,
		.id = DPAA2_ETH_DIST_VLAN,
		.size = 2,
	पूर्ण, अणु
		/* IP header */
		.rxnfc_field = RXH_IP_SRC,
		.cls_prot = NET_PROT_IP,
		.cls_field = NH_FLD_IP_SRC,
		.id = DPAA2_ETH_DIST_IPSRC,
		.size = 4,
	पूर्ण, अणु
		.rxnfc_field = RXH_IP_DST,
		.cls_prot = NET_PROT_IP,
		.cls_field = NH_FLD_IP_DST,
		.id = DPAA2_ETH_DIST_IPDST,
		.size = 4,
	पूर्ण, अणु
		.rxnfc_field = RXH_L3_PROTO,
		.cls_prot = NET_PROT_IP,
		.cls_field = NH_FLD_IP_PROTO,
		.id = DPAA2_ETH_DIST_IPPROTO,
		.size = 1,
	पूर्ण, अणु
		/* Using UDP ports, this is functionally equivalent to raw
		 * byte pairs from L4 header.
		 */
		.rxnfc_field = RXH_L4_B_0_1,
		.cls_prot = NET_PROT_UDP,
		.cls_field = NH_FLD_UDP_PORT_SRC,
		.id = DPAA2_ETH_DIST_L4SRC,
		.size = 2,
	पूर्ण, अणु
		.rxnfc_field = RXH_L4_B_2_3,
		.cls_prot = NET_PROT_UDP,
		.cls_field = NH_FLD_UDP_PORT_DST,
		.id = DPAA2_ETH_DIST_L4DST,
		.size = 2,
	पूर्ण,
पूर्ण;

/* Configure the Rx hash key using the legacy API */
अटल पूर्णांक dpaa2_eth_config_legacy_hash_key(काष्ठा dpaa2_eth_priv *priv, dma_addr_t key)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpni_rx_tc_dist_cfg dist_cfg;
	पूर्णांक i, err = 0;

	स_रखो(&dist_cfg, 0, माप(dist_cfg));

	dist_cfg.key_cfg_iova = key;
	dist_cfg.dist_size = dpaa2_eth_queue_count(priv);
	dist_cfg.dist_mode = DPNI_DIST_MODE_HASH;

	क्रम (i = 0; i < dpaa2_eth_tc_count(priv); i++) अणु
		err = dpni_set_rx_tc_dist(priv->mc_io, 0, priv->mc_token,
					  i, &dist_cfg);
		अगर (err) अणु
			dev_err(dev, "dpni_set_rx_tc_dist failed\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/* Configure the Rx hash key using the new API */
अटल पूर्णांक dpaa2_eth_config_hash_key(काष्ठा dpaa2_eth_priv *priv, dma_addr_t key)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpni_rx_dist_cfg dist_cfg;
	पूर्णांक i, err = 0;

	स_रखो(&dist_cfg, 0, माप(dist_cfg));

	dist_cfg.key_cfg_iova = key;
	dist_cfg.dist_size = dpaa2_eth_queue_count(priv);
	dist_cfg.enable = 1;

	क्रम (i = 0; i < dpaa2_eth_tc_count(priv); i++) अणु
		dist_cfg.tc = i;
		err = dpni_set_rx_hash_dist(priv->mc_io, 0, priv->mc_token,
					    &dist_cfg);
		अगर (err) अणु
			dev_err(dev, "dpni_set_rx_hash_dist failed\n");
			अवरोध;
		पूर्ण

		/* If the flow steering / hashing key is shared between all
		 * traffic classes, install it just once
		 */
		अगर (priv->dpni_attrs.options & DPNI_OPT_SHARED_FS)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Configure the Rx flow classअगरication key */
अटल पूर्णांक dpaa2_eth_config_cls_key(काष्ठा dpaa2_eth_priv *priv, dma_addr_t key)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	काष्ठा dpni_rx_dist_cfg dist_cfg;
	पूर्णांक i, err = 0;

	स_रखो(&dist_cfg, 0, माप(dist_cfg));

	dist_cfg.key_cfg_iova = key;
	dist_cfg.dist_size = dpaa2_eth_queue_count(priv);
	dist_cfg.enable = 1;

	क्रम (i = 0; i < dpaa2_eth_tc_count(priv); i++) अणु
		dist_cfg.tc = i;
		err = dpni_set_rx_fs_dist(priv->mc_io, 0, priv->mc_token,
					  &dist_cfg);
		अगर (err) अणु
			dev_err(dev, "dpni_set_rx_fs_dist failed\n");
			अवरोध;
		पूर्ण

		/* If the flow steering / hashing key is shared between all
		 * traffic classes, install it just once
		 */
		अगर (priv->dpni_attrs.options & DPNI_OPT_SHARED_FS)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Size of the Rx flow classअगरication key */
पूर्णांक dpaa2_eth_cls_key_size(u64 fields)
अणु
	पूर्णांक i, size = 0;

	क्रम (i = 0; i < ARRAY_SIZE(dist_fields); i++) अणु
		अगर (!(fields & dist_fields[i].id))
			जारी;
		size += dist_fields[i].size;
	पूर्ण

	वापस size;
पूर्ण

/* Offset of header field in Rx classअगरication key */
पूर्णांक dpaa2_eth_cls_fld_off(पूर्णांक prot, पूर्णांक field)
अणु
	पूर्णांक i, off = 0;

	क्रम (i = 0; i < ARRAY_SIZE(dist_fields); i++) अणु
		अगर (dist_fields[i].cls_prot == prot &&
		    dist_fields[i].cls_field == field)
			वापस off;
		off += dist_fields[i].size;
	पूर्ण

	WARN_ONCE(1, "Unsupported header field used for Rx flow cls\n");
	वापस 0;
पूर्ण

/* Prune unused fields from the classअगरication rule.
 * Used when masking is not supported
 */
व्योम dpaa2_eth_cls_trim_rule(व्योम *key_mem, u64 fields)
अणु
	पूर्णांक off = 0, new_off = 0;
	पूर्णांक i, size;

	क्रम (i = 0; i < ARRAY_SIZE(dist_fields); i++) अणु
		size = dist_fields[i].size;
		अगर (dist_fields[i].id & fields) अणु
			स_नकल(key_mem + new_off, key_mem + off, size);
			new_off += size;
		पूर्ण
		off += size;
	पूर्ण
पूर्ण

/* Set Rx distribution (hash or flow classअगरication) key
 * flags is a combination of RXH_ bits
 */
अटल पूर्णांक dpaa2_eth_set_dist_key(काष्ठा net_device *net_dev,
				  क्रमागत dpaa2_eth_rx_dist type, u64 flags)
अणु
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा dpkg_profile_cfg cls_cfg;
	u32 rx_hash_fields = 0;
	dma_addr_t key_iova;
	u8 *dma_mem;
	पूर्णांक i;
	पूर्णांक err = 0;

	स_रखो(&cls_cfg, 0, माप(cls_cfg));

	क्रम (i = 0; i < ARRAY_SIZE(dist_fields); i++) अणु
		काष्ठा dpkg_extract *key =
			&cls_cfg.extracts[cls_cfg.num_extracts];

		/* For both Rx hashing and classअगरication keys
		 * we set only the selected fields.
		 */
		अगर (!(flags & dist_fields[i].id))
			जारी;
		अगर (type == DPAA2_ETH_RX_DIST_HASH)
			rx_hash_fields |= dist_fields[i].rxnfc_field;

		अगर (cls_cfg.num_extracts >= DPKG_MAX_NUM_OF_EXTRACTS) अणु
			dev_err(dev, "error adding key extraction rule, too many rules?\n");
			वापस -E2BIG;
		पूर्ण

		key->type = DPKG_EXTRACT_FROM_HDR;
		key->extract.from_hdr.prot = dist_fields[i].cls_prot;
		key->extract.from_hdr.type = DPKG_FULL_FIELD;
		key->extract.from_hdr.field = dist_fields[i].cls_field;
		cls_cfg.num_extracts++;
	पूर्ण

	dma_mem = kzalloc(DPAA2_CLASSIFIER_DMA_SIZE, GFP_KERNEL);
	अगर (!dma_mem)
		वापस -ENOMEM;

	err = dpni_prepare_key_cfg(&cls_cfg, dma_mem);
	अगर (err) अणु
		dev_err(dev, "dpni_prepare_key_cfg error %d\n", err);
		जाओ मुक्त_key;
	पूर्ण

	/* Prepare क्रम setting the rx dist */
	key_iova = dma_map_single(dev, dma_mem, DPAA2_CLASSIFIER_DMA_SIZE,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, key_iova)) अणु
		dev_err(dev, "DMA mapping failed\n");
		err = -ENOMEM;
		जाओ मुक्त_key;
	पूर्ण

	अगर (type == DPAA2_ETH_RX_DIST_HASH) अणु
		अगर (dpaa2_eth_has_legacy_dist(priv))
			err = dpaa2_eth_config_legacy_hash_key(priv, key_iova);
		अन्यथा
			err = dpaa2_eth_config_hash_key(priv, key_iova);
	पूर्ण अन्यथा अणु
		err = dpaa2_eth_config_cls_key(priv, key_iova);
	पूर्ण

	dma_unmap_single(dev, key_iova, DPAA2_CLASSIFIER_DMA_SIZE,
			 DMA_TO_DEVICE);
	अगर (!err && type == DPAA2_ETH_RX_DIST_HASH)
		priv->rx_hash_fields = rx_hash_fields;

मुक्त_key:
	kमुक्त(dma_mem);
	वापस err;
पूर्ण

पूर्णांक dpaa2_eth_set_hash(काष्ठा net_device *net_dev, u64 flags)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u64 key = 0;
	पूर्णांक i;

	अगर (!dpaa2_eth_hash_enabled(priv))
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i < ARRAY_SIZE(dist_fields); i++)
		अगर (dist_fields[i].rxnfc_field & flags)
			key |= dist_fields[i].id;

	वापस dpaa2_eth_set_dist_key(net_dev, DPAA2_ETH_RX_DIST_HASH, key);
पूर्ण

पूर्णांक dpaa2_eth_set_cls(काष्ठा net_device *net_dev, u64 flags)
अणु
	वापस dpaa2_eth_set_dist_key(net_dev, DPAA2_ETH_RX_DIST_CLS, flags);
पूर्ण

अटल पूर्णांक dpaa2_eth_set_शेष_cls(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा device *dev = priv->net_dev->dev.parent;
	पूर्णांक err;

	/* Check अगर we actually support Rx flow classअगरication */
	अगर (dpaa2_eth_has_legacy_dist(priv)) अणु
		dev_dbg(dev, "Rx cls not supported by current MC version\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!dpaa2_eth_fs_enabled(priv)) अणु
		dev_dbg(dev, "Rx cls disabled in DPNI options\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!dpaa2_eth_hash_enabled(priv)) अणु
		dev_dbg(dev, "Rx cls disabled for single queue DPNIs\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If there is no support क्रम masking in the classअगरication table,
	 * we करोn't set a शेष key, as it will depend on the rules
	 * added by the user at runसमय.
	 */
	अगर (!dpaa2_eth_fs_mask_enabled(priv))
		जाओ out;

	err = dpaa2_eth_set_cls(priv->net_dev, DPAA2_ETH_DIST_ALL);
	अगर (err)
		वापस err;

out:
	priv->rx_cls_enabled = 1;

	वापस 0;
पूर्ण

/* Bind the DPNI to its needed objects and resources: buffer pool, DPIOs,
 * frame queues and channels
 */
अटल पूर्णांक dpaa2_eth_bind_dpni(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा net_device *net_dev = priv->net_dev;
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा dpni_pools_cfg pools_params;
	काष्ठा dpni_error_cfg err_cfg;
	पूर्णांक err = 0;
	पूर्णांक i;

	pools_params.num_dpbp = 1;
	pools_params.pools[0].dpbp_id = priv->dpbp_dev->obj_desc.id;
	pools_params.pools[0].backup_pool = 0;
	pools_params.pools[0].buffer_size = priv->rx_buf_size;
	err = dpni_set_pools(priv->mc_io, 0, priv->mc_token, &pools_params);
	अगर (err) अणु
		dev_err(dev, "dpni_set_pools() failed\n");
		वापस err;
	पूर्ण

	/* have the पूर्णांकerface implicitly distribute traffic based on
	 * the शेष hash key
	 */
	err = dpaa2_eth_set_hash(net_dev, DPAA2_RXH_DEFAULT);
	अगर (err && err != -EOPNOTSUPP)
		dev_err(dev, "Failed to configure hashing\n");

	/* Configure the flow classअगरication key; it includes all
	 * supported header fields and cannot be modअगरied at runसमय
	 */
	err = dpaa2_eth_set_शेष_cls(priv);
	अगर (err && err != -EOPNOTSUPP)
		dev_err(dev, "Failed to configure Rx classification key\n");

	/* Configure handling of error frames */
	err_cfg.errors = DPAA2_FAS_RX_ERR_MASK;
	err_cfg.set_frame_annotation = 1;
	err_cfg.error_action = DPNI_ERROR_ACTION_DISCARD;
	err = dpni_set_errors_behavior(priv->mc_io, 0, priv->mc_token,
				       &err_cfg);
	अगर (err) अणु
		dev_err(dev, "dpni_set_errors_behavior failed\n");
		वापस err;
	पूर्ण

	/* Configure Rx and Tx conf queues to generate CDANs */
	क्रम (i = 0; i < priv->num_fqs; i++) अणु
		चयन (priv->fq[i].type) अणु
		हाल DPAA2_RX_FQ:
			err = dpaa2_eth_setup_rx_flow(priv, &priv->fq[i]);
			अवरोध;
		हाल DPAA2_TX_CONF_FQ:
			err = dpaa2_eth_setup_tx_flow(priv, &priv->fq[i]);
			अवरोध;
		हाल DPAA2_RX_ERR_FQ:
			err = setup_rx_err_flow(priv, &priv->fq[i]);
			अवरोध;
		शेष:
			dev_err(dev, "Invalid FQ type %d\n", priv->fq[i].type);
			वापस -EINVAL;
		पूर्ण
		अगर (err)
			वापस err;
	पूर्ण

	err = dpni_get_qdid(priv->mc_io, 0, priv->mc_token,
			    DPNI_QUEUE_TX, &priv->tx_qdid);
	अगर (err) अणु
		dev_err(dev, "dpni_get_qdid() failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Allocate rings क्रम storing incoming frame descriptors */
अटल पूर्णांक dpaa2_eth_alloc_rings(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा net_device *net_dev = priv->net_dev;
	काष्ठा device *dev = net_dev->dev.parent;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		priv->channel[i]->store =
			dpaa2_io_store_create(DPAA2_ETH_STORE_SIZE, dev);
		अगर (!priv->channel[i]->store) अणु
			netdev_err(net_dev, "dpaa2_io_store_create() failed\n");
			जाओ err_ring;
		पूर्ण
	पूर्ण

	वापस 0;

err_ring:
	क्रम (i = 0; i < priv->num_channels; i++) अणु
		अगर (!priv->channel[i]->store)
			अवरोध;
		dpaa2_io_store_destroy(priv->channel[i]->store);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल व्योम dpaa2_eth_मुक्त_rings(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_channels; i++)
		dpaa2_io_store_destroy(priv->channel[i]->store);
पूर्ण

अटल पूर्णांक dpaa2_eth_set_mac_addr(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा net_device *net_dev = priv->net_dev;
	काष्ठा device *dev = net_dev->dev.parent;
	u8 mac_addr[ETH_ALEN], dpni_mac_addr[ETH_ALEN];
	पूर्णांक err;

	/* Get firmware address, अगर any */
	err = dpni_get_port_mac_addr(priv->mc_io, 0, priv->mc_token, mac_addr);
	अगर (err) अणु
		dev_err(dev, "dpni_get_port_mac_addr() failed\n");
		वापस err;
	पूर्ण

	/* Get DPNI attributes address, अगर any */
	err = dpni_get_primary_mac_addr(priv->mc_io, 0, priv->mc_token,
					dpni_mac_addr);
	अगर (err) अणु
		dev_err(dev, "dpni_get_primary_mac_addr() failed\n");
		वापस err;
	पूर्ण

	/* First check अगर firmware has any address configured by bootloader */
	अगर (!is_zero_ether_addr(mac_addr)) अणु
		/* If the DPMAC addr != DPNI addr, update it */
		अगर (!ether_addr_equal(mac_addr, dpni_mac_addr)) अणु
			err = dpni_set_primary_mac_addr(priv->mc_io, 0,
							priv->mc_token,
							mac_addr);
			अगर (err) अणु
				dev_err(dev, "dpni_set_primary_mac_addr() failed\n");
				वापस err;
			पूर्ण
		पूर्ण
		स_नकल(net_dev->dev_addr, mac_addr, net_dev->addr_len);
	पूर्ण अन्यथा अगर (is_zero_ether_addr(dpni_mac_addr)) अणु
		/* No MAC address configured, fill in net_dev->dev_addr
		 * with a अक्रमom one
		 */
		eth_hw_addr_अक्रमom(net_dev);
		dev_dbg_once(dev, "device(s) have all-zero hwaddr, replaced with random\n");

		err = dpni_set_primary_mac_addr(priv->mc_io, 0, priv->mc_token,
						net_dev->dev_addr);
		अगर (err) अणु
			dev_err(dev, "dpni_set_primary_mac_addr() failed\n");
			वापस err;
		पूर्ण

		/* Override NET_ADDR_RANDOM set by eth_hw_addr_अक्रमom(); क्रम all
		 * practical purposes, this will be our "permanent" mac address,
		 * at least until the next reboot. This move will also permit
		 * रेजिस्टर_netdevice() to properly fill up net_dev->perm_addr.
		 */
		net_dev->addr_assign_type = NET_ADDR_PERM;
	पूर्ण अन्यथा अणु
		/* NET_ADDR_PERM is शेष, all we have to करो is
		 * fill in the device addr.
		 */
		स_नकल(net_dev->dev_addr, dpni_mac_addr, net_dev->addr_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_netdev_init(काष्ठा net_device *net_dev)
अणु
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u32 options = priv->dpni_attrs.options;
	u64 supported = 0, not_supported = 0;
	u8 bcast_addr[ETH_ALEN];
	u8 num_queues;
	पूर्णांक err;

	net_dev->netdev_ops = &dpaa2_eth_ops;
	net_dev->ethtool_ops = &dpaa2_ethtool_ops;

	err = dpaa2_eth_set_mac_addr(priv);
	अगर (err)
		वापस err;

	/* Explicitly add the broadcast address to the MAC filtering table */
	eth_broadcast_addr(bcast_addr);
	err = dpni_add_mac_addr(priv->mc_io, 0, priv->mc_token, bcast_addr);
	अगर (err) अणु
		dev_err(dev, "dpni_add_mac_addr() failed\n");
		वापस err;
	पूर्ण

	/* Set MTU upper limit; lower limit is 68B (शेष value) */
	net_dev->max_mtu = DPAA2_ETH_MAX_MTU;
	err = dpni_set_max_frame_length(priv->mc_io, 0, priv->mc_token,
					DPAA2_ETH_MFL);
	अगर (err) अणु
		dev_err(dev, "dpni_set_max_frame_length() failed\n");
		वापस err;
	पूर्ण

	/* Set actual number of queues in the net device */
	num_queues = dpaa2_eth_queue_count(priv);
	err = netअगर_set_real_num_tx_queues(net_dev, num_queues);
	अगर (err) अणु
		dev_err(dev, "netif_set_real_num_tx_queues() failed\n");
		वापस err;
	पूर्ण
	err = netअगर_set_real_num_rx_queues(net_dev, num_queues);
	अगर (err) अणु
		dev_err(dev, "netif_set_real_num_rx_queues() failed\n");
		वापस err;
	पूर्ण

	/* Capabilities listing */
	supported |= IFF_LIVE_ADDR_CHANGE;

	अगर (options & DPNI_OPT_NO_MAC_FILTER)
		not_supported |= IFF_UNICAST_FLT;
	अन्यथा
		supported |= IFF_UNICAST_FLT;

	net_dev->priv_flags |= supported;
	net_dev->priv_flags &= ~not_supported;

	/* Features */
	net_dev->features = NETIF_F_RXCSUM |
			    NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			    NETIF_F_SG | NETIF_F_HIGHDMA |
			    NETIF_F_LLTX | NETIF_F_HW_TC;
	net_dev->hw_features = net_dev->features;

	अगर (priv->dpni_attrs.vlan_filter_entries)
		net_dev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_poll_link_state(व्योम *arg)
अणु
	काष्ठा dpaa2_eth_priv *priv = (काष्ठा dpaa2_eth_priv *)arg;
	पूर्णांक err;

	जबतक (!kthपढ़ो_should_stop()) अणु
		err = dpaa2_eth_link_state_update(priv);
		अगर (unlikely(err))
			वापस err;

		msleep(DPAA2_ETH_LINK_STATE_REFRESH);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_connect_mac(काष्ठा dpaa2_eth_priv *priv)
अणु
	काष्ठा fsl_mc_device *dpni_dev, *dpmac_dev;
	काष्ठा dpaa2_mac *mac;
	पूर्णांक err;

	dpni_dev = to_fsl_mc_device(priv->net_dev->dev.parent);
	dpmac_dev = fsl_mc_get_endpoपूर्णांक(dpni_dev);

	अगर (PTR_ERR(dpmac_dev) == -EPROBE_DEFER)
		वापस PTR_ERR(dpmac_dev);

	अगर (IS_ERR(dpmac_dev) || dpmac_dev->dev.type != &fsl_mc_bus_dpmac_type)
		वापस 0;

	mac = kzalloc(माप(काष्ठा dpaa2_mac), GFP_KERNEL);
	अगर (!mac)
		वापस -ENOMEM;

	mac->mc_dev = dpmac_dev;
	mac->mc_io = priv->mc_io;
	mac->net_dev = priv->net_dev;

	err = dpaa2_mac_खोलो(mac);
	अगर (err)
		जाओ err_मुक्त_mac;
	priv->mac = mac;

	अगर (dpaa2_eth_is_type_phy(priv)) अणु
		err = dpaa2_mac_connect(mac);
		अगर (err) अणु
			netdev_err(priv->net_dev, "Error connecting to the MAC endpoint\n");
			जाओ err_बंद_mac;
		पूर्ण
	पूर्ण

	वापस 0;

err_बंद_mac:
	dpaa2_mac_बंद(mac);
	priv->mac = शून्य;
err_मुक्त_mac:
	kमुक्त(mac);
	वापस err;
पूर्ण

अटल व्योम dpaa2_eth_disconnect_mac(काष्ठा dpaa2_eth_priv *priv)
अणु
	अगर (dpaa2_eth_is_type_phy(priv))
		dpaa2_mac_disconnect(priv->mac);

	अगर (!dpaa2_eth_has_mac(priv))
		वापस;

	dpaa2_mac_बंद(priv->mac);
	kमुक्त(priv->mac);
	priv->mac = शून्य;
पूर्ण

अटल irqवापस_t dpni_irq0_handler_thपढ़ो(पूर्णांक irq_num, व्योम *arg)
अणु
	u32 status = ~0;
	काष्ठा device *dev = (काष्ठा device *)arg;
	काष्ठा fsl_mc_device *dpni_dev = to_fsl_mc_device(dev);
	काष्ठा net_device *net_dev = dev_get_drvdata(dev);
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक err;

	err = dpni_get_irq_status(dpni_dev->mc_io, 0, dpni_dev->mc_handle,
				  DPNI_IRQ_INDEX, &status);
	अगर (unlikely(err)) अणु
		netdev_err(net_dev, "Can't get irq status (err %d)\n", err);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (status & DPNI_IRQ_EVENT_LINK_CHANGED)
		dpaa2_eth_link_state_update(netdev_priv(net_dev));

	अगर (status & DPNI_IRQ_EVENT_ENDPOINT_CHANGED) अणु
		dpaa2_eth_set_mac_addr(netdev_priv(net_dev));
		dpaa2_eth_update_tx_fqids(priv);

		rtnl_lock();
		अगर (dpaa2_eth_has_mac(priv))
			dpaa2_eth_disconnect_mac(priv);
		अन्यथा
			dpaa2_eth_connect_mac(priv);
		rtnl_unlock();
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dpaa2_eth_setup_irqs(काष्ठा fsl_mc_device *ls_dev)
अणु
	पूर्णांक err = 0;
	काष्ठा fsl_mc_device_irq *irq;

	err = fsl_mc_allocate_irqs(ls_dev);
	अगर (err) अणु
		dev_err(&ls_dev->dev, "MC irqs allocation failed\n");
		वापस err;
	पूर्ण

	irq = ls_dev->irqs[0];
	err = devm_request_thपढ़ोed_irq(&ls_dev->dev, irq->msi_desc->irq,
					शून्य, dpni_irq0_handler_thपढ़ो,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					dev_name(&ls_dev->dev), &ls_dev->dev);
	अगर (err < 0) अणु
		dev_err(&ls_dev->dev, "devm_request_threaded_irq(): %d\n", err);
		जाओ मुक्त_mc_irq;
	पूर्ण

	err = dpni_set_irq_mask(ls_dev->mc_io, 0, ls_dev->mc_handle,
				DPNI_IRQ_INDEX, DPNI_IRQ_EVENT_LINK_CHANGED |
				DPNI_IRQ_EVENT_ENDPOINT_CHANGED);
	अगर (err < 0) अणु
		dev_err(&ls_dev->dev, "dpni_set_irq_mask(): %d\n", err);
		जाओ मुक्त_irq;
	पूर्ण

	err = dpni_set_irq_enable(ls_dev->mc_io, 0, ls_dev->mc_handle,
				  DPNI_IRQ_INDEX, 1);
	अगर (err < 0) अणु
		dev_err(&ls_dev->dev, "dpni_set_irq_enable(): %d\n", err);
		जाओ मुक्त_irq;
	पूर्ण

	वापस 0;

मुक्त_irq:
	devm_मुक्त_irq(&ls_dev->dev, irq->msi_desc->irq, &ls_dev->dev);
मुक्त_mc_irq:
	fsl_mc_मुक्त_irqs(ls_dev);

	वापस err;
पूर्ण

अटल व्योम dpaa2_eth_add_ch_napi(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक i;
	काष्ठा dpaa2_eth_channel *ch;

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		ch = priv->channel[i];
		/* NAPI weight *MUST* be a multiple of DPAA2_ETH_STORE_SIZE */
		netअगर_napi_add(priv->net_dev, &ch->napi, dpaa2_eth_poll,
			       NAPI_POLL_WEIGHT);
	पूर्ण
पूर्ण

अटल व्योम dpaa2_eth_del_ch_napi(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक i;
	काष्ठा dpaa2_eth_channel *ch;

	क्रम (i = 0; i < priv->num_channels; i++) अणु
		ch = priv->channel[i];
		netअगर_napi_del(&ch->napi);
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_eth_probe(काष्ठा fsl_mc_device *dpni_dev)
अणु
	काष्ठा device *dev;
	काष्ठा net_device *net_dev = शून्य;
	काष्ठा dpaa2_eth_priv *priv = शून्य;
	पूर्णांक err = 0;

	dev = &dpni_dev->dev;

	/* Net device */
	net_dev = alloc_etherdev_mq(माप(*priv), DPAA2_ETH_MAX_NETDEV_QUEUES);
	अगर (!net_dev) अणु
		dev_err(dev, "alloc_etherdev_mq() failed\n");
		वापस -ENOMEM;
	पूर्ण

	SET_NETDEV_DEV(net_dev, dev);
	dev_set_drvdata(dev, net_dev);

	priv = netdev_priv(net_dev);
	priv->net_dev = net_dev;

	priv->iommu_करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	priv->tx_tstamp_type = HWTSTAMP_TX_OFF;
	priv->rx_tstamp = false;

	priv->dpaa2_ptp_wq = alloc_workqueue("dpaa2_ptp_wq", 0, 0);
	अगर (!priv->dpaa2_ptp_wq) अणु
		err = -ENOMEM;
		जाओ err_wq_alloc;
	पूर्ण

	INIT_WORK(&priv->tx_onestep_tstamp, dpaa2_eth_tx_onestep_tstamp);

	skb_queue_head_init(&priv->tx_skbs);

	priv->rx_copyअवरोध = DPAA2_ETH_DEFAULT_COPYBREAK;

	/* Obtain a MC portal */
	err = fsl_mc_portal_allocate(dpni_dev, FSL_MC_IO_ATOMIC_CONTEXT_PORTAL,
				     &priv->mc_io);
	अगर (err) अणु
		अगर (err == -ENXIO)
			err = -EPROBE_DEFER;
		अन्यथा
			dev_err(dev, "MC portal allocation failed\n");
		जाओ err_portal_alloc;
	पूर्ण

	/* MC objects initialization and configuration */
	err = dpaa2_eth_setup_dpni(dpni_dev);
	अगर (err)
		जाओ err_dpni_setup;

	err = dpaa2_eth_setup_dpio(priv);
	अगर (err)
		जाओ err_dpio_setup;

	dpaa2_eth_setup_fqs(priv);

	err = dpaa2_eth_setup_dpbp(priv);
	अगर (err)
		जाओ err_dpbp_setup;

	err = dpaa2_eth_bind_dpni(priv);
	अगर (err)
		जाओ err_bind;

	/* Add a NAPI context क्रम each channel */
	dpaa2_eth_add_ch_napi(priv);

	/* Percpu statistics */
	priv->percpu_stats = alloc_percpu(*priv->percpu_stats);
	अगर (!priv->percpu_stats) अणु
		dev_err(dev, "alloc_percpu(percpu_stats) failed\n");
		err = -ENOMEM;
		जाओ err_alloc_percpu_stats;
	पूर्ण
	priv->percpu_extras = alloc_percpu(*priv->percpu_extras);
	अगर (!priv->percpu_extras) अणु
		dev_err(dev, "alloc_percpu(percpu_extras) failed\n");
		err = -ENOMEM;
		जाओ err_alloc_percpu_extras;
	पूर्ण

	priv->sgt_cache = alloc_percpu(*priv->sgt_cache);
	अगर (!priv->sgt_cache) अणु
		dev_err(dev, "alloc_percpu(sgt_cache) failed\n");
		err = -ENOMEM;
		जाओ err_alloc_sgt_cache;
	पूर्ण

	err = dpaa2_eth_netdev_init(net_dev);
	अगर (err)
		जाओ err_netdev_init;

	/* Configure checksum offload based on current पूर्णांकerface flags */
	err = dpaa2_eth_set_rx_csum(priv, !!(net_dev->features & NETIF_F_RXCSUM));
	अगर (err)
		जाओ err_csum;

	err = dpaa2_eth_set_tx_csum(priv,
				    !!(net_dev->features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)));
	अगर (err)
		जाओ err_csum;

	err = dpaa2_eth_alloc_rings(priv);
	अगर (err)
		जाओ err_alloc_rings;

#अगर_घोषित CONFIG_FSL_DPAA2_ETH_DCB
	अगर (dpaa2_eth_has_छोड़ो_support(priv) && priv->vlan_cls_enabled) अणु
		priv->dcbx_mode = DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VER_IEEE;
		net_dev->dcbnl_ops = &dpaa2_eth_dcbnl_ops;
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "PFC not supported\n");
	पूर्ण
#पूर्ण_अगर

	err = dpaa2_eth_setup_irqs(dpni_dev);
	अगर (err) अणु
		netdev_warn(net_dev, "Failed to set link interrupt, fall back to polling\n");
		priv->poll_thपढ़ो = kthपढ़ो_run(dpaa2_eth_poll_link_state, priv,
						"%s_poll_link", net_dev->name);
		अगर (IS_ERR(priv->poll_thपढ़ो)) अणु
			dev_err(dev, "Error starting polling thread\n");
			जाओ err_poll_thपढ़ो;
		पूर्ण
		priv->करो_link_poll = true;
	पूर्ण

	err = dpaa2_eth_connect_mac(priv);
	अगर (err)
		जाओ err_connect_mac;

	err = dpaa2_eth_dl_रेजिस्टर(priv);
	अगर (err)
		जाओ err_dl_रेजिस्टर;

	err = dpaa2_eth_dl_traps_रेजिस्टर(priv);
	अगर (err)
		जाओ err_dl_trap_रेजिस्टर;

	err = dpaa2_eth_dl_port_add(priv);
	अगर (err)
		जाओ err_dl_port_add;

	err = रेजिस्टर_netdev(net_dev);
	अगर (err < 0) अणु
		dev_err(dev, "register_netdev() failed\n");
		जाओ err_netdev_reg;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	dpaa2_dbg_add(priv);
#पूर्ण_अगर

	dev_info(dev, "Probed interface %s\n", net_dev->name);
	वापस 0;

err_netdev_reg:
	dpaa2_eth_dl_port_del(priv);
err_dl_port_add:
	dpaa2_eth_dl_traps_unरेजिस्टर(priv);
err_dl_trap_रेजिस्टर:
	dpaa2_eth_dl_unरेजिस्टर(priv);
err_dl_रेजिस्टर:
	dpaa2_eth_disconnect_mac(priv);
err_connect_mac:
	अगर (priv->करो_link_poll)
		kthपढ़ो_stop(priv->poll_thपढ़ो);
	अन्यथा
		fsl_mc_मुक्त_irqs(dpni_dev);
err_poll_thपढ़ो:
	dpaa2_eth_मुक्त_rings(priv);
err_alloc_rings:
err_csum:
err_netdev_init:
	मुक्त_percpu(priv->sgt_cache);
err_alloc_sgt_cache:
	मुक्त_percpu(priv->percpu_extras);
err_alloc_percpu_extras:
	मुक्त_percpu(priv->percpu_stats);
err_alloc_percpu_stats:
	dpaa2_eth_del_ch_napi(priv);
err_bind:
	dpaa2_eth_मुक्त_dpbp(priv);
err_dpbp_setup:
	dpaa2_eth_मुक्त_dpio(priv);
err_dpio_setup:
	dpaa2_eth_मुक्त_dpni(priv);
err_dpni_setup:
	fsl_mc_portal_मुक्त(priv->mc_io);
err_portal_alloc:
	destroy_workqueue(priv->dpaa2_ptp_wq);
err_wq_alloc:
	dev_set_drvdata(dev, शून्य);
	मुक्त_netdev(net_dev);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_eth_हटाओ(काष्ठा fsl_mc_device *ls_dev)
अणु
	काष्ठा device *dev;
	काष्ठा net_device *net_dev;
	काष्ठा dpaa2_eth_priv *priv;

	dev = &ls_dev->dev;
	net_dev = dev_get_drvdata(dev);
	priv = netdev_priv(net_dev);

#अगर_घोषित CONFIG_DEBUG_FS
	dpaa2_dbg_हटाओ(priv);
#पूर्ण_अगर
	rtnl_lock();
	dpaa2_eth_disconnect_mac(priv);
	rtnl_unlock();

	unरेजिस्टर_netdev(net_dev);

	dpaa2_eth_dl_port_del(priv);
	dpaa2_eth_dl_traps_unरेजिस्टर(priv);
	dpaa2_eth_dl_unरेजिस्टर(priv);

	अगर (priv->करो_link_poll)
		kthपढ़ो_stop(priv->poll_thपढ़ो);
	अन्यथा
		fsl_mc_मुक्त_irqs(ls_dev);

	dpaa2_eth_मुक्त_rings(priv);
	मुक्त_percpu(priv->sgt_cache);
	मुक्त_percpu(priv->percpu_stats);
	मुक्त_percpu(priv->percpu_extras);

	dpaa2_eth_del_ch_napi(priv);
	dpaa2_eth_मुक्त_dpbp(priv);
	dpaa2_eth_मुक्त_dpio(priv);
	dpaa2_eth_मुक्त_dpni(priv);

	fsl_mc_portal_मुक्त(priv->mc_io);

	मुक्त_netdev(net_dev);

	dev_dbg(net_dev->dev.parent, "Removed interface %s\n", net_dev->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsl_mc_device_id dpaa2_eth_match_id_table[] = अणु
	अणु
		.venकरोr = FSL_MC_VENDOR_FREESCALE,
		.obj_type = "dpni",
	पूर्ण,
	अणु .venकरोr = 0x0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(fslmc, dpaa2_eth_match_id_table);

अटल काष्ठा fsl_mc_driver dpaa2_eth_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = dpaa2_eth_probe,
	.हटाओ = dpaa2_eth_हटाओ,
	.match_id_table = dpaa2_eth_match_id_table
पूर्ण;

अटल पूर्णांक __init dpaa2_eth_driver_init(व्योम)
अणु
	पूर्णांक err;

	dpaa2_eth_dbg_init();
	err = fsl_mc_driver_रेजिस्टर(&dpaa2_eth_driver);
	अगर (err) अणु
		dpaa2_eth_dbg_निकास();
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास dpaa2_eth_driver_निकास(व्योम)
अणु
	dpaa2_eth_dbg_निकास();
	fsl_mc_driver_unरेजिस्टर(&dpaa2_eth_driver);
पूर्ण

module_init(dpaa2_eth_driver_init);
module_निकास(dpaa2_eth_driver_निकास);
