<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kmem

#अगर !defined(_TRACE_KMEM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KMEM_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <trace/events/mmflags.h>

DECLARE_EVENT_CLASS(kmem_alloc,

	TP_PROTO(अचिन्हित दीर्घ call_site,
		 स्थिर व्योम *ptr,
		 माप_प्रकार bytes_req,
		 माप_प्रकार bytes_alloc,
		 gfp_t gfp_flags),

	TP_ARGS(call_site, ptr, bytes_req, bytes_alloc, gfp_flags),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	call_site	)
		__field(	स्थिर व्योम *,	ptr		)
		__field(	माप_प्रकार,		bytes_req	)
		__field(	माप_प्रकार,		bytes_alloc	)
		__field(	gfp_t,		gfp_flags	)
	),

	TP_fast_assign(
		__entry->call_site	= call_site;
		__entry->ptr		= ptr;
		__entry->bytes_req	= bytes_req;
		__entry->bytes_alloc	= bytes_alloc;
		__entry->gfp_flags	= gfp_flags;
	),

	TP_prपूर्णांकk("call_site=%pS ptr=%p bytes_req=%zu bytes_alloc=%zu gfp_flags=%s",
		(व्योम *)__entry->call_site,
		__entry->ptr,
		__entry->bytes_req,
		__entry->bytes_alloc,
		show_gfp_flags(__entry->gfp_flags))
);

DEFINE_EVENT(kmem_alloc, kदो_स्मृति,

	TP_PROTO(अचिन्हित दीर्घ call_site, स्थिर व्योम *ptr,
		 माप_प्रकार bytes_req, माप_प्रकार bytes_alloc, gfp_t gfp_flags),

	TP_ARGS(call_site, ptr, bytes_req, bytes_alloc, gfp_flags)
);

DEFINE_EVENT(kmem_alloc, kmem_cache_alloc,

	TP_PROTO(अचिन्हित दीर्घ call_site, स्थिर व्योम *ptr,
		 माप_प्रकार bytes_req, माप_प्रकार bytes_alloc, gfp_t gfp_flags),

	TP_ARGS(call_site, ptr, bytes_req, bytes_alloc, gfp_flags)
);

DECLARE_EVENT_CLASS(kmem_alloc_node,

	TP_PROTO(अचिन्हित दीर्घ call_site,
		 स्थिर व्योम *ptr,
		 माप_प्रकार bytes_req,
		 माप_प्रकार bytes_alloc,
		 gfp_t gfp_flags,
		 पूर्णांक node),

	TP_ARGS(call_site, ptr, bytes_req, bytes_alloc, gfp_flags, node),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	call_site	)
		__field(	स्थिर व्योम *,	ptr		)
		__field(	माप_प्रकार,		bytes_req	)
		__field(	माप_प्रकार,		bytes_alloc	)
		__field(	gfp_t,		gfp_flags	)
		__field(	पूर्णांक,		node		)
	),

	TP_fast_assign(
		__entry->call_site	= call_site;
		__entry->ptr		= ptr;
		__entry->bytes_req	= bytes_req;
		__entry->bytes_alloc	= bytes_alloc;
		__entry->gfp_flags	= gfp_flags;
		__entry->node		= node;
	),

	TP_prपूर्णांकk("call_site=%pS ptr=%p bytes_req=%zu bytes_alloc=%zu gfp_flags=%s node=%d",
		(व्योम *)__entry->call_site,
		__entry->ptr,
		__entry->bytes_req,
		__entry->bytes_alloc,
		show_gfp_flags(__entry->gfp_flags),
		__entry->node)
);

DEFINE_EVENT(kmem_alloc_node, kदो_स्मृति_node,

	TP_PROTO(अचिन्हित दीर्घ call_site, स्थिर व्योम *ptr,
		 माप_प्रकार bytes_req, माप_प्रकार bytes_alloc,
		 gfp_t gfp_flags, पूर्णांक node),

	TP_ARGS(call_site, ptr, bytes_req, bytes_alloc, gfp_flags, node)
);

DEFINE_EVENT(kmem_alloc_node, kmem_cache_alloc_node,

	TP_PROTO(अचिन्हित दीर्घ call_site, स्थिर व्योम *ptr,
		 माप_प्रकार bytes_req, माप_प्रकार bytes_alloc,
		 gfp_t gfp_flags, पूर्णांक node),

	TP_ARGS(call_site, ptr, bytes_req, bytes_alloc, gfp_flags, node)
);

TRACE_EVENT(kमुक्त,

	TP_PROTO(अचिन्हित दीर्घ call_site, स्थिर व्योम *ptr),

	TP_ARGS(call_site, ptr),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	call_site	)
		__field(	स्थिर व्योम *,	ptr		)
	),

	TP_fast_assign(
		__entry->call_site	= call_site;
		__entry->ptr		= ptr;
	),

	TP_prपूर्णांकk("call_site=%pS ptr=%p",
		  (व्योम *)__entry->call_site, __entry->ptr)
);

TRACE_EVENT(kmem_cache_मुक्त,

	TP_PROTO(अचिन्हित दीर्घ call_site, स्थिर व्योम *ptr, स्थिर अक्षर *name),

	TP_ARGS(call_site, ptr, name),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	call_site	)
		__field(	स्थिर व्योम *,	ptr		)
		__string(	name,	name	)
	),

	TP_fast_assign(
		__entry->call_site	= call_site;
		__entry->ptr		= ptr;
		__assign_str(name, name);
	),

	TP_prपूर्णांकk("call_site=%pS ptr=%p name=%s",
		  (व्योम *)__entry->call_site, __entry->ptr, __get_str(name))
);

TRACE_EVENT(mm_page_मुक्त,

	TP_PROTO(काष्ठा page *page, अचिन्हित पूर्णांक order),

	TP_ARGS(page, order),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	pfn		)
		__field(	अचिन्हित पूर्णांक,	order		)
	),

	TP_fast_assign(
		__entry->pfn		= page_to_pfn(page);
		__entry->order		= order;
	),

	TP_prपूर्णांकk("page=%p pfn=%lu order=%d",
			pfn_to_page(__entry->pfn),
			__entry->pfn,
			__entry->order)
);

TRACE_EVENT(mm_page_मुक्त_batched,

	TP_PROTO(काष्ठा page *page),

	TP_ARGS(page),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	pfn		)
	),

	TP_fast_assign(
		__entry->pfn		= page_to_pfn(page);
	),

	TP_prपूर्णांकk("page=%p pfn=%lu order=0",
			pfn_to_page(__entry->pfn),
			__entry->pfn)
);

TRACE_EVENT(mm_page_alloc,

	TP_PROTO(काष्ठा page *page, अचिन्हित पूर्णांक order,
			gfp_t gfp_flags, पूर्णांक migratetype),

	TP_ARGS(page, order, gfp_flags, migratetype),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	pfn		)
		__field(	अचिन्हित पूर्णांक,	order		)
		__field(	gfp_t,		gfp_flags	)
		__field(	पूर्णांक,		migratetype	)
	),

	TP_fast_assign(
		__entry->pfn		= page ? page_to_pfn(page) : -1UL;
		__entry->order		= order;
		__entry->gfp_flags	= gfp_flags;
		__entry->migratetype	= migratetype;
	),

	TP_prपूर्णांकk("page=%p pfn=%lu order=%d migratetype=%d gfp_flags=%s",
		__entry->pfn != -1UL ? pfn_to_page(__entry->pfn) : शून्य,
		__entry->pfn != -1UL ? __entry->pfn : 0,
		__entry->order,
		__entry->migratetype,
		show_gfp_flags(__entry->gfp_flags))
);

DECLARE_EVENT_CLASS(mm_page,

	TP_PROTO(काष्ठा page *page, अचिन्हित पूर्णांक order, पूर्णांक migratetype),

	TP_ARGS(page, order, migratetype),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	pfn		)
		__field(	अचिन्हित पूर्णांक,	order		)
		__field(	पूर्णांक,		migratetype	)
	),

	TP_fast_assign(
		__entry->pfn		= page ? page_to_pfn(page) : -1UL;
		__entry->order		= order;
		__entry->migratetype	= migratetype;
	),

	TP_prपूर्णांकk("page=%p pfn=%lu order=%u migratetype=%d percpu_refill=%d",
		__entry->pfn != -1UL ? pfn_to_page(__entry->pfn) : शून्य,
		__entry->pfn != -1UL ? __entry->pfn : 0,
		__entry->order,
		__entry->migratetype,
		__entry->order == 0)
);

DEFINE_EVENT(mm_page, mm_page_alloc_zone_locked,

	TP_PROTO(काष्ठा page *page, अचिन्हित पूर्णांक order, पूर्णांक migratetype),

	TP_ARGS(page, order, migratetype)
);

TRACE_EVENT(mm_page_pcpu_drain,

	TP_PROTO(काष्ठा page *page, अचिन्हित पूर्णांक order, पूर्णांक migratetype),

	TP_ARGS(page, order, migratetype),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	pfn		)
		__field(	अचिन्हित पूर्णांक,	order		)
		__field(	पूर्णांक,		migratetype	)
	),

	TP_fast_assign(
		__entry->pfn		= page ? page_to_pfn(page) : -1UL;
		__entry->order		= order;
		__entry->migratetype	= migratetype;
	),

	TP_prपूर्णांकk("page=%p pfn=%lu order=%d migratetype=%d",
		pfn_to_page(__entry->pfn), __entry->pfn,
		__entry->order, __entry->migratetype)
);

TRACE_EVENT(mm_page_alloc_extfrag,

	TP_PROTO(काष्ठा page *page,
		पूर्णांक alloc_order, पूर्णांक fallback_order,
		पूर्णांक alloc_migratetype, पूर्णांक fallback_migratetype),

	TP_ARGS(page,
		alloc_order, fallback_order,
		alloc_migratetype, fallback_migratetype),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	pfn			)
		__field(	पूर्णांक,		alloc_order		)
		__field(	पूर्णांक,		fallback_order		)
		__field(	पूर्णांक,		alloc_migratetype	)
		__field(	पूर्णांक,		fallback_migratetype	)
		__field(	पूर्णांक,		change_ownership	)
	),

	TP_fast_assign(
		__entry->pfn			= page_to_pfn(page);
		__entry->alloc_order		= alloc_order;
		__entry->fallback_order		= fallback_order;
		__entry->alloc_migratetype	= alloc_migratetype;
		__entry->fallback_migratetype	= fallback_migratetype;
		__entry->change_ownership	= (alloc_migratetype ==
					get_pageblock_migratetype(page));
	),

	TP_prपूर्णांकk("page=%p pfn=%lu alloc_order=%d fallback_order=%d pageblock_order=%d alloc_migratetype=%d fallback_migratetype=%d fragmenting=%d change_ownership=%d",
		pfn_to_page(__entry->pfn),
		__entry->pfn,
		__entry->alloc_order,
		__entry->fallback_order,
		pageblock_order,
		__entry->alloc_migratetype,
		__entry->fallback_migratetype,
		__entry->fallback_order < pageblock_order,
		__entry->change_ownership)
);

/*
 * Required क्रम uniquely and securely identअगरying mm in rss_stat tracepoपूर्णांक.
 */
#अगर_अघोषित __PTR_TO_HASHVAL
अटल अचिन्हित पूर्णांक __maybe_unused mm_ptr_to_hash(स्थिर व्योम *ptr)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ hashval;

	ret = ptr_to_hashval(ptr, &hashval);
	अगर (ret)
		वापस 0;

	/* The hashed value is only 32-bit */
	वापस (अचिन्हित पूर्णांक)hashval;
पूर्ण
#घोषणा __PTR_TO_HASHVAL
#पूर्ण_अगर

#घोषणा TRACE_MM_PAGES		\
	EM(MM_खाताPAGES)	\
	EM(MM_ANONPAGES)	\
	EM(MM_SWAPENTS)		\
	EMe(MM_SHMEMPAGES)

#अघोषित EM
#अघोषित EMe

#घोषणा EM(a)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a)	TRACE_DEFINE_ENUM(a);

TRACE_MM_PAGES

#अघोषित EM
#अघोषित EMe

#घोषणा EM(a)	अणु a, #a पूर्ण,
#घोषणा EMe(a)	अणु a, #a पूर्ण

TRACE_EVENT(rss_stat,

	TP_PROTO(काष्ठा mm_काष्ठा *mm,
		पूर्णांक member,
		दीर्घ count),

	TP_ARGS(mm, member, count),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, mm_id)
		__field(अचिन्हित पूर्णांक, curr)
		__field(पूर्णांक, member)
		__field(दीर्घ, size)
	),

	TP_fast_assign(
		__entry->mm_id = mm_ptr_to_hash(mm);
		__entry->curr = !!(current->mm == mm);
		__entry->member = member;
		__entry->size = (count << PAGE_SHIFT);
	),

	TP_prपूर्णांकk("mm_id=%u curr=%d type=%s size=%ldB",
		__entry->mm_id,
		__entry->curr,
		__prपूर्णांक_symbolic(__entry->member, TRACE_MM_PAGES),
		__entry->size)
	);
#पूर्ण_अगर /* _TRACE_KMEM_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
