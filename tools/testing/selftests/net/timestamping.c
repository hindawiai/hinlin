<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This program demonstrates how the various समय stamping features in
 * the Linux kernel work. It emulates the behavior of a PTP
 * implementation in stand-alone master mode by sending PTPv1 Sync
 * multicasts once every second. It looks क्रम similar packets, but
 * beyond that करोesn't actually implement PTP.
 *
 * Outgoing packets are समय stamped with SO_TIMESTAMPING with or
 * without hardware support.
 *
 * Incoming packets are समय stamped with SO_TIMESTAMPING with or
 * without hardware support, SIOCGSTAMP[NS] (per-socket समय stamp) and
 * SO_TIMESTAMP[NS].
 *
 * Copyright (C) 2009 Intel Corporation.
 * Author: Patrick Ohly <patrick.ohly@पूर्णांकel.com>
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>

#समावेश <sys/समय.स>
#समावेश <sys/socket.h>
#समावेश <sys/select.h>
#समावेश <sys/ioctl.h>
#समावेश <arpa/inet.h>
#समावेश <net/अगर.h>

#समावेश <यंत्र/types.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/sockios.h>

#अगर_अघोषित SO_TIMESTAMPING
# define SO_TIMESTAMPING         37
# define SCM_TIMESTAMPING        SO_TIMESTAMPING
#पूर्ण_अगर

#अगर_अघोषित SO_TIMESTAMPNS
# define SO_TIMESTAMPNS 35
#पूर्ण_अगर

अटल व्योम usage(स्थिर अक्षर *error)
अणु
	अगर (error)
		म_लिखो("invalid option: %s\n", error);
	म_लिखो("timestamping interface option*\n\n"
	       "Options:\n"
	       "  IP_MULTICAST_LOOP - looping outgoing multicasts\n"
	       "  SO_TIMESTAMP - normal software time stamping, ms resolution\n"
	       "  SO_TIMESTAMPNS - more accurate software time stamping\n"
	       "  SOF_TIMESTAMPING_TX_HARDWARE - hardware time stamping of outgoing packets\n"
	       "  SOF_TIMESTAMPING_TX_SOFTWARE - software fallback for outgoing packets\n"
	       "  SOF_TIMESTAMPING_RX_HARDWARE - hardware time stamping of incoming packets\n"
	       "  SOF_TIMESTAMPING_RX_SOFTWARE - software fallback for incoming packets\n"
	       "  SOF_TIMESTAMPING_SOFTWARE - request reporting of software time stamps\n"
	       "  SOF_TIMESTAMPING_RAW_HARDWARE - request reporting of raw HW time stamps\n"
	       "  SIOCGSTAMP - check last socket time stamp\n"
	       "  SIOCGSTAMPNS - more accurate socket time stamp\n"
	       "  PTPV2 - use PTPv2 messages\n");
	निकास(1);
पूर्ण

अटल व्योम bail(स्थिर अक्षर *error)
अणु
	म_लिखो("%s: %s\n", error, म_त्रुटि(त्रुटि_सं));
	निकास(1);
पूर्ण

अटल स्थिर अचिन्हित अक्षर sync[] = अणु
	0x00, 0x01, 0x00, 0x01,
	0x5f, 0x44, 0x46, 0x4c,
	0x54, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x01, 0x01,

	/* fake uuid */
	0x00, 0x01,
	0x02, 0x03, 0x04, 0x05,

	0x00, 0x01, 0x00, 0x37,
	0x00, 0x00, 0x00, 0x08,
	0x00, 0x00, 0x00, 0x00,
	0x49, 0x05, 0xcd, 0x01,
	0x29, 0xb1, 0x8d, 0xb0,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x01,

	/* fake uuid */
	0x00, 0x01,
	0x02, 0x03, 0x04, 0x05,

	0x00, 0x00, 0x00, 0x37,
	0x00, 0x00, 0x00, 0x04,
	0x44, 0x46, 0x4c, 0x54,
	0x00, 0x00, 0xf0, 0x60,
	0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01,
	0x00, 0x00, 0xf0, 0x60,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x04,
	0x44, 0x46, 0x4c, 0x54,
	0x00, 0x01,

	/* fake uuid */
	0x00, 0x01,
	0x02, 0x03, 0x04, 0x05,

	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल स्थिर अचिन्हित अक्षर sync_v2[] = अणु
	0x00, 0x02, 0x00, 0x2C,
	0x00, 0x00, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF,
	0xFE, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
पूर्ण;

अटल व्योम sendpacket(पूर्णांक sock, काष्ठा sockaddr *addr, socklen_t addr_len, पूर्णांक ptpv2)
अणु
	माप_प्रकार sync_len = ptpv2 ? माप(sync_v2) : माप(sync);
	स्थिर व्योम *sync_p = ptpv2 ? sync_v2 : sync;
	काष्ठा समयval now;
	पूर्णांक res;

	res = sendto(sock, sync_p, sync_len, 0, addr, addr_len);
	समय_लोofday(&now, 0);
	अगर (res < 0)
		म_लिखो("%s: %s\n", "send", म_त्रुटि(त्रुटि_सं));
	अन्यथा
		म_लिखो("%ld.%06ld: sent %d bytes\n",
		       (दीर्घ)now.tv_sec, (दीर्घ)now.tv_usec,
		       res);
पूर्ण

अटल व्योम prपूर्णांकpacket(काष्ठा msghdr *msg, पूर्णांक res,
			अक्षर *data,
			पूर्णांक sock, पूर्णांक recvmsg_flags,
			पूर्णांक siocgstamp, पूर्णांक siocgstampns, पूर्णांक ptpv2)
अणु
	काष्ठा sockaddr_in *from_addr = (काष्ठा sockaddr_in *)msg->msg_name;
	माप_प्रकार sync_len = ptpv2 ? माप(sync_v2) : माप(sync);
	स्थिर व्योम *sync_p = ptpv2 ? sync_v2 : sync;
	काष्ठा cmsghdr *cmsg;
	काष्ठा समयval tv;
	काष्ठा बारpec ts;
	काष्ठा समयval now;

	समय_लोofday(&now, 0);

	म_लिखो("%ld.%06ld: received %s data, %d bytes from %s, %zu bytes control messages\n",
	       (दीर्घ)now.tv_sec, (दीर्घ)now.tv_usec,
	       (recvmsg_flags & MSG_ERRQUEUE) ? "error" : "regular",
	       res,
	       inet_ntoa(from_addr->sin_addr),
	       msg->msg_controllen);
	क्रम (cmsg = CMSG_FIRSTHDR(msg);
	     cmsg;
	     cmsg = CMSG_NXTHDR(msg, cmsg)) अणु
		म_लिखो("   cmsg len %zu: ", cmsg->cmsg_len);
		चयन (cmsg->cmsg_level) अणु
		हाल SOL_SOCKET:
			म_लिखो("SOL_SOCKET ");
			चयन (cmsg->cmsg_type) अणु
			हाल SO_TIMESTAMP: अणु
				काष्ठा समयval *stamp =
					(काष्ठा समयval *)CMSG_DATA(cmsg);
				म_लिखो("SO_TIMESTAMP %ld.%06ld",
				       (दीर्घ)stamp->tv_sec,
				       (दीर्घ)stamp->tv_usec);
				अवरोध;
			पूर्ण
			हाल SO_TIMESTAMPNS: अणु
				काष्ठा बारpec *stamp =
					(काष्ठा बारpec *)CMSG_DATA(cmsg);
				म_लिखो("SO_TIMESTAMPNS %ld.%09ld",
				       (दीर्घ)stamp->tv_sec,
				       (दीर्घ)stamp->tv_nsec);
				अवरोध;
			पूर्ण
			हाल SO_TIMESTAMPING: अणु
				काष्ठा बारpec *stamp =
					(काष्ठा बारpec *)CMSG_DATA(cmsg);
				म_लिखो("SO_TIMESTAMPING ");
				म_लिखो("SW %ld.%09ld ",
				       (दीर्घ)stamp->tv_sec,
				       (दीर्घ)stamp->tv_nsec);
				stamp++;
				/* skip deprecated HW transक्रमmed */
				stamp++;
				म_लिखो("HW raw %ld.%09ld",
				       (दीर्घ)stamp->tv_sec,
				       (दीर्घ)stamp->tv_nsec);
				अवरोध;
			पूर्ण
			शेष:
				म_लिखो("type %d", cmsg->cmsg_type);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल IPPROTO_IP:
			म_लिखो("IPPROTO_IP ");
			चयन (cmsg->cmsg_type) अणु
			हाल IP_RECVERR: अणु
				काष्ठा sock_extended_err *err =
					(काष्ठा sock_extended_err *)CMSG_DATA(cmsg);
				म_लिखो("IP_RECVERR ee_errno '%s' ee_origin %d => %s",
					म_त्रुटि(err->ee_त्रुटि_सं),
					err->ee_origin,
#अगर_घोषित SO_EE_ORIGIN_TIMESTAMPING
					err->ee_origin == SO_EE_ORIGIN_TIMESTAMPING ?
					"bounced packet" : "unexpected origin"
#अन्यथा
					"probably SO_EE_ORIGIN_TIMESTAMPING"
#पूर्ण_अगर
					);
				अगर (res < sync_len)
					म_लिखो(" => truncated data?!");
				अन्यथा अगर (!स_भेद(sync_p, data + res - sync_len, sync_len))
					म_लिखो(" => GOT OUR DATA BACK (HURRAY!)");
				अवरोध;
			पूर्ण
			हाल IP_PKTINFO: अणु
				काष्ठा in_pktinfo *pktinfo =
					(काष्ठा in_pktinfo *)CMSG_DATA(cmsg);
				म_लिखो("IP_PKTINFO interface index %u",
					pktinfo->ipi_अगरindex);
				अवरोध;
			पूर्ण
			शेष:
				म_लिखो("type %d", cmsg->cmsg_type);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			म_लिखो("level %d type %d",
				cmsg->cmsg_level,
				cmsg->cmsg_type);
			अवरोध;
		पूर्ण
		म_लिखो("\n");
	पूर्ण

	अगर (siocgstamp) अणु
		अगर (ioctl(sock, SIOCGSTAMP, &tv))
			म_लिखो("   %s: %s\n", "SIOCGSTAMP", म_त्रुटि(त्रुटि_सं));
		अन्यथा
			म_लिखो("SIOCGSTAMP %ld.%06ld\n",
			       (दीर्घ)tv.tv_sec,
			       (दीर्घ)tv.tv_usec);
	पूर्ण
	अगर (siocgstampns) अणु
		अगर (ioctl(sock, SIOCGSTAMPNS, &ts))
			म_लिखो("   %s: %s\n", "SIOCGSTAMPNS", म_त्रुटि(त्रुटि_सं));
		अन्यथा
			म_लिखो("SIOCGSTAMPNS %ld.%09ld\n",
			       (दीर्घ)ts.tv_sec,
			       (दीर्घ)ts.tv_nsec);
	पूर्ण
पूर्ण

अटल व्योम recvpacket(पूर्णांक sock, पूर्णांक recvmsg_flags,
		       पूर्णांक siocgstamp, पूर्णांक siocgstampns, पूर्णांक ptpv2)
अणु
	अक्षर data[256];
	काष्ठा msghdr msg;
	काष्ठा iovec entry;
	काष्ठा sockaddr_in from_addr;
	काष्ठा अणु
		काष्ठा cmsghdr cm;
		अक्षर control[512];
	पूर्ण control;
	पूर्णांक res;

	स_रखो(&msg, 0, माप(msg));
	msg.msg_iov = &entry;
	msg.msg_iovlen = 1;
	entry.iov_base = data;
	entry.iov_len = माप(data);
	msg.msg_name = (caddr_t)&from_addr;
	msg.msg_namelen = माप(from_addr);
	msg.msg_control = &control;
	msg.msg_controllen = माप(control);

	res = recvmsg(sock, &msg, recvmsg_flags|MSG_DONTWAIT);
	अगर (res < 0) अणु
		म_लिखो("%s %s: %s\n",
		       "recvmsg",
		       (recvmsg_flags & MSG_ERRQUEUE) ? "error" : "regular",
		       म_त्रुटि(त्रुटि_सं));
	पूर्ण अन्यथा अणु
		prपूर्णांकpacket(&msg, res, data,
			    sock, recvmsg_flags,
			    siocgstamp, siocgstampns, ptpv2);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक so_बारtamping_flags = 0;
	पूर्णांक so_बारtamp = 0;
	पूर्णांक so_बारtampns = 0;
	पूर्णांक siocgstamp = 0;
	पूर्णांक siocgstampns = 0;
	पूर्णांक ip_multicast_loop = 0;
	पूर्णांक ptpv2 = 0;
	अक्षर *पूर्णांकerface;
	पूर्णांक i;
	पूर्णांक enabled = 1;
	पूर्णांक sock;
	काष्ठा अगरreq device;
	काष्ठा अगरreq hwtstamp;
	काष्ठा hwtstamp_config hwconfig, hwconfig_requested;
	काष्ठा sockaddr_in addr;
	काष्ठा ip_mreq imr;
	काष्ठा in_addr iaddr;
	पूर्णांक val;
	socklen_t len;
	काष्ठा समयval next;
	माप_प्रकार अगर_len;

	अगर (argc < 2)
		usage(0);
	पूर्णांकerface = argv[1];
	अगर_len = म_माप(पूर्णांकerface);
	अगर (अगर_len >= IFNAMSIZ) अणु
		म_लिखो("interface name exceeds IFNAMSIZ\n");
		निकास(1);
	पूर्ण

	क्रम (i = 2; i < argc; i++) अणु
		अगर (!strहालcmp(argv[i], "SO_TIMESTAMP"))
			so_बारtamp = 1;
		अन्यथा अगर (!strहालcmp(argv[i], "SO_TIMESTAMPNS"))
			so_बारtampns = 1;
		अन्यथा अगर (!strहालcmp(argv[i], "SIOCGSTAMP"))
			siocgstamp = 1;
		अन्यथा अगर (!strहालcmp(argv[i], "SIOCGSTAMPNS"))
			siocgstampns = 1;
		अन्यथा अगर (!strहालcmp(argv[i], "IP_MULTICAST_LOOP"))
			ip_multicast_loop = 1;
		अन्यथा अगर (!strहालcmp(argv[i], "PTPV2"))
			ptpv2 = 1;
		अन्यथा अगर (!strहालcmp(argv[i], "SOF_TIMESTAMPING_TX_HARDWARE"))
			so_बारtamping_flags |= SOF_TIMESTAMPING_TX_HARDWARE;
		अन्यथा अगर (!strहालcmp(argv[i], "SOF_TIMESTAMPING_TX_SOFTWARE"))
			so_बारtamping_flags |= SOF_TIMESTAMPING_TX_SOFTWARE;
		अन्यथा अगर (!strहालcmp(argv[i], "SOF_TIMESTAMPING_RX_HARDWARE"))
			so_बारtamping_flags |= SOF_TIMESTAMPING_RX_HARDWARE;
		अन्यथा अगर (!strहालcmp(argv[i], "SOF_TIMESTAMPING_RX_SOFTWARE"))
			so_बारtamping_flags |= SOF_TIMESTAMPING_RX_SOFTWARE;
		अन्यथा अगर (!strहालcmp(argv[i], "SOF_TIMESTAMPING_SOFTWARE"))
			so_बारtamping_flags |= SOF_TIMESTAMPING_SOFTWARE;
		अन्यथा अगर (!strहालcmp(argv[i], "SOF_TIMESTAMPING_RAW_HARDWARE"))
			so_बारtamping_flags |= SOF_TIMESTAMPING_RAW_HARDWARE;
		अन्यथा
			usage(argv[i]);
	पूर्ण

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	अगर (sock < 0)
		bail("socket");

	स_रखो(&device, 0, माप(device));
	स_नकल(device.अगरr_name, पूर्णांकerface, अगर_len + 1);
	अगर (ioctl(sock, SIOCGIFADDR, &device) < 0)
		bail("getting interface IP address");

	स_रखो(&hwtstamp, 0, माप(hwtstamp));
	स_नकल(hwtstamp.अगरr_name, पूर्णांकerface, अगर_len + 1);
	hwtstamp.अगरr_data = (व्योम *)&hwconfig;
	स_रखो(&hwconfig, 0, माप(hwconfig));
	hwconfig.tx_type =
		(so_बारtamping_flags & SOF_TIMESTAMPING_TX_HARDWARE) ?
		HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	hwconfig.rx_filter =
		(so_बारtamping_flags & SOF_TIMESTAMPING_RX_HARDWARE) ?
		ptpv2 ? HWTSTAMP_FILTER_PTP_V2_L4_SYNC :
		HWTSTAMP_FILTER_PTP_V1_L4_SYNC : HWTSTAMP_FILTER_NONE;
	hwconfig_requested = hwconfig;
	अगर (ioctl(sock, SIOCSHWTSTAMP, &hwtstamp) < 0) अणु
		अगर ((त्रुटि_सं == EINVAL || त्रुटि_सं == ENOTSUP) &&
		    hwconfig_requested.tx_type == HWTSTAMP_TX_OFF &&
		    hwconfig_requested.rx_filter == HWTSTAMP_FILTER_NONE)
			म_लिखो("SIOCSHWTSTAMP: disabling hardware time stamping not possible\n");
		अन्यथा
			bail("SIOCSHWTSTAMP");
	पूर्ण
	म_लिखो("SIOCSHWTSTAMP: tx_type %d requested, got %d; rx_filter %d requested, got %d\n",
	       hwconfig_requested.tx_type, hwconfig.tx_type,
	       hwconfig_requested.rx_filter, hwconfig.rx_filter);

	/* bind to PTP port */
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(319 /* PTP event port */);
	अगर (bind(sock,
		 (काष्ठा sockaddr *)&addr,
		 माप(काष्ठा sockaddr_in)) < 0)
		bail("bind");

	/* set multicast group क्रम outgoing packets */
	inet_aton("224.0.1.130", &iaddr); /* alternate PTP करोमुख्य 1 */
	addr.sin_addr = iaddr;
	imr.imr_multiaddr.s_addr = iaddr.s_addr;
	imr.imr_पूर्णांकerface.s_addr =
		((काष्ठा sockaddr_in *)&device.अगरr_addr)->sin_addr.s_addr;
	अगर (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF,
		       &imr.imr_पूर्णांकerface.s_addr, माप(काष्ठा in_addr)) < 0)
		bail("set multicast");

	/* join multicast group, loop our own packet */
	अगर (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		       &imr, माप(काष्ठा ip_mreq)) < 0)
		bail("join multicast group");

	अगर (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP,
		       &ip_multicast_loop, माप(enabled)) < 0) अणु
		bail("loop multicast");
	पूर्ण

	/* set socket options क्रम समय stamping */
	अगर (so_बारtamp &&
		setsockopt(sock, SOL_SOCKET, SO_TIMESTAMP,
			   &enabled, माप(enabled)) < 0)
		bail("setsockopt SO_TIMESTAMP");

	अगर (so_बारtampns &&
		setsockopt(sock, SOL_SOCKET, SO_TIMESTAMPNS,
			   &enabled, माप(enabled)) < 0)
		bail("setsockopt SO_TIMESTAMPNS");

	अगर (so_बारtamping_flags &&
		setsockopt(sock, SOL_SOCKET, SO_TIMESTAMPING,
			   &so_बारtamping_flags,
			   माप(so_बारtamping_flags)) < 0)
		bail("setsockopt SO_TIMESTAMPING");

	/* request IP_PKTINFO क्रम debugging purposes */
	अगर (setsockopt(sock, SOL_IP, IP_PKTINFO,
		       &enabled, माप(enabled)) < 0)
		म_लिखो("%s: %s\n", "setsockopt IP_PKTINFO", म_त्रुटि(त्रुटि_सं));

	/* verअगरy socket options */
	len = माप(val);
	अगर (माला_लोockopt(sock, SOL_SOCKET, SO_TIMESTAMP, &val, &len) < 0)
		म_लिखो("%s: %s\n", "getsockopt SO_TIMESTAMP", म_त्रुटि(त्रुटि_सं));
	अन्यथा
		म_लिखो("SO_TIMESTAMP %d\n", val);

	अगर (माला_लोockopt(sock, SOL_SOCKET, SO_TIMESTAMPNS, &val, &len) < 0)
		म_लिखो("%s: %s\n", "getsockopt SO_TIMESTAMPNS",
		       म_त्रुटि(त्रुटि_सं));
	अन्यथा
		म_लिखो("SO_TIMESTAMPNS %d\n", val);

	अगर (माला_लोockopt(sock, SOL_SOCKET, SO_TIMESTAMPING, &val, &len) < 0) अणु
		म_लिखो("%s: %s\n", "getsockopt SO_TIMESTAMPING",
		       म_त्रुटि(त्रुटि_सं));
	पूर्ण अन्यथा अणु
		म_लिखो("SO_TIMESTAMPING %d\n", val);
		अगर (val != so_बारtamping_flags)
			म_लिखो("   not the expected value %d\n",
			       so_बारtamping_flags);
	पूर्ण

	/* send packets क्रमever every five seconds */
	समय_लोofday(&next, 0);
	next.tv_sec = (next.tv_sec + 1) / 5 * 5;
	next.tv_usec = 0;
	जबतक (1) अणु
		काष्ठा समयval now;
		काष्ठा समयval delta;
		दीर्घ delta_us;
		पूर्णांक res;
		fd_set पढ़ोfs, errorfs;

		समय_लोofday(&now, 0);
		delta_us = (दीर्घ)(next.tv_sec - now.tv_sec) * 1000000 +
			(दीर्घ)(next.tv_usec - now.tv_usec);
		अगर (delta_us > 0) अणु
			/* जारी रुकोing क्रम समयout or data */
			delta.tv_sec = delta_us / 1000000;
			delta.tv_usec = delta_us % 1000000;

			FD_ZERO(&पढ़ोfs);
			FD_ZERO(&errorfs);
			FD_SET(sock, &पढ़ोfs);
			FD_SET(sock, &errorfs);
			म_लिखो("%ld.%06ld: select %ldus\n",
			       (दीर्घ)now.tv_sec, (दीर्घ)now.tv_usec,
			       delta_us);
			res = select(sock + 1, &पढ़ोfs, 0, &errorfs, &delta);
			समय_लोofday(&now, 0);
			म_लिखो("%ld.%06ld: select returned: %d, %s\n",
			       (दीर्घ)now.tv_sec, (दीर्घ)now.tv_usec,
			       res,
			       res < 0 ? म_त्रुटि(त्रुटि_सं) : "success");
			अगर (res > 0) अणु
				अगर (FD_ISSET(sock, &पढ़ोfs))
					म_लिखो("ready for reading\n");
				अगर (FD_ISSET(sock, &errorfs))
					म_लिखो("has error\n");
				recvpacket(sock, 0,
					   siocgstamp,
					   siocgstampns, ptpv2);
				recvpacket(sock, MSG_ERRQUEUE,
					   siocgstamp,
					   siocgstampns, ptpv2);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* ग_लिखो one packet */
			sendpacket(sock,
				   (काष्ठा sockaddr *)&addr,
				   माप(addr), ptpv2);
			next.tv_sec += 5;
			जारी;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
