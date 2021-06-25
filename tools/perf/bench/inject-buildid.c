<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>
#समावेश <मानकघोष.स>
#समावेश <ftw.h>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <pthपढ़ो.h>
#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय64.h>
#समावेश <linux/list.h>
#समावेश <linux/err.h>
#समावेश <पूर्णांकernal/lib.h>
#समावेश <subcmd/parse-options.h>

#समावेश "bench.h"
#समावेश "util/data.h"
#समावेश "util/stat.h"
#समावेश "util/debug.h"
#समावेश "util/event.h"
#समावेश "util/symbol.h"
#समावेश "util/session.h"
#समावेश "util/build-id.h"
#समावेश "util/synthetic-events.h"

#घोषणा MMAP_DEV_MAJOR  8
#घोषणा DSO_MMAP_RATIO  4

अटल अचिन्हित पूर्णांक iterations = 100;
अटल अचिन्हित पूर्णांक nr_mmaps   = 100;
अटल अचिन्हित पूर्णांक nr_samples = 100;  /* samples per mmap */

अटल u64 bench_sample_type;
अटल u16 bench_id_hdr_size;

काष्ठा bench_data अणु
	पूर्णांक			pid;
	पूर्णांक			input_pipe[2];
	पूर्णांक			output_pipe[2];
	pthपढ़ो_t		th;
पूर्ण;

काष्ठा bench_dso अणु
	काष्ठा list_head	list;
	अक्षर			*name;
	पूर्णांक			ino;
पूर्ण;

अटल पूर्णांक nr_dsos;
अटल काष्ठा bench_dso *dsos;

बाह्य पूर्णांक cmd_inject(पूर्णांक argc, स्थिर अक्षर *argv[]);

अटल स्थिर काष्ठा option options[] = अणु
	OPT_UINTEGER('i', "iterations", &iterations,
		     "Number of iterations used to compute average (default: 100)"),
	OPT_UINTEGER('m', "nr-mmaps", &nr_mmaps,
		     "Number of mmap events for each iteration (default: 100)"),
	OPT_UINTEGER('n', "nr-samples", &nr_samples,
		     "Number of sample events per mmap event (default: 100)"),
	OPT_INCR('v', "verbose", &verbose,
		 "be more verbose (show iteration count, DSO name, etc)"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर *स्थिर bench_usage[] = अणु
	"perf bench internals inject-build-id <options>",
	शून्य
पूर्ण;

/*
 * Helper क्रम collect_dso that adds the given file as a dso to dso_list
 * अगर it contains a build-id.  Stops after collecting 4 बार more than
 * we need (क्रम MMAP2 events).
 */
अटल पूर्णांक add_dso(स्थिर अक्षर *fpath, स्थिर काष्ठा stat *sb __maybe_unused,
		   पूर्णांक typeflag, काष्ठा FTW *ftwbuf __maybe_unused)
अणु
	काष्ठा bench_dso *dso = &dsos[nr_dsos];
	काष्ठा build_id bid;

	अगर (typeflag == FTW_D || typeflag == FTW_SL)
		वापस 0;

	अगर (filename__पढ़ो_build_id(fpath, &bid) < 0)
		वापस 0;

	dso->name = realpath(fpath, शून्य);
	अगर (dso->name == शून्य)
		वापस -1;

	dso->ino = nr_dsos++;
	pr_debug2("  Adding DSO: %s\n", fpath);

	/* stop अगर we collected enough DSOs */
	अगर ((अचिन्हित पूर्णांक)nr_dsos == DSO_MMAP_RATIO * nr_mmaps)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम collect_dso(व्योम)
अणु
	dsos = सुस्मृति(nr_mmaps * DSO_MMAP_RATIO, माप(*dsos));
	अगर (dsos == शून्य) अणु
		म_लिखो("  Memory allocation failed\n");
		निकास(1);
	पूर्ण

	अगर (nftw("/usr/lib/", add_dso, 10, FTW_PHYS) < 0)
		वापस;

	pr_debug("  Collected %d DSOs\n", nr_dsos);
पूर्ण

अटल व्योम release_dso(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_dsos; i++) अणु
		काष्ठा bench_dso *dso = &dsos[i];

		मुक्त(dso->name);
	पूर्ण
	मुक्त(dsos);
पूर्ण

/* Fake address used by mmap and sample events */
अटल u64 dso_map_addr(काष्ठा bench_dso *dso)
अणु
	वापस 0x400000ULL + dso->ino * 8192ULL;
पूर्ण

अटल u32 synthesize_attr(काष्ठा bench_data *data)
अणु
	जोड़ perf_event event;

	स_रखो(&event, 0, माप(event.attr) + माप(u64));

	event.header.type = PERF_RECORD_HEADER_ATTR;
	event.header.size = माप(event.attr) + माप(u64);

	event.attr.attr.type = PERF_TYPE_SOFTWARE;
	event.attr.attr.config = PERF_COUNT_SW_TASK_CLOCK;
	event.attr.attr.exclude_kernel = 1;
	event.attr.attr.sample_id_all = 1;
	event.attr.attr.sample_type = bench_sample_type;

	वापस ग_लिखोn(data->input_pipe[1], &event, event.header.size);
पूर्ण

अटल u32 synthesize_विभाजन(काष्ठा bench_data *data)
अणु
	जोड़ perf_event event;

	स_रखो(&event, 0, माप(event.विभाजन) + bench_id_hdr_size);

	event.header.type = PERF_RECORD_FORK;
	event.header.misc = PERF_RECORD_MISC_FORK_EXEC;
	event.header.size = माप(event.विभाजन) + bench_id_hdr_size;

	event.विभाजन.ppid = 1;
	event.विभाजन.ptid = 1;
	event.विभाजन.pid = data->pid;
	event.विभाजन.tid = data->pid;

	वापस ग_लिखोn(data->input_pipe[1], &event, event.header.size);
पूर्ण

अटल u32 synthesize_mmap(काष्ठा bench_data *data, काष्ठा bench_dso *dso,
			   u64 बारtamp)
अणु
	जोड़ perf_event event;
	माप_प्रकार len = दुरत्व(काष्ठा perf_record_mmap2, filename);
	u64 *id_hdr_ptr = (व्योम *)&event;
	पूर्णांक ts_idx;

	len += roundup(म_माप(dso->name) + 1, 8) + bench_id_hdr_size;

	स_रखो(&event, 0, min(len, माप(event.mmap2)));

	event.header.type = PERF_RECORD_MMAP2;
	event.header.misc = PERF_RECORD_MISC_USER;
	event.header.size = len;

	event.mmap2.pid = data->pid;
	event.mmap2.tid = data->pid;
	event.mmap2.maj = MMAP_DEV_MAJOR;
	event.mmap2.ino = dso->ino;

	म_नकल(event.mmap2.filename, dso->name);

	event.mmap2.start = dso_map_addr(dso);
	event.mmap2.len = 4096;
	event.mmap2.prot = PROT_EXEC;

	अगर (len > माप(event.mmap2)) अणु
		/* ग_लिखो mmap2 event first */
		ग_लिखोn(data->input_pipe[1], &event, len - bench_id_hdr_size);
		/* zero-fill sample id header */
		स_रखो(id_hdr_ptr, 0, bench_id_hdr_size);
		/* put बारtamp in the right position */
		ts_idx = (bench_id_hdr_size / माप(u64)) - 2;
		id_hdr_ptr[ts_idx] = बारtamp;
		ग_लिखोn(data->input_pipe[1], id_hdr_ptr, bench_id_hdr_size);
	पूर्ण अन्यथा अणु
		ts_idx = (len / माप(u64)) - 2;
		id_hdr_ptr[ts_idx] = बारtamp;
		ग_लिखोn(data->input_pipe[1], &event, len);
	पूर्ण
	वापस len;
पूर्ण

अटल u32 synthesize_sample(काष्ठा bench_data *data, काष्ठा bench_dso *dso,
			     u64 बारtamp)
अणु
	जोड़ perf_event event;
	काष्ठा perf_sample sample = अणु
		.tid = data->pid,
		.pid = data->pid,
		.ip = dso_map_addr(dso),
		.समय = बारtamp,
	पूर्ण;

	event.header.type = PERF_RECORD_SAMPLE;
	event.header.misc = PERF_RECORD_MISC_USER;
	event.header.size = perf_event__sample_event_size(&sample, bench_sample_type, 0);

	perf_event__synthesize_sample(&event, bench_sample_type, 0, &sample);

	वापस ग_लिखोn(data->input_pipe[1], &event, event.header.size);
पूर्ण

अटल u32 synthesize_flush(काष्ठा bench_data *data)
अणु
	काष्ठा perf_event_header header = अणु
		.size = माप(header),
		.type = PERF_RECORD_FINISHED_ROUND,
	पूर्ण;

	वापस ग_लिखोn(data->input_pipe[1], &header, header.size);
पूर्ण

अटल व्योम *data_पढ़ोer(व्योम *arg)
अणु
	काष्ठा bench_data *data = arg;
	अक्षर buf[8192];
	पूर्णांक flag;
	पूर्णांक n;

	flag = fcntl(data->output_pipe[0], F_GETFL);
	fcntl(data->output_pipe[0], F_SETFL, flag | O_NONBLOCK);

	/* पढ़ो out data from child */
	जबतक (true) अणु
		n = पढ़ो(data->output_pipe[0], buf, माप(buf));
		अगर (n > 0)
			जारी;
		अगर (n == 0)
			अवरोध;

		अगर (त्रुटि_सं != EINTR && त्रुटि_सं != EAGAIN)
			अवरोध;

		usleep(100);
	पूर्ण

	बंद(data->output_pipe[0]);
	वापस शून्य;
पूर्ण

अटल पूर्णांक setup_injection(काष्ठा bench_data *data, bool build_id_all)
अणु
	पूर्णांक पढ़ोy_pipe[2];
	पूर्णांक dev_null_fd;
	अक्षर buf;

	अगर (pipe(पढ़ोy_pipe) < 0)
		वापस -1;

	अगर (pipe(data->input_pipe) < 0)
		वापस -1;

	अगर (pipe(data->output_pipe) < 0)
		वापस -1;

	data->pid = विभाजन();
	अगर (data->pid < 0)
		वापस -1;

	अगर (data->pid == 0) अणु
		स्थिर अक्षर **inject_argv;
		पूर्णांक inject_argc = 2;

		बंद(data->input_pipe[1]);
		बंद(data->output_pipe[0]);
		बंद(पढ़ोy_pipe[0]);

		dup2(data->input_pipe[0], STDIN_खाताNO);
		बंद(data->input_pipe[0]);
		dup2(data->output_pipe[1], STDOUT_खाताNO);
		बंद(data->output_pipe[1]);

		dev_null_fd = खोलो("/dev/null", O_WRONLY);
		अगर (dev_null_fd < 0)
			निकास(1);

		dup2(dev_null_fd, STDERR_खाताNO);

		अगर (build_id_all)
			inject_argc++;

		inject_argv = सुस्मृति(inject_argc + 1, माप(*inject_argv));
		अगर (inject_argv == शून्य)
			निकास(1);

		inject_argv[0] = strdup("inject");
		inject_argv[1] = strdup("-b");
		अगर (build_id_all)
			inject_argv[2] = strdup("--buildid-all");

		/* संकेत that we're पढ़ोy to go */
		बंद(पढ़ोy_pipe[1]);

		cmd_inject(inject_argc, inject_argv);

		निकास(0);
	पूर्ण

	pthपढ़ो_create(&data->th, शून्य, data_पढ़ोer, data);

	बंद(पढ़ोy_pipe[1]);
	बंद(data->input_pipe[0]);
	बंद(data->output_pipe[1]);

	/* रुको क्रम child पढ़ोy */
	अगर (पढ़ो(पढ़ोy_pipe[0], &buf, 1) < 0)
		वापस -1;
	बंद(पढ़ोy_pipe[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक inject_build_id(काष्ठा bench_data *data, u64 *max_rss)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक i, k;
	काष्ठा rusage rusage;
	u64 len = 0;

	/* this makes the child to run */
	अगर (perf_header__ग_लिखो_pipe(data->input_pipe[1]) < 0)
		वापस -1;

	len += synthesize_attr(data);
	len += synthesize_विभाजन(data);

	क्रम (i = 0; i < nr_mmaps; i++) अणु
		पूर्णांक idx = अक्रम() % (nr_dsos - 1);
		काष्ठा bench_dso *dso = &dsos[idx];
		u64 बारtamp = अक्रम() % 1000000;

		pr_debug2("   [%d] injecting: %s\n", i+1, dso->name);
		len += synthesize_mmap(data, dso, बारtamp);

		क्रम (k = 0; k < nr_samples; k++)
			len += synthesize_sample(data, dso, बारtamp + k * 1000);

		अगर ((i + 1) % 10 == 0)
			len += synthesize_flush(data);
	पूर्ण

	/* this makes the child to finish */
	बंद(data->input_pipe[1]);

	रुको4(data->pid, &status, 0, &rusage);
	*max_rss = rusage.ru_maxrss;

	pr_debug("   Child %d exited with %d\n", data->pid, status);

	वापस 0;
पूर्ण

अटल व्योम करो_inject_loop(काष्ठा bench_data *data, bool build_id_all)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा stats समय_stats, mem_stats;
	द्विगुन समय_average, समय_stddev;
	द्विगुन mem_average, mem_stddev;

	init_stats(&समय_stats);
	init_stats(&mem_stats);

	pr_debug("  Build-id%s injection benchmark\n", build_id_all ? "-all" : "");

	क्रम (i = 0; i < iterations; i++) अणु
		काष्ठा समयval start, end, dअगरf;
		u64 runसमय_us, max_rss;

		pr_debug("  Iteration #%d\n", i+1);

		अगर (setup_injection(data, build_id_all) < 0) अणु
			म_लिखो("  Build-id injection setup failed\n");
			अवरोध;
		पूर्ण

		समय_लोofday(&start, शून्य);
		अगर (inject_build_id(data, &max_rss) < 0) अणु
			म_लिखो("  Build-id injection failed\n");
			अवरोध;
		पूर्ण

		समय_लोofday(&end, शून्य);
		समयrsub(&end, &start, &dअगरf);
		runसमय_us = dअगरf.tv_sec * USEC_PER_SEC + dअगरf.tv_usec;
		update_stats(&समय_stats, runसमय_us);
		update_stats(&mem_stats, max_rss);

		pthपढ़ो_join(data->th, शून्य);
	पूर्ण

	समय_average = avg_stats(&समय_stats) / USEC_PER_MSEC;
	समय_stddev = stddev_stats(&समय_stats) / USEC_PER_MSEC;
	म_लिखो("  Average build-id%s injection took: %.3f msec (+- %.3f msec)\n",
	       build_id_all ? "-all" : "", समय_average, समय_stddev);

	/* each iteration, it processes MMAP2 + BUILD_ID + nr_samples * SAMPLE */
	समय_average = avg_stats(&समय_stats) / (nr_mmaps * (nr_samples + 2));
	समय_stddev = stddev_stats(&समय_stats) / (nr_mmaps * (nr_samples + 2));
	म_लिखो("  Average time per event: %.3f usec (+- %.3f usec)\n",
		समय_average, समय_stddev);

	mem_average = avg_stats(&mem_stats);
	mem_stddev = stddev_stats(&mem_stats);
	म_लिखो("  Average memory usage: %.0f KB (+- %.0f KB)\n",
		mem_average, mem_stddev);
पूर्ण

अटल पूर्णांक करो_inject_loops(काष्ठा bench_data *data)
अणु

	बेक्रम(समय(शून्य));
	symbol__init(शून्य);

	bench_sample_type  = PERF_SAMPLE_IDENTIFIER | PERF_SAMPLE_IP;
	bench_sample_type |= PERF_SAMPLE_TID | PERF_SAMPLE_TIME;
	bench_id_hdr_size  = 32;

	collect_dso();
	अगर (nr_dsos == 0) अणु
		म_लिखो("  Cannot collect DSOs for injection\n");
		वापस -1;
	पूर्ण

	करो_inject_loop(data, false);
	करो_inject_loop(data, true);

	release_dso();
	वापस 0;
पूर्ण

पूर्णांक bench_inject_build_id(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा bench_data data;

	argc = parse_options(argc, argv, options, bench_usage, 0);
	अगर (argc) अणु
		usage_with_options(bench_usage, options);
		निकास(निकास_त्रुटि);
	पूर्ण

	वापस करो_inject_loops(&data);
पूर्ण

