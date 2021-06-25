<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश <linux/tcp.h>
#समावेश <linux/bpf.h>
#समावेश <netinet/in.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

पूर्णांक page_size = 0; /* userspace should set it */

#अगर_अघोषित SOL_TCP
#घोषणा SOL_TCP IPPROTO_TCP
#पूर्ण_अगर

#घोषणा SOL_CUSTOM			0xdeadbeef

काष्ठा sockopt_sk अणु
	__u8 val;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा sockopt_sk);
पूर्ण socket_storage_map SEC(".maps");

SEC("cgroup/getsockopt")
पूर्णांक _माला_लोockopt(काष्ठा bpf_sockopt *ctx)
अणु
	__u8 *optval_end = ctx->optval_end;
	__u8 *optval = ctx->optval;
	काष्ठा sockopt_sk *storage;

	अगर (ctx->level == SOL_IP && ctx->optname == IP_TOS) अणु
		/* Not पूर्णांकerested in SOL_IP:IP_TOS;
		 * let next BPF program in the cgroup chain or kernel
		 * handle it.
		 */
		ctx->optlen = 0; /* bypass optval>PAGE_SIZE */
		वापस 1;
	पूर्ण

	अगर (ctx->level == SOL_SOCKET && ctx->optname == SO_SNDBUF) अणु
		/* Not पूर्णांकerested in SOL_SOCKET:SO_SNDBUF;
		 * let next BPF program in the cgroup chain or kernel
		 * handle it.
		 */
		वापस 1;
	पूर्ण

	अगर (ctx->level == SOL_TCP && ctx->optname == TCP_CONGESTION) अणु
		/* Not पूर्णांकerested in SOL_TCP:TCP_CONGESTION;
		 * let next BPF program in the cgroup chain or kernel
		 * handle it.
		 */
		वापस 1;
	पूर्ण

	अगर (ctx->level == SOL_TCP && ctx->optname == TCP_ZEROCOPY_RECEIVE) अणु
		/* Verअगरy that TCP_ZEROCOPY_RECEIVE triggers.
		 * It has a custom implementation क्रम perक्रमmance
		 * reasons.
		 */

		अगर (optval + माप(काष्ठा tcp_zerocopy_receive) > optval_end)
			वापस 0; /* EPERM, bounds check */

		अगर (((काष्ठा tcp_zerocopy_receive *)optval)->address != 0)
			वापस 0; /* EPERM, unexpected data */

		वापस 1;
	पूर्ण

	अगर (ctx->level == SOL_IP && ctx->optname == IP_FREEBIND) अणु
		अगर (optval + 1 > optval_end)
			वापस 0; /* EPERM, bounds check */

		ctx->retval = 0; /* Reset प्रणाली call वापस value to zero */

		/* Always export 0x55 */
		optval[0] = 0x55;
		ctx->optlen = 1;

		/* Userspace buffer is PAGE_SIZE * 2, but BPF
		 * program can only see the first PAGE_SIZE
		 * bytes of data.
		 */
		अगर (optval_end - optval != page_size)
			वापस 0; /* EPERM, unexpected data size */

		वापस 1;
	पूर्ण

	अगर (ctx->level != SOL_CUSTOM)
		वापस 0; /* EPERM, deny everything except custom level */

	अगर (optval + 1 > optval_end)
		वापस 0; /* EPERM, bounds check */

	storage = bpf_sk_storage_get(&socket_storage_map, ctx->sk, 0,
				     BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!storage)
		वापस 0; /* EPERM, couldn't get sk storage */

	अगर (!ctx->retval)
		वापस 0; /* EPERM, kernel should not have handled
			   * SOL_CUSTOM, something is wrong!
			   */
	ctx->retval = 0; /* Reset प्रणाली call वापस value to zero */

	optval[0] = storage->val;
	ctx->optlen = 1;

	वापस 1;
पूर्ण

SEC("cgroup/setsockopt")
पूर्णांक _setsockopt(काष्ठा bpf_sockopt *ctx)
अणु
	__u8 *optval_end = ctx->optval_end;
	__u8 *optval = ctx->optval;
	काष्ठा sockopt_sk *storage;

	अगर (ctx->level == SOL_IP && ctx->optname == IP_TOS) अणु
		/* Not पूर्णांकerested in SOL_IP:IP_TOS;
		 * let next BPF program in the cgroup chain or kernel
		 * handle it.
		 */
		ctx->optlen = 0; /* bypass optval>PAGE_SIZE */
		वापस 1;
	पूर्ण

	अगर (ctx->level == SOL_SOCKET && ctx->optname == SO_SNDBUF) अणु
		/* Overग_लिखो SO_SNDBUF value */

		अगर (optval + माप(__u32) > optval_end)
			वापस 0; /* EPERM, bounds check */

		*(__u32 *)optval = 0x55AA;
		ctx->optlen = 4;

		वापस 1;
	पूर्ण

	अगर (ctx->level == SOL_TCP && ctx->optname == TCP_CONGESTION) अणु
		/* Always use cubic */

		अगर (optval + 5 > optval_end)
			वापस 0; /* EPERM, bounds check */

		स_नकल(optval, "cubic", 5);
		ctx->optlen = 5;

		वापस 1;
	पूर्ण

	अगर (ctx->level == SOL_IP && ctx->optname == IP_FREEBIND) अणु
		/* Original optlen is larger than PAGE_SIZE. */
		अगर (ctx->optlen != page_size * 2)
			वापस 0; /* EPERM, unexpected data size */

		अगर (optval + 1 > optval_end)
			वापस 0; /* EPERM, bounds check */

		/* Make sure we can trim the buffer. */
		optval[0] = 0;
		ctx->optlen = 1;

		/* Usepace buffer is PAGE_SIZE * 2, but BPF
		 * program can only see the first PAGE_SIZE
		 * bytes of data.
		 */
		अगर (optval_end - optval != page_size)
			वापस 0; /* EPERM, unexpected data size */

		वापस 1;
	पूर्ण

	अगर (ctx->level != SOL_CUSTOM)
		वापस 0; /* EPERM, deny everything except custom level */

	अगर (optval + 1 > optval_end)
		वापस 0; /* EPERM, bounds check */

	storage = bpf_sk_storage_get(&socket_storage_map, ctx->sk, 0,
				     BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!storage)
		वापस 0; /* EPERM, couldn't get sk storage */

	storage->val = optval[0];
	ctx->optlen = -1; /* BPF has consumed this option, करोn't call kernel
			   * setsockopt handler.
			   */

	वापस 1;
पूर्ण
