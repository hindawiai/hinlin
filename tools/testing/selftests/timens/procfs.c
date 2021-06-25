<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <गणित.स>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश "log.h"
#समावेश "timens.h"

/*
 * Test shouldn't be run क्रम a day, so add 10 days to child
 * समय and check parent's समय to be in the same day.
 */
#घोषणा MAX_TEST_TIME_SEC		(60*5)
#घोषणा DAY_IN_SEC			(60*60*24)
#घोषणा TEN_DAYS_IN_SEC			(10*DAY_IN_SEC)

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

अटल पूर्णांक child_ns, parent_ns;

अटल पूर्णांक चयन_ns(पूर्णांक fd)
अणु
	अगर (setns(fd, CLONE_NEWTIME))
		वापस pr_लिखो_त्रुटि("setns()");

	वापस 0;
पूर्ण

अटल पूर्णांक init_namespaces(व्योम)
अणु
	अक्षर path[] = "/proc/self/ns/time_for_children";
	काष्ठा stat st1, st2;

	parent_ns = खोलो(path, O_RDONLY);
	अगर (parent_ns <= 0)
		वापस pr_लिखो_त्रुटि("Unable to open %s", path);

	अगर (ख_स्थिति(parent_ns, &st1))
		वापस pr_लिखो_त्रुटि("Unable to stat the parent timens");

	अगर (unshare_समयns())
		वापस -1;

	child_ns = खोलो(path, O_RDONLY);
	अगर (child_ns <= 0)
		वापस pr_लिखो_त्रुटि("Unable to open %s", path);

	अगर (ख_स्थिति(child_ns, &st2))
		वापस pr_लिखो_त्रुटि("Unable to stat the timens");

	अगर (st1.st_ino == st2.st_ino)
		वापस pr_err("The same child_ns after CLONE_NEWTIME");

	अगर (_समय_रखो(CLOCK_BOOTTIME, TEN_DAYS_IN_SEC))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_proc_upसमय(काष्ठा बारpec *upसमय)
अणु
	अचिन्हित दीर्घ up_sec, up_nsec;
	खाता *proc;

	proc = ख_खोलो("/proc/uptime", "r");
	अगर (proc == शून्य) अणु
		pr_लिखो_त्रुटि("Unable to open /proc/uptime");
		वापस -1;
	पूर्ण

	अगर (ख_पूछो(proc, "%lu.%02lu", &up_sec, &up_nsec) != 2) अणु
		अगर (त्रुटि_सं) अणु
			pr_लिखो_त्रुटि("fscanf");
			वापस -त्रुटि_सं;
		पूर्ण
		pr_err("failed to parse /proc/uptime");
		वापस -1;
	पूर्ण
	ख_बंद(proc);

	upसमय->tv_sec = up_sec;
	upसमय->tv_nsec = up_nsec;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_proc_stat_bसमय(अचिन्हित दीर्घ दीर्घ *bootसमय_sec)
अणु
	खाता *proc;
	अक्षर line_buf[2048];

	proc = ख_खोलो("/proc/stat", "r");
	अगर (proc == शून्य) अणु
		pr_लिखो_त्रुटि("Unable to open /proc/stat");
		वापस -1;
	पूर्ण

	जबतक (ख_माला_लो(line_buf, 2048, proc)) अणु
		अगर (माला_पूछो(line_buf, "btime %llu", bootसमय_sec) != 1)
			जारी;
		ख_बंद(proc);
		वापस 0;
	पूर्ण
	अगर (त्रुटि_सं) अणु
		pr_लिखो_त्रुटि("fscanf");
		ख_बंद(proc);
		वापस -त्रुटि_सं;
	पूर्ण
	pr_err("failed to parse /proc/stat");
	ख_बंद(proc);
	वापस -1;
पूर्ण

अटल पूर्णांक check_upसमय(व्योम)
अणु
	काष्ठा बारpec upसमय_new, upसमय_old;
	समय_प्रकार upसमय_expected;
	द्विगुन prec = MAX_TEST_TIME_SEC;

	अगर (चयन_ns(parent_ns))
		वापस pr_err("switch_ns(%d)", parent_ns);

	अगर (पढ़ो_proc_upसमय(&upसमय_old))
		वापस 1;

	अगर (चयन_ns(child_ns))
		वापस pr_err("switch_ns(%d)", child_ns);

	अगर (पढ़ो_proc_upसमय(&upसमय_new))
		वापस 1;

	upसमय_expected = upसमय_old.tv_sec + TEN_DAYS_IN_SEC;
	अगर (भ_असल(स_अंतर(upसमय_new.tv_sec, upसमय_expected)) > prec) अणु
		pr_fail("uptime in /proc/uptime: old %ld, new %ld [%ld]",
			upसमय_old.tv_sec, upसमय_new.tv_sec,
			upसमय_old.tv_sec + TEN_DAYS_IN_SEC);
		वापस 1;
	पूर्ण

	ksft_test_result_pass("Passed for /proc/uptime\n");
	वापस 0;
पूर्ण

अटल पूर्णांक check_stat_bसमय(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ bसमय_new, bसमय_old;
	अचिन्हित दीर्घ दीर्घ bसमय_expected;

	अगर (चयन_ns(parent_ns))
		वापस pr_err("switch_ns(%d)", parent_ns);

	अगर (पढ़ो_proc_stat_bसमय(&bसमय_old))
		वापस 1;

	अगर (चयन_ns(child_ns))
		वापस pr_err("switch_ns(%d)", child_ns);

	अगर (पढ़ो_proc_stat_bसमय(&bसमय_new))
		वापस 1;

	bसमय_expected = bसमय_old - TEN_DAYS_IN_SEC;
	अगर (bसमय_new != bसमय_expected) अणु
		pr_fail("btime in /proc/stat: old %llu, new %llu [%llu]",
			bसमय_old, bसमय_new, bसमय_expected);
		वापस 1;
	पूर्ण

	ksft_test_result_pass("Passed for /proc/stat btime\n");
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ret = 0;

	nscheck();

	ksft_set_plan(2);

	अगर (init_namespaces())
		वापस 1;

	ret |= check_upसमय();
	ret |= check_stat_bसमय();

	अगर (ret)
		ksft_निकास_fail();
	ksft_निकास_pass();
	वापस ret;
पूर्ण
