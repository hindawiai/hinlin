<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

#अगर_अघोषित MAX_STACK
#घोषणा MAX_STACK (512 - 3 * 32 + 8)
#पूर्ण_अगर

अटल __attribute__ ((noअंतरभूत))
पूर्णांक f0(पूर्णांक var, काष्ठा __sk_buff *skb)
अणु
	वापस skb->len;
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक f1(काष्ठा __sk_buff *skb)
अणु
	अस्थिर अक्षर buf[MAX_STACK] = अणुपूर्ण;

	वापस f0(0, skb) + skb->len;
पूर्ण

पूर्णांक f3(पूर्णांक, काष्ठा __sk_buff *skb, पूर्णांक);

__attribute__ ((noअंतरभूत))
पूर्णांक f2(पूर्णांक val, काष्ठा __sk_buff *skb)
अणु
	वापस f1(skb) + f3(val, skb, 1);
पूर्ण

__attribute__ ((noअंतरभूत))
पूर्णांक f3(पूर्णांक val, काष्ठा __sk_buff *skb, पूर्णांक var)
अणु
	अस्थिर अक्षर buf[MAX_STACK] = अणुपूर्ण;

	वापस skb->अगरindex * val * var;
पूर्ण

SEC("classifier/test")
पूर्णांक test_cls(काष्ठा __sk_buff *skb)
अणु
	वापस f0(1, skb) + f1(skb) + f2(2, skb) + f3(3, skb, 4);
पूर्ण
