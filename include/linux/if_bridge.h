<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */
#अगर_अघोषित _LINUX_IF_BRIDGE_H
#घोषणा _LINUX_IF_BRIDGE_H


#समावेश <linux/netdevice.h>
#समावेश <uapi/linux/अगर_bridge.h>
#समावेश <linux/bitops.h>

काष्ठा br_ip अणु
	जोड़ अणु
		__be32	ip4;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा in6_addr ip6;
#पूर्ण_अगर
	पूर्ण src;
	जोड़ अणु
		__be32	ip4;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा in6_addr ip6;
#पूर्ण_अगर
		अचिन्हित अक्षर	mac_addr[ETH_ALEN];
	पूर्ण dst;
	__be16		proto;
	__u16           vid;
पूर्ण;

काष्ठा br_ip_list अणु
	काष्ठा list_head list;
	काष्ठा br_ip addr;
पूर्ण;

#घोषणा BR_HAIRPIN_MODE		BIT(0)
#घोषणा BR_BPDU_GUARD		BIT(1)
#घोषणा BR_ROOT_BLOCK		BIT(2)
#घोषणा BR_MULTICAST_FAST_LEAVE	BIT(3)
#घोषणा BR_ADMIN_COST		BIT(4)
#घोषणा BR_LEARNING		BIT(5)
#घोषणा BR_FLOOD		BIT(6)
#घोषणा BR_AUTO_MASK		(BR_FLOOD | BR_LEARNING)
#घोषणा BR_PROMISC		BIT(7)
#घोषणा BR_PROXYARP		BIT(8)
#घोषणा BR_LEARNING_SYNC	BIT(9)
#घोषणा BR_PROXYARP_WIFI	BIT(10)
#घोषणा BR_MCAST_FLOOD		BIT(11)
#घोषणा BR_MULTICAST_TO_UNICAST	BIT(12)
#घोषणा BR_VLAN_TUNNEL		BIT(13)
#घोषणा BR_BCAST_FLOOD		BIT(14)
#घोषणा BR_NEIGH_SUPPRESS	BIT(15)
#घोषणा BR_ISOLATED		BIT(16)
#घोषणा BR_MRP_AWARE		BIT(17)
#घोषणा BR_MRP_LOST_CONT	BIT(18)
#घोषणा BR_MRP_LOST_IN_CONT	BIT(19)

#घोषणा BR_DEFAULT_AGEING_TIME	(300 * HZ)

बाह्य व्योम brioctl_set(पूर्णांक (*ioctl_hook)(काष्ठा net *, अचिन्हित पूर्णांक, व्योम __user *));

#अगर IS_ENABLED(CONFIG_BRIDGE) && IS_ENABLED(CONFIG_BRIDGE_IGMP_SNOOPING)
पूर्णांक br_multicast_list_adjacent(काष्ठा net_device *dev,
			       काष्ठा list_head *br_ip_list);
bool br_multicast_has_querier_anywhere(काष्ठा net_device *dev, पूर्णांक proto);
bool br_multicast_has_querier_adjacent(काष्ठा net_device *dev, पूर्णांक proto);
bool br_multicast_enabled(स्थिर काष्ठा net_device *dev);
bool br_multicast_router(स्थिर काष्ठा net_device *dev);
पूर्णांक br_mdb_replay(काष्ठा net_device *br_dev, काष्ठा net_device *dev,
		  काष्ठा notअगरier_block *nb, काष्ठा netlink_ext_ack *extack);
#अन्यथा
अटल अंतरभूत पूर्णांक br_multicast_list_adjacent(काष्ठा net_device *dev,
					     काष्ठा list_head *br_ip_list)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool br_multicast_has_querier_anywhere(काष्ठा net_device *dev,
						     पूर्णांक proto)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool br_multicast_has_querier_adjacent(काष्ठा net_device *dev,
						     पूर्णांक proto)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool br_multicast_enabled(स्थिर काष्ठा net_device *dev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool br_multicast_router(स्थिर काष्ठा net_device *dev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक br_mdb_replay(काष्ठा net_device *br_dev,
				काष्ठा net_device *dev,
				काष्ठा notअगरier_block *nb,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_BRIDGE) && IS_ENABLED(CONFIG_BRIDGE_VLAN_FILTERING)
bool br_vlan_enabled(स्थिर काष्ठा net_device *dev);
पूर्णांक br_vlan_get_pvid(स्थिर काष्ठा net_device *dev, u16 *p_pvid);
पूर्णांक br_vlan_get_pvid_rcu(स्थिर काष्ठा net_device *dev, u16 *p_pvid);
पूर्णांक br_vlan_get_proto(स्थिर काष्ठा net_device *dev, u16 *p_proto);
पूर्णांक br_vlan_get_info(स्थिर काष्ठा net_device *dev, u16 vid,
		     काष्ठा bridge_vlan_info *p_vinfo);
पूर्णांक br_vlan_replay(काष्ठा net_device *br_dev, काष्ठा net_device *dev,
		   काष्ठा notअगरier_block *nb, काष्ठा netlink_ext_ack *extack);
#अन्यथा
अटल अंतरभूत bool br_vlan_enabled(स्थिर काष्ठा net_device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_get_pvid(स्थिर काष्ठा net_device *dev, u16 *p_pvid)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_get_proto(स्थिर काष्ठा net_device *dev, u16 *p_proto)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_get_pvid_rcu(स्थिर काष्ठा net_device *dev, u16 *p_pvid)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_get_info(स्थिर काष्ठा net_device *dev, u16 vid,
				   काष्ठा bridge_vlan_info *p_vinfo)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_replay(काष्ठा net_device *br_dev,
				 काष्ठा net_device *dev,
				 काष्ठा notअगरier_block *nb,
				 काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_BRIDGE)
काष्ठा net_device *br_fdb_find_port(स्थिर काष्ठा net_device *br_dev,
				    स्थिर अचिन्हित अक्षर *addr,
				    __u16 vid);
व्योम br_fdb_clear_offload(स्थिर काष्ठा net_device *dev, u16 vid);
bool br_port_flag_is_set(स्थिर काष्ठा net_device *dev, अचिन्हित दीर्घ flag);
u8 br_port_get_stp_state(स्थिर काष्ठा net_device *dev);
घड़ी_प्रकार br_get_ageing_समय(काष्ठा net_device *br_dev);
पूर्णांक br_fdb_replay(काष्ठा net_device *br_dev, काष्ठा net_device *dev,
		  काष्ठा notअगरier_block *nb);
#अन्यथा
अटल अंतरभूत काष्ठा net_device *
br_fdb_find_port(स्थिर काष्ठा net_device *br_dev,
		 स्थिर अचिन्हित अक्षर *addr,
		 __u16 vid)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम br_fdb_clear_offload(स्थिर काष्ठा net_device *dev, u16 vid)
अणु
पूर्ण

अटल अंतरभूत bool
br_port_flag_is_set(स्थिर काष्ठा net_device *dev, अचिन्हित दीर्घ flag)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u8 br_port_get_stp_state(स्थिर काष्ठा net_device *dev)
अणु
	वापस BR_STATE_DISABLED;
पूर्ण

अटल अंतरभूत घड़ी_प्रकार br_get_ageing_समय(काष्ठा net_device *br_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक br_fdb_replay(काष्ठा net_device *br_dev,
				काष्ठा net_device *dev,
				काष्ठा notअगरier_block *nb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
