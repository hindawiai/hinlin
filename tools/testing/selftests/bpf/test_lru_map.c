<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Facebook
 */
#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <sched.h>
#समावेश <मानककोष.स>
#समावेश <समय.स>

#समावेश <sys/रुको.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_util.h"
#समावेश "bpf_rlimit.h"
#समावेश "../../../include/linux/filter.h"

#घोषणा LOCAL_FREE_TARGET	(128)
#घोषणा PERCPU_FREE_TARGET	(4)

अटल पूर्णांक nr_cpus;

अटल पूर्णांक create_map(पूर्णांक map_type, पूर्णांक map_flags, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक map_fd;

	map_fd = bpf_create_map(map_type, माप(अचिन्हित दीर्घ दीर्घ),
				माप(अचिन्हित दीर्घ दीर्घ), size, map_flags);

	अगर (map_fd == -1)
		लिखो_त्रुटि("bpf_create_map");

	वापस map_fd;
पूर्ण

अटल पूर्णांक bpf_map_lookup_elem_with_ref_bit(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ key,
					    व्योम *value)
अणु
	काष्ठा bpf_load_program_attr prog;
	काष्ठा bpf_create_map_attr map;
	काष्ठा bpf_insn insns[] = अणु
		BPF_LD_MAP_VALUE(BPF_REG_9, 0, 0),
		BPF_LD_MAP_FD(BPF_REG_1, fd),
		BPF_LD_IMM64(BPF_REG_3, key),
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
		BPF_STX_MEM(BPF_DW, BPF_REG_2, BPF_REG_3, 0),
		BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 4),
		BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_0, 0),
		BPF_STX_MEM(BPF_DW, BPF_REG_9, BPF_REG_1, 0),
		BPF_MOV64_IMM(BPF_REG_0, 42),
		BPF_JMP_IMM(BPF_JA, 0, 0, 1),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण;
	__u8 data[64] = अणुपूर्ण;
	पूर्णांक mfd, pfd, ret, zero = 0;
	__u32 retval = 0;

	स_रखो(&map, 0, माप(map));
	map.map_type = BPF_MAP_TYPE_ARRAY;
	map.key_size = माप(पूर्णांक);
	map.value_size = माप(अचिन्हित दीर्घ दीर्घ);
	map.max_entries = 1;

	mfd = bpf_create_map_xattr(&map);
	अगर (mfd < 0)
		वापस -1;

	insns[0].imm = mfd;

	स_रखो(&prog, 0, माप(prog));
	prog.prog_type = BPF_PROG_TYPE_SCHED_CLS;
	prog.insns = insns;
	prog.insns_cnt = ARRAY_SIZE(insns);
	prog.license = "GPL";

	pfd = bpf_load_program_xattr(&prog, शून्य, 0);
	अगर (pfd < 0) अणु
		बंद(mfd);
		वापस -1;
	पूर्ण

	ret = bpf_prog_test_run(pfd, 1, data, माप(data),
				शून्य, शून्य, &retval, शून्य);
	अगर (ret < 0 || retval != 42) अणु
		ret = -1;
	पूर्ण अन्यथा अणु
		निश्चित(!bpf_map_lookup_elem(mfd, &zero, value));
		ret = 0;
	पूर्ण
	बंद(pfd);
	बंद(mfd);
	वापस ret;
पूर्ण

अटल पूर्णांक map_subset(पूर्णांक map0, पूर्णांक map1)
अणु
	अचिन्हित दीर्घ दीर्घ next_key = 0;
	अचिन्हित दीर्घ दीर्घ value0[nr_cpus], value1[nr_cpus];
	पूर्णांक ret;

	जबतक (!bpf_map_get_next_key(map1, &next_key, &next_key)) अणु
		निश्चित(!bpf_map_lookup_elem(map1, &next_key, value1));
		ret = bpf_map_lookup_elem(map0, &next_key, value0);
		अगर (ret) अणु
			म_लिखो("key:%llu not found from map. %s(%d)\n",
			       next_key, म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
			वापस 0;
		पूर्ण
		अगर (value0[0] != value1[0]) अणु
			म_लिखो("key:%llu value0:%llu != value1:%llu\n",
			       next_key, value0[0], value1[0]);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक map_equal(पूर्णांक lru_map, पूर्णांक expected)
अणु
	वापस map_subset(lru_map, expected) && map_subset(expected, lru_map);
पूर्ण

अटल पूर्णांक sched_next_online(पूर्णांक pid, पूर्णांक *next_to_try)
अणु
	cpu_set_t cpuset;
	पूर्णांक next = *next_to_try;
	पूर्णांक ret = -1;

	जबतक (next < nr_cpus) अणु
		CPU_ZERO(&cpuset);
		CPU_SET(next++, &cpuset);
		अगर (!sched_setaffinity(pid, माप(cpuset), &cpuset)) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	*next_to_try = next;
	वापस ret;
पूर्ण

/* Size of the LRU map is 2
 * Add key=1 (+1 key)
 * Add key=2 (+1 key)
 * Lookup Key=1
 * Add Key=3
 *   => Key=2 will be हटाओd by LRU
 * Iterate map.  Only found key=1 and key=3
 */
अटल व्योम test_lru_sanity0(पूर्णांक map_type, पूर्णांक map_flags)
अणु
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	पूर्णांक lru_map_fd, expected_map_fd;
	पूर्णांक next_cpu = 0;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, &next_cpu) != -1);

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		lru_map_fd = create_map(map_type, map_flags, 2 * nr_cpus);
	अन्यथा
		lru_map_fd = create_map(map_type, map_flags, 2);
	निश्चित(lru_map_fd != -1);

	expected_map_fd = create_map(BPF_MAP_TYPE_HASH, 0, 2);
	निश्चित(expected_map_fd != -1);

	value[0] = 1234;

	/* insert key=1 element */

	key = 1;
	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));
	निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
				    BPF_NOEXIST));

	/* BPF_NOEXIST means: add new element अगर it करोesn't exist */
	निश्चित(bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST) == -1
	       /* key=1 alपढ़ोy exists */
	       && त्रुटि_सं == EEXIST);

	निश्चित(bpf_map_update_elem(lru_map_fd, &key, value, -1) == -1 &&
	       त्रुटि_सं == EINVAL);

	/* insert key=2 element */

	/* check that key=2 is not found */
	key = 2;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* BPF_EXIST means: update existing element */
	निश्चित(bpf_map_update_elem(lru_map_fd, &key, value, BPF_EXIST) == -1 &&
	       /* key=2 is not there */
	       त्रुटि_सं == ENOENT);

	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));

	/* insert key=3 element */

	/* check that key=3 is not found */
	key = 3;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* check that key=1 can be found and mark the ref bit to
	 * stop LRU from removing key=1
	 */
	key = 1;
	निश्चित(!bpf_map_lookup_elem_with_ref_bit(lru_map_fd, key, value));
	निश्चित(value[0] == 1234);

	key = 3;
	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));
	निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
				    BPF_NOEXIST));

	/* key=2 has been हटाओd from the LRU */
	key = 2;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	निश्चित(map_equal(lru_map_fd, expected_map_fd));

	बंद(expected_map_fd);
	बंद(lru_map_fd);

	म_लिखो("Pass\n");
पूर्ण

/* Size of the LRU map is 1.5*tgt_मुक्त
 * Insert 1 to tgt_मुक्त (+tgt_मुक्त keys)
 * Lookup 1 to tgt_मुक्त/2
 * Insert 1+tgt_मुक्त to 2*tgt_मुक्त (+tgt_मुक्त keys)
 * => 1+tgt_मुक्त/2 to LOCALFREE_TARGET will be हटाओd by LRU
 */
अटल व्योम test_lru_sanity1(पूर्णांक map_type, पूर्णांक map_flags, अचिन्हित पूर्णांक tgt_मुक्त)
अणु
	अचिन्हित दीर्घ दीर्घ key, end_key, value[nr_cpus];
	पूर्णांक lru_map_fd, expected_map_fd;
	अचिन्हित पूर्णांक batch_size;
	अचिन्हित पूर्णांक map_size;
	पूर्णांक next_cpu = 0;

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		/* This test is only applicable to common LRU list */
		वापस;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, &next_cpu) != -1);

	batch_size = tgt_मुक्त / 2;
	निश्चित(batch_size * 2 == tgt_मुक्त);

	map_size = tgt_मुक्त + batch_size;
	lru_map_fd = create_map(map_type, map_flags, map_size);
	निश्चित(lru_map_fd != -1);

	expected_map_fd = create_map(BPF_MAP_TYPE_HASH, 0, map_size);
	निश्चित(expected_map_fd != -1);

	value[0] = 1234;

	/* Insert 1 to tgt_मुक्त (+tgt_मुक्त keys) */
	end_key = 1 + tgt_मुक्त;
	क्रम (key = 1; key < end_key; key++)
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));

	/* Lookup 1 to tgt_मुक्त/2 */
	end_key = 1 + batch_size;
	क्रम (key = 1; key < end_key; key++) अणु
		निश्चित(!bpf_map_lookup_elem_with_ref_bit(lru_map_fd, key, value));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	/* Insert 1+tgt_मुक्त to 2*tgt_मुक्त
	 * => 1+tgt_मुक्त/2 to LOCALFREE_TARGET will be
	 * हटाओd by LRU
	 */
	key = 1 + tgt_मुक्त;
	end_key = key + tgt_मुक्त;
	क्रम (; key < end_key; key++) अणु
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	निश्चित(map_equal(lru_map_fd, expected_map_fd));

	बंद(expected_map_fd);
	बंद(lru_map_fd);

	म_लिखो("Pass\n");
पूर्ण

/* Size of the LRU map 1.5 * tgt_मुक्त
 * Insert 1 to tgt_मुक्त (+tgt_मुक्त keys)
 * Update 1 to tgt_मुक्त/2
 *   => The original 1 to tgt_मुक्त/2 will be हटाओd due to
 *      the LRU shrink process
 * Re-insert 1 to tgt_मुक्त/2 again and करो a lookup immeidately
 * Insert 1+tgt_मुक्त to tgt_मुक्त*3/2
 * Insert 1+tgt_मुक्त*3/2 to tgt_मुक्त*5/2
 *   => Key 1+tgt_मुक्त to tgt_मुक्त*3/2
 *      will be हटाओd from LRU because it has never
 *      been lookup and ref bit is not set
 */
अटल व्योम test_lru_sanity2(पूर्णांक map_type, पूर्णांक map_flags, अचिन्हित पूर्णांक tgt_मुक्त)
अणु
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	अचिन्हित दीर्घ दीर्घ end_key;
	पूर्णांक lru_map_fd, expected_map_fd;
	अचिन्हित पूर्णांक batch_size;
	अचिन्हित पूर्णांक map_size;
	पूर्णांक next_cpu = 0;

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		/* This test is only applicable to common LRU list */
		वापस;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, &next_cpu) != -1);

	batch_size = tgt_मुक्त / 2;
	निश्चित(batch_size * 2 == tgt_मुक्त);

	map_size = tgt_मुक्त + batch_size;
	lru_map_fd = create_map(map_type, map_flags, map_size);
	निश्चित(lru_map_fd != -1);

	expected_map_fd = create_map(BPF_MAP_TYPE_HASH, 0, map_size);
	निश्चित(expected_map_fd != -1);

	value[0] = 1234;

	/* Insert 1 to tgt_मुक्त (+tgt_मुक्त keys) */
	end_key = 1 + tgt_मुक्त;
	क्रम (key = 1; key < end_key; key++)
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));

	/* Any bpf_map_update_elem will require to acquire a new node
	 * from LRU first.
	 *
	 * The local list is running out of मुक्त nodes.
	 * It माला_लो from the global LRU list which tries to
	 * shrink the inactive list to get tgt_मुक्त
	 * number of मुक्त nodes.
	 *
	 * Hence, the oldest key 1 to tgt_मुक्त/2
	 * are हटाओd from the LRU list.
	 */
	key = 1;
	अगर (map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH) अणु
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
		निश्चित(!bpf_map_delete_elem(lru_map_fd, &key));
	पूर्ण अन्यथा अणु
		निश्चित(bpf_map_update_elem(lru_map_fd, &key, value,
					   BPF_EXIST));
	पूर्ण

	/* Re-insert 1 to tgt_मुक्त/2 again and करो a lookup
	 * immeidately.
	 */
	end_key = 1 + batch_size;
	value[0] = 4321;
	क्रम (key = 1; key < end_key; key++) अणु
		निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
		       त्रुटि_सं == ENOENT);
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
		निश्चित(!bpf_map_lookup_elem_with_ref_bit(lru_map_fd, key, value));
		निश्चित(value[0] == 4321);
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	value[0] = 1234;

	/* Insert 1+tgt_मुक्त to tgt_मुक्त*3/2 */
	end_key = 1 + tgt_मुक्त + batch_size;
	क्रम (key = 1 + tgt_मुक्त; key < end_key; key++)
		/* These newly added but not referenced keys will be
		 * gone during the next LRU shrink.
		 */
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));

	/* Insert 1+tgt_मुक्त*3/2 to  tgt_मुक्त*5/2 */
	end_key = key + tgt_मुक्त;
	क्रम (; key < end_key; key++) अणु
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	निश्चित(map_equal(lru_map_fd, expected_map_fd));

	बंद(expected_map_fd);
	बंद(lru_map_fd);

	म_लिखो("Pass\n");
पूर्ण

/* Size of the LRU map is 2*tgt_मुक्त
 * It is to test the active/inactive list rotation
 * Insert 1 to 2*tgt_मुक्त (+2*tgt_मुक्त keys)
 * Lookup key 1 to tgt_मुक्त*3/2
 * Add 1+2*tgt_मुक्त to tgt_मुक्त*5/2 (+tgt_मुक्त/2 keys)
 *  => key 1+tgt_मुक्त*3/2 to 2*tgt_मुक्त are हटाओd from LRU
 */
अटल व्योम test_lru_sanity3(पूर्णांक map_type, पूर्णांक map_flags, अचिन्हित पूर्णांक tgt_मुक्त)
अणु
	अचिन्हित दीर्घ दीर्घ key, end_key, value[nr_cpus];
	पूर्णांक lru_map_fd, expected_map_fd;
	अचिन्हित पूर्णांक batch_size;
	अचिन्हित पूर्णांक map_size;
	पूर्णांक next_cpu = 0;

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		/* This test is only applicable to common LRU list */
		वापस;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, &next_cpu) != -1);

	batch_size = tgt_मुक्त / 2;
	निश्चित(batch_size * 2 == tgt_मुक्त);

	map_size = tgt_मुक्त * 2;
	lru_map_fd = create_map(map_type, map_flags, map_size);
	निश्चित(lru_map_fd != -1);

	expected_map_fd = create_map(BPF_MAP_TYPE_HASH, 0, map_size);
	निश्चित(expected_map_fd != -1);

	value[0] = 1234;

	/* Insert 1 to 2*tgt_मुक्त (+2*tgt_मुक्त keys) */
	end_key = 1 + (2 * tgt_मुक्त);
	क्रम (key = 1; key < end_key; key++)
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));

	/* Lookup key 1 to tgt_मुक्त*3/2 */
	end_key = tgt_मुक्त + batch_size;
	क्रम (key = 1; key < end_key; key++) अणु
		निश्चित(!bpf_map_lookup_elem_with_ref_bit(lru_map_fd, key, value));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	/* Add 1+2*tgt_मुक्त to tgt_मुक्त*5/2
	 * (+tgt_मुक्त/2 keys)
	 */
	key = 2 * tgt_मुक्त + 1;
	end_key = key + batch_size;
	क्रम (; key < end_key; key++) अणु
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	निश्चित(map_equal(lru_map_fd, expected_map_fd));

	बंद(expected_map_fd);
	बंद(lru_map_fd);

	म_लिखो("Pass\n");
पूर्ण

/* Test deletion */
अटल व्योम test_lru_sanity4(पूर्णांक map_type, पूर्णांक map_flags, अचिन्हित पूर्णांक tgt_मुक्त)
अणु
	पूर्णांक lru_map_fd, expected_map_fd;
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	अचिन्हित दीर्घ दीर्घ end_key;
	पूर्णांक next_cpu = 0;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, &next_cpu) != -1);

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		lru_map_fd = create_map(map_type, map_flags,
					3 * tgt_मुक्त * nr_cpus);
	अन्यथा
		lru_map_fd = create_map(map_type, map_flags, 3 * tgt_मुक्त);
	निश्चित(lru_map_fd != -1);

	expected_map_fd = create_map(BPF_MAP_TYPE_HASH, 0,
				     3 * tgt_मुक्त);
	निश्चित(expected_map_fd != -1);

	value[0] = 1234;

	क्रम (key = 1; key <= 2 * tgt_मुक्त; key++)
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));

	key = 1;
	निश्चित(bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));

	क्रम (key = 1; key <= tgt_मुक्त; key++) अणु
		निश्चित(!bpf_map_lookup_elem_with_ref_bit(lru_map_fd, key, value));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	क्रम (; key <= 2 * tgt_मुक्त; key++) अणु
		निश्चित(!bpf_map_delete_elem(lru_map_fd, &key));
		निश्चित(bpf_map_delete_elem(lru_map_fd, &key));
	पूर्ण

	end_key = key + 2 * tgt_मुक्त;
	क्रम (; key < end_key; key++) अणु
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	निश्चित(map_equal(lru_map_fd, expected_map_fd));

	बंद(expected_map_fd);
	बंद(lru_map_fd);

	म_लिखो("Pass\n");
पूर्ण

अटल व्योम करो_test_lru_sanity5(अचिन्हित दीर्घ दीर्घ last_key, पूर्णांक map_fd)
अणु
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];

	/* Ensure the last key inserted by previous CPU can be found */
	निश्चित(!bpf_map_lookup_elem_with_ref_bit(map_fd, last_key, value));
	value[0] = 1234;

	key = last_key + 1;
	निश्चित(!bpf_map_update_elem(map_fd, &key, value, BPF_NOEXIST));
	निश्चित(!bpf_map_lookup_elem_with_ref_bit(map_fd, key, value));

	/* Cannot find the last key because it was हटाओd by LRU */
	निश्चित(bpf_map_lookup_elem(map_fd, &last_key, value) == -1 &&
	       त्रुटि_सं == ENOENT);
पूर्ण

/* Test map with only one element */
अटल व्योम test_lru_sanity5(पूर्णांक map_type, पूर्णांक map_flags)
अणु
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	पूर्णांक next_cpu = 0;
	पूर्णांक map_fd;

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		वापस;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	map_fd = create_map(map_type, map_flags, 1);
	निश्चित(map_fd != -1);

	value[0] = 1234;
	key = 0;
	निश्चित(!bpf_map_update_elem(map_fd, &key, value, BPF_NOEXIST));

	जबतक (sched_next_online(0, &next_cpu) != -1) अणु
		pid_t pid;

		pid = विभाजन();
		अगर (pid == 0) अणु
			करो_test_lru_sanity5(key, map_fd);
			निकास(0);
		पूर्ण अन्यथा अगर (pid == -1) अणु
			म_लिखो("couldn't spawn process to test key:%llu\n",
			       key);
			निकास(1);
		पूर्ण अन्यथा अणु
			पूर्णांक status;

			निश्चित(रुकोpid(pid, &status, 0) == pid);
			निश्चित(status == 0);
			key++;
		पूर्ण
	पूर्ण

	बंद(map_fd);
	/* At least one key should be tested */
	निश्चित(key > 0);

	म_लिखो("Pass\n");
पूर्ण

/* Test list rotation क्रम BPF_F_NO_COMMON_LRU map */
अटल व्योम test_lru_sanity6(पूर्णांक map_type, पूर्णांक map_flags, पूर्णांक tgt_मुक्त)
अणु
	पूर्णांक lru_map_fd, expected_map_fd;
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	अचिन्हित पूर्णांक map_size = tgt_मुक्त * 2;
	पूर्णांक next_cpu = 0;

	अगर (!(map_flags & BPF_F_NO_COMMON_LRU))
		वापस;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, &next_cpu) != -1);

	expected_map_fd = create_map(BPF_MAP_TYPE_HASH, 0, map_size);
	निश्चित(expected_map_fd != -1);

	lru_map_fd = create_map(map_type, map_flags, map_size * nr_cpus);
	निश्चित(lru_map_fd != -1);

	value[0] = 1234;

	क्रम (key = 1; key <= tgt_मुक्त; key++) अणु
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	क्रम (; key <= tgt_मुक्त * 2; key++) अणु
		अचिन्हित दीर्घ दीर्घ stable_key;

		/* Make ref bit sticky क्रम key: [1, tgt_मुक्त] */
		क्रम (stable_key = 1; stable_key <= tgt_मुक्त; stable_key++) अणु
			/* Mark the ref bit */
			निश्चित(!bpf_map_lookup_elem_with_ref_bit(lru_map_fd,
								 stable_key, value));
		पूर्ण
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	क्रम (; key <= tgt_मुक्त * 3; key++) अणु
		निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value,
					    BPF_NOEXIST));
		निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
					    BPF_NOEXIST));
	पूर्ण

	निश्चित(map_equal(lru_map_fd, expected_map_fd));

	बंद(expected_map_fd);
	बंद(lru_map_fd);

	म_लिखो("Pass\n");
पूर्ण

/* Size of the LRU map is 2
 * Add key=1 (+1 key)
 * Add key=2 (+1 key)
 * Lookup Key=1 (datapath)
 * Lookup Key=2 (syscall)
 * Add Key=3
 *   => Key=2 will be हटाओd by LRU
 * Iterate map.  Only found key=1 and key=3
 */
अटल व्योम test_lru_sanity7(पूर्णांक map_type, पूर्णांक map_flags)
अणु
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	पूर्णांक lru_map_fd, expected_map_fd;
	पूर्णांक next_cpu = 0;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, &next_cpu) != -1);

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		lru_map_fd = create_map(map_type, map_flags, 2 * nr_cpus);
	अन्यथा
		lru_map_fd = create_map(map_type, map_flags, 2);
	निश्चित(lru_map_fd != -1);

	expected_map_fd = create_map(BPF_MAP_TYPE_HASH, 0, 2);
	निश्चित(expected_map_fd != -1);

	value[0] = 1234;

	/* insert key=1 element */

	key = 1;
	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));
	निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
				    BPF_NOEXIST));

	/* BPF_NOEXIST means: add new element अगर it करोesn't exist */
	निश्चित(bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST) == -1
	       /* key=1 alपढ़ोy exists */
	       && त्रुटि_सं == EEXIST);

	/* insert key=2 element */

	/* check that key=2 is not found */
	key = 2;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* BPF_EXIST means: update existing element */
	निश्चित(bpf_map_update_elem(lru_map_fd, &key, value, BPF_EXIST) == -1 &&
	       /* key=2 is not there */
	       त्रुटि_सं == ENOENT);

	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));

	/* insert key=3 element */

	/* check that key=3 is not found */
	key = 3;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* check that key=1 can be found and mark the ref bit to
	 * stop LRU from removing key=1
	 */
	key = 1;
	निश्चित(!bpf_map_lookup_elem_with_ref_bit(lru_map_fd, key, value));
	निश्चित(value[0] == 1234);

	/* check that key=2 can be found and करो _not_ mark ref bit.
	 * this will be evicted on next update.
	 */
	key = 2;
	निश्चित(!bpf_map_lookup_elem(lru_map_fd, &key, value));
	निश्चित(value[0] == 1234);

	key = 3;
	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));
	निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
				    BPF_NOEXIST));

	/* key=2 has been हटाओd from the LRU */
	key = 2;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	निश्चित(map_equal(lru_map_fd, expected_map_fd));

	बंद(expected_map_fd);
	बंद(lru_map_fd);

	म_लिखो("Pass\n");
पूर्ण

/* Size of the LRU map is 2
 * Add key=1 (+1 key)
 * Add key=2 (+1 key)
 * Lookup Key=1 (syscall)
 * Lookup Key=2 (datapath)
 * Add Key=3
 *   => Key=1 will be हटाओd by LRU
 * Iterate map.  Only found key=2 and key=3
 */
अटल व्योम test_lru_sanity8(पूर्णांक map_type, पूर्णांक map_flags)
अणु
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	पूर्णांक lru_map_fd, expected_map_fd;
	पूर्णांक next_cpu = 0;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, &next_cpu) != -1);

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		lru_map_fd = create_map(map_type, map_flags, 2 * nr_cpus);
	अन्यथा
		lru_map_fd = create_map(map_type, map_flags, 2);
	निश्चित(lru_map_fd != -1);

	expected_map_fd = create_map(BPF_MAP_TYPE_HASH, 0, 2);
	निश्चित(expected_map_fd != -1);

	value[0] = 1234;

	/* insert key=1 element */

	key = 1;
	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));

	/* BPF_NOEXIST means: add new element अगर it करोesn't exist */
	निश्चित(bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST) == -1
	       /* key=1 alपढ़ोy exists */
	       && त्रुटि_सं == EEXIST);

	/* insert key=2 element */

	/* check that key=2 is not found */
	key = 2;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* BPF_EXIST means: update existing element */
	निश्चित(bpf_map_update_elem(lru_map_fd, &key, value, BPF_EXIST) == -1 &&
	       /* key=2 is not there */
	       त्रुटि_सं == ENOENT);

	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));
	निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
				    BPF_NOEXIST));

	/* insert key=3 element */

	/* check that key=3 is not found */
	key = 3;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* check that key=1 can be found and करो _not_ mark ref bit.
	 * this will be evicted on next update.
	 */
	key = 1;
	निश्चित(!bpf_map_lookup_elem(lru_map_fd, &key, value));
	निश्चित(value[0] == 1234);

	/* check that key=2 can be found and mark the ref bit to
	 * stop LRU from removing key=2
	 */
	key = 2;
	निश्चित(!bpf_map_lookup_elem_with_ref_bit(lru_map_fd, key, value));
	निश्चित(value[0] == 1234);

	key = 3;
	निश्चित(!bpf_map_update_elem(lru_map_fd, &key, value, BPF_NOEXIST));
	निश्चित(!bpf_map_update_elem(expected_map_fd, &key, value,
				    BPF_NOEXIST));

	/* key=1 has been हटाओd from the LRU */
	key = 1;
	निश्चित(bpf_map_lookup_elem(lru_map_fd, &key, value) == -1 &&
	       त्रुटि_सं == ENOENT);

	निश्चित(map_equal(lru_map_fd, expected_map_fd));

	बंद(expected_map_fd);
	बंद(lru_map_fd);

	म_लिखो("Pass\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक map_types[] = अणुBPF_MAP_TYPE_LRU_HASH,
			     BPF_MAP_TYPE_LRU_PERCPU_HASHपूर्ण;
	पूर्णांक map_flags[] = अणु0, BPF_F_NO_COMMON_LRUपूर्ण;
	पूर्णांक t, f;

	रखो_बफ(मानक_निकास, शून्य);

	nr_cpus = bpf_num_possible_cpus();
	निश्चित(nr_cpus != -1);
	म_लिखो("nr_cpus:%d\n\n", nr_cpus);

	क्रम (f = 0; f < माप(map_flags) / माप(*map_flags); f++) अणु
		अचिन्हित पूर्णांक tgt_मुक्त = (map_flags[f] & BPF_F_NO_COMMON_LRU) ?
			PERCPU_FREE_TARGET : LOCAL_FREE_TARGET;

		क्रम (t = 0; t < माप(map_types) / माप(*map_types); t++) अणु
			test_lru_sanity0(map_types[t], map_flags[f]);
			test_lru_sanity1(map_types[t], map_flags[f], tgt_मुक्त);
			test_lru_sanity2(map_types[t], map_flags[f], tgt_मुक्त);
			test_lru_sanity3(map_types[t], map_flags[f], tgt_मुक्त);
			test_lru_sanity4(map_types[t], map_flags[f], tgt_मुक्त);
			test_lru_sanity5(map_types[t], map_flags[f]);
			test_lru_sanity6(map_types[t], map_flags[f], tgt_मुक्त);
			test_lru_sanity7(map_types[t], map_flags[f]);
			test_lru_sanity8(map_types[t], map_flags[f]);

			म_लिखो("\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
