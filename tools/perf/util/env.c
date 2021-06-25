<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "cpumap.h"
#समावेश "debug.h"
#समावेश "env.h"
#समावेश "util/header.h"
#समावेश <linux/प्रकार.स>
#समावेश <linux/zभाग.स>
#समावेश "cgroup.h"
#समावेश <त्रुटिसं.स>
#समावेश <sys/utsname.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>

काष्ठा perf_env perf_env;

#अगर_घोषित HAVE_LIBBPF_SUPPORT
#समावेश "bpf-event.h"
#समावेश <bpf/libbpf.h>

व्योम perf_env__insert_bpf_prog_info(काष्ठा perf_env *env,
				    काष्ठा bpf_prog_info_node *info_node)
अणु
	__u32 prog_id = info_node->info_linear->info.id;
	काष्ठा bpf_prog_info_node *node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rb_node **p;

	करोwn_ग_लिखो(&env->bpf_progs.lock);
	p = &env->bpf_progs.infos.rb_node;

	जबतक (*p != शून्य) अणु
		parent = *p;
		node = rb_entry(parent, काष्ठा bpf_prog_info_node, rb_node);
		अगर (prog_id < node->info_linear->info.id) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (prog_id > node->info_linear->info.id) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			pr_debug("duplicated bpf prog info %u\n", prog_id);
			जाओ out;
		पूर्ण
	पूर्ण

	rb_link_node(&info_node->rb_node, parent, p);
	rb_insert_color(&info_node->rb_node, &env->bpf_progs.infos);
	env->bpf_progs.infos_cnt++;
out:
	up_ग_लिखो(&env->bpf_progs.lock);
पूर्ण

काष्ठा bpf_prog_info_node *perf_env__find_bpf_prog_info(काष्ठा perf_env *env,
							__u32 prog_id)
अणु
	काष्ठा bpf_prog_info_node *node = शून्य;
	काष्ठा rb_node *n;

	करोwn_पढ़ो(&env->bpf_progs.lock);
	n = env->bpf_progs.infos.rb_node;

	जबतक (n) अणु
		node = rb_entry(n, काष्ठा bpf_prog_info_node, rb_node);
		अगर (prog_id < node->info_linear->info.id)
			n = n->rb_left;
		अन्यथा अगर (prog_id > node->info_linear->info.id)
			n = n->rb_right;
		अन्यथा
			जाओ out;
	पूर्ण
	node = शून्य;

out:
	up_पढ़ो(&env->bpf_progs.lock);
	वापस node;
पूर्ण

व्योम perf_env__insert_btf(काष्ठा perf_env *env, काष्ठा btf_node *btf_node)
अणु
	काष्ठा rb_node *parent = शून्य;
	__u32 btf_id = btf_node->id;
	काष्ठा btf_node *node;
	काष्ठा rb_node **p;

	करोwn_ग_लिखो(&env->bpf_progs.lock);
	p = &env->bpf_progs.btfs.rb_node;

	जबतक (*p != शून्य) अणु
		parent = *p;
		node = rb_entry(parent, काष्ठा btf_node, rb_node);
		अगर (btf_id < node->id) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (btf_id > node->id) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			pr_debug("duplicated btf %u\n", btf_id);
			जाओ out;
		पूर्ण
	पूर्ण

	rb_link_node(&btf_node->rb_node, parent, p);
	rb_insert_color(&btf_node->rb_node, &env->bpf_progs.btfs);
	env->bpf_progs.btfs_cnt++;
out:
	up_ग_लिखो(&env->bpf_progs.lock);
पूर्ण

काष्ठा btf_node *perf_env__find_btf(काष्ठा perf_env *env, __u32 btf_id)
अणु
	काष्ठा btf_node *node = शून्य;
	काष्ठा rb_node *n;

	करोwn_पढ़ो(&env->bpf_progs.lock);
	n = env->bpf_progs.btfs.rb_node;

	जबतक (n) अणु
		node = rb_entry(n, काष्ठा btf_node, rb_node);
		अगर (btf_id < node->id)
			n = n->rb_left;
		अन्यथा अगर (btf_id > node->id)
			n = n->rb_right;
		अन्यथा
			जाओ out;
	पूर्ण
	node = शून्य;

out:
	up_पढ़ो(&env->bpf_progs.lock);
	वापस node;
पूर्ण

/* purge data in bpf_progs.infos tree */
अटल व्योम perf_env__purge_bpf(काष्ठा perf_env *env)
अणु
	काष्ठा rb_root *root;
	काष्ठा rb_node *next;

	करोwn_ग_लिखो(&env->bpf_progs.lock);

	root = &env->bpf_progs.infos;
	next = rb_first(root);

	जबतक (next) अणु
		काष्ठा bpf_prog_info_node *node;

		node = rb_entry(next, काष्ठा bpf_prog_info_node, rb_node);
		next = rb_next(&node->rb_node);
		rb_erase(&node->rb_node, root);
		मुक्त(node->info_linear);
		मुक्त(node);
	पूर्ण

	env->bpf_progs.infos_cnt = 0;

	root = &env->bpf_progs.btfs;
	next = rb_first(root);

	जबतक (next) अणु
		काष्ठा btf_node *node;

		node = rb_entry(next, काष्ठा btf_node, rb_node);
		next = rb_next(&node->rb_node);
		rb_erase(&node->rb_node, root);
		मुक्त(node);
	पूर्ण

	env->bpf_progs.btfs_cnt = 0;

	up_ग_लिखो(&env->bpf_progs.lock);
पूर्ण
#अन्यथा // HAVE_LIBBPF_SUPPORT
अटल व्योम perf_env__purge_bpf(काष्ठा perf_env *env __maybe_unused)
अणु
पूर्ण
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT

व्योम perf_env__निकास(काष्ठा perf_env *env)
अणु
	पूर्णांक i;

	perf_env__purge_bpf(env);
	perf_env__purge_cgroups(env);
	zमुक्त(&env->hostname);
	zमुक्त(&env->os_release);
	zमुक्त(&env->version);
	zमुक्त(&env->arch);
	zमुक्त(&env->cpu_desc);
	zमुक्त(&env->cpuid);
	zमुक्त(&env->cmdline);
	zमुक्त(&env->cmdline_argv);
	zमुक्त(&env->sibling_cores);
	zमुक्त(&env->sibling_thपढ़ोs);
	zमुक्त(&env->pmu_mappings);
	zमुक्त(&env->cpu);
	zमुक्त(&env->numa_map);

	क्रम (i = 0; i < env->nr_numa_nodes; i++)
		perf_cpu_map__put(env->numa_nodes[i].map);
	zमुक्त(&env->numa_nodes);

	क्रम (i = 0; i < env->caches_cnt; i++)
		cpu_cache_level__मुक्त(&env->caches[i]);
	zमुक्त(&env->caches);

	क्रम (i = 0; i < env->nr_memory_nodes; i++)
		zमुक्त(&env->memory_nodes[i].set);
	zमुक्त(&env->memory_nodes);
पूर्ण

व्योम perf_env__init(काष्ठा perf_env *env __maybe_unused)
अणु
#अगर_घोषित HAVE_LIBBPF_SUPPORT
	env->bpf_progs.infos = RB_ROOT;
	env->bpf_progs.btfs = RB_ROOT;
	init_rwsem(&env->bpf_progs.lock);
#पूर्ण_अगर
पूर्ण

पूर्णांक perf_env__set_cmdline(काष्ठा perf_env *env, पूर्णांक argc, स्थिर अक्षर *argv[])
अणु
	पूर्णांक i;

	/* करो not include शून्य termination */
	env->cmdline_argv = सुस्मृति(argc, माप(अक्षर *));
	अगर (env->cmdline_argv == शून्य)
		जाओ out_enomem;

	/*
	 * Must copy argv contents because it माला_लो moved around during option
	 * parsing:
	 */
	क्रम (i = 0; i < argc ; i++) अणु
		env->cmdline_argv[i] = argv[i];
		अगर (env->cmdline_argv[i] == शून्य)
			जाओ out_मुक्त;
	पूर्ण

	env->nr_cmdline = argc;

	वापस 0;
out_मुक्त:
	zमुक्त(&env->cmdline_argv);
out_enomem:
	वापस -ENOMEM;
पूर्ण

पूर्णांक perf_env__पढ़ो_cpu_topology_map(काष्ठा perf_env *env)
अणु
	पूर्णांक cpu, nr_cpus;

	अगर (env->cpu != शून्य)
		वापस 0;

	अगर (env->nr_cpus_avail == 0)
		env->nr_cpus_avail = cpu__max_present_cpu();

	nr_cpus = env->nr_cpus_avail;
	अगर (nr_cpus == -1)
		वापस -EINVAL;

	env->cpu = सुस्मृति(nr_cpus, माप(env->cpu[0]));
	अगर (env->cpu == शून्य)
		वापस -ENOMEM;

	क्रम (cpu = 0; cpu < nr_cpus; ++cpu) अणु
		env->cpu[cpu].core_id	= cpu_map__get_core_id(cpu);
		env->cpu[cpu].socket_id	= cpu_map__get_socket_id(cpu);
		env->cpu[cpu].die_id	= cpu_map__get_die_id(cpu);
	पूर्ण

	env->nr_cpus_avail = nr_cpus;
	वापस 0;
पूर्ण

पूर्णांक perf_env__पढ़ो_cpuid(काष्ठा perf_env *env)
अणु
	अक्षर cpuid[128];
	पूर्णांक err = get_cpuid(cpuid, माप(cpuid));

	अगर (err)
		वापस err;

	मुक्त(env->cpuid);
	env->cpuid = strdup(cpuid);
	अगर (env->cpuid == शून्य)
		वापस ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक perf_env__पढ़ो_arch(काष्ठा perf_env *env)
अणु
	काष्ठा utsname uts;

	अगर (env->arch)
		वापस 0;

	अगर (!uname(&uts))
		env->arch = strdup(uts.machine);

	वापस env->arch ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक perf_env__पढ़ो_nr_cpus_avail(काष्ठा perf_env *env)
अणु
	अगर (env->nr_cpus_avail == 0)
		env->nr_cpus_avail = cpu__max_present_cpu();

	वापस env->nr_cpus_avail ? 0 : -ENOENT;
पूर्ण

स्थिर अक्षर *perf_env__raw_arch(काष्ठा perf_env *env)
अणु
	वापस env && !perf_env__पढ़ो_arch(env) ? env->arch : "unknown";
पूर्ण

पूर्णांक perf_env__nr_cpus_avail(काष्ठा perf_env *env)
अणु
	वापस env && !perf_env__पढ़ो_nr_cpus_avail(env) ? env->nr_cpus_avail : 0;
पूर्ण

व्योम cpu_cache_level__मुक्त(काष्ठा cpu_cache_level *cache)
अणु
	zमुक्त(&cache->type);
	zमुक्त(&cache->map);
	zमुक्त(&cache->size);
पूर्ण

/*
 * Return architecture name in a normalized क्रमm.
 * The conversion logic comes from the Makefile.
 */
अटल स्थिर अक्षर *normalize_arch(अक्षर *arch)
अणु
	अगर (!म_भेद(arch, "x86_64"))
		वापस "x86";
	अगर (arch[0] == 'i' && arch[2] == '8' && arch[3] == '6')
		वापस "x86";
	अगर (!म_भेद(arch, "sun4u") || !म_भेदन(arch, "sparc", 5))
		वापस "sparc";
	अगर (!म_भेद(arch, "aarch64") || !म_भेद(arch, "arm64"))
		वापस "arm64";
	अगर (!म_भेदन(arch, "arm", 3) || !म_भेद(arch, "sa110"))
		वापस "arm";
	अगर (!म_भेदन(arch, "s390", 4))
		वापस "s390";
	अगर (!म_भेदन(arch, "parisc", 6))
		वापस "parisc";
	अगर (!म_भेदन(arch, "powerpc", 7) || !म_भेदन(arch, "ppc", 3))
		वापस "powerpc";
	अगर (!म_भेदन(arch, "mips", 4))
		वापस "mips";
	अगर (!म_भेदन(arch, "sh", 2) && है_अंक(arch[2]))
		वापस "sh";

	वापस arch;
पूर्ण

स्थिर अक्षर *perf_env__arch(काष्ठा perf_env *env)
अणु
	अक्षर *arch_name;

	अगर (!env || !env->arch) अणु /* Assume local operation */
		अटल काष्ठा utsname uts = अणु .machine[0] = '\0', पूर्ण;
		अगर (uts.machine[0] == '\0' && uname(&uts) < 0)
			वापस शून्य;
		arch_name = uts.machine;
	पूर्ण अन्यथा
		arch_name = env->arch;

	वापस normalize_arch(arch_name);
पूर्ण


पूर्णांक perf_env__numa_node(काष्ठा perf_env *env, पूर्णांक cpu)
अणु
	अगर (!env->nr_numa_map) अणु
		काष्ठा numa_node *nn;
		पूर्णांक i, nr = 0;

		क्रम (i = 0; i < env->nr_numa_nodes; i++) अणु
			nn = &env->numa_nodes[i];
			nr = max(nr, perf_cpu_map__max(nn->map));
		पूर्ण

		nr++;

		/*
		 * We initialize the numa_map array to prepare
		 * it क्रम missing cpus, which वापस node -1
		 */
		env->numa_map = दो_स्मृति(nr * माप(पूर्णांक));
		अगर (!env->numa_map)
			वापस -1;

		क्रम (i = 0; i < nr; i++)
			env->numa_map[i] = -1;

		env->nr_numa_map = nr;

		क्रम (i = 0; i < env->nr_numa_nodes; i++) अणु
			पूर्णांक पंचांगp, j;

			nn = &env->numa_nodes[i];
			perf_cpu_map__क्रम_each_cpu(j, पंचांगp, nn->map)
				env->numa_map[j] = i;
		पूर्ण
	पूर्ण

	वापस cpu >= 0 && cpu < env->nr_numa_map ? env->numa_map[cpu] : -1;
पूर्ण
