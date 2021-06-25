<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा LOOP_BOUND 0xf
#घोषणा MAX_ENTRIES 8
#घोषणा HALF_ENTRIES (MAX_ENTRIES >> 1)

_Static_निश्चित(MAX_ENTRIES < LOOP_BOUND, "MAX_ENTRIES must be < LOOP_BOUND");

क्रमागत bpf_map_type g_map_type = BPF_MAP_TYPE_UNSPEC;
__u32 g_line = 0;
पूर्णांक page_size = 0; /* userspace should set it */

#घोषणा VERIFY_TYPE(type, func) (अणु	\
	g_map_type = type;		\
	अगर (!func())			\
		वापस 0;		\
पूर्ण)


#घोषणा VERIFY(expr) (अणु		\
	g_line = __LINE__;	\
	अगर (!(expr))		\
		वापस 0;	\
पूर्ण)

काष्ठा bpf_map अणु
	क्रमागत bpf_map_type map_type;
	__u32 key_size;
	__u32 value_size;
	__u32 max_entries;
	__u32 id;
पूर्ण __attribute__((preserve_access_index));

अटल अंतरभूत पूर्णांक check_bpf_map_fields(काष्ठा bpf_map *map, __u32 key_size,
				       __u32 value_size, __u32 max_entries)
अणु
	VERIFY(map->map_type == g_map_type);
	VERIFY(map->key_size == key_size);
	VERIFY(map->value_size == value_size);
	VERIFY(map->max_entries == max_entries);
	VERIFY(map->id > 0);

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक check_bpf_map_ptr(काष्ठा bpf_map *indirect,
				    काष्ठा bpf_map *direct)
अणु
	VERIFY(indirect->map_type == direct->map_type);
	VERIFY(indirect->key_size == direct->key_size);
	VERIFY(indirect->value_size == direct->value_size);
	VERIFY(indirect->max_entries == direct->max_entries);
	VERIFY(indirect->id == direct->id);

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक check(काष्ठा bpf_map *indirect, काष्ठा bpf_map *direct,
			__u32 key_size, __u32 value_size, __u32 max_entries)
अणु
	VERIFY(check_bpf_map_ptr(indirect, direct));
	VERIFY(check_bpf_map_fields(indirect, key_size, value_size,
				    max_entries));
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक check_शेष(काष्ठा bpf_map *indirect,
				काष्ठा bpf_map *direct)
अणु
	VERIFY(check(indirect, direct, माप(__u32), माप(__u32),
		     MAX_ENTRIES));
	वापस 1;
पूर्ण

अटल __noअंतरभूत पूर्णांक
check_शेष_noअंतरभूत(काष्ठा bpf_map *indirect, काष्ठा bpf_map *direct)
अणु
	VERIFY(check(indirect, direct, माप(__u32), माप(__u32),
		     MAX_ENTRIES));
	वापस 1;
पूर्ण

प्रकार काष्ठा अणु
	पूर्णांक counter;
पूर्ण atomic_t;

काष्ठा bpf_htab अणु
	काष्ठा bpf_map map;
	atomic_t count;
	__u32 n_buckets;
	__u32 elem_size;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC); /* to test bpf_htab.count */
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_hash SEC(".maps");

अटल अंतरभूत पूर्णांक check_hash(व्योम)
अणु
	काष्ठा bpf_htab *hash = (काष्ठा bpf_htab *)&m_hash;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_hash;
	पूर्णांक i;

	VERIFY(check_शेष_noअंतरभूत(&hash->map, map));

	VERIFY(hash->n_buckets == MAX_ENTRIES);
	VERIFY(hash->elem_size == 64);

	VERIFY(hash->count.counter == 0);
	क्रम (i = 0; i < HALF_ENTRIES; ++i) अणु
		स्थिर __u32 key = i;
		स्थिर __u32 val = 1;

		अगर (bpf_map_update_elem(hash, &key, &val, 0))
			वापस 0;
	पूर्ण
	VERIFY(hash->count.counter == HALF_ENTRIES);

	वापस 1;
पूर्ण

काष्ठा bpf_array अणु
	काष्ठा bpf_map map;
	__u32 elem_size;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_array SEC(".maps");

अटल अंतरभूत पूर्णांक check_array(व्योम)
अणु
	काष्ठा bpf_array *array = (काष्ठा bpf_array *)&m_array;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_array;
	पूर्णांक i, n_lookups = 0, n_keys = 0;

	VERIFY(check_शेष(&array->map, map));

	VERIFY(array->elem_size == 8);

	क्रम (i = 0; i < array->map.max_entries && i < LOOP_BOUND; ++i) अणु
		स्थिर __u32 key = i;
		__u32 *val = bpf_map_lookup_elem(array, &key);

		++n_lookups;
		अगर (val)
			++n_keys;
	पूर्ण

	VERIFY(n_lookups == MAX_ENTRIES);
	VERIFY(n_keys == MAX_ENTRIES);

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_prog_array SEC(".maps");

अटल अंतरभूत पूर्णांक check_prog_array(व्योम)
अणु
	काष्ठा bpf_array *prog_array = (काष्ठा bpf_array *)&m_prog_array;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_prog_array;

	VERIFY(check_शेष(&prog_array->map, map));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_perf_event_array SEC(".maps");

अटल अंतरभूत पूर्णांक check_perf_event_array(व्योम)
अणु
	काष्ठा bpf_array *perf_event_array = (काष्ठा bpf_array *)&m_perf_event_array;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_perf_event_array;

	VERIFY(check_शेष(&perf_event_array->map, map));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_HASH);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_percpu_hash SEC(".maps");

अटल अंतरभूत पूर्णांक check_percpu_hash(व्योम)
अणु
	काष्ठा bpf_htab *percpu_hash = (काष्ठा bpf_htab *)&m_percpu_hash;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_percpu_hash;

	VERIFY(check_शेष(&percpu_hash->map, map));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_percpu_array SEC(".maps");

अटल अंतरभूत पूर्णांक check_percpu_array(व्योम)
अणु
	काष्ठा bpf_array *percpu_array = (काष्ठा bpf_array *)&m_percpu_array;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_percpu_array;

	VERIFY(check_शेष(&percpu_array->map, map));

	वापस 1;
पूर्ण

काष्ठा bpf_stack_map अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण m_stack_trace SEC(".maps");

अटल अंतरभूत पूर्णांक check_stack_trace(व्योम)
अणु
	काष्ठा bpf_stack_map *stack_trace =
		(काष्ठा bpf_stack_map *)&m_stack_trace;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_stack_trace;

	VERIFY(check(&stack_trace->map, map, माप(__u32), माप(__u64),
		     MAX_ENTRIES));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CGROUP_ARRAY);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_cgroup_array SEC(".maps");

अटल अंतरभूत पूर्णांक check_cgroup_array(व्योम)
अणु
	काष्ठा bpf_array *cgroup_array = (काष्ठा bpf_array *)&m_cgroup_array;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_cgroup_array;

	VERIFY(check_शेष(&cgroup_array->map, map));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_HASH);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_lru_hash SEC(".maps");

अटल अंतरभूत पूर्णांक check_lru_hash(व्योम)
अणु
	काष्ठा bpf_htab *lru_hash = (काष्ठा bpf_htab *)&m_lru_hash;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_lru_hash;

	VERIFY(check_शेष(&lru_hash->map, map));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LRU_PERCPU_HASH);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_lru_percpu_hash SEC(".maps");

अटल अंतरभूत पूर्णांक check_lru_percpu_hash(व्योम)
अणु
	काष्ठा bpf_htab *lru_percpu_hash = (काष्ठा bpf_htab *)&m_lru_percpu_hash;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_lru_percpu_hash;

	VERIFY(check_शेष(&lru_percpu_hash->map, map));

	वापस 1;
पूर्ण

काष्ठा lpm_trie अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा lpm_key अणु
	काष्ठा bpf_lpm_trie_key trie_key;
	__u32 data;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_LPM_TRIE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, काष्ठा lpm_key);
	__type(value, __u32);
पूर्ण m_lpm_trie SEC(".maps");

अटल अंतरभूत पूर्णांक check_lpm_trie(व्योम)
अणु
	काष्ठा lpm_trie *lpm_trie = (काष्ठा lpm_trie *)&m_lpm_trie;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_lpm_trie;

	VERIFY(check(&lpm_trie->map, map, माप(काष्ठा lpm_key), माप(__u32),
		     MAX_ENTRIES));

	वापस 1;
पूर्ण

काष्ठा inner_map अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण inner_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
	__array(values, काष्ठा अणु
		__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
		__uपूर्णांक(max_entries, 1);
		__type(key, __u32);
		__type(value, __u32);
	पूर्ण);
पूर्ण m_array_of_maps SEC(".maps") = अणु
	.values = अणु (व्योम *)&inner_map, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक check_array_of_maps(व्योम)
अणु
	काष्ठा bpf_array *array_of_maps = (काष्ठा bpf_array *)&m_array_of_maps;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_array_of_maps;

	VERIFY(check_शेष(&array_of_maps->map, map));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
	__array(values, काष्ठा inner_map);
पूर्ण m_hash_of_maps SEC(".maps") = अणु
	.values = अणु
		[2] = &inner_map,
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक check_hash_of_maps(व्योम)
अणु
	काष्ठा bpf_htab *hash_of_maps = (काष्ठा bpf_htab *)&m_hash_of_maps;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_hash_of_maps;

	VERIFY(check_शेष(&hash_of_maps->map, map));

	वापस 1;
पूर्ण

काष्ठा bpf_dtab अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_DEVMAP);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_devmap SEC(".maps");

अटल अंतरभूत पूर्णांक check_devmap(व्योम)
अणु
	काष्ठा bpf_dtab *devmap = (काष्ठा bpf_dtab *)&m_devmap;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_devmap;

	VERIFY(check_शेष(&devmap->map, map));

	वापस 1;
पूर्ण

काष्ठा bpf_stab अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_sockmap SEC(".maps");

अटल अंतरभूत पूर्णांक check_sockmap(व्योम)
अणु
	काष्ठा bpf_stab *sockmap = (काष्ठा bpf_stab *)&m_sockmap;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_sockmap;

	VERIFY(check_शेष(&sockmap->map, map));

	वापस 1;
पूर्ण

काष्ठा bpf_cpu_map अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CPUMAP);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_cpumap SEC(".maps");

अटल अंतरभूत पूर्णांक check_cpumap(व्योम)
अणु
	काष्ठा bpf_cpu_map *cpumap = (काष्ठा bpf_cpu_map *)&m_cpumap;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_cpumap;

	VERIFY(check_शेष(&cpumap->map, map));

	वापस 1;
पूर्ण

काष्ठा xsk_map अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_XSKMAP);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_xskmap SEC(".maps");

अटल अंतरभूत पूर्णांक check_xskmap(व्योम)
अणु
	काष्ठा xsk_map *xskmap = (काष्ठा xsk_map *)&m_xskmap;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_xskmap;

	VERIFY(check_शेष(&xskmap->map, map));

	वापस 1;
पूर्ण

काष्ठा bpf_shtab अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKHASH);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_sockhash SEC(".maps");

अटल अंतरभूत पूर्णांक check_sockhash(व्योम)
अणु
	काष्ठा bpf_shtab *sockhash = (काष्ठा bpf_shtab *)&m_sockhash;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_sockhash;

	VERIFY(check_शेष(&sockhash->map, map));

	वापस 1;
पूर्ण

काष्ठा bpf_cgroup_storage_map अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CGROUP_STORAGE);
	__type(key, काष्ठा bpf_cgroup_storage_key);
	__type(value, __u32);
पूर्ण m_cgroup_storage SEC(".maps");

अटल अंतरभूत पूर्णांक check_cgroup_storage(व्योम)
अणु
	काष्ठा bpf_cgroup_storage_map *cgroup_storage =
		(काष्ठा bpf_cgroup_storage_map *)&m_cgroup_storage;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_cgroup_storage;

	VERIFY(check(&cgroup_storage->map, map,
		     माप(काष्ठा bpf_cgroup_storage_key), माप(__u32), 0));

	वापस 1;
पूर्ण

काष्ठा reuseport_array अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_REUSEPORT_SOCKARRAY);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_reuseport_sockarray SEC(".maps");

अटल अंतरभूत पूर्णांक check_reuseport_sockarray(व्योम)
अणु
	काष्ठा reuseport_array *reuseport_sockarray =
		(काष्ठा reuseport_array *)&m_reuseport_sockarray;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_reuseport_sockarray;

	VERIFY(check_शेष(&reuseport_sockarray->map, map));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE);
	__type(key, काष्ठा bpf_cgroup_storage_key);
	__type(value, __u32);
पूर्ण m_percpu_cgroup_storage SEC(".maps");

अटल अंतरभूत पूर्णांक check_percpu_cgroup_storage(व्योम)
अणु
	काष्ठा bpf_cgroup_storage_map *percpu_cgroup_storage =
		(काष्ठा bpf_cgroup_storage_map *)&m_percpu_cgroup_storage;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_percpu_cgroup_storage;

	VERIFY(check(&percpu_cgroup_storage->map, map,
		     माप(काष्ठा bpf_cgroup_storage_key), माप(__u32), 0));

	वापस 1;
पूर्ण

काष्ठा bpf_queue_stack अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_QUEUE);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(value, __u32);
पूर्ण m_queue SEC(".maps");

अटल अंतरभूत पूर्णांक check_queue(व्योम)
अणु
	काष्ठा bpf_queue_stack *queue = (काष्ठा bpf_queue_stack *)&m_queue;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_queue;

	VERIFY(check(&queue->map, map, 0, माप(__u32), MAX_ENTRIES));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(value, __u32);
पूर्ण m_stack SEC(".maps");

अटल अंतरभूत पूर्णांक check_stack(व्योम)
अणु
	काष्ठा bpf_queue_stack *stack = (काष्ठा bpf_queue_stack *)&m_stack;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_stack;

	VERIFY(check(&stack->map, map, 0, माप(__u32), MAX_ENTRIES));

	वापस 1;
पूर्ण

काष्ठा bpf_local_storage_map अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_sk_storage SEC(".maps");

अटल अंतरभूत पूर्णांक check_sk_storage(व्योम)
अणु
	काष्ठा bpf_local_storage_map *sk_storage =
		(काष्ठा bpf_local_storage_map *)&m_sk_storage;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_sk_storage;

	VERIFY(check(&sk_storage->map, map, माप(__u32), माप(__u32), 0));

	वापस 1;
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_DEVMAP_HASH);
	__uपूर्णांक(max_entries, MAX_ENTRIES);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण m_devmap_hash SEC(".maps");

अटल अंतरभूत पूर्णांक check_devmap_hash(व्योम)
अणु
	काष्ठा bpf_dtab *devmap_hash = (काष्ठा bpf_dtab *)&m_devmap_hash;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_devmap_hash;

	VERIFY(check_शेष(&devmap_hash->map, map));

	वापस 1;
पूर्ण

काष्ठा bpf_ringbuf_map अणु
	काष्ठा bpf_map map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_RINGBUF);
पूर्ण m_ringbuf SEC(".maps");

अटल अंतरभूत पूर्णांक check_ringbuf(व्योम)
अणु
	काष्ठा bpf_ringbuf_map *ringbuf = (काष्ठा bpf_ringbuf_map *)&m_ringbuf;
	काष्ठा bpf_map *map = (काष्ठा bpf_map *)&m_ringbuf;

	VERIFY(check(&ringbuf->map, map, 0, 0, page_size));

	वापस 1;
पूर्ण

SEC("cgroup_skb/egress")
पूर्णांक cg_skb(व्योम *ctx)
अणु
	VERIFY_TYPE(BPF_MAP_TYPE_HASH, check_hash);
	VERIFY_TYPE(BPF_MAP_TYPE_ARRAY, check_array);
	VERIFY_TYPE(BPF_MAP_TYPE_PROG_ARRAY, check_prog_array);
	VERIFY_TYPE(BPF_MAP_TYPE_PERF_EVENT_ARRAY, check_perf_event_array);
	VERIFY_TYPE(BPF_MAP_TYPE_PERCPU_HASH, check_percpu_hash);
	VERIFY_TYPE(BPF_MAP_TYPE_PERCPU_ARRAY, check_percpu_array);
	VERIFY_TYPE(BPF_MAP_TYPE_STACK_TRACE, check_stack_trace);
	VERIFY_TYPE(BPF_MAP_TYPE_CGROUP_ARRAY, check_cgroup_array);
	VERIFY_TYPE(BPF_MAP_TYPE_LRU_HASH, check_lru_hash);
	VERIFY_TYPE(BPF_MAP_TYPE_LRU_PERCPU_HASH, check_lru_percpu_hash);
	VERIFY_TYPE(BPF_MAP_TYPE_LPM_TRIE, check_lpm_trie);
	VERIFY_TYPE(BPF_MAP_TYPE_ARRAY_OF_MAPS, check_array_of_maps);
	VERIFY_TYPE(BPF_MAP_TYPE_HASH_OF_MAPS, check_hash_of_maps);
	VERIFY_TYPE(BPF_MAP_TYPE_DEVMAP, check_devmap);
	VERIFY_TYPE(BPF_MAP_TYPE_SOCKMAP, check_sockmap);
	VERIFY_TYPE(BPF_MAP_TYPE_CPUMAP, check_cpumap);
	VERIFY_TYPE(BPF_MAP_TYPE_XSKMAP, check_xskmap);
	VERIFY_TYPE(BPF_MAP_TYPE_SOCKHASH, check_sockhash);
	VERIFY_TYPE(BPF_MAP_TYPE_CGROUP_STORAGE, check_cgroup_storage);
	VERIFY_TYPE(BPF_MAP_TYPE_REUSEPORT_SOCKARRAY,
		    check_reuseport_sockarray);
	VERIFY_TYPE(BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE,
		    check_percpu_cgroup_storage);
	VERIFY_TYPE(BPF_MAP_TYPE_QUEUE, check_queue);
	VERIFY_TYPE(BPF_MAP_TYPE_STACK, check_stack);
	VERIFY_TYPE(BPF_MAP_TYPE_SK_STORAGE, check_sk_storage);
	VERIFY_TYPE(BPF_MAP_TYPE_DEVMAP_HASH, check_devmap_hash);
	VERIFY_TYPE(BPF_MAP_TYPE_RINGBUF, check_ringbuf);

	वापस 1;
पूर्ण

__u32 _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";
