<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/मानकघोष.स>
#समावेश <linux/ipv6.h>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <sys/socket.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

SEC("freplace/connect_v4_prog")
पूर्णांक new_connect_v4_prog(काष्ठा bpf_sock_addr *ctx)
अणु
	// वापस value thats in invalid range
	वापस 255;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
