<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Testsuite क्रम eBPF maps
 *
 * Copyright (c) 2014 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2016 Facebook
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>

#समावेश <sys/रुको.h>
#समावेश <sys/socket.h>
#समावेश <netinet/in.h>
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_util.h"
#समावेश "bpf_rlimit.h"
#समावेश "test_maps.h"

#अगर_अघोषित ENOTSUPP
#घोषणा ENOTSUPP 524
#पूर्ण_अगर

अटल पूर्णांक skips;

अटल पूर्णांक map_flags;

अटल व्योम test_hashmap(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	दीर्घ दीर्घ key, next_key, first_key, value;
	पूर्णांक fd;

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, माप(key), माप(value),
			    2, map_flags);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create hashmap '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	key = 1;
	value = 1234;
	/* Insert key=1 element. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == 0);

	value = 0;
	/* BPF_NOEXIST means add new element अगर it करोesn't exist. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       /* key=1 alपढ़ोy exists. */
	       त्रुटि_सं == EEXIST);

	/* -1 is an invalid flag. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, -1) == -1 &&
	       त्रुटि_सं == EINVAL);

	/* Check that key=1 can be found. */
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == 0 && value == 1234);

	key = 2;
	/* Check that key=2 is not found. */
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == -1 && त्रुटि_सं == ENOENT);

	/* BPF_EXIST means update existing element. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_EXIST) == -1 &&
	       /* key=2 is not there. */
	       त्रुटि_सं == ENOENT);

	/* Insert key=2 element. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == 0);

	/* key=1 and key=2 were inserted, check that key=0 cannot be
	 * inserted due to max_entries limit.
	 */
	key = 0;
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       त्रुटि_सं == E2BIG);

	/* Update existing element, though the map is full. */
	key = 1;
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_EXIST) == 0);
	key = 2;
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == 0);
	key = 3;
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       त्रुटि_सं == E2BIG);

	/* Check that key = 0 करोesn't exist. */
	key = 0;
	निश्चित(bpf_map_delete_elem(fd, &key) == -1 && त्रुटि_सं == ENOENT);

	/* Iterate over two elements. */
	निश्चित(bpf_map_get_next_key(fd, शून्य, &first_key) == 0 &&
	       (first_key == 1 || first_key == 2));
	निश्चित(bpf_map_get_next_key(fd, &key, &next_key) == 0 &&
	       (next_key == first_key));
	निश्चित(bpf_map_get_next_key(fd, &next_key, &next_key) == 0 &&
	       (next_key == 1 || next_key == 2) &&
	       (next_key != first_key));
	निश्चित(bpf_map_get_next_key(fd, &next_key, &next_key) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* Delete both elements. */
	key = 1;
	निश्चित(bpf_map_delete_elem(fd, &key) == 0);
	key = 2;
	निश्चित(bpf_map_delete_elem(fd, &key) == 0);
	निश्चित(bpf_map_delete_elem(fd, &key) == -1 && त्रुटि_सं == ENOENT);

	key = 0;
	/* Check that map is empty. */
	निश्चित(bpf_map_get_next_key(fd, शून्य, &next_key) == -1 &&
	       त्रुटि_सं == ENOENT);
	निश्चित(bpf_map_get_next_key(fd, &key, &next_key) == -1 &&
	       त्रुटि_सं == ENOENT);

	बंद(fd);
पूर्ण

अटल व्योम test_hashmap_sizes(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	पूर्णांक fd, i, j;

	क्रम (i = 1; i <= 512; i <<= 1)
		क्रम (j = 1; j <= 1 << 18; j <<= 1) अणु
			fd = bpf_create_map(BPF_MAP_TYPE_HASH, i, j,
					    2, map_flags);
			अगर (fd < 0) अणु
				अगर (त्रुटि_सं == ENOMEM)
					वापस;
				म_लिखो("Failed to create hashmap key=%d value=%d '%s'\n",
				       i, j, म_त्रुटि(त्रुटि_सं));
				निकास(1);
			पूर्ण
			बंद(fd);
			usleep(10); /* give kernel समय to destroy */
		पूर्ण
पूर्ण

अटल व्योम test_hashmap_percpu(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	BPF_DECLARE_PERCPU(दीर्घ, value);
	दीर्घ दीर्घ key, next_key, first_key;
	पूर्णांक expected_key_mask = 0;
	पूर्णांक fd, i;

	fd = bpf_create_map(BPF_MAP_TYPE_PERCPU_HASH, माप(key),
			    माप(bpf_percpu(value, 0)), 2, map_flags);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create hashmap '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	क्रम (i = 0; i < nr_cpus; i++)
		bpf_percpu(value, i) = i + 100;

	key = 1;
	/* Insert key=1 element. */
	निश्चित(!(expected_key_mask & key));
	निश्चित(bpf_map_update_elem(fd, &key, value, BPF_ANY) == 0);
	expected_key_mask |= key;

	/* BPF_NOEXIST means add new element अगर it करोesn't exist. */
	निश्चित(bpf_map_update_elem(fd, &key, value, BPF_NOEXIST) == -1 &&
	       /* key=1 alपढ़ोy exists. */
	       त्रुटि_सं == EEXIST);

	/* -1 is an invalid flag. */
	निश्चित(bpf_map_update_elem(fd, &key, value, -1) == -1 &&
	       त्रुटि_सं == EINVAL);

	/* Check that key=1 can be found. Value could be 0 अगर the lookup
	 * was run from a dअगरferent CPU.
	 */
	bpf_percpu(value, 0) = 1;
	निश्चित(bpf_map_lookup_elem(fd, &key, value) == 0 &&
	       bpf_percpu(value, 0) == 100);

	key = 2;
	/* Check that key=2 is not found. */
	निश्चित(bpf_map_lookup_elem(fd, &key, value) == -1 && त्रुटि_सं == ENOENT);

	/* BPF_EXIST means update existing element. */
	निश्चित(bpf_map_update_elem(fd, &key, value, BPF_EXIST) == -1 &&
	       /* key=2 is not there. */
	       त्रुटि_सं == ENOENT);

	/* Insert key=2 element. */
	निश्चित(!(expected_key_mask & key));
	निश्चित(bpf_map_update_elem(fd, &key, value, BPF_NOEXIST) == 0);
	expected_key_mask |= key;

	/* key=1 and key=2 were inserted, check that key=0 cannot be
	 * inserted due to max_entries limit.
	 */
	key = 0;
	निश्चित(bpf_map_update_elem(fd, &key, value, BPF_NOEXIST) == -1 &&
	       त्रुटि_सं == E2BIG);

	/* Check that key = 0 करोesn't exist. */
	निश्चित(bpf_map_delete_elem(fd, &key) == -1 && त्रुटि_सं == ENOENT);

	/* Iterate over two elements. */
	निश्चित(bpf_map_get_next_key(fd, शून्य, &first_key) == 0 &&
	       ((expected_key_mask & first_key) == first_key));
	जबतक (!bpf_map_get_next_key(fd, &key, &next_key)) अणु
		अगर (first_key) अणु
			निश्चित(next_key == first_key);
			first_key = 0;
		पूर्ण
		निश्चित((expected_key_mask & next_key) == next_key);
		expected_key_mask &= ~next_key;

		निश्चित(bpf_map_lookup_elem(fd, &next_key, value) == 0);

		क्रम (i = 0; i < nr_cpus; i++)
			निश्चित(bpf_percpu(value, i) == i + 100);

		key = next_key;
	पूर्ण
	निश्चित(त्रुटि_सं == ENOENT);

	/* Update with BPF_EXIST. */
	key = 1;
	निश्चित(bpf_map_update_elem(fd, &key, value, BPF_EXIST) == 0);

	/* Delete both elements. */
	key = 1;
	निश्चित(bpf_map_delete_elem(fd, &key) == 0);
	key = 2;
	निश्चित(bpf_map_delete_elem(fd, &key) == 0);
	निश्चित(bpf_map_delete_elem(fd, &key) == -1 && त्रुटि_सं == ENOENT);

	key = 0;
	/* Check that map is empty. */
	निश्चित(bpf_map_get_next_key(fd, शून्य, &next_key) == -1 &&
	       त्रुटि_सं == ENOENT);
	निश्चित(bpf_map_get_next_key(fd, &key, &next_key) == -1 &&
	       त्रुटि_सं == ENOENT);

	बंद(fd);
पूर्ण

अटल पूर्णांक helper_fill_hashmap(पूर्णांक max_entries)
अणु
	पूर्णांक i, fd, ret;
	दीर्घ दीर्घ key, value;

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, माप(key), माप(value),
			    max_entries, map_flags);
	CHECK(fd < 0,
	      "failed to create hashmap",
	      "err: %s, flags: 0x%x\n", म_त्रुटि(त्रुटि_सं), map_flags);

	क्रम (i = 0; i < max_entries; i++) अणु
		key = i; value = key;
		ret = bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST);
		CHECK(ret != 0,
		      "can't update hashmap",
		      "err: %s\n", म_त्रुटि(ret));
	पूर्ण

	वापस fd;
पूर्ण

अटल व्योम test_hashmap_walk(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	पूर्णांक fd, i, max_entries = 1000;
	दीर्घ दीर्घ key, value, next_key;
	bool next_key_valid = true;

	fd = helper_fill_hashmap(max_entries);

	क्रम (i = 0; bpf_map_get_next_key(fd, !i ? शून्य : &key,
					 &next_key) == 0; i++) अणु
		key = next_key;
		निश्चित(bpf_map_lookup_elem(fd, &key, &value) == 0);
	पूर्ण

	निश्चित(i == max_entries);

	निश्चित(bpf_map_get_next_key(fd, शून्य, &key) == 0);
	क्रम (i = 0; next_key_valid; i++) अणु
		next_key_valid = bpf_map_get_next_key(fd, &key, &next_key) == 0;
		निश्चित(bpf_map_lookup_elem(fd, &key, &value) == 0);
		value++;
		निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_EXIST) == 0);
		key = next_key;
	पूर्ण

	निश्चित(i == max_entries);

	क्रम (i = 0; bpf_map_get_next_key(fd, !i ? शून्य : &key,
					 &next_key) == 0; i++) अणु
		key = next_key;
		निश्चित(bpf_map_lookup_elem(fd, &key, &value) == 0);
		निश्चित(value - 1 == key);
	पूर्ण

	निश्चित(i == max_entries);
	बंद(fd);
पूर्ण

अटल व्योम test_hashmap_zero_seed(व्योम)
अणु
	पूर्णांक i, first, second, old_flags;
	दीर्घ दीर्घ key, next_first, next_second;

	old_flags = map_flags;
	map_flags |= BPF_F_ZERO_SEED;

	first = helper_fill_hashmap(3);
	second = helper_fill_hashmap(3);

	क्रम (i = 0; ; i++) अणु
		व्योम *key_ptr = !i ? शून्य : &key;

		अगर (bpf_map_get_next_key(first, key_ptr, &next_first) != 0)
			अवरोध;

		CHECK(bpf_map_get_next_key(second, key_ptr, &next_second) != 0,
		      "next_key for second map must succeed",
		      "key_ptr: %p", key_ptr);
		CHECK(next_first != next_second,
		      "keys must match",
		      "i: %d first: %lld second: %lld\n", i,
		      next_first, next_second);

		key = next_first;
	पूर्ण

	map_flags = old_flags;
	बंद(first);
	बंद(second);
पूर्ण

अटल व्योम test_arraymap(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	पूर्णांक key, next_key, fd;
	दीर्घ दीर्घ value;

	fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, माप(key), माप(value),
			    2, 0);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create arraymap '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	key = 1;
	value = 1234;
	/* Insert key=1 element. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == 0);

	value = 0;
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       त्रुटि_सं == EEXIST);

	/* Check that key=1 can be found. */
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == 0 && value == 1234);

	key = 0;
	/* Check that key=0 is also found and zero initialized. */
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == 0 && value == 0);

	/* key=0 and key=1 were inserted, check that key=2 cannot be inserted
	 * due to max_entries limit.
	 */
	key = 2;
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_EXIST) == -1 &&
	       त्रुटि_सं == E2BIG);

	/* Check that key = 2 करोesn't exist. */
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == -1 && त्रुटि_सं == ENOENT);

	/* Iterate over two elements. */
	निश्चित(bpf_map_get_next_key(fd, शून्य, &next_key) == 0 &&
	       next_key == 0);
	निश्चित(bpf_map_get_next_key(fd, &key, &next_key) == 0 &&
	       next_key == 0);
	निश्चित(bpf_map_get_next_key(fd, &next_key, &next_key) == 0 &&
	       next_key == 1);
	निश्चित(bpf_map_get_next_key(fd, &next_key, &next_key) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* Delete shouldn't succeed. */
	key = 1;
	निश्चित(bpf_map_delete_elem(fd, &key) == -1 && त्रुटि_सं == EINVAL);

	बंद(fd);
पूर्ण

अटल व्योम test_arraymap_percpu(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	BPF_DECLARE_PERCPU(दीर्घ, values);
	पूर्णांक key, next_key, fd, i;

	fd = bpf_create_map(BPF_MAP_TYPE_PERCPU_ARRAY, माप(key),
			    माप(bpf_percpu(values, 0)), 2, 0);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create arraymap '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	क्रम (i = 0; i < nr_cpus; i++)
		bpf_percpu(values, i) = i + 100;

	key = 1;
	/* Insert key=1 element. */
	निश्चित(bpf_map_update_elem(fd, &key, values, BPF_ANY) == 0);

	bpf_percpu(values, 0) = 0;
	निश्चित(bpf_map_update_elem(fd, &key, values, BPF_NOEXIST) == -1 &&
	       त्रुटि_सं == EEXIST);

	/* Check that key=1 can be found. */
	निश्चित(bpf_map_lookup_elem(fd, &key, values) == 0 &&
	       bpf_percpu(values, 0) == 100);

	key = 0;
	/* Check that key=0 is also found and zero initialized. */
	निश्चित(bpf_map_lookup_elem(fd, &key, values) == 0 &&
	       bpf_percpu(values, 0) == 0 &&
	       bpf_percpu(values, nr_cpus - 1) == 0);

	/* Check that key=2 cannot be inserted due to max_entries limit. */
	key = 2;
	निश्चित(bpf_map_update_elem(fd, &key, values, BPF_EXIST) == -1 &&
	       त्रुटि_सं == E2BIG);

	/* Check that key = 2 करोesn't exist. */
	निश्चित(bpf_map_lookup_elem(fd, &key, values) == -1 && त्रुटि_सं == ENOENT);

	/* Iterate over two elements. */
	निश्चित(bpf_map_get_next_key(fd, शून्य, &next_key) == 0 &&
	       next_key == 0);
	निश्चित(bpf_map_get_next_key(fd, &key, &next_key) == 0 &&
	       next_key == 0);
	निश्चित(bpf_map_get_next_key(fd, &next_key, &next_key) == 0 &&
	       next_key == 1);
	निश्चित(bpf_map_get_next_key(fd, &next_key, &next_key) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* Delete shouldn't succeed. */
	key = 1;
	निश्चित(bpf_map_delete_elem(fd, &key) == -1 && त्रुटि_सं == EINVAL);

	बंद(fd);
पूर्ण

अटल व्योम test_arraymap_percpu_many_keys(व्योम)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	BPF_DECLARE_PERCPU(दीर्घ, values);
	/* nr_keys is not too large otherwise the test stresses percpu
	 * allocator more than anything अन्यथा
	 */
	अचिन्हित पूर्णांक nr_keys = 2000;
	पूर्णांक key, fd, i;

	fd = bpf_create_map(BPF_MAP_TYPE_PERCPU_ARRAY, माप(key),
			    माप(bpf_percpu(values, 0)), nr_keys, 0);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create per-cpu arraymap '%s'!\n",
		       म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	क्रम (i = 0; i < nr_cpus; i++)
		bpf_percpu(values, i) = i + 10;

	क्रम (key = 0; key < nr_keys; key++)
		निश्चित(bpf_map_update_elem(fd, &key, values, BPF_ANY) == 0);

	क्रम (key = 0; key < nr_keys; key++) अणु
		क्रम (i = 0; i < nr_cpus; i++)
			bpf_percpu(values, i) = 0;

		निश्चित(bpf_map_lookup_elem(fd, &key, values) == 0);

		क्रम (i = 0; i < nr_cpus; i++)
			निश्चित(bpf_percpu(values, i) == i + 10);
	पूर्ण

	बंद(fd);
पूर्ण

अटल व्योम test_devmap(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	पूर्णांक fd;
	__u32 key, value;

	fd = bpf_create_map(BPF_MAP_TYPE_DEVMAP, माप(key), माप(value),
			    2, 0);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create devmap '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	बंद(fd);
पूर्ण

अटल व्योम test_devmap_hash(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	पूर्णांक fd;
	__u32 key, value;

	fd = bpf_create_map(BPF_MAP_TYPE_DEVMAP_HASH, माप(key), माप(value),
			    2, 0);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create devmap_hash '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	बंद(fd);
पूर्ण

अटल व्योम test_queuemap(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	स्थिर पूर्णांक MAP_SIZE = 32;
	__u32 vals[MAP_SIZE + MAP_SIZE/2], val;
	पूर्णांक fd, i;

	/* Fill test values to be used */
	क्रम (i = 0; i < MAP_SIZE + MAP_SIZE/2; i++)
		vals[i] = अक्रम();

	/* Invalid key size */
	fd = bpf_create_map(BPF_MAP_TYPE_QUEUE, 4, माप(val), MAP_SIZE,
			    map_flags);
	निश्चित(fd < 0 && त्रुटि_सं == EINVAL);

	fd = bpf_create_map(BPF_MAP_TYPE_QUEUE, 0, माप(val), MAP_SIZE,
			    map_flags);
	/* Queue map करोes not support BPF_F_NO_PREALLOC */
	अगर (map_flags & BPF_F_NO_PREALLOC) अणु
		निश्चित(fd < 0 && त्रुटि_सं == EINVAL);
		वापस;
	पूर्ण
	अगर (fd < 0) अणु
		म_लिखो("Failed to create queuemap '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	/* Push MAP_SIZE elements */
	क्रम (i = 0; i < MAP_SIZE; i++)
		निश्चित(bpf_map_update_elem(fd, शून्य, &vals[i], 0) == 0);

	/* Check that element cannot be pushed due to max_entries limit */
	निश्चित(bpf_map_update_elem(fd, शून्य, &val, 0) == -1 &&
	       त्रुटि_सं == E2BIG);

	/* Peek element */
	निश्चित(bpf_map_lookup_elem(fd, शून्य, &val) == 0 && val == vals[0]);

	/* Replace half elements */
	क्रम (i = MAP_SIZE; i < MAP_SIZE + MAP_SIZE/2; i++)
		निश्चित(bpf_map_update_elem(fd, शून्य, &vals[i], BPF_EXIST) == 0);

	/* Pop all elements */
	क्रम (i = MAP_SIZE/2; i < MAP_SIZE + MAP_SIZE/2; i++)
		निश्चित(bpf_map_lookup_and_delete_elem(fd, शून्य, &val) == 0 &&
		       val == vals[i]);

	/* Check that there are not elements left */
	निश्चित(bpf_map_lookup_and_delete_elem(fd, शून्य, &val) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* Check that non supported functions set त्रुटि_सं to EINVAL */
	निश्चित(bpf_map_delete_elem(fd, शून्य) == -1 && त्रुटि_सं == EINVAL);
	निश्चित(bpf_map_get_next_key(fd, शून्य, शून्य) == -1 && त्रुटि_सं == EINVAL);

	बंद(fd);
पूर्ण

अटल व्योम test_stackmap(अचिन्हित पूर्णांक task, व्योम *data)
अणु
	स्थिर पूर्णांक MAP_SIZE = 32;
	__u32 vals[MAP_SIZE + MAP_SIZE/2], val;
	पूर्णांक fd, i;

	/* Fill test values to be used */
	क्रम (i = 0; i < MAP_SIZE + MAP_SIZE/2; i++)
		vals[i] = अक्रम();

	/* Invalid key size */
	fd = bpf_create_map(BPF_MAP_TYPE_STACK, 4, माप(val), MAP_SIZE,
			    map_flags);
	निश्चित(fd < 0 && त्रुटि_सं == EINVAL);

	fd = bpf_create_map(BPF_MAP_TYPE_STACK, 0, माप(val), MAP_SIZE,
			    map_flags);
	/* Stack map करोes not support BPF_F_NO_PREALLOC */
	अगर (map_flags & BPF_F_NO_PREALLOC) अणु
		निश्चित(fd < 0 && त्रुटि_सं == EINVAL);
		वापस;
	पूर्ण
	अगर (fd < 0) अणु
		म_लिखो("Failed to create stackmap '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	/* Push MAP_SIZE elements */
	क्रम (i = 0; i < MAP_SIZE; i++)
		निश्चित(bpf_map_update_elem(fd, शून्य, &vals[i], 0) == 0);

	/* Check that element cannot be pushed due to max_entries limit */
	निश्चित(bpf_map_update_elem(fd, शून्य, &val, 0) == -1 &&
	       त्रुटि_सं == E2BIG);

	/* Peek element */
	निश्चित(bpf_map_lookup_elem(fd, शून्य, &val) == 0 && val == vals[i - 1]);

	/* Replace half elements */
	क्रम (i = MAP_SIZE; i < MAP_SIZE + MAP_SIZE/2; i++)
		निश्चित(bpf_map_update_elem(fd, शून्य, &vals[i], BPF_EXIST) == 0);

	/* Pop all elements */
	क्रम (i = MAP_SIZE + MAP_SIZE/2 - 1; i >= MAP_SIZE/2; i--)
		निश्चित(bpf_map_lookup_and_delete_elem(fd, शून्य, &val) == 0 &&
		       val == vals[i]);

	/* Check that there are not elements left */
	निश्चित(bpf_map_lookup_and_delete_elem(fd, शून्य, &val) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* Check that non supported functions set त्रुटि_सं to EINVAL */
	निश्चित(bpf_map_delete_elem(fd, शून्य) == -1 && त्रुटि_सं == EINVAL);
	निश्चित(bpf_map_get_next_key(fd, शून्य, शून्य) == -1 && त्रुटि_सं == EINVAL);

	बंद(fd);
पूर्ण

#समावेश <sys/ioctl.h>
#समावेश <arpa/inet.h>
#समावेश <sys/select.h>
#समावेश <linux/err.h>
#घोषणा SOCKMAP_PARSE_PROG "./sockmap_parse_prog.o"
#घोषणा SOCKMAP_VERDICT_PROG "./sockmap_verdict_prog.o"
#घोषणा SOCKMAP_TCP_MSG_PROG "./sockmap_tcp_msg_prog.o"
अटल व्योम test_sockmap(अचिन्हित पूर्णांक tasks, व्योम *data)
अणु
	काष्ठा bpf_map *bpf_map_rx, *bpf_map_tx, *bpf_map_msg, *bpf_map_अवरोध;
	पूर्णांक map_fd_msg = 0, map_fd_rx = 0, map_fd_tx = 0, map_fd_अवरोध;
	पूर्णांक ports[] = अणु50200, 50201, 50202, 50204पूर्ण;
	पूर्णांक err, i, fd, udp, sfd[6] = अणु0xdeadbeefपूर्ण;
	u8 buf[20] = अणु0x0, 0x5, 0x3, 0x2, 0x1, 0x0पूर्ण;
	पूर्णांक parse_prog, verdict_prog, msg_prog;
	काष्ठा sockaddr_in addr;
	पूर्णांक one = 1, s, sc, rc;
	काष्ठा bpf_object *obj;
	काष्ठा समयval to;
	__u32 key, value;
	pid_t pid[tasks];
	fd_set w;

	/* Create some sockets to use with sockmap */
	क्रम (i = 0; i < 2; i++) अणु
		sfd[i] = socket(AF_INET, SOCK_STREAM, 0);
		अगर (sfd[i] < 0)
			जाओ out;
		err = setsockopt(sfd[i], SOL_SOCKET, SO_REUSEADDR,
				 (अक्षर *)&one, माप(one));
		अगर (err) अणु
			म_लिखो("failed to setsockopt\n");
			जाओ out;
		पूर्ण
		err = ioctl(sfd[i], FIONBIO, (अक्षर *)&one);
		अगर (err < 0) अणु
			म_लिखो("failed to ioctl\n");
			जाओ out;
		पूर्ण
		स_रखो(&addr, 0, माप(काष्ठा sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(ports[i]);
		err = bind(sfd[i], (काष्ठा sockaddr *)&addr, माप(addr));
		अगर (err < 0) अणु
			म_लिखो("failed to bind: err %i: %i:%i\n",
			       err, i, sfd[i]);
			जाओ out;
		पूर्ण
		err = listen(sfd[i], 32);
		अगर (err < 0) अणु
			म_लिखो("failed to listen\n");
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 2; i < 4; i++) अणु
		sfd[i] = socket(AF_INET, SOCK_STREAM, 0);
		अगर (sfd[i] < 0)
			जाओ out;
		err = setsockopt(sfd[i], SOL_SOCKET, SO_REUSEADDR,
				 (अक्षर *)&one, माप(one));
		अगर (err) अणु
			म_लिखो("set sock opt\n");
			जाओ out;
		पूर्ण
		स_रखो(&addr, 0, माप(काष्ठा sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(ports[i - 2]);
		err = connect(sfd[i], (काष्ठा sockaddr *)&addr, माप(addr));
		अगर (err) अणु
			म_लिखो("failed to connect\n");
			जाओ out;
		पूर्ण
	पूर्ण


	क्रम (i = 4; i < 6; i++) अणु
		sfd[i] = accept(sfd[i - 4], शून्य, शून्य);
		अगर (sfd[i] < 0) अणु
			म_लिखो("accept failed\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Test sockmap with connected sockets */
	fd = bpf_create_map(BPF_MAP_TYPE_SOCKMAP,
			    माप(key), माप(value),
			    6, 0);
	अगर (fd < 0) अणु
		अगर (!bpf_probe_map_type(BPF_MAP_TYPE_SOCKMAP, 0)) अणु
			म_लिखो("%s SKIP (unsupported map type BPF_MAP_TYPE_SOCKMAP)\n",
			       __func__);
			skips++;
			क्रम (i = 0; i < 6; i++)
				बंद(sfd[i]);
			वापस;
		पूर्ण

		म_लिखो("Failed to create sockmap %i\n", fd);
		जाओ out_sockmap;
	पूर्ण

	/* Test update with unsupported UDP socket */
	udp = socket(AF_INET, SOCK_DGRAM, 0);
	i = 0;
	err = bpf_map_update_elem(fd, &i, &udp, BPF_ANY);
	अगर (!err) अणु
		म_लिखो("Failed socket SOCK_DGRAM allowed '%i:%i'\n",
		       i, udp);
		जाओ out_sockmap;
	पूर्ण

	/* Test update without programs */
	क्रम (i = 0; i < 6; i++) अणु
		err = bpf_map_update_elem(fd, &i, &sfd[i], BPF_ANY);
		अगर (err) अणु
			म_लिखो("Failed noprog update sockmap '%i:%i'\n",
			       i, sfd[i]);
			जाओ out_sockmap;
		पूर्ण
	पूर्ण

	/* Test attaching/detaching bad fds */
	err = bpf_prog_attach(-1, fd, BPF_SK_SKB_STREAM_PARSER, 0);
	अगर (!err) अणु
		म_लिखो("Failed invalid parser prog attach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_attach(-1, fd, BPF_SK_SKB_STREAM_VERDICT, 0);
	अगर (!err) अणु
		म_लिखो("Failed invalid verdict prog attach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_attach(-1, fd, BPF_SK_MSG_VERDICT, 0);
	अगर (!err) अणु
		म_लिखो("Failed invalid msg verdict prog attach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_attach(-1, fd, __MAX_BPF_ATTACH_TYPE, 0);
	अगर (!err) अणु
		म_लिखो("Failed unknown prog attach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_detach(fd, BPF_SK_SKB_STREAM_PARSER);
	अगर (!err) अणु
		म_लिखो("Failed empty parser prog detach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_detach(fd, BPF_SK_SKB_STREAM_VERDICT);
	अगर (!err) अणु
		म_लिखो("Failed empty verdict prog detach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_detach(fd, BPF_SK_MSG_VERDICT);
	अगर (!err) अणु
		म_लिखो("Failed empty msg verdict prog detach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_detach(fd, __MAX_BPF_ATTACH_TYPE);
	अगर (!err) अणु
		म_लिखो("Detach invalid prog successful\n");
		जाओ out_sockmap;
	पूर्ण

	/* Load SK_SKB program and Attach */
	err = bpf_prog_load(SOCKMAP_PARSE_PROG,
			    BPF_PROG_TYPE_SK_SKB, &obj, &parse_prog);
	अगर (err) अणु
		म_लिखो("Failed to load SK_SKB parse prog\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_load(SOCKMAP_TCP_MSG_PROG,
			    BPF_PROG_TYPE_SK_MSG, &obj, &msg_prog);
	अगर (err) अणु
		म_लिखो("Failed to load SK_SKB msg prog\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_load(SOCKMAP_VERDICT_PROG,
			    BPF_PROG_TYPE_SK_SKB, &obj, &verdict_prog);
	अगर (err) अणु
		म_लिखो("Failed to load SK_SKB verdict prog\n");
		जाओ out_sockmap;
	पूर्ण

	bpf_map_rx = bpf_object__find_map_by_name(obj, "sock_map_rx");
	अगर (IS_ERR(bpf_map_rx)) अणु
		म_लिखो("Failed to load map rx from verdict prog\n");
		जाओ out_sockmap;
	पूर्ण

	map_fd_rx = bpf_map__fd(bpf_map_rx);
	अगर (map_fd_rx < 0) अणु
		म_लिखो("Failed to get map rx fd\n");
		जाओ out_sockmap;
	पूर्ण

	bpf_map_tx = bpf_object__find_map_by_name(obj, "sock_map_tx");
	अगर (IS_ERR(bpf_map_tx)) अणु
		म_लिखो("Failed to load map tx from verdict prog\n");
		जाओ out_sockmap;
	पूर्ण

	map_fd_tx = bpf_map__fd(bpf_map_tx);
	अगर (map_fd_tx < 0) अणु
		म_लिखो("Failed to get map tx fd\n");
		जाओ out_sockmap;
	पूर्ण

	bpf_map_msg = bpf_object__find_map_by_name(obj, "sock_map_msg");
	अगर (IS_ERR(bpf_map_msg)) अणु
		म_लिखो("Failed to load map msg from msg_verdict prog\n");
		जाओ out_sockmap;
	पूर्ण

	map_fd_msg = bpf_map__fd(bpf_map_msg);
	अगर (map_fd_msg < 0) अणु
		म_लिखो("Failed to get map msg fd\n");
		जाओ out_sockmap;
	पूर्ण

	bpf_map_अवरोध = bpf_object__find_map_by_name(obj, "sock_map_break");
	अगर (IS_ERR(bpf_map_अवरोध)) अणु
		म_लिखो("Failed to load map tx from verdict prog\n");
		जाओ out_sockmap;
	पूर्ण

	map_fd_अवरोध = bpf_map__fd(bpf_map_अवरोध);
	अगर (map_fd_अवरोध < 0) अणु
		म_लिखो("Failed to get map tx fd\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_attach(parse_prog, map_fd_अवरोध,
			      BPF_SK_SKB_STREAM_PARSER, 0);
	अगर (!err) अणु
		म_लिखो("Allowed attaching SK_SKB program to invalid map\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_attach(parse_prog, map_fd_rx,
		      BPF_SK_SKB_STREAM_PARSER, 0);
	अगर (err) अणु
		म_लिखो("Failed stream parser bpf prog attach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_attach(verdict_prog, map_fd_rx,
			      BPF_SK_SKB_STREAM_VERDICT, 0);
	अगर (err) अणु
		म_लिखो("Failed stream verdict bpf prog attach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_attach(msg_prog, map_fd_msg, BPF_SK_MSG_VERDICT, 0);
	अगर (err) अणु
		म_लिखो("Failed msg verdict bpf prog attach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_attach(verdict_prog, map_fd_rx,
			      __MAX_BPF_ATTACH_TYPE, 0);
	अगर (!err) अणु
		म_लिखो("Attached unknown bpf prog\n");
		जाओ out_sockmap;
	पूर्ण

	/* Test map update elem afterwards fd lives in fd and map_fd */
	क्रम (i = 2; i < 6; i++) अणु
		err = bpf_map_update_elem(map_fd_rx, &i, &sfd[i], BPF_ANY);
		अगर (err) अणु
			म_लिखो("Failed map_fd_rx update sockmap %i '%i:%i'\n",
			       err, i, sfd[i]);
			जाओ out_sockmap;
		पूर्ण
		err = bpf_map_update_elem(map_fd_tx, &i, &sfd[i], BPF_ANY);
		अगर (err) अणु
			म_लिखो("Failed map_fd_tx update sockmap %i '%i:%i'\n",
			       err, i, sfd[i]);
			जाओ out_sockmap;
		पूर्ण
	पूर्ण

	/* Test map delete elem and हटाओ send/recv sockets */
	क्रम (i = 2; i < 4; i++) अणु
		err = bpf_map_delete_elem(map_fd_rx, &i);
		अगर (err) अणु
			म_लिखो("Failed delete sockmap rx %i '%i:%i'\n",
			       err, i, sfd[i]);
			जाओ out_sockmap;
		पूर्ण
		err = bpf_map_delete_elem(map_fd_tx, &i);
		अगर (err) अणु
			म_लिखो("Failed delete sockmap tx %i '%i:%i'\n",
			       err, i, sfd[i]);
			जाओ out_sockmap;
		पूर्ण
	पूर्ण

	/* Put sfd[2] (sending fd below) पूर्णांकo msg map to test sendmsg bpf */
	i = 0;
	err = bpf_map_update_elem(map_fd_msg, &i, &sfd[2], BPF_ANY);
	अगर (err) अणु
		म_लिखो("Failed map_fd_msg update sockmap %i\n", err);
		जाओ out_sockmap;
	पूर्ण

	/* Test map send/recv */
	क्रम (i = 0; i < 2; i++) अणु
		buf[0] = i;
		buf[1] = 0x5;
		sc = send(sfd[2], buf, 20, 0);
		अगर (sc < 0) अणु
			म_लिखो("Failed sockmap send\n");
			जाओ out_sockmap;
		पूर्ण

		FD_ZERO(&w);
		FD_SET(sfd[3], &w);
		to.tv_sec = 1;
		to.tv_usec = 0;
		s = select(sfd[3] + 1, &w, शून्य, शून्य, &to);
		अगर (s == -1) अणु
			लिखो_त्रुटि("Failed sockmap select()");
			जाओ out_sockmap;
		पूर्ण अन्यथा अगर (!s) अणु
			म_लिखो("Failed sockmap unexpected timeout\n");
			जाओ out_sockmap;
		पूर्ण

		अगर (!FD_ISSET(sfd[3], &w)) अणु
			म_लिखो("Failed sockmap select/recv\n");
			जाओ out_sockmap;
		पूर्ण

		rc = recv(sfd[3], buf, माप(buf), 0);
		अगर (rc < 0) अणु
			म_लिखो("Failed sockmap recv\n");
			जाओ out_sockmap;
		पूर्ण
	पूर्ण

	/* Negative null entry lookup from datapath should be dropped */
	buf[0] = 1;
	buf[1] = 12;
	sc = send(sfd[2], buf, 20, 0);
	अगर (sc < 0) अणु
		म_लिखो("Failed sockmap send\n");
		जाओ out_sockmap;
	पूर्ण

	/* Push fd पूर्णांकo same slot */
	i = 2;
	err = bpf_map_update_elem(fd, &i, &sfd[i], BPF_NOEXIST);
	अगर (!err) अणु
		म_लिखो("Failed allowed sockmap dup slot BPF_NOEXIST\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_map_update_elem(fd, &i, &sfd[i], BPF_ANY);
	अगर (err) अणु
		म_लिखो("Failed sockmap update new slot BPF_ANY\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_map_update_elem(fd, &i, &sfd[i], BPF_EXIST);
	अगर (err) अणु
		म_लिखो("Failed sockmap update new slot BPF_EXIST\n");
		जाओ out_sockmap;
	पूर्ण

	/* Delete the elems without programs */
	क्रम (i = 2; i < 6; i++) अणु
		err = bpf_map_delete_elem(fd, &i);
		अगर (err) अणु
			म_लिखो("Failed delete sockmap %i '%i:%i'\n",
			       err, i, sfd[i]);
		पूर्ण
	पूर्ण

	/* Test having multiple maps खोलो and set with programs on same fds */
	err = bpf_prog_attach(parse_prog, fd,
			      BPF_SK_SKB_STREAM_PARSER, 0);
	अगर (err) अणु
		म_लिखो("Failed fd bpf parse prog attach\n");
		जाओ out_sockmap;
	पूर्ण
	err = bpf_prog_attach(verdict_prog, fd,
			      BPF_SK_SKB_STREAM_VERDICT, 0);
	अगर (err) अणु
		म_लिखो("Failed fd bpf verdict prog attach\n");
		जाओ out_sockmap;
	पूर्ण

	क्रम (i = 4; i < 6; i++) अणु
		err = bpf_map_update_elem(fd, &i, &sfd[i], BPF_ANY);
		अगर (!err) अणु
			म_लिखो("Failed allowed duplicate programs in update ANY sockmap %i '%i:%i'\n",
			       err, i, sfd[i]);
			जाओ out_sockmap;
		पूर्ण
		err = bpf_map_update_elem(fd, &i, &sfd[i], BPF_NOEXIST);
		अगर (!err) अणु
			म_लिखो("Failed allowed duplicate program in update NOEXIST sockmap  %i '%i:%i'\n",
			       err, i, sfd[i]);
			जाओ out_sockmap;
		पूर्ण
		err = bpf_map_update_elem(fd, &i, &sfd[i], BPF_EXIST);
		अगर (!err) अणु
			म_लिखो("Failed allowed duplicate program in update EXIST sockmap  %i '%i:%i'\n",
			       err, i, sfd[i]);
			जाओ out_sockmap;
		पूर्ण
	पूर्ण

	/* Test tasks number of विभाजनed operations */
	क्रम (i = 0; i < tasks; i++) अणु
		pid[i] = विभाजन();
		अगर (pid[i] == 0) अणु
			क्रम (i = 0; i < 6; i++) अणु
				bpf_map_delete_elem(map_fd_tx, &i);
				bpf_map_delete_elem(map_fd_rx, &i);
				bpf_map_update_elem(map_fd_tx, &i,
						    &sfd[i], BPF_ANY);
				bpf_map_update_elem(map_fd_rx, &i,
						    &sfd[i], BPF_ANY);
			पूर्ण
			निकास(0);
		पूर्ण अन्यथा अगर (pid[i] == -1) अणु
			म_लिखो("Couldn't spawn #%d process!\n", i);
			निकास(1);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < tasks; i++) अणु
		पूर्णांक status;

		निश्चित(रुकोpid(pid[i], &status, 0) == pid[i]);
		निश्चित(status == 0);
	पूर्ण

	err = bpf_prog_detach2(parse_prog, map_fd_rx, __MAX_BPF_ATTACH_TYPE);
	अगर (!err) अणु
		म_लिखो("Detached an invalid prog type.\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_detach2(parse_prog, map_fd_rx, BPF_SK_SKB_STREAM_PARSER);
	अगर (err) अणु
		म_लिखो("Failed parser prog detach\n");
		जाओ out_sockmap;
	पूर्ण

	err = bpf_prog_detach2(verdict_prog, map_fd_rx, BPF_SK_SKB_STREAM_VERDICT);
	अगर (err) अणु
		म_लिखो("Failed parser prog detach\n");
		जाओ out_sockmap;
	पूर्ण

	/* Test map बंद sockets and empty maps */
	क्रम (i = 0; i < 6; i++) अणु
		bpf_map_delete_elem(map_fd_tx, &i);
		bpf_map_delete_elem(map_fd_rx, &i);
		बंद(sfd[i]);
	पूर्ण
	बंद(fd);
	बंद(map_fd_rx);
	bpf_object__बंद(obj);
	वापस;
out:
	क्रम (i = 0; i < 6; i++)
		बंद(sfd[i]);
	म_लिखो("Failed to create sockmap '%i:%s'!\n", i, म_त्रुटि(त्रुटि_सं));
	निकास(1);
out_sockmap:
	क्रम (i = 0; i < 6; i++) अणु
		अगर (map_fd_tx)
			bpf_map_delete_elem(map_fd_tx, &i);
		अगर (map_fd_rx)
			bpf_map_delete_elem(map_fd_rx, &i);
		बंद(sfd[i]);
	पूर्ण
	बंद(fd);
	निकास(1);
पूर्ण

#घोषणा MAPINMAP_PROG "./test_map_in_map.o"
अटल व्योम test_map_in_map(व्योम)
अणु
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	पूर्णांक mim_fd, fd, err;
	पूर्णांक pos = 0;

	obj = bpf_object__खोलो(MAPINMAP_PROG);

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, माप(पूर्णांक), माप(पूर्णांक),
			    2, 0);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create hashmap '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	map = bpf_object__find_map_by_name(obj, "mim_array");
	अगर (IS_ERR(map)) अणु
		म_लिखो("Failed to load array of maps from test prog\n");
		जाओ out_map_in_map;
	पूर्ण
	err = bpf_map__set_inner_map_fd(map, fd);
	अगर (err) अणु
		म_लिखो("Failed to set inner_map_fd for array of maps\n");
		जाओ out_map_in_map;
	पूर्ण

	map = bpf_object__find_map_by_name(obj, "mim_hash");
	अगर (IS_ERR(map)) अणु
		म_लिखो("Failed to load hash of maps from test prog\n");
		जाओ out_map_in_map;
	पूर्ण
	err = bpf_map__set_inner_map_fd(map, fd);
	अगर (err) अणु
		म_लिखो("Failed to set inner_map_fd for hash of maps\n");
		जाओ out_map_in_map;
	पूर्ण

	bpf_object__load(obj);

	map = bpf_object__find_map_by_name(obj, "mim_array");
	अगर (IS_ERR(map)) अणु
		म_लिखो("Failed to load array of maps from test prog\n");
		जाओ out_map_in_map;
	पूर्ण
	mim_fd = bpf_map__fd(map);
	अगर (mim_fd < 0) अणु
		म_लिखो("Failed to get descriptor for array of maps\n");
		जाओ out_map_in_map;
	पूर्ण

	err = bpf_map_update_elem(mim_fd, &pos, &fd, 0);
	अगर (err) अणु
		म_लिखो("Failed to update array of maps\n");
		जाओ out_map_in_map;
	पूर्ण

	map = bpf_object__find_map_by_name(obj, "mim_hash");
	अगर (IS_ERR(map)) अणु
		म_लिखो("Failed to load hash of maps from test prog\n");
		जाओ out_map_in_map;
	पूर्ण
	mim_fd = bpf_map__fd(map);
	अगर (mim_fd < 0) अणु
		म_लिखो("Failed to get descriptor for hash of maps\n");
		जाओ out_map_in_map;
	पूर्ण

	err = bpf_map_update_elem(mim_fd, &pos, &fd, 0);
	अगर (err) अणु
		म_लिखो("Failed to update hash of maps\n");
		जाओ out_map_in_map;
	पूर्ण

	बंद(fd);
	bpf_object__बंद(obj);
	वापस;

out_map_in_map:
	बंद(fd);
	निकास(1);
पूर्ण

#घोषणा MAP_SIZE (32 * 1024)

अटल व्योम test_map_large(व्योम)
अणु

	काष्ठा bigkey अणु
		पूर्णांक a;
		अक्षर b[4096];
		दीर्घ दीर्घ c;
	पूर्ण key;
	पूर्णांक fd, i, value;

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, माप(key), माप(value),
			    MAP_SIZE, map_flags);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create large map '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	क्रम (i = 0; i < MAP_SIZE; i++) अणु
		key = (काष्ठा bigkey) अणु .c = i पूर्ण;
		value = i;

		निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == 0);
	पूर्ण

	key.c = -1;
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       त्रुटि_सं == E2BIG);

	/* Iterate through all elements. */
	निश्चित(bpf_map_get_next_key(fd, शून्य, &key) == 0);
	key.c = -1;
	क्रम (i = 0; i < MAP_SIZE; i++)
		निश्चित(bpf_map_get_next_key(fd, &key, &key) == 0);
	निश्चित(bpf_map_get_next_key(fd, &key, &key) == -1 && त्रुटि_सं == ENOENT);

	key.c = 0;
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == 0 && value == 0);
	key.a = 1;
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == -1 && त्रुटि_सं == ENOENT);

	बंद(fd);
पूर्ण

#घोषणा run_parallel(N, FN, DATA) \
	म_लिखो("Fork %u tasks to '" #FN "'\n", N); \
	__run_parallel(N, FN, DATA)

अटल व्योम __run_parallel(अचिन्हित पूर्णांक tasks,
			   व्योम (*fn)(अचिन्हित पूर्णांक task, व्योम *data),
			   व्योम *data)
अणु
	pid_t pid[tasks];
	पूर्णांक i;

	ख_साफ(मानक_निकास);

	क्रम (i = 0; i < tasks; i++) अणु
		pid[i] = विभाजन();
		अगर (pid[i] == 0) अणु
			fn(i, data);
			निकास(0);
		पूर्ण अन्यथा अगर (pid[i] == -1) अणु
			म_लिखो("Couldn't spawn #%d process!\n", i);
			निकास(1);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < tasks; i++) अणु
		पूर्णांक status;

		निश्चित(रुकोpid(pid[i], &status, 0) == pid[i]);
		निश्चित(status == 0);
	पूर्ण
पूर्ण

अटल व्योम test_map_stress(व्योम)
अणु
	run_parallel(100, test_hashmap, शून्य);
	run_parallel(100, test_hashmap_percpu, शून्य);
	run_parallel(100, test_hashmap_sizes, शून्य);
	run_parallel(100, test_hashmap_walk, शून्य);

	run_parallel(100, test_arraymap, शून्य);
	run_parallel(100, test_arraymap_percpu, शून्य);
पूर्ण

#घोषणा TASKS 1024

#घोषणा DO_UPDATE 1
#घोषणा DO_DELETE 0

#घोषणा MAP_RETRIES 20

अटल पूर्णांक map_update_retriable(पूर्णांक map_fd, स्थिर व्योम *key, स्थिर व्योम *value,
				पूर्णांक flags, पूर्णांक attempts)
अणु
	जबतक (bpf_map_update_elem(map_fd, key, value, flags)) अणु
		अगर (!attempts || (त्रुटि_सं != EAGAIN && त्रुटि_सं != EBUSY))
			वापस -त्रुटि_सं;

		usleep(1);
		attempts--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक map_delete_retriable(पूर्णांक map_fd, स्थिर व्योम *key, पूर्णांक attempts)
अणु
	जबतक (bpf_map_delete_elem(map_fd, key)) अणु
		अगर (!attempts || (त्रुटि_सं != EAGAIN && त्रुटि_सं != EBUSY))
			वापस -त्रुटि_सं;

		usleep(1);
		attempts--;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम test_update_delete(अचिन्हित पूर्णांक fn, व्योम *data)
अणु
	पूर्णांक करो_update = ((पूर्णांक *)data)[1];
	पूर्णांक fd = ((पूर्णांक *)data)[0];
	पूर्णांक i, key, value, err;

	क्रम (i = fn; i < MAP_SIZE; i += TASKS) अणु
		key = value = i;

		अगर (करो_update) अणु
			err = map_update_retriable(fd, &key, &value, BPF_NOEXIST, MAP_RETRIES);
			अगर (err)
				म_लिखो("error %d %d\n", err, त्रुटि_सं);
			निश्चित(err == 0);
			err = map_update_retriable(fd, &key, &value, BPF_EXIST, MAP_RETRIES);
			अगर (err)
				म_लिखो("error %d %d\n", err, त्रुटि_सं);
			निश्चित(err == 0);
		पूर्ण अन्यथा अणु
			err = map_delete_retriable(fd, &key, MAP_RETRIES);
			अगर (err)
				म_लिखो("error %d %d\n", err, त्रुटि_सं);
			निश्चित(err == 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम test_map_parallel(व्योम)
अणु
	पूर्णांक i, fd, key = 0, value = 0;
	पूर्णांक data[2];

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, माप(key), माप(value),
			    MAP_SIZE, map_flags);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create map for parallel test '%s'!\n",
		       म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	/* Use the same fd in children to add elements to this map:
	 * child_0 adds key=0, key=1024, key=2048, ...
	 * child_1 adds key=1, key=1025, key=2049, ...
	 * child_1023 adds key=1023, ...
	 */
	data[0] = fd;
	data[1] = DO_UPDATE;
	run_parallel(TASKS, test_update_delete, data);

	/* Check that key=0 is alपढ़ोy there. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_NOEXIST) == -1 &&
	       त्रुटि_सं == EEXIST);

	/* Check that all elements were inserted. */
	निश्चित(bpf_map_get_next_key(fd, शून्य, &key) == 0);
	key = -1;
	क्रम (i = 0; i < MAP_SIZE; i++)
		निश्चित(bpf_map_get_next_key(fd, &key, &key) == 0);
	निश्चित(bpf_map_get_next_key(fd, &key, &key) == -1 && त्रुटि_सं == ENOENT);

	/* Another check क्रम all elements */
	क्रम (i = 0; i < MAP_SIZE; i++) अणु
		key = MAP_SIZE - i - 1;

		निश्चित(bpf_map_lookup_elem(fd, &key, &value) == 0 &&
		       value == key);
	पूर्ण

	/* Now let's delete all elemenets in parallel. */
	data[1] = DO_DELETE;
	run_parallel(TASKS, test_update_delete, data);

	/* Nothing should be left. */
	key = -1;
	निश्चित(bpf_map_get_next_key(fd, शून्य, &key) == -1 && त्रुटि_सं == ENOENT);
	निश्चित(bpf_map_get_next_key(fd, &key, &key) == -1 && त्रुटि_सं == ENOENT);
पूर्ण

अटल व्योम test_map_rकरोnly(व्योम)
अणु
	पूर्णांक fd, key = 0, value = 0;

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, माप(key), माप(value),
			    MAP_SIZE, map_flags | BPF_F_RDONLY);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create map for read only test '%s'!\n",
		       म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	key = 1;
	value = 1234;
	/* Try to insert key=1 element. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == -1 &&
	       त्रुटि_सं == EPERM);

	/* Check that key=1 is not found. */
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == -1 && त्रुटि_सं == ENOENT);
	निश्चित(bpf_map_get_next_key(fd, &key, &value) == -1 && त्रुटि_सं == ENOENT);

	बंद(fd);
पूर्ण

अटल व्योम test_map_wronly_hash(व्योम)
अणु
	पूर्णांक fd, key = 0, value = 0;

	fd = bpf_create_map(BPF_MAP_TYPE_HASH, माप(key), माप(value),
			    MAP_SIZE, map_flags | BPF_F_WRONLY);
	अगर (fd < 0) अणु
		म_लिखो("Failed to create map for write only test '%s'!\n",
		       म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	key = 1;
	value = 1234;
	/* Insert key=1 element. */
	निश्चित(bpf_map_update_elem(fd, &key, &value, BPF_ANY) == 0);

	/* Check that पढ़ोing elements and keys from the map is not allowed. */
	निश्चित(bpf_map_lookup_elem(fd, &key, &value) == -1 && त्रुटि_सं == EPERM);
	निश्चित(bpf_map_get_next_key(fd, &key, &value) == -1 && त्रुटि_सं == EPERM);

	बंद(fd);
पूर्ण

अटल व्योम test_map_wronly_stack_or_queue(क्रमागत bpf_map_type map_type)
अणु
	पूर्णांक fd, value = 0;

	निश्चित(map_type == BPF_MAP_TYPE_QUEUE ||
	       map_type == BPF_MAP_TYPE_STACK);
	fd = bpf_create_map(map_type, 0, माप(value), MAP_SIZE,
			    map_flags | BPF_F_WRONLY);
	/* Stack/Queue maps करो not support BPF_F_NO_PREALLOC */
	अगर (map_flags & BPF_F_NO_PREALLOC) अणु
		निश्चित(fd < 0 && त्रुटि_सं == EINVAL);
		वापस;
	पूर्ण
	अगर (fd < 0) अणु
		म_लिखो("Failed to create map '%s'!\n", म_त्रुटि(त्रुटि_सं));
		निकास(1);
	पूर्ण

	value = 1234;
	निश्चित(bpf_map_update_elem(fd, शून्य, &value, BPF_ANY) == 0);

	/* Peek element should fail */
	निश्चित(bpf_map_lookup_elem(fd, शून्य, &value) == -1 && त्रुटि_सं == EPERM);

	/* Pop element should fail */
	निश्चित(bpf_map_lookup_and_delete_elem(fd, शून्य, &value) == -1 &&
	       त्रुटि_सं == EPERM);

	बंद(fd);
पूर्ण

अटल व्योम test_map_wronly(व्योम)
अणु
	test_map_wronly_hash();
	test_map_wronly_stack_or_queue(BPF_MAP_TYPE_STACK);
	test_map_wronly_stack_or_queue(BPF_MAP_TYPE_QUEUE);
पूर्ण

अटल व्योम prepare_reuseport_grp(पूर्णांक type, पूर्णांक map_fd, माप_प्रकार map_elem_size,
				  __s64 *fds64, __u64 *sk_cookies,
				  अचिन्हित पूर्णांक n)
अणु
	socklen_t optlen, addrlen;
	काष्ठा sockaddr_in6 s6;
	स्थिर __u32 index0 = 0;
	स्थिर पूर्णांक optval = 1;
	अचिन्हित पूर्णांक i;
	u64 sk_cookie;
	व्योम *value;
	__s32 fd32;
	__s64 fd64;
	पूर्णांक err;

	s6.sin6_family = AF_INET6;
	s6.sin6_addr = in6addr_any;
	s6.sin6_port = 0;
	addrlen = माप(s6);
	optlen = माप(sk_cookie);

	क्रम (i = 0; i < n; i++) अणु
		fd64 = socket(AF_INET6, type, 0);
		CHECK(fd64 == -1, "socket()",
		      "sock_type:%d fd64:%lld errno:%d\n",
		      type, fd64, त्रुटि_सं);

		err = setsockopt(fd64, SOL_SOCKET, SO_REUSEPORT,
				 &optval, माप(optval));
		CHECK(err == -1, "setsockopt(SO_REUSEPORT)",
		      "err:%d errno:%d\n", err, त्रुटि_सं);

		/* reuseport_array करोes not allow unbound sk */
		अगर (map_elem_size == माप(__u64))
			value = &fd64;
		अन्यथा अणु
			निश्चित(map_elem_size == माप(__u32));
			fd32 = (__s32)fd64;
			value = &fd32;
		पूर्ण
		err = bpf_map_update_elem(map_fd, &index0, value, BPF_ANY);
		CHECK(err != -1 || त्रुटि_सं != EINVAL,
		      "reuseport array update unbound sk",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, त्रुटि_सं);

		err = bind(fd64, (काष्ठा sockaddr *)&s6, माप(s6));
		CHECK(err == -1, "bind()",
		      "sock_type:%d err:%d errno:%d\n", type, err, त्रुटि_सं);

		अगर (i == 0) अणु
			err = माला_लोockname(fd64, (काष्ठा sockaddr *)&s6,
					  &addrlen);
			CHECK(err == -1, "getsockname()",
			      "sock_type:%d err:%d errno:%d\n",
			      type, err, त्रुटि_सं);
		पूर्ण

		err = माला_लोockopt(fd64, SOL_SOCKET, SO_COOKIE, &sk_cookie,
				 &optlen);
		CHECK(err == -1, "getsockopt(SO_COOKIE)",
		      "sock_type:%d err:%d errno:%d\n", type, err, त्रुटि_सं);

		अगर (type == SOCK_STREAM) अणु
			/*
			 * reuseport_array करोes not allow
			 * non-listening tcp sk.
			 */
			err = bpf_map_update_elem(map_fd, &index0, value,
						  BPF_ANY);
			CHECK(err != -1 || त्रुटि_सं != EINVAL,
			      "reuseport array update non-listening sk",
			      "sock_type:%d err:%d errno:%d\n",
			      type, err, त्रुटि_सं);
			err = listen(fd64, 0);
			CHECK(err == -1, "listen()",
			      "sock_type:%d, err:%d errno:%d\n",
			      type, err, त्रुटि_सं);
		पूर्ण

		fds64[i] = fd64;
		sk_cookies[i] = sk_cookie;
	पूर्ण
पूर्ण

अटल व्योम test_reuseport_array(व्योम)
अणु
#घोषणा REUSEPORT_FD_IDX(err, last) (अणु (err) ? last : !last; पूर्ण)

	स्थिर __u32 array_size = 4, index0 = 0, index3 = 3;
	पूर्णांक types[2] = अणु SOCK_STREAM, SOCK_DGRAM पूर्ण, type;
	__u64 grpa_cookies[2], sk_cookie, map_cookie;
	__s64 grpa_fds64[2] = अणु -1, -1 पूर्ण, fd64 = -1;
	स्थिर __u32 bad_index = array_size;
	पूर्णांक map_fd, err, t, f;
	__u32 fds_idx = 0;
	पूर्णांक fd;

	map_fd = bpf_create_map(BPF_MAP_TYPE_REUSEPORT_SOCKARRAY,
				माप(__u32), माप(__u64), array_size, 0);
	CHECK(map_fd == -1, "reuseport array create",
	      "map_fd:%d, errno:%d\n", map_fd, त्रुटि_सं);

	/* Test lookup/update/delete with invalid index */
	err = bpf_map_delete_elem(map_fd, &bad_index);
	CHECK(err != -1 || त्रुटि_सं != E2BIG, "reuseport array del >=max_entries",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	err = bpf_map_update_elem(map_fd, &bad_index, &fd64, BPF_ANY);
	CHECK(err != -1 || त्रुटि_सं != E2BIG,
	      "reuseport array update >=max_entries",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	err = bpf_map_lookup_elem(map_fd, &bad_index, &map_cookie);
	CHECK(err != -1 || त्रुटि_सं != ENOENT,
	      "reuseport array update >=max_entries",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	/* Test lookup/delete non existence elem */
	err = bpf_map_lookup_elem(map_fd, &index3, &map_cookie);
	CHECK(err != -1 || त्रुटि_सं != ENOENT,
	      "reuseport array lookup not-exist elem",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	err = bpf_map_delete_elem(map_fd, &index3);
	CHECK(err != -1 || त्रुटि_सं != ENOENT,
	      "reuseport array del not-exist elem",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	क्रम (t = 0; t < ARRAY_SIZE(types); t++) अणु
		type = types[t];

		prepare_reuseport_grp(type, map_fd, माप(__u64), grpa_fds64,
				      grpa_cookies, ARRAY_SIZE(grpa_fds64));

		/* Test BPF_* update flags */
		/* BPF_EXIST failure हाल */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_EXIST);
		CHECK(err != -1 || त्रुटि_सं != ENOENT,
		      "reuseport array update empty elem BPF_EXIST",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, त्रुटि_सं);
		fds_idx = REUSEPORT_FD_IDX(err, fds_idx);

		/* BPF_NOEXIST success हाल */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_NOEXIST);
		CHECK(err == -1,
		      "reuseport array update empty elem BPF_NOEXIST",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, त्रुटि_सं);
		fds_idx = REUSEPORT_FD_IDX(err, fds_idx);

		/* BPF_EXIST success हाल. */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_EXIST);
		CHECK(err == -1,
		      "reuseport array update same elem BPF_EXIST",
		      "sock_type:%d err:%d errno:%d\n", type, err, त्रुटि_सं);
		fds_idx = REUSEPORT_FD_IDX(err, fds_idx);

		/* BPF_NOEXIST failure हाल */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_NOEXIST);
		CHECK(err != -1 || त्रुटि_सं != EEXIST,
		      "reuseport array update non-empty elem BPF_NOEXIST",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, त्रुटि_सं);
		fds_idx = REUSEPORT_FD_IDX(err, fds_idx);

		/* BPF_ANY हाल (always succeed) */
		err = bpf_map_update_elem(map_fd, &index3, &grpa_fds64[fds_idx],
					  BPF_ANY);
		CHECK(err == -1,
		      "reuseport array update same sk with BPF_ANY",
		      "sock_type:%d err:%d errno:%d\n", type, err, त्रुटि_सं);

		fd64 = grpa_fds64[fds_idx];
		sk_cookie = grpa_cookies[fds_idx];

		/* The same sk cannot be added to reuseport_array twice */
		err = bpf_map_update_elem(map_fd, &index3, &fd64, BPF_ANY);
		CHECK(err != -1 || त्रुटि_सं != EBUSY,
		      "reuseport array update same sk with same index",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, त्रुटि_सं);

		err = bpf_map_update_elem(map_fd, &index0, &fd64, BPF_ANY);
		CHECK(err != -1 || त्रुटि_सं != EBUSY,
		      "reuseport array update same sk with different index",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, त्रुटि_सं);

		/* Test delete elem */
		err = bpf_map_delete_elem(map_fd, &index3);
		CHECK(err == -1, "reuseport array delete sk",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, त्रुटि_सं);

		/* Add it back with BPF_NOEXIST */
		err = bpf_map_update_elem(map_fd, &index3, &fd64, BPF_NOEXIST);
		CHECK(err == -1,
		      "reuseport array re-add with BPF_NOEXIST after del",
		      "sock_type:%d err:%d errno:%d\n", type, err, त्रुटि_सं);

		/* Test cookie */
		err = bpf_map_lookup_elem(map_fd, &index3, &map_cookie);
		CHECK(err == -1 || sk_cookie != map_cookie,
		      "reuseport array lookup re-added sk",
		      "sock_type:%d err:%d errno:%d sk_cookie:0x%llx map_cookie:0x%llxn",
		      type, err, त्रुटि_सं, sk_cookie, map_cookie);

		/* Test elem हटाओd by बंद() */
		क्रम (f = 0; f < ARRAY_SIZE(grpa_fds64); f++)
			बंद(grpa_fds64[f]);
		err = bpf_map_lookup_elem(map_fd, &index3, &map_cookie);
		CHECK(err != -1 || त्रुटि_सं != ENOENT,
		      "reuseport array lookup after close()",
		      "sock_type:%d err:%d errno:%d\n",
		      type, err, त्रुटि_सं);
	पूर्ण

	/* Test SOCK_RAW */
	fd64 = socket(AF_INET6, SOCK_RAW, IPPROTO_UDP);
	CHECK(fd64 == -1, "socket(SOCK_RAW)", "err:%d errno:%d\n",
	      err, त्रुटि_सं);
	err = bpf_map_update_elem(map_fd, &index3, &fd64, BPF_NOEXIST);
	CHECK(err != -1 || त्रुटि_सं != ENOTSUPP, "reuseport array update SOCK_RAW",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	बंद(fd64);

	/* Close the 64 bit value map */
	बंद(map_fd);

	/* Test 32 bit fd */
	map_fd = bpf_create_map(BPF_MAP_TYPE_REUSEPORT_SOCKARRAY,
				माप(__u32), माप(__u32), array_size, 0);
	CHECK(map_fd == -1, "reuseport array create",
	      "map_fd:%d, errno:%d\n", map_fd, त्रुटि_सं);
	prepare_reuseport_grp(SOCK_STREAM, map_fd, माप(__u32), &fd64,
			      &sk_cookie, 1);
	fd = fd64;
	err = bpf_map_update_elem(map_fd, &index3, &fd, BPF_NOEXIST);
	CHECK(err == -1, "reuseport array update 32 bit fd",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	err = bpf_map_lookup_elem(map_fd, &index3, &map_cookie);
	CHECK(err != -1 || त्रुटि_सं != ENOSPC,
	      "reuseport array lookup 32 bit fd",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	बंद(fd);
	बंद(map_fd);
पूर्ण

अटल व्योम run_all_tests(व्योम)
अणु
	test_hashmap(0, शून्य);
	test_hashmap_percpu(0, शून्य);
	test_hashmap_walk(0, शून्य);
	test_hashmap_zero_seed();

	test_arraymap(0, शून्य);
	test_arraymap_percpu(0, शून्य);

	test_arraymap_percpu_many_keys();

	test_devmap(0, शून्य);
	test_devmap_hash(0, शून्य);
	test_sockmap(0, शून्य);

	test_map_large();
	test_map_parallel();
	test_map_stress();

	test_map_rकरोnly();
	test_map_wronly();

	test_reuseport_array();

	test_queuemap(0, शून्य);
	test_stackmap(0, शून्य);

	test_map_in_map();
पूर्ण

#घोषणा DEFINE_TEST(name) बाह्य व्योम test_##name(व्योम);
#समावेश <map_tests/tests.h>
#अघोषित DEFINE_TEST

पूर्णांक मुख्य(व्योम)
अणु
	बेक्रम(समय(शून्य));

	map_flags = 0;
	run_all_tests();

	map_flags = BPF_F_NO_PREALLOC;
	run_all_tests();

#घोषणा DEFINE_TEST(name) test_##name();
#समावेश <map_tests/tests.h>
#अघोषित DEFINE_TEST

	म_लिखो("test_maps: OK, %d SKIPPED\n", skips);
	वापस 0;
पूर्ण
