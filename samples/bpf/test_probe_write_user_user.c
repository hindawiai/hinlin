<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <निश्चित.स>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <sys/socket.h>
#समावेश <netinet/in.h>
#समावेश <arpa/inet.h>

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **argv)
अणु
	काष्ठा sockaddr_in *serv_addr_in, *mapped_addr_in, *पंचांगp_addr_in;
	काष्ठा sockaddr serv_addr, mapped_addr, पंचांगp_addr;
	पूर्णांक serverfd, serverconnfd, clientfd, map_fd;
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	socklen_t sockaddr_len;
	अक्षर filename[256];
	अक्षर *ip;

	serv_addr_in = (काष्ठा sockaddr_in *)&serv_addr;
	mapped_addr_in = (काष्ठा sockaddr_in *)&mapped_addr;
	पंचांगp_addr_in = (काष्ठा sockaddr_in *)&पंचांगp_addr;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "bpf_prog1");
	अगर (libbpf_get_error(prog)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a prog in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd = bpf_object__find_map_fd_by_name(obj, "dnat_map");
	अगर (map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	link = bpf_program__attach(prog);
	अगर (libbpf_get_error(link)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
		link = शून्य;
		जाओ cleanup;
	पूर्ण

	निश्चित((serverfd = socket(AF_INET, SOCK_STREAM, 0)) > 0);
	निश्चित((clientfd = socket(AF_INET, SOCK_STREAM, 0)) > 0);

	/* Bind server to ephemeral port on lo */
	स_रखो(&serv_addr, 0, माप(serv_addr));
	serv_addr_in->sin_family = AF_INET;
	serv_addr_in->sin_port = 0;
	serv_addr_in->sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	निश्चित(bind(serverfd, &serv_addr, माप(serv_addr)) == 0);

	sockaddr_len = माप(serv_addr);
	निश्चित(माला_लोockname(serverfd, &serv_addr, &sockaddr_len) == 0);
	ip = inet_ntoa(serv_addr_in->sin_addr);
	म_लिखो("Server bound to: %s:%d\n", ip, ntohs(serv_addr_in->sin_port));

	स_रखो(&mapped_addr, 0, माप(mapped_addr));
	mapped_addr_in->sin_family = AF_INET;
	mapped_addr_in->sin_port = htons(5555);
	mapped_addr_in->sin_addr.s_addr = inet_addr("255.255.255.255");

	निश्चित(!bpf_map_update_elem(map_fd, &mapped_addr, &serv_addr, BPF_ANY));

	निश्चित(listen(serverfd, 5) == 0);

	ip = inet_ntoa(mapped_addr_in->sin_addr);
	म_लिखो("Client connecting to: %s:%d\n",
	       ip, ntohs(mapped_addr_in->sin_port));
	निश्चित(connect(clientfd, &mapped_addr, माप(mapped_addr)) == 0);

	sockaddr_len = माप(पंचांगp_addr);
	ip = inet_ntoa(पंचांगp_addr_in->sin_addr);
	निश्चित((serverconnfd = accept(serverfd, &पंचांगp_addr, &sockaddr_len)) > 0);
	म_लिखो("Server received connection from: %s:%d\n",
	       ip, ntohs(पंचांगp_addr_in->sin_port));

	sockaddr_len = माप(पंचांगp_addr);
	निश्चित(getpeername(clientfd, &पंचांगp_addr, &sockaddr_len) == 0);
	ip = inet_ntoa(पंचांगp_addr_in->sin_addr);
	म_लिखो("Client's peer address: %s:%d\n",
	       ip, ntohs(पंचांगp_addr_in->sin_port));

	/* Is the server's माला_लोockname = the socket getpeername */
	निश्चित(स_भेद(&serv_addr, &पंचांगp_addr, माप(काष्ठा sockaddr_in)) == 0);

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
