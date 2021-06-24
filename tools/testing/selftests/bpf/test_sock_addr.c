<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#समावेश <arpa/inet.h>
#समावेश <netinet/in.h>
#समावेश <sys/types.h>
#समावेश <sys/select.h>
#समावेश <sys/socket.h>

#समावेश <linux/filter.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "cgroup_helpers.h"
#समावेश "bpf_rlimit.h"
#समावेश "bpf_util.h"

#अगर_अघोषित ENOTSUPP
# define ENOTSUPP 524
#पूर्ण_अगर

#घोषणा CG_PATH	"/foo"
#घोषणा CONNECT4_PROG_PATH	"./connect4_prog.o"
#घोषणा CONNECT6_PROG_PATH	"./connect6_prog.o"
#घोषणा SENDMSG4_PROG_PATH	"./sendmsg4_prog.o"
#घोषणा SENDMSG6_PROG_PATH	"./sendmsg6_prog.o"
#घोषणा RECVMSG4_PROG_PATH	"./recvmsg4_prog.o"
#घोषणा RECVMSG6_PROG_PATH	"./recvmsg6_prog.o"
#घोषणा BIND4_PROG_PATH		"./bind4_prog.o"
#घोषणा BIND6_PROG_PATH		"./bind6_prog.o"

#घोषणा SERV4_IP		"192.168.1.254"
#घोषणा SERV4_REWRITE_IP	"127.0.0.1"
#घोषणा SRC4_IP			"172.16.0.1"
#घोषणा SRC4_REWRITE_IP		"127.0.0.4"
#घोषणा SERV4_PORT		4040
#घोषणा SERV4_REWRITE_PORT	4444

#घोषणा SERV6_IP		"face:b00c:1234:5678::abcd"
#घोषणा SERV6_REWRITE_IP	"::1"
#घोषणा SERV6_V4MAPPED_IP	"::ffff:192.168.0.4"
#घोषणा SRC6_IP			"::1"
#घोषणा SRC6_REWRITE_IP		"::6"
#घोषणा WILDCARD6_IP		"::"
#घोषणा SERV6_PORT		6060
#घोषणा SERV6_REWRITE_PORT	6666

#घोषणा INET_NTOP_BUF	40

काष्ठा sock_addr_test;

प्रकार पूर्णांक (*load_fn)(स्थिर काष्ठा sock_addr_test *test);
प्रकार पूर्णांक (*info_fn)(पूर्णांक, काष्ठा sockaddr *, socklen_t *);

अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

काष्ठा sock_addr_test अणु
	स्थिर अक्षर *descr;
	/* BPF prog properties */
	load_fn loadfn;
	क्रमागत bpf_attach_type expected_attach_type;
	क्रमागत bpf_attach_type attach_type;
	/* Socket properties */
	पूर्णांक करोमुख्य;
	पूर्णांक type;
	/* IP:port pairs क्रम BPF prog to override */
	स्थिर अक्षर *requested_ip;
	अचिन्हित लघु requested_port;
	स्थिर अक्षर *expected_ip;
	अचिन्हित लघु expected_port;
	स्थिर अक्षर *expected_src_ip;
	/* Expected test result */
	क्रमागत अणु
		LOAD_REJECT,
		ATTACH_REJECT,
		ATTACH_OKAY,
		SYSCALL_EPERM,
		SYSCALL_ENOTSUPP,
		SUCCESS,
	पूर्ण expected_result;
पूर्ण;

अटल पूर्णांक bind4_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक bind6_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक connect4_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक connect6_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक sendmsg_allow_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक sendmsg_deny_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक recvmsg_allow_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक recvmsg_deny_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक sendmsg4_rw_यंत्र_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक recvmsg4_rw_c_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक sendmsg4_rw_c_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक sendmsg6_rw_यंत्र_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक recvmsg6_rw_c_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक sendmsg6_rw_c_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक sendmsg6_rw_v4mapped_prog_load(स्थिर काष्ठा sock_addr_test *test);
अटल पूर्णांक sendmsg6_rw_wildcard_prog_load(स्थिर काष्ठा sock_addr_test *test);

अटल काष्ठा sock_addr_test tests[] = अणु
	/* bind */
	अणु
		"bind4: load prog with wrong expected attach type",
		bind4_prog_load,
		BPF_CGROUP_INET6_BIND,
		BPF_CGROUP_INET4_BIND,
		AF_INET,
		SOCK_STREAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"bind4: attach prog with wrong attach type",
		bind4_prog_load,
		BPF_CGROUP_INET4_BIND,
		BPF_CGROUP_INET6_BIND,
		AF_INET,
		SOCK_STREAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"bind4: rewrite IP & TCP port in",
		bind4_prog_load,
		BPF_CGROUP_INET4_BIND,
		BPF_CGROUP_INET4_BIND,
		AF_INET,
		SOCK_STREAM,
		SERV4_IP,
		SERV4_PORT,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		शून्य,
		SUCCESS,
	पूर्ण,
	अणु
		"bind4: rewrite IP & UDP port in",
		bind4_prog_load,
		BPF_CGROUP_INET4_BIND,
		BPF_CGROUP_INET4_BIND,
		AF_INET,
		SOCK_DGRAM,
		SERV4_IP,
		SERV4_PORT,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		शून्य,
		SUCCESS,
	पूर्ण,
	अणु
		"bind6: load prog with wrong expected attach type",
		bind6_prog_load,
		BPF_CGROUP_INET4_BIND,
		BPF_CGROUP_INET6_BIND,
		AF_INET6,
		SOCK_STREAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"bind6: attach prog with wrong attach type",
		bind6_prog_load,
		BPF_CGROUP_INET6_BIND,
		BPF_CGROUP_INET4_BIND,
		AF_INET,
		SOCK_STREAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"bind6: rewrite IP & TCP port in",
		bind6_prog_load,
		BPF_CGROUP_INET6_BIND,
		BPF_CGROUP_INET6_BIND,
		AF_INET6,
		SOCK_STREAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		शून्य,
		SUCCESS,
	पूर्ण,
	अणु
		"bind6: rewrite IP & UDP port in",
		bind6_prog_load,
		BPF_CGROUP_INET6_BIND,
		BPF_CGROUP_INET6_BIND,
		AF_INET6,
		SOCK_DGRAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		शून्य,
		SUCCESS,
	पूर्ण,

	/* connect */
	अणु
		"connect4: load prog with wrong expected attach type",
		connect4_prog_load,
		BPF_CGROUP_INET6_CONNECT,
		BPF_CGROUP_INET4_CONNECT,
		AF_INET,
		SOCK_STREAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"connect4: attach prog with wrong attach type",
		connect4_prog_load,
		BPF_CGROUP_INET4_CONNECT,
		BPF_CGROUP_INET6_CONNECT,
		AF_INET,
		SOCK_STREAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"connect4: rewrite IP & TCP port",
		connect4_prog_load,
		BPF_CGROUP_INET4_CONNECT,
		BPF_CGROUP_INET4_CONNECT,
		AF_INET,
		SOCK_STREAM,
		SERV4_IP,
		SERV4_PORT,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		SRC4_REWRITE_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"connect4: rewrite IP & UDP port",
		connect4_prog_load,
		BPF_CGROUP_INET4_CONNECT,
		BPF_CGROUP_INET4_CONNECT,
		AF_INET,
		SOCK_DGRAM,
		SERV4_IP,
		SERV4_PORT,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		SRC4_REWRITE_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"connect6: load prog with wrong expected attach type",
		connect6_prog_load,
		BPF_CGROUP_INET4_CONNECT,
		BPF_CGROUP_INET6_CONNECT,
		AF_INET6,
		SOCK_STREAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"connect6: attach prog with wrong attach type",
		connect6_prog_load,
		BPF_CGROUP_INET6_CONNECT,
		BPF_CGROUP_INET4_CONNECT,
		AF_INET,
		SOCK_STREAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"connect6: rewrite IP & TCP port",
		connect6_prog_load,
		BPF_CGROUP_INET6_CONNECT,
		BPF_CGROUP_INET6_CONNECT,
		AF_INET6,
		SOCK_STREAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SRC6_REWRITE_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"connect6: rewrite IP & UDP port",
		connect6_prog_load,
		BPF_CGROUP_INET6_CONNECT,
		BPF_CGROUP_INET6_CONNECT,
		AF_INET6,
		SOCK_DGRAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SRC6_REWRITE_IP,
		SUCCESS,
	पूर्ण,

	/* sendmsg */
	अणु
		"sendmsg4: load prog with wrong expected attach type",
		sendmsg4_rw_यंत्र_prog_load,
		BPF_CGROUP_UDP6_SENDMSG,
		BPF_CGROUP_UDP4_SENDMSG,
		AF_INET,
		SOCK_DGRAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"sendmsg4: attach prog with wrong attach type",
		sendmsg4_rw_यंत्र_prog_load,
		BPF_CGROUP_UDP4_SENDMSG,
		BPF_CGROUP_UDP6_SENDMSG,
		AF_INET,
		SOCK_DGRAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"sendmsg4: rewrite IP & port (asm)",
		sendmsg4_rw_यंत्र_prog_load,
		BPF_CGROUP_UDP4_SENDMSG,
		BPF_CGROUP_UDP4_SENDMSG,
		AF_INET,
		SOCK_DGRAM,
		SERV4_IP,
		SERV4_PORT,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		SRC4_REWRITE_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"sendmsg4: rewrite IP & port (C)",
		sendmsg4_rw_c_prog_load,
		BPF_CGROUP_UDP4_SENDMSG,
		BPF_CGROUP_UDP4_SENDMSG,
		AF_INET,
		SOCK_DGRAM,
		SERV4_IP,
		SERV4_PORT,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		SRC4_REWRITE_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"sendmsg4: deny call",
		sendmsg_deny_prog_load,
		BPF_CGROUP_UDP4_SENDMSG,
		BPF_CGROUP_UDP4_SENDMSG,
		AF_INET,
		SOCK_DGRAM,
		SERV4_IP,
		SERV4_PORT,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		SRC4_REWRITE_IP,
		SYSCALL_EPERM,
	पूर्ण,
	अणु
		"sendmsg6: load prog with wrong expected attach type",
		sendmsg6_rw_यंत्र_prog_load,
		BPF_CGROUP_UDP4_SENDMSG,
		BPF_CGROUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGRAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"sendmsg6: attach prog with wrong attach type",
		sendmsg6_rw_यंत्र_prog_load,
		BPF_CGROUP_UDP6_SENDMSG,
		BPF_CGROUP_UDP4_SENDMSG,
		AF_INET6,
		SOCK_DGRAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		ATTACH_REJECT,
	पूर्ण,
	अणु
		"sendmsg6: rewrite IP & port (asm)",
		sendmsg6_rw_यंत्र_prog_load,
		BPF_CGROUP_UDP6_SENDMSG,
		BPF_CGROUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGRAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SRC6_REWRITE_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"sendmsg6: rewrite IP & port (C)",
		sendmsg6_rw_c_prog_load,
		BPF_CGROUP_UDP6_SENDMSG,
		BPF_CGROUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGRAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SRC6_REWRITE_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"sendmsg6: IPv4-mapped IPv6",
		sendmsg6_rw_v4mapped_prog_load,
		BPF_CGROUP_UDP6_SENDMSG,
		BPF_CGROUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGRAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SRC6_REWRITE_IP,
		SYSCALL_ENOTSUPP,
	पूर्ण,
	अणु
		"sendmsg6: set dst IP = [::] (BSD'ism)",
		sendmsg6_rw_wildcard_prog_load,
		BPF_CGROUP_UDP6_SENDMSG,
		BPF_CGROUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGRAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SRC6_REWRITE_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"sendmsg6: preserve dst IP = [::] (BSD'ism)",
		sendmsg_allow_prog_load,
		BPF_CGROUP_UDP6_SENDMSG,
		BPF_CGROUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGRAM,
		WILDCARD6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_PORT,
		SRC6_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"sendmsg6: deny call",
		sendmsg_deny_prog_load,
		BPF_CGROUP_UDP6_SENDMSG,
		BPF_CGROUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGRAM,
		SERV6_IP,
		SERV6_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SRC6_REWRITE_IP,
		SYSCALL_EPERM,
	पूर्ण,

	/* recvmsg */
	अणु
		"recvmsg4: return code ok",
		recvmsg_allow_prog_load,
		BPF_CGROUP_UDP4_RECVMSG,
		BPF_CGROUP_UDP4_RECVMSG,
		AF_INET,
		SOCK_DGRAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		ATTACH_OKAY,
	पूर्ण,
	अणु
		"recvmsg4: return code !ok",
		recvmsg_deny_prog_load,
		BPF_CGROUP_UDP4_RECVMSG,
		BPF_CGROUP_UDP4_RECVMSG,
		AF_INET,
		SOCK_DGRAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"recvmsg6: return code ok",
		recvmsg_allow_prog_load,
		BPF_CGROUP_UDP6_RECVMSG,
		BPF_CGROUP_UDP6_RECVMSG,
		AF_INET6,
		SOCK_DGRAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		ATTACH_OKAY,
	पूर्ण,
	अणु
		"recvmsg6: return code !ok",
		recvmsg_deny_prog_load,
		BPF_CGROUP_UDP6_RECVMSG,
		BPF_CGROUP_UDP6_RECVMSG,
		AF_INET6,
		SOCK_DGRAM,
		शून्य,
		0,
		शून्य,
		0,
		शून्य,
		LOAD_REJECT,
	पूर्ण,
	अणु
		"recvmsg4: rewrite IP & port (C)",
		recvmsg4_rw_c_prog_load,
		BPF_CGROUP_UDP4_RECVMSG,
		BPF_CGROUP_UDP4_RECVMSG,
		AF_INET,
		SOCK_DGRAM,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		SERV4_REWRITE_IP,
		SERV4_REWRITE_PORT,
		SERV4_IP,
		SUCCESS,
	पूर्ण,
	अणु
		"recvmsg6: rewrite IP & port (C)",
		recvmsg6_rw_c_prog_load,
		BPF_CGROUP_UDP6_RECVMSG,
		BPF_CGROUP_UDP6_RECVMSG,
		AF_INET6,
		SOCK_DGRAM,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SERV6_REWRITE_IP,
		SERV6_REWRITE_PORT,
		SERV6_IP,
		SUCCESS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mk_sockaddr(पूर्णांक करोमुख्य, स्थिर अक्षर *ip, अचिन्हित लघु port,
		       काष्ठा sockaddr *addr, socklen_t addr_len)
अणु
	काष्ठा sockaddr_in6 *addr6;
	काष्ठा sockaddr_in *addr4;

	अगर (करोमुख्य != AF_INET && करोमुख्य != AF_INET6) अणु
		log_err("Unsupported address family");
		वापस -1;
	पूर्ण

	स_रखो(addr, 0, addr_len);

	अगर (करोमुख्य == AF_INET) अणु
		अगर (addr_len < माप(काष्ठा sockaddr_in))
			वापस -1;
		addr4 = (काष्ठा sockaddr_in *)addr;
		addr4->sin_family = करोमुख्य;
		addr4->sin_port = htons(port);
		अगर (inet_pton(करोमुख्य, ip, (व्योम *)&addr4->sin_addr) != 1) अणु
			log_err("Invalid IPv4: %s", ip);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अगर (करोमुख्य == AF_INET6) अणु
		अगर (addr_len < माप(काष्ठा sockaddr_in6))
			वापस -1;
		addr6 = (काष्ठा sockaddr_in6 *)addr;
		addr6->sin6_family = करोमुख्य;
		addr6->sin6_port = htons(port);
		अगर (inet_pton(करोमुख्य, ip, (व्योम *)&addr6->sin6_addr) != 1) अणु
			log_err("Invalid IPv6: %s", ip);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक load_insns(स्थिर काष्ठा sock_addr_test *test,
		      स्थिर काष्ठा bpf_insn *insns, माप_प्रकार insns_cnt)
अणु
	काष्ठा bpf_load_program_attr load_attr;
	पूर्णांक ret;

	स_रखो(&load_attr, 0, माप(काष्ठा bpf_load_program_attr));
	load_attr.prog_type = BPF_PROG_TYPE_CGROUP_SOCK_ADDR;
	load_attr.expected_attach_type = test->expected_attach_type;
	load_attr.insns = insns;
	load_attr.insns_cnt = insns_cnt;
	load_attr.license = "GPL";

	ret = bpf_load_program_xattr(&load_attr, bpf_log_buf, BPF_LOG_BUF_SIZE);
	अगर (ret < 0 && test->expected_result != LOAD_REJECT) अणु
		log_err(">>> Loading program error.\n"
			">>> Verifier output:\n%s\n-------\n", bpf_log_buf);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक load_path(स्थिर काष्ठा sock_addr_test *test, स्थिर अक्षर *path)
अणु
	काष्ठा bpf_prog_load_attr attr;
	काष्ठा bpf_object *obj;
	पूर्णांक prog_fd;

	स_रखो(&attr, 0, माप(काष्ठा bpf_prog_load_attr));
	attr.file = path;
	attr.prog_type = BPF_PROG_TYPE_CGROUP_SOCK_ADDR;
	attr.expected_attach_type = test->expected_attach_type;
	attr.prog_flags = BPF_F_TEST_RND_HI32;

	अगर (bpf_prog_load_xattr(&attr, &obj, &prog_fd)) अणु
		अगर (test->expected_result != LOAD_REJECT)
			log_err(">>> Loading program (%s) error.\n", path);
		वापस -1;
	पूर्ण

	वापस prog_fd;
पूर्ण

अटल पूर्णांक bind4_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस load_path(test, BIND4_PROG_PATH);
पूर्ण

अटल पूर्णांक bind6_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस load_path(test, BIND6_PROG_PATH);
पूर्ण

अटल पूर्णांक connect4_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस load_path(test, CONNECT4_PROG_PATH);
पूर्ण

अटल पूर्णांक connect6_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस load_path(test, CONNECT6_PROG_PATH);
पूर्ण

अटल पूर्णांक xmsg_ret_only_prog_load(स्थिर काष्ठा sock_addr_test *test,
				   पूर्णांक32_t rc)
अणु
	काष्ठा bpf_insn insns[] = अणु
		/* वापस rc */
		BPF_MOV64_IMM(BPF_REG_0, rc),
		BPF_EXIT_INSN(),
	पूर्ण;
	वापस load_insns(test, insns, माप(insns) / माप(काष्ठा bpf_insn));
पूर्ण

अटल पूर्णांक sendmsg_allow_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस xmsg_ret_only_prog_load(test, /*rc*/ 1);
पूर्ण

अटल पूर्णांक sendmsg_deny_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस xmsg_ret_only_prog_load(test, /*rc*/ 0);
पूर्ण

अटल पूर्णांक recvmsg_allow_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस xmsg_ret_only_prog_load(test, /*rc*/ 1);
पूर्ण

अटल पूर्णांक recvmsg_deny_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस xmsg_ret_only_prog_load(test, /*rc*/ 0);
पूर्ण

अटल पूर्णांक sendmsg4_rw_यंत्र_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	काष्ठा sockaddr_in dst4_rw_addr;
	काष्ठा in_addr src4_rw_ip;

	अगर (inet_pton(AF_INET, SRC4_REWRITE_IP, (व्योम *)&src4_rw_ip) != 1) अणु
		log_err("Invalid IPv4: %s", SRC4_REWRITE_IP);
		वापस -1;
	पूर्ण

	अगर (mk_sockaddr(AF_INET, SERV4_REWRITE_IP, SERV4_REWRITE_PORT,
			(काष्ठा sockaddr *)&dst4_rw_addr,
			माप(dst4_rw_addr)) == -1)
		वापस -1;

	काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),

		/* अगर (sk.family == AF_INET && */
		BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
			    दुरत्व(काष्ठा bpf_sock_addr, family)),
		BPF_JMP_IMM(BPF_JNE, BPF_REG_7, AF_INET, 8),

		/*     sk.type == SOCK_DGRAM)  अणु */
		BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
			    दुरत्व(काष्ठा bpf_sock_addr, type)),
		BPF_JMP_IMM(BPF_JNE, BPF_REG_7, SOCK_DGRAM, 6),

		/*      msg_src_ip4 = src4_rw_ip */
		BPF_MOV32_IMM(BPF_REG_7, src4_rw_ip.s_addr),
		BPF_STX_MEM(BPF_W, BPF_REG_6, BPF_REG_7,
			    दुरत्व(काष्ठा bpf_sock_addr, msg_src_ip4)),

		/*      user_ip4 = dst4_rw_addr.sin_addr */
		BPF_MOV32_IMM(BPF_REG_7, dst4_rw_addr.sin_addr.s_addr),
		BPF_STX_MEM(BPF_W, BPF_REG_6, BPF_REG_7,
			    दुरत्व(काष्ठा bpf_sock_addr, user_ip4)),

		/*      user_port = dst4_rw_addr.sin_port */
		BPF_MOV32_IMM(BPF_REG_7, dst4_rw_addr.sin_port),
		BPF_STX_MEM(BPF_W, BPF_REG_6, BPF_REG_7,
			    दुरत्व(काष्ठा bpf_sock_addr, user_port)),
		/* पूर्ण */

		/* वापस 1 */
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण;

	वापस load_insns(test, insns, माप(insns) / माप(काष्ठा bpf_insn));
पूर्ण

अटल पूर्णांक recvmsg4_rw_c_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस load_path(test, RECVMSG4_PROG_PATH);
पूर्ण

अटल पूर्णांक sendmsg4_rw_c_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस load_path(test, SENDMSG4_PROG_PATH);
पूर्ण

अटल पूर्णांक sendmsg6_rw_dst_यंत्र_prog_load(स्थिर काष्ठा sock_addr_test *test,
					 स्थिर अक्षर *rw_dst_ip)
अणु
	काष्ठा sockaddr_in6 dst6_rw_addr;
	काष्ठा in6_addr src6_rw_ip;

	अगर (inet_pton(AF_INET6, SRC6_REWRITE_IP, (व्योम *)&src6_rw_ip) != 1) अणु
		log_err("Invalid IPv6: %s", SRC6_REWRITE_IP);
		वापस -1;
	पूर्ण

	अगर (mk_sockaddr(AF_INET6, rw_dst_ip, SERV6_REWRITE_PORT,
			(काष्ठा sockaddr *)&dst6_rw_addr,
			माप(dst6_rw_addr)) == -1)
		वापस -1;

	काष्ठा bpf_insn insns[] = अणु
		BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),

		/* अगर (sk.family == AF_INET6) अणु */
		BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_6,
			    दुरत्व(काष्ठा bpf_sock_addr, family)),
		BPF_JMP_IMM(BPF_JNE, BPF_REG_7, AF_INET6, 18),

#घोषणा STORE_IPV6_WORD_N(DST, SRC, N)					       \
		BPF_MOV32_IMM(BPF_REG_7, SRC[N]),			       \
		BPF_STX_MEM(BPF_W, BPF_REG_6, BPF_REG_7,		       \
			    दुरत्व(काष्ठा bpf_sock_addr, DST[N]))

#घोषणा STORE_IPV6(DST, SRC)						       \
		STORE_IPV6_WORD_N(DST, SRC, 0),				       \
		STORE_IPV6_WORD_N(DST, SRC, 1),				       \
		STORE_IPV6_WORD_N(DST, SRC, 2),				       \
		STORE_IPV6_WORD_N(DST, SRC, 3)

		STORE_IPV6(msg_src_ip6, src6_rw_ip.s6_addr32),
		STORE_IPV6(user_ip6, dst6_rw_addr.sin6_addr.s6_addr32),

		/*      user_port = dst6_rw_addr.sin6_port */
		BPF_MOV32_IMM(BPF_REG_7, dst6_rw_addr.sin6_port),
		BPF_STX_MEM(BPF_W, BPF_REG_6, BPF_REG_7,
			    दुरत्व(काष्ठा bpf_sock_addr, user_port)),

		/* पूर्ण */

		/* वापस 1 */
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण;

	वापस load_insns(test, insns, माप(insns) / माप(काष्ठा bpf_insn));
पूर्ण

अटल पूर्णांक sendmsg6_rw_यंत्र_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस sendmsg6_rw_dst_यंत्र_prog_load(test, SERV6_REWRITE_IP);
पूर्ण

अटल पूर्णांक recvmsg6_rw_c_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस load_path(test, RECVMSG6_PROG_PATH);
पूर्ण

अटल पूर्णांक sendmsg6_rw_v4mapped_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस sendmsg6_rw_dst_यंत्र_prog_load(test, SERV6_V4MAPPED_IP);
पूर्ण

अटल पूर्णांक sendmsg6_rw_wildcard_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस sendmsg6_rw_dst_यंत्र_prog_load(test, WILDCARD6_IP);
पूर्ण

अटल पूर्णांक sendmsg6_rw_c_prog_load(स्थिर काष्ठा sock_addr_test *test)
अणु
	वापस load_path(test, SENDMSG6_PROG_PATH);
पूर्ण

अटल पूर्णांक cmp_addr(स्थिर काष्ठा sockaddr_storage *addr1,
		    स्थिर काष्ठा sockaddr_storage *addr2, पूर्णांक cmp_port)
अणु
	स्थिर काष्ठा sockaddr_in *four1, *four2;
	स्थिर काष्ठा sockaddr_in6 *six1, *six2;

	अगर (addr1->ss_family != addr2->ss_family)
		वापस -1;

	अगर (addr1->ss_family == AF_INET) अणु
		four1 = (स्थिर काष्ठा sockaddr_in *)addr1;
		four2 = (स्थिर काष्ठा sockaddr_in *)addr2;
		वापस !((four1->sin_port == four2->sin_port || !cmp_port) &&
			 four1->sin_addr.s_addr == four2->sin_addr.s_addr);
	पूर्ण अन्यथा अगर (addr1->ss_family == AF_INET6) अणु
		six1 = (स्थिर काष्ठा sockaddr_in6 *)addr1;
		six2 = (स्थिर काष्ठा sockaddr_in6 *)addr2;
		वापस !((six1->sin6_port == six2->sin6_port || !cmp_port) &&
			 !स_भेद(&six1->sin6_addr, &six2->sin6_addr,
				 माप(काष्ठा in6_addr)));
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक cmp_sock_addr(info_fn fn, पूर्णांक sock1,
			 स्थिर काष्ठा sockaddr_storage *addr2, पूर्णांक cmp_port)
अणु
	काष्ठा sockaddr_storage addr1;
	socklen_t len1 = माप(addr1);

	स_रखो(&addr1, 0, len1);
	अगर (fn(sock1, (काष्ठा sockaddr *)&addr1, (socklen_t *)&len1) != 0)
		वापस -1;

	वापस cmp_addr(&addr1, addr2, cmp_port);
पूर्ण

अटल पूर्णांक cmp_local_ip(पूर्णांक sock1, स्थिर काष्ठा sockaddr_storage *addr2)
अणु
	वापस cmp_sock_addr(माला_लोockname, sock1, addr2, /*cmp_port*/ 0);
पूर्ण

अटल पूर्णांक cmp_local_addr(पूर्णांक sock1, स्थिर काष्ठा sockaddr_storage *addr2)
अणु
	वापस cmp_sock_addr(माला_लोockname, sock1, addr2, /*cmp_port*/ 1);
पूर्ण

अटल पूर्णांक cmp_peer_addr(पूर्णांक sock1, स्थिर काष्ठा sockaddr_storage *addr2)
अणु
	वापस cmp_sock_addr(getpeername, sock1, addr2, /*cmp_port*/ 1);
पूर्ण

अटल पूर्णांक start_server(पूर्णांक type, स्थिर काष्ठा sockaddr_storage *addr,
			socklen_t addr_len)
अणु
	पूर्णांक fd;

	fd = socket(addr->ss_family, type, 0);
	अगर (fd == -1) अणु
		log_err("Failed to create server socket");
		जाओ out;
	पूर्ण

	अगर (bind(fd, (स्थिर काष्ठा sockaddr *)addr, addr_len) == -1) अणु
		log_err("Failed to bind server socket");
		जाओ बंद_out;
	पूर्ण

	अगर (type == SOCK_STREAM) अणु
		अगर (listen(fd, 128) == -1) अणु
			log_err("Failed to listen on server socket");
			जाओ बंद_out;
		पूर्ण
	पूर्ण

	जाओ out;
बंद_out:
	बंद(fd);
	fd = -1;
out:
	वापस fd;
पूर्ण

अटल पूर्णांक connect_to_server(पूर्णांक type, स्थिर काष्ठा sockaddr_storage *addr,
			     socklen_t addr_len)
अणु
	पूर्णांक करोमुख्य;
	पूर्णांक fd = -1;

	करोमुख्य = addr->ss_family;

	अगर (करोमुख्य != AF_INET && करोमुख्य != AF_INET6) अणु
		log_err("Unsupported address family");
		जाओ err;
	पूर्ण

	fd = socket(करोमुख्य, type, 0);
	अगर (fd == -1) अणु
		log_err("Failed to create client socket");
		जाओ err;
	पूर्ण

	अगर (connect(fd, (स्थिर काष्ठा sockaddr *)addr, addr_len) == -1) अणु
		log_err("Fail to connect to server");
		जाओ err;
	पूर्ण

	जाओ out;
err:
	बंद(fd);
	fd = -1;
out:
	वापस fd;
पूर्ण

पूर्णांक init_pktinfo(पूर्णांक करोमुख्य, काष्ठा cmsghdr *cmsg)
अणु
	काष्ठा in6_pktinfo *pktinfo6;
	काष्ठा in_pktinfo *pktinfo4;

	अगर (करोमुख्य == AF_INET) अणु
		cmsg->cmsg_level = SOL_IP;
		cmsg->cmsg_type = IP_PKTINFO;
		cmsg->cmsg_len = CMSG_LEN(माप(काष्ठा in_pktinfo));
		pktinfo4 = (काष्ठा in_pktinfo *)CMSG_DATA(cmsg);
		स_रखो(pktinfo4, 0, माप(काष्ठा in_pktinfo));
		अगर (inet_pton(करोमुख्य, SRC4_IP,
			      (व्योम *)&pktinfo4->ipi_spec_dst) != 1)
			वापस -1;
	पूर्ण अन्यथा अगर (करोमुख्य == AF_INET6) अणु
		cmsg->cmsg_level = SOL_IPV6;
		cmsg->cmsg_type = IPV6_PKTINFO;
		cmsg->cmsg_len = CMSG_LEN(माप(काष्ठा in6_pktinfo));
		pktinfo6 = (काष्ठा in6_pktinfo *)CMSG_DATA(cmsg);
		स_रखो(pktinfo6, 0, माप(काष्ठा in6_pktinfo));
		अगर (inet_pton(करोमुख्य, SRC6_IP,
			      (व्योम *)&pktinfo6->ipi6_addr) != 1)
			वापस -1;
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sendmsg_to_server(पूर्णांक type, स्थिर काष्ठा sockaddr_storage *addr,
			     socklen_t addr_len, पूर्णांक set_cmsg, पूर्णांक flags,
			     पूर्णांक *syscall_err)
अणु
	जोड़ अणु
		अक्षर buf[CMSG_SPACE(माप(काष्ठा in6_pktinfo))];
		काष्ठा cmsghdr align;
	पूर्ण control6;
	जोड़ अणु
		अक्षर buf[CMSG_SPACE(माप(काष्ठा in_pktinfo))];
		काष्ठा cmsghdr align;
	पूर्ण control4;
	काष्ठा msghdr hdr;
	काष्ठा iovec iov;
	अक्षर data = 'a';
	पूर्णांक करोमुख्य;
	पूर्णांक fd = -1;

	करोमुख्य = addr->ss_family;

	अगर (करोमुख्य != AF_INET && करोमुख्य != AF_INET6) अणु
		log_err("Unsupported address family");
		जाओ err;
	पूर्ण

	fd = socket(करोमुख्य, type, 0);
	अगर (fd == -1) अणु
		log_err("Failed to create client socket");
		जाओ err;
	पूर्ण

	स_रखो(&iov, 0, माप(iov));
	iov.iov_base = &data;
	iov.iov_len = माप(data);

	स_रखो(&hdr, 0, माप(hdr));
	hdr.msg_name = (व्योम *)addr;
	hdr.msg_namelen = addr_len;
	hdr.msg_iov = &iov;
	hdr.msg_iovlen = 1;

	अगर (set_cmsg) अणु
		अगर (करोमुख्य == AF_INET) अणु
			hdr.msg_control = &control4;
			hdr.msg_controllen = माप(control4.buf);
		पूर्ण अन्यथा अगर (करोमुख्य == AF_INET6) अणु
			hdr.msg_control = &control6;
			hdr.msg_controllen = माप(control6.buf);
		पूर्ण
		अगर (init_pktinfo(करोमुख्य, CMSG_FIRSTHDR(&hdr))) अणु
			log_err("Fail to init pktinfo");
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (sendmsg(fd, &hdr, flags) != माप(data)) अणु
		log_err("Fail to send message to server");
		*syscall_err = त्रुटि_सं;
		जाओ err;
	पूर्ण

	जाओ out;
err:
	बंद(fd);
	fd = -1;
out:
	वापस fd;
पूर्ण

अटल पूर्णांक fastconnect_to_server(स्थिर काष्ठा sockaddr_storage *addr,
				 socklen_t addr_len)
अणु
	पूर्णांक sendmsg_err;

	वापस sendmsg_to_server(SOCK_STREAM, addr, addr_len, /*set_cmsg*/0,
				 MSG_FASTOPEN, &sendmsg_err);
पूर्ण

अटल पूर्णांक recvmsg_from_client(पूर्णांक sockfd, काष्ठा sockaddr_storage *src_addr)
अणु
	काष्ठा समयval tv;
	काष्ठा msghdr hdr;
	काष्ठा iovec iov;
	अक्षर data[64];
	fd_set rfds;

	FD_ZERO(&rfds);
	FD_SET(sockfd, &rfds);

	tv.tv_sec = 2;
	tv.tv_usec = 0;

	अगर (select(sockfd + 1, &rfds, शून्य, शून्य, &tv) <= 0 ||
	    !FD_ISSET(sockfd, &rfds))
		वापस -1;

	स_रखो(&iov, 0, माप(iov));
	iov.iov_base = data;
	iov.iov_len = माप(data);

	स_रखो(&hdr, 0, माप(hdr));
	hdr.msg_name = src_addr;
	hdr.msg_namelen = माप(काष्ठा sockaddr_storage);
	hdr.msg_iov = &iov;
	hdr.msg_iovlen = 1;

	वापस recvmsg(sockfd, &hdr, 0);
पूर्ण

अटल पूर्णांक init_addrs(स्थिर काष्ठा sock_addr_test *test,
		      काष्ठा sockaddr_storage *requested_addr,
		      काष्ठा sockaddr_storage *expected_addr,
		      काष्ठा sockaddr_storage *expected_src_addr)
अणु
	socklen_t addr_len = माप(काष्ठा sockaddr_storage);

	अगर (mk_sockaddr(test->करोमुख्य, test->expected_ip, test->expected_port,
			(काष्ठा sockaddr *)expected_addr, addr_len) == -1)
		जाओ err;

	अगर (mk_sockaddr(test->करोमुख्य, test->requested_ip, test->requested_port,
			(काष्ठा sockaddr *)requested_addr, addr_len) == -1)
		जाओ err;

	अगर (test->expected_src_ip &&
	    mk_sockaddr(test->करोमुख्य, test->expected_src_ip, 0,
			(काष्ठा sockaddr *)expected_src_addr, addr_len) == -1)
		जाओ err;

	वापस 0;
err:
	वापस -1;
पूर्ण

अटल पूर्णांक run_bind_test_हाल(स्थिर काष्ठा sock_addr_test *test)
अणु
	socklen_t addr_len = माप(काष्ठा sockaddr_storage);
	काष्ठा sockaddr_storage requested_addr;
	काष्ठा sockaddr_storage expected_addr;
	पूर्णांक clientfd = -1;
	पूर्णांक servfd = -1;
	पूर्णांक err = 0;

	अगर (init_addrs(test, &requested_addr, &expected_addr, शून्य))
		जाओ err;

	servfd = start_server(test->type, &requested_addr, addr_len);
	अगर (servfd == -1)
		जाओ err;

	अगर (cmp_local_addr(servfd, &expected_addr))
		जाओ err;

	/* Try to connect to server just in हाल */
	clientfd = connect_to_server(test->type, &expected_addr, addr_len);
	अगर (clientfd == -1)
		जाओ err;

	जाओ out;
err:
	err = -1;
out:
	बंद(clientfd);
	बंद(servfd);
	वापस err;
पूर्ण

अटल पूर्णांक run_connect_test_हाल(स्थिर काष्ठा sock_addr_test *test)
अणु
	socklen_t addr_len = माप(काष्ठा sockaddr_storage);
	काष्ठा sockaddr_storage expected_src_addr;
	काष्ठा sockaddr_storage requested_addr;
	काष्ठा sockaddr_storage expected_addr;
	पूर्णांक clientfd = -1;
	पूर्णांक servfd = -1;
	पूर्णांक err = 0;

	अगर (init_addrs(test, &requested_addr, &expected_addr,
		       &expected_src_addr))
		जाओ err;

	/* Prepare server to connect to */
	servfd = start_server(test->type, &expected_addr, addr_len);
	अगर (servfd == -1)
		जाओ err;

	clientfd = connect_to_server(test->type, &requested_addr, addr_len);
	अगर (clientfd == -1)
		जाओ err;

	/* Make sure src and dst addrs were overridden properly */
	अगर (cmp_peer_addr(clientfd, &expected_addr))
		जाओ err;

	अगर (cmp_local_ip(clientfd, &expected_src_addr))
		जाओ err;

	अगर (test->type == SOCK_STREAM) अणु
		/* Test TCP Fast Open scenario */
		clientfd = fastconnect_to_server(&requested_addr, addr_len);
		अगर (clientfd == -1)
			जाओ err;

		/* Make sure src and dst addrs were overridden properly */
		अगर (cmp_peer_addr(clientfd, &expected_addr))
			जाओ err;

		अगर (cmp_local_ip(clientfd, &expected_src_addr))
			जाओ err;
	पूर्ण

	जाओ out;
err:
	err = -1;
out:
	बंद(clientfd);
	बंद(servfd);
	वापस err;
पूर्ण

अटल पूर्णांक run_xmsg_test_हाल(स्थिर काष्ठा sock_addr_test *test, पूर्णांक max_cmsg)
अणु
	socklen_t addr_len = माप(काष्ठा sockaddr_storage);
	काष्ठा sockaddr_storage expected_addr;
	काष्ठा sockaddr_storage server_addr;
	काष्ठा sockaddr_storage sendmsg_addr;
	काष्ठा sockaddr_storage recvmsg_addr;
	पूर्णांक clientfd = -1;
	पूर्णांक servfd = -1;
	पूर्णांक set_cmsg;
	पूर्णांक err = 0;

	अगर (test->type != SOCK_DGRAM)
		जाओ err;

	अगर (init_addrs(test, &sendmsg_addr, &server_addr, &expected_addr))
		जाओ err;

	/* Prepare server to sendmsg to */
	servfd = start_server(test->type, &server_addr, addr_len);
	अगर (servfd == -1)
		जाओ err;

	क्रम (set_cmsg = 0; set_cmsg <= max_cmsg; ++set_cmsg) अणु
		अगर (clientfd >= 0)
			बंद(clientfd);

		clientfd = sendmsg_to_server(test->type, &sendmsg_addr,
					     addr_len, set_cmsg, /*flags*/0,
					     &err);
		अगर (err)
			जाओ out;
		अन्यथा अगर (clientfd == -1)
			जाओ err;

		/* Try to receive message on server instead of using
		 * getpeername(2) on client socket, to check that client's
		 * destination address was rewritten properly, since
		 * getpeername(2) करोesn't work with unconnected datagram
		 * sockets.
		 *
		 * Get source address from recvmsg(2) as well to make sure
		 * source was rewritten properly: माला_लोockname(2) can't be used
		 * since socket is unconnected and source defined क्रम one
		 * specअगरic packet may dअगरfer from the one used by शेष and
		 * वापसed by माला_लोockname(2).
		 */
		अगर (recvmsg_from_client(servfd, &recvmsg_addr) == -1)
			जाओ err;

		अगर (cmp_addr(&recvmsg_addr, &expected_addr, /*cmp_port*/0))
			जाओ err;
	पूर्ण

	जाओ out;
err:
	err = -1;
out:
	बंद(clientfd);
	बंद(servfd);
	वापस err;
पूर्ण

अटल पूर्णांक run_test_हाल(पूर्णांक cgfd, स्थिर काष्ठा sock_addr_test *test)
अणु
	पूर्णांक progfd = -1;
	पूर्णांक err = 0;

	म_लिखो("Test case: %s .. ", test->descr);

	progfd = test->loadfn(test);
	अगर (test->expected_result == LOAD_REJECT && progfd < 0)
		जाओ out;
	अन्यथा अगर (test->expected_result == LOAD_REJECT || progfd < 0)
		जाओ err;

	err = bpf_prog_attach(progfd, cgfd, test->attach_type,
			      BPF_F_ALLOW_OVERRIDE);
	अगर (test->expected_result == ATTACH_REJECT && err) अणु
		err = 0; /* error was expected, reset it */
		जाओ out;
	पूर्ण अन्यथा अगर (test->expected_result == ATTACH_REJECT || err) अणु
		जाओ err;
	पूर्ण अन्यथा अगर (test->expected_result == ATTACH_OKAY) अणु
		err = 0;
		जाओ out;
	पूर्ण

	चयन (test->attach_type) अणु
	हाल BPF_CGROUP_INET4_BIND:
	हाल BPF_CGROUP_INET6_BIND:
		err = run_bind_test_हाल(test);
		अवरोध;
	हाल BPF_CGROUP_INET4_CONNECT:
	हाल BPF_CGROUP_INET6_CONNECT:
		err = run_connect_test_हाल(test);
		अवरोध;
	हाल BPF_CGROUP_UDP4_SENDMSG:
	हाल BPF_CGROUP_UDP6_SENDMSG:
		err = run_xmsg_test_हाल(test, 1);
		अवरोध;
	हाल BPF_CGROUP_UDP4_RECVMSG:
	हाल BPF_CGROUP_UDP6_RECVMSG:
		err = run_xmsg_test_हाल(test, 0);
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	अगर (test->expected_result == SYSCALL_EPERM && err == EPERM) अणु
		err = 0; /* error was expected, reset it */
		जाओ out;
	पूर्ण

	अगर (test->expected_result == SYSCALL_ENOTSUPP && err == ENOTSUPP) अणु
		err = 0; /* error was expected, reset it */
		जाओ out;
	पूर्ण

	अगर (err || test->expected_result != SUCCESS)
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

	अगर (argc < 2) अणु
		ख_लिखो(मानक_त्रुटि,
			"%s has to be run via %s.sh. Skip direct run.\n",
			argv[0], argv[0]);
		निकास(err);
	पूर्ण

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
