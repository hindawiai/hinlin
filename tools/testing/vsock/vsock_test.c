<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vsock_test - vsock.ko test suite
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
#समावेश <linux/kernel.h>

#समावेश "timeout.h"
#समावेश "control.h"
#समावेश "util.h"

अटल व्योम test_stream_connection_reset(स्थिर काष्ठा test_opts *opts)
अणु
	जोड़ अणु
		काष्ठा sockaddr sa;
		काष्ठा sockaddr_vm svm;
	पूर्ण addr = अणु
		.svm = अणु
			.svm_family = AF_VSOCK,
			.svm_port = 1234,
			.svm_cid = opts->peer_cid,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक fd;

	fd = socket(AF_VSOCK, SOCK_STREAM, 0);

	समयout_begin(TIMEOUT);
	करो अणु
		ret = connect(fd, &addr.sa, माप(addr.svm));
		समयout_check("connect");
	पूर्ण जबतक (ret < 0 && त्रुटि_सं == EINTR);
	समयout_end();

	अगर (ret != -1) अणु
		ख_लिखो(मानक_त्रुटि, "expected connect(2) failure, got %d\n", ret);
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (त्रुटि_सं != ECONNRESET) अणु
		ख_लिखो(मानक_त्रुटि, "unexpected connect(2) errno %d\n", त्रुटि_सं);
		निकास(निकास_त्रुटि);
	पूर्ण

	बंद(fd);
पूर्ण

अटल व्योम test_stream_bind_only_client(स्थिर काष्ठा test_opts *opts)
अणु
	जोड़ अणु
		काष्ठा sockaddr sa;
		काष्ठा sockaddr_vm svm;
	पूर्ण addr = अणु
		.svm = अणु
			.svm_family = AF_VSOCK,
			.svm_port = 1234,
			.svm_cid = opts->peer_cid,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक fd;

	/* Wait क्रम the server to be पढ़ोy */
	control_expectln("BIND");

	fd = socket(AF_VSOCK, SOCK_STREAM, 0);

	समयout_begin(TIMEOUT);
	करो अणु
		ret = connect(fd, &addr.sa, माप(addr.svm));
		समयout_check("connect");
	पूर्ण जबतक (ret < 0 && त्रुटि_सं == EINTR);
	समयout_end();

	अगर (ret != -1) अणु
		ख_लिखो(मानक_त्रुटि, "expected connect(2) failure, got %d\n", ret);
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (त्रुटि_सं != ECONNRESET) अणु
		ख_लिखो(मानक_त्रुटि, "unexpected connect(2) errno %d\n", त्रुटि_सं);
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Notअगरy the server that the client has finished */
	control_ग_लिखोln("DONE");

	बंद(fd);
पूर्ण

अटल व्योम test_stream_bind_only_server(स्थिर काष्ठा test_opts *opts)
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
	पूर्णांक fd;

	fd = socket(AF_VSOCK, SOCK_STREAM, 0);

	अगर (bind(fd, &addr.sa, माप(addr.svm)) < 0) अणु
		लिखो_त्रुटि("bind");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Notअगरy the client that the server is पढ़ोy */
	control_ग_लिखोln("BIND");

	/* Wait क्रम the client to finish */
	control_expectln("DONE");

	बंद(fd);
पूर्ण

अटल व्योम test_stream_client_बंद_client(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fd;

	fd = vsock_stream_connect(opts->peer_cid, 1234);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("connect");
		निकास(निकास_त्रुटि);
	पूर्ण

	send_byte(fd, 1, 0);
	बंद(fd);
पूर्ण

अटल व्योम test_stream_client_बंद_server(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fd;

	fd = vsock_stream_accept(VMADDR_CID_ANY, 1234, शून्य);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("accept");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Wait क्रम the remote to बंद the connection, beक्रमe check
	 * -EPIPE error on send.
	 */
	vsock_रुको_remote_बंद(fd);

	send_byte(fd, -EPIPE, 0);
	recv_byte(fd, 1, 0);
	recv_byte(fd, 0, 0);
	बंद(fd);
पूर्ण

अटल व्योम test_stream_server_बंद_client(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fd;

	fd = vsock_stream_connect(opts->peer_cid, 1234);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("connect");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Wait क्रम the remote to बंद the connection, beक्रमe check
	 * -EPIPE error on send.
	 */
	vsock_रुको_remote_बंद(fd);

	send_byte(fd, -EPIPE, 0);
	recv_byte(fd, 1, 0);
	recv_byte(fd, 0, 0);
	बंद(fd);
पूर्ण

अटल व्योम test_stream_server_बंद_server(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fd;

	fd = vsock_stream_accept(VMADDR_CID_ANY, 1234, शून्य);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("accept");
		निकास(निकास_त्रुटि);
	पूर्ण

	send_byte(fd, 1, 0);
	बंद(fd);
पूर्ण

/* With the standard socket sizes, VMCI is able to support about 100
 * concurrent stream connections.
 */
#घोषणा MULTICONN_NFDS 100

अटल व्योम test_stream_multiconn_client(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fds[MULTICONN_NFDS];
	पूर्णांक i;

	क्रम (i = 0; i < MULTICONN_NFDS; i++) अणु
		fds[i] = vsock_stream_connect(opts->peer_cid, 1234);
		अगर (fds[i] < 0) अणु
			लिखो_त्रुटि("connect");
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MULTICONN_NFDS; i++) अणु
		अगर (i % 2)
			recv_byte(fds[i], 1, 0);
		अन्यथा
			send_byte(fds[i], 1, 0);
	पूर्ण

	क्रम (i = 0; i < MULTICONN_NFDS; i++)
		बंद(fds[i]);
पूर्ण

अटल व्योम test_stream_multiconn_server(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fds[MULTICONN_NFDS];
	पूर्णांक i;

	क्रम (i = 0; i < MULTICONN_NFDS; i++) अणु
		fds[i] = vsock_stream_accept(VMADDR_CID_ANY, 1234, शून्य);
		अगर (fds[i] < 0) अणु
			लिखो_त्रुटि("accept");
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MULTICONN_NFDS; i++) अणु
		अगर (i % 2)
			send_byte(fds[i], 1, 0);
		अन्यथा
			recv_byte(fds[i], 1, 0);
	पूर्ण

	क्रम (i = 0; i < MULTICONN_NFDS; i++)
		बंद(fds[i]);
पूर्ण

अटल व्योम test_stream_msg_peek_client(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fd;

	fd = vsock_stream_connect(opts->peer_cid, 1234);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("connect");
		निकास(निकास_त्रुटि);
	पूर्ण

	send_byte(fd, 1, 0);
	बंद(fd);
पूर्ण

अटल व्योम test_stream_msg_peek_server(स्थिर काष्ठा test_opts *opts)
अणु
	पूर्णांक fd;

	fd = vsock_stream_accept(VMADDR_CID_ANY, 1234, शून्य);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("accept");
		निकास(निकास_त्रुटि);
	पूर्ण

	recv_byte(fd, 1, MSG_PEEK);
	recv_byte(fd, 1, 0);
	बंद(fd);
पूर्ण

अटल काष्ठा test_हाल test_हालs[] = अणु
	अणु
		.name = "SOCK_STREAM connection reset",
		.run_client = test_stream_connection_reset,
	पूर्ण,
	अणु
		.name = "SOCK_STREAM bind only",
		.run_client = test_stream_bind_only_client,
		.run_server = test_stream_bind_only_server,
	पूर्ण,
	अणु
		.name = "SOCK_STREAM client close",
		.run_client = test_stream_client_बंद_client,
		.run_server = test_stream_client_बंद_server,
	पूर्ण,
	अणु
		.name = "SOCK_STREAM server close",
		.run_client = test_stream_server_बंद_client,
		.run_server = test_stream_server_बंद_server,
	पूर्ण,
	अणु
		.name = "SOCK_STREAM multiple connections",
		.run_client = test_stream_multiconn_client,
		.run_server = test_stream_multiconn_server,
	पूर्ण,
	अणु
		.name = "SOCK_STREAM MSG_PEEK",
		.run_client = test_stream_msg_peek_client,
		.run_server = test_stream_msg_peek_server,
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
	ख_लिखो(मानक_त्रुटि, "Usage: vsock_test [--help] [--control-host=<host>] --control-port=<port> --mode=client|server --peer-cid=<cid> [--list] [--skip=<test_id>]\n"
		"\n"
		"  Server: vsock_test --control-port=1234 --mode=server --peer-cid=3\n"
		"  Client: vsock_test --control-host=192.168.0.1 --control-port=1234 --mode=client --peer-cid=2\n"
		"\n"
		"Run vsock.ko tests.  Must be launched in both guest\n"
		"and host.  One side must use --mode=client and\n"
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
