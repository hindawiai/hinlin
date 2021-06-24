<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_CTINFO_H
#घोषणा __NET_TC_CTINFO_H

#समावेश <net/act_api.h>

काष्ठा tcf_ctinfo_params अणु
	काष्ठा rcu_head rcu;
	काष्ठा net *net;
	u32 dscpmask;
	u32 dscpstatemask;
	u32 cpmarkmask;
	u16 zone;
	u8 mode;
	u8 dscpmaskshअगरt;
पूर्ण;

काष्ठा tcf_ctinfo अणु
	काष्ठा tc_action common;
	काष्ठा tcf_ctinfo_params __rcu *params;
	u64 stats_dscp_set;
	u64 stats_dscp_error;
	u64 stats_cpmark_set;
पूर्ण;

क्रमागत अणु
	CTINFO_MODE_DSCP	= BIT(0),
	CTINFO_MODE_CPMARK	= BIT(1)
पूर्ण;

#घोषणा to_ctinfo(a) ((काष्ठा tcf_ctinfo *)a)

#पूर्ण_अगर /* __NET_TC_CTINFO_H */
