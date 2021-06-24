<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/net/चयनdev.h - Switch device API
 * Copyright (c) 2014-2015 Jiri Pirko <jiri@resnulli.us>
 * Copyright (c) 2014-2015 Scott Feldman <sfeldma@gmail.com>
 */
#अगर_अघोषित _LINUX_SWITCHDEV_H_
#घोषणा _LINUX_SWITCHDEV_H_

#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/list.h>
#समावेश <net/ip_fib.h>

#घोषणा SWITCHDEV_F_NO_RECURSE		BIT(0)
#घोषणा SWITCHDEV_F_SKIP_EOPNOTSUPP	BIT(1)
#घोषणा SWITCHDEV_F_DEFER		BIT(2)

क्रमागत चयनdev_attr_id अणु
	SWITCHDEV_ATTR_ID_UNDEFINED,
	SWITCHDEV_ATTR_ID_PORT_STP_STATE,
	SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS,
	SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS,
	SWITCHDEV_ATTR_ID_PORT_MROUTER,
	SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME,
	SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING,
	SWITCHDEV_ATTR_ID_BRIDGE_VLAN_PROTOCOL,
	SWITCHDEV_ATTR_ID_BRIDGE_MC_DISABLED,
	SWITCHDEV_ATTR_ID_BRIDGE_MROUTER,
	SWITCHDEV_ATTR_ID_MRP_PORT_ROLE,
पूर्ण;

काष्ठा चयनdev_brport_flags अणु
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ mask;
पूर्ण;

काष्ठा चयनdev_attr अणु
	काष्ठा net_device *orig_dev;
	क्रमागत चयनdev_attr_id id;
	u32 flags;
	व्योम *complete_priv;
	व्योम (*complete)(काष्ठा net_device *dev, पूर्णांक err, व्योम *priv);
	जोड़ अणु
		u8 stp_state;				/* PORT_STP_STATE */
		काष्ठा चयनdev_brport_flags brport_flags; /* PORT_BRIDGE_FLAGS */
		bool mrouter;				/* PORT_MROUTER */
		घड़ी_प्रकार ageing_समय;			/* BRIDGE_AGEING_TIME */
		bool vlan_filtering;			/* BRIDGE_VLAN_FILTERING */
		u16 vlan_protocol;			/* BRIDGE_VLAN_PROTOCOL */
		bool mc_disabled;			/* MC_DISABLED */
		u8 mrp_port_role;			/* MRP_PORT_ROLE */
	पूर्ण u;
पूर्ण;

क्रमागत चयनdev_obj_id अणु
	SWITCHDEV_OBJ_ID_UNDEFINED,
	SWITCHDEV_OBJ_ID_PORT_VLAN,
	SWITCHDEV_OBJ_ID_PORT_MDB,
	SWITCHDEV_OBJ_ID_HOST_MDB,
	SWITCHDEV_OBJ_ID_MRP,
	SWITCHDEV_OBJ_ID_RING_TEST_MRP,
	SWITCHDEV_OBJ_ID_RING_ROLE_MRP,
	SWITCHDEV_OBJ_ID_RING_STATE_MRP,
	SWITCHDEV_OBJ_ID_IN_TEST_MRP,
	SWITCHDEV_OBJ_ID_IN_ROLE_MRP,
	SWITCHDEV_OBJ_ID_IN_STATE_MRP,
पूर्ण;

काष्ठा चयनdev_obj अणु
	काष्ठा list_head list;
	काष्ठा net_device *orig_dev;
	क्रमागत चयनdev_obj_id id;
	u32 flags;
	व्योम *complete_priv;
	व्योम (*complete)(काष्ठा net_device *dev, पूर्णांक err, व्योम *priv);
पूर्ण;

/* SWITCHDEV_OBJ_ID_PORT_VLAN */
काष्ठा चयनdev_obj_port_vlan अणु
	काष्ठा चयनdev_obj obj;
	u16 flags;
	u16 vid;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_PORT_VLAN(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_port_vlan, obj)

/* SWITCHDEV_OBJ_ID_PORT_MDB */
काष्ठा चयनdev_obj_port_mdb अणु
	काष्ठा चयनdev_obj obj;
	अचिन्हित अक्षर addr[ETH_ALEN];
	u16 vid;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_PORT_MDB(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_port_mdb, obj)


/* SWITCHDEV_OBJ_ID_MRP */
काष्ठा चयनdev_obj_mrp अणु
	काष्ठा चयनdev_obj obj;
	काष्ठा net_device *p_port;
	काष्ठा net_device *s_port;
	u32 ring_id;
	u16 prio;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_MRP(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_mrp, obj)

/* SWITCHDEV_OBJ_ID_RING_TEST_MRP */
काष्ठा चयनdev_obj_ring_test_mrp अणु
	काष्ठा चयनdev_obj obj;
	/* The value is in us and a value of 0 represents to stop */
	u32 पूर्णांकerval;
	u8 max_miss;
	u32 ring_id;
	u32 period;
	bool monitor;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_RING_TEST_MRP(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_ring_test_mrp, obj)

/* SWICHDEV_OBJ_ID_RING_ROLE_MRP */
काष्ठा चयनdev_obj_ring_role_mrp अणु
	काष्ठा चयनdev_obj obj;
	u8 ring_role;
	u32 ring_id;
	u8 sw_backup;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_RING_ROLE_MRP(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_ring_role_mrp, obj)

काष्ठा चयनdev_obj_ring_state_mrp अणु
	काष्ठा चयनdev_obj obj;
	u8 ring_state;
	u32 ring_id;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_RING_STATE_MRP(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_ring_state_mrp, obj)

/* SWITCHDEV_OBJ_ID_IN_TEST_MRP */
काष्ठा चयनdev_obj_in_test_mrp अणु
	काष्ठा चयनdev_obj obj;
	/* The value is in us and a value of 0 represents to stop */
	u32 पूर्णांकerval;
	u32 in_id;
	u32 period;
	u8 max_miss;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_IN_TEST_MRP(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_in_test_mrp, obj)

/* SWICHDEV_OBJ_ID_IN_ROLE_MRP */
काष्ठा चयनdev_obj_in_role_mrp अणु
	काष्ठा चयनdev_obj obj;
	काष्ठा net_device *i_port;
	u32 ring_id;
	u16 in_id;
	u8 in_role;
	u8 sw_backup;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_IN_ROLE_MRP(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_in_role_mrp, obj)

काष्ठा चयनdev_obj_in_state_mrp अणु
	काष्ठा चयनdev_obj obj;
	u32 in_id;
	u8 in_state;
पूर्ण;

#घोषणा SWITCHDEV_OBJ_IN_STATE_MRP(OBJ) \
	container_of((OBJ), काष्ठा चयनdev_obj_in_state_mrp, obj)

प्रकार पूर्णांक चयनdev_obj_dump_cb_t(काष्ठा चयनdev_obj *obj);

क्रमागत चयनdev_notअगरier_type अणु
	SWITCHDEV_FDB_ADD_TO_BRIDGE = 1,
	SWITCHDEV_FDB_DEL_TO_BRIDGE,
	SWITCHDEV_FDB_ADD_TO_DEVICE,
	SWITCHDEV_FDB_DEL_TO_DEVICE,
	SWITCHDEV_FDB_OFFLOADED,
	SWITCHDEV_FDB_FLUSH_TO_BRIDGE,

	SWITCHDEV_PORT_OBJ_ADD, /* Blocking. */
	SWITCHDEV_PORT_OBJ_DEL, /* Blocking. */
	SWITCHDEV_PORT_ATTR_SET, /* May be blocking . */

	SWITCHDEV_VXLAN_FDB_ADD_TO_BRIDGE,
	SWITCHDEV_VXLAN_FDB_DEL_TO_BRIDGE,
	SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE,
	SWITCHDEV_VXLAN_FDB_DEL_TO_DEVICE,
	SWITCHDEV_VXLAN_FDB_OFFLOADED,
पूर्ण;

काष्ठा चयनdev_notअगरier_info अणु
	काष्ठा net_device *dev;
	काष्ठा netlink_ext_ack *extack;
पूर्ण;

काष्ठा चयनdev_notअगरier_fdb_info अणु
	काष्ठा चयनdev_notअगरier_info info; /* must be first */
	स्थिर अचिन्हित अक्षर *addr;
	u16 vid;
	u8 added_by_user:1,
	   is_local:1,
	   offloaded:1;
पूर्ण;

काष्ठा चयनdev_notअगरier_port_obj_info अणु
	काष्ठा चयनdev_notअगरier_info info; /* must be first */
	स्थिर काष्ठा चयनdev_obj *obj;
	bool handled;
पूर्ण;

काष्ठा चयनdev_notअगरier_port_attr_info अणु
	काष्ठा चयनdev_notअगरier_info info; /* must be first */
	स्थिर काष्ठा चयनdev_attr *attr;
	bool handled;
पूर्ण;

अटल अंतरभूत काष्ठा net_device *
चयनdev_notअगरier_info_to_dev(स्थिर काष्ठा चयनdev_notअगरier_info *info)
अणु
	वापस info->dev;
पूर्ण

अटल अंतरभूत काष्ठा netlink_ext_ack *
चयनdev_notअगरier_info_to_extack(स्थिर काष्ठा चयनdev_notअगरier_info *info)
अणु
	वापस info->extack;
पूर्ण

#अगर_घोषित CONFIG_NET_SWITCHDEV

व्योम चयनdev_deferred_process(व्योम);
पूर्णांक चयनdev_port_attr_set(काष्ठा net_device *dev,
			    स्थिर काष्ठा चयनdev_attr *attr,
			    काष्ठा netlink_ext_ack *extack);
पूर्णांक चयनdev_port_obj_add(काष्ठा net_device *dev,
			   स्थिर काष्ठा चयनdev_obj *obj,
			   काष्ठा netlink_ext_ack *extack);
पूर्णांक चयनdev_port_obj_del(काष्ठा net_device *dev,
			   स्थिर काष्ठा चयनdev_obj *obj);

पूर्णांक रेजिस्टर_चयनdev_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_चयनdev_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक call_चयनdev_notअगरiers(अचिन्हित दीर्घ val, काष्ठा net_device *dev,
			     काष्ठा चयनdev_notअगरier_info *info,
			     काष्ठा netlink_ext_ack *extack);

पूर्णांक रेजिस्टर_चयनdev_blocking_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_चयनdev_blocking_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक call_चयनdev_blocking_notअगरiers(अचिन्हित दीर्घ val, काष्ठा net_device *dev,
				      काष्ठा चयनdev_notअगरier_info *info,
				      काष्ठा netlink_ext_ack *extack);

व्योम चयनdev_port_fwd_mark_set(काष्ठा net_device *dev,
				 काष्ठा net_device *group_dev,
				 bool joining);

पूर्णांक चयनdev_handle_port_obj_add(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*add_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj,
				      काष्ठा netlink_ext_ack *extack));
पूर्णांक चयनdev_handle_port_obj_del(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*del_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj));

पूर्णांक चयनdev_handle_port_attr_set(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_attr_info *port_attr_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*set_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_attr *attr,
				      काष्ठा netlink_ext_ack *extack));
#अन्यथा

अटल अंतरभूत व्योम चयनdev_deferred_process(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक चयनdev_port_attr_set(काष्ठा net_device *dev,
					  स्थिर काष्ठा चयनdev_attr *attr,
					  काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक चयनdev_port_obj_add(काष्ठा net_device *dev,
					 स्थिर काष्ठा चयनdev_obj *obj,
					 काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक चयनdev_port_obj_del(काष्ठा net_device *dev,
					 स्थिर काष्ठा चयनdev_obj *obj)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक रेजिस्टर_चयनdev_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक unरेजिस्टर_चयनdev_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक call_चयनdev_notअगरiers(अचिन्हित दीर्घ val,
					   काष्ठा net_device *dev,
					   काष्ठा चयनdev_notअगरier_info *info,
					   काष्ठा netlink_ext_ack *extack)
अणु
	वापस NOTIFY_DONE;
पूर्ण

अटल अंतरभूत पूर्णांक
रेजिस्टर_चयनdev_blocking_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
unरेजिस्टर_चयनdev_blocking_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
call_चयनdev_blocking_notअगरiers(अचिन्हित दीर्घ val,
				  काष्ठा net_device *dev,
				  काष्ठा चयनdev_notअगरier_info *info,
				  काष्ठा netlink_ext_ack *extack)
अणु
	वापस NOTIFY_DONE;
पूर्ण

अटल अंतरभूत पूर्णांक
चयनdev_handle_port_obj_add(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*add_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj,
				      काष्ठा netlink_ext_ack *extack))
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
चयनdev_handle_port_obj_del(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_obj_info *port_obj_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*del_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_obj *obj))
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
चयनdev_handle_port_attr_set(काष्ठा net_device *dev,
			काष्ठा चयनdev_notअगरier_port_attr_info *port_attr_info,
			bool (*check_cb)(स्थिर काष्ठा net_device *dev),
			पूर्णांक (*set_cb)(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_attr *attr,
				      काष्ठा netlink_ext_ack *extack))
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SWITCHDEV_H_ */
