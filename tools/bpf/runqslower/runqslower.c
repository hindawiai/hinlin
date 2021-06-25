<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
// Copyright (c) 2019 Facebook
#समावेश <argp.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/resource.h>
#समावेश <समय.स>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>
#समावेश "runqslower.h"
#समावेश "runqslower.skel.h"

काष्ठा env अणु
	pid_t pid;
	__u64 min_us;
	bool verbose;
पूर्ण env = अणु
	.min_us = 10000,
पूर्ण;

स्थिर अक्षर *argp_program_version = "runqslower 0.1";
स्थिर अक्षर *argp_program_bug_address = "<bpf@vger.kernel.org>";
स्थिर अक्षर argp_program_करोc[] =
"runqslower    Trace long process scheduling delays.\n"
"              For Linux, uses eBPF, BPF CO-RE, libbpf, BTF.\n"
"\n"
"This script traces high scheduling delays between tasks being\n"
"ready to run and them running on CPU after that.\n"
"\n"
"USAGE: runqslower [-p PID] [min_us]\n"
"\n"
"EXAMPLES:\n"
"    runqslower         # trace run queue latency higher than 10000 us (default)\n"
"    runqslower 1000    # trace run queue latency higher than 1000 us\n"
"    runqslower -p 123  # trace pid 123 only\n";

अटल स्थिर काष्ठा argp_option opts[] = अणु
	अणु "pid", 'p', "PID", 0, "Process PID to trace"पूर्ण,
	अणु "verbose", 'v', शून्य, 0, "Verbose debug output" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल error_t parse_arg(पूर्णांक key, अक्षर *arg, काष्ठा argp_state *state)
अणु
	अटल पूर्णांक pos_args;
	पूर्णांक pid;
	दीर्घ दीर्घ min_us;

	चयन (key) अणु
	हाल 'v':
		env.verbose = true;
		अवरोध;
	हाल 'p':
		त्रुटि_सं = 0;
		pid = म_से_दीर्घ(arg, शून्य, 10);
		अगर (त्रुटि_सं || pid <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid PID: %s\n", arg);
			argp_usage(state);
		पूर्ण
		env.pid = pid;
		अवरोध;
	हाल ARGP_KEY_ARG:
		अगर (pos_args++) अणु
			ख_लिखो(मानक_त्रुटि,
				"Unrecognized positional argument: %s\n", arg);
			argp_usage(state);
		पूर्ण
		त्रुटि_सं = 0;
		min_us = म_से_दीर्घl(arg, शून्य, 10);
		अगर (त्रुटि_सं || min_us <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid delay (in us): %s\n", arg);
			argp_usage(state);
		पूर्ण
		env.min_us = min_us;
		अवरोध;
	शेष:
		वापस ARGP_ERR_UNKNOWN;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक libbpf_prपूर्णांक_fn(क्रमागत libbpf_prपूर्णांक_level level,
		    स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अगर (level == LIBBPF_DEBUG && !env.verbose)
		वापस 0;
	वापस भख_लिखो(मानक_त्रुटि, क्रमmat, args);
पूर्ण

अटल पूर्णांक bump_memlock_rlimit(व्योम)
अणु
	काष्ठा rlimit rlim_new = अणु
		.rlim_cur	= RLIM_अनन्त,
		.rlim_max	= RLIM_अनन्त,
	पूर्ण;

	वापस setrlimit(RLIMIT_MEMLOCK, &rlim_new);
पूर्ण

व्योम handle_event(व्योम *ctx, पूर्णांक cpu, व्योम *data, __u32 data_sz)
अणु
	स्थिर काष्ठा event *e = data;
	काष्ठा पंचांग *पंचांग;
	अक्षर ts[32];
	समय_प्रकार t;

	समय(&t);
	पंचांग = स_स्थानीय(&t);
	स_माला(ts, माप(ts), "%H:%M:%S", पंचांग);
	म_लिखो("%-8s %-16s %-6d %14llu\n", ts, e->task, e->pid, e->delta_us);
पूर्ण

व्योम handle_lost_events(व्योम *ctx, पूर्णांक cpu, __u64 lost_cnt)
अणु
	म_लिखो("Lost %llu events on CPU #%d!\n", lost_cnt, cpu);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अटल स्थिर काष्ठा argp argp = अणु
		.options = opts,
		.parser = parse_arg,
		.करोc = argp_program_करोc,
	पूर्ण;
	काष्ठा perf_buffer_opts pb_opts;
	काष्ठा perf_buffer *pb = शून्य;
	काष्ठा runqslower_bpf *obj;
	पूर्णांक err;

	err = argp_parse(&argp, argc, argv, 0, शून्य, शून्य);
	अगर (err)
		वापस err;

	libbpf_set_prपूर्णांक(libbpf_prपूर्णांक_fn);

	err = bump_memlock_rlimit();
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "failed to increase rlimit: %d", err);
		वापस 1;
	पूर्ण

	obj = runqslower_bpf__खोलो();
	अगर (!obj) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open and/or load BPF object\n");
		वापस 1;
	पूर्ण

	/* initialize global data (filtering options) */
	obj->rodata->targ_pid = env.pid;
	obj->rodata->min_us = env.min_us;

	err = runqslower_bpf__load(obj);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "failed to load BPF object: %d\n", err);
		जाओ cleanup;
	पूर्ण

	err = runqslower_bpf__attach(obj);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "failed to attach BPF programs\n");
		जाओ cleanup;
	पूर्ण

	म_लिखो("Tracing run queue latency higher than %llu us\n", env.min_us);
	म_लिखो("%-8s %-16s %-6s %14s\n", "TIME", "COMM", "PID", "LAT(us)");

	pb_opts.sample_cb = handle_event;
	pb_opts.lost_cb = handle_lost_events;
	pb = perf_buffer__new(bpf_map__fd(obj->maps.events), 64, &pb_opts);
	err = libbpf_get_error(pb);
	अगर (err) अणु
		pb = शून्य;
		ख_लिखो(मानक_त्रुटि, "failed to open perf buffer: %d\n", err);
		जाओ cleanup;
	पूर्ण

	जबतक ((err = perf_buffer__poll(pb, 100)) >= 0)
		;
	म_लिखो("Error polling perf buffer: %d\n", err);

cleanup:
	perf_buffer__मुक्त(pb);
	runqslower_bpf__destroy(obj);

	वापस err != 0;
पूर्ण
