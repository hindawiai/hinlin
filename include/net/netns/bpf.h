<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * BPF programs attached to network namespace
 */

#अगर_अघोषित __NETNS_BPF_H__
#घोषणा __NETNS_BPF_H__

#समावेश <linux/bpf-netns.h>

काष्ठा bpf_prog;
काष्ठा bpf_prog_array;

काष्ठा netns_bpf अणु
	/* Array of programs to run compiled from progs or links */
	काष्ठा bpf_prog_array __rcu *run_array[MAX_NETNS_BPF_ATTACH_TYPE];
	काष्ठा bpf_prog *progs[MAX_NETNS_BPF_ATTACH_TYPE];
	काष्ठा list_head links[MAX_NETNS_BPF_ATTACH_TYPE];
पूर्ण;

#पूर्ण_अगर /* __NETNS_BPF_H__ */
