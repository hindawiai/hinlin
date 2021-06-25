<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Support क्रम MMIO probes.
 * Benefit many code from kprobes
 * (C) 2002 Louis Zhuang <louis.zhuang@पूर्णांकel.com>.
 *     2007 Alexander Eichner
 *     2008 Pekka Paalanen <pq@iki.fi>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/hash.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/preempt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/debugreg.h>
#समावेश <linux/mmiotrace.h>

#घोषणा KMMIO_PAGE_HASH_BITS 4
#घोषणा KMMIO_PAGE_TABLE_SIZE (1 << KMMIO_PAGE_HASH_BITS)

काष्ठा kmmio_fault_page अणु
	काष्ठा list_head list;
	काष्ठा kmmio_fault_page *release_next;
	अचिन्हित दीर्घ addr; /* the requested address */
	pteval_t old_presence; /* page presence prior to arming */
	bool armed;

	/*
	 * Number of बार this page has been रेजिस्टरed as a part
	 * of a probe. If zero, page is disarmed and this may be मुक्तd.
	 * Used only by ग_लिखोrs (RCU) and post_kmmio_handler().
	 * Protected by kmmio_lock, when linked पूर्णांकo kmmio_page_table.
	 */
	पूर्णांक count;

	bool scheduled_क्रम_release;
पूर्ण;

काष्ठा kmmio_delayed_release अणु
	काष्ठा rcu_head rcu;
	काष्ठा kmmio_fault_page *release_list;
पूर्ण;

काष्ठा kmmio_context अणु
	काष्ठा kmmio_fault_page *fpage;
	काष्ठा kmmio_probe *probe;
	अचिन्हित दीर्घ saved_flags;
	अचिन्हित दीर्घ addr;
	पूर्णांक active;
पूर्ण;

अटल DEFINE_SPINLOCK(kmmio_lock);

/* Protected by kmmio_lock */
अचिन्हित पूर्णांक kmmio_count;

/* Read-रक्षित by RCU, ग_लिखो-रक्षित by kmmio_lock. */
अटल काष्ठा list_head kmmio_page_table[KMMIO_PAGE_TABLE_SIZE];
अटल LIST_HEAD(kmmio_probes);

अटल काष्ठा list_head *kmmio_page_list(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक l;
	pte_t *pte = lookup_address(addr, &l);

	अगर (!pte)
		वापस शून्य;
	addr &= page_level_mask(l);

	वापस &kmmio_page_table[hash_दीर्घ(addr, KMMIO_PAGE_HASH_BITS)];
पूर्ण

/* Accessed per-cpu */
अटल DEFINE_PER_CPU(काष्ठा kmmio_context, kmmio_ctx);

/*
 * this is basically a dynamic stabbing problem:
 * Could use the existing prio tree code or
 * Possible better implementations:
 * The Interval Skip List: A Data Structure क्रम Finding All Intervals That
 * Overlap a Poपूर्णांक (might be simple)
 * Space Efficient Dynamic Stabbing with Fast Queries - Mikkel Thorup
 */
/* Get the kmmio at this addr (अगर any). You must be holding RCU पढ़ो lock. */
अटल काष्ठा kmmio_probe *get_kmmio_probe(अचिन्हित दीर्घ addr)
अणु
	काष्ठा kmmio_probe *p;
	list_क्रम_each_entry_rcu(p, &kmmio_probes, list) अणु
		अगर (addr >= p->addr && addr < (p->addr + p->len))
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

/* You must be holding RCU पढ़ो lock. */
अटल काष्ठा kmmio_fault_page *get_kmmio_fault_page(अचिन्हित दीर्घ addr)
अणु
	काष्ठा list_head *head;
	काष्ठा kmmio_fault_page *f;
	अचिन्हित पूर्णांक l;
	pte_t *pte = lookup_address(addr, &l);

	अगर (!pte)
		वापस शून्य;
	addr &= page_level_mask(l);
	head = kmmio_page_list(addr);
	list_क्रम_each_entry_rcu(f, head, list) अणु
		अगर (f->addr == addr)
			वापस f;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम clear_pmd_presence(pmd_t *pmd, bool clear, pmdval_t *old)
अणु
	pmd_t new_pmd;
	pmdval_t v = pmd_val(*pmd);
	अगर (clear) अणु
		*old = v;
		new_pmd = pmd_mkinvalid(*pmd);
	पूर्ण अन्यथा अणु
		/* Presume this has been called with clear==true previously */
		new_pmd = __pmd(*old);
	पूर्ण
	set_pmd(pmd, new_pmd);
पूर्ण

अटल व्योम clear_pte_presence(pte_t *pte, bool clear, pteval_t *old)
अणु
	pteval_t v = pte_val(*pte);
	अगर (clear) अणु
		*old = v;
		/* Nothing should care about address */
		pte_clear(&init_mm, 0, pte);
	पूर्ण अन्यथा अणु
		/* Presume this has been called with clear==true previously */
		set_pte_atomic(pte, __pte(*old));
	पूर्ण
पूर्ण

अटल पूर्णांक clear_page_presence(काष्ठा kmmio_fault_page *f, bool clear)
अणु
	अचिन्हित पूर्णांक level;
	pte_t *pte = lookup_address(f->addr, &level);

	अगर (!pte) अणु
		pr_err("no pte for addr 0x%08lx\n", f->addr);
		वापस -1;
	पूर्ण

	चयन (level) अणु
	हाल PG_LEVEL_2M:
		clear_pmd_presence((pmd_t *)pte, clear, &f->old_presence);
		अवरोध;
	हाल PG_LEVEL_4K:
		clear_pte_presence(pte, clear, &f->old_presence);
		अवरोध;
	शेष:
		pr_err("unexpected page level 0x%x.\n", level);
		वापस -1;
	पूर्ण

	flush_tlb_one_kernel(f->addr);
	वापस 0;
पूर्ण

/*
 * Mark the given page as not present. Access to it will trigger a fault.
 *
 * Struct kmmio_fault_page is रक्षित by RCU and kmmio_lock, but the
 * protection is ignored here. RCU पढ़ो lock is assumed held, so the काष्ठा
 * will not disappear unexpectedly. Furthermore, the caller must guarantee,
 * that द्विगुन arming the same भव address (page) cannot occur.
 *
 * Double disarming on the other hand is allowed, and may occur when a fault
 * and mmiotrace shutकरोwn happen simultaneously.
 */
अटल पूर्णांक arm_kmmio_fault_page(काष्ठा kmmio_fault_page *f)
अणु
	पूर्णांक ret;
	WARN_ONCE(f->armed, KERN_ERR pr_fmt("kmmio page already armed.\n"));
	अगर (f->armed) अणु
		pr_warn("double-arm: addr 0x%08lx, ref %d, old %d\n",
			f->addr, f->count, !!f->old_presence);
	पूर्ण
	ret = clear_page_presence(f, true);
	WARN_ONCE(ret < 0, KERN_ERR pr_fmt("arming at 0x%08lx failed.\n"),
		  f->addr);
	f->armed = true;
	वापस ret;
पूर्ण

/** Restore the given page to saved presence state. */
अटल व्योम disarm_kmmio_fault_page(काष्ठा kmmio_fault_page *f)
अणु
	पूर्णांक ret = clear_page_presence(f, false);
	WARN_ONCE(ret < 0,
			KERN_ERR "kmmio disarming at 0x%08lx failed.\n", f->addr);
	f->armed = false;
पूर्ण

/*
 * This is being called from करो_page_fault().
 *
 * We may be in an पूर्णांकerrupt or a critical section. Also prefecthing may
 * trigger a page fault. We may be in the middle of process चयन.
 * We cannot take any locks, because we could be executing especially
 * within a kmmio critical section.
 *
 * Local पूर्णांकerrupts are disabled, so preemption cannot happen.
 * Do not enable पूर्णांकerrupts, करो not sleep, and watch out क्रम other CPUs.
 */
/*
 * Interrupts are disabled on entry as trap3 is an पूर्णांकerrupt gate
 * and they reमुख्य disabled throughout this function.
 */
पूर्णांक kmmio_handler(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	काष्ठा kmmio_context *ctx;
	काष्ठा kmmio_fault_page *faultpage;
	पूर्णांक ret = 0; /* शेष to fault not handled */
	अचिन्हित दीर्घ page_base = addr;
	अचिन्हित पूर्णांक l;
	pte_t *pte = lookup_address(addr, &l);
	अगर (!pte)
		वापस -EINVAL;
	page_base &= page_level_mask(l);

	/*
	 * Preemption is now disabled to prevent process चयन during
	 * single stepping. We can only handle one active kmmio trace
	 * per cpu, so ensure that we finish it beक्रमe something अन्यथा
	 * माला_लो to run. We also hold the RCU पढ़ो lock over single
	 * stepping to aव्योम looking up the probe and kmmio_fault_page
	 * again.
	 */
	preempt_disable();
	rcu_पढ़ो_lock();

	faultpage = get_kmmio_fault_page(page_base);
	अगर (!faultpage) अणु
		/*
		 * Either this page fault is not caused by kmmio, or
		 * another CPU just pulled the kmmio probe from under
		 * our feet. The latter हाल should not be possible.
		 */
		जाओ no_kmmio;
	पूर्ण

	ctx = this_cpu_ptr(&kmmio_ctx);
	अगर (ctx->active) अणु
		अगर (page_base == ctx->addr) अणु
			/*
			 * A second fault on the same page means some other
			 * condition needs handling by करो_page_fault(), the
			 * page really not being present is the most common.
			 */
			pr_debug("secondary hit for 0x%08lx CPU %d.\n",
				 addr, smp_processor_id());

			अगर (!faultpage->old_presence)
				pr_info("unexpected secondary hit for address 0x%08lx on CPU %d.\n",
					addr, smp_processor_id());
		पूर्ण अन्यथा अणु
			/*
			 * Prevent overwriting alपढ़ोy in-flight context.
			 * This should not happen, let's hope disarming at
			 * least prevents a panic.
			 */
			pr_emerg("recursive probe hit on CPU %d, for address 0x%08lx. Ignoring.\n",
				 smp_processor_id(), addr);
			pr_emerg("previous hit was at 0x%08lx.\n", ctx->addr);
			disarm_kmmio_fault_page(faultpage);
		पूर्ण
		जाओ no_kmmio;
	पूर्ण
	ctx->active++;

	ctx->fpage = faultpage;
	ctx->probe = get_kmmio_probe(page_base);
	ctx->saved_flags = (regs->flags & (X86_EFLAGS_TF | X86_EFLAGS_IF));
	ctx->addr = page_base;

	अगर (ctx->probe && ctx->probe->pre_handler)
		ctx->probe->pre_handler(ctx->probe, regs, addr);

	/*
	 * Enable single-stepping and disable पूर्णांकerrupts क्रम the faulting
	 * context. Local पूर्णांकerrupts must not get enabled during stepping.
	 */
	regs->flags |= X86_EFLAGS_TF;
	regs->flags &= ~X86_EFLAGS_IF;

	/* Now we set present bit in PTE and single step. */
	disarm_kmmio_fault_page(ctx->fpage);

	/*
	 * If another cpu accesses the same page जबतक we are stepping,
	 * the access will not be caught. It will simply succeed and the
	 * only करोwnside is we lose the event. If this becomes a problem,
	 * the user should drop to single cpu beक्रमe tracing.
	 */

	वापस 1; /* fault handled */

no_kmmio:
	rcu_पढ़ो_unlock();
	preempt_enable_no_resched();
	वापस ret;
पूर्ण

/*
 * Interrupts are disabled on entry as trap1 is an पूर्णांकerrupt gate
 * and they reमुख्य disabled throughout this function.
 * This must always get called as the pair to kmmio_handler().
 */
अटल पूर्णांक post_kmmio_handler(अचिन्हित दीर्घ condition, काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret = 0;
	काष्ठा kmmio_context *ctx = this_cpu_ptr(&kmmio_ctx);

	अगर (!ctx->active) अणु
		/*
		 * debug traps without an active context are due to either
		 * something बाह्यal causing them (f.e. using a debugger जबतक
		 * mmio tracing enabled), or erroneous behaviour
		 */
		pr_warn("unexpected debug trap on CPU %d.\n", smp_processor_id());
		जाओ out;
	पूर्ण

	अगर (ctx->probe && ctx->probe->post_handler)
		ctx->probe->post_handler(ctx->probe, condition, regs);

	/* Prevent racing against release_kmmio_fault_page(). */
	spin_lock(&kmmio_lock);
	अगर (ctx->fpage->count)
		arm_kmmio_fault_page(ctx->fpage);
	spin_unlock(&kmmio_lock);

	regs->flags &= ~X86_EFLAGS_TF;
	regs->flags |= ctx->saved_flags;

	/* These were acquired in kmmio_handler(). */
	ctx->active--;
	BUG_ON(ctx->active);
	rcu_पढ़ो_unlock();
	preempt_enable_no_resched();

	/*
	 * अगर somebody अन्यथा is singlestepping across a probe poपूर्णांक, flags
	 * will have TF set, in which हाल, जारी the reमुख्यing processing
	 * of करो_debug, as अगर this is not a probe hit.
	 */
	अगर (!(regs->flags & X86_EFLAGS_TF))
		ret = 1;
out:
	वापस ret;
पूर्ण

/* You must be holding kmmio_lock. */
अटल पूर्णांक add_kmmio_fault_page(अचिन्हित दीर्घ addr)
अणु
	काष्ठा kmmio_fault_page *f;

	f = get_kmmio_fault_page(addr);
	अगर (f) अणु
		अगर (!f->count)
			arm_kmmio_fault_page(f);
		f->count++;
		वापस 0;
	पूर्ण

	f = kzalloc(माप(*f), GFP_ATOMIC);
	अगर (!f)
		वापस -1;

	f->count = 1;
	f->addr = addr;

	अगर (arm_kmmio_fault_page(f)) अणु
		kमुक्त(f);
		वापस -1;
	पूर्ण

	list_add_rcu(&f->list, kmmio_page_list(f->addr));

	वापस 0;
पूर्ण

/* You must be holding kmmio_lock. */
अटल व्योम release_kmmio_fault_page(अचिन्हित दीर्घ addr,
				काष्ठा kmmio_fault_page **release_list)
अणु
	काष्ठा kmmio_fault_page *f;

	f = get_kmmio_fault_page(addr);
	अगर (!f)
		वापस;

	f->count--;
	BUG_ON(f->count < 0);
	अगर (!f->count) अणु
		disarm_kmmio_fault_page(f);
		अगर (!f->scheduled_क्रम_release) अणु
			f->release_next = *release_list;
			*release_list = f;
			f->scheduled_क्रम_release = true;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * With page-unaligned ioremaps, one or two armed pages may contain
 * addresses from outside the पूर्णांकended mapping. Events क्रम these addresses
 * are currently silently dropped. The events may result only from programming
 * mistakes by accessing addresses beक्रमe the beginning or past the end of a
 * mapping.
 */
पूर्णांक रेजिस्टर_kmmio_probe(काष्ठा kmmio_probe *p)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ size = 0;
	अचिन्हित दीर्घ addr = p->addr & PAGE_MASK;
	स्थिर अचिन्हित दीर्घ size_lim = p->len + (p->addr & ~PAGE_MASK);
	अचिन्हित पूर्णांक l;
	pte_t *pte;

	spin_lock_irqsave(&kmmio_lock, flags);
	अगर (get_kmmio_probe(addr)) अणु
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	pte = lookup_address(addr, &l);
	अगर (!pte) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	kmmio_count++;
	list_add_rcu(&p->list, &kmmio_probes);
	जबतक (size < size_lim) अणु
		अगर (add_kmmio_fault_page(addr + size))
			pr_err("Unable to set page fault.\n");
		size += page_level_size(l);
	पूर्ण
out:
	spin_unlock_irqrestore(&kmmio_lock, flags);
	/*
	 * XXX: What should I करो here?
	 * Here was a call to global_flush_tlb(), but it करोes not exist
	 * anymore. It seems it's not needed after all.
	 */
	वापस ret;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_kmmio_probe);

अटल व्योम rcu_मुक्त_kmmio_fault_pages(काष्ठा rcu_head *head)
अणु
	काष्ठा kmmio_delayed_release *dr = container_of(
						head,
						काष्ठा kmmio_delayed_release,
						rcu);
	काष्ठा kmmio_fault_page *f = dr->release_list;
	जबतक (f) अणु
		काष्ठा kmmio_fault_page *next = f->release_next;
		BUG_ON(f->count);
		kमुक्त(f);
		f = next;
	पूर्ण
	kमुक्त(dr);
पूर्ण

अटल व्योम हटाओ_kmmio_fault_pages(काष्ठा rcu_head *head)
अणु
	काष्ठा kmmio_delayed_release *dr =
		container_of(head, काष्ठा kmmio_delayed_release, rcu);
	काष्ठा kmmio_fault_page *f = dr->release_list;
	काष्ठा kmmio_fault_page **prevp = &dr->release_list;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kmmio_lock, flags);
	जबतक (f) अणु
		अगर (!f->count) अणु
			list_del_rcu(&f->list);
			prevp = &f->release_next;
		पूर्ण अन्यथा अणु
			*prevp = f->release_next;
			f->release_next = शून्य;
			f->scheduled_क्रम_release = false;
		पूर्ण
		f = *prevp;
	पूर्ण
	spin_unlock_irqrestore(&kmmio_lock, flags);

	/* This is the real RCU destroy call. */
	call_rcu(&dr->rcu, rcu_मुक्त_kmmio_fault_pages);
पूर्ण

/*
 * Remove a kmmio probe. You have to synchronize_rcu() beक्रमe you can be
 * sure that the callbacks will not be called anymore. Only after that
 * you may actually release your काष्ठा kmmio_probe.
 *
 * Unरेजिस्टरing a kmmio fault page has three steps:
 * 1. release_kmmio_fault_page()
 *    Disarm the page, रुको a grace period to let all faults finish.
 * 2. हटाओ_kmmio_fault_pages()
 *    Remove the pages from kmmio_page_table.
 * 3. rcu_मुक्त_kmmio_fault_pages()
 *    Actually मुक्त the kmmio_fault_page काष्ठाs as with RCU.
 */
व्योम unरेजिस्टर_kmmio_probe(काष्ठा kmmio_probe *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ size = 0;
	अचिन्हित दीर्घ addr = p->addr & PAGE_MASK;
	स्थिर अचिन्हित दीर्घ size_lim = p->len + (p->addr & ~PAGE_MASK);
	काष्ठा kmmio_fault_page *release_list = शून्य;
	काष्ठा kmmio_delayed_release *drelease;
	अचिन्हित पूर्णांक l;
	pte_t *pte;

	pte = lookup_address(addr, &l);
	अगर (!pte)
		वापस;

	spin_lock_irqsave(&kmmio_lock, flags);
	जबतक (size < size_lim) अणु
		release_kmmio_fault_page(addr + size, &release_list);
		size += page_level_size(l);
	पूर्ण
	list_del_rcu(&p->list);
	kmmio_count--;
	spin_unlock_irqrestore(&kmmio_lock, flags);

	अगर (!release_list)
		वापस;

	drelease = kदो_स्मृति(माप(*drelease), GFP_ATOMIC);
	अगर (!drelease) अणु
		pr_crit("leaking kmmio_fault_page objects.\n");
		वापस;
	पूर्ण
	drelease->release_list = release_list;

	/*
	 * This is not really RCU here. We have just disarmed a set of
	 * pages so that they cannot trigger page faults anymore. However,
	 * we cannot हटाओ the pages from kmmio_page_table,
	 * because a probe hit might be in flight on another CPU. The
	 * pages are collected पूर्णांकo a list, and they will be हटाओd from
	 * kmmio_page_table when it is certain that no probe hit related to
	 * these pages can be in flight. RCU grace period sounds like a
	 * good choice.
	 *
	 * If we हटाओd the pages too early, kmmio page fault handler might
	 * not find the respective kmmio_fault_page and determine it's not
	 * a kmmio fault, when it actually is. This would lead to madness.
	 */
	call_rcu(&drelease->rcu, हटाओ_kmmio_fault_pages);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_kmmio_probe);

अटल पूर्णांक
kmmio_die_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val, व्योम *args)
अणु
	काष्ठा die_args *arg = args;
	अचिन्हित दीर्घ* dr6_p = (अचिन्हित दीर्घ *)ERR_PTR(arg->err);

	अगर (val == DIE_DEBUG && (*dr6_p & DR_STEP))
		अगर (post_kmmio_handler(*dr6_p, arg->regs) == 1) अणु
			/*
			 * Reset the BS bit in dr6 (poपूर्णांकed by args->err) to
			 * denote completion of processing
			 */
			*dr6_p &= ~DR_STEP;
			वापस NOTIFY_STOP;
		पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nb_die = अणु
	.notअगरier_call = kmmio_die_notअगरier
पूर्ण;

पूर्णांक kmmio_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KMMIO_PAGE_TABLE_SIZE; i++)
		INIT_LIST_HEAD(&kmmio_page_table[i]);

	वापस रेजिस्टर_die_notअगरier(&nb_die);
पूर्ण

व्योम kmmio_cleanup(व्योम)
अणु
	पूर्णांक i;

	unरेजिस्टर_die_notअगरier(&nb_die);
	क्रम (i = 0; i < KMMIO_PAGE_TABLE_SIZE; i++) अणु
		WARN_ONCE(!list_empty(&kmmio_page_table[i]),
			KERN_ERR "kmmio_page_table not empty at cleanup, any further tracing will leak memory.\n");
	पूर्ण
पूर्ण
