<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_IFE_H
#घोषणा __NET_IFE_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <uapi/linux/अगरe.h>

#अगर IS_ENABLED(CONFIG_NET_IFE)

व्योम *अगरe_encode(काष्ठा sk_buff *skb, u16 metalen);
व्योम *अगरe_decode(काष्ठा sk_buff *skb, u16 *metalen);

व्योम *अगरe_tlv_meta_decode(व्योम *skbdata, स्थिर व्योम *अगरehdr_end, u16 *attrtype,
			  u16 *dlen, u16 *totlen);
पूर्णांक अगरe_tlv_meta_encode(व्योम *skbdata, u16 attrtype, u16 dlen,
			स्थिर व्योम *dval);

व्योम *अगरe_tlv_meta_next(व्योम *skbdata);

#अन्यथा

अटल अंतरभूत व्योम *अगरe_encode(काष्ठा sk_buff *skb, u16 metalen)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *अगरe_decode(काष्ठा sk_buff *skb, u16 *metalen)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *अगरe_tlv_meta_decode(व्योम *skbdata, u16 *attrtype, u16 *dlen,
					u16 *totlen)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक अगरe_tlv_meta_encode(व्योम *skbdata, u16 attrtype, u16 dlen,
			स्थिर व्योम *dval)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *अगरe_tlv_meta_next(व्योम *skbdata)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __NET_IFE_H */
