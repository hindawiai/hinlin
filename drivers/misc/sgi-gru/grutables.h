<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SN Platक्रमm GRU Driver
 *
 *            GRU DRIVER TABLES, MACROS, बाह्यs, etc
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#अगर_अघोषित __GRUTABLES_H__
#घोषणा __GRUTABLES_H__

/*
 * GRU Chiplet:
 *   The GRU is a user addressible memory accelerator. It provides
 *   several क्रमms of load, store, स_रखो, bcopy inकाष्ठाions. In addition, it
 *   contains special inकाष्ठाions क्रम AMOs, sending messages to message
 *   queues, etc.
 *
 *   The GRU is an पूर्णांकegral part of the node controller. It connects
 *   directly to the cpu socket. In its current implementation, there are 2
 *   GRU chiplets in the node controller on each blade (~node).
 *
 *   The entire GRU memory space is fully coherent and cacheable by the cpus.
 *
 *   Each GRU chiplet has a physical memory map that looks like the following:
 *
 *   	+-----------------+
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	|/////////////////|
 *   	+-----------------+
 *   	|  प्रणाली control |
 *   	+-----------------+        _______ +-------------+
 *   	|/////////////////|       /        |             |
 *   	|/////////////////|      /         |             |
 *   	|/////////////////|     /          | inकाष्ठाions|
 *   	|/////////////////|    /           |             |
 *   	|/////////////////|   /            |             |
 *   	|/////////////////|  /             |-------------|
 *   	|/////////////////| /              |             |
 *   	+-----------------+                |             |
 *   	|   context 15    |                |  data       |
 *   	+-----------------+                |             |
 *   	|    ......       | \              |             |
 *   	+-----------------+  \____________ +-------------+
 *   	|   context 1     |
 *   	+-----------------+
 *   	|   context 0     |
 *   	+-----------------+
 *
 *   Each of the "contexts" is a chunk of memory that can be mmaped पूर्णांकo user
 *   space. The context consists of 2 parts:
 *
 *  	- an inकाष्ठाion space that can be directly accessed by the user
 *  	  to issue GRU inकाष्ठाions and to check inकाष्ठाion status.
 *
 *  	- a data area that acts as normal RAM.
 *
 *   User inकाष्ठाions contain भव addresses of data to be accessed by the
 *   GRU. The GRU contains a TLB that is used to convert these user भव
 *   addresses to physical addresses.
 *
 *   The "system control" area of the GRU chiplet is used by the kernel driver
 *   to manage user contexts and to perक्रमm functions such as TLB dropin and
 *   purging.
 *
 *   One context may be reserved क्रम the kernel and used क्रम cross-partition
 *   communication. The GRU will also be used to asynchronously zero out
 *   large blocks of memory (not currently implemented).
 *
 *
 * Tables:
 *
 * 	VDATA-VMA Data		- Holds a few parameters. Head of linked list of
 * 				  GTS tables क्रम thपढ़ोs using the GSEG
 * 	GTS - Gru Thपढ़ो State  - contains info क्रम managing a GSEG context. A
 * 				  GTS is allocated क्रम each thपढ़ो accessing a
 * 				  GSEG.
 *     	GTD - GRU Thपढ़ो Data   - contains shaकरोw copy of GRU data when GSEG is
 *     				  not loaded पूर्णांकo a GRU
 *	GMS - GRU Memory Struct - Used to manage TLB shootकरोwns. Tracks GRUs
 *				  where a GSEG has been loaded. Similar to
 *				  an mm_काष्ठा but क्रम GRU.
 *
 *	GS  - GRU State 	- Used to manage the state of a GRU chiplet
 *	BS  - Blade State	- Used to manage state of all GRU chiplets
 *				  on a blade
 *
 *
 *  Normal task tables क्रम task using GRU.
 *  		- 2 thपढ़ोs in process
 *  		- 2 GSEGs खोलो in process
 *  		- GSEG1 is being used by both thपढ़ोs
 *  		- GSEG2 is used only by thपढ़ो 2
 *
 *       task -->|
 *       task ---+---> mm ->------ (notअगरier) -------+-> gms
 *                     |                             |
 *                     |--> vma -> vdata ---> gts--->|		GSEG1 (thपढ़ो1)
 *                     |                  |          |
 *                     |                  +-> gts--->|		GSEG1 (thपढ़ो2)
 *                     |                             |
 *                     |--> vma -> vdata ---> gts--->|		GSEG2 (thपढ़ो2)
 *                     .
 *                     .
 *
 *  GSEGs are marked DONTCOPY on विभाजन
 *
 * At खोलो
 * 	file.निजी_data -> शून्य
 *
 * At mmap,
 * 	vma -> vdata
 *
 * After gseg reference
 * 	vma -> vdata ->gts
 *
 * After विभाजन
 *   parent
 * 	vma -> vdata -> gts
 *   child
 * 	(vma is not copied)
 *
 */

#समावेश <linux/rmap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/mm_types.h>
#समावेश "gru.h"
#समावेश "grulib.h"
#समावेश "gruhandles.h"

बाह्य काष्ठा gru_stats_s gru_stats;
बाह्य काष्ठा gru_blade_state *gru_base[];
बाह्य अचिन्हित दीर्घ gru_start_paddr, gru_end_paddr;
बाह्य व्योम *gru_start_vaddr;
बाह्य अचिन्हित पूर्णांक gru_max_gids;

#घोषणा GRU_MAX_BLADES		MAX_NUMNODES
#घोषणा GRU_MAX_GRUS		(GRU_MAX_BLADES * GRU_CHIPLETS_PER_BLADE)

#घोषणा GRU_DRIVER_ID_STR	"SGI GRU Device Driver"
#घोषणा GRU_DRIVER_VERSION_STR	"0.85"

/*
 * GRU statistics.
 */
काष्ठा gru_stats_s अणु
	atomic_दीर्घ_t vdata_alloc;
	atomic_दीर्घ_t vdata_मुक्त;
	atomic_दीर्घ_t gts_alloc;
	atomic_दीर्घ_t gts_मुक्त;
	atomic_दीर्घ_t gms_alloc;
	atomic_दीर्घ_t gms_मुक्त;
	atomic_दीर्घ_t gts_द्विगुन_allocate;
	atomic_दीर्घ_t assign_context;
	atomic_दीर्घ_t assign_context_failed;
	atomic_दीर्घ_t मुक्त_context;
	atomic_दीर्घ_t load_user_context;
	atomic_दीर्घ_t load_kernel_context;
	atomic_दीर्घ_t lock_kernel_context;
	atomic_दीर्घ_t unlock_kernel_context;
	atomic_दीर्घ_t steal_user_context;
	atomic_दीर्घ_t steal_kernel_context;
	atomic_दीर्घ_t steal_context_failed;
	atomic_दीर्घ_t nopfn;
	atomic_दीर्घ_t asid_new;
	atomic_दीर्घ_t asid_next;
	atomic_दीर्घ_t asid_wrap;
	atomic_दीर्घ_t asid_reuse;
	atomic_दीर्घ_t पूर्णांकr;
	atomic_दीर्घ_t पूर्णांकr_cbr;
	atomic_दीर्घ_t पूर्णांकr_tfh;
	atomic_दीर्घ_t पूर्णांकr_spurious;
	atomic_दीर्घ_t पूर्णांकr_mm_lock_failed;
	atomic_दीर्घ_t call_os;
	atomic_दीर्घ_t call_os_रुको_queue;
	atomic_दीर्घ_t user_flush_tlb;
	atomic_दीर्घ_t user_unload_context;
	atomic_दीर्घ_t user_exception;
	atomic_दीर्घ_t set_context_option;
	atomic_दीर्घ_t check_context_retarget_पूर्णांकr;
	atomic_दीर्घ_t check_context_unload;
	atomic_दीर्घ_t tlb_dropin;
	atomic_दीर्घ_t tlb_preload_page;
	atomic_दीर्घ_t tlb_dropin_fail_no_asid;
	atomic_दीर्घ_t tlb_dropin_fail_upm;
	atomic_दीर्घ_t tlb_dropin_fail_invalid;
	atomic_दीर्घ_t tlb_dropin_fail_range_active;
	atomic_दीर्घ_t tlb_dropin_fail_idle;
	atomic_दीर्घ_t tlb_dropin_fail_fmm;
	atomic_दीर्घ_t tlb_dropin_fail_no_exception;
	atomic_दीर्घ_t tfh_stale_on_fault;
	atomic_दीर्घ_t mmu_invalidate_range;
	atomic_दीर्घ_t mmu_invalidate_page;
	atomic_दीर्घ_t flush_tlb;
	atomic_दीर्घ_t flush_tlb_gru;
	atomic_दीर्घ_t flush_tlb_gru_tgh;
	atomic_दीर्घ_t flush_tlb_gru_zero_asid;

	atomic_दीर्घ_t copy_gpa;
	atomic_दीर्घ_t पढ़ो_gpa;

	atomic_दीर्घ_t mesq_receive;
	atomic_दीर्घ_t mesq_receive_none;
	atomic_दीर्घ_t mesq_send;
	atomic_दीर्घ_t mesq_send_failed;
	atomic_दीर्घ_t mesq_noop;
	atomic_दीर्घ_t mesq_send_unexpected_error;
	atomic_दीर्घ_t mesq_send_lb_overflow;
	atomic_दीर्घ_t mesq_send_qlimit_reached;
	atomic_दीर्घ_t mesq_send_amo_nacked;
	atomic_दीर्घ_t mesq_send_put_nacked;
	atomic_दीर्घ_t mesq_page_overflow;
	atomic_दीर्घ_t mesq_qf_locked;
	atomic_दीर्घ_t mesq_qf_noop_not_full;
	atomic_दीर्घ_t mesq_qf_चयन_head_failed;
	atomic_दीर्घ_t mesq_qf_unexpected_error;
	atomic_दीर्घ_t mesq_noop_unexpected_error;
	atomic_दीर्घ_t mesq_noop_lb_overflow;
	atomic_दीर्घ_t mesq_noop_qlimit_reached;
	atomic_दीर्घ_t mesq_noop_amo_nacked;
	atomic_दीर्घ_t mesq_noop_put_nacked;
	atomic_दीर्घ_t mesq_noop_page_overflow;

पूर्ण;

क्रमागत mcs_op अणुcchop_allocate, cchop_start, cchop_पूर्णांकerrupt, cchop_पूर्णांकerrupt_sync,
	cchop_deallocate, tfhop_ग_लिखो_only, tfhop_ग_लिखो_restart,
	tghop_invalidate, mcsop_lastपूर्ण;

काष्ठा mcs_op_statistic अणु
	atomic_दीर्घ_t	count;
	atomic_दीर्घ_t	total;
	अचिन्हित दीर्घ	max;
पूर्ण;

बाह्य काष्ठा mcs_op_statistic mcs_op_statistics[mcsop_last];

#घोषणा OPT_DPRINT		1
#घोषणा OPT_STATS		2


#घोषणा IRQ_GRU			110	/* Starting IRQ number क्रम पूर्णांकerrupts */

/* Delay in jअगरfies between attempts to assign a GRU context */
#घोषणा GRU_ASSIGN_DELAY	((HZ * 20) / 1000)

/*
 * If a process has it's context stolen, min delay in jअगरfies beक्रमe trying to
 * steal a context from another process.
 */
#घोषणा GRU_STEAL_DELAY		((HZ * 200) / 1000)

#घोषणा STAT(id)	करो अणु						\
				अगर (gru_options & OPT_STATS)		\
					atomic_दीर्घ_inc(&gru_stats.id);	\
			पूर्ण जबतक (0)

#अगर_घोषित CONFIG_SGI_GRU_DEBUG
#घोषणा gru_dbg(dev, fmt, x...)						\
	करो अणु								\
		अगर (gru_options & OPT_DPRINT)				\
			prपूर्णांकk(KERN_DEBUG "GRU:%d %s: " fmt, smp_processor_id(), __func__, x);\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा gru_dbg(x...)
#पूर्ण_अगर

/*-----------------------------------------------------------------------------
 * ASID management
 */
#घोषणा MAX_ASID	0xfffff0
#घोषणा MIN_ASID	8
#घोषणा ASID_INC	8	/* number of regions */

/* Generate a GRU asid value from a GRU base asid & a भव address. */
#घोषणा VADDR_HI_BIT		64
#घोषणा GRUREGION(addr)		((addr) >> (VADDR_HI_BIT - 3) & 3)
#घोषणा GRUASID(asid, addr)	((asid) + GRUREGION(addr))

/*------------------------------------------------------------------------------
 *  File & VMS Tables
 */

काष्ठा gru_state;

/*
 * This काष्ठाure is poपूर्णांकed to from the mmकाष्ठा via the notअगरier poपूर्णांकer.
 * There is one of these per address space.
 */
काष्ठा gru_mm_tracker अणु				/* pack to reduce size */
	अचिन्हित पूर्णांक		mt_asid_gen:24;	/* ASID wrap count */
	अचिन्हित पूर्णांक		mt_asid:24;	/* current base ASID क्रम gru */
	अचिन्हित लघु		mt_ctxbiपंचांगap:16;/* biपंचांगap of contexts using
						   asid */
पूर्ण __attribute__ ((packed));

काष्ठा gru_mm_काष्ठा अणु
	काष्ठा mmu_notअगरier	ms_notअगरier;
	spinlock_t		ms_asid_lock;	/* protects ASID assignment */
	atomic_t		ms_range_active;/* num range_invals active */
	रुको_queue_head_t	ms_रुको_queue;
	DECLARE_BITMAP(ms_asidmap, GRU_MAX_GRUS);
	काष्ठा gru_mm_tracker	ms_asids[GRU_MAX_GRUS];
पूर्ण;

/*
 * One of these काष्ठाures is allocated when a GSEG is mmaped. The
 * काष्ठाure is poपूर्णांकed to by the vma->vm_निजी_data field in the vma काष्ठा.
 */
काष्ठा gru_vma_data अणु
	spinlock_t		vd_lock;	/* Serialize access to vma */
	काष्ठा list_head	vd_head;	/* head of linked list of gts */
	दीर्घ			vd_user_options;/* misc user option flags */
	पूर्णांक			vd_cbr_au_count;
	पूर्णांक			vd_dsr_au_count;
	अचिन्हित अक्षर		vd_tlb_preload_count;
पूर्ण;

/*
 * One of these is allocated क्रम each thपढ़ो accessing a mmaped GRU. A linked
 * list of these काष्ठाure is hung off the काष्ठा gru_vma_data in the mm_काष्ठा.
 */
काष्ठा gru_thपढ़ो_state अणु
	काष्ठा list_head	ts_next;	/* list - head at vma-निजी */
	काष्ठा mutex		ts_ctxlock;	/* load/unload CTX lock */
	काष्ठा mm_काष्ठा	*ts_mm;		/* mm currently mapped to
						   context */
	काष्ठा vm_area_काष्ठा	*ts_vma;	/* vma of GRU context */
	काष्ठा gru_state	*ts_gru;	/* GRU where the context is
						   loaded */
	काष्ठा gru_mm_काष्ठा	*ts_gms;	/* asid & ioproc काष्ठा */
	अचिन्हित अक्षर		ts_tlb_preload_count; /* TLB preload pages */
	अचिन्हित दीर्घ		ts_cbr_map;	/* map of allocated CBRs */
	अचिन्हित दीर्घ		ts_dsr_map;	/* map of allocated DATA
						   resources */
	अचिन्हित दीर्घ		ts_steal_jअगरfies;/* jअगरfies when context last
						    stolen */
	दीर्घ			ts_user_options;/* misc user option flags */
	pid_t			ts_tgid_owner;	/* task that is using the
						   context - क्रम migration */
	लघु			ts_user_blade_id;/* user selected blade */
	अक्षर			ts_user_chiplet_id;/* user selected chiplet */
	अचिन्हित लघु		ts_sizeavail;	/* Pagesizes in use */
	पूर्णांक			ts_tsid;	/* thपढ़ो that owns the
						   काष्ठाure */
	पूर्णांक			ts_tlb_पूर्णांक_select;/* target cpu अगर पूर्णांकerrupts
						     enabled */
	पूर्णांक			ts_ctxnum;	/* context number where the
						   context is loaded */
	atomic_t		ts_refcnt;	/* reference count GTS */
	अचिन्हित अक्षर		ts_dsr_au_count;/* Number of DSR resources
						   required क्रम contest */
	अचिन्हित अक्षर		ts_cbr_au_count;/* Number of CBR resources
						   required क्रम contest */
	अक्षर			ts_cch_req_slice;/* CCH packet slice */
	अक्षर			ts_blade;	/* If >= 0, migrate context अगर
						   ref from dअगरferent blade */
	अक्षर			ts_क्रमce_cch_reload;
	अक्षर			ts_cbr_idx[GRU_CBR_AU];/* CBR numbers of each
							  allocated CB */
	पूर्णांक			ts_data_valid;	/* Indicates अगर ts_gdata has
						   valid data */
	काष्ठा gru_gseg_statistics ustats;	/* User statistics */
	अचिन्हित दीर्घ		ts_gdata[];	/* save area क्रम GRU data (CB,
						   DS, CBE) */
पूर्ण;

/*
 * Thपढ़ोed programs actually allocate an array of GSEGs when a context is
 * created. Each thपढ़ो uses a separate GSEG. TSID is the index पूर्णांकo the GSEG
 * array.
 */
#घोषणा TSID(a, v)		(((a) - (v)->vm_start) / GRU_GSEG_PAGESIZE)
#घोषणा UGRUADDR(gts)		((gts)->ts_vma->vm_start +		\
					(gts)->ts_tsid * GRU_GSEG_PAGESIZE)

#घोषणा शून्यCTX			(-1)	/* अगर context not loaded पूर्णांकo GRU */

/*-----------------------------------------------------------------------------
 *  GRU State Tables
 */

/*
 * One of these exists क्रम each GRU chiplet.
 */
काष्ठा gru_state अणु
	काष्ठा gru_blade_state	*gs_blade;		/* GRU state क्रम entire
							   blade */
	अचिन्हित दीर्घ		gs_gru_base_paddr;	/* Physical address of
							   gru segments (64) */
	व्योम			*gs_gru_base_vaddr;	/* Virtual address of
							   gru segments (64) */
	अचिन्हित लघु		gs_gid;			/* unique GRU number */
	अचिन्हित लघु		gs_blade_id;		/* blade of GRU */
	अचिन्हित अक्षर		gs_chiplet_id;		/* blade chiplet of GRU */
	अचिन्हित अक्षर		gs_tgh_local_shअगरt;	/* used to pick TGH क्रम
							   local flush */
	अचिन्हित अक्षर		gs_tgh_first_remote;	/* starting TGH# क्रम
							   remote flush */
	spinlock_t		gs_asid_lock;		/* lock used क्रम
							   assigning asids */
	spinlock_t		gs_lock;		/* lock used क्रम
							   assigning contexts */

	/* -- the following are रक्षित by the gs_asid_lock spinlock ---- */
	अचिन्हित पूर्णांक		gs_asid;		/* Next availe ASID */
	अचिन्हित पूर्णांक		gs_asid_limit;		/* Limit of available
							   ASIDs */
	अचिन्हित पूर्णांक		gs_asid_gen;		/* asid generation.
							   Inc on wrap */

	/* --- the following fields are रक्षित by the gs_lock spinlock --- */
	अचिन्हित दीर्घ		gs_context_map;		/* biपंचांगap to manage
							   contexts in use */
	अचिन्हित दीर्घ		gs_cbr_map;		/* biपंचांगap to manage CB
							   resources */
	अचिन्हित दीर्घ		gs_dsr_map;		/* biपंचांगap used to manage
							   DATA resources */
	अचिन्हित पूर्णांक		gs_reserved_cbrs;	/* Number of kernel-
							   reserved cbrs */
	अचिन्हित पूर्णांक		gs_reserved_dsr_bytes;	/* Bytes of kernel-
							   reserved dsrs */
	अचिन्हित लघु		gs_active_contexts;	/* number of contexts
							   in use */
	काष्ठा gru_thपढ़ो_state	*gs_gts[GRU_NUM_CCH];	/* GTS currently using
							   the context */
	पूर्णांक			gs_irq[GRU_NUM_TFM];	/* Interrupt irqs */
पूर्ण;

/*
 * This काष्ठाure contains the GRU state क्रम all the GRUs on a blade.
 */
काष्ठा gru_blade_state अणु
	व्योम			*kernel_cb;		/* First kernel
							   reserved cb */
	व्योम			*kernel_dsr;		/* First kernel
							   reserved DSR */
	काष्ठा rw_semaphore	bs_kgts_sema;		/* lock क्रम kgts */
	काष्ठा gru_thपढ़ो_state *bs_kgts;		/* GTS क्रम kernel use */

	/* ---- the following are used क्रम managing kernel async GRU CBRs --- */
	पूर्णांक			bs_async_dsr_bytes;	/* DSRs क्रम async */
	पूर्णांक			bs_async_cbrs;		/* CBRs AU क्रम async */
	काष्ठा completion	*bs_async_wq;

	/* ---- the following are रक्षित by the bs_lock spinlock ---- */
	spinlock_t		bs_lock;		/* lock used क्रम
							   stealing contexts */
	पूर्णांक			bs_lru_ctxnum;		/* STEAL - last context
							   stolen */
	काष्ठा gru_state	*bs_lru_gru;		/* STEAL - last gru
							   stolen */

	काष्ठा gru_state	bs_grus[GRU_CHIPLETS_PER_BLADE];
पूर्ण;

/*-----------------------------------------------------------------------------
 * Address Primitives
 */
#घोषणा get_tfm_क्रम_cpu(g, c)						\
	((काष्ठा gru_tlb_fault_map *)get_tfm((g)->gs_gru_base_vaddr, (c)))
#घोषणा get_tfh_by_index(g, i)						\
	((काष्ठा gru_tlb_fault_handle *)get_tfh((g)->gs_gru_base_vaddr, (i)))
#घोषणा get_tgh_by_index(g, i)						\
	((काष्ठा gru_tlb_global_handle *)get_tgh((g)->gs_gru_base_vaddr, (i)))
#घोषणा get_cbe_by_index(g, i)						\
	((काष्ठा gru_control_block_extended *)get_cbe((g)->gs_gru_base_vaddr,\
			(i)))

/*-----------------------------------------------------------------------------
 * Useful Macros
 */

/* Given a blade# & chiplet#, get a poपूर्णांकer to the GRU */
#घोषणा get_gru(b, c)		(&gru_base[b]->bs_grus[c])

/* Number of bytes to save/restore when unloading/loading GRU contexts */
#घोषणा DSR_BYTES(dsr)		((dsr) * GRU_DSR_AU_BYTES)
#घोषणा CBR_BYTES(cbr)		((cbr) * GRU_HANDLE_BYTES * GRU_CBR_AU_SIZE * 2)

/* Convert a user CB number to the actual CBRNUM */
#घोषणा thपढ़ो_cbr_number(gts, n) ((gts)->ts_cbr_idx[(n) / GRU_CBR_AU_SIZE] \
				  * GRU_CBR_AU_SIZE + (n) % GRU_CBR_AU_SIZE)

/* Convert a gid to a poपूर्णांकer to the GRU */
#घोषणा GID_TO_GRU(gid)							\
	(gru_base[(gid) / GRU_CHIPLETS_PER_BLADE] ?			\
		(&gru_base[(gid) / GRU_CHIPLETS_PER_BLADE]->		\
			bs_grus[(gid) % GRU_CHIPLETS_PER_BLADE]) :	\
	 शून्य)

/* Scan all active GRUs in a GRU biपंचांगap */
#घोषणा क्रम_each_gru_in_biपंचांगap(gid, map)				\
	क्रम_each_set_bit((gid), (map), GRU_MAX_GRUS)

/* Scan all active GRUs on a specअगरic blade */
#घोषणा क्रम_each_gru_on_blade(gru, nid, i)				\
	क्रम ((gru) = gru_base[nid]->bs_grus, (i) = 0;			\
			(i) < GRU_CHIPLETS_PER_BLADE;			\
			(i)++, (gru)++)

/* Scan all GRUs */
#घोषणा क्रमeach_gid(gid)						\
	क्रम ((gid) = 0; (gid) < gru_max_gids; (gid)++)

/* Scan all active GTSs on a gru. Note: must hold ss_lock to use this macro. */
#घोषणा क्रम_each_gts_on_gru(gts, gru, ctxnum)				\
	क्रम ((ctxnum) = 0; (ctxnum) < GRU_NUM_CCH; (ctxnum)++)		\
		अगर (((gts) = (gru)->gs_gts[ctxnum]))

/* Scan each CBR whose bit is set in a TFM (or copy of) */
#घोषणा क्रम_each_cbr_in_tfm(i, map)					\
	क्रम_each_set_bit((i), (map), GRU_NUM_CBE)

/* Scan each CBR in a CBR biपंचांगap. Note: multiple CBRs in an allocation unit */
#घोषणा क्रम_each_cbr_in_allocation_map(i, map, k)			\
	क्रम_each_set_bit((k), (map), GRU_CBR_AU)			\
		क्रम ((i) = (k)*GRU_CBR_AU_SIZE;				\
				(i) < ((k) + 1) * GRU_CBR_AU_SIZE; (i)++)

/* Scan each DSR in a DSR biपंचांगap. Note: multiple DSRs in an allocation unit */
#घोषणा क्रम_each_dsr_in_allocation_map(i, map, k)			\
	क्रम_each_set_bit((k), (स्थिर अचिन्हित दीर्घ *)(map), GRU_DSR_AU)	\
		क्रम ((i) = (k) * GRU_DSR_AU_CL;				\
				(i) < ((k) + 1) * GRU_DSR_AU_CL; (i)++)

#घोषणा gseg_physical_address(gru, ctxnum)				\
		((gru)->gs_gru_base_paddr + ctxnum * GRU_GSEG_STRIDE)
#घोषणा gseg_भव_address(gru, ctxnum)				\
		((gru)->gs_gru_base_vaddr + ctxnum * GRU_GSEG_STRIDE)

/*-----------------------------------------------------------------------------
 * Lock / Unlock GRU handles
 * 	Use the "delresp" bit in the handle as a "lock" bit.
 */

/* Lock hierarchy checking enabled only in emulator */

/* 0 = lock failed, 1 = locked */
अटल अंतरभूत पूर्णांक __trylock_handle(व्योम *h)
अणु
	वापस !test_and_set_bit(1, h);
पूर्ण

अटल अंतरभूत व्योम __lock_handle(व्योम *h)
अणु
	जबतक (test_and_set_bit(1, h))
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम __unlock_handle(व्योम *h)
अणु
	clear_bit(1, h);
पूर्ण

अटल अंतरभूत पूर्णांक trylock_cch_handle(काष्ठा gru_context_configuration_handle *cch)
अणु
	वापस __trylock_handle(cch);
पूर्ण

अटल अंतरभूत व्योम lock_cch_handle(काष्ठा gru_context_configuration_handle *cch)
अणु
	__lock_handle(cch);
पूर्ण

अटल अंतरभूत व्योम unlock_cch_handle(काष्ठा gru_context_configuration_handle
				     *cch)
अणु
	__unlock_handle(cch);
पूर्ण

अटल अंतरभूत व्योम lock_tgh_handle(काष्ठा gru_tlb_global_handle *tgh)
अणु
	__lock_handle(tgh);
पूर्ण

अटल अंतरभूत व्योम unlock_tgh_handle(काष्ठा gru_tlb_global_handle *tgh)
अणु
	__unlock_handle(tgh);
पूर्ण

अटल अंतरभूत पूर्णांक is_kernel_context(काष्ठा gru_thपढ़ो_state *gts)
अणु
	वापस !gts->ts_mm;
पूर्ण

/*
 * The following are क्रम Nehelem-EX. A more general scheme is needed क्रम
 * future processors.
 */
#घोषणा UV_MAX_INT_CORES		8
#घोषणा uv_cpu_socket_number(p)		((cpu_physical_id(p) >> 5) & 1)
#घोषणा uv_cpu_ht_number(p)		(cpu_physical_id(p) & 1)
#घोषणा uv_cpu_core_number(p)		(((cpu_physical_id(p) >> 2) & 4) |	\
					((cpu_physical_id(p) >> 1) & 3))
/*-----------------------------------------------------------------------------
 * Function prototypes & बाह्यs
 */
काष्ठा gru_unload_context_req;

बाह्य स्थिर काष्ठा vm_operations_काष्ठा gru_vm_ops;
बाह्य काष्ठा device *grudev;

बाह्य काष्ठा gru_vma_data *gru_alloc_vma_data(काष्ठा vm_area_काष्ठा *vma,
				पूर्णांक tsid);
बाह्य काष्ठा gru_thपढ़ो_state *gru_find_thपढ़ो_state(काष्ठा vm_area_काष्ठा
				*vma, पूर्णांक tsid);
बाह्य काष्ठा gru_thपढ़ो_state *gru_alloc_thपढ़ो_state(काष्ठा vm_area_काष्ठा
				*vma, पूर्णांक tsid);
बाह्य काष्ठा gru_state *gru_assign_gru_context(काष्ठा gru_thपढ़ो_state *gts);
बाह्य व्योम gru_load_context(काष्ठा gru_thपढ़ो_state *gts);
बाह्य व्योम gru_steal_context(काष्ठा gru_thपढ़ो_state *gts);
बाह्य व्योम gru_unload_context(काष्ठा gru_thपढ़ो_state *gts, पूर्णांक savestate);
बाह्य पूर्णांक gru_update_cch(काष्ठा gru_thपढ़ो_state *gts);
बाह्य व्योम gts_drop(काष्ठा gru_thपढ़ो_state *gts);
बाह्य व्योम gru_tgh_flush_init(काष्ठा gru_state *gru);
बाह्य पूर्णांक gru_kservices_init(व्योम);
बाह्य व्योम gru_kservices_निकास(व्योम);
बाह्य irqवापस_t gru0_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
बाह्य irqवापस_t gru1_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
बाह्य irqवापस_t gru_पूर्णांकr_mblade(पूर्णांक irq, व्योम *dev_id);
बाह्य पूर्णांक gru_dump_chiplet_request(अचिन्हित दीर्घ arg);
बाह्य दीर्घ gru_get_gseg_statistics(अचिन्हित दीर्घ arg);
बाह्य पूर्णांक gru_handle_user_call_os(अचिन्हित दीर्घ address);
बाह्य पूर्णांक gru_user_flush_tlb(अचिन्हित दीर्घ arg);
बाह्य पूर्णांक gru_user_unload_context(अचिन्हित दीर्घ arg);
बाह्य पूर्णांक gru_get_exception_detail(अचिन्हित दीर्घ arg);
बाह्य पूर्णांक gru_set_context_option(अचिन्हित दीर्घ address);
बाह्य व्योम gru_check_context_placement(काष्ठा gru_thपढ़ो_state *gts);
बाह्य पूर्णांक gru_cpu_fault_map_id(व्योम);
बाह्य काष्ठा vm_area_काष्ठा *gru_find_vma(अचिन्हित दीर्घ vaddr);
बाह्य व्योम gru_flush_all_tlb(काष्ठा gru_state *gru);
बाह्य पूर्णांक gru_proc_init(व्योम);
बाह्य व्योम gru_proc_निकास(व्योम);

बाह्य काष्ठा gru_thपढ़ो_state *gru_alloc_gts(काष्ठा vm_area_काष्ठा *vma,
		पूर्णांक cbr_au_count, पूर्णांक dsr_au_count,
		अचिन्हित अक्षर tlb_preload_count, पूर्णांक options, पूर्णांक tsid);
बाह्य अचिन्हित दीर्घ gru_reserve_cb_resources(काष्ठा gru_state *gru,
		पूर्णांक cbr_au_count, अक्षर *cbmap);
बाह्य अचिन्हित दीर्घ gru_reserve_ds_resources(काष्ठा gru_state *gru,
		पूर्णांक dsr_au_count, अक्षर *dsmap);
बाह्य vm_fault_t gru_fault(काष्ठा vm_fault *vmf);
बाह्य काष्ठा gru_mm_काष्ठा *gru_रेजिस्टर_mmu_notअगरier(व्योम);
बाह्य व्योम gru_drop_mmu_notअगरier(काष्ठा gru_mm_काष्ठा *gms);

बाह्य पूर्णांक gru_ktest(अचिन्हित दीर्घ arg);
बाह्य व्योम gru_flush_tlb_range(काष्ठा gru_mm_काष्ठा *gms, अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ len);

बाह्य अचिन्हित दीर्घ gru_options;

#पूर्ण_अगर /* __GRUTABLES_H__ */
