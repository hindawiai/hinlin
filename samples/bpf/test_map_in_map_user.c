<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Facebook
 */
#समावेश <sys/resource.h>
#समावेश <sys/socket.h>
#समावेश <arpa/inet.h>
#समावेश <मानक_निवेशt.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

अटल पूर्णांक map_fd[7];

#घोषणा PORT_A		(map_fd[0])
#घोषणा PORT_H		(map_fd[1])
#घोषणा REG_RESULT_H	(map_fd[2])
#घोषणा INLINE_RESULT_H	(map_fd[3])
#घोषणा A_OF_PORT_A	(map_fd[4]) /* Test हाल #0 */
#घोषणा H_OF_PORT_A	(map_fd[5]) /* Test हाल #1 */
#घोषणा H_OF_PORT_H	(map_fd[6]) /* Test हाल #2 */

अटल स्थिर अक्षर * स्थिर test_names[] = अणु
	"Array of Array",
	"Hash of Array",
	"Hash of Hash",
पूर्ण;

#घोषणा NR_TESTS (माप(test_names) / माप(*test_names))

अटल व्योम check_map_id(पूर्णांक inner_map_fd, पूर्णांक map_in_map_fd, uपूर्णांक32_t key)
अणु
	काष्ठा bpf_map_info info = अणुपूर्ण;
	uपूर्णांक32_t info_len = माप(info);
	पूर्णांक ret, id;

	ret = bpf_obj_get_info_by_fd(inner_map_fd, &info, &info_len);
	निश्चित(!ret);

	ret = bpf_map_lookup_elem(map_in_map_fd, &key, &id);
	निश्चित(!ret);
	निश्चित(id == info.id);
पूर्ण

अटल व्योम populate_map(uपूर्णांक32_t port_key, पूर्णांक magic_result)
अणु
	पूर्णांक ret;

	ret = bpf_map_update_elem(PORT_A, &port_key, &magic_result, BPF_ANY);
	निश्चित(!ret);

	ret = bpf_map_update_elem(PORT_H, &port_key, &magic_result,
				  BPF_NOEXIST);
	निश्चित(!ret);

	ret = bpf_map_update_elem(A_OF_PORT_A, &port_key, &PORT_A, BPF_ANY);
	निश्चित(!ret);
	check_map_id(PORT_A, A_OF_PORT_A, port_key);

	ret = bpf_map_update_elem(H_OF_PORT_A, &port_key, &PORT_A, BPF_NOEXIST);
	निश्चित(!ret);
	check_map_id(PORT_A, H_OF_PORT_A, port_key);

	ret = bpf_map_update_elem(H_OF_PORT_H, &port_key, &PORT_H, BPF_NOEXIST);
	निश्चित(!ret);
	check_map_id(PORT_H, H_OF_PORT_H, port_key);
पूर्ण

अटल व्योम test_map_in_map(व्योम)
अणु
	काष्ठा sockaddr_in6 in6 = अणु .sin6_family = AF_INET6 पूर्ण;
	uपूर्णांक32_t result_key = 0, port_key;
	पूर्णांक result, अंतरभूत_result;
	पूर्णांक magic_result = 0xfaceb00c;
	पूर्णांक ret;
	पूर्णांक i;

	port_key = अक्रम() & 0x00FF;
	populate_map(port_key, magic_result);

	in6.sin6_addr.s6_addr16[0] = 0xdead;
	in6.sin6_addr.s6_addr16[1] = 0xbeef;
	in6.sin6_port = port_key;

	क्रम (i = 0; i < NR_TESTS; i++) अणु
		म_लिखो("%s: ", test_names[i]);

		in6.sin6_addr.s6_addr16[7] = i;
		ret = connect(-1, (काष्ठा sockaddr *)&in6, माप(in6));
		निश्चित(ret == -1 && त्रुटि_सं == EBADF);

		ret = bpf_map_lookup_elem(REG_RESULT_H, &result_key, &result);
		निश्चित(!ret);

		ret = bpf_map_lookup_elem(INLINE_RESULT_H, &result_key,
					  &अंतरभूत_result);
		निश्चित(!ret);

		अगर (result != magic_result || अंतरभूत_result != magic_result) अणु
			म_लिखो("Error. result:%d inline_result:%d\n",
			       result, अंतरभूत_result);
			निकास(1);
		पूर्ण

		bpf_map_delete_elem(REG_RESULT_H, &result_key);
		bpf_map_delete_elem(INLINE_RESULT_H, &result_key);

		म_लिखो("Pass\n");
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	अक्षर filename[256];

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	obj = bpf_object__खोलो_file(filename, शून्य);
	अगर (libbpf_get_error(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: opening BPF object file failed\n");
		वापस 0;
	पूर्ण

	prog = bpf_object__find_program_by_name(obj, "trace_sys_connect");
	अगर (!prog) अणु
		म_लिखो("finding a prog in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	/* load BPF program */
	अगर (bpf_object__load(obj)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: loading BPF object file failed\n");
		जाओ cleanup;
	पूर्ण

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "port_a");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "port_h");
	map_fd[2] = bpf_object__find_map_fd_by_name(obj, "reg_result_h");
	map_fd[3] = bpf_object__find_map_fd_by_name(obj, "inline_result_h");
	map_fd[4] = bpf_object__find_map_fd_by_name(obj, "a_of_port_a");
	map_fd[5] = bpf_object__find_map_fd_by_name(obj, "h_of_port_a");
	map_fd[6] = bpf_object__find_map_fd_by_name(obj, "h_of_port_h");
	अगर (map_fd[0] < 0 || map_fd[1] < 0 || map_fd[2] < 0 ||
	    map_fd[3] < 0 || map_fd[4] < 0 || map_fd[5] < 0 || map_fd[6] < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: finding a map in obj file failed\n");
		जाओ cleanup;
	पूर्ण

	link = bpf_program__attach(prog);
	अगर (libbpf_get_error(link)) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_program__attach failed\n");
		link = शून्य;
		जाओ cleanup;
	पूर्ण

	test_map_in_map();

cleanup:
	bpf_link__destroy(link);
	bpf_object__बंद(obj);
	वापस 0;
पूर्ण
