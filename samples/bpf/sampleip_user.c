<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sampleip: sample inकाष्ठाion poपूर्णांकer and frequency count in a BPF map.
 *
 * Copyright 2016 Netflix, Inc.
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "perf-sys.h"
#समावेश "trace_helpers.h"

#घोषणा DEFAULT_FREQ	99
#घोषणा DEFAULT_SECS	5
#घोषणा MAX_IPS		8192
#घोषणा PAGE_OFFSET	0xffff880000000000

अटल पूर्णांक map_fd;
अटल पूर्णांक nr_cpus;

अटल व्योम usage(व्योम)
अणु
	म_लिखो("USAGE: sampleip [-F freq] [duration]\n");
	म_लिखो("       -F freq    # sample frequency (Hertz), default 99\n");
	म_लिखो("       duration   # sampling duration (seconds), default 5\n");
पूर्ण

अटल पूर्णांक sampling_start(पूर्णांक freq, काष्ठा bpf_program *prog,
			  काष्ठा bpf_link *links[])
अणु
	पूर्णांक i, pmu_fd;

	काष्ठा perf_event_attr pe_sample_attr = अणु
		.type = PERF_TYPE_SOFTWARE,
		.freq = 1,
		.sample_period = freq,
		.config = PERF_COUNT_SW_CPU_CLOCK,
		.inherit = 1,
	पूर्ण;

	क्रम (i = 0; i < nr_cpus; i++) अणु
		pmu_fd = sys_perf_event_खोलो(&pe_sample_attr, -1 /* pid */, i,
					    -1 /* group_fd */, 0 /* flags */);
		अगर (pmu_fd < 0) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: Initializing perf sampling\n");
			वापस 1;
		पूर्ण
		links[i] = bpf_program__attach_perf_event(prog, pmu_fd);
		अगर (libbpf_get_error(links[i])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: Attach perf event\n");
			links[i] = शून्य;
			बंद(pmu_fd);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sampling_end(काष्ठा bpf_link *links[])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_cpus; i++)
		bpf_link__destroy(links[i]);
पूर्ण

काष्ठा ipcount अणु
	__u64 ip;
	__u32 count;
पूर्ण;

/* used क्रम sorting */
काष्ठा ipcount counts[MAX_IPS];

अटल पूर्णांक count_cmp(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	वापस ((काष्ठा ipcount *)p1)->count - ((काष्ठा ipcount *)p2)->count;
पूर्ण

अटल व्योम prपूर्णांक_ip_map(पूर्णांक fd)
अणु
	काष्ठा ksym *sym;
	__u64 key, next_key;
	__u32 value;
	पूर्णांक i, max;

	म_लिखो("%-19s %-32s %s\n", "ADDR", "KSYM", "COUNT");

	/* fetch IPs and counts */
	key = 0, i = 0;
	जबतक (bpf_map_get_next_key(fd, &key, &next_key) == 0) अणु
		bpf_map_lookup_elem(fd, &next_key, &value);
		counts[i].ip = next_key;
		counts[i++].count = value;
		key = next_key;
	पूर्ण
	max = i;

	/* sort and prपूर्णांक */
	क्विक(counts, max, माप(काष्ठा ipcount), count_cmp);
	क्रम (i = 0; i < max; i++) अणु
		अगर (counts[i].ip > PAGE_OFFSET) अणु
			sym = ksym_search(counts[i].ip);
			अगर (!sym) अणु
				म_लिखो("ksym not found. Is kallsyms loaded?\n");
				जारी;
			पूर्ण

			म_लिखो("0x%-17llx %-32s %u\n", counts[i].ip, sym->name,
			       counts[i].count);
		पूर्ण अन्यथा अणु
			म_लिखो("0x%-17llx %-32s %u\n", counts[i].ip, "(user)",
			       counts[i].count);
		पूर्ण
	पूर्ण

	अगर (max == MAX_IPS) अणु
		म_लिखो("WARNING: IP hash was full (max %d entries); ", max);
		म_लिखो("may have dropped samples\n");
	पूर्ण
पूर्ण

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	म_लिखो("\n");
	prपूर्णांक_ip_map(map_fd);
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt, freq = DEFAULT_FREQ, secs = DEFAULT_SECS, error = 1;
	काष्ठा bpf_object *obj = शून्य;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_link **links;
	अक्षर filename[256];

	/* process arguments */
	जबतक ((opt = getopt(argc, argv, "F:h")) != -1) अणु
		चयन (opt) अणु
		हाल 'F':
			freq = म_से_प(optarg);
			अवरोध;
		हाल 'h':
		शेष:
			usage();
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (argc - optind == 1)
		secs = म_से_प(argv[optind]);
	अगर (freq == 0 || secs == 0) अणु
		usage();
		वापस 1;
	पूर्ण

	/* initialize kernel symbol translation */
	अगर (load_kallsyms()) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading /proc/kallsyms\n");
		वापस 2;
	पूर्ण

	/* create perf FDs क्रम each CPU */
	nr_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	links = सुस्मृति(nr_cpus, माप(काष्ठा bpf_link *));
	अगर (!links) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: malloc of links\n");
		जाओ cleanup;
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		obj = शून्य;
		जाओ cleanup;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "do_sample");
	अगर (!prog) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a prog in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd = bpf_object__find_map_fd_by_name(obj, "ip_map");
	अगर (map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	/* करो sampling */
	म_लिखो("Sampling at %d Hertz for %d seconds. Ctrl-C also ends.\n",
	       freq, secs);
	अगर (sampling_start(freq, prog, links) != 0)
		जाओ cleanup;

	sleep(secs);
	error = 0;

cleanup:
	sampling_end(links);
	/* output sample counts */
	अगर (!error)
		prपूर्णांक_ip_map(map_fd);

	मुक्त(links);
	bpf_object__बंद(obj);
	वापस error;
पूर्ण
