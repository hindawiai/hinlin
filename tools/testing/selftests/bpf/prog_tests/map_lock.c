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

अटल व्योम *parallel_map_access(व्योम *arg)
अणु
	पूर्णांक err, map_fd = *(u32 *) arg;
	पूर्णांक vars[17], i, j, rnd, key = 0;

	क्रम (i = 0; i < 10000; i++) अणु
		err = bpf_map_lookup_elem_flags(map_fd, &key, vars, BPF_F_LOCK);
		अगर (CHECK_FAIL(err)) अणु
			म_लिखो("lookup failed\n");
			जाओ out;
		पूर्ण
		अगर (CHECK_FAIL(vars[0] != 0)) अणु
			म_लिखो("lookup #%d var[0]=%d\n", i, vars[0]);
			जाओ out;
		पूर्ण
		rnd = vars[1];
		क्रम (j = 2; j < 17; j++) अणु
			अगर (vars[j] == rnd)
				जारी;
			म_लिखो("lookup #%d var[1]=%d var[%d]=%d\n",
			       i, rnd, j, vars[j]);
			CHECK_FAIL(vars[j] != rnd);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	pthपढ़ो_निकास(arg);
पूर्ण

व्योम test_map_lock(व्योम)
अणु
	स्थिर अक्षर *file = "./test_map_lock.o";
	पूर्णांक prog_fd, map_fd[2], vars[17] = अणुपूर्ण;
	pthपढ़ो_t thपढ़ो_id[6];
	काष्ठा bpf_object *obj = शून्य;
	पूर्णांक err = 0, key = 0, i;
	व्योम *ret;

	err = bpf_prog_load(file, BPF_PROG_TYPE_CGROUP_SKB, &obj, &prog_fd);
	अगर (CHECK_FAIL(err)) अणु
		म_लिखो("test_map_lock:bpf_prog_load errno %d\n", त्रुटि_सं);
		जाओ बंद_prog;
	पूर्ण
	map_fd[0] = bpf_find_map(__func__, obj, "hash_map");
	अगर (CHECK_FAIL(map_fd[0] < 0))
		जाओ बंद_prog;
	map_fd[1] = bpf_find_map(__func__, obj, "array_map");
	अगर (CHECK_FAIL(map_fd[1] < 0))
		जाओ बंद_prog;

	bpf_map_update_elem(map_fd[0], &key, vars, BPF_F_LOCK);

	क्रम (i = 0; i < 4; i++)
		अगर (CHECK_FAIL(pthपढ़ो_create(&thपढ़ो_id[i], शून्य,
					      &spin_lock_thपढ़ो, &prog_fd)))
			जाओ बंद_prog;
	क्रम (i = 4; i < 6; i++)
		अगर (CHECK_FAIL(pthपढ़ो_create(&thपढ़ो_id[i], शून्य,
					      &parallel_map_access,
					      &map_fd[i - 4])))
			जाओ बंद_prog;
	क्रम (i = 0; i < 4; i++)
		अगर (CHECK_FAIL(pthपढ़ो_join(thपढ़ो_id[i], &ret) ||
			       ret != (व्योम *)&prog_fd))
			जाओ बंद_prog;
	क्रम (i = 4; i < 6; i++)
		अगर (CHECK_FAIL(pthपढ़ो_join(thपढ़ो_id[i], &ret) ||
			       ret != (व्योम *)&map_fd[i - 4]))
			जाओ बंद_prog;
बंद_prog:
	bpf_object__बंद(obj);
पूर्ण
