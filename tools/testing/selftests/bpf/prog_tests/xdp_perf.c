<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_xdp_perf(व्योम)
अणु
	स्थिर अक्षर *file = "./xdp_dummy.o";
	__u32 duration, retval, size;
	काष्ठा bpf_object *obj;
	अक्षर in[128], out[128];
	पूर्णांक err, prog_fd;

	err = bpf_prog_load(file, BPF_PROG_TYPE_XDP, &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	err = bpf_prog_test_run(prog_fd, 1000000, &in[0], 128,
				out, &size, &retval, &duration);

	CHECK(err || retval != XDP_PASS || size != 128,
	      "xdp-perf",
	      "err %d errno %d retval %d size %d\n",
	      err, त्रुटि_सं, retval, size);

	bpf_object__बंद(obj);
पूर्ण
