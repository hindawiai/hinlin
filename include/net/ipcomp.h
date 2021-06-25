<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_IPCOMP_H
#घोषणा _NET_IPCOMP_H

#समावेश <linux/types.h>

#घोषणा IPCOMP_SCRATCH_SIZE     65400

काष्ठा crypto_comp;

काष्ठा ipcomp_data अणु
	u16 threshold;
	काष्ठा crypto_comp * __percpu *tfms;
पूर्ण;

काष्ठा ip_comp_hdr;
काष्ठा sk_buff;
काष्ठा xfrm_state;

पूर्णांक ipcomp_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb);
पूर्णांक ipcomp_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb);
व्योम ipcomp_destroy(काष्ठा xfrm_state *x);
पूर्णांक ipcomp_init_state(काष्ठा xfrm_state *x);

अटल अंतरभूत काष्ठा ip_comp_hdr *ip_comp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ip_comp_hdr *)skb_transport_header(skb);
पूर्ण

#पूर्ण_अगर
