<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vsock_diag_test - vsock_diag.ko test suite
 *
 * Copyright (C) 2017 Red Hat, Inc.
 *
 * Author: Stefan Hajnoczi <stefanha@redhat.com>
 */

#समावेश <getopt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <linux/list.h>
#समावेश <linux/net.h>
#समावेश <linux/netlink.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/vm_sockets_diag.h>
#समावेश <netinet/tcp.h>

#समावेश "timeout.h"
#समावेश "control.h"
#समावेश "util.h"

/* Per-socket status */
काष्ठा vsock_stat अणु
	काष्ठा list_head list;
	काष्ठा vsock_diag_msg msg;
पूर्ण;

अटल स्थिर अक्षर *sock_type_str(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल SOCK_DGRAM:
		वापस "DGRAM";
	हाल SOCK_STREAM:
		वापस "STREAM";
	शेष:
		वापस "INVALID TYPE";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *sock_state_str(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल TCP_CLOSE:
		वापस "UNCONNECTED";
	हाल TCP_SYN_SENT:
		वापस "CONNECTING";
	हाल TCP_ESTABLISHED:
		वापस "CONNECTED";
	हाल TCP_CLOSING:
		वापस "DISCONNECTING";
	हाल TCP_LISTEN:
		वापस "LISTEN";
	शेष:
		वापस "INVALID STATE";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *sock_shutकरोwn_str(पूर्णांक shutकरोwn)
अणु
	चयन (shutकरोwn) अणु
	हाल 1:
		वापस "RCV_SHUTDOWN";
	हाल 2:
		वापस "SEND_SHUTDOWN";
	हाल 3:
		वापस "RCV_SHUTDOWN | SEND_SHUTDOWN";
	शेष:
		वापस "0";
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_vsock_addr(खाता *fp, अचिन्हित पूर्णांक cid, अचिन्हित पूर्णांक port)
अणु
	अगर (cid == VMADDR_CID_ANY)
		ख_लिखो(fp, "*:");
	अन्यथा
		ख_लिखो(fp, "%u:", cid);

	अगर (port == VMADDR_PORT_ANY)
		ख_लिखो(fp, "*");
	अन्यथा
		ख_लिखो(fp, "%u", port);
पूर्ण

अटल व्योम prपूर्णांक_vsock_stat(खाता *fp, काष्ठा vsock_stat *st)
अणु
	prपूर्णांक_vsock_addr(fp, st->msg.vdiag_src_cid, st->msg.vdiag_src_port);
	ख_लिखो(fp, " ");
	prपूर्णांक_vsock_addr(fp, st->msg.vdiag_dst_cid, st->msg.vdiag_dst_port);
	ख_लिखो(fp, " %s %s %s %u\n",
		sock_type_str(st->msg.vdiag_type),
		sock_state_str(st->msg.vdiag_state),
		sock_shutकरोwn_str(st->msg.vdiag_shutकरोwn),
		st->msg.vdiag_ino);
पूर्ण

अटल व्योम prपूर्णांक_vsock_stats(खाता *fp, काष्ठा list_head *head)
अणु
	काष्ठा vsock_stat *st;

	list_क्रम_each_entry(st, head, list)
		prपूर्णांक_vsock_stat(fp, st);
पूर्ण

अटल काष्ठा vsock_stat *find_vsock_stat(काष्ठा list_head *head, पूर्णांक fd)
अणु
	काष्ठा vsock_stat *st;
	काष्ठा stat stat;

	अगर (ख_स्थिति(fd, &stat) < 0) अणु
		लिखो_त्रुटि("fstat");
		निकास(निकास_त्रुटि);
	पूर्ण

	list_क्रम_each_entry(st, head, list)
		अगर (st->msg.vdiag_ino == stat.st_ino)
			वापस st;

	ख_लिखो(मानक_त्रुटि, "cannot find fd %d\n", fd);
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम check_no_sockets(काष्ठा list_head *head)
अणु
	अगर (!list_empty(head)) अणु
		ख_लिखो(मानक_त्रुटि, "expected no sockets\n");
		prपूर्णांक_vsock_stats(मानक_त्रुटि, head);
		निकास(1);
	पूर्ण
पूर्ण

अटल व्योम check_num_sockets(काष्ठा list_head *head, पूर्णांक expected)
अणु
	काष्ठा list_head *node;
	पूर्णांक n = 0;

	list_क्रम_each(node, head)
		n++;

	अगर (n != expected) अणु
		ख_लिखो(मानक_त्रुटि, "expected %d sockets, found %d\n",
			expected, n);
		prपूर्णांक_vsock_stats(मानक_त्रुटि, head);
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम check_socket_state(काष्ठा vsock_stat *st, __u8 state)
अणु
	अगर (st->msg.vdiag_state != state) अणु
		ख_लिखो(मानक_त्रुटि, "expected socket state %#x, got %#x\n",
			state, st->msg.vdiag_state);
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम send_req(पूर्णांक fd)
अणु
	काष्ठा sockaddr_nl nladdr = अणु
		.nl_family = AF_NETLINK,
	पूर्ण;
	काष्ठा अणु
		काष्ठा nlmsghdr nlh;
		काष्ठा vsock_diag_req vreq;
	पूर्ण req = अणु
		.nlh = अणु
			.nlmsg_len = माप(req),
			.nlmsg_type = SOCK_DIAG_BY_FAMILY,
			.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP,
		पूर्ण,
		.vreq = अणु
			.sdiag_family = AF_VSOCK,
			.vdiag_states = ~(__u32)0,
		पूर्ण,
	पूर्ण;
	काष्ठा iovec iov = अणु
		.iov_base = &req,
		.iov_len = माप(req),
	पूर्ण;
	काष्ठा msghdr msg = अणु
		.msg_name = &nladdr,
		.msg_namelen = माप(nladdr),
		.msg_iov = &iov,
		.msg_iovlen = 1,
	पूर्ण;

	क्रम (;;) अणु
		अगर (sendmsg(fd, &msg, 0) < 0) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;

			लिखो_त्रुटि("sendmsg");
			निकास(निकास_त्रुटि);
		पूर्ण

		वापस;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार recv_resp(पूर्णांक fd, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा sockaddr_nl nladdr = अणु
		.nl_family = AF_NETLINK,
	पूर्ण;
	काष्ठा iovec iov = अणु
		.iov_base = buf,
		.iov_len = len,
	पूर्ण;
	काष्ठा msghdr msg = अणु
		.msg_name = &nladdr,
		.msg_namelen = माप(nladdr),
		.msg_iov = &iov,
		.msg_iovlen = 1,
	पूर्ण;
	sमाप_प्रकार ret;

	करो अणु
		ret = recvmsg(fd, &msg, 0);
	पूर्ण जबतक (ret < 0 && त्रुटि_सं == EINTR);

	अगर (ret < 0) अणु
		लिखो_त्रुटि("recvmsg");
		निकास(निकास_त्रुटि);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम add_vsock_stat(काष्ठा list_head *sockets,
			   स्थिर काष्ठा vsock_diag_msg *resp)
अणु
	काष्ठा vsock_stat *st;

	st = दो_स्मृति(माप(*st));
	अगर (!st) अणु
		लिखो_त्रुटि("malloc");
		निकास(निकास_त्रुटि);
	पूर्ण

	st->msg = *resp;
	list_add_tail(&st->list, sockets);
पूर्ण

/*
 * Read vsock stats पूर्णांकo a list.
 */
अटल व्योम पढ़ो_vsock_stat(काष्ठा list_head *sockets)
अणु
	दीर्घ buf[8192 / माप(दीर्घ)];
	पूर्णांक fd;

	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_SOCK_DIAG);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("socket");
		निकास(निकास_त्रुटि);
	पूर्ण

	send_req(fd);

	क्रम (;;) अणु
		स्थिर काष्ठा nlmsghdr *h;
		sमाप_प्रकार ret;

		ret = recv_resp(fd, buf, माप(buf));
		अगर (ret == 0)
			जाओ करोne;
		अगर (ret < माप(*h)) अणु
			ख_लिखो(मानक_त्रुटि, "short read of %zd bytes\n", ret);
			निकास(निकास_त्रुटि);
		पूर्ण

		h = (काष्ठा nlmsghdr *)buf;

		जबतक (NLMSG_OK(h, ret)) अणु
			अगर (h->nlmsg_type == NLMSG_DONE)
				जाओ करोne;

			अगर (h->nlmsg_type == NLMSG_ERROR) अणु
				स्थिर काष्ठा nlmsgerr *err = NLMSG_DATA(h);

				अगर (h->nlmsg_len < NLMSG_LENGTH(माप(*err)))
					ख_लिखो(मानक_त्रुटि, "NLMSG_ERROR\n");
				अन्यथा अणु
					त्रुटि_सं = -err->error;
					लिखो_त्रुटि("NLMSG_ERROR");
				पूर्ण

				निकास(निकास_त्रुटि);
			पूर्ण

			अगर (h->nlmsg_type != SOCK_DIAG_BY_FAMILY) अणु
				ख_लिखो(मानक_त्रुटि, "unexpected nlmsg_type %#x\n",
					h->nlmsg_type);
				निकास(निकास_त्रुटि);
			पूर्ण
			अगर (h->nlmsg_len <
			    NLMSG_LENGTH(माप(काष्ठा vsock_diag_msg))) अणु
				ख_लिखो(मानक_त्रुटि, "short vsock_diag_msg\n");
				निकास(निकास_त्रुटि);
			पूर्ण

			add_vsock_stat(sockets, NLMSG_DATA(h));

			h = NLMSG_NEXT(h, ret);
		पूर्ण
	पूर्ण

करोne:
	बंद(fd);
पूर्ण

अटल व्योम मुक्त_sock_stat(काष्ठा list_head *sockets)
अणु
	काष्ठा vsock_stat *st;
	काष्ठा vsock_stat *next;

	list_क्रम_each_entry_safe(st, next, sockets, list)
		मुक्त(st);
पूर्ण

अटल व्योम test_no_sockets(स्थिर काष्ठा test_opts *opts)
अणु
	LIST_HEAD(sockets);

	पढ़ो_vsock_stat(&sockets);

	check_no_sockets(&sockets);

	मुक्त_sock_stat(&sockets);
पूर्ण

अटल व्योम test_listen_socket_server(स्थिर काष्ठा test_opts *opts)
अणु
	जोड़ अणु
		काष्ठा sockaddr sa;
		काष्ठा sockaddr_vm svm;
	पूर्ण addr = अणु
		.svm = अणु
			.svm_family = AF_VSOCK,
			.svm_port = 1234,
			.svm_cid = VMADDR_CID_ANY,
		पूर्ण,
	पूर्ण;
	LIST_HEAD(sockets);
	काष्ठा vsock_stat *st;
	पूर्णांक fd;

	fd = socket(AF_VSOCK, SOCK_STREAM, 0);

	अगर (bind(fd, &addr.sa, माप(addr.svm)) < 0) अणु
		लिखो_त्रुटि("bind");
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (listen(fd, 1) < 0) अणु
		लिखो_त्रुटि("listen");
		निकास(निकास_त्रुटि);
	पूर्ण

	पढ़ो_vsock_stat(&sockets);

	check_num_sockets(&sockets, 1);
	st = find_vsock_stat(&sockets, fd);
	check_socket_state(st, TCP_LISTEN);

	बंद(fd);
	मुक्त_sock_stat(&sockets);
पूर्ण

अटल व्योम test_connect_client(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fd;
	LIST_HEAD(sockets);
	काष्ठा vsock_stat *st;

	fd = vsock_stream_connect(opts->peer_cid, 1234);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("connect");
		निकास(निकास_त्रुटि);
	पूर्ण

	पढ़ो_vsock_stat(&sockets);

	check_num_sockets(&sockets, 1);
	st = find_vsock_stat(&sockets, fd);
	check_socket_state(st, TCP_ESTABLISHED);

	control_expectln("DONE");
	control_ग_लिखोln("DONE");

	बंद(fd);
	मुक्त_sock_stat(&sockets);
पूर्ण

अटल व्योम test_connect_server(स्थिर काष्ठा test_opts *opts)
अणु
	काष्ठा vsock_stat *st;
	LIST_HEAD(sockets);
	पूर्णांक client_fd;

	client_fd = vsock_stream_accept(VMADDR_CID_ANY, 1234, शून्य);
	अगर (client_fd < 0) अणु
		लिखो_त्रुटि("accept");
		निकास(निकास_त्रुटि);
	पूर्ण

	पढ़ो_vsock_stat(&sockets);

	check_num_sockets(&sockets, 1);
	st = find_vsock_stat(&sockets, client_fd);
	check_socket_state(st, TCP_ESTABLISHED);

	control_ग_लिखोln("DONE");
	control_expectln("DONE");

	बंद(client_fd);
	मुक्त_sock_stat(&sockets);
पूर्ण

अटल काष्ठा test_हाल test_हालs[] = अणु
	अणु
		.name = "No sockets",
		.run_server = test_no_sockets,
	पूर्ण,
	अणु
		.name = "Listen socket",
		.run_server = test_listen_socket_server,
	पूर्ण,
	अणु
		.name = "Connect",
		.run_client = test_connect_client,
		.run_server = test_connect_server,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर अक्षर optstring[] = "";
अटल स्थिर काष्ठा option दीर्घopts[] = अणु
	अणु
		.name = "control-host",
		.has_arg = required_argument,
		.val = 'H',
	पूर्ण,
	अणु
		.name = "control-port",
		.has_arg = required_argument,
		.val = 'P',
	पूर्ण,
	अणु
		.name = "mode",
		.has_arg = required_argument,
		.val = 'm',
	पूर्ण,
	अणु
		.name = "peer-cid",
		.has_arg = required_argument,
		.val = 'p',
	पूर्ण,
	अणु
		.name = "list",
		.has_arg = no_argument,
		.val = 'l',
	पूर्ण,
	अणु
		.name = "skip",
		.has_arg = required_argument,
		.val = 's',
	पूर्ण,
	अणु
		.name = "help",
		.has_arg = no_argument,
		.val = '?',
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: vsock_diag_test [--help] [--control-host=<host>] --control-port=<port> --mode=client|server --peer-cid=<cid> [--list] [--skip=<test_id>]\n"
		"\n"
		"  Server: vsock_diag_test --control-port=1234 --mode=server --peer-cid=3\n"
		"  Client: vsock_diag_test --control-host=192.168.0.1 --control-port=1234 --mode=client --peer-cid=2\n"
		"\n"
		"Run vsock_diag.ko tests.  Must be launched in both\n"
		"guest and host.  One side must use --mode=client and\n"
		"the other side must use --mode=server.\n"
		"\n"
		"A TCP control socket connection is used to coordinate tests\n"
		"between the client and the server.  The server requires a\n"
		"listen address and the client requires an address to\n"
		"connect to.\n"
		"\n"
		"The CID of the other side must be given with --peer-cid=<cid>.\n"
		"\n"
		"Options:\n"
		"  --help                 This help message\n"
		"  --control-host <host>  Server IP address to connect to\n"
		"  --control-port <port>  Server port to listen on/connect to\n"
		"  --mode client|server   Server or client mode\n"
		"  --peer-cid <cid>       CID of the other side\n"
		"  --list                 List of tests that will be executed\n"
		"  --skip <test_id>       Test ID to skip;\n"
		"                         use multiple --skip options to skip more tests\n"
		);
	निकास(निकास_त्रुटि);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *control_host = शून्य;
	स्थिर अक्षर *control_port = शून्य;
	काष्ठा test_opts opts = अणु
		.mode = TEST_MODE_UNSET,
		.peer_cid = VMADDR_CID_ANY,
	पूर्ण;

	init_संकेतs();

	क्रम (;;) अणु
		पूर्णांक opt = getopt_दीर्घ(argc, argv, optstring, दीर्घopts, शून्य);

		अगर (opt == -1)
			अवरोध;

		चयन (opt) अणु
		हाल 'H':
			control_host = optarg;
			अवरोध;
		हाल 'm':
			अगर (म_भेद(optarg, "client") == 0)
				opts.mode = TEST_MODE_CLIENT;
			अन्यथा अगर (म_भेद(optarg, "server") == 0)
				opts.mode = TEST_MODE_SERVER;
			अन्यथा अणु
				ख_लिखो(मानक_त्रुटि, "--mode must be \"client\" or \"server\"\n");
				वापस निकास_त्रुटि;
			पूर्ण
			अवरोध;
		हाल 'p':
			opts.peer_cid = parse_cid(optarg);
			अवरोध;
		हाल 'P':
			control_port = optarg;
			अवरोध;
		हाल 'l':
			list_tests(test_हालs);
			अवरोध;
		हाल 's':
			skip_test(test_हालs, ARRAY_SIZE(test_हालs) - 1,
				  optarg);
			अवरोध;
		हाल '?':
		शेष:
			usage();
		पूर्ण
	पूर्ण

	अगर (!control_port)
		usage();
	अगर (opts.mode == TEST_MODE_UNSET)
		usage();
	अगर (opts.peer_cid == VMADDR_CID_ANY)
		usage();

	अगर (!control_host) अणु
		अगर (opts.mode != TEST_MODE_SERVER)
			usage();
		control_host = "0.0.0.0";
	पूर्ण

	control_init(control_host, control_port,
		     opts.mode == TEST_MODE_SERVER);

	run_tests(test_हालs, &opts);

	control_cleanup();
	वापस निकास_सफल;
पूर्ण
