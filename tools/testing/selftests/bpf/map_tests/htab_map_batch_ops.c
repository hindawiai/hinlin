<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook  */
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश <bpf_util.h>
#समावेश <test_maps.h>

अटल व्योम map_batch_update(पूर्णांक map_fd, __u32 max_entries, पूर्णांक *keys,
			     व्योम *values, bool is_pcpu)
अणु
	प्रकार BPF_DECLARE_PERCPU(पूर्णांक, value);
	value *v = शून्य;
	पूर्णांक i, j, err;
	DECLARE_LIBBPF_OPTS(bpf_map_batch_opts, opts,
		.elem_flags = 0,
		.flags = 0,
	);

	अगर (is_pcpu)
		v = (value *)values;

	क्रम (i = 0; i < max_entries; i++) अणु
		keys[i] = i + 1;
		अगर (is_pcpu)
			क्रम (j = 0; j < bpf_num_possible_cpus(); j++)
				bpf_percpu(v[i], j) = i + 2 + j;
		अन्यथा
			((पूर्णांक *)values)[i] = i + 2;
	पूर्ण

	err = bpf_map_update_batch(map_fd, keys, values, &max_entries, &opts);
	CHECK(err, "bpf_map_update_batch()", "error:%s\n", म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम map_batch_verअगरy(पूर्णांक *visited, __u32 max_entries,
			     पूर्णांक *keys, व्योम *values, bool is_pcpu)
अणु
	प्रकार BPF_DECLARE_PERCPU(पूर्णांक, value);
	value *v = शून्य;
	पूर्णांक i, j;

	अगर (is_pcpu)
		v = (value *)values;

	स_रखो(visited, 0, max_entries * माप(*visited));
	क्रम (i = 0; i < max_entries; i++) अणु

		अगर (is_pcpu) अणु
			क्रम (j = 0; j < bpf_num_possible_cpus(); j++) अणु
				CHECK(keys[i] + 1 + j != bpf_percpu(v[i], j),
				      "key/value checking",
				      "error: i %d j %d key %d value %d\n",
				      i, j, keys[i], bpf_percpu(v[i],  j));
			पूर्ण
		पूर्ण अन्यथा अणु
			CHECK(keys[i] + 1 != ((पूर्णांक *)values)[i],
			      "key/value checking",
			      "error: i %d key %d value %d\n", i, keys[i],
			      ((पूर्णांक *)values)[i]);
		पूर्ण

		visited[i] = 1;

	पूर्ण
	क्रम (i = 0; i < max_entries; i++) अणु
		CHECK(visited[i] != 1, "visited checking",
		      "error: keys array at index %d missing\n", i);
	पूर्ण
पूर्ण

व्योम __test_map_lookup_and_delete_batch(bool is_pcpu)
अणु
	__u32 batch, count, total, total_success;
	प्रकार BPF_DECLARE_PERCPU(पूर्णांक, value);
	पूर्णांक map_fd, *keys, *visited, key;
	स्थिर __u32 max_entries = 10;
	value pcpu_values[max_entries];
	पूर्णांक err, step, value_size;
	bool nospace_err;
	व्योम *values;
	काष्ठा bpf_create_map_attr xattr = अणु
		.name = "hash_map",
		.map_type = is_pcpu ? BPF_MAP_TYPE_PERCPU_HASH :
			    BPF_MAP_TYPE_HASH,
		.key_size = माप(पूर्णांक),
		.value_size = माप(पूर्णांक),
	पूर्ण;
	DECLARE_LIBBPF_OPTS(bpf_map_batch_opts, opts,
		.elem_flags = 0,
		.flags = 0,
	);

	xattr.max_entries = max_entries;
	map_fd = bpf_create_map_xattr(&xattr);
	CHECK(map_fd == -1,
	      "bpf_create_map_xattr()", "error:%s\n", म_त्रुटि(त्रुटि_सं));

	value_size = is_pcpu ? माप(value) : माप(पूर्णांक);
	keys = दो_स्मृति(max_entries * माप(पूर्णांक));
	अगर (is_pcpu)
		values = pcpu_values;
	अन्यथा
		values = दो_स्मृति(max_entries * माप(पूर्णांक));
	visited = दो_स्मृति(max_entries * माप(पूर्णांक));
	CHECK(!keys || !values || !visited, "malloc()",
	      "error:%s\n", म_त्रुटि(त्रुटि_सं));

	/* test 1: lookup/delete an empty hash table, -ENOENT */
	count = max_entries;
	err = bpf_map_lookup_and_delete_batch(map_fd, शून्य, &batch, keys,
					      values, &count, &opts);
	CHECK((err && त्रुटि_सं != ENOENT), "empty map",
	      "error: %s\n", म_त्रुटि(त्रुटि_सं));

	/* populate elements to the map */
	map_batch_update(map_fd, max_entries, keys, values, is_pcpu);

	/* test 2: lookup/delete with count = 0, success */
	count = 0;
	err = bpf_map_lookup_and_delete_batch(map_fd, शून्य, &batch, keys,
					      values, &count, &opts);
	CHECK(err, "count = 0", "error: %s\n", म_त्रुटि(त्रुटि_सं));

	/* test 3: lookup/delete with count = max_entries, success */
	स_रखो(keys, 0, max_entries * माप(*keys));
	स_रखो(values, 0, max_entries * value_size);
	count = max_entries;
	err = bpf_map_lookup_and_delete_batch(map_fd, शून्य, &batch, keys,
					      values, &count, &opts);
	CHECK((err && त्रुटि_सं != ENOENT), "count = max_entries",
	       "error: %s\n", म_त्रुटि(त्रुटि_सं));
	CHECK(count != max_entries, "count = max_entries",
	      "count = %u, max_entries = %u\n", count, max_entries);
	map_batch_verअगरy(visited, max_entries, keys, values, is_pcpu);

	/* bpf_map_get_next_key() should वापस -ENOENT क्रम an empty map. */
	err = bpf_map_get_next_key(map_fd, शून्य, &key);
	CHECK(!err, "bpf_map_get_next_key()", "error: %s\n", म_त्रुटि(त्रुटि_सं));

	/* test 4: lookup/delete in a loop with various steps. */
	total_success = 0;
	क्रम (step = 1; step < max_entries; step++) अणु
		map_batch_update(map_fd, max_entries, keys, values, is_pcpu);
		स_रखो(keys, 0, max_entries * माप(*keys));
		स_रखो(values, 0, max_entries * value_size);
		total = 0;
		/* iteratively lookup/delete elements with 'step'
		 * elements each
		 */
		count = step;
		nospace_err = false;
		जबतक (true) अणु
			err = bpf_map_lookup_batch(map_fd,
						   total ? &batch : शून्य,
						   &batch, keys + total,
						   values +
						   total * value_size,
						   &count, &opts);
			/* It is possible that we are failing due to buffer size
			 * not big enough. In such हालs, let us just निकास and
			 * go with large steps. Not that a buffer size with
			 * max_entries should always work.
			 */
			अगर (err && त्रुटि_सं == ENOSPC) अणु
				nospace_err = true;
				अवरोध;
			पूर्ण

			CHECK((err && त्रुटि_सं != ENOENT), "lookup with steps",
			      "error: %s\n", म_त्रुटि(त्रुटि_सं));

			total += count;
			अगर (err)
				अवरोध;

		पूर्ण
		अगर (nospace_err == true)
			जारी;

		CHECK(total != max_entries, "lookup with steps",
		      "total = %u, max_entries = %u\n", total, max_entries);
		map_batch_verअगरy(visited, max_entries, keys, values, is_pcpu);

		total = 0;
		count = step;
		जबतक (total < max_entries) अणु
			अगर (max_entries - total < step)
				count = max_entries - total;
			err = bpf_map_delete_batch(map_fd,
						   keys + total,
						   &count, &opts);
			CHECK((err && त्रुटि_सं != ENOENT), "delete batch",
			      "error: %s\n", म_त्रुटि(त्रुटि_सं));
			total += count;
			अगर (err)
				अवरोध;
		पूर्ण
		CHECK(total != max_entries, "delete with steps",
		      "total = %u, max_entries = %u\n", total, max_entries);

		/* check map is empty, errono == ENOENT */
		err = bpf_map_get_next_key(map_fd, शून्य, &key);
		CHECK(!err || त्रुटि_सं != ENOENT, "bpf_map_get_next_key()",
		      "error: %s\n", म_त्रुटि(त्रुटि_सं));

		/* iteratively lookup/delete elements with 'step'
		 * elements each
		 */
		map_batch_update(map_fd, max_entries, keys, values, is_pcpu);
		स_रखो(keys, 0, max_entries * माप(*keys));
		स_रखो(values, 0, max_entries * value_size);
		total = 0;
		count = step;
		nospace_err = false;
		जबतक (true) अणु
			err = bpf_map_lookup_and_delete_batch(map_fd,
							total ? &batch : शून्य,
							&batch, keys + total,
							values +
							total * value_size,
							&count, &opts);
			/* It is possible that we are failing due to buffer size
			 * not big enough. In such हालs, let us just निकास and
			 * go with large steps. Not that a buffer size with
			 * max_entries should always work.
			 */
			अगर (err && त्रुटि_सं == ENOSPC) अणु
				nospace_err = true;
				अवरोध;
			पूर्ण

			CHECK((err && त्रुटि_सं != ENOENT), "lookup with steps",
			      "error: %s\n", म_त्रुटि(त्रुटि_सं));

			total += count;
			अगर (err)
				अवरोध;
		पूर्ण

		अगर (nospace_err == true)
			जारी;

		CHECK(total != max_entries, "lookup/delete with steps",
		      "total = %u, max_entries = %u\n", total, max_entries);

		map_batch_verअगरy(visited, max_entries, keys, values, is_pcpu);
		err = bpf_map_get_next_key(map_fd, शून्य, &key);
		CHECK(!err, "bpf_map_get_next_key()", "error: %s\n",
		      म_त्रुटि(त्रुटि_सं));

		total_success++;
	पूर्ण

	CHECK(total_success == 0, "check total_success",
	      "unexpected failure\n");
	मुक्त(keys);
	मुक्त(visited);
	अगर (!is_pcpu)
		मुक्त(values);
पूर्ण

व्योम htab_map_batch_ops(व्योम)
अणु
	__test_map_lookup_and_delete_batch(false);
	म_लिखो("test_%s:PASS\n", __func__);
पूर्ण

व्योम htab_percpu_map_batch_ops(व्योम)
अणु
	__test_map_lookup_and_delete_batch(true);
	म_लिखो("test_%s:PASS\n", __func__);
पूर्ण

व्योम test_htab_map_batch_ops(व्योम)
अणु
	htab_map_batch_ops();
	htab_percpu_map_batch_ops();
पूर्ण
