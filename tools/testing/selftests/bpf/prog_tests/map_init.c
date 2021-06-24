<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Tessares SA <http://www.tessares.net> */

#समावेश <test_progs.h>
#समावेश "test_map_init.skel.h"

#घोषणा TEST_VALUE 0x1234
#घोषणा FILL_VALUE 0xdeadbeef

अटल पूर्णांक nr_cpus;
अटल पूर्णांक duration;

प्रकार अचिन्हित दीर्घ दीर्घ map_key_t;
प्रकार अचिन्हित दीर्घ दीर्घ map_value_t;
प्रकार काष्ठा अणु
	map_value_t v; /* padding */
पूर्ण __bpf_percpu_val_align pcpu_map_value_t;


अटल पूर्णांक map_populate(पूर्णांक map_fd, पूर्णांक num)
अणु
	pcpu_map_value_t value[nr_cpus];
	पूर्णांक i, err;
	map_key_t key;

	क्रम (i = 0; i < nr_cpus; i++)
		bpf_percpu(value, i) = FILL_VALUE;

	क्रम (key = 1; key <= num; key++) अणु
		err = bpf_map_update_elem(map_fd, &key, value, BPF_NOEXIST);
		अगर (!ASSERT_OK(err, "bpf_map_update_elem"))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा test_map_init *setup(क्रमागत bpf_map_type map_type, पूर्णांक map_sz,
			    पूर्णांक *map_fd, पूर्णांक populate)
अणु
	काष्ठा test_map_init *skel;
	पूर्णांक err;

	skel = test_map_init__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस शून्य;

	err = bpf_map__set_type(skel->maps.hashmap1, map_type);
	अगर (!ASSERT_OK(err, "bpf_map__set_type"))
		जाओ error;

	err = bpf_map__set_max_entries(skel->maps.hashmap1, map_sz);
	अगर (!ASSERT_OK(err, "bpf_map__set_max_entries"))
		जाओ error;

	err = test_map_init__load(skel);
	अगर (!ASSERT_OK(err, "skel_load"))
		जाओ error;

	*map_fd = bpf_map__fd(skel->maps.hashmap1);
	अगर (CHECK(*map_fd < 0, "bpf_map__fd", "failed\n"))
		जाओ error;

	err = map_populate(*map_fd, populate);
	अगर (!ASSERT_OK(err, "map_populate"))
		जाओ error_map;

	वापस skel;

error_map:
	बंद(*map_fd);
error:
	test_map_init__destroy(skel);
	वापस शून्य;
पूर्ण

/* executes bpf program that updates map with key, value */
अटल पूर्णांक prog_run_insert_elem(काष्ठा test_map_init *skel, map_key_t key,
				map_value_t value)
अणु
	काष्ठा test_map_init__bss *bss;

	bss = skel->bss;

	bss->inKey = key;
	bss->inValue = value;
	bss->inPid = getpid();

	अगर (!ASSERT_OK(test_map_init__attach(skel), "skel_attach"))
		वापस -1;

	/* Let tracepoपूर्णांक trigger */
	syscall(__NR_getpgid);

	test_map_init__detach(skel);

	वापस 0;
पूर्ण

अटल पूर्णांक check_values_one_cpu(pcpu_map_value_t *value, map_value_t expected)
अणु
	पूर्णांक i, nzCnt = 0;
	map_value_t val;

	क्रम (i = 0; i < nr_cpus; i++) अणु
		val = bpf_percpu(value, i);
		अगर (val) अणु
			अगर (CHECK(val != expected, "map value",
				  "unexpected for cpu %d: 0x%llx\n", i, val))
				वापस -1;
			nzCnt++;
		पूर्ण
	पूर्ण

	अगर (CHECK(nzCnt != 1, "map value", "set for %d CPUs instead of 1!\n",
		  nzCnt))
		वापस -1;

	वापस 0;
पूर्ण

/* Add key=1 elem with values set क्रम all CPUs
 * Delete elem key=1
 * Run bpf prog that inserts new key=1 elem with value=0x1234
 *   (bpf prog can only set value क्रम current CPU)
 * Lookup Key=1 and check value is as expected क्रम all CPUs:
 *   value set by bpf prog क्रम one CPU, 0 क्रम all others
 */
अटल व्योम test_pcpu_map_init(व्योम)
अणु
	pcpu_map_value_t value[nr_cpus];
	काष्ठा test_map_init *skel;
	पूर्णांक map_fd, err;
	map_key_t key;

	/* max 1 elem in map so insertion is क्रमced to reuse मुक्तd entry */
	skel = setup(BPF_MAP_TYPE_PERCPU_HASH, 1, &map_fd, 1);
	अगर (!ASSERT_OK_PTR(skel, "prog_setup"))
		वापस;

	/* delete element so the entry can be re-used*/
	key = 1;
	err = bpf_map_delete_elem(map_fd, &key);
	अगर (!ASSERT_OK(err, "bpf_map_delete_elem"))
		जाओ cleanup;

	/* run bpf prog that inserts new elem, re-using the slot just मुक्तd */
	err = prog_run_insert_elem(skel, key, TEST_VALUE);
	अगर (!ASSERT_OK(err, "prog_run_insert_elem"))
		जाओ cleanup;

	/* check that key=1 was re-created by bpf prog */
	err = bpf_map_lookup_elem(map_fd, &key, value);
	अगर (!ASSERT_OK(err, "bpf_map_lookup_elem"))
		जाओ cleanup;

	/* and has expected values */
	check_values_one_cpu(value, TEST_VALUE);

cleanup:
	test_map_init__destroy(skel);
पूर्ण

/* Add key=1 and key=2 elems with values set क्रम all CPUs
 * Run bpf prog that inserts new key=3 elem
 *   (only क्रम current cpu; other cpus should have initial value = 0)
 * Lookup Key=1 and check value is as expected क्रम all CPUs
 */
अटल व्योम test_pcpu_lru_map_init(व्योम)
अणु
	pcpu_map_value_t value[nr_cpus];
	काष्ठा test_map_init *skel;
	पूर्णांक map_fd, err;
	map_key_t key;

	/* Set up LRU map with 2 elements, values filled क्रम all CPUs.
	 * With these 2 elements, the LRU map is full
	 */
	skel = setup(BPF_MAP_TYPE_LRU_PERCPU_HASH, 2, &map_fd, 2);
	अगर (!ASSERT_OK_PTR(skel, "prog_setup"))
		वापस;

	/* run bpf prog that inserts new key=3 element, re-using LRU slot */
	key = 3;
	err = prog_run_insert_elem(skel, key, TEST_VALUE);
	अगर (!ASSERT_OK(err, "prog_run_insert_elem"))
		जाओ cleanup;

	/* check that key=3 replaced one of earlier elements */
	err = bpf_map_lookup_elem(map_fd, &key, value);
	अगर (!ASSERT_OK(err, "bpf_map_lookup_elem"))
		जाओ cleanup;

	/* and has expected values */
	check_values_one_cpu(value, TEST_VALUE);

cleanup:
	test_map_init__destroy(skel);
पूर्ण

व्योम test_map_init(व्योम)
अणु
	nr_cpus = bpf_num_possible_cpus();
	अगर (nr_cpus <= 1) अणु
		म_लिखो("%s:SKIP: >1 cpu needed for this test\n", __func__);
		test__skip();
		वापस;
	पूर्ण

	अगर (test__start_subtest("pcpu_map_init"))
		test_pcpu_map_init();
	अगर (test__start_subtest("pcpu_lru_map_init"))
		test_pcpu_lru_map_init();
पूर्ण
