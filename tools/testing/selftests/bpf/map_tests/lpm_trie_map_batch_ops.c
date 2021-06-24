<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <arpa/inet.h>
#समावेश <linux/bpf.h>
#समावेश <netinet/in.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश <test_maps.h>

काष्ठा test_lpm_key अणु
	__u32 prefix;
	काष्ठा in_addr ipv4;
पूर्ण;

अटल व्योम map_batch_update(पूर्णांक map_fd, __u32 max_entries,
			     काष्ठा test_lpm_key *keys, पूर्णांक *values)
अणु
	__u32 i;
	पूर्णांक err;
	अक्षर buff[16] = अणु 0 पूर्ण;
	DECLARE_LIBBPF_OPTS(bpf_map_batch_opts, opts,
		.elem_flags = 0,
		.flags = 0,
	);

	क्रम (i = 0; i < max_entries; i++) अणु
		keys[i].prefix = 32;
		snम_लिखो(buff, 16, "192.168.1.%d", i + 1);
		inet_pton(AF_INET, buff, &keys[i].ipv4);
		values[i] = i + 1;
	पूर्ण

	err = bpf_map_update_batch(map_fd, keys, values, &max_entries, &opts);
	CHECK(err, "bpf_map_update_batch()", "error:%s\n", म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम map_batch_verअगरy(पूर्णांक *visited, __u32 max_entries,
			     काष्ठा test_lpm_key *keys, पूर्णांक *values)
अणु
	अक्षर buff[16] = अणु 0 पूर्ण;
	पूर्णांक lower_byte = 0;
	__u32 i;

	स_रखो(visited, 0, max_entries * माप(*visited));
	क्रम (i = 0; i < max_entries; i++) अणु
		inet_ntop(AF_INET, &keys[i].ipv4, buff, 32);
		CHECK(माला_पूछो(buff, "192.168.1.%d", &lower_byte) == खातापूर्ण,
		      "sscanf()", "error: i %d\n", i);
		CHECK(lower_byte != values[i], "key/value checking",
		      "error: i %d key %s value %d\n", i, buff, values[i]);
		visited[i] = 1;
	पूर्ण
	क्रम (i = 0; i < max_entries; i++) अणु
		CHECK(visited[i] != 1, "visited checking",
		      "error: keys array at index %d missing\n", i);
	पूर्ण
पूर्ण

व्योम test_lpm_trie_map_batch_ops(व्योम)
अणु
	काष्ठा bpf_create_map_attr xattr = अणु
		.name = "lpm_trie_map",
		.map_type = BPF_MAP_TYPE_LPM_TRIE,
		.key_size = माप(काष्ठा test_lpm_key),
		.value_size = माप(पूर्णांक),
		.map_flags = BPF_F_NO_PREALLOC,
	पूर्ण;
	काष्ठा test_lpm_key *keys, key;
	पूर्णांक map_fd, *values, *visited;
	__u32 step, count, total, total_success;
	स्थिर __u32 max_entries = 10;
	__u64 batch = 0;
	पूर्णांक err;
	DECLARE_LIBBPF_OPTS(bpf_map_batch_opts, opts,
		.elem_flags = 0,
		.flags = 0,
	);

	xattr.max_entries = max_entries;
	map_fd = bpf_create_map_xattr(&xattr);
	CHECK(map_fd == -1, "bpf_create_map_xattr()", "error:%s\n",
	      म_त्रुटि(त्रुटि_सं));

	keys = दो_स्मृति(max_entries * माप(काष्ठा test_lpm_key));
	values = दो_स्मृति(max_entries * माप(पूर्णांक));
	visited = दो_स्मृति(max_entries * माप(पूर्णांक));
	CHECK(!keys || !values || !visited, "malloc()", "error:%s\n",
	      म_त्रुटि(त्रुटि_सं));

	total_success = 0;
	क्रम (step = 1; step < max_entries; step++) अणु
		map_batch_update(map_fd, max_entries, keys, values);
		map_batch_verअगरy(visited, max_entries, keys, values);
		स_रखो(keys, 0, max_entries * माप(*keys));
		स_रखो(values, 0, max_entries * माप(*values));
		batch = 0;
		total = 0;
		/* iteratively lookup/delete elements with 'step'
		 * elements each.
		 */
		count = step;
		जबतक (true) अणु
			err = bpf_map_lookup_batch(map_fd,
				total ? &batch : शून्य, &batch,
				keys + total, values + total, &count, &opts);

			CHECK((err && त्रुटि_सं != ENOENT), "lookup with steps",
			      "error: %s\n", म_त्रुटि(त्रुटि_सं));

			total += count;
			अगर (err)
				अवरोध;
		पूर्ण

		CHECK(total != max_entries, "lookup with steps",
		      "total = %u, max_entries = %u\n", total, max_entries);

		map_batch_verअगरy(visited, max_entries, keys, values);

		total = 0;
		count = step;
		जबतक (total < max_entries) अणु
			अगर (max_entries - total < step)
				count = max_entries - total;
			err = bpf_map_delete_batch(map_fd, keys + total, &count,
						   &opts);
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

		total_success++;
	पूर्ण

	CHECK(total_success == 0, "check total_success",
	      "unexpected failure\n");

	म_लिखो("%s:PASS\n", __func__);

	मुक्त(keys);
	मुक्त(values);
	मुक्त(visited);
पूर्ण
