<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (c) 2005-2016 Advanced Micro Devices, Inc.
 *
 *  Written by Jacob Shin - AMD, Inc.
 *  Maपूर्णांकained by: Borislav Petkov <bp@alien8.de>
 *
 *  All MC4_MISCi रेजिस्टरs are shared between cores on a node.
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kobject.h>
#समावेश <linux/percpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/amd_nb.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/trace/irq_vectors.h>

#समावेश "internal.h"

#घोषणा NR_BLOCKS         5
#घोषणा THRESHOLD_MAX     0xFFF
#घोषणा INT_TYPE_APIC     0x00020000
#घोषणा MASK_VALID_HI     0x80000000
#घोषणा MASK_CNTP_HI      0x40000000
#घोषणा MASK_LOCKED_HI    0x20000000
#घोषणा MASK_LVTOFF_HI    0x00F00000
#घोषणा MASK_COUNT_EN_HI  0x00080000
#घोषणा MASK_INT_TYPE_HI  0x00060000
#घोषणा MASK_OVERFLOW_HI  0x00010000
#घोषणा MASK_ERR_COUNT_HI 0x00000FFF
#घोषणा MASK_BLKPTR_LO    0xFF000000
#घोषणा MCG_XBLK_ADDR     0xC0000400

/* Deferred error settings */
#घोषणा MSR_CU_DEF_ERR		0xC0000410
#घोषणा MASK_DEF_LVTOFF		0x000000F0
#घोषणा MASK_DEF_INT_TYPE	0x00000006
#घोषणा DEF_LVT_OFF		0x2
#घोषणा DEF_INT_TYPE_APIC	0x2

/* Scalable MCA: */

/* Threshold LVT offset is at MSR0xC0000410[15:12] */
#घोषणा SMCA_THR_LVT_OFF	0xF000

अटल bool thresholding_irq_en;

अटल स्थिर अक्षर * स्थिर th_names[] = अणु
	"load_store",
	"insn_fetch",
	"combined_unit",
	"decode_unit",
	"northbridge",
	"execution_unit",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smca_umc_block_names[] = अणु
	"dram_ecc",
	"misc_umc"
पूर्ण;

काष्ठा smca_bank_name अणु
	स्थिर अक्षर *name;	/* Short name क्रम sysfs */
	स्थिर अक्षर *दीर्घ_name;	/* Long name क्रम pretty-prपूर्णांकing */
पूर्ण;

अटल काष्ठा smca_bank_name smca_names[] = अणु
	[SMCA_LS]	= अणु "load_store",	"Load Store Unit" पूर्ण,
	[SMCA_LS_V2]	= अणु "load_store",	"Load Store Unit" पूर्ण,
	[SMCA_IF]	= अणु "insn_fetch",	"Instruction Fetch Unit" पूर्ण,
	[SMCA_L2_CACHE]	= अणु "l2_cache",		"L2 Cache" पूर्ण,
	[SMCA_DE]	= अणु "decode_unit",	"Decode Unit" पूर्ण,
	[SMCA_RESERVED]	= अणु "reserved",		"Reserved" पूर्ण,
	[SMCA_EX]	= अणु "execution_unit",	"Execution Unit" पूर्ण,
	[SMCA_FP]	= अणु "floating_point",	"Floating Point Unit" पूर्ण,
	[SMCA_L3_CACHE]	= अणु "l3_cache",		"L3 Cache" पूर्ण,
	[SMCA_CS]	= अणु "coherent_slave",	"Coherent Slave" पूर्ण,
	[SMCA_CS_V2]	= अणु "coherent_slave",	"Coherent Slave" पूर्ण,
	[SMCA_PIE]	= अणु "pie",		"Power, Interrupts, etc." पूर्ण,
	[SMCA_UMC]	= अणु "umc",		"Unified Memory Controller" पूर्ण,
	[SMCA_PB]	= अणु "param_block",	"Parameter Block" पूर्ण,
	[SMCA_PSP]	= अणु "psp",		"Platform Security Processor" पूर्ण,
	[SMCA_PSP_V2]	= अणु "psp",		"Platform Security Processor" पूर्ण,
	[SMCA_SMU]	= अणु "smu",		"System Management Unit" पूर्ण,
	[SMCA_SMU_V2]	= अणु "smu",		"System Management Unit" पूर्ण,
	[SMCA_MP5]	= अणु "mp5",		"Microprocessor 5 Unit" पूर्ण,
	[SMCA_NBIO]	= अणु "nbio",		"Northbridge IO Unit" पूर्ण,
	[SMCA_PCIE]	= अणु "pcie",		"PCI Express Unit" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *smca_get_name(क्रमागत smca_bank_types t)
अणु
	अगर (t >= N_SMCA_BANK_TYPES)
		वापस शून्य;

	वापस smca_names[t].name;
पूर्ण

स्थिर अक्षर *smca_get_दीर्घ_name(क्रमागत smca_bank_types t)
अणु
	अगर (t >= N_SMCA_BANK_TYPES)
		वापस शून्य;

	वापस smca_names[t].दीर्घ_name;
पूर्ण
EXPORT_SYMBOL_GPL(smca_get_दीर्घ_name);

अटल क्रमागत smca_bank_types smca_get_bank_type(अचिन्हित पूर्णांक bank)
अणु
	काष्ठा smca_bank *b;

	अगर (bank >= MAX_NR_BANKS)
		वापस N_SMCA_BANK_TYPES;

	b = &smca_banks[bank];
	अगर (!b->hwid)
		वापस N_SMCA_BANK_TYPES;

	वापस b->hwid->bank_type;
पूर्ण

अटल काष्ठा smca_hwid smca_hwid_mcatypes[] = अणु
	/* अणु bank_type, hwid_mcatype पूर्ण */

	/* Reserved type */
	अणु SMCA_RESERVED, HWID_MCATYPE(0x00, 0x0)	पूर्ण,

	/* ZN Core (HWID=0xB0) MCA types */
	अणु SMCA_LS,	 HWID_MCATYPE(0xB0, 0x0)	पूर्ण,
	अणु SMCA_LS_V2,	 HWID_MCATYPE(0xB0, 0x10)	पूर्ण,
	अणु SMCA_IF,	 HWID_MCATYPE(0xB0, 0x1)	पूर्ण,
	अणु SMCA_L2_CACHE, HWID_MCATYPE(0xB0, 0x2)	पूर्ण,
	अणु SMCA_DE,	 HWID_MCATYPE(0xB0, 0x3)	पूर्ण,
	/* HWID 0xB0 MCATYPE 0x4 is Reserved */
	अणु SMCA_EX,	 HWID_MCATYPE(0xB0, 0x5)	पूर्ण,
	अणु SMCA_FP,	 HWID_MCATYPE(0xB0, 0x6)	पूर्ण,
	अणु SMCA_L3_CACHE, HWID_MCATYPE(0xB0, 0x7)	पूर्ण,

	/* Data Fabric MCA types */
	अणु SMCA_CS,	 HWID_MCATYPE(0x2E, 0x0)	पूर्ण,
	अणु SMCA_PIE,	 HWID_MCATYPE(0x2E, 0x1)	पूर्ण,
	अणु SMCA_CS_V2,	 HWID_MCATYPE(0x2E, 0x2)	पूर्ण,

	/* Unअगरied Memory Controller MCA type */
	अणु SMCA_UMC,	 HWID_MCATYPE(0x96, 0x0)	पूर्ण,

	/* Parameter Block MCA type */
	अणु SMCA_PB,	 HWID_MCATYPE(0x05, 0x0)	पूर्ण,

	/* Platक्रमm Security Processor MCA type */
	अणु SMCA_PSP,	 HWID_MCATYPE(0xFF, 0x0)	पूर्ण,
	अणु SMCA_PSP_V2,	 HWID_MCATYPE(0xFF, 0x1)	पूर्ण,

	/* System Management Unit MCA type */
	अणु SMCA_SMU,	 HWID_MCATYPE(0x01, 0x0)	पूर्ण,
	अणु SMCA_SMU_V2,	 HWID_MCATYPE(0x01, 0x1)	पूर्ण,

	/* Microprocessor 5 Unit MCA type */
	अणु SMCA_MP5,	 HWID_MCATYPE(0x01, 0x2)	पूर्ण,

	/* Northbridge IO Unit MCA type */
	अणु SMCA_NBIO,	 HWID_MCATYPE(0x18, 0x0)	पूर्ण,

	/* PCI Express Unit MCA type */
	अणु SMCA_PCIE,	 HWID_MCATYPE(0x46, 0x0)	पूर्ण,
पूर्ण;

काष्ठा smca_bank smca_banks[MAX_NR_BANKS];
EXPORT_SYMBOL_GPL(smca_banks);

/*
 * In SMCA enabled processors, we can have multiple banks क्रम a given IP type.
 * So to define a unique name क्रम each bank, we use a temp c-string to append
 * the MCA_IPID[InstanceId] to type's name in get_name().
 *
 * InstanceId is 32 bits which is 8 अक्षरacters. Make sure MAX_MCATYPE_NAME_LEN
 * is greater than 8 plus 1 (क्रम underscore) plus length of दीर्घest type name.
 */
#घोषणा MAX_MCATYPE_NAME_LEN	30
अटल अक्षर buf_mcatype[MAX_MCATYPE_NAME_LEN];

अटल DEFINE_PER_CPU(काष्ठा threshold_bank **, threshold_banks);

/*
 * A list of the banks enabled on each logical CPU. Controls which respective
 * descriptors to initialize later in mce_threshold_create_device().
 */
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, bank_map);

/* Map of banks that have more than MCA_MISC0 available. */
अटल DEFINE_PER_CPU(u32, smca_misc_banks_map);

अटल व्योम amd_threshold_पूर्णांकerrupt(व्योम);
अटल व्योम amd_deferred_error_पूर्णांकerrupt(व्योम);

अटल व्योम शेष_deferred_error_पूर्णांकerrupt(व्योम)
अणु
	pr_err("Unexpected deferred interrupt at vector %x\n", DEFERRED_ERROR_VECTOR);
पूर्ण
व्योम (*deferred_error_पूर्णांक_vector)(व्योम) = शेष_deferred_error_पूर्णांकerrupt;

अटल व्योम smca_set_misc_banks_map(अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक cpu)
अणु
	u32 low, high;

	/*
	 * For SMCA enabled processors, BLKPTR field of the first MISC रेजिस्टर
	 * (MCx_MISC0) indicates presence of additional MISC regs set (MISC1-4).
	 */
	अगर (rdmsr_safe(MSR_AMD64_SMCA_MCx_CONFIG(bank), &low, &high))
		वापस;

	अगर (!(low & MCI_CONFIG_MCAX))
		वापस;

	अगर (rdmsr_safe(MSR_AMD64_SMCA_MCx_MISC(bank), &low, &high))
		वापस;

	अगर (low & MASK_BLKPTR_LO)
		per_cpu(smca_misc_banks_map, cpu) |= BIT(bank);

पूर्ण

अटल व्योम smca_configure(अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक i, hwid_mcatype;
	काष्ठा smca_hwid *s_hwid;
	u32 high, low;
	u32 smca_config = MSR_AMD64_SMCA_MCx_CONFIG(bank);

	/* Set appropriate bits in MCA_CONFIG */
	अगर (!rdmsr_safe(smca_config, &low, &high)) अणु
		/*
		 * OS is required to set the MCAX bit to acknowledge that it is
		 * now using the new MSR ranges and new रेजिस्टरs under each
		 * bank. It also means that the OS will configure deferred
		 * errors in the new MCx_CONFIG रेजिस्टर. If the bit is not set,
		 * uncorrectable errors will cause a प्रणाली panic.
		 *
		 * MCA_CONFIG[MCAX] is bit 32 (0 in the high portion of the MSR.)
		 */
		high |= BIT(0);

		/*
		 * SMCA sets the Deferred Error Interrupt type per bank.
		 *
		 * MCA_CONFIG[DeferredIntTypeSupported] is bit 5, and tells us
		 * अगर the DeferredIntType bit field is available.
		 *
		 * MCA_CONFIG[DeferredIntType] is bits [38:37] ([6:5] in the
		 * high portion of the MSR). OS should set this to 0x1 to enable
		 * APIC based पूर्णांकerrupt. First, check that no पूर्णांकerrupt has been
		 * set.
		 */
		अगर ((low & BIT(5)) && !((high >> 5) & 0x3))
			high |= BIT(5);

		wrmsr(smca_config, low, high);
	पूर्ण

	smca_set_misc_banks_map(bank, cpu);

	/* Return early अगर this bank was alपढ़ोy initialized. */
	अगर (smca_banks[bank].hwid && smca_banks[bank].hwid->hwid_mcatype != 0)
		वापस;

	अगर (rdmsr_safe(MSR_AMD64_SMCA_MCx_IPID(bank), &low, &high)) अणु
		pr_warn("Failed to read MCA_IPID for bank %d\n", bank);
		वापस;
	पूर्ण

	hwid_mcatype = HWID_MCATYPE(high & MCI_IPID_HWID,
				    (high & MCI_IPID_MCATYPE) >> 16);

	क्रम (i = 0; i < ARRAY_SIZE(smca_hwid_mcatypes); i++) अणु
		s_hwid = &smca_hwid_mcatypes[i];
		अगर (hwid_mcatype == s_hwid->hwid_mcatype) अणु
			smca_banks[bank].hwid = s_hwid;
			smca_banks[bank].id = low;
			smca_banks[bank].sysfs_id = s_hwid->count++;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा thresh_restart अणु
	काष्ठा threshold_block	*b;
	पूर्णांक			reset;
	पूर्णांक			set_lvt_off;
	पूर्णांक			lvt_off;
	u16			old_limit;
पूर्ण;

अटल अंतरभूत bool is_shared_bank(पूर्णांक bank)
अणु
	/*
	 * Scalable MCA provides क्रम only one core to have access to the MSRs of
	 * a shared bank.
	 */
	अगर (mce_flags.smca)
		वापस false;

	/* Bank 4 is क्रम northbridge reporting and is thus shared */
	वापस (bank == 4);
पूर्ण

अटल स्थिर अक्षर *bank4_names(स्थिर काष्ठा threshold_block *b)
अणु
	चयन (b->address) अणु
	/* MSR4_MISC0 */
	हाल 0x00000413:
		वापस "dram";

	हाल 0xc0000408:
		वापस "ht_links";

	हाल 0xc0000409:
		वापस "l3_cache";

	शेष:
		WARN(1, "Funny MSR: 0x%08x\n", b->address);
		वापस "";
	पूर्ण
पूर्ण;


अटल bool lvt_पूर्णांकerrupt_supported(अचिन्हित पूर्णांक bank, u32 msr_high_bits)
अणु
	/*
	 * bank 4 supports APIC LVT पूर्णांकerrupts implicitly since क्रमever.
	 */
	अगर (bank == 4)
		वापस true;

	/*
	 * IntP: पूर्णांकerrupt present; अगर this bit is set, the thresholding
	 * bank can generate APIC LVT पूर्णांकerrupts
	 */
	वापस msr_high_bits & BIT(28);
पूर्ण

अटल पूर्णांक lvt_off_valid(काष्ठा threshold_block *b, पूर्णांक apic, u32 lo, u32 hi)
अणु
	पूर्णांक msr = (hi & MASK_LVTOFF_HI) >> 20;

	अगर (apic < 0) अणु
		pr_err(FW_BUG "cpu %d, failed to setup threshold interrupt "
		       "for bank %d, block %d (MSR%08X=0x%x%08x)\n", b->cpu,
		       b->bank, b->block, b->address, hi, lo);
		वापस 0;
	पूर्ण

	अगर (apic != msr) अणु
		/*
		 * On SMCA CPUs, LVT offset is programmed at a dअगरferent MSR, and
		 * the BIOS provides the value. The original field where LVT offset
		 * was set is reserved. Return early here:
		 */
		अगर (mce_flags.smca)
			वापस 0;

		pr_err(FW_BUG "cpu %d, invalid threshold interrupt offset %d "
		       "for bank %d, block %d (MSR%08X=0x%x%08x)\n",
		       b->cpu, apic, b->bank, b->block, b->address, hi, lo);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण;

/* Reprogram MCx_MISC MSR behind this threshold bank. */
अटल व्योम threshold_restart_bank(व्योम *_tr)
अणु
	काष्ठा thresh_restart *tr = _tr;
	u32 hi, lo;

	/* sysfs ग_लिखो might race against an offline operation */
	अगर (this_cpu_पढ़ो(threshold_banks))
		वापस;

	rdmsr(tr->b->address, lo, hi);

	अगर (tr->b->threshold_limit < (hi & THRESHOLD_MAX))
		tr->reset = 1;	/* limit cannot be lower than err count */

	अगर (tr->reset) अणु		/* reset err count and overflow bit */
		hi =
		    (hi & ~(MASK_ERR_COUNT_HI | MASK_OVERFLOW_HI)) |
		    (THRESHOLD_MAX - tr->b->threshold_limit);
	पूर्ण अन्यथा अगर (tr->old_limit) अणु	/* change limit w/o reset */
		पूर्णांक new_count = (hi & THRESHOLD_MAX) +
		    (tr->old_limit - tr->b->threshold_limit);

		hi = (hi & ~MASK_ERR_COUNT_HI) |
		    (new_count & THRESHOLD_MAX);
	पूर्ण

	/* clear IntType */
	hi &= ~MASK_INT_TYPE_HI;

	अगर (!tr->b->पूर्णांकerrupt_capable)
		जाओ करोne;

	अगर (tr->set_lvt_off) अणु
		अगर (lvt_off_valid(tr->b, tr->lvt_off, lo, hi)) अणु
			/* set new lvt offset */
			hi &= ~MASK_LVTOFF_HI;
			hi |= tr->lvt_off << 20;
		पूर्ण
	पूर्ण

	अगर (tr->b->पूर्णांकerrupt_enable)
		hi |= INT_TYPE_APIC;

 करोne:

	hi |= MASK_COUNT_EN_HI;
	wrmsr(tr->b->address, lo, hi);
पूर्ण

अटल व्योम mce_threshold_block_init(काष्ठा threshold_block *b, पूर्णांक offset)
अणु
	काष्ठा thresh_restart tr = अणु
		.b			= b,
		.set_lvt_off		= 1,
		.lvt_off		= offset,
	पूर्ण;

	b->threshold_limit		= THRESHOLD_MAX;
	threshold_restart_bank(&tr);
पूर्ण;

अटल पूर्णांक setup_APIC_mce_threshold(पूर्णांक reserved, पूर्णांक new)
अणु
	अगर (reserved < 0 && !setup_APIC_eilvt(new, THRESHOLD_APIC_VECTOR,
					      APIC_EILVT_MSG_FIX, 0))
		वापस new;

	वापस reserved;
पूर्ण

अटल पूर्णांक setup_APIC_deferred_error(पूर्णांक reserved, पूर्णांक new)
अणु
	अगर (reserved < 0 && !setup_APIC_eilvt(new, DEFERRED_ERROR_VECTOR,
					      APIC_EILVT_MSG_FIX, 0))
		वापस new;

	वापस reserved;
पूर्ण

अटल व्योम deferred_error_पूर्णांकerrupt_enable(काष्ठा cpuinfo_x86 *c)
अणु
	u32 low = 0, high = 0;
	पूर्णांक def_offset = -1, def_new;

	अगर (rdmsr_safe(MSR_CU_DEF_ERR, &low, &high))
		वापस;

	def_new = (low & MASK_DEF_LVTOFF) >> 4;
	अगर (!(low & MASK_DEF_LVTOFF)) अणु
		pr_err(FW_BUG "Your BIOS is not setting up LVT offset 0x2 for deferred error IRQs correctly.\n");
		def_new = DEF_LVT_OFF;
		low = (low & ~MASK_DEF_LVTOFF) | (DEF_LVT_OFF << 4);
	पूर्ण

	def_offset = setup_APIC_deferred_error(def_offset, def_new);
	अगर ((def_offset == def_new) &&
	    (deferred_error_पूर्णांक_vector != amd_deferred_error_पूर्णांकerrupt))
		deferred_error_पूर्णांक_vector = amd_deferred_error_पूर्णांकerrupt;

	अगर (!mce_flags.smca)
		low = (low & ~MASK_DEF_INT_TYPE) | DEF_INT_TYPE_APIC;

	wrmsr(MSR_CU_DEF_ERR, low, high);
पूर्ण

अटल u32 smca_get_block_address(अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक block,
				  अचिन्हित पूर्णांक cpu)
अणु
	अगर (!block)
		वापस MSR_AMD64_SMCA_MCx_MISC(bank);

	अगर (!(per_cpu(smca_misc_banks_map, cpu) & BIT(bank)))
		वापस 0;

	वापस MSR_AMD64_SMCA_MCx_MISCy(bank, block - 1);
पूर्ण

अटल u32 get_block_address(u32 current_addr, u32 low, u32 high,
			     अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक block,
			     अचिन्हित पूर्णांक cpu)
अणु
	u32 addr = 0, offset = 0;

	अगर ((bank >= per_cpu(mce_num_banks, cpu)) || (block >= NR_BLOCKS))
		वापस addr;

	अगर (mce_flags.smca)
		वापस smca_get_block_address(bank, block, cpu);

	/* Fall back to method we used क्रम older processors: */
	चयन (block) अणु
	हाल 0:
		addr = msr_ops.misc(bank);
		अवरोध;
	हाल 1:
		offset = ((low & MASK_BLKPTR_LO) >> 21);
		अगर (offset)
			addr = MCG_XBLK_ADDR + offset;
		अवरोध;
	शेष:
		addr = ++current_addr;
	पूर्ण
	वापस addr;
पूर्ण

अटल पूर्णांक
prepare_threshold_block(अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक block, u32 addr,
			पूर्णांक offset, u32 misc_high)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u32 smca_low, smca_high;
	काष्ठा threshold_block b;
	पूर्णांक new;

	अगर (!block)
		per_cpu(bank_map, cpu) |= (1 << bank);

	स_रखो(&b, 0, माप(b));
	b.cpu			= cpu;
	b.bank			= bank;
	b.block			= block;
	b.address		= addr;
	b.पूर्णांकerrupt_capable	= lvt_पूर्णांकerrupt_supported(bank, misc_high);

	अगर (!b.पूर्णांकerrupt_capable)
		जाओ करोne;

	b.पूर्णांकerrupt_enable = 1;

	अगर (!mce_flags.smca) अणु
		new = (misc_high & MASK_LVTOFF_HI) >> 20;
		जाओ set_offset;
	पूर्ण

	/* Gather LVT offset क्रम thresholding: */
	अगर (rdmsr_safe(MSR_CU_DEF_ERR, &smca_low, &smca_high))
		जाओ out;

	new = (smca_low & SMCA_THR_LVT_OFF) >> 12;

set_offset:
	offset = setup_APIC_mce_threshold(offset, new);
	अगर (offset == new)
		thresholding_irq_en = true;

करोne:
	mce_threshold_block_init(&b, offset);

out:
	वापस offset;
पूर्ण

bool amd_filter_mce(काष्ठा mce *m)
अणु
	क्रमागत smca_bank_types bank_type = smca_get_bank_type(m->bank);
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	/* See Family 17h Models 10h-2Fh Erratum #1114. */
	अगर (c->x86 == 0x17 &&
	    c->x86_model >= 0x10 && c->x86_model <= 0x2F &&
	    bank_type == SMCA_IF && XEC(m->status, 0x3f) == 10)
		वापस true;

	/* NB GART TLB error reporting is disabled by शेष. */
	अगर (c->x86 < 0x17) अणु
		अगर (m->bank == 4 && XEC(m->status, 0x1f) == 0x5)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Turn off thresholding banks क्रम the following conditions:
 * - MC4_MISC thresholding is not supported on Family 0x15.
 * - Prevent possible spurious पूर्णांकerrupts from the IF bank on Family 0x17
 *   Models 0x10-0x2F due to Erratum #1114.
 */
अटल व्योम disable_err_thresholding(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक bank)
अणु
	पूर्णांक i, num_msrs;
	u64 hwcr;
	bool need_toggle;
	u32 msrs[NR_BLOCKS];

	अगर (c->x86 == 0x15 && bank == 4) अणु
		msrs[0] = 0x00000413; /* MC4_MISC0 */
		msrs[1] = 0xc0000408; /* MC4_MISC1 */
		num_msrs = 2;
	पूर्ण अन्यथा अगर (c->x86 == 0x17 &&
		   (c->x86_model >= 0x10 && c->x86_model <= 0x2F)) अणु

		अगर (smca_get_bank_type(bank) != SMCA_IF)
			वापस;

		msrs[0] = MSR_AMD64_SMCA_MCx_MISC(bank);
		num_msrs = 1;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	rdmsrl(MSR_K7_HWCR, hwcr);

	/* McStatusWrEn has to be set */
	need_toggle = !(hwcr & BIT(18));
	अगर (need_toggle)
		wrmsrl(MSR_K7_HWCR, hwcr | BIT(18));

	/* Clear CntP bit safely */
	क्रम (i = 0; i < num_msrs; i++)
		msr_clear_bit(msrs[i], 62);

	/* restore old settings */
	अगर (need_toggle)
		wrmsrl(MSR_K7_HWCR, hwcr);
पूर्ण

/* cpu init entry poपूर्णांक, called from mce.c with preempt off */
व्योम mce_amd_feature_init(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक bank, block, cpu = smp_processor_id();
	u32 low = 0, high = 0, address = 0;
	पूर्णांक offset = -1;


	क्रम (bank = 0; bank < this_cpu_पढ़ो(mce_num_banks); ++bank) अणु
		अगर (mce_flags.smca)
			smca_configure(bank, cpu);

		disable_err_thresholding(c, bank);

		क्रम (block = 0; block < NR_BLOCKS; ++block) अणु
			address = get_block_address(address, low, high, bank, block, cpu);
			अगर (!address)
				अवरोध;

			अगर (rdmsr_safe(address, &low, &high))
				अवरोध;

			अगर (!(high & MASK_VALID_HI))
				जारी;

			अगर (!(high & MASK_CNTP_HI)  ||
			     (high & MASK_LOCKED_HI))
				जारी;

			offset = prepare_threshold_block(bank, block, address, offset, high);
		पूर्ण
	पूर्ण

	अगर (mce_flags.succor)
		deferred_error_पूर्णांकerrupt_enable(c);
पूर्ण

पूर्णांक umc_normaddr_to_sysaddr(u64 norm_addr, u16 nid, u8 umc, u64 *sys_addr)
अणु
	u64 dram_base_addr, dram_limit_addr, dram_hole_base;
	/* We start from the normalized address */
	u64 ret_addr = norm_addr;

	u32 पंचांगp;

	u8 die_id_shअगरt, die_id_mask, socket_id_shअगरt, socket_id_mask;
	u8 पूर्णांकlv_num_dies, पूर्णांकlv_num_chan, पूर्णांकlv_num_sockets;
	u8 पूर्णांकlv_addr_sel, पूर्णांकlv_addr_bit;
	u8 num_पूर्णांकlv_bits, hashed_bit;
	u8 lgcy_mmio_hole_en, base = 0;
	u8 cs_mask, cs_id = 0;
	bool hash_enabled = false;

	/* Read D18F0x1B4 (DramOffset), check अगर base 1 is used. */
	अगर (amd_df_indirect_पढ़ो(nid, 0, 0x1B4, umc, &पंचांगp))
		जाओ out_err;

	/* Remove HiAddrOffset from normalized address, अगर enabled: */
	अगर (पंचांगp & BIT(0)) अणु
		u64 hi_addr_offset = (पंचांगp & GENMASK_ULL(31, 20)) << 8;

		अगर (norm_addr >= hi_addr_offset) अणु
			ret_addr -= hi_addr_offset;
			base = 1;
		पूर्ण
	पूर्ण

	/* Read D18F0x110 (DramBaseAddress). */
	अगर (amd_df_indirect_पढ़ो(nid, 0, 0x110 + (8 * base), umc, &पंचांगp))
		जाओ out_err;

	/* Check अगर address range is valid. */
	अगर (!(पंचांगp & BIT(0))) अणु
		pr_err("%s: Invalid DramBaseAddress range: 0x%x.\n",
			__func__, पंचांगp);
		जाओ out_err;
	पूर्ण

	lgcy_mmio_hole_en = पंचांगp & BIT(1);
	पूर्णांकlv_num_chan	  = (पंचांगp >> 4) & 0xF;
	पूर्णांकlv_addr_sel	  = (पंचांगp >> 8) & 0x7;
	dram_base_addr	  = (पंचांगp & GENMASK_ULL(31, 12)) << 16;

	/* अणु0, 1, 2, 3पूर्ण map to address bits अणु8, 9, 10, 11पूर्ण respectively */
	अगर (पूर्णांकlv_addr_sel > 3) अणु
		pr_err("%s: Invalid interleave address select %d.\n",
			__func__, पूर्णांकlv_addr_sel);
		जाओ out_err;
	पूर्ण

	/* Read D18F0x114 (DramLimitAddress). */
	अगर (amd_df_indirect_पढ़ो(nid, 0, 0x114 + (8 * base), umc, &पंचांगp))
		जाओ out_err;

	पूर्णांकlv_num_sockets = (पंचांगp >> 8) & 0x1;
	पूर्णांकlv_num_dies	  = (पंचांगp >> 10) & 0x3;
	dram_limit_addr	  = ((पंचांगp & GENMASK_ULL(31, 12)) << 16) | GENMASK_ULL(27, 0);

	पूर्णांकlv_addr_bit = पूर्णांकlv_addr_sel + 8;

	/* Re-use पूर्णांकlv_num_chan by setting it equal to log2(#channels) */
	चयन (पूर्णांकlv_num_chan) अणु
	हाल 0:	पूर्णांकlv_num_chan = 0; अवरोध;
	हाल 1: पूर्णांकlv_num_chan = 1; अवरोध;
	हाल 3: पूर्णांकlv_num_chan = 2; अवरोध;
	हाल 5:	पूर्णांकlv_num_chan = 3; अवरोध;
	हाल 7:	पूर्णांकlv_num_chan = 4; अवरोध;

	हाल 8: पूर्णांकlv_num_chan = 1;
		hash_enabled = true;
		अवरोध;
	शेष:
		pr_err("%s: Invalid number of interleaved channels %d.\n",
			__func__, पूर्णांकlv_num_chan);
		जाओ out_err;
	पूर्ण

	num_पूर्णांकlv_bits = पूर्णांकlv_num_chan;

	अगर (पूर्णांकlv_num_dies > 2) अणु
		pr_err("%s: Invalid number of interleaved nodes/dies %d.\n",
			__func__, पूर्णांकlv_num_dies);
		जाओ out_err;
	पूर्ण

	num_पूर्णांकlv_bits += पूर्णांकlv_num_dies;

	/* Add a bit अगर sockets are पूर्णांकerleaved. */
	num_पूर्णांकlv_bits += पूर्णांकlv_num_sockets;

	/* Assert num_पूर्णांकlv_bits <= 4 */
	अगर (num_पूर्णांकlv_bits > 4) अणु
		pr_err("%s: Invalid interleave bits %d.\n",
			__func__, num_पूर्णांकlv_bits);
		जाओ out_err;
	पूर्ण

	अगर (num_पूर्णांकlv_bits > 0) अणु
		u64 temp_addr_x, temp_addr_i, temp_addr_y;
		u8 die_id_bit, sock_id_bit, cs_fabric_id;

		/*
		 * Read FabricBlockInstanceInक्रमmation3_CS[BlockFabricID].
		 * This is the fabric id क्रम this coherent slave. Use
		 * umc/channel# as instance id of the coherent slave
		 * क्रम FICAA.
		 */
		अगर (amd_df_indirect_पढ़ो(nid, 0, 0x50, umc, &पंचांगp))
			जाओ out_err;

		cs_fabric_id = (पंचांगp >> 8) & 0xFF;
		die_id_bit   = 0;

		/* If पूर्णांकerleaved over more than 1 channel: */
		अगर (पूर्णांकlv_num_chan) अणु
			die_id_bit = पूर्णांकlv_num_chan;
			cs_mask	   = (1 << die_id_bit) - 1;
			cs_id	   = cs_fabric_id & cs_mask;
		पूर्ण

		sock_id_bit = die_id_bit;

		/* Read D18F1x208 (SystemFabricIdMask). */
		अगर (पूर्णांकlv_num_dies || पूर्णांकlv_num_sockets)
			अगर (amd_df_indirect_पढ़ो(nid, 1, 0x208, umc, &पंचांगp))
				जाओ out_err;

		/* If पूर्णांकerleaved over more than 1 die. */
		अगर (पूर्णांकlv_num_dies) अणु
			sock_id_bit  = die_id_bit + पूर्णांकlv_num_dies;
			die_id_shअगरt = (पंचांगp >> 24) & 0xF;
			die_id_mask  = (पंचांगp >> 8) & 0xFF;

			cs_id |= ((cs_fabric_id & die_id_mask) >> die_id_shअगरt) << die_id_bit;
		पूर्ण

		/* If पूर्णांकerleaved over more than 1 socket. */
		अगर (पूर्णांकlv_num_sockets) अणु
			socket_id_shअगरt	= (पंचांगp >> 28) & 0xF;
			socket_id_mask	= (पंचांगp >> 16) & 0xFF;

			cs_id |= ((cs_fabric_id & socket_id_mask) >> socket_id_shअगरt) << sock_id_bit;
		पूर्ण

		/*
		 * The pre-पूर्णांकerleaved address consists of XXXXXXIIIYYYYY
		 * where III is the ID क्रम this CS, and XXXXXXYYYYY are the
		 * address bits from the post-पूर्णांकerleaved address.
		 * "num_intlv_bits" has been calculated to tell us how many "I"
		 * bits there are. "intlv_addr_bit" tells us how many "Y" bits
		 * there are (where "I" starts).
		 */
		temp_addr_y = ret_addr & GENMASK_ULL(पूर्णांकlv_addr_bit-1, 0);
		temp_addr_i = (cs_id << पूर्णांकlv_addr_bit);
		temp_addr_x = (ret_addr & GENMASK_ULL(63, पूर्णांकlv_addr_bit)) << num_पूर्णांकlv_bits;
		ret_addr    = temp_addr_x | temp_addr_i | temp_addr_y;
	पूर्ण

	/* Add dram base address */
	ret_addr += dram_base_addr;

	/* If legacy MMIO hole enabled */
	अगर (lgcy_mmio_hole_en) अणु
		अगर (amd_df_indirect_पढ़ो(nid, 0, 0x104, umc, &पंचांगp))
			जाओ out_err;

		dram_hole_base = पंचांगp & GENMASK(31, 24);
		अगर (ret_addr >= dram_hole_base)
			ret_addr += (BIT_ULL(32) - dram_hole_base);
	पूर्ण

	अगर (hash_enabled) अणु
		/* Save some parentheses and grab ls-bit at the end. */
		hashed_bit =	(ret_addr >> 12) ^
				(ret_addr >> 18) ^
				(ret_addr >> 21) ^
				(ret_addr >> 30) ^
				cs_id;

		hashed_bit &= BIT(0);

		अगर (hashed_bit != ((ret_addr >> पूर्णांकlv_addr_bit) & BIT(0)))
			ret_addr ^= BIT(पूर्णांकlv_addr_bit);
	पूर्ण

	/* Is calculated प्रणाली address is above DRAM limit address? */
	अगर (ret_addr > dram_limit_addr)
		जाओ out_err;

	*sys_addr = ret_addr;
	वापस 0;

out_err:
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(umc_normaddr_to_sysaddr);

bool amd_mce_is_memory_error(काष्ठा mce *m)
अणु
	/* ErrCodeExt[20:16] */
	u8 xec = (m->status >> 16) & 0x1f;

	अगर (mce_flags.smca)
		वापस smca_get_bank_type(m->bank) == SMCA_UMC && xec == 0x0;

	वापस m->bank == 4 && xec == 0x8;
पूर्ण

अटल व्योम __log_error(अचिन्हित पूर्णांक bank, u64 status, u64 addr, u64 misc)
अणु
	काष्ठा mce m;

	mce_setup(&m);

	m.status = status;
	m.misc   = misc;
	m.bank   = bank;
	m.tsc	 = rdtsc();

	अगर (m.status & MCI_STATUS_ADDRV) अणु
		m.addr = addr;

		/*
		 * Extract [55:<lsb>] where lsb is the least signअगरicant
		 * *valid* bit of the address bits.
		 */
		अगर (mce_flags.smca) अणु
			u8 lsb = (m.addr >> 56) & 0x3f;

			m.addr &= GENMASK_ULL(55, lsb);
		पूर्ण
	पूर्ण

	अगर (mce_flags.smca) अणु
		rdmsrl(MSR_AMD64_SMCA_MCx_IPID(bank), m.ipid);

		अगर (m.status & MCI_STATUS_SYNDV)
			rdmsrl(MSR_AMD64_SMCA_MCx_SYND(bank), m.synd);
	पूर्ण

	mce_log(&m);
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_deferred_error)
अणु
	trace_deferred_error_apic_entry(DEFERRED_ERROR_VECTOR);
	inc_irq_stat(irq_deferred_error_count);
	deferred_error_पूर्णांक_vector();
	trace_deferred_error_apic_निकास(DEFERRED_ERROR_VECTOR);
	ack_APIC_irq();
पूर्ण

/*
 * Returns true अगर the logged error is deferred. False, otherwise.
 */
अटल अंतरभूत bool
_log_error_bank(अचिन्हित पूर्णांक bank, u32 msr_stat, u32 msr_addr, u64 misc)
अणु
	u64 status, addr = 0;

	rdmsrl(msr_stat, status);
	अगर (!(status & MCI_STATUS_VAL))
		वापस false;

	अगर (status & MCI_STATUS_ADDRV)
		rdmsrl(msr_addr, addr);

	__log_error(bank, status, addr, misc);

	wrmsrl(msr_stat, 0);

	वापस status & MCI_STATUS_DEFERRED;
पूर्ण

/*
 * We have three scenarios क्रम checking क्रम Deferred errors:
 *
 * 1) Non-SMCA प्रणालीs check MCA_STATUS and log error अगर found.
 * 2) SMCA प्रणालीs check MCA_STATUS. If error is found then log it and also
 *    clear MCA_DESTAT.
 * 3) SMCA प्रणालीs check MCA_DESTAT, अगर error was not found in MCA_STATUS, and
 *    log it.
 */
अटल व्योम log_error_deferred(अचिन्हित पूर्णांक bank)
अणु
	bool defrd;

	defrd = _log_error_bank(bank, msr_ops.status(bank),
					msr_ops.addr(bank), 0);

	अगर (!mce_flags.smca)
		वापस;

	/* Clear MCA_DESTAT अगर we logged the deferred error from MCA_STATUS. */
	अगर (defrd) अणु
		wrmsrl(MSR_AMD64_SMCA_MCx_DESTAT(bank), 0);
		वापस;
	पूर्ण

	/*
	 * Only deferred errors are logged in MCA_DEअणुSTAT,ADDRपूर्ण so just check
	 * क्रम a valid error.
	 */
	_log_error_bank(bank, MSR_AMD64_SMCA_MCx_DESTAT(bank),
			      MSR_AMD64_SMCA_MCx_DEADDR(bank), 0);
पूर्ण

/* APIC पूर्णांकerrupt handler क्रम deferred errors */
अटल व्योम amd_deferred_error_पूर्णांकerrupt(व्योम)
अणु
	अचिन्हित पूर्णांक bank;

	क्रम (bank = 0; bank < this_cpu_पढ़ो(mce_num_banks); ++bank)
		log_error_deferred(bank);
पूर्ण

अटल व्योम log_error_thresholding(अचिन्हित पूर्णांक bank, u64 misc)
अणु
	_log_error_bank(bank, msr_ops.status(bank), msr_ops.addr(bank), misc);
पूर्ण

अटल व्योम log_and_reset_block(काष्ठा threshold_block *block)
अणु
	काष्ठा thresh_restart tr;
	u32 low = 0, high = 0;

	अगर (!block)
		वापस;

	अगर (rdmsr_safe(block->address, &low, &high))
		वापस;

	अगर (!(high & MASK_OVERFLOW_HI))
		वापस;

	/* Log the MCE which caused the threshold event. */
	log_error_thresholding(block->bank, ((u64)high << 32) | low);

	/* Reset threshold block after logging error. */
	स_रखो(&tr, 0, माप(tr));
	tr.b = block;
	threshold_restart_bank(&tr);
पूर्ण

/*
 * Threshold पूर्णांकerrupt handler will service THRESHOLD_APIC_VECTOR. The पूर्णांकerrupt
 * goes off when error_count reaches threshold_limit.
 */
अटल व्योम amd_threshold_पूर्णांकerrupt(व्योम)
अणु
	काष्ठा threshold_block *first_block = शून्य, *block = शून्य, *पंचांगp = शून्य;
	काष्ठा threshold_bank **bp = this_cpu_पढ़ो(threshold_banks);
	अचिन्हित पूर्णांक bank, cpu = smp_processor_id();

	/*
	 * Validate that the threshold bank has been initialized alपढ़ोy. The
	 * handler is installed at boot समय, but on a hotplug event the
	 * पूर्णांकerrupt might fire beक्रमe the data has been initialized.
	 */
	अगर (!bp)
		वापस;

	क्रम (bank = 0; bank < this_cpu_पढ़ो(mce_num_banks); ++bank) अणु
		अगर (!(per_cpu(bank_map, cpu) & (1 << bank)))
			जारी;

		first_block = bp[bank]->blocks;
		अगर (!first_block)
			जारी;

		/*
		 * The first block is also the head of the list. Check it first
		 * beक्रमe iterating over the rest.
		 */
		log_and_reset_block(first_block);
		list_क्रम_each_entry_safe(block, पंचांगp, &first_block->miscj, miscj)
			log_and_reset_block(block);
	पूर्ण
पूर्ण

/*
 * Sysfs Interface
 */

काष्ठा threshold_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show) (काष्ठा threshold_block *, अक्षर *);
	sमाप_प्रकार (*store) (काष्ठा threshold_block *, स्थिर अक्षर *, माप_प्रकार count);
पूर्ण;

#घोषणा SHOW_FIELDS(name)						\
अटल sमाप_प्रकार show_ ## name(काष्ठा threshold_block *b, अक्षर *buf)	\
अणु									\
	वापस प्र_लिखो(buf, "%lu\n", (अचिन्हित दीर्घ) b->name);		\
पूर्ण
SHOW_FIELDS(पूर्णांकerrupt_enable)
SHOW_FIELDS(threshold_limit)

अटल sमाप_प्रकार
store_पूर्णांकerrupt_enable(काष्ठा threshold_block *b, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा thresh_restart tr;
	अचिन्हित दीर्घ new;

	अगर (!b->पूर्णांकerrupt_capable)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buf, 0, &new) < 0)
		वापस -EINVAL;

	b->पूर्णांकerrupt_enable = !!new;

	स_रखो(&tr, 0, माप(tr));
	tr.b		= b;

	अगर (smp_call_function_single(b->cpu, threshold_restart_bank, &tr, 1))
		वापस -ENODEV;

	वापस size;
पूर्ण

अटल sमाप_प्रकार
store_threshold_limit(काष्ठा threshold_block *b, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा thresh_restart tr;
	अचिन्हित दीर्घ new;

	अगर (kम_से_अदीर्घ(buf, 0, &new) < 0)
		वापस -EINVAL;

	अगर (new > THRESHOLD_MAX)
		new = THRESHOLD_MAX;
	अगर (new < 1)
		new = 1;

	स_रखो(&tr, 0, माप(tr));
	tr.old_limit = b->threshold_limit;
	b->threshold_limit = new;
	tr.b = b;

	अगर (smp_call_function_single(b->cpu, threshold_restart_bank, &tr, 1))
		वापस -ENODEV;

	वापस size;
पूर्ण

अटल sमाप_प्रकार show_error_count(काष्ठा threshold_block *b, अक्षर *buf)
अणु
	u32 lo, hi;

	/* CPU might be offline by now */
	अगर (rdmsr_on_cpu(b->cpu, b->address, &lo, &hi))
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%u\n", ((hi & THRESHOLD_MAX) -
				     (THRESHOLD_MAX - b->threshold_limit)));
पूर्ण

अटल काष्ठा threshold_attr error_count = अणु
	.attr = अणु.name = __stringअगरy(error_count), .mode = 0444 पूर्ण,
	.show = show_error_count,
पूर्ण;

#घोषणा RW_ATTR(val)							\
अटल काष्ठा threshold_attr val = अणु					\
	.attr	= अणु.name = __stringअगरy(val), .mode = 0644 पूर्ण,		\
	.show	= show_## val,						\
	.store	= store_## val,						\
पूर्ण;

RW_ATTR(पूर्णांकerrupt_enable);
RW_ATTR(threshold_limit);

अटल काष्ठा attribute *शेष_attrs[] = अणु
	&threshold_limit.attr,
	&error_count.attr,
	शून्य,	/* possibly पूर्णांकerrupt_enable अगर supported, see below */
	शून्य,
पूर्ण;

#घोषणा to_block(k)	container_of(k, काष्ठा threshold_block, kobj)
#घोषणा to_attr(a)	container_of(a, काष्ठा threshold_attr, attr)

अटल sमाप_प्रकार show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा threshold_block *b = to_block(kobj);
	काष्ठा threshold_attr *a = to_attr(attr);
	sमाप_प्रकार ret;

	ret = a->show ? a->show(b, buf) : -EIO;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा threshold_block *b = to_block(kobj);
	काष्ठा threshold_attr *a = to_attr(attr);
	sमाप_प्रकार ret;

	ret = a->store ? a->store(b, buf, count) : -EIO;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops threshold_ops = अणु
	.show			= show,
	.store			= store,
पूर्ण;

अटल व्योम threshold_block_release(काष्ठा kobject *kobj);

अटल काष्ठा kobj_type threshold_ktype = अणु
	.sysfs_ops		= &threshold_ops,
	.शेष_attrs		= शेष_attrs,
	.release		= threshold_block_release,
पूर्ण;

अटल स्थिर अक्षर *get_name(अचिन्हित पूर्णांक bank, काष्ठा threshold_block *b)
अणु
	क्रमागत smca_bank_types bank_type;

	अगर (!mce_flags.smca) अणु
		अगर (b && bank == 4)
			वापस bank4_names(b);

		वापस th_names[bank];
	पूर्ण

	bank_type = smca_get_bank_type(bank);
	अगर (bank_type >= N_SMCA_BANK_TYPES)
		वापस शून्य;

	अगर (b && bank_type == SMCA_UMC) अणु
		अगर (b->block < ARRAY_SIZE(smca_umc_block_names))
			वापस smca_umc_block_names[b->block];
		वापस शून्य;
	पूर्ण

	अगर (smca_banks[bank].hwid->count == 1)
		वापस smca_get_name(bank_type);

	snम_लिखो(buf_mcatype, MAX_MCATYPE_NAME_LEN,
		 "%s_%x", smca_get_name(bank_type),
			  smca_banks[bank].sysfs_id);
	वापस buf_mcatype;
पूर्ण

अटल पूर्णांक allocate_threshold_blocks(अचिन्हित पूर्णांक cpu, काष्ठा threshold_bank *tb,
				     अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक block,
				     u32 address)
अणु
	काष्ठा threshold_block *b = शून्य;
	u32 low, high;
	पूर्णांक err;

	अगर ((bank >= this_cpu_पढ़ो(mce_num_banks)) || (block >= NR_BLOCKS))
		वापस 0;

	अगर (rdmsr_safe(address, &low, &high))
		वापस 0;

	अगर (!(high & MASK_VALID_HI)) अणु
		अगर (block)
			जाओ recurse;
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (!(high & MASK_CNTP_HI)  ||
	     (high & MASK_LOCKED_HI))
		जाओ recurse;

	b = kzalloc(माप(काष्ठा threshold_block), GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	b->block		= block;
	b->bank			= bank;
	b->cpu			= cpu;
	b->address		= address;
	b->पूर्णांकerrupt_enable	= 0;
	b->पूर्णांकerrupt_capable	= lvt_पूर्णांकerrupt_supported(bank, high);
	b->threshold_limit	= THRESHOLD_MAX;

	अगर (b->पूर्णांकerrupt_capable) अणु
		threshold_ktype.शेष_attrs[2] = &पूर्णांकerrupt_enable.attr;
		b->पूर्णांकerrupt_enable = 1;
	पूर्ण अन्यथा अणु
		threshold_ktype.शेष_attrs[2] = शून्य;
	पूर्ण

	INIT_LIST_HEAD(&b->miscj);

	/* This is safe as @tb is not visible yet */
	अगर (tb->blocks)
		list_add(&b->miscj, &tb->blocks->miscj);
	अन्यथा
		tb->blocks = b;

	err = kobject_init_and_add(&b->kobj, &threshold_ktype, tb->kobj, get_name(bank, b));
	अगर (err)
		जाओ out_मुक्त;
recurse:
	address = get_block_address(address, low, high, bank, ++block, cpu);
	अगर (!address)
		वापस 0;

	err = allocate_threshold_blocks(cpu, tb, bank, block, address);
	अगर (err)
		जाओ out_मुक्त;

	अगर (b)
		kobject_uevent(&b->kobj, KOBJ_ADD);

	वापस 0;

out_मुक्त:
	अगर (b) अणु
		list_del(&b->miscj);
		kobject_put(&b->kobj);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __threshold_add_blocks(काष्ठा threshold_bank *b)
अणु
	काष्ठा list_head *head = &b->blocks->miscj;
	काष्ठा threshold_block *pos = शून्य;
	काष्ठा threshold_block *पंचांगp = शून्य;
	पूर्णांक err = 0;

	err = kobject_add(&b->blocks->kobj, b->kobj, b->blocks->kobj.name);
	अगर (err)
		वापस err;

	list_क्रम_each_entry_safe(pos, पंचांगp, head, miscj) अणु

		err = kobject_add(&pos->kobj, b->kobj, pos->kobj.name);
		अगर (err) अणु
			list_क्रम_each_entry_safe_reverse(pos, पंचांगp, head, miscj)
				kobject_del(&pos->kobj);

			वापस err;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक threshold_create_bank(काष्ठा threshold_bank **bp, अचिन्हित पूर्णांक cpu,
				 अचिन्हित पूर्णांक bank)
अणु
	काष्ठा device *dev = this_cpu_पढ़ो(mce_device);
	काष्ठा amd_northbridge *nb = शून्य;
	काष्ठा threshold_bank *b = शून्य;
	स्थिर अक्षर *name = get_name(bank, शून्य);
	पूर्णांक err = 0;

	अगर (!dev)
		वापस -ENODEV;

	अगर (is_shared_bank(bank)) अणु
		nb = node_to_amd_nb(topology_die_id(cpu));

		/* threshold descriptor alपढ़ोy initialized on this node? */
		अगर (nb && nb->bank4) अणु
			/* yes, use it */
			b = nb->bank4;
			err = kobject_add(b->kobj, &dev->kobj, name);
			अगर (err)
				जाओ out;

			bp[bank] = b;
			refcount_inc(&b->cpus);

			err = __threshold_add_blocks(b);

			जाओ out;
		पूर्ण
	पूर्ण

	b = kzalloc(माप(काष्ठा threshold_bank), GFP_KERNEL);
	अगर (!b) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Associate the bank with the per-CPU MCE device */
	b->kobj = kobject_create_and_add(name, &dev->kobj);
	अगर (!b->kobj) अणु
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (is_shared_bank(bank)) अणु
		b->shared = 1;
		refcount_set(&b->cpus, 1);

		/* nb is alपढ़ोy initialized, see above */
		अगर (nb) अणु
			WARN_ON(nb->bank4);
			nb->bank4 = b;
		पूर्ण
	पूर्ण

	err = allocate_threshold_blocks(cpu, b, bank, 0, msr_ops.misc(bank));
	अगर (err)
		जाओ out_kobj;

	bp[bank] = b;
	वापस 0;

out_kobj:
	kobject_put(b->kobj);
out_मुक्त:
	kमुक्त(b);
out:
	वापस err;
पूर्ण

अटल व्योम threshold_block_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(to_block(kobj));
पूर्ण

अटल व्योम deallocate_threshold_blocks(काष्ठा threshold_bank *bank)
अणु
	काष्ठा threshold_block *pos, *पंचांगp;

	list_क्रम_each_entry_safe(pos, पंचांगp, &bank->blocks->miscj, miscj) अणु
		list_del(&pos->miscj);
		kobject_put(&pos->kobj);
	पूर्ण

	kobject_put(&bank->blocks->kobj);
पूर्ण

अटल व्योम __threshold_हटाओ_blocks(काष्ठा threshold_bank *b)
अणु
	काष्ठा threshold_block *pos = शून्य;
	काष्ठा threshold_block *पंचांगp = शून्य;

	kobject_del(b->kobj);

	list_क्रम_each_entry_safe(pos, पंचांगp, &b->blocks->miscj, miscj)
		kobject_del(&pos->kobj);
पूर्ण

अटल व्योम threshold_हटाओ_bank(काष्ठा threshold_bank *bank)
अणु
	काष्ठा amd_northbridge *nb;

	अगर (!bank->blocks)
		जाओ out_मुक्त;

	अगर (!bank->shared)
		जाओ out_dealloc;

	अगर (!refcount_dec_and_test(&bank->cpus)) अणु
		__threshold_हटाओ_blocks(bank);
		वापस;
	पूर्ण अन्यथा अणु
		/*
		 * The last CPU on this node using the shared bank is going
		 * away, हटाओ that bank now.
		 */
		nb = node_to_amd_nb(topology_die_id(smp_processor_id()));
		nb->bank4 = शून्य;
	पूर्ण

out_dealloc:
	deallocate_threshold_blocks(bank);

out_मुक्त:
	kobject_put(bank->kobj);
	kमुक्त(bank);
पूर्ण

पूर्णांक mce_threshold_हटाओ_device(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा threshold_bank **bp = this_cpu_पढ़ो(threshold_banks);
	अचिन्हित पूर्णांक bank, numbanks = this_cpu_पढ़ो(mce_num_banks);

	अगर (!bp)
		वापस 0;

	/*
	 * Clear the poपूर्णांकer beक्रमe cleaning up, so that the पूर्णांकerrupt won't
	 * touch anything of this.
	 */
	this_cpu_ग_लिखो(threshold_banks, शून्य);

	क्रम (bank = 0; bank < numbanks; bank++) अणु
		अगर (bp[bank]) अणु
			threshold_हटाओ_bank(bp[bank]);
			bp[bank] = शून्य;
		पूर्ण
	पूर्ण
	kमुक्त(bp);
	वापस 0;
पूर्ण

/**
 * mce_threshold_create_device - Create the per-CPU MCE threshold device
 * @cpu:	The plugged in CPU
 *
 * Create directories and files क्रम all valid threshold banks.
 *
 * This is invoked from the CPU hotplug callback which was installed in
 * mcheck_init_device(). The invocation happens in context of the hotplug
 * thपढ़ो running on @cpu.  The callback is invoked on all CPUs which are
 * online when the callback is installed or during a real hotplug event.
 */
पूर्णांक mce_threshold_create_device(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक numbanks, bank;
	काष्ठा threshold_bank **bp;
	पूर्णांक err;

	अगर (!mce_flags.amd_threshold)
		वापस 0;

	bp = this_cpu_पढ़ो(threshold_banks);
	अगर (bp)
		वापस 0;

	numbanks = this_cpu_पढ़ो(mce_num_banks);
	bp = kसुस्मृति(numbanks, माप(*bp), GFP_KERNEL);
	अगर (!bp)
		वापस -ENOMEM;

	क्रम (bank = 0; bank < numbanks; ++bank) अणु
		अगर (!(this_cpu_पढ़ो(bank_map) & (1 << bank)))
			जारी;
		err = threshold_create_bank(bp, cpu, bank);
		अगर (err)
			जाओ out_err;
	पूर्ण
	this_cpu_ग_लिखो(threshold_banks, bp);

	अगर (thresholding_irq_en)
		mce_threshold_vector = amd_threshold_पूर्णांकerrupt;
	वापस 0;
out_err:
	mce_threshold_हटाओ_device(cpu);
	वापस err;
पूर्ण
