<शैली गुरु>
/*
 * Copyright (C) 2003 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright 2003 PathScale, Inc.
 *
 * Licensed under the GPL
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/prctl.h> /* XXX This should get the स्थिरants from libc */
#समावेश <os.h>

दीर्घ arch_prctl(काष्ठा task_काष्ठा *task, पूर्णांक option,
		अचिन्हित दीर्घ __user *arg2)
अणु
	अचिन्हित दीर्घ *ptr = arg2, पंचांगp;
	दीर्घ ret;
	पूर्णांक pid = task->mm->context.id.u.pid;

	/*
	 * With ARCH_SET_FS (and ARCH_SET_GS is treated similarly to
	 * be safe), we need to call arch_prctl on the host because
	 * setting %fs may result in something अन्यथा happening (like a
	 * GDT or thपढ़ो.fs being set instead).  So, we let the host
	 * fiddle the रेजिस्टरs and thपढ़ो काष्ठा and restore the
	 * रेजिस्टरs afterwards.
	 *
	 * So, the saved रेजिस्टरs are stored to the process (this
	 * needed because a stub may have been the last thing to run),
	 * arch_prctl is run on the host, then the रेजिस्टरs are पढ़ो
	 * back.
	 */
	चयन (option) अणु
	हाल ARCH_SET_FS:
	हाल ARCH_SET_GS:
		ret = restore_रेजिस्टरs(pid, &current->thपढ़ो.regs.regs);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल ARCH_GET_FS:
	हाल ARCH_GET_GS:
		/*
		 * With these two, we पढ़ो to a local poपूर्णांकer and
		 * put_user it to the userspace poपूर्णांकer that we were
		 * given.  If addr isn't valid (because it hasn't been
		 * faulted in or is just bogus), we want put_user to
		 * fault it in (or वापस -EFAULT) instead of having
		 * the host वापस -EFAULT.
		 */
		ptr = &पंचांगp;
	पूर्ण

	ret = os_arch_prctl(pid, option, ptr);
	अगर (ret)
		वापस ret;

	चयन (option) अणु
	हाल ARCH_SET_FS:
		current->thपढ़ो.arch.fs = (अचिन्हित दीर्घ) ptr;
		ret = save_रेजिस्टरs(pid, &current->thपढ़ो.regs.regs);
		अवरोध;
	हाल ARCH_SET_GS:
		ret = save_रेजिस्टरs(pid, &current->thपढ़ो.regs.regs);
		अवरोध;
	हाल ARCH_GET_FS:
		ret = put_user(पंचांगp, arg2);
		अवरोध;
	हाल ARCH_GET_GS:
		ret = put_user(पंचांगp, arg2);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE2(arch_prctl, पूर्णांक, option, अचिन्हित दीर्घ, arg2)
अणु
	वापस arch_prctl(current, option, (अचिन्हित दीर्घ __user *) arg2);
पूर्ण

व्योम arch_चयन_to(काष्ठा task_काष्ठा *to)
अणु
	अगर ((to->thपढ़ो.arch.fs == 0) || (to->mm == शून्य))
		वापस;

	arch_prctl(to, ARCH_SET_FS, (व्योम __user *) to->thपढ़ो.arch.fs);
पूर्ण
