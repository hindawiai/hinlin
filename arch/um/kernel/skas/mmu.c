<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sections.h>
#समावेश <as-layout.h>
#समावेश <os.h>
#समावेश <skas.h>

पूर्णांक init_new_context(काष्ठा task_काष्ठा *task, काष्ठा mm_काष्ठा *mm)
अणु
 	काष्ठा mm_context *from_mm = शून्य;
	काष्ठा mm_context *to_mm = &mm->context;
	अचिन्हित दीर्घ stack = 0;
	पूर्णांक ret = -ENOMEM;

	stack = get_zeroed_page(GFP_KERNEL);
	अगर (stack == 0)
		जाओ out;

	to_mm->id.stack = stack;
	अगर (current->mm != शून्य && current->mm != &init_mm)
		from_mm = &current->mm->context;

	block_संकेतs_trace();
	अगर (from_mm)
		to_mm->id.u.pid = copy_context_skas0(stack,
						     from_mm->id.u.pid);
	अन्यथा to_mm->id.u.pid = start_userspace(stack);
	unblock_संकेतs_trace();

	अगर (to_mm->id.u.pid < 0) अणु
		ret = to_mm->id.u.pid;
		जाओ out_मुक्त;
	पूर्ण

	ret = init_new_ldt(to_mm, from_mm);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "init_new_context_skas - init_ldt"
		       " failed, errno = %d\n", ret);
		जाओ out_मुक्त;
	पूर्ण

	वापस 0;

 out_मुक्त:
	अगर (to_mm->id.stack != 0)
		मुक्त_page(to_mm->id.stack);
 out:
	वापस ret;
पूर्ण

व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mm_context *mmu = &mm->context;

	/*
	 * If init_new_context wasn't called, this will be
	 * zero, resulting in a समाप्त(0), which will result in the
	 * whole UML suddenly dying.  Also, cover negative and
	 * 1 हालs, since they shouldn't happen either.
	 */
	अगर (mmu->id.u.pid < 2) अणु
		prपूर्णांकk(KERN_ERR "corrupt mm_context - pid = %d\n",
		       mmu->id.u.pid);
		वापस;
	पूर्ण
	os_समाप्त_ptraced_process(mmu->id.u.pid, 1);

	मुक्त_page(mmu->id.stack);
	मुक्त_ldt(mmu);
पूर्ण
