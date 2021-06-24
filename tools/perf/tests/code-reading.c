<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/param.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/evlist.h>
#समावेश <perf/mmap.h>

#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "env.h"
#समावेश "parse-events.h"
#समावेश "trace-event.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "thread_map.h"
#समावेश "machine.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "event.h"
#समावेश "record.h"
#समावेश "util/mmap.h"
#समावेश "util/string2.h"
#समावेश "util/synthetic-events.h"
#समावेश "thread.h"

#समावेश "tests.h"

#समावेश <linux/प्रकार.स>

#घोषणा BUFSZ	1024
#घोषणा READLEN	128

काष्ठा state अणु
	u64 करोne[1024];
	माप_प्रकार करोne_cnt;
पूर्ण;

अटल माप_प्रकार पढ़ो_objdump_chunk(स्थिर अक्षर **line, अचिन्हित अक्षर **buf,
				 माप_प्रकार *buf_len)
अणु
	माप_प्रकार bytes_पढ़ो = 0;
	अचिन्हित अक्षर *chunk_start = *buf;

	/* Read bytes */
	जबतक (*buf_len > 0) अणु
		अक्षर c1, c2;

		/* Get 2 hex digits */
		c1 = *(*line)++;
		अगर (!है_षष्ठादशक(c1))
			अवरोध;
		c2 = *(*line)++;
		अगर (!है_षष्ठादशक(c2))
			अवरोध;

		/* Store byte and advance buf */
		**buf = (hex(c1) << 4) | hex(c2);
		(*buf)++;
		(*buf_len)--;
		bytes_पढ़ो++;

		/* End of chunk? */
		अगर (है_खाली(**line))
			अवरोध;
	पूर्ण

	/*
	 * objdump will display raw insn as LE अगर code endian
	 * is LE and bytes_per_chunk > 1. In that हाल reverse
	 * the chunk we just पढ़ो.
	 *
	 * see disassemble_bytes() at binutils/objdump.c क्रम details
	 * how objdump chooses display endian)
	 */
	अगर (bytes_पढ़ो > 1 && !bigendian()) अणु
		अचिन्हित अक्षर *chunk_end = chunk_start + bytes_पढ़ो - 1;
		अचिन्हित अक्षर पंचांगp;

		जबतक (chunk_start < chunk_end) अणु
			पंचांगp = *chunk_start;
			*chunk_start = *chunk_end;
			*chunk_end = पंचांगp;
			chunk_start++;
			chunk_end--;
		पूर्ण
	पूर्ण

	वापस bytes_पढ़ो;
पूर्ण

अटल माप_प्रकार पढ़ो_objdump_line(स्थिर अक्षर *line, अचिन्हित अक्षर *buf,
				माप_प्रकार buf_len)
अणु
	स्थिर अक्षर *p;
	माप_प्रकार ret, bytes_पढ़ो = 0;

	/* Skip to a colon */
	p = म_अक्षर(line, ':');
	अगर (!p)
		वापस 0;
	p++;

	/* Skip initial spaces */
	जबतक (*p) अणु
		अगर (!है_खाली(*p))
			अवरोध;
		p++;
	पूर्ण

	करो अणु
		ret = पढ़ो_objdump_chunk(&p, &buf, &buf_len);
		bytes_पढ़ो += ret;
		p++;
	पूर्ण जबतक (ret > 0);

	/* वापस number of successfully पढ़ो bytes */
	वापस bytes_पढ़ो;
पूर्ण

अटल पूर्णांक पढ़ो_objdump_output(खाता *f, व्योम *buf, माप_प्रकार *len, u64 start_addr)
अणु
	अक्षर *line = शून्य;
	माप_प्रकार line_len, off_last = 0;
	sमाप_प्रकार ret;
	पूर्णांक err = 0;
	u64 addr, last_addr = start_addr;

	जबतक (off_last < *len) अणु
		माप_प्रकार off, पढ़ो_bytes, written_bytes;
		अचिन्हित अक्षर पंचांगp[BUFSZ];

		ret = getline(&line, &line_len, f);
		अगर (ख_पूर्ण(f))
			अवरोध;
		अगर (ret < 0) अणु
			pr_debug("getline failed\n");
			err = -1;
			अवरोध;
		पूर्ण

		/* पढ़ो objdump data पूर्णांकo temporary buffer */
		पढ़ो_bytes = पढ़ो_objdump_line(line, पंचांगp, माप(पंचांगp));
		अगर (!पढ़ो_bytes)
			जारी;

		अगर (माला_पूछो(line, "%"PRIx64, &addr) != 1)
			जारी;
		अगर (addr < last_addr) अणु
			pr_debug("addr going backwards, read beyond section?\n");
			अवरोध;
		पूर्ण
		last_addr = addr;

		/* copy it from temporary buffer to 'buf' according
		 * to address on current objdump line */
		off = addr - start_addr;
		अगर (off >= *len)
			अवरोध;
		written_bytes = MIN(पढ़ो_bytes, *len - off);
		स_नकल(buf + off, पंचांगp, written_bytes);
		off_last = off + written_bytes;
	पूर्ण

	/* len वापसs number of bytes that could not be पढ़ो */
	*len -= off_last;

	मुक्त(line);

	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_via_objdump(स्थिर अक्षर *filename, u64 addr, व्योम *buf,
			    माप_प्रकार len)
अणु
	अक्षर cmd[PATH_MAX * 2];
	स्थिर अक्षर *fmt;
	खाता *f;
	पूर्णांक ret;

	fmt = "%s -z -d --start-address=0x%"PRIx64" --stop-address=0x%"PRIx64" %s";
	ret = snम_लिखो(cmd, माप(cmd), fmt, "objdump", addr, addr + len,
		       filename);
	अगर (ret <= 0 || (माप_प्रकार)ret >= माप(cmd))
		वापस -1;

	pr_debug("Objdump command is: %s\n", cmd);

	/* Ignore objdump errors */
	म_जोड़ो(cmd, " 2>/dev/null");

	f = pखोलो(cmd, "r");
	अगर (!f) अणु
		pr_debug("popen failed\n");
		वापस -1;
	पूर्ण

	ret = पढ़ो_objdump_output(f, buf, &len, addr);
	अगर (len) अणु
		pr_debug("objdump read too few bytes: %zd\n", len);
		अगर (!ret)
			ret = len;
	पूर्ण

	pबंद(f);

	वापस ret;
पूर्ण

अटल व्योम dump_buf(अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++) अणु
		pr_debug("0x%02x ", buf[i]);
		अगर (i % 16 == 15)
			pr_debug("\n");
	पूर्ण
	pr_debug("\n");
पूर्ण

अटल पूर्णांक पढ़ो_object_code(u64 addr, माप_प्रकार len, u8 cpumode,
			    काष्ठा thपढ़ो *thपढ़ो, काष्ठा state *state)
अणु
	काष्ठा addr_location al;
	अचिन्हित अक्षर buf1[BUFSZ];
	अचिन्हित अक्षर buf2[BUFSZ];
	माप_प्रकार ret_len;
	u64 objdump_addr;
	स्थिर अक्षर *objdump_name;
	अक्षर decomp_name[KMOD_DECOMP_LEN];
	bool decomp = false;
	पूर्णांक ret;

	pr_debug("Reading object code for memory address: %#"PRIx64"\n", addr);

	अगर (!thपढ़ो__find_map(thपढ़ो, cpumode, addr, &al) || !al.map->dso) अणु
		अगर (cpumode == PERF_RECORD_MISC_HYPERVISOR) अणु
			pr_debug("Hypervisor address can not be resolved - skipping\n");
			वापस 0;
		पूर्ण

		pr_debug("thread__find_map failed\n");
		वापस -1;
	पूर्ण

	pr_debug("File is: %s\n", al.map->dso->दीर्घ_name);

	अगर (al.map->dso->symtab_type == DSO_BINARY_TYPE__KALLSYMS &&
	    !dso__is_kcore(al.map->dso)) अणु
		pr_debug("Unexpected kernel address - skipping\n");
		वापस 0;
	पूर्ण

	pr_debug("On file address is: %#"PRIx64"\n", al.addr);

	अगर (len > BUFSZ)
		len = BUFSZ;

	/* Do not go off the map */
	अगर (addr + len > al.map->end)
		len = al.map->end - addr;

	/* Read the object code using perf */
	ret_len = dso__data_पढ़ो_offset(al.map->dso, thपढ़ो->maps->machine,
					al.addr, buf1, len);
	अगर (ret_len != len) अणु
		pr_debug("dso__data_read_offset failed\n");
		वापस -1;
	पूर्ण

	/*
	 * Converting addresses क्रम use by objdump requires more inक्रमmation.
	 * map__load() करोes that.  See map__rip_2objdump() क्रम details.
	 */
	अगर (map__load(al.map))
		वापस -1;

	/* objdump struggles with kcore - try each map only once */
	अगर (dso__is_kcore(al.map->dso)) अणु
		माप_प्रकार d;

		क्रम (d = 0; d < state->करोne_cnt; d++) अणु
			अगर (state->करोne[d] == al.map->start) अणु
				pr_debug("kcore map tested already");
				pr_debug(" - skipping\n");
				वापस 0;
			पूर्ण
		पूर्ण
		अगर (state->करोne_cnt >= ARRAY_SIZE(state->करोne)) अणु
			pr_debug("Too many kcore maps - skipping\n");
			वापस 0;
		पूर्ण
		state->करोne[state->करोne_cnt++] = al.map->start;
	पूर्ण

	objdump_name = al.map->dso->दीर्घ_name;
	अगर (dso__needs_decompress(al.map->dso)) अणु
		अगर (dso__decompress_kmodule_path(al.map->dso, objdump_name,
						 decomp_name,
						 माप(decomp_name)) < 0) अणु
			pr_debug("decompression failed\n");
			वापस -1;
		पूर्ण

		decomp = true;
		objdump_name = decomp_name;
	पूर्ण

	/* Read the object code using objdump */
	objdump_addr = map__rip_2objdump(al.map, al.addr);
	ret = पढ़ो_via_objdump(objdump_name, objdump_addr, buf2, len);

	अगर (decomp)
		unlink(objdump_name);

	अगर (ret > 0) अणु
		/*
		 * The kernel maps are inaccurate - assume objdump is right in
		 * that हाल.
		 */
		अगर (cpumode == PERF_RECORD_MISC_KERNEL ||
		    cpumode == PERF_RECORD_MISC_GUEST_KERNEL) अणु
			len -= ret;
			अगर (len) अणु
				pr_debug("Reducing len to %zu\n", len);
			पूर्ण अन्यथा अगर (dso__is_kcore(al.map->dso)) अणु
				/*
				 * objdump cannot handle very large segments
				 * that may be found in kcore.
				 */
				pr_debug("objdump failed for kcore");
				pr_debug(" - skipping\n");
				वापस 0;
			पूर्ण अन्यथा अणु
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (ret < 0) अणु
		pr_debug("read_via_objdump failed\n");
		वापस -1;
	पूर्ण

	/* The results should be identical */
	अगर (स_भेद(buf1, buf2, len)) अणु
		pr_debug("Bytes read differ from those read by objdump\n");
		pr_debug("buf1 (dso):\n");
		dump_buf(buf1, len);
		pr_debug("buf2 (objdump):\n");
		dump_buf(buf2, len);
		वापस -1;
	पूर्ण
	pr_debug("Bytes read match those read by objdump\n");

	वापस 0;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा machine *machine,
				काष्ठा evlist *evlist,
				जोड़ perf_event *event, काष्ठा state *state)
अणु
	काष्ठा perf_sample sample;
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक ret;

	अगर (evlist__parse_sample(evlist, event, &sample)) अणु
		pr_debug("evlist__parse_sample failed\n");
		वापस -1;
	पूर्ण

	thपढ़ो = machine__findnew_thपढ़ो(machine, sample.pid, sample.tid);
	अगर (!thपढ़ो) अणु
		pr_debug("machine__findnew_thread failed\n");
		वापस -1;
	पूर्ण

	ret = पढ़ो_object_code(sample.ip, READLEN, sample.cpumode, thपढ़ो, state);
	thपढ़ो__put(thपढ़ो);
	वापस ret;
पूर्ण

अटल पूर्णांक process_event(काष्ठा machine *machine, काष्ठा evlist *evlist,
			 जोड़ perf_event *event, काष्ठा state *state)
अणु
	अगर (event->header.type == PERF_RECORD_SAMPLE)
		वापस process_sample_event(machine, evlist, event, state);

	अगर (event->header.type == PERF_RECORD_THROTTLE ||
	    event->header.type == PERF_RECORD_UNTHROTTLE)
		वापस 0;

	अगर (event->header.type < PERF_RECORD_MAX) अणु
		पूर्णांक ret;

		ret = machine__process_event(machine, event, शून्य);
		अगर (ret < 0)
			pr_debug("machine__process_event failed, event type %u\n",
				 event->header.type);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_events(काष्ठा machine *machine, काष्ठा evlist *evlist,
			  काष्ठा state *state)
अणु
	जोड़ perf_event *event;
	काष्ठा mmap *md;
	पूर्णांक i, ret;

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		md = &evlist->mmap[i];
		अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
			जारी;

		जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
			ret = process_event(machine, evlist, event, state);
			perf_mmap__consume(&md->core);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		perf_mmap__पढ़ो_करोne(&md->core);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक comp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस *(पूर्णांक *)a - *(पूर्णांक *)b;
पूर्ण

अटल व्योम करो_sort_something(व्योम)
अणु
	पूर्णांक buf[40960], i;

	क्रम (i = 0; i < (पूर्णांक)ARRAY_SIZE(buf); i++)
		buf[i] = ARRAY_SIZE(buf) - i - 1;

	क्विक(buf, ARRAY_SIZE(buf), माप(पूर्णांक), comp);

	क्रम (i = 0; i < (पूर्णांक)ARRAY_SIZE(buf); i++) अणु
		अगर (buf[i] != i) अणु
			pr_debug("qsort failed\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sort_something(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++)
		करो_sort_something();
पूर्ण

अटल व्योम syscall_something(व्योम)
अणु
	पूर्णांक pipefd[2];
	पूर्णांक i;

	क्रम (i = 0; i < 1000; i++) अणु
		अगर (pipe(pipefd) < 0) अणु
			pr_debug("pipe failed\n");
			अवरोध;
		पूर्ण
		बंद(pipefd[1]);
		बंद(pipefd[0]);
	पूर्ण
पूर्ण

अटल व्योम fs_something(व्योम)
अणु
	स्थिर अक्षर *test_file_name = "temp-perf-code-reading-test-file--";
	खाता *f;
	पूर्णांक i;

	क्रम (i = 0; i < 1000; i++) अणु
		f = ख_खोलो(test_file_name, "w+");
		अगर (f) अणु
			ख_बंद(f);
			unlink(test_file_name);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित __s390x__
#समावेश "header.h" // क्रम get_cpuid()
#पूर्ण_अगर

अटल स्थिर अक्षर *करो_determine_event(bool excl_kernel)
अणु
	स्थिर अक्षर *event = excl_kernel ? "cycles:u" : "cycles";

#अगर_घोषित __s390x__
	अक्षर cpuid[128], model[16], model_c[16], cpum_cf_v[16];
	अचिन्हित पूर्णांक family;
	पूर्णांक ret, cpum_cf_a;

	अगर (get_cpuid(cpuid, माप(cpuid)))
		जाओ out_घड़ीs;
	ret = माला_पूछो(cpuid, "%*[^,],%u,%[^,],%[^,],%[^,],%x", &family, model_c,
		     model, cpum_cf_v, &cpum_cf_a);
	अगर (ret != 5)		 /* Not available */
		जाओ out_घड़ीs;
	अगर (excl_kernel && (cpum_cf_a & 4))
		वापस event;
	अगर (!excl_kernel && (cpum_cf_a & 2))
		वापस event;

	/* Fall through: missing authorization */
out_घड़ीs:
	event = excl_kernel ? "cpu-clock:u" : "cpu-clock";

#पूर्ण_अगर
	वापस event;
पूर्ण

अटल व्योम करो_something(व्योम)
अणु
	fs_something();

	sort_something();

	syscall_something();
पूर्ण

क्रमागत अणु
	TEST_CODE_READING_OK,
	TEST_CODE_READING_NO_VMLINUX,
	TEST_CODE_READING_NO_KCORE,
	TEST_CODE_READING_NO_ACCESS,
	TEST_CODE_READING_NO_KERNEL_OBJ,
पूर्ण;

अटल पूर्णांक करो_test_code_पढ़ोing(bool try_kcore)
अणु
	काष्ठा machine *machine;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा record_opts opts = अणु
		.mmap_pages	     = अच_पूर्णांक_उच्च,
		.user_freq	     = अच_पूर्णांक_उच्च,
		.user_पूर्णांकerval	     = ULदीर्घ_उच्च,
		.freq		     = 500,
		.target		     = अणु
			.uses_mmap   = true,
		पूर्ण,
	पूर्ण;
	काष्ठा state state = अणु
		.करोne_cnt = 0,
	पूर्ण;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = शून्य;
	काष्ठा perf_cpu_map *cpus = शून्य;
	काष्ठा evlist *evlist = शून्य;
	काष्ठा evsel *evsel = शून्य;
	पूर्णांक err = -1, ret;
	pid_t pid;
	काष्ठा map *map;
	bool have_vmlinux, have_kcore, excl_kernel = false;

	pid = getpid();

	machine = machine__new_host();
	machine->env = &perf_env;

	ret = machine__create_kernel_maps(machine);
	अगर (ret < 0) अणु
		pr_debug("machine__create_kernel_maps failed\n");
		जाओ out_err;
	पूर्ण

	/* Force the use of kallsyms instead of vmlinux to try kcore */
	अगर (try_kcore)
		symbol_conf.kallsyms_name = "/proc/kallsyms";

	/* Load kernel map */
	map = machine__kernel_map(machine);
	ret = map__load(map);
	अगर (ret < 0) अणु
		pr_debug("map__load failed\n");
		जाओ out_err;
	पूर्ण
	have_vmlinux = dso__is_vmlinux(map->dso);
	have_kcore = dso__is_kcore(map->dso);

	/* 2nd समय through we just try kcore */
	अगर (try_kcore && !have_kcore)
		वापस TEST_CODE_READING_NO_KCORE;

	/* No poपूर्णांक getting kernel events अगर there is no kernel object */
	अगर (!have_vmlinux && !have_kcore)
		excl_kernel = true;

	thपढ़ोs = thपढ़ो_map__new_by_tid(pid);
	अगर (!thपढ़ोs) अणु
		pr_debug("thread_map__new_by_tid failed\n");
		जाओ out_err;
	पूर्ण

	ret = perf_event__syntheमाप_प्रकारhपढ़ो_map(शून्य, thपढ़ोs,
						perf_event__process, machine, false);
	अगर (ret < 0) अणु
		pr_debug("perf_event__synthesize_thread_map failed\n");
		जाओ out_err;
	पूर्ण

	thपढ़ो = machine__findnew_thपढ़ो(machine, pid, pid);
	अगर (!thपढ़ो) अणु
		pr_debug("machine__findnew_thread failed\n");
		जाओ out_put;
	पूर्ण

	cpus = perf_cpu_map__new(शून्य);
	अगर (!cpus) अणु
		pr_debug("perf_cpu_map__new failed\n");
		जाओ out_put;
	पूर्ण

	जबतक (1) अणु
		स्थिर अक्षर *str;

		evlist = evlist__new();
		अगर (!evlist) अणु
			pr_debug("evlist__new failed\n");
			जाओ out_put;
		पूर्ण

		perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

		str = करो_determine_event(excl_kernel);
		pr_debug("Parsing event '%s'\n", str);
		ret = parse_events(evlist, str, शून्य);
		अगर (ret < 0) अणु
			pr_debug("parse_events failed\n");
			जाओ out_put;
		पूर्ण

		evlist__config(evlist, &opts, शून्य);

		evsel = evlist__first(evlist);

		evsel->core.attr.comm = 1;
		evsel->core.attr.disabled = 1;
		evsel->core.attr.enable_on_exec = 0;

		ret = evlist__खोलो(evlist);
		अगर (ret < 0) अणु
			अगर (!excl_kernel) अणु
				excl_kernel = true;
				/*
				 * Both cpus and thपढ़ोs are now owned by evlist
				 * and will be मुक्तd by following perf_evlist__set_maps
				 * call. Getting reference to keep them alive.
				 */
				perf_cpu_map__get(cpus);
				perf_thपढ़ो_map__get(thपढ़ोs);
				perf_evlist__set_maps(&evlist->core, शून्य, शून्य);
				evlist__delete(evlist);
				evlist = शून्य;
				जारी;
			पूर्ण

			अगर (verbose > 0) अणु
				अक्षर errbuf[512];
				evlist__म_त्रुटि_खोलो(evlist, त्रुटि_सं, errbuf, माप(errbuf));
				pr_debug("perf_evlist__open() failed!\n%s\n", errbuf);
			पूर्ण

			जाओ out_put;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = evlist__mmap(evlist, अच_पूर्णांक_उच्च);
	अगर (ret < 0) अणु
		pr_debug("evlist__mmap failed\n");
		जाओ out_put;
	पूर्ण

	evlist__enable(evlist);

	करो_something();

	evlist__disable(evlist);

	ret = process_events(machine, evlist, &state);
	अगर (ret < 0)
		जाओ out_put;

	अगर (!have_vmlinux && !have_kcore && !try_kcore)
		err = TEST_CODE_READING_NO_KERNEL_OBJ;
	अन्यथा अगर (!have_vmlinux && !try_kcore)
		err = TEST_CODE_READING_NO_VMLINUX;
	अन्यथा अगर (excl_kernel)
		err = TEST_CODE_READING_NO_ACCESS;
	अन्यथा
		err = TEST_CODE_READING_OK;
out_put:
	thपढ़ो__put(thपढ़ो);
out_err:
	evlist__delete(evlist);
	perf_cpu_map__put(cpus);
	perf_thपढ़ो_map__put(thपढ़ोs);
	machine__delete_thपढ़ोs(machine);
	machine__delete(machine);

	वापस err;
पूर्ण

पूर्णांक test__code_पढ़ोing(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret;

	ret = करो_test_code_पढ़ोing(false);
	अगर (!ret)
		ret = करो_test_code_पढ़ोing(true);

	चयन (ret) अणु
	हाल TEST_CODE_READING_OK:
		वापस 0;
	हाल TEST_CODE_READING_NO_VMLINUX:
		pr_debug("no vmlinux\n");
		वापस 0;
	हाल TEST_CODE_READING_NO_KCORE:
		pr_debug("no kcore\n");
		वापस 0;
	हाल TEST_CODE_READING_NO_ACCESS:
		pr_debug("no access\n");
		वापस 0;
	हाल TEST_CODE_READING_NO_KERNEL_OBJ:
		pr_debug("no kernel obj\n");
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण;
पूर्ण
