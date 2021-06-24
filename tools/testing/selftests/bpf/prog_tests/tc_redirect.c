<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause

/*
 * This test sets up 3 netns (src <-> fwd <-> dst). There is no direct veth link
 * between src and dst. The netns fwd has veth links to each src and dst. The
 * client is in src and server in dst. The test installs a TC BPF program to each
 * host facing veth in fwd which calls पूर्णांकo i) bpf_redirect_neigh() to perक्रमm the
 * neigh addr population and redirect or ii) bpf_redirect_peer() क्रम namespace
 * चयन from ingress side; it also installs a checker prog on the egress side
 * to drop unexpected traffic.
 */

#घोषणा _GNU_SOURCE

#समावेश <arpa/inet.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/अगर_tun.h>
#समावेश <linux/अगर.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mount.h>

#समावेश "test_progs.h"
#समावेश "network_helpers.h"
#समावेश "test_tc_neigh_fib.skel.h"
#समावेश "test_tc_neigh.skel.h"
#समावेश "test_tc_peer.skel.h"

#घोषणा NS_SRC "ns_src"
#घोषणा NS_FWD "ns_fwd"
#घोषणा NS_DST "ns_dst"

#घोषणा IP4_SRC "172.16.1.100"
#घोषणा IP4_DST "172.16.2.100"
#घोषणा IP4_TUN_SRC "172.17.1.100"
#घोषणा IP4_TUN_FWD "172.17.1.200"
#घोषणा IP4_PORT 9004

#घोषणा IP6_SRC "0::1:dead:beef:cafe"
#घोषणा IP6_DST "0::2:dead:beef:cafe"
#घोषणा IP6_TUN_SRC "1::1:dead:beef:cafe"
#घोषणा IP6_TUN_FWD "1::2:dead:beef:cafe"
#घोषणा IP6_PORT 9006

#घोषणा IP4_SLL "169.254.0.1"
#घोषणा IP4_DLL "169.254.0.2"
#घोषणा IP4_NET "169.254.0.0"

#घोषणा MAC_DST_FWD "00:11:22:33:44:55"
#घोषणा MAC_DST "00:22:33:44:55:66"

#घोषणा IFADDR_STR_LEN 18
#घोषणा PING_ARGS "-i 0.2 -c 3 -w 10 -q"

#घोषणा SRC_PROG_PIN_खाता "/sys/fs/bpf/test_tc_src"
#घोषणा DST_PROG_PIN_खाता "/sys/fs/bpf/test_tc_dst"
#घोषणा CHK_PROG_PIN_खाता "/sys/fs/bpf/test_tc_chk"

#घोषणा TIMEOUT_MILLIS 10000

#घोषणा log_err(MSG, ...) \
	ख_लिखो(मानक_त्रुटि, "(%s:%d: errno: %s) " MSG "\n", \
		__खाता__, __LINE__, म_त्रुटि(त्रुटि_सं), ##__VA_ARGS__)

अटल स्थिर अक्षर * स्थिर namespaces[] = अणुNS_SRC, NS_FWD, NS_DST, शून्यपूर्ण;

अटल पूर्णांक ग_लिखो_file(स्थिर अक्षर *path, स्थिर अक्षर *newval)
अणु
	खाता *f;

	f = ख_खोलो(path, "r+");
	अगर (!f)
		वापस -1;
	अगर (ख_डालो(newval, म_माप(newval), 1, f) != 1) अणु
		log_err("writing to %s failed", path);
		ख_बंद(f);
		वापस -1;
	पूर्ण
	ख_बंद(f);
	वापस 0;
पूर्ण

काष्ठा nstoken अणु
	पूर्णांक orig_netns_fd;
पूर्ण;

अटल पूर्णांक setns_by_fd(पूर्णांक nsfd)
अणु
	पूर्णांक err;

	err = setns(nsfd, CLONE_NEWNET);
	बंद(nsfd);

	अगर (!ASSERT_OK(err, "setns"))
		वापस err;

	/* Switch /sys to the new namespace so that e.g. /sys/class/net
	 * reflects the devices in the new namespace.
	 */
	err = unshare(CLONE_NEWNS);
	अगर (!ASSERT_OK(err, "unshare"))
		वापस err;

	err = umount2("/sys", MNT_DETACH);
	अगर (!ASSERT_OK(err, "umount2 /sys"))
		वापस err;

	err = mount("sysfs", "/sys", "sysfs", 0, शून्य);
	अगर (!ASSERT_OK(err, "mount /sys"))
		वापस err;

	err = mount("bpffs", "/sys/fs/bpf", "bpf", 0, शून्य);
	अगर (!ASSERT_OK(err, "mount /sys/fs/bpf"))
		वापस err;

	वापस 0;
पूर्ण

/**
 * खोलो_netns() - Switch to specअगरied network namespace by name.
 *
 * Returns token with which to restore the original namespace
 * using बंद_netns().
 */
अटल काष्ठा nstoken *खोलो_netns(स्थिर अक्षर *name)
अणु
	पूर्णांक nsfd;
	अक्षर nspath[PATH_MAX];
	पूर्णांक err;
	काष्ठा nstoken *token;

	token = दो_स्मृति(माप(काष्ठा nstoken));
	अगर (!ASSERT_OK_PTR(token, "malloc token"))
		वापस शून्य;

	token->orig_netns_fd = खोलो("/proc/self/ns/net", O_RDONLY);
	अगर (!ASSERT_GE(token->orig_netns_fd, 0, "open /proc/self/ns/net"))
		जाओ fail;

	snम_लिखो(nspath, माप(nspath), "%s/%s", "/var/run/netns", name);
	nsfd = खोलो(nspath, O_RDONLY | O_CLOEXEC);
	अगर (!ASSERT_GE(nsfd, 0, "open netns fd"))
		जाओ fail;

	err = setns_by_fd(nsfd);
	अगर (!ASSERT_OK(err, "setns_by_fd"))
		जाओ fail;

	वापस token;
fail:
	मुक्त(token);
	वापस शून्य;
पूर्ण

अटल व्योम बंद_netns(काष्ठा nstoken *token)
अणु
	ASSERT_OK(setns_by_fd(token->orig_netns_fd), "setns_by_fd");
	मुक्त(token);
पूर्ण

अटल पूर्णांक netns_setup_namespaces(स्थिर अक्षर *verb)
अणु
	स्थिर अक्षर * स्थिर *ns = namespaces;
	अक्षर cmd[128];

	जबतक (*ns) अणु
		snम_लिखो(cmd, माप(cmd), "ip netns %s %s", verb, *ns);
		अगर (!ASSERT_OK(प्रणाली(cmd), cmd))
			वापस -1;
		ns++;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा netns_setup_result अणु
	पूर्णांक अगरindex_veth_src_fwd;
	पूर्णांक अगरindex_veth_dst_fwd;
पूर्ण;

अटल पूर्णांक get_अगरaddr(स्थिर अक्षर *name, अक्षर *अगरaddr)
अणु
	अक्षर path[PATH_MAX];
	खाता *f;
	पूर्णांक ret;

	snम_लिखो(path, PATH_MAX, "/sys/class/net/%s/address", name);
	f = ख_खोलो(path, "r");
	अगर (!ASSERT_OK_PTR(f, path))
		वापस -1;

	ret = ख_पढ़ो(अगरaddr, 1, IFADDR_STR_LEN, f);
	अगर (!ASSERT_EQ(ret, IFADDR_STR_LEN, "fread ifaddr")) अणु
		ख_बंद(f);
		वापस -1;
	पूर्ण
	ख_बंद(f);
	वापस 0;
पूर्ण

अटल पूर्णांक get_अगरindex(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	अक्षर buf[32];
	खाता *f;
	पूर्णांक ret;

	snम_लिखो(path, PATH_MAX, "/sys/class/net/%s/ifindex", name);
	f = ख_खोलो(path, "r");
	अगर (!ASSERT_OK_PTR(f, path))
		वापस -1;

	ret = ख_पढ़ो(buf, 1, माप(buf), f);
	अगर (!ASSERT_GT(ret, 0, "fread ifindex")) अणु
		ख_बंद(f);
		वापस -1;
	पूर्ण
	ख_बंद(f);
	वापस म_से_प(buf);
पूर्ण

#घोषणा SYS(fmt, ...)						\
	(अणु							\
		अक्षर cmd[1024];					\
		snम_लिखो(cmd, माप(cmd), fmt, ##__VA_ARGS__);	\
		अगर (!ASSERT_OK(प्रणाली(cmd), cmd))		\
			जाओ fail;				\
	पूर्ण)

अटल पूर्णांक netns_setup_links_and_routes(काष्ठा netns_setup_result *result)
अणु
	काष्ठा nstoken *nstoken = शून्य;
	अक्षर veth_src_fwd_addr[IFADDR_STR_LEN+1] = अणुपूर्ण;

	SYS("ip link add veth_src type veth peer name veth_src_fwd");
	SYS("ip link add veth_dst type veth peer name veth_dst_fwd");

	SYS("ip link set veth_dst_fwd address " MAC_DST_FWD);
	SYS("ip link set veth_dst address " MAC_DST);

	अगर (get_अगरaddr("veth_src_fwd", veth_src_fwd_addr))
		जाओ fail;

	result->अगरindex_veth_src_fwd = get_अगरindex("veth_src_fwd");
	अगर (result->अगरindex_veth_src_fwd < 0)
		जाओ fail;
	result->अगरindex_veth_dst_fwd = get_अगरindex("veth_dst_fwd");
	अगर (result->अगरindex_veth_dst_fwd < 0)
		जाओ fail;

	SYS("ip link set veth_src netns " NS_SRC);
	SYS("ip link set veth_src_fwd netns " NS_FWD);
	SYS("ip link set veth_dst_fwd netns " NS_FWD);
	SYS("ip link set veth_dst netns " NS_DST);

	/** setup in 'src' namespace */
	nstoken = खोलो_netns(NS_SRC);
	अगर (!ASSERT_OK_PTR(nstoken, "setns src"))
		जाओ fail;

	SYS("ip addr add " IP4_SRC "/32 dev veth_src");
	SYS("ip addr add " IP6_SRC "/128 dev veth_src nodad");
	SYS("ip link set dev veth_src up");

	SYS("ip route add " IP4_DST "/32 dev veth_src scope global");
	SYS("ip route add " IP4_NET "/16 dev veth_src scope global");
	SYS("ip route add " IP6_DST "/128 dev veth_src scope global");

	SYS("ip neigh add " IP4_DST " dev veth_src lladdr %s",
	    veth_src_fwd_addr);
	SYS("ip neigh add " IP6_DST " dev veth_src lladdr %s",
	    veth_src_fwd_addr);

	बंद_netns(nstoken);

	/** setup in 'fwd' namespace */
	nstoken = खोलो_netns(NS_FWD);
	अगर (!ASSERT_OK_PTR(nstoken, "setns fwd"))
		जाओ fail;

	/* The fwd netns स्वतःmatically माला_लो a v6 LL address / routes, but also
	 * needs v4 one in order to start ARP probing. IP4_NET route is added
	 * to the endpoपूर्णांकs so that the ARP processing will reply.
	 */
	SYS("ip addr add " IP4_SLL "/32 dev veth_src_fwd");
	SYS("ip addr add " IP4_DLL "/32 dev veth_dst_fwd");
	SYS("ip link set dev veth_src_fwd up");
	SYS("ip link set dev veth_dst_fwd up");

	SYS("ip route add " IP4_SRC "/32 dev veth_src_fwd scope global");
	SYS("ip route add " IP6_SRC "/128 dev veth_src_fwd scope global");
	SYS("ip route add " IP4_DST "/32 dev veth_dst_fwd scope global");
	SYS("ip route add " IP6_DST "/128 dev veth_dst_fwd scope global");

	बंद_netns(nstoken);

	/** setup in 'dst' namespace */
	nstoken = खोलो_netns(NS_DST);
	अगर (!ASSERT_OK_PTR(nstoken, "setns dst"))
		जाओ fail;

	SYS("ip addr add " IP4_DST "/32 dev veth_dst");
	SYS("ip addr add " IP6_DST "/128 dev veth_dst nodad");
	SYS("ip link set dev veth_dst up");

	SYS("ip route add " IP4_SRC "/32 dev veth_dst scope global");
	SYS("ip route add " IP4_NET "/16 dev veth_dst scope global");
	SYS("ip route add " IP6_SRC "/128 dev veth_dst scope global");

	SYS("ip neigh add " IP4_SRC " dev veth_dst lladdr " MAC_DST_FWD);
	SYS("ip neigh add " IP6_SRC " dev veth_dst lladdr " MAC_DST_FWD);

	बंद_netns(nstoken);

	वापस 0;
fail:
	अगर (nstoken)
		बंद_netns(nstoken);
	वापस -1;
पूर्ण

अटल पूर्णांक netns_load_bpf(व्योम)
अणु
	SYS("tc qdisc add dev veth_src_fwd clsact");
	SYS("tc filter add dev veth_src_fwd ingress bpf da object-pinned "
	    SRC_PROG_PIN_खाता);
	SYS("tc filter add dev veth_src_fwd egress bpf da object-pinned "
	    CHK_PROG_PIN_खाता);

	SYS("tc qdisc add dev veth_dst_fwd clsact");
	SYS("tc filter add dev veth_dst_fwd ingress bpf da object-pinned "
	    DST_PROG_PIN_खाता);
	SYS("tc filter add dev veth_dst_fwd egress bpf da object-pinned "
	    CHK_PROG_PIN_खाता);

	वापस 0;
fail:
	वापस -1;
पूर्ण

अटल व्योम test_tcp(पूर्णांक family, स्थिर अक्षर *addr, __u16 port)
अणु
	पूर्णांक listen_fd = -1, accept_fd = -1, client_fd = -1;
	अक्षर buf[] = "testing testing";
	पूर्णांक n;
	काष्ठा nstoken *nstoken;

	nstoken = खोलो_netns(NS_DST);
	अगर (!ASSERT_OK_PTR(nstoken, "setns dst"))
		वापस;

	listen_fd = start_server(family, SOCK_STREAM, addr, port, 0);
	अगर (!ASSERT_GE(listen_fd, 0, "listen"))
		जाओ करोne;

	बंद_netns(nstoken);
	nstoken = खोलो_netns(NS_SRC);
	अगर (!ASSERT_OK_PTR(nstoken, "setns src"))
		जाओ करोne;

	client_fd = connect_to_fd(listen_fd, TIMEOUT_MILLIS);
	अगर (!ASSERT_GE(client_fd, 0, "connect_to_fd"))
		जाओ करोne;

	accept_fd = accept(listen_fd, शून्य, शून्य);
	अगर (!ASSERT_GE(accept_fd, 0, "accept"))
		जाओ करोne;

	अगर (!ASSERT_OK(समय_रखोo(accept_fd, TIMEOUT_MILLIS), "settimeo"))
		जाओ करोne;

	n = ग_लिखो(client_fd, buf, माप(buf));
	अगर (!ASSERT_EQ(n, माप(buf), "send to server"))
		जाओ करोne;

	n = पढ़ो(accept_fd, buf, माप(buf));
	ASSERT_EQ(n, माप(buf), "recv from server");

करोne:
	अगर (nstoken)
		बंद_netns(nstoken);
	अगर (listen_fd >= 0)
		बंद(listen_fd);
	अगर (accept_fd >= 0)
		बंद(accept_fd);
	अगर (client_fd >= 0)
		बंद(client_fd);
पूर्ण

अटल पूर्णांक test_ping(पूर्णांक family, स्थिर अक्षर *addr)
अणु
	स्थिर अक्षर *ping = family == AF_INET6 ? "ping6" : "ping";

	SYS("ip netns exec " NS_SRC " %s " PING_ARGS " %s > /dev/null", ping, addr);
	वापस 0;
fail:
	वापस -1;
पूर्ण

अटल व्योम test_connectivity(व्योम)
अणु
	test_tcp(AF_INET, IP4_DST, IP4_PORT);
	test_ping(AF_INET, IP4_DST);
	test_tcp(AF_INET6, IP6_DST, IP6_PORT);
	test_ping(AF_INET6, IP6_DST);
पूर्ण

अटल पूर्णांक set_क्रमwarding(bool enable)
अणु
	पूर्णांक err;

	err = ग_लिखो_file("/proc/sys/net/ipv4/ip_forward", enable ? "1" : "0");
	अगर (!ASSERT_OK(err, "set ipv4.ip_forward=0"))
		वापस err;

	err = ग_लिखो_file("/proc/sys/net/ipv6/conf/all/forwarding", enable ? "1" : "0");
	अगर (!ASSERT_OK(err, "set ipv6.forwarding=0"))
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम test_tc_redirect_neigh_fib(काष्ठा netns_setup_result *setup_result)
अणु
	काष्ठा nstoken *nstoken = शून्य;
	काष्ठा test_tc_neigh_fib *skel = शून्य;
	पूर्णांक err;

	nstoken = खोलो_netns(NS_FWD);
	अगर (!ASSERT_OK_PTR(nstoken, "setns fwd"))
		वापस;

	skel = test_tc_neigh_fib__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "test_tc_neigh_fib__open"))
		जाओ करोne;

	अगर (!ASSERT_OK(test_tc_neigh_fib__load(skel), "test_tc_neigh_fib__load"))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_src, SRC_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " SRC_PROG_PIN_खाता))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_chk, CHK_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " CHK_PROG_PIN_खाता))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_dst, DST_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " DST_PROG_PIN_खाता))
		जाओ करोne;

	अगर (netns_load_bpf())
		जाओ करोne;

	/* bpf_fib_lookup() checks अगर क्रमwarding is enabled */
	अगर (!ASSERT_OK(set_क्रमwarding(true), "enable forwarding"))
		जाओ करोne;

	test_connectivity();

करोne:
	अगर (skel)
		test_tc_neigh_fib__destroy(skel);
	बंद_netns(nstoken);
पूर्ण

अटल व्योम test_tc_redirect_neigh(काष्ठा netns_setup_result *setup_result)
अणु
	काष्ठा nstoken *nstoken = शून्य;
	काष्ठा test_tc_neigh *skel = शून्य;
	पूर्णांक err;

	nstoken = खोलो_netns(NS_FWD);
	अगर (!ASSERT_OK_PTR(nstoken, "setns fwd"))
		वापस;

	skel = test_tc_neigh__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "test_tc_neigh__open"))
		जाओ करोne;

	skel->rodata->IFINDEX_SRC = setup_result->अगरindex_veth_src_fwd;
	skel->rodata->IFINDEX_DST = setup_result->अगरindex_veth_dst_fwd;

	err = test_tc_neigh__load(skel);
	अगर (!ASSERT_OK(err, "test_tc_neigh__load"))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_src, SRC_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " SRC_PROG_PIN_खाता))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_chk, CHK_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " CHK_PROG_PIN_खाता))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_dst, DST_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " DST_PROG_PIN_खाता))
		जाओ करोne;

	अगर (netns_load_bpf())
		जाओ करोne;

	अगर (!ASSERT_OK(set_क्रमwarding(false), "disable forwarding"))
		जाओ करोne;

	test_connectivity();

करोne:
	अगर (skel)
		test_tc_neigh__destroy(skel);
	बंद_netns(nstoken);
पूर्ण

अटल व्योम test_tc_redirect_peer(काष्ठा netns_setup_result *setup_result)
अणु
	काष्ठा nstoken *nstoken;
	काष्ठा test_tc_peer *skel;
	पूर्णांक err;

	nstoken = खोलो_netns(NS_FWD);
	अगर (!ASSERT_OK_PTR(nstoken, "setns fwd"))
		वापस;

	skel = test_tc_peer__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "test_tc_peer__open"))
		जाओ करोne;

	skel->rodata->IFINDEX_SRC = setup_result->अगरindex_veth_src_fwd;
	skel->rodata->IFINDEX_DST = setup_result->अगरindex_veth_dst_fwd;

	err = test_tc_peer__load(skel);
	अगर (!ASSERT_OK(err, "test_tc_peer__load"))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_src, SRC_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " SRC_PROG_PIN_खाता))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_chk, CHK_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " CHK_PROG_PIN_खाता))
		जाओ करोne;

	err = bpf_program__pin(skel->progs.tc_dst, DST_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " DST_PROG_PIN_खाता))
		जाओ करोne;

	अगर (netns_load_bpf())
		जाओ करोne;

	अगर (!ASSERT_OK(set_क्रमwarding(false), "disable forwarding"))
		जाओ करोne;

	test_connectivity();

करोne:
	अगर (skel)
		test_tc_peer__destroy(skel);
	बंद_netns(nstoken);
पूर्ण

अटल पूर्णांक tun_खोलो(अक्षर *name)
अणु
	काष्ठा अगरreq अगरr;
	पूर्णांक fd, err;

	fd = खोलो("/dev/net/tun", O_RDWR);
	अगर (!ASSERT_GE(fd, 0, "open /dev/net/tun"))
		वापस -1;

	स_रखो(&अगरr, 0, माप(अगरr));

	अगरr.अगरr_flags = IFF_TUN | IFF_NO_PI;
	अगर (*name)
		म_नकलन(अगरr.अगरr_name, name, IFNAMSIZ);

	err = ioctl(fd, TUNSETIFF, &अगरr);
	अगर (!ASSERT_OK(err, "ioctl TUNSETIFF"))
		जाओ fail;

	SYS("ip link set dev %s up", name);

	वापस fd;
fail:
	बंद(fd);
	वापस -1;
पूर्ण

#घोषणा MAX(a, b) ((a) > (b) ? (a) : (b))
क्रमागत अणु
	SRC_TO_TARGET = 0,
	TARGET_TO_SRC = 1,
पूर्ण;

अटल पूर्णांक tun_relay_loop(पूर्णांक src_fd, पूर्णांक target_fd)
अणु
	fd_set rfds, wfds;

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);

	क्रम (;;) अणु
		अक्षर buf[1500];
		पूर्णांक direction, nपढ़ो, nग_लिखो;

		FD_SET(src_fd, &rfds);
		FD_SET(target_fd, &rfds);

		अगर (select(1 + MAX(src_fd, target_fd), &rfds, शून्य, शून्य, शून्य) < 0) अणु
			log_err("select failed");
			वापस 1;
		पूर्ण

		direction = FD_ISSET(src_fd, &rfds) ? SRC_TO_TARGET : TARGET_TO_SRC;

		nपढ़ो = पढ़ो(direction == SRC_TO_TARGET ? src_fd : target_fd, buf, माप(buf));
		अगर (nपढ़ो < 0) अणु
			log_err("read failed");
			वापस 1;
		पूर्ण

		nग_लिखो = ग_लिखो(direction == SRC_TO_TARGET ? target_fd : src_fd, buf, nपढ़ो);
		अगर (nग_लिखो != nपढ़ो) अणु
			log_err("write failed");
			वापस 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम test_tc_redirect_peer_l3(काष्ठा netns_setup_result *setup_result)
अणु
	काष्ठा test_tc_peer *skel = शून्य;
	काष्ठा nstoken *nstoken = शून्य;
	पूर्णांक err;
	पूर्णांक tunnel_pid = -1;
	पूर्णांक src_fd, target_fd;
	पूर्णांक अगरindex;

	/* Start a L3 TUN/TAP tunnel between the src and dst namespaces.
	 * This test is using TUN/TAP instead of e.g. IPIP or GRE tunnel as those
	 * expose the L2 headers encapsulating the IP packet to BPF and hence
	 * करोn't have skb in suitable state क्रम this test. Alternative to TUN/TAP
	 * would be e.g. Wireguard which would appear as a pure L3 device to BPF,
	 * but that requires much more complicated setup.
	 */
	nstoken = खोलो_netns(NS_SRC);
	अगर (!ASSERT_OK_PTR(nstoken, "setns " NS_SRC))
		वापस;

	src_fd = tun_खोलो("tun_src");
	अगर (!ASSERT_GE(src_fd, 0, "tun_open tun_src"))
		जाओ fail;

	बंद_netns(nstoken);

	nstoken = खोलो_netns(NS_FWD);
	अगर (!ASSERT_OK_PTR(nstoken, "setns " NS_FWD))
		जाओ fail;

	target_fd = tun_खोलो("tun_fwd");
	अगर (!ASSERT_GE(target_fd, 0, "tun_open tun_fwd"))
		जाओ fail;

	tunnel_pid = विभाजन();
	अगर (!ASSERT_GE(tunnel_pid, 0, "fork tun_relay_loop"))
		जाओ fail;

	अगर (tunnel_pid == 0)
		निकास(tun_relay_loop(src_fd, target_fd));

	skel = test_tc_peer__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "test_tc_peer__open"))
		जाओ fail;

	अगरindex = get_अगरindex("tun_fwd");
	अगर (!ASSERT_GE(अगरindex, 0, "get_ifindex tun_fwd"))
		जाओ fail;

	skel->rodata->IFINDEX_SRC = अगरindex;
	skel->rodata->IFINDEX_DST = setup_result->अगरindex_veth_dst_fwd;

	err = test_tc_peer__load(skel);
	अगर (!ASSERT_OK(err, "test_tc_peer__load"))
		जाओ fail;

	err = bpf_program__pin(skel->progs.tc_src_l3, SRC_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " SRC_PROG_PIN_खाता))
		जाओ fail;

	err = bpf_program__pin(skel->progs.tc_dst_l3, DST_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " DST_PROG_PIN_खाता))
		जाओ fail;

	err = bpf_program__pin(skel->progs.tc_chk, CHK_PROG_PIN_खाता);
	अगर (!ASSERT_OK(err, "pin " CHK_PROG_PIN_खाता))
		जाओ fail;

	/* Load "tc_src_l3" to the tun_fwd पूर्णांकerface to redirect packets
	 * towards dst, and "tc_dst" to redirect packets
	 * and "tc_chk" on veth_dst_fwd to drop non-redirected packets.
	 */
	SYS("tc qdisc add dev tun_fwd clsact");
	SYS("tc filter add dev tun_fwd ingress bpf da object-pinned "
	    SRC_PROG_PIN_खाता);

	SYS("tc qdisc add dev veth_dst_fwd clsact");
	SYS("tc filter add dev veth_dst_fwd ingress bpf da object-pinned "
	    DST_PROG_PIN_खाता);
	SYS("tc filter add dev veth_dst_fwd egress bpf da object-pinned "
	    CHK_PROG_PIN_खाता);

	/* Setup route and neigh tables */
	SYS("ip -netns " NS_SRC " addr add dev tun_src " IP4_TUN_SRC "/24");
	SYS("ip -netns " NS_FWD " addr add dev tun_fwd " IP4_TUN_FWD "/24");

	SYS("ip -netns " NS_SRC " addr add dev tun_src " IP6_TUN_SRC "/64 nodad");
	SYS("ip -netns " NS_FWD " addr add dev tun_fwd " IP6_TUN_FWD "/64 nodad");

	SYS("ip -netns " NS_SRC " route del " IP4_DST "/32 dev veth_src scope global");
	SYS("ip -netns " NS_SRC " route add " IP4_DST "/32 via " IP4_TUN_FWD
	    " dev tun_src scope global");
	SYS("ip -netns " NS_DST " route add " IP4_TUN_SRC "/32 dev veth_dst scope global");
	SYS("ip -netns " NS_SRC " route del " IP6_DST "/128 dev veth_src scope global");
	SYS("ip -netns " NS_SRC " route add " IP6_DST "/128 via " IP6_TUN_FWD
	    " dev tun_src scope global");
	SYS("ip -netns " NS_DST " route add " IP6_TUN_SRC "/128 dev veth_dst scope global");

	SYS("ip -netns " NS_DST " neigh add " IP4_TUN_SRC " dev veth_dst lladdr " MAC_DST_FWD);
	SYS("ip -netns " NS_DST " neigh add " IP6_TUN_SRC " dev veth_dst lladdr " MAC_DST_FWD);

	अगर (!ASSERT_OK(set_क्रमwarding(false), "disable forwarding"))
		जाओ fail;

	test_connectivity();

fail:
	अगर (tunnel_pid > 0) अणु
		समाप्त(tunnel_pid, संक_इति);
		रुकोpid(tunnel_pid, शून्य, 0);
	पूर्ण
	अगर (src_fd >= 0)
		बंद(src_fd);
	अगर (target_fd >= 0)
		बंद(target_fd);
	अगर (skel)
		test_tc_peer__destroy(skel);
	अगर (nstoken)
		बंद_netns(nstoken);
पूर्ण

#घोषणा RUN_TEST(name)                                                                      \
	(अणु                                                                                  \
		काष्ठा netns_setup_result setup_result;                                     \
		अगर (test__start_subtest(#name))                                             \
			अगर (ASSERT_OK(netns_setup_namespaces("add"), "setup namespaces")) अणु \
				अगर (ASSERT_OK(netns_setup_links_and_routes(&setup_result),  \
					      "setup links and routes"))                    \
					test_ ## name(&setup_result);                       \
				netns_setup_namespaces("delete");                           \
			पूर्ण                                                                   \
	पूर्ण)

अटल व्योम *test_tc_redirect_run_tests(व्योम *arg)
अणु
	RUN_TEST(tc_redirect_peer);
	RUN_TEST(tc_redirect_peer_l3);
	RUN_TEST(tc_redirect_neigh);
	RUN_TEST(tc_redirect_neigh_fib);
	वापस शून्य;
पूर्ण

व्योम test_tc_redirect(व्योम)
अणु
	pthपढ़ो_t test_thपढ़ो;
	पूर्णांक err;

	/* Run the tests in their own thपढ़ो to isolate the namespace changes
	 * so they करो not affect the environment of other tests.
	 * (specअगरically needed because of unshare(CLONE_NEWNS) in खोलो_netns())
	 */
	err = pthपढ़ो_create(&test_thपढ़ो, शून्य, &test_tc_redirect_run_tests, शून्य);
	अगर (ASSERT_OK(err, "pthread_create"))
		ASSERT_OK(pthपढ़ो_join(test_thपढ़ो, शून्य), "pthread_join");
पूर्ण
