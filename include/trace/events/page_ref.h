<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM page_ref

#अगर !defined(_TRACE_PAGE_REF_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PAGE_REF_H

#समावेश <linux/types.h>
#समावेश <linux/page_ref.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <trace/events/mmflags.h>

DECLARE_EVENT_CLASS(page_ref_mod_ढाँचा,

	TP_PROTO(काष्ठा page *page, पूर्णांक v),

	TP_ARGS(page, v),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, pfn)
		__field(अचिन्हित दीर्घ, flags)
		__field(पूर्णांक, count)
		__field(पूर्णांक, mapcount)
		__field(व्योम *, mapping)
		__field(पूर्णांक, mt)
		__field(पूर्णांक, val)
	),

	TP_fast_assign(
		__entry->pfn = page_to_pfn(page);
		__entry->flags = page->flags;
		__entry->count = page_ref_count(page);
		__entry->mapcount = page_mapcount(page);
		__entry->mapping = page->mapping;
		__entry->mt = get_pageblock_migratetype(page);
		__entry->val = v;
	),

	TP_prपूर्णांकk("pfn=0x%lx flags=%s count=%d mapcount=%d mapping=%p mt=%d val=%d",
		__entry->pfn,
		show_page_flags(__entry->flags & ((1UL << NR_PAGEFLAGS) - 1)),
		__entry->count,
		__entry->mapcount, __entry->mapping, __entry->mt,
		__entry->val)
);

DEFINE_EVENT(page_ref_mod_ढाँचा, page_ref_set,

	TP_PROTO(काष्ठा page *page, पूर्णांक v),

	TP_ARGS(page, v)
);

DEFINE_EVENT(page_ref_mod_ढाँचा, page_ref_mod,

	TP_PROTO(काष्ठा page *page, पूर्णांक v),

	TP_ARGS(page, v)
);

DECLARE_EVENT_CLASS(page_ref_mod_and_test_ढाँचा,

	TP_PROTO(काष्ठा page *page, पूर्णांक v, पूर्णांक ret),

	TP_ARGS(page, v, ret),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, pfn)
		__field(अचिन्हित दीर्घ, flags)
		__field(पूर्णांक, count)
		__field(पूर्णांक, mapcount)
		__field(व्योम *, mapping)
		__field(पूर्णांक, mt)
		__field(पूर्णांक, val)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->pfn = page_to_pfn(page);
		__entry->flags = page->flags;
		__entry->count = page_ref_count(page);
		__entry->mapcount = page_mapcount(page);
		__entry->mapping = page->mapping;
		__entry->mt = get_pageblock_migratetype(page);
		__entry->val = v;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("pfn=0x%lx flags=%s count=%d mapcount=%d mapping=%p mt=%d val=%d ret=%d",
		__entry->pfn,
		show_page_flags(__entry->flags & ((1UL << NR_PAGEFLAGS) - 1)),
		__entry->count,
		__entry->mapcount, __entry->mapping, __entry->mt,
		__entry->val, __entry->ret)
);

DEFINE_EVENT(page_ref_mod_and_test_ढाँचा, page_ref_mod_and_test,

	TP_PROTO(काष्ठा page *page, पूर्णांक v, पूर्णांक ret),

	TP_ARGS(page, v, ret)
);

DEFINE_EVENT(page_ref_mod_and_test_ढाँचा, page_ref_mod_and_वापस,

	TP_PROTO(काष्ठा page *page, पूर्णांक v, पूर्णांक ret),

	TP_ARGS(page, v, ret)
);

DEFINE_EVENT(page_ref_mod_and_test_ढाँचा, page_ref_mod_unless,

	TP_PROTO(काष्ठा page *page, पूर्णांक v, पूर्णांक ret),

	TP_ARGS(page, v, ret)
);

DEFINE_EVENT(page_ref_mod_and_test_ढाँचा, page_ref_मुक्तze,

	TP_PROTO(काष्ठा page *page, पूर्णांक v, पूर्णांक ret),

	TP_ARGS(page, v, ret)
);

DEFINE_EVENT(page_ref_mod_ढाँचा, page_ref_unमुक्तze,

	TP_PROTO(काष्ठा page *page, पूर्णांक v),

	TP_ARGS(page, v)
);

#पूर्ण_अगर /* _TRACE_PAGE_COUNT_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
