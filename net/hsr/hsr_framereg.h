<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * include file क्रम HSR and PRP.
 */

#अगर_अघोषित __HSR_FRAMEREG_H
#घोषणा __HSR_FRAMEREG_H

#समावेश "hsr_main.h"

काष्ठा hsr_node;

काष्ठा hsr_frame_info अणु
	काष्ठा sk_buff *skb_std;
	काष्ठा sk_buff *skb_hsr;
	काष्ठा sk_buff *skb_prp;
	काष्ठा hsr_port *port_rcv;
	काष्ठा hsr_node *node_src;
	u16 sequence_nr;
	bool is_supervision;
	bool is_vlan;
	bool is_local_dest;
	bool is_local_exclusive;
	bool is_from_san;
पूर्ण;

व्योम hsr_del_self_node(काष्ठा hsr_priv *hsr);
व्योम hsr_del_nodes(काष्ठा list_head *node_db);
काष्ठा hsr_node *hsr_get_node(काष्ठा hsr_port *port, काष्ठा list_head *node_db,
			      काष्ठा sk_buff *skb, bool is_sup,
			      क्रमागत hsr_port_type rx_port);
व्योम hsr_handle_sup_frame(काष्ठा hsr_frame_info *frame);
bool hsr_addr_is_self(काष्ठा hsr_priv *hsr, अचिन्हित अक्षर *addr);

व्योम hsr_addr_subst_source(काष्ठा hsr_node *node, काष्ठा sk_buff *skb);
व्योम hsr_addr_subst_dest(काष्ठा hsr_node *node_src, काष्ठा sk_buff *skb,
			 काष्ठा hsr_port *port);

व्योम hsr_रेजिस्टर_frame_in(काष्ठा hsr_node *node, काष्ठा hsr_port *port,
			   u16 sequence_nr);
पूर्णांक hsr_रेजिस्टर_frame_out(काष्ठा hsr_port *port, काष्ठा hsr_node *node,
			   u16 sequence_nr);

व्योम hsr_prune_nodes(काष्ठा समयr_list *t);

पूर्णांक hsr_create_self_node(काष्ठा hsr_priv *hsr,
			 अचिन्हित अक्षर addr_a[ETH_ALEN],
			 अचिन्हित अक्षर addr_b[ETH_ALEN]);

व्योम *hsr_get_next_node(काष्ठा hsr_priv *hsr, व्योम *_pos,
			अचिन्हित अक्षर addr[ETH_ALEN]);

पूर्णांक hsr_get_node_data(काष्ठा hsr_priv *hsr,
		      स्थिर अचिन्हित अक्षर *addr,
		      अचिन्हित अक्षर addr_b[ETH_ALEN],
		      अचिन्हित पूर्णांक *addr_b_अगरindex,
		      पूर्णांक *अगर1_age,
		      u16 *अगर1_seq,
		      पूर्णांक *अगर2_age,
		      u16 *अगर2_seq);

व्योम prp_handle_san_frame(bool san, क्रमागत hsr_port_type port,
			  काष्ठा hsr_node *node);
व्योम prp_update_san_info(काष्ठा hsr_node *node, bool is_sup);

काष्ठा hsr_node अणु
	काष्ठा list_head	mac_list;
	अचिन्हित अक्षर		macaddress_A[ETH_ALEN];
	अचिन्हित अक्षर		macaddress_B[ETH_ALEN];
	/* Local slave through which AddrB frames are received from this node */
	क्रमागत hsr_port_type	addr_B_port;
	अचिन्हित दीर्घ		समय_in[HSR_PT_PORTS];
	bool			समय_in_stale[HSR_PT_PORTS];
	अचिन्हित दीर्घ		समय_out[HSR_PT_PORTS];
	/* अगर the node is a SAN */
	bool			san_a;
	bool			san_b;
	u16			seq_out[HSR_PT_PORTS];
	काष्ठा rcu_head		rcu_head;
पूर्ण;

#पूर्ण_अगर /* __HSR_FRAMEREG_H */
