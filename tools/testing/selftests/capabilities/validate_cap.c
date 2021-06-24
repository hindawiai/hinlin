<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <cap-ng.h>
#समावेश <linux/capability.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <sys/prctl.h>
#समावेश <sys/auxv.h>

#समावेश "../kselftest.h"

#अगर_अघोषित PR_CAP_AMBIENT
#घोषणा PR_CAP_AMBIENT			47
# define PR_CAP_AMBIENT_IS_SET		1
# define PR_CAP_AMBIENT_RAISE		2
# define PR_CAP_AMBIENT_LOWER		3
# define PR_CAP_AMBIENT_CLEAR_ALL	4
#पूर्ण_अगर

#अगर __GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 19)
# define HAVE_GETAUXVAL
#पूर्ण_अगर

अटल bool bool_arg(अक्षर **argv, पूर्णांक i)
अणु
	अगर (!म_भेद(argv[i], "0"))
		वापस false;
	अन्यथा अगर (!म_भेद(argv[i], "1"))
		वापस true;
	अन्यथा अणु
		ksft_निकास_fail_msg("wrong argv[%d]\n", i);
		वापस false;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *atsec = "";

	/*
	 * Be careful just in हाल a setgid or setcapped copy of this
	 * helper माला_लो out.
	 */

	अगर (argc != 5)
		ksft_निकास_fail_msg("wrong argc\n");

#अगर_घोषित HAVE_GETAUXVAL
	अगर (getauxval(AT_SECURE))
		atsec = " (AT_SECURE is set)";
	अन्यथा
		atsec = " (AT_SECURE is not set)";
#पूर्ण_अगर

	capng_get_caps_process();

	अगर (capng_have_capability(CAPNG_EFFECTIVE, CAP_NET_BIND_SERVICE) != bool_arg(argv, 1)) अणु
		ksft_prपूर्णांक_msg("Wrong effective state%s\n", atsec);
		वापस 1;
	पूर्ण

	अगर (capng_have_capability(CAPNG_PERMITTED, CAP_NET_BIND_SERVICE) != bool_arg(argv, 2)) अणु
		ksft_prपूर्णांक_msg("Wrong permitted state%s\n", atsec);
		वापस 1;
	पूर्ण

	अगर (capng_have_capability(CAPNG_INHERITABLE, CAP_NET_BIND_SERVICE) != bool_arg(argv, 3)) अणु
		ksft_prपूर्णांक_msg("Wrong inheritable state%s\n", atsec);
		वापस 1;
	पूर्ण

	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SERVICE, 0, 0, 0) != bool_arg(argv, 4)) अणु
		ksft_prपूर्णांक_msg("Wrong ambient state%s\n", atsec);
		वापस 1;
	पूर्ण

	ksft_prपूर्णांक_msg("%s: Capabilities after execve were correct\n",
			"validate_cap:");
	वापस 0;
पूर्ण
