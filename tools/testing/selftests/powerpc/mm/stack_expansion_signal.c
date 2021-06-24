<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test that संकेत delivery is able to expand the stack segment without
 * triggering a SEGV.
 *
 * Based on test code by Tom Lane.
 */

#समावेश <err.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#समावेश "../pmu/lib.h"
#समावेश "utils.h"

#घोषणा _KB (1024)
#घोषणा _MB (1024 * 1024)

अटल अक्षर *stack_base_ptr;
अटल अक्षर *stack_top_ptr;

अटल अस्थिर संक_पूर्ण_प्रकार sig_occurred = 0;

अटल व्योम sigusr1_handler(पूर्णांक संकेत_arg)
अणु
	sig_occurred = 1;
पूर्ण

अटल पूर्णांक consume_stack(अचिन्हित पूर्णांक stack_size, जोड़ pipe ग_लिखो_pipe)
अणु
	अक्षर stack_cur;

	अगर ((stack_base_ptr - &stack_cur) < stack_size)
		वापस consume_stack(stack_size, ग_लिखो_pipe);
	अन्यथा अणु
		stack_top_ptr = &stack_cur;

		FAIL_IF(notअगरy_parent(ग_लिखो_pipe));

		जबतक (!sig_occurred)
			barrier();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक child(अचिन्हित पूर्णांक stack_size, जोड़ pipe ग_लिखो_pipe)
अणु
	काष्ठा sigaction act;
	अक्षर stack_base;

	act.sa_handler = sigusr1_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	अगर (sigaction(SIGUSR1, &act, शून्य) < 0)
		err(1, "sigaction");

	stack_base_ptr = (अक्षर *) (((माप_प्रकार) &stack_base + 65535) & ~65535UL);

	FAIL_IF(consume_stack(stack_size, ग_लिखो_pipe));

	म_लिखो("size 0x%06x: OK, stack base %p top %p (%zx used)\n",
		stack_size, stack_base_ptr, stack_top_ptr,
		stack_base_ptr - stack_top_ptr);

	वापस 0;
पूर्ण

अटल पूर्णांक test_one_size(अचिन्हित पूर्णांक stack_size)
अणु
	जोड़ pipe पढ़ो_pipe, ग_लिखो_pipe;
	pid_t pid;

	FAIL_IF(pipe(पढ़ो_pipe.fds) == -1);
	FAIL_IF(pipe(ग_लिखो_pipe.fds) == -1);

	pid = विभाजन();
	अगर (pid == 0) अणु
		बंद(पढ़ो_pipe.पढ़ो_fd);
		बंद(ग_लिखो_pipe.ग_लिखो_fd);
		निकास(child(stack_size, पढ़ो_pipe));
	पूर्ण

	बंद(पढ़ो_pipe.ग_लिखो_fd);
	बंद(ग_लिखो_pipe.पढ़ो_fd);
	FAIL_IF(sync_with_child(पढ़ो_pipe, ग_लिखो_pipe));

	समाप्त(pid, SIGUSR1);

	FAIL_IF(रुको_क्रम_child(pid));

	बंद(पढ़ो_pipe.पढ़ो_fd);
	बंद(ग_लिखो_pipe.ग_लिखो_fd);

	वापस 0;
पूर्ण

पूर्णांक test(व्योम)
अणु
	अचिन्हित पूर्णांक i, size;

	// Test with used stack from 1MB - 64K to 1MB + 64K
	// Increment by 64 to get more coverage of odd sizes
	क्रम (i = 0; i < (128 * _KB); i += 64) अणु
		size = i + (1 * _MB) - (64 * _KB);
		FAIL_IF(test_one_size(size));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test, "stack_expansion_signal");
पूर्ण
