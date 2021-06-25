<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tests क्रम prctl(PR_GET_TSC, ...) / prctl(PR_SET_TSC, ...)
 *
 * Basic test to test behaviour of PR_GET_TSC and PR_SET_TSC
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <पूर्णांकtypes.h>


#समावेश <sys/prctl.h>
#समावेश <linux/prctl.h>

/* Get/set the process' ability to use the बारtamp counter inकाष्ठाion */
#अगर_अघोषित PR_GET_TSC
#घोषणा PR_GET_TSC 25
#घोषणा PR_SET_TSC 26
# define PR_TSC_ENABLE		1   /* allow the use of the बारtamp counter */
# define PR_TSC_संक_अंश		2   /* throw a संक_अंश instead of पढ़ोing the TSC */
#पूर्ण_अगर

स्थिर अक्षर *tsc_names[] =
अणु
	[0] = "[not set]",
	[PR_TSC_ENABLE] = "PR_TSC_ENABLE",
	[PR_TSC_संक_अंश] = "PR_TSC_SIGSEGV",
पूर्ण;

अटल uपूर्णांक64_t rdtsc(व्योम)
अणु
uपूर्णांक32_t lo, hi;
/* We cannot use "=A", since this would use %rax on x86_64 */
__यंत्र__ __अस्थिर__ ("rdtsc" : "=a" (lo), "=d" (hi));
वापस (uपूर्णांक64_t)hi << 32 | lo;
पूर्ण

अटल व्योम sigsegv_cb(पूर्णांक sig)
अणु
	पूर्णांक tsc_val = 0;

	म_लिखो("[ SIG_SEGV ]\n");
	म_लिखो("prctl(PR_GET_TSC, &tsc_val); ");
	ख_साफ(मानक_निकास);

	अगर ( prctl(PR_GET_TSC, &tsc_val) == -1)
		लिखो_त्रुटि("prctl");

	म_लिखो("tsc_val == %s\n", tsc_names[tsc_val]);
	म_लिखो("prctl(PR_SET_TSC, PR_TSC_ENABLE)\n");
	ख_साफ(मानक_निकास);
	अगर ( prctl(PR_SET_TSC, PR_TSC_ENABLE) == -1)
		लिखो_त्रुटि("prctl");

	म_लिखो("rdtsc() == ");
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक tsc_val = 0;

	संकेत(संक_अंश, sigsegv_cb);

	म_लिखो("rdtsc() == %llu\n", (अचिन्हित दीर्घ दीर्घ)rdtsc());
	म_लिखो("prctl(PR_GET_TSC, &tsc_val); ");
	ख_साफ(मानक_निकास);

	अगर ( prctl(PR_GET_TSC, &tsc_val) == -1)
		लिखो_त्रुटि("prctl");

	म_लिखो("tsc_val == %s\n", tsc_names[tsc_val]);
	म_लिखो("rdtsc() == %llu\n", (अचिन्हित दीर्घ दीर्घ)rdtsc());
	म_लिखो("prctl(PR_SET_TSC, PR_TSC_ENABLE)\n");
	ख_साफ(मानक_निकास);

	अगर ( prctl(PR_SET_TSC, PR_TSC_ENABLE) == -1)
		लिखो_त्रुटि("prctl");

	म_लिखो("rdtsc() == %llu\n", (अचिन्हित दीर्घ दीर्घ)rdtsc());
	म_लिखो("prctl(PR_SET_TSC, PR_TSC_SIGSEGV)\n");
	ख_साफ(मानक_निकास);

	अगर ( prctl(PR_SET_TSC, PR_TSC_संक_अंश) == -1)
		लिखो_त्रुटि("prctl");

	म_लिखो("rdtsc() == ");
	ख_साफ(मानक_निकास);
	म_लिखो("%llu\n", (अचिन्हित दीर्घ दीर्घ)rdtsc());
	ख_साफ(मानक_निकास);

	निकास(निकास_सफल);
पूर्ण

