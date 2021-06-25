<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_EXTEND_H
#घोषणा _NF_CONNTRACK_EXTEND_H

#समावेश <linux/slab.h>

#समावेश <net/netfilter/nf_conntrack.h>

क्रमागत nf_ct_ext_id अणु
	NF_CT_EXT_HELPER,
#अगर IS_ENABLED(CONFIG_NF_NAT)
	NF_CT_EXT_NAT,
#पूर्ण_अगर
	NF_CT_EXT_SEQADJ,
	NF_CT_EXT_ACCT,
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	NF_CT_EXT_ECACHE,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
	NF_CT_EXT_TSTAMP,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	NF_CT_EXT_TIMEOUT,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	NF_CT_EXT_LABELS,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NETFILTER_SYNPROXY)
	NF_CT_EXT_SYNPROXY,
#पूर्ण_अगर
	NF_CT_EXT_NUM,
पूर्ण;

#घोषणा NF_CT_EXT_HELPER_TYPE काष्ठा nf_conn_help
#घोषणा NF_CT_EXT_NAT_TYPE काष्ठा nf_conn_nat
#घोषणा NF_CT_EXT_SEQADJ_TYPE काष्ठा nf_conn_seqadj
#घोषणा NF_CT_EXT_ACCT_TYPE काष्ठा nf_conn_acct
#घोषणा NF_CT_EXT_ECACHE_TYPE काष्ठा nf_conntrack_ecache
#घोषणा NF_CT_EXT_TSTAMP_TYPE काष्ठा nf_conn_tstamp
#घोषणा NF_CT_EXT_TIMEOUT_TYPE काष्ठा nf_conn_समयout
#घोषणा NF_CT_EXT_LABELS_TYPE काष्ठा nf_conn_labels
#घोषणा NF_CT_EXT_SYNPROXY_TYPE काष्ठा nf_conn_synproxy

/* Extensions: optional stuff which isn't permanently in काष्ठा. */
काष्ठा nf_ct_ext अणु
	u8 offset[NF_CT_EXT_NUM];
	u8 len;
	अक्षर data[];
पूर्ण;

अटल अंतरभूत bool __nf_ct_ext_exist(स्थिर काष्ठा nf_ct_ext *ext, u8 id)
अणु
	वापस !!ext->offset[id];
पूर्ण

अटल अंतरभूत bool nf_ct_ext_exist(स्थिर काष्ठा nf_conn *ct, u8 id)
अणु
	वापस (ct->ext && __nf_ct_ext_exist(ct->ext, id));
पूर्ण

अटल अंतरभूत व्योम *__nf_ct_ext_find(स्थिर काष्ठा nf_conn *ct, u8 id)
अणु
	अगर (!nf_ct_ext_exist(ct, id))
		वापस शून्य;

	वापस (व्योम *)ct->ext + ct->ext->offset[id];
पूर्ण
#घोषणा nf_ct_ext_find(ext, id)	\
	((id##_TYPE *)__nf_ct_ext_find((ext), (id)))

/* Destroy all relationships */
व्योम nf_ct_ext_destroy(काष्ठा nf_conn *ct);

/* Add this type, वापसs poपूर्णांकer to data or शून्य. */
व्योम *nf_ct_ext_add(काष्ठा nf_conn *ct, क्रमागत nf_ct_ext_id id, gfp_t gfp);

काष्ठा nf_ct_ext_type अणु
	/* Destroys relationships (can be शून्य). */
	व्योम (*destroy)(काष्ठा nf_conn *ct);

	क्रमागत nf_ct_ext_id id;

	/* Length and min alignment. */
	u8 len;
	u8 align;
पूर्ण;

पूर्णांक nf_ct_extend_रेजिस्टर(स्थिर काष्ठा nf_ct_ext_type *type);
व्योम nf_ct_extend_unरेजिस्टर(स्थिर काष्ठा nf_ct_ext_type *type);
#पूर्ण_अगर /* _NF_CONNTRACK_EXTEND_H */
