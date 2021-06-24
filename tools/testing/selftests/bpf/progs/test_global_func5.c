<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

__attribute__ ((noअंतरभूत))
पूर्णांक f1(काष्ठा __sk_buff *skb)
अणु
	वापस skb->len;
पूर्ण

पूर्णांक f3(पूर्णांक, काष्ठा __sk_buff *skb);

__attribute__ ((noअंतरभूत))
पूर्णांक f2(पूर्णांक val, काष्ठा __sk_buff *skb)
अणु
	वापस f1(skb) + f3(val, (व्योम *)&val); /* type mismatch */
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक f3(पूर्णांक val, काष्ठा __sk_buff *skb)
अणु
	वापस skb->अगरindex * val;
पूर्ण

SEC("classifier/test")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	वापस f1(skb) + f2(2, skb) + f3(3, skb);
पूर्ण
