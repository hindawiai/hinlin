<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MAC commands पूर्णांकerface
 *
 * Copyright 2007-2012 Siemens AG
 *
 * Written by:
 * Sergey Lapin <slapin@ossfans.org>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ieee802154.h>

#समावेश <net/ieee802154_netdev.h>
#समावेश <net/cfg802154.h>
#समावेश <net/mac802154.h>

#समावेश "ieee802154_i.h"
#समावेश "driver-ops.h"

अटल पूर्णांक mac802154_mlme_start_req(काष्ठा net_device *dev,
				    काष्ठा ieee802154_addr *addr,
				    u8 channel, u8 page,
				    u8 bcn_ord, u8 sf_ord,
				    u8 pan_coord, u8 blx,
				    u8 coord_realign)
अणु
	काष्ठा ieee802154_llsec_params params;
	पूर्णांक changed = 0;

	ASSERT_RTNL();

	BUG_ON(addr->mode != IEEE802154_ADDR_SHORT);

	dev->ieee802154_ptr->pan_id = addr->pan_id;
	dev->ieee802154_ptr->लघु_addr = addr->लघु_addr;
	mac802154_dev_set_page_channel(dev, page, channel);

	params.pan_id = addr->pan_id;
	changed |= IEEE802154_LLSEC_PARAM_PAN_ID;

	params.hwaddr = ieee802154_devaddr_from_raw(dev->dev_addr);
	changed |= IEEE802154_LLSEC_PARAM_HWADDR;

	params.coord_hwaddr = params.hwaddr;
	changed |= IEEE802154_LLSEC_PARAM_COORD_HWADDR;

	params.coord_लघुaddr = addr->लघु_addr;
	changed |= IEEE802154_LLSEC_PARAM_COORD_SHORTADDR;

	वापस mac802154_set_params(dev, &params, changed);
पूर्ण

अटल पूर्णांक mac802154_set_mac_params(काष्ठा net_device *dev,
				    स्थिर काष्ठा ieee802154_mac_params *params)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा ieee802154_local *local = sdata->local;
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	पूर्णांक ret;

	ASSERT_RTNL();

	/* PHY */
	wpan_dev->wpan_phy->transmit_घातer = params->transmit_घातer;
	wpan_dev->wpan_phy->cca = params->cca;
	wpan_dev->wpan_phy->cca_ed_level = params->cca_ed_level;

	/* MAC */
	wpan_dev->min_be = params->min_be;
	wpan_dev->max_be = params->max_be;
	wpan_dev->csma_retries = params->csma_retries;
	wpan_dev->frame_retries = params->frame_retries;
	wpan_dev->lbt = params->lbt;

	अगर (local->hw.phy->flags & WPAN_PHY_FLAG_TXPOWER) अणु
		ret = drv_set_tx_घातer(local, params->transmit_घातer);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (local->hw.phy->flags & WPAN_PHY_FLAG_CCA_MODE) अणु
		ret = drv_set_cca_mode(local, &params->cca);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (local->hw.phy->flags & WPAN_PHY_FLAG_CCA_ED_LEVEL) अणु
		ret = drv_set_cca_ed_level(local, params->cca_ed_level);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mac802154_get_mac_params(काष्ठा net_device *dev,
				     काष्ठा ieee802154_mac_params *params)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;

	ASSERT_RTNL();

	/* PHY */
	params->transmit_घातer = wpan_dev->wpan_phy->transmit_घातer;
	params->cca = wpan_dev->wpan_phy->cca;
	params->cca_ed_level = wpan_dev->wpan_phy->cca_ed_level;

	/* MAC */
	params->min_be = wpan_dev->min_be;
	params->max_be = wpan_dev->max_be;
	params->csma_retries = wpan_dev->csma_retries;
	params->frame_retries = wpan_dev->frame_retries;
	params->lbt = wpan_dev->lbt;
पूर्ण

अटल स्थिर काष्ठा ieee802154_llsec_ops mac802154_llsec_ops = अणु
	.get_params = mac802154_get_params,
	.set_params = mac802154_set_params,
	.add_key = mac802154_add_key,
	.del_key = mac802154_del_key,
	.add_dev = mac802154_add_dev,
	.del_dev = mac802154_del_dev,
	.add_devkey = mac802154_add_devkey,
	.del_devkey = mac802154_del_devkey,
	.add_seclevel = mac802154_add_seclevel,
	.del_seclevel = mac802154_del_seclevel,
	.lock_table = mac802154_lock_table,
	.get_table = mac802154_get_table,
	.unlock_table = mac802154_unlock_table,
पूर्ण;

काष्ठा ieee802154_mlme_ops mac802154_mlme_wpan = अणु
	.start_req = mac802154_mlme_start_req,

	.llsec = &mac802154_llsec_ops,

	.set_mac_params = mac802154_set_mac_params,
	.get_mac_params = mac802154_get_mac_params,
पूर्ण;
