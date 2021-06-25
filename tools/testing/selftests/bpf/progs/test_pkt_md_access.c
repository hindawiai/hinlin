<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Facebook
 */
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <linux/bpf.h>
#समावेश <linux/pkt_cls.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक _version SEC("version") = 1;

#अगर  __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#घोषणा TEST_FIELD(TYPE, FIELD, MASK)					\
	अणु								\
		TYPE पंचांगp = *(अस्थिर TYPE *)&skb->FIELD;		\
		अगर (पंचांगp != ((*(अस्थिर __u32 *)&skb->FIELD) & MASK))	\
			वापस TC_ACT_SHOT;				\
	पूर्ण
#अन्यथा
#घोषणा TEST_FIELD_OFFSET(a, b)	((माप(a) - माप(b)) / माप(b))
#घोषणा TEST_FIELD(TYPE, FIELD, MASK)					\
	अणु								\
		TYPE पंचांगp = *((अस्थिर TYPE *)&skb->FIELD +		\
			      TEST_FIELD_OFFSET(skb->FIELD, TYPE));	\
		अगर (पंचांगp != ((*(अस्थिर __u32 *)&skb->FIELD) & MASK))	\
			वापस TC_ACT_SHOT;				\
	पूर्ण
#पूर्ण_अगर

SEC("classifier/test_pkt_md_access")
पूर्णांक test_pkt_md_access(काष्ठा __sk_buff *skb)
अणु
	TEST_FIELD(__u8,  len, 0xFF);
	TEST_FIELD(__u16, len, 0xFFFF);
	TEST_FIELD(__u32, len, 0xFFFFFFFF);
	TEST_FIELD(__u16, protocol, 0xFFFF);
	TEST_FIELD(__u32, protocol, 0xFFFFFFFF);
	TEST_FIELD(__u8,  hash, 0xFF);
	TEST_FIELD(__u16, hash, 0xFFFF);
	TEST_FIELD(__u32, hash, 0xFFFFFFFF);

	वापस TC_ACT_OK;
पूर्ण
