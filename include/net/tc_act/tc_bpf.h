<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2015 Jiri Pirko <jiri@resnulli.us>
 */

#अगर_अघोषित __NET_TC_BPF_H
#घोषणा __NET_TC_BPF_H

#समावेश <linux/filter.h>
#समावेश <net/act_api.h>

काष्ठा tcf_bpf अणु
	काष्ठा tc_action	common;
	काष्ठा bpf_prog __rcu	*filter;
	जोड़ अणु
		u32		bpf_fd;
		u16		bpf_num_ops;
	पूर्ण;
	काष्ठा sock_filter	*bpf_ops;
	स्थिर अक्षर		*bpf_name;
पूर्ण;
#घोषणा to_bpf(a) ((काष्ठा tcf_bpf *)a)

#पूर्ण_अगर /* __NET_TC_BPF_H */
