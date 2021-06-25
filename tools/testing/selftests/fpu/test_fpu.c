<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* This testहाल operates with the test_fpu kernel driver.
 * It modअगरies the FPU control रेजिस्टर in user mode and calls the kernel
 * module to perक्रमm भग्नing poपूर्णांक operations in the kernel. The control
 * रेजिस्टर value should be independent between kernel and user mode.
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <fenv.h>
#समावेश <unistd.h>
#समावेश <fcntl.h>

स्थिर अक्षर *test_fpu_path = "/sys/kernel/debug/selftest_helpers/test_fpu";

पूर्णांक मुख्य(व्योम)
अणु
	अक्षर dummy[1];
	पूर्णांक fd = खोलो(test_fpu_path, O_RDONLY);

	अगर (fd < 0) अणु
		म_लिखो("[SKIP]\tcan't access %s: %s\n",
		       test_fpu_path, म_त्रुटि(त्रुटि_सं));
		वापस 0;
	पूर्ण

	अगर (पढ़ो(fd, dummy, 1) < 0) अणु
		म_लिखो("[FAIL]\taccess with default rounding mode failed\n");
		वापस 1;
	पूर्ण

	fesetround(FE_DOWNWARD);
	अगर (पढ़ो(fd, dummy, 1) < 0) अणु
		म_लिखो("[FAIL]\taccess with downward rounding mode failed\n");
		वापस 2;
	पूर्ण
	अगर (fegetround() != FE_DOWNWARD) अणु
		म_लिखो("[FAIL]\tusermode rounding mode clobbered\n");
		वापस 3;
	पूर्ण

	/* Note: the tests up to this poपूर्णांक are quite safe and will only वापस
	 * an error. But the exception mask setting can cause misbehaving kernel
	 * to crash.
	 */
	feclearexcept(FE_ALL_EXCEPT);
	feenableexcept(FE_ALL_EXCEPT);
	अगर (पढ़ो(fd, dummy, 1) < 0) अणु
		म_लिखो("[FAIL]\taccess with fpu exceptions unmasked failed\n");
		वापस 4;
	पूर्ण
	अगर (fegetexcept() != FE_ALL_EXCEPT) अणु
		म_लिखो("[FAIL]\tusermode fpu exception mask clobbered\n");
		वापस 5;
	पूर्ण

	म_लिखो("[OK]\ttest_fpu\n");
	वापस 0;
पूर्ण
