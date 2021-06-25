<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_T2__H__
#घोषणा __ALPHA_T2__H__

/* Fit everything पूर्णांकo one 128MB HAE winकरोw. */
#घोषणा T2_ONE_HAE_WINDOW 1

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/compiler.h>

/*
 * T2 is the पूर्णांकernal name क्रम the core logic chipset which provides
 * memory controller and PCI access क्रम the SABLE-based प्रणालीs.
 *
 * This file is based on:
 *
 * SABLE I/O Specअगरication
 * Revision/Update Inक्रमmation: 1.3
 *
 * jestabro@amt.tay1.dec.com Initial Version.
 *
 */

#घोषणा T2_MEM_R1_MASK 0x07ffffff  /* Mem sparse region 1 mask is 27 bits */

/* GAMMA-SABLE is a SABLE with EV5-based CPUs */
/* All LYNX machines, EV4 or EV5, use the GAMMA bias also */
#घोषणा _GAMMA_BIAS		0x8000000000UL

#अगर defined(CONFIG_ALPHA_GENERIC)
#घोषणा GAMMA_BIAS		alpha_mv.sys.t2.gamma_bias
#या_अगर defined(CONFIG_ALPHA_GAMMA)
#घोषणा GAMMA_BIAS		_GAMMA_BIAS
#अन्यथा
#घोषणा GAMMA_BIAS		0
#पूर्ण_अगर

/*
 * Memory spaces:
 */
#घोषणा T2_CONF		        (IDENT_ADDR + GAMMA_BIAS + 0x390000000UL)
#घोषणा T2_IO			(IDENT_ADDR + GAMMA_BIAS + 0x3a0000000UL)
#घोषणा T2_SPARSE_MEM		(IDENT_ADDR + GAMMA_BIAS + 0x200000000UL)
#घोषणा T2_DENSE_MEM	        (IDENT_ADDR + GAMMA_BIAS + 0x3c0000000UL)

#घोषणा T2_IOCSR		(IDENT_ADDR + GAMMA_BIAS + 0x38e000000UL)
#घोषणा T2_CERR1		(IDENT_ADDR + GAMMA_BIAS + 0x38e000020UL)
#घोषणा T2_CERR2		(IDENT_ADDR + GAMMA_BIAS + 0x38e000040UL)
#घोषणा T2_CERR3		(IDENT_ADDR + GAMMA_BIAS + 0x38e000060UL)
#घोषणा T2_PERR1		(IDENT_ADDR + GAMMA_BIAS + 0x38e000080UL)
#घोषणा T2_PERR2		(IDENT_ADDR + GAMMA_BIAS + 0x38e0000a0UL)
#घोषणा T2_PSCR			(IDENT_ADDR + GAMMA_BIAS + 0x38e0000c0UL)
#घोषणा T2_HAE_1		(IDENT_ADDR + GAMMA_BIAS + 0x38e0000e0UL)
#घोषणा T2_HAE_2		(IDENT_ADDR + GAMMA_BIAS + 0x38e000100UL)
#घोषणा T2_HBASE		(IDENT_ADDR + GAMMA_BIAS + 0x38e000120UL)
#घोषणा T2_WBASE1		(IDENT_ADDR + GAMMA_BIAS + 0x38e000140UL)
#घोषणा T2_WMASK1		(IDENT_ADDR + GAMMA_BIAS + 0x38e000160UL)
#घोषणा T2_TBASE1		(IDENT_ADDR + GAMMA_BIAS + 0x38e000180UL)
#घोषणा T2_WBASE2		(IDENT_ADDR + GAMMA_BIAS + 0x38e0001a0UL)
#घोषणा T2_WMASK2		(IDENT_ADDR + GAMMA_BIAS + 0x38e0001c0UL)
#घोषणा T2_TBASE2		(IDENT_ADDR + GAMMA_BIAS + 0x38e0001e0UL)
#घोषणा T2_TLBBR		(IDENT_ADDR + GAMMA_BIAS + 0x38e000200UL)
#घोषणा T2_IVR			(IDENT_ADDR + GAMMA_BIAS + 0x38e000220UL)
#घोषणा T2_HAE_3		(IDENT_ADDR + GAMMA_BIAS + 0x38e000240UL)
#घोषणा T2_HAE_4		(IDENT_ADDR + GAMMA_BIAS + 0x38e000260UL)

/* The CSRs below are T3/T4 only */
#घोषणा T2_WBASE3		(IDENT_ADDR + GAMMA_BIAS + 0x38e000280UL)
#घोषणा T2_WMASK3		(IDENT_ADDR + GAMMA_BIAS + 0x38e0002a0UL)
#घोषणा T2_TBASE3		(IDENT_ADDR + GAMMA_BIAS + 0x38e0002c0UL)

#घोषणा T2_TDR0			(IDENT_ADDR + GAMMA_BIAS + 0x38e000300UL)
#घोषणा T2_TDR1			(IDENT_ADDR + GAMMA_BIAS + 0x38e000320UL)
#घोषणा T2_TDR2			(IDENT_ADDR + GAMMA_BIAS + 0x38e000340UL)
#घोषणा T2_TDR3			(IDENT_ADDR + GAMMA_BIAS + 0x38e000360UL)
#घोषणा T2_TDR4			(IDENT_ADDR + GAMMA_BIAS + 0x38e000380UL)
#घोषणा T2_TDR5			(IDENT_ADDR + GAMMA_BIAS + 0x38e0003a0UL)
#घोषणा T2_TDR6			(IDENT_ADDR + GAMMA_BIAS + 0x38e0003c0UL)
#घोषणा T2_TDR7			(IDENT_ADDR + GAMMA_BIAS + 0x38e0003e0UL)

#घोषणा T2_WBASE4		(IDENT_ADDR + GAMMA_BIAS + 0x38e000400UL)
#घोषणा T2_WMASK4		(IDENT_ADDR + GAMMA_BIAS + 0x38e000420UL)
#घोषणा T2_TBASE4		(IDENT_ADDR + GAMMA_BIAS + 0x38e000440UL)

#घोषणा T2_AIR			(IDENT_ADDR + GAMMA_BIAS + 0x38e000460UL)
#घोषणा T2_VAR			(IDENT_ADDR + GAMMA_BIAS + 0x38e000480UL)
#घोषणा T2_सूची			(IDENT_ADDR + GAMMA_BIAS + 0x38e0004a0UL)
#घोषणा T2_ICE			(IDENT_ADDR + GAMMA_BIAS + 0x38e0004c0UL)

#अगर_अघोषित T2_ONE_HAE_WINDOW
#घोषणा T2_HAE_ADDRESS		T2_HAE_1
#पूर्ण_अगर

/*  T2 CSRs are in the non-cachable primary IO space from 3.8000.0000 to
 3.8fff.ffff
 *
 *  +--------------+ 3 8000 0000
 *  | CPU 0 CSRs   |
 *  +--------------+ 3 8100 0000
 *  | CPU 1 CSRs   |
 *  +--------------+ 3 8200 0000
 *  | CPU 2 CSRs   |
 *  +--------------+ 3 8300 0000
 *  | CPU 3 CSRs   |
 *  +--------------+ 3 8400 0000
 *  | CPU Reserved |
 *  +--------------+ 3 8700 0000
 *  | Mem Reserved |
 *  +--------------+ 3 8800 0000
 *  | Mem 0 CSRs   |
 *  +--------------+ 3 8900 0000
 *  | Mem 1 CSRs   |
 *  +--------------+ 3 8a00 0000
 *  | Mem 2 CSRs   |
 *  +--------------+ 3 8b00 0000
 *  | Mem 3 CSRs   |
 *  +--------------+ 3 8c00 0000
 *  | Mem Reserved |
 *  +--------------+ 3 8e00 0000
 *  | PCI Bridge   |
 *  +--------------+ 3 8f00 0000
 *  | Expansion IO |
 *  +--------------+ 3 9000 0000
 *
 *
 */
#घोषणा T2_CPU0_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x380000000L)
#घोषणा T2_CPU1_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x381000000L)
#घोषणा T2_CPU2_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x382000000L)
#घोषणा T2_CPU3_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x383000000L)

#घोषणा T2_CPUn_BASE(n)		(T2_CPU0_BASE + (((n)&3) * 0x001000000L))

#घोषणा T2_MEM0_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x388000000L)
#घोषणा T2_MEM1_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x389000000L)
#घोषणा T2_MEM2_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x38a000000L)
#घोषणा T2_MEM3_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x38b000000L)


/*
 * Sable CPU Module CSRS
 *
 * These are CSRs क्रम hardware other than the CPU chip on the CPU module.
 * The CPU module has Backup Cache control logic, Cbus control logic, and
 * पूर्णांकerrupt control logic on it.  There is a duplicate tag store to speed
 * up मुख्यtaining cache coherency.
 */

काष्ठा sable_cpu_csr अणु
  अचिन्हित दीर्घ bcc;     दीर्घ fill_00[3]; /* Backup Cache Control */
  अचिन्हित दीर्घ bcce;    दीर्घ fill_01[3]; /* Backup Cache Correctable Error */
  अचिन्हित दीर्घ bccea;   दीर्घ fill_02[3]; /* B-Cache Corr Err Address Latch */
  अचिन्हित दीर्घ bcue;    दीर्घ fill_03[3]; /* B-Cache Uncorrectable Error */
  अचिन्हित दीर्घ bcuea;   दीर्घ fill_04[3]; /* B-Cache Uncorr Err Addr Latch */
  अचिन्हित दीर्घ dter;    दीर्घ fill_05[3]; /* Duplicate Tag Error */
  अचिन्हित दीर्घ cbctl;   दीर्घ fill_06[3]; /* CBus Control */
  अचिन्हित दीर्घ cbe;     दीर्घ fill_07[3]; /* CBus Error */
  अचिन्हित दीर्घ cbeal;   दीर्घ fill_08[3]; /* CBus Error Addr Latch low */
  अचिन्हित दीर्घ cbeah;   दीर्घ fill_09[3]; /* CBus Error Addr Latch high */
  अचिन्हित दीर्घ pmbx;    दीर्घ fill_10[3]; /* Processor Mailbox */
  अचिन्हित दीर्घ ipir;    दीर्घ fill_11[3]; /* Inter-Processor Int Request */
  अचिन्हित दीर्घ sic;     दीर्घ fill_12[3]; /* System Interrupt Clear */
  अचिन्हित दीर्घ adlk;    दीर्घ fill_13[3]; /* Address Lock (LDxL/STxC) */
  अचिन्हित दीर्घ madrl;   दीर्घ fill_14[3]; /* CBus Miss Address */
  अचिन्हित दीर्घ rev;     दीर्घ fill_15[3]; /* CMIC Revision */
पूर्ण;

/*
 * Data काष्ठाure क्रम handling T2 machine checks:
 */
काष्ठा el_t2_frame_header अणु
	अचिन्हित पूर्णांक	elcf_fid;	/* Frame ID (from above) */
	अचिन्हित पूर्णांक	elcf_size;	/* Size of frame in bytes */
पूर्ण;

काष्ठा el_t2_procdata_mcheck अणु
	अचिन्हित दीर्घ	elfmc_paltemp[32];	/* PAL TEMP REGS. */
	/* EV4-specअगरic fields */
	अचिन्हित दीर्घ	elfmc_exc_addr;	/* Addr of excepting insn. */
	अचिन्हित दीर्घ	elfmc_exc_sum;	/* Summary of arith traps. */
	अचिन्हित दीर्घ	elfmc_exc_mask;	/* Exception mask (from exc_sum). */
	अचिन्हित दीर्घ	elfmc_iccsr;	/* IBox hardware enables. */
	अचिन्हित दीर्घ	elfmc_pal_base;	/* Base address क्रम PALcode. */
	अचिन्हित दीर्घ	elfmc_hier;	/* Hardware Interrupt Enable. */
	अचिन्हित दीर्घ	elfmc_hirr;	/* Hardware Interrupt Request. */
	अचिन्हित दीर्घ	elfmc_mm_csr;	/* D-stream fault info. */
	अचिन्हित दीर्घ	elfmc_dc_stat;	/* D-cache status (ECC/Parity Err). */
	अचिन्हित दीर्घ	elfmc_dc_addr;	/* EV3 Phys Addr क्रम ECC/DPERR. */
	अचिन्हित दीर्घ	elfmc_abox_ctl;	/* ABox Control Register. */
	अचिन्हित दीर्घ	elfmc_biu_stat;	/* BIU Status. */
	अचिन्हित दीर्घ	elfmc_biu_addr;	/* BUI Address. */
	अचिन्हित दीर्घ	elfmc_biu_ctl;	/* BIU Control. */
	अचिन्हित दीर्घ	elfmc_fill_syndrome; /* For correcting ECC errors. */
	अचिन्हित दीर्घ	elfmc_fill_addr;/* Cache block which was being पढ़ो. */
	अचिन्हित दीर्घ	elfmc_va;	/* Effective VA of fault or miss. */
	अचिन्हित दीर्घ	elfmc_bc_tag;	/* Backup Cache Tag Probe Results. */
पूर्ण;

/*
 * Sable processor specअगरic Machine Check Data segment.
 */

काष्ठा el_t2_logout_header अणु
	अचिन्हित पूर्णांक	elfl_size;	/* size in bytes of logout area. */
	अचिन्हित पूर्णांक	elfl_sbz1:31;	/* Should be zero. */
	अचिन्हित पूर्णांक	elfl_retry:1;	/* Retry flag. */
	अचिन्हित पूर्णांक	elfl_procoffset; /* Processor-specअगरic offset. */
	अचिन्हित पूर्णांक	elfl_sysoffset;	 /* Offset of प्रणाली-specअगरic. */
	अचिन्हित पूर्णांक	elfl_error_type;	/* PAL error type code. */
	अचिन्हित पूर्णांक	elfl_frame_rev;		/* PAL Frame revision. */
पूर्ण;
काष्ठा el_t2_sysdata_mcheck अणु
	अचिन्हित दीर्घ    elcmc_bcc;	      /* CSR 0 */
	अचिन्हित दीर्घ    elcmc_bcce;	      /* CSR 1 */
	अचिन्हित दीर्घ    elcmc_bccea;      /* CSR 2 */
	अचिन्हित दीर्घ    elcmc_bcue;	      /* CSR 3 */
	अचिन्हित दीर्घ    elcmc_bcuea;      /* CSR 4 */
	अचिन्हित दीर्घ    elcmc_dter;	      /* CSR 5 */
	अचिन्हित दीर्घ    elcmc_cbctl;      /* CSR 6 */
	अचिन्हित दीर्घ    elcmc_cbe;	      /* CSR 7 */
	अचिन्हित दीर्घ    elcmc_cbeal;      /* CSR 8 */
	अचिन्हित दीर्घ    elcmc_cbeah;      /* CSR 9 */
	अचिन्हित दीर्घ    elcmc_pmbx;	      /* CSR 10 */
	अचिन्हित दीर्घ    elcmc_ipir;	      /* CSR 11 */
	अचिन्हित दीर्घ    elcmc_sic;	      /* CSR 12 */
	अचिन्हित दीर्घ    elcmc_adlk;	      /* CSR 13 */
	अचिन्हित दीर्घ    elcmc_madrl;      /* CSR 14 */
	अचिन्हित दीर्घ    elcmc_crrev4;     /* CSR 15 */
पूर्ण;

/*
 * Sable memory error frame - sable pfms section 3.42
 */
काष्ठा el_t2_data_memory अणु
	काष्ठा	el_t2_frame_header elcm_hdr;	/* ID$MEM-FERR = 0x08 */
	अचिन्हित पूर्णांक  elcm_module;	/* Module id. */
	अचिन्हित पूर्णांक  elcm_res04;	/* Reserved. */
	अचिन्हित दीर्घ elcm_merr;	/* CSR0: Error Reg 1. */
	अचिन्हित दीर्घ elcm_mcmd1;	/* CSR1: Command Trap 1. */
	अचिन्हित दीर्घ elcm_mcmd2;	/* CSR2: Command Trap 2. */
	अचिन्हित दीर्घ elcm_mconf;	/* CSR3: Configuration. */
	अचिन्हित दीर्घ elcm_medc1;	/* CSR4: EDC Status 1. */
	अचिन्हित दीर्घ elcm_medc2;	/* CSR5: EDC Status 2. */
	अचिन्हित दीर्घ elcm_medcc;	/* CSR6: EDC Control. */
	अचिन्हित दीर्घ elcm_msctl;	/* CSR7: Stream Buffer Control. */
	अचिन्हित दीर्घ elcm_mref;	/* CSR8: Refresh Control. */
	अचिन्हित दीर्घ elcm_filter;	/* CSR9: CRD Filter Control. */
पूर्ण;


/*
 * Sable other CPU error frame - sable pfms section 3.43
 */
काष्ठा el_t2_data_other_cpu अणु
	लघु	      elco_cpuid;	/* CPU ID */
	लघु	      elco_res02[3];
	अचिन्हित दीर्घ elco_bcc;	/* CSR 0 */
	अचिन्हित दीर्घ elco_bcce;	/* CSR 1 */
	अचिन्हित दीर्घ elco_bccea;	/* CSR 2 */
	अचिन्हित दीर्घ elco_bcue;	/* CSR 3 */
	अचिन्हित दीर्घ elco_bcuea;	/* CSR 4 */
	अचिन्हित दीर्घ elco_dter;	/* CSR 5 */
	अचिन्हित दीर्घ elco_cbctl;	/* CSR 6 */
	अचिन्हित दीर्घ elco_cbe;	/* CSR 7 */
	अचिन्हित दीर्घ elco_cbeal;	/* CSR 8 */
	अचिन्हित दीर्घ elco_cbeah;	/* CSR 9 */
	अचिन्हित दीर्घ elco_pmbx;	/* CSR 10 */
	अचिन्हित दीर्घ elco_ipir;	/* CSR 11 */
	अचिन्हित दीर्घ elco_sic;	/* CSR 12 */
	अचिन्हित दीर्घ elco_adlk;	/* CSR 13 */
	अचिन्हित दीर्घ elco_madrl;	/* CSR 14 */
	अचिन्हित दीर्घ elco_crrev4;	/* CSR 15 */
पूर्ण;

/*
 * Sable other CPU error frame - sable pfms section 3.44
 */
काष्ठा el_t2_data_t2अणु
	काष्ठा el_t2_frame_header elct_hdr;	/* ID$T2-FRAME */
	अचिन्हित दीर्घ elct_iocsr;	/* IO Control and Status Register */
	अचिन्हित दीर्घ elct_cerr1;	/* Cbus Error Register 1 */
	अचिन्हित दीर्घ elct_cerr2;	/* Cbus Error Register 2 */
	अचिन्हित दीर्घ elct_cerr3;	/* Cbus Error Register 3 */
	अचिन्हित दीर्घ elct_perr1;	/* PCI Error Register 1 */
	अचिन्हित दीर्घ elct_perr2;	/* PCI Error Register 2 */
	अचिन्हित दीर्घ elct_hae0_1;	/* High Address Extension Register 1 */
	अचिन्हित दीर्घ elct_hae0_2;	/* High Address Extension Register 2 */
	अचिन्हित दीर्घ elct_hbase;	/* High Base Register */
	अचिन्हित दीर्घ elct_wbase1;	/* Winकरोw Base Register 1 */
	अचिन्हित दीर्घ elct_wmask1;	/* Winकरोw Mask Register 1 */
	अचिन्हित दीर्घ elct_tbase1;	/* Translated Base Register 1 */
	अचिन्हित दीर्घ elct_wbase2;	/* Winकरोw Base Register 2 */
	अचिन्हित दीर्घ elct_wmask2;	/* Winकरोw Mask Register 2 */
	अचिन्हित दीर्घ elct_tbase2;	/* Translated Base Register 2 */
	अचिन्हित दीर्घ elct_tdr0;	/* TLB Data Register 0 */
	अचिन्हित दीर्घ elct_tdr1;	/* TLB Data Register 1 */
	अचिन्हित दीर्घ elct_tdr2;	/* TLB Data Register 2 */
	अचिन्हित दीर्घ elct_tdr3;	/* TLB Data Register 3 */
	अचिन्हित दीर्घ elct_tdr4;	/* TLB Data Register 4 */
	अचिन्हित दीर्घ elct_tdr5;	/* TLB Data Register 5 */
	अचिन्हित दीर्घ elct_tdr6;	/* TLB Data Register 6 */
	अचिन्हित दीर्घ elct_tdr7;	/* TLB Data Register 7 */
पूर्ण;

/*
 * Sable error log data काष्ठाure - sable pfms section 3.40
 */
काष्ठा el_t2_data_corrected अणु
	अचिन्हित दीर्घ elcpb_biu_stat;
	अचिन्हित दीर्घ elcpb_biu_addr;
	अचिन्हित दीर्घ elcpb_biu_ctl;
	अचिन्हित दीर्घ elcpb_fill_syndrome;
	अचिन्हित दीर्घ elcpb_fill_addr;
	अचिन्हित दीर्घ elcpb_bc_tag;
पूर्ण;

/*
 * Sable error log data काष्ठाure
 * Note there are 4 memory slots on sable (see t2.h)
 */
काष्ठा el_t2_frame_mcheck अणु
	काष्ठा el_t2_frame_header elfmc_header;	/* ID$P-FRAME_MCHECK */
	काष्ठा el_t2_logout_header elfmc_hdr;
	काष्ठा el_t2_procdata_mcheck elfmc_procdata;
	काष्ठा el_t2_sysdata_mcheck elfmc_sysdata;
	काष्ठा el_t2_data_t2 elfmc_t2data;
	काष्ठा el_t2_data_memory elfmc_memdata[4];
	काष्ठा el_t2_frame_header elfmc_footer;	/* empty */
पूर्ण;


/*
 * Sable error log data काष्ठाures on memory errors
 */
काष्ठा el_t2_frame_corrected अणु
	काष्ठा el_t2_frame_header elfcc_header;	/* ID$P-BC-COR */
	काष्ठा el_t2_logout_header elfcc_hdr;
	काष्ठा el_t2_data_corrected elfcc_procdata;
/*	काष्ठा el_t2_data_t2 elfcc_t2data;		*/
/*	काष्ठा el_t2_data_memory elfcc_memdata[4];	*/
	काष्ठा el_t2_frame_header elfcc_footer;	/* empty */
पूर्ण;


#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * T2 (the core logic PCI/memory support chipset क्रम the SABLE
 * series of processors uses a sparse address mapping scheme to
 * get at PCI memory and I/O.
 */

#घोषणा vip	अस्थिर पूर्णांक *
#घोषणा vuip	अस्थिर अचिन्हित पूर्णांक *

बाह्य अंतरभूत u8 t2_inb(अचिन्हित दीर्घ addr)
अणु
	दीर्घ result = *(vip) ((addr << 5) + T2_IO + 0x00);
	वापस __kernel_extbl(result, addr & 3);
पूर्ण

बाह्य अंतरभूत व्योम t2_outb(u8 b, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ w;

	w = __kernel_insbl(b, addr & 3);
	*(vuip) ((addr << 5) + T2_IO + 0x00) = w;
	mb();
पूर्ण

बाह्य अंतरभूत u16 t2_inw(अचिन्हित दीर्घ addr)
अणु
	दीर्घ result = *(vip) ((addr << 5) + T2_IO + 0x08);
	वापस __kernel_extwl(result, addr & 3);
पूर्ण

बाह्य अंतरभूत व्योम t2_outw(u16 b, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ w;

	w = __kernel_inswl(b, addr & 3);
	*(vuip) ((addr << 5) + T2_IO + 0x08) = w;
	mb();
पूर्ण

बाह्य अंतरभूत u32 t2_inl(अचिन्हित दीर्घ addr)
अणु
	वापस *(vuip) ((addr << 5) + T2_IO + 0x18);
पूर्ण

बाह्य अंतरभूत व्योम t2_outl(u32 b, अचिन्हित दीर्घ addr)
अणु
	*(vuip) ((addr << 5) + T2_IO + 0x18) = b;
	mb();
पूर्ण


/*
 * Memory functions.
 *
 * For पढ़ोing and writing 8 and 16 bit quantities we need to
 * go through one of the three sparse address mapping regions
 * and use the HAE_MEM CSR to provide some bits of the address.
 * The following few routines use only sparse address region 1
 * which gives 1Gbyte of accessible space which relates exactly
 * to the amount of PCI memory mapping *पूर्णांकo* प्रणाली address space.
 * See p 6-17 of the specअगरication but it looks something like this:
 *
 * 21164 Address:
 *
 *          3         2         1
 * 9876543210987654321098765432109876543210
 * 1ZZZZ0.PCI.QW.Address............BBLL
 *
 * ZZ = SBZ
 * BB = Byte offset
 * LL = Transfer length
 *
 * PCI Address:
 *
 * 3         2         1
 * 10987654321098765432109876543210
 * HHH....PCI.QW.Address........ 00
 *
 * HHH = 31:29 HAE_MEM CSR
 *
 */

#अगर_घोषित T2_ONE_HAE_WINDOW
#घोषणा t2_set_hae
#अन्यथा
#घोषणा t2_set_hae अणु \
	अचिन्हित दीर्घ msb = addr >> 27; \
	addr &= T2_MEM_R1_MASK; \
	set_hae(msb); \
पूर्ण
#पूर्ण_अगर

/*
 * NOTE: take T2_DENSE_MEM off in each पढ़ोX/ग_लिखोX routine, since
 *       they may be called directly, rather than through the
 *       ioपढ़ोNN/ioग_लिखोNN routines.
 */

__EXTERN_INLINE u8 t2_पढ़ोb(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr - T2_DENSE_MEM;
	अचिन्हित दीर्घ result;

	t2_set_hae;

	result = *(vip) ((addr << 5) + T2_SPARSE_MEM + 0x00);
	वापस __kernel_extbl(result, addr & 3);
पूर्ण

__EXTERN_INLINE u16 t2_पढ़ोw(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr - T2_DENSE_MEM;
	अचिन्हित दीर्घ result;

	t2_set_hae;

	result = *(vuip) ((addr << 5) + T2_SPARSE_MEM + 0x08);
	वापस __kernel_extwl(result, addr & 3);
पूर्ण

/*
 * On SABLE with T2, we must use SPARSE memory even क्रम 32-bit access,
 * because we cannot access all of DENSE without changing its HAE.
 */
__EXTERN_INLINE u32 t2_पढ़ोl(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr - T2_DENSE_MEM;
	अचिन्हित दीर्घ result;

	t2_set_hae;

	result = *(vuip) ((addr << 5) + T2_SPARSE_MEM + 0x18);
	वापस result & 0xffffffffUL;
पूर्ण

__EXTERN_INLINE u64 t2_पढ़ोq(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr - T2_DENSE_MEM;
	अचिन्हित दीर्घ r0, r1, work;

	t2_set_hae;

	work = (addr << 5) + T2_SPARSE_MEM + 0x18;
	r0 = *(vuip)(work);
	r1 = *(vuip)(work + (4 << 5));
	वापस r1 << 32 | r0;
पूर्ण

__EXTERN_INLINE व्योम t2_ग_लिखोb(u8 b, अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr - T2_DENSE_MEM;
	अचिन्हित दीर्घ w;

	t2_set_hae;

	w = __kernel_insbl(b, addr & 3);
	*(vuip) ((addr << 5) + T2_SPARSE_MEM + 0x00) = w;
पूर्ण

__EXTERN_INLINE व्योम t2_ग_लिखोw(u16 b, अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr - T2_DENSE_MEM;
	अचिन्हित दीर्घ w;

	t2_set_hae;

	w = __kernel_inswl(b, addr & 3);
	*(vuip) ((addr << 5) + T2_SPARSE_MEM + 0x08) = w;
पूर्ण

/*
 * On SABLE with T2, we must use SPARSE memory even क्रम 32-bit access,
 * because we cannot access all of DENSE without changing its HAE.
 */
__EXTERN_INLINE व्योम t2_ग_लिखोl(u32 b, अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr - T2_DENSE_MEM;

	t2_set_hae;

	*(vuip) ((addr << 5) + T2_SPARSE_MEM + 0x18) = b;
पूर्ण

__EXTERN_INLINE व्योम t2_ग_लिखोq(u64 b, अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr - T2_DENSE_MEM;
	अचिन्हित दीर्घ work;

	t2_set_hae;

	work = (addr << 5) + T2_SPARSE_MEM + 0x18;
	*(vuip)work = b;
	*(vuip)(work + (4 << 5)) = b >> 32;
पूर्ण

__EXTERN_INLINE व्योम __iomem *t2_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + T2_IO);
पूर्ण

__EXTERN_INLINE व्योम __iomem *t2_ioremap(अचिन्हित दीर्घ addr, 
					 अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + T2_DENSE_MEM);
पूर्ण

__EXTERN_INLINE पूर्णांक t2_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस (दीर्घ)addr >= 0;
पूर्ण

__EXTERN_INLINE पूर्णांक t2_is_mmio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr >= T2_DENSE_MEM;
पूर्ण

/* New-style ioपढ़ो पूर्णांकerface.  The mmio routines are so ugly क्रम T2 that
   it करोesn't make sense to merge the pio and mmio routines.  */

#घोषणा IOPORT(OS, NS)							\
__EXTERN_INLINE अचिन्हित पूर्णांक t2_ioपढ़ो##NS(स्थिर व्योम __iomem *xaddr)		\
अणु									\
	अगर (t2_is_mmio(xaddr))						\
		वापस t2_पढ़ो##OS(xaddr);				\
	अन्यथा								\
		वापस t2_in##OS((अचिन्हित दीर्घ)xaddr - T2_IO);		\
पूर्ण									\
__EXTERN_INLINE व्योम t2_ioग_लिखो##NS(u##NS b, व्योम __iomem *xaddr)	\
अणु									\
	अगर (t2_is_mmio(xaddr))						\
		t2_ग_लिखो##OS(b, xaddr);					\
	अन्यथा								\
		t2_out##OS(b, (अचिन्हित दीर्घ)xaddr - T2_IO);		\
पूर्ण

IOPORT(b, 8)
IOPORT(w, 16)
IOPORT(l, 32)

#अघोषित IOPORT

#अघोषित vip
#अघोषित vuip

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		t2
#घोषणा t2_trivial_rw_bw	0
#घोषणा t2_trivial_rw_lq	0
#घोषणा t2_trivial_io_bw	0
#घोषणा t2_trivial_io_lq	0
#घोषणा t2_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_T2__H__ */
