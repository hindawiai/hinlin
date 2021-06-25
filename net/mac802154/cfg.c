<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Authors:
 * Alexander Aring <aar@pengutronix.de>
 *
 * Based on: net/mac80211/cfg.c
 */

#समावेश <net/rtnetlink.h>
#समावेश <net/cfg802154.h>

#समावेश "ieee802154_i.h"
#समावेश "driver-ops.h"
#समावेश "cfg.h"

अटल काष्ठा net_device *
ieee802154_add_अगरace_deprecated(काष्ठा wpan_phy *wpan_phy,
				स्थिर अक्षर *name,
				अचिन्हित अक्षर name_assign_type, पूर्णांक type)
अणु
	काष्ठा ieee802154_local *local = wpan_phy_priv(wpan_phy);
	काष्ठा net_device *dev;

	rtnl_lock();
	dev = ieee802154_अगर_add(local, name, name_assign_type, type,
				cpu_to_le64(0x0000000000000000ULL));
	rtnl_unlock();

	वापस dev;
पूर्ण

अटल व्योम ieee802154_del_अगरace_deprecated(काष्ठा wpan_phy *wpan_phy,
					    काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	ieee802154_अगर_हटाओ(sdata);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ieee802154_suspend(काष्ठा wpan_phy *wpan_phy)
अणु
	काष्ठा ieee802154_local *local = wpan_phy_priv(wpan_phy);

	अगर (!local->खोलो_count)
		जाओ suspend;

	ieee802154_stop_queue(&local->hw);
	synchronize_net();

	/* stop hardware - this must stop RX */
	ieee802154_stop_device(local);

suspend:
	local->suspended = true;
	वापस 0;
पूर्ण

अटल पूर्णांक ieee802154_resume(काष्ठा wpan_phy *wpan_phy)
अणु
	काष्ठा ieee802154_local *local = wpan_phy_priv(wpan_phy);
	पूर्णांक ret;

	/* nothing to करो अगर HW shouldn't run */
	अगर (!local->खोलो_count)
		जाओ wake_up;

	/* restart hardware */
	ret = drv_start(local);
	अगर (ret)
		वापस ret;

wake_up:
	ieee802154_wake_queue(&local->hw);
	local->suspended = false;
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ieee802154_suspend शून्य
#घोषणा ieee802154_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक
ieee802154_add_अगरace(काष्ठा wpan_phy *phy, स्थिर अक्षर *name,
		     अचिन्हित अक्षर name_assign_type,
		     क्रमागत nl802154_अगरtype type, __le64 extended_addr)
अणु
	काष्ठा ieee802154_local *local = wpan_phy_priv(phy);
	काष्ठा net_device *err;

	err = ieee802154_अगर_add(local, name, name_assign_type, type,
				extended_addr);
	वापस PTR_ERR_OR_ZERO(err);
पूर्ण

अटल पूर्णांक
ieee802154_del_अगरace(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev)
अणु
	ieee802154_अगर_हटाओ(IEEE802154_WPAN_DEV_TO_SUB_IF(wpan_dev));

	वापस 0;
पूर्ण

अटल पूर्णांक
ieee802154_set_channel(काष्ठा wpan_phy *wpan_phy, u8 page, u8 channel)
अणु
	काष्ठा ieee802154_local *local = wpan_phy_priv(wpan_phy);
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (wpan_phy->current_page == page &&
	    wpan_phy->current_channel == channel)
		वापस 0;

	ret = drv_set_channel(local, page, channel);
	अगर (!ret) अणु
		wpan_phy->current_page = page;
		wpan_phy->current_channel = channel;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
ieee802154_set_cca_mode(काष्ठा wpan_phy *wpan_phy,
			स्थिर काष्ठा wpan_phy_cca *cca)
अणु
	काष्ठा ieee802154_local *local = wpan_phy_priv(wpan_phy);
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (wpan_phy_cca_cmp(&wpan_phy->cca, cca))
		वापस 0;

	ret = drv_set_cca_mode(local, cca);
	अगर (!ret)
		wpan_phy->cca = *cca;

	वापस ret;
पूर्ण

अटल पूर्णांक
ieee802154_set_cca_ed_level(काष्ठा wpan_phy *wpan_phy, s32 ed_level)
अणु
	काष्ठा ieee802154_local *local = wpan_phy_priv(wpan_phy);
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (wpan_phy->cca_ed_level == ed_level)
		वापस 0;

	ret = drv_set_cca_ed_level(local, ed_level);
	अगर (!ret)
		wpan_phy->cca_ed_level = ed_level;

	वापस ret;
पूर्ण

अटल पूर्णांक
ieee802154_set_tx_घातer(काष्ठा wpan_phy *wpan_phy, s32 घातer)
अणु
	काष्ठा ieee802154_local *local = wpan_phy_priv(wpan_phy);
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (wpan_phy->transmit_घातer == घातer)
		वापस 0;

	ret = drv_set_tx_घातer(local, घातer);
	अगर (!ret)
		wpan_phy->transmit_घातer = घातer;

	वापस ret;
पूर्ण

अटल पूर्णांक
ieee802154_set_pan_id(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		      __le16 pan_id)
अणु
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (wpan_dev->pan_id == pan_id)
		वापस 0;

	ret = mac802154_wpan_update_llsec(wpan_dev->netdev);
	अगर (!ret)
		wpan_dev->pan_id = pan_id;

	वापस ret;
पूर्ण

अटल पूर्णांक
ieee802154_set_backoff_exponent(काष्ठा wpan_phy *wpan_phy,
				काष्ठा wpan_dev *wpan_dev,
				u8 min_be, u8 max_be)
अणु
	ASSERT_RTNL();

	wpan_dev->min_be = min_be;
	wpan_dev->max_be = max_be;
	वापस 0;
पूर्ण

अटल पूर्णांक
ieee802154_set_लघु_addr(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
			  __le16 लघु_addr)
अणु
	ASSERT_RTNL();

	wpan_dev->लघु_addr = लघु_addr;
	वापस 0;
पूर्ण

अटल पूर्णांक
ieee802154_set_max_csma_backoffs(काष्ठा wpan_phy *wpan_phy,
				 काष्ठा wpan_dev *wpan_dev,
				 u8 max_csma_backoffs)
अणु
	ASSERT_RTNL();

	wpan_dev->csma_retries = max_csma_backoffs;
	वापस 0;
पूर्ण

अटल पूर्णांक
ieee802154_set_max_frame_retries(काष्ठा wpan_phy *wpan_phy,
				 काष्ठा wpan_dev *wpan_dev,
				 s8 max_frame_retries)
अणु
	ASSERT_RTNL();

	wpan_dev->frame_retries = max_frame_retries;
	वापस 0;
पूर्ण

अटल पूर्णांक
ieee802154_set_lbt_mode(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
			bool mode)
अणु
	ASSERT_RTNL();

	wpan_dev->lbt = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक
ieee802154_set_ackreq_शेष(काष्ठा wpan_phy *wpan_phy,
			      काष्ठा wpan_dev *wpan_dev, bool ackreq)
अणु
	ASSERT_RTNL();

	wpan_dev->ackreq = ackreq;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
अटल व्योम
ieee802154_get_llsec_table(काष्ठा wpan_phy *wpan_phy,
			   काष्ठा wpan_dev *wpan_dev,
			   काष्ठा ieee802154_llsec_table **table)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	*table = &sdata->sec.table;
पूर्ण

अटल व्योम
ieee802154_lock_llsec_table(काष्ठा wpan_phy *wpan_phy,
			    काष्ठा wpan_dev *wpan_dev)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	mutex_lock(&sdata->sec_mtx);
पूर्ण

अटल व्योम
ieee802154_unlock_llsec_table(काष्ठा wpan_phy *wpan_phy,
			      काष्ठा wpan_dev *wpan_dev)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	mutex_unlock(&sdata->sec_mtx);
पूर्ण

अटल पूर्णांक
ieee802154_set_llsec_params(काष्ठा wpan_phy *wpan_phy,
			    काष्ठा wpan_dev *wpan_dev,
			    स्थिर काष्ठा ieee802154_llsec_params *params,
			    पूर्णांक changed)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_set_params(&sdata->sec, params, changed);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_get_llsec_params(काष्ठा wpan_phy *wpan_phy,
			    काष्ठा wpan_dev *wpan_dev,
			    काष्ठा ieee802154_llsec_params *params)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_get_params(&sdata->sec, params);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_add_llsec_key(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
			 स्थिर काष्ठा ieee802154_llsec_key_id *id,
			 स्थिर काष्ठा ieee802154_llsec_key *key)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_key_add(&sdata->sec, id, key);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_del_llsec_key(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
			 स्थिर काष्ठा ieee802154_llsec_key_id *id)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_key_del(&sdata->sec, id);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_add_seclevel(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
			स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_seclevel_add(&sdata->sec, sl);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_del_seclevel(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
			स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_seclevel_del(&sdata->sec, sl);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_add_device(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		      स्थिर काष्ठा ieee802154_llsec_device *dev_desc)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_dev_add(&sdata->sec, dev_desc);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_del_device(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		      __le64 extended_addr)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_dev_del(&sdata->sec, extended_addr);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_add_devkey(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		      __le64 extended_addr,
		      स्थिर काष्ठा ieee802154_llsec_device_key *key)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_devkey_add(&sdata->sec, extended_addr, key);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_del_devkey(काष्ठा wpan_phy *wpan_phy, काष्ठा wpan_dev *wpan_dev,
		      __le64 extended_addr,
		      स्थिर काष्ठा ieee802154_llsec_device_key *key)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_devkey_del(&sdata->sec, extended_addr, key);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */

स्थिर काष्ठा cfg802154_ops mac802154_config_ops = अणु
	.add_भव_पूर्णांकf_deprecated = ieee802154_add_अगरace_deprecated,
	.del_भव_पूर्णांकf_deprecated = ieee802154_del_अगरace_deprecated,
	.suspend = ieee802154_suspend,
	.resume = ieee802154_resume,
	.add_भव_पूर्णांकf = ieee802154_add_अगरace,
	.del_भव_पूर्णांकf = ieee802154_del_अगरace,
	.set_channel = ieee802154_set_channel,
	.set_cca_mode = ieee802154_set_cca_mode,
	.set_cca_ed_level = ieee802154_set_cca_ed_level,
	.set_tx_घातer = ieee802154_set_tx_घातer,
	.set_pan_id = ieee802154_set_pan_id,
	.set_लघु_addr = ieee802154_set_लघु_addr,
	.set_backoff_exponent = ieee802154_set_backoff_exponent,
	.set_max_csma_backoffs = ieee802154_set_max_csma_backoffs,
	.set_max_frame_retries = ieee802154_set_max_frame_retries,
	.set_lbt_mode = ieee802154_set_lbt_mode,
	.set_ackreq_शेष = ieee802154_set_ackreq_शेष,
#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
	.get_llsec_table = ieee802154_get_llsec_table,
	.lock_llsec_table = ieee802154_lock_llsec_table,
	.unlock_llsec_table = ieee802154_unlock_llsec_table,
	/* TODO above */
	.set_llsec_params = ieee802154_set_llsec_params,
	.get_llsec_params = ieee802154_get_llsec_params,
	.add_llsec_key = ieee802154_add_llsec_key,
	.del_llsec_key = ieee802154_del_llsec_key,
	.add_seclevel = ieee802154_add_seclevel,
	.del_seclevel = ieee802154_del_seclevel,
	.add_device = ieee802154_add_device,
	.del_device = ieee802154_del_device,
	.add_devkey = ieee802154_add_devkey,
	.del_devkey = ieee802154_del_devkey,
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */
पूर्ण;
