<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_global_data_init(व्योम)
अणु
	स्थिर अक्षर *file = "./test_global_data.o";
	पूर्णांक err = -ENOMEM, map_fd, zero = 0;
	__u8 *buff = शून्य, *newval = शून्य;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
        __u32 duration = 0;
	माप_प्रकार sz;

	obj = bpf_object__खोलो_file(file, शून्य);
	err = libbpf_get_error(obj);
	अगर (CHECK_FAIL(err))
		वापस;

	map = bpf_object__find_map_by_name(obj, "test_glo.rodata");
	अगर (CHECK_FAIL(!map || !bpf_map__is_पूर्णांकernal(map)))
		जाओ out;

	sz = bpf_map__def(map)->value_size;
	newval = दो_स्मृति(sz);
	अगर (CHECK_FAIL(!newval))
		जाओ out;

	स_रखो(newval, 0, sz);
	/* wrong size, should fail */
	err = bpf_map__set_initial_value(map, newval, sz - 1);
	अगर (CHECK(!err, "reject set initial value wrong size", "err %d\n", err))
		जाओ out;

	err = bpf_map__set_initial_value(map, newval, sz);
	अगर (CHECK(err, "set initial value", "err %d\n", err))
		जाओ out;

	err = bpf_object__load(obj);
	अगर (CHECK_FAIL(err))
		जाओ out;

	map_fd = bpf_map__fd(map);
	अगर (CHECK_FAIL(map_fd < 0))
		जाओ out;

	buff = दो_स्मृति(sz);
	अगर (buff)
		err = bpf_map_lookup_elem(map_fd, &zero, buff);
	अगर (CHECK(!buff || err || स_भेद(buff, newval, sz),
		  "compare .rodata map data override",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	स_रखो(newval, 1, sz);
	/* object loaded - should fail */
	err = bpf_map__set_initial_value(map, newval, sz);
	CHECK(!err, "reject set initial value after load", "err %d\n", err);
out:
	मुक्त(buff);
	मुक्त(newval);
	bpf_object__बंद(obj);
पूर्ण
