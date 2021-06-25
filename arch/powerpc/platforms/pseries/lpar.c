<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pSeries_lpar.c
 * Copyright (C) 2001 Todd Inglett, IBM Corporation
 *
 * pSeries LPAR support.
 */

/* Enables debugging of low-level hash table routines - careful! */
#अघोषित DEBUG
#घोषणा pr_fmt(fmt) "lpar: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/console.h>
#समावेश <linux/export.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/delay.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/dtl.h>

#समावेश "pseries.h"

/* Flag bits क्रम H_BULK_REMOVE */
#घोषणा HBR_REQUEST	0x4000000000000000UL
#घोषणा HBR_RESPONSE	0x8000000000000000UL
#घोषणा HBR_END		0xc000000000000000UL
#घोषणा HBR_AVPN	0x0200000000000000UL
#घोषणा HBR_ANDCOND	0x0100000000000000UL


/* in hvCall.S */
EXPORT_SYMBOL(plpar_hcall);
EXPORT_SYMBOL(plpar_hcall9);
EXPORT_SYMBOL(plpar_hcall_norets);

/*
 * H_BLOCK_REMOVE supported block size क्रम this page size in segment who's base
 * page size is that page size.
 *
 * The first index is the segment base page size, the second one is the actual
 * page size.
 */
अटल पूर्णांक hblkrm_size[MMU_PAGE_COUNT][MMU_PAGE_COUNT] __ro_after_init;

/*
 * Due to the involved complनिकासy, and that the current hypervisor is only
 * वापसing this value or 0, we are limiting the support of the H_BLOCK_REMOVE
 * buffer size to 8 size block.
 */
#घोषणा HBLKRM_SUPPORTED_BLOCK_SIZE 8

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
अटल u8 dtl_mask = DTL_LOG_PREEMPT;
#अन्यथा
अटल u8 dtl_mask;
#पूर्ण_अगर

व्योम alloc_dtl_buffers(अचिन्हित दीर्घ *समय_limit)
अणु
	पूर्णांक cpu;
	काष्ठा paca_काष्ठा *pp;
	काष्ठा dtl_entry *dtl;

	क्रम_each_possible_cpu(cpu) अणु
		pp = paca_ptrs[cpu];
		अगर (pp->dispatch_log)
			जारी;
		dtl = kmem_cache_alloc(dtl_cache, GFP_KERNEL);
		अगर (!dtl) अणु
			pr_warn("Failed to allocate dispatch trace log for cpu %d\n",
				cpu);
#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
			pr_warn("Stolen time statistics will be unreliable\n");
#पूर्ण_अगर
			अवरोध;
		पूर्ण

		pp->dtl_ridx = 0;
		pp->dispatch_log = dtl;
		pp->dispatch_log_end = dtl + N_DISPATCH_LOG;
		pp->dtl_curr = dtl;

		अगर (समय_limit && समय_after(jअगरfies, *समय_limit)) अणु
			cond_resched();
			*समय_limit = jअगरfies + HZ;
		पूर्ण
	पूर्ण
पूर्ण

व्योम रेजिस्टर_dtl_buffer(पूर्णांक cpu)
अणु
	दीर्घ ret;
	काष्ठा paca_काष्ठा *pp;
	काष्ठा dtl_entry *dtl;
	पूर्णांक hwcpu = get_hard_smp_processor_id(cpu);

	pp = paca_ptrs[cpu];
	dtl = pp->dispatch_log;
	अगर (dtl && dtl_mask) अणु
		pp->dtl_ridx = 0;
		pp->dtl_curr = dtl;
		lppaca_of(cpu).dtl_idx = 0;

		/* hypervisor पढ़ोs buffer length from this field */
		dtl->enqueue_to_dispatch_समय = cpu_to_be32(DISPATCH_LOG_BYTES);
		ret = रेजिस्टर_dtl(hwcpu, __pa(dtl));
		अगर (ret)
			pr_err("WARNING: DTL registration of cpu %d (hw %d) failed with %ld\n",
			       cpu, hwcpu, ret);

		lppaca_of(cpu).dtl_enable_mask = dtl_mask;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC_SPLPAR
काष्ठा dtl_worker अणु
	काष्ठा delayed_work work;
	पूर्णांक cpu;
पूर्ण;

काष्ठा vcpu_dispatch_data अणु
	पूर्णांक last_disp_cpu;

	पूर्णांक total_disp;

	पूर्णांक same_cpu_disp;
	पूर्णांक same_chip_disp;
	पूर्णांक dअगरf_chip_disp;
	पूर्णांक far_chip_disp;

	पूर्णांक numa_home_disp;
	पूर्णांक numa_remote_disp;
	पूर्णांक numa_far_disp;
पूर्ण;

/*
 * This represents the number of cpus in the hypervisor. Since there is no
 * architected way to discover the number of processors in the host, we
 * provision क्रम dealing with NR_CPUS. This is currently 2048 by शेष, and
 * is sufficient क्रम our purposes. This will need to be tweaked अगर
 * CONFIG_NR_CPUS is changed.
 */
#घोषणा NR_CPUS_H	NR_CPUS

DEFINE_RWLOCK(dtl_access_lock);
अटल DEFINE_PER_CPU(काष्ठा vcpu_dispatch_data, vcpu_disp_data);
अटल DEFINE_PER_CPU(u64, dtl_entry_ridx);
अटल DEFINE_PER_CPU(काष्ठा dtl_worker, dtl_workers);
अटल क्रमागत cpuhp_state dtl_worker_state;
अटल DEFINE_MUTEX(dtl_enable_mutex);
अटल पूर्णांक vcpudispatch_stats_on __पढ़ो_mostly;
अटल पूर्णांक vcpudispatch_stats_freq = 50;
अटल __be32 *vcpu_associativity, *pcpu_associativity;


अटल व्योम मुक्त_dtl_buffers(अचिन्हित दीर्घ *समय_limit)
अणु
#अगर_अघोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	पूर्णांक cpu;
	काष्ठा paca_काष्ठा *pp;

	क्रम_each_possible_cpu(cpu) अणु
		pp = paca_ptrs[cpu];
		अगर (!pp->dispatch_log)
			जारी;
		kmem_cache_मुक्त(dtl_cache, pp->dispatch_log);
		pp->dtl_ridx = 0;
		pp->dispatch_log = 0;
		pp->dispatch_log_end = 0;
		pp->dtl_curr = 0;

		अगर (समय_limit && समय_after(jअगरfies, *समय_limit)) अणु
			cond_resched();
			*समय_limit = jअगरfies + HZ;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक init_cpu_associativity(व्योम)
अणु
	vcpu_associativity = kसुस्मृति(num_possible_cpus() / thपढ़ोs_per_core,
			VPHN_ASSOC_बफ_मानE * माप(__be32), GFP_KERNEL);
	pcpu_associativity = kसुस्मृति(NR_CPUS_H / thपढ़ोs_per_core,
			VPHN_ASSOC_बफ_मानE * माप(__be32), GFP_KERNEL);

	अगर (!vcpu_associativity || !pcpu_associativity) अणु
		pr_err("error allocating memory for associativity information\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम destroy_cpu_associativity(व्योम)
अणु
	kमुक्त(vcpu_associativity);
	kमुक्त(pcpu_associativity);
	vcpu_associativity = pcpu_associativity = 0;
पूर्ण

अटल __be32 *__get_cpu_associativity(पूर्णांक cpu, __be32 *cpu_assoc, पूर्णांक flag)
अणु
	__be32 *assoc;
	पूर्णांक rc = 0;

	assoc = &cpu_assoc[(पूर्णांक)(cpu / thपढ़ोs_per_core) * VPHN_ASSOC_बफ_मानE];
	अगर (!assoc[0]) अणु
		rc = hcall_vphn(cpu, flag, &assoc[0]);
		अगर (rc)
			वापस शून्य;
	पूर्ण

	वापस assoc;
पूर्ण

अटल __be32 *get_pcpu_associativity(पूर्णांक cpu)
अणु
	वापस __get_cpu_associativity(cpu, pcpu_associativity, VPHN_FLAG_PCPU);
पूर्ण

अटल __be32 *get_vcpu_associativity(पूर्णांक cpu)
अणु
	वापस __get_cpu_associativity(cpu, vcpu_associativity, VPHN_FLAG_VCPU);
पूर्ण

अटल पूर्णांक cpu_relative_dispatch_distance(पूर्णांक last_disp_cpu, पूर्णांक cur_disp_cpu)
अणु
	__be32 *last_disp_cpu_assoc, *cur_disp_cpu_assoc;

	अगर (last_disp_cpu >= NR_CPUS_H || cur_disp_cpu >= NR_CPUS_H)
		वापस -EINVAL;

	last_disp_cpu_assoc = get_pcpu_associativity(last_disp_cpu);
	cur_disp_cpu_assoc = get_pcpu_associativity(cur_disp_cpu);

	अगर (!last_disp_cpu_assoc || !cur_disp_cpu_assoc)
		वापस -EIO;

	वापस cpu_distance(last_disp_cpu_assoc, cur_disp_cpu_assoc);
पूर्ण

अटल पूर्णांक cpu_home_node_dispatch_distance(पूर्णांक disp_cpu)
अणु
	__be32 *disp_cpu_assoc, *vcpu_assoc;
	पूर्णांक vcpu_id = smp_processor_id();

	अगर (disp_cpu >= NR_CPUS_H) अणु
		pr_debug_ratelimited("vcpu dispatch cpu %d > %d\n",
						disp_cpu, NR_CPUS_H);
		वापस -EINVAL;
	पूर्ण

	disp_cpu_assoc = get_pcpu_associativity(disp_cpu);
	vcpu_assoc = get_vcpu_associativity(vcpu_id);

	अगर (!disp_cpu_assoc || !vcpu_assoc)
		वापस -EIO;

	वापस cpu_distance(disp_cpu_assoc, vcpu_assoc);
पूर्ण

अटल व्योम update_vcpu_disp_stat(पूर्णांक disp_cpu)
अणु
	काष्ठा vcpu_dispatch_data *disp;
	पूर्णांक distance;

	disp = this_cpu_ptr(&vcpu_disp_data);
	अगर (disp->last_disp_cpu == -1) अणु
		disp->last_disp_cpu = disp_cpu;
		वापस;
	पूर्ण

	disp->total_disp++;

	अगर (disp->last_disp_cpu == disp_cpu ||
		(cpu_first_thपढ़ो_sibling(disp->last_disp_cpu) ==
					cpu_first_thपढ़ो_sibling(disp_cpu)))
		disp->same_cpu_disp++;
	अन्यथा अणु
		distance = cpu_relative_dispatch_distance(disp->last_disp_cpu,
								disp_cpu);
		अगर (distance < 0)
			pr_debug_ratelimited("vcpudispatch_stats: cpu %d: error determining associativity\n",
					smp_processor_id());
		अन्यथा अणु
			चयन (distance) अणु
			हाल 0:
				disp->same_chip_disp++;
				अवरोध;
			हाल 1:
				disp->dअगरf_chip_disp++;
				अवरोध;
			हाल 2:
				disp->far_chip_disp++;
				अवरोध;
			शेष:
				pr_debug_ratelimited("vcpudispatch_stats: cpu %d (%d -> %d): unexpected relative dispatch distance %d\n",
						 smp_processor_id(),
						 disp->last_disp_cpu,
						 disp_cpu,
						 distance);
			पूर्ण
		पूर्ण
	पूर्ण

	distance = cpu_home_node_dispatch_distance(disp_cpu);
	अगर (distance < 0)
		pr_debug_ratelimited("vcpudispatch_stats: cpu %d: error determining associativity\n",
				smp_processor_id());
	अन्यथा अणु
		चयन (distance) अणु
		हाल 0:
			disp->numa_home_disp++;
			अवरोध;
		हाल 1:
			disp->numa_remote_disp++;
			अवरोध;
		हाल 2:
			disp->numa_far_disp++;
			अवरोध;
		शेष:
			pr_debug_ratelimited("vcpudispatch_stats: cpu %d on %d: unexpected numa dispatch distance %d\n",
						 smp_processor_id(),
						 disp_cpu,
						 distance);
		पूर्ण
	पूर्ण

	disp->last_disp_cpu = disp_cpu;
पूर्ण

अटल व्योम process_dtl_buffer(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dtl_entry dtle;
	u64 i = __this_cpu_पढ़ो(dtl_entry_ridx);
	काष्ठा dtl_entry *dtl = local_paca->dispatch_log + (i % N_DISPATCH_LOG);
	काष्ठा dtl_entry *dtl_end = local_paca->dispatch_log_end;
	काष्ठा lppaca *vpa = local_paca->lppaca_ptr;
	काष्ठा dtl_worker *d = container_of(work, काष्ठा dtl_worker, work.work);

	अगर (!local_paca->dispatch_log)
		वापस;

	/* अगर we have been migrated away, we cancel ourself */
	अगर (d->cpu != smp_processor_id()) अणु
		pr_debug("vcpudispatch_stats: cpu %d worker migrated -- canceling worker\n",
						smp_processor_id());
		वापस;
	पूर्ण

	अगर (i == be64_to_cpu(vpa->dtl_idx))
		जाओ out;

	जबतक (i < be64_to_cpu(vpa->dtl_idx)) अणु
		dtle = *dtl;
		barrier();
		अगर (i + N_DISPATCH_LOG < be64_to_cpu(vpa->dtl_idx)) अणु
			/* buffer has overflowed */
			pr_debug_ratelimited("vcpudispatch_stats: cpu %d lost %lld DTL samples\n",
				d->cpu,
				be64_to_cpu(vpa->dtl_idx) - N_DISPATCH_LOG - i);
			i = be64_to_cpu(vpa->dtl_idx) - N_DISPATCH_LOG;
			dtl = local_paca->dispatch_log + (i % N_DISPATCH_LOG);
			जारी;
		पूर्ण
		update_vcpu_disp_stat(be16_to_cpu(dtle.processor_id));
		++i;
		++dtl;
		अगर (dtl == dtl_end)
			dtl = local_paca->dispatch_log;
	पूर्ण

	__this_cpu_ग_लिखो(dtl_entry_ridx, i);

out:
	schedule_delayed_work_on(d->cpu, to_delayed_work(work),
					HZ / vcpudispatch_stats_freq);
पूर्ण

अटल पूर्णांक dtl_worker_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा dtl_worker *d = &per_cpu(dtl_workers, cpu);

	स_रखो(d, 0, माप(*d));
	INIT_DELAYED_WORK(&d->work, process_dtl_buffer);
	d->cpu = cpu;

#अगर_अघोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	per_cpu(dtl_entry_ridx, cpu) = 0;
	रेजिस्टर_dtl_buffer(cpu);
#अन्यथा
	per_cpu(dtl_entry_ridx, cpu) = be64_to_cpu(lppaca_of(cpu).dtl_idx);
#पूर्ण_अगर

	schedule_delayed_work_on(cpu, &d->work, HZ / vcpudispatch_stats_freq);
	वापस 0;
पूर्ण

अटल पूर्णांक dtl_worker_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा dtl_worker *d = &per_cpu(dtl_workers, cpu);

	cancel_delayed_work_sync(&d->work);

#अगर_अघोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	unरेजिस्टर_dtl(get_hard_smp_processor_id(cpu));
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम set_global_dtl_mask(u8 mask)
अणु
	पूर्णांक cpu;

	dtl_mask = mask;
	क्रम_each_present_cpu(cpu)
		lppaca_of(cpu).dtl_enable_mask = dtl_mask;
पूर्ण

अटल व्योम reset_global_dtl_mask(व्योम)
अणु
	पूर्णांक cpu;

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	dtl_mask = DTL_LOG_PREEMPT;
#अन्यथा
	dtl_mask = 0;
#पूर्ण_अगर
	क्रम_each_present_cpu(cpu)
		lppaca_of(cpu).dtl_enable_mask = dtl_mask;
पूर्ण

अटल पूर्णांक dtl_worker_enable(अचिन्हित दीर्घ *समय_limit)
अणु
	पूर्णांक rc = 0, state;

	अगर (!ग_लिखो_trylock(&dtl_access_lock)) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	set_global_dtl_mask(DTL_LOG_ALL);

	/* Setup dtl buffers and रेजिस्टर those */
	alloc_dtl_buffers(समय_limit);

	state = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "powerpc/dtl:online",
					dtl_worker_online, dtl_worker_offline);
	अगर (state < 0) अणु
		pr_err("vcpudispatch_stats: unable to setup workqueue for DTL processing\n");
		मुक्त_dtl_buffers(समय_limit);
		reset_global_dtl_mask();
		ग_लिखो_unlock(&dtl_access_lock);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	dtl_worker_state = state;

out:
	वापस rc;
पूर्ण

अटल व्योम dtl_worker_disable(अचिन्हित दीर्घ *समय_limit)
अणु
	cpuhp_हटाओ_state(dtl_worker_state);
	मुक्त_dtl_buffers(समय_limit);
	reset_global_dtl_mask();
	ग_लिखो_unlock(&dtl_access_lock);
पूर्ण

अटल sमाप_प्रकार vcpudispatch_stats_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *p,
		माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ समय_limit = jअगरfies + HZ;
	काष्ठा vcpu_dispatch_data *disp;
	पूर्णांक rc, cmd, cpu;
	अक्षर buf[16];

	अगर (count > 15)
		वापस -EINVAL;

	अगर (copy_from_user(buf, p, count))
		वापस -EFAULT;

	buf[count] = 0;
	rc = kstrtoपूर्णांक(buf, 0, &cmd);
	अगर (rc || cmd < 0 || cmd > 1) अणु
		pr_err("vcpudispatch_stats: please use 0 to disable or 1 to enable dispatch statistics\n");
		वापस rc ? rc : -EINVAL;
	पूर्ण

	mutex_lock(&dtl_enable_mutex);

	अगर ((cmd == 0 && !vcpudispatch_stats_on) ||
			(cmd == 1 && vcpudispatch_stats_on))
		जाओ out;

	अगर (cmd) अणु
		rc = init_cpu_associativity();
		अगर (rc)
			जाओ out;

		क्रम_each_possible_cpu(cpu) अणु
			disp = per_cpu_ptr(&vcpu_disp_data, cpu);
			स_रखो(disp, 0, माप(*disp));
			disp->last_disp_cpu = -1;
		पूर्ण

		rc = dtl_worker_enable(&समय_limit);
		अगर (rc) अणु
			destroy_cpu_associativity();
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		dtl_worker_disable(&समय_limit);
		destroy_cpu_associativity();
	पूर्ण

	vcpudispatch_stats_on = cmd;

out:
	mutex_unlock(&dtl_enable_mutex);
	अगर (rc)
		वापस rc;
	वापस count;
पूर्ण

अटल पूर्णांक vcpudispatch_stats_display(काष्ठा seq_file *p, व्योम *v)
अणु
	पूर्णांक cpu;
	काष्ठा vcpu_dispatch_data *disp;

	अगर (!vcpudispatch_stats_on) अणु
		seq_माला_दो(p, "off\n");
		वापस 0;
	पूर्ण

	क्रम_each_online_cpu(cpu) अणु
		disp = per_cpu_ptr(&vcpu_disp_data, cpu);
		seq_म_लिखो(p, "cpu%d", cpu);
		seq_put_decimal_ull(p, " ", disp->total_disp);
		seq_put_decimal_ull(p, " ", disp->same_cpu_disp);
		seq_put_decimal_ull(p, " ", disp->same_chip_disp);
		seq_put_decimal_ull(p, " ", disp->dअगरf_chip_disp);
		seq_put_decimal_ull(p, " ", disp->far_chip_disp);
		seq_put_decimal_ull(p, " ", disp->numa_home_disp);
		seq_put_decimal_ull(p, " ", disp->numa_remote_disp);
		seq_put_decimal_ull(p, " ", disp->numa_far_disp);
		seq_माला_दो(p, "\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcpudispatch_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, vcpudispatch_stats_display, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops vcpudispatch_stats_proc_ops = अणु
	.proc_खोलो	= vcpudispatch_stats_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= vcpudispatch_stats_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

अटल sमाप_प्रकार vcpudispatch_stats_freq_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *p, माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rc, freq;
	अक्षर buf[16];

	अगर (count > 15)
		वापस -EINVAL;

	अगर (copy_from_user(buf, p, count))
		वापस -EFAULT;

	buf[count] = 0;
	rc = kstrtoपूर्णांक(buf, 0, &freq);
	अगर (rc || freq < 1 || freq > HZ) अणु
		pr_err("vcpudispatch_stats_freq: please specify a frequency between 1 and %d\n",
				HZ);
		वापस rc ? rc : -EINVAL;
	पूर्ण

	vcpudispatch_stats_freq = freq;

	वापस count;
पूर्ण

अटल पूर्णांक vcpudispatch_stats_freq_display(काष्ठा seq_file *p, व्योम *v)
अणु
	seq_म_लिखो(p, "%d\n", vcpudispatch_stats_freq);
	वापस 0;
पूर्ण

अटल पूर्णांक vcpudispatch_stats_freq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, vcpudispatch_stats_freq_display, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops vcpudispatch_stats_freq_proc_ops = अणु
	.proc_खोलो	= vcpudispatch_stats_freq_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= vcpudispatch_stats_freq_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक __init vcpudispatch_stats_procfs_init(व्योम)
अणु
	/*
	 * Aव्योम smp_processor_id जबतक preemptible. All CPUs should have
	 * the same value क्रम lppaca_shared_proc.
	 */
	preempt_disable();
	अगर (!lppaca_shared_proc(get_lppaca())) अणु
		preempt_enable();
		वापस 0;
	पूर्ण
	preempt_enable();

	अगर (!proc_create("powerpc/vcpudispatch_stats", 0600, शून्य,
					&vcpudispatch_stats_proc_ops))
		pr_err("vcpudispatch_stats: error creating procfs file\n");
	अन्यथा अगर (!proc_create("powerpc/vcpudispatch_stats_freq", 0600, शून्य,
					&vcpudispatch_stats_freq_proc_ops))
		pr_err("vcpudispatch_stats_freq: error creating procfs file\n");

	वापस 0;
पूर्ण

machine_device_initcall(pseries, vcpudispatch_stats_procfs_init);
#पूर्ण_अगर /* CONFIG_PPC_SPLPAR */

व्योम vpa_init(पूर्णांक cpu)
अणु
	पूर्णांक hwcpu = get_hard_smp_processor_id(cpu);
	अचिन्हित दीर्घ addr;
	दीर्घ ret;

	/*
	 * The spec says it "may be problematic" अगर CPU x रेजिस्टरs the VPA of
	 * CPU y. We should never करो that, but wail अगर we ever करो.
	 */
	WARN_ON(cpu != smp_processor_id());

	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		lppaca_of(cpu).vmxregs_in_use = 1;

	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		lppaca_of(cpu).ebb_regs_in_use = 1;

	addr = __pa(&lppaca_of(cpu));
	ret = रेजिस्टर_vpa(hwcpu, addr);

	अगर (ret) अणु
		pr_err("WARNING: VPA registration for cpu %d (hw %d) of area "
		       "%lx failed with %ld\n", cpu, hwcpu, addr, ret);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/*
	 * PAPR says this feature is SLB-Buffer but firmware never
	 * reports that.  All SPLPAR support SLB shaकरोw buffer.
	 */
	अगर (!radix_enabled() && firmware_has_feature(FW_FEATURE_SPLPAR)) अणु
		addr = __pa(paca_ptrs[cpu]->slb_shaकरोw_ptr);
		ret = रेजिस्टर_slb_shaकरोw(hwcpu, addr);
		अगर (ret)
			pr_err("WARNING: SLB shadow buffer registration for "
			       "cpu %d (hw %d) of area %lx failed with %ld\n",
			       cpu, hwcpu, addr, ret);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

	/*
	 * Register dispatch trace log, अगर one has been allocated.
	 */
	रेजिस्टर_dtl_buffer(cpu);
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64

अटल दीर्घ pSeries_lpar_hpte_insert(अचिन्हित दीर्घ hpte_group,
				     अचिन्हित दीर्घ vpn, अचिन्हित दीर्घ pa,
				     अचिन्हित दीर्घ rflags, अचिन्हित दीर्घ vflags,
				     पूर्णांक psize, पूर्णांक apsize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ lpar_rc;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ slot;
	अचिन्हित दीर्घ hpte_v, hpte_r;

	अगर (!(vflags & HPTE_V_BOLTED))
		pr_devel("hpte_insert(group=%lx, vpn=%016lx, "
			 "pa=%016lx, rflags=%lx, vflags=%lx, psize=%d)\n",
			 hpte_group, vpn,  pa, rflags, vflags, psize);

	hpte_v = hpte_encode_v(vpn, psize, apsize, ssize) | vflags | HPTE_V_VALID;
	hpte_r = hpte_encode_r(pa, psize, apsize) | rflags;

	अगर (!(vflags & HPTE_V_BOLTED))
		pr_devel(" hpte_v=%016lx, hpte_r=%016lx\n", hpte_v, hpte_r);

	/* Now fill in the actual HPTE */
	/* Set CEC cookie to 0         */
	/* Zero page = 0               */
	/* I-cache Invalidate = 0      */
	/* I-cache synchronize = 0     */
	/* Exact = 0                   */
	flags = 0;

	अगर (firmware_has_feature(FW_FEATURE_XCMO) && !(hpte_r & HPTE_R_N))
		flags |= H_COALESCE_CAND;

	lpar_rc = plpar_pte_enter(flags, hpte_group, hpte_v, hpte_r, &slot);
	अगर (unlikely(lpar_rc == H_PTEG_FULL)) अणु
		pr_devel("Hash table group is full\n");
		वापस -1;
	पूर्ण

	/*
	 * Since we try and ioremap PHBs we करोn't own, the pte insert
	 * will fail. However we must catch the failure in hash_page
	 * or we will loop क्रमever, so वापस -2 in this हाल.
	 */
	अगर (unlikely(lpar_rc != H_SUCCESS)) अणु
		pr_err("Failed hash pte insert with error %ld\n", lpar_rc);
		वापस -2;
	पूर्ण
	अगर (!(vflags & HPTE_V_BOLTED))
		pr_devel(" -> slot: %lu\n", slot & 7);

	/* Because of iSeries, we have to pass करोwn the secondary
	 * bucket bit here as well
	 */
	वापस (slot & 7) | (!!(vflags & HPTE_V_SECONDARY) << 3);
पूर्ण

अटल DEFINE_SPINLOCK(pSeries_lpar_tlbie_lock);

अटल दीर्घ pSeries_lpar_hpte_हटाओ(अचिन्हित दीर्घ hpte_group)
अणु
	अचिन्हित दीर्घ slot_offset;
	अचिन्हित दीर्घ lpar_rc;
	पूर्णांक i;
	अचिन्हित दीर्घ dummy1, dummy2;

	/* pick a अक्रमom slot to start at */
	slot_offset = mftb() & 0x7;

	क्रम (i = 0; i < HPTES_PER_GROUP; i++) अणु

		/* करोn't हटाओ a bolted entry */
		lpar_rc = plpar_pte_हटाओ(H_ANDCOND, hpte_group + slot_offset,
					   HPTE_V_BOLTED, &dummy1, &dummy2);
		अगर (lpar_rc == H_SUCCESS)
			वापस i;

		/*
		 * The test क्रम adjunct partition is perक्रमmed beक्रमe the
		 * ANDCOND test.  H_RESOURCE may be वापसed, so we need to
		 * check क्रम that as well.
		 */
		BUG_ON(lpar_rc != H_NOT_FOUND && lpar_rc != H_RESOURCE);

		slot_offset++;
		slot_offset &= 0x7;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम manual_hpte_clear_all(व्योम)
अणु
	अचिन्हित दीर्घ size_bytes = 1UL << ppc64_pft_size;
	अचिन्हित दीर्घ hpte_count = size_bytes >> 4;
	काष्ठा अणु
		अचिन्हित दीर्घ pteh;
		अचिन्हित दीर्घ ptel;
	पूर्ण ptes[4];
	दीर्घ lpar_rc;
	अचिन्हित दीर्घ i, j;

	/* Read in batches of 4,
	 * invalidate only valid entries not in the VRMA
	 * hpte_count will be a multiple of 4
         */
	क्रम (i = 0; i < hpte_count; i += 4) अणु
		lpar_rc = plpar_pte_पढ़ो_4_raw(0, i, (व्योम *)ptes);
		अगर (lpar_rc != H_SUCCESS) अणु
			pr_info("Failed to read hash page table at %ld err %ld\n",
				i, lpar_rc);
			जारी;
		पूर्ण
		क्रम (j = 0; j < 4; j++)अणु
			अगर ((ptes[j].pteh & HPTE_V_VRMA_MASK) ==
				HPTE_V_VRMA_MASK)
				जारी;
			अगर (ptes[j].pteh & HPTE_V_VALID)
				plpar_pte_हटाओ_raw(0, i + j, 0,
					&(ptes[j].pteh), &(ptes[j].ptel));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hcall_hpte_clear_all(व्योम)
अणु
	पूर्णांक rc;

	करो अणु
		rc = plpar_hcall_norets(H_CLEAR_HPT);
	पूर्ण जबतक (rc == H_CONTINUE);

	वापस rc;
पूर्ण

अटल व्योम pseries_hpte_clear_all(व्योम)
अणु
	पूर्णांक rc;

	rc = hcall_hpte_clear_all();
	अगर (rc != H_SUCCESS)
		manual_hpte_clear_all();

#अगर_घोषित __LITTLE_ENDIAN__
	/*
	 * Reset exceptions to big endian.
	 *
	 * FIXME this is a hack क्रम kexec, we need to reset the exception
	 * endian beक्रमe starting the new kernel and this is a convenient place
	 * to करो it.
	 *
	 * This is also called on boot when a fadump happens. In that हाल we
	 * must not change the exception endian mode.
	 */
	अगर (firmware_has_feature(FW_FEATURE_SET_MODE) && !is_fadump_active())
		pseries_big_endian_exceptions();
#पूर्ण_अगर
पूर्ण

/*
 * NOTE: क्रम updatepp ops we are क्रमtunate that the linux "newpp" bits and
 * the low 3 bits of flags happen to line up.  So no transक्रमm is needed.
 * We can probably optimize here and assume the high bits of newpp are
 * alपढ़ोy zero.  For now I am paranoid.
 */
अटल दीर्घ pSeries_lpar_hpte_updatepp(अचिन्हित दीर्घ slot,
				       अचिन्हित दीर्घ newpp,
				       अचिन्हित दीर्घ vpn,
				       पूर्णांक psize, पूर्णांक apsize,
				       पूर्णांक ssize, अचिन्हित दीर्घ inv_flags)
अणु
	अचिन्हित दीर्घ lpar_rc;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ want_v;

	want_v = hpte_encode_avpn(vpn, psize, ssize);

	flags = (newpp & (HPTE_R_PP | HPTE_R_N | HPTE_R_KEY_LO)) | H_AVPN;
	flags |= (newpp & HPTE_R_KEY_HI) >> 48;
	अगर (mmu_has_feature(MMU_FTR_KERNEL_RO))
		/* Move pp0 पूर्णांकo bit 8 (IBM 55) */
		flags |= (newpp & HPTE_R_PP0) >> 55;

	pr_devel("    update: avpnv=%016lx, hash=%016lx, f=%lx, psize: %d ...",
		 want_v, slot, flags, psize);

	lpar_rc = plpar_pte_protect(flags, slot, want_v);

	अगर (lpar_rc == H_NOT_FOUND) अणु
		pr_devel("not found !\n");
		वापस -1;
	पूर्ण

	pr_devel("ok\n");

	BUG_ON(lpar_rc != H_SUCCESS);

	वापस 0;
पूर्ण

अटल दीर्घ __pSeries_lpar_hpte_find(अचिन्हित दीर्घ want_v, अचिन्हित दीर्घ hpte_group)
अणु
	दीर्घ lpar_rc;
	अचिन्हित दीर्घ i, j;
	काष्ठा अणु
		अचिन्हित दीर्घ pteh;
		अचिन्हित दीर्घ ptel;
	पूर्ण ptes[4];

	क्रम (i = 0; i < HPTES_PER_GROUP; i += 4, hpte_group += 4) अणु

		lpar_rc = plpar_pte_पढ़ो_4(0, hpte_group, (व्योम *)ptes);
		अगर (lpar_rc != H_SUCCESS) अणु
			pr_info("Failed to read hash page table at %ld err %ld\n",
				hpte_group, lpar_rc);
			जारी;
		पूर्ण

		क्रम (j = 0; j < 4; j++) अणु
			अगर (HPTE_V_COMPARE(ptes[j].pteh, want_v) &&
			    (ptes[j].pteh & HPTE_V_VALID))
				वापस i + j;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल दीर्घ pSeries_lpar_hpte_find(अचिन्हित दीर्घ vpn, पूर्णांक psize, पूर्णांक ssize)
अणु
	दीर्घ slot;
	अचिन्हित दीर्घ hash;
	अचिन्हित दीर्घ want_v;
	अचिन्हित दीर्घ hpte_group;

	hash = hpt_hash(vpn, mmu_psize_defs[psize].shअगरt, ssize);
	want_v = hpte_encode_avpn(vpn, psize, ssize);

	/*
	 * We try to keep bolted entries always in primary hash
	 * But in some हाल we can find them in secondary too.
	 */
	hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	slot = __pSeries_lpar_hpte_find(want_v, hpte_group);
	अगर (slot < 0) अणु
		/* Try in secondary */
		hpte_group = (~hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot = __pSeries_lpar_hpte_find(want_v, hpte_group);
		अगर (slot < 0)
			वापस -1;
	पूर्ण
	वापस hpte_group + slot;
पूर्ण

अटल व्योम pSeries_lpar_hpte_updateboltedpp(अचिन्हित दीर्घ newpp,
					     अचिन्हित दीर्घ ea,
					     पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ vpn;
	अचिन्हित दीर्घ lpar_rc, slot, vsid, flags;

	vsid = get_kernel_vsid(ea, ssize);
	vpn = hpt_vpn(ea, vsid, ssize);

	slot = pSeries_lpar_hpte_find(vpn, psize, ssize);
	BUG_ON(slot == -1);

	flags = newpp & (HPTE_R_PP | HPTE_R_N);
	अगर (mmu_has_feature(MMU_FTR_KERNEL_RO))
		/* Move pp0 पूर्णांकo bit 8 (IBM 55) */
		flags |= (newpp & HPTE_R_PP0) >> 55;

	flags |= ((newpp & HPTE_R_KEY_HI) >> 48) | (newpp & HPTE_R_KEY_LO);

	lpar_rc = plpar_pte_protect(flags, slot, 0);

	BUG_ON(lpar_rc != H_SUCCESS);
पूर्ण

अटल व्योम pSeries_lpar_hpte_invalidate(अचिन्हित दीर्घ slot, अचिन्हित दीर्घ vpn,
					 पूर्णांक psize, पूर्णांक apsize,
					 पूर्णांक ssize, पूर्णांक local)
अणु
	अचिन्हित दीर्घ want_v;
	अचिन्हित दीर्घ lpar_rc;
	अचिन्हित दीर्घ dummy1, dummy2;

	pr_devel("    inval : slot=%lx, vpn=%016lx, psize: %d, local: %d\n",
		 slot, vpn, psize, local);

	want_v = hpte_encode_avpn(vpn, psize, ssize);
	lpar_rc = plpar_pte_हटाओ(H_AVPN, slot, want_v, &dummy1, &dummy2);
	अगर (lpar_rc == H_NOT_FOUND)
		वापस;

	BUG_ON(lpar_rc != H_SUCCESS);
पूर्ण


/*
 * As defined in the PAPR's section 14.5.4.1.8
 * The control mask करोesn't include the वापसed reference and change bit from
 * the processed PTE.
 */
#घोषणा HBLKR_AVPN		0x0100000000000000UL
#घोषणा HBLKR_CTRL_MASK		0xf800000000000000UL
#घोषणा HBLKR_CTRL_SUCCESS	0x8000000000000000UL
#घोषणा HBLKR_CTRL_ERRNOTFOUND	0x8800000000000000UL
#घोषणा HBLKR_CTRL_ERRBUSY	0xa000000000000000UL

/*
 * Returned true अगर we are supporting this block size क्रम the specअगरied segment
 * base page size and actual page size.
 *
 * Currently, we only support 8 size block.
 */
अटल अंतरभूत bool is_supported_hlbkrm(पूर्णांक bpsize, पूर्णांक psize)
अणु
	वापस (hblkrm_size[bpsize][psize] == HBLKRM_SUPPORTED_BLOCK_SIZE);
पूर्ण

/**
 * H_BLOCK_REMOVE caller.
 * @idx should poपूर्णांक to the latest @param entry set with a PTEX.
 * If PTE cannot be processed because another CPUs has alपढ़ोy locked that
 * group, those entries are put back in @param starting at index 1.
 * If entries has to be retried and @retry_busy is set to true, these entries
 * are retried until success. If @retry_busy is set to false, the वापसed
 * is the number of entries yet to process.
 */
अटल अचिन्हित दीर्घ call_block_हटाओ(अचिन्हित दीर्घ idx, अचिन्हित दीर्घ *param,
				       bool retry_busy)
अणु
	अचिन्हित दीर्घ i, rc, new_idx;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];

	अगर (idx < 2) अणु
		pr_warn("Unexpected empty call to H_BLOCK_REMOVE");
		वापस 0;
	पूर्ण
again:
	new_idx = 0;
	अगर (idx > PLPAR_HCALL9_बफ_मानE) अणु
		pr_err("Too many PTEs (%lu) for H_BLOCK_REMOVE", idx);
		idx = PLPAR_HCALL9_बफ_मानE;
	पूर्ण अन्यथा अगर (idx < PLPAR_HCALL9_बफ_मानE)
		param[idx] = HBR_END;

	rc = plpar_hcall9(H_BLOCK_REMOVE, retbuf,
			  param[0], /* AVA */
			  param[1],  param[2],  param[3],  param[4], /* TS0-7 */
			  param[5],  param[6],  param[7],  param[8]);
	अगर (rc == H_SUCCESS)
		वापस 0;

	BUG_ON(rc != H_PARTIAL);

	/* Check that the unprocessed entries were 'not found' or 'busy' */
	क्रम (i = 0; i < idx-1; i++) अणु
		अचिन्हित दीर्घ ctrl = retbuf[i] & HBLKR_CTRL_MASK;

		अगर (ctrl == HBLKR_CTRL_ERRBUSY) अणु
			param[++new_idx] = param[i+1];
			जारी;
		पूर्ण

		BUG_ON(ctrl != HBLKR_CTRL_SUCCESS
		       && ctrl != HBLKR_CTRL_ERRNOTFOUND);
	पूर्ण

	/*
	 * If there were entries found busy, retry these entries अगर requested,
	 * of अगर all the entries have to be retried.
	 */
	अगर (new_idx && (retry_busy || new_idx == (PLPAR_HCALL9_बफ_मानE-1))) अणु
		idx = new_idx + 1;
		जाओ again;
	पूर्ण

	वापस new_idx;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/*
 * Limit iterations holding pSeries_lpar_tlbie_lock to 3. We also need
 * to make sure that we aव्योम bouncing the hypervisor tlbie lock.
 */
#घोषणा PPC64_HUGE_HPTE_BATCH 12

अटल व्योम hugepage_block_invalidate(अचिन्हित दीर्घ *slot, अचिन्हित दीर्घ *vpn,
				      पूर्णांक count, पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ param[PLPAR_HCALL9_बफ_मानE];
	अचिन्हित दीर्घ shअगरt, current_vpgb, vpgb;
	पूर्णांक i, pix = 0;

	shअगरt = mmu_psize_defs[psize].shअगरt;

	क्रम (i = 0; i < count; i++) अणु
		/*
		 * Shअगरting 3 bits more on the right to get a
		 * 8 pages aligned भव addresse.
		 */
		vpgb = (vpn[i] >> (shअगरt - VPN_SHIFT + 3));
		अगर (!pix || vpgb != current_vpgb) अणु
			/*
			 * Need to start a new 8 pages block, flush
			 * the current one अगर needed.
			 */
			अगर (pix)
				(व्योम)call_block_हटाओ(pix, param, true);
			current_vpgb = vpgb;
			param[0] = hpte_encode_avpn(vpn[i], psize, ssize);
			pix = 1;
		पूर्ण

		param[pix++] = HBR_REQUEST | HBLKR_AVPN | slot[i];
		अगर (pix == PLPAR_HCALL9_बफ_मानE) अणु
			pix = call_block_हटाओ(pix, param, false);
			/*
			 * pix = 0 means that all the entries were
			 * हटाओd, we can start a new block.
			 * Otherwise, this means that there are entries
			 * to retry, and pix poपूर्णांकs to latest one, so
			 * we should increment it and try to जारी
			 * the same block.
			 */
			अगर (pix)
				pix++;
		पूर्ण
	पूर्ण
	अगर (pix)
		(व्योम)call_block_हटाओ(pix, param, true);
पूर्ण

अटल व्योम hugepage_bulk_invalidate(अचिन्हित दीर्घ *slot, अचिन्हित दीर्घ *vpn,
				     पूर्णांक count, पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ param[PLPAR_HCALL9_बफ_मानE];
	पूर्णांक i = 0, pix = 0, rc;

	क्रम (i = 0; i < count; i++) अणु

		अगर (!firmware_has_feature(FW_FEATURE_BULK_REMOVE)) अणु
			pSeries_lpar_hpte_invalidate(slot[i], vpn[i], psize, 0,
						     ssize, 0);
		पूर्ण अन्यथा अणु
			param[pix] = HBR_REQUEST | HBR_AVPN | slot[i];
			param[pix+1] = hpte_encode_avpn(vpn[i], psize, ssize);
			pix += 2;
			अगर (pix == 8) अणु
				rc = plpar_hcall9(H_BULK_REMOVE, param,
						  param[0], param[1], param[2],
						  param[3], param[4], param[5],
						  param[6], param[7]);
				BUG_ON(rc != H_SUCCESS);
				pix = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (pix) अणु
		param[pix] = HBR_END;
		rc = plpar_hcall9(H_BULK_REMOVE, param, param[0], param[1],
				  param[2], param[3], param[4], param[5],
				  param[6], param[7]);
		BUG_ON(rc != H_SUCCESS);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __pSeries_lpar_hugepage_invalidate(अचिन्हित दीर्घ *slot,
						      अचिन्हित दीर्घ *vpn,
						      पूर्णांक count, पूर्णांक psize,
						      पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक lock_tlbie = !mmu_has_feature(MMU_FTR_LOCKLESS_TLBIE);

	अगर (lock_tlbie)
		spin_lock_irqsave(&pSeries_lpar_tlbie_lock, flags);

	/* Assuming THP size is 16M */
	अगर (is_supported_hlbkrm(psize, MMU_PAGE_16M))
		hugepage_block_invalidate(slot, vpn, count, psize, ssize);
	अन्यथा
		hugepage_bulk_invalidate(slot, vpn, count, psize, ssize);

	अगर (lock_tlbie)
		spin_unlock_irqrestore(&pSeries_lpar_tlbie_lock, flags);
पूर्ण

अटल व्योम pSeries_lpar_hugepage_invalidate(अचिन्हित दीर्घ vsid,
					     अचिन्हित दीर्घ addr,
					     अचिन्हित अक्षर *hpte_slot_array,
					     पूर्णांक psize, पूर्णांक ssize, पूर्णांक local)
अणु
	पूर्णांक i, index = 0;
	अचिन्हित दीर्घ s_addr = addr;
	अचिन्हित पूर्णांक max_hpte_count, valid;
	अचिन्हित दीर्घ vpn_array[PPC64_HUGE_HPTE_BATCH];
	अचिन्हित दीर्घ slot_array[PPC64_HUGE_HPTE_BATCH];
	अचिन्हित दीर्घ shअगरt, hidx, vpn = 0, hash, slot;

	shअगरt = mmu_psize_defs[psize].shअगरt;
	max_hpte_count = 1U << (PMD_SHIFT - shअगरt);

	क्रम (i = 0; i < max_hpte_count; i++) अणु
		valid = hpte_valid(hpte_slot_array, i);
		अगर (!valid)
			जारी;
		hidx =  hpte_hash_index(hpte_slot_array, i);

		/* get the vpn */
		addr = s_addr + (i * (1ul << shअगरt));
		vpn = hpt_vpn(addr, vsid, ssize);
		hash = hpt_hash(vpn, shअगरt, ssize);
		अगर (hidx & _PTEIDX_SECONDARY)
			hash = ~hash;

		slot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot += hidx & _PTEIDX_GROUP_IX;

		slot_array[index] = slot;
		vpn_array[index] = vpn;
		अगर (index == PPC64_HUGE_HPTE_BATCH - 1) अणु
			/*
			 * Now करो a bluk invalidate
			 */
			__pSeries_lpar_hugepage_invalidate(slot_array,
							   vpn_array,
							   PPC64_HUGE_HPTE_BATCH,
							   psize, ssize);
			index = 0;
		पूर्ण अन्यथा
			index++;
	पूर्ण
	अगर (index)
		__pSeries_lpar_hugepage_invalidate(slot_array, vpn_array,
						   index, psize, ssize);
पूर्ण
#अन्यथा
अटल व्योम pSeries_lpar_hugepage_invalidate(अचिन्हित दीर्घ vsid,
					     अचिन्हित दीर्घ addr,
					     अचिन्हित अक्षर *hpte_slot_array,
					     पूर्णांक psize, पूर्णांक ssize, पूर्णांक local)
अणु
	WARN(1, "%s called without THP support\n", __func__);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pSeries_lpar_hpte_हटाओbolted(अचिन्हित दीर्घ ea,
					  पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ vpn;
	अचिन्हित दीर्घ slot, vsid;

	vsid = get_kernel_vsid(ea, ssize);
	vpn = hpt_vpn(ea, vsid, ssize);

	slot = pSeries_lpar_hpte_find(vpn, psize, ssize);
	अगर (slot == -1)
		वापस -ENOENT;

	/*
	 * lpar करोesn't use the passed actual page size
	 */
	pSeries_lpar_hpte_invalidate(slot, vpn, psize, 0, ssize, 0);
	वापस 0;
पूर्ण


अटल अंतरभूत अचिन्हित दीर्घ compute_slot(real_pte_t pte,
					 अचिन्हित दीर्घ vpn,
					 अचिन्हित दीर्घ index,
					 अचिन्हित दीर्घ shअगरt,
					 पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ slot, hash, hidx;

	hash = hpt_hash(vpn, shअगरt, ssize);
	hidx = __rpte_to_hidx(pte, index);
	अगर (hidx & _PTEIDX_SECONDARY)
		hash = ~hash;
	slot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	slot += hidx & _PTEIDX_GROUP_IX;
	वापस slot;
पूर्ण

/**
 * The hcall H_BLOCK_REMOVE implies that the भव pages to processed are
 * "all within the same naturally aligned 8 page virtual address block".
 */
अटल व्योम करो_block_हटाओ(अचिन्हित दीर्घ number, काष्ठा ppc64_tlb_batch *batch,
			    अचिन्हित दीर्घ *param)
अणु
	अचिन्हित दीर्घ vpn;
	अचिन्हित दीर्घ i, pix = 0;
	अचिन्हित दीर्घ index, shअगरt, slot, current_vpgb, vpgb;
	real_pte_t pte;
	पूर्णांक psize, ssize;

	psize = batch->psize;
	ssize = batch->ssize;

	क्रम (i = 0; i < number; i++) अणु
		vpn = batch->vpn[i];
		pte = batch->pte[i];
		pte_iterate_hashed_subpages(pte, psize, vpn, index, shअगरt) अणु
			/*
			 * Shअगरting 3 bits more on the right to get a
			 * 8 pages aligned भव addresse.
			 */
			vpgb = (vpn >> (shअगरt - VPN_SHIFT + 3));
			अगर (!pix || vpgb != current_vpgb) अणु
				/*
				 * Need to start a new 8 pages block, flush
				 * the current one अगर needed.
				 */
				अगर (pix)
					(व्योम)call_block_हटाओ(pix, param,
								true);
				current_vpgb = vpgb;
				param[0] = hpte_encode_avpn(vpn, psize,
							    ssize);
				pix = 1;
			पूर्ण

			slot = compute_slot(pte, vpn, index, shअगरt, ssize);
			param[pix++] = HBR_REQUEST | HBLKR_AVPN | slot;

			अगर (pix == PLPAR_HCALL9_बफ_मानE) अणु
				pix = call_block_हटाओ(pix, param, false);
				/*
				 * pix = 0 means that all the entries were
				 * हटाओd, we can start a new block.
				 * Otherwise, this means that there are entries
				 * to retry, and pix poपूर्णांकs to latest one, so
				 * we should increment it and try to जारी
				 * the same block.
				 */
				अगर (pix)
					pix++;
			पूर्ण
		पूर्ण pte_iterate_hashed_end();
	पूर्ण

	अगर (pix)
		(व्योम)call_block_हटाओ(pix, param, true);
पूर्ण

/*
 * TLB Block Invalidate Characteristics
 *
 * These अक्षरacteristics define the size of the block the hcall H_BLOCK_REMOVE
 * is able to process क्रम each couple segment base page size, actual page size.
 *
 * The ibm,get-प्रणाली-parameter properties is वापसing a buffer with the
 * following layout:
 *
 * [ 2 bytes size of the RTAS buffer (excluding these 2 bytes) ]
 * -----------------
 * TLB Block Invalidate Specअगरiers:
 * [ 1 byte LOG base 2 of the TLB invalidate block size being specअगरied ]
 * [ 1 byte Number of page sizes (N) that are supported क्रम the specअगरied
 *          TLB invalidate block size ]
 * [ 1 byte Encoded segment base page size and actual page size
 *          MSB=0 means 4k segment base page size and actual page size
 *          MSB=1 the penc value in mmu_psize_def ]
 * ...
 * -----------------
 * Next TLB Block Invalidate Specअगरiers...
 * -----------------
 * [ 0 ]
 */
अटल अंतरभूत व्योम set_hblkrm_bloc_size(पूर्णांक bpsize, पूर्णांक psize,
					अचिन्हित पूर्णांक block_size)
अणु
	अगर (block_size > hblkrm_size[bpsize][psize])
		hblkrm_size[bpsize][psize] = block_size;
पूर्ण

/*
 * Decode the Encoded segment base page size and actual page size.
 * PAPR specअगरies:
 *   - bit 7 is the L bit
 *   - bits 0-5 are the penc value
 * If the L bit is 0, this means 4K segment base page size and actual page size
 * otherwise the penc value should be पढ़ो.
 */
#घोषणा HBLKRM_L_MASK		0x80
#घोषणा HBLKRM_PENC_MASK	0x3f
अटल अंतरभूत व्योम __init check_lp_set_hblkrm(अचिन्हित पूर्णांक lp,
					      अचिन्हित पूर्णांक block_size)
अणु
	अचिन्हित पूर्णांक bpsize, psize;

	/* First, check the L bit, अगर not set, this means 4K */
	अगर ((lp & HBLKRM_L_MASK) == 0) अणु
		set_hblkrm_bloc_size(MMU_PAGE_4K, MMU_PAGE_4K, block_size);
		वापस;
	पूर्ण

	lp &= HBLKRM_PENC_MASK;
	क्रम (bpsize = 0; bpsize < MMU_PAGE_COUNT; bpsize++) अणु
		काष्ठा mmu_psize_def *def = &mmu_psize_defs[bpsize];

		क्रम (psize = 0; psize < MMU_PAGE_COUNT; psize++) अणु
			अगर (def->penc[psize] == lp) अणु
				set_hblkrm_bloc_size(bpsize, psize, block_size);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा SPLPAR_TLB_BIC_TOKEN		50

/*
 * The size of the TLB Block Invalidate Characteristics is variable. But at the
 * maximum it will be the number of possible page sizes *2 + 10 bytes.
 * Currently MMU_PAGE_COUNT is 16, which means 42 bytes. Use a cache line size
 * (128 bytes) क्रम the buffer to get plenty of space.
 */
#घोषणा SPLPAR_TLB_BIC_MAXLENGTH	128

व्योम __init pseries_lpar_पढ़ो_hblkrm_अक्षरacteristics(व्योम)
अणु
	अचिन्हित अक्षर local_buffer[SPLPAR_TLB_BIC_MAXLENGTH];
	पूर्णांक call_status, len, idx, bpsize;

	अगर (!firmware_has_feature(FW_FEATURE_BLOCK_REMOVE))
		वापस;

	spin_lock(&rtas_data_buf_lock);
	स_रखो(rtas_data_buf, 0, RTAS_DATA_BUF_SIZE);
	call_status = rtas_call(rtas_token("ibm,get-system-parameter"), 3, 1,
				शून्य,
				SPLPAR_TLB_BIC_TOKEN,
				__pa(rtas_data_buf),
				RTAS_DATA_BUF_SIZE);
	स_नकल(local_buffer, rtas_data_buf, SPLPAR_TLB_BIC_MAXLENGTH);
	local_buffer[SPLPAR_TLB_BIC_MAXLENGTH - 1] = '\0';
	spin_unlock(&rtas_data_buf_lock);

	अगर (call_status != 0) अणु
		pr_warn("%s %s Error calling get-system-parameter (0x%x)\n",
			__खाता__, __func__, call_status);
		वापस;
	पूर्ण

	/*
	 * The first two (2) bytes of the data in the buffer are the length of
	 * the वापसed data, not counting these first two (2) bytes.
	 */
	len = be16_to_cpu(*((u16 *)local_buffer)) + 2;
	अगर (len > SPLPAR_TLB_BIC_MAXLENGTH) अणु
		pr_warn("%s too large returned buffer %d", __func__, len);
		वापस;
	पूर्ण

	idx = 2;
	जबतक (idx < len) अणु
		u8 block_shअगरt = local_buffer[idx++];
		u32 block_size;
		अचिन्हित पूर्णांक npsize;

		अगर (!block_shअगरt)
			अवरोध;

		block_size = 1 << block_shअगरt;

		क्रम (npsize = local_buffer[idx++];
		     npsize > 0 && idx < len; npsize--)
			check_lp_set_hblkrm((अचिन्हित पूर्णांक) local_buffer[idx++],
					    block_size);
	पूर्ण

	क्रम (bpsize = 0; bpsize < MMU_PAGE_COUNT; bpsize++)
		क्रम (idx = 0; idx < MMU_PAGE_COUNT; idx++)
			अगर (hblkrm_size[bpsize][idx])
				pr_info("H_BLOCK_REMOVE supports base psize:%d psize:%d block size:%d",
					bpsize, idx, hblkrm_size[bpsize][idx]);
पूर्ण

/*
 * Take a spinlock around flushes to aव्योम bouncing the hypervisor tlbie
 * lock.
 */
अटल व्योम pSeries_lpar_flush_hash_range(अचिन्हित दीर्घ number, पूर्णांक local)
अणु
	अचिन्हित दीर्घ vpn;
	अचिन्हित दीर्घ i, pix, rc;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ppc64_tlb_batch *batch = this_cpu_ptr(&ppc64_tlb_batch);
	पूर्णांक lock_tlbie = !mmu_has_feature(MMU_FTR_LOCKLESS_TLBIE);
	अचिन्हित दीर्घ param[PLPAR_HCALL9_बफ_मानE];
	अचिन्हित दीर्घ index, shअगरt, slot;
	real_pte_t pte;
	पूर्णांक psize, ssize;

	अगर (lock_tlbie)
		spin_lock_irqsave(&pSeries_lpar_tlbie_lock, flags);

	अगर (is_supported_hlbkrm(batch->psize, batch->psize)) अणु
		करो_block_हटाओ(number, batch, param);
		जाओ out;
	पूर्ण

	psize = batch->psize;
	ssize = batch->ssize;
	pix = 0;
	क्रम (i = 0; i < number; i++) अणु
		vpn = batch->vpn[i];
		pte = batch->pte[i];
		pte_iterate_hashed_subpages(pte, psize, vpn, index, shअगरt) अणु
			slot = compute_slot(pte, vpn, index, shअगरt, ssize);
			अगर (!firmware_has_feature(FW_FEATURE_BULK_REMOVE)) अणु
				/*
				 * lpar करोesn't use the passed actual page size
				 */
				pSeries_lpar_hpte_invalidate(slot, vpn, psize,
							     0, ssize, local);
			पूर्ण अन्यथा अणु
				param[pix] = HBR_REQUEST | HBR_AVPN | slot;
				param[pix+1] = hpte_encode_avpn(vpn, psize,
								ssize);
				pix += 2;
				अगर (pix == 8) अणु
					rc = plpar_hcall9(H_BULK_REMOVE, param,
						param[0], param[1], param[2],
						param[3], param[4], param[5],
						param[6], param[7]);
					BUG_ON(rc != H_SUCCESS);
					pix = 0;
				पूर्ण
			पूर्ण
		पूर्ण pte_iterate_hashed_end();
	पूर्ण
	अगर (pix) अणु
		param[pix] = HBR_END;
		rc = plpar_hcall9(H_BULK_REMOVE, param, param[0], param[1],
				  param[2], param[3], param[4], param[5],
				  param[6], param[7]);
		BUG_ON(rc != H_SUCCESS);
	पूर्ण

out:
	अगर (lock_tlbie)
		spin_unlock_irqrestore(&pSeries_lpar_tlbie_lock, flags);
पूर्ण

अटल पूर्णांक __init disable_bulk_हटाओ(अक्षर *str)
अणु
	अगर (म_भेद(str, "off") == 0 &&
	    firmware_has_feature(FW_FEATURE_BULK_REMOVE)) अणु
		pr_info("Disabling BULK_REMOVE firmware feature");
		घातerpc_firmware_features &= ~FW_FEATURE_BULK_REMOVE;
	पूर्ण
	वापस 1;
पूर्ण

__setup("bulk_remove=", disable_bulk_हटाओ);

#घोषणा HPT_RESIZE_TIMEOUT	10000 /* ms */

काष्ठा hpt_resize_state अणु
	अचिन्हित दीर्घ shअगरt;
	पूर्णांक commit_rc;
पूर्ण;

अटल पूर्णांक pseries_lpar_resize_hpt_commit(व्योम *data)
अणु
	काष्ठा hpt_resize_state *state = data;

	state->commit_rc = plpar_resize_hpt_commit(0, state->shअगरt);
	अगर (state->commit_rc != H_SUCCESS)
		वापस -EIO;

	/* Hypervisor has transitioned the HTAB, update our globals */
	ppc64_pft_size = state->shअगरt;
	htab_size_bytes = 1UL << ppc64_pft_size;
	htab_hash_mask = (htab_size_bytes >> 7) - 1;

	वापस 0;
पूर्ण

/*
 * Must be called in process context. The caller must hold the
 * cpus_lock.
 */
अटल पूर्णांक pseries_lpar_resize_hpt(अचिन्हित दीर्घ shअगरt)
अणु
	काष्ठा hpt_resize_state state = अणु
		.shअगरt = shअगरt,
		.commit_rc = H_FUNCTION,
	पूर्ण;
	अचिन्हित पूर्णांक delay, total_delay = 0;
	पूर्णांक rc;
	kसमय_प्रकार t0, t1, t2;

	might_sleep();

	अगर (!firmware_has_feature(FW_FEATURE_HPT_RESIZE))
		वापस -ENODEV;

	pr_info("Attempting to resize HPT to shift %lu\n", shअगरt);

	t0 = kसमय_get();

	rc = plpar_resize_hpt_prepare(0, shअगरt);
	जबतक (H_IS_LONG_BUSY(rc)) अणु
		delay = get_दीर्घbusy_msecs(rc);
		total_delay += delay;
		अगर (total_delay > HPT_RESIZE_TIMEOUT) अणु
			/* prepare with shअगरt==0 cancels an in-progress resize */
			rc = plpar_resize_hpt_prepare(0, 0);
			अगर (rc != H_SUCCESS)
				pr_warn("Unexpected error %d cancelling timed out HPT resize\n",
				       rc);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(delay);
		rc = plpar_resize_hpt_prepare(0, shअगरt);
	पूर्ण

	चयन (rc) अणु
	हाल H_SUCCESS:
		/* Continue on */
		अवरोध;

	हाल H_PARAMETER:
		pr_warn("Invalid argument from H_RESIZE_HPT_PREPARE\n");
		वापस -EINVAL;
	हाल H_RESOURCE:
		pr_warn("Operation not permitted from H_RESIZE_HPT_PREPARE\n");
		वापस -EPERM;
	शेष:
		pr_warn("Unexpected error %d from H_RESIZE_HPT_PREPARE\n", rc);
		वापस -EIO;
	पूर्ण

	t1 = kसमय_get();

	rc = stop_machine_cpuslocked(pseries_lpar_resize_hpt_commit,
				     &state, शून्य);

	t2 = kसमय_get();

	अगर (rc != 0) अणु
		चयन (state.commit_rc) अणु
		हाल H_PTEG_FULL:
			वापस -ENOSPC;

		शेष:
			pr_warn("Unexpected error %d from H_RESIZE_HPT_COMMIT\n",
				state.commit_rc);
			वापस -EIO;
		पूर्ण;
	पूर्ण

	pr_info("HPT resize to shift %lu complete (%lld ms / %lld ms)\n",
		shअगरt, (दीर्घ दीर्घ) kसमय_ms_delta(t1, t0),
		(दीर्घ दीर्घ) kसमय_ms_delta(t2, t1));

	वापस 0;
पूर्ण

अटल पूर्णांक pseries_lpar_रेजिस्टर_process_table(अचिन्हित दीर्घ base,
			अचिन्हित दीर्घ page_size, अचिन्हित दीर्घ table_size)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ flags = 0;

	अगर (table_size)
		flags |= PROC_TABLE_NEW;
	अगर (radix_enabled()) अणु
		flags |= PROC_TABLE_RADIX;
		अगर (mmu_has_feature(MMU_FTR_GTSE))
			flags |= PROC_TABLE_GTSE;
	पूर्ण अन्यथा
		flags |= PROC_TABLE_HPT_SLB;
	क्रम (;;) अणु
		rc = plpar_hcall_norets(H_REGISTER_PROC_TBL, flags, base,
					page_size, table_size);
		अगर (!H_IS_LONG_BUSY(rc))
			अवरोध;
		mdelay(get_दीर्घbusy_msecs(rc));
	पूर्ण
	अगर (rc != H_SUCCESS) अणु
		pr_err("Failed to register process table (rc=%ld)\n", rc);
		BUG();
	पूर्ण
	वापस rc;
पूर्ण

व्योम __init hpte_init_pseries(व्योम)
अणु
	mmu_hash_ops.hpte_invalidate	 = pSeries_lpar_hpte_invalidate;
	mmu_hash_ops.hpte_updatepp	 = pSeries_lpar_hpte_updatepp;
	mmu_hash_ops.hpte_updateboltedpp = pSeries_lpar_hpte_updateboltedpp;
	mmu_hash_ops.hpte_insert	 = pSeries_lpar_hpte_insert;
	mmu_hash_ops.hpte_हटाओ	 = pSeries_lpar_hpte_हटाओ;
	mmu_hash_ops.hpte_हटाओbolted   = pSeries_lpar_hpte_हटाओbolted;
	mmu_hash_ops.flush_hash_range	 = pSeries_lpar_flush_hash_range;
	mmu_hash_ops.hpte_clear_all      = pseries_hpte_clear_all;
	mmu_hash_ops.hugepage_invalidate = pSeries_lpar_hugepage_invalidate;

	अगर (firmware_has_feature(FW_FEATURE_HPT_RESIZE))
		mmu_hash_ops.resize_hpt = pseries_lpar_resize_hpt;

	/*
	 * On POWER9, we need to करो a H_REGISTER_PROC_TBL hcall
	 * to inक्रमm the hypervisor that we wish to use the HPT.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		pseries_lpar_रेजिस्टर_process_table(0, 0, 0);
पूर्ण

#अगर_घोषित CONFIG_PPC_RADIX_MMU
व्योम radix_init_pseries(व्योम)
अणु
	pr_info("Using radix MMU under hypervisor\n");

	pseries_lpar_रेजिस्टर_process_table(__pa(process_tb),
						0, PRTB_SIZE_SHIFT - 12);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_SMLPAR
#घोषणा CMO_FREE_HINT_DEFAULT 1
अटल पूर्णांक cmo_मुक्त_hपूर्णांक_flag = CMO_FREE_HINT_DEFAULT;

अटल पूर्णांक __init cmo_मुक्त_hपूर्णांक(अक्षर *str)
अणु
	अक्षर *parm;
	parm = म_मालाip(str);

	अगर (strहालcmp(parm, "no") == 0 || strहालcmp(parm, "off") == 0) अणु
		pr_info("%s: CMO free page hinting is not active.\n", __func__);
		cmo_मुक्त_hपूर्णांक_flag = 0;
		वापस 1;
	पूर्ण

	cmo_मुक्त_hपूर्णांक_flag = 1;
	pr_info("%s: CMO free page hinting is active.\n", __func__);

	अगर (strहालcmp(parm, "yes") == 0 || strहालcmp(parm, "on") == 0)
		वापस 1;

	वापस 0;
पूर्ण

__setup("cmo_free_hint=", cmo_मुक्त_hपूर्णांक);

अटल व्योम pSeries_set_page_state(काष्ठा page *page, पूर्णांक order,
				   अचिन्हित दीर्घ state)
अणु
	पूर्णांक i, j;
	अचिन्हित दीर्घ cmo_page_sz, addr;

	cmo_page_sz = cmo_get_page_size();
	addr = __pa((अचिन्हित दीर्घ)page_address(page));

	क्रम (i = 0; i < (1 << order); i++, addr += PAGE_SIZE) अणु
		क्रम (j = 0; j < PAGE_SIZE; j += cmo_page_sz)
			plpar_hcall_norets(H_PAGE_INIT, state, addr + j, 0);
	पूर्ण
पूर्ण

व्योम arch_मुक्त_page(काष्ठा page *page, पूर्णांक order)
अणु
	अगर (radix_enabled())
		वापस;
	अगर (!cmo_मुक्त_hपूर्णांक_flag || !firmware_has_feature(FW_FEATURE_CMO))
		वापस;

	pSeries_set_page_state(page, order, H_PAGE_SET_UNUSED);
पूर्ण
EXPORT_SYMBOL(arch_मुक्त_page);

#पूर्ण_अगर /* CONFIG_PPC_SMLPAR */
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#अगर_घोषित CONFIG_TRACEPOINTS
#अगर_घोषित CONFIG_JUMP_LABEL
काष्ठा अटल_key hcall_tracepoपूर्णांक_key = STATIC_KEY_INIT;

पूर्णांक hcall_tracepoपूर्णांक_regfunc(व्योम)
अणु
	अटल_key_slow_inc(&hcall_tracepoपूर्णांक_key);
	वापस 0;
पूर्ण

व्योम hcall_tracepoपूर्णांक_unregfunc(व्योम)
अणु
	अटल_key_slow_dec(&hcall_tracepoपूर्णांक_key);
पूर्ण
#अन्यथा
/*
 * We optimise our hcall path by placing hcall_tracepoपूर्णांक_refcount
 * directly in the TOC so we can check अगर the hcall tracepoपूर्णांकs are
 * enabled via a single load.
 */

/* NB: reg/unreg are called जबतक guarded with the tracepoपूर्णांकs_mutex */
बाह्य दीर्घ hcall_tracepoपूर्णांक_refcount;

पूर्णांक hcall_tracepoपूर्णांक_regfunc(व्योम)
अणु
	hcall_tracepoपूर्णांक_refcount++;
	वापस 0;
पूर्ण

व्योम hcall_tracepoपूर्णांक_unregfunc(व्योम)
अणु
	hcall_tracepoपूर्णांक_refcount--;
पूर्ण
#पूर्ण_अगर

/*
 * Keep track of hcall tracing depth and prevent recursion. Warn अगर any is
 * detected because it may indicate a problem. This will not catch all
 * problems with tracing code making hcalls, because the tracing might have
 * been invoked from a non-hcall, so the first hcall could recurse पूर्णांकo it
 * without warning here, but this better than nothing.
 *
 * Hcalls with specअगरic problems being traced should use the _notrace
 * plpar_hcall variants.
 */
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, hcall_trace_depth);


notrace व्योम __trace_hcall_entry(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *args)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक *depth;

	local_irq_save(flags);

	depth = this_cpu_ptr(&hcall_trace_depth);

	अगर (WARN_ON_ONCE(*depth))
		जाओ out;

	(*depth)++;
	preempt_disable();
	trace_hcall_entry(opcode, args);
	(*depth)--;

out:
	local_irq_restore(flags);
पूर्ण

notrace व्योम __trace_hcall_निकास(दीर्घ opcode, दीर्घ retval, अचिन्हित दीर्घ *retbuf)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक *depth;

	local_irq_save(flags);

	depth = this_cpu_ptr(&hcall_trace_depth);

	अगर (*depth) /* Don't warn again on the way out */
		जाओ out;

	(*depth)++;
	trace_hcall_निकास(opcode, retval, retbuf);
	preempt_enable();
	(*depth)--;

out:
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर

/**
 * h_get_mpp
 * H_GET_MPP hcall वापसs info in 7 parms
 */
पूर्णांक h_get_mpp(काष्ठा hvcall_mpp_data *mpp_data)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE];

	rc = plpar_hcall9(H_GET_MPP, retbuf);

	mpp_data->entitled_mem = retbuf[0];
	mpp_data->mapped_mem = retbuf[1];

	mpp_data->group_num = (retbuf[2] >> 2 * 8) & 0xffff;
	mpp_data->pool_num = retbuf[2] & 0xffff;

	mpp_data->mem_weight = (retbuf[3] >> 7 * 8) & 0xff;
	mpp_data->unallocated_mem_weight = (retbuf[3] >> 6 * 8) & 0xff;
	mpp_data->unallocated_entitlement = retbuf[3] & 0xffffffffffffUL;

	mpp_data->pool_size = retbuf[4];
	mpp_data->loan_request = retbuf[5];
	mpp_data->backing_mem = retbuf[6];

	वापस rc;
पूर्ण
EXPORT_SYMBOL(h_get_mpp);

पूर्णांक h_get_mpp_x(काष्ठा hvcall_mpp_x_data *mpp_x_data)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL9_बफ_मानE] = अणु 0 पूर्ण;

	rc = plpar_hcall9(H_GET_MPP_X, retbuf);

	mpp_x_data->coalesced_bytes = retbuf[0];
	mpp_x_data->pool_coalesced_bytes = retbuf[1];
	mpp_x_data->pool_purr_cycles = retbuf[2];
	mpp_x_data->pool_spurr_cycles = retbuf[3];

	वापस rc;
पूर्ण

अटल अचिन्हित दीर्घ vsid_unscramble(अचिन्हित दीर्घ vsid, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ protovsid;
	अचिन्हित दीर्घ va_bits = VA_BITS;
	अचिन्हित दीर्घ modinv, vsid_modulus;
	अचिन्हित दीर्घ max_mod_inv, पंचांगp_modinv;

	अगर (!mmu_has_feature(MMU_FTR_68_BIT_VA))
		va_bits = 65;

	अगर (ssize == MMU_SEGSIZE_256M) अणु
		modinv = VSID_MULINV_256M;
		vsid_modulus = ((1UL << (va_bits - SID_SHIFT)) - 1);
	पूर्ण अन्यथा अणु
		modinv = VSID_MULINV_1T;
		vsid_modulus = ((1UL << (va_bits - SID_SHIFT_1T)) - 1);
	पूर्ण

	/*
	 * vsid outside our range.
	 */
	अगर (vsid >= vsid_modulus)
		वापस 0;

	/*
	 * If modinv is the modular multiplicate inverse of (x % vsid_modulus)
	 * and vsid = (protovsid * x) % vsid_modulus, then we say:
	 *   protovsid = (vsid * modinv) % vsid_modulus
	 */

	/* Check अगर (vsid * modinv) overflow (63 bits) */
	max_mod_inv = 0x7fffffffffffffffull / vsid;
	अगर (modinv < max_mod_inv)
		वापस (vsid * modinv) % vsid_modulus;

	पंचांगp_modinv = modinv/max_mod_inv;
	modinv %= max_mod_inv;

	protovsid = (((vsid * max_mod_inv) % vsid_modulus) * पंचांगp_modinv) % vsid_modulus;
	protovsid = (protovsid + vsid * modinv) % vsid_modulus;

	वापस protovsid;
पूर्ण

अटल पूर्णांक __init reserve_vrma_context_id(व्योम)
अणु
	अचिन्हित दीर्घ protovsid;

	/*
	 * Reserve context ids which map to reserved भव addresses. For now
	 * we only reserve the context id which maps to the VRMA VSID. We ignore
	 * the addresses in "ibm,adjunct-virtual-addresses" because we करोn't
	 * enable adjunct support via the "ibm,client-architecture-support"
	 * पूर्णांकerface.
	 */
	protovsid = vsid_unscramble(VRMA_VSID, MMU_SEGSIZE_1T);
	hash__reserve_context_id(protovsid >> ESID_BITS_1T);
	वापस 0;
पूर्ण
machine_device_initcall(pseries, reserve_vrma_context_id);

#अगर_घोषित CONFIG_DEBUG_FS
/* debugfs file पूर्णांकerface क्रम vpa data */
अटल sमाप_प्रकार vpa_file_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार len,
			      loff_t *pos)
अणु
	पूर्णांक cpu = (दीर्घ)filp->निजी_data;
	काष्ठा lppaca *lppaca = &lppaca_of(cpu);

	वापस simple_पढ़ो_from_buffer(buf, len, pos, lppaca,
				माप(काष्ठा lppaca));
पूर्ण

अटल स्थिर काष्ठा file_operations vpa_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= vpa_file_पढ़ो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल पूर्णांक __init vpa_debugfs_init(व्योम)
अणु
	अक्षर name[16];
	दीर्घ i;
	काष्ठा dentry *vpa_dir;

	अगर (!firmware_has_feature(FW_FEATURE_SPLPAR))
		वापस 0;

	vpa_dir = debugfs_create_dir("vpa", घातerpc_debugfs_root);

	/* set up the per-cpu vpa file*/
	क्रम_each_possible_cpu(i) अणु
		प्र_लिखो(name, "cpu-%ld", i);
		debugfs_create_file(name, 0400, vpa_dir, (व्योम *)i, &vpa_fops);
	पूर्ण

	वापस 0;
पूर्ण
machine_arch_initcall(pseries, vpa_debugfs_init);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
