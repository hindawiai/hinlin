<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* nettest - used क्रम functional tests of networking APIs
 *
 * Copyright (c) 2013-2019 David Ahern <dsahern@gmail.com>. All rights reserved.
 */

#घोषणा _GNU_SOURCE
#समावेश <features.h>
#समावेश <sys/types.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/socket.h>
#समावेश <sys/रुको.h>
#समावेश <linux/tcp.h>
#समावेश <arpa/inet.h>
#समावेश <net/अगर.h>
#समावेश <netinet/in.h>
#समावेश <netdb.h>
#समावेश <fcntl.h>
#समावेश <libgen.h>
#समावेश <सीमा.स>
#समावेश <sched.h>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <समय.स>
#समावेश <त्रुटिसं.स>

#अगर_अघोषित IPV6_UNICAST_IF
#घोषणा IPV6_UNICAST_IF         76
#पूर्ण_अगर
#अगर_अघोषित IPV6_MULTICAST_IF
#घोषणा IPV6_MULTICAST_IF       17
#पूर्ण_अगर

#घोषणा DEFAULT_PORT 12345

#घोषणा NS_PREFIX "/run/netns/"

#अगर_अघोषित MAX
#घोषणा MAX(a, b)  ((a) > (b) ? (a) : (b))
#पूर्ण_अगर
#अगर_अघोषित MIN
#घोषणा MIN(a, b)  ((a) < (b) ? (a) : (b))
#पूर्ण_अगर

काष्ठा sock_args अणु
	/* local address */
	स्थिर अक्षर *local_addr_str;
	स्थिर अक्षर *client_local_addr_str;
	जोड़ अणु
		काष्ठा in_addr  in;
		काष्ठा in6_addr in6;
	पूर्ण local_addr;

	/* remote address */
	स्थिर अक्षर *remote_addr_str;
	जोड़ अणु
		काष्ठा in_addr  in;
		काष्ठा in6_addr in6;
	पूर्ण remote_addr;
	पूर्णांक scope_id;  /* remote scope; v6 send only */

	काष्ठा in_addr grp;     /* multicast group */

	अचिन्हित पूर्णांक has_local_ip:1,
		     has_remote_ip:1,
		     has_grp:1,
		     has_expected_laddr:1,
		     has_expected_raddr:1,
		     bind_test_only:1;

	अचिन्हित लघु port;

	पूर्णांक type;      /* DGRAM, STREAM, RAW */
	पूर्णांक protocol;
	पूर्णांक version;   /* AF_INET/AF_INET6 */

	पूर्णांक use_setsockopt;
	पूर्णांक use_cmsg;
	स्थिर अक्षर *dev;
	स्थिर अक्षर *server_dev;
	पूर्णांक अगरindex;

	स्थिर अक्षर *clientns;
	स्थिर अक्षर *serverns;

	स्थिर अक्षर *password;
	स्थिर अक्षर *client_pw;
	/* prefix क्रम MD5 password */
	स्थिर अक्षर *md5_prefix_str;
	जोड़ अणु
		काष्ठा sockaddr_in v4;
		काष्ठा sockaddr_in6 v6;
	पूर्ण md5_prefix;
	अचिन्हित पूर्णांक prefix_len;

	/* expected addresses and device index क्रम connection */
	स्थिर अक्षर *expected_dev;
	स्थिर अक्षर *expected_server_dev;
	पूर्णांक expected_अगरindex;

	/* local address */
	स्थिर अक्षर *expected_laddr_str;
	जोड़ अणु
		काष्ठा in_addr  in;
		काष्ठा in6_addr in6;
	पूर्ण expected_laddr;

	/* remote address */
	स्थिर अक्षर *expected_raddr_str;
	जोड़ अणु
		काष्ठा in_addr  in;
		काष्ठा in6_addr in6;
	पूर्ण expected_raddr;
पूर्ण;

अटल पूर्णांक server_mode;
अटल अचिन्हित पूर्णांक prog_समयout = 5;
अटल अचिन्हित पूर्णांक पूर्णांकeractive;
अटल पूर्णांक iter = 1;
अटल अक्षर *msg = "Hello world!";
अटल पूर्णांक msglen;
अटल पूर्णांक quiet;
अटल पूर्णांक try_broadcast = 1;

अटल अक्षर *बारtamp(अक्षर *समयbuf, पूर्णांक buflen)
अणु
	समय_प्रकार now;

	now = समय(शून्य);
	अगर (स_माला(समयbuf, buflen, "%T", स_स्थानीय(&now)) == 0) अणु
		स_रखो(समयbuf, 0, buflen);
		म_नकलन(समयbuf, "00:00:00", buflen-1);
	पूर्ण

	वापस समयbuf;
पूर्ण

अटल व्योम log_msg(स्थिर अक्षर *क्रमmat, ...)
अणु
	अक्षर समयbuf[64];
	बहु_सूची args;

	अगर (quiet)
		वापस;

	ख_लिखो(मानक_निकास, "%s %s:",
		बारtamp(समयbuf, माप(समयbuf)),
		server_mode ? "server" : "client");
	बहु_शुरू(args, क्रमmat);
	भख_लिखो(मानक_निकास, क्रमmat, args);
	बहु_पूर्ण(args);

	ख_साफ(मानक_निकास);
पूर्ण

अटल व्योम log_error(स्थिर अक्षर *क्रमmat, ...)
अणु
	अक्षर समयbuf[64];
	बहु_सूची args;

	अगर (quiet)
		वापस;

	ख_लिखो(मानक_त्रुटि, "%s %s:",
		बारtamp(समयbuf, माप(समयbuf)),
		server_mode ? "server" : "client");
	बहु_शुरू(args, क्रमmat);
	भख_लिखो(मानक_त्रुटि, क्रमmat, args);
	बहु_पूर्ण(args);

	ख_साफ(मानक_त्रुटि);
पूर्ण

अटल व्योम log_err_त्रुटि_सं(स्थिर अक्षर *fmt, ...)
अणु
	अक्षर समयbuf[64];
	बहु_सूची args;

	अगर (quiet)
		वापस;

	ख_लिखो(मानक_त्रुटि, "%s %s: ",
		बारtamp(समयbuf, माप(समयbuf)),
		server_mode ? "server" : "client");
	बहु_शुरू(args, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, args);
	बहु_पूर्ण(args);

	ख_लिखो(मानक_त्रुटि, ": %d: %s\n", त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
	ख_साफ(मानक_त्रुटि);
पूर्ण

अटल व्योम log_address(स्थिर अक्षर *desc, काष्ठा sockaddr *sa)
अणु
	अक्षर addrstr[64];

	अगर (quiet)
		वापस;

	अगर (sa->sa_family == AF_INET) अणु
		काष्ठा sockaddr_in *s = (काष्ठा sockaddr_in *) sa;

		log_msg("%s %s:%d\n",
			desc,
			inet_ntop(AF_INET, &s->sin_addr, addrstr,
				  माप(addrstr)),
			ntohs(s->sin_port));

	पूर्ण अन्यथा अगर (sa->sa_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *s6 = (काष्ठा sockaddr_in6 *) sa;

		log_msg("%s [%s]:%d\n",
			desc,
			inet_ntop(AF_INET6, &s6->sin6_addr, addrstr,
				  माप(addrstr)),
			ntohs(s6->sin6_port));
	पूर्ण

	ख_साफ(मानक_निकास);
पूर्ण

अटल पूर्णांक चयन_ns(स्थिर अक्षर *ns)
अणु
	अक्षर path[PATH_MAX];
	पूर्णांक fd, ret;

	अगर (geteuid())
		log_error("warning: likely need root to set netns %s!\n", ns);

	snम_लिखो(path, माप(path), "%s%s", NS_PREFIX, ns);
	fd = खोलो(path, 0);
	अगर (fd < 0) अणु
		log_err_त्रुटि_सं("Failed to open netns path; can not switch netns");
		वापस 1;
	पूर्ण

	ret = setns(fd, CLONE_NEWNET);
	बंद(fd);

	वापस ret;
पूर्ण

अटल पूर्णांक tcp_md5sig(पूर्णांक sd, व्योम *addr, socklen_t alen, काष्ठा sock_args *args)
अणु
	पूर्णांक keylen = म_माप(args->password);
	काष्ठा tcp_md5sig md5sig = अणुपूर्ण;
	पूर्णांक opt = TCP_MD5SIG;
	पूर्णांक rc;

	md5sig.tcpm_keylen = keylen;
	स_नकल(md5sig.tcpm_key, args->password, keylen);

	अगर (args->prefix_len) अणु
		opt = TCP_MD5SIG_EXT;
		md5sig.tcpm_flags |= TCP_MD5SIG_FLAG_PREFIX;

		md5sig.tcpm_prefixlen = args->prefix_len;
		addr = &args->md5_prefix;
	पूर्ण
	स_नकल(&md5sig.tcpm_addr, addr, alen);

	अगर (args->अगरindex) अणु
		opt = TCP_MD5SIG_EXT;
		md5sig.tcpm_flags |= TCP_MD5SIG_FLAG_IFINDEX;

		md5sig.tcpm_अगरindex = args->अगरindex;
	पूर्ण

	rc = setsockopt(sd, IPPROTO_TCP, opt, &md5sig, माप(md5sig));
	अगर (rc < 0) अणु
		/* ENOENT is harmless. Returned when a password is cleared */
		अगर (त्रुटि_सं == ENOENT)
			rc = 0;
		अन्यथा
			log_err_त्रुटि_सं("setsockopt(TCP_MD5SIG)");
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक tcp_md5_remote(पूर्णांक sd, काष्ठा sock_args *args)
अणु
	काष्ठा sockaddr_in sin = अणु
		.sin_family = AF_INET,
	पूर्ण;
	काष्ठा sockaddr_in6 sin6 = अणु
		.sin6_family = AF_INET6,
	पूर्ण;
	व्योम *addr;
	पूर्णांक alen;

	चयन (args->version) अणु
	हाल AF_INET:
		sin.sin_port = htons(args->port);
		sin.sin_addr = args->md5_prefix.v4.sin_addr;
		addr = &sin;
		alen = माप(sin);
		अवरोध;
	हाल AF_INET6:
		sin6.sin6_port = htons(args->port);
		sin6.sin6_addr = args->md5_prefix.v6.sin6_addr;
		addr = &sin6;
		alen = माप(sin6);
		अवरोध;
	शेष:
		log_error("unknown address family\n");
		निकास(1);
	पूर्ण

	अगर (tcp_md5sig(sd, addr, alen, args))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक get_अगरidx(स्थिर अक्षर *अगरname)
अणु
	काष्ठा अगरreq अगरdata;
	पूर्णांक sd, rc;

	अगर (!अगरname || *अगरname == '\0')
		वापस -1;

	स_रखो(&अगरdata, 0, माप(अगरdata));

	म_नकल(अगरdata.अगरr_name, अगरname);

	sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
	अगर (sd < 0) अणु
		log_err_त्रुटि_सं("socket failed");
		वापस -1;
	पूर्ण

	rc = ioctl(sd, SIOCGIFINDEX, (अक्षर *)&अगरdata);
	बंद(sd);
	अगर (rc != 0) अणु
		log_err_त्रुटि_सं("ioctl(SIOCGIFINDEX) failed");
		वापस -1;
	पूर्ण

	वापस अगरdata.अगरr_अगरindex;
पूर्ण

अटल पूर्णांक bind_to_device(पूर्णांक sd, स्थिर अक्षर *name)
अणु
	पूर्णांक rc;

	rc = setsockopt(sd, SOL_SOCKET, SO_BINDTODEVICE, name, म_माप(name)+1);
	अगर (rc < 0)
		log_err_त्रुटि_सं("setsockopt(SO_BINDTODEVICE)");

	वापस rc;
पूर्ण

अटल पूर्णांक get_bind_to_device(पूर्णांक sd, अक्षर *name, माप_प्रकार len)
अणु
	पूर्णांक rc;
	socklen_t optlen = len;

	name[0] = '\0';
	rc = माला_लोockopt(sd, SOL_SOCKET, SO_BINDTODEVICE, name, &optlen);
	अगर (rc < 0)
		log_err_त्रुटि_सं("setsockopt(SO_BINDTODEVICE)");

	वापस rc;
पूर्ण

अटल पूर्णांक check_device(पूर्णांक sd, काष्ठा sock_args *args)
अणु
	पूर्णांक अगरindex = 0;
	अक्षर name[32];

	अगर (get_bind_to_device(sd, name, माप(name)))
		*name = '\0';
	अन्यथा
		अगरindex = get_अगरidx(name);

	log_msg("    bound to device %s/%d\n",
		*name ? name : "<none>", अगरindex);

	अगर (!args->expected_अगरindex)
		वापस 0;

	अगर (args->expected_अगरindex != अगरindex) अणु
		log_error("Device index mismatch: expected %d have %d\n",
			  args->expected_अगरindex, अगरindex);
		वापस 1;
	पूर्ण

	log_msg("Device index matches: expected %d have %d\n",
		args->expected_अगरindex, अगरindex);

	वापस 0;
पूर्ण

अटल पूर्णांक set_pktinfo_v4(पूर्णांक sd)
अणु
	पूर्णांक one = 1;
	पूर्णांक rc;

	rc = setsockopt(sd, SOL_IP, IP_PKTINFO, &one, माप(one));
	अगर (rc < 0 && rc != -ENOTSUP)
		log_err_त्रुटि_सं("setsockopt(IP_PKTINFO)");

	वापस rc;
पूर्ण

अटल पूर्णांक set_recvpktinfo_v6(पूर्णांक sd)
अणु
	पूर्णांक one = 1;
	पूर्णांक rc;

	rc = setsockopt(sd, SOL_IPV6, IPV6_RECVPKTINFO, &one, माप(one));
	अगर (rc < 0 && rc != -ENOTSUP)
		log_err_त्रुटि_सं("setsockopt(IPV6_RECVPKTINFO)");

	वापस rc;
पूर्ण

अटल पूर्णांक set_recverr_v4(पूर्णांक sd)
अणु
	पूर्णांक one = 1;
	पूर्णांक rc;

	rc = setsockopt(sd, SOL_IP, IP_RECVERR, &one, माप(one));
	अगर (rc < 0 && rc != -ENOTSUP)
		log_err_त्रुटि_सं("setsockopt(IP_RECVERR)");

	वापस rc;
पूर्ण

अटल पूर्णांक set_recverr_v6(पूर्णांक sd)
अणु
	पूर्णांक one = 1;
	पूर्णांक rc;

	rc = setsockopt(sd, SOL_IPV6, IPV6_RECVERR, &one, माप(one));
	अगर (rc < 0 && rc != -ENOTSUP)
		log_err_त्रुटि_सं("setsockopt(IPV6_RECVERR)");

	वापस rc;
पूर्ण

अटल पूर्णांक set_unicast_अगर(पूर्णांक sd, पूर्णांक अगरindex, पूर्णांक version)
अणु
	पूर्णांक opt = IP_UNICAST_IF;
	पूर्णांक level = SOL_IP;
	पूर्णांक rc;

	अगरindex = htonl(अगरindex);

	अगर (version == AF_INET6) अणु
		opt = IPV6_UNICAST_IF;
		level = SOL_IPV6;
	पूर्ण
	rc = setsockopt(sd, level, opt, &अगरindex, माप(अगरindex));
	अगर (rc < 0)
		log_err_त्रुटि_सं("setsockopt(IP_UNICAST_IF)");

	वापस rc;
पूर्ण

अटल पूर्णांक set_multicast_अगर(पूर्णांक sd, पूर्णांक अगरindex)
अणु
	काष्ठा ip_mreqn mreq = अणु .imr_अगरindex = अगरindex पूर्ण;
	पूर्णांक rc;

	rc = setsockopt(sd, SOL_IP, IP_MULTICAST_IF, &mreq, माप(mreq));
	अगर (rc < 0)
		log_err_त्रुटि_सं("setsockopt(IP_MULTICAST_IF)");

	वापस rc;
पूर्ण

अटल पूर्णांक set_membership(पूर्णांक sd, uपूर्णांक32_t grp, uपूर्णांक32_t addr, पूर्णांक अगरindex)
अणु
	uपूर्णांक32_t अगर_addr = addr;
	काष्ठा ip_mreqn mreq;
	पूर्णांक rc;

	अगर (addr == htonl(INADDR_ANY) && !अगरindex) अणु
		log_error("Either local address or device needs to be given for multicast membership\n");
		वापस -1;
	पूर्ण

	mreq.imr_multiaddr.s_addr = grp;
	mreq.imr_address.s_addr = अगर_addr;
	mreq.imr_अगरindex = अगरindex;

	rc = setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, माप(mreq));
	अगर (rc < 0) अणु
		log_err_त्रुटि_सं("setsockopt(IP_ADD_MEMBERSHIP)");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_broadcast(पूर्णांक sd)
अणु
	अचिन्हित पूर्णांक one = 1;
	पूर्णांक rc = 0;

	अगर (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &one, माप(one)) != 0) अणु
		log_err_त्रुटि_सं("setsockopt(SO_BROADCAST)");
		rc = -1;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक set_reuseport(पूर्णांक sd)
अणु
	अचिन्हित पूर्णांक one = 1;
	पूर्णांक rc = 0;

	अगर (setsockopt(sd, SOL_SOCKET, SO_REUSEPORT, &one, माप(one)) != 0) अणु
		log_err_त्रुटि_सं("setsockopt(SO_REUSEPORT)");
		rc = -1;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक set_reuseaddr(पूर्णांक sd)
अणु
	अचिन्हित पूर्णांक one = 1;
	पूर्णांक rc = 0;

	अगर (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &one, माप(one)) != 0) अणु
		log_err_त्रुटि_सं("setsockopt(SO_REUSEADDR)");
		rc = -1;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक str_to_uपूर्णांक(स्थिर अक्षर *str, पूर्णांक min, पूर्णांक max, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक number;
	अक्षर *end;

	त्रुटि_सं = 0;
	number = (अचिन्हित पूर्णांक) म_से_अदीर्घ(str, &end, 0);

	/* entire string should be consumed by conversion
	 * and value should be between min and max
	 */
	अगर (((*end == '\0') || (*end == '\n')) && (end != str) &&
	    (त्रुटि_सं != दुस्फल) && (min <= number) && (number <= max)) अणु
		*value = number;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक resolve_devices(काष्ठा sock_args *args)
अणु
	अगर (args->dev) अणु
		args->अगरindex = get_अगरidx(args->dev);
		अगर (args->अगरindex < 0) अणु
			log_error("Invalid device name\n");
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (args->expected_dev) अणु
		अचिन्हित पूर्णांक पंचांगp;

		अगर (str_to_uपूर्णांक(args->expected_dev, 0, पूर्णांक_उच्च, &पंचांगp) == 0) अणु
			args->expected_अगरindex = (पूर्णांक)पंचांगp;
		पूर्ण अन्यथा अणु
			args->expected_अगरindex = get_अगरidx(args->expected_dev);
			अगर (args->expected_अगरindex < 0) अणु
				ख_लिखो(मानक_त्रुटि, "Invalid expected device\n");
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक expected_addr_match(काष्ठा sockaddr *sa, व्योम *expected,
			       स्थिर अक्षर *desc)
अणु
	अक्षर addrstr[64];
	पूर्णांक rc = 0;

	अगर (sa->sa_family == AF_INET) अणु
		काष्ठा sockaddr_in *s = (काष्ठा sockaddr_in *) sa;
		काष्ठा in_addr *exp_in = (काष्ठा in_addr *) expected;

		अगर (s->sin_addr.s_addr != exp_in->s_addr) अणु
			log_error("%s address does not match expected %s\n",
				  desc,
				  inet_ntop(AF_INET, exp_in,
					    addrstr, माप(addrstr)));
			rc = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (sa->sa_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *s6 = (काष्ठा sockaddr_in6 *) sa;
		काष्ठा in6_addr *exp_in = (काष्ठा in6_addr *) expected;

		अगर (स_भेद(&s6->sin6_addr, exp_in, माप(*exp_in))) अणु
			log_error("%s address does not match expected %s\n",
				  desc,
				  inet_ntop(AF_INET6, exp_in,
					    addrstr, माप(addrstr)));
			rc = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		log_error("%s address does not match expected - unknown family\n",
			  desc);
		rc = 1;
	पूर्ण

	अगर (!rc)
		log_msg("%s address matches expected\n", desc);

	वापस rc;
पूर्ण

अटल पूर्णांक show_sockstat(पूर्णांक sd, काष्ठा sock_args *args)
अणु
	काष्ठा sockaddr_in6 local_addr, remote_addr;
	socklen_t alen = माप(local_addr);
	काष्ठा sockaddr *sa;
	स्थिर अक्षर *desc;
	पूर्णांक rc = 0;

	desc = server_mode ? "server local:" : "client local:";
	sa = (काष्ठा sockaddr *) &local_addr;
	अगर (माला_लोockname(sd, sa, &alen) == 0) अणु
		log_address(desc, sa);

		अगर (args->has_expected_laddr) अणु
			rc = expected_addr_match(sa, &args->expected_laddr,
						 "local");
		पूर्ण
	पूर्ण अन्यथा अणु
		log_err_त्रुटि_सं("getsockname failed");
	पूर्ण

	sa = (काष्ठा sockaddr *) &remote_addr;
	desc = server_mode ? "server peer:" : "client peer:";
	अगर (getpeername(sd, sa, &alen) == 0) अणु
		log_address(desc, sa);

		अगर (args->has_expected_raddr) अणु
			rc |= expected_addr_match(sa, &args->expected_raddr,
						 "remote");
		पूर्ण
	पूर्ण अन्यथा अणु
		log_err_त्रुटि_सं("getpeername failed");
	पूर्ण

	वापस rc;
पूर्ण

क्रमागत addr_type अणु
	ADDR_TYPE_LOCAL,
	ADDR_TYPE_REMOTE,
	ADDR_TYPE_MCAST,
	ADDR_TYPE_EXPECTED_LOCAL,
	ADDR_TYPE_EXPECTED_REMOTE,
	ADDR_TYPE_MD5_PREFIX,
पूर्ण;

अटल पूर्णांक convert_addr(काष्ठा sock_args *args, स्थिर अक्षर *_str,
			क्रमागत addr_type atype)
अणु
	पूर्णांक pfx_len_max = args->version == AF_INET6 ? 128 : 32;
	पूर्णांक family = args->version;
	अक्षर *str, *dev, *sep;
	काष्ठा in6_addr *in6;
	काष्ठा in_addr  *in;
	स्थिर अक्षर *desc;
	व्योम *addr;
	पूर्णांक rc = 0;

	str = strdup(_str);
	अगर (!str)
		वापस -ENOMEM;

	चयन (atype) अणु
	हाल ADDR_TYPE_LOCAL:
		desc = "local";
		addr = &args->local_addr;
		अवरोध;
	हाल ADDR_TYPE_REMOTE:
		desc = "remote";
		addr = &args->remote_addr;
		अवरोध;
	हाल ADDR_TYPE_MCAST:
		desc = "mcast grp";
		addr = &args->grp;
		अवरोध;
	हाल ADDR_TYPE_EXPECTED_LOCAL:
		desc = "expected local";
		addr = &args->expected_laddr;
		अवरोध;
	हाल ADDR_TYPE_EXPECTED_REMOTE:
		desc = "expected remote";
		addr = &args->expected_raddr;
		अवरोध;
	हाल ADDR_TYPE_MD5_PREFIX:
		desc = "md5 prefix";
		अगर (family == AF_INET) अणु
			args->md5_prefix.v4.sin_family = AF_INET;
			addr = &args->md5_prefix.v4.sin_addr;
		पूर्ण अन्यथा अगर (family == AF_INET6) अणु
			args->md5_prefix.v6.sin6_family = AF_INET6;
			addr = &args->md5_prefix.v6.sin6_addr;
		पूर्ण अन्यथा
			वापस 1;

		sep = म_अक्षर(str, '/');
		अगर (sep) अणु
			*sep = '\0';
			sep++;
			अगर (str_to_uपूर्णांक(sep, 1, pfx_len_max,
					&args->prefix_len) != 0) अणु
				ख_लिखो(मानक_त्रुटि, "Invalid port\n");
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			args->prefix_len = 0;
		पूर्ण
		अवरोध;
	शेष:
		log_error("unknown address type\n");
		निकास(1);
	पूर्ण

	चयन (family) अणु
	हाल AF_INET:
		in  = (काष्ठा in_addr *) addr;
		अगर (str) अणु
			अगर (inet_pton(AF_INET, str, in) == 0) अणु
				log_error("Invalid %s IP address\n", desc);
				rc = -1;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			in->s_addr = htonl(INADDR_ANY);
		पूर्ण
		अवरोध;

	हाल AF_INET6:
		dev = म_अक्षर(str, '%');
		अगर (dev) अणु
			*dev = '\0';
			dev++;
		पूर्ण

		in6 = (काष्ठा in6_addr *) addr;
		अगर (str) अणु
			अगर (inet_pton(AF_INET6, str, in6) == 0) अणु
				log_error("Invalid %s IPv6 address\n", desc);
				rc = -1;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			*in6 = in6addr_any;
		पूर्ण
		अगर (dev) अणु
			args->scope_id = get_अगरidx(dev);
			अगर (args->scope_id < 0) अणु
				log_error("Invalid scope on %s IPv6 address\n",
					  desc);
				rc = -1;
				जाओ out;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		log_error("Invalid address family\n");
	पूर्ण

out:
	मुक्त(str);
	वापस rc;
पूर्ण

अटल पूर्णांक validate_addresses(काष्ठा sock_args *args)
अणु
	अगर (args->local_addr_str &&
	    convert_addr(args, args->local_addr_str, ADDR_TYPE_LOCAL) < 0)
		वापस 1;

	अगर (args->remote_addr_str &&
	    convert_addr(args, args->remote_addr_str, ADDR_TYPE_REMOTE) < 0)
		वापस 1;

	अगर (args->md5_prefix_str &&
	    convert_addr(args, args->md5_prefix_str,
			 ADDR_TYPE_MD5_PREFIX) < 0)
		वापस 1;

	अगर (args->expected_laddr_str &&
	    convert_addr(args, args->expected_laddr_str,
			 ADDR_TYPE_EXPECTED_LOCAL))
		वापस 1;

	अगर (args->expected_raddr_str &&
	    convert_addr(args, args->expected_raddr_str,
			 ADDR_TYPE_EXPECTED_REMOTE))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक get_index_from_cmsg(काष्ठा msghdr *m)
अणु
	काष्ठा cmsghdr *cm;
	पूर्णांक अगरindex = 0;
	अक्षर buf[64];

	क्रम (cm = (काष्ठा cmsghdr *)CMSG_FIRSTHDR(m);
	     m->msg_controllen != 0 && cm;
	     cm = (काष्ठा cmsghdr *)CMSG_NXTHDR(m, cm)) अणु

		अगर (cm->cmsg_level == SOL_IP &&
		    cm->cmsg_type == IP_PKTINFO) अणु
			काष्ठा in_pktinfo *pi;

			pi = (काष्ठा in_pktinfo *)(CMSG_DATA(cm));
			inet_ntop(AF_INET, &pi->ipi_addr, buf, माप(buf));
			अगरindex = pi->ipi_अगरindex;
		पूर्ण अन्यथा अगर (cm->cmsg_level == SOL_IPV6 &&
			   cm->cmsg_type == IPV6_PKTINFO) अणु
			काष्ठा in6_pktinfo *pi6;

			pi6 = (काष्ठा in6_pktinfo *)(CMSG_DATA(cm));
			inet_ntop(AF_INET6, &pi6->ipi6_addr, buf, माप(buf));
			अगरindex = pi6->ipi6_अगरindex;
		पूर्ण
	पूर्ण

	अगर (अगरindex) अणु
		log_msg("    pktinfo: ifindex %d dest addr %s\n",
			अगरindex, buf);
	पूर्ण
	वापस अगरindex;
पूर्ण

अटल पूर्णांक send_msg_no_cmsg(पूर्णांक sd, व्योम *addr, socklen_t alen)
अणु
	पूर्णांक err;

again:
	err = sendto(sd, msg, msglen, 0, addr, alen);
	अगर (err < 0) अणु
		अगर (त्रुटि_सं == EACCES && try_broadcast) अणु
			try_broadcast = 0;
			अगर (!set_broadcast(sd))
				जाओ again;
			त्रुटि_सं = EACCES;
		पूर्ण

		log_err_त्रुटि_सं("sendto failed");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक send_msg_cmsg(पूर्णांक sd, व्योम *addr, socklen_t alen,
			 पूर्णांक अगरindex, पूर्णांक version)
अणु
	अचिन्हित अक्षर cmsgbuf[64];
	काष्ठा iovec iov[2];
	काष्ठा cmsghdr *cm;
	काष्ठा msghdr m;
	पूर्णांक err;

	iov[0].iov_base = msg;
	iov[0].iov_len = msglen;
	m.msg_iov = iov;
	m.msg_iovlen = 1;
	m.msg_name = (caddr_t)addr;
	m.msg_namelen = alen;

	स_रखो(cmsgbuf, 0, माप(cmsgbuf));
	cm = (काष्ठा cmsghdr *)cmsgbuf;
	m.msg_control = (caddr_t)cm;

	अगर (version == AF_INET) अणु
		काष्ठा in_pktinfo *pi;

		cm->cmsg_level = SOL_IP;
		cm->cmsg_type = IP_PKTINFO;
		cm->cmsg_len = CMSG_LEN(माप(काष्ठा in_pktinfo));
		pi = (काष्ठा in_pktinfo *)(CMSG_DATA(cm));
		pi->ipi_अगरindex = अगरindex;

		m.msg_controllen = cm->cmsg_len;

	पूर्ण अन्यथा अगर (version == AF_INET6) अणु
		काष्ठा in6_pktinfo *pi6;

		cm->cmsg_level = SOL_IPV6;
		cm->cmsg_type = IPV6_PKTINFO;
		cm->cmsg_len = CMSG_LEN(माप(काष्ठा in6_pktinfo));

		pi6 = (काष्ठा in6_pktinfo *)(CMSG_DATA(cm));
		pi6->ipi6_अगरindex = अगरindex;

		m.msg_controllen = cm->cmsg_len;
	पूर्ण

again:
	err = sendmsg(sd, &m, 0);
	अगर (err < 0) अणु
		अगर (त्रुटि_सं == EACCES && try_broadcast) अणु
			try_broadcast = 0;
			अगर (!set_broadcast(sd))
				जाओ again;
			त्रुटि_सं = EACCES;
		पूर्ण

		log_err_त्रुटि_सं("sendmsg failed");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक send_msg(पूर्णांक sd, व्योम *addr, socklen_t alen, काष्ठा sock_args *args)
अणु
	अगर (args->type == SOCK_STREAM) अणु
		अगर (ग_लिखो(sd, msg, msglen) < 0) अणु
			log_err_त्रुटि_सं("write failed sending msg to peer");
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (args->अगरindex && args->use_cmsg) अणु
		अगर (send_msg_cmsg(sd, addr, alen, args->अगरindex, args->version))
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (send_msg_no_cmsg(sd, addr, alen))
			वापस 1;
	पूर्ण

	log_msg("Sent message:\n");
	log_msg("    %.24s%s\n", msg, msglen > 24 ? " ..." : "");

	वापस 0;
पूर्ण

अटल पूर्णांक socket_पढ़ो_dgram(पूर्णांक sd, काष्ठा sock_args *args)
अणु
	अचिन्हित अक्षर addr[माप(काष्ठा sockaddr_in6)];
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *) addr;
	socklen_t alen = माप(addr);
	काष्ठा iovec iov[2];
	काष्ठा msghdr m = अणु
		.msg_name = (caddr_t)addr,
		.msg_namelen = alen,
		.msg_iov = iov,
		.msg_iovlen = 1,
	पूर्ण;
	अचिन्हित अक्षर cmsgbuf[256];
	काष्ठा cmsghdr *cm = (काष्ठा cmsghdr *)cmsgbuf;
	अक्षर buf[16*1024];
	पूर्णांक अगरindex;
	पूर्णांक len;

	iov[0].iov_base = (caddr_t)buf;
	iov[0].iov_len = माप(buf);

	स_रखो(cmsgbuf, 0, माप(cmsgbuf));
	m.msg_control = (caddr_t)cm;
	m.msg_controllen = माप(cmsgbuf);

	len = recvmsg(sd, &m, 0);
	अगर (len == 0) अणु
		log_msg("peer closed connection.\n");
		वापस 0;
	पूर्ण अन्यथा अगर (len < 0) अणु
		log_msg("failed to read message: %d: %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	buf[len] = '\0';

	log_address("Message from:", sa);
	log_msg("    %.24s%s\n", buf, len > 24 ? " ..." : "");

	अगरindex = get_index_from_cmsg(&m);
	अगर (args->expected_अगरindex) अणु
		अगर (args->expected_अगरindex != अगरindex) अणु
			log_error("Device index mismatch: expected %d have %d\n",
				  args->expected_अगरindex, अगरindex);
			वापस -1;
		पूर्ण
		log_msg("Device index matches: expected %d have %d\n",
			args->expected_अगरindex, अगरindex);
	पूर्ण

	अगर (!पूर्णांकeractive && server_mode) अणु
		अगर (sa->sa_family == AF_INET6) अणु
			काष्ठा sockaddr_in6 *s6 = (काष्ठा sockaddr_in6 *) sa;
			काष्ठा in6_addr *in6 = &s6->sin6_addr;

			अगर (IN6_IS_ADDR_V4MAPPED(in6)) अणु
				स्थिर uपूर्णांक32_t *pa = (uपूर्णांक32_t *) &in6->s6_addr;
				काष्ठा in_addr in4;
				काष्ठा sockaddr_in *sin;

				sin = (काष्ठा sockaddr_in *) addr;
				pa += 3;
				in4.s_addr = *pa;
				sin->sin_addr = in4;
				sin->sin_family = AF_INET;
				अगर (send_msg_cmsg(sd, addr, alen,
						  अगरindex, AF_INET) < 0)
					जाओ out_err;
			पूर्ण
		पूर्ण
again:
		iov[0].iov_len = len;

		अगर (args->version == AF_INET6) अणु
			काष्ठा sockaddr_in6 *s6 = (काष्ठा sockaddr_in6 *) sa;

			अगर (args->dev) अणु
				/* aव्योम PKTINFO conflicts with bindtodev */
				अगर (sendto(sd, buf, len, 0,
					   (व्योम *) addr, alen) < 0)
					जाओ out_err;
			पूर्ण अन्यथा अणु
				/* kernel is allowing scope_id to be set to VRF
				 * index क्रम LLA. क्रम sends to global address
				 * reset scope id
				 */
				s6->sin6_scope_id = अगरindex;
				अगर (sendmsg(sd, &m, 0) < 0)
					जाओ out_err;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक err;

			err = sendmsg(sd, &m, 0);
			अगर (err < 0) अणु
				अगर (त्रुटि_सं == EACCES && try_broadcast) अणु
					try_broadcast = 0;
					अगर (!set_broadcast(sd))
						जाओ again;
					त्रुटि_सं = EACCES;
				पूर्ण
				जाओ out_err;
			पूर्ण
		पूर्ण
		log_msg("Sent message:\n");
		log_msg("    %.24s%s\n", buf, len > 24 ? " ..." : "");
	पूर्ण

	वापस 1;
out_err:
	log_err_त्रुटि_सं("failed to send msg to peer");
	वापस -1;
पूर्ण

अटल पूर्णांक socket_पढ़ो_stream(पूर्णांक sd)
अणु
	अक्षर buf[1024];
	पूर्णांक len;

	len = पढ़ो(sd, buf, माप(buf)-1);
	अगर (len == 0) अणु
		log_msg("client closed connection.\n");
		वापस 0;
	पूर्ण अन्यथा अगर (len < 0) अणु
		log_msg("failed to read message\n");
		वापस -1;
	पूर्ण

	buf[len] = '\0';
	log_msg("Incoming message:\n");
	log_msg("    %.24s%s\n", buf, len > 24 ? " ..." : "");

	अगर (!पूर्णांकeractive && server_mode) अणु
		अगर (ग_लिखो(sd, buf, len) < 0) अणु
			log_err_त्रुटि_सं("failed to send buf");
			वापस -1;
		पूर्ण
		log_msg("Sent message:\n");
		log_msg("     %.24s%s\n", buf, len > 24 ? " ..." : "");
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक socket_पढ़ो(पूर्णांक sd, काष्ठा sock_args *args)
अणु
	अगर (args->type == SOCK_STREAM)
		वापस socket_पढ़ो_stream(sd);

	वापस socket_पढ़ो_dgram(sd, args);
पूर्ण

अटल पूर्णांक मानक_निवेश_to_socket(पूर्णांक sd, पूर्णांक type, व्योम *addr, socklen_t alen)
अणु
	अक्षर buf[1024];
	पूर्णांक len;

	अगर (ख_माला_लो(buf, माप(buf), मानक_निवेश) == शून्य)
		वापस 0;

	len = म_माप(buf);
	अगर (type == SOCK_STREAM) अणु
		अगर (ग_लिखो(sd, buf, len) < 0) अणु
			log_err_त्रुटि_सं("failed to send buf");
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक err;

again:
		err = sendto(sd, buf, len, 0, addr, alen);
		अगर (err < 0) अणु
			अगर (त्रुटि_सं == EACCES && try_broadcast) अणु
				try_broadcast = 0;
				अगर (!set_broadcast(sd))
					जाओ again;
				त्रुटि_सं = EACCES;
			पूर्ण
			log_err_त्रुटि_सं("failed to send msg to peer");
			वापस -1;
		पूर्ण
	पूर्ण
	log_msg("Sent message:\n");
	log_msg("    %.24s%s\n", buf, len > 24 ? " ..." : "");

	वापस 1;
पूर्ण

अटल व्योम set_recv_attr(पूर्णांक sd, पूर्णांक version)
अणु
	अगर (version == AF_INET6) अणु
		set_recvpktinfo_v6(sd);
		set_recverr_v6(sd);
	पूर्ण अन्यथा अणु
		set_pktinfo_v4(sd);
		set_recverr_v4(sd);
	पूर्ण
पूर्ण

अटल पूर्णांक msg_loop(पूर्णांक client, पूर्णांक sd, व्योम *addr, socklen_t alen,
		    काष्ठा sock_args *args)
अणु
	काष्ठा समयval समयout = अणु .tv_sec = prog_समयout पूर्ण, *ptval = शून्य;
	fd_set rfds;
	पूर्णांक nfds;
	पूर्णांक rc;

	अगर (args->type != SOCK_STREAM)
		set_recv_attr(sd, args->version);

	अगर (msg) अणु
		msglen = म_माप(msg);

		/* client sends first message */
		अगर (client) अणु
			अगर (send_msg(sd, addr, alen, args))
				वापस 1;
		पूर्ण
		अगर (!पूर्णांकeractive) अणु
			ptval = &समयout;
			अगर (!prog_समयout)
				समयout.tv_sec = 5;
		पूर्ण
	पूर्ण

	nfds = पूर्णांकeractive ? MAX(fileno(मानक_निवेश), sd)  + 1 : sd + 1;
	जबतक (1) अणु
		FD_ZERO(&rfds);
		FD_SET(sd, &rfds);
		अगर (पूर्णांकeractive)
			FD_SET(fileno(मानक_निवेश), &rfds);

		rc = select(nfds, &rfds, शून्य, शून्य, ptval);
		अगर (rc < 0) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;

			rc = 1;
			log_err_त्रुटि_सं("select failed");
			अवरोध;
		पूर्ण अन्यथा अगर (rc == 0) अणु
			log_error("Timed out waiting for response\n");
			rc = 2;
			अवरोध;
		पूर्ण

		अगर (FD_ISSET(sd, &rfds)) अणु
			rc = socket_पढ़ो(sd, args);
			अगर (rc < 0) अणु
				rc = 1;
				अवरोध;
			पूर्ण
			अगर (rc == 0)
				अवरोध;
		पूर्ण

		rc = 0;

		अगर (FD_ISSET(fileno(मानक_निवेश), &rfds)) अणु
			अगर (मानक_निवेश_to_socket(sd, args->type, addr, alen) <= 0)
				अवरोध;
		पूर्ण

		अगर (पूर्णांकeractive)
			जारी;

		अगर (iter != -1) अणु
			--iter;
			अगर (iter == 0)
				अवरोध;
		पूर्ण

		log_msg("Going into quiet mode\n");
		quiet = 1;

		अगर (client) अणु
			अगर (send_msg(sd, addr, alen, args)) अणु
				rc = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक msock_init(काष्ठा sock_args *args, पूर्णांक server)
अणु
	uपूर्णांक32_t अगर_addr = htonl(INADDR_ANY);
	काष्ठा sockaddr_in laddr = अणु
		.sin_family = AF_INET,
		.sin_port = htons(args->port),
	पूर्ण;
	पूर्णांक one = 1;
	पूर्णांक sd;

	अगर (!server && args->has_local_ip)
		अगर_addr = args->local_addr.in.s_addr;

	sd = socket(PF_INET, SOCK_DGRAM, 0);
	अगर (sd < 0) अणु
		log_err_त्रुटि_सं("socket");
		वापस -1;
	पूर्ण

	अगर (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,
		       (अक्षर *)&one, माप(one)) < 0) अणु
		log_err_त्रुटि_सं("Setting SO_REUSEADDR error");
		जाओ out_err;
	पूर्ण

	अगर (setsockopt(sd, SOL_SOCKET, SO_BROADCAST,
		       (अक्षर *)&one, माप(one)) < 0)
		log_err_त्रुटि_सं("Setting SO_BROADCAST error");

	अगर (args->dev && bind_to_device(sd, args->dev) != 0)
		जाओ out_err;
	अन्यथा अगर (args->use_setsockopt &&
		 set_multicast_अगर(sd, args->अगरindex))
		जाओ out_err;

	laddr.sin_addr.s_addr = अगर_addr;

	अगर (bind(sd, (काष्ठा sockaddr *) &laddr, माप(laddr)) < 0) अणु
		log_err_त्रुटि_सं("bind failed");
		जाओ out_err;
	पूर्ण

	अगर (server &&
	    set_membership(sd, args->grp.s_addr,
			   args->local_addr.in.s_addr, args->अगरindex))
		जाओ out_err;

	वापस sd;
out_err:
	बंद(sd);
	वापस -1;
पूर्ण

अटल पूर्णांक msock_server(काष्ठा sock_args *args)
अणु
	वापस msock_init(args, 1);
पूर्ण

अटल पूर्णांक msock_client(काष्ठा sock_args *args)
अणु
	वापस msock_init(args, 0);
पूर्ण

अटल पूर्णांक bind_socket(पूर्णांक sd, काष्ठा sock_args *args)
अणु
	काष्ठा sockaddr_in serv_addr = अणु
		.sin_family = AF_INET,
	पूर्ण;
	काष्ठा sockaddr_in6 serv6_addr = अणु
		.sin6_family = AF_INET6,
	पूर्ण;
	व्योम *addr;
	socklen_t alen;

	अगर (!args->has_local_ip && args->type == SOCK_RAW)
		वापस 0;

	चयन (args->version) अणु
	हाल AF_INET:
		serv_addr.sin_port = htons(args->port);
		serv_addr.sin_addr = args->local_addr.in;
		addr = &serv_addr;
		alen = माप(serv_addr);
		अवरोध;

	हाल AF_INET6:
		serv6_addr.sin6_port = htons(args->port);
		serv6_addr.sin6_addr = args->local_addr.in6;
		addr = &serv6_addr;
		alen = माप(serv6_addr);
		अवरोध;

	शेष:
		log_error("Invalid address family\n");
		वापस -1;
	पूर्ण

	अगर (bind(sd, addr, alen) < 0) अणु
		log_err_त्रुटि_सं("error binding socket");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lsock_init(काष्ठा sock_args *args)
अणु
	दीर्घ flags;
	पूर्णांक sd;

	sd = socket(args->version, args->type, args->protocol);
	अगर (sd < 0) अणु
		log_err_त्रुटि_सं("Error opening socket");
		वापस  -1;
	पूर्ण

	अगर (set_reuseaddr(sd) != 0)
		जाओ err;

	अगर (set_reuseport(sd) != 0)
		जाओ err;

	अगर (args->dev && bind_to_device(sd, args->dev) != 0)
		जाओ err;
	अन्यथा अगर (args->use_setsockopt &&
		 set_unicast_अगर(sd, args->अगरindex, args->version))
		जाओ err;

	अगर (bind_socket(sd, args))
		जाओ err;

	अगर (args->bind_test_only)
		जाओ out;

	अगर (args->type == SOCK_STREAM && listen(sd, 1) < 0) अणु
		log_err_त्रुटि_सं("listen failed");
		जाओ err;
	पूर्ण

	flags = fcntl(sd, F_GETFL);
	अगर ((flags < 0) || (fcntl(sd, F_SETFL, flags|O_NONBLOCK) < 0)) अणु
		log_err_त्रुटि_सं("Failed to set non-blocking option");
		जाओ err;
	पूर्ण

	अगर (fcntl(sd, F_SETFD, FD_CLOEXEC) < 0)
		log_err_त्रुटि_सं("Failed to set close-on-exec flag");

out:
	वापस sd;

err:
	बंद(sd);
	वापस -1;
पूर्ण

अटल व्योम ipc_ग_लिखो(पूर्णांक fd, पूर्णांक message)
अणु
	/* Not in both_mode, so there's no process to संकेत */
	अगर (fd < 0)
		वापस;

	अगर (ग_लिखो(fd, &message, माप(message)) < 0)
		log_err_त्रुटि_सं("Failed to send client status");
पूर्ण

अटल पूर्णांक करो_server(काष्ठा sock_args *args, पूर्णांक ipc_fd)
अणु
	/* ipc_fd = -1 अगर no parent process to संकेत */
	काष्ठा समयval समयout = अणु .tv_sec = prog_समयout पूर्ण, *ptval = शून्य;
	अचिन्हित अक्षर addr[माप(काष्ठा sockaddr_in6)] = अणुपूर्ण;
	socklen_t alen = माप(addr);
	पूर्णांक lsd, csd = -1;

	fd_set rfds;
	पूर्णांक rc;

	अगर (args->serverns) अणु
		अगर (चयन_ns(args->serverns)) अणु
			log_error("Could not set server netns to %s\n",
				  args->serverns);
			जाओ err_निकास;
		पूर्ण
		log_msg("Switched server netns\n");
	पूर्ण

	args->dev = args->server_dev;
	args->expected_dev = args->expected_server_dev;
	अगर (resolve_devices(args) || validate_addresses(args))
		जाओ err_निकास;

	अगर (prog_समयout)
		ptval = &समयout;

	अगर (args->has_grp)
		lsd = msock_server(args);
	अन्यथा
		lsd = lsock_init(args);

	अगर (lsd < 0)
		जाओ err_निकास;

	अगर (args->bind_test_only) अणु
		बंद(lsd);
		ipc_ग_लिखो(ipc_fd, 1);
		वापस 0;
	पूर्ण

	अगर (args->type != SOCK_STREAM) अणु
		ipc_ग_लिखो(ipc_fd, 1);
		rc = msg_loop(0, lsd, (व्योम *) addr, alen, args);
		बंद(lsd);
		वापस rc;
	पूर्ण

	अगर (args->password && tcp_md5_remote(lsd, args)) अणु
		बंद(lsd);
		जाओ err_निकास;
	पूर्ण

	ipc_ग_लिखो(ipc_fd, 1);
	जबतक (1) अणु
		log_msg("waiting for client connection.\n");
		FD_ZERO(&rfds);
		FD_SET(lsd, &rfds);

		rc = select(lsd+1, &rfds, शून्य, शून्य, ptval);
		अगर (rc == 0) अणु
			rc = 2;
			अवरोध;
		पूर्ण

		अगर (rc < 0) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;

			log_err_त्रुटि_सं("select failed");
			अवरोध;
		पूर्ण

		अगर (FD_ISSET(lsd, &rfds)) अणु

			csd = accept(lsd, (व्योम *) addr, &alen);
			अगर (csd < 0) अणु
				log_err_त्रुटि_सं("accept failed");
				अवरोध;
			पूर्ण

			rc = show_sockstat(csd, args);
			अगर (rc)
				अवरोध;

			rc = check_device(csd, args);
			अगर (rc)
				अवरोध;
		पूर्ण

		rc = msg_loop(0, csd, (व्योम *) addr, alen, args);
		बंद(csd);

		अगर (!पूर्णांकeractive)
			अवरोध;
	पूर्ण

	बंद(lsd);

	वापस rc;
err_निकास:
	ipc_ग_लिखो(ipc_fd, 0);
	वापस 1;
पूर्ण

अटल पूर्णांक रुको_क्रम_connect(पूर्णांक sd)
अणु
	काष्ठा समयval _tv = अणु .tv_sec = prog_समयout पूर्ण, *tv = शून्य;
	fd_set wfd;
	पूर्णांक val = 0, sz = माप(val);
	पूर्णांक rc;

	FD_ZERO(&wfd);
	FD_SET(sd, &wfd);

	अगर (prog_समयout)
		tv = &_tv;

	rc = select(FD_SETSIZE, शून्य, &wfd, शून्य, tv);
	अगर (rc == 0) अणु
		log_error("connect timed out\n");
		वापस -2;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		log_err_त्रुटि_सं("select failed");
		वापस -3;
	पूर्ण

	अगर (माला_लोockopt(sd, SOL_SOCKET, SO_ERROR, &val, (socklen_t *)&sz) < 0) अणु
		log_err_त्रुटि_सं("getsockopt(SO_ERROR) failed");
		वापस -4;
	पूर्ण

	अगर (val != 0) अणु
		log_error("connect failed: %d: %s\n", val, म_त्रुटि(val));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक connectsock(व्योम *addr, socklen_t alen, काष्ठा sock_args *args)
अणु
	पूर्णांक sd, rc = -1;
	दीर्घ flags;

	sd = socket(args->version, args->type, args->protocol);
	अगर (sd < 0) अणु
		log_err_त्रुटि_सं("Failed to create socket");
		वापस -1;
	पूर्ण

	flags = fcntl(sd, F_GETFL);
	अगर ((flags < 0) || (fcntl(sd, F_SETFL, flags|O_NONBLOCK) < 0)) अणु
		log_err_त्रुटि_सं("Failed to set non-blocking option");
		जाओ err;
	पूर्ण

	अगर (set_reuseport(sd) != 0)
		जाओ err;

	अगर (args->dev && bind_to_device(sd, args->dev) != 0)
		जाओ err;
	अन्यथा अगर (args->use_setsockopt &&
		 set_unicast_अगर(sd, args->अगरindex, args->version))
		जाओ err;

	अगर (args->has_local_ip && bind_socket(sd, args))
		जाओ err;

	अगर (args->type != SOCK_STREAM)
		जाओ out;

	अगर (args->password && tcp_md5sig(sd, addr, alen, args))
		जाओ err;

	अगर (args->bind_test_only)
		जाओ out;

	अगर (connect(sd, addr, alen) < 0) अणु
		अगर (त्रुटि_सं != EINPROGRESS) अणु
			log_err_त्रुटि_सं("Failed to connect to remote host");
			rc = -1;
			जाओ err;
		पूर्ण
		rc = रुको_क्रम_connect(sd);
		अगर (rc < 0)
			जाओ err;
	पूर्ण
out:
	वापस sd;

err:
	बंद(sd);
	वापस rc;
पूर्ण

अटल पूर्णांक करो_client(काष्ठा sock_args *args)
अणु
	काष्ठा sockaddr_in sin = अणु
		.sin_family = AF_INET,
	पूर्ण;
	काष्ठा sockaddr_in6 sin6 = अणु
		.sin6_family = AF_INET6,
	पूर्ण;
	व्योम *addr;
	पूर्णांक alen;
	पूर्णांक rc = 0;
	पूर्णांक sd;

	अगर (!args->has_remote_ip && !args->has_grp) अणु
		ख_लिखो(मानक_त्रुटि, "remote IP or multicast group not given\n");
		वापस 1;
	पूर्ण

	अगर (args->clientns) अणु
		अगर (चयन_ns(args->clientns)) अणु
			log_error("Could not set client netns to %s\n",
				  args->clientns);
			वापस 1;
		पूर्ण
		log_msg("Switched client netns\n");
	पूर्ण

	args->local_addr_str = args->client_local_addr_str;
	अगर (resolve_devices(args) || validate_addresses(args))
		वापस 1;

	अगर ((args->use_setsockopt || args->use_cmsg) && !args->अगरindex) अणु
		ख_लिखो(मानक_त्रुटि, "Device binding not specified\n");
		वापस 1;
	पूर्ण
	अगर (args->use_setsockopt || args->use_cmsg)
		args->dev = शून्य;

	चयन (args->version) अणु
	हाल AF_INET:
		sin.sin_port = htons(args->port);
		अगर (args->has_grp)
			sin.sin_addr = args->grp;
		अन्यथा
			sin.sin_addr = args->remote_addr.in;
		addr = &sin;
		alen = माप(sin);
		अवरोध;
	हाल AF_INET6:
		sin6.sin6_port = htons(args->port);
		sin6.sin6_addr = args->remote_addr.in6;
		sin6.sin6_scope_id = args->scope_id;
		addr = &sin6;
		alen = माप(sin6);
		अवरोध;
	पूर्ण

	args->password = args->client_pw;

	अगर (args->has_grp)
		sd = msock_client(args);
	अन्यथा
		sd = connectsock(addr, alen, args);

	अगर (sd < 0)
		वापस -sd;

	अगर (args->bind_test_only)
		जाओ out;

	अगर (args->type == SOCK_STREAM) अणु
		rc = show_sockstat(sd, args);
		अगर (rc != 0)
			जाओ out;
	पूर्ण

	rc = msg_loop(1, sd, addr, alen, args);

out:
	बंद(sd);

	वापस rc;
पूर्ण

अटल अक्षर *अक्रमom_msg(पूर्णांक len)
अणु
	पूर्णांक i, n = 0, olen = len + 1;
	अक्षर *m;

	अगर (len <= 0)
		वापस शून्य;

	m = दो_स्मृति(olen);
	अगर (!m)
		वापस शून्य;

	जबतक (len > 26) अणु
		i = snम_लिखो(m + n, olen - n, "%.26s",
			     "abcdefghijklmnopqrstuvwxyz");
		n += i;
		len -= i;
	पूर्ण
	i = snम_लिखो(m + n, olen - n, "%.*s", len,
		     "abcdefghijklmnopqrstuvwxyz");
	वापस m;
पूर्ण

अटल पूर्णांक ipc_child(पूर्णांक fd, काष्ठा sock_args *args)
अणु
	अक्षर *outbuf, *errbuf;
	पूर्णांक rc = 1;

	outbuf = दो_स्मृति(4096);
	errbuf = दो_स्मृति(4096);
	अगर (!outbuf || !errbuf) अणु
		ख_लिखो(मानक_त्रुटि, "server: Failed to allocate buffers for stdout and stderr\n");
		जाओ out;
	पूर्ण

	रखो_बफfer(मानक_निकास, outbuf, 4096);
	रखो_बफfer(मानक_त्रुटि, errbuf, 4096);

	server_mode = 1; /* to tell log_msg in हाल we are in both_mode */

	/* when running in both mode, address validation applies
	 * solely to client side
	 */
	args->has_expected_laddr = 0;
	args->has_expected_raddr = 0;

	rc = करो_server(args, fd);

out:
	मुक्त(outbuf);
	मुक्त(errbuf);

	वापस rc;
पूर्ण

अटल पूर्णांक ipc_parent(पूर्णांक cpid, पूर्णांक fd, काष्ठा sock_args *args)
अणु
	पूर्णांक client_status;
	पूर्णांक status;
	पूर्णांक buf;

	/* करो the client-side function here in the parent process,
	 * रुकोing to be told when to जारी
	 */
	अगर (पढ़ो(fd, &buf, माप(buf)) <= 0) अणु
		log_err_त्रुटि_सं("Failed to read IPC status from status");
		वापस 1;
	पूर्ण
	अगर (!buf) अणु
		log_error("Server failed; can not continue\n");
		वापस 1;
	पूर्ण
	log_msg("Server is ready\n");

	client_status = करो_client(args);
	log_msg("parent is done!\n");

	अगर (समाप्त(cpid, 0) == 0)
		समाप्त(cpid, SIGKILL);

	रुको(&status);
	वापस client_status;
पूर्ण

#घोषणा GETOPT_STR  "sr:l:c:p:t:g:P:DRn:M:X:m:d:I:BN:O:SCi6L:0:1:2:3:Fbq"

अटल व्योम prपूर्णांक_usage(अक्षर *prog)
अणु
	म_लिखो(
	"usage: %s OPTS\n"
	"Required:\n"
	"    -r addr       remote address to connect to (client mode only)\n"
	"    -p port       port to connect to (client mode)/listen on (server mode)\n"
	"                  (default: %d)\n"
	"    -s            server mode (default: client mode)\n"
	"    -t            timeout seconds (default: none)\n"
	"\n"
	"Optional:\n"
	"    -B            do both client and server via fork and IPC\n"
	"    -N ns         set client to network namespace ns (requires root)\n"
	"    -O ns         set server to network namespace ns (requires root)\n"
	"    -F            Restart server loop\n"
	"    -6            IPv6 (default is IPv4)\n"
	"    -P proto      protocol for socket: icmp, ospf (default: none)\n"
	"    -D|R          datagram (D) / raw (R) socket (default stream)\n"
	"    -l addr       local address to bind to in server mode\n"
	"    -c addr       local address to bind to in client mode\n"
	"\n"
	"    -d dev        bind socket to given device name\n"
	"    -I dev        bind socket to given device name - server mode\n"
	"    -S            use setsockopt (IP_UNICAST_IF or IP_MULTICAST_IF)\n"
	"                  to set device binding\n"
	"    -C            use cmsg and IP_PKTINFO to specify device binding\n"
	"\n"
	"    -L len        send random message of given length\n"
	"    -n num        number of times to send message\n"
	"\n"
	"    -M password   use MD5 sum protection\n"
	"    -X password   MD5 password for client mode\n"
	"    -m prefix/len prefix and length to use for MD5 key\n"
	"    -g grp        multicast group (e.g., 239.1.1.1)\n"
	"    -i            interactive mode (default is echo and terminate)\n"
	"\n"
	"    -0 addr       Expected local address\n"
	"    -1 addr       Expected remote address\n"
	"    -2 dev        Expected device name (or index) to receive packet\n"
	"    -3 dev        Expected device name (or index) to receive packets - server mode\n"
	"\n"
	"    -b            Bind test only.\n"
	"    -q            Be quiet. Run test without printing anything.\n"
	, prog, DEFAULT_PORT);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा sock_args args = अणु
		.version = AF_INET,
		.type    = SOCK_STREAM,
		.port    = DEFAULT_PORT,
	पूर्ण;
	काष्ठा protoent *pe;
	पूर्णांक both_mode = 0;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक क्रमever = 0;
	पूर्णांक fd[2];
	पूर्णांक cpid;

	/* process inमाला_दो */
	बाह्य अक्षर *optarg;
	पूर्णांक rc = 0;

	/*
	 * process input args
	 */

	जबतक ((rc = getopt(argc, argv, GETOPT_STR)) != -1) अणु
		चयन (rc) अणु
		हाल 'B':
			both_mode = 1;
			अवरोध;
		हाल 's':
			server_mode = 1;
			अवरोध;
		हाल 'F':
			क्रमever = 1;
			अवरोध;
		हाल 'l':
			args.has_local_ip = 1;
			args.local_addr_str = optarg;
			अवरोध;
		हाल 'r':
			args.has_remote_ip = 1;
			args.remote_addr_str = optarg;
			अवरोध;
		हाल 'c':
			args.has_local_ip = 1;
			args.client_local_addr_str = optarg;
			अवरोध;
		हाल 'p':
			अगर (str_to_uपूर्णांक(optarg, 1, 65535, &पंचांगp) != 0) अणु
				ख_लिखो(मानक_त्रुटि, "Invalid port\n");
				वापस 1;
			पूर्ण
			args.port = (अचिन्हित लघु) पंचांगp;
			अवरोध;
		हाल 't':
			अगर (str_to_uपूर्णांक(optarg, 0, पूर्णांक_उच्च,
					&prog_समयout) != 0) अणु
				ख_लिखो(मानक_त्रुटि, "Invalid timeout\n");
				वापस 1;
			पूर्ण
			अवरोध;
		हाल 'D':
			args.type = SOCK_DGRAM;
			अवरोध;
		हाल 'R':
			args.type = SOCK_RAW;
			args.port = 0;
			अगर (!args.protocol)
				args.protocol = IPPROTO_RAW;
			अवरोध;
		हाल 'P':
			pe = getprotobyname(optarg);
			अगर (pe) अणु
				args.protocol = pe->p_proto;
			पूर्ण अन्यथा अणु
				अगर (str_to_uपूर्णांक(optarg, 0, 0xffff, &पंचांगp) != 0) अणु
					ख_लिखो(मानक_त्रुटि, "Invalid protocol\n");
					वापस 1;
				पूर्ण
				args.protocol = पंचांगp;
			पूर्ण
			अवरोध;
		हाल 'n':
			iter = म_से_प(optarg);
			अवरोध;
		हाल 'N':
			args.clientns = optarg;
			अवरोध;
		हाल 'O':
			args.serverns = optarg;
			अवरोध;
		हाल 'L':
			msg = अक्रमom_msg(म_से_प(optarg));
			अवरोध;
		हाल 'M':
			args.password = optarg;
			अवरोध;
		हाल 'X':
			args.client_pw = optarg;
			अवरोध;
		हाल 'm':
			args.md5_prefix_str = optarg;
			अवरोध;
		हाल 'S':
			args.use_setsockopt = 1;
			अवरोध;
		हाल 'C':
			args.use_cmsg = 1;
			अवरोध;
		हाल 'd':
			args.dev = optarg;
			अवरोध;
		हाल 'I':
			args.server_dev = optarg;
			अवरोध;
		हाल 'i':
			पूर्णांकeractive = 1;
			अवरोध;
		हाल 'g':
			args.has_grp = 1;
			अगर (convert_addr(&args, optarg, ADDR_TYPE_MCAST) < 0)
				वापस 1;
			args.type = SOCK_DGRAM;
			अवरोध;
		हाल '6':
			args.version = AF_INET6;
			अवरोध;
		हाल 'b':
			args.bind_test_only = 1;
			अवरोध;
		हाल '0':
			args.has_expected_laddr = 1;
			args.expected_laddr_str = optarg;
			अवरोध;
		हाल '1':
			args.has_expected_raddr = 1;
			args.expected_raddr_str = optarg;
			अवरोध;
		हाल '2':
			args.expected_dev = optarg;
			अवरोध;
		हाल '3':
			args.expected_server_dev = optarg;
			अवरोध;
		हाल 'q':
			quiet = 1;
			अवरोध;
		शेष:
			prपूर्णांक_usage(argv[0]);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (args.password &&
	    ((!args.has_remote_ip && !args.md5_prefix_str) ||
	      args.type != SOCK_STREAM)) अणु
		log_error("MD5 passwords apply to TCP only and require a remote ip for the password\n");
		वापस 1;
	पूर्ण

	अगर (args.md5_prefix_str && !args.password) अणु
		log_error("Prefix range for MD5 protection specified without a password\n");
		वापस 1;
	पूर्ण

	अगर (iter == 0) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid number of messages to send\n");
		वापस 1;
	पूर्ण

	अगर (args.type == SOCK_STREAM && !args.protocol)
		args.protocol = IPPROTO_TCP;
	अगर (args.type == SOCK_DGRAM && !args.protocol)
		args.protocol = IPPROTO_UDP;

	अगर ((args.type == SOCK_STREAM || args.type == SOCK_DGRAM) &&
	     args.port == 0) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid port number\n");
		वापस 1;
	पूर्ण

	अगर ((both_mode || !server_mode) && !args.has_grp &&
	    !args.has_remote_ip && !args.has_local_ip) अणु
		ख_लिखो(मानक_त्रुटि,
			"Local (server mode) or remote IP (client IP) required\n");
		वापस 1;
	पूर्ण

	अगर (पूर्णांकeractive) अणु
		prog_समयout = 0;
		msg = शून्य;
	पूर्ण

	अगर (both_mode) अणु
		अगर (pipe(fd) < 0) अणु
			लिखो_त्रुटि("pipe");
			निकास(1);
		पूर्ण

		cpid = विभाजन();
		अगर (cpid < 0) अणु
			लिखो_त्रुटि("fork");
			निकास(1);
		पूर्ण
		अगर (cpid)
			वापस ipc_parent(cpid, fd[0], &args);

		वापस ipc_child(fd[1], &args);
	पूर्ण

	अगर (server_mode) अणु
		करो अणु
			rc = करो_server(&args, -1);
		पूर्ण जबतक (क्रमever);

		वापस rc;
	पूर्ण
	वापस करो_client(&args);
पूर्ण
