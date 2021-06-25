<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <api/fs/tracing_path.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश "thread_map.h"
#समावेश "evsel.h"
#समावेश "debug.h"
#समावेश "tests.h"
#समावेश "util/counts.h"

पूर्णांक test__खोलोat_syscall_event(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = -1, fd;
	काष्ठा evsel *evsel;
	अचिन्हित पूर्णांक nr_खोलोat_calls = 111, i;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = thपढ़ो_map__new(-1, getpid(), अच_पूर्णांक_उच्च);
	अक्षर sbuf[STRERR_बफ_मानE];
	अक्षर errbuf[बफ_मान];

	अगर (thपढ़ोs == शून्य) अणु
		pr_debug("thread_map__new\n");
		वापस -1;
	पूर्ण

	evsel = evsel__newtp("syscalls", "sys_enter_openat");
	अगर (IS_ERR(evsel)) अणु
		tracing_path__म_त्रुटि_खोलो_tp(त्रुटि_सं, errbuf, माप(errbuf), "syscalls", "sys_enter_openat");
		pr_debug("%s\n", errbuf);
		जाओ out_thपढ़ो_map_delete;
	पूर्ण

	अगर (evsel__खोलो_per_thपढ़ो(evsel, thपढ़ोs) < 0) अणु
		pr_debug("failed to open counter: %s, "
			 "tweak /proc/sys/kernel/perf_event_paranoid?\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_evsel_delete;
	पूर्ण

	क्रम (i = 0; i < nr_खोलोat_calls; ++i) अणु
		fd = खोलोat(0, "/etc/passwd", O_RDONLY);
		बंद(fd);
	पूर्ण

	अगर (evsel__पढ़ो_on_cpu(evsel, 0, 0) < 0) अणु
		pr_debug("evsel__read_on_cpu\n");
		जाओ out_बंद_fd;
	पूर्ण

	अगर (perf_counts(evsel->counts, 0, 0)->val != nr_खोलोat_calls) अणु
		pr_debug("evsel__read_on_cpu: expected to intercept %d calls, got %" PRIu64 "\n",
			 nr_खोलोat_calls, perf_counts(evsel->counts, 0, 0)->val);
		जाओ out_बंद_fd;
	पूर्ण

	err = 0;
out_बंद_fd:
	perf_evsel__बंद_fd(&evsel->core);
out_evsel_delete:
	evsel__delete(evsel);
out_thपढ़ो_map_delete:
	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस err;
पूर्ण
