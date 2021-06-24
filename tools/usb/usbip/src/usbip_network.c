<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश <sys/socket.h>

#समावेश <माला.स>

#समावेश <arpa/inet.h>
#समावेश <netdb.h>
#समावेश <netinet/tcp.h>
#समावेश <unistd.h>

#अगर_घोषित HAVE_LIBWRAP
#समावेश <tcpd.h>
#पूर्ण_अगर

#समावेश "usbip_common.h"
#समावेश "usbip_network.h"

पूर्णांक usbip_port = 3240;
अक्षर *usbip_port_string = "3240";

व्योम usbip_setup_port_number(अक्षर *arg)
अणु
	dbg("parsing port arg '%s'", arg);
	अक्षर *end;
	अचिन्हित दीर्घ पूर्णांक port = म_से_अदीर्घ(arg, &end, 10);

	अगर (end == arg) अणु
		err("port: could not parse '%s' as a decimal integer", arg);
		वापस;
	पूर्ण

	अगर (*end != '\0') अणु
		err("port: garbage at end of '%s'", arg);
		वापस;
	पूर्ण

	अगर (port > UINT16_MAX) अणु
		err("port: %s too high (max=%d)",
		    arg, UINT16_MAX);
		वापस;
	पूर्ण

	usbip_port = port;
	usbip_port_string = arg;
	info("using port %d (\"%s\")", usbip_port, usbip_port_string);
पूर्ण

uपूर्णांक32_t usbip_net_pack_uपूर्णांक32_t(पूर्णांक pack, uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t i;

	अगर (pack)
		i = htonl(num);
	अन्यथा
		i = ntohl(num);

	वापस i;
पूर्ण

uपूर्णांक16_t usbip_net_pack_uपूर्णांक16_t(पूर्णांक pack, uपूर्णांक16_t num)
अणु
	uपूर्णांक16_t i;

	अगर (pack)
		i = htons(num);
	अन्यथा
		i = ntohs(num);

	वापस i;
पूर्ण

व्योम usbip_net_pack_usb_device(पूर्णांक pack, काष्ठा usbip_usb_device *udev)
अणु
	udev->busnum = usbip_net_pack_uपूर्णांक32_t(pack, udev->busnum);
	udev->devnum = usbip_net_pack_uपूर्णांक32_t(pack, udev->devnum);
	udev->speed = usbip_net_pack_uपूर्णांक32_t(pack, udev->speed);

	udev->idVenकरोr = usbip_net_pack_uपूर्णांक16_t(pack, udev->idVenकरोr);
	udev->idProduct = usbip_net_pack_uपूर्णांक16_t(pack, udev->idProduct);
	udev->bcdDevice = usbip_net_pack_uपूर्णांक16_t(pack, udev->bcdDevice);
पूर्ण

व्योम usbip_net_pack_usb_पूर्णांकerface(पूर्णांक pack __attribute__((unused)),
				  काष्ठा usbip_usb_पूर्णांकerface *udev
				  __attribute__((unused)))
अणु
	/* uपूर्णांक8_t members need nothing */
पूर्ण

अटल sमाप_प्रकार usbip_net_xmit(पूर्णांक sockfd, व्योम *buff, माप_प्रकार bufflen,
			      पूर्णांक sending)
अणु
	sमाप_प्रकार nbytes;
	sमाप_प्रकार total = 0;

	अगर (!bufflen)
		वापस 0;

	करो अणु
		अगर (sending)
			nbytes = send(sockfd, buff, bufflen, 0);
		अन्यथा
			nbytes = recv(sockfd, buff, bufflen, MSG_WAITALL);

		अगर (nbytes <= 0)
			वापस -1;

		buff	 = (व्योम *)((पूर्णांकptr_t) buff + nbytes);
		bufflen	-= nbytes;
		total	+= nbytes;

	पूर्ण जबतक (bufflen > 0);

	वापस total;
पूर्ण

sमाप_प्रकार usbip_net_recv(पूर्णांक sockfd, व्योम *buff, माप_प्रकार bufflen)
अणु
	वापस usbip_net_xmit(sockfd, buff, bufflen, 0);
पूर्ण

sमाप_प्रकार usbip_net_send(पूर्णांक sockfd, व्योम *buff, माप_प्रकार bufflen)
अणु
	वापस usbip_net_xmit(sockfd, buff, bufflen, 1);
पूर्ण

अटल अंतरभूत व्योम usbip_net_pack_op_common(पूर्णांक pack,
					    काष्ठा op_common *op_common)
अणु
	op_common->version = usbip_net_pack_uपूर्णांक16_t(pack, op_common->version);
	op_common->code = usbip_net_pack_uपूर्णांक16_t(pack, op_common->code);
	op_common->status = usbip_net_pack_uपूर्णांक32_t(pack, op_common->status);
पूर्ण

पूर्णांक usbip_net_send_op_common(पूर्णांक sockfd, uपूर्णांक32_t code, uपूर्णांक32_t status)
अणु
	काष्ठा op_common op_common;
	पूर्णांक rc;

	स_रखो(&op_common, 0, माप(op_common));

	op_common.version = USBIP_VERSION;
	op_common.code    = code;
	op_common.status  = status;

	usbip_net_pack_op_common(1, &op_common);

	rc = usbip_net_send(sockfd, &op_common, माप(op_common));
	अगर (rc < 0) अणु
		dbg("usbip_net_send failed: %d", rc);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक usbip_net_recv_op_common(पूर्णांक sockfd, uपूर्णांक16_t *code, पूर्णांक *status)
अणु
	काष्ठा op_common op_common;
	पूर्णांक rc;

	स_रखो(&op_common, 0, माप(op_common));

	rc = usbip_net_recv(sockfd, &op_common, माप(op_common));
	अगर (rc < 0) अणु
		dbg("usbip_net_recv failed: %d", rc);
		जाओ err;
	पूर्ण

	usbip_net_pack_op_common(0, &op_common);

	अगर (op_common.version != USBIP_VERSION) अणु
		err("USBIP Kernel and tool version mismatch: %d %d:",
		    op_common.version, USBIP_VERSION);
		जाओ err;
	पूर्ण

	चयन (*code) अणु
	हाल OP_UNSPEC:
		अवरोध;
	शेष:
		अगर (op_common.code != *code) अणु
			dbg("unexpected pdu %#0x for %#0x", op_common.code,
			    *code);
			/* वापस error status */
			*status = ST_ERROR;
			जाओ err;
		पूर्ण
	पूर्ण

	*status = op_common.status;

	अगर (op_common.status != ST_OK) अणु
		dbg("request failed at peer: %d", op_common.status);
		जाओ err;
	पूर्ण

	*code = op_common.code;

	वापस 0;
err:
	वापस -1;
पूर्ण

पूर्णांक usbip_net_set_reuseaddr(पूर्णांक sockfd)
अणु
	स्थिर पूर्णांक val = 1;
	पूर्णांक ret;

	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, माप(val));
	अगर (ret < 0)
		dbg("setsockopt: SO_REUSEADDR");

	वापस ret;
पूर्ण

पूर्णांक usbip_net_set_nodelay(पूर्णांक sockfd)
अणु
	स्थिर पूर्णांक val = 1;
	पूर्णांक ret;

	ret = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &val, माप(val));
	अगर (ret < 0)
		dbg("setsockopt: TCP_NODELAY");

	वापस ret;
पूर्ण

पूर्णांक usbip_net_set_keepalive(पूर्णांक sockfd)
अणु
	स्थिर पूर्णांक val = 1;
	पूर्णांक ret;

	ret = setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &val, माप(val));
	अगर (ret < 0)
		dbg("setsockopt: SO_KEEPALIVE");

	वापस ret;
पूर्ण

पूर्णांक usbip_net_set_v6only(पूर्णांक sockfd)
अणु
	स्थिर पूर्णांक val = 1;
	पूर्णांक ret;

	ret = setsockopt(sockfd, IPPROTO_IPV6, IPV6_V6ONLY, &val, माप(val));
	अगर (ret < 0)
		dbg("setsockopt: IPV6_V6ONLY");

	वापस ret;
पूर्ण

/*
 * IPv6 Ready
 */
पूर्णांक usbip_net_tcp_connect(अक्षर *hostname, अक्षर *service)
अणु
	काष्ठा addrinfo hपूर्णांकs, *res, *rp;
	पूर्णांक sockfd;
	पूर्णांक ret;

	स_रखो(&hपूर्णांकs, 0, माप(hपूर्णांकs));
	hपूर्णांकs.ai_family = AF_UNSPEC;
	hपूर्णांकs.ai_socktype = SOCK_STREAM;

	/* get all possible addresses */
	ret = getaddrinfo(hostname, service, &hपूर्णांकs, &res);
	अगर (ret < 0) अणु
		dbg("getaddrinfo: %s service %s: %s", hostname, service,
		    gai_म_त्रुटि(ret));
		वापस ret;
	पूर्ण

	/* try the addresses */
	क्रम (rp = res; rp; rp = rp->ai_next) अणु
		sockfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		अगर (sockfd < 0)
			जारी;

		/* should set TCP_NODELAY क्रम usbip */
		usbip_net_set_nodelay(sockfd);
		/* TODO: ग_लिखो code क्रम heartbeat */
		usbip_net_set_keepalive(sockfd);

		अगर (connect(sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
			अवरोध;

		बंद(sockfd);
	पूर्ण

	मुक्तaddrinfo(res);

	अगर (!rp)
		वापस EAI_SYSTEM;

	वापस sockfd;
पूर्ण
