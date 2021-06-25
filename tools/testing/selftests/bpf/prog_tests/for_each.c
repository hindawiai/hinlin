<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#समावेश <test_progs.h>
#समावेश <network_helpers.h>
#समावेश "for_each_hash_map_elem.skel.h"
#समावेश "for_each_array_map_elem.skel.h"

अटल अचिन्हित पूर्णांक duration;

अटल व्योम test_hash_map(व्योम)
अणु
	पूर्णांक i, err, hashmap_fd, max_entries, percpu_map_fd;
	काष्ठा क्रम_each_hash_map_elem *skel;
	__u64 *percpu_valbuf = शून्य;
	__u32 key, num_cpus, retval;
	__u64 val;

	skel = क्रम_each_hash_map_elem__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "for_each_hash_map_elem__open_and_load"))
		वापस;

	hashmap_fd = bpf_map__fd(skel->maps.hashmap);
	max_entries = bpf_map__max_entries(skel->maps.hashmap);
	क्रम (i = 0; i < max_entries; i++) अणु
		key = i;
		val = i + 1;
		err = bpf_map_update_elem(hashmap_fd, &key, &val, BPF_ANY);
		अगर (!ASSERT_OK(err, "map_update"))
			जाओ out;
	पूर्ण

	num_cpus = bpf_num_possible_cpus();
	percpu_map_fd = bpf_map__fd(skel->maps.percpu_map);
	percpu_valbuf = दो_स्मृति(माप(__u64) * num_cpus);
	अगर (!ASSERT_OK_PTR(percpu_valbuf, "percpu_valbuf"))
		जाओ out;

	key = 1;
	क्रम (i = 0; i < num_cpus; i++)
		percpu_valbuf[i] = i + 1;
	err = bpf_map_update_elem(percpu_map_fd, &key, percpu_valbuf, BPF_ANY);
	अगर (!ASSERT_OK(err, "percpu_map_update"))
		जाओ out;

	err = bpf_prog_test_run(bpf_program__fd(skel->progs.test_pkt_access),
				1, &pkt_v4, माप(pkt_v4), शून्य, शून्य,
				&retval, &duration);
	अगर (CHECK(err || retval, "ipv4", "err %d errno %d retval %d\n",
		  err, त्रुटि_सं, retval))
		जाओ out;

	ASSERT_EQ(skel->bss->hashmap_output, 4, "hashmap_output");
	ASSERT_EQ(skel->bss->hashmap_elems, max_entries, "hashmap_elems");

	key = 1;
	err = bpf_map_lookup_elem(hashmap_fd, &key, &val);
	ASSERT_ERR(err, "hashmap_lookup");

	ASSERT_EQ(skel->bss->percpu_called, 1, "percpu_called");
	ASSERT_LT(skel->bss->cpu, num_cpus, "num_cpus");
	ASSERT_EQ(skel->bss->percpu_map_elems, 1, "percpu_map_elems");
	ASSERT_EQ(skel->bss->percpu_key, 1, "percpu_key");
	ASSERT_EQ(skel->bss->percpu_val, skel->bss->cpu + 1, "percpu_val");
	ASSERT_EQ(skel->bss->percpu_output, 100, "percpu_output");
out:
	मुक्त(percpu_valbuf);
	क्रम_each_hash_map_elem__destroy(skel);
पूर्ण

अटल व्योम test_array_map(व्योम)
अणु
	__u32 key, num_cpus, max_entries, retval;
	पूर्णांक i, arraymap_fd, percpu_map_fd, err;
	काष्ठा क्रम_each_array_map_elem *skel;
	__u64 *percpu_valbuf = शून्य;
	__u64 val, expected_total;

	skel = क्रम_each_array_map_elem__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "for_each_array_map_elem__open_and_load"))
		वापस;

	arraymap_fd = bpf_map__fd(skel->maps.arraymap);
	expected_total = 0;
	max_entries = bpf_map__max_entries(skel->maps.arraymap);
	क्रम (i = 0; i < max_entries; i++) अणु
		key = i;
		val = i + 1;
		/* skip the last iteration क्रम expected total */
		अगर (i != max_entries - 1)
			expected_total += val;
		err = bpf_map_update_elem(arraymap_fd, &key, &val, BPF_ANY);
		अगर (!ASSERT_OK(err, "map_update"))
			जाओ out;
	पूर्ण

	num_cpus = bpf_num_possible_cpus();
	percpu_map_fd = bpf_map__fd(skel->maps.percpu_map);
	percpu_valbuf = दो_स्मृति(माप(__u64) * num_cpus);
	अगर (!ASSERT_OK_PTR(percpu_valbuf, "percpu_valbuf"))
		जाओ out;

	key = 0;
	क्रम (i = 0; i < num_cpus; i++)
		percpu_valbuf[i] = i + 1;
	err = bpf_map_update_elem(percpu_map_fd, &key, percpu_valbuf, BPF_ANY);
	अगर (!ASSERT_OK(err, "percpu_map_update"))
		जाओ out;

	err = bpf_prog_test_run(bpf_program__fd(skel->progs.test_pkt_access),
				1, &pkt_v4, माप(pkt_v4), शून्य, शून्य,
				&retval, &duration);
	अगर (CHECK(err || retval, "ipv4", "err %d errno %d retval %d\n",
		  err, त्रुटि_सं, retval))
		जाओ out;

	ASSERT_EQ(skel->bss->arraymap_output, expected_total, "array_output");
	ASSERT_EQ(skel->bss->cpu + 1, skel->bss->percpu_val, "percpu_val");

out:
	मुक्त(percpu_valbuf);
	क्रम_each_array_map_elem__destroy(skel);
पूर्ण

व्योम test_क्रम_each(व्योम)
अणु
	अगर (test__start_subtest("hash_map"))
		test_hash_map();
	अगर (test__start_subtest("array_map"))
		test_array_map();
पूर्ण
