<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * builtin-ftrace.c
 *
 * Copyright (c) 2013  LG Electronics,  Namhyung Kim <namhyung@kernel.org>
 * Copyright (c) 2020  Changbin Du <changbin.du@gmail.com>, signअगरicant enhancement.
 */

#समावेश "builtin.h"

#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <linux/capability.h>
#समावेश <linux/माला.स>

#समावेश "debug.h"
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश <api/fs/tracing_path.h>
#समावेश "evlist.h"
#समावेश "target.h"
#समावेश "cpumap.h"
#समावेश "thread_map.h"
#समावेश "strfilter.h"
#समावेश "util/cap.h"
#समावेश "util/config.h"
#समावेश "util/units.h"
#समावेश "util/parse-sublevel-options.h"

#घोषणा DEFAULT_TRACER  "function_graph"

काष्ठा perf_ftrace अणु
	काष्ठा evlist		*evlist;
	काष्ठा target		target;
	स्थिर अक्षर		*tracer;
	काष्ठा list_head	filters;
	काष्ठा list_head	notrace;
	काष्ठा list_head	graph_funcs;
	काष्ठा list_head	nograph_funcs;
	पूर्णांक			graph_depth;
	अचिन्हित दीर्घ		percpu_buffer_size;
	bool			inherit;
	पूर्णांक			func_stack_trace;
	पूर्णांक			func_irq_info;
	पूर्णांक			graph_nosleep_समय;
	पूर्णांक			graph_noirqs;
	पूर्णांक			graph_verbose;
	पूर्णांक			graph_thresh;
	अचिन्हित पूर्णांक		initial_delay;
पूर्ण;

काष्ठा filter_entry अणु
	काष्ठा list_head	list;
	अक्षर			name[];
पूर्ण;

अटल अस्थिर पूर्णांक workload_exec_त्रुटि_सं;
अटल bool करोne;

अटल व्योम sig_handler(पूर्णांक sig __maybe_unused)
अणु
	करोne = true;
पूर्ण

/*
 * evlist__prepare_workload will send a SIGUSR1 अगर the विभाजन fails, since
 * we asked by setting its exec_error to the function below,
 * ftrace__workload_exec_failed_संकेत.
 *
 * XXX We need to handle this more appropriately, emitting an error, etc.
 */
अटल व्योम ftrace__workload_exec_failed_संकेत(पूर्णांक signo __maybe_unused,
						siginfo_t *info __maybe_unused,
						व्योम *ucontext __maybe_unused)
अणु
	workload_exec_त्रुटि_सं = info->si_value.sival_पूर्णांक;
	करोne = true;
पूर्ण

अटल पूर्णांक __ग_लिखो_tracing_file(स्थिर अक्षर *name, स्थिर अक्षर *val, bool append)
अणु
	अक्षर *file;
	पूर्णांक fd, ret = -1;
	sमाप_प्रकार size = म_माप(val);
	पूर्णांक flags = O_WRONLY;
	अक्षर errbuf[512];
	अक्षर *val_copy;

	file = get_tracing_file(name);
	अगर (!file) अणु
		pr_debug("cannot get tracing file: %s\n", name);
		वापस -1;
	पूर्ण

	अगर (append)
		flags |= O_APPEND;
	अन्यथा
		flags |= O_TRUNC;

	fd = खोलो(file, flags);
	अगर (fd < 0) अणु
		pr_debug("cannot open tracing file: %s: %s\n",
			 name, str_error_r(त्रुटि_सं, errbuf, माप(errbuf)));
		जाओ out;
	पूर्ण

	/*
	 * Copy the original value and append a '\n'. Without this,
	 * the kernel can hide possible errors.
	 */
	val_copy = strdup(val);
	अगर (!val_copy)
		जाओ out_बंद;
	val_copy[size] = '\n';

	अगर (ग_लिखो(fd, val_copy, size + 1) == size + 1)
		ret = 0;
	अन्यथा
		pr_debug("write '%s' to tracing/%s failed: %s\n",
			 val, name, str_error_r(त्रुटि_सं, errbuf, माप(errbuf)));

	मुक्त(val_copy);
out_बंद:
	बंद(fd);
out:
	put_tracing_file(file);
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_tracing_file(स्थिर अक्षर *name, स्थिर अक्षर *val)
अणु
	वापस __ग_लिखो_tracing_file(name, val, false);
पूर्ण

अटल पूर्णांक append_tracing_file(स्थिर अक्षर *name, स्थिर अक्षर *val)
अणु
	वापस __ग_लिखो_tracing_file(name, val, true);
पूर्ण

अटल पूर्णांक पढ़ो_tracing_file_to_मानक_निकास(स्थिर अक्षर *name)
अणु
	अक्षर buf[4096];
	अक्षर *file;
	पूर्णांक fd;
	पूर्णांक ret = -1;

	file = get_tracing_file(name);
	अगर (!file) अणु
		pr_debug("cannot get tracing file: %s\n", name);
		वापस -1;
	पूर्ण

	fd = खोलो(file, O_RDONLY);
	अगर (fd < 0) अणु
		pr_debug("cannot open tracing file: %s: %s\n",
			 name, str_error_r(त्रुटि_सं, buf, माप(buf)));
		जाओ out;
	पूर्ण

	/* पढ़ो contents to मानक_निकास */
	जबतक (true) अणु
		पूर्णांक n = पढ़ो(fd, buf, माप(buf));
		अगर (n == 0)
			अवरोध;
		अन्यथा अगर (n < 0)
			जाओ out_बंद;

		अगर (ख_डालो(buf, n, 1, मानक_निकास) != 1)
			जाओ out_बंद;
	पूर्ण
	ret = 0;

out_बंद:
	बंद(fd);
out:
	put_tracing_file(file);
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_tracing_file_by_line(स्थिर अक्षर *name,
				     व्योम (*cb)(अक्षर *str, व्योम *arg),
				     व्योम *cb_arg)
अणु
	अक्षर *line = शून्य;
	माप_प्रकार len = 0;
	अक्षर *file;
	खाता *fp;

	file = get_tracing_file(name);
	अगर (!file) अणु
		pr_debug("cannot get tracing file: %s\n", name);
		वापस -1;
	पूर्ण

	fp = ख_खोलो(file, "r");
	अगर (fp == शून्य) अणु
		pr_debug("cannot open tracing file: %s\n", name);
		put_tracing_file(file);
		वापस -1;
	पूर्ण

	जबतक (getline(&line, &len, fp) != -1) अणु
		cb(line, cb_arg);
	पूर्ण

	अगर (line)
		मुक्त(line);

	ख_बंद(fp);
	put_tracing_file(file);
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_tracing_file_पूर्णांक(स्थिर अक्षर *name, पूर्णांक value)
अणु
	अक्षर buf[16];

	snम_लिखो(buf, माप(buf), "%d", value);
	अगर (ग_लिखो_tracing_file(name, buf) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_tracing_option_file(स्थिर अक्षर *name, स्थिर अक्षर *val)
अणु
	अक्षर *file;
	पूर्णांक ret;

	अगर (aप्र_लिखो(&file, "options/%s", name) < 0)
		वापस -1;

	ret = __ग_लिखो_tracing_file(file, val, false);
	मुक्त(file);
	वापस ret;
पूर्ण

अटल पूर्णांक reset_tracing_cpu(व्योम);
अटल व्योम reset_tracing_filters(व्योम);

अटल व्योम reset_tracing_options(काष्ठा perf_ftrace *ftrace __maybe_unused)
अणु
	ग_लिखो_tracing_option_file("function-fork", "0");
	ग_लिखो_tracing_option_file("func_stack_trace", "0");
	ग_लिखो_tracing_option_file("sleep-time", "1");
	ग_लिखो_tracing_option_file("funcgraph-irqs", "1");
	ग_लिखो_tracing_option_file("funcgraph-proc", "0");
	ग_लिखो_tracing_option_file("funcgraph-abstime", "0");
	ग_लिखो_tracing_option_file("latency-format", "0");
	ग_लिखो_tracing_option_file("irq-info", "0");
पूर्ण

अटल पूर्णांक reset_tracing_files(काष्ठा perf_ftrace *ftrace __maybe_unused)
अणु
	अगर (ग_लिखो_tracing_file("tracing_on", "0") < 0)
		वापस -1;

	अगर (ग_लिखो_tracing_file("current_tracer", "nop") < 0)
		वापस -1;

	अगर (ग_लिखो_tracing_file("set_ftrace_pid", " ") < 0)
		वापस -1;

	अगर (reset_tracing_cpu() < 0)
		वापस -1;

	अगर (ग_लिखो_tracing_file("max_graph_depth", "0") < 0)
		वापस -1;

	अगर (ग_लिखो_tracing_file("tracing_thresh", "0") < 0)
		वापस -1;

	reset_tracing_filters();
	reset_tracing_options(ftrace);
	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_pid(काष्ठा perf_ftrace *ftrace)
अणु
	पूर्णांक i;
	अक्षर buf[16];

	अगर (target__has_cpu(&ftrace->target))
		वापस 0;

	क्रम (i = 0; i < perf_thपढ़ो_map__nr(ftrace->evlist->core.thपढ़ोs); i++) अणु
		scnम_लिखो(buf, माप(buf), "%d",
			  perf_thपढ़ो_map__pid(ftrace->evlist->core.thपढ़ोs, i));
		अगर (append_tracing_file("set_ftrace_pid", buf) < 0)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_cpumask(काष्ठा perf_cpu_map *cpumap)
अणु
	अक्षर *cpumask;
	माप_प्रकार mask_size;
	पूर्णांक ret;
	पूर्णांक last_cpu;

	last_cpu = cpu_map__cpu(cpumap, cpumap->nr - 1);
	mask_size = last_cpu / 4 + 2; /* one more byte क्रम EOS */
	mask_size += last_cpu / 32; /* ',' is needed क्रम every 32th cpus */

	cpumask = दो_स्मृति(mask_size);
	अगर (cpumask == शून्य) अणु
		pr_debug("failed to allocate cpu mask\n");
		वापस -1;
	पूर्ण

	cpu_map__snprपूर्णांक_mask(cpumap, cpumask, mask_size);

	ret = ग_लिखो_tracing_file("tracing_cpumask", cpumask);

	मुक्त(cpumask);
	वापस ret;
पूर्ण

अटल पूर्णांक set_tracing_cpu(काष्ठा perf_ftrace *ftrace)
अणु
	काष्ठा perf_cpu_map *cpumap = ftrace->evlist->core.cpus;

	अगर (!target__has_cpu(&ftrace->target))
		वापस 0;

	वापस set_tracing_cpumask(cpumap);
पूर्ण

अटल पूर्णांक set_tracing_func_stack_trace(काष्ठा perf_ftrace *ftrace)
अणु
	अगर (!ftrace->func_stack_trace)
		वापस 0;

	अगर (ग_लिखो_tracing_option_file("func_stack_trace", "1") < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_func_irqinfo(काष्ठा perf_ftrace *ftrace)
अणु
	अगर (!ftrace->func_irq_info)
		वापस 0;

	अगर (ग_लिखो_tracing_option_file("irq-info", "1") < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक reset_tracing_cpu(व्योम)
अणु
	काष्ठा perf_cpu_map *cpumap = perf_cpu_map__new(शून्य);
	पूर्णांक ret;

	ret = set_tracing_cpumask(cpumap);
	perf_cpu_map__put(cpumap);
	वापस ret;
पूर्ण

अटल पूर्णांक __set_tracing_filter(स्थिर अक्षर *filter_file, काष्ठा list_head *funcs)
अणु
	काष्ठा filter_entry *pos;

	list_क्रम_each_entry(pos, funcs, list) अणु
		अगर (append_tracing_file(filter_file, pos->name) < 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_filters(काष्ठा perf_ftrace *ftrace)
अणु
	पूर्णांक ret;

	ret = __set_tracing_filter("set_ftrace_filter", &ftrace->filters);
	अगर (ret < 0)
		वापस ret;

	ret = __set_tracing_filter("set_ftrace_notrace", &ftrace->notrace);
	अगर (ret < 0)
		वापस ret;

	ret = __set_tracing_filter("set_graph_function", &ftrace->graph_funcs);
	अगर (ret < 0)
		वापस ret;

	/* old kernels करो not have this filter */
	__set_tracing_filter("set_graph_notrace", &ftrace->nograph_funcs);

	वापस ret;
पूर्ण

अटल व्योम reset_tracing_filters(व्योम)
अणु
	ग_लिखो_tracing_file("set_ftrace_filter", " ");
	ग_लिखो_tracing_file("set_ftrace_notrace", " ");
	ग_लिखो_tracing_file("set_graph_function", " ");
	ग_लिखो_tracing_file("set_graph_notrace", " ");
पूर्ण

अटल पूर्णांक set_tracing_depth(काष्ठा perf_ftrace *ftrace)
अणु
	अगर (ftrace->graph_depth == 0)
		वापस 0;

	अगर (ftrace->graph_depth < 0) अणु
		pr_err("invalid graph depth: %d\n", ftrace->graph_depth);
		वापस -1;
	पूर्ण

	अगर (ग_लिखो_tracing_file_पूर्णांक("max_graph_depth", ftrace->graph_depth) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_percpu_buffer_size(काष्ठा perf_ftrace *ftrace)
अणु
	पूर्णांक ret;

	अगर (ftrace->percpu_buffer_size == 0)
		वापस 0;

	ret = ग_लिखो_tracing_file_पूर्णांक("buffer_size_kb",
				     ftrace->percpu_buffer_size / 1024);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_trace_inherit(काष्ठा perf_ftrace *ftrace)
अणु
	अगर (!ftrace->inherit)
		वापस 0;

	अगर (ग_लिखो_tracing_option_file("function-fork", "1") < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_sleep_समय(काष्ठा perf_ftrace *ftrace)
अणु
	अगर (!ftrace->graph_nosleep_समय)
		वापस 0;

	अगर (ग_लिखो_tracing_option_file("sleep-time", "0") < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_funcgraph_irqs(काष्ठा perf_ftrace *ftrace)
अणु
	अगर (!ftrace->graph_noirqs)
		वापस 0;

	अगर (ग_लिखो_tracing_option_file("funcgraph-irqs", "0") < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_funcgraph_verbose(काष्ठा perf_ftrace *ftrace)
अणु
	अगर (!ftrace->graph_verbose)
		वापस 0;

	अगर (ग_लिखो_tracing_option_file("funcgraph-proc", "1") < 0)
		वापस -1;

	अगर (ग_लिखो_tracing_option_file("funcgraph-abstime", "1") < 0)
		वापस -1;

	अगर (ग_लिखो_tracing_option_file("latency-format", "1") < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_thresh(काष्ठा perf_ftrace *ftrace)
अणु
	पूर्णांक ret;

	अगर (ftrace->graph_thresh == 0)
		वापस 0;

	ret = ग_लिखो_tracing_file_पूर्णांक("tracing_thresh", ftrace->graph_thresh);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक set_tracing_options(काष्ठा perf_ftrace *ftrace)
अणु
	अगर (set_tracing_pid(ftrace) < 0) अणु
		pr_err("failed to set ftrace pid\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_cpu(ftrace) < 0) अणु
		pr_err("failed to set tracing cpumask\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_func_stack_trace(ftrace) < 0) अणु
		pr_err("failed to set tracing option func_stack_trace\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_func_irqinfo(ftrace) < 0) अणु
		pr_err("failed to set tracing option irq-info\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_filters(ftrace) < 0) अणु
		pr_err("failed to set tracing filters\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_depth(ftrace) < 0) अणु
		pr_err("failed to set graph depth\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_percpu_buffer_size(ftrace) < 0) अणु
		pr_err("failed to set tracing per-cpu buffer size\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_trace_inherit(ftrace) < 0) अणु
		pr_err("failed to set tracing option function-fork\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_sleep_समय(ftrace) < 0) अणु
		pr_err("failed to set tracing option sleep-time\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_funcgraph_irqs(ftrace) < 0) अणु
		pr_err("failed to set tracing option funcgraph-irqs\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_funcgraph_verbose(ftrace) < 0) अणु
		pr_err("failed to set tracing option funcgraph-proc/funcgraph-abstime\n");
		वापस -1;
	पूर्ण

	अगर (set_tracing_thresh(ftrace) < 0) अणु
		pr_err("failed to set tracing thresh\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __cmd_ftrace(काष्ठा perf_ftrace *ftrace, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अक्षर *trace_file;
	पूर्णांक trace_fd;
	अक्षर buf[4096];
	काष्ठा pollfd pollfd = अणु
		.events = POLLIN,
	पूर्ण;

	अगर (!(perf_cap__capable(CAP_PERFMON) ||
	      perf_cap__capable(CAP_SYS_ADMIN))) अणु
		pr_err("ftrace only works for %s!\n",
#अगर_घोषित HAVE_LIBCAP_SUPPORT
		"users with the CAP_PERFMON or CAP_SYS_ADMIN capability"
#अन्यथा
		"root"
#पूर्ण_अगर
		);
		वापस -1;
	पूर्ण

	संकेत(संक_विघ्न, sig_handler);
	संकेत(SIGUSR1, sig_handler);
	संकेत(SIGCHLD, sig_handler);
	संकेत(SIGPIPE, sig_handler);

	अगर (reset_tracing_files(ftrace) < 0) अणु
		pr_err("failed to reset ftrace\n");
		जाओ out;
	पूर्ण

	/* reset ftrace buffer */
	अगर (ग_लिखो_tracing_file("trace", "0") < 0)
		जाओ out;

	अगर (argc && evlist__prepare_workload(ftrace->evlist, &ftrace->target, argv, false,
					     ftrace__workload_exec_failed_संकेत) < 0) अणु
		जाओ out;
	पूर्ण

	अगर (set_tracing_options(ftrace) < 0)
		जाओ out_reset;

	अगर (ग_लिखो_tracing_file("current_tracer", ftrace->tracer) < 0) अणु
		pr_err("failed to set current_tracer to %s\n", ftrace->tracer);
		जाओ out_reset;
	पूर्ण

	setup_pager();

	trace_file = get_tracing_file("trace_pipe");
	अगर (!trace_file) अणु
		pr_err("failed to open trace_pipe\n");
		जाओ out_reset;
	पूर्ण

	trace_fd = खोलो(trace_file, O_RDONLY);

	put_tracing_file(trace_file);

	अगर (trace_fd < 0) अणु
		pr_err("failed to open trace_pipe\n");
		जाओ out_reset;
	पूर्ण

	fcntl(trace_fd, F_SETFL, O_NONBLOCK);
	pollfd.fd = trace_fd;

	/* display column headers */
	पढ़ो_tracing_file_to_मानक_निकास("trace");

	अगर (!ftrace->initial_delay) अणु
		अगर (ग_लिखो_tracing_file("tracing_on", "1") < 0) अणु
			pr_err("can't enable tracing\n");
			जाओ out_बंद_fd;
		पूर्ण
	पूर्ण

	evlist__start_workload(ftrace->evlist);

	अगर (ftrace->initial_delay) अणु
		usleep(ftrace->initial_delay * 1000);
		अगर (ग_लिखो_tracing_file("tracing_on", "1") < 0) अणु
			pr_err("can't enable tracing\n");
			जाओ out_बंद_fd;
		पूर्ण
	पूर्ण

	जबतक (!करोne) अणु
		अगर (poll(&pollfd, 1, -1) < 0)
			अवरोध;

		अगर (pollfd.revents & POLLIN) अणु
			पूर्णांक n = पढ़ो(trace_fd, buf, माप(buf));
			अगर (n < 0)
				अवरोध;
			अगर (ख_डालो(buf, n, 1, मानक_निकास) != 1)
				अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखो_tracing_file("tracing_on", "0");

	अगर (workload_exec_त्रुटि_सं) अणु
		स्थिर अक्षर *emsg = str_error_r(workload_exec_त्रुटि_सं, buf, माप(buf));
		/* flush मानक_निकास first so below error msg appears at the end. */
		ख_साफ(मानक_निकास);
		pr_err("workload failed: %s\n", emsg);
		जाओ out_बंद_fd;
	पूर्ण

	/* पढ़ो reमुख्यing buffer contents */
	जबतक (true) अणु
		पूर्णांक n = पढ़ो(trace_fd, buf, माप(buf));
		अगर (n <= 0)
			अवरोध;
		अगर (ख_डालो(buf, n, 1, मानक_निकास) != 1)
			अवरोध;
	पूर्ण

out_बंद_fd:
	बंद(trace_fd);
out_reset:
	reset_tracing_files(ftrace);
out:
	वापस (करोne && !workload_exec_त्रुटि_सं) ? 0 : -1;
पूर्ण

अटल पूर्णांक perf_ftrace_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb)
अणु
	काष्ठा perf_ftrace *ftrace = cb;

	अगर (!strstarts(var, "ftrace."))
		वापस 0;

	अगर (म_भेद(var, "ftrace.tracer"))
		वापस -1;

	अगर (!म_भेद(value, "function_graph") ||
	    !म_भेद(value, "function")) अणु
		ftrace->tracer = value;
		वापस 0;
	पूर्ण

	pr_err("Please select \"function_graph\" (default) or \"function\"\n");
	वापस -1;
पूर्ण

अटल व्योम list_function_cb(अक्षर *str, व्योम *arg)
अणु
	काष्ठा strfilter *filter = (काष्ठा strfilter *)arg;

	अगर (strfilter__compare(filter, str))
		म_लिखो("%s", str);
पूर्ण

अटल पूर्णांक opt_list_avail_functions(स्थिर काष्ठा option *opt __maybe_unused,
				    स्थिर अक्षर *str, पूर्णांक unset)
अणु
	काष्ठा strfilter *filter;
	स्थिर अक्षर *err = शून्य;
	पूर्णांक ret;

	अगर (unset || !str)
		वापस -1;

	filter = strfilter__new(str, &err);
	अगर (!filter)
		वापस err ? -EINVAL : -ENOMEM;

	ret = strfilter__or(filter, str, &err);
	अगर (ret == -EINVAL) अणु
		pr_err("Filter parse error at %td.\n", err - str + 1);
		pr_err("Source: \"%s\"\n", str);
		pr_err("         %*c\n", (पूर्णांक)(err - str + 1), '^');
		strfilter__delete(filter);
		वापस ret;
	पूर्ण

	ret = पढ़ो_tracing_file_by_line("available_filter_functions",
					list_function_cb, filter);
	strfilter__delete(filter);
	अगर (ret < 0)
		वापस ret;

	निकास(0);
पूर्ण

अटल पूर्णांक parse_filter_func(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			     पूर्णांक unset __maybe_unused)
अणु
	काष्ठा list_head *head = opt->value;
	काष्ठा filter_entry *entry;

	entry = दो_स्मृति(माप(*entry) + म_माप(str) + 1);
	अगर (entry == शून्य)
		वापस -ENOMEM;

	म_नकल(entry->name, str);
	list_add_tail(&entry->list, head);

	वापस 0;
पूर्ण

अटल व्योम delete_filter_func(काष्ठा list_head *head)
अणु
	काष्ठा filter_entry *pos, *पंचांगp;

	list_क्रम_each_entry_safe(pos, पंचांगp, head, list) अणु
		list_del_init(&pos->list);
		मुक्त(pos);
	पूर्ण
पूर्ण

अटल पूर्णांक parse_buffer_size(स्थिर काष्ठा option *opt,
			     स्थिर अक्षर *str, पूर्णांक unset)
अणु
	अचिन्हित दीर्घ *s = (अचिन्हित दीर्घ *)opt->value;
	अटल काष्ठा parse_tag tags_size[] = अणु
		अणु .tag  = 'B', .mult = 1       पूर्ण,
		अणु .tag  = 'K', .mult = 1 << 10 पूर्ण,
		अणु .tag  = 'M', .mult = 1 << 20 पूर्ण,
		अणु .tag  = 'G', .mult = 1 << 30 पूर्ण,
		अणु .tag  = 0 पूर्ण,
	पूर्ण;
	अचिन्हित दीर्घ val;

	अगर (unset) अणु
		*s = 0;
		वापस 0;
	पूर्ण

	val = parse_tag_value(str, tags_size);
	अगर (val != (अचिन्हित दीर्घ) -1) अणु
		अगर (val < 1024) अणु
			pr_err("buffer size too small, must larger than 1KB.");
			वापस -1;
		पूर्ण
		*s = val;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक parse_func_tracer_opts(स्थिर काष्ठा option *opt,
				  स्थिर अक्षर *str, पूर्णांक unset)
अणु
	पूर्णांक ret;
	काष्ठा perf_ftrace *ftrace = (काष्ठा perf_ftrace *) opt->value;
	काष्ठा sublevel_option func_tracer_opts[] = अणु
		अणु .name = "call-graph",	.value_ptr = &ftrace->func_stack_trace पूर्ण,
		अणु .name = "irq-info",	.value_ptr = &ftrace->func_irq_info पूर्ण,
		अणु .name = शून्य, पूर्ण
	पूर्ण;

	अगर (unset)
		वापस 0;

	ret = perf_parse_sublevel_options(str, func_tracer_opts);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_graph_tracer_opts(स्थिर काष्ठा option *opt,
				  स्थिर अक्षर *str, पूर्णांक unset)
अणु
	पूर्णांक ret;
	काष्ठा perf_ftrace *ftrace = (काष्ठा perf_ftrace *) opt->value;
	काष्ठा sublevel_option graph_tracer_opts[] = अणु
		अणु .name = "nosleep-time",	.value_ptr = &ftrace->graph_nosleep_समय पूर्ण,
		अणु .name = "noirqs",		.value_ptr = &ftrace->graph_noirqs पूर्ण,
		अणु .name = "verbose",		.value_ptr = &ftrace->graph_verbose पूर्ण,
		अणु .name = "thresh",		.value_ptr = &ftrace->graph_thresh पूर्ण,
		अणु .name = "depth",		.value_ptr = &ftrace->graph_depth पूर्ण,
		अणु .name = शून्य, पूर्ण
	पूर्ण;

	अगर (unset)
		वापस 0;

	ret = perf_parse_sublevel_options(str, graph_tracer_opts);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम select_tracer(काष्ठा perf_ftrace *ftrace)
अणु
	bool graph = !list_empty(&ftrace->graph_funcs) ||
		     !list_empty(&ftrace->nograph_funcs);
	bool func = !list_empty(&ftrace->filters) ||
		    !list_empty(&ftrace->notrace);

	/* The function_graph has priority over function tracer. */
	अगर (graph)
		ftrace->tracer = "function_graph";
	अन्यथा अगर (func)
		ftrace->tracer = "function";
	/* Otherwise, the शेष tracer is used. */

	pr_debug("%s tracer is used\n", ftrace->tracer);
पूर्ण

पूर्णांक cmd_ftrace(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक ret;
	काष्ठा perf_ftrace ftrace = अणु
		.tracer = DEFAULT_TRACER,
		.target = अणु .uid = अच_पूर्णांक_उच्च, पूर्ण,
	पूर्ण;
	स्थिर अक्षर * स्थिर ftrace_usage[] = अणु
		"perf ftrace [<options>] [<command>]",
		"perf ftrace [<options>] -- <command> [<options>]",
		शून्य
	पूर्ण;
	स्थिर काष्ठा option ftrace_options[] = अणु
	OPT_STRING('t', "tracer", &ftrace.tracer, "tracer",
		   "Tracer to use: function_graph(default) or function"),
	OPT_CALLBACK_DEFAULT('F', "funcs", शून्य, "[FILTER]",
			     "Show available functions to filter",
			     opt_list_avail_functions, "*"),
	OPT_STRING('p', "pid", &ftrace.target.pid, "pid",
		   "Trace on existing process id"),
	/* TODO: Add लघु option -t after -t/--tracer can be हटाओd. */
	OPT_STRING(0, "tid", &ftrace.target.tid, "tid",
		   "Trace on existing thread id (exclusive to --pid)"),
	OPT_INCR('v', "verbose", &verbose,
		 "Be more verbose"),
	OPT_BOOLEAN('a', "all-cpus", &ftrace.target.प्रणाली_wide,
		    "System-wide collection from all CPUs"),
	OPT_STRING('C', "cpu", &ftrace.target.cpu_list, "cpu",
		    "List of cpus to monitor"),
	OPT_CALLBACK('T', "trace-funcs", &ftrace.filters, "func",
		     "Trace given functions using function tracer",
		     parse_filter_func),
	OPT_CALLBACK('N', "notrace-funcs", &ftrace.notrace, "func",
		     "Do not trace given functions", parse_filter_func),
	OPT_CALLBACK(0, "func-opts", &ftrace, "options",
		     "Function tracer options, available options: call-graph,irq-info",
		     parse_func_tracer_opts),
	OPT_CALLBACK('G', "graph-funcs", &ftrace.graph_funcs, "func",
		     "Trace given functions using function_graph tracer",
		     parse_filter_func),
	OPT_CALLBACK('g', "nograph-funcs", &ftrace.nograph_funcs, "func",
		     "Set nograph filter on given functions", parse_filter_func),
	OPT_CALLBACK(0, "graph-opts", &ftrace, "options",
		     "Graph tracer options, available options: nosleep-time,noirqs,verbose,thresh=<n>,depth=<n>",
		     parse_graph_tracer_opts),
	OPT_CALLBACK('m', "buffer-size", &ftrace.percpu_buffer_size, "size",
		     "Size of per cpu buffer, needs to use a B, K, M or G suffix.", parse_buffer_size),
	OPT_BOOLEAN(0, "inherit", &ftrace.inherit,
		    "Trace children processes"),
	OPT_UINTEGER('D', "delay", &ftrace.initial_delay,
		     "Number of milliseconds to wait before starting tracing after program start"),
	OPT_END()
	पूर्ण;

	INIT_LIST_HEAD(&ftrace.filters);
	INIT_LIST_HEAD(&ftrace.notrace);
	INIT_LIST_HEAD(&ftrace.graph_funcs);
	INIT_LIST_HEAD(&ftrace.nograph_funcs);

	ret = perf_config(perf_ftrace_config, &ftrace);
	अगर (ret < 0)
		वापस -1;

	argc = parse_options(argc, argv, ftrace_options, ftrace_usage,
			    PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (!argc && target__none(&ftrace.target))
		ftrace.target.प्रणाली_wide = true;

	select_tracer(&ftrace);

	ret = target__validate(&ftrace.target);
	अगर (ret) अणु
		अक्षर errbuf[512];

		target__म_त्रुटि(&ftrace.target, ret, errbuf, 512);
		pr_err("%s\n", errbuf);
		जाओ out_delete_filters;
	पूर्ण

	ftrace.evlist = evlist__new();
	अगर (ftrace.evlist == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_delete_filters;
	पूर्ण

	ret = evlist__create_maps(ftrace.evlist, &ftrace.target);
	अगर (ret < 0)
		जाओ out_delete_evlist;

	ret = __cmd_ftrace(&ftrace, argc, argv);

out_delete_evlist:
	evlist__delete(ftrace.evlist);

out_delete_filters:
	delete_filter_func(&ftrace.filters);
	delete_filter_func(&ftrace.notrace);
	delete_filter_func(&ftrace.graph_funcs);
	delete_filter_func(&ftrace.nograph_funcs);

	वापस ret;
पूर्ण
