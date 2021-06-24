<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  User-space Probes (UProbes) क्रम s390
 *
 *    Copyright IBM Corp. 2014
 *    Author(s): Jan Willeke,
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/compat.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/dis.h>
#समावेश "entry.h"

#घोषणा	UPROBE_TRAP_NR	अच_पूर्णांक_उच्च

पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm,
			     अचिन्हित दीर्घ addr)
अणु
	वापस probe_is_prohibited_opcode(auprobe->insn);
पूर्ण

पूर्णांक arch_uprobe_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अगर (psw_bits(regs->psw).eaba == PSW_BITS_AMODE_24BIT)
		वापस -EINVAL;
	अगर (!is_compat_task() && psw_bits(regs->psw).eaba == PSW_BITS_AMODE_31BIT)
		वापस -EINVAL;
	clear_thपढ़ो_flag(TIF_PER_TRAP);
	auprobe->saved_per = psw_bits(regs->psw).per;
	auprobe->saved_पूर्णांक_code = regs->पूर्णांक_code;
	regs->पूर्णांक_code = UPROBE_TRAP_NR;
	regs->psw.addr = current->utask->xol_vaddr;
	set_tsk_thपढ़ो_flag(current, TIF_UPROBE_SINGLESTEP);
	update_cr_regs(current);
	वापस 0;
पूर्ण

bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(tsk);

	अगर (regs->पूर्णांक_code != UPROBE_TRAP_NR)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक check_per_event(अचिन्हित लघु cause, अचिन्हित दीर्घ control,
			   काष्ठा pt_regs *regs)
अणु
	अगर (!(regs->psw.mask & PSW_MASK_PER))
		वापस 0;
	/* user space single step */
	अगर (control == 0)
		वापस 1;
	/* over indication क्रम storage alteration */
	अगर ((control & 0x20200000) && (cause & 0x2000))
		वापस 1;
	अगर (cause & 0x8000) अणु
		/* all branches */
		अगर ((control & 0x80800000) == 0x80000000)
			वापस 1;
		/* branch पूर्णांकo selected range */
		अगर (((control & 0x80800000) == 0x80800000) &&
		    regs->psw.addr >= current->thपढ़ो.per_user.start &&
		    regs->psw.addr <= current->thपढ़ो.per_user.end)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	पूर्णांक fixup = probe_get_fixup_type(auprobe->insn);
	काष्ठा uprobe_task *utask = current->utask;

	clear_tsk_thपढ़ो_flag(current, TIF_UPROBE_SINGLESTEP);
	update_cr_regs(current);
	psw_bits(regs->psw).per = auprobe->saved_per;
	regs->पूर्णांक_code = auprobe->saved_पूर्णांक_code;

	अगर (fixup & FIXUP_PSW_NORMAL)
		regs->psw.addr += utask->vaddr - utask->xol_vaddr;
	अगर (fixup & FIXUP_RETURN_REGISTER) अणु
		पूर्णांक reg = (auprobe->insn[0] & 0xf0) >> 4;

		regs->gprs[reg] += utask->vaddr - utask->xol_vaddr;
	पूर्ण
	अगर (fixup & FIXUP_BRANCH_NOT_TAKEN) अणु
		पूर्णांक ilen = insn_length(auprobe->insn[0] >> 8);

		अगर (regs->psw.addr - utask->xol_vaddr == ilen)
			regs->psw.addr = utask->vaddr + ilen;
	पूर्ण
	अगर (check_per_event(current->thपढ़ो.per_event.cause,
			    current->thपढ़ो.per_user.control, regs)) अणु
		/* fix per address */
		current->thपढ़ो.per_event.address = utask->vaddr;
		/* trigger per event */
		set_thपढ़ो_flag(TIF_PER_TRAP);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val,
				 व्योम *data)
अणु
	काष्ठा die_args *args = data;
	काष्ठा pt_regs *regs = args->regs;

	अगर (!user_mode(regs))
		वापस NOTIFY_DONE;
	अगर (regs->पूर्णांक_code & 0x200) /* Trap during transaction */
		वापस NOTIFY_DONE;
	चयन (val) अणु
	हाल DIE_BPT:
		अगर (uprobe_pre_sstep_notअगरier(regs))
			वापस NOTIFY_STOP;
		अवरोध;
	हाल DIE_SSTEP:
		अगर (uprobe_post_sstep_notअगरier(regs))
			वापस NOTIFY_STOP;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	clear_thपढ़ो_flag(TIF_UPROBE_SINGLESTEP);
	regs->पूर्णांक_code = auprobe->saved_पूर्णांक_code;
	regs->psw.addr = current->utask->vaddr;
	current->thपढ़ो.per_event.address = current->utask->vaddr;
पूर्ण

अचिन्हित दीर्घ arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline,
						काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig;

	orig = regs->gprs[14];
	regs->gprs[14] = trampoline;
	वापस orig;
पूर्ण

bool arch_uretprobe_is_alive(काष्ठा वापस_instance *ret, क्रमागत rp_check ctx,
			     काष्ठा pt_regs *regs)
अणु
	अगर (ctx == RP_CHECK_CHAIN_CALL)
		वापस user_stack_poपूर्णांकer(regs) <= ret->stack;
	अन्यथा
		वापस user_stack_poपूर्णांकer(regs) < ret->stack;
पूर्ण

/* Inकाष्ठाion Emulation */

अटल व्योम adjust_psw_addr(psw_t *psw, अचिन्हित दीर्घ len)
अणु
	psw->addr = __शुरुआत_psw(*psw, -len);
पूर्ण

#घोषणा EMU_ILLEGAL_OP		1
#घोषणा EMU_SPECIFICATION	2
#घोषणा EMU_ADDRESSING		3

#घोषणा emu_load_ril(ptr, output)			\
(अणु							\
	अचिन्हित पूर्णांक mask = माप(*(ptr)) - 1;		\
	__typeof__(*(ptr)) input;			\
	पूर्णांक __rc = 0;					\
							\
	अगर (!test_facility(34))				\
		__rc = EMU_ILLEGAL_OP;			\
	अन्यथा अगर ((u64 __क्रमce)ptr & mask)		\
		__rc = EMU_SPECIFICATION;		\
	अन्यथा अगर (get_user(input, ptr))			\
		__rc = EMU_ADDRESSING;			\
	अन्यथा						\
		*(output) = input;			\
	__rc;						\
पूर्ण)

#घोषणा emu_store_ril(regs, ptr, input)			\
(अणु							\
	अचिन्हित पूर्णांक mask = माप(*(ptr)) - 1;		\
	__typeof__(ptr) __ptr = (ptr);			\
	पूर्णांक __rc = 0;					\
							\
	अगर (!test_facility(34))				\
		__rc = EMU_ILLEGAL_OP;			\
	अन्यथा अगर ((u64 __क्रमce)__ptr & mask)		\
		__rc = EMU_SPECIFICATION;		\
	अन्यथा अगर (put_user(*(input), __ptr))		\
		__rc = EMU_ADDRESSING;			\
	अगर (__rc == 0)					\
		sim_stor_event(regs,			\
			       (व्योम __क्रमce *)__ptr,	\
			       mask + 1);		\
	__rc;						\
पूर्ण)

#घोषणा emu_cmp_ril(regs, ptr, cmp)			\
(अणु							\
	अचिन्हित पूर्णांक mask = माप(*(ptr)) - 1;		\
	__typeof__(*(ptr)) input;			\
	पूर्णांक __rc = 0;					\
							\
	अगर (!test_facility(34))				\
		__rc = EMU_ILLEGAL_OP;			\
	अन्यथा अगर ((u64 __क्रमce)ptr & mask)		\
		__rc = EMU_SPECIFICATION;		\
	अन्यथा अगर (get_user(input, ptr))			\
		__rc = EMU_ADDRESSING;			\
	अन्यथा अगर (input > *(cmp))			\
		psw_bits((regs)->psw).cc = 1;		\
	अन्यथा अगर (input < *(cmp))			\
		psw_bits((regs)->psw).cc = 2;		\
	अन्यथा						\
		psw_bits((regs)->psw).cc = 0;		\
	__rc;						\
पूर्ण)

काष्ठा insn_ril अणु
	u8 opc0;
	u8 reg	: 4;
	u8 opc1 : 4;
	s32 disp;
पूर्ण __packed;

जोड़ split_रेजिस्टर अणु
	u64 u64;
	u32 u32[2];
	u16 u16[4];
	s64 s64;
	s32 s32[2];
	s16 s16[4];
पूर्ण;

/*
 * If user per रेजिस्टरs are setup to trace storage alterations and an
 * emulated store took place on a fitting address a user trap is generated.
 */
अटल व्योम sim_stor_event(काष्ठा pt_regs *regs, व्योम *addr, पूर्णांक len)
अणु
	अगर (!(regs->psw.mask & PSW_MASK_PER))
		वापस;
	अगर (!(current->thपढ़ो.per_user.control & PER_EVENT_STORE))
		वापस;
	अगर ((व्योम *)current->thपढ़ो.per_user.start > (addr + len))
		वापस;
	अगर ((व्योम *)current->thपढ़ो.per_user.end < addr)
		वापस;
	current->thपढ़ो.per_event.address = regs->psw.addr;
	current->thपढ़ो.per_event.cause = PER_EVENT_STORE >> 16;
	set_thपढ़ो_flag(TIF_PER_TRAP);
पूर्ण

/*
 * pc relative inकाष्ठाions are emulated, since parameters may not be
 * accessible from the xol area due to range limitations.
 */
अटल व्योम handle_insn_ril(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	जोड़ split_रेजिस्टर *rx;
	काष्ठा insn_ril *insn;
	अचिन्हित पूर्णांक ilen;
	व्योम *uptr;
	पूर्णांक rc = 0;

	insn = (काष्ठा insn_ril *) &auprobe->insn;
	rx = (जोड़ split_रेजिस्टर *) &regs->gprs[insn->reg];
	uptr = (व्योम *)(regs->psw.addr + (insn->disp * 2));
	ilen = insn_length(insn->opc0);

	चयन (insn->opc0) अणु
	हाल 0xc0:
		चयन (insn->opc1) अणु
		हाल 0x00: /* larl */
			rx->u64 = (अचिन्हित दीर्घ)uptr;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0xc4:
		चयन (insn->opc1) अणु
		हाल 0x02: /* llhrl */
			rc = emu_load_ril((u16 __user *)uptr, &rx->u32[1]);
			अवरोध;
		हाल 0x04: /* lghrl */
			rc = emu_load_ril((s16 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x05: /* lhrl */
			rc = emu_load_ril((s16 __user *)uptr, &rx->u32[1]);
			अवरोध;
		हाल 0x06: /* llghrl */
			rc = emu_load_ril((u16 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x08: /* lgrl */
			rc = emu_load_ril((u64 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x0c: /* lgfrl */
			rc = emu_load_ril((s32 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x0d: /* lrl */
			rc = emu_load_ril((u32 __user *)uptr, &rx->u32[1]);
			अवरोध;
		हाल 0x0e: /* llgfrl */
			rc = emu_load_ril((u32 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x07: /* sthrl */
			rc = emu_store_ril(regs, (u16 __user *)uptr, &rx->u16[3]);
			अवरोध;
		हाल 0x0b: /* stgrl */
			rc = emu_store_ril(regs, (u64 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x0f: /* strl */
			rc = emu_store_ril(regs, (u32 __user *)uptr, &rx->u32[1]);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0xc6:
		चयन (insn->opc1) अणु
		हाल 0x02: /* pfdrl */
			अगर (!test_facility(34))
				rc = EMU_ILLEGAL_OP;
			अवरोध;
		हाल 0x04: /* cghrl */
			rc = emu_cmp_ril(regs, (s16 __user *)uptr, &rx->s64);
			अवरोध;
		हाल 0x05: /* chrl */
			rc = emu_cmp_ril(regs, (s16 __user *)uptr, &rx->s32[1]);
			अवरोध;
		हाल 0x06: /* clghrl */
			rc = emu_cmp_ril(regs, (u16 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x07: /* clhrl */
			rc = emu_cmp_ril(regs, (u16 __user *)uptr, &rx->u32[1]);
			अवरोध;
		हाल 0x08: /* cgrl */
			rc = emu_cmp_ril(regs, (s64 __user *)uptr, &rx->s64);
			अवरोध;
		हाल 0x0a: /* clgrl */
			rc = emu_cmp_ril(regs, (u64 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x0c: /* cgfrl */
			rc = emu_cmp_ril(regs, (s32 __user *)uptr, &rx->s64);
			अवरोध;
		हाल 0x0d: /* crl */
			rc = emu_cmp_ril(regs, (s32 __user *)uptr, &rx->s32[1]);
			अवरोध;
		हाल 0x0e: /* clgfrl */
			rc = emu_cmp_ril(regs, (u32 __user *)uptr, &rx->u64);
			अवरोध;
		हाल 0x0f: /* clrl */
			rc = emu_cmp_ril(regs, (u32 __user *)uptr, &rx->u32[1]);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	adjust_psw_addr(&regs->psw, ilen);
	चयन (rc) अणु
	हाल EMU_ILLEGAL_OP:
		regs->पूर्णांक_code = ilen << 16 | 0x0001;
		करो_report_trap(regs, संक_अवैध, ILL_ILLOPC, शून्य);
		अवरोध;
	हाल EMU_SPECIFICATION:
		regs->पूर्णांक_code = ilen << 16 | 0x0006;
		करो_report_trap(regs, संक_अवैध, ILL_ILLOPC , शून्य);
		अवरोध;
	हाल EMU_ADDRESSING:
		regs->पूर्णांक_code = ilen << 16 | 0x0005;
		करो_report_trap(regs, संक_अंश, SEGV_MAPERR, शून्य);
		अवरोध;
	पूर्ण
पूर्ण

bool arch_uprobe_skip_sstep(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अगर ((psw_bits(regs->psw).eaba == PSW_BITS_AMODE_24BIT) ||
	    ((psw_bits(regs->psw).eaba == PSW_BITS_AMODE_31BIT) &&
	     !is_compat_task())) अणु
		regs->psw.addr = __शुरुआत_psw(regs->psw, UPROBE_SWBP_INSN_SIZE);
		करो_report_trap(regs, संक_अवैध, ILL_ILLADR, शून्य);
		वापस true;
	पूर्ण
	अगर (probe_is_insn_relative_दीर्घ(auprobe->insn)) अणु
		handle_insn_ril(auprobe, regs);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
