<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/kernel/profile.c
 *  Simple profiling. Manages a direct-mapped profile hit count buffer,
 *  with configurable resolution, support क्रम restricting the cpus on
 *  which profiling is करोne, and चयनing between cpu समय and
 *  schedule() calls via kernel command line parameters passed at boot.
 *
 *  Scheduler profiling support, Arjan van de Ven and Ingo Molnar,
 *	Red Hat, July 2004
 *  Consolidation of architecture support code क्रम profiling,
 *	Nadia Yvette Chambers, Oracle, July 2004
 *  Amortized hit count accounting via per-cpu खोलो-addressed hashtables
 *	to resolve समयr पूर्णांकerrupt livelocks, Nadia Yvette Chambers,
 *	Oracle, 2004
 */

#समावेश <linux/export.h>
#समावेश <linux/profile.h>
#समावेश <linux/memblock.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/स्थिति.स>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/ptrace.h>

काष्ठा profile_hit अणु
	u32 pc, hits;
पूर्ण;
#घोषणा PROखाता_GRPSHIFT	3
#घोषणा PROखाता_GRPSZ		(1 << PROखाता_GRPSHIFT)
#घोषणा NR_PROखाता_HIT		(PAGE_SIZE/माप(काष्ठा profile_hit))
#घोषणा NR_PROखाता_GRP		(NR_PROखाता_HIT/PROखाता_GRPSZ)

अटल atomic_t *prof_buffer;
अटल अचिन्हित दीर्घ prof_len, prof_shअगरt;

पूर्णांक prof_on __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(prof_on);

अटल cpumask_var_t prof_cpu_mask;
#अगर defined(CONFIG_SMP) && defined(CONFIG_PROC_FS)
अटल DEFINE_PER_CPU(काष्ठा profile_hit *[2], cpu_profile_hits);
अटल DEFINE_PER_CPU(पूर्णांक, cpu_profile_flip);
अटल DEFINE_MUTEX(profile_flip_mutex);
#पूर्ण_अगर /* CONFIG_SMP */

पूर्णांक profile_setup(अक्षर *str)
अणु
	अटल स्थिर अक्षर schedstr[] = "schedule";
	अटल स्थिर अक्षर sleepstr[] = "sleep";
	अटल स्थिर अक्षर kvmstr[] = "kvm";
	पूर्णांक par;

	अगर (!म_भेदन(str, sleepstr, म_माप(sleepstr))) अणु
#अगर_घोषित CONFIG_SCHEDSTATS
		क्रमce_schedstat_enabled();
		prof_on = SLEEP_PROFILING;
		अगर (str[म_माप(sleepstr)] == ',')
			str += म_माप(sleepstr) + 1;
		अगर (get_option(&str, &par))
			prof_shअगरt = par;
		pr_info("kernel sleep profiling enabled (shift: %ld)\n",
			prof_shअगरt);
#अन्यथा
		pr_warn("kernel sleep profiling requires CONFIG_SCHEDSTATS\n");
#पूर्ण_अगर /* CONFIG_SCHEDSTATS */
	पूर्ण अन्यथा अगर (!म_भेदन(str, schedstr, म_माप(schedstr))) अणु
		prof_on = SCHED_PROFILING;
		अगर (str[म_माप(schedstr)] == ',')
			str += म_माप(schedstr) + 1;
		अगर (get_option(&str, &par))
			prof_shअगरt = par;
		pr_info("kernel schedule profiling enabled (shift: %ld)\n",
			prof_shअगरt);
	पूर्ण अन्यथा अगर (!म_भेदन(str, kvmstr, म_माप(kvmstr))) अणु
		prof_on = KVM_PROFILING;
		अगर (str[म_माप(kvmstr)] == ',')
			str += म_माप(kvmstr) + 1;
		अगर (get_option(&str, &par))
			prof_shअगरt = par;
		pr_info("kernel KVM profiling enabled (shift: %ld)\n",
			prof_shअगरt);
	पूर्ण अन्यथा अगर (get_option(&str, &par)) अणु
		prof_shअगरt = par;
		prof_on = CPU_PROFILING;
		pr_info("kernel profiling enabled (shift: %ld)\n",
			prof_shअगरt);
	पूर्ण
	वापस 1;
पूर्ण
__setup("profile=", profile_setup);


पूर्णांक __ref profile_init(व्योम)
अणु
	पूर्णांक buffer_bytes;
	अगर (!prof_on)
		वापस 0;

	/* only text is profiled */
	prof_len = (_etext - _stext) >> prof_shअगरt;
	buffer_bytes = prof_len*माप(atomic_t);

	अगर (!alloc_cpumask_var(&prof_cpu_mask, GFP_KERNEL))
		वापस -ENOMEM;

	cpumask_copy(prof_cpu_mask, cpu_possible_mask);

	prof_buffer = kzalloc(buffer_bytes, GFP_KERNEL|__GFP_NOWARN);
	अगर (prof_buffer)
		वापस 0;

	prof_buffer = alloc_pages_exact(buffer_bytes,
					GFP_KERNEL|__GFP_ZERO|__GFP_NOWARN);
	अगर (prof_buffer)
		वापस 0;

	prof_buffer = vzalloc(buffer_bytes);
	अगर (prof_buffer)
		वापस 0;

	मुक्त_cpumask_var(prof_cpu_mask);
	वापस -ENOMEM;
पूर्ण

/* Profile event notअगरications */

अटल BLOCKING_NOTIFIER_HEAD(task_निकास_notअगरier);
अटल ATOMIC_NOTIFIER_HEAD(task_मुक्त_notअगरier);
अटल BLOCKING_NOTIFIER_HEAD(munmap_notअगरier);

व्योम profile_task_निकास(काष्ठा task_काष्ठा *task)
अणु
	blocking_notअगरier_call_chain(&task_निकास_notअगरier, 0, task);
पूर्ण

पूर्णांक profile_hanकरोff_task(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक ret;
	ret = atomic_notअगरier_call_chain(&task_मुक्त_notअगरier, 0, task);
	वापस (ret == NOTIFY_OK) ? 1 : 0;
पूर्ण

व्योम profile_munmap(अचिन्हित दीर्घ addr)
अणु
	blocking_notअगरier_call_chain(&munmap_notअगरier, 0, (व्योम *)addr);
पूर्ण

पूर्णांक task_hanकरोff_रेजिस्टर(काष्ठा notअगरier_block *n)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&task_मुक्त_notअगरier, n);
पूर्ण
EXPORT_SYMBOL_GPL(task_hanकरोff_रेजिस्टर);

पूर्णांक task_hanकरोff_unरेजिस्टर(काष्ठा notअगरier_block *n)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&task_मुक्त_notअगरier, n);
पूर्ण
EXPORT_SYMBOL_GPL(task_hanकरोff_unरेजिस्टर);

पूर्णांक profile_event_रेजिस्टर(क्रमागत profile_type type, काष्ठा notअगरier_block *n)
अणु
	पूर्णांक err = -EINVAL;

	चयन (type) अणु
	हाल PROखाता_TASK_EXIT:
		err = blocking_notअगरier_chain_रेजिस्टर(
				&task_निकास_notअगरier, n);
		अवरोध;
	हाल PROखाता_MUNMAP:
		err = blocking_notअगरier_chain_रेजिस्टर(
				&munmap_notअगरier, n);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(profile_event_रेजिस्टर);

पूर्णांक profile_event_unरेजिस्टर(क्रमागत profile_type type, काष्ठा notअगरier_block *n)
अणु
	पूर्णांक err = -EINVAL;

	चयन (type) अणु
	हाल PROखाता_TASK_EXIT:
		err = blocking_notअगरier_chain_unरेजिस्टर(
				&task_निकास_notअगरier, n);
		अवरोध;
	हाल PROखाता_MUNMAP:
		err = blocking_notअगरier_chain_unरेजिस्टर(
				&munmap_notअगरier, n);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(profile_event_unरेजिस्टर);

#अगर defined(CONFIG_SMP) && defined(CONFIG_PROC_FS)
/*
 * Each cpu has a pair of खोलो-addressed hashtables क्रम pending
 * profile hits. पढ़ो_profile() IPI's all cpus to request them
 * to flip buffers and flushes their contents to prof_buffer itself.
 * Flip requests are serialized by the profile_flip_mutex. The sole
 * use of having a second hashtable is क्रम aव्योमing cacheline
 * contention that would otherwise happen during flushes of pending
 * profile hits required क्रम the accuracy of reported profile hits
 * and so resurrect the पूर्णांकerrupt livelock issue.
 *
 * The खोलो-addressed hashtables are indexed by profile buffer slot
 * and hold the number of pending hits to that profile buffer slot on
 * a cpu in an entry. When the hashtable overflows, all pending hits
 * are accounted to their corresponding profile buffer slots with
 * atomic_add() and the hashtable emptied. As numerous pending hits
 * may be accounted to a profile buffer slot in a hashtable entry,
 * this amortizes a number of atomic profile buffer increments likely
 * to be far larger than the number of entries in the hashtable,
 * particularly given that the number of distinct profile buffer
 * positions to which hits are accounted during लघु पूर्णांकervals (e.g.
 * several seconds) is usually very small. Exclusion from buffer
 * flipping is provided by पूर्णांकerrupt disablement (note that क्रम
 * SCHED_PROFILING or SLEEP_PROFILING profile_hit() may be called from
 * process context).
 * The hash function is meant to be lightweight as opposed to strong,
 * and was vaguely inspired by ppc64 firmware-supported inverted
 * pagetable hash functions, but uses a full hashtable full of finite
 * collision chains, not just pairs of them.
 *
 * -- nyc
 */
अटल व्योम __profile_flip_buffers(व्योम *unused)
अणु
	पूर्णांक cpu = smp_processor_id();

	per_cpu(cpu_profile_flip, cpu) = !per_cpu(cpu_profile_flip, cpu);
पूर्ण

अटल व्योम profile_flip_buffers(व्योम)
अणु
	पूर्णांक i, j, cpu;

	mutex_lock(&profile_flip_mutex);
	j = per_cpu(cpu_profile_flip, get_cpu());
	put_cpu();
	on_each_cpu(__profile_flip_buffers, शून्य, 1);
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा profile_hit *hits = per_cpu(cpu_profile_hits, cpu)[j];
		क्रम (i = 0; i < NR_PROखाता_HIT; ++i) अणु
			अगर (!hits[i].hits) अणु
				अगर (hits[i].pc)
					hits[i].pc = 0;
				जारी;
			पूर्ण
			atomic_add(hits[i].hits, &prof_buffer[hits[i].pc]);
			hits[i].hits = hits[i].pc = 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&profile_flip_mutex);
पूर्ण

अटल व्योम profile_discard_flip_buffers(व्योम)
अणु
	पूर्णांक i, cpu;

	mutex_lock(&profile_flip_mutex);
	i = per_cpu(cpu_profile_flip, get_cpu());
	put_cpu();
	on_each_cpu(__profile_flip_buffers, शून्य, 1);
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा profile_hit *hits = per_cpu(cpu_profile_hits, cpu)[i];
		स_रखो(hits, 0, NR_PROखाता_HIT*माप(काष्ठा profile_hit));
	पूर्ण
	mutex_unlock(&profile_flip_mutex);
पूर्ण

अटल व्योम करो_profile_hits(पूर्णांक type, व्योम *__pc, अचिन्हित पूर्णांक nr_hits)
अणु
	अचिन्हित दीर्घ primary, secondary, flags, pc = (अचिन्हित दीर्घ)__pc;
	पूर्णांक i, j, cpu;
	काष्ठा profile_hit *hits;

	pc = min((pc - (अचिन्हित दीर्घ)_stext) >> prof_shअगरt, prof_len - 1);
	i = primary = (pc & (NR_PROखाता_GRP - 1)) << PROखाता_GRPSHIFT;
	secondary = (~(pc << 1) & (NR_PROखाता_GRP - 1)) << PROखाता_GRPSHIFT;
	cpu = get_cpu();
	hits = per_cpu(cpu_profile_hits, cpu)[per_cpu(cpu_profile_flip, cpu)];
	अगर (!hits) अणु
		put_cpu();
		वापस;
	पूर्ण
	/*
	 * We buffer the global profiler buffer पूर्णांकo a per-CPU
	 * queue and thus reduce the number of global (and possibly
	 * NUMA-alien) accesses. The ग_लिखो-queue is self-coalescing:
	 */
	local_irq_save(flags);
	करो अणु
		क्रम (j = 0; j < PROखाता_GRPSZ; ++j) अणु
			अगर (hits[i + j].pc == pc) अणु
				hits[i + j].hits += nr_hits;
				जाओ out;
			पूर्ण अन्यथा अगर (!hits[i + j].hits) अणु
				hits[i + j].pc = pc;
				hits[i + j].hits = nr_hits;
				जाओ out;
			पूर्ण
		पूर्ण
		i = (i + secondary) & (NR_PROखाता_HIT - 1);
	पूर्ण जबतक (i != primary);

	/*
	 * Add the current hit(s) and flush the ग_लिखो-queue out
	 * to the global buffer:
	 */
	atomic_add(nr_hits, &prof_buffer[pc]);
	क्रम (i = 0; i < NR_PROखाता_HIT; ++i) अणु
		atomic_add(hits[i].hits, &prof_buffer[hits[i].pc]);
		hits[i].pc = hits[i].hits = 0;
	पूर्ण
out:
	local_irq_restore(flags);
	put_cpu();
पूर्ण

अटल पूर्णांक profile_dead_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा page *page;
	पूर्णांक i;

	अगर (cpumask_available(prof_cpu_mask))
		cpumask_clear_cpu(cpu, prof_cpu_mask);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (per_cpu(cpu_profile_hits, cpu)[i]) अणु
			page = virt_to_page(per_cpu(cpu_profile_hits, cpu)[i]);
			per_cpu(cpu_profile_hits, cpu)[i] = शून्य;
			__मुक्त_page(page);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक profile_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i, node = cpu_to_mem(cpu);
	काष्ठा page *page;

	per_cpu(cpu_profile_flip, cpu) = 0;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (per_cpu(cpu_profile_hits, cpu)[i])
			जारी;

		page = __alloc_pages_node(node, GFP_KERNEL | __GFP_ZERO, 0);
		अगर (!page) अणु
			profile_dead_cpu(cpu);
			वापस -ENOMEM;
		पूर्ण
		per_cpu(cpu_profile_hits, cpu)[i] = page_address(page);

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक profile_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpumask_available(prof_cpu_mask))
		cpumask_set_cpu(cpu, prof_cpu_mask);

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_SMP */
#घोषणा profile_flip_buffers()		करो अणु पूर्ण जबतक (0)
#घोषणा profile_discard_flip_buffers()	करो अणु पूर्ण जबतक (0)

अटल व्योम करो_profile_hits(पूर्णांक type, व्योम *__pc, अचिन्हित पूर्णांक nr_hits)
अणु
	अचिन्हित दीर्घ pc;
	pc = ((अचिन्हित दीर्घ)__pc - (अचिन्हित दीर्घ)_stext) >> prof_shअगरt;
	atomic_add(nr_hits, &prof_buffer[min(pc, prof_len - 1)]);
पूर्ण
#पूर्ण_अगर /* !CONFIG_SMP */

व्योम profile_hits(पूर्णांक type, व्योम *__pc, अचिन्हित पूर्णांक nr_hits)
अणु
	अगर (prof_on != type || !prof_buffer)
		वापस;
	करो_profile_hits(type, __pc, nr_hits);
पूर्ण
EXPORT_SYMBOL_GPL(profile_hits);

व्योम profile_tick(पूर्णांक type)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();

	अगर (!user_mode(regs) && cpumask_available(prof_cpu_mask) &&
	    cpumask_test_cpu(smp_processor_id(), prof_cpu_mask))
		profile_hit(type, (व्योम *)profile_pc(regs));
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>

अटल पूर्णांक prof_cpu_mask_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%*pb\n", cpumask_pr_args(prof_cpu_mask));
	वापस 0;
पूर्ण

अटल पूर्णांक prof_cpu_mask_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, prof_cpu_mask_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार prof_cpu_mask_proc_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	cpumask_var_t new_value;
	पूर्णांक err;

	अगर (!zalloc_cpumask_var(&new_value, GFP_KERNEL))
		वापस -ENOMEM;

	err = cpumask_parse_user(buffer, count, new_value);
	अगर (!err) अणु
		cpumask_copy(prof_cpu_mask, new_value);
		err = count;
	पूर्ण
	मुक्त_cpumask_var(new_value);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा proc_ops prof_cpu_mask_proc_ops = अणु
	.proc_खोलो	= prof_cpu_mask_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= prof_cpu_mask_proc_ग_लिखो,
पूर्ण;

व्योम create_prof_cpu_mask(व्योम)
अणु
	/* create /proc/irq/prof_cpu_mask */
	proc_create("irq/prof_cpu_mask", 0600, शून्य, &prof_cpu_mask_proc_ops);
पूर्ण

/*
 * This function accesses profiling inक्रमmation. The वापसed data is
 * binary: the sampling step and the actual contents of the profile
 * buffer. Use of the program पढ़ोprofile is recommended in order to
 * get meaningful info out of these data.
 */
अटल sमाप_प्रकार
पढ़ो_profile(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ p = *ppos;
	sमाप_प्रकार पढ़ो;
	अक्षर *pnt;
	अचिन्हित पूर्णांक sample_step = 1 << prof_shअगरt;

	profile_flip_buffers();
	अगर (p >= (prof_len+1)*माप(अचिन्हित पूर्णांक))
		वापस 0;
	अगर (count > (prof_len+1)*माप(अचिन्हित पूर्णांक) - p)
		count = (prof_len+1)*माप(अचिन्हित पूर्णांक) - p;
	पढ़ो = 0;

	जबतक (p < माप(अचिन्हित पूर्णांक) && count > 0) अणु
		अगर (put_user(*((अक्षर *)(&sample_step)+p), buf))
			वापस -EFAULT;
		buf++; p++; count--; पढ़ो++;
	पूर्ण
	pnt = (अक्षर *)prof_buffer + p - माप(atomic_t);
	अगर (copy_to_user(buf, (व्योम *)pnt, count))
		वापस -EFAULT;
	पढ़ो += count;
	*ppos += पढ़ो;
	वापस पढ़ो;
पूर्ण

/*
 * Writing to /proc/profile resets the counters
 *
 * Writing a 'profiling multiplier' value पूर्णांकo it also re-sets the profiling
 * पूर्णांकerrupt frequency, on architectures that support this.
 */
अटल sमाप_प्रकार ग_लिखो_profile(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
#अगर_घोषित CONFIG_SMP
	बाह्य पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier);

	अगर (count == माप(पूर्णांक)) अणु
		अचिन्हित पूर्णांक multiplier;

		अगर (copy_from_user(&multiplier, buf, माप(पूर्णांक)))
			वापस -EFAULT;

		अगर (setup_profiling_समयr(multiplier))
			वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
	profile_discard_flip_buffers();
	स_रखो(prof_buffer, 0, prof_len * माप(atomic_t));
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops profile_proc_ops = अणु
	.proc_पढ़ो	= पढ़ो_profile,
	.proc_ग_लिखो	= ग_लिखो_profile,
	.proc_lseek	= शेष_llseek,
पूर्ण;

पूर्णांक __ref create_proc_profile(व्योम)
अणु
	काष्ठा proc_dir_entry *entry;
#अगर_घोषित CONFIG_SMP
	क्रमागत cpuhp_state online_state;
#पूर्ण_अगर

	पूर्णांक err = 0;

	अगर (!prof_on)
		वापस 0;
#अगर_घोषित CONFIG_SMP
	err = cpuhp_setup_state(CPUHP_PROखाता_PREPARE, "PROFILE_PREPARE",
				profile_prepare_cpu, profile_dead_cpu);
	अगर (err)
		वापस err;

	err = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "AP_PROFILE_ONLINE",
				profile_online_cpu, शून्य);
	अगर (err < 0)
		जाओ err_state_prep;
	online_state = err;
	err = 0;
#पूर्ण_अगर
	entry = proc_create("profile", S_IWUSR | S_IRUGO,
			    शून्य, &profile_proc_ops);
	अगर (!entry)
		जाओ err_state_onl;
	proc_set_size(entry, (1 + prof_len) * माप(atomic_t));

	वापस err;
err_state_onl:
#अगर_घोषित CONFIG_SMP
	cpuhp_हटाओ_state(online_state);
err_state_prep:
	cpuhp_हटाओ_state(CPUHP_PROखाता_PREPARE);
#पूर्ण_अगर
	वापस err;
पूर्ण
subsys_initcall(create_proc_profile);
#पूर्ण_अगर /* CONFIG_PROC_FS */
