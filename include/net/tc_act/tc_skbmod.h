<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2016, Jamal Hadi Salim
*/

#अगर_अघोषित __NET_TC_SKBMOD_H
#घोषणा __NET_TC_SKBMOD_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_skbmod.h>

काष्ठा tcf_skbmod_params अणु
	काष्ठा rcu_head	rcu;
	u64	flags; /*up to 64 types of operations; extend अगर needed */
	u8	eth_dst[ETH_ALEN];
	u16	eth_type;
	u8	eth_src[ETH_ALEN];
पूर्ण;

काष्ठा tcf_skbmod अणु
	काष्ठा tc_action	common;
	काष्ठा tcf_skbmod_params __rcu *skbmod_p;
पूर्ण;
#घोषणा to_skbmod(a) ((काष्ठा tcf_skbmod *)a)

#पूर्ण_अगर /* __NET_TC_SKBMOD_H */
