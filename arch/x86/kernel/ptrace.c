<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* By Ross Biro 1/23/92 */
/*
 * Pentium III FXSR, SSE support
 *	Gareth Hughes <gareth@valinux.com>, May 2000
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/user.h>
#समावेश <linux/elf.h>
#समावेश <linux/security.h>
#समावेश <linux/audit.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/export.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/nospec.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/fpu/संकेत.स>
#समावेश <यंत्र/fpu/regset.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/ldt.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/prctl.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/fsgsbase.h>
#समावेश <यंत्र/io_biपंचांगap.h>

#समावेश "tls.h"

क्रमागत x86_regset अणु
	REGSET_GENERAL,
	REGSET_FP,
	REGSET_XFP,
	REGSET_IOPERM64 = REGSET_XFP,
	REGSET_XSTATE,
	REGSET_TLS,
	REGSET_IOPERM32,
पूर्ण;

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(r) अणु.name = #r, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
#अगर_घोषित CONFIG_X86_64
	REG_OFFSET_NAME(r15),
	REG_OFFSET_NAME(r14),
	REG_OFFSET_NAME(r13),
	REG_OFFSET_NAME(r12),
	REG_OFFSET_NAME(r11),
	REG_OFFSET_NAME(r10),
	REG_OFFSET_NAME(r9),
	REG_OFFSET_NAME(r8),
#पूर्ण_अगर
	REG_OFFSET_NAME(bx),
	REG_OFFSET_NAME(cx),
	REG_OFFSET_NAME(dx),
	REG_OFFSET_NAME(si),
	REG_OFFSET_NAME(di),
	REG_OFFSET_NAME(bp),
	REG_OFFSET_NAME(ax),
#अगर_घोषित CONFIG_X86_32
	REG_OFFSET_NAME(ds),
	REG_OFFSET_NAME(es),
	REG_OFFSET_NAME(fs),
	REG_OFFSET_NAME(gs),
#पूर्ण_अगर
	REG_OFFSET_NAME(orig_ax),
	REG_OFFSET_NAME(ip),
	REG_OFFSET_NAME(cs),
	REG_OFFSET_NAME(flags),
	REG_OFFSET_NAME(sp),
	REG_OFFSET_NAME(ss),
	REG_OFFSET_END,
पूर्ण;

/**
 * regs_query_रेजिस्टर_offset() - query रेजिस्टर offset from its name
 * @name:	the name of a रेजिस्टर
 *
 * regs_query_रेजिस्टर_offset() वापसs the offset of a रेजिस्टर in काष्ठा
 * pt_regs from its name. If the name is invalid, this वापसs -EINVAL;
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (!म_भेद(roff->name, name))
			वापस roff->offset;
	वापस -EINVAL;
पूर्ण

/**
 * regs_query_रेजिस्टर_name() - query रेजिस्टर name from its offset
 * @offset:	the offset of a रेजिस्टर in काष्ठा pt_regs.
 *
 * regs_query_रेजिस्टर_name() वापसs the name of a रेजिस्टर from its
 * offset in काष्ठा pt_regs. If the @offset is invalid, this वापसs शून्य;
 */
स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (roff->offset == offset)
			वापस roff->name;
	वापस शून्य;
पूर्ण

/*
 * करोes not yet catch संकेतs sent when the child dies.
 * in निकास.c or in संकेत.c.
 */

/*
 * Determines which flags the user has access to [1 = access, 0 = no access].
 */
#घोषणा FLAG_MASK_32		((अचिन्हित दीर्घ)			\
				 (X86_EFLAGS_CF | X86_EFLAGS_PF |	\
				  X86_EFLAGS_AF | X86_EFLAGS_ZF |	\
				  X86_EFLAGS_SF | X86_EFLAGS_TF |	\
				  X86_EFLAGS_DF | X86_EFLAGS_OF |	\
				  X86_EFLAGS_RF | X86_EFLAGS_AC))

/*
 * Determines whether a value may be installed in a segment रेजिस्टर.
 */
अटल अंतरभूत bool invalid_selector(u16 value)
अणु
	वापस unlikely(value != 0 && (value & SEGMENT_RPL_MASK) != USER_RPL);
पूर्ण

#अगर_घोषित CONFIG_X86_32

#घोषणा FLAG_MASK		FLAG_MASK_32

अटल अचिन्हित दीर्घ *pt_regs_access(काष्ठा pt_regs *regs, अचिन्हित दीर्घ regno)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, bx) != 0);
	वापस &regs->bx + (regno >> 2);
पूर्ण

अटल u16 get_segment_reg(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ offset)
अणु
	/*
	 * Returning the value truncates it to 16 bits.
	 */
	अचिन्हित पूर्णांक retval;
	अगर (offset != दुरत्व(काष्ठा user_regs_काष्ठा, gs))
		retval = *pt_regs_access(task_pt_regs(task), offset);
	अन्यथा अणु
		अगर (task == current)
			retval = get_user_gs(task_pt_regs(task));
		अन्यथा
			retval = task_user_gs(task);
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक set_segment_reg(काष्ठा task_काष्ठा *task,
			   अचिन्हित दीर्घ offset, u16 value)
अणु
	अगर (WARN_ON_ONCE(task == current))
		वापस -EIO;

	/*
	 * The value argument was alपढ़ोy truncated to 16 bits.
	 */
	अगर (invalid_selector(value))
		वापस -EIO;

	/*
	 * For %cs and %ss we cannot permit a null selector.
	 * We can permit a bogus selector as दीर्घ as it has USER_RPL.
	 * Null selectors are fine क्रम other segment रेजिस्टरs, but
	 * we will never get back to user mode with invalid %cs or %ss
	 * and will take the trap in iret instead.  Much code relies
	 * on user_mode() to distinguish a user trap frame (which can
	 * safely use invalid selectors) from a kernel trap frame.
	 */
	चयन (offset) अणु
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, cs):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, ss):
		अगर (unlikely(value == 0))
			वापस -EIO;
		fallthrough;

	शेष:
		*pt_regs_access(task_pt_regs(task), offset) = value;
		अवरोध;

	हाल दुरत्व(काष्ठा user_regs_काष्ठा, gs):
		task_user_gs(task) = value;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा  /* CONFIG_X86_64 */

#घोषणा FLAG_MASK		(FLAG_MASK_32 | X86_EFLAGS_NT)

अटल अचिन्हित दीर्घ *pt_regs_access(काष्ठा pt_regs *regs, अचिन्हित दीर्घ offset)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, r15) != 0);
	वापस &regs->r15 + (offset / माप(regs->r15));
पूर्ण

अटल u16 get_segment_reg(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ offset)
अणु
	/*
	 * Returning the value truncates it to 16 bits.
	 */
	अचिन्हित पूर्णांक seg;

	चयन (offset) अणु
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, fs):
		अगर (task == current) अणु
			/* Older gas can't assemble movq %?s,%r?? */
			यंत्र("movl %%fs,%0" : "=r" (seg));
			वापस seg;
		पूर्ण
		वापस task->thपढ़ो.fsindex;
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, gs):
		अगर (task == current) अणु
			यंत्र("movl %%gs,%0" : "=r" (seg));
			वापस seg;
		पूर्ण
		वापस task->thपढ़ो.gsindex;
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, ds):
		अगर (task == current) अणु
			यंत्र("movl %%ds,%0" : "=r" (seg));
			वापस seg;
		पूर्ण
		वापस task->thपढ़ो.ds;
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, es):
		अगर (task == current) अणु
			यंत्र("movl %%es,%0" : "=r" (seg));
			वापस seg;
		पूर्ण
		वापस task->thपढ़ो.es;

	हाल दुरत्व(काष्ठा user_regs_काष्ठा, cs):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, ss):
		अवरोध;
	पूर्ण
	वापस *pt_regs_access(task_pt_regs(task), offset);
पूर्ण

अटल पूर्णांक set_segment_reg(काष्ठा task_काष्ठा *task,
			   अचिन्हित दीर्घ offset, u16 value)
अणु
	अगर (WARN_ON_ONCE(task == current))
		वापस -EIO;

	/*
	 * The value argument was alपढ़ोy truncated to 16 bits.
	 */
	अगर (invalid_selector(value))
		वापस -EIO;

	/*
	 * Writes to FS and GS will change the stored selector.  Whether
	 * this changes the segment base as well depends on whether
	 * FSGSBASE is enabled.
	 */

	चयन (offset) अणु
	हाल दुरत्व(काष्ठा user_regs_काष्ठा,fs):
		task->thपढ़ो.fsindex = value;
		अवरोध;
	हाल दुरत्व(काष्ठा user_regs_काष्ठा,gs):
		task->thपढ़ो.gsindex = value;
		अवरोध;
	हाल दुरत्व(काष्ठा user_regs_काष्ठा,ds):
		task->thपढ़ो.ds = value;
		अवरोध;
	हाल दुरत्व(काष्ठा user_regs_काष्ठा,es):
		task->thपढ़ो.es = value;
		अवरोध;

		/*
		 * Can't actually change these in 64-bit mode.
		 */
	हाल दुरत्व(काष्ठा user_regs_काष्ठा,cs):
		अगर (unlikely(value == 0))
			वापस -EIO;
		task_pt_regs(task)->cs = value;
		अवरोध;
	हाल दुरत्व(काष्ठा user_regs_काष्ठा,ss):
		अगर (unlikely(value == 0))
			वापस -EIO;
		task_pt_regs(task)->ss = value;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_X86_32 */

अटल अचिन्हित दीर्घ get_flags(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ retval = task_pt_regs(task)->flags;

	/*
	 * If the debugger set TF, hide it from the पढ़ोout.
	 */
	अगर (test_tsk_thपढ़ो_flag(task, TIF_FORCED_TF))
		retval &= ~X86_EFLAGS_TF;

	वापस retval;
पूर्ण

अटल पूर्णांक set_flags(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ value)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(task);

	/*
	 * If the user value contains TF, mark that
	 * it was not "us" (the debugger) that set it.
	 * If not, make sure it stays set अगर we had.
	 */
	अगर (value & X86_EFLAGS_TF)
		clear_tsk_thपढ़ो_flag(task, TIF_FORCED_TF);
	अन्यथा अगर (test_tsk_thपढ़ो_flag(task, TIF_FORCED_TF))
		value |= X86_EFLAGS_TF;

	regs->flags = (regs->flags & ~FLAG_MASK) | (value & FLAG_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक putreg(काष्ठा task_काष्ठा *child,
		  अचिन्हित दीर्घ offset, अचिन्हित दीर्घ value)
अणु
	चयन (offset) अणु
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, cs):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, ds):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, es):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, fs):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, gs):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, ss):
		वापस set_segment_reg(child, offset, value);

	हाल दुरत्व(काष्ठा user_regs_काष्ठा, flags):
		वापस set_flags(child, value);

#अगर_घोषित CONFIG_X86_64
	हाल दुरत्व(काष्ठा user_regs_काष्ठा,fs_base):
		अगर (value >= TASK_SIZE_MAX)
			वापस -EIO;
		x86_fsbase_ग_लिखो_task(child, value);
		वापस 0;
	हाल दुरत्व(काष्ठा user_regs_काष्ठा,gs_base):
		अगर (value >= TASK_SIZE_MAX)
			वापस -EIO;
		x86_gsbase_ग_लिखो_task(child, value);
		वापस 0;
#पूर्ण_अगर
	पूर्ण

	*pt_regs_access(task_pt_regs(child), offset) = value;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ getreg(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ offset)
अणु
	चयन (offset) अणु
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, cs):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, ds):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, es):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, fs):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, gs):
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, ss):
		वापस get_segment_reg(task, offset);

	हाल दुरत्व(काष्ठा user_regs_काष्ठा, flags):
		वापस get_flags(task);

#अगर_घोषित CONFIG_X86_64
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, fs_base):
		वापस x86_fsbase_पढ़ो_task(task);
	हाल दुरत्व(काष्ठा user_regs_काष्ठा, gs_base):
		वापस x86_gsbase_पढ़ो_task(task);
#पूर्ण_अगर
	पूर्ण

	वापस *pt_regs_access(task_pt_regs(task), offset);
पूर्ण

अटल पूर्णांक genregs_get(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       काष्ठा membuf to)
अणु
	पूर्णांक reg;

	क्रम (reg = 0; to.left; reg++)
		membuf_store(&to, getreg(target, reg * माप(अचिन्हित दीर्घ)));
	वापस 0;
पूर्ण

अटल पूर्णांक genregs_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret = 0;
	अगर (kbuf) अणु
		स्थिर अचिन्हित दीर्घ *k = kbuf;
		जबतक (count >= माप(*k) && !ret) अणु
			ret = putreg(target, pos, *k++);
			count -= माप(*k);
			pos += माप(*k);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित दीर्घ  __user *u = ubuf;
		जबतक (count >= माप(*u) && !ret) अणु
			अचिन्हित दीर्घ word;
			ret = __get_user(word, u++);
			अगर (ret)
				अवरोध;
			ret = putreg(target, pos, word);
			count -= माप(*u);
			pos += माप(*u);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ptrace_triggered(काष्ठा perf_event *bp,
			     काष्ठा perf_sample_data *data,
			     काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &(current->thपढ़ो);

	/*
	 * Store in the भव DR6 रेजिस्टर the fact that the अवरोधpoपूर्णांक
	 * was hit so the thपढ़ो's debugger will see it.
	 */
	क्रम (i = 0; i < HBP_NUM; i++) अणु
		अगर (thपढ़ो->ptrace_bps[i] == bp)
			अवरोध;
	पूर्ण

	thपढ़ो->भव_dr6 |= (DR_TRAP0 << i);
पूर्ण

/*
 * Walk through every ptrace अवरोधpoपूर्णांकs क्रम this thपढ़ो and
 * build the dr7 value on top of their attributes.
 *
 */
अटल अचिन्हित दीर्घ ptrace_get_dr7(काष्ठा perf_event *bp[])
अणु
	पूर्णांक i;
	पूर्णांक dr7 = 0;
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info;

	क्रम (i = 0; i < HBP_NUM; i++) अणु
		अगर (bp[i] && !bp[i]->attr.disabled) अणु
			info = counter_arch_bp(bp[i]);
			dr7 |= encode_dr7(i, info->len, info->type);
		पूर्ण
	पूर्ण

	वापस dr7;
पूर्ण

अटल पूर्णांक ptrace_fill_bp_fields(काष्ठा perf_event_attr *attr,
					पूर्णांक len, पूर्णांक type, bool disabled)
अणु
	पूर्णांक err, bp_len, bp_type;

	err = arch_bp_generic_fields(len, type, &bp_len, &bp_type);
	अगर (!err) अणु
		attr->bp_len = bp_len;
		attr->bp_type = bp_type;
		attr->disabled = disabled;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा perf_event *
ptrace_रेजिस्टर_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk, पूर्णांक len, पूर्णांक type,
				अचिन्हित दीर्घ addr, bool disabled)
अणु
	काष्ठा perf_event_attr attr;
	पूर्णांक err;

	ptrace_अवरोधpoपूर्णांक_init(&attr);
	attr.bp_addr = addr;

	err = ptrace_fill_bp_fields(&attr, len, type, disabled);
	अगर (err)
		वापस ERR_PTR(err);

	वापस रेजिस्टर_user_hw_अवरोधpoपूर्णांक(&attr, ptrace_triggered,
						 शून्य, tsk);
पूर्ण

अटल पूर्णांक ptrace_modअगरy_अवरोधpoपूर्णांक(काष्ठा perf_event *bp, पूर्णांक len, पूर्णांक type,
					पूर्णांक disabled)
अणु
	काष्ठा perf_event_attr attr = bp->attr;
	पूर्णांक err;

	err = ptrace_fill_bp_fields(&attr, len, type, disabled);
	अगर (err)
		वापस err;

	वापस modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
पूर्ण

/*
 * Handle ptrace ग_लिखोs to debug रेजिस्टर 7.
 */
अटल पूर्णांक ptrace_ग_लिखो_dr7(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ data)
अणु
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &tsk->thपढ़ो;
	अचिन्हित दीर्घ old_dr7;
	bool second_pass = false;
	पूर्णांक i, rc, ret = 0;

	data &= ~DR_CONTROL_RESERVED;
	old_dr7 = ptrace_get_dr7(thपढ़ो->ptrace_bps);

restore:
	rc = 0;
	क्रम (i = 0; i < HBP_NUM; i++) अणु
		अचिन्हित len, type;
		bool disabled = !decode_dr7(data, i, &len, &type);
		काष्ठा perf_event *bp = thपढ़ो->ptrace_bps[i];

		अगर (!bp) अणु
			अगर (disabled)
				जारी;

			bp = ptrace_रेजिस्टर_अवरोधpoपूर्णांक(tsk,
					len, type, 0, disabled);
			अगर (IS_ERR(bp)) अणु
				rc = PTR_ERR(bp);
				अवरोध;
			पूर्ण

			thपढ़ो->ptrace_bps[i] = bp;
			जारी;
		पूर्ण

		rc = ptrace_modअगरy_अवरोधpoपूर्णांक(bp, len, type, disabled);
		अगर (rc)
			अवरोध;
	पूर्ण

	/* Restore अगर the first pass failed, second_pass shouldn't fail. */
	अगर (rc && !WARN_ON(second_pass)) अणु
		ret = rc;
		data = old_dr7;
		second_pass = true;
		जाओ restore;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Handle PTRACE_PEEKUSR calls क्रम the debug रेजिस्टर area.
 */
अटल अचिन्हित दीर्घ ptrace_get_debugreg(काष्ठा task_काष्ठा *tsk, पूर्णांक n)
अणु
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &tsk->thपढ़ो;
	अचिन्हित दीर्घ val = 0;

	अगर (n < HBP_NUM) अणु
		पूर्णांक index = array_index_nospec(n, HBP_NUM);
		काष्ठा perf_event *bp = thपढ़ो->ptrace_bps[index];

		अगर (bp)
			val = bp->hw.info.address;
	पूर्ण अन्यथा अगर (n == 6) अणु
		val = thपढ़ो->भव_dr6 ^ DR6_RESERVED; /* Flip back to arch polarity */
	पूर्ण अन्यथा अगर (n == 7) अणु
		val = thपढ़ो->ptrace_dr7;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक ptrace_set_अवरोधpoपूर्णांक_addr(काष्ठा task_काष्ठा *tsk, पूर्णांक nr,
				      अचिन्हित दीर्घ addr)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;
	काष्ठा perf_event *bp = t->ptrace_bps[nr];
	पूर्णांक err = 0;

	अगर (!bp) अणु
		/*
		 * Put stub len and type to create an inactive but correct bp.
		 *
		 * CHECKME: the previous code वापसed -EIO अगर the addr wasn't
		 * a valid task भव addr. The new one will वापस -EINVAL in
		 *  this हाल.
		 * -EINVAL may be what we want क्रम in-kernel अवरोधpoपूर्णांकs users,
		 * but -EIO looks better क्रम ptrace, since we refuse a रेजिस्टर
		 * writing क्रम the user. And anyway this is the previous
		 * behaviour.
		 */
		bp = ptrace_रेजिस्टर_अवरोधpoपूर्णांक(tsk,
				X86_BREAKPOINT_LEN_1, X86_BREAKPOINT_WRITE,
				addr, true);
		अगर (IS_ERR(bp))
			err = PTR_ERR(bp);
		अन्यथा
			t->ptrace_bps[nr] = bp;
	पूर्ण अन्यथा अणु
		काष्ठा perf_event_attr attr = bp->attr;

		attr.bp_addr = addr;
		err = modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Handle PTRACE_POKEUSR calls क्रम the debug रेजिस्टर area.
 */
अटल पूर्णांक ptrace_set_debugreg(काष्ठा task_काष्ठा *tsk, पूर्णांक n,
			       अचिन्हित दीर्घ val)
अणु
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &tsk->thपढ़ो;
	/* There are no DR4 or DR5 रेजिस्टरs */
	पूर्णांक rc = -EIO;

	अगर (n < HBP_NUM) अणु
		rc = ptrace_set_अवरोधpoपूर्णांक_addr(tsk, n, val);
	पूर्ण अन्यथा अगर (n == 6) अणु
		thपढ़ो->भव_dr6 = val ^ DR6_RESERVED; /* Flip to positive polarity */
		rc = 0;
	पूर्ण अन्यथा अगर (n == 7) अणु
		rc = ptrace_ग_लिखो_dr7(tsk, val);
		अगर (!rc)
			thपढ़ो->ptrace_dr7 = val;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * These access the current or another (stopped) task's io permission
 * biपंचांगap क्रम debugging or core dump.
 */
अटल पूर्णांक ioperm_active(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset)
अणु
	काष्ठा io_biपंचांगap *iobm = target->thपढ़ो.io_biपंचांगap;

	वापस iobm ? DIV_ROUND_UP(iobm->max, regset->size) : 0;
पूर्ण

अटल पूर्णांक ioperm_get(काष्ठा task_काष्ठा *target,
		      स्थिर काष्ठा user_regset *regset,
		      काष्ठा membuf to)
अणु
	काष्ठा io_biपंचांगap *iobm = target->thपढ़ो.io_biपंचांगap;

	अगर (!iobm)
		वापस -ENXIO;

	वापस membuf_ग_लिखो(&to, iobm->biपंचांगap, IO_BITMAP_BYTES);
पूर्ण

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure the single step bit is not set.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	user_disable_single_step(child);
पूर्ण

#अगर defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
अटल स्थिर काष्ठा user_regset_view user_x86_32_view; /* Initialized below. */
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_64
अटल स्थिर काष्ठा user_regset_view user_x86_64_view; /* Initialized below. */
#पूर्ण_अगर

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ __user *datap = (अचिन्हित दीर्घ __user *)data;

#अगर_घोषित CONFIG_X86_64
	/* This is native 64-bit ptrace() */
	स्थिर काष्ठा user_regset_view *regset_view = &user_x86_64_view;
#अन्यथा
	/* This is native 32-bit ptrace() */
	स्थिर काष्ठा user_regset_view *regset_view = &user_x86_32_view;
#पूर्ण_अगर

	चयन (request) अणु
	/* पढ़ो the word at location addr in the USER area. */
	हाल PTRACE_PEEKUSR: अणु
		अचिन्हित दीर्घ पंचांगp;

		ret = -EIO;
		अगर ((addr & (माप(data) - 1)) || addr >= माप(काष्ठा user))
			अवरोध;

		पंचांगp = 0;  /* Default वापस condition */
		अगर (addr < माप(काष्ठा user_regs_काष्ठा))
			पंचांगp = getreg(child, addr);
		अन्यथा अगर (addr >= दुरत्व(काष्ठा user, u_debugreg[0]) &&
			 addr <= दुरत्व(काष्ठा user, u_debugreg[7])) अणु
			addr -= दुरत्व(काष्ठा user, u_debugreg[0]);
			पंचांगp = ptrace_get_debugreg(child, addr / माप(data));
		पूर्ण
		ret = put_user(पंचांगp, datap);
		अवरोध;
	पूर्ण

	हाल PTRACE_POKEUSR: /* ग_लिखो the word at location addr in the USER area */
		ret = -EIO;
		अगर ((addr & (माप(data) - 1)) || addr >= माप(काष्ठा user))
			अवरोध;

		अगर (addr < माप(काष्ठा user_regs_काष्ठा))
			ret = putreg(child, addr, data);
		अन्यथा अगर (addr >= दुरत्व(काष्ठा user, u_debugreg[0]) &&
			 addr <= दुरत्व(काष्ठा user, u_debugreg[7])) अणु
			addr -= दुरत्व(काष्ठा user, u_debugreg[0]);
			ret = ptrace_set_debugreg(child,
						  addr / माप(data), data);
		पूर्ण
		अवरोध;

	हाल PTRACE_GETREGS:	/* Get all gp regs from the child. */
		वापस copy_regset_to_user(child,
					   regset_view,
					   REGSET_GENERAL,
					   0, माप(काष्ठा user_regs_काष्ठा),
					   datap);

	हाल PTRACE_SETREGS:	/* Set all gp regs in the child. */
		वापस copy_regset_from_user(child,
					     regset_view,
					     REGSET_GENERAL,
					     0, माप(काष्ठा user_regs_काष्ठा),
					     datap);

	हाल PTRACE_GETFPREGS:	/* Get the child FPU state. */
		वापस copy_regset_to_user(child,
					   regset_view,
					   REGSET_FP,
					   0, माप(काष्ठा user_i387_काष्ठा),
					   datap);

	हाल PTRACE_SETFPREGS:	/* Set the child FPU state. */
		वापस copy_regset_from_user(child,
					     regset_view,
					     REGSET_FP,
					     0, माप(काष्ठा user_i387_काष्ठा),
					     datap);

#अगर_घोषित CONFIG_X86_32
	हाल PTRACE_GETFPXREGS:	/* Get the child extended FPU state. */
		वापस copy_regset_to_user(child, &user_x86_32_view,
					   REGSET_XFP,
					   0, माप(काष्ठा user_fxsr_काष्ठा),
					   datap) ? -EIO : 0;

	हाल PTRACE_SETFPXREGS:	/* Set the child extended FPU state. */
		वापस copy_regset_from_user(child, &user_x86_32_view,
					     REGSET_XFP,
					     0, माप(काष्ठा user_fxsr_काष्ठा),
					     datap) ? -EIO : 0;
#पूर्ण_अगर

#अगर defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
	हाल PTRACE_GET_THREAD_AREA:
		अगर ((पूर्णांक) addr < 0)
			वापस -EIO;
		ret = करो_get_thपढ़ो_area(child, addr,
					(काष्ठा user_desc __user *)data);
		अवरोध;

	हाल PTRACE_SET_THREAD_AREA:
		अगर ((पूर्णांक) addr < 0)
			वापस -EIO;
		ret = करो_set_thपढ़ो_area(child, addr,
					(काष्ठा user_desc __user *)data, 0);
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
		/* normal 64bit पूर्णांकerface to access TLS data.
		   Works just like arch_prctl, except that the arguments
		   are reversed. */
	हाल PTRACE_ARCH_PRCTL:
		ret = करो_arch_prctl_64(child, data, addr);
		अवरोध;
#पूर्ण_अगर

	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IA32_EMULATION

#समावेश <linux/compat.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/ia32.h>
#समावेश <यंत्र/user32.h>

#घोषणा R32(l,q)							\
	हाल दुरत्व(काष्ठा user32, regs.l):				\
		regs->q = value; अवरोध

#घोषणा SEG32(rs)							\
	हाल दुरत्व(काष्ठा user32, regs.rs):				\
		वापस set_segment_reg(child,				\
				       दुरत्व(काष्ठा user_regs_काष्ठा, rs), \
				       value);				\
		अवरोध

अटल पूर्णांक putreg32(काष्ठा task_काष्ठा *child, अचिन्हित regno, u32 value)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(child);
	पूर्णांक ret;

	चयन (regno) अणु

	SEG32(cs);
	SEG32(ds);
	SEG32(es);

	/*
	 * A 32-bit ptracer on a 64-bit kernel expects that writing
	 * FS or GS will also update the base.  This is needed क्रम
	 * operations like PTRACE_SETREGS to fully restore a saved
	 * CPU state.
	 */

	हाल दुरत्व(काष्ठा user32, regs.fs):
		ret = set_segment_reg(child,
				      दुरत्व(काष्ठा user_regs_काष्ठा, fs),
				      value);
		अगर (ret == 0)
			child->thपढ़ो.fsbase =
				x86_fsgsbase_पढ़ो_task(child, value);
		वापस ret;

	हाल दुरत्व(काष्ठा user32, regs.gs):
		ret = set_segment_reg(child,
				      दुरत्व(काष्ठा user_regs_काष्ठा, gs),
				      value);
		अगर (ret == 0)
			child->thपढ़ो.gsbase =
				x86_fsgsbase_पढ़ो_task(child, value);
		वापस ret;

	SEG32(ss);

	R32(ebx, bx);
	R32(ecx, cx);
	R32(edx, dx);
	R32(edi, di);
	R32(esi, si);
	R32(ebp, bp);
	R32(eax, ax);
	R32(eip, ip);
	R32(esp, sp);

	हाल दुरत्व(काष्ठा user32, regs.orig_eax):
		/*
		 * Warning: bizarre corner हाल fixup here.  A 32-bit
		 * debugger setting orig_eax to -1 wants to disable
		 * syscall restart.  Make sure that the syscall
		 * restart code sign-extends orig_ax.  Also make sure
		 * we पूर्णांकerpret the -ERESTART* codes correctly अगर
		 * loaded पूर्णांकo regs->ax in हाल the task is not
		 * actually still sitting at the निकास from a 32-bit
		 * syscall with TS_COMPAT still set.
		 */
		regs->orig_ax = value;
		अगर (syscall_get_nr(child, regs) >= 0)
			child->thपढ़ो_info.status |= TS_I386_REGS_POKED;
		अवरोध;

	हाल दुरत्व(काष्ठा user32, regs.eflags):
		वापस set_flags(child, value);

	हाल दुरत्व(काष्ठा user32, u_debugreg[0]) ...
		दुरत्व(काष्ठा user32, u_debugreg[7]):
		regno -= दुरत्व(काष्ठा user32, u_debugreg[0]);
		वापस ptrace_set_debugreg(child, regno / 4, value);

	शेष:
		अगर (regno > माप(काष्ठा user32) || (regno & 3))
			वापस -EIO;

		/*
		 * Other dummy fields in the भव user काष्ठाure
		 * are ignored
		 */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#अघोषित R32
#अघोषित SEG32

#घोषणा R32(l,q)							\
	हाल दुरत्व(काष्ठा user32, regs.l):				\
		*val = regs->q; अवरोध

#घोषणा SEG32(rs)							\
	हाल दुरत्व(काष्ठा user32, regs.rs):				\
		*val = get_segment_reg(child,				\
				       दुरत्व(काष्ठा user_regs_काष्ठा, rs)); \
		अवरोध

अटल पूर्णांक getreg32(काष्ठा task_काष्ठा *child, अचिन्हित regno, u32 *val)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(child);

	चयन (regno) अणु

	SEG32(ds);
	SEG32(es);
	SEG32(fs);
	SEG32(gs);

	R32(cs, cs);
	R32(ss, ss);
	R32(ebx, bx);
	R32(ecx, cx);
	R32(edx, dx);
	R32(edi, di);
	R32(esi, si);
	R32(ebp, bp);
	R32(eax, ax);
	R32(orig_eax, orig_ax);
	R32(eip, ip);
	R32(esp, sp);

	हाल दुरत्व(काष्ठा user32, regs.eflags):
		*val = get_flags(child);
		अवरोध;

	हाल दुरत्व(काष्ठा user32, u_debugreg[0]) ...
		दुरत्व(काष्ठा user32, u_debugreg[7]):
		regno -= दुरत्व(काष्ठा user32, u_debugreg[0]);
		*val = ptrace_get_debugreg(child, regno / 4);
		अवरोध;

	शेष:
		अगर (regno > माप(काष्ठा user32) || (regno & 3))
			वापस -EIO;

		/*
		 * Other dummy fields in the भव user काष्ठाure
		 * are ignored
		 */
		*val = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#अघोषित R32
#अघोषित SEG32

अटल पूर्णांक genregs32_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	पूर्णांक reg;

	क्रम (reg = 0; to.left; reg++) अणु
		u32 val;
		getreg32(target, reg * 4, &val);
		membuf_store(&to, val);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक genregs32_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret = 0;
	अगर (kbuf) अणु
		स्थिर compat_uदीर्घ_t *k = kbuf;
		जबतक (count >= माप(*k) && !ret) अणु
			ret = putreg32(target, pos, *k++);
			count -= माप(*k);
			pos += माप(*k);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर compat_uदीर्घ_t __user *u = ubuf;
		जबतक (count >= माप(*u) && !ret) अणु
			compat_uदीर्घ_t word;
			ret = __get_user(word, u++);
			अगर (ret)
				अवरोध;
			ret = putreg32(target, pos, word);
			count -= माप(*u);
			pos += माप(*u);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल दीर्घ ia32_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			     compat_uदीर्घ_t caddr, compat_uदीर्घ_t cdata)
अणु
	अचिन्हित दीर्घ addr = caddr;
	अचिन्हित दीर्घ data = cdata;
	व्योम __user *datap = compat_ptr(data);
	पूर्णांक ret;
	__u32 val;

	चयन (request) अणु
	हाल PTRACE_PEEKUSR:
		ret = getreg32(child, addr, &val);
		अगर (ret == 0)
			ret = put_user(val, (__u32 __user *)datap);
		अवरोध;

	हाल PTRACE_POKEUSR:
		ret = putreg32(child, addr, data);
		अवरोध;

	हाल PTRACE_GETREGS:	/* Get all gp regs from the child. */
		वापस copy_regset_to_user(child, &user_x86_32_view,
					   REGSET_GENERAL,
					   0, माप(काष्ठा user_regs_काष्ठा32),
					   datap);

	हाल PTRACE_SETREGS:	/* Set all gp regs in the child. */
		वापस copy_regset_from_user(child, &user_x86_32_view,
					     REGSET_GENERAL, 0,
					     माप(काष्ठा user_regs_काष्ठा32),
					     datap);

	हाल PTRACE_GETFPREGS:	/* Get the child FPU state. */
		वापस copy_regset_to_user(child, &user_x86_32_view,
					   REGSET_FP, 0,
					   माप(काष्ठा user_i387_ia32_काष्ठा),
					   datap);

	हाल PTRACE_SETFPREGS:	/* Set the child FPU state. */
		वापस copy_regset_from_user(
			child, &user_x86_32_view, REGSET_FP,
			0, माप(काष्ठा user_i387_ia32_काष्ठा), datap);

	हाल PTRACE_GETFPXREGS:	/* Get the child extended FPU state. */
		वापस copy_regset_to_user(child, &user_x86_32_view,
					   REGSET_XFP, 0,
					   माप(काष्ठा user32_fxsr_काष्ठा),
					   datap);

	हाल PTRACE_SETFPXREGS:	/* Set the child extended FPU state. */
		वापस copy_regset_from_user(child, &user_x86_32_view,
					     REGSET_XFP, 0,
					     माप(काष्ठा user32_fxsr_काष्ठा),
					     datap);

	हाल PTRACE_GET_THREAD_AREA:
	हाल PTRACE_SET_THREAD_AREA:
		वापस arch_ptrace(child, request, addr, data);

	शेष:
		वापस compat_ptrace_request(child, request, addr, data);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_IA32_EMULATION */

#अगर_घोषित CONFIG_X86_X32_ABI
अटल दीर्घ x32_arch_ptrace(काष्ठा task_काष्ठा *child,
			    compat_दीर्घ_t request, compat_uदीर्घ_t caddr,
			    compat_uदीर्घ_t cdata)
अणु
	अचिन्हित दीर्घ addr = caddr;
	अचिन्हित दीर्घ data = cdata;
	व्योम __user *datap = compat_ptr(data);
	पूर्णांक ret;

	चयन (request) अणु
	/* Read 32bits at location addr in the USER area.  Only allow
	   to वापस the lower 32bits of segment and debug रेजिस्टरs.  */
	हाल PTRACE_PEEKUSR: अणु
		u32 पंचांगp;

		ret = -EIO;
		अगर ((addr & (माप(data) - 1)) || addr >= माप(काष्ठा user) ||
		    addr < दुरत्व(काष्ठा user_regs_काष्ठा, cs))
			अवरोध;

		पंचांगp = 0;  /* Default वापस condition */
		अगर (addr < माप(काष्ठा user_regs_काष्ठा))
			पंचांगp = getreg(child, addr);
		अन्यथा अगर (addr >= दुरत्व(काष्ठा user, u_debugreg[0]) &&
			 addr <= दुरत्व(काष्ठा user, u_debugreg[7])) अणु
			addr -= दुरत्व(काष्ठा user, u_debugreg[0]);
			पंचांगp = ptrace_get_debugreg(child, addr / माप(data));
		पूर्ण
		ret = put_user(पंचांगp, (__u32 __user *)datap);
		अवरोध;
	पूर्ण

	/* Write the word at location addr in the USER area.  Only allow
	   to update segment and debug रेजिस्टरs with the upper 32bits
	   zero-extended. */
	हाल PTRACE_POKEUSR:
		ret = -EIO;
		अगर ((addr & (माप(data) - 1)) || addr >= माप(काष्ठा user) ||
		    addr < दुरत्व(काष्ठा user_regs_काष्ठा, cs))
			अवरोध;

		अगर (addr < माप(काष्ठा user_regs_काष्ठा))
			ret = putreg(child, addr, data);
		अन्यथा अगर (addr >= दुरत्व(काष्ठा user, u_debugreg[0]) &&
			 addr <= दुरत्व(काष्ठा user, u_debugreg[7])) अणु
			addr -= दुरत्व(काष्ठा user, u_debugreg[0]);
			ret = ptrace_set_debugreg(child,
						  addr / माप(data), data);
		पूर्ण
		अवरोध;

	हाल PTRACE_GETREGS:	/* Get all gp regs from the child. */
		वापस copy_regset_to_user(child,
					   &user_x86_64_view,
					   REGSET_GENERAL,
					   0, माप(काष्ठा user_regs_काष्ठा),
					   datap);

	हाल PTRACE_SETREGS:	/* Set all gp regs in the child. */
		वापस copy_regset_from_user(child,
					     &user_x86_64_view,
					     REGSET_GENERAL,
					     0, माप(काष्ठा user_regs_काष्ठा),
					     datap);

	हाल PTRACE_GETFPREGS:	/* Get the child FPU state. */
		वापस copy_regset_to_user(child,
					   &user_x86_64_view,
					   REGSET_FP,
					   0, माप(काष्ठा user_i387_काष्ठा),
					   datap);

	हाल PTRACE_SETFPREGS:	/* Set the child FPU state. */
		वापस copy_regset_from_user(child,
					     &user_x86_64_view,
					     REGSET_FP,
					     0, माप(काष्ठा user_i387_काष्ठा),
					     datap);

	शेष:
		वापस compat_ptrace_request(child, request, addr, data);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
दीर्घ compat_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			compat_uदीर्घ_t caddr, compat_uदीर्घ_t cdata)
अणु
#अगर_घोषित CONFIG_X86_X32_ABI
	अगर (!in_ia32_syscall())
		वापस x32_arch_ptrace(child, request, caddr, cdata);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IA32_EMULATION
	वापस ia32_arch_ptrace(child, request, caddr, cdata);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर	/* CONFIG_COMPAT */

#अगर_घोषित CONFIG_X86_64

अटल काष्ठा user_regset x86_64_regsets[] __ro_after_init = अणु
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = माप(काष्ठा user_regs_काष्ठा) / माप(दीर्घ),
		.size = माप(दीर्घ), .align = माप(दीर्घ),
		.regset_get = genregs_get, .set = genregs_set
	पूर्ण,
	[REGSET_FP] = अणु
		.core_note_type = NT_PRFPREG,
		.n = माप(काष्ठा user_i387_काष्ठा) / माप(दीर्घ),
		.size = माप(दीर्घ), .align = माप(दीर्घ),
		.active = regset_xregset_fpregs_active, .regset_get = xfpregs_get, .set = xfpregs_set
	पूर्ण,
	[REGSET_XSTATE] = अणु
		.core_note_type = NT_X86_XSTATE,
		.size = माप(u64), .align = माप(u64),
		.active = xstateregs_active, .regset_get = xstateregs_get,
		.set = xstateregs_set
	पूर्ण,
	[REGSET_IOPERM64] = अणु
		.core_note_type = NT_386_IOPERM,
		.n = IO_BITMAP_LONGS,
		.size = माप(दीर्घ), .align = माप(दीर्घ),
		.active = ioperm_active, .regset_get = ioperm_get
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_x86_64_view = अणु
	.name = "x86_64", .e_machine = EM_X86_64,
	.regsets = x86_64_regsets, .n = ARRAY_SIZE(x86_64_regsets)
पूर्ण;

#अन्यथा  /* CONFIG_X86_32 */

#घोषणा user_regs_काष्ठा32	user_regs_काष्ठा
#घोषणा genregs32_get		genregs_get
#घोषणा genregs32_set		genregs_set

#पूर्ण_अगर	/* CONFIG_X86_64 */

#अगर defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
अटल काष्ठा user_regset x86_32_regsets[] __ro_after_init = अणु
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = माप(काष्ठा user_regs_काष्ठा32) / माप(u32),
		.size = माप(u32), .align = माप(u32),
		.regset_get = genregs32_get, .set = genregs32_set
	पूर्ण,
	[REGSET_FP] = अणु
		.core_note_type = NT_PRFPREG,
		.n = माप(काष्ठा user_i387_ia32_काष्ठा) / माप(u32),
		.size = माप(u32), .align = माप(u32),
		.active = regset_fpregs_active, .regset_get = fpregs_get, .set = fpregs_set
	पूर्ण,
	[REGSET_XFP] = अणु
		.core_note_type = NT_PRXFPREG,
		.n = माप(काष्ठा user32_fxsr_काष्ठा) / माप(u32),
		.size = माप(u32), .align = माप(u32),
		.active = regset_xregset_fpregs_active, .regset_get = xfpregs_get, .set = xfpregs_set
	पूर्ण,
	[REGSET_XSTATE] = अणु
		.core_note_type = NT_X86_XSTATE,
		.size = माप(u64), .align = माप(u64),
		.active = xstateregs_active, .regset_get = xstateregs_get,
		.set = xstateregs_set
	पूर्ण,
	[REGSET_TLS] = अणु
		.core_note_type = NT_386_TLS,
		.n = GDT_ENTRY_TLS_ENTRIES, .bias = GDT_ENTRY_TLS_MIN,
		.size = माप(काष्ठा user_desc),
		.align = माप(काष्ठा user_desc),
		.active = regset_tls_active,
		.regset_get = regset_tls_get, .set = regset_tls_set
	पूर्ण,
	[REGSET_IOPERM32] = अणु
		.core_note_type = NT_386_IOPERM,
		.n = IO_BITMAP_BYTES / माप(u32),
		.size = माप(u32), .align = माप(u32),
		.active = ioperm_active, .regset_get = ioperm_get
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_x86_32_view = अणु
	.name = "i386", .e_machine = EM_386,
	.regsets = x86_32_regsets, .n = ARRAY_SIZE(x86_32_regsets)
पूर्ण;
#पूर्ण_अगर

/*
 * This represents bytes 464..511 in the memory layout exported through
 * the REGSET_XSTATE पूर्णांकerface.
 */
u64 xstate_fx_sw_bytes[USER_XSTATE_FX_SW_WORDS];

व्योम __init update_regset_xstate_info(अचिन्हित पूर्णांक size, u64 xstate_mask)
अणु
#अगर_घोषित CONFIG_X86_64
	x86_64_regsets[REGSET_XSTATE].n = size / माप(u64);
#पूर्ण_अगर
#अगर defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
	x86_32_regsets[REGSET_XSTATE].n = size / माप(u64);
#पूर्ण_अगर
	xstate_fx_sw_bytes[USER_XSTATE_XCR0_WORD] = xstate_mask;
पूर्ण

/*
 * This is used by the core dump code to decide which regset to dump.  The
 * core dump code ग_लिखोs out the resulting .e_machine and the corresponding
 * regsets.  This is suboptimal अगर the task is messing around with its CS.L
 * field, but at worst the core dump will end up missing some inक्रमmation.
 *
 * Unक्रमtunately, it is also used by the broken PTRACE_GETREGSET and
 * PTRACE_SETREGSET APIs.  These APIs look at the .regsets field but have
 * no way to make sure that the e_machine they use matches the caller's
 * expectations.  The result is that the data क्रमmat वापसed by
 * PTRACE_GETREGSET depends on the वापसed CS field (and even the offset
 * of the वापसed CS field depends on its value!) and the data क्रमmat
 * accepted by PTRACE_SETREGSET is determined by the old CS value.  The
 * upshot is that it is basically impossible to use these APIs correctly.
 *
 * The best way to fix it in the दीर्घ run would probably be to add new
 * improved ptrace() APIs to पढ़ो and ग_लिखो रेजिस्टरs reliably, possibly by
 * allowing userspace to select the ELF e_machine variant that they expect.
 */
स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_IA32_EMULATION
	अगर (!user_64bit_mode(task_pt_regs(task)))
#पूर्ण_अगर
#अगर defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
		वापस &user_x86_32_view;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_64
	वापस &user_x86_64_view;
#पूर्ण_अगर
पूर्ण

व्योम send_sigtrap(काष्ठा pt_regs *regs, पूर्णांक error_code, पूर्णांक si_code)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	tsk->thपढ़ो.trap_nr = X86_TRAP_DB;
	tsk->thपढ़ो.error_code = error_code;

	/* Send us the fake SIGTRAP */
	क्रमce_sig_fault(SIGTRAP, si_code,
			user_mode(regs) ? (व्योम __user *)regs->ip : शून्य);
पूर्ण

व्योम user_single_step_report(काष्ठा pt_regs *regs)
अणु
	send_sigtrap(regs, 0, TRAP_BRKPT);
पूर्ण
