<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_NAT_H
#घोषणा __NET_TC_NAT_H

#समावेश <linux/types.h>
#समावेश <net/act_api.h>

काष्ठा tcf_nat अणु
	काष्ठा tc_action common;

	__be32 old_addr;
	__be32 new_addr;
	__be32 mask;
	u32 flags;
पूर्ण;

#घोषणा to_tcf_nat(a) ((काष्ठा tcf_nat *)a)

#पूर्ण_अगर /* __NET_TC_NAT_H */
