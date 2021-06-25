<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * This file handles the architecture independent parts of process handling..
 */

#समावेश <linux/compat.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/संकेत.स>

#समावेश "kernel.h"

यंत्रlinkage दीर्घ sparc_विभाजन(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_i1 = regs->u_regs[UREG_I1];
	दीर्घ ret;
	काष्ठा kernel_clone_args args = अणु
		.निकास_संकेत	= SIGCHLD,
		/* Reuse the parent's stack क्रम the child. */
		.stack		= regs->u_regs[UREG_FP],
	पूर्ण;

	ret = kernel_clone(&args);

	/* If we get an error and potentially restart the प्रणाली
	 * call, we're screwed because copy_thपढ़ो() clobbered
	 * the parent's %o1.  So detect that हाल and restore it
	 * here.
	 */
	अगर ((अचिन्हित दीर्घ)ret >= -ERESTART_RESTARTBLOCK)
		regs->u_regs[UREG_I1] = orig_i1;

	वापस ret;
पूर्ण

यंत्रlinkage दीर्घ sparc_vविभाजन(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_i1 = regs->u_regs[UREG_I1];
	दीर्घ ret;

	काष्ठा kernel_clone_args args = अणु
		.flags		= CLONE_VFORK | CLONE_VM,
		.निकास_संकेत	= SIGCHLD,
		/* Reuse the parent's stack क्रम the child. */
		.stack		= regs->u_regs[UREG_FP],
	पूर्ण;

	ret = kernel_clone(&args);

	/* If we get an error and potentially restart the प्रणाली
	 * call, we're screwed because copy_thपढ़ो() clobbered
	 * the parent's %o1.  So detect that हाल and restore it
	 * here.
	 */
	अगर ((अचिन्हित दीर्घ)ret >= -ERESTART_RESTARTBLOCK)
		regs->u_regs[UREG_I1] = orig_i1;

	वापस ret;
पूर्ण

यंत्रlinkage दीर्घ sparc_clone(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ orig_i1 = regs->u_regs[UREG_I1];
	अचिन्हित पूर्णांक flags = lower_32_bits(regs->u_regs[UREG_I0]);
	दीर्घ ret;

	काष्ठा kernel_clone_args args = अणु
		.flags		= (flags & ~CSIGNAL),
		.निकास_संकेत	= (flags & CSIGNAL),
		.tls		= regs->u_regs[UREG_I3],
	पूर्ण;

#अगर_घोषित CONFIG_COMPAT
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		args.pidfd	= compat_ptr(regs->u_regs[UREG_I2]);
		args.child_tid	= compat_ptr(regs->u_regs[UREG_I4]);
		args.parent_tid	= compat_ptr(regs->u_regs[UREG_I2]);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		args.pidfd	= (पूर्णांक __user *)regs->u_regs[UREG_I2];
		args.child_tid	= (पूर्णांक __user *)regs->u_regs[UREG_I4];
		args.parent_tid	= (पूर्णांक __user *)regs->u_regs[UREG_I2];
	पूर्ण

	/* Did userspace give setup a separate stack क्रम the child or are we
	 * reusing the parent's?
	 */
	अगर (regs->u_regs[UREG_I1])
		args.stack = regs->u_regs[UREG_I1];
	अन्यथा
		args.stack = regs->u_regs[UREG_FP];

	ret = kernel_clone(&args);

	/* If we get an error and potentially restart the प्रणाली
	 * call, we're screwed because copy_thपढ़ो() clobbered
	 * the parent's %o1.  So detect that हाल and restore it
	 * here.
	 */
	अगर ((अचिन्हित दीर्घ)ret >= -ERESTART_RESTARTBLOCK)
		regs->u_regs[UREG_I1] = orig_i1;

	वापस ret;
पूर्ण
