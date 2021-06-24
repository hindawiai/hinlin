<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

SEC("socket")
पूर्णांक combinations(अस्थिर काष्ठा __sk_buff* skb)
अणु
	पूर्णांक ret = 0, i;

#आशय nounroll
	क्रम (i = 0; i < 20; i++)
		अगर (skb->len)
			ret |= 1 << i;
	वापस ret;
पूर्ण
