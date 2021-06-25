<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2018 Intel Corporation. */

#समावेश <त्रुटिसं.स>
#समावेश <getopt.h>
#समावेश <libgen.h>
#समावेश <net/अगर.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/socket.h>
#समावेश <sys/un.h>
#समावेश <unistd.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/xsk.h>
#समावेश "xdpsock.h"

अटल स्थिर अक्षर *opt_अगर = "";

अटल काष्ठा option दीर्घ_options[] = अणु
	अणु"interface", required_argument, 0, 'i'पूर्ण,
	अणु0, 0, 0, 0पूर्ण
पूर्ण;

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	स्थिर अक्षर *str =
		"  Usage: %s [OPTIONS]\n"
		"  Options:\n"
		"  -i, --interface=n	Run on interface n\n"
		"\n";
	ख_लिखो(मानक_त्रुटि, "%s\n", str);

	निकास(0);
पूर्ण

अटल व्योम parse_command_line(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक option_index, c;

	opterr = 0;

	क्रम (;;) अणु
		c = getopt_दीर्घ(argc, argv, "i:",
				दीर्घ_options, &option_index);
		अगर (c == -1)
			अवरोध;

		चयन (c) अणु
		हाल 'i':
			opt_अगर = optarg;
			अवरोध;
		शेष:
			usage(basename(argv[0]));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक send_xsks_map_fd(पूर्णांक sock, पूर्णांक fd)
अणु
	अक्षर cmsgbuf[CMSG_SPACE(माप(पूर्णांक))];
	काष्ठा msghdr msg;
	काष्ठा iovec iov;
	पूर्णांक value = 0;

	अगर (fd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "Incorrect fd = %d\n", fd);
		वापस -1;
	पूर्ण
	iov.iov_base = &value;
	iov.iov_len = माप(पूर्णांक);

	msg.msg_name = शून्य;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_flags = 0;
	msg.msg_control = cmsgbuf;
	msg.msg_controllen = CMSG_LEN(माप(पूर्णांक));

	काष्ठा cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);

	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(माप(पूर्णांक));

	*(पूर्णांक *)CMSG_DATA(cmsg) = fd;
	पूर्णांक ret = sendmsg(sock, &msg, 0);

	अगर (ret == -1) अणु
		ख_लिखो(मानक_त्रुटि, "Sendmsg failed with %s", म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा sockaddr_un server;
	पूर्णांक listening = 1;
	पूर्णांक rval, msgsock;
	पूर्णांक अगरindex = 0;
	पूर्णांक flag = 1;
	पूर्णांक cmd = 0;
	पूर्णांक sock;
	पूर्णांक err;
	पूर्णांक xsks_map_fd;

	parse_command_line(argc, argv);

	अगरindex = अगर_nametoindex(opt_अगर);
	अगर (अगरindex == 0) अणु
		ख_लिखो(मानक_त्रुटि, "Unable to get ifindex for Interface %s. Reason:%s",
			opt_अगर, म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	अगर (sock < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Opening socket stream failed: %s", म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	server.sun_family = AF_UNIX;
	म_नकल(server.sun_path, SOCKET_NAME);

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag, माप(पूर्णांक));

	अगर (bind(sock, (काष्ठा sockaddr *)&server, माप(काष्ठा sockaddr_un))) अणु
		ख_लिखो(मानक_त्रुटि, "Binding to socket stream failed: %s", म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	listen(sock, MAX_NUM_OF_CLIENTS);

	err = xsk_setup_xdp_prog(अगरindex, &xsks_map_fd);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "Setup of xdp program failed\n");
		जाओ बंद_sock;
	पूर्ण

	जबतक (listening) अणु
		msgsock = accept(sock, 0, 0);
		अगर (msgsock == -1) अणु
			ख_लिखो(मानक_त्रुटि, "Error accepting connection: %s", म_त्रुटि(त्रुटि_सं));
			err = -त्रुटि_सं;
			जाओ बंद_sock;
		पूर्ण
		err = send_xsks_map_fd(msgsock, xsks_map_fd);
		अगर (err <= 0) अणु
			ख_लिखो(मानक_त्रुटि, "Error %d sending xsks_map_fd\n", err);
			जाओ cleanup;
		पूर्ण
		करो अणु
			rval = पढ़ो(msgsock, &cmd, माप(पूर्णांक));
			अगर (rval < 0) अणु
				ख_लिखो(मानक_त्रुटि, "Error reading stream message");
			पूर्ण अन्यथा अणु
				अगर (cmd != CLOSE_CONN)
					ख_लिखो(मानक_त्रुटि, "Recv unknown cmd = %d\n", cmd);
				listening = 0;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (rval > 0);
	पूर्ण
	बंद(msgsock);
	बंद(sock);
	unlink(SOCKET_NAME);

	/* Unset fd क्रम given अगरindex */
	err = bpf_set_link_xdp_fd(अगरindex, -1, 0);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "Error when unsetting bpf prog_fd for ifindex(%d)\n", अगरindex);
		वापस err;
	पूर्ण

	वापस 0;

cleanup:
	बंद(msgsock);
बंद_sock:
	बंद(sock);
	unlink(SOCKET_NAME);
	वापस err;
पूर्ण
