<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ipsec.c - Check xfrm on veth inside a net-ns.
 * Copyright (c) 2018 Dmitry Safonov
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <यंत्र/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/netlink.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/veth.h>
#समावेश <linux/xfrm.h>
#समावेश <netinet/in.h>
#समावेश <net/अगर.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश "../kselftest.h"

#घोषणा prपूर्णांकk(fmt, ...)						\
	ksft_prपूर्णांक_msg("%d[%u] " fmt "\n", getpid(), __LINE__, ##__VA_ARGS__)

#घोषणा pr_err(fmt, ...)	prपूर्णांकk(fmt ": %m", ##__VA_ARGS__)

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))
#घोषणा BUILD_BUG_ON(condition) ((व्योम)माप(अक्षर[1 - 2*!!(condition)]))

#घोषणा IPV4_STR_SZ	16	/* xxx.xxx.xxx.xxx is दीर्घest + \0 */
#घोषणा MAX_PAYLOAD	2048
#घोषणा XFRM_ALGO_KEY_BUF_SIZE	512
#घोषणा MAX_PROCESSES	(1 << 14) /* /16 mask भागided by /30 subnets */
#घोषणा INADDR_A	((in_addr_t) 0x0a000000) /* 10.0.0.0 */
#घोषणा INADDR_B	((in_addr_t) 0xc0a80000) /* 192.168.0.0 */

/* /30 mask क्रम one veth connection */
#घोषणा PREFIX_LEN	30
#घोषणा child_ip(nr)	(4*nr + 1)
#घोषणा grchild_ip(nr)	(4*nr + 2)

#घोषणा VETH_FMT	"ktst-%d"
#घोषणा VETH_LEN	12

अटल पूर्णांक nsfd_parent	= -1;
अटल पूर्णांक nsfd_childa	= -1;
अटल पूर्णांक nsfd_childb	= -1;
अटल दीर्घ page_size;

/*
 * ksft_cnt is अटल in kselftest, so isn't shared with children.
 * We have to send a test result back to parent and count there.
 * results_fd is a pipe with test feedback from children.
 */
अटल पूर्णांक results_fd[2];

स्थिर अचिन्हित पूर्णांक ping_delay_nsec	= 50 * 1000 * 1000;
स्थिर अचिन्हित पूर्णांक ping_समयout		= 300;
स्थिर अचिन्हित पूर्णांक ping_count		= 100;
स्थिर अचिन्हित पूर्णांक ping_success		= 80;

अटल व्योम अक्रमomize_buffer(व्योम *buf, माप_प्रकार buflen)
अणु
	पूर्णांक *p = (पूर्णांक *)buf;
	माप_प्रकार words = buflen / माप(पूर्णांक);
	माप_प्रकार leftover = buflen % माप(पूर्णांक);

	अगर (!buflen)
		वापस;

	जबतक (words--)
		*p++ = अक्रम();

	अगर (leftover) अणु
		पूर्णांक पंचांगp = अक्रम();

		स_नकल(buf + buflen - leftover, &पंचांगp, leftover);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक unshare_खोलो(व्योम)
अणु
	स्थिर अक्षर *netns_path = "/proc/self/ns/net";
	पूर्णांक fd;

	अगर (unshare(CLONE_NEWNET) != 0) अणु
		pr_err("unshare()");
		वापस -1;
	पूर्ण

	fd = खोलो(netns_path, O_RDONLY);
	अगर (fd <= 0) अणु
		pr_err("open(%s)", netns_path);
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

अटल पूर्णांक चयन_ns(पूर्णांक fd)
अणु
	अगर (setns(fd, CLONE_NEWNET)) अणु
		pr_err("setns()");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Running the test inside a new parent net namespace to bother less
 * about cleanup on error-path.
 */
अटल पूर्णांक init_namespaces(व्योम)
अणु
	nsfd_parent = unshare_खोलो();
	अगर (nsfd_parent <= 0)
		वापस -1;

	nsfd_childa = unshare_खोलो();
	अगर (nsfd_childa <= 0)
		वापस -1;

	अगर (चयन_ns(nsfd_parent))
		वापस -1;

	nsfd_childb = unshare_खोलो();
	अगर (nsfd_childb <= 0)
		वापस -1;

	अगर (चयन_ns(nsfd_parent))
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक netlink_sock(पूर्णांक *sock, uपूर्णांक32_t *seq_nr, पूर्णांक proto)
अणु
	अगर (*sock > 0) अणु
		seq_nr++;
		वापस 0;
	पूर्ण

	*sock = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, proto);
	अगर (*sock <= 0) अणु
		pr_err("socket(AF_NETLINK)");
		वापस -1;
	पूर्ण

	अक्रमomize_buffer(seq_nr, माप(*seq_nr));

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा rtattr *rtattr_hdr(काष्ठा nlmsghdr *nh)
अणु
	वापस (काष्ठा rtattr *)((अक्षर *)(nh) + RTA_ALIGN((nh)->nlmsg_len));
पूर्ण

अटल पूर्णांक rtattr_pack(काष्ठा nlmsghdr *nh, माप_प्रकार req_sz,
		अचिन्हित लघु rta_type, स्थिर व्योम *payload, माप_प्रकार size)
अणु
	/* NLMSG_ALIGNTO == RTA_ALIGNTO, nlmsg_len alपढ़ोy aligned */
	काष्ठा rtattr *attr = rtattr_hdr(nh);
	माप_प्रकार nl_size = RTA_ALIGN(nh->nlmsg_len) + RTA_LENGTH(size);

	अगर (req_sz < nl_size) अणु
		prपूर्णांकk("req buf is too small: %zu < %zu", req_sz, nl_size);
		वापस -1;
	पूर्ण
	nh->nlmsg_len = nl_size;

	attr->rta_len = RTA_LENGTH(size);
	attr->rta_type = rta_type;
	स_नकल(RTA_DATA(attr), payload, size);

	वापस 0;
पूर्ण

अटल काष्ठा rtattr *_rtattr_begin(काष्ठा nlmsghdr *nh, माप_प्रकार req_sz,
		अचिन्हित लघु rta_type, स्थिर व्योम *payload, माप_प्रकार size)
अणु
	काष्ठा rtattr *ret = rtattr_hdr(nh);

	अगर (rtattr_pack(nh, req_sz, rta_type, payload, size))
		वापस 0;

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा rtattr *rtattr_begin(काष्ठा nlmsghdr *nh, माप_प्रकार req_sz,
		अचिन्हित लघु rta_type)
अणु
	वापस _rtattr_begin(nh, req_sz, rta_type, 0, 0);
पूर्ण

अटल अंतरभूत व्योम rtattr_end(काष्ठा nlmsghdr *nh, काष्ठा rtattr *attr)
अणु
	अक्षर *nlmsg_end = (अक्षर *)nh + nh->nlmsg_len;

	attr->rta_len = nlmsg_end - (अक्षर *)attr;
पूर्ण

अटल पूर्णांक veth_pack_peerb(काष्ठा nlmsghdr *nh, माप_प्रकार req_sz,
		स्थिर अक्षर *peer, पूर्णांक ns)
अणु
	काष्ठा अगरinfomsg pi;
	काष्ठा rtattr *peer_attr;

	स_रखो(&pi, 0, माप(pi));
	pi.अगरi_family	= AF_UNSPEC;
	pi.अगरi_change	= 0xFFFFFFFF;

	peer_attr = _rtattr_begin(nh, req_sz, VETH_INFO_PEER, &pi, माप(pi));
	अगर (!peer_attr)
		वापस -1;

	अगर (rtattr_pack(nh, req_sz, IFLA_IFNAME, peer, म_माप(peer)))
		वापस -1;

	अगर (rtattr_pack(nh, req_sz, IFLA_NET_NS_FD, &ns, माप(ns)))
		वापस -1;

	rtattr_end(nh, peer_attr);

	वापस 0;
पूर्ण

अटल पूर्णांक netlink_check_answer(पूर्णांक sock)
अणु
	काष्ठा nlmsgerror अणु
		काष्ठा nlmsghdr hdr;
		पूर्णांक error;
		काष्ठा nlmsghdr orig_msg;
	पूर्ण answer;

	अगर (recv(sock, &answer, माप(answer), 0) < 0) अणु
		pr_err("recv()");
		वापस -1;
	पूर्ण अन्यथा अगर (answer.hdr.nlmsg_type != NLMSG_ERROR) अणु
		prपूर्णांकk("expected NLMSG_ERROR, got %d", (पूर्णांक)answer.hdr.nlmsg_type);
		वापस -1;
	पूर्ण अन्यथा अगर (answer.error) अणु
		prपूर्णांकk("NLMSG_ERROR: %d: %s",
			answer.error, म_त्रुटि(-answer.error));
		वापस answer.error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक veth_add(पूर्णांक sock, uपूर्णांक32_t seq, स्थिर अक्षर *peera, पूर्णांक ns_a,
		स्थिर अक्षर *peerb, पूर्णांक ns_b)
अणु
	uपूर्णांक16_t flags = NLM_F_REQUEST | NLM_F_ACK | NLM_F_EXCL | NLM_F_CREATE;
	काष्ठा अणु
		काष्ठा nlmsghdr		nh;
		काष्ठा अगरinfomsg	info;
		अक्षर			attrbuf[MAX_PAYLOAD];
	पूर्ण req;
	स्थिर अक्षर veth_type[] = "veth";
	काष्ठा rtattr *link_info, *info_data;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.info));
	req.nh.nlmsg_type	= RTM_NEWLINK;
	req.nh.nlmsg_flags	= flags;
	req.nh.nlmsg_seq	= seq;
	req.info.अगरi_family	= AF_UNSPEC;
	req.info.अगरi_change	= 0xFFFFFFFF;

	अगर (rtattr_pack(&req.nh, माप(req), IFLA_IFNAME, peera, म_माप(peera)))
		वापस -1;

	अगर (rtattr_pack(&req.nh, माप(req), IFLA_NET_NS_FD, &ns_a, माप(ns_a)))
		वापस -1;

	link_info = rtattr_begin(&req.nh, माप(req), IFLA_LINKINFO);
	अगर (!link_info)
		वापस -1;

	अगर (rtattr_pack(&req.nh, माप(req), IFLA_INFO_KIND, veth_type, माप(veth_type)))
		वापस -1;

	info_data = rtattr_begin(&req.nh, माप(req), IFLA_INFO_DATA);
	अगर (!info_data)
		वापस -1;

	अगर (veth_pack_peerb(&req.nh, माप(req), peerb, ns_b))
		वापस -1;

	rtattr_end(&req.nh, info_data);
	rtattr_end(&req.nh, link_info);

	अगर (send(sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण
	वापस netlink_check_answer(sock);
पूर्ण

अटल पूर्णांक ip4_addr_set(पूर्णांक sock, uपूर्णांक32_t seq, स्थिर अक्षर *पूर्णांकf,
		काष्ठा in_addr addr, uपूर्णांक8_t prefix)
अणु
	uपूर्णांक16_t flags = NLM_F_REQUEST | NLM_F_ACK | NLM_F_EXCL | NLM_F_CREATE;
	काष्ठा अणु
		काष्ठा nlmsghdr		nh;
		काष्ठा अगरaddrmsg	info;
		अक्षर			attrbuf[MAX_PAYLOAD];
	पूर्ण req;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.info));
	req.nh.nlmsg_type	= RTM_NEWADDR;
	req.nh.nlmsg_flags	= flags;
	req.nh.nlmsg_seq	= seq;
	req.info.अगरa_family	= AF_INET;
	req.info.अगरa_prefixlen	= prefix;
	req.info.अगरa_index	= अगर_nametoindex(पूर्णांकf);

#अगर_घोषित DEBUG
	अणु
		अक्षर addr_str[IPV4_STR_SZ] = अणुपूर्ण;

		म_नकलन(addr_str, inet_ntoa(addr), IPV4_STR_SZ - 1);

		prपूर्णांकk("ip addr set %s", addr_str);
	पूर्ण
#पूर्ण_अगर

	अगर (rtattr_pack(&req.nh, माप(req), IFA_LOCAL, &addr, माप(addr)))
		वापस -1;

	अगर (rtattr_pack(&req.nh, माप(req), IFA_ADDRESS, &addr, माप(addr)))
		वापस -1;

	अगर (send(sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण
	वापस netlink_check_answer(sock);
पूर्ण

अटल पूर्णांक link_set_up(पूर्णांक sock, uपूर्णांक32_t seq, स्थिर अक्षर *पूर्णांकf)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr		nh;
		काष्ठा अगरinfomsg	info;
		अक्षर			attrbuf[MAX_PAYLOAD];
	पूर्ण req;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.info));
	req.nh.nlmsg_type	= RTM_NEWLINK;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_seq	= seq;
	req.info.अगरi_family	= AF_UNSPEC;
	req.info.अगरi_change	= 0xFFFFFFFF;
	req.info.अगरi_index	= अगर_nametoindex(पूर्णांकf);
	req.info.अगरi_flags	= IFF_UP;
	req.info.अगरi_change	= IFF_UP;

	अगर (send(sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण
	वापस netlink_check_answer(sock);
पूर्ण

अटल पूर्णांक ip4_route_set(पूर्णांक sock, uपूर्णांक32_t seq, स्थिर अक्षर *पूर्णांकf,
		काष्ठा in_addr src, काष्ठा in_addr dst)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr	nh;
		काष्ठा rपंचांगsg	rt;
		अक्षर		attrbuf[MAX_PAYLOAD];
	पूर्ण req;
	अचिन्हित पूर्णांक index = अगर_nametoindex(पूर्णांकf);

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.rt));
	req.nh.nlmsg_type	= RTM_NEWROUTE;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK | NLM_F_CREATE;
	req.nh.nlmsg_seq	= seq;
	req.rt.rपंचांग_family	= AF_INET;
	req.rt.rपंचांग_dst_len	= 32;
	req.rt.rपंचांग_table	= RT_TABLE_MAIN;
	req.rt.rपंचांग_protocol	= RTPROT_BOOT;
	req.rt.rपंचांग_scope	= RT_SCOPE_LINK;
	req.rt.rपंचांग_type		= RTN_UNICAST;

	अगर (rtattr_pack(&req.nh, माप(req), RTA_DST, &dst, माप(dst)))
		वापस -1;

	अगर (rtattr_pack(&req.nh, माप(req), RTA_PREFSRC, &src, माप(src)))
		वापस -1;

	अगर (rtattr_pack(&req.nh, माप(req), RTA_OIF, &index, माप(index)))
		वापस -1;

	अगर (send(sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण

	वापस netlink_check_answer(sock);
पूर्ण

अटल पूर्णांक tunnel_set_route(पूर्णांक route_sock, uपूर्णांक32_t *route_seq, अक्षर *veth,
		काष्ठा in_addr tunsrc, काष्ठा in_addr tundst)
अणु
	अगर (ip4_addr_set(route_sock, (*route_seq)++, "lo",
			tunsrc, PREFIX_LEN)) अणु
		prपूर्णांकk("Failed to set ipv4 addr");
		वापस -1;
	पूर्ण

	अगर (ip4_route_set(route_sock, (*route_seq)++, veth, tunsrc, tundst)) अणु
		prपूर्णांकk("Failed to set ipv4 route");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_child(पूर्णांक nsfd, अक्षर *veth, अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dst)
अणु
	काष्ठा in_addr पूर्णांकsrc = inet_makeaddr(INADDR_B, src);
	काष्ठा in_addr tunsrc = inet_makeaddr(INADDR_A, src);
	काष्ठा in_addr tundst = inet_makeaddr(INADDR_A, dst);
	पूर्णांक route_sock = -1, ret = -1;
	uपूर्णांक32_t route_seq;

	अगर (चयन_ns(nsfd))
		वापस -1;

	अगर (netlink_sock(&route_sock, &route_seq, NETLINK_ROUTE)) अणु
		prपूर्णांकk("Failed to open netlink route socket in child");
		वापस -1;
	पूर्ण

	अगर (ip4_addr_set(route_sock, route_seq++, veth, पूर्णांकsrc, PREFIX_LEN)) अणु
		prपूर्णांकk("Failed to set ipv4 addr");
		जाओ err;
	पूर्ण

	अगर (link_set_up(route_sock, route_seq++, veth)) अणु
		prपूर्णांकk("Failed to bring up %s", veth);
		जाओ err;
	पूर्ण

	अगर (tunnel_set_route(route_sock, &route_seq, veth, tunsrc, tundst)) अणु
		prपूर्णांकk("Failed to add tunnel route on %s", veth);
		जाओ err;
	पूर्ण
	ret = 0;

err:
	बंद(route_sock);
	वापस ret;
पूर्ण

#घोषणा ALGO_LEN	64
क्रमागत desc_type अणु
	CREATE_TUNNEL	= 0,
	ALLOCATE_SPI,
	MONITOR_ACQUIRE,
	EXPIRE_STATE,
	EXPIRE_POLICY,
पूर्ण;
स्थिर अक्षर *desc_name[] = अणु
	"create tunnel",
	"alloc spi",
	"monitor acquire",
	"expire state",
	"expire policy"
पूर्ण;
काष्ठा xfrm_desc अणु
	क्रमागत desc_type	type;
	uपूर्णांक8_t		proto;
	अक्षर		a_algo[ALGO_LEN];
	अक्षर		e_algo[ALGO_LEN];
	अक्षर		c_algo[ALGO_LEN];
	अक्षर		ae_algo[ALGO_LEN];
	अचिन्हित पूर्णांक	icv_len;
	/* अचिन्हित key_len; */
पूर्ण;

क्रमागत msg_type अणु
	MSG_ACK		= 0,
	MSG_EXIT,
	MSG_PING,
	MSG_XFRM_PREPARE,
	MSG_XFRM_ADD,
	MSG_XFRM_DEL,
	MSG_XFRM_CLEANUP,
पूर्ण;

काष्ठा test_desc अणु
	क्रमागत msg_type type;
	जोड़ अणु
		काष्ठा अणु
			in_addr_t reply_ip;
			अचिन्हित पूर्णांक port;
		पूर्ण ping;
		काष्ठा xfrm_desc xfrm_desc;
	पूर्ण body;
पूर्ण;

काष्ठा test_result अणु
	काष्ठा xfrm_desc desc;
	अचिन्हित पूर्णांक res;
पूर्ण;

अटल व्योम ग_लिखो_test_result(अचिन्हित पूर्णांक res, काष्ठा xfrm_desc *d)
अणु
	काष्ठा test_result tr = अणुपूर्ण;
	sमाप_प्रकार ret;

	tr.desc = *d;
	tr.res = res;

	ret = ग_लिखो(results_fd[1], &tr, माप(tr));
	अगर (ret != माप(tr))
		pr_err("Failed to write the result in pipe %zd", ret);
पूर्ण

अटल व्योम ग_लिखो_msg(पूर्णांक fd, काष्ठा test_desc *msg, bool निकास_of_fail)
अणु
	sमाप_प्रकार bytes = ग_लिखो(fd, msg, माप(*msg));

	/* Make sure that ग_लिखो/पढ़ो is atomic to a pipe */
	BUILD_BUG_ON(माप(काष्ठा test_desc) > PIPE_BUF);

	अगर (bytes < 0) अणु
		pr_err("write()");
		अगर (निकास_of_fail)
			निकास(KSFT_FAIL);
	पूर्ण
	अगर (bytes != माप(*msg)) अणु
		pr_err("sent part of the message %zd/%zu", bytes, माप(*msg));
		अगर (निकास_of_fail)
			निकास(KSFT_FAIL);
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_msg(पूर्णांक fd, काष्ठा test_desc *msg, bool निकास_of_fail)
अणु
	sमाप_प्रकार bytes = पढ़ो(fd, msg, माप(*msg));

	अगर (bytes < 0) अणु
		pr_err("read()");
		अगर (निकास_of_fail)
			निकास(KSFT_FAIL);
	पूर्ण
	अगर (bytes != माप(*msg)) अणु
		pr_err("got incomplete message %zd/%zu", bytes, माप(*msg));
		अगर (निकास_of_fail)
			निकास(KSFT_FAIL);
	पूर्ण
पूर्ण

अटल पूर्णांक udp_ping_init(काष्ठा in_addr listen_ip, अचिन्हित पूर्णांक u_समयout,
		अचिन्हित पूर्णांक *server_port, पूर्णांक sock[2])
अणु
	काष्ठा sockaddr_in server;
	काष्ठा समयval t = अणु .tv_sec = 0, .tv_usec = u_समयout पूर्ण;
	socklen_t s_len = माप(server);

	sock[0] = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (sock[0] < 0) अणु
		pr_err("socket()");
		वापस -1;
	पूर्ण

	server.sin_family	= AF_INET;
	server.sin_port		= 0;
	स_नकल(&server.sin_addr.s_addr, &listen_ip, माप(काष्ठा in_addr));

	अगर (bind(sock[0], (काष्ठा sockaddr *)&server, s_len)) अणु
		pr_err("bind()");
		जाओ err_बंद_server;
	पूर्ण

	अगर (माला_लोockname(sock[0], (काष्ठा sockaddr *)&server, &s_len)) अणु
		pr_err("getsockname()");
		जाओ err_बंद_server;
	पूर्ण

	*server_port = ntohs(server.sin_port);

	अगर (setsockopt(sock[0], SOL_SOCKET, SO_RCVTIMEO, (स्थिर अक्षर *)&t, माप t)) अणु
		pr_err("setsockopt()");
		जाओ err_बंद_server;
	पूर्ण

	sock[1] = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (sock[1] < 0) अणु
		pr_err("socket()");
		जाओ err_बंद_server;
	पूर्ण

	वापस 0;

err_बंद_server:
	बंद(sock[0]);
	वापस -1;
पूर्ण

अटल पूर्णांक udp_ping_send(पूर्णांक sock[2], in_addr_t dest_ip, अचिन्हित पूर्णांक port,
		अक्षर *buf, माप_प्रकार buf_len)
अणु
	काष्ठा sockaddr_in server;
	स्थिर काष्ठा sockaddr *dest_addr = (काष्ठा sockaddr *)&server;
	अक्षर *sock_buf[buf_len];
	sमाप_प्रकार r_bytes, s_bytes;

	server.sin_family	= AF_INET;
	server.sin_port		= htons(port);
	server.sin_addr.s_addr	= dest_ip;

	s_bytes = sendto(sock[1], buf, buf_len, 0, dest_addr, माप(server));
	अगर (s_bytes < 0) अणु
		pr_err("sendto()");
		वापस -1;
	पूर्ण अन्यथा अगर (s_bytes != buf_len) अणु
		prपूर्णांकk("send part of the message: %zd/%zu", s_bytes, माप(server));
		वापस -1;
	पूर्ण

	r_bytes = recv(sock[0], sock_buf, buf_len, 0);
	अगर (r_bytes < 0) अणु
		अगर (त्रुटि_सं != EAGAIN)
			pr_err("recv()");
		वापस -1;
	पूर्ण अन्यथा अगर (r_bytes == 0) अणु /* खातापूर्ण */
		prपूर्णांकk("EOF on reply to ping");
		वापस -1;
	पूर्ण अन्यथा अगर (r_bytes != buf_len || स_भेद(buf, sock_buf, buf_len)) अणु
		prपूर्णांकk("ping reply packet is corrupted %zd/%zu", r_bytes, buf_len);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक udp_ping_reply(पूर्णांक sock[2], in_addr_t dest_ip, अचिन्हित पूर्णांक port,
		अक्षर *buf, माप_प्रकार buf_len)
अणु
	काष्ठा sockaddr_in server;
	स्थिर काष्ठा sockaddr *dest_addr = (काष्ठा sockaddr *)&server;
	अक्षर *sock_buf[buf_len];
	sमाप_प्रकार r_bytes, s_bytes;

	server.sin_family	= AF_INET;
	server.sin_port		= htons(port);
	server.sin_addr.s_addr	= dest_ip;

	r_bytes = recv(sock[0], sock_buf, buf_len, 0);
	अगर (r_bytes < 0) अणु
		अगर (त्रुटि_सं != EAGAIN)
			pr_err("recv()");
		वापस -1;
	पूर्ण
	अगर (r_bytes == 0) अणु /* खातापूर्ण */
		prपूर्णांकk("EOF on reply to ping");
		वापस -1;
	पूर्ण
	अगर (r_bytes != buf_len || स_भेद(buf, sock_buf, buf_len)) अणु
		prपूर्णांकk("ping reply packet is corrupted %zd/%zu", r_bytes, buf_len);
		वापस -1;
	पूर्ण

	s_bytes = sendto(sock[1], buf, buf_len, 0, dest_addr, माप(server));
	अगर (s_bytes < 0) अणु
		pr_err("sendto()");
		वापस -1;
	पूर्ण अन्यथा अगर (s_bytes != buf_len) अणु
		prपूर्णांकk("send part of the message: %zd/%zu", s_bytes, माप(server));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

प्रकार पूर्णांक (*ping_f)(पूर्णांक sock[2], in_addr_t dest_ip, अचिन्हित पूर्णांक port,
		अक्षर *buf, माप_प्रकार buf_len);
अटल पूर्णांक करो_ping(पूर्णांक cmd_fd, अक्षर *buf, माप_प्रकार buf_len, काष्ठा in_addr from,
		bool init_side, पूर्णांक d_port, in_addr_t to, ping_f func)
अणु
	काष्ठा test_desc msg;
	अचिन्हित पूर्णांक s_port, i, ping_succeeded = 0;
	पूर्णांक ping_sock[2];
	अक्षर to_str[IPV4_STR_SZ] = अणुपूर्ण, from_str[IPV4_STR_SZ] = अणुपूर्ण;

	अगर (udp_ping_init(from, ping_समयout, &s_port, ping_sock)) अणु
		prपूर्णांकk("Failed to init ping");
		वापस -1;
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	msg.type		= MSG_PING;
	msg.body.ping.port	= s_port;
	स_नकल(&msg.body.ping.reply_ip, &from, माप(from));

	ग_लिखो_msg(cmd_fd, &msg, 0);
	अगर (init_side) अणु
		/* The other end sends ip to ping */
		पढ़ो_msg(cmd_fd, &msg, 0);
		अगर (msg.type != MSG_PING)
			वापस -1;
		to = msg.body.ping.reply_ip;
		d_port = msg.body.ping.port;
	पूर्ण

	क्रम (i = 0; i < ping_count ; i++) अणु
		काष्ठा बारpec sleep_समय = अणु
			.tv_sec = 0,
			.tv_nsec = ping_delay_nsec,
		पूर्ण;

		ping_succeeded += !func(ping_sock, to, d_port, buf, page_size);
		nanosleep(&sleep_समय, 0);
	पूर्ण

	बंद(ping_sock[0]);
	बंद(ping_sock[1]);

	म_नकलन(to_str, inet_ntoa(*(काष्ठा in_addr *)&to), IPV4_STR_SZ - 1);
	म_नकलन(from_str, inet_ntoa(from), IPV4_STR_SZ - 1);

	अगर (ping_succeeded < ping_success) अणु
		prपूर्णांकk("ping (%s) %s->%s failed %u/%u times",
			init_side ? "send" : "reply", from_str, to_str,
			ping_count - ping_succeeded, ping_count);
		वापस -1;
	पूर्ण

#अगर_घोषित DEBUG
	prपूर्णांकk("ping (%s) %s->%s succeeded %u/%u times",
		init_side ? "send" : "reply", from_str, to_str,
		ping_succeeded, ping_count);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_fill_key(अक्षर *name, अक्षर *buf,
		माप_प्रकार buf_len, अचिन्हित पूर्णांक *key_len)
अणु
	/* TODO: use set/map instead */
	अगर (म_भेदन(name, "digest_null", ALGO_LEN) == 0)
		*key_len = 0;
	अन्यथा अगर (म_भेदन(name, "ecb(cipher_null)", ALGO_LEN) == 0)
		*key_len = 0;
	अन्यथा अगर (म_भेदन(name, "cbc(des)", ALGO_LEN) == 0)
		*key_len = 64;
	अन्यथा अगर (म_भेदन(name, "hmac(md5)", ALGO_LEN) == 0)
		*key_len = 128;
	अन्यथा अगर (म_भेदन(name, "cmac(aes)", ALGO_LEN) == 0)
		*key_len = 128;
	अन्यथा अगर (म_भेदन(name, "xcbc(aes)", ALGO_LEN) == 0)
		*key_len = 128;
	अन्यथा अगर (म_भेदन(name, "cbc(cast5)", ALGO_LEN) == 0)
		*key_len = 128;
	अन्यथा अगर (म_भेदन(name, "cbc(serpent)", ALGO_LEN) == 0)
		*key_len = 128;
	अन्यथा अगर (म_भेदन(name, "hmac(sha1)", ALGO_LEN) == 0)
		*key_len = 160;
	अन्यथा अगर (म_भेदन(name, "hmac(rmd160)", ALGO_LEN) == 0)
		*key_len = 160;
	अन्यथा अगर (म_भेदन(name, "cbc(des3_ede)", ALGO_LEN) == 0)
		*key_len = 192;
	अन्यथा अगर (म_भेदन(name, "hmac(sha256)", ALGO_LEN) == 0)
		*key_len = 256;
	अन्यथा अगर (म_भेदन(name, "cbc(aes)", ALGO_LEN) == 0)
		*key_len = 256;
	अन्यथा अगर (म_भेदन(name, "cbc(camellia)", ALGO_LEN) == 0)
		*key_len = 256;
	अन्यथा अगर (म_भेदन(name, "cbc(twofish)", ALGO_LEN) == 0)
		*key_len = 256;
	अन्यथा अगर (म_भेदन(name, "rfc3686(ctr(aes))", ALGO_LEN) == 0)
		*key_len = 288;
	अन्यथा अगर (म_भेदन(name, "hmac(sha384)", ALGO_LEN) == 0)
		*key_len = 384;
	अन्यथा अगर (म_भेदन(name, "cbc(blowfish)", ALGO_LEN) == 0)
		*key_len = 448;
	अन्यथा अगर (म_भेदन(name, "hmac(sha512)", ALGO_LEN) == 0)
		*key_len = 512;
	अन्यथा अगर (म_भेदन(name, "rfc4106(gcm(aes))-128", ALGO_LEN) == 0)
		*key_len = 160;
	अन्यथा अगर (म_भेदन(name, "rfc4543(gcm(aes))-128", ALGO_LEN) == 0)
		*key_len = 160;
	अन्यथा अगर (म_भेदन(name, "rfc4309(ccm(aes))-128", ALGO_LEN) == 0)
		*key_len = 152;
	अन्यथा अगर (म_भेदन(name, "rfc4106(gcm(aes))-192", ALGO_LEN) == 0)
		*key_len = 224;
	अन्यथा अगर (म_भेदन(name, "rfc4543(gcm(aes))-192", ALGO_LEN) == 0)
		*key_len = 224;
	अन्यथा अगर (म_भेदन(name, "rfc4309(ccm(aes))-192", ALGO_LEN) == 0)
		*key_len = 216;
	अन्यथा अगर (म_भेदन(name, "rfc4106(gcm(aes))-256", ALGO_LEN) == 0)
		*key_len = 288;
	अन्यथा अगर (म_भेदन(name, "rfc4543(gcm(aes))-256", ALGO_LEN) == 0)
		*key_len = 288;
	अन्यथा अगर (म_भेदन(name, "rfc4309(ccm(aes))-256", ALGO_LEN) == 0)
		*key_len = 280;
	अन्यथा अगर (म_भेदन(name, "rfc7539(chacha20,poly1305)-128", ALGO_LEN) == 0)
		*key_len = 0;

	अगर (*key_len > buf_len) अणु
		prपूर्णांकk("Can't pack a key - too big for buffer");
		वापस -1;
	पूर्ण

	अक्रमomize_buffer(buf, *key_len);

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_state_pack_algo(काष्ठा nlmsghdr *nh, माप_प्रकार req_sz,
		काष्ठा xfrm_desc *desc)
अणु
	काष्ठा अणु
		जोड़ अणु
			काष्ठा xfrm_algo	alg;
			काष्ठा xfrm_algo_aead	aead;
			काष्ठा xfrm_algo_auth	auth;
		पूर्ण u;
		अक्षर buf[XFRM_ALGO_KEY_BUF_SIZE];
	पूर्ण alg = अणुपूर्ण;
	माप_प्रकार alen, elen, clen, aelen;
	अचिन्हित लघु type;

	alen = म_माप(desc->a_algo);
	elen = म_माप(desc->e_algo);
	clen = म_माप(desc->c_algo);
	aelen = म_माप(desc->ae_algo);

	/* Verअगरy desc */
	चयन (desc->proto) अणु
	हाल IPPROTO_AH:
		अगर (!alen || elen || clen || aelen) अणु
			prपूर्णांकk("BUG: buggy ah desc");
			वापस -1;
		पूर्ण
		म_नकलन(alg.u.alg.alg_name, desc->a_algo, ALGO_LEN - 1);
		अगर (xfrm_fill_key(desc->a_algo, alg.u.alg.alg_key,
				माप(alg.buf), &alg.u.alg.alg_key_len))
			वापस -1;
		type = XFRMA_ALG_AUTH;
		अवरोध;
	हाल IPPROTO_COMP:
		अगर (!clen || elen || alen || aelen) अणु
			prपूर्णांकk("BUG: buggy comp desc");
			वापस -1;
		पूर्ण
		म_नकलन(alg.u.alg.alg_name, desc->c_algo, ALGO_LEN - 1);
		अगर (xfrm_fill_key(desc->c_algo, alg.u.alg.alg_key,
				माप(alg.buf), &alg.u.alg.alg_key_len))
			वापस -1;
		type = XFRMA_ALG_COMP;
		अवरोध;
	हाल IPPROTO_ESP:
		अगर (!((alen && elen) ^ aelen) || clen) अणु
			prपूर्णांकk("BUG: buggy esp desc");
			वापस -1;
		पूर्ण
		अगर (aelen) अणु
			alg.u.aead.alg_icv_len = desc->icv_len;
			म_नकलन(alg.u.aead.alg_name, desc->ae_algo, ALGO_LEN - 1);
			अगर (xfrm_fill_key(desc->ae_algo, alg.u.aead.alg_key,
						माप(alg.buf), &alg.u.aead.alg_key_len))
				वापस -1;
			type = XFRMA_ALG_AEAD;
		पूर्ण अन्यथा अणु

			म_नकलन(alg.u.alg.alg_name, desc->e_algo, ALGO_LEN - 1);
			type = XFRMA_ALG_CRYPT;
			अगर (xfrm_fill_key(desc->e_algo, alg.u.alg.alg_key,
						माप(alg.buf), &alg.u.alg.alg_key_len))
				वापस -1;
			अगर (rtattr_pack(nh, req_sz, type, &alg, माप(alg)))
				वापस -1;

			म_नकलन(alg.u.alg.alg_name, desc->a_algo, ALGO_LEN);
			type = XFRMA_ALG_AUTH;
			अगर (xfrm_fill_key(desc->a_algo, alg.u.alg.alg_key,
						माप(alg.buf), &alg.u.alg.alg_key_len))
				वापस -1;
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk("BUG: unknown proto in desc");
		वापस -1;
	पूर्ण

	अगर (rtattr_pack(nh, req_sz, type, &alg, माप(alg)))
		वापस -1;

	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t gen_spi(काष्ठा in_addr src)
अणु
	वापस htonl(inet_lnaof(src));
पूर्ण

अटल पूर्णांक xfrm_state_add(पूर्णांक xfrm_sock, uपूर्णांक32_t seq, uपूर्णांक32_t spi,
		काष्ठा in_addr src, काष्ठा in_addr dst,
		काष्ठा xfrm_desc *desc)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr		nh;
		काष्ठा xfrm_usersa_info	info;
		अक्षर			attrbuf[MAX_PAYLOAD];
	पूर्ण req;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.info));
	req.nh.nlmsg_type	= XFRM_MSG_NEWSA;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_seq	= seq;

	/* Fill selector. */
	स_नकल(&req.info.sel.daddr, &dst, माप(dst));
	स_नकल(&req.info.sel.saddr, &src, माप(src));
	req.info.sel.family		= AF_INET;
	req.info.sel.prefixlen_d	= PREFIX_LEN;
	req.info.sel.prefixlen_s	= PREFIX_LEN;

	/* Fill id */
	स_नकल(&req.info.id.daddr, &dst, माप(dst));
	/* Note: zero-spi cannot be deleted */
	req.info.id.spi = spi;
	req.info.id.proto	= desc->proto;

	स_नकल(&req.info.saddr, &src, माप(src));

	/* Fill lअगरteme_cfg */
	req.info.lft.soft_byte_limit	= XFRM_INF;
	req.info.lft.hard_byte_limit	= XFRM_INF;
	req.info.lft.soft_packet_limit	= XFRM_INF;
	req.info.lft.hard_packet_limit	= XFRM_INF;

	req.info.family		= AF_INET;
	req.info.mode		= XFRM_MODE_TUNNEL;

	अगर (xfrm_state_pack_algo(&req.nh, माप(req), desc))
		वापस -1;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण

	वापस netlink_check_answer(xfrm_sock);
पूर्ण

अटल bool xfrm_usersa_found(काष्ठा xfrm_usersa_info *info, uपूर्णांक32_t spi,
		काष्ठा in_addr src, काष्ठा in_addr dst,
		काष्ठा xfrm_desc *desc)
अणु
	अगर (स_भेद(&info->sel.daddr, &dst, माप(dst)))
		वापस false;

	अगर (स_भेद(&info->sel.saddr, &src, माप(src)))
		वापस false;

	अगर (info->sel.family != AF_INET					||
			info->sel.prefixlen_d != PREFIX_LEN		||
			info->sel.prefixlen_s != PREFIX_LEN)
		वापस false;

	अगर (info->id.spi != spi || info->id.proto != desc->proto)
		वापस false;

	अगर (स_भेद(&info->id.daddr, &dst, माप(dst)))
		वापस false;

	अगर (स_भेद(&info->saddr, &src, माप(src)))
		वापस false;

	अगर (info->lft.soft_byte_limit != XFRM_INF			||
			info->lft.hard_byte_limit != XFRM_INF		||
			info->lft.soft_packet_limit != XFRM_INF		||
			info->lft.hard_packet_limit != XFRM_INF)
		वापस false;

	अगर (info->family != AF_INET || info->mode != XFRM_MODE_TUNNEL)
		वापस false;

	/* XXX: check xfrm algo, see xfrm_state_pack_algo(). */

	वापस true;
पूर्ण

अटल पूर्णांक xfrm_state_check(पूर्णांक xfrm_sock, uपूर्णांक32_t seq, uपूर्णांक32_t spi,
		काष्ठा in_addr src, काष्ठा in_addr dst,
		काष्ठा xfrm_desc *desc)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr		nh;
		अक्षर			attrbuf[MAX_PAYLOAD];
	पूर्ण req;
	काष्ठा अणु
		काष्ठा nlmsghdr		nh;
		जोड़ अणु
			काष्ठा xfrm_usersa_info	info;
			पूर्णांक error;
		पूर्ण;
		अक्षर			attrbuf[MAX_PAYLOAD];
	पूर्ण answer;
	काष्ठा xfrm_address_filter filter = अणुपूर्ण;
	bool found = false;


	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(0);
	req.nh.nlmsg_type	= XFRM_MSG_GETSA;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_DUMP;
	req.nh.nlmsg_seq	= seq;

	/*
	 * Add dump filter by source address as there may be other tunnels
	 * in this netns (अगर tests run in parallel).
	 */
	filter.family = AF_INET;
	filter.splen = 0x1f;	/* 0xffffffff mask see addr_match() */
	स_नकल(&filter.saddr, &src, माप(src));
	अगर (rtattr_pack(&req.nh, माप(req), XFRMA_ADDRESS_FILTER,
				&filter, माप(filter)))
		वापस -1;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण

	जबतक (1) अणु
		अगर (recv(xfrm_sock, &answer, माप(answer), 0) < 0) अणु
			pr_err("recv()");
			वापस -1;
		पूर्ण
		अगर (answer.nh.nlmsg_type == NLMSG_ERROR) अणु
			prपूर्णांकk("NLMSG_ERROR: %d: %s",
				answer.error, म_त्रुटि(-answer.error));
			वापस -1;
		पूर्ण अन्यथा अगर (answer.nh.nlmsg_type == NLMSG_DONE) अणु
			अगर (found)
				वापस 0;
			prपूर्णांकk("didn't find allocated xfrm state in dump");
			वापस -1;
		पूर्ण अन्यथा अगर (answer.nh.nlmsg_type == XFRM_MSG_NEWSA) अणु
			अगर (xfrm_usersa_found(&answer.info, spi, src, dst, desc))
				found = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xfrm_set(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq,
		काष्ठा in_addr src, काष्ठा in_addr dst,
		काष्ठा in_addr tunsrc, काष्ठा in_addr tundst,
		काष्ठा xfrm_desc *desc)
अणु
	पूर्णांक err;

	err = xfrm_state_add(xfrm_sock, (*seq)++, gen_spi(src), src, dst, desc);
	अगर (err) अणु
		prपूर्णांकk("Failed to add xfrm state");
		वापस -1;
	पूर्ण

	err = xfrm_state_add(xfrm_sock, (*seq)++, gen_spi(src), dst, src, desc);
	अगर (err) अणु
		prपूर्णांकk("Failed to add xfrm state");
		वापस -1;
	पूर्ण

	/* Check dumps क्रम XFRM_MSG_GETSA */
	err = xfrm_state_check(xfrm_sock, (*seq)++, gen_spi(src), src, dst, desc);
	err |= xfrm_state_check(xfrm_sock, (*seq)++, gen_spi(src), dst, src, desc);
	अगर (err) अणु
		prपूर्णांकk("Failed to check xfrm state");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_policy_add(पूर्णांक xfrm_sock, uपूर्णांक32_t seq, uपूर्णांक32_t spi,
		काष्ठा in_addr src, काष्ठा in_addr dst, uपूर्णांक8_t dir,
		काष्ठा in_addr tunsrc, काष्ठा in_addr tundst, uपूर्णांक8_t proto)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr			nh;
		काष्ठा xfrm_userpolicy_info	info;
		अक्षर				attrbuf[MAX_PAYLOAD];
	पूर्ण req;
	काष्ठा xfrm_user_पंचांगpl पंचांगpl;

	स_रखो(&req, 0, माप(req));
	स_रखो(&पंचांगpl, 0, माप(पंचांगpl));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.info));
	req.nh.nlmsg_type	= XFRM_MSG_NEWPOLICY;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_seq	= seq;

	/* Fill selector. */
	स_नकल(&req.info.sel.daddr, &dst, माप(tundst));
	स_नकल(&req.info.sel.saddr, &src, माप(tunsrc));
	req.info.sel.family		= AF_INET;
	req.info.sel.prefixlen_d	= PREFIX_LEN;
	req.info.sel.prefixlen_s	= PREFIX_LEN;

	/* Fill lअगरteme_cfg */
	req.info.lft.soft_byte_limit	= XFRM_INF;
	req.info.lft.hard_byte_limit	= XFRM_INF;
	req.info.lft.soft_packet_limit	= XFRM_INF;
	req.info.lft.hard_packet_limit	= XFRM_INF;

	req.info.dir = dir;

	/* Fill पंचांगpl */
	स_नकल(&पंचांगpl.id.daddr, &dst, माप(dst));
	/* Note: zero-spi cannot be deleted */
	पंचांगpl.id.spi = spi;
	पंचांगpl.id.proto	= proto;
	पंचांगpl.family	= AF_INET;
	स_नकल(&पंचांगpl.saddr, &src, माप(src));
	पंचांगpl.mode	= XFRM_MODE_TUNNEL;
	पंचांगpl.aalgos = (~(uपूर्णांक32_t)0);
	पंचांगpl.ealgos = (~(uपूर्णांक32_t)0);
	पंचांगpl.calgos = (~(uपूर्णांक32_t)0);

	अगर (rtattr_pack(&req.nh, माप(req), XFRMA_TMPL, &पंचांगpl, माप(पंचांगpl)))
		वापस -1;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण

	वापस netlink_check_answer(xfrm_sock);
पूर्ण

अटल पूर्णांक xfrm_prepare(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq,
		काष्ठा in_addr src, काष्ठा in_addr dst,
		काष्ठा in_addr tunsrc, काष्ठा in_addr tundst, uपूर्णांक8_t proto)
अणु
	अगर (xfrm_policy_add(xfrm_sock, (*seq)++, gen_spi(src), src, dst,
				XFRM_POLICY_OUT, tunsrc, tundst, proto)) अणु
		prपूर्णांकk("Failed to add xfrm policy");
		वापस -1;
	पूर्ण

	अगर (xfrm_policy_add(xfrm_sock, (*seq)++, gen_spi(src), dst, src,
				XFRM_POLICY_IN, tunsrc, tundst, proto)) अणु
		prपूर्णांकk("Failed to add xfrm policy");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_policy_del(पूर्णांक xfrm_sock, uपूर्णांक32_t seq,
		काष्ठा in_addr src, काष्ठा in_addr dst, uपूर्णांक8_t dir,
		काष्ठा in_addr tunsrc, काष्ठा in_addr tundst)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr			nh;
		काष्ठा xfrm_userpolicy_id	id;
		अक्षर				attrbuf[MAX_PAYLOAD];
	पूर्ण req;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.id));
	req.nh.nlmsg_type	= XFRM_MSG_DELPOLICY;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_seq	= seq;

	/* Fill id */
	स_नकल(&req.id.sel.daddr, &dst, माप(tundst));
	स_नकल(&req.id.sel.saddr, &src, माप(tunsrc));
	req.id.sel.family		= AF_INET;
	req.id.sel.prefixlen_d		= PREFIX_LEN;
	req.id.sel.prefixlen_s		= PREFIX_LEN;
	req.id.dir = dir;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण

	वापस netlink_check_answer(xfrm_sock);
पूर्ण

अटल पूर्णांक xfrm_cleanup(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq,
		काष्ठा in_addr src, काष्ठा in_addr dst,
		काष्ठा in_addr tunsrc, काष्ठा in_addr tundst)
अणु
	अगर (xfrm_policy_del(xfrm_sock, (*seq)++, src, dst,
				XFRM_POLICY_OUT, tunsrc, tundst)) अणु
		prपूर्णांकk("Failed to add xfrm policy");
		वापस -1;
	पूर्ण

	अगर (xfrm_policy_del(xfrm_sock, (*seq)++, dst, src,
				XFRM_POLICY_IN, tunsrc, tundst)) अणु
		prपूर्णांकk("Failed to add xfrm policy");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_state_del(पूर्णांक xfrm_sock, uपूर्णांक32_t seq, uपूर्णांक32_t spi,
		काष्ठा in_addr src, काष्ठा in_addr dst, uपूर्णांक8_t proto)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr		nh;
		काष्ठा xfrm_usersa_id	id;
		अक्षर			attrbuf[MAX_PAYLOAD];
	पूर्ण req;
	xfrm_address_t saddr = अणुपूर्ण;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.id));
	req.nh.nlmsg_type	= XFRM_MSG_DELSA;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_seq	= seq;

	स_नकल(&req.id.daddr, &dst, माप(dst));
	req.id.family		= AF_INET;
	req.id.proto		= proto;
	/* Note: zero-spi cannot be deleted */
	req.id.spi = spi;

	स_नकल(&saddr, &src, माप(src));
	अगर (rtattr_pack(&req.nh, माप(req), XFRMA_SRCADDR, &saddr, माप(saddr)))
		वापस -1;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस -1;
	पूर्ण

	वापस netlink_check_answer(xfrm_sock);
पूर्ण

अटल पूर्णांक xfrm_delete(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq,
		काष्ठा in_addr src, काष्ठा in_addr dst,
		काष्ठा in_addr tunsrc, काष्ठा in_addr tundst, uपूर्णांक8_t proto)
अणु
	अगर (xfrm_state_del(xfrm_sock, (*seq)++, gen_spi(src), src, dst, proto)) अणु
		prपूर्णांकk("Failed to remove xfrm state");
		वापस -1;
	पूर्ण

	अगर (xfrm_state_del(xfrm_sock, (*seq)++, gen_spi(src), dst, src, proto)) अणु
		prपूर्णांकk("Failed to remove xfrm state");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_state_allocspi(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq,
		uपूर्णांक32_t spi, uपूर्णांक8_t proto)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr			nh;
		काष्ठा xfrm_userspi_info	spi;
	पूर्ण req;
	काष्ठा अणु
		काष्ठा nlmsghdr			nh;
		जोड़ अणु
			काष्ठा xfrm_usersa_info	info;
			पूर्णांक error;
		पूर्ण;
	पूर्ण answer;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.spi));
	req.nh.nlmsg_type	= XFRM_MSG_ALLOCSPI;
	req.nh.nlmsg_flags	= NLM_F_REQUEST;
	req.nh.nlmsg_seq	= (*seq)++;

	req.spi.info.family	= AF_INET;
	req.spi.min		= spi;
	req.spi.max		= spi;
	req.spi.info.id.proto	= proto;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		वापस KSFT_FAIL;
	पूर्ण

	अगर (recv(xfrm_sock, &answer, माप(answer), 0) < 0) अणु
		pr_err("recv()");
		वापस KSFT_FAIL;
	पूर्ण अन्यथा अगर (answer.nh.nlmsg_type == XFRM_MSG_NEWSA) अणु
		uपूर्णांक32_t new_spi = htonl(answer.info.id.spi);

		अगर (new_spi != spi) अणु
			prपूर्णांकk("allocated spi is different from requested: %#x != %#x",
					new_spi, spi);
			वापस KSFT_FAIL;
		पूर्ण
		वापस KSFT_PASS;
	पूर्ण अन्यथा अगर (answer.nh.nlmsg_type != NLMSG_ERROR) अणु
		prपूर्णांकk("expected NLMSG_ERROR, got %d", (पूर्णांक)answer.nh.nlmsg_type);
		वापस KSFT_FAIL;
	पूर्ण

	prपूर्णांकk("NLMSG_ERROR: %d: %s", answer.error, म_त्रुटि(-answer.error));
	वापस (answer.error) ? KSFT_FAIL : KSFT_PASS;
पूर्ण

अटल पूर्णांक netlink_sock_bind(पूर्णांक *sock, uपूर्णांक32_t *seq, पूर्णांक proto, uपूर्णांक32_t groups)
अणु
	काष्ठा sockaddr_nl snl = अणुपूर्ण;
	socklen_t addr_len;
	पूर्णांक ret = -1;

	snl.nl_family = AF_NETLINK;
	snl.nl_groups = groups;

	अगर (netlink_sock(sock, seq, proto)) अणु
		prपूर्णांकk("Failed to open xfrm netlink socket");
		वापस -1;
	पूर्ण

	अगर (bind(*sock, (काष्ठा sockaddr *)&snl, माप(snl)) < 0) अणु
		pr_err("bind()");
		जाओ out_बंद;
	पूर्ण

	addr_len = माप(snl);
	अगर (माला_लोockname(*sock, (काष्ठा sockaddr *)&snl, &addr_len) < 0) अणु
		pr_err("getsockname()");
		जाओ out_बंद;
	पूर्ण
	अगर (addr_len != माप(snl)) अणु
		prपूर्णांकk("Wrong address length %d", addr_len);
		जाओ out_बंद;
	पूर्ण
	अगर (snl.nl_family != AF_NETLINK) अणु
		prपूर्णांकk("Wrong address family %d", snl.nl_family);
		जाओ out_बंद;
	पूर्ण
	वापस 0;

out_बंद:
	बंद(*sock);
	वापस ret;
पूर्ण

अटल पूर्णांक xfrm_monitor_acquire(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr nh;
		जोड़ अणु
			काष्ठा xfrm_user_acquire acq;
			पूर्णांक error;
		पूर्ण;
		अक्षर attrbuf[MAX_PAYLOAD];
	पूर्ण req;
	काष्ठा xfrm_user_पंचांगpl xfrm_पंचांगpl = अणुपूर्ण;
	पूर्णांक xfrm_listen = -1, ret = KSFT_FAIL;
	uपूर्णांक32_t seq_listen;

	अगर (netlink_sock_bind(&xfrm_listen, &seq_listen, NETLINK_XFRM, XFRMNLGRP_ACQUIRE))
		वापस KSFT_FAIL;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.acq));
	req.nh.nlmsg_type	= XFRM_MSG_ACQUIRE;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_seq	= (*seq)++;

	req.acq.policy.sel.family	= AF_INET;
	req.acq.aalgos	= 0xfeed;
	req.acq.ealgos	= 0xbaad;
	req.acq.calgos	= 0xbabe;

	xfrm_पंचांगpl.family = AF_INET;
	xfrm_पंचांगpl.id.proto = IPPROTO_ESP;
	अगर (rtattr_pack(&req.nh, माप(req), XFRMA_TMPL, &xfrm_पंचांगpl, माप(xfrm_पंचांगpl)))
		जाओ out_बंद;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		जाओ out_बंद;
	पूर्ण

	अगर (recv(xfrm_sock, &req, माप(req), 0) < 0) अणु
		pr_err("recv()");
		जाओ out_बंद;
	पूर्ण अन्यथा अगर (req.nh.nlmsg_type != NLMSG_ERROR) अणु
		prपूर्णांकk("expected NLMSG_ERROR, got %d", (पूर्णांक)req.nh.nlmsg_type);
		जाओ out_बंद;
	पूर्ण

	अगर (req.error) अणु
		prपूर्णांकk("NLMSG_ERROR: %d: %s", req.error, म_त्रुटि(-req.error));
		ret = req.error;
		जाओ out_बंद;
	पूर्ण

	अगर (recv(xfrm_listen, &req, माप(req), 0) < 0) अणु
		pr_err("recv()");
		जाओ out_बंद;
	पूर्ण

	अगर (req.acq.aalgos != 0xfeed || req.acq.ealgos != 0xbaad
			|| req.acq.calgos != 0xbabe) अणु
		prपूर्णांकk("xfrm_user_acquire has changed  %x %x %x",
				req.acq.aalgos, req.acq.ealgos, req.acq.calgos);
		जाओ out_बंद;
	पूर्ण

	ret = KSFT_PASS;
out_बंद:
	बंद(xfrm_listen);
	वापस ret;
पूर्ण

अटल पूर्णांक xfrm_expire_state(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq,
		अचिन्हित पूर्णांक nr, काष्ठा xfrm_desc *desc)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr nh;
		जोड़ अणु
			काष्ठा xfrm_user_expire expire;
			पूर्णांक error;
		पूर्ण;
	पूर्ण req;
	काष्ठा in_addr src, dst;
	पूर्णांक xfrm_listen = -1, ret = KSFT_FAIL;
	uपूर्णांक32_t seq_listen;

	src = inet_makeaddr(INADDR_B, child_ip(nr));
	dst = inet_makeaddr(INADDR_B, grchild_ip(nr));

	अगर (xfrm_state_add(xfrm_sock, (*seq)++, gen_spi(src), src, dst, desc)) अणु
		prपूर्णांकk("Failed to add xfrm state");
		वापस KSFT_FAIL;
	पूर्ण

	अगर (netlink_sock_bind(&xfrm_listen, &seq_listen, NETLINK_XFRM, XFRMNLGRP_EXPIRE))
		वापस KSFT_FAIL;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.expire));
	req.nh.nlmsg_type	= XFRM_MSG_EXPIRE;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_seq	= (*seq)++;

	स_नकल(&req.expire.state.id.daddr, &dst, माप(dst));
	req.expire.state.id.spi		= gen_spi(src);
	req.expire.state.id.proto	= desc->proto;
	req.expire.state.family		= AF_INET;
	req.expire.hard			= 0xff;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		जाओ out_बंद;
	पूर्ण

	अगर (recv(xfrm_sock, &req, माप(req), 0) < 0) अणु
		pr_err("recv()");
		जाओ out_बंद;
	पूर्ण अन्यथा अगर (req.nh.nlmsg_type != NLMSG_ERROR) अणु
		prपूर्णांकk("expected NLMSG_ERROR, got %d", (पूर्णांक)req.nh.nlmsg_type);
		जाओ out_बंद;
	पूर्ण

	अगर (req.error) अणु
		prपूर्णांकk("NLMSG_ERROR: %d: %s", req.error, म_त्रुटि(-req.error));
		ret = req.error;
		जाओ out_बंद;
	पूर्ण

	अगर (recv(xfrm_listen, &req, माप(req), 0) < 0) अणु
		pr_err("recv()");
		जाओ out_बंद;
	पूर्ण

	अगर (req.expire.hard != 0x1) अणु
		prपूर्णांकk("expire.hard is not set: %x", req.expire.hard);
		जाओ out_बंद;
	पूर्ण

	ret = KSFT_PASS;
out_बंद:
	बंद(xfrm_listen);
	वापस ret;
पूर्ण

अटल पूर्णांक xfrm_expire_policy(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq,
		अचिन्हित पूर्णांक nr, काष्ठा xfrm_desc *desc)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr nh;
		जोड़ अणु
			काष्ठा xfrm_user_polexpire expire;
			पूर्णांक error;
		पूर्ण;
	पूर्ण req;
	काष्ठा in_addr src, dst, tunsrc, tundst;
	पूर्णांक xfrm_listen = -1, ret = KSFT_FAIL;
	uपूर्णांक32_t seq_listen;

	src = inet_makeaddr(INADDR_B, child_ip(nr));
	dst = inet_makeaddr(INADDR_B, grchild_ip(nr));
	tunsrc = inet_makeaddr(INADDR_A, child_ip(nr));
	tundst = inet_makeaddr(INADDR_A, grchild_ip(nr));

	अगर (xfrm_policy_add(xfrm_sock, (*seq)++, gen_spi(src), src, dst,
				XFRM_POLICY_OUT, tunsrc, tundst, desc->proto)) अणु
		prपूर्णांकk("Failed to add xfrm policy");
		वापस KSFT_FAIL;
	पूर्ण

	अगर (netlink_sock_bind(&xfrm_listen, &seq_listen, NETLINK_XFRM, XFRMNLGRP_EXPIRE))
		वापस KSFT_FAIL;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len	= NLMSG_LENGTH(माप(req.expire));
	req.nh.nlmsg_type	= XFRM_MSG_POLEXPIRE;
	req.nh.nlmsg_flags	= NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_seq	= (*seq)++;

	/* Fill selector. */
	स_नकल(&req.expire.pol.sel.daddr, &dst, माप(tundst));
	स_नकल(&req.expire.pol.sel.saddr, &src, माप(tunsrc));
	req.expire.pol.sel.family	= AF_INET;
	req.expire.pol.sel.prefixlen_d	= PREFIX_LEN;
	req.expire.pol.sel.prefixlen_s	= PREFIX_LEN;
	req.expire.pol.dir		= XFRM_POLICY_OUT;
	req.expire.hard			= 0xff;

	अगर (send(xfrm_sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		pr_err("send()");
		जाओ out_बंद;
	पूर्ण

	अगर (recv(xfrm_sock, &req, माप(req), 0) < 0) अणु
		pr_err("recv()");
		जाओ out_बंद;
	पूर्ण अन्यथा अगर (req.nh.nlmsg_type != NLMSG_ERROR) अणु
		prपूर्णांकk("expected NLMSG_ERROR, got %d", (पूर्णांक)req.nh.nlmsg_type);
		जाओ out_बंद;
	पूर्ण

	अगर (req.error) अणु
		prपूर्णांकk("NLMSG_ERROR: %d: %s", req.error, म_त्रुटि(-req.error));
		ret = req.error;
		जाओ out_बंद;
	पूर्ण

	अगर (recv(xfrm_listen, &req, माप(req), 0) < 0) अणु
		pr_err("recv()");
		जाओ out_बंद;
	पूर्ण

	अगर (req.expire.hard != 0x1) अणु
		prपूर्णांकk("expire.hard is not set: %x", req.expire.hard);
		जाओ out_बंद;
	पूर्ण

	ret = KSFT_PASS;
out_बंद:
	बंद(xfrm_listen);
	वापस ret;
पूर्ण

अटल पूर्णांक child_serv(पूर्णांक xfrm_sock, uपूर्णांक32_t *seq,
		अचिन्हित पूर्णांक nr, पूर्णांक cmd_fd, व्योम *buf, काष्ठा xfrm_desc *desc)
अणु
	काष्ठा in_addr src, dst, tunsrc, tundst;
	काष्ठा test_desc msg;
	पूर्णांक ret = KSFT_FAIL;

	src = inet_makeaddr(INADDR_B, child_ip(nr));
	dst = inet_makeaddr(INADDR_B, grchild_ip(nr));
	tunsrc = inet_makeaddr(INADDR_A, child_ip(nr));
	tundst = inet_makeaddr(INADDR_A, grchild_ip(nr));

	/* UDP pinging without xfrm */
	अगर (करो_ping(cmd_fd, buf, page_size, src, true, 0, 0, udp_ping_send)) अणु
		prपूर्णांकk("ping failed before setting xfrm");
		वापस KSFT_FAIL;
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	msg.type = MSG_XFRM_PREPARE;
	स_नकल(&msg.body.xfrm_desc, desc, माप(*desc));
	ग_लिखो_msg(cmd_fd, &msg, 1);

	अगर (xfrm_prepare(xfrm_sock, seq, src, dst, tunsrc, tundst, desc->proto)) अणु
		prपूर्णांकk("failed to prepare xfrm");
		जाओ cleanup;
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	msg.type = MSG_XFRM_ADD;
	स_नकल(&msg.body.xfrm_desc, desc, माप(*desc));
	ग_लिखो_msg(cmd_fd, &msg, 1);
	अगर (xfrm_set(xfrm_sock, seq, src, dst, tunsrc, tundst, desc)) अणु
		prपूर्णांकk("failed to set xfrm");
		जाओ delete;
	पूर्ण

	/* UDP pinging with xfrm tunnel */
	अगर (करो_ping(cmd_fd, buf, page_size, tunsrc,
				true, 0, 0, udp_ping_send)) अणु
		prपूर्णांकk("ping failed for xfrm");
		जाओ delete;
	पूर्ण

	ret = KSFT_PASS;
delete:
	/* xfrm delete */
	स_रखो(&msg, 0, माप(msg));
	msg.type = MSG_XFRM_DEL;
	स_नकल(&msg.body.xfrm_desc, desc, माप(*desc));
	ग_लिखो_msg(cmd_fd, &msg, 1);

	अगर (xfrm_delete(xfrm_sock, seq, src, dst, tunsrc, tundst, desc->proto)) अणु
		prपूर्णांकk("failed ping to remove xfrm");
		ret = KSFT_FAIL;
	पूर्ण

cleanup:
	स_रखो(&msg, 0, माप(msg));
	msg.type = MSG_XFRM_CLEANUP;
	स_नकल(&msg.body.xfrm_desc, desc, माप(*desc));
	ग_लिखो_msg(cmd_fd, &msg, 1);
	अगर (xfrm_cleanup(xfrm_sock, seq, src, dst, tunsrc, tundst)) अणु
		prपूर्णांकk("failed ping to cleanup xfrm");
		ret = KSFT_FAIL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक child_f(अचिन्हित पूर्णांक nr, पूर्णांक test_desc_fd, पूर्णांक cmd_fd, व्योम *buf)
अणु
	काष्ठा xfrm_desc desc;
	काष्ठा test_desc msg;
	पूर्णांक xfrm_sock = -1;
	uपूर्णांक32_t seq;

	अगर (चयन_ns(nsfd_childa))
		निकास(KSFT_FAIL);

	अगर (netlink_sock(&xfrm_sock, &seq, NETLINK_XFRM)) अणु
		prपूर्णांकk("Failed to open xfrm netlink socket");
		निकास(KSFT_FAIL);
	पूर्ण

	/* Check that seq sock is पढ़ोy, just क्रम sure. */
	स_रखो(&msg, 0, माप(msg));
	msg.type = MSG_ACK;
	ग_लिखो_msg(cmd_fd, &msg, 1);
	पढ़ो_msg(cmd_fd, &msg, 1);
	अगर (msg.type != MSG_ACK) अणु
		prपूर्णांकk("Ack failed");
		निकास(KSFT_FAIL);
	पूर्ण

	क्रम (;;) अणु
		sमाप_प्रकार received = पढ़ो(test_desc_fd, &desc, माप(desc));
		पूर्णांक ret;

		अगर (received == 0) /* खातापूर्ण */
			अवरोध;

		अगर (received != माप(desc)) अणु
			pr_err("read() returned %zd", received);
			निकास(KSFT_FAIL);
		पूर्ण

		चयन (desc.type) अणु
		हाल CREATE_TUNNEL:
			ret = child_serv(xfrm_sock, &seq, nr,
					 cmd_fd, buf, &desc);
			अवरोध;
		हाल ALLOCATE_SPI:
			ret = xfrm_state_allocspi(xfrm_sock, &seq,
						  -1, desc.proto);
			अवरोध;
		हाल MONITOR_ACQUIRE:
			ret = xfrm_monitor_acquire(xfrm_sock, &seq, nr);
			अवरोध;
		हाल EXPIRE_STATE:
			ret = xfrm_expire_state(xfrm_sock, &seq, nr, &desc);
			अवरोध;
		हाल EXPIRE_POLICY:
			ret = xfrm_expire_policy(xfrm_sock, &seq, nr, &desc);
			अवरोध;
		शेष:
			prपूर्णांकk("Unknown desc type %d", desc.type);
			निकास(KSFT_FAIL);
		पूर्ण
		ग_लिखो_test_result(ret, &desc);
	पूर्ण

	बंद(xfrm_sock);

	msg.type = MSG_EXIT;
	ग_लिखो_msg(cmd_fd, &msg, 1);
	निकास(KSFT_PASS);
पूर्ण

अटल व्योम gअक्रम_child_serv(अचिन्हित पूर्णांक nr, पूर्णांक cmd_fd, व्योम *buf,
		काष्ठा test_desc *msg, पूर्णांक xfrm_sock, uपूर्णांक32_t *seq)
अणु
	काष्ठा in_addr src, dst, tunsrc, tundst;
	bool tun_reply;
	काष्ठा xfrm_desc *desc = &msg->body.xfrm_desc;

	src = inet_makeaddr(INADDR_B, grchild_ip(nr));
	dst = inet_makeaddr(INADDR_B, child_ip(nr));
	tunsrc = inet_makeaddr(INADDR_A, grchild_ip(nr));
	tundst = inet_makeaddr(INADDR_A, child_ip(nr));

	चयन (msg->type) अणु
	हाल MSG_EXIT:
		निकास(KSFT_PASS);
	हाल MSG_ACK:
		ग_लिखो_msg(cmd_fd, msg, 1);
		अवरोध;
	हाल MSG_PING:
		tun_reply = स_भेद(&dst, &msg->body.ping.reply_ip, माप(in_addr_t));
		/* UDP pinging without xfrm */
		अगर (करो_ping(cmd_fd, buf, page_size, tun_reply ? tunsrc : src,
				false, msg->body.ping.port,
				msg->body.ping.reply_ip, udp_ping_reply)) अणु
			prपूर्णांकk("ping failed before setting xfrm");
		पूर्ण
		अवरोध;
	हाल MSG_XFRM_PREPARE:
		अगर (xfrm_prepare(xfrm_sock, seq, src, dst, tunsrc, tundst,
					desc->proto)) अणु
			xfrm_cleanup(xfrm_sock, seq, src, dst, tunsrc, tundst);
			prपूर्णांकk("failed to prepare xfrm");
		पूर्ण
		अवरोध;
	हाल MSG_XFRM_ADD:
		अगर (xfrm_set(xfrm_sock, seq, src, dst, tunsrc, tundst, desc)) अणु
			xfrm_cleanup(xfrm_sock, seq, src, dst, tunsrc, tundst);
			prपूर्णांकk("failed to set xfrm");
		पूर्ण
		अवरोध;
	हाल MSG_XFRM_DEL:
		अगर (xfrm_delete(xfrm_sock, seq, src, dst, tunsrc, tundst,
					desc->proto)) अणु
			xfrm_cleanup(xfrm_sock, seq, src, dst, tunsrc, tundst);
			prपूर्णांकk("failed to remove xfrm");
		पूर्ण
		अवरोध;
	हाल MSG_XFRM_CLEANUP:
		अगर (xfrm_cleanup(xfrm_sock, seq, src, dst, tunsrc, tundst)) अणु
			prपूर्णांकk("failed to cleanup xfrm");
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk("got unknown msg type %d", msg->type);
	पूर्ण
पूर्ण

अटल पूर्णांक gअक्रम_child_f(अचिन्हित पूर्णांक nr, पूर्णांक cmd_fd, व्योम *buf)
अणु
	काष्ठा test_desc msg;
	पूर्णांक xfrm_sock = -1;
	uपूर्णांक32_t seq;

	अगर (चयन_ns(nsfd_childb))
		निकास(KSFT_FAIL);

	अगर (netlink_sock(&xfrm_sock, &seq, NETLINK_XFRM)) अणु
		prपूर्णांकk("Failed to open xfrm netlink socket");
		निकास(KSFT_FAIL);
	पूर्ण

	करो अणु
		पढ़ो_msg(cmd_fd, &msg, 1);
		gअक्रम_child_serv(nr, cmd_fd, buf, &msg, xfrm_sock, &seq);
	पूर्ण जबतक (1);

	बंद(xfrm_sock);
	निकास(KSFT_FAIL);
पूर्ण

अटल पूर्णांक start_child(अचिन्हित पूर्णांक nr, अक्षर *veth, पूर्णांक test_desc_fd[2])
अणु
	पूर्णांक cmd_sock[2];
	व्योम *data_map;
	pid_t child;

	अगर (init_child(nsfd_childa, veth, child_ip(nr), grchild_ip(nr)))
		वापस -1;

	अगर (init_child(nsfd_childb, veth, grchild_ip(nr), child_ip(nr)))
		वापस -1;

	child = विभाजन();
	अगर (child < 0) अणु
		pr_err("fork()");
		वापस -1;
	पूर्ण अन्यथा अगर (child) अणु
		/* in parent - selftest */
		वापस चयन_ns(nsfd_parent);
	पूर्ण

	अगर (बंद(test_desc_fd[1])) अणु
		pr_err("close()");
		वापस -1;
	पूर्ण

	/* child */
	data_map = mmap(0, page_size, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	अगर (data_map == MAP_FAILED) अणु
		pr_err("mmap()");
		वापस -1;
	पूर्ण

	अक्रमomize_buffer(data_map, page_size);

	अगर (socketpair(PF_LOCAL, SOCK_SEQPACKET, 0, cmd_sock)) अणु
		pr_err("socketpair()");
		वापस -1;
	पूर्ण

	child = विभाजन();
	अगर (child < 0) अणु
		pr_err("fork()");
		वापस -1;
	पूर्ण अन्यथा अगर (child) अणु
		अगर (बंद(cmd_sock[0])) अणु
			pr_err("close()");
			वापस -1;
		पूर्ण
		वापस child_f(nr, test_desc_fd[0], cmd_sock[1], data_map);
	पूर्ण
	अगर (बंद(cmd_sock[1])) अणु
		pr_err("close()");
		वापस -1;
	पूर्ण
	वापस gअक्रम_child_f(nr, cmd_sock[0], data_map);
पूर्ण

अटल व्योम निकास_usage(अक्षर **argv)
अणु
	prपूर्णांकk("Usage: %s [nr_process]", argv[0]);
	निकास(KSFT_FAIL);
पूर्ण

अटल पूर्णांक __ग_लिखो_desc(पूर्णांक test_desc_fd, काष्ठा xfrm_desc *desc)
अणु
	sमाप_प्रकार ret;

	ret = ग_लिखो(test_desc_fd, desc, माप(*desc));

	अगर (ret == माप(*desc))
		वापस 0;

	pr_err("Writing test's desc failed %ld", ret);

	वापस -1;
पूर्ण

अटल पूर्णांक ग_लिखो_desc(पूर्णांक proto, पूर्णांक test_desc_fd,
		अक्षर *a, अक्षर *e, अक्षर *c, अक्षर *ae)
अणु
	काष्ठा xfrm_desc desc = अणुपूर्ण;

	desc.type = CREATE_TUNNEL;
	desc.proto = proto;

	अगर (a)
		म_नकलन(desc.a_algo, a, ALGO_LEN - 1);
	अगर (e)
		म_नकलन(desc.e_algo, e, ALGO_LEN - 1);
	अगर (c)
		म_नकलन(desc.c_algo, c, ALGO_LEN - 1);
	अगर (ae)
		म_नकलन(desc.ae_algo, ae, ALGO_LEN - 1);

	वापस __ग_लिखो_desc(test_desc_fd, &desc);
पूर्ण

पूर्णांक proto_list[] = अणु IPPROTO_AH, IPPROTO_COMP, IPPROTO_ESP पूर्ण;
अक्षर *ah_list[] = अणु
	"digest_null", "hmac(md5)", "hmac(sha1)", "hmac(sha256)",
	"hmac(sha384)", "hmac(sha512)", "hmac(rmd160)",
	"xcbc(aes)", "cmac(aes)"
पूर्ण;
अक्षर *comp_list[] = अणु
	"deflate",
#अगर 0
	/* No compression backend realization */
	"lzs", "lzjh"
#पूर्ण_अगर
पूर्ण;
अक्षर *e_list[] = अणु
	"ecb(cipher_null)", "cbc(des)", "cbc(des3_ede)", "cbc(cast5)",
	"cbc(blowfish)", "cbc(aes)", "cbc(serpent)", "cbc(camellia)",
	"cbc(twofish)", "rfc3686(ctr(aes))"
पूर्ण;
अक्षर *ae_list[] = अणु
#अगर 0
	/* not implemented */
	"rfc4106(gcm(aes))", "rfc4309(ccm(aes))", "rfc4543(gcm(aes))",
	"rfc7539esp(chacha20,poly1305)"
#पूर्ण_अगर
पूर्ण;

स्थिर अचिन्हित पूर्णांक proto_plan = ARRAY_SIZE(ah_list) + ARRAY_SIZE(comp_list) \
				+ (ARRAY_SIZE(ah_list) * ARRAY_SIZE(e_list)) \
				+ ARRAY_SIZE(ae_list);

अटल पूर्णांक ग_लिखो_proto_plan(पूर्णांक fd, पूर्णांक proto)
अणु
	अचिन्हित पूर्णांक i;

	चयन (proto) अणु
	हाल IPPROTO_AH:
		क्रम (i = 0; i < ARRAY_SIZE(ah_list); i++) अणु
			अगर (ग_लिखो_desc(proto, fd, ah_list[i], 0, 0, 0))
				वापस -1;
		पूर्ण
		अवरोध;
	हाल IPPROTO_COMP:
		क्रम (i = 0; i < ARRAY_SIZE(comp_list); i++) अणु
			अगर (ग_लिखो_desc(proto, fd, 0, 0, comp_list[i], 0))
				वापस -1;
		पूर्ण
		अवरोध;
	हाल IPPROTO_ESP:
		क्रम (i = 0; i < ARRAY_SIZE(ah_list); i++) अणु
			पूर्णांक j;

			क्रम (j = 0; j < ARRAY_SIZE(e_list); j++) अणु
				अगर (ग_लिखो_desc(proto, fd, ah_list[i],
							e_list[j], 0, 0))
					वापस -1;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(ae_list); i++) अणु
			अगर (ग_लिखो_desc(proto, fd, 0, 0, 0, ae_list[i]))
				वापस -1;
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk("BUG: Specified unknown proto %d", proto);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Some काष्ठाures in xfrm uapi header dअगरfer in size between
 * 64-bit and 32-bit ABI:
 *
 *             32-bit UABI               |            64-bit UABI
 *  -------------------------------------|-------------------------------------
 *   माप(xfrm_usersa_info)     = 220  |  माप(xfrm_usersa_info)     = 224
 *   माप(xfrm_userpolicy_info) = 164  |  माप(xfrm_userpolicy_info) = 168
 *   माप(xfrm_userspi_info)    = 228  |  माप(xfrm_userspi_info)    = 232
 *   माप(xfrm_user_acquire)    = 276  |  माप(xfrm_user_acquire)    = 280
 *   माप(xfrm_user_expire)     = 224  |  माप(xfrm_user_expire)     = 232
 *   माप(xfrm_user_polexpire)  = 168  |  माप(xfrm_user_polexpire)  = 176
 *
 * Check the affected by the UABI dअगरference काष्ठाures.
 */
स्थिर अचिन्हित पूर्णांक compat_plan = 4;
अटल पूर्णांक ग_लिखो_compat_काष्ठा_tests(पूर्णांक test_desc_fd)
अणु
	काष्ठा xfrm_desc desc = अणुपूर्ण;

	desc.type = ALLOCATE_SPI;
	desc.proto = IPPROTO_AH;
	म_नकलन(desc.a_algo, ah_list[0], ALGO_LEN - 1);

	अगर (__ग_लिखो_desc(test_desc_fd, &desc))
		वापस -1;

	desc.type = MONITOR_ACQUIRE;
	अगर (__ग_लिखो_desc(test_desc_fd, &desc))
		वापस -1;

	desc.type = EXPIRE_STATE;
	अगर (__ग_लिखो_desc(test_desc_fd, &desc))
		वापस -1;

	desc.type = EXPIRE_POLICY;
	अगर (__ग_लिखो_desc(test_desc_fd, &desc))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_test_plan(पूर्णांक test_desc_fd)
अणु
	अचिन्हित पूर्णांक i;
	pid_t child;

	child = विभाजन();
	अगर (child < 0) अणु
		pr_err("fork()");
		वापस -1;
	पूर्ण
	अगर (child) अणु
		अगर (बंद(test_desc_fd))
			prपूर्णांकk("close(): %m");
		वापस 0;
	पूर्ण

	अगर (ग_लिखो_compat_काष्ठा_tests(test_desc_fd))
		निकास(KSFT_FAIL);

	क्रम (i = 0; i < ARRAY_SIZE(proto_list); i++) अणु
		अगर (ग_लिखो_proto_plan(test_desc_fd, proto_list[i]))
			निकास(KSFT_FAIL);
	पूर्ण

	निकास(KSFT_PASS);
पूर्ण

अटल पूर्णांक children_cleanup(व्योम)
अणु
	अचिन्हित ret = KSFT_PASS;

	जबतक (1) अणु
		पूर्णांक status;
		pid_t p = रुको(&status);

		अगर ((p < 0) && त्रुटि_सं == ECHILD)
			अवरोध;

		अगर (p < 0) अणु
			pr_err("wait()");
			वापस KSFT_FAIL;
		पूर्ण

		अगर (!WIFEXITED(status)) अणु
			ret = KSFT_FAIL;
			जारी;
		पूर्ण

		अगर (WEXITSTATUS(status) == KSFT_FAIL)
			ret = KSFT_FAIL;
	पूर्ण

	वापस ret;
पूर्ण

प्रकार व्योम (*prपूर्णांक_res)(स्थिर अक्षर *, ...);

अटल पूर्णांक check_results(व्योम)
अणु
	काष्ठा test_result tr = अणुपूर्ण;
	काष्ठा xfrm_desc *d = &tr.desc;
	पूर्णांक ret = KSFT_PASS;

	जबतक (1) अणु
		sमाप_प्रकार received = पढ़ो(results_fd[0], &tr, माप(tr));
		prपूर्णांक_res result;

		अगर (received == 0) /* खातापूर्ण */
			अवरोध;

		अगर (received != माप(tr)) अणु
			pr_err("read() returned %zd", received);
			वापस KSFT_FAIL;
		पूर्ण

		चयन (tr.res) अणु
		हाल KSFT_PASS:
			result = ksft_test_result_pass;
			अवरोध;
		हाल KSFT_FAIL:
		शेष:
			result = ksft_test_result_fail;
			ret = KSFT_FAIL;
		पूर्ण

		result(" %s: [%u, '%s', '%s', '%s', '%s', %u]\n",
		       desc_name[d->type], (अचिन्हित पूर्णांक)d->proto, d->a_algo,
		       d->e_algo, d->c_algo, d->ae_algo, d->icv_len);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक nr_process = 1;
	पूर्णांक route_sock = -1, ret = KSFT_SKIP;
	पूर्णांक test_desc_fd[2];
	uपूर्णांक32_t route_seq;
	अचिन्हित पूर्णांक i;

	अगर (argc > 2)
		निकास_usage(argv);

	अगर (argc > 1) अणु
		अक्षर *endptr;

		त्रुटि_सं = 0;
		nr_process = म_से_दीर्घ(argv[1], &endptr, 10);
		अगर ((त्रुटि_सं == दुस्फल && (nr_process == दीर्घ_उच्च || nr_process == दीर्घ_न्यून))
				|| (त्रुटि_सं != 0 && nr_process == 0)
				|| (endptr == argv[1]) || (*endptr != '\0')) अणु
			prपूर्णांकk("Failed to parse [nr_process]");
			निकास_usage(argv);
		पूर्ण

		अगर (nr_process > MAX_PROCESSES || !nr_process) अणु
			prपूर्णांकk("nr_process should be between [1; %u]",
					MAX_PROCESSES);
			निकास_usage(argv);
		पूर्ण
	पूर्ण

	बेक्रम(समय(शून्य));
	page_size = sysconf(_SC_PAGESIZE);
	अगर (page_size < 1)
		ksft_निकास_skip("sysconf(): %m\n");

	अगर (pipe2(test_desc_fd, O_सूचीECT) < 0)
		ksft_निकास_skip("pipe(): %m\n");

	अगर (pipe2(results_fd, O_सूचीECT) < 0)
		ksft_निकास_skip("pipe(): %m\n");

	अगर (init_namespaces())
		ksft_निकास_skip("Failed to create namespaces\n");

	अगर (netlink_sock(&route_sock, &route_seq, NETLINK_ROUTE))
		ksft_निकास_skip("Failed to open netlink route socket\n");

	क्रम (i = 0; i < nr_process; i++) अणु
		अक्षर veth[VETH_LEN];

		snम_लिखो(veth, VETH_LEN, VETH_FMT, i);

		अगर (veth_add(route_sock, route_seq++, veth, nsfd_childa, veth, nsfd_childb)) अणु
			बंद(route_sock);
			ksft_निकास_fail_msg("Failed to create veth device");
		पूर्ण

		अगर (start_child(i, veth, test_desc_fd)) अणु
			बंद(route_sock);
			ksft_निकास_fail_msg("Child %u failed to start", i);
		पूर्ण
	पूर्ण

	अगर (बंद(route_sock) || बंद(test_desc_fd[0]) || बंद(results_fd[1]))
		ksft_निकास_fail_msg("close(): %m");

	ksft_set_plan(proto_plan + compat_plan);

	अगर (ग_लिखो_test_plan(test_desc_fd[1]))
		ksft_निकास_fail_msg("Failed to write test plan to pipe");

	ret = check_results();

	अगर (children_cleanup() == KSFT_FAIL)
		निकास(KSFT_FAIL);

	निकास(ret);
पूर्ण
