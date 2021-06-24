<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश "bpf_tracing_net.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_endian.h>

अक्षर _license[] SEC("license") = "GPL";

अटल दीर्घ sock_i_ino(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा socket *sk_socket = sk->sk_socket;
	स्थिर काष्ठा inode *inode;
	अचिन्हित दीर्घ ino;

	अगर (!sk_socket)
		वापस 0;

	inode = &container_of(sk_socket, काष्ठा socket_alloc, socket)->vfs_inode;
	bpf_probe_पढ़ो_kernel(&ino, माप(ino), &inode->i_ino);
	वापस ino;
पूर्ण

SEC("iter/udp")
पूर्णांक dump_udp4(काष्ठा bpf_iter__udp *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा udp_sock *udp_sk = ctx->udp_sk;
	काष्ठा inet_sock *inet;
	__u16 srcp, destp;
	__be32 dest, src;
	__u32 seq_num;
	पूर्णांक rqueue;

	अगर (udp_sk == (व्योम *)0)
		वापस 0;

	seq_num = ctx->meta->seq_num;
	अगर (seq_num == 0)
		BPF_SEQ_PRINTF(seq,
			       "  sl  local_address rem_address   st tx_queue "
			       "rx_queue tr tm->when retrnsmt   uid  timeout "
			       "inode ref pointer drops\n");

	/* filter out udp6 sockets */
	inet = &udp_sk->inet;
	अगर (inet->sk.sk_family == AF_INET6)
		वापस 0;

	inet = &udp_sk->inet;
	dest = inet->inet_daddr;
	src = inet->inet_rcv_saddr;
	srcp = bpf_ntohs(inet->inet_sport);
	destp = bpf_ntohs(inet->inet_dport);
	rqueue = inet->sk.sk_rmem_alloc.counter - udp_sk->क्रमward_deficit;

	BPF_SEQ_PRINTF(seq, "%5d: %08X:%04X %08X:%04X ",
		       ctx->bucket, src, srcp, dest, destp);

	BPF_SEQ_PRINTF(seq, "%02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %u\n",
		       inet->sk.sk_state,
		       inet->sk.sk_wmem_alloc.refs.counter - 1,
		       rqueue,
		       0, 0L, 0, ctx->uid, 0,
		       sock_i_ino(&inet->sk),
		       inet->sk.sk_refcnt.refs.counter, udp_sk,
		       inet->sk.sk_drops.counter);

	वापस 0;
पूर्ण
