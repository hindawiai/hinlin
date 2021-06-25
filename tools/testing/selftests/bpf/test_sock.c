<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <मानकपन.स>
#समावेश <unistd.h>

#समावेश <arpa/inet.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>

#समावेश <linux/filter.h>

#समावेश <bpf/bpf.h>

#समावेश "cgroup_helpers.h"
#समावेश <bpf/bpf_endian.h>
#समावेश "bpf_rlimit.h"
#समावेश "bpf_util.h"

#घोषणा CG_PATH		"/foo"
#घोषणा MAX_INSNS	512

अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];
अटल bool verbose = false;

काष्ठा sock_test अणु
	स्थिर अक्षर *descr;
	/* BPF prog properties */
	काष्ठा bpf_insn	insns[MAX_INSNS];
	क्रमागत bpf_attach_type expected_attach_type;
	क्रमागत bpf_attach_type attach_type;
	/* Socket properties */
	पूर्णांक करोमुख्य;
	पूर्णांक type;
	/* Endpoपूर्णांक to bind() to */
	स्थिर अक्षर *ip;
	अचिन्हित लघु port;
	/* Expected test result */
	क्रमागत अणु
		LOAD_REJECT,
		ATTACH_REJECT,
		BIND_REJECT,
		SUCCESS,
	पूर्ण result;
पूर्ण;

अटल काष्ठा sock_test tests[] = अणु
	अणु
		"bind4 load with invalid access: src_ip6",
		.insns = अणु
			BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
				    दुरत्व(काष्ठा bpf_sock, src_ip6[0])),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET4_POST_BIND,
		BPF_CGROUP_INET4_POST_BIND,
		0,
		0,
		शून्य,
		0,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"bind4 load with invalid access: mark",
		.insns = अणु
			BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
				    दुरत्व(काष्ठा bpf_sock, mark)),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET4_POST_BIND,
		BPF_CGROUP_INET4_POST_BIND,
		0,
		0,
		शून्य,
		0,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"bind6 load with invalid access: src_ip4",
		.insns = अणु
			BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
				    दुरत्व(काष्ठा bpf_sock, src_ip4)),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET6_POST_BIND,
		BPF_CGROUP_INET6_POST_BIND,
		0,
		0,
		शून्य,
		0,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"sock_create load with invalid access: src_port",
		.insns = अणु
			BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
				    दुरत्व(काष्ठा bpf_sock, src_port)),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET_SOCK_CREATE,
		BPF_CGROUP_INET_SOCK_CREATE,
		0,
		0,
		शून्य,
		0,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"sock_create load w/o expected_attach_type (compat mode)",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		0,
		BPF_CGROUP_INET_SOCK_CREATE,
		AF_INET,
		SOCK_STREAM,
		"127.0.0.1",
		8097,
		SUCCESS,
	पूर्ण,
	अणु
		"sock_create load w/ expected_attach_type",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET_SOCK_CREATE,
		BPF_CGROUP_INET_SOCK_CREATE,
		AF_INET,
		SOCK_STREAM,
		"127.0.0.1",
		8097,
		SUCCESS,
	पूर्ण,
	अणु
		"attach type mismatch bind4 vs bind6",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET4_POST_BIND,
		BPF_CGROUP_INET6_POST_BIND,
		0,
		0,
		शून्य,
		0,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"attach type mismatch bind6 vs bind4",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET6_POST_BIND,
		BPF_CGROUP_INET4_POST_BIND,
		0,
		0,
		शून्य,
		0,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"attach type mismatch default vs bind4",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		0,
		BPF_CGROUP_INET4_POST_BIND,
		0,
		0,
		शून्य,
		0,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"attach type mismatch bind6 vs sock_create",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET6_POST_BIND,
		BPF_CGROUP_INET_SOCK_CREATE,
		0,
		0,
		शून्य,
		0,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"bind4 reject all",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET4_POST_BIND,
		BPF_CGROUP_INET4_POST_BIND,
		AF_INET,
		SOCK_STREAM,
		"0.0.0.0",
		0,
		BIND_REJECT,
	पूर्ण,
	अणु
		"bind6 reject all",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET6_POST_BIND,
		BPF_CGROUP_INET6_POST_BIND,
		AF_INET6,
		SOCK_STREAM,
		"::",
		0,
		BIND_REJECT,
	पूर्ण,
	अणु
		"bind6 deny specific IP & port",
		.insns = अणु
			BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),

			/* अगर (ip == expected && port == expected) */
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
				    दुरत्व(काष्ठा bpf_sock, src_ip6[3])),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_7,
				    __bpf_स्थिरant_ntohl(0x00000001), 4),
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
				    दुरत्व(काष्ठा bpf_sock, src_port)),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_7, 0x2001, 2),

			/* वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_JMP_A(1),

			/* अन्यथा वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET6_POST_BIND,
		BPF_CGROUP_INET6_POST_BIND,
		AF_INET6,
		SOCK_STREAM,
		"::1",
		8193,
		BIND_REJECT,
	पूर्ण,
	अणु
		"bind4 allow specific IP & port",
		.insns = अणु
			BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),

			/* अगर (ip == expected && port == expected) */
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
				    दुरत्व(काष्ठा bpf_sock, src_ip4)),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_7,
				    __bpf_स्थिरant_ntohl(0x7F000001), 4),
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
				    दुरत्व(काष्ठा bpf_sock, src_port)),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_7, 0x1002, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET4_POST_BIND,
		BPF_CGROUP_INET4_POST_BIND,
		AF_INET,
		SOCK_STREAM,
		"127.0.0.1",
		4098,
		SUCCESS,
	पूर्ण,
	अणु
		"bind4 allow all",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET4_POST_BIND,
		BPF_CGROUP_INET4_POST_BIND,
		AF_INET,
		SOCK_STREAM,
		"0.0.0.0",
		0,
		SUCCESS,
	पूर्ण,
	अणु
		"bind6 allow all",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		BPF_CGROUP_INET6_POST_BIND,
		BPF_CGROUP_INET6_POST_BIND,
		AF_INET6,
		SOCK_STREAM,
		"::",
		0,
		SUCCESS,
	पूर्ण,
पूर्ण;

अटल माप_प्रकार probe_prog_length(स्थिर काष्ठा bpf_insn *fp)
अणु
	माप_प्रकार len;

	क्रम (len = MAX_INSNS - 1; len > 0; --len)
		अगर (fp[len].code != 0 || fp[len].imm != 0)
			अवरोध;
	वापस len + 1;
पूर्ण

अटल पूर्णांक load_sock_prog(स्थिर काष्ठा bpf_insn *prog,
			  क्रमागत bpf_attach_type attach_type)
अणु
	काष्ठा bpf_load_program_attr attr;
	पूर्णांक ret;

	स_रखो(&attr, 0, माप(काष्ठा bpf_load_program_attr));
	attr.prog_type = BPF_PROG_TYPE_CGROUP_SOCK;
	attr.expected_attach_type = attach_type;
	attr.insns = prog;
	attr.insns_cnt = probe_prog_length(attr.insns);
	attr.license = "GPL";
	attr.log_level = 2;

	ret = bpf_load_program_xattr(&attr, bpf_log_buf, BPF_LOG_BUF_SIZE);
	अगर (verbose && ret < 0)
		ख_लिखो(मानक_त्रुटि, "%s\n", bpf_log_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक attach_sock_prog(पूर्णांक cgfd, पूर्णांक progfd,
			    क्रमागत bpf_attach_type attach_type)
अणु
	वापस bpf_prog_attach(progfd, cgfd, attach_type, BPF_F_ALLOW_OVERRIDE);
पूर्ण

अटल पूर्णांक bind_sock(पूर्णांक करोमुख्य, पूर्णांक type, स्थिर अक्षर *ip, अचिन्हित लघु port)
अणु
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr_in6 *addr6;
	काष्ठा sockaddr_in *addr4;
	पूर्णांक sockfd = -1;
	socklen_t len;
	पूर्णांक err = 0;

	sockfd = socket(करोमुख्य, type, 0);
	अगर (sockfd < 0)
		जाओ err;

	स_रखो(&addr, 0, माप(addr));

	अगर (करोमुख्य == AF_INET) अणु
		len = माप(काष्ठा sockaddr_in);
		addr4 = (काष्ठा sockaddr_in *)&addr;
		addr4->sin_family = करोमुख्य;
		addr4->sin_port = htons(port);
		अगर (inet_pton(करोमुख्य, ip, (व्योम *)&addr4->sin_addr) != 1)
			जाओ err;
	पूर्ण अन्यथा अगर (करोमुख्य == AF_INET6) अणु
		len = माप(काष्ठा sockaddr_in6);
		addr6 = (काष्ठा sockaddr_in6 *)&addr;
		addr6->sin6_family = करोमुख्य;
		addr6->sin6_port = htons(port);
		अगर (inet_pton(करोमुख्य, ip, (व्योम *)&addr6->sin6_addr) != 1)
			जाओ err;
	पूर्ण अन्यथा अणु
		जाओ err;
	पूर्ण

	अगर (bind(sockfd, (स्थिर काष्ठा sockaddr *)&addr, len) == -1)
		जाओ err;

	जाओ out;
err:
	err = -1;
out:
	बंद(sockfd);
	वापस err;
पूर्ण

अटल पूर्णांक run_test_हाल(पूर्णांक cgfd, स्थिर काष्ठा sock_test *test)
अणु
	पूर्णांक progfd = -1;
	पूर्णांक err = 0;

	म_लिखो("Test case: %s .. ", test->descr);
	progfd = load_sock_prog(test->insns, test->expected_attach_type);
	अगर (progfd < 0) अणु
		अगर (test->result == LOAD_REJECT)
			जाओ out;
		अन्यथा
			जाओ err;
	पूर्ण

	अगर (attach_sock_prog(cgfd, progfd, test->attach_type) == -1) अणु
		अगर (test->result == ATTACH_REJECT)
			जाओ out;
		अन्यथा
			जाओ err;
	पूर्ण

	अगर (bind_sock(test->करोमुख्य, test->type, test->ip, test->port) == -1) अणु
		/* sys_bind() may fail क्रम dअगरferent reasons, त्रुटि_सं has to be
		 * checked to confirm that BPF program rejected it.
		 */
		अगर (test->result == BIND_REJECT && त्रुटि_सं == EPERM)
			जाओ out;
		अन्यथा
			जाओ err;
	पूर्ण


	अगर (test->result != SUCCESS)
		जाओ err;

	जाओ out;
err:
	err = -1;
out:
	/* Detaching w/o checking वापस code: best efक्रमt attempt. */
	अगर (progfd != -1)
		bpf_prog_detach(cgfd, test->attach_type);
	बंद(progfd);
	म_लिखो("[%s]\n", err ? "FAIL" : "PASS");
	वापस err;
पूर्ण

अटल पूर्णांक run_tests(पूर्णांक cgfd)
अणु
	पूर्णांक passes = 0;
	पूर्णांक fails = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tests); ++i) अणु
		अगर (run_test_हाल(cgfd, &tests[i]))
			++fails;
		अन्यथा
			++passes;
	पूर्ण
	म_लिखो("Summary: %d PASSED, %d FAILED\n", passes, fails);
	वापस fails ? -1 : 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक cgfd = -1;
	पूर्णांक err = 0;

	cgfd = cgroup_setup_and_join(CG_PATH);
	अगर (cgfd < 0)
		जाओ err;

	अगर (run_tests(cgfd))
		जाओ err;

	जाओ out;
err:
	err = -1;
out:
	बंद(cgfd);
	cleanup_cgroup_environment();
	वापस err;
पूर्ण
