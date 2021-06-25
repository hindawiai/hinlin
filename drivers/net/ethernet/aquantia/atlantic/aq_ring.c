<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_ring.c: Definition of functions क्रम Rx/Tx rings. */

#समावेश "aq_ring.h"
#समावेश "aq_nic.h"
#समावेश "aq_hw.h"
#समावेश "aq_hw_utils.h"
#समावेश "aq_ptp.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>

अटल अंतरभूत व्योम aq_मुक्त_rxpage(काष्ठा aq_rxpage *rxpage, काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक len = PAGE_SIZE << rxpage->order;

	dma_unmap_page(dev, rxpage->daddr, len, DMA_FROM_DEVICE);

	/* Drop the ref क्रम being in the ring. */
	__मुक्त_pages(rxpage->page, rxpage->order);
	rxpage->page = शून्य;
पूर्ण

अटल पूर्णांक aq_get_rxpage(काष्ठा aq_rxpage *rxpage, अचिन्हित पूर्णांक order,
			 काष्ठा device *dev)
अणु
	काष्ठा page *page;
	पूर्णांक ret = -ENOMEM;
	dma_addr_t daddr;

	page = dev_alloc_pages(order);
	अगर (unlikely(!page))
		जाओ err_निकास;

	daddr = dma_map_page(dev, page, 0, PAGE_SIZE << order,
			     DMA_FROM_DEVICE);

	अगर (unlikely(dma_mapping_error(dev, daddr)))
		जाओ मुक्त_page;

	rxpage->page = page;
	rxpage->daddr = daddr;
	rxpage->order = order;
	rxpage->pg_off = 0;

	वापस 0;

मुक्त_page:
	__मुक्त_pages(page, order);

err_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक aq_get_rxpages(काष्ठा aq_ring_s *self, काष्ठा aq_ring_buff_s *rxbuf,
			  पूर्णांक order)
अणु
	पूर्णांक ret;

	अगर (rxbuf->rxdata.page) अणु
		/* One means ring is the only user and can reuse */
		अगर (page_ref_count(rxbuf->rxdata.page) > 1) अणु
			/* Try reuse buffer */
			rxbuf->rxdata.pg_off += AQ_CFG_RX_FRAME_MAX;
			अगर (rxbuf->rxdata.pg_off + AQ_CFG_RX_FRAME_MAX <=
				(PAGE_SIZE << order)) अणु
				u64_stats_update_begin(&self->stats.rx.syncp);
				self->stats.rx.pg_flips++;
				u64_stats_update_end(&self->stats.rx.syncp);
			पूर्ण अन्यथा अणु
				/* Buffer exhausted. We have other users and
				 * should release this page and पुनः_स्मृति
				 */
				aq_मुक्त_rxpage(&rxbuf->rxdata,
					       aq_nic_get_dev(self->aq_nic));
				u64_stats_update_begin(&self->stats.rx.syncp);
				self->stats.rx.pg_losts++;
				u64_stats_update_end(&self->stats.rx.syncp);
			पूर्ण
		पूर्ण अन्यथा अणु
			rxbuf->rxdata.pg_off = 0;
			u64_stats_update_begin(&self->stats.rx.syncp);
			self->stats.rx.pg_reuses++;
			u64_stats_update_end(&self->stats.rx.syncp);
		पूर्ण
	पूर्ण

	अगर (!rxbuf->rxdata.page) अणु
		ret = aq_get_rxpage(&rxbuf->rxdata, order,
				    aq_nic_get_dev(self->aq_nic));
		अगर (ret) अणु
			u64_stats_update_begin(&self->stats.rx.syncp);
			self->stats.rx.alloc_fails++;
			u64_stats_update_end(&self->stats.rx.syncp);
		पूर्ण
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा aq_ring_s *aq_ring_alloc(काष्ठा aq_ring_s *self,
				       काष्ठा aq_nic_s *aq_nic)
अणु
	पूर्णांक err = 0;

	self->buff_ring =
		kसुस्मृति(self->size, माप(काष्ठा aq_ring_buff_s), GFP_KERNEL);

	अगर (!self->buff_ring) अणु
		err = -ENOMEM;
		जाओ err_निकास;
	पूर्ण
	self->dx_ring = dma_alloc_coherent(aq_nic_get_dev(aq_nic),
					   self->size * self->dx_size,
					   &self->dx_ring_pa, GFP_KERNEL);
	अगर (!self->dx_ring) अणु
		err = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

err_निकास:
	अगर (err < 0) अणु
		aq_ring_मुक्त(self);
		self = शून्य;
	पूर्ण

	वापस self;
पूर्ण

काष्ठा aq_ring_s *aq_ring_tx_alloc(काष्ठा aq_ring_s *self,
				   काष्ठा aq_nic_s *aq_nic,
				   अचिन्हित पूर्णांक idx,
				   काष्ठा aq_nic_cfg_s *aq_nic_cfg)
अणु
	पूर्णांक err = 0;

	self->aq_nic = aq_nic;
	self->idx = idx;
	self->size = aq_nic_cfg->txds;
	self->dx_size = aq_nic_cfg->aq_hw_caps->txd_size;

	self = aq_ring_alloc(self, aq_nic);
	अगर (!self) अणु
		err = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

err_निकास:
	अगर (err < 0) अणु
		aq_ring_मुक्त(self);
		self = शून्य;
	पूर्ण

	वापस self;
पूर्ण

काष्ठा aq_ring_s *aq_ring_rx_alloc(काष्ठा aq_ring_s *self,
				   काष्ठा aq_nic_s *aq_nic,
				   अचिन्हित पूर्णांक idx,
				   काष्ठा aq_nic_cfg_s *aq_nic_cfg)
अणु
	पूर्णांक err = 0;

	self->aq_nic = aq_nic;
	self->idx = idx;
	self->size = aq_nic_cfg->rxds;
	self->dx_size = aq_nic_cfg->aq_hw_caps->rxd_size;
	self->page_order = fls(AQ_CFG_RX_FRAME_MAX / PAGE_SIZE +
			       (AQ_CFG_RX_FRAME_MAX % PAGE_SIZE ? 1 : 0)) - 1;

	अगर (aq_nic_cfg->rxpageorder > self->page_order)
		self->page_order = aq_nic_cfg->rxpageorder;

	self = aq_ring_alloc(self, aq_nic);
	अगर (!self) अणु
		err = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

err_निकास:
	अगर (err < 0) अणु
		aq_ring_मुक्त(self);
		self = शून्य;
	पूर्ण

	वापस self;
पूर्ण

काष्ठा aq_ring_s *
aq_ring_hwts_rx_alloc(काष्ठा aq_ring_s *self, काष्ठा aq_nic_s *aq_nic,
		      अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक dx_size)
अणु
	काष्ठा device *dev = aq_nic_get_dev(aq_nic);
	माप_प्रकार sz = size * dx_size + AQ_CFG_RXDS_DEF;

	स_रखो(self, 0, माप(*self));

	self->aq_nic = aq_nic;
	self->idx = idx;
	self->size = size;
	self->dx_size = dx_size;

	self->dx_ring = dma_alloc_coherent(dev, sz, &self->dx_ring_pa,
					   GFP_KERNEL);
	अगर (!self->dx_ring) अणु
		aq_ring_मुक्त(self);
		वापस शून्य;
	पूर्ण

	वापस self;
पूर्ण

पूर्णांक aq_ring_init(काष्ठा aq_ring_s *self, स्थिर क्रमागत atl_ring_type ring_type)
अणु
	self->hw_head = 0;
	self->sw_head = 0;
	self->sw_tail = 0;
	self->ring_type = ring_type;

	अगर (self->ring_type == ATL_RING_RX)
		u64_stats_init(&self->stats.rx.syncp);
	अन्यथा
		u64_stats_init(&self->stats.tx.syncp);

	वापस 0;
पूर्ण

अटल अंतरभूत bool aq_ring_dx_in_range(अचिन्हित पूर्णांक h, अचिन्हित पूर्णांक i,
				       अचिन्हित पूर्णांक t)
अणु
	वापस (h < t) ? ((h < i) && (i < t)) : ((h < i) || (i < t));
पूर्ण

व्योम aq_ring_update_queue_state(काष्ठा aq_ring_s *ring)
अणु
	अगर (aq_ring_avail_dx(ring) <= AQ_CFG_SKB_FRAGS_MAX)
		aq_ring_queue_stop(ring);
	अन्यथा अगर (aq_ring_avail_dx(ring) > AQ_CFG_RESTART_DESC_THRES)
		aq_ring_queue_wake(ring);
पूर्ण

व्योम aq_ring_queue_wake(काष्ठा aq_ring_s *ring)
अणु
	काष्ठा net_device *ndev = aq_nic_get_ndev(ring->aq_nic);

	अगर (__netअगर_subqueue_stopped(ndev,
				     AQ_NIC_RING2QMAP(ring->aq_nic,
						      ring->idx))) अणु
		netअगर_wake_subqueue(ndev,
				    AQ_NIC_RING2QMAP(ring->aq_nic, ring->idx));
		u64_stats_update_begin(&ring->stats.tx.syncp);
		ring->stats.tx.queue_restarts++;
		u64_stats_update_end(&ring->stats.tx.syncp);
	पूर्ण
पूर्ण

व्योम aq_ring_queue_stop(काष्ठा aq_ring_s *ring)
अणु
	काष्ठा net_device *ndev = aq_nic_get_ndev(ring->aq_nic);

	अगर (!__netअगर_subqueue_stopped(ndev,
				      AQ_NIC_RING2QMAP(ring->aq_nic,
						       ring->idx)))
		netअगर_stop_subqueue(ndev,
				    AQ_NIC_RING2QMAP(ring->aq_nic, ring->idx));
पूर्ण

bool aq_ring_tx_clean(काष्ठा aq_ring_s *self)
अणु
	काष्ठा device *dev = aq_nic_get_dev(self->aq_nic);
	अचिन्हित पूर्णांक budget;

	क्रम (budget = AQ_CFG_TX_CLEAN_BUDGET;
	     budget && self->sw_head != self->hw_head; budget--) अणु
		काष्ठा aq_ring_buff_s *buff = &self->buff_ring[self->sw_head];

		अगर (likely(buff->is_mapped)) अणु
			अगर (unlikely(buff->is_sop)) अणु
				अगर (!buff->is_eop &&
				    buff->eop_index != 0xffffU &&
				    (!aq_ring_dx_in_range(self->sw_head,
						buff->eop_index,
						self->hw_head)))
					अवरोध;

				dma_unmap_single(dev, buff->pa, buff->len,
						 DMA_TO_DEVICE);
			पूर्ण अन्यथा अणु
				dma_unmap_page(dev, buff->pa, buff->len,
					       DMA_TO_DEVICE);
			पूर्ण
		पूर्ण

		अगर (unlikely(buff->is_eop)) अणु
			u64_stats_update_begin(&self->stats.tx.syncp);
			++self->stats.tx.packets;
			self->stats.tx.bytes += buff->skb->len;
			u64_stats_update_end(&self->stats.tx.syncp);

			dev_kमुक्त_skb_any(buff->skb);
		पूर्ण
		buff->pa = 0U;
		buff->eop_index = 0xffffU;
		self->sw_head = aq_ring_next_dx(self, self->sw_head);
	पूर्ण

	वापस !!budget;
पूर्ण

अटल व्योम aq_rx_checksum(काष्ठा aq_ring_s *self,
			   काष्ठा aq_ring_buff_s *buff,
			   काष्ठा sk_buff *skb)
अणु
	अगर (!(self->aq_nic->ndev->features & NETIF_F_RXCSUM))
		वापस;

	अगर (unlikely(buff->is_cso_err)) अणु
		u64_stats_update_begin(&self->stats.rx.syncp);
		++self->stats.rx.errors;
		u64_stats_update_end(&self->stats.rx.syncp);
		skb->ip_summed = CHECKSUM_NONE;
		वापस;
	पूर्ण
	अगर (buff->is_ip_cso) अणु
		__skb_incr_checksum_unnecessary(skb);
	पूर्ण अन्यथा अणु
		skb->ip_summed = CHECKSUM_NONE;
	पूर्ण

	अगर (buff->is_udp_cso || buff->is_tcp_cso)
		__skb_incr_checksum_unnecessary(skb);
पूर्ण

#घोषणा AQ_SKB_ALIGN SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info))
पूर्णांक aq_ring_rx_clean(काष्ठा aq_ring_s *self,
		     काष्ठा napi_काष्ठा *napi,
		     पूर्णांक *work_करोne,
		     पूर्णांक budget)
अणु
	काष्ठा net_device *ndev = aq_nic_get_ndev(self->aq_nic);
	bool is_rsc_completed = true;
	पूर्णांक err = 0;

	क्रम (; (self->sw_head != self->hw_head) && budget;
		self->sw_head = aq_ring_next_dx(self, self->sw_head),
		--budget, ++(*work_करोne)) अणु
		काष्ठा aq_ring_buff_s *buff = &self->buff_ring[self->sw_head];
		bool is_ptp_ring = aq_ptp_ring(self->aq_nic, self);
		काष्ठा aq_ring_buff_s *buff_ = शून्य;
		काष्ठा sk_buff *skb = शून्य;
		अचिन्हित पूर्णांक next_ = 0U;
		अचिन्हित पूर्णांक i = 0U;
		u16 hdr_len;

		अगर (buff->is_cleaned)
			जारी;

		अगर (!buff->is_eop) अणु
			buff_ = buff;
			करो अणु
				next_ = buff_->next,
				buff_ = &self->buff_ring[next_];
				is_rsc_completed =
					aq_ring_dx_in_range(self->sw_head,
							    next_,
							    self->hw_head);

				अगर (unlikely(!is_rsc_completed))
					अवरोध;

				buff->is_error |= buff_->is_error;
				buff->is_cso_err |= buff_->is_cso_err;

			पूर्ण जबतक (!buff_->is_eop);

			अगर (!is_rsc_completed) अणु
				err = 0;
				जाओ err_निकास;
			पूर्ण
			अगर (buff->is_error ||
			    (buff->is_lro && buff->is_cso_err)) अणु
				buff_ = buff;
				करो अणु
					next_ = buff_->next,
					buff_ = &self->buff_ring[next_];

					buff_->is_cleaned = true;
				पूर्ण जबतक (!buff_->is_eop);

				u64_stats_update_begin(&self->stats.rx.syncp);
				++self->stats.rx.errors;
				u64_stats_update_end(&self->stats.rx.syncp);
				जारी;
			पूर्ण
		पूर्ण

		अगर (buff->is_error) अणु
			u64_stats_update_begin(&self->stats.rx.syncp);
			++self->stats.rx.errors;
			u64_stats_update_end(&self->stats.rx.syncp);
			जारी;
		पूर्ण

		dma_sync_single_range_क्रम_cpu(aq_nic_get_dev(self->aq_nic),
					      buff->rxdata.daddr,
					      buff->rxdata.pg_off,
					      buff->len, DMA_FROM_DEVICE);

		skb = napi_alloc_skb(napi, AQ_CFG_RX_HDR_SIZE);
		अगर (unlikely(!skb)) अणु
			u64_stats_update_begin(&self->stats.rx.syncp);
			self->stats.rx.skb_alloc_fails++;
			u64_stats_update_end(&self->stats.rx.syncp);
			err = -ENOMEM;
			जाओ err_निकास;
		पूर्ण
		अगर (is_ptp_ring)
			buff->len -=
				aq_ptp_extract_ts(self->aq_nic, skb,
						  aq_buf_vaddr(&buff->rxdata),
						  buff->len);

		hdr_len = buff->len;
		अगर (hdr_len > AQ_CFG_RX_HDR_SIZE)
			hdr_len = eth_get_headlen(skb->dev,
						  aq_buf_vaddr(&buff->rxdata),
						  AQ_CFG_RX_HDR_SIZE);

		स_नकल(__skb_put(skb, hdr_len), aq_buf_vaddr(&buff->rxdata),
		       ALIGN(hdr_len, माप(दीर्घ)));

		अगर (buff->len - hdr_len > 0) अणु
			skb_add_rx_frag(skb, 0, buff->rxdata.page,
					buff->rxdata.pg_off + hdr_len,
					buff->len - hdr_len,
					AQ_CFG_RX_FRAME_MAX);
			page_ref_inc(buff->rxdata.page);
		पूर्ण

		अगर (!buff->is_eop) अणु
			buff_ = buff;
			i = 1U;
			करो अणु
				next_ = buff_->next;
				buff_ = &self->buff_ring[next_];

				dma_sync_single_range_क्रम_cpu(aq_nic_get_dev(self->aq_nic),
							      buff_->rxdata.daddr,
							      buff_->rxdata.pg_off,
							      buff_->len,
							      DMA_FROM_DEVICE);
				skb_add_rx_frag(skb, i++,
						buff_->rxdata.page,
						buff_->rxdata.pg_off,
						buff_->len,
						AQ_CFG_RX_FRAME_MAX);
				page_ref_inc(buff_->rxdata.page);
				buff_->is_cleaned = 1;

				buff->is_ip_cso &= buff_->is_ip_cso;
				buff->is_udp_cso &= buff_->is_udp_cso;
				buff->is_tcp_cso &= buff_->is_tcp_cso;
				buff->is_cso_err |= buff_->is_cso_err;

			पूर्ण जबतक (!buff_->is_eop);
		पूर्ण

		अगर (buff->is_vlan)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       buff->vlan_rx_tag);

		skb->protocol = eth_type_trans(skb, ndev);

		aq_rx_checksum(self, buff, skb);

		skb_set_hash(skb, buff->rss_hash,
			     buff->is_hash_l4 ? PKT_HASH_TYPE_L4 :
			     PKT_HASH_TYPE_NONE);
		/* Send all PTP traffic to 0 queue */
		skb_record_rx_queue(skb,
				    is_ptp_ring ? 0
						: AQ_NIC_RING2QMAP(self->aq_nic,
								   self->idx));

		u64_stats_update_begin(&self->stats.rx.syncp);
		++self->stats.rx.packets;
		self->stats.rx.bytes += skb->len;
		u64_stats_update_end(&self->stats.rx.syncp);

		napi_gro_receive(napi, skb);
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

व्योम aq_ring_hwts_rx_clean(काष्ठा aq_ring_s *self, काष्ठा aq_nic_s *aq_nic)
अणु
#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
	जबतक (self->sw_head != self->hw_head) अणु
		u64 ns;

		aq_nic->aq_hw_ops->extract_hwts(aq_nic->aq_hw,
						self->dx_ring +
						(self->sw_head * self->dx_size),
						self->dx_size, &ns);
		aq_ptp_tx_hwtstamp(aq_nic, ns);

		self->sw_head = aq_ring_next_dx(self, self->sw_head);
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक aq_ring_rx_fill(काष्ठा aq_ring_s *self)
अणु
	अचिन्हित पूर्णांक page_order = self->page_order;
	काष्ठा aq_ring_buff_s *buff = शून्य;
	पूर्णांक err = 0;
	पूर्णांक i = 0;

	अगर (aq_ring_avail_dx(self) < min_t(अचिन्हित पूर्णांक, AQ_CFG_RX_REFILL_THRES,
					   self->size / 2))
		वापस err;

	क्रम (i = aq_ring_avail_dx(self); i--;
		self->sw_tail = aq_ring_next_dx(self, self->sw_tail)) अणु
		buff = &self->buff_ring[self->sw_tail];

		buff->flags = 0U;
		buff->len = AQ_CFG_RX_FRAME_MAX;

		err = aq_get_rxpages(self, buff, page_order);
		अगर (err)
			जाओ err_निकास;

		buff->pa = aq_buf_daddr(&buff->rxdata);
		buff = शून्य;
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

व्योम aq_ring_rx_deinit(काष्ठा aq_ring_s *self)
अणु
	अगर (!self)
		वापस;

	क्रम (; self->sw_head != self->sw_tail;
		self->sw_head = aq_ring_next_dx(self, self->sw_head)) अणु
		काष्ठा aq_ring_buff_s *buff = &self->buff_ring[self->sw_head];

		aq_मुक्त_rxpage(&buff->rxdata, aq_nic_get_dev(self->aq_nic));
	पूर्ण
पूर्ण

व्योम aq_ring_मुक्त(काष्ठा aq_ring_s *self)
अणु
	अगर (!self)
		वापस;

	kमुक्त(self->buff_ring);

	अगर (self->dx_ring)
		dma_मुक्त_coherent(aq_nic_get_dev(self->aq_nic),
				  self->size * self->dx_size, self->dx_ring,
				  self->dx_ring_pa);
पूर्ण

अचिन्हित पूर्णांक aq_ring_fill_stats_data(काष्ठा aq_ring_s *self, u64 *data)
अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक start;

	अगर (self->ring_type == ATL_RING_RX) अणु
		/* This data should mimic aq_ethtool_queue_rx_stat_names काष्ठाure */
		करो अणु
			count = 0;
			start = u64_stats_fetch_begin_irq(&self->stats.rx.syncp);
			data[count] = self->stats.rx.packets;
			data[++count] = self->stats.rx.jumbo_packets;
			data[++count] = self->stats.rx.lro_packets;
			data[++count] = self->stats.rx.errors;
			data[++count] = self->stats.rx.alloc_fails;
			data[++count] = self->stats.rx.skb_alloc_fails;
			data[++count] = self->stats.rx.polls;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&self->stats.rx.syncp, start));
	पूर्ण अन्यथा अणु
		/* This data should mimic aq_ethtool_queue_tx_stat_names काष्ठाure */
		करो अणु
			count = 0;
			start = u64_stats_fetch_begin_irq(&self->stats.tx.syncp);
			data[count] = self->stats.tx.packets;
			data[++count] = self->stats.tx.queue_restarts;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&self->stats.tx.syncp, start));
	पूर्ण

	वापस ++count;
पूर्ण
