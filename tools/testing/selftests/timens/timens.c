<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <माला.स>

#समावेश "log.h"
#समावेश "timens.h"

/*
 * Test shouldn't be run क्रम a day, so add 10 days to child
 * समय and check parent's समय to be in the same day.
 */
#घोषणा DAY_IN_SEC			(60*60*24)
#घोषणा TEN_DAYS_IN_SEC			(10*DAY_IN_SEC)

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

काष्ठा test_घड़ी अणु
	घड़ीid_t id;
	अक्षर *name;
	/*
	 * off_id is -1 अगर a घड़ी has own offset, or it contains an index
	 * which contains a right offset of this घड़ी.
	 */
	पूर्णांक off_id;
	समय_प्रकार offset;
पूर्ण;

#घोषणा ct(घड़ी, off_id)	अणु घड़ी, #घड़ी, off_id पूर्ण
अटल काष्ठा test_घड़ी घड़ीs[] = अणु
	ct(CLOCK_BOOTTIME, -1),
	ct(CLOCK_BOOTTIME_ALARM, 1),
	ct(CLOCK_MONOTONIC, -1),
	ct(CLOCK_MONOTONIC_COARSE, 1),
	ct(CLOCK_MONOTONIC_RAW, 1),
पूर्ण;
#अघोषित ct

अटल पूर्णांक child_ns, parent_ns = -1;

अटल पूर्णांक चयन_ns(पूर्णांक fd)
अणु
	अगर (setns(fd, CLONE_NEWTIME)) अणु
		pr_लिखो_त्रुटि("setns()");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_namespaces(व्योम)
अणु
	अक्षर path[] = "/proc/self/ns/time_for_children";
	काष्ठा stat st1, st2;

	अगर (parent_ns == -1) अणु
		parent_ns = खोलो(path, O_RDONLY);
		अगर (parent_ns <= 0)
			वापस pr_लिखो_त्रुटि("Unable to open %s", path);
	पूर्ण

	अगर (ख_स्थिति(parent_ns, &st1))
		वापस pr_लिखो_त्रुटि("Unable to stat the parent timens");

	अगर (unshare_समयns())
		वापस  -1;

	child_ns = खोलो(path, O_RDONLY);
	अगर (child_ns <= 0)
		वापस pr_लिखो_त्रुटि("Unable to open %s", path);

	अगर (ख_स्थिति(child_ns, &st2))
		वापस pr_लिखो_त्रुटि("Unable to stat the timens");

	अगर (st1.st_ino == st2.st_ino)
		वापस pr_लिखो_त्रुटि("The same child_ns after CLONE_NEWTIME");

	वापस 0;
पूर्ण

अटल पूर्णांक test_समय_लो(घड़ीid_t घड़ी_index, bool raw_syscall, समय_प्रकार offset)
अणु
	काष्ठा बारpec child_ts_new, parent_ts_old, cur_ts;
	अक्षर *entry = raw_syscall ? "syscall" : "vdso";
	द्विगुन precision = 0.0;

	अगर (check_skip(घड़ीs[घड़ी_index].id))
		वापस 0;

	चयन (घड़ीs[घड़ी_index].id) अणु
	हाल CLOCK_MONOTONIC_COARSE:
	हाल CLOCK_MONOTONIC_RAW:
		precision = -2.0;
		अवरोध;
	पूर्ण

	अगर (चयन_ns(parent_ns))
		वापस pr_err("switch_ns(%d)", child_ns);

	अगर (_समय_लो(घड़ीs[घड़ी_index].id, &parent_ts_old, raw_syscall))
		वापस -1;

	child_ts_new.tv_nsec = parent_ts_old.tv_nsec;
	child_ts_new.tv_sec = parent_ts_old.tv_sec + offset;

	अगर (चयन_ns(child_ns))
		वापस pr_err("switch_ns(%d)", child_ns);

	अगर (_समय_लो(घड़ीs[घड़ी_index].id, &cur_ts, raw_syscall))
		वापस -1;

	अगर (स_अंतर(cur_ts.tv_sec, child_ts_new.tv_sec) < precision) अणु
		ksft_test_result_fail(
			"Child's %s (%s) time has not changed: %lu -> %lu [%lu]\n",
			घड़ीs[घड़ी_index].name, entry, parent_ts_old.tv_sec,
			child_ts_new.tv_sec, cur_ts.tv_sec);
		वापस -1;
	पूर्ण

	अगर (चयन_ns(parent_ns))
		वापस pr_err("switch_ns(%d)", parent_ns);

	अगर (_समय_लो(घड़ीs[घड़ी_index].id, &cur_ts, raw_syscall))
		वापस -1;

	अगर (स_अंतर(cur_ts.tv_sec, parent_ts_old.tv_sec) > DAY_IN_SEC) अणु
		ksft_test_result_fail(
			"Parent's %s (%s) time has changed: %lu -> %lu [%lu]\n",
			घड़ीs[घड़ी_index].name, entry, parent_ts_old.tv_sec,
			child_ts_new.tv_sec, cur_ts.tv_sec);
		/* Let's play nice and put it बंदr to original */
		घड़ी_समय_रखो(घड़ीs[घड़ी_index].id, &cur_ts);
		वापस -1;
	पूर्ण

	ksft_test_result_pass("Passed for %s (%s)\n",
				घड़ीs[घड़ी_index].name, entry);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अचिन्हित पूर्णांक i;
	समय_प्रकार offset;
	पूर्णांक ret = 0;

	nscheck();

	check_supported_समयrs();

	ksft_set_plan(ARRAY_SIZE(घड़ीs) * 2);

	अगर (init_namespaces())
		वापस 1;

	/* Offsets have to be set beक्रमe tasks enter the namespace. */
	क्रम (i = 0; i < ARRAY_SIZE(घड़ीs); i++) अणु
		अगर (घड़ीs[i].off_id != -1)
			जारी;
		offset = TEN_DAYS_IN_SEC + i * 1000;
		घड़ीs[i].offset = offset;
		अगर (_समय_रखो(घड़ीs[i].id, offset))
			वापस 1;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(घड़ीs); i++) अणु
		अगर (घड़ीs[i].off_id != -1)
			offset = घड़ीs[घड़ीs[i].off_id].offset;
		अन्यथा
			offset = घड़ीs[i].offset;
		ret |= test_समय_लो(i, true, offset);
		ret |= test_समय_लो(i, false, offset);
	पूर्ण

	अगर (ret)
		ksft_निकास_fail();

	ksft_निकास_pass();
	वापस !!ret;
पूर्ण
