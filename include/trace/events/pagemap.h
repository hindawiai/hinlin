<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM pagemap

#अगर !defined(_TRACE_PAGEMAP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PAGEMAP_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/mm.h>

#घोषणा	PAGEMAP_MAPPED		0x0001u
#घोषणा PAGEMAP_ANONYMOUS	0x0002u
#घोषणा PAGEMAP_खाता		0x0004u
#घोषणा PAGEMAP_SWAPCACHE	0x0008u
#घोषणा PAGEMAP_SWAPBACKED	0x0010u
#घोषणा PAGEMAP_MAPPEDDISK	0x0020u
#घोषणा PAGEMAP_BUFFERS		0x0040u

#घोषणा trace_pagemap_flags(page) ( \
	(PageAnon(page)		? PAGEMAP_ANONYMOUS  : PAGEMAP_खाता) | \
	(page_mapped(page)	? PAGEMAP_MAPPED     : 0) | \
	(PageSwapCache(page)	? PAGEMAP_SWAPCACHE  : 0) | \
	(PageSwapBacked(page)	? PAGEMAP_SWAPBACKED : 0) | \
	(PageMappedToDisk(page)	? PAGEMAP_MAPPEDDISK : 0) | \
	(page_has_निजी(page) ? PAGEMAP_BUFFERS    : 0) \
	)

TRACE_EVENT(mm_lru_insertion,

	TP_PROTO(काष्ठा page *page),

	TP_ARGS(page),

	TP_STRUCT__entry(
		__field(काष्ठा page *,	page	)
		__field(अचिन्हित दीर्घ,	pfn	)
		__field(क्रमागत lru_list,	lru	)
		__field(अचिन्हित दीर्घ,	flags	)
	),

	TP_fast_assign(
		__entry->page	= page;
		__entry->pfn	= page_to_pfn(page);
		__entry->lru	= page_lru(page);
		__entry->flags	= trace_pagemap_flags(page);
	),

	/* Flag क्रमmat is based on page-types.c क्रमmatting क्रम pagemap */
	TP_prपूर्णांकk("page=%p pfn=%lu lru=%d flags=%s%s%s%s%s%s",
			__entry->page,
			__entry->pfn,
			__entry->lru,
			__entry->flags & PAGEMAP_MAPPED		? "M" : " ",
			__entry->flags & PAGEMAP_ANONYMOUS	? "a" : "f",
			__entry->flags & PAGEMAP_SWAPCACHE	? "s" : " ",
			__entry->flags & PAGEMAP_SWAPBACKED	? "b" : " ",
			__entry->flags & PAGEMAP_MAPPEDDISK	? "d" : " ",
			__entry->flags & PAGEMAP_BUFFERS	? "B" : " ")
);

TRACE_EVENT(mm_lru_activate,

	TP_PROTO(काष्ठा page *page),

	TP_ARGS(page),

	TP_STRUCT__entry(
		__field(काष्ठा page *,	page	)
		__field(अचिन्हित दीर्घ,	pfn	)
	),

	TP_fast_assign(
		__entry->page	= page;
		__entry->pfn	= page_to_pfn(page);
	),

	/* Flag क्रमmat is based on page-types.c क्रमmatting क्रम pagemap */
	TP_prपूर्णांकk("page=%p pfn=%lu", __entry->page, __entry->pfn)

);

#पूर्ण_अगर /* _TRACE_PAGEMAP_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
