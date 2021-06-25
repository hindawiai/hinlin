<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/core/ethtool.c - Ethtool ioctl handler
 * Copyright (c) 2003 Matthew Wilcox <matthew@wil.cx>
 *
 * This file is where we call all the ethtool_ops commands to get
 * the inक्रमmation ethtool needs.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/net.h>
#समावेश <net/devlink.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश <net/flow_offload.h>
#समावेश <linux/ethtool_netlink.h>
#समावेश <generated/utsrelease.h>
#समावेश "common.h"

/*
 * Some useful ethtool_ops methods that're device independent.
 * If we find that all drivers want to करो the same thing here,
 * we can turn these पूर्णांकo dev_() function calls.
 */

u32 ethtool_op_get_link(काष्ठा net_device *dev)
अणु
	वापस netअगर_carrier_ok(dev) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL(ethtool_op_get_link);

पूर्णांक ethtool_op_get_ts_info(काष्ठा net_device *dev, काष्ठा ethtool_ts_info *info)
अणु
	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE;
	info->phc_index = -1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ethtool_op_get_ts_info);

/* Handlers क्रम each ethtool command */

अटल पूर्णांक ethtool_get_features(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_gfeatures cmd = अणु
		.cmd = ETHTOOL_GFEATURES,
		.size = ETHTOOL_DEV_FEATURE_WORDS,
	पूर्ण;
	काष्ठा ethtool_get_features_block features[ETHTOOL_DEV_FEATURE_WORDS];
	u32 __user *sizeaddr;
	u32 copy_size;
	पूर्णांक i;

	/* in हाल feature bits run out again */
	BUILD_BUG_ON(ETHTOOL_DEV_FEATURE_WORDS * माप(u32) > माप(netdev_features_t));

	क्रम (i = 0; i < ETHTOOL_DEV_FEATURE_WORDS; ++i) अणु
		features[i].available = (u32)(dev->hw_features >> (32 * i));
		features[i].requested = (u32)(dev->wanted_features >> (32 * i));
		features[i].active = (u32)(dev->features >> (32 * i));
		features[i].never_changed =
			(u32)(NETIF_F_NEVER_CHANGE >> (32 * i));
	पूर्ण

	sizeaddr = useraddr + दुरत्व(काष्ठा ethtool_gfeatures, size);
	अगर (get_user(copy_size, sizeaddr))
		वापस -EFAULT;

	अगर (copy_size > ETHTOOL_DEV_FEATURE_WORDS)
		copy_size = ETHTOOL_DEV_FEATURE_WORDS;

	अगर (copy_to_user(useraddr, &cmd, माप(cmd)))
		वापस -EFAULT;
	useraddr += माप(cmd);
	अगर (copy_to_user(useraddr, features, copy_size * माप(*features)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_features(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_sfeatures cmd;
	काष्ठा ethtool_set_features_block features[ETHTOOL_DEV_FEATURE_WORDS];
	netdev_features_t wanted = 0, valid = 0;
	पूर्णांक i, ret = 0;

	अगर (copy_from_user(&cmd, useraddr, माप(cmd)))
		वापस -EFAULT;
	useraddr += माप(cmd);

	अगर (cmd.size != ETHTOOL_DEV_FEATURE_WORDS)
		वापस -EINVAL;

	अगर (copy_from_user(features, useraddr, माप(features)))
		वापस -EFAULT;

	क्रम (i = 0; i < ETHTOOL_DEV_FEATURE_WORDS; ++i) अणु
		valid |= (netdev_features_t)features[i].valid << (32 * i);
		wanted |= (netdev_features_t)features[i].requested << (32 * i);
	पूर्ण

	अगर (valid & ~NETIF_F_ETHTOOL_BITS)
		वापस -EINVAL;

	अगर (valid & ~dev->hw_features) अणु
		valid &= dev->hw_features;
		ret |= ETHTOOL_F_UNSUPPORTED;
	पूर्ण

	dev->wanted_features &= ~valid;
	dev->wanted_features |= wanted & valid;
	__netdev_update_features(dev);

	अगर ((dev->wanted_features ^ dev->features) & valid)
		ret |= ETHTOOL_F_WISH;

	वापस ret;
पूर्ण

अटल पूर्णांक __ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	स्थिर काष्ठा ethtool_phy_ops *phy_ops = ethtool_phy_ops;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;

	अगर (sset == ETH_SS_FEATURES)
		वापस ARRAY_SIZE(netdev_features_strings);

	अगर (sset == ETH_SS_RSS_HASH_FUNCS)
		वापस ARRAY_SIZE(rss_hash_func_strings);

	अगर (sset == ETH_SS_TUNABLES)
		वापस ARRAY_SIZE(tunable_strings);

	अगर (sset == ETH_SS_PHY_TUNABLES)
		वापस ARRAY_SIZE(phy_tunable_strings);

	अगर (sset == ETH_SS_PHY_STATS && dev->phydev &&
	    !ops->get_ethtool_phy_stats &&
	    phy_ops && phy_ops->get_sset_count)
		वापस phy_ops->get_sset_count(dev->phydev);

	अगर (sset == ETH_SS_LINK_MODES)
		वापस __ETHTOOL_LINK_MODE_MASK_NBITS;

	अगर (ops->get_sset_count && ops->get_strings)
		वापस ops->get_sset_count(dev, sset);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम __ethtool_get_strings(काष्ठा net_device *dev,
	u32 stringset, u8 *data)
अणु
	स्थिर काष्ठा ethtool_phy_ops *phy_ops = ethtool_phy_ops;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;

	अगर (stringset == ETH_SS_FEATURES)
		स_नकल(data, netdev_features_strings,
			माप(netdev_features_strings));
	अन्यथा अगर (stringset == ETH_SS_RSS_HASH_FUNCS)
		स_नकल(data, rss_hash_func_strings,
		       माप(rss_hash_func_strings));
	अन्यथा अगर (stringset == ETH_SS_TUNABLES)
		स_नकल(data, tunable_strings, माप(tunable_strings));
	अन्यथा अगर (stringset == ETH_SS_PHY_TUNABLES)
		स_नकल(data, phy_tunable_strings, माप(phy_tunable_strings));
	अन्यथा अगर (stringset == ETH_SS_PHY_STATS && dev->phydev &&
		 !ops->get_ethtool_phy_stats && phy_ops &&
		 phy_ops->get_strings)
		phy_ops->get_strings(dev->phydev, data);
	अन्यथा अगर (stringset == ETH_SS_LINK_MODES)
		स_नकल(data, link_mode_names,
		       __ETHTOOL_LINK_MODE_MASK_NBITS * ETH_GSTRING_LEN);
	अन्यथा
		/* ops->get_strings is valid because checked earlier */
		ops->get_strings(dev, stringset, data);
पूर्ण

अटल netdev_features_t ethtool_get_feature_mask(u32 eth_cmd)
अणु
	/* feature masks of legacy discrete ethtool ops */

	चयन (eth_cmd) अणु
	हाल ETHTOOL_GTXCSUM:
	हाल ETHTOOL_STXCSUM:
		वापस NETIF_F_CSUM_MASK | NETIF_F_FCOE_CRC |
		       NETIF_F_SCTP_CRC;
	हाल ETHTOOL_GRXCSUM:
	हाल ETHTOOL_SRXCSUM:
		वापस NETIF_F_RXCSUM;
	हाल ETHTOOL_GSG:
	हाल ETHTOOL_SSG:
		वापस NETIF_F_SG | NETIF_F_FRAGLIST;
	हाल ETHTOOL_GTSO:
	हाल ETHTOOL_STSO:
		वापस NETIF_F_ALL_TSO;
	हाल ETHTOOL_GGSO:
	हाल ETHTOOL_SGSO:
		वापस NETIF_F_GSO;
	हाल ETHTOOL_GGRO:
	हाल ETHTOOL_SGRO:
		वापस NETIF_F_GRO;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक ethtool_get_one_feature(काष्ठा net_device *dev,
	अक्षर __user *useraddr, u32 ethcmd)
अणु
	netdev_features_t mask = ethtool_get_feature_mask(ethcmd);
	काष्ठा ethtool_value edata = अणु
		.cmd = ethcmd,
		.data = !!(dev->features & mask),
	पूर्ण;

	अगर (copy_to_user(useraddr, &edata, माप(edata)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_one_feature(काष्ठा net_device *dev,
	व्योम __user *useraddr, u32 ethcmd)
अणु
	काष्ठा ethtool_value edata;
	netdev_features_t mask;

	अगर (copy_from_user(&edata, useraddr, माप(edata)))
		वापस -EFAULT;

	mask = ethtool_get_feature_mask(ethcmd);
	mask &= dev->hw_features;
	अगर (!mask)
		वापस -EOPNOTSUPP;

	अगर (edata.data)
		dev->wanted_features |= mask;
	अन्यथा
		dev->wanted_features &= ~mask;

	__netdev_update_features(dev);

	वापस 0;
पूर्ण

#घोषणा ETH_ALL_FLAGS    (ETH_FLAG_LRO | ETH_FLAG_RXVLAN | ETH_FLAG_TXVLAN | \
			  ETH_FLAG_NTUPLE | ETH_FLAG_RXHASH)
#घोषणा ETH_ALL_FEATURES (NETIF_F_LRO | NETIF_F_HW_VLAN_CTAG_RX | \
			  NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_NTUPLE | \
			  NETIF_F_RXHASH)

अटल u32 __ethtool_get_flags(काष्ठा net_device *dev)
अणु
	u32 flags = 0;

	अगर (dev->features & NETIF_F_LRO)
		flags |= ETH_FLAG_LRO;
	अगर (dev->features & NETIF_F_HW_VLAN_CTAG_RX)
		flags |= ETH_FLAG_RXVLAN;
	अगर (dev->features & NETIF_F_HW_VLAN_CTAG_TX)
		flags |= ETH_FLAG_TXVLAN;
	अगर (dev->features & NETIF_F_NTUPLE)
		flags |= ETH_FLAG_NTUPLE;
	अगर (dev->features & NETIF_F_RXHASH)
		flags |= ETH_FLAG_RXHASH;

	वापस flags;
पूर्ण

अटल पूर्णांक __ethtool_set_flags(काष्ठा net_device *dev, u32 data)
अणु
	netdev_features_t features = 0, changed;

	अगर (data & ~ETH_ALL_FLAGS)
		वापस -EINVAL;

	अगर (data & ETH_FLAG_LRO)
		features |= NETIF_F_LRO;
	अगर (data & ETH_FLAG_RXVLAN)
		features |= NETIF_F_HW_VLAN_CTAG_RX;
	अगर (data & ETH_FLAG_TXVLAN)
		features |= NETIF_F_HW_VLAN_CTAG_TX;
	अगर (data & ETH_FLAG_NTUPLE)
		features |= NETIF_F_NTUPLE;
	अगर (data & ETH_FLAG_RXHASH)
		features |= NETIF_F_RXHASH;

	/* allow changing only bits set in hw_features */
	changed = (features ^ dev->features) & ETH_ALL_FEATURES;
	अगर (changed & ~dev->hw_features)
		वापस (changed & dev->hw_features) ? -EINVAL : -EOPNOTSUPP;

	dev->wanted_features =
		(dev->wanted_features & ~changed) | (features & changed);

	__netdev_update_features(dev);

	वापस 0;
पूर्ण

/* Given two link masks, AND them together and save the result in dst. */
व्योम ethtool_पूर्णांकersect_link_masks(काष्ठा ethtool_link_ksettings *dst,
				  काष्ठा ethtool_link_ksettings *src)
अणु
	अचिन्हित पूर्णांक size = BITS_TO_LONGS(__ETHTOOL_LINK_MODE_MASK_NBITS);
	अचिन्हित पूर्णांक idx = 0;

	क्रम (; idx < size; idx++) अणु
		dst->link_modes.supported[idx] &=
			src->link_modes.supported[idx];
		dst->link_modes.advertising[idx] &=
			src->link_modes.advertising[idx];
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ethtool_पूर्णांकersect_link_masks);

व्योम ethtool_convert_legacy_u32_to_link_mode(अचिन्हित दीर्घ *dst,
					     u32 legacy_u32)
अणु
	biपंचांगap_zero(dst, __ETHTOOL_LINK_MODE_MASK_NBITS);
	dst[0] = legacy_u32;
पूर्ण
EXPORT_SYMBOL(ethtool_convert_legacy_u32_to_link_mode);

/* वापस false अगर src had higher bits set. lower bits always updated. */
bool ethtool_convert_link_mode_to_legacy_u32(u32 *legacy_u32,
					     स्थिर अचिन्हित दीर्घ *src)
अणु
	bool retval = true;

	/* TODO: following test will soon always be true */
	अगर (__ETHTOOL_LINK_MODE_MASK_NBITS > 32) अणु
		__ETHTOOL_DECLARE_LINK_MODE_MASK(ext);

		biपंचांगap_zero(ext, __ETHTOOL_LINK_MODE_MASK_NBITS);
		biपंचांगap_fill(ext, 32);
		biपंचांगap_complement(ext, ext, __ETHTOOL_LINK_MODE_MASK_NBITS);
		अगर (biपंचांगap_पूर्णांकersects(ext, src,
				      __ETHTOOL_LINK_MODE_MASK_NBITS)) अणु
			/* src mask goes beyond bit 31 */
			retval = false;
		पूर्ण
	पूर्ण
	*legacy_u32 = src[0];
	वापस retval;
पूर्ण
EXPORT_SYMBOL(ethtool_convert_link_mode_to_legacy_u32);

/* वापस false अगर ksettings link modes had higher bits
 * set. legacy_settings always updated (best efक्रमt)
 */
अटल bool
convert_link_ksettings_to_legacy_settings(
	काष्ठा ethtool_cmd *legacy_settings,
	स्थिर काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	bool retval = true;

	स_रखो(legacy_settings, 0, माप(*legacy_settings));
	/* this also clears the deprecated fields in legacy काष्ठाure:
	 * __u8		transceiver;
	 * __u32	maxtxpkt;
	 * __u32	maxrxpkt;
	 */

	retval &= ethtool_convert_link_mode_to_legacy_u32(
		&legacy_settings->supported,
		link_ksettings->link_modes.supported);
	retval &= ethtool_convert_link_mode_to_legacy_u32(
		&legacy_settings->advertising,
		link_ksettings->link_modes.advertising);
	retval &= ethtool_convert_link_mode_to_legacy_u32(
		&legacy_settings->lp_advertising,
		link_ksettings->link_modes.lp_advertising);
	ethtool_cmd_speed_set(legacy_settings, link_ksettings->base.speed);
	legacy_settings->duplex
		= link_ksettings->base.duplex;
	legacy_settings->port
		= link_ksettings->base.port;
	legacy_settings->phy_address
		= link_ksettings->base.phy_address;
	legacy_settings->स्वतःneg
		= link_ksettings->base.स्वतःneg;
	legacy_settings->mdio_support
		= link_ksettings->base.mdio_support;
	legacy_settings->eth_tp_mdix
		= link_ksettings->base.eth_tp_mdix;
	legacy_settings->eth_tp_mdix_ctrl
		= link_ksettings->base.eth_tp_mdix_ctrl;
	legacy_settings->transceiver
		= link_ksettings->base.transceiver;
	वापस retval;
पूर्ण

/* number of 32-bit words to store the user's link mode biपंचांगaps */
#घोषणा __ETHTOOL_LINK_MODE_MASK_NU32			\
	DIV_ROUND_UP(__ETHTOOL_LINK_MODE_MASK_NBITS, 32)

/* layout of the काष्ठा passed from/to userland */
काष्ठा ethtool_link_usettings अणु
	काष्ठा ethtool_link_settings base;
	काष्ठा अणु
		__u32 supported[__ETHTOOL_LINK_MODE_MASK_NU32];
		__u32 advertising[__ETHTOOL_LINK_MODE_MASK_NU32];
		__u32 lp_advertising[__ETHTOOL_LINK_MODE_MASK_NU32];
	पूर्ण link_modes;
पूर्ण;

/* Internal kernel helper to query a device ethtool_link_settings. */
पूर्णांक __ethtool_get_link_ksettings(काष्ठा net_device *dev,
				 काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	ASSERT_RTNL();

	अगर (!dev->ethtool_ops->get_link_ksettings)
		वापस -EOPNOTSUPP;

	स_रखो(link_ksettings, 0, माप(*link_ksettings));
	वापस dev->ethtool_ops->get_link_ksettings(dev, link_ksettings);
पूर्ण
EXPORT_SYMBOL(__ethtool_get_link_ksettings);

/* convert ethtool_link_usettings in user space to a kernel पूर्णांकernal
 * ethtool_link_ksettings. वापस 0 on success, त्रुटि_सं on error.
 */
अटल पूर्णांक load_link_ksettings_from_user(काष्ठा ethtool_link_ksettings *to,
					 स्थिर व्योम __user *from)
अणु
	काष्ठा ethtool_link_usettings link_usettings;

	अगर (copy_from_user(&link_usettings, from, माप(link_usettings)))
		वापस -EFAULT;

	स_नकल(&to->base, &link_usettings.base, माप(to->base));
	biपंचांगap_from_arr32(to->link_modes.supported,
			  link_usettings.link_modes.supported,
			  __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_from_arr32(to->link_modes.advertising,
			  link_usettings.link_modes.advertising,
			  __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_from_arr32(to->link_modes.lp_advertising,
			  link_usettings.link_modes.lp_advertising,
			  __ETHTOOL_LINK_MODE_MASK_NBITS);

	वापस 0;
पूर्ण

/* Check अगर the user is trying to change anything besides speed/duplex */
bool ethtool_virtdev_validate_cmd(स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ethtool_link_settings base2 = अणुपूर्ण;

	base2.speed = cmd->base.speed;
	base2.port = PORT_OTHER;
	base2.duplex = cmd->base.duplex;
	base2.cmd = cmd->base.cmd;
	base2.link_mode_masks_nwords = cmd->base.link_mode_masks_nwords;

	वापस !स_भेद(&base2, &cmd->base, माप(base2)) &&
		biपंचांगap_empty(cmd->link_modes.supported,
			     __ETHTOOL_LINK_MODE_MASK_NBITS) &&
		biपंचांगap_empty(cmd->link_modes.lp_advertising,
			     __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

/* convert a kernel पूर्णांकernal ethtool_link_ksettings to
 * ethtool_link_usettings in user space. वापस 0 on success, त्रुटि_सं on
 * error.
 */
अटल पूर्णांक
store_link_ksettings_क्रम_user(व्योम __user *to,
			      स्थिर काष्ठा ethtool_link_ksettings *from)
अणु
	काष्ठा ethtool_link_usettings link_usettings;

	स_नकल(&link_usettings, from, माप(link_usettings));
	biपंचांगap_to_arr32(link_usettings.link_modes.supported,
			from->link_modes.supported,
			__ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_to_arr32(link_usettings.link_modes.advertising,
			from->link_modes.advertising,
			__ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_to_arr32(link_usettings.link_modes.lp_advertising,
			from->link_modes.lp_advertising,
			__ETHTOOL_LINK_MODE_MASK_NBITS);

	अगर (copy_to_user(to, &link_usettings, माप(link_usettings)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* Query device क्रम its ethtool_link_settings. */
अटल पूर्णांक ethtool_get_link_ksettings(काष्ठा net_device *dev,
				      व्योम __user *useraddr)
अणु
	पूर्णांक err = 0;
	काष्ठा ethtool_link_ksettings link_ksettings;

	ASSERT_RTNL();
	अगर (!dev->ethtool_ops->get_link_ksettings)
		वापस -EOPNOTSUPP;

	/* handle biपंचांगap nbits handshake */
	अगर (copy_from_user(&link_ksettings.base, useraddr,
			   माप(link_ksettings.base)))
		वापस -EFAULT;

	अगर (__ETHTOOL_LINK_MODE_MASK_NU32
	    != link_ksettings.base.link_mode_masks_nwords) अणु
		/* wrong link mode nbits requested */
		स_रखो(&link_ksettings, 0, माप(link_ksettings));
		link_ksettings.base.cmd = ETHTOOL_GLINKSETTINGS;
		/* send back number of words required as negative val */
		compileसमय_निश्चित(__ETHTOOL_LINK_MODE_MASK_NU32 <= S8_MAX,
				   "need too many bits for link modes!");
		link_ksettings.base.link_mode_masks_nwords
			= -((s8)__ETHTOOL_LINK_MODE_MASK_NU32);

		/* copy the base fields back to user, not the link
		 * mode biपंचांगaps
		 */
		अगर (copy_to_user(useraddr, &link_ksettings.base,
				 माप(link_ksettings.base)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	/* handshake successful: user/kernel agree on
	 * link_mode_masks_nwords
	 */

	स_रखो(&link_ksettings, 0, माप(link_ksettings));
	err = dev->ethtool_ops->get_link_ksettings(dev, &link_ksettings);
	अगर (err < 0)
		वापस err;

	/* make sure we tell the right values to user */
	link_ksettings.base.cmd = ETHTOOL_GLINKSETTINGS;
	link_ksettings.base.link_mode_masks_nwords
		= __ETHTOOL_LINK_MODE_MASK_NU32;
	link_ksettings.base.master_slave_cfg = MASTER_SLAVE_CFG_UNSUPPORTED;
	link_ksettings.base.master_slave_state = MASTER_SLAVE_STATE_UNSUPPORTED;

	वापस store_link_ksettings_क्रम_user(useraddr, &link_ksettings);
पूर्ण

/* Update device ethtool_link_settings. */
अटल पूर्णांक ethtool_set_link_ksettings(काष्ठा net_device *dev,
				      व्योम __user *useraddr)
अणु
	पूर्णांक err;
	काष्ठा ethtool_link_ksettings link_ksettings;

	ASSERT_RTNL();

	अगर (!dev->ethtool_ops->set_link_ksettings)
		वापस -EOPNOTSUPP;

	/* make sure nbits field has expected value */
	अगर (copy_from_user(&link_ksettings.base, useraddr,
			   माप(link_ksettings.base)))
		वापस -EFAULT;

	अगर (__ETHTOOL_LINK_MODE_MASK_NU32
	    != link_ksettings.base.link_mode_masks_nwords)
		वापस -EINVAL;

	/* copy the whole काष्ठाure, now that we know it has expected
	 * क्रमmat
	 */
	err = load_link_ksettings_from_user(&link_ksettings, useraddr);
	अगर (err)
		वापस err;

	/* re-check nwords field, just in हाल */
	अगर (__ETHTOOL_LINK_MODE_MASK_NU32
	    != link_ksettings.base.link_mode_masks_nwords)
		वापस -EINVAL;

	अगर (link_ksettings.base.master_slave_cfg ||
	    link_ksettings.base.master_slave_state)
		वापस -EINVAL;

	err = dev->ethtool_ops->set_link_ksettings(dev, &link_ksettings);
	अगर (err >= 0) अणु
		ethtool_notअगरy(dev, ETHTOOL_MSG_LINKINFO_NTF, शून्य);
		ethtool_notअगरy(dev, ETHTOOL_MSG_LINKMODES_NTF, शून्य);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक ethtool_virtdev_set_link_ksettings(काष्ठा net_device *dev,
				       स्थिर काष्ठा ethtool_link_ksettings *cmd,
				       u32 *dev_speed, u8 *dev_duplex)
अणु
	u32 speed;
	u8 duplex;

	speed = cmd->base.speed;
	duplex = cmd->base.duplex;
	/* करोn't allow custom speed and duplex */
	अगर (!ethtool_validate_speed(speed) ||
	    !ethtool_validate_duplex(duplex) ||
	    !ethtool_virtdev_validate_cmd(cmd))
		वापस -EINVAL;
	*dev_speed = speed;
	*dev_duplex = duplex;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ethtool_virtdev_set_link_ksettings);

/* Query device क्रम its ethtool_cmd settings.
 *
 * Backward compatibility note: क्रम compatibility with legacy ethtool, this is
 * now implemented via get_link_ksettings. When driver reports higher link mode
 * bits, a kernel warning is logged once (with name of 1st driver/device) to
 * recommend user to upgrade ethtool, but the command is successful (only the
 * lower link mode bits reported back to user). Deprecated fields from
 * ethtool_cmd (transceiver/maxrxpkt/maxtxpkt) are always set to zero.
 */
अटल पूर्णांक ethtool_get_settings(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_link_ksettings link_ksettings;
	काष्ठा ethtool_cmd cmd;
	पूर्णांक err;

	ASSERT_RTNL();
	अगर (!dev->ethtool_ops->get_link_ksettings)
		वापस -EOPNOTSUPP;

	स_रखो(&link_ksettings, 0, माप(link_ksettings));
	err = dev->ethtool_ops->get_link_ksettings(dev, &link_ksettings);
	अगर (err < 0)
		वापस err;
	convert_link_ksettings_to_legacy_settings(&cmd, &link_ksettings);

	/* send a sensible cmd tag back to user */
	cmd.cmd = ETHTOOL_GSET;

	अगर (copy_to_user(useraddr, &cmd, माप(cmd)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* Update device link settings with given ethtool_cmd.
 *
 * Backward compatibility note: क्रम compatibility with legacy ethtool, this is
 * now always implemented via set_link_settings. When user's request updates
 * deprecated ethtool_cmd fields (transceiver/maxrxpkt/maxtxpkt), a kernel
 * warning is logged once (with name of 1st driver/device) to recommend user to
 * upgrade ethtool, and the request is rejected.
 */
अटल पूर्णांक ethtool_set_settings(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_link_ksettings link_ksettings;
	काष्ठा ethtool_cmd cmd;
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (copy_from_user(&cmd, useraddr, माप(cmd)))
		वापस -EFAULT;
	अगर (!dev->ethtool_ops->set_link_ksettings)
		वापस -EOPNOTSUPP;

	अगर (!convert_legacy_settings_to_link_ksettings(&link_ksettings, &cmd))
		वापस -EINVAL;
	link_ksettings.base.link_mode_masks_nwords =
		__ETHTOOL_LINK_MODE_MASK_NU32;
	ret = dev->ethtool_ops->set_link_ksettings(dev, &link_ksettings);
	अगर (ret >= 0) अणु
		ethtool_notअगरy(dev, ETHTOOL_MSG_LINKINFO_NTF, शून्य);
		ethtool_notअगरy(dev, ETHTOOL_MSG_LINKMODES_NTF, शून्य);
	पूर्ण
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_get_drvinfo(काष्ठा net_device *dev,
						  व्योम __user *useraddr)
अणु
	काष्ठा ethtool_drvinfo info;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;

	स_रखो(&info, 0, माप(info));
	info.cmd = ETHTOOL_GDRVINFO;
	strlcpy(info.version, UTS_RELEASE, माप(info.version));
	अगर (ops->get_drvinfo) अणु
		ops->get_drvinfo(dev, &info);
	पूर्ण अन्यथा अगर (dev->dev.parent && dev->dev.parent->driver) अणु
		strlcpy(info.bus_info, dev_name(dev->dev.parent),
			माप(info.bus_info));
		strlcpy(info.driver, dev->dev.parent->driver->name,
			माप(info.driver));
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * this method of obtaining string set info is deprecated;
	 * Use ETHTOOL_GSSET_INFO instead.
	 */
	अगर (ops->get_sset_count) अणु
		पूर्णांक rc;

		rc = ops->get_sset_count(dev, ETH_SS_TEST);
		अगर (rc >= 0)
			info.testinfo_len = rc;
		rc = ops->get_sset_count(dev, ETH_SS_STATS);
		अगर (rc >= 0)
			info.n_stats = rc;
		rc = ops->get_sset_count(dev, ETH_SS_PRIV_FLAGS);
		अगर (rc >= 0)
			info.n_priv_flags = rc;
	पूर्ण
	अगर (ops->get_regs_len) अणु
		पूर्णांक ret = ops->get_regs_len(dev);

		अगर (ret > 0)
			info.regdump_len = ret;
	पूर्ण

	अगर (ops->get_eeprom_len)
		info.eedump_len = ops->get_eeprom_len(dev);

	अगर (!info.fw_version[0])
		devlink_compat_running_version(dev, info.fw_version,
					       माप(info.fw_version));

	अगर (copy_to_user(useraddr, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_get_sset_info(काष्ठा net_device *dev,
						    व्योम __user *useraddr)
अणु
	काष्ठा ethtool_sset_info info;
	u64 sset_mask;
	पूर्णांक i, idx = 0, n_bits = 0, ret, rc;
	u32 *info_buf = शून्य;

	अगर (copy_from_user(&info, useraddr, माप(info)))
		वापस -EFAULT;

	/* store copy of mask, because we zero काष्ठा later on */
	sset_mask = info.sset_mask;
	अगर (!sset_mask)
		वापस 0;

	/* calculate size of वापस buffer */
	n_bits = hweight64(sset_mask);

	स_रखो(&info, 0, माप(info));
	info.cmd = ETHTOOL_GSSET_INFO;

	info_buf = kसुस्मृति(n_bits, माप(u32), GFP_USER);
	अगर (!info_buf)
		वापस -ENOMEM;

	/*
	 * fill वापस buffer based on input biपंचांगask and successful
	 * get_sset_count वापस
	 */
	क्रम (i = 0; i < 64; i++) अणु
		अगर (!(sset_mask & (1ULL << i)))
			जारी;

		rc = __ethtool_get_sset_count(dev, i);
		अगर (rc >= 0) अणु
			info.sset_mask |= (1ULL << i);
			info_buf[idx++] = rc;
		पूर्ण
	पूर्ण

	ret = -EFAULT;
	अगर (copy_to_user(useraddr, &info, माप(info)))
		जाओ out;

	useraddr += दुरत्व(काष्ठा ethtool_sset_info, data);
	अगर (copy_to_user(useraddr, info_buf, idx * माप(u32)))
		जाओ out;

	ret = 0;

out:
	kमुक्त(info_buf);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_set_rxnfc(काष्ठा net_device *dev,
						u32 cmd, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_rxnfc info;
	माप_प्रकार info_size = माप(info);
	पूर्णांक rc;

	अगर (!dev->ethtool_ops->set_rxnfc)
		वापस -EOPNOTSUPP;

	/* काष्ठा ethtool_rxnfc was originally defined क्रम
	 * ETHTOOL_अणुG,Sपूर्णRXFH with only the cmd, flow_type and data
	 * members.  User-space might still be using that
	 * definition. */
	अगर (cmd == ETHTOOL_SRXFH)
		info_size = (दुरत्व(काष्ठा ethtool_rxnfc, data) +
			     माप(info.data));

	अगर (copy_from_user(&info, useraddr, info_size))
		वापस -EFAULT;

	rc = dev->ethtool_ops->set_rxnfc(dev, &info);
	अगर (rc)
		वापस rc;

	अगर (cmd == ETHTOOL_SRXCLSRLINS &&
	    copy_to_user(useraddr, &info, info_size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_get_rxnfc(काष्ठा net_device *dev,
						u32 cmd, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_rxnfc info;
	माप_प्रकार info_size = माप(info);
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	पूर्णांक ret;
	व्योम *rule_buf = शून्य;

	अगर (!ops->get_rxnfc)
		वापस -EOPNOTSUPP;

	/* काष्ठा ethtool_rxnfc was originally defined क्रम
	 * ETHTOOL_अणुG,Sपूर्णRXFH with only the cmd, flow_type and data
	 * members.  User-space might still be using that
	 * definition. */
	अगर (cmd == ETHTOOL_GRXFH)
		info_size = (दुरत्व(काष्ठा ethtool_rxnfc, data) +
			     माप(info.data));

	अगर (copy_from_user(&info, useraddr, info_size))
		वापस -EFAULT;

	/* If FLOW_RSS was requested then user-space must be using the
	 * new definition, as FLOW_RSS is newer.
	 */
	अगर (cmd == ETHTOOL_GRXFH && info.flow_type & FLOW_RSS) अणु
		info_size = माप(info);
		अगर (copy_from_user(&info, useraddr, info_size))
			वापस -EFAULT;
		/* Since malicious users may modअगरy the original data,
		 * we need to check whether FLOW_RSS is still requested.
		 */
		अगर (!(info.flow_type & FLOW_RSS))
			वापस -EINVAL;
	पूर्ण

	अगर (info.cmd != cmd)
		वापस -EINVAL;

	अगर (info.cmd == ETHTOOL_GRXCLSRLALL) अणु
		अगर (info.rule_cnt > 0) अणु
			अगर (info.rule_cnt <= KMALLOC_MAX_SIZE / माप(u32))
				rule_buf = kसुस्मृति(info.rule_cnt, माप(u32),
						   GFP_USER);
			अगर (!rule_buf)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण

	ret = ops->get_rxnfc(dev, &info, rule_buf);
	अगर (ret < 0)
		जाओ err_out;

	ret = -EFAULT;
	अगर (copy_to_user(useraddr, &info, info_size))
		जाओ err_out;

	अगर (rule_buf) अणु
		useraddr += दुरत्व(काष्ठा ethtool_rxnfc, rule_locs);
		अगर (copy_to_user(useraddr, rule_buf,
				 info.rule_cnt * माप(u32)))
			जाओ err_out;
	पूर्ण
	ret = 0;

err_out:
	kमुक्त(rule_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_copy_validate_indir(u32 *indir, व्योम __user *useraddr,
					काष्ठा ethtool_rxnfc *rx_rings,
					u32 size)
अणु
	पूर्णांक i;

	अगर (copy_from_user(indir, useraddr, size * माप(indir[0])))
		वापस -EFAULT;

	/* Validate ring indices */
	क्रम (i = 0; i < size; i++)
		अगर (indir[i] >= rx_rings->data)
			वापस -EINVAL;

	वापस 0;
पूर्ण

u8 netdev_rss_key[NETDEV_RSS_KEY_LEN] __पढ़ो_mostly;

व्योम netdev_rss_key_fill(व्योम *buffer, माप_प्रकार len)
अणु
	BUG_ON(len > माप(netdev_rss_key));
	net_get_अक्रमom_once(netdev_rss_key, माप(netdev_rss_key));
	स_नकल(buffer, netdev_rss_key, len);
पूर्ण
EXPORT_SYMBOL(netdev_rss_key_fill);

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_get_rxfh_indir(काष्ठा net_device *dev,
						     व्योम __user *useraddr)
अणु
	u32 user_size, dev_size;
	u32 *indir;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_rxfh_indir_size ||
	    !dev->ethtool_ops->get_rxfh)
		वापस -EOPNOTSUPP;
	dev_size = dev->ethtool_ops->get_rxfh_indir_size(dev);
	अगर (dev_size == 0)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&user_size,
			   useraddr + दुरत्व(काष्ठा ethtool_rxfh_indir, size),
			   माप(user_size)))
		वापस -EFAULT;

	अगर (copy_to_user(useraddr + दुरत्व(काष्ठा ethtool_rxfh_indir, size),
			 &dev_size, माप(dev_size)))
		वापस -EFAULT;

	/* If the user buffer size is 0, this is just a query क्रम the
	 * device table size.  Otherwise, अगर it's smaller than the
	 * device table size it's an error.
	 */
	अगर (user_size < dev_size)
		वापस user_size == 0 ? 0 : -EINVAL;

	indir = kसुस्मृति(dev_size, माप(indir[0]), GFP_USER);
	अगर (!indir)
		वापस -ENOMEM;

	ret = dev->ethtool_ops->get_rxfh(dev, indir, शून्य, शून्य);
	अगर (ret)
		जाओ out;

	अगर (copy_to_user(useraddr +
			 दुरत्व(काष्ठा ethtool_rxfh_indir, ring_index[0]),
			 indir, dev_size * माप(indir[0])))
		ret = -EFAULT;

out:
	kमुक्त(indir);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_set_rxfh_indir(काष्ठा net_device *dev,
						     व्योम __user *useraddr)
अणु
	काष्ठा ethtool_rxnfc rx_rings;
	u32 user_size, dev_size, i;
	u32 *indir;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	पूर्णांक ret;
	u32 ringidx_offset = दुरत्व(काष्ठा ethtool_rxfh_indir, ring_index[0]);

	अगर (!ops->get_rxfh_indir_size || !ops->set_rxfh ||
	    !ops->get_rxnfc)
		वापस -EOPNOTSUPP;

	dev_size = ops->get_rxfh_indir_size(dev);
	अगर (dev_size == 0)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&user_size,
			   useraddr + दुरत्व(काष्ठा ethtool_rxfh_indir, size),
			   माप(user_size)))
		वापस -EFAULT;

	अगर (user_size != 0 && user_size != dev_size)
		वापस -EINVAL;

	indir = kसुस्मृति(dev_size, माप(indir[0]), GFP_USER);
	अगर (!indir)
		वापस -ENOMEM;

	rx_rings.cmd = ETHTOOL_GRXRINGS;
	ret = ops->get_rxnfc(dev, &rx_rings, शून्य);
	अगर (ret)
		जाओ out;

	अगर (user_size == 0) अणु
		क्रम (i = 0; i < dev_size; i++)
			indir[i] = ethtool_rxfh_indir_शेष(i, rx_rings.data);
	पूर्ण अन्यथा अणु
		ret = ethtool_copy_validate_indir(indir,
						  useraddr + ringidx_offset,
						  &rx_rings,
						  dev_size);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = ops->set_rxfh(dev, indir, शून्य, ETH_RSS_HASH_NO_CHANGE);
	अगर (ret)
		जाओ out;

	/* indicate whether rxfh was set to शेष */
	अगर (user_size == 0)
		dev->priv_flags &= ~IFF_RXFH_CONFIGURED;
	अन्यथा
		dev->priv_flags |= IFF_RXFH_CONFIGURED;

out:
	kमुक्त(indir);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_get_rxfh(काष्ठा net_device *dev,
					       व्योम __user *useraddr)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	u32 user_indir_size, user_key_size;
	u32 dev_indir_size = 0, dev_key_size = 0;
	काष्ठा ethtool_rxfh rxfh;
	u32 total_size;
	u32 indir_bytes;
	u32 *indir = शून्य;
	u8 dev_hfunc = 0;
	u8 *hkey = शून्य;
	u8 *rss_config;

	अगर (!ops->get_rxfh)
		वापस -EOPNOTSUPP;

	अगर (ops->get_rxfh_indir_size)
		dev_indir_size = ops->get_rxfh_indir_size(dev);
	अगर (ops->get_rxfh_key_size)
		dev_key_size = ops->get_rxfh_key_size(dev);

	अगर (copy_from_user(&rxfh, useraddr, माप(rxfh)))
		वापस -EFAULT;
	user_indir_size = rxfh.indir_size;
	user_key_size = rxfh.key_size;

	/* Check that reserved fields are 0 क्रम now */
	अगर (rxfh.rsvd8[0] || rxfh.rsvd8[1] || rxfh.rsvd8[2] || rxfh.rsvd32)
		वापस -EINVAL;
	/* Most drivers करोn't handle rss_context, check it's 0 as well */
	अगर (rxfh.rss_context && !ops->get_rxfh_context)
		वापस -EOPNOTSUPP;

	rxfh.indir_size = dev_indir_size;
	rxfh.key_size = dev_key_size;
	अगर (copy_to_user(useraddr, &rxfh, माप(rxfh)))
		वापस -EFAULT;

	अगर ((user_indir_size && (user_indir_size != dev_indir_size)) ||
	    (user_key_size && (user_key_size != dev_key_size)))
		वापस -EINVAL;

	indir_bytes = user_indir_size * माप(indir[0]);
	total_size = indir_bytes + user_key_size;
	rss_config = kzalloc(total_size, GFP_USER);
	अगर (!rss_config)
		वापस -ENOMEM;

	अगर (user_indir_size)
		indir = (u32 *)rss_config;

	अगर (user_key_size)
		hkey = rss_config + indir_bytes;

	अगर (rxfh.rss_context)
		ret = dev->ethtool_ops->get_rxfh_context(dev, indir, hkey,
							 &dev_hfunc,
							 rxfh.rss_context);
	अन्यथा
		ret = dev->ethtool_ops->get_rxfh(dev, indir, hkey, &dev_hfunc);
	अगर (ret)
		जाओ out;

	अगर (copy_to_user(useraddr + दुरत्व(काष्ठा ethtool_rxfh, hfunc),
			 &dev_hfunc, माप(rxfh.hfunc))) अणु
		ret = -EFAULT;
	पूर्ण अन्यथा अगर (copy_to_user(useraddr +
			      दुरत्व(काष्ठा ethtool_rxfh, rss_config[0]),
			      rss_config, total_size)) अणु
		ret = -EFAULT;
	पूर्ण
out:
	kमुक्त(rss_config);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_set_rxfh(काष्ठा net_device *dev,
					       व्योम __user *useraddr)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	काष्ठा ethtool_rxnfc rx_rings;
	काष्ठा ethtool_rxfh rxfh;
	u32 dev_indir_size = 0, dev_key_size = 0, i;
	u32 *indir = शून्य, indir_bytes = 0;
	u8 *hkey = शून्य;
	u8 *rss_config;
	u32 rss_cfg_offset = दुरत्व(काष्ठा ethtool_rxfh, rss_config[0]);
	bool delete = false;

	अगर (!ops->get_rxnfc || !ops->set_rxfh)
		वापस -EOPNOTSUPP;

	अगर (ops->get_rxfh_indir_size)
		dev_indir_size = ops->get_rxfh_indir_size(dev);
	अगर (ops->get_rxfh_key_size)
		dev_key_size = ops->get_rxfh_key_size(dev);

	अगर (copy_from_user(&rxfh, useraddr, माप(rxfh)))
		वापस -EFAULT;

	/* Check that reserved fields are 0 क्रम now */
	अगर (rxfh.rsvd8[0] || rxfh.rsvd8[1] || rxfh.rsvd8[2] || rxfh.rsvd32)
		वापस -EINVAL;
	/* Most drivers करोn't handle rss_context, check it's 0 as well */
	अगर (rxfh.rss_context && !ops->set_rxfh_context)
		वापस -EOPNOTSUPP;

	/* If either indir, hash key or function is valid, proceed further.
	 * Must request at least one change: indir size, hash key or function.
	 */
	अगर ((rxfh.indir_size &&
	     rxfh.indir_size != ETH_RXFH_INसूची_NO_CHANGE &&
	     rxfh.indir_size != dev_indir_size) ||
	    (rxfh.key_size && (rxfh.key_size != dev_key_size)) ||
	    (rxfh.indir_size == ETH_RXFH_INसूची_NO_CHANGE &&
	     rxfh.key_size == 0 && rxfh.hfunc == ETH_RSS_HASH_NO_CHANGE))
		वापस -EINVAL;

	अगर (rxfh.indir_size != ETH_RXFH_INसूची_NO_CHANGE)
		indir_bytes = dev_indir_size * माप(indir[0]);

	rss_config = kzalloc(indir_bytes + rxfh.key_size, GFP_USER);
	अगर (!rss_config)
		वापस -ENOMEM;

	rx_rings.cmd = ETHTOOL_GRXRINGS;
	ret = ops->get_rxnfc(dev, &rx_rings, शून्य);
	अगर (ret)
		जाओ out;

	/* rxfh.indir_size == 0 means reset the indir table to शेष (master
	 * context) or delete the context (other RSS contexts).
	 * rxfh.indir_size == ETH_RXFH_INसूची_NO_CHANGE means leave it unchanged.
	 */
	अगर (rxfh.indir_size &&
	    rxfh.indir_size != ETH_RXFH_INसूची_NO_CHANGE) अणु
		indir = (u32 *)rss_config;
		ret = ethtool_copy_validate_indir(indir,
						  useraddr + rss_cfg_offset,
						  &rx_rings,
						  rxfh.indir_size);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अगर (rxfh.indir_size == 0) अणु
		अगर (rxfh.rss_context == 0) अणु
			indir = (u32 *)rss_config;
			क्रम (i = 0; i < dev_indir_size; i++)
				indir[i] = ethtool_rxfh_indir_शेष(i, rx_rings.data);
		पूर्ण अन्यथा अणु
			delete = true;
		पूर्ण
	पूर्ण

	अगर (rxfh.key_size) अणु
		hkey = rss_config + indir_bytes;
		अगर (copy_from_user(hkey,
				   useraddr + rss_cfg_offset + indir_bytes,
				   rxfh.key_size)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (rxfh.rss_context)
		ret = ops->set_rxfh_context(dev, indir, hkey, rxfh.hfunc,
					    &rxfh.rss_context, delete);
	अन्यथा
		ret = ops->set_rxfh(dev, indir, hkey, rxfh.hfunc);
	अगर (ret)
		जाओ out;

	अगर (copy_to_user(useraddr + दुरत्व(काष्ठा ethtool_rxfh, rss_context),
			 &rxfh.rss_context, माप(rxfh.rss_context)))
		ret = -EFAULT;

	अगर (!rxfh.rss_context) अणु
		/* indicate whether rxfh was set to शेष */
		अगर (rxfh.indir_size == 0)
			dev->priv_flags &= ~IFF_RXFH_CONFIGURED;
		अन्यथा अगर (rxfh.indir_size != ETH_RXFH_INसूची_NO_CHANGE)
			dev->priv_flags |= IFF_RXFH_CONFIGURED;
	पूर्ण

out:
	kमुक्त(rss_config);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_regs(काष्ठा net_device *dev, अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_regs regs;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	व्योम *regbuf;
	पूर्णांक reglen, ret;

	अगर (!ops->get_regs || !ops->get_regs_len)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&regs, useraddr, माप(regs)))
		वापस -EFAULT;

	reglen = ops->get_regs_len(dev);
	अगर (reglen <= 0)
		वापस reglen;

	अगर (regs.len > reglen)
		regs.len = reglen;

	regbuf = vzalloc(reglen);
	अगर (!regbuf)
		वापस -ENOMEM;

	अगर (regs.len < reglen)
		reglen = regs.len;

	ops->get_regs(dev, &regs, regbuf);

	ret = -EFAULT;
	अगर (copy_to_user(useraddr, &regs, माप(regs)))
		जाओ out;
	useraddr += दुरत्व(काष्ठा ethtool_regs, data);
	अगर (copy_to_user(useraddr, regbuf, reglen))
		जाओ out;
	ret = 0;

 out:
	vमुक्त(regbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_reset(काष्ठा net_device *dev, अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_value reset;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->reset)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&reset, useraddr, माप(reset)))
		वापस -EFAULT;

	ret = dev->ethtool_ops->reset(dev, &reset.data);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(useraddr, &reset, माप(reset)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_get_wol(काष्ठा net_device *dev, अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_wolinfo wol;

	अगर (!dev->ethtool_ops->get_wol)
		वापस -EOPNOTSUPP;

	स_रखो(&wol, 0, माप(काष्ठा ethtool_wolinfo));
	wol.cmd = ETHTOOL_GWOL;
	dev->ethtool_ops->get_wol(dev, &wol);

	अगर (copy_to_user(useraddr, &wol, माप(wol)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_wol(काष्ठा net_device *dev, अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_wolinfo wol;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->set_wol)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&wol, useraddr, माप(wol)))
		वापस -EFAULT;

	ret = dev->ethtool_ops->set_wol(dev, &wol);
	अगर (ret)
		वापस ret;

	dev->wol_enabled = !!wol.wolopts;
	ethtool_notअगरy(dev, ETHTOOL_MSG_WOL_NTF, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_get_eee(काष्ठा net_device *dev, अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_eee edata;
	पूर्णांक rc;

	अगर (!dev->ethtool_ops->get_eee)
		वापस -EOPNOTSUPP;

	स_रखो(&edata, 0, माप(काष्ठा ethtool_eee));
	edata.cmd = ETHTOOL_GEEE;
	rc = dev->ethtool_ops->get_eee(dev, &edata);

	अगर (rc)
		वापस rc;

	अगर (copy_to_user(useraddr, &edata, माप(edata)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_eee(काष्ठा net_device *dev, अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_eee edata;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->set_eee)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&edata, useraddr, माप(edata)))
		वापस -EFAULT;

	ret = dev->ethtool_ops->set_eee(dev, &edata);
	अगर (!ret)
		ethtool_notअगरy(dev, ETHTOOL_MSG_EEE_NTF, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_nway_reset(काष्ठा net_device *dev)
अणु
	अगर (!dev->ethtool_ops->nway_reset)
		वापस -EOPNOTSUPP;

	वापस dev->ethtool_ops->nway_reset(dev);
पूर्ण

अटल पूर्णांक ethtool_get_link(काष्ठा net_device *dev, अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_value edata = अणु .cmd = ETHTOOL_GLINK पूर्ण;
	पूर्णांक link = __ethtool_get_link(dev);

	अगर (link < 0)
		वापस link;

	edata.data = link;
	अगर (copy_to_user(useraddr, &edata, माप(edata)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_get_any_eeprom(काष्ठा net_device *dev, व्योम __user *useraddr,
				  पूर्णांक (*getter)(काष्ठा net_device *,
						काष्ठा ethtool_eeprom *, u8 *),
				  u32 total_len)
अणु
	काष्ठा ethtool_eeprom eeprom;
	व्योम __user *userbuf = useraddr + माप(eeprom);
	u32 bytes_reमुख्यing;
	u8 *data;
	पूर्णांक ret = 0;

	अगर (copy_from_user(&eeprom, useraddr, माप(eeprom)))
		वापस -EFAULT;

	/* Check क्रम wrap and zero */
	अगर (eeprom.offset + eeprom.len <= eeprom.offset)
		वापस -EINVAL;

	/* Check क्रम exceeding total eeprom len */
	अगर (eeprom.offset + eeprom.len > total_len)
		वापस -EINVAL;

	data = kzalloc(PAGE_SIZE, GFP_USER);
	अगर (!data)
		वापस -ENOMEM;

	bytes_reमुख्यing = eeprom.len;
	जबतक (bytes_reमुख्यing > 0) अणु
		eeprom.len = min(bytes_reमुख्यing, (u32)PAGE_SIZE);

		ret = getter(dev, &eeprom, data);
		अगर (ret)
			अवरोध;
		अगर (copy_to_user(userbuf, data, eeprom.len)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		userbuf += eeprom.len;
		eeprom.offset += eeprom.len;
		bytes_reमुख्यing -= eeprom.len;
	पूर्ण

	eeprom.len = userbuf - (useraddr + माप(eeprom));
	eeprom.offset -= eeprom.len;
	अगर (copy_to_user(useraddr, &eeprom, माप(eeprom)))
		ret = -EFAULT;

	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_eeprom(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;

	अगर (!ops->get_eeprom || !ops->get_eeprom_len ||
	    !ops->get_eeprom_len(dev))
		वापस -EOPNOTSUPP;

	वापस ethtool_get_any_eeprom(dev, useraddr, ops->get_eeprom,
				      ops->get_eeprom_len(dev));
पूर्ण

अटल पूर्णांक ethtool_set_eeprom(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_eeprom eeprom;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	व्योम __user *userbuf = useraddr + माप(eeprom);
	u32 bytes_reमुख्यing;
	u8 *data;
	पूर्णांक ret = 0;

	अगर (!ops->set_eeprom || !ops->get_eeprom_len ||
	    !ops->get_eeprom_len(dev))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&eeprom, useraddr, माप(eeprom)))
		वापस -EFAULT;

	/* Check क्रम wrap and zero */
	अगर (eeprom.offset + eeprom.len <= eeprom.offset)
		वापस -EINVAL;

	/* Check क्रम exceeding total eeprom len */
	अगर (eeprom.offset + eeprom.len > ops->get_eeprom_len(dev))
		वापस -EINVAL;

	data = kzalloc(PAGE_SIZE, GFP_USER);
	अगर (!data)
		वापस -ENOMEM;

	bytes_reमुख्यing = eeprom.len;
	जबतक (bytes_reमुख्यing > 0) अणु
		eeprom.len = min(bytes_reमुख्यing, (u32)PAGE_SIZE);

		अगर (copy_from_user(data, userbuf, eeprom.len)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ret = ops->set_eeprom(dev, &eeprom, data);
		अगर (ret)
			अवरोध;
		userbuf += eeprom.len;
		eeprom.offset += eeprom.len;
		bytes_reमुख्यing -= eeprom.len;
	पूर्ण

	kमुक्त(data);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_get_coalesce(काष्ठा net_device *dev,
						   व्योम __user *useraddr)
अणु
	काष्ठा ethtool_coalesce coalesce = अणु .cmd = ETHTOOL_GCOALESCE पूर्ण;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_coalesce)
		वापस -EOPNOTSUPP;

	ret = dev->ethtool_ops->get_coalesce(dev, &coalesce);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(useraddr, &coalesce, माप(coalesce)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल bool
ethtool_set_coalesce_supported(काष्ठा net_device *dev,
			       काष्ठा ethtool_coalesce *coalesce)
अणु
	u32 supported_params = dev->ethtool_ops->supported_coalesce_params;
	u32 nonzero_params = 0;

	अगर (coalesce->rx_coalesce_usecs)
		nonzero_params |= ETHTOOL_COALESCE_RX_USECS;
	अगर (coalesce->rx_max_coalesced_frames)
		nonzero_params |= ETHTOOL_COALESCE_RX_MAX_FRAMES;
	अगर (coalesce->rx_coalesce_usecs_irq)
		nonzero_params |= ETHTOOL_COALESCE_RX_USECS_IRQ;
	अगर (coalesce->rx_max_coalesced_frames_irq)
		nonzero_params |= ETHTOOL_COALESCE_RX_MAX_FRAMES_IRQ;
	अगर (coalesce->tx_coalesce_usecs)
		nonzero_params |= ETHTOOL_COALESCE_TX_USECS;
	अगर (coalesce->tx_max_coalesced_frames)
		nonzero_params |= ETHTOOL_COALESCE_TX_MAX_FRAMES;
	अगर (coalesce->tx_coalesce_usecs_irq)
		nonzero_params |= ETHTOOL_COALESCE_TX_USECS_IRQ;
	अगर (coalesce->tx_max_coalesced_frames_irq)
		nonzero_params |= ETHTOOL_COALESCE_TX_MAX_FRAMES_IRQ;
	अगर (coalesce->stats_block_coalesce_usecs)
		nonzero_params |= ETHTOOL_COALESCE_STATS_BLOCK_USECS;
	अगर (coalesce->use_adaptive_rx_coalesce)
		nonzero_params |= ETHTOOL_COALESCE_USE_ADAPTIVE_RX;
	अगर (coalesce->use_adaptive_tx_coalesce)
		nonzero_params |= ETHTOOL_COALESCE_USE_ADAPTIVE_TX;
	अगर (coalesce->pkt_rate_low)
		nonzero_params |= ETHTOOL_COALESCE_PKT_RATE_LOW;
	अगर (coalesce->rx_coalesce_usecs_low)
		nonzero_params |= ETHTOOL_COALESCE_RX_USECS_LOW;
	अगर (coalesce->rx_max_coalesced_frames_low)
		nonzero_params |= ETHTOOL_COALESCE_RX_MAX_FRAMES_LOW;
	अगर (coalesce->tx_coalesce_usecs_low)
		nonzero_params |= ETHTOOL_COALESCE_TX_USECS_LOW;
	अगर (coalesce->tx_max_coalesced_frames_low)
		nonzero_params |= ETHTOOL_COALESCE_TX_MAX_FRAMES_LOW;
	अगर (coalesce->pkt_rate_high)
		nonzero_params |= ETHTOOL_COALESCE_PKT_RATE_HIGH;
	अगर (coalesce->rx_coalesce_usecs_high)
		nonzero_params |= ETHTOOL_COALESCE_RX_USECS_HIGH;
	अगर (coalesce->rx_max_coalesced_frames_high)
		nonzero_params |= ETHTOOL_COALESCE_RX_MAX_FRAMES_HIGH;
	अगर (coalesce->tx_coalesce_usecs_high)
		nonzero_params |= ETHTOOL_COALESCE_TX_USECS_HIGH;
	अगर (coalesce->tx_max_coalesced_frames_high)
		nonzero_params |= ETHTOOL_COALESCE_TX_MAX_FRAMES_HIGH;
	अगर (coalesce->rate_sample_पूर्णांकerval)
		nonzero_params |= ETHTOOL_COALESCE_RATE_SAMPLE_INTERVAL;

	वापस (supported_params & nonzero_params) == nonzero_params;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_set_coalesce(काष्ठा net_device *dev,
						   व्योम __user *useraddr)
अणु
	काष्ठा ethtool_coalesce coalesce;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->set_coalesce)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&coalesce, useraddr, माप(coalesce)))
		वापस -EFAULT;

	अगर (!ethtool_set_coalesce_supported(dev, &coalesce))
		वापस -EOPNOTSUPP;

	ret = dev->ethtool_ops->set_coalesce(dev, &coalesce);
	अगर (!ret)
		ethtool_notअगरy(dev, ETHTOOL_MSG_COALESCE_NTF, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_ringparam(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_ringparam ringparam = अणु .cmd = ETHTOOL_GRINGPARAM पूर्ण;

	अगर (!dev->ethtool_ops->get_ringparam)
		वापस -EOPNOTSUPP;

	dev->ethtool_ops->get_ringparam(dev, &ringparam);

	अगर (copy_to_user(useraddr, &ringparam, माप(ringparam)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_ringparam(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_ringparam ringparam, max = अणु .cmd = ETHTOOL_GRINGPARAM पूर्ण;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->set_ringparam || !dev->ethtool_ops->get_ringparam)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&ringparam, useraddr, माप(ringparam)))
		वापस -EFAULT;

	dev->ethtool_ops->get_ringparam(dev, &max);

	/* ensure new ring parameters are within the maximums */
	अगर (ringparam.rx_pending > max.rx_max_pending ||
	    ringparam.rx_mini_pending > max.rx_mini_max_pending ||
	    ringparam.rx_jumbo_pending > max.rx_jumbo_max_pending ||
	    ringparam.tx_pending > max.tx_max_pending)
		वापस -EINVAL;

	ret = dev->ethtool_ops->set_ringparam(dev, &ringparam);
	अगर (!ret)
		ethtool_notअगरy(dev, ETHTOOL_MSG_RINGS_NTF, शून्य);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_get_channels(काष्ठा net_device *dev,
						   व्योम __user *useraddr)
अणु
	काष्ठा ethtool_channels channels = अणु .cmd = ETHTOOL_GCHANNELS पूर्ण;

	अगर (!dev->ethtool_ops->get_channels)
		वापस -EOPNOTSUPP;

	dev->ethtool_ops->get_channels(dev, &channels);

	अगर (copy_to_user(useraddr, &channels, माप(channels)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_set_channels(काष्ठा net_device *dev,
						   व्योम __user *useraddr)
अणु
	काष्ठा ethtool_channels channels, curr = अणु .cmd = ETHTOOL_GCHANNELS पूर्ण;
	u16 from_channel, to_channel;
	u32 max_rx_in_use = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->set_channels || !dev->ethtool_ops->get_channels)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&channels, useraddr, माप(channels)))
		वापस -EFAULT;

	dev->ethtool_ops->get_channels(dev, &curr);

	अगर (channels.rx_count == curr.rx_count &&
	    channels.tx_count == curr.tx_count &&
	    channels.combined_count == curr.combined_count &&
	    channels.other_count == curr.other_count)
		वापस 0;

	/* ensure new counts are within the maximums */
	अगर (channels.rx_count > curr.max_rx ||
	    channels.tx_count > curr.max_tx ||
	    channels.combined_count > curr.max_combined ||
	    channels.other_count > curr.max_other)
		वापस -EINVAL;

	/* ensure there is at least one RX and one TX channel */
	अगर (!channels.combined_count &&
	    (!channels.rx_count || !channels.tx_count))
		वापस -EINVAL;

	/* ensure the new Rx count fits within the configured Rx flow
	 * indirection table settings */
	अगर (netअगर_is_rxfh_configured(dev) &&
	    !ethtool_get_max_rxfh_channel(dev, &max_rx_in_use) &&
	    (channels.combined_count + channels.rx_count) <= max_rx_in_use)
	    वापस -EINVAL;

	/* Disabling channels, query zero-copy AF_XDP sockets */
	from_channel = channels.combined_count +
		min(channels.rx_count, channels.tx_count);
	to_channel = curr.combined_count + max(curr.rx_count, curr.tx_count);
	क्रम (i = from_channel; i < to_channel; i++)
		अगर (xsk_get_pool_from_qid(dev, i))
			वापस -EINVAL;

	ret = dev->ethtool_ops->set_channels(dev, &channels);
	अगर (!ret)
		ethtool_notअगरy(dev, ETHTOOL_MSG_CHANNELS_NTF, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_छोड़ोparam(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_छोड़ोparam छोड़ोparam = अणु .cmd = ETHTOOL_GPAUSEPARAM पूर्ण;

	अगर (!dev->ethtool_ops->get_छोड़ोparam)
		वापस -EOPNOTSUPP;

	dev->ethtool_ops->get_छोड़ोparam(dev, &छोड़ोparam);

	अगर (copy_to_user(useraddr, &छोड़ोparam, माप(छोड़ोparam)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_छोड़ोparam(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_छोड़ोparam छोड़ोparam;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->set_छोड़ोparam)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&छोड़ोparam, useraddr, माप(छोड़ोparam)))
		वापस -EFAULT;

	ret = dev->ethtool_ops->set_छोड़ोparam(dev, &छोड़ोparam);
	अगर (!ret)
		ethtool_notअगरy(dev, ETHTOOL_MSG_PAUSE_NTF, शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_self_test(काष्ठा net_device *dev, अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_test test;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	u64 *data;
	पूर्णांक ret, test_len;

	अगर (!ops->self_test || !ops->get_sset_count)
		वापस -EOPNOTSUPP;

	test_len = ops->get_sset_count(dev, ETH_SS_TEST);
	अगर (test_len < 0)
		वापस test_len;
	WARN_ON(test_len == 0);

	अगर (copy_from_user(&test, useraddr, माप(test)))
		वापस -EFAULT;

	test.len = test_len;
	data = kसुस्मृति(test_len, माप(u64), GFP_USER);
	अगर (!data)
		वापस -ENOMEM;

	netअगर_testing_on(dev);
	ops->self_test(dev, &test, data);
	netअगर_testing_off(dev);

	ret = -EFAULT;
	अगर (copy_to_user(useraddr, &test, माप(test)))
		जाओ out;
	useraddr += माप(test);
	अगर (copy_to_user(useraddr, data, test.len * माप(u64)))
		जाओ out;
	ret = 0;

 out:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_strings(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_gstrings gstrings;
	u8 *data;
	पूर्णांक ret;

	अगर (copy_from_user(&gstrings, useraddr, माप(gstrings)))
		वापस -EFAULT;

	ret = __ethtool_get_sset_count(dev, gstrings.string_set);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > S32_MAX / ETH_GSTRING_LEN)
		वापस -ENOMEM;
	WARN_ON_ONCE(!ret);

	gstrings.len = ret;

	अगर (gstrings.len) अणु
		data = vzalloc(array_size(gstrings.len, ETH_GSTRING_LEN));
		अगर (!data)
			वापस -ENOMEM;

		__ethtool_get_strings(dev, gstrings.string_set, data);
	पूर्ण अन्यथा अणु
		data = शून्य;
	पूर्ण

	ret = -EFAULT;
	अगर (copy_to_user(useraddr, &gstrings, माप(gstrings)))
		जाओ out;
	useraddr += माप(gstrings);
	अगर (gstrings.len &&
	    copy_to_user(useraddr, data, gstrings.len * ETH_GSTRING_LEN))
		जाओ out;
	ret = 0;

out:
	vमुक्त(data);
	वापस ret;
पूर्ण

__म_लिखो(2, 3) व्योम ethtool_प्र_लिखो(u8 **data, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(*data, ETH_GSTRING_LEN, fmt, args);
	बहु_पूर्ण(args);

	*data += ETH_GSTRING_LEN;
पूर्ण
EXPORT_SYMBOL(ethtool_प्र_लिखो);

अटल पूर्णांक ethtool_phys_id(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_value id;
	अटल bool busy;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	पूर्णांक rc;

	अगर (!ops->set_phys_id)
		वापस -EOPNOTSUPP;

	अगर (busy)
		वापस -EBUSY;

	अगर (copy_from_user(&id, useraddr, माप(id)))
		वापस -EFAULT;

	rc = ops->set_phys_id(dev, ETHTOOL_ID_ACTIVE);
	अगर (rc < 0)
		वापस rc;

	/* Drop the RTNL lock जबतक रुकोing, but prevent reentry or
	 * removal of the device.
	 */
	busy = true;
	dev_hold(dev);
	rtnl_unlock();

	अगर (rc == 0) अणु
		/* Driver will handle this itself */
		schedule_समयout_पूर्णांकerruptible(
			id.data ? (id.data * HZ) : MAX_SCHEDULE_TIMEOUT);
	पूर्ण अन्यथा अणु
		/* Driver expects to be called at twice the frequency in rc */
		पूर्णांक n = rc * 2, पूर्णांकerval = HZ / n;
		u64 count = n * id.data, i = 0;

		करो अणु
			rtnl_lock();
			rc = ops->set_phys_id(dev,
				    (i++ & 1) ? ETHTOOL_ID_OFF : ETHTOOL_ID_ON);
			rtnl_unlock();
			अगर (rc)
				अवरोध;
			schedule_समयout_पूर्णांकerruptible(पूर्णांकerval);
		पूर्ण जबतक (!संकेत_pending(current) && (!id.data || i < count));
	पूर्ण

	rtnl_lock();
	dev_put(dev);
	busy = false;

	(व्योम) ops->set_phys_id(dev, ETHTOOL_ID_INACTIVE);
	वापस rc;
पूर्ण

अटल पूर्णांक ethtool_get_stats(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_stats stats;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	u64 *data;
	पूर्णांक ret, n_stats;

	अगर (!ops->get_ethtool_stats || !ops->get_sset_count)
		वापस -EOPNOTSUPP;

	n_stats = ops->get_sset_count(dev, ETH_SS_STATS);
	अगर (n_stats < 0)
		वापस n_stats;
	अगर (n_stats > S32_MAX / माप(u64))
		वापस -ENOMEM;
	WARN_ON_ONCE(!n_stats);
	अगर (copy_from_user(&stats, useraddr, माप(stats)))
		वापस -EFAULT;

	stats.n_stats = n_stats;

	अगर (n_stats) अणु
		data = vzalloc(array_size(n_stats, माप(u64)));
		अगर (!data)
			वापस -ENOMEM;
		ops->get_ethtool_stats(dev, &stats, data);
	पूर्ण अन्यथा अणु
		data = शून्य;
	पूर्ण

	ret = -EFAULT;
	अगर (copy_to_user(useraddr, &stats, माप(stats)))
		जाओ out;
	useraddr += माप(stats);
	अगर (n_stats && copy_to_user(useraddr, data, array_size(n_stats, माप(u64))))
		जाओ out;
	ret = 0;

 out:
	vमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_phy_stats(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	स्थिर काष्ठा ethtool_phy_ops *phy_ops = ethtool_phy_ops;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	काष्ठा phy_device *phydev = dev->phydev;
	काष्ठा ethtool_stats stats;
	u64 *data;
	पूर्णांक ret, n_stats;

	अगर (!phydev && (!ops->get_ethtool_phy_stats || !ops->get_sset_count))
		वापस -EOPNOTSUPP;

	अगर (dev->phydev && !ops->get_ethtool_phy_stats &&
	    phy_ops && phy_ops->get_sset_count)
		n_stats = phy_ops->get_sset_count(dev->phydev);
	अन्यथा
		n_stats = ops->get_sset_count(dev, ETH_SS_PHY_STATS);
	अगर (n_stats < 0)
		वापस n_stats;
	अगर (n_stats > S32_MAX / माप(u64))
		वापस -ENOMEM;
	WARN_ON_ONCE(!n_stats);

	अगर (copy_from_user(&stats, useraddr, माप(stats)))
		वापस -EFAULT;

	stats.n_stats = n_stats;

	अगर (n_stats) अणु
		data = vzalloc(array_size(n_stats, माप(u64)));
		अगर (!data)
			वापस -ENOMEM;

		अगर (dev->phydev && !ops->get_ethtool_phy_stats &&
		    phy_ops && phy_ops->get_stats) अणु
			ret = phy_ops->get_stats(dev->phydev, &stats, data);
			अगर (ret < 0)
				जाओ out;
		पूर्ण अन्यथा अणु
			ops->get_ethtool_phy_stats(dev, &stats, data);
		पूर्ण
	पूर्ण अन्यथा अणु
		data = शून्य;
	पूर्ण

	ret = -EFAULT;
	अगर (copy_to_user(useraddr, &stats, माप(stats)))
		जाओ out;
	useraddr += माप(stats);
	अगर (n_stats && copy_to_user(useraddr, data, array_size(n_stats, माप(u64))))
		जाओ out;
	ret = 0;

 out:
	vमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_perm_addr(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_perm_addr epaddr;

	अगर (copy_from_user(&epaddr, useraddr, माप(epaddr)))
		वापस -EFAULT;

	अगर (epaddr.size < dev->addr_len)
		वापस -ETOOSMALL;
	epaddr.size = dev->addr_len;

	अगर (copy_to_user(useraddr, &epaddr, माप(epaddr)))
		वापस -EFAULT;
	useraddr += माप(epaddr);
	अगर (copy_to_user(useraddr, dev->perm_addr, epaddr.size))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_get_value(काष्ठा net_device *dev, अक्षर __user *useraddr,
			     u32 cmd, u32 (*actor)(काष्ठा net_device *))
अणु
	काष्ठा ethtool_value edata = अणु .cmd = cmd पूर्ण;

	अगर (!actor)
		वापस -EOPNOTSUPP;

	edata.data = actor(dev);

	अगर (copy_to_user(useraddr, &edata, माप(edata)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_value_व्योम(काष्ठा net_device *dev, अक्षर __user *useraddr,
			     व्योम (*actor)(काष्ठा net_device *, u32))
अणु
	काष्ठा ethtool_value edata;

	अगर (!actor)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&edata, useraddr, माप(edata)))
		वापस -EFAULT;

	actor(dev, edata.data);
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_value(काष्ठा net_device *dev, अक्षर __user *useraddr,
			     पूर्णांक (*actor)(काष्ठा net_device *, u32))
अणु
	काष्ठा ethtool_value edata;

	अगर (!actor)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&edata, useraddr, माप(edata)))
		वापस -EFAULT;

	वापस actor(dev, edata.data);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ethtool_flash_device(काष्ठा net_device *dev,
						   अक्षर __user *useraddr)
अणु
	काष्ठा ethtool_flash efl;

	अगर (copy_from_user(&efl, useraddr, माप(efl)))
		वापस -EFAULT;
	efl.data[ETHTOOL_FLASH_MAX_खाताNAME - 1] = 0;

	अगर (!dev->ethtool_ops->flash_device)
		वापस devlink_compat_flash_update(dev, efl.data);

	वापस dev->ethtool_ops->flash_device(dev, &efl);
पूर्ण

अटल पूर्णांक ethtool_set_dump(काष्ठा net_device *dev,
			व्योम __user *useraddr)
अणु
	काष्ठा ethtool_dump dump;

	अगर (!dev->ethtool_ops->set_dump)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&dump, useraddr, माप(dump)))
		वापस -EFAULT;

	वापस dev->ethtool_ops->set_dump(dev, &dump);
पूर्ण

अटल पूर्णांक ethtool_get_dump_flag(काष्ठा net_device *dev,
				व्योम __user *useraddr)
अणु
	पूर्णांक ret;
	काष्ठा ethtool_dump dump;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;

	अगर (!ops->get_dump_flag)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&dump, useraddr, माप(dump)))
		वापस -EFAULT;

	ret = ops->get_dump_flag(dev, &dump);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(useraddr, &dump, माप(dump)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_get_dump_data(काष्ठा net_device *dev,
				व्योम __user *useraddr)
अणु
	पूर्णांक ret;
	__u32 len;
	काष्ठा ethtool_dump dump, पंचांगp;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	व्योम *data = शून्य;

	अगर (!ops->get_dump_data || !ops->get_dump_flag)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&dump, useraddr, माप(dump)))
		वापस -EFAULT;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	पंचांगp.cmd = ETHTOOL_GET_DUMP_FLAG;
	ret = ops->get_dump_flag(dev, &पंचांगp);
	अगर (ret)
		वापस ret;

	len = min(पंचांगp.len, dump.len);
	अगर (!len)
		वापस -EFAULT;

	/* Don't ever let the driver think there's more space available
	 * than it requested with .get_dump_flag().
	 */
	dump.len = len;

	/* Always allocate enough space to hold the whole thing so that the
	 * driver करोes not need to check the length and bother with partial
	 * dumping.
	 */
	data = vzalloc(पंचांगp.len);
	अगर (!data)
		वापस -ENOMEM;
	ret = ops->get_dump_data(dev, &dump, data);
	अगर (ret)
		जाओ out;

	/* There are two sane possibilities:
	 * 1. The driver's .get_dump_data() करोes not touch dump.len.
	 * 2. Or it may set dump.len to how much it really ग_लिखोs, which
	 *    should be पंचांगp.len (or len अगर it can करो a partial dump).
	 * In any हाल respond to userspace with the actual length of data
	 * it's receiving.
	 */
	WARN_ON(dump.len != len && dump.len != पंचांगp.len);
	dump.len = len;

	अगर (copy_to_user(useraddr, &dump, माप(dump))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	useraddr += दुरत्व(काष्ठा ethtool_dump, data);
	अगर (copy_to_user(useraddr, data, len))
		ret = -EFAULT;
out:
	vमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_ts_info(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_ts_info info;
	पूर्णांक err;

	err = __ethtool_get_ts_info(dev, &info);
	अगर (err)
		वापस err;

	अगर (copy_to_user(useraddr, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक ethtool_get_module_info_call(काष्ठा net_device *dev,
				 काष्ठा ethtool_modinfo *modinfo)
अणु
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	काष्ठा phy_device *phydev = dev->phydev;

	अगर (dev->sfp_bus)
		वापस sfp_get_module_info(dev->sfp_bus, modinfo);

	अगर (phydev && phydev->drv && phydev->drv->module_info)
		वापस phydev->drv->module_info(phydev, modinfo);

	अगर (ops->get_module_info)
		वापस ops->get_module_info(dev, modinfo);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ethtool_get_module_info(काष्ठा net_device *dev,
				   व्योम __user *useraddr)
अणु
	पूर्णांक ret;
	काष्ठा ethtool_modinfo modinfo;

	अगर (copy_from_user(&modinfo, useraddr, माप(modinfo)))
		वापस -EFAULT;

	ret = ethtool_get_module_info_call(dev, &modinfo);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(useraddr, &modinfo, माप(modinfo)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक ethtool_get_module_eeprom_call(काष्ठा net_device *dev,
				   काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	काष्ठा phy_device *phydev = dev->phydev;

	अगर (dev->sfp_bus)
		वापस sfp_get_module_eeprom(dev->sfp_bus, ee, data);

	अगर (phydev && phydev->drv && phydev->drv->module_eeprom)
		वापस phydev->drv->module_eeprom(phydev, ee, data);

	अगर (ops->get_module_eeprom)
		वापस ops->get_module_eeprom(dev, ee, data);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ethtool_get_module_eeprom(काष्ठा net_device *dev,
				     व्योम __user *useraddr)
अणु
	पूर्णांक ret;
	काष्ठा ethtool_modinfo modinfo;

	ret = ethtool_get_module_info_call(dev, &modinfo);
	अगर (ret)
		वापस ret;

	वापस ethtool_get_any_eeprom(dev, useraddr,
				      ethtool_get_module_eeprom_call,
				      modinfo.eeprom_len);
पूर्ण

अटल पूर्णांक ethtool_tunable_valid(स्थिर काष्ठा ethtool_tunable *tuna)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
	हाल ETHTOOL_TX_COPYBREAK:
		अगर (tuna->len != माप(u32) ||
		    tuna->type_id != ETHTOOL_TUNABLE_U32)
			वापस -EINVAL;
		अवरोध;
	हाल ETHTOOL_PFC_PREVENTION_TOUT:
		अगर (tuna->len != माप(u16) ||
		    tuna->type_id != ETHTOOL_TUNABLE_U16)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_get_tunable(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	पूर्णांक ret;
	काष्ठा ethtool_tunable tuna;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	व्योम *data;

	अगर (!ops->get_tunable)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&tuna, useraddr, माप(tuna)))
		वापस -EFAULT;
	ret = ethtool_tunable_valid(&tuna);
	अगर (ret)
		वापस ret;
	data = kzalloc(tuna.len, GFP_USER);
	अगर (!data)
		वापस -ENOMEM;
	ret = ops->get_tunable(dev, &tuna, data);
	अगर (ret)
		जाओ out;
	useraddr += माप(tuna);
	ret = -EFAULT;
	अगर (copy_to_user(useraddr, data, tuna.len))
		जाओ out;
	ret = 0;

out:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_set_tunable(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	पूर्णांक ret;
	काष्ठा ethtool_tunable tuna;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	व्योम *data;

	अगर (!ops->set_tunable)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&tuna, useraddr, माप(tuna)))
		वापस -EFAULT;
	ret = ethtool_tunable_valid(&tuna);
	अगर (ret)
		वापस ret;
	useraddr += माप(tuna);
	data = memdup_user(useraddr, tuna.len);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	ret = ops->set_tunable(dev, &tuna, data);

	kमुक्त(data);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ethtool_get_per_queue_coalesce(काष्ठा net_device *dev,
			       व्योम __user *useraddr,
			       काष्ठा ethtool_per_queue_op *per_queue_opt)
अणु
	u32 bit;
	पूर्णांक ret;
	DECLARE_BITMAP(queue_mask, MAX_NUM_QUEUE);

	अगर (!dev->ethtool_ops->get_per_queue_coalesce)
		वापस -EOPNOTSUPP;

	useraddr += माप(*per_queue_opt);

	biपंचांगap_from_arr32(queue_mask, per_queue_opt->queue_mask,
			  MAX_NUM_QUEUE);

	क्रम_each_set_bit(bit, queue_mask, MAX_NUM_QUEUE) अणु
		काष्ठा ethtool_coalesce coalesce = अणु .cmd = ETHTOOL_GCOALESCE पूर्ण;

		ret = dev->ethtool_ops->get_per_queue_coalesce(dev, bit, &coalesce);
		अगर (ret != 0)
			वापस ret;
		अगर (copy_to_user(useraddr, &coalesce, माप(coalesce)))
			वापस -EFAULT;
		useraddr += माप(coalesce);
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ethtool_set_per_queue_coalesce(काष्ठा net_device *dev,
			       व्योम __user *useraddr,
			       काष्ठा ethtool_per_queue_op *per_queue_opt)
अणु
	u32 bit;
	पूर्णांक i, ret = 0;
	पूर्णांक n_queue;
	काष्ठा ethtool_coalesce *backup = शून्य, *पंचांगp = शून्य;
	DECLARE_BITMAP(queue_mask, MAX_NUM_QUEUE);

	अगर ((!dev->ethtool_ops->set_per_queue_coalesce) ||
	    (!dev->ethtool_ops->get_per_queue_coalesce))
		वापस -EOPNOTSUPP;

	useraddr += माप(*per_queue_opt);

	biपंचांगap_from_arr32(queue_mask, per_queue_opt->queue_mask, MAX_NUM_QUEUE);
	n_queue = biपंचांगap_weight(queue_mask, MAX_NUM_QUEUE);
	पंचांगp = backup = kदो_स्मृति_array(n_queue, माप(*backup), GFP_KERNEL);
	अगर (!backup)
		वापस -ENOMEM;

	क्रम_each_set_bit(bit, queue_mask, MAX_NUM_QUEUE) अणु
		काष्ठा ethtool_coalesce coalesce;

		ret = dev->ethtool_ops->get_per_queue_coalesce(dev, bit, पंचांगp);
		अगर (ret != 0)
			जाओ roll_back;

		पंचांगp++;

		अगर (copy_from_user(&coalesce, useraddr, माप(coalesce))) अणु
			ret = -EFAULT;
			जाओ roll_back;
		पूर्ण

		अगर (!ethtool_set_coalesce_supported(dev, &coalesce)) अणु
			ret = -EOPNOTSUPP;
			जाओ roll_back;
		पूर्ण

		ret = dev->ethtool_ops->set_per_queue_coalesce(dev, bit, &coalesce);
		अगर (ret != 0)
			जाओ roll_back;

		useraddr += माप(coalesce);
	पूर्ण

roll_back:
	अगर (ret != 0) अणु
		पंचांगp = backup;
		क्रम_each_set_bit(i, queue_mask, bit) अणु
			dev->ethtool_ops->set_per_queue_coalesce(dev, i, पंचांगp);
			पंचांगp++;
		पूर्ण
	पूर्ण
	kमुक्त(backup);

	वापस ret;
पूर्ण

अटल पूर्णांक noअंतरभूत_क्रम_stack ethtool_set_per_queue(काष्ठा net_device *dev,
				 व्योम __user *useraddr, u32 sub_cmd)
अणु
	काष्ठा ethtool_per_queue_op per_queue_opt;

	अगर (copy_from_user(&per_queue_opt, useraddr, माप(per_queue_opt)))
		वापस -EFAULT;

	अगर (per_queue_opt.sub_command != sub_cmd)
		वापस -EINVAL;

	चयन (per_queue_opt.sub_command) अणु
	हाल ETHTOOL_GCOALESCE:
		वापस ethtool_get_per_queue_coalesce(dev, useraddr, &per_queue_opt);
	हाल ETHTOOL_SCOALESCE:
		वापस ethtool_set_per_queue_coalesce(dev, useraddr, &per_queue_opt);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ethtool_phy_tunable_valid(स्थिर काष्ठा ethtool_tunable *tuna)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
	हाल ETHTOOL_PHY_FAST_LINK_DOWN:
		अगर (tuna->len != माप(u8) ||
		    tuna->type_id != ETHTOOL_TUNABLE_U8)
			वापस -EINVAL;
		अवरोध;
	हाल ETHTOOL_PHY_EDPD:
		अगर (tuna->len != माप(u16) ||
		    tuna->type_id != ETHTOOL_TUNABLE_U16)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_phy_tunable(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा phy_device *phydev = dev->phydev;
	काष्ठा ethtool_tunable tuna;
	bool phy_drv_tunable;
	व्योम *data;
	पूर्णांक ret;

	phy_drv_tunable = phydev && phydev->drv && phydev->drv->get_tunable;
	अगर (!phy_drv_tunable && !dev->ethtool_ops->get_phy_tunable)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&tuna, useraddr, माप(tuna)))
		वापस -EFAULT;
	ret = ethtool_phy_tunable_valid(&tuna);
	अगर (ret)
		वापस ret;
	data = kzalloc(tuna.len, GFP_USER);
	अगर (!data)
		वापस -ENOMEM;
	अगर (phy_drv_tunable) अणु
		mutex_lock(&phydev->lock);
		ret = phydev->drv->get_tunable(phydev, &tuna, data);
		mutex_unlock(&phydev->lock);
	पूर्ण अन्यथा अणु
		ret = dev->ethtool_ops->get_phy_tunable(dev, &tuna, data);
	पूर्ण
	अगर (ret)
		जाओ out;
	useraddr += माप(tuna);
	ret = -EFAULT;
	अगर (copy_to_user(useraddr, data, tuna.len))
		जाओ out;
	ret = 0;

out:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक set_phy_tunable(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा phy_device *phydev = dev->phydev;
	काष्ठा ethtool_tunable tuna;
	bool phy_drv_tunable;
	व्योम *data;
	पूर्णांक ret;

	phy_drv_tunable = phydev && phydev->drv && phydev->drv->get_tunable;
	अगर (!phy_drv_tunable && !dev->ethtool_ops->set_phy_tunable)
		वापस -EOPNOTSUPP;
	अगर (copy_from_user(&tuna, useraddr, माप(tuna)))
		वापस -EFAULT;
	ret = ethtool_phy_tunable_valid(&tuna);
	अगर (ret)
		वापस ret;
	useraddr += माप(tuna);
	data = memdup_user(useraddr, tuna.len);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	अगर (phy_drv_tunable) अणु
		mutex_lock(&phydev->lock);
		ret = phydev->drv->set_tunable(phydev, &tuna, data);
		mutex_unlock(&phydev->lock);
	पूर्ण अन्यथा अणु
		ret = dev->ethtool_ops->set_phy_tunable(dev, &tuna, data);
	पूर्ण

	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक ethtool_get_fecparam(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_fecparam fecparam = अणु .cmd = ETHTOOL_GFECPARAM पूर्ण;
	पूर्णांक rc;

	अगर (!dev->ethtool_ops->get_fecparam)
		वापस -EOPNOTSUPP;

	rc = dev->ethtool_ops->get_fecparam(dev, &fecparam);
	अगर (rc)
		वापस rc;

	अगर (WARN_ON_ONCE(fecparam.reserved))
		fecparam.reserved = 0;

	अगर (copy_to_user(useraddr, &fecparam, माप(fecparam)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक ethtool_set_fecparam(काष्ठा net_device *dev, व्योम __user *useraddr)
अणु
	काष्ठा ethtool_fecparam fecparam;

	अगर (!dev->ethtool_ops->set_fecparam)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&fecparam, useraddr, माप(fecparam)))
		वापस -EFAULT;

	अगर (!fecparam.fec || fecparam.fec & ETHTOOL_FEC_NONE)
		वापस -EINVAL;

	fecparam.active_fec = 0;
	fecparam.reserved = 0;

	वापस dev->ethtool_ops->set_fecparam(dev, &fecparam);
पूर्ण

/* The मुख्य entry poपूर्णांक in this file.  Called from net/core/dev_ioctl.c */

पूर्णांक dev_ethtool(काष्ठा net *net, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा net_device *dev = __dev_get_by_name(net, अगरr->अगरr_name);
	व्योम __user *useraddr = अगरr->अगरr_data;
	u32 ethcmd, sub_cmd;
	पूर्णांक rc;
	netdev_features_t old_features;

	अगर (!dev || !netअगर_device_present(dev))
		वापस -ENODEV;

	अगर (copy_from_user(&ethcmd, useraddr, माप(ethcmd)))
		वापस -EFAULT;

	अगर (ethcmd == ETHTOOL_PERQUEUE) अणु
		अगर (copy_from_user(&sub_cmd, useraddr + माप(ethcmd), माप(sub_cmd)))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		sub_cmd = ethcmd;
	पूर्ण
	/* Allow some commands to be करोne by anyone */
	चयन (sub_cmd) अणु
	हाल ETHTOOL_GSET:
	हाल ETHTOOL_GDRVINFO:
	हाल ETHTOOL_GMSGLVL:
	हाल ETHTOOL_GLINK:
	हाल ETHTOOL_GCOALESCE:
	हाल ETHTOOL_GRINGPARAM:
	हाल ETHTOOL_GPAUSEPARAM:
	हाल ETHTOOL_GRXCSUM:
	हाल ETHTOOL_GTXCSUM:
	हाल ETHTOOL_GSG:
	हाल ETHTOOL_GSSET_INFO:
	हाल ETHTOOL_GSTRINGS:
	हाल ETHTOOL_GSTATS:
	हाल ETHTOOL_GPHYSTATS:
	हाल ETHTOOL_GTSO:
	हाल ETHTOOL_GPERMADDR:
	हाल ETHTOOL_GUFO:
	हाल ETHTOOL_GGSO:
	हाल ETHTOOL_GGRO:
	हाल ETHTOOL_GFLAGS:
	हाल ETHTOOL_GPFLAGS:
	हाल ETHTOOL_GRXFH:
	हाल ETHTOOL_GRXRINGS:
	हाल ETHTOOL_GRXCLSRLCNT:
	हाल ETHTOOL_GRXCLSRULE:
	हाल ETHTOOL_GRXCLSRLALL:
	हाल ETHTOOL_GRXFHINसूची:
	हाल ETHTOOL_GRSSH:
	हाल ETHTOOL_GFEATURES:
	हाल ETHTOOL_GCHANNELS:
	हाल ETHTOOL_GET_TS_INFO:
	हाल ETHTOOL_GEEE:
	हाल ETHTOOL_GTUNABLE:
	हाल ETHTOOL_PHY_GTUNABLE:
	हाल ETHTOOL_GLINKSETTINGS:
	हाल ETHTOOL_GFECPARAM:
		अवरोध;
	शेष:
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
	पूर्ण

	अगर (dev->ethtool_ops->begin) अणु
		rc = dev->ethtool_ops->begin(dev);
		अगर (rc  < 0)
			वापस rc;
	पूर्ण
	old_features = dev->features;

	चयन (ethcmd) अणु
	हाल ETHTOOL_GSET:
		rc = ethtool_get_settings(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SSET:
		rc = ethtool_set_settings(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GDRVINFO:
		rc = ethtool_get_drvinfo(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GREGS:
		rc = ethtool_get_regs(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GWOL:
		rc = ethtool_get_wol(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SWOL:
		rc = ethtool_set_wol(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GMSGLVL:
		rc = ethtool_get_value(dev, useraddr, ethcmd,
				       dev->ethtool_ops->get_msglevel);
		अवरोध;
	हाल ETHTOOL_SMSGLVL:
		rc = ethtool_set_value_व्योम(dev, useraddr,
				       dev->ethtool_ops->set_msglevel);
		अगर (!rc)
			ethtool_notअगरy(dev, ETHTOOL_MSG_DEBUG_NTF, शून्य);
		अवरोध;
	हाल ETHTOOL_GEEE:
		rc = ethtool_get_eee(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SEEE:
		rc = ethtool_set_eee(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_NWAY_RST:
		rc = ethtool_nway_reset(dev);
		अवरोध;
	हाल ETHTOOL_GLINK:
		rc = ethtool_get_link(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GEEPROM:
		rc = ethtool_get_eeprom(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SEEPROM:
		rc = ethtool_set_eeprom(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GCOALESCE:
		rc = ethtool_get_coalesce(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SCOALESCE:
		rc = ethtool_set_coalesce(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GRINGPARAM:
		rc = ethtool_get_ringparam(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SRINGPARAM:
		rc = ethtool_set_ringparam(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GPAUSEPARAM:
		rc = ethtool_get_छोड़ोparam(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SPAUSEPARAM:
		rc = ethtool_set_छोड़ोparam(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_TEST:
		rc = ethtool_self_test(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GSTRINGS:
		rc = ethtool_get_strings(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_PHYS_ID:
		rc = ethtool_phys_id(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GSTATS:
		rc = ethtool_get_stats(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GPERMADDR:
		rc = ethtool_get_perm_addr(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GFLAGS:
		rc = ethtool_get_value(dev, useraddr, ethcmd,
					__ethtool_get_flags);
		अवरोध;
	हाल ETHTOOL_SFLAGS:
		rc = ethtool_set_value(dev, useraddr, __ethtool_set_flags);
		अवरोध;
	हाल ETHTOOL_GPFLAGS:
		rc = ethtool_get_value(dev, useraddr, ethcmd,
				       dev->ethtool_ops->get_priv_flags);
		अगर (!rc)
			ethtool_notअगरy(dev, ETHTOOL_MSG_PRIVFLAGS_NTF, शून्य);
		अवरोध;
	हाल ETHTOOL_SPFLAGS:
		rc = ethtool_set_value(dev, useraddr,
				       dev->ethtool_ops->set_priv_flags);
		अवरोध;
	हाल ETHTOOL_GRXFH:
	हाल ETHTOOL_GRXRINGS:
	हाल ETHTOOL_GRXCLSRLCNT:
	हाल ETHTOOL_GRXCLSRULE:
	हाल ETHTOOL_GRXCLSRLALL:
		rc = ethtool_get_rxnfc(dev, ethcmd, useraddr);
		अवरोध;
	हाल ETHTOOL_SRXFH:
	हाल ETHTOOL_SRXCLSRLDEL:
	हाल ETHTOOL_SRXCLSRLINS:
		rc = ethtool_set_rxnfc(dev, ethcmd, useraddr);
		अवरोध;
	हाल ETHTOOL_FLASHDEV:
		rc = ethtool_flash_device(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_RESET:
		rc = ethtool_reset(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GSSET_INFO:
		rc = ethtool_get_sset_info(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GRXFHINसूची:
		rc = ethtool_get_rxfh_indir(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SRXFHINसूची:
		rc = ethtool_set_rxfh_indir(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GRSSH:
		rc = ethtool_get_rxfh(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SRSSH:
		rc = ethtool_set_rxfh(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GFEATURES:
		rc = ethtool_get_features(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SFEATURES:
		rc = ethtool_set_features(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GTXCSUM:
	हाल ETHTOOL_GRXCSUM:
	हाल ETHTOOL_GSG:
	हाल ETHTOOL_GTSO:
	हाल ETHTOOL_GGSO:
	हाल ETHTOOL_GGRO:
		rc = ethtool_get_one_feature(dev, useraddr, ethcmd);
		अवरोध;
	हाल ETHTOOL_STXCSUM:
	हाल ETHTOOL_SRXCSUM:
	हाल ETHTOOL_SSG:
	हाल ETHTOOL_STSO:
	हाल ETHTOOL_SGSO:
	हाल ETHTOOL_SGRO:
		rc = ethtool_set_one_feature(dev, useraddr, ethcmd);
		अवरोध;
	हाल ETHTOOL_GCHANNELS:
		rc = ethtool_get_channels(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SCHANNELS:
		rc = ethtool_set_channels(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SET_DUMP:
		rc = ethtool_set_dump(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GET_DUMP_FLAG:
		rc = ethtool_get_dump_flag(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GET_DUMP_DATA:
		rc = ethtool_get_dump_data(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GET_TS_INFO:
		rc = ethtool_get_ts_info(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GMODULEINFO:
		rc = ethtool_get_module_info(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GMODULEEEPROM:
		rc = ethtool_get_module_eeprom(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GTUNABLE:
		rc = ethtool_get_tunable(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_STUNABLE:
		rc = ethtool_set_tunable(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GPHYSTATS:
		rc = ethtool_get_phy_stats(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_PERQUEUE:
		rc = ethtool_set_per_queue(dev, useraddr, sub_cmd);
		अवरोध;
	हाल ETHTOOL_GLINKSETTINGS:
		rc = ethtool_get_link_ksettings(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SLINKSETTINGS:
		rc = ethtool_set_link_ksettings(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_PHY_GTUNABLE:
		rc = get_phy_tunable(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_PHY_STUNABLE:
		rc = set_phy_tunable(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_GFECPARAM:
		rc = ethtool_get_fecparam(dev, useraddr);
		अवरोध;
	हाल ETHTOOL_SFECPARAM:
		rc = ethtool_set_fecparam(dev, useraddr);
		अवरोध;
	शेष:
		rc = -EOPNOTSUPP;
	पूर्ण

	अगर (dev->ethtool_ops->complete)
		dev->ethtool_ops->complete(dev);

	अगर (old_features != dev->features)
		netdev_features_change(dev);

	वापस rc;
पूर्ण

काष्ठा ethtool_rx_flow_key अणु
	काष्ठा flow_dissector_key_basic			basic;
	जोड़ अणु
		काष्ठा flow_dissector_key_ipv4_addrs	ipv4;
		काष्ठा flow_dissector_key_ipv6_addrs	ipv6;
	पूर्ण;
	काष्ठा flow_dissector_key_ports			tp;
	काष्ठा flow_dissector_key_ip			ip;
	काष्ठा flow_dissector_key_vlan			vlan;
	काष्ठा flow_dissector_key_eth_addrs		eth_addrs;
पूर्ण __aligned(BITS_PER_LONG / 8); /* Ensure that we can करो comparisons as दीर्घs. */

काष्ठा ethtool_rx_flow_match अणु
	काष्ठा flow_dissector		dissector;
	काष्ठा ethtool_rx_flow_key	key;
	काष्ठा ethtool_rx_flow_key	mask;
पूर्ण;

काष्ठा ethtool_rx_flow_rule *
ethtool_rx_flow_rule_create(स्थिर काष्ठा ethtool_rx_flow_spec_input *input)
अणु
	स्थिर काष्ठा ethtool_rx_flow_spec *fs = input->fs;
	अटल काष्ठा in6_addr zero_addr = अणुपूर्ण;
	काष्ठा ethtool_rx_flow_match *match;
	काष्ठा ethtool_rx_flow_rule *flow;
	काष्ठा flow_action_entry *act;

	flow = kzalloc(माप(काष्ठा ethtool_rx_flow_rule) +
		       माप(काष्ठा ethtool_rx_flow_match), GFP_KERNEL);
	अगर (!flow)
		वापस ERR_PTR(-ENOMEM);

	/* ethtool_rx supports only one single action per rule. */
	flow->rule = flow_rule_alloc(1);
	अगर (!flow->rule) अणु
		kमुक्त(flow);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	match = (काष्ठा ethtool_rx_flow_match *)flow->priv;
	flow->rule->match.dissector	= &match->dissector;
	flow->rule->match.mask		= &match->mask;
	flow->rule->match.key		= &match->key;

	match->mask.basic.n_proto = htons(0xffff);

	चयन (fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT | FLOW_RSS)) अणु
	हाल ETHER_FLOW: अणु
		स्थिर काष्ठा ethhdr *ether_spec, *ether_m_spec;

		ether_spec = &fs->h_u.ether_spec;
		ether_m_spec = &fs->m_u.ether_spec;

		अगर (!is_zero_ether_addr(ether_m_spec->h_source)) अणु
			ether_addr_copy(match->key.eth_addrs.src,
					ether_spec->h_source);
			ether_addr_copy(match->mask.eth_addrs.src,
					ether_m_spec->h_source);
		पूर्ण
		अगर (!is_zero_ether_addr(ether_m_spec->h_dest)) अणु
			ether_addr_copy(match->key.eth_addrs.dst,
					ether_spec->h_dest);
			ether_addr_copy(match->mask.eth_addrs.dst,
					ether_m_spec->h_dest);
		पूर्ण
		अगर (ether_m_spec->h_proto) अणु
			match->key.basic.n_proto = ether_spec->h_proto;
			match->mask.basic.n_proto = ether_m_spec->h_proto;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW: अणु
		स्थिर काष्ठा ethtool_tcpip4_spec *v4_spec, *v4_m_spec;

		match->key.basic.n_proto = htons(ETH_P_IP);

		v4_spec = &fs->h_u.tcp_ip4_spec;
		v4_m_spec = &fs->m_u.tcp_ip4_spec;

		अगर (v4_m_spec->ip4src) अणु
			match->key.ipv4.src = v4_spec->ip4src;
			match->mask.ipv4.src = v4_m_spec->ip4src;
		पूर्ण
		अगर (v4_m_spec->ip4dst) अणु
			match->key.ipv4.dst = v4_spec->ip4dst;
			match->mask.ipv4.dst = v4_m_spec->ip4dst;
		पूर्ण
		अगर (v4_m_spec->ip4src ||
		    v4_m_spec->ip4dst) अणु
			match->dissector.used_keys |=
				BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS);
			match->dissector.offset[FLOW_DISSECTOR_KEY_IPV4_ADDRS] =
				दुरत्व(काष्ठा ethtool_rx_flow_key, ipv4);
		पूर्ण
		अगर (v4_m_spec->psrc) अणु
			match->key.tp.src = v4_spec->psrc;
			match->mask.tp.src = v4_m_spec->psrc;
		पूर्ण
		अगर (v4_m_spec->pdst) अणु
			match->key.tp.dst = v4_spec->pdst;
			match->mask.tp.dst = v4_m_spec->pdst;
		पूर्ण
		अगर (v4_m_spec->psrc ||
		    v4_m_spec->pdst) अणु
			match->dissector.used_keys |=
				BIT(FLOW_DISSECTOR_KEY_PORTS);
			match->dissector.offset[FLOW_DISSECTOR_KEY_PORTS] =
				दुरत्व(काष्ठा ethtool_rx_flow_key, tp);
		पूर्ण
		अगर (v4_m_spec->tos) अणु
			match->key.ip.tos = v4_spec->tos;
			match->mask.ip.tos = v4_m_spec->tos;
			match->dissector.used_keys |=
				BIT(FLOW_DISSECTOR_KEY_IP);
			match->dissector.offset[FLOW_DISSECTOR_KEY_IP] =
				दुरत्व(काष्ठा ethtool_rx_flow_key, ip);
		पूर्ण
		पूर्ण
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW: अणु
		स्थिर काष्ठा ethtool_tcpip6_spec *v6_spec, *v6_m_spec;

		match->key.basic.n_proto = htons(ETH_P_IPV6);

		v6_spec = &fs->h_u.tcp_ip6_spec;
		v6_m_spec = &fs->m_u.tcp_ip6_spec;
		अगर (स_भेद(v6_m_spec->ip6src, &zero_addr, माप(zero_addr))) अणु
			स_नकल(&match->key.ipv6.src, v6_spec->ip6src,
			       माप(match->key.ipv6.src));
			स_नकल(&match->mask.ipv6.src, v6_m_spec->ip6src,
			       माप(match->mask.ipv6.src));
		पूर्ण
		अगर (स_भेद(v6_m_spec->ip6dst, &zero_addr, माप(zero_addr))) अणु
			स_नकल(&match->key.ipv6.dst, v6_spec->ip6dst,
			       माप(match->key.ipv6.dst));
			स_नकल(&match->mask.ipv6.dst, v6_m_spec->ip6dst,
			       माप(match->mask.ipv6.dst));
		पूर्ण
		अगर (स_भेद(v6_m_spec->ip6src, &zero_addr, माप(zero_addr)) ||
		    स_भेद(v6_m_spec->ip6dst, &zero_addr, माप(zero_addr))) अणु
			match->dissector.used_keys |=
				BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS);
			match->dissector.offset[FLOW_DISSECTOR_KEY_IPV6_ADDRS] =
				दुरत्व(काष्ठा ethtool_rx_flow_key, ipv6);
		पूर्ण
		अगर (v6_m_spec->psrc) अणु
			match->key.tp.src = v6_spec->psrc;
			match->mask.tp.src = v6_m_spec->psrc;
		पूर्ण
		अगर (v6_m_spec->pdst) अणु
			match->key.tp.dst = v6_spec->pdst;
			match->mask.tp.dst = v6_m_spec->pdst;
		पूर्ण
		अगर (v6_m_spec->psrc ||
		    v6_m_spec->pdst) अणु
			match->dissector.used_keys |=
				BIT(FLOW_DISSECTOR_KEY_PORTS);
			match->dissector.offset[FLOW_DISSECTOR_KEY_PORTS] =
				दुरत्व(काष्ठा ethtool_rx_flow_key, tp);
		पूर्ण
		अगर (v6_m_spec->tclass) अणु
			match->key.ip.tos = v6_spec->tclass;
			match->mask.ip.tos = v6_m_spec->tclass;
			match->dissector.used_keys |=
				BIT(FLOW_DISSECTOR_KEY_IP);
			match->dissector.offset[FLOW_DISSECTOR_KEY_IP] =
				दुरत्व(काष्ठा ethtool_rx_flow_key, ip);
		पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		ethtool_rx_flow_rule_destroy(flow);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	चयन (fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT | FLOW_RSS)) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		match->key.basic.ip_proto = IPPROTO_TCP;
		match->mask.basic.ip_proto = 0xff;
		अवरोध;
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		match->key.basic.ip_proto = IPPROTO_UDP;
		match->mask.basic.ip_proto = 0xff;
		अवरोध;
	पूर्ण

	match->dissector.used_keys |= BIT(FLOW_DISSECTOR_KEY_BASIC);
	match->dissector.offset[FLOW_DISSECTOR_KEY_BASIC] =
		दुरत्व(काष्ठा ethtool_rx_flow_key, basic);

	अगर (fs->flow_type & FLOW_EXT) अणु
		स्थिर काष्ठा ethtool_flow_ext *ext_h_spec = &fs->h_ext;
		स्थिर काष्ठा ethtool_flow_ext *ext_m_spec = &fs->m_ext;

		अगर (ext_m_spec->vlan_etype) अणु
			match->key.vlan.vlan_tpid = ext_h_spec->vlan_etype;
			match->mask.vlan.vlan_tpid = ext_m_spec->vlan_etype;
		पूर्ण

		अगर (ext_m_spec->vlan_tci) अणु
			match->key.vlan.vlan_id =
				ntohs(ext_h_spec->vlan_tci) & 0x0fff;
			match->mask.vlan.vlan_id =
				ntohs(ext_m_spec->vlan_tci) & 0x0fff;

			match->key.vlan.vlan_dei =
				!!(ext_h_spec->vlan_tci & htons(0x1000));
			match->mask.vlan.vlan_dei =
				!!(ext_m_spec->vlan_tci & htons(0x1000));

			match->key.vlan.vlan_priority =
				(ntohs(ext_h_spec->vlan_tci) & 0xe000) >> 13;
			match->mask.vlan.vlan_priority =
				(ntohs(ext_m_spec->vlan_tci) & 0xe000) >> 13;
		पूर्ण

		अगर (ext_m_spec->vlan_etype ||
		    ext_m_spec->vlan_tci) अणु
			match->dissector.used_keys |=
				BIT(FLOW_DISSECTOR_KEY_VLAN);
			match->dissector.offset[FLOW_DISSECTOR_KEY_VLAN] =
				दुरत्व(काष्ठा ethtool_rx_flow_key, vlan);
		पूर्ण
	पूर्ण
	अगर (fs->flow_type & FLOW_MAC_EXT) अणु
		स्थिर काष्ठा ethtool_flow_ext *ext_h_spec = &fs->h_ext;
		स्थिर काष्ठा ethtool_flow_ext *ext_m_spec = &fs->m_ext;

		स_नकल(match->key.eth_addrs.dst, ext_h_spec->h_dest,
		       ETH_ALEN);
		स_नकल(match->mask.eth_addrs.dst, ext_m_spec->h_dest,
		       ETH_ALEN);

		match->dissector.used_keys |=
			BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS);
		match->dissector.offset[FLOW_DISSECTOR_KEY_ETH_ADDRS] =
			दुरत्व(काष्ठा ethtool_rx_flow_key, eth_addrs);
	पूर्ण

	act = &flow->rule->action.entries[0];
	चयन (fs->ring_cookie) अणु
	हाल RX_CLS_FLOW_DISC:
		act->id = FLOW_ACTION_DROP;
		अवरोध;
	हाल RX_CLS_FLOW_WAKE:
		act->id = FLOW_ACTION_WAKE;
		अवरोध;
	शेष:
		act->id = FLOW_ACTION_QUEUE;
		अगर (fs->flow_type & FLOW_RSS)
			act->queue.ctx = input->rss_ctx;

		act->queue.vf = ethtool_get_flow_spec_ring_vf(fs->ring_cookie);
		act->queue.index = ethtool_get_flow_spec_ring(fs->ring_cookie);
		अवरोध;
	पूर्ण

	वापस flow;
पूर्ण
EXPORT_SYMBOL(ethtool_rx_flow_rule_create);

व्योम ethtool_rx_flow_rule_destroy(काष्ठा ethtool_rx_flow_rule *flow)
अणु
	kमुक्त(flow->rule);
	kमुक्त(flow);
पूर्ण
EXPORT_SYMBOL(ethtool_rx_flow_rule_destroy);
