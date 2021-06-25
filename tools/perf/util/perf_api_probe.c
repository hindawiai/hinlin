<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश "perf-sys.h"
#समावेश "util/cloexec.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/parse-events.h"
#समावेश "util/perf_api_probe.h"
#समावेश <perf/cpumap.h>
#समावेश <त्रुटिसं.स>

प्रकार व्योम (*setup_probe_fn_t)(काष्ठा evsel *evsel);

अटल पूर्णांक perf_करो_probe_api(setup_probe_fn_t fn, पूर्णांक cpu, स्थिर अक्षर *str)
अणु
	काष्ठा evlist *evlist;
	काष्ठा evsel *evsel;
	अचिन्हित दीर्घ flags = perf_event_खोलो_cloexec_flag();
	पूर्णांक err = -EAGAIN, fd;
	अटल pid_t pid = -1;

	evlist = evlist__new();
	अगर (!evlist)
		वापस -ENOMEM;

	अगर (parse_events(evlist, str, शून्य))
		जाओ out_delete;

	evsel = evlist__first(evlist);

	जबतक (1) अणु
		fd = sys_perf_event_खोलो(&evsel->core.attr, pid, cpu, -1, flags);
		अगर (fd < 0) अणु
			अगर (pid == -1 && त्रुटि_सं == EACCES) अणु
				pid = 0;
				जारी;
			पूर्ण
			जाओ out_delete;
		पूर्ण
		अवरोध;
	पूर्ण
	बंद(fd);

	fn(evsel);

	fd = sys_perf_event_खोलो(&evsel->core.attr, pid, cpu, -1, flags);
	अगर (fd < 0) अणु
		अगर (त्रुटि_सं == EINVAL)
			err = -EINVAL;
		जाओ out_delete;
	पूर्ण
	बंद(fd);
	err = 0;

out_delete:
	evlist__delete(evlist);
	वापस err;
पूर्ण

अटल bool perf_probe_api(setup_probe_fn_t fn)
अणु
	स्थिर अक्षर *try[] = अणु"cycles:u", "instructions:u", "cpu-clock:u", शून्यपूर्ण;
	काष्ठा perf_cpu_map *cpus;
	पूर्णांक cpu, ret, i = 0;

	cpus = perf_cpu_map__new(शून्य);
	अगर (!cpus)
		वापस false;
	cpu = cpus->map[0];
	perf_cpu_map__put(cpus);

	करो अणु
		ret = perf_करो_probe_api(fn, cpu, try[i++]);
		अगर (!ret)
			वापस true;
	पूर्ण जबतक (ret == -EAGAIN && try[i]);

	वापस false;
पूर्ण

अटल व्योम perf_probe_sample_identअगरier(काष्ठा evsel *evsel)
अणु
	evsel->core.attr.sample_type |= PERF_SAMPLE_IDENTIFIER;
पूर्ण

अटल व्योम perf_probe_comm_exec(काष्ठा evsel *evsel)
अणु
	evsel->core.attr.comm_exec = 1;
पूर्ण

अटल व्योम perf_probe_context_चयन(काष्ठा evsel *evsel)
अणु
	evsel->core.attr.context_चयन = 1;
पूर्ण

अटल व्योम perf_probe_text_poke(काष्ठा evsel *evsel)
अणु
	evsel->core.attr.text_poke = 1;
पूर्ण

अटल व्योम perf_probe_build_id(काष्ठा evsel *evsel)
अणु
	evsel->core.attr.build_id = 1;
पूर्ण

अटल व्योम perf_probe_cgroup(काष्ठा evsel *evsel)
अणु
	evsel->core.attr.cgroup = 1;
पूर्ण

bool perf_can_sample_identअगरier(व्योम)
अणु
	वापस perf_probe_api(perf_probe_sample_identअगरier);
पूर्ण

bool perf_can_comm_exec(व्योम)
अणु
	वापस perf_probe_api(perf_probe_comm_exec);
पूर्ण

bool perf_can_record_चयन_events(व्योम)
अणु
	वापस perf_probe_api(perf_probe_context_चयन);
पूर्ण

bool perf_can_record_text_poke_events(व्योम)
अणु
	वापस perf_probe_api(perf_probe_text_poke);
पूर्ण

bool perf_can_record_cpu_wide(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_CPU_CLOCK,
		.exclude_kernel = 1,
	पूर्ण;
	काष्ठा perf_cpu_map *cpus;
	पूर्णांक cpu, fd;

	cpus = perf_cpu_map__new(शून्य);
	अगर (!cpus)
		वापस false;
	cpu = cpus->map[0];
	perf_cpu_map__put(cpus);

	fd = sys_perf_event_खोलो(&attr, -1, cpu, -1, 0);
	अगर (fd < 0)
		वापस false;
	बंद(fd);

	वापस true;
पूर्ण

/*
 * Architectures are expected to know अगर AUX area sampling is supported by the
 * hardware. Here we check क्रम kernel support.
 */
bool perf_can_aux_sample(व्योम)
अणु
	काष्ठा perf_event_attr attr = अणु
		.size = माप(काष्ठा perf_event_attr),
		.exclude_kernel = 1,
		/*
		 * Non-zero value causes the kernel to calculate the effective
		 * attribute size up to that byte.
		 */
		.aux_sample_size = 1,
	पूर्ण;
	पूर्णांक fd;

	fd = sys_perf_event_खोलो(&attr, -1, 0, -1, 0);
	/*
	 * If the kernel attribute is big enough to contain aux_sample_size
	 * then we assume that it is supported. We are relying on the kernel to
	 * validate the attribute size beक्रमe anything अन्यथा that could be wrong.
	 */
	अगर (fd < 0 && त्रुटि_सं == E2BIG)
		वापस false;
	अगर (fd >= 0)
		बंद(fd);

	वापस true;
पूर्ण

bool perf_can_record_build_id(व्योम)
अणु
	वापस perf_probe_api(perf_probe_build_id);
पूर्ण

bool perf_can_record_cgroup(व्योम)
अणु
	वापस perf_probe_api(perf_probe_cgroup);
पूर्ण
