<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <perf/evsel.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/thपढ़ोmap.h>
#समावेश <linux/list.h>
#समावेश <पूर्णांकernal/evsel.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>
#समावेश <पूर्णांकernal/xyarray.h>
#समावेश <पूर्णांकernal/cpumap.h>
#समावेश <पूर्णांकernal/mmap.h>
#समावेश <पूर्णांकernal/thपढ़ोmap.h>
#समावेश <पूर्णांकernal/lib.h>
#समावेश <linux/माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>

व्योम perf_evsel__init(काष्ठा perf_evsel *evsel, काष्ठा perf_event_attr *attr)
अणु
	INIT_LIST_HEAD(&evsel->node);
	evsel->attr = *attr;
पूर्ण

काष्ठा perf_evsel *perf_evsel__new(काष्ठा perf_event_attr *attr)
अणु
	काष्ठा perf_evsel *evsel = zalloc(माप(*evsel));

	अगर (evsel != शून्य)
		perf_evsel__init(evsel, attr);

	वापस evsel;
पूर्ण

व्योम perf_evsel__delete(काष्ठा perf_evsel *evsel)
अणु
	मुक्त(evsel);
पूर्ण

#घोषणा FD(e, x, y) (*(पूर्णांक *) xyarray__entry(e->fd, x, y))
#घोषणा MMAP(e, x, y) (e->mmap ? ((काष्ठा perf_mmap *) xyarray__entry(e->mmap, x, y)) : शून्य)

पूर्णांक perf_evsel__alloc_fd(काष्ठा perf_evsel *evsel, पूर्णांक ncpus, पूर्णांक nthपढ़ोs)
अणु
	evsel->fd = xyarray__new(ncpus, nthपढ़ोs, माप(पूर्णांक));

	अगर (evsel->fd) अणु
		पूर्णांक cpu, thपढ़ो;
		क्रम (cpu = 0; cpu < ncpus; cpu++) अणु
			क्रम (thपढ़ो = 0; thपढ़ो < nthपढ़ोs; thपढ़ो++) अणु
				FD(evsel, cpu, thपढ़ो) = -1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस evsel->fd != शून्य ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक perf_evsel__alloc_mmap(काष्ठा perf_evsel *evsel, पूर्णांक ncpus, पूर्णांक nthपढ़ोs)
अणु
	evsel->mmap = xyarray__new(ncpus, nthपढ़ोs, माप(काष्ठा perf_mmap));

	वापस evsel->mmap != शून्य ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक
sys_perf_event_खोलो(काष्ठा perf_event_attr *attr,
		    pid_t pid, पूर्णांक cpu, पूर्णांक group_fd,
		    अचिन्हित दीर्घ flags)
अणु
	वापस syscall(__NR_perf_event_खोलो, attr, pid, cpu, group_fd, flags);
पूर्ण

पूर्णांक perf_evsel__खोलो(काष्ठा perf_evsel *evsel, काष्ठा perf_cpu_map *cpus,
		     काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	पूर्णांक cpu, thपढ़ो, err = 0;

	अगर (cpus == शून्य) अणु
		अटल काष्ठा perf_cpu_map *empty_cpu_map;

		अगर (empty_cpu_map == शून्य) अणु
			empty_cpu_map = perf_cpu_map__dummy_new();
			अगर (empty_cpu_map == शून्य)
				वापस -ENOMEM;
		पूर्ण

		cpus = empty_cpu_map;
	पूर्ण

	अगर (thपढ़ोs == शून्य) अणु
		अटल काष्ठा perf_thपढ़ो_map *empty_thपढ़ो_map;

		अगर (empty_thपढ़ो_map == शून्य) अणु
			empty_thपढ़ो_map = perf_thपढ़ो_map__new_dummy();
			अगर (empty_thपढ़ो_map == शून्य)
				वापस -ENOMEM;
		पूर्ण

		thपढ़ोs = empty_thपढ़ो_map;
	पूर्ण

	अगर (evsel->fd == शून्य &&
	    perf_evsel__alloc_fd(evsel, cpus->nr, thपढ़ोs->nr) < 0)
		वापस -ENOMEM;

	क्रम (cpu = 0; cpu < cpus->nr; cpu++) अणु
		क्रम (thपढ़ो = 0; thपढ़ो < thपढ़ोs->nr; thपढ़ो++) अणु
			पूर्णांक fd;

			fd = sys_perf_event_खोलो(&evsel->attr,
						 thपढ़ोs->map[thपढ़ो].pid,
						 cpus->map[cpu], -1, 0);

			अगर (fd < 0)
				वापस -त्रुटि_सं;

			FD(evsel, cpu, thपढ़ो) = fd;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम perf_evsel__बंद_fd_cpu(काष्ठा perf_evsel *evsel, पूर्णांक cpu)
अणु
	पूर्णांक thपढ़ो;

	क्रम (thपढ़ो = 0; thपढ़ो < xyarray__max_y(evsel->fd); ++thपढ़ो) अणु
		अगर (FD(evsel, cpu, thपढ़ो) >= 0)
			बंद(FD(evsel, cpu, thपढ़ो));
		FD(evsel, cpu, thपढ़ो) = -1;
	पूर्ण
पूर्ण

व्योम perf_evsel__बंद_fd(काष्ठा perf_evsel *evsel)
अणु
	पूर्णांक cpu;

	क्रम (cpu = 0; cpu < xyarray__max_x(evsel->fd); cpu++)
		perf_evsel__बंद_fd_cpu(evsel, cpu);
पूर्ण

व्योम perf_evsel__मुक्त_fd(काष्ठा perf_evsel *evsel)
अणु
	xyarray__delete(evsel->fd);
	evsel->fd = शून्य;
पूर्ण

व्योम perf_evsel__बंद(काष्ठा perf_evsel *evsel)
अणु
	अगर (evsel->fd == शून्य)
		वापस;

	perf_evsel__बंद_fd(evsel);
	perf_evsel__मुक्त_fd(evsel);
पूर्ण

व्योम perf_evsel__बंद_cpu(काष्ठा perf_evsel *evsel, पूर्णांक cpu)
अणु
	अगर (evsel->fd == शून्य)
		वापस;

	perf_evsel__बंद_fd_cpu(evsel, cpu);
पूर्ण

व्योम perf_evsel__munmap(काष्ठा perf_evsel *evsel)
अणु
	पूर्णांक cpu, thपढ़ो;

	अगर (evsel->fd == शून्य || evsel->mmap == शून्य)
		वापस;

	क्रम (cpu = 0; cpu < xyarray__max_x(evsel->fd); cpu++) अणु
		क्रम (thपढ़ो = 0; thपढ़ो < xyarray__max_y(evsel->fd); thपढ़ो++) अणु
			पूर्णांक fd = FD(evsel, cpu, thपढ़ो);
			काष्ठा perf_mmap *map = MMAP(evsel, cpu, thपढ़ो);

			अगर (fd < 0)
				जारी;

			perf_mmap__munmap(map);
		पूर्ण
	पूर्ण

	xyarray__delete(evsel->mmap);
	evsel->mmap = शून्य;
पूर्ण

पूर्णांक perf_evsel__mmap(काष्ठा perf_evsel *evsel, पूर्णांक pages)
अणु
	पूर्णांक ret, cpu, thपढ़ो;
	काष्ठा perf_mmap_param mp = अणु
		.prot = PROT_READ | PROT_WRITE,
		.mask = (pages * page_size) - 1,
	पूर्ण;

	अगर (evsel->fd == शून्य || evsel->mmap)
		वापस -EINVAL;

	अगर (perf_evsel__alloc_mmap(evsel, xyarray__max_x(evsel->fd), xyarray__max_y(evsel->fd)) < 0)
		वापस -ENOMEM;

	क्रम (cpu = 0; cpu < xyarray__max_x(evsel->fd); cpu++) अणु
		क्रम (thपढ़ो = 0; thपढ़ो < xyarray__max_y(evsel->fd); thपढ़ो++) अणु
			पूर्णांक fd = FD(evsel, cpu, thपढ़ो);
			काष्ठा perf_mmap *map = MMAP(evsel, cpu, thपढ़ो);

			अगर (fd < 0)
				जारी;

			perf_mmap__init(map, शून्य, false, शून्य);

			ret = perf_mmap__mmap(map, &mp, fd, cpu);
			अगर (ret) अणु
				perf_evsel__munmap(evsel);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम *perf_evsel__mmap_base(काष्ठा perf_evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	अगर (FD(evsel, cpu, thपढ़ो) < 0 || MMAP(evsel, cpu, thपढ़ो) == शून्य)
		वापस शून्य;

	वापस MMAP(evsel, cpu, thपढ़ो)->base;
पूर्ण

पूर्णांक perf_evsel__पढ़ो_size(काष्ठा perf_evsel *evsel)
अणु
	u64 पढ़ो_क्रमmat = evsel->attr.पढ़ो_क्रमmat;
	पूर्णांक entry = माप(u64); /* value */
	पूर्णांक size = 0;
	पूर्णांक nr = 1;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
		size += माप(u64);

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
		size += माप(u64);

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_ID)
		entry += माप(u64);

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
		nr = evsel->nr_members;
		size += माप(u64);
	पूर्ण

	size += entry * nr;
	वापस size;
पूर्ण

पूर्णांक perf_evsel__पढ़ो(काष्ठा perf_evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो,
		     काष्ठा perf_counts_values *count)
अणु
	माप_प्रकार size = perf_evsel__पढ़ो_size(evsel);

	स_रखो(count, 0, माप(*count));

	अगर (FD(evsel, cpu, thपढ़ो) < 0)
		वापस -EINVAL;

	अगर (MMAP(evsel, cpu, thपढ़ो) &&
	    !perf_mmap__पढ़ो_self(MMAP(evsel, cpu, thपढ़ो), count))
		वापस 0;

	अगर (पढ़ोn(FD(evsel, cpu, thपढ़ो), count->values, size) <= 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

अटल पूर्णांक perf_evsel__run_ioctl(काष्ठा perf_evsel *evsel,
				 पूर्णांक ioc,  व्योम *arg,
				 पूर्णांक cpu)
अणु
	पूर्णांक thपढ़ो;

	क्रम (thपढ़ो = 0; thपढ़ो < xyarray__max_y(evsel->fd); thपढ़ो++) अणु
		पूर्णांक fd = FD(evsel, cpu, thपढ़ो),
		    err = ioctl(fd, ioc, arg);

		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_evsel__enable_cpu(काष्ठा perf_evsel *evsel, पूर्णांक cpu)
अणु
	वापस perf_evsel__run_ioctl(evsel, PERF_EVENT_IOC_ENABLE, शून्य, cpu);
पूर्ण

पूर्णांक perf_evsel__enable(काष्ठा perf_evsel *evsel)
अणु
	पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < xyarray__max_x(evsel->fd) && !err; i++)
		err = perf_evsel__run_ioctl(evsel, PERF_EVENT_IOC_ENABLE, शून्य, i);
	वापस err;
पूर्ण

पूर्णांक perf_evsel__disable_cpu(काष्ठा perf_evsel *evsel, पूर्णांक cpu)
अणु
	वापस perf_evsel__run_ioctl(evsel, PERF_EVENT_IOC_DISABLE, शून्य, cpu);
पूर्ण

पूर्णांक perf_evsel__disable(काष्ठा perf_evsel *evsel)
अणु
	पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < xyarray__max_x(evsel->fd) && !err; i++)
		err = perf_evsel__run_ioctl(evsel, PERF_EVENT_IOC_DISABLE, शून्य, i);
	वापस err;
पूर्ण

पूर्णांक perf_evsel__apply_filter(काष्ठा perf_evsel *evsel, स्थिर अक्षर *filter)
अणु
	पूर्णांक err = 0, i;

	क्रम (i = 0; i < evsel->cpus->nr && !err; i++)
		err = perf_evsel__run_ioctl(evsel,
				     PERF_EVENT_IOC_SET_FILTER,
				     (व्योम *)filter, i);
	वापस err;
पूर्ण

काष्ठा perf_cpu_map *perf_evsel__cpus(काष्ठा perf_evsel *evsel)
अणु
	वापस evsel->cpus;
पूर्ण

काष्ठा perf_thपढ़ो_map *perf_evsel__thपढ़ोs(काष्ठा perf_evsel *evsel)
अणु
	वापस evsel->thपढ़ोs;
पूर्ण

काष्ठा perf_event_attr *perf_evsel__attr(काष्ठा perf_evsel *evsel)
अणु
	वापस &evsel->attr;
पूर्ण

पूर्णांक perf_evsel__alloc_id(काष्ठा perf_evsel *evsel, पूर्णांक ncpus, पूर्णांक nthपढ़ोs)
अणु
	अगर (ncpus == 0 || nthपढ़ोs == 0)
		वापस 0;

	अगर (evsel->प्रणाली_wide)
		nthपढ़ोs = 1;

	evsel->sample_id = xyarray__new(ncpus, nthपढ़ोs, माप(काष्ठा perf_sample_id));
	अगर (evsel->sample_id == शून्य)
		वापस -ENOMEM;

	evsel->id = zalloc(ncpus * nthपढ़ोs * माप(u64));
	अगर (evsel->id == शून्य) अणु
		xyarray__delete(evsel->sample_id);
		evsel->sample_id = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम perf_evsel__मुक्त_id(काष्ठा perf_evsel *evsel)
अणु
	xyarray__delete(evsel->sample_id);
	evsel->sample_id = शून्य;
	zमुक्त(&evsel->id);
	evsel->ids = 0;
पूर्ण
