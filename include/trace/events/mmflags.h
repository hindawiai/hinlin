<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/node.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/compaction.h>
/*
 * The order of these masks is important. Matching masks will be seen
 * first and the left over flags will end up showing by themselves.
 *
 * For example, अगर we have GFP_KERNEL beक्रमe GFP_USER we wil get:
 *
 *  GFP_KERNEL|GFP_HARDWALL
 *
 * Thus most bits set go first.
 */

#घोषणा __def_gfpflag_names						\
	अणु(अचिन्हित दीर्घ)GFP_TRANSHUGE,		"GFP_TRANSHUGE"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)GFP_TRANSHUGE_LIGHT,	"GFP_TRANSHUGE_LIGHT"पूर्ण, \
	अणु(अचिन्हित दीर्घ)GFP_HIGHUSER_MOVABLE,	"GFP_HIGHUSER_MOVABLE"पूर्ण,\
	अणु(अचिन्हित दीर्घ)GFP_HIGHUSER,		"GFP_HIGHUSER"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)GFP_USER,		"GFP_USER"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)GFP_KERNEL_ACCOUNT,	"GFP_KERNEL_ACCOUNT"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)GFP_KERNEL,		"GFP_KERNEL"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)GFP_NOFS,		"GFP_NOFS"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)GFP_ATOMIC,		"GFP_ATOMIC"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)GFP_NOIO,		"GFP_NOIO"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)GFP_NOWAIT,		"GFP_NOWAIT"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)GFP_DMA,		"GFP_DMA"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)__GFP_HIGHMEM,		"__GFP_HIGHMEM"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)GFP_DMA32,		"GFP_DMA32"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)__GFP_HIGH,		"__GFP_HIGH"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)__GFP_ATOMIC,		"__GFP_ATOMIC"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_IO,		"__GFP_IO"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)__GFP_FS,		"__GFP_FS"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)__GFP_NOWARN,		"__GFP_NOWARN"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_RETRY_MAYFAIL,	"__GFP_RETRY_MAYFAIL"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_NOFAIL,		"__GFP_NOFAIL"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_NORETRY,		"__GFP_NORETRY"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_COMP,		"__GFP_COMP"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)__GFP_ZERO,		"__GFP_ZERO"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)__GFP_NOMEMALLOC,	"__GFP_NOMEMALLOC"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_MEMALLOC,		"__GFP_MEMALLOC"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_HARDWALL,		"__GFP_HARDWALL"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_THISNODE,		"__GFP_THISNODE"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_RECLAIMABLE,	"__GFP_RECLAIMABLE"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_MOVABLE,		"__GFP_MOVABLE"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_ACCOUNT,		"__GFP_ACCOUNT"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_WRITE,		"__GFP_WRITE"पूर्ण,		\
	अणु(अचिन्हित दीर्घ)__GFP_RECLAIM,		"__GFP_RECLAIM"पूर्ण,	\
	अणु(अचिन्हित दीर्घ)__GFP_सूचीECT_RECLAIM,	"__GFP_DIRECT_RECLAIM"पूर्ण,\
	अणु(अचिन्हित दीर्घ)__GFP_KSWAPD_RECLAIM,	"__GFP_KSWAPD_RECLAIM"पूर्ण\

#घोषणा show_gfp_flags(flags)						\
	(flags) ? __prपूर्णांक_flags(flags, "|",				\
	__def_gfpflag_names						\
	) : "none"

#अगर_घोषित CONFIG_MMU
#घोषणा IF_HAVE_PG_MLOCK(flag,string) ,अणु1UL << flag, stringपूर्ण
#अन्यथा
#घोषणा IF_HAVE_PG_MLOCK(flag,string)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_USES_PG_UNCACHED
#घोषणा IF_HAVE_PG_UNCACHED(flag,string) ,अणु1UL << flag, stringपूर्ण
#अन्यथा
#घोषणा IF_HAVE_PG_UNCACHED(flag,string)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMORY_FAILURE
#घोषणा IF_HAVE_PG_HWPOISON(flag,string) ,अणु1UL << flag, stringपूर्ण
#अन्यथा
#घोषणा IF_HAVE_PG_HWPOISON(flag,string)
#पूर्ण_अगर

#अगर defined(CONFIG_IDLE_PAGE_TRACKING) && defined(CONFIG_64BIT)
#घोषणा IF_HAVE_PG_IDLE(flag,string) ,अणु1UL << flag, stringपूर्ण
#अन्यथा
#घोषणा IF_HAVE_PG_IDLE(flag,string)
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#घोषणा IF_HAVE_PG_ARCH_2(flag,string) ,अणु1UL << flag, stringपूर्ण
#अन्यथा
#घोषणा IF_HAVE_PG_ARCH_2(flag,string)
#पूर्ण_अगर

#घोषणा __def_pageflag_names						\
	अणु1UL << PG_locked,		"locked"	पूर्ण,		\
	अणु1UL << PG_रुकोers,		"waiters"	पूर्ण,		\
	अणु1UL << PG_error,		"error"		पूर्ण,		\
	अणु1UL << PG_referenced,		"referenced"	पूर्ण,		\
	अणु1UL << PG_uptodate,		"uptodate"	पूर्ण,		\
	अणु1UL << PG_dirty,		"dirty"		पूर्ण,		\
	अणु1UL << PG_lru,			"lru"		पूर्ण,		\
	अणु1UL << PG_active,		"active"	पूर्ण,		\
	अणु1UL << PG_workingset,		"workingset"	पूर्ण,		\
	अणु1UL << PG_slab,		"slab"		पूर्ण,		\
	अणु1UL << PG_owner_priv_1,	"owner_priv_1"	पूर्ण,		\
	अणु1UL << PG_arch_1,		"arch_1"	पूर्ण,		\
	अणु1UL << PG_reserved,		"reserved"	पूर्ण,		\
	अणु1UL << PG_निजी,		"private"	पूर्ण,		\
	अणु1UL << PG_निजी_2,		"private_2"	पूर्ण,		\
	अणु1UL << PG_ग_लिखोback,		"writeback"	पूर्ण,		\
	अणु1UL << PG_head,		"head"		पूर्ण,		\
	अणु1UL << PG_mappedtodisk,	"mappedtodisk"	पूर्ण,		\
	अणु1UL << PG_reclaim,		"reclaim"	पूर्ण,		\
	अणु1UL << PG_swapbacked,		"swapbacked"	पूर्ण,		\
	अणु1UL << PG_unevictable,		"unevictable"	पूर्ण		\
IF_HAVE_PG_MLOCK(PG_mlocked,		"mlocked"	)		\
IF_HAVE_PG_UNCACHED(PG_uncached,	"uncached"	)		\
IF_HAVE_PG_HWPOISON(PG_hwpoison,	"hwpoison"	)		\
IF_HAVE_PG_IDLE(PG_young,		"young"		)		\
IF_HAVE_PG_IDLE(PG_idle,		"idle"		)		\
IF_HAVE_PG_ARCH_2(PG_arch_2,		"arch_2"	)

#घोषणा show_page_flags(flags)						\
	(flags) ? __prपूर्णांक_flags(flags, "|",				\
	__def_pageflag_names						\
	) : "none"

#अगर defined(CONFIG_X86)
#घोषणा __VM_ARCH_SPECIFIC_1 अणुVM_PAT,     "pat"           पूर्ण
#या_अगर defined(CONFIG_PPC)
#घोषणा __VM_ARCH_SPECIFIC_1 अणुVM_SAO,     "sao"           पूर्ण
#या_अगर defined(CONFIG_PARISC) || defined(CONFIG_IA64)
#घोषणा __VM_ARCH_SPECIFIC_1 अणुVM_GROWSUP,	"growsup"	पूर्ण
#या_अगर !defined(CONFIG_MMU)
#घोषणा __VM_ARCH_SPECIFIC_1 अणुVM_MAPPED_COPY,"mappedcopy"	पूर्ण
#अन्यथा
#घोषणा __VM_ARCH_SPECIFIC_1 अणुVM_ARCH_1,	"arch_1"	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
#घोषणा IF_HAVE_VM_SOFTसूचीTY(flag,name) अणुflag, name पूर्ण,
#अन्यथा
#घोषणा IF_HAVE_VM_SOFTसूचीTY(flag,name)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_USERFAULTFD_MINOR
# define IF_HAVE_UFFD_MINOR(flag, name) अणुflag, nameपूर्ण,
#अन्यथा
# define IF_HAVE_UFFD_MINOR(flag, name)
#पूर्ण_अगर

#घोषणा __def_vmaflag_names						\
	अणुVM_READ,			"read"		पूर्ण,		\
	अणुVM_WRITE,			"write"		पूर्ण,		\
	अणुVM_EXEC,			"exec"		पूर्ण,		\
	अणुVM_SHARED,			"shared"	पूर्ण,		\
	अणुVM_MAYREAD,			"mayread"	पूर्ण,		\
	अणुVM_MAYWRITE,			"maywrite"	पूर्ण,		\
	अणुVM_MAYEXEC,			"mayexec"	पूर्ण,		\
	अणुVM_MAYSHARE,			"mayshare"	पूर्ण,		\
	अणुVM_GROWSDOWN,			"growsdown"	पूर्ण,		\
	अणुVM_UFFD_MISSING,		"uffd_missing"	पूर्ण,		\
IF_HAVE_UFFD_MINOR(VM_UFFD_MINOR,	"uffd_minor"	)		\
	अणुVM_PFNMAP,			"pfnmap"	पूर्ण,		\
	अणुVM_DENYWRITE,			"denywrite"	पूर्ण,		\
	अणुVM_UFFD_WP,			"uffd_wp"	पूर्ण,		\
	अणुVM_LOCKED,			"locked"	पूर्ण,		\
	अणुVM_IO,				"io"		पूर्ण,		\
	अणुVM_SEQ_READ,			"seqread"	पूर्ण,		\
	अणुVM_RAND_READ,			"randread"	पूर्ण,		\
	अणुVM_DONTCOPY,			"dontcopy"	पूर्ण,		\
	अणुVM_DONTEXPAND,			"dontexpand"	पूर्ण,		\
	अणुVM_LOCKONFAULT,		"lockonfault"	पूर्ण,		\
	अणुVM_ACCOUNT,			"account"	पूर्ण,		\
	अणुVM_NORESERVE,			"noreserve"	पूर्ण,		\
	अणुVM_HUGETLB,			"hugetlb"	पूर्ण,		\
	अणुVM_SYNC,			"sync"		पूर्ण,		\
	__VM_ARCH_SPECIFIC_1				,		\
	अणुVM_WIPEONFORK,			"wipeonfork"	पूर्ण,		\
	अणुVM_DONTDUMP,			"dontdump"	पूर्ण,		\
IF_HAVE_VM_SOFTसूचीTY(VM_SOFTसूचीTY,	"softdirty"	)		\
	अणुVM_MIXEDMAP,			"mixedmap"	पूर्ण,		\
	अणुVM_HUGEPAGE,			"hugepage"	पूर्ण,		\
	अणुVM_NOHUGEPAGE,			"nohugepage"	पूर्ण,		\
	अणुVM_MERGEABLE,			"mergeable"	पूर्ण		\

#घोषणा show_vma_flags(flags)						\
	(flags) ? __prपूर्णांक_flags(flags, "|",				\
	__def_vmaflag_names						\
	) : "none"

#अगर_घोषित CONFIG_COMPACTION
#घोषणा COMPACTION_STATUS					\
	EM( COMPACT_SKIPPED,		"skipped")		\
	EM( COMPACT_DEFERRED,		"deferred")		\
	EM( COMPACT_CONTINUE,		"continue")		\
	EM( COMPACT_SUCCESS,		"success")		\
	EM( COMPACT_PARTIAL_SKIPPED,	"partial_skipped")	\
	EM( COMPACT_COMPLETE,		"complete")		\
	EM( COMPACT_NO_SUITABLE_PAGE,	"no_suitable_page")	\
	EM( COMPACT_NOT_SUITABLE_ZONE,	"not_suitable_zone")	\
	EMe(COMPACT_CONTENDED,		"contended")

/* High-level compaction status feedback */
#घोषणा COMPACTION_FAILED	1
#घोषणा COMPACTION_WITHDRAWN	2
#घोषणा COMPACTION_PROGRESS	3

#घोषणा compact_result_to_feedback(result)	\
(अणु						\
	क्रमागत compact_result __result = result;	\
	(compaction_failed(__result)) ? COMPACTION_FAILED : \
		(compaction_withdrawn(__result)) ? COMPACTION_WITHDRAWN : COMPACTION_PROGRESS; \
पूर्ण)

#घोषणा COMPACTION_FEEDBACK		\
	EM(COMPACTION_FAILED,		"failed")	\
	EM(COMPACTION_WITHDRAWN,	"withdrawn")	\
	EMe(COMPACTION_PROGRESS,	"progress")

#घोषणा COMPACTION_PRIORITY						\
	EM(COMPACT_PRIO_SYNC_FULL,	"COMPACT_PRIO_SYNC_FULL")	\
	EM(COMPACT_PRIO_SYNC_LIGHT,	"COMPACT_PRIO_SYNC_LIGHT")	\
	EMe(COMPACT_PRIO_ASYNC,		"COMPACT_PRIO_ASYNC")
#अन्यथा
#घोषणा COMPACTION_STATUS
#घोषणा COMPACTION_PRIORITY
#घोषणा COMPACTION_FEEDBACK
#पूर्ण_अगर

#अगर_घोषित CONFIG_ZONE_DMA
#घोषणा IFDEF_ZONE_DMA(X) X
#अन्यथा
#घोषणा IFDEF_ZONE_DMA(X)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ZONE_DMA32
#घोषणा IFDEF_ZONE_DMA32(X) X
#अन्यथा
#घोषणा IFDEF_ZONE_DMA32(X)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIGHMEM
#घोषणा IFDEF_ZONE_HIGHMEM(X) X
#अन्यथा
#घोषणा IFDEF_ZONE_HIGHMEM(X)
#पूर्ण_अगर

#घोषणा ZONE_TYPE						\
	IFDEF_ZONE_DMA(		EM (ZONE_DMA,	 "DMA"))	\
	IFDEF_ZONE_DMA32(	EM (ZONE_DMA32,	 "DMA32"))	\
				EM (ZONE_NORMAL, "Normal")	\
	IFDEF_ZONE_HIGHMEM(	EM (ZONE_HIGHMEM,"HighMem"))	\
				EMe(ZONE_MOVABLE,"Movable")

#घोषणा LRU_NAMES		\
		EM (LRU_INACTIVE_ANON, "inactive_anon") \
		EM (LRU_ACTIVE_ANON, "active_anon") \
		EM (LRU_INACTIVE_खाता, "inactive_file") \
		EM (LRU_ACTIVE_खाता, "active_file") \
		EMe(LRU_UNEVICTABLE, "unevictable")

/*
 * First define the क्रमागतs in the above macros to be exported to userspace
 * via TRACE_DEFINE_ENUM().
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a, b)	TRACE_DEFINE_ENUM(a);

COMPACTION_STATUS
COMPACTION_PRIORITY
/* COMPACTION_FEEDBACK are defines not क्रमागतs. Not needed here. */
ZONE_TYPE
LRU_NAMES

/*
 * Now redefine the EM() and EMe() macros to map the क्रमागतs to the strings
 * that will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	अणुa, bपूर्ण,
#घोषणा EMe(a, b)	अणुa, bपूर्ण
