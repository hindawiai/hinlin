<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_SYNPROXY_H
#घोषणा _NF_CONNTRACK_SYNPROXY_H

#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netns/generic.h>

काष्ठा nf_conn_synproxy अणु
	u32	isn;
	u32	its;
	u32	tsoff;
पूर्ण;

अटल अंतरभूत काष्ठा nf_conn_synproxy *nfct_synproxy(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर IS_ENABLED(CONFIG_NETFILTER_SYNPROXY)
	वापस nf_ct_ext_find(ct, NF_CT_EXT_SYNPROXY);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा nf_conn_synproxy *nfct_synproxy_ext_add(काष्ठा nf_conn *ct)
अणु
#अगर IS_ENABLED(CONFIG_NETFILTER_SYNPROXY)
	वापस nf_ct_ext_add(ct, NF_CT_EXT_SYNPROXY, GFP_ATOMIC);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool nf_ct_add_synproxy(काष्ठा nf_conn *ct,
				      स्थिर काष्ठा nf_conn *पंचांगpl)
अणु
#अगर IS_ENABLED(CONFIG_NETFILTER_SYNPROXY)
	अगर (पंचांगpl && nfct_synproxy(पंचांगpl)) अणु
		अगर (!nfct_seqadj_ext_add(ct))
			वापस false;

		अगर (!nfct_synproxy_ext_add(ct))
			वापस false;
	पूर्ण
#पूर्ण_अगर

	वापस true;
पूर्ण

#पूर्ण_अगर /* _NF_CONNTRACK_SYNPROXY_H */
