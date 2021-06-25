<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <net/अगर.h>
#समावेश <linux/अगर_tun.h>
#समावेश <arpa/inet.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <sys/socket.h>
#समावेश <sys/un.h>
#समावेश <netinet/ip.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <sys/रुको.h>
#समावेश <sys/uपन.स>
#समावेश <linux/virtio_net.h>
#समावेश <netdb.h>
#समावेश <मानककोष.स>
#समावेश <os.h>
#समावेश <सीमा.स>
#समावेश <um_दो_स्मृति.h>
#समावेश "vector_user.h"

#घोषणा ID_GRE 0
#घोषणा ID_L2TPV3 1
#घोषणा ID_BESS 2
#घोषणा ID_MAX 2

#घोषणा TOKEN_IFNAME "ifname"
#घोषणा TOKEN_SCRIPT "ifup"

#घोषणा TRANS_RAW "raw"
#घोषणा TRANS_RAW_LEN म_माप(TRANS_RAW)

#घोषणा TRANS_FD "fd"
#घोषणा TRANS_FD_LEN म_माप(TRANS_FD)

#घोषणा VNET_HDR_FAIL "could not enable vnet headers on fd %d"
#घोषणा TUN_GET_F_FAIL "tapraw: TUNGETFEATURES failed: %s"
#घोषणा L2TPV3_BIND_FAIL "l2tpv3_open : could not bind socket err=%i"
#घोषणा UNIX_BIND_FAIL "unix_open : could not bind socket err=%i"
#घोषणा BPF_ATTACH_FAIL "Failed to attach filter size %d prog %px to %d, err %d\n"
#घोषणा BPF_DETACH_FAIL "Failed to detach filter size %d prog %px to %d, err %d\n"

#घोषणा MAX_UN_LEN 107

अटल स्थिर अक्षर padअक्षर[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
अटल स्थिर अक्षर *ढाँचा = "tapXXXXXX";

/* This is very ugly and brute क्रमce lookup, but it is करोne
 * only once at initialization so not worth करोing hashes or
 * anything more पूर्णांकelligent
 */

अक्षर *uml_vector_fetch_arg(काष्ठा arglist *अगरspec, अक्षर *token)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < अगरspec->numargs; i++) अणु
		अगर (म_भेद(अगरspec->tokens[i], token) == 0)
			वापस अगरspec->values[i];
	पूर्ण
	वापस शून्य;

पूर्ण

काष्ठा arglist *uml_parse_vector_अगरspec(अक्षर *arg)
अणु
	काष्ठा arglist *result;
	पूर्णांक pos, len;
	bool parsing_token = true, next_starts = true;

	अगर (arg == शून्य)
		वापस शून्य;
	result = uml_kदो_स्मृति(माप(काष्ठा arglist), UM_GFP_KERNEL);
	अगर (result == शून्य)
		वापस शून्य;
	result->numargs = 0;
	len = म_माप(arg);
	क्रम (pos = 0; pos < len; pos++) अणु
		अगर (next_starts) अणु
			अगर (parsing_token) अणु
				result->tokens[result->numargs] = arg + pos;
			पूर्ण अन्यथा अणु
				result->values[result->numargs] = arg + pos;
				result->numargs++;
			पूर्ण
			next_starts = false;
		पूर्ण
		अगर (*(arg + pos) == '=') अणु
			अगर (parsing_token)
				parsing_token = false;
			अन्यथा
				जाओ cleanup;
			next_starts = true;
			(*(arg + pos)) = '\0';
		पूर्ण
		अगर (*(arg + pos) == ',') अणु
			parsing_token = true;
			next_starts = true;
			(*(arg + pos)) = '\0';
		पूर्ण
	पूर्ण
	वापस result;
cleanup:
	prपूर्णांकk(UM_KERN_ERR "vector_setup - Couldn't parse '%s'\n", arg);
	kमुक्त(result);
	वापस शून्य;
पूर्ण

/*
 * Socket/FD configuration functions. These वापस an काष्ठाure
 * of rx and tx descriptors to cover हालs where these are not
 * the same (f.e. पढ़ो via raw socket and ग_लिखो via tap).
 */

#घोषणा PATH_NET_TUN "/dev/net/tun"


अटल पूर्णांक create_tap_fd(अक्षर *अगरace)
अणु
	काष्ठा अगरreq अगरr;
	पूर्णांक fd = -1;
	पूर्णांक err = -ENOMEM, offload;

	fd = खोलो(PATH_NET_TUN, O_RDWR);
	अगर (fd < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "uml_tap: failed to open tun device\n");
		जाओ tap_fd_cleanup;
	पूर्ण
	स_रखो(&अगरr, 0, माप(अगरr));
	अगरr.अगरr_flags = IFF_TAP | IFF_NO_PI | IFF_VNET_HDR;
	म_नकलन((अक्षर *)&अगरr.अगरr_name, अगरace, माप(अगरr.अगरr_name) - 1);

	err = ioctl(fd, TUNSETIFF, (व्योम *) &अगरr);
	अगर (err != 0) अणु
		prपूर्णांकk(UM_KERN_ERR "uml_tap: failed to select tap interface\n");
		जाओ tap_fd_cleanup;
	पूर्ण

	offload = TUN_F_CSUM | TUN_F_TSO4 | TUN_F_TSO6;
	ioctl(fd, TUNSETOFFLOAD, offload);
	वापस fd;
tap_fd_cleanup:
	अगर (fd >= 0)
		os_बंद_file(fd);
	वापस err;
पूर्ण

अटल पूर्णांक create_raw_fd(अक्षर *अगरace, पूर्णांक flags, पूर्णांक proto)
अणु
	काष्ठा अगरreq अगरr;
	पूर्णांक fd = -1;
	काष्ठा sockaddr_ll sock;
	पूर्णांक err = -ENOMEM;

	fd = socket(AF_PACKET, SOCK_RAW, flags);
	अगर (fd == -1) अणु
		err = -त्रुटि_सं;
		जाओ raw_fd_cleanup;
	पूर्ण
	स_रखो(&अगरr, 0, माप(अगरr));
	म_नकलन((अक्षर *)&अगरr.अगरr_name, अगरace, माप(अगरr.अगरr_name) - 1);
	अगर (ioctl(fd, SIOCGIFINDEX, (व्योम *) &अगरr) < 0) अणु
		err = -त्रुटि_सं;
		जाओ raw_fd_cleanup;
	पूर्ण

	sock.sll_family = AF_PACKET;
	sock.sll_protocol = htons(proto);
	sock.sll_अगरindex = अगरr.अगरr_अगरindex;

	अगर (bind(fd,
		(काष्ठा sockaddr *) &sock, माप(काष्ठा sockaddr_ll)) < 0) अणु
		err = -त्रुटि_सं;
		जाओ raw_fd_cleanup;
	पूर्ण
	वापस fd;
raw_fd_cleanup:
	prपूर्णांकk(UM_KERN_ERR "user_init_raw: init failed, error %d", err);
	अगर (fd >= 0)
		os_बंद_file(fd);
	वापस err;
पूर्ण


अटल काष्ठा vector_fds *user_init_tap_fds(काष्ठा arglist *अगरspec)
अणु
	पूर्णांक fd = -1, i;
	अक्षर *अगरace;
	काष्ठा vector_fds *result = शून्य;
	bool dynamic = false;
	अक्षर dynamic_अगरname[IFNAMSIZ];
	अक्षर *argv[] = अणुशून्य, शून्य, शून्य, शून्यपूर्ण;

	अगरace = uml_vector_fetch_arg(अगरspec, TOKEN_IFNAME);
	अगर (अगरace == शून्य) अणु
		dynamic = true;
		अगरace = dynamic_अगरname;
		बेक्रम(getpid());
	पूर्ण

	result = uml_kदो_स्मृति(माप(काष्ठा vector_fds), UM_GFP_KERNEL);
	अगर (result == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "uml_tap: failed to allocate file descriptors\n");
		जाओ tap_cleanup;
	पूर्ण
	result->rx_fd = -1;
	result->tx_fd = -1;
	result->remote_addr = शून्य;
	result->remote_addr_size = 0;

	/* TAP */
	करो अणु
		अगर (dynamic) अणु
			म_नकल(अगरace, ढाँचा);
			क्रम (i = 0; i < म_माप(अगरace); i++) अणु
				अगर (अगरace[i] == 'X') अणु
					अगरace[i] = padअक्षर[अक्रम() % म_माप(padअक्षर)];
				पूर्ण
			पूर्ण
		पूर्ण
		fd = create_tap_fd(अगरace);
		अगर ((fd < 0) && (!dynamic)) अणु
			prपूर्णांकk(UM_KERN_ERR "uml_tap: failed to create tun interface\n");
			जाओ tap_cleanup;
		पूर्ण
		result->tx_fd = fd;
		result->rx_fd = fd;
	पूर्ण जबतक (fd < 0);

	argv[0] = uml_vector_fetch_arg(अगरspec, TOKEN_SCRIPT);
	अगर (argv[0]) अणु
		argv[1] = अगरace;
		run_helper(शून्य, शून्य, argv);
	पूर्ण

	वापस result;
tap_cleanup:
	prपूर्णांकk(UM_KERN_ERR "user_init_tap: init failed, error %d", fd);
	kमुक्त(result);
	वापस शून्य;
पूर्ण

अटल काष्ठा vector_fds *user_init_hybrid_fds(काष्ठा arglist *अगरspec)
अणु
	अक्षर *अगरace;
	काष्ठा vector_fds *result = शून्य;
	अक्षर *argv[] = अणुशून्य, शून्य, शून्य, शून्यपूर्ण;

	अगरace = uml_vector_fetch_arg(अगरspec, TOKEN_IFNAME);
	अगर (अगरace == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "uml_tap: failed to parse interface spec\n");
		जाओ hybrid_cleanup;
	पूर्ण

	result = uml_kदो_स्मृति(माप(काष्ठा vector_fds), UM_GFP_KERNEL);
	अगर (result == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "uml_tap: failed to allocate file descriptors\n");
		जाओ hybrid_cleanup;
	पूर्ण
	result->rx_fd = -1;
	result->tx_fd = -1;
	result->remote_addr = शून्य;
	result->remote_addr_size = 0;

	/* TAP */

	result->tx_fd = create_tap_fd(अगरace);
	अगर (result->tx_fd < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "uml_tap: failed to create tun interface: %i\n", result->tx_fd);
		जाओ hybrid_cleanup;
	पूर्ण

	/* RAW */

	result->rx_fd = create_raw_fd(अगरace, ETH_P_ALL, ETH_P_ALL);
	अगर (result->rx_fd == -1) अणु
		prपूर्णांकk(UM_KERN_ERR
			"uml_tap: failed to create paired raw socket: %i\n", result->rx_fd);
		जाओ hybrid_cleanup;
	पूर्ण

	argv[0] = uml_vector_fetch_arg(अगरspec, TOKEN_SCRIPT);
	अगर (argv[0]) अणु
		argv[1] = अगरace;
		run_helper(शून्य, शून्य, argv);
	पूर्ण
	वापस result;
hybrid_cleanup:
	prपूर्णांकk(UM_KERN_ERR "user_init_hybrid: init failed");
	kमुक्त(result);
	वापस शून्य;
पूर्ण

अटल काष्ठा vector_fds *user_init_unix_fds(काष्ठा arglist *अगरspec, पूर्णांक id)
अणु
	पूर्णांक fd = -1;
	पूर्णांक socktype;
	अक्षर *src, *dst;
	काष्ठा vector_fds *result = शून्य;
	काष्ठा sockaddr_un *local_addr = शून्य, *remote_addr = शून्य;

	src = uml_vector_fetch_arg(अगरspec, "src");
	dst = uml_vector_fetch_arg(अगरspec, "dst");
	result = uml_kदो_स्मृति(माप(काष्ठा vector_fds), UM_GFP_KERNEL);
	अगर (result == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "unix open:cannot allocate remote addr");
		जाओ unix_cleanup;
	पूर्ण
	remote_addr = uml_kदो_स्मृति(माप(काष्ठा sockaddr_un), UM_GFP_KERNEL);
	अगर (remote_addr == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "unix open:cannot allocate remote addr");
		जाओ unix_cleanup;
	पूर्ण

	चयन (id) अणु
	हाल ID_BESS:
		socktype = SOCK_SEQPACKET;
		अगर ((src != शून्य) && (म_माप(src) <= MAX_UN_LEN)) अणु
			local_addr = uml_kदो_स्मृति(माप(काष्ठा sockaddr_un), UM_GFP_KERNEL);
			अगर (local_addr == शून्य) अणु
				prपूर्णांकk(UM_KERN_ERR "bess open:cannot allocate local addr");
				जाओ unix_cleanup;
			पूर्ण
			local_addr->sun_family = AF_UNIX;
			स_नकल(local_addr->sun_path, src, म_माप(src) + 1);
		पूर्ण
		अगर ((dst == शून्य) || (म_माप(dst) > MAX_UN_LEN))
			जाओ unix_cleanup;
		remote_addr->sun_family = AF_UNIX;
		स_नकल(remote_addr->sun_path, dst, म_माप(dst) + 1);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Unsupported unix socket type\n");
		वापस शून्य;
	पूर्ण

	fd = socket(AF_UNIX, socktype, 0);
	अगर (fd == -1) अणु
		prपूर्णांकk(UM_KERN_ERR
			"unix open: could not open socket, error = %d",
			-त्रुटि_सं
		);
		जाओ unix_cleanup;
	पूर्ण
	अगर (local_addr != शून्य) अणु
		अगर (bind(fd, (काष्ठा sockaddr *) local_addr, माप(काष्ठा sockaddr_un))) अणु
			prपूर्णांकk(UM_KERN_ERR UNIX_BIND_FAIL, त्रुटि_सं);
			जाओ unix_cleanup;
		पूर्ण
	पूर्ण
	चयन (id) अणु
	हाल ID_BESS:
		अगर (connect(fd, (स्थिर काष्ठा sockaddr *) remote_addr, माप(काष्ठा sockaddr_un)) < 0) अणु
			prपूर्णांकk(UM_KERN_ERR "bess open:cannot connect to %s %i", remote_addr->sun_path, -त्रुटि_सं);
			जाओ unix_cleanup;
		पूर्ण
		अवरोध;
	पूर्ण
	result->rx_fd = fd;
	result->tx_fd = fd;
	result->remote_addr_size = माप(काष्ठा sockaddr_un);
	result->remote_addr = remote_addr;
	वापस result;
unix_cleanup:
	अगर (fd >= 0)
		os_बंद_file(fd);
	kमुक्त(remote_addr);
	kमुक्त(result);
	वापस शून्य;
पूर्ण

अटल पूर्णांक strtofd(स्थिर अक्षर *nptr)
अणु
	दीर्घ fd;
	अक्षर *endptr;

	अगर (nptr == शून्य)
		वापस -1;

	त्रुटि_सं = 0;
	fd = म_से_दीर्घ(nptr, &endptr, 10);
	अगर (nptr == endptr ||
		त्रुटि_सं != 0 ||
		*endptr != '\0' ||
		fd < 0 ||
		fd > पूर्णांक_उच्च) अणु
		वापस -1;
	पूर्ण
	वापस fd;
पूर्ण

अटल काष्ठा vector_fds *user_init_fd_fds(काष्ठा arglist *अगरspec)
अणु
	पूर्णांक fd = -1;
	अक्षर *fdarg = शून्य;
	काष्ठा vector_fds *result = शून्य;

	fdarg = uml_vector_fetch_arg(अगरspec, "fd");
	fd = strtofd(fdarg);
	अगर (fd == -1) अणु
		prपूर्णांकk(UM_KERN_ERR "fd open: bad or missing fd argument");
		जाओ fd_cleanup;
	पूर्ण

	result = uml_kदो_स्मृति(माप(काष्ठा vector_fds), UM_GFP_KERNEL);
	अगर (result == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "fd open: allocation failed");
		जाओ fd_cleanup;
	पूर्ण

	result->rx_fd = fd;
	result->tx_fd = fd;
	result->remote_addr_size = 0;
	result->remote_addr = शून्य;
	वापस result;

fd_cleanup:
	अगर (fd >= 0)
		os_बंद_file(fd);
	kमुक्त(result);
	वापस शून्य;
पूर्ण

अटल काष्ठा vector_fds *user_init_raw_fds(काष्ठा arglist *अगरspec)
अणु
	पूर्णांक rxfd = -1, txfd = -1;
	पूर्णांक err = -ENOMEM;
	अक्षर *अगरace;
	काष्ठा vector_fds *result = शून्य;
	अक्षर *argv[] = अणुशून्य, शून्य, शून्य, शून्यपूर्ण;

	अगरace = uml_vector_fetch_arg(अगरspec, TOKEN_IFNAME);
	अगर (अगरace == शून्य)
		जाओ raw_cleanup;

	rxfd = create_raw_fd(अगरace, ETH_P_ALL, ETH_P_ALL);
	अगर (rxfd == -1) अणु
		err = -त्रुटि_सं;
		जाओ raw_cleanup;
	पूर्ण
	txfd = create_raw_fd(अगरace, 0, ETH_P_IP); /* Turn off RX on this fd */
	अगर (txfd == -1) अणु
		err = -त्रुटि_सं;
		जाओ raw_cleanup;
	पूर्ण
	result = uml_kदो_स्मृति(माप(काष्ठा vector_fds), UM_GFP_KERNEL);
	अगर (result != शून्य) अणु
		result->rx_fd = rxfd;
		result->tx_fd = txfd;
		result->remote_addr = शून्य;
		result->remote_addr_size = 0;
	पूर्ण
	argv[0] = uml_vector_fetch_arg(अगरspec, TOKEN_SCRIPT);
	अगर (argv[0]) अणु
		argv[1] = अगरace;
		run_helper(शून्य, शून्य, argv);
	पूर्ण
	वापस result;
raw_cleanup:
	prपूर्णांकk(UM_KERN_ERR "user_init_raw: init failed, error %d", err);
	kमुक्त(result);
	वापस शून्य;
पूर्ण


bool uml_raw_enable_qdisc_bypass(पूर्णांक fd)
अणु
	पूर्णांक optval = 1;

	अगर (setsockopt(fd,
		SOL_PACKET, PACKET_QDISC_BYPASS,
		&optval, माप(optval)) != 0) अणु
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

bool uml_raw_enable_vnet_headers(पूर्णांक fd)
अणु
	पूर्णांक optval = 1;

	अगर (setsockopt(fd,
		SOL_PACKET, PACKET_VNET_HDR,
		&optval, माप(optval)) != 0) अणु
		prपूर्णांकk(UM_KERN_INFO VNET_HDR_FAIL, fd);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
bool uml_tap_enable_vnet_headers(पूर्णांक fd)
अणु
	अचिन्हित पूर्णांक features;
	पूर्णांक len = माप(काष्ठा virtio_net_hdr);

	अगर (ioctl(fd, TUNGETFEATURES, &features) == -1) अणु
		prपूर्णांकk(UM_KERN_INFO TUN_GET_F_FAIL, म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	अगर ((features & IFF_VNET_HDR) == 0) अणु
		prपूर्णांकk(UM_KERN_INFO "tapraw: No VNET HEADER support");
		वापस false;
	पूर्ण
	ioctl(fd, TUNSETVNETHDRSZ, &len);
	वापस true;
पूर्ण

अटल काष्ठा vector_fds *user_init_socket_fds(काष्ठा arglist *अगरspec, पूर्णांक id)
अणु
	पूर्णांक err = -ENOMEM;
	पूर्णांक fd = -1, gairet;
	काष्ठा addrinfo srchपूर्णांकs;
	काष्ठा addrinfo dsthपूर्णांकs;
	bool v6, udp;
	अक्षर *value;
	अक्षर *src, *dst, *srcport, *dstport;
	काष्ठा addrinfo *gairesult = शून्य;
	काष्ठा vector_fds *result = शून्य;


	value = uml_vector_fetch_arg(अगरspec, "v6");
	v6 = false;
	udp = false;
	अगर (value != शून्य) अणु
		अगर (म_से_दीर्घ((स्थिर अक्षर *) value, शून्य, 10) > 0)
			v6 = true;
	पूर्ण

	value = uml_vector_fetch_arg(अगरspec, "udp");
	अगर (value != शून्य) अणु
		अगर (म_से_दीर्घ((स्थिर अक्षर *) value, शून्य, 10) > 0)
			udp = true;
	पूर्ण
	src = uml_vector_fetch_arg(अगरspec, "src");
	dst = uml_vector_fetch_arg(अगरspec, "dst");
	srcport = uml_vector_fetch_arg(अगरspec, "srcport");
	dstport = uml_vector_fetch_arg(अगरspec, "dstport");

	स_रखो(&dsthपूर्णांकs, 0, माप(dsthपूर्णांकs));

	अगर (v6)
		dsthपूर्णांकs.ai_family = AF_INET6;
	अन्यथा
		dsthपूर्णांकs.ai_family = AF_INET;

	चयन (id) अणु
	हाल ID_GRE:
		dsthपूर्णांकs.ai_socktype = SOCK_RAW;
		dsthपूर्णांकs.ai_protocol = IPPROTO_GRE;
		अवरोध;
	हाल ID_L2TPV3:
		अगर (udp) अणु
			dsthपूर्णांकs.ai_socktype = SOCK_DGRAM;
			dsthपूर्णांकs.ai_protocol = 0;
		पूर्ण अन्यथा अणु
			dsthपूर्णांकs.ai_socktype = SOCK_RAW;
			dsthपूर्णांकs.ai_protocol = IPPROTO_L2TP;
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Unsupported socket type\n");
		वापस शून्य;
	पूर्ण
	स_नकल(&srchपूर्णांकs, &dsthपूर्णांकs, माप(काष्ठा addrinfo));

	gairet = getaddrinfo(src, srcport, &dsthपूर्णांकs, &gairesult);
	अगर ((gairet != 0) || (gairesult == शून्य)) अणु
		prपूर्णांकk(UM_KERN_ERR
			"socket_open : could not resolve src, error = %s",
			gai_म_त्रुटि(gairet)
		);
		वापस शून्य;
	पूर्ण
	fd = socket(gairesult->ai_family,
		gairesult->ai_socktype, gairesult->ai_protocol);
	अगर (fd == -1) अणु
		prपूर्णांकk(UM_KERN_ERR
			"socket_open : could not open socket, error = %d",
			-त्रुटि_सं
		);
		जाओ cleanup;
	पूर्ण
	अगर (bind(fd,
		(काष्ठा sockaddr *) gairesult->ai_addr,
		gairesult->ai_addrlen)) अणु
		prपूर्णांकk(UM_KERN_ERR L2TPV3_BIND_FAIL, त्रुटि_सं);
		जाओ cleanup;
	पूर्ण

	अगर (gairesult != शून्य)
		मुक्तaddrinfo(gairesult);

	gairesult = शून्य;

	gairet = getaddrinfo(dst, dstport, &dsthपूर्णांकs, &gairesult);
	अगर ((gairet != 0) || (gairesult == शून्य)) अणु
		prपूर्णांकk(UM_KERN_ERR
			"socket_open : could not resolve dst, error = %s",
			gai_म_त्रुटि(gairet)
		);
		वापस शून्य;
	पूर्ण

	result = uml_kदो_स्मृति(माप(काष्ठा vector_fds), UM_GFP_KERNEL);
	अगर (result != शून्य) अणु
		result->rx_fd = fd;
		result->tx_fd = fd;
		result->remote_addr = uml_kदो_स्मृति(
			gairesult->ai_addrlen, UM_GFP_KERNEL);
		अगर (result->remote_addr == शून्य)
			जाओ cleanup;
		result->remote_addr_size = gairesult->ai_addrlen;
		स_नकल(
			result->remote_addr,
			gairesult->ai_addr,
			gairesult->ai_addrlen
		);
	पूर्ण
	मुक्तaddrinfo(gairesult);
	वापस result;
cleanup:
	अगर (gairesult != शून्य)
		मुक्तaddrinfo(gairesult);
	prपूर्णांकk(UM_KERN_ERR "user_init_socket: init failed, error %d", err);
	अगर (fd >= 0)
		os_बंद_file(fd);
	अगर (result != शून्य) अणु
		kमुक्त(result->remote_addr);
		kमुक्त(result);
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा vector_fds *uml_vector_user_खोलो(
	पूर्णांक unit,
	काष्ठा arglist *parsed
)
अणु
	अक्षर *transport;

	अगर (parsed == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "no parsed config for unit %d\n", unit);
		वापस शून्य;
	पूर्ण
	transport = uml_vector_fetch_arg(parsed, "transport");
	अगर (transport == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "missing transport for unit %d\n", unit);
		वापस शून्य;
	पूर्ण
	अगर (म_भेदन(transport, TRANS_RAW, TRANS_RAW_LEN) == 0)
		वापस user_init_raw_fds(parsed);
	अगर (म_भेदन(transport, TRANS_HYBRID, TRANS_HYBRID_LEN) == 0)
		वापस user_init_hybrid_fds(parsed);
	अगर (म_भेदन(transport, TRANS_TAP, TRANS_TAP_LEN) == 0)
		वापस user_init_tap_fds(parsed);
	अगर (म_भेदन(transport, TRANS_GRE, TRANS_GRE_LEN) == 0)
		वापस user_init_socket_fds(parsed, ID_GRE);
	अगर (म_भेदन(transport, TRANS_L2TPV3, TRANS_L2TPV3_LEN) == 0)
		वापस user_init_socket_fds(parsed, ID_L2TPV3);
	अगर (म_भेदन(transport, TRANS_BESS, TRANS_BESS_LEN) == 0)
		वापस user_init_unix_fds(parsed, ID_BESS);
	अगर (म_भेदन(transport, TRANS_FD, TRANS_FD_LEN) == 0)
		वापस user_init_fd_fds(parsed);
	वापस शून्य;
पूर्ण


पूर्णांक uml_vector_sendmsg(पूर्णांक fd, व्योम *hdr, पूर्णांक flags)
अणु
	पूर्णांक n;

	CATCH_EINTR(n = sendmsg(fd, (काष्ठा msghdr *) hdr,  flags));
	अगर ((n < 0) && (त्रुटि_सं == EAGAIN))
		वापस 0;
	अगर (n >= 0)
		वापस n;
	अन्यथा
		वापस -त्रुटि_सं;
पूर्ण

पूर्णांक uml_vector_recvmsg(पूर्णांक fd, व्योम *hdr, पूर्णांक flags)
अणु
	पूर्णांक n;
	काष्ठा msghdr *msg = (काष्ठा msghdr *) hdr;

	CATCH_EINTR(n = पढ़ोv(fd, msg->msg_iov, msg->msg_iovlen));
	अगर ((n < 0) && (त्रुटि_सं == EAGAIN))
		वापस 0;
	अगर (n >= 0)
		वापस n;
	अन्यथा
		वापस -त्रुटि_सं;
पूर्ण

पूर्णांक uml_vector_ग_लिखोv(पूर्णांक fd, व्योम *hdr, पूर्णांक iovcount)
अणु
	पूर्णांक n;

	CATCH_EINTR(n = ग_लिखोv(fd, (काष्ठा iovec *) hdr,  iovcount));
	अगर ((n < 0) && ((त्रुटि_सं == EAGAIN) || (त्रुटि_सं == ENOBUFS)))
		वापस 0;
	अगर (n >= 0)
		वापस n;
	अन्यथा
		वापस -त्रुटि_सं;
पूर्ण

पूर्णांक uml_vector_sendmmsg(
	पूर्णांक fd,
	व्योम *msgvec,
	अचिन्हित पूर्णांक vlen,
	अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक n;

	CATCH_EINTR(n = sendmmsg(fd, (काष्ठा mmsghdr *) msgvec, vlen, flags));
	अगर ((n < 0) && ((त्रुटि_सं == EAGAIN) || (त्रुटि_सं == ENOBUFS)))
		वापस 0;
	अगर (n >= 0)
		वापस n;
	अन्यथा
		वापस -त्रुटि_सं;
पूर्ण

पूर्णांक uml_vector_recvmmsg(
	पूर्णांक fd,
	व्योम *msgvec,
	अचिन्हित पूर्णांक vlen,
	अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक n;

	CATCH_EINTR(
		n = recvmmsg(fd, (काष्ठा mmsghdr *) msgvec, vlen, flags, 0));
	अगर ((n < 0) && (त्रुटि_सं == EAGAIN))
		वापस 0;
	अगर (n >= 0)
		वापस n;
	अन्यथा
		वापस -त्रुटि_सं;
पूर्ण
पूर्णांक uml_vector_attach_bpf(पूर्णांक fd, व्योम *bpf)
अणु
	काष्ठा sock_fprog *prog = bpf;

	पूर्णांक err = setsockopt(fd, SOL_SOCKET, SO_ATTACH_FILTER, bpf, माप(काष्ठा sock_fprog));

	अगर (err < 0)
		prपूर्णांकk(KERN_ERR BPF_ATTACH_FAIL, prog->len, prog->filter, fd, -त्रुटि_सं);
	वापस err;
पूर्ण

पूर्णांक uml_vector_detach_bpf(पूर्णांक fd, व्योम *bpf)
अणु
	काष्ठा sock_fprog *prog = bpf;

	पूर्णांक err = setsockopt(fd, SOL_SOCKET, SO_DETACH_FILTER, bpf, माप(काष्ठा sock_fprog));
	अगर (err < 0)
		prपूर्णांकk(KERN_ERR BPF_DETACH_FAIL, prog->len, prog->filter, fd, -त्रुटि_सं);
	वापस err;
पूर्ण
व्योम *uml_vector_शेष_bpf(व्योम *mac)
अणु
	काष्ठा sock_filter *bpf;
	uपूर्णांक32_t *mac1 = (uपूर्णांक32_t *)(mac + 2);
	uपूर्णांक16_t *mac2 = (uपूर्णांक16_t *) mac;
	काष्ठा sock_fprog *bpf_prog;

	bpf_prog = uml_kदो_स्मृति(माप(काष्ठा sock_fprog), UM_GFP_KERNEL);
	अगर (bpf_prog) अणु
		bpf_prog->len = DEFAULT_BPF_LEN;
		bpf_prog->filter = शून्य;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण
	bpf = uml_kदो_स्मृति(
		माप(काष्ठा sock_filter) * DEFAULT_BPF_LEN, UM_GFP_KERNEL);
	अगर (bpf) अणु
		bpf_prog->filter = bpf;
		/* ld	[8] */
		bpf[0] = (काष्ठा sock_filter)अणु 0x20, 0, 0, 0x00000008 पूर्ण;
		/* jeq	#0xMAC[2-6] jt 2 jf 5*/
		bpf[1] = (काष्ठा sock_filter)अणु 0x15, 0, 3, ntohl(*mac1)पूर्ण;
		/* ldh	[6] */
		bpf[2] = (काष्ठा sock_filter)अणु 0x28, 0, 0, 0x00000006 पूर्ण;
		/* jeq	#0xMAC[0-1] jt 4 jf 5 */
		bpf[3] = (काष्ठा sock_filter)अणु 0x15, 0, 1, ntohs(*mac2)पूर्ण;
		/* ret	#0 */
		bpf[4] = (काष्ठा sock_filter)अणु 0x6, 0, 0, 0x00000000 पूर्ण;
		/* ret	#0x40000 */
		bpf[5] = (काष्ठा sock_filter)अणु 0x6, 0, 0, 0x00040000 पूर्ण;
	पूर्ण अन्यथा अणु
		kमुक्त(bpf_prog);
		bpf_prog = शून्य;
	पूर्ण
	वापस bpf_prog;
पूर्ण

/* Note - this function requires a valid mac being passed as an arg */

व्योम *uml_vector_user_bpf(अक्षर *filename)
अणु
	काष्ठा sock_filter *bpf;
	काष्ठा sock_fprog *bpf_prog;
	काष्ठा stat statbuf;
	पूर्णांक res, ffd = -1;

	अगर (filename == शून्य)
		वापस शून्य;

	अगर (stat(filename, &statbuf) < 0) अणु
		prपूर्णांकk(KERN_ERR "Error %d reading bpf file", -त्रुटि_सं);
		वापस false;
	पूर्ण
	bpf_prog = uml_kदो_स्मृति(माप(काष्ठा sock_fprog), UM_GFP_KERNEL);
	अगर (bpf_prog == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Failed to allocate bpf prog buffer");
		वापस शून्य;
	पूर्ण
	bpf_prog->len = statbuf.st_size / माप(काष्ठा sock_filter);
	bpf_prog->filter = शून्य;
	ffd = os_खोलो_file(filename, of_पढ़ो(OPENFLAGS()), 0);
	अगर (ffd < 0) अणु
		prपूर्णांकk(KERN_ERR "Error %d opening bpf file", -त्रुटि_सं);
		जाओ bpf_failed;
	पूर्ण
	bpf = uml_kदो_स्मृति(statbuf.st_size, UM_GFP_KERNEL);
	अगर (bpf == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Failed to allocate bpf buffer");
		जाओ bpf_failed;
	पूर्ण
	bpf_prog->filter = bpf;
	res = os_पढ़ो_file(ffd, bpf, statbuf.st_size);
	अगर (res < statbuf.st_size) अणु
		prपूर्णांकk(KERN_ERR "Failed to read bpf program %s, error %d", filename, res);
		kमुक्त(bpf);
		जाओ bpf_failed;
	पूर्ण
	os_बंद_file(ffd);
	वापस bpf_prog;
bpf_failed:
	अगर (ffd > 0)
		os_बंद_file(ffd);
	kमुक्त(bpf_prog);
	वापस शून्य;
पूर्ण
