<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dynamic function tracing support.
 *
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 *
 * Thanks goes to Ingo Molnar, क्रम suggesting the idea.
 * Mathieu Desnoyers, क्रम suggesting postponing the modअगरications.
 * Arjan van de Ven, क्रम keeping me straight, and explaining to me
 * the dangers of modअगरying code on the run.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/spinlock.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/memory.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <trace/syscall.h>

#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/nops.h>
#समावेश <यंत्र/text-patching.h>

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

अटल पूर्णांक ftrace_poke_late = 0;

पूर्णांक ftrace_arch_code_modअगरy_prepare(व्योम)
    __acquires(&text_mutex)
अणु
	/*
	 * Need to grab text_mutex to prevent a race from module loading
	 * and live kernel patching from changing the text permissions जबतक
	 * ftrace has it set to "read/write".
	 */
	mutex_lock(&text_mutex);
	ftrace_poke_late = 1;
	वापस 0;
पूर्ण

पूर्णांक ftrace_arch_code_modअगरy_post_process(व्योम)
    __releases(&text_mutex)
अणु
	/*
	 * ftrace_make_अणुcall,nopपूर्ण() may be called during
	 * module load, and we need to finish the text_poke_queue()
	 * that they करो, here.
	 */
	text_poke_finish();
	ftrace_poke_late = 0;
	mutex_unlock(&text_mutex);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *ftrace_nop_replace(व्योम)
अणु
	वापस x86_nops[5];
पूर्ण

अटल स्थिर अक्षर *ftrace_call_replace(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	वापस text_gen_insn(CALL_INSN_OPCODE, (व्योम *)ip, (व्योम *)addr);
पूर्ण

अटल पूर्णांक ftrace_verअगरy_code(अचिन्हित दीर्घ ip, स्थिर अक्षर *old_code)
अणु
	अक्षर cur_code[MCOUNT_INSN_SIZE];

	/*
	 * Note:
	 * We are paranoid about modअगरying text, as अगर a bug was to happen, it
	 * could cause us to पढ़ो or ग_लिखो to someplace that could cause harm.
	 * Carefully पढ़ो and modअगरy the code with probe_kernel_*(), and make
	 * sure what we पढ़ो is what we expected it to be beक्रमe modअगरying it.
	 */
	/* पढ़ो the text we want to modअगरy */
	अगर (copy_from_kernel_nofault(cur_code, (व्योम *)ip, MCOUNT_INSN_SIZE)) अणु
		WARN_ON(1);
		वापस -EFAULT;
	पूर्ण

	/* Make sure it is what we expect it to be */
	अगर (स_भेद(cur_code, old_code, MCOUNT_INSN_SIZE) != 0) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Marked __ref because it calls text_poke_early() which is .init.text. That is
 * ok because that call will happen early, during boot, when .init sections are
 * still present.
 */
अटल पूर्णांक __ref
ftrace_modअगरy_code_direct(अचिन्हित दीर्घ ip, स्थिर अक्षर *old_code,
			  स्थिर अक्षर *new_code)
अणु
	पूर्णांक ret = ftrace_verअगरy_code(ip, old_code);
	अगर (ret)
		वापस ret;

	/* replace the text with the new text */
	अगर (ftrace_poke_late)
		text_poke_queue((व्योम *)ip, new_code, MCOUNT_INSN_SIZE, शून्य);
	अन्यथा
		text_poke_early((व्योम *)ip, new_code, MCOUNT_INSN_SIZE);
	वापस 0;
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	स्थिर अक्षर *new, *old;

	old = ftrace_call_replace(ip, addr);
	new = ftrace_nop_replace();

	/*
	 * On boot up, and when modules are loaded, the MCOUNT_ADDR
	 * is converted to a nop, and will never become MCOUNT_ADDR
	 * again. This code is either running beक्रमe SMP (on boot up)
	 * or beक्रमe the code will ever be executed (module load).
	 * We करो not want to use the अवरोधpoपूर्णांक version in this हाल,
	 * just modअगरy the code directly.
	 */
	अगर (addr == MCOUNT_ADDR)
		वापस ftrace_modअगरy_code_direct(ip, old, new);

	/*
	 * x86 overrides ftrace_replace_code -- this function will never be used
	 * in this हाल.
	 */
	WARN_ONCE(1, "invalid use of ftrace_make_nop");
	वापस -EINVAL;
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	स्थिर अक्षर *new, *old;

	old = ftrace_nop_replace();
	new = ftrace_call_replace(ip, addr);

	/* Should only be called when module is loaded */
	वापस ftrace_modअगरy_code_direct(rec->ip, old, new);
पूर्ण

/*
 * Should never be called:
 *  As it is only called by __ftrace_replace_code() which is called by
 *  ftrace_replace_code() that x86 overrides, and by ftrace_update_code()
 *  which is called to turn mcount पूर्णांकo nops or nops पूर्णांकo function calls
 *  but not to convert a function from not using regs to one that uses
 *  regs, which ftrace_modअगरy_call() is क्रम.
 */
पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
				 अचिन्हित दीर्घ addr)
अणु
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ ip;
	स्थिर अक्षर *new;

	ip = (अचिन्हित दीर्घ)(&ftrace_call);
	new = ftrace_call_replace(ip, (अचिन्हित दीर्घ)func);
	text_poke_bp((व्योम *)ip, new, MCOUNT_INSN_SIZE, शून्य);

	ip = (अचिन्हित दीर्घ)(&ftrace_regs_call);
	new = ftrace_call_replace(ip, (अचिन्हित दीर्घ)func);
	text_poke_bp((व्योम *)ip, new, MCOUNT_INSN_SIZE, शून्य);

	वापस 0;
पूर्ण

व्योम ftrace_replace_code(पूर्णांक enable)
अणु
	काष्ठा ftrace_rec_iter *iter;
	काष्ठा dyn_ftrace *rec;
	स्थिर अक्षर *new, *old;
	पूर्णांक ret;

	क्रम_ftrace_rec_iter(iter) अणु
		rec = ftrace_rec_iter_record(iter);

		चयन (ftrace_test_record(rec, enable)) अणु
		हाल FTRACE_UPDATE_IGNORE:
		शेष:
			जारी;

		हाल FTRACE_UPDATE_MAKE_CALL:
			old = ftrace_nop_replace();
			अवरोध;

		हाल FTRACE_UPDATE_MODIFY_CALL:
		हाल FTRACE_UPDATE_MAKE_NOP:
			old = ftrace_call_replace(rec->ip, ftrace_get_addr_curr(rec));
			अवरोध;
		पूर्ण

		ret = ftrace_verअगरy_code(rec->ip, old);
		अगर (ret) अणु
			ftrace_bug(ret, rec);
			वापस;
		पूर्ण
	पूर्ण

	क्रम_ftrace_rec_iter(iter) अणु
		rec = ftrace_rec_iter_record(iter);

		चयन (ftrace_test_record(rec, enable)) अणु
		हाल FTRACE_UPDATE_IGNORE:
		शेष:
			जारी;

		हाल FTRACE_UPDATE_MAKE_CALL:
		हाल FTRACE_UPDATE_MODIFY_CALL:
			new = ftrace_call_replace(rec->ip, ftrace_get_addr_new(rec));
			अवरोध;

		हाल FTRACE_UPDATE_MAKE_NOP:
			new = ftrace_nop_replace();
			अवरोध;
		पूर्ण

		text_poke_queue((व्योम *)rec->ip, new, MCOUNT_INSN_SIZE, शून्य);
		ftrace_update_record(rec, enable);
	पूर्ण
	text_poke_finish();
पूर्ण

व्योम arch_ftrace_update_code(पूर्णांक command)
अणु
	ftrace_modअगरy_all_code(command);
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण

/* Currently only x86_64 supports dynamic trampolines */
#अगर_घोषित CONFIG_X86_64

#अगर_घोषित CONFIG_MODULES
#समावेश <linux/moduleloader.h>
/* Module allocation simplअगरies allocating memory क्रम code */
अटल अंतरभूत व्योम *alloc_tramp(अचिन्हित दीर्घ size)
अणु
	वापस module_alloc(size);
पूर्ण
अटल अंतरभूत व्योम tramp_मुक्त(व्योम *tramp)
अणु
	module_memमुक्त(tramp);
पूर्ण
#अन्यथा
/* Trampolines can only be created अगर modules are supported */
अटल अंतरभूत व्योम *alloc_tramp(अचिन्हित दीर्घ size)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम tramp_मुक्त(व्योम *tramp) अणु पूर्ण
#पूर्ण_अगर

/* Defined as markers to the end of the ftrace शेष trampolines */
बाह्य व्योम ftrace_regs_caller_end(व्योम);
बाह्य व्योम ftrace_regs_caller_ret(व्योम);
बाह्य व्योम ftrace_caller_end(व्योम);
बाह्य व्योम ftrace_caller_op_ptr(व्योम);
बाह्य व्योम ftrace_regs_caller_op_ptr(व्योम);
बाह्य व्योम ftrace_regs_caller_jmp(व्योम);

/* movq function_trace_op(%rip), %rdx */
/* 0x48 0x8b 0x15 <offset-to-ftrace_trace_op (4 bytes)> */
#घोषणा OP_REF_SIZE	7

/*
 * The ftrace_ops is passed to the function callback. Since the
 * trampoline only services a single ftrace_ops, we can pass in
 * that ops directly.
 *
 * The ftrace_op_code_जोड़ is used to create a poपूर्णांकer to the
 * ftrace_ops that will be passed to the callback function.
 */
जोड़ ftrace_op_code_जोड़ अणु
	अक्षर code[OP_REF_SIZE];
	काष्ठा अणु
		अक्षर op[3];
		पूर्णांक offset;
	पूर्ण __attribute__((packed));
पूर्ण;

#घोषणा RET_SIZE		1

अटल अचिन्हित दीर्घ
create_trampoline(काष्ठा ftrace_ops *ops, अचिन्हित पूर्णांक *tramp_size)
अणु
	अचिन्हित दीर्घ start_offset;
	अचिन्हित दीर्घ end_offset;
	अचिन्हित दीर्घ op_offset;
	अचिन्हित दीर्घ call_offset;
	अचिन्हित दीर्घ jmp_offset;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ retq;
	अचिन्हित दीर्घ *ptr;
	व्योम *trampoline;
	व्योम *ip;
	/* 48 8b 15 <offset> is movq <offset>(%rip), %rdx */
	अचिन्हित स्थिर अक्षर op_ref[] = अणु 0x48, 0x8b, 0x15 पूर्ण;
	जोड़ ftrace_op_code_जोड़ op_ptr;
	पूर्णांक ret;

	अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS) अणु
		start_offset = (अचिन्हित दीर्घ)ftrace_regs_caller;
		end_offset = (अचिन्हित दीर्घ)ftrace_regs_caller_end;
		op_offset = (अचिन्हित दीर्घ)ftrace_regs_caller_op_ptr;
		call_offset = (अचिन्हित दीर्घ)ftrace_regs_call;
		jmp_offset = (अचिन्हित दीर्घ)ftrace_regs_caller_jmp;
	पूर्ण अन्यथा अणु
		start_offset = (अचिन्हित दीर्घ)ftrace_caller;
		end_offset = (अचिन्हित दीर्घ)ftrace_caller_end;
		op_offset = (अचिन्हित दीर्घ)ftrace_caller_op_ptr;
		call_offset = (अचिन्हित दीर्घ)ftrace_call;
		jmp_offset = 0;
	पूर्ण

	size = end_offset - start_offset;

	/*
	 * Allocate enough size to store the ftrace_caller code,
	 * the iret , as well as the address of the ftrace_ops this
	 * trampoline is used क्रम.
	 */
	trampoline = alloc_tramp(size + RET_SIZE + माप(व्योम *));
	अगर (!trampoline)
		वापस 0;

	*tramp_size = size + RET_SIZE + माप(व्योम *);
	npages = DIV_ROUND_UP(*tramp_size, PAGE_SIZE);

	/* Copy ftrace_caller onto the trampoline memory */
	ret = copy_from_kernel_nofault(trampoline, (व्योम *)start_offset, size);
	अगर (WARN_ON(ret < 0))
		जाओ fail;

	ip = trampoline + size;

	/* The trampoline ends with ret(q) */
	retq = (अचिन्हित दीर्घ)ftrace_stub;
	ret = copy_from_kernel_nofault(ip, (व्योम *)retq, RET_SIZE);
	अगर (WARN_ON(ret < 0))
		जाओ fail;

	/* No need to test direct calls on created trampolines */
	अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS) अणु
		/* NOP the jnz 1f; but make sure it's a 2 byte jnz */
		ip = trampoline + (jmp_offset - start_offset);
		अगर (WARN_ON(*(अक्षर *)ip != 0x75))
			जाओ fail;
		ret = copy_from_kernel_nofault(ip, x86_nops[2], 2);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	/*
	 * The address of the ftrace_ops that is used क्रम this trampoline
	 * is stored at the end of the trampoline. This will be used to
	 * load the third parameter क्रम the callback. Basically, that
	 * location at the end of the trampoline takes the place of
	 * the global function_trace_op variable.
	 */

	ptr = (अचिन्हित दीर्घ *)(trampoline + size + RET_SIZE);
	*ptr = (अचिन्हित दीर्घ)ops;

	op_offset -= start_offset;
	स_नकल(&op_ptr, trampoline + op_offset, OP_REF_SIZE);

	/* Are we poपूर्णांकing to the reference? */
	अगर (WARN_ON(स_भेद(op_ptr.op, op_ref, 3) != 0))
		जाओ fail;

	/* Load the contents of ptr पूर्णांकo the callback parameter */
	offset = (अचिन्हित दीर्घ)ptr;
	offset -= (अचिन्हित दीर्घ)trampoline + op_offset + OP_REF_SIZE;

	op_ptr.offset = offset;

	/* put in the new offset to the ftrace_ops */
	स_नकल(trampoline + op_offset, &op_ptr, OP_REF_SIZE);

	/* put in the call to the function */
	mutex_lock(&text_mutex);
	call_offset -= start_offset;
	स_नकल(trampoline + call_offset,
	       text_gen_insn(CALL_INSN_OPCODE,
			     trampoline + call_offset,
			     ftrace_ops_get_func(ops)), CALL_INSN_SIZE);
	mutex_unlock(&text_mutex);

	/* ALLOC_TRAMP flags lets us know we created it */
	ops->flags |= FTRACE_OPS_FL_ALLOC_TRAMP;

	set_vm_flush_reset_perms(trampoline);

	अगर (likely(प्रणाली_state != SYSTEM_BOOTING))
		set_memory_ro((अचिन्हित दीर्घ)trampoline, npages);
	set_memory_x((अचिन्हित दीर्घ)trampoline, npages);
	वापस (अचिन्हित दीर्घ)trampoline;
fail:
	tramp_मुक्त(trampoline);
	वापस 0;
पूर्ण

व्योम set_ftrace_ops_ro(व्योम)
अणु
	काष्ठा ftrace_ops *ops;
	अचिन्हित दीर्घ start_offset;
	अचिन्हित दीर्घ end_offset;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;

	करो_क्रम_each_ftrace_op(ops, ftrace_ops_list) अणु
		अगर (!(ops->flags & FTRACE_OPS_FL_ALLOC_TRAMP))
			जारी;

		अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS) अणु
			start_offset = (अचिन्हित दीर्घ)ftrace_regs_caller;
			end_offset = (अचिन्हित दीर्घ)ftrace_regs_caller_end;
		पूर्ण अन्यथा अणु
			start_offset = (अचिन्हित दीर्घ)ftrace_caller;
			end_offset = (अचिन्हित दीर्घ)ftrace_caller_end;
		पूर्ण
		size = end_offset - start_offset;
		size = size + RET_SIZE + माप(व्योम *);
		npages = DIV_ROUND_UP(size, PAGE_SIZE);
		set_memory_ro((अचिन्हित दीर्घ)ops->trampoline, npages);
	पूर्ण जबतक_क्रम_each_ftrace_op(ops);
पूर्ण

अटल अचिन्हित दीर्घ calc_trampoline_call_offset(bool save_regs)
अणु
	अचिन्हित दीर्घ start_offset;
	अचिन्हित दीर्घ call_offset;

	अगर (save_regs) अणु
		start_offset = (अचिन्हित दीर्घ)ftrace_regs_caller;
		call_offset = (अचिन्हित दीर्घ)ftrace_regs_call;
	पूर्ण अन्यथा अणु
		start_offset = (अचिन्हित दीर्घ)ftrace_caller;
		call_offset = (अचिन्हित दीर्घ)ftrace_call;
	पूर्ण

	वापस call_offset - start_offset;
पूर्ण

व्योम arch_ftrace_update_trampoline(काष्ठा ftrace_ops *ops)
अणु
	ftrace_func_t func;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ ip;
	अचिन्हित पूर्णांक size;
	स्थिर अक्षर *new;

	अगर (!ops->trampoline) अणु
		ops->trampoline = create_trampoline(ops, &size);
		अगर (!ops->trampoline)
			वापस;
		ops->trampoline_size = size;
		वापस;
	पूर्ण

	/*
	 * The ftrace_ops caller may set up its own trampoline.
	 * In such a हाल, this code must not modअगरy it.
	 */
	अगर (!(ops->flags & FTRACE_OPS_FL_ALLOC_TRAMP))
		वापस;

	offset = calc_trampoline_call_offset(ops->flags & FTRACE_OPS_FL_SAVE_REGS);
	ip = ops->trampoline + offset;
	func = ftrace_ops_get_func(ops);

	mutex_lock(&text_mutex);
	/* Do a safe modअगरy in हाल the trampoline is executing */
	new = ftrace_call_replace(ip, (अचिन्हित दीर्घ)func);
	text_poke_bp((व्योम *)ip, new, MCOUNT_INSN_SIZE, शून्य);
	mutex_unlock(&text_mutex);
पूर्ण

/* Return the address of the function the trampoline calls */
अटल व्योम *addr_from_call(व्योम *ptr)
अणु
	जोड़ text_poke_insn call;
	पूर्णांक ret;

	ret = copy_from_kernel_nofault(&call, ptr, CALL_INSN_SIZE);
	अगर (WARN_ON_ONCE(ret < 0))
		वापस शून्य;

	/* Make sure this is a call */
	अगर (WARN_ON_ONCE(call.opcode != CALL_INSN_OPCODE)) अणु
		pr_warn("Expected E8, got %x\n", call.opcode);
		वापस शून्य;
	पूर्ण

	वापस ptr + CALL_INSN_SIZE + call.disp;
पूर्ण

व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ self_addr, अचिन्हित दीर्घ *parent,
			   अचिन्हित दीर्घ frame_poपूर्णांकer);

/*
 * If the ops->trampoline was not allocated, then it probably
 * has a अटल trampoline func, or is the ftrace caller itself.
 */
अटल व्योम *अटल_tramp_func(काष्ठा ftrace_ops *ops, काष्ठा dyn_ftrace *rec)
अणु
	अचिन्हित दीर्घ offset;
	bool save_regs = rec->flags & FTRACE_FL_REGS_EN;
	व्योम *ptr;

	अगर (ops && ops->trampoline) अणु
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
		/*
		 * We only know about function graph tracer setting as अटल
		 * trampoline.
		 */
		अगर (ops->trampoline == FTRACE_GRAPH_ADDR)
			वापस (व्योम *)prepare_ftrace_वापस;
#पूर्ण_अगर
		वापस शून्य;
	पूर्ण

	offset = calc_trampoline_call_offset(save_regs);

	अगर (save_regs)
		ptr = (व्योम *)FTRACE_REGS_ADDR + offset;
	अन्यथा
		ptr = (व्योम *)FTRACE_ADDR + offset;

	वापस addr_from_call(ptr);
पूर्ण

व्योम *arch_ftrace_trampoline_func(काष्ठा ftrace_ops *ops, काष्ठा dyn_ftrace *rec)
अणु
	अचिन्हित दीर्घ offset;

	/* If we didn't allocate this trampoline, consider it अटल */
	अगर (!ops || !(ops->flags & FTRACE_OPS_FL_ALLOC_TRAMP))
		वापस अटल_tramp_func(ops, rec);

	offset = calc_trampoline_call_offset(ops->flags & FTRACE_OPS_FL_SAVE_REGS);
	वापस addr_from_call((व्योम *)ops->trampoline + offset);
पूर्ण

व्योम arch_ftrace_trampoline_मुक्त(काष्ठा ftrace_ops *ops)
अणु
	अगर (!ops || !(ops->flags & FTRACE_OPS_FL_ALLOC_TRAMP))
		वापस;

	tramp_मुक्त((व्योम *)ops->trampoline);
	ops->trampoline = 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_64 */
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य व्योम ftrace_graph_call(व्योम);

अटल स्थिर अक्षर *ftrace_jmp_replace(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	वापस text_gen_insn(JMP32_INSN_OPCODE, (व्योम *)ip, (व्योम *)addr);
पूर्ण

अटल पूर्णांक ftrace_mod_jmp(अचिन्हित दीर्घ ip, व्योम *func)
अणु
	स्थिर अक्षर *new;

	new = ftrace_jmp_replace(ip, (अचिन्हित दीर्घ)func);
	text_poke_bp((व्योम *)ip, new, MCOUNT_INSN_SIZE, शून्य);
	वापस 0;
पूर्ण

पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_graph_call);

	वापस ftrace_mod_jmp(ip, &ftrace_graph_caller);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_graph_call);

	वापस ftrace_mod_jmp(ip, &ftrace_stub);
पूर्ण

#पूर्ण_अगर /* !CONFIG_DYNAMIC_FTRACE */

/*
 * Hook the वापस address and push it in the stack of वापस addrs
 * in current thपढ़ो info.
 */
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ self_addr, अचिन्हित दीर्घ *parent,
			   अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ)&वापस_to_handler;
	अचिन्हित दीर्घ old;
	पूर्णांक faulted;

	/*
	 * When resuming from suspend-to-ram, this function can be indirectly
	 * called from early CPU startup code जबतक the CPU is in real mode,
	 * which would fail miserably.  Make sure the stack poपूर्णांकer is a
	 * भव address.
	 *
	 * This check isn't as accurate as virt_addr_valid(), but it should be
	 * good enough क्रम this purpose, and it's fast.
	 */
	अगर (unlikely((दीर्घ)__builtin_frame_address(0) >= 0))
		वापस;

	अगर (unlikely(ftrace_graph_is_dead()))
		वापस;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	/*
	 * Protect against fault, even अगर it shouldn't
	 * happen. This tool is too much पूर्णांकrusive to
	 * ignore such a protection.
	 */
	यंत्र अस्थिर(
		"1: " _ASM_MOV " (%[parent]), %[old]\n"
		"2: " _ASM_MOV " %[return_hooker], (%[parent])\n"
		"   movl $0, %[faulted]\n"
		"3:\n"

		".section .fixup, \"ax\"\n"
		"4: movl $1, %[faulted]\n"
		"   jmp 3b\n"
		".previous\n"

		_ASM_EXTABLE(1b, 4b)
		_ASM_EXTABLE(2b, 4b)

		: [old] "=&r" (old), [faulted] "=r" (faulted)
		: [parent] "r" (parent), [वापस_hooker] "r" (वापस_hooker)
		: "memory"
	);

	अगर (unlikely(faulted)) अणु
		ftrace_graph_stop();
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (function_graph_enter(old, self_addr, frame_poपूर्णांकer, parent))
		*parent = old;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */
