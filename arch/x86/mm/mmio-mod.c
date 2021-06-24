<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) IBM Corporation, 2005
 *               Jeff Muizelaar, 2006, 2007
 *               Pekka Paalanen, 2008 <pq@iki.fi>
 *
 * Derived from the पढ़ो-mod example from relay-examples by Tom Zanussi.
 */

#घोषणा pr_fmt(fmt) "mmiotrace: " fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/mmiotrace.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/e820/api.h> /* क्रम ISA_START_ADDRESS */
#समावेश <linux/atomic.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpu.h>

#समावेश "pf_in.h"

काष्ठा trap_reason अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ ip;
	क्रमागत reason_type type;
	पूर्णांक active_traces;
पूर्ण;

काष्ठा remap_trace अणु
	काष्ठा list_head list;
	काष्ठा kmmio_probe probe;
	resource_माप_प्रकार phys;
	अचिन्हित दीर्घ id;
पूर्ण;

/* Accessed per-cpu. */
अटल DEFINE_PER_CPU(काष्ठा trap_reason, pf_reason);
अटल DEFINE_PER_CPU(काष्ठा mmiotrace_rw, cpu_trace);

अटल DEFINE_MUTEX(mmiotrace_mutex);
अटल DEFINE_SPINLOCK(trace_lock);
अटल atomic_t mmiotrace_enabled;
अटल LIST_HEAD(trace_list);		/* काष्ठा remap_trace */

/*
 * Locking in this file:
 * - mmiotrace_mutex enक्रमces enable/disable_mmiotrace() critical sections.
 * - mmiotrace_enabled may be modअगरied only when holding mmiotrace_mutex
 *   and trace_lock.
 * - Routines depending on is_enabled() must take trace_lock.
 * - trace_list users must hold trace_lock.
 * - is_enabled() guarantees that mmio_trace_अणुrw,mappingपूर्ण are allowed.
 * - pre/post callbacks assume the effect of is_enabled() being true.
 */

/* module parameters */
अटल अचिन्हित दीर्घ	filter_offset;
अटल bool		nommiotrace;
अटल bool		trace_pc;

module_param(filter_offset, uदीर्घ, 0);
module_param(nommiotrace, bool, 0);
module_param(trace_pc, bool, 0);

MODULE_PARM_DESC(filter_offset, "Start address of traced mappings.");
MODULE_PARM_DESC(nommiotrace, "Disable actual MMIO tracing.");
MODULE_PARM_DESC(trace_pc, "Record address of faulting instructions.");

अटल bool is_enabled(व्योम)
अणु
	वापस atomic_पढ़ो(&mmiotrace_enabled);
पूर्ण

अटल व्योम prपूर्णांक_pte(अचिन्हित दीर्घ address)
अणु
	अचिन्हित पूर्णांक level;
	pte_t *pte = lookup_address(address, &level);

	अगर (!pte) अणु
		pr_err("Error in %s: no pte for page 0x%08lx\n",
		       __func__, address);
		वापस;
	पूर्ण

	अगर (level == PG_LEVEL_2M) अणु
		pr_emerg("4MB pages are not currently supported: 0x%08lx\n",
			 address);
		BUG();
	पूर्ण
	pr_info("pte for 0x%lx: 0x%llx 0x%llx\n",
		address,
		(अचिन्हित दीर्घ दीर्घ)pte_val(*pte),
		(अचिन्हित दीर्घ दीर्घ)pte_val(*pte) & _PAGE_PRESENT);
पूर्ण

/*
 * For some reason the pre/post pairs have been called in an
 * unmatched order. Report and die.
 */
अटल व्योम die_kmmio_nesting_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	स्थिर काष्ठा trap_reason *my_reason = &get_cpu_var(pf_reason);
	pr_emerg("unexpected fault for address: 0x%08lx, last fault for address: 0x%08lx\n",
		 addr, my_reason->addr);
	prपूर्णांक_pte(addr);
	pr_emerg("faulting IP is at %pS\n", (व्योम *)regs->ip);
	pr_emerg("last faulting IP was at %pS\n", (व्योम *)my_reason->ip);
#अगर_घोषित __i386__
	pr_emerg("eax: %08lx   ebx: %08lx   ecx: %08lx   edx: %08lx\n",
		 regs->ax, regs->bx, regs->cx, regs->dx);
	pr_emerg("esi: %08lx   edi: %08lx   ebp: %08lx   esp: %08lx\n",
		 regs->si, regs->di, regs->bp, regs->sp);
#अन्यथा
	pr_emerg("rax: %016lx   rcx: %016lx   rdx: %016lx\n",
		 regs->ax, regs->cx, regs->dx);
	pr_emerg("rsi: %016lx   rdi: %016lx   rbp: %016lx   rsp: %016lx\n",
		 regs->si, regs->di, regs->bp, regs->sp);
#पूर्ण_अगर
	put_cpu_var(pf_reason);
	BUG();
पूर्ण

अटल व्योम pre(काष्ठा kmmio_probe *p, काष्ठा pt_regs *regs,
						अचिन्हित दीर्घ addr)
अणु
	काष्ठा trap_reason *my_reason = &get_cpu_var(pf_reason);
	काष्ठा mmiotrace_rw *my_trace = &get_cpu_var(cpu_trace);
	स्थिर अचिन्हित दीर्घ instptr = inकाष्ठाion_poपूर्णांकer(regs);
	स्थिर क्रमागत reason_type type = get_ins_type(instptr);
	काष्ठा remap_trace *trace = p->निजी;

	/* it करोesn't make sense to have more than one active trace per cpu */
	अगर (my_reason->active_traces)
		die_kmmio_nesting_error(regs, addr);
	अन्यथा
		my_reason->active_traces++;

	my_reason->type = type;
	my_reason->addr = addr;
	my_reason->ip = instptr;

	my_trace->phys = addr - trace->probe.addr + trace->phys;
	my_trace->map_id = trace->id;

	/*
	 * Only record the program counter when requested.
	 * It may taपूर्णांक clean-room reverse engineering.
	 */
	अगर (trace_pc)
		my_trace->pc = instptr;
	अन्यथा
		my_trace->pc = 0;

	/*
	 * XXX: the बारtamp recorded will be *after* the tracing has been
	 * करोne, not at the समय we hit the inकाष्ठाion. SMP implications
	 * on event ordering?
	 */

	चयन (type) अणु
	हाल REG_READ:
		my_trace->opcode = MMIO_READ;
		my_trace->width = get_ins_mem_width(instptr);
		अवरोध;
	हाल REG_WRITE:
		my_trace->opcode = MMIO_WRITE;
		my_trace->width = get_ins_mem_width(instptr);
		my_trace->value = get_ins_reg_val(instptr, regs);
		अवरोध;
	हाल IMM_WRITE:
		my_trace->opcode = MMIO_WRITE;
		my_trace->width = get_ins_mem_width(instptr);
		my_trace->value = get_ins_imm_val(instptr);
		अवरोध;
	शेष:
		अणु
			अचिन्हित अक्षर *ip = (अचिन्हित अक्षर *)instptr;
			my_trace->opcode = MMIO_UNKNOWN_OP;
			my_trace->width = 0;
			my_trace->value = (*ip) << 16 | *(ip + 1) << 8 |
								*(ip + 2);
		पूर्ण
	पूर्ण
	put_cpu_var(cpu_trace);
	put_cpu_var(pf_reason);
पूर्ण

अटल व्योम post(काष्ठा kmmio_probe *p, अचिन्हित दीर्घ condition,
							काष्ठा pt_regs *regs)
अणु
	काष्ठा trap_reason *my_reason = &get_cpu_var(pf_reason);
	काष्ठा mmiotrace_rw *my_trace = &get_cpu_var(cpu_trace);

	/* this should always वापस the active_trace count to 0 */
	my_reason->active_traces--;
	अगर (my_reason->active_traces) अणु
		pr_emerg("unexpected post handler");
		BUG();
	पूर्ण

	चयन (my_reason->type) अणु
	हाल REG_READ:
		my_trace->value = get_ins_reg_val(my_reason->ip, regs);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mmio_trace_rw(my_trace);
	put_cpu_var(cpu_trace);
	put_cpu_var(pf_reason);
पूर्ण

अटल व्योम ioremap_trace_core(resource_माप_प्रकार offset, अचिन्हित दीर्घ size,
							व्योम __iomem *addr)
अणु
	अटल atomic_t next_id;
	काष्ठा remap_trace *trace = kदो_स्मृति(माप(*trace), GFP_KERNEL);
	/* These are page-unaligned. */
	काष्ठा mmiotrace_map map = अणु
		.phys = offset,
		.virt = (अचिन्हित दीर्घ)addr,
		.len = size,
		.opcode = MMIO_PROBE
	पूर्ण;

	अगर (!trace) अणु
		pr_err("kmalloc failed in ioremap\n");
		वापस;
	पूर्ण

	*trace = (काष्ठा remap_trace) अणु
		.probe = अणु
			.addr = (अचिन्हित दीर्घ)addr,
			.len = size,
			.pre_handler = pre,
			.post_handler = post,
			.निजी = trace
		पूर्ण,
		.phys = offset,
		.id = atomic_inc_वापस(&next_id)
	पूर्ण;
	map.map_id = trace->id;

	spin_lock_irq(&trace_lock);
	अगर (!is_enabled()) अणु
		kमुक्त(trace);
		जाओ not_enabled;
	पूर्ण

	mmio_trace_mapping(&map);
	list_add_tail(&trace->list, &trace_list);
	अगर (!nommiotrace)
		रेजिस्टर_kmmio_probe(&trace->probe);

not_enabled:
	spin_unlock_irq(&trace_lock);
पूर्ण

व्योम mmiotrace_ioremap(resource_माप_प्रकार offset, अचिन्हित दीर्घ size,
						व्योम __iomem *addr)
अणु
	अगर (!is_enabled()) /* recheck and proper locking in *_core() */
		वापस;

	pr_debug("ioremap_*(0x%llx, 0x%lx) = %p\n",
		 (अचिन्हित दीर्घ दीर्घ)offset, size, addr);
	अगर ((filter_offset) && (offset != filter_offset))
		वापस;
	ioremap_trace_core(offset, size, addr);
पूर्ण

अटल व्योम iounmap_trace_core(अस्थिर व्योम __iomem *addr)
अणु
	काष्ठा mmiotrace_map map = अणु
		.phys = 0,
		.virt = (अचिन्हित दीर्घ)addr,
		.len = 0,
		.opcode = MMIO_UNPROBE
	पूर्ण;
	काष्ठा remap_trace *trace;
	काष्ठा remap_trace *पंचांगp;
	काष्ठा remap_trace *found_trace = शून्य;

	pr_debug("Unmapping %p.\n", addr);

	spin_lock_irq(&trace_lock);
	अगर (!is_enabled())
		जाओ not_enabled;

	list_क्रम_each_entry_safe(trace, पंचांगp, &trace_list, list) अणु
		अगर ((अचिन्हित दीर्घ)addr == trace->probe.addr) अणु
			अगर (!nommiotrace)
				unरेजिस्टर_kmmio_probe(&trace->probe);
			list_del(&trace->list);
			found_trace = trace;
			अवरोध;
		पूर्ण
	पूर्ण
	map.map_id = (found_trace) ? found_trace->id : -1;
	mmio_trace_mapping(&map);

not_enabled:
	spin_unlock_irq(&trace_lock);
	अगर (found_trace) अणु
		synchronize_rcu(); /* unरेजिस्टर_kmmio_probe() requirement */
		kमुक्त(found_trace);
	पूर्ण
पूर्ण

व्योम mmiotrace_iounmap(अस्थिर व्योम __iomem *addr)
अणु
	might_sleep();
	अगर (is_enabled()) /* recheck and proper locking in *_core() */
		iounmap_trace_core(addr);
पूर्ण

पूर्णांक mmiotrace_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret = 0;
	बहु_सूची args;
	अचिन्हित दीर्घ flags;
	बहु_शुरू(args, fmt);

	spin_lock_irqsave(&trace_lock, flags);
	अगर (is_enabled())
		ret = mmio_trace_prपूर्णांकk(fmt, args);
	spin_unlock_irqrestore(&trace_lock, flags);

	बहु_पूर्ण(args);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mmiotrace_prपूर्णांकk);

अटल व्योम clear_trace_list(व्योम)
अणु
	काष्ठा remap_trace *trace;
	काष्ठा remap_trace *पंचांगp;

	/*
	 * No locking required, because the caller ensures we are in a
	 * critical section via mutex, and is_enabled() is false,
	 * i.e. nothing can traverse or modअगरy this list.
	 * Caller also ensures is_enabled() cannot change.
	 */
	list_क्रम_each_entry(trace, &trace_list, list) अणु
		pr_notice("purging non-iounmapped trace @0x%08lx, size 0x%lx.\n",
			  trace->probe.addr, trace->probe.len);
		अगर (!nommiotrace)
			unरेजिस्टर_kmmio_probe(&trace->probe);
	पूर्ण
	synchronize_rcu(); /* unरेजिस्टर_kmmio_probe() requirement */

	list_क्रम_each_entry_safe(trace, पंचांगp, &trace_list, list) अणु
		list_del(&trace->list);
		kमुक्त(trace);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल cpumask_var_t करोwned_cpus;

अटल व्योम enter_uniprocessor(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक err;

	अगर (!cpumask_available(करोwned_cpus) &&
	    !alloc_cpumask_var(&करोwned_cpus, GFP_KERNEL)) अणु
		pr_notice("Failed to allocate mask\n");
		जाओ out;
	पूर्ण

	get_online_cpus();
	cpumask_copy(करोwned_cpus, cpu_online_mask);
	cpumask_clear_cpu(cpumask_first(cpu_online_mask), करोwned_cpus);
	अगर (num_online_cpus() > 1)
		pr_notice("Disabling non-boot CPUs...\n");
	put_online_cpus();

	क्रम_each_cpu(cpu, करोwned_cpus) अणु
		err = हटाओ_cpu(cpu);
		अगर (!err)
			pr_info("CPU%d is down.\n", cpu);
		अन्यथा
			pr_err("Error taking CPU%d down: %d\n", cpu, err);
	पूर्ण
out:
	अगर (num_online_cpus() > 1)
		pr_warn("multiple CPUs still online, may miss events.\n");
पूर्ण

अटल व्योम leave_uniprocessor(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक err;

	अगर (!cpumask_available(करोwned_cpus) || cpumask_weight(करोwned_cpus) == 0)
		वापस;
	pr_notice("Re-enabling CPUs...\n");
	क्रम_each_cpu(cpu, करोwned_cpus) अणु
		err = add_cpu(cpu);
		अगर (!err)
			pr_info("enabled CPU%d.\n", cpu);
		अन्यथा
			pr_err("cannot re-enable CPU%d: %d\n", cpu, err);
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_HOTPLUG_CPU */
अटल व्योम enter_uniprocessor(व्योम)
अणु
	अगर (num_online_cpus() > 1)
		pr_warn("multiple CPUs are online, may miss events. "
			"Suggest booting with maxcpus=1 kernel argument.\n");
पूर्ण

अटल व्योम leave_uniprocessor(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

व्योम enable_mmiotrace(व्योम)
अणु
	mutex_lock(&mmiotrace_mutex);
	अगर (is_enabled())
		जाओ out;

	अगर (nommiotrace)
		pr_info("MMIO tracing disabled.\n");
	kmmio_init();
	enter_uniprocessor();
	spin_lock_irq(&trace_lock);
	atomic_inc(&mmiotrace_enabled);
	spin_unlock_irq(&trace_lock);
	pr_info("enabled.\n");
out:
	mutex_unlock(&mmiotrace_mutex);
पूर्ण

व्योम disable_mmiotrace(व्योम)
अणु
	mutex_lock(&mmiotrace_mutex);
	अगर (!is_enabled())
		जाओ out;

	spin_lock_irq(&trace_lock);
	atomic_dec(&mmiotrace_enabled);
	BUG_ON(is_enabled());
	spin_unlock_irq(&trace_lock);

	clear_trace_list(); /* guarantees: no more kmmio callbacks */
	leave_uniprocessor();
	kmmio_cleanup();
	pr_info("disabled.\n");
out:
	mutex_unlock(&mmiotrace_mutex);
पूर्ण
