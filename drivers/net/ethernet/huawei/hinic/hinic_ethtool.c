<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * क्रम more details.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sfp.h>

#समावेश "hinic_hw_qp.h"
#समावेश "hinic_hw_dev.h"
#समावेश "hinic_port.h"
#समावेश "hinic_tx.h"
#समावेश "hinic_rx.h"
#समावेश "hinic_dev.h"

#घोषणा SET_LINK_STR_MAX_LEN	16

#घोषणा GET_SUPPORTED_MODE	0
#घोषणा GET_ADVERTISED_MODE	1

#घोषणा ETHTOOL_ADD_SUPPORTED_SPEED_LINK_MODE(ecmd, mode)	\
		((ecmd)->supported |=	\
		(1UL << hw_to_ethtool_link_mode_table[mode].link_mode_bit))
#घोषणा ETHTOOL_ADD_ADVERTISED_SPEED_LINK_MODE(ecmd, mode)	\
		((ecmd)->advertising |=	\
		(1UL << hw_to_ethtool_link_mode_table[mode].link_mode_bit))
#घोषणा ETHTOOL_ADD_SUPPORTED_LINK_MODE(ecmd, mode)	\
				((ecmd)->supported |= SUPPORTED_##mode)
#घोषणा ETHTOOL_ADD_ADVERTISED_LINK_MODE(ecmd, mode)	\
				((ecmd)->advertising |= ADVERTISED_##mode)

#घोषणा COALESCE_PENDING_LIMIT_UNIT	8
#घोषणा	COALESCE_TIMER_CFG_UNIT		9
#घोषणा COALESCE_ALL_QUEUE		0xFFFF
#घोषणा COALESCE_MAX_PENDING_LIMIT	(255 * COALESCE_PENDING_LIMIT_UNIT)
#घोषणा COALESCE_MAX_TIMER_CFG		(255 * COALESCE_TIMER_CFG_UNIT)
#घोषणा OBJ_STR_MAX_LEN			32

काष्ठा hw2ethtool_link_mode अणु
	क्रमागत ethtool_link_mode_bit_indices link_mode_bit;
	u32 speed;
	क्रमागत hinic_link_mode hw_link_mode;
पूर्ण;

काष्ठा cmd_link_settings अणु
	u64	supported;
	u64	advertising;

	u32	speed;
	u8	duplex;
	u8	port;
	u8	स्वतःneg;
पूर्ण;

अटल u32 hw_to_ethtool_speed[LINK_SPEED_LEVELS] = अणु
	SPEED_10, SPEED_100,
	SPEED_1000, SPEED_10000,
	SPEED_25000, SPEED_40000,
	SPEED_100000
पूर्ण;

अटल काष्ठा hw2ethtool_link_mode
	hw_to_ethtool_link_mode_table[HINIC_LINK_MODE_NUMBERS] = अणु
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
		.speed = SPEED_10000,
		.hw_link_mode = HINIC_10GE_BASE_KR,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
		.speed = SPEED_40000,
		.hw_link_mode = HINIC_40GE_BASE_KR4,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
		.speed = SPEED_40000,
		.hw_link_mode = HINIC_40GE_BASE_CR4,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
		.speed = SPEED_100000,
		.hw_link_mode = HINIC_100GE_BASE_KR4,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
		.speed = SPEED_100000,
		.hw_link_mode = HINIC_100GE_BASE_CR4,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
		.speed = SPEED_25000,
		.hw_link_mode = HINIC_25GE_BASE_KR_S,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
		.speed = SPEED_25000,
		.hw_link_mode = HINIC_25GE_BASE_CR_S,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
		.speed = SPEED_25000,
		.hw_link_mode = HINIC_25GE_BASE_KR,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
		.speed = SPEED_25000,
		.hw_link_mode = HINIC_25GE_BASE_CR,
	पूर्ण,
	अणु
		.link_mode_bit = ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
		.speed = SPEED_1000,
		.hw_link_mode = HINIC_GE_BASE_KX,
	पूर्ण,
पूर्ण;

#घोषणा LP_DEFAULT_TIME                 5 /* seconds */
#घोषणा LP_PKT_LEN                      1514

#घोषणा PORT_DOWN_ERR_IDX		0
क्रमागत diag_test_index अणु
	INTERNAL_LP_TEST = 0,
	EXTERNAL_LP_TEST = 1,
	DIAG_TEST_MAX = 2,
पूर्ण;

अटल व्योम set_link_speed(काष्ठा ethtool_link_ksettings *link_ksettings,
			   क्रमागत hinic_speed speed)
अणु
	चयन (speed) अणु
	हाल HINIC_SPEED_10MB_LINK:
		link_ksettings->base.speed = SPEED_10;
		अवरोध;

	हाल HINIC_SPEED_100MB_LINK:
		link_ksettings->base.speed = SPEED_100;
		अवरोध;

	हाल HINIC_SPEED_1000MB_LINK:
		link_ksettings->base.speed = SPEED_1000;
		अवरोध;

	हाल HINIC_SPEED_10GB_LINK:
		link_ksettings->base.speed = SPEED_10000;
		अवरोध;

	हाल HINIC_SPEED_25GB_LINK:
		link_ksettings->base.speed = SPEED_25000;
		अवरोध;

	हाल HINIC_SPEED_40GB_LINK:
		link_ksettings->base.speed = SPEED_40000;
		अवरोध;

	हाल HINIC_SPEED_100GB_LINK:
		link_ksettings->base.speed = SPEED_100000;
		अवरोध;

	शेष:
		link_ksettings->base.speed = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक hinic_get_link_mode_index(क्रमागत hinic_link_mode link_mode)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < HINIC_LINK_MODE_NUMBERS; i++) अणु
		अगर (link_mode == hw_to_ethtool_link_mode_table[i].hw_link_mode)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम hinic_add_ethtool_link_mode(काष्ठा cmd_link_settings *link_settings,
					क्रमागत hinic_link_mode hw_link_mode,
					u32 name)
अणु
	क्रमागत hinic_link_mode link_mode;
	पूर्णांक idx = 0;

	क्रम (link_mode = 0; link_mode < HINIC_LINK_MODE_NUMBERS; link_mode++) अणु
		अगर (hw_link_mode & ((u32)1 << link_mode)) अणु
			idx = hinic_get_link_mode_index(link_mode);
			अगर (idx >= HINIC_LINK_MODE_NUMBERS)
				जारी;

			अगर (name == GET_SUPPORTED_MODE)
				ETHTOOL_ADD_SUPPORTED_SPEED_LINK_MODE
					(link_settings, idx);
			अन्यथा
				ETHTOOL_ADD_ADVERTISED_SPEED_LINK_MODE
					(link_settings, idx);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hinic_link_port_type(काष्ठा cmd_link_settings *link_settings,
				 क्रमागत hinic_port_type port_type)
अणु
	चयन (port_type) अणु
	हाल HINIC_PORT_ELEC:
	हाल HINIC_PORT_TP:
		ETHTOOL_ADD_SUPPORTED_LINK_MODE(link_settings, TP);
		ETHTOOL_ADD_ADVERTISED_LINK_MODE(link_settings, TP);
		link_settings->port = PORT_TP;
		अवरोध;

	हाल HINIC_PORT_AOC:
	हाल HINIC_PORT_FIBRE:
		ETHTOOL_ADD_SUPPORTED_LINK_MODE(link_settings, FIBRE);
		ETHTOOL_ADD_ADVERTISED_LINK_MODE(link_settings, FIBRE);
		link_settings->port = PORT_FIBRE;
		अवरोध;

	हाल HINIC_PORT_COPPER:
		ETHTOOL_ADD_SUPPORTED_LINK_MODE(link_settings, FIBRE);
		ETHTOOL_ADD_ADVERTISED_LINK_MODE(link_settings, FIBRE);
		link_settings->port = PORT_DA;
		अवरोध;

	हाल HINIC_PORT_BACKPLANE:
		ETHTOOL_ADD_SUPPORTED_LINK_MODE(link_settings, Backplane);
		ETHTOOL_ADD_ADVERTISED_LINK_MODE(link_settings, Backplane);
		link_settings->port = PORT_NONE;
		अवरोध;

	शेष:
		link_settings->port = PORT_OTHER;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक hinic_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings
				    *link_ksettings)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_link_mode_cmd link_mode = अणु 0 पूर्ण;
	काष्ठा hinic_छोड़ो_config छोड़ो_info = अणु 0 पूर्ण;
	काष्ठा cmd_link_settings settings = अणु 0 पूर्ण;
	क्रमागत hinic_port_link_state link_state;
	काष्ठा hinic_port_cap port_cap;
	पूर्णांक err;

	ethtool_link_ksettings_zero_link_mode(link_ksettings, supported);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, advertising);

	link_ksettings->base.speed = SPEED_UNKNOWN;
	link_ksettings->base.स्वतःneg = AUTONEG_DISABLE;
	link_ksettings->base.duplex = DUPLEX_UNKNOWN;

	err = hinic_port_get_cap(nic_dev, &port_cap);
	अगर (err)
		वापस err;

	hinic_link_port_type(&settings, port_cap.port_type);
	link_ksettings->base.port = settings.port;

	err = hinic_port_link_state(nic_dev, &link_state);
	अगर (err)
		वापस err;

	अगर (link_state == HINIC_LINK_STATE_UP) अणु
		set_link_speed(link_ksettings, port_cap.speed);
		link_ksettings->base.duplex =
			(port_cap.duplex == HINIC_DUPLEX_FULL) ?
			DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण

	अगर (!!(port_cap.स्वतःneg_cap & HINIC_AUTONEG_SUPPORTED))
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Autoneg);

	अगर (port_cap.स्वतःneg_state == HINIC_AUTONEG_ACTIVE)
		link_ksettings->base.स्वतःneg = AUTONEG_ENABLE;

	err = hinic_get_link_mode(nic_dev->hwdev, &link_mode);
	अगर (err || link_mode.supported == HINIC_SUPPORTED_UNKNOWN ||
	    link_mode.advertised == HINIC_SUPPORTED_UNKNOWN)
		वापस -EIO;

	hinic_add_ethtool_link_mode(&settings, link_mode.supported,
				    GET_SUPPORTED_MODE);
	hinic_add_ethtool_link_mode(&settings, link_mode.advertised,
				    GET_ADVERTISED_MODE);

	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर)) अणु
		err = hinic_get_hw_छोड़ो_info(nic_dev->hwdev, &छोड़ो_info);
		अगर (err)
			वापस err;
		ETHTOOL_ADD_SUPPORTED_LINK_MODE(&settings, Pause);
		अगर (छोड़ो_info.rx_छोड़ो && छोड़ो_info.tx_छोड़ो) अणु
			ETHTOOL_ADD_ADVERTISED_LINK_MODE(&settings, Pause);
		पूर्ण अन्यथा अगर (छोड़ो_info.tx_छोड़ो) अणु
			ETHTOOL_ADD_ADVERTISED_LINK_MODE(&settings, Asym_Pause);
		पूर्ण अन्यथा अगर (छोड़ो_info.rx_छोड़ो) अणु
			ETHTOOL_ADD_ADVERTISED_LINK_MODE(&settings, Pause);
			ETHTOOL_ADD_ADVERTISED_LINK_MODE(&settings, Asym_Pause);
		पूर्ण
	पूर्ण

	biपंचांगap_copy(link_ksettings->link_modes.supported,
		    (अचिन्हित दीर्घ *)&settings.supported,
		    __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_copy(link_ksettings->link_modes.advertising,
		    (अचिन्हित दीर्घ *)&settings.advertising,
		    __ETHTOOL_LINK_MODE_MASK_NBITS);

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_ethtool_to_hw_speed_level(u32 speed)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LINK_SPEED_LEVELS; i++) अणु
		अगर (hw_to_ethtool_speed[i] == speed)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल bool hinic_is_support_speed(क्रमागत hinic_link_mode supported_link,
				   u32 speed)
अणु
	क्रमागत hinic_link_mode link_mode;
	पूर्णांक idx;

	क्रम (link_mode = 0; link_mode < HINIC_LINK_MODE_NUMBERS; link_mode++) अणु
		अगर (!(supported_link & ((u32)1 << link_mode)))
			जारी;

		idx = hinic_get_link_mode_index(link_mode);
		अगर (idx >= HINIC_LINK_MODE_NUMBERS)
			जारी;

		अगर (hw_to_ethtool_link_mode_table[idx].speed == speed)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hinic_is_speed_legal(काष्ठा hinic_dev *nic_dev, u32 speed)
अणु
	काष्ठा hinic_link_mode_cmd link_mode = अणु 0 पूर्ण;
	काष्ठा net_device *netdev = nic_dev->netdev;
	क्रमागत nic_speed_level speed_level = 0;
	पूर्णांक err;

	err = hinic_get_link_mode(nic_dev->hwdev, &link_mode);
	अगर (err)
		वापस false;

	अगर (link_mode.supported == HINIC_SUPPORTED_UNKNOWN ||
	    link_mode.advertised == HINIC_SUPPORTED_UNKNOWN)
		वापस false;

	speed_level = hinic_ethtool_to_hw_speed_level(speed);
	अगर (speed_level >= LINK_SPEED_LEVELS ||
	    !hinic_is_support_speed(link_mode.supported, speed)) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Unsupported speed: %d\n", speed);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक get_link_settings_type(काष्ठा hinic_dev *nic_dev,
				  u8 स्वतःneg, u32 speed, u32 *set_settings)
अणु
	काष्ठा hinic_port_cap port_cap = अणु 0 पूर्ण;
	पूर्णांक err;

	err = hinic_port_get_cap(nic_dev, &port_cap);
	अगर (err)
		वापस err;

	/* always set स्वतःnegotiation */
	अगर (port_cap.स्वतःneg_cap)
		*set_settings |= HILINK_LINK_SET_AUTONEG;

	अगर (स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (!port_cap.स्वतःneg_cap) अणु
			netअगर_err(nic_dev, drv, nic_dev->netdev, "Not support autoneg\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अगर (speed != (u32)SPEED_UNKNOWN) अणु
		/* set speed only when स्वतःneg is disabled */
		अगर (!hinic_is_speed_legal(nic_dev, speed))
			वापस -EINVAL;
		*set_settings |= HILINK_LINK_SET_SPEED;
	पूर्ण अन्यथा अणु
		netअगर_err(nic_dev, drv, nic_dev->netdev, "Need to set speed when autoneg is off\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_link_settings_separate_cmd(काष्ठा hinic_dev *nic_dev,
					  u32 set_settings, u8 स्वतःneg,
					  u32 speed)
अणु
	क्रमागत nic_speed_level speed_level = 0;
	पूर्णांक err = 0;

	अगर (set_settings & HILINK_LINK_SET_AUTONEG) अणु
		err = hinic_set_स्वतःneg(nic_dev->hwdev,
					(स्वतःneg == AUTONEG_ENABLE));
		अगर (err)
			netअगर_err(nic_dev, drv, nic_dev->netdev, "%s autoneg failed\n",
				  (स्वतःneg == AUTONEG_ENABLE) ?
				  "Enable" : "Disable");
		अन्यथा
			netअगर_info(nic_dev, drv, nic_dev->netdev, "%s autoneg successfully\n",
				   (स्वतःneg == AUTONEG_ENABLE) ?
				   "Enable" : "Disable");
	पूर्ण

	अगर (!err && (set_settings & HILINK_LINK_SET_SPEED)) अणु
		speed_level = hinic_ethtool_to_hw_speed_level(speed);
		err = hinic_set_speed(nic_dev->hwdev, speed_level);
		अगर (err)
			netअगर_err(nic_dev, drv, nic_dev->netdev, "Set speed %d failed\n",
				  speed);
		अन्यथा
			netअगर_info(nic_dev, drv, nic_dev->netdev, "Set speed %d successfully\n",
				   speed);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hinic_set_settings_to_hw(काष्ठा hinic_dev *nic_dev,
				    u32 set_settings, u8 स्वतःneg, u32 speed)
अणु
	काष्ठा hinic_link_ksettings_info settings = अणु0पूर्ण;
	अक्षर set_link_str[SET_LINK_STR_MAX_LEN] = अणु0पूर्ण;
	स्थिर अक्षर *स्वतःneg_str;
	काष्ठा net_device *netdev = nic_dev->netdev;
	क्रमागत nic_speed_level speed_level = 0;
	पूर्णांक err;

	स्वतःneg_str = (set_settings & HILINK_LINK_SET_AUTONEG) ?
		      (स्वतःneg ? "autong enable " : "autong disable ") : "";

	अगर (set_settings & HILINK_LINK_SET_SPEED) अणु
		speed_level = hinic_ethtool_to_hw_speed_level(speed);
		err = snम_लिखो(set_link_str, SET_LINK_STR_MAX_LEN,
			       "speed %d ", speed);
		अगर (err >= SET_LINK_STR_MAX_LEN) अणु
			netअगर_err(nic_dev, drv, netdev, "Failed to snprintf link speed, function return(%d) and dest_len(%d)\n",
				  err, SET_LINK_STR_MAX_LEN);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	settings.func_id = HINIC_HWIF_FUNC_IDX(nic_dev->hwdev->hwअगर);
	settings.valid_biपंचांगap = set_settings;
	settings.स्वतःneg = स्वतःneg;
	settings.speed = speed_level;

	err = hinic_set_link_settings(nic_dev->hwdev, &settings);
	अगर (err != HINIC_MGMT_CMD_UNSUPPORTED) अणु
		अगर (err)
			netअगर_err(nic_dev, drv, netdev, "Set %s%sfailed\n",
				  स्वतःneg_str, set_link_str);
		अन्यथा
			netअगर_info(nic_dev, drv, netdev, "Set %s%ssuccessfully\n",
				   स्वतःneg_str, set_link_str);

		वापस err;
	पूर्ण

	वापस set_link_settings_separate_cmd(nic_dev, set_settings, स्वतःneg,
					      speed);
पूर्ण

अटल पूर्णांक set_link_settings(काष्ठा net_device *netdev, u8 स्वतःneg, u32 speed)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u32 set_settings = 0;
	पूर्णांक err;

	err = get_link_settings_type(nic_dev, स्वतःneg, speed, &set_settings);
	अगर (err)
		वापस err;

	अगर (set_settings)
		err = hinic_set_settings_to_hw(nic_dev, set_settings,
					       स्वतःneg, speed);
	अन्यथा
		netअगर_info(nic_dev, drv, netdev, "Nothing changed, exit without setting anything\n");

	वापस err;
पूर्ण

अटल पूर्णांक hinic_set_link_ksettings(काष्ठा net_device *netdev, स्थिर काष्ठा
				    ethtool_link_ksettings *link_settings)
अणु
	/* only support to set स्वतःneg and speed */
	वापस set_link_settings(netdev, link_settings->base.स्वतःneg,
				 link_settings->base.speed);
पूर्ण

अटल व्योम hinic_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u8 mgmt_ver[HINIC_MGMT_VERSION_MAX_LEN] = अणु0पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	पूर्णांक err;

	strscpy(info->driver, HINIC_DRV_NAME, माप(info->driver));
	strscpy(info->bus_info, pci_name(hwअगर->pdev), माप(info->bus_info));

	err = hinic_get_mgmt_version(nic_dev, mgmt_ver);
	अगर (err)
		वापस;

	snम_लिखो(info->fw_version, माप(info->fw_version), "%s", mgmt_ver);
पूर्ण

अटल व्योम hinic_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);

	ring->rx_max_pending = HINIC_MAX_QUEUE_DEPTH;
	ring->tx_max_pending = HINIC_MAX_QUEUE_DEPTH;
	ring->rx_pending = nic_dev->rq_depth;
	ring->tx_pending = nic_dev->sq_depth;
पूर्ण

अटल पूर्णांक check_ringparam_valid(काष्ठा hinic_dev *nic_dev,
				 काष्ठा ethtool_ringparam *ring)
अणु
	अगर (ring->rx_jumbo_pending || ring->rx_mini_pending) अणु
		netअगर_err(nic_dev, drv, nic_dev->netdev,
			  "Unsupported rx_jumbo_pending/rx_mini_pending\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ring->tx_pending > HINIC_MAX_QUEUE_DEPTH ||
	    ring->tx_pending < HINIC_MIN_QUEUE_DEPTH ||
	    ring->rx_pending > HINIC_MAX_QUEUE_DEPTH ||
	    ring->rx_pending < HINIC_MIN_QUEUE_DEPTH) अणु
		netअगर_err(nic_dev, drv, nic_dev->netdev,
			  "Queue depth out of range [%d-%d]\n",
			  HINIC_MIN_QUEUE_DEPTH, HINIC_MAX_QUEUE_DEPTH);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u16 new_sq_depth, new_rq_depth;
	पूर्णांक err;

	err = check_ringparam_valid(nic_dev, ring);
	अगर (err)
		वापस err;

	new_sq_depth = (u16)(1U << (u16)ilog2(ring->tx_pending));
	new_rq_depth = (u16)(1U << (u16)ilog2(ring->rx_pending));

	अगर (new_sq_depth == nic_dev->sq_depth &&
	    new_rq_depth == nic_dev->rq_depth)
		वापस 0;

	netअगर_info(nic_dev, drv, netdev,
		   "Change Tx/Rx ring depth from %d/%d to %d/%d\n",
		   nic_dev->sq_depth, nic_dev->rq_depth,
		   new_sq_depth, new_rq_depth);

	nic_dev->sq_depth = new_sq_depth;
	nic_dev->rq_depth = new_rq_depth;

	अगर (netअगर_running(netdev)) अणु
		netअगर_info(nic_dev, drv, netdev, "Restarting netdev\n");
		err = hinic_बंद(netdev);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to close netdev\n");
			वापस -EFAULT;
		पूर्ण

		err = hinic_खोलो(netdev);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to open netdev\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __hinic_get_coalesce(काष्ठा net_device *netdev,
				काष्ठा ethtool_coalesce *coal, u16 queue)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_पूर्णांकr_coal_info *rx_पूर्णांकr_coal_info;
	काष्ठा hinic_पूर्णांकr_coal_info *tx_पूर्णांकr_coal_info;

	अगर (queue == COALESCE_ALL_QUEUE) अणु
		/* get tx/rx irq0 as शेष parameters */
		rx_पूर्णांकr_coal_info = &nic_dev->rx_पूर्णांकr_coalesce[0];
		tx_पूर्णांकr_coal_info = &nic_dev->tx_पूर्णांकr_coalesce[0];
	पूर्ण अन्यथा अणु
		अगर (queue >= nic_dev->num_qps) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Invalid queue_id: %d\n", queue);
			वापस -EINVAL;
		पूर्ण
		rx_पूर्णांकr_coal_info = &nic_dev->rx_पूर्णांकr_coalesce[queue];
		tx_पूर्णांकr_coal_info = &nic_dev->tx_पूर्णांकr_coalesce[queue];
	पूर्ण

	/* coalesce_समयr is in unit of 9us */
	coal->rx_coalesce_usecs = rx_पूर्णांकr_coal_info->coalesce_समयr_cfg *
			COALESCE_TIMER_CFG_UNIT;
	/* coalesced_frames is in unit of 8 */
	coal->rx_max_coalesced_frames = rx_पूर्णांकr_coal_info->pending_limt *
			COALESCE_PENDING_LIMIT_UNIT;
	coal->tx_coalesce_usecs = tx_पूर्णांकr_coal_info->coalesce_समयr_cfg *
			COALESCE_TIMER_CFG_UNIT;
	coal->tx_max_coalesced_frames = tx_पूर्णांकr_coal_info->pending_limt *
			COALESCE_PENDING_LIMIT_UNIT;

	वापस 0;
पूर्ण

अटल पूर्णांक is_coalesce_exceed_limit(स्थिर काष्ठा ethtool_coalesce *coal)
अणु
	अगर (coal->rx_coalesce_usecs > COALESCE_MAX_TIMER_CFG ||
	    coal->rx_max_coalesced_frames > COALESCE_MAX_PENDING_LIMIT ||
	    coal->tx_coalesce_usecs > COALESCE_MAX_TIMER_CFG ||
	    coal->tx_max_coalesced_frames > COALESCE_MAX_PENDING_LIMIT)
		वापस -दुस्फल;

	वापस 0;
पूर्ण

अटल पूर्णांक set_queue_coalesce(काष्ठा hinic_dev *nic_dev, u16 q_id,
			      काष्ठा hinic_पूर्णांकr_coal_info *coal,
			      bool set_rx_coal)
अणु
	काष्ठा hinic_पूर्णांकr_coal_info *पूर्णांकr_coal = शून्य;
	काष्ठा hinic_msix_config पूर्णांकerrupt_info = अणु0पूर्ण;
	काष्ठा net_device *netdev = nic_dev->netdev;
	u16 msix_idx;
	पूर्णांक err;

	पूर्णांकr_coal = set_rx_coal ? &nic_dev->rx_पूर्णांकr_coalesce[q_id] :
		    &nic_dev->tx_पूर्णांकr_coalesce[q_id];

	पूर्णांकr_coal->coalesce_समयr_cfg = coal->coalesce_समयr_cfg;
	पूर्णांकr_coal->pending_limt = coal->pending_limt;

	/* netdev not running or qp not in using,
	 * करोn't need to set coalesce to hw
	 */
	अगर (!(nic_dev->flags & HINIC_INTF_UP) ||
	    q_id >= nic_dev->num_qps)
		वापस 0;

	msix_idx = set_rx_coal ? nic_dev->rxqs[q_id].rq->msix_entry :
		   nic_dev->txqs[q_id].sq->msix_entry;
	पूर्णांकerrupt_info.msix_index = msix_idx;
	पूर्णांकerrupt_info.coalesce_समयr_cnt = पूर्णांकr_coal->coalesce_समयr_cfg;
	पूर्णांकerrupt_info.pending_cnt = पूर्णांकr_coal->pending_limt;
	पूर्णांकerrupt_info.resend_समयr_cnt = पूर्णांकr_coal->resend_समयr_cfg;

	err = hinic_set_पूर्णांकerrupt_cfg(nic_dev->hwdev, &पूर्णांकerrupt_info);
	अगर (err)
		netअगर_warn(nic_dev, drv, netdev,
			   "Failed to set %s queue%d coalesce",
			   set_rx_coal ? "rx" : "tx", q_id);

	वापस err;
पूर्ण

अटल पूर्णांक __set_hw_coal_param(काष्ठा hinic_dev *nic_dev,
			       काष्ठा hinic_पूर्णांकr_coal_info *पूर्णांकr_coal,
			       u16 queue, bool set_rx_coal)
अणु
	पूर्णांक err;
	u16 i;

	अगर (queue == COALESCE_ALL_QUEUE) अणु
		क्रम (i = 0; i < nic_dev->max_qps; i++) अणु
			err = set_queue_coalesce(nic_dev, i, पूर्णांकr_coal,
						 set_rx_coal);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (queue >= nic_dev->num_qps) अणु
			netअगर_err(nic_dev, drv, nic_dev->netdev,
				  "Invalid queue_id: %d\n", queue);
			वापस -EINVAL;
		पूर्ण
		err = set_queue_coalesce(nic_dev, queue, पूर्णांकr_coal,
					 set_rx_coal);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __hinic_set_coalesce(काष्ठा net_device *netdev,
				काष्ठा ethtool_coalesce *coal, u16 queue)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_पूर्णांकr_coal_info rx_पूर्णांकr_coal = अणु0पूर्ण;
	काष्ठा hinic_पूर्णांकr_coal_info tx_पूर्णांकr_coal = अणु0पूर्ण;
	bool set_rx_coal = false;
	bool set_tx_coal = false;
	पूर्णांक err;

	err = is_coalesce_exceed_limit(coal);
	अगर (err)
		वापस err;

	अगर (coal->rx_coalesce_usecs || coal->rx_max_coalesced_frames) अणु
		rx_पूर्णांकr_coal.coalesce_समयr_cfg =
		(u8)(coal->rx_coalesce_usecs / COALESCE_TIMER_CFG_UNIT);
		rx_पूर्णांकr_coal.pending_limt = (u8)(coal->rx_max_coalesced_frames /
				COALESCE_PENDING_LIMIT_UNIT);
		set_rx_coal = true;
	पूर्ण

	अगर (coal->tx_coalesce_usecs || coal->tx_max_coalesced_frames) अणु
		tx_पूर्णांकr_coal.coalesce_समयr_cfg =
		(u8)(coal->tx_coalesce_usecs / COALESCE_TIMER_CFG_UNIT);
		tx_पूर्णांकr_coal.pending_limt = (u8)(coal->tx_max_coalesced_frames /
		COALESCE_PENDING_LIMIT_UNIT);
		set_tx_coal = true;
	पूर्ण

	/* setting coalesce समयr or pending limit to zero will disable
	 * coalesce
	 */
	अगर (set_rx_coal && (!rx_पूर्णांकr_coal.coalesce_समयr_cfg ||
			    !rx_पूर्णांकr_coal.pending_limt))
		netअगर_warn(nic_dev, drv, netdev, "RX coalesce will be disabled\n");
	अगर (set_tx_coal && (!tx_पूर्णांकr_coal.coalesce_समयr_cfg ||
			    !tx_पूर्णांकr_coal.pending_limt))
		netअगर_warn(nic_dev, drv, netdev, "TX coalesce will be disabled\n");

	अगर (set_rx_coal) अणु
		err = __set_hw_coal_param(nic_dev, &rx_पूर्णांकr_coal, queue, true);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (set_tx_coal) अणु
		err = __set_hw_coal_param(nic_dev, &tx_पूर्णांकr_coal, queue, false);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hinic_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	वापस __hinic_get_coalesce(netdev, coal, COALESCE_ALL_QUEUE);
पूर्ण

अटल पूर्णांक hinic_set_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	वापस __hinic_set_coalesce(netdev, coal, COALESCE_ALL_QUEUE);
पूर्ण

अटल पूर्णांक hinic_get_per_queue_coalesce(काष्ठा net_device *netdev, u32 queue,
					काष्ठा ethtool_coalesce *coal)
अणु
	वापस __hinic_get_coalesce(netdev, coal, queue);
पूर्ण

अटल पूर्णांक hinic_set_per_queue_coalesce(काष्ठा net_device *netdev, u32 queue,
					काष्ठा ethtool_coalesce *coal)
अणु
	वापस __hinic_set_coalesce(netdev, coal, queue);
पूर्ण

अटल व्योम hinic_get_छोड़ोparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_छोड़ो_config छोड़ो_info = अणु0पूर्ण;
	काष्ठा hinic_nic_cfg *nic_cfg;
	पूर्णांक err;

	nic_cfg = &nic_dev->hwdev->func_to_io.nic_cfg;

	err = hinic_get_hw_छोड़ो_info(nic_dev->hwdev, &छोड़ो_info);
	अगर (!err) अणु
		छोड़ो->स्वतःneg = छोड़ो_info.स्वतः_neg;
		अगर (nic_cfg->छोड़ो_set || !छोड़ो_info.स्वतः_neg) अणु
			छोड़ो->rx_छोड़ो = nic_cfg->rx_छोड़ो;
			छोड़ो->tx_छोड़ो = nic_cfg->tx_छोड़ो;
		पूर्ण अन्यथा अणु
			छोड़ो->rx_छोड़ो = छोड़ो_info.rx_छोड़ो;
			छोड़ो->tx_छोड़ो = छोड़ो_info.tx_छोड़ो;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hinic_set_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_छोड़ो_config छोड़ो_info = अणु0पूर्ण;
	काष्ठा hinic_port_cap port_cap = अणु0पूर्ण;
	पूर्णांक err;

	err = hinic_port_get_cap(nic_dev, &port_cap);
	अगर (err)
		वापस -EIO;

	अगर (छोड़ो->स्वतःneg != port_cap.स्वतःneg_state)
		वापस -EOPNOTSUPP;

	छोड़ो_info.स्वतः_neg = छोड़ो->स्वतःneg;
	छोड़ो_info.rx_छोड़ो = छोड़ो->rx_छोड़ो;
	छोड़ो_info.tx_छोड़ो = छोड़ो->tx_छोड़ो;

	mutex_lock(&nic_dev->hwdev->func_to_io.nic_cfg.cfg_mutex);
	err = hinic_set_hw_छोड़ो_info(nic_dev->hwdev, &छोड़ो_info);
	अगर (err) अणु
		mutex_unlock(&nic_dev->hwdev->func_to_io.nic_cfg.cfg_mutex);
		वापस err;
	पूर्ण
	nic_dev->hwdev->func_to_io.nic_cfg.छोड़ो_set = true;
	nic_dev->hwdev->func_to_io.nic_cfg.स्वतः_neg = छोड़ो->स्वतःneg;
	nic_dev->hwdev->func_to_io.nic_cfg.rx_छोड़ो = छोड़ो->rx_छोड़ो;
	nic_dev->hwdev->func_to_io.nic_cfg.tx_छोड़ो = छोड़ो->tx_छोड़ो;
	mutex_unlock(&nic_dev->hwdev->func_to_io.nic_cfg.cfg_mutex);

	वापस 0;
पूर्ण

अटल व्योम hinic_get_channels(काष्ठा net_device *netdev,
			       काष्ठा ethtool_channels *channels)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;

	channels->max_combined = nic_dev->max_qps;
	channels->combined_count = hinic_hwdev_num_qps(hwdev);
पूर्ण

अटल पूर्णांक hinic_set_channels(काष्ठा net_device *netdev,
			      काष्ठा ethtool_channels *channels)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	अचिन्हित पूर्णांक count = channels->combined_count;
	पूर्णांक err;

	netअगर_info(nic_dev, drv, netdev, "Set max combined queue number from %d to %d\n",
		   hinic_hwdev_num_qps(nic_dev->hwdev), count);

	अगर (netअगर_running(netdev)) अणु
		netअगर_info(nic_dev, drv, netdev, "Restarting netdev\n");
		hinic_बंद(netdev);

		nic_dev->hwdev->nic_cap.num_qps = count;

		err = hinic_खोलो(netdev);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to open netdev\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		nic_dev->hwdev->nic_cap.num_qps = count;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_get_rss_hash_opts(काष्ठा hinic_dev *nic_dev,
				   काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा hinic_rss_type rss_type = अणु 0 पूर्ण;
	पूर्णांक err;

	cmd->data = 0;

	अगर (!(nic_dev->flags & HINIC_RSS_ENABLE))
		वापस 0;

	err = hinic_get_rss_type(nic_dev, nic_dev->rss_पंचांगpl_idx,
				 &rss_type);
	अगर (err)
		वापस err;

	cmd->data = RXH_IP_SRC | RXH_IP_DST;
	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		अगर (rss_type.tcp_ipv4)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल TCP_V6_FLOW:
		अगर (rss_type.tcp_ipv6)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर (rss_type.udp_ipv4)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (rss_type.udp_ipv6)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		अवरोध;
	शेष:
		cmd->data = 0;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_l4_rss_hash_ops(काष्ठा ethtool_rxnfc *cmd,
			       काष्ठा hinic_rss_type *rss_type)
अणु
	u8 rss_l4_en = 0;

	चयन (cmd->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
	हाल 0:
		rss_l4_en = 0;
		अवरोध;
	हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
		rss_l4_en = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		rss_type->tcp_ipv4 = rss_l4_en;
		अवरोध;
	हाल TCP_V6_FLOW:
		rss_type->tcp_ipv6 = rss_l4_en;
		अवरोध;
	हाल UDP_V4_FLOW:
		rss_type->udp_ipv4 = rss_l4_en;
		अवरोध;
	हाल UDP_V6_FLOW:
		rss_type->udp_ipv6 = rss_l4_en;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_rss_hash_opts(काष्ठा hinic_dev *nic_dev,
				   काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा hinic_rss_type *rss_type = &nic_dev->rss_type;
	पूर्णांक err;

	अगर (!(nic_dev->flags & HINIC_RSS_ENABLE)) अणु
		cmd->data = 0;
		वापस -EOPNOTSUPP;
	पूर्ण

	/* RSS करोes not support anything other than hashing
	 * to queues on src and dst IPs and ports
	 */
	अगर (cmd->data & ~(RXH_IP_SRC | RXH_IP_DST | RXH_L4_B_0_1 |
		RXH_L4_B_2_3))
		वापस -EINVAL;

	/* We need at least the IP SRC and DEST fields क्रम hashing */
	अगर (!(cmd->data & RXH_IP_SRC) || !(cmd->data & RXH_IP_DST))
		वापस -EINVAL;

	err = hinic_get_rss_type(nic_dev,
				 nic_dev->rss_पंचांगpl_idx, rss_type);
	अगर (err)
		वापस -EFAULT;

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		err = set_l4_rss_hash_ops(cmd, rss_type);
		अगर (err)
			वापस err;
		अवरोध;
	हाल IPV4_FLOW:
		rss_type->ipv4 = 1;
		अवरोध;
	हाल IPV6_FLOW:
		rss_type->ipv6 = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = hinic_set_rss_type(nic_dev, nic_dev->rss_पंचांगpl_idx,
				 *rss_type);
	अगर (err)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक __set_rss_rxfh(काष्ठा net_device *netdev,
			  स्थिर u32 *indir, स्थिर u8 *key)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक err;

	अगर (indir) अणु
		अगर (!nic_dev->rss_indir_user) अणु
			nic_dev->rss_indir_user =
				kzalloc(माप(u32) * HINIC_RSS_INसूची_SIZE,
					GFP_KERNEL);
			अगर (!nic_dev->rss_indir_user)
				वापस -ENOMEM;
		पूर्ण

		स_नकल(nic_dev->rss_indir_user, indir,
		       माप(u32) * HINIC_RSS_INसूची_SIZE);

		err = hinic_rss_set_indir_tbl(nic_dev,
					      nic_dev->rss_पंचांगpl_idx, indir);
		अगर (err)
			वापस -EFAULT;
	पूर्ण

	अगर (key) अणु
		अगर (!nic_dev->rss_hkey_user) अणु
			nic_dev->rss_hkey_user =
				kzalloc(HINIC_RSS_KEY_SIZE * 2, GFP_KERNEL);

			अगर (!nic_dev->rss_hkey_user)
				वापस -ENOMEM;
		पूर्ण

		स_नकल(nic_dev->rss_hkey_user, key, HINIC_RSS_KEY_SIZE);

		err = hinic_rss_set_ढाँचा_tbl(nic_dev,
						 nic_dev->rss_पंचांगpl_idx, key);
		अगर (err)
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_get_rxnfc(काष्ठा net_device *netdev,
			   काष्ठा ethtool_rxnfc *cmd, u32 *rule_locs)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = nic_dev->num_qps;
		अवरोध;
	हाल ETHTOOL_GRXFH:
		err = hinic_get_rss_hash_opts(nic_dev, cmd);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hinic_set_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		err = hinic_set_rss_hash_opts(nic_dev, cmd);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hinic_get_rxfh(काष्ठा net_device *netdev,
			  u32 *indir, u8 *key, u8 *hfunc)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u8 hash_engine_type = 0;
	पूर्णांक err = 0;

	अगर (!(nic_dev->flags & HINIC_RSS_ENABLE))
		वापस -EOPNOTSUPP;

	अगर (hfunc) अणु
		err = hinic_rss_get_hash_engine(nic_dev,
						nic_dev->rss_पंचांगpl_idx,
						&hash_engine_type);
		अगर (err)
			वापस -EFAULT;

		*hfunc = hash_engine_type ? ETH_RSS_HASH_TOP : ETH_RSS_HASH_XOR;
	पूर्ण

	अगर (indir) अणु
		err = hinic_rss_get_indir_tbl(nic_dev,
					      nic_dev->rss_पंचांगpl_idx, indir);
		अगर (err)
			वापस -EFAULT;
	पूर्ण

	अगर (key)
		err = hinic_rss_get_ढाँचा_tbl(nic_dev,
						 nic_dev->rss_पंचांगpl_idx, key);

	वापस err;
पूर्ण

अटल पूर्णांक hinic_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			  स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक err = 0;

	अगर (!(nic_dev->flags & HINIC_RSS_ENABLE))
		वापस -EOPNOTSUPP;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE) अणु
		अगर (hfunc != ETH_RSS_HASH_TOP && hfunc != ETH_RSS_HASH_XOR)
			वापस -EOPNOTSUPP;

		nic_dev->rss_hash_engine = (hfunc == ETH_RSS_HASH_XOR) ?
			HINIC_RSS_HASH_ENGINE_TYPE_XOR :
			HINIC_RSS_HASH_ENGINE_TYPE_TOEP;
		err = hinic_rss_set_hash_engine
			(nic_dev, nic_dev->rss_पंचांगpl_idx,
			nic_dev->rss_hash_engine);
		अगर (err)
			वापस -EFAULT;
	पूर्ण

	err = __set_rss_rxfh(netdev, indir, key);

	वापस err;
पूर्ण

अटल u32 hinic_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस HINIC_RSS_KEY_SIZE;
पूर्ण

अटल u32 hinic_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	वापस HINIC_RSS_INसूची_SIZE;
पूर्ण

#घोषणा ARRAY_LEN(arr) ((पूर्णांक)((पूर्णांक)माप(arr) / (पूर्णांक)माप(arr[0])))

#घोषणा HINIC_FUNC_STAT(_stat_item) अणु	\
	.name = #_stat_item, \
	.size = माप_field(काष्ठा hinic_vport_stats, _stat_item), \
	.offset = दुरत्व(काष्ठा hinic_vport_stats, _stat_item) \
पूर्ण

अटल काष्ठा hinic_stats hinic_function_stats[] = अणु
	HINIC_FUNC_STAT(tx_unicast_pkts_vport),
	HINIC_FUNC_STAT(tx_unicast_bytes_vport),
	HINIC_FUNC_STAT(tx_multicast_pkts_vport),
	HINIC_FUNC_STAT(tx_multicast_bytes_vport),
	HINIC_FUNC_STAT(tx_broadcast_pkts_vport),
	HINIC_FUNC_STAT(tx_broadcast_bytes_vport),

	HINIC_FUNC_STAT(rx_unicast_pkts_vport),
	HINIC_FUNC_STAT(rx_unicast_bytes_vport),
	HINIC_FUNC_STAT(rx_multicast_pkts_vport),
	HINIC_FUNC_STAT(rx_multicast_bytes_vport),
	HINIC_FUNC_STAT(rx_broadcast_pkts_vport),
	HINIC_FUNC_STAT(rx_broadcast_bytes_vport),

	HINIC_FUNC_STAT(tx_discard_vport),
	HINIC_FUNC_STAT(rx_discard_vport),
	HINIC_FUNC_STAT(tx_err_vport),
	HINIC_FUNC_STAT(rx_err_vport),
पूर्ण;

अटल अक्षर hinic_test_strings[][ETH_GSTRING_LEN] = अणु
	"Internal lb test  (on/offline)",
	"External lb test (external_lb)",
पूर्ण;

#घोषणा HINIC_PORT_STAT(_stat_item) अणु \
	.name = #_stat_item, \
	.size = माप_field(काष्ठा hinic_phy_port_stats, _stat_item), \
	.offset = दुरत्व(काष्ठा hinic_phy_port_stats, _stat_item) \
पूर्ण

अटल काष्ठा hinic_stats hinic_port_stats[] = अणु
	HINIC_PORT_STAT(mac_rx_total_pkt_num),
	HINIC_PORT_STAT(mac_rx_total_oct_num),
	HINIC_PORT_STAT(mac_rx_bad_pkt_num),
	HINIC_PORT_STAT(mac_rx_bad_oct_num),
	HINIC_PORT_STAT(mac_rx_good_pkt_num),
	HINIC_PORT_STAT(mac_rx_good_oct_num),
	HINIC_PORT_STAT(mac_rx_uni_pkt_num),
	HINIC_PORT_STAT(mac_rx_multi_pkt_num),
	HINIC_PORT_STAT(mac_rx_broad_pkt_num),
	HINIC_PORT_STAT(mac_tx_total_pkt_num),
	HINIC_PORT_STAT(mac_tx_total_oct_num),
	HINIC_PORT_STAT(mac_tx_bad_pkt_num),
	HINIC_PORT_STAT(mac_tx_bad_oct_num),
	HINIC_PORT_STAT(mac_tx_good_pkt_num),
	HINIC_PORT_STAT(mac_tx_good_oct_num),
	HINIC_PORT_STAT(mac_tx_uni_pkt_num),
	HINIC_PORT_STAT(mac_tx_multi_pkt_num),
	HINIC_PORT_STAT(mac_tx_broad_pkt_num),
	HINIC_PORT_STAT(mac_rx_fragment_pkt_num),
	HINIC_PORT_STAT(mac_rx_undersize_pkt_num),
	HINIC_PORT_STAT(mac_rx_undermin_pkt_num),
	HINIC_PORT_STAT(mac_rx_64_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_65_127_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_128_255_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_256_511_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_512_1023_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_1024_1518_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_1519_2047_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_2048_4095_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_4096_8191_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_8192_9216_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_9217_12287_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_12288_16383_oct_pkt_num),
	HINIC_PORT_STAT(mac_rx_1519_max_good_pkt_num),
	HINIC_PORT_STAT(mac_rx_1519_max_bad_pkt_num),
	HINIC_PORT_STAT(mac_rx_oversize_pkt_num),
	HINIC_PORT_STAT(mac_rx_jabber_pkt_num),
	HINIC_PORT_STAT(mac_rx_छोड़ो_num),
	HINIC_PORT_STAT(mac_rx_pfc_pkt_num),
	HINIC_PORT_STAT(mac_rx_pfc_pri0_pkt_num),
	HINIC_PORT_STAT(mac_rx_pfc_pri1_pkt_num),
	HINIC_PORT_STAT(mac_rx_pfc_pri2_pkt_num),
	HINIC_PORT_STAT(mac_rx_pfc_pri3_pkt_num),
	HINIC_PORT_STAT(mac_rx_pfc_pri4_pkt_num),
	HINIC_PORT_STAT(mac_rx_pfc_pri5_pkt_num),
	HINIC_PORT_STAT(mac_rx_pfc_pri6_pkt_num),
	HINIC_PORT_STAT(mac_rx_pfc_pri7_pkt_num),
	HINIC_PORT_STAT(mac_rx_control_pkt_num),
	HINIC_PORT_STAT(mac_rx_sym_err_pkt_num),
	HINIC_PORT_STAT(mac_rx_fcs_err_pkt_num),
	HINIC_PORT_STAT(mac_rx_send_app_good_pkt_num),
	HINIC_PORT_STAT(mac_rx_send_app_bad_pkt_num),
	HINIC_PORT_STAT(mac_tx_fragment_pkt_num),
	HINIC_PORT_STAT(mac_tx_undersize_pkt_num),
	HINIC_PORT_STAT(mac_tx_undermin_pkt_num),
	HINIC_PORT_STAT(mac_tx_64_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_65_127_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_128_255_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_256_511_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_512_1023_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_1024_1518_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_1519_2047_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_2048_4095_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_4096_8191_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_8192_9216_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_9217_12287_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_12288_16383_oct_pkt_num),
	HINIC_PORT_STAT(mac_tx_1519_max_good_pkt_num),
	HINIC_PORT_STAT(mac_tx_1519_max_bad_pkt_num),
	HINIC_PORT_STAT(mac_tx_oversize_pkt_num),
	HINIC_PORT_STAT(mac_tx_jabber_pkt_num),
	HINIC_PORT_STAT(mac_tx_छोड़ो_num),
	HINIC_PORT_STAT(mac_tx_pfc_pkt_num),
	HINIC_PORT_STAT(mac_tx_pfc_pri0_pkt_num),
	HINIC_PORT_STAT(mac_tx_pfc_pri1_pkt_num),
	HINIC_PORT_STAT(mac_tx_pfc_pri2_pkt_num),
	HINIC_PORT_STAT(mac_tx_pfc_pri3_pkt_num),
	HINIC_PORT_STAT(mac_tx_pfc_pri4_pkt_num),
	HINIC_PORT_STAT(mac_tx_pfc_pri5_pkt_num),
	HINIC_PORT_STAT(mac_tx_pfc_pri6_pkt_num),
	HINIC_PORT_STAT(mac_tx_pfc_pri7_pkt_num),
	HINIC_PORT_STAT(mac_tx_control_pkt_num),
	HINIC_PORT_STAT(mac_tx_err_all_pkt_num),
	HINIC_PORT_STAT(mac_tx_from_app_good_pkt_num),
	HINIC_PORT_STAT(mac_tx_from_app_bad_pkt_num),
पूर्ण;

#घोषणा HINIC_TXQ_STAT(_stat_item) अणु \
	.name = "txq%d_"#_stat_item, \
	.size = माप_field(काष्ठा hinic_txq_stats, _stat_item), \
	.offset = दुरत्व(काष्ठा hinic_txq_stats, _stat_item) \
पूर्ण

अटल काष्ठा hinic_stats hinic_tx_queue_stats[] = अणु
	HINIC_TXQ_STAT(pkts),
	HINIC_TXQ_STAT(bytes),
	HINIC_TXQ_STAT(tx_busy),
	HINIC_TXQ_STAT(tx_wake),
	HINIC_TXQ_STAT(tx_dropped),
	HINIC_TXQ_STAT(big_frags_pkts),
पूर्ण;

#घोषणा HINIC_RXQ_STAT(_stat_item) अणु \
	.name = "rxq%d_"#_stat_item, \
	.size = माप_field(काष्ठा hinic_rxq_stats, _stat_item), \
	.offset = दुरत्व(काष्ठा hinic_rxq_stats, _stat_item) \
पूर्ण

अटल काष्ठा hinic_stats hinic_rx_queue_stats[] = अणु
	HINIC_RXQ_STAT(pkts),
	HINIC_RXQ_STAT(bytes),
	HINIC_RXQ_STAT(errors),
	HINIC_RXQ_STAT(csum_errors),
	HINIC_RXQ_STAT(other_errors),
पूर्ण;

अटल व्योम get_drv_queue_stats(काष्ठा hinic_dev *nic_dev, u64 *data)
अणु
	काष्ठा hinic_txq_stats txq_stats;
	काष्ठा hinic_rxq_stats rxq_stats;
	u16 i = 0, j = 0, qid = 0;
	अक्षर *p;

	क्रम (qid = 0; qid < nic_dev->num_qps; qid++) अणु
		अगर (!nic_dev->txqs)
			अवरोध;

		hinic_txq_get_stats(&nic_dev->txqs[qid], &txq_stats);
		क्रम (j = 0; j < ARRAY_LEN(hinic_tx_queue_stats); j++, i++) अणु
			p = (अक्षर *)&txq_stats +
				hinic_tx_queue_stats[j].offset;
			data[i] = (hinic_tx_queue_stats[j].size ==
					माप(u64)) ? *(u64 *)p : *(u32 *)p;
		पूर्ण
	पूर्ण

	क्रम (qid = 0; qid < nic_dev->num_qps; qid++) अणु
		अगर (!nic_dev->rxqs)
			अवरोध;

		hinic_rxq_get_stats(&nic_dev->rxqs[qid], &rxq_stats);
		क्रम (j = 0; j < ARRAY_LEN(hinic_rx_queue_stats); j++, i++) अणु
			p = (अक्षर *)&rxq_stats +
				hinic_rx_queue_stats[j].offset;
			data[i] = (hinic_rx_queue_stats[j].size ==
					माप(u64)) ? *(u64 *)p : *(u32 *)p;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hinic_get_ethtool_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_vport_stats vport_stats = अणु0पूर्ण;
	काष्ठा hinic_phy_port_stats *port_stats;
	u16 i = 0, j = 0;
	अक्षर *p;
	पूर्णांक err;

	err = hinic_get_vport_stats(nic_dev, &vport_stats);
	अगर (err)
		netअगर_err(nic_dev, drv, netdev,
			  "Failed to get vport stats from firmware\n");

	क्रम (j = 0; j < ARRAY_LEN(hinic_function_stats); j++, i++) अणु
		p = (अक्षर *)&vport_stats + hinic_function_stats[j].offset;
		data[i] = (hinic_function_stats[j].size ==
				माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण

	port_stats = kzalloc(माप(*port_stats), GFP_KERNEL);
	अगर (!port_stats) अणु
		स_रखो(&data[i], 0,
		       ARRAY_LEN(hinic_port_stats) * माप(*data));
		i += ARRAY_LEN(hinic_port_stats);
		जाओ get_drv_stats;
	पूर्ण

	err = hinic_get_phy_port_stats(nic_dev, port_stats);
	अगर (err)
		netअगर_err(nic_dev, drv, netdev,
			  "Failed to get port stats from firmware\n");

	क्रम (j = 0; j < ARRAY_LEN(hinic_port_stats); j++, i++) अणु
		p = (अक्षर *)port_stats + hinic_port_stats[j].offset;
		data[i] = (hinic_port_stats[j].size ==
				माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण

	kमुक्त(port_stats);

get_drv_stats:
	get_drv_queue_stats(nic_dev, data + i);
पूर्ण

अटल पूर्णांक hinic_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक count, q_num;

	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस ARRAY_LEN(hinic_test_strings);
	हाल ETH_SS_STATS:
		q_num = nic_dev->num_qps;
		count = ARRAY_LEN(hinic_function_stats) +
			(ARRAY_LEN(hinic_tx_queue_stats) +
			ARRAY_LEN(hinic_rx_queue_stats)) * q_num;

		count += ARRAY_LEN(hinic_port_stats);

		वापस count;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम hinic_get_strings(काष्ठा net_device *netdev,
			      u32 stringset, u8 *data)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	अक्षर *p = (अक्षर *)data;
	u16 i, j;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, *hinic_test_strings, माप(hinic_test_strings));
		वापस;
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_LEN(hinic_function_stats); i++) अणु
			स_नकल(p, hinic_function_stats[i].name,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < ARRAY_LEN(hinic_port_stats); i++) अणु
			स_नकल(p, hinic_port_stats[i].name,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < nic_dev->num_qps; i++) अणु
			क्रम (j = 0; j < ARRAY_LEN(hinic_tx_queue_stats); j++) अणु
				प्र_लिखो(p, hinic_tx_queue_stats[j].name, i);
				p += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < nic_dev->num_qps; i++) अणु
			क्रम (j = 0; j < ARRAY_LEN(hinic_rx_queue_stats); j++) अणु
				प्र_लिखो(p, hinic_rx_queue_stats[j].name, i);
				p += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण

		वापस;
	शेष:
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक hinic_run_lp_test(काष्ठा hinic_dev *nic_dev, u32 test_समय)
अणु
	u8 *lb_test_rx_buf = nic_dev->lb_test_rx_buf;
	काष्ठा net_device *netdev = nic_dev->netdev;
	काष्ठा sk_buff *skb_पंचांगp = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	u32 cnt = test_समय * 5;
	u8 *test_data = शून्य;
	u32 i;
	u8 j;

	skb_पंचांगp = alloc_skb(LP_PKT_LEN, GFP_ATOMIC);
	अगर (!skb_पंचांगp)
		वापस -ENOMEM;

	test_data = __skb_put(skb_पंचांगp, LP_PKT_LEN);

	स_रखो(test_data, 0xFF, 2 * ETH_ALEN);
	test_data[ETH_ALEN] = 0xFE;
	test_data[2 * ETH_ALEN] = 0x08;
	test_data[2 * ETH_ALEN + 1] = 0x0;

	क्रम (i = ETH_HLEN; i < LP_PKT_LEN; i++)
		test_data[i] = i & 0xFF;

	skb_पंचांगp->queue_mapping = 0;
	skb_पंचांगp->ip_summed = CHECKSUM_COMPLETE;
	skb_पंचांगp->dev = netdev;

	क्रम (i = 0; i < cnt; i++) अणु
		nic_dev->lb_test_rx_idx = 0;
		स_रखो(lb_test_rx_buf, 0, LP_PKT_CNT * LP_PKT_LEN);

		क्रम (j = 0; j < LP_PKT_CNT; j++) अणु
			skb = pskb_copy(skb_पंचांगp, GFP_ATOMIC);
			अगर (!skb) अणु
				dev_kमुक्त_skb_any(skb_पंचांगp);
				netअगर_err(nic_dev, drv, netdev,
					  "Copy skb failed for loopback test\n");
				वापस -ENOMEM;
			पूर्ण

			/* mark index क्रम every pkt */
			skb->data[LP_PKT_LEN - 1] = j;

			अगर (hinic_lb_xmit_frame(skb, netdev)) अणु
				dev_kमुक्त_skb_any(skb);
				dev_kमुक्त_skb_any(skb_पंचांगp);
				netअगर_err(nic_dev, drv, netdev,
					  "Xmit pkt failed for loopback test\n");
				वापस -EBUSY;
			पूर्ण
		पूर्ण

		/* रुको till all pkts received to RX buffer */
		msleep(200);

		क्रम (j = 0; j < LP_PKT_CNT; j++) अणु
			अगर (स_भेद(lb_test_rx_buf + j * LP_PKT_LEN,
				   skb_पंचांगp->data, LP_PKT_LEN - 1) ||
			    (*(lb_test_rx_buf + j * LP_PKT_LEN +
			     LP_PKT_LEN - 1) != j)) अणु
				dev_kमुक्त_skb_any(skb_पंचांगp);
				netअगर_err(nic_dev, drv, netdev,
					  "Compare pkt failed in loopback test(index=0x%02x, data[%d]=0x%02x)\n",
					  j + i * LP_PKT_CNT,
					  LP_PKT_LEN - 1,
					  *(lb_test_rx_buf + j * LP_PKT_LEN +
					    LP_PKT_LEN - 1));
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_kमुक्त_skb_any(skb_पंचांगp);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_lp_test(काष्ठा hinic_dev *nic_dev, u32 flags, u32 test_समय,
		      क्रमागत diag_test_index *test_index)
अणु
	काष्ठा net_device *netdev = nic_dev->netdev;
	u8 *lb_test_rx_buf = शून्य;
	पूर्णांक err = 0;

	अगर (!(flags & ETH_TEST_FL_EXTERNAL_LB)) अणु
		*test_index = INTERNAL_LP_TEST;
		अगर (hinic_set_loopback_mode(nic_dev->hwdev,
					    HINIC_INTERNAL_LP_MODE, true)) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to set port loopback mode before loopback test\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		*test_index = EXTERNAL_LP_TEST;
	पूर्ण

	lb_test_rx_buf = vदो_स्मृति(LP_PKT_CNT * LP_PKT_LEN);
	अगर (!lb_test_rx_buf) अणु
		err = -ENOMEM;
	पूर्ण अन्यथा अणु
		nic_dev->lb_test_rx_buf = lb_test_rx_buf;
		nic_dev->lb_pkt_len = LP_PKT_LEN;
		nic_dev->flags |= HINIC_LP_TEST;
		err = hinic_run_lp_test(nic_dev, test_समय);
		nic_dev->flags &= ~HINIC_LP_TEST;
		msleep(100);
		vमुक्त(lb_test_rx_buf);
		nic_dev->lb_test_rx_buf = शून्य;
	पूर्ण

	अगर (!(flags & ETH_TEST_FL_EXTERNAL_LB)) अणु
		अगर (hinic_set_loopback_mode(nic_dev->hwdev,
					    HINIC_INTERNAL_LP_MODE, false)) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to cancel port loopback mode after loopback test\n");
			err = -EIO;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम hinic_diag_test(काष्ठा net_device *netdev,
			    काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	क्रमागत hinic_port_link_state link_state;
	क्रमागत diag_test_index test_index = 0;
	पूर्णांक err = 0;

	स_रखो(data, 0, DIAG_TEST_MAX * माप(u64));

	/* करोn't support loopback test when netdev is बंदd. */
	अगर (!(nic_dev->flags & HINIC_INTF_UP)) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Do not support loopback test when netdev is closed\n");
		eth_test->flags |= ETH_TEST_FL_FAILED;
		data[PORT_DOWN_ERR_IDX] = 1;
		वापस;
	पूर्ण

	netअगर_carrier_off(netdev);
	netअगर_tx_disable(netdev);

	err = करो_lp_test(nic_dev, eth_test->flags, LP_DEFAULT_TIME,
			 &test_index);
	अगर (err) अणु
		eth_test->flags |= ETH_TEST_FL_FAILED;
		data[test_index] = 1;
	पूर्ण

	netअगर_tx_wake_all_queues(netdev);

	err = hinic_port_link_state(nic_dev, &link_state);
	अगर (!err && link_state == HINIC_LINK_STATE_UP)
		netअगर_carrier_on(netdev);

पूर्ण

अटल पूर्णांक hinic_set_phys_id(काष्ठा net_device *netdev,
			     क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक err = 0;
	u8 port;

	port = nic_dev->hwdev->port_id;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		err = hinic_set_led_status(nic_dev->hwdev, port,
					   HINIC_LED_TYPE_LINK,
					   HINIC_LED_MODE_FORCE_2HZ);
		अगर (err)
			netअगर_err(nic_dev, drv, netdev,
				  "Set LED blinking in 2HZ failed\n");
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		err = hinic_reset_led_status(nic_dev->hwdev, port);
		अगर (err)
			netअगर_err(nic_dev, drv, netdev,
				  "Reset LED to original status failed\n");
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hinic_get_module_info(काष्ठा net_device *netdev,
				 काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u8 sfp_type_ext;
	u8 sfp_type;
	पूर्णांक err;

	err = hinic_get_sfp_type(nic_dev->hwdev, &sfp_type, &sfp_type_ext);
	अगर (err)
		वापस err;

	चयन (sfp_type) अणु
	हाल SFF8024_ID_SFP:
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		अवरोध;
	हाल SFF8024_ID_QSFP_8438:
		modinfo->type = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_MAX_LEN;
		अवरोध;
	हाल SFF8024_ID_QSFP_8436_8636:
		अगर (sfp_type_ext >= 0x3) अणु
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_MAX_LEN;

		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_MAX_LEN;
		पूर्ण
		अवरोध;
	हाल SFF8024_ID_QSFP28_8636:
		modinfo->type = ETH_MODULE_SFF_8636;
		modinfo->eeprom_len = ETH_MODULE_SFF_8636_MAX_LEN;
		अवरोध;
	शेष:
		netअगर_warn(nic_dev, drv, netdev,
			   "Optical module unknown: 0x%x\n", sfp_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_get_module_eeprom(काष्ठा net_device *netdev,
				   काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u8 sfp_data[STD_SFP_INFO_MAX_SIZE];
	u16 len;
	पूर्णांक err;

	अगर (!ee->len || ((ee->len + ee->offset) > STD_SFP_INFO_MAX_SIZE))
		वापस -EINVAL;

	स_रखो(data, 0, ee->len);

	err = hinic_get_sfp_eeprom(nic_dev->hwdev, sfp_data, &len);
	अगर (err)
		वापस err;

	स_नकल(data, sfp_data + ee->offset, ee->len);

	वापस 0;
पूर्ण

अटल पूर्णांक
hinic_get_link_ext_state(काष्ठा net_device *netdev,
			 काष्ठा ethtool_link_ext_state_info *link_ext_state_info)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);

	अगर (netअगर_carrier_ok(netdev))
		वापस -ENODATA;

	अगर (nic_dev->cable_unplugged)
		link_ext_state_info->link_ext_state =
			ETHTOOL_LINK_EXT_STATE_NO_CABLE;
	अन्यथा अगर (nic_dev->module_unrecognized)
		link_ext_state_info->link_ext_state =
			ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops hinic_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_RX_MAX_FRAMES |
				     ETHTOOL_COALESCE_TX_USECS |
				     ETHTOOL_COALESCE_TX_MAX_FRAMES,

	.get_link_ksettings = hinic_get_link_ksettings,
	.set_link_ksettings = hinic_set_link_ksettings,
	.get_drvinfo = hinic_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_link_ext_state = hinic_get_link_ext_state,
	.get_ringparam = hinic_get_ringparam,
	.set_ringparam = hinic_set_ringparam,
	.get_coalesce = hinic_get_coalesce,
	.set_coalesce = hinic_set_coalesce,
	.get_per_queue_coalesce = hinic_get_per_queue_coalesce,
	.set_per_queue_coalesce = hinic_set_per_queue_coalesce,
	.get_छोड़ोparam = hinic_get_छोड़ोparam,
	.set_छोड़ोparam = hinic_set_छोड़ोparam,
	.get_channels = hinic_get_channels,
	.set_channels = hinic_set_channels,
	.get_rxnfc = hinic_get_rxnfc,
	.set_rxnfc = hinic_set_rxnfc,
	.get_rxfh_key_size = hinic_get_rxfh_key_size,
	.get_rxfh_indir_size = hinic_get_rxfh_indir_size,
	.get_rxfh = hinic_get_rxfh,
	.set_rxfh = hinic_set_rxfh,
	.get_sset_count = hinic_get_sset_count,
	.get_ethtool_stats = hinic_get_ethtool_stats,
	.get_strings = hinic_get_strings,
	.self_test = hinic_diag_test,
	.set_phys_id = hinic_set_phys_id,
	.get_module_info = hinic_get_module_info,
	.get_module_eeprom = hinic_get_module_eeprom,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops hinicvf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_RX_MAX_FRAMES |
				     ETHTOOL_COALESCE_TX_USECS |
				     ETHTOOL_COALESCE_TX_MAX_FRAMES,

	.get_link_ksettings = hinic_get_link_ksettings,
	.get_drvinfo = hinic_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_ringparam = hinic_get_ringparam,
	.set_ringparam = hinic_set_ringparam,
	.get_coalesce = hinic_get_coalesce,
	.set_coalesce = hinic_set_coalesce,
	.get_per_queue_coalesce = hinic_get_per_queue_coalesce,
	.set_per_queue_coalesce = hinic_set_per_queue_coalesce,
	.get_channels = hinic_get_channels,
	.set_channels = hinic_set_channels,
	.get_rxnfc = hinic_get_rxnfc,
	.set_rxnfc = hinic_set_rxnfc,
	.get_rxfh_key_size = hinic_get_rxfh_key_size,
	.get_rxfh_indir_size = hinic_get_rxfh_indir_size,
	.get_rxfh = hinic_get_rxfh,
	.set_rxfh = hinic_set_rxfh,
	.get_sset_count = hinic_get_sset_count,
	.get_ethtool_stats = hinic_get_ethtool_stats,
	.get_strings = hinic_get_strings,
पूर्ण;

व्योम hinic_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);

	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		netdev->ethtool_ops = &hinic_ethtool_ops;
	अन्यथा
		netdev->ethtool_ops = &hinicvf_ethtool_ops;
पूर्ण
