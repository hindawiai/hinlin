<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश <test_maps.h>

अटल पूर्णांक nr_cpus;

अटल व्योम map_batch_update(पूर्णांक map_fd, __u32 max_entries, पूर्णांक *keys,
			     __s64 *values, bool is_pcpu)
अणु
	पूर्णांक i, j, err;
	पूर्णांक cpu_offset = 0;
	DECLARE_LIBBPF_OPTS(bpf_map_batch_opts, opts,
		.elem_flags = 0,
		.flags = 0,
	);

	क्रम (i = 0; i < max_entries; i++) अणु
		keys[i] = i;
		अगर (is_pcpu) अणु
			cpu_offset = i * nr_cpus;
			क्रम (j = 0; j < nr_cpus; j++)
				(values + cpu_offset)[j] = i + 1 + j;
		पूर्ण अन्यथा अणु
			values[i] = i + 1;
		पूर्ण
	पूर्ण

	err = bpf_map_update_batch(map_fd, keys, values, &max_entries, &opts);
	CHECK(err, "bpf_map_update_batch()", "error:%s\n", म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम map_batch_verअगरy(पूर्णांक *visited, __u32 max_entries, पूर्णांक *keys,
			     __s64 *values, bool is_pcpu)
अणु
	पूर्णांक i, j;
	पूर्णांक cpu_offset = 0;

	स_रखो(visited, 0, max_entries * माप(*visited));
	क्रम (i = 0; i < max_entries; i++) अणु
		अगर (is_pcpu) अणु
			cpu_offset = i * nr_cpus;
			क्रम (j = 0; j < nr_cpus; j++) अणु
				__s64 value = (values + cpu_offset)[j];
				CHECK(keys[i] + j + 1 != value,
				      "key/value checking",
				      "error: i %d j %d key %d value %lld\n", i,
				      j, keys[i], value);
			पूर्ण
		पूर्ण अन्यथा अणु
			CHECK(keys[i] + 1 != values[i], "key/value checking",
			      "error: i %d key %d value %lld\n", i, keys[i],
			      values[i]);
		पूर्ण
		visited[i] = 1;
	पूर्ण
	क्रम (i = 0; i < max_entries; i++) अणु
		CHECK(visited[i] != 1, "visited checking",
		      "error: keys array at index %d missing\n", i);
	पूर्ण
पूर्ण

अटल व्योम __test_map_lookup_and_update_batch(bool is_pcpu)
अणु
	काष्ठा bpf_create_map_attr xattr = अणु
		.name = "array_map",
		.map_type = is_pcpu ? BPF_MAP_TYPE_PERCPU_ARRAY :
				      BPF_MAP_TYPE_ARRAY,
		.key_size = माप(पूर्णांक),
		.value_size = माप(__s64),
	पूर्ण;
	पूर्णांक map_fd, *keys, *visited;
	__u32 count, total, total_success;
	स्थिर __u32 max_entries = 10;
	__u64 batch = 0;
	पूर्णांक err, step, value_size;
	व्योम *values;
	DECLARE_LIBBPF_OPTS(bpf_map_batch_opts, opts,
		.elem_flags = 0,
		.flags = 0,
	);

	xattr.max_entries = max_entries;
	map_fd = bpf_create_map_xattr(&xattr);
	CHECK(map_fd == -1,
	      "bpf_create_map_xattr()", "error:%s\n", म_त्रुटि(त्रुटि_सं));

	value_size = माप(__s64);
	अगर (is_pcpu)
		value_size *= nr_cpus;

	keys = सुस्मृति(max_entries, माप(*keys));
	values = सुस्मृति(max_entries, value_size);
	visited = सुस्मृति(max_entries, माप(*visited));
	CHECK(!keys || !values || !visited, "malloc()", "error:%s\n",
	      म_त्रुटि(त्रुटि_सं));

	/* test 1: lookup in a loop with various steps. */
	total_success = 0;
	क्रम (step = 1; step < max_entries; step++) अणु
		map_batch_update(map_fd, max_entries, keys, values, is_pcpu);
		map_batch_verअगरy(visited, max_entries, keys, values, is_pcpu);
		स_रखो(keys, 0, max_entries * माप(*keys));
		स_रखो(values, 0, max_entries * value_size);
		batch = 0;
		total = 0;
		/* iteratively lookup/delete elements with 'step'
		 * elements each.
		 */
		count = step;
		जबतक (true) अणु
			err = bpf_map_lookup_batch(map_fd,
						   total ? &batch : शून्य,
						   &batch, keys + total,
						   values + total * value_size,
						   &count, &opts);

			CHECK((err && त्रुटि_सं != ENOENT), "lookup with steps",
			      "error: %s\n", म_त्रुटि(त्रुटि_सं));

			total += count;
			अगर (err)
				अवरोध;

		पूर्ण

		CHECK(total != max_entries, "lookup with steps",
		      "total = %u, max_entries = %u\n", total, max_entries);

		map_batch_verअगरy(visited, max_entries, keys, values, is_pcpu);

		total_success++;
	पूर्ण

	CHECK(total_success == 0, "check total_success",
	      "unexpected failure\n");

	मुक्त(keys);
	मुक्त(values);
	मुक्त(visited);
पूर्ण

अटल व्योम array_map_batch_ops(व्योम)
अणु
	__test_map_lookup_and_update_batch(false);
	म_लिखो("test_%s:PASS\n", __func__);
पूर्ण

अटल व्योम array_percpu_map_batch_ops(व्योम)
अणु
	__test_map_lookup_and_update_batch(true);
	म_लिखो("test_%s:PASS\n", __func__);
पूर्ण

व्योम test_array_map_batch_ops(व्योम)
अणु
	nr_cpus = libbpf_num_possible_cpus();

	CHECK(nr_cpus < 0, "nr_cpus checking",
	      "error: get possible cpus failed");

	array_map_batch_ops();
	array_percpu_map_batch_ops();
पूर्ण
