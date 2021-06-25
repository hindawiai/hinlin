<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_CSUM_H
#घोषणा __NET_TC_CSUM_H

#समावेश <linux/types.h>
#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_csum.h>

काष्ठा tcf_csum_params अणु
	u32 update_flags;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा tcf_csum अणु
	काष्ठा tc_action common;

	काष्ठा tcf_csum_params __rcu *params;
पूर्ण;
#घोषणा to_tcf_csum(a) ((काष्ठा tcf_csum *)a)

अटल अंतरभूत bool is_tcf_csum(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_CSUM)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत u32 tcf_csum_update_flags(स्थिर काष्ठा tc_action *a)
अणु
	u32 update_flags;

	rcu_पढ़ो_lock();
	update_flags = rcu_dereference(to_tcf_csum(a)->params)->update_flags;
	rcu_पढ़ो_unlock();

	वापस update_flags;
पूर्ण

#पूर्ण_अगर /* __NET_TC_CSUM_H */
