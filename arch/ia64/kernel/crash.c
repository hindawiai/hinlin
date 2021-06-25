<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/ia64/kernel/crash.c
 *
 * Architecture specअगरic (ia64) functions क्रम kexec based crash dumps.
 *
 * Created by: Khalid Aziz <khalid.aziz@hp.com>
 * Copyright (C) 2005 Hewlett-Packard Development Company, L.P.
 * Copyright (C) 2005 Intel Corp	Zou Nan hai <nanhai.zou@पूर्णांकel.com>
 *
 */
#समावेश <linux/smp.h>
#समावेश <linux/delay.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/memblock.h>
#समावेश <linux/kexec.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/init.h>
#समावेश <linux/kdebug.h>

#समावेश <यंत्र/mca.h>

पूर्णांक kdump_status[NR_CPUS];
अटल atomic_t kdump_cpu_frozen;
atomic_t kdump_in_progress;
अटल पूर्णांक kdump_मुक्तze_monarch;
अटल पूर्णांक kdump_on_init = 1;
अटल पूर्णांक kdump_on_fatal_mca = 1;

बाह्य व्योम ia64_dump_cpu_regs(व्योम *);

अटल DEFINE_PER_CPU(काष्ठा elf_prstatus, elf_prstatus);

व्योम
crash_save_this_cpu(व्योम)
अणु
	व्योम *buf;
	अचिन्हित दीर्घ cfm, sof, sol;

	पूर्णांक cpu = smp_processor_id();
	काष्ठा elf_prstatus *prstatus = &per_cpu(elf_prstatus, cpu);

	elf_greg_t *dst = (elf_greg_t *)&(prstatus->pr_reg);
	स_रखो(prstatus, 0, माप(*prstatus));
	prstatus->common.pr_pid = current->pid;

	ia64_dump_cpu_regs(dst);
	cfm = dst[43];
	sol = (cfm >> 7) & 0x7f;
	sof = cfm & 0x7f;
	dst[46] = (अचिन्हित दीर्घ)ia64_rse_skip_regs((अचिन्हित दीर्घ *)dst[46],
			sof - sol);

	buf = (u64 *) per_cpu_ptr(crash_notes, cpu);
	अगर (!buf)
		वापस;
	buf = append_elf_note(buf, KEXEC_CORE_NOTE_NAME, NT_PRSTATUS, prstatus,
			माप(*prstatus));
	final_note(buf);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक
kdump_रुको_cpu_मुक्तze(व्योम)
अणु
	पूर्णांक cpu_num = num_online_cpus() - 1;
	पूर्णांक समयout = 1000;
	जबतक(समयout-- > 0) अणु
		अगर (atomic_पढ़ो(&kdump_cpu_frozen) == cpu_num)
			वापस 0;
		udelay(1000);
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर

व्योम
machine_crash_shutकरोwn(काष्ठा pt_regs *pt)
अणु
	/* This function is only called after the प्रणाली
	 * has paniced or is otherwise in a critical state.
	 * The minimum amount of code to allow a kexec'd kernel
	 * to run successfully needs to happen here.
	 *
	 * In practice this means shooting करोwn the other cpus in
	 * an SMP प्रणाली.
	 */
	kexec_disable_iosapic();
#अगर_घोषित CONFIG_SMP
	/*
	 * If kdump_on_init is set and an INIT is निश्चितed here, kdump will
	 * be started again via INIT monarch.
	 */
	local_irq_disable();
	ia64_set_psr_mc();	/* mask MCA/INIT */
	अगर (atomic_inc_वापस(&kdump_in_progress) != 1)
		unw_init_running(kdump_cpu_मुक्तze, शून्य);

	/*
	 * Now this cpu is पढ़ोy क्रम kdump.
	 * Stop all others by IPI or INIT.  They could receive INIT from
	 * outside and might be INIT monarch, but only thing they have to
	 * करो is falling पूर्णांकo kdump_cpu_मुक्तze().
	 *
	 * If an INIT is निश्चितed here:
	 * - All receivers might be slaves, since some of cpus could alपढ़ोy
	 *   be frozen and INIT might be masked on monarch.  In this हाल,
	 *   all slaves will be frozen soon since kdump_in_progress will let
	 *   them पूर्णांकo DIE_INIT_SLAVE_LEAVE.
	 * - One might be a monarch, but INIT rendezvous will fail since
	 *   at least this cpu alपढ़ोy have INIT masked so it never join
	 *   to the rendezvous.  In this हाल, all slaves and monarch will
	 *   be frozen soon with no रुको since the INIT rendezvous is skipped
	 *   by kdump_in_progress.
	 */
	kdump_smp_send_stop();
	/* not all cpu response to IPI, send INIT to मुक्तze them */
	अगर (kdump_रुको_cpu_मुक्तze()) अणु
		kdump_smp_send_init();
		/* रुको again, करोn't go ahead अगर possible */
		kdump_रुको_cpu_मुक्तze();
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम
machine_kdump_on_init(व्योम)
अणु
	crash_save_vmcoreinfo();
	local_irq_disable();
	kexec_disable_iosapic();
	machine_kexec(ia64_kimage);
पूर्ण

व्योम
kdump_cpu_मुक्तze(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	पूर्णांक cpuid;

	local_irq_disable();
	cpuid = smp_processor_id();
	crash_save_this_cpu();
	current->thपढ़ो.ksp = (__u64)info->sw - 16;

	ia64_set_psr_mc();	/* mask MCA/INIT and stop reentrance */

	atomic_inc(&kdump_cpu_frozen);
	kdump_status[cpuid] = 1;
	mb();
	क्रम (;;)
		cpu_relax();
पूर्ण

अटल पूर्णांक
kdump_init_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा ia64_mca_notअगरy_die *nd;
	काष्ठा die_args *args = data;

	अगर (atomic_पढ़ो(&kdump_in_progress)) अणु
		चयन (val) अणु
		हाल DIE_INIT_MONARCH_LEAVE:
			अगर (!kdump_मुक्तze_monarch)
				अवरोध;
			fallthrough;
		हाल DIE_INIT_SLAVE_LEAVE:
		हाल DIE_INIT_MONARCH_ENTER:
		हाल DIE_MCA_RENDZVOUS_LEAVE:
			unw_init_running(kdump_cpu_मुक्तze, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!kdump_on_init && !kdump_on_fatal_mca)
		वापस NOTIFY_DONE;

	अगर (!ia64_kimage) अणु
		अगर (val == DIE_INIT_MONARCH_LEAVE)
			ia64_mca_prपूर्णांकk(KERN_NOTICE
					"%s: kdump not configured\n",
					__func__);
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (val != DIE_INIT_MONARCH_LEAVE &&
	    val != DIE_INIT_MONARCH_PROCESS &&
	    val != DIE_MCA_MONARCH_LEAVE)
		वापस NOTIFY_DONE;

	nd = (काष्ठा ia64_mca_notअगरy_die *)args->err;

	चयन (val) अणु
	हाल DIE_INIT_MONARCH_PROCESS:
		/* Reason code 1 means machine check rendezvous*/
		अगर (kdump_on_init && (nd->sos->rv_rc != 1)) अणु
			अगर (atomic_inc_वापस(&kdump_in_progress) != 1)
				kdump_मुक्तze_monarch = 1;
		पूर्ण
		अवरोध;
	हाल DIE_INIT_MONARCH_LEAVE:
		/* Reason code 1 means machine check rendezvous*/
		अगर (kdump_on_init && (nd->sos->rv_rc != 1))
			machine_kdump_on_init();
		अवरोध;
	हाल DIE_MCA_MONARCH_LEAVE:
		/* *(nd->data) indicate अगर MCA is recoverable */
		अगर (kdump_on_fatal_mca && !(*(nd->data))) अणु
			अगर (atomic_inc_वापस(&kdump_in_progress) == 1)
				machine_kdump_on_init();
			/* We got fatal MCA जबतक kdump!? No way!! */
		पूर्ण
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table kdump_ctl_table[] = अणु
	अणु
		.procname = "kdump_on_init",
		.data = &kdump_on_init,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname = "kdump_on_fatal_mca",
		.data = &kdump_on_fatal_mca,
		.maxlen = माप(पूर्णांक),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table sys_table[] = अणु
	अणु
	  .procname = "kernel",
	  .mode = 0555,
	  .child = kdump_ctl_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक
machine_crash_setup(व्योम)
अणु
	/* be notअगरied beक्रमe शेष_monarch_init_process */
	अटल काष्ठा notअगरier_block kdump_init_notअगरier_nb = अणु
		.notअगरier_call = kdump_init_notअगरier,
		.priority = 1,
	पूर्ण;
	पूर्णांक ret;
	अगर((ret = रेजिस्टर_die_notअगरier(&kdump_init_notअगरier_nb)) != 0)
		वापस ret;
#अगर_घोषित CONFIG_SYSCTL
	रेजिस्टर_sysctl_table(sys_table);
#पूर्ण_अगर
	वापस 0;
पूर्ण

__initcall(machine_crash_setup);

