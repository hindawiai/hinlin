<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

क्रमागत अणु
	QUEUE,
	STACK,
पूर्ण;

अटल व्योम test_queue_stack_map_by_type(पूर्णांक type)
अणु
	स्थिर पूर्णांक MAP_SIZE = 32;
	__u32 vals[MAP_SIZE], duration, retval, size, val;
	पूर्णांक i, err, prog_fd, map_in_fd, map_out_fd;
	अक्षर file[32], buf[128];
	काष्ठा bpf_object *obj;
	काष्ठा iphdr *iph = (व्योम *)buf + माप(काष्ठा ethhdr);

	/* Fill test values to be used */
	क्रम (i = 0; i < MAP_SIZE; i++)
		vals[i] = अक्रम();

	अगर (type == QUEUE)
		म_नकलन(file, "./test_queue_map.o", माप(file));
	अन्यथा अगर (type == STACK)
		म_नकलन(file, "./test_stack_map.o", माप(file));
	अन्यथा
		वापस;

	err = bpf_prog_load(file, BPF_PROG_TYPE_SCHED_CLS, &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	map_in_fd = bpf_find_map(__func__, obj, "map_in");
	अगर (map_in_fd < 0)
		जाओ out;

	map_out_fd = bpf_find_map(__func__, obj, "map_out");
	अगर (map_out_fd < 0)
		जाओ out;

	/* Push 32 elements to the input map */
	क्रम (i = 0; i < MAP_SIZE; i++) अणु
		err = bpf_map_update_elem(map_in_fd, शून्य, &vals[i], 0);
		अगर (CHECK_FAIL(err))
			जाओ out;
	पूर्ण

	/* The eBPF program pushes iph.saddr in the output map,
	 * pops the input map and saves this value in iph.daddr
	 */
	क्रम (i = 0; i < MAP_SIZE; i++) अणु
		अगर (type == QUEUE) अणु
			val = vals[i];
			pkt_v4.iph.saddr = vals[i] * 5;
		पूर्ण अन्यथा अगर (type == STACK) अणु
			val = vals[MAP_SIZE - 1 - i];
			pkt_v4.iph.saddr = vals[MAP_SIZE - 1 - i] * 5;
		पूर्ण

		err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
					buf, &size, &retval, &duration);
		अगर (err || retval || size != माप(pkt_v4) ||
		    iph->daddr != val)
			अवरोध;
	पूर्ण

	CHECK(err || retval || size != माप(pkt_v4) || iph->daddr != val,
	      "bpf_map_pop_elem",
	      "err %d errno %d retval %d size %d iph->daddr %u\n",
	      err, त्रुटि_सं, retval, size, iph->daddr);

	/* Queue is empty, program should वापस TC_ACT_SHOT */
	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				buf, &size, &retval, &duration);
	CHECK(err || retval != 2 /* TC_ACT_SHOT */|| size != माप(pkt_v4),
	      "check-queue-stack-map-empty",
	      "err %d errno %d retval %d size %d\n",
	      err, त्रुटि_सं, retval, size);

	/* Check that the program pushed elements correctly */
	क्रम (i = 0; i < MAP_SIZE; i++) अणु
		err = bpf_map_lookup_and_delete_elem(map_out_fd, शून्य, &val);
		अगर (err || val != vals[i] * 5)
			अवरोध;
	पूर्ण

	CHECK(i != MAP_SIZE && (err || val != vals[i] * 5),
	      "bpf_map_push_elem", "err %d value %u\n", err, val);

out:
	pkt_v4.iph.saddr = 0;
	bpf_object__बंद(obj);
पूर्ण

व्योम test_queue_stack_map(व्योम)
अणु
	test_queue_stack_map_by_type(QUEUE);
	test_queue_stack_map_by_type(STACK);
पूर्ण
