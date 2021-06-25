<शैली गुरु>
/*
 *  linux/arch/h8300/kernel/ptrace.c
 *
 *  Copyright 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of
 * this archive क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/audit.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/regset.h>
#समावेश <linux/elf.h>

#घोषणा CCR_MASK 0x6f    /* mode/imask not set */
#घोषणा EXR_MASK 0x80    /* modअगरy only T */

#घोषणा PT_REG(r) दुरत्व(काष्ठा pt_regs, r)

बाह्य व्योम user_disable_single_step(काष्ठा task_काष्ठा *child);

/* Mapping from PT_xxx to the stack offset at which the रेजिस्टर is
   saved.  Notice that usp has no stack-slot and needs to be treated
   specially (see get_reg/put_reg below). */
अटल स्थिर पूर्णांक रेजिस्टर_offset[] = अणु
	PT_REG(er1), PT_REG(er2), PT_REG(er3), PT_REG(er4),
	PT_REG(er5), PT_REG(er6), PT_REG(er0), -1,
	PT_REG(orig_er0), PT_REG(ccr), PT_REG(pc),
#अगर defined(CONFIG_CPU_H8S)
	PT_REG(exr),
#पूर्ण_अगर
पूर्ण;

/* पढ़ो रेजिस्टर */
दीर्घ h8300_get_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno)
अणु
	चयन (regno) अणु
	हाल PT_USP:
		वापस task->thपढ़ो.usp + माप(दीर्घ)*2;
	हाल PT_CCR:
	हाल PT_EXR:
	    वापस *(अचिन्हित लघु *)(task->thपढ़ो.esp0 +
				       रेजिस्टर_offset[regno]);
	शेष:
	    वापस *(अचिन्हित दीर्घ *)(task->thपढ़ो.esp0 +
				      रेजिस्टर_offset[regno]);
	पूर्ण
पूर्ण

पूर्णांक h8300_put_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno, अचिन्हित दीर्घ data)
अणु
	अचिन्हित लघु oldccr;
	अचिन्हित लघु oldexr;

	चयन (regno) अणु
	हाल PT_USP:
		task->thपढ़ो.usp = data - माप(दीर्घ)*2;
	हाल PT_CCR:
		oldccr = *(अचिन्हित लघु *)(task->thपढ़ो.esp0 +
					     रेजिस्टर_offset[regno]);
		oldccr &= ~CCR_MASK;
		data &= CCR_MASK;
		data |= oldccr;
		*(अचिन्हित लघु *)(task->thपढ़ो.esp0 +
				    रेजिस्टर_offset[regno]) = data;
		अवरोध;
	हाल PT_EXR:
		oldexr = *(अचिन्हित लघु *)(task->thपढ़ो.esp0 +
					     रेजिस्टर_offset[regno]);
		oldccr &= ~EXR_MASK;
		data &= EXR_MASK;
		data |= oldexr;
		*(अचिन्हित लघु *)(task->thपढ़ो.esp0 +
				    रेजिस्टर_offset[regno]) = data;
		अवरोध;
	शेष:
		*(अचिन्हित दीर्घ *)(task->thपढ़ो.esp0 +
				   रेजिस्टर_offset[regno]) = data;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक regs_get(काष्ठा task_काष्ठा *target,
		    स्थिर काष्ठा user_regset *regset,
		    काष्ठा membuf to)
अणु
	पूर्णांक r;

	BUILD_BUG_ON(माप(काष्ठा user_regs_काष्ठा) % माप(दीर्घ) != 0);
	क्रम (r = 0; r < ELF_NGREG; r++)
		membuf_store(&to, h8300_get_reg(target, r));

	वापस 0;
पूर्ण

अटल पूर्णांक regs_set(काष्ठा task_काष्ठा *target,
		    स्थिर काष्ठा user_regset *regset,
		    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक r;
	पूर्णांक ret;
	काष्ठा user_regs_काष्ठा regs;
	दीर्घ *reg;

	/* build user regs in buffer */
	BUILD_BUG_ON(माप(regs) % माप(दीर्घ) != 0);
	क्रम (reg = (दीर्घ *)&regs, r = 0; r < माप(regs) / माप(दीर्घ); r++)
		*reg++ = h8300_get_reg(target, r);

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &regs, 0, माप(regs));
	अगर (ret)
		वापस ret;

	/* ग_लिखो back to pt_regs */
	क्रम (reg = (दीर्घ *)&regs, r = 0; r < माप(regs) / माप(दीर्घ); r++)
		h8300_put_reg(target, r, *reg++);
	वापस 0;
पूर्ण

क्रमागत h8300_regset अणु
	REGSET_GENERAL,
पूर्ण;

अटल स्थिर काष्ठा user_regset h8300_regsets[] = अणु
	[REGSET_GENERAL] = अणु
		.core_note_type	= NT_PRSTATUS,
		.n		= ELF_NGREG,
		.size		= माप(दीर्घ),
		.align		= माप(दीर्घ),
		.regset_get		= regs_get,
		.set		= regs_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_h8300_native_view = अणु
	.name = "h8300",
	.e_machine = EM_H8_300,
	.regsets = h8300_regsets,
	.n = ARRAY_SIZE(h8300_regsets),
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &user_h8300_native_view;
पूर्ण

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	user_disable_single_step(child);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret;

	चयन (request) अणु
	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

यंत्रlinkage दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	दीर्घ ret = 0;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE) &&
	    tracehook_report_syscall_entry(regs))
		/*
		 * Tracing decided this syscall should not happen.
		 * We'll वापस a bogus call number to get an ENOSYS
		 * error, but leave the original number in regs->regs[0].
		 */
		ret = -1L;

	audit_syscall_entry(regs->er1, regs->er2, regs->er3,
			    regs->er4, regs->er5);

	वापस ret ?: regs->er0;
पूर्ण

यंत्रlinkage व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	पूर्णांक step;

	audit_syscall_निकास(regs);

	step = test_thपढ़ो_flag(TIF_SINGLESTEP);
	अगर (step || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, step);
पूर्ण
