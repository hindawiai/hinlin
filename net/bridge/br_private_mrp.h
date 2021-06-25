<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#अगर_अघोषित _BR_PRIVATE_MRP_H_
#घोषणा _BR_PRIVATE_MRP_H_

#समावेश "br_private.h"
#समावेश <uapi/linux/mrp_bridge.h>

काष्ठा br_mrp अणु
	/* list of mrp instances */
	काष्ठा hlist_node		list;

	काष्ठा net_bridge_port __rcu	*p_port;
	काष्ठा net_bridge_port __rcu	*s_port;
	काष्ठा net_bridge_port __rcu	*i_port;

	u32				ring_id;
	u16				in_id;
	u16				prio;

	क्रमागत br_mrp_ring_role_type	ring_role;
	u8				ring_role_offloaded;
	क्रमागत br_mrp_ring_state_type	ring_state;
	u32				ring_transitions;

	क्रमागत br_mrp_in_role_type	in_role;
	u8				in_role_offloaded;
	क्रमागत br_mrp_in_state_type	in_state;
	u32				in_transitions;

	काष्ठा delayed_work		test_work;
	u32				test_पूर्णांकerval;
	अचिन्हित दीर्घ			test_end;
	u32				test_count_miss;
	u32				test_max_miss;
	bool				test_monitor;

	काष्ठा delayed_work		in_test_work;
	u32				in_test_पूर्णांकerval;
	अचिन्हित दीर्घ			in_test_end;
	u32				in_test_count_miss;
	u32				in_test_max_miss;

	u32				seq_id;

	काष्ठा rcu_head			rcu;
पूर्ण;

/* This type is वापसed by br_mrp_चयनdev functions that allow to have a SW
 * backup in हाल the HW can't implement completely the protocol.
 * BR_MRP_NONE - means the HW can't run at all the protocol, so the SW stops
 *               configuring the node anymore.
 * BR_MRP_SW - the HW can help the SW to run the protocol, by redirecting MRP
 *             frames to CPU.
 * BR_MRP_HW - the HW can implement completely the protocol.
 */
क्रमागत br_mrp_hw_support अणु
	BR_MRP_NONE,
	BR_MRP_SW,
	BR_MRP_HW,
पूर्ण;

/* br_mrp.c */
पूर्णांक br_mrp_add(काष्ठा net_bridge *br, काष्ठा br_mrp_instance *instance);
पूर्णांक br_mrp_del(काष्ठा net_bridge *br, काष्ठा br_mrp_instance *instance);
पूर्णांक br_mrp_set_port_state(काष्ठा net_bridge_port *p,
			  क्रमागत br_mrp_port_state_type state);
पूर्णांक br_mrp_set_port_role(काष्ठा net_bridge_port *p,
			 क्रमागत br_mrp_port_role_type role);
पूर्णांक br_mrp_set_ring_state(काष्ठा net_bridge *br,
			  काष्ठा br_mrp_ring_state *state);
पूर्णांक br_mrp_set_ring_role(काष्ठा net_bridge *br, काष्ठा br_mrp_ring_role *role);
पूर्णांक br_mrp_start_test(काष्ठा net_bridge *br, काष्ठा br_mrp_start_test *test);
पूर्णांक br_mrp_set_in_state(काष्ठा net_bridge *br, काष्ठा br_mrp_in_state *state);
पूर्णांक br_mrp_set_in_role(काष्ठा net_bridge *br, काष्ठा br_mrp_in_role *role);
पूर्णांक br_mrp_start_in_test(काष्ठा net_bridge *br,
			 काष्ठा br_mrp_start_in_test *test);

/* br_mrp_चयनdev.c */
पूर्णांक br_mrp_चयनdev_add(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp);
पूर्णांक br_mrp_चयनdev_del(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp);
क्रमागत br_mrp_hw_support
br_mrp_चयनdev_set_ring_role(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
			       क्रमागत br_mrp_ring_role_type role);
पूर्णांक br_mrp_चयनdev_set_ring_state(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
				    क्रमागत br_mrp_ring_state_type state);
क्रमागत br_mrp_hw_support
br_mrp_चयनdev_send_ring_test(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
				u32 पूर्णांकerval, u8 max_miss, u32 period,
				bool monitor);
पूर्णांक br_mrp_port_चयनdev_set_state(काष्ठा net_bridge_port *p, u32 state);
पूर्णांक br_mrp_port_चयनdev_set_role(काष्ठा net_bridge_port *p,
				   क्रमागत br_mrp_port_role_type role);
क्रमागत br_mrp_hw_support
br_mrp_चयनdev_set_in_role(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
			     u16 in_id, u32 ring_id,
			     क्रमागत br_mrp_in_role_type role);
पूर्णांक br_mrp_चयनdev_set_in_state(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
				  क्रमागत br_mrp_in_state_type state);
क्रमागत br_mrp_hw_support
br_mrp_चयनdev_send_in_test(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
			      u32 पूर्णांकerval, u8 max_miss, u32 period);

/* br_mrp_netlink.c  */
पूर्णांक br_mrp_ring_port_खोलो(काष्ठा net_device *dev, u8 loc);
पूर्णांक br_mrp_in_port_खोलो(काष्ठा net_device *dev, u8 loc);

/* MRP protocol data units */
काष्ठा br_mrp_tlv_hdr अणु
	__u8 type;
	__u8 length;
पूर्ण;

काष्ठा br_mrp_common_hdr अणु
	__be16 seq_id;
	__u8 करोमुख्य[MRP_DOMAIN_UUID_LENGTH];
पूर्ण;

काष्ठा br_mrp_ring_test_hdr अणु
	__be16 prio;
	__u8 sa[ETH_ALEN];
	__be16 port_role;
	__be16 state;
	__be16 transitions;
	__be32 बारtamp;
पूर्ण __attribute__((__packed__));

काष्ठा br_mrp_in_test_hdr अणु
	__be16 id;
	__u8 sa[ETH_ALEN];
	__be16 port_role;
	__be16 state;
	__be16 transitions;
	__be32 बारtamp;
पूर्ण __attribute__((__packed__));

#पूर्ण_अगर /* _BR_PRIVATE_MRP_H */
