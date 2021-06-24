<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_PAL_H
#घोषणा _ASM_IA64_PAL_H

/*
 * Processor Abstraction Layer definitions.
 *
 * This is based on Intel IA-64 Architecture Software Developer's Manual rev 1.0
 * chapter 11 IA-64 Processor Abstraction Layer
 *
 * Copyright (C) 1998-2001 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999 Srinivasa Prasad Thirumalaअक्षर <sprasad@sprasad.engr.sgi.com>
 * Copyright (C) 2008 Silicon Graphics, Inc. (SGI)
 *
 * 99/10/01	davidm	Make sure we pass zero क्रम reserved parameters.
 * 00/03/07	davidm	Updated pal_cache_flush() to be in sync with PAL v2.6.
 * 00/03/23     cfleck  Modअगरied processor min-state save area to match updated PAL & SAL info
 * 00/05/24     eranian Updated to latest PAL spec, fix काष्ठाures bugs, added
 * 00/05/25	eranian Support क्रम stack calls, and अटल physical calls
 * 00/06/18	eranian Support क्रम stacked physical calls
 * 06/10/26	rja	Support क्रम Intel Itanium Architecture Software Developer's
 *			Manual Rev 2.2 (Jan 2006)
 */

/*
 * Note that some of these calls use a अटल-रेजिस्टर only calling
 * convention which has nothing to करो with the regular calling
 * convention.
 */
#घोषणा PAL_CACHE_FLUSH		1	/* flush i/d cache */
#घोषणा PAL_CACHE_INFO		2	/* get detailed i/d cache info */
#घोषणा PAL_CACHE_INIT		3	/* initialize i/d cache */
#घोषणा PAL_CACHE_SUMMARY	4	/* get summary of cache hierarchy */
#घोषणा PAL_MEM_ATTRIB		5	/* list supported memory attributes */
#घोषणा PAL_PTCE_INFO		6	/* purge TLB info */
#घोषणा PAL_VM_INFO		7	/* वापस supported भव memory features */
#घोषणा PAL_VM_SUMMARY		8	/* वापस summary on supported vm features */
#घोषणा PAL_BUS_GET_FEATURES	9	/* वापस processor bus पूर्णांकerface features settings */
#घोषणा PAL_BUS_SET_FEATURES	10	/* set processor bus features */
#घोषणा PAL_DEBUG_INFO		11	/* get number of debug रेजिस्टरs */
#घोषणा PAL_FIXED_ADDR		12	/* get fixed component of processors's directed address */
#घोषणा PAL_FREQ_BASE		13	/* base frequency of the platक्रमm */
#घोषणा PAL_FREQ_RATIOS		14	/* ratio of processor, bus and ITC frequency */
#घोषणा PAL_PERF_MON_INFO	15	/* वापस perक्रमmance monitor info */
#घोषणा PAL_PLATFORM_ADDR	16	/* set processor पूर्णांकerrupt block and IO port space addr */
#घोषणा PAL_PROC_GET_FEATURES	17	/* get configurable processor features & settings */
#घोषणा PAL_PROC_SET_FEATURES	18	/* enable/disable configurable processor features */
#घोषणा PAL_RSE_INFO		19	/* वापस rse inक्रमmation */
#घोषणा PAL_VERSION		20	/* वापस version of PAL code */
#घोषणा PAL_MC_CLEAR_LOG	21	/* clear all processor log info */
#घोषणा PAL_MC_DRAIN		22	/* drain operations which could result in an MCA */
#घोषणा PAL_MC_EXPECTED		23	/* set/reset expected MCA indicator */
#घोषणा PAL_MC_DYNAMIC_STATE	24	/* get processor dynamic state */
#घोषणा PAL_MC_ERROR_INFO	25	/* get processor MCA info and अटल state */
#घोषणा PAL_MC_RESUME		26	/* Return to पूर्णांकerrupted process */
#घोषणा PAL_MC_REGISTER_MEM	27	/* Register memory क्रम PAL to use during MCAs and inits */
#घोषणा PAL_HALT		28	/* enter the low घातer HALT state */
#घोषणा PAL_HALT_LIGHT		29	/* enter the low घातer light halt state*/
#घोषणा PAL_COPY_INFO		30	/* वापसs info needed to relocate PAL */
#घोषणा PAL_CACHE_LINE_INIT	31	/* init tags & data of cache line */
#घोषणा PAL_PMI_ENTRYPOINT	32	/* रेजिस्टर PMI memory entry poपूर्णांकs with the processor */
#घोषणा PAL_ENTER_IA_32_ENV	33	/* enter IA-32 प्रणाली environment */
#घोषणा PAL_VM_PAGE_SIZE	34	/* वापस vm TC and page walker page sizes */

#घोषणा PAL_MEM_FOR_TEST	37	/* get amount of memory needed क्रम late processor test */
#घोषणा PAL_CACHE_PROT_INFO	38	/* get i/d cache protection info */
#घोषणा PAL_REGISTER_INFO	39	/* वापस AR and CR रेजिस्टर inक्रमmation*/
#घोषणा PAL_SHUTDOWN		40	/* enter processor shutकरोwn state */
#घोषणा PAL_PREFETCH_VISIBILITY	41	/* Make Processor Prefetches Visible */
#घोषणा PAL_LOGICAL_TO_PHYSICAL 42	/* वापसs inक्रमmation on logical to physical processor mapping */
#घोषणा PAL_CACHE_SHARED_INFO	43	/* वापसs inक्रमmation on caches shared by logical processor */
#घोषणा PAL_GET_HW_POLICY	48	/* Get current hardware resource sharing policy */
#घोषणा PAL_SET_HW_POLICY	49	/* Set current hardware resource sharing policy */
#घोषणा PAL_VP_INFO		50	/* Inक्रमmation about भव processor features */
#घोषणा PAL_MC_HW_TRACKING	51	/* Hardware tracking status */

#घोषणा PAL_COPY_PAL		256	/* relocate PAL procedures and PAL PMI */
#घोषणा PAL_HALT_INFO		257	/* वापस the low घातer capabilities of processor */
#घोषणा PAL_TEST_PROC		258	/* perक्रमm late processor self-test */
#घोषणा PAL_CACHE_READ		259	/* पढ़ो tag & data of cacheline क्रम diagnostic testing */
#घोषणा PAL_CACHE_WRITE		260	/* ग_लिखो tag & data of cacheline क्रम diagnostic testing */
#घोषणा PAL_VM_TR_READ		261	/* पढ़ो contents of translation रेजिस्टर */
#घोषणा PAL_GET_PSTATE		262	/* get the current P-state */
#घोषणा PAL_SET_PSTATE		263	/* set the P-state */
#घोषणा PAL_BRAND_INFO		274	/* Processor bअक्रमing inक्रमmation */

#घोषणा PAL_GET_PSTATE_TYPE_LASTSET	0
#घोषणा PAL_GET_PSTATE_TYPE_AVGANDRESET	1
#घोषणा PAL_GET_PSTATE_TYPE_AVGNORESET	2
#घोषणा PAL_GET_PSTATE_TYPE_INSTANT	3

#घोषणा PAL_MC_ERROR_INJECT	276	/* Injects processor error or वापसs injection capabilities */

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/fpu.h>

/*
 * Data types needed to pass inक्रमmation पूर्णांकo PAL procedures and
 * पूर्णांकerpret inक्रमmation वापसed by them.
 */

/* Return status from the PAL procedure */
प्रकार s64				pal_status_t;

#घोषणा PAL_STATUS_SUCCESS		0	/* No error */
#घोषणा PAL_STATUS_UNIMPLEMENTED	(-1)	/* Unimplemented procedure */
#घोषणा PAL_STATUS_EINVAL		(-2)	/* Invalid argument */
#घोषणा PAL_STATUS_ERROR		(-3)	/* Error */
#घोषणा PAL_STATUS_CACHE_INIT_FAIL	(-4)	/* Could not initialize the
						 * specअगरied level and type of
						 * cache without sideeffects
						 * and "restrict" was 1
						 */
#घोषणा PAL_STATUS_REQUIRES_MEMORY	(-9)	/* Call requires PAL memory buffer */

/* Processor cache level in the hierarchy */
प्रकार u64				pal_cache_level_t;
#घोषणा PAL_CACHE_LEVEL_L0		0	/* L0 */
#घोषणा PAL_CACHE_LEVEL_L1		1	/* L1 */
#घोषणा PAL_CACHE_LEVEL_L2		2	/* L2 */


/* Processor cache type at a particular level in the hierarchy */

प्रकार u64				pal_cache_type_t;
#घोषणा PAL_CACHE_TYPE_INSTRUCTION	1	/* Inकाष्ठाion cache */
#घोषणा PAL_CACHE_TYPE_DATA		2	/* Data or unअगरied cache */
#घोषणा PAL_CACHE_TYPE_INSTRUCTION_DATA	3	/* Both Data & Inकाष्ठाion */


#घोषणा PAL_CACHE_FLUSH_INVALIDATE	1	/* Invalidate clean lines */
#घोषणा PAL_CACHE_FLUSH_CHK_INTRS	2	/* check क्रम पूर्णांकerrupts/mc जबतक flushing */

/* Processor cache line size in bytes  */
प्रकार पूर्णांक				pal_cache_line_माप_प्रकार;

/* Processor cache line state */
प्रकार u64				pal_cache_line_state_t;
#घोषणा PAL_CACHE_LINE_STATE_INVALID	0	/* Invalid */
#घोषणा PAL_CACHE_LINE_STATE_SHARED	1	/* Shared */
#घोषणा PAL_CACHE_LINE_STATE_EXCLUSIVE	2	/* Exclusive */
#घोषणा PAL_CACHE_LINE_STATE_MODIFIED	3	/* Modअगरied */

प्रकार काष्ठा pal_freq_ratio अणु
	u32 den, num;		/* numerator & denominator */
पूर्ण itc_ratio, proc_ratio;

प्रकार	जोड़  pal_cache_config_info_1_s अणु
	काष्ठा अणु
		u64		u		: 1,	/* 0 Unअगरied cache ? */
				at		: 2,	/* 2-1 Cache mem attr*/
				reserved	: 5,	/* 7-3 Reserved */
				associativity	: 8,	/* 16-8 Associativity*/
				line_size	: 8,	/* 23-17 Line size */
				stride		: 8,	/* 31-24 Stride */
				store_latency	: 8,	/*39-32 Store latency*/
				load_latency	: 8,	/* 47-40 Load latency*/
				store_hपूर्णांकs	: 8,	/* 55-48 Store hपूर्णांकs*/
				load_hपूर्णांकs	: 8;	/* 63-56 Load hपूर्णांकs */
	पूर्ण pcci1_bits;
	u64			pcci1_data;
पूर्ण pal_cache_config_info_1_t;

प्रकार	जोड़  pal_cache_config_info_2_s अणु
	काष्ठा अणु
		u32		cache_size;		/*cache size in bytes*/


		u32		alias_boundary	: 8,	/* 39-32 aliased addr
							 * separation क्रम max
							 * perक्रमmance.
							 */
				tag_ls_bit	: 8,	/* 47-40 LSb of addr*/
				tag_ms_bit	: 8,	/* 55-48 MSb of addr*/
				reserved	: 8;	/* 63-56 Reserved */
	पूर्ण pcci2_bits;
	u64			pcci2_data;
पूर्ण pal_cache_config_info_2_t;


प्रकार काष्ठा pal_cache_config_info_s अणु
	pal_status_t			pcci_status;
	pal_cache_config_info_1_t	pcci_info_1;
	pal_cache_config_info_2_t	pcci_info_2;
	u64				pcci_reserved;
पूर्ण pal_cache_config_info_t;

#घोषणा pcci_ld_hपूर्णांकs		pcci_info_1.pcci1_bits.load_hपूर्णांकs
#घोषणा pcci_st_hपूर्णांकs		pcci_info_1.pcci1_bits.store_hपूर्णांकs
#घोषणा pcci_ld_latency		pcci_info_1.pcci1_bits.load_latency
#घोषणा pcci_st_latency		pcci_info_1.pcci1_bits.store_latency
#घोषणा pcci_stride		pcci_info_1.pcci1_bits.stride
#घोषणा pcci_line_size		pcci_info_1.pcci1_bits.line_size
#घोषणा pcci_assoc		pcci_info_1.pcci1_bits.associativity
#घोषणा pcci_cache_attr		pcci_info_1.pcci1_bits.at
#घोषणा pcci_unअगरied		pcci_info_1.pcci1_bits.u
#घोषणा pcci_tag_msb		pcci_info_2.pcci2_bits.tag_ms_bit
#घोषणा pcci_tag_lsb		pcci_info_2.pcci2_bits.tag_ls_bit
#घोषणा pcci_alias_boundary	pcci_info_2.pcci2_bits.alias_boundary
#घोषणा pcci_cache_size		pcci_info_2.pcci2_bits.cache_size



/* Possible values क्रम cache attributes */

#घोषणा PAL_CACHE_ATTR_WT		0	/* Write through cache */
#घोषणा PAL_CACHE_ATTR_WB		1	/* Write back cache */
#घोषणा PAL_CACHE_ATTR_WT_OR_WB		2	/* Either ग_लिखो thru or ग_लिखो
						 * back depending on TLB
						 * memory attributes
						 */


/* Possible values क्रम cache hपूर्णांकs */

#घोषणा PAL_CACHE_HINT_TEMP_1		0	/* Temporal level 1 */
#घोषणा PAL_CACHE_HINT_NTEMP_1		1	/* Non-temporal level 1 */
#घोषणा PAL_CACHE_HINT_NTEMP_ALL	3	/* Non-temporal all levels */

/* Processor cache protection  inक्रमmation */
प्रकार जोड़ pal_cache_protection_element_u अणु
	u32			pcpi_data;
	काष्ठा अणु
		u32		data_bits	: 8, /* # data bits covered by
						      * each unit of protection
						      */

				tagprot_lsb	: 6, /* Least -करो- */
				tagprot_msb	: 6, /* Most Sig. tag address
						      * bit that this
						      * protection covers.
						      */
				prot_bits	: 6, /* # of protection bits */
				method		: 4, /* Protection method */
				t_d		: 2; /* Indicates which part
						      * of the cache this
						      * protection encoding
						      * applies.
						      */
	पूर्ण pcp_info;
पूर्ण pal_cache_protection_element_t;

#घोषणा pcpi_cache_prot_part	pcp_info.t_d
#घोषणा pcpi_prot_method	pcp_info.method
#घोषणा pcpi_prot_bits		pcp_info.prot_bits
#घोषणा pcpi_tagprot_msb	pcp_info.tagprot_msb
#घोषणा pcpi_tagprot_lsb	pcp_info.tagprot_lsb
#घोषणा pcpi_data_bits		pcp_info.data_bits

/* Processor cache part encodings */
#घोषणा PAL_CACHE_PROT_PART_DATA	0	/* Data protection  */
#घोषणा PAL_CACHE_PROT_PART_TAG		1	/* Tag  protection */
#घोषणा PAL_CACHE_PROT_PART_TAG_DATA	2	/* Tag+data protection (tag is
						 * more signअगरicant )
						 */
#घोषणा PAL_CACHE_PROT_PART_DATA_TAG	3	/* Data+tag protection (data is
						 * more signअगरicant )
						 */
#घोषणा PAL_CACHE_PROT_PART_MAX		6


प्रकार काष्ठा pal_cache_protection_info_s अणु
	pal_status_t			pcpi_status;
	pal_cache_protection_element_t	pcp_info[PAL_CACHE_PROT_PART_MAX];
पूर्ण pal_cache_protection_info_t;


/* Processor cache protection method encodings */
#घोषणा PAL_CACHE_PROT_METHOD_NONE		0	/* No protection */
#घोषणा PAL_CACHE_PROT_METHOD_ODD_PARITY	1	/* Odd parity */
#घोषणा PAL_CACHE_PROT_METHOD_EVEN_PARITY	2	/* Even parity */
#घोषणा PAL_CACHE_PROT_METHOD_ECC		3	/* ECC protection */


/* Processor cache line identअगरication in the hierarchy */
प्रकार जोड़ pal_cache_line_id_u अणु
	u64			pclid_data;
	काष्ठा अणु
		u64		cache_type	: 8,	/* 7-0 cache type */
				level		: 8,	/* 15-8 level of the
							 * cache in the
							 * hierarchy.
							 */
				way		: 8,	/* 23-16 way in the set
							 */
				part		: 8,	/* 31-24 part of the
							 * cache
							 */
				reserved	: 32;	/* 63-32 is reserved*/
	पूर्ण pclid_info_पढ़ो;
	काष्ठा अणु
		u64		cache_type	: 8,	/* 7-0 cache type */
				level		: 8,	/* 15-8 level of the
							 * cache in the
							 * hierarchy.
							 */
				way		: 8,	/* 23-16 way in the set
							 */
				part		: 8,	/* 31-24 part of the
							 * cache
							 */
				mesi		: 8,	/* 39-32 cache line
							 * state
							 */
				start		: 8,	/* 47-40 lsb of data to
							 * invert
							 */
				length		: 8,	/* 55-48 #bits to
							 * invert
							 */
				trigger		: 8;	/* 63-56 Trigger error
							 * by करोing a load
							 * after the ग_लिखो
							 */

	पूर्ण pclid_info_ग_लिखो;
पूर्ण pal_cache_line_id_u_t;

#घोषणा pclid_पढ़ो_part		pclid_info_पढ़ो.part
#घोषणा pclid_पढ़ो_way		pclid_info_पढ़ो.way
#घोषणा pclid_पढ़ो_level	pclid_info_पढ़ो.level
#घोषणा pclid_पढ़ो_cache_type	pclid_info_पढ़ो.cache_type

#घोषणा pclid_ग_लिखो_trigger	pclid_info_ग_लिखो.trigger
#घोषणा pclid_ग_लिखो_length	pclid_info_ग_लिखो.length
#घोषणा pclid_ग_लिखो_start	pclid_info_ग_लिखो.start
#घोषणा pclid_ग_लिखो_mesi	pclid_info_ग_लिखो.mesi
#घोषणा pclid_ग_लिखो_part	pclid_info_ग_लिखो.part
#घोषणा pclid_ग_लिखो_way		pclid_info_ग_लिखो.way
#घोषणा pclid_ग_लिखो_level	pclid_info_ग_लिखो.level
#घोषणा pclid_ग_लिखो_cache_type	pclid_info_ग_लिखो.cache_type

/* Processor cache line part encodings */
#घोषणा PAL_CACHE_LINE_ID_PART_DATA		0	/* Data */
#घोषणा PAL_CACHE_LINE_ID_PART_TAG		1	/* Tag */
#घोषणा PAL_CACHE_LINE_ID_PART_DATA_PROT	2	/* Data protection */
#घोषणा PAL_CACHE_LINE_ID_PART_TAG_PROT		3	/* Tag protection */
#घोषणा PAL_CACHE_LINE_ID_PART_DATA_TAG_PROT	4	/* Data+tag
							 * protection
							 */
प्रकार काष्ठा pal_cache_line_info_s अणु
	pal_status_t		pcli_status;		/* Return status of the पढ़ो cache line
							 * info call.
							 */
	u64			pcli_data;		/* 64-bit data, tag, protection bits .. */
	u64			pcli_data_len;		/* data length in bits */
	pal_cache_line_state_t	pcli_cache_line_state;	/* mesi state */

पूर्ण pal_cache_line_info_t;


/* Machine Check related crap */

/* Pending event status bits  */
प्रकार u64					pal_mc_pending_events_t;

#घोषणा PAL_MC_PENDING_MCA			(1 << 0)
#घोषणा PAL_MC_PENDING_INIT			(1 << 1)

/* Error inक्रमmation type */
प्रकार u64					pal_mc_info_index_t;

#घोषणा PAL_MC_INFO_PROCESSOR			0	/* Processor */
#घोषणा PAL_MC_INFO_CACHE_CHECK			1	/* Cache check */
#घोषणा PAL_MC_INFO_TLB_CHECK			2	/* Tlb check */
#घोषणा PAL_MC_INFO_BUS_CHECK			3	/* Bus check */
#घोषणा PAL_MC_INFO_REQ_ADDR			4	/* Requestor address */
#घोषणा PAL_MC_INFO_RESP_ADDR			5	/* Responder address */
#घोषणा PAL_MC_INFO_TARGET_ADDR			6	/* Target address */
#घोषणा PAL_MC_INFO_IMPL_DEP			7	/* Implementation
							 * dependent
							 */

#घोषणा PAL_TLB_CHECK_OP_PURGE			8

प्रकार काष्ठा pal_process_state_info_s अणु
	u64		reserved1	: 2,
			rz		: 1,	/* PAL_CHECK processor
						 * rendezvous
						 * successful.
						 */

			ra		: 1,	/* PAL_CHECK attempted
						 * a rendezvous.
						 */
			me		: 1,	/* Distinct multiple
						 * errors occurred
						 */

			mn		: 1,	/* Min. state save
						 * area has been
						 * रेजिस्टरed with PAL
						 */

			sy		: 1,	/* Storage पूर्णांकegrity
						 * synched
						 */


			co		: 1,	/* Continuable */
			ci		: 1,	/* MC isolated */
			us		: 1,	/* Uncontained storage
						 * damage.
						 */


			hd		: 1,	/* Non-essential hw
						 * lost (no loss of
						 * functionality)
						 * causing the
						 * processor to run in
						 * degraded mode.
						 */

			tl		: 1,	/* 1 => MC occurred
						 * after an instr was
						 * executed but beक्रमe
						 * the trap that
						 * resulted from instr
						 * execution was
						 * generated.
						 * (Trap Lost )
						 */
			mi		: 1,	/* More inक्रमmation available
						 * call PAL_MC_ERROR_INFO
						 */
			pi		: 1,	/* Precise inकाष्ठाion poपूर्णांकer */
			pm		: 1,	/* Precise min-state save area */

			dy		: 1,	/* Processor dynamic
						 * state valid
						 */


			in		: 1,	/* 0 = MC, 1 = INIT */
			rs		: 1,	/* RSE valid */
			cm		: 1,	/* MC corrected */
			ex		: 1,	/* MC is expected */
			cr		: 1,	/* Control regs valid*/
			pc		: 1,	/* Perf cntrs valid */
			dr		: 1,	/* Debug regs valid */
			tr		: 1,	/* Translation regs
						 * valid
						 */
			rr		: 1,	/* Region regs valid */
			ar		: 1,	/* App regs valid */
			br		: 1,	/* Branch regs valid */
			pr		: 1,	/* Predicate रेजिस्टरs
						 * valid
						 */

			fp		: 1,	/* fp रेजिस्टरs valid*/
			b1		: 1,	/* Preserved bank one
						 * general रेजिस्टरs
						 * are valid
						 */
			b0		: 1,	/* Preserved bank zero
						 * general रेजिस्टरs
						 * are valid
						 */
			gr		: 1,	/* General रेजिस्टरs
						 * are valid
						 * (excl. banked regs)
						 */
			dsize		: 16,	/* size of dynamic
						 * state वापसed
						 * by the processor
						 */

			se		: 1,	/* Shared error.  MCA in a
						   shared काष्ठाure */
			reserved2	: 10,
			cc		: 1,	/* Cache check */
			tc		: 1,	/* TLB check */
			bc		: 1,	/* Bus check */
			rc		: 1,	/* Register file check */
			uc		: 1;	/* Uarch check */

पूर्ण pal_processor_state_info_t;

प्रकार काष्ठा pal_cache_check_info_s अणु
	u64		op		: 4,	/* Type of cache
						 * operation that
						 * caused the machine
						 * check.
						 */
			level		: 2,	/* Cache level */
			reserved1	: 2,
			dl		: 1,	/* Failure in data part
						 * of cache line
						 */
			tl		: 1,	/* Failure in tag part
						 * of cache line
						 */
			dc		: 1,	/* Failure in dcache */
			ic		: 1,	/* Failure in icache */
			mesi		: 3,	/* Cache line state */
			mv		: 1,	/* mesi valid */
			way		: 5,	/* Way in which the
						 * error occurred
						 */
			wiv		: 1,	/* Way field valid */
			reserved2	: 1,
			dp		: 1,	/* Data poisoned on MBE */
			reserved3	: 6,
			hlth		: 2,	/* Health indicator */

			index		: 20,	/* Cache line index */
			reserved4	: 2,

			is		: 1,	/* inकाष्ठाion set (1 == ia32) */
			iv		: 1,	/* inकाष्ठाion set field valid */
			pl		: 2,	/* privilege level */
			pv		: 1,	/* privilege level field valid */
			mcc		: 1,	/* Machine check corrected */
			tv		: 1,	/* Target address
						 * काष्ठाure is valid
						 */
			rq		: 1,	/* Requester identअगरier
						 * काष्ठाure is valid
						 */
			rp		: 1,	/* Responder identअगरier
						 * काष्ठाure is valid
						 */
			pi		: 1;	/* Precise inकाष्ठाion poपूर्णांकer
						 * काष्ठाure is valid
						 */
पूर्ण pal_cache_check_info_t;

प्रकार काष्ठा pal_tlb_check_info_s अणु

	u64		tr_slot		: 8,	/* Slot# of TR where
						 * error occurred
						 */
			trv		: 1,	/* tr_slot field is valid */
			reserved1	: 1,
			level		: 2,	/* TLB level where failure occurred */
			reserved2	: 4,
			dtr		: 1,	/* Fail in data TR */
			itr		: 1,	/* Fail in inst TR */
			dtc		: 1,	/* Fail in data TC */
			itc		: 1,	/* Fail in inst. TC */
			op		: 4,	/* Cache operation */
			reserved3	: 6,
			hlth		: 2,	/* Health indicator */
			reserved4	: 22,

			is		: 1,	/* inकाष्ठाion set (1 == ia32) */
			iv		: 1,	/* inकाष्ठाion set field valid */
			pl		: 2,	/* privilege level */
			pv		: 1,	/* privilege level field valid */
			mcc		: 1,	/* Machine check corrected */
			tv		: 1,	/* Target address
						 * काष्ठाure is valid
						 */
			rq		: 1,	/* Requester identअगरier
						 * काष्ठाure is valid
						 */
			rp		: 1,	/* Responder identअगरier
						 * काष्ठाure is valid
						 */
			pi		: 1;	/* Precise inकाष्ठाion poपूर्णांकer
						 * काष्ठाure is valid
						 */
पूर्ण pal_tlb_check_info_t;

प्रकार काष्ठा pal_bus_check_info_s अणु
	u64		size		: 5,	/* Xaction size */
			ib		: 1,	/* Internal bus error */
			eb		: 1,	/* External bus error */
			cc		: 1,	/* Error occurred
						 * during cache-cache
						 * transfer.
						 */
			type		: 8,	/* Bus xaction type*/
			sev		: 5,	/* Bus error severity*/
			hier		: 2,	/* Bus hierarchy level */
			dp		: 1,	/* Data poisoned on MBE */
			bsi		: 8,	/* Bus error status
						 * info
						 */
			reserved2	: 22,

			is		: 1,	/* inकाष्ठाion set (1 == ia32) */
			iv		: 1,	/* inकाष्ठाion set field valid */
			pl		: 2,	/* privilege level */
			pv		: 1,	/* privilege level field valid */
			mcc		: 1,	/* Machine check corrected */
			tv		: 1,	/* Target address
						 * काष्ठाure is valid
						 */
			rq		: 1,	/* Requester identअगरier
						 * काष्ठाure is valid
						 */
			rp		: 1,	/* Responder identअगरier
						 * काष्ठाure is valid
						 */
			pi		: 1;	/* Precise inकाष्ठाion poपूर्णांकer
						 * काष्ठाure is valid
						 */
पूर्ण pal_bus_check_info_t;

प्रकार काष्ठा pal_reg_file_check_info_s अणु
	u64		id		: 4,	/* Register file identअगरier */
			op		: 4,	/* Type of रेजिस्टर
						 * operation that
						 * caused the machine
						 * check.
						 */
			reg_num		: 7,	/* Register number */
			rnv		: 1,	/* reg_num valid */
			reserved2	: 38,

			is		: 1,	/* inकाष्ठाion set (1 == ia32) */
			iv		: 1,	/* inकाष्ठाion set field valid */
			pl		: 2,	/* privilege level */
			pv		: 1,	/* privilege level field valid */
			mcc		: 1,	/* Machine check corrected */
			reserved3	: 3,
			pi		: 1;	/* Precise inकाष्ठाion poपूर्णांकer
						 * काष्ठाure is valid
						 */
पूर्ण pal_reg_file_check_info_t;

प्रकार काष्ठा pal_uarch_check_info_s अणु
	u64		sid		: 5,	/* Structure identअगरication */
			level		: 3,	/* Level of failure */
			array_id	: 4,	/* Array identअगरication */
			op		: 4,	/* Type of
						 * operation that
						 * caused the machine
						 * check.
						 */
			way		: 6,	/* Way of काष्ठाure */
			wv		: 1,	/* way valid */
			xv		: 1,	/* index valid */
			reserved1	: 6,
			hlth		: 2,	/* Health indicator */
			index		: 8,	/* Index or set of the uarch
						 * काष्ठाure that failed.
						 */
			reserved2	: 24,

			is		: 1,	/* inकाष्ठाion set (1 == ia32) */
			iv		: 1,	/* inकाष्ठाion set field valid */
			pl		: 2,	/* privilege level */
			pv		: 1,	/* privilege level field valid */
			mcc		: 1,	/* Machine check corrected */
			tv		: 1,	/* Target address
						 * काष्ठाure is valid
						 */
			rq		: 1,	/* Requester identअगरier
						 * काष्ठाure is valid
						 */
			rp		: 1,	/* Responder identअगरier
						 * काष्ठाure is valid
						 */
			pi		: 1;	/* Precise inकाष्ठाion poपूर्णांकer
						 * काष्ठाure is valid
						 */
पूर्ण pal_uarch_check_info_t;

प्रकार जोड़ pal_mc_error_info_u अणु
	u64				pmei_data;
	pal_processor_state_info_t	pme_processor;
	pal_cache_check_info_t		pme_cache;
	pal_tlb_check_info_t		pme_tlb;
	pal_bus_check_info_t		pme_bus;
	pal_reg_file_check_info_t	pme_reg_file;
	pal_uarch_check_info_t		pme_uarch;
पूर्ण pal_mc_error_info_t;

#घोषणा pmci_proc_unknown_check			pme_processor.uc
#घोषणा pmci_proc_bus_check			pme_processor.bc
#घोषणा pmci_proc_tlb_check			pme_processor.tc
#घोषणा pmci_proc_cache_check			pme_processor.cc
#घोषणा pmci_proc_dynamic_state_size		pme_processor.dsize
#घोषणा pmci_proc_gpr_valid			pme_processor.gr
#घोषणा pmci_proc_preserved_bank0_gpr_valid	pme_processor.b0
#घोषणा pmci_proc_preserved_bank1_gpr_valid	pme_processor.b1
#घोषणा pmci_proc_fp_valid			pme_processor.fp
#घोषणा pmci_proc_predicate_regs_valid		pme_processor.pr
#घोषणा pmci_proc_branch_regs_valid		pme_processor.br
#घोषणा pmci_proc_app_regs_valid		pme_processor.ar
#घोषणा pmci_proc_region_regs_valid		pme_processor.rr
#घोषणा pmci_proc_translation_regs_valid	pme_processor.tr
#घोषणा pmci_proc_debug_regs_valid		pme_processor.dr
#घोषणा pmci_proc_perf_counters_valid		pme_processor.pc
#घोषणा pmci_proc_control_regs_valid		pme_processor.cr
#घोषणा pmci_proc_machine_check_expected	pme_processor.ex
#घोषणा pmci_proc_machine_check_corrected	pme_processor.cm
#घोषणा pmci_proc_rse_valid			pme_processor.rs
#घोषणा pmci_proc_machine_check_or_init		pme_processor.in
#घोषणा pmci_proc_dynamic_state_valid		pme_processor.dy
#घोषणा pmci_proc_operation			pme_processor.op
#घोषणा pmci_proc_trap_lost			pme_processor.tl
#घोषणा pmci_proc_hardware_damage		pme_processor.hd
#घोषणा pmci_proc_uncontained_storage_damage	pme_processor.us
#घोषणा pmci_proc_machine_check_isolated	pme_processor.ci
#घोषणा pmci_proc_continuable			pme_processor.co
#घोषणा pmci_proc_storage_पूर्णांकergrity_synced	pme_processor.sy
#घोषणा pmci_proc_min_state_save_area_regd	pme_processor.mn
#घोषणा	pmci_proc_distinct_multiple_errors	pme_processor.me
#घोषणा pmci_proc_pal_attempted_rendezvous	pme_processor.ra
#घोषणा pmci_proc_pal_rendezvous_complete	pme_processor.rz


#घोषणा pmci_cache_level			pme_cache.level
#घोषणा pmci_cache_line_state			pme_cache.mesi
#घोषणा pmci_cache_line_state_valid		pme_cache.mv
#घोषणा pmci_cache_line_index			pme_cache.index
#घोषणा pmci_cache_instr_cache_fail		pme_cache.ic
#घोषणा pmci_cache_data_cache_fail		pme_cache.dc
#घोषणा pmci_cache_line_tag_fail		pme_cache.tl
#घोषणा pmci_cache_line_data_fail		pme_cache.dl
#घोषणा pmci_cache_operation			pme_cache.op
#घोषणा pmci_cache_way_valid			pme_cache.wv
#घोषणा pmci_cache_target_address_valid		pme_cache.tv
#घोषणा pmci_cache_way				pme_cache.way
#घोषणा pmci_cache_mc				pme_cache.mc

#घोषणा pmci_tlb_instr_translation_cache_fail	pme_tlb.itc
#घोषणा pmci_tlb_data_translation_cache_fail	pme_tlb.dtc
#घोषणा pmci_tlb_instr_translation_reg_fail	pme_tlb.itr
#घोषणा pmci_tlb_data_translation_reg_fail	pme_tlb.dtr
#घोषणा pmci_tlb_translation_reg_slot		pme_tlb.tr_slot
#घोषणा pmci_tlb_mc				pme_tlb.mc

#घोषणा pmci_bus_status_info			pme_bus.bsi
#घोषणा pmci_bus_req_address_valid		pme_bus.rq
#घोषणा pmci_bus_resp_address_valid		pme_bus.rp
#घोषणा pmci_bus_target_address_valid		pme_bus.tv
#घोषणा pmci_bus_error_severity			pme_bus.sev
#घोषणा pmci_bus_transaction_type		pme_bus.type
#घोषणा pmci_bus_cache_cache_transfer		pme_bus.cc
#घोषणा pmci_bus_transaction_size		pme_bus.size
#घोषणा pmci_bus_पूर्णांकernal_error			pme_bus.ib
#घोषणा pmci_bus_बाह्यal_error			pme_bus.eb
#घोषणा pmci_bus_mc				pme_bus.mc

/*
 * NOTE: this min_state_save area काष्ठा only includes the 1KB
 * architectural state save area.  The other 3 KB is scratch space
 * क्रम PAL.
 */

काष्ठा pal_min_state_area अणु
	u64	pmsa_nat_bits;		/* nat bits क्रम saved GRs  */
	u64	pmsa_gr[15];		/* GR1	- GR15		   */
	u64	pmsa_bank0_gr[16];	/* GR16 - GR31		   */
	u64	pmsa_bank1_gr[16];	/* GR16 - GR31		   */
	u64	pmsa_pr;		/* predicate रेजिस्टरs	   */
	u64	pmsa_br0;		/* branch रेजिस्टर 0	   */
	u64	pmsa_rsc;		/* ar.rsc		   */
	u64	pmsa_iip;		/* cr.iip		   */
	u64	pmsa_ipsr;		/* cr.ipsr		   */
	u64	pmsa_अगरs;		/* cr.अगरs		   */
	u64	pmsa_xip;		/* previous iip		   */
	u64	pmsa_xpsr;		/* previous psr		   */
	u64	pmsa_xfs;		/* previous अगरs		   */
	u64	pmsa_br1;		/* branch रेजिस्टर 1	   */
	u64	pmsa_reserved[70];	/* pal_min_state_area should total to 1KB */
पूर्ण;


काष्ठा ia64_pal_retval अणु
	/*
	 * A zero status value indicates call completed without error.
	 * A negative status value indicates reason of call failure.
	 * A positive status value indicates success but an
	 * inक्रमmational value should be prपूर्णांकed (e.g., "reboot क्रम
	 * change to take effect").
	 */
	s64 status;
	u64 v0;
	u64 v1;
	u64 v2;
पूर्ण;

/*
 * Note: Currently unused PAL arguments are generally labeled
 * "reserved" so the value specअगरied in the PAL करोcumentation
 * (generally 0) MUST be passed.  Reserved parameters are not optional
 * parameters.
 */
बाह्य काष्ठा ia64_pal_retval ia64_pal_call_अटल (u64, u64, u64, u64);
बाह्य काष्ठा ia64_pal_retval ia64_pal_call_stacked (u64, u64, u64, u64);
बाह्य काष्ठा ia64_pal_retval ia64_pal_call_phys_अटल (u64, u64, u64, u64);
बाह्य काष्ठा ia64_pal_retval ia64_pal_call_phys_stacked (u64, u64, u64, u64);
बाह्य व्योम ia64_save_scratch_fpregs (काष्ठा ia64_fpreg *);
बाह्य व्योम ia64_load_scratch_fpregs (काष्ठा ia64_fpreg *);

#घोषणा PAL_CALL(iprv,a0,a1,a2,a3) करो अणु			\
	काष्ठा ia64_fpreg fr[6];			\
	ia64_save_scratch_fpregs(fr);			\
	iprv = ia64_pal_call_अटल(a0, a1, a2, a3);	\
	ia64_load_scratch_fpregs(fr);			\
पूर्ण जबतक (0)

#घोषणा PAL_CALL_STK(iprv,a0,a1,a2,a3) करो अणु		\
	काष्ठा ia64_fpreg fr[6];			\
	ia64_save_scratch_fpregs(fr);			\
	iprv = ia64_pal_call_stacked(a0, a1, a2, a3);	\
	ia64_load_scratch_fpregs(fr);			\
पूर्ण जबतक (0)

#घोषणा PAL_CALL_PHYS(iprv,a0,a1,a2,a3) करो अणु			\
	काष्ठा ia64_fpreg fr[6];				\
	ia64_save_scratch_fpregs(fr);				\
	iprv = ia64_pal_call_phys_अटल(a0, a1, a2, a3);	\
	ia64_load_scratch_fpregs(fr);				\
पूर्ण जबतक (0)

#घोषणा PAL_CALL_PHYS_STK(iprv,a0,a1,a2,a3) करो अणु		\
	काष्ठा ia64_fpreg fr[6];				\
	ia64_save_scratch_fpregs(fr);				\
	iprv = ia64_pal_call_phys_stacked(a0, a1, a2, a3);	\
	ia64_load_scratch_fpregs(fr);				\
पूर्ण जबतक (0)

प्रकार पूर्णांक (*ia64_pal_handler) (u64, ...);
बाह्य ia64_pal_handler ia64_pal;
बाह्य व्योम ia64_pal_handler_init (व्योम *);

बाह्य ia64_pal_handler ia64_pal;

बाह्य pal_cache_config_info_t		l0d_cache_config_info;
बाह्य pal_cache_config_info_t		l0i_cache_config_info;
बाह्य pal_cache_config_info_t		l1_cache_config_info;
बाह्य pal_cache_config_info_t		l2_cache_config_info;

बाह्य pal_cache_protection_info_t	l0d_cache_protection_info;
बाह्य pal_cache_protection_info_t	l0i_cache_protection_info;
बाह्य pal_cache_protection_info_t	l1_cache_protection_info;
बाह्य pal_cache_protection_info_t	l2_cache_protection_info;

बाह्य pal_cache_config_info_t		pal_cache_config_info_get(pal_cache_level_t,
								  pal_cache_type_t);

बाह्य pal_cache_protection_info_t	pal_cache_protection_info_get(pal_cache_level_t,
								      pal_cache_type_t);


बाह्य व्योम				pal_error(पूर्णांक);


/* Useful wrappers क्रम the current list of pal procedures */

प्रकार जोड़ pal_bus_features_u अणु
	u64	pal_bus_features_val;
	काष्ठा अणु
		u64	pbf_reserved1				:	29;
		u64	pbf_req_bus_parking			:	1;
		u64	pbf_bus_lock_mask			:	1;
		u64	pbf_enable_half_xfer_rate		:	1;
		u64	pbf_reserved2				:	20;
		u64	pbf_enable_shared_line_replace		:	1;
		u64	pbf_enable_exclusive_line_replace	:	1;
		u64	pbf_disable_xaction_queueing		:	1;
		u64	pbf_disable_resp_err_check		:	1;
		u64	pbf_disable_berr_check			:	1;
		u64	pbf_disable_bus_req_पूर्णांकernal_err_संकेत	:	1;
		u64	pbf_disable_bus_req_berr_संकेत		:	1;
		u64	pbf_disable_bus_init_event_check	:	1;
		u64	pbf_disable_bus_init_event_संकेत	:	1;
		u64	pbf_disable_bus_addr_err_check		:	1;
		u64	pbf_disable_bus_addr_err_संकेत		:	1;
		u64	pbf_disable_bus_data_err_check		:	1;
	पूर्ण pal_bus_features_s;
पूर्ण pal_bus_features_u_t;

बाह्य व्योम pal_bus_features_prपूर्णांक (u64);

/* Provide inक्रमmation about configurable processor bus features */
अटल अंतरभूत s64
ia64_pal_bus_get_features (pal_bus_features_u_t *features_avail,
			   pal_bus_features_u_t *features_status,
			   pal_bus_features_u_t *features_control)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS(iprv, PAL_BUS_GET_FEATURES, 0, 0, 0);
	अगर (features_avail)
		features_avail->pal_bus_features_val = iprv.v0;
	अगर (features_status)
		features_status->pal_bus_features_val = iprv.v1;
	अगर (features_control)
		features_control->pal_bus_features_val = iprv.v2;
	वापस iprv.status;
पूर्ण

/* Enables/disables specअगरic processor bus features */
अटल अंतरभूत s64
ia64_pal_bus_set_features (pal_bus_features_u_t feature_select)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS(iprv, PAL_BUS_SET_FEATURES, feature_select.pal_bus_features_val, 0, 0);
	वापस iprv.status;
पूर्ण

/* Get detailed cache inक्रमmation */
अटल अंतरभूत s64
ia64_pal_cache_config_info (u64 cache_level, u64 cache_type, pal_cache_config_info_t *conf)
अणु
	काष्ठा ia64_pal_retval iprv;

	PAL_CALL(iprv, PAL_CACHE_INFO, cache_level, cache_type, 0);

	अगर (iprv.status == 0) अणु
		conf->pcci_status                 = iprv.status;
		conf->pcci_info_1.pcci1_data      = iprv.v0;
		conf->pcci_info_2.pcci2_data      = iprv.v1;
		conf->pcci_reserved               = iprv.v2;
	पूर्ण
	वापस iprv.status;

पूर्ण

/* Get detailed cche protection inक्रमmation */
अटल अंतरभूत s64
ia64_pal_cache_prot_info (u64 cache_level, u64 cache_type, pal_cache_protection_info_t *prot)
अणु
	काष्ठा ia64_pal_retval iprv;

	PAL_CALL(iprv, PAL_CACHE_PROT_INFO, cache_level, cache_type, 0);

	अगर (iprv.status == 0) अणु
		prot->pcpi_status           = iprv.status;
		prot->pcp_info[0].pcpi_data = iprv.v0 & 0xffffffff;
		prot->pcp_info[1].pcpi_data = iprv.v0 >> 32;
		prot->pcp_info[2].pcpi_data = iprv.v1 & 0xffffffff;
		prot->pcp_info[3].pcpi_data = iprv.v1 >> 32;
		prot->pcp_info[4].pcpi_data = iprv.v2 & 0xffffffff;
		prot->pcp_info[5].pcpi_data = iprv.v2 >> 32;
	पूर्ण
	वापस iprv.status;
पूर्ण

/*
 * Flush the processor inकाष्ठाion or data caches.  *PROGRESS must be
 * initialized to zero beक्रमe calling this क्रम the first समय..
 */
अटल अंतरभूत s64
ia64_pal_cache_flush (u64 cache_type, u64 invalidate, u64 *progress, u64 *vector)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_CACHE_FLUSH, cache_type, invalidate, *progress);
	अगर (vector)
		*vector = iprv.v0;
	*progress = iprv.v1;
	वापस iprv.status;
पूर्ण


/* Initialize the processor controlled caches */
अटल अंतरभूत s64
ia64_pal_cache_init (u64 level, u64 cache_type, u64 rest)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_CACHE_INIT, level, cache_type, rest);
	वापस iprv.status;
पूर्ण

/* Initialize the tags and data of a data or unअगरied cache line of
 * processor controlled cache to known values without the availability
 * of backing memory.
 */
अटल अंतरभूत s64
ia64_pal_cache_line_init (u64 physical_addr, u64 data_value)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_CACHE_LINE_INIT, physical_addr, data_value, 0);
	वापस iprv.status;
पूर्ण


/* Read the data and tag of a processor controlled cache line क्रम diags */
अटल अंतरभूत s64
ia64_pal_cache_पढ़ो (pal_cache_line_id_u_t line_id, u64 physical_addr)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS_STK(iprv, PAL_CACHE_READ, line_id.pclid_data,
				physical_addr, 0);
	वापस iprv.status;
पूर्ण

/* Return summary inक्रमmation about the hierarchy of caches controlled by the processor */
अटल अंतरभूत दीर्घ ia64_pal_cache_summary(अचिन्हित दीर्घ *cache_levels,
						अचिन्हित दीर्घ *unique_caches)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_CACHE_SUMMARY, 0, 0, 0);
	अगर (cache_levels)
		*cache_levels = iprv.v0;
	अगर (unique_caches)
		*unique_caches = iprv.v1;
	वापस iprv.status;
पूर्ण

/* Write the data and tag of a processor-controlled cache line क्रम diags */
अटल अंतरभूत s64
ia64_pal_cache_ग_लिखो (pal_cache_line_id_u_t line_id, u64 physical_addr, u64 data)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS_STK(iprv, PAL_CACHE_WRITE, line_id.pclid_data,
				physical_addr, data);
	वापस iprv.status;
पूर्ण


/* Return the parameters needed to copy relocatable PAL procedures from ROM to memory */
अटल अंतरभूत s64
ia64_pal_copy_info (u64 copy_type, u64 num_procs, u64 num_iopics,
		    u64 *buffer_size, u64 *buffer_align)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_COPY_INFO, copy_type, num_procs, num_iopics);
	अगर (buffer_size)
		*buffer_size = iprv.v0;
	अगर (buffer_align)
		*buffer_align = iprv.v1;
	वापस iprv.status;
पूर्ण

/* Copy relocatable PAL procedures from ROM to memory */
अटल अंतरभूत s64
ia64_pal_copy_pal (u64 target_addr, u64 alloc_size, u64 processor, u64 *pal_proc_offset)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_COPY_PAL, target_addr, alloc_size, processor);
	अगर (pal_proc_offset)
		*pal_proc_offset = iprv.v0;
	वापस iprv.status;
पूर्ण

/* Return the number of inकाष्ठाion and data debug रेजिस्टर pairs */
अटल अंतरभूत दीर्घ ia64_pal_debug_info(अचिन्हित दीर्घ *inst_regs,
						अचिन्हित दीर्घ *data_regs)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_DEBUG_INFO, 0, 0, 0);
	अगर (inst_regs)
		*inst_regs = iprv.v0;
	अगर (data_regs)
		*data_regs = iprv.v1;

	वापस iprv.status;
पूर्ण

#अगर_घोषित TBD
/* Switch from IA64-प्रणाली environment to IA-32 प्रणाली environment */
अटल अंतरभूत s64
ia64_pal_enter_ia32_env (ia32_env1, ia32_env2, ia32_env3)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_ENTER_IA_32_ENV, ia32_env1, ia32_env2, ia32_env3);
	वापस iprv.status;
पूर्ण
#पूर्ण_अगर

/* Get unique geographical address of this processor on its bus */
अटल अंतरभूत s64
ia64_pal_fixed_addr (u64 *global_unique_addr)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_FIXED_ADDR, 0, 0, 0);
	अगर (global_unique_addr)
		*global_unique_addr = iprv.v0;
	वापस iprv.status;
पूर्ण

/* Get base frequency of the platक्रमm अगर generated by the processor */
अटल अंतरभूत दीर्घ ia64_pal_freq_base(अचिन्हित दीर्घ *platक्रमm_base_freq)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_FREQ_BASE, 0, 0, 0);
	अगर (platक्रमm_base_freq)
		*platक्रमm_base_freq = iprv.v0;
	वापस iprv.status;
पूर्ण

/*
 * Get the ratios क्रम processor frequency, bus frequency and पूर्णांकerval समयr to
 * to base frequency of the platक्रमm
 */
अटल अंतरभूत s64
ia64_pal_freq_ratios (काष्ठा pal_freq_ratio *proc_ratio, काष्ठा pal_freq_ratio *bus_ratio,
		      काष्ठा pal_freq_ratio *itc_ratio)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_FREQ_RATIOS, 0, 0, 0);
	अगर (proc_ratio)
		*(u64 *)proc_ratio = iprv.v0;
	अगर (bus_ratio)
		*(u64 *)bus_ratio = iprv.v1;
	अगर (itc_ratio)
		*(u64 *)itc_ratio = iprv.v2;
	वापस iprv.status;
पूर्ण

/*
 * Get the current hardware resource sharing policy of the processor
 */
अटल अंतरभूत s64
ia64_pal_get_hw_policy (u64 proc_num, u64 *cur_policy, u64 *num_impacted,
			u64 *la)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_GET_HW_POLICY, proc_num, 0, 0);
	अगर (cur_policy)
		*cur_policy = iprv.v0;
	अगर (num_impacted)
		*num_impacted = iprv.v1;
	अगर (la)
		*la = iprv.v2;
	वापस iprv.status;
पूर्ण

/* Make the processor enter HALT or one of the implementation dependent low
 * घातer states where prefetching and execution are suspended and cache and
 * TLB coherency is not मुख्यtained.
 */
अटल अंतरभूत s64
ia64_pal_halt (u64 halt_state)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_HALT, halt_state, 0, 0);
	वापस iprv.status;
पूर्ण

प्रकार जोड़ pal_घातer_mgmt_info_u अणु
	u64			ppmi_data;
	काष्ठा अणु
	       u64		निकास_latency		: 16,
				entry_latency		: 16,
				घातer_consumption	: 28,
				im			: 1,
				co			: 1,
				reserved		: 2;
	पूर्ण pal_घातer_mgmt_info_s;
पूर्ण pal_घातer_mgmt_info_u_t;

/* Return inक्रमmation about processor's optional घातer management capabilities. */
अटल अंतरभूत s64
ia64_pal_halt_info (pal_घातer_mgmt_info_u_t *घातer_buf)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_STK(iprv, PAL_HALT_INFO, (अचिन्हित दीर्घ) घातer_buf, 0, 0);
	वापस iprv.status;
पूर्ण

/* Get the current P-state inक्रमmation */
अटल अंतरभूत s64
ia64_pal_get_pstate (u64 *pstate_index, अचिन्हित दीर्घ type)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_STK(iprv, PAL_GET_PSTATE, type, 0, 0);
	*pstate_index = iprv.v0;
	वापस iprv.status;
पूर्ण

/* Set the P-state */
अटल अंतरभूत s64
ia64_pal_set_pstate (u64 pstate_index)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_STK(iprv, PAL_SET_PSTATE, pstate_index, 0, 0);
	वापस iprv.status;
पूर्ण

/* Processor bअक्रमing inक्रमmation*/
अटल अंतरभूत s64
ia64_pal_get_bअक्रम_info (अक्षर *bअक्रम_info)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_STK(iprv, PAL_BRAND_INFO, 0, (u64)bअक्रम_info, 0);
	वापस iprv.status;
पूर्ण

/* Cause the processor to enter LIGHT HALT state, where prefetching and execution are
 * suspended, but cache and TLB coherency is मुख्यtained.
 */
अटल अंतरभूत s64
ia64_pal_halt_light (व्योम)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_HALT_LIGHT, 0, 0, 0);
	वापस iprv.status;
पूर्ण

/* Clear all the processor error logging   रेजिस्टरs and reset the indicator that allows
 * the error logging रेजिस्टरs to be written. This procedure also checks the pending
 * machine check bit and pending INIT bit and reports their states.
 */
अटल अंतरभूत s64
ia64_pal_mc_clear_log (u64 *pending_vector)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MC_CLEAR_LOG, 0, 0, 0);
	अगर (pending_vector)
		*pending_vector = iprv.v0;
	वापस iprv.status;
पूर्ण

/* Ensure that all outstanding transactions in a processor are completed or that any
 * MCA due to thes outstanding transaction is taken.
 */
अटल अंतरभूत s64
ia64_pal_mc_drain (व्योम)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MC_DRAIN, 0, 0, 0);
	वापस iprv.status;
पूर्ण

/* Return the machine check dynamic processor state */
अटल अंतरभूत s64
ia64_pal_mc_dynamic_state (u64 info_type, u64 dy_buffer, u64 *size)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MC_DYNAMIC_STATE, info_type, dy_buffer, 0);
	अगर (size)
		*size = iprv.v0;
	वापस iprv.status;
पूर्ण

/* Return processor machine check inक्रमmation */
अटल अंतरभूत s64
ia64_pal_mc_error_info (u64 info_index, u64 type_index, u64 *size, u64 *error_info)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MC_ERROR_INFO, info_index, type_index, 0);
	अगर (size)
		*size = iprv.v0;
	अगर (error_info)
		*error_info = iprv.v1;
	वापस iprv.status;
पूर्ण

/* Injects the requested processor error or वापसs info on
 * supported injection capabilities क्रम current processor implementation
 */
अटल अंतरभूत s64
ia64_pal_mc_error_inject_phys (u64 err_type_info, u64 err_काष्ठा_info,
			u64 err_data_buffer, u64 *capabilities, u64 *resources)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS_STK(iprv, PAL_MC_ERROR_INJECT, err_type_info,
			  err_काष्ठा_info, err_data_buffer);
	अगर (capabilities)
		*capabilities= iprv.v0;
	अगर (resources)
		*resources= iprv.v1;
	वापस iprv.status;
पूर्ण

अटल अंतरभूत s64
ia64_pal_mc_error_inject_virt (u64 err_type_info, u64 err_काष्ठा_info,
			u64 err_data_buffer, u64 *capabilities, u64 *resources)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_STK(iprv, PAL_MC_ERROR_INJECT, err_type_info,
			  err_काष्ठा_info, err_data_buffer);
	अगर (capabilities)
		*capabilities= iprv.v0;
	अगर (resources)
		*resources= iprv.v1;
	वापस iprv.status;
पूर्ण

/* Inक्रमm PALE_CHECK whether a machine check is expected so that PALE_CHECK willnot
 * attempt to correct any expected machine checks.
 */
अटल अंतरभूत s64
ia64_pal_mc_expected (u64 expected, u64 *previous)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MC_EXPECTED, expected, 0, 0);
	अगर (previous)
		*previous = iprv.v0;
	वापस iprv.status;
पूर्ण

प्रकार जोड़ pal_hw_tracking_u अणु
	u64			pht_data;
	काष्ठा अणु
		u64		itc	:4,	/* Inकाष्ठाion cache tracking */
				dct	:4,	/* Date cache tracking */
				itt	:4,	/* Inकाष्ठाion TLB tracking */
				ddt	:4,	/* Data TLB tracking */
				reserved:48;
	पूर्ण pal_hw_tracking_s;
पूर्ण pal_hw_tracking_u_t;

/*
 * Hardware tracking status.
 */
अटल अंतरभूत s64
ia64_pal_mc_hw_tracking (u64 *status)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MC_HW_TRACKING, 0, 0, 0);
	अगर (status)
		*status = iprv.v0;
	वापस iprv.status;
पूर्ण

/* Register a platक्रमm dependent location with PAL to which it can save
 * minimal processor state in the event of a machine check or initialization
 * event.
 */
अटल अंतरभूत s64
ia64_pal_mc_रेजिस्टर_mem (u64 physical_addr, u64 size, u64 *req_size)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MC_REGISTER_MEM, physical_addr, size, 0);
	अगर (req_size)
		*req_size = iprv.v0;
	वापस iprv.status;
पूर्ण

/* Restore minimal architectural processor state, set CMC पूर्णांकerrupt अगर necessary
 * and resume execution
 */
अटल अंतरभूत s64
ia64_pal_mc_resume (u64 set_cmci, u64 save_ptr)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MC_RESUME, set_cmci, save_ptr, 0);
	वापस iprv.status;
पूर्ण

/* Return the memory attributes implemented by the processor */
अटल अंतरभूत s64
ia64_pal_mem_attrib (u64 *mem_attrib)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MEM_ATTRIB, 0, 0, 0);
	अगर (mem_attrib)
		*mem_attrib = iprv.v0 & 0xff;
	वापस iprv.status;
पूर्ण

/* Return the amount of memory needed क्रम second phase of processor
 * self-test and the required alignment of memory.
 */
अटल अंतरभूत s64
ia64_pal_mem_क्रम_test (u64 *bytes_needed, u64 *alignment)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_MEM_FOR_TEST, 0, 0, 0);
	अगर (bytes_needed)
		*bytes_needed = iprv.v0;
	अगर (alignment)
		*alignment = iprv.v1;
	वापस iprv.status;
पूर्ण

प्रकार जोड़ pal_perf_mon_info_u अणु
	u64			  ppmi_data;
	काष्ठा अणु
	       u64		generic		: 8,
				width		: 8,
				cycles		: 8,
				retired		: 8,
				reserved	: 32;
	पूर्ण pal_perf_mon_info_s;
पूर्ण pal_perf_mon_info_u_t;

/* Return the perक्रमmance monitor inक्रमmation about what can be counted
 * and how to configure the monitors to count the desired events.
 */
अटल अंतरभूत s64
ia64_pal_perf_mon_info (u64 *pm_buffer, pal_perf_mon_info_u_t *pm_info)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_PERF_MON_INFO, (अचिन्हित दीर्घ) pm_buffer, 0, 0);
	अगर (pm_info)
		pm_info->ppmi_data = iprv.v0;
	वापस iprv.status;
पूर्ण

/* Specअगरies the physical address of the processor पूर्णांकerrupt block
 * and I/O port space.
 */
अटल अंतरभूत s64
ia64_pal_platक्रमm_addr (u64 type, u64 physical_addr)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_PLATFORM_ADDR, type, physical_addr, 0);
	वापस iprv.status;
पूर्ण

/* Set the SAL PMI entrypoपूर्णांक in memory */
अटल अंतरभूत s64
ia64_pal_pmi_entrypoपूर्णांक (u64 sal_pmi_entry_addr)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_PMI_ENTRYPOINT, sal_pmi_entry_addr, 0, 0);
	वापस iprv.status;
पूर्ण

काष्ठा pal_features_s;
/* Provide inक्रमmation about configurable processor features */
अटल अंतरभूत s64
ia64_pal_proc_get_features (u64 *features_avail,
			    u64 *features_status,
			    u64 *features_control,
			    u64 features_set)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS(iprv, PAL_PROC_GET_FEATURES, 0, features_set, 0);
	अगर (iprv.status == 0) अणु
		*features_avail   = iprv.v0;
		*features_status  = iprv.v1;
		*features_control = iprv.v2;
	पूर्ण
	वापस iprv.status;
पूर्ण

/* Enable/disable processor dependent features */
अटल अंतरभूत s64
ia64_pal_proc_set_features (u64 feature_select)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS(iprv, PAL_PROC_SET_FEATURES, feature_select, 0, 0);
	वापस iprv.status;
पूर्ण

/*
 * Put everything in a काष्ठा so we aव्योम the global offset table whenever
 * possible.
 */
प्रकार काष्ठा ia64_ptce_info_s अणु
	अचिन्हित दीर्घ	base;
	u32		count[2];
	u32		stride[2];
पूर्ण ia64_ptce_info_t;

/* Return the inक्रमmation required क्रम the architected loop used to purge
 * (initialize) the entire TC
 */
अटल अंतरभूत s64
ia64_get_ptce (ia64_ptce_info_t *ptce)
अणु
	काष्ठा ia64_pal_retval iprv;

	अगर (!ptce)
		वापस -1;

	PAL_CALL(iprv, PAL_PTCE_INFO, 0, 0, 0);
	अगर (iprv.status == 0) अणु
		ptce->base = iprv.v0;
		ptce->count[0] = iprv.v1 >> 32;
		ptce->count[1] = iprv.v1 & 0xffffffff;
		ptce->stride[0] = iprv.v2 >> 32;
		ptce->stride[1] = iprv.v2 & 0xffffffff;
	पूर्ण
	वापस iprv.status;
पूर्ण

/* Return info about implemented application and control रेजिस्टरs. */
अटल अंतरभूत s64
ia64_pal_रेजिस्टर_info (u64 info_request, u64 *reg_info_1, u64 *reg_info_2)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_REGISTER_INFO, info_request, 0, 0);
	अगर (reg_info_1)
		*reg_info_1 = iprv.v0;
	अगर (reg_info_2)
		*reg_info_2 = iprv.v1;
	वापस iprv.status;
पूर्ण

प्रकार जोड़ pal_hपूर्णांकs_u अणु
	अचिन्हित दीर्घ		ph_data;
	काष्ठा अणु
	       अचिन्हित दीर्घ	si		: 1,
				li		: 1,
				reserved	: 62;
	पूर्ण pal_hपूर्णांकs_s;
पूर्ण pal_hपूर्णांकs_u_t;

/* Return inक्रमmation about the रेजिस्टर stack and RSE क्रम this processor
 * implementation.
 */
अटल अंतरभूत दीर्घ ia64_pal_rse_info(अचिन्हित दीर्घ *num_phys_stacked,
							pal_hपूर्णांकs_u_t *hपूर्णांकs)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_RSE_INFO, 0, 0, 0);
	अगर (num_phys_stacked)
		*num_phys_stacked = iprv.v0;
	अगर (hपूर्णांकs)
		hपूर्णांकs->ph_data = iprv.v1;
	वापस iprv.status;
पूर्ण

/*
 * Set the current hardware resource sharing policy of the processor
 */
अटल अंतरभूत s64
ia64_pal_set_hw_policy (u64 policy)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_SET_HW_POLICY, policy, 0, 0);
	वापस iprv.status;
पूर्ण

/* Cause the processor to enter	SHUTDOWN state, where prefetching and execution are
 * suspended, but cause cache and TLB coherency to be मुख्यtained.
 * This is usually called in IA-32 mode.
 */
अटल अंतरभूत s64
ia64_pal_shutकरोwn (व्योम)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_SHUTDOWN, 0, 0, 0);
	वापस iprv.status;
पूर्ण

/* Perक्रमm the second phase of processor self-test. */
अटल अंतरभूत s64
ia64_pal_test_proc (u64 test_addr, u64 test_size, u64 attributes, u64 *self_test_state)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_TEST_PROC, test_addr, test_size, attributes);
	अगर (self_test_state)
		*self_test_state = iprv.v0;
	वापस iprv.status;
पूर्ण

प्रकार जोड़  pal_version_u अणु
	u64	pal_version_val;
	काष्ठा अणु
		u64	pv_pal_b_rev		:	8;
		u64	pv_pal_b_model		:	8;
		u64	pv_reserved1		:	8;
		u64	pv_pal_venकरोr		:	8;
		u64	pv_pal_a_rev		:	8;
		u64	pv_pal_a_model		:	8;
		u64	pv_reserved2		:	16;
	पूर्ण pal_version_s;
पूर्ण pal_version_u_t;


/*
 * Return PAL version inक्रमmation.  While the करोcumentation states that
 * PAL_VERSION can be called in either physical or भव mode, some
 * implementations only allow physical calls.  We करोn't call it very often,
 * so the overhead isn't worth eliminating.
 */
अटल अंतरभूत s64
ia64_pal_version (pal_version_u_t *pal_min_version, pal_version_u_t *pal_cur_version)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS(iprv, PAL_VERSION, 0, 0, 0);
	अगर (pal_min_version)
		pal_min_version->pal_version_val = iprv.v0;

	अगर (pal_cur_version)
		pal_cur_version->pal_version_val = iprv.v1;

	वापस iprv.status;
पूर्ण

प्रकार जोड़ pal_tc_info_u अणु
	u64			pti_val;
	काष्ठा अणु
	       u64		num_sets	:	8,
				associativity	:	8,
				num_entries	:	16,
				pf		:	1,
				unअगरied		:	1,
				reduce_tr	:	1,
				reserved	:	29;
	पूर्ण pal_tc_info_s;
पूर्ण pal_tc_info_u_t;

#घोषणा tc_reduce_tr		pal_tc_info_s.reduce_tr
#घोषणा tc_unअगरied		pal_tc_info_s.unअगरied
#घोषणा tc_pf			pal_tc_info_s.pf
#घोषणा tc_num_entries		pal_tc_info_s.num_entries
#घोषणा tc_associativity	pal_tc_info_s.associativity
#घोषणा tc_num_sets		pal_tc_info_s.num_sets


/* Return inक्रमmation about the भव memory अक्षरacteristics of the processor
 * implementation.
 */
अटल अंतरभूत s64
ia64_pal_vm_info (u64 tc_level, u64 tc_type,  pal_tc_info_u_t *tc_info, u64 *tc_pages)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_VM_INFO, tc_level, tc_type, 0);
	अगर (tc_info)
		tc_info->pti_val = iprv.v0;
	अगर (tc_pages)
		*tc_pages = iprv.v1;
	वापस iprv.status;
पूर्ण

/* Get page size inक्रमmation about the भव memory अक्षरacteristics of the processor
 * implementation.
 */
अटल अंतरभूत s64 ia64_pal_vm_page_size(u64 *tr_pages, u64 *vw_pages)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_VM_PAGE_SIZE, 0, 0, 0);
	अगर (tr_pages)
		*tr_pages = iprv.v0;
	अगर (vw_pages)
		*vw_pages = iprv.v1;
	वापस iprv.status;
पूर्ण

प्रकार जोड़ pal_vm_info_1_u अणु
	u64			pvi1_val;
	काष्ठा अणु
		u64		vw		: 1,
				phys_add_size	: 7,
				key_size	: 8,
				max_pkr		: 8,
				hash_tag_id	: 8,
				max_dtr_entry	: 8,
				max_itr_entry	: 8,
				max_unique_tcs	: 8,
				num_tc_levels	: 8;
	पूर्ण pal_vm_info_1_s;
पूर्ण pal_vm_info_1_u_t;

#घोषणा PAL_MAX_PURGES		0xFFFF		/* all ones is means unlimited */

प्रकार जोड़ pal_vm_info_2_u अणु
	u64			pvi2_val;
	काष्ठा अणु
		u64		impl_va_msb	: 8,
				rid_size	: 8,
				max_purges	: 16,
				reserved	: 32;
	पूर्ण pal_vm_info_2_s;
पूर्ण pal_vm_info_2_u_t;

/* Get summary inक्रमmation about the भव memory अक्षरacteristics of the processor
 * implementation.
 */
अटल अंतरभूत s64
ia64_pal_vm_summary (pal_vm_info_1_u_t *vm_info_1, pal_vm_info_2_u_t *vm_info_2)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_VM_SUMMARY, 0, 0, 0);
	अगर (vm_info_1)
		vm_info_1->pvi1_val = iprv.v0;
	अगर (vm_info_2)
		vm_info_2->pvi2_val = iprv.v1;
	वापस iprv.status;
पूर्ण

प्रकार जोड़ pal_vp_info_u अणु
	u64			pvi_val;
	काष्ठा अणु
		u64		index:		48,	/* भव feature set info */
				vmm_id:		16;	/* feature set id */
	पूर्ण pal_vp_info_s;
पूर्ण pal_vp_info_u_t;

/*
 * Returns inक्रमmation about भव processor features
 */
अटल अंतरभूत s64
ia64_pal_vp_info (u64 feature_set, u64 vp_buffer, u64 *vp_info, u64 *vmm_id)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_VP_INFO, feature_set, vp_buffer, 0);
	अगर (vp_info)
		*vp_info = iprv.v0;
	अगर (vmm_id)
		*vmm_id = iprv.v1;
	वापस iprv.status;
पूर्ण

प्रकार जोड़ pal_itr_valid_u अणु
	u64			piv_val;
	काष्ठा अणु
	       u64		access_rights_valid	: 1,
				priv_level_valid	: 1,
				dirty_bit_valid		: 1,
				mem_attr_valid		: 1,
				reserved		: 60;
	पूर्ण pal_tr_valid_s;
पूर्ण pal_tr_valid_u_t;

/* Read a translation रेजिस्टर */
अटल अंतरभूत s64
ia64_pal_tr_पढ़ो (u64 reg_num, u64 tr_type, u64 *tr_buffer, pal_tr_valid_u_t *tr_valid)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL_PHYS_STK(iprv, PAL_VM_TR_READ, reg_num, tr_type,(u64)ia64_tpa(tr_buffer));
	अगर (tr_valid)
		tr_valid->piv_val = iprv.v0;
	वापस iprv.status;
पूर्ण

/*
 * PAL_PREFETCH_VISIBILITY transaction types
 */
#घोषणा PAL_VISIBILITY_VIRTUAL		0
#घोषणा PAL_VISIBILITY_PHYSICAL		1

/*
 * PAL_PREFETCH_VISIBILITY वापस codes
 */
#घोषणा PAL_VISIBILITY_OK		1
#घोषणा PAL_VISIBILITY_OK_REMOTE_NEEDED	0
#घोषणा PAL_VISIBILITY_INVAL_ARG	-2
#घोषणा PAL_VISIBILITY_ERROR		-3

अटल अंतरभूत s64
ia64_pal_prefetch_visibility (s64 trans_type)
अणु
	काष्ठा ia64_pal_retval iprv;
	PAL_CALL(iprv, PAL_PREFETCH_VISIBILITY, trans_type, 0, 0);
	वापस iprv.status;
पूर्ण

/* data काष्ठाure क्रम getting inक्रमmation on logical to physical mappings */
प्रकार जोड़ pal_log_overview_u अणु
	काष्ठा अणु
		u64	num_log		:16,	/* Total number of logical
						 * processors on this die
						 */
			tpc		:8,	/* Thपढ़ोs per core */
			reserved3	:8,	/* Reserved */
			cpp		:8,	/* Cores per processor */
			reserved2	:8,	/* Reserved */
			ppid		:8,	/* Physical processor ID */
			reserved1	:8;	/* Reserved */
	पूर्ण overview_bits;
	u64 overview_data;
पूर्ण pal_log_overview_t;

प्रकार जोड़ pal_proc_n_log_info1_uअणु
	काष्ठा अणु
		u64	tid		:16,	/* Thपढ़ो id */
			reserved2	:16,	/* Reserved */
			cid		:16,	/* Core id */
			reserved1	:16;	/* Reserved */
	पूर्ण ppli1_bits;
	u64	ppli1_data;
पूर्ण pal_proc_n_log_info1_t;

प्रकार जोड़ pal_proc_n_log_info2_u अणु
	काष्ठा अणु
		u64	la		:16,	/* Logical address */
			reserved	:48;	/* Reserved */
	पूर्ण ppli2_bits;
	u64	ppli2_data;
पूर्ण pal_proc_n_log_info2_t;

प्रकार काष्ठा pal_logical_to_physical_s
अणु
	pal_log_overview_t overview;
	pal_proc_n_log_info1_t ppli1;
	pal_proc_n_log_info2_t ppli2;
पूर्ण pal_logical_to_physical_t;

#घोषणा overview_num_log	overview.overview_bits.num_log
#घोषणा overview_tpc		overview.overview_bits.tpc
#घोषणा overview_cpp		overview.overview_bits.cpp
#घोषणा overview_ppid		overview.overview_bits.ppid
#घोषणा log1_tid		ppli1.ppli1_bits.tid
#घोषणा log1_cid		ppli1.ppli1_bits.cid
#घोषणा log2_la			ppli2.ppli2_bits.la

/* Get inक्रमmation on logical to physical processor mappings. */
अटल अंतरभूत s64
ia64_pal_logical_to_phys(u64 proc_number, pal_logical_to_physical_t *mapping)
अणु
	काष्ठा ia64_pal_retval iprv;

	PAL_CALL(iprv, PAL_LOGICAL_TO_PHYSICAL, proc_number, 0, 0);

	अगर (iprv.status == PAL_STATUS_SUCCESS)
	अणु
		mapping->overview.overview_data = iprv.v0;
		mapping->ppli1.ppli1_data = iprv.v1;
		mapping->ppli2.ppli2_data = iprv.v2;
	पूर्ण

	वापस iprv.status;
पूर्ण

प्रकार काष्ठा pal_cache_shared_info_s
अणु
	u64 num_shared;
	pal_proc_n_log_info1_t ppli1;
	pal_proc_n_log_info2_t ppli2;
पूर्ण pal_cache_shared_info_t;

/* Get inक्रमmation on logical to physical processor mappings. */
अटल अंतरभूत s64
ia64_pal_cache_shared_info(u64 level,
		u64 type,
		u64 proc_number,
		pal_cache_shared_info_t *info)
अणु
	काष्ठा ia64_pal_retval iprv;

	PAL_CALL(iprv, PAL_CACHE_SHARED_INFO, level, type, proc_number);

	अगर (iprv.status == PAL_STATUS_SUCCESS) अणु
		info->num_shared = iprv.v0;
		info->ppli1.ppli1_data = iprv.v1;
		info->ppli2.ppli2_data = iprv.v2;
	पूर्ण

	वापस iprv.status;
पूर्ण
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_IA64_PAL_H */
