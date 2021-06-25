<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * (C) 2008 Krzysztof Piotr Oledzki <ole@ans.pl>
 */

#अगर_अघोषित _NF_CONNTRACK_ACCT_H
#घोषणा _NF_CONNTRACK_ACCT_H
#समावेश <net/net_namespace.h>
#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>

काष्ठा nf_conn_counter अणु
	atomic64_t packets;
	atomic64_t bytes;
पूर्ण;

काष्ठा nf_conn_acct अणु
	काष्ठा nf_conn_counter counter[IP_CT_सूची_MAX];
पूर्ण;

अटल अंतरभूत
काष्ठा nf_conn_acct *nf_conn_acct_find(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस nf_ct_ext_find(ct, NF_CT_EXT_ACCT);
पूर्ण

अटल अंतरभूत
काष्ठा nf_conn_acct *nf_ct_acct_ext_add(काष्ठा nf_conn *ct, gfp_t gfp)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_conn_acct *acct;

	अगर (!net->ct.sysctl_acct)
		वापस शून्य;

	acct = nf_ct_ext_add(ct, NF_CT_EXT_ACCT, gfp);
	अगर (!acct)
		pr_debug("failed to add accounting extension area");


	वापस acct;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

/* Check अगर connection tracking accounting is enabled */
अटल अंतरभूत bool nf_ct_acct_enabled(काष्ठा net *net)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	वापस net->ct.sysctl_acct != 0;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/* Enable/disable connection tracking accounting */
अटल अंतरभूत व्योम nf_ct_set_acct(काष्ठा net *net, bool enable)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	net->ct.sysctl_acct = enable;
#पूर्ण_अगर
पूर्ण

व्योम nf_ct_acct_add(काष्ठा nf_conn *ct, u32 dir, अचिन्हित पूर्णांक packets,
		    अचिन्हित पूर्णांक bytes);

अटल अंतरभूत व्योम nf_ct_acct_update(काष्ठा nf_conn *ct, u32 dir,
				     अचिन्हित पूर्णांक bytes)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	nf_ct_acct_add(ct, dir, 1, bytes);
#पूर्ण_अगर
पूर्ण

व्योम nf_conntrack_acct_pernet_init(काष्ठा net *net);

पूर्णांक nf_conntrack_acct_init(व्योम);
व्योम nf_conntrack_acct_fini(व्योम);

#पूर्ण_अगर /* _NF_CONNTRACK_ACCT_H */
