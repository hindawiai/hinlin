<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_MIR_H
#घोषणा __NET_TC_MIR_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_mirred.h>

काष्ठा tcf_mirred अणु
	काष्ठा tc_action	common;
	पूर्णांक			tcfm_eaction;
	bool			tcfm_mac_header_xmit;
	काष्ठा net_device __rcu	*tcfm_dev;
	काष्ठा list_head	tcfm_list;
पूर्ण;
#घोषणा to_mirred(a) ((काष्ठा tcf_mirred *)a)

अटल अंतरभूत bool is_tcf_mirred_egress_redirect(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_MIRRED)
		वापस to_mirred(a)->tcfm_eaction == TCA_EGRESS_REसूची;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत bool is_tcf_mirred_egress_mirror(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_MIRRED)
		वापस to_mirred(a)->tcfm_eaction == TCA_EGRESS_MIRROR;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत bool is_tcf_mirred_ingress_redirect(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_MIRRED)
		वापस to_mirred(a)->tcfm_eaction == TCA_INGRESS_REसूची;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत bool is_tcf_mirred_ingress_mirror(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_MIRRED)
		वापस to_mirred(a)->tcfm_eaction == TCA_INGRESS_MIRROR;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा net_device *tcf_mirred_dev(स्थिर काष्ठा tc_action *a)
अणु
	वापस rtnl_dereference(to_mirred(a)->tcfm_dev);
पूर्ण

#पूर्ण_अगर /* __NET_TC_MIR_H */
