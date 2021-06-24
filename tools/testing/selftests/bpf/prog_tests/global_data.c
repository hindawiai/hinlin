<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

अटल व्योम test_global_data_number(काष्ठा bpf_object *obj, __u32 duration)
अणु
	पूर्णांक i, err, map_fd;
	__u64 num;

	map_fd = bpf_find_map(__func__, obj, "result_number");
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	काष्ठा अणु
		अक्षर *name;
		uपूर्णांक32_t key;
		__u64 num;
	पूर्ण tests[] = अणु
		अणु "relocate .bss reference",     0, 0 पूर्ण,
		अणु "relocate .data reference",    1, 42 पूर्ण,
		अणु "relocate .rodata reference",  2, 24 पूर्ण,
		अणु "relocate .bss reference",     3, 0 पूर्ण,
		अणु "relocate .data reference",    4, 0xffeeff पूर्ण,
		अणु "relocate .rodata reference",  5, 0xabab पूर्ण,
		अणु "relocate .bss reference",     6, 1234 पूर्ण,
		अणु "relocate .bss reference",     7, 0 पूर्ण,
		अणु "relocate .rodata reference",  8, 0xab पूर्ण,
		अणु "relocate .rodata reference",  9, 0x1111111111111111 पूर्ण,
		अणु "relocate .rodata reference", 10, ~0 पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < माप(tests) / माप(tests[0]); i++) अणु
		err = bpf_map_lookup_elem(map_fd, &tests[i].key, &num);
		CHECK(err || num != tests[i].num, tests[i].name,
		      "err %d result %llx expected %llx\n",
		      err, num, tests[i].num);
	पूर्ण
पूर्ण

अटल व्योम test_global_data_string(काष्ठा bpf_object *obj, __u32 duration)
अणु
	पूर्णांक i, err, map_fd;
	अक्षर str[32];

	map_fd = bpf_find_map(__func__, obj, "result_string");
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	काष्ठा अणु
		अक्षर *name;
		uपूर्णांक32_t key;
		अक्षर str[32];
	पूर्ण tests[] = अणु
		अणु "relocate .rodata reference", 0, "abcdefghijklmnopqrstuvwxyz" पूर्ण,
		अणु "relocate .data reference",   1, "abcdefghijklmnopqrstuvwxyz" पूर्ण,
		अणु "relocate .bss reference",    2, "" पूर्ण,
		अणु "relocate .data reference",   3, "abcdexghijklmnopqrstuvwxyz" पूर्ण,
		अणु "relocate .bss reference",    4, "\0\0hello" पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < माप(tests) / माप(tests[0]); i++) अणु
		err = bpf_map_lookup_elem(map_fd, &tests[i].key, str);
		CHECK(err || स_भेद(str, tests[i].str, माप(str)),
		      tests[i].name, "err %d result \'%s\' expected \'%s\'\n",
		      err, str, tests[i].str);
	पूर्ण
पूर्ण

काष्ठा foo अणु
	__u8  a;
	__u32 b;
	__u64 c;
पूर्ण;

अटल व्योम test_global_data_काष्ठा(काष्ठा bpf_object *obj, __u32 duration)
अणु
	पूर्णांक i, err, map_fd;
	काष्ठा foo val;

	map_fd = bpf_find_map(__func__, obj, "result_struct");
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	काष्ठा अणु
		अक्षर *name;
		uपूर्णांक32_t key;
		काष्ठा foo val;
	पूर्ण tests[] = अणु
		अणु "relocate .rodata reference", 0, अणु 42, 0xfefeefef, 0x1111111111111111ULL, पूर्ण पूर्ण,
		अणु "relocate .bss reference",    1, अणु पूर्ण पूर्ण,
		अणु "relocate .rodata reference", 2, अणु पूर्ण पूर्ण,
		अणु "relocate .data reference",   3, अणु 41, 0xeeeeefef, 0x2111111111111111ULL, पूर्ण पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < माप(tests) / माप(tests[0]); i++) अणु
		err = bpf_map_lookup_elem(map_fd, &tests[i].key, &val);
		CHECK(err || स_भेद(&val, &tests[i].val, माप(val)),
		      tests[i].name, "err %d result { %u, %u, %llu } expected { %u, %u, %llu }\n",
		      err, val.a, val.b, val.c, tests[i].val.a, tests[i].val.b, tests[i].val.c);
	पूर्ण
पूर्ण

अटल व्योम test_global_data_rकरोnly(काष्ठा bpf_object *obj, __u32 duration)
अणु
	पूर्णांक err = -ENOMEM, map_fd, zero = 0;
	काष्ठा bpf_map *map;
	__u8 *buff;

	map = bpf_object__find_map_by_name(obj, "test_glo.rodata");
	अगर (CHECK_FAIL(!map || !bpf_map__is_पूर्णांकernal(map)))
		वापस;

	map_fd = bpf_map__fd(map);
	अगर (CHECK_FAIL(map_fd < 0))
		वापस;

	buff = दो_स्मृति(bpf_map__def(map)->value_size);
	अगर (buff)
		err = bpf_map_update_elem(map_fd, &zero, buff, 0);
	मुक्त(buff);
	CHECK(!err || त्रुटि_सं != EPERM, "test .rodata read-only map",
	      "err %d errno %d\n", err, त्रुटि_सं);
पूर्ण

व्योम test_global_data(व्योम)
अणु
	स्थिर अक्षर *file = "./test_global_data.o";
	__u32 duration = 0, retval;
	काष्ठा bpf_object *obj;
	पूर्णांक err, prog_fd;

	err = bpf_prog_load(file, BPF_PROG_TYPE_SCHED_CLS, &obj, &prog_fd);
	अगर (CHECK(err, "load program", "error %d loading %s\n", err, file))
		वापस;

	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, &retval, &duration);
	CHECK(err || retval, "pass global data run",
	      "err %d errno %d retval %d duration %d\n",
	      err, त्रुटि_सं, retval, duration);

	test_global_data_number(obj, duration);
	test_global_data_string(obj, duration);
	test_global_data_काष्ठा(obj, duration);
	test_global_data_rकरोnly(obj, duration);

	bpf_object__बंद(obj);
पूर्ण
