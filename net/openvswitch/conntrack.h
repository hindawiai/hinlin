<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 Nicira, Inc.
 */

#अगर_अघोषित OVS_CONNTRACK_H
#घोषणा OVS_CONNTRACK_H 1

#समावेश "flow.h"

काष्ठा ovs_conntrack_info;
काष्ठा ovs_ct_limit_info;
क्रमागत ovs_key_attr;

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
पूर्णांक ovs_ct_init(काष्ठा net *);
व्योम ovs_ct_निकास(काष्ठा net *);
bool ovs_ct_verअगरy(काष्ठा net *, क्रमागत ovs_key_attr attr);
पूर्णांक ovs_ct_copy_action(काष्ठा net *, स्थिर काष्ठा nlattr *,
		       स्थिर काष्ठा sw_flow_key *, काष्ठा sw_flow_actions **,
		       bool log);
पूर्णांक ovs_ct_action_to_attr(स्थिर काष्ठा ovs_conntrack_info *, काष्ठा sk_buff *);

पूर्णांक ovs_ct_execute(काष्ठा net *, काष्ठा sk_buff *, काष्ठा sw_flow_key *,
		   स्थिर काष्ठा ovs_conntrack_info *);
पूर्णांक ovs_ct_clear(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key);

व्योम ovs_ct_fill_key(स्थिर काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key,
		     bool post_ct);
पूर्णांक ovs_ct_put_key(स्थिर काष्ठा sw_flow_key *swkey,
		   स्थिर काष्ठा sw_flow_key *output, काष्ठा sk_buff *skb);
व्योम ovs_ct_मुक्त_action(स्थिर काष्ठा nlattr *a);

#घोषणा CT_SUPPORTED_MASK (OVS_CS_F_NEW | OVS_CS_F_ESTABLISHED | \
			   OVS_CS_F_RELATED | OVS_CS_F_REPLY_सूची | \
			   OVS_CS_F_INVALID | OVS_CS_F_TRACKED | \
			   OVS_CS_F_SRC_NAT | OVS_CS_F_DST_NAT)
#अन्यथा
#समावेश <linux/त्रुटिसं.स>

अटल अंतरभूत पूर्णांक ovs_ct_init(काष्ठा net *net) अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम ovs_ct_निकास(काष्ठा net *net) अणु पूर्ण

अटल अंतरभूत bool ovs_ct_verअगरy(काष्ठा net *net, पूर्णांक attr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक ovs_ct_copy_action(काष्ठा net *net, स्थिर काष्ठा nlattr *nla,
				     स्थिर काष्ठा sw_flow_key *key,
				     काष्ठा sw_flow_actions **acts, bool log)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ovs_ct_action_to_attr(स्थिर काष्ठा ovs_conntrack_info *info,
					काष्ठा sk_buff *skb)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ovs_ct_execute(काष्ठा net *net, काष्ठा sk_buff *skb,
				 काष्ठा sw_flow_key *key,
				 स्थिर काष्ठा ovs_conntrack_info *info)
अणु
	kमुक्त_skb(skb);
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ovs_ct_clear(काष्ठा sk_buff *skb,
			       काष्ठा sw_flow_key *key)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ovs_ct_fill_key(स्थिर काष्ठा sk_buff *skb,
				   काष्ठा sw_flow_key *key,
				   bool post_ct)
अणु
	key->ct_state = 0;
	key->ct_zone = 0;
	key->ct.mark = 0;
	स_रखो(&key->ct.labels, 0, माप(key->ct.labels));
	/* Clear 'ct_orig_proto' to mark the non-existence of original
	 * direction key fields.
	 */
	key->ct_orig_proto = 0;
पूर्ण

अटल अंतरभूत पूर्णांक ovs_ct_put_key(स्थिर काष्ठा sw_flow_key *swkey,
				 स्थिर काष्ठा sw_flow_key *output,
				 काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ovs_ct_मुक्त_action(स्थिर काष्ठा nlattr *a) अणु पूर्ण

#घोषणा CT_SUPPORTED_MASK 0
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK */

#अगर IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
बाह्य काष्ठा genl_family dp_ct_limit_genl_family;
#पूर्ण_अगर
#पूर्ण_अगर /* ovs_conntrack.h */
