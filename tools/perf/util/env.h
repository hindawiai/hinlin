<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_ENV_H
#घोषणा __PERF_ENV_H

#समावेश <linux/types.h>
#समावेश <linux/rbtree.h>
#समावेश "rwsem.h"

काष्ठा perf_cpu_map;

काष्ठा cpu_topology_map अणु
	पूर्णांक	socket_id;
	पूर्णांक	die_id;
	पूर्णांक	core_id;
पूर्ण;

काष्ठा cpu_cache_level अणु
	u32	level;
	u32	line_size;
	u32	sets;
	u32	ways;
	अक्षर	*type;
	अक्षर	*size;
	अक्षर	*map;
पूर्ण;

काष्ठा numa_node अणु
	u32		 node;
	u64		 mem_total;
	u64		 mem_मुक्त;
	काष्ठा perf_cpu_map	*map;
पूर्ण;

काष्ठा memory_node अणु
	u64		 node;
	u64		 size;
	अचिन्हित दीर्घ	*set;
पूर्ण;

काष्ठा perf_env अणु
	अक्षर			*hostname;
	अक्षर			*os_release;
	अक्षर			*version;
	अक्षर			*arch;
	पूर्णांक			nr_cpus_online;
	पूर्णांक			nr_cpus_avail;
	अक्षर			*cpu_desc;
	अक्षर			*cpuid;
	अचिन्हित दीर्घ दीर्घ	total_mem;
	अचिन्हित पूर्णांक		msr_pmu_type;
	अचिन्हित पूर्णांक		max_branches;

	पूर्णांक			nr_cmdline;
	पूर्णांक			nr_sibling_cores;
	पूर्णांक			nr_sibling_dies;
	पूर्णांक			nr_sibling_thपढ़ोs;
	पूर्णांक			nr_numa_nodes;
	पूर्णांक			nr_memory_nodes;
	पूर्णांक			nr_pmu_mappings;
	पूर्णांक			nr_groups;
	पूर्णांक			nr_cpu_pmu_caps;
	अक्षर			*cmdline;
	स्थिर अक्षर		**cmdline_argv;
	अक्षर			*sibling_cores;
	अक्षर			*sibling_dies;
	अक्षर			*sibling_thपढ़ोs;
	अक्षर			*pmu_mappings;
	अक्षर			*cpu_pmu_caps;
	काष्ठा cpu_topology_map	*cpu;
	काष्ठा cpu_cache_level	*caches;
	पूर्णांक			 caches_cnt;
	u32			comp_ratio;
	u32			comp_ver;
	u32			comp_type;
	u32			comp_level;
	u32			comp_mmap_len;
	काष्ठा numa_node	*numa_nodes;
	काष्ठा memory_node	*memory_nodes;
	अचिन्हित दीर्घ दीर्घ	 memory_bsize;
#अगर_घोषित HAVE_LIBBPF_SUPPORT
	/*
	 * bpf_info_lock protects bpf rbtrees. This is needed because the
	 * trees are accessed by dअगरferent thपढ़ोs in perf-top
	 */
	काष्ठा अणु
		काष्ठा rw_semaphore	lock;
		काष्ठा rb_root		infos;
		u32			infos_cnt;
		काष्ठा rb_root		btfs;
		u32			btfs_cnt;
	पूर्ण bpf_progs;
#पूर्ण_अगर // HAVE_LIBBPF_SUPPORT
	/* same reason as above (क्रम perf-top) */
	काष्ठा अणु
		काष्ठा rw_semaphore	lock;
		काष्ठा rb_root		tree;
	पूर्ण cgroups;

	/* For fast cpu to numa node lookup via perf_env__numa_node */
	पूर्णांक			*numa_map;
	पूर्णांक			 nr_numa_map;

	/* For real घड़ी समय reference. */
	काष्ठा अणु
		u64	tod_ns;
		u64	घड़ीid_ns;
		u64     घड़ीid_res_ns;
		पूर्णांक	घड़ीid;
		/*
		 * enabled is valid क्रम report mode, and is true अगर above
		 * values are set, it's set in process_घड़ी_data
		 */
		bool	enabled;
	पूर्ण घड़ी;
पूर्ण;

क्रमागत perf_compress_type अणु
	PERF_COMP_NONE = 0,
	PERF_COMP_ZSTD,
	PERF_COMP_MAX
पूर्ण;

काष्ठा bpf_prog_info_node;
काष्ठा btf_node;

बाह्य काष्ठा perf_env perf_env;

व्योम perf_env__निकास(काष्ठा perf_env *env);

पूर्णांक perf_env__set_cmdline(काष्ठा perf_env *env, पूर्णांक argc, स्थिर अक्षर *argv[]);

पूर्णांक perf_env__पढ़ो_cpuid(काष्ठा perf_env *env);
पूर्णांक perf_env__पढ़ो_cpu_topology_map(काष्ठा perf_env *env);

व्योम cpu_cache_level__मुक्त(काष्ठा cpu_cache_level *cache);

स्थिर अक्षर *perf_env__arch(काष्ठा perf_env *env);
स्थिर अक्षर *perf_env__raw_arch(काष्ठा perf_env *env);
पूर्णांक perf_env__nr_cpus_avail(काष्ठा perf_env *env);

व्योम perf_env__init(काष्ठा perf_env *env);
व्योम perf_env__insert_bpf_prog_info(काष्ठा perf_env *env,
				    काष्ठा bpf_prog_info_node *info_node);
काष्ठा bpf_prog_info_node *perf_env__find_bpf_prog_info(काष्ठा perf_env *env,
							__u32 prog_id);
व्योम perf_env__insert_btf(काष्ठा perf_env *env, काष्ठा btf_node *btf_node);
काष्ठा btf_node *perf_env__find_btf(काष्ठा perf_env *env, __u32 btf_id);

पूर्णांक perf_env__numa_node(काष्ठा perf_env *env, पूर्णांक cpu);
#पूर्ण_अगर /* __PERF_ENV_H */
