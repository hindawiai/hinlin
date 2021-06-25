<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <net/चयनdev.h>

#समावेश "br_private_mrp.h"

अटल क्रमागत br_mrp_hw_support
br_mrp_चयनdev_port_obj(काष्ठा net_bridge *br,
			  स्थिर काष्ठा चयनdev_obj *obj, bool add)
अणु
	पूर्णांक err;

	अगर (add)
		err = चयनdev_port_obj_add(br->dev, obj, शून्य);
	अन्यथा
		err = चयनdev_port_obj_del(br->dev, obj);

	/* In हाल of success just वापस and notअगरy the SW that करोesn't need
	 * to करो anything
	 */
	अगर (!err)
		वापस BR_MRP_HW;

	अगर (err != -EOPNOTSUPP)
		वापस BR_MRP_NONE;

	/* Continue with SW backup */
	वापस BR_MRP_SW;
पूर्ण

पूर्णांक br_mrp_चयनdev_add(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp)
अणु
	काष्ठा चयनdev_obj_mrp mrp_obj = अणु
		.obj.orig_dev = br->dev,
		.obj.id = SWITCHDEV_OBJ_ID_MRP,
		.p_port = rtnl_dereference(mrp->p_port)->dev,
		.s_port = rtnl_dereference(mrp->s_port)->dev,
		.ring_id = mrp->ring_id,
		.prio = mrp->prio,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस 0;

	वापस चयनdev_port_obj_add(br->dev, &mrp_obj.obj, शून्य);
पूर्ण

पूर्णांक br_mrp_चयनdev_del(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp)
अणु
	काष्ठा चयनdev_obj_mrp mrp_obj = अणु
		.obj.orig_dev = br->dev,
		.obj.id = SWITCHDEV_OBJ_ID_MRP,
		.p_port = शून्य,
		.s_port = शून्य,
		.ring_id = mrp->ring_id,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस 0;

	वापस चयनdev_port_obj_del(br->dev, &mrp_obj.obj);
पूर्ण

क्रमागत br_mrp_hw_support
br_mrp_चयनdev_set_ring_role(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
			       क्रमागत br_mrp_ring_role_type role)
अणु
	काष्ठा चयनdev_obj_ring_role_mrp mrp_role = अणु
		.obj.orig_dev = br->dev,
		.obj.id = SWITCHDEV_OBJ_ID_RING_ROLE_MRP,
		.ring_role = role,
		.ring_id = mrp->ring_id,
		.sw_backup = false,
	पूर्ण;
	क्रमागत br_mrp_hw_support support;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस BR_MRP_SW;

	support = br_mrp_चयनdev_port_obj(br, &mrp_role.obj,
					    role != BR_MRP_RING_ROLE_DISABLED);
	अगर (support != BR_MRP_SW)
		वापस support;

	/* If the driver can't configure to run completely the protocol in HW,
	 * then try again to configure the HW so the SW can run the protocol.
	 */
	mrp_role.sw_backup = true;
	अगर (role != BR_MRP_RING_ROLE_DISABLED)
		err = चयनdev_port_obj_add(br->dev, &mrp_role.obj, शून्य);
	अन्यथा
		err = चयनdev_port_obj_del(br->dev, &mrp_role.obj);

	अगर (!err)
		वापस BR_MRP_SW;

	वापस BR_MRP_NONE;
पूर्ण

क्रमागत br_mrp_hw_support
br_mrp_चयनdev_send_ring_test(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
				u32 पूर्णांकerval, u8 max_miss, u32 period,
				bool monitor)
अणु
	काष्ठा चयनdev_obj_ring_test_mrp test = अणु
		.obj.orig_dev = br->dev,
		.obj.id = SWITCHDEV_OBJ_ID_RING_TEST_MRP,
		.पूर्णांकerval = पूर्णांकerval,
		.max_miss = max_miss,
		.ring_id = mrp->ring_id,
		.period = period,
		.monitor = monitor,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस BR_MRP_SW;

	वापस br_mrp_चयनdev_port_obj(br, &test.obj, पूर्णांकerval != 0);
पूर्ण

पूर्णांक br_mrp_चयनdev_set_ring_state(काष्ठा net_bridge *br,
				    काष्ठा br_mrp *mrp,
				    क्रमागत br_mrp_ring_state_type state)
अणु
	काष्ठा चयनdev_obj_ring_state_mrp mrp_state = अणु
		.obj.orig_dev = br->dev,
		.obj.id = SWITCHDEV_OBJ_ID_RING_STATE_MRP,
		.ring_state = state,
		.ring_id = mrp->ring_id,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस 0;

	वापस चयनdev_port_obj_add(br->dev, &mrp_state.obj, शून्य);
पूर्ण

क्रमागत br_mrp_hw_support
br_mrp_चयनdev_set_in_role(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
			     u16 in_id, u32 ring_id,
			     क्रमागत br_mrp_in_role_type role)
अणु
	काष्ठा चयनdev_obj_in_role_mrp mrp_role = अणु
		.obj.orig_dev = br->dev,
		.obj.id = SWITCHDEV_OBJ_ID_IN_ROLE_MRP,
		.in_role = role,
		.in_id = mrp->in_id,
		.ring_id = mrp->ring_id,
		.i_port = rtnl_dereference(mrp->i_port)->dev,
		.sw_backup = false,
	पूर्ण;
	क्रमागत br_mrp_hw_support support;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस BR_MRP_SW;

	support = br_mrp_चयनdev_port_obj(br, &mrp_role.obj,
					    role != BR_MRP_IN_ROLE_DISABLED);
	अगर (support != BR_MRP_NONE)
		वापस support;

	/* If the driver can't configure to run completely the protocol in HW,
	 * then try again to configure the HW so the SW can run the protocol.
	 */
	mrp_role.sw_backup = true;
	अगर (role != BR_MRP_IN_ROLE_DISABLED)
		err = चयनdev_port_obj_add(br->dev, &mrp_role.obj, शून्य);
	अन्यथा
		err = चयनdev_port_obj_del(br->dev, &mrp_role.obj);

	अगर (!err)
		वापस BR_MRP_SW;

	वापस BR_MRP_NONE;
पूर्ण

पूर्णांक br_mrp_चयनdev_set_in_state(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
				  क्रमागत br_mrp_in_state_type state)
अणु
	काष्ठा चयनdev_obj_in_state_mrp mrp_state = अणु
		.obj.orig_dev = br->dev,
		.obj.id = SWITCHDEV_OBJ_ID_IN_STATE_MRP,
		.in_state = state,
		.in_id = mrp->in_id,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस 0;

	वापस चयनdev_port_obj_add(br->dev, &mrp_state.obj, शून्य);
पूर्ण

क्रमागत br_mrp_hw_support
br_mrp_चयनdev_send_in_test(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp,
			      u32 पूर्णांकerval, u8 max_miss, u32 period)
अणु
	काष्ठा चयनdev_obj_in_test_mrp test = अणु
		.obj.orig_dev = br->dev,
		.obj.id = SWITCHDEV_OBJ_ID_IN_TEST_MRP,
		.पूर्णांकerval = पूर्णांकerval,
		.max_miss = max_miss,
		.in_id = mrp->in_id,
		.period = period,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस BR_MRP_SW;

	वापस br_mrp_चयनdev_port_obj(br, &test.obj, पूर्णांकerval != 0);
पूर्ण

पूर्णांक br_mrp_port_चयनdev_set_state(काष्ठा net_bridge_port *p, u32 state)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_PORT_STP_STATE,
		.u.stp_state = state,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस 0;

	वापस चयनdev_port_attr_set(p->dev, &attr, शून्य);
पूर्ण

पूर्णांक br_mrp_port_चयनdev_set_role(काष्ठा net_bridge_port *p,
				   क्रमागत br_mrp_port_role_type role)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = p->dev,
		.id = SWITCHDEV_ATTR_ID_MRP_PORT_ROLE,
		.u.mrp_port_role = role,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_NET_SWITCHDEV))
		वापस 0;

	वापस चयनdev_port_attr_set(p->dev, &attr, शून्य);
पूर्ण
