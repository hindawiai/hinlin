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

	sp = (अचिन्हित दीर्घ) regs[PERF_REG_ARM_SP];

	map = maps__find(thपढ़ो->maps, (u64)sp);
	अगर (!map) अणु
		pr_debug("failed to get stack map\n");
		मुक्त(buf);
		वापस -1;
	पूर्ण

	stack_size = map->end - sp;
	stack_size = stack_size > STACK_SIZE ? STACK_SIZE : stack_size;

	स_नकल(buf, (व्योम *) sp, stack_size);
	stack->data = (अक्षर *) buf;
	stack->size = stack_size;
	वापस 0;
पूर्ण

पूर्णांक test__arch_unwind_sample(काष्ठा perf_sample *sample,
			     काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा regs_dump *regs = &sample->user_regs;
	u64 *buf;

	buf = सुस्मृति(1, माप(u64) * PERF_REGS_MAX);
	अगर (!buf) अणु
		pr_debug("failed to allocate sample uregs data\n");
		वापस -1;
	पूर्ण

	perf_regs_load(buf);
	regs->abi  = PERF_SAMPLE_REGS_ABI;
	regs->regs = buf;
	regs->mask = PERF_REGS_MASK;

	वापस sample_ustack(sample, thपढ़ो, buf);
पूर्ण
