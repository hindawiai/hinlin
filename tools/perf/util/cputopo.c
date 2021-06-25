<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/param.h>
#समावेश <sys/utsname.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <api/fs/fs.h>
#समावेश <linux/zभाग.स>
#समावेश <perf/cpumap.h>

#समावेश "cputopo.h"
#समावेश "cpumap.h"
#समावेश "debug.h"
#समावेश "env.h"

#घोषणा CORE_SIB_FMT \
	"%s/devices/system/cpu/cpu%d/topology/core_siblings_list"
#घोषणा DIE_SIB_FMT \
	"%s/devices/system/cpu/cpu%d/topology/die_cpus_list"
#घोषणा THRD_SIB_FMT \
	"%s/devices/system/cpu/cpu%d/topology/thread_siblings_list"
#घोषणा THRD_SIB_FMT_NEW \
	"%s/devices/system/cpu/cpu%d/topology/core_cpus_list"
#घोषणा NODE_ONLINE_FMT \
	"%s/devices/system/node/online"
#घोषणा NODE_MEMINFO_FMT \
	"%s/devices/system/node/node%d/meminfo"
#घोषणा NODE_CPULIST_FMT \
	"%s/devices/system/node/node%d/cpulist"

अटल पूर्णांक build_cpu_topology(काष्ठा cpu_topology *tp, पूर्णांक cpu)
अणु
	खाता *fp;
	अक्षर filename[MAXPATHLEN];
	अक्षर *buf = शून्य, *p;
	माप_प्रकार len = 0;
	sमाप_प्रकार sret;
	u32 i = 0;
	पूर्णांक ret = -1;

	scnम_लिखो(filename, MAXPATHLEN, CORE_SIB_FMT,
		  sysfs__mountpoपूर्णांक(), cpu);
	fp = ख_खोलो(filename, "r");
	अगर (!fp)
		जाओ try_dies;

	sret = getline(&buf, &len, fp);
	ख_बंद(fp);
	अगर (sret <= 0)
		जाओ try_dies;

	p = म_अक्षर(buf, '\n');
	अगर (p)
		*p = '\0';

	क्रम (i = 0; i < tp->core_sib; i++) अणु
		अगर (!म_भेद(buf, tp->core_siblings[i]))
			अवरोध;
	पूर्ण
	अगर (i == tp->core_sib) अणु
		tp->core_siblings[i] = buf;
		tp->core_sib++;
		buf = शून्य;
		len = 0;
	पूर्ण
	ret = 0;

try_dies:
	अगर (!tp->die_siblings)
		जाओ try_thपढ़ोs;

	scnम_लिखो(filename, MAXPATHLEN, DIE_SIB_FMT,
		  sysfs__mountpoपूर्णांक(), cpu);
	fp = ख_खोलो(filename, "r");
	अगर (!fp)
		जाओ try_thपढ़ोs;

	sret = getline(&buf, &len, fp);
	ख_बंद(fp);
	अगर (sret <= 0)
		जाओ try_thपढ़ोs;

	p = म_अक्षर(buf, '\n');
	अगर (p)
		*p = '\0';

	क्रम (i = 0; i < tp->die_sib; i++) अणु
		अगर (!म_भेद(buf, tp->die_siblings[i]))
			अवरोध;
	पूर्ण
	अगर (i == tp->die_sib) अणु
		tp->die_siblings[i] = buf;
		tp->die_sib++;
		buf = शून्य;
		len = 0;
	पूर्ण
	ret = 0;

try_thपढ़ोs:
	scnम_लिखो(filename, MAXPATHLEN, THRD_SIB_FMT_NEW,
		  sysfs__mountpoपूर्णांक(), cpu);
	अगर (access(filename, F_OK) == -1) अणु
		scnम_लिखो(filename, MAXPATHLEN, THRD_SIB_FMT,
			  sysfs__mountpoपूर्णांक(), cpu);
	पूर्ण
	fp = ख_खोलो(filename, "r");
	अगर (!fp)
		जाओ करोne;

	अगर (getline(&buf, &len, fp) <= 0)
		जाओ करोne;

	p = म_अक्षर(buf, '\n');
	अगर (p)
		*p = '\0';

	क्रम (i = 0; i < tp->thपढ़ो_sib; i++) अणु
		अगर (!म_भेद(buf, tp->thपढ़ो_siblings[i]))
			अवरोध;
	पूर्ण
	अगर (i == tp->thपढ़ो_sib) अणु
		tp->thपढ़ो_siblings[i] = buf;
		tp->thपढ़ो_sib++;
		buf = शून्य;
	पूर्ण
	ret = 0;
करोne:
	अगर (fp)
		ख_बंद(fp);
	मुक्त(buf);
	वापस ret;
पूर्ण

व्योम cpu_topology__delete(काष्ठा cpu_topology *tp)
अणु
	u32 i;

	अगर (!tp)
		वापस;

	क्रम (i = 0 ; i < tp->core_sib; i++)
		zमुक्त(&tp->core_siblings[i]);

	अगर (tp->die_sib) अणु
		क्रम (i = 0 ; i < tp->die_sib; i++)
			zमुक्त(&tp->die_siblings[i]);
	पूर्ण

	क्रम (i = 0 ; i < tp->thपढ़ो_sib; i++)
		zमुक्त(&tp->thपढ़ो_siblings[i]);

	मुक्त(tp);
पूर्ण

अटल bool has_die_topology(व्योम)
अणु
	अक्षर filename[MAXPATHLEN];
	काष्ठा utsname uts;

	अगर (uname(&uts) < 0)
		वापस false;

	अगर (म_भेदन(uts.machine, "x86_64", 6))
		वापस false;

	scnम_लिखो(filename, MAXPATHLEN, DIE_SIB_FMT,
		  sysfs__mountpoपूर्णांक(), 0);
	अगर (access(filename, F_OK) == -1)
		वापस false;

	वापस true;
पूर्ण

काष्ठा cpu_topology *cpu_topology__new(व्योम)
अणु
	काष्ठा cpu_topology *tp = शून्य;
	व्योम *addr;
	u32 nr, i, nr_addr;
	माप_प्रकार sz;
	दीर्घ ncpus;
	पूर्णांक ret = -1;
	काष्ठा perf_cpu_map *map;
	bool has_die = has_die_topology();

	ncpus = cpu__max_present_cpu();

	/* build online CPU map */
	map = perf_cpu_map__new(शून्य);
	अगर (map == शून्य) अणु
		pr_debug("failed to get system cpumap\n");
		वापस शून्य;
	पूर्ण

	nr = (u32)(ncpus & अच_पूर्णांक_उच्च);

	sz = nr * माप(अक्षर *);
	अगर (has_die)
		nr_addr = 3;
	अन्यथा
		nr_addr = 2;
	addr = सुस्मृति(1, माप(*tp) + nr_addr * sz);
	अगर (!addr)
		जाओ out_मुक्त;

	tp = addr;
	addr += माप(*tp);
	tp->core_siblings = addr;
	addr += sz;
	अगर (has_die) अणु
		tp->die_siblings = addr;
		addr += sz;
	पूर्ण
	tp->thपढ़ो_siblings = addr;

	क्रम (i = 0; i < nr; i++) अणु
		अगर (!cpu_map__has(map, i))
			जारी;

		ret = build_cpu_topology(tp, i);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

out_मुक्त:
	perf_cpu_map__put(map);
	अगर (ret) अणु
		cpu_topology__delete(tp);
		tp = शून्य;
	पूर्ण
	वापस tp;
पूर्ण

अटल पूर्णांक load_numa_node(काष्ठा numa_topology_node *node, पूर्णांक nr)
अणु
	अक्षर str[MAXPATHLEN];
	अक्षर field[32];
	अक्षर *buf = शून्य, *p;
	माप_प्रकार len = 0;
	पूर्णांक ret = -1;
	खाता *fp;
	u64 mem;

	node->node = (u32) nr;

	scnम_लिखो(str, MAXPATHLEN, NODE_MEMINFO_FMT,
		  sysfs__mountpoपूर्णांक(), nr);
	fp = ख_खोलो(str, "r");
	अगर (!fp)
		वापस -1;

	जबतक (getline(&buf, &len, fp) > 0) अणु
		/* skip over invalid lines */
		अगर (!म_अक्षर(buf, ':'))
			जारी;
		अगर (माला_पूछो(buf, "%*s %*d %31s %"PRIu64, field, &mem) != 2)
			जाओ err;
		अगर (!म_भेद(field, "MemTotal:"))
			node->mem_total = mem;
		अगर (!म_भेद(field, "MemFree:"))
			node->mem_मुक्त = mem;
		अगर (node->mem_total && node->mem_मुक्त)
			अवरोध;
	पूर्ण

	ख_बंद(fp);
	fp = शून्य;

	scnम_लिखो(str, MAXPATHLEN, NODE_CPULIST_FMT,
		  sysfs__mountpoपूर्णांक(), nr);

	fp = ख_खोलो(str, "r");
	अगर (!fp)
		वापस -1;

	अगर (getline(&buf, &len, fp) <= 0)
		जाओ err;

	p = म_अक्षर(buf, '\n');
	अगर (p)
		*p = '\0';

	node->cpus = buf;
	ख_बंद(fp);
	वापस 0;

err:
	मुक्त(buf);
	अगर (fp)
		ख_बंद(fp);
	वापस ret;
पूर्ण

काष्ठा numa_topology *numa_topology__new(व्योम)
अणु
	काष्ठा perf_cpu_map *node_map = शून्य;
	काष्ठा numa_topology *tp = शून्य;
	अक्षर path[MAXPATHLEN];
	अक्षर *buf = शून्य;
	माप_प्रकार len = 0;
	u32 nr, i;
	खाता *fp;
	अक्षर *c;

	scnम_लिखो(path, MAXPATHLEN, NODE_ONLINE_FMT,
		  sysfs__mountpoपूर्णांक());

	fp = ख_खोलो(path, "r");
	अगर (!fp)
		वापस शून्य;

	अगर (getline(&buf, &len, fp) <= 0)
		जाओ out;

	c = म_अक्षर(buf, '\n');
	अगर (c)
		*c = '\0';

	node_map = perf_cpu_map__new(buf);
	अगर (!node_map)
		जाओ out;

	nr = (u32) node_map->nr;

	tp = zalloc(माप(*tp) + माप(tp->nodes[0])*nr);
	अगर (!tp)
		जाओ out;

	tp->nr = nr;

	क्रम (i = 0; i < nr; i++) अणु
		अगर (load_numa_node(&tp->nodes[i], node_map->map[i])) अणु
			numa_topology__delete(tp);
			tp = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	मुक्त(buf);
	ख_बंद(fp);
	perf_cpu_map__put(node_map);
	वापस tp;
पूर्ण

व्योम numa_topology__delete(काष्ठा numa_topology *tp)
अणु
	u32 i;

	क्रम (i = 0; i < tp->nr; i++)
		zमुक्त(&tp->nodes[i].cpus);

	मुक्त(tp);
पूर्ण
