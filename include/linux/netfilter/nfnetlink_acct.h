<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFNL_ACCT_H_
#घोषणा _NFNL_ACCT_H_

#समावेश <uapi/linux/netfilter/nfnetlink_acct.h>
#समावेश <net/net_namespace.h>

क्रमागत अणु
	NFACCT_NO_QUOTA		= -1,
	NFACCT_UNDERQUOTA,
	NFACCT_OVERQUOTA,
पूर्ण;

काष्ठा nf_acct;

काष्ठा nf_acct *nfnl_acct_find_get(काष्ठा net *net, स्थिर अक्षर *filter_name);
व्योम nfnl_acct_put(काष्ठा nf_acct *acct);
व्योम nfnl_acct_update(स्थिर काष्ठा sk_buff *skb, काष्ठा nf_acct *nfacct);
पूर्णांक nfnl_acct_overquota(काष्ठा net *net, काष्ठा nf_acct *nfacct);
#पूर्ण_अगर /* _NFNL_ACCT_H */
