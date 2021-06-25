<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>

व्योम test_probe_user(व्योम)
अणु
	स्थिर अक्षर *prog_name = "kprobe/__sys_connect";
	स्थिर अक्षर *obj_file = "./test_probe_user.o";
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts, );
	पूर्णांक err, results_map_fd, sock_fd, duration = 0;
	काष्ठा sockaddr curr, orig, पंचांगp;
	काष्ठा sockaddr_in *in = (काष्ठा sockaddr_in *)&curr;
	काष्ठा bpf_link *kprobe_link = शून्य;
	काष्ठा bpf_program *kprobe_prog;
	काष्ठा bpf_object *obj;
	अटल स्थिर पूर्णांक zero = 0;

	obj = bpf_object__खोलो_file(obj_file, &opts);
	अगर (CHECK(IS_ERR(obj), "obj_open_file", "err %ld\n", PTR_ERR(obj)))
		वापस;

	kprobe_prog = bpf_object__find_program_by_title(obj, prog_name);
	अगर (CHECK(!kprobe_prog, "find_probe",
		  "prog '%s' not found\n", prog_name))
		जाओ cleanup;

	err = bpf_object__load(obj);
	अगर (CHECK(err, "obj_load", "err %d\n", err))
		जाओ cleanup;

	results_map_fd = bpf_find_map(__func__, obj, "test_pro.bss");
	अगर (CHECK(results_map_fd < 0, "find_bss_map",
		  "err %d\n", results_map_fd))
		जाओ cleanup;

	kprobe_link = bpf_program__attach(kprobe_prog);
	अगर (CHECK(IS_ERR(kprobe_link), "attach_kprobe",
		  "err %ld\n", PTR_ERR(kprobe_link))) अणु
		kprobe_link = शून्य;
		जाओ cleanup;
	पूर्ण

	स_रखो(&curr, 0, माप(curr));
	in->sin_family = AF_INET;
	in->sin_port = htons(5555);
	in->sin_addr.s_addr = inet_addr("255.255.255.255");
	स_नकल(&orig, &curr, माप(curr));

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	अगर (CHECK(sock_fd < 0, "create_sock_fd", "err %d\n", sock_fd))
		जाओ cleanup;

	connect(sock_fd, &curr, माप(curr));
	बंद(sock_fd);

	err = bpf_map_lookup_elem(results_map_fd, &zero, &पंचांगp);
	अगर (CHECK(err, "get_kprobe_res",
		  "failed to get kprobe res: %d\n", err))
		जाओ cleanup;

	in = (काष्ठा sockaddr_in *)&पंचांगp;
	अगर (CHECK(स_भेद(&पंचांगp, &orig, माप(orig)), "check_kprobe_res",
		  "wrong kprobe res from probe read: %s:%u\n",
		  inet_ntoa(in->sin_addr), ntohs(in->sin_port)))
		जाओ cleanup;

	स_रखो(&पंचांगp, 0xab, माप(पंचांगp));

	in = (काष्ठा sockaddr_in *)&curr;
	अगर (CHECK(स_भेद(&curr, &पंचांगp, माप(पंचांगp)), "check_kprobe_res",
		  "wrong kprobe res from probe write: %s:%u\n",
		  inet_ntoa(in->sin_addr), ntohs(in->sin_port)))
		जाओ cleanup;
cleanup:
	bpf_link__destroy(kprobe_link);
	bpf_object__बंद(obj);
पूर्ण
