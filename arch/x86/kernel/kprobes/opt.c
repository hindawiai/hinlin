<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Kernel Probes Jump Optimization (Optprobes)
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 * Copyright (C) Hitachi Ltd., 2012
 */
#समावेश <linux/kprobes.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/preempt.h>
#समावेश <linux/extable.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/objtool.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/अटल_call.h>

#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/desc.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/nospec-branch.h>

#समावेश "common.h"

अचिन्हित दीर्घ __recover_optprobed_insn(kprobe_opcode_t *buf, अचिन्हित दीर्घ addr)
अणु
	काष्ठा optimized_kprobe *op;
	काष्ठा kprobe *kp;
	दीर्घ offs;
	पूर्णांक i;

	क्रम (i = 0; i < JMP32_INSN_SIZE; i++) अणु
		kp = get_kprobe((व्योम *)addr - i);
		/* This function only handles jump-optimized kprobe */
		अगर (kp && kprobe_optimized(kp)) अणु
			op = container_of(kp, काष्ठा optimized_kprobe, kp);
			/* If op->list is not empty, op is under optimizing */
			अगर (list_empty(&op->list))
				जाओ found;
		पूर्ण
	पूर्ण

	वापस addr;
found:
	/*
	 * If the kprobe can be optimized, original bytes which can be
	 * overwritten by jump destination address. In this हाल, original
	 * bytes must be recovered from op->optinsn.copied_insn buffer.
	 */
	अगर (copy_from_kernel_nofault(buf, (व्योम *)addr,
		MAX_INSN_SIZE * माप(kprobe_opcode_t)))
		वापस 0UL;

	अगर (addr == (अचिन्हित दीर्घ)kp->addr) अणु
		buf[0] = kp->opcode;
		स_नकल(buf + 1, op->optinsn.copied_insn, DISP32_SIZE);
	पूर्ण अन्यथा अणु
		offs = addr - (अचिन्हित दीर्घ)kp->addr - 1;
		स_नकल(buf, op->optinsn.copied_insn + offs, DISP32_SIZE - offs);
	पूर्ण

	वापस (अचिन्हित दीर्घ)buf;
पूर्ण

अटल व्योम synthesize_clac(kprobe_opcode_t *addr)
अणु
	/*
	 * Can't be अटल_cpu_has() due to how objtool treats this feature bit.
	 * This isn't a fast path anyway.
	 */
	अगर (!boot_cpu_has(X86_FEATURE_SMAP))
		वापस;

	/* Replace the NOP3 with CLAC */
	addr[0] = 0x0f;
	addr[1] = 0x01;
	addr[2] = 0xca;
पूर्ण

/* Insert a move inकाष्ठाion which sets a poपूर्णांकer to eax/rdi (1st arg). */
अटल व्योम synthesize_set_arg1(kprobe_opcode_t *addr, अचिन्हित दीर्घ val)
अणु
#अगर_घोषित CONFIG_X86_64
	*addr++ = 0x48;
	*addr++ = 0xbf;
#अन्यथा
	*addr++ = 0xb8;
#पूर्ण_अगर
	*(अचिन्हित दीर्घ *)addr = val;
पूर्ण

यंत्र (
			".pushsection .rodata\n"
			"optprobe_template_func:\n"
			".global optprobe_template_entry\n"
			"optprobe_template_entry:\n"
#अगर_घोषित CONFIG_X86_64
			/* We करोn't bother saving the ss रेजिस्टर */
			"	pushq %rsp\n"
			"	pushfq\n"
			".global optprobe_template_clac\n"
			"optprobe_template_clac:\n"
			ASM_NOP3
			SAVE_REGS_STRING
			"	movq %rsp, %rsi\n"
			".global optprobe_template_val\n"
			"optprobe_template_val:\n"
			ASM_NOP5
			ASM_NOP5
			".global optprobe_template_call\n"
			"optprobe_template_call:\n"
			ASM_NOP5
			/* Move flags to rsp */
			"	movq 18*8(%rsp), %rdx\n"
			"	movq %rdx, 19*8(%rsp)\n"
			RESTORE_REGS_STRING
			/* Skip flags entry */
			"	addq $8, %rsp\n"
			"	popfq\n"
#अन्यथा /* CONFIG_X86_32 */
			"	pushl %esp\n"
			"	pushfl\n"
			".global optprobe_template_clac\n"
			"optprobe_template_clac:\n"
			ASM_NOP3
			SAVE_REGS_STRING
			"	movl %esp, %edx\n"
			".global optprobe_template_val\n"
			"optprobe_template_val:\n"
			ASM_NOP5
			".global optprobe_template_call\n"
			"optprobe_template_call:\n"
			ASM_NOP5
			/* Move flags पूर्णांकo esp */
			"	movl 14*4(%esp), %edx\n"
			"	movl %edx, 15*4(%esp)\n"
			RESTORE_REGS_STRING
			/* Skip flags entry */
			"	addl $4, %esp\n"
			"	popfl\n"
#पूर्ण_अगर
			".global optprobe_template_end\n"
			"optprobe_template_end:\n"
			".popsection\n");

व्योम optprobe_ढाँचा_func(व्योम);
STACK_FRAME_NON_STANDARD(optprobe_ढाँचा_func);

#घोषणा TMPL_CLAC_IDX \
	((दीर्घ)optprobe_ढाँचा_clac - (दीर्घ)optprobe_ढाँचा_entry)
#घोषणा TMPL_MOVE_IDX \
	((दीर्घ)optprobe_ढाँचा_val - (दीर्घ)optprobe_ढाँचा_entry)
#घोषणा TMPL_CALL_IDX \
	((दीर्घ)optprobe_ढाँचा_call - (दीर्घ)optprobe_ढाँचा_entry)
#घोषणा TMPL_END_IDX \
	((दीर्घ)optprobe_ढाँचा_end - (दीर्घ)optprobe_ढाँचा_entry)

/* Optimized kprobe call back function: called from optinsn */
अटल व्योम
optimized_callback(काष्ठा optimized_kprobe *op, काष्ठा pt_regs *regs)
अणु
	/* This is possible अगर op is under delayed unoptimizing */
	अगर (kprobe_disabled(&op->kp))
		वापस;

	preempt_disable();
	अगर (kprobe_running()) अणु
		kprobes_inc_nmissed_count(&op->kp);
	पूर्ण अन्यथा अणु
		काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();
		/* Save skipped रेजिस्टरs */
		regs->cs = __KERNEL_CS;
#अगर_घोषित CONFIG_X86_32
		regs->gs = 0;
#पूर्ण_अगर
		regs->ip = (अचिन्हित दीर्घ)op->kp.addr + INT3_INSN_SIZE;
		regs->orig_ax = ~0UL;

		__this_cpu_ग_लिखो(current_kprobe, &op->kp);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;
		opt_pre_handler(&op->kp, regs);
		__this_cpu_ग_लिखो(current_kprobe, शून्य);
	पूर्ण
	preempt_enable();
पूर्ण
NOKPROBE_SYMBOL(optimized_callback);

अटल पूर्णांक copy_optimized_inकाष्ठाions(u8 *dest, u8 *src, u8 *real)
अणु
	काष्ठा insn insn;
	पूर्णांक len = 0, ret;

	जबतक (len < JMP32_INSN_SIZE) अणु
		ret = __copy_inकाष्ठाion(dest + len, src + len, real + len, &insn);
		अगर (!ret || !can_boost(&insn, src + len))
			वापस -EINVAL;
		len += ret;
	पूर्ण
	/* Check whether the address range is reserved */
	अगर (ftrace_text_reserved(src, src + len - 1) ||
	    alternatives_text_reserved(src, src + len - 1) ||
	    jump_label_text_reserved(src, src + len - 1) ||
	    अटल_call_text_reserved(src, src + len - 1))
		वापस -EBUSY;

	वापस len;
पूर्ण

/* Check whether insn is indirect jump */
अटल पूर्णांक __insn_is_indirect_jump(काष्ठा insn *insn)
अणु
	वापस ((insn->opcode.bytes[0] == 0xff &&
		(X86_MODRM_REG(insn->modrm.value) & 6) == 4) || /* Jump */
		insn->opcode.bytes[0] == 0xea);	/* Segment based jump */
पूर्ण

/* Check whether insn jumps पूर्णांकo specअगरied address range */
अटल पूर्णांक insn_jump_पूर्णांकo_range(काष्ठा insn *insn, अचिन्हित दीर्घ start, पूर्णांक len)
अणु
	अचिन्हित दीर्घ target = 0;

	चयन (insn->opcode.bytes[0]) अणु
	हाल 0xe0:	/* loopne */
	हाल 0xe1:	/* loope */
	हाल 0xe2:	/* loop */
	हाल 0xe3:	/* jcxz */
	हाल 0xe9:	/* near relative jump */
	हाल 0xeb:	/* लघु relative jump */
		अवरोध;
	हाल 0x0f:
		अगर ((insn->opcode.bytes[1] & 0xf0) == 0x80) /* jcc near */
			अवरोध;
		वापस 0;
	शेष:
		अगर ((insn->opcode.bytes[0] & 0xf0) == 0x70) /* jcc लघु */
			अवरोध;
		वापस 0;
	पूर्ण
	target = (अचिन्हित दीर्घ)insn->next_byte + insn->immediate.value;

	वापस (start <= target && target <= start + len);
पूर्ण

अटल पूर्णांक insn_is_indirect_jump(काष्ठा insn *insn)
अणु
	पूर्णांक ret = __insn_is_indirect_jump(insn);

#अगर_घोषित CONFIG_RETPOLINE
	/*
	 * Jump to x86_indirect_thunk_* is treated as an indirect jump.
	 * Note that even with CONFIG_RETPOLINE=y, the kernel compiled with
	 * older gcc may use indirect jump. So we add this check instead of
	 * replace indirect-jump check.
	 */
	अगर (!ret)
		ret = insn_jump_पूर्णांकo_range(insn,
				(अचिन्हित दीर्घ)__indirect_thunk_start,
				(अचिन्हित दीर्घ)__indirect_thunk_end -
				(अचिन्हित दीर्घ)__indirect_thunk_start);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल bool is_padding_पूर्णांक3(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ eaddr)
अणु
	अचिन्हित अक्षर ops;

	क्रम (; addr < eaddr; addr++) अणु
		अगर (get_kernel_nofault(ops, (व्योम *)addr) < 0 ||
		    ops != INT3_INSN_OPCODE)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Decode whole function to ensure any inकाष्ठाions करोn't jump पूर्णांकo target */
अटल पूर्णांक can_optimize(अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित दीर्घ addr, size = 0, offset = 0;
	काष्ठा insn insn;
	kprobe_opcode_t buf[MAX_INSN_SIZE];

	/* Lookup symbol including addr */
	अगर (!kallsyms_lookup_size_offset(paddr, &size, &offset))
		वापस 0;

	/*
	 * Do not optimize in the entry code due to the unstable
	 * stack handling and रेजिस्टरs setup.
	 */
	अगर (((paddr >= (अचिन्हित दीर्घ)__entry_text_start) &&
	     (paddr <  (अचिन्हित दीर्घ)__entry_text_end)))
		वापस 0;

	/* Check there is enough space क्रम a relative jump. */
	अगर (size - offset < JMP32_INSN_SIZE)
		वापस 0;

	/* Decode inकाष्ठाions */
	addr = paddr - offset;
	जबतक (addr < paddr - offset + size) अणु /* Decode until function end */
		अचिन्हित दीर्घ recovered_insn;
		पूर्णांक ret;

		अगर (search_exception_tables(addr))
			/*
			 * Since some fixup code will jumps पूर्णांकo this function,
			 * we can't optimize kprobe in this function.
			 */
			वापस 0;
		recovered_insn = recover_probed_inकाष्ठाion(buf, addr);
		अगर (!recovered_insn)
			वापस 0;

		ret = insn_decode_kernel(&insn, (व्योम *)recovered_insn);
		अगर (ret < 0)
			वापस 0;

		/*
		 * In the हाल of detecting unknown अवरोधpoपूर्णांक, this could be
		 * a padding INT3 between functions. Let's check that all the
		 * rest of the bytes are also INT3.
		 */
		अगर (insn.opcode.bytes[0] == INT3_INSN_OPCODE)
			वापस is_padding_पूर्णांक3(addr, paddr - offset + size) ? 1 : 0;

		/* Recover address */
		insn.kaddr = (व्योम *)addr;
		insn.next_byte = (व्योम *)(addr + insn.length);
		/* Check any inकाष्ठाions करोn't jump पूर्णांकo target */
		अगर (insn_is_indirect_jump(&insn) ||
		    insn_jump_पूर्णांकo_range(&insn, paddr + INT3_INSN_SIZE,
					 DISP32_SIZE))
			वापस 0;
		addr += insn.length;
	पूर्ण

	वापस 1;
पूर्ण

/* Check optimized_kprobe can actually be optimized. */
पूर्णांक arch_check_optimized_kprobe(काष्ठा optimized_kprobe *op)
अणु
	पूर्णांक i;
	काष्ठा kprobe *p;

	क्रम (i = 1; i < op->optinsn.size; i++) अणु
		p = get_kprobe(op->kp.addr + i);
		अगर (p && !kprobe_disabled(p))
			वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

/* Check the addr is within the optimized inकाष्ठाions. */
पूर्णांक arch_within_optimized_kprobe(काष्ठा optimized_kprobe *op,
				 अचिन्हित दीर्घ addr)
अणु
	वापस ((अचिन्हित दीर्घ)op->kp.addr <= addr &&
		(अचिन्हित दीर्घ)op->kp.addr + op->optinsn.size > addr);
पूर्ण

/* Free optimized inकाष्ठाion slot */
अटल
व्योम __arch_हटाओ_optimized_kprobe(काष्ठा optimized_kprobe *op, पूर्णांक dirty)
अणु
	u8 *slot = op->optinsn.insn;
	अगर (slot) अणु
		पूर्णांक len = TMPL_END_IDX + op->optinsn.size + JMP32_INSN_SIZE;

		/* Record the perf event beक्रमe मुक्तing the slot */
		अगर (dirty)
			perf_event_text_poke(slot, slot, len, शून्य, 0);

		मुक्त_optinsn_slot(slot, dirty);
		op->optinsn.insn = शून्य;
		op->optinsn.size = 0;
	पूर्ण
पूर्ण

व्योम arch_हटाओ_optimized_kprobe(काष्ठा optimized_kprobe *op)
अणु
	__arch_हटाओ_optimized_kprobe(op, 1);
पूर्ण

/*
 * Copy replacing target inकाष्ठाions
 * Target inकाष्ठाions MUST be relocatable (checked inside)
 * This is called when new aggr(opt)probe is allocated or reused.
 */
पूर्णांक arch_prepare_optimized_kprobe(काष्ठा optimized_kprobe *op,
				  काष्ठा kprobe *__unused)
अणु
	u8 *buf = शून्य, *slot;
	पूर्णांक ret, len;
	दीर्घ rel;

	अगर (!can_optimize((अचिन्हित दीर्घ)op->kp.addr))
		वापस -EILSEQ;

	buf = kzalloc(MAX_OPTINSN_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	op->optinsn.insn = slot = get_optinsn_slot();
	अगर (!slot) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Verअगरy अगर the address gap is in 2GB range, because this uses
	 * a relative jump.
	 */
	rel = (दीर्घ)slot - (दीर्घ)op->kp.addr + JMP32_INSN_SIZE;
	अगर (असल(rel) > 0x7fffffff) अणु
		ret = -दुस्फल;
		जाओ err;
	पूर्ण

	/* Copy arch-dep-instance from ढाँचा */
	स_नकल(buf, optprobe_ढाँचा_entry, TMPL_END_IDX);

	/* Copy inकाष्ठाions पूर्णांकo the out-of-line buffer */
	ret = copy_optimized_inकाष्ठाions(buf + TMPL_END_IDX, op->kp.addr,
					  slot + TMPL_END_IDX);
	अगर (ret < 0)
		जाओ err;
	op->optinsn.size = ret;
	len = TMPL_END_IDX + op->optinsn.size;

	synthesize_clac(buf + TMPL_CLAC_IDX);

	/* Set probe inक्रमmation */
	synthesize_set_arg1(buf + TMPL_MOVE_IDX, (अचिन्हित दीर्घ)op);

	/* Set probe function call */
	synthesize_relcall(buf + TMPL_CALL_IDX,
			   slot + TMPL_CALL_IDX, optimized_callback);

	/* Set वापसing jmp inकाष्ठाion at the tail of out-of-line buffer */
	synthesize_reljump(buf + len, slot + len,
			   (u8 *)op->kp.addr + op->optinsn.size);
	len += JMP32_INSN_SIZE;

	/*
	 * Note	len = TMPL_END_IDX + op->optinsn.size + JMP32_INSN_SIZE is also
	 * used in __arch_हटाओ_optimized_kprobe().
	 */

	/* We have to use text_poke() क्रम inकाष्ठाion buffer because it is RO */
	perf_event_text_poke(slot, शून्य, 0, buf, len);
	text_poke(slot, buf, len);

	ret = 0;
out:
	kमुक्त(buf);
	वापस ret;

err:
	__arch_हटाओ_optimized_kprobe(op, 0);
	जाओ out;
पूर्ण

/*
 * Replace अवरोधpoपूर्णांकs (INT3) with relative jumps (JMP.d32).
 * Caller must call with locking kprobe_mutex and text_mutex.
 *
 * The caller will have installed a regular kprobe and after that issued
 * syncrhonize_rcu_tasks(), this ensures that the inकाष्ठाion(s) that live in
 * the 4 bytes after the INT3 are unused and can now be overwritten.
 */
व्योम arch_optimize_kprobes(काष्ठा list_head *oplist)
अणु
	काष्ठा optimized_kprobe *op, *पंचांगp;
	u8 insn_buff[JMP32_INSN_SIZE];

	list_क्रम_each_entry_safe(op, पंचांगp, oplist, list) अणु
		s32 rel = (s32)((दीर्घ)op->optinsn.insn -
			((दीर्घ)op->kp.addr + JMP32_INSN_SIZE));

		WARN_ON(kprobe_disabled(&op->kp));

		/* Backup inकाष्ठाions which will be replaced by jump address */
		स_नकल(op->optinsn.copied_insn, op->kp.addr + INT3_INSN_SIZE,
		       DISP32_SIZE);

		insn_buff[0] = JMP32_INSN_OPCODE;
		*(s32 *)(&insn_buff[1]) = rel;

		text_poke_bp(op->kp.addr, insn_buff, JMP32_INSN_SIZE, शून्य);

		list_del_init(&op->list);
	पूर्ण
पूर्ण

/*
 * Replace a relative jump (JMP.d32) with a अवरोधpoपूर्णांक (INT3).
 *
 * After that, we can restore the 4 bytes after the INT3 to unकरो what
 * arch_optimize_kprobes() scribbled. This is safe since those bytes will be
 * unused once the INT3 lands.
 */
व्योम arch_unoptimize_kprobe(काष्ठा optimized_kprobe *op)
अणु
	u8 new[JMP32_INSN_SIZE] = अणु INT3_INSN_OPCODE, पूर्ण;
	u8 old[JMP32_INSN_SIZE];
	u8 *addr = op->kp.addr;

	स_नकल(old, op->kp.addr, JMP32_INSN_SIZE);
	स_नकल(new + INT3_INSN_SIZE,
	       op->optinsn.copied_insn,
	       JMP32_INSN_SIZE - INT3_INSN_SIZE);

	text_poke(addr, new, INT3_INSN_SIZE);
	text_poke_sync();
	text_poke(addr + INT3_INSN_SIZE,
		  new + INT3_INSN_SIZE,
		  JMP32_INSN_SIZE - INT3_INSN_SIZE);
	text_poke_sync();

	perf_event_text_poke(op->kp.addr, old, JMP32_INSN_SIZE, new, JMP32_INSN_SIZE);
पूर्ण

/*
 * Recover original inकाष्ठाions and अवरोधpoपूर्णांकs from relative jumps.
 * Caller must call with locking kprobe_mutex.
 */
बाह्य व्योम arch_unoptimize_kprobes(काष्ठा list_head *oplist,
				    काष्ठा list_head *करोne_list)
अणु
	काष्ठा optimized_kprobe *op, *पंचांगp;

	list_क्रम_each_entry_safe(op, पंचांगp, oplist, list) अणु
		arch_unoptimize_kprobe(op);
		list_move(&op->list, करोne_list);
	पूर्ण
पूर्ण

पूर्णांक setup_detour_execution(काष्ठा kprobe *p, काष्ठा pt_regs *regs, पूर्णांक reenter)
अणु
	काष्ठा optimized_kprobe *op;

	अगर (p->flags & KPROBE_FLAG_OPTIMIZED) अणु
		/* This kprobe is really able to run optimized path. */
		op = container_of(p, काष्ठा optimized_kprobe, kp);
		/* Detour through copied inकाष्ठाions */
		regs->ip = (अचिन्हित दीर्घ)op->optinsn.insn + TMPL_END_IDX;
		अगर (!reenter)
			reset_current_kprobe();
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(setup_detour_execution);
