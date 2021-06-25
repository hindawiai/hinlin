<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Test IPV6_FLOWINFO_MGR */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <error.h>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <linux/in6.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

/* uapi/glibc weirdness may leave this undefined */
#अगर_अघोषित IPV6_FLOWLABEL_MGR
#घोषणा IPV6_FLOWLABEL_MGR	32
#पूर्ण_अगर

/* from net/ipv6/ip6_flowlabel.c */
#घोषणा FL_MIN_LINGER		6

#घोषणा explain(x)							\
	करो अणु अगर (cfg_verbose) ख_लिखो(मानक_त्रुटि, "       " x "\n"); पूर्ण जबतक (0)

#घोषणा __expect(x)							\
	करो अणु								\
		अगर (!(x))						\
			ख_लिखो(मानक_त्रुटि, "[OK]   " #x "\n");		\
		अन्यथा							\
			error(1, 0, "[ERR]  " #x " (line %d)", __LINE__); \
	पूर्ण जबतक (0)

#घोषणा expect_pass(x)	__expect(x)
#घोषणा expect_fail(x)	__expect(!(x))

अटल bool cfg_दीर्घ_running;
अटल bool cfg_verbose;

अटल पूर्णांक flowlabel_get(पूर्णांक fd, uपूर्णांक32_t label, uपूर्णांक8_t share, uपूर्णांक16_t flags)
अणु
	काष्ठा in6_flowlabel_req req = अणु
		.flr_action = IPV6_FL_A_GET,
		.flr_label = htonl(label),
		.flr_flags = flags,
		.flr_share = share,
	पूर्ण;

	/* करो not pass IPV6_ADDR_ANY or IPV6_ADDR_MAPPED */
	req.flr_dst.s6_addr[0] = 0xfd;
	req.flr_dst.s6_addr[15] = 0x1;

	वापस setsockopt(fd, SOL_IPV6, IPV6_FLOWLABEL_MGR, &req, माप(req));
पूर्ण

अटल पूर्णांक flowlabel_put(पूर्णांक fd, uपूर्णांक32_t label)
अणु
	काष्ठा in6_flowlabel_req req = अणु
		.flr_action = IPV6_FL_A_PUT,
		.flr_label = htonl(label),
	पूर्ण;

	वापस setsockopt(fd, SOL_IPV6, IPV6_FLOWLABEL_MGR, &req, माप(req));
पूर्ण

अटल व्योम run_tests(पूर्णांक fd)
अणु
	पूर्णांक wstatus;
	pid_t pid;

	explain("cannot get non-existent label");
	expect_fail(flowlabel_get(fd, 1, IPV6_FL_S_ANY, 0));

	explain("cannot put non-existent label");
	expect_fail(flowlabel_put(fd, 1));

	explain("cannot create label greater than 20 bits");
	expect_fail(flowlabel_get(fd, 0x1FFFFF, IPV6_FL_S_ANY,
				  IPV6_FL_F_CREATE));

	explain("create a new label (FL_F_CREATE)");
	expect_pass(flowlabel_get(fd, 1, IPV6_FL_S_ANY, IPV6_FL_F_CREATE));
	explain("can get the label (without FL_F_CREATE)");
	expect_pass(flowlabel_get(fd, 1, IPV6_FL_S_ANY, 0));
	explain("can get it again with create flag set, too");
	expect_pass(flowlabel_get(fd, 1, IPV6_FL_S_ANY, IPV6_FL_F_CREATE));
	explain("cannot get it again with the exclusive (FL_FL_EXCL) flag");
	expect_fail(flowlabel_get(fd, 1, IPV6_FL_S_ANY,
					 IPV6_FL_F_CREATE | IPV6_FL_F_EXCL));
	explain("can now put exactly three references");
	expect_pass(flowlabel_put(fd, 1));
	expect_pass(flowlabel_put(fd, 1));
	expect_pass(flowlabel_put(fd, 1));
	expect_fail(flowlabel_put(fd, 1));

	explain("create a new exclusive label (FL_S_EXCL)");
	expect_pass(flowlabel_get(fd, 2, IPV6_FL_S_EXCL, IPV6_FL_F_CREATE));
	explain("cannot get it again in non-exclusive mode");
	expect_fail(flowlabel_get(fd, 2, IPV6_FL_S_ANY,  IPV6_FL_F_CREATE));
	explain("cannot get it again in exclusive mode either");
	expect_fail(flowlabel_get(fd, 2, IPV6_FL_S_EXCL, IPV6_FL_F_CREATE));
	expect_pass(flowlabel_put(fd, 2));

	अगर (cfg_दीर्घ_running) अणु
		explain("cannot reuse the label, due to linger");
		expect_fail(flowlabel_get(fd, 2, IPV6_FL_S_ANY,
					  IPV6_FL_F_CREATE));
		explain("after sleep, can reuse");
		sleep(FL_MIN_LINGER * 2 + 1);
		expect_pass(flowlabel_get(fd, 2, IPV6_FL_S_ANY,
					  IPV6_FL_F_CREATE));
	पूर्ण

	explain("create a new user-private label (FL_S_USER)");
	expect_pass(flowlabel_get(fd, 3, IPV6_FL_S_USER, IPV6_FL_F_CREATE));
	explain("cannot get it again in non-exclusive mode");
	expect_fail(flowlabel_get(fd, 3, IPV6_FL_S_ANY, 0));
	explain("cannot get it again in exclusive mode");
	expect_fail(flowlabel_get(fd, 3, IPV6_FL_S_EXCL, 0));
	explain("can get it again in user mode");
	expect_pass(flowlabel_get(fd, 3, IPV6_FL_S_USER, 0));
	explain("child process can get it too, but not after setuid(nobody)");
	pid = विभाजन();
	अगर (pid == -1)
		error(1, त्रुटि_सं, "fork");
	अगर (!pid) अणु
		expect_pass(flowlabel_get(fd, 3, IPV6_FL_S_USER, 0));
		अगर (setuid(अच_लघु_उच्च))
			ख_लिखो(मानक_त्रुटि, "[INFO] skip setuid child test\n");
		अन्यथा
			expect_fail(flowlabel_get(fd, 3, IPV6_FL_S_USER, 0));
		निकास(0);
	पूर्ण
	अगर (रुको(&wstatus) == -1)
		error(1, त्रुटि_सं, "wait");
	अगर (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0)
		error(1, त्रुटि_सं, "wait: unexpected child result");

	explain("create a new process-private label (FL_S_PROCESS)");
	expect_pass(flowlabel_get(fd, 4, IPV6_FL_S_PROCESS, IPV6_FL_F_CREATE));
	explain("can get it again");
	expect_pass(flowlabel_get(fd, 4, IPV6_FL_S_PROCESS, 0));
	explain("child process cannot can get it");
	pid = विभाजन();
	अगर (pid == -1)
		error(1, त्रुटि_सं, "fork");
	अगर (!pid) अणु
		expect_fail(flowlabel_get(fd, 4, IPV6_FL_S_PROCESS, 0));
		निकास(0);
	पूर्ण
	अगर (रुको(&wstatus) == -1)
		error(1, त्रुटि_सं, "wait");
	अगर (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0)
		error(1, त्रुटि_सं, "wait: unexpected child result");
पूर्ण

अटल व्योम parse_opts(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "lv")) != -1) अणु
		चयन (c) अणु
		हाल 'l':
			cfg_दीर्घ_running = true;
			अवरोध;
		हाल 'v':
			cfg_verbose = true;
			अवरोध;
		शेष:
			error(1, 0, "%s: parse error", argv[0]);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक fd;

	parse_opts(argc, argv);

	fd = socket(PF_INET6, SOCK_DGRAM, 0);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket");

	run_tests(fd);

	अगर (बंद(fd))
		error(1, त्रुटि_सं, "close");

	वापस 0;
पूर्ण
