<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Machine check injection support.
 * Copyright 2008 Intel Corporation.
 *
 * Authors:
 * Andi Kleen
 * Ying Huang
 *
 * The AMD part (from mce_amd_inj.c): a simple MCE injection facility
 * क्रम testing dअगरferent aspects of the RAS code. This driver should be
 * built as module so that it can be loaded on production kernels क्रम
 * testing purposes.
 *
 * Copyright (c) 2010-17:  Borislav Petkov <bp@alien8.de>
 *			   Advanced Micro Devices Inc.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/amd_nb.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/irq_vectors.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/smp.h>

#समावेश "internal.h"

/*
 * Collect all the MCi_XXX settings
 */
अटल काष्ठा mce i_mce;
अटल काष्ठा dentry *dfs_inj;

#घोषणा MAX_FLAG_OPT_SIZE	4
#घोषणा NBCFG			0x44

क्रमागत injection_type अणु
	SW_INJ = 0,	/* SW injection, simply decode the error */
	HW_INJ,		/* Trigger a #MC */
	DFR_INT_INJ,    /* Trigger Deferred error पूर्णांकerrupt */
	THR_INT_INJ,    /* Trigger threshold पूर्णांकerrupt */
	N_INJ_TYPES,
पूर्ण;

अटल स्थिर अक्षर * स्थिर flags_options[] = अणु
	[SW_INJ] = "sw",
	[HW_INJ] = "hw",
	[DFR_INT_INJ] = "df",
	[THR_INT_INJ] = "th",
	शून्य
पूर्ण;

/* Set शेष injection to SW_INJ */
अटल क्रमागत injection_type inj_type = SW_INJ;

#घोषणा MCE_INJECT_SET(reg)						\
अटल पूर्णांक inj_##reg##_set(व्योम *data, u64 val)				\
अणु									\
	काष्ठा mce *m = (काष्ठा mce *)data;				\
									\
	m->reg = val;							\
	वापस 0;							\
पूर्ण

MCE_INJECT_SET(status);
MCE_INJECT_SET(misc);
MCE_INJECT_SET(addr);
MCE_INJECT_SET(synd);
MCE_INJECT_SET(ipid);

#घोषणा MCE_INJECT_GET(reg)						\
अटल पूर्णांक inj_##reg##_get(व्योम *data, u64 *val)			\
अणु									\
	काष्ठा mce *m = (काष्ठा mce *)data;				\
									\
	*val = m->reg;							\
	वापस 0;							\
पूर्ण

MCE_INJECT_GET(status);
MCE_INJECT_GET(misc);
MCE_INJECT_GET(addr);
MCE_INJECT_GET(synd);
MCE_INJECT_GET(ipid);

DEFINE_SIMPLE_ATTRIBUTE(status_fops, inj_status_get, inj_status_set, "%llx\n");
DEFINE_SIMPLE_ATTRIBUTE(misc_fops, inj_misc_get, inj_misc_set, "%llx\n");
DEFINE_SIMPLE_ATTRIBUTE(addr_fops, inj_addr_get, inj_addr_set, "%llx\n");
DEFINE_SIMPLE_ATTRIBUTE(synd_fops, inj_synd_get, inj_synd_set, "%llx\n");
DEFINE_SIMPLE_ATTRIBUTE(ipid_fops, inj_ipid_get, inj_ipid_set, "%llx\n");

अटल व्योम setup_inj_काष्ठा(काष्ठा mce *m)
अणु
	स_रखो(m, 0, माप(काष्ठा mce));

	m->cpuvenकरोr = boot_cpu_data.x86_venकरोr;
	m->समय	     = kसमय_get_real_seconds();
	m->cpuid     = cpuid_eax(1);
	m->microcode = boot_cpu_data.microcode;
पूर्ण

/* Update fake mce रेजिस्टरs on current CPU. */
अटल व्योम inject_mce(काष्ठा mce *m)
अणु
	काष्ठा mce *i = &per_cpu(injecपंचांग, m->extcpu);

	/* Make sure no one पढ़ोs partially written injecपंचांग */
	i->finished = 0;
	mb();
	m->finished = 0;
	/* First set the fields after finished */
	i->extcpu = m->extcpu;
	mb();
	/* Now ग_लिखो record in order, finished last (except above) */
	स_नकल(i, m, माप(काष्ठा mce));
	/* Finally activate it */
	mb();
	i->finished = 1;
पूर्ण

अटल व्योम उठाओ_poll(काष्ठा mce *m)
अणु
	अचिन्हित दीर्घ flags;
	mce_banks_t b;

	स_रखो(&b, 0xff, माप(mce_banks_t));
	local_irq_save(flags);
	machine_check_poll(0, &b);
	local_irq_restore(flags);
	m->finished = 0;
पूर्ण

अटल व्योम उठाओ_exception(काष्ठा mce *m, काष्ठा pt_regs *pregs)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित दीर्घ flags;

	अगर (!pregs) अणु
		स_रखो(&regs, 0, माप(काष्ठा pt_regs));
		regs.ip = m->ip;
		regs.cs = m->cs;
		pregs = &regs;
	पूर्ण
	/* करो_machine_check() expects पूर्णांकerrupts disabled -- at least */
	local_irq_save(flags);
	करो_machine_check(pregs);
	local_irq_restore(flags);
	m->finished = 0;
पूर्ण

अटल cpumask_var_t mce_inject_cpumask;
अटल DEFINE_MUTEX(mce_inject_mutex);

अटल पूर्णांक mce_उठाओ_notअगरy(अचिन्हित पूर्णांक cmd, काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा mce *m = this_cpu_ptr(&injecपंचांग);
	अगर (!cpumask_test_cpu(cpu, mce_inject_cpumask))
		वापस NMI_DONE;
	cpumask_clear_cpu(cpu, mce_inject_cpumask);
	अगर (m->inject_flags & MCJ_EXCEPTION)
		उठाओ_exception(m, regs);
	अन्यथा अगर (m->status)
		उठाओ_poll(m);
	वापस NMI_HANDLED;
पूर्ण

अटल व्योम mce_irq_ipi(व्योम *info)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा mce *m = this_cpu_ptr(&injecपंचांग);

	अगर (cpumask_test_cpu(cpu, mce_inject_cpumask) &&
			m->inject_flags & MCJ_EXCEPTION) अणु
		cpumask_clear_cpu(cpu, mce_inject_cpumask);
		उठाओ_exception(m, शून्य);
	पूर्ण
पूर्ण

/* Inject mce on current CPU */
अटल पूर्णांक उठाओ_local(व्योम)
अणु
	काष्ठा mce *m = this_cpu_ptr(&injecपंचांग);
	पूर्णांक context = MCJ_CTX(m->inject_flags);
	पूर्णांक ret = 0;
	पूर्णांक cpu = m->extcpu;

	अगर (m->inject_flags & MCJ_EXCEPTION) अणु
		pr_info("Triggering MCE exception on CPU %d\n", cpu);
		चयन (context) अणु
		हाल MCJ_CTX_IRQ:
			/*
			 * Could करो more to fake पूर्णांकerrupts like
			 * calling irq_enter, but the necessary
			 * machinery isn't exported currently.
			 */
			fallthrough;
		हाल MCJ_CTX_PROCESS:
			उठाओ_exception(m, शून्य);
			अवरोध;
		शेष:
			pr_info("Invalid MCE context\n");
			ret = -EINVAL;
		पूर्ण
		pr_info("MCE exception done on CPU %d\n", cpu);
	पूर्ण अन्यथा अगर (m->status) अणु
		pr_info("Starting machine check poll CPU %d\n", cpu);
		उठाओ_poll(m);
		mce_notअगरy_irq();
		pr_info("Machine check poll done on CPU %d\n", cpu);
	पूर्ण अन्यथा
		m->finished = 0;

	वापस ret;
पूर्ण

अटल व्योम __maybe_unused उठाओ_mce(काष्ठा mce *m)
अणु
	पूर्णांक context = MCJ_CTX(m->inject_flags);

	inject_mce(m);

	अगर (context == MCJ_CTX_RANDOM)
		वापस;

	अगर (m->inject_flags & (MCJ_IRQ_BROADCAST | MCJ_NMI_BROADCAST)) अणु
		अचिन्हित दीर्घ start;
		पूर्णांक cpu;

		get_online_cpus();
		cpumask_copy(mce_inject_cpumask, cpu_online_mask);
		cpumask_clear_cpu(get_cpu(), mce_inject_cpumask);
		क्रम_each_online_cpu(cpu) अणु
			काष्ठा mce *mcpu = &per_cpu(injecपंचांग, cpu);
			अगर (!mcpu->finished ||
			    MCJ_CTX(mcpu->inject_flags) != MCJ_CTX_RANDOM)
				cpumask_clear_cpu(cpu, mce_inject_cpumask);
		पूर्ण
		अगर (!cpumask_empty(mce_inject_cpumask)) अणु
			अगर (m->inject_flags & MCJ_IRQ_BROADCAST) अणु
				/*
				 * करोn't रुको because mce_irq_ipi is necessary
				 * to be sync with following उठाओ_local
				 */
				preempt_disable();
				smp_call_function_many(mce_inject_cpumask,
					mce_irq_ipi, शून्य, 0);
				preempt_enable();
			पूर्ण अन्यथा अगर (m->inject_flags & MCJ_NMI_BROADCAST)
				apic->send_IPI_mask(mce_inject_cpumask,
						NMI_VECTOR);
		पूर्ण
		start = jअगरfies;
		जबतक (!cpumask_empty(mce_inject_cpumask)) अणु
			अगर (!समय_beक्रमe(jअगरfies, start + 2*HZ)) अणु
				pr_err("Timeout waiting for mce inject %lx\n",
					*cpumask_bits(mce_inject_cpumask));
				अवरोध;
			पूर्ण
			cpu_relax();
		पूर्ण
		उठाओ_local();
		put_cpu();
		put_online_cpus();
	पूर्ण अन्यथा अणु
		preempt_disable();
		उठाओ_local();
		preempt_enable();
	पूर्ण
पूर्ण

अटल पूर्णांक mce_inject_उठाओ(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			    व्योम *data)
अणु
	काष्ठा mce *m = (काष्ठा mce *)data;

	अगर (!m)
		वापस NOTIFY_DONE;

	mutex_lock(&mce_inject_mutex);
	उठाओ_mce(m);
	mutex_unlock(&mce_inject_mutex);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block inject_nb = अणु
	.notअगरier_call  = mce_inject_उठाओ,
पूर्ण;

/*
 * Caller needs to be make sure this cpu करोesn't disappear
 * from under us, i.e.: get_cpu/put_cpu.
 */
अटल पूर्णांक toggle_hw_mce_inject(अचिन्हित पूर्णांक cpu, bool enable)
अणु
	u32 l, h;
	पूर्णांक err;

	err = rdmsr_on_cpu(cpu, MSR_K7_HWCR, &l, &h);
	अगर (err) अणु
		pr_err("%s: error reading HWCR\n", __func__);
		वापस err;
	पूर्ण

	enable ? (l |= BIT(18)) : (l &= ~BIT(18));

	err = wrmsr_on_cpu(cpu, MSR_K7_HWCR, l, h);
	अगर (err)
		pr_err("%s: error writing HWCR\n", __func__);

	वापस err;
पूर्ण

अटल पूर्णांक __set_inj(स्थिर अक्षर *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_INJ_TYPES; i++) अणु
		अगर (!म_भेदन(flags_options[i], buf, म_माप(flags_options[i]))) अणु
			inj_type = i;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार flags_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
			  माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[MAX_FLAG_OPT_SIZE];
	पूर्णांक n;

	n = प्र_लिखो(buf, "%s\n", flags_options[inj_type]);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, n);
पूर्ण

अटल sमाप_प्रकार flags_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			   माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[MAX_FLAG_OPT_SIZE], *__buf;
	पूर्णांक err;

	अगर (cnt > MAX_FLAG_OPT_SIZE)
		वापस -EINVAL;

	अगर (copy_from_user(&buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt - 1] = 0;

	/* strip whitespace */
	__buf = म_मालाip(buf);

	err = __set_inj(__buf);
	अगर (err) अणु
		pr_err("%s: Invalid flags value: %s\n", __func__, __buf);
		वापस err;
	पूर्ण

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations flags_fops = अणु
	.पढ़ो           = flags_पढ़ो,
	.ग_लिखो          = flags_ग_लिखो,
	.llseek         = generic_file_llseek,
पूर्ण;

/*
 * On which CPU to inject?
 */
MCE_INJECT_GET(extcpu);

अटल पूर्णांक inj_extcpu_set(व्योम *data, u64 val)
अणु
	काष्ठा mce *m = (काष्ठा mce *)data;

	अगर (val >= nr_cpu_ids || !cpu_online(val)) अणु
		pr_err("%s: Invalid CPU: %llu\n", __func__, val);
		वापस -EINVAL;
	पूर्ण
	m->extcpu = val;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(extcpu_fops, inj_extcpu_get, inj_extcpu_set, "%llu\n");

अटल व्योम trigger_mce(व्योम *info)
अणु
	यंत्र अस्थिर("int $18");
पूर्ण

अटल व्योम trigger_dfr_पूर्णांक(व्योम *info)
अणु
	यंत्र अस्थिर("int %0" :: "i" (DEFERRED_ERROR_VECTOR));
पूर्ण

अटल व्योम trigger_thr_पूर्णांक(व्योम *info)
अणु
	यंत्र अस्थिर("int %0" :: "i" (THRESHOLD_APIC_VECTOR));
पूर्ण

अटल u32 get_nbc_क्रम_node(पूर्णांक node_id)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;
	u32 cores_per_node;

	cores_per_node = (c->x86_max_cores * smp_num_siblings) / amd_get_nodes_per_socket();

	वापस cores_per_node * node_id;
पूर्ण

अटल व्योम toggle_nb_mca_mst_cpu(u16 nid)
अणु
	काष्ठा amd_northbridge *nb;
	काष्ठा pci_dev *F3;
	u32 val;
	पूर्णांक err;

	nb = node_to_amd_nb(nid);
	अगर (!nb)
		वापस;

	F3 = nb->misc;
	अगर (!F3)
		वापस;

	err = pci_पढ़ो_config_dword(F3, NBCFG, &val);
	अगर (err) अणु
		pr_err("%s: Error reading F%dx%03x.\n",
		       __func__, PCI_FUNC(F3->devfn), NBCFG);
		वापस;
	पूर्ण

	अगर (val & BIT(27))
		वापस;

	pr_err("%s: Set D18F3x44[NbMcaToMstCpuEn] which BIOS hasn't done.\n",
	       __func__);

	val |= BIT(27);
	err = pci_ग_लिखो_config_dword(F3, NBCFG, val);
	अगर (err)
		pr_err("%s: Error writing F%dx%03x.\n",
		       __func__, PCI_FUNC(F3->devfn), NBCFG);
पूर्ण

अटल व्योम prepare_msrs(व्योम *info)
अणु
	काष्ठा mce m = *(काष्ठा mce *)info;
	u8 b = m.bank;

	wrmsrl(MSR_IA32_MCG_STATUS, m.mcgstatus);

	अगर (boot_cpu_has(X86_FEATURE_SMCA)) अणु
		अगर (m.inject_flags == DFR_INT_INJ) अणु
			wrmsrl(MSR_AMD64_SMCA_MCx_DESTAT(b), m.status);
			wrmsrl(MSR_AMD64_SMCA_MCx_DEADDR(b), m.addr);
		पूर्ण अन्यथा अणु
			wrmsrl(MSR_AMD64_SMCA_MCx_STATUS(b), m.status);
			wrmsrl(MSR_AMD64_SMCA_MCx_ADDR(b), m.addr);
		पूर्ण

		wrmsrl(MSR_AMD64_SMCA_MCx_MISC(b), m.misc);
		wrmsrl(MSR_AMD64_SMCA_MCx_SYND(b), m.synd);
	पूर्ण अन्यथा अणु
		wrmsrl(MSR_IA32_MCx_STATUS(b), m.status);
		wrmsrl(MSR_IA32_MCx_ADDR(b), m.addr);
		wrmsrl(MSR_IA32_MCx_MISC(b), m.misc);
	पूर्ण
पूर्ण

अटल व्योम करो_inject(व्योम)
अणु
	u64 mcg_status = 0;
	अचिन्हित पूर्णांक cpu = i_mce.extcpu;
	u8 b = i_mce.bank;

	i_mce.tsc = rdtsc_ordered();

	अगर (i_mce.misc)
		i_mce.status |= MCI_STATUS_MISCV;

	अगर (i_mce.synd)
		i_mce.status |= MCI_STATUS_SYNDV;

	अगर (inj_type == SW_INJ) अणु
		mce_log(&i_mce);
		वापस;
	पूर्ण

	/* prep MCE global settings क्रम the injection */
	mcg_status = MCG_STATUS_MCIP | MCG_STATUS_EIPV;

	अगर (!(i_mce.status & MCI_STATUS_PCC))
		mcg_status |= MCG_STATUS_RIPV;

	/*
	 * Ensure necessary status bits क्रम deferred errors:
	 * - MCx_STATUS[Deferred]: make sure it is a deferred error
	 * - MCx_STATUS[UC] cleared: deferred errors are _not_ UC
	 */
	अगर (inj_type == DFR_INT_INJ) अणु
		i_mce.status |= MCI_STATUS_DEFERRED;
		i_mce.status &= ~MCI_STATUS_UC;
	पूर्ण

	/*
	 * For multi node CPUs, logging and reporting of bank 4 errors happens
	 * only on the node base core. Refer to D18F3x44[NbMcaToMstCpuEn] क्रम
	 * Fam10h and later BKDGs.
	 */
	अगर (boot_cpu_has(X86_FEATURE_AMD_DCM) &&
	    b == 4 &&
	    boot_cpu_data.x86 < 0x17) अणु
		toggle_nb_mca_mst_cpu(topology_die_id(cpu));
		cpu = get_nbc_क्रम_node(topology_die_id(cpu));
	पूर्ण

	get_online_cpus();
	अगर (!cpu_online(cpu))
		जाओ err;

	toggle_hw_mce_inject(cpu, true);

	i_mce.mcgstatus = mcg_status;
	i_mce.inject_flags = inj_type;
	smp_call_function_single(cpu, prepare_msrs, &i_mce, 0);

	toggle_hw_mce_inject(cpu, false);

	चयन (inj_type) अणु
	हाल DFR_INT_INJ:
		smp_call_function_single(cpu, trigger_dfr_पूर्णांक, शून्य, 0);
		अवरोध;
	हाल THR_INT_INJ:
		smp_call_function_single(cpu, trigger_thr_पूर्णांक, शून्य, 0);
		अवरोध;
	शेष:
		smp_call_function_single(cpu, trigger_mce, शून्य, 0);
	पूर्ण

err:
	put_online_cpus();

पूर्ण

/*
 * This denotes पूर्णांकo which bank we're injecting and triggers
 * the injection, at the same समय.
 */
अटल पूर्णांक inj_bank_set(व्योम *data, u64 val)
अणु
	काष्ठा mce *m = (काष्ठा mce *)data;
	u8 n_banks;
	u64 cap;

	/* Get bank count on target CPU so we can handle non-unअगरorm values. */
	rdmsrl_on_cpu(m->extcpu, MSR_IA32_MCG_CAP, &cap);
	n_banks = cap & MCG_BANKCNT_MASK;

	अगर (val >= n_banks) अणु
		pr_err("MCA bank %llu non-existent on CPU%d\n", val, m->extcpu);
		वापस -EINVAL;
	पूर्ण

	m->bank = val;
	करो_inject();

	/* Reset injection काष्ठा */
	setup_inj_काष्ठा(&i_mce);

	वापस 0;
पूर्ण

MCE_INJECT_GET(bank);

DEFINE_SIMPLE_ATTRIBUTE(bank_fops, inj_bank_get, inj_bank_set, "%llu\n");

अटल स्थिर अक्षर पढ़ोme_msg[] =
"Description of the files and their usages:\n"
"\n"
"Note1: i refers to the bank number below.\n"
"Note2: See respective BKDGs for the exact bit definitions of the files below\n"
"as they mirror the hardware registers.\n"
"\n"
"status:\t Set MCi_STATUS: the bits in that MSR control the error type and\n"
"\t attributes of the error which caused the MCE.\n"
"\n"
"misc:\t Set MCi_MISC: provide auxiliary info about the error. It is mostly\n"
"\t used for error thresholding purposes and its validity is indicated by\n"
"\t MCi_STATUS[MiscV].\n"
"\n"
"synd:\t Set MCi_SYND: provide syndrome info about the error. Only valid on\n"
"\t Scalable MCA systems, and its validity is indicated by MCi_STATUS[SyndV].\n"
"\n"
"addr:\t Error address value to be written to MCi_ADDR. Log address information\n"
"\t associated with the error.\n"
"\n"
"cpu:\t The CPU to inject the error on.\n"
"\n"
"bank:\t Specify the bank you want to inject the error into: the number of\n"
"\t banks in a processor varies and is family/model-specific, therefore, the\n"
"\t supplied value is sanity-checked. Setting the bank value also triggers the\n"
"\t injection.\n"
"\n"
"flags:\t Injection type to be performed. Writing to this file will trigger a\n"
"\t real machine check, an APIC interrupt or invoke the error decoder routines\n"
"\t for AMD processors.\n"
"\n"
"\t Allowed error injection types:\n"
"\t  - \"sw\": Software error injection. Decode error to a human-readable \n"
"\t    format only. Safe to use.\n"
"\t  - \"hw\": Hardware error injection. Causes the #MC exception handler to \n"
"\t    handle the error. Be warned: might cause system panic if MCi_STATUS[PCC] \n"
"\t    is set. Therefore, consider setting (debugfs_mountpoint)/mce/fake_panic \n"
"\t    before injecting.\n"
"\t  - \"df\": Trigger APIC interrupt for Deferred error. Causes deferred \n"
"\t    error APIC interrupt handler to handle the error if the feature is \n"
"\t    is present in hardware. \n"
"\t  - \"th\": Trigger APIC interrupt for Threshold errors. Causes threshold \n"
"\t    APIC interrupt handler to handle the error. \n"
"\n"
"ipid:\t IPID (AMD-specific)\n"
"\n";

अटल sमाप_प्रकार
inj_पढ़ोme_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		       माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos,
					पढ़ोme_msg, म_माप(पढ़ोme_msg));
पूर्ण

अटल स्थिर काष्ठा file_operations पढ़ोme_fops = अणु
	.पढ़ो		= inj_पढ़ोme_पढ़ो,
पूर्ण;

अटल काष्ठा dfs_node अणु
	अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
	umode_t perm;
पूर्ण dfs_fls[] = अणु
	अणु .name = "status",	.fops = &status_fops, .perm = S_IRUSR | S_IWUSR पूर्ण,
	अणु .name = "misc",	.fops = &misc_fops,   .perm = S_IRUSR | S_IWUSR पूर्ण,
	अणु .name = "addr",	.fops = &addr_fops,   .perm = S_IRUSR | S_IWUSR पूर्ण,
	अणु .name = "synd",	.fops = &synd_fops,   .perm = S_IRUSR | S_IWUSR पूर्ण,
	अणु .name = "ipid",	.fops = &ipid_fops,   .perm = S_IRUSR | S_IWUSR पूर्ण,
	अणु .name = "bank",	.fops = &bank_fops,   .perm = S_IRUSR | S_IWUSR पूर्ण,
	अणु .name = "flags",	.fops = &flags_fops,  .perm = S_IRUSR | S_IWUSR पूर्ण,
	अणु .name = "cpu",	.fops = &extcpu_fops, .perm = S_IRUSR | S_IWUSR पूर्ण,
	अणु .name = "README",	.fops = &पढ़ोme_fops, .perm = S_IRUSR | S_IRGRP | S_IROTH पूर्ण,
पूर्ण;

अटल व्योम __init debugfs_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	dfs_inj = debugfs_create_dir("mce-inject", शून्य);

	क्रम (i = 0; i < ARRAY_SIZE(dfs_fls); i++)
		debugfs_create_file(dfs_fls[i].name, dfs_fls[i].perm, dfs_inj,
				    &i_mce, dfs_fls[i].fops);
पूर्ण

अटल पूर्णांक __init inject_init(व्योम)
अणु
	अगर (!alloc_cpumask_var(&mce_inject_cpumask, GFP_KERNEL))
		वापस -ENOMEM;

	debugfs_init();

	रेजिस्टर_nmi_handler(NMI_LOCAL, mce_उठाओ_notअगरy, 0, "mce_notify");
	mce_रेजिस्टर_injector_chain(&inject_nb);

	setup_inj_काष्ठा(&i_mce);

	pr_info("Machine check injector initialized\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास inject_निकास(व्योम)
अणु

	mce_unरेजिस्टर_injector_chain(&inject_nb);
	unरेजिस्टर_nmi_handler(NMI_LOCAL, "mce_notify");

	debugfs_हटाओ_recursive(dfs_inj);
	dfs_inj = शून्य;

	स_रखो(&dfs_fls, 0, माप(dfs_fls));

	मुक्त_cpumask_var(mce_inject_cpumask);
पूर्ण

module_init(inject_init);
module_निकास(inject_निकास);
MODULE_LICENSE("GPL");
