<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>
#समावेश "test_hash_large_key.skel.h"

व्योम test_hash_large_key(व्योम)
अणु
	पूर्णांक err, value = 21, duration = 0, hash_map_fd;
	काष्ठा test_hash_large_key *skel;

	काष्ठा bigelement अणु
		पूर्णांक a;
		अक्षर b[4096];
		दीर्घ दीर्घ c;
	पूर्ण key;
	bzero(&key, माप(key));

	skel = test_hash_large_key__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open_and_load", "skeleton open/load failed\n"))
		वापस;

	hash_map_fd = bpf_map__fd(skel->maps.hash_map);
	अगर (CHECK(hash_map_fd < 0, "bpf_map__fd", "failed\n"))
		जाओ cleanup;

	err = test_hash_large_key__attach(skel);
	अगर (CHECK(err, "attach_raw_tp", "err %d\n", err))
		जाओ cleanup;

	err = bpf_map_update_elem(hash_map_fd, &key, &value, BPF_ANY);
	अगर (CHECK(err, "bpf_map_update_elem", "errno=%d\n", त्रुटि_सं))
		जाओ cleanup;

	key.c = 1;
	err = bpf_map_lookup_elem(hash_map_fd, &key, &value);
	अगर (CHECK(err, "bpf_map_lookup_elem", "errno=%d\n", त्रुटि_सं))
		जाओ cleanup;

	CHECK_FAIL(value != 42);

cleanup:
	test_hash_large_key__destroy(skel);
पूर्ण
