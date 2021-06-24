<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test backward bit in event attribute, पढ़ो ring buffer from end to
 * beginning
 */

#समावेश <evlist.h>
#समावेश <sys/prctl.h>
#समावेश "record.h"
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "parse-events.h"
#समावेश "util/mmap.h"
#समावेश <त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <perf/mmap.h>

#घोषणा NR_ITERS 111

अटल व्योम testहाल(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_ITERS; i++) अणु
		अक्षर proc_name[15];

		snम_लिखो(proc_name, माप(proc_name), "p:%d\n", i);
		prctl(PR_SET_NAME, proc_name);
	पूर्ण
पूर्ण

अटल पूर्णांक count_samples(काष्ठा evlist *evlist, पूर्णांक *sample_count,
			 पूर्णांक *comm_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		काष्ठा mmap *map = &evlist->overग_लिखो_mmap[i];
		जोड़ perf_event *event;

		perf_mmap__पढ़ो_init(&map->core);
		जबतक ((event = perf_mmap__पढ़ो_event(&map->core)) != शून्य) अणु
			स्थिर u32 type = event->header.type;

			चयन (type) अणु
			हाल PERF_RECORD_SAMPLE:
				(*sample_count)++;
				अवरोध;
			हाल PERF_RECORD_COMM:
				(*comm_count)++;
				अवरोध;
			शेष:
				pr_err("Unexpected record of type %d\n", type);
				वापस TEST_FAIL;
			पूर्ण
		पूर्ण
		perf_mmap__पढ़ो_करोne(&map->core);
	पूर्ण
	वापस TEST_OK;
पूर्ण

अटल पूर्णांक करो_test(काष्ठा evlist *evlist, पूर्णांक mmap_pages,
		   पूर्णांक *sample_count, पूर्णांक *comm_count)
अणु
	पूर्णांक err;
	अक्षर sbuf[STRERR_बफ_मानE];

	err = evlist__mmap(evlist, mmap_pages);
	अगर (err < 0) अणु
		pr_debug("evlist__mmap: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		वापस TEST_FAIL;
	पूर्ण

	evlist__enable(evlist);
	testहाल();
	evlist__disable(evlist);

	err = count_samples(evlist, sample_count, comm_count);
	evlist__munmap(evlist);
	वापस err;
पूर्ण


पूर्णांक test__backward_ring_buffer(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret = TEST_SKIP, err, sample_count = 0, comm_count = 0;
	अक्षर pid[16], sbuf[STRERR_बफ_मानE];
	काष्ठा evlist *evlist;
	काष्ठा evsel *evsel __maybe_unused;
	काष्ठा parse_events_error parse_error;
	काष्ठा record_opts opts = अणु
		.target = अणु
			.uid = अच_पूर्णांक_उच्च,
			.uses_mmap = true,
		पूर्ण,
		.freq	      = 0,
		.mmap_pages   = 256,
		.शेष_पूर्णांकerval = 1,
	पूर्ण;

	snम_लिखो(pid, माप(pid), "%d", getpid());
	pid[माप(pid) - 1] = '\0';
	opts.target.tid = opts.target.pid = pid;

	evlist = evlist__new();
	अगर (!evlist) अणु
		pr_debug("Not enough memory to create evlist\n");
		वापस TEST_FAIL;
	पूर्ण

	err = evlist__create_maps(evlist, &opts.target);
	अगर (err < 0) अणु
		pr_debug("Not enough memory to create thread/cpu maps\n");
		जाओ out_delete_evlist;
	पूर्ण

	bzero(&parse_error, माप(parse_error));
	/*
	 * Set backward bit, ring buffer should be writing from end. Record
	 * it in aux evlist
	 */
	err = parse_events(evlist, "syscalls:sys_enter_prctl/overwrite/", &parse_error);
	अगर (err) अणु
		pr_debug("Failed to parse tracepoint event, try use root\n");
		ret = TEST_SKIP;
		जाओ out_delete_evlist;
	पूर्ण

	evlist__config(evlist, &opts, शून्य);

	err = evlist__खोलो(evlist);
	अगर (err < 0) अणु
		pr_debug("perf_evlist__open: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	ret = TEST_FAIL;
	err = करो_test(evlist, opts.mmap_pages, &sample_count,
		      &comm_count);
	अगर (err != TEST_OK)
		जाओ out_delete_evlist;

	अगर ((sample_count != NR_ITERS) || (comm_count != NR_ITERS)) अणु
		pr_err("Unexpected counter: sample_count=%d, comm_count=%d\n",
		       sample_count, comm_count);
		जाओ out_delete_evlist;
	पूर्ण

	evlist__बंद(evlist);

	err = evlist__खोलो(evlist);
	अगर (err < 0) अणु
		pr_debug("perf_evlist__open: %s\n",
			 str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_delete_evlist;
	पूर्ण

	err = करो_test(evlist, 1, &sample_count, &comm_count);
	अगर (err != TEST_OK)
		जाओ out_delete_evlist;

	ret = TEST_OK;
out_delete_evlist:
	evlist__delete(evlist);
	वापस ret;
पूर्ण
