<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_ESP_H
#घोषणा _NET_ESP_H

#समावेश <linux/skbuff.h>

काष्ठा ip_esp_hdr;

अटल अंतरभूत काष्ठा ip_esp_hdr *ip_esp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ip_esp_hdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत व्योम esp_output_fill_trailer(u8 *tail, पूर्णांक tfclen, पूर्णांक plen, __u8 proto)
अणु
	/* Fill padding... */
	अगर (tfclen) अणु
		स_रखो(tail, 0, tfclen);
		tail += tfclen;
	पूर्ण
	करो अणु
		पूर्णांक i;
		क्रम (i = 0; i < plen - 2; i++)
			tail[i] = i + 1;
	पूर्ण जबतक (0);
	tail[plen - 2] = plen - 2;
	tail[plen - 1] = proto;
पूर्ण

काष्ठा esp_info अणु
	काष्ठा	ip_esp_hdr *esph;
	__be64	seqno;
	पूर्णांक	tfclen;
	पूर्णांक	tailen;
	पूर्णांक	plen;
	पूर्णांक	clen;
	पूर्णांक 	len;
	पूर्णांक 	nfrags;
	__u8	proto;
	bool	inplace;
पूर्ण;

पूर्णांक esp_output_head(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb, काष्ठा esp_info *esp);
पूर्णांक esp_output_tail(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb, काष्ठा esp_info *esp);
पूर्णांक esp_input_करोne2(काष्ठा sk_buff *skb, पूर्णांक err);
पूर्णांक esp6_output_head(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb, काष्ठा esp_info *esp);
पूर्णांक esp6_output_tail(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb, काष्ठा esp_info *esp);
पूर्णांक esp6_input_करोne2(काष्ठा sk_buff *skb, पूर्णांक err);
#पूर्ण_अगर
