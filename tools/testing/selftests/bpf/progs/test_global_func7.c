<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

__attribute__ ((noअंतरभूत))
व्योम foo(काष्ठा __sk_buff *skb)
अणु
	skb->tc_index = 0;
पूर्ण

SEC("classifier/test")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	foo(skb);
	वापस 0;
पूर्ण
