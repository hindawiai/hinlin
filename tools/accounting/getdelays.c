<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* getdelays.c
 *
 * Utility to get per-pid and per-tgid delay accounting statistics
 * Also illustrates usage of the taskstats पूर्णांकerface
 *
 * Copyright (C) Shailabh Nagar, IBM Corp. 2005
 * Copyright (C) Balbir Singh, IBM Corp. 2006
 * Copyright (c) Jay Lan, SGI. 2006
 *
 * Compile with
 *	gcc -I/usr/src/linux/include getdelays.c -o getdelays
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <poll.h>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/socket.h>
#समावेश <sys/रुको.h>
#समावेश <संकेत.स>

#समावेश <linux/genetlink.h>
#समावेश <linux/taskstats.h>
#समावेश <linux/cgroupstats.h>

/*
 * Generic macros क्रम dealing with netlink sockets. Might be duplicated
 * अन्यथाwhere. It is recommended that commercial grade applications use
 * libnl or libnetlink and use the पूर्णांकerfaces provided by the library
 */
#घोषणा GENLMSG_DATA(glh)	((व्योम *)(NLMSG_DATA(glh) + GENL_HDRLEN))
#घोषणा GENLMSG_PAYLOAD(glh)	(NLMSG_PAYLOAD(glh, 0) - GENL_HDRLEN)
#घोषणा NLA_DATA(na)		((व्योम *)((अक्षर*)(na) + NLA_HDRLEN))
#घोषणा NLA_PAYLOAD(len)	(len - NLA_HDRLEN)

#घोषणा err(code, fmt, arg...)			\
	करो अणु					\
		ख_लिखो(मानक_त्रुटि, fmt, ##arg);	\
		निकास(code);			\
	पूर्ण जबतक (0)

पूर्णांक करोne;
पूर्णांक rcvbufsz;
अक्षर name[100];
पूर्णांक dbg;
पूर्णांक prपूर्णांक_delays;
पूर्णांक prपूर्णांक_io_accounting;
पूर्णांक prपूर्णांक_task_context_चयन_counts;

#घोषणा PRINTF(fmt, arg...) अणु			\
	    अगर (dbg) अणु				\
		म_लिखो(fmt, ##arg);		\
	    पूर्ण					\
	पूर्ण

/* Maximum size of response requested or message sent */
#घोषणा MAX_MSG_SIZE	1024
/* Maximum number of cpus expected to be specअगरied in a cpumask */
#घोषणा MAX_CPUS	32

काष्ठा msgढाँचा अणु
	काष्ठा nlmsghdr n;
	काष्ठा genlmsghdr g;
	अक्षर buf[MAX_MSG_SIZE];
पूर्ण;

अक्षर cpumask[100+6*MAX_CPUS];

अटल व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "getdelays [-dilv] [-w logfile] [-r bufsize] "
			"[-m cpumask] [-t tgid] [-p pid]\n");
	ख_लिखो(मानक_त्रुटि, "  -d: print delayacct stats\n");
	ख_लिखो(मानक_त्रुटि, "  -i: print IO accounting (works only with -p)\n");
	ख_लिखो(मानक_त्रुटि, "  -l: listen forever\n");
	ख_लिखो(मानक_त्रुटि, "  -v: debug on\n");
	ख_लिखो(मानक_त्रुटि, "  -C: container path\n");
पूर्ण

/*
 * Create a raw netlink socket and bind
 */
अटल पूर्णांक create_nl_socket(पूर्णांक protocol)
अणु
	पूर्णांक fd;
	काष्ठा sockaddr_nl local;

	fd = socket(AF_NETLINK, SOCK_RAW, protocol);
	अगर (fd < 0)
		वापस -1;

	अगर (rcvbufsz)
		अगर (setsockopt(fd, SOL_SOCKET, SO_RCVBUF,
				&rcvbufsz, माप(rcvbufsz)) < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Unable to set socket rcv buf size to %d\n",
				rcvbufsz);
			जाओ error;
		पूर्ण

	स_रखो(&local, 0, माप(local));
	local.nl_family = AF_NETLINK;

	अगर (bind(fd, (काष्ठा sockaddr *) &local, माप(local)) < 0)
		जाओ error;

	वापस fd;
error:
	बंद(fd);
	वापस -1;
पूर्ण


अटल पूर्णांक send_cmd(पूर्णांक sd, __u16 nlmsg_type, __u32 nlmsg_pid,
	     __u8 genl_cmd, __u16 nla_type,
	     व्योम *nla_data, पूर्णांक nla_len)
अणु
	काष्ठा nlattr *na;
	काष्ठा sockaddr_nl nladdr;
	पूर्णांक r, buflen;
	अक्षर *buf;

	काष्ठा msgढाँचा msg;

	msg.n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
	msg.n.nlmsg_type = nlmsg_type;
	msg.n.nlmsg_flags = NLM_F_REQUEST;
	msg.n.nlmsg_seq = 0;
	msg.n.nlmsg_pid = nlmsg_pid;
	msg.g.cmd = genl_cmd;
	msg.g.version = 0x1;
	na = (काष्ठा nlattr *) GENLMSG_DATA(&msg);
	na->nla_type = nla_type;
	na->nla_len = nla_len + NLA_HDRLEN;
	स_नकल(NLA_DATA(na), nla_data, nla_len);
	msg.n.nlmsg_len += NLMSG_ALIGN(na->nla_len);

	buf = (अक्षर *) &msg;
	buflen = msg.n.nlmsg_len ;
	स_रखो(&nladdr, 0, माप(nladdr));
	nladdr.nl_family = AF_NETLINK;
	जबतक ((r = sendto(sd, buf, buflen, 0, (काष्ठा sockaddr *) &nladdr,
			   माप(nladdr))) < buflen) अणु
		अगर (r > 0) अणु
			buf += r;
			buflen -= r;
		पूर्ण अन्यथा अगर (त्रुटि_सं != EAGAIN)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * Probe the controller in genetlink to find the family id
 * क्रम the TASKSTATS family
 */
अटल पूर्णांक get_family_id(पूर्णांक sd)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr n;
		काष्ठा genlmsghdr g;
		अक्षर buf[256];
	पूर्ण ans;

	पूर्णांक id = 0, rc;
	काष्ठा nlattr *na;
	पूर्णांक rep_len;

	म_नकल(name, TASKSTATS_GENL_NAME);
	rc = send_cmd(sd, GENL_ID_CTRL, getpid(), CTRL_CMD_GETFAMILY,
			CTRL_ATTR_FAMILY_NAME, (व्योम *)name,
			म_माप(TASKSTATS_GENL_NAME)+1);
	अगर (rc < 0)
		वापस 0;	/* sendto() failure? */

	rep_len = recv(sd, &ans, माप(ans), 0);
	अगर (ans.n.nlmsg_type == NLMSG_ERROR ||
	    (rep_len < 0) || !NLMSG_OK((&ans.n), rep_len))
		वापस 0;

	na = (काष्ठा nlattr *) GENLMSG_DATA(&ans);
	na = (काष्ठा nlattr *) ((अक्षर *) na + NLA_ALIGN(na->nla_len));
	अगर (na->nla_type == CTRL_ATTR_FAMILY_ID) अणु
		id = *(__u16 *) NLA_DATA(na);
	पूर्ण
	वापस id;
पूर्ण

#घोषणा average_ms(t, c) (t / 1000000ULL / (c ? c : 1))

अटल व्योम prपूर्णांक_delayacct(काष्ठा taskstats *t)
अणु
	म_लिखो("\n\nCPU   %15s%15s%15s%15s%15s\n"
	       "      %15llu%15llu%15llu%15llu%15.3fms\n"
	       "IO    %15s%15s%15s\n"
	       "      %15llu%15llu%15llums\n"
	       "SWAP  %15s%15s%15s\n"
	       "      %15llu%15llu%15llums\n"
	       "RECLAIM  %12s%15s%15s\n"
	       "      %15llu%15llu%15llums\n"
	       "THRASHING%12s%15s%15s\n"
	       "      %15llu%15llu%15llums\n",
	       "count", "real total", "virtual total",
	       "delay total", "delay average",
	       (अचिन्हित दीर्घ दीर्घ)t->cpu_count,
	       (अचिन्हित दीर्घ दीर्घ)t->cpu_run_real_total,
	       (अचिन्हित दीर्घ दीर्घ)t->cpu_run_भव_total,
	       (अचिन्हित दीर्घ दीर्घ)t->cpu_delay_total,
	       average_ms((द्विगुन)t->cpu_delay_total, t->cpu_count),
	       "count", "delay total", "delay average",
	       (अचिन्हित दीर्घ दीर्घ)t->blkio_count,
	       (अचिन्हित दीर्घ दीर्घ)t->blkio_delay_total,
	       average_ms(t->blkio_delay_total, t->blkio_count),
	       "count", "delay total", "delay average",
	       (अचिन्हित दीर्घ दीर्घ)t->swapin_count,
	       (अचिन्हित दीर्घ दीर्घ)t->swapin_delay_total,
	       average_ms(t->swapin_delay_total, t->swapin_count),
	       "count", "delay total", "delay average",
	       (अचिन्हित दीर्घ दीर्घ)t->मुक्तpages_count,
	       (अचिन्हित दीर्घ दीर्घ)t->मुक्तpages_delay_total,
	       average_ms(t->मुक्तpages_delay_total, t->मुक्तpages_count),
	       "count", "delay total", "delay average",
	       (अचिन्हित दीर्घ दीर्घ)t->thrashing_count,
	       (अचिन्हित दीर्घ दीर्घ)t->thrashing_delay_total,
	       average_ms(t->thrashing_delay_total, t->thrashing_count));
पूर्ण

अटल व्योम task_context_चयन_counts(काष्ठा taskstats *t)
अणु
	म_लिखो("\n\nTask   %15s%15s\n"
	       "       %15llu%15llu\n",
	       "voluntary", "nonvoluntary",
	       (अचिन्हित दीर्घ दीर्घ)t->nvcsw, (अचिन्हित दीर्घ दीर्घ)t->nivcsw);
पूर्ण

अटल व्योम prपूर्णांक_cgroupstats(काष्ठा cgroupstats *c)
अणु
	म_लिखो("sleeping %llu, blocked %llu, running %llu, stopped %llu, "
		"uninterruptible %llu\n", (अचिन्हित दीर्घ दीर्घ)c->nr_sleeping,
		(अचिन्हित दीर्घ दीर्घ)c->nr_io_रुको,
		(अचिन्हित दीर्घ दीर्घ)c->nr_running,
		(अचिन्हित दीर्घ दीर्घ)c->nr_stopped,
		(अचिन्हित दीर्घ दीर्घ)c->nr_unपूर्णांकerruptible);
पूर्ण


अटल व्योम prपूर्णांक_ioacct(काष्ठा taskstats *t)
अणु
	म_लिखो("%s: read=%llu, write=%llu, cancelled_write=%llu\n",
		t->ac_comm,
		(अचिन्हित दीर्घ दीर्घ)t->पढ़ो_bytes,
		(अचिन्हित दीर्घ दीर्घ)t->ग_लिखो_bytes,
		(अचिन्हित दीर्घ दीर्घ)t->cancelled_ग_लिखो_bytes);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक c, rc, rep_len, aggr_len, len2;
	पूर्णांक cmd_type = TASKSTATS_CMD_ATTR_UNSPEC;
	__u16 id;
	__u32 mypid;

	काष्ठा nlattr *na;
	पूर्णांक nl_sd = -1;
	पूर्णांक len = 0;
	pid_t tid = 0;
	pid_t rtid = 0;

	पूर्णांक fd = 0;
	पूर्णांक count = 0;
	पूर्णांक ग_लिखो_file = 0;
	पूर्णांक maskset = 0;
	अक्षर *logfile = शून्य;
	पूर्णांक loop = 0;
	पूर्णांक containerset = 0;
	अक्षर *containerpath = शून्य;
	पूर्णांक cfd = 0;
	पूर्णांक विभाजनing = 0;
	sigset_t sigset;

	काष्ठा msgढाँचा msg;

	जबतक (!विभाजनing) अणु
		c = getopt(argc, argv, "qdiw:r:m:t:p:vlC:c:");
		अगर (c < 0)
			अवरोध;

		चयन (c) अणु
		हाल 'd':
			म_लिखो("print delayacct stats ON\n");
			prपूर्णांक_delays = 1;
			अवरोध;
		हाल 'i':
			म_लिखो("printing IO accounting\n");
			prपूर्णांक_io_accounting = 1;
			अवरोध;
		हाल 'q':
			म_लिखो("printing task/process context switch rates\n");
			prपूर्णांक_task_context_चयन_counts = 1;
			अवरोध;
		हाल 'C':
			containerset = 1;
			containerpath = optarg;
			अवरोध;
		हाल 'w':
			logfile = strdup(optarg);
			म_लिखो("write to file %s\n", logfile);
			ग_लिखो_file = 1;
			अवरोध;
		हाल 'r':
			rcvbufsz = म_से_प(optarg);
			म_लिखो("receive buf size %d\n", rcvbufsz);
			अगर (rcvbufsz < 0)
				err(1, "Invalid rcv buf size\n");
			अवरोध;
		हाल 'm':
			म_नकलन(cpumask, optarg, माप(cpumask));
			cpumask[माप(cpumask) - 1] = '\0';
			maskset = 1;
			म_लिखो("cpumask %s maskset %d\n", cpumask, maskset);
			अवरोध;
		हाल 't':
			tid = म_से_प(optarg);
			अगर (!tid)
				err(1, "Invalid tgid\n");
			cmd_type = TASKSTATS_CMD_ATTR_TGID;
			अवरोध;
		हाल 'p':
			tid = म_से_प(optarg);
			अगर (!tid)
				err(1, "Invalid pid\n");
			cmd_type = TASKSTATS_CMD_ATTR_PID;
			अवरोध;
		हाल 'c':

			/* Block SIGCHLD क्रम sigरुको() later */
			अगर (sigemptyset(&sigset) == -1)
				err(1, "Failed to empty sigset");
			अगर (sigaddset(&sigset, SIGCHLD))
				err(1, "Failed to set sigchld in sigset");
			sigprocmask(SIG_BLOCK, &sigset, शून्य);

			/* विभाजन/exec a child */
			tid = विभाजन();
			अगर (tid < 0)
				err(1, "Fork failed\n");
			अगर (tid == 0)
				अगर (execvp(argv[optind - 1],
				    &argv[optind - 1]) < 0)
					निकास(-1);

			/* Set the command type and aव्योम further processing */
			cmd_type = TASKSTATS_CMD_ATTR_PID;
			विभाजनing = 1;
			अवरोध;
		हाल 'v':
			म_लिखो("debug on\n");
			dbg = 1;
			अवरोध;
		हाल 'l':
			म_लिखो("listen forever\n");
			loop = 1;
			अवरोध;
		शेष:
			usage();
			निकास(-1);
		पूर्ण
	पूर्ण

	अगर (ग_लिखो_file) अणु
		fd = खोलो(logfile, O_WRONLY | O_CREAT | O_TRUNC,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		अगर (fd == -1) अणु
			लिखो_त्रुटि("Cannot open output file\n");
			निकास(1);
		पूर्ण
	पूर्ण

	nl_sd = create_nl_socket(NETLINK_GENERIC);
	अगर (nl_sd < 0)
		err(1, "error creating Netlink socket\n");


	mypid = getpid();
	id = get_family_id(nl_sd);
	अगर (!id) अणु
		ख_लिखो(मानक_त्रुटि, "Error getting family id, errno %d\n", त्रुटि_सं);
		जाओ err;
	पूर्ण
	PRINTF("family id %d\n", id);

	अगर (maskset) अणु
		rc = send_cmd(nl_sd, id, mypid, TASKSTATS_CMD_GET,
			      TASKSTATS_CMD_ATTR_REGISTER_CPUMASK,
			      &cpumask, म_माप(cpumask) + 1);
		PRINTF("Sent register cpumask, retval %d\n", rc);
		अगर (rc < 0) अणु
			ख_लिखो(मानक_त्रुटि, "error sending register cpumask\n");
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (tid && containerset) अणु
		ख_लिखो(मानक_त्रुटि, "Select either -t or -C, not both\n");
		जाओ err;
	पूर्ण

	/*
	 * If we विभाजनed a child, रुको क्रम it to निकास. Cannot use रुकोpid()
	 * as all the delicious data would be reaped as part of the रुको
	 */
	अगर (tid && विभाजनing) अणु
		पूर्णांक sig_received;
		sigरुको(&sigset, &sig_received);
	पूर्ण

	अगर (tid) अणु
		rc = send_cmd(nl_sd, id, mypid, TASKSTATS_CMD_GET,
			      cmd_type, &tid, माप(__u32));
		PRINTF("Sent pid/tgid, retval %d\n", rc);
		अगर (rc < 0) अणु
			ख_लिखो(मानक_त्रुटि, "error sending tid/tgid cmd\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (containerset) अणु
		cfd = खोलो(containerpath, O_RDONLY);
		अगर (cfd < 0) अणु
			लिखो_त्रुटि("error opening container file");
			जाओ err;
		पूर्ण
		rc = send_cmd(nl_sd, id, mypid, CGROUPSTATS_CMD_GET,
			      CGROUPSTATS_CMD_ATTR_FD, &cfd, माप(__u32));
		अगर (rc < 0) अणु
			लिखो_त्रुटि("error sending cgroupstats command");
			जाओ err;
		पूर्ण
	पूर्ण
	अगर (!maskset && !tid && !containerset) अणु
		usage();
		जाओ err;
	पूर्ण

	करो अणु
		rep_len = recv(nl_sd, &msg, माप(msg), 0);
		PRINTF("received %d bytes\n", rep_len);

		अगर (rep_len < 0) अणु
			ख_लिखो(मानक_त्रुटि, "nonfatal reply error: errno %d\n",
				त्रुटि_सं);
			जारी;
		पूर्ण
		अगर (msg.n.nlmsg_type == NLMSG_ERROR ||
		    !NLMSG_OK((&msg.n), rep_len)) अणु
			काष्ठा nlmsgerr *err = NLMSG_DATA(&msg);
			ख_लिखो(मानक_त्रुटि, "fatal reply error,  errno %d\n",
				err->error);
			जाओ करोne;
		पूर्ण

		PRINTF("nlmsghdr size=%zu, nlmsg_len=%d, rep_len=%d\n",
		       माप(काष्ठा nlmsghdr), msg.n.nlmsg_len, rep_len);


		rep_len = GENLMSG_PAYLOAD(&msg.n);

		na = (काष्ठा nlattr *) GENLMSG_DATA(&msg);
		len = 0;
		जबतक (len < rep_len) अणु
			len += NLA_ALIGN(na->nla_len);
			चयन (na->nla_type) अणु
			हाल TASKSTATS_TYPE_AGGR_TGID:
				/* Fall through */
			हाल TASKSTATS_TYPE_AGGR_PID:
				aggr_len = NLA_PAYLOAD(na->nla_len);
				len2 = 0;
				/* For nested attributes, na follows */
				na = (काष्ठा nlattr *) NLA_DATA(na);
				करोne = 0;
				जबतक (len2 < aggr_len) अणु
					चयन (na->nla_type) अणु
					हाल TASKSTATS_TYPE_PID:
						rtid = *(पूर्णांक *) NLA_DATA(na);
						अगर (prपूर्णांक_delays)
							म_लिखो("PID\t%d\n", rtid);
						अवरोध;
					हाल TASKSTATS_TYPE_TGID:
						rtid = *(पूर्णांक *) NLA_DATA(na);
						अगर (prपूर्णांक_delays)
							म_लिखो("TGID\t%d\n", rtid);
						अवरोध;
					हाल TASKSTATS_TYPE_STATS:
						count++;
						अगर (prपूर्णांक_delays)
							prपूर्णांक_delayacct((काष्ठा taskstats *) NLA_DATA(na));
						अगर (prपूर्णांक_io_accounting)
							prपूर्णांक_ioacct((काष्ठा taskstats *) NLA_DATA(na));
						अगर (prपूर्णांक_task_context_चयन_counts)
							task_context_चयन_counts((काष्ठा taskstats *) NLA_DATA(na));
						अगर (fd) अणु
							अगर (ग_लिखो(fd, NLA_DATA(na), na->nla_len) < 0) अणु
								err(1,"write error\n");
							पूर्ण
						पूर्ण
						अगर (!loop)
							जाओ करोne;
						अवरोध;
					हाल TASKSTATS_TYPE_शून्य:
						अवरोध;
					शेष:
						ख_लिखो(मानक_त्रुटि, "Unknown nested"
							" nla_type %d\n",
							na->nla_type);
						अवरोध;
					पूर्ण
					len2 += NLA_ALIGN(na->nla_len);
					na = (काष्ठा nlattr *)((अक्षर *)na +
							       NLA_ALIGN(na->nla_len));
				पूर्ण
				अवरोध;

			हाल CGROUPSTATS_TYPE_CGROUP_STATS:
				prपूर्णांक_cgroupstats(NLA_DATA(na));
				अवरोध;
			शेष:
				ख_लिखो(मानक_त्रुटि, "Unknown nla_type %d\n",
					na->nla_type);
			हाल TASKSTATS_TYPE_शून्य:
				अवरोध;
			पूर्ण
			na = (काष्ठा nlattr *) (GENLMSG_DATA(&msg) + len);
		पूर्ण
	पूर्ण जबतक (loop);
करोne:
	अगर (maskset) अणु
		rc = send_cmd(nl_sd, id, mypid, TASKSTATS_CMD_GET,
			      TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK,
			      &cpumask, म_माप(cpumask) + 1);
		म_लिखो("Sent deregister mask, retval %d\n", rc);
		अगर (rc < 0)
			err(rc, "error sending deregister cpumask\n");
	पूर्ण
err:
	बंद(nl_sd);
	अगर (fd)
		बंद(fd);
	अगर (cfd)
		बंद(cfd);
	वापस 0;
पूर्ण
