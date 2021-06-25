<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/net/dsa.h - Driver क्रम Distributed Switch Architecture चयन chips
 * Copyright (c) 2008-2009 Marvell Semiconductor
 */

#अगर_अघोषित __LINUX_NET_DSA_H
#घोषणा __LINUX_NET_DSA_H

#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_data/dsa.h>
#समावेश <linux/phylink.h>
#समावेश <net/devlink.h>
#समावेश <net/चयनdev.h>

काष्ठा tc_action;
काष्ठा phy_device;
काष्ठा fixed_phy_status;
काष्ठा phylink_link_state;

#घोषणा DSA_TAG_PROTO_NONE_VALUE		0
#घोषणा DSA_TAG_PROTO_BRCM_VALUE		1
#घोषणा DSA_TAG_PROTO_BRCM_PREPEND_VALUE	2
#घोषणा DSA_TAG_PROTO_DSA_VALUE			3
#घोषणा DSA_TAG_PROTO_EDSA_VALUE		4
#घोषणा DSA_TAG_PROTO_GSWIP_VALUE		5
#घोषणा DSA_TAG_PROTO_KSZ9477_VALUE		6
#घोषणा DSA_TAG_PROTO_KSZ9893_VALUE		7
#घोषणा DSA_TAG_PROTO_LAN9303_VALUE		8
#घोषणा DSA_TAG_PROTO_MTK_VALUE			9
#घोषणा DSA_TAG_PROTO_QCA_VALUE			10
#घोषणा DSA_TAG_PROTO_TRAILER_VALUE		11
#घोषणा DSA_TAG_PROTO_8021Q_VALUE		12
#घोषणा DSA_TAG_PROTO_SJA1105_VALUE		13
#घोषणा DSA_TAG_PROTO_KSZ8795_VALUE		14
#घोषणा DSA_TAG_PROTO_OCELOT_VALUE		15
#घोषणा DSA_TAG_PROTO_AR9331_VALUE		16
#घोषणा DSA_TAG_PROTO_RTL4_A_VALUE		17
#घोषणा DSA_TAG_PROTO_HELLCREEK_VALUE		18
#घोषणा DSA_TAG_PROTO_XRS700X_VALUE		19
#घोषणा DSA_TAG_PROTO_OCELOT_8021Q_VALUE	20
#घोषणा DSA_TAG_PROTO_SEVILLE_VALUE		21
#घोषणा DSA_TAG_PROTO_BRCM_LEGACY_VALUE		22

क्रमागत dsa_tag_protocol अणु
	DSA_TAG_PROTO_NONE		= DSA_TAG_PROTO_NONE_VALUE,
	DSA_TAG_PROTO_BRCM		= DSA_TAG_PROTO_BRCM_VALUE,
	DSA_TAG_PROTO_BRCM_LEGACY	= DSA_TAG_PROTO_BRCM_LEGACY_VALUE,
	DSA_TAG_PROTO_BRCM_PREPEND	= DSA_TAG_PROTO_BRCM_PREPEND_VALUE,
	DSA_TAG_PROTO_DSA		= DSA_TAG_PROTO_DSA_VALUE,
	DSA_TAG_PROTO_EDSA		= DSA_TAG_PROTO_EDSA_VALUE,
	DSA_TAG_PROTO_GSWIP		= DSA_TAG_PROTO_GSWIP_VALUE,
	DSA_TAG_PROTO_KSZ9477		= DSA_TAG_PROTO_KSZ9477_VALUE,
	DSA_TAG_PROTO_KSZ9893		= DSA_TAG_PROTO_KSZ9893_VALUE,
	DSA_TAG_PROTO_LAN9303		= DSA_TAG_PROTO_LAN9303_VALUE,
	DSA_TAG_PROTO_MTK		= DSA_TAG_PROTO_MTK_VALUE,
	DSA_TAG_PROTO_QCA		= DSA_TAG_PROTO_QCA_VALUE,
	DSA_TAG_PROTO_TRAILER		= DSA_TAG_PROTO_TRAILER_VALUE,
	DSA_TAG_PROTO_8021Q		= DSA_TAG_PROTO_8021Q_VALUE,
	DSA_TAG_PROTO_SJA1105		= DSA_TAG_PROTO_SJA1105_VALUE,
	DSA_TAG_PROTO_KSZ8795		= DSA_TAG_PROTO_KSZ8795_VALUE,
	DSA_TAG_PROTO_OCELOT		= DSA_TAG_PROTO_OCELOT_VALUE,
	DSA_TAG_PROTO_AR9331		= DSA_TAG_PROTO_AR9331_VALUE,
	DSA_TAG_PROTO_RTL4_A		= DSA_TAG_PROTO_RTL4_A_VALUE,
	DSA_TAG_PROTO_HELLCREEK		= DSA_TAG_PROTO_HELLCREEK_VALUE,
	DSA_TAG_PROTO_XRS700X		= DSA_TAG_PROTO_XRS700X_VALUE,
	DSA_TAG_PROTO_OCELOT_8021Q	= DSA_TAG_PROTO_OCELOT_8021Q_VALUE,
	DSA_TAG_PROTO_SEVILLE		= DSA_TAG_PROTO_SEVILLE_VALUE,
पूर्ण;

काष्ठा packet_type;
काष्ठा dsa_चयन;

काष्ठा dsa_device_ops अणु
	काष्ठा sk_buff *(*xmit)(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
	काष्ठा sk_buff *(*rcv)(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			       काष्ठा packet_type *pt);
	व्योम (*flow_dissect)(स्थिर काष्ठा sk_buff *skb, __be16 *proto,
			     पूर्णांक *offset);
	/* Used to determine which traffic should match the DSA filter in
	 * eth_type_trans, and which, अगर any, should bypass it and be processed
	 * as regular on the master net device.
	 */
	bool (*filter)(स्थिर काष्ठा sk_buff *skb, काष्ठा net_device *dev);
	अचिन्हित पूर्णांक overhead;
	स्थिर अक्षर *name;
	क्रमागत dsa_tag_protocol proto;
	/* Some tagging protocols either mangle or shअगरt the destination MAC
	 * address, in which हाल the DSA master would drop packets on ingress
	 * अगर what it understands out of the destination MAC address is not in
	 * its RX filter.
	 */
	bool promisc_on_master;
	bool tail_tag;
पूर्ण;

/* This काष्ठाure defines the control पूर्णांकerfaces that are overlayed by the
 * DSA layer on top of the DSA CPU/management net_device instance. This is
 * used by the core net_device layer जबतक calling various net_device_ops
 * function poपूर्णांकers.
 */
काष्ठा dsa_netdevice_ops अणु
	पूर्णांक (*nकरो_करो_ioctl)(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
			    पूर्णांक cmd);
पूर्ण;

#घोषणा DSA_TAG_DRIVER_ALIAS "dsa_tag-"
#घोषणा MODULE_ALIAS_DSA_TAG_DRIVER(__proto)				\
	MODULE_ALIAS(DSA_TAG_DRIVER_ALIAS __stringअगरy(__proto##_VALUE))

काष्ठा dsa_चयन_tree अणु
	काष्ठा list_head	list;

	/* Notअगरier chain क्रम चयन-wide events */
	काष्ठा raw_notअगरier_head	nh;

	/* Tree identअगरier */
	अचिन्हित पूर्णांक index;

	/* Number of चयनes attached to this tree */
	काष्ठा kref refcount;

	/* Has this tree been applied to the hardware? */
	bool setup;

	/* Tagging protocol operations */
	स्थिर काष्ठा dsa_device_ops *tag_ops;

	/* Default tagging protocol preferred by the चयनes in this
	 * tree.
	 */
	क्रमागत dsa_tag_protocol शेष_proto;

	/*
	 * Configuration data क्रम the platक्रमm device that owns
	 * this dsa चयन tree instance.
	 */
	काष्ठा dsa_platक्रमm_data	*pd;

	/* List of चयन ports */
	काष्ठा list_head ports;

	/* List of DSA links composing the routing table */
	काष्ठा list_head rtable;

	/* Maps offloaded LAG netdevs to a zero-based linear ID क्रम
	 * drivers that need it.
	 */
	काष्ठा net_device **lags;
	अचिन्हित पूर्णांक lags_len;
पूर्ण;

#घोषणा dsa_lags_क्रमeach_id(_id, _dst)				\
	क्रम ((_id) = 0; (_id) < (_dst)->lags_len; (_id)++)	\
		अगर ((_dst)->lags[(_id)])

#घोषणा dsa_lag_क्रमeach_port(_dp, _dst, _lag)			\
	list_क्रम_each_entry((_dp), &(_dst)->ports, list)	\
		अगर ((_dp)->lag_dev == (_lag))

#घोषणा dsa_hsr_क्रमeach_port(_dp, _ds, _hsr)			\
	list_क्रम_each_entry((_dp), &(_ds)->dst->ports, list)	\
		अगर ((_dp)->ds == (_ds) && (_dp)->hsr_dev == (_hsr))

अटल अंतरभूत काष्ठा net_device *dsa_lag_dev(काष्ठा dsa_चयन_tree *dst,
					     अचिन्हित पूर्णांक id)
अणु
	वापस dst->lags[id];
पूर्ण

अटल अंतरभूत पूर्णांक dsa_lag_id(काष्ठा dsa_चयन_tree *dst,
			     काष्ठा net_device *lag)
अणु
	अचिन्हित पूर्णांक id;

	dsa_lags_क्रमeach_id(id, dst) अणु
		अगर (dsa_lag_dev(dst, id) == lag)
			वापस id;
	पूर्ण

	वापस -ENODEV;
पूर्ण

/* TC matchall action types */
क्रमागत dsa_port_mall_action_type अणु
	DSA_PORT_MALL_MIRROR,
	DSA_PORT_MALL_POLICER,
पूर्ण;

/* TC mirroring entry */
काष्ठा dsa_mall_mirror_tc_entry अणु
	u8 to_local_port;
	bool ingress;
पूर्ण;

/* TC port policer entry */
काष्ठा dsa_mall_policer_tc_entry अणु
	u32 burst;
	u64 rate_bytes_per_sec;
पूर्ण;

/* TC matchall entry */
काष्ठा dsa_mall_tc_entry अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ cookie;
	क्रमागत dsa_port_mall_action_type type;
	जोड़ अणु
		काष्ठा dsa_mall_mirror_tc_entry mirror;
		काष्ठा dsa_mall_policer_tc_entry policer;
	पूर्ण;
पूर्ण;


काष्ठा dsa_port अणु
	/* A CPU port is physically connected to a master device.
	 * A user port exposed to userspace has a slave device.
	 */
	जोड़ अणु
		काष्ठा net_device *master;
		काष्ठा net_device *slave;
	पूर्ण;

	/* Copy of the tagging protocol operations, क्रम quicker access
	 * in the data path. Valid only क्रम the CPU ports.
	 */
	स्थिर काष्ठा dsa_device_ops *tag_ops;

	/* Copies क्रम faster access in master receive hot path */
	काष्ठा dsa_चयन_tree *dst;
	काष्ठा sk_buff *(*rcv)(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			       काष्ठा packet_type *pt);
	bool (*filter)(स्थिर काष्ठा sk_buff *skb, काष्ठा net_device *dev);

	क्रमागत अणु
		DSA_PORT_TYPE_UNUSED = 0,
		DSA_PORT_TYPE_CPU,
		DSA_PORT_TYPE_DSA,
		DSA_PORT_TYPE_USER,
	पूर्ण type;

	काष्ठा dsa_चयन	*ds;
	अचिन्हित पूर्णांक		index;
	स्थिर अक्षर		*name;
	काष्ठा dsa_port		*cpu_dp;
	u8			mac[ETH_ALEN];
	काष्ठा device_node	*dn;
	अचिन्हित पूर्णांक		ageing_समय;
	bool			vlan_filtering;
	u8			stp_state;
	काष्ठा net_device	*bridge_dev;
	काष्ठा devlink_port	devlink_port;
	bool			devlink_port_setup;
	काष्ठा phylink		*pl;
	काष्ठा phylink_config	pl_config;
	काष्ठा net_device	*lag_dev;
	bool			lag_tx_enabled;
	काष्ठा net_device	*hsr_dev;

	काष्ठा list_head list;

	/*
	 * Give the चयन driver somewhere to hang its per-port निजी data
	 * काष्ठाures (accessible from the tagger).
	 */
	व्योम *priv;

	/*
	 * Original copy of the master netdev ethtool_ops
	 */
	स्थिर काष्ठा ethtool_ops *orig_ethtool_ops;

	/*
	 * Original copy of the master netdev net_device_ops
	 */
	स्थिर काष्ठा dsa_netdevice_ops *netdev_ops;

	bool setup;
पूर्ण;

/* TODO: ideally DSA ports would have a single dp->link_dp member,
 * and no dst->rtable nor this काष्ठा dsa_link would be needed,
 * but this would require some more complex tree walking,
 * so keep it stupid at the moment and list them all.
 */
काष्ठा dsa_link अणु
	काष्ठा dsa_port *dp;
	काष्ठा dsa_port *link_dp;
	काष्ठा list_head list;
पूर्ण;

काष्ठा dsa_चयन अणु
	bool setup;

	काष्ठा device *dev;

	/*
	 * Parent चयन tree, and चयन index.
	 */
	काष्ठा dsa_चयन_tree	*dst;
	अचिन्हित पूर्णांक		index;

	/* Listener क्रम चयन fabric events */
	काष्ठा notअगरier_block	nb;

	/*
	 * Give the चयन driver somewhere to hang its निजी data
	 * काष्ठाure.
	 */
	व्योम *priv;

	/*
	 * Configuration data क्रम this चयन.
	 */
	काष्ठा dsa_chip_data	*cd;

	/*
	 * The चयन operations.
	 */
	स्थिर काष्ठा dsa_चयन_ops	*ops;

	/*
	 * Slave mii_bus and devices क्रम the inभागidual ports.
	 */
	u32			phys_mii_mask;
	काष्ठा mii_bus		*slave_mii_bus;

	/* Ageing Time limits in msecs */
	अचिन्हित पूर्णांक ageing_समय_min;
	अचिन्हित पूर्णांक ageing_समय_max;

	/* devlink used to represent this चयन device */
	काष्ठा devlink		*devlink;

	/* Number of चयन port queues */
	अचिन्हित पूर्णांक		num_tx_queues;

	/* Disallow bridge core from requesting dअगरferent VLAN awareness
	 * settings on ports अगर not hardware-supported
	 */
	bool			vlan_filtering_is_global;

	/* Pass .port_vlan_add and .port_vlan_del to drivers even क्रम bridges
	 * that have vlan_filtering=0. All drivers should ideally set this (and
	 * then the option would get हटाओd), but it is unknown whether this
	 * would अवरोध things or not.
	 */
	bool			configure_vlan_जबतक_not_filtering;

	/* If the चयन driver always programs the CPU port as egress tagged
	 * despite the VLAN configuration indicating otherwise, then setting
	 * @untag_bridge_pvid will क्रमce the DSA receive path to pop the bridge's
	 * शेष_pvid VLAN tagged frames to offer a consistent behavior
	 * between a vlan_filtering=0 and vlan_filtering=1 bridge device.
	 */
	bool			untag_bridge_pvid;

	/* Let DSA manage the FDB entries towards the CPU, based on the
	 * software bridge database.
	 */
	bool			assisted_learning_on_cpu_port;

	/* In हाल vlan_filtering_is_global is set, the VLAN awareness state
	 * should be retrieved from here and not from the per-port settings.
	 */
	bool			vlan_filtering;

	/* MAC PCS करोes not provide link state change पूर्णांकerrupt, and requires
	 * polling. Flag passed on to PHYLINK.
	 */
	bool			pcs_poll;

	/* For चयनes that only have the MRU configurable. To ensure the
	 * configured MTU is not exceeded, normalization of MRU on all bridged
	 * पूर्णांकerfaces is needed.
	 */
	bool			mtu_enक्रमcement_ingress;

	/* Drivers that benefit from having an ID associated with each
	 * offloaded LAG should set this to the maximum number of
	 * supported IDs. DSA will then मुख्यtain a mapping of _at
	 * least_ these many IDs, accessible to drivers via
	 * dsa_lag_id().
	 */
	अचिन्हित पूर्णांक		num_lag_ids;

	माप_प्रकार num_ports;
पूर्ण;

अटल अंतरभूत काष्ठा dsa_port *dsa_to_port(काष्ठा dsa_चयन *ds, पूर्णांक p)
अणु
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dp->ds == ds && dp->index == p)
			वापस dp;

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool dsa_is_unused_port(काष्ठा dsa_चयन *ds, पूर्णांक p)
अणु
	वापस dsa_to_port(ds, p)->type == DSA_PORT_TYPE_UNUSED;
पूर्ण

अटल अंतरभूत bool dsa_is_cpu_port(काष्ठा dsa_चयन *ds, पूर्णांक p)
अणु
	वापस dsa_to_port(ds, p)->type == DSA_PORT_TYPE_CPU;
पूर्ण

अटल अंतरभूत bool dsa_is_dsa_port(काष्ठा dsa_चयन *ds, पूर्णांक p)
अणु
	वापस dsa_to_port(ds, p)->type == DSA_PORT_TYPE_DSA;
पूर्ण

अटल अंतरभूत bool dsa_is_user_port(काष्ठा dsa_चयन *ds, पूर्णांक p)
अणु
	वापस dsa_to_port(ds, p)->type == DSA_PORT_TYPE_USER;
पूर्ण

अटल अंतरभूत u32 dsa_user_ports(काष्ठा dsa_चयन *ds)
अणु
	u32 mask = 0;
	पूर्णांक p;

	क्रम (p = 0; p < ds->num_ports; p++)
		अगर (dsa_is_user_port(ds, p))
			mask |= BIT(p);

	वापस mask;
पूर्ण

/* Return the local port used to reach an arbitrary चयन device */
अटल अंतरभूत अचिन्हित पूर्णांक dsa_routing_port(काष्ठा dsa_चयन *ds, पूर्णांक device)
अणु
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	काष्ठा dsa_link *dl;

	list_क्रम_each_entry(dl, &dst->rtable, list)
		अगर (dl->dp->ds == ds && dl->link_dp->ds->index == device)
			वापस dl->dp->index;

	वापस ds->num_ports;
पूर्ण

/* Return the local port used to reach an arbitrary चयन port */
अटल अंतरभूत अचिन्हित पूर्णांक dsa_towards_port(काष्ठा dsa_चयन *ds, पूर्णांक device,
					    पूर्णांक port)
अणु
	अगर (device == ds->index)
		वापस port;
	अन्यथा
		वापस dsa_routing_port(ds, device);
पूर्ण

/* Return the local port used to reach the dedicated CPU port */
अटल अंतरभूत अचिन्हित पूर्णांक dsa_upstream_port(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	स्थिर काष्ठा dsa_port *dp = dsa_to_port(ds, port);
	स्थिर काष्ठा dsa_port *cpu_dp = dp->cpu_dp;

	अगर (!cpu_dp)
		वापस port;

	वापस dsa_towards_port(ds, cpu_dp->ds->index, cpu_dp->index);
पूर्ण

अटल अंतरभूत bool dsa_port_is_vlan_filtering(स्थिर काष्ठा dsa_port *dp)
अणु
	स्थिर काष्ठा dsa_चयन *ds = dp->ds;

	अगर (ds->vlan_filtering_is_global)
		वापस ds->vlan_filtering;
	अन्यथा
		वापस dp->vlan_filtering;
पूर्ण

अटल अंतरभूत
काष्ठा net_device *dsa_port_to_bridge_port(स्थिर काष्ठा dsa_port *dp)
अणु
	अगर (!dp->bridge_dev)
		वापस शून्य;

	अगर (dp->lag_dev)
		वापस dp->lag_dev;
	अन्यथा अगर (dp->hsr_dev)
		वापस dp->hsr_dev;

	वापस dp->slave;
पूर्ण

प्रकार पूर्णांक dsa_fdb_dump_cb_t(स्थिर अचिन्हित अक्षर *addr, u16 vid,
			      bool is_अटल, व्योम *data);
काष्ठा dsa_चयन_ops अणु
	/*
	 * Tagging protocol helpers called क्रम the CPU ports and DSA links.
	 * @get_tag_protocol retrieves the initial tagging protocol and is
	 * mandatory. Switches which can operate using multiple tagging
	 * protocols should implement @change_tag_protocol and report in
	 * @get_tag_protocol the tagger in current use.
	 */
	क्रमागत dsa_tag_protocol (*get_tag_protocol)(काष्ठा dsa_चयन *ds,
						  पूर्णांक port,
						  क्रमागत dsa_tag_protocol mprot);
	पूर्णांक	(*change_tag_protocol)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       क्रमागत dsa_tag_protocol proto);

	पूर्णांक	(*setup)(काष्ठा dsa_चयन *ds);
	व्योम	(*tearकरोwn)(काष्ठा dsa_चयन *ds);
	u32	(*get_phy_flags)(काष्ठा dsa_चयन *ds, पूर्णांक port);

	/*
	 * Access to the चयन's PHY रेजिस्टरs.
	 */
	पूर्णांक	(*phy_पढ़ो)(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum);
	पूर्णांक	(*phy_ग_लिखो)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     पूर्णांक regnum, u16 val);

	/*
	 * Link state adjusपंचांगent (called from libphy)
	 */
	व्योम	(*adjust_link)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा phy_device *phydev);
	व्योम	(*fixed_link_update)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा fixed_phy_status *st);

	/*
	 * PHYLINK पूर्णांकegration
	 */
	व्योम	(*phylink_validate)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    अचिन्हित दीर्घ *supported,
				    काष्ठा phylink_link_state *state);
	पूर्णांक	(*phylink_mac_link_state)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					  काष्ठा phylink_link_state *state);
	व्योम	(*phylink_mac_config)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      अचिन्हित पूर्णांक mode,
				      स्थिर काष्ठा phylink_link_state *state);
	व्योम	(*phylink_mac_an_restart)(काष्ठा dsa_चयन *ds, पूर्णांक port);
	व्योम	(*phylink_mac_link_करोwn)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 अचिन्हित पूर्णांक mode,
					 phy_पूर्णांकerface_t पूर्णांकerface);
	व्योम	(*phylink_mac_link_up)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       अचिन्हित पूर्णांक mode,
				       phy_पूर्णांकerface_t पूर्णांकerface,
				       काष्ठा phy_device *phydev,
				       पूर्णांक speed, पूर्णांक duplex,
				       bool tx_छोड़ो, bool rx_छोड़ो);
	व्योम	(*phylink_fixed_state)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       काष्ठा phylink_link_state *state);
	/*
	 * Port statistics counters.
	 */
	व्योम	(*get_strings)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       u32 stringset, uपूर्णांक8_t *data);
	व्योम	(*get_ethtool_stats)(काष्ठा dsa_चयन *ds,
				     पूर्णांक port, uपूर्णांक64_t *data);
	पूर्णांक	(*get_sset_count)(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset);
	व्योम	(*get_ethtool_phy_stats)(काष्ठा dsa_चयन *ds,
					 पूर्णांक port, uपूर्णांक64_t *data);
	व्योम	(*get_stats64)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   काष्ठा rtnl_link_stats64 *s);
	व्योम	(*self_test)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा ethtool_test *etest, u64 *data);

	/*
	 * ethtool Wake-on-LAN
	 */
	व्योम	(*get_wol)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा ethtool_wolinfo *w);
	पूर्णांक	(*set_wol)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा ethtool_wolinfo *w);

	/*
	 * ethtool बारtamp info
	 */
	पूर्णांक	(*get_ts_info)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा ethtool_ts_info *ts);

	/*
	 * Suspend and resume
	 */
	पूर्णांक	(*suspend)(काष्ठा dsa_चयन *ds);
	पूर्णांक	(*resume)(काष्ठा dsa_चयन *ds);

	/*
	 * Port enable/disable
	 */
	पूर्णांक	(*port_enable)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा phy_device *phy);
	व्योम	(*port_disable)(काष्ठा dsa_चयन *ds, पूर्णांक port);

	/*
	 * Port's MAC EEE settings
	 */
	पूर्णांक	(*set_mac_eee)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा ethtool_eee *e);
	पूर्णांक	(*get_mac_eee)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा ethtool_eee *e);

	/* EEPROM access */
	पूर्णांक	(*get_eeprom_len)(काष्ठा dsa_चयन *ds);
	पूर्णांक	(*get_eeprom)(काष्ठा dsa_चयन *ds,
			      काष्ठा ethtool_eeprom *eeprom, u8 *data);
	पूर्णांक	(*set_eeprom)(काष्ठा dsa_चयन *ds,
			      काष्ठा ethtool_eeprom *eeprom, u8 *data);

	/*
	 * Register access.
	 */
	पूर्णांक	(*get_regs_len)(काष्ठा dsa_चयन *ds, पूर्णांक port);
	व्योम	(*get_regs)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    काष्ठा ethtool_regs *regs, व्योम *p);

	/*
	 * Upper device tracking.
	 */
	पूर्णांक	(*port_prechangeupper)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       काष्ठा netdev_notअगरier_changeupper_info *info);

	/*
	 * Bridge पूर्णांकegration
	 */
	पूर्णांक	(*set_ageing_समय)(काष्ठा dsa_चयन *ds, अचिन्हित पूर्णांक msecs);
	पूर्णांक	(*port_bridge_join)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा net_device *bridge);
	व्योम	(*port_bridge_leave)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     काष्ठा net_device *bridge);
	व्योम	(*port_stp_state_set)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      u8 state);
	व्योम	(*port_fast_age)(काष्ठा dsa_चयन *ds, पूर्णांक port);
	पूर्णांक	(*port_pre_bridge_flags)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 काष्ठा चयनdev_brport_flags flags,
					 काष्ठा netlink_ext_ack *extack);
	पूर्णांक	(*port_bridge_flags)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     काष्ठा चयनdev_brport_flags flags,
				     काष्ठा netlink_ext_ack *extack);
	पूर्णांक	(*port_set_mrouter)(काष्ठा dsa_चयन *ds, पूर्णांक port, bool mrouter,
				    काष्ठा netlink_ext_ack *extack);

	/*
	 * VLAN support
	 */
	पूर्णांक	(*port_vlan_filtering)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       bool vlan_filtering,
				       काष्ठा netlink_ext_ack *extack);
	पूर्णांक	(*port_vlan_add)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
				 काष्ठा netlink_ext_ack *extack);
	पूर्णांक	(*port_vlan_del)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan);
	/*
	 * Forwarding database
	 */
	पूर्णांक	(*port_fdb_add)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर अचिन्हित अक्षर *addr, u16 vid);
	पूर्णांक	(*port_fdb_del)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर अचिन्हित अक्षर *addr, u16 vid);
	पूर्णांक	(*port_fdb_dump)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 dsa_fdb_dump_cb_t *cb, व्योम *data);

	/*
	 * Multicast database
	 */
	पूर्णांक	(*port_mdb_add)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
	पूर्णांक	(*port_mdb_del)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
	/*
	 * RXNFC
	 */
	पूर्णांक	(*get_rxnfc)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा ethtool_rxnfc *nfc, u32 *rule_locs);
	पूर्णांक	(*set_rxnfc)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा ethtool_rxnfc *nfc);

	/*
	 * TC पूर्णांकegration
	 */
	पूर्णांक	(*cls_flower_add)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा flow_cls_offload *cls, bool ingress);
	पूर्णांक	(*cls_flower_del)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा flow_cls_offload *cls, bool ingress);
	पूर्णांक	(*cls_flower_stats)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा flow_cls_offload *cls, bool ingress);
	पूर्णांक	(*port_mirror_add)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   काष्ठा dsa_mall_mirror_tc_entry *mirror,
				   bool ingress);
	व्योम	(*port_mirror_del)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   काष्ठा dsa_mall_mirror_tc_entry *mirror);
	पूर्णांक	(*port_policer_add)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा dsa_mall_policer_tc_entry *policer);
	व्योम	(*port_policer_del)(काष्ठा dsa_चयन *ds, पूर्णांक port);
	पूर्णांक	(*port_setup_tc)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 क्रमागत tc_setup_type type, व्योम *type_data);

	/*
	 * Cross-chip operations
	 */
	पूर्णांक	(*crosschip_bridge_join)(काष्ठा dsa_चयन *ds, पूर्णांक tree_index,
					 पूर्णांक sw_index, पूर्णांक port,
					 काष्ठा net_device *br);
	व्योम	(*crosschip_bridge_leave)(काष्ठा dsa_चयन *ds, पूर्णांक tree_index,
					  पूर्णांक sw_index, पूर्णांक port,
					  काष्ठा net_device *br);
	पूर्णांक	(*crosschip_lag_change)(काष्ठा dsa_चयन *ds, पूर्णांक sw_index,
					पूर्णांक port);
	पूर्णांक	(*crosschip_lag_join)(काष्ठा dsa_चयन *ds, पूर्णांक sw_index,
				      पूर्णांक port, काष्ठा net_device *lag,
				      काष्ठा netdev_lag_upper_info *info);
	पूर्णांक	(*crosschip_lag_leave)(काष्ठा dsa_चयन *ds, पूर्णांक sw_index,
				       पूर्णांक port, काष्ठा net_device *lag);

	/*
	 * PTP functionality
	 */
	पूर्णांक	(*port_hwtstamp_get)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     काष्ठा अगरreq *अगरr);
	पूर्णांक	(*port_hwtstamp_set)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     काष्ठा अगरreq *अगरr);
	व्योम	(*port_txtstamp)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा sk_buff *skb);
	bool	(*port_rxtstamp)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type);

	/* Devlink parameters, etc */
	पूर्णांक	(*devlink_param_get)(काष्ठा dsa_चयन *ds, u32 id,
				     काष्ठा devlink_param_gset_ctx *ctx);
	पूर्णांक	(*devlink_param_set)(काष्ठा dsa_चयन *ds, u32 id,
				     काष्ठा devlink_param_gset_ctx *ctx);
	पूर्णांक	(*devlink_info_get)(काष्ठा dsa_चयन *ds,
				    काष्ठा devlink_info_req *req,
				    काष्ठा netlink_ext_ack *extack);
	पूर्णांक	(*devlink_sb_pool_get)(काष्ठा dsa_चयन *ds,
				       अचिन्हित पूर्णांक sb_index, u16 pool_index,
				       काष्ठा devlink_sb_pool_info *pool_info);
	पूर्णांक	(*devlink_sb_pool_set)(काष्ठा dsa_चयन *ds, अचिन्हित पूर्णांक sb_index,
				       u16 pool_index, u32 size,
				       क्रमागत devlink_sb_threshold_type threshold_type,
				       काष्ठा netlink_ext_ack *extack);
	पूर्णांक	(*devlink_sb_port_pool_get)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					    अचिन्हित पूर्णांक sb_index, u16 pool_index,
					    u32 *p_threshold);
	पूर्णांक	(*devlink_sb_port_pool_set)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					    अचिन्हित पूर्णांक sb_index, u16 pool_index,
					    u32 threshold,
					    काष्ठा netlink_ext_ack *extack);
	पूर्णांक	(*devlink_sb_tc_pool_bind_get)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					       अचिन्हित पूर्णांक sb_index, u16 tc_index,
					       क्रमागत devlink_sb_pool_type pool_type,
					       u16 *p_pool_index, u32 *p_threshold);
	पूर्णांक	(*devlink_sb_tc_pool_bind_set)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					       अचिन्हित पूर्णांक sb_index, u16 tc_index,
					       क्रमागत devlink_sb_pool_type pool_type,
					       u16 pool_index, u32 threshold,
					       काष्ठा netlink_ext_ack *extack);
	पूर्णांक	(*devlink_sb_occ_snapshot)(काष्ठा dsa_चयन *ds,
					   अचिन्हित पूर्णांक sb_index);
	पूर्णांक	(*devlink_sb_occ_max_clear)(काष्ठा dsa_चयन *ds,
					    अचिन्हित पूर्णांक sb_index);
	पूर्णांक	(*devlink_sb_occ_port_pool_get)(काष्ठा dsa_चयन *ds, पूर्णांक port,
						अचिन्हित पूर्णांक sb_index, u16 pool_index,
						u32 *p_cur, u32 *p_max);
	पूर्णांक	(*devlink_sb_occ_tc_port_bind_get)(काष्ठा dsa_चयन *ds, पूर्णांक port,
						   अचिन्हित पूर्णांक sb_index, u16 tc_index,
						   क्रमागत devlink_sb_pool_type pool_type,
						   u32 *p_cur, u32 *p_max);

	/*
	 * MTU change functionality. Switches can also adjust their MRU through
	 * this method. By MTU, one understands the SDU (L2 payload) length.
	 * If the चयन needs to account क्रम the DSA tag on the CPU port, this
	 * method needs to करो so निजीly.
	 */
	पूर्णांक	(*port_change_mtu)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   पूर्णांक new_mtu);
	पूर्णांक	(*port_max_mtu)(काष्ठा dsa_चयन *ds, पूर्णांक port);

	/*
	 * LAG पूर्णांकegration
	 */
	पूर्णांक	(*port_lag_change)(काष्ठा dsa_चयन *ds, पूर्णांक port);
	पूर्णांक	(*port_lag_join)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा net_device *lag,
				 काष्ठा netdev_lag_upper_info *info);
	पूर्णांक	(*port_lag_leave)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा net_device *lag);

	/*
	 * HSR पूर्णांकegration
	 */
	पूर्णांक	(*port_hsr_join)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा net_device *hsr);
	पूर्णांक	(*port_hsr_leave)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा net_device *hsr);

	/*
	 * MRP पूर्णांकegration
	 */
	पूर्णांक	(*port_mrp_add)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर काष्ठा चयनdev_obj_mrp *mrp);
	पूर्णांक	(*port_mrp_del)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				स्थिर काष्ठा चयनdev_obj_mrp *mrp);
	पूर्णांक	(*port_mrp_add_ring_role)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					  स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp);
	पूर्णांक	(*port_mrp_del_ring_role)(काष्ठा dsa_चयन *ds, पूर्णांक port,
					  स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp);
पूर्ण;

#घोषणा DSA_DEVLINK_PARAM_DRIVER(_id, _name, _type, _cmodes)		\
	DEVLINK_PARAM_DRIVER(_id, _name, _type, _cmodes,		\
			     dsa_devlink_param_get, dsa_devlink_param_set, शून्य)

पूर्णांक dsa_devlink_param_get(काष्ठा devlink *dl, u32 id,
			  काष्ठा devlink_param_gset_ctx *ctx);
पूर्णांक dsa_devlink_param_set(काष्ठा devlink *dl, u32 id,
			  काष्ठा devlink_param_gset_ctx *ctx);
पूर्णांक dsa_devlink_params_रेजिस्टर(काष्ठा dsa_चयन *ds,
				स्थिर काष्ठा devlink_param *params,
				माप_प्रकार params_count);
व्योम dsa_devlink_params_unरेजिस्टर(काष्ठा dsa_चयन *ds,
				   स्थिर काष्ठा devlink_param *params,
				   माप_प्रकार params_count);
पूर्णांक dsa_devlink_resource_रेजिस्टर(काष्ठा dsa_चयन *ds,
				  स्थिर अक्षर *resource_name,
				  u64 resource_size,
				  u64 resource_id,
				  u64 parent_resource_id,
				  स्थिर काष्ठा devlink_resource_size_params *size_params);

व्योम dsa_devlink_resources_unरेजिस्टर(काष्ठा dsa_चयन *ds);

व्योम dsa_devlink_resource_occ_get_रेजिस्टर(काष्ठा dsa_चयन *ds,
					   u64 resource_id,
					   devlink_resource_occ_get_t *occ_get,
					   व्योम *occ_get_priv);
व्योम dsa_devlink_resource_occ_get_unरेजिस्टर(काष्ठा dsa_चयन *ds,
					     u64 resource_id);
काष्ठा devlink_region *
dsa_devlink_region_create(काष्ठा dsa_चयन *ds,
			  स्थिर काष्ठा devlink_region_ops *ops,
			  u32 region_max_snapshots, u64 region_size);
काष्ठा devlink_region *
dsa_devlink_port_region_create(काष्ठा dsa_चयन *ds,
			       पूर्णांक port,
			       स्थिर काष्ठा devlink_port_region_ops *ops,
			       u32 region_max_snapshots, u64 region_size);
व्योम dsa_devlink_region_destroy(काष्ठा devlink_region *region);

काष्ठा dsa_port *dsa_port_from_netdev(काष्ठा net_device *netdev);

काष्ठा dsa_devlink_priv अणु
	काष्ठा dsa_चयन *ds;
पूर्ण;

अटल अंतरभूत काष्ठा dsa_चयन *dsa_devlink_to_ds(काष्ठा devlink *dl)
अणु
	काष्ठा dsa_devlink_priv *dl_priv = devlink_priv(dl);

	वापस dl_priv->ds;
पूर्ण

अटल अंतरभूत
काष्ठा dsa_चयन *dsa_devlink_port_to_ds(काष्ठा devlink_port *port)
अणु
	काष्ठा devlink *dl = port->devlink;
	काष्ठा dsa_devlink_priv *dl_priv = devlink_priv(dl);

	वापस dl_priv->ds;
पूर्ण

अटल अंतरभूत पूर्णांक dsa_devlink_port_to_port(काष्ठा devlink_port *port)
अणु
	वापस port->index;
पूर्ण

काष्ठा dsa_चयन_driver अणु
	काष्ठा list_head	list;
	स्थिर काष्ठा dsa_चयन_ops *ops;
पूर्ण;

काष्ठा net_device *dsa_dev_to_net_device(काष्ठा device *dev);

/* Keep अंतरभूत क्रम faster access in hot path */
अटल अंतरभूत bool netdev_uses_dsa(स्थिर काष्ठा net_device *dev)
अणु
#अगर IS_ENABLED(CONFIG_NET_DSA)
	वापस dev->dsa_ptr && dev->dsa_ptr->rcv;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत bool dsa_can_decode(स्थिर काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev)
अणु
#अगर IS_ENABLED(CONFIG_NET_DSA)
	वापस !dev->dsa_ptr->filter || dev->dsa_ptr->filter(skb, dev);
#पूर्ण_अगर
	वापस false;
पूर्ण

/* All DSA tags that push the EtherType to the right (basically all except tail
 * tags, which करोn't अवरोध dissection) can be treated the same from the
 * perspective of the flow dissector.
 *
 * We need to वापस:
 *  - offset: the (B - A) dअगरference between:
 *    A. the position of the real EtherType and
 *    B. the current skb->data (aka ETH_HLEN bytes पूर्णांकo the frame, aka 2 bytes
 *       after the normal EtherType was supposed to be)
 *    The offset in bytes is exactly equal to the tagger overhead (and half of
 *    that, in __be16 लघुs).
 *
 *  - proto: the value of the real EtherType.
 */
अटल अंतरभूत व्योम dsa_tag_generic_flow_dissect(स्थिर काष्ठा sk_buff *skb,
						__be16 *proto, पूर्णांक *offset)
अणु
#अगर IS_ENABLED(CONFIG_NET_DSA)
	स्थिर काष्ठा dsa_device_ops *ops = skb->dev->dsa_ptr->tag_ops;
	पूर्णांक tag_len = ops->overhead;

	*offset = tag_len;
	*proto = ((__be16 *)skb->data)[(tag_len / 2) - 1];
#पूर्ण_अगर
पूर्ण

#अगर IS_ENABLED(CONFIG_NET_DSA)
अटल अंतरभूत पूर्णांक __dsa_netdevice_ops_check(काष्ठा net_device *dev)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	अगर (!dev->dsa_ptr)
		वापस err;

	अगर (!dev->dsa_ptr->netdev_ops)
		वापस err;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dsa_nकरो_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
				   पूर्णांक cmd)
अणु
	स्थिर काष्ठा dsa_netdevice_ops *ops;
	पूर्णांक err;

	err = __dsa_netdevice_ops_check(dev);
	अगर (err)
		वापस err;

	ops = dev->dsa_ptr->netdev_ops;

	वापस ops->nकरो_करो_ioctl(dev, अगरr, cmd);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक dsa_nकरो_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
				   पूर्णांक cmd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

व्योम dsa_unरेजिस्टर_चयन(काष्ठा dsa_चयन *ds);
पूर्णांक dsa_रेजिस्टर_चयन(काष्ठा dsa_चयन *ds);
काष्ठा dsa_चयन *dsa_चयन_find(पूर्णांक tree_index, पूर्णांक sw_index);
#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक dsa_चयन_suspend(काष्ठा dsa_चयन *ds);
पूर्णांक dsa_चयन_resume(काष्ठा dsa_चयन *ds);
#अन्यथा
अटल अंतरभूत पूर्णांक dsa_चयन_suspend(काष्ठा dsa_चयन *ds)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक dsa_चयन_resume(काष्ठा dsa_चयन *ds)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर IS_ENABLED(CONFIG_NET_DSA)
bool dsa_slave_dev_check(स्थिर काष्ठा net_device *dev);
#अन्यथा
अटल अंतरभूत bool dsa_slave_dev_check(स्थिर काष्ठा net_device *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

netdev_tx_t dsa_enqueue_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक dsa_port_get_phy_strings(काष्ठा dsa_port *dp, uपूर्णांक8_t *data);
पूर्णांक dsa_port_get_ethtool_phy_stats(काष्ठा dsa_port *dp, uपूर्णांक64_t *data);
पूर्णांक dsa_port_get_phy_sset_count(काष्ठा dsa_port *dp);
व्योम dsa_port_phylink_mac_change(काष्ठा dsa_चयन *ds, पूर्णांक port, bool up);

काष्ठा dsa_tag_driver अणु
	स्थिर काष्ठा dsa_device_ops *ops;
	काष्ठा list_head list;
	काष्ठा module *owner;
पूर्ण;

व्योम dsa_tag_drivers_रेजिस्टर(काष्ठा dsa_tag_driver *dsa_tag_driver_array[],
			      अचिन्हित पूर्णांक count,
			      काष्ठा module *owner);
व्योम dsa_tag_drivers_unरेजिस्टर(काष्ठा dsa_tag_driver *dsa_tag_driver_array[],
				अचिन्हित पूर्णांक count);

#घोषणा dsa_tag_driver_module_drivers(__dsa_tag_drivers_array, __count)	\
अटल पूर्णांक __init dsa_tag_driver_module_init(व्योम)			\
अणु									\
	dsa_tag_drivers_रेजिस्टर(__dsa_tag_drivers_array, __count,	\
				 THIS_MODULE);				\
	वापस 0;							\
पूर्ण									\
module_init(dsa_tag_driver_module_init);				\
									\
अटल व्योम __निकास dsa_tag_driver_module_निकास(व्योम)			\
अणु									\
	dsa_tag_drivers_unरेजिस्टर(__dsa_tag_drivers_array, __count);	\
पूर्ण									\
module_निकास(dsa_tag_driver_module_निकास)

/**
 * module_dsa_tag_drivers() - Helper macro क्रम रेजिस्टरing DSA tag
 * drivers
 * @__ops_array: Array of tag driver strucutres
 *
 * Helper macro क्रम DSA tag drivers which करो not करो anything special
 * in module init/निकास. Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास().
 */
#घोषणा module_dsa_tag_drivers(__ops_array)				\
dsa_tag_driver_module_drivers(__ops_array, ARRAY_SIZE(__ops_array))

#घोषणा DSA_TAG_DRIVER_NAME(__ops) dsa_tag_driver ## _ ## __ops

/* Create a अटल काष्ठाure we can build a linked list of dsa_tag
 * drivers
 */
#घोषणा DSA_TAG_DRIVER(__ops)						\
अटल काष्ठा dsa_tag_driver DSA_TAG_DRIVER_NAME(__ops) = अणु		\
	.ops = &__ops,							\
पूर्ण

/**
 * module_dsa_tag_driver() - Helper macro क्रम रेजिस्टरing a single DSA tag
 * driver
 * @__ops: Single tag driver काष्ठाures
 *
 * Helper macro क्रम DSA tag drivers which करो not करो anything special
 * in module init/निकास. Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास().
 */
#घोषणा module_dsa_tag_driver(__ops)					\
DSA_TAG_DRIVER(__ops);							\
									\
अटल काष्ठा dsa_tag_driver *dsa_tag_driver_array[] =	अणु		\
	&DSA_TAG_DRIVER_NAME(__ops)					\
पूर्ण;									\
module_dsa_tag_drivers(dsa_tag_driver_array)
#पूर्ण_अगर

