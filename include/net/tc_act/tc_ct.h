<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_CT_H
#घोषणा __NET_TC_CT_H

#समावेश <net/act_api.h>
#समावेश <uapi/linux/tc_act/tc_ct.h>

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>

काष्ठा tcf_ct_params अणु
	काष्ठा nf_conn *पंचांगpl;
	u16 zone;

	u32 mark;
	u32 mark_mask;

	u32 labels[NF_CT_LABELS_MAX_SIZE / माप(u32)];
	u32 labels_mask[NF_CT_LABELS_MAX_SIZE / माप(u32)];

	काष्ठा nf_nat_range2 range;
	bool ipv4_range;

	u16 ct_action;

	काष्ठा rcu_head rcu;

	काष्ठा tcf_ct_flow_table *ct_ft;
	काष्ठा nf_flowtable *nf_ft;
पूर्ण;

काष्ठा tcf_ct अणु
	काष्ठा tc_action common;
	काष्ठा tcf_ct_params __rcu *params;
पूर्ण;

#घोषणा to_ct(a) ((काष्ठा tcf_ct *)a)
#घोषणा to_ct_params(a)							\
	((काष्ठा tcf_ct_params *)					\
	 rcu_dereference_रक्षित(to_ct(a)->params,			\
				   lockdep_is_held(&a->tcfa_lock)))

अटल अंतरभूत uपूर्णांक16_t tcf_ct_zone(स्थिर काष्ठा tc_action *a)
अणु
	वापस to_ct_params(a)->zone;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_ct_action(स्थिर काष्ठा tc_action *a)
अणु
	वापस to_ct_params(a)->ct_action;
पूर्ण

अटल अंतरभूत काष्ठा nf_flowtable *tcf_ct_ft(स्थिर काष्ठा tc_action *a)
अणु
	वापस to_ct_params(a)->nf_ft;
पूर्ण

#अन्यथा
अटल अंतरभूत uपूर्णांक16_t tcf_ct_zone(स्थिर काष्ठा tc_action *a) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक tcf_ct_action(स्थिर काष्ठा tc_action *a) अणु वापस 0; पूर्ण
अटल अंतरभूत काष्ठा nf_flowtable *tcf_ct_ft(स्थिर काष्ठा tc_action *a)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK */

#अगर IS_ENABLED(CONFIG_NET_ACT_CT)
अटल अंतरभूत व्योम
tcf_ct_flow_table_restore_skb(काष्ठा sk_buff *skb, अचिन्हित दीर्घ cookie)
अणु
	क्रमागत ip_conntrack_info ctinfo = cookie & NFCT_INFOMASK;
	काष्ठा nf_conn *ct;

	ct = (काष्ठा nf_conn *)(cookie & NFCT_PTRMASK);
	nf_conntrack_get(&ct->ct_general);
	nf_ct_set(skb, ct, ctinfo);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
tcf_ct_flow_table_restore_skb(काष्ठा sk_buff *skb, अचिन्हित दीर्घ cookie) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool is_tcf_ct(स्थिर काष्ठा tc_action *a)
अणु
#अगर defined(CONFIG_NET_CLS_ACT) && IS_ENABLED(CONFIG_NF_CONNTRACK)
	अगर (a->ops && a->ops->id == TCA_ID_CT)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

#पूर्ण_अगर /* __NET_TC_CT_H */
