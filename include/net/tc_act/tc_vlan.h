<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014 Jiri Pirko <jiri@resnulli.us>
 */

#अगर_अघोषित __NET_TC_VLAN_H
#घोषणा __NET_TC_VLAN_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_vlan.h>

काष्ठा tcf_vlan_params अणु
	पूर्णांक               tcfv_action;
	अचिन्हित अक्षर     tcfv_push_dst[ETH_ALEN];
	अचिन्हित अक्षर     tcfv_push_src[ETH_ALEN];
	u16               tcfv_push_vid;
	__be16            tcfv_push_proto;
	u8                tcfv_push_prio;
	काष्ठा rcu_head   rcu;
पूर्ण;

काष्ठा tcf_vlan अणु
	काष्ठा tc_action	common;
	काष्ठा tcf_vlan_params __rcu *vlan_p;
पूर्ण;
#घोषणा to_vlan(a) ((काष्ठा tcf_vlan *)a)

अटल अंतरभूत bool is_tcf_vlan(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_VLAN)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत u32 tcf_vlan_action(स्थिर काष्ठा tc_action *a)
अणु
	u32 tcfv_action;

	rcu_पढ़ो_lock();
	tcfv_action = rcu_dereference(to_vlan(a)->vlan_p)->tcfv_action;
	rcu_पढ़ो_unlock();

	वापस tcfv_action;
पूर्ण

अटल अंतरभूत u16 tcf_vlan_push_vid(स्थिर काष्ठा tc_action *a)
अणु
	u16 tcfv_push_vid;

	rcu_पढ़ो_lock();
	tcfv_push_vid = rcu_dereference(to_vlan(a)->vlan_p)->tcfv_push_vid;
	rcu_पढ़ो_unlock();

	वापस tcfv_push_vid;
पूर्ण

अटल अंतरभूत __be16 tcf_vlan_push_proto(स्थिर काष्ठा tc_action *a)
अणु
	__be16 tcfv_push_proto;

	rcu_पढ़ो_lock();
	tcfv_push_proto = rcu_dereference(to_vlan(a)->vlan_p)->tcfv_push_proto;
	rcu_पढ़ो_unlock();

	वापस tcfv_push_proto;
पूर्ण

अटल अंतरभूत u8 tcf_vlan_push_prio(स्थिर काष्ठा tc_action *a)
अणु
	u8 tcfv_push_prio;

	rcu_पढ़ो_lock();
	tcfv_push_prio = rcu_dereference(to_vlan(a)->vlan_p)->tcfv_push_prio;
	rcu_पढ़ो_unlock();

	वापस tcfv_push_prio;
पूर्ण
#पूर्ण_अगर /* __NET_TC_VLAN_H */
