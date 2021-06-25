<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/net/xdp.h
 *
 * Copyright (c) 2017 Jesper Dangaard Brouer, Red Hat Inc.
 */
#अगर_अघोषित __LINUX_NET_XDP_H__
#घोषणा __LINUX_NET_XDP_H__

#समावेश <linux/skbuff.h> /* skb_shared_info */

/**
 * DOC: XDP RX-queue inक्रमmation
 *
 * The XDP RX-queue info (xdp_rxq_info) is associated with the driver
 * level RX-ring queues.  It is inक्रमmation that is specअगरic to how
 * the driver have configured a given RX-ring queue.
 *
 * Each xdp_buff frame received in the driver carry a (poपूर्णांकer)
 * reference to this xdp_rxq_info काष्ठाure.  This provides the XDP
 * data-path पढ़ो-access to RX-info क्रम both kernel and bpf-side
 * (limited subset).
 *
 * For now, direct access is only safe जबतक running in NAPI/softirq
 * context.  Contents is पढ़ो-mostly and must not be updated during
 * driver NAPI/softirq poll.
 *
 * The driver usage API is a रेजिस्टर and unरेजिस्टर API.
 *
 * The काष्ठा is not directly tied to the XDP prog.  A new XDP prog
 * can be attached as दीर्घ as it करोesn't change the underlying
 * RX-ring.  If the RX-ring करोes change signअगरicantly, the NIC driver
 * naturally need to stop the RX-ring beक्रमe purging and पुनः_स्मृतिating
 * memory.  In that process the driver MUST call unregistor (which
 * also apply क्रम driver shutकरोwn and unload).  The रेजिस्टर API is
 * also mandatory during RX-ring setup.
 */

क्रमागत xdp_mem_type अणु
	MEM_TYPE_PAGE_SHARED = 0, /* Split-page refcnt based model */
	MEM_TYPE_PAGE_ORDER0,     /* Orig XDP full page model */
	MEM_TYPE_PAGE_POOL,
	MEM_TYPE_XSK_BUFF_POOL,
	MEM_TYPE_MAX,
पूर्ण;

/* XDP flags क्रम nकरो_xdp_xmit */
#घोषणा XDP_XMIT_FLUSH		(1U << 0)	/* करोorbell संकेत consumer */
#घोषणा XDP_XMIT_FLAGS_MASK	XDP_XMIT_FLUSH

काष्ठा xdp_mem_info अणु
	u32 type; /* क्रमागत xdp_mem_type, but known size type */
	u32 id;
पूर्ण;

काष्ठा page_pool;

काष्ठा xdp_rxq_info अणु
	काष्ठा net_device *dev;
	u32 queue_index;
	u32 reg_state;
	काष्ठा xdp_mem_info mem;
	अचिन्हित पूर्णांक napi_id;
पूर्ण ____cacheline_aligned; /* perf critical, aव्योम false-sharing */

काष्ठा xdp_txq_info अणु
	काष्ठा net_device *dev;
पूर्ण;

काष्ठा xdp_buff अणु
	व्योम *data;
	व्योम *data_end;
	व्योम *data_meta;
	व्योम *data_hard_start;
	काष्ठा xdp_rxq_info *rxq;
	काष्ठा xdp_txq_info *txq;
	u32 frame_sz; /* frame size to deduce data_hard_end/reserved tailroom*/
पूर्ण;

अटल __always_अंतरभूत व्योम
xdp_init_buff(काष्ठा xdp_buff *xdp, u32 frame_sz, काष्ठा xdp_rxq_info *rxq)
अणु
	xdp->frame_sz = frame_sz;
	xdp->rxq = rxq;
पूर्ण

अटल __always_अंतरभूत व्योम
xdp_prepare_buff(काष्ठा xdp_buff *xdp, अचिन्हित अक्षर *hard_start,
		 पूर्णांक headroom, पूर्णांक data_len, स्थिर bool meta_valid)
अणु
	अचिन्हित अक्षर *data = hard_start + headroom;

	xdp->data_hard_start = hard_start;
	xdp->data = data;
	xdp->data_end = data + data_len;
	xdp->data_meta = meta_valid ? data : data + 1;
पूर्ण

/* Reserve memory area at end-of data area.
 *
 * This macro reserves tailroom in the XDP buffer by limiting the
 * XDP/BPF data access to data_hard_end.  Notice same area (and size)
 * is used क्रम XDP_PASS, when स्थिरructing the SKB via build_skb().
 */
#घोषणा xdp_data_hard_end(xdp)				\
	((xdp)->data_hard_start + (xdp)->frame_sz -	\
	 SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

अटल अंतरभूत काष्ठा skb_shared_info *
xdp_get_shared_info_from_buff(काष्ठा xdp_buff *xdp)
अणु
	वापस (काष्ठा skb_shared_info *)xdp_data_hard_end(xdp);
पूर्ण

काष्ठा xdp_frame अणु
	व्योम *data;
	u16 len;
	u16 headroom;
	u32 metasize:8;
	u32 frame_sz:24;
	/* Lअगरeसमय of xdp_rxq_info is limited to NAPI/enqueue समय,
	 * जबतक mem info is valid on remote CPU.
	 */
	काष्ठा xdp_mem_info mem;
	काष्ठा net_device *dev_rx; /* used by cpumap */
पूर्ण;

#घोषणा XDP_BULK_QUEUE_SIZE	16
काष्ठा xdp_frame_bulk अणु
	पूर्णांक count;
	व्योम *xa;
	व्योम *q[XDP_BULK_QUEUE_SIZE];
पूर्ण;

अटल __always_अंतरभूत व्योम xdp_frame_bulk_init(काष्ठा xdp_frame_bulk *bq)
अणु
	/* bq->count will be zero'ed when bq->xa माला_लो updated */
	bq->xa = शून्य;
पूर्ण

अटल अंतरभूत काष्ठा skb_shared_info *
xdp_get_shared_info_from_frame(काष्ठा xdp_frame *frame)
अणु
	व्योम *data_hard_start = frame->data - frame->headroom - माप(*frame);

	वापस (काष्ठा skb_shared_info *)(data_hard_start + frame->frame_sz -
				SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)));
पूर्ण

काष्ठा xdp_cpumap_stats अणु
	अचिन्हित पूर्णांक redirect;
	अचिन्हित पूर्णांक pass;
	अचिन्हित पूर्णांक drop;
पूर्ण;

/* Clear kernel poपूर्णांकers in xdp_frame */
अटल अंतरभूत व्योम xdp_scrub_frame(काष्ठा xdp_frame *frame)
अणु
	frame->data = शून्य;
	frame->dev_rx = शून्य;
पूर्ण

/* Aव्योमs inlining WARN macro in fast-path */
व्योम xdp_warn(स्थिर अक्षर *msg, स्थिर अक्षर *func, स्थिर पूर्णांक line);
#घोषणा XDP_WARN(msg) xdp_warn(msg, __func__, __LINE__)

काष्ठा xdp_frame *xdp_convert_zc_to_xdp_frame(काष्ठा xdp_buff *xdp);
काष्ठा sk_buff *__xdp_build_skb_from_frame(काष्ठा xdp_frame *xdpf,
					   काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev);
काष्ठा sk_buff *xdp_build_skb_from_frame(काष्ठा xdp_frame *xdpf,
					 काष्ठा net_device *dev);
पूर्णांक xdp_alloc_skb_bulk(व्योम **skbs, पूर्णांक n_skb, gfp_t gfp);

अटल अंतरभूत
व्योम xdp_convert_frame_to_buff(काष्ठा xdp_frame *frame, काष्ठा xdp_buff *xdp)
अणु
	xdp->data_hard_start = frame->data - frame->headroom - माप(*frame);
	xdp->data = frame->data;
	xdp->data_end = frame->data + frame->len;
	xdp->data_meta = frame->data - frame->metasize;
	xdp->frame_sz = frame->frame_sz;
पूर्ण

अटल अंतरभूत
पूर्णांक xdp_update_frame_from_buff(काष्ठा xdp_buff *xdp,
			       काष्ठा xdp_frame *xdp_frame)
अणु
	पूर्णांक metasize, headroom;

	/* Assure headroom is available क्रम storing info */
	headroom = xdp->data - xdp->data_hard_start;
	metasize = xdp->data - xdp->data_meta;
	metasize = metasize > 0 ? metasize : 0;
	अगर (unlikely((headroom - metasize) < माप(*xdp_frame)))
		वापस -ENOSPC;

	/* Catch अगर driver didn't reserve tailroom क्रम skb_shared_info */
	अगर (unlikely(xdp->data_end > xdp_data_hard_end(xdp))) अणु
		XDP_WARN("Driver BUG: missing reserved tailroom");
		वापस -ENOSPC;
	पूर्ण

	xdp_frame->data = xdp->data;
	xdp_frame->len  = xdp->data_end - xdp->data;
	xdp_frame->headroom = headroom - माप(*xdp_frame);
	xdp_frame->metasize = metasize;
	xdp_frame->frame_sz = xdp->frame_sz;

	वापस 0;
पूर्ण

/* Convert xdp_buff to xdp_frame */
अटल अंतरभूत
काष्ठा xdp_frame *xdp_convert_buff_to_frame(काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_frame *xdp_frame;

	अगर (xdp->rxq->mem.type == MEM_TYPE_XSK_BUFF_POOL)
		वापस xdp_convert_zc_to_xdp_frame(xdp);

	/* Store info in top of packet */
	xdp_frame = xdp->data_hard_start;
	अगर (unlikely(xdp_update_frame_from_buff(xdp, xdp_frame) < 0))
		वापस शून्य;

	/* rxq only valid until napi_schedule ends, convert to xdp_mem_info */
	xdp_frame->mem = xdp->rxq->mem;

	वापस xdp_frame;
पूर्ण

व्योम xdp_वापस_frame(काष्ठा xdp_frame *xdpf);
व्योम xdp_वापस_frame_rx_napi(काष्ठा xdp_frame *xdpf);
व्योम xdp_वापस_buff(काष्ठा xdp_buff *xdp);
व्योम xdp_flush_frame_bulk(काष्ठा xdp_frame_bulk *bq);
व्योम xdp_वापस_frame_bulk(काष्ठा xdp_frame *xdpf,
			   काष्ठा xdp_frame_bulk *bq);

/* When sending xdp_frame पूर्णांकo the network stack, then there is no
 * वापस poपूर्णांक callback, which is needed to release e.g. DMA-mapping
 * resources with page_pool.  Thus, have explicit function to release
 * frame resources.
 */
व्योम __xdp_release_frame(व्योम *data, काष्ठा xdp_mem_info *mem);
अटल अंतरभूत व्योम xdp_release_frame(काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा xdp_mem_info *mem = &xdpf->mem;

	/* Curr only page_pool needs this */
	अगर (mem->type == MEM_TYPE_PAGE_POOL)
		__xdp_release_frame(xdpf->data, mem);
पूर्ण

पूर्णांक xdp_rxq_info_reg(काष्ठा xdp_rxq_info *xdp_rxq,
		     काष्ठा net_device *dev, u32 queue_index, अचिन्हित पूर्णांक napi_id);
व्योम xdp_rxq_info_unreg(काष्ठा xdp_rxq_info *xdp_rxq);
व्योम xdp_rxq_info_unused(काष्ठा xdp_rxq_info *xdp_rxq);
bool xdp_rxq_info_is_reg(काष्ठा xdp_rxq_info *xdp_rxq);
पूर्णांक xdp_rxq_info_reg_mem_model(काष्ठा xdp_rxq_info *xdp_rxq,
			       क्रमागत xdp_mem_type type, व्योम *allocator);
व्योम xdp_rxq_info_unreg_mem_model(काष्ठा xdp_rxq_info *xdp_rxq);

/* Drivers not supporting XDP metadata can use this helper, which
 * rejects any room expansion क्रम metadata as a result.
 */
अटल __always_अंतरभूत व्योम
xdp_set_data_meta_invalid(काष्ठा xdp_buff *xdp)
अणु
	xdp->data_meta = xdp->data + 1;
पूर्ण

अटल __always_अंतरभूत bool
xdp_data_meta_unsupported(स्थिर काष्ठा xdp_buff *xdp)
अणु
	वापस unlikely(xdp->data_meta > xdp->data);
पूर्ण

काष्ठा xdp_attachment_info अणु
	काष्ठा bpf_prog *prog;
	u32 flags;
पूर्ण;

काष्ठा netdev_bpf;
व्योम xdp_attachment_setup(काष्ठा xdp_attachment_info *info,
			  काष्ठा netdev_bpf *bpf);

#घोषणा DEV_MAP_BULK_SIZE XDP_BULK_QUEUE_SIZE

#पूर्ण_अगर /* __LINUX_NET_XDP_H__ */
