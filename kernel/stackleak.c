<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This code fills the used part of the kernel stack with a poison value
 * beक्रमe वापसing to userspace. It's part of the STACKLEAK feature
 * ported from grsecurity/PaX.
 *
 * Author: Alexander Popov <alex.popov@linux.com>
 *
 * STACKLEAK reduces the inक्रमmation which kernel stack leak bugs can
 * reveal and blocks some uninitialized stack variable attacks.
 */

#समावेश <linux/stackleak.h>
#समावेश <linux/kprobes.h>

#अगर_घोषित CONFIG_STACKLEAK_RUNTIME_DISABLE
#समावेश <linux/jump_label.h>
#समावेश <linux/sysctl.h>

अटल DEFINE_STATIC_KEY_FALSE(stack_erasing_bypass);

पूर्णांक stack_erasing_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret = 0;
	पूर्णांक state = !अटल_branch_unlikely(&stack_erasing_bypass);
	पूर्णांक prev_state = state;

	table->data = &state;
	table->maxlen = माप(पूर्णांक);
	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	state = !!state;
	अगर (ret || !ग_लिखो || state == prev_state)
		वापस ret;

	अगर (state)
		अटल_branch_disable(&stack_erasing_bypass);
	अन्यथा
		अटल_branch_enable(&stack_erasing_bypass);

	pr_warn("stackleak: kernel stack erasing is %s\n",
					state ? "enabled" : "disabled");
	वापस ret;
पूर्ण

#घोषणा skip_erasing()	अटल_branch_unlikely(&stack_erasing_bypass)
#अन्यथा
#घोषणा skip_erasing()	false
#पूर्ण_अगर /* CONFIG_STACKLEAK_RUNTIME_DISABLE */

यंत्रlinkage व्योम notrace stackleak_erase(व्योम)
अणु
	/* It would be nice not to have 'kstack_ptr' and 'boundary' on stack */
	अचिन्हित दीर्घ kstack_ptr = current->lowest_stack;
	अचिन्हित दीर्घ boundary = (अचिन्हित दीर्घ)end_of_stack(current);
	अचिन्हित पूर्णांक poison_count = 0;
	स्थिर अचिन्हित पूर्णांक depth = STACKLEAK_SEARCH_DEPTH / माप(अचिन्हित दीर्घ);

	अगर (skip_erasing())
		वापस;

	/* Check that 'lowest_stack' value is sane */
	अगर (unlikely(kstack_ptr - boundary >= THREAD_SIZE))
		kstack_ptr = boundary;

	/* Search क्रम the poison value in the kernel stack */
	जबतक (kstack_ptr > boundary && poison_count <= depth) अणु
		अगर (*(अचिन्हित दीर्घ *)kstack_ptr == STACKLEAK_POISON)
			poison_count++;
		अन्यथा
			poison_count = 0;

		kstack_ptr -= माप(अचिन्हित दीर्घ);
	पूर्ण

	/*
	 * One 'long int' at the bottom of the thपढ़ो stack is reserved and
	 * should not be poisoned (see CONFIG_SCHED_STACK_END_CHECK=y).
	 */
	अगर (kstack_ptr == boundary)
		kstack_ptr += माप(अचिन्हित दीर्घ);

#अगर_घोषित CONFIG_STACKLEAK_METRICS
	current->prev_lowest_stack = kstack_ptr;
#पूर्ण_अगर

	/*
	 * Now ग_लिखो the poison value to the kernel stack. Start from
	 * 'kstack_ptr' and move up till the new 'boundary'. We assume that
	 * the stack poपूर्णांकer करोesn't change when we ग_लिखो poison.
	 */
	अगर (on_thपढ़ो_stack())
		boundary = current_stack_poपूर्णांकer;
	अन्यथा
		boundary = current_top_of_stack();

	जबतक (kstack_ptr < boundary) अणु
		*(अचिन्हित दीर्घ *)kstack_ptr = STACKLEAK_POISON;
		kstack_ptr += माप(अचिन्हित दीर्घ);
	पूर्ण

	/* Reset the 'lowest_stack' value क्रम the next syscall */
	current->lowest_stack = current_top_of_stack() - THREAD_SIZE/64;
पूर्ण
NOKPROBE_SYMBOL(stackleak_erase);

व्योम __used __no_caller_saved_रेजिस्टरs notrace stackleak_track_stack(व्योम)
अणु
	अचिन्हित दीर्घ sp = current_stack_poपूर्णांकer;

	/*
	 * Having CONFIG_STACKLEAK_TRACK_MIN_SIZE larger than
	 * STACKLEAK_SEARCH_DEPTH makes the poison search in
	 * stackleak_erase() unreliable. Let's prevent that.
	 */
	BUILD_BUG_ON(CONFIG_STACKLEAK_TRACK_MIN_SIZE > STACKLEAK_SEARCH_DEPTH);

	/* 'lowest_stack' should be aligned on the रेजिस्टर width boundary */
	sp = ALIGN(sp, माप(अचिन्हित दीर्घ));
	अगर (sp < current->lowest_stack &&
	    sp >= (अचिन्हित दीर्घ)task_stack_page(current) +
						माप(अचिन्हित दीर्घ)) अणु
		current->lowest_stack = sp;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(stackleak_track_stack);
