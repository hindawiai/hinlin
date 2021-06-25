<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <निश्चित.स>
#समावेश <sys/sysinfo.h>
#समावेश <sys/समय.स>

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "cgroup_helpers.h"
#समावेश "bpf_rlimit.h"
#समावेश "netcnt_common.h"

#घोषणा BPF_PROG "./netcnt_prog.o"
#घोषणा TEST_CGROUP "/test-network-counters/"

अटल पूर्णांक bpf_find_map(स्थिर अक्षर *test, काष्ठा bpf_object *obj,
			स्थिर अक्षर *name)
अणु
	काष्ठा bpf_map *map;

	map = bpf_object__find_map_by_name(obj, name);
	अगर (!map) अणु
		म_लिखो("%s:FAIL:map '%s' not found\n", test, name);
		वापस -1;
	पूर्ण
	वापस bpf_map__fd(map);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा percpu_net_cnt *percpu_netcnt;
	काष्ठा bpf_cgroup_storage_key key;
	पूर्णांक map_fd, percpu_map_fd;
	पूर्णांक error = निकास_त्रुटि;
	काष्ठा net_cnt netcnt;
	काष्ठा bpf_object *obj;
	पूर्णांक prog_fd, cgroup_fd;
	अचिन्हित दीर्घ packets;
	अचिन्हित दीर्घ bytes;
	पूर्णांक cpu, nproc;
	__u32 prog_cnt;

	nproc = get_nprocs_conf();
	percpu_netcnt = दो_स्मृति(माप(*percpu_netcnt) * nproc);
	अगर (!percpu_netcnt) अणु
		म_लिखो("Not enough memory for per-cpu area (%d cpus)\n", nproc);
		जाओ err;
	पूर्ण

	अगर (bpf_prog_load(BPF_PROG, BPF_PROG_TYPE_CGROUP_SKB,
			  &obj, &prog_fd)) अणु
		म_लिखो("Failed to load bpf program\n");
		जाओ out;
	पूर्ण

	cgroup_fd = cgroup_setup_and_join(TEST_CGROUP);
	अगर (cgroup_fd < 0)
		जाओ err;

	/* Attach bpf program */
	अगर (bpf_prog_attach(prog_fd, cgroup_fd, BPF_CGROUP_INET_EGRESS, 0)) अणु
		म_लिखो("Failed to attach bpf program");
		जाओ err;
	पूर्ण

	अगर (प्रणाली("which ping6 &>/dev/null") == 0)
		निश्चित(!प्रणाली("ping6 ::1 -c 10000 -f -q > /dev/null"));
	अन्यथा
		निश्चित(!प्रणाली("ping -6 ::1 -c 10000 -f -q > /dev/null"));

	अगर (bpf_prog_query(cgroup_fd, BPF_CGROUP_INET_EGRESS, 0, शून्य, शून्य,
			   &prog_cnt)) अणु
		म_लिखो("Failed to query attached programs");
		जाओ err;
	पूर्ण

	map_fd = bpf_find_map(__func__, obj, "netcnt");
	अगर (map_fd < 0) अणु
		म_लिखो("Failed to find bpf map with net counters");
		जाओ err;
	पूर्ण

	percpu_map_fd = bpf_find_map(__func__, obj, "percpu_netcnt");
	अगर (percpu_map_fd < 0) अणु
		म_लिखो("Failed to find bpf map with percpu net counters");
		जाओ err;
	पूर्ण

	अगर (bpf_map_get_next_key(map_fd, शून्य, &key)) अणु
		म_लिखो("Failed to get key in cgroup storage\n");
		जाओ err;
	पूर्ण

	अगर (bpf_map_lookup_elem(map_fd, &key, &netcnt)) अणु
		म_लिखो("Failed to lookup cgroup storage\n");
		जाओ err;
	पूर्ण

	अगर (bpf_map_lookup_elem(percpu_map_fd, &key, &percpu_netcnt[0])) अणु
		म_लिखो("Failed to lookup percpu cgroup storage\n");
		जाओ err;
	पूर्ण

	/* Some packets can be still in per-cpu cache, but not more than
	 * MAX_PERCPU_PACKETS.
	 */
	packets = netcnt.packets;
	bytes = netcnt.bytes;
	क्रम (cpu = 0; cpu < nproc; cpu++) अणु
		अगर (percpu_netcnt[cpu].packets > MAX_PERCPU_PACKETS) अणु
			म_लिखो("Unexpected percpu value: %llu\n",
			       percpu_netcnt[cpu].packets);
			जाओ err;
		पूर्ण

		packets += percpu_netcnt[cpu].packets;
		bytes += percpu_netcnt[cpu].bytes;
	पूर्ण

	/* No packets should be lost */
	अगर (packets != 10000) अणु
		म_लिखो("Unexpected packet count: %lu\n", packets);
		जाओ err;
	पूर्ण

	/* Let's check that bytes counter matches the number of packets
	 * multiplied by the size of ipv6 ICMP packet.
	 */
	अगर (bytes != packets * 104) अणु
		म_लिखो("Unexpected bytes count: %lu\n", bytes);
		जाओ err;
	पूर्ण

	error = 0;
	म_लिखो("test_netcnt:PASS\n");

err:
	cleanup_cgroup_environment();
	मुक्त(percpu_netcnt);

out:
	वापस error;
पूर्ण
