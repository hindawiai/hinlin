<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Contains the definition of रेजिस्टरs common to all PowerPC variants.
 * If a रेजिस्टर definition has been changed in a dअगरferent PowerPC
 * variant, we will हाल it in #अगर_अघोषित XXX ... #पूर्ण_अगर, and have the
 * number used in the Programming Environments Manual For 32-Bit
 * Implementations of the PowerPC Architecture (a.k.a. Green Book) here.
 */

#अगर_अघोषित _ASM_POWERPC_REG_H
#घोषणा _ASM_POWERPC_REG_H
#अगर_घोषित __KERNEL__

#समावेश <linux/stringअगरy.h>
#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>
#समावेश <यंत्र/feature-fixups.h>

/* Pickup Book E specअगरic रेजिस्टरs. */
#अगर defined(CONFIG_BOOKE) || defined(CONFIG_40x)
#समावेश <यंत्र/reg_booke.h>
#पूर्ण_अगर /* CONFIG_BOOKE || CONFIG_40x */

#अगर_घोषित CONFIG_FSL_EMB_PERFMON
#समावेश <यंत्र/reg_fsl_emb.h>
#पूर्ण_अगर

#समावेश <यंत्र/reg_8xx.h>

#घोषणा MSR_SF_LG	63              /* Enable 64 bit mode */
#घोषणा MSR_HV_LG 	60              /* Hypervisor state */
#घोषणा MSR_TS_T_LG	34		/* Trans Mem state: Transactional */
#घोषणा MSR_TS_S_LG	33		/* Trans Mem state: Suspended */
#घोषणा MSR_TS_LG	33		/* Trans Mem state (2 bits) */
#घोषणा MSR_TM_LG	32		/* Trans Mem Available */
#घोषणा MSR_VEC_LG	25	        /* Enable AltiVec */
#घोषणा MSR_VSX_LG	23		/* Enable VSX */
#घोषणा MSR_S_LG	22		/* Secure state */
#घोषणा MSR_POW_LG	18		/* Enable Power Management */
#घोषणा MSR_WE_LG	18		/* Wait State Enable */
#घोषणा MSR_TGPR_LG	17		/* TLB Update रेजिस्टरs in use */
#घोषणा MSR_CE_LG	17		/* Critical Interrupt Enable */
#घोषणा MSR_ILE_LG	16		/* Interrupt Little Endian */
#घोषणा MSR_EE_LG	15		/* External Interrupt Enable */
#घोषणा MSR_PR_LG	14		/* Problem State / Privilege Level */
#घोषणा MSR_FP_LG	13		/* Floating Poपूर्णांक enable */
#घोषणा MSR_ME_LG	12		/* Machine Check Enable */
#घोषणा MSR_FE0_LG	11		/* Floating Exception mode 0 */
#घोषणा MSR_SE_LG	10		/* Single Step */
#घोषणा MSR_BE_LG	9		/* Branch Trace */
#घोषणा MSR_DE_LG	9 		/* Debug Exception Enable */
#घोषणा MSR_FE1_LG	8		/* Floating Exception mode 1 */
#घोषणा MSR_IP_LG	6		/* Exception prefix 0x000/0xFFF */
#घोषणा MSR_IR_LG	5 		/* Inकाष्ठाion Relocate */
#घोषणा MSR_DR_LG	4 		/* Data Relocate */
#घोषणा MSR_PE_LG	3		/* Protection Enable */
#घोषणा MSR_PX_LG	2		/* Protection Exclusive Mode */
#घोषणा MSR_PMM_LG	2		/* Perक्रमmance monitor */
#घोषणा MSR_RI_LG	1		/* Recoverable Exception */
#घोषणा MSR_LE_LG	0 		/* Little Endian */

#अगर_घोषित __ASSEMBLY__
#घोषणा __MASK(X)	(1<<(X))
#अन्यथा
#घोषणा __MASK(X)	(1UL<<(X))
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
#घोषणा MSR_SF		__MASK(MSR_SF_LG)	/* Enable 64 bit mode */
#घोषणा MSR_HV 		__MASK(MSR_HV_LG)	/* Hypervisor state */
#घोषणा MSR_S		__MASK(MSR_S_LG)	/* Secure state */
#अन्यथा
/* so tests क्रम these bits fail on 32-bit */
#घोषणा MSR_SF		0
#घोषणा MSR_HV		0
#घोषणा MSR_S		0
#पूर्ण_अगर

/*
 * To be used in shared book E/book S, this aव्योमs needing to worry about
 * book S/book E in shared code
 */
#अगर_अघोषित MSR_SPE
#घोषणा MSR_SPE 	0
#पूर्ण_अगर

#घोषणा MSR_VEC		__MASK(MSR_VEC_LG)	/* Enable AltiVec */
#घोषणा MSR_VSX		__MASK(MSR_VSX_LG)	/* Enable VSX */
#घोषणा MSR_POW		__MASK(MSR_POW_LG)	/* Enable Power Management */
#घोषणा MSR_WE		__MASK(MSR_WE_LG)	/* Wait State Enable */
#घोषणा MSR_TGPR	__MASK(MSR_TGPR_LG)	/* TLB Update रेजिस्टरs in use */
#घोषणा MSR_CE		__MASK(MSR_CE_LG)	/* Critical Interrupt Enable */
#घोषणा MSR_ILE		__MASK(MSR_ILE_LG)	/* Interrupt Little Endian */
#घोषणा MSR_EE		__MASK(MSR_EE_LG)	/* External Interrupt Enable */
#घोषणा MSR_PR		__MASK(MSR_PR_LG)	/* Problem State / Privilege Level */
#घोषणा MSR_FP		__MASK(MSR_FP_LG)	/* Floating Poपूर्णांक enable */
#घोषणा MSR_ME		__MASK(MSR_ME_LG)	/* Machine Check Enable */
#घोषणा MSR_FE0		__MASK(MSR_FE0_LG)	/* Floating Exception mode 0 */
#घोषणा MSR_SE		__MASK(MSR_SE_LG)	/* Single Step */
#घोषणा MSR_BE		__MASK(MSR_BE_LG)	/* Branch Trace */
#घोषणा MSR_DE		__MASK(MSR_DE_LG)	/* Debug Exception Enable */
#घोषणा MSR_FE1		__MASK(MSR_FE1_LG)	/* Floating Exception mode 1 */
#घोषणा MSR_IP		__MASK(MSR_IP_LG)	/* Exception prefix 0x000/0xFFF */
#घोषणा MSR_IR		__MASK(MSR_IR_LG)	/* Inकाष्ठाion Relocate */
#घोषणा MSR_DR		__MASK(MSR_DR_LG)	/* Data Relocate */
#घोषणा MSR_PE		__MASK(MSR_PE_LG)	/* Protection Enable */
#घोषणा MSR_PX		__MASK(MSR_PX_LG)	/* Protection Exclusive Mode */
#अगर_अघोषित MSR_PMM
#घोषणा MSR_PMM		__MASK(MSR_PMM_LG)	/* Perक्रमmance monitor */
#पूर्ण_अगर
#घोषणा MSR_RI		__MASK(MSR_RI_LG)	/* Recoverable Exception */
#घोषणा MSR_LE		__MASK(MSR_LE_LG)	/* Little Endian */

#घोषणा MSR_TM		__MASK(MSR_TM_LG)	/* Transactional Mem Available */
#घोषणा MSR_TS_N	0			/*  Non-transactional */
#घोषणा MSR_TS_S	__MASK(MSR_TS_S_LG)	/*  Transaction Suspended */
#घोषणा MSR_TS_T	__MASK(MSR_TS_T_LG)	/*  Transaction Transactional */
#घोषणा MSR_TS_MASK	(MSR_TS_T | MSR_TS_S)   /* Transaction State bits */
#घोषणा MSR_TM_RESV(x) (((x) & MSR_TS_MASK) == MSR_TS_MASK) /* Reserved */
#घोषणा MSR_TM_TRANSACTIONAL(x)	(((x) & MSR_TS_MASK) == MSR_TS_T)
#घोषणा MSR_TM_SUSPENDED(x)	(((x) & MSR_TS_MASK) == MSR_TS_S)

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
#घोषणा MSR_TM_ACTIVE(x) (((x) & MSR_TS_MASK) != 0) /* Transaction active? */
#अन्यथा
#घोषणा MSR_TM_ACTIVE(x) ((व्योम)(x), 0)
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_BOOK3S_64)
#घोषणा MSR_64BIT	MSR_SF

/* Server variant */
#घोषणा __MSR		(MSR_ME | MSR_RI | MSR_IR | MSR_DR | MSR_HV)
#अगर_घोषित __BIG_ENDIAN__
#घोषणा MSR_		__MSR
#घोषणा MSR_IDLE	(MSR_ME | MSR_SF | MSR_HV)
#अन्यथा
#घोषणा MSR_		(__MSR | MSR_LE)
#घोषणा MSR_IDLE	(MSR_ME | MSR_SF | MSR_HV | MSR_LE)
#पूर्ण_अगर
#घोषणा MSR_KERNEL	(MSR_ | MSR_64BIT)
#घोषणा MSR_USER32	(MSR_ | MSR_PR | MSR_EE)
#घोषणा MSR_USER64	(MSR_USER32 | MSR_64BIT)
#या_अगर defined(CONFIG_PPC_BOOK3S_32) || defined(CONFIG_PPC_8xx)
/* Default MSR क्रम kernel mode. */
#घोषणा MSR_KERNEL	(MSR_ME|MSR_RI|MSR_IR|MSR_DR)
#घोषणा MSR_USER	(MSR_KERNEL|MSR_PR|MSR_EE)
#पूर्ण_अगर

#अगर_अघोषित MSR_64BIT
#घोषणा MSR_64BIT	0
#पूर्ण_अगर

/* Condition Register related */
#घोषणा CR0_SHIFT	28
#घोषणा CR0_MASK	0xF
#घोषणा CR0_TBEGIN_FAILURE	(0x2 << 28) /* 0b0010 */


/* Power Management - Processor Stop Status and Control Register Fields */
#घोषणा PSSCR_RL_MASK		0x0000000F /* Requested Level */
#घोषणा PSSCR_MTL_MASK		0x000000F0 /* Maximum Transition Level */
#घोषणा PSSCR_TR_MASK		0x00000300 /* Transition State */
#घोषणा PSSCR_PSLL_MASK		0x000F0000 /* Power-Saving Level Limit */
#घोषणा PSSCR_EC		0x00100000 /* Exit Criterion */
#घोषणा PSSCR_ESL		0x00200000 /* Enable State Loss */
#घोषणा PSSCR_SD		0x00400000 /* Status Disable */
#घोषणा PSSCR_PLS	0xf000000000000000 /* Power-saving Level Status */
#घोषणा PSSCR_PLS_SHIFT	60
#घोषणा PSSCR_GUEST_VIS	0xf0000000000003ffUL /* Guest-visible PSSCR fields */
#घोषणा PSSCR_FAKE_SUSPEND	0x00000400 /* Fake-suspend bit (P9 DD2.2) */
#घोषणा PSSCR_FAKE_SUSPEND_LG	10	   /* Fake-suspend bit position */

/* Floating Poपूर्णांक Status and Control Register (FPSCR) Fields */
#घोषणा FPSCR_FX	0x80000000	/* FPU exception summary */
#घोषणा FPSCR_FEX	0x40000000	/* FPU enabled exception summary */
#घोषणा FPSCR_VX	0x20000000	/* Invalid operation summary */
#घोषणा FPSCR_OX	0x10000000	/* Overflow exception summary */
#घोषणा FPSCR_UX	0x08000000	/* Underflow exception summary */
#घोषणा FPSCR_ZX	0x04000000	/* Zero-भागide exception summary */
#घोषणा FPSCR_XX	0x02000000	/* Inexact exception summary */
#घोषणा FPSCR_VXSन_अंक	0x01000000	/* Invalid op क्रम SNaN */
#घोषणा FPSCR_VXISI	0x00800000	/* Invalid op क्रम Inv - Inv */
#घोषणा FPSCR_VXIDI	0x00400000	/* Invalid op क्रम Inv / Inv */
#घोषणा FPSCR_VXZDZ	0x00200000	/* Invalid op क्रम Zero / Zero */
#घोषणा FPSCR_VXIMZ	0x00100000	/* Invalid op क्रम Inv * Zero */
#घोषणा FPSCR_VXVC	0x00080000	/* Invalid op क्रम Compare */
#घोषणा FPSCR_FR	0x00040000	/* Fraction rounded */
#घोषणा FPSCR_FI	0x00020000	/* Fraction inexact */
#घोषणा FPSCR_FPRF	0x0001f000	/* FPU Result Flags */
#घोषणा FPSCR_FPCC	0x0000f000	/* FPU Condition Codes */
#घोषणा FPSCR_VXSOFT	0x00000400	/* Invalid op क्रम software request */
#घोषणा FPSCR_VXSQRT	0x00000200	/* Invalid op क्रम square root */
#घोषणा FPSCR_VXCVI	0x00000100	/* Invalid op क्रम पूर्णांकeger convert */
#घोषणा FPSCR_VE	0x00000080	/* Invalid op exception enable */
#घोषणा FPSCR_OE	0x00000040	/* IEEE overflow exception enable */
#घोषणा FPSCR_UE	0x00000020	/* IEEE underflow exception enable */
#घोषणा FPSCR_ZE	0x00000010	/* IEEE zero भागide exception enable */
#घोषणा FPSCR_XE	0x00000008	/* FP inexact exception enable */
#घोषणा FPSCR_NI	0x00000004	/* FPU non IEEE-Mode */
#घोषणा FPSCR_RN	0x00000003	/* FPU rounding control */

/* Bit definitions क्रम SPEFSCR. */
#घोषणा SPEFSCR_SOVH	0x80000000	/* Summary पूर्णांकeger overflow high */
#घोषणा SPEFSCR_OVH	0x40000000	/* Integer overflow high */
#घोषणा SPEFSCR_FGH	0x20000000	/* Embedded FP guard bit high */
#घोषणा SPEFSCR_FXH	0x10000000	/* Embedded FP sticky bit high */
#घोषणा SPEFSCR_FINVH	0x08000000	/* Embedded FP invalid operation high */
#घोषणा SPEFSCR_FDBZH	0x04000000	/* Embedded FP भाग by zero high */
#घोषणा SPEFSCR_FUNFH	0x02000000	/* Embedded FP underflow high */
#घोषणा SPEFSCR_FOVFH	0x01000000	/* Embedded FP overflow high */
#घोषणा SPEFSCR_FINXS	0x00200000	/* Embedded FP inexact sticky */
#घोषणा SPEFSCR_FINVS	0x00100000	/* Embedded FP invalid op. sticky */
#घोषणा SPEFSCR_FDBZS	0x00080000	/* Embedded FP भाग by zero sticky */
#घोषणा SPEFSCR_FUNFS	0x00040000	/* Embedded FP underflow sticky */
#घोषणा SPEFSCR_FOVFS	0x00020000	/* Embedded FP overflow sticky */
#घोषणा SPEFSCR_MODE	0x00010000	/* Embedded FP mode */
#घोषणा SPEFSCR_SOV	0x00008000	/* Integer summary overflow */
#घोषणा SPEFSCR_OV	0x00004000	/* Integer overflow */
#घोषणा SPEFSCR_FG	0x00002000	/* Embedded FP guard bit */
#घोषणा SPEFSCR_FX	0x00001000	/* Embedded FP sticky bit */
#घोषणा SPEFSCR_FINV	0x00000800	/* Embedded FP invalid operation */
#घोषणा SPEFSCR_FDBZ	0x00000400	/* Embedded FP भाग by zero */
#घोषणा SPEFSCR_FUNF	0x00000200	/* Embedded FP underflow */
#घोषणा SPEFSCR_FOVF	0x00000100	/* Embedded FP overflow */
#घोषणा SPEFSCR_FINXE	0x00000040	/* Embedded FP inexact enable */
#घोषणा SPEFSCR_FINVE	0x00000020	/* Embedded FP invalid op. enable */
#घोषणा SPEFSCR_FDBZE	0x00000010	/* Embedded FP भाग by zero enable */
#घोषणा SPEFSCR_FUNFE	0x00000008	/* Embedded FP underflow enable */
#घोषणा SPEFSCR_FOVFE	0x00000004	/* Embedded FP overflow enable */
#घोषणा SPEFSCR_FRMC 	0x00000003	/* Embedded FP rounding mode control */

/* Special Purpose Registers (SPRNs)*/

#अगर_घोषित CONFIG_40x
#घोषणा SPRN_PID	0x3B1	/* Process ID */
#अन्यथा
#घोषणा SPRN_PID	0x030	/* Process ID */
#अगर_घोषित CONFIG_BOOKE
#घोषणा SPRN_PID0	SPRN_PID/* Process ID Register 0 */
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा SPRN_CTR	0x009	/* Count Register */
#घोषणा SPRN_DSCR	0x11
#घोषणा SPRN_CFAR	0x1c	/* Come From Address Register */
#घोषणा SPRN_AMR	0x1d	/* Authority Mask Register */
#घोषणा SPRN_UAMOR	0x9d	/* User Authority Mask Override Register */
#घोषणा SPRN_AMOR	0x15d	/* Authority Mask Override Register */
#घोषणा SPRN_ACOP	0x1F	/* Available Coprocessor Register */
#घोषणा SPRN_TFIAR	0x81	/* Transaction Failure Inst Addr   */
#घोषणा SPRN_TEXASR	0x82	/* Transaction EXception & Summary */
#घोषणा SPRN_TEXASRU	0x83	/* ''	   ''	   ''	 Upper 32  */

#घोषणा TEXASR_FC_LG	(63 - 7)	/* Failure Code */
#घोषणा TEXASR_AB_LG	(63 - 31)	/* Abort */
#घोषणा TEXASR_SU_LG	(63 - 32)	/* Suspend */
#घोषणा TEXASR_HV_LG	(63 - 34)	/* Hypervisor state*/
#घोषणा TEXASR_PR_LG	(63 - 35)	/* Privilege level */
#घोषणा TEXASR_FS_LG	(63 - 36)	/* failure summary */
#घोषणा TEXASR_EX_LG	(63 - 37)	/* TFIAR exact bit */
#घोषणा TEXASR_ROT_LG	(63 - 38)	/* ROT bit */

#घोषणा   TEXASR_ABORT	__MASK(TEXASR_AB_LG) /* terminated by tपात or treclaim */
#घोषणा   TEXASR_SUSP	__MASK(TEXASR_SU_LG) /* tx failed in suspended state */
#घोषणा   TEXASR_HV	__MASK(TEXASR_HV_LG) /* MSR[HV] when failure occurred */
#घोषणा   TEXASR_PR	__MASK(TEXASR_PR_LG) /* MSR[PR] when failure occurred */
#घोषणा   TEXASR_FS	__MASK(TEXASR_FS_LG) /* TEXASR Failure Summary */
#घोषणा   TEXASR_EXACT	__MASK(TEXASR_EX_LG) /* TFIAR value is exact */
#घोषणा   TEXASR_ROT	__MASK(TEXASR_ROT_LG)
#घोषणा   TEXASR_FC	(ASM_CONST(0xFF) << TEXASR_FC_LG)

#घोषणा SPRN_TFHAR	0x80	/* Transaction Failure Handler Addr */

#घोषणा SPRN_TIDR	144	/* Thपढ़ो ID रेजिस्टर */
#घोषणा SPRN_CTRLF	0x088
#घोषणा SPRN_CTRLT	0x098
#घोषणा   CTRL_CT	0xc0000000	/* current thपढ़ो */
#घोषणा   CTRL_CT0	0x80000000	/* thपढ़ो 0 */
#घोषणा   CTRL_CT1	0x40000000	/* thपढ़ो 1 */
#घोषणा   CTRL_TE	0x00c00000	/* thपढ़ो enable */
#घोषणा   CTRL_RUNLATCH	0x1
#घोषणा SPRN_DAWR0	0xB4
#घोषणा SPRN_DAWR1	0xB5
#घोषणा SPRN_RPR	0xBA	/* Relative Priority Register */
#घोषणा SPRN_CIABR	0xBB
#घोषणा   CIABR_PRIV		0x3
#घोषणा   CIABR_PRIV_USER	1
#घोषणा   CIABR_PRIV_SUPER	2
#घोषणा   CIABR_PRIV_HYPER	3
#घोषणा SPRN_DAWRX0	0xBC
#घोषणा SPRN_DAWRX1	0xBD
#घोषणा   DAWRX_USER	__MASK(0)
#घोषणा   DAWRX_KERNEL	__MASK(1)
#घोषणा   DAWRX_HYP	__MASK(2)
#घोषणा   DAWRX_WTI	__MASK(3)
#घोषणा   DAWRX_WT	__MASK(4)
#घोषणा   DAWRX_DR	__MASK(5)
#घोषणा   DAWRX_DW	__MASK(6)
#घोषणा SPRN_DABR	0x3F5	/* Data Address Breakpoपूर्णांक Register */
#घोषणा SPRN_DABR2	0x13D	/* e300 */
#घोषणा SPRN_DABRX	0x3F7	/* Data Address Breakpoपूर्णांक Register Extension */
#घोषणा   DABRX_USER	__MASK(0)
#घोषणा   DABRX_KERNEL	__MASK(1)
#घोषणा   DABRX_HYP	__MASK(2)
#घोषणा   DABRX_BTI	__MASK(3)
#घोषणा   DABRX_ALL     (DABRX_BTI | DABRX_HYP | DABRX_KERNEL | DABRX_USER)
#घोषणा SPRN_DAR	0x013	/* Data Address Register */
#घोषणा SPRN_DBCR	0x136	/* e300 Data Breakpoपूर्णांक Control Reg */
#घोषणा SPRN_DSISR	0x012	/* Data Storage Interrupt Status Register */
#घोषणा   DSISR_BAD_सूचीECT_ST	0x80000000 /* Obsolete: Direct store error */
#घोषणा   DSISR_NOHPTE		0x40000000 /* no translation found */
#घोषणा   DSISR_ATTR_CONFLICT	0x20000000 /* P9: Process vs. Partition attr */
#घोषणा   DSISR_NOEXEC_OR_G	0x10000000 /* Alias of SRR1 bit, see below */
#घोषणा   DSISR_PROTFAULT	0x08000000 /* protection fault */
#घोषणा   DSISR_BADACCESS	0x04000000 /* bad access to CI or G */
#घोषणा   DSISR_ISSTORE		0x02000000 /* access was a store */
#घोषणा   DSISR_DABRMATCH	0x00400000 /* hit data अवरोधpoपूर्णांक */
#घोषणा   DSISR_NOSEGMENT	0x00200000 /* STAB miss (unsupported) */
#घोषणा   DSISR_KEYFAULT	0x00200000 /* Storage Key fault */
#घोषणा   DSISR_BAD_EXT_CTRL	0x00100000 /* Obsolete: External ctrl error */
#घोषणा   DSISR_UNSUPP_MMU	0x00080000 /* P9: Unsupported MMU config */
#घोषणा   DSISR_SET_RC		0x00040000 /* P9: Failed setting of R/C bits */
#घोषणा   DSISR_PRTABLE_FAULT   0x00020000 /* P9: Fault on process table */
#घोषणा   DSISR_ICSWX_NO_CT     0x00004000 /* P7: icswx unavailable cp type */
#घोषणा   DSISR_BAD_COPYPASTE   0x00000008 /* P9: Copy/Paste on wrong memtype */
#घोषणा   DSISR_BAD_AMO		0x00000004 /* P9: Incorrect AMO opcode */
#घोषणा   DSISR_BAD_CI_LDST	0x00000002 /* P8: Bad HV CI load/store */

/*
 * DSISR_NOEXEC_OR_G करोesn't actually exist. This bit is always
 * 0 on DSIs. However, on ISIs, the corresponding bit in SRR1
 * indicates an attempt at executing from a no-execute PTE
 * or segment or from a guarded page.
 *
 * We add a definition here क्रम completeness as we alias
 * DSISR and SRR1 in करो_page_fault.
 */

/*
 * DSISR bits that are treated as a fault. Any bit set
 * here will skip hash_page, and cause करो_page_fault to
 * trigger a SIGBUS or संक_अंश:
 */
#घोषणा   DSISR_BAD_FAULT_32S	(DSISR_BAD_सूचीECT_ST	| \
				 DSISR_BADACCESS	| \
				 DSISR_BAD_EXT_CTRL)
#घोषणा	  DSISR_BAD_FAULT_64S	(DSISR_BAD_FAULT_32S	| \
				 DSISR_ATTR_CONFLICT	| \
				 DSISR_UNSUPP_MMU	| \
				 DSISR_PRTABLE_FAULT	| \
				 DSISR_ICSWX_NO_CT	| \
				 DSISR_BAD_COPYPASTE	| \
				 DSISR_BAD_AMO		| \
				 DSISR_BAD_CI_LDST)
/*
 * These bits are equivalent in SRR1 and DSISR क्रम 0x400
 * inकाष्ठाion access पूर्णांकerrupts on Book3S
 */
#घोषणा   DSISR_SRR1_MATCH_32S	(DSISR_NOHPTE		| \
				 DSISR_NOEXEC_OR_G	| \
				 DSISR_PROTFAULT)
#घोषणा   DSISR_SRR1_MATCH_64S	(DSISR_SRR1_MATCH_32S	| \
				 DSISR_KEYFAULT		| \
				 DSISR_UNSUPP_MMU	| \
				 DSISR_SET_RC		| \
				 DSISR_PRTABLE_FAULT)

#घोषणा SPRN_TBRL	0x10C	/* Time Base Read Lower Register (user, R/O) */
#घोषणा SPRN_TBRU	0x10D	/* Time Base Read Upper Register (user, R/O) */
#घोषणा SPRN_CIR	0x11B	/* Chip Inक्रमmation Register (hyper, R/0) */
#घोषणा SPRN_TBWL	0x11C	/* Time Base Lower Register (super, R/W) */
#घोषणा SPRN_TBWU	0x11D	/* Time Base Upper Register (super, R/W) */
#घोषणा SPRN_TBU40	0x11E	/* Timebase upper 40 bits (hyper, R/W) */
#घोषणा SPRN_SPURR	0x134	/* Scaled PURR */
#घोषणा SPRN_HSPRG0	0x130	/* Hypervisor Scratch 0 */
#घोषणा SPRN_HSPRG1	0x131	/* Hypervisor Scratch 1 */
#घोषणा SPRN_HDSISR     0x132
#घोषणा SPRN_HDAR       0x133
#घोषणा SPRN_HDEC	0x136	/* Hypervisor Decrementer */
#घोषणा SPRN_HIOR	0x137	/* 970 Hypervisor पूर्णांकerrupt offset */
#घोषणा SPRN_RMOR	0x138	/* Real mode offset रेजिस्टर */
#घोषणा SPRN_HRMOR	0x139	/* Real mode offset रेजिस्टर */
#घोषणा SPRN_HSRR0	0x13A	/* Hypervisor Save/Restore 0 */
#घोषणा SPRN_HSRR1	0x13B	/* Hypervisor Save/Restore 1 */
#घोषणा SPRN_ASDR	0x330	/* Access segment descriptor रेजिस्टर */
#घोषणा SPRN_IC		0x350	/* Virtual Inकाष्ठाion Count */
#घोषणा SPRN_VTB	0x351	/* Virtual Time Base */
#घोषणा SPRN_LDBAR	0x352	/* LD Base Address Register */
#घोषणा SPRN_PMICR	0x354   /* Power Management Idle Control Reg */
#घोषणा SPRN_PMSR	0x355   /* Power Management Status Reg */
#घोषणा SPRN_PMMAR	0x356	/* Power Management Memory Activity Register */
#घोषणा SPRN_PSSCR	0x357	/* Processor Stop Status and Control Register (ISA 3.0) */
#घोषणा SPRN_PSSCR_PR	0x337	/* PSSCR ISA 3.0, privileged mode access */
#घोषणा SPRN_PMCR	0x374	/* Power Management Control Register */
#घोषणा SPRN_RWMR	0x375	/* Region-Weighting Mode Register */

/* HFSCR and FSCR bit numbers are the same */
#घोषणा FSCR_PREFIX_LG	13	/* Enable Prefix Inकाष्ठाions */
#घोषणा FSCR_SCV_LG	12	/* Enable System Call Vectored */
#घोषणा FSCR_MSGP_LG	10	/* Enable MSGP */
#घोषणा FSCR_TAR_LG	8	/* Enable Target Address Register */
#घोषणा FSCR_EBB_LG	7	/* Enable Event Based Branching */
#घोषणा FSCR_TM_LG	5	/* Enable Transactional Memory */
#घोषणा FSCR_BHRB_LG	4	/* Enable Branch History Rolling Buffer*/
#घोषणा FSCR_PM_LG	3	/* Enable prob/priv access to PMU SPRs */
#घोषणा FSCR_DSCR_LG	2	/* Enable Data Stream Control Register */
#घोषणा FSCR_VECVSX_LG	1	/* Enable VMX/VSX  */
#घोषणा FSCR_FP_LG	0	/* Enable Floating Poपूर्णांक */
#घोषणा SPRN_FSCR	0x099	/* Facility Status & Control Register */
#घोषणा   FSCR_PREFIX	__MASK(FSCR_PREFIX_LG)
#घोषणा   FSCR_SCV	__MASK(FSCR_SCV_LG)
#घोषणा   FSCR_TAR	__MASK(FSCR_TAR_LG)
#घोषणा   FSCR_EBB	__MASK(FSCR_EBB_LG)
#घोषणा   FSCR_DSCR	__MASK(FSCR_DSCR_LG)
#घोषणा SPRN_HFSCR	0xbe	/* HV=1 Facility Status & Control Register */
#घोषणा   HFSCR_PREFIX	__MASK(FSCR_PREFIX_LG)
#घोषणा   HFSCR_MSGP	__MASK(FSCR_MSGP_LG)
#घोषणा   HFSCR_TAR	__MASK(FSCR_TAR_LG)
#घोषणा   HFSCR_EBB	__MASK(FSCR_EBB_LG)
#घोषणा   HFSCR_TM	__MASK(FSCR_TM_LG)
#घोषणा   HFSCR_PM	__MASK(FSCR_PM_LG)
#घोषणा   HFSCR_BHRB	__MASK(FSCR_BHRB_LG)
#घोषणा   HFSCR_DSCR	__MASK(FSCR_DSCR_LG)
#घोषणा   HFSCR_VECVSX	__MASK(FSCR_VECVSX_LG)
#घोषणा   HFSCR_FP	__MASK(FSCR_FP_LG)
#घोषणा   HFSCR_INTR_CAUSE (ASM_CONST(0xFF) << 56)	/* पूर्णांकerrupt cause */
#घोषणा SPRN_TAR	0x32f	/* Target Address Register */
#घोषणा SPRN_LPCR	0x13E	/* LPAR Control Register */
#घोषणा   LPCR_VPM0		ASM_CONST(0x8000000000000000)
#घोषणा   LPCR_VPM1		ASM_CONST(0x4000000000000000)
#घोषणा   LPCR_ISL		ASM_CONST(0x2000000000000000)
#घोषणा   LPCR_VC_SH		61
#घोषणा   LPCR_DPFD_SH		52
#घोषणा   LPCR_DPFD		(ASM_CONST(7) << LPCR_DPFD_SH)
#घोषणा   LPCR_VRMASD_SH	47
#घोषणा   LPCR_VRMASD		(ASM_CONST(0x1f) << LPCR_VRMASD_SH)
#घोषणा   LPCR_VRMA_L		ASM_CONST(0x0008000000000000)
#घोषणा   LPCR_VRMA_LP0		ASM_CONST(0x0001000000000000)
#घोषणा   LPCR_VRMA_LP1		ASM_CONST(0x0000800000000000)
#घोषणा   LPCR_RMLS		0x1C000000	/* Implementation dependent RMO limit sel */
#घोषणा   LPCR_RMLS_SH		26
#घोषणा   LPCR_HAIL		ASM_CONST(0x0000000004000000)   /* HV AIL (ISAv3.1) */
#घोषणा   LPCR_ILE		ASM_CONST(0x0000000002000000)   /* !HV irqs set MSR:LE */
#घोषणा   LPCR_AIL		ASM_CONST(0x0000000001800000)	/* Alternate पूर्णांकerrupt location */
#घोषणा   LPCR_AIL_0		ASM_CONST(0x0000000000000000)	/* MMU off exception offset 0x0 */
#घोषणा   LPCR_AIL_3		ASM_CONST(0x0000000001800000)   /* MMU on exception offset 0xc00...4xxx */
#घोषणा   LPCR_ONL		ASM_CONST(0x0000000000040000)	/* online - PURR/SPURR count */
#घोषणा   LPCR_LD		ASM_CONST(0x0000000000020000)	/* large decremeter */
#घोषणा   LPCR_PECE		ASM_CONST(0x000000000001f000)	/* घातersave निकास cause enable */
#घोषणा     LPCR_PECEDP	ASM_CONST(0x0000000000010000)	/* directed priv dbells cause निकास */
#घोषणा     LPCR_PECEDH	ASM_CONST(0x0000000000008000)	/* directed hyp dbells cause निकास */
#घोषणा     LPCR_PECE0		ASM_CONST(0x0000000000004000)	/* ext. exceptions can cause निकास */
#घोषणा     LPCR_PECE1		ASM_CONST(0x0000000000002000)	/* decrementer can cause निकास */
#घोषणा     LPCR_PECE2		ASM_CONST(0x0000000000001000)	/* machine check etc can cause निकास */
#घोषणा     LPCR_PECE_HVEE	ASM_CONST(0x0000400000000000)	/* P9 Wakeup on HV पूर्णांकerrupts */
#घोषणा   LPCR_MER		ASM_CONST(0x0000000000000800)	/* Mediated External Exception */
#घोषणा   LPCR_MER_SH		11
#घोषणा	  LPCR_GTSE		ASM_CONST(0x0000000000000400)  	/* Guest Translation Shootकरोwn Enable */
#घोषणा   LPCR_TC		ASM_CONST(0x0000000000000200)	/* Translation control */
#घोषणा   LPCR_HEIC		ASM_CONST(0x0000000000000010)   /* Hypervisor External Interrupt Control */
#घोषणा   LPCR_LPES		0x0000000c
#घोषणा   LPCR_LPES0		ASM_CONST(0x0000000000000008)      /* LPAR Env selector 0 */
#घोषणा   LPCR_LPES1		ASM_CONST(0x0000000000000004)      /* LPAR Env selector 1 */
#घोषणा   LPCR_LPES_SH		2
#घोषणा   LPCR_RMI		ASM_CONST(0x0000000000000002)      /* real mode is cache inhibit */
#घोषणा   LPCR_HVICE		ASM_CONST(0x0000000000000002)      /* P9: HV पूर्णांकerrupt enable */
#घोषणा   LPCR_HDICE		ASM_CONST(0x0000000000000001)      /* Hyp Decr enable (HV,PR,EE) */
#घोषणा   LPCR_UPRT		ASM_CONST(0x0000000000400000)      /* Use Process Table (ISA 3) */
#घोषणा   LPCR_HR		ASM_CONST(0x0000000000100000)
#अगर_अघोषित SPRN_LPID
#घोषणा SPRN_LPID	0x13F	/* Logical Partition Identअगरier */
#पूर्ण_अगर
#घोषणा   LPID_RSVD_POWER7	0x3ff	/* Reserved LPID क्रम partn चयनing */
#घोषणा   LPID_RSVD		0xfff	/* Reserved LPID क्रम partn चयनing */
#घोषणा	SPRN_HMER	0x150	/* Hypervisor मुख्यtenance exception reg */
#घोषणा   HMER_DEBUG_TRIG	(1ul << (63 - 17)) /* Debug trigger */
#घोषणा	SPRN_HMEER	0x151	/* Hyp मुख्यtenance exception enable reg */
#घोषणा SPRN_PCR	0x152	/* Processor compatibility रेजिस्टर */
#घोषणा   PCR_VEC_DIS	(__MASK(63-0))	/* Vec. disable (bit NA since POWER8) */
#घोषणा   PCR_VSX_DIS	(__MASK(63-1))	/* VSX disable (bit NA since POWER8) */
#घोषणा   PCR_TM_DIS	(__MASK(63-2))	/* Trans. memory disable (POWER8) */
#घोषणा   PCR_MMA_DIS	(__MASK(63-3)) /* Matrix-Multiply Accelerator */
#घोषणा   PCR_HIGH_BITS	(PCR_MMA_DIS | PCR_VEC_DIS | PCR_VSX_DIS | PCR_TM_DIS)
/*
 * These bits are used in the function kvmppc_set_arch_compat() to specअगरy and
 * determine both the compatibility level which we want to emulate and the
 * compatibility level which the host is capable of emulating.
 */
#घोषणा   PCR_ARCH_300	0x10		/* Architecture 3.00 */
#घोषणा   PCR_ARCH_207	0x8		/* Architecture 2.07 */
#घोषणा   PCR_ARCH_206	0x4		/* Architecture 2.06 */
#घोषणा   PCR_ARCH_205	0x2		/* Architecture 2.05 */
#घोषणा   PCR_LOW_BITS	(PCR_ARCH_207 | PCR_ARCH_206 | PCR_ARCH_205 | PCR_ARCH_300)
#घोषणा   PCR_MASK	~(PCR_HIGH_BITS | PCR_LOW_BITS)	/* PCR Reserved Bits */
#घोषणा	SPRN_HEIR	0x153	/* Hypervisor Emulated Inकाष्ठाion Register */
#घोषणा SPRN_TLBINDEXR	0x154	/* P7 TLB control रेजिस्टर */
#घोषणा SPRN_TLBVPNR	0x155	/* P7 TLB control रेजिस्टर */
#घोषणा SPRN_TLBRPNR	0x156	/* P7 TLB control रेजिस्टर */
#घोषणा SPRN_TLBLPIDR	0x157	/* P7 TLB control रेजिस्टर */
#घोषणा SPRN_DBAT0L	0x219	/* Data BAT 0 Lower Register */
#घोषणा SPRN_DBAT0U	0x218	/* Data BAT 0 Upper Register */
#घोषणा SPRN_DBAT1L	0x21B	/* Data BAT 1 Lower Register */
#घोषणा SPRN_DBAT1U	0x21A	/* Data BAT 1 Upper Register */
#घोषणा SPRN_DBAT2L	0x21D	/* Data BAT 2 Lower Register */
#घोषणा SPRN_DBAT2U	0x21C	/* Data BAT 2 Upper Register */
#घोषणा SPRN_DBAT3L	0x21F	/* Data BAT 3 Lower Register */
#घोषणा SPRN_DBAT3U	0x21E	/* Data BAT 3 Upper Register */
#घोषणा SPRN_DBAT4L	0x239	/* Data BAT 4 Lower Register */
#घोषणा SPRN_DBAT4U	0x238	/* Data BAT 4 Upper Register */
#घोषणा SPRN_DBAT5L	0x23B	/* Data BAT 5 Lower Register */
#घोषणा SPRN_DBAT5U	0x23A	/* Data BAT 5 Upper Register */
#घोषणा SPRN_DBAT6L	0x23D	/* Data BAT 6 Lower Register */
#घोषणा SPRN_DBAT6U	0x23C	/* Data BAT 6 Upper Register */
#घोषणा SPRN_DBAT7L	0x23F	/* Data BAT 7 Lower Register */
#घोषणा SPRN_DBAT7U	0x23E	/* Data BAT 7 Upper Register */
#घोषणा SPRN_PPR	0x380	/* SMT Thपढ़ो status Register */
#घोषणा SPRN_TSCR	0x399	/* Thपढ़ो Switch Control Register */

#घोषणा SPRN_DEC	0x016		/* Decrement Register */
#घोषणा SPRN_PIT	0x3DB		/* Programmable Interval Timer (40x/BOOKE) */

#घोषणा SPRN_DER	0x095		/* Debug Enable Register */
#घोषणा DER_RSTE	0x40000000	/* Reset Interrupt */
#घोषणा DER_CHSTPE	0x20000000	/* Check Stop */
#घोषणा DER_MCIE	0x10000000	/* Machine Check Interrupt */
#घोषणा DER_EXTIE	0x02000000	/* External Interrupt */
#घोषणा DER_ALIE	0x01000000	/* Alignment Interrupt */
#घोषणा DER_PRIE	0x00800000	/* Program Interrupt */
#घोषणा DER_FPUVIE	0x00400000	/* FP Unavailable Interrupt */
#घोषणा DER_DECIE	0x00200000	/* Decrementer Interrupt */
#घोषणा DER_SYSIE	0x00040000	/* System Call Interrupt */
#घोषणा DER_TRE		0x00020000	/* Trace Interrupt */
#घोषणा DER_SEIE	0x00004000	/* FP SW Emulation Interrupt */
#घोषणा DER_ITLBMSE	0x00002000	/* Imp. Spec. Inकाष्ठाion TLB Miss */
#घोषणा DER_ITLBERE	0x00001000	/* Imp. Spec. Inकाष्ठाion TLB Error */
#घोषणा DER_DTLBMSE	0x00000800	/* Imp. Spec. Data TLB Miss */
#घोषणा DER_DTLBERE	0x00000400	/* Imp. Spec. Data TLB Error */
#घोषणा DER_LBRKE	0x00000008	/* Load/Store Breakpoपूर्णांक Interrupt */
#घोषणा DER_IBRKE	0x00000004	/* Inकाष्ठाion Breakpoपूर्णांक Interrupt */
#घोषणा DER_EBRKE	0x00000002	/* External Breakpoपूर्णांक Interrupt */
#घोषणा DER_DPIE	0x00000001	/* Dev. Port Nonmaskable Request */
#घोषणा SPRN_DMISS	0x3D0		/* Data TLB Miss Register */
#घोषणा SPRN_DHDES	0x0B1		/* Directed Hyp. Doorbell Exc. State */
#घोषणा SPRN_DPDES	0x0B0		/* Directed Priv. Doorbell Exc. State */
#घोषणा SPRN_EAR	0x11A		/* External Address Register */
#घोषणा SPRN_HASH1	0x3D2		/* Primary Hash Address Register */
#घोषणा SPRN_HASH2	0x3D3		/* Secondary Hash Address Register */
#घोषणा SPRN_HID0	0x3F0		/* Hardware Implementation Register 0 */
#घोषणा HID0_HDICE_SH	(63 - 23)	/* 970 HDEC पूर्णांकerrupt enable */
#घोषणा HID0_EMCP	(1<<31)		/* Enable Machine Check pin */
#घोषणा HID0_EBA	(1<<29)		/* Enable Bus Address Parity */
#घोषणा HID0_EBD	(1<<28)		/* Enable Bus Data Parity */
#घोषणा HID0_SBCLK	(1<<27)
#घोषणा HID0_EICE	(1<<26)
#घोषणा HID0_TBEN	(1<<26)		/* Timebase enable - 745x */
#घोषणा HID0_ECLK	(1<<25)
#घोषणा HID0_PAR	(1<<24)
#घोषणा HID0_STEN	(1<<24)		/* Software table search enable - 745x */
#घोषणा HID0_HIGH_BAT	(1<<23)		/* Enable high BATs - 7455 */
#घोषणा HID0_DOZE	(1<<23)
#घोषणा HID0_NAP	(1<<22)
#घोषणा HID0_SLEEP	(1<<21)
#घोषणा HID0_DPM	(1<<20)
#घोषणा HID0_BHTCLR	(1<<18)		/* Clear branch history table - 7450 */
#घोषणा HID0_XAEN	(1<<17)		/* Extended addressing enable - 7450 */
#घोषणा HID0_NHR	(1<<16)		/* Not hard reset (software bit-7450)*/
#घोषणा HID0_ICE	(1<<15)		/* Inकाष्ठाion Cache Enable */
#घोषणा HID0_DCE	(1<<14)		/* Data Cache Enable */
#घोषणा HID0_ILOCK	(1<<13)		/* Inकाष्ठाion Cache Lock */
#घोषणा HID0_DLOCK	(1<<12)		/* Data Cache Lock */
#घोषणा HID0_ICFI	(1<<11)		/* Instr. Cache Flash Invalidate */
#घोषणा HID0_DCI	(1<<10)		/* Data Cache Invalidate */
#घोषणा HID0_SPD	(1<<9)		/* Speculative disable */
#घोषणा HID0_DAPUEN	(1<<8)		/* Debug APU enable */
#घोषणा HID0_SGE	(1<<7)		/* Store Gathering Enable */
#घोषणा HID0_SIED	(1<<7)		/* Serial Instr. Execution [Disable] */
#घोषणा HID0_DCFA	(1<<6)		/* Data Cache Flush Assist */
#घोषणा HID0_LRSTK	(1<<4)		/* Link रेजिस्टर stack - 745x */
#घोषणा HID0_BTIC	(1<<5)		/* Branch Target Instr Cache Enable */
#घोषणा HID0_ABE	(1<<3)		/* Address Broadcast Enable */
#घोषणा HID0_FOLD	(1<<3)		/* Branch Folding enable - 745x */
#घोषणा HID0_BHTE	(1<<2)		/* Branch History Table Enable */
#घोषणा HID0_BTCD	(1<<1)		/* Branch target cache disable */
#घोषणा HID0_NOPDST	(1<<1)		/* No-op dst, dstt, etc. instr. */
#घोषणा HID0_NOPTI	(1<<0)		/* No-op dcbt and dcbst instr. */
/* POWER8 HID0 bits */
#घोषणा HID0_POWER8_4LPARMODE	__MASK(61)
#घोषणा HID0_POWER8_2LPARMODE	__MASK(57)
#घोषणा HID0_POWER8_1TO2LPAR	__MASK(52)
#घोषणा HID0_POWER8_1TO4LPAR	__MASK(51)
#घोषणा HID0_POWER8_DYNLPARDIS	__MASK(48)

/* POWER9 HID0 bits */
#घोषणा HID0_POWER9_RADIX	__MASK(63 - 8)

#घोषणा SPRN_HID1	0x3F1		/* Hardware Implementation Register 1 */
#अगर_घोषित CONFIG_PPC_BOOK3S_32
#घोषणा HID1_EMCP	(1<<31)		/* 7450 Machine Check Pin Enable */
#घोषणा HID1_DFS	(1<<22)		/* 7447A Dynamic Frequency Scaling */
#घोषणा HID1_PC0	(1<<16)		/* 7450 PLL_CFG[0] */
#घोषणा HID1_PC1	(1<<15)		/* 7450 PLL_CFG[1] */
#घोषणा HID1_PC2	(1<<14)		/* 7450 PLL_CFG[2] */
#घोषणा HID1_PC3	(1<<13)		/* 7450 PLL_CFG[3] */
#घोषणा HID1_SYNCBE	(1<<11)		/* 7450 ABE क्रम sync, eieio */
#घोषणा HID1_ABE	(1<<10)		/* 7450 Address Broadcast Enable */
#घोषणा HID1_PS		(1<<16)		/* 750FX PLL selection */
#पूर्ण_अगर
#घोषणा SPRN_HID2	0x3F8		/* Hardware Implementation Register 2 */
#घोषणा SPRN_HID2_GEKKO	0x398		/* Gekko HID2 Register */
#घोषणा SPRN_IABR	0x3F2	/* Inकाष्ठाion Address Breakpoपूर्णांक Register */
#घोषणा SPRN_IABR2	0x3FA		/* 83xx */
#घोषणा SPRN_IBCR	0x135		/* 83xx Insn Breakpoपूर्णांक Control Reg */
#घोषणा SPRN_IAMR	0x03D		/* Instr. Authority Mask Reg */
#घोषणा SPRN_HID4	0x3F4		/* 970 HID4 */
#घोषणा  HID4_LPES0	 (1ul << (63-0)) /* LPAR env. sel. bit 0 */
#घोषणा	 HID4_RMLS2_SH	 (63 - 2)	/* Real mode limit bottom 2 bits */
#घोषणा	 HID4_LPID5_SH	 (63 - 6)	/* partition ID bottom 4 bits */
#घोषणा	 HID4_RMOR_SH	 (63 - 22)	/* real mode offset (16 bits) */
#घोषणा  HID4_RMOR	 (0xFFFFul << HID4_RMOR_SH)
#घोषणा  HID4_LPES1	 (1 << (63-57))	/* LPAR env. sel. bit 1 */
#घोषणा  HID4_RMLS0_SH	 (63 - 58)	/* Real mode limit top bit */
#घोषणा	 HID4_LPID1_SH	 0		/* partition ID top 2 bits */
#घोषणा SPRN_HID4_GEKKO	0x3F3		/* Gekko HID4 */
#घोषणा SPRN_HID5	0x3F6		/* 970 HID5 */
#घोषणा SPRN_HID6	0x3F9	/* BE HID 6 */
#घोषणा   HID6_LB	(0x0F<<12) /* Concurrent Large Page Modes */
#घोषणा   HID6_DLP	(1<<20)	/* Disable all large page modes (4K only) */
#घोषणा SPRN_TSC_CELL	0x399	/* Thपढ़ो चयन control on Cell */
#घोषणा   TSC_CELL_DEC_ENABLE_0	0x400000 /* Decrementer Interrupt */
#घोषणा   TSC_CELL_DEC_ENABLE_1	0x200000 /* Decrementer Interrupt */
#घोषणा   TSC_CELL_EE_ENABLE	0x100000 /* External Interrupt */
#घोषणा   TSC_CELL_EE_BOOST	0x080000 /* External Interrupt Boost */
#घोषणा SPRN_TSC 	0x3FD	/* Thपढ़ो चयन control on others */
#घोषणा SPRN_TST 	0x3FC	/* Thपढ़ो चयन समयout on others */
#अगर !defined(SPRN_IAC1) && !defined(SPRN_IAC2)
#घोषणा SPRN_IAC1	0x3F4		/* Inकाष्ठाion Address Compare 1 */
#घोषणा SPRN_IAC2	0x3F5		/* Inकाष्ठाion Address Compare 2 */
#पूर्ण_अगर
#घोषणा SPRN_IBAT0L	0x211		/* Inकाष्ठाion BAT 0 Lower Register */
#घोषणा SPRN_IBAT0U	0x210		/* Inकाष्ठाion BAT 0 Upper Register */
#घोषणा SPRN_IBAT1L	0x213		/* Inकाष्ठाion BAT 1 Lower Register */
#घोषणा SPRN_IBAT1U	0x212		/* Inकाष्ठाion BAT 1 Upper Register */
#घोषणा SPRN_IBAT2L	0x215		/* Inकाष्ठाion BAT 2 Lower Register */
#घोषणा SPRN_IBAT2U	0x214		/* Inकाष्ठाion BAT 2 Upper Register */
#घोषणा SPRN_IBAT3L	0x217		/* Inकाष्ठाion BAT 3 Lower Register */
#घोषणा SPRN_IBAT3U	0x216		/* Inकाष्ठाion BAT 3 Upper Register */
#घोषणा SPRN_IBAT4L	0x231		/* Inकाष्ठाion BAT 4 Lower Register */
#घोषणा SPRN_IBAT4U	0x230		/* Inकाष्ठाion BAT 4 Upper Register */
#घोषणा SPRN_IBAT5L	0x233		/* Inकाष्ठाion BAT 5 Lower Register */
#घोषणा SPRN_IBAT5U	0x232		/* Inकाष्ठाion BAT 5 Upper Register */
#घोषणा SPRN_IBAT6L	0x235		/* Inकाष्ठाion BAT 6 Lower Register */
#घोषणा SPRN_IBAT6U	0x234		/* Inकाष्ठाion BAT 6 Upper Register */
#घोषणा SPRN_IBAT7L	0x237		/* Inकाष्ठाion BAT 7 Lower Register */
#घोषणा SPRN_IBAT7U	0x236		/* Inकाष्ठाion BAT 7 Upper Register */
#घोषणा SPRN_ICMP	0x3D5		/* Inकाष्ठाion TLB Compare Register */
#घोषणा SPRN_ICTC	0x3FB	/* Inकाष्ठाion Cache Throttling Control Reg */
#अगर_अघोषित SPRN_ICTRL
#घोषणा SPRN_ICTRL	0x3F3	/* 1011 7450 icache and पूर्णांकerrupt ctrl */
#पूर्ण_अगर
#घोषणा ICTRL_EICE	0x08000000	/* enable icache parity errs */
#घोषणा ICTRL_EDC	0x04000000	/* enable dcache parity errs */
#घोषणा ICTRL_EICP	0x00000100	/* enable icache par. check */
#घोषणा SPRN_IMISS	0x3D4		/* Inकाष्ठाion TLB Miss Register */
#घोषणा SPRN_IMMR	0x27E		/* Internal Memory Map Register */
#घोषणा SPRN_L2CR	0x3F9		/* Level 2 Cache Control Register */
#घोषणा SPRN_L2CR2	0x3f8
#घोषणा L2CR_L2E		0x80000000	/* L2 enable */
#घोषणा L2CR_L2PE		0x40000000	/* L2 parity enable */
#घोषणा L2CR_L2SIZ_MASK		0x30000000	/* L2 size mask */
#घोषणा L2CR_L2SIZ_256KB	0x10000000	/* L2 size 256KB */
#घोषणा L2CR_L2SIZ_512KB	0x20000000	/* L2 size 512KB */
#घोषणा L2CR_L2SIZ_1MB		0x30000000	/* L2 size 1MB */
#घोषणा L2CR_L2CLK_MASK		0x0e000000	/* L2 घड़ी mask */
#घोषणा L2CR_L2CLK_DISABLED	0x00000000	/* L2 घड़ी disabled */
#घोषणा L2CR_L2CLK_DIV1		0x02000000	/* L2 घड़ी / 1 */
#घोषणा L2CR_L2CLK_DIV1_5	0x04000000	/* L2 घड़ी / 1.5 */
#घोषणा L2CR_L2CLK_DIV2		0x08000000	/* L2 घड़ी / 2 */
#घोषणा L2CR_L2CLK_DIV2_5	0x0a000000	/* L2 घड़ी / 2.5 */
#घोषणा L2CR_L2CLK_DIV3		0x0c000000	/* L2 घड़ी / 3 */
#घोषणा L2CR_L2RAM_MASK		0x01800000	/* L2 RAM type mask */
#घोषणा L2CR_L2RAM_FLOW		0x00000000	/* L2 RAM flow through */
#घोषणा L2CR_L2RAM_PIPE		0x01000000	/* L2 RAM pipelined */
#घोषणा L2CR_L2RAM_PIPE_LW	0x01800000	/* L2 RAM pipelined latewr */
#घोषणा L2CR_L2DO		0x00400000	/* L2 data only */
#घोषणा L2CR_L2I		0x00200000	/* L2 global invalidate */
#घोषणा L2CR_L2CTL		0x00100000	/* L2 RAM control */
#घोषणा L2CR_L2WT		0x00080000	/* L2 ग_लिखो-through */
#घोषणा L2CR_L2TS		0x00040000	/* L2 test support */
#घोषणा L2CR_L2OH_MASK		0x00030000	/* L2 output hold mask */
#घोषणा L2CR_L2OH_0_5		0x00000000	/* L2 output hold 0.5 ns */
#घोषणा L2CR_L2OH_1_0		0x00010000	/* L2 output hold 1.0 ns */
#घोषणा L2CR_L2SL		0x00008000	/* L2 DLL slow */
#घोषणा L2CR_L2DF		0x00004000	/* L2 dअगरferential घड़ी */
#घोषणा L2CR_L2BYP		0x00002000	/* L2 DLL bypass */
#घोषणा L2CR_L2IP		0x00000001	/* L2 GI in progress */
#घोषणा L2CR_L2IO_745x		0x00100000	/* L2 instr. only (745x) */
#घोषणा L2CR_L2DO_745x		0x00010000	/* L2 data only (745x) */
#घोषणा L2CR_L2REP_745x		0x00001000	/* L2 repl. algorithm (745x) */
#घोषणा L2CR_L2HWF_745x		0x00000800	/* L2 hardware flush (745x) */
#घोषणा SPRN_L3CR		0x3FA	/* Level 3 Cache Control Register */
#घोषणा L3CR_L3E		0x80000000	/* L3 enable */
#घोषणा L3CR_L3PE		0x40000000	/* L3 data parity enable */
#घोषणा L3CR_L3APE		0x20000000	/* L3 addr parity enable */
#घोषणा L3CR_L3SIZ		0x10000000	/* L3 size */
#घोषणा L3CR_L3CLKEN		0x08000000	/* L3 घड़ी enable */
#घोषणा L3CR_L3RES		0x04000000	/* L3 special reserved bit */
#घोषणा L3CR_L3CLKDIV		0x03800000	/* L3 घड़ी भागisor */
#घोषणा L3CR_L3IO		0x00400000	/* L3 inकाष्ठाion only */
#घोषणा L3CR_L3SPO		0x00040000	/* L3 sample poपूर्णांक override */
#घोषणा L3CR_L3CKSP		0x00030000	/* L3 घड़ी sample poपूर्णांक */
#घोषणा L3CR_L3PSP		0x0000e000	/* L3 P-घड़ी sample poपूर्णांक */
#घोषणा L3CR_L3REP		0x00001000	/* L3 replacement algorithm */
#घोषणा L3CR_L3HWF		0x00000800	/* L3 hardware flush */
#घोषणा L3CR_L3I		0x00000400	/* L3 global invalidate */
#घोषणा L3CR_L3RT		0x00000300	/* L3 SRAM type */
#घोषणा L3CR_L3NIRCA		0x00000080	/* L3 non-पूर्णांकeger ratio घड़ी adj. */
#घोषणा L3CR_L3DO		0x00000040	/* L3 data only mode */
#घोषणा L3CR_PMEN		0x00000004	/* L3 निजी memory enable */
#घोषणा L3CR_PMSIZ		0x00000001	/* L3 निजी memory size */

#घोषणा SPRN_MSSCR0	0x3f6	/* Memory Subप्रणाली Control Register 0 */
#घोषणा SPRN_MSSSR0	0x3f7	/* Memory Subप्रणाली Status Register 1 */
#घोषणा SPRN_LDSTCR	0x3f8	/* Load/Store control रेजिस्टर */
#घोषणा SPRN_LDSTDB	0x3f4	/* */
#घोषणा SPRN_LR		0x008	/* Link Register */
#अगर_अघोषित SPRN_PIR
#घोषणा SPRN_PIR	0x3FF	/* Processor Identअगरication Register */
#पूर्ण_अगर
#घोषणा SPRN_TIR	0x1BE	/* Thपढ़ो Identअगरication Register */
#घोषणा SPRN_PTCR	0x1D0	/* Partition table control Register */
#घोषणा SPRN_PSPB	0x09F	/* Problem State Priority Boost reg */
#घोषणा SPRN_PTEHI	0x3D5	/* 981 7450 PTE HI word (S/W TLB load) */
#घोषणा SPRN_PTELO	0x3D6	/* 982 7450 PTE LO word (S/W TLB load) */
#घोषणा SPRN_PURR	0x135	/* Processor Utilization of Resources Reg */
#घोषणा SPRN_PVR	0x11F	/* Processor Version Register */
#घोषणा SPRN_RPA	0x3D6	/* Required Physical Address Register */
#घोषणा SPRN_SDA	0x3BF	/* Sampled Data Address Register */
#घोषणा SPRN_SDR1	0x019	/* MMU Hash Base Register */
#घोषणा SPRN_ASR	0x118   /* Address Space Register */
#घोषणा SPRN_SIA	0x3BB	/* Sampled Inकाष्ठाion Address Register */
#घोषणा SPRN_SPRG0	0x110	/* Special Purpose Register General 0 */
#घोषणा SPRN_SPRG1	0x111	/* Special Purpose Register General 1 */
#घोषणा SPRN_SPRG2	0x112	/* Special Purpose Register General 2 */
#घोषणा SPRN_SPRG3	0x113	/* Special Purpose Register General 3 */
#घोषणा SPRN_USPRG3	0x103	/* SPRG3 userspace पढ़ो */
#घोषणा SPRN_SPRG4	0x114	/* Special Purpose Register General 4 */
#घोषणा SPRN_USPRG4	0x104	/* SPRG4 userspace पढ़ो */
#घोषणा SPRN_SPRG5	0x115	/* Special Purpose Register General 5 */
#घोषणा SPRN_USPRG5	0x105	/* SPRG5 userspace पढ़ो */
#घोषणा SPRN_SPRG6	0x116	/* Special Purpose Register General 6 */
#घोषणा SPRN_USPRG6	0x106	/* SPRG6 userspace पढ़ो */
#घोषणा SPRN_SPRG7	0x117	/* Special Purpose Register General 7 */
#घोषणा SPRN_USPRG7	0x107	/* SPRG7 userspace पढ़ो */
#घोषणा SPRN_SRR0	0x01A	/* Save/Restore Register 0 */
#घोषणा SPRN_SRR1	0x01B	/* Save/Restore Register 1 */

#अगर_घोषित CONFIG_PPC_BOOK3S
/*
 * Bits loaded from MSR upon पूर्णांकerrupt.
 * PPC (64-bit) bits 33-36,42-47 are पूर्णांकerrupt dependent, the others are
 * loaded from MSR. The exception is that SRESET and MCE करो not always load
 * bit 62 (RI) from MSR. Don't use PPC_BITMASK क्रम this because 32-bit uses
 * it.
 */
#घोषणा   SRR1_MSR_BITS		(~0x783f0000UL)
#पूर्ण_अगर

#घोषणा   SRR1_ISI_NOPT		0x40000000 /* ISI: Not found in hash */
#घोषणा   SRR1_ISI_N_G_OR_CIP	0x10000000 /* ISI: Access is no-exec or G or CI क्रम a prefixed inकाष्ठाion */
#घोषणा   SRR1_ISI_PROT		0x08000000 /* ISI: Other protection fault */
#घोषणा   SRR1_WAKEMASK		0x00380000 /* reason क्रम wakeup */
#घोषणा   SRR1_WAKEMASK_P8	0x003c0000 /* reason क्रम wakeup on POWER8 and 9 */
#घोषणा   SRR1_WAKEMCE_RESVD	0x003c0000 /* Unused/reserved value used by MCE wakeup to indicate cause to idle wakeup handler */
#घोषणा   SRR1_WAKESYSERR	0x00300000 /* System error */
#घोषणा   SRR1_WAKEEE		0x00200000 /* External पूर्णांकerrupt */
#घोषणा   SRR1_WAKEHVI		0x00240000 /* Hypervisor Virtualization Interrupt (P9) */
#घोषणा   SRR1_WAKEMT		0x00280000 /* mtctrl */
#घोषणा	  SRR1_WAKEHMI		0x00280000 /* Hypervisor मुख्यtenance */
#घोषणा   SRR1_WAKEDEC		0x00180000 /* Decrementer पूर्णांकerrupt */
#घोषणा   SRR1_WAKEDBELL	0x00140000 /* Privileged करोorbell on P8 */
#घोषणा   SRR1_WAKETHERM	0x00100000 /* Thermal management पूर्णांकerrupt */
#घोषणा	  SRR1_WAKERESET	0x00100000 /* System reset */
#घोषणा   SRR1_WAKEHDBELL	0x000c0000 /* Hypervisor करोorbell on P8 */
#घोषणा	  SRR1_WAKESTATE	0x00030000 /* Powersave निकास mask [46:47] */
#घोषणा	  SRR1_WS_HVLOSS	0x00030000 /* HV resources not मुख्यtained */
#घोषणा	  SRR1_WS_GPRLOSS	0x00020000 /* GPRs not मुख्यtained */
#घोषणा	  SRR1_WS_NOLOSS	0x00010000 /* All resources मुख्यtained */
#घोषणा   SRR1_PROGTM		0x00200000 /* TM Bad Thing */
#घोषणा   SRR1_PROGFPE		0x00100000 /* Floating Poपूर्णांक Enabled */
#घोषणा   SRR1_PROGILL		0x00080000 /* Illegal inकाष्ठाion */
#घोषणा   SRR1_PROGPRIV		0x00040000 /* Privileged inकाष्ठाion */
#घोषणा   SRR1_PROGTRAP		0x00020000 /* Trap */
#घोषणा   SRR1_PROGADDR		0x00010000 /* SRR0 contains subsequent addr */

#घोषणा   SRR1_MCE_MCP		0x00080000 /* Machine check संकेत caused पूर्णांकerrupt */
#घोषणा   SRR1_BOUNDARY		0x10000000 /* Prefixed inकाष्ठाion crosses 64-byte boundary */
#घोषणा   SRR1_PREFIXED		0x20000000 /* Exception caused by prefixed inकाष्ठाion */

#घोषणा SPRN_HSRR0	0x13A	/* Save/Restore Register 0 */
#घोषणा SPRN_HSRR1	0x13B	/* Save/Restore Register 1 */
#घोषणा   HSRR1_DENORM		0x00100000 /* Denorm exception */
#घोषणा   HSRR1_HISI_WRITE	0x00010000 /* HISI bcs couldn't update mem */

#घोषणा SPRN_TBCTL	0x35f	/* PA6T Timebase control रेजिस्टर */
#घोषणा   TBCTL_FREEZE		0x0000000000000000ull /* Freeze all tbs */
#घोषणा   TBCTL_RESTART		0x0000000100000000ull /* Restart all tbs */
#घोषणा   TBCTL_UPDATE_UPPER	0x0000000200000000ull /* Set upper 32 bits */
#घोषणा   TBCTL_UPDATE_LOWER	0x0000000300000000ull /* Set lower 32 bits */

#अगर_अघोषित SPRN_SVR
#घोषणा SPRN_SVR	0x11E	/* System Version Register */
#पूर्ण_अगर
#घोषणा SPRN_THRM1	0x3FC		/* Thermal Management Register 1 */
/* these bits were defined in inverted endian sense originally, ugh, confusing */
#घोषणा THRM1_TIN	(1 << 31)
#घोषणा THRM1_TIV	(1 << 30)
#घोषणा THRM1_THRES(x)	((x&0x7f)<<23)
#घोषणा THRM3_SITV(x)	((x & 0x1fff) << 1)
#घोषणा THRM1_TID	(1<<2)
#घोषणा THRM1_TIE	(1<<1)
#घोषणा THRM1_V		(1<<0)
#घोषणा SPRN_THRM2	0x3FD		/* Thermal Management Register 2 */
#घोषणा SPRN_THRM3	0x3FE		/* Thermal Management Register 3 */
#घोषणा THRM3_E		(1<<0)
#घोषणा SPRN_TLBMISS	0x3D4		/* 980 7450 TLB Miss Register */
#घोषणा SPRN_UMMCR0	0x3A8	/* User Monitor Mode Control Register 0 */
#घोषणा SPRN_UMMCR1	0x3AC	/* User Monitor Mode Control Register 0 */
#घोषणा SPRN_UPMC1	0x3A9	/* User Perक्रमmance Counter Register 1 */
#घोषणा SPRN_UPMC2	0x3AA	/* User Perक्रमmance Counter Register 2 */
#घोषणा SPRN_UPMC3	0x3AD	/* User Perक्रमmance Counter Register 3 */
#घोषणा SPRN_UPMC4	0x3AE	/* User Perक्रमmance Counter Register 4 */
#घोषणा SPRN_USIA	0x3AB	/* User Sampled Inकाष्ठाion Address Register */
#घोषणा SPRN_VRSAVE	0x100	/* Vector Register Save Register */
#घोषणा SPRN_XER	0x001	/* Fixed Poपूर्णांक Exception Register */

#घोषणा SPRN_MMCR0_GEKKO 0x3B8 /* Gekko Monitor Mode Control Register 0 */
#घोषणा SPRN_MMCR1_GEKKO 0x3BC /* Gekko Monitor Mode Control Register 1 */
#घोषणा SPRN_PMC1_GEKKO  0x3B9 /* Gekko Perक्रमmance Monitor Control 1 */
#घोषणा SPRN_PMC2_GEKKO  0x3BA /* Gekko Perक्रमmance Monitor Control 2 */
#घोषणा SPRN_PMC3_GEKKO  0x3BD /* Gekko Perक्रमmance Monitor Control 3 */
#घोषणा SPRN_PMC4_GEKKO  0x3BE /* Gekko Perक्रमmance Monitor Control 4 */
#घोषणा SPRN_WPAR_GEKKO  0x399 /* Gekko Write Pipe Address Register */

#घोषणा SPRN_SCOMC	0x114	/* SCOM Access Control */
#घोषणा SPRN_SCOMD	0x115	/* SCOM Access DATA */

/* Perक्रमmance monitor SPRs */
#अगर_घोषित CONFIG_PPC64
#घोषणा SPRN_MMCR0	795
#घोषणा   MMCR0_FC	0x80000000UL /* मुक्तze counters */
#घोषणा   MMCR0_FCS	0x40000000UL /* मुक्तze in supervisor state */
#घोषणा   MMCR0_KERNEL_DISABLE MMCR0_FCS
#घोषणा   MMCR0_FCP	0x20000000UL /* मुक्तze in problem state */
#घोषणा   MMCR0_PROBLEM_DISABLE MMCR0_FCP
#घोषणा   MMCR0_FCM1	0x10000000UL /* मुक्तze counters जबतक MSR mark = 1 */
#घोषणा   MMCR0_FCM0	0x08000000UL /* मुक्तze counters जबतक MSR mark = 0 */
#घोषणा   MMCR0_PMXE	ASM_CONST(0x04000000) /* perf mon exception enable */
#घोषणा   MMCR0_FCECE	ASM_CONST(0x02000000) /* मुक्तze ctrs on enabled cond or event */
#घोषणा   MMCR0_TBEE	0x00400000UL /* समय base exception enable */
#घोषणा   MMCR0_BHRBA	0x00200000UL /* BHRB Access allowed in userspace */
#घोषणा   MMCR0_EBE	0x00100000UL /* Event based branch enable */
#घोषणा   MMCR0_PMCC	0x000c0000UL /* PMC control */
#घोषणा   MMCR0_PMCCEXT	ASM_CONST(0x00000200) /* PMCCEXT control */
#घोषणा   MMCR0_PMCC_U6	0x00080000UL /* PMC1-6 are R/W by user (PR) */
#घोषणा   MMCR0_PMC1CE	0x00008000UL /* PMC1 count enable*/
#घोषणा   MMCR0_PMCjCE	ASM_CONST(0x00004000) /* PMCj count enable*/
#घोषणा   MMCR0_TRIGGER	0x00002000UL /* TRIGGER enable */
#घोषणा   MMCR0_PMAO_SYNC ASM_CONST(0x00000800) /* PMU पूर्णांकr is synchronous */
#घोषणा   MMCR0_C56RUN	ASM_CONST(0x00000100) /* PMC5/6 count when RUN=0 */
/* perक्रमmance monitor alert has occurred, set to 0 after handling exception */
#घोषणा   MMCR0_PMAO	ASM_CONST(0x00000080)
#घोषणा   MMCR0_SHRFC	0x00000040UL /* SHRre मुक्तze conditions between thपढ़ोs */
#घोषणा   MMCR0_FC56	0x00000010UL /* मुक्तze counters 5 and 6 */
#घोषणा   MMCR0_FCTI	0x00000008UL /* मुक्तze counters in tags inactive mode */
#घोषणा   MMCR0_FCTA	0x00000004UL /* मुक्तze counters in tags active mode */
#घोषणा   MMCR0_FCWAIT	0x00000002UL /* मुक्तze counter in WAIT state */
#घोषणा   MMCR0_FCHV	0x00000001UL /* मुक्तze conditions in hypervisor mode */
#घोषणा SPRN_MMCR1	798
#घोषणा SPRN_MMCR2	785
#घोषणा SPRN_MMCR3	754
#घोषणा SPRN_UMMCR2	769
#घोषणा SPRN_UMMCR3	738
#घोषणा SPRN_MMCRA	0x312
#घोषणा   MMCRA_SDSYNC	0x80000000UL /* SDAR synced with SIAR */
#घोषणा   MMCRA_SDAR_DCACHE_MISS 0x40000000UL
#घोषणा   MMCRA_SDAR_ERAT_MISS   0x20000000UL
#घोषणा   MMCRA_SIHV	0x10000000UL /* state of MSR HV when SIAR set */
#घोषणा   MMCRA_SIPR	0x08000000UL /* state of MSR PR when SIAR set */
#घोषणा   MMCRA_SLOT	0x07000000UL /* SLOT bits (37-39) */
#घोषणा   MMCRA_SLOT_SHIFT	24
#घोषणा   MMCRA_SAMPLE_ENABLE 0x00000001UL /* enable sampling */
#घोषणा   MMCRA_BHRB_DISABLE  _UL(0x2000000000) // BHRB disable bit क्रम ISA v3.1
#घोषणा   POWER6_MMCRA_SDSYNC 0x0000080000000000ULL	/* SDAR/SIAR synced */
#घोषणा   POWER6_MMCRA_SIHV   0x0000040000000000ULL
#घोषणा   POWER6_MMCRA_SIPR   0x0000020000000000ULL
#घोषणा   POWER6_MMCRA_THRM	0x00000020UL
#घोषणा   POWER6_MMCRA_OTHER	0x0000000EUL

#घोषणा   POWER7P_MMCRA_SIAR_VALID 0x10000000	/* P7+ SIAR contents valid */
#घोषणा   POWER7P_MMCRA_SDAR_VALID 0x08000000	/* P7+ SDAR contents valid */

#घोषणा SPRN_MMCRH	316	/* Hypervisor monitor mode control रेजिस्टर */
#घोषणा SPRN_MMCRS	894	/* Supervisor monitor mode control रेजिस्टर */
#घोषणा SPRN_MMCRC	851	/* Core monitor mode control रेजिस्टर */
#घोषणा SPRN_EBBHR	804	/* Event based branch handler रेजिस्टर */
#घोषणा SPRN_EBBRR	805	/* Event based branch वापस रेजिस्टर */
#घोषणा SPRN_BESCR	806	/* Branch event status and control रेजिस्टर */
#घोषणा   BESCR_GE	0x8000000000000000ULL /* Global Enable */
#घोषणा SPRN_WORT	895	/* Workload optimization रेजिस्टर - thपढ़ो */
#घोषणा SPRN_WORC	863	/* Workload optimization रेजिस्टर - core */

#घोषणा SPRN_PMC1	787
#घोषणा SPRN_PMC2	788
#घोषणा SPRN_PMC3	789
#घोषणा SPRN_PMC4	790
#घोषणा SPRN_PMC5	791
#घोषणा SPRN_PMC6	792
#घोषणा SPRN_PMC7	793
#घोषणा SPRN_PMC8	794
#घोषणा SPRN_SIER	784
#घोषणा   SIER_SIPR		0x2000000	/* Sampled MSR_PR */
#घोषणा   SIER_SIHV		0x1000000	/* Sampled MSR_HV */
#घोषणा   SIER_SIAR_VALID	0x0400000	/* SIAR contents valid */
#घोषणा   SIER_SDAR_VALID	0x0200000	/* SDAR contents valid */
#घोषणा SPRN_SIER2	752
#घोषणा SPRN_SIER3	753
#घोषणा SPRN_USIER2	736
#घोषणा SPRN_USIER3	737
#घोषणा SPRN_SIAR	796
#घोषणा SPRN_SDAR	797
#घोषणा SPRN_TACR	888
#घोषणा SPRN_TCSCR	889
#घोषणा SPRN_CSIGR	890
#घोषणा SPRN_SPMC1	892
#घोषणा SPRN_SPMC2	893

/* When EBB is enabled, some of MMCR0/MMCR2/SIER are user accessible */
#घोषणा MMCR0_USER_MASK	(MMCR0_FC | MMCR0_PMXE | MMCR0_PMAO)
#घोषणा MMCR2_USER_MASK	0x4020100804020000UL /* (FC1P|FC2P|FC3P|FC4P|FC5P|FC6P) */
#घोषणा SIER_USER_MASK	0x7fffffUL

#घोषणा SPRN_PA6T_MMCR0 795
#घोषणा   PA6T_MMCR0_EN0	0x0000000000000001UL
#घोषणा   PA6T_MMCR0_EN1	0x0000000000000002UL
#घोषणा   PA6T_MMCR0_EN2	0x0000000000000004UL
#घोषणा   PA6T_MMCR0_EN3	0x0000000000000008UL
#घोषणा   PA6T_MMCR0_EN4	0x0000000000000010UL
#घोषणा   PA6T_MMCR0_EN5	0x0000000000000020UL
#घोषणा   PA6T_MMCR0_SUPEN	0x0000000000000040UL
#घोषणा   PA6T_MMCR0_PREN	0x0000000000000080UL
#घोषणा   PA6T_MMCR0_HYPEN	0x0000000000000100UL
#घोषणा   PA6T_MMCR0_FCM0	0x0000000000000200UL
#घोषणा   PA6T_MMCR0_FCM1	0x0000000000000400UL
#घोषणा   PA6T_MMCR0_INTGEN	0x0000000000000800UL
#घोषणा   PA6T_MMCR0_INTEN0	0x0000000000001000UL
#घोषणा   PA6T_MMCR0_INTEN1	0x0000000000002000UL
#घोषणा   PA6T_MMCR0_INTEN2	0x0000000000004000UL
#घोषणा   PA6T_MMCR0_INTEN3	0x0000000000008000UL
#घोषणा   PA6T_MMCR0_INTEN4	0x0000000000010000UL
#घोषणा   PA6T_MMCR0_INTEN5	0x0000000000020000UL
#घोषणा   PA6T_MMCR0_DISCNT	0x0000000000040000UL
#घोषणा   PA6T_MMCR0_UOP	0x0000000000080000UL
#घोषणा   PA6T_MMCR0_TRG	0x0000000000100000UL
#घोषणा   PA6T_MMCR0_TRGEN	0x0000000000200000UL
#घोषणा   PA6T_MMCR0_TRGREG	0x0000000001600000UL
#घोषणा   PA6T_MMCR0_SIARLOG	0x0000000002000000UL
#घोषणा   PA6T_MMCR0_SDARLOG	0x0000000004000000UL
#घोषणा   PA6T_MMCR0_PROEN	0x0000000008000000UL
#घोषणा   PA6T_MMCR0_PROLOG	0x0000000010000000UL
#घोषणा   PA6T_MMCR0_DAMEN2	0x0000000020000000UL
#घोषणा   PA6T_MMCR0_DAMEN3	0x0000000040000000UL
#घोषणा   PA6T_MMCR0_DAMEN4	0x0000000080000000UL
#घोषणा   PA6T_MMCR0_DAMEN5	0x0000000100000000UL
#घोषणा   PA6T_MMCR0_DAMSEL2	0x0000000200000000UL
#घोषणा   PA6T_MMCR0_DAMSEL3	0x0000000400000000UL
#घोषणा   PA6T_MMCR0_DAMSEL4	0x0000000800000000UL
#घोषणा   PA6T_MMCR0_DAMSEL5	0x0000001000000000UL
#घोषणा   PA6T_MMCR0_HANDDIS	0x0000002000000000UL
#घोषणा   PA6T_MMCR0_PCTEN	0x0000004000000000UL
#घोषणा   PA6T_MMCR0_SOCEN	0x0000008000000000UL
#घोषणा   PA6T_MMCR0_SOCMOD	0x0000010000000000UL

#घोषणा SPRN_PA6T_MMCR1 798
#घोषणा   PA6T_MMCR1_ES2	0x00000000000000ffUL
#घोषणा   PA6T_MMCR1_ES3	0x000000000000ff00UL
#घोषणा   PA6T_MMCR1_ES4	0x0000000000ff0000UL
#घोषणा   PA6T_MMCR1_ES5	0x00000000ff000000UL

#घोषणा SPRN_PA6T_UPMC0 771	/* User PerfMon Counter 0 */
#घोषणा SPRN_PA6T_UPMC1 772	/* ... */
#घोषणा SPRN_PA6T_UPMC2 773
#घोषणा SPRN_PA6T_UPMC3 774
#घोषणा SPRN_PA6T_UPMC4 775
#घोषणा SPRN_PA6T_UPMC5 776
#घोषणा SPRN_PA6T_UMMCR0 779	/* User Monitor Mode Control Register 0 */
#घोषणा SPRN_PA6T_SIAR	780	/* Sampled Inकाष्ठाion Address */
#घोषणा SPRN_PA6T_UMMCR1 782	/* User Monitor Mode Control Register 1 */
#घोषणा SPRN_PA6T_SIER	785	/* Sampled Inकाष्ठाion Event Register */
#घोषणा SPRN_PA6T_PMC0	787
#घोषणा SPRN_PA6T_PMC1	788
#घोषणा SPRN_PA6T_PMC2	789
#घोषणा SPRN_PA6T_PMC3	790
#घोषणा SPRN_PA6T_PMC4	791
#घोषणा SPRN_PA6T_PMC5	792
#घोषणा SPRN_PA6T_TSR0	793	/* Timestamp Register 0 */
#घोषणा SPRN_PA6T_TSR1	794	/* Timestamp Register 1 */
#घोषणा SPRN_PA6T_TSR2	799	/* Timestamp Register 2 */
#घोषणा SPRN_PA6T_TSR3	784	/* Timestamp Register 3 */

#घोषणा SPRN_PA6T_IER	981	/* Icache Error Register */
#घोषणा SPRN_PA6T_DER	982	/* Dcache Error Register */
#घोषणा SPRN_PA6T_BER	862	/* BIU Error Address Register */
#घोषणा SPRN_PA6T_MER	849	/* MMU Error Register */

#घोषणा SPRN_PA6T_IMA0	880	/* Inकाष्ठाion Match Array 0 */
#घोषणा SPRN_PA6T_IMA1	881	/* ... */
#घोषणा SPRN_PA6T_IMA2	882
#घोषणा SPRN_PA6T_IMA3	883
#घोषणा SPRN_PA6T_IMA4	884
#घोषणा SPRN_PA6T_IMA5	885
#घोषणा SPRN_PA6T_IMA6	886
#घोषणा SPRN_PA6T_IMA7	887
#घोषणा SPRN_PA6T_IMA8	888
#घोषणा SPRN_PA6T_IMA9	889
#घोषणा SPRN_PA6T_BTCR	978	/* Breakpoपूर्णांक and Tagging Control Register */
#घोषणा SPRN_PA6T_IMAAT	979	/* Inकाष्ठाion Match Array Action Table */
#घोषणा SPRN_PA6T_PCCR	1019	/* Power Counter Control Register */
#घोषणा SPRN_BKMK	1020	/* Cell Bookmark Register */
#घोषणा SPRN_PA6T_RPCCR	1021	/* Retire PC Trace Control Register */


#अन्यथा /* 32-bit */
#घोषणा SPRN_MMCR0	952	/* Monitor Mode Control Register 0 */
#घोषणा   MMCR0_FC	0x80000000UL /* मुक्तze counters */
#घोषणा   MMCR0_FCS	0x40000000UL /* मुक्तze in supervisor state */
#घोषणा   MMCR0_FCP	0x20000000UL /* मुक्तze in problem state */
#घोषणा   MMCR0_FCM1	0x10000000UL /* मुक्तze counters जबतक MSR mark = 1 */
#घोषणा   MMCR0_FCM0	0x08000000UL /* मुक्तze counters जबतक MSR mark = 0 */
#घोषणा   MMCR0_PMXE	0x04000000UL /* perक्रमmance monitor exception enable */
#घोषणा   MMCR0_FCECE	0x02000000UL /* मुक्तze ctrs on enabled cond or event */
#घोषणा   MMCR0_TBEE	0x00400000UL /* समय base exception enable */
#घोषणा   MMCR0_PMC1CE	0x00008000UL /* PMC1 count enable*/
#घोषणा   MMCR0_PMCnCE	0x00004000UL /* count enable क्रम all but PMC 1*/
#घोषणा   MMCR0_TRIGGER	0x00002000UL /* TRIGGER enable */
#घोषणा   MMCR0_PMC1SEL	0x00001fc0UL /* PMC 1 Event */
#घोषणा   MMCR0_PMC2SEL	0x0000003fUL /* PMC 2 Event */

#घोषणा SPRN_MMCR1	956
#घोषणा   MMCR1_PMC3SEL	0xf8000000UL /* PMC 3 Event */
#घोषणा   MMCR1_PMC4SEL	0x07c00000UL /* PMC 4 Event */
#घोषणा   MMCR1_PMC5SEL	0x003e0000UL /* PMC 5 Event */
#घोषणा   MMCR1_PMC6SEL 0x0001f800UL /* PMC 6 Event */
#घोषणा SPRN_MMCR2	944
#घोषणा SPRN_PMC1	953	/* Perक्रमmance Counter Register 1 */
#घोषणा SPRN_PMC2	954	/* Perक्रमmance Counter Register 2 */
#घोषणा SPRN_PMC3	957	/* Perक्रमmance Counter Register 3 */
#घोषणा SPRN_PMC4	958	/* Perक्रमmance Counter Register 4 */
#घोषणा SPRN_PMC5	945	/* Perक्रमmance Counter Register 5 */
#घोषणा SPRN_PMC6	946	/* Perक्रमmance Counter Register 6 */

#घोषणा SPRN_SIAR	955	/* Sampled Inकाष्ठाion Address Register */

/* Bit definitions क्रम MMCR0 and PMC1 / PMC2. */
#घोषणा MMCR0_PMC1_CYCLES	(1 << 7)
#घोषणा MMCR0_PMC1_ICACHEMISS	(5 << 7)
#घोषणा MMCR0_PMC1_DTLB		(6 << 7)
#घोषणा MMCR0_PMC2_DCACHEMISS	0x6
#घोषणा MMCR0_PMC2_CYCLES	0x1
#घोषणा MMCR0_PMC2_ITLB		0x7
#घोषणा MMCR0_PMC2_LOADMISSTIME	0x5
#पूर्ण_अगर

/*
 * SPRG usage:
 *
 * All 64-bit:
 *	- SPRG1 stores PACA poपूर्णांकer except 64-bit server in
 *        HV mode in which हाल it is HSPRG0
 *
 * 64-bit server:
 *	- SPRG0 scratch क्रम TM recheckpoपूर्णांक/reclaim (reserved क्रम HV on Power4)
 *	- SPRG2 scratch क्रम exception vectors
 *	- SPRG3 CPU and NUMA node क्रम VDSO अ_लोpu (user visible)
 *      - HSPRG0 stores PACA in HV mode
 *      - HSPRG1 scratch क्रम "HV" exceptions
 *
 * 64-bit embedded
 *	- SPRG0 generic exception scratch
 *	- SPRG2 TLB exception stack
 *	- SPRG3 critical exception scratch (user visible, sorry!)
 *	- SPRG4 unused (user visible)
 *	- SPRG6 TLB miss scratch (user visible, sorry !)
 *	- SPRG7 CPU and NUMA node क्रम VDSO अ_लोpu (user visible)
 *	- SPRG8 machine check exception scratch
 *	- SPRG9 debug exception scratch
 *
 * All 32-bit:
 *	- SPRG3 current thपढ़ो_काष्ठा physical addr poपूर्णांकer
 *        (भव on BookE, physical on others)
 *
 * 32-bit classic:
 *	- SPRG0 scratch क्रम exception vectors
 *	- SPRG1 scratch क्रम exception vectors
 *	- SPRG2 indicator that we are in RTAS
 *	- SPRG4 (603 only) pseuकरो TLB LRU data
 *
 * 32-bit 40x:
 *	- SPRG0 scratch क्रम exception vectors
 *	- SPRG1 scratch क्रम exception vectors
 *	- SPRG2 scratch क्रम exception vectors
 *	- SPRG4 scratch क्रम exception vectors (not 403)
 *	- SPRG5 scratch क्रम exception vectors (not 403)
 *	- SPRG6 scratch क्रम exception vectors (not 403)
 *	- SPRG7 scratch क्रम exception vectors (not 403)
 *
 * 32-bit 440 and FSL BookE:
 *	- SPRG0 scratch क्रम exception vectors
 *	- SPRG1 scratch क्रम exception vectors (*)
 *	- SPRG2 scratch क्रम crit पूर्णांकerrupts handler
 *	- SPRG4 scratch क्रम exception vectors
 *	- SPRG5 scratch क्रम exception vectors
 *	- SPRG6 scratch क्रम machine check handler
 *	- SPRG7 scratch क्रम exception vectors
 *	- SPRG9 scratch क्रम debug vectors (e500 only)
 *
 *      Additionally, BookE separates "read" and "write"
 *      of those रेजिस्टरs. That allows to use the userspace
 *      पढ़ोable variant क्रम पढ़ोs, which can aव्योम a fault
 *      with KVM type भवization.
 *
 * 32-bit 8xx:
 *	- SPRG0 scratch क्रम exception vectors
 *	- SPRG1 scratch क्रम exception vectors
 *	- SPRG2 scratch क्रम exception vectors
 *
 */
#अगर_घोषित CONFIG_PPC64
#घोषणा SPRN_SPRG_PACA 		SPRN_SPRG1
#अन्यथा
#घोषणा SPRN_SPRG_THREAD 	SPRN_SPRG3
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#घोषणा SPRN_SPRG_SCRATCH0	SPRN_SPRG2
#घोषणा SPRN_SPRG_HPACA		SPRN_HSPRG0
#घोषणा SPRN_SPRG_HSCRATCH0	SPRN_HSPRG1
#घोषणा SPRN_SPRG_VDSO_READ	SPRN_USPRG3
#घोषणा SPRN_SPRG_VDSO_WRITE	SPRN_SPRG3

#घोषणा GET_PACA(rX)					\
	BEGIN_FTR_SECTION_NESTED(66);			\
	mfspr	rX,SPRN_SPRG_PACA;			\
	FTR_SECTION_ELSE_NESTED(66);			\
	mfspr	rX,SPRN_SPRG_HPACA;			\
	ALT_FTR_SECTION_END_NESTED_IFCLR(CPU_FTR_HVMODE, 66)

#घोषणा SET_PACA(rX)					\
	BEGIN_FTR_SECTION_NESTED(66);			\
	mtspr	SPRN_SPRG_PACA,rX;			\
	FTR_SECTION_ELSE_NESTED(66);			\
	mtspr	SPRN_SPRG_HPACA,rX;			\
	ALT_FTR_SECTION_END_NESTED_IFCLR(CPU_FTR_HVMODE, 66)

#घोषणा GET_SCRATCH0(rX)				\
	BEGIN_FTR_SECTION_NESTED(66);			\
	mfspr	rX,SPRN_SPRG_SCRATCH0;			\
	FTR_SECTION_ELSE_NESTED(66);			\
	mfspr	rX,SPRN_SPRG_HSCRATCH0;			\
	ALT_FTR_SECTION_END_NESTED_IFCLR(CPU_FTR_HVMODE, 66)

#घोषणा SET_SCRATCH0(rX)				\
	BEGIN_FTR_SECTION_NESTED(66);			\
	mtspr	SPRN_SPRG_SCRATCH0,rX;			\
	FTR_SECTION_ELSE_NESTED(66);			\
	mtspr	SPRN_SPRG_HSCRATCH0,rX;			\
	ALT_FTR_SECTION_END_NESTED_IFCLR(CPU_FTR_HVMODE, 66)

#अन्यथा /* CONFIG_PPC_BOOK3S_64 */
#घोषणा GET_SCRATCH0(rX)	mfspr	rX,SPRN_SPRG_SCRATCH0
#घोषणा SET_SCRATCH0(rX)	mtspr	SPRN_SPRG_SCRATCH0,rX

#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3E_64
#घोषणा SPRN_SPRG_MC_SCRATCH	SPRN_SPRG8
#घोषणा SPRN_SPRG_CRIT_SCRATCH	SPRN_SPRG3
#घोषणा SPRN_SPRG_DBG_SCRATCH	SPRN_SPRG9
#घोषणा SPRN_SPRG_TLB_EXFRAME	SPRN_SPRG2
#घोषणा SPRN_SPRG_TLB_SCRATCH	SPRN_SPRG6
#घोषणा SPRN_SPRG_GEN_SCRATCH	SPRN_SPRG0
#घोषणा SPRN_SPRG_GDBELL_SCRATCH SPRN_SPRG_GEN_SCRATCH
#घोषणा SPRN_SPRG_VDSO_READ	SPRN_USPRG7
#घोषणा SPRN_SPRG_VDSO_WRITE	SPRN_SPRG7

#घोषणा SET_PACA(rX)	mtspr	SPRN_SPRG_PACA,rX
#घोषणा GET_PACA(rX)	mfspr	rX,SPRN_SPRG_PACA

#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_32
#घोषणा SPRN_SPRG_SCRATCH0	SPRN_SPRG0
#घोषणा SPRN_SPRG_SCRATCH1	SPRN_SPRG1
#घोषणा SPRN_SPRG_SCRATCH2	SPRN_SPRG2
#घोषणा SPRN_SPRG_603_LRU	SPRN_SPRG4
#पूर्ण_अगर

#अगर_घोषित CONFIG_40x
#घोषणा SPRN_SPRG_SCRATCH0	SPRN_SPRG0
#घोषणा SPRN_SPRG_SCRATCH1	SPRN_SPRG1
#घोषणा SPRN_SPRG_SCRATCH2	SPRN_SPRG2
#घोषणा SPRN_SPRG_SCRATCH3	SPRN_SPRG4
#घोषणा SPRN_SPRG_SCRATCH4	SPRN_SPRG5
#घोषणा SPRN_SPRG_SCRATCH5	SPRN_SPRG6
#घोषणा SPRN_SPRG_SCRATCH6	SPRN_SPRG7
#पूर्ण_अगर

#अगर_घोषित CONFIG_BOOKE
#घोषणा SPRN_SPRG_RSCRATCH0	SPRN_SPRG0
#घोषणा SPRN_SPRG_WSCRATCH0	SPRN_SPRG0
#घोषणा SPRN_SPRG_RSCRATCH1	SPRN_SPRG1
#घोषणा SPRN_SPRG_WSCRATCH1	SPRN_SPRG1
#घोषणा SPRN_SPRG_RSCRATCH_CRIT	SPRN_SPRG2
#घोषणा SPRN_SPRG_WSCRATCH_CRIT	SPRN_SPRG2
#घोषणा SPRN_SPRG_RSCRATCH2	SPRN_SPRG4R
#घोषणा SPRN_SPRG_WSCRATCH2	SPRN_SPRG4W
#घोषणा SPRN_SPRG_RSCRATCH3	SPRN_SPRG5R
#घोषणा SPRN_SPRG_WSCRATCH3	SPRN_SPRG5W
#घोषणा SPRN_SPRG_RSCRATCH_MC	SPRN_SPRG1
#घोषणा SPRN_SPRG_WSCRATCH_MC	SPRN_SPRG1
#घोषणा SPRN_SPRG_RSCRATCH4	SPRN_SPRG7R
#घोषणा SPRN_SPRG_WSCRATCH4	SPRN_SPRG7W
#घोषणा SPRN_SPRG_RSCRATCH_DBG	SPRN_SPRG9
#घोषणा SPRN_SPRG_WSCRATCH_DBG	SPRN_SPRG9
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_8xx
#घोषणा SPRN_SPRG_SCRATCH0	SPRN_SPRG0
#घोषणा SPRN_SPRG_SCRATCH1	SPRN_SPRG1
#घोषणा SPRN_SPRG_SCRATCH2	SPRN_SPRG2
#पूर्ण_अगर



/*
 * An mtfsf inकाष्ठाion with the L bit set. On CPUs that support this a
 * full 64bits of FPSCR is restored and on other CPUs the L bit is ignored.
 *
 * Until binutils माला_लो the new क्रमm of mtfsf, hardwire the inकाष्ठाion.
 */
#अगर_घोषित CONFIG_PPC64
#घोषणा MTFSF_L(REG) \
	.दीर्घ (0xfc00058e | ((0xff) << 17) | ((REG) << 11) | (1 << 25))
#अन्यथा
#घोषणा MTFSF_L(REG)	mtfsf	0xff, (REG)
#पूर्ण_अगर

/* Processor Version Register (PVR) field extraction */

#घोषणा PVR_VER(pvr)	(((pvr) >>  16) & 0xFFFF)	/* Version field */
#घोषणा PVR_REV(pvr)	(((pvr) >>   0) & 0xFFFF)	/* Revison field */

#घोषणा pvr_version_is(pvr)	(PVR_VER(mfspr(SPRN_PVR)) == (pvr))

/*
 * IBM has further subभागided the standard PowerPC 16-bit version and
 * revision subfields of the PVR क्रम the PowerPC 403s पूर्णांकo the following:
 */

#घोषणा PVR_FAM(pvr)	(((pvr) >> 20) & 0xFFF)	/* Family field */
#घोषणा PVR_MEM(pvr)	(((pvr) >> 16) & 0xF)	/* Member field */
#घोषणा PVR_CORE(pvr)	(((pvr) >> 12) & 0xF)	/* Core field */
#घोषणा PVR_CFG(pvr)	(((pvr) >>  8) & 0xF)	/* Configuration field */
#घोषणा PVR_MAJ(pvr)	(((pvr) >>  4) & 0xF)	/* Major revision field */
#घोषणा PVR_MIN(pvr)	(((pvr) >>  0) & 0xF)	/* Minor revision field */

/* Processor Version Numbers */

#घोषणा PVR_403GA	0x00200000
#घोषणा PVR_403GB	0x00200100
#घोषणा PVR_403GC	0x00200200
#घोषणा PVR_403GCX	0x00201400
#घोषणा PVR_405GP	0x40110000
#घोषणा PVR_476		0x11a52000
#घोषणा PVR_476FPE	0x7ff50000
#घोषणा PVR_STB03XXX	0x40310000
#घोषणा PVR_NP405H	0x41410000
#घोषणा PVR_NP405L	0x41610000
#घोषणा PVR_601		0x00010000
#घोषणा PVR_602		0x00050000
#घोषणा PVR_603		0x00030000
#घोषणा PVR_603e	0x00060000
#घोषणा PVR_603ev	0x00070000
#घोषणा PVR_603r	0x00071000
#घोषणा PVR_604		0x00040000
#घोषणा PVR_604e	0x00090000
#घोषणा PVR_604r	0x000A0000
#घोषणा PVR_620		0x00140000
#घोषणा PVR_740		0x00080000
#घोषणा PVR_750		PVR_740
#घोषणा PVR_740P	0x10080000
#घोषणा PVR_750P	PVR_740P
#घोषणा PVR_7400	0x000C0000
#घोषणा PVR_7410	0x800C0000
#घोषणा PVR_7450	0x80000000
#घोषणा PVR_8540	0x80200000
#घोषणा PVR_8560	0x80200000
#घोषणा PVR_VER_E500V1	0x8020
#घोषणा PVR_VER_E500V2	0x8021
#घोषणा PVR_VER_E500MC	0x8023
#घोषणा PVR_VER_E5500	0x8024
#घोषणा PVR_VER_E6500	0x8040

/*
 * For the 8xx processors, all of them report the same PVR family क्रम
 * the PowerPC core. The various versions of these processors must be
 * dअगरferentiated by the version number in the Communication Processor
 * Module (CPM).
 */
#घोषणा PVR_8xx		0x00500000

#घोषणा PVR_8240	0x00810100
#घोषणा PVR_8245	0x80811014
#घोषणा PVR_8260	PVR_8240

/* 476 Simulator seems to currently have the PVR of the 602... */
#घोषणा PVR_476_ISS	0x00052000

/* 64-bit processors */
#घोषणा PVR_NORTHSTAR	0x0033
#घोषणा PVR_PULSAR	0x0034
#घोषणा PVR_POWER4	0x0035
#घोषणा PVR_ICESTAR	0x0036
#घोषणा PVR_SSTAR	0x0037
#घोषणा PVR_POWER4p	0x0038
#घोषणा PVR_970		0x0039
#घोषणा PVR_POWER5	0x003A
#घोषणा PVR_POWER5p	0x003B
#घोषणा PVR_970FX	0x003C
#घोषणा PVR_POWER6	0x003E
#घोषणा PVR_POWER7	0x003F
#घोषणा PVR_630		0x0040
#घोषणा PVR_630p	0x0041
#घोषणा PVR_970MP	0x0044
#घोषणा PVR_970GX	0x0045
#घोषणा PVR_POWER7p	0x004A
#घोषणा PVR_POWER8E	0x004B
#घोषणा PVR_POWER8NVL	0x004C
#घोषणा PVR_POWER8	0x004D
#घोषणा PVR_POWER9	0x004E
#घोषणा PVR_POWER10	0x0080
#घोषणा PVR_BE		0x0070
#घोषणा PVR_PA6T	0x0090

/* "Logical" PVR values defined in PAPR, representing architecture levels */
#घोषणा PVR_ARCH_204	0x0f000001
#घोषणा PVR_ARCH_205	0x0f000002
#घोषणा PVR_ARCH_206	0x0f000003
#घोषणा PVR_ARCH_206p	0x0f100003
#घोषणा PVR_ARCH_207	0x0f000004
#घोषणा PVR_ARCH_300	0x0f000005
#घोषणा PVR_ARCH_31	0x0f000006

/* Macros क्रम setting and retrieving special purpose रेजिस्टरs */
#अगर_अघोषित __ASSEMBLY__
#घोषणा mfmsr()		(अणुअचिन्हित दीर्घ rval; \
			यंत्र अस्थिर("mfmsr %0" : "=r" (rval) : \
						: "memory"); rval;पूर्ण)
#अगर_घोषित CONFIG_PPC_BOOK3S_64
#घोषणा __mपंचांगsrd(v, l)	यंत्र अस्थिर("mtmsrd %0," __stringअगरy(l) \
				     : : "r" (v) : "memory")
#घोषणा mपंचांगsr(v)	__mपंचांगsrd((v), 0)
#घोषणा __MTMSR		"mtmsrd"
#अन्यथा
#घोषणा mपंचांगsr(v)	यंत्र अस्थिर("mtmsr %0" : \
				     : "r" ((अचिन्हित दीर्घ)(v)) \
				     : "memory")
#घोषणा __mपंचांगsrd(v, l)	BUILD_BUG()
#घोषणा __MTMSR		"mtmsr"
#पूर्ण_अगर

अटल अंतरभूत व्योम mपंचांगsr_isync(अचिन्हित दीर्घ val)
अणु
	यंत्र अस्थिर(__MTMSR " %0; " ASM_FTR_IFCLR("isync", "nop", %1) : :
			"r" (val), "i" (CPU_FTR_ARCH_206) : "memory");
पूर्ण

#घोषणा mfspr(rn)	(अणुअचिन्हित दीर्घ rval; \
			यंत्र अस्थिर("mfspr %0," __stringअगरy(rn) \
				: "=r" (rval)); rval;पूर्ण)
#अगर_अघोषित mtspr
#घोषणा mtspr(rn, v)	यंत्र अस्थिर("mtspr " __stringअगरy(rn) ",%0" : \
				     : "r" ((अचिन्हित दीर्घ)(v)) \
				     : "memory")
#पूर्ण_अगर
#घोषणा wrtspr(rn)	यंत्र अस्थिर("mtspr " __stringअगरy(rn) ",2" : : : "memory")

अटल अंतरभूत व्योम wrtee(अचिन्हित दीर्घ val)
अणु
	अगर (__builtin_स्थिरant_p(val))
		यंत्र अस्थिर("wrteei %0" : : "i" ((val & MSR_EE) ? 1 : 0) : "memory");
	अन्यथा
		यंत्र अस्थिर("wrtee %0" : : "r" (val) : "memory");
पूर्ण

बाह्य अचिन्हित दीर्घ msr_check_and_set(अचिन्हित दीर्घ bits);
बाह्य bool strict_msr_control;
बाह्य व्योम __msr_check_and_clear(अचिन्हित दीर्घ bits);
अटल अंतरभूत व्योम msr_check_and_clear(अचिन्हित दीर्घ bits)
अणु
	अगर (strict_msr_control)
		__msr_check_and_clear(bits);
पूर्ण

#अगर_घोषित CONFIG_PPC32
अटल अंतरभूत u32 mfsr(u32 idx)
अणु
	u32 val;

	अगर (__builtin_स्थिरant_p(idx))
		यंत्र अस्थिर("mfsr %0, %1" : "=r" (val): "i" (idx >> 28));
	अन्यथा
		यंत्र अस्थिर("mfsrin %0, %1" : "=r" (val): "r" (idx));

	वापस val;
पूर्ण

अटल अंतरभूत व्योम mtsr(u32 val, u32 idx)
अणु
	अगर (__builtin_स्थिरant_p(idx))
		यंत्र अस्थिर("mtsr %1, %0" : : "r" (val), "i" (idx >> 28));
	अन्यथा
		यंत्र अस्थिर("mtsrin %0, %1" : : "r" (val), "r" (idx));
पूर्ण
#पूर्ण_अगर

#घोषणा proc_trap()	यंत्र अस्थिर("trap")

बाह्य अचिन्हित दीर्घ current_stack_frame(व्योम);

रेजिस्टर अचिन्हित दीर्घ current_stack_poपूर्णांकer यंत्र("r1");

बाह्य अचिन्हित दीर्घ scom970_पढ़ो(अचिन्हित पूर्णांक address);
बाह्य व्योम scom970_ग_लिखो(अचिन्हित पूर्णांक address, अचिन्हित दीर्घ value);

काष्ठा pt_regs;

बाह्य व्योम ppc_save_regs(काष्ठा pt_regs *regs);

अटल अंतरभूत व्योम update_घातer8_hid0(अचिन्हित दीर्घ hid0)
अणु
	/*
	 *  The HID0 update on Power8 should at the very least be
	 *  preceded by a SYNC inकाष्ठाion followed by an ISYNC
	 *  inकाष्ठाion
	 */
	यंत्र अस्थिर("sync; mtspr %0,%1; isync":: "i"(SPRN_HID0), "r"(hid0));
पूर्ण
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_REG_H */
