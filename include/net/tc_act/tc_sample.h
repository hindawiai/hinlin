<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_SAMPLE_H
#घोषणा __NET_TC_SAMPLE_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_sample.h>
#समावेश <net/psample.h>

काष्ठा tcf_sample अणु
	काष्ठा tc_action common;
	u32 rate;
	bool truncate;
	u32 trunc_size;
	काष्ठा psample_group __rcu *psample_group;
	u32 psample_group_num;
	काष्ठा list_head tcfm_list;
पूर्ण;
#घोषणा to_sample(a) ((काष्ठा tcf_sample *)a)

अटल अंतरभूत bool is_tcf_sample(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	वापस a->ops && a->ops->id == TCA_ID_SAMPLE;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __u32 tcf_sample_rate(स्थिर काष्ठा tc_action *a)
अणु
	वापस to_sample(a)->rate;
पूर्ण

अटल अंतरभूत bool tcf_sample_truncate(स्थिर काष्ठा tc_action *a)
अणु
	वापस to_sample(a)->truncate;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_sample_trunc_size(स्थिर काष्ठा tc_action *a)
अणु
	वापस to_sample(a)->trunc_size;
पूर्ण

#पूर्ण_अगर /* __NET_TC_SAMPLE_H */
