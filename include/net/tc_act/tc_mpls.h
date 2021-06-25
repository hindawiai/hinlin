<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2019 Netronome Systems, Inc. */

#अगर_अघोषित __NET_TC_MPLS_H
#घोषणा __NET_TC_MPLS_H

#समावेश <linux/tc_act/tc_mpls.h>
#समावेश <net/act_api.h>

काष्ठा tcf_mpls_params अणु
	पूर्णांक tcfm_action;
	u32 tcfm_label;
	u8 tcfm_tc;
	u8 tcfm_ttl;
	u8 tcfm_bos;
	__be16 tcfm_proto;
	काष्ठा rcu_head	rcu;
पूर्ण;

#घोषणा ACT_MPLS_TC_NOT_SET	0xff
#घोषणा ACT_MPLS_BOS_NOT_SET	0xff
#घोषणा ACT_MPLS_LABEL_NOT_SET	0xffffffff

काष्ठा tcf_mpls अणु
	काष्ठा tc_action common;
	काष्ठा tcf_mpls_params __rcu *mpls_p;
पूर्ण;
#घोषणा to_mpls(a) ((काष्ठा tcf_mpls *)a)

अटल अंतरभूत bool is_tcf_mpls(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_MPLS)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत u32 tcf_mpls_action(स्थिर काष्ठा tc_action *a)
अणु
	u32 tcfm_action;

	rcu_पढ़ो_lock();
	tcfm_action = rcu_dereference(to_mpls(a)->mpls_p)->tcfm_action;
	rcu_पढ़ो_unlock();

	वापस tcfm_action;
पूर्ण

अटल अंतरभूत __be16 tcf_mpls_proto(स्थिर काष्ठा tc_action *a)
अणु
	__be16 tcfm_proto;

	rcu_पढ़ो_lock();
	tcfm_proto = rcu_dereference(to_mpls(a)->mpls_p)->tcfm_proto;
	rcu_पढ़ो_unlock();

	वापस tcfm_proto;
पूर्ण

अटल अंतरभूत u32 tcf_mpls_label(स्थिर काष्ठा tc_action *a)
अणु
	u32 tcfm_label;

	rcu_पढ़ो_lock();
	tcfm_label = rcu_dereference(to_mpls(a)->mpls_p)->tcfm_label;
	rcu_पढ़ो_unlock();

	वापस tcfm_label;
पूर्ण

अटल अंतरभूत u8 tcf_mpls_tc(स्थिर काष्ठा tc_action *a)
अणु
	u8 tcfm_tc;

	rcu_पढ़ो_lock();
	tcfm_tc = rcu_dereference(to_mpls(a)->mpls_p)->tcfm_tc;
	rcu_पढ़ो_unlock();

	वापस tcfm_tc;
पूर्ण

अटल अंतरभूत u8 tcf_mpls_bos(स्थिर काष्ठा tc_action *a)
अणु
	u8 tcfm_bos;

	rcu_पढ़ो_lock();
	tcfm_bos = rcu_dereference(to_mpls(a)->mpls_p)->tcfm_bos;
	rcu_पढ़ो_unlock();

	वापस tcfm_bos;
पूर्ण

अटल अंतरभूत u8 tcf_mpls_ttl(स्थिर काष्ठा tc_action *a)
अणु
	u8 tcfm_ttl;

	rcu_पढ़ो_lock();
	tcfm_ttl = rcu_dereference(to_mpls(a)->mpls_p)->tcfm_ttl;
	rcu_पढ़ो_unlock();

	वापस tcfm_ttl;
पूर्ण

#पूर्ण_अगर /* __NET_TC_MPLS_H */
