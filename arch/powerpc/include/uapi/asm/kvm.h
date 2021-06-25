<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301, USA.
 *
 * Copyright IBM Corp. 2007
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#अगर_अघोषित __LINUX_KVM_POWERPC_H
#घोषणा __LINUX_KVM_POWERPC_H

#समावेश <linux/types.h>

/* Select घातerpc specअगरic features in <linux/kvm.h> */
#घोषणा __KVM_HAVE_SPAPR_TCE
#घोषणा __KVM_HAVE_PPC_SMT
#घोषणा __KVM_HAVE_IRQCHIP
#घोषणा __KVM_HAVE_IRQ_LINE
#घोषणा __KVM_HAVE_GUEST_DEBUG

/* Not always available, but अगर it is, this is the correct offset.  */
#घोषणा KVM_COALESCED_MMIO_PAGE_OFFSET 1

काष्ठा kvm_regs अणु
	__u64 pc;
	__u64 cr;
	__u64 ctr;
	__u64 lr;
	__u64 xer;
	__u64 msr;
	__u64 srr0;
	__u64 srr1;
	__u64 pid;

	__u64 sprg0;
	__u64 sprg1;
	__u64 sprg2;
	__u64 sprg3;
	__u64 sprg4;
	__u64 sprg5;
	__u64 sprg6;
	__u64 sprg7;

	__u64 gpr[32];
पूर्ण;

#घोषणा KVM_SREGS_E_IMPL_NONE	0
#घोषणा KVM_SREGS_E_IMPL_FSL	1

#घोषणा KVM_SREGS_E_FSL_PIDn	(1 << 0) /* PID1/PID2 */

/* flags क्रम kvm_run.flags */
#घोषणा KVM_RUN_PPC_NMI_DISP_MASK		(3 << 0)
#घोषणा   KVM_RUN_PPC_NMI_DISP_FULLY_RECOV	(1 << 0)
#घोषणा   KVM_RUN_PPC_NMI_DISP_LIMITED_RECOV	(2 << 0)
#घोषणा   KVM_RUN_PPC_NMI_DISP_NOT_RECOV	(3 << 0)

/*
 * Feature bits indicate which sections of the sregs काष्ठा are valid,
 * both in KVM_GET_SREGS and KVM_SET_SREGS.  On KVM_SET_SREGS, रेजिस्टरs
 * corresponding to unset feature bits will not be modअगरied.  This allows
 * restoring a checkpoपूर्णांक made without that feature, जबतक keeping the
 * शेष values of the new रेजिस्टरs.
 *
 * KVM_SREGS_E_BASE contains:
 * CSRR0/1 (refers to SRR2/3 on 40x)
 * ESR
 * DEAR
 * MCSR
 * TSR
 * TCR
 * DEC
 * TB
 * VRSAVE (USPRG0)
 */
#घोषणा KVM_SREGS_E_BASE		(1 << 0)

/*
 * KVM_SREGS_E_ARCH206 contains:
 *
 * PIR
 * MCSRR0/1
 * DECAR
 * IVPR
 */
#घोषणा KVM_SREGS_E_ARCH206		(1 << 1)

/*
 * Contains EPCR, plus the upper half of 64-bit रेजिस्टरs
 * that are 32-bit on 32-bit implementations.
 */
#घोषणा KVM_SREGS_E_64			(1 << 2)

#घोषणा KVM_SREGS_E_SPRG8		(1 << 3)
#घोषणा KVM_SREGS_E_MCIVPR		(1 << 4)

/*
 * IVORs are used -- contains IVOR0-15, plus additional IVORs
 * in combination with an appropriate feature bit.
 */
#घोषणा KVM_SREGS_E_IVOR		(1 << 5)

/*
 * Contains MAS0-4, MAS6-7, TLBnCFG, MMUCFG.
 * Also TLBnPS अगर MMUCFG[MAVN] = 1.
 */
#घोषणा KVM_SREGS_E_ARCH206_MMU		(1 << 6)

/* DBSR, DBCR, IAC, DAC, DVC */
#घोषणा KVM_SREGS_E_DEBUG		(1 << 7)

/* Enhanced debug -- DSRR0/1, SPRG9 */
#घोषणा KVM_SREGS_E_ED			(1 << 8)

/* Embedded Floating Poपूर्णांक (SPE) -- IVOR32-34 अगर KVM_SREGS_E_IVOR */
#घोषणा KVM_SREGS_E_SPE			(1 << 9)

/*
 * DEPRECATED! USE ONE_REG FOR THIS ONE!
 * External Proxy (EXP) -- EPR
 */
#घोषणा KVM_SREGS_EXP			(1 << 10)

/* External PID (E.PD) -- EPSC/EPLC */
#घोषणा KVM_SREGS_E_PD			(1 << 11)

/* Processor Control (E.PC) -- IVOR36-37 अगर KVM_SREGS_E_IVOR */
#घोषणा KVM_SREGS_E_PC			(1 << 12)

/* Page table (E.PT) -- EPTCFG */
#घोषणा KVM_SREGS_E_PT			(1 << 13)

/* Embedded Perक्रमmance Monitor (E.PM) -- IVOR35 अगर KVM_SREGS_E_IVOR */
#घोषणा KVM_SREGS_E_PM			(1 << 14)

/*
 * Special updates:
 *
 * Some रेजिस्टरs may change even जबतक a vcpu is not running.
 * To aव्योम losing these changes, by शेष these रेजिस्टरs are
 * not updated by KVM_SET_SREGS.  To क्रमce an update, set the bit
 * in u.e.update_special corresponding to the रेजिस्टर to be updated.
 *
 * The update_special field is zero on वापस from KVM_GET_SREGS.
 *
 * When restoring a checkpoपूर्णांक, the caller can set update_special
 * to 0xffffffff to ensure that everything is restored, even new features
 * that the caller करोesn't know about.
 */
#घोषणा KVM_SREGS_E_UPDATE_MCSR		(1 << 0)
#घोषणा KVM_SREGS_E_UPDATE_TSR		(1 << 1)
#घोषणा KVM_SREGS_E_UPDATE_DEC		(1 << 2)
#घोषणा KVM_SREGS_E_UPDATE_DBSR		(1 << 3)

/*
 * In KVM_SET_SREGS, reserved/pad fields must be left untouched from a
 * previous KVM_GET_REGS.
 *
 * Unless otherwise indicated, setting any रेजिस्टर with KVM_SET_SREGS
 * directly sets its value.  It करोes not trigger any special semantics such
 * as ग_लिखो-one-to-clear.  Calling KVM_SET_SREGS on an unmodअगरied काष्ठा
 * just received from KVM_GET_SREGS is always a no-op.
 */
काष्ठा kvm_sregs अणु
	__u32 pvr;
	जोड़ अणु
		काष्ठा अणु
			__u64 sdr1;
			काष्ठा अणु
				काष्ठा अणु
					__u64 slbe;
					__u64 slbv;
				पूर्ण slb[64];
			पूर्ण ppc64;
			काष्ठा अणु
				__u32 sr[16];
				__u64 ibat[8];
				__u64 dbat[8];
			पूर्ण ppc32;
		पूर्ण s;
		काष्ठा अणु
			जोड़ अणु
				काष्ठा अणु /* KVM_SREGS_E_IMPL_FSL */
					__u32 features; /* KVM_SREGS_E_FSL_ */
					__u32 svr;
					__u64 mcar;
					__u32 hid0;

					/* KVM_SREGS_E_FSL_PIDn */
					__u32 pid1, pid2;
				पूर्ण fsl;
				__u8 pad[256];
			पूर्ण impl;

			__u32 features; /* KVM_SREGS_E_ */
			__u32 impl_id;	/* KVM_SREGS_E_IMPL_ */
			__u32 update_special; /* KVM_SREGS_E_UPDATE_ */
			__u32 pir;	/* पढ़ो-only */
			__u64 sprg8;
			__u64 sprg9;	/* E.ED */
			__u64 csrr0;
			__u64 dsrr0;	/* E.ED */
			__u64 mcsrr0;
			__u32 csrr1;
			__u32 dsrr1;	/* E.ED */
			__u32 mcsrr1;
			__u32 esr;
			__u64 dear;
			__u64 ivpr;
			__u64 mcivpr;
			__u64 mcsr;	/* KVM_SREGS_E_UPDATE_MCSR */

			__u32 tsr;	/* KVM_SREGS_E_UPDATE_TSR */
			__u32 tcr;
			__u32 decar;
			__u32 dec;	/* KVM_SREGS_E_UPDATE_DEC */

			/*
			 * Userspace can पढ़ो TB directly, but the
			 * value reported here is consistent with "dec".
			 *
			 * Read-only.
			 */
			__u64 tb;

			__u32 dbsr;	/* KVM_SREGS_E_UPDATE_DBSR */
			__u32 dbcr[3];
			/*
			 * iac/dac रेजिस्टरs are 64bit wide, जबतक this API
			 * पूर्णांकerface provides only lower 32 bits on 64 bit
			 * processors. ONE_REG पूर्णांकerface is added क्रम 64bit
			 * iac/dac रेजिस्टरs.
			 */
			__u32 iac[4];
			__u32 dac[2];
			__u32 dvc[2];
			__u8 num_iac;	/* पढ़ो-only */
			__u8 num_dac;	/* पढ़ो-only */
			__u8 num_dvc;	/* पढ़ो-only */
			__u8 pad;

			__u32 epr;	/* EXP */
			__u32 vrsave;	/* a.k.a. USPRG0 */
			__u32 epcr;	/* KVM_SREGS_E_64 */

			__u32 mas0;
			__u32 mas1;
			__u64 mas2;
			__u64 mas7_3;
			__u32 mas4;
			__u32 mas6;

			__u32 ivor_low[16]; /* IVOR0-15 */
			__u32 ivor_high[18]; /* IVOR32+, plus room to expand */

			__u32 mmucfg;	/* पढ़ो-only */
			__u32 eptcfg;	/* E.PT, पढ़ो-only */
			__u32 tlbcfg[4];/* पढ़ो-only */
			__u32 tlbps[4]; /* पढ़ो-only */

			__u32 eplc, epsc; /* E.PD */
		पूर्ण e;
		__u8 pad[1020];
	पूर्ण u;
पूर्ण;

काष्ठा kvm_fpu अणु
	__u64 fpr[32];
पूर्ण;

/*
 * Defines क्रम h/w अवरोधpoपूर्णांक, watchpoपूर्णांक (पढ़ो, ग_लिखो or both) and
 * software अवरोधpoपूर्णांक.
 * These are used as "type" in KVM_SET_GUEST_DEBUG ioctl and "status"
 * क्रम KVM_DEBUG_EXIT.
 */
#घोषणा KVMPPC_DEBUG_NONE		0x0
#घोषणा KVMPPC_DEBUG_BREAKPOINT		(1UL << 1)
#घोषणा KVMPPC_DEBUG_WATCH_WRITE	(1UL << 2)
#घोषणा KVMPPC_DEBUG_WATCH_READ		(1UL << 3)
काष्ठा kvm_debug_निकास_arch अणु
	__u64 address;
	/*
	 * निकासing to userspace because of h/w अवरोधpoपूर्णांक, watchpoपूर्णांक
	 * (पढ़ो, ग_लिखो or both) and software अवरोधpoपूर्णांक.
	 */
	__u32 status;
	__u32 reserved;
पूर्ण;

/* क्रम KVM_SET_GUEST_DEBUG */
काष्ठा kvm_guest_debug_arch अणु
	काष्ठा अणु
		/* H/W अवरोधpoपूर्णांक/watchpoपूर्णांक address */
		__u64 addr;
		/*
		 * Type denotes h/w अवरोधpoपूर्णांक, पढ़ो watchpoपूर्णांक, ग_लिखो
		 * watchpoपूर्णांक or watchpoपूर्णांक (both पढ़ो and ग_लिखो).
		 */
		__u32 type;
		__u32 reserved;
	पूर्ण bp[16];
पूर्ण;

/* Debug related defines */
/*
 * kvm_guest_debug->control is a 32 bit field. The lower 16 bits are generic
 * and upper 16 bits are architecture specअगरic. Architecture specअगरic defines
 * that ioctl is क्रम setting hardware अवरोधpoपूर्णांक or software अवरोधpoपूर्णांक.
 */
#घोषणा KVM_GUESTDBG_USE_SW_BP		0x00010000
#घोषणा KVM_GUESTDBG_USE_HW_BP		0x00020000

/* definition of रेजिस्टरs in kvm_run */
काष्ठा kvm_sync_regs अणु
पूर्ण;

#घोषणा KVM_INTERRUPT_SET	-1U
#घोषणा KVM_INTERRUPT_UNSET	-2U
#घोषणा KVM_INTERRUPT_SET_LEVEL	-3U

#घोषणा KVM_CPU_440		1
#घोषणा KVM_CPU_E500V2		2
#घोषणा KVM_CPU_3S_32		3
#घोषणा KVM_CPU_3S_64		4
#घोषणा KVM_CPU_E500MC		5

/* क्रम KVM_CAP_SPAPR_TCE */
काष्ठा kvm_create_spapr_tce अणु
	__u64 liobn;
	__u32 winकरोw_size;
पूर्ण;

/* क्रम KVM_CAP_SPAPR_TCE_64 */
काष्ठा kvm_create_spapr_tce_64 अणु
	__u64 liobn;
	__u32 page_shअगरt;
	__u32 flags;
	__u64 offset;	/* in pages */
	__u64 size;	/* in pages */
पूर्ण;

/* क्रम KVM_ALLOCATE_RMA */
काष्ठा kvm_allocate_rma अणु
	__u64 rma_size;
पूर्ण;

/* क्रम KVM_CAP_PPC_RTAS */
काष्ठा kvm_rtas_token_args अणु
	अक्षर name[120];
	__u64 token;	/* Use a token of 0 to undefine a mapping */
पूर्ण;

काष्ठा kvm_book3e_206_tlb_entry अणु
	__u32 mas8;
	__u32 mas1;
	__u64 mas2;
	__u64 mas7_3;
पूर्ण;

काष्ठा kvm_book3e_206_tlb_params अणु
	/*
	 * For mmu types KVM_MMU_FSL_BOOKE_NOHV and KVM_MMU_FSL_BOOKE_HV:
	 *
	 * - The number of ways of TLB0 must be a घातer of two between 2 and
	 *   16.
	 * - TLB1 must be fully associative.
	 * - The size of TLB0 must be a multiple of the number of ways, and
	 *   the number of sets must be a घातer of two.
	 * - The size of TLB1 may not exceed 64 entries.
	 * - TLB0 supports 4 KiB pages.
	 * - The page sizes supported by TLB1 are as indicated by
	 *   TLB1CFG (अगर MMUCFG[MAVN] = 0) or TLB1PS (अगर MMUCFG[MAVN] = 1)
	 *   as वापसed by KVM_GET_SREGS.
	 * - TLB2 and TLB3 are reserved, and their entries in tlb_sizes[]
	 *   and tlb_ways[] must be zero.
	 *
	 * tlb_ways[n] = tlb_sizes[n] means the array is fully associative.
	 *
	 * KVM will adjust TLBnCFG based on the sizes configured here,
	 * though arrays greater than 2048 entries will have TLBnCFG[NENTRY]
	 * set to zero.
	 */
	__u32 tlb_sizes[4];
	__u32 tlb_ways[4];
	__u32 reserved[8];
पूर्ण;

/* For KVM_PPC_GET_HTAB_FD */
काष्ठा kvm_get_htab_fd अणु
	__u64	flags;
	__u64	start_index;
	__u64	reserved[2];
पूर्ण;

/* Values क्रम kvm_get_htab_fd.flags */
#घोषणा KVM_GET_HTAB_BOLTED_ONLY	((__u64)0x1)
#घोषणा KVM_GET_HTAB_WRITE		((__u64)0x2)

/*
 * Data पढ़ो on the file descriptor is क्रमmatted as a series of
 * records, each consisting of a header followed by a series of
 * `n_valid' HPTEs (16 bytes each), which are all valid.  Following
 * those valid HPTEs there are `n_invalid' invalid HPTEs, which
 * are not represented explicitly in the stream.  The same क्रमmat
 * is used क्रम writing.
 */
काष्ठा kvm_get_htab_header अणु
	__u32	index;
	__u16	n_valid;
	__u16	n_invalid;
पूर्ण;

/* For KVM_PPC_CONFIGURE_V3_MMU */
काष्ठा kvm_ppc_mmuv3_cfg अणु
	__u64	flags;
	__u64	process_table;	/* second द्विगुनword of partition table entry */
पूर्ण;

/* Flag values क्रम KVM_PPC_CONFIGURE_V3_MMU */
#घोषणा KVM_PPC_MMUV3_RADIX	1	/* 1 = radix mode, 0 = HPT */
#घोषणा KVM_PPC_MMUV3_GTSE	2	/* global translation shootकरोwn enb. */

/* For KVM_PPC_GET_RMMU_INFO */
काष्ठा kvm_ppc_rmmu_info अणु
	काष्ठा kvm_ppc_radix_geom अणु
		__u8	page_shअगरt;
		__u8	level_bits[4];
		__u8	pad[3];
	पूर्ण	geometries[8];
	__u32	ap_encodings[8];
पूर्ण;

/* For KVM_PPC_GET_CPU_CHAR */
काष्ठा kvm_ppc_cpu_अक्षर अणु
	__u64	अक्षरacter;		/* अक्षरacteristics of the CPU */
	__u64	behaviour;		/* recommended software behaviour */
	__u64	अक्षरacter_mask;		/* valid bits in अक्षरacter */
	__u64	behaviour_mask;		/* valid bits in behaviour */
पूर्ण;

/*
 * Values क्रम अक्षरacter and अक्षरacter_mask.
 * These are identical to the values used by H_GET_CPU_CHARACTERISTICS.
 */
#घोषणा KVM_PPC_CPU_CHAR_SPEC_BAR_ORI31		(1ULL << 63)
#घोषणा KVM_PPC_CPU_CHAR_BCCTRL_SERIALISED	(1ULL << 62)
#घोषणा KVM_PPC_CPU_CHAR_L1D_FLUSH_ORI30	(1ULL << 61)
#घोषणा KVM_PPC_CPU_CHAR_L1D_FLUSH_TRIG2	(1ULL << 60)
#घोषणा KVM_PPC_CPU_CHAR_L1D_THREAD_PRIV	(1ULL << 59)
#घोषणा KVM_PPC_CPU_CHAR_BR_HINT_HONOURED	(1ULL << 58)
#घोषणा KVM_PPC_CPU_CHAR_MTTRIG_THR_RECONF	(1ULL << 57)
#घोषणा KVM_PPC_CPU_CHAR_COUNT_CACHE_DIS	(1ULL << 56)
#घोषणा KVM_PPC_CPU_CHAR_BCCTR_FLUSH_ASSIST	(1ull << 54)

#घोषणा KVM_PPC_CPU_BEHAV_FAVOUR_SECURITY	(1ULL << 63)
#घोषणा KVM_PPC_CPU_BEHAV_L1D_FLUSH_PR		(1ULL << 62)
#घोषणा KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAR	(1ULL << 61)
#घोषणा KVM_PPC_CPU_BEHAV_FLUSH_COUNT_CACHE	(1ull << 58)

/* Per-vcpu XICS पूर्णांकerrupt controller state */
#घोषणा KVM_REG_PPC_ICP_STATE	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x8c)

#घोषणा  KVM_REG_PPC_ICP_CPPR_SHIFT	56	/* current proc priority */
#घोषणा  KVM_REG_PPC_ICP_CPPR_MASK	0xff
#घोषणा  KVM_REG_PPC_ICP_XISR_SHIFT	32	/* पूर्णांकerrupt status field */
#घोषणा  KVM_REG_PPC_ICP_XISR_MASK	0xffffff
#घोषणा  KVM_REG_PPC_ICP_MFRR_SHIFT	24	/* pending IPI priority */
#घोषणा  KVM_REG_PPC_ICP_MFRR_MASK	0xff
#घोषणा  KVM_REG_PPC_ICP_PPRI_SHIFT	16	/* pending irq priority */
#घोषणा  KVM_REG_PPC_ICP_PPRI_MASK	0xff

#घोषणा KVM_REG_PPC_VP_STATE	(KVM_REG_PPC | KVM_REG_SIZE_U128 | 0x8d)

/* Device control API: PPC-specअगरic devices */
#घोषणा KVM_DEV_MPIC_GRP_MISC		1
#घोषणा   KVM_DEV_MPIC_BASE_ADDR	0	/* 64-bit */

#घोषणा KVM_DEV_MPIC_GRP_REGISTER	2	/* 32-bit */
#घोषणा KVM_DEV_MPIC_GRP_IRQ_ACTIVE	3	/* 32-bit */

/* One-Reg API: PPC-specअगरic रेजिस्टरs */
#घोषणा KVM_REG_PPC_HIOR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x1)
#घोषणा KVM_REG_PPC_IAC1	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x2)
#घोषणा KVM_REG_PPC_IAC2	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x3)
#घोषणा KVM_REG_PPC_IAC3	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x4)
#घोषणा KVM_REG_PPC_IAC4	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x5)
#घोषणा KVM_REG_PPC_DAC1	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x6)
#घोषणा KVM_REG_PPC_DAC2	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x7)
#घोषणा KVM_REG_PPC_DABR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x8)
#घोषणा KVM_REG_PPC_DSCR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x9)
#घोषणा KVM_REG_PPC_PURR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa)
#घोषणा KVM_REG_PPC_SPURR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xb)
#घोषणा KVM_REG_PPC_DAR		(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xc)
#घोषणा KVM_REG_PPC_DSISR	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0xd)
#घोषणा KVM_REG_PPC_AMR		(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xe)
#घोषणा KVM_REG_PPC_UAMOR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xf)

#घोषणा KVM_REG_PPC_MMCR0	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x10)
#घोषणा KVM_REG_PPC_MMCR1	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x11)
#घोषणा KVM_REG_PPC_MMCRA	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x12)
#घोषणा KVM_REG_PPC_MMCR2	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x13)
#घोषणा KVM_REG_PPC_MMCRS	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x14)
#घोषणा KVM_REG_PPC_SIAR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x15)
#घोषणा KVM_REG_PPC_SDAR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x16)
#घोषणा KVM_REG_PPC_SIER	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x17)

#घोषणा KVM_REG_PPC_PMC1	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x18)
#घोषणा KVM_REG_PPC_PMC2	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x19)
#घोषणा KVM_REG_PPC_PMC3	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x1a)
#घोषणा KVM_REG_PPC_PMC4	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x1b)
#घोषणा KVM_REG_PPC_PMC5	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x1c)
#घोषणा KVM_REG_PPC_PMC6	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x1d)
#घोषणा KVM_REG_PPC_PMC7	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x1e)
#घोषणा KVM_REG_PPC_PMC8	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x1f)

/* 32 भग्नing-poपूर्णांक रेजिस्टरs */
#घोषणा KVM_REG_PPC_FPR0	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x20)
#घोषणा KVM_REG_PPC_FPR(n)	(KVM_REG_PPC_FPR0 + (n))
#घोषणा KVM_REG_PPC_FPR31	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x3f)

/* 32 VMX/Altivec vector रेजिस्टरs */
#घोषणा KVM_REG_PPC_VR0		(KVM_REG_PPC | KVM_REG_SIZE_U128 | 0x40)
#घोषणा KVM_REG_PPC_VR(n)	(KVM_REG_PPC_VR0 + (n))
#घोषणा KVM_REG_PPC_VR31	(KVM_REG_PPC | KVM_REG_SIZE_U128 | 0x5f)

/* 32 द्विगुन-width FP रेजिस्टरs क्रम VSX */
/* High-order halves overlap with FP regs */
#घोषणा KVM_REG_PPC_VSR0	(KVM_REG_PPC | KVM_REG_SIZE_U128 | 0x60)
#घोषणा KVM_REG_PPC_VSR(n)	(KVM_REG_PPC_VSR0 + (n))
#घोषणा KVM_REG_PPC_VSR31	(KVM_REG_PPC | KVM_REG_SIZE_U128 | 0x7f)

/* FP and vector status/control रेजिस्टरs */
#घोषणा KVM_REG_PPC_FPSCR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x80)
/*
 * VSCR रेजिस्टर is करोcumented as a 32-bit रेजिस्टर in the ISA, but it can
 * only be accesses via a vector रेजिस्टर. Expose VSCR as a 32-bit रेजिस्टर
 * even though the kernel represents it as a 128-bit vector.
 */
#घोषणा KVM_REG_PPC_VSCR	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x81)

/* Virtual processor areas */
/* For SLB & DTL, address in high (first) half, length in low half */
#घोषणा KVM_REG_PPC_VPA_ADDR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x82)
#घोषणा KVM_REG_PPC_VPA_SLB	(KVM_REG_PPC | KVM_REG_SIZE_U128 | 0x83)
#घोषणा KVM_REG_PPC_VPA_DTL	(KVM_REG_PPC | KVM_REG_SIZE_U128 | 0x84)

#घोषणा KVM_REG_PPC_EPCR	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x85)
#घोषणा KVM_REG_PPC_EPR		(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x86)

/* Timer Status Register OR/CLEAR पूर्णांकerface */
#घोषणा KVM_REG_PPC_OR_TSR	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x87)
#घोषणा KVM_REG_PPC_CLEAR_TSR	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x88)
#घोषणा KVM_REG_PPC_TCR		(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x89)
#घोषणा KVM_REG_PPC_TSR		(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x8a)

/* Debugging: Special inकाष्ठाion क्रम software अवरोधpoपूर्णांक */
#घोषणा KVM_REG_PPC_DEBUG_INST	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x8b)

/* MMU रेजिस्टरs */
#घोषणा KVM_REG_PPC_MAS0	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x8c)
#घोषणा KVM_REG_PPC_MAS1	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x8d)
#घोषणा KVM_REG_PPC_MAS2	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x8e)
#घोषणा KVM_REG_PPC_MAS7_3	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x8f)
#घोषणा KVM_REG_PPC_MAS4	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x90)
#घोषणा KVM_REG_PPC_MAS6	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x91)
#घोषणा KVM_REG_PPC_MMUCFG	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x92)
/*
 * TLBnCFG fields TLBnCFG_N_ENTRY and TLBnCFG_ASSOC can be changed only using
 * KVM_CAP_SW_TLB ioctl
 */
#घोषणा KVM_REG_PPC_TLB0CFG	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x93)
#घोषणा KVM_REG_PPC_TLB1CFG	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x94)
#घोषणा KVM_REG_PPC_TLB2CFG	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x95)
#घोषणा KVM_REG_PPC_TLB3CFG	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x96)
#घोषणा KVM_REG_PPC_TLB0PS	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x97)
#घोषणा KVM_REG_PPC_TLB1PS	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x98)
#घोषणा KVM_REG_PPC_TLB2PS	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x99)
#घोषणा KVM_REG_PPC_TLB3PS	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x9a)
#घोषणा KVM_REG_PPC_EPTCFG	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x9b)

/* Timebase offset */
#घोषणा KVM_REG_PPC_TB_OFFSET	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x9c)

/* POWER8 रेजिस्टरs */
#घोषणा KVM_REG_PPC_SPMC1	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x9d)
#घोषणा KVM_REG_PPC_SPMC2	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0x9e)
#घोषणा KVM_REG_PPC_IAMR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0x9f)
#घोषणा KVM_REG_PPC_TFHAR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa0)
#घोषणा KVM_REG_PPC_TFIAR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa1)
#घोषणा KVM_REG_PPC_TEXASR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa2)
#घोषणा KVM_REG_PPC_FSCR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa3)
#घोषणा KVM_REG_PPC_PSPB	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0xa4)
#घोषणा KVM_REG_PPC_EBBHR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa5)
#घोषणा KVM_REG_PPC_EBBRR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa6)
#घोषणा KVM_REG_PPC_BESCR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa7)
#घोषणा KVM_REG_PPC_TAR		(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa8)
#घोषणा KVM_REG_PPC_DPDES	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xa9)
#घोषणा KVM_REG_PPC_DAWR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xaa)
#घोषणा KVM_REG_PPC_DAWRX	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xab)
#घोषणा KVM_REG_PPC_CIABR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xac)
#घोषणा KVM_REG_PPC_IC		(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xad)
#घोषणा KVM_REG_PPC_VTB		(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xae)
#घोषणा KVM_REG_PPC_CSIGR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xaf)
#घोषणा KVM_REG_PPC_TACR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xb0)
#घोषणा KVM_REG_PPC_TCSCR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xb1)
#घोषणा KVM_REG_PPC_PID		(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xb2)
#घोषणा KVM_REG_PPC_ACOP	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xb3)

#घोषणा KVM_REG_PPC_VRSAVE	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0xb4)
#घोषणा KVM_REG_PPC_LPCR	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0xb5)
#घोषणा KVM_REG_PPC_LPCR_64	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xb5)
#घोषणा KVM_REG_PPC_PPR		(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xb6)

/* Architecture compatibility level */
#घोषणा KVM_REG_PPC_ARCH_COMPAT	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0xb7)

#घोषणा KVM_REG_PPC_DABRX	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0xb8)
#घोषणा KVM_REG_PPC_WORT	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xb9)
#घोषणा KVM_REG_PPC_SPRG9	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xba)
#घोषणा KVM_REG_PPC_DBSR	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0xbb)

/* POWER9 रेजिस्टरs */
#घोषणा KVM_REG_PPC_TIDR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xbc)
#घोषणा KVM_REG_PPC_PSSCR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xbd)

#घोषणा KVM_REG_PPC_DEC_EXPIRY	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xbe)
#घोषणा KVM_REG_PPC_ONLINE	(KVM_REG_PPC | KVM_REG_SIZE_U32 | 0xbf)
#घोषणा KVM_REG_PPC_PTCR	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xc0)

/* POWER10 रेजिस्टरs */
#घोषणा KVM_REG_PPC_MMCR3	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xc1)
#घोषणा KVM_REG_PPC_SIER2	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xc2)
#घोषणा KVM_REG_PPC_SIER3	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xc3)
#घोषणा KVM_REG_PPC_DAWR1	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xc4)
#घोषणा KVM_REG_PPC_DAWRX1	(KVM_REG_PPC | KVM_REG_SIZE_U64 | 0xc5)

/* Transactional Memory checkpoपूर्णांकed state:
 * This is all GPRs, all VSX regs and a subset of SPRs
 */
#घोषणा KVM_REG_PPC_TM		(KVM_REG_PPC | 0x80000000)
/* TM GPRs */
#घोषणा KVM_REG_PPC_TM_GPR0	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0)
#घोषणा KVM_REG_PPC_TM_GPR(n)	(KVM_REG_PPC_TM_GPR0 + (n))
#घोषणा KVM_REG_PPC_TM_GPR31	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x1f)
/* TM VSX */
#घोषणा KVM_REG_PPC_TM_VSR0	(KVM_REG_PPC_TM | KVM_REG_SIZE_U128 | 0x20)
#घोषणा KVM_REG_PPC_TM_VSR(n)	(KVM_REG_PPC_TM_VSR0 + (n))
#घोषणा KVM_REG_PPC_TM_VSR63	(KVM_REG_PPC_TM | KVM_REG_SIZE_U128 | 0x5f)
/* TM SPRS */
#घोषणा KVM_REG_PPC_TM_CR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x60)
#घोषणा KVM_REG_PPC_TM_LR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x61)
#घोषणा KVM_REG_PPC_TM_CTR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x62)
#घोषणा KVM_REG_PPC_TM_FPSCR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x63)
#घोषणा KVM_REG_PPC_TM_AMR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x64)
#घोषणा KVM_REG_PPC_TM_PPR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x65)
#घोषणा KVM_REG_PPC_TM_VRSAVE	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x66)
#घोषणा KVM_REG_PPC_TM_VSCR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U32 | 0x67)
#घोषणा KVM_REG_PPC_TM_DSCR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x68)
#घोषणा KVM_REG_PPC_TM_TAR	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x69)
#घोषणा KVM_REG_PPC_TM_XER	(KVM_REG_PPC_TM | KVM_REG_SIZE_U64 | 0x6a)

/* PPC64 eXternal Interrupt Controller Specअगरication */
#घोषणा KVM_DEV_XICS_GRP_SOURCES	1	/* 64-bit source attributes */
#घोषणा KVM_DEV_XICS_GRP_CTRL		2
#घोषणा   KVM_DEV_XICS_NR_SERVERS	1

/* Layout of 64-bit source attribute values */
#घोषणा  KVM_XICS_DESTINATION_SHIFT	0
#घोषणा  KVM_XICS_DESTINATION_MASK	0xffffffffULL
#घोषणा  KVM_XICS_PRIORITY_SHIFT	32
#घोषणा  KVM_XICS_PRIORITY_MASK		0xff
#घोषणा  KVM_XICS_LEVEL_SENSITIVE	(1ULL << 40)
#घोषणा  KVM_XICS_MASKED		(1ULL << 41)
#घोषणा  KVM_XICS_PENDING		(1ULL << 42)
#घोषणा  KVM_XICS_PRESENTED		(1ULL << 43)
#घोषणा  KVM_XICS_QUEUED		(1ULL << 44)

/* POWER9 XIVE Native Interrupt Controller */
#घोषणा KVM_DEV_XIVE_GRP_CTRL		1
#घोषणा   KVM_DEV_XIVE_RESET		1
#घोषणा   KVM_DEV_XIVE_EQ_SYNC		2
#घोषणा   KVM_DEV_XIVE_NR_SERVERS	3
#घोषणा KVM_DEV_XIVE_GRP_SOURCE		2	/* 64-bit source identअगरier */
#घोषणा KVM_DEV_XIVE_GRP_SOURCE_CONFIG	3	/* 64-bit source identअगरier */
#घोषणा KVM_DEV_XIVE_GRP_EQ_CONFIG	4	/* 64-bit EQ identअगरier */
#घोषणा KVM_DEV_XIVE_GRP_SOURCE_SYNC	5       /* 64-bit source identअगरier */

/* Layout of 64-bit XIVE source attribute values */
#घोषणा KVM_XIVE_LEVEL_SENSITIVE	(1ULL << 0)
#घोषणा KVM_XIVE_LEVEL_ASSERTED		(1ULL << 1)

/* Layout of 64-bit XIVE source configuration attribute values */
#घोषणा KVM_XIVE_SOURCE_PRIORITY_SHIFT	0
#घोषणा KVM_XIVE_SOURCE_PRIORITY_MASK	0x7
#घोषणा KVM_XIVE_SOURCE_SERVER_SHIFT	3
#घोषणा KVM_XIVE_SOURCE_SERVER_MASK	0xfffffff8ULL
#घोषणा KVM_XIVE_SOURCE_MASKED_SHIFT	32
#घोषणा KVM_XIVE_SOURCE_MASKED_MASK	0x100000000ULL
#घोषणा KVM_XIVE_SOURCE_EISN_SHIFT	33
#घोषणा KVM_XIVE_SOURCE_EISN_MASK	0xfffffffe00000000ULL

/* Layout of 64-bit EQ identअगरier */
#घोषणा KVM_XIVE_EQ_PRIORITY_SHIFT	0
#घोषणा KVM_XIVE_EQ_PRIORITY_MASK	0x7
#घोषणा KVM_XIVE_EQ_SERVER_SHIFT	3
#घोषणा KVM_XIVE_EQ_SERVER_MASK		0xfffffff8ULL

/* Layout of EQ configuration values (64 bytes) */
काष्ठा kvm_ppc_xive_eq अणु
	__u32 flags;
	__u32 qshअगरt;
	__u64 qaddr;
	__u32 qtoggle;
	__u32 qindex;
	__u8  pad[40];
पूर्ण;

#घोषणा KVM_XIVE_EQ_ALWAYS_NOTIFY	0x00000001

#घोषणा KVM_XIVE_TIMA_PAGE_OFFSET	0
#घोषणा KVM_XIVE_ESB_PAGE_OFFSET	4

#पूर्ण_अगर /* __LINUX_KVM_POWERPC_H */
