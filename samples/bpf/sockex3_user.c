<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <निश्चित.स>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "sock_example.h"
#समावेश <unistd.h>
#समावेश <arpa/inet.h>
#समावेश <sys/resource.h>

काष्ठा flow_key_record अणु
	__be32 src;
	__be32 dst;
	जोड़ अणु
		__be32 ports;
		__be16 port16[2];
	पूर्ण;
	__u32 ip_proto;
पूर्ण;

काष्ठा pair अणु
	__u64 packets;
	__u64 bytes;
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक i, sock, key, fd, मुख्य_prog_fd, jmp_table_fd, hash_map_fd;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	स्थिर अक्षर *section;
	अक्षर filename[256];
	खाता *f;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);

	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	jmp_table_fd = bpf_object__find_map_fd_by_name(obj, "jmp_table");
	hash_map_fd = bpf_object__find_map_fd_by_name(obj, "hash_map");
	अगर (jmp_table_fd < 0 || hash_map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		fd = bpf_program__fd(prog);

		section = bpf_program__section_name(prog);
		अगर (माला_पूछो(section, "socket/%d", &key) != 1) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: finding prog failed\n");
			जाओ cleanup;
		पूर्ण

		अगर (key == 0)
			मुख्य_prog_fd = fd;
		अन्यथा
			bpf_map_update_elem(jmp_table_fd, &key, &fd, BPF_ANY);
	पूर्ण

	sock = खोलो_raw_sock("lo");

	/* attach BPF program to socket */
	निश्चित(setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &मुख्य_prog_fd,
			  माप(__u32)) == 0);

	अगर (argc > 1)
		f = pखोलो("ping -4 -c5 localhost", "r");
	अन्यथा
		f = pखोलो("netperf -l 4 localhost", "r");
	(व्योम) f;

	क्रम (i = 0; i < 5; i++) अणु
		काष्ठा flow_key_record key = अणुपूर्ण, next_key;
		काष्ठा pair value;

		sleep(1);
		म_लिखो("IP     src.port -> dst.port               bytes      packets\n");
		जबतक (bpf_map_get_next_key(hash_map_fd, &key, &next_key) == 0) अणु
			bpf_map_lookup_elem(hash_map_fd, &next_key, &value);
			म_लिखो("%s.%05d -> %s.%05d %12lld %12lld\n",
			       inet_ntoa((काष्ठा in_addr)अणुhtonl(next_key.src)पूर्ण),
			       next_key.port16[0],
			       inet_ntoa((काष्ठा in_addr)अणुhtonl(next_key.dst)पूर्ण),
			       next_key.port16[1],
			       value.bytes, value.packets);
			key = next_key;
		पूर्ण
	पूर्ण

cleanup:
	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
