<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#अगर_अघोषित _BR_PRIVATE_STP_H
#घोषणा _BR_PRIVATE_STP_H

#घोषणा BPDU_TYPE_CONFIG 0
#घोषणा BPDU_TYPE_TCN 0x80

/* IEEE 802.1D-1998 समयr values */
#घोषणा BR_MIN_HELLO_TIME	(1*HZ)
#घोषणा BR_MAX_HELLO_TIME	(10*HZ)

#घोषणा BR_MIN_FORWARD_DELAY	(2*HZ)
#घोषणा BR_MAX_FORWARD_DELAY	(30*HZ)

#घोषणा BR_MIN_MAX_AGE		(6*HZ)
#घोषणा BR_MAX_MAX_AGE		(40*HZ)

#घोषणा BR_MIN_PATH_COST	1
#घोषणा BR_MAX_PATH_COST	65535

काष्ठा br_config_bpdu अणु
	अचिन्हित पूर्णांक	topology_change:1;
	अचिन्हित पूर्णांक	topology_change_ack:1;
	bridge_id	root;
	पूर्णांक		root_path_cost;
	bridge_id	bridge_id;
	port_id		port_id;
	पूर्णांक		message_age;
	पूर्णांक		max_age;
	पूर्णांक		hello_समय;
	पूर्णांक		क्रमward_delay;
पूर्ण;

/* called under bridge lock */
अटल अंतरभूत पूर्णांक br_is_designated_port(स्थिर काष्ठा net_bridge_port *p)
अणु
	वापस !स_भेद(&p->designated_bridge, &p->br->bridge_id, 8) &&
		(p->designated_port == p->port_id);
पूर्ण


/* br_stp.c */
व्योम br_become_root_bridge(काष्ठा net_bridge *br);
व्योम br_config_bpdu_generation(काष्ठा net_bridge *);
व्योम br_configuration_update(काष्ठा net_bridge *);
व्योम br_port_state_selection(काष्ठा net_bridge *);
व्योम br_received_config_bpdu(काष्ठा net_bridge_port *p,
			     स्थिर काष्ठा br_config_bpdu *bpdu);
व्योम br_received_tcn_bpdu(काष्ठा net_bridge_port *p);
व्योम br_transmit_config(काष्ठा net_bridge_port *p);
व्योम br_transmit_tcn(काष्ठा net_bridge *br);
व्योम br_topology_change_detection(काष्ठा net_bridge *br);
व्योम __br_set_topology_change(काष्ठा net_bridge *br, अचिन्हित अक्षर val);

/* br_stp_bpdu.c */
व्योम br_send_config_bpdu(काष्ठा net_bridge_port *, काष्ठा br_config_bpdu *);
व्योम br_send_tcn_bpdu(काष्ठा net_bridge_port *);

#पूर्ण_अगर
