<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश "vmlinux.h"

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा AF_INET6 10

काष्ठा socket_cookie अणु
	__u64 cookie_key;
	__u32 cookie_value;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा socket_cookie);
पूर्ण socket_cookies SEC(".maps");

/*
 * These three programs get executed in a row on connect() syscalls. The
 * userspace side of the test creates a client socket, issues a connect() on it
 * and then checks that the local storage associated with this socket has:
 * cookie_value == local_port << 8 | 0xFF
 * The dअगरferent parts of this cookie_value are appended by those hooks अगर they
 * all agree on the output of bpf_get_socket_cookie().
 */
SEC("cgroup/connect6")
पूर्णांक set_cookie(काष्ठा bpf_sock_addr *ctx)
अणु
	काष्ठा socket_cookie *p;

	अगर (ctx->family != AF_INET6 || ctx->user_family != AF_INET6)
		वापस 1;

	p = bpf_sk_storage_get(&socket_cookies, ctx->sk, 0,
			       BPF_SK_STORAGE_GET_F_CREATE);
	अगर (!p)
		वापस 1;

	p->cookie_value = 0xF;
	p->cookie_key = bpf_get_socket_cookie(ctx);

	वापस 1;
पूर्ण

SEC("sockops")
पूर्णांक update_cookie_sockops(काष्ठा bpf_sock_ops *ctx)
अणु
	काष्ठा bpf_sock *sk = ctx->sk;
	काष्ठा socket_cookie *p;

	अगर (ctx->family != AF_INET6)
		वापस 1;

	अगर (ctx->op != BPF_SOCK_OPS_TCP_CONNECT_CB)
		वापस 1;

	अगर (!sk)
		वापस 1;

	p = bpf_sk_storage_get(&socket_cookies, sk, 0, 0);
	अगर (!p)
		वापस 1;

	अगर (p->cookie_key != bpf_get_socket_cookie(ctx))
		वापस 1;

	p->cookie_value |= (ctx->local_port << 8);

	वापस 1;
पूर्ण

SEC("fexit/inet_stream_connect")
पूर्णांक BPF_PROG(update_cookie_tracing, काष्ठा socket *sock,
	     काष्ठा sockaddr *uaddr, पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा socket_cookie *p;

	अगर (uaddr->sa_family != AF_INET6)
		वापस 0;

	p = bpf_sk_storage_get(&socket_cookies, sock->sk, 0, 0);
	अगर (!p)
		वापस 0;

	अगर (p->cookie_key != bpf_get_socket_cookie(sock->sk))
		वापस 0;

	p->cookie_value |= 0xF0;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
