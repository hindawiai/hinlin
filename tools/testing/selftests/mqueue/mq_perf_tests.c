<शैली गुरु>
/*
 * This application is Copyright 2012 Red Hat, Inc.
 *	Doug Ledक्रमd <dledक्रमd@redhat.com>
 *
 * mq_perf_tests is मुक्त software: you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * mq_perf_tests is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * For the full text of the license, see <http://www.gnu.org/licenses/>.
 *
 * mq_perf_tests.c
 *   Tests various types of message queue workloads, concentrating on those
 *   situations that invole large message sizes, large message queue depths,
 *   or both, and reports back useful metrics about kernel message queue
 *   perक्रमmance.
 *
 */
#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <sys/types.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <sys/स्थिति.स>
#समावेश <mqueue.h>
#समावेश <popt.h>
#समावेश <error.h>

#समावेश "../kselftest.h"

अटल अक्षर *usage =
"Usage:\n"
"  %s [-c #[,#..] -f] path\n"
"\n"
"	-c #	Skip most tests and go straight to a high queue depth test\n"
"		and then run that test continuously (useful for running at\n"
"		the same time as some other workload to see how much the\n"
"		cache thrashing caused by adding messages to a very deep\n"
"		queue impacts the performance of other programs).  The number\n"
"		indicates which CPU core we should bind the process to during\n"
"		the run.  If you have more than one physical CPU, then you\n"
"		will need one copy per physical CPU package, and you should\n"
"		specify the CPU cores to pin ourself to via a comma separated\n"
"		list of CPU values.\n"
"	-f	Only usable with continuous mode.  Pin ourself to the CPUs\n"
"		as requested, then instead of looping doing a high mq\n"
"		workload, just busy loop.  This will allow us to lock up a\n"
"		single CPU just like we normally would, but without actually\n"
"		thrashing the CPU cache.  This is to make it easier to get\n"
"		comparable numbers from some other workload running on the\n"
"		other CPUs.  One set of numbers with # CPUs locked up running\n"
"		an mq workload, and another set of numbers with those same\n"
"		CPUs locked away from the test workload, but not doing\n"
"		anything to trash the cache like the mq workload might.\n"
"	path	Path name of the message queue to create\n"
"\n"
"	Note: this program must be run as root in order to enable all tests\n"
"\n";

अक्षर *MAX_MSGS = "/proc/sys/fs/mqueue/msg_max";
अक्षर *MAX_MSGSIZE = "/proc/sys/fs/mqueue/msgsize_max";

#घोषणा min(a, b) ((a) < (b) ? (a) : (b))
#घोषणा MAX_CPUS 64
अक्षर *cpu_option_string;
पूर्णांक cpus_to_pin[MAX_CPUS];
पूर्णांक num_cpus_to_pin;
pthपढ़ो_t cpu_thपढ़ोs[MAX_CPUS];
pthपढ़ो_t मुख्य_thपढ़ो;
cpu_set_t *cpu_set;
पूर्णांक cpu_set_size;
पूर्णांक cpus_online;

#घोषणा MSG_SIZE 16
#घोषणा TEST1_LOOPS 10000000
#घोषणा TEST2_LOOPS 100000
पूर्णांक continuous_mode;
पूर्णांक continuous_mode_fake;

काष्ठा rlimit saved_limits, cur_limits;
पूर्णांक saved_max_msgs, saved_max_msgsize;
पूर्णांक cur_max_msgs, cur_max_msgsize;
खाता *max_msgs, *max_msgsize;
पूर्णांक cur_nice;
अक्षर *queue_path = "/mq_perf_tests";
mqd_t queue = -1;
काष्ठा mq_attr result;
पूर्णांक mq_prio_max;

स्थिर काष्ठा poptOption options[] = अणु
	अणु
		.दीर्घName = "continuous",
		.लघुName = 'c',
		.argInfo = POPT_ARG_STRING,
		.arg = &cpu_option_string,
		.val = 'c',
		.descrip = "Run continuous tests at a high queue depth in "
			"order to test the effects of cache thrashing on "
			"other tasks on the system.  This test is intended "
			"to be run on one core of each physical CPU while "
			"some other CPU intensive task is run on all the other "
			"cores of that same physical CPU and the other task "
			"is timed.  It is assumed that the process of adding "
			"messages to the message queue in a tight loop will "
			"impact that other task to some degree.  Once the "
			"tests are performed in this way, you should then "
			"re-run the tests using fake mode in order to check "
			"the difference in time required to perform the CPU "
			"intensive task",
		.argDescrip = "cpu[,cpu]",
	पूर्ण,
	अणु
		.दीर्घName = "fake",
		.लघुName = 'f',
		.argInfo = POPT_ARG_NONE,
		.arg = &continuous_mode_fake,
		.val = 0,
		.descrip = "Tie up the CPUs that we would normally tie up in"
			"continuous mode, but don't actually do any mq stuff, "
			"just keep the CPU busy so it can't be used to process "
			"system level tasks as this would free up resources on "
			"the other CPU cores and skew the comparison between "
			"the no-mqueue work and mqueue work tests",
		.argDescrip = शून्य,
	पूर्ण,
	अणु
		.दीर्घName = "path",
		.लघुName = 'p',
		.argInfo = POPT_ARG_STRING | POPT_ARGFLAG_SHOW_DEFAULT,
		.arg = &queue_path,
		.val = 'p',
		.descrip = "The name of the path to use in the mqueue "
			"filesystem for our tests",
		.argDescrip = "pathname",
	पूर्ण,
	POPT_AUTOHELP
	POPT_TABLEEND
पूर्ण;

अटल अंतरभूत व्योम __set(खाता *stream, पूर्णांक value, अक्षर *err_msg);
व्योम shutकरोwn(पूर्णांक निकास_val, अक्षर *err_cause, पूर्णांक line_no);
व्योम sig_action_SIGUSR1(पूर्णांक signum, siginfo_t *info, व्योम *context);
व्योम sig_action(पूर्णांक signum, siginfo_t *info, व्योम *context);
अटल अंतरभूत पूर्णांक get(खाता *stream);
अटल अंतरभूत व्योम set(खाता *stream, पूर्णांक value);
अटल अंतरभूत पूर्णांक try_set(खाता *stream, पूर्णांक value);
अटल अंतरभूत व्योम getr(पूर्णांक type, काष्ठा rlimit *rlim);
अटल अंतरभूत व्योम setr(पूर्णांक type, काष्ठा rlimit *rlim);
अटल अंतरभूत व्योम खोलो_queue(काष्ठा mq_attr *attr);
व्योम increase_limits(व्योम);

अटल अंतरभूत व्योम __set(खाता *stream, पूर्णांक value, अक्षर *err_msg)
अणु
	शुरुआत(stream);
	अगर (ख_लिखो(stream, "%d", value) < 0)
		लिखो_त्रुटि(err_msg);
पूर्ण


व्योम shutकरोwn(पूर्णांक निकास_val, अक्षर *err_cause, पूर्णांक line_no)
अणु
	अटल पूर्णांक in_shutकरोwn = 0;
	पूर्णांक त्रुटि_सं_at_shutकरोwn = त्रुटि_सं;
	पूर्णांक i;

	/* In हाल we get called by multiple thपढ़ोs or from an sighandler */
	अगर (in_shutकरोwn++)
		वापस;

	क्रम (i = 0; i < num_cpus_to_pin; i++)
		अगर (cpu_thपढ़ोs[i]) अणु
			pthपढ़ो_समाप्त(cpu_thपढ़ोs[i], SIGUSR1);
			pthपढ़ो_join(cpu_thपढ़ोs[i], शून्य);
		पूर्ण

	अगर (queue != -1)
		अगर (mq_बंद(queue))
			लिखो_त्रुटि("mq_close() during shutdown");
	अगर (queue_path)
		/*
		 * Be silent अगर this fails, अगर we cleaned up alपढ़ोy it's
		 * expected to fail
		 */
		mq_unlink(queue_path);
	अगर (saved_max_msgs)
		__set(max_msgs, saved_max_msgs,
		      "failed to restore saved_max_msgs");
	अगर (saved_max_msgsize)
		__set(max_msgsize, saved_max_msgsize,
		      "failed to restore saved_max_msgsize");
	अगर (निकास_val)
		error(निकास_val, त्रुटि_सं_at_shutकरोwn, "%s at %d",
		      err_cause, line_no);
	निकास(0);
पूर्ण

व्योम sig_action_SIGUSR1(पूर्णांक signum, siginfo_t *info, व्योम *context)
अणु
	अगर (pthपढ़ो_self() != मुख्य_thपढ़ो)
		pthपढ़ो_निकास(0);
	अन्यथा अणु
		ख_लिखो(मानक_त्रुटि, "Caught signal %d in SIGUSR1 handler, "
				"exiting\n", signum);
		shutकरोwn(0, "", 0);
		ख_लिखो(मानक_त्रुटि, "\n\nReturned from shutdown?!?!\n\n");
		निकास(0);
	पूर्ण
पूर्ण

व्योम sig_action(पूर्णांक signum, siginfo_t *info, व्योम *context)
अणु
	अगर (pthपढ़ो_self() != मुख्य_thपढ़ो)
		pthपढ़ो_समाप्त(मुख्य_thपढ़ो, signum);
	अन्यथा अणु
		ख_लिखो(मानक_त्रुटि, "Caught signal %d, exiting\n", signum);
		shutकरोwn(0, "", 0);
		ख_लिखो(मानक_त्रुटि, "\n\nReturned from shutdown?!?!\n\n");
		निकास(0);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक get(खाता *stream)
अणु
	पूर्णांक value;
	शुरुआत(stream);
	अगर (ख_पूछो(stream, "%d", &value) != 1)
		shutकरोwn(4, "Error reading /proc entry", __LINE__);
	वापस value;
पूर्ण

अटल अंतरभूत व्योम set(खाता *stream, पूर्णांक value)
अणु
	पूर्णांक new_value;

	शुरुआत(stream);
	अगर (ख_लिखो(stream, "%d", value) < 0)
		वापस shutकरोwn(5, "Failed writing to /proc file", __LINE__);
	new_value = get(stream);
	अगर (new_value != value)
		वापस shutकरोwn(5, "We didn't get what we wrote to /proc back",
				__LINE__);
पूर्ण

अटल अंतरभूत पूर्णांक try_set(खाता *stream, पूर्णांक value)
अणु
	पूर्णांक new_value;

	शुरुआत(stream);
	ख_लिखो(stream, "%d", value);
	new_value = get(stream);
	वापस new_value == value;
पूर्ण

अटल अंतरभूत व्योम getr(पूर्णांक type, काष्ठा rlimit *rlim)
अणु
	अगर (getrlimit(type, rlim))
		shutकरोwn(6, "getrlimit()", __LINE__);
पूर्ण

अटल अंतरभूत व्योम setr(पूर्णांक type, काष्ठा rlimit *rlim)
अणु
	अगर (setrlimit(type, rlim))
		shutकरोwn(7, "setrlimit()", __LINE__);
पूर्ण

/**
 * खोलो_queue - खोलो the global queue क्रम testing
 * @attr - An attr काष्ठा specअगरying the desired queue traits
 * @result - An attr काष्ठा that lists the actual traits the queue has
 *
 * This खोलो is not allowed to fail, failure will result in an orderly
 * shutकरोwn of the program.  The global queue_path is used to set what
 * queue to खोलो, the queue descriptor is saved in the global queue
 * variable.
 */
अटल अंतरभूत व्योम खोलो_queue(काष्ठा mq_attr *attr)
अणु
	पूर्णांक flags = O_RDWR | O_EXCL | O_CREAT | O_NONBLOCK;
	पूर्णांक perms = DEFखाताMODE;

	queue = mq_खोलो(queue_path, flags, perms, attr);
	अगर (queue == -1)
		shutकरोwn(1, "mq_open()", __LINE__);
	अगर (mq_getattr(queue, &result))
		shutकरोwn(1, "mq_getattr()", __LINE__);
	म_लिखो("\n\tQueue %s created:\n", queue_path);
	म_लिखो("\t\tmq_flags:\t\t\t%s\n", result.mq_flags & O_NONBLOCK ?
	       "O_NONBLOCK" : "(null)");
	म_लिखो("\t\tmq_maxmsg:\t\t\t%lu\n", result.mq_maxmsg);
	म_लिखो("\t\tmq_msgsize:\t\t\t%lu\n", result.mq_msgsize);
	म_लिखो("\t\tmq_curmsgs:\t\t\t%lu\n", result.mq_curmsgs);
पूर्ण

व्योम *fake_cont_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_cpus_to_pin; i++)
		अगर (cpu_thपढ़ोs[i] == pthपढ़ो_self())
			अवरोध;
	म_लिखो("\tStarted fake continuous mode thread %d on CPU %d\n", i,
	       cpus_to_pin[i]);
	जबतक (1)
		;
पूर्ण

व्योम *cont_thपढ़ो(व्योम *arg)
अणु
	अक्षर buff[MSG_SIZE];
	पूर्णांक i, priority;

	क्रम (i = 0; i < num_cpus_to_pin; i++)
		अगर (cpu_thपढ़ोs[i] == pthपढ़ो_self())
			अवरोध;
	म_लिखो("\tStarted continuous mode thread %d on CPU %d\n", i,
	       cpus_to_pin[i]);
	जबतक (1) अणु
		जबतक (mq_send(queue, buff, माप(buff), 0) == 0)
			;
		mq_receive(queue, buff, माप(buff), &priority);
	पूर्ण
पूर्ण

#घोषणा drain_queue() \
	जबतक (mq_receive(queue, buff, MSG_SIZE, &prio_in) == MSG_SIZE)

#घोषणा करो_unसमयd_send() \
	करो अणु \
		अगर (mq_send(queue, buff, MSG_SIZE, prio_out)) \
			shutकरोwn(3, "Test send failure", __LINE__); \
	पूर्ण जबतक (0)

#घोषणा करो_send_recv() \
	करो अणु \
		घड़ी_समय_लो(घड़ी, &start); \
		अगर (mq_send(queue, buff, MSG_SIZE, prio_out)) \
			shutकरोwn(3, "Test send failure", __LINE__); \
		घड़ी_समय_लो(घड़ी, &middle); \
		अगर (mq_receive(queue, buff, MSG_SIZE, &prio_in) != MSG_SIZE) \
			shutकरोwn(3, "Test receive failure", __LINE__); \
		घड़ी_समय_लो(घड़ी, &end); \
		nsec = ((middle.tv_sec - start.tv_sec) * 1000000000) + \
			(middle.tv_nsec - start.tv_nsec); \
		send_total.tv_nsec += nsec; \
		अगर (send_total.tv_nsec >= 1000000000) अणु \
			send_total.tv_sec++; \
			send_total.tv_nsec -= 1000000000; \
		पूर्ण \
		nsec = ((end.tv_sec - middle.tv_sec) * 1000000000) + \
			(end.tv_nsec - middle.tv_nsec); \
		recv_total.tv_nsec += nsec; \
		अगर (recv_total.tv_nsec >= 1000000000) अणु \
			recv_total.tv_sec++; \
			recv_total.tv_nsec -= 1000000000; \
		पूर्ण \
	पूर्ण जबतक (0)

काष्ठा test अणु
	अक्षर *desc;
	व्योम (*func)(पूर्णांक *);
पूर्ण;

व्योम स्थिर_prio(पूर्णांक *prio)
अणु
	वापस;
पूर्ण

व्योम inc_prio(पूर्णांक *prio)
अणु
	अगर (++*prio == mq_prio_max)
		*prio = 0;
पूर्ण

व्योम dec_prio(पूर्णांक *prio)
अणु
	अगर (--*prio < 0)
		*prio = mq_prio_max - 1;
पूर्ण

व्योम अक्रमom_prio(पूर्णांक *prio)
अणु
	*prio = अक्रमom() % mq_prio_max;
पूर्ण

काष्ठा test test2[] = अणु
	अणु"\n\tTest #2a: Time send/recv message, queue full, constant prio\n",
		स्थिर_prioपूर्ण,
	अणु"\n\tTest #2b: Time send/recv message, queue full, increasing prio\n",
		inc_prioपूर्ण,
	अणु"\n\tTest #2c: Time send/recv message, queue full, decreasing prio\n",
		dec_prioपूर्ण,
	अणु"\n\tTest #2d: Time send/recv message, queue full, random prio\n",
		अक्रमom_prioपूर्ण,
	अणुशून्य, शून्यपूर्ण
पूर्ण;

/**
 * Tests to perक्रमm (all करोne with MSG_SIZE messages):
 *
 * 1) Time to add/हटाओ message with 0 messages on queue
 * 1a) with स्थिरant prio
 * 2) Time to add/हटाओ message when queue बंद to capacity:
 * 2a) with स्थिरant prio
 * 2b) with increasing prio
 * 2c) with decreasing prio
 * 2d) with अक्रमom prio
 * 3) Test limits of priorities honored (द्विगुन check _SC_MQ_PRIO_MAX)
 */
व्योम *perf_test_thपढ़ो(व्योम *arg)
अणु
	अक्षर buff[MSG_SIZE];
	पूर्णांक prio_out, prio_in;
	पूर्णांक i;
	घड़ीid_t घड़ी;
	pthपढ़ो_t *t;
	काष्ठा बारpec res, start, middle, end, send_total, recv_total;
	अचिन्हित दीर्घ दीर्घ nsec;
	काष्ठा test *cur_test;

	t = &cpu_thपढ़ोs[0];
	म_लिखो("\n\tStarted mqueue performance test thread on CPU %d\n",
	       cpus_to_pin[0]);
	mq_prio_max = sysconf(_SC_MQ_PRIO_MAX);
	अगर (mq_prio_max == -1)
		shutकरोwn(2, "sysconf(_SC_MQ_PRIO_MAX)", __LINE__);
	अगर (pthपढ़ो_अ_लोpuघड़ीid(cpu_thपढ़ोs[0], &घड़ी) != 0)
		shutकरोwn(2, "pthread_getcpuclockid", __LINE__);

	अगर (घड़ी_getres(घड़ी, &res))
		shutकरोwn(2, "clock_getres()", __LINE__);

	म_लिखो("\t\tMax priorities:\t\t\t%d\n", mq_prio_max);
	म_लिखो("\t\tClock resolution:\t\t%lu nsec%s\n", res.tv_nsec,
	       res.tv_nsec > 1 ? "s" : "");



	म_लिखो("\n\tTest #1: Time send/recv message, queue empty\n");
	म_लिखो("\t\t(%d iterations)\n", TEST1_LOOPS);
	prio_out = 0;
	send_total.tv_sec = 0;
	send_total.tv_nsec = 0;
	recv_total.tv_sec = 0;
	recv_total.tv_nsec = 0;
	क्रम (i = 0; i < TEST1_LOOPS; i++)
		करो_send_recv();
	म_लिखो("\t\tSend msg:\t\t\t%ld.%lus total time\n",
	       send_total.tv_sec, send_total.tv_nsec);
	nsec = ((अचिन्हित दीर्घ दीर्घ)send_total.tv_sec * 1000000000 +
		 send_total.tv_nsec) / TEST1_LOOPS;
	म_लिखो("\t\t\t\t\t\t%lld nsec/msg\n", nsec);
	म_लिखो("\t\tRecv msg:\t\t\t%ld.%lus total time\n",
	       recv_total.tv_sec, recv_total.tv_nsec);
	nsec = ((अचिन्हित दीर्घ दीर्घ)recv_total.tv_sec * 1000000000 +
		recv_total.tv_nsec) / TEST1_LOOPS;
	म_लिखो("\t\t\t\t\t\t%lld nsec/msg\n", nsec);


	क्रम (cur_test = test2; cur_test->desc != शून्य; cur_test++) अणु
		म_लिखो("%s:\n", cur_test->desc);
		म_लिखो("\t\t(%d iterations)\n", TEST2_LOOPS);
		prio_out = 0;
		send_total.tv_sec = 0;
		send_total.tv_nsec = 0;
		recv_total.tv_sec = 0;
		recv_total.tv_nsec = 0;
		म_लिखो("\t\tFilling queue...");
		ख_साफ(मानक_निकास);
		घड़ी_समय_लो(घड़ी, &start);
		क्रम (i = 0; i < result.mq_maxmsg - 1; i++) अणु
			करो_unसमयd_send();
			cur_test->func(&prio_out);
		पूर्ण
		घड़ी_समय_लो(घड़ी, &end);
		nsec = ((अचिन्हित दीर्घ दीर्घ)(end.tv_sec - start.tv_sec) *
			1000000000) + (end.tv_nsec - start.tv_nsec);
		म_लिखो("done.\t\t%lld.%llds\n", nsec / 1000000000,
		       nsec % 1000000000);
		म_लिखो("\t\tTesting...");
		ख_साफ(मानक_निकास);
		क्रम (i = 0; i < TEST2_LOOPS; i++) अणु
			करो_send_recv();
			cur_test->func(&prio_out);
		पूर्ण
		म_लिखो("done.\n");
		म_लिखो("\t\tSend msg:\t\t\t%ld.%lus total time\n",
		       send_total.tv_sec, send_total.tv_nsec);
		nsec = ((अचिन्हित दीर्घ दीर्घ)send_total.tv_sec * 1000000000 +
			 send_total.tv_nsec) / TEST2_LOOPS;
		म_लिखो("\t\t\t\t\t\t%lld nsec/msg\n", nsec);
		म_लिखो("\t\tRecv msg:\t\t\t%ld.%lus total time\n",
		       recv_total.tv_sec, recv_total.tv_nsec);
		nsec = ((अचिन्हित दीर्घ दीर्घ)recv_total.tv_sec * 1000000000 +
			recv_total.tv_nsec) / TEST2_LOOPS;
		म_लिखो("\t\t\t\t\t\t%lld nsec/msg\n", nsec);
		म_लिखो("\t\tDraining queue...");
		ख_साफ(मानक_निकास);
		घड़ी_समय_लो(घड़ी, &start);
		drain_queue();
		घड़ी_समय_लो(घड़ी, &end);
		nsec = ((अचिन्हित दीर्घ दीर्घ)(end.tv_sec - start.tv_sec) *
			1000000000) + (end.tv_nsec - start.tv_nsec);
		म_लिखो("done.\t\t%lld.%llds\n", nsec / 1000000000,
		       nsec % 1000000000);
	पूर्ण
	वापस 0;
पूर्ण

व्योम increase_limits(व्योम)
अणु
	cur_limits.rlim_cur = RLIM_अनन्त;
	cur_limits.rlim_max = RLIM_अनन्त;
	setr(RLIMIT_MSGQUEUE, &cur_limits);
	जबतक (try_set(max_msgs, cur_max_msgs += 10))
		;
	cur_max_msgs = get(max_msgs);
	जबतक (try_set(max_msgsize, cur_max_msgsize += 1024))
		;
	cur_max_msgsize = get(max_msgsize);
	अगर (setpriority(PRIO_PROCESS, 0, -20) != 0)
		shutकरोwn(2, "setpriority()", __LINE__);
	cur_nice = -20;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा mq_attr attr;
	अक्षर *option, *next_option;
	पूर्णांक i, cpu, rc;
	काष्ठा sigaction sa;
	poptContext popt_context;
	व्योम *retval;

	मुख्य_thपढ़ो = pthपढ़ो_self();
	num_cpus_to_pin = 0;

	अगर (sysconf(_SC_NPROCESSORS_ONLN) == -1) अणु
		लिखो_त्रुटि("sysconf(_SC_NPROCESSORS_ONLN)");
		निकास(1);
	पूर्ण
	cpus_online = min(MAX_CPUS, sysconf(_SC_NPROCESSORS_ONLN));
	cpu_set = CPU_ALLOC(cpus_online);
	अगर (cpu_set == शून्य) अणु
		लिखो_त्रुटि("CPU_ALLOC()");
		निकास(1);
	पूर्ण
	cpu_set_size = CPU_ALLOC_SIZE(cpus_online);
	CPU_ZERO_S(cpu_set_size, cpu_set);

	popt_context = poptGetContext(शून्य, argc, (स्थिर अक्षर **)argv,
				      options, 0);

	जबतक ((rc = poptGetNextOpt(popt_context)) > 0) अणु
		चयन (rc) अणु
		हाल 'c':
			continuous_mode = 1;
			option = cpu_option_string;
			करो अणु
				next_option = म_अक्षर(option, ',');
				अगर (next_option)
					*next_option = '\0';
				cpu = म_से_प(option);
				अगर (cpu >= cpus_online)
					ख_लिखो(मानक_त्रुटि, "CPU %d exceeds "
						"cpus online, ignoring.\n",
						cpu);
				अन्यथा
					cpus_to_pin[num_cpus_to_pin++] = cpu;
				अगर (next_option)
					option = ++next_option;
			पूर्ण जबतक (next_option && num_cpus_to_pin < MAX_CPUS);
			/* Double check that they didn't give us the same CPU
			 * more than once */
			क्रम (cpu = 0; cpu < num_cpus_to_pin; cpu++) अणु
				अगर (CPU_ISSET_S(cpus_to_pin[cpu], cpu_set_size,
						cpu_set)) अणु
					ख_लिखो(मानक_त्रुटि, "Any given CPU may "
						"only be given once.\n");
					निकास(1);
				पूर्ण अन्यथा
					CPU_SET_S(cpus_to_pin[cpu],
						  cpu_set_size, cpu_set);
			पूर्ण
			अवरोध;
		हाल 'p':
			/*
			 * Although we can create a msg queue with a
			 * non-असलolute path name, unlink will fail.  So,
			 * अगर the name करोesn't start with a /, add one
			 * when we save it.
			 */
			option = queue_path;
			अगर (*option != '/') अणु
				queue_path = दो_स्मृति(म_माप(option) + 2);
				अगर (!queue_path) अणु
					लिखो_त्रुटि("malloc()");
					निकास(1);
				पूर्ण
				queue_path[0] = '/';
				queue_path[1] = 0;
				म_जोड़ो(queue_path, option);
				मुक्त(option);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (continuous_mode && num_cpus_to_pin == 0) अणु
		ख_लिखो(मानक_त्रुटि, "Must pass at least one CPU to continuous "
			"mode.\n");
		poptPrपूर्णांकUsage(popt_context, मानक_त्रुटि, 0);
		निकास(1);
	पूर्ण अन्यथा अगर (!continuous_mode) अणु
		num_cpus_to_pin = 1;
		cpus_to_pin[0] = cpus_online - 1;
	पूर्ण

	अगर (getuid() != 0)
		ksft_निकास_skip("Not running as root, but almost all tests "
			"require root in order to modify\nsystem settings.  "
			"Exiting.\n");

	max_msgs = ख_खोलो(MAX_MSGS, "r+");
	max_msgsize = ख_खोलो(MAX_MSGSIZE, "r+");
	अगर (!max_msgs)
		shutकरोwn(2, "Failed to open msg_max", __LINE__);
	अगर (!max_msgsize)
		shutकरोwn(2, "Failed to open msgsize_max", __LINE__);

	/* Load up the current प्रणाली values क्रम everything we can */
	getr(RLIMIT_MSGQUEUE, &saved_limits);
	cur_limits = saved_limits;
	saved_max_msgs = cur_max_msgs = get(max_msgs);
	saved_max_msgsize = cur_max_msgsize = get(max_msgsize);
	त्रुटि_सं = 0;
	cur_nice = getpriority(PRIO_PROCESS, 0);
	अगर (त्रुटि_सं)
		shutकरोwn(2, "getpriority()", __LINE__);

	/* Tell the user our initial state */
	म_लिखो("\nInitial system state:\n");
	म_लिखो("\tUsing queue path:\t\t\t%s\n", queue_path);
	म_लिखो("\tRLIMIT_MSGQUEUE(soft):\t\t\t%ld\n",
		(दीर्घ) saved_limits.rlim_cur);
	म_लिखो("\tRLIMIT_MSGQUEUE(hard):\t\t\t%ld\n",
		(दीर्घ) saved_limits.rlim_max);
	म_लिखो("\tMaximum Message Size:\t\t\t%d\n", saved_max_msgsize);
	म_लिखो("\tMaximum Queue Size:\t\t\t%d\n", saved_max_msgs);
	म_लिखो("\tNice value:\t\t\t\t%d\n", cur_nice);
	म_लिखो("\n");

	increase_limits();

	म_लिखो("Adjusted system state for testing:\n");
	अगर (cur_limits.rlim_cur == RLIM_अनन्त) अणु
		म_लिखो("\tRLIMIT_MSGQUEUE(soft):\t\t\t(unlimited)\n");
		म_लिखो("\tRLIMIT_MSGQUEUE(hard):\t\t\t(unlimited)\n");
	पूर्ण अन्यथा अणु
		म_लिखो("\tRLIMIT_MSGQUEUE(soft):\t\t\t%ld\n",
		       (दीर्घ) cur_limits.rlim_cur);
		म_लिखो("\tRLIMIT_MSGQUEUE(hard):\t\t\t%ld\n",
		       (दीर्घ) cur_limits.rlim_max);
	पूर्ण
	म_लिखो("\tMaximum Message Size:\t\t\t%d\n", cur_max_msgsize);
	म_लिखो("\tMaximum Queue Size:\t\t\t%d\n", cur_max_msgs);
	म_लिखो("\tNice value:\t\t\t\t%d\n", cur_nice);
	म_लिखो("\tContinuous mode:\t\t\t(%s)\n", continuous_mode ?
	       (continuous_mode_fake ? "fake mode" : "enabled") :
	       "disabled");
	म_लिखो("\tCPUs to pin:\t\t\t\t%d", cpus_to_pin[0]);
	क्रम (cpu = 1; cpu < num_cpus_to_pin; cpu++)
			म_लिखो(",%d", cpus_to_pin[cpu]);
	म_लिखो("\n");

	sa.sa_sigaction = sig_action_SIGUSR1;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGHUP);
	sigaddset(&sa.sa_mask, संक_विघ्न);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, संक_इति);
	sa.sa_flags = SA_SIGINFO;
	अगर (sigaction(SIGUSR1, &sa, शून्य) == -1)
		shutकरोwn(1, "sigaction(SIGUSR1)", __LINE__);
	sa.sa_sigaction = sig_action;
	अगर (sigaction(SIGHUP, &sa, शून्य) == -1)
		shutकरोwn(1, "sigaction(SIGHUP)", __LINE__);
	अगर (sigaction(संक_विघ्न, &sa, शून्य) == -1)
		shutकरोwn(1, "sigaction(SIGINT)", __LINE__);
	अगर (sigaction(SIGQUIT, &sa, शून्य) == -1)
		shutकरोwn(1, "sigaction(SIGQUIT)", __LINE__);
	अगर (sigaction(संक_इति, &sa, शून्य) == -1)
		shutकरोwn(1, "sigaction(SIGTERM)", __LINE__);

	अगर (!continuous_mode_fake) अणु
		attr.mq_flags = O_NONBLOCK;
		attr.mq_maxmsg = cur_max_msgs;
		attr.mq_msgsize = MSG_SIZE;
		खोलो_queue(&attr);
	पूर्ण
	क्रम (i = 0; i < num_cpus_to_pin; i++) अणु
		pthपढ़ो_attr_t thपढ़ो_attr;
		व्योम *thपढ़ो_func;

		अगर (continuous_mode_fake)
			thपढ़ो_func = &fake_cont_thपढ़ो;
		अन्यथा अगर (continuous_mode)
			thपढ़ो_func = &cont_thपढ़ो;
		अन्यथा
			thपढ़ो_func = &perf_test_thपढ़ो;

		CPU_ZERO_S(cpu_set_size, cpu_set);
		CPU_SET_S(cpus_to_pin[i], cpu_set_size, cpu_set);
		pthपढ़ो_attr_init(&thपढ़ो_attr);
		pthपढ़ो_attr_setaffinity_np(&thपढ़ो_attr, cpu_set_size,
					    cpu_set);
		अगर (pthपढ़ो_create(&cpu_thपढ़ोs[i], &thपढ़ो_attr, thपढ़ो_func,
				   शून्य))
			shutकरोwn(1, "pthread_create()", __LINE__);
		pthपढ़ो_attr_destroy(&thपढ़ो_attr);
	पूर्ण

	अगर (!continuous_mode) अणु
		pthपढ़ो_join(cpu_thपढ़ोs[0], &retval);
		shutकरोwn((दीर्घ)retval, "perf_test_thread()", __LINE__);
	पूर्ण अन्यथा अणु
		जबतक (1)
			sleep(1);
	पूर्ण
	shutकरोwn(0, "", 0);
पूर्ण
