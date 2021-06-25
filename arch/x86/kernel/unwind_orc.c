<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/objtool.h>
#समावेश <linux/module.h>
#समावेश <linux/sort.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/orc_types.h>
#समावेश <यंत्र/orc_lookup.h>

#घोषणा orc_warn(fmt, ...) \
	prपूर्णांकk_deferred_once(KERN_WARNING "WARNING: " fmt, ##__VA_ARGS__)

#घोषणा orc_warn_current(args...)					\
(अणु									\
	अगर (state->task == current && !state->error)			\
		orc_warn(args);						\
पूर्ण)

बाह्य पूर्णांक __start_orc_unwind_ip[];
बाह्य पूर्णांक __stop_orc_unwind_ip[];
बाह्य काष्ठा orc_entry __start_orc_unwind[];
बाह्य काष्ठा orc_entry __stop_orc_unwind[];

अटल bool orc_init __ro_after_init;
अटल अचिन्हित पूर्णांक lookup_num_blocks __ro_after_init;

अटल अंतरभूत अचिन्हित दीर्घ orc_ip(स्थिर पूर्णांक *ip)
अणु
	वापस (अचिन्हित दीर्घ)ip + *ip;
पूर्ण

अटल काष्ठा orc_entry *__orc_find(पूर्णांक *ip_table, काष्ठा orc_entry *u_table,
				    अचिन्हित पूर्णांक num_entries, अचिन्हित दीर्घ ip)
अणु
	पूर्णांक *first = ip_table;
	पूर्णांक *last = ip_table + num_entries - 1;
	पूर्णांक *mid = first, *found = first;

	अगर (!num_entries)
		वापस शून्य;

	/*
	 * Do a binary range search to find the righपंचांगost duplicate of a given
	 * starting address.  Some entries are section terminators which are
	 * "weak" entries क्रम ensuring there are no gaps.  They should be
	 * ignored when they conflict with a real entry.
	 */
	जबतक (first <= last) अणु
		mid = first + ((last - first) / 2);

		अगर (orc_ip(mid) <= ip) अणु
			found = mid;
			first = mid + 1;
		पूर्ण अन्यथा
			last = mid - 1;
	पूर्ण

	वापस u_table + (found - ip_table);
पूर्ण

#अगर_घोषित CONFIG_MODULES
अटल काष्ठा orc_entry *orc_module_find(अचिन्हित दीर्घ ip)
अणु
	काष्ठा module *mod;

	mod = __module_address(ip);
	अगर (!mod || !mod->arch.orc_unwind || !mod->arch.orc_unwind_ip)
		वापस शून्य;
	वापस __orc_find(mod->arch.orc_unwind_ip, mod->arch.orc_unwind,
			  mod->arch.num_orcs, ip);
पूर्ण
#अन्यथा
अटल काष्ठा orc_entry *orc_module_find(अचिन्हित दीर्घ ip)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
अटल काष्ठा orc_entry *orc_find(अचिन्हित दीर्घ ip);

/*
 * Ftrace dynamic trampolines करो not have orc entries of their own.
 * But they are copies of the ftrace entries that are अटल and
 * defined in ftrace_*.S, which करो have orc entries.
 *
 * If the unwinder comes across a ftrace trampoline, then find the
 * ftrace function that was used to create it, and use that ftrace
 * function's orc entry, as the placement of the वापस code in
 * the stack will be identical.
 */
अटल काष्ठा orc_entry *orc_ftrace_find(अचिन्हित दीर्घ ip)
अणु
	काष्ठा ftrace_ops *ops;
	अचिन्हित दीर्घ caller;

	ops = ftrace_ops_trampoline(ip);
	अगर (!ops)
		वापस शून्य;

	अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS)
		caller = (अचिन्हित दीर्घ)ftrace_regs_call;
	अन्यथा
		caller = (अचिन्हित दीर्घ)ftrace_call;

	/* Prevent unlikely recursion */
	अगर (ip == caller)
		वापस शून्य;

	वापस orc_find(caller);
पूर्ण
#अन्यथा
अटल काष्ठा orc_entry *orc_ftrace_find(अचिन्हित दीर्घ ip)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/*
 * If we crash with IP==0, the last successfully executed inकाष्ठाion
 * was probably an indirect function call with a शून्य function poपूर्णांकer,
 * and we करोn't have unwind inक्रमmation क्रम शून्य.
 * This hardcoded ORC entry क्रम IP==0 allows us to unwind from a शून्य function
 * poपूर्णांकer पूर्णांकo its parent and then जारी normally from there.
 */
अटल काष्ठा orc_entry null_orc_entry = अणु
	.sp_offset = माप(दीर्घ),
	.sp_reg = ORC_REG_SP,
	.bp_reg = ORC_REG_UNDEFINED,
	.type = UNWIND_HINT_TYPE_CALL
पूर्ण;

/* Fake frame poपूर्णांकer entry -- used as a fallback क्रम generated code */
अटल काष्ठा orc_entry orc_fp_entry = अणु
	.type		= UNWIND_HINT_TYPE_CALL,
	.sp_reg		= ORC_REG_BP,
	.sp_offset	= 16,
	.bp_reg		= ORC_REG_PREV_SP,
	.bp_offset	= -16,
	.end		= 0,
पूर्ण;

अटल काष्ठा orc_entry *orc_find(अचिन्हित दीर्घ ip)
अणु
	अटल काष्ठा orc_entry *orc;

	अगर (ip == 0)
		वापस &null_orc_entry;

	/* For non-init vmlinux addresses, use the fast lookup table: */
	अगर (ip >= LOOKUP_START_IP && ip < LOOKUP_STOP_IP) अणु
		अचिन्हित पूर्णांक idx, start, stop;

		idx = (ip - LOOKUP_START_IP) / LOOKUP_BLOCK_SIZE;

		अगर (unlikely((idx >= lookup_num_blocks-1))) अणु
			orc_warn("WARNING: bad lookup idx: idx=%u num=%u ip=%pB\n",
				 idx, lookup_num_blocks, (व्योम *)ip);
			वापस शून्य;
		पूर्ण

		start = orc_lookup[idx];
		stop = orc_lookup[idx + 1] + 1;

		अगर (unlikely((__start_orc_unwind + start >= __stop_orc_unwind) ||
			     (__start_orc_unwind + stop > __stop_orc_unwind))) अणु
			orc_warn("WARNING: bad lookup value: idx=%u num=%u start=%u stop=%u ip=%pB\n",
				 idx, lookup_num_blocks, start, stop, (व्योम *)ip);
			वापस शून्य;
		पूर्ण

		वापस __orc_find(__start_orc_unwind_ip + start,
				  __start_orc_unwind + start, stop - start, ip);
	पूर्ण

	/* vmlinux .init slow lookup: */
	अगर (init_kernel_text(ip))
		वापस __orc_find(__start_orc_unwind_ip, __start_orc_unwind,
				  __stop_orc_unwind_ip - __start_orc_unwind_ip, ip);

	/* Module lookup: */
	orc = orc_module_find(ip);
	अगर (orc)
		वापस orc;

	वापस orc_ftrace_find(ip);
पूर्ण

#अगर_घोषित CONFIG_MODULES

अटल DEFINE_MUTEX(sort_mutex);
अटल पूर्णांक *cur_orc_ip_table = __start_orc_unwind_ip;
अटल काष्ठा orc_entry *cur_orc_table = __start_orc_unwind;

अटल व्योम orc_sort_swap(व्योम *_a, व्योम *_b, पूर्णांक size)
अणु
	काष्ठा orc_entry *orc_a, *orc_b;
	काष्ठा orc_entry orc_पंचांगp;
	पूर्णांक *a = _a, *b = _b, पंचांगp;
	पूर्णांक delta = _b - _a;

	/* Swap the .orc_unwind_ip entries: */
	पंचांगp = *a;
	*a = *b + delta;
	*b = पंचांगp - delta;

	/* Swap the corresponding .orc_unwind entries: */
	orc_a = cur_orc_table + (a - cur_orc_ip_table);
	orc_b = cur_orc_table + (b - cur_orc_ip_table);
	orc_पंचांगp = *orc_a;
	*orc_a = *orc_b;
	*orc_b = orc_पंचांगp;
पूर्ण

अटल पूर्णांक orc_sort_cmp(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	काष्ठा orc_entry *orc_a;
	स्थिर पूर्णांक *a = _a, *b = _b;
	अचिन्हित दीर्घ a_val = orc_ip(a);
	अचिन्हित दीर्घ b_val = orc_ip(b);

	अगर (a_val > b_val)
		वापस 1;
	अगर (a_val < b_val)
		वापस -1;

	/*
	 * The "weak" section terminator entries need to always be on the left
	 * to ensure the lookup code skips them in favor of real entries.
	 * These terminator entries exist to handle any gaps created by
	 * whitelisted .o files which didn't get objtool generation.
	 */
	orc_a = cur_orc_table + (a - cur_orc_ip_table);
	वापस orc_a->sp_reg == ORC_REG_UNDEFINED && !orc_a->end ? -1 : 1;
पूर्ण

व्योम unwind_module_init(काष्ठा module *mod, व्योम *_orc_ip, माप_प्रकार orc_ip_size,
			व्योम *_orc, माप_प्रकार orc_size)
अणु
	पूर्णांक *orc_ip = _orc_ip;
	काष्ठा orc_entry *orc = _orc;
	अचिन्हित पूर्णांक num_entries = orc_ip_size / माप(पूर्णांक);

	WARN_ON_ONCE(orc_ip_size % माप(पूर्णांक) != 0 ||
		     orc_size % माप(*orc) != 0 ||
		     num_entries != orc_size / माप(*orc));

	/*
	 * The 'cur_orc_*' globals allow the orc_sort_swap() callback to
	 * associate an .orc_unwind_ip table entry with its corresponding
	 * .orc_unwind entry so they can both be swapped.
	 */
	mutex_lock(&sort_mutex);
	cur_orc_ip_table = orc_ip;
	cur_orc_table = orc;
	sort(orc_ip, num_entries, माप(पूर्णांक), orc_sort_cmp, orc_sort_swap);
	mutex_unlock(&sort_mutex);

	mod->arch.orc_unwind_ip = orc_ip;
	mod->arch.orc_unwind = orc;
	mod->arch.num_orcs = num_entries;
पूर्ण
#पूर्ण_अगर

व्योम __init unwind_init(व्योम)
अणु
	माप_प्रकार orc_ip_size = (व्योम *)__stop_orc_unwind_ip - (व्योम *)__start_orc_unwind_ip;
	माप_प्रकार orc_size = (व्योम *)__stop_orc_unwind - (व्योम *)__start_orc_unwind;
	माप_प्रकार num_entries = orc_ip_size / माप(पूर्णांक);
	काष्ठा orc_entry *orc;
	पूर्णांक i;

	अगर (!num_entries || orc_ip_size % माप(पूर्णांक) != 0 ||
	    orc_size % माप(काष्ठा orc_entry) != 0 ||
	    num_entries != orc_size / माप(काष्ठा orc_entry)) अणु
		orc_warn("WARNING: Bad or missing .orc_unwind table.  Disabling unwinder.\n");
		वापस;
	पूर्ण

	/*
	 * Note, the orc_unwind and orc_unwind_ip tables were alपढ़ोy
	 * sorted at build समय via the 'sorttable' tool.
	 * It's पढ़ोy क्रम binary search straight away, no need to sort it.
	 */

	/* Initialize the fast lookup table: */
	lookup_num_blocks = orc_lookup_end - orc_lookup;
	क्रम (i = 0; i < lookup_num_blocks-1; i++) अणु
		orc = __orc_find(__start_orc_unwind_ip, __start_orc_unwind,
				 num_entries,
				 LOOKUP_START_IP + (LOOKUP_BLOCK_SIZE * i));
		अगर (!orc) अणु
			orc_warn("WARNING: Corrupt .orc_unwind table.  Disabling unwinder.\n");
			वापस;
		पूर्ण

		orc_lookup[i] = orc - __start_orc_unwind;
	पूर्ण

	/* Initialize the ending block: */
	orc = __orc_find(__start_orc_unwind_ip, __start_orc_unwind, num_entries,
			 LOOKUP_STOP_IP);
	अगर (!orc) अणु
		orc_warn("WARNING: Corrupt .orc_unwind table.  Disabling unwinder.\n");
		वापस;
	पूर्ण
	orc_lookup[lookup_num_blocks-1] = orc - __start_orc_unwind;

	orc_init = true;
पूर्ण

अचिन्हित दीर्घ unwind_get_वापस_address(काष्ठा unwind_state *state)
अणु
	अगर (unwind_करोne(state))
		वापस 0;

	वापस __kernel_text_address(state->ip) ? state->ip : 0;
पूर्ण
EXPORT_SYMBOL_GPL(unwind_get_वापस_address);

अचिन्हित दीर्घ *unwind_get_वापस_address_ptr(काष्ठा unwind_state *state)
अणु
	अगर (unwind_करोne(state))
		वापस शून्य;

	अगर (state->regs)
		वापस &state->regs->ip;

	अगर (state->sp)
		वापस (अचिन्हित दीर्घ *)state->sp - 1;

	वापस शून्य;
पूर्ण

अटल bool stack_access_ok(काष्ठा unwind_state *state, अचिन्हित दीर्घ _addr,
			    माप_प्रकार len)
अणु
	काष्ठा stack_info *info = &state->stack_info;
	व्योम *addr = (व्योम *)_addr;

	अगर (!on_stack(info, addr, len) &&
	    (get_stack_info(addr, state->task, info, &state->stack_mask)))
		वापस false;

	वापस true;
पूर्ण

अटल bool deref_stack_reg(काष्ठा unwind_state *state, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ *val)
अणु
	अगर (!stack_access_ok(state, addr, माप(दीर्घ)))
		वापस false;

	*val = READ_ONCE_NOCHECK(*(अचिन्हित दीर्घ *)addr);
	वापस true;
पूर्ण

अटल bool deref_stack_regs(काष्ठा unwind_state *state, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ *ip, अचिन्हित दीर्घ *sp)
अणु
	काष्ठा pt_regs *regs = (काष्ठा pt_regs *)addr;

	/* x86-32 support will be more complicated due to the &regs->sp hack */
	BUILD_BUG_ON(IS_ENABLED(CONFIG_X86_32));

	अगर (!stack_access_ok(state, addr, माप(काष्ठा pt_regs)))
		वापस false;

	*ip = READ_ONCE_NOCHECK(regs->ip);
	*sp = READ_ONCE_NOCHECK(regs->sp);
	वापस true;
पूर्ण

अटल bool deref_stack_iret_regs(काष्ठा unwind_state *state, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ *ip, अचिन्हित दीर्घ *sp)
अणु
	काष्ठा pt_regs *regs = (व्योम *)addr - IRET_FRAME_OFFSET;

	अगर (!stack_access_ok(state, addr, IRET_FRAME_SIZE))
		वापस false;

	*ip = READ_ONCE_NOCHECK(regs->ip);
	*sp = READ_ONCE_NOCHECK(regs->sp);
	वापस true;
पूर्ण

/*
 * If state->regs is non-शून्य, and poपूर्णांकs to a full pt_regs, just get the reg
 * value from state->regs.
 *
 * Otherwise, अगर state->regs just poपूर्णांकs to IRET regs, and the previous frame
 * had full regs, it's safe to get the value from the previous regs.  This can
 * happen when early/late IRQ entry code माला_लो पूर्णांकerrupted by an NMI.
 */
अटल bool get_reg(काष्ठा unwind_state *state, अचिन्हित पूर्णांक reg_off,
		    अचिन्हित दीर्घ *val)
अणु
	अचिन्हित पूर्णांक reg = reg_off/8;

	अगर (!state->regs)
		वापस false;

	अगर (state->full_regs) अणु
		*val = READ_ONCE_NOCHECK(((अचिन्हित दीर्घ *)state->regs)[reg]);
		वापस true;
	पूर्ण

	अगर (state->prev_regs) अणु
		*val = READ_ONCE_NOCHECK(((अचिन्हित दीर्घ *)state->prev_regs)[reg]);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool unwind_next_frame(काष्ठा unwind_state *state)
अणु
	अचिन्हित दीर्घ ip_p, sp, पंचांगp, orig_ip = state->ip, prev_sp = state->sp;
	क्रमागत stack_type prev_type = state->stack_info.type;
	काष्ठा orc_entry *orc;
	bool indirect = false;

	अगर (unwind_करोne(state))
		वापस false;

	/* Don't let modules unload while we're पढ़ोing their ORC data. */
	preempt_disable();

	/* End-of-stack check क्रम user tasks: */
	अगर (state->regs && user_mode(state->regs))
		जाओ the_end;

	/*
	 * Find the orc_entry associated with the text address.
	 *
	 * For a call frame (as opposed to a संकेत frame), state->ip poपूर्णांकs to
	 * the inकाष्ठाion after the call.  That inकाष्ठाion's stack layout
	 * could be dअगरferent from the call inकाष्ठाion's layout, क्रम example
	 * अगर the call was to a noवापस function.  So get the ORC data क्रम the
	 * call inकाष्ठाion itself.
	 */
	orc = orc_find(state->संकेत ? state->ip : state->ip - 1);
	अगर (!orc) अणु
		/*
		 * As a fallback, try to assume this code uses a frame poपूर्णांकer.
		 * This is useful क्रम generated code, like BPF, which ORC
		 * करोesn't know about.  This is just a guess, so the rest of
		 * the unwind is no दीर्घer considered reliable.
		 */
		orc = &orc_fp_entry;
		state->error = true;
	पूर्ण

	/* End-of-stack check क्रम kernel thपढ़ोs: */
	अगर (orc->sp_reg == ORC_REG_UNDEFINED) अणु
		अगर (!orc->end)
			जाओ err;

		जाओ the_end;
	पूर्ण

	/* Find the previous frame's stack: */
	चयन (orc->sp_reg) अणु
	हाल ORC_REG_SP:
		sp = state->sp + orc->sp_offset;
		अवरोध;

	हाल ORC_REG_BP:
		sp = state->bp + orc->sp_offset;
		अवरोध;

	हाल ORC_REG_SP_INसूचीECT:
		sp = state->sp;
		indirect = true;
		अवरोध;

	हाल ORC_REG_BP_INसूचीECT:
		sp = state->bp + orc->sp_offset;
		indirect = true;
		अवरोध;

	हाल ORC_REG_R10:
		अगर (!get_reg(state, दुरत्व(काष्ठा pt_regs, r10), &sp)) अणु
			orc_warn_current("missing R10 value at %pB\n",
					 (व्योम *)state->ip);
			जाओ err;
		पूर्ण
		अवरोध;

	हाल ORC_REG_R13:
		अगर (!get_reg(state, दुरत्व(काष्ठा pt_regs, r13), &sp)) अणु
			orc_warn_current("missing R13 value at %pB\n",
					 (व्योम *)state->ip);
			जाओ err;
		पूर्ण
		अवरोध;

	हाल ORC_REG_DI:
		अगर (!get_reg(state, दुरत्व(काष्ठा pt_regs, di), &sp)) अणु
			orc_warn_current("missing RDI value at %pB\n",
					 (व्योम *)state->ip);
			जाओ err;
		पूर्ण
		अवरोध;

	हाल ORC_REG_DX:
		अगर (!get_reg(state, दुरत्व(काष्ठा pt_regs, dx), &sp)) अणु
			orc_warn_current("missing DX value at %pB\n",
					 (व्योम *)state->ip);
			जाओ err;
		पूर्ण
		अवरोध;

	शेष:
		orc_warn("unknown SP base reg %d at %pB\n",
			 orc->sp_reg, (व्योम *)state->ip);
		जाओ err;
	पूर्ण

	अगर (indirect) अणु
		अगर (!deref_stack_reg(state, sp, &sp))
			जाओ err;

		अगर (orc->sp_reg == ORC_REG_SP_INसूचीECT)
			sp += orc->sp_offset;
	पूर्ण

	/* Find IP, SP and possibly regs: */
	चयन (orc->type) अणु
	हाल UNWIND_HINT_TYPE_CALL:
		ip_p = sp - माप(दीर्घ);

		अगर (!deref_stack_reg(state, ip_p, &state->ip))
			जाओ err;

		state->ip = ftrace_graph_ret_addr(state->task, &state->graph_idx,
						  state->ip, (व्योम *)ip_p);

		state->sp = sp;
		state->regs = शून्य;
		state->prev_regs = शून्य;
		state->संकेत = false;
		अवरोध;

	हाल UNWIND_HINT_TYPE_REGS:
		अगर (!deref_stack_regs(state, sp, &state->ip, &state->sp)) अणु
			orc_warn_current("can't access registers at %pB\n",
					 (व्योम *)orig_ip);
			जाओ err;
		पूर्ण

		state->regs = (काष्ठा pt_regs *)sp;
		state->prev_regs = शून्य;
		state->full_regs = true;
		state->संकेत = true;
		अवरोध;

	हाल UNWIND_HINT_TYPE_REGS_PARTIAL:
		अगर (!deref_stack_iret_regs(state, sp, &state->ip, &state->sp)) अणु
			orc_warn_current("can't access iret registers at %pB\n",
					 (व्योम *)orig_ip);
			जाओ err;
		पूर्ण

		अगर (state->full_regs)
			state->prev_regs = state->regs;
		state->regs = (व्योम *)sp - IRET_FRAME_OFFSET;
		state->full_regs = false;
		state->संकेत = true;
		अवरोध;

	शेष:
		orc_warn("unknown .orc_unwind entry type %d at %pB\n",
			 orc->type, (व्योम *)orig_ip);
		जाओ err;
	पूर्ण

	/* Find BP: */
	चयन (orc->bp_reg) अणु
	हाल ORC_REG_UNDEFINED:
		अगर (get_reg(state, दुरत्व(काष्ठा pt_regs, bp), &पंचांगp))
			state->bp = पंचांगp;
		अवरोध;

	हाल ORC_REG_PREV_SP:
		अगर (!deref_stack_reg(state, sp + orc->bp_offset, &state->bp))
			जाओ err;
		अवरोध;

	हाल ORC_REG_BP:
		अगर (!deref_stack_reg(state, state->bp + orc->bp_offset, &state->bp))
			जाओ err;
		अवरोध;

	शेष:
		orc_warn("unknown BP base reg %d for ip %pB\n",
			 orc->bp_reg, (व्योम *)orig_ip);
		जाओ err;
	पूर्ण

	/* Prevent a recursive loop due to bad ORC data: */
	अगर (state->stack_info.type == prev_type &&
	    on_stack(&state->stack_info, (व्योम *)state->sp, माप(दीर्घ)) &&
	    state->sp <= prev_sp) अणु
		orc_warn_current("stack going in the wrong direction? at %pB\n",
				 (व्योम *)orig_ip);
		जाओ err;
	पूर्ण

	preempt_enable();
	वापस true;

err:
	state->error = true;

the_end:
	preempt_enable();
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(unwind_next_frame);

व्योम __unwind_start(काष्ठा unwind_state *state, काष्ठा task_काष्ठा *task,
		    काष्ठा pt_regs *regs, अचिन्हित दीर्घ *first_frame)
अणु
	स_रखो(state, 0, माप(*state));
	state->task = task;

	अगर (!orc_init)
		जाओ err;

	/*
	 * Refuse to unwind the stack of a task जबतक it's executing on another
	 * CPU.  This check is racy, but that's ok: the unwinder has other
	 * checks to prevent it from going off the rails.
	 */
	अगर (task_on_another_cpu(task))
		जाओ err;

	अगर (regs) अणु
		अगर (user_mode(regs))
			जाओ the_end;

		state->ip = regs->ip;
		state->sp = regs->sp;
		state->bp = regs->bp;
		state->regs = regs;
		state->full_regs = true;
		state->संकेत = true;

	पूर्ण अन्यथा अगर (task == current) अणु
		यंत्र अस्थिर("lea (%%rip), %0\n\t"
			     "mov %%rsp, %1\n\t"
			     "mov %%rbp, %2\n\t"
			     : "=r" (state->ip), "=r" (state->sp),
			       "=r" (state->bp));

	पूर्ण अन्यथा अणु
		काष्ठा inactive_task_frame *frame = (व्योम *)task->thपढ़ो.sp;

		state->sp = task->thपढ़ो.sp + माप(*frame);
		state->bp = READ_ONCE_NOCHECK(frame->bp);
		state->ip = READ_ONCE_NOCHECK(frame->ret_addr);
		state->संकेत = (व्योम *)state->ip == ret_from_विभाजन;
	पूर्ण

	अगर (get_stack_info((अचिन्हित दीर्घ *)state->sp, state->task,
			   &state->stack_info, &state->stack_mask)) अणु
		/*
		 * We weren't on a valid stack.  It's possible that
		 * we overflowed a valid stack पूर्णांकo a guard page.
		 * See अगर the next page up is valid so that we can
		 * generate some kind of backtrace अगर this happens.
		 */
		व्योम *next_page = (व्योम *)PAGE_ALIGN((अचिन्हित दीर्घ)state->sp);
		state->error = true;
		अगर (get_stack_info(next_page, state->task, &state->stack_info,
				   &state->stack_mask))
			वापस;
	पूर्ण

	/*
	 * The caller can provide the address of the first frame directly
	 * (first_frame) or indirectly (regs->sp) to indicate which stack frame
	 * to start unwinding at.  Skip ahead until we reach it.
	 */

	/* When starting from regs, skip the regs frame: */
	अगर (regs) अणु
		unwind_next_frame(state);
		वापस;
	पूर्ण

	/* Otherwise, skip ahead to the user-specअगरied starting frame: */
	जबतक (!unwind_करोne(state) &&
	       (!on_stack(&state->stack_info, first_frame, माप(दीर्घ)) ||
			state->sp < (अचिन्हित दीर्घ)first_frame))
		unwind_next_frame(state);

	वापस;

err:
	state->error = true;
the_end:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
पूर्ण
EXPORT_SYMBOL_GPL(__unwind_start);
