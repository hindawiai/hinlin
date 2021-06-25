<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <perf/cpumap.h>
#समावेश <मानककोष.स>
#समावेश <linux/refcount.h>
#समावेश <पूर्णांकernal/cpumap.h>
#समावेश <यंत्र/bug.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <प्रकार.स>
#समावेश <सीमा.स>

काष्ठा perf_cpu_map *perf_cpu_map__dummy_new(व्योम)
अणु
	काष्ठा perf_cpu_map *cpus = दो_स्मृति(माप(*cpus) + माप(पूर्णांक));

	अगर (cpus != शून्य) अणु
		cpus->nr = 1;
		cpus->map[0] = -1;
		refcount_set(&cpus->refcnt, 1);
	पूर्ण

	वापस cpus;
पूर्ण

अटल व्योम cpu_map__delete(काष्ठा perf_cpu_map *map)
अणु
	अगर (map) अणु
		WARN_ONCE(refcount_पढ़ो(&map->refcnt) != 0,
			  "cpu_map refcnt unbalanced\n");
		मुक्त(map);
	पूर्ण
पूर्ण

काष्ठा perf_cpu_map *perf_cpu_map__get(काष्ठा perf_cpu_map *map)
अणु
	अगर (map)
		refcount_inc(&map->refcnt);
	वापस map;
पूर्ण

व्योम perf_cpu_map__put(काष्ठा perf_cpu_map *map)
अणु
	अगर (map && refcount_dec_and_test(&map->refcnt))
		cpu_map__delete(map);
पूर्ण

अटल काष्ठा perf_cpu_map *cpu_map__शेष_new(व्योम)
अणु
	काष्ठा perf_cpu_map *cpus;
	पूर्णांक nr_cpus;

	nr_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	अगर (nr_cpus < 0)
		वापस शून्य;

	cpus = दो_स्मृति(माप(*cpus) + nr_cpus * माप(पूर्णांक));
	अगर (cpus != शून्य) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_cpus; ++i)
			cpus->map[i] = i;

		cpus->nr = nr_cpus;
		refcount_set(&cpus->refcnt, 1);
	पूर्ण

	वापस cpus;
पूर्ण

अटल पूर्णांक cmp_पूर्णांक(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस *(स्थिर पूर्णांक *)a - *(स्थिर पूर्णांक*)b;
पूर्ण

अटल काष्ठा perf_cpu_map *cpu_map__trim_new(पूर्णांक nr_cpus, पूर्णांक *पंचांगp_cpus)
अणु
	माप_प्रकार payload_size = nr_cpus * माप(पूर्णांक);
	काष्ठा perf_cpu_map *cpus = दो_स्मृति(माप(*cpus) + payload_size);
	पूर्णांक i, j;

	अगर (cpus != शून्य) अणु
		स_नकल(cpus->map, पंचांगp_cpus, payload_size);
		क्विक(cpus->map, nr_cpus, माप(पूर्णांक), cmp_पूर्णांक);
		/* Remove dups */
		j = 0;
		क्रम (i = 0; i < nr_cpus; i++) अणु
			अगर (i == 0 || cpus->map[i] != cpus->map[i - 1])
				cpus->map[j++] = cpus->map[i];
		पूर्ण
		cpus->nr = j;
		निश्चित(j <= nr_cpus);
		refcount_set(&cpus->refcnt, 1);
	पूर्ण

	वापस cpus;
पूर्ण

काष्ठा perf_cpu_map *perf_cpu_map__पढ़ो(खाता *file)
अणु
	काष्ठा perf_cpu_map *cpus = शून्य;
	पूर्णांक nr_cpus = 0;
	पूर्णांक *पंचांगp_cpus = शून्य, *पंचांगp;
	पूर्णांक max_entries = 0;
	पूर्णांक n, cpu, prev;
	अक्षर sep;

	sep = 0;
	prev = -1;
	क्रम (;;) अणु
		n = ख_पूछो(file, "%u%c", &cpu, &sep);
		अगर (n <= 0)
			अवरोध;
		अगर (prev >= 0) अणु
			पूर्णांक new_max = nr_cpus + cpu - prev - 1;

			WARN_ONCE(new_max >= MAX_NR_CPUS, "Perf can support %d CPUs. "
							  "Consider raising MAX_NR_CPUS\n", MAX_NR_CPUS);

			अगर (new_max >= max_entries) अणु
				max_entries = new_max + MAX_NR_CPUS / 2;
				पंचांगp = पुनः_स्मृति(पंचांगp_cpus, max_entries * माप(पूर्णांक));
				अगर (पंचांगp == शून्य)
					जाओ out_मुक्त_पंचांगp;
				पंचांगp_cpus = पंचांगp;
			पूर्ण

			जबतक (++prev < cpu)
				पंचांगp_cpus[nr_cpus++] = prev;
		पूर्ण
		अगर (nr_cpus == max_entries) अणु
			max_entries += MAX_NR_CPUS;
			पंचांगp = पुनः_स्मृति(पंचांगp_cpus, max_entries * माप(पूर्णांक));
			अगर (पंचांगp == शून्य)
				जाओ out_मुक्त_पंचांगp;
			पंचांगp_cpus = पंचांगp;
		पूर्ण

		पंचांगp_cpus[nr_cpus++] = cpu;
		अगर (n == 2 && sep == '-')
			prev = cpu;
		अन्यथा
			prev = -1;
		अगर (n == 1 || sep == '\n')
			अवरोध;
	पूर्ण

	अगर (nr_cpus > 0)
		cpus = cpu_map__trim_new(nr_cpus, पंचांगp_cpus);
	अन्यथा
		cpus = cpu_map__शेष_new();
out_मुक्त_पंचांगp:
	मुक्त(पंचांगp_cpus);
	वापस cpus;
पूर्ण

अटल काष्ठा perf_cpu_map *cpu_map__पढ़ो_all_cpu_map(व्योम)
अणु
	काष्ठा perf_cpu_map *cpus = शून्य;
	खाता *onlnf;

	onlnf = ख_खोलो("/sys/devices/system/cpu/online", "r");
	अगर (!onlnf)
		वापस cpu_map__शेष_new();

	cpus = perf_cpu_map__पढ़ो(onlnf);
	ख_बंद(onlnf);
	वापस cpus;
पूर्ण

काष्ठा perf_cpu_map *perf_cpu_map__new(स्थिर अक्षर *cpu_list)
अणु
	काष्ठा perf_cpu_map *cpus = शून्य;
	अचिन्हित दीर्घ start_cpu, end_cpu = 0;
	अक्षर *p = शून्य;
	पूर्णांक i, nr_cpus = 0;
	पूर्णांक *पंचांगp_cpus = शून्य, *पंचांगp;
	पूर्णांक max_entries = 0;

	अगर (!cpu_list)
		वापस cpu_map__पढ़ो_all_cpu_map();

	/*
	 * must handle the हाल of empty cpumap to cover
	 * TOPOLOGY header क्रम NUMA nodes with no CPU
	 * ( e.g., because of CPU hotplug)
	 */
	अगर (!है_अंक(*cpu_list) && *cpu_list != '\0')
		जाओ out;

	जबतक (है_अंक(*cpu_list)) अणु
		p = शून्य;
		start_cpu = म_से_अदीर्घ(cpu_list, &p, 0);
		अगर (start_cpu >= पूर्णांक_उच्च
		    || (*p != '\0' && *p != ',' && *p != '-'))
			जाओ invalid;

		अगर (*p == '-') अणु
			cpu_list = ++p;
			p = शून्य;
			end_cpu = म_से_अदीर्घ(cpu_list, &p, 0);

			अगर (end_cpu >= पूर्णांक_उच्च || (*p != '\0' && *p != ','))
				जाओ invalid;

			अगर (end_cpu < start_cpu)
				जाओ invalid;
		पूर्ण अन्यथा अणु
			end_cpu = start_cpu;
		पूर्ण

		WARN_ONCE(end_cpu >= MAX_NR_CPUS, "Perf can support %d CPUs. "
						  "Consider raising MAX_NR_CPUS\n", MAX_NR_CPUS);

		क्रम (; start_cpu <= end_cpu; start_cpu++) अणु
			/* check क्रम duplicates */
			क्रम (i = 0; i < nr_cpus; i++)
				अगर (पंचांगp_cpus[i] == (पूर्णांक)start_cpu)
					जाओ invalid;

			अगर (nr_cpus == max_entries) अणु
				max_entries += MAX_NR_CPUS;
				पंचांगp = पुनः_स्मृति(पंचांगp_cpus, max_entries * माप(पूर्णांक));
				अगर (पंचांगp == शून्य)
					जाओ invalid;
				पंचांगp_cpus = पंचांगp;
			पूर्ण
			पंचांगp_cpus[nr_cpus++] = (पूर्णांक)start_cpu;
		पूर्ण
		अगर (*p)
			++p;

		cpu_list = p;
	पूर्ण

	अगर (nr_cpus > 0)
		cpus = cpu_map__trim_new(nr_cpus, पंचांगp_cpus);
	अन्यथा अगर (*cpu_list != '\0')
		cpus = cpu_map__शेष_new();
	अन्यथा
		cpus = perf_cpu_map__dummy_new();
invalid:
	मुक्त(पंचांगp_cpus);
out:
	वापस cpus;
पूर्ण

पूर्णांक perf_cpu_map__cpu(स्थिर काष्ठा perf_cpu_map *cpus, पूर्णांक idx)
अणु
	अगर (cpus && idx < cpus->nr)
		वापस cpus->map[idx];

	वापस -1;
पूर्ण

पूर्णांक perf_cpu_map__nr(स्थिर काष्ठा perf_cpu_map *cpus)
अणु
	वापस cpus ? cpus->nr : 1;
पूर्ण

bool perf_cpu_map__empty(स्थिर काष्ठा perf_cpu_map *map)
अणु
	वापस map ? map->map[0] == -1 : true;
पूर्ण

पूर्णांक perf_cpu_map__idx(काष्ठा perf_cpu_map *cpus, पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cpus->nr; ++i) अणु
		अगर (cpus->map[i] == cpu)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक perf_cpu_map__max(काष्ठा perf_cpu_map *map)
अणु
	पूर्णांक i, max = -1;

	क्रम (i = 0; i < map->nr; i++) अणु
		अगर (map->map[i] > max)
			max = map->map[i];
	पूर्ण

	वापस max;
पूर्ण

/*
 * Merge two cpumaps
 *
 * orig either माला_लो मुक्तd and replaced with a new map, or reused
 * with no reference count change (similar to "realloc")
 * other has its reference count increased.
 */

काष्ठा perf_cpu_map *perf_cpu_map__merge(काष्ठा perf_cpu_map *orig,
					 काष्ठा perf_cpu_map *other)
अणु
	पूर्णांक *पंचांगp_cpus;
	पूर्णांक पंचांगp_len;
	पूर्णांक i, j, k;
	काष्ठा perf_cpu_map *merged;

	अगर (!orig && !other)
		वापस शून्य;
	अगर (!orig) अणु
		perf_cpu_map__get(other);
		वापस other;
	पूर्ण
	अगर (!other)
		वापस orig;
	अगर (orig->nr == other->nr &&
	    !स_भेद(orig->map, other->map, orig->nr * माप(पूर्णांक)))
		वापस orig;

	पंचांगp_len = orig->nr + other->nr;
	पंचांगp_cpus = दो_स्मृति(पंचांगp_len * माप(पूर्णांक));
	अगर (!पंचांगp_cpus)
		वापस शून्य;

	/* Standard merge algorithm from wikipedia */
	i = j = k = 0;
	जबतक (i < orig->nr && j < other->nr) अणु
		अगर (orig->map[i] <= other->map[j]) अणु
			अगर (orig->map[i] == other->map[j])
				j++;
			पंचांगp_cpus[k++] = orig->map[i++];
		पूर्ण अन्यथा
			पंचांगp_cpus[k++] = other->map[j++];
	पूर्ण

	जबतक (i < orig->nr)
		पंचांगp_cpus[k++] = orig->map[i++];

	जबतक (j < other->nr)
		पंचांगp_cpus[k++] = other->map[j++];
	निश्चित(k <= पंचांगp_len);

	merged = cpu_map__trim_new(k, पंचांगp_cpus);
	मुक्त(पंचांगp_cpus);
	perf_cpu_map__put(orig);
	वापस merged;
पूर्ण
