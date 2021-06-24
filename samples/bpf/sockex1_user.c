<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <निश्चित.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश "sock_example.h"
#समावेश <unistd.h>
#समावेश <arpa/inet.h>

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **argv)
अणु
	काष्ठा bpf_object *obj;
	पूर्णांक map_fd, prog_fd;
	अक्षर filename[256];
	पूर्णांक i, sock;
	खाता *f;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);

	अगर (bpf_prog_load(filename, BPF_PROG_TYPE_SOCKET_FILTER,
			  &obj, &prog_fd))
		वापस 1;

	map_fd = bpf_object__find_map_fd_by_name(obj, "my_map");

	sock = खोलो_raw_sock("lo");

	निश्चित(setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd,
			  माप(prog_fd)) == 0);

	f = pखोलो("ping -4 -c5 localhost", "r");
	(व्योम) f;

	क्रम (i = 0; i < 5; i++) अणु
		दीर्घ दीर्घ tcp_cnt, udp_cnt, icmp_cnt;
		पूर्णांक key;

		key = IPPROTO_TCP;
		निश्चित(bpf_map_lookup_elem(map_fd, &key, &tcp_cnt) == 0);

		key = IPPROTO_UDP;
		निश्चित(bpf_map_lookup_elem(map_fd, &key, &udp_cnt) == 0);

		key = IPPROTO_ICMP;
		निश्चित(bpf_map_lookup_elem(map_fd, &key, &icmp_cnt) == 0);

		म_लिखो("TCP %lld UDP %lld ICMP %lld bytes\n",
		       tcp_cnt, udp_cnt, icmp_cnt);
		sleep(1);
	पूर्ण

	वापस 0;
पूर्ण
