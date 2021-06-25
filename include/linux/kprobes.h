<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _LINUX_KPROBES_H
#घोषणा _LINUX_KPROBES_H
/*
 *  Kernel Probes (KProbes)
 *  include/linux/kprobes.h
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 *
 * 2002-Oct	Created by Vamsi Krishna S <vamsi_krishna@in.ibm.com> Kernel
 *		Probes initial implementation ( includes suggestions from
 *		Rusty Russell).
 * 2004-July	Suparna Bhattaअक्षरya <suparna@in.ibm.com> added jumper probes
 *		पूर्णांकerface to access function arguments.
 * 2005-May	Hien Nguyen <hien@us.ibm.com> and Jim Keniston
 *		<jkenisto@us.ibm.com>  and Prasanna S Panchamukhi
 *		<prasanna@in.ibm.com> added function-वापस probes.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/smp.h>
#समावेश <linux/bug.h>
#समावेश <linux/percpu.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/refcount.h>
#समावेश <linux/मुक्तlist.h>
#समावेश <यंत्र/kprobes.h>

#अगर_घोषित CONFIG_KPROBES

/* kprobe_status settings */
#घोषणा KPROBE_HIT_ACTIVE	0x00000001
#घोषणा KPROBE_HIT_SS		0x00000002
#घोषणा KPROBE_REENTER		0x00000004
#घोषणा KPROBE_HIT_SSDONE	0x00000008

#अन्यथा /* CONFIG_KPROBES */
#समावेश <यंत्र-generic/kprobes.h>
प्रकार पूर्णांक kprobe_opcode_t;
काष्ठा arch_specअगरic_insn अणु
	पूर्णांक dummy;
पूर्ण;
#पूर्ण_अगर /* CONFIG_KPROBES */

काष्ठा kprobe;
काष्ठा pt_regs;
काष्ठा kretprobe;
काष्ठा kretprobe_instance;
प्रकार पूर्णांक (*kprobe_pre_handler_t) (काष्ठा kprobe *, काष्ठा pt_regs *);
प्रकार व्योम (*kprobe_post_handler_t) (काष्ठा kprobe *, काष्ठा pt_regs *,
				       अचिन्हित दीर्घ flags);
प्रकार पूर्णांक (*kprobe_fault_handler_t) (काष्ठा kprobe *, काष्ठा pt_regs *,
				       पूर्णांक trapnr);
प्रकार पूर्णांक (*kretprobe_handler_t) (काष्ठा kretprobe_instance *,
				    काष्ठा pt_regs *);

काष्ठा kprobe अणु
	काष्ठा hlist_node hlist;

	/* list of kprobes क्रम multi-handler support */
	काष्ठा list_head list;

	/*count the number of बार this probe was temporarily disarmed */
	अचिन्हित दीर्घ nmissed;

	/* location of the probe poपूर्णांक */
	kprobe_opcode_t *addr;

	/* Allow user to indicate symbol name of the probe poपूर्णांक */
	स्थिर अक्षर *symbol_name;

	/* Offset पूर्णांकo the symbol */
	अचिन्हित पूर्णांक offset;

	/* Called beक्रमe addr is executed. */
	kprobe_pre_handler_t pre_handler;

	/* Called after addr is executed, unless... */
	kprobe_post_handler_t post_handler;

	/*
	 * ... called अगर executing addr causes a fault (eg. page fault).
	 * Return 1 अगर it handled fault, otherwise kernel will see it.
	 */
	kprobe_fault_handler_t fault_handler;

	/* Saved opcode (which has been replaced with अवरोधpoपूर्णांक) */
	kprobe_opcode_t opcode;

	/* copy of the original inकाष्ठाion */
	काष्ठा arch_specअगरic_insn ainsn;

	/*
	 * Indicates various status flags.
	 * Protected by kprobe_mutex after this kprobe is रेजिस्टरed.
	 */
	u32 flags;
पूर्ण;

/* Kprobe status flags */
#घोषणा KPROBE_FLAG_GONE	1 /* अवरोधpoपूर्णांक has alपढ़ोy gone */
#घोषणा KPROBE_FLAG_DISABLED	2 /* probe is temporarily disabled */
#घोषणा KPROBE_FLAG_OPTIMIZED	4 /*
				   * probe is really optimized.
				   * NOTE:
				   * this flag is only क्रम optimized_kprobe.
				   */
#घोषणा KPROBE_FLAG_FTRACE	8 /* probe is using ftrace */

/* Has this kprobe gone ? */
अटल अंतरभूत पूर्णांक kprobe_gone(काष्ठा kprobe *p)
अणु
	वापस p->flags & KPROBE_FLAG_GONE;
पूर्ण

/* Is this kprobe disabled ? */
अटल अंतरभूत पूर्णांक kprobe_disabled(काष्ठा kprobe *p)
अणु
	वापस p->flags & (KPROBE_FLAG_DISABLED | KPROBE_FLAG_GONE);
पूर्ण

/* Is this kprobe really running optimized path ? */
अटल अंतरभूत पूर्णांक kprobe_optimized(काष्ठा kprobe *p)
अणु
	वापस p->flags & KPROBE_FLAG_OPTIMIZED;
पूर्ण

/* Is this kprobe uses ftrace ? */
अटल अंतरभूत पूर्णांक kprobe_ftrace(काष्ठा kprobe *p)
अणु
	वापस p->flags & KPROBE_FLAG_FTRACE;
पूर्ण

/*
 * Function-वापस probe -
 * Note:
 * User needs to provide a handler function, and initialize maxactive.
 * maxactive - The maximum number of instances of the probed function that
 * can be active concurrently.
 * nmissed - tracks the number of बार the probed function's वापस was
 * ignored, due to maxactive being too low.
 *
 */
काष्ठा kretprobe_holder अणु
	काष्ठा kretprobe	*rp;
	refcount_t		ref;
पूर्ण;

काष्ठा kretprobe अणु
	काष्ठा kprobe kp;
	kretprobe_handler_t handler;
	kretprobe_handler_t entry_handler;
	पूर्णांक maxactive;
	पूर्णांक nmissed;
	माप_प्रकार data_size;
	काष्ठा मुक्तlist_head मुक्तlist;
	काष्ठा kretprobe_holder *rph;
पूर्ण;

काष्ठा kretprobe_instance अणु
	जोड़ अणु
		काष्ठा मुक्तlist_node मुक्तlist;
		काष्ठा rcu_head rcu;
	पूर्ण;
	काष्ठा llist_node llist;
	काष्ठा kretprobe_holder *rph;
	kprobe_opcode_t *ret_addr;
	व्योम *fp;
	अक्षर data[];
पूर्ण;

काष्ठा kretprobe_blackpoपूर्णांक अणु
	स्थिर अक्षर *name;
	व्योम *addr;
पूर्ण;

काष्ठा kprobe_blacklist_entry अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ start_addr;
	अचिन्हित दीर्घ end_addr;
पूर्ण;

#अगर_घोषित CONFIG_KPROBES
DECLARE_PER_CPU(काष्ठा kprobe *, current_kprobe);
DECLARE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

/*
 * For #अगर_घोषित aव्योमance:
 */
अटल अंतरभूत पूर्णांक kprobes_built_in(व्योम)
अणु
	वापस 1;
पूर्ण

बाह्य व्योम kprobe_busy_begin(व्योम);
बाह्य व्योम kprobe_busy_end(व्योम);

#अगर_घोषित CONFIG_KRETPROBES
बाह्य व्योम arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri,
				   काष्ठा pt_regs *regs);
बाह्य पूर्णांक arch_trampoline_kprobe(काष्ठा kprobe *p);

/* If the trampoline handler called from a kprobe, use this version */
अचिन्हित दीर्घ __kretprobe_trampoline_handler(काष्ठा pt_regs *regs,
				व्योम *trampoline_address,
				व्योम *frame_poपूर्णांकer);

अटल nokprobe_अंतरभूत
अचिन्हित दीर्घ kretprobe_trampoline_handler(काष्ठा pt_regs *regs,
				व्योम *trampoline_address,
				व्योम *frame_poपूर्णांकer)
अणु
	अचिन्हित दीर्घ ret;
	/*
	 * Set a dummy kprobe क्रम aव्योमing kretprobe recursion.
	 * Since kretprobe never runs in kprobe handler, no kprobe must
	 * be running at this poपूर्णांक.
	 */
	kprobe_busy_begin();
	ret = __kretprobe_trampoline_handler(regs, trampoline_address, frame_poपूर्णांकer);
	kprobe_busy_end();

	वापस ret;
पूर्ण

अटल nokprobe_अंतरभूत काष्ठा kretprobe *get_kretprobe(काष्ठा kretprobe_instance *ri)
अणु
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_any_held(),
		"Kretprobe is accessed from instance under preemptive context");

	वापस READ_ONCE(ri->rph->rp);
पूर्ण

#अन्यथा /* CONFIG_KRETPROBES */
अटल अंतरभूत व्योम arch_prepare_kretprobe(काष्ठा kretprobe *rp,
					काष्ठा pt_regs *regs)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_KRETPROBES */

बाह्य काष्ठा kretprobe_blackpoपूर्णांक kretprobe_blacklist[];

#अगर_घोषित CONFIG_KPROBES_SANITY_TEST
बाह्य पूर्णांक init_test_probes(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक init_test_probes(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_KPROBES_SANITY_TEST */

बाह्य पूर्णांक arch_prepare_kprobe(काष्ठा kprobe *p);
बाह्य व्योम arch_arm_kprobe(काष्ठा kprobe *p);
बाह्य व्योम arch_disarm_kprobe(काष्ठा kprobe *p);
बाह्य पूर्णांक arch_init_kprobes(व्योम);
बाह्य व्योम kprobes_inc_nmissed_count(काष्ठा kprobe *p);
बाह्य bool arch_within_kprobe_blacklist(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक arch_populate_kprobe_blacklist(व्योम);
बाह्य bool arch_kprobe_on_func_entry(अचिन्हित दीर्घ offset);
बाह्य पूर्णांक kprobe_on_func_entry(kprobe_opcode_t *addr, स्थिर अक्षर *sym, अचिन्हित दीर्घ offset);

बाह्य bool within_kprobe_blacklist(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक kprobe_add_ksym_blacklist(अचिन्हित दीर्घ entry);
बाह्य पूर्णांक kprobe_add_area_blacklist(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

काष्ठा kprobe_insn_cache अणु
	काष्ठा mutex mutex;
	व्योम *(*alloc)(व्योम);	/* allocate insn page */
	व्योम (*मुक्त)(व्योम *);	/* मुक्त insn page */
	स्थिर अक्षर *sym;	/* symbol क्रम insn pages */
	काष्ठा list_head pages; /* list of kprobe_insn_page */
	माप_प्रकार insn_size;	/* size of inकाष्ठाion slot */
	पूर्णांक nr_garbage;
पूर्ण;

#अगर_घोषित __ARCH_WANT_KPROBES_INSN_SLOT
बाह्य kprobe_opcode_t *__get_insn_slot(काष्ठा kprobe_insn_cache *c);
बाह्य व्योम __मुक्त_insn_slot(काष्ठा kprobe_insn_cache *c,
			     kprobe_opcode_t *slot, पूर्णांक dirty);
/* sleep-less address checking routine  */
बाह्य bool __is_insn_slot_addr(काष्ठा kprobe_insn_cache *c,
				अचिन्हित दीर्घ addr);

#घोषणा DEFINE_INSN_CACHE_OPS(__name)					\
बाह्य काष्ठा kprobe_insn_cache kprobe_##__name##_slots;		\
									\
अटल अंतरभूत kprobe_opcode_t *get_##__name##_slot(व्योम)		\
अणु									\
	वापस __get_insn_slot(&kprobe_##__name##_slots);		\
पूर्ण									\
									\
अटल अंतरभूत व्योम मुक्त_##__name##_slot(kprobe_opcode_t *slot, पूर्णांक dirty)\
अणु									\
	__मुक्त_insn_slot(&kprobe_##__name##_slots, slot, dirty);	\
पूर्ण									\
									\
अटल अंतरभूत bool is_kprobe_##__name##_slot(अचिन्हित दीर्घ addr)	\
अणु									\
	वापस __is_insn_slot_addr(&kprobe_##__name##_slots, addr);	\
पूर्ण
#घोषणा KPROBE_INSN_PAGE_SYM		"kprobe_insn_page"
#घोषणा KPROBE_OPTINSN_PAGE_SYM		"kprobe_optinsn_page"
पूर्णांक kprobe_cache_get_kallsym(काष्ठा kprobe_insn_cache *c, अचिन्हित पूर्णांक *symnum,
			     अचिन्हित दीर्घ *value, अक्षर *type, अक्षर *sym);
#अन्यथा /* __ARCH_WANT_KPROBES_INSN_SLOT */
#घोषणा DEFINE_INSN_CACHE_OPS(__name)					\
अटल अंतरभूत bool is_kprobe_##__name##_slot(अचिन्हित दीर्घ addr)	\
अणु									\
	वापस 0;							\
पूर्ण
#पूर्ण_अगर

DEFINE_INSN_CACHE_OPS(insn);

#अगर_घोषित CONFIG_OPTPROBES
/*
 * Internal काष्ठाure क्रम direct jump optimized probe
 */
काष्ठा optimized_kprobe अणु
	काष्ठा kprobe kp;
	काष्ठा list_head list;	/* list क्रम optimizing queue */
	काष्ठा arch_optimized_insn optinsn;
पूर्ण;

/* Architecture dependent functions क्रम direct jump optimization */
बाह्य पूर्णांक arch_prepared_optinsn(काष्ठा arch_optimized_insn *optinsn);
बाह्य पूर्णांक arch_check_optimized_kprobe(काष्ठा optimized_kprobe *op);
बाह्य पूर्णांक arch_prepare_optimized_kprobe(काष्ठा optimized_kprobe *op,
					 काष्ठा kprobe *orig);
बाह्य व्योम arch_हटाओ_optimized_kprobe(काष्ठा optimized_kprobe *op);
बाह्य व्योम arch_optimize_kprobes(काष्ठा list_head *oplist);
बाह्य व्योम arch_unoptimize_kprobes(काष्ठा list_head *oplist,
				    काष्ठा list_head *करोne_list);
बाह्य व्योम arch_unoptimize_kprobe(काष्ठा optimized_kprobe *op);
बाह्य पूर्णांक arch_within_optimized_kprobe(काष्ठा optimized_kprobe *op,
					अचिन्हित दीर्घ addr);

बाह्य व्योम opt_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs);

DEFINE_INSN_CACHE_OPS(optinsn);

#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक sysctl_kprobes_optimization;
बाह्य पूर्णांक proc_kprobes_optimization_handler(काष्ठा ctl_table *table,
					     पूर्णांक ग_लिखो, व्योम *buffer,
					     माप_प्रकार *length, loff_t *ppos);
#पूर्ण_अगर
बाह्य व्योम रुको_क्रम_kprobe_optimizer(व्योम);
#अन्यथा
अटल अंतरभूत व्योम रुको_क्रम_kprobe_optimizer(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_OPTPROBES */
#अगर_घोषित CONFIG_KPROBES_ON_FTRACE
बाह्य व्योम kprobe_ftrace_handler(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				  काष्ठा ftrace_ops *ops, काष्ठा ftrace_regs *fregs);
बाह्य पूर्णांक arch_prepare_kprobe_ftrace(काष्ठा kprobe *p);
#पूर्ण_अगर

पूर्णांक arch_check_ftrace_location(काष्ठा kprobe *p);

/* Get the kprobe at this addr (अगर any) - called with preemption disabled */
काष्ठा kprobe *get_kprobe(व्योम *addr);

/* kprobe_running() will just वापस the current_kprobe on this CPU */
अटल अंतरभूत काष्ठा kprobe *kprobe_running(व्योम)
अणु
	वापस (__this_cpu_पढ़ो(current_kprobe));
पूर्ण

अटल अंतरभूत व्योम reset_current_kprobe(व्योम)
अणु
	__this_cpu_ग_लिखो(current_kprobe, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा kprobe_ctlblk *get_kprobe_ctlblk(व्योम)
अणु
	वापस this_cpu_ptr(&kprobe_ctlblk);
पूर्ण

kprobe_opcode_t *kprobe_lookup_name(स्थिर अक्षर *name, अचिन्हित पूर्णांक offset);
पूर्णांक रेजिस्टर_kprobe(काष्ठा kprobe *p);
व्योम unरेजिस्टर_kprobe(काष्ठा kprobe *p);
पूर्णांक रेजिस्टर_kprobes(काष्ठा kprobe **kps, पूर्णांक num);
व्योम unरेजिस्टर_kprobes(काष्ठा kprobe **kps, पूर्णांक num);
अचिन्हित दीर्घ arch_deref_entry_poपूर्णांक(व्योम *);

पूर्णांक रेजिस्टर_kretprobe(काष्ठा kretprobe *rp);
व्योम unरेजिस्टर_kretprobe(काष्ठा kretprobe *rp);
पूर्णांक रेजिस्टर_kretprobes(काष्ठा kretprobe **rps, पूर्णांक num);
व्योम unरेजिस्टर_kretprobes(काष्ठा kretprobe **rps, पूर्णांक num);

व्योम kprobe_flush_task(काष्ठा task_काष्ठा *tk);

व्योम kprobe_मुक्त_init_mem(व्योम);

पूर्णांक disable_kprobe(काष्ठा kprobe *kp);
पूर्णांक enable_kprobe(काष्ठा kprobe *kp);

व्योम dump_kprobe(काष्ठा kprobe *kp);

व्योम *alloc_insn_page(व्योम);
व्योम मुक्त_insn_page(व्योम *page);

पूर्णांक kprobe_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value, अक्षर *type,
		       अक्षर *sym);

पूर्णांक arch_kprobe_get_kallsym(अचिन्हित पूर्णांक *symnum, अचिन्हित दीर्घ *value,
			    अक्षर *type, अक्षर *sym);
#अन्यथा /* !CONFIG_KPROBES: */

अटल अंतरभूत पूर्णांक kprobes_built_in(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा kprobe *get_kprobe(व्योम *addr)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा kprobe *kprobe_running(व्योम)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_kprobe(काष्ठा kprobe *p)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_kprobes(काष्ठा kprobe **kps, पूर्णांक num)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_kprobe(काष्ठा kprobe *p)
अणु
पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_kprobes(काष्ठा kprobe **kps, पूर्णांक num)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_kretprobe(काष्ठा kretprobe *rp)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_kretprobes(काष्ठा kretprobe **rps, पूर्णांक num)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_kretprobe(काष्ठा kretprobe *rp)
अणु
पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_kretprobes(काष्ठा kretprobe **rps, पूर्णांक num)
अणु
पूर्ण
अटल अंतरभूत व्योम kprobe_flush_task(काष्ठा task_काष्ठा *tk)
अणु
पूर्ण
अटल अंतरभूत व्योम kprobe_मुक्त_init_mem(व्योम)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक disable_kprobe(काष्ठा kprobe *kp)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक enable_kprobe(काष्ठा kprobe *kp)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत bool within_kprobe_blacklist(अचिन्हित दीर्घ addr)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत पूर्णांक kprobe_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value,
				     अक्षर *type, अक्षर *sym)
अणु
	वापस -दुस्फल;
पूर्ण
#पूर्ण_अगर /* CONFIG_KPROBES */
अटल अंतरभूत पूर्णांक disable_kretprobe(काष्ठा kretprobe *rp)
अणु
	वापस disable_kprobe(&rp->kp);
पूर्ण
अटल अंतरभूत पूर्णांक enable_kretprobe(काष्ठा kretprobe *rp)
अणु
	वापस enable_kprobe(&rp->kp);
पूर्ण

#अगर_अघोषित CONFIG_KPROBES
अटल अंतरभूत bool is_kprobe_insn_slot(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#अगर_अघोषित CONFIG_OPTPROBES
अटल अंतरभूत bool is_kprobe_optinsn_slot(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/* Returns true अगर kprobes handled the fault */
अटल nokprobe_अंतरभूत bool kprobe_page_fault(काष्ठा pt_regs *regs,
					      अचिन्हित पूर्णांक trap)
अणु
	अगर (!kprobes_built_in())
		वापस false;
	अगर (user_mode(regs))
		वापस false;
	/*
	 * To be potentially processing a kprobe fault and to be allowed
	 * to call kprobe_running(), we have to be non-preemptible.
	 */
	अगर (preemptible())
		वापस false;
	अगर (!kprobe_running())
		वापस false;
	वापस kprobe_fault_handler(regs, trap);
पूर्ण

#पूर्ण_अगर /* _LINUX_KPROBES_H */
