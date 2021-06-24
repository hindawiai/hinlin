<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Ftrace header.  For implementation details beyond the अक्रमom comments
 * scattered below, see: Documentation/trace/ftrace-design.rst
 */

#अगर_अघोषित _LINUX_FTRACE_H
#घोषणा _LINUX_FTRACE_H

#समावेश <linux/trace_recursion.h>
#समावेश <linux/trace_घड़ी.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/linkage.h>
#समावेश <linux/bitops.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>

#समावेश <यंत्र/ftrace.h>

/*
 * If the arch supports passing the variable contents of
 * function_trace_op as the third parameter back from the
 * mcount call, then the arch should define this as 1.
 */
#अगर_अघोषित ARCH_SUPPORTS_FTRACE_OPS
#घोषणा ARCH_SUPPORTS_FTRACE_OPS 0
#पूर्ण_अगर

/*
 * If the arch's mcount caller does not support all of ftrace's
 * features, then it must call an indirect function that
 * करोes. Or at least करोes enough to prevent any unwelcome side effects.
 */
#अगर !ARCH_SUPPORTS_FTRACE_OPS
# define FTRACE_FORCE_LIST_FUNC 1
#अन्यथा
# define FTRACE_FORCE_LIST_FUNC 0
#पूर्ण_अगर

/* Main tracing buffer and events set up */
#अगर_घोषित CONFIG_TRACING
व्योम trace_init(व्योम);
व्योम early_trace_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम trace_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम early_trace_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

काष्ठा module;
काष्ठा ftrace_hash;
काष्ठा ftrace_direct_func;

#अगर defined(CONFIG_FUNCTION_TRACER) && defined(CONFIG_MODULES) && \
	defined(CONFIG_DYNAMIC_FTRACE)
स्थिर अक्षर *
ftrace_mod_address_lookup(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
		   अचिन्हित दीर्घ *off, अक्षर **modname, अक्षर *sym);
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *
ftrace_mod_address_lookup(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
		   अचिन्हित दीर्घ *off, अक्षर **modname, अक्षर *sym)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FUNCTION_TRACER) && defined(CONFIG_DYNAMIC_FTRACE)
पूर्णांक ftrace_mod_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value,
			   अक्षर *type, अक्षर *name,
			   अक्षर *module_name, पूर्णांक *exported);
#अन्यथा
अटल अंतरभूत पूर्णांक ftrace_mod_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value,
					 अक्षर *type, अक्षर *name,
					 अक्षर *module_name, पूर्णांक *exported)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_TRACER

बाह्य पूर्णांक ftrace_enabled;
बाह्य पूर्णांक
ftrace_enable_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);

काष्ठा ftrace_ops;

#अगर_अघोषित CONFIG_HAVE_DYNAMIC_FTRACE_WITH_ARGS

काष्ठा ftrace_regs अणु
	काष्ठा pt_regs		regs;
पूर्ण;
#घोषणा arch_ftrace_get_regs(fregs) (&(fregs)->regs)

/*
 * ftrace_inकाष्ठाion_poपूर्णांकer_set() is to be defined by the architecture
 * अगर to allow setting of the inकाष्ठाion poपूर्णांकer from the ftrace_regs
 * when HAVE_DYNAMIC_FTRACE_WITH_ARGS is set and it supports
 * live kernel patching.
 */
#घोषणा ftrace_inकाष्ठाion_poपूर्णांकer_set(fregs, ip) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_HAVE_DYNAMIC_FTRACE_WITH_ARGS */

अटल __always_अंतरभूत काष्ठा pt_regs *ftrace_get_regs(काष्ठा ftrace_regs *fregs)
अणु
	अगर (!fregs)
		वापस शून्य;

	वापस arch_ftrace_get_regs(fregs);
पूर्ण

प्रकार व्योम (*ftrace_func_t)(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			      काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs);

ftrace_func_t ftrace_ops_get_func(काष्ठा ftrace_ops *ops);

/*
 * FTRACE_OPS_FL_* bits denote the state of ftrace_ops काष्ठा and are
 * set in the flags member.
 * CONTROL, SAVE_REGS, SAVE_REGS_IF_SUPPORTED, RECURSION, STUB and
 * IPMODIFY are a kind of attribute flags which can be set only beक्रमe
 * रेजिस्टरing the ftrace_ops, and can not be modअगरied जबतक रेजिस्टरed.
 * Changing those attribute flags after रेजिस्टरing ftrace_ops will
 * cause unexpected results.
 *
 * ENABLED - set/unset when ftrace_ops is रेजिस्टरed/unरेजिस्टरed
 * DYNAMIC - set when ftrace_ops is रेजिस्टरed to denote dynamically
 *           allocated ftrace_ops which need special care
 * SAVE_REGS - The ftrace_ops wants regs saved at each function called
 *            and passed to the callback. If this flag is set, but the
 *            architecture करोes not support passing regs
 *            (CONFIG_DYNAMIC_FTRACE_WITH_REGS is not defined), then the
 *            ftrace_ops will fail to रेजिस्टर, unless the next flag
 *            is set.
 * SAVE_REGS_IF_SUPPORTED - This is the same as SAVE_REGS, but अगर the
 *            handler can handle an arch that करोes not save regs
 *            (the handler tests अगर regs == शून्य), then it can set
 *            this flag instead. It will not fail रेजिस्टरing the ftrace_ops
 *            but, the regs field will be शून्य अगर the arch करोes not support
 *            passing regs to the handler.
 *            Note, अगर this flag is set, the SAVE_REGS flag will स्वतःmatically
 *            get set upon रेजिस्टरing the ftrace_ops, अगर the arch supports it.
 * RECURSION - The ftrace_ops can set this to tell the ftrace infraकाष्ठाure
 *            that the call back needs recursion protection. If it करोes
 *            not set this, then the ftrace infraकाष्ठाure will assume
 *            that the callback can handle recursion on its own.
 * STUB   - The ftrace_ops is just a place holder.
 * INITIALIZED - The ftrace_ops has alपढ़ोy been initialized (first use समय
 *            रेजिस्टर_ftrace_function() is called, it will initialized the ops)
 * DELETED - The ops are being deleted, करो not let them be रेजिस्टरed again.
 * ADDING  - The ops is in the process of being added.
 * REMOVING - The ops is in the process of being हटाओd.
 * MODIFYING - The ops is in the process of changing its filter functions.
 * ALLOC_TRAMP - A dynamic trampoline was allocated by the core code.
 *            The arch specअगरic code sets this flag when it allocated a
 *            trampoline. This lets the arch know that it can update the
 *            trampoline in हाल the callback function changes.
 *            The ftrace_ops trampoline can be set by the ftrace users, and
 *            in such हालs the arch must not modअगरy it. Only the arch ftrace
 *            core code should set this flag.
 * IPMODIFY - The ops can modअगरy the IP रेजिस्टर. This can only be set with
 *            SAVE_REGS. If another ops with this flag set is alपढ़ोy रेजिस्टरed
 *            क्रम any of the functions that this ops will be रेजिस्टरed क्रम, then
 *            this ops will fail to रेजिस्टर or set_filter_ip.
 * PID     - Is affected by set_ftrace_pid (allows filtering on those pids)
 * RCU     - Set when the ops can only be called when RCU is watching.
 * TRACE_ARRAY - The ops->निजी poपूर्णांकs to a trace_array descriptor.
 * PERMANENT - Set when the ops is permanent and should not be affected by
 *             ftrace_enabled.
 * सूचीECT - Used by the direct ftrace_ops helper क्रम direct functions
 *            (पूर्णांकernal ftrace only, should not be used by others)
 */
क्रमागत अणु
	FTRACE_OPS_FL_ENABLED			= BIT(0),
	FTRACE_OPS_FL_DYNAMIC			= BIT(1),
	FTRACE_OPS_FL_SAVE_REGS			= BIT(2),
	FTRACE_OPS_FL_SAVE_REGS_IF_SUPPORTED	= BIT(3),
	FTRACE_OPS_FL_RECURSION			= BIT(4),
	FTRACE_OPS_FL_STUB			= BIT(5),
	FTRACE_OPS_FL_INITIALIZED		= BIT(6),
	FTRACE_OPS_FL_DELETED			= BIT(7),
	FTRACE_OPS_FL_ADDING			= BIT(8),
	FTRACE_OPS_FL_REMOVING			= BIT(9),
	FTRACE_OPS_FL_MODIFYING			= BIT(10),
	FTRACE_OPS_FL_ALLOC_TRAMP		= BIT(11),
	FTRACE_OPS_FL_IPMODIFY			= BIT(12),
	FTRACE_OPS_FL_PID			= BIT(13),
	FTRACE_OPS_FL_RCU			= BIT(14),
	FTRACE_OPS_FL_TRACE_ARRAY		= BIT(15),
	FTRACE_OPS_FL_PERMANENT                 = BIT(16),
	FTRACE_OPS_FL_सूचीECT			= BIT(17),
पूर्ण;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
/* The hash used to know what functions callbacks trace */
काष्ठा ftrace_ops_hash अणु
	काष्ठा ftrace_hash __rcu	*notrace_hash;
	काष्ठा ftrace_hash __rcu	*filter_hash;
	काष्ठा mutex			regex_lock;
पूर्ण;

व्योम ftrace_मुक्त_init_mem(व्योम);
व्योम ftrace_मुक्त_mem(काष्ठा module *mod, व्योम *start, व्योम *end);
#अन्यथा
अटल अंतरभूत व्योम ftrace_मुक्त_init_mem(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_मुक्त_mem(काष्ठा module *mod, व्योम *start, व्योम *end) अणु पूर्ण
#पूर्ण_अगर

/*
 * Note, ftrace_ops can be referenced outside of RCU protection, unless
 * the RCU flag is set. If ftrace_ops is allocated and not part of kernel
 * core data, the unरेजिस्टरing of it will perक्रमm a scheduling on all CPUs
 * to make sure that there are no more users. Depending on the load of the
 * प्रणाली that may take a bit of समय.
 *
 * Any निजी data added must also take care not to be मुक्तd and अगर निजी
 * data is added to a ftrace_ops that is in core code, the user of the
 * ftrace_ops must perक्रमm a schedule_on_each_cpu() beक्रमe मुक्तing it.
 */
काष्ठा ftrace_ops अणु
	ftrace_func_t			func;
	काष्ठा ftrace_ops __rcu		*next;
	अचिन्हित दीर्घ			flags;
	व्योम				*निजी;
	ftrace_func_t			saved_func;
#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	काष्ठा ftrace_ops_hash		local_hash;
	काष्ठा ftrace_ops_hash		*func_hash;
	काष्ठा ftrace_ops_hash		old_hash;
	अचिन्हित दीर्घ			trampoline;
	अचिन्हित दीर्घ			trampoline_size;
	काष्ठा list_head		list;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा ftrace_ops __rcu *ftrace_ops_list;
बाह्य काष्ठा ftrace_ops ftrace_list_end;

/*
 * Traverse the ftrace_ops_list, invoking all entries.  The reason that we
 * can use rcu_dereference_raw_check() is that elements हटाओd from this list
 * are simply leaked, so there is no need to पूर्णांकeract with a grace-period
 * mechanism.  The rcu_dereference_raw_check() calls are needed to handle
 * concurrent insertions पूर्णांकo the ftrace_ops_list.
 *
 * Silly Alpha and silly poपूर्णांकer-speculation compiler optimizations!
 */
#घोषणा करो_क्रम_each_ftrace_op(op, list)			\
	op = rcu_dereference_raw_check(list);			\
	करो

/*
 * Optimized क्रम just a single item in the list (as that is the normal हाल).
 */
#घोषणा जबतक_क्रम_each_ftrace_op(op)				\
	जबतक (likely(op = rcu_dereference_raw_check((op)->next)) &&	\
	       unlikely((op) != &ftrace_list_end))

/*
 * Type of the current tracing.
 */
क्रमागत ftrace_tracing_type_t अणु
	FTRACE_TYPE_ENTER = 0, /* Hook the call of the function */
	FTRACE_TYPE_RETURN,	/* Hook the वापस of the function */
पूर्ण;

/* Current tracing type, शेष is FTRACE_TYPE_ENTER */
बाह्य क्रमागत ftrace_tracing_type_t ftrace_tracing_type;

/*
 * The ftrace_ops must be a अटल and should also
 * be पढ़ो_mostly.  These functions करो modअगरy पढ़ो_mostly variables
 * so use them sparely. Never मुक्त an ftrace_op or modअगरy the
 * next poपूर्णांकer after it has been रेजिस्टरed. Even after unरेजिस्टरing
 * it, the next poपूर्णांकer may still be used पूर्णांकernally.
 */
पूर्णांक रेजिस्टर_ftrace_function(काष्ठा ftrace_ops *ops);
पूर्णांक unरेजिस्टर_ftrace_function(काष्ठा ftrace_ops *ops);

बाह्य व्योम ftrace_stub(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
			काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs);

#अन्यथा /* !CONFIG_FUNCTION_TRACER */
/*
 * (un)रेजिस्टर_ftrace_function must be a macro since the ops parameter
 * must not be evaluated.
 */
#घोषणा रेजिस्टर_ftrace_function(ops) (अणु 0; पूर्ण)
#घोषणा unरेजिस्टर_ftrace_function(ops) (अणु 0; पूर्ण)
अटल अंतरभूत व्योम ftrace_समाप्त(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_मुक्त_init_mem(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_मुक्त_mem(काष्ठा module *mod, व्योम *start, व्योम *end) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

काष्ठा ftrace_func_entry अणु
	काष्ठा hlist_node hlist;
	अचिन्हित दीर्घ ip;
	अचिन्हित दीर्घ direct; /* क्रम direct lookup only */
पूर्ण;

काष्ठा dyn_ftrace;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS
बाह्य पूर्णांक ftrace_direct_func_count;
पूर्णांक रेजिस्टर_ftrace_direct(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr);
पूर्णांक unरेजिस्टर_ftrace_direct(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr);
पूर्णांक modअगरy_ftrace_direct(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ new_addr);
काष्ठा ftrace_direct_func *ftrace_find_direct_func(अचिन्हित दीर्घ addr);
पूर्णांक ftrace_modअगरy_direct_caller(काष्ठा ftrace_func_entry *entry,
				काष्ठा dyn_ftrace *rec,
				अचिन्हित दीर्घ old_addr,
				अचिन्हित दीर्घ new_addr);
अचिन्हित दीर्घ ftrace_find_rec_direct(अचिन्हित दीर्घ ip);
#अन्यथा
# define ftrace_direct_func_count 0
अटल अंतरभूत पूर्णांक रेजिस्टर_ftrace_direct(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक unरेजिस्टर_ftrace_direct(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक modअगरy_ftrace_direct(अचिन्हित दीर्घ ip,
				       अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ new_addr)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत काष्ठा ftrace_direct_func *ftrace_find_direct_func(अचिन्हित दीर्घ addr)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक ftrace_modअगरy_direct_caller(काष्ठा ftrace_func_entry *entry,
					      काष्ठा dyn_ftrace *rec,
					      अचिन्हित दीर्घ old_addr,
					      अचिन्हित दीर्घ new_addr)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ ftrace_find_rec_direct(अचिन्हित दीर्घ ip)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS */

#अगर_अघोषित CONFIG_HAVE_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS
/*
 * This must be implemented by the architecture.
 * It is the way the ftrace direct_ops helper, when called
 * via ftrace (because there's other callbacks besides the
 * direct call), can inक्रमm the architecture's trampoline that this
 * routine has a direct caller, and what the caller is.
 *
 * For example, in x86, it वापसs the direct caller
 * callback function via the regs->orig_ax parameter.
 * Then in the ftrace trampoline, अगर this is set, it makes
 * the वापस from the trampoline jump to the direct caller
 * instead of going back to the function it just traced.
 */
अटल अंतरभूत व्योम arch_ftrace_set_direct_caller(काष्ठा pt_regs *regs,
						 अचिन्हित दीर्घ addr) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS */

#अगर_घोषित CONFIG_STACK_TRACER

बाह्य पूर्णांक stack_tracer_enabled;

पूर्णांक stack_trace_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		       माप_प्रकार *lenp, loff_t *ppos);

/* DO NOT MODIFY THIS VARIABLE सूचीECTLY! */
DECLARE_PER_CPU(पूर्णांक, disable_stack_tracer);

/**
 * stack_tracer_disable - temporarily disable the stack tracer
 *
 * There's a few locations (namely in RCU) where stack tracing
 * cannot be executed. This function is used to disable stack
 * tracing during those critical sections.
 *
 * This function must be called with preemption or पूर्णांकerrupts
 * disabled and stack_tracer_enable() must be called लघुly after
 * जबतक preemption or पूर्णांकerrupts are still disabled.
 */
अटल अंतरभूत व्योम stack_tracer_disable(व्योम)
अणु
	/* Preemption or पूर्णांकerrupts must be disabled */
	अगर (IS_ENABLED(CONFIG_DEBUG_PREEMPT))
		WARN_ON_ONCE(!preempt_count() || !irqs_disabled());
	this_cpu_inc(disable_stack_tracer);
पूर्ण

/**
 * stack_tracer_enable - re-enable the stack tracer
 *
 * After stack_tracer_disable() is called, stack_tracer_enable()
 * must be called लघुly afterward.
 */
अटल अंतरभूत व्योम stack_tracer_enable(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_PREEMPT))
		WARN_ON_ONCE(!preempt_count() || !irqs_disabled());
	this_cpu_dec(disable_stack_tracer);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम stack_tracer_disable(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम stack_tracer_enable(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

पूर्णांक ftrace_arch_code_modअगरy_prepare(व्योम);
पूर्णांक ftrace_arch_code_modअगरy_post_process(व्योम);

क्रमागत ftrace_bug_type अणु
	FTRACE_BUG_UNKNOWN,
	FTRACE_BUG_INIT,
	FTRACE_BUG_NOP,
	FTRACE_BUG_CALL,
	FTRACE_BUG_UPDATE,
पूर्ण;
बाह्य क्रमागत ftrace_bug_type ftrace_bug_type;

/*
 * Archs can set this to poपूर्णांक to a variable that holds the value that was
 * expected at the call site beक्रमe calling ftrace_bug().
 */
बाह्य स्थिर व्योम *ftrace_expected;

व्योम ftrace_bug(पूर्णांक err, काष्ठा dyn_ftrace *rec);

काष्ठा seq_file;

बाह्य पूर्णांक ftrace_text_reserved(स्थिर व्योम *start, स्थिर व्योम *end);

काष्ठा ftrace_ops *ftrace_ops_trampoline(अचिन्हित दीर्घ addr);

bool is_ftrace_trampoline(अचिन्हित दीर्घ addr);

/*
 * The dyn_ftrace record's flags field is split पूर्णांकo two parts.
 * the first part which is '0-FTRACE_REF_MAX' is a counter of
 * the number of callbacks that have रेजिस्टरed the function that
 * the dyn_ftrace descriptor represents.
 *
 * The second part is a mask:
 *  ENABLED - the function is being traced
 *  REGS    - the record wants the function to save regs
 *  REGS_EN - the function is set up to save regs.
 *  IPMODIFY - the record allows क्रम the IP address to be changed.
 *  DISABLED - the record is not पढ़ोy to be touched yet
 *  सूचीECT   - there is a direct function to call
 *
 * When a new ftrace_ops is रेजिस्टरed and wants a function to save
 * pt_regs, the rec->flags REGS is set. When the function has been
 * set up to save regs, the REG_EN flag is set. Once a function
 * starts saving regs it will करो so until all ftrace_ops are हटाओd
 * from tracing that function.
 */
क्रमागत अणु
	FTRACE_FL_ENABLED	= (1UL << 31),
	FTRACE_FL_REGS		= (1UL << 30),
	FTRACE_FL_REGS_EN	= (1UL << 29),
	FTRACE_FL_TRAMP		= (1UL << 28),
	FTRACE_FL_TRAMP_EN	= (1UL << 27),
	FTRACE_FL_IPMODIFY	= (1UL << 26),
	FTRACE_FL_DISABLED	= (1UL << 25),
	FTRACE_FL_सूचीECT	= (1UL << 24),
	FTRACE_FL_सूचीECT_EN	= (1UL << 23),
पूर्ण;

#घोषणा FTRACE_REF_MAX_SHIFT	23
#घोषणा FTRACE_REF_MAX		((1UL << FTRACE_REF_MAX_SHIFT) - 1)

#घोषणा ftrace_rec_count(rec)	((rec)->flags & FTRACE_REF_MAX)

काष्ठा dyn_ftrace अणु
	अचिन्हित दीर्घ		ip; /* address of mcount call-site */
	अचिन्हित दीर्घ		flags;
	काष्ठा dyn_arch_ftrace	arch;
पूर्ण;

पूर्णांक ftrace_set_filter_ip(काष्ठा ftrace_ops *ops, अचिन्हित दीर्घ ip,
			 पूर्णांक हटाओ, पूर्णांक reset);
पूर्णांक ftrace_set_filter(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf,
		       पूर्णांक len, पूर्णांक reset);
पूर्णांक ftrace_set_notrace(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf,
			पूर्णांक len, पूर्णांक reset);
व्योम ftrace_set_global_filter(अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक reset);
व्योम ftrace_set_global_notrace(अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक reset);
व्योम ftrace_मुक्त_filter(काष्ठा ftrace_ops *ops);
व्योम ftrace_ops_set_global_filter(काष्ठा ftrace_ops *ops);

क्रमागत अणु
	FTRACE_UPDATE_CALLS		= (1 << 0),
	FTRACE_DISABLE_CALLS		= (1 << 1),
	FTRACE_UPDATE_TRACE_FUNC	= (1 << 2),
	FTRACE_START_FUNC_RET		= (1 << 3),
	FTRACE_STOP_FUNC_RET		= (1 << 4),
	FTRACE_MAY_SLEEP		= (1 << 5),
पूर्ण;

/*
 * The FTRACE_UPDATE_* क्रमागत is used to pass inक्रमmation back
 * from the ftrace_update_record() and ftrace_test_record()
 * functions. These are called by the code update routines
 * to find out what is to be करोne क्रम a given function.
 *
 *  IGNORE           - The function is alपढ़ोy what we want it to be
 *  MAKE_CALL        - Start tracing the function
 *  MODIFY_CALL      - Stop saving regs क्रम the function
 *  MAKE_NOP         - Stop tracing the function
 */
क्रमागत अणु
	FTRACE_UPDATE_IGNORE,
	FTRACE_UPDATE_MAKE_CALL,
	FTRACE_UPDATE_MODIFY_CALL,
	FTRACE_UPDATE_MAKE_NOP,
पूर्ण;

क्रमागत अणु
	FTRACE_ITER_FILTER	= (1 << 0),
	FTRACE_ITER_NOTRACE	= (1 << 1),
	FTRACE_ITER_PRINTALL	= (1 << 2),
	FTRACE_ITER_DO_PROBES	= (1 << 3),
	FTRACE_ITER_PROBE	= (1 << 4),
	FTRACE_ITER_MOD		= (1 << 5),
	FTRACE_ITER_ENABLED	= (1 << 6),
पूर्ण;

व्योम arch_ftrace_update_code(पूर्णांक command);
व्योम arch_ftrace_update_trampoline(काष्ठा ftrace_ops *ops);
व्योम *arch_ftrace_trampoline_func(काष्ठा ftrace_ops *ops, काष्ठा dyn_ftrace *rec);
व्योम arch_ftrace_trampoline_मुक्त(काष्ठा ftrace_ops *ops);

काष्ठा ftrace_rec_iter;

काष्ठा ftrace_rec_iter *ftrace_rec_iter_start(व्योम);
काष्ठा ftrace_rec_iter *ftrace_rec_iter_next(काष्ठा ftrace_rec_iter *iter);
काष्ठा dyn_ftrace *ftrace_rec_iter_record(काष्ठा ftrace_rec_iter *iter);

#घोषणा क्रम_ftrace_rec_iter(iter)		\
	क्रम (iter = ftrace_rec_iter_start();	\
	     iter;				\
	     iter = ftrace_rec_iter_next(iter))


पूर्णांक ftrace_update_record(काष्ठा dyn_ftrace *rec, bool enable);
पूर्णांक ftrace_test_record(काष्ठा dyn_ftrace *rec, bool enable);
व्योम ftrace_run_stop_machine(पूर्णांक command);
अचिन्हित दीर्घ ftrace_location(अचिन्हित दीर्घ ip);
अचिन्हित दीर्घ ftrace_location_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
अचिन्हित दीर्घ ftrace_get_addr_new(काष्ठा dyn_ftrace *rec);
अचिन्हित दीर्घ ftrace_get_addr_curr(काष्ठा dyn_ftrace *rec);

बाह्य ftrace_func_t ftrace_trace_function;

पूर्णांक ftrace_regex_खोलो(काष्ठा ftrace_ops *ops, पूर्णांक flag,
		  काष्ठा inode *inode, काष्ठा file *file);
sमाप_प्रकार ftrace_filter_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			    माप_प्रकार cnt, loff_t *ppos);
sमाप_प्रकार ftrace_notrace_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			     माप_प्रकार cnt, loff_t *ppos);
पूर्णांक ftrace_regex_release(काष्ठा inode *inode, काष्ठा file *file);

व्योम __init
ftrace_set_early_filter(काष्ठा ftrace_ops *ops, अक्षर *buf, पूर्णांक enable);

/* defined in arch */
बाह्य पूर्णांक ftrace_ip_converted(अचिन्हित दीर्घ ip);
बाह्य पूर्णांक ftrace_dyn_arch_init(व्योम);
बाह्य व्योम ftrace_replace_code(पूर्णांक enable);
बाह्य पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func);
बाह्य व्योम ftrace_caller(व्योम);
बाह्य व्योम ftrace_regs_caller(व्योम);
बाह्य व्योम ftrace_call(व्योम);
बाह्य व्योम ftrace_regs_call(व्योम);
बाह्य व्योम mcount_call(व्योम);

व्योम ftrace_modअगरy_all_code(पूर्णांक command);

#अगर_अघोषित FTRACE_ADDR
#घोषणा FTRACE_ADDR ((अचिन्हित दीर्घ)ftrace_caller)
#पूर्ण_अगर

#अगर_अघोषित FTRACE_GRAPH_ADDR
#घोषणा FTRACE_GRAPH_ADDR ((अचिन्हित दीर्घ)ftrace_graph_caller)
#पूर्ण_अगर

#अगर_अघोषित FTRACE_REGS_ADDR
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
# define FTRACE_REGS_ADDR ((अचिन्हित दीर्घ)ftrace_regs_caller)
#अन्यथा
# define FTRACE_REGS_ADDR FTRACE_ADDR
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * If an arch would like functions that are only traced
 * by the function graph tracer to jump directly to its own
 * trampoline, then they can define FTRACE_GRAPH_TRAMP_ADDR
 * to be that address to jump to.
 */
#अगर_अघोषित FTRACE_GRAPH_TRAMP_ADDR
#घोषणा FTRACE_GRAPH_TRAMP_ADDR ((अचिन्हित दीर्घ) 0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
बाह्य व्योम ftrace_graph_caller(व्योम);
बाह्य पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम);
बाह्य पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/**
 * ftrace_make_nop - convert code पूर्णांकo nop
 * @mod: module काष्ठाure अगर called by module load initialization
 * @rec: the call site record (e.g. mcount/fentry)
 * @addr: the address that the call site should be calling
 *
 * This is a very sensitive operation and great care needs
 * to be taken by the arch.  The operation should carefully
 * पढ़ो the location, check to see अगर what is पढ़ो is indeed
 * what we expect it to be, and then on success of the compare,
 * it should ग_लिखो to the location.
 *
 * The code segment at @rec->ip should be a caller to @addr
 *
 * Return must be:
 *  0 on success
 *  -EFAULT on error पढ़ोing the location
 *  -EINVAL on a failed compare of the contents
 *  -EPERM  on error writing to the location
 * Any other value will be considered a failure.
 */
बाह्य पूर्णांक ftrace_make_nop(काष्ठा module *mod,
			   काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr);


/**
 * ftrace_init_nop - initialize a nop call site
 * @mod: module काष्ठाure अगर called by module load initialization
 * @rec: the call site record (e.g. mcount/fentry)
 *
 * This is a very sensitive operation and great care needs
 * to be taken by the arch.  The operation should carefully
 * पढ़ो the location, check to see अगर what is पढ़ो is indeed
 * what we expect it to be, and then on success of the compare,
 * it should ग_लिखो to the location.
 *
 * The code segment at @rec->ip should contain the contents created by
 * the compiler
 *
 * Return must be:
 *  0 on success
 *  -EFAULT on error पढ़ोing the location
 *  -EINVAL on a failed compare of the contents
 *  -EPERM  on error writing to the location
 * Any other value will be considered a failure.
 */
#अगर_अघोषित ftrace_init_nop
अटल अंतरभूत पूर्णांक ftrace_init_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec)
अणु
	वापस ftrace_make_nop(mod, rec, MCOUNT_ADDR);
पूर्ण
#पूर्ण_अगर

/**
 * ftrace_make_call - convert a nop call site पूर्णांकo a call to addr
 * @rec: the call site record (e.g. mcount/fentry)
 * @addr: the address that the call site should call
 *
 * This is a very sensitive operation and great care needs
 * to be taken by the arch.  The operation should carefully
 * पढ़ो the location, check to see अगर what is पढ़ो is indeed
 * what we expect it to be, and then on success of the compare,
 * it should ग_लिखो to the location.
 *
 * The code segment at @rec->ip should be a nop
 *
 * Return must be:
 *  0 on success
 *  -EFAULT on error पढ़ोing the location
 *  -EINVAL on a failed compare of the contents
 *  -EPERM  on error writing to the location
 * Any other value will be considered a failure.
 */
बाह्य पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
/**
 * ftrace_modअगरy_call - convert from one addr to another (no nop)
 * @rec: the call site record (e.g. mcount/fentry)
 * @old_addr: the address expected to be currently called to
 * @addr: the address to change to
 *
 * This is a very sensitive operation and great care needs
 * to be taken by the arch.  The operation should carefully
 * पढ़ो the location, check to see अगर what is पढ़ो is indeed
 * what we expect it to be, and then on success of the compare,
 * it should ग_लिखो to the location.
 *
 * The code segment at @rec->ip should be a caller to @old_addr
 *
 * Return must be:
 *  0 on success
 *  -EFAULT on error पढ़ोing the location
 *  -EINVAL on a failed compare of the contents
 *  -EPERM  on error writing to the location
 * Any other value will be considered a failure.
 */
बाह्य पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
			      अचिन्हित दीर्घ addr);
#अन्यथा
/* Should never be called */
अटल अंतरभूत पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
				     अचिन्हित दीर्घ addr)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/* May be defined in arch */
बाह्य पूर्णांक ftrace_arch_पढ़ो_dyn_info(अक्षर *buf, पूर्णांक size);

बाह्य पूर्णांक skip_trace(अचिन्हित दीर्घ ip);
बाह्य व्योम ftrace_module_init(काष्ठा module *mod);
बाह्य व्योम ftrace_module_enable(काष्ठा module *mod);
बाह्य व्योम ftrace_release_mod(काष्ठा module *mod);

बाह्य व्योम ftrace_disable_daemon(व्योम);
बाह्य व्योम ftrace_enable_daemon(व्योम);
#अन्यथा /* CONFIG_DYNAMIC_FTRACE */
अटल अंतरभूत पूर्णांक skip_trace(अचिन्हित दीर्घ ip) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ftrace_disable_daemon(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_enable_daemon(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_module_init(काष्ठा module *mod) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_module_enable(काष्ठा module *mod) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_release_mod(काष्ठा module *mod) अणु पूर्ण
अटल अंतरभूत पूर्णांक ftrace_text_reserved(स्थिर व्योम *start, स्थिर व्योम *end)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ ftrace_location(अचिन्हित दीर्घ ip)
अणु
	वापस 0;
पूर्ण

/*
 * Again users of functions that have ftrace_ops may not
 * have them defined when ftrace is not enabled, but these
 * functions may still be called. Use a macro instead of अंतरभूत.
 */
#घोषणा ftrace_regex_खोलो(ops, flag, inod, file) (अणु -ENODEV; पूर्ण)
#घोषणा ftrace_set_early_filter(ops, buf, enable) करो अणु पूर्ण जबतक (0)
#घोषणा ftrace_set_filter_ip(ops, ip, हटाओ, reset) (अणु -ENODEV; पूर्ण)
#घोषणा ftrace_set_filter(ops, buf, len, reset) (अणु -ENODEV; पूर्ण)
#घोषणा ftrace_set_notrace(ops, buf, len, reset) (अणु -ENODEV; पूर्ण)
#घोषणा ftrace_मुक्त_filter(ops) करो अणु पूर्ण जबतक (0)
#घोषणा ftrace_ops_set_global_filter(ops) करो अणु पूर्ण जबतक (0)

अटल अंतरभूत sमाप_प्रकार ftrace_filter_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			    माप_प्रकार cnt, loff_t *ppos) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत sमाप_प्रकार ftrace_notrace_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			     माप_प्रकार cnt, loff_t *ppos) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक
ftrace_regex_release(काष्ठा inode *inode, काष्ठा file *file) अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत bool is_ftrace_trampoline(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

/* totally disable ftrace - can not re-enable after this */
व्योम ftrace_समाप्त(व्योम);

अटल अंतरभूत व्योम tracer_disable(व्योम)
अणु
#अगर_घोषित CONFIG_FUNCTION_TRACER
	ftrace_enabled = 0;
#पूर्ण_अगर
पूर्ण

/*
 * Ftrace disable/restore without lock. Some synchronization mechanism
 * must be used to prevent ftrace_enabled to be changed between
 * disable/restore.
 */
अटल अंतरभूत पूर्णांक __ftrace_enabled_save(व्योम)
अणु
#अगर_घोषित CONFIG_FUNCTION_TRACER
	पूर्णांक saved_ftrace_enabled = ftrace_enabled;
	ftrace_enabled = 0;
	वापस saved_ftrace_enabled;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __ftrace_enabled_restore(पूर्णांक enabled)
अणु
#अगर_घोषित CONFIG_FUNCTION_TRACER
	ftrace_enabled = enabled;
#पूर्ण_अगर
पूर्ण

/* All archs should have this, but we define it क्रम consistency */
#अगर_अघोषित ftrace_वापस_address0
# define ftrace_वापस_address0 __builtin_वापस_address(0)
#पूर्ण_अगर

/* Archs may use other ways क्रम ADDR1 and beyond */
#अगर_अघोषित ftrace_वापस_address
# अगरdef CONFIG_FRAME_POINTER
#  define ftrace_वापस_address(n) __builtin_वापस_address(n)
# अन्यथा
#  define ftrace_वापस_address(n) 0UL
# endअगर
#पूर्ण_अगर

#घोषणा CALLER_ADDR0 ((अचिन्हित दीर्घ)ftrace_वापस_address0)
#घोषणा CALLER_ADDR1 ((अचिन्हित दीर्घ)ftrace_वापस_address(1))
#घोषणा CALLER_ADDR2 ((अचिन्हित दीर्घ)ftrace_वापस_address(2))
#घोषणा CALLER_ADDR3 ((अचिन्हित दीर्घ)ftrace_वापस_address(3))
#घोषणा CALLER_ADDR4 ((अचिन्हित दीर्घ)ftrace_वापस_address(4))
#घोषणा CALLER_ADDR5 ((अचिन्हित दीर्घ)ftrace_वापस_address(5))
#घोषणा CALLER_ADDR6 ((अचिन्हित दीर्घ)ftrace_वापस_address(6))

अटल अंतरभूत अचिन्हित दीर्घ get_lock_parent_ip(व्योम)
अणु
	अचिन्हित दीर्घ addr = CALLER_ADDR0;

	अगर (!in_lock_functions(addr))
		वापस addr;
	addr = CALLER_ADDR1;
	अगर (!in_lock_functions(addr))
		वापस addr;
	वापस CALLER_ADDR2;
पूर्ण

#अगर_घोषित CONFIG_TRACE_PREEMPT_TOGGLE
  बाह्य व्योम trace_preempt_on(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1);
  बाह्य व्योम trace_preempt_off(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1);
#अन्यथा
/*
 * Use defines instead of अटल अंतरभूतs because some arches will make code out
 * of the CALLER_ADDR, when we really want these to be a real nop.
 */
# define trace_preempt_on(a0, a1) करो अणु पूर्ण जबतक (0)
# define trace_preempt_off(a0, a1) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_FTRACE_MCOUNT_RECORD
बाह्य व्योम ftrace_init(व्योम);
#अगर_घोषित CC_USING_PATCHABLE_FUNCTION_ENTRY
#घोषणा FTRACE_CALLSITE_SECTION	"__patchable_function_entries"
#अन्यथा
#घोषणा FTRACE_CALLSITE_SECTION	"__mcount_loc"
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत व्योम ftrace_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * Structure that defines an entry function trace.
 * It's alपढ़ोy packed but the attribute "packed" is needed
 * to हटाओ extra padding at the end.
 */
काष्ठा ftrace_graph_ent अणु
	अचिन्हित दीर्घ func; /* Current function */
	पूर्णांक depth;
पूर्ण __packed;

/*
 * Structure that defines a वापस function trace.
 * It's alपढ़ोy packed but the attribute "packed" is needed
 * to हटाओ extra padding at the end.
 */
काष्ठा ftrace_graph_ret अणु
	अचिन्हित दीर्घ func; /* Current function */
	पूर्णांक depth;
	/* Number of functions that overran the depth limit क्रम current task */
	अचिन्हित पूर्णांक overrun;
	अचिन्हित दीर्घ दीर्घ callसमय;
	अचिन्हित दीर्घ दीर्घ retसमय;
पूर्ण __packed;

/* Type of the callback handlers क्रम tracing function graph*/
प्रकार व्योम (*trace_func_graph_ret_t)(काष्ठा ftrace_graph_ret *); /* वापस */
प्रकार पूर्णांक (*trace_func_graph_ent_t)(काष्ठा ftrace_graph_ent *); /* entry */

बाह्य पूर्णांक ftrace_graph_entry_stub(काष्ठा ftrace_graph_ent *trace);

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

काष्ठा fgraph_ops अणु
	trace_func_graph_ent_t		entryfunc;
	trace_func_graph_ret_t		retfunc;
पूर्ण;

/*
 * Stack of वापस addresses क्रम functions
 * of a thपढ़ो.
 * Used in काष्ठा thपढ़ो_info
 */
काष्ठा ftrace_ret_stack अणु
	अचिन्हित दीर्घ ret;
	अचिन्हित दीर्घ func;
	अचिन्हित दीर्घ दीर्घ callसमय;
#अगर_घोषित CONFIG_FUNCTION_PROखाताR
	अचिन्हित दीर्घ दीर्घ subसमय;
#पूर्ण_अगर
#अगर_घोषित HAVE_FUNCTION_GRAPH_FP_TEST
	अचिन्हित दीर्घ fp;
#पूर्ण_अगर
#अगर_घोषित HAVE_FUNCTION_GRAPH_RET_ADDR_PTR
	अचिन्हित दीर्घ *retp;
#पूर्ण_अगर
पूर्ण;

/*
 * Primary handler of a function वापस.
 * It relays on ftrace_वापस_to_handler.
 * Defined in entry_32/64.S
 */
बाह्य व्योम वापस_to_handler(व्योम);

बाह्य पूर्णांक
function_graph_enter(अचिन्हित दीर्घ ret, अचिन्हित दीर्घ func,
		     अचिन्हित दीर्घ frame_poपूर्णांकer, अचिन्हित दीर्घ *retp);

काष्ठा ftrace_ret_stack *
ftrace_graph_get_ret_stack(काष्ठा task_काष्ठा *task, पूर्णांक idx);

अचिन्हित दीर्घ ftrace_graph_ret_addr(काष्ठा task_काष्ठा *task, पूर्णांक *idx,
				    अचिन्हित दीर्घ ret, अचिन्हित दीर्घ *retp);

/*
 * Someबार we करोn't want to trace a function with the function
 * graph tracer but we want them to keep traced by the usual function
 * tracer अगर the function graph tracer is not configured.
 */
#घोषणा __notrace_funcgraph		notrace

#घोषणा FTRACE_RETFUNC_DEPTH 50
#घोषणा FTRACE_RETSTACK_ALLOC_SIZE 32

बाह्य पूर्णांक रेजिस्टर_ftrace_graph(काष्ठा fgraph_ops *ops);
बाह्य व्योम unरेजिस्टर_ftrace_graph(काष्ठा fgraph_ops *ops);

बाह्य bool ftrace_graph_is_dead(व्योम);
बाह्य व्योम ftrace_graph_stop(व्योम);

/* The current handlers in use */
बाह्य trace_func_graph_ret_t ftrace_graph_वापस;
बाह्य trace_func_graph_ent_t ftrace_graph_entry;

बाह्य व्योम ftrace_graph_init_task(काष्ठा task_काष्ठा *t);
बाह्य व्योम ftrace_graph_निकास_task(काष्ठा task_काष्ठा *t);
बाह्य व्योम ftrace_graph_init_idle_task(काष्ठा task_काष्ठा *t, पूर्णांक cpu);

अटल अंतरभूत व्योम छोड़ो_graph_tracing(व्योम)
अणु
	atomic_inc(&current->tracing_graph_छोड़ो);
पूर्ण

अटल अंतरभूत व्योम unछोड़ो_graph_tracing(व्योम)
अणु
	atomic_dec(&current->tracing_graph_छोड़ो);
पूर्ण
#अन्यथा /* !CONFIG_FUNCTION_GRAPH_TRACER */

#घोषणा __notrace_funcgraph

अटल अंतरभूत व्योम ftrace_graph_init_task(काष्ठा task_काष्ठा *t) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_graph_निकास_task(काष्ठा task_काष्ठा *t) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_graph_init_idle_task(काष्ठा task_काष्ठा *t, पूर्णांक cpu) अणु पूर्ण

/* Define as macros as fgraph_ops may not be defined */
#घोषणा रेजिस्टर_ftrace_graph(ops) (अणु -1; पूर्ण)
#घोषणा unरेजिस्टर_ftrace_graph(ops) करो अणु पूर्ण जबतक (0)

अटल अंतरभूत अचिन्हित दीर्घ
ftrace_graph_ret_addr(काष्ठा task_काष्ठा *task, पूर्णांक *idx, अचिन्हित दीर्घ ret,
		      अचिन्हित दीर्घ *retp)
अणु
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम छोड़ो_graph_tracing(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम unछोड़ो_graph_tracing(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

#अगर_घोषित CONFIG_TRACING

/* flags क्रम current->trace */
क्रमागत अणु
	TSK_TRACE_FL_TRACE_BIT	= 0,
	TSK_TRACE_FL_GRAPH_BIT	= 1,
पूर्ण;
क्रमागत अणु
	TSK_TRACE_FL_TRACE	= 1 << TSK_TRACE_FL_TRACE_BIT,
	TSK_TRACE_FL_GRAPH	= 1 << TSK_TRACE_FL_GRAPH_BIT,
पूर्ण;

अटल अंतरभूत व्योम set_tsk_trace_trace(काष्ठा task_काष्ठा *tsk)
अणु
	set_bit(TSK_TRACE_FL_TRACE_BIT, &tsk->trace);
पूर्ण

अटल अंतरभूत व्योम clear_tsk_trace_trace(काष्ठा task_काष्ठा *tsk)
अणु
	clear_bit(TSK_TRACE_FL_TRACE_BIT, &tsk->trace);
पूर्ण

अटल अंतरभूत पूर्णांक test_tsk_trace_trace(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk->trace & TSK_TRACE_FL_TRACE;
पूर्ण

अटल अंतरभूत व्योम set_tsk_trace_graph(काष्ठा task_काष्ठा *tsk)
अणु
	set_bit(TSK_TRACE_FL_GRAPH_BIT, &tsk->trace);
पूर्ण

अटल अंतरभूत व्योम clear_tsk_trace_graph(काष्ठा task_काष्ठा *tsk)
अणु
	clear_bit(TSK_TRACE_FL_GRAPH_BIT, &tsk->trace);
पूर्ण

अटल अंतरभूत पूर्णांक test_tsk_trace_graph(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk->trace & TSK_TRACE_FL_GRAPH;
पूर्ण

क्रमागत ftrace_dump_mode;

बाह्य क्रमागत ftrace_dump_mode ftrace_dump_on_oops;
बाह्य पूर्णांक tracepoपूर्णांक_prपूर्णांकk;

बाह्य व्योम disable_trace_on_warning(व्योम);
बाह्य पूर्णांक __disable_trace_on_warning;

पूर्णांक tracepoपूर्णांक_prपूर्णांकk_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);

#अन्यथा /* CONFIG_TRACING */
अटल अंतरभूत व्योम  disable_trace_on_warning(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TRACING */

#अगर_घोषित CONFIG_FTRACE_SYSCALLS

अचिन्हित दीर्घ arch_syscall_addr(पूर्णांक nr);

#पूर्ण_अगर /* CONFIG_FTRACE_SYSCALLS */

#पूर्ण_अगर /* _LINUX_FTRACE_H */
