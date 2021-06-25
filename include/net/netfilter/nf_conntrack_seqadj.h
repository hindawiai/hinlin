<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_SEQADJ_H
#घोषणा _NF_CONNTRACK_SEQADJ_H

#समावेश <net/netfilter/nf_conntrack_extend.h>

/**
 * काष्ठा nf_ct_seqadj - sequence number adjusपंचांगent inक्रमmation
 *
 * @correction_pos: position of the last TCP sequence number modअगरication
 * @offset_beक्रमe: sequence number offset beक्रमe last modअगरication
 * @offset_after: sequence number offset after last modअगरication
 */
काष्ठा nf_ct_seqadj अणु
	u32		correction_pos;
	s32		offset_beक्रमe;
	s32		offset_after;
पूर्ण;

काष्ठा nf_conn_seqadj अणु
	काष्ठा nf_ct_seqadj	seq[IP_CT_सूची_MAX];
पूर्ण;

अटल अंतरभूत काष्ठा nf_conn_seqadj *nfct_seqadj(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस nf_ct_ext_find(ct, NF_CT_EXT_SEQADJ);
पूर्ण

अटल अंतरभूत काष्ठा nf_conn_seqadj *nfct_seqadj_ext_add(काष्ठा nf_conn *ct)
अणु
	वापस nf_ct_ext_add(ct, NF_CT_EXT_SEQADJ, GFP_ATOMIC);
पूर्ण

पूर्णांक nf_ct_seqadj_init(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
		      s32 off);
पूर्णांक nf_ct_seqadj_set(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
		     __be32 seq, s32 off);
व्योम nf_ct_tcp_seqadj_set(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			  क्रमागत ip_conntrack_info ctinfo, s32 off);

पूर्णांक nf_ct_seq_adjust(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		     क्रमागत ip_conntrack_info ctinfo, अचिन्हित पूर्णांक protoff);
s32 nf_ct_seq_offset(स्थिर काष्ठा nf_conn *ct, क्रमागत ip_conntrack_dir, u32 seq);

पूर्णांक nf_conntrack_seqadj_init(व्योम);
व्योम nf_conntrack_seqadj_fini(व्योम);

#पूर्ण_अगर /* _NF_CONNTRACK_SEQADJ_H */
