<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 	ucon.c
 *
 * Copyright (c) 2004+ Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <यंत्र/types.h>

#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <sys/poll.h>

#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>

#समावेश <arpa/inet.h>

#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <समय.स>
#समावेश <getopt.h>

#समावेश <linux/connector.h>

#घोषणा DEBUG
#घोषणा NETLINK_CONNECTOR 	11

/* Hopefully your userspace connector.h matches this kernel */
#घोषणा CN_TEST_IDX		CN_NETLINK_USERS + 3
#घोषणा CN_TEST_VAL		0x456

#अगर_घोषित DEBUG
#घोषणा ulog(f, a...) ख_लिखो(मानक_निकास, f, ##a)
#अन्यथा
#घोषणा ulog(f, a...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक need_निकास;
अटल __u32 seq;

अटल पूर्णांक netlink_send(पूर्णांक s, काष्ठा cn_msg *msg)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक size;
	पूर्णांक err;
	अक्षर buf[128];
	काष्ठा cn_msg *m;

	size = NLMSG_SPACE(माप(काष्ठा cn_msg) + msg->len);

	nlh = (काष्ठा nlmsghdr *)buf;
	nlh->nlmsg_seq = seq++;
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_type = NLMSG_DONE;
	nlh->nlmsg_len = size;
	nlh->nlmsg_flags = 0;

	m = NLMSG_DATA(nlh);
#अगर 0
	ulog("%s: [%08x.%08x] len=%u, seq=%u, ack=%u.\n",
	       __func__, msg->id.idx, msg->id.val, msg->len, msg->seq, msg->ack);
#पूर्ण_अगर
	स_नकल(m, msg, माप(*m) + msg->len);

	err = send(s, nlh, size, 0);
	अगर (err == -1)
		ulog("Failed to send: %s [%d].\n",
			म_त्रुटि(त्रुटि_सं), त्रुटि_सं);

	वापस err;
पूर्ण

अटल व्योम usage(व्योम)
अणु
	म_लिखो(
		"Usage: ucon [options] [output file]\n"
		"\n"
		"\t-h\tthis help screen\n"
		"\t-s\tsend buffers to the test module\n"
		"\n"
		"The default behavior of ucon is to subscribe to the test module\n"
		"and wait for state messages.  Any ones received are dumped to the\n"
		"specified output file (or stdout).  The test module is assumed to\n"
		"have an id of {%u.%u}\n"
		"\n"
		"If you get no output, then verify the cn_test module id matches\n"
		"the expected id above.\n"
		, CN_TEST_IDX, CN_TEST_VAL
	);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक s;
	अक्षर buf[1024];
	पूर्णांक len;
	काष्ठा nlmsghdr *reply;
	काष्ठा sockaddr_nl l_local;
	काष्ठा cn_msg *data;
	खाता *out;
	समय_प्रकार पंचांग;
	काष्ठा pollfd pfd;
	bool send_msgs = false;

	जबतक ((s = getopt(argc, argv, "hs")) != -1) अणु
		चयन (s) अणु
		हाल 's':
			send_msgs = true;
			अवरोध;

		हाल 'h':
			usage();
			वापस 0;

		शेष:
			/* getopt() outमाला_दो an error क्रम us */
			usage();
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (argc != optind) अणु
		out = ख_खोलो(argv[optind], "a+");
		अगर (!out) अणु
			ulog("Unable to open %s for writing: %s\n",
				argv[1], म_त्रुटि(त्रुटि_सं));
			out = मानक_निकास;
		पूर्ण
	पूर्ण अन्यथा
		out = मानक_निकास;

	स_रखो(buf, 0, माप(buf));

	s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_CONNECTOR);
	अगर (s == -1) अणु
		लिखो_त्रुटि("socket");
		वापस -1;
	पूर्ण

	l_local.nl_family = AF_NETLINK;
	l_local.nl_groups = -1; /* biपंचांगask of requested groups */
	l_local.nl_pid = 0;

	ulog("subscribing to %u.%u\n", CN_TEST_IDX, CN_TEST_VAL);

	अगर (bind(s, (काष्ठा sockaddr *)&l_local, माप(काष्ठा sockaddr_nl)) == -1) अणु
		लिखो_त्रुटि("bind");
		बंद(s);
		वापस -1;
	पूर्ण

#अगर 0
	अणु
		पूर्णांक on = 0x57; /* Additional group number */
		setsockopt(s, SOL_NETLINK, NETLINK_ADD_MEMBERSHIP, &on, माप(on));
	पूर्ण
#पूर्ण_अगर
	अगर (send_msgs) अणु
		पूर्णांक i, j;

		स_रखो(buf, 0, माप(buf));

		data = (काष्ठा cn_msg *)buf;

		data->id.idx = CN_TEST_IDX;
		data->id.val = CN_TEST_VAL;
		data->seq = seq++;
		data->ack = 0;
		data->len = 0;

		क्रम (j=0; j<10; ++j) अणु
			क्रम (i=0; i<1000; ++i) अणु
				len = netlink_send(s, data);
			पूर्ण

			ulog("%d messages have been sent to %08x.%08x.\n", i, data->id.idx, data->id.val);
		पूर्ण

		वापस 0;
	पूर्ण


	pfd.fd = s;

	जबतक (!need_निकास) अणु
		pfd.events = POLLIN;
		pfd.revents = 0;
		चयन (poll(&pfd, 1, -1)) अणु
			हाल 0:
				need_निकास = 1;
				अवरोध;
			हाल -1:
				अगर (त्रुटि_सं != EINTR) अणु
					need_निकास = 1;
					अवरोध;
				पूर्ण
				जारी;
		पूर्ण
		अगर (need_निकास)
			अवरोध;

		स_रखो(buf, 0, माप(buf));
		len = recv(s, buf, माप(buf), 0);
		अगर (len == -1) अणु
			लिखो_त्रुटि("recv buf");
			बंद(s);
			वापस -1;
		पूर्ण
		reply = (काष्ठा nlmsghdr *)buf;

		चयन (reply->nlmsg_type) अणु
		हाल NLMSG_ERROR:
			ख_लिखो(out, "Error message received.\n");
			ख_साफ(out);
			अवरोध;
		हाल NLMSG_DONE:
			data = (काष्ठा cn_msg *)NLMSG_DATA(reply);

			समय(&पंचांग);
			ख_लिखो(out, "%.24s : [%x.%x] [%08u.%08u].\n",
				स_समय(&पंचांग), data->id.idx, data->id.val, data->seq, data->ack);
			ख_साफ(out);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	बंद(s);
	वापस 0;
पूर्ण
