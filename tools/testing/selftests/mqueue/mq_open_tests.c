<शैली गुरु>
/*
 * This application is Copyright 2012 Red Hat, Inc.
 *	Doug Ledक्रमd <dledक्रमd@redhat.com>
 *
 * mq_खोलो_tests is मुक्त software: you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * mq_खोलो_tests is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * For the full text of the license, see <http://www.gnu.org/licenses/>.
 *
 * mq_खोलो_tests.c
 *   Tests the various situations that should either succeed or fail to
 *   खोलो a posix message queue and then reports whether or not they
 *   did as they were supposed to.
 *
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <sys/स्थिति.स>
#समावेश <mqueue.h>
#समावेश <error.h>

#समावेश "../kselftest.h"

अटल अक्षर *usage =
"Usage:\n"
"  %s path\n"
"\n"
"	path	Path name of the message queue to create\n"
"\n"
"	Note: this program must be run as root in order to enable all tests\n"
"\n";

अक्षर *DEF_MSGS = "/proc/sys/fs/mqueue/msg_default";
अक्षर *DEF_MSGSIZE = "/proc/sys/fs/mqueue/msgsize_default";
अक्षर *MAX_MSGS = "/proc/sys/fs/mqueue/msg_max";
अक्षर *MAX_MSGSIZE = "/proc/sys/fs/mqueue/msgsize_max";

पूर्णांक शेष_settings;
काष्ठा rlimit saved_limits, cur_limits;
पूर्णांक saved_def_msgs, saved_def_msgsize, saved_max_msgs, saved_max_msgsize;
पूर्णांक cur_def_msgs, cur_def_msgsize, cur_max_msgs, cur_max_msgsize;
खाता *def_msgs, *def_msgsize, *max_msgs, *max_msgsize;
अक्षर *queue_path;
अक्षर *शेष_queue_path = "/test1";
mqd_t queue = -1;

अटल अंतरभूत व्योम __set(खाता *stream, पूर्णांक value, अक्षर *err_msg);
व्योम shutकरोwn(पूर्णांक निकास_val, अक्षर *err_cause, पूर्णांक line_no);
अटल अंतरभूत पूर्णांक get(खाता *stream);
अटल अंतरभूत व्योम set(खाता *stream, पूर्णांक value);
अटल अंतरभूत व्योम getr(पूर्णांक type, काष्ठा rlimit *rlim);
अटल अंतरभूत व्योम setr(पूर्णांक type, काष्ठा rlimit *rlim);
व्योम validate_current_settings();
अटल अंतरभूत व्योम test_queue(काष्ठा mq_attr *attr, काष्ठा mq_attr *result);
अटल अंतरभूत पूर्णांक test_queue_fail(काष्ठा mq_attr *attr, काष्ठा mq_attr *result);

अटल अंतरभूत व्योम __set(खाता *stream, पूर्णांक value, अक्षर *err_msg)
अणु
	शुरुआत(stream);
	अगर (ख_लिखो(stream, "%d", value) < 0)
		लिखो_त्रुटि(err_msg);
पूर्ण


व्योम shutकरोwn(पूर्णांक निकास_val, अक्षर *err_cause, पूर्णांक line_no)
अणु
	अटल पूर्णांक in_shutकरोwn = 0;

	/* In हाल we get called recursively by a set() call below */
	अगर (in_shutकरोwn++)
		वापस;

	अगर (seteuid(0) == -1)
		लिखो_त्रुटि("seteuid() failed");

	अगर (queue != -1)
		अगर (mq_बंद(queue))
			लिखो_त्रुटि("mq_close() during shutdown");
	अगर (queue_path)
		/*
		 * Be silent अगर this fails, अगर we cleaned up alपढ़ोy it's
		 * expected to fail
		 */
		mq_unlink(queue_path);
	अगर (शेष_settings) अणु
		अगर (saved_def_msgs)
			__set(def_msgs, saved_def_msgs,
			      "failed to restore saved_def_msgs");
		अगर (saved_def_msgsize)
			__set(def_msgsize, saved_def_msgsize,
			      "failed to restore saved_def_msgsize");
	पूर्ण
	अगर (saved_max_msgs)
		__set(max_msgs, saved_max_msgs,
		      "failed to restore saved_max_msgs");
	अगर (saved_max_msgsize)
		__set(max_msgsize, saved_max_msgsize,
		      "failed to restore saved_max_msgsize");
	अगर (निकास_val)
		error(निकास_val, त्रुटि_सं, "%s at %d", err_cause, line_no);
	निकास(0);
पूर्ण

अटल अंतरभूत पूर्णांक get(खाता *stream)
अणु
	पूर्णांक value;
	शुरुआत(stream);
	अगर (ख_पूछो(stream, "%d", &value) != 1)
		shutकरोwn(4, "Error reading /proc entry", __LINE__ - 1);
	वापस value;
पूर्ण

अटल अंतरभूत व्योम set(खाता *stream, पूर्णांक value)
अणु
	पूर्णांक new_value;

	शुरुआत(stream);
	अगर (ख_लिखो(stream, "%d", value) < 0)
		वापस shutकरोwn(5, "Failed writing to /proc file",
				__LINE__ - 1);
	new_value = get(stream);
	अगर (new_value != value)
		वापस shutकरोwn(5, "We didn't get what we wrote to /proc back",
				__LINE__ - 1);
पूर्ण

अटल अंतरभूत व्योम getr(पूर्णांक type, काष्ठा rlimit *rlim)
अणु
	अगर (getrlimit(type, rlim))
		shutकरोwn(6, "getrlimit()", __LINE__ - 1);
पूर्ण

अटल अंतरभूत व्योम setr(पूर्णांक type, काष्ठा rlimit *rlim)
अणु
	अगर (setrlimit(type, rlim))
		shutकरोwn(7, "setrlimit()", __LINE__ - 1);
पूर्ण

व्योम validate_current_settings()
अणु
	पूर्णांक rlim_needed;

	अगर (cur_limits.rlim_cur < 4096) अणु
		म_लिखो("Current rlimit value for POSIX message queue bytes is "
		       "unreasonably low,\nincreasing.\n\n");
		cur_limits.rlim_cur = 8192;
		cur_limits.rlim_max = 16384;
		setr(RLIMIT_MSGQUEUE, &cur_limits);
	पूर्ण

	अगर (शेष_settings) अणु
		rlim_needed = (cur_def_msgs + 1) * (cur_def_msgsize + 1 +
						    2 * माप(व्योम *));
		अगर (rlim_needed > cur_limits.rlim_cur) अणु
			म_लिखो("Temporarily lowering default queue parameters "
			       "to something that will work\n"
			       "with the current rlimit values.\n\n");
			set(def_msgs, 10);
			cur_def_msgs = 10;
			set(def_msgsize, 128);
			cur_def_msgsize = 128;
		पूर्ण
	पूर्ण अन्यथा अणु
		rlim_needed = (cur_max_msgs + 1) * (cur_max_msgsize + 1 +
						    2 * माप(व्योम *));
		अगर (rlim_needed > cur_limits.rlim_cur) अणु
			म_लिखो("Temporarily lowering maximum queue parameters "
			       "to something that will work\n"
			       "with the current rlimit values in case this is "
			       "a kernel that ties the default\n"
			       "queue parameters to the maximum queue "
			       "parameters.\n\n");
			set(max_msgs, 10);
			cur_max_msgs = 10;
			set(max_msgsize, 128);
			cur_max_msgsize = 128;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * test_queue - Test खोलोing a queue, shutकरोwn अगर we fail.  This should
 * only be called in situations that should never fail.  We clean up
 * after ourselves and वापस the queue attributes in *result.
 */
अटल अंतरभूत व्योम test_queue(काष्ठा mq_attr *attr, काष्ठा mq_attr *result)
अणु
	पूर्णांक flags = O_RDWR | O_EXCL | O_CREAT;
	पूर्णांक perms = DEFखाताMODE;

	अगर ((queue = mq_खोलो(queue_path, flags, perms, attr)) == -1)
		shutकरोwn(1, "mq_open()", __LINE__);
	अगर (mq_getattr(queue, result))
		shutकरोwn(1, "mq_getattr()", __LINE__);
	अगर (mq_बंद(queue))
		shutकरोwn(1, "mq_close()", __LINE__);
	queue = -1;
	अगर (mq_unlink(queue_path))
		shutकरोwn(1, "mq_unlink()", __LINE__);
पूर्ण

/*
 * Same as test_queue above, but failure is not fatal.
 * Returns:
 * 0 - Failed to create a queue
 * 1 - Created a queue, attributes in *result
 */
अटल अंतरभूत पूर्णांक test_queue_fail(काष्ठा mq_attr *attr, काष्ठा mq_attr *result)
अणु
	पूर्णांक flags = O_RDWR | O_EXCL | O_CREAT;
	पूर्णांक perms = DEFखाताMODE;

	अगर ((queue = mq_खोलो(queue_path, flags, perms, attr)) == -1)
		वापस 0;
	अगर (mq_getattr(queue, result))
		shutकरोwn(1, "mq_getattr()", __LINE__);
	अगर (mq_बंद(queue))
		shutकरोwn(1, "mq_close()", __LINE__);
	queue = -1;
	अगर (mq_unlink(queue_path))
		shutकरोwn(1, "mq_unlink()", __LINE__);
	वापस 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा mq_attr attr, result;

	अगर (argc != 2) अणु
		म_लिखो("Using Default queue path - %s\n", शेष_queue_path);
		queue_path = शेष_queue_path;
	पूर्ण अन्यथा अणु

	/*
	 * Although we can create a msg queue with a non-असलolute path name,
	 * unlink will fail.  So, अगर the name करोesn't start with a /, add one
	 * when we save it.
	 */
		अगर (*argv[1] == '/')
			queue_path = strdup(argv[1]);
		अन्यथा अणु
			queue_path = दो_स्मृति(म_माप(argv[1]) + 2);
			अगर (!queue_path) अणु
				लिखो_त्रुटि("malloc()");
				निकास(1);
			पूर्ण
			queue_path[0] = '/';
			queue_path[1] = 0;
			म_जोड़ो(queue_path, argv[1]);
		पूर्ण
	पूर्ण

	अगर (getuid() != 0)
		ksft_निकास_skip("Not running as root, but almost all tests "
			"require root in order to modify\nsystem settings.  "
			"Exiting.\n");

	/* Find out what files there are क्रम us to make tweaks in */
	def_msgs = ख_खोलो(DEF_MSGS, "r+");
	def_msgsize = ख_खोलो(DEF_MSGSIZE, "r+");
	max_msgs = ख_खोलो(MAX_MSGS, "r+");
	max_msgsize = ख_खोलो(MAX_MSGSIZE, "r+");

	अगर (!max_msgs)
		shutकरोwn(2, "Failed to open msg_max", __LINE__);
	अगर (!max_msgsize)
		shutकरोwn(2, "Failed to open msgsize_max", __LINE__);
	अगर (def_msgs || def_msgsize)
		शेष_settings = 1;

	/* Load up the current प्रणाली values क्रम everything we can */
	getr(RLIMIT_MSGQUEUE, &saved_limits);
	cur_limits = saved_limits;
	अगर (शेष_settings) अणु
		saved_def_msgs = cur_def_msgs = get(def_msgs);
		saved_def_msgsize = cur_def_msgsize = get(def_msgsize);
	पूर्ण
	saved_max_msgs = cur_max_msgs = get(max_msgs);
	saved_max_msgsize = cur_max_msgsize = get(max_msgsize);

	/* Tell the user our initial state */
	म_लिखो("\nInitial system state:\n");
	म_लिखो("\tUsing queue path:\t\t%s\n", queue_path);
	म_लिखो("\tRLIMIT_MSGQUEUE(soft):\t\t%ld\n",
		(दीर्घ) saved_limits.rlim_cur);
	म_लिखो("\tRLIMIT_MSGQUEUE(hard):\t\t%ld\n",
		(दीर्घ) saved_limits.rlim_max);
	म_लिखो("\tMaximum Message Size:\t\t%d\n", saved_max_msgsize);
	म_लिखो("\tMaximum Queue Size:\t\t%d\n", saved_max_msgs);
	अगर (शेष_settings) अणु
		म_लिखो("\tDefault Message Size:\t\t%d\n", saved_def_msgsize);
		म_लिखो("\tDefault Queue Size:\t\t%d\n", saved_def_msgs);
	पूर्ण अन्यथा अणु
		म_लिखो("\tDefault Message Size:\t\tNot Supported\n");
		म_लिखो("\tDefault Queue Size:\t\tNot Supported\n");
	पूर्ण
	म_लिखो("\n");

	validate_current_settings();

	म_लिखो("Adjusted system state for testing:\n");
	म_लिखो("\tRLIMIT_MSGQUEUE(soft):\t\t%ld\n", (दीर्घ) cur_limits.rlim_cur);
	म_लिखो("\tRLIMIT_MSGQUEUE(hard):\t\t%ld\n", (दीर्घ) cur_limits.rlim_max);
	म_लिखो("\tMaximum Message Size:\t\t%d\n", cur_max_msgsize);
	म_लिखो("\tMaximum Queue Size:\t\t%d\n", cur_max_msgs);
	अगर (शेष_settings) अणु
		म_लिखो("\tDefault Message Size:\t\t%d\n", cur_def_msgsize);
		म_लिखो("\tDefault Queue Size:\t\t%d\n", cur_def_msgs);
	पूर्ण

	म_लिखो("\n\nTest series 1, behavior when no attr struct "
	       "passed to mq_open:\n");
	अगर (!शेष_settings) अणु
		test_queue(शून्य, &result);
		म_लिखो("Given sane system settings, mq_open without an attr "
		       "struct succeeds:\tPASS\n");
		अगर (result.mq_maxmsg != cur_max_msgs ||
		    result.mq_msgsize != cur_max_msgsize) अणु
			म_लिखो("Kernel does not support setting the default "
			       "mq attributes,\nbut also doesn't tie the "
			       "defaults to the maximums:\t\t\tPASS\n");
		पूर्ण अन्यथा अणु
			set(max_msgs, ++cur_max_msgs);
			set(max_msgsize, ++cur_max_msgsize);
			test_queue(शून्य, &result);
			अगर (result.mq_maxmsg == cur_max_msgs &&
			    result.mq_msgsize == cur_max_msgsize)
				म_लिखो("Kernel does not support setting the "
				       "default mq attributes and\n"
				       "also ties system wide defaults to "
				       "the system wide maximums:\t\t"
				       "FAIL\n");
			अन्यथा
				म_लिखो("Kernel does not support setting the "
				       "default mq attributes,\n"
				       "but also doesn't tie the defaults to "
				       "the maximums:\t\t\tPASS\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		म_लिखो("Kernel supports setting defaults separately from "
		       "maximums:\t\tPASS\n");
		/*
		 * While we are here, go ahead and test that the kernel
		 * properly follows the शेष settings
		 */
		test_queue(शून्य, &result);
		म_लिखो("Given sane values, mq_open without an attr struct "
		       "succeeds:\t\tPASS\n");
		अगर (result.mq_maxmsg != cur_def_msgs ||
		    result.mq_msgsize != cur_def_msgsize)
			म_लिखो("Kernel supports setting defaults, but does "
			       "not actually honor them:\tFAIL\n\n");
		अन्यथा अणु
			set(def_msgs, ++cur_def_msgs);
			set(def_msgsize, ++cur_def_msgsize);
			/* In हाल max was the same as the शेष */
			set(max_msgs, ++cur_max_msgs);
			set(max_msgsize, ++cur_max_msgsize);
			test_queue(शून्य, &result);
			अगर (result.mq_maxmsg != cur_def_msgs ||
			    result.mq_msgsize != cur_def_msgsize)
				म_लिखो("Kernel supports setting defaults, but "
				       "does not actually honor them:\t"
				       "FAIL\n");
			अन्यथा
				म_लिखो("Kernel properly honors default setting "
				       "knobs:\t\t\t\tPASS\n");
		पूर्ण
		set(def_msgs, cur_max_msgs + 1);
		cur_def_msgs = cur_max_msgs + 1;
		set(def_msgsize, cur_max_msgsize + 1);
		cur_def_msgsize = cur_max_msgsize + 1;
		अगर (cur_def_msgs * (cur_def_msgsize + 2 * माप(व्योम *)) >=
		    cur_limits.rlim_cur) अणु
			cur_limits.rlim_cur = (cur_def_msgs + 2) *
				(cur_def_msgsize + 2 * माप(व्योम *));
			cur_limits.rlim_max = 2 * cur_limits.rlim_cur;
			setr(RLIMIT_MSGQUEUE, &cur_limits);
		पूर्ण
		अगर (test_queue_fail(शून्य, &result)) अणु
			अगर (result.mq_maxmsg == cur_max_msgs &&
			    result.mq_msgsize == cur_max_msgsize)
				म_लिखो("Kernel properly limits default values "
				       "to lesser of default/max:\t\tPASS\n");
			अन्यथा
				म_लिखो("Kernel does not properly set default "
				       "queue parameters when\ndefaults > "
				       "max:\t\t\t\t\t\t\t\tFAIL\n");
		पूर्ण अन्यथा
			म_लिखो("Kernel fails to open mq because defaults are "
			       "greater than maximums:\tFAIL\n");
		set(def_msgs, --cur_def_msgs);
		set(def_msgsize, --cur_def_msgsize);
		cur_limits.rlim_cur = cur_limits.rlim_max = cur_def_msgs *
			cur_def_msgsize;
		setr(RLIMIT_MSGQUEUE, &cur_limits);
		अगर (test_queue_fail(शून्य, &result))
			म_लिखो("Kernel creates queue even though defaults "
			       "would exceed\nrlimit setting:"
			       "\t\t\t\t\t\t\t\tFAIL\n");
		अन्यथा
			म_लिखो("Kernel properly fails to create queue when "
			       "defaults would\nexceed rlimit:"
			       "\t\t\t\t\t\t\t\tPASS\n");
	पूर्ण

	/*
	 * Test #2 - खोलो with an attr काष्ठा that exceeds rlimit
	 */
	म_लिखो("\n\nTest series 2, behavior when attr struct is "
	       "passed to mq_open:\n");
	cur_max_msgs = 32;
	cur_max_msgsize = cur_limits.rlim_max >> 4;
	set(max_msgs, cur_max_msgs);
	set(max_msgsize, cur_max_msgsize);
	attr.mq_maxmsg = cur_max_msgs;
	attr.mq_msgsize = cur_max_msgsize;
	अगर (test_queue_fail(&attr, &result))
		म_लिखो("Queue open in excess of rlimit max when euid = 0 "
		       "succeeded:\t\tFAIL\n");
	अन्यथा
		म_लिखो("Queue open in excess of rlimit max when euid = 0 "
		       "failed:\t\tPASS\n");
	attr.mq_maxmsg = cur_max_msgs + 1;
	attr.mq_msgsize = 10;
	अगर (test_queue_fail(&attr, &result))
		म_लिखो("Queue open with mq_maxmsg > limit when euid = 0 "
		       "succeeded:\t\tPASS\n");
	अन्यथा
		म_लिखो("Queue open with mq_maxmsg > limit when euid = 0 "
		       "failed:\t\tFAIL\n");
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = cur_max_msgsize + 1;
	अगर (test_queue_fail(&attr, &result))
		म_लिखो("Queue open with mq_msgsize > limit when euid = 0 "
		       "succeeded:\t\tPASS\n");
	अन्यथा
		म_लिखो("Queue open with mq_msgsize > limit when euid = 0 "
		       "failed:\t\tFAIL\n");
	attr.mq_maxmsg = 65536;
	attr.mq_msgsize = 65536;
	अगर (test_queue_fail(&attr, &result))
		म_लिखो("Queue open with total size > 2GB when euid = 0 "
		       "succeeded:\t\tFAIL\n");
	अन्यथा
		म_लिखो("Queue open with total size > 2GB when euid = 0 "
		       "failed:\t\t\tPASS\n");

	अगर (seteuid(99) == -1) अणु
		लिखो_त्रुटि("seteuid() failed");
		निकास(1);
	पूर्ण

	attr.mq_maxmsg = cur_max_msgs;
	attr.mq_msgsize = cur_max_msgsize;
	अगर (test_queue_fail(&attr, &result))
		म_लिखो("Queue open in excess of rlimit max when euid = 99 "
		       "succeeded:\t\tFAIL\n");
	अन्यथा
		म_लिखो("Queue open in excess of rlimit max when euid = 99 "
		       "failed:\t\tPASS\n");
	attr.mq_maxmsg = cur_max_msgs + 1;
	attr.mq_msgsize = 10;
	अगर (test_queue_fail(&attr, &result))
		म_लिखो("Queue open with mq_maxmsg > limit when euid = 99 "
		       "succeeded:\t\tFAIL\n");
	अन्यथा
		म_लिखो("Queue open with mq_maxmsg > limit when euid = 99 "
		       "failed:\t\tPASS\n");
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = cur_max_msgsize + 1;
	अगर (test_queue_fail(&attr, &result))
		म_लिखो("Queue open with mq_msgsize > limit when euid = 99 "
		       "succeeded:\t\tFAIL\n");
	अन्यथा
		म_लिखो("Queue open with mq_msgsize > limit when euid = 99 "
		       "failed:\t\tPASS\n");
	attr.mq_maxmsg = 65536;
	attr.mq_msgsize = 65536;
	अगर (test_queue_fail(&attr, &result))
		म_लिखो("Queue open with total size > 2GB when euid = 99 "
		       "succeeded:\t\tFAIL\n");
	अन्यथा
		म_लिखो("Queue open with total size > 2GB when euid = 99 "
		       "failed:\t\t\tPASS\n");

	shutकरोwn(0,"",0);
पूर्ण
