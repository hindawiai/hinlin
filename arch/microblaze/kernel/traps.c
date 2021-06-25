<शैली गुरु>
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/debug_locks.h>

#समावेश <यंत्र/exceptions.h>
#समावेश <यंत्र/unwind.h>

व्योम trap_init(व्योम)
अणु
	__enable_hw_exceptions();
पूर्ण

अटल अचिन्हित दीर्घ kstack_depth_to_prपूर्णांक;	/* 0 == entire stack */

अटल पूर्णांक __init kstack_setup(अक्षर *s)
अणु
	वापस !kम_से_अदीर्घ(s, 0, &kstack_depth_to_prपूर्णांक);
पूर्ण
__setup("kstack=", kstack_setup);

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ words_to_show;
	u32 fp = (u32) sp;

	अगर (fp == 0) अणु
		अगर (task) अणु
			fp = ((काष्ठा thपढ़ो_info *)
				(task->stack))->cpu_context.r1;
		पूर्ण अन्यथा अणु
			/* Pick up caller of dump_stack() */
			fp = (u32)&sp - 8;
		पूर्ण
	पूर्ण

	words_to_show = (THREAD_SIZE - (fp & (THREAD_SIZE - 1))) >> 2;
	अगर (kstack_depth_to_prपूर्णांक && (words_to_show > kstack_depth_to_prपूर्णांक))
		words_to_show = kstack_depth_to_prपूर्णांक;

	prपूर्णांकk("%sKernel Stack:\n", loglvl);

	/*
	 * Make the first line an 'odd' size अगर necessary to get
	 * reमुख्यing lines to start at an address multiple of 0x10
	 */
	अगर (fp & 0xF) अणु
		अचिन्हित दीर्घ line1_words = (0x10 - (fp & 0xF)) >> 2;
		अगर (line1_words < words_to_show) अणु
			prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS, 32,
				       4, (व्योम *)fp, line1_words << 2, 0);
			fp += line1_words << 2;
			words_to_show -= line1_words;
		पूर्ण
	पूर्ण
	prपूर्णांक_hex_dump(loglvl, "", DUMP_PREFIX_ADDRESS, 32, 4, (व्योम *)fp,
		       words_to_show << 2, 0);
	prपूर्णांकk("%s\n\nCall Trace:\n", loglvl);
	microblaze_unwind(task, शून्य, loglvl);
	prपूर्णांकk("%s\n", loglvl);

	अगर (!task)
		task = current;

	debug_show_held_locks(task);
पूर्ण
