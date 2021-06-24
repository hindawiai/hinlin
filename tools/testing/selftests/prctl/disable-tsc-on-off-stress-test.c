<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tests क्रम prctl(PR_GET_TSC, ...) / prctl(PR_SET_TSC, ...)
 *
 * Tests अगर the control रेजिस्टर is updated correctly
 * when set with prctl()
 *
 * Warning: this test will cause a very high load क्रम a few seconds
 *
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <रुको.h>


#समावेश <sys/prctl.h>
#समावेश <linux/prctl.h>

/* Get/set the process' ability to use the बारtamp counter inकाष्ठाion */
#अगर_अघोषित PR_GET_TSC
#घोषणा PR_GET_TSC 25
#घोषणा PR_SET_TSC 26
# define PR_TSC_ENABLE		1   /* allow the use of the बारtamp counter */
# define PR_TSC_संक_अंश		2   /* throw a संक_अंश instead of पढ़ोing the TSC */
#पूर्ण_अगर

/* snippet from wikipedia :-) */

अटल uपूर्णांक64_t rdtsc(व्योम)
अणु
uपूर्णांक32_t lo, hi;
/* We cannot use "=A", since this would use %rax on x86_64 */
__यंत्र__ __अस्थिर__ ("rdtsc" : "=a" (lo), "=d" (hi));
वापस (uपूर्णांक64_t)hi << 32 | lo;
पूर्ण

पूर्णांक should_segv = 0;

अटल व्योम sigsegv_cb(पूर्णांक sig)
अणु
	अगर (!should_segv)
	अणु
		ख_लिखो(मानक_त्रुटि, "FATAL ERROR, rdtsc() failed while enabled\n");
		निकास(0);
	पूर्ण
	अगर (prctl(PR_SET_TSC, PR_TSC_ENABLE) < 0)
	अणु
		लिखो_त्रुटि("prctl");
		निकास(0);
	पूर्ण
	should_segv = 0;

	rdtsc();
पूर्ण

अटल व्योम task(व्योम)
अणु
	संकेत(संक_अंश, sigsegv_cb);
	alarm(10);
	क्रम(;;)
	अणु
		rdtsc();
		अगर (should_segv)
		अणु
			ख_लिखो(मानक_त्रुटि, "FATAL ERROR, rdtsc() succeeded while disabled\n");
			निकास(0);
		पूर्ण
		अगर (prctl(PR_SET_TSC, PR_TSC_संक_अंश) < 0)
		अणु
			लिखो_त्रुटि("prctl");
			निकास(0);
		पूर्ण
		should_segv = 1;
	पूर्ण
पूर्ण


पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक n_tasks = 100, i;

	ख_लिखो(मानक_त्रुटि, "[No further output means we're allright]\n");

	क्रम (i=0; i<n_tasks; i++)
		अगर (विभाजन() == 0)
			task();

	क्रम (i=0; i<n_tasks; i++)
		रुको(शून्य);

	निकास(0);
पूर्ण

