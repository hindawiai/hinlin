<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/stacktrace.c
 *
 * Stack trace management functions
 *
 *  Copyright (C) 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 */
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/stacktrace.h>

/**
 * stack_trace_prपूर्णांक - Prपूर्णांक the entries in the stack trace
 * @entries:	Poपूर्णांकer to storage array
 * @nr_entries:	Number of entries in the storage array
 * @spaces:	Number of leading spaces to prपूर्णांक
 */
व्योम stack_trace_prपूर्णांक(स्थिर अचिन्हित दीर्घ *entries, अचिन्हित पूर्णांक nr_entries,
		       पूर्णांक spaces)
अणु
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON(!entries))
		वापस;

	क्रम (i = 0; i < nr_entries; i++)
		prपूर्णांकk("%*c%pS\n", 1 + spaces, ' ', (व्योम *)entries[i]);
पूर्ण
EXPORT_SYMBOL_GPL(stack_trace_prपूर्णांक);

/**
 * stack_trace_snprपूर्णांक - Prपूर्णांक the entries in the stack trace पूर्णांकo a buffer
 * @buf:	Poपूर्णांकer to the prपूर्णांक buffer
 * @size:	Size of the prपूर्णांक buffer
 * @entries:	Poपूर्णांकer to storage array
 * @nr_entries:	Number of entries in the storage array
 * @spaces:	Number of leading spaces to prपूर्णांक
 *
 * Return: Number of bytes prपूर्णांकed.
 */
पूर्णांक stack_trace_snprपूर्णांक(अक्षर *buf, माप_प्रकार size, स्थिर अचिन्हित दीर्घ *entries,
			अचिन्हित पूर्णांक nr_entries, पूर्णांक spaces)
अणु
	अचिन्हित पूर्णांक generated, i, total = 0;

	अगर (WARN_ON(!entries))
		वापस 0;

	क्रम (i = 0; i < nr_entries && size; i++) अणु
		generated = snम_लिखो(buf, size, "%*c%pS\n", 1 + spaces, ' ',
				     (व्योम *)entries[i]);

		total += generated;
		अगर (generated >= size) अणु
			buf += size;
			size = 0;
		पूर्ण अन्यथा अणु
			buf += generated;
			size -= generated;
		पूर्ण
	पूर्ण

	वापस total;
पूर्ण
EXPORT_SYMBOL_GPL(stack_trace_snprपूर्णांक);

#अगर_घोषित CONFIG_ARCH_STACKWALK

काष्ठा stacktrace_cookie अणु
	अचिन्हित दीर्घ	*store;
	अचिन्हित पूर्णांक	size;
	अचिन्हित पूर्णांक	skip;
	अचिन्हित पूर्णांक	len;
पूर्ण;

अटल bool stack_trace_consume_entry(व्योम *cookie, अचिन्हित दीर्घ addr)
अणु
	काष्ठा stacktrace_cookie *c = cookie;

	अगर (c->len >= c->size)
		वापस false;

	अगर (c->skip > 0) अणु
		c->skip--;
		वापस true;
	पूर्ण
	c->store[c->len++] = addr;
	वापस c->len < c->size;
पूर्ण

अटल bool stack_trace_consume_entry_nosched(व्योम *cookie, अचिन्हित दीर्घ addr)
अणु
	अगर (in_sched_functions(addr))
		वापस true;
	वापस stack_trace_consume_entry(cookie, addr);
पूर्ण

/**
 * stack_trace_save - Save a stack trace पूर्णांकo a storage array
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 * @skipnr:	Number of entries to skip at the start of the stack trace
 *
 * Return: Number of trace entries stored.
 */
अचिन्हित पूर्णांक stack_trace_save(अचिन्हित दीर्घ *store, अचिन्हित पूर्णांक size,
			      अचिन्हित पूर्णांक skipnr)
अणु
	stack_trace_consume_fn consume_entry = stack_trace_consume_entry;
	काष्ठा stacktrace_cookie c = अणु
		.store	= store,
		.size	= size,
		.skip	= skipnr + 1,
	पूर्ण;

	arch_stack_walk(consume_entry, &c, current, शून्य);
	वापस c.len;
पूर्ण
EXPORT_SYMBOL_GPL(stack_trace_save);

/**
 * stack_trace_save_tsk - Save a task stack trace पूर्णांकo a storage array
 * @task:	The task to examine
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 * @skipnr:	Number of entries to skip at the start of the stack trace
 *
 * Return: Number of trace entries stored.
 */
अचिन्हित पूर्णांक stack_trace_save_tsk(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *store,
				  अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक skipnr)
अणु
	stack_trace_consume_fn consume_entry = stack_trace_consume_entry_nosched;
	काष्ठा stacktrace_cookie c = अणु
		.store	= store,
		.size	= size,
		/* skip this function अगर they are tracing us */
		.skip	= skipnr + (current == tsk),
	पूर्ण;

	अगर (!try_get_task_stack(tsk))
		वापस 0;

	arch_stack_walk(consume_entry, &c, tsk, शून्य);
	put_task_stack(tsk);
	वापस c.len;
पूर्ण

/**
 * stack_trace_save_regs - Save a stack trace based on pt_regs पूर्णांकo a storage array
 * @regs:	Poपूर्णांकer to pt_regs to examine
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 * @skipnr:	Number of entries to skip at the start of the stack trace
 *
 * Return: Number of trace entries stored.
 */
अचिन्हित पूर्णांक stack_trace_save_regs(काष्ठा pt_regs *regs, अचिन्हित दीर्घ *store,
				   अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक skipnr)
अणु
	stack_trace_consume_fn consume_entry = stack_trace_consume_entry;
	काष्ठा stacktrace_cookie c = अणु
		.store	= store,
		.size	= size,
		.skip	= skipnr,
	पूर्ण;

	arch_stack_walk(consume_entry, &c, current, regs);
	वापस c.len;
पूर्ण

#अगर_घोषित CONFIG_HAVE_RELIABLE_STACKTRACE
/**
 * stack_trace_save_tsk_reliable - Save task stack with verअगरication
 * @tsk:	Poपूर्णांकer to the task to examine
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 *
 * Return:	An error अगर it detects any unreliable features of the
 *		stack. Otherwise it guarantees that the stack trace is
 *		reliable and वापसs the number of entries stored.
 *
 * If the task is not 'current', the caller *must* ensure the task is inactive.
 */
पूर्णांक stack_trace_save_tsk_reliable(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *store,
				  अचिन्हित पूर्णांक size)
अणु
	stack_trace_consume_fn consume_entry = stack_trace_consume_entry;
	काष्ठा stacktrace_cookie c = अणु
		.store	= store,
		.size	= size,
	पूर्ण;
	पूर्णांक ret;

	/*
	 * If the task करोesn't have a stack (e.g., a zombie), the stack is
	 * "reliably" empty.
	 */
	अगर (!try_get_task_stack(tsk))
		वापस 0;

	ret = arch_stack_walk_reliable(consume_entry, &c, tsk);
	put_task_stack(tsk);
	वापस ret ? ret : c.len;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_USER_STACKTRACE_SUPPORT
/**
 * stack_trace_save_user - Save a user space stack trace पूर्णांकo a storage array
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 *
 * Return: Number of trace entries stored.
 */
अचिन्हित पूर्णांक stack_trace_save_user(अचिन्हित दीर्घ *store, अचिन्हित पूर्णांक size)
अणु
	stack_trace_consume_fn consume_entry = stack_trace_consume_entry;
	काष्ठा stacktrace_cookie c = अणु
		.store	= store,
		.size	= size,
	पूर्ण;
	mm_segment_t fs;

	/* Trace user stack अगर not a kernel thपढ़ो */
	अगर (current->flags & PF_KTHREAD)
		वापस 0;

	fs = क्रमce_uaccess_begin();
	arch_stack_walk_user(consume_entry, &c, task_pt_regs(current));
	क्रमce_uaccess_end(fs);

	वापस c.len;
पूर्ण
#पूर्ण_अगर

#अन्यथा /* CONFIG_ARCH_STACKWALK */

/*
 * Architectures that करो not implement save_stack_trace_*()
 * get these weak aliases and once-per-bootup warnings
 * (whenever this facility is utilized - क्रम example by procfs):
 */
__weak व्योम
save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	WARN_ONCE(1, KERN_INFO "save_stack_trace_tsk() not implemented yet.\n");
पूर्ण

__weak व्योम
save_stack_trace_regs(काष्ठा pt_regs *regs, काष्ठा stack_trace *trace)
अणु
	WARN_ONCE(1, KERN_INFO "save_stack_trace_regs() not implemented yet.\n");
पूर्ण

/**
 * stack_trace_save - Save a stack trace पूर्णांकo a storage array
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 * @skipnr:	Number of entries to skip at the start of the stack trace
 *
 * Return: Number of trace entries stored
 */
अचिन्हित पूर्णांक stack_trace_save(अचिन्हित दीर्घ *store, अचिन्हित पूर्णांक size,
			      अचिन्हित पूर्णांक skipnr)
अणु
	काष्ठा stack_trace trace = अणु
		.entries	= store,
		.max_entries	= size,
		.skip		= skipnr + 1,
	पूर्ण;

	save_stack_trace(&trace);
	वापस trace.nr_entries;
पूर्ण
EXPORT_SYMBOL_GPL(stack_trace_save);

/**
 * stack_trace_save_tsk - Save a task stack trace पूर्णांकo a storage array
 * @task:	The task to examine
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 * @skipnr:	Number of entries to skip at the start of the stack trace
 *
 * Return: Number of trace entries stored
 */
अचिन्हित पूर्णांक stack_trace_save_tsk(काष्ठा task_काष्ठा *task,
				  अचिन्हित दीर्घ *store, अचिन्हित पूर्णांक size,
				  अचिन्हित पूर्णांक skipnr)
अणु
	काष्ठा stack_trace trace = अणु
		.entries	= store,
		.max_entries	= size,
		/* skip this function अगर they are tracing us */
		.skip	= skipnr + (current == task),
	पूर्ण;

	save_stack_trace_tsk(task, &trace);
	वापस trace.nr_entries;
पूर्ण

/**
 * stack_trace_save_regs - Save a stack trace based on pt_regs पूर्णांकo a storage array
 * @regs:	Poपूर्णांकer to pt_regs to examine
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 * @skipnr:	Number of entries to skip at the start of the stack trace
 *
 * Return: Number of trace entries stored
 */
अचिन्हित पूर्णांक stack_trace_save_regs(काष्ठा pt_regs *regs, अचिन्हित दीर्घ *store,
				   अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक skipnr)
अणु
	काष्ठा stack_trace trace = अणु
		.entries	= store,
		.max_entries	= size,
		.skip		= skipnr,
	पूर्ण;

	save_stack_trace_regs(regs, &trace);
	वापस trace.nr_entries;
पूर्ण

#अगर_घोषित CONFIG_HAVE_RELIABLE_STACKTRACE
/**
 * stack_trace_save_tsk_reliable - Save task stack with verअगरication
 * @tsk:	Poपूर्णांकer to the task to examine
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 *
 * Return:	An error अगर it detects any unreliable features of the
 *		stack. Otherwise it guarantees that the stack trace is
 *		reliable and वापसs the number of entries stored.
 *
 * If the task is not 'current', the caller *must* ensure the task is inactive.
 */
पूर्णांक stack_trace_save_tsk_reliable(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *store,
				  अचिन्हित पूर्णांक size)
अणु
	काष्ठा stack_trace trace = अणु
		.entries	= store,
		.max_entries	= size,
	पूर्ण;
	पूर्णांक ret = save_stack_trace_tsk_reliable(tsk, &trace);

	वापस ret ? ret : trace.nr_entries;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_USER_STACKTRACE_SUPPORT
/**
 * stack_trace_save_user - Save a user space stack trace पूर्णांकo a storage array
 * @store:	Poपूर्णांकer to storage array
 * @size:	Size of the storage array
 *
 * Return: Number of trace entries stored
 */
अचिन्हित पूर्णांक stack_trace_save_user(अचिन्हित दीर्घ *store, अचिन्हित पूर्णांक size)
अणु
	काष्ठा stack_trace trace = अणु
		.entries	= store,
		.max_entries	= size,
	पूर्ण;

	save_stack_trace_user(&trace);
	वापस trace.nr_entries;
पूर्ण
#पूर्ण_अगर /* CONFIG_USER_STACKTRACE_SUPPORT */

#पूर्ण_अगर /* !CONFIG_ARCH_STACKWALK */
