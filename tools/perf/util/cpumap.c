<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <api/fs/fs.h>
#समावेश "cpumap.h"
#समावेश "debug.h"
#समावेश "event.h"
#समावेश <निश्चित.स>
#समावेश <dirent.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/biपंचांगap.h>
#समावेश "asm/bug.h"

#समावेश <linux/प्रकार.स>
#समावेश <linux/zभाग.स>

अटल पूर्णांक max_cpu_num;
अटल पूर्णांक max_present_cpu_num;
अटल पूर्णांक max_node_num;
अटल पूर्णांक *cpunode_map;

अटल काष्ठा perf_cpu_map *cpu_map__from_entries(काष्ठा cpu_map_entries *cpus)
अणु
	काष्ठा perf_cpu_map *map;

	map = perf_cpu_map__empty_new(cpus->nr);
	अगर (map) अणु
		अचिन्हित i;

		क्रम (i = 0; i < cpus->nr; i++) अणु
			/*
			 * Special treaपंचांगent क्रम -1, which is not real cpu number,
			 * and we need to use (पूर्णांक) -1 to initialize map[i],
			 * otherwise it would become 65535.
			 */
			अगर (cpus->cpu[i] == (u16) -1)
				map->map[i] = -1;
			अन्यथा
				map->map[i] = (पूर्णांक) cpus->cpu[i];
		पूर्ण
	पूर्ण

	वापस map;
पूर्ण

अटल काष्ठा perf_cpu_map *cpu_map__from_mask(काष्ठा perf_record_record_cpu_map *mask)
अणु
	काष्ठा perf_cpu_map *map;
	पूर्णांक nr, nbits = mask->nr * mask->दीर्घ_size * BITS_PER_BYTE;

	nr = biपंचांगap_weight(mask->mask, nbits);

	map = perf_cpu_map__empty_new(nr);
	अगर (map) अणु
		पूर्णांक cpu, i = 0;

		क्रम_each_set_bit(cpu, mask->mask, nbits)
			map->map[i++] = cpu;
	पूर्ण
	वापस map;

पूर्ण

काष्ठा perf_cpu_map *cpu_map__new_data(काष्ठा perf_record_cpu_map_data *data)
अणु
	अगर (data->type == PERF_CPU_MAP__CPUS)
		वापस cpu_map__from_entries((काष्ठा cpu_map_entries *)data->data);
	अन्यथा
		वापस cpu_map__from_mask((काष्ठा perf_record_record_cpu_map *)data->data);
पूर्ण

माप_प्रकार cpu_map__ख_लिखो(काष्ठा perf_cpu_map *map, खाता *fp)
अणु
#घोषणा बफ_मानE 1024
	अक्षर buf[बफ_मानE];

	cpu_map__snprपूर्णांक(map, buf, माप(buf));
	वापस ख_लिखो(fp, "%s\n", buf);
#अघोषित बफ_मानE
पूर्ण

काष्ठा perf_cpu_map *perf_cpu_map__empty_new(पूर्णांक nr)
अणु
	काष्ठा perf_cpu_map *cpus = दो_स्मृति(माप(*cpus) + माप(पूर्णांक) * nr);

	अगर (cpus != शून्य) अणु
		पूर्णांक i;

		cpus->nr = nr;
		क्रम (i = 0; i < nr; i++)
			cpus->map[i] = -1;

		refcount_set(&cpus->refcnt, 1);
	पूर्ण

	वापस cpus;
पूर्ण

काष्ठा cpu_aggr_map *cpu_aggr_map__empty_new(पूर्णांक nr)
अणु
	काष्ठा cpu_aggr_map *cpus = दो_स्मृति(माप(*cpus) + माप(काष्ठा aggr_cpu_id) * nr);

	अगर (cpus != शून्य) अणु
		पूर्णांक i;

		cpus->nr = nr;
		क्रम (i = 0; i < nr; i++)
			cpus->map[i] = cpu_map__empty_aggr_cpu_id();

		refcount_set(&cpus->refcnt, 1);
	पूर्ण

	वापस cpus;
पूर्ण

अटल पूर्णांक cpu__get_topology_पूर्णांक(पूर्णांक cpu, स्थिर अक्षर *name, पूर्णांक *value)
अणु
	अक्षर path[PATH_MAX];

	snम_लिखो(path, PATH_MAX,
		"devices/system/cpu/cpu%d/topology/%s", cpu, name);

	वापस sysfs__पढ़ो_पूर्णांक(path, value);
पूर्ण

पूर्णांक cpu_map__get_socket_id(पूर्णांक cpu)
अणु
	पूर्णांक value, ret = cpu__get_topology_पूर्णांक(cpu, "physical_package_id", &value);
	वापस ret ?: value;
पूर्ण

काष्ठा aggr_cpu_id cpu_map__get_socket(काष्ठा perf_cpu_map *map, पूर्णांक idx,
					व्योम *data __maybe_unused)
अणु
	पूर्णांक cpu;
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();

	अगर (idx > map->nr)
		वापस id;

	cpu = map->map[idx];

	id.socket = cpu_map__get_socket_id(cpu);
	वापस id;
पूर्ण

अटल पूर्णांक cmp_aggr_cpu_id(स्थिर व्योम *a_poपूर्णांकer, स्थिर व्योम *b_poपूर्णांकer)
अणु
	काष्ठा aggr_cpu_id *a = (काष्ठा aggr_cpu_id *)a_poपूर्णांकer;
	काष्ठा aggr_cpu_id *b = (काष्ठा aggr_cpu_id *)b_poपूर्णांकer;

	अगर (a->node != b->node)
		वापस a->node - b->node;
	अन्यथा अगर (a->socket != b->socket)
		वापस a->socket - b->socket;
	अन्यथा अगर (a->die != b->die)
		वापस a->die - b->die;
	अन्यथा अगर (a->core != b->core)
		वापस a->core - b->core;
	अन्यथा
		वापस a->thपढ़ो - b->thपढ़ो;
पूर्ण

पूर्णांक cpu_map__build_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **res,
		       काष्ठा aggr_cpu_id (*f)(काष्ठा perf_cpu_map *map, पूर्णांक cpu, व्योम *data),
		       व्योम *data)
अणु
	पूर्णांक nr = cpus->nr;
	काष्ठा cpu_aggr_map *c = cpu_aggr_map__empty_new(nr);
	पूर्णांक cpu, s2;
	काष्ठा aggr_cpu_id s1;

	अगर (!c)
		वापस -1;

	/* Reset size as it may only be partially filled */
	c->nr = 0;

	क्रम (cpu = 0; cpu < nr; cpu++) अणु
		s1 = f(cpus, cpu, data);
		क्रम (s2 = 0; s2 < c->nr; s2++) अणु
			अगर (cpu_map__compare_aggr_cpu_id(s1, c->map[s2]))
				अवरोध;
		पूर्ण
		अगर (s2 == c->nr) अणु
			c->map[c->nr] = s1;
			c->nr++;
		पूर्ण
	पूर्ण
	/* ensure we process id in increasing order */
	क्विक(c->map, c->nr, माप(काष्ठा aggr_cpu_id), cmp_aggr_cpu_id);

	*res = c;
	वापस 0;
पूर्ण

पूर्णांक cpu_map__get_die_id(पूर्णांक cpu)
अणु
	पूर्णांक value, ret = cpu__get_topology_पूर्णांक(cpu, "die_id", &value);

	वापस ret ?: value;
पूर्ण

काष्ठा aggr_cpu_id cpu_map__get_die(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data)
अणु
	पूर्णांक cpu, die;
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();

	अगर (idx > map->nr)
		वापस id;

	cpu = map->map[idx];

	die = cpu_map__get_die_id(cpu);
	/* There is no die_id on legacy प्रणाली. */
	अगर (die == -1)
		die = 0;

	/*
	 * die_id is relative to socket, so start
	 * with the socket ID and then add die to
	 * make a unique ID.
	 */
	id = cpu_map__get_socket(map, idx, data);
	अगर (cpu_map__aggr_cpu_id_is_empty(id))
		वापस id;

	id.die = die;
	वापस id;
पूर्ण

पूर्णांक cpu_map__get_core_id(पूर्णांक cpu)
अणु
	पूर्णांक value, ret = cpu__get_topology_पूर्णांक(cpu, "core_id", &value);
	वापस ret ?: value;
पूर्ण

पूर्णांक cpu_map__get_node_id(पूर्णांक cpu)
अणु
	वापस cpu__get_node(cpu);
पूर्ण

काष्ठा aggr_cpu_id cpu_map__get_core(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data)
अणु
	पूर्णांक cpu;
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();

	अगर (idx > map->nr)
		वापस id;

	cpu = map->map[idx];

	cpu = cpu_map__get_core_id(cpu);

	/* cpu_map__get_die वापसs a काष्ठा with socket and die set*/
	id = cpu_map__get_die(map, idx, data);
	अगर (cpu_map__aggr_cpu_id_is_empty(id))
		वापस id;

	/*
	 * core_id is relative to socket and die, we need a global id.
	 * So we combine the result from cpu_map__get_die with the core id
	 */
	id.core = cpu;
	वापस id;
पूर्ण

काष्ठा aggr_cpu_id cpu_map__get_node(काष्ठा perf_cpu_map *map, पूर्णांक idx, व्योम *data __maybe_unused)
अणु
	काष्ठा aggr_cpu_id id = cpu_map__empty_aggr_cpu_id();

	अगर (idx < 0 || idx >= map->nr)
		वापस id;

	id.node = cpu_map__get_node_id(map->map[idx]);
	वापस id;
पूर्ण

पूर्णांक cpu_map__build_socket_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **sockp)
अणु
	वापस cpu_map__build_map(cpus, sockp, cpu_map__get_socket, शून्य);
पूर्ण

पूर्णांक cpu_map__build_die_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **diep)
अणु
	वापस cpu_map__build_map(cpus, diep, cpu_map__get_die, शून्य);
पूर्ण

पूर्णांक cpu_map__build_core_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **corep)
अणु
	वापस cpu_map__build_map(cpus, corep, cpu_map__get_core, शून्य);
पूर्ण

पूर्णांक cpu_map__build_node_map(काष्ठा perf_cpu_map *cpus, काष्ठा cpu_aggr_map **numap)
अणु
	वापस cpu_map__build_map(cpus, numap, cpu_map__get_node, शून्य);
पूर्ण

/* setup simple routines to easily access node numbers given a cpu number */
अटल पूर्णांक get_max_num(अक्षर *path, पूर्णांक *max)
अणु
	माप_प्रकार num;
	अक्षर *buf;
	पूर्णांक err = 0;

	अगर (filename__पढ़ो_str(path, &buf, &num))
		वापस -1;

	buf[num] = '\0';

	/* start on the right, to find highest node num */
	जबतक (--num) अणु
		अगर ((buf[num] == ',') || (buf[num] == '-')) अणु
			num++;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (माला_पूछो(&buf[num], "%d", max) < 1) अणु
		err = -1;
		जाओ out;
	पूर्ण

	/* convert from 0-based to 1-based */
	(*max)++;

out:
	मुक्त(buf);
	वापस err;
पूर्ण

/* Determine highest possible cpu in the प्रणाली क्रम sparse allocation */
अटल व्योम set_max_cpu_num(व्योम)
अणु
	स्थिर अक्षर *mnt;
	अक्षर path[PATH_MAX];
	पूर्णांक ret = -1;

	/* set up शेष */
	max_cpu_num = 4096;
	max_present_cpu_num = 4096;

	mnt = sysfs__mountpoपूर्णांक();
	अगर (!mnt)
		जाओ out;

	/* get the highest possible cpu number क्रम a sparse allocation */
	ret = snम_लिखो(path, PATH_MAX, "%s/devices/system/cpu/possible", mnt);
	अगर (ret >= PATH_MAX) अणु
		pr_err("sysfs path crossed PATH_MAX(%d) size\n", PATH_MAX);
		जाओ out;
	पूर्ण

	ret = get_max_num(path, &max_cpu_num);
	अगर (ret)
		जाओ out;

	/* get the highest present cpu number क्रम a sparse allocation */
	ret = snम_लिखो(path, PATH_MAX, "%s/devices/system/cpu/present", mnt);
	अगर (ret >= PATH_MAX) अणु
		pr_err("sysfs path crossed PATH_MAX(%d) size\n", PATH_MAX);
		जाओ out;
	पूर्ण

	ret = get_max_num(path, &max_present_cpu_num);

out:
	अगर (ret)
		pr_err("Failed to read max cpus, using default of %d\n", max_cpu_num);
पूर्ण

/* Determine highest possible node in the प्रणाली क्रम sparse allocation */
अटल व्योम set_max_node_num(व्योम)
अणु
	स्थिर अक्षर *mnt;
	अक्षर path[PATH_MAX];
	पूर्णांक ret = -1;

	/* set up शेष */
	max_node_num = 8;

	mnt = sysfs__mountpoपूर्णांक();
	अगर (!mnt)
		जाओ out;

	/* get the highest possible cpu number क्रम a sparse allocation */
	ret = snम_लिखो(path, PATH_MAX, "%s/devices/system/node/possible", mnt);
	अगर (ret >= PATH_MAX) अणु
		pr_err("sysfs path crossed PATH_MAX(%d) size\n", PATH_MAX);
		जाओ out;
	पूर्ण

	ret = get_max_num(path, &max_node_num);

out:
	अगर (ret)
		pr_err("Failed to read max nodes, using default of %d\n", max_node_num);
पूर्ण

पूर्णांक cpu__max_node(व्योम)
अणु
	अगर (unlikely(!max_node_num))
		set_max_node_num();

	वापस max_node_num;
पूर्ण

पूर्णांक cpu__max_cpu(व्योम)
अणु
	अगर (unlikely(!max_cpu_num))
		set_max_cpu_num();

	वापस max_cpu_num;
पूर्ण

पूर्णांक cpu__max_present_cpu(व्योम)
अणु
	अगर (unlikely(!max_present_cpu_num))
		set_max_cpu_num();

	वापस max_present_cpu_num;
पूर्ण


पूर्णांक cpu__get_node(पूर्णांक cpu)
अणु
	अगर (unlikely(cpunode_map == शून्य)) अणु
		pr_debug("cpu_map not initialized\n");
		वापस -1;
	पूर्ण

	वापस cpunode_map[cpu];
पूर्ण

अटल पूर्णांक init_cpunode_map(व्योम)
अणु
	पूर्णांक i;

	set_max_cpu_num();
	set_max_node_num();

	cpunode_map = सुस्मृति(max_cpu_num, माप(पूर्णांक));
	अगर (!cpunode_map) अणु
		pr_err("%s: calloc failed\n", __func__);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < max_cpu_num; i++)
		cpunode_map[i] = -1;

	वापस 0;
पूर्ण

पूर्णांक cpu__setup_cpunode_map(व्योम)
अणु
	काष्ठा dirent *dent1, *dent2;
	सूची *dir1, *dir2;
	अचिन्हित पूर्णांक cpu, mem;
	अक्षर buf[PATH_MAX];
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *mnt;
	पूर्णांक n;

	/* initialize globals */
	अगर (init_cpunode_map())
		वापस -1;

	mnt = sysfs__mountpoपूर्णांक();
	अगर (!mnt)
		वापस 0;

	n = snम_लिखो(path, PATH_MAX, "%s/devices/system/node", mnt);
	अगर (n >= PATH_MAX) अणु
		pr_err("sysfs path crossed PATH_MAX(%d) size\n", PATH_MAX);
		वापस -1;
	पूर्ण

	dir1 = सूची_खोलो(path);
	अगर (!dir1)
		वापस 0;

	/* walk tree and setup map */
	जबतक ((dent1 = सूची_पढ़ो(dir1)) != शून्य) अणु
		अगर (dent1->d_type != DT_सूची || माला_पूछो(dent1->d_name, "node%u", &mem) < 1)
			जारी;

		n = snम_लिखो(buf, PATH_MAX, "%s/%s", path, dent1->d_name);
		अगर (n >= PATH_MAX) अणु
			pr_err("sysfs path crossed PATH_MAX(%d) size\n", PATH_MAX);
			जारी;
		पूर्ण

		dir2 = सूची_खोलो(buf);
		अगर (!dir2)
			जारी;
		जबतक ((dent2 = सूची_पढ़ो(dir2)) != शून्य) अणु
			अगर (dent2->d_type != DT_LNK || माला_पूछो(dent2->d_name, "cpu%u", &cpu) < 1)
				जारी;
			cpunode_map[cpu] = mem;
		पूर्ण
		बंद_सूची(dir2);
	पूर्ण
	बंद_सूची(dir1);
	वापस 0;
पूर्ण

bool cpu_map__has(काष्ठा perf_cpu_map *cpus, पूर्णांक cpu)
अणु
	वापस perf_cpu_map__idx(cpus, cpu) != -1;
पूर्ण

पूर्णांक cpu_map__cpu(काष्ठा perf_cpu_map *cpus, पूर्णांक idx)
अणु
	वापस cpus->map[idx];
पूर्ण

माप_प्रकार cpu_map__snprपूर्णांक(काष्ठा perf_cpu_map *map, अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक i, cpu, start = -1;
	bool first = true;
	माप_प्रकार ret = 0;

#घोषणा COMMA first ? "" : ","

	क्रम (i = 0; i < map->nr + 1; i++) अणु
		bool last = i == map->nr;

		cpu = last ? पूर्णांक_उच्च : map->map[i];

		अगर (start == -1) अणु
			start = i;
			अगर (last) अणु
				ret += snम_लिखो(buf + ret, size - ret,
						"%s%d", COMMA,
						map->map[i]);
			पूर्ण
		पूर्ण अन्यथा अगर (((i - start) != (cpu - map->map[start])) || last) अणु
			पूर्णांक end = i - 1;

			अगर (start == end) अणु
				ret += snम_लिखो(buf + ret, size - ret,
						"%s%d", COMMA,
						map->map[start]);
			पूर्ण अन्यथा अणु
				ret += snम_लिखो(buf + ret, size - ret,
						"%s%d-%d", COMMA,
						map->map[start], map->map[end]);
			पूर्ण
			first = false;
			start = i;
		पूर्ण
	पूर्ण

#अघोषित COMMA

	pr_debug2("cpumask list: %s\n", buf);
	वापस ret;
पूर्ण

अटल अक्षर hex_अक्षर(अचिन्हित अक्षर val)
अणु
	अगर (val < 10)
		वापस val + '0';
	अगर (val < 16)
		वापस val - 10 + 'a';
	वापस '?';
पूर्ण

माप_प्रकार cpu_map__snprपूर्णांक_mask(काष्ठा perf_cpu_map *map, अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक i, cpu;
	अक्षर *ptr = buf;
	अचिन्हित अक्षर *biपंचांगap;
	पूर्णांक last_cpu = cpu_map__cpu(map, map->nr - 1);

	अगर (buf == शून्य)
		वापस 0;

	biपंचांगap = zalloc(last_cpu / 8 + 1);
	अगर (biपंचांगap == शून्य) अणु
		buf[0] = '\0';
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < map->nr; i++) अणु
		cpu = cpu_map__cpu(map, i);
		biपंचांगap[cpu / 8] |= 1 << (cpu % 8);
	पूर्ण

	क्रम (cpu = last_cpu / 4 * 4; cpu >= 0; cpu -= 4) अणु
		अचिन्हित अक्षर bits = biपंचांगap[cpu / 8];

		अगर (cpu % 8)
			bits >>= 4;
		अन्यथा
			bits &= 0xf;

		*ptr++ = hex_अक्षर(bits);
		अगर ((cpu % 32) == 0 && cpu > 0)
			*ptr++ = ',';
	पूर्ण
	*ptr = '\0';
	मुक्त(biपंचांगap);

	buf[size - 1] = '\0';
	वापस ptr - buf;
पूर्ण

स्थिर काष्ठा perf_cpu_map *cpu_map__online(व्योम) /* thपढ़ो unsafe */
अणु
	अटल स्थिर काष्ठा perf_cpu_map *online = शून्य;

	अगर (!online)
		online = perf_cpu_map__new(शून्य); /* from /sys/devices/प्रणाली/cpu/online */

	वापस online;
पूर्ण

bool cpu_map__compare_aggr_cpu_id(काष्ठा aggr_cpu_id a, काष्ठा aggr_cpu_id b)
अणु
	वापस a.thपढ़ो == b.thपढ़ो &&
		a.node == b.node &&
		a.socket == b.socket &&
		a.die == b.die &&
		a.core == b.core;
पूर्ण

bool cpu_map__aggr_cpu_id_is_empty(काष्ठा aggr_cpu_id a)
अणु
	वापस a.thपढ़ो == -1 &&
		a.node == -1 &&
		a.socket == -1 &&
		a.die == -1 &&
		a.core == -1;
पूर्ण

काष्ठा aggr_cpu_id cpu_map__empty_aggr_cpu_id(व्योम)
अणु
	काष्ठा aggr_cpu_id ret = अणु
		.thपढ़ो = -1,
		.node = -1,
		.socket = -1,
		.die = -1,
		.core = -1
	पूर्ण;
	वापस ret;
पूर्ण
