<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2018-2019 Hisilicon Limited. */

/* This must be outside अगरdef _HNS3_TRACE_H */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hns3

#अगर !defined(_HNS3_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _HNS3_TRACE_H_

#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा DESC_NR		(माप(काष्ठा hns3_desc) / माप(u32))

DECLARE_EVENT_CLASS(hns3_skb_ढाँचा,
	TP_PROTO(काष्ठा sk_buff *skb),
	TP_ARGS(skb),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, headlen)
		__field(अचिन्हित पूर्णांक, len)
		__field(__u8, nr_frags)
		__field(__u8, ip_summed)
		__field(अचिन्हित पूर्णांक, hdr_len)
		__field(अचिन्हित लघु, gso_size)
		__field(अचिन्हित लघु, gso_segs)
		__field(अचिन्हित पूर्णांक, gso_type)
		__field(bool, fraglist)
		__array(__u32, size, MAX_SKB_FRAGS)
	),

	TP_fast_assign(
		__entry->headlen = skb_headlen(skb);
		__entry->len = skb->len;
		__entry->nr_frags = skb_shinfo(skb)->nr_frags;
		__entry->gso_size = skb_shinfo(skb)->gso_size;
		__entry->gso_segs = skb_shinfo(skb)->gso_segs;
		__entry->gso_type = skb_shinfo(skb)->gso_type;
		__entry->hdr_len = skb->encapsulation ?
		skb_inner_transport_offset(skb) + inner_tcp_hdrlen(skb) :
		skb_transport_offset(skb) + tcp_hdrlen(skb);
		__entry->ip_summed = skb->ip_summed;
		__entry->fraglist = skb_has_frag_list(skb);
		hns3_shinfo_pack(skb_shinfo(skb), __entry->size);
	),

	TP_prपूर्णांकk(
		"len: %u, %u, %u, cs: %u, gso: %u, %u, %x, frag(%d %u): %s",
		__entry->headlen, __entry->len, __entry->hdr_len,
		__entry->ip_summed, __entry->gso_size, __entry->gso_segs,
		__entry->gso_type, __entry->fraglist, __entry->nr_frags,
		__prपूर्णांक_array(__entry->size, MAX_SKB_FRAGS, माप(__u32))
	)
);

DEFINE_EVENT(hns3_skb_ढाँचा, hns3_over_max_bd,
	TP_PROTO(काष्ठा sk_buff *skb),
	TP_ARGS(skb));

DEFINE_EVENT(hns3_skb_ढाँचा, hns3_gro,
	TP_PROTO(काष्ठा sk_buff *skb),
	TP_ARGS(skb));

DEFINE_EVENT(hns3_skb_ढाँचा, hns3_tso,
	TP_PROTO(काष्ठा sk_buff *skb),
	TP_ARGS(skb));

TRACE_EVENT(hns3_tx_desc,
	TP_PROTO(काष्ठा hns3_enet_ring *ring, पूर्णांक cur_ntu),
	TP_ARGS(ring, cur_ntu),

	TP_STRUCT__entry(
		__field(पूर्णांक, index)
		__field(पूर्णांक, ntu)
		__field(पूर्णांक, ntc)
		__field(dma_addr_t, desc_dma)
		__array(u32, desc, DESC_NR)
		__string(devname, ring->tqp->handle->kinfo.netdev->name)
	),

	TP_fast_assign(
		__entry->index = ring->tqp->tqp_index;
		__entry->ntu = ring->next_to_use;
		__entry->ntc = ring->next_to_clean;
		__entry->desc_dma = ring->desc_dma_addr,
		स_नकल(__entry->desc, &ring->desc[cur_ntu],
		       माप(काष्ठा hns3_desc));
		__assign_str(devname, ring->tqp->handle->kinfo.netdev->name);
	),

	TP_prपूर्णांकk(
		"%s-%d-%d/%d desc(%pad): %s",
		__get_str(devname), __entry->index, __entry->ntu,
		__entry->ntc, &__entry->desc_dma,
		__prपूर्णांक_array(__entry->desc, DESC_NR, माप(u32))
	)
);

TRACE_EVENT(hns3_rx_desc,
	TP_PROTO(काष्ठा hns3_enet_ring *ring),
	TP_ARGS(ring),

	TP_STRUCT__entry(
		__field(पूर्णांक, index)
		__field(पूर्णांक, ntu)
		__field(पूर्णांक, ntc)
		__field(dma_addr_t, desc_dma)
		__field(dma_addr_t, buf_dma)
		__array(u32, desc, DESC_NR)
		__string(devname, ring->tqp->handle->kinfo.netdev->name)
	),

	TP_fast_assign(
		__entry->index = ring->tqp->tqp_index;
		__entry->ntu = ring->next_to_use;
		__entry->ntc = ring->next_to_clean;
		__entry->desc_dma = ring->desc_dma_addr;
		__entry->buf_dma = ring->desc_cb[ring->next_to_clean].dma;
		स_नकल(__entry->desc, &ring->desc[ring->next_to_clean],
		       माप(काष्ठा hns3_desc));
		__assign_str(devname, ring->tqp->handle->kinfo.netdev->name);
	),

	TP_prपूर्णांकk(
		"%s-%d-%d/%d desc(%pad) buf(%pad): %s",
		__get_str(devname), __entry->index, __entry->ntu,
		__entry->ntc, &__entry->desc_dma, &__entry->buf_dma,
		__prपूर्णांक_array(__entry->desc, DESC_NR, माप(u32))
	)
);

#पूर्ण_अगर /* _HNS3_TRACE_H_ */

/* This must be outside अगरdef _HNS3_TRACE_H */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता hns3_trace
#समावेश <trace/define_trace.h>
