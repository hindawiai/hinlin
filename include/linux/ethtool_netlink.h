<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित _LINUX_ETHTOOL_NETLINK_H_
#घोषणा _LINUX_ETHTOOL_NETLINK_H_

#समावेश <uapi/linux/ethtool_netlink.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>

#घोषणा __ETHTOOL_LINK_MODE_MASK_NWORDS \
	DIV_ROUND_UP(__ETHTOOL_LINK_MODE_MASK_NBITS, 32)

क्रमागत ethtool_multicast_groups अणु
	ETHNL_MCGRP_MONITOR,
पूर्ण;

काष्ठा phy_device;

#अगर IS_ENABLED(CONFIG_ETHTOOL_NETLINK)
पूर्णांक ethnl_cable_test_alloc(काष्ठा phy_device *phydev, u8 cmd);
व्योम ethnl_cable_test_मुक्त(काष्ठा phy_device *phydev);
व्योम ethnl_cable_test_finished(काष्ठा phy_device *phydev);
पूर्णांक ethnl_cable_test_result(काष्ठा phy_device *phydev, u8 pair, u8 result);
पूर्णांक ethnl_cable_test_fault_length(काष्ठा phy_device *phydev, u8 pair, u32 cm);
पूर्णांक ethnl_cable_test_amplitude(काष्ठा phy_device *phydev, u8 pair, s16 mV);
पूर्णांक ethnl_cable_test_pulse(काष्ठा phy_device *phydev, u16 mV);
पूर्णांक ethnl_cable_test_step(काष्ठा phy_device *phydev, u32 first, u32 last,
			  u32 step);
#अन्यथा
अटल अंतरभूत पूर्णांक ethnl_cable_test_alloc(काष्ठा phy_device *phydev, u8 cmd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ethnl_cable_test_मुक्त(काष्ठा phy_device *phydev)
अणु
पूर्ण

अटल अंतरभूत व्योम ethnl_cable_test_finished(काष्ठा phy_device *phydev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ethnl_cable_test_result(काष्ठा phy_device *phydev, u8 pair,
					  u8 result)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ethnl_cable_test_fault_length(काष्ठा phy_device *phydev,
						u8 pair, u32 cm)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ethnl_cable_test_amplitude(काष्ठा phy_device *phydev,
					     u8 pair, s16 mV)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ethnl_cable_test_pulse(काष्ठा phy_device *phydev, u16 mV)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ethnl_cable_test_step(काष्ठा phy_device *phydev, u32 first,
					u32 last, u32 step)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_ETHTOOL_NETLINK) */
#पूर्ण_अगर /* _LINUX_ETHTOOL_NETLINK_H_ */
