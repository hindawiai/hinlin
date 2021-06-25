<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Pseuकरो NMI support on sparc64 प्रणालीs.
 *
 * Copyright (C) 2009 David S. Miller <davem@davemloft.net>
 *
 * The NMI watchकरोg support and infraकाष्ठाure is based almost
 * entirely upon the x86 NMI support code.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/nmi.h>
#समावेश <linux/export.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/pcr.h>

#समावेश "kstack.h"

/* We करोn't have a real NMI on sparc64, but we can fake one
 * up using profiling counter overflow पूर्णांकerrupts and पूर्णांकerrupt
 * levels.
 *
 * The profile overflow पूर्णांकerrupts at level 15, so we use
 * level 14 as our IRQ off level.
 */

अटल पूर्णांक panic_on_समयout;

/* nmi_active:
 * >0: the NMI watchकरोg is active, but can be disabled
 * <0: the NMI watchकरोg has not been set up, and cannot be enabled
 *  0: the NMI watchकरोg is disabled, but can be enabled
 */
atomic_t nmi_active = ATOMIC_INIT(0);		/* oprofile uses this */
EXPORT_SYMBOL(nmi_active);
अटल पूर्णांक nmi_init_करोne;
अटल अचिन्हित पूर्णांक nmi_hz = HZ;
अटल DEFINE_PER_CPU(लघु, wd_enabled);
अटल पूर्णांक endflag __initdata;

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, last_irq_sum);
अटल DEFINE_PER_CPU(दीर्घ, alert_counter);
अटल DEFINE_PER_CPU(पूर्णांक, nmi_touch);

व्योम arch_touch_nmi_watchकरोg(व्योम)
अणु
	अगर (atomic_पढ़ो(&nmi_active)) अणु
		पूर्णांक cpu;

		क्रम_each_present_cpu(cpu) अणु
			अगर (per_cpu(nmi_touch, cpu) != 1)
				per_cpu(nmi_touch, cpu) = 1;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(arch_touch_nmi_watchकरोg);

अटल व्योम die_nmi(स्थिर अक्षर *str, काष्ठा pt_regs *regs, पूर्णांक करो_panic)
अणु
	पूर्णांक this_cpu = smp_processor_id();

	अगर (notअगरy_die(DIE_NMIWATCHDOG, str, regs, 0,
		       pt_regs_trap_type(regs), संक_विघ्न) == NOTIFY_STOP)
		वापस;

	अगर (करो_panic || panic_on_oops)
		panic("Watchdog detected hard LOCKUP on cpu %d", this_cpu);
	अन्यथा
		WARN(1, "Watchdog detected hard LOCKUP on cpu %d", this_cpu);
पूर्ण

notrace __kprobes व्योम perfctr_irq(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक sum, touched = 0;
	व्योम *orig_sp;

	clear_softपूर्णांक(1 << irq);

	local_cpu_data().__nmi_count++;

	nmi_enter();

	orig_sp = set_hardirq_stack();

	अगर (notअगरy_die(DIE_NMI, "nmi", regs, 0,
		       pt_regs_trap_type(regs), संक_विघ्न) == NOTIFY_STOP)
		touched = 1;
	अन्यथा
		pcr_ops->ग_लिखो_pcr(0, pcr_ops->pcr_nmi_disable);

	sum = local_cpu_data().irq0_irqs;
	अगर (__this_cpu_पढ़ो(nmi_touch)) अणु
		__this_cpu_ग_लिखो(nmi_touch, 0);
		touched = 1;
	पूर्ण
	अगर (!touched && __this_cpu_पढ़ो(last_irq_sum) == sum) अणु
		__this_cpu_inc(alert_counter);
		अगर (__this_cpu_पढ़ो(alert_counter) == 30 * nmi_hz)
			die_nmi("BUG: NMI Watchdog detected LOCKUP",
				regs, panic_on_समयout);
	पूर्ण अन्यथा अणु
		__this_cpu_ग_लिखो(last_irq_sum, sum);
		__this_cpu_ग_लिखो(alert_counter, 0);
	पूर्ण
	अगर (__this_cpu_पढ़ो(wd_enabled)) अणु
		pcr_ops->ग_लिखो_pic(0, pcr_ops->nmi_picl_value(nmi_hz));
		pcr_ops->ग_लिखो_pcr(0, pcr_ops->pcr_nmi_enable);
	पूर्ण

	restore_hardirq_stack(orig_sp);

	nmi_निकास();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_nmi_count(पूर्णांक cpu)
अणु
	वापस cpu_data(cpu).__nmi_count;
पूर्ण

अटल __init व्योम nmi_cpu_busy(व्योम *data)
अणु
	जबतक (endflag == 0)
		mb();
पूर्ण

अटल व्योम report_broken_nmi(पूर्णांक cpu, पूर्णांक *prev_nmi_count)
अणु
	prपूर्णांकk(KERN_CONT "\n");

	prपूर्णांकk(KERN_WARNING
		"WARNING: CPU#%d: NMI appears to be stuck (%d->%d)!\n",
			cpu, prev_nmi_count[cpu], get_nmi_count(cpu));

	prपूर्णांकk(KERN_WARNING
		"Please report this to bugzilla.kernel.org,\n");
	prपूर्णांकk(KERN_WARNING
		"and attach the output of the 'dmesg' command.\n");

	per_cpu(wd_enabled, cpu) = 0;
	atomic_dec(&nmi_active);
पूर्ण

व्योम stop_nmi_watchकरोg(व्योम *unused)
अणु
	अगर (!__this_cpu_पढ़ो(wd_enabled))
		वापस;
	pcr_ops->ग_लिखो_pcr(0, pcr_ops->pcr_nmi_disable);
	__this_cpu_ग_लिखो(wd_enabled, 0);
	atomic_dec(&nmi_active);
पूर्ण

अटल पूर्णांक __init check_nmi_watchकरोg(व्योम)
अणु
	अचिन्हित पूर्णांक *prev_nmi_count;
	पूर्णांक cpu, err;

	अगर (!atomic_पढ़ो(&nmi_active))
		वापस 0;

	prev_nmi_count = kदो_स्मृति_array(nr_cpu_ids, माप(अचिन्हित पूर्णांक),
				       GFP_KERNEL);
	अगर (!prev_nmi_count) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Testing NMI watchdog ... ");

	smp_call_function(nmi_cpu_busy, (व्योम *)&endflag, 0);

	क्रम_each_possible_cpu(cpu)
		prev_nmi_count[cpu] = get_nmi_count(cpu);
	local_irq_enable();
	mdelay((20 * 1000) / nmi_hz); /* रुको 20 ticks */

	क्रम_each_online_cpu(cpu) अणु
		अगर (!per_cpu(wd_enabled, cpu))
			जारी;
		अगर (get_nmi_count(cpu) - prev_nmi_count[cpu] <= 5)
			report_broken_nmi(cpu, prev_nmi_count);
	पूर्ण
	endflag = 1;
	अगर (!atomic_पढ़ो(&nmi_active)) अणु
		kमुक्त(prev_nmi_count);
		atomic_set(&nmi_active, -1);
		err = -ENODEV;
		जाओ error;
	पूर्ण
	prपूर्णांकk("OK.\n");

	nmi_hz = 1;

	kमुक्त(prev_nmi_count);
	वापस 0;
error:
	on_each_cpu(stop_nmi_watchकरोg, शून्य, 1);
	वापस err;
पूर्ण

व्योम start_nmi_watchकरोg(व्योम *unused)
अणु
	अगर (__this_cpu_पढ़ो(wd_enabled))
		वापस;

	__this_cpu_ग_लिखो(wd_enabled, 1);
	atomic_inc(&nmi_active);

	pcr_ops->ग_लिखो_pcr(0, pcr_ops->pcr_nmi_disable);
	pcr_ops->ग_लिखो_pic(0, pcr_ops->nmi_picl_value(nmi_hz));

	pcr_ops->ग_लिखो_pcr(0, pcr_ops->pcr_nmi_enable);
पूर्ण

अटल व्योम nmi_adjust_hz_one(व्योम *unused)
अणु
	अगर (!__this_cpu_पढ़ो(wd_enabled))
		वापस;

	pcr_ops->ग_लिखो_pcr(0, pcr_ops->pcr_nmi_disable);
	pcr_ops->ग_लिखो_pic(0, pcr_ops->nmi_picl_value(nmi_hz));

	pcr_ops->ग_लिखो_pcr(0, pcr_ops->pcr_nmi_enable);
पूर्ण

व्योम nmi_adjust_hz(अचिन्हित पूर्णांक new_hz)
अणु
	nmi_hz = new_hz;
	on_each_cpu(nmi_adjust_hz_one, शून्य, 1);
पूर्ण
EXPORT_SYMBOL_GPL(nmi_adjust_hz);

अटल पूर्णांक nmi_shutकरोwn(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ cmd, व्योम *p)
अणु
	on_each_cpu(stop_nmi_watchकरोg, शून्य, 1);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block nmi_reboot_notअगरier = अणु
	.notअगरier_call = nmi_shutकरोwn,
पूर्ण;

पूर्णांक __init nmi_init(व्योम)
अणु
	पूर्णांक err;

	on_each_cpu(start_nmi_watchकरोg, शून्य, 1);

	err = check_nmi_watchकरोg();
	अगर (!err) अणु
		err = रेजिस्टर_reboot_notअगरier(&nmi_reboot_notअगरier);
		अगर (err) अणु
			on_each_cpu(stop_nmi_watchकरोg, शून्य, 1);
			atomic_set(&nmi_active, -1);
		पूर्ण
	पूर्ण

	nmi_init_करोne = 1;

	वापस err;
पूर्ण

अटल पूर्णांक __init setup_nmi_watchकरोg(अक्षर *str)
अणु
	अगर (!म_भेदन(str, "panic", 5))
		panic_on_समयout = 1;

	वापस 0;
पूर्ण
__setup("nmi_watchdog=", setup_nmi_watchकरोg);

/*
 * sparc specअगरic NMI watchकरोg enable function.
 * Enables watchकरोg अगर it is not enabled alपढ़ोy.
 */
पूर्णांक watchकरोg_nmi_enable(अचिन्हित पूर्णांक cpu)
अणु
	अगर (atomic_पढ़ो(&nmi_active) == -1) अणु
		pr_warn("NMI watchdog cannot be enabled or disabled\n");
		वापस -1;
	पूर्ण

	/*
	 * watchकरोg thपढ़ो could start even beक्रमe nmi_init is called.
	 * Just Return in that हाल. Let nmi_init finish the init
	 * process first.
	 */
	अगर (!nmi_init_करोne)
		वापस 0;

	smp_call_function_single(cpu, start_nmi_watchकरोg, शून्य, 1);

	वापस 0;
पूर्ण
/*
 * sparc specअगरic NMI watchकरोg disable function.
 * Disables watchकरोg अगर it is not disabled alपढ़ोy.
 */
व्योम watchकरोg_nmi_disable(अचिन्हित पूर्णांक cpu)
अणु
	अगर (atomic_पढ़ो(&nmi_active) == -1)
		pr_warn_once("NMI watchdog cannot be enabled or disabled\n");
	अन्यथा
		smp_call_function_single(cpu, stop_nmi_watchकरोg, शून्य, 1);
पूर्ण
