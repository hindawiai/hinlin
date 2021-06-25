<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#अगर_घोषित HAVE_CONFIG_H
#समावेश "../config.h"
#पूर्ण_अगर

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <netdb.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <arpa/inet.h>
#समावेश <sys/socket.h>
#समावेश <netinet/in.h>

#अगर_घोषित HAVE_LIBWRAP
#समावेश <tcpd.h>
#पूर्ण_अगर

#समावेश <getopt.h>
#समावेश <संकेत.स>
#समावेश <poll.h>

#समावेश "usbip_host_driver.h"
#समावेश "usbip_host_common.h"
#समावेश "usbip_device_driver.h"
#समावेश "usbip_common.h"
#समावेश "usbip_network.h"
#समावेश "list.h"

#अघोषित  PROGNAME
#घोषणा PROGNAME "usbipd"
#घोषणा MAXSOCKFD 20

#घोषणा MAIN_LOOP_TIMEOUT 10

#घोषणा DEFAULT_PID_खाता "/var/run/" PROGNAME ".pid"

अटल स्थिर अक्षर usbip_version_string[] = PACKAGE_STRING;

अटल स्थिर अक्षर usbipd_help_string[] =
	"usage: usbipd [options]\n"
	"\n"
	"	-4, --ipv4\n"
	"		Bind to IPv4. Default is both.\n"
	"\n"
	"	-6, --ipv6\n"
	"		Bind to IPv6. Default is both.\n"
	"\n"
	"	-e, --device\n"
	"		Run in device mode.\n"
	"		Rather than drive an attached device, create\n"
	"		a virtual UDC to bind gadgets to.\n"
	"\n"
	"	-D, --daemon\n"
	"		Run as a daemon process.\n"
	"\n"
	"	-d, --debug\n"
	"		Print debugging information.\n"
	"\n"
	"	-PFILE, --pid FILE\n"
	"		Write process id to FILE.\n"
	"		If no FILE specified, use " DEFAULT_PID_खाता "\n"
	"\n"
	"	-tPORT, --tcp-port PORT\n"
	"		Listen on TCP/IP port PORT.\n"
	"\n"
	"	-h, --help\n"
	"		Print this help.\n"
	"\n"
	"	-v, --version\n"
	"		Show version.\n";

अटल काष्ठा usbip_host_driver *driver;

अटल व्योम usbipd_help(व्योम)
अणु
	म_लिखो("%s\n", usbipd_help_string);
पूर्ण

अटल पूर्णांक recv_request_import(पूर्णांक sockfd)
अणु
	काष्ठा op_import_request req;
	काष्ठा usbip_exported_device *edev;
	काष्ठा usbip_usb_device pdu_udev;
	काष्ठा list_head *i;
	पूर्णांक found = 0;
	पूर्णांक status = ST_OK;
	पूर्णांक rc;

	स_रखो(&req, 0, माप(req));

	rc = usbip_net_recv(sockfd, &req, माप(req));
	अगर (rc < 0) अणु
		dbg("usbip_net_recv failed: import request");
		वापस -1;
	पूर्ण
	PACK_OP_IMPORT_REQUEST(0, &req);

	list_क्रम_each(i, &driver->edev_list) अणु
		edev = list_entry(i, काष्ठा usbip_exported_device, node);
		अगर (!म_भेदन(req.busid, edev->udev.busid, SYSFS_BUS_ID_SIZE)) अणु
			info("found requested device: %s", req.busid);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		/* should set TCP_NODELAY क्रम usbip */
		usbip_net_set_nodelay(sockfd);

		/* export device needs a TCP/IP socket descriptor */
		status = usbip_export_device(edev, sockfd);
		अगर (status < 0)
			status = ST_NA;
	पूर्ण अन्यथा अणु
		info("requested device not found: %s", req.busid);
		status = ST_NODEV;
	पूर्ण

	rc = usbip_net_send_op_common(sockfd, OP_REP_IMPORT, status);
	अगर (rc < 0) अणु
		dbg("usbip_net_send_op_common failed: %#0x", OP_REP_IMPORT);
		वापस -1;
	पूर्ण

	अगर (status) अणु
		dbg("import request busid %s: failed", req.busid);
		वापस -1;
	पूर्ण

	स_नकल(&pdu_udev, &edev->udev, माप(pdu_udev));
	usbip_net_pack_usb_device(1, &pdu_udev);

	rc = usbip_net_send(sockfd, &pdu_udev, माप(pdu_udev));
	अगर (rc < 0) अणु
		dbg("usbip_net_send failed: devinfo");
		वापस -1;
	पूर्ण

	dbg("import request busid %s: complete", req.busid);

	वापस 0;
पूर्ण

अटल पूर्णांक send_reply_devlist(पूर्णांक connfd)
अणु
	काष्ठा usbip_exported_device *edev;
	काष्ठा usbip_usb_device pdu_udev;
	काष्ठा usbip_usb_पूर्णांकerface pdu_uinf;
	काष्ठा op_devlist_reply reply;
	काष्ठा list_head *j;
	पूर्णांक rc, i;

	/*
	 * Exclude devices that are alपढ़ोy exported to a client from
	 * the exportable device list to aव्योम:
	 *	- import requests क्रम devices that are exported only to
	 *	  fail the request.
	 *	- revealing devices that are imported by a client to
	 *	  another client.
	 */

	reply.ndev = 0;
	/* number of exported devices */
	list_क्रम_each(j, &driver->edev_list) अणु
		edev = list_entry(j, काष्ठा usbip_exported_device, node);
		अगर (edev->status != SDEV_ST_USED)
			reply.ndev += 1;
	पूर्ण
	info("exportable devices: %d", reply.ndev);

	rc = usbip_net_send_op_common(connfd, OP_REP_DEVLIST, ST_OK);
	अगर (rc < 0) अणु
		dbg("usbip_net_send_op_common failed: %#0x", OP_REP_DEVLIST);
		वापस -1;
	पूर्ण
	PACK_OP_DEVLIST_REPLY(1, &reply);

	rc = usbip_net_send(connfd, &reply, माप(reply));
	अगर (rc < 0) अणु
		dbg("usbip_net_send failed: %#0x", OP_REP_DEVLIST);
		वापस -1;
	पूर्ण

	list_क्रम_each(j, &driver->edev_list) अणु
		edev = list_entry(j, काष्ठा usbip_exported_device, node);
		अगर (edev->status == SDEV_ST_USED)
			जारी;

		dump_usb_device(&edev->udev);
		स_नकल(&pdu_udev, &edev->udev, माप(pdu_udev));
		usbip_net_pack_usb_device(1, &pdu_udev);

		rc = usbip_net_send(connfd, &pdu_udev, माप(pdu_udev));
		अगर (rc < 0) अणु
			dbg("usbip_net_send failed: pdu_udev");
			वापस -1;
		पूर्ण

		क्रम (i = 0; i < edev->udev.bNumInterfaces; i++) अणु
			dump_usb_पूर्णांकerface(&edev->uinf[i]);
			स_नकल(&pdu_uinf, &edev->uinf[i], माप(pdu_uinf));
			usbip_net_pack_usb_पूर्णांकerface(1, &pdu_uinf);

			rc = usbip_net_send(connfd, &pdu_uinf,
					माप(pdu_uinf));
			अगर (rc < 0) अणु
				err("usbip_net_send failed: pdu_uinf");
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक recv_request_devlist(पूर्णांक connfd)
अणु
	काष्ठा op_devlist_request req;
	पूर्णांक rc;

	स_रखो(&req, 0, माप(req));

	rc = usbip_net_recv(connfd, &req, माप(req));
	अगर (rc < 0) अणु
		dbg("usbip_net_recv failed: devlist request");
		वापस -1;
	पूर्ण

	rc = send_reply_devlist(connfd);
	अगर (rc < 0) अणु
		dbg("send_reply_devlist failed");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक recv_pdu(पूर्णांक connfd)
अणु
	uपूर्णांक16_t code = OP_UNSPEC;
	पूर्णांक ret;
	पूर्णांक status;

	ret = usbip_net_recv_op_common(connfd, &code, &status);
	अगर (ret < 0) अणु
		dbg("could not receive opcode: %#0x", code);
		वापस -1;
	पूर्ण

	ret = usbip_refresh_device_list(driver);
	अगर (ret < 0) अणु
		dbg("could not refresh device list: %d", ret);
		वापस -1;
	पूर्ण

	info("received request: %#0x(%d)", code, connfd);
	चयन (code) अणु
	हाल OP_REQ_DEVLIST:
		ret = recv_request_devlist(connfd);
		अवरोध;
	हाल OP_REQ_IMPORT:
		ret = recv_request_import(connfd);
		अवरोध;
	हाल OP_REQ_DEVINFO:
	हाल OP_REQ_CRYPKEY:
	शेष:
		err("received an unknown opcode: %#0x", code);
		ret = -1;
	पूर्ण

	अगर (ret == 0)
		info("request %#0x(%d): complete", code, connfd);
	अन्यथा
		info("request %#0x(%d): failed", code, connfd);

	वापस ret;
पूर्ण

#अगर_घोषित HAVE_LIBWRAP
अटल पूर्णांक tcpd_auth(पूर्णांक connfd)
अणु
	काष्ठा request_info request;
	पूर्णांक rc;

	request_init(&request, RQ_DAEMON, PROGNAME, RQ_खाता, connfd, 0);
	fromhost(&request);
	rc = hosts_access(&request);
	अगर (rc == 0)
		वापस -1;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक करो_accept(पूर्णांक listenfd)
अणु
	पूर्णांक connfd;
	काष्ठा sockaddr_storage ss;
	socklen_t len = माप(ss);
	अक्षर host[NI_MAXHOST], port[NI_MAXSERV];
	पूर्णांक rc;

	स_रखो(&ss, 0, माप(ss));

	connfd = accept(listenfd, (काष्ठा sockaddr *)&ss, &len);
	अगर (connfd < 0) अणु
		err("failed to accept connection");
		वापस -1;
	पूर्ण

	rc = getnameinfo((काष्ठा sockaddr *)&ss, len, host, माप(host),
			 port, माप(port), NI_NUMERICHOST | NI_NUMERICSERV);
	अगर (rc)
		err("getnameinfo: %s", gai_म_त्रुटि(rc));

#अगर_घोषित HAVE_LIBWRAP
	rc = tcpd_auth(connfd);
	अगर (rc < 0) अणु
		info("denied access from %s", host);
		बंद(connfd);
		वापस -1;
	पूर्ण
#पूर्ण_अगर
	info("connection from %s:%s", host, port);

	वापस connfd;
पूर्ण

पूर्णांक process_request(पूर्णांक listenfd)
अणु
	pid_t childpid;
	पूर्णांक connfd;

	connfd = करो_accept(listenfd);
	अगर (connfd < 0)
		वापस -1;
	childpid = विभाजन();
	अगर (childpid == 0) अणु
		बंद(listenfd);
		recv_pdu(connfd);
		निकास(0);
	पूर्ण
	बंद(connfd);
	वापस 0;
पूर्ण

अटल व्योम addrinfo_to_text(काष्ठा addrinfo *ai, अक्षर buf[],
			     स्थिर माप_प्रकार buf_size)
अणु
	अक्षर hbuf[NI_MAXHOST];
	अक्षर sbuf[NI_MAXSERV];
	पूर्णांक rc;

	buf[0] = '\0';

	rc = getnameinfo(ai->ai_addr, ai->ai_addrlen, hbuf, माप(hbuf),
			 sbuf, माप(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
	अगर (rc)
		err("getnameinfo: %s", gai_म_त्रुटि(rc));

	snम_लिखो(buf, buf_size, "%s:%s", hbuf, sbuf);
पूर्ण

अटल पूर्णांक listen_all_addrinfo(काष्ठा addrinfo *ai_head, पूर्णांक sockfdlist[],
			     पूर्णांक maxsockfd)
अणु
	काष्ठा addrinfo *ai;
	पूर्णांक ret, nsockfd = 0;
	स्थिर माप_प्रकार ai_buf_size = NI_MAXHOST + NI_MAXSERV + 2;
	अक्षर ai_buf[ai_buf_size];

	क्रम (ai = ai_head; ai && nsockfd < maxsockfd; ai = ai->ai_next) अणु
		पूर्णांक sock;

		addrinfo_to_text(ai, ai_buf, ai_buf_size);
		dbg("opening %s", ai_buf);
		sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		अगर (sock < 0) अणु
			err("socket: %s: %d (%s)",
			    ai_buf, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			जारी;
		पूर्ण

		usbip_net_set_reuseaddr(sock);
		usbip_net_set_nodelay(sock);
		/* We use seperate sockets क्रम IPv4 and IPv6
		 * (see करो_standalone_mode()) */
		usbip_net_set_v6only(sock);

		ret = bind(sock, ai->ai_addr, ai->ai_addrlen);
		अगर (ret < 0) अणु
			err("bind: %s: %d (%s)",
			    ai_buf, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			बंद(sock);
			जारी;
		पूर्ण

		ret = listen(sock, SOMAXCONN);
		अगर (ret < 0) अणु
			err("listen: %s: %d (%s)",
			    ai_buf, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			बंद(sock);
			जारी;
		पूर्ण

		info("listening on %s", ai_buf);
		sockfdlist[nsockfd++] = sock;
	पूर्ण

	वापस nsockfd;
पूर्ण

अटल काष्ठा addrinfo *करो_getaddrinfo(अक्षर *host, पूर्णांक ai_family)
अणु
	काष्ठा addrinfo hपूर्णांकs, *ai_head;
	पूर्णांक rc;

	स_रखो(&hपूर्णांकs, 0, माप(hपूर्णांकs));
	hपूर्णांकs.ai_family   = ai_family;
	hपूर्णांकs.ai_socktype = SOCK_STREAM;
	hपूर्णांकs.ai_flags    = AI_PASSIVE;

	rc = getaddrinfo(host, usbip_port_string, &hपूर्णांकs, &ai_head);
	अगर (rc) अणु
		err("failed to get a network address %s: %s", usbip_port_string,
		    gai_म_त्रुटि(rc));
		वापस शून्य;
	पूर्ण

	वापस ai_head;
पूर्ण

अटल व्योम संकेत_handler(पूर्णांक i)
अणु
	dbg("received '%s' signal", strसंकेत(i));
पूर्ण

अटल व्योम set_संकेत(व्योम)
अणु
	काष्ठा sigaction act;

	स_रखो(&act, 0, माप(act));
	act.sa_handler = संकेत_handler;
	sigemptyset(&act.sa_mask);
	sigaction(संक_इति, &act, शून्य);
	sigaction(संक_विघ्न, &act, शून्य);
	act.sa_handler = संक_छोड़ो;
	sigaction(SIGCHLD, &act, शून्य);
पूर्ण

अटल स्थिर अक्षर *pid_file;

अटल व्योम ग_लिखो_pid_file(व्योम)
अणु
	अगर (pid_file) अणु
		dbg("creating pid file %s", pid_file);
		खाता *fp;

		fp = ख_खोलो(pid_file, "w");
		अगर (!fp) अणु
			err("pid_file: %s: %d (%s)",
			    pid_file, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			वापस;
		पूर्ण
		ख_लिखो(fp, "%d\n", getpid());
		ख_बंद(fp);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_pid_file(व्योम)
अणु
	अगर (pid_file) अणु
		dbg("removing pid file %s", pid_file);
		unlink(pid_file);
	पूर्ण
पूर्ण

अटल पूर्णांक करो_standalone_mode(पूर्णांक daemonize, पूर्णांक ipv4, पूर्णांक ipv6)
अणु
	काष्ठा addrinfo *ai_head;
	पूर्णांक sockfdlist[MAXSOCKFD];
	पूर्णांक nsockfd, family;
	पूर्णांक i, terminate;
	काष्ठा pollfd *fds;
	काष्ठा बारpec समयout;
	sigset_t sigmask;

	अगर (usbip_driver_खोलो(driver))
		वापस -1;

	अगर (daemonize) अणु
		अगर (daemon(0, 0) < 0) अणु
			err("daemonizing failed: %s", म_त्रुटि(त्रुटि_सं));
			usbip_driver_बंद(driver);
			वापस -1;
		पूर्ण
		umask(0);
		usbip_use_syslog = 1;
	पूर्ण
	set_संकेत();
	ग_लिखो_pid_file();

	info("starting " PROGNAME " (%s)", usbip_version_string);

	/*
	 * To suppress warnings on प्रणालीs with bindv6only disabled
	 * (शेष), we use seperate sockets क्रम IPv6 and IPv4 and set
	 * IPV6_V6ONLY on the IPv6 sockets.
	 */
	अगर (ipv4 && ipv6)
		family = AF_UNSPEC;
	अन्यथा अगर (ipv4)
		family = AF_INET;
	अन्यथा
		family = AF_INET6;

	ai_head = करो_getaddrinfo(शून्य, family);
	अगर (!ai_head) अणु
		usbip_driver_बंद(driver);
		वापस -1;
	पूर्ण
	nsockfd = listen_all_addrinfo(ai_head, sockfdlist,
		माप(sockfdlist) / माप(*sockfdlist));
	मुक्तaddrinfo(ai_head);
	अगर (nsockfd <= 0) अणु
		err("failed to open a listening socket");
		usbip_driver_बंद(driver);
		वापस -1;
	पूर्ण

	dbg("listening on %d address%s", nsockfd, (nsockfd == 1) ? "" : "es");

	fds = सुस्मृति(nsockfd, माप(काष्ठा pollfd));
	क्रम (i = 0; i < nsockfd; i++) अणु
		fds[i].fd = sockfdlist[i];
		fds[i].events = POLLIN;
	पूर्ण
	समयout.tv_sec = MAIN_LOOP_TIMEOUT;
	समयout.tv_nsec = 0;

	sigfillset(&sigmask);
	sigdअन्यथाt(&sigmask, संक_इति);
	sigdअन्यथाt(&sigmask, संक_विघ्न);

	terminate = 0;
	जबतक (!terminate) अणु
		पूर्णांक r;

		r = ppoll(fds, nsockfd, &समयout, &sigmask);
		अगर (r < 0) अणु
			dbg("%s", म_त्रुटि(त्रुटि_सं));
			terminate = 1;
		पूर्ण अन्यथा अगर (r) अणु
			क्रम (i = 0; i < nsockfd; i++) अणु
				अगर (fds[i].revents & POLLIN) अणु
					dbg("read event on fd[%d]=%d",
					    i, sockfdlist[i]);
					process_request(sockfdlist[i]);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			dbg("heartbeat timeout on ppoll()");
		पूर्ण
	पूर्ण

	info("shutting down " PROGNAME);
	मुक्त(fds);
	usbip_driver_बंद(driver);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अटल स्थिर काष्ठा option दीर्घopts[] = अणु
		अणु "ipv4",     no_argument,       शून्य, '4' पूर्ण,
		अणु "ipv6",     no_argument,       शून्य, '6' पूर्ण,
		अणु "daemon",   no_argument,       शून्य, 'D' पूर्ण,
		अणु "daemon",   no_argument,       शून्य, 'D' पूर्ण,
		अणु "debug",    no_argument,       शून्य, 'd' पूर्ण,
		अणु "device",   no_argument,       शून्य, 'e' पूर्ण,
		अणु "pid",      optional_argument, शून्य, 'P' पूर्ण,
		अणु "tcp-port", required_argument, शून्य, 't' पूर्ण,
		अणु "help",     no_argument,       शून्य, 'h' पूर्ण,
		अणु "version",  no_argument,       शून्य, 'v' पूर्ण,
		अणु शून्य,	      0,                 शून्य,  0  पूर्ण
	पूर्ण;

	क्रमागत अणु
		cmd_standalone_mode = 1,
		cmd_help,
		cmd_version
	पूर्ण cmd;

	पूर्णांक daemonize = 0;
	पूर्णांक ipv4 = 0, ipv6 = 0;
	पूर्णांक opt, rc = -1;

	pid_file = शून्य;

	usbip_use_मानक_त्रुटि = 1;
	usbip_use_syslog = 0;

	अगर (geteuid() != 0)
		err("not running as root?");

	cmd = cmd_standalone_mode;
	driver = &host_driver;
	क्रम (;;) अणु
		opt = getopt_दीर्घ(argc, argv, "46DdeP::t:hv", दीर्घopts, शून्य);

		अगर (opt == -1)
			अवरोध;

		चयन (opt) अणु
		हाल '4':
			ipv4 = 1;
			अवरोध;
		हाल '6':
			ipv6 = 1;
			अवरोध;
		हाल 'D':
			daemonize = 1;
			अवरोध;
		हाल 'd':
			usbip_use_debug = 1;
			अवरोध;
		हाल 'h':
			cmd = cmd_help;
			अवरोध;
		हाल 'P':
			pid_file = optarg ? optarg : DEFAULT_PID_खाता;
			अवरोध;
		हाल 't':
			usbip_setup_port_number(optarg);
			अवरोध;
		हाल 'v':
			cmd = cmd_version;
			अवरोध;
		हाल 'e':
			driver = &device_driver;
			अवरोध;
		हाल '?':
			usbipd_help();
		शेष:
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (!ipv4 && !ipv6)
		ipv4 = ipv6 = 1;

	चयन (cmd) अणु
	हाल cmd_standalone_mode:
		rc = करो_standalone_mode(daemonize, ipv4, ipv6);
		हटाओ_pid_file();
		अवरोध;
	हाल cmd_version:
		म_लिखो(PROGNAME " (%s)\n", usbip_version_string);
		rc = 0;
		अवरोध;
	हाल cmd_help:
		usbipd_help();
		rc = 0;
		अवरोध;
	शेष:
		usbipd_help();
		जाओ err_out;
	पूर्ण

err_out:
	वापस (rc > -1 ? निकास_सफल : निकास_त्रुटि);
पूर्ण
