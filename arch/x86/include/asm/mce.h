<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MCE_H
#घोषणा _ASM_X86_MCE_H

#समावेश <uapi/यंत्र/mce.h>

/*
 * Machine Check support क्रम x86
 */

/* MCG_CAP रेजिस्टर defines */
#घोषणा MCG_BANKCNT_MASK	0xff         /* Number of Banks */
#घोषणा MCG_CTL_P		BIT_ULL(8)   /* MCG_CTL रेजिस्टर available */
#घोषणा MCG_EXT_P		BIT_ULL(9)   /* Extended रेजिस्टरs available */
#घोषणा MCG_CMCI_P		BIT_ULL(10)  /* CMCI supported */
#घोषणा MCG_EXT_CNT_MASK	0xff0000     /* Number of Extended रेजिस्टरs */
#घोषणा MCG_EXT_CNT_SHIFT	16
#घोषणा MCG_EXT_CNT(c)		(((c) & MCG_EXT_CNT_MASK) >> MCG_EXT_CNT_SHIFT)
#घोषणा MCG_SER_P		BIT_ULL(24)  /* MCA recovery/new status bits */
#घोषणा MCG_ELOG_P		BIT_ULL(26)  /* Extended error log supported */
#घोषणा MCG_LMCE_P		BIT_ULL(27)  /* Local machine check supported */

/* MCG_STATUS रेजिस्टर defines */
#घोषणा MCG_STATUS_RIPV		BIT_ULL(0)   /* restart ip valid */
#घोषणा MCG_STATUS_EIPV		BIT_ULL(1)   /* ip poपूर्णांकs to correct inकाष्ठाion */
#घोषणा MCG_STATUS_MCIP		BIT_ULL(2)   /* machine check in progress */
#घोषणा MCG_STATUS_LMCES	BIT_ULL(3)   /* LMCE संकेतed */

/* MCG_EXT_CTL रेजिस्टर defines */
#घोषणा MCG_EXT_CTL_LMCE_EN	BIT_ULL(0) /* Enable LMCE */

/* MCi_STATUS रेजिस्टर defines */
#घोषणा MCI_STATUS_VAL		BIT_ULL(63)  /* valid error */
#घोषणा MCI_STATUS_OVER		BIT_ULL(62)  /* previous errors lost */
#घोषणा MCI_STATUS_UC		BIT_ULL(61)  /* uncorrected error */
#घोषणा MCI_STATUS_EN		BIT_ULL(60)  /* error enabled */
#घोषणा MCI_STATUS_MISCV	BIT_ULL(59)  /* misc error reg. valid */
#घोषणा MCI_STATUS_ADDRV	BIT_ULL(58)  /* addr reg. valid */
#घोषणा MCI_STATUS_PCC		BIT_ULL(57)  /* processor context corrupt */
#घोषणा MCI_STATUS_S		BIT_ULL(56)  /* Signaled machine check */
#घोषणा MCI_STATUS_AR		BIT_ULL(55)  /* Action required */
#घोषणा MCI_STATUS_CEC_SHIFT	38           /* Corrected Error Count */
#घोषणा MCI_STATUS_CEC_MASK	GENMASK_ULL(52,38)
#घोषणा MCI_STATUS_CEC(c)	(((c) & MCI_STATUS_CEC_MASK) >> MCI_STATUS_CEC_SHIFT)

/* AMD-specअगरic bits */
#घोषणा MCI_STATUS_TCC		BIT_ULL(55)  /* Task context corrupt */
#घोषणा MCI_STATUS_SYNDV	BIT_ULL(53)  /* synd reg. valid */
#घोषणा MCI_STATUS_DEFERRED	BIT_ULL(44)  /* uncorrected error, deferred exception */
#घोषणा MCI_STATUS_POISON	BIT_ULL(43)  /* access poisonous data */
#घोषणा MCI_STATUS_SCRUB	BIT_ULL(40)  /* Error detected during scrub operation */

/*
 * McaX field अगर set indicates a given bank supports MCA extensions:
 *  - Deferred error पूर्णांकerrupt type is specअगरiable by bank.
 *  - MCx_MISC0[BlkPtr] field indicates presence of extended MISC रेजिस्टरs,
 *    But should not be used to determine MSR numbers.
 *  - TCC bit is present in MCx_STATUS.
 */
#घोषणा MCI_CONFIG_MCAX		0x1
#घोषणा MCI_IPID_MCATYPE	0xFFFF0000
#घोषणा MCI_IPID_HWID		0xFFF

/*
 * Note that the full MCACOD field of IA32_MCi_STATUS MSR is
 * bits 15:0.  But bit 12 is the 'F' bit, defined क्रम corrected
 * errors to indicate that errors are being filtered by hardware.
 * We should mask out bit 12 when looking क्रम specअगरic signatures
 * of uncorrected errors - so the F bit is deliberately skipped
 * in this #घोषणा.
 */
#घोषणा MCACOD		  0xefff     /* MCA Error Code */

/* Architecturally defined codes from SDM Vol. 3B Chapter 15 */
#घोषणा MCACOD_SCRUB	0x00C0	/* 0xC0-0xCF Memory Scrubbing */
#घोषणा MCACOD_SCRUBMSK	0xeff0	/* Skip bit 12 ('F' bit) */
#घोषणा MCACOD_L3WB	0x017A	/* L3 Explicit Writeback */
#घोषणा MCACOD_DATA	0x0134	/* Data Load */
#घोषणा MCACOD_INSTR	0x0150	/* Inकाष्ठाion Fetch */

/* MCi_MISC रेजिस्टर defines */
#घोषणा MCI_MISC_ADDR_LSB(m)	((m) & 0x3f)
#घोषणा MCI_MISC_ADDR_MODE(m)	(((m) >> 6) & 7)
#घोषणा  MCI_MISC_ADDR_SEGOFF	0	/* segment offset */
#घोषणा  MCI_MISC_ADDR_LINEAR	1	/* linear address */
#घोषणा  MCI_MISC_ADDR_PHYS	2	/* physical address */
#घोषणा  MCI_MISC_ADDR_MEM	3	/* memory address */
#घोषणा  MCI_MISC_ADDR_GENERIC	7	/* generic */

/* CTL2 रेजिस्टर defines */
#घोषणा MCI_CTL2_CMCI_EN		BIT_ULL(30)
#घोषणा MCI_CTL2_CMCI_THRESHOLD_MASK	0x7fffULL

#घोषणा MCJ_CTX_MASK		3
#घोषणा MCJ_CTX(flags)		((flags) & MCJ_CTX_MASK)
#घोषणा MCJ_CTX_RANDOM		0    /* inject context: अक्रमom */
#घोषणा MCJ_CTX_PROCESS		0x1  /* inject context: process */
#घोषणा MCJ_CTX_IRQ		0x2  /* inject context: IRQ */
#घोषणा MCJ_NMI_BROADCAST	0x4  /* करो NMI broadcasting */
#घोषणा MCJ_EXCEPTION		0x8  /* उठाओ as exception */
#घोषणा MCJ_IRQ_BROADCAST	0x10 /* करो IRQ broadcasting */

#घोषणा MCE_OVERFLOW 0		/* bit 0 in flags means overflow */

#घोषणा MCE_LOG_MIN_LEN 32U
#घोषणा MCE_LOG_SIGNATURE	"MACHINECHECK"

/* AMD Scalable MCA */
#घोषणा MSR_AMD64_SMCA_MC0_CTL		0xc0002000
#घोषणा MSR_AMD64_SMCA_MC0_STATUS	0xc0002001
#घोषणा MSR_AMD64_SMCA_MC0_ADDR		0xc0002002
#घोषणा MSR_AMD64_SMCA_MC0_MISC0	0xc0002003
#घोषणा MSR_AMD64_SMCA_MC0_CONFIG	0xc0002004
#घोषणा MSR_AMD64_SMCA_MC0_IPID		0xc0002005
#घोषणा MSR_AMD64_SMCA_MC0_SYND		0xc0002006
#घोषणा MSR_AMD64_SMCA_MC0_DESTAT	0xc0002008
#घोषणा MSR_AMD64_SMCA_MC0_DEADDR	0xc0002009
#घोषणा MSR_AMD64_SMCA_MC0_MISC1	0xc000200a
#घोषणा MSR_AMD64_SMCA_MCx_CTL(x)	(MSR_AMD64_SMCA_MC0_CTL + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_STATUS(x)	(MSR_AMD64_SMCA_MC0_STATUS + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_ADDR(x)	(MSR_AMD64_SMCA_MC0_ADDR + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_MISC(x)	(MSR_AMD64_SMCA_MC0_MISC0 + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_CONFIG(x)	(MSR_AMD64_SMCA_MC0_CONFIG + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_IPID(x)	(MSR_AMD64_SMCA_MC0_IPID + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_SYND(x)	(MSR_AMD64_SMCA_MC0_SYND + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_DESTAT(x)	(MSR_AMD64_SMCA_MC0_DESTAT + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_DEADDR(x)	(MSR_AMD64_SMCA_MC0_DEADDR + 0x10*(x))
#घोषणा MSR_AMD64_SMCA_MCx_MISCy(x, y)	((MSR_AMD64_SMCA_MC0_MISC1 + y) + (0x10*(x)))

#घोषणा XEC(x, mask)			(((x) >> 16) & mask)

/* mce.kflags flag bits क्रम logging etc. */
#घोषणा	MCE_HANDLED_CEC		BIT_ULL(0)
#घोषणा	MCE_HANDLED_UC		BIT_ULL(1)
#घोषणा	MCE_HANDLED_EXTLOG	BIT_ULL(2)
#घोषणा	MCE_HANDLED_NFIT	BIT_ULL(3)
#घोषणा	MCE_HANDLED_EDAC	BIT_ULL(4)
#घोषणा	MCE_HANDLED_MCELOG	BIT_ULL(5)

/*
 * Indicates an MCE which has happened in kernel space but from
 * which the kernel can recover simply by executing fixup_exception()
 * so that an error is वापसed to the caller of the function that
 * hit the machine check.
 */
#घोषणा MCE_IN_KERNEL_RECOV	BIT_ULL(6)

/*
 * Indicates an MCE that happened in kernel space जबतक copying data
 * from user. In this हाल fixup_exception() माला_लो the kernel to the
 * error निकास क्रम the copy function. Machine check handler can then
 * treat it like a fault taken in user mode.
 */
#घोषणा MCE_IN_KERNEL_COPYIN	BIT_ULL(7)

/*
 * This काष्ठाure contains all data related to the MCE log.  Also
 * carries a signature to make it easier to find from बाह्यal
 * debugging tools.  Each entry is only valid when its finished flag
 * is set.
 */
काष्ठा mce_log_buffer अणु
	अक्षर signature[12]; /* "MACHINECHECK" */
	अचिन्हित len;	    /* = elements in .mce_entry[] */
	अचिन्हित next;
	अचिन्हित flags;
	अचिन्हित recordlen;	/* length of काष्ठा mce */
	काष्ठा mce entry[];
पूर्ण;

/* Highest last */
क्रमागत mce_notअगरier_prios अणु
	MCE_PRIO_LOWEST,
	MCE_PRIO_MCELOG,
	MCE_PRIO_EDAC,
	MCE_PRIO_NFIT,
	MCE_PRIO_EXTLOG,
	MCE_PRIO_UC,
	MCE_PRIO_EARLY,
	MCE_PRIO_CEC,
	MCE_PRIO_HIGHEST = MCE_PRIO_CEC
पूर्ण;

काष्ठा notअगरier_block;
बाह्य व्योम mce_रेजिस्टर_decode_chain(काष्ठा notअगरier_block *nb);
बाह्य व्योम mce_unरेजिस्टर_decode_chain(काष्ठा notअगरier_block *nb);

#समावेश <linux/percpu.h>
#समावेश <linux/atomic.h>

बाह्य पूर्णांक mce_p5_enabled;

#अगर_घोषित CONFIG_ARCH_HAS_COPY_MC
बाह्य व्योम enable_copy_mc_fragile(व्योम);
अचिन्हित दीर्घ __must_check copy_mc_fragile(व्योम *dst, स्थिर व्योम *src, अचिन्हित cnt);
#अन्यथा
अटल अंतरभूत व्योम enable_copy_mc_fragile(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा cper_ia_proc_ctx;

#अगर_घोषित CONFIG_X86_MCE
पूर्णांक mcheck_init(व्योम);
व्योम mcheck_cpu_init(काष्ठा cpuinfo_x86 *c);
व्योम mcheck_cpu_clear(काष्ठा cpuinfo_x86 *c);
व्योम mcheck_venकरोr_init_severity(व्योम);
पूर्णांक apei_smca_report_x86_error(काष्ठा cper_ia_proc_ctx *ctx_info,
			       u64 lapic_id);
#अन्यथा
अटल अंतरभूत पूर्णांक mcheck_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mcheck_cpu_init(काष्ठा cpuinfo_x86 *c) अणुपूर्ण
अटल अंतरभूत व्योम mcheck_cpu_clear(काष्ठा cpuinfo_x86 *c) अणुपूर्ण
अटल अंतरभूत व्योम mcheck_venकरोr_init_severity(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक apei_smca_report_x86_error(काष्ठा cper_ia_proc_ctx *ctx_info,
					     u64 lapic_id) अणु वापस -EINVAL; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_ANCIENT_MCE
व्योम पूर्णांकel_p5_mcheck_init(काष्ठा cpuinfo_x86 *c);
व्योम winchip_mcheck_init(काष्ठा cpuinfo_x86 *c);
अटल अंतरभूत व्योम enable_p5_mce(व्योम) अणु mce_p5_enabled = 1; पूर्ण
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_p5_mcheck_init(काष्ठा cpuinfo_x86 *c) अणुपूर्ण
अटल अंतरभूत व्योम winchip_mcheck_init(काष्ठा cpuinfo_x86 *c) अणुपूर्ण
अटल अंतरभूत व्योम enable_p5_mce(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम mce_setup(काष्ठा mce *m);
व्योम mce_log(काष्ठा mce *m);
DECLARE_PER_CPU(काष्ठा device *, mce_device);

/* Maximum number of MCA banks per CPU. */
#घोषणा MAX_NR_BANKS 64

#अगर_घोषित CONFIG_X86_MCE_INTEL
व्योम mce_पूर्णांकel_feature_init(काष्ठा cpuinfo_x86 *c);
व्योम mce_पूर्णांकel_feature_clear(काष्ठा cpuinfo_x86 *c);
व्योम cmci_clear(व्योम);
व्योम cmci_reenable(व्योम);
व्योम cmci_rediscover(व्योम);
व्योम cmci_recheck(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mce_पूर्णांकel_feature_init(काष्ठा cpuinfo_x86 *c) अणु पूर्ण
अटल अंतरभूत व्योम mce_पूर्णांकel_feature_clear(काष्ठा cpuinfo_x86 *c) अणु पूर्ण
अटल अंतरभूत व्योम cmci_clear(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम cmci_reenable(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम cmci_rediscover(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम cmci_recheck(व्योम) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक mce_available(काष्ठा cpuinfo_x86 *c);
bool mce_is_memory_error(काष्ठा mce *m);
bool mce_is_correctable(काष्ठा mce *m);
पूर्णांक mce_usable_address(काष्ठा mce *m);

DECLARE_PER_CPU(अचिन्हित, mce_exception_count);
DECLARE_PER_CPU(अचिन्हित, mce_poll_count);

प्रकार DECLARE_BITMAP(mce_banks_t, MAX_NR_BANKS);
DECLARE_PER_CPU(mce_banks_t, mce_poll_banks);

क्रमागत mcp_flags अणु
	MCP_TIMESTAMP	= BIT(0),	/* log समय stamp */
	MCP_UC		= BIT(1),	/* log uncorrected errors */
	MCP_DONTLOG	= BIT(2),	/* only clear, करोn't log */
पूर्ण;
bool machine_check_poll(क्रमागत mcp_flags flags, mce_banks_t *b);

पूर्णांक mce_notअगरy_irq(व्योम);

DECLARE_PER_CPU(काष्ठा mce, injecपंचांग);

/* Disable CMCI/polling क्रम MCA bank claimed by firmware */
बाह्य व्योम mce_disable_bank(पूर्णांक bank);

/*
 * Exception handler
 */
व्योम करो_machine_check(काष्ठा pt_regs *pt_regs);

/*
 * Threshold handler
 */
बाह्य व्योम (*mce_threshold_vector)(व्योम);

/* Deferred error पूर्णांकerrupt handler */
बाह्य व्योम (*deferred_error_पूर्णांक_vector)(व्योम);

/*
 * Used by APEI to report memory error via /dev/mcelog
 */

काष्ठा cper_sec_mem_err;
बाह्य व्योम apei_mce_report_mem_error(पूर्णांक corrected,
				      काष्ठा cper_sec_mem_err *mem_err);

/*
 * Enumerate new IP types and HWID values in AMD processors which support
 * Scalable MCA.
 */
#अगर_घोषित CONFIG_X86_MCE_AMD

/* These may be used by multiple smca_hwid_mcatypes */
क्रमागत smca_bank_types अणु
	SMCA_LS = 0,	/* Load Store */
	SMCA_LS_V2,	/* Load Store */
	SMCA_IF,	/* Inकाष्ठाion Fetch */
	SMCA_L2_CACHE,	/* L2 Cache */
	SMCA_DE,	/* Decoder Unit */
	SMCA_RESERVED,	/* Reserved */
	SMCA_EX,	/* Execution Unit */
	SMCA_FP,	/* Floating Poपूर्णांक */
	SMCA_L3_CACHE,	/* L3 Cache */
	SMCA_CS,	/* Coherent Slave */
	SMCA_CS_V2,	/* Coherent Slave */
	SMCA_PIE,	/* Power, Interrupts, etc. */
	SMCA_UMC,	/* Unअगरied Memory Controller */
	SMCA_PB,	/* Parameter Block */
	SMCA_PSP,	/* Platक्रमm Security Processor */
	SMCA_PSP_V2,	/* Platक्रमm Security Processor */
	SMCA_SMU,	/* System Management Unit */
	SMCA_SMU_V2,	/* System Management Unit */
	SMCA_MP5,	/* Microprocessor 5 Unit */
	SMCA_NBIO,	/* Northbridge IO Unit */
	SMCA_PCIE,	/* PCI Express Unit */
	N_SMCA_BANK_TYPES
पूर्ण;

#घोषणा HWID_MCATYPE(hwid, mcatype) (((hwid) << 16) | (mcatype))

काष्ठा smca_hwid अणु
	अचिन्हित पूर्णांक bank_type;	/* Use with smca_bank_types क्रम easy indexing. */
	u32 hwid_mcatype;	/* (hwid,mcatype) tuple */
	u8 count;		/* Number of instances. */
पूर्ण;

काष्ठा smca_bank अणु
	काष्ठा smca_hwid *hwid;
	u32 id;			/* Value of MCA_IPID[InstanceId]. */
	u8 sysfs_id;		/* Value used क्रम sysfs name. */
पूर्ण;

बाह्य काष्ठा smca_bank smca_banks[MAX_NR_BANKS];

बाह्य स्थिर अक्षर *smca_get_दीर्घ_name(क्रमागत smca_bank_types t);
बाह्य bool amd_mce_is_memory_error(काष्ठा mce *m);

बाह्य पूर्णांक mce_threshold_create_device(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक mce_threshold_हटाओ_device(अचिन्हित पूर्णांक cpu);

व्योम mce_amd_feature_init(काष्ठा cpuinfo_x86 *c);
पूर्णांक umc_normaddr_to_sysaddr(u64 norm_addr, u16 nid, u8 umc, u64 *sys_addr);

#अन्यथा

अटल अंतरभूत पूर्णांक mce_threshold_create_device(अचिन्हित पूर्णांक cpu)		अणु वापस 0; पूर्ण;
अटल अंतरभूत पूर्णांक mce_threshold_हटाओ_device(अचिन्हित पूर्णांक cpu)		अणु वापस 0; पूर्ण;
अटल अंतरभूत bool amd_mce_is_memory_error(काष्ठा mce *m)		अणु वापस false; पूर्ण;
अटल अंतरभूत व्योम mce_amd_feature_init(काष्ठा cpuinfo_x86 *c)		अणु पूर्ण
अटल अंतरभूत पूर्णांक
umc_normaddr_to_sysaddr(u64 norm_addr, u16 nid, u8 umc, u64 *sys_addr)	अणु वापस -EINVAL; पूर्ण;
#पूर्ण_अगर

अटल अंतरभूत व्योम mce_hygon_feature_init(काष्ठा cpuinfo_x86 *c)	अणु वापस mce_amd_feature_init(c); पूर्ण
#पूर्ण_अगर /* _ASM_X86_MCE_H */
