<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM huge_memory

#अगर !defined(__HUGE_MEMORY_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HUGE_MEMORY_H

#समावेश  <linux/tracepoपूर्णांक.h>

#घोषणा SCAN_STATUS							\
	EM( SCAN_FAIL,			"failed")			\
	EM( SCAN_SUCCEED,		"succeeded")			\
	EM( SCAN_PMD_शून्य,		"pmd_null")			\
	EM( SCAN_EXCEED_NONE_PTE,	"exceed_none_pte")		\
	EM( SCAN_EXCEED_SWAP_PTE,	"exceed_swap_pte")		\
	EM( SCAN_EXCEED_SHARED_PTE,	"exceed_shared_pte")		\
	EM( SCAN_PTE_NON_PRESENT,	"pte_non_present")		\
	EM( SCAN_PTE_UFFD_WP,		"pte_uffd_wp")			\
	EM( SCAN_PAGE_RO,		"no_writable_page")		\
	EM( SCAN_LACK_REFERENCED_PAGE,	"lack_referenced_page")		\
	EM( SCAN_PAGE_शून्य,		"page_null")			\
	EM( SCAN_SCAN_ABORT,		"scan_aborted")			\
	EM( SCAN_PAGE_COUNT,		"not_suitable_page_count")	\
	EM( SCAN_PAGE_LRU,		"page_not_in_lru")		\
	EM( SCAN_PAGE_LOCK,		"page_locked")			\
	EM( SCAN_PAGE_ANON,		"page_not_anon")		\
	EM( SCAN_PAGE_COMPOUND,		"page_compound")		\
	EM( SCAN_ANY_PROCESS,		"no_process_for_page")		\
	EM( SCAN_VMA_शून्य,		"vma_null")			\
	EM( SCAN_VMA_CHECK,		"vma_check_failed")		\
	EM( SCAN_ADDRESS_RANGE,		"not_suitable_address_range")	\
	EM( SCAN_SWAP_CACHE_PAGE,	"page_swap_cache")		\
	EM( SCAN_DEL_PAGE_LRU,		"could_not_delete_page_from_lru")\
	EM( SCAN_ALLOC_HUGE_PAGE_FAIL,	"alloc_huge_page_failed")	\
	EM( SCAN_CGROUP_CHARGE_FAIL,	"ccgroup_charge_failed")	\
	EM( SCAN_TRUNCATED,		"truncated")			\
	EMe(SCAN_PAGE_HAS_PRIVATE,	"page_has_private")		\

#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a, b)	TRACE_DEFINE_ENUM(a);

SCAN_STATUS

#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	अणुa, bपूर्ण,
#घोषणा EMe(a, b)	अणुa, bपूर्ण

TRACE_EVENT(mm_khugepaged_scan_pmd,

	TP_PROTO(काष्ठा mm_काष्ठा *mm, काष्ठा page *page, bool writable,
		 पूर्णांक referenced, पूर्णांक none_or_zero, पूर्णांक status, पूर्णांक unmapped),

	TP_ARGS(mm, page, writable, referenced, none_or_zero, status, unmapped),

	TP_STRUCT__entry(
		__field(काष्ठा mm_काष्ठा *, mm)
		__field(अचिन्हित दीर्घ, pfn)
		__field(bool, writable)
		__field(पूर्णांक, referenced)
		__field(पूर्णांक, none_or_zero)
		__field(पूर्णांक, status)
		__field(पूर्णांक, unmapped)
	),

	TP_fast_assign(
		__entry->mm = mm;
		__entry->pfn = page ? page_to_pfn(page) : -1;
		__entry->writable = writable;
		__entry->referenced = referenced;
		__entry->none_or_zero = none_or_zero;
		__entry->status = status;
		__entry->unmapped = unmapped;
	),

	TP_prपूर्णांकk("mm=%p, scan_pfn=0x%lx, writable=%d, referenced=%d, none_or_zero=%d, status=%s, unmapped=%d",
		__entry->mm,
		__entry->pfn,
		__entry->writable,
		__entry->referenced,
		__entry->none_or_zero,
		__prपूर्णांक_symbolic(__entry->status, SCAN_STATUS),
		__entry->unmapped)
);

TRACE_EVENT(mm_collapse_huge_page,

	TP_PROTO(काष्ठा mm_काष्ठा *mm, पूर्णांक isolated, पूर्णांक status),

	TP_ARGS(mm, isolated, status),

	TP_STRUCT__entry(
		__field(काष्ठा mm_काष्ठा *, mm)
		__field(पूर्णांक, isolated)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		__entry->mm = mm;
		__entry->isolated = isolated;
		__entry->status = status;
	),

	TP_prपूर्णांकk("mm=%p, isolated=%d, status=%s",
		__entry->mm,
		__entry->isolated,
		__prपूर्णांक_symbolic(__entry->status, SCAN_STATUS))
);

TRACE_EVENT(mm_collapse_huge_page_isolate,

	TP_PROTO(काष्ठा page *page, पूर्णांक none_or_zero,
		 पूर्णांक referenced, bool  writable, पूर्णांक status),

	TP_ARGS(page, none_or_zero, referenced, writable, status),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, pfn)
		__field(पूर्णांक, none_or_zero)
		__field(पूर्णांक, referenced)
		__field(bool, writable)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		__entry->pfn = page ? page_to_pfn(page) : -1;
		__entry->none_or_zero = none_or_zero;
		__entry->referenced = referenced;
		__entry->writable = writable;
		__entry->status = status;
	),

	TP_prपूर्णांकk("scan_pfn=0x%lx, none_or_zero=%d, referenced=%d, writable=%d, status=%s",
		__entry->pfn,
		__entry->none_or_zero,
		__entry->referenced,
		__entry->writable,
		__prपूर्णांक_symbolic(__entry->status, SCAN_STATUS))
);

TRACE_EVENT(mm_collapse_huge_page_swapin,

	TP_PROTO(काष्ठा mm_काष्ठा *mm, पूर्णांक swapped_in, पूर्णांक referenced, पूर्णांक ret),

	TP_ARGS(mm, swapped_in, referenced, ret),

	TP_STRUCT__entry(
		__field(काष्ठा mm_काष्ठा *, mm)
		__field(पूर्णांक, swapped_in)
		__field(पूर्णांक, referenced)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->mm = mm;
		__entry->swapped_in = swapped_in;
		__entry->referenced = referenced;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("mm=%p, swapped_in=%d, referenced=%d, ret=%d",
		__entry->mm,
		__entry->swapped_in,
		__entry->referenced,
		__entry->ret)
);

#पूर्ण_अगर /* __HUGE_MEMORY_H */
#समावेश <trace/define_trace.h>
