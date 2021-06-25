<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2013
 *    Author(s): Eugene Crosser <eugene.crosser@ru.ibm.com>
 */

#अगर_अघोषित __QETH_L2_H__
#घोषणा __QETH_L2_H__

#समावेश "qeth_core.h"

बाह्य स्थिर काष्ठा attribute_group *qeth_l2_attr_groups[];

पूर्णांक qeth_bridgeport_query_ports(काष्ठा qeth_card *card,
				क्रमागत qeth_sbp_roles *role,
				क्रमागत qeth_sbp_states *state);
पूर्णांक qeth_bridgeport_setrole(काष्ठा qeth_card *card, क्रमागत qeth_sbp_roles role);
पूर्णांक qeth_bridgeport_an_set(काष्ठा qeth_card *card, पूर्णांक enable);

पूर्णांक qeth_l2_vnicc_set_state(काष्ठा qeth_card *card, u32 vnicc, bool state);
पूर्णांक qeth_l2_vnicc_get_state(काष्ठा qeth_card *card, u32 vnicc, bool *state);
पूर्णांक qeth_l2_vnicc_set_समयout(काष्ठा qeth_card *card, u32 समयout);
पूर्णांक qeth_l2_vnicc_get_समयout(काष्ठा qeth_card *card, u32 *समयout);
bool qeth_bridgeport_allowed(काष्ठा qeth_card *card);

काष्ठा qeth_mac अणु
	u8 mac_addr[ETH_ALEN];
	u8 disp_flag:2;
	काष्ठा hlist_node hnode;
पूर्ण;

अटल अंतरभूत bool qeth_bridgeport_is_in_use(काष्ठा qeth_card *card)
अणु
	वापस card->options.sbp.role ||
	       card->options.sbp.reflect_promisc ||
	       card->options.sbp.hostnotअगरication;
पूर्ण

#पूर्ण_अगर /* __QETH_L2_H__ */
