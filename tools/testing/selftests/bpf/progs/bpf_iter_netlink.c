<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश "bpf_tracing_net.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

अटल __attribute__((noअंतरभूत)) काष्ठा inode *SOCK_INODE(काष्ठा socket *socket)
अणु
	वापस &container_of(socket, काष्ठा socket_alloc, socket)->vfs_inode;
पूर्ण

SEC("iter/netlink")
पूर्णांक dump_netlink(काष्ठा bpf_iter__netlink *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा netlink_sock *nlk = ctx->sk;
	अचिन्हित दीर्घ group, ino;
	काष्ठा inode *inode;
	काष्ठा socket *sk;
	काष्ठा sock *s;

	अगर (nlk == (व्योम *)0)
		वापस 0;

	अगर (ctx->meta->seq_num == 0)
		BPF_SEQ_PRINTF(seq, "sk               Eth Pid        Groups   "
				    "Rmem     Wmem     Dump  Locks    Drops    "
				    "Inode\n");

	s = &nlk->sk;
	BPF_SEQ_PRINTF(seq, "%pK %-3d ", s, s->sk_protocol);

	अगर (!nlk->groups)  अणु
		group = 0;
	पूर्ण अन्यथा अणु
		/* FIXME: temporary use bpf_probe_पढ़ो_kernel here, needs
		 * verअगरier support to करो direct access.
		 */
		bpf_probe_पढ़ो_kernel(&group, माप(group), &nlk->groups[0]);
	पूर्ण
	BPF_SEQ_PRINTF(seq, "%-10u %08x %-8d %-8d %-5d %-8d ",
		       nlk->portid, (u32)group,
		       s->sk_rmem_alloc.counter,
		       s->sk_wmem_alloc.refs.counter - 1,
		       nlk->cb_running, s->sk_refcnt.refs.counter);

	sk = s->sk_socket;
	अगर (!sk) अणु
		ino = 0;
	पूर्ण अन्यथा अणु
		/* FIXME: container_of inside SOCK_INODE has a क्रमced
		 * type conversion, and direct access cannot be used
		 * with current verअगरier.
		 */
		inode = SOCK_INODE(sk);
		bpf_probe_पढ़ो_kernel(&ino, माप(ino), &inode->i_ino);
	पूर्ण
	BPF_SEQ_PRINTF(seq, "%-8u %-8lu\n", s->sk_drops.counter, ino);

	वापस 0;
पूर्ण
