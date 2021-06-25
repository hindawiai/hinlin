<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <निश्चित.स>
#समावेश <bpf/bpf.h>
#समावेश <linux/filter.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/sysinfo.h>

#समावेश "bpf_rlimit.h"
#समावेश "cgroup_helpers.h"

अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

#घोषणा TEST_CGROUP "/test-bpf-cgroup-storage-buf/"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_insn prog[] = अणु
		BPF_LD_MAP_FD(BPF_REG_1, 0), /* percpu map fd */
		BPF_MOV64_IMM(BPF_REG_2, 0), /* flags, not used */
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
			     BPF_FUNC_get_local_storage),
		BPF_LDX_MEM(BPF_DW, BPF_REG_3, BPF_REG_0, 0),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, 0x1),
		BPF_STX_MEM(BPF_DW, BPF_REG_0, BPF_REG_3, 0),

		BPF_LD_MAP_FD(BPF_REG_1, 0), /* map fd */
		BPF_MOV64_IMM(BPF_REG_2, 0), /* flags, not used */
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
			     BPF_FUNC_get_local_storage),
		BPF_MOV64_IMM(BPF_REG_1, 1),
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_0, BPF_REG_1, 0),
		BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_0, 0),
		BPF_ALU64_IMM(BPF_AND, BPF_REG_1, 0x1),
		BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	पूर्ण;
	माप_प्रकार insns_cnt = माप(prog) / माप(काष्ठा bpf_insn);
	पूर्णांक error = निकास_त्रुटि;
	पूर्णांक map_fd, percpu_map_fd, prog_fd, cgroup_fd;
	काष्ठा bpf_cgroup_storage_key key;
	अचिन्हित दीर्घ दीर्घ value;
	अचिन्हित दीर्घ दीर्घ *percpu_value;
	पूर्णांक cpu, nproc;

	nproc = get_nprocs_conf();
	percpu_value = दो_स्मृति(माप(*percpu_value) * nproc);
	अगर (!percpu_value) अणु
		म_लिखो("Not enough memory for per-cpu area (%d cpus)\n", nproc);
		जाओ err;
	पूर्ण

	map_fd = bpf_create_map(BPF_MAP_TYPE_CGROUP_STORAGE, माप(key),
				माप(value), 0, 0);
	अगर (map_fd < 0) अणु
		म_लिखो("Failed to create map: %s\n", म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	percpu_map_fd = bpf_create_map(BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE,
				       माप(key), माप(value), 0, 0);
	अगर (percpu_map_fd < 0) अणु
		म_लिखो("Failed to create map: %s\n", म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	prog[0].imm = percpu_map_fd;
	prog[7].imm = map_fd;
	prog_fd = bpf_load_program(BPF_PROG_TYPE_CGROUP_SKB,
				   prog, insns_cnt, "GPL", 0,
				   bpf_log_buf, BPF_LOG_BUF_SIZE);
	अगर (prog_fd < 0) अणु
		म_लिखो("Failed to load bpf program: %s\n", bpf_log_buf);
		जाओ out;
	पूर्ण

	cgroup_fd = cgroup_setup_and_join(TEST_CGROUP);

	/* Attach the bpf program */
	अगर (bpf_prog_attach(prog_fd, cgroup_fd, BPF_CGROUP_INET_EGRESS, 0)) अणु
		म_लिखो("Failed to attach bpf program\n");
		जाओ err;
	पूर्ण

	अगर (bpf_map_get_next_key(map_fd, शून्य, &key)) अणु
		म_लिखो("Failed to get the first key in cgroup storage\n");
		जाओ err;
	पूर्ण

	अगर (bpf_map_lookup_elem(map_fd, &key, &value)) अणु
		म_लिखो("Failed to lookup cgroup storage 0\n");
		जाओ err;
	पूर्ण

	क्रम (cpu = 0; cpu < nproc; cpu++)
		percpu_value[cpu] = 1000;

	अगर (bpf_map_update_elem(percpu_map_fd, &key, percpu_value, 0)) अणु
		म_लिखो("Failed to update the data in the cgroup storage\n");
		जाओ err;
	पूर्ण

	/* Every second packet should be dropped */
	निश्चित(प्रणाली("ping localhost -c 1 -W 1 -q > /dev/null") == 0);
	निश्चित(प्रणाली("ping localhost -c 1 -W 1 -q > /dev/null"));
	निश्चित(प्रणाली("ping localhost -c 1 -W 1 -q > /dev/null") == 0);

	/* Check the counter in the cgroup local storage */
	अगर (bpf_map_lookup_elem(map_fd, &key, &value)) अणु
		म_लिखो("Failed to lookup cgroup storage\n");
		जाओ err;
	पूर्ण

	अगर (value != 3) अणु
		म_लिखो("Unexpected data in the cgroup storage: %llu\n", value);
		जाओ err;
	पूर्ण

	/* Bump the counter in the cgroup local storage */
	value++;
	अगर (bpf_map_update_elem(map_fd, &key, &value, 0)) अणु
		म_लिखो("Failed to update the data in the cgroup storage\n");
		जाओ err;
	पूर्ण

	/* Every second packet should be dropped */
	निश्चित(प्रणाली("ping localhost -c 1 -W 1 -q > /dev/null") == 0);
	निश्चित(प्रणाली("ping localhost -c 1 -W 1 -q > /dev/null"));
	निश्चित(प्रणाली("ping localhost -c 1 -W 1 -q > /dev/null") == 0);

	/* Check the final value of the counter in the cgroup local storage */
	अगर (bpf_map_lookup_elem(map_fd, &key, &value)) अणु
		म_लिखो("Failed to lookup the cgroup storage\n");
		जाओ err;
	पूर्ण

	अगर (value != 7) अणु
		म_लिखो("Unexpected data in the cgroup storage: %llu\n", value);
		जाओ err;
	पूर्ण

	/* Check the final value of the counter in the percpu local storage */

	क्रम (cpu = 0; cpu < nproc; cpu++)
		percpu_value[cpu] = 0;

	अगर (bpf_map_lookup_elem(percpu_map_fd, &key, percpu_value)) अणु
		म_लिखो("Failed to lookup the per-cpu cgroup storage\n");
		जाओ err;
	पूर्ण

	value = 0;
	क्रम (cpu = 0; cpu < nproc; cpu++)
		value += percpu_value[cpu];

	अगर (value != nproc * 1000 + 6) अणु
		म_लिखो("Unexpected data in the per-cpu cgroup storage\n");
		जाओ err;
	पूर्ण

	error = 0;
	म_लिखो("test_cgroup_storage:PASS\n");

err:
	cleanup_cgroup_environment();
	मुक्त(percpu_value);

out:
	वापस error;
पूर्ण
