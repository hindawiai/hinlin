<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_tcp_estats(व्योम)
अणु
	स्थिर अक्षर *file = "./test_tcp_estats.o";
	पूर्णांक err, prog_fd;
	काष्ठा bpf_object *obj;
	__u32 duration = 0;

	err = bpf_prog_load(file, BPF_PROG_TYPE_TRACEPOINT, &obj, &prog_fd);
	CHECK(err, "", "err %d errno %d\n", err, त्रुटि_सं);
	अगर (err)
		वापस;

	bpf_object__बंद(obj);
पूर्ण
