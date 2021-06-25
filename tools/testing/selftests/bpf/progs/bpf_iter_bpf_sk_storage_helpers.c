<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Google LLC. */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sk_stg_map SEC(".maps");

SEC("iter/bpf_sk_storage_map")
पूर्णांक delete_bpf_sk_storage_map(काष्ठा bpf_iter__bpf_sk_storage_map *ctx)
अणु
	अगर (ctx->sk)
		bpf_sk_storage_delete(&sk_stg_map, ctx->sk);

	वापस 0;
पूर्ण

SEC("iter/task_file")
पूर्णांक fill_socket_owner(काष्ठा bpf_iter__task_file *ctx)
अणु
	काष्ठा task_काष्ठा *task = ctx->task;
	काष्ठा file *file = ctx->file;
	काष्ठा socket *sock;
	पूर्णांक *sock_tgid;

	अगर (!task || !file)
		वापस 0;

	sock = bpf_sock_from_file(file);
	अगर (!sock)
		वापस 0;

	sock_tgid = bpf_sk_storage_get(&sk_stg_map, sock->sk, 0, 0);
	अगर (!sock_tgid)
		वापस 0;

	*sock_tgid = task->tgid;

	वापस 0;
पूर्ण

SEC("iter/tcp")
पूर्णांक negate_socket_local_storage(काष्ठा bpf_iter__tcp *ctx)
अणु
	काष्ठा sock_common *sk_common = ctx->sk_common;
	पूर्णांक *sock_tgid;

	अगर (!sk_common)
		वापस 0;

	sock_tgid = bpf_sk_storage_get(&sk_stg_map, sk_common, 0, 0);
	अगर (!sock_tgid)
		वापस 0;

	*sock_tgid = -*sock_tgid;

	वापस 0;
पूर्ण
