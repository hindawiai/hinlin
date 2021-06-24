<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/kernel/unwind.c
 *
 * Copyright (C) 2008 ARM Limited
 *
 * Stack unwinding support क्रम ARM
 *
 * An ARM EABI version of gcc is required to generate the unwind
 * tables. For inक्रमmation about the काष्ठाure of the unwind tables,
 * see "Exception Handling ABI for the ARM Architecture" at:
 *
 * http://infocenter.arm.com/help/topic/com.arm.करोc.subset.swdev.abi/index.hपंचांगl
 */

#अगर_अघोषित __CHECKER__
#अगर !defined (__ARM_EABI__)
#warning Your compiler करोes not have EABI support.
#warning    ARM unwind is known to compile only with EABI compilers.
#warning    Change compiler or disable ARM_UNWIND option.
#पूर्ण_अगर
#पूर्ण_अगर /* __CHECKER__ */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>

#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/unwind.h>

/* Dummy functions to aव्योम linker complaपूर्णांकs */
व्योम __aeabi_unwind_cpp_pr0(व्योम)
अणु
पूर्ण;
EXPORT_SYMBOL(__aeabi_unwind_cpp_pr0);

व्योम __aeabi_unwind_cpp_pr1(व्योम)
अणु
पूर्ण;
EXPORT_SYMBOL(__aeabi_unwind_cpp_pr1);

व्योम __aeabi_unwind_cpp_pr2(व्योम)
अणु
पूर्ण;
EXPORT_SYMBOL(__aeabi_unwind_cpp_pr2);

काष्ठा unwind_ctrl_block अणु
	अचिन्हित दीर्घ vrs[16];		/* भव रेजिस्टर set */
	स्थिर अचिन्हित दीर्घ *insn;	/* poपूर्णांकer to the current inकाष्ठाions word */
	अचिन्हित दीर्घ sp_high;		/* highest value of sp allowed */
	/*
	 * 1 : check क्रम stack overflow क्रम each रेजिस्टर pop.
	 * 0 : save overhead अगर there is plenty of stack reमुख्यing.
	 */
	पूर्णांक check_each_pop;
	पूर्णांक entries;			/* number of entries left to पूर्णांकerpret */
	पूर्णांक byte;			/* current byte number in the inकाष्ठाions word */
पूर्ण;

क्रमागत regs अणु
#अगर_घोषित CONFIG_THUMB2_KERNEL
	FP = 7,
#अन्यथा
	FP = 11,
#पूर्ण_अगर
	SP = 13,
	LR = 14,
	PC = 15
पूर्ण;

बाह्य स्थिर काष्ठा unwind_idx __start_unwind_idx[];
अटल स्थिर काष्ठा unwind_idx *__origin_unwind_idx;
बाह्य स्थिर काष्ठा unwind_idx __stop_unwind_idx[];

अटल DEFINE_RAW_SPINLOCK(unwind_lock);
अटल LIST_HEAD(unwind_tables);

/* Convert a prel31 symbol to an असलolute address */
#घोषणा prel31_to_addr(ptr)				\
(अणु							\
	/* sign-extend to 32 bits */			\
	दीर्घ offset = (((दीर्घ)*(ptr)) << 1) >> 1;	\
	(अचिन्हित दीर्घ)(ptr) + offset;			\
पूर्ण)

/*
 * Binary search in the unwind index. The entries are
 * guaranteed to be sorted in ascending order by the linker.
 *
 * start = first entry
 * origin = first entry with positive offset (or stop अगर there is no such entry)
 * stop - 1 = last entry
 */
अटल स्थिर काष्ठा unwind_idx *search_index(अचिन्हित दीर्घ addr,
				       स्थिर काष्ठा unwind_idx *start,
				       स्थिर काष्ठा unwind_idx *origin,
				       स्थिर काष्ठा unwind_idx *stop)
अणु
	अचिन्हित दीर्घ addr_prel31;

	pr_debug("%s(%08lx, %p, %p, %p)\n",
			__func__, addr, start, origin, stop);

	/*
	 * only search in the section with the matching sign. This way the
	 * prel31 numbers can be compared as अचिन्हित दीर्घs.
	 */
	अगर (addr < (अचिन्हित दीर्घ)start)
		/* negative offsets: [start; origin) */
		stop = origin;
	अन्यथा
		/* positive offsets: [origin; stop) */
		start = origin;

	/* prel31 क्रम address relavive to start */
	addr_prel31 = (addr - (अचिन्हित दीर्घ)start) & 0x7fffffff;

	जबतक (start < stop - 1) अणु
		स्थिर काष्ठा unwind_idx *mid = start + ((stop - start) >> 1);

		/*
		 * As addr_prel31 is relative to start an offset is needed to
		 * make it relative to mid.
		 */
		अगर (addr_prel31 - ((अचिन्हित दीर्घ)mid - (अचिन्हित दीर्घ)start) <
				mid->addr_offset)
			stop = mid;
		अन्यथा अणु
			/* keep addr_prel31 relative to start */
			addr_prel31 -= ((अचिन्हित दीर्घ)mid -
					(अचिन्हित दीर्घ)start);
			start = mid;
		पूर्ण
	पूर्ण

	अगर (likely(start->addr_offset <= addr_prel31))
		वापस start;
	अन्यथा अणु
		pr_warn("unwind: Unknown symbol address %08lx\n", addr);
		वापस शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा unwind_idx *unwind_find_origin(
		स्थिर काष्ठा unwind_idx *start, स्थिर काष्ठा unwind_idx *stop)
अणु
	pr_debug("%s(%p, %p)\n", __func__, start, stop);
	जबतक (start < stop) अणु
		स्थिर काष्ठा unwind_idx *mid = start + ((stop - start) >> 1);

		अगर (mid->addr_offset >= 0x40000000)
			/* negative offset */
			start = mid + 1;
		अन्यथा
			/* positive offset */
			stop = mid;
	पूर्ण
	pr_debug("%s -> %p\n", __func__, stop);
	वापस stop;
पूर्ण

अटल स्थिर काष्ठा unwind_idx *unwind_find_idx(अचिन्हित दीर्घ addr)
अणु
	स्थिर काष्ठा unwind_idx *idx = शून्य;
	अचिन्हित दीर्घ flags;

	pr_debug("%s(%08lx)\n", __func__, addr);

	अगर (core_kernel_text(addr)) अणु
		अगर (unlikely(!__origin_unwind_idx))
			__origin_unwind_idx =
				unwind_find_origin(__start_unwind_idx,
						__stop_unwind_idx);

		/* मुख्य unwind table */
		idx = search_index(addr, __start_unwind_idx,
				   __origin_unwind_idx,
				   __stop_unwind_idx);
	पूर्ण अन्यथा अणु
		/* module unwind tables */
		काष्ठा unwind_table *table;

		raw_spin_lock_irqsave(&unwind_lock, flags);
		list_क्रम_each_entry(table, &unwind_tables, list) अणु
			अगर (addr >= table->begin_addr &&
			    addr < table->end_addr) अणु
				idx = search_index(addr, table->start,
						   table->origin,
						   table->stop);
				/* Move-to-front to exploit common traces */
				list_move(&table->list, &unwind_tables);
				अवरोध;
			पूर्ण
		पूर्ण
		raw_spin_unlock_irqrestore(&unwind_lock, flags);
	पूर्ण

	pr_debug("%s: idx = %p\n", __func__, idx);
	वापस idx;
पूर्ण

अटल अचिन्हित दीर्घ unwind_get_byte(काष्ठा unwind_ctrl_block *ctrl)
अणु
	अचिन्हित दीर्घ ret;

	अगर (ctrl->entries <= 0) अणु
		pr_warn("unwind: Corrupt unwind table\n");
		वापस 0;
	पूर्ण

	ret = (*ctrl->insn >> (ctrl->byte * 8)) & 0xff;

	अगर (ctrl->byte == 0) अणु
		ctrl->insn++;
		ctrl->entries--;
		ctrl->byte = 3;
	पूर्ण अन्यथा
		ctrl->byte--;

	वापस ret;
पूर्ण

/* Beक्रमe poping a रेजिस्टर check whether it is feasible or not */
अटल पूर्णांक unwind_pop_रेजिस्टर(काष्ठा unwind_ctrl_block *ctrl,
				अचिन्हित दीर्घ **vsp, अचिन्हित पूर्णांक reg)
अणु
	अगर (unlikely(ctrl->check_each_pop))
		अगर (*vsp >= (अचिन्हित दीर्घ *)ctrl->sp_high)
			वापस -URC_FAILURE;

	/* Use READ_ONCE_NOCHECK here to aव्योम this memory access
	 * from being tracked by KASAN.
	 */
	ctrl->vrs[reg] = READ_ONCE_NOCHECK(*(*vsp));
	(*vsp)++;
	वापस URC_OK;
पूर्ण

/* Helper functions to execute the inकाष्ठाions */
अटल पूर्णांक unwind_exec_pop_subset_r4_to_r13(काष्ठा unwind_ctrl_block *ctrl,
						अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ *vsp = (अचिन्हित दीर्घ *)ctrl->vrs[SP];
	पूर्णांक load_sp, reg = 4;

	load_sp = mask & (1 << (13 - 4));
	जबतक (mask) अणु
		अगर (mask & 1)
			अगर (unwind_pop_रेजिस्टर(ctrl, &vsp, reg))
				वापस -URC_FAILURE;
		mask >>= 1;
		reg++;
	पूर्ण
	अगर (!load_sp)
		ctrl->vrs[SP] = (अचिन्हित दीर्घ)vsp;

	वापस URC_OK;
पूर्ण

अटल पूर्णांक unwind_exec_pop_r4_to_rN(काष्ठा unwind_ctrl_block *ctrl,
					अचिन्हित दीर्घ insn)
अणु
	अचिन्हित दीर्घ *vsp = (अचिन्हित दीर्घ *)ctrl->vrs[SP];
	पूर्णांक reg;

	/* pop R4-R[4+bbb] */
	क्रम (reg = 4; reg <= 4 + (insn & 7); reg++)
		अगर (unwind_pop_रेजिस्टर(ctrl, &vsp, reg))
				वापस -URC_FAILURE;

	अगर (insn & 0x8)
		अगर (unwind_pop_रेजिस्टर(ctrl, &vsp, 14))
				वापस -URC_FAILURE;

	ctrl->vrs[SP] = (अचिन्हित दीर्घ)vsp;

	वापस URC_OK;
पूर्ण

अटल पूर्णांक unwind_exec_pop_subset_r0_to_r3(काष्ठा unwind_ctrl_block *ctrl,
						अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ *vsp = (अचिन्हित दीर्घ *)ctrl->vrs[SP];
	पूर्णांक reg = 0;

	/* pop R0-R3 according to mask */
	जबतक (mask) अणु
		अगर (mask & 1)
			अगर (unwind_pop_रेजिस्टर(ctrl, &vsp, reg))
				वापस -URC_FAILURE;
		mask >>= 1;
		reg++;
	पूर्ण
	ctrl->vrs[SP] = (अचिन्हित दीर्घ)vsp;

	वापस URC_OK;
पूर्ण

/*
 * Execute the current unwind inकाष्ठाion.
 */
अटल पूर्णांक unwind_exec_insn(काष्ठा unwind_ctrl_block *ctrl)
अणु
	अचिन्हित दीर्घ insn = unwind_get_byte(ctrl);
	पूर्णांक ret = URC_OK;

	pr_debug("%s: insn = %08lx\n", __func__, insn);

	अगर ((insn & 0xc0) == 0x00)
		ctrl->vrs[SP] += ((insn & 0x3f) << 2) + 4;
	अन्यथा अगर ((insn & 0xc0) == 0x40)
		ctrl->vrs[SP] -= ((insn & 0x3f) << 2) + 4;
	अन्यथा अगर ((insn & 0xf0) == 0x80) अणु
		अचिन्हित दीर्घ mask;

		insn = (insn << 8) | unwind_get_byte(ctrl);
		mask = insn & 0x0fff;
		अगर (mask == 0) अणु
			pr_warn("unwind: 'Refuse to unwind' instruction %04lx\n",
				insn);
			वापस -URC_FAILURE;
		पूर्ण

		ret = unwind_exec_pop_subset_r4_to_r13(ctrl, mask);
		अगर (ret)
			जाओ error;
	पूर्ण अन्यथा अगर ((insn & 0xf0) == 0x90 &&
		   (insn & 0x0d) != 0x0d)
		ctrl->vrs[SP] = ctrl->vrs[insn & 0x0f];
	अन्यथा अगर ((insn & 0xf0) == 0xa0) अणु
		ret = unwind_exec_pop_r4_to_rN(ctrl, insn);
		अगर (ret)
			जाओ error;
	पूर्ण अन्यथा अगर (insn == 0xb0) अणु
		अगर (ctrl->vrs[PC] == 0)
			ctrl->vrs[PC] = ctrl->vrs[LR];
		/* no further processing */
		ctrl->entries = 0;
	पूर्ण अन्यथा अगर (insn == 0xb1) अणु
		अचिन्हित दीर्घ mask = unwind_get_byte(ctrl);

		अगर (mask == 0 || mask & 0xf0) अणु
			pr_warn("unwind: Spare encoding %04lx\n",
				(insn << 8) | mask);
			वापस -URC_FAILURE;
		पूर्ण

		ret = unwind_exec_pop_subset_r0_to_r3(ctrl, mask);
		अगर (ret)
			जाओ error;
	पूर्ण अन्यथा अगर (insn == 0xb2) अणु
		अचिन्हित दीर्घ uleb128 = unwind_get_byte(ctrl);

		ctrl->vrs[SP] += 0x204 + (uleb128 << 2);
	पूर्ण अन्यथा अणु
		pr_warn("unwind: Unhandled instruction %02lx\n", insn);
		वापस -URC_FAILURE;
	पूर्ण

	pr_debug("%s: fp = %08lx sp = %08lx lr = %08lx pc = %08lx\n", __func__,
		 ctrl->vrs[FP], ctrl->vrs[SP], ctrl->vrs[LR], ctrl->vrs[PC]);

error:
	वापस ret;
पूर्ण

/*
 * Unwind a single frame starting with *sp क्रम the symbol at *pc. It
 * updates the *pc and *sp with the new values.
 */
पूर्णांक unwind_frame(काष्ठा stackframe *frame)
अणु
	अचिन्हित दीर्घ low;
	स्थिर काष्ठा unwind_idx *idx;
	काष्ठा unwind_ctrl_block ctrl;

	/* store the highest address on the stack to aव्योम crossing it*/
	low = frame->sp;
	ctrl.sp_high = ALIGN(low, THREAD_SIZE);

	pr_debug("%s(pc = %08lx lr = %08lx sp = %08lx)\n", __func__,
		 frame->pc, frame->lr, frame->sp);

	अगर (!kernel_text_address(frame->pc))
		वापस -URC_FAILURE;

	idx = unwind_find_idx(frame->pc);
	अगर (!idx) अणु
		pr_warn("unwind: Index not found %08lx\n", frame->pc);
		वापस -URC_FAILURE;
	पूर्ण

	ctrl.vrs[FP] = frame->fp;
	ctrl.vrs[SP] = frame->sp;
	ctrl.vrs[LR] = frame->lr;
	ctrl.vrs[PC] = 0;

	अगर (idx->insn == 1)
		/* can't unwind */
		वापस -URC_FAILURE;
	अन्यथा अगर ((idx->insn & 0x80000000) == 0)
		/* prel31 to the unwind table */
		ctrl.insn = (अचिन्हित दीर्घ *)prel31_to_addr(&idx->insn);
	अन्यथा अगर ((idx->insn & 0xff000000) == 0x80000000)
		/* only personality routine 0 supported in the index */
		ctrl.insn = &idx->insn;
	अन्यथा अणु
		pr_warn("unwind: Unsupported personality routine %08lx in the index at %p\n",
			idx->insn, idx);
		वापस -URC_FAILURE;
	पूर्ण

	/* check the personality routine */
	अगर ((*ctrl.insn & 0xff000000) == 0x80000000) अणु
		ctrl.byte = 2;
		ctrl.entries = 1;
	पूर्ण अन्यथा अगर ((*ctrl.insn & 0xff000000) == 0x81000000) अणु
		ctrl.byte = 1;
		ctrl.entries = 1 + ((*ctrl.insn & 0x00ff0000) >> 16);
	पूर्ण अन्यथा अणु
		pr_warn("unwind: Unsupported personality routine %08lx at %p\n",
			*ctrl.insn, ctrl.insn);
		वापस -URC_FAILURE;
	पूर्ण

	ctrl.check_each_pop = 0;

	जबतक (ctrl.entries > 0) अणु
		पूर्णांक urc;
		अगर ((ctrl.sp_high - ctrl.vrs[SP]) < माप(ctrl.vrs))
			ctrl.check_each_pop = 1;
		urc = unwind_exec_insn(&ctrl);
		अगर (urc < 0)
			वापस urc;
		अगर (ctrl.vrs[SP] < low || ctrl.vrs[SP] >= ctrl.sp_high)
			वापस -URC_FAILURE;
	पूर्ण

	अगर (ctrl.vrs[PC] == 0)
		ctrl.vrs[PC] = ctrl.vrs[LR];

	/* check क्रम infinite loop */
	अगर (frame->pc == ctrl.vrs[PC] && frame->sp == ctrl.vrs[SP])
		वापस -URC_FAILURE;

	frame->fp = ctrl.vrs[FP];
	frame->sp = ctrl.vrs[SP];
	frame->lr = ctrl.vrs[LR];
	frame->pc = ctrl.vrs[PC];

	वापस URC_OK;
पूर्ण

व्योम unwind_backtrace(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *tsk,
		      स्थिर अक्षर *loglvl)
अणु
	काष्ठा stackframe frame;

	pr_debug("%s(regs = %p tsk = %p)\n", __func__, regs, tsk);

	अगर (!tsk)
		tsk = current;

	अगर (regs) अणु
		arm_get_current_stackframe(regs, &frame);
		/* PC might be corrupted, use LR in that हाल. */
		अगर (!kernel_text_address(regs->ARM_pc))
			frame.pc = regs->ARM_lr;
	पूर्ण अन्यथा अगर (tsk == current) अणु
		frame.fp = (अचिन्हित दीर्घ)__builtin_frame_address(0);
		frame.sp = current_stack_poपूर्णांकer;
		frame.lr = (अचिन्हित दीर्घ)__builtin_वापस_address(0);
		frame.pc = (अचिन्हित दीर्घ)unwind_backtrace;
	पूर्ण अन्यथा अणु
		/* task blocked in __चयन_to */
		frame.fp = thपढ़ो_saved_fp(tsk);
		frame.sp = thपढ़ो_saved_sp(tsk);
		/*
		 * The function calling __चयन_to cannot be a leaf function
		 * so LR is recovered from the stack.
		 */
		frame.lr = 0;
		frame.pc = thपढ़ो_saved_pc(tsk);
	पूर्ण

	जबतक (1) अणु
		पूर्णांक urc;
		अचिन्हित दीर्घ where = frame.pc;

		urc = unwind_frame(&frame);
		अगर (urc < 0)
			अवरोध;
		dump_backtrace_entry(where, frame.pc, frame.sp - 4, loglvl);
	पूर्ण
पूर्ण

काष्ठा unwind_table *unwind_table_add(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
				      अचिन्हित दीर्घ text_addr,
				      अचिन्हित दीर्घ text_size)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा unwind_table *tab = kदो_स्मृति(माप(*tab), GFP_KERNEL);

	pr_debug("%s(%08lx, %08lx, %08lx, %08lx)\n", __func__, start, size,
		 text_addr, text_size);

	अगर (!tab)
		वापस tab;

	tab->start = (स्थिर काष्ठा unwind_idx *)start;
	tab->stop = (स्थिर काष्ठा unwind_idx *)(start + size);
	tab->origin = unwind_find_origin(tab->start, tab->stop);
	tab->begin_addr = text_addr;
	tab->end_addr = text_addr + text_size;

	raw_spin_lock_irqsave(&unwind_lock, flags);
	list_add_tail(&tab->list, &unwind_tables);
	raw_spin_unlock_irqrestore(&unwind_lock, flags);

	वापस tab;
पूर्ण

व्योम unwind_table_del(काष्ठा unwind_table *tab)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!tab)
		वापस;

	raw_spin_lock_irqsave(&unwind_lock, flags);
	list_del(&tab->list);
	raw_spin_unlock_irqrestore(&unwind_lock, flags);

	kमुक्त(tab);
पूर्ण
