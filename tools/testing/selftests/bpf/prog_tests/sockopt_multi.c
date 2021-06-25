<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "cgroup_helpers.h"

अटल पूर्णांक prog_attach(काष्ठा bpf_object *obj, पूर्णांक cgroup_fd, स्थिर अक्षर *title)
अणु
	क्रमागत bpf_attach_type attach_type;
	क्रमागत bpf_prog_type prog_type;
	काष्ठा bpf_program *prog;
	पूर्णांक err;

	err = libbpf_prog_type_by_name(title, &prog_type, &attach_type);
	अगर (err) अणु
		log_err("Failed to deduct types for %s BPF program", title);
		वापस -1;
	पूर्ण

	prog = bpf_object__find_program_by_title(obj, title);
	अगर (!prog) अणु
		log_err("Failed to find %s BPF program", title);
		वापस -1;
	पूर्ण

	err = bpf_prog_attach(bpf_program__fd(prog), cgroup_fd,
			      attach_type, BPF_F_ALLOW_MULTI);
	अगर (err) अणु
		log_err("Failed to attach %s BPF program", title);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prog_detach(काष्ठा bpf_object *obj, पूर्णांक cgroup_fd, स्थिर अक्षर *title)
अणु
	क्रमागत bpf_attach_type attach_type;
	क्रमागत bpf_prog_type prog_type;
	काष्ठा bpf_program *prog;
	पूर्णांक err;

	err = libbpf_prog_type_by_name(title, &prog_type, &attach_type);
	अगर (err)
		वापस -1;

	prog = bpf_object__find_program_by_title(obj, title);
	अगर (!prog)
		वापस -1;

	err = bpf_prog_detach2(bpf_program__fd(prog), cgroup_fd,
			       attach_type);
	अगर (err)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक run_माला_लोockopt_test(काष्ठा bpf_object *obj, पूर्णांक cg_parent,
			       पूर्णांक cg_child, पूर्णांक sock_fd)
अणु
	socklen_t optlen;
	__u8 buf;
	पूर्णांक err;

	/* Set IP_TOS to the expected value (0x80). */

	buf = 0x80;
	err = setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1);
	अगर (err < 0) अणु
		log_err("Failed to call setsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	अगर (buf != 0x80) अणु
		log_err("Unexpected getsockopt 0x%x != 0x80 without BPF", buf);
		err = -1;
		जाओ detach;
	पूर्ण

	/* Attach child program and make sure it वापसs new value:
	 * - kernel:      -> 0x80
	 * - child:  0x80 -> 0x90
	 */

	err = prog_attach(obj, cg_child, "cgroup/getsockopt/child");
	अगर (err)
		जाओ detach;

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	अगर (buf != 0x90) अणु
		log_err("Unexpected getsockopt 0x%x != 0x90", buf);
		err = -1;
		जाओ detach;
	पूर्ण

	/* Attach parent program and make sure it वापसs new value:
	 * - kernel:      -> 0x80
	 * - child:  0x80 -> 0x90
	 * - parent: 0x90 -> 0xA0
	 */

	err = prog_attach(obj, cg_parent, "cgroup/getsockopt/parent");
	अगर (err)
		जाओ detach;

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	अगर (buf != 0xA0) अणु
		log_err("Unexpected getsockopt 0x%x != 0xA0", buf);
		err = -1;
		जाओ detach;
	पूर्ण

	/* Setting unexpected initial sockopt should वापस EPERM:
	 * - kernel: -> 0x40
	 * - child:  unexpected 0x40, EPERM
	 * - parent: unexpected 0x40, EPERM
	 */

	buf = 0x40;
	err = setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1);
	अगर (err < 0) अणु
		log_err("Failed to call setsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (!err) अणु
		log_err("Unexpected success from getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	/* Detach child program and make sure we still get EPERM:
	 * - kernel: -> 0x40
	 * - parent: unexpected 0x40, EPERM
	 */

	err = prog_detach(obj, cg_child, "cgroup/getsockopt/child");
	अगर (err) अणु
		log_err("Failed to detach child program");
		जाओ detach;
	पूर्ण

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (!err) अणु
		log_err("Unexpected success from getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	/* Set initial value to the one the parent program expects:
	 * - kernel:      -> 0x90
	 * - parent: 0x90 -> 0xA0
	 */

	buf = 0x90;
	err = setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1);
	अगर (err < 0) अणु
		log_err("Failed to call setsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	अगर (buf != 0xA0) अणु
		log_err("Unexpected getsockopt 0x%x != 0xA0", buf);
		err = -1;
		जाओ detach;
	पूर्ण

detach:
	prog_detach(obj, cg_child, "cgroup/getsockopt/child");
	prog_detach(obj, cg_parent, "cgroup/getsockopt/parent");

	वापस err;
पूर्ण

अटल पूर्णांक run_setsockopt_test(काष्ठा bpf_object *obj, पूर्णांक cg_parent,
			       पूर्णांक cg_child, पूर्णांक sock_fd)
अणु
	socklen_t optlen;
	__u8 buf;
	पूर्णांक err;

	/* Set IP_TOS to the expected value (0x80). */

	buf = 0x80;
	err = setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1);
	अगर (err < 0) अणु
		log_err("Failed to call setsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	अगर (buf != 0x80) अणु
		log_err("Unexpected getsockopt 0x%x != 0x80 without BPF", buf);
		err = -1;
		जाओ detach;
	पूर्ण

	/* Attach child program and make sure it adds 0x10. */

	err = prog_attach(obj, cg_child, "cgroup/setsockopt");
	अगर (err)
		जाओ detach;

	buf = 0x80;
	err = setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1);
	अगर (err < 0) अणु
		log_err("Failed to call setsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	अगर (buf != 0x80 + 0x10) अणु
		log_err("Unexpected getsockopt 0x%x != 0x80 + 0x10", buf);
		err = -1;
		जाओ detach;
	पूर्ण

	/* Attach parent program and make sure it adds another 0x10. */

	err = prog_attach(obj, cg_parent, "cgroup/setsockopt");
	अगर (err)
		जाओ detach;

	buf = 0x80;
	err = setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1);
	अगर (err < 0) अणु
		log_err("Failed to call setsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	buf = 0x00;
	optlen = 1;
	err = माला_लोockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(IP_TOS)");
		जाओ detach;
	पूर्ण

	अगर (buf != 0x80 + 2 * 0x10) अणु
		log_err("Unexpected getsockopt 0x%x != 0x80 + 2 * 0x10", buf);
		err = -1;
		जाओ detach;
	पूर्ण

detach:
	prog_detach(obj, cg_child, "cgroup/setsockopt");
	prog_detach(obj, cg_parent, "cgroup/setsockopt");

	वापस err;
पूर्ण

व्योम test_sockopt_multi(व्योम)
अणु
	काष्ठा bpf_prog_load_attr attr = अणु
		.file = "./sockopt_multi.o",
	पूर्ण;
	पूर्णांक cg_parent = -1, cg_child = -1;
	काष्ठा bpf_object *obj = शून्य;
	पूर्णांक sock_fd = -1;
	पूर्णांक err = -1;
	पूर्णांक ignored;

	cg_parent = test__join_cgroup("/parent");
	अगर (CHECK_FAIL(cg_parent < 0))
		जाओ out;

	cg_child = test__join_cgroup("/parent/child");
	अगर (CHECK_FAIL(cg_child < 0))
		जाओ out;

	err = bpf_prog_load_xattr(&attr, &obj, &ignored);
	अगर (CHECK_FAIL(err))
		जाओ out;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	अगर (CHECK_FAIL(sock_fd < 0))
		जाओ out;

	CHECK_FAIL(run_माला_लोockopt_test(obj, cg_parent, cg_child, sock_fd));
	CHECK_FAIL(run_setsockopt_test(obj, cg_parent, cg_child, sock_fd));

out:
	बंद(sock_fd);
	bpf_object__बंद(obj);
	बंद(cg_child);
	बंद(cg_parent);
पूर्ण
