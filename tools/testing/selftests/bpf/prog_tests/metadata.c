<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Copyright 2020 Google LLC.
 */

#समावेश <test_progs.h>
#समावेश <cgroup_helpers.h>
#समावेश <network_helpers.h>

#समावेश "metadata_unused.skel.h"
#समावेश "metadata_used.skel.h"

अटल पूर्णांक duration;

अटल पूर्णांक prog_holds_map(पूर्णांक prog_fd, पूर्णांक map_fd)
अणु
	काष्ठा bpf_prog_info prog_info = अणुपूर्ण;
	काष्ठा bpf_prog_info map_info = अणुपूर्ण;
	__u32 prog_info_len;
	__u32 map_info_len;
	__u32 *map_ids;
	पूर्णांक nr_maps;
	पूर्णांक ret;
	पूर्णांक i;

	map_info_len = माप(map_info);
	ret = bpf_obj_get_info_by_fd(map_fd, &map_info, &map_info_len);
	अगर (ret)
		वापस -त्रुटि_सं;

	prog_info_len = माप(prog_info);
	ret = bpf_obj_get_info_by_fd(prog_fd, &prog_info, &prog_info_len);
	अगर (ret)
		वापस -त्रुटि_सं;

	map_ids = सुस्मृति(prog_info.nr_map_ids, माप(__u32));
	अगर (!map_ids)
		वापस -ENOMEM;

	nr_maps = prog_info.nr_map_ids;
	स_रखो(&prog_info, 0, माप(prog_info));
	prog_info.nr_map_ids = nr_maps;
	prog_info.map_ids = ptr_to_u64(map_ids);
	prog_info_len = माप(prog_info);

	ret = bpf_obj_get_info_by_fd(prog_fd, &prog_info, &prog_info_len);
	अगर (ret) अणु
		ret = -त्रुटि_सं;
		जाओ मुक्त_map_ids;
	पूर्ण

	ret = -ENOENT;
	क्रम (i = 0; i < prog_info.nr_map_ids; i++) अणु
		अगर (map_ids[i] == map_info.id) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

मुक्त_map_ids:
	मुक्त(map_ids);
	वापस ret;
पूर्ण

अटल व्योम test_metadata_unused(व्योम)
अणु
	काष्ठा metadata_unused *obj;
	पूर्णांक err;

	obj = metadata_unused__खोलो_and_load();
	अगर (CHECK(!obj, "skel-load", "errno %d", त्रुटि_सं))
		वापस;

	err = prog_holds_map(bpf_program__fd(obj->progs.prog),
			     bpf_map__fd(obj->maps.rodata));
	अगर (CHECK(err, "prog-holds-rodata", "errno: %d", err))
		वापस;

	/* Assert that we can access the metadata in skel and the values are
	 * what we expect.
	 */
	अगर (CHECK(म_भेदन(obj->rodata->bpf_metadata_a, "foo",
			  माप(obj->rodata->bpf_metadata_a)),
		  "bpf_metadata_a", "expected \"foo\", value differ"))
		जाओ बंद_bpf_object;
	अगर (CHECK(obj->rodata->bpf_metadata_b != 1, "bpf_metadata_b",
		  "expected 1, got %d", obj->rodata->bpf_metadata_b))
		जाओ बंद_bpf_object;

	/* Assert that binding metadata map to prog again succeeds. */
	err = bpf_prog_bind_map(bpf_program__fd(obj->progs.prog),
				bpf_map__fd(obj->maps.rodata), शून्य);
	CHECK(err, "rebind_map", "errno %d, expected 0", त्रुटि_सं);

बंद_bpf_object:
	metadata_unused__destroy(obj);
पूर्ण

अटल व्योम test_metadata_used(व्योम)
अणु
	काष्ठा metadata_used *obj;
	पूर्णांक err;

	obj = metadata_used__खोलो_and_load();
	अगर (CHECK(!obj, "skel-load", "errno %d", त्रुटि_सं))
		वापस;

	err = prog_holds_map(bpf_program__fd(obj->progs.prog),
			     bpf_map__fd(obj->maps.rodata));
	अगर (CHECK(err, "prog-holds-rodata", "errno: %d", err))
		वापस;

	/* Assert that we can access the metadata in skel and the values are
	 * what we expect.
	 */
	अगर (CHECK(म_भेदन(obj->rodata->bpf_metadata_a, "bar",
			  माप(obj->rodata->bpf_metadata_a)),
		  "metadata_a", "expected \"bar\", value differ"))
		जाओ बंद_bpf_object;
	अगर (CHECK(obj->rodata->bpf_metadata_b != 2, "metadata_b",
		  "expected 2, got %d", obj->rodata->bpf_metadata_b))
		जाओ बंद_bpf_object;

	/* Assert that binding metadata map to prog again succeeds. */
	err = bpf_prog_bind_map(bpf_program__fd(obj->progs.prog),
				bpf_map__fd(obj->maps.rodata), शून्य);
	CHECK(err, "rebind_map", "errno %d, expected 0", त्रुटि_सं);

बंद_bpf_object:
	metadata_used__destroy(obj);
पूर्ण

व्योम test_metadata(व्योम)
अणु
	अगर (test__start_subtest("unused"))
		test_metadata_unused();

	अगर (test__start_subtest("used"))
		test_metadata_used();
पूर्ण
