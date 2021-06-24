<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_DEFRAG_IPV6_H
#घोषणा _NF_DEFRAG_IPV6_H

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>

पूर्णांक nf_defrag_ipv6_enable(काष्ठा net *net);
व्योम nf_defrag_ipv6_disable(काष्ठा net *net);

पूर्णांक nf_ct_frag6_init(व्योम);
व्योम nf_ct_frag6_cleanup(व्योम);
पूर्णांक nf_ct_frag6_gather(काष्ठा net *net, काष्ठा sk_buff *skb, u32 user);

काष्ठा inet_frags_ctl;

काष्ठा nft_ct_frag6_pernet अणु
	काष्ठा ctl_table_header *nf_frag_frags_hdr;
	काष्ठा fqdir	*fqdir;
	अचिन्हित पूर्णांक users;
पूर्ण;

#पूर्ण_अगर /* _NF_DEFRAG_IPV6_H */
