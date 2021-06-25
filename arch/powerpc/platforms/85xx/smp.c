<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Author: Andy Fleming <afleming@मुक्तscale.com>
 * 	   Kumar Gala <galak@kernel.crashing.org>
 *
 * Copyright 2006-2008, 2011-2012, 2015 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/kexec.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/cpu.h>
#समावेश <linux/fsl/guts.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/dbell.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/fsl_pm.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/mpic.h>
#समावेश "smp.h"

काष्ठा epapr_spin_table अणु
	u32	addr_h;
	u32	addr_l;
	u32	r3_h;
	u32	r3_l;
	u32	reserved;
	u32	pir;
पूर्ण;

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल u64 समयbase;
अटल पूर्णांक tb_req;
अटल पूर्णांक tb_valid;

अटल व्योम mpc85xx_give_समयbase(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	hard_irq_disable();

	जबतक (!tb_req)
		barrier();
	tb_req = 0;

	qoriq_pm_ops->मुक्तze_समय_base(true);
#अगर_घोषित CONFIG_PPC64
	/*
	 * e5500/e6500 have a workaround क्रम erratum A-006958 in place
	 * that will reपढ़ो the समयbase until TBL is non-zero.
	 * That would be a bad thing when the समयbase is frozen.
	 *
	 * Thus, we पढ़ो it manually, and instead of checking that
	 * TBL is non-zero, we ensure that TB करोes not change.  We करोn't
	 * करो that क्रम the मुख्य mftb implementation, because it requires
	 * a scratch रेजिस्टर
	 */
	अणु
		u64 prev;

		यंत्र अस्थिर("mfspr %0, %1" : "=r" (समयbase) :
			     "i" (SPRN_TBRL));

		करो अणु
			prev = समयbase;
			यंत्र अस्थिर("mfspr %0, %1" : "=r" (समयbase) :
				     "i" (SPRN_TBRL));
		पूर्ण जबतक (prev != समयbase);
	पूर्ण
#अन्यथा
	समयbase = get_tb();
#पूर्ण_अगर
	mb();
	tb_valid = 1;

	जबतक (tb_valid)
		barrier();

	qoriq_pm_ops->मुक्तze_समय_base(false);

	local_irq_restore(flags);
पूर्ण

अटल व्योम mpc85xx_take_समयbase(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	hard_irq_disable();

	tb_req = 1;
	जबतक (!tb_valid)
		barrier();

	set_tb(समयbase >> 32, समयbase & 0xffffffff);
	isync();
	tb_valid = 0;

	local_irq_restore(flags);
पूर्ण

अटल व्योम smp_85xx_cpu_offline_self(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	local_irq_disable();
	hard_irq_disable();
	/* mask all irqs to prevent cpu wakeup */
	qoriq_pm_ops->irq_mask(cpu);

	idle_task_निकास();

	mtspr(SPRN_TCR, 0);
	mtspr(SPRN_TSR, mfspr(SPRN_TSR));

	generic_set_cpu_dead(cpu);

	cur_cpu_spec->cpu_करोwn_flush();

	qoriq_pm_ops->cpu_die(cpu);

	जबतक (1)
		;
पूर्ण

अटल व्योम qoriq_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 500; i++) अणु
		अगर (is_cpu_dead(cpu)) अणु
#अगर_घोषित CONFIG_PPC64
			paca_ptrs[cpu]->cpu_start = 0;
#पूर्ण_अगर
			वापस;
		पूर्ण
		msleep(20);
	पूर्ण
	pr_err("CPU%d didn't die...\n", cpu);
पूर्ण
#पूर्ण_अगर

/*
 * To keep it compatible with old boot program which uses
 * cache-inhibit spin table, we need to flush the cache
 * beक्रमe accessing spin table to invalidate any staled data.
 * We also need to flush the cache after writing to spin
 * table to push data out.
 */
अटल अंतरभूत व्योम flush_spin_table(व्योम *spin_table)
अणु
	flush_dcache_range((uदीर्घ)spin_table,
		(uदीर्घ)spin_table + माप(काष्ठा epapr_spin_table));
पूर्ण

अटल अंतरभूत u32 पढ़ो_spin_table_addr_l(व्योम *spin_table)
अणु
	flush_dcache_range((uदीर्घ)spin_table,
		(uदीर्घ)spin_table + माप(काष्ठा epapr_spin_table));
	वापस in_be32(&((काष्ठा epapr_spin_table *)spin_table)->addr_l);
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल व्योम wake_hw_thपढ़ो(व्योम *info)
अणु
	व्योम fsl_secondary_thपढ़ो_init(व्योम);
	अचिन्हित दीर्घ inia;
	पूर्णांक cpu = *(स्थिर पूर्णांक *)info;

	inia = *(अचिन्हित दीर्घ *)fsl_secondary_thपढ़ो_init;
	book3e_start_thपढ़ो(cpu_thपढ़ो_in_core(cpu), inia);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक smp_85xx_start_cpu(पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;
	काष्ठा device_node *np;
	स्थिर u64 *cpu_rel_addr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ioremappable;
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	काष्ठा epapr_spin_table __iomem *spin_table;

	np = of_get_cpu_node(cpu, शून्य);
	cpu_rel_addr = of_get_property(np, "cpu-release-addr", शून्य);
	अगर (!cpu_rel_addr) अणु
		pr_err("No cpu-release-addr for cpu %d\n", cpu);
		वापस -ENOENT;
	पूर्ण

	/*
	 * A secondary core could be in a spinloop in the bootpage
	 * (0xfffff000), somewhere in highmem, or somewhere in lowmem.
	 * The bootpage and highmem can be accessed via ioremap(), but
	 * we need to directly access the spinloop अगर its in lowmem.
	 */
	ioremappable = *cpu_rel_addr > virt_to_phys(high_memory);

	/* Map the spin table */
	अगर (ioremappable)
		spin_table = ioremap_coherent(*cpu_rel_addr,
					      माप(काष्ठा epapr_spin_table));
	अन्यथा
		spin_table = phys_to_virt(*cpu_rel_addr);

	local_irq_save(flags);
	hard_irq_disable();

	अगर (qoriq_pm_ops)
		qoriq_pm_ops->cpu_up_prepare(cpu);

	/* अगर cpu is not spinning, reset it */
	अगर (पढ़ो_spin_table_addr_l(spin_table) != 1) अणु
		/*
		 * We करोn't set the BPTR रेजिस्टर here since it alपढ़ोy poपूर्णांकs
		 * to the boot page properly.
		 */
		mpic_reset_core(cpu);

		/*
		 * रुको until core is पढ़ोy...
		 * We need to invalidate the stale data, in हाल the boot
		 * loader uses a cache-inhibited spin table.
		 */
		अगर (!spin_event_समयout(
				पढ़ो_spin_table_addr_l(spin_table) == 1,
				10000, 100)) अणु
			pr_err("timeout waiting for cpu %d to reset\n",
				hw_cpu);
			ret = -EAGAIN;
			जाओ err;
		पूर्ण
	पूर्ण

	flush_spin_table(spin_table);
	out_be32(&spin_table->pir, hw_cpu);
#अगर_घोषित CONFIG_PPC64
	out_be64((u64 *)(&spin_table->addr_h),
		__pa(ppc_function_entry(generic_secondary_smp_init)));
#अन्यथा
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	/*
	 * We need also to ग_लिखो addr_h to spin table क्रम प्रणालीs
	 * in which their physical memory start address was configured
	 * to above 4G, otherwise the secondary core can not get
	 * correct entry to start from.
	 */
	out_be32(&spin_table->addr_h, __pa(__early_start) >> 32);
#पूर्ण_अगर
	out_be32(&spin_table->addr_l, __pa(__early_start));
#पूर्ण_अगर
	flush_spin_table(spin_table);
err:
	local_irq_restore(flags);

	अगर (ioremappable)
		iounmap(spin_table);

	वापस ret;
पूर्ण

अटल पूर्णांक smp_85xx_kick_cpu(पूर्णांक nr)
अणु
	पूर्णांक ret = 0;
#अगर_घोषित CONFIG_PPC64
	पूर्णांक primary = nr;
#पूर्ण_अगर

	WARN_ON(nr < 0 || nr >= num_possible_cpus());

	pr_debug("kick CPU #%d\n", nr);

#अगर_घोषित CONFIG_PPC64
	अगर (thपढ़ोs_per_core == 2) अणु
		अगर (WARN_ON_ONCE(!cpu_has_feature(CPU_FTR_SMT)))
			वापस -ENOENT;

		booting_thपढ़ो_hwid = cpu_thपढ़ो_in_core(nr);
		primary = cpu_first_thपढ़ो_sibling(nr);

		अगर (qoriq_pm_ops)
			qoriq_pm_ops->cpu_up_prepare(nr);

		/*
		 * If either thपढ़ो in the core is online, use it to start
		 * the other.
		 */
		अगर (cpu_online(primary)) अणु
			smp_call_function_single(primary,
					wake_hw_thपढ़ो, &nr, 1);
			जाओ करोne;
		पूर्ण अन्यथा अगर (cpu_online(primary + 1)) अणु
			smp_call_function_single(primary + 1,
					wake_hw_thपढ़ो, &nr, 1);
			जाओ करोne;
		पूर्ण

		/*
		 * If getting here, it means both thपढ़ोs in the core are
		 * offline. So start the primary thपढ़ो, then it will start
		 * the thपढ़ो specअगरied in booting_thपढ़ो_hwid, the one
		 * corresponding to nr.
		 */

	पूर्ण अन्यथा अगर (thपढ़ोs_per_core == 1) अणु
		/*
		 * If one core has only one thपढ़ो, set booting_thपढ़ो_hwid to
		 * an invalid value.
		 */
		booting_thपढ़ो_hwid = INVALID_THREAD_HWID;

	पूर्ण अन्यथा अगर (thपढ़ोs_per_core > 2) अणु
		pr_err("Do not support more than 2 threads per CPU.");
		वापस -EINVAL;
	पूर्ण

	ret = smp_85xx_start_cpu(primary);
	अगर (ret)
		वापस ret;

करोne:
	paca_ptrs[nr]->cpu_start = 1;
	generic_set_cpu_up(nr);

	वापस ret;
#अन्यथा
	ret = smp_85xx_start_cpu(nr);
	अगर (ret)
		वापस ret;

	generic_set_cpu_up(nr);

	वापस ret;
#पूर्ण_अगर
पूर्ण

काष्ठा smp_ops_t smp_85xx_ops = अणु
	.cause_nmi_ipi = शून्य,
	.kick_cpu = smp_85xx_kick_cpu,
	.cpu_bootable = smp_generic_cpu_bootable,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable	= generic_cpu_disable,
	.cpu_die	= generic_cpu_die,
#पूर्ण_अगर
#अगर defined(CONFIG_KEXEC_CORE) && !defined(CONFIG_PPC64)
	.give_समयbase	= smp_generic_give_समयbase,
	.take_समयbase	= smp_generic_take_समयbase,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_KEXEC_CORE
#अगर_घोषित CONFIG_PPC32
atomic_t kexec_करोwn_cpus = ATOMIC_INIT(0);

व्योम mpc85xx_smp_kexec_cpu_करोwn(पूर्णांक crash_shutकरोwn, पूर्णांक secondary)
अणु
	local_irq_disable();

	अगर (secondary) अणु
		cur_cpu_spec->cpu_करोwn_flush();
		atomic_inc(&kexec_करोwn_cpus);
		/* loop क्रमever */
		जबतक (1);
	पूर्ण
पूर्ण

अटल व्योम mpc85xx_smp_kexec_करोwn(व्योम *arg)
अणु
	अगर (ppc_md.kexec_cpu_करोwn)
		ppc_md.kexec_cpu_करोwn(0,1);
पूर्ण
#अन्यथा
व्योम mpc85xx_smp_kexec_cpu_करोwn(पूर्णांक crash_shutकरोwn, पूर्णांक secondary)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक sibling = cpu_last_thपढ़ो_sibling(cpu);
	bool notअगरied = false;
	पूर्णांक disable_cpu;
	पूर्णांक disable_thपढ़ोbit = 0;
	दीर्घ start = mftb();
	दीर्घ now;

	local_irq_disable();
	hard_irq_disable();
	mpic_tearकरोwn_this_cpu(secondary);

	अगर (cpu == crashing_cpu && cpu_thपढ़ो_in_core(cpu) != 0) अणु
		/*
		 * We enter the crash kernel on whatever cpu crashed,
		 * even अगर it's a secondary thread.  If that's the हाल,
		 * disable the corresponding primary thपढ़ो.
		 */
		disable_thपढ़ोbit = 1;
		disable_cpu = cpu_first_thपढ़ो_sibling(cpu);
	पूर्ण अन्यथा अगर (sibling != crashing_cpu &&
		   cpu_thपढ़ो_in_core(cpu) == 0 &&
		   cpu_thपढ़ो_in_core(sibling) != 0) अणु
		disable_thपढ़ोbit = 2;
		disable_cpu = sibling;
	पूर्ण

	अगर (disable_thपढ़ोbit) अणु
		जबतक (paca_ptrs[disable_cpu]->kexec_state < KEXEC_STATE_REAL_MODE) अणु
			barrier();
			now = mftb();
			अगर (!notअगरied && now - start > 1000000) अणु
				pr_info("%s/%d: waiting for cpu %d to enter KEXEC_STATE_REAL_MODE (%d)\n",
					__func__, smp_processor_id(),
					disable_cpu,
					paca_ptrs[disable_cpu]->kexec_state);
				notअगरied = true;
			पूर्ण
		पूर्ण

		अगर (notअगरied) अणु
			pr_info("%s: cpu %d done waiting\n",
				__func__, disable_cpu);
		पूर्ण

		mtspr(SPRN_TENC, disable_thपढ़ोbit);
		जबतक (mfspr(SPRN_TENSR) & disable_thपढ़ोbit)
			cpu_relax();
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम mpc85xx_smp_machine_kexec(काष्ठा kimage *image)
अणु
#अगर_घोषित CONFIG_PPC32
	पूर्णांक समयout = पूर्णांक_उच्च;
	पूर्णांक i, num_cpus = num_present_cpus();

	अगर (image->type == KEXEC_TYPE_DEFAULT)
		smp_call_function(mpc85xx_smp_kexec_करोwn, शून्य, 0);

	जबतक ( (atomic_पढ़ो(&kexec_करोwn_cpus) != (num_cpus - 1)) &&
		( समयout > 0 ) )
	अणु
		समयout--;
	पूर्ण

	अगर ( !समयout )
		prपूर्णांकk(KERN_ERR "Unable to bring down secondary cpu(s)");

	क्रम_each_online_cpu(i)
	अणु
		अगर ( i == smp_processor_id() ) जारी;
		mpic_reset_core(i);
	पूर्ण
#पूर्ण_अगर

	शेष_machine_kexec(image);
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

अटल व्योम smp_85xx_setup_cpu(पूर्णांक cpu_nr)
अणु
	mpic_setup_this_cpu();
पूर्ण

व्योम __init mpc85xx_smp_init(व्योम)
अणु
	काष्ठा device_node *np;


	np = of_find_node_by_type(शून्य, "open-pic");
	अगर (np) अणु
		smp_85xx_ops.probe = smp_mpic_probe;
		smp_85xx_ops.setup_cpu = smp_85xx_setup_cpu;
		smp_85xx_ops.message_pass = smp_mpic_message_pass;
	पूर्ण अन्यथा
		smp_85xx_ops.setup_cpu = शून्य;

	अगर (cpu_has_feature(CPU_FTR_DBELL)) अणु
		/*
		 * If left शून्य, .message_pass शेषs to
		 * smp_muxed_ipi_message_pass
		 */
		smp_85xx_ops.message_pass = शून्य;
		smp_85xx_ops.cause_ipi = करोorbell_global_ipi;
		smp_85xx_ops.probe = शून्य;
	पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
#अगर_घोषित CONFIG_FSL_CORENET_RCPM
	fsl_rcpm_init();
#पूर्ण_अगर

#अगर_घोषित CONFIG_FSL_PMC
	mpc85xx_setup_pmc();
#पूर्ण_अगर
	अगर (qoriq_pm_ops) अणु
		smp_85xx_ops.give_समयbase = mpc85xx_give_समयbase;
		smp_85xx_ops.take_समयbase = mpc85xx_take_समयbase;
		smp_85xx_ops.cpu_offline_self = smp_85xx_cpu_offline_self;
		smp_85xx_ops.cpu_die = qoriq_cpu_समाप्त;
	पूर्ण
#पूर्ण_अगर
	smp_ops = &smp_85xx_ops;

#अगर_घोषित CONFIG_KEXEC_CORE
	ppc_md.kexec_cpu_करोwn = mpc85xx_smp_kexec_cpu_करोwn;
	ppc_md.machine_kexec = mpc85xx_smp_machine_kexec;
#पूर्ण_अगर
पूर्ण
