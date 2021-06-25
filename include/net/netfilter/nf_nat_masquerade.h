<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_NAT_MASQUERADE_H_
#घोषणा _NF_NAT_MASQUERADE_H_

#समावेश <linux/skbuff.h>
#समावेश <net/netfilter/nf_nat.h>

अचिन्हित पूर्णांक
nf_nat_masquerade_ipv4(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hooknum,
		       स्थिर काष्ठा nf_nat_range2 *range,
		       स्थिर काष्ठा net_device *out);

पूर्णांक nf_nat_masquerade_inet_रेजिस्टर_notअगरiers(व्योम);
व्योम nf_nat_masquerade_inet_unरेजिस्टर_notअगरiers(व्योम);

अचिन्हित पूर्णांक
nf_nat_masquerade_ipv6(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_nat_range2 *range,
		       स्थिर काष्ठा net_device *out);

#पूर्ण_अगर /*_NF_NAT_MASQUERADE_H_ */
