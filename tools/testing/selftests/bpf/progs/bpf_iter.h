<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2020 Facebook */
/* "undefine" काष्ठाs in vmlinux.h, because we "override" them below */
#घोषणा bpf_iter_meta bpf_iter_meta___not_used
#घोषणा bpf_iter__bpf_map bpf_iter__bpf_map___not_used
#घोषणा bpf_iter__ipv6_route bpf_iter__ipv6_route___not_used
#घोषणा bpf_iter__netlink bpf_iter__netlink___not_used
#घोषणा bpf_iter__task bpf_iter__task___not_used
#घोषणा bpf_iter__task_file bpf_iter__task_file___not_used
#घोषणा bpf_iter__task_vma bpf_iter__task_vma___not_used
#घोषणा bpf_iter__tcp bpf_iter__tcp___not_used
#घोषणा tcp6_sock tcp6_sock___not_used
#घोषणा bpf_iter__udp bpf_iter__udp___not_used
#घोषणा udp6_sock udp6_sock___not_used
#घोषणा bpf_iter__bpf_map_elem bpf_iter__bpf_map_elem___not_used
#घोषणा bpf_iter__bpf_sk_storage_map bpf_iter__bpf_sk_storage_map___not_used
#घोषणा bpf_iter__sockmap bpf_iter__sockmap___not_used
#घोषणा btf_ptr btf_ptr___not_used
#घोषणा BTF_F_COMPACT BTF_F_COMPACT___not_used
#घोषणा BTF_F_NONAME BTF_F_NONAME___not_used
#घोषणा BTF_F_PTR_RAW BTF_F_PTR_RAW___not_used
#घोषणा BTF_F_ZERO BTF_F_ZERO___not_used
#समावेश "vmlinux.h"
#अघोषित bpf_iter_meta
#अघोषित bpf_iter__bpf_map
#अघोषित bpf_iter__ipv6_route
#अघोषित bpf_iter__netlink
#अघोषित bpf_iter__task
#अघोषित bpf_iter__task_file
#अघोषित bpf_iter__task_vma
#अघोषित bpf_iter__tcp
#अघोषित tcp6_sock
#अघोषित bpf_iter__udp
#अघोषित udp6_sock
#अघोषित bpf_iter__bpf_map_elem
#अघोषित bpf_iter__bpf_sk_storage_map
#अघोषित bpf_iter__sockmap
#अघोषित btf_ptr
#अघोषित BTF_F_COMPACT
#अघोषित BTF_F_NONAME
#अघोषित BTF_F_PTR_RAW
#अघोषित BTF_F_ZERO

काष्ठा bpf_iter_meta अणु
	काष्ठा seq_file *seq;
	__u64 session_id;
	__u64 seq_num;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__ipv6_route अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा fib6_info *rt;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__netlink अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा netlink_sock *sk;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__task अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा task_काष्ठा *task;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__task_file अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा task_काष्ठा *task;
	__u32 fd;
	काष्ठा file *file;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__task_vma अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा task_काष्ठा *task;
	काष्ठा vm_area_काष्ठा *vma;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__bpf_map अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा bpf_map *map;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__tcp अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा sock_common *sk_common;
	uid_t uid;
पूर्ण __attribute__((preserve_access_index));

काष्ठा tcp6_sock अणु
	काष्ठा tcp_sock	tcp;
	काष्ठा ipv6_pinfo inet6;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__udp अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा udp_sock *udp_sk;
	uid_t uid __attribute__((aligned(8)));
	पूर्णांक bucket __attribute__((aligned(8)));
पूर्ण __attribute__((preserve_access_index));

काष्ठा udp6_sock अणु
	काष्ठा udp_sock	udp;
	काष्ठा ipv6_pinfo inet6;
पूर्ण __attribute__((preserve_access_index));

काष्ठा bpf_iter__bpf_map_elem अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा bpf_map *map;
	व्योम *key;
	व्योम *value;
पूर्ण;

काष्ठा bpf_iter__bpf_sk_storage_map अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा bpf_map *map;
	काष्ठा sock *sk;
	व्योम *value;
पूर्ण;

काष्ठा bpf_iter__sockmap अणु
	काष्ठा bpf_iter_meta *meta;
	काष्ठा bpf_map *map;
	व्योम *key;
	काष्ठा sock *sk;
पूर्ण;

काष्ठा btf_ptr अणु
	व्योम *ptr;
	__u32 type_id;
	__u32 flags;
पूर्ण;

क्रमागत अणु
	BTF_F_COMPACT	=	(1ULL << 0),
	BTF_F_NONAME	=	(1ULL << 1),
	BTF_F_PTR_RAW	=	(1ULL << 2),
	BTF_F_ZERO	=	(1ULL << 3),
पूर्ण;
