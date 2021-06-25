<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The काष्ठा perf_event_attr test support.
 *
 * This test is embedded inside पूर्णांकo perf directly and is governed
 * by the PERF_TEST_ATTR environment variable and hook inside
 * sys_perf_event_खोलो function.
 *
 * The general idea is to store 'struct perf_event_attr' details क्रम
 * each event created within single perf command. Each event details
 * are stored पूर्णांकo separate text file. Once perf command is finished
 * these files can be checked क्रम values we expect क्रम command.
 *
 * Besides 'struct perf_event_attr' values we also store 'fd' and
 * 'group_fd' values to allow checking क्रम groups created.
 *
 * This all is triggered by setting PERF_TEST_ATTR environment variable.
 * It must contain name of existing directory with access and ग_लिखो
 * permissions. All the event text files are stored there.
 */

#समावेश <debug.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <sys/param.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <subcmd/exec-cmd.h>
#समावेश "event.h"
#समावेश "util.h"
#समावेश "tests.h"
#समावेश "pmu.h"

#घोषणा ENV "PERF_TEST_ATTR"

अटल अक्षर *dir;
अटल bool पढ़ोy;

व्योम test_attr__init(व्योम)
अणु
	dir = दो_पर्या(ENV);
	test_attr__enabled = (dir != शून्य);
पूर्ण

#घोषणा बफ_मानE 1024

#घोषणा __WRITE_ASS(str, fmt, data)					\
करो अणु									\
	अक्षर buf[बफ_मानE];						\
	माप_प्रकार size;							\
									\
	size = snम_लिखो(buf, बफ_मानE, #str "=%"fmt "\n", data);		\
	अगर (1 != ख_डालो(buf, size, 1, file)) अणु				\
		लिखो_त्रुटि("test attr - failed to write event file");	\
		ख_बंद(file);						\
		वापस -1;						\
	पूर्ण								\
									\
पूर्ण जबतक (0)

#घोषणा WRITE_ASS(field, fmt) __WRITE_ASS(field, fmt, attr->field)

अटल पूर्णांक store_event(काष्ठा perf_event_attr *attr, pid_t pid, पूर्णांक cpu,
		       पूर्णांक fd, पूर्णांक group_fd, अचिन्हित दीर्घ flags)
अणु
	खाता *file;
	अक्षर path[PATH_MAX];

	अगर (!पढ़ोy)
		वापस 0;

	snम_लिखो(path, PATH_MAX, "%s/event-%d-%llu-%d", dir,
		 attr->type, attr->config, fd);

	file = ख_खोलो(path, "w+");
	अगर (!file) अणु
		लिखो_त्रुटि("test attr - failed to open event file");
		वापस -1;
	पूर्ण

	अगर (ख_लिखो(file, "[event-%d-%llu-%d]\n",
		    attr->type, attr->config, fd) < 0) अणु
		लिखो_त्रुटि("test attr - failed to write event file");
		ख_बंद(file);
		वापस -1;
	पूर्ण

	/* syscall arguments */
	__WRITE_ASS(fd,       "d", fd);
	__WRITE_ASS(group_fd, "d", group_fd);
	__WRITE_ASS(cpu,      "d", cpu);
	__WRITE_ASS(pid,      "d", pid);
	__WRITE_ASS(flags,   "lu", flags);

	/* काष्ठा perf_event_attr */
	WRITE_ASS(type,   PRIu32);
	WRITE_ASS(size,   PRIu32);
	WRITE_ASS(config,  "llu");
	WRITE_ASS(sample_period, "llu");
	WRITE_ASS(sample_type,   "llu");
	WRITE_ASS(पढ़ो_क्रमmat,   "llu");
	WRITE_ASS(disabled,       "d");
	WRITE_ASS(inherit,        "d");
	WRITE_ASS(pinned,         "d");
	WRITE_ASS(exclusive,      "d");
	WRITE_ASS(exclude_user,   "d");
	WRITE_ASS(exclude_kernel, "d");
	WRITE_ASS(exclude_hv,     "d");
	WRITE_ASS(exclude_idle,   "d");
	WRITE_ASS(mmap,           "d");
	WRITE_ASS(comm,           "d");
	WRITE_ASS(freq,           "d");
	WRITE_ASS(inherit_stat,   "d");
	WRITE_ASS(enable_on_exec, "d");
	WRITE_ASS(task,           "d");
	WRITE_ASS(watermark,      "d");
	WRITE_ASS(precise_ip,     "d");
	WRITE_ASS(mmap_data,      "d");
	WRITE_ASS(sample_id_all,  "d");
	WRITE_ASS(exclude_host,   "d");
	WRITE_ASS(exclude_guest,  "d");
	WRITE_ASS(exclude_callchain_kernel, "d");
	WRITE_ASS(exclude_callchain_user, "d");
	WRITE_ASS(mmap2,	  "d");
	WRITE_ASS(comm_exec,	  "d");
	WRITE_ASS(context_चयन, "d");
	WRITE_ASS(ग_लिखो_backward, "d");
	WRITE_ASS(namespaces,	  "d");
	WRITE_ASS(use_घड़ीid,    "d");
	WRITE_ASS(wakeup_events, PRIu32);
	WRITE_ASS(bp_type, PRIu32);
	WRITE_ASS(config1, "llu");
	WRITE_ASS(config2, "llu");
	WRITE_ASS(branch_sample_type, "llu");
	WRITE_ASS(sample_regs_user,   "llu");
	WRITE_ASS(sample_stack_user,  PRIu32);

	ख_बंद(file);
	वापस 0;
पूर्ण

व्योम test_attr__खोलो(काष्ठा perf_event_attr *attr, pid_t pid, पूर्णांक cpu,
		     पूर्णांक fd, पूर्णांक group_fd, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक त्रुटि_सं_saved = त्रुटि_सं;

	अगर ((fd != -1) && store_event(attr, pid, cpu, fd, group_fd, flags)) अणु
		pr_err("test attr FAILED");
		निकास(128);
	पूर्ण

	त्रुटि_सं = त्रुटि_सं_saved;
पूर्ण

व्योम test_attr__पढ़ोy(व्योम)
अणु
	अगर (unlikely(test_attr__enabled) && !पढ़ोy)
		पढ़ोy = true;
पूर्ण

अटल पूर्णांक run_dir(स्थिर अक्षर *d, स्थिर अक्षर *perf)
अणु
	अक्षर v[] = "-vvvvv";
	पूर्णांक vcnt = min(verbose, (पूर्णांक) माप(v) - 1);
	अक्षर cmd[3*PATH_MAX];

	अगर (verbose > 0)
		vcnt++;

	scnम_लिखो(cmd, 3*PATH_MAX, PYTHON " %s/attr.py -d %s/attr/ -p %s %.*s",
		  d, d, perf, vcnt, v);

	वापस प्रणाली(cmd) ? TEST_FAIL : TEST_OK;
पूर्ण

पूर्णांक test__attr(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा stat st;
	अक्षर path_perf[PATH_MAX];
	अक्षर path_dir[PATH_MAX];
	अक्षर *exec_path;

	अगर (perf_pmu__has_hybrid())
		वापस TEST_SKIP;

	/* First try development tree tests. */
	अगर (!lstat("./tests", &st))
		वापस run_dir("./tests", "./perf");

	exec_path = get_argv_exec_path();
	अगर (exec_path == शून्य)
		वापस -1;

	/* Then installed path. */
	snम_लिखो(path_dir,  PATH_MAX, "%s/tests", exec_path);
	snम_लिखो(path_perf, PATH_MAX, "%s/perf", BINसूची);
	मुक्त(exec_path);

	अगर (!lstat(path_dir, &st) &&
	    !lstat(path_perf, &st))
		वापस run_dir(path_dir, path_perf);

	वापस TEST_SKIP;
पूर्ण
