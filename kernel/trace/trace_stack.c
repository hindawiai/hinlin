<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Steven Rostedt <srostedt@redhat.com>
 *
 */
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/security.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/module.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/setup.h>

#समावेश "trace.h"

#घोषणा STACK_TRACE_ENTRIES 500

अटल अचिन्हित दीर्घ stack_dump_trace[STACK_TRACE_ENTRIES];
अटल अचिन्हित stack_trace_index[STACK_TRACE_ENTRIES];

अटल अचिन्हित पूर्णांक stack_trace_nr_entries;
अटल अचिन्हित दीर्घ stack_trace_max_size;
अटल arch_spinlock_t stack_trace_max_lock =
	(arch_spinlock_t)__ARCH_SPIN_LOCK_UNLOCKED;

DEFINE_PER_CPU(पूर्णांक, disable_stack_tracer);
अटल DEFINE_MUTEX(stack_sysctl_mutex);

पूर्णांक stack_tracer_enabled;

अटल व्योम prपूर्णांक_max_stack(व्योम)
अणु
	दीर्घ i;
	पूर्णांक size;

	pr_emerg("        Depth    Size   Location    (%d entries)\n"
			   "        -----    ----   --------\n",
			   stack_trace_nr_entries);

	क्रम (i = 0; i < stack_trace_nr_entries; i++) अणु
		अगर (i + 1 == stack_trace_nr_entries)
			size = stack_trace_index[i];
		अन्यथा
			size = stack_trace_index[i] - stack_trace_index[i+1];

		pr_emerg("%3ld) %8d   %5d   %pS\n", i, stack_trace_index[i],
				size, (व्योम *)stack_dump_trace[i]);
	पूर्ण
पूर्ण

/*
 * The stack tracer looks क्रम a maximum stack at each call from a function. It
 * रेजिस्टरs a callback from ftrace, and in that callback it examines the stack
 * size. It determines the stack size from the variable passed in, which is the
 * address of a local variable in the stack_trace_call() callback function.
 * The stack size is calculated by the address of the local variable to the top
 * of the current stack. If that size is smaller than the currently saved max
 * stack size, nothing more is करोne.
 *
 * If the size of the stack is greater than the maximum recorded size, then the
 * following algorithm takes place.
 *
 * For architectures (like x86) that store the function's वापस address beक्रमe
 * saving the function's local variables, the stack will look something like
 * this:
 *
 *   [ top of stack ]
 *    0: sys call entry frame
 *   10: वापस addr to entry code
 *   11: start of sys_foo frame
 *   20: वापस addr to sys_foo
 *   21: start of kernel_func_bar frame
 *   30: वापस addr to kernel_func_bar
 *   31: [ करो trace stack here ]
 *
 * The save_stack_trace() is called वापसing all the functions it finds in the
 * current stack. Which would be (from the bottom of the stack to the top):
 *
 *   वापस addr to kernel_func_bar
 *   वापस addr to sys_foo
 *   वापस addr to entry code
 *
 * Now to figure out how much each of these functions' local variable size is,
 * a search of the stack is made to find these values. When a match is made, it
 * is added to the stack_dump_trace[] array. The offset पूर्णांकo the stack is saved
 * in the stack_trace_index[] array. The above example would show:
 *
 *        stack_dump_trace[]        |   stack_trace_index[]
 *        ------------------        +   -------------------
 *  वापस addr to kernel_func_bar  |          30
 *  वापस addr to sys_foo          |          20
 *  वापस addr to entry            |          10
 *
 * The prपूर्णांक_max_stack() function above, uses these values to prपूर्णांक the size of
 * each function's portion of the stack.
 *
 *  क्रम (i = 0; i < nr_entries; i++) अणु
 *     size = i == nr_entries - 1 ? stack_trace_index[i] :
 *                    stack_trace_index[i] - stack_trace_index[i+1]
 *     prपूर्णांक "%d %d %d %s\n", i, stack_trace_index[i], size, stack_dump_trace[i]);
 *  पूर्ण
 *
 * The above shows
 *
 *     depth size  location
 *     ----- ----  --------
 *  0    30   10   kernel_func_bar
 *  1    20   10   sys_foo
 *  2    10   10   entry code
 *
 * Now क्रम architectures that might save the वापस address after the functions
 * local variables (saving the link रेजिस्टर beक्रमe calling nested functions),
 * this will cause the stack to look a little dअगरferent:
 *
 * [ top of stack ]
 *  0: sys call entry frame
 * 10: start of sys_foo_frame
 * 19: वापस addr to entry code << lr saved beक्रमe calling kernel_func_bar
 * 20: start of kernel_func_bar frame
 * 29: वापस addr to sys_foo_frame << lr saved beक्रमe calling next function
 * 30: [ करो trace stack here ]
 *
 * Although the functions वापसed by save_stack_trace() may be the same, the
 * placement in the stack will be dअगरferent. Using the same algorithm as above
 * would yield:
 *
 *        stack_dump_trace[]        |   stack_trace_index[]
 *        ------------------        +   -------------------
 *  वापस addr to kernel_func_bar  |          30
 *  वापस addr to sys_foo          |          29
 *  वापस addr to entry            |          19
 *
 * Where the mapping is off by one:
 *
 *   kernel_func_bar stack frame size is 29 - 19 not 30 - 29!
 *
 * To fix this, अगर the architecture sets ARCH_RET_ADDR_AFTER_LOCAL_VARS the
 * values in stack_trace_index[] are shअगरted by one to and the number of
 * stack trace entries is decremented by one.
 *
 *        stack_dump_trace[]        |   stack_trace_index[]
 *        ------------------        +   -------------------
 *  वापस addr to kernel_func_bar  |          29
 *  वापस addr to sys_foo          |          19
 *
 * Although the entry function is not displayed, the first function (sys_foo)
 * will still include the stack size of it.
 */
अटल व्योम check_stack(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ *stack)
अणु
	अचिन्हित दीर्घ this_size, flags; अचिन्हित दीर्घ *p, *top, *start;
	अटल पूर्णांक tracer_frame;
	पूर्णांक frame_size = READ_ONCE(tracer_frame);
	पूर्णांक i, x;

	this_size = ((अचिन्हित दीर्घ)stack) & (THREAD_SIZE-1);
	this_size = THREAD_SIZE - this_size;
	/* Remove the frame of the tracer */
	this_size -= frame_size;

	अगर (this_size <= stack_trace_max_size)
		वापस;

	/* we करो not handle पूर्णांकerrupt stacks yet */
	अगर (!object_is_on_stack(stack))
		वापस;

	/* Can't करो this from NMI context (can cause deadlocks) */
	अगर (in_nmi())
		वापस;

	local_irq_save(flags);
	arch_spin_lock(&stack_trace_max_lock);

	/* In हाल another CPU set the tracer_frame on us */
	अगर (unlikely(!frame_size))
		this_size -= tracer_frame;

	/* a race could have alपढ़ोy updated it */
	अगर (this_size <= stack_trace_max_size)
		जाओ out;

	stack_trace_max_size = this_size;

	stack_trace_nr_entries = stack_trace_save(stack_dump_trace,
					       ARRAY_SIZE(stack_dump_trace) - 1,
					       0);

	/* Skip over the overhead of the stack tracer itself */
	क्रम (i = 0; i < stack_trace_nr_entries; i++) अणु
		अगर (stack_dump_trace[i] == ip)
			अवरोध;
	पूर्ण

	/*
	 * Some archs may not have the passed in ip in the dump.
	 * If that happens, we need to show everything.
	 */
	अगर (i == stack_trace_nr_entries)
		i = 0;

	/*
	 * Now find where in the stack these are.
	 */
	x = 0;
	start = stack;
	top = (अचिन्हित दीर्घ *)
		(((अचिन्हित दीर्घ)start & ~(THREAD_SIZE-1)) + THREAD_SIZE);

	/*
	 * Loop through all the entries. One of the entries may
	 * क्रम some reason be missed on the stack, so we may
	 * have to account क्रम them. If they are all there, this
	 * loop will only happen once. This code only takes place
	 * on a new max, so it is far from a fast path.
	 */
	जबतक (i < stack_trace_nr_entries) अणु
		पूर्णांक found = 0;

		stack_trace_index[x] = this_size;
		p = start;

		क्रम (; p < top && i < stack_trace_nr_entries; p++) अणु
			/*
			 * The READ_ONCE_NOCHECK is used to let KASAN know that
			 * this is not a stack-out-of-bounds error.
			 */
			अगर ((READ_ONCE_NOCHECK(*p)) == stack_dump_trace[i]) अणु
				stack_dump_trace[x] = stack_dump_trace[i++];
				this_size = stack_trace_index[x++] =
					(top - p) * माप(अचिन्हित दीर्घ);
				found = 1;
				/* Start the search from here */
				start = p + 1;
				/*
				 * We करो not want to show the overhead
				 * of the stack tracer stack in the
				 * max stack. If we haven't figured
				 * out what that is, then figure it out
				 * now.
				 */
				अगर (unlikely(!tracer_frame)) अणु
					tracer_frame = (p - stack) *
						माप(अचिन्हित दीर्घ);
					stack_trace_max_size -= tracer_frame;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!found)
			i++;
	पूर्ण

#अगर_घोषित ARCH_FTRACE_SHIFT_STACK_TRACER
	/*
	 * Some archs will store the link रेजिस्टर beक्रमe calling
	 * nested functions. This means the saved वापस address
	 * comes after the local storage, and we need to shअगरt
	 * क्रम that.
	 */
	अगर (x > 1) अणु
		स_हटाओ(&stack_trace_index[0], &stack_trace_index[1],
			माप(stack_trace_index[0]) * (x - 1));
		x--;
	पूर्ण
#पूर्ण_अगर

	stack_trace_nr_entries = x;

	अगर (task_stack_end_corrupted(current)) अणु
		prपूर्णांक_max_stack();
		BUG();
	पूर्ण

 out:
	arch_spin_unlock(&stack_trace_max_lock);
	local_irq_restore(flags);
पूर्ण

/* Some archs may not define MCOUNT_INSN_SIZE */
#अगर_अघोषित MCOUNT_INSN_SIZE
# define MCOUNT_INSN_SIZE 0
#पूर्ण_अगर

अटल व्योम
stack_trace_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		 काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	अचिन्हित दीर्घ stack;

	preempt_disable_notrace();

	/* no atomic needed, we only modअगरy this variable by this cpu */
	__this_cpu_inc(disable_stack_tracer);
	अगर (__this_cpu_पढ़ो(disable_stack_tracer) != 1)
		जाओ out;

	/* If rcu is not watching, then save stack trace can fail */
	अगर (!rcu_is_watching())
		जाओ out;

	ip += MCOUNT_INSN_SIZE;

	check_stack(ip, &stack);

 out:
	__this_cpu_dec(disable_stack_tracer);
	/* prevent recursion in schedule */
	preempt_enable_notrace();
पूर्ण

अटल काष्ठा ftrace_ops trace_ops __पढ़ो_mostly =
अणु
	.func = stack_trace_call,
पूर्ण;

अटल sमाप_प्रकार
stack_max_size_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		    माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ *ptr = filp->निजी_data;
	अक्षर buf[64];
	पूर्णांक r;

	r = snम_लिखो(buf, माप(buf), "%ld\n", *ptr);
	अगर (r > माप(buf))
		r = माप(buf);
	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, r);
पूर्ण

अटल sमाप_प्रकार
stack_max_size_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		     माप_प्रकार count, loff_t *ppos)
अणु
	दीर्घ *ptr = filp->निजी_data;
	अचिन्हित दीर्घ val, flags;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, count, 10, &val);
	अगर (ret)
		वापस ret;

	local_irq_save(flags);

	/*
	 * In हाल we trace inside arch_spin_lock() or after (NMI),
	 * we will cause circular lock, so we also need to increase
	 * the percpu disable_stack_tracer here.
	 */
	__this_cpu_inc(disable_stack_tracer);

	arch_spin_lock(&stack_trace_max_lock);
	*ptr = val;
	arch_spin_unlock(&stack_trace_max_lock);

	__this_cpu_dec(disable_stack_tracer);
	local_irq_restore(flags);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations stack_max_size_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= stack_max_size_पढ़ो,
	.ग_लिखो		= stack_max_size_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल व्योम *
__next(काष्ठा seq_file *m, loff_t *pos)
अणु
	दीर्घ n = *pos - 1;

	अगर (n >= stack_trace_nr_entries)
		वापस शून्य;

	m->निजी = (व्योम *)n;
	वापस &m->निजी;
पूर्ण

अटल व्योम *
t_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस __next(m, pos);
पूर्ण

अटल व्योम *t_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	local_irq_disable();

	__this_cpu_inc(disable_stack_tracer);

	arch_spin_lock(&stack_trace_max_lock);

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	वापस __next(m, pos);
पूर्ण

अटल व्योम t_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	arch_spin_unlock(&stack_trace_max_lock);

	__this_cpu_dec(disable_stack_tracer);

	local_irq_enable();
पूर्ण

अटल व्योम trace_lookup_stack(काष्ठा seq_file *m, दीर्घ i)
अणु
	अचिन्हित दीर्घ addr = stack_dump_trace[i];

	seq_म_लिखो(m, "%pS\n", (व्योम *)addr);
पूर्ण

अटल व्योम prपूर्णांक_disabled(काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, "#\n"
		 "#  Stack tracer disabled\n"
		 "#\n"
		 "# To enable the stack tracer, either add 'stacktrace' to the\n"
		 "# kernel command line\n"
		 "# or 'echo 1 > /proc/sys/kernel/stack_tracer_enabled'\n"
		 "#\n");
पूर्ण

अटल पूर्णांक t_show(काष्ठा seq_file *m, व्योम *v)
अणु
	दीर्घ i;
	पूर्णांक size;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(m, "        Depth    Size   Location"
			   "    (%d entries)\n"
			   "        -----    ----   --------\n",
			   stack_trace_nr_entries);

		अगर (!stack_tracer_enabled && !stack_trace_max_size)
			prपूर्णांक_disabled(m);

		वापस 0;
	पूर्ण

	i = *(दीर्घ *)v;

	अगर (i >= stack_trace_nr_entries)
		वापस 0;

	अगर (i + 1 == stack_trace_nr_entries)
		size = stack_trace_index[i];
	अन्यथा
		size = stack_trace_index[i] - stack_trace_index[i+1];

	seq_म_लिखो(m, "%3ld) %8d   %5d   ", i, stack_trace_index[i], size);

	trace_lookup_stack(m, i);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations stack_trace_seq_ops = अणु
	.start		= t_start,
	.next		= t_next,
	.stop		= t_stop,
	.show		= t_show,
पूर्ण;

अटल पूर्णांक stack_trace_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	वापस seq_खोलो(file, &stack_trace_seq_ops);
पूर्ण

अटल स्थिर काष्ठा file_operations stack_trace_fops = अणु
	.खोलो		= stack_trace_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

अटल पूर्णांक
stack_trace_filter_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_ops *ops = inode->i_निजी;

	/* Checks क्रम tracefs lockकरोwn */
	वापस ftrace_regex_खोलो(ops, FTRACE_ITER_FILTER,
				 inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations stack_trace_filter_fops = अणु
	.खोलो = stack_trace_filter_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = ftrace_filter_ग_लिखो,
	.llseek = tracing_lseek,
	.release = ftrace_regex_release,
पूर्ण;

#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

पूर्णांक
stack_trace_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		   माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक was_enabled;
	पूर्णांक ret;

	mutex_lock(&stack_sysctl_mutex);
	was_enabled = !!stack_tracer_enabled;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);

	अगर (ret || !ग_लिखो || (was_enabled == !!stack_tracer_enabled))
		जाओ out;

	अगर (stack_tracer_enabled)
		रेजिस्टर_ftrace_function(&trace_ops);
	अन्यथा
		unरेजिस्टर_ftrace_function(&trace_ops);
 out:
	mutex_unlock(&stack_sysctl_mutex);
	वापस ret;
पूर्ण

अटल अक्षर stack_trace_filter_buf[COMMAND_LINE_SIZE+1] __initdata;

अटल __init पूर्णांक enable_stacktrace(अक्षर *str)
अणु
	पूर्णांक len;

	अगर ((len = str_has_prefix(str, "_filter=")))
		म_नकलन(stack_trace_filter_buf, str + len, COMMAND_LINE_SIZE);

	stack_tracer_enabled = 1;
	वापस 1;
पूर्ण
__setup("stacktrace", enable_stacktrace);

अटल __init पूर्णांक stack_trace_init(व्योम)
अणु
	पूर्णांक ret;

	ret = tracing_init_dentry();
	अगर (ret)
		वापस 0;

	trace_create_file("stack_max_size", 0644, शून्य,
			&stack_trace_max_size, &stack_max_size_fops);

	trace_create_file("stack_trace", 0444, शून्य,
			शून्य, &stack_trace_fops);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	trace_create_file("stack_trace_filter", 0644, शून्य,
			  &trace_ops, &stack_trace_filter_fops);
#पूर्ण_अगर

	अगर (stack_trace_filter_buf[0])
		ftrace_set_early_filter(&trace_ops, stack_trace_filter_buf, 1);

	अगर (stack_tracer_enabled)
		रेजिस्टर_ftrace_function(&trace_ops);

	वापस 0;
पूर्ण

device_initcall(stack_trace_init);
