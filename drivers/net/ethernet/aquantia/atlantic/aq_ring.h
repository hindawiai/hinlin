<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_ring.h: Declaration of functions क्रम Rx/Tx rings. */

#अगर_अघोषित AQ_RING_H
#घोषणा AQ_RING_H

#समावेश "aq_common.h"

काष्ठा page;
काष्ठा aq_nic_cfg_s;

काष्ठा aq_rxpage अणु
	काष्ठा page *page;
	dma_addr_t daddr;
	अचिन्हित पूर्णांक order;
	अचिन्हित पूर्णांक pg_off;
पूर्ण;

/*           TxC       SOP        DX         EOP
 *         +----------+----------+----------+-----------
 *   8bytes|len l3,l4 | pa       | pa       | pa
 *         +----------+----------+----------+-----------
 * 4/8bytes|len pkt   |len pkt   |          | skb
 *         +----------+----------+----------+-----------
 * 4/8bytes|is_gso    |len,flags |len       |len,is_eop
 *         +----------+----------+----------+-----------
 *
 *  This aq_ring_buff_s करोesn't have endianness dependency.
 *  It is __packed क्रम cache line optimizations.
 */
काष्ठा __packed aq_ring_buff_s अणु
	जोड़ अणु
		/* RX/TX */
		dma_addr_t pa;
		/* RX */
		काष्ठा अणु
			u32 rss_hash;
			u16 next;
			u8 is_hash_l4;
			u8 rsvd1;
			काष्ठा aq_rxpage rxdata;
			u16 vlan_rx_tag;
		पूर्ण;
		/* EOP */
		काष्ठा अणु
			dma_addr_t pa_eop;
			काष्ठा sk_buff *skb;
		पूर्ण;
		/* TxC */
		काष्ठा अणु
			u32 mss;
			u8 len_l2;
			u8 len_l3;
			u8 len_l4;
			u8 is_ipv6:1;
			u8 rsvd2:7;
			u32 len_pkt;
			u16 vlan_tx_tag;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 len:16;
			u32 is_ip_cso:1;
			u32 is_udp_cso:1;
			u32 is_tcp_cso:1;
			u32 is_cso_err:1;
			u32 is_sop:1;
			u32 is_eop:1;
			u32 is_gso_tcp:1;
			u32 is_gso_udp:1;
			u32 is_mapped:1;
			u32 is_cleaned:1;
			u32 is_error:1;
			u32 is_vlan:1;
			u32 is_lro:1;
			u32 rsvd3:3;
			u16 eop_index;
			u16 rsvd4;
		पूर्ण;
		u64 flags;
	पूर्ण;
पूर्ण;

काष्ठा aq_ring_stats_rx_s अणु
	काष्ठा u64_stats_sync syncp;	/* must be first */
	u64 errors;
	u64 packets;
	u64 bytes;
	u64 lro_packets;
	u64 jumbo_packets;
	u64 alloc_fails;
	u64 skb_alloc_fails;
	u64 polls;
	u64 pg_losts;
	u64 pg_flips;
	u64 pg_reuses;
पूर्ण;

काष्ठा aq_ring_stats_tx_s अणु
	काष्ठा u64_stats_sync syncp;	/* must be first */
	u64 errors;
	u64 packets;
	u64 bytes;
	u64 queue_restarts;
पूर्ण;

जोड़ aq_ring_stats_s अणु
	काष्ठा aq_ring_stats_rx_s rx;
	काष्ठा aq_ring_stats_tx_s tx;
पूर्ण;

क्रमागत atl_ring_type अणु
	ATL_RING_TX,
	ATL_RING_RX,
पूर्ण;

काष्ठा aq_ring_s अणु
	काष्ठा aq_ring_buff_s *buff_ring;
	u8 *dx_ring;		/* descriptors ring, dma shared mem */
	काष्ठा aq_nic_s *aq_nic;
	अचिन्हित पूर्णांक idx;	/* क्रम HW layer रेजिस्टरs operations */
	अचिन्हित पूर्णांक hw_head;
	अचिन्हित पूर्णांक sw_head;
	अचिन्हित पूर्णांक sw_tail;
	अचिन्हित पूर्णांक size;	/* descriptors number */
	अचिन्हित पूर्णांक dx_size;	/* TX or RX descriptor size,  */
				/* stored here क्रम fater math */
	अचिन्हित पूर्णांक page_order;
	जोड़ aq_ring_stats_s stats;
	dma_addr_t dx_ring_pa;
	क्रमागत atl_ring_type ring_type;
पूर्ण;

काष्ठा aq_ring_param_s अणु
	अचिन्हित पूर्णांक vec_idx;
	अचिन्हित पूर्णांक cpu;
	cpumask_t affinity_mask;
पूर्ण;

अटल अंतरभूत व्योम *aq_buf_vaddr(काष्ठा aq_rxpage *rxpage)
अणु
	वापस page_to_virt(rxpage->page) + rxpage->pg_off;
पूर्ण

अटल अंतरभूत dma_addr_t aq_buf_daddr(काष्ठा aq_rxpage *rxpage)
अणु
	वापस rxpage->daddr + rxpage->pg_off;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक aq_ring_next_dx(काष्ठा aq_ring_s *self,
					   अचिन्हित पूर्णांक dx)
अणु
	वापस (++dx >= self->size) ? 0U : dx;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक aq_ring_avail_dx(काष्ठा aq_ring_s *self)
अणु
	वापस (((self->sw_tail >= self->sw_head)) ?
		(self->size - 1) - self->sw_tail + self->sw_head :
		self->sw_head - self->sw_tail - 1);
पूर्ण

काष्ठा aq_ring_s *aq_ring_tx_alloc(काष्ठा aq_ring_s *self,
				   काष्ठा aq_nic_s *aq_nic,
				   अचिन्हित पूर्णांक idx,
				   काष्ठा aq_nic_cfg_s *aq_nic_cfg);
काष्ठा aq_ring_s *aq_ring_rx_alloc(काष्ठा aq_ring_s *self,
				   काष्ठा aq_nic_s *aq_nic,
				   अचिन्हित पूर्णांक idx,
				   काष्ठा aq_nic_cfg_s *aq_nic_cfg);
पूर्णांक aq_ring_init(काष्ठा aq_ring_s *self, स्थिर क्रमागत atl_ring_type ring_type);
व्योम aq_ring_rx_deinit(काष्ठा aq_ring_s *self);
व्योम aq_ring_मुक्त(काष्ठा aq_ring_s *self);
व्योम aq_ring_update_queue_state(काष्ठा aq_ring_s *ring);
व्योम aq_ring_queue_wake(काष्ठा aq_ring_s *ring);
व्योम aq_ring_queue_stop(काष्ठा aq_ring_s *ring);
bool aq_ring_tx_clean(काष्ठा aq_ring_s *self);
पूर्णांक aq_ring_rx_clean(काष्ठा aq_ring_s *self,
		     काष्ठा napi_काष्ठा *napi,
		     पूर्णांक *work_करोne,
		     पूर्णांक budget);
पूर्णांक aq_ring_rx_fill(काष्ठा aq_ring_s *self);

काष्ठा aq_ring_s *aq_ring_hwts_rx_alloc(काष्ठा aq_ring_s *self,
		काष्ठा aq_nic_s *aq_nic, अचिन्हित पूर्णांक idx,
		अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक dx_size);
व्योम aq_ring_hwts_rx_clean(काष्ठा aq_ring_s *self, काष्ठा aq_nic_s *aq_nic);

अचिन्हित पूर्णांक aq_ring_fill_stats_data(काष्ठा aq_ring_s *self, u64 *data);

#पूर्ण_अगर /* AQ_RING_H */
