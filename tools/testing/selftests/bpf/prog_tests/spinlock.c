<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

अटल व्योम *spin_lock_thपढ़ो(व्योम *arg)
अणु
	__u32 duration, retval;
	पूर्णांक err, prog_fd = *(u32 *) arg;

	err = bpf_prog_test_run(prog_fd, 10000, &pkt_v4, माप(pkt_v4),
				शून्य, शून्य, &retval, &duration);
	CHECK(err || retval, "",
	      "err %d errno %d retval %d duration %d\n",
	      err, त्रुटि_सं, retval, duration);
	pthपढ़ो_निकास(arg);
पूर्ण

व्योम test_spinlock(व्योम)
अणु
	स्थिर अक्षर *file = "./test_spin_lock.o";
	pthपढ़ो_t thपढ़ो_id[4];
	काष्ठा bpf_object *obj = शून्य;
	पूर्णांक prog_fd;
	पूर्णांक err = 0, i;
	व्योम *ret;

	err = bpf_prog_load(file, BPF_PROG_TYPE_CGROUP_SKB, &obj, &prog_fd);
	अगर (CHECK_FAIL(err)) अणु
		म_लिखो("test_spin_lock:bpf_prog_load errno %d\n", त्रुटि_सं);
		जाओ बंद_prog;
	पूर्ण
	क्रम (i = 0; i < 4; i++)
		अगर (CHECK_FAIL(pthपढ़ो_create(&thपढ़ो_id[i], शून्य,
					      &spin_lock_thपढ़ो, &prog_fd)))
			जाओ बंद_prog;

	क्रम (i = 0; i < 4; i++)
		अगर (CHECK_FAIL(pthपढ़ो_join(thपढ़ो_id[i], &ret) ||
			       ret != (व्योम *)&prog_fd))
			जाओ बंद_prog;
बंद_prog:
	bpf_object__बंद(obj);
पूर्ण
