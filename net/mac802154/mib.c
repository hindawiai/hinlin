<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2007-2012 Siemens AG
 *
 * Written by:
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Sergey Lapin <slapin@ossfans.org>
 * Maxim Gorbachyov <maxim.gorbachev@siemens.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#समावेश <linux/अगर_arp.h>

#समावेश <net/mac802154.h>
#समावेश <net/ieee802154_netdev.h>
#समावेश <net/cfg802154.h>

#समावेश "ieee802154_i.h"
#समावेश "driver-ops.h"

व्योम mac802154_dev_set_page_channel(काष्ठा net_device *dev, u8 page, u8 chan)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा ieee802154_local *local = sdata->local;
	पूर्णांक res;

	ASSERT_RTNL();

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	res = drv_set_channel(local, page, chan);
	अगर (res) अणु
		pr_debug("set_channel failed\n");
	पूर्ण अन्यथा अणु
		local->phy->current_channel = chan;
		local->phy->current_page = page;
	पूर्ण
पूर्ण

पूर्णांक mac802154_get_params(काष्ठा net_device *dev,
			 काष्ठा ieee802154_llsec_params *params)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_get_params(&sdata->sec, params);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_set_params(काष्ठा net_device *dev,
			 स्थिर काष्ठा ieee802154_llsec_params *params,
			 पूर्णांक changed)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_set_params(&sdata->sec, params, changed);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_add_key(काष्ठा net_device *dev,
		      स्थिर काष्ठा ieee802154_llsec_key_id *id,
		      स्थिर काष्ठा ieee802154_llsec_key *key)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_key_add(&sdata->sec, id, key);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_del_key(काष्ठा net_device *dev,
		      स्थिर काष्ठा ieee802154_llsec_key_id *id)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_key_del(&sdata->sec, id);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_add_dev(काष्ठा net_device *dev,
		      स्थिर काष्ठा ieee802154_llsec_device *llsec_dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_dev_add(&sdata->sec, llsec_dev);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_del_dev(काष्ठा net_device *dev, __le64 dev_addr)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_dev_del(&sdata->sec, dev_addr);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_add_devkey(काष्ठा net_device *dev,
			 __le64 device_addr,
			 स्थिर काष्ठा ieee802154_llsec_device_key *key)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_devkey_add(&sdata->sec, device_addr, key);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_del_devkey(काष्ठा net_device *dev,
			 __le64 device_addr,
			 स्थिर काष्ठा ieee802154_llsec_device_key *key)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_devkey_del(&sdata->sec, device_addr, key);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_add_seclevel(काष्ठा net_device *dev,
			   स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_seclevel_add(&sdata->sec, sl);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

पूर्णांक mac802154_del_seclevel(काष्ठा net_device *dev,
			   स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	पूर्णांक res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_seclevel_del(&sdata->sec, sl);
	mutex_unlock(&sdata->sec_mtx);

	वापस res;
पूर्ण

व्योम mac802154_lock_table(काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
पूर्ण

व्योम mac802154_get_table(काष्ठा net_device *dev,
			 काष्ठा ieee802154_llsec_table **t)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	*t = &sdata->sec.table;
पूर्ण

व्योम mac802154_unlock_table(काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_unlock(&sdata->sec_mtx);
पूर्ण
