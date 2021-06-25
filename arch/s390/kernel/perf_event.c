<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance event support क्रम s390x
 *
 *  Copyright IBM Corp. 2012, 2013
 *  Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */
#घोषणा KMSG_COMPONENT	"perf"
#घोषणा pr_fmt(fmt)	KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/percpu.h>
#समावेश <linux/export.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/cpu_mf.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/unwind.h>

अटल काष्ठा kvm_s390_sie_block *sie_block(काष्ठा pt_regs *regs)
अणु
	काष्ठा stack_frame *stack = (काष्ठा stack_frame *) regs->gprs[15];

	अगर (!stack)
		वापस शून्य;

	वापस (काष्ठा kvm_s390_sie_block *) stack->empty1[0];
पूर्ण

अटल bool is_in_guest(काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs))
		वापस false;
#अगर IS_ENABLED(CONFIG_KVM)
	वापस inकाष्ठाion_poपूर्णांकer(regs) == (अचिन्हित दीर्घ) &sie_निकास;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ guest_is_user_mode(काष्ठा pt_regs *regs)
अणु
	वापस sie_block(regs)->gpsw.mask & PSW_MASK_PSTATE;
पूर्ण

अटल अचिन्हित दीर्घ inकाष्ठाion_poपूर्णांकer_guest(काष्ठा pt_regs *regs)
अणु
	वापस sie_block(regs)->gpsw.addr;
पूर्ण

अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस is_in_guest(regs) ? inकाष्ठाion_poपूर्णांकer_guest(regs)
				 : inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

अटल अचिन्हित दीर्घ perf_misc_guest_flags(काष्ठा pt_regs *regs)
अणु
	वापस guest_is_user_mode(regs) ? PERF_RECORD_MISC_GUEST_USER
					: PERF_RECORD_MISC_GUEST_KERNEL;
पूर्ण

अटल अचिन्हित दीर्घ perf_misc_flags_sf(काष्ठा pt_regs *regs)
अणु
	काष्ठा perf_sf_sde_regs *sde_regs;
	अचिन्हित दीर्घ flags;

	sde_regs = (काष्ठा perf_sf_sde_regs *) &regs->पूर्णांक_parm_दीर्घ;
	अगर (sde_regs->in_guest)
		flags = user_mode(regs) ? PERF_RECORD_MISC_GUEST_USER
					: PERF_RECORD_MISC_GUEST_KERNEL;
	अन्यथा
		flags = user_mode(regs) ? PERF_RECORD_MISC_USER
					: PERF_RECORD_MISC_KERNEL;
	वापस flags;
पूर्ण

अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs)
अणु
	/* Check अगर the cpum_sf PMU has created the pt_regs काष्ठाure.
	 * In this हाल, perf misc flags can be easily extracted.  Otherwise,
	 * करो regular checks on the pt_regs content.
	 */
	अगर (regs->पूर्णांक_code == 0x1407 && regs->पूर्णांक_parm == CPU_MF_INT_SF_PRA)
		अगर (!regs->gprs[15])
			वापस perf_misc_flags_sf(regs);

	अगर (is_in_guest(regs))
		वापस perf_misc_guest_flags(regs);

	वापस user_mode(regs) ? PERF_RECORD_MISC_USER
			       : PERF_RECORD_MISC_KERNEL;
पूर्ण

अटल व्योम prपूर्णांक_debug_cf(व्योम)
अणु
	काष्ठा cpumf_ctr_info cf_info;
	पूर्णांक cpu = smp_processor_id();

	स_रखो(&cf_info, 0, माप(cf_info));
	अगर (!qctri(&cf_info))
		pr_info("CPU[%i] CPUM_CF: ver=%u.%u A=%04x E=%04x C=%04x\n",
			cpu, cf_info.cfvn, cf_info.csvn,
			cf_info.auth_ctl, cf_info.enable_ctl, cf_info.act_ctl);
पूर्ण

अटल व्योम prपूर्णांक_debug_sf(व्योम)
अणु
	काष्ठा hws_qsi_info_block si;
	पूर्णांक cpu = smp_processor_id();

	स_रखो(&si, 0, माप(si));
	अगर (qsi(&si))
		वापस;

	pr_info("CPU[%i] CPUM_SF: basic=%i diag=%i min=%lu max=%lu cpu_speed=%u\n",
		cpu, si.as, si.ad, si.min_sampl_rate, si.max_sampl_rate,
		si.cpu_speed);

	अगर (si.as)
		pr_info("CPU[%i] CPUM_SF: Basic-sampling: a=%i e=%i c=%i"
			" bsdes=%i tear=%016lx dear=%016lx\n", cpu,
			si.as, si.es, si.cs, si.bsdes, si.tear, si.dear);
	अगर (si.ad)
		pr_info("CPU[%i] CPUM_SF: Diagnostic-sampling: a=%i e=%i c=%i"
			" dsdes=%i tear=%016lx dear=%016lx\n", cpu,
			si.ad, si.ed, si.cd, si.dsdes, si.tear, si.dear);
पूर्ण

व्योम perf_event_prपूर्णांक_debug(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (cpum_cf_avail())
		prपूर्णांक_debug_cf();
	अगर (cpum_sf_avail())
		prपूर्णांक_debug_sf();
	local_irq_restore(flags);
पूर्ण

/* Service level infraकाष्ठाure */
अटल व्योम sl_prपूर्णांक_counter(काष्ठा seq_file *m)
अणु
	काष्ठा cpumf_ctr_info ci;

	स_रखो(&ci, 0, माप(ci));
	अगर (qctri(&ci))
		वापस;

	seq_म_लिखो(m, "CPU-MF: Counter facility: version=%u.%u "
		   "authorization=%04x\n", ci.cfvn, ci.csvn, ci.auth_ctl);
पूर्ण

अटल व्योम sl_prपूर्णांक_sampling(काष्ठा seq_file *m)
अणु
	काष्ठा hws_qsi_info_block si;

	स_रखो(&si, 0, माप(si));
	अगर (qsi(&si))
		वापस;

	अगर (!si.as && !si.ad)
		वापस;

	seq_म_लिखो(m, "CPU-MF: Sampling facility: min_rate=%lu max_rate=%lu"
		   " cpu_speed=%u\n", si.min_sampl_rate, si.max_sampl_rate,
		   si.cpu_speed);
	अगर (si.as)
		seq_म_लिखो(m, "CPU-MF: Sampling facility: mode=basic"
			   " sample_size=%u\n", si.bsdes);
	अगर (si.ad)
		seq_म_लिखो(m, "CPU-MF: Sampling facility: mode=diagnostic"
			   " sample_size=%u\n", si.dsdes);
पूर्ण

अटल व्योम service_level_perf_prपूर्णांक(काष्ठा seq_file *m,
				     काष्ठा service_level *sl)
अणु
	अगर (cpum_cf_avail())
		sl_prपूर्णांक_counter(m);
	अगर (cpum_sf_avail())
		sl_prपूर्णांक_sampling(m);
पूर्ण

अटल काष्ठा service_level service_level_perf = अणु
	.seq_prपूर्णांक = service_level_perf_prपूर्णांक,
पूर्ण;

अटल पूर्णांक __init service_level_perf_रेजिस्टर(व्योम)
अणु
	वापस रेजिस्टर_service_level(&service_level_perf);
पूर्ण
arch_initcall(service_level_perf_रेजिस्टर);

व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
			   काष्ठा pt_regs *regs)
अणु
	काष्ठा unwind_state state;
	अचिन्हित दीर्घ addr;

	unwind_क्रम_each_frame(&state, current, regs, 0) अणु
		addr = unwind_get_वापस_address(&state);
		अगर (!addr || perf_callchain_store(entry, addr))
			वापस;
	पूर्ण
पूर्ण

/* Perf definitions क्रम PMU event attributes in sysfs */
sमाप_प्रकार cpumf_events_sysfs_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr);
	वापस प्र_लिखो(page, "event=0x%04llx\n", pmu_attr->id);
पूर्ण
