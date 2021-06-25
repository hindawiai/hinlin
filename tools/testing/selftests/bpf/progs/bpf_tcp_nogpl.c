<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <linux/types.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश "bpf_tcp_helpers.h"

अक्षर _license[] SEC("license") = "X";

व्योम BPF_STRUCT_OPS(nogpltcp_init, काष्ठा sock *sk)
अणु
पूर्ण

SEC(".struct_ops")
काष्ठा tcp_congestion_ops bpf_nogpltcp = अणु
	.init           = (व्योम *)nogpltcp_init,
	.name           = "bpf_nogpltcp",
पूर्ण;
