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

__attribute__ ((noअंतरभूत))
पूर्णांक f2(पूर्णांक val, काष्ठा __sk_buff *skb)
अणु
	वापस f1(skb) + val;
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक f3(पूर्णांक val, काष्ठा __sk_buff *skb, पूर्णांक var)
अणु
	वापस f2(var, skb) + val;
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक f4(काष्ठा __sk_buff *skb)
अणु
	वापस f3(1, skb, 2);
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक f5(काष्ठा __sk_buff *skb)
अणु
	वापस f4(skb);
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक f6(काष्ठा __sk_buff *skb)
अणु
	वापस f5(skb);
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक f7(काष्ठा __sk_buff *skb)
अणु
	वापस f6(skb);
पूर्ण

#अगर_अघोषित NO_FN8
__attribute__ ((noअंतरभूत))
पूर्णांक f8(काष्ठा __sk_buff *skb)
अणु
	वापस f7(skb);
पूर्ण
#पूर्ण_अगर

SEC("classifier/test")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
#अगर_अघोषित NO_FN8
	वापस f8(skb);
#अन्यथा
	वापस f7(skb);
#पूर्ण_अगर
पूर्ण
