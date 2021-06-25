<शैली गुरु>
/*
 * Backtrace support क्रम Microblaze
 *
 * Copyright (C) 2010  Digital Design Corporation
 *
 * Based on arch/sh/kernel/cpu/sh5/unwind.c code which is:
 * Copyright (C) 2004  Paul Mundt
 * Copyright (C) 2004  Riअक्षरd Curnow
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

/* #घोषणा DEBUG 1 */
#समावेश <linux/export.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/exceptions.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/चयन_to.h>

काष्ठा stack_trace;

/*
 * On Microblaze, finding the previous stack frame is a little tricky.
 * At this writing (3/2010), Microblaze करोes not support CONFIG_FRAME_POINTERS,
 * and even अगर it did, gcc (4.1.2) करोes not store the frame poपूर्णांकer at
 * a consistent offset within each frame. To determine frame size, it is
 * necessary to search क्रम the assembly inकाष्ठाion that creates or reclaims
 * the frame and extract the size from it.
 *
 * Microblaze stores the stack poपूर्णांकer in r1, and creates a frame via
 *
 *     addik r1, r1, -FRAME_SIZE
 *
 * The frame is reclaimed via
 *
 *     addik r1, r1, FRAME_SIZE
 *
 * Frame creation occurs at or near the top of a function.
 * Depending on the compiler, reclaim may occur at the end, or beक्रमe
 * a mid-function वापस.
 *
 * A stack frame is usually not created in a leaf function.
 *
 */

/**
 * get_frame_size - Extract the stack adjusपंचांगent from an
 *                  "addik r1, r1, adjust" inकाष्ठाion
 * @instr : Microblaze inकाष्ठाion
 *
 * Return - Number of stack bytes the inकाष्ठाion reserves or reclaims
 */
अटल अंतरभूत दीर्घ get_frame_size(अचिन्हित दीर्घ instr)
अणु
	वापस असल((s16)(instr & 0xFFFF));
पूर्ण

/**
 * find_frame_creation - Search backward to find the inकाष्ठाion that creates
 *                       the stack frame (hopefully, क्रम the same function the
 *                       initial PC is in).
 * @pc : Program counter at which to begin the search
 *
 * Return - PC at which stack frame creation occurs
 *          शून्य अगर this cannot be found, i.e. a leaf function
 */
अटल अचिन्हित दीर्घ *find_frame_creation(अचिन्हित दीर्घ *pc)
अणु
	पूर्णांक i;

	/* NOTE: Distance to search is arbitrary
	 *	 250 works well क्रम most things,
	 *	 750 picks up things like tcp_recvmsg(),
	 *	1000 needed क्रम fat_fill_super()
	 */
	क्रम (i = 0; i < 1000; i++, pc--) अणु
		अचिन्हित दीर्घ instr;
		s16 frame_size;

		अगर (!kernel_text_address((अचिन्हित दीर्घ) pc))
			वापस शून्य;

		instr = *pc;

		/* addik r1, r1, foo ? */
		अगर ((instr & 0xFFFF0000) != 0x30210000)
			जारी;	/* No */

		frame_size = get_frame_size(instr);
		अगर ((frame_size < 8) || (frame_size & 3)) अणु
			pr_debug("    Invalid frame size %d at 0x%p\n",
				 frame_size, pc);
			वापस शून्य;
		पूर्ण

		pr_debug("    Found frame creation at 0x%p, size %d\n", pc,
			 frame_size);
		वापस pc;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * lookup_prev_stack_frame - Find the stack frame of the previous function.
 * @fp          : Frame (stack) poपूर्णांकer क्रम current function
 * @pc          : Program counter within current function
 * @leaf_वापस : r15 value within current function. If the current function
 *		  is a leaf, this is the caller's वापस address.
 * @pprev_fp    : On निकास, set to frame (stack) poपूर्णांकer क्रम previous function
 * @pprev_pc    : On निकास, set to current function caller's वापस address
 *
 * Return - 0 on success, -EINVAL अगर the previous frame cannot be found
 */
अटल पूर्णांक lookup_prev_stack_frame(अचिन्हित दीर्घ fp, अचिन्हित दीर्घ pc,
				   अचिन्हित दीर्घ leaf_वापस,
				   अचिन्हित दीर्घ *pprev_fp,
				   अचिन्हित दीर्घ *pprev_pc)
अणु
	अचिन्हित दीर्घ *prologue = शून्य;

	/* _चयन_to is a special leaf function */
	अगर (pc != (अचिन्हित दीर्घ) &_चयन_to)
		prologue = find_frame_creation((अचिन्हित दीर्घ *)pc);

	अगर (prologue) अणु
		दीर्घ frame_size = get_frame_size(*prologue);

		*pprev_fp = fp + frame_size;
		*pprev_pc = *(अचिन्हित दीर्घ *)fp;
	पूर्ण अन्यथा अणु
		अगर (!leaf_वापस)
			वापस -EINVAL;
		*pprev_pc = leaf_वापस;
		*pprev_fp = fp;
	पूर्ण

	/* NOTE: करोn't check kernel_text_address here, to allow display
	 *	 of userland वापस address
	 */
	वापस (!*pprev_pc || (*pprev_pc & 3)) ? -EINVAL : 0;
पूर्ण

अटल व्योम microblaze_unwind_inner(काष्ठा task_काष्ठा *task,
				    अचिन्हित दीर्घ pc, अचिन्हित दीर्घ fp,
				    अचिन्हित दीर्घ leaf_वापस,
				    काष्ठा stack_trace *trace,
				    स्थिर अक्षर *loglvl);

/**
 * unwind_trap - Unwind through a प्रणाली trap, that stored previous state
 *		 on the stack.
 */
अटल अंतरभूत व्योम unwind_trap(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ pc,
				अचिन्हित दीर्घ fp, काष्ठा stack_trace *trace,
				स्थिर अक्षर *loglvl)
अणु
	/* To be implemented */
पूर्ण

/**
 * microblaze_unwind_inner - Unwind the stack from the specअगरied poपूर्णांक
 * @task  : Task whose stack we are to unwind (may be शून्य)
 * @pc    : Program counter from which we start unwinding
 * @fp    : Frame (stack) poपूर्णांकer from which we start unwinding
 * @leaf_वापस : Value of r15 at pc. If the function is a leaf, this is
 *				  the caller's वापस address.
 * @trace : Where to store stack backtrace (PC values).
 *	    शून्य == prपूर्णांक backtrace to kernel log
 * @loglvl : Used क्रम prपूर्णांकk log level अगर (trace == शून्य).
 */
अटल व्योम microblaze_unwind_inner(काष्ठा task_काष्ठा *task,
			     अचिन्हित दीर्घ pc, अचिन्हित दीर्घ fp,
			     अचिन्हित दीर्घ leaf_वापस,
			     काष्ठा stack_trace *trace,
			     स्थिर अक्षर *loglvl)
अणु
	पूर्णांक ofs = 0;

	pr_debug("    Unwinding with PC=%p, FP=%p\n", (व्योम *)pc, (व्योम *)fp);
	अगर (!pc || !fp || (pc & 3) || (fp & 3)) अणु
		pr_debug("    Invalid state for unwind, aborting\n");
		वापस;
	पूर्ण
	क्रम (; pc != 0;) अणु
		अचिन्हित दीर्घ next_fp, next_pc = 0;
		अचिन्हित दीर्घ वापस_to = pc +  2 * माप(अचिन्हित दीर्घ);
		स्थिर काष्ठा trap_handler_info *handler =
			&microblaze_trap_handlers;

		/* Is previous function the HW exception handler? */
		अगर ((वापस_to >= (अचिन्हित दीर्घ)&_hw_exception_handler)
		    &&(वापस_to < (अचिन्हित दीर्घ)&ex_handler_unhandled)) अणु
			/*
			 * HW exception handler करोesn't save all रेजिस्टरs,
			 * so we खोलो-code a special हाल of unwind_trap()
			 */
			prपूर्णांकk("%sHW EXCEPTION\n", loglvl);
			वापस;
		पूर्ण

		/* Is previous function a trap handler? */
		क्रम (; handler->start_addr; ++handler) अणु
			अगर ((वापस_to >= handler->start_addr)
			    && (वापस_to <= handler->end_addr)) अणु
				अगर (!trace)
					prपूर्णांकk("%s%s\n", loglvl, handler->trap_name);
				unwind_trap(task, pc, fp, trace, loglvl);
				वापस;
			पूर्ण
		पूर्ण
		pc -= ofs;

		अगर (trace) अणु
#अगर_घोषित CONFIG_STACKTRACE
			अगर (trace->skip > 0)
				trace->skip--;
			अन्यथा
				trace->entries[trace->nr_entries++] = pc;

			अगर (trace->nr_entries >= trace->max_entries)
				अवरोध;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			/* Have we reached userland? */
			अगर (unlikely(pc == task_pt_regs(task)->pc)) अणु
				prपूर्णांकk("%s[<%p>] PID %lu [%s]\n",
					loglvl, (व्योम *) pc,
					(अचिन्हित दीर्घ) task->pid,
					task->comm);
				अवरोध;
			पूर्ण अन्यथा
				prपूर्णांक_ip_sym(loglvl, pc);
		पूर्ण

		/* Stop when we reach anything not part of the kernel */
		अगर (!kernel_text_address(pc))
			अवरोध;

		अगर (lookup_prev_stack_frame(fp, pc, leaf_वापस, &next_fp,
					    &next_pc) == 0) अणु
			ofs = माप(अचिन्हित दीर्घ);
			pc = next_pc & ~3;
			fp = next_fp;
			leaf_वापस = 0;
		पूर्ण अन्यथा अणु
			pr_debug("    Failed to find previous stack frame\n");
			अवरोध;
		पूर्ण

		pr_debug("    Next PC=%p, next FP=%p\n",
			 (व्योम *)next_pc, (व्योम *)next_fp);
	पूर्ण
पूर्ण

/**
 * microblaze_unwind - Stack unwinder क्रम Microblaze (बाह्यal entry poपूर्णांक)
 * @task  : Task whose stack we are to unwind (शून्य == current)
 * @trace : Where to store stack backtrace (PC values).
 *	    शून्य == prपूर्णांक backtrace to kernel log
 * @loglvl : Used क्रम prपूर्णांकk log level अगर (trace == शून्य).
 */
व्योम microblaze_unwind(काष्ठा task_काष्ठा *task, काष्ठा stack_trace *trace,
		       स्थिर अक्षर *loglvl)
अणु
	अगर (task) अणु
		अगर (task == current) अणु
			स्थिर काष्ठा pt_regs *regs = task_pt_regs(task);
			microblaze_unwind_inner(task, regs->pc, regs->r1,
						regs->r15, trace, loglvl);
		पूर्ण अन्यथा अणु
			काष्ठा thपढ़ो_info *thपढ़ो_info =
				(काष्ठा thपढ़ो_info *)(task->stack);
			स्थिर काष्ठा cpu_context *cpu_context =
				&thपढ़ो_info->cpu_context;

			microblaze_unwind_inner(task,
						(अचिन्हित दीर्घ) &_चयन_to,
						cpu_context->r1,
						cpu_context->r15,
						trace, loglvl);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ pc, fp;

		__यंत्र__ __अस्थिर__ ("or %0, r1, r0" : "=r" (fp));

		__यंत्र__ __अस्थिर__ (
			"brlid %0, 0f;"
			"nop;"
			"0:"
			: "=r" (pc)
		);

		/* Since we are not a leaf function, use leaf_वापस = 0 */
		microblaze_unwind_inner(current, pc, fp, 0, trace, loglvl);
	पूर्ण
पूर्ण

