<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 *
 * Copyright FUJITSU LIMITED 2010
 * Copyright KOSAKI Motohiro <kosaki.motohiro@jp.fujitsu.com>
 *
 * DESCRIPTION
 *      Wait on uninitialized heap. It shold be zero and FUTEX_WAIT should
 *      वापस immediately. This test is पूर्णांकent to test zero page handling in
 *      futex.
 *
 * AUTHOR
 *      KOSAKI Motohiro <kosaki.motohiro@jp.fujitsu.com>
 *
 * HISTORY
 *      2010-Jan-6: Initial version by KOSAKI Motohiro <kosaki.motohiro@jp.fujitsu.com>
 *
 *****************************************************************************/

#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>
#समावेश <syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/futex.h>
#समावेश <libgen.h>

#समावेश "logging.h"
#समावेश "futextest.h"

#घोषणा TEST_NAME "futex-wait-uninitialized-heap"
#घोषणा WAIT_US 5000000

अटल पूर्णांक child_blocked = 1;
अटल पूर्णांक child_ret;
व्योम *buf;

व्योम usage(अक्षर *prog)
अणु
	म_लिखो("Usage: %s\n", prog);
	म_लिखो("  -c	Use color\n");
	म_लिखो("  -h	Display this help message\n");
	म_लिखो("  -v L	Verbosity level: %d=QUIET %d=CRITICAL %d=INFO\n",
	       VQUIET, VCRITICAL, VINFO);
पूर्ण

व्योम *रुको_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक res;

	child_ret = RET_PASS;
	res = futex_रुको(buf, 1, शून्य, 0);
	child_blocked = 0;

	अगर (res != 0 && त्रुटि_सं != EWOULDBLOCK) अणु
		error("futex failure\n", त्रुटि_सं);
		child_ret = RET_ERROR;
	पूर्ण
	pthपढ़ो_निकास(शून्य);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c, ret = RET_PASS;
	दीर्घ page_size;
	pthपढ़ो_t thr;

	जबतक ((c = getopt(argc, argv, "chv:")) != -1) अणु
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

	page_size = sysconf(_SC_PAGESIZE);

	buf = mmap(शून्य, page_size, PROT_READ|PROT_WRITE,
		   MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
	अगर (buf == (व्योम *)-1) अणु
		error("mmap\n", त्रुटि_सं);
		निकास(1);
	पूर्ण

	ksft_prपूर्णांक_header();
	ksft_set_plan(1);
	ksft_prपूर्णांक_msg("%s: Test the uninitialized futex value in FUTEX_WAIT\n",
	       basename(argv[0]));


	ret = pthपढ़ो_create(&thr, शून्य, रुको_thपढ़ो, शून्य);
	अगर (ret) अणु
		error("pthread_create\n", त्रुटि_सं);
		ret = RET_ERROR;
		जाओ out;
	पूर्ण

	info("waiting %dus for child to return\n", WAIT_US);
	usleep(WAIT_US);

	ret = child_ret;
	अगर (child_blocked) अणु
		fail("child blocked in kernel\n");
		ret = RET_FAIL;
	पूर्ण

 out:
	prपूर्णांक_result(TEST_NAME, ret);
	वापस ret;
पूर्ण
