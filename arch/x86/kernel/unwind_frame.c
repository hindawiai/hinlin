<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/unwind.h>

#घोषणा FRAME_HEADER_SIZE (माप(दीर्घ) * 2)

अचिन्हित दीर्घ unwind_get_वापस_address(काष्ठा unwind_state *state)
अणु
	अगर (unwind_करोne(state))
		वापस 0;

	वापस __kernel_text_address(state->ip) ? state->ip : 0;
पूर्ण
EXPORT_SYMBOL_GPL(unwind_get_वापस_address);

अचिन्हित दीर्घ *unwind_get_वापस_address_ptr(काष्ठा unwind_state *state)
अणु
	अगर (unwind_करोne(state))
		वापस शून्य;

	वापस state->regs ? &state->regs->ip : state->bp + 1;
पूर्ण

अटल व्योम unwind_dump(काष्ठा unwind_state *state)
अणु
	अटल bool dumped_beक्रमe = false;
	bool prev_zero, zero = false;
	अचिन्हित दीर्घ word, *sp;
	काष्ठा stack_info stack_info = अणु0पूर्ण;
	अचिन्हित दीर्घ visit_mask = 0;

	अगर (dumped_beक्रमe)
		वापस;

	dumped_beक्रमe = true;

	prपूर्णांकk_deferred("unwind stack type:%d next_sp:%p mask:0x%lx graph_idx:%d\n",
			state->stack_info.type, state->stack_info.next_sp,
			state->stack_mask, state->graph_idx);

	क्रम (sp = PTR_ALIGN(state->orig_sp, माप(दीर्घ)); sp;
	     sp = PTR_ALIGN(stack_info.next_sp, माप(दीर्घ))) अणु
		अगर (get_stack_info(sp, state->task, &stack_info, &visit_mask))
			अवरोध;

		क्रम (; sp < stack_info.end; sp++) अणु

			word = READ_ONCE_NOCHECK(*sp);

			prev_zero = zero;
			zero = word == 0;

			अगर (zero) अणु
				अगर (!prev_zero)
					prपूर्णांकk_deferred("%p: %0*x ...\n",
							sp, BITS_PER_LONG/4, 0);
				जारी;
			पूर्ण

			prपूर्णांकk_deferred("%p: %0*lx (%pB)\n",
					sp, BITS_PER_LONG/4, word, (व्योम *)word);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool in_entry_code(अचिन्हित दीर्घ ip)
अणु
	अक्षर *addr = (अक्षर *)ip;

	वापस addr >= __entry_text_start && addr < __entry_text_end;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *last_frame(काष्ठा unwind_state *state)
अणु
	वापस (अचिन्हित दीर्घ *)task_pt_regs(state->task) - 2;
पूर्ण

अटल bool is_last_frame(काष्ठा unwind_state *state)
अणु
	वापस state->bp == last_frame(state);
पूर्ण

#अगर_घोषित CONFIG_X86_32
#घोषणा GCC_REALIGN_WORDS 3
#अन्यथा
#घोषणा GCC_REALIGN_WORDS 1
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ *last_aligned_frame(काष्ठा unwind_state *state)
अणु
	वापस last_frame(state) - GCC_REALIGN_WORDS;
पूर्ण

अटल bool is_last_aligned_frame(काष्ठा unwind_state *state)
अणु
	अचिन्हित दीर्घ *last_bp = last_frame(state);
	अचिन्हित दीर्घ *aligned_bp = last_aligned_frame(state);

	/*
	 * GCC can occasionally decide to realign the stack poपूर्णांकer and change
	 * the offset of the stack frame in the prologue of a function called
	 * by head/entry code.  Examples:
	 *
	 * <start_secondary>:
	 *      push   %edi
	 *      lea    0x8(%esp),%edi
	 *      and    $0xfffffff8,%esp
	 *      pushl  -0x4(%edi)
	 *      push   %ebp
	 *      mov    %esp,%ebp
	 *
	 * <x86_64_start_kernel>:
	 *      lea    0x8(%rsp),%r10
	 *      and    $0xfffffffffffffff0,%rsp
	 *      pushq  -0x8(%r10)
	 *      push   %rbp
	 *      mov    %rsp,%rbp
	 *
	 * After aligning the stack, it pushes a duplicate copy of the वापस
	 * address beक्रमe pushing the frame poपूर्णांकer.
	 */
	वापस (state->bp == aligned_bp && *(aligned_bp + 1) == *(last_bp + 1));
पूर्ण

अटल bool is_last_ftrace_frame(काष्ठा unwind_state *state)
अणु
	अचिन्हित दीर्घ *last_bp = last_frame(state);
	अचिन्हित दीर्घ *last_ftrace_bp = last_bp - 3;

	/*
	 * When unwinding from an ftrace handler of a function called by entry
	 * code, the stack layout of the last frame is:
	 *
	 *   bp
	 *   parent ret addr
	 *   bp
	 *   function ret addr
	 *   parent ret addr
	 *   pt_regs
	 *   -----------------
	 */
	वापस (state->bp == last_ftrace_bp &&
		*state->bp == *(state->bp + 2) &&
		*(state->bp + 1) == *(state->bp + 4));
पूर्ण

अटल bool is_last_task_frame(काष्ठा unwind_state *state)
अणु
	वापस is_last_frame(state) || is_last_aligned_frame(state) ||
	       is_last_ftrace_frame(state);
पूर्ण

/*
 * This determines अगर the frame poपूर्णांकer actually contains an encoded poपूर्णांकer to
 * pt_regs on the stack.  See ENCODE_FRAME_POINTER.
 */
#अगर_घोषित CONFIG_X86_64
अटल काष्ठा pt_regs *decode_frame_poपूर्णांकer(अचिन्हित दीर्घ *bp)
अणु
	अचिन्हित दीर्घ regs = (अचिन्हित दीर्घ)bp;

	अगर (!(regs & 0x1))
		वापस शून्य;

	वापस (काष्ठा pt_regs *)(regs & ~0x1);
पूर्ण
#अन्यथा
अटल काष्ठा pt_regs *decode_frame_poपूर्णांकer(अचिन्हित दीर्घ *bp)
अणु
	अचिन्हित दीर्घ regs = (अचिन्हित दीर्घ)bp;

	अगर (regs & 0x80000000)
		वापस शून्य;

	वापस (काष्ठा pt_regs *)(regs | 0x80000000);
पूर्ण
#पूर्ण_अगर

अटल bool update_stack_state(काष्ठा unwind_state *state,
			       अचिन्हित दीर्घ *next_bp)
अणु
	काष्ठा stack_info *info = &state->stack_info;
	क्रमागत stack_type prev_type = info->type;
	काष्ठा pt_regs *regs;
	अचिन्हित दीर्घ *frame, *prev_frame_end, *addr_p, addr;
	माप_प्रकार len;

	अगर (state->regs)
		prev_frame_end = (व्योम *)state->regs + माप(*state->regs);
	अन्यथा
		prev_frame_end = (व्योम *)state->bp + FRAME_HEADER_SIZE;

	/* Is the next frame poपूर्णांकer an encoded poपूर्णांकer to pt_regs? */
	regs = decode_frame_poपूर्णांकer(next_bp);
	अगर (regs) अणु
		frame = (अचिन्हित दीर्घ *)regs;
		len = माप(*regs);
		state->got_irq = true;
	पूर्ण अन्यथा अणु
		frame = next_bp;
		len = FRAME_HEADER_SIZE;
	पूर्ण

	/*
	 * If the next bp isn't on the current stack, चयन to the next one.
	 *
	 * We may have to traverse multiple stacks to deal with the possibility
	 * that info->next_sp could poपूर्णांक to an empty stack and the next bp
	 * could be on a subsequent stack.
	 */
	जबतक (!on_stack(info, frame, len))
		अगर (get_stack_info(info->next_sp, state->task, info,
				   &state->stack_mask))
			वापस false;

	/* Make sure it only unwinds up and करोesn't overlap the prev frame: */
	अगर (state->orig_sp && state->stack_info.type == prev_type &&
	    frame < prev_frame_end)
		वापस false;

	/* Move state to the next frame: */
	अगर (regs) अणु
		state->regs = regs;
		state->bp = शून्य;
	पूर्ण अन्यथा अणु
		state->bp = next_bp;
		state->regs = शून्य;
	पूर्ण

	/* Save the वापस address: */
	अगर (state->regs && user_mode(state->regs))
		state->ip = 0;
	अन्यथा अणु
		addr_p = unwind_get_वापस_address_ptr(state);
		addr = READ_ONCE_TASK_STACK(state->task, *addr_p);
		state->ip = ftrace_graph_ret_addr(state->task, &state->graph_idx,
						  addr, addr_p);
	पूर्ण

	/* Save the original stack poपूर्णांकer क्रम unwind_dump(): */
	अगर (!state->orig_sp)
		state->orig_sp = frame;

	वापस true;
पूर्ण

bool unwind_next_frame(काष्ठा unwind_state *state)
अणु
	काष्ठा pt_regs *regs;
	अचिन्हित दीर्घ *next_bp;

	अगर (unwind_करोne(state))
		वापस false;

	/* Have we reached the end? */
	अगर (state->regs && user_mode(state->regs))
		जाओ the_end;

	अगर (is_last_task_frame(state)) अणु
		regs = task_pt_regs(state->task);

		/*
		 * kthपढ़ोs (other than the boot CPU's idle thपढ़ो) have some
		 * partial regs at the end of their stack which were placed
		 * there by copy_thपढ़ो().  But the regs करोn't have any
		 * useful inक्रमmation, so we can skip them.
		 *
		 * This user_mode() check is slightly broader than a PF_KTHREAD
		 * check because it also catches the awkward situation where a
		 * newly विभाजनed kthपढ़ो transitions पूर्णांकo a user task by calling
		 * kernel_execve(), which eventually clears PF_KTHREAD.
		 */
		अगर (!user_mode(regs))
			जाओ the_end;

		/*
		 * We're almost at the end, but not quite: there's still the
		 * syscall regs frame.  Entry code करोesn't encode the regs
		 * poपूर्णांकer क्रम syscalls, so we have to set it manually.
		 */
		state->regs = regs;
		state->bp = शून्य;
		state->ip = 0;
		वापस true;
	पूर्ण

	/* Get the next frame poपूर्णांकer: */
	अगर (state->next_bp) अणु
		next_bp = state->next_bp;
		state->next_bp = शून्य;
	पूर्ण अन्यथा अगर (state->regs) अणु
		next_bp = (अचिन्हित दीर्घ *)state->regs->bp;
	पूर्ण अन्यथा अणु
		next_bp = (अचिन्हित दीर्घ *)READ_ONCE_TASK_STACK(state->task, *state->bp);
	पूर्ण

	/* Move to the next frame अगर it's safe: */
	अगर (!update_stack_state(state, next_bp))
		जाओ bad_address;

	वापस true;

bad_address:
	state->error = true;

	/*
	 * When unwinding a non-current task, the task might actually be
	 * running on another CPU, in which हाल it could be modअगरying its
	 * stack जबतक we're पढ़ोing it.  This is generally not a problem and
	 * can be ignored as दीर्घ as the caller understands that unwinding
	 * another task will not always succeed.
	 */
	अगर (state->task != current)
		जाओ the_end;

	/*
	 * Don't warn अगर the unwinder got lost due to an पूर्णांकerrupt in entry
	 * code or in the C handler beक्रमe the first frame poपूर्णांकer got set up:
	 */
	अगर (state->got_irq && in_entry_code(state->ip))
		जाओ the_end;
	अगर (state->regs &&
	    state->regs->sp >= (अचिन्हित दीर्घ)last_aligned_frame(state) &&
	    state->regs->sp < (अचिन्हित दीर्घ)task_pt_regs(state->task))
		जाओ the_end;

	/*
	 * There are some known frame poपूर्णांकer issues on 32-bit.  Disable
	 * unwinder warnings on 32-bit until it माला_लो objtool support.
	 */
	अगर (IS_ENABLED(CONFIG_X86_32))
		जाओ the_end;

	अगर (state->task != current)
		जाओ the_end;

	अगर (state->regs) अणु
		prपूर्णांकk_deferred_once(KERN_WARNING
			"WARNING: kernel stack regs at %p in %s:%d has bad 'bp' value %p\n",
			state->regs, state->task->comm,
			state->task->pid, next_bp);
		unwind_dump(state);
	पूर्ण अन्यथा अणु
		prपूर्णांकk_deferred_once(KERN_WARNING
			"WARNING: kernel stack frame pointer at %p in %s:%d has bad value %p\n",
			state->bp, state->task->comm,
			state->task->pid, next_bp);
		unwind_dump(state);
	पूर्ण
the_end:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(unwind_next_frame);

व्योम __unwind_start(काष्ठा unwind_state *state, काष्ठा task_काष्ठा *task,
		    काष्ठा pt_regs *regs, अचिन्हित दीर्घ *first_frame)
अणु
	अचिन्हित दीर्घ *bp;

	स_रखो(state, 0, माप(*state));
	state->task = task;
	state->got_irq = (regs);

	/* Don't even attempt to start from user mode regs: */
	अगर (regs && user_mode(regs)) अणु
		state->stack_info.type = STACK_TYPE_UNKNOWN;
		वापस;
	पूर्ण

	bp = get_frame_poपूर्णांकer(task, regs);

	/*
	 * If we crash with IP==0, the last successfully executed inकाष्ठाion
	 * was probably an indirect function call with a शून्य function poपूर्णांकer.
	 * That means that SP poपूर्णांकs पूर्णांकo the middle of an incomplete frame:
	 * *SP is a वापस poपूर्णांकer, and *(SP-माप(अचिन्हित दीर्घ)) is where we
	 * would have written a frame poपूर्णांकer अगर we hadn't crashed.
	 * Pretend that the frame is complete and that BP poपूर्णांकs to it, but save
	 * the real BP so that we can use it when looking क्रम the next frame.
	 */
	अगर (regs && regs->ip == 0 && (अचिन्हित दीर्घ *)regs->sp >= first_frame) अणु
		state->next_bp = bp;
		bp = ((अचिन्हित दीर्घ *)regs->sp) - 1;
	पूर्ण

	/* Initialize stack info and make sure the frame data is accessible: */
	get_stack_info(bp, state->task, &state->stack_info,
		       &state->stack_mask);
	update_stack_state(state, bp);

	/*
	 * The caller can provide the address of the first frame directly
	 * (first_frame) or indirectly (regs->sp) to indicate which stack frame
	 * to start unwinding at.  Skip ahead until we reach it.
	 */
	जबतक (!unwind_करोne(state) &&
	       (!on_stack(&state->stack_info, first_frame, माप(दीर्घ)) ||
			(state->next_bp == शून्य && state->bp < first_frame)))
		unwind_next_frame(state);
पूर्ण
EXPORT_SYMBOL_GPL(__unwind_start);
