<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा KBUILD_MODNAME "xdp_dummy"
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

SEC("xdp_dummy")
पूर्णांक xdp_dummy_prog(काष्ठा xdp_md *ctx)
अणु
	वापस XDP_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
