<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved */

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>

#समावेश "prestera_ethtool.h"
#समावेश "prestera.h"
#समावेश "prestera_hw.h"

#घोषणा PRESTERA_STATS_CNT \
	(माप(काष्ठा prestera_port_stats) / माप(u64))
#घोषणा PRESTERA_STATS_IDX(name) \
	(दुरत्व(काष्ठा prestera_port_stats, name) / माप(u64))
#घोषणा PRESTERA_STATS_FIELD(name)	\
	[PRESTERA_STATS_IDX(name)] = __stringअगरy(name)

अटल स्थिर अक्षर driver_kind[] = "prestera";

अटल स्थिर काष्ठा prestera_link_mode अणु
	क्रमागत ethtool_link_mode_bit_indices eth_mode;
	u32 speed;
	u64 pr_mask;
	u8 duplex;
	u8 port_type;
पूर्ण port_link_modes[PRESTERA_LINK_MODE_MAX] = अणु
	[PRESTERA_LINK_MODE_10baseT_Half] = अणु
		.eth_mode =  ETHTOOL_LINK_MODE_10baseT_Half_BIT,
		.speed = 10,
		.pr_mask = 1 << PRESTERA_LINK_MODE_10baseT_Half,
		.duplex = PRESTERA_PORT_DUPLEX_HALF,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_10baseT_Full] = अणु
		.eth_mode =  ETHTOOL_LINK_MODE_10baseT_Full_BIT,
		.speed = 10,
		.pr_mask = 1 << PRESTERA_LINK_MODE_10baseT_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_100baseT_Half] = अणु
		.eth_mode =  ETHTOOL_LINK_MODE_100baseT_Half_BIT,
		.speed = 100,
		.pr_mask = 1 << PRESTERA_LINK_MODE_100baseT_Half,
		.duplex = PRESTERA_PORT_DUPLEX_HALF,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_100baseT_Full] = अणु
		.eth_mode =  ETHTOOL_LINK_MODE_100baseT_Full_BIT,
		.speed = 100,
		.pr_mask = 1 << PRESTERA_LINK_MODE_100baseT_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_1000baseT_Half] = अणु
		.eth_mode =  ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
		.speed = 1000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_1000baseT_Half,
		.duplex = PRESTERA_PORT_DUPLEX_HALF,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_1000baseT_Full] = अणु
		.eth_mode =  ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
		.speed = 1000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_1000baseT_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_1000baseX_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
		.speed = 1000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_1000baseX_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_FIBRE,
	पूर्ण,
	[PRESTERA_LINK_MODE_1000baseKX_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
		.speed = 1000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_1000baseKX_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_2500baseX_Full] = अणु
		.eth_mode =  ETHTOOL_LINK_MODE_2500baseX_Full_BIT,
		.speed = 2500,
		.pr_mask = 1 << PRESTERA_LINK_MODE_2500baseX_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
	पूर्ण,
	[PRESTERA_LINK_MODE_10GbaseKR_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
		.speed = 10000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_10GbaseKR_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_10GbaseSR_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
		.speed = 10000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_10GbaseSR_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_FIBRE,
	पूर्ण,
	[PRESTERA_LINK_MODE_10GbaseLR_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
		.speed = 10000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_10GbaseLR_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_FIBRE,
	पूर्ण,
	[PRESTERA_LINK_MODE_20GbaseKR2_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT,
		.speed = 20000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_20GbaseKR2_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_25GbaseCR_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
		.speed = 25000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_25GbaseCR_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_DA,
	पूर्ण,
	[PRESTERA_LINK_MODE_25GbaseKR_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
		.speed = 25000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_25GbaseKR_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_25GbaseSR_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
		.speed = 25000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_25GbaseSR_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_FIBRE,
	पूर्ण,
	[PRESTERA_LINK_MODE_40GbaseKR4_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
		.speed = 40000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_40GbaseKR4_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_40GbaseCR4_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
		.speed = 40000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_40GbaseCR4_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_DA,
	पूर्ण,
	[PRESTERA_LINK_MODE_40GbaseSR4_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
		.speed = 40000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_40GbaseSR4_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_FIBRE,
	पूर्ण,
	[PRESTERA_LINK_MODE_50GbaseCR2_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
		.speed = 50000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_50GbaseCR2_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_DA,
	पूर्ण,
	[PRESTERA_LINK_MODE_50GbaseKR2_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
		.speed = 50000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_50GbaseKR2_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_50GbaseSR2_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
		.speed = 50000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_50GbaseSR2_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_FIBRE,
	पूर्ण,
	[PRESTERA_LINK_MODE_100GbaseKR4_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
		.speed = 100000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_100GbaseKR4_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_TP,
	पूर्ण,
	[PRESTERA_LINK_MODE_100GbaseSR4_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
		.speed = 100000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_100GbaseSR4_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_FIBRE,
	पूर्ण,
	[PRESTERA_LINK_MODE_100GbaseCR4_Full] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
		.speed = 100000,
		.pr_mask = 1 << PRESTERA_LINK_MODE_100GbaseCR4_Full,
		.duplex = PRESTERA_PORT_DUPLEX_FULL,
		.port_type = PRESTERA_PORT_TYPE_DA,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा prestera_fec अणु
	u32 eth_fec;
	क्रमागत ethtool_link_mode_bit_indices eth_mode;
	u8 pr_fec;
पूर्ण port_fec_caps[PRESTERA_PORT_FEC_MAX] = अणु
	[PRESTERA_PORT_FEC_OFF] = अणु
		.eth_fec = ETHTOOL_FEC_OFF,
		.eth_mode = ETHTOOL_LINK_MODE_FEC_NONE_BIT,
		.pr_fec = 1 << PRESTERA_PORT_FEC_OFF,
	पूर्ण,
	[PRESTERA_PORT_FEC_BASER] = अणु
		.eth_fec = ETHTOOL_FEC_BASER,
		.eth_mode = ETHTOOL_LINK_MODE_FEC_BASER_BIT,
		.pr_fec = 1 << PRESTERA_PORT_FEC_BASER,
	पूर्ण,
	[PRESTERA_PORT_FEC_RS] = अणु
		.eth_fec = ETHTOOL_FEC_RS,
		.eth_mode = ETHTOOL_LINK_MODE_FEC_RS_BIT,
		.pr_fec = 1 << PRESTERA_PORT_FEC_RS,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा prestera_port_type अणु
	क्रमागत ethtool_link_mode_bit_indices eth_mode;
	u8 eth_type;
पूर्ण port_types[PRESTERA_PORT_TYPE_MAX] = अणु
	[PRESTERA_PORT_TYPE_NONE] = अणु
		.eth_mode = __ETHTOOL_LINK_MODE_MASK_NBITS,
		.eth_type = PORT_NONE,
	पूर्ण,
	[PRESTERA_PORT_TYPE_TP] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_TP_BIT,
		.eth_type = PORT_TP,
	पूर्ण,
	[PRESTERA_PORT_TYPE_AUI] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_AUI_BIT,
		.eth_type = PORT_AUI,
	पूर्ण,
	[PRESTERA_PORT_TYPE_MII] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_MII_BIT,
		.eth_type = PORT_MII,
	पूर्ण,
	[PRESTERA_PORT_TYPE_FIBRE] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_FIBRE_BIT,
		.eth_type = PORT_FIBRE,
	पूर्ण,
	[PRESTERA_PORT_TYPE_BNC] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_BNC_BIT,
		.eth_type = PORT_BNC,
	पूर्ण,
	[PRESTERA_PORT_TYPE_DA] = अणु
		.eth_mode = ETHTOOL_LINK_MODE_TP_BIT,
		.eth_type = PORT_TP,
	पूर्ण,
	[PRESTERA_PORT_TYPE_OTHER] = अणु
		.eth_mode = __ETHTOOL_LINK_MODE_MASK_NBITS,
		.eth_type = PORT_OTHER,
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर prestera_cnt_name[PRESTERA_STATS_CNT][ETH_GSTRING_LEN] = अणु
	PRESTERA_STATS_FIELD(good_octets_received),
	PRESTERA_STATS_FIELD(bad_octets_received),
	PRESTERA_STATS_FIELD(mac_trans_error),
	PRESTERA_STATS_FIELD(broadcast_frames_received),
	PRESTERA_STATS_FIELD(multicast_frames_received),
	PRESTERA_STATS_FIELD(frames_64_octets),
	PRESTERA_STATS_FIELD(frames_65_to_127_octets),
	PRESTERA_STATS_FIELD(frames_128_to_255_octets),
	PRESTERA_STATS_FIELD(frames_256_to_511_octets),
	PRESTERA_STATS_FIELD(frames_512_to_1023_octets),
	PRESTERA_STATS_FIELD(frames_1024_to_max_octets),
	PRESTERA_STATS_FIELD(excessive_collision),
	PRESTERA_STATS_FIELD(multicast_frames_sent),
	PRESTERA_STATS_FIELD(broadcast_frames_sent),
	PRESTERA_STATS_FIELD(fc_sent),
	PRESTERA_STATS_FIELD(fc_received),
	PRESTERA_STATS_FIELD(buffer_overrun),
	PRESTERA_STATS_FIELD(undersize),
	PRESTERA_STATS_FIELD(fragments),
	PRESTERA_STATS_FIELD(oversize),
	PRESTERA_STATS_FIELD(jabber),
	PRESTERA_STATS_FIELD(rx_error_frame_received),
	PRESTERA_STATS_FIELD(bad_crc),
	PRESTERA_STATS_FIELD(collisions),
	PRESTERA_STATS_FIELD(late_collision),
	PRESTERA_STATS_FIELD(unicast_frames_received),
	PRESTERA_STATS_FIELD(unicast_frames_sent),
	PRESTERA_STATS_FIELD(sent_multiple),
	PRESTERA_STATS_FIELD(sent_deferred),
	PRESTERA_STATS_FIELD(good_octets_sent),
पूर्ण;

अटल व्योम prestera_ethtool_get_drvinfo(काष्ठा net_device *dev,
					 काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	काष्ठा prestera_चयन *sw = port->sw;

	strlcpy(drvinfo->driver, driver_kind, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, dev_name(prestera_dev(sw)),
		माप(drvinfo->bus_info));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%d.%d.%d",
		 sw->dev->fw_rev.maj,
		 sw->dev->fw_rev.min,
		 sw->dev->fw_rev.sub);
पूर्ण

अटल u8 prestera_port_type_get(काष्ठा prestera_port *port)
अणु
	अगर (port->caps.type < PRESTERA_PORT_TYPE_MAX)
		वापस port_types[port->caps.type].eth_type;

	वापस PORT_OTHER;
पूर्ण

अटल पूर्णांक prestera_port_type_set(स्थिर काष्ठा ethtool_link_ksettings *ecmd,
				  काष्ठा prestera_port *port)
अणु
	u32 new_mode = PRESTERA_LINK_MODE_MAX;
	u32 type, mode;
	पूर्णांक err;

	क्रम (type = 0; type < PRESTERA_PORT_TYPE_MAX; type++) अणु
		अगर (port_types[type].eth_type == ecmd->base.port &&
		    test_bit(port_types[type].eth_mode,
			     ecmd->link_modes.supported)) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (type == port->caps.type)
		वापस 0;
	अगर (type != port->caps.type && ecmd->base.स्वतःneg == AUTONEG_ENABLE)
		वापस -EINVAL;
	अगर (type == PRESTERA_PORT_TYPE_MAX)
		वापस -EOPNOTSUPP;

	क्रम (mode = 0; mode < PRESTERA_LINK_MODE_MAX; mode++) अणु
		अगर ((port_link_modes[mode].pr_mask &
		    port->caps.supp_link_modes) &&
		    type == port_link_modes[mode].port_type) अणु
			new_mode = mode;
		पूर्ण
	पूर्ण

	अगर (new_mode < PRESTERA_LINK_MODE_MAX)
		err = prestera_hw_port_link_mode_set(port, new_mode);
	अन्यथा
		err = -EINVAL;

	अगर (err)
		वापस err;

	port->caps.type = type;
	port->स्वतःneg = false;

	वापस 0;
पूर्ण

अटल व्योम prestera_modes_to_eth(अचिन्हित दीर्घ *eth_modes, u64 link_modes,
				  u8 fec, u8 type)
अणु
	u32 mode;

	क्रम (mode = 0; mode < PRESTERA_LINK_MODE_MAX; mode++) अणु
		अगर ((port_link_modes[mode].pr_mask & link_modes) == 0)
			जारी;

		अगर (type != PRESTERA_PORT_TYPE_NONE &&
		    port_link_modes[mode].port_type != type)
			जारी;

		__set_bit(port_link_modes[mode].eth_mode, eth_modes);
	पूर्ण

	क्रम (mode = 0; mode < PRESTERA_PORT_FEC_MAX; mode++) अणु
		अगर ((port_fec_caps[mode].pr_fec & fec) == 0)
			जारी;

		__set_bit(port_fec_caps[mode].eth_mode, eth_modes);
	पूर्ण
पूर्ण

अटल व्योम prestera_modes_from_eth(स्थिर अचिन्हित दीर्घ *eth_modes,
				    u64 *link_modes, u8 *fec, u8 type)
अणु
	u64 adver_modes = 0;
	u32 fec_modes = 0;
	u32 mode;

	क्रम (mode = 0; mode < PRESTERA_LINK_MODE_MAX; mode++) अणु
		अगर (!test_bit(port_link_modes[mode].eth_mode, eth_modes))
			जारी;

		अगर (port_link_modes[mode].port_type != type)
			जारी;

		adver_modes |= port_link_modes[mode].pr_mask;
	पूर्ण

	क्रम (mode = 0; mode < PRESTERA_PORT_FEC_MAX; mode++) अणु
		अगर (!test_bit(port_fec_caps[mode].eth_mode, eth_modes))
			जारी;

		fec_modes |= port_fec_caps[mode].pr_fec;
	पूर्ण

	*link_modes = adver_modes;
	*fec = fec_modes;
पूर्ण

अटल व्योम prestera_port_supp_types_get(काष्ठा ethtool_link_ksettings *ecmd,
					 काष्ठा prestera_port *port)
अणु
	u32 mode;
	u8 ptype;

	क्रम (mode = 0; mode < PRESTERA_LINK_MODE_MAX; mode++) अणु
		अगर ((port_link_modes[mode].pr_mask &
		    port->caps.supp_link_modes) == 0)
			जारी;

		ptype = port_link_modes[mode].port_type;
		__set_bit(port_types[ptype].eth_mode,
			  ecmd->link_modes.supported);
	पूर्ण
पूर्ण

अटल व्योम prestera_port_remote_cap_get(काष्ठा ethtool_link_ksettings *ecmd,
					 काष्ठा prestera_port *port)
अणु
	bool asym_छोड़ो;
	bool छोड़ो;
	u64 biपंचांगap;
	पूर्णांक err;

	err = prestera_hw_port_remote_cap_get(port, &biपंचांगap);
	अगर (!err) अणु
		prestera_modes_to_eth(ecmd->link_modes.lp_advertising,
				      biपंचांगap, 0, PRESTERA_PORT_TYPE_NONE);

		अगर (!biपंचांगap_empty(ecmd->link_modes.lp_advertising,
				  __ETHTOOL_LINK_MODE_MASK_NBITS)) अणु
			ethtool_link_ksettings_add_link_mode(ecmd,
							     lp_advertising,
							     Autoneg);
		पूर्ण
	पूर्ण

	err = prestera_hw_port_remote_fc_get(port, &छोड़ो, &asym_छोड़ो);
	अगर (err)
		वापस;

	अगर (छोड़ो)
		ethtool_link_ksettings_add_link_mode(ecmd,
						     lp_advertising,
						     Pause);
	अगर (asym_छोड़ो)
		ethtool_link_ksettings_add_link_mode(ecmd,
						     lp_advertising,
						     Asym_Pause);
पूर्ण

अटल व्योम prestera_port_speed_get(काष्ठा ethtool_link_ksettings *ecmd,
				    काष्ठा prestera_port *port)
अणु
	u32 speed;
	पूर्णांक err;

	err = prestera_hw_port_speed_get(port, &speed);
	ecmd->base.speed = err ? SPEED_UNKNOWN : speed;
पूर्ण

अटल व्योम prestera_port_duplex_get(काष्ठा ethtool_link_ksettings *ecmd,
				     काष्ठा prestera_port *port)
अणु
	u8 duplex;
	पूर्णांक err;

	err = prestera_hw_port_duplex_get(port, &duplex);
	अगर (err) अणु
		ecmd->base.duplex = DUPLEX_UNKNOWN;
		वापस;
	पूर्ण

	ecmd->base.duplex = duplex == PRESTERA_PORT_DUPLEX_FULL ?
			    DUPLEX_FULL : DUPLEX_HALF;
पूर्ण

अटल पूर्णांक
prestera_ethtool_get_link_ksettings(काष्ठा net_device *dev,
				    काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);

	ethtool_link_ksettings_zero_link_mode(ecmd, supported);
	ethtool_link_ksettings_zero_link_mode(ecmd, advertising);
	ethtool_link_ksettings_zero_link_mode(ecmd, lp_advertising);

	ecmd->base.स्वतःneg = port->स्वतःneg ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	अगर (port->caps.type == PRESTERA_PORT_TYPE_TP) अणु
		ethtool_link_ksettings_add_link_mode(ecmd, supported, Autoneg);

		अगर (netअगर_running(dev) &&
		    (port->स्वतःneg ||
		     port->caps.transceiver == PRESTERA_PORT_TCVR_COPPER))
			ethtool_link_ksettings_add_link_mode(ecmd, advertising,
							     Autoneg);
	पूर्ण

	prestera_modes_to_eth(ecmd->link_modes.supported,
			      port->caps.supp_link_modes,
			      port->caps.supp_fec,
			      port->caps.type);

	prestera_port_supp_types_get(ecmd, port);

	अगर (netअगर_carrier_ok(dev)) अणु
		prestera_port_speed_get(ecmd, port);
		prestera_port_duplex_get(ecmd, port);
	पूर्ण अन्यथा अणु
		ecmd->base.speed = SPEED_UNKNOWN;
		ecmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	ecmd->base.port = prestera_port_type_get(port);

	अगर (port->स्वतःneg) अणु
		अगर (netअगर_running(dev))
			prestera_modes_to_eth(ecmd->link_modes.advertising,
					      port->adver_link_modes,
					      port->adver_fec,
					      port->caps.type);

		अगर (netअगर_carrier_ok(dev) &&
		    port->caps.transceiver == PRESTERA_PORT_TCVR_COPPER)
			prestera_port_remote_cap_get(ecmd, port);
	पूर्ण

	अगर (port->caps.type == PRESTERA_PORT_TYPE_TP &&
	    port->caps.transceiver == PRESTERA_PORT_TCVR_COPPER)
		prestera_hw_port_mdix_get(port, &ecmd->base.eth_tp_mdix,
					  &ecmd->base.eth_tp_mdix_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_mdix_set(स्थिर काष्ठा ethtool_link_ksettings *ecmd,
				  काष्ठा prestera_port *port)
अणु
	अगर (ecmd->base.eth_tp_mdix_ctrl != ETH_TP_MDI_INVALID &&
	    port->caps.transceiver == PRESTERA_PORT_TCVR_COPPER &&
	    port->caps.type == PRESTERA_PORT_TYPE_TP)
		वापस prestera_hw_port_mdix_set(port,
						 ecmd->base.eth_tp_mdix_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_link_mode_set(काष्ठा prestera_port *port,
				       u32 speed, u8 duplex, u8 type)
अणु
	u32 new_mode = PRESTERA_LINK_MODE_MAX;
	u32 mode;

	क्रम (mode = 0; mode < PRESTERA_LINK_MODE_MAX; mode++) अणु
		अगर (speed != port_link_modes[mode].speed)
			जारी;

		अगर (duplex != port_link_modes[mode].duplex)
			जारी;

		अगर (!(port_link_modes[mode].pr_mask &
		    port->caps.supp_link_modes))
			जारी;

		अगर (type != port_link_modes[mode].port_type)
			जारी;

		new_mode = mode;
		अवरोध;
	पूर्ण

	अगर (new_mode == PRESTERA_LINK_MODE_MAX)
		वापस -EOPNOTSUPP;

	वापस prestera_hw_port_link_mode_set(port, new_mode);
पूर्ण

अटल पूर्णांक
prestera_port_speed_duplex_set(स्थिर काष्ठा ethtool_link_ksettings *ecmd,
			       काष्ठा prestera_port *port)
अणु
	u32 curr_mode;
	u8 duplex;
	u32 speed;
	पूर्णांक err;

	err = prestera_hw_port_link_mode_get(port, &curr_mode);
	अगर (err)
		वापस err;
	अगर (curr_mode >= PRESTERA_LINK_MODE_MAX)
		वापस -EINVAL;

	अगर (ecmd->base.duplex != DUPLEX_UNKNOWN)
		duplex = ecmd->base.duplex == DUPLEX_FULL ?
			 PRESTERA_PORT_DUPLEX_FULL : PRESTERA_PORT_DUPLEX_HALF;
	अन्यथा
		duplex = port_link_modes[curr_mode].duplex;

	अगर (ecmd->base.speed != SPEED_UNKNOWN)
		speed = ecmd->base.speed;
	अन्यथा
		speed = port_link_modes[curr_mode].speed;

	वापस prestera_port_link_mode_set(port, speed, duplex,
					   port->caps.type);
पूर्ण

अटल पूर्णांक
prestera_ethtool_set_link_ksettings(काष्ठा net_device *dev,
				    स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	u64 adver_modes;
	u8 adver_fec;
	पूर्णांक err;

	err = prestera_port_type_set(ecmd, port);
	अगर (err)
		वापस err;

	अगर (port->caps.transceiver == PRESTERA_PORT_TCVR_COPPER) अणु
		err = prestera_port_mdix_set(ecmd, port);
		अगर (err)
			वापस err;
	पूर्ण

	prestera_modes_from_eth(ecmd->link_modes.advertising, &adver_modes,
				&adver_fec, port->caps.type);

	err = prestera_port_स्वतःneg_set(port,
					ecmd->base.स्वतःneg == AUTONEG_ENABLE,
					adver_modes, adver_fec);
	अगर (err)
		वापस err;

	अगर (ecmd->base.स्वतःneg == AUTONEG_DISABLE) अणु
		err = prestera_port_speed_duplex_set(ecmd, port);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_ethtool_get_fecparam(काष्ठा net_device *dev,
					 काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	u8 active;
	u32 mode;
	पूर्णांक err;

	err = prestera_hw_port_fec_get(port, &active);
	अगर (err)
		वापस err;

	fecparam->fec = 0;

	क्रम (mode = 0; mode < PRESTERA_PORT_FEC_MAX; mode++) अणु
		अगर ((port_fec_caps[mode].pr_fec & port->caps.supp_fec) == 0)
			जारी;

		fecparam->fec |= port_fec_caps[mode].eth_fec;
	पूर्ण

	अगर (active < PRESTERA_PORT_FEC_MAX)
		fecparam->active_fec = port_fec_caps[active].eth_fec;
	अन्यथा
		fecparam->active_fec = ETHTOOL_FEC_AUTO;

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_ethtool_set_fecparam(काष्ठा net_device *dev,
					 काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	u8 fec, active;
	u32 mode;
	पूर्णांक err;

	अगर (port->स्वतःneg) अणु
		netdev_err(dev, "FEC set is not allowed while autoneg is on\n");
		वापस -EINVAL;
	पूर्ण

	err = prestera_hw_port_fec_get(port, &active);
	अगर (err)
		वापस err;

	fec = PRESTERA_PORT_FEC_MAX;
	क्रम (mode = 0; mode < PRESTERA_PORT_FEC_MAX; mode++) अणु
		अगर ((port_fec_caps[mode].eth_fec & fecparam->fec) &&
		    (port_fec_caps[mode].pr_fec & port->caps.supp_fec)) अणु
			fec = mode;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fec == active)
		वापस 0;

	अगर (fec == PRESTERA_PORT_FEC_MAX)
		वापस -EOPNOTSUPP;

	वापस prestera_hw_port_fec_set(port, fec);
पूर्ण

अटल पूर्णांक prestera_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस PRESTERA_STATS_CNT;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम prestera_ethtool_get_strings(काष्ठा net_device *dev,
					 u32 stringset, u8 *data)
अणु
	अगर (stringset != ETH_SS_STATS)
		वापस;

	स_नकल(data, prestera_cnt_name, माप(prestera_cnt_name));
पूर्ण

अटल व्योम prestera_ethtool_get_stats(काष्ठा net_device *dev,
				       काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	काष्ठा prestera_port_stats *port_stats;

	port_stats = &port->cached_hw_stats.stats;

	स_नकल(data, port_stats, माप(*port_stats));
पूर्ण

अटल पूर्णांक prestera_ethtool_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);

	अगर (netअगर_running(dev) &&
	    port->caps.transceiver == PRESTERA_PORT_TCVR_COPPER &&
	    port->caps.type == PRESTERA_PORT_TYPE_TP)
		वापस prestera_hw_port_स्वतःneg_restart(port);

	वापस -EINVAL;
पूर्ण

स्थिर काष्ठा ethtool_ops prestera_ethtool_ops = अणु
	.get_drvinfo = prestera_ethtool_get_drvinfo,
	.get_link_ksettings = prestera_ethtool_get_link_ksettings,
	.set_link_ksettings = prestera_ethtool_set_link_ksettings,
	.get_fecparam = prestera_ethtool_get_fecparam,
	.set_fecparam = prestera_ethtool_set_fecparam,
	.get_sset_count = prestera_ethtool_get_sset_count,
	.get_strings = prestera_ethtool_get_strings,
	.get_ethtool_stats = prestera_ethtool_get_stats,
	.get_link = ethtool_op_get_link,
	.nway_reset = prestera_ethtool_nway_reset
पूर्ण;
