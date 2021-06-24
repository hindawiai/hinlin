<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_GACT_H
#घोषणा __NET_TC_GACT_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_gact.h>

काष्ठा tcf_gact अणु
	काष्ठा tc_action	common;
#अगर_घोषित CONFIG_GACT_PROB
	u16			tcfg_ptype;
	u16			tcfg_pval;
	पूर्णांक			tcfg_paction;
	atomic_t		packets;
#पूर्ण_अगर
पूर्ण;
#घोषणा to_gact(a) ((काष्ठा tcf_gact *)a)

अटल अंतरभूत bool __is_tcf_gact_act(स्थिर काष्ठा tc_action *a, पूर्णांक act,
				     bool is_ext)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा tcf_gact *gact;

	अगर (a->ops && a->ops->id != TCA_ID_GACT)
		वापस false;

	gact = to_gact(a);
	अगर ((!is_ext && gact->tcf_action == act) ||
	    (is_ext && TC_ACT_EXT_CMP(gact->tcf_action, act)))
		वापस true;

#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत bool is_tcf_gact_ok(स्थिर काष्ठा tc_action *a)
अणु
	वापस __is_tcf_gact_act(a, TC_ACT_OK, false);
पूर्ण

अटल अंतरभूत bool is_tcf_gact_shot(स्थिर काष्ठा tc_action *a)
अणु
	वापस __is_tcf_gact_act(a, TC_ACT_SHOT, false);
पूर्ण

अटल अंतरभूत bool is_tcf_gact_trap(स्थिर काष्ठा tc_action *a)
अणु
	वापस __is_tcf_gact_act(a, TC_ACT_TRAP, false);
पूर्ण

अटल अंतरभूत bool is_tcf_gact_जाओ_chain(स्थिर काष्ठा tc_action *a)
अणु
	वापस __is_tcf_gact_act(a, TC_ACT_GOTO_CHAIN, true);
पूर्ण

अटल अंतरभूत u32 tcf_gact_जाओ_chain_index(स्थिर काष्ठा tc_action *a)
अणु
	वापस READ_ONCE(a->tcfa_action) & TC_ACT_EXT_VAL_MASK;
पूर्ण

#पूर्ण_अगर /* __NET_TC_GACT_H */
