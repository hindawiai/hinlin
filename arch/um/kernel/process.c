<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Anton Ivanov (aivanov@अणुbrocade.com,kot-begemot.co.ukपूर्ण)
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright 2003 PathScale, Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/err.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/personality.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/tick.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/tracehook.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <linux/uaccess.h>
#समावेश <as-layout.h>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <skas.h>
#समावेश <linux/समय-पूर्णांकernal.h>

/*
 * This is a per-cpu array.  A processor only modअगरies its entry and it only
 * cares about its entry, so it's OK अगर another processor is modअगरying its
 * entry.
 */
काष्ठा cpu_task cpu_tasks[NR_CPUS] = अणु [0 ... NR_CPUS - 1] = अणु -1, शून्य पूर्ण पूर्ण;

अटल अंतरभूत पूर्णांक बाह्यal_pid(व्योम)
अणु
	/* FIXME: Need to look up userspace_pid by cpu */
	वापस userspace_pid[0];
पूर्ण

पूर्णांक pid_to_processor_id(पूर्णांक pid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ncpus; i++) अणु
		अगर (cpu_tasks[i].pid == pid)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

व्योम मुक्त_stack(अचिन्हित दीर्घ stack, पूर्णांक order)
अणु
	मुक्त_pages(stack, order);
पूर्ण

अचिन्हित दीर्घ alloc_stack(पूर्णांक order, पूर्णांक atomic)
अणु
	अचिन्हित दीर्घ page;
	gfp_t flags = GFP_KERNEL;

	अगर (atomic)
		flags = GFP_ATOMIC;
	page = __get_मुक्त_pages(flags, order);

	वापस page;
पूर्ण

अटल अंतरभूत व्योम set_current(काष्ठा task_काष्ठा *task)
अणु
	cpu_tasks[task_thपढ़ो_info(task)->cpu] = ((काष्ठा cpu_task)
		अणु बाह्यal_pid(), task पूर्ण);
पूर्ण

बाह्य व्योम arch_चयन_to(काष्ठा task_काष्ठा *to);

व्योम *__चयन_to(काष्ठा task_काष्ठा *from, काष्ठा task_काष्ठा *to)
अणु
	to->thपढ़ो.prev_sched = from;
	set_current(to);

	चयन_thपढ़ोs(&from->thपढ़ो.चयन_buf, &to->thपढ़ो.चयन_buf);
	arch_चयन_to(current);

	वापस current->thपढ़ो.prev_sched;
पूर्ण

व्योम पूर्णांकerrupt_end(व्योम)
अणु
	काष्ठा pt_regs *regs = &current->thपढ़ो.regs;

	अगर (need_resched())
		schedule();
	अगर (test_thपढ़ो_flag(TIF_SIGPENDING) ||
	    test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs);
	अगर (test_thपढ़ो_flag(TIF_NOTIFY_RESUME))
		tracehook_notअगरy_resume(regs);
पूर्ण

पूर्णांक get_current_pid(व्योम)
अणु
	वापस task_pid_nr(current);
पूर्ण

/*
 * This is called magically, by its address being stuffed in a लाँघ_बफ
 * and being दीर्घ_लाँघ-d to.
 */
व्योम new_thपढ़ो_handler(व्योम)
अणु
	पूर्णांक (*fn)(व्योम *), n;
	व्योम *arg;

	अगर (current->thपढ़ो.prev_sched != शून्य)
		schedule_tail(current->thपढ़ो.prev_sched);
	current->thपढ़ो.prev_sched = शून्य;

	fn = current->thपढ़ो.request.u.thपढ़ो.proc;
	arg = current->thपढ़ो.request.u.thपढ़ो.arg;

	/*
	 * callback वापसs only अगर the kernel thपढ़ो execs a process
	 */
	n = fn(arg);
	userspace(&current->thपढ़ो.regs.regs, current_thपढ़ो_info()->aux_fp_regs);
पूर्ण

/* Called magically, see new_thपढ़ो_handler above */
व्योम विभाजन_handler(व्योम)
अणु
	क्रमce_flush_all();

	schedule_tail(current->thपढ़ो.prev_sched);

	/*
	 * XXX: अगर पूर्णांकerrupt_end() calls schedule, this call to
	 * arch_चयन_to isn't needed. We could want to apply this to
	 * improve perक्रमmance. -bb
	 */
	arch_चयन_to(current);

	current->thपढ़ो.prev_sched = शून्य;

	userspace(&current->thपढ़ो.regs.regs, current_thपढ़ो_info()->aux_fp_regs);
पूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ sp,
		अचिन्हित दीर्घ arg, काष्ठा task_काष्ठा * p, अचिन्हित दीर्घ tls)
अणु
	व्योम (*handler)(व्योम);
	पूर्णांक kthपढ़ो = current->flags & (PF_KTHREAD | PF_IO_WORKER);
	पूर्णांक ret = 0;

	p->thपढ़ो = (काष्ठा thपढ़ो_काष्ठा) INIT_THREAD;

	अगर (!kthपढ़ो) अणु
	  	स_नकल(&p->thपढ़ो.regs.regs, current_pt_regs(),
		       माप(p->thपढ़ो.regs.regs));
		PT_REGS_SET_SYSCALL_RETURN(&p->thपढ़ो.regs, 0);
		अगर (sp != 0)
			REGS_SP(p->thपढ़ो.regs.regs.gp) = sp;

		handler = विभाजन_handler;

		arch_copy_thपढ़ो(&current->thपढ़ो.arch, &p->thपढ़ो.arch);
	पूर्ण अन्यथा अणु
		get_safe_रेजिस्टरs(p->thपढ़ो.regs.regs.gp, p->thपढ़ो.regs.regs.fp);
		p->thपढ़ो.request.u.thपढ़ो.proc = (पूर्णांक (*)(व्योम *))sp;
		p->thपढ़ो.request.u.thपढ़ो.arg = (व्योम *)arg;
		handler = new_thपढ़ो_handler;
	पूर्ण

	new_thपढ़ो(task_stack_page(p), &p->thपढ़ो.चयन_buf, handler);

	अगर (!kthपढ़ो) अणु
		clear_flushed_tls(p);

		/*
		 * Set a new TLS क्रम the child thपढ़ो?
		 */
		अगर (clone_flags & CLONE_SETTLS)
			ret = arch_set_tls(p, tls);
	पूर्ण

	वापस ret;
पूर्ण

व्योम initial_thपढ़ो_cb(व्योम (*proc)(व्योम *), व्योम *arg)
अणु
	पूर्णांक save_kदो_स्मृति_ok = kदो_स्मृति_ok;

	kदो_स्मृति_ok = 0;
	initial_thपढ़ो_cb_skas(proc, arg);
	kदो_स्मृति_ok = save_kदो_स्मृति_ok;
पूर्ण

व्योम um_idle_sleep(व्योम)
अणु
	अगर (समय_प्रकारravel_mode != TT_MODE_OFF)
		समय_प्रकारravel_sleep();
	अन्यथा
		os_idle_sleep();
पूर्ण

व्योम arch_cpu_idle(व्योम)
अणु
	cpu_tasks[current_thपढ़ो_info()->cpu].pid = os_getpid();
	um_idle_sleep();
	raw_local_irq_enable();
पूर्ण

पूर्णांक __cant_sleep(व्योम) अणु
	वापस in_atomic() || irqs_disabled() || in_पूर्णांकerrupt();
	/* Is in_पूर्णांकerrupt() really needed? */
पूर्ण

पूर्णांक user_context(अचिन्हित दीर्घ sp)
अणु
	अचिन्हित दीर्घ stack;

	stack = sp & (PAGE_MASK << CONFIG_KERNEL_STACK_ORDER);
	वापस stack != (अचिन्हित दीर्घ) current_thपढ़ो_info();
पूर्ण

बाह्य निकासcall_t __uml_निकासcall_begin, __uml_निकासcall_end;

व्योम करो_uml_निकासcalls(व्योम)
अणु
	निकासcall_t *call;

	call = &__uml_निकासcall_end;
	जबतक (--call >= &__uml_निकासcall_begin)
		(*call)();
पूर्ण

अक्षर *uml_strdup(स्थिर अक्षर *string)
अणु
	वापस kstrdup(string, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(uml_strdup);

पूर्णांक copy_to_user_proc(व्योम __user *to, व्योम *from, पूर्णांक size)
अणु
	वापस copy_to_user(to, from, size);
पूर्ण

पूर्णांक copy_from_user_proc(व्योम *to, व्योम __user *from, पूर्णांक size)
अणु
	वापस copy_from_user(to, from, size);
पूर्ण

पूर्णांक clear_user_proc(व्योम __user *buf, पूर्णांक size)
अणु
	वापस clear_user(buf, size);
पूर्ण

पूर्णांक cpu(व्योम)
अणु
	वापस current_thपढ़ो_info()->cpu;
पूर्ण

अटल atomic_t using_sysemu = ATOMIC_INIT(0);
पूर्णांक sysemu_supported;

व्योम set_using_sysemu(पूर्णांक value)
अणु
	अगर (value > sysemu_supported)
		वापस;
	atomic_set(&using_sysemu, value);
पूर्ण

पूर्णांक get_using_sysemu(व्योम)
अणु
	वापस atomic_पढ़ो(&using_sysemu);
पूर्ण

अटल पूर्णांक sysemu_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%d\n", get_using_sysemu());
	वापस 0;
पूर्ण

अटल पूर्णांक sysemu_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, sysemu_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार sysemu_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *pos)
अणु
	अक्षर पंचांगp[2];

	अगर (copy_from_user(पंचांगp, buf, 1))
		वापस -EFAULT;

	अगर (पंचांगp[0] >= '0' && tmp[0] <= '2')
		set_using_sysemu(पंचांगp[0] - '0');
	/* We use the first अक्षर, but pretend to ग_लिखो everything */
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops sysemu_proc_ops = अणु
	.proc_खोलो	= sysemu_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= sysemu_proc_ग_लिखो,
पूर्ण;

पूर्णांक __init make_proc_sysemu(व्योम)
अणु
	काष्ठा proc_dir_entry *ent;
	अगर (!sysemu_supported)
		वापस 0;

	ent = proc_create("sysemu", 0600, शून्य, &sysemu_proc_ops);

	अगर (ent == शून्य)
	अणु
		prपूर्णांकk(KERN_WARNING "Failed to register /proc/sysemu\n");
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

late_initcall(make_proc_sysemu);

पूर्णांक singlestepping(व्योम * t)
अणु
	काष्ठा task_काष्ठा *task = t ? t : current;

	अगर (!(task->ptrace & PT_DTRACE))
		वापस 0;

	अगर (task->thपढ़ो.singlestep_syscall)
		वापस 1;

	वापस 2;
पूर्ण

/*
 * Only x86 and x86_64 have an arch_align_stack().
 * All other arches have "#define arch_align_stack(x) (x)"
 * in their यंत्र/exec.h
 * As this is included in UML from यंत्र-um/प्रणाली-generic.h,
 * we can use it to behave as the subarch करोes.
 */
#अगर_अघोषित arch_align_stack
अचिन्हित दीर्घ arch_align_stack(अचिन्हित दीर्घ sp)
अणु
	अगर (!(current->personality & ADDR_NO_RANDOMIZE) && अक्रमomize_va_space)
		sp -= get_अक्रमom_पूर्णांक() % 8192;
	वापस sp & ~0xf;
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ stack_page, sp, ip;
	bool seen_sched = 0;

	अगर ((p == शून्य) || (p == current) || (p->state == TASK_RUNNING))
		वापस 0;

	stack_page = (अचिन्हित दीर्घ) task_stack_page(p);
	/* Bail अगर the process has no kernel stack क्रम some reason */
	अगर (stack_page == 0)
		वापस 0;

	sp = p->thपढ़ो.चयन_buf->JB_SP;
	/*
	 * Bail अगर the stack poपूर्णांकer is below the bottom of the kernel
	 * stack क्रम some reason
	 */
	अगर (sp < stack_page)
		वापस 0;

	जबतक (sp < stack_page + THREAD_SIZE) अणु
		ip = *((अचिन्हित दीर्घ *) sp);
		अगर (in_sched_functions(ip))
			/* Ignore everything until we're above the scheduler */
			seen_sched = 1;
		अन्यथा अगर (kernel_text_address(ip) && seen_sched)
			वापस ip;

		sp += माप(अचिन्हित दीर्घ);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक elf_core_copy_fpregs(काष्ठा task_काष्ठा *t, elf_fpregset_t *fpu)
अणु
	पूर्णांक cpu = current_thपढ़ो_info()->cpu;

	वापस save_i387_रेजिस्टरs(userspace_pid[cpu], (अचिन्हित दीर्घ *) fpu);
पूर्ण

