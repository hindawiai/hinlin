<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2008, Intel Corporation.
 *
 * Author: Alexander Duyck <alexander.h.duyck@पूर्णांकel.com>
 */

#अगर_अघोषित __NET_TC_SKBEDIT_H
#घोषणा __NET_TC_SKBEDIT_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_skbedit.h>

काष्ठा tcf_skbedit_params अणु
	u32 flags;
	u32 priority;
	u32 mark;
	u32 mask;
	u16 queue_mapping;
	u16 ptype;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा tcf_skbedit अणु
	काष्ठा tc_action common;
	काष्ठा tcf_skbedit_params __rcu *params;
पूर्ण;
#घोषणा to_skbedit(a) ((काष्ठा tcf_skbedit *)a)

/* Return true अगरf action is the one identअगरied by FLAG. */
अटल अंतरभूत bool is_tcf_skbedit_with_flag(स्थिर काष्ठा tc_action *a, u32 flag)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	u32 flags;

	अगर (a->ops && a->ops->id == TCA_ID_SKBEDIT) अणु
		rcu_पढ़ो_lock();
		flags = rcu_dereference(to_skbedit(a)->params)->flags;
		rcu_पढ़ो_unlock();
		वापस flags == flag;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

/* Return true अगरf action is mark */
अटल अंतरभूत bool is_tcf_skbedit_mark(स्थिर काष्ठा tc_action *a)
अणु
	वापस is_tcf_skbedit_with_flag(a, SKBEDIT_F_MARK);
पूर्ण

अटल अंतरभूत u32 tcf_skbedit_mark(स्थिर काष्ठा tc_action *a)
अणु
	u32 mark;

	rcu_पढ़ो_lock();
	mark = rcu_dereference(to_skbedit(a)->params)->mark;
	rcu_पढ़ो_unlock();

	वापस mark;
पूर्ण

/* Return true अगरf action is ptype */
अटल अंतरभूत bool is_tcf_skbedit_ptype(स्थिर काष्ठा tc_action *a)
अणु
	वापस is_tcf_skbedit_with_flag(a, SKBEDIT_F_PTYPE);
पूर्ण

अटल अंतरभूत u32 tcf_skbedit_ptype(स्थिर काष्ठा tc_action *a)
अणु
	u16 ptype;

	rcu_पढ़ो_lock();
	ptype = rcu_dereference(to_skbedit(a)->params)->ptype;
	rcu_पढ़ो_unlock();

	वापस ptype;
पूर्ण

/* Return true अगरf action is priority */
अटल अंतरभूत bool is_tcf_skbedit_priority(स्थिर काष्ठा tc_action *a)
अणु
	वापस is_tcf_skbedit_with_flag(a, SKBEDIT_F_PRIORITY);
पूर्ण

अटल अंतरभूत u32 tcf_skbedit_priority(स्थिर काष्ठा tc_action *a)
अणु
	u32 priority;

	rcu_पढ़ो_lock();
	priority = rcu_dereference(to_skbedit(a)->params)->priority;
	rcu_पढ़ो_unlock();

	वापस priority;
पूर्ण

#पूर्ण_अगर /* __NET_TC_SKBEDIT_H */
