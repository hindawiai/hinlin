<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_AH_H
#घोषणा _NET_AH_H

#समावेश <linux/skbuff.h>

काष्ठा crypto_ahash;

काष्ठा ah_data अणु
	पूर्णांक			icv_full_len;
	पूर्णांक			icv_trunc_len;

	काष्ठा crypto_ahash	*ahash;
पूर्ण;

काष्ठा ip_auth_hdr;

अटल अंतरभूत काष्ठा ip_auth_hdr *ip_auth_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ip_auth_hdr *)skb_transport_header(skb);
पूर्ण

#पूर्ण_अगर
