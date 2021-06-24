<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM page_pool

#अगर !defined(_TRACE_PAGE_POOL_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा      _TRACE_PAGE_POOL_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <trace/events/mmflags.h>
#समावेश <net/page_pool.h>

TRACE_EVENT(page_pool_release,

	TP_PROTO(स्थिर काष्ठा page_pool *pool,
		 s32 inflight, u32 hold, u32 release),

	TP_ARGS(pool, inflight, hold, release),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा page_pool *, pool)
		__field(s32,	inflight)
		__field(u32,	hold)
		__field(u32,	release)
		__field(u64,	cnt)
	),

	TP_fast_assign(
		__entry->pool		= pool;
		__entry->inflight	= inflight;
		__entry->hold		= hold;
		__entry->release	= release;
		__entry->cnt		= pool->destroy_cnt;
	),

	TP_prपूर्णांकk("page_pool=%p inflight=%d hold=%u release=%u cnt=%llu",
		__entry->pool, __entry->inflight, __entry->hold,
		__entry->release, __entry->cnt)
);

TRACE_EVENT(page_pool_state_release,

	TP_PROTO(स्थिर काष्ठा page_pool *pool,
		 स्थिर काष्ठा page *page, u32 release),

	TP_ARGS(pool, page, release),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा page_pool *,	pool)
		__field(स्थिर काष्ठा page *,		page)
		__field(u32,				release)
		__field(अचिन्हित दीर्घ,			pfn)
	),

	TP_fast_assign(
		__entry->pool		= pool;
		__entry->page		= page;
		__entry->release	= release;
		__entry->pfn		= page_to_pfn(page);
	),

	TP_prपूर्णांकk("page_pool=%p page=%p pfn=%lu release=%u",
		  __entry->pool, __entry->page, __entry->pfn, __entry->release)
);

TRACE_EVENT(page_pool_state_hold,

	TP_PROTO(स्थिर काष्ठा page_pool *pool,
		 स्थिर काष्ठा page *page, u32 hold),

	TP_ARGS(pool, page, hold),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा page_pool *,	pool)
		__field(स्थिर काष्ठा page *,		page)
		__field(u32,				hold)
		__field(अचिन्हित दीर्घ,			pfn)
	),

	TP_fast_assign(
		__entry->pool	= pool;
		__entry->page	= page;
		__entry->hold	= hold;
		__entry->pfn	= page_to_pfn(page);
	),

	TP_prपूर्णांकk("page_pool=%p page=%p pfn=%lu hold=%u",
		  __entry->pool, __entry->page, __entry->pfn, __entry->hold)
);

TRACE_EVENT(page_pool_update_nid,

	TP_PROTO(स्थिर काष्ठा page_pool *pool, पूर्णांक new_nid),

	TP_ARGS(pool, new_nid),

	TP_STRUCT__entry(
		__field(स्थिर काष्ठा page_pool *, pool)
		__field(पूर्णांक,			  pool_nid)
		__field(पूर्णांक,			  new_nid)
	),

	TP_fast_assign(
		__entry->pool		= pool;
		__entry->pool_nid	= pool->p.nid;
		__entry->new_nid	= new_nid;
	),

	TP_prपूर्णांकk("page_pool=%p pool_nid=%d new_nid=%d",
		  __entry->pool, __entry->pool_nid, __entry->new_nid)
);

#पूर्ण_अगर /* _TRACE_PAGE_POOL_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
