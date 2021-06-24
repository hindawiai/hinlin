<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_task_fd_query_rawtp(व्योम)
अणु
	स्थिर अक्षर *file = "./test_get_stack_rawtp.o";
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	काष्ठा bpf_object *obj;
	पूर्णांक efd, err, prog_fd;
	__u32 duration = 0;
	अक्षर buf[256];

	err = bpf_prog_load(file, BPF_PROG_TYPE_RAW_TRACEPOINT, &obj, &prog_fd);
	अगर (CHECK(err, "prog_load raw tp", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	efd = bpf_raw_tracepoपूर्णांक_खोलो("sys_enter", prog_fd);
	अगर (CHECK(efd < 0, "raw_tp_open", "err %d errno %d\n", efd, त्रुटि_सं))
		जाओ बंद_prog;

	/* query (getpid(), efd) */
	len = माप(buf);
	err = bpf_task_fd_query(getpid(), efd, 0, buf, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	अगर (CHECK(err < 0, "bpf_task_fd_query", "err %d errno %d\n", err,
		  त्रुटि_सं))
		जाओ बंद_prog;

	err = fd_type == BPF_FD_TYPE_RAW_TRACEPOINT &&
	      म_भेद(buf, "sys_enter") == 0;
	अगर (CHECK(!err, "check_results", "fd_type %d tp_name %s\n",
		  fd_type, buf))
		जाओ बंद_prog;

	/* test zero len */
	len = 0;
	err = bpf_task_fd_query(getpid(), efd, 0, buf, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	अगर (CHECK(err < 0, "bpf_task_fd_query (len = 0)", "err %d errno %d\n",
		  err, त्रुटि_सं))
		जाओ बंद_prog;
	err = fd_type == BPF_FD_TYPE_RAW_TRACEPOINT &&
	      len == म_माप("sys_enter");
	अगर (CHECK(!err, "check_results", "fd_type %d len %u\n", fd_type, len))
		जाओ बंद_prog;

	/* test empty buffer */
	len = माप(buf);
	err = bpf_task_fd_query(getpid(), efd, 0, 0, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	अगर (CHECK(err < 0, "bpf_task_fd_query (buf = 0)", "err %d errno %d\n",
		  err, त्रुटि_सं))
		जाओ बंद_prog;
	err = fd_type == BPF_FD_TYPE_RAW_TRACEPOINT &&
	      len == म_माप("sys_enter");
	अगर (CHECK(!err, "check_results", "fd_type %d len %u\n", fd_type, len))
		जाओ बंद_prog;

	/* test smaller buffer */
	len = 3;
	err = bpf_task_fd_query(getpid(), efd, 0, buf, &len, &prog_id,
				&fd_type, &probe_offset, &probe_addr);
	अगर (CHECK(err >= 0 || त्रुटि_सं != ENOSPC, "bpf_task_fd_query (len = 3)",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_prog;
	err = fd_type == BPF_FD_TYPE_RAW_TRACEPOINT &&
	      len == म_माप("sys_enter") &&
	      म_भेद(buf, "sy") == 0;
	अगर (CHECK(!err, "check_results", "fd_type %d len %u\n", fd_type, len))
		जाओ बंद_prog;

बंद_prog:
	bpf_object__बंद(obj);
पूर्ण
