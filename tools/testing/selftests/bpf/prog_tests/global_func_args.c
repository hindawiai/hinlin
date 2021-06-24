<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "test_progs.h"
#समावेश "network_helpers.h"

अटल __u32 duration;

अटल व्योम test_global_func_args0(काष्ठा bpf_object *obj)
अणु
	पूर्णांक err, i, map_fd, actual_value;
	स्थिर अक्षर *map_name = "values";

	map_fd = bpf_find_map(__func__, obj, map_name);
	अगर (CHECK(map_fd < 0, "bpf_find_map", "cannot find BPF map %s: %s\n",
		map_name, म_त्रुटि(त्रुटि_सं)))
		वापस;

	काष्ठा अणु
		स्थिर अक्षर *descr;
		पूर्णांक expected_value;
	पूर्ण tests[] = अणु
		अणु"passing NULL pointer", 0पूर्ण,
		अणु"returning value", 1पूर्ण,
		अणु"reading local variable", 100 पूर्ण,
		अणु"writing local variable", 101 पूर्ण,
		अणु"reading global variable", 42 पूर्ण,
		अणु"writing global variable", 43 पूर्ण,
		अणु"writing to pointer-to-pointer", 1 पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(tests); ++i) अणु
		स्थिर पूर्णांक expected_value = tests[i].expected_value;

		err = bpf_map_lookup_elem(map_fd, &i, &actual_value);

		CHECK(err || actual_value != expected_value, tests[i].descr,
			 "err %d result %d expected %d\n", err, actual_value, expected_value);
	पूर्ण
पूर्ण

व्योम test_global_func_args(व्योम)
अणु
	स्थिर अक्षर *file = "./test_global_func_args.o";
	__u32 retval;
	काष्ठा bpf_object *obj;
	पूर्णांक err, prog_fd;

	err = bpf_prog_load(file, BPF_PROG_TYPE_CGROUP_SKB, &obj, &prog_fd);
	अगर (CHECK(err, "load program", "error %d loading %s\n", err, file))
		वापस;

	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, &retval, &duration);
	CHECK(err || retval, "pass global func args run",
	      "err %d errno %d retval %d duration %d\n",
	      err, त्रुटि_सं, retval, duration);

	test_global_func_args0(obj);

	bpf_object__बंद(obj);
पूर्ण
