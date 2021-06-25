<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 *
 *   Copyright तऊ International Business Machines  Corp., 2009
 *
 * DESCRIPTION
 *      Test अगर FUTEX_WAIT op वापसs -EWOULDBLOCK अगर the futex value dअगरfers
 *      from the expected one.
 *
 * AUTHOR
 *      Gowrishankar <gowrishankar.m@in.ibm.com>
 *
 * HISTORY
 *      2009-Nov-14: Initial version by Gowrishankar <gowrishankar.m@in.ibm.com>
 *
 *****************************************************************************/

#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश "futextest.h"
#समावेश "logging.h"

#घोषणा TEST_NAME "futex-wait-wouldblock"
#घोषणा समयout_ns 100000

व्योम usage(अक्षर *prog)
अणु
	म_लिखो("Usage: %s\n", prog);
	म_लिखो("  -c	Use color\n");
	म_लिखो("  -h	Display this help message\n");
	म_लिखो("  -v L	Verbosity level: %d=QUIET %d=CRITICAL %d=INFO\n",
	       VQUIET, VCRITICAL, VINFO);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा बारpec to = अणु.tv_sec = 0, .tv_nsec = समयout_nsपूर्ण;
	futex_t f1 = FUTEX_INITIALIZER;
	पूर्णांक res, ret = RET_PASS;
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "cht:v:")) != -1) अणु
		चयन (c) अणु
		हाल 'c':
			log_color(1);
			अवरोध;
		हाल 'h':
			usage(basename(argv[0]));
			निकास(0);
		हाल 'v':
			log_verbosity(म_से_प(optarg));
			अवरोध;
		शेष:
			usage(basename(argv[0]));
			निकास(1);
		पूर्ण
	पूर्ण

	ksft_prपूर्णांक_header();
	ksft_set_plan(1);
	ksft_prपूर्णांक_msg("%s: Test the unexpected futex value in FUTEX_WAIT\n",
	       basename(argv[0]));

	info("Calling futex_wait on f1: %u @ %p with val=%u\n", f1, &f1, f1+1);
	res = futex_रुको(&f1, f1+1, &to, FUTEX_PRIVATE_FLAG);
	अगर (!res || त्रुटि_सं != EWOULDBLOCK) अणु
		fail("futex_wait returned: %d %s\n",
		     res ? त्रुटि_सं : res, res ? म_त्रुटि(त्रुटि_सं) : "");
		ret = RET_FAIL;
	पूर्ण

	prपूर्णांक_result(TEST_NAME, ret);
	वापस ret;
पूर्ण
