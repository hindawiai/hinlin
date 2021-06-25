<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_TSTAMP_H
#घोषणा _NF_CONNTRACK_TSTAMP_H

#समावेश <net/net_namespace.h>
#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>

काष्ठा nf_conn_tstamp अणु
	u_पूर्णांक64_t start;
	u_पूर्णांक64_t stop;
पूर्ण;

अटल अंतरभूत
काष्ठा nf_conn_tstamp *nf_conn_tstamp_find(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
	वापस nf_ct_ext_find(ct, NF_CT_EXT_TSTAMP);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत
काष्ठा nf_conn_tstamp *nf_ct_tstamp_ext_add(काष्ठा nf_conn *ct, gfp_t gfp)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
	काष्ठा net *net = nf_ct_net(ct);

	अगर (!net->ct.sysctl_tstamp)
		वापस शून्य;

	वापस nf_ct_ext_add(ct, NF_CT_EXT_TSTAMP, gfp);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
व्योम nf_conntrack_tstamp_pernet_init(काष्ठा net *net);

पूर्णांक nf_conntrack_tstamp_init(व्योम);
व्योम nf_conntrack_tstamp_fini(व्योम);
#अन्यथा
अटल अंतरभूत व्योम nf_conntrack_tstamp_pernet_init(काष्ठा net *net) अणुपूर्ण

अटल अंतरभूत पूर्णांक nf_conntrack_tstamp_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nf_conntrack_tstamp_fini(व्योम)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMESTAMP */

#पूर्ण_अगर /* _NF_CONNTRACK_TSTAMP_H */
