<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM xdp

#अगर !defined(_TRACE_XDP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_XDP_H

#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/bpf.h>

#घोषणा __XDP_ACT_MAP(FN)	\
	FN(ABORTED)		\
	FN(DROP)		\
	FN(PASS)		\
	FN(TX)			\
	FN(REसूचीECT)

#घोषणा __XDP_ACT_TP_FN(x)	\
	TRACE_DEFINE_ENUM(XDP_##x);
#घोषणा __XDP_ACT_SYM_FN(x)	\
	अणु XDP_##x, #x पूर्ण,
#घोषणा __XDP_ACT_SYM_TAB	\
	__XDP_ACT_MAP(__XDP_ACT_SYM_FN) अणु -1, शून्य पूर्ण
__XDP_ACT_MAP(__XDP_ACT_TP_FN)

TRACE_EVENT(xdp_exception,

	TP_PROTO(स्थिर काष्ठा net_device *dev,
		 स्थिर काष्ठा bpf_prog *xdp, u32 act),

	TP_ARGS(dev, xdp, act),

	TP_STRUCT__entry(
		__field(पूर्णांक, prog_id)
		__field(u32, act)
		__field(पूर्णांक, अगरindex)
	),

	TP_fast_assign(
		__entry->prog_id	= xdp->aux->id;
		__entry->act		= act;
		__entry->अगरindex	= dev->अगरindex;
	),

	TP_prपूर्णांकk("prog_id=%d action=%s ifindex=%d",
		  __entry->prog_id,
		  __prपूर्णांक_symbolic(__entry->act, __XDP_ACT_SYM_TAB),
		  __entry->अगरindex)
);

TRACE_EVENT(xdp_bulk_tx,

	TP_PROTO(स्थिर काष्ठा net_device *dev,
		 पूर्णांक sent, पूर्णांक drops, पूर्णांक err),

	TP_ARGS(dev, sent, drops, err),

	TP_STRUCT__entry(
		__field(पूर्णांक, अगरindex)
		__field(u32, act)
		__field(पूर्णांक, drops)
		__field(पूर्णांक, sent)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->अगरindex	= dev->अगरindex;
		__entry->act		= XDP_TX;
		__entry->drops		= drops;
		__entry->sent		= sent;
		__entry->err		= err;
	),

	TP_prपूर्णांकk("ifindex=%d action=%s sent=%d drops=%d err=%d",
		  __entry->अगरindex,
		  __prपूर्णांक_symbolic(__entry->act, __XDP_ACT_SYM_TAB),
		  __entry->sent, __entry->drops, __entry->err)
);

#अगर_अघोषित __DEVMAP_OBJ_TYPE
#घोषणा __DEVMAP_OBJ_TYPE
काष्ठा _bpf_dtab_netdev अणु
	काष्ठा net_device *dev;
पूर्ण;
#पूर्ण_अगर /* __DEVMAP_OBJ_TYPE */

DECLARE_EVENT_CLASS(xdp_redirect_ढाँचा,

	TP_PROTO(स्थिर काष्ठा net_device *dev,
		 स्थिर काष्ठा bpf_prog *xdp,
		 स्थिर व्योम *tgt, पूर्णांक err,
		 क्रमागत bpf_map_type map_type,
		 u32 map_id, u32 index),

	TP_ARGS(dev, xdp, tgt, err, map_type, map_id, index),

	TP_STRUCT__entry(
		__field(पूर्णांक, prog_id)
		__field(u32, act)
		__field(पूर्णांक, अगरindex)
		__field(पूर्णांक, err)
		__field(पूर्णांक, to_अगरindex)
		__field(u32, map_id)
		__field(पूर्णांक, map_index)
	),

	TP_fast_assign(
		u32 अगरindex = 0, map_index = index;

		अगर (map_type == BPF_MAP_TYPE_DEVMAP || map_type == BPF_MAP_TYPE_DEVMAP_HASH) अणु
			अगरindex = ((काष्ठा _bpf_dtab_netdev *)tgt)->dev->अगरindex;
		पूर्ण अन्यथा अगर (map_type == BPF_MAP_TYPE_UNSPEC && map_id == पूर्णांक_उच्च) अणु
			अगरindex = index;
			map_index = 0;
		पूर्ण

		__entry->prog_id	= xdp->aux->id;
		__entry->act		= XDP_REसूचीECT;
		__entry->अगरindex	= dev->अगरindex;
		__entry->err		= err;
		__entry->to_अगरindex	= अगरindex;
		__entry->map_id		= map_id;
		__entry->map_index	= map_index;
	),

	TP_prपूर्णांकk("prog_id=%d action=%s ifindex=%d to_ifindex=%d err=%d"
		  " map_id=%d map_index=%d",
		  __entry->prog_id,
		  __prपूर्णांक_symbolic(__entry->act, __XDP_ACT_SYM_TAB),
		  __entry->अगरindex, __entry->to_अगरindex,
		  __entry->err, __entry->map_id, __entry->map_index)
);

DEFINE_EVENT(xdp_redirect_ढाँचा, xdp_redirect,
	TP_PROTO(स्थिर काष्ठा net_device *dev,
		 स्थिर काष्ठा bpf_prog *xdp,
		 स्थिर व्योम *tgt, पूर्णांक err,
		 क्रमागत bpf_map_type map_type,
		 u32 map_id, u32 index),
	TP_ARGS(dev, xdp, tgt, err, map_type, map_id, index)
);

DEFINE_EVENT(xdp_redirect_ढाँचा, xdp_redirect_err,
	TP_PROTO(स्थिर काष्ठा net_device *dev,
		 स्थिर काष्ठा bpf_prog *xdp,
		 स्थिर व्योम *tgt, पूर्णांक err,
		 क्रमागत bpf_map_type map_type,
		 u32 map_id, u32 index),
	TP_ARGS(dev, xdp, tgt, err, map_type, map_id, index)
);

#घोषणा _trace_xdp_redirect(dev, xdp, to)						\
	 trace_xdp_redirect(dev, xdp, शून्य, 0, BPF_MAP_TYPE_UNSPEC, पूर्णांक_उच्च, to)

#घोषणा _trace_xdp_redirect_err(dev, xdp, to, err)					\
	 trace_xdp_redirect_err(dev, xdp, शून्य, err, BPF_MAP_TYPE_UNSPEC, पूर्णांक_उच्च, to)

#घोषणा _trace_xdp_redirect_map(dev, xdp, to, map_type, map_id, index) \
	 trace_xdp_redirect(dev, xdp, to, 0, map_type, map_id, index)

#घोषणा _trace_xdp_redirect_map_err(dev, xdp, to, map_type, map_id, index, err) \
	 trace_xdp_redirect_err(dev, xdp, to, err, map_type, map_id, index)

/* not used anymore, but kept around so as not to अवरोध old programs */
DEFINE_EVENT(xdp_redirect_ढाँचा, xdp_redirect_map,
	TP_PROTO(स्थिर काष्ठा net_device *dev,
		 स्थिर काष्ठा bpf_prog *xdp,
		 स्थिर व्योम *tgt, पूर्णांक err,
		 क्रमागत bpf_map_type map_type,
		 u32 map_id, u32 index),
	TP_ARGS(dev, xdp, tgt, err, map_type, map_id, index)
);

DEFINE_EVENT(xdp_redirect_ढाँचा, xdp_redirect_map_err,
	TP_PROTO(स्थिर काष्ठा net_device *dev,
		 स्थिर काष्ठा bpf_prog *xdp,
		 स्थिर व्योम *tgt, पूर्णांक err,
		 क्रमागत bpf_map_type map_type,
		 u32 map_id, u32 index),
	TP_ARGS(dev, xdp, tgt, err, map_type, map_id, index)
);

TRACE_EVENT(xdp_cpumap_kthपढ़ो,

	TP_PROTO(पूर्णांक map_id, अचिन्हित पूर्णांक processed,  अचिन्हित पूर्णांक drops,
		 पूर्णांक sched, काष्ठा xdp_cpumap_stats *xdp_stats),

	TP_ARGS(map_id, processed, drops, sched, xdp_stats),

	TP_STRUCT__entry(
		__field(पूर्णांक, map_id)
		__field(u32, act)
		__field(पूर्णांक, cpu)
		__field(अचिन्हित पूर्णांक, drops)
		__field(अचिन्हित पूर्णांक, processed)
		__field(पूर्णांक, sched)
		__field(अचिन्हित पूर्णांक, xdp_pass)
		__field(अचिन्हित पूर्णांक, xdp_drop)
		__field(अचिन्हित पूर्णांक, xdp_redirect)
	),

	TP_fast_assign(
		__entry->map_id		= map_id;
		__entry->act		= XDP_REसूचीECT;
		__entry->cpu		= smp_processor_id();
		__entry->drops		= drops;
		__entry->processed	= processed;
		__entry->sched	= sched;
		__entry->xdp_pass	= xdp_stats->pass;
		__entry->xdp_drop	= xdp_stats->drop;
		__entry->xdp_redirect	= xdp_stats->redirect;
	),

	TP_prपूर्णांकk("kthread"
		  " cpu=%d map_id=%d action=%s"
		  " processed=%u drops=%u"
		  " sched=%d"
		  " xdp_pass=%u xdp_drop=%u xdp_redirect=%u",
		  __entry->cpu, __entry->map_id,
		  __prपूर्णांक_symbolic(__entry->act, __XDP_ACT_SYM_TAB),
		  __entry->processed, __entry->drops,
		  __entry->sched,
		  __entry->xdp_pass, __entry->xdp_drop, __entry->xdp_redirect)
);

TRACE_EVENT(xdp_cpumap_enqueue,

	TP_PROTO(पूर्णांक map_id, अचिन्हित पूर्णांक processed,  अचिन्हित पूर्णांक drops,
		 पूर्णांक to_cpu),

	TP_ARGS(map_id, processed, drops, to_cpu),

	TP_STRUCT__entry(
		__field(पूर्णांक, map_id)
		__field(u32, act)
		__field(पूर्णांक, cpu)
		__field(अचिन्हित पूर्णांक, drops)
		__field(अचिन्हित पूर्णांक, processed)
		__field(पूर्णांक, to_cpu)
	),

	TP_fast_assign(
		__entry->map_id		= map_id;
		__entry->act		= XDP_REसूचीECT;
		__entry->cpu		= smp_processor_id();
		__entry->drops		= drops;
		__entry->processed	= processed;
		__entry->to_cpu		= to_cpu;
	),

	TP_prपूर्णांकk("enqueue"
		  " cpu=%d map_id=%d action=%s"
		  " processed=%u drops=%u"
		  " to_cpu=%d",
		  __entry->cpu, __entry->map_id,
		  __prपूर्णांक_symbolic(__entry->act, __XDP_ACT_SYM_TAB),
		  __entry->processed, __entry->drops,
		  __entry->to_cpu)
);

TRACE_EVENT(xdp_devmap_xmit,

	TP_PROTO(स्थिर काष्ठा net_device *from_dev,
		 स्थिर काष्ठा net_device *to_dev,
		 पूर्णांक sent, पूर्णांक drops, पूर्णांक err),

	TP_ARGS(from_dev, to_dev, sent, drops, err),

	TP_STRUCT__entry(
		__field(पूर्णांक, from_अगरindex)
		__field(u32, act)
		__field(पूर्णांक, to_अगरindex)
		__field(पूर्णांक, drops)
		__field(पूर्णांक, sent)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->from_अगरindex	= from_dev->अगरindex;
		__entry->act		= XDP_REसूचीECT;
		__entry->to_अगरindex	= to_dev->अगरindex;
		__entry->drops		= drops;
		__entry->sent		= sent;
		__entry->err		= err;
	),

	TP_prपूर्णांकk("ndo_xdp_xmit"
		  " from_ifindex=%d to_ifindex=%d action=%s"
		  " sent=%d drops=%d"
		  " err=%d",
		  __entry->from_अगरindex, __entry->to_अगरindex,
		  __prपूर्णांक_symbolic(__entry->act, __XDP_ACT_SYM_TAB),
		  __entry->sent, __entry->drops,
		  __entry->err)
);

/* Expect users alपढ़ोy include <net/xdp.h>, but not xdp_priv.h */
#समावेश <net/xdp_priv.h>

#घोषणा __MEM_TYPE_MAP(FN)	\
	FN(PAGE_SHARED)		\
	FN(PAGE_ORDER0)		\
	FN(PAGE_POOL)		\
	FN(XSK_BUFF_POOL)

#घोषणा __MEM_TYPE_TP_FN(x)	\
	TRACE_DEFINE_ENUM(MEM_TYPE_##x);
#घोषणा __MEM_TYPE_SYM_FN(x)	\
	अणु MEM_TYPE_##x, #x पूर्ण,
#घोषणा __MEM_TYPE_SYM_TAB	\
	__MEM_TYPE_MAP(__MEM_TYPE_SYM_FN) अणु -1, 0 पूर्ण
__MEM_TYPE_MAP(__MEM_TYPE_TP_FN)

TRACE_EVENT(mem_disconnect,

	TP_PROTO(स्थिर काष्ठा xdp_mem_allocator *xa),

	TP_ARGS(xa),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा xdp_mem_allocator *,	xa)
		__field(u32,		mem_id)
		__field(u32,		mem_type)
		__field(स्थिर व्योम *,	allocator)
	),

	TP_fast_assign(
		__entry->xa		= xa;
		__entry->mem_id		= xa->mem.id;
		__entry->mem_type	= xa->mem.type;
		__entry->allocator	= xa->allocator;
	),

	TP_prपूर्णांकk("mem_id=%d mem_type=%s allocator=%p",
		  __entry->mem_id,
		  __prपूर्णांक_symbolic(__entry->mem_type, __MEM_TYPE_SYM_TAB),
		  __entry->allocator
	)
);

TRACE_EVENT(mem_connect,

	TP_PROTO(स्थिर काष्ठा xdp_mem_allocator *xa,
		 स्थिर काष्ठा xdp_rxq_info *rxq),

	TP_ARGS(xa, rxq),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा xdp_mem_allocator *,	xa)
		__field(u32,		mem_id)
		__field(u32,		mem_type)
		__field(स्थिर व्योम *,	allocator)
		__field(स्थिर काष्ठा xdp_rxq_info *,		rxq)
		__field(पूर्णांक,		अगरindex)
	),

	TP_fast_assign(
		__entry->xa		= xa;
		__entry->mem_id		= xa->mem.id;
		__entry->mem_type	= xa->mem.type;
		__entry->allocator	= xa->allocator;
		__entry->rxq		= rxq;
		__entry->अगरindex	= rxq->dev->अगरindex;
	),

	TP_prपूर्णांकk("mem_id=%d mem_type=%s allocator=%p"
		  " ifindex=%d",
		  __entry->mem_id,
		  __prपूर्णांक_symbolic(__entry->mem_type, __MEM_TYPE_SYM_TAB),
		  __entry->allocator,
		  __entry->अगरindex
	)
);

TRACE_EVENT(mem_वापस_failed,

	TP_PROTO(स्थिर काष्ठा xdp_mem_info *mem,
		 स्थिर काष्ठा page *page),

	TP_ARGS(mem, page),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा page *,	page)
		__field(u32,		mem_id)
		__field(u32,		mem_type)
	),

	TP_fast_assign(
		__entry->page		= page;
		__entry->mem_id		= mem->id;
		__entry->mem_type	= mem->type;
	),

	TP_prपूर्णांकk("mem_id=%d mem_type=%s page=%p",
		  __entry->mem_id,
		  __prपूर्णांक_symbolic(__entry->mem_type, __MEM_TYPE_SYM_TAB),
		  __entry->page
	)
);

#पूर्ण_अगर /* _TRACE_XDP_H */

#समावेश <trace/define_trace.h>
