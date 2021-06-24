<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013-2015, Michael Ellerman, IBM Corp.
 */

#घोषणा _GNU_SOURCE	/* For CPU_ZERO etc. */

#समावेश <elf.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <link.h>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/sysinfo.h>
#समावेश <sys/types.h>
#समावेश <sys/utsname.h>
#समावेश <unistd.h>
#समावेश <यंत्र/unistd.h>
#समावेश <linux/सीमा.स>

#समावेश "utils.h"

अटल अक्षर auxv[4096];

पूर्णांक पढ़ो_auxv(अक्षर *buf, sमाप_प्रकार buf_size)
अणु
	sमाप_प्रकार num;
	पूर्णांक rc, fd;

	fd = खोलो("/proc/self/auxv", O_RDONLY);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("open");
		वापस -त्रुटि_सं;
	पूर्ण

	num = पढ़ो(fd, buf, buf_size);
	अगर (num < 0) अणु
		लिखो_त्रुटि("read");
		rc = -EIO;
		जाओ out;
	पूर्ण

	अगर (num > buf_size) अणु
		म_लिखो("overflowed auxv buffer\n");
		rc = -EOVERFLOW;
		जाओ out;
	पूर्ण

	rc = 0;
out:
	बंद(fd);
	वापस rc;
पूर्ण

व्योम *find_auxv_entry(पूर्णांक type, अक्षर *auxv)
अणु
	ElfW(auxv_t) *p;

	p = (ElfW(auxv_t) *)auxv;

	जबतक (p->a_type != AT_शून्य) अणु
		अगर (p->a_type == type)
			वापस p;

		p++;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम *get_auxv_entry(पूर्णांक type)
अणु
	ElfW(auxv_t) *p;

	अगर (पढ़ो_auxv(auxv, माप(auxv)))
		वापस शून्य;

	p = find_auxv_entry(type, auxv);
	अगर (p)
		वापस (व्योम *)p->a_un.a_val;

	वापस शून्य;
पूर्ण

पूर्णांक pick_online_cpu(व्योम)
अणु
	पूर्णांक ncpus, cpu = -1;
	cpu_set_t *mask;
	माप_प्रकार size;

	ncpus = get_nprocs_conf();
	size = CPU_ALLOC_SIZE(ncpus);
	mask = CPU_ALLOC(ncpus);
	अगर (!mask) अणु
		लिखो_त्रुटि("malloc");
		वापस -1;
	पूर्ण

	CPU_ZERO_S(size, mask);

	अगर (sched_getaffinity(0, size, mask)) अणु
		लिखो_त्रुटि("sched_getaffinity");
		जाओ करोne;
	पूर्ण

	/* We prefer a primary thपढ़ो, but skip 0 */
	क्रम (cpu = 8; cpu < ncpus; cpu += 8)
		अगर (CPU_ISSET_S(cpu, size, mask))
			जाओ करोne;

	/* Search क्रम anything, but in reverse */
	क्रम (cpu = ncpus - 1; cpu >= 0; cpu--)
		अगर (CPU_ISSET_S(cpu, size, mask))
			जाओ करोne;

	म_लिखो("No cpus in affinity mask?!\n");

करोne:
	CPU_FREE(mask);
	वापस cpu;
पूर्ण

bool is_ppc64le(व्योम)
अणु
	काष्ठा utsname uts;
	पूर्णांक rc;

	त्रुटि_सं = 0;
	rc = uname(&uts);
	अगर (rc) अणु
		लिखो_त्रुटि("uname");
		वापस false;
	पूर्ण

	वापस म_भेद(uts.machine, "ppc64le") == 0;
पूर्ण

पूर्णांक पढ़ो_sysfs_file(अक्षर *fpath, अक्षर *result, माप_प्रकार result_size)
अणु
	अक्षर path[PATH_MAX] = "/sys/";
	पूर्णांक rc = -1, fd;

	म_जोड़न(path, fpath, PATH_MAX - म_माप(path) - 1);

	अगर ((fd = खोलो(path, O_RDONLY)) < 0)
		वापस rc;

	rc = पढ़ो(fd, result, result_size);

	बंद(fd);

	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

पूर्णांक पढ़ो_debugfs_file(अक्षर *debugfs_file, पूर्णांक *result)
अणु
	पूर्णांक rc = -1, fd;
	अक्षर path[PATH_MAX];
	अक्षर value[16];

	म_नकल(path, "/sys/kernel/debug/");
	म_जोड़न(path, debugfs_file, PATH_MAX - म_माप(path) - 1);

	अगर ((fd = खोलो(path, O_RDONLY)) < 0)
		वापस rc;

	अगर ((rc = पढ़ो(fd, value, माप(value))) < 0)
		वापस rc;

	value[15] = 0;
	*result = म_से_प(value);
	बंद(fd);

	वापस 0;
पूर्ण

पूर्णांक ग_लिखो_debugfs_file(अक्षर *debugfs_file, पूर्णांक result)
अणु
	पूर्णांक rc = -1, fd;
	अक्षर path[PATH_MAX];
	अक्षर value[16];

	म_नकल(path, "/sys/kernel/debug/");
	म_जोड़न(path, debugfs_file, PATH_MAX - म_माप(path) - 1);

	अगर ((fd = खोलो(path, O_WRONLY)) < 0)
		वापस rc;

	snम_लिखो(value, 16, "%d", result);

	अगर ((rc = ग_लिखो(fd, value, म_माप(value))) < 0)
		वापस rc;

	बंद(fd);

	वापस 0;
पूर्ण

अटल दीर्घ perf_event_खोलो(काष्ठा perf_event_attr *hw_event, pid_t pid,
		पूर्णांक cpu, पूर्णांक group_fd, अचिन्हित दीर्घ flags)
अणु
	वापस syscall(__NR_perf_event_खोलो, hw_event, pid, cpu,
		      group_fd, flags);
पूर्ण

अटल व्योम perf_event_attr_init(काष्ठा perf_event_attr *event_attr,
					अचिन्हित पूर्णांक type,
					अचिन्हित दीर्घ config)
अणु
	स_रखो(event_attr, 0, माप(*event_attr));

	event_attr->type = type;
	event_attr->size = माप(काष्ठा perf_event_attr);
	event_attr->config = config;
	event_attr->पढ़ो_क्रमmat = PERF_FORMAT_GROUP;
	event_attr->disabled = 1;
	event_attr->exclude_kernel = 1;
	event_attr->exclude_hv = 1;
	event_attr->exclude_guest = 1;
पूर्ण

पूर्णांक perf_event_खोलो_counter(अचिन्हित पूर्णांक type,
			    अचिन्हित दीर्घ config, पूर्णांक group_fd)
अणु
	पूर्णांक fd;
	काष्ठा perf_event_attr event_attr;

	perf_event_attr_init(&event_attr, type, config);

	fd = perf_event_खोलो(&event_attr, 0, -1, group_fd, 0);

	अगर (fd < 0)
		लिखो_त्रुटि("perf_event_open() failed");

	वापस fd;
पूर्ण

पूर्णांक perf_event_enable(पूर्णांक fd)
अणु
	अगर (ioctl(fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) अणु
		लिखो_त्रुटि("error while enabling perf events");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_event_disable(पूर्णांक fd)
अणु
	अगर (ioctl(fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) अणु
		लिखो_त्रुटि("error disabling perf events");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_event_reset(पूर्णांक fd)
अणु
	अगर (ioctl(fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) अणु
		लिखो_त्रुटि("error resetting perf events");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक using_hash_mmu(bool *using_hash)
अणु
	अक्षर line[128];
	खाता *f;
	पूर्णांक rc;

	f = ख_खोलो("/proc/cpuinfo", "r");
	FAIL_IF(!f);

	rc = 0;
	जबतक (ख_माला_लो(line, माप(line), f) != शून्य) अणु
		अगर (!म_भेद(line, "MMU		: Hash\n") ||
		    !म_भेद(line, "platform	: Cell\n") ||
		    !म_भेद(line, "platform	: PowerMac\n")) अणु
			*using_hash = true;
			जाओ out;
		पूर्ण

		अगर (म_भेद(line, "MMU		: Radix\n") == 0) अणु
			*using_hash = false;
			जाओ out;
		पूर्ण
	पूर्ण

	rc = -1;
out:
	ख_बंद(f);
	वापस rc;
पूर्ण
