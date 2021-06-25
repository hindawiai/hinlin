<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2004-2009  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 */

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>

#समावेश "cpupower.h"
#समावेश "cpupower_intern.h"

अचिन्हित पूर्णांक cpuघातer_पढ़ो_sysfs(स्थिर अक्षर *path, अक्षर *buf, माप_प्रकार buflen)
अणु
	sमाप_प्रकार numपढ़ो;
	पूर्णांक fd;

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस 0;

	numपढ़ो = पढ़ो(fd, buf, buflen - 1);
	अगर (numपढ़ो < 1) अणु
		बंद(fd);
		वापस 0;
	पूर्ण

	buf[numपढ़ो] = '\0';
	बंद(fd);

	वापस (अचिन्हित पूर्णांक) numपढ़ो;
पूर्ण

अचिन्हित पूर्णांक cpuघातer_ग_लिखो_sysfs(स्थिर अक्षर *path, अक्षर *buf, माप_प्रकार buflen)
अणु
	sमाप_प्रकार numwritten;
	पूर्णांक fd;

	fd = खोलो(path, O_WRONLY);
	अगर (fd == -1)
		वापस 0;

	numwritten = ग_लिखो(fd, buf, buflen - 1);
	अगर (numwritten < 1) अणु
		लिखो_त्रुटि(path);
		बंद(fd);
		वापस -1;
	पूर्ण

	बंद(fd);

	वापस (अचिन्हित पूर्णांक) numwritten;
पूर्ण

/*
 * Detect whether a CPU is online
 *
 * Returns:
 *     1 -> अगर CPU is online
 *     0 -> अगर CPU is offline
 *     negative त्रुटि_सं values in error हाल
 */
पूर्णांक cpuघातer_is_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अक्षर path[SYSFS_PATH_MAX];
	पूर्णांक fd;
	sमाप_प्रकार numपढ़ो;
	अचिन्हित दीर्घ दीर्घ value;
	अक्षर linebuf[MAX_LINE_LEN];
	अक्षर *endp;
	काष्ठा stat statbuf;

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u", cpu);

	अगर (stat(path, &statbuf) != 0)
		वापस 0;

	/*
	 * kernel without CONFIG_HOTPLUG_CPU
	 * -> cpuX directory exists, but not cpuX/online file
	 */
	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/online", cpu);
	अगर (stat(path, &statbuf) != 0)
		वापस 1;

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस -त्रुटि_सं;

	numपढ़ो = पढ़ो(fd, linebuf, MAX_LINE_LEN - 1);
	अगर (numपढ़ो < 1) अणु
		बंद(fd);
		वापस -EIO;
	पूर्ण
	linebuf[numपढ़ो] = '\0';
	बंद(fd);

	value = म_से_अदीर्घl(linebuf, &endp, 0);
	अगर (value > 1)
		वापस -EINVAL;

	वापस value;
पूर्ण

/* वापसs -1 on failure, 0 on success */
अटल पूर्णांक sysfs_topology_पढ़ो_file(अचिन्हित पूर्णांक cpu, स्थिर अक्षर *fname, पूर्णांक *result)
अणु
	अक्षर linebuf[MAX_LINE_LEN];
	अक्षर *endp;
	अक्षर path[SYSFS_PATH_MAX];

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/topology/%s",
			 cpu, fname);
	अगर (cpuघातer_पढ़ो_sysfs(path, linebuf, MAX_LINE_LEN) == 0)
		वापस -1;
	*result = म_से_दीर्घ(linebuf, &endp, 0);
	अगर (endp == linebuf || त्रुटि_सं == दुस्फल)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक __compare(स्थिर व्योम *t1, स्थिर व्योम *t2)
अणु
	काष्ठा cpuid_core_info *top1 = (काष्ठा cpuid_core_info *)t1;
	काष्ठा cpuid_core_info *top2 = (काष्ठा cpuid_core_info *)t2;
	अगर (top1->pkg < top2->pkg)
		वापस -1;
	अन्यथा अगर (top1->pkg > top2->pkg)
		वापस 1;
	अन्यथा अगर (top1->core < top2->core)
		वापस -1;
	अन्यथा अगर (top1->core > top2->core)
		वापस 1;
	अन्यथा अगर (top1->cpu < top2->cpu)
		वापस -1;
	अन्यथा अगर (top1->cpu > top2->cpu)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * Returns amount of cpus, negative on error, cpu_top must be
 * passed to cpu_topology_release to मुक्त resources
 *
 * Array is sorted after ->pkg, ->core, then ->cpu
 */
पूर्णांक get_cpu_topology(काष्ठा cpuघातer_topology *cpu_top)
अणु
	पूर्णांक cpu, last_pkg, cpus = sysconf(_SC_NPROCESSORS_CONF);

	cpu_top->core_info = दो_स्मृति(माप(काष्ठा cpuid_core_info) * cpus);
	अगर (cpu_top->core_info == शून्य)
		वापस -ENOMEM;
	cpu_top->pkgs = cpu_top->cores = 0;
	क्रम (cpu = 0; cpu < cpus; cpu++) अणु
		cpu_top->core_info[cpu].cpu = cpu;
		cpu_top->core_info[cpu].is_online = cpuघातer_is_cpu_online(cpu);
		अगर(sysfs_topology_पढ़ो_file(
			cpu,
			"physical_package_id",
			&(cpu_top->core_info[cpu].pkg)) < 0) अणु
			cpu_top->core_info[cpu].pkg = -1;
			cpu_top->core_info[cpu].core = -1;
			जारी;
		पूर्ण
		अगर(sysfs_topology_पढ़ो_file(
			cpu,
			"core_id",
			&(cpu_top->core_info[cpu].core)) < 0) अणु
			cpu_top->core_info[cpu].pkg = -1;
			cpu_top->core_info[cpu].core = -1;
			जारी;
		पूर्ण
	पूर्ण

	क्विक(cpu_top->core_info, cpus, माप(काष्ठा cpuid_core_info),
	      __compare);

	/* Count the number of distinct pkgs values. This works
	   because the primary sort of the core_info काष्ठा was just
	   करोne by pkg value. */
	last_pkg = cpu_top->core_info[0].pkg;
	क्रम(cpu = 1; cpu < cpus; cpu++) अणु
		अगर (cpu_top->core_info[cpu].pkg != last_pkg &&
				cpu_top->core_info[cpu].pkg != -1) अणु

			last_pkg = cpu_top->core_info[cpu].pkg;
			cpu_top->pkgs++;
		पूर्ण
	पूर्ण
	अगर (!(cpu_top->core_info[0].pkg == -1))
		cpu_top->pkgs++;

	/* Intel's cores count is not consecutively numbered, there may
	 * be a core_id of 3, but none of 2. Assume there always is 0
	 * Get amount of cores by counting duplicates in a package
	क्रम (cpu = 0; cpu_top->core_info[cpu].pkg = 0 && cpu < cpus; cpu++) अणु
		अगर (cpu_top->core_info[cpu].core == 0)
	cpu_top->cores++;
	*/
	वापस cpus;
पूर्ण

व्योम cpu_topology_release(काष्ठा cpuघातer_topology cpu_top)
अणु
	मुक्त(cpu_top.core_info);
पूर्ण
