<शैली गुरु>
/*
 * Netburst Perक्रमmance Events (P4, old Xeon)
 *
 *  Copyright (C) 2010 Parallels, Inc., Cyrill Gorcunov <gorcunov@खोलोvz.org>
 *  Copyright (C) 2010 Intel Corporation, Lin Ming <ming.m.lin@पूर्णांकel.com>
 *
 *  For licencing details see kernel-base/COPYING
 */

#समावेश <linux/perf_event.h>

#समावेश <यंत्र/perf_event_p4.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/apic.h>

#समावेश "../perf_event.h"

#घोषणा P4_CNTR_LIMIT 3
/*
 * array indices: 0,1 - HT thपढ़ोs, used with HT enabled cpu
 */
काष्ठा p4_event_bind अणु
	अचिन्हित पूर्णांक opcode;			/* Event code and ESCR selector */
	अचिन्हित पूर्णांक escr_msr[2];		/* ESCR MSR क्रम this event */
	अचिन्हित पूर्णांक escr_emask;		/* valid ESCR EventMask bits */
	अचिन्हित पूर्णांक shared;			/* event is shared across thपढ़ोs */
	अक्षर cntr[2][P4_CNTR_LIMIT];		/* counter index (offset), -1 on असलence */
पूर्ण;

काष्ठा p4_pebs_bind अणु
	अचिन्हित पूर्णांक metric_pebs;
	अचिन्हित पूर्णांक metric_vert;
पूर्ण;

/* it sets P4_PEBS_ENABLE_UOP_TAG as well */
#घोषणा P4_GEN_PEBS_BIND(name, pebs, vert)			\
	[P4_PEBS_METRIC__##name] = अणु				\
		.metric_pebs = pebs | P4_PEBS_ENABLE_UOP_TAG,	\
		.metric_vert = vert,				\
	पूर्ण

/*
 * note we have P4_PEBS_ENABLE_UOP_TAG always set here
 *
 * it's needed क्रम mapping P4_PEBS_CONFIG_METRIC_MASK bits of
 * event configuration to find out which values are to be
 * written पूर्णांकo MSR_IA32_PEBS_ENABLE and MSR_P4_PEBS_MATRIX_VERT
 * रेजिस्टरs
 */
अटल काष्ठा p4_pebs_bind p4_pebs_bind_map[] = अणु
	P4_GEN_PEBS_BIND(1stl_cache_load_miss_retired,	0x0000001, 0x0000001),
	P4_GEN_PEBS_BIND(2ndl_cache_load_miss_retired,	0x0000002, 0x0000001),
	P4_GEN_PEBS_BIND(dtlb_load_miss_retired,	0x0000004, 0x0000001),
	P4_GEN_PEBS_BIND(dtlb_store_miss_retired,	0x0000004, 0x0000002),
	P4_GEN_PEBS_BIND(dtlb_all_miss_retired,		0x0000004, 0x0000003),
	P4_GEN_PEBS_BIND(tagged_mispred_branch,		0x0018000, 0x0000010),
	P4_GEN_PEBS_BIND(mob_load_replay_retired,	0x0000200, 0x0000001),
	P4_GEN_PEBS_BIND(split_load_retired,		0x0000400, 0x0000001),
	P4_GEN_PEBS_BIND(split_store_retired,		0x0000400, 0x0000002),
पूर्ण;

/*
 * Note that we करोn't use CCCR1 here, there is an
 * exception क्रम P4_BSQ_ALLOCATION but we just have
 * no workaround
 *
 * consider this binding as resources which particular
 * event may borrow, it करोesn't contain EventMask,
 * Tags and मित्रs -- they are left to a caller
 */
अटल काष्ठा p4_event_bind p4_event_bind_map[] = अणु
	[P4_EVENT_TC_DELIVER_MODE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_TC_DELIVER_MODE),
		.escr_msr	= अणु MSR_P4_TC_ESCR0, MSR_P4_TC_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_DELIVER_MODE, DD)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_DELIVER_MODE, DB)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_DELIVER_MODE, DI)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_DELIVER_MODE, BD)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_DELIVER_MODE, BB)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_DELIVER_MODE, BI)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_DELIVER_MODE, ID),
		.shared		= 1,
		.cntr		= अणु अणु4, 5, -1पूर्ण, अणु6, 7, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_BPU_FETCH_REQUEST] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_BPU_FETCH_REQUEST),
		.escr_msr	= अणु MSR_P4_BPU_ESCR0, MSR_P4_BPU_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_BPU_FETCH_REQUEST, TCMISS),
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_ITLB_REFERENCE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_ITLB_REFERENCE),
		.escr_msr	= अणु MSR_P4_ITLB_ESCR0, MSR_P4_ITLB_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_ITLB_REFERENCE, HIT)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_ITLB_REFERENCE, MISS)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_ITLB_REFERENCE, HIT_UK),
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_MEMORY_CANCEL] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_MEMORY_CANCEL),
		.escr_msr	= अणु MSR_P4_DAC_ESCR0, MSR_P4_DAC_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_MEMORY_CANCEL, ST_RB_FULL)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_MEMORY_CANCEL, 64K_CONF),
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_MEMORY_COMPLETE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_MEMORY_COMPLETE),
		.escr_msr	= अणु MSR_P4_SAAT_ESCR0 , MSR_P4_SAAT_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_MEMORY_COMPLETE, LSC)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_MEMORY_COMPLETE, SSC),
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_LOAD_PORT_REPLAY] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_LOAD_PORT_REPLAY),
		.escr_msr	= अणु MSR_P4_SAAT_ESCR0, MSR_P4_SAAT_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_LOAD_PORT_REPLAY, SPLIT_LD),
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_STORE_PORT_REPLAY] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_STORE_PORT_REPLAY),
		.escr_msr	= अणु MSR_P4_SAAT_ESCR0 ,  MSR_P4_SAAT_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_STORE_PORT_REPLAY, SPLIT_ST),
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_MOB_LOAD_REPLAY] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_MOB_LOAD_REPLAY),
		.escr_msr	= अणु MSR_P4_MOB_ESCR0, MSR_P4_MOB_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_MOB_LOAD_REPLAY, NO_STA)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_MOB_LOAD_REPLAY, NO_STD)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_MOB_LOAD_REPLAY, PARTIAL_DATA)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_MOB_LOAD_REPLAY, UNALGN_ADDR),
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_PAGE_WALK_TYPE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_PAGE_WALK_TYPE),
		.escr_msr	= अणु MSR_P4_PMH_ESCR0, MSR_P4_PMH_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_PAGE_WALK_TYPE, DTMISS)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_PAGE_WALK_TYPE, ITMISS),
		.shared		= 1,
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_BSQ_CACHE_REFERENCE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_BSQ_CACHE_REFERENCE),
		.escr_msr	= अणु MSR_P4_BSU_ESCR0, MSR_P4_BSU_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITS)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITM)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITS)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITM)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_MISS)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_MISS)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, WR_2ndL_MISS),
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_IOQ_ALLOCATION] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_IOQ_ALLOCATION),
		.escr_msr	= अणु MSR_P4_FSB_ESCR0, MSR_P4_FSB_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, DEFAULT)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, ALL_READ)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, ALL_WRITE)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, MEM_UC)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, MEM_WC)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, MEM_WT)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, MEM_WP)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, MEM_WB)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, OWN)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, OTHER)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ALLOCATION, PREFETCH),
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_IOQ_ACTIVE_ENTRIES] = अणु	/* shared ESCR */
		.opcode		= P4_OPCODE(P4_EVENT_IOQ_ACTIVE_ENTRIES),
		.escr_msr	= अणु MSR_P4_FSB_ESCR1,  MSR_P4_FSB_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, DEFAULT)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, ALL_READ)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, ALL_WRITE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_UC)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_WC)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_WT)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_WP)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_WB)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, OWN)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, OTHER)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_IOQ_ACTIVE_ENTRIES, PREFETCH),
		.cntr		= अणु अणु2, -1, -1पूर्ण, अणु3, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_FSB_DATA_ACTIVITY] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_FSB_DATA_ACTIVITY),
		.escr_msr	= अणु MSR_P4_FSB_ESCR0, MSR_P4_FSB_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DRDY_DRV)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DRDY_OWN)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DRDY_OTHER)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_DRV)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_OWN)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_OTHER),
		.shared		= 1,
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_BSQ_ALLOCATION] = अणु		/* shared ESCR, broken CCCR1 */
		.opcode		= P4_OPCODE(P4_EVENT_BSQ_ALLOCATION),
		.escr_msr	= अणु MSR_P4_BSU_ESCR0, MSR_P4_BSU_ESCR0 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_TYPE0)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_TYPE1)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_LEN0)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_LEN1)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_IO_TYPE)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_LOCK_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_CACHE_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_SPLIT_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_DEM_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, REQ_ORD_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, MEM_TYPE0)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, MEM_TYPE1)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ALLOCATION, MEM_TYPE2),
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु1, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_BSQ_ACTIVE_ENTRIES] = अणु	/* shared ESCR */
		.opcode		= P4_OPCODE(P4_EVENT_BSQ_ACTIVE_ENTRIES),
		.escr_msr	= अणु MSR_P4_BSU_ESCR1 , MSR_P4_BSU_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_TYPE0)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_TYPE1)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_LEN0)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_LEN1)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_IO_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_LOCK_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_CACHE_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_SPLIT_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_DEM_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_ORD_TYPE)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, MEM_TYPE0)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, MEM_TYPE1)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_ACTIVE_ENTRIES, MEM_TYPE2),
		.cntr		= अणु अणु2, -1, -1पूर्ण, अणु3, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_SSE_INPUT_ASSIST] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_SSE_INPUT_ASSIST),
		.escr_msr	= अणु MSR_P4_FIRM_ESCR0, MSR_P4_FIRM_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_SSE_INPUT_ASSIST, ALL),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_PACKED_SP_UOP] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_PACKED_SP_UOP),
		.escr_msr	= अणु MSR_P4_FIRM_ESCR0, MSR_P4_FIRM_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_PACKED_SP_UOP, ALL),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_PACKED_DP_UOP] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_PACKED_DP_UOP),
		.escr_msr	= अणु MSR_P4_FIRM_ESCR0, MSR_P4_FIRM_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_PACKED_DP_UOP, ALL),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_SCALAR_SP_UOP] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_SCALAR_SP_UOP),
		.escr_msr	= अणु MSR_P4_FIRM_ESCR0, MSR_P4_FIRM_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_SCALAR_SP_UOP, ALL),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_SCALAR_DP_UOP] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_SCALAR_DP_UOP),
		.escr_msr	= अणु MSR_P4_FIRM_ESCR0, MSR_P4_FIRM_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_SCALAR_DP_UOP, ALL),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_64BIT_MMX_UOP] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_64BIT_MMX_UOP),
		.escr_msr	= अणु MSR_P4_FIRM_ESCR0, MSR_P4_FIRM_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_64BIT_MMX_UOP, ALL),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_128BIT_MMX_UOP] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_128BIT_MMX_UOP),
		.escr_msr	= अणु MSR_P4_FIRM_ESCR0, MSR_P4_FIRM_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_128BIT_MMX_UOP, ALL),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_X87_FP_UOP] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_X87_FP_UOP),
		.escr_msr	= अणु MSR_P4_FIRM_ESCR0, MSR_P4_FIRM_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_X87_FP_UOP, ALL),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_TC_MISC] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_TC_MISC),
		.escr_msr	= अणु MSR_P4_TC_ESCR0, MSR_P4_TC_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_MISC, FLUSH),
		.cntr		= अणु अणु4, 5, -1पूर्ण, अणु6, 7, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_GLOBAL_POWER_EVENTS] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_GLOBAL_POWER_EVENTS),
		.escr_msr	= अणु MSR_P4_FSB_ESCR0, MSR_P4_FSB_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_GLOBAL_POWER_EVENTS, RUNNING),
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_TC_MS_XFER] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_TC_MS_XFER),
		.escr_msr	= अणु MSR_P4_MS_ESCR0, MSR_P4_MS_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_TC_MS_XFER, CISC),
		.cntr		= अणु अणु4, 5, -1पूर्ण, अणु6, 7, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_UOP_QUEUE_WRITES] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_UOP_QUEUE_WRITES),
		.escr_msr	= अणु MSR_P4_MS_ESCR0, MSR_P4_MS_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_UOP_QUEUE_WRITES, FROM_TC_BUILD)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_UOP_QUEUE_WRITES, FROM_TC_DELIVER)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_UOP_QUEUE_WRITES, FROM_ROM),
		.cntr		= अणु अणु4, 5, -1पूर्ण, अणु6, 7, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE),
		.escr_msr	= अणु MSR_P4_TBPU_ESCR0 , MSR_P4_TBPU_ESCR0 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE, CONDITIONAL)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE, CALL)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE, RETURN)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE, INसूचीECT),
		.cntr		= अणु अणु4, 5, -1पूर्ण, अणु6, 7, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_RETIRED_BRANCH_TYPE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_RETIRED_BRANCH_TYPE),
		.escr_msr	= अणु MSR_P4_TBPU_ESCR0 , MSR_P4_TBPU_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_BRANCH_TYPE, CONDITIONAL)	|
			P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_BRANCH_TYPE, CALL)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_BRANCH_TYPE, RETURN)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_BRANCH_TYPE, INसूचीECT),
		.cntr		= अणु अणु4, 5, -1पूर्ण, अणु6, 7, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_RESOURCE_STALL] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_RESOURCE_STALL),
		.escr_msr	= अणु MSR_P4_ALF_ESCR0, MSR_P4_ALF_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_RESOURCE_STALL, SBFULL),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_WC_BUFFER] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_WC_BUFFER),
		.escr_msr	= अणु MSR_P4_DAC_ESCR0, MSR_P4_DAC_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_WC_BUFFER, WCB_EVICTS)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_WC_BUFFER, WCB_FULL_EVICTS),
		.shared		= 1,
		.cntr		= अणु अणु8, 9, -1पूर्ण, अणु10, 11, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_B2B_CYCLES] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_B2B_CYCLES),
		.escr_msr	= अणु MSR_P4_FSB_ESCR0, MSR_P4_FSB_ESCR1 पूर्ण,
		.escr_emask	= 0,
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_BNR] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_BNR),
		.escr_msr	= अणु MSR_P4_FSB_ESCR0, MSR_P4_FSB_ESCR1 पूर्ण,
		.escr_emask	= 0,
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_SNOOP] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_SNOOP),
		.escr_msr	= अणु MSR_P4_FSB_ESCR0, MSR_P4_FSB_ESCR1 पूर्ण,
		.escr_emask	= 0,
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_RESPONSE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_RESPONSE),
		.escr_msr	= अणु MSR_P4_FSB_ESCR0, MSR_P4_FSB_ESCR1 पूर्ण,
		.escr_emask	= 0,
		.cntr		= अणु अणु0, -1, -1पूर्ण, अणु2, -1, -1पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_FRONT_END_EVENT] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_FRONT_END_EVENT),
		.escr_msr	= अणु MSR_P4_CRU_ESCR2, MSR_P4_CRU_ESCR3 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_FRONT_END_EVENT, NBOGUS)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_FRONT_END_EVENT, BOGUS),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_EXECUTION_EVENT] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_EXECUTION_EVENT),
		.escr_msr	= अणु MSR_P4_CRU_ESCR2, MSR_P4_CRU_ESCR3 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS0)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS1)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS2)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS3)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS0)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS1)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS2)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS3),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_REPLAY_EVENT] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_REPLAY_EVENT),
		.escr_msr	= अणु MSR_P4_CRU_ESCR2, MSR_P4_CRU_ESCR3 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_REPLAY_EVENT, NBOGUS)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_REPLAY_EVENT, BOGUS),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_INSTR_RETIRED] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_INSTR_RETIRED),
		.escr_msr	= अणु MSR_P4_CRU_ESCR0, MSR_P4_CRU_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_INSTR_RETIRED, NBOGUSNTAG)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_INSTR_RETIRED, NBOGUSTAG)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_INSTR_RETIRED, BOGUSNTAG)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_INSTR_RETIRED, BOGUSTAG),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_UOPS_RETIRED] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_UOPS_RETIRED),
		.escr_msr	= अणु MSR_P4_CRU_ESCR0, MSR_P4_CRU_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_UOPS_RETIRED, NBOGUS)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_UOPS_RETIRED, BOGUS),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_UOP_TYPE] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_UOP_TYPE),
		.escr_msr	= अणु MSR_P4_RAT_ESCR0, MSR_P4_RAT_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_UOP_TYPE, TAGLOADS)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_UOP_TYPE, TAGSTORES),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_BRANCH_RETIRED] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_BRANCH_RETIRED),
		.escr_msr	= अणु MSR_P4_CRU_ESCR2, MSR_P4_CRU_ESCR3 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_BRANCH_RETIRED, MMNP)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BRANCH_RETIRED, MMNM)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BRANCH_RETIRED, MMTP)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_BRANCH_RETIRED, MMTM),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_MISPRED_BRANCH_RETIRED] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_MISPRED_BRANCH_RETIRED),
		.escr_msr	= अणु MSR_P4_CRU_ESCR0, MSR_P4_CRU_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_MISPRED_BRANCH_RETIRED, NBOGUS),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_X87_ASSIST] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_X87_ASSIST),
		.escr_msr	= अणु MSR_P4_CRU_ESCR2, MSR_P4_CRU_ESCR3 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_X87_ASSIST, FPSU)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_X87_ASSIST, FPSO)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_X87_ASSIST, POAO)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_X87_ASSIST, POAU)			|
			P4_ESCR_EMASK_BIT(P4_EVENT_X87_ASSIST, PREA),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_MACHINE_CLEAR] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_MACHINE_CLEAR),
		.escr_msr	= अणु MSR_P4_CRU_ESCR2, MSR_P4_CRU_ESCR3 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_MACHINE_CLEAR, CLEAR)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_MACHINE_CLEAR, MOCLEAR)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_MACHINE_CLEAR, SMCLEAR),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
	[P4_EVENT_INSTR_COMPLETED] = अणु
		.opcode		= P4_OPCODE(P4_EVENT_INSTR_COMPLETED),
		.escr_msr	= अणु MSR_P4_CRU_ESCR0, MSR_P4_CRU_ESCR1 पूर्ण,
		.escr_emask	=
			P4_ESCR_EMASK_BIT(P4_EVENT_INSTR_COMPLETED, NBOGUS)		|
			P4_ESCR_EMASK_BIT(P4_EVENT_INSTR_COMPLETED, BOGUS),
		.cntr		= अणु अणु12, 13, 16पूर्ण, अणु14, 15, 17पूर्ण पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा P4_GEN_CACHE_EVENT(event, bit, metric)				  \
	p4_config_pack_escr(P4_ESCR_EVENT(event)			| \
			    P4_ESCR_EMASK_BIT(event, bit))		| \
	p4_config_pack_cccr(metric					| \
			    P4_CCCR_ESEL(P4_OPCODE_ESEL(P4_OPCODE(event))))

अटल __initस्थिर स्थिर u64 p4_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_REPLAY_EVENT, NBOGUS,
						P4_PEBS_METRIC__1stl_cache_load_miss_retired),
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_REPLAY_EVENT, NBOGUS,
						P4_PEBS_METRIC__2ndl_cache_load_miss_retired),
	पूर्ण,
पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_REPLAY_EVENT, NBOGUS,
						P4_PEBS_METRIC__dtlb_load_miss_retired),
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_REPLAY_EVENT, NBOGUS,
						P4_PEBS_METRIC__dtlb_store_miss_retired),
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = P4_GEN_CACHE_EVENT(P4_EVENT_ITLB_REFERENCE, HIT,
						P4_PEBS_METRIC__none),
		[ C(RESULT_MISS)   ] = P4_GEN_CACHE_EVENT(P4_EVENT_ITLB_REFERENCE, MISS,
						P4_PEBS_METRIC__none),
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
पूर्ण;

/*
 * Because of Netburst being quite restricted in how many
 * identical events may run simultaneously, we पूर्णांकroduce event aliases,
 * ie the dअगरferent events which have the same functionality but
 * utilize non-पूर्णांकersected resources (ESCR/CCCR/counter रेजिस्टरs).
 *
 * This allow us to relax restrictions a bit and run two or more
 * identical events together.
 *
 * Never set any custom पूर्णांकernal bits such as P4_CONFIG_HT,
 * P4_CONFIG_ALIASABLE or bits क्रम P4_PEBS_METRIC, they are
 * either up to date स्वतःmatically or not applicable at all.
 */
अटल काष्ठा p4_event_alias अणु
	u64 original;
	u64 alternative;
पूर्ण p4_event_aliases[] = अणु
	अणु
		/*
		 * Non-halted cycles can be substituted with non-sleeping cycles (see
		 * Intel SDM Vol3b क्रम details). We need this alias to be able
		 * to run nmi-watchकरोg and 'perf top' (or any other user space tool
		 * which is पूर्णांकerested in running PERF_COUNT_HW_CPU_CYCLES)
		 * simultaneously.
		 */
	.original	=
		p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_GLOBAL_POWER_EVENTS)		|
				    P4_ESCR_EMASK_BIT(P4_EVENT_GLOBAL_POWER_EVENTS, RUNNING)),
	.alternative	=
		p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_EXECUTION_EVENT)		|
				    P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS0)|
				    P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS1)|
				    P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS2)|
				    P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, NBOGUS3)|
				    P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS0)	|
				    P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS1)	|
				    P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS2)	|
				    P4_ESCR_EMASK_BIT(P4_EVENT_EXECUTION_EVENT, BOGUS3))|
		p4_config_pack_cccr(P4_CCCR_THRESHOLD(15) | P4_CCCR_COMPLEMENT		|
				    P4_CCCR_COMPARE),
	पूर्ण,
पूर्ण;

अटल u64 p4_get_alias_event(u64 config)
अणु
	u64 config_match;
	पूर्णांक i;

	/*
	 * Only event with special mark is allowed,
	 * we're to be sure it didn't come as malक्रमmed
	 * RAW event.
	 */
	अगर (!(config & P4_CONFIG_ALIASABLE))
		वापस 0;

	config_match = config & P4_CONFIG_EVENT_ALIAS_MASK;

	क्रम (i = 0; i < ARRAY_SIZE(p4_event_aliases); i++) अणु
		अगर (config_match == p4_event_aliases[i].original) अणु
			config_match = p4_event_aliases[i].alternative;
			अवरोध;
		पूर्ण अन्यथा अगर (config_match == p4_event_aliases[i].alternative) अणु
			config_match = p4_event_aliases[i].original;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= ARRAY_SIZE(p4_event_aliases))
		वापस 0;

	वापस config_match | (config & P4_CONFIG_EVENT_ALIAS_IMMUTABLE_BITS);
पूर्ण

अटल u64 p4_general_events[PERF_COUNT_HW_MAX] = अणु
  /* non-halted CPU घड़ीs */
  [PERF_COUNT_HW_CPU_CYCLES] =
	p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_GLOBAL_POWER_EVENTS)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_GLOBAL_POWER_EVENTS, RUNNING))	|
		P4_CONFIG_ALIASABLE,

  /*
   * retired inकाष्ठाions
   * in a sake of simplicity we करोn't use the FSB tagging
   */
  [PERF_COUNT_HW_INSTRUCTIONS] =
	p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_INSTR_RETIRED)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_INSTR_RETIRED, NBOGUSNTAG)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_INSTR_RETIRED, BOGUSNTAG)),

  /* cache hits */
  [PERF_COUNT_HW_CACHE_REFERENCES] =
	p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_BSQ_CACHE_REFERENCE)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITS)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITE)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITM)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITS)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITE)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITM)),

  /* cache misses */
  [PERF_COUNT_HW_CACHE_MISSES] =
	p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_BSQ_CACHE_REFERENCE)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_MISS)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_MISS)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_BSQ_CACHE_REFERENCE, WR_2ndL_MISS)),

  /* branch inकाष्ठाions retired */
  [PERF_COUNT_HW_BRANCH_INSTRUCTIONS] =
	p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_RETIRED_BRANCH_TYPE)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_BRANCH_TYPE, CONDITIONAL)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_BRANCH_TYPE, CALL)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_BRANCH_TYPE, RETURN)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_RETIRED_BRANCH_TYPE, INसूचीECT)),

  /* mispredicted branches retired */
  [PERF_COUNT_HW_BRANCH_MISSES]	=
	p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_MISPRED_BRANCH_RETIRED)	|
		P4_ESCR_EMASK_BIT(P4_EVENT_MISPRED_BRANCH_RETIRED, NBOGUS)),

  /* bus पढ़ोy घड़ीs (cpu is driving #DRDY_DRV\#DRDY_OWN):  */
  [PERF_COUNT_HW_BUS_CYCLES] =
	p4_config_pack_escr(P4_ESCR_EVENT(P4_EVENT_FSB_DATA_ACTIVITY)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DRDY_DRV)		|
		P4_ESCR_EMASK_BIT(P4_EVENT_FSB_DATA_ACTIVITY, DRDY_OWN))	|
	p4_config_pack_cccr(P4_CCCR_EDGE | P4_CCCR_COMPARE),
पूर्ण;

अटल काष्ठा p4_event_bind *p4_config_get_bind(u64 config)
अणु
	अचिन्हित पूर्णांक evnt = p4_config_unpack_event(config);
	काष्ठा p4_event_bind *bind = शून्य;

	अगर (evnt < ARRAY_SIZE(p4_event_bind_map))
		bind = &p4_event_bind_map[evnt];

	वापस bind;
पूर्ण

अटल u64 p4_pmu_event_map(पूर्णांक hw_event)
अणु
	काष्ठा p4_event_bind *bind;
	अचिन्हित पूर्णांक esel;
	u64 config;

	config = p4_general_events[hw_event];
	bind = p4_config_get_bind(config);
	esel = P4_OPCODE_ESEL(bind->opcode);
	config |= p4_config_pack_cccr(P4_CCCR_ESEL(esel));

	वापस config;
पूर्ण

/* check cpu model specअगरics */
अटल bool p4_event_match_cpu_model(अचिन्हित पूर्णांक event_idx)
अणु
	/* INSTR_COMPLETED event only exist क्रम model 3, 4, 6 (Prescott) */
	अगर (event_idx == P4_EVENT_INSTR_COMPLETED) अणु
		अगर (boot_cpu_data.x86_model != 3 &&
			boot_cpu_data.x86_model != 4 &&
			boot_cpu_data.x86_model != 6)
			वापस false;
	पूर्ण

	/*
	 * For info
	 * - IQ_ESCR0, IQ_ESCR1 only क्रम models 1 and 2
	 */

	वापस true;
पूर्ण

अटल पूर्णांक p4_validate_raw_event(काष्ठा perf_event *event)
अणु
	अचिन्हित पूर्णांक v, emask;

	/* User data may have out-of-bound event index */
	v = p4_config_unpack_event(event->attr.config);
	अगर (v >= ARRAY_SIZE(p4_event_bind_map))
		वापस -EINVAL;

	/* It may be unsupported: */
	अगर (!p4_event_match_cpu_model(v))
		वापस -EINVAL;

	/*
	 * NOTE: P4_CCCR_THREAD_ANY has not the same meaning as
	 * in Architectural Perक्रमmance Monitoring, it means not
	 * on _which_ logical cpu to count but rather _when_, ie it
	 * depends on logical cpu state -- count event अगर one cpu active,
	 * none, both or any, so we just allow user to pass any value
	 * desired.
	 *
	 * In turn we always set Tx_OS/Tx_USR bits bound to logical
	 * cpu without their propagation to another cpu
	 */

	/*
	 * अगर an event is shared across the logical thपढ़ोs
	 * the user needs special permissions to be able to use it
	 */
	अगर (p4_ht_active() && p4_event_bind_map[v].shared) अणु
		v = perf_allow_cpu(&event->attr);
		अगर (v)
			वापस v;
	पूर्ण

	/* ESCR EventMask bits may be invalid */
	emask = p4_config_unpack_escr(event->attr.config) & P4_ESCR_EVENTMASK_MASK;
	अगर (emask & ~p4_event_bind_map[v].escr_emask)
		वापस -EINVAL;

	/*
	 * it may have some invalid PEBS bits
	 */
	अगर (p4_config_pebs_has(event->attr.config, P4_PEBS_CONFIG_ENABLE))
		वापस -EINVAL;

	v = p4_config_unpack_metric(event->attr.config);
	अगर (v >= ARRAY_SIZE(p4_pebs_bind_map))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक p4_hw_config(काष्ठा perf_event *event)
अणु
	पूर्णांक cpu = get_cpu();
	पूर्णांक rc = 0;
	u32 escr, cccr;

	/*
	 * the reason we use cpu that early is that: अगर we get scheduled
	 * first समय on the same cpu -- we will not need swap thपढ़ो
	 * specअगरic flags in config (and will save some cpu cycles)
	 */

	cccr = p4_शेष_cccr_conf(cpu);
	escr = p4_शेष_escr_conf(cpu, event->attr.exclude_kernel,
					 event->attr.exclude_user);
	event->hw.config = p4_config_pack_escr(escr) |
			   p4_config_pack_cccr(cccr);

	अगर (p4_ht_active() && p4_ht_thपढ़ो(cpu))
		event->hw.config = p4_set_ht_bit(event->hw.config);

	अगर (event->attr.type == PERF_TYPE_RAW) अणु
		काष्ठा p4_event_bind *bind;
		अचिन्हित पूर्णांक esel;
		/*
		 * Clear bits we reserve to be managed by kernel itself
		 * and never allowed from a user space
		 */
		event->attr.config &= P4_CONFIG_MASK;

		rc = p4_validate_raw_event(event);
		अगर (rc)
			जाओ out;

		/*
		 * Note that क्रम RAW events we allow user to use P4_CCCR_RESERVED
		 * bits since we keep additional info here (क्रम cache events and etc)
		 */
		event->hw.config |= event->attr.config;
		bind = p4_config_get_bind(event->attr.config);
		अगर (!bind) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		esel = P4_OPCODE_ESEL(bind->opcode);
		event->hw.config |= p4_config_pack_cccr(P4_CCCR_ESEL(esel));
	पूर्ण

	rc = x86_setup_perfctr(event);
out:
	put_cpu();
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक p4_pmu_clear_cccr_ovf(काष्ठा hw_perf_event *hwc)
अणु
	u64 v;

	/* an official way क्रम overflow indication */
	rdmsrl(hwc->config_base, v);
	अगर (v & P4_CCCR_OVF) अणु
		wrmsrl(hwc->config_base, v & ~P4_CCCR_OVF);
		वापस 1;
	पूर्ण

	/*
	 * In some circumstances the overflow might issue an NMI but did
	 * not set P4_CCCR_OVF bit. Because a counter holds a negative value
	 * we simply check क्रम high bit being set, अगर it's cleared it means
	 * the counter has reached zero value and जारीd counting beक्रमe
	 * real NMI संकेत was received:
	 */
	rdmsrl(hwc->event_base, v);
	अगर (!(v & ARCH_P4_UNFLAGGED_BIT))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम p4_pmu_disable_pebs(व्योम)
अणु
	/*
	 * FIXME
	 *
	 * It's still allowed that two thपढ़ोs setup same cache
	 * events so we can't simply clear metrics until we knew
	 * no one is depending on us, so we need kind of counter
	 * क्रम "ReplayEvent" users.
	 *
	 * What is more complex -- RAW events, अगर user (क्रम some
	 * reason) will pass some cache event metric with improper
	 * event opcode -- it's fine from hardware poपूर्णांक of view
	 * but completely nonsense from "meaning" of such action.
	 *
	 * So at moment let leave metrics turned on क्रमever -- it's
	 * ok क्रम now but need to be revisited!
	 *
	 * (व्योम)wrmsrl_safe(MSR_IA32_PEBS_ENABLE, 0);
	 * (व्योम)wrmsrl_safe(MSR_P4_PEBS_MATRIX_VERT, 0);
	 */
पूर्ण

अटल अंतरभूत व्योम p4_pmu_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	/*
	 * If event माला_लो disabled जबतक counter is in overflowed
	 * state we need to clear P4_CCCR_OVF, otherwise पूर्णांकerrupt get
	 * निश्चितed again and again
	 */
	(व्योम)wrmsrl_safe(hwc->config_base,
		p4_config_unpack_cccr(hwc->config) & ~P4_CCCR_ENABLE & ~P4_CCCR_OVF & ~P4_CCCR_RESERVED);
पूर्ण

अटल व्योम p4_pmu_disable_all(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx;

	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++) अणु
		काष्ठा perf_event *event = cpuc->events[idx];
		अगर (!test_bit(idx, cpuc->active_mask))
			जारी;
		p4_pmu_disable_event(event);
	पूर्ण

	p4_pmu_disable_pebs();
पूर्ण

/* configuration must be valid */
अटल व्योम p4_pmu_enable_pebs(u64 config)
अणु
	काष्ठा p4_pebs_bind *bind;
	अचिन्हित पूर्णांक idx;

	BUILD_BUG_ON(P4_PEBS_METRIC__max > P4_PEBS_CONFIG_METRIC_MASK);

	idx = p4_config_unpack_metric(config);
	अगर (idx == P4_PEBS_METRIC__none)
		वापस;

	bind = &p4_pebs_bind_map[idx];

	(व्योम)wrmsrl_safe(MSR_IA32_PEBS_ENABLE,	(u64)bind->metric_pebs);
	(व्योम)wrmsrl_safe(MSR_P4_PEBS_MATRIX_VERT,	(u64)bind->metric_vert);
पूर्ण

अटल व्योम __p4_pmu_enable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक thपढ़ो = p4_ht_config_thपढ़ो(hwc->config);
	u64 escr_conf = p4_config_unpack_escr(p4_clear_ht_bit(hwc->config));
	अचिन्हित पूर्णांक idx = p4_config_unpack_event(hwc->config);
	काष्ठा p4_event_bind *bind;
	u64 escr_addr, cccr;

	bind = &p4_event_bind_map[idx];
	escr_addr = bind->escr_msr[thपढ़ो];

	/*
	 * - we करोnt support cascaded counters yet
	 * - and counter 1 is broken (erratum)
	 */
	WARN_ON_ONCE(p4_is_event_cascaded(hwc->config));
	WARN_ON_ONCE(hwc->idx == 1);

	/* we need a real Event value */
	escr_conf &= ~P4_ESCR_EVENT_MASK;
	escr_conf |= P4_ESCR_EVENT(P4_OPCODE_EVNT(bind->opcode));

	cccr = p4_config_unpack_cccr(hwc->config);

	/*
	 * it could be Cache event so we need to ग_लिखो metrics
	 * पूर्णांकo additional MSRs
	 */
	p4_pmu_enable_pebs(hwc->config);

	(व्योम)wrmsrl_safe(escr_addr, escr_conf);
	(व्योम)wrmsrl_safe(hwc->config_base,
				(cccr & ~P4_CCCR_RESERVED) | P4_CCCR_ENABLE);
पूर्ण

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ [BITS_TO_LONGS(X86_PMC_IDX_MAX)], p4_running);

अटल व्योम p4_pmu_enable_event(काष्ठा perf_event *event)
अणु
	पूर्णांक idx = event->hw.idx;

	__set_bit(idx, per_cpu(p4_running, smp_processor_id()));
	__p4_pmu_enable_event(event);
पूर्ण

अटल व्योम p4_pmu_enable_all(पूर्णांक added)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx;

	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++) अणु
		काष्ठा perf_event *event = cpuc->events[idx];
		अगर (!test_bit(idx, cpuc->active_mask))
			जारी;
		__p4_pmu_enable_event(event);
	पूर्ण
पूर्ण

अटल पूर्णांक p4_pmu_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा cpu_hw_events *cpuc;
	काष्ठा perf_event *event;
	काष्ठा hw_perf_event *hwc;
	पूर्णांक idx, handled = 0;
	u64 val;

	cpuc = this_cpu_ptr(&cpu_hw_events);

	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++) अणु
		पूर्णांक overflow;

		अगर (!test_bit(idx, cpuc->active_mask)) अणु
			/* catch in-flight IRQs */
			अगर (__test_and_clear_bit(idx, per_cpu(p4_running, smp_processor_id())))
				handled++;
			जारी;
		पूर्ण

		event = cpuc->events[idx];
		hwc = &event->hw;

		WARN_ON_ONCE(hwc->idx != idx);

		/* it might be unflagged overflow */
		overflow = p4_pmu_clear_cccr_ovf(hwc);

		val = x86_perf_event_update(event);
		अगर (!overflow && (val & (1ULL << (x86_pmu.cntval_bits - 1))))
			जारी;

		handled += overflow;

		/* event overflow क्रम sure */
		perf_sample_data_init(&data, 0, hwc->last_period);

		अगर (!x86_perf_event_set_period(event))
			जारी;


		अगर (perf_event_overflow(event, &data, regs))
			x86_pmu_stop(event, 0);
	पूर्ण

	अगर (handled)
		inc_irq_stat(apic_perf_irqs);

	/*
	 * When dealing with the unmasking of the LVTPC on P4 perf hw, it has
	 * been observed that the OVF bit flag has to be cleared first _beक्रमe_
	 * the LVTPC can be unmasked.
	 *
	 * The reason is the NMI line will जारी to be निश्चितed जबतक the OVF
	 * bit is set.  This causes a second NMI to generate अगर the LVTPC is
	 * unmasked beक्रमe the OVF bit is cleared, leading to unknown NMI
	 * messages.
	 */
	apic_ग_लिखो(APIC_LVTPC, APIC_DM_NMI);

	वापस handled;
पूर्ण

/*
 * swap thपढ़ो specअगरic fields according to a thपढ़ो
 * we are going to run on
 */
अटल व्योम p4_pmu_swap_config_ts(काष्ठा hw_perf_event *hwc, पूर्णांक cpu)
अणु
	u32 escr, cccr;

	/*
	 * we either lucky and जारी on same cpu or no HT support
	 */
	अगर (!p4_should_swap_ts(hwc->config, cpu))
		वापस;

	/*
	 * the event is migrated from an another logical
	 * cpu, so we need to swap thपढ़ो specअगरic flags
	 */

	escr = p4_config_unpack_escr(hwc->config);
	cccr = p4_config_unpack_cccr(hwc->config);

	अगर (p4_ht_thपढ़ो(cpu)) अणु
		cccr &= ~P4_CCCR_OVF_PMI_T0;
		cccr |= P4_CCCR_OVF_PMI_T1;
		अगर (escr & P4_ESCR_T0_OS) अणु
			escr &= ~P4_ESCR_T0_OS;
			escr |= P4_ESCR_T1_OS;
		पूर्ण
		अगर (escr & P4_ESCR_T0_USR) अणु
			escr &= ~P4_ESCR_T0_USR;
			escr |= P4_ESCR_T1_USR;
		पूर्ण
		hwc->config  = p4_config_pack_escr(escr);
		hwc->config |= p4_config_pack_cccr(cccr);
		hwc->config |= P4_CONFIG_HT;
	पूर्ण अन्यथा अणु
		cccr &= ~P4_CCCR_OVF_PMI_T1;
		cccr |= P4_CCCR_OVF_PMI_T0;
		अगर (escr & P4_ESCR_T1_OS) अणु
			escr &= ~P4_ESCR_T1_OS;
			escr |= P4_ESCR_T0_OS;
		पूर्ण
		अगर (escr & P4_ESCR_T1_USR) अणु
			escr &= ~P4_ESCR_T1_USR;
			escr |= P4_ESCR_T0_USR;
		पूर्ण
		hwc->config  = p4_config_pack_escr(escr);
		hwc->config |= p4_config_pack_cccr(cccr);
		hwc->config &= ~P4_CONFIG_HT;
	पूर्ण
पूर्ण

/*
 * ESCR address hashing is tricky, ESCRs are not sequential
 * in memory but all starts from MSR_P4_BSU_ESCR0 (0x03a0) and
 * the metric between any ESCRs is laid in range [0xa0,0xe1]
 *
 * so we make ~70% filled hashtable
 */

#घोषणा P4_ESCR_MSR_BASE		0x000003a0
#घोषणा P4_ESCR_MSR_MAX			0x000003e1
#घोषणा P4_ESCR_MSR_TABLE_SIZE		(P4_ESCR_MSR_MAX - P4_ESCR_MSR_BASE + 1)
#घोषणा P4_ESCR_MSR_IDX(msr)		(msr - P4_ESCR_MSR_BASE)
#घोषणा P4_ESCR_MSR_TABLE_ENTRY(msr)	[P4_ESCR_MSR_IDX(msr)] = msr

अटल स्थिर अचिन्हित पूर्णांक p4_escr_table[P4_ESCR_MSR_TABLE_SIZE] = अणु
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_ALF_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_ALF_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_BPU_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_BPU_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_BSU_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_BSU_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_CRU_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_CRU_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_CRU_ESCR2),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_CRU_ESCR3),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_CRU_ESCR4),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_CRU_ESCR5),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_DAC_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_DAC_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_FIRM_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_FIRM_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_FLAME_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_FLAME_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_FSB_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_FSB_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_IQ_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_IQ_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_IS_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_IS_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_ITLB_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_ITLB_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_IX_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_IX_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_MOB_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_MOB_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_MS_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_MS_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_PMH_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_PMH_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_RAT_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_RAT_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_SAAT_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_SAAT_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_SSU_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_SSU_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_TBPU_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_TBPU_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_TC_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_TC_ESCR1),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_U2L_ESCR0),
	P4_ESCR_MSR_TABLE_ENTRY(MSR_P4_U2L_ESCR1),
पूर्ण;

अटल पूर्णांक p4_get_escr_idx(अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक idx = P4_ESCR_MSR_IDX(addr);

	अगर (unlikely(idx >= P4_ESCR_MSR_TABLE_SIZE	||
			!p4_escr_table[idx]		||
			p4_escr_table[idx] != addr)) अणु
		WARN_ONCE(1, "P4 PMU: Wrong address passed: %x\n", addr);
		वापस -1;
	पूर्ण

	वापस idx;
पूर्ण

अटल पूर्णांक p4_next_cntr(पूर्णांक thपढ़ो, अचिन्हित दीर्घ *used_mask,
			काष्ठा p4_event_bind *bind)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < P4_CNTR_LIMIT; i++) अणु
		j = bind->cntr[thपढ़ो][i];
		अगर (j != -1 && !test_bit(j, used_mask))
			वापस j;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक p4_pmu_schedule_events(काष्ठा cpu_hw_events *cpuc, पूर्णांक n, पूर्णांक *assign)
अणु
	अचिन्हित दीर्घ used_mask[BITS_TO_LONGS(X86_PMC_IDX_MAX)];
	अचिन्हित दीर्घ escr_mask[BITS_TO_LONGS(P4_ESCR_MSR_TABLE_SIZE)];
	पूर्णांक cpu = smp_processor_id();
	काष्ठा hw_perf_event *hwc;
	काष्ठा p4_event_bind *bind;
	अचिन्हित पूर्णांक i, thपढ़ो, num;
	पूर्णांक cntr_idx, escr_idx;
	u64 config_alias;
	पूर्णांक pass;

	biपंचांगap_zero(used_mask, X86_PMC_IDX_MAX);
	biपंचांगap_zero(escr_mask, P4_ESCR_MSR_TABLE_SIZE);

	क्रम (i = 0, num = n; i < n; i++, num--) अणु

		hwc = &cpuc->event_list[i]->hw;
		thपढ़ो = p4_ht_thपढ़ो(cpu);
		pass = 0;

again:
		/*
		 * It's possible to hit a circular lock
		 * between original and alternative events
		 * अगर both are scheduled alपढ़ोy.
		 */
		अगर (pass > 2)
			जाओ करोne;

		bind = p4_config_get_bind(hwc->config);
		escr_idx = p4_get_escr_idx(bind->escr_msr[thपढ़ो]);
		अगर (unlikely(escr_idx == -1))
			जाओ करोne;

		अगर (hwc->idx != -1 && !p4_should_swap_ts(hwc->config, cpu)) अणु
			cntr_idx = hwc->idx;
			अगर (assign)
				assign[i] = hwc->idx;
			जाओ reserve;
		पूर्ण

		cntr_idx = p4_next_cntr(thपढ़ो, used_mask, bind);
		अगर (cntr_idx == -1 || test_bit(escr_idx, escr_mask)) अणु
			/*
			 * Check whether an event alias is still available.
			 */
			config_alias = p4_get_alias_event(hwc->config);
			अगर (!config_alias)
				जाओ करोne;
			hwc->config = config_alias;
			pass++;
			जाओ again;
		पूर्ण
		/*
		 * Perf करोes test runs to see अगर a whole group can be asचिन्हित
		 * together successfully.  There can be multiple rounds of this.
		 * Unक्रमtunately, p4_pmu_swap_config_ts touches the hwc->config
		 * bits, such that the next round of group assignments will
		 * cause the above p4_should_swap_ts to pass instead of fail.
		 * This leads to counters exclusive to thपढ़ो0 being used by
		 * thपढ़ो1.
		 *
		 * Solve this with a cheap hack, reset the idx back to -1 to
		 * क्रमce a new lookup (p4_next_cntr) to get the right counter
		 * क्रम the right thपढ़ो.
		 *
		 * This probably करोesn't comply with the general spirit of how
		 * perf wants to work, but P4 is special. :-(
		 */
		अगर (p4_should_swap_ts(hwc->config, cpu))
			hwc->idx = -1;
		p4_pmu_swap_config_ts(hwc, cpu);
		अगर (assign)
			assign[i] = cntr_idx;
reserve:
		set_bit(cntr_idx, used_mask);
		set_bit(escr_idx, escr_mask);
	पूर्ण

करोne:
	वापस num ? -EINVAL : 0;
पूर्ण

PMU_FORMAT_ATTR(cccr, "config:0-31" );
PMU_FORMAT_ATTR(escr, "config:32-62");
PMU_FORMAT_ATTR(ht,   "config:63"   );

अटल काष्ठा attribute *पूर्णांकel_p4_क्रमmats_attr[] = अणु
	&क्रमmat_attr_cccr.attr,
	&क्रमmat_attr_escr.attr,
	&क्रमmat_attr_ht.attr,
	शून्य,
पूर्ण;

अटल __initस्थिर स्थिर काष्ठा x86_pmu p4_pmu = अणु
	.name			= "Netburst P4/Xeon",
	.handle_irq		= p4_pmu_handle_irq,
	.disable_all		= p4_pmu_disable_all,
	.enable_all		= p4_pmu_enable_all,
	.enable			= p4_pmu_enable_event,
	.disable		= p4_pmu_disable_event,
	.eventsel		= MSR_P4_BPU_CCCR0,
	.perfctr		= MSR_P4_BPU_PERFCTR0,
	.event_map		= p4_pmu_event_map,
	.max_events		= ARRAY_SIZE(p4_general_events),
	.get_event_स्थिरraपूर्णांकs	= x86_get_event_स्थिरraपूर्णांकs,
	/*
	 * IF HT disabled we may need to use all
	 * ARCH_P4_MAX_CCCR counters simultaneously
	 * though leave it restricted at moment assuming
	 * HT is on
	 */
	.num_counters		= ARCH_P4_MAX_CCCR,
	.apic			= 1,
	.cntval_bits		= ARCH_P4_CNTRVAL_BITS,
	.cntval_mask		= ARCH_P4_CNTRVAL_MASK,
	.max_period		= (1ULL << (ARCH_P4_CNTRVAL_BITS - 1)) - 1,
	.hw_config		= p4_hw_config,
	.schedule_events	= p4_pmu_schedule_events,
	/*
	 * This handles erratum N15 in पूर्णांकel करोc 249199-029,
	 * the counter may not be updated correctly on ग_लिखो
	 * so we need a second ग_लिखो operation to करो the trick
	 * (the official workaround didn't work)
	 *
	 * the क्रमmer idea is taken from OProfile code
	 */
	.perfctr_second_ग_लिखो	= 1,

	.क्रमmat_attrs		= पूर्णांकel_p4_क्रमmats_attr,
पूर्ण;

__init पूर्णांक p4_pmu_init(व्योम)
अणु
	अचिन्हित पूर्णांक low, high;
	पूर्णांक i, reg;

	/* If we get stripped -- indexing fails */
	BUILD_BUG_ON(ARCH_P4_MAX_CCCR > INTEL_PMC_MAX_GENERIC);

	rdmsr(MSR_IA32_MISC_ENABLE, low, high);
	अगर (!(low & (1 << 7))) अणु
		pr_cont("unsupported Netburst CPU model %d ",
			boot_cpu_data.x86_model);
		वापस -ENODEV;
	पूर्ण

	स_नकल(hw_cache_event_ids, p4_hw_cache_event_ids,
		माप(hw_cache_event_ids));

	pr_cont("Netburst events, ");

	x86_pmu = p4_pmu;

	/*
	 * Even though the counters are configured to पूर्णांकerrupt a particular
	 * logical processor when an overflow happens, testing has shown that
	 * on kdump kernels (which uses a single cpu), thपढ़ो1's counter
	 * जारीs to run and will report an NMI on thपढ़ो0.  Due to the
	 * overflow bug, this leads to a stream of unknown NMIs.
	 *
	 * Solve this by zero'ing out the रेजिस्टरs to mimic a reset.
	 */
	क्रम (i = 0; i < x86_pmu.num_counters; i++) अणु
		reg = x86_pmu_config_addr(i);
		wrmsrl_safe(reg, 0ULL);
	पूर्ण

	वापस 0;
पूर्ण
