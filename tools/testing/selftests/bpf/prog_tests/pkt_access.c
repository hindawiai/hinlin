<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

व्योम test_pkt_access(व्योम)
अणु
	स्थिर अक्षर *file = "./test_pkt_access.o";
	काष्ठा bpf_object *obj;
	__u32 duration, retval;
	पूर्णांक err, prog_fd;

	err = bpf_prog_load(file, BPF_PROG_TYPE_SCHED_CLS, &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	err = bpf_prog_test_run(prog_fd, 100000, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, &retval, &duration);
	CHECK(err || retval, "ipv4",
	      "err %d errno %d retval %d duration %d\n",
	      err, त्रुटि_सं, retval, duration);

	err = bpf_prog_test_run(prog_fd, 100000, &pkt_v6, माप(pkt_v6),
				शून्य, शून्य, &retval, &duration);
	CHECK(err || retval, "ipv6",
	      "err %d errno %d retval %d duration %d\n",
	      err, त्रुटि_सं, retval, duration);
	bpf_object__बंद(obj);
पूर्ण
