<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Kernel Probes (KProbes)
 *  kernel/kprobes.c
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 *
 * 2002-Oct	Created by Vamsi Krishna S <vamsi_krishna@in.ibm.com> Kernel
 *		Probes initial implementation (includes suggestions from
 *		Rusty Russell).
 * 2004-Aug	Updated by Prasanna S Panchamukhi <prasanna@in.ibm.com> with
 *		hlists and exceptions notअगरier as suggested by Andi Kleen.
 * 2004-July	Suparna Bhattaअक्षरya <suparna@in.ibm.com> added jumper probes
 *		पूर्णांकerface to access function arguments.
 * 2004-Sep	Prasanna S Panchamukhi <prasanna@in.ibm.com> Changed Kprobes
 *		exceptions notअगरier to be first on the priority list.
 * 2005-May	Hien Nguyen <hien@us.ibm.com>, Jim Keniston
 *		<jkenisto@us.ibm.com> and Prasanna S Panchamukhi
 *		<prasanna@in.ibm.com> added function-वापस probes.
 */
#समावेश <linux/kprobes.h>
#समावेश <linux/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/export.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/memory.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/cpu.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#घोषणा KPROBE_HASH_BITS 6
#घोषणा KPROBE_TABLE_SIZE (1 << KPROBE_HASH_BITS)


अटल पूर्णांक kprobes_initialized;
/* kprobe_table can be accessed by
 * - Normal hlist traversal and RCU add/del under kprobe_mutex is held.
 * Or
 * - RCU hlist traversal under disabling preempt (अवरोधpoपूर्णांक handlers)
 */
अटल काष्ठा hlist_head kprobe_table[KPROBE_TABLE_SIZE];

/* NOTE: change this value only with kprobe_mutex held */
अटल bool kprobes_all_disarmed;

/* This protects kprobe_table and optimizing_list */
अटल DEFINE_MUTEX(kprobe_mutex);
अटल DEFINE_PER_CPU(काष्ठा kprobe *, kprobe_instance) = शून्य;

kprobe_opcode_t * __weak kprobe_lookup_name(स्थिर अक्षर *name,
					अचिन्हित पूर्णांक __unused)
अणु
	वापस ((kprobe_opcode_t *)(kallsyms_lookup_name(name)));
पूर्ण

/* Blacklist -- list of काष्ठा kprobe_blacklist_entry */
अटल LIST_HEAD(kprobe_blacklist);

#अगर_घोषित __ARCH_WANT_KPROBES_INSN_SLOT
/*
 * kprobe->ainsn.insn poपूर्णांकs to the copy of the inकाष्ठाion to be
 * single-stepped. x86_64, POWER4 and above have no-exec support and
 * stepping on the inकाष्ठाion on a vदो_स्मृतिed/kदो_स्मृतिed/data page
 * is a recipe क्रम disaster
 */
काष्ठा kprobe_insn_page अणु
	काष्ठा list_head list;
	kprobe_opcode_t *insns;		/* Page of inकाष्ठाion slots */
	काष्ठा kprobe_insn_cache *cache;
	पूर्णांक nused;
	पूर्णांक ngarbage;
	अक्षर slot_used[];
पूर्ण;

#घोषणा KPROBE_INSN_PAGE_SIZE(slots)			\
	(दुरत्व(काष्ठा kprobe_insn_page, slot_used) +	\
	 (माप(अक्षर) * (slots)))

अटल पूर्णांक slots_per_page(काष्ठा kprobe_insn_cache *c)
अणु
	वापस PAGE_SIZE/(c->insn_size * माप(kprobe_opcode_t));
पूर्ण

क्रमागत kprobe_slot_state अणु
	SLOT_CLEAN = 0,
	SLOT_सूचीTY = 1,
	SLOT_USED = 2,
पूर्ण;

व्योम __weak *alloc_insn_page(व्योम)
अणु
	वापस module_alloc(PAGE_SIZE);
पूर्ण

व्योम __weak मुक्त_insn_page(व्योम *page)
अणु
	module_memमुक्त(page);
पूर्ण

काष्ठा kprobe_insn_cache kprobe_insn_slots = अणु
	.mutex = __MUTEX_INITIALIZER(kprobe_insn_slots.mutex),
	.alloc = alloc_insn_page,
	.मुक्त = मुक्त_insn_page,
	.sym = KPROBE_INSN_PAGE_SYM,
	.pages = LIST_HEAD_INIT(kprobe_insn_slots.pages),
	.insn_size = MAX_INSN_SIZE,
	.nr_garbage = 0,
पूर्ण;
अटल पूर्णांक collect_garbage_slots(काष्ठा kprobe_insn_cache *c);

/**
 * __get_insn_slot() - Find a slot on an executable page क्रम an inकाष्ठाion.
 * We allocate an executable page अगर there's no room on existing ones.
 */
kprobe_opcode_t *__get_insn_slot(काष्ठा kprobe_insn_cache *c)
अणु
	काष्ठा kprobe_insn_page *kip;
	kprobe_opcode_t *slot = शून्य;

	/* Since the slot array is not रक्षित by rcu, we need a mutex */
	mutex_lock(&c->mutex);
 retry:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(kip, &c->pages, list) अणु
		अगर (kip->nused < slots_per_page(c)) अणु
			पूर्णांक i;
			क्रम (i = 0; i < slots_per_page(c); i++) अणु
				अगर (kip->slot_used[i] == SLOT_CLEAN) अणु
					kip->slot_used[i] = SLOT_USED;
					kip->nused++;
					slot = kip->insns + (i * c->insn_size);
					rcu_पढ़ो_unlock();
					जाओ out;
				पूर्ण
			पूर्ण
			/* kip->nused is broken. Fix it. */
			kip->nused = slots_per_page(c);
			WARN_ON(1);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/* If there are any garbage slots, collect it and try again. */
	अगर (c->nr_garbage && collect_garbage_slots(c) == 0)
		जाओ retry;

	/* All out of space.  Need to allocate a new page. */
	kip = kदो_स्मृति(KPROBE_INSN_PAGE_SIZE(slots_per_page(c)), GFP_KERNEL);
	अगर (!kip)
		जाओ out;

	/*
	 * Use module_alloc so this page is within +/- 2GB of where the
	 * kernel image and loaded module images reside. This is required
	 * so x86_64 can correctly handle the %rip-relative fixups.
	 */
	kip->insns = c->alloc();
	अगर (!kip->insns) अणु
		kमुक्त(kip);
		जाओ out;
	पूर्ण
	INIT_LIST_HEAD(&kip->list);
	स_रखो(kip->slot_used, SLOT_CLEAN, slots_per_page(c));
	kip->slot_used[0] = SLOT_USED;
	kip->nused = 1;
	kip->ngarbage = 0;
	kip->cache = c;
	list_add_rcu(&kip->list, &c->pages);
	slot = kip->insns;

	/* Record the perf ksymbol रेजिस्टर event after adding the page */
	perf_event_ksymbol(PERF_RECORD_KSYMBOL_TYPE_OOL, (अचिन्हित दीर्घ)kip->insns,
			   PAGE_SIZE, false, c->sym);
out:
	mutex_unlock(&c->mutex);
	वापस slot;
पूर्ण

/* Return 1 अगर all garbages are collected, otherwise 0. */
अटल पूर्णांक collect_one_slot(काष्ठा kprobe_insn_page *kip, पूर्णांक idx)
अणु
	kip->slot_used[idx] = SLOT_CLEAN;
	kip->nused--;
	अगर (kip->nused == 0) अणु
		/*
		 * Page is no दीर्घer in use.  Free it unless
		 * it's the last one.  We keep the last one
		 * so as not to have to set it up again the
		 * next समय somebody inserts a probe.
		 */
		अगर (!list_is_singular(&kip->list)) अणु
			/*
			 * Record perf ksymbol unरेजिस्टर event beक्रमe removing
			 * the page.
			 */
			perf_event_ksymbol(PERF_RECORD_KSYMBOL_TYPE_OOL,
					   (अचिन्हित दीर्घ)kip->insns, PAGE_SIZE, true,
					   kip->cache->sym);
			list_del_rcu(&kip->list);
			synchronize_rcu();
			kip->cache->मुक्त(kip->insns);
			kमुक्त(kip);
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक collect_garbage_slots(काष्ठा kprobe_insn_cache *c)
अणु
	काष्ठा kprobe_insn_page *kip, *next;

	/* Ensure no-one is पूर्णांकerrupted on the garbages */
	synchronize_rcu();

	list_क्रम_each_entry_safe(kip, next, &c->pages, list) अणु
		पूर्णांक i;
		अगर (kip->ngarbage == 0)
			जारी;
		kip->ngarbage = 0;	/* we will collect all garbages */
		क्रम (i = 0; i < slots_per_page(c); i++) अणु
			अगर (kip->slot_used[i] == SLOT_सूचीTY && collect_one_slot(kip, i))
				अवरोध;
		पूर्ण
	पूर्ण
	c->nr_garbage = 0;
	वापस 0;
पूर्ण

व्योम __मुक्त_insn_slot(काष्ठा kprobe_insn_cache *c,
		      kprobe_opcode_t *slot, पूर्णांक dirty)
अणु
	काष्ठा kprobe_insn_page *kip;
	दीर्घ idx;

	mutex_lock(&c->mutex);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(kip, &c->pages, list) अणु
		idx = ((दीर्घ)slot - (दीर्घ)kip->insns) /
			(c->insn_size * माप(kprobe_opcode_t));
		अगर (idx >= 0 && idx < slots_per_page(c))
			जाओ out;
	पूर्ण
	/* Could not find this slot. */
	WARN_ON(1);
	kip = शून्य;
out:
	rcu_पढ़ो_unlock();
	/* Mark and sweep: this may sleep */
	अगर (kip) अणु
		/* Check द्विगुन मुक्त */
		WARN_ON(kip->slot_used[idx] != SLOT_USED);
		अगर (dirty) अणु
			kip->slot_used[idx] = SLOT_सूचीTY;
			kip->ngarbage++;
			अगर (++c->nr_garbage > slots_per_page(c))
				collect_garbage_slots(c);
		पूर्ण अन्यथा अणु
			collect_one_slot(kip, idx);
		पूर्ण
	पूर्ण
	mutex_unlock(&c->mutex);
पूर्ण

/*
 * Check given address is on the page of kprobe inकाष्ठाion slots.
 * This will be used क्रम checking whether the address on a stack
 * is on a text area or not.
 */
bool __is_insn_slot_addr(काष्ठा kprobe_insn_cache *c, अचिन्हित दीर्घ addr)
अणु
	काष्ठा kprobe_insn_page *kip;
	bool ret = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(kip, &c->pages, list) अणु
		अगर (addr >= (अचिन्हित दीर्घ)kip->insns &&
		    addr < (अचिन्हित दीर्घ)kip->insns + PAGE_SIZE) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

पूर्णांक kprobe_cache_get_kallsym(काष्ठा kprobe_insn_cache *c, अचिन्हित पूर्णांक *symnum,
			     अचिन्हित दीर्घ *value, अक्षर *type, अक्षर *sym)
अणु
	काष्ठा kprobe_insn_page *kip;
	पूर्णांक ret = -दुस्फल;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(kip, &c->pages, list) अणु
		अगर ((*symnum)--)
			जारी;
		strlcpy(sym, c->sym, KSYM_NAME_LEN);
		*type = 't';
		*value = (अचिन्हित दीर्घ)kip->insns;
		ret = 0;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OPTPROBES
/* For optimized_kprobe buffer */
काष्ठा kprobe_insn_cache kprobe_optinsn_slots = अणु
	.mutex = __MUTEX_INITIALIZER(kprobe_optinsn_slots.mutex),
	.alloc = alloc_insn_page,
	.मुक्त = मुक्त_insn_page,
	.sym = KPROBE_OPTINSN_PAGE_SYM,
	.pages = LIST_HEAD_INIT(kprobe_optinsn_slots.pages),
	/* .insn_size is initialized later */
	.nr_garbage = 0,
पूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर

/* We have preemption disabled.. so it is safe to use __ versions */
अटल अंतरभूत व्योम set_kprobe_instance(काष्ठा kprobe *kp)
अणु
	__this_cpu_ग_लिखो(kprobe_instance, kp);
पूर्ण

अटल अंतरभूत व्योम reset_kprobe_instance(व्योम)
अणु
	__this_cpu_ग_लिखो(kprobe_instance, शून्य);
पूर्ण

/*
 * This routine is called either:
 * 	- under the kprobe_mutex - during kprobe_[un]रेजिस्टर()
 * 				OR
 * 	- with preemption disabled - from arch/xxx/kernel/kprobes.c
 */
काष्ठा kprobe *get_kprobe(व्योम *addr)
अणु
	काष्ठा hlist_head *head;
	काष्ठा kprobe *p;

	head = &kprobe_table[hash_ptr(addr, KPROBE_HASH_BITS)];
	hlist_क्रम_each_entry_rcu(p, head, hlist,
				 lockdep_is_held(&kprobe_mutex)) अणु
		अगर (p->addr == addr)
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण
NOKPROBE_SYMBOL(get_kprobe);

अटल पूर्णांक aggr_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs);

/* Return true अगर the kprobe is an aggregator */
अटल अंतरभूत पूर्णांक kprobe_aggrprobe(काष्ठा kprobe *p)
अणु
	वापस p->pre_handler == aggr_pre_handler;
पूर्ण

/* Return true(!0) अगर the kprobe is unused */
अटल अंतरभूत पूर्णांक kprobe_unused(काष्ठा kprobe *p)
अणु
	वापस kprobe_aggrprobe(p) && kprobe_disabled(p) &&
	       list_empty(&p->list);
पूर्ण

/*
 * Keep all fields in the kprobe consistent
 */
अटल अंतरभूत व्योम copy_kprobe(काष्ठा kprobe *ap, काष्ठा kprobe *p)
अणु
	स_नकल(&p->opcode, &ap->opcode, माप(kprobe_opcode_t));
	स_नकल(&p->ainsn, &ap->ainsn, माप(काष्ठा arch_specअगरic_insn));
पूर्ण

#अगर_घोषित CONFIG_OPTPROBES
/* NOTE: change this value only with kprobe_mutex held */
अटल bool kprobes_allow_optimization;

/*
 * Call all pre_handler on the list, but ignores its वापस value.
 * This must be called from arch-dep optimized caller.
 */
व्योम opt_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *kp;

	list_क्रम_each_entry_rcu(kp, &p->list, list) अणु
		अगर (kp->pre_handler && likely(!kprobe_disabled(kp))) अणु
			set_kprobe_instance(kp);
			kp->pre_handler(kp, regs);
		पूर्ण
		reset_kprobe_instance();
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(opt_pre_handler);

/* Free optimized inकाष्ठाions and optimized_kprobe */
अटल व्योम मुक्त_aggr_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा optimized_kprobe *op;

	op = container_of(p, काष्ठा optimized_kprobe, kp);
	arch_हटाओ_optimized_kprobe(op);
	arch_हटाओ_kprobe(p);
	kमुक्त(op);
पूर्ण

/* Return true(!0) अगर the kprobe is पढ़ोy क्रम optimization. */
अटल अंतरभूत पूर्णांक kprobe_optपढ़ोy(काष्ठा kprobe *p)
अणु
	काष्ठा optimized_kprobe *op;

	अगर (kprobe_aggrprobe(p)) अणु
		op = container_of(p, काष्ठा optimized_kprobe, kp);
		वापस arch_prepared_optinsn(&op->optinsn);
	पूर्ण

	वापस 0;
पूर्ण

/* Return true(!0) अगर the kprobe is disarmed. Note: p must be on hash list */
अटल अंतरभूत पूर्णांक kprobe_disarmed(काष्ठा kprobe *p)
अणु
	काष्ठा optimized_kprobe *op;

	/* If kprobe is not aggr/opt probe, just वापस kprobe is disabled */
	अगर (!kprobe_aggrprobe(p))
		वापस kprobe_disabled(p);

	op = container_of(p, काष्ठा optimized_kprobe, kp);

	वापस kprobe_disabled(p) && list_empty(&op->list);
पूर्ण

/* Return true(!0) अगर the probe is queued on (un)optimizing lists */
अटल पूर्णांक kprobe_queued(काष्ठा kprobe *p)
अणु
	काष्ठा optimized_kprobe *op;

	अगर (kprobe_aggrprobe(p)) अणु
		op = container_of(p, काष्ठा optimized_kprobe, kp);
		अगर (!list_empty(&op->list))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return an optimized kprobe whose optimizing code replaces
 * inकाष्ठाions including addr (exclude अवरोधpoपूर्णांक).
 */
अटल काष्ठा kprobe *get_optimized_kprobe(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक i;
	काष्ठा kprobe *p = शून्य;
	काष्ठा optimized_kprobe *op;

	/* Don't check i == 0, since that is a अवरोधpoपूर्णांक हाल. */
	क्रम (i = 1; !p && i < MAX_OPTIMIZED_LENGTH; i++)
		p = get_kprobe((व्योम *)(addr - i));

	अगर (p && kprobe_optपढ़ोy(p)) अणु
		op = container_of(p, काष्ठा optimized_kprobe, kp);
		अगर (arch_within_optimized_kprobe(op, addr))
			वापस p;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Optimization staging list, रक्षित by kprobe_mutex */
अटल LIST_HEAD(optimizing_list);
अटल LIST_HEAD(unoptimizing_list);
अटल LIST_HEAD(मुक्तing_list);

अटल व्योम kprobe_optimizer(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(optimizing_work, kprobe_optimizer);
#घोषणा OPTIMIZE_DELAY 5

/*
 * Optimize (replace a अवरोधpoपूर्णांक with a jump) kprobes listed on
 * optimizing_list.
 */
अटल व्योम करो_optimize_kprobes(व्योम)
अणु
	lockdep_निश्चित_held(&text_mutex);
	/*
	 * The optimization/unoptimization refers online_cpus via
	 * stop_machine() and cpu-hotplug modअगरies online_cpus.
	 * And same समय, text_mutex will be held in cpu-hotplug and here.
	 * This combination can cause a deadlock (cpu-hotplug try to lock
	 * text_mutex but stop_machine can not be करोne because online_cpus
	 * has been changed)
	 * To aव्योम this deadlock, caller must have locked cpu hotplug
	 * क्रम preventing cpu-hotplug outside of text_mutex locking.
	 */
	lockdep_निश्चित_cpus_held();

	/* Optimization never be करोne when disarmed */
	अगर (kprobes_all_disarmed || !kprobes_allow_optimization ||
	    list_empty(&optimizing_list))
		वापस;

	arch_optimize_kprobes(&optimizing_list);
पूर्ण

/*
 * Unoptimize (replace a jump with a अवरोधpoपूर्णांक and हटाओ the अवरोधpoपूर्णांक
 * अगर need) kprobes listed on unoptimizing_list.
 */
अटल व्योम करो_unoptimize_kprobes(व्योम)
अणु
	काष्ठा optimized_kprobe *op, *पंचांगp;

	lockdep_निश्चित_held(&text_mutex);
	/* See comment in करो_optimize_kprobes() */
	lockdep_निश्चित_cpus_held();

	/* Unoptimization must be करोne anyसमय */
	अगर (list_empty(&unoptimizing_list))
		वापस;

	arch_unoptimize_kprobes(&unoptimizing_list, &मुक्तing_list);
	/* Loop मुक्त_list क्रम disarming */
	list_क्रम_each_entry_safe(op, पंचांगp, &मुक्तing_list, list) अणु
		/* Switching from detour code to origin */
		op->kp.flags &= ~KPROBE_FLAG_OPTIMIZED;
		/* Disarm probes अगर marked disabled */
		अगर (kprobe_disabled(&op->kp))
			arch_disarm_kprobe(&op->kp);
		अगर (kprobe_unused(&op->kp)) अणु
			/*
			 * Remove unused probes from hash list. After रुकोing
			 * क्रम synchronization, these probes are reclaimed.
			 * (reclaiming is करोne by करो_मुक्त_cleaned_kprobes.)
			 */
			hlist_del_rcu(&op->kp.hlist);
		पूर्ण अन्यथा
			list_del_init(&op->list);
	पूर्ण
पूर्ण

/* Reclaim all kprobes on the मुक्त_list */
अटल व्योम करो_मुक्त_cleaned_kprobes(व्योम)
अणु
	काष्ठा optimized_kprobe *op, *पंचांगp;

	list_क्रम_each_entry_safe(op, पंचांगp, &मुक्तing_list, list) अणु
		list_del_init(&op->list);
		अगर (WARN_ON_ONCE(!kprobe_unused(&op->kp))) अणु
			/*
			 * This must not happen, but अगर there is a kprobe
			 * still in use, keep it on kprobes hash list.
			 */
			जारी;
		पूर्ण
		मुक्त_aggr_kprobe(&op->kp);
	पूर्ण
पूर्ण

/* Start optimizer after OPTIMIZE_DELAY passed */
अटल व्योम kick_kprobe_optimizer(व्योम)
अणु
	schedule_delayed_work(&optimizing_work, OPTIMIZE_DELAY);
पूर्ण

/* Kprobe jump optimizer */
अटल व्योम kprobe_optimizer(काष्ठा work_काष्ठा *work)
अणु
	mutex_lock(&kprobe_mutex);
	cpus_पढ़ो_lock();
	mutex_lock(&text_mutex);

	/*
	 * Step 1: Unoptimize kprobes and collect cleaned (unused and disarmed)
	 * kprobes beक्रमe रुकोing क्रम quiesence period.
	 */
	करो_unoptimize_kprobes();

	/*
	 * Step 2: Wait क्रम quiesence period to ensure all potentially
	 * preempted tasks to have normally scheduled. Because optprobe
	 * may modअगरy multiple inकाष्ठाions, there is a chance that Nth
	 * inकाष्ठाion is preempted. In that हाल, such tasks can वापस
	 * to 2nd-Nth byte of jump inकाष्ठाion. This रुको is क्रम aव्योमing it.
	 * Note that on non-preemptive kernel, this is transparently converted
	 * to synchronoze_sched() to रुको क्रम all पूर्णांकerrupts to have completed.
	 */
	synchronize_rcu_tasks();

	/* Step 3: Optimize kprobes after quiesence period */
	करो_optimize_kprobes();

	/* Step 4: Free cleaned kprobes after quiesence period */
	करो_मुक्त_cleaned_kprobes();

	mutex_unlock(&text_mutex);
	cpus_पढ़ो_unlock();

	/* Step 5: Kick optimizer again अगर needed */
	अगर (!list_empty(&optimizing_list) || !list_empty(&unoptimizing_list))
		kick_kprobe_optimizer();

	mutex_unlock(&kprobe_mutex);
पूर्ण

/* Wait क्रम completing optimization and unoptimization */
व्योम रुको_क्रम_kprobe_optimizer(व्योम)
अणु
	mutex_lock(&kprobe_mutex);

	जबतक (!list_empty(&optimizing_list) || !list_empty(&unoptimizing_list)) अणु
		mutex_unlock(&kprobe_mutex);

		/* this will also make optimizing_work execute immmediately */
		flush_delayed_work(&optimizing_work);
		/* @optimizing_work might not have been queued yet, relax */
		cpu_relax();

		mutex_lock(&kprobe_mutex);
	पूर्ण

	mutex_unlock(&kprobe_mutex);
पूर्ण

अटल bool optprobe_queued_unopt(काष्ठा optimized_kprobe *op)
अणु
	काष्ठा optimized_kprobe *_op;

	list_क्रम_each_entry(_op, &unoptimizing_list, list) अणु
		अगर (op == _op)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Optimize kprobe अगर p is पढ़ोy to be optimized */
अटल व्योम optimize_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा optimized_kprobe *op;

	/* Check अगर the kprobe is disabled or not पढ़ोy क्रम optimization. */
	अगर (!kprobe_optपढ़ोy(p) || !kprobes_allow_optimization ||
	    (kprobe_disabled(p) || kprobes_all_disarmed))
		वापस;

	/* kprobes with post_handler can not be optimized */
	अगर (p->post_handler)
		वापस;

	op = container_of(p, काष्ठा optimized_kprobe, kp);

	/* Check there is no other kprobes at the optimized inकाष्ठाions */
	अगर (arch_check_optimized_kprobe(op) < 0)
		वापस;

	/* Check अगर it is alपढ़ोy optimized. */
	अगर (op->kp.flags & KPROBE_FLAG_OPTIMIZED) अणु
		अगर (optprobe_queued_unopt(op)) अणु
			/* This is under unoptimizing. Just dequeue the probe */
			list_del_init(&op->list);
		पूर्ण
		वापस;
	पूर्ण
	op->kp.flags |= KPROBE_FLAG_OPTIMIZED;

	/* On unoptimizing/optimizing_list, op must have OPTIMIZED flag */
	अगर (WARN_ON_ONCE(!list_empty(&op->list)))
		वापस;

	list_add(&op->list, &optimizing_list);
	kick_kprobe_optimizer();
पूर्ण

/* Short cut to direct unoptimizing */
अटल व्योम क्रमce_unoptimize_kprobe(काष्ठा optimized_kprobe *op)
अणु
	lockdep_निश्चित_cpus_held();
	arch_unoptimize_kprobe(op);
	op->kp.flags &= ~KPROBE_FLAG_OPTIMIZED;
पूर्ण

/* Unoptimize a kprobe अगर p is optimized */
अटल व्योम unoptimize_kprobe(काष्ठा kprobe *p, bool क्रमce)
अणु
	काष्ठा optimized_kprobe *op;

	अगर (!kprobe_aggrprobe(p) || kprobe_disarmed(p))
		वापस; /* This is not an optprobe nor optimized */

	op = container_of(p, काष्ठा optimized_kprobe, kp);
	अगर (!kprobe_optimized(p))
		वापस;

	अगर (!list_empty(&op->list)) अणु
		अगर (optprobe_queued_unopt(op)) अणु
			/* Queued in unoptimizing queue */
			अगर (क्रमce) अणु
				/*
				 * Forcibly unoptimize the kprobe here, and queue it
				 * in the मुक्तing list क्रम release afterwards.
				 */
				क्रमce_unoptimize_kprobe(op);
				list_move(&op->list, &मुक्तing_list);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Dequeue from the optimizing queue */
			list_del_init(&op->list);
			op->kp.flags &= ~KPROBE_FLAG_OPTIMIZED;
		पूर्ण
		वापस;
	पूर्ण

	/* Optimized kprobe हाल */
	अगर (क्रमce) अणु
		/* Forcibly update the code: this is a special हाल */
		क्रमce_unoptimize_kprobe(op);
	पूर्ण अन्यथा अणु
		list_add(&op->list, &unoptimizing_list);
		kick_kprobe_optimizer();
	पूर्ण
पूर्ण

/* Cancel unoptimizing क्रम reusing */
अटल पूर्णांक reuse_unused_kprobe(काष्ठा kprobe *ap)
अणु
	काष्ठा optimized_kprobe *op;

	/*
	 * Unused kprobe MUST be on the way of delayed unoptimizing (means
	 * there is still a relative jump) and disabled.
	 */
	op = container_of(ap, काष्ठा optimized_kprobe, kp);
	WARN_ON_ONCE(list_empty(&op->list));
	/* Enable the probe again */
	ap->flags &= ~KPROBE_FLAG_DISABLED;
	/* Optimize it again (हटाओ from op->list) */
	अगर (!kprobe_optपढ़ोy(ap))
		वापस -EINVAL;

	optimize_kprobe(ap);
	वापस 0;
पूर्ण

/* Remove optimized inकाष्ठाions */
अटल व्योम समाप्त_optimized_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा optimized_kprobe *op;

	op = container_of(p, काष्ठा optimized_kprobe, kp);
	अगर (!list_empty(&op->list))
		/* Dequeue from the (un)optimization queue */
		list_del_init(&op->list);
	op->kp.flags &= ~KPROBE_FLAG_OPTIMIZED;

	अगर (kprobe_unused(p)) अणु
		/* Enqueue अगर it is unused */
		list_add(&op->list, &मुक्तing_list);
		/*
		 * Remove unused probes from the hash list. After रुकोing
		 * क्रम synchronization, this probe is reclaimed.
		 * (reclaiming is करोne by करो_मुक्त_cleaned_kprobes().)
		 */
		hlist_del_rcu(&op->kp.hlist);
	पूर्ण

	/* Don't touch the code, because it is alपढ़ोy मुक्तd. */
	arch_हटाओ_optimized_kprobe(op);
पूर्ण

अटल अंतरभूत
व्योम __prepare_optimized_kprobe(काष्ठा optimized_kprobe *op, काष्ठा kprobe *p)
अणु
	अगर (!kprobe_ftrace(p))
		arch_prepare_optimized_kprobe(op, p);
पूर्ण

/* Try to prepare optimized inकाष्ठाions */
अटल व्योम prepare_optimized_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा optimized_kprobe *op;

	op = container_of(p, काष्ठा optimized_kprobe, kp);
	__prepare_optimized_kprobe(op, p);
पूर्ण

/* Allocate new optimized_kprobe and try to prepare optimized inकाष्ठाions */
अटल काष्ठा kprobe *alloc_aggr_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा optimized_kprobe *op;

	op = kzalloc(माप(काष्ठा optimized_kprobe), GFP_KERNEL);
	अगर (!op)
		वापस शून्य;

	INIT_LIST_HEAD(&op->list);
	op->kp.addr = p->addr;
	__prepare_optimized_kprobe(op, p);

	वापस &op->kp;
पूर्ण

अटल व्योम init_aggr_kprobe(काष्ठा kprobe *ap, काष्ठा kprobe *p);

/*
 * Prepare an optimized_kprobe and optimize it
 * NOTE: p must be a normal रेजिस्टरed kprobe
 */
अटल व्योम try_to_optimize_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *ap;
	काष्ठा optimized_kprobe *op;

	/* Impossible to optimize ftrace-based kprobe */
	अगर (kprobe_ftrace(p))
		वापस;

	/* For preparing optimization, jump_label_text_reserved() is called */
	cpus_पढ़ो_lock();
	jump_label_lock();
	mutex_lock(&text_mutex);

	ap = alloc_aggr_kprobe(p);
	अगर (!ap)
		जाओ out;

	op = container_of(ap, काष्ठा optimized_kprobe, kp);
	अगर (!arch_prepared_optinsn(&op->optinsn)) अणु
		/* If failed to setup optimizing, fallback to kprobe */
		arch_हटाओ_optimized_kprobe(op);
		kमुक्त(op);
		जाओ out;
	पूर्ण

	init_aggr_kprobe(ap, p);
	optimize_kprobe(ap);	/* This just kicks optimizer thपढ़ो */

out:
	mutex_unlock(&text_mutex);
	jump_label_unlock();
	cpus_पढ़ो_unlock();
पूर्ण

अटल व्योम optimize_all_kprobes(व्योम)
अणु
	काष्ठा hlist_head *head;
	काष्ठा kprobe *p;
	अचिन्हित पूर्णांक i;

	mutex_lock(&kprobe_mutex);
	/* If optimization is alपढ़ोy allowed, just वापस */
	अगर (kprobes_allow_optimization)
		जाओ out;

	cpus_पढ़ो_lock();
	kprobes_allow_optimization = true;
	क्रम (i = 0; i < KPROBE_TABLE_SIZE; i++) अणु
		head = &kprobe_table[i];
		hlist_क्रम_each_entry(p, head, hlist)
			अगर (!kprobe_disabled(p))
				optimize_kprobe(p);
	पूर्ण
	cpus_पढ़ो_unlock();
	prपूर्णांकk(KERN_INFO "Kprobes globally optimized\n");
out:
	mutex_unlock(&kprobe_mutex);
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल व्योम unoptimize_all_kprobes(व्योम)
अणु
	काष्ठा hlist_head *head;
	काष्ठा kprobe *p;
	अचिन्हित पूर्णांक i;

	mutex_lock(&kprobe_mutex);
	/* If optimization is alपढ़ोy prohibited, just वापस */
	अगर (!kprobes_allow_optimization) अणु
		mutex_unlock(&kprobe_mutex);
		वापस;
	पूर्ण

	cpus_पढ़ो_lock();
	kprobes_allow_optimization = false;
	क्रम (i = 0; i < KPROBE_TABLE_SIZE; i++) अणु
		head = &kprobe_table[i];
		hlist_क्रम_each_entry(p, head, hlist) अणु
			अगर (!kprobe_disabled(p))
				unoptimize_kprobe(p, false);
		पूर्ण
	पूर्ण
	cpus_पढ़ो_unlock();
	mutex_unlock(&kprobe_mutex);

	/* Wait क्रम unoptimizing completion */
	रुको_क्रम_kprobe_optimizer();
	prपूर्णांकk(KERN_INFO "Kprobes globally unoptimized\n");
पूर्ण

अटल DEFINE_MUTEX(kprobe_sysctl_mutex);
पूर्णांक sysctl_kprobes_optimization;
पूर्णांक proc_kprobes_optimization_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				      व्योम *buffer, माप_प्रकार *length,
				      loff_t *ppos)
अणु
	पूर्णांक ret;

	mutex_lock(&kprobe_sysctl_mutex);
	sysctl_kprobes_optimization = kprobes_allow_optimization ? 1 : 0;
	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);

	अगर (sysctl_kprobes_optimization)
		optimize_all_kprobes();
	अन्यथा
		unoptimize_all_kprobes();
	mutex_unlock(&kprobe_sysctl_mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

/* Put a अवरोधpoपूर्णांक क्रम a probe. Must be called with text_mutex locked */
अटल व्योम __arm_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *_p;

	/* Check collision with other optimized kprobes */
	_p = get_optimized_kprobe((अचिन्हित दीर्घ)p->addr);
	अगर (unlikely(_p))
		/* Fallback to unoptimized kprobe */
		unoptimize_kprobe(_p, true);

	arch_arm_kprobe(p);
	optimize_kprobe(p);	/* Try to optimize (add kprobe to a list) */
पूर्ण

/* Remove the अवरोधpoपूर्णांक of a probe. Must be called with text_mutex locked */
अटल व्योम __disarm_kprobe(काष्ठा kprobe *p, bool reopt)
अणु
	काष्ठा kprobe *_p;

	/* Try to unoptimize */
	unoptimize_kprobe(p, kprobes_all_disarmed);

	अगर (!kprobe_queued(p)) अणु
		arch_disarm_kprobe(p);
		/* If another kprobe was blocked, optimize it. */
		_p = get_optimized_kprobe((अचिन्हित दीर्घ)p->addr);
		अगर (unlikely(_p) && reopt)
			optimize_kprobe(_p);
	पूर्ण
	/* TODO: reoptimize others after unoptimized this probe */
पूर्ण

#अन्यथा /* !CONFIG_OPTPROBES */

#घोषणा optimize_kprobe(p)			करो अणुपूर्ण जबतक (0)
#घोषणा unoptimize_kprobe(p, f)			करो अणुपूर्ण जबतक (0)
#घोषणा समाप्त_optimized_kprobe(p)		करो अणुपूर्ण जबतक (0)
#घोषणा prepare_optimized_kprobe(p)		करो अणुपूर्ण जबतक (0)
#घोषणा try_to_optimize_kprobe(p)		करो अणुपूर्ण जबतक (0)
#घोषणा __arm_kprobe(p)				arch_arm_kprobe(p)
#घोषणा __disarm_kprobe(p, o)			arch_disarm_kprobe(p)
#घोषणा kprobe_disarmed(p)			kprobe_disabled(p)
#घोषणा रुको_क्रम_kprobe_optimizer()		करो अणुपूर्ण जबतक (0)

अटल पूर्णांक reuse_unused_kprobe(काष्ठा kprobe *ap)
अणु
	/*
	 * If the optimized kprobe is NOT supported, the aggr kprobe is
	 * released at the same समय that the last aggregated kprobe is
	 * unरेजिस्टरed.
	 * Thus there should be no chance to reuse unused kprobe.
	 */
	prपूर्णांकk(KERN_ERR "Error: There should be no unused kprobe here.\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम मुक्त_aggr_kprobe(काष्ठा kprobe *p)
अणु
	arch_हटाओ_kprobe(p);
	kमुक्त(p);
पूर्ण

अटल काष्ठा kprobe *alloc_aggr_kprobe(काष्ठा kprobe *p)
अणु
	वापस kzalloc(माप(काष्ठा kprobe), GFP_KERNEL);
पूर्ण
#पूर्ण_अगर /* CONFIG_OPTPROBES */

#अगर_घोषित CONFIG_KPROBES_ON_FTRACE
अटल काष्ठा ftrace_ops kprobe_ftrace_ops __पढ़ो_mostly = अणु
	.func = kprobe_ftrace_handler,
	.flags = FTRACE_OPS_FL_SAVE_REGS,
पूर्ण;

अटल काष्ठा ftrace_ops kprobe_ipmodअगरy_ops __पढ़ो_mostly = अणु
	.func = kprobe_ftrace_handler,
	.flags = FTRACE_OPS_FL_SAVE_REGS | FTRACE_OPS_FL_IPMODIFY,
पूर्ण;

अटल पूर्णांक kprobe_ipmodअगरy_enabled;
अटल पूर्णांक kprobe_ftrace_enabled;

/* Must ensure p->addr is really on ftrace */
अटल पूर्णांक prepare_kprobe(काष्ठा kprobe *p)
अणु
	अगर (!kprobe_ftrace(p))
		वापस arch_prepare_kprobe(p);

	वापस arch_prepare_kprobe_ftrace(p);
पूर्ण

/* Caller must lock kprobe_mutex */
अटल पूर्णांक __arm_kprobe_ftrace(काष्ठा kprobe *p, काष्ठा ftrace_ops *ops,
			       पूर्णांक *cnt)
अणु
	पूर्णांक ret = 0;

	ret = ftrace_set_filter_ip(ops, (अचिन्हित दीर्घ)p->addr, 0, 0);
	अगर (ret) अणु
		pr_debug("Failed to arm kprobe-ftrace at %pS (%d)\n",
			 p->addr, ret);
		वापस ret;
	पूर्ण

	अगर (*cnt == 0) अणु
		ret = रेजिस्टर_ftrace_function(ops);
		अगर (ret) अणु
			pr_debug("Failed to init kprobe-ftrace (%d)\n", ret);
			जाओ err_ftrace;
		पूर्ण
	पूर्ण

	(*cnt)++;
	वापस ret;

err_ftrace:
	/*
	 * At this poपूर्णांक, sinec ops is not रेजिस्टरed, we should be sefe from
	 * रेजिस्टरing empty filter.
	 */
	ftrace_set_filter_ip(ops, (अचिन्हित दीर्घ)p->addr, 1, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक arm_kprobe_ftrace(काष्ठा kprobe *p)
अणु
	bool ipmodअगरy = (p->post_handler != शून्य);

	वापस __arm_kprobe_ftrace(p,
		ipmodअगरy ? &kprobe_ipmodअगरy_ops : &kprobe_ftrace_ops,
		ipmodअगरy ? &kprobe_ipmodअगरy_enabled : &kprobe_ftrace_enabled);
पूर्ण

/* Caller must lock kprobe_mutex */
अटल पूर्णांक __disarm_kprobe_ftrace(काष्ठा kprobe *p, काष्ठा ftrace_ops *ops,
				  पूर्णांक *cnt)
अणु
	पूर्णांक ret = 0;

	अगर (*cnt == 1) अणु
		ret = unरेजिस्टर_ftrace_function(ops);
		अगर (WARN(ret < 0, "Failed to unregister kprobe-ftrace (%d)\n", ret))
			वापस ret;
	पूर्ण

	(*cnt)--;

	ret = ftrace_set_filter_ip(ops, (अचिन्हित दीर्घ)p->addr, 1, 0);
	WARN_ONCE(ret < 0, "Failed to disarm kprobe-ftrace at %pS (%d)\n",
		  p->addr, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक disarm_kprobe_ftrace(काष्ठा kprobe *p)
अणु
	bool ipmodअगरy = (p->post_handler != शून्य);

	वापस __disarm_kprobe_ftrace(p,
		ipmodअगरy ? &kprobe_ipmodअगरy_ops : &kprobe_ftrace_ops,
		ipmodअगरy ? &kprobe_ipmodअगरy_enabled : &kprobe_ftrace_enabled);
पूर्ण
#अन्यथा	/* !CONFIG_KPROBES_ON_FTRACE */
अटल अंतरभूत पूर्णांक prepare_kprobe(काष्ठा kprobe *p)
अणु
	वापस arch_prepare_kprobe(p);
पूर्ण

अटल अंतरभूत पूर्णांक arm_kprobe_ftrace(काष्ठा kprobe *p)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक disarm_kprobe_ftrace(काष्ठा kprobe *p)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

/* Arm a kprobe with text_mutex */
अटल पूर्णांक arm_kprobe(काष्ठा kprobe *kp)
अणु
	अगर (unlikely(kprobe_ftrace(kp)))
		वापस arm_kprobe_ftrace(kp);

	cpus_पढ़ो_lock();
	mutex_lock(&text_mutex);
	__arm_kprobe(kp);
	mutex_unlock(&text_mutex);
	cpus_पढ़ो_unlock();

	वापस 0;
पूर्ण

/* Disarm a kprobe with text_mutex */
अटल पूर्णांक disarm_kprobe(काष्ठा kprobe *kp, bool reopt)
अणु
	अगर (unlikely(kprobe_ftrace(kp)))
		वापस disarm_kprobe_ftrace(kp);

	cpus_पढ़ो_lock();
	mutex_lock(&text_mutex);
	__disarm_kprobe(kp, reopt);
	mutex_unlock(&text_mutex);
	cpus_पढ़ो_unlock();

	वापस 0;
पूर्ण

/*
 * Aggregate handlers क्रम multiple kprobes support - these handlers
 * take care of invoking the inभागidual kprobe handlers on p->list
 */
अटल पूर्णांक aggr_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	काष्ठा kprobe *kp;

	list_क्रम_each_entry_rcu(kp, &p->list, list) अणु
		अगर (kp->pre_handler && likely(!kprobe_disabled(kp))) अणु
			set_kprobe_instance(kp);
			अगर (kp->pre_handler(kp, regs))
				वापस 1;
		पूर्ण
		reset_kprobe_instance();
	पूर्ण
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(aggr_pre_handler);

अटल व्योम aggr_post_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
			      अचिन्हित दीर्घ flags)
अणु
	काष्ठा kprobe *kp;

	list_क्रम_each_entry_rcu(kp, &p->list, list) अणु
		अगर (kp->post_handler && likely(!kprobe_disabled(kp))) अणु
			set_kprobe_instance(kp);
			kp->post_handler(kp, regs, flags);
			reset_kprobe_instance();
		पूर्ण
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(aggr_post_handler);

अटल पूर्णांक aggr_fault_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
			      पूर्णांक trapnr)
अणु
	काष्ठा kprobe *cur = __this_cpu_पढ़ो(kprobe_instance);

	/*
	 * अगर we faulted "during" the execution of a user specअगरied
	 * probe handler, invoke just that probe's fault handler
	 */
	अगर (cur && cur->fault_handler) अणु
		अगर (cur->fault_handler(cur, regs, trapnr))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(aggr_fault_handler);

/* Walks the list and increments nmissed count क्रम multiprobe हाल */
व्योम kprobes_inc_nmissed_count(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *kp;
	अगर (!kprobe_aggrprobe(p)) अणु
		p->nmissed++;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(kp, &p->list, list)
			kp->nmissed++;
	पूर्ण
	वापस;
पूर्ण
NOKPROBE_SYMBOL(kprobes_inc_nmissed_count);

अटल व्योम मुक्त_rp_inst_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा kretprobe_instance *ri = container_of(head, काष्ठा kretprobe_instance, rcu);

	अगर (refcount_dec_and_test(&ri->rph->ref))
		kमुक्त(ri->rph);
	kमुक्त(ri);
पूर्ण
NOKPROBE_SYMBOL(मुक्त_rp_inst_rcu);

अटल व्योम recycle_rp_inst(काष्ठा kretprobe_instance *ri)
अणु
	काष्ठा kretprobe *rp = get_kretprobe(ri);

	अगर (likely(rp)) अणु
		मुक्तlist_add(&ri->मुक्तlist, &rp->मुक्तlist);
	पूर्ण अन्यथा
		call_rcu(&ri->rcu, मुक्त_rp_inst_rcu);
पूर्ण
NOKPROBE_SYMBOL(recycle_rp_inst);

अटल काष्ठा kprobe kprobe_busy = अणु
	.addr = (व्योम *) get_kprobe,
पूर्ण;

व्योम kprobe_busy_begin(व्योम)
अणु
	काष्ठा kprobe_ctlblk *kcb;

	preempt_disable();
	__this_cpu_ग_लिखो(current_kprobe, &kprobe_busy);
	kcb = get_kprobe_ctlblk();
	kcb->kprobe_status = KPROBE_HIT_ACTIVE;
पूर्ण

व्योम kprobe_busy_end(व्योम)
अणु
	__this_cpu_ग_लिखो(current_kprobe, शून्य);
	preempt_enable();
पूर्ण

/*
 * This function is called from finish_task_चयन when task tk becomes dead,
 * so that we can recycle any function-वापस probe instances associated
 * with this task. These left over instances represent probed functions
 * that have been called but will never वापस.
 */
व्योम kprobe_flush_task(काष्ठा task_काष्ठा *tk)
अणु
	काष्ठा kretprobe_instance *ri;
	काष्ठा llist_node *node;

	/* Early boot, not yet initialized. */
	अगर (unlikely(!kprobes_initialized))
		वापस;

	kprobe_busy_begin();

	node = __llist_del_all(&tk->kretprobe_instances);
	जबतक (node) अणु
		ri = container_of(node, काष्ठा kretprobe_instance, llist);
		node = node->next;

		recycle_rp_inst(ri);
	पूर्ण

	kprobe_busy_end();
पूर्ण
NOKPROBE_SYMBOL(kprobe_flush_task);

अटल अंतरभूत व्योम मुक्त_rp_inst(काष्ठा kretprobe *rp)
अणु
	काष्ठा kretprobe_instance *ri;
	काष्ठा मुक्तlist_node *node;
	पूर्णांक count = 0;

	node = rp->मुक्तlist.head;
	जबतक (node) अणु
		ri = container_of(node, काष्ठा kretprobe_instance, मुक्तlist);
		node = node->next;

		kमुक्त(ri);
		count++;
	पूर्ण

	अगर (refcount_sub_and_test(count, &rp->rph->ref)) अणु
		kमुक्त(rp->rph);
		rp->rph = शून्य;
	पूर्ण
पूर्ण

/* Add the new probe to ap->list */
अटल पूर्णांक add_new_kprobe(काष्ठा kprobe *ap, काष्ठा kprobe *p)
अणु
	अगर (p->post_handler)
		unoptimize_kprobe(ap, true);	/* Fall back to normal kprobe */

	list_add_rcu(&p->list, &ap->list);
	अगर (p->post_handler && !ap->post_handler)
		ap->post_handler = aggr_post_handler;

	वापस 0;
पूर्ण

/*
 * Fill in the required fields of the "manager kprobe". Replace the
 * earlier kprobe in the hlist with the manager kprobe
 */
अटल व्योम init_aggr_kprobe(काष्ठा kprobe *ap, काष्ठा kprobe *p)
अणु
	/* Copy p's insn slot to ap */
	copy_kprobe(p, ap);
	flush_insn_slot(ap);
	ap->addr = p->addr;
	ap->flags = p->flags & ~KPROBE_FLAG_OPTIMIZED;
	ap->pre_handler = aggr_pre_handler;
	ap->fault_handler = aggr_fault_handler;
	/* We करोn't care the kprobe which has gone. */
	अगर (p->post_handler && !kprobe_gone(p))
		ap->post_handler = aggr_post_handler;

	INIT_LIST_HEAD(&ap->list);
	INIT_HLIST_NODE(&ap->hlist);

	list_add_rcu(&p->list, &ap->list);
	hlist_replace_rcu(&p->hlist, &ap->hlist);
पूर्ण

/*
 * This is the second or subsequent kprobe at the address - handle
 * the पूर्णांकricacies
 */
अटल पूर्णांक रेजिस्टर_aggr_kprobe(काष्ठा kprobe *orig_p, काष्ठा kprobe *p)
अणु
	पूर्णांक ret = 0;
	काष्ठा kprobe *ap = orig_p;

	cpus_पढ़ो_lock();

	/* For preparing optimization, jump_label_text_reserved() is called */
	jump_label_lock();
	mutex_lock(&text_mutex);

	अगर (!kprobe_aggrprobe(orig_p)) अणु
		/* If orig_p is not an aggr_kprobe, create new aggr_kprobe. */
		ap = alloc_aggr_kprobe(orig_p);
		अगर (!ap) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		init_aggr_kprobe(ap, orig_p);
	पूर्ण अन्यथा अगर (kprobe_unused(ap)) अणु
		/* This probe is going to die. Rescue it */
		ret = reuse_unused_kprobe(ap);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (kprobe_gone(ap)) अणु
		/*
		 * Attempting to insert new probe at the same location that
		 * had a probe in the module vaddr area which alपढ़ोy
		 * मुक्तd. So, the inकाष्ठाion slot has alपढ़ोy been
		 * released. We need a new slot क्रम the new probe.
		 */
		ret = arch_prepare_kprobe(ap);
		अगर (ret)
			/*
			 * Even अगर fail to allocate new slot, करोn't need to
			 * मुक्त aggr_probe. It will be used next समय, or
			 * मुक्तd by unरेजिस्टर_kprobe.
			 */
			जाओ out;

		/* Prepare optimized inकाष्ठाions अगर possible. */
		prepare_optimized_kprobe(ap);

		/*
		 * Clear gone flag to prevent allocating new slot again, and
		 * set disabled flag because it is not armed yet.
		 */
		ap->flags = (ap->flags & ~KPROBE_FLAG_GONE)
			    | KPROBE_FLAG_DISABLED;
	पूर्ण

	/* Copy ap's insn slot to p */
	copy_kprobe(ap, p);
	ret = add_new_kprobe(ap, p);

out:
	mutex_unlock(&text_mutex);
	jump_label_unlock();
	cpus_पढ़ो_unlock();

	अगर (ret == 0 && kprobe_disabled(ap) && !kprobe_disabled(p)) अणु
		ap->flags &= ~KPROBE_FLAG_DISABLED;
		अगर (!kprobes_all_disarmed) अणु
			/* Arm the अवरोधpoपूर्णांक again. */
			ret = arm_kprobe(ap);
			अगर (ret) अणु
				ap->flags |= KPROBE_FLAG_DISABLED;
				list_del_rcu(&p->list);
				synchronize_rcu();
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool __weak arch_within_kprobe_blacklist(अचिन्हित दीर्घ addr)
अणु
	/* The __kprobes marked functions and entry code must not be probed */
	वापस addr >= (अचिन्हित दीर्घ)__kprobes_text_start &&
	       addr < (अचिन्हित दीर्घ)__kprobes_text_end;
पूर्ण

अटल bool __within_kprobe_blacklist(अचिन्हित दीर्घ addr)
अणु
	काष्ठा kprobe_blacklist_entry *ent;

	अगर (arch_within_kprobe_blacklist(addr))
		वापस true;
	/*
	 * If there exists a kprobe_blacklist, verअगरy and
	 * fail any probe registration in the prohibited area
	 */
	list_क्रम_each_entry(ent, &kprobe_blacklist, list) अणु
		अगर (addr >= ent->start_addr && addr < ent->end_addr)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool within_kprobe_blacklist(अचिन्हित दीर्घ addr)
अणु
	अक्षर symname[KSYM_NAME_LEN], *p;

	अगर (__within_kprobe_blacklist(addr))
		वापस true;

	/* Check अगर the address is on a suffixed-symbol */
	अगर (!lookup_symbol_name(addr, symname)) अणु
		p = म_अक्षर(symname, '.');
		अगर (!p)
			वापस false;
		*p = '\0';
		addr = (अचिन्हित दीर्घ)kprobe_lookup_name(symname, 0);
		अगर (addr)
			वापस __within_kprobe_blacklist(addr);
	पूर्ण
	वापस false;
पूर्ण

/*
 * If we have a symbol_name argument, look it up and add the offset field
 * to it. This way, we can specअगरy a relative address to a symbol.
 * This वापसs encoded errors अगर it fails to look up symbol or invalid
 * combination of parameters.
 */
अटल kprobe_opcode_t *_kprobe_addr(kprobe_opcode_t *addr,
			स्थिर अक्षर *symbol_name, अचिन्हित पूर्णांक offset)
अणु
	अगर ((symbol_name && addr) || (!symbol_name && !addr))
		जाओ invalid;

	अगर (symbol_name) अणु
		addr = kprobe_lookup_name(symbol_name, offset);
		अगर (!addr)
			वापस ERR_PTR(-ENOENT);
	पूर्ण

	addr = (kprobe_opcode_t *)(((अक्षर *)addr) + offset);
	अगर (addr)
		वापस addr;

invalid:
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल kprobe_opcode_t *kprobe_addr(काष्ठा kprobe *p)
अणु
	वापस _kprobe_addr(p->addr, p->symbol_name, p->offset);
पूर्ण

/* Check passed kprobe is valid and वापस kprobe in kprobe_table. */
अटल काष्ठा kprobe *__get_valid_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *ap, *list_p;

	lockdep_निश्चित_held(&kprobe_mutex);

	ap = get_kprobe(p->addr);
	अगर (unlikely(!ap))
		वापस शून्य;

	अगर (p != ap) अणु
		list_क्रम_each_entry(list_p, &ap->list, list)
			अगर (list_p == p)
			/* kprobe p is a valid probe */
				जाओ valid;
		वापस शून्य;
	पूर्ण
valid:
	वापस ap;
पूर्ण

/*
 * Warn and वापस error अगर the kprobe is being re-रेजिस्टरed since
 * there must be a software bug.
 */
अटल अंतरभूत पूर्णांक warn_kprobe_rereg(काष्ठा kprobe *p)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&kprobe_mutex);
	अगर (WARN_ON_ONCE(__get_valid_kprobe(p)))
		ret = -EINVAL;
	mutex_unlock(&kprobe_mutex);

	वापस ret;
पूर्ण

पूर्णांक __weak arch_check_ftrace_location(काष्ठा kprobe *p)
अणु
	अचिन्हित दीर्घ ftrace_addr;

	ftrace_addr = ftrace_location((अचिन्हित दीर्घ)p->addr);
	अगर (ftrace_addr) अणु
#अगर_घोषित CONFIG_KPROBES_ON_FTRACE
		/* Given address is not on the inकाष्ठाion boundary */
		अगर ((अचिन्हित दीर्घ)p->addr != ftrace_addr)
			वापस -EILSEQ;
		p->flags |= KPROBE_FLAG_FTRACE;
#अन्यथा	/* !CONFIG_KPROBES_ON_FTRACE */
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_kprobe_address_safe(काष्ठा kprobe *p,
				     काष्ठा module **probed_mod)
अणु
	पूर्णांक ret;

	ret = arch_check_ftrace_location(p);
	अगर (ret)
		वापस ret;
	jump_label_lock();
	preempt_disable();

	/* Ensure it is not in reserved area nor out of text */
	अगर (!kernel_text_address((अचिन्हित दीर्घ) p->addr) ||
	    within_kprobe_blacklist((अचिन्हित दीर्घ) p->addr) ||
	    jump_label_text_reserved(p->addr, p->addr) ||
	    find_bug((अचिन्हित दीर्घ)p->addr)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Check अगर are we probing a module */
	*probed_mod = __module_text_address((अचिन्हित दीर्घ) p->addr);
	अगर (*probed_mod) अणु
		/*
		 * We must hold a refcount of the probed module जबतक updating
		 * its code to prohibit unexpected unloading.
		 */
		अगर (unlikely(!try_module_get(*probed_mod))) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण

		/*
		 * If the module मुक्तd .init.text, we couldn't insert
		 * kprobes in there.
		 */
		अगर (within_module_init((अचिन्हित दीर्घ)p->addr, *probed_mod) &&
		    (*probed_mod)->state != MODULE_STATE_COMING) अणु
			module_put(*probed_mod);
			*probed_mod = शून्य;
			ret = -ENOENT;
		पूर्ण
	पूर्ण
out:
	preempt_enable();
	jump_label_unlock();

	वापस ret;
पूर्ण

पूर्णांक रेजिस्टर_kprobe(काष्ठा kprobe *p)
अणु
	पूर्णांक ret;
	काष्ठा kprobe *old_p;
	काष्ठा module *probed_mod;
	kprobe_opcode_t *addr;

	/* Adjust probe address from symbol */
	addr = kprobe_addr(p);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);
	p->addr = addr;

	ret = warn_kprobe_rereg(p);
	अगर (ret)
		वापस ret;

	/* User can pass only KPROBE_FLAG_DISABLED to रेजिस्टर_kprobe */
	p->flags &= KPROBE_FLAG_DISABLED;
	p->nmissed = 0;
	INIT_LIST_HEAD(&p->list);

	ret = check_kprobe_address_safe(p, &probed_mod);
	अगर (ret)
		वापस ret;

	mutex_lock(&kprobe_mutex);

	old_p = get_kprobe(p->addr);
	अगर (old_p) अणु
		/* Since this may unoptimize old_p, locking text_mutex. */
		ret = रेजिस्टर_aggr_kprobe(old_p, p);
		जाओ out;
	पूर्ण

	cpus_पढ़ो_lock();
	/* Prevent text modअगरication */
	mutex_lock(&text_mutex);
	ret = prepare_kprobe(p);
	mutex_unlock(&text_mutex);
	cpus_पढ़ो_unlock();
	अगर (ret)
		जाओ out;

	INIT_HLIST_NODE(&p->hlist);
	hlist_add_head_rcu(&p->hlist,
		       &kprobe_table[hash_ptr(p->addr, KPROBE_HASH_BITS)]);

	अगर (!kprobes_all_disarmed && !kprobe_disabled(p)) अणु
		ret = arm_kprobe(p);
		अगर (ret) अणु
			hlist_del_rcu(&p->hlist);
			synchronize_rcu();
			जाओ out;
		पूर्ण
	पूर्ण

	/* Try to optimize kprobe */
	try_to_optimize_kprobe(p);
out:
	mutex_unlock(&kprobe_mutex);

	अगर (probed_mod)
		module_put(probed_mod);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_kprobe);

/* Check अगर all probes on the aggrprobe are disabled */
अटल पूर्णांक aggr_kprobe_disabled(काष्ठा kprobe *ap)
अणु
	काष्ठा kprobe *kp;

	lockdep_निश्चित_held(&kprobe_mutex);

	list_क्रम_each_entry(kp, &ap->list, list)
		अगर (!kprobe_disabled(kp))
			/*
			 * There is an active probe on the list.
			 * We can't disable this ap.
			 */
			वापस 0;

	वापस 1;
पूर्ण

/* Disable one kprobe: Make sure called under kprobe_mutex is locked */
अटल काष्ठा kprobe *__disable_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *orig_p;
	पूर्णांक ret;

	/* Get an original kprobe क्रम वापस */
	orig_p = __get_valid_kprobe(p);
	अगर (unlikely(orig_p == शून्य))
		वापस ERR_PTR(-EINVAL);

	अगर (!kprobe_disabled(p)) अणु
		/* Disable probe अगर it is a child probe */
		अगर (p != orig_p)
			p->flags |= KPROBE_FLAG_DISABLED;

		/* Try to disarm and disable this/parent probe */
		अगर (p == orig_p || aggr_kprobe_disabled(orig_p)) अणु
			/*
			 * If kprobes_all_disarmed is set, orig_p
			 * should have alपढ़ोy been disarmed, so
			 * skip unneed disarming process.
			 */
			अगर (!kprobes_all_disarmed) अणु
				ret = disarm_kprobe(orig_p, true);
				अगर (ret) अणु
					p->flags &= ~KPROBE_FLAG_DISABLED;
					वापस ERR_PTR(ret);
				पूर्ण
			पूर्ण
			orig_p->flags |= KPROBE_FLAG_DISABLED;
		पूर्ण
	पूर्ण

	वापस orig_p;
पूर्ण

/*
 * Unरेजिस्टर a kprobe without a scheduler synchronization.
 */
अटल पूर्णांक __unरेजिस्टर_kprobe_top(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *ap, *list_p;

	/* Disable kprobe. This will disarm it अगर needed. */
	ap = __disable_kprobe(p);
	अगर (IS_ERR(ap))
		वापस PTR_ERR(ap);

	अगर (ap == p)
		/*
		 * This probe is an independent(and non-optimized) kprobe
		 * (not an aggrprobe). Remove from the hash list.
		 */
		जाओ disarmed;

	/* Following process expects this probe is an aggrprobe */
	WARN_ON(!kprobe_aggrprobe(ap));

	अगर (list_is_singular(&ap->list) && kprobe_disarmed(ap))
		/*
		 * !disarmed could be happen अगर the probe is under delayed
		 * unoptimizing.
		 */
		जाओ disarmed;
	अन्यथा अणु
		/* If disabling probe has special handlers, update aggrprobe */
		अगर (p->post_handler && !kprobe_gone(p)) अणु
			list_क्रम_each_entry(list_p, &ap->list, list) अणु
				अगर ((list_p != p) && (list_p->post_handler))
					जाओ noclean;
			पूर्ण
			ap->post_handler = शून्य;
		पूर्ण
noclean:
		/*
		 * Remove from the aggrprobe: this path will करो nothing in
		 * __unरेजिस्टर_kprobe_bottom().
		 */
		list_del_rcu(&p->list);
		अगर (!kprobe_disabled(ap) && !kprobes_all_disarmed)
			/*
			 * Try to optimize this probe again, because post
			 * handler may have been changed.
			 */
			optimize_kprobe(ap);
	पूर्ण
	वापस 0;

disarmed:
	hlist_del_rcu(&ap->hlist);
	वापस 0;
पूर्ण

अटल व्योम __unरेजिस्टर_kprobe_bottom(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *ap;

	अगर (list_empty(&p->list))
		/* This is an independent kprobe */
		arch_हटाओ_kprobe(p);
	अन्यथा अगर (list_is_singular(&p->list)) अणु
		/* This is the last child of an aggrprobe */
		ap = list_entry(p->list.next, काष्ठा kprobe, list);
		list_del(&p->list);
		मुक्त_aggr_kprobe(ap);
	पूर्ण
	/* Otherwise, करो nothing. */
पूर्ण

पूर्णांक रेजिस्टर_kprobes(काष्ठा kprobe **kps, पूर्णांक num)
अणु
	पूर्णांक i, ret = 0;

	अगर (num <= 0)
		वापस -EINVAL;
	क्रम (i = 0; i < num; i++) अणु
		ret = रेजिस्टर_kprobe(kps[i]);
		अगर (ret < 0) अणु
			अगर (i > 0)
				unरेजिस्टर_kprobes(kps, i);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_kprobes);

व्योम unरेजिस्टर_kprobe(काष्ठा kprobe *p)
अणु
	unरेजिस्टर_kprobes(&p, 1);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_kprobe);

व्योम unरेजिस्टर_kprobes(काष्ठा kprobe **kps, पूर्णांक num)
अणु
	पूर्णांक i;

	अगर (num <= 0)
		वापस;
	mutex_lock(&kprobe_mutex);
	क्रम (i = 0; i < num; i++)
		अगर (__unरेजिस्टर_kprobe_top(kps[i]) < 0)
			kps[i]->addr = शून्य;
	mutex_unlock(&kprobe_mutex);

	synchronize_rcu();
	क्रम (i = 0; i < num; i++)
		अगर (kps[i]->addr)
			__unरेजिस्टर_kprobe_bottom(kps[i]);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_kprobes);

पूर्णांक __weak kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
					अचिन्हित दीर्घ val, व्योम *data)
अणु
	वापस NOTIFY_DONE;
पूर्ण
NOKPROBE_SYMBOL(kprobe_exceptions_notअगरy);

अटल काष्ठा notअगरier_block kprobe_exceptions_nb = अणु
	.notअगरier_call = kprobe_exceptions_notअगरy,
	.priority = 0x7fffffff /* we need to be notअगरied first */
पूर्ण;

अचिन्हित दीर्घ __weak arch_deref_entry_poपूर्णांक(व्योम *entry)
अणु
	वापस (अचिन्हित दीर्घ)entry;
पूर्ण

#अगर_घोषित CONFIG_KRETPROBES

अचिन्हित दीर्घ __kretprobe_trampoline_handler(काष्ठा pt_regs *regs,
					     व्योम *trampoline_address,
					     व्योम *frame_poपूर्णांकer)
अणु
	kprobe_opcode_t *correct_ret_addr = शून्य;
	काष्ठा kretprobe_instance *ri = शून्य;
	काष्ठा llist_node *first, *node;
	काष्ठा kretprobe *rp;

	/* Find all nodes क्रम this frame. */
	first = node = current->kretprobe_instances.first;
	जबतक (node) अणु
		ri = container_of(node, काष्ठा kretprobe_instance, llist);

		BUG_ON(ri->fp != frame_poपूर्णांकer);

		अगर (ri->ret_addr != trampoline_address) अणु
			correct_ret_addr = ri->ret_addr;
			/*
			 * This is the real वापस address. Any other
			 * instances associated with this task are क्रम
			 * other calls deeper on the call stack
			 */
			जाओ found;
		पूर्ण

		node = node->next;
	पूर्ण
	pr_err("Oops! Kretprobe fails to find correct return address.\n");
	BUG_ON(1);

found:
	/* Unlink all nodes क्रम this frame. */
	current->kretprobe_instances.first = node->next;
	node->next = शून्य;

	/* Run them..  */
	जबतक (first) अणु
		ri = container_of(first, काष्ठा kretprobe_instance, llist);
		first = first->next;

		rp = get_kretprobe(ri);
		अगर (rp && rp->handler) अणु
			काष्ठा kprobe *prev = kprobe_running();

			__this_cpu_ग_लिखो(current_kprobe, &rp->kp);
			ri->ret_addr = correct_ret_addr;
			rp->handler(ri, regs);
			__this_cpu_ग_लिखो(current_kprobe, prev);
		पूर्ण

		recycle_rp_inst(ri);
	पूर्ण

	वापस (अचिन्हित दीर्घ)correct_ret_addr;
पूर्ण
NOKPROBE_SYMBOL(__kretprobe_trampoline_handler)

/*
 * This kprobe pre_handler is रेजिस्टरed with every kretprobe. When probe
 * hits it will set up the वापस probe.
 */
अटल पूर्णांक pre_handler_kretprobe(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	काष्ठा kretprobe *rp = container_of(p, काष्ठा kretprobe, kp);
	काष्ठा kretprobe_instance *ri;
	काष्ठा मुक्तlist_node *fn;

	fn = मुक्तlist_try_get(&rp->मुक्तlist);
	अगर (!fn) अणु
		rp->nmissed++;
		वापस 0;
	पूर्ण

	ri = container_of(fn, काष्ठा kretprobe_instance, मुक्तlist);

	अगर (rp->entry_handler && rp->entry_handler(ri, regs)) अणु
		मुक्तlist_add(&ri->मुक्तlist, &rp->मुक्तlist);
		वापस 0;
	पूर्ण

	arch_prepare_kretprobe(ri, regs);

	__llist_add(&ri->llist, &current->kretprobe_instances);

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(pre_handler_kretprobe);

bool __weak arch_kprobe_on_func_entry(अचिन्हित दीर्घ offset)
अणु
	वापस !offset;
पूर्ण

/**
 * kprobe_on_func_entry() -- check whether given address is function entry
 * @addr: Target address
 * @sym:  Target symbol name
 * @offset: The offset from the symbol or the address
 *
 * This checks whether the given @addr+@offset or @sym+@offset is on the
 * function entry address or not.
 * This वापसs 0 अगर it is the function entry, or -EINVAL अगर it is not.
 * And also it वापसs -ENOENT अगर it fails the symbol or address lookup.
 * Caller must pass @addr or @sym (either one must be शून्य), or this
 * वापसs -EINVAL.
 */
पूर्णांक kprobe_on_func_entry(kprobe_opcode_t *addr, स्थिर अक्षर *sym, अचिन्हित दीर्घ offset)
अणु
	kprobe_opcode_t *kp_addr = _kprobe_addr(addr, sym, offset);

	अगर (IS_ERR(kp_addr))
		वापस PTR_ERR(kp_addr);

	अगर (!kallsyms_lookup_size_offset((अचिन्हित दीर्घ)kp_addr, शून्य, &offset))
		वापस -ENOENT;

	अगर (!arch_kprobe_on_func_entry(offset))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक रेजिस्टर_kretprobe(काष्ठा kretprobe *rp)
अणु
	पूर्णांक ret;
	काष्ठा kretprobe_instance *inst;
	पूर्णांक i;
	व्योम *addr;

	ret = kprobe_on_func_entry(rp->kp.addr, rp->kp.symbol_name, rp->kp.offset);
	अगर (ret)
		वापस ret;

	/* If only rp->kp.addr is specअगरied, check reरेजिस्टरing kprobes */
	अगर (rp->kp.addr && warn_kprobe_rereg(&rp->kp))
		वापस -EINVAL;

	अगर (kretprobe_blacklist_size) अणु
		addr = kprobe_addr(&rp->kp);
		अगर (IS_ERR(addr))
			वापस PTR_ERR(addr);

		क्रम (i = 0; kretprobe_blacklist[i].name != शून्य; i++) अणु
			अगर (kretprobe_blacklist[i].addr == addr)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	rp->kp.pre_handler = pre_handler_kretprobe;
	rp->kp.post_handler = शून्य;
	rp->kp.fault_handler = शून्य;

	/* Pre-allocate memory क्रम max kretprobe instances */
	अगर (rp->maxactive <= 0) अणु
#अगर_घोषित CONFIG_PREEMPTION
		rp->maxactive = max_t(अचिन्हित पूर्णांक, 10, 2*num_possible_cpus());
#अन्यथा
		rp->maxactive = num_possible_cpus();
#पूर्ण_अगर
	पूर्ण
	rp->मुक्तlist.head = शून्य;
	rp->rph = kzalloc(माप(काष्ठा kretprobe_holder), GFP_KERNEL);
	अगर (!rp->rph)
		वापस -ENOMEM;

	rp->rph->rp = rp;
	क्रम (i = 0; i < rp->maxactive; i++) अणु
		inst = kzalloc(माप(काष्ठा kretprobe_instance) +
			       rp->data_size, GFP_KERNEL);
		अगर (inst == शून्य) अणु
			refcount_set(&rp->rph->ref, i);
			मुक्त_rp_inst(rp);
			वापस -ENOMEM;
		पूर्ण
		inst->rph = rp->rph;
		मुक्तlist_add(&inst->मुक्तlist, &rp->मुक्तlist);
	पूर्ण
	refcount_set(&rp->rph->ref, i);

	rp->nmissed = 0;
	/* Establish function entry probe poपूर्णांक */
	ret = रेजिस्टर_kprobe(&rp->kp);
	अगर (ret != 0)
		मुक्त_rp_inst(rp);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_kretprobe);

पूर्णांक रेजिस्टर_kretprobes(काष्ठा kretprobe **rps, पूर्णांक num)
अणु
	पूर्णांक ret = 0, i;

	अगर (num <= 0)
		वापस -EINVAL;
	क्रम (i = 0; i < num; i++) अणु
		ret = रेजिस्टर_kretprobe(rps[i]);
		अगर (ret < 0) अणु
			अगर (i > 0)
				unरेजिस्टर_kretprobes(rps, i);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_kretprobes);

व्योम unरेजिस्टर_kretprobe(काष्ठा kretprobe *rp)
अणु
	unरेजिस्टर_kretprobes(&rp, 1);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_kretprobe);

व्योम unरेजिस्टर_kretprobes(काष्ठा kretprobe **rps, पूर्णांक num)
अणु
	पूर्णांक i;

	अगर (num <= 0)
		वापस;
	mutex_lock(&kprobe_mutex);
	क्रम (i = 0; i < num; i++) अणु
		अगर (__unरेजिस्टर_kprobe_top(&rps[i]->kp) < 0)
			rps[i]->kp.addr = शून्य;
		rps[i]->rph->rp = शून्य;
	पूर्ण
	mutex_unlock(&kprobe_mutex);

	synchronize_rcu();
	क्रम (i = 0; i < num; i++) अणु
		अगर (rps[i]->kp.addr) अणु
			__unरेजिस्टर_kprobe_bottom(&rps[i]->kp);
			मुक्त_rp_inst(rps[i]);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_kretprobes);

#अन्यथा /* CONFIG_KRETPROBES */
पूर्णांक रेजिस्टर_kretprobe(काष्ठा kretprobe *rp)
अणु
	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_kretprobe);

पूर्णांक रेजिस्टर_kretprobes(काष्ठा kretprobe **rps, पूर्णांक num)
अणु
	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_kretprobes);

व्योम unरेजिस्टर_kretprobe(काष्ठा kretprobe *rp)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_kretprobe);

व्योम unरेजिस्टर_kretprobes(काष्ठा kretprobe **rps, पूर्णांक num)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_kretprobes);

अटल पूर्णांक pre_handler_kretprobe(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(pre_handler_kretprobe);

#पूर्ण_अगर /* CONFIG_KRETPROBES */

/* Set the kprobe gone and हटाओ its inकाष्ठाion buffer. */
अटल व्योम समाप्त_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा kprobe *kp;

	lockdep_निश्चित_held(&kprobe_mutex);

	p->flags |= KPROBE_FLAG_GONE;
	अगर (kprobe_aggrprobe(p)) अणु
		/*
		 * If this is an aggr_kprobe, we have to list all the
		 * chained probes and mark them GONE.
		 */
		list_क्रम_each_entry(kp, &p->list, list)
			kp->flags |= KPROBE_FLAG_GONE;
		p->post_handler = शून्य;
		समाप्त_optimized_kprobe(p);
	पूर्ण
	/*
	 * Here, we can हटाओ insn_slot safely, because no thपढ़ो calls
	 * the original probed function (which will be मुक्तd soon) any more.
	 */
	arch_हटाओ_kprobe(p);

	/*
	 * The module is going away. We should disarm the kprobe which
	 * is using ftrace, because ftrace framework is still available at
	 * MODULE_STATE_GOING notअगरication.
	 */
	अगर (kprobe_ftrace(p) && !kprobe_disabled(p) && !kprobes_all_disarmed)
		disarm_kprobe_ftrace(p);
पूर्ण

/* Disable one kprobe */
पूर्णांक disable_kprobe(काष्ठा kprobe *kp)
अणु
	पूर्णांक ret = 0;
	काष्ठा kprobe *p;

	mutex_lock(&kprobe_mutex);

	/* Disable this kprobe */
	p = __disable_kprobe(kp);
	अगर (IS_ERR(p))
		ret = PTR_ERR(p);

	mutex_unlock(&kprobe_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(disable_kprobe);

/* Enable one kprobe */
पूर्णांक enable_kprobe(काष्ठा kprobe *kp)
अणु
	पूर्णांक ret = 0;
	काष्ठा kprobe *p;

	mutex_lock(&kprobe_mutex);

	/* Check whether specअगरied probe is valid. */
	p = __get_valid_kprobe(kp);
	अगर (unlikely(p == शून्य)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (kprobe_gone(kp)) अणु
		/* This kprobe has gone, we couldn't enable it. */
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (p != kp)
		kp->flags &= ~KPROBE_FLAG_DISABLED;

	अगर (!kprobes_all_disarmed && kprobe_disabled(p)) अणु
		p->flags &= ~KPROBE_FLAG_DISABLED;
		ret = arm_kprobe(p);
		अगर (ret)
			p->flags |= KPROBE_FLAG_DISABLED;
	पूर्ण
out:
	mutex_unlock(&kprobe_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(enable_kprobe);

/* Caller must NOT call this in usual path. This is only क्रम critical हाल */
व्योम dump_kprobe(काष्ठा kprobe *kp)
अणु
	pr_err("Dumping kprobe:\n");
	pr_err("Name: %s\nOffset: %x\nAddress: %pS\n",
	       kp->symbol_name, kp->offset, kp->addr);
पूर्ण
NOKPROBE_SYMBOL(dump_kprobe);

पूर्णांक kprobe_add_ksym_blacklist(अचिन्हित दीर्घ entry)
अणु
	काष्ठा kprobe_blacklist_entry *ent;
	अचिन्हित दीर्घ offset = 0, size = 0;

	अगर (!kernel_text_address(entry) ||
	    !kallsyms_lookup_size_offset(entry, &size, &offset))
		वापस -EINVAL;

	ent = kदो_स्मृति(माप(*ent), GFP_KERNEL);
	अगर (!ent)
		वापस -ENOMEM;
	ent->start_addr = entry;
	ent->end_addr = entry + size;
	INIT_LIST_HEAD(&ent->list);
	list_add_tail(&ent->list, &kprobe_blacklist);

	वापस (पूर्णांक)size;
पूर्ण

/* Add all symbols in given area पूर्णांकo kprobe blacklist */
पूर्णांक kprobe_add_area_blacklist(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ entry;
	पूर्णांक ret = 0;

	क्रम (entry = start; entry < end; entry += ret) अणु
		ret = kprobe_add_ksym_blacklist(entry);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 0)	/* In हाल of alias symbol */
			ret = 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Remove all symbols in given area from kprobe blacklist */
अटल व्योम kprobe_हटाओ_area_blacklist(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा kprobe_blacklist_entry *ent, *n;

	list_क्रम_each_entry_safe(ent, n, &kprobe_blacklist, list) अणु
		अगर (ent->start_addr < start || ent->start_addr >= end)
			जारी;
		list_del(&ent->list);
		kमुक्त(ent);
	पूर्ण
पूर्ण

अटल व्योम kprobe_हटाओ_ksym_blacklist(अचिन्हित दीर्घ entry)
अणु
	kprobe_हटाओ_area_blacklist(entry, entry + 1);
पूर्ण

पूर्णांक __weak arch_kprobe_get_kallsym(अचिन्हित पूर्णांक *symnum, अचिन्हित दीर्घ *value,
				   अक्षर *type, अक्षर *sym)
अणु
	वापस -दुस्फल;
पूर्ण

पूर्णांक kprobe_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value, अक्षर *type,
		       अक्षर *sym)
अणु
#अगर_घोषित __ARCH_WANT_KPROBES_INSN_SLOT
	अगर (!kprobe_cache_get_kallsym(&kprobe_insn_slots, &symnum, value, type, sym))
		वापस 0;
#अगर_घोषित CONFIG_OPTPROBES
	अगर (!kprobe_cache_get_kallsym(&kprobe_optinsn_slots, &symnum, value, type, sym))
		वापस 0;
#पूर्ण_अगर
#पूर्ण_अगर
	अगर (!arch_kprobe_get_kallsym(&symnum, value, type, sym))
		वापस 0;
	वापस -दुस्फल;
पूर्ण

पूर्णांक __init __weak arch_populate_kprobe_blacklist(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * Lookup and populate the kprobe_blacklist.
 *
 * Unlike the kretprobe blacklist, we'll need to determine
 * the range of addresses that beदीर्घ to the said functions,
 * since a kprobe need not necessarily be at the beginning
 * of a function.
 */
अटल पूर्णांक __init populate_kprobe_blacklist(अचिन्हित दीर्घ *start,
					     अचिन्हित दीर्घ *end)
अणु
	अचिन्हित दीर्घ entry;
	अचिन्हित दीर्घ *iter;
	पूर्णांक ret;

	क्रम (iter = start; iter < end; iter++) अणु
		entry = arch_deref_entry_poपूर्णांक((व्योम *)*iter);
		ret = kprobe_add_ksym_blacklist(entry);
		अगर (ret == -EINVAL)
			जारी;
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Symbols in __kprobes_text are blacklisted */
	ret = kprobe_add_area_blacklist((अचिन्हित दीर्घ)__kprobes_text_start,
					(अचिन्हित दीर्घ)__kprobes_text_end);
	अगर (ret)
		वापस ret;

	/* Symbols in noinstr section are blacklisted */
	ret = kprobe_add_area_blacklist((अचिन्हित दीर्घ)__noinstr_text_start,
					(अचिन्हित दीर्घ)__noinstr_text_end);

	वापस ret ? : arch_populate_kprobe_blacklist();
पूर्ण

अटल व्योम add_module_kprobe_blacklist(काष्ठा module *mod)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक i;

	अगर (mod->kprobe_blacklist) अणु
		क्रम (i = 0; i < mod->num_kprobe_blacklist; i++)
			kprobe_add_ksym_blacklist(mod->kprobe_blacklist[i]);
	पूर्ण

	start = (अचिन्हित दीर्घ)mod->kprobes_text_start;
	अगर (start) अणु
		end = start + mod->kprobes_text_size;
		kprobe_add_area_blacklist(start, end);
	पूर्ण

	start = (अचिन्हित दीर्घ)mod->noinstr_text_start;
	अगर (start) अणु
		end = start + mod->noinstr_text_size;
		kprobe_add_area_blacklist(start, end);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_module_kprobe_blacklist(काष्ठा module *mod)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक i;

	अगर (mod->kprobe_blacklist) अणु
		क्रम (i = 0; i < mod->num_kprobe_blacklist; i++)
			kprobe_हटाओ_ksym_blacklist(mod->kprobe_blacklist[i]);
	पूर्ण

	start = (अचिन्हित दीर्घ)mod->kprobes_text_start;
	अगर (start) अणु
		end = start + mod->kprobes_text_size;
		kprobe_हटाओ_area_blacklist(start, end);
	पूर्ण

	start = (अचिन्हित दीर्घ)mod->noinstr_text_start;
	अगर (start) अणु
		end = start + mod->noinstr_text_size;
		kprobe_हटाओ_area_blacklist(start, end);
	पूर्ण
पूर्ण

/* Module notअगरier call back, checking kprobes on the module */
अटल पूर्णांक kprobes_module_callback(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;
	काष्ठा hlist_head *head;
	काष्ठा kprobe *p;
	अचिन्हित पूर्णांक i;
	पूर्णांक checkcore = (val == MODULE_STATE_GOING);

	अगर (val == MODULE_STATE_COMING) अणु
		mutex_lock(&kprobe_mutex);
		add_module_kprobe_blacklist(mod);
		mutex_unlock(&kprobe_mutex);
	पूर्ण
	अगर (val != MODULE_STATE_GOING && val != MODULE_STATE_LIVE)
		वापस NOTIFY_DONE;

	/*
	 * When MODULE_STATE_GOING was notअगरied, both of module .text and
	 * .init.text sections would be मुक्तd. When MODULE_STATE_LIVE was
	 * notअगरied, only .init.text section would be मुक्तd. We need to
	 * disable kprobes which have been inserted in the sections.
	 */
	mutex_lock(&kprobe_mutex);
	क्रम (i = 0; i < KPROBE_TABLE_SIZE; i++) अणु
		head = &kprobe_table[i];
		hlist_क्रम_each_entry(p, head, hlist)
			अगर (within_module_init((अचिन्हित दीर्घ)p->addr, mod) ||
			    (checkcore &&
			     within_module_core((अचिन्हित दीर्घ)p->addr, mod))) अणु
				/*
				 * The vaddr this probe is installed will soon
				 * be vमुक्तd buy not synced to disk. Hence,
				 * disarming the अवरोधpoपूर्णांक isn't needed.
				 *
				 * Note, this will also move any optimized probes
				 * that are pending to be हटाओd from their
				 * corresponding lists to the मुक्तing_list and
				 * will not be touched by the delayed
				 * kprobe_optimizer work handler.
				 */
				समाप्त_kprobe(p);
			पूर्ण
	पूर्ण
	अगर (val == MODULE_STATE_GOING)
		हटाओ_module_kprobe_blacklist(mod);
	mutex_unlock(&kprobe_mutex);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block kprobe_module_nb = अणु
	.notअगरier_call = kprobes_module_callback,
	.priority = 0
पूर्ण;

/* Markers of _kprobe_blacklist section */
बाह्य अचिन्हित दीर्घ __start_kprobe_blacklist[];
बाह्य अचिन्हित दीर्घ __stop_kprobe_blacklist[];

व्योम kprobe_मुक्त_init_mem(व्योम)
अणु
	व्योम *start = (व्योम *)(&__init_begin);
	व्योम *end = (व्योम *)(&__init_end);
	काष्ठा hlist_head *head;
	काष्ठा kprobe *p;
	पूर्णांक i;

	mutex_lock(&kprobe_mutex);

	/* Kill all kprobes on iniपंचांगem */
	क्रम (i = 0; i < KPROBE_TABLE_SIZE; i++) अणु
		head = &kprobe_table[i];
		hlist_क्रम_each_entry(p, head, hlist) अणु
			अगर (start <= (व्योम *)p->addr && (व्योम *)p->addr < end)
				समाप्त_kprobe(p);
		पूर्ण
	पूर्ण

	mutex_unlock(&kprobe_mutex);
पूर्ण

अटल पूर्णांक __init init_kprobes(व्योम)
अणु
	पूर्णांक i, err = 0;

	/* FIXME allocate the probe table, currently defined अटलally */
	/* initialize all list heads */
	क्रम (i = 0; i < KPROBE_TABLE_SIZE; i++)
		INIT_HLIST_HEAD(&kprobe_table[i]);

	err = populate_kprobe_blacklist(__start_kprobe_blacklist,
					__stop_kprobe_blacklist);
	अगर (err) अणु
		pr_err("kprobes: failed to populate blacklist: %d\n", err);
		pr_err("Please take care of using kprobes.\n");
	पूर्ण

	अगर (kretprobe_blacklist_size) अणु
		/* lookup the function address from its name */
		क्रम (i = 0; kretprobe_blacklist[i].name != शून्य; i++) अणु
			kretprobe_blacklist[i].addr =
				kprobe_lookup_name(kretprobe_blacklist[i].name, 0);
			अगर (!kretprobe_blacklist[i].addr)
				prपूर्णांकk("kretprobe: lookup failed: %s\n",
				       kretprobe_blacklist[i].name);
		पूर्ण
	पूर्ण

	/* By शेष, kprobes are armed */
	kprobes_all_disarmed = false;

#अगर defined(CONFIG_OPTPROBES) && defined(__ARCH_WANT_KPROBES_INSN_SLOT)
	/* Init kprobe_optinsn_slots क्रम allocation */
	kprobe_optinsn_slots.insn_size = MAX_OPTINSN_SIZE;
#पूर्ण_अगर

	err = arch_init_kprobes();
	अगर (!err)
		err = रेजिस्टर_die_notअगरier(&kprobe_exceptions_nb);
	अगर (!err)
		err = रेजिस्टर_module_notअगरier(&kprobe_module_nb);

	kprobes_initialized = (err == 0);

	अगर (!err)
		init_test_probes();
	वापस err;
पूर्ण
early_initcall(init_kprobes);

#अगर defined(CONFIG_OPTPROBES)
अटल पूर्णांक __init init_optprobes(व्योम)
अणु
	/*
	 * Enable kprobe optimization - this kicks the optimizer which
	 * depends on synchronize_rcu_tasks() and ksoftirqd, that is
	 * not spawned in early initcall. So delay the optimization.
	 */
	optimize_all_kprobes();

	वापस 0;
पूर्ण
subsys_initcall(init_optprobes);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम report_probe(काष्ठा seq_file *pi, काष्ठा kprobe *p,
		स्थिर अक्षर *sym, पूर्णांक offset, अक्षर *modname, काष्ठा kprobe *pp)
अणु
	अक्षर *kprobe_type;
	व्योम *addr = p->addr;

	अगर (p->pre_handler == pre_handler_kretprobe)
		kprobe_type = "r";
	अन्यथा
		kprobe_type = "k";

	अगर (!kallsyms_show_value(pi->file->f_cred))
		addr = शून्य;

	अगर (sym)
		seq_म_लिखो(pi, "%px  %s  %s+0x%x  %s ",
			addr, kprobe_type, sym, offset,
			(modname ? modname : " "));
	अन्यथा	/* try to use %pS */
		seq_म_लिखो(pi, "%px  %s  %pS ",
			addr, kprobe_type, p->addr);

	अगर (!pp)
		pp = p;
	seq_म_लिखो(pi, "%s%s%s%s\n",
		(kprobe_gone(p) ? "[GONE]" : ""),
		((kprobe_disabled(p) && !kprobe_gone(p)) ?  "[DISABLED]" : ""),
		(kprobe_optimized(pp) ? "[OPTIMIZED]" : ""),
		(kprobe_ftrace(pp) ? "[FTRACE]" : ""));
पूर्ण

अटल व्योम *kprobe_seq_start(काष्ठा seq_file *f, loff_t *pos)
अणु
	वापस (*pos < KPROBE_TABLE_SIZE) ? pos : शून्य;
पूर्ण

अटल व्योम *kprobe_seq_next(काष्ठा seq_file *f, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	अगर (*pos >= KPROBE_TABLE_SIZE)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम kprobe_seq_stop(काष्ठा seq_file *f, व्योम *v)
अणु
	/* Nothing to करो */
पूर्ण

अटल पूर्णांक show_kprobe_addr(काष्ठा seq_file *pi, व्योम *v)
अणु
	काष्ठा hlist_head *head;
	काष्ठा kprobe *p, *kp;
	स्थिर अक्षर *sym = शून्य;
	अचिन्हित पूर्णांक i = *(loff_t *) v;
	अचिन्हित दीर्घ offset = 0;
	अक्षर *modname, namebuf[KSYM_NAME_LEN];

	head = &kprobe_table[i];
	preempt_disable();
	hlist_क्रम_each_entry_rcu(p, head, hlist) अणु
		sym = kallsyms_lookup((अचिन्हित दीर्घ)p->addr, शून्य,
					&offset, &modname, namebuf);
		अगर (kprobe_aggrprobe(p)) अणु
			list_क्रम_each_entry_rcu(kp, &p->list, list)
				report_probe(pi, kp, sym, offset, modname, p);
		पूर्ण अन्यथा
			report_probe(pi, p, sym, offset, modname, शून्य);
	पूर्ण
	preempt_enable();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations kprobes_sops = अणु
	.start = kprobe_seq_start,
	.next  = kprobe_seq_next,
	.stop  = kprobe_seq_stop,
	.show  = show_kprobe_addr
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(kprobes);

/* kprobes/blacklist -- shows which functions can not be probed */
अटल व्योम *kprobe_blacklist_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	mutex_lock(&kprobe_mutex);
	वापस seq_list_start(&kprobe_blacklist, *pos);
पूर्ण

अटल व्योम *kprobe_blacklist_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &kprobe_blacklist, pos);
पूर्ण

अटल पूर्णांक kprobe_blacklist_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा kprobe_blacklist_entry *ent =
		list_entry(v, काष्ठा kprobe_blacklist_entry, list);

	/*
	 * If /proc/kallsyms is not showing kernel address, we won't
	 * show them here either.
	 */
	अगर (!kallsyms_show_value(m->file->f_cred))
		seq_म_लिखो(m, "0x%px-0x%px\t%ps\n", शून्य, शून्य,
			   (व्योम *)ent->start_addr);
	अन्यथा
		seq_म_लिखो(m, "0x%px-0x%px\t%ps\n", (व्योम *)ent->start_addr,
			   (व्योम *)ent->end_addr, (व्योम *)ent->start_addr);
	वापस 0;
पूर्ण

अटल व्योम kprobe_blacklist_seq_stop(काष्ठा seq_file *f, व्योम *v)
अणु
	mutex_unlock(&kprobe_mutex);
पूर्ण

अटल स्थिर काष्ठा seq_operations kprobe_blacklist_sops = अणु
	.start = kprobe_blacklist_seq_start,
	.next  = kprobe_blacklist_seq_next,
	.stop  = kprobe_blacklist_seq_stop,
	.show  = kprobe_blacklist_seq_show,
पूर्ण;
DEFINE_SEQ_ATTRIBUTE(kprobe_blacklist);

अटल पूर्णांक arm_all_kprobes(व्योम)
अणु
	काष्ठा hlist_head *head;
	काष्ठा kprobe *p;
	अचिन्हित पूर्णांक i, total = 0, errors = 0;
	पूर्णांक err, ret = 0;

	mutex_lock(&kprobe_mutex);

	/* If kprobes are armed, just वापस */
	अगर (!kprobes_all_disarmed)
		जाओ alपढ़ोy_enabled;

	/*
	 * optimize_kprobe() called by arm_kprobe() checks
	 * kprobes_all_disarmed, so set kprobes_all_disarmed beक्रमe
	 * arm_kprobe.
	 */
	kprobes_all_disarmed = false;
	/* Arming kprobes करोesn't optimize kprobe itself */
	क्रम (i = 0; i < KPROBE_TABLE_SIZE; i++) अणु
		head = &kprobe_table[i];
		/* Arm all kprobes on a best-efक्रमt basis */
		hlist_क्रम_each_entry(p, head, hlist) अणु
			अगर (!kprobe_disabled(p)) अणु
				err = arm_kprobe(p);
				अगर (err)  अणु
					errors++;
					ret = err;
				पूर्ण
				total++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (errors)
		pr_warn("Kprobes globally enabled, but failed to arm %d out of %d probes\n",
			errors, total);
	अन्यथा
		pr_info("Kprobes globally enabled\n");

alपढ़ोy_enabled:
	mutex_unlock(&kprobe_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक disarm_all_kprobes(व्योम)
अणु
	काष्ठा hlist_head *head;
	काष्ठा kprobe *p;
	अचिन्हित पूर्णांक i, total = 0, errors = 0;
	पूर्णांक err, ret = 0;

	mutex_lock(&kprobe_mutex);

	/* If kprobes are alपढ़ोy disarmed, just वापस */
	अगर (kprobes_all_disarmed) अणु
		mutex_unlock(&kprobe_mutex);
		वापस 0;
	पूर्ण

	kprobes_all_disarmed = true;

	क्रम (i = 0; i < KPROBE_TABLE_SIZE; i++) अणु
		head = &kprobe_table[i];
		/* Disarm all kprobes on a best-efक्रमt basis */
		hlist_क्रम_each_entry(p, head, hlist) अणु
			अगर (!arch_trampoline_kprobe(p) && !kprobe_disabled(p)) अणु
				err = disarm_kprobe(p, false);
				अगर (err) अणु
					errors++;
					ret = err;
				पूर्ण
				total++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (errors)
		pr_warn("Kprobes globally disabled, but failed to disarm %d out of %d probes\n",
			errors, total);
	अन्यथा
		pr_info("Kprobes globally disabled\n");

	mutex_unlock(&kprobe_mutex);

	/* Wait क्रम disarming all kprobes by optimizer */
	रुको_क्रम_kprobe_optimizer();

	वापस ret;
पूर्ण

/*
 * XXX: The debugfs bool file पूर्णांकerface करोesn't allow क्रम callbacks
 * when the bool state is चयनed. We can reuse that facility when
 * available
 */
अटल sमाप_प्रकार पढ़ो_enabled_file_bool(काष्ठा file *file,
	       अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[3];

	अगर (!kprobes_all_disarmed)
		buf[0] = '1';
	अन्यथा
		buf[0] = '0';
	buf[1] = '\n';
	buf[2] = 0x00;
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_enabled_file_bool(काष्ठा file *file,
	       स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[32];
	माप_प्रकार buf_size;
	पूर्णांक ret = 0;

	buf_size = min(count, (माप(buf)-1));
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	buf[buf_size] = '\0';
	चयन (buf[0]) अणु
	हाल 'y':
	हाल 'Y':
	हाल '1':
		ret = arm_all_kprobes();
		अवरोध;
	हाल 'n':
	हाल 'N':
	हाल '0':
		ret = disarm_all_kprobes();
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_kp = अणु
	.पढ़ो =         पढ़ो_enabled_file_bool,
	.ग_लिखो =        ग_लिखो_enabled_file_bool,
	.llseek =	शेष_llseek,
पूर्ण;

अटल पूर्णांक __init debugfs_kprobe_init(व्योम)
अणु
	काष्ठा dentry *dir;
	अचिन्हित पूर्णांक value = 1;

	dir = debugfs_create_dir("kprobes", शून्य);

	debugfs_create_file("list", 0400, dir, शून्य, &kprobes_fops);

	debugfs_create_file("enabled", 0600, dir, &value, &fops_kp);

	debugfs_create_file("blacklist", 0400, dir, शून्य,
			    &kprobe_blacklist_fops);

	वापस 0;
पूर्ण

late_initcall(debugfs_kprobe_init);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
