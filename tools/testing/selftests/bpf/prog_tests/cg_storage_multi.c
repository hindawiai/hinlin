<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Copyright 2020 Google LLC.
 */

#समावेश <test_progs.h>
#समावेश <cgroup_helpers.h>
#समावेश <network_helpers.h>

#समावेश "progs/cg_storage_multi.h"

#समावेश "cg_storage_multi_egress_only.skel.h"
#समावेश "cg_storage_multi_isolated.skel.h"
#समावेश "cg_storage_multi_shared.skel.h"

#घोषणा PARENT_CGROUP "/cgroup_storage"
#घोषणा CHILD_CGROUP "/cgroup_storage/child"

अटल पूर्णांक duration;

अटल bool निश्चित_storage(काष्ठा bpf_map *map, स्थिर व्योम *key,
			   काष्ठा cgroup_value *expected)
अणु
	काष्ठा cgroup_value value;
	पूर्णांक map_fd;

	map_fd = bpf_map__fd(map);

	अगर (CHECK(bpf_map_lookup_elem(map_fd, key, &value) < 0,
		  "map-lookup", "errno %d", त्रुटि_सं))
		वापस true;
	अगर (CHECK(स_भेद(&value, expected, माप(काष्ठा cgroup_value)),
		  "assert-storage", "storages differ"))
		वापस true;

	वापस false;
पूर्ण

अटल bool निश्चित_storage_noexist(काष्ठा bpf_map *map, स्थिर व्योम *key)
अणु
	काष्ठा cgroup_value value;
	पूर्णांक map_fd;

	map_fd = bpf_map__fd(map);

	अगर (CHECK(bpf_map_lookup_elem(map_fd, key, &value) == 0,
		  "map-lookup", "succeeded, expected ENOENT"))
		वापस true;
	अगर (CHECK(त्रुटि_सं != ENOENT,
		  "map-lookup", "errno %d, expected ENOENT", त्रुटि_सं))
		वापस true;

	वापस false;
पूर्ण

अटल bool connect_send(स्थिर अक्षर *cgroup_path)
अणु
	bool res = true;
	पूर्णांक server_fd = -1, client_fd = -1;

	अगर (join_cgroup(cgroup_path))
		जाओ out_clean;

	server_fd = start_server(AF_INET, SOCK_DGRAM, शून्य, 0, 0);
	अगर (server_fd < 0)
		जाओ out_clean;

	client_fd = connect_to_fd(server_fd, 0);
	अगर (client_fd < 0)
		जाओ out_clean;

	अगर (send(client_fd, "message", म_माप("message"), 0) < 0)
		जाओ out_clean;

	res = false;

out_clean:
	बंद(client_fd);
	बंद(server_fd);
	वापस res;
पूर्ण

अटल व्योम test_egress_only(पूर्णांक parent_cgroup_fd, पूर्णांक child_cgroup_fd)
अणु
	काष्ठा cg_storage_multi_egress_only *obj;
	काष्ठा cgroup_value expected_cgroup_value;
	काष्ठा bpf_cgroup_storage_key key;
	काष्ठा bpf_link *parent_link = शून्य, *child_link = शून्य;
	bool err;

	key.attach_type = BPF_CGROUP_INET_EGRESS;

	obj = cg_storage_multi_egress_only__खोलो_and_load();
	अगर (CHECK(!obj, "skel-load", "errno %d", त्रुटि_सं))
		वापस;

	/* Attach to parent cgroup, trigger packet from child.
	 * Assert that there is only one run and in that run the storage is
	 * parent cgroup's storage.
	 * Also निश्चित that child cgroup's storage करोes not exist
	 */
	parent_link = bpf_program__attach_cgroup(obj->progs.egress,
						 parent_cgroup_fd);
	अगर (CHECK(IS_ERR(parent_link), "parent-cg-attach",
		  "err %ld", PTR_ERR(parent_link)))
		जाओ बंद_bpf_object;
	err = connect_send(CHILD_CGROUP);
	अगर (CHECK(err, "first-connect-send", "errno %d", त्रुटि_सं))
		जाओ बंद_bpf_object;
	अगर (CHECK(obj->bss->invocations != 1,
		  "first-invoke", "invocations=%d", obj->bss->invocations))
		जाओ बंद_bpf_object;
	key.cgroup_inode_id = get_cgroup_id(PARENT_CGROUP);
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .egress_pkts = 1 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key.cgroup_inode_id = get_cgroup_id(CHILD_CGROUP);
	अगर (निश्चित_storage_noexist(obj->maps.cgroup_storage, &key))
		जाओ बंद_bpf_object;

	/* Attach to parent and child cgroup, trigger packet from child.
	 * Assert that there are two additional runs, one that run with parent
	 * cgroup's storage and one with child cgroup's storage.
	 */
	child_link = bpf_program__attach_cgroup(obj->progs.egress,
						child_cgroup_fd);
	अगर (CHECK(IS_ERR(child_link), "child-cg-attach",
		  "err %ld", PTR_ERR(child_link)))
		जाओ बंद_bpf_object;
	err = connect_send(CHILD_CGROUP);
	अगर (CHECK(err, "second-connect-send", "errno %d", त्रुटि_सं))
		जाओ बंद_bpf_object;
	अगर (CHECK(obj->bss->invocations != 3,
		  "second-invoke", "invocations=%d", obj->bss->invocations))
		जाओ बंद_bpf_object;
	key.cgroup_inode_id = get_cgroup_id(PARENT_CGROUP);
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .egress_pkts = 2 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key.cgroup_inode_id = get_cgroup_id(CHILD_CGROUP);
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .egress_pkts = 1 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;

बंद_bpf_object:
	अगर (!IS_ERR(parent_link))
		bpf_link__destroy(parent_link);
	अगर (!IS_ERR(child_link))
		bpf_link__destroy(child_link);

	cg_storage_multi_egress_only__destroy(obj);
पूर्ण

अटल व्योम test_isolated(पूर्णांक parent_cgroup_fd, पूर्णांक child_cgroup_fd)
अणु
	काष्ठा cg_storage_multi_isolated *obj;
	काष्ठा cgroup_value expected_cgroup_value;
	काष्ठा bpf_cgroup_storage_key key;
	काष्ठा bpf_link *parent_egress1_link = शून्य, *parent_egress2_link = शून्य;
	काष्ठा bpf_link *child_egress1_link = शून्य, *child_egress2_link = शून्य;
	काष्ठा bpf_link *parent_ingress_link = शून्य, *child_ingress_link = शून्य;
	bool err;

	obj = cg_storage_multi_isolated__खोलो_and_load();
	अगर (CHECK(!obj, "skel-load", "errno %d", त्रुटि_सं))
		वापस;

	/* Attach to parent cgroup, trigger packet from child.
	 * Assert that there is three runs, two with parent cgroup egress and
	 * one with parent cgroup ingress, stored in separate parent storages.
	 * Also निश्चित that child cgroup's storages करोes not exist
	 */
	parent_egress1_link = bpf_program__attach_cgroup(obj->progs.egress1,
							 parent_cgroup_fd);
	अगर (CHECK(IS_ERR(parent_egress1_link), "parent-egress1-cg-attach",
		  "err %ld", PTR_ERR(parent_egress1_link)))
		जाओ बंद_bpf_object;
	parent_egress2_link = bpf_program__attach_cgroup(obj->progs.egress2,
							 parent_cgroup_fd);
	अगर (CHECK(IS_ERR(parent_egress2_link), "parent-egress2-cg-attach",
		  "err %ld", PTR_ERR(parent_egress2_link)))
		जाओ बंद_bpf_object;
	parent_ingress_link = bpf_program__attach_cgroup(obj->progs.ingress,
							 parent_cgroup_fd);
	अगर (CHECK(IS_ERR(parent_ingress_link), "parent-ingress-cg-attach",
		  "err %ld", PTR_ERR(parent_ingress_link)))
		जाओ बंद_bpf_object;
	err = connect_send(CHILD_CGROUP);
	अगर (CHECK(err, "first-connect-send", "errno %d", त्रुटि_सं))
		जाओ बंद_bpf_object;
	अगर (CHECK(obj->bss->invocations != 3,
		  "first-invoke", "invocations=%d", obj->bss->invocations))
		जाओ बंद_bpf_object;
	key.cgroup_inode_id = get_cgroup_id(PARENT_CGROUP);
	key.attach_type = BPF_CGROUP_INET_EGRESS;
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .egress_pkts = 2 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key.attach_type = BPF_CGROUP_INET_INGRESS;
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .ingress_pkts = 1 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key.cgroup_inode_id = get_cgroup_id(CHILD_CGROUP);
	key.attach_type = BPF_CGROUP_INET_EGRESS;
	अगर (निश्चित_storage_noexist(obj->maps.cgroup_storage, &key))
		जाओ बंद_bpf_object;
	key.attach_type = BPF_CGROUP_INET_INGRESS;
	अगर (निश्चित_storage_noexist(obj->maps.cgroup_storage, &key))
		जाओ बंद_bpf_object;

	/* Attach to parent and child cgroup, trigger packet from child.
	 * Assert that there is six additional runs, parent cgroup egresses and
	 * ingress, child cgroup egresses and ingress.
	 * Assert that egree and ingress storages are separate.
	 */
	child_egress1_link = bpf_program__attach_cgroup(obj->progs.egress1,
							child_cgroup_fd);
	अगर (CHECK(IS_ERR(child_egress1_link), "child-egress1-cg-attach",
		  "err %ld", PTR_ERR(child_egress1_link)))
		जाओ बंद_bpf_object;
	child_egress2_link = bpf_program__attach_cgroup(obj->progs.egress2,
							child_cgroup_fd);
	अगर (CHECK(IS_ERR(child_egress2_link), "child-egress2-cg-attach",
		  "err %ld", PTR_ERR(child_egress2_link)))
		जाओ बंद_bpf_object;
	child_ingress_link = bpf_program__attach_cgroup(obj->progs.ingress,
							child_cgroup_fd);
	अगर (CHECK(IS_ERR(child_ingress_link), "child-ingress-cg-attach",
		  "err %ld", PTR_ERR(child_ingress_link)))
		जाओ बंद_bpf_object;
	err = connect_send(CHILD_CGROUP);
	अगर (CHECK(err, "second-connect-send", "errno %d", त्रुटि_सं))
		जाओ बंद_bpf_object;
	अगर (CHECK(obj->bss->invocations != 9,
		  "second-invoke", "invocations=%d", obj->bss->invocations))
		जाओ बंद_bpf_object;
	key.cgroup_inode_id = get_cgroup_id(PARENT_CGROUP);
	key.attach_type = BPF_CGROUP_INET_EGRESS;
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .egress_pkts = 4 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key.attach_type = BPF_CGROUP_INET_INGRESS;
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .ingress_pkts = 2 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key.cgroup_inode_id = get_cgroup_id(CHILD_CGROUP);
	key.attach_type = BPF_CGROUP_INET_EGRESS;
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .egress_pkts = 2 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key.attach_type = BPF_CGROUP_INET_INGRESS;
	expected_cgroup_value = (काष्ठा cgroup_value) अणु .ingress_pkts = 1 पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;

बंद_bpf_object:
	अगर (!IS_ERR(parent_egress1_link))
		bpf_link__destroy(parent_egress1_link);
	अगर (!IS_ERR(parent_egress2_link))
		bpf_link__destroy(parent_egress2_link);
	अगर (!IS_ERR(parent_ingress_link))
		bpf_link__destroy(parent_ingress_link);
	अगर (!IS_ERR(child_egress1_link))
		bpf_link__destroy(child_egress1_link);
	अगर (!IS_ERR(child_egress2_link))
		bpf_link__destroy(child_egress2_link);
	अगर (!IS_ERR(child_ingress_link))
		bpf_link__destroy(child_ingress_link);

	cg_storage_multi_isolated__destroy(obj);
पूर्ण

अटल व्योम test_shared(पूर्णांक parent_cgroup_fd, पूर्णांक child_cgroup_fd)
अणु
	काष्ठा cg_storage_multi_shared *obj;
	काष्ठा cgroup_value expected_cgroup_value;
	__u64 key;
	काष्ठा bpf_link *parent_egress1_link = शून्य, *parent_egress2_link = शून्य;
	काष्ठा bpf_link *child_egress1_link = शून्य, *child_egress2_link = शून्य;
	काष्ठा bpf_link *parent_ingress_link = शून्य, *child_ingress_link = शून्य;
	bool err;

	obj = cg_storage_multi_shared__खोलो_and_load();
	अगर (CHECK(!obj, "skel-load", "errno %d", त्रुटि_सं))
		वापस;

	/* Attach to parent cgroup, trigger packet from child.
	 * Assert that there is three runs, two with parent cgroup egress and
	 * one with parent cgroup ingress.
	 * Also निश्चित that child cgroup's storage करोes not exist
	 */
	parent_egress1_link = bpf_program__attach_cgroup(obj->progs.egress1,
							 parent_cgroup_fd);
	अगर (CHECK(IS_ERR(parent_egress1_link), "parent-egress1-cg-attach",
		  "err %ld", PTR_ERR(parent_egress1_link)))
		जाओ बंद_bpf_object;
	parent_egress2_link = bpf_program__attach_cgroup(obj->progs.egress2,
							 parent_cgroup_fd);
	अगर (CHECK(IS_ERR(parent_egress2_link), "parent-egress2-cg-attach",
		  "err %ld", PTR_ERR(parent_egress2_link)))
		जाओ बंद_bpf_object;
	parent_ingress_link = bpf_program__attach_cgroup(obj->progs.ingress,
							 parent_cgroup_fd);
	अगर (CHECK(IS_ERR(parent_ingress_link), "parent-ingress-cg-attach",
		  "err %ld", PTR_ERR(parent_ingress_link)))
		जाओ बंद_bpf_object;
	err = connect_send(CHILD_CGROUP);
	अगर (CHECK(err, "first-connect-send", "errno %d", त्रुटि_सं))
		जाओ बंद_bpf_object;
	अगर (CHECK(obj->bss->invocations != 3,
		  "first-invoke", "invocations=%d", obj->bss->invocations))
		जाओ बंद_bpf_object;
	key = get_cgroup_id(PARENT_CGROUP);
	expected_cgroup_value = (काष्ठा cgroup_value) अणु
		.egress_pkts = 2,
		.ingress_pkts = 1,
	पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key = get_cgroup_id(CHILD_CGROUP);
	अगर (निश्चित_storage_noexist(obj->maps.cgroup_storage, &key))
		जाओ बंद_bpf_object;

	/* Attach to parent and child cgroup, trigger packet from child.
	 * Assert that there is six additional runs, parent cgroup egresses and
	 * ingress, child cgroup egresses and ingress.
	 */
	child_egress1_link = bpf_program__attach_cgroup(obj->progs.egress1,
							child_cgroup_fd);
	अगर (CHECK(IS_ERR(child_egress1_link), "child-egress1-cg-attach",
		  "err %ld", PTR_ERR(child_egress1_link)))
		जाओ बंद_bpf_object;
	child_egress2_link = bpf_program__attach_cgroup(obj->progs.egress2,
							child_cgroup_fd);
	अगर (CHECK(IS_ERR(child_egress2_link), "child-egress2-cg-attach",
		  "err %ld", PTR_ERR(child_egress2_link)))
		जाओ बंद_bpf_object;
	child_ingress_link = bpf_program__attach_cgroup(obj->progs.ingress,
							child_cgroup_fd);
	अगर (CHECK(IS_ERR(child_ingress_link), "child-ingress-cg-attach",
		  "err %ld", PTR_ERR(child_ingress_link)))
		जाओ बंद_bpf_object;
	err = connect_send(CHILD_CGROUP);
	अगर (CHECK(err, "second-connect-send", "errno %d", त्रुटि_सं))
		जाओ बंद_bpf_object;
	अगर (CHECK(obj->bss->invocations != 9,
		  "second-invoke", "invocations=%d", obj->bss->invocations))
		जाओ बंद_bpf_object;
	key = get_cgroup_id(PARENT_CGROUP);
	expected_cgroup_value = (काष्ठा cgroup_value) अणु
		.egress_pkts = 4,
		.ingress_pkts = 2,
	पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;
	key = get_cgroup_id(CHILD_CGROUP);
	expected_cgroup_value = (काष्ठा cgroup_value) अणु
		.egress_pkts = 2,
		.ingress_pkts = 1,
	पूर्ण;
	अगर (निश्चित_storage(obj->maps.cgroup_storage,
			   &key, &expected_cgroup_value))
		जाओ बंद_bpf_object;

बंद_bpf_object:
	अगर (!IS_ERR(parent_egress1_link))
		bpf_link__destroy(parent_egress1_link);
	अगर (!IS_ERR(parent_egress2_link))
		bpf_link__destroy(parent_egress2_link);
	अगर (!IS_ERR(parent_ingress_link))
		bpf_link__destroy(parent_ingress_link);
	अगर (!IS_ERR(child_egress1_link))
		bpf_link__destroy(child_egress1_link);
	अगर (!IS_ERR(child_egress2_link))
		bpf_link__destroy(child_egress2_link);
	अगर (!IS_ERR(child_ingress_link))
		bpf_link__destroy(child_ingress_link);

	cg_storage_multi_shared__destroy(obj);
पूर्ण

व्योम test_cg_storage_multi(व्योम)
अणु
	पूर्णांक parent_cgroup_fd = -1, child_cgroup_fd = -1;

	parent_cgroup_fd = test__join_cgroup(PARENT_CGROUP);
	अगर (CHECK(parent_cgroup_fd < 0, "cg-create-parent", "errno %d", त्रुटि_सं))
		जाओ बंद_cgroup_fd;
	child_cgroup_fd = create_and_get_cgroup(CHILD_CGROUP);
	अगर (CHECK(child_cgroup_fd < 0, "cg-create-child", "errno %d", त्रुटि_सं))
		जाओ बंद_cgroup_fd;

	अगर (test__start_subtest("egress_only"))
		test_egress_only(parent_cgroup_fd, child_cgroup_fd);

	अगर (test__start_subtest("isolated"))
		test_isolated(parent_cgroup_fd, child_cgroup_fd);

	अगर (test__start_subtest("shared"))
		test_shared(parent_cgroup_fd, child_cgroup_fd);

बंद_cgroup_fd:
	बंद(child_cgroup_fd);
	बंद(parent_cgroup_fd);
पूर्ण
