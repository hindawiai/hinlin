<शैली गुरु>
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/socket.h>
#समावेश <linux/net.h>
#समावेश <uapi/linux/in.h>
#समावेश <uapi/linux/in6.h>
#समावेश <bpf/bpf_helpers.h>

SEC("cgroup/sock1")
पूर्णांक bpf_prog1(काष्ठा bpf_sock *sk)
अणु
	अक्षर fmt[] = "socket: family %d type %d protocol %d\n";
	अक्षर fmt2[] = "socket: uid %u gid %u\n";
	__u64 gid_uid = bpf_get_current_uid_gid();
	__u32 uid = gid_uid & 0xffffffff;
	__u32 gid = gid_uid >> 32;

	bpf_trace_prपूर्णांकk(fmt, माप(fmt), sk->family, sk->type, sk->protocol);
	bpf_trace_prपूर्णांकk(fmt2, माप(fmt2), uid, gid);

	/* block PF_INET6, SOCK_RAW, IPPROTO_ICMPV6 sockets
	 * ie., make ping6 fail
	 */
	अगर (sk->family == PF_INET6 &&
	    sk->type == SOCK_RAW   &&
	    sk->protocol == IPPROTO_ICMPV6)
		वापस 0;

	वापस 1;
पूर्ण

SEC("cgroup/sock2")
पूर्णांक bpf_prog2(काष्ठा bpf_sock *sk)
अणु
	अक्षर fmt[] = "socket: family %d type %d protocol %d\n";

	bpf_trace_prपूर्णांकk(fmt, माप(fmt), sk->family, sk->type, sk->protocol);

	/* block PF_INET, SOCK_RAW, IPPROTO_ICMP sockets
	 * ie., make ping fail
	 */
	अगर (sk->family == PF_INET &&
	    sk->type == SOCK_RAW  &&
	    sk->protocol == IPPROTO_ICMP)
		वापस 0;

	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
