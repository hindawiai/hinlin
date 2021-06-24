<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <stdbool.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "thread_map.h"
#समावेश "record.h"
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "util/mmap.h"
#समावेश <त्रुटिसं.स>
#समावेश <perf/mmap.h>

#अगर_अघोषित O_सूचीECTORY
#घोषणा O_सूचीECTORY    00200000
#पूर्ण_अगर
#अगर_अघोषित AT_FDCWD
#घोषणा AT_FDCWD       -100
#पूर्ण_अगर

पूर्णांक test__syscall_खोलोat_tp_fields(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा record_opts opts = अणु
		.target = अणु
			.uid = अच_पूर्णांक_उच्च,
			.uses_mmap = true,
		पूर्ण,
		.no_buffering = true,
		.freq	      = 1,
		.mmap_pages   = 256,
		.raw_samples  = true,
	पूर्ण;
	स्थिर अक्षर *filename = "/etc/passwd";
	पूर्णांक flags = O_RDONLY | O_सूचीECTORY;
	काष्ठा evlist *evlist = evlist__new();
	काष्ठा evsel *evsel;
	पूर्णांक err = -1, i, nr_events = 0, nr_polls = 0;
	अक्षर sbuf[STRERR_बफ_मानE];

	अगर (evlist == शून्य) अणु
		pr_debug("%s: evlist__new\n", __func__);
		जाओ out;
	पूर्ण

	evsel = evsel__newtp("syscalls", "sys_enter_openat");
	अगर (IS_ERR(evsel)) अणु
		pr_debug("%s: evsel__newtp\n", __func__);
		जाओ out_delete_evlist;
	पूर्ण

	evlist__add(evlist, evsel);

	err = evlist__create_maps(evlist, &opts.target);
	अगर (err < 0) अणु
		pr_debug("%s: evlist__create_maps\n", __func__);
		जाओ out_delete_evlist;
	पूर्ण

	evsel__config(evsel, &opts, शून्य);

	perf_thपढ़ो_map__set_pid(evlist->core.thपढ़ोs, 0, getpid());

	err = evlist__खोलो(evlist);
	अगर (err < 0) अणु
		pr_debug("perf_evlist__open: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	err = evlist__mmap(evlist, अच_पूर्णांक_उच्च);
	अगर (err < 0) अणु
		pr_debug("evlist__mmap: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	evlist__enable(evlist);

	/*
	 * Generate the event:
	 */
	खोलोat(AT_FDCWD, filename, flags);

	जबतक (1) अणु
		पूर्णांक beक्रमe = nr_events;

		क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
			जोड़ perf_event *event;
			काष्ठा mmap *md;

			md = &evlist->mmap[i];
			अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
				जारी;

			जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
				स्थिर u32 type = event->header.type;
				पूर्णांक tp_flags;
				काष्ठा perf_sample sample;

				++nr_events;

				अगर (type != PERF_RECORD_SAMPLE) अणु
					perf_mmap__consume(&md->core);
					जारी;
				पूर्ण

				err = evsel__parse_sample(evsel, event, &sample);
				अगर (err) अणु
					pr_debug("Can't parse sample, err = %d\n", err);
					जाओ out_delete_evlist;
				पूर्ण

				tp_flags = evsel__पूर्णांकval(evsel, &sample, "flags");

				अगर (flags != tp_flags) अणु
					pr_debug("%s: Expected flags=%#x, got %#x\n",
						 __func__, flags, tp_flags);
					जाओ out_delete_evlist;
				पूर्ण

				जाओ out_ok;
			पूर्ण
			perf_mmap__पढ़ो_करोne(&md->core);
		पूर्ण

		अगर (nr_events == beक्रमe)
			evlist__poll(evlist, 10);

		अगर (++nr_polls > 5) अणु
			pr_debug("%s: no events!\n", __func__);
			जाओ out_delete_evlist;
		पूर्ण
	पूर्ण
out_ok:
	err = 0;
out_delete_evlist:
	evlist__delete(evlist);
out:
	वापस err;
पूर्ण
