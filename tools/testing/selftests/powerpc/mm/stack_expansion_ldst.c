<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test that loads/stores expand the stack segment, or trigger a SEGV, in
 * various conditions.
 *
 * Based on test code by Tom Lane.
 */

#अघोषित न_संशोधन
#समावेश <निश्चित.स>

#समावेश <err.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/resource.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#घोषणा _KB (1024)
#घोषणा _MB (1024 * 1024)

अस्थिर अक्षर *stack_top_ptr;
अस्थिर अचिन्हित दीर्घ stack_top_sp;
अस्थिर अक्षर c;

क्रमागत access_type अणु
	LOAD,
	STORE,
पूर्ण;

/*
 * Consume stack until the stack poपूर्णांकer is below @target_sp, then करो an access
 * (load or store) at offset @delta from either the base of the stack or the
 * current stack poपूर्णांकer.
 */
__attribute__ ((noअंतरभूत))
पूर्णांक consume_stack(अचिन्हित दीर्घ target_sp, अचिन्हित दीर्घ stack_high, पूर्णांक delta, क्रमागत access_type type)
अणु
	अचिन्हित दीर्घ target;
	अक्षर stack_cur;

	अगर ((अचिन्हित दीर्घ)&stack_cur > target_sp)
		वापस consume_stack(target_sp, stack_high, delta, type);
	अन्यथा अणु
		// We करोn't really need this, but without it GCC might not
		// generate a recursive call above.
		stack_top_ptr = &stack_cur;

#अगर_घोषित __घातerpc__
		यंत्र अस्थिर ("mr %[sp], %%r1" : [sp] "=r" (stack_top_sp));
#अन्यथा
		यंत्र अस्थिर ("mov %%rsp, %[sp]" : [sp] "=r" (stack_top_sp));
#पूर्ण_अगर
		target = stack_high - delta + 1;
		अस्थिर अक्षर *p = (अक्षर *)target;

		अगर (type == STORE)
			*p = c;
		अन्यथा
			c = *p;

		// Do something to prevent the stack frame being popped prior to
		// our access above.
		getpid();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक search_proc_maps(अक्षर *needle, अचिन्हित दीर्घ *low, अचिन्हित दीर्घ *high)
अणु
	अचिन्हित दीर्घ start, end;
	अटल अक्षर buf[4096];
	अक्षर name[128];
	खाता *f;
	पूर्णांक rc;

	f = ख_खोलो("/proc/self/maps", "r");
	अगर (!f) अणु
		लिखो_त्रुटि("fopen");
		वापस -1;
	पूर्ण

	जबतक (ख_माला_लो(buf, माप(buf), f)) अणु
		rc = माला_पूछो(buf, "%lx-%lx %*c%*c%*c%*c %*x %*d:%*d %*d %127s\n",
			    &start, &end, name);
		अगर (rc == 2)
			जारी;

		अगर (rc != 3) अणु
			म_लिखो("sscanf errored\n");
			rc = -1;
			अवरोध;
		पूर्ण

		अगर (म_माला(name, needle)) अणु
			*low = start;
			*high = end - 1;
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	ख_बंद(f);

	वापस rc;
पूर्ण

पूर्णांक child(अचिन्हित पूर्णांक stack_used, पूर्णांक delta, क्रमागत access_type type)
अणु
	अचिन्हित दीर्घ low, stack_high;

	निश्चित(search_proc_maps("[stack]", &low, &stack_high) == 0);

	निश्चित(consume_stack(stack_high - stack_used, stack_high, delta, type) == 0);

	म_लिखो("Access OK: %s delta %-7d used size 0x%06x stack high 0x%lx top_ptr %p top sp 0x%lx actual used 0x%lx\n",
	       type == LOAD ? "load" : "store", delta, stack_used, stack_high,
	       stack_top_ptr, stack_top_sp, stack_high - stack_top_sp + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक test_one(अचिन्हित पूर्णांक stack_used, पूर्णांक delta, क्रमागत access_type type)
अणु
	pid_t pid;
	पूर्णांक rc;

	pid = विभाजन();
	अगर (pid == 0)
		निकास(child(stack_used, delta, type));

	निश्चित(रुकोpid(pid, &rc, 0) != -1);

	अगर (WIFEXITED(rc) && WEXITSTATUS(rc) == 0)
		वापस 0;

	// We करोn't expect a non-zero exit that's not a संकेत
	निश्चित(!WIFEXITED(rc));

	म_लिखो("Faulted:   %s delta %-7d used size 0x%06x signal %d\n",
	       type == LOAD ? "load" : "store", delta, stack_used,
	       WTERMSIG(rc));

	वापस 1;
पूर्ण

// This is fairly arbitrary but is well below any of the tarमाला_लो below,
// so that the delta between the stack poपूर्णांकer and the target is large.
#घोषणा DEFAULT_SIZE	(32 * _KB)

अटल व्योम test_one_type(क्रमागत access_type type, अचिन्हित दीर्घ page_size, अचिन्हित दीर्घ rlim_cur)
अणु
	अचिन्हित दीर्घ delta;

	// We should be able to access anywhere within the rlimit
	क्रम (delta = page_size; delta <= rlim_cur; delta += page_size)
		निश्चित(test_one(DEFAULT_SIZE, delta, type) == 0);

	निश्चित(test_one(DEFAULT_SIZE, rlim_cur, type) == 0);

	// But अगर we go past the rlimit it should fail
	निश्चित(test_one(DEFAULT_SIZE, rlim_cur + 1, type) != 0);
पूर्ण

अटल पूर्णांक test(व्योम)
अणु
	अचिन्हित दीर्घ page_size;
	काष्ठा rlimit rlimit;

	page_size = getpagesize();
	getrlimit(RLIMIT_STACK, &rlimit);
	म_लिखो("Stack rlimit is 0x%lx\n", rlimit.rlim_cur);

	म_लिखो("Testing loads ...\n");
	test_one_type(LOAD, page_size, rlimit.rlim_cur);
	म_लिखो("Testing stores ...\n");
	test_one_type(STORE, page_size, rlimit.rlim_cur);

	म_लिखो("All OK\n");

	वापस 0;
पूर्ण

#अगर_घोषित __घातerpc__
#समावेश "utils.h"

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test, "stack_expansion_ldst");
पूर्ण
#अन्यथा
पूर्णांक मुख्य(व्योम)
अणु
	वापस test();
पूर्ण
#पूर्ण_अगर
