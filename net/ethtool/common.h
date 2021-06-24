<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित _ETHTOOL_COMMON_H
#घोषणा _ETHTOOL_COMMON_H

#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>

#घोषणा ETHTOOL_DEV_FEATURE_WORDS	DIV_ROUND_UP(NETDEV_FEATURE_COUNT, 32)

/* compose link mode index from speed, type and duplex */
#घोषणा ETHTOOL_LINK_MODE(speed, type, duplex) \
	ETHTOOL_LINK_MODE_ ## speed ## base ## type ## _ ## duplex ## _BIT

#घोषणा __SOF_TIMESTAMPING_CNT (स्थिर_ilog2(SOF_TIMESTAMPING_LAST) + 1)

काष्ठा link_mode_info अणु
	पूर्णांक				speed;
	u8				lanes;
	u8				duplex;
पूर्ण;

बाह्य स्थिर अक्षर
netdev_features_strings[NETDEV_FEATURE_COUNT][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर
rss_hash_func_strings[ETH_RSS_HASH_FUNCS_COUNT][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर
tunable_strings[__ETHTOOL_TUNABLE_COUNT][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर
phy_tunable_strings[__ETHTOOL_PHY_TUNABLE_COUNT][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर link_mode_names[][ETH_GSTRING_LEN];
बाह्य स्थिर काष्ठा link_mode_info link_mode_params[];
बाह्य स्थिर अक्षर netअगर_msg_class_names[][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर wol_mode_names[][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर sof_बारtamping_names[][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर ts_tx_type_names[][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर ts_rx_filter_names[][ETH_GSTRING_LEN];
बाह्य स्थिर अक्षर udp_tunnel_type_names[][ETH_GSTRING_LEN];

पूर्णांक __ethtool_get_link(काष्ठा net_device *dev);

bool convert_legacy_settings_to_link_ksettings(
	काष्ठा ethtool_link_ksettings *link_ksettings,
	स्थिर काष्ठा ethtool_cmd *legacy_settings);
पूर्णांक ethtool_get_max_rxfh_channel(काष्ठा net_device *dev, u32 *max);
पूर्णांक __ethtool_get_ts_info(काष्ठा net_device *dev, काष्ठा ethtool_ts_info *info);

बाह्य स्थिर काष्ठा ethtool_phy_ops *ethtool_phy_ops;

पूर्णांक ethtool_get_module_info_call(काष्ठा net_device *dev,
				 काष्ठा ethtool_modinfo *modinfo);
पूर्णांक ethtool_get_module_eeprom_call(काष्ठा net_device *dev,
				   काष्ठा ethtool_eeprom *ee, u8 *data);

#पूर्ण_अगर /* _ETHTOOL_COMMON_H */
