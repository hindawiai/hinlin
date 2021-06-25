<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2016, Amir Vadai <amir@vadai.me>
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित __NET_TC_TUNNEL_KEY_H
#घोषणा __NET_TC_TUNNEL_KEY_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_tunnel_key.h>
#समावेश <net/dst_metadata.h>

काष्ठा tcf_tunnel_key_params अणु
	काष्ठा rcu_head		rcu;
	पूर्णांक			tcft_action;
	काष्ठा metadata_dst     *tcft_enc_metadata;
पूर्ण;

काष्ठा tcf_tunnel_key अणु
	काष्ठा tc_action	      common;
	काष्ठा tcf_tunnel_key_params __rcu *params;
पूर्ण;

#घोषणा to_tunnel_key(a) ((काष्ठा tcf_tunnel_key *)a)

अटल अंतरभूत bool is_tcf_tunnel_set(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा tcf_tunnel_key *t = to_tunnel_key(a);
	काष्ठा tcf_tunnel_key_params *params;

	params = rcu_dereference_रक्षित(t->params,
					   lockdep_is_held(&a->tcfa_lock));
	अगर (a->ops && a->ops->id == TCA_ID_TUNNEL_KEY)
		वापस params->tcft_action == TCA_TUNNEL_KEY_ACT_SET;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत bool is_tcf_tunnel_release(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा tcf_tunnel_key *t = to_tunnel_key(a);
	काष्ठा tcf_tunnel_key_params *params;

	params = rcu_dereference_रक्षित(t->params,
					   lockdep_is_held(&a->tcfa_lock));
	अगर (a->ops && a->ops->id == TCA_ID_TUNNEL_KEY)
		वापस params->tcft_action == TCA_TUNNEL_KEY_ACT_RELEASE;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा ip_tunnel_info *tcf_tunnel_info(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा tcf_tunnel_key *t = to_tunnel_key(a);
	काष्ठा tcf_tunnel_key_params *params;

	params = rcu_dereference_रक्षित(t->params,
					   lockdep_is_held(&a->tcfa_lock));

	वापस &params->tcft_enc_metadata->u.tun_info;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा ip_tunnel_info *
tcf_tunnel_info_copy(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा ip_tunnel_info *tun = tcf_tunnel_info(a);

	अगर (tun) अणु
		माप_प्रकार tun_size = माप(*tun) + tun->options_len;
		काष्ठा ip_tunnel_info *tun_copy = kmemdup(tun, tun_size,
							  GFP_ATOMIC);

		वापस tun_copy;
	पूर्ण
#पूर्ण_अगर
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* __NET_TC_TUNNEL_KEY_H */
