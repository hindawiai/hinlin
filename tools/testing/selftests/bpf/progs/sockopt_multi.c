<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <netinet/in.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";
__u32 _version SEC("version") = 1;

SEC("cgroup/getsockopt/child")
पूर्णांक _माला_लोockopt_child(काष्ठा bpf_sockopt *ctx)
अणु
	__u8 *optval_end = ctx->optval_end;
	__u8 *optval = ctx->optval;

	अगर (ctx->level != SOL_IP || ctx->optname != IP_TOS)
		वापस 1;

	अगर (optval + 1 > optval_end)
		वापस 0; /* EPERM, bounds check */

	अगर (optval[0] != 0x80)
		वापस 0; /* EPERM, unexpected optval from the kernel */

	ctx->retval = 0; /* Reset प्रणाली call वापस value to zero */

	optval[0] = 0x90;
	ctx->optlen = 1;

	वापस 1;
पूर्ण

SEC("cgroup/getsockopt/parent")
पूर्णांक _माला_लोockopt_parent(काष्ठा bpf_sockopt *ctx)
अणु
	__u8 *optval_end = ctx->optval_end;
	__u8 *optval = ctx->optval;

	अगर (ctx->level != SOL_IP || ctx->optname != IP_TOS)
		वापस 1;

	अगर (optval + 1 > optval_end)
		वापस 0; /* EPERM, bounds check */

	अगर (optval[0] != 0x90)
		वापस 0; /* EPERM, unexpected optval from the kernel */

	ctx->retval = 0; /* Reset प्रणाली call वापस value to zero */

	optval[0] = 0xA0;
	ctx->optlen = 1;

	वापस 1;
पूर्ण

SEC("cgroup/setsockopt")
पूर्णांक _setsockopt(काष्ठा bpf_sockopt *ctx)
अणु
	__u8 *optval_end = ctx->optval_end;
	__u8 *optval = ctx->optval;

	अगर (ctx->level != SOL_IP || ctx->optname != IP_TOS)
		वापस 1;

	अगर (optval + 1 > optval_end)
		वापस 0; /* EPERM, bounds check */

	optval[0] += 0x10;
	ctx->optlen = 1;

	वापस 1;
पूर्ण
