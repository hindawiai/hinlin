<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <यंत्र/unistd.h>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <sys/रुको.h>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <sys/resource.h>
#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#घोषणा TEST_BIT(t) (1U << (t))
#घोषणा MAX_NR_CPUS 1024

अटल __u64 समय_get_ns(व्योम)
अणु
	काष्ठा बारpec ts;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
	वापस ts.tv_sec * 1000000000ull + ts.tv_nsec;
पूर्ण

क्रमागत test_type अणु
	HASH_PREALLOC,
	PERCPU_HASH_PREALLOC,
	HASH_KMALLOC,
	PERCPU_HASH_KMALLOC,
	LRU_HASH_PREALLOC,
	NOCOMMON_LRU_HASH_PREALLOC,
	LPM_KMALLOC,
	HASH_LOOKUP,
	ARRAY_LOOKUP,
	INNER_LRU_HASH_PREALLOC,
	LRU_HASH_LOOKUP,
	NR_TESTS,
पूर्ण;

स्थिर अक्षर *test_map_names[NR_TESTS] = अणु
	[HASH_PREALLOC] = "hash_map",
	[PERCPU_HASH_PREALLOC] = "percpu_hash_map",
	[HASH_KMALLOC] = "hash_map_alloc",
	[PERCPU_HASH_KMALLOC] = "percpu_hash_map_alloc",
	[LRU_HASH_PREALLOC] = "lru_hash_map",
	[NOCOMMON_LRU_HASH_PREALLOC] = "nocommon_lru_hash_map",
	[LPM_KMALLOC] = "lpm_trie_map_alloc",
	[HASH_LOOKUP] = "hash_map",
	[ARRAY_LOOKUP] = "array_map",
	[INNER_LRU_HASH_PREALLOC] = "inner_lru_hash_map",
	[LRU_HASH_LOOKUP] = "lru_hash_lookup_map",
पूर्ण;

क्रमागत map_idx अणु
	array_of_lru_hashs_idx,
	hash_map_alloc_idx,
	lru_hash_lookup_idx,
	NR_IDXES,
पूर्ण;

अटल पूर्णांक map_fd[NR_IDXES];

अटल पूर्णांक test_flags = ~0;
अटल uपूर्णांक32_t num_map_entries;
अटल uपूर्णांक32_t inner_lru_hash_size;
अटल पूर्णांक lru_hash_lookup_test_entries = 32;
अटल uपूर्णांक32_t max_cnt = 1000000;

अटल पूर्णांक check_test_flags(क्रमागत test_type t)
अणु
	वापस test_flags & TEST_BIT(t);
पूर्ण

अटल व्योम test_hash_pपुनः_स्मृति(पूर्णांक cpu)
अणु
	__u64 start_समय;
	पूर्णांक i;

	start_समय = समय_get_ns();
	क्रम (i = 0; i < max_cnt; i++)
		syscall(__NR_getuid);
	म_लिखो("%d:hash_map_perf pre-alloc %lld events per sec\n",
	       cpu, max_cnt * 1000000000ll / (समय_get_ns() - start_समय));
पूर्ण

अटल पूर्णांक pre_test_lru_hash_lookup(पूर्णांक tasks)
अणु
	पूर्णांक fd = map_fd[lru_hash_lookup_idx];
	uपूर्णांक32_t key;
	दीर्घ val = 1;
	पूर्णांक ret;

	अगर (num_map_entries > lru_hash_lookup_test_entries)
		lru_hash_lookup_test_entries = num_map_entries;

	/* Populate the lru_hash_map क्रम LRU_HASH_LOOKUP perf test.
	 *
	 * It is fine that the user requests क्रम a map with
	 * num_map_entries < 32 and some of the later lru hash lookup
	 * may वापस not found.  For LRU map, we are not पूर्णांकerested
	 * in such small map perक्रमmance.
	 */
	क्रम (key = 0; key < lru_hash_lookup_test_entries; key++) अणु
		ret = bpf_map_update_elem(fd, &key, &val, BPF_NOEXIST);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम करो_test_lru(क्रमागत test_type test, पूर्णांक cpu)
अणु
	अटल पूर्णांक inner_lru_map_fds[MAX_NR_CPUS];

	काष्ठा sockaddr_in6 in6 = अणु .sin6_family = AF_INET6 पूर्ण;
	स्थिर अक्षर *test_name;
	__u64 start_समय;
	पूर्णांक i, ret;

	अगर (test == INNER_LRU_HASH_PREALLOC && cpu) अणु
		/* If CPU is not 0, create inner_lru hash map and insert the fd
		 * value पूर्णांकo the array_of_lru_hash map. In हाल of CPU 0,
		 * 'inner_lru_hash_map' was अटलally inserted on the map init
		 */
		पूर्णांक outer_fd = map_fd[array_of_lru_hashs_idx];
		अचिन्हित पूर्णांक mycpu, mynode;

		निश्चित(cpu < MAX_NR_CPUS);

		ret = syscall(__NR_अ_लोpu, &mycpu, &mynode, शून्य);
		निश्चित(!ret);

		inner_lru_map_fds[cpu] =
			bpf_create_map_node(BPF_MAP_TYPE_LRU_HASH,
					    test_map_names[INNER_LRU_HASH_PREALLOC],
					    माप(uपूर्णांक32_t),
					    माप(दीर्घ),
					    inner_lru_hash_size, 0,
					    mynode);
		अगर (inner_lru_map_fds[cpu] == -1) अणु
			म_लिखो("cannot create BPF_MAP_TYPE_LRU_HASH %s(%d)\n",
			       म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
			निकास(1);
		पूर्ण

		ret = bpf_map_update_elem(outer_fd, &cpu,
					  &inner_lru_map_fds[cpu],
					  BPF_ANY);
		अगर (ret) अणु
			म_लिखो("cannot update ARRAY_OF_LRU_HASHS with key:%u. %s(%d)\n",
			       cpu, म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
			निकास(1);
		पूर्ण
	पूर्ण

	in6.sin6_addr.s6_addr16[0] = 0xdead;
	in6.sin6_addr.s6_addr16[1] = 0xbeef;

	अगर (test == LRU_HASH_PREALLOC) अणु
		test_name = "lru_hash_map_perf";
		in6.sin6_addr.s6_addr16[2] = 0;
	पूर्ण अन्यथा अगर (test == NOCOMMON_LRU_HASH_PREALLOC) अणु
		test_name = "nocommon_lru_hash_map_perf";
		in6.sin6_addr.s6_addr16[2] = 1;
	पूर्ण अन्यथा अगर (test == INNER_LRU_HASH_PREALLOC) अणु
		test_name = "inner_lru_hash_map_perf";
		in6.sin6_addr.s6_addr16[2] = 2;
	पूर्ण अन्यथा अगर (test == LRU_HASH_LOOKUP) अणु
		test_name = "lru_hash_lookup_perf";
		in6.sin6_addr.s6_addr16[2] = 3;
		in6.sin6_addr.s6_addr32[3] = 0;
	पूर्ण अन्यथा अणु
		निश्चित(0);
	पूर्ण

	start_समय = समय_get_ns();
	क्रम (i = 0; i < max_cnt; i++) अणु
		ret = connect(-1, (स्थिर काष्ठा sockaddr *)&in6, माप(in6));
		निश्चित(ret == -1 && त्रुटि_सं == EBADF);
		अगर (in6.sin6_addr.s6_addr32[3] <
		    lru_hash_lookup_test_entries - 32)
			in6.sin6_addr.s6_addr32[3] += 32;
		अन्यथा
			in6.sin6_addr.s6_addr32[3] = 0;
	पूर्ण
	म_लिखो("%d:%s pre-alloc %lld events per sec\n",
	       cpu, test_name,
	       max_cnt * 1000000000ll / (समय_get_ns() - start_समय));
पूर्ण

अटल व्योम test_lru_hash_pपुनः_स्मृति(पूर्णांक cpu)
अणु
	करो_test_lru(LRU_HASH_PREALLOC, cpu);
पूर्ण

अटल व्योम test_nocommon_lru_hash_pपुनः_स्मृति(पूर्णांक cpu)
अणु
	करो_test_lru(NOCOMMON_LRU_HASH_PREALLOC, cpu);
पूर्ण

अटल व्योम test_inner_lru_hash_pपुनः_स्मृति(पूर्णांक cpu)
अणु
	करो_test_lru(INNER_LRU_HASH_PREALLOC, cpu);
पूर्ण

अटल व्योम test_lru_hash_lookup(पूर्णांक cpu)
अणु
	करो_test_lru(LRU_HASH_LOOKUP, cpu);
पूर्ण

अटल व्योम test_percpu_hash_pपुनः_स्मृति(पूर्णांक cpu)
अणु
	__u64 start_समय;
	पूर्णांक i;

	start_समय = समय_get_ns();
	क्रम (i = 0; i < max_cnt; i++)
		syscall(__NR_geteuid);
	म_लिखो("%d:percpu_hash_map_perf pre-alloc %lld events per sec\n",
	       cpu, max_cnt * 1000000000ll / (समय_get_ns() - start_समय));
पूर्ण

अटल व्योम test_hash_kदो_स्मृति(पूर्णांक cpu)
अणु
	__u64 start_समय;
	पूर्णांक i;

	start_समय = समय_get_ns();
	क्रम (i = 0; i < max_cnt; i++)
		syscall(__NR_getgid);
	म_लिखो("%d:hash_map_perf kmalloc %lld events per sec\n",
	       cpu, max_cnt * 1000000000ll / (समय_get_ns() - start_समय));
पूर्ण

अटल व्योम test_percpu_hash_kदो_स्मृति(पूर्णांक cpu)
अणु
	__u64 start_समय;
	पूर्णांक i;

	start_समय = समय_get_ns();
	क्रम (i = 0; i < max_cnt; i++)
		syscall(__NR_getegid);
	म_लिखो("%d:percpu_hash_map_perf kmalloc %lld events per sec\n",
	       cpu, max_cnt * 1000000000ll / (समय_get_ns() - start_समय));
पूर्ण

अटल व्योम test_lpm_kदो_स्मृति(पूर्णांक cpu)
अणु
	__u64 start_समय;
	पूर्णांक i;

	start_समय = समय_get_ns();
	क्रम (i = 0; i < max_cnt; i++)
		syscall(__NR_gettid);
	म_लिखो("%d:lpm_perf kmalloc %lld events per sec\n",
	       cpu, max_cnt * 1000000000ll / (समय_get_ns() - start_समय));
पूर्ण

अटल व्योम test_hash_lookup(पूर्णांक cpu)
अणु
	__u64 start_समय;
	पूर्णांक i;

	start_समय = समय_get_ns();
	क्रम (i = 0; i < max_cnt; i++)
		syscall(__NR_getpgid, 0);
	म_लिखो("%d:hash_lookup %lld lookups per sec\n",
	       cpu, max_cnt * 1000000000ll * 64 / (समय_get_ns() - start_समय));
पूर्ण

अटल व्योम test_array_lookup(पूर्णांक cpu)
अणु
	__u64 start_समय;
	पूर्णांक i;

	start_समय = समय_get_ns();
	क्रम (i = 0; i < max_cnt; i++)
		syscall(__NR_getppid, 0);
	म_लिखो("%d:array_lookup %lld lookups per sec\n",
	       cpu, max_cnt * 1000000000ll * 64 / (समय_get_ns() - start_समय));
पूर्ण

प्रकार पूर्णांक (*pre_test_func)(पूर्णांक tasks);
स्थिर pre_test_func pre_test_funcs[] = अणु
	[LRU_HASH_LOOKUP] = pre_test_lru_hash_lookup,
पूर्ण;

प्रकार व्योम (*test_func)(पूर्णांक cpu);
स्थिर test_func test_funcs[] = अणु
	[HASH_PREALLOC] = test_hash_pपुनः_स्मृति,
	[PERCPU_HASH_PREALLOC] = test_percpu_hash_pपुनः_स्मृति,
	[HASH_KMALLOC] = test_hash_kदो_स्मृति,
	[PERCPU_HASH_KMALLOC] = test_percpu_hash_kदो_स्मृति,
	[LRU_HASH_PREALLOC] = test_lru_hash_pपुनः_स्मृति,
	[NOCOMMON_LRU_HASH_PREALLOC] = test_nocommon_lru_hash_pपुनः_स्मृति,
	[LPM_KMALLOC] = test_lpm_kदो_स्मृति,
	[HASH_LOOKUP] = test_hash_lookup,
	[ARRAY_LOOKUP] = test_array_lookup,
	[INNER_LRU_HASH_PREALLOC] = test_inner_lru_hash_pपुनः_स्मृति,
	[LRU_HASH_LOOKUP] = test_lru_hash_lookup,
पूर्ण;

अटल पूर्णांक pre_test(पूर्णांक tasks)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_TESTS; i++) अणु
		अगर (pre_test_funcs[i] && check_test_flags(i)) अणु
			पूर्णांक ret = pre_test_funcs[i](tasks);

			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम loop(पूर्णांक cpu)
अणु
	cpu_set_t cpuset;
	पूर्णांक i;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	sched_setaffinity(0, माप(cpuset), &cpuset);

	क्रम (i = 0; i < NR_TESTS; i++) अणु
		अगर (check_test_flags(i))
			test_funcs[i](cpu);
	पूर्ण
पूर्ण

अटल व्योम run_perf_test(पूर्णांक tasks)
अणु
	pid_t pid[tasks];
	पूर्णांक i;

	निश्चित(!pre_test(tasks));

	क्रम (i = 0; i < tasks; i++) अणु
		pid[i] = विभाजन();
		अगर (pid[i] == 0) अणु
			loop(i);
			निकास(0);
		पूर्ण अन्यथा अगर (pid[i] == -1) अणु
			म_लिखो("couldn't spawn #%d process\n", i);
			निकास(1);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < tasks; i++) अणु
		पूर्णांक status;

		निश्चित(रुकोpid(pid[i], &status, 0) == pid[i]);
		निश्चित(status == 0);
	पूर्ण
पूर्ण

अटल व्योम fill_lpm_trie(व्योम)
अणु
	काष्ठा bpf_lpm_trie_key *key;
	अचिन्हित दीर्घ value = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक r;

	key = alloca(माप(*key) + 4);
	key->prefixlen = 32;

	क्रम (i = 0; i < 512; ++i) अणु
		key->prefixlen = अक्रम() % 33;
		key->data[0] = अक्रम() & 0xff;
		key->data[1] = अक्रम() & 0xff;
		key->data[2] = अक्रम() & 0xff;
		key->data[3] = अक्रम() & 0xff;
		r = bpf_map_update_elem(map_fd[hash_map_alloc_idx],
					key, &value, 0);
		निश्चित(!r);
	पूर्ण

	key->prefixlen = 32;
	key->data[0] = 192;
	key->data[1] = 168;
	key->data[2] = 0;
	key->data[3] = 1;
	value = 128;

	r = bpf_map_update_elem(map_fd[hash_map_alloc_idx], key, &value, 0);
	निश्चित(!r);
पूर्ण

अटल व्योम fixup_map(काष्ठा bpf_object *obj)
अणु
	काष्ठा bpf_map *map;
	पूर्णांक i;

	bpf_object__क्रम_each_map(map, obj) अणु
		स्थिर अक्षर *name = bpf_map__name(map);

		/* Only change the max_entries क्रम the enabled test(s) */
		क्रम (i = 0; i < NR_TESTS; i++) अणु
			अगर (!म_भेद(test_map_names[i], name) &&
			    (check_test_flags(i))) अणु
				bpf_map__resize(map, num_map_entries);
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण

	inner_lru_hash_size = num_map_entries;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक nr_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	काष्ठा bpf_link *links[8];
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	अक्षर filename[256];
	पूर्णांक i = 0;

	अगर (argc > 1)
		test_flags = म_से_प(argv[1]) ? : test_flags;

	अगर (argc > 2)
		nr_cpus = म_से_प(argv[2]) ? : nr_cpus;

	अगर (argc > 3)
		num_map_entries = म_से_प(argv[3]);

	अगर (argc > 4)
		max_cnt = म_से_प(argv[4]);

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	map = bpf_object__find_map_by_name(obj, "inner_lru_hash_map");
	अगर (libbpf_get_error(map)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	inner_lru_hash_size = bpf_map__max_entries(map);
	अगर (!inner_lru_hash_size) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: failed to get map attribute\n");
		जाओ cleanup;
	पूर्ण

	/* resize BPF map prior to loading */
	अगर (num_map_entries > 0)
		fixup_map(obj);

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "array_of_lru_hashs");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "hash_map_alloc");
	map_fd[2] = bpf_object__find_map_fd_by_name(obj, "lru_hash_lookup_map");
	अगर (map_fd[0] < 0 || map_fd[1] < 0 || map_fd[2] < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		links[i] = bpf_program__attach(prog);
		अगर (libbpf_get_error(links[i])) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
			links[i] = शून्य;
			जाओ cleanup;
		पूर्ण
		i++;
	पूर्ण

	fill_lpm_trie();

	run_perf_test(nr_cpus);

cleanup:
	क्रम (i--; i >= 0; i--)
		bpf_link__destroy(links[i]);

	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
