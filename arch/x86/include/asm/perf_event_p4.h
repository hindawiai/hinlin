<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Netburst Perक्रमmance Events (P4, old Xeon)
 */

#अगर_अघोषित PERF_EVENT_P4_H
#घोषणा PERF_EVENT_P4_H

#समावेश <linux/cpu.h>
#समावेश <linux/bitops.h>

/*
 * NetBurst has perक्रमmance MSRs shared between
 * thपढ़ोs अगर HT is turned on, ie क्रम both logical
 * processors (mem: in turn in Atom with HT support
 * perf-MSRs are not shared and every thपढ़ो has its
 * own perf-MSRs set)
 */
#घोषणा ARCH_P4_TOTAL_ESCR	(46)
#घोषणा ARCH_P4_RESERVED_ESCR	(2) /* IQ_ESCR(0,1) not always present */
#घोषणा ARCH_P4_MAX_ESCR	(ARCH_P4_TOTAL_ESCR - ARCH_P4_RESERVED_ESCR)
#घोषणा ARCH_P4_MAX_CCCR	(18)

#घोषणा ARCH_P4_CNTRVAL_BITS	(40)
#घोषणा ARCH_P4_CNTRVAL_MASK	((1ULL << ARCH_P4_CNTRVAL_BITS) - 1)
#घोषणा ARCH_P4_UNFLAGGED_BIT	((1ULL) << (ARCH_P4_CNTRVAL_BITS - 1))

#घोषणा P4_ESCR_EVENT_MASK	0x7e000000ULL
#घोषणा P4_ESCR_EVENT_SHIFT	25
#घोषणा P4_ESCR_EVENTMASK_MASK	0x01fffe00ULL
#घोषणा P4_ESCR_EVENTMASK_SHIFT	9
#घोषणा P4_ESCR_TAG_MASK	0x000001e0ULL
#घोषणा P4_ESCR_TAG_SHIFT	5
#घोषणा P4_ESCR_TAG_ENABLE	0x00000010ULL
#घोषणा P4_ESCR_T0_OS		0x00000008ULL
#घोषणा P4_ESCR_T0_USR		0x00000004ULL
#घोषणा P4_ESCR_T1_OS		0x00000002ULL
#घोषणा P4_ESCR_T1_USR		0x00000001ULL

#घोषणा P4_ESCR_EVENT(v)	((v) << P4_ESCR_EVENT_SHIFT)
#घोषणा P4_ESCR_EMASK(v)	((v) << P4_ESCR_EVENTMASK_SHIFT)
#घोषणा P4_ESCR_TAG(v)		((v) << P4_ESCR_TAG_SHIFT)

#घोषणा P4_CCCR_OVF			0x80000000ULL
#घोषणा P4_CCCR_CASCADE			0x40000000ULL
#घोषणा P4_CCCR_OVF_PMI_T0		0x04000000ULL
#घोषणा P4_CCCR_OVF_PMI_T1		0x08000000ULL
#घोषणा P4_CCCR_FORCE_OVF		0x02000000ULL
#घोषणा P4_CCCR_EDGE			0x01000000ULL
#घोषणा P4_CCCR_THRESHOLD_MASK		0x00f00000ULL
#घोषणा P4_CCCR_THRESHOLD_SHIFT		20
#घोषणा P4_CCCR_COMPLEMENT		0x00080000ULL
#घोषणा P4_CCCR_COMPARE			0x00040000ULL
#घोषणा P4_CCCR_ESCR_SELECT_MASK	0x0000e000ULL
#घोषणा P4_CCCR_ESCR_SELECT_SHIFT	13
#घोषणा P4_CCCR_ENABLE			0x00001000ULL
#घोषणा P4_CCCR_THREAD_SINGLE		0x00010000ULL
#घोषणा P4_CCCR_THREAD_BOTH		0x00020000ULL
#घोषणा P4_CCCR_THREAD_ANY		0x00030000ULL
#घोषणा P4_CCCR_RESERVED		0x00000fffULL

#घोषणा P4_CCCR_THRESHOLD(v)		((v) << P4_CCCR_THRESHOLD_SHIFT)
#घोषणा P4_CCCR_ESEL(v)			((v) << P4_CCCR_ESCR_SELECT_SHIFT)

#घोषणा P4_GEN_ESCR_EMASK(class, name, bit)	\
	class##__##name = ((1ULL << bit) << P4_ESCR_EVENTMASK_SHIFT)
#घोषणा P4_ESCR_EMASK_BIT(class, name)		class##__##name

/*
 * config field is 64bit width and consists of
 * HT << 63 | ESCR << 32 | CCCR
 * where HT is HyperThपढ़ोing bit (since ESCR
 * has it reserved we may use it क्रम own purpose)
 *
 * note that this is NOT the addresses of respective
 * ESCR and CCCR but rather an only packed value should
 * be unpacked and written to a proper addresses
 *
 * the base idea is to pack as much info as possible
 */
#घोषणा p4_config_pack_escr(v)		(((u64)(v)) << 32)
#घोषणा p4_config_pack_cccr(v)		(((u64)(v)) & 0xffffffffULL)
#घोषणा p4_config_unpack_escr(v)	(((u64)(v)) >> 32)
#घोषणा p4_config_unpack_cccr(v)	(((u64)(v)) & 0xffffffffULL)

#घोषणा p4_config_unpack_emask(v)			\
	(अणु						\
		u32 t = p4_config_unpack_escr((v));	\
		t = t &  P4_ESCR_EVENTMASK_MASK;	\
		t = t >> P4_ESCR_EVENTMASK_SHIFT;	\
		t;					\
	पूर्ण)

#घोषणा p4_config_unpack_event(v)			\
	(अणु						\
		u32 t = p4_config_unpack_escr((v));	\
		t = t &  P4_ESCR_EVENT_MASK;		\
		t = t >> P4_ESCR_EVENT_SHIFT;		\
		t;					\
	पूर्ण)

#घोषणा P4_CONFIG_HT_SHIFT		63
#घोषणा P4_CONFIG_HT			(1ULL << P4_CONFIG_HT_SHIFT)

/*
 * If an event has alias it should be marked
 * with a special bit. (Don't क्रमget to check
 * P4_PEBS_CONFIG_MASK and related bits on
 * modअगरication.)
 */
#घोषणा P4_CONFIG_ALIASABLE		(1ULL << 9)

/*
 * The bits we allow to pass क्रम RAW events
 */
#घोषणा P4_CONFIG_MASK_ESCR		\
	P4_ESCR_EVENT_MASK	|	\
	P4_ESCR_EVENTMASK_MASK	|	\
	P4_ESCR_TAG_MASK	|	\
	P4_ESCR_TAG_ENABLE

#घोषणा P4_CONFIG_MASK_CCCR		\
	P4_CCCR_EDGE		|	\
	P4_CCCR_THRESHOLD_MASK	|	\
	P4_CCCR_COMPLEMENT	|	\
	P4_CCCR_COMPARE		|	\
	P4_CCCR_THREAD_ANY	|	\
	P4_CCCR_RESERVED

/* some dangerous bits are reserved क्रम kernel पूर्णांकernals */
#घोषणा P4_CONFIG_MASK				  	  \
	(p4_config_pack_escr(P4_CONFIG_MASK_ESCR))	| \
	(p4_config_pack_cccr(P4_CONFIG_MASK_CCCR))

/*
 * In हाल of event aliasing we need to preserve some
 * caller bits, otherwise the mapping won't be complete.
 */
#घोषणा P4_CONFIG_EVENT_ALIAS_MASK			  \
	(p4_config_pack_escr(P4_CONFIG_MASK_ESCR)	| \
	 p4_config_pack_cccr(P4_CCCR_EDGE		| \
			     P4_CCCR_THRESHOLD_MASK	| \
			     P4_CCCR_COMPLEMENT		| \
			     P4_CCCR_COMPARE))

#घोषणा  P4_CONFIG_EVENT_ALIAS_IMMUTABLE_BITS		  \
	((P4_CONFIG_HT)					| \
	 p4_config_pack_escr(P4_ESCR_T0_OS		| \
			     P4_ESCR_T0_USR		| \
			     P4_ESCR_T1_OS		| \
			     P4_ESCR_T1_USR)		| \
	 p4_config_pack_cccr(P4_CCCR_OVF		| \
			     P4_CCCR_CASCADE		| \
			     P4_CCCR_FORCE_OVF		| \
			     P4_CCCR_THREAD_ANY		| \
			     P4_CCCR_OVF_PMI_T0		| \
			     P4_CCCR_OVF_PMI_T1		| \
			     P4_CONFIG_ALIASABLE))

अटल अंतरभूत bool p4_is_event_cascaded(u64 config)
अणु
	u32 cccr = p4_config_unpack_cccr(config);
	वापस !!(cccr & P4_CCCR_CASCADE);
पूर्ण

अटल अंतरभूत पूर्णांक p4_ht_config_thपढ़ो(u64 config)
अणु
	वापस !!(config & P4_CONFIG_HT);
पूर्ण

अटल अंतरभूत u64 p4_set_ht_bit(u64 config)
अणु
	वापस config | P4_CONFIG_HT;
पूर्ण

अटल अंतरभूत u64 p4_clear_ht_bit(u64 config)
अणु
	वापस config & ~P4_CONFIG_HT;
पूर्ण

अटल अंतरभूत पूर्णांक p4_ht_active(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	वापस smp_num_siblings > 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक p4_ht_thपढ़ो(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (smp_num_siblings == 2)
		वापस cpu != cpumask_first(this_cpu_cpumask_var_ptr(cpu_sibling_map));
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक p4_should_swap_ts(u64 config, पूर्णांक cpu)
अणु
	वापस p4_ht_config_thपढ़ो(config) ^ p4_ht_thपढ़ो(cpu);
पूर्ण

अटल अंतरभूत u32 p4_शेष_cccr_conf(पूर्णांक cpu)
अणु
	/*
	 * Note that P4_CCCR_THREAD_ANY is "required" on
	 * non-HT machines (on HT machines we count TS events
	 * regardless the state of second logical processor
	 */
	u32 cccr = P4_CCCR_THREAD_ANY;

	अगर (!p4_ht_thपढ़ो(cpu))
		cccr |= P4_CCCR_OVF_PMI_T0;
	अन्यथा
		cccr |= P4_CCCR_OVF_PMI_T1;

	वापस cccr;
पूर्ण

अटल अंतरभूत u32 p4_शेष_escr_conf(पूर्णांक cpu, पूर्णांक exclude_os, पूर्णांक exclude_usr)
अणु
	u32 escr = 0;

	अगर (!p4_ht_thपढ़ो(cpu)) अणु
		अगर (!exclude_os)
			escr |= P4_ESCR_T0_OS;
		अगर (!exclude_usr)
			escr |= P4_ESCR_T0_USR;
	पूर्ण अन्यथा अणु
		अगर (!exclude_os)
			escr |= P4_ESCR_T1_OS;
		अगर (!exclude_usr)
			escr |= P4_ESCR_T1_USR;
	पूर्ण

	वापस escr;
पूर्ण

/*
 * This are the events which should be used in "Event Select"
 * field of ESCR रेजिस्टर, they are like unique keys which allow
 * the kernel to determinate which CCCR and COUNTER should be
 * used to track an event
 */
क्रमागत P4_EVENTS अणु
	P4_EVENT_TC_DELIVER_MODE,
	P4_EVENT_BPU_FETCH_REQUEST,
	P4_EVENT_ITLB_REFERENCE,
	P4_EVENT_MEMORY_CANCEL,
	P4_EVENT_MEMORY_COMPLETE,
	P4_EVENT_LOAD_PORT_REPLAY,
	P4_EVENT_STORE_PORT_REPLAY,
	P4_EVENT_MOB_LOAD_REPLAY,
	P4_EVENT_PAGE_WALK_TYPE,
	P4_EVENT_BSQ_CACHE_REFERENCE,
	P4_EVENT_IOQ_ALLOCATION,
	P4_EVENT_IOQ_ACTIVE_ENTRIES,
	P4_EVENT_FSB_DATA_ACTIVITY,
	P4_EVENT_BSQ_ALLOCATION,
	P4_EVENT_BSQ_ACTIVE_ENTRIES,
	P4_EVENT_SSE_INPUT_ASSIST,
	P4_EVENT_PACKED_SP_UOP,
	P4_EVENT_PACKED_DP_UOP,
	P4_EVENT_SCALAR_SP_UOP,
	P4_EVENT_SCALAR_DP_UOP,
	P4_EVENT_64BIT_MMX_UOP,
	P4_EVENT_128BIT_MMX_UOP,
	P4_EVENT_X87_FP_UOP,
	P4_EVENT_TC_MISC,
	P4_EVENT_GLOBAL_POWER_EVENTS,
	P4_EVENT_TC_MS_XFER,
	P4_EVENT_UOP_QUEUE_WRITES,
	P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE,
	P4_EVENT_RETIRED_BRANCH_TYPE,
	P4_EVENT_RESOURCE_STALL,
	P4_EVENT_WC_BUFFER,
	P4_EVENT_B2B_CYCLES,
	P4_EVENT_BNR,
	P4_EVENT_SNOOP,
	P4_EVENT_RESPONSE,
	P4_EVENT_FRONT_END_EVENT,
	P4_EVENT_EXECUTION_EVENT,
	P4_EVENT_REPLAY_EVENT,
	P4_EVENT_INSTR_RETIRED,
	P4_EVENT_UOPS_RETIRED,
	P4_EVENT_UOP_TYPE,
	P4_EVENT_BRANCH_RETIRED,
	P4_EVENT_MISPRED_BRANCH_RETIRED,
	P4_EVENT_X87_ASSIST,
	P4_EVENT_MACHINE_CLEAR,
	P4_EVENT_INSTR_COMPLETED,
पूर्ण;

#घोषणा P4_OPCODE(event)		event##_OPCODE
#घोषणा P4_OPCODE_ESEL(opcode)		((opcode & 0x00ff) >> 0)
#घोषणा P4_OPCODE_EVNT(opcode)		((opcode & 0xff00) >> 8)
#घोषणा P4_OPCODE_PACK(event, sel)	(((event) << 8) | sel)

/*
 * Comments below the event represent ESCR restriction
 * क्रम this event and counter index per ESCR
 *
 * MSR_P4_IQ_ESCR0 and MSR_P4_IQ_ESCR1 are available only on early
 * processor builds (family 0FH, models 01H-02H). These MSRs
 * are not available on later versions, so that we करोn't use
 * them completely
 *
 * Also note that CCCR1 करो not have P4_CCCR_ENABLE bit properly
 * working so that we should not use this CCCR and respective
 * counter as result
 */
क्रमागत P4_EVENT_OPCODES अणु
	P4_OPCODE(P4_EVENT_TC_DELIVER_MODE)		= P4_OPCODE_PACK(0x01, 0x01),
	/*
	 * MSR_P4_TC_ESCR0:	4, 5
	 * MSR_P4_TC_ESCR1:	6, 7
	 */

	P4_OPCODE(P4_EVENT_BPU_FETCH_REQUEST)		= P4_OPCODE_PACK(0x03, 0x00),
	/*
	 * MSR_P4_BPU_ESCR0:	0, 1
	 * MSR_P4_BPU_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_ITLB_REFERENCE)		= P4_OPCODE_PACK(0x18, 0x03),
	/*
	 * MSR_P4_ITLB_ESCR0:	0, 1
	 * MSR_P4_ITLB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_MEMORY_CANCEL)		= P4_OPCODE_PACK(0x02, 0x05),
	/*
	 * MSR_P4_DAC_ESCR0:	8, 9
	 * MSR_P4_DAC_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_MEMORY_COMPLETE)		= P4_OPCODE_PACK(0x08, 0x02),
	/*
	 * MSR_P4_SAAT_ESCR0:	8, 9
	 * MSR_P4_SAAT_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_LOAD_PORT_REPLAY)		= P4_OPCODE_PACK(0x04, 0x02),
	/*
	 * MSR_P4_SAAT_ESCR0:	8, 9
	 * MSR_P4_SAAT_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_STORE_PORT_REPLAY)		= P4_OPCODE_PACK(0x05, 0x02),
	/*
	 * MSR_P4_SAAT_ESCR0:	8, 9
	 * MSR_P4_SAAT_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_MOB_LOAD_REPLAY)		= P4_OPCODE_PACK(0x03, 0x02),
	/*
	 * MSR_P4_MOB_ESCR0:	0, 1
	 * MSR_P4_MOB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_PAGE_WALK_TYPE)		= P4_OPCODE_PACK(0x01, 0x04),
	/*
	 * MSR_P4_PMH_ESCR0:	0, 1
	 * MSR_P4_PMH_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_BSQ_CACHE_REFERENCE)		= P4_OPCODE_PACK(0x0c, 0x07),
	/*
	 * MSR_P4_BSU_ESCR0:	0, 1
	 * MSR_P4_BSU_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_IOQ_ALLOCATION)		= P4_OPCODE_PACK(0x03, 0x06),
	/*
	 * MSR_P4_FSB_ESCR0:	0, 1
	 * MSR_P4_FSB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_IOQ_ACTIVE_ENTRIES)		= P4_OPCODE_PACK(0x1a, 0x06),
	/*
	 * MSR_P4_FSB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_FSB_DATA_ACTIVITY)		= P4_OPCODE_PACK(0x17, 0x06),
	/*
	 * MSR_P4_FSB_ESCR0:	0, 1
	 * MSR_P4_FSB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_BSQ_ALLOCATION)		= P4_OPCODE_PACK(0x05, 0x07),
	/*
	 * MSR_P4_BSU_ESCR0:	0, 1
	 */

	P4_OPCODE(P4_EVENT_BSQ_ACTIVE_ENTRIES)		= P4_OPCODE_PACK(0x06, 0x07),
	/*
	 * NOTE: no ESCR name in करोcs, it's guessed
	 * MSR_P4_BSU_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_SSE_INPUT_ASSIST)		= P4_OPCODE_PACK(0x34, 0x01),
	/*
	 * MSR_P4_FIRM_ESCR0:	8, 9
	 * MSR_P4_FIRM_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_PACKED_SP_UOP)		= P4_OPCODE_PACK(0x08, 0x01),
	/*
	 * MSR_P4_FIRM_ESCR0:	8, 9
	 * MSR_P4_FIRM_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_PACKED_DP_UOP)		= P4_OPCODE_PACK(0x0c, 0x01),
	/*
	 * MSR_P4_FIRM_ESCR0:	8, 9
	 * MSR_P4_FIRM_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_SCALAR_SP_UOP)		= P4_OPCODE_PACK(0x0a, 0x01),
	/*
	 * MSR_P4_FIRM_ESCR0:	8, 9
	 * MSR_P4_FIRM_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_SCALAR_DP_UOP)		= P4_OPCODE_PACK(0x0e, 0x01),
	/*
	 * MSR_P4_FIRM_ESCR0:	8, 9
	 * MSR_P4_FIRM_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_64BIT_MMX_UOP)		= P4_OPCODE_PACK(0x02, 0x01),
	/*
	 * MSR_P4_FIRM_ESCR0:	8, 9
	 * MSR_P4_FIRM_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_128BIT_MMX_UOP)		= P4_OPCODE_PACK(0x1a, 0x01),
	/*
	 * MSR_P4_FIRM_ESCR0:	8, 9
	 * MSR_P4_FIRM_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_X87_FP_UOP)			= P4_OPCODE_PACK(0x04, 0x01),
	/*
	 * MSR_P4_FIRM_ESCR0:	8, 9
	 * MSR_P4_FIRM_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_TC_MISC)			= P4_OPCODE_PACK(0x06, 0x01),
	/*
	 * MSR_P4_TC_ESCR0:	4, 5
	 * MSR_P4_TC_ESCR1:	6, 7
	 */

	P4_OPCODE(P4_EVENT_GLOBAL_POWER_EVENTS)		= P4_OPCODE_PACK(0x13, 0x06),
	/*
	 * MSR_P4_FSB_ESCR0:	0, 1
	 * MSR_P4_FSB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_TC_MS_XFER)			= P4_OPCODE_PACK(0x05, 0x00),
	/*
	 * MSR_P4_MS_ESCR0:	4, 5
	 * MSR_P4_MS_ESCR1:	6, 7
	 */

	P4_OPCODE(P4_EVENT_UOP_QUEUE_WRITES)		= P4_OPCODE_PACK(0x09, 0x00),
	/*
	 * MSR_P4_MS_ESCR0:	4, 5
	 * MSR_P4_MS_ESCR1:	6, 7
	 */

	P4_OPCODE(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE)	= P4_OPCODE_PACK(0x05, 0x02),
	/*
	 * MSR_P4_TBPU_ESCR0:	4, 5
	 * MSR_P4_TBPU_ESCR1:	6, 7
	 */

	P4_OPCODE(P4_EVENT_RETIRED_BRANCH_TYPE)		= P4_OPCODE_PACK(0x04, 0x02),
	/*
	 * MSR_P4_TBPU_ESCR0:	4, 5
	 * MSR_P4_TBPU_ESCR1:	6, 7
	 */

	P4_OPCODE(P4_EVENT_RESOURCE_STALL)		= P4_OPCODE_PACK(0x01, 0x01),
	/*
	 * MSR_P4_ALF_ESCR0:	12, 13, 16
	 * MSR_P4_ALF_ESCR1:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_WC_BUFFER)			= P4_OPCODE_PACK(0x05, 0x05),
	/*
	 * MSR_P4_DAC_ESCR0:	8, 9
	 * MSR_P4_DAC_ESCR1:	10, 11
	 */

	P4_OPCODE(P4_EVENT_B2B_CYCLES)			= P4_OPCODE_PACK(0x16, 0x03),
	/*
	 * MSR_P4_FSB_ESCR0:	0, 1
	 * MSR_P4_FSB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_BNR)				= P4_OPCODE_PACK(0x08, 0x03),
	/*
	 * MSR_P4_FSB_ESCR0:	0, 1
	 * MSR_P4_FSB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_SNOOP)			= P4_OPCODE_PACK(0x06, 0x03),
	/*
	 * MSR_P4_FSB_ESCR0:	0, 1
	 * MSR_P4_FSB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_RESPONSE)			= P4_OPCODE_PACK(0x04, 0x03),
	/*
	 * MSR_P4_FSB_ESCR0:	0, 1
	 * MSR_P4_FSB_ESCR1:	2, 3
	 */

	P4_OPCODE(P4_EVENT_FRONT_END_EVENT)		= P4_OPCODE_PACK(0x08, 0x05),
	/*
	 * MSR_P4_CRU_ESCR2:	12, 13, 16
	 * MSR_P4_CRU_ESCR3:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_EXECUTION_EVENT)		= P4_OPCODE_PACK(0x0c, 0x05),
	/*
	 * MSR_P4_CRU_ESCR2:	12, 13, 16
	 * MSR_P4_CRU_ESCR3:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_REPLAY_EVENT)		= P4_OPCODE_PACK(0x09, 0x05),
	/*
	 * MSR_P4_CRU_ESCR2:	12, 13, 16
	 * MSR_P4_CRU_ESCR3:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_INSTR_RETIRED)		= P4_OPCODE_PACK(0x02, 0x04),
	/*
	 * MSR_P4_CRU_ESCR0:	12, 13, 16
	 * MSR_P4_CRU_ESCR1:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_UOPS_RETIRED)		= P4_OPCODE_PACK(0x01, 0x04),
	/*
	 * MSR_P4_CRU_ESCR0:	12, 13, 16
	 * MSR_P4_CRU_ESCR1:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_UOP_TYPE)			= P4_OPCODE_PACK(0x02, 0x02),
	/*
	 * MSR_P4_RAT_ESCR0:	12, 13, 16
	 * MSR_P4_RAT_ESCR1:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_BRANCH_RETIRED)		= P4_OPCODE_PACK(0x06, 0x05),
	/*
	 * MSR_P4_CRU_ESCR2:	12, 13, 16
	 * MSR_P4_CRU_ESCR3:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_MISPRED_BRANCH_RETIRED)	= P4_OPCODE_PACK(0x03, 0x04),
	/*
	 * MSR_P4_CRU_ESCR0:	12, 13, 16
	 * MSR_P4_CRU_ESCR1:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_X87_ASSIST)			= P4_OPCODE_PACK(0x03, 0x05),
	/*
	 * MSR_P4_CRU_ESCR2:	12, 13, 16
	 * MSR_P4_CRU_ESCR3:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_MACHINE_CLEAR)		= P4_OPCODE_PACK(0x02, 0x05),
	/*
	 * MSR_P4_CRU_ESCR2:	12, 13, 16
	 * MSR_P4_CRU_ESCR3:	14, 15, 17
	 */

	P4_OPCODE(P4_EVENT_INSTR_COMPLETED)		= P4_OPCODE_PACK(0x07, 0x04),
	/*
	 * MSR_P4_CRU_ESCR0:	12, 13, 16
	 * MSR_P4_CRU_ESCR1:	14, 15, 17
	 */
पूर्ण;

/*
 * a caller should use P4_ESCR_EMASK_NAME helper to
 * pick the EventMask needed, क्रम example
 *
 *	P4_ESCR_EMASK_BIT(P4_EVENT_TC_DELIVER_MODE, DD)
 */
क्रमागत P4_ESCR_EMASKS अणु
	P4_GEN_ESCR_EMASK(P4_EVENT_TC_DELIVER_MODE, DD, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_TC_DELIVER_MODE, DB, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_TC_DELIVER_MODE, DI, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_TC_DELIVER_MODE, BD, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_TC_DELIVER_MODE, BB, 4),
	P4_GEN_ESCR_EMASK(P4_EVENT_TC_DELIVER_MODE, BI, 5),
	P4_GEN_ESCR_EMASK(P4_EVENT_TC_DELIVER_MODE, ID, 6),

	P4_GEN_ESCR_EMASK(P4_EVENT_BPU_FETCH_REQUEST, TCMISS, 0),

	P4_GEN_ESCR_EMASK(P4_EVENT_ITLB_REFERENCE, HIT, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_ITLB_REFERENCE, MISS, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_ITLB_REFERENCE, HIT_UK, 2),

	P4_GEN_ESCR_EMASK(P4_EVENT_MEMORY_CANCEL, ST_RB_FULL, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_MEMORY_CANCEL, 64K_CONF, 3),

	P4_GEN_ESCR_EMASK(P4_EVENT_MEMORY_COMPLETE, LSC, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_MEMORY_COMPLETE, SSC, 1),

	P4_GEN_ESCR_EMASK(P4_EVENT_LOAD_PORT_REPLAY, SPLIT_LD, 1),

	P4_GEN_ESCR_EMASK(P4_EVENT_STORE_PORT_REPLAY, SPLIT_ST, 1),

	P4_GEN_ESCR_EMASK(P4_EVENT_MOB_LOAD_REPLAY, NO_STA, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_MOB_LOAD_REPLAY, NO_STD, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_MOB_LOAD_REPLAY, PARTIAL_DATA, 4),
	P4_GEN_ESCR_EMASK(P4_EVENT_MOB_LOAD_REPLAY, UNALGN_ADDR, 5),

	P4_GEN_ESCR_EMASK(P4_EVENT_PAGE_WALK_TYPE, DTMISS, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_PAGE_WALK_TYPE, ITMISS, 1),

	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITS, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITE, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_HITM, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITS, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITE, 4),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_HITM, 5),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, RD_2ndL_MISS, 8),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, RD_3rdL_MISS, 9),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_CACHE_REFERENCE, WR_2ndL_MISS, 10),

	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, DEFAULT, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, ALL_READ, 5),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, ALL_WRITE, 6),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, MEM_UC, 7),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, MEM_WC, 8),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, MEM_WT, 9),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, MEM_WP, 10),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, MEM_WB, 11),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, OWN, 13),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, OTHER, 14),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ALLOCATION, PREFETCH, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, DEFAULT, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, ALL_READ, 5),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, ALL_WRITE, 6),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_UC, 7),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_WC, 8),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_WT, 9),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_WP, 10),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, MEM_WB, 11),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, OWN, 13),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, OTHER, 14),
	P4_GEN_ESCR_EMASK(P4_EVENT_IOQ_ACTIVE_ENTRIES, PREFETCH, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_FSB_DATA_ACTIVITY, DRDY_DRV, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_FSB_DATA_ACTIVITY, DRDY_OWN, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_FSB_DATA_ACTIVITY, DRDY_OTHER, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_DRV, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_OWN, 4),
	P4_GEN_ESCR_EMASK(P4_EVENT_FSB_DATA_ACTIVITY, DBSY_OTHER, 5),

	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_TYPE0, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_TYPE1, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_LEN0, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_LEN1, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_IO_TYPE, 5),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_LOCK_TYPE, 6),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_CACHE_TYPE, 7),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_SPLIT_TYPE, 8),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_DEM_TYPE, 9),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, REQ_ORD_TYPE, 10),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, MEM_TYPE0, 11),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, MEM_TYPE1, 12),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ALLOCATION, MEM_TYPE2, 13),

	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_TYPE0, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_TYPE1, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_LEN0, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_LEN1, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_IO_TYPE, 5),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_LOCK_TYPE, 6),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_CACHE_TYPE, 7),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_SPLIT_TYPE, 8),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_DEM_TYPE, 9),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, REQ_ORD_TYPE, 10),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, MEM_TYPE0, 11),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, MEM_TYPE1, 12),
	P4_GEN_ESCR_EMASK(P4_EVENT_BSQ_ACTIVE_ENTRIES, MEM_TYPE2, 13),

	P4_GEN_ESCR_EMASK(P4_EVENT_SSE_INPUT_ASSIST, ALL, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_PACKED_SP_UOP, ALL, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_PACKED_DP_UOP, ALL, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_SCALAR_SP_UOP, ALL, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_SCALAR_DP_UOP, ALL, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_64BIT_MMX_UOP, ALL, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_128BIT_MMX_UOP, ALL, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_X87_FP_UOP, ALL, 15),

	P4_GEN_ESCR_EMASK(P4_EVENT_TC_MISC, FLUSH, 4),

	P4_GEN_ESCR_EMASK(P4_EVENT_GLOBAL_POWER_EVENTS, RUNNING, 0),

	P4_GEN_ESCR_EMASK(P4_EVENT_TC_MS_XFER, CISC, 0),

	P4_GEN_ESCR_EMASK(P4_EVENT_UOP_QUEUE_WRITES, FROM_TC_BUILD, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_UOP_QUEUE_WRITES, FROM_TC_DELIVER, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_UOP_QUEUE_WRITES, FROM_ROM, 2),

	P4_GEN_ESCR_EMASK(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE, CONDITIONAL, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE, CALL, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE, RETURN, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE, INसूचीECT, 4),

	P4_GEN_ESCR_EMASK(P4_EVENT_RETIRED_BRANCH_TYPE, CONDITIONAL, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_RETIRED_BRANCH_TYPE, CALL, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_RETIRED_BRANCH_TYPE, RETURN, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_RETIRED_BRANCH_TYPE, INसूचीECT, 4),

	P4_GEN_ESCR_EMASK(P4_EVENT_RESOURCE_STALL, SBFULL, 5),

	P4_GEN_ESCR_EMASK(P4_EVENT_WC_BUFFER, WCB_EVICTS, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_WC_BUFFER, WCB_FULL_EVICTS, 1),

	P4_GEN_ESCR_EMASK(P4_EVENT_FRONT_END_EVENT, NBOGUS, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_FRONT_END_EVENT, BOGUS, 1),

	P4_GEN_ESCR_EMASK(P4_EVENT_EXECUTION_EVENT, NBOGUS0, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_EXECUTION_EVENT, NBOGUS1, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_EXECUTION_EVENT, NBOGUS2, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_EXECUTION_EVENT, NBOGUS3, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_EXECUTION_EVENT, BOGUS0, 4),
	P4_GEN_ESCR_EMASK(P4_EVENT_EXECUTION_EVENT, BOGUS1, 5),
	P4_GEN_ESCR_EMASK(P4_EVENT_EXECUTION_EVENT, BOGUS2, 6),
	P4_GEN_ESCR_EMASK(P4_EVENT_EXECUTION_EVENT, BOGUS3, 7),

	P4_GEN_ESCR_EMASK(P4_EVENT_REPLAY_EVENT, NBOGUS, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_REPLAY_EVENT, BOGUS, 1),

	P4_GEN_ESCR_EMASK(P4_EVENT_INSTR_RETIRED, NBOGUSNTAG, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_INSTR_RETIRED, NBOGUSTAG, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_INSTR_RETIRED, BOGUSNTAG, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_INSTR_RETIRED, BOGUSTAG, 3),

	P4_GEN_ESCR_EMASK(P4_EVENT_UOPS_RETIRED, NBOGUS, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_UOPS_RETIRED, BOGUS, 1),

	P4_GEN_ESCR_EMASK(P4_EVENT_UOP_TYPE, TAGLOADS, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_UOP_TYPE, TAGSTORES, 2),

	P4_GEN_ESCR_EMASK(P4_EVENT_BRANCH_RETIRED, MMNP, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_BRANCH_RETIRED, MMNM, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_BRANCH_RETIRED, MMTP, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_BRANCH_RETIRED, MMTM, 3),

	P4_GEN_ESCR_EMASK(P4_EVENT_MISPRED_BRANCH_RETIRED, NBOGUS, 0),

	P4_GEN_ESCR_EMASK(P4_EVENT_X87_ASSIST, FPSU, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_X87_ASSIST, FPSO, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_X87_ASSIST, POAO, 2),
	P4_GEN_ESCR_EMASK(P4_EVENT_X87_ASSIST, POAU, 3),
	P4_GEN_ESCR_EMASK(P4_EVENT_X87_ASSIST, PREA, 4),

	P4_GEN_ESCR_EMASK(P4_EVENT_MACHINE_CLEAR, CLEAR, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_MACHINE_CLEAR, MOCLEAR, 1),
	P4_GEN_ESCR_EMASK(P4_EVENT_MACHINE_CLEAR, SMCLEAR, 2),

	P4_GEN_ESCR_EMASK(P4_EVENT_INSTR_COMPLETED, NBOGUS, 0),
	P4_GEN_ESCR_EMASK(P4_EVENT_INSTR_COMPLETED, BOGUS, 1),
पूर्ण;

/*
 * Note we have UOP and PEBS bits reserved क्रम now
 * just in हाल अगर we will need them once
 */
#घोषणा P4_PEBS_CONFIG_ENABLE		(1ULL << 7)
#घोषणा P4_PEBS_CONFIG_UOP_TAG		(1ULL << 8)
#घोषणा P4_PEBS_CONFIG_METRIC_MASK	0x3FLL
#घोषणा P4_PEBS_CONFIG_MASK		0xFFLL

/*
 * mem: Only counters MSR_IQ_COUNTER4 (16) and
 * MSR_IQ_COUNTER5 (17) are allowed क्रम PEBS sampling
 */
#घोषणा P4_PEBS_ENABLE			0x02000000ULL
#घोषणा P4_PEBS_ENABLE_UOP_TAG		0x01000000ULL

#घोषणा p4_config_unpack_metric(v)	(((u64)(v)) & P4_PEBS_CONFIG_METRIC_MASK)
#घोषणा p4_config_unpack_pebs(v)	(((u64)(v)) & P4_PEBS_CONFIG_MASK)

#घोषणा p4_config_pebs_has(v, mask)	(p4_config_unpack_pebs(v) & (mask))

क्रमागत P4_PEBS_METRIC अणु
	P4_PEBS_METRIC__none,

	P4_PEBS_METRIC__1stl_cache_load_miss_retired,
	P4_PEBS_METRIC__2ndl_cache_load_miss_retired,
	P4_PEBS_METRIC__dtlb_load_miss_retired,
	P4_PEBS_METRIC__dtlb_store_miss_retired,
	P4_PEBS_METRIC__dtlb_all_miss_retired,
	P4_PEBS_METRIC__tagged_mispred_branch,
	P4_PEBS_METRIC__mob_load_replay_retired,
	P4_PEBS_METRIC__split_load_retired,
	P4_PEBS_METRIC__split_store_retired,

	P4_PEBS_METRIC__max
पूर्ण;

/*
 * Notes on पूर्णांकernal configuration of ESCR+CCCR tuples
 *
 * Since P4 has quite the dअगरferent architecture of
 * perक्रमmance रेजिस्टरs in compare with "architectural"
 * once and we have on 64 bits to keep configuration
 * of perक्रमmance event, the following trick is used.
 *
 * 1) Since both ESCR and CCCR रेजिस्टरs have only low
 *    32 bits valuable, we pack them पूर्णांकo a single 64 bit
 *    configuration. Low 32 bits of such config correspond
 *    to low 32 bits of CCCR रेजिस्टर and high 32 bits
 *    correspond to low 32 bits of ESCR रेजिस्टर.
 *
 * 2) The meaning of every bit of such config field can
 *    be found in Intel SDM but it should be noted that
 *    we "borrow" some reserved bits क्रम own usage and
 *    clean them or set to a proper value when we करो
 *    a real ग_लिखो to hardware रेजिस्टरs.
 *
 * 3) The क्रमmat of bits of config is the following
 *    and should be either 0 or set to some predefined
 *    values:
 *
 *    Low 32 bits
 *    -----------
 *      0-6: P4_PEBS_METRIC क्रमागत
 *     7-11:                    reserved
 *       12:                    reserved (Enable)
 *    13-15:                    reserved (ESCR select)
 *    16-17: Active Thपढ़ो
 *       18: Compare
 *       19: Complement
 *    20-23: Threshold
 *       24: Edge
 *       25:                    reserved (FORCE_OVF)
 *       26:                    reserved (OVF_PMI_T0)
 *       27:                    reserved (OVF_PMI_T1)
 *    28-29:                    reserved
 *       30:                    reserved (Cascade)
 *       31:                    reserved (OVF)
 *
 *    High 32 bits
 *    ------------
 *        0:                    reserved (T1_USR)
 *        1:                    reserved (T1_OS)
 *        2:                    reserved (T0_USR)
 *        3:                    reserved (T0_OS)
 *        4: Tag Enable
 *      5-8: Tag Value
 *     9-24: Event Mask (may use P4_ESCR_EMASK_BIT helper)
 *    25-30: क्रमागत P4_EVENTS
 *       31:                    reserved (HT thपढ़ो)
 */

#पूर्ण_अगर /* PERF_EVENT_P4_H */

