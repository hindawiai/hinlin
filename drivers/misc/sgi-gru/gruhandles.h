<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SN Platक्रमm GRU Driver
 *
 *              GRU HANDLE DEFINITION
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#अगर_अघोषित __GRUHANDLES_H__
#घोषणा __GRUHANDLES_H__
#समावेश "gru_instructions.h"

/*
 * Manअगरest स्थिरants क्रम GRU Memory Map
 */
#घोषणा GRU_GSEG0_BASE		0
#घोषणा GRU_MCS_BASE		(64 * 1024 * 1024)
#घोषणा GRU_SIZE		(128UL * 1024 * 1024)

/* Handle & resource counts */
#घोषणा GRU_NUM_CB		128
#घोषणा GRU_NUM_DSR_BYTES	(32 * 1024)
#घोषणा GRU_NUM_TFM		16
#घोषणा GRU_NUM_TGH		24
#घोषणा GRU_NUM_CBE		128
#घोषणा GRU_NUM_TFH		128
#घोषणा GRU_NUM_CCH		16

/* Maximum resource counts that can be reserved by user programs */
#घोषणा GRU_NUM_USER_CBR	GRU_NUM_CBE
#घोषणा GRU_NUM_USER_DSR_BYTES	GRU_NUM_DSR_BYTES

/* Bytes per handle & handle stride. Code assumes all cb, tfh, cbe handles
 * are the same */
#घोषणा GRU_HANDLE_BYTES	64
#घोषणा GRU_HANDLE_STRIDE	256

/* Base addresses of handles */
#घोषणा GRU_TFM_BASE		(GRU_MCS_BASE + 0x00000)
#घोषणा GRU_TGH_BASE		(GRU_MCS_BASE + 0x08000)
#घोषणा GRU_CBE_BASE		(GRU_MCS_BASE + 0x10000)
#घोषणा GRU_TFH_BASE		(GRU_MCS_BASE + 0x18000)
#घोषणा GRU_CCH_BASE		(GRU_MCS_BASE + 0x20000)

/* User gseg स्थिरants */
#घोषणा GRU_GSEG_STRIDE		(4 * 1024 * 1024)
#घोषणा GSEG_BASE(a)		((a) & ~(GRU_GSEG_PAGESIZE - 1))

/* Data segment स्थिरants */
#घोषणा GRU_DSR_AU_BYTES	1024
#घोषणा GRU_DSR_CL		(GRU_NUM_DSR_BYTES / GRU_CACHE_LINE_BYTES)
#घोषणा GRU_DSR_AU_CL		(GRU_DSR_AU_BYTES / GRU_CACHE_LINE_BYTES)
#घोषणा GRU_DSR_AU		(GRU_NUM_DSR_BYTES / GRU_DSR_AU_BYTES)

/* Control block स्थिरants */
#घोषणा GRU_CBR_AU_SIZE		2
#घोषणा GRU_CBR_AU		(GRU_NUM_CBE / GRU_CBR_AU_SIZE)

/* Convert resource counts to the number of AU */
#घोषणा GRU_DS_BYTES_TO_AU(n)	DIV_ROUND_UP(n, GRU_DSR_AU_BYTES)
#घोषणा GRU_CB_COUNT_TO_AU(n)	DIV_ROUND_UP(n, GRU_CBR_AU_SIZE)

/* UV limits */
#घोषणा GRU_CHIPLETS_PER_HUB	2
#घोषणा GRU_HUBS_PER_BLADE	1
#घोषणा GRU_CHIPLETS_PER_BLADE	(GRU_HUBS_PER_BLADE * GRU_CHIPLETS_PER_HUB)

/* User GRU Gseg offsets */
#घोषणा GRU_CB_BASE		0
#घोषणा GRU_CB_LIMIT		(GRU_CB_BASE + GRU_HANDLE_STRIDE * GRU_NUM_CBE)
#घोषणा GRU_DS_BASE		0x20000
#घोषणा GRU_DS_LIMIT		(GRU_DS_BASE + GRU_NUM_DSR_BYTES)

/* Convert a GRU physical address to the chiplet offset */
#घोषणा GSEGPOFF(h) 		((h) & (GRU_SIZE - 1))

/* Convert an arbitrary handle address to the beginning of the GRU segment */
#घोषणा GRUBASE(h)		((व्योम *)((अचिन्हित दीर्घ)(h) & ~(GRU_SIZE - 1)))

/* Test a valid handle address to determine the type */
#घोषणा TYPE_IS(hn, h)		((h) >= GRU_##hn##_BASE && (h) <	\
		GRU_##hn##_BASE + GRU_NUM_##hn * GRU_HANDLE_STRIDE &&   \
		(((h) & (GRU_HANDLE_STRIDE - 1)) == 0))


/* General addressing macros. */
अटल अंतरभूत व्योम *get_gseg_base_address(व्योम *base, पूर्णांक ctxnum)
अणु
	वापस (व्योम *)(base + GRU_GSEG0_BASE + GRU_GSEG_STRIDE * ctxnum);
पूर्ण

अटल अंतरभूत व्योम *get_gseg_base_address_cb(व्योम *base, पूर्णांक ctxnum, पूर्णांक line)
अणु
	वापस (व्योम *)(get_gseg_base_address(base, ctxnum) +
			GRU_CB_BASE + GRU_HANDLE_STRIDE * line);
पूर्ण

अटल अंतरभूत व्योम *get_gseg_base_address_ds(व्योम *base, पूर्णांक ctxnum, पूर्णांक line)
अणु
	वापस (व्योम *)(get_gseg_base_address(base, ctxnum) + GRU_DS_BASE +
			GRU_CACHE_LINE_BYTES * line);
पूर्ण

अटल अंतरभूत काष्ठा gru_tlb_fault_map *get_tfm(व्योम *base, पूर्णांक ctxnum)
अणु
	वापस (काष्ठा gru_tlb_fault_map *)(base + GRU_TFM_BASE +
					ctxnum * GRU_HANDLE_STRIDE);
पूर्ण

अटल अंतरभूत काष्ठा gru_tlb_global_handle *get_tgh(व्योम *base, पूर्णांक ctxnum)
अणु
	वापस (काष्ठा gru_tlb_global_handle *)(base + GRU_TGH_BASE +
					ctxnum * GRU_HANDLE_STRIDE);
पूर्ण

अटल अंतरभूत काष्ठा gru_control_block_extended *get_cbe(व्योम *base, पूर्णांक ctxnum)
अणु
	वापस (काष्ठा gru_control_block_extended *)(base + GRU_CBE_BASE +
					ctxnum * GRU_HANDLE_STRIDE);
पूर्ण

अटल अंतरभूत काष्ठा gru_tlb_fault_handle *get_tfh(व्योम *base, पूर्णांक ctxnum)
अणु
	वापस (काष्ठा gru_tlb_fault_handle *)(base + GRU_TFH_BASE +
					ctxnum * GRU_HANDLE_STRIDE);
पूर्ण

अटल अंतरभूत काष्ठा gru_context_configuration_handle *get_cch(व्योम *base,
					पूर्णांक ctxnum)
अणु
	वापस (काष्ठा gru_context_configuration_handle *)(base +
				GRU_CCH_BASE + ctxnum * GRU_HANDLE_STRIDE);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_cb_number(व्योम *cb)
अणु
	वापस (((अचिन्हित दीर्घ)cb - GRU_CB_BASE) % GRU_GSEG_PAGESIZE) /
					GRU_HANDLE_STRIDE;
पूर्ण

/* byte offset to a specअगरic GRU chiplet. (p=pnode, c=chiplet (0 or 1)*/
अटल अंतरभूत अचिन्हित दीर्घ gru_chiplet_paddr(अचिन्हित दीर्घ paddr, पूर्णांक pnode,
							पूर्णांक chiplet)
अणु
	वापस paddr + GRU_SIZE * (2 * pnode  + chiplet);
पूर्ण

अटल अंतरभूत व्योम *gru_chiplet_vaddr(व्योम *vaddr, पूर्णांक pnode, पूर्णांक chiplet)
अणु
	वापस vaddr + GRU_SIZE * (2 * pnode  + chiplet);
पूर्ण

अटल अंतरभूत काष्ठा gru_control_block_extended *gru_tfh_to_cbe(
					काष्ठा gru_tlb_fault_handle *tfh)
अणु
	अचिन्हित दीर्घ cbe;

	cbe = (अचिन्हित दीर्घ)tfh - GRU_TFH_BASE + GRU_CBE_BASE;
	वापस (काष्ठा gru_control_block_extended*)cbe;
पूर्ण




/*
 * Global TLB Fault Map
 * 	Biपंचांगap of outstanding TLB misses needing पूर्णांकerrupt/polling service.
 *
 */
काष्ठा gru_tlb_fault_map अणु
	अचिन्हित दीर्घ fault_bits[BITS_TO_LONGS(GRU_NUM_CBE)];
	अचिन्हित दीर्घ fill0[2];
	अचिन्हित दीर्घ करोne_bits[BITS_TO_LONGS(GRU_NUM_CBE)];
	अचिन्हित दीर्घ fill1[2];
पूर्ण;

/*
 * TGH - TLB Global Handle
 * 	Used क्रम TLB flushing.
 *
 */
काष्ठा gru_tlb_global_handle अणु
	अचिन्हित पूर्णांक cmd:1;		/* DW 0 */
	अचिन्हित पूर्णांक delresp:1;
	अचिन्हित पूर्णांक opc:1;
	अचिन्हित पूर्णांक fill1:5;

	अचिन्हित पूर्णांक fill2:8;

	अचिन्हित पूर्णांक status:2;
	अचिन्हित दीर्घ fill3:2;
	अचिन्हित पूर्णांक state:3;
	अचिन्हित दीर्घ fill4:1;

	अचिन्हित पूर्णांक cause:3;
	अचिन्हित दीर्घ fill5:37;

	अचिन्हित दीर्घ vaddr:64;		/* DW 1 */

	अचिन्हित पूर्णांक asid:24;		/* DW 2 */
	अचिन्हित पूर्णांक fill6:8;

	अचिन्हित पूर्णांक pagesize:5;
	अचिन्हित पूर्णांक fill7:11;

	अचिन्हित पूर्णांक global:1;
	अचिन्हित पूर्णांक fill8:15;

	अचिन्हित दीर्घ vaddrmask:39;	/* DW 3 */
	अचिन्हित पूर्णांक fill9:9;
	अचिन्हित पूर्णांक n:10;
	अचिन्हित पूर्णांक fill10:6;

	अचिन्हित पूर्णांक ctxbiपंचांगap:16;	/* DW4 */
	अचिन्हित दीर्घ fill11[3];
पूर्ण;

क्रमागत gru_tgh_cmd अणु
	TGHCMD_START
पूर्ण;

क्रमागत gru_tgh_opc अणु
	TGHOP_TLBNOP,
	TGHOP_TLBINV
पूर्ण;

क्रमागत gru_tgh_status अणु
	TGHSTATUS_IDLE,
	TGHSTATUS_EXCEPTION,
	TGHSTATUS_ACTIVE
पूर्ण;

क्रमागत gru_tgh_state अणु
	TGHSTATE_IDLE,
	TGHSTATE_PE_INVAL,
	TGHSTATE_INTERRUPT_INVAL,
	TGHSTATE_WAITDONE,
	TGHSTATE_RESTART_CTX,
पूर्ण;

क्रमागत gru_tgh_cause अणु
	TGHCAUSE_RR_ECC,
	TGHCAUSE_TLB_ECC,
	TGHCAUSE_LRU_ECC,
	TGHCAUSE_PS_ECC,
	TGHCAUSE_MUL_ERR,
	TGHCAUSE_DATA_ERR,
	TGHCAUSE_SW_FORCE
पूर्ण;


/*
 * TFH - TLB Global Handle
 * 	Used क्रम TLB dropins पूर्णांकo the GRU TLB.
 *
 */
काष्ठा gru_tlb_fault_handle अणु
	अचिन्हित पूर्णांक cmd:1;		/* DW 0 - low 32*/
	अचिन्हित पूर्णांक delresp:1;
	अचिन्हित पूर्णांक fill0:2;
	अचिन्हित पूर्णांक opc:3;
	अचिन्हित पूर्णांक fill1:9;

	अचिन्हित पूर्णांक status:2;
	अचिन्हित पूर्णांक fill2:2;
	अचिन्हित पूर्णांक state:3;
	अचिन्हित पूर्णांक fill3:1;

	अचिन्हित पूर्णांक cause:6;
	अचिन्हित पूर्णांक cb_पूर्णांक:1;
	अचिन्हित पूर्णांक fill4:1;

	अचिन्हित पूर्णांक indexway:12;	/* DW 0 - high 32 */
	अचिन्हित पूर्णांक fill5:4;

	अचिन्हित पूर्णांक ctxnum:4;
	अचिन्हित पूर्णांक fill6:12;

	अचिन्हित दीर्घ missvaddr:64;	/* DW 1 */

	अचिन्हित पूर्णांक missasid:24;	/* DW 2 */
	अचिन्हित पूर्णांक fill7:8;
	अचिन्हित पूर्णांक fillasid:24;
	अचिन्हित पूर्णांक dirty:1;
	अचिन्हित पूर्णांक gaa:2;
	अचिन्हित दीर्घ fill8:5;

	अचिन्हित दीर्घ pfn:41;		/* DW 3 */
	अचिन्हित पूर्णांक fill9:7;
	अचिन्हित पूर्णांक pagesize:5;
	अचिन्हित पूर्णांक fill10:11;

	अचिन्हित दीर्घ fillvaddr:64;	/* DW 4 */

	अचिन्हित दीर्घ fill11[3];
पूर्ण;

क्रमागत gru_tfh_opc अणु
	TFHOP_NOOP,
	TFHOP_RESTART,
	TFHOP_WRITE_ONLY,
	TFHOP_WRITE_RESTART,
	TFHOP_EXCEPTION,
	TFHOP_USER_POLLING_MODE = 7,
पूर्ण;

क्रमागत tfh_status अणु
	TFHSTATUS_IDLE,
	TFHSTATUS_EXCEPTION,
	TFHSTATUS_ACTIVE,
पूर्ण;

क्रमागत tfh_state अणु
	TFHSTATE_INACTIVE,
	TFHSTATE_IDLE,
	TFHSTATE_MISS_UPM,
	TFHSTATE_MISS_FMM,
	TFHSTATE_HW_ERR,
	TFHSTATE_WRITE_TLB,
	TFHSTATE_RESTART_CBR,
पूर्ण;

/* TFH cause bits */
क्रमागत tfh_cause अणु
	TFHCAUSE_NONE,
	TFHCAUSE_TLB_MISS,
	TFHCAUSE_TLB_MOD,
	TFHCAUSE_HW_ERROR_RR,
	TFHCAUSE_HW_ERROR_MAIN_ARRAY,
	TFHCAUSE_HW_ERROR_VALID,
	TFHCAUSE_HW_ERROR_PAGESIZE,
	TFHCAUSE_INSTRUCTION_EXCEPTION,
	TFHCAUSE_UNCORRECTIBLE_ERROR,
पूर्ण;

/* GAA values */
#घोषणा GAA_RAM				0x0
#घोषणा GAA_NCRAM			0x2
#घोषणा GAA_MMIO			0x1
#घोषणा GAA_REGISTER			0x3

/* GRU paddr shअगरt क्रम pfn. (NOTE: shअगरt is NOT by actual pagesize) */
#घोषणा GRU_PADDR_SHIFT			12

/*
 * Context Configuration handle
 * 	Used to allocate resources to a GSEG context.
 *
 */
काष्ठा gru_context_configuration_handle अणु
	अचिन्हित पूर्णांक cmd:1;			/* DW0 */
	अचिन्हित पूर्णांक delresp:1;
	अचिन्हित पूर्णांक opc:3;
	अचिन्हित पूर्णांक unmap_enable:1;
	अचिन्हित पूर्णांक req_slice_set_enable:1;
	अचिन्हित पूर्णांक req_slice:2;
	अचिन्हित पूर्णांक cb_पूर्णांक_enable:1;
	अचिन्हित पूर्णांक tlb_पूर्णांक_enable:1;
	अचिन्हित पूर्णांक tfm_fault_bit_enable:1;
	अचिन्हित पूर्णांक tlb_पूर्णांक_select:4;

	अचिन्हित पूर्णांक status:2;
	अचिन्हित पूर्णांक state:2;
	अचिन्हित पूर्णांक reserved2:4;

	अचिन्हित पूर्णांक cause:4;
	अचिन्हित पूर्णांक tfm_करोne_bit_enable:1;
	अचिन्हित पूर्णांक unused:3;

	अचिन्हित पूर्णांक dsr_allocation_map;

	अचिन्हित दीर्घ cbr_allocation_map;	/* DW1 */

	अचिन्हित पूर्णांक asid[8];			/* DW 2 - 5 */
	अचिन्हित लघु sizeavail[8];		/* DW 6 - 7 */
पूर्ण __attribute__ ((packed));

क्रमागत gru_cch_opc अणु
	CCHOP_START = 1,
	CCHOP_ALLOCATE,
	CCHOP_INTERRUPT,
	CCHOP_DEALLOCATE,
	CCHOP_INTERRUPT_SYNC,
पूर्ण;

क्रमागत gru_cch_status अणु
	CCHSTATUS_IDLE,
	CCHSTATUS_EXCEPTION,
	CCHSTATUS_ACTIVE,
पूर्ण;

क्रमागत gru_cch_state अणु
	CCHSTATE_INACTIVE,
	CCHSTATE_MAPPED,
	CCHSTATE_ACTIVE,
	CCHSTATE_INTERRUPTED,
पूर्ण;

/* CCH Exception cause */
क्रमागत gru_cch_cause अणु
	CCHCAUSE_REGION_REGISTER_WRITE_ERROR = 1,
	CCHCAUSE_ILLEGAL_OPCODE = 2,
	CCHCAUSE_INVALID_START_REQUEST = 3,
	CCHCAUSE_INVALID_ALLOCATION_REQUEST = 4,
	CCHCAUSE_INVALID_DEALLOCATION_REQUEST = 5,
	CCHCAUSE_INVALID_INTERRUPT_REQUEST = 6,
	CCHCAUSE_CCH_BUSY = 7,
	CCHCAUSE_NO_CBRS_TO_ALLOCATE = 8,
	CCHCAUSE_BAD_TFM_CONFIG = 9,
	CCHCAUSE_CBR_RESOURCES_OVERSUBSCRIPED = 10,
	CCHCAUSE_DSR_RESOURCES_OVERSUBSCRIPED = 11,
	CCHCAUSE_CBR_DEALLOCATION_ERROR = 12,
पूर्ण;
/*
 * CBE - Control Block Extended
 * 	Maपूर्णांकains पूर्णांकernal GRU state क्रम active CBs.
 *
 */
काष्ठा gru_control_block_extended अणु
	अचिन्हित पूर्णांक reserved0:1;	/* DW 0  - low */
	अचिन्हित पूर्णांक imacpy:3;
	अचिन्हित पूर्णांक reserved1:4;
	अचिन्हित पूर्णांक xtypecpy:3;
	अचिन्हित पूर्णांक iaa0cpy:2;
	अचिन्हित पूर्णांक iaa1cpy:2;
	अचिन्हित पूर्णांक reserved2:1;
	अचिन्हित पूर्णांक opccpy:8;
	अचिन्हित पूर्णांक exopccpy:8;

	अचिन्हित पूर्णांक idef2cpy:22;	/* DW 0  - high */
	अचिन्हित पूर्णांक reserved3:10;

	अचिन्हित पूर्णांक idef4cpy:22;	/* DW 1 */
	अचिन्हित पूर्णांक reserved4:10;
	अचिन्हित पूर्णांक idef4upd:22;
	अचिन्हित पूर्णांक reserved5:10;

	अचिन्हित दीर्घ idef1upd:64;	/* DW 2 */

	अचिन्हित दीर्घ idef5cpy:64;	/* DW 3 */

	अचिन्हित दीर्घ idef6cpy:64;	/* DW 4 */

	अचिन्हित दीर्घ idef3upd:64;	/* DW 5 */

	अचिन्हित दीर्घ idef5upd:64;	/* DW 6 */

	अचिन्हित पूर्णांक idef2upd:22;	/* DW 7 */
	अचिन्हित पूर्णांक reserved6:10;

	अचिन्हित पूर्णांक ecause:20;
	अचिन्हित पूर्णांक cbrstate:4;
	अचिन्हित पूर्णांक cbrexecstatus:8;
पूर्ण;

/* CBE fields क्रम active BCOPY inकाष्ठाions */
#घोषणा cbe_baddr0	idef1upd
#घोषणा cbe_baddr1	idef3upd
#घोषणा cbe_src_cl	idef6cpy
#घोषणा cbe_nelemcur	idef5upd

क्रमागत gru_cbr_state अणु
	CBRSTATE_INACTIVE,
	CBRSTATE_IDLE,
	CBRSTATE_PE_CHECK,
	CBRSTATE_QUEUED,
	CBRSTATE_WAIT_RESPONSE,
	CBRSTATE_INTERRUPTED,
	CBRSTATE_INTERRUPTED_MISS_FMM,
	CBRSTATE_BUSY_INTERRUPT_MISS_FMM,
	CBRSTATE_INTERRUPTED_MISS_UPM,
	CBRSTATE_BUSY_INTERRUPTED_MISS_UPM,
	CBRSTATE_REQUEST_ISSUE,
	CBRSTATE_BUSY_INTERRUPT,
पूर्ण;

/* CBE cbrexecstatus bits  - defined in gru_inकाष्ठाions.h*/
/* CBE ecause bits  - defined in gru_inकाष्ठाions.h */

/*
 * Convert a processor pagesize पूर्णांकo the strange encoded pagesize used by the
 * GRU. Processor pagesize is encoded as log of bytes per page. (or PAGE_SHIFT)
 * 	pagesize	log pagesize	grupagesize
 * 	  4k			12	0
 * 	 16k 			14	1
 * 	 64k			16	2
 * 	256k			18	3
 * 	  1m			20	4
 * 	  2m			21	5
 * 	  4m			22	6
 * 	 16m			24	7
 * 	 64m			26	8
 * 	...
 */
#घोषणा GRU_PAGESIZE(sh)	((((sh) > 20 ? (sh) + 2 : (sh)) >> 1) - 6)
#घोषणा GRU_SIZEAVAIL(sh)	(1UL << GRU_PAGESIZE(sh))

/* minimum TLB purge count to ensure a full purge */
#घोषणा GRUMAXINVAL		1024UL

पूर्णांक cch_allocate(काष्ठा gru_context_configuration_handle *cch);
पूर्णांक cch_start(काष्ठा gru_context_configuration_handle *cch);
पूर्णांक cch_पूर्णांकerrupt(काष्ठा gru_context_configuration_handle *cch);
पूर्णांक cch_deallocate(काष्ठा gru_context_configuration_handle *cch);
पूर्णांक cch_पूर्णांकerrupt_sync(काष्ठा gru_context_configuration_handle *cch);
पूर्णांक tgh_invalidate(काष्ठा gru_tlb_global_handle *tgh, अचिन्हित दीर्घ vaddr,
	अचिन्हित दीर्घ vaddrmask, पूर्णांक asid, पूर्णांक pagesize, पूर्णांक global, पूर्णांक n,
	अचिन्हित लघु ctxbiपंचांगap);
पूर्णांक tfh_ग_लिखो_only(काष्ठा gru_tlb_fault_handle *tfh, अचिन्हित दीर्घ paddr,
	पूर्णांक gaa, अचिन्हित दीर्घ vaddr, पूर्णांक asid, पूर्णांक dirty, पूर्णांक pagesize);
व्योम tfh_ग_लिखो_restart(काष्ठा gru_tlb_fault_handle *tfh, अचिन्हित दीर्घ paddr,
	पूर्णांक gaa, अचिन्हित दीर्घ vaddr, पूर्णांक asid, पूर्णांक dirty, पूर्णांक pagesize);
व्योम tfh_user_polling_mode(काष्ठा gru_tlb_fault_handle *tfh);
व्योम tfh_exception(काष्ठा gru_tlb_fault_handle *tfh);

#पूर्ण_अगर /* __GRUHANDLES_H__ */
