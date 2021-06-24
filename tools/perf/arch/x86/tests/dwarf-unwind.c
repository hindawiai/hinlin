<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश "perf_regs.h"
#समावेश "thread.h"
#समावेश "map.h"
#समावेश "maps.h"
#समावेश "event.h"
#समावेश "debug.h"
#समावेश "tests/tests.h"
#समावेश "arch-tests.h"

#घोषणा STACK_SIZE 8192

अटल पूर्णांक sample_ustack(काष्ठा perf_sample *sample,
			 काष्ठा thपढ़ो *thपढ़ो, u64 *regs)
अणु
	काष्ठा stack_dump *stack = &sample->user_stack;
	काष्ठा map *map;
	अचिन्हित दीर्घ sp;
	u64 stack_size, *buf;

	buf = दो_स्मृति(STACK_SIZE);
	अगर (!buf) अणु
		pr_debug("failed to allocate sample uregs data\n");
		वापस -1;
	पूर्ण

	sp = (अचिन्हित दीर्घ) regs[PERF_REG_X86_SP];

	map = maps__find(thपढ़ो->maps, (u64)sp);
	अगर (!map) अणु
		pr_debug("failed to get stack map\n");
		मुक्त(buf);
		वापस -1;
	पूर्ण

	stack_size = map->end - sp;
	stack_size = stack_size > STACK_SIZE ? STACK_SIZE : stack_size;

	स_नकल(buf, (व्योम *) sp, stack_size);
#अगर_घोषित MEMORY_SANITIZER
	/*
	 * Copying the stack may copy msan poison, aव्योम false positives in the
	 * unwinder by removing the poison here.
	 */
	__msan_unpoison(buf, stack_size);
#पूर्ण_अगर
	stack->data = (अक्षर *) buf;
	stack->size = stack_size;
	वापस 0;
पूर्ण

पूर्णांक test__arch_unwind_sample(काष्ठा perf_sample *sample,
			     काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा regs_dump *regs = &sample->user_regs;
	u64 *buf;

	buf = दो_स्मृति(माप(u64) * PERF_REGS_MAX);
	अगर (!buf) अणु
		pr_debug("failed to allocate sample uregs data\n");
		वापस -1;
	पूर्ण

#अगर_घोषित MEMORY_SANITIZER
	/*
	 * Assignments to buf in the assembly function perf_regs_load aren't
	 * seen by memory sanitizer. Zero the memory to convince memory
	 * sanitizer the memory is initialized.
	 */
	स_रखो(buf, 0, माप(u64) * PERF_REGS_MAX);
#पूर्ण_अगर
	perf_regs_load(buf);
	regs->abi  = PERF_SAMPLE_REGS_ABI;
	regs->regs = buf;
	regs->mask = PERF_REGS_MASK;

	वापस sample_ustack(sample, thपढ़ो, buf);
पूर्ण
