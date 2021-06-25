<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is the linux wireless configuration पूर्णांकerface.
 *
 * Copyright 2006-2010		Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright 2015-2017	Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/अगर.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/sched.h>
#समावेश <net/genetlink.h>
#समावेश <net/cfg80211.h>
#समावेश "nl80211.h"
#समावेश "core.h"
#समावेश "sysfs.h"
#समावेश "debugfs.h"
#समावेश "wext-compat.h"
#समावेश "rdev-ops.h"

/* name क्रम sysfs, %d is appended */
#घोषणा PHY_NAME "phy"

MODULE_AUTHOR("Johannes Berg");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("wireless configuration support");
MODULE_ALIAS_GENL_FAMILY(NL80211_GENL_NAME);

/* RCU-रक्षित (and RTNL क्रम ग_लिखोrs) */
LIST_HEAD(cfg80211_rdev_list);
पूर्णांक cfg80211_rdev_list_generation;

/* क्रम debugfs */
अटल काष्ठा dentry *ieee80211_debugfs_dir;

/* क्रम the cleanup, scan and event works */
काष्ठा workqueue_काष्ठा *cfg80211_wq;

अटल bool cfg80211_disable_40mhz_24ghz;
module_param(cfg80211_disable_40mhz_24ghz, bool, 0644);
MODULE_PARM_DESC(cfg80211_disable_40mhz_24ghz,
		 "Disable 40MHz support in the 2.4GHz band");

काष्ठा cfg80211_रेजिस्टरed_device *cfg80211_rdev_by_wiphy_idx(पूर्णांक wiphy_idx)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *result = शून्य, *rdev;

	ASSERT_RTNL();

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		अगर (rdev->wiphy_idx == wiphy_idx) अणु
			result = rdev;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक get_wiphy_idx(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	वापस rdev->wiphy_idx;
पूर्ण

काष्ठा wiphy *wiphy_idx_to_wiphy(पूर्णांक wiphy_idx)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	ASSERT_RTNL();

	rdev = cfg80211_rdev_by_wiphy_idx(wiphy_idx);
	अगर (!rdev)
		वापस शून्य;
	वापस &rdev->wiphy;
पूर्ण

अटल पूर्णांक cfg80211_dev_check_name(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   स्थिर अक्षर *newname)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev2;
	पूर्णांक wiphy_idx, taken = -1, digits;

	ASSERT_RTNL();

	अगर (म_माप(newname) > NL80211_WIPHY_NAME_MAXLEN)
		वापस -EINVAL;

	/* prohibit calling the thing phy%d when %d is not its number */
	माला_पूछो(newname, PHY_NAME "%d%n", &wiphy_idx, &taken);
	अगर (taken == म_माप(newname) && wiphy_idx != rdev->wiphy_idx) अणु
		/* count number of places needed to prपूर्णांक wiphy_idx */
		digits = 1;
		जबतक (wiphy_idx /= 10)
			digits++;
		/*
		 * deny the name अगर it is phy<idx> where <idx> is prपूर्णांकed
		 * without leading zeroes. taken == म_माप(newname) here
		 */
		अगर (taken == म_माप(PHY_NAME) + digits)
			वापस -EINVAL;
	पूर्ण

	/* Ensure another device करोes not alपढ़ोy have this name. */
	list_क्रम_each_entry(rdev2, &cfg80211_rdev_list, list)
		अगर (म_भेद(newname, wiphy_name(&rdev2->wiphy)) == 0)
			वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक cfg80211_dev_नाम(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			अक्षर *newname)
अणु
	पूर्णांक result;

	ASSERT_RTNL();

	/* Ignore nop नामs */
	अगर (म_भेद(newname, wiphy_name(&rdev->wiphy)) == 0)
		वापस 0;

	result = cfg80211_dev_check_name(rdev, newname);
	अगर (result < 0)
		वापस result;

	result = device_नाम(&rdev->wiphy.dev, newname);
	अगर (result)
		वापस result;

	अगर (!IS_ERR_OR_शून्य(rdev->wiphy.debugfsdir))
		debugfs_नाम(rdev->wiphy.debugfsdir->d_parent,
			       rdev->wiphy.debugfsdir,
			       rdev->wiphy.debugfsdir->d_parent, newname);

	nl80211_notअगरy_wiphy(rdev, NL80211_CMD_NEW_WIPHY);

	वापस 0;
पूर्ण

पूर्णांक cfg80211_चयन_netns(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net *net)
अणु
	काष्ठा wireless_dev *wdev;
	पूर्णांक err = 0;

	अगर (!(rdev->wiphy.flags & WIPHY_FLAG_NETNS_OK))
		वापस -EOPNOTSUPP;

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		अगर (!wdev->netdev)
			जारी;
		wdev->netdev->features &= ~NETIF_F_NETNS_LOCAL;
		err = dev_change_net_namespace(wdev->netdev, net, "wlan%d");
		अगर (err)
			अवरोध;
		wdev->netdev->features |= NETIF_F_NETNS_LOCAL;
	पूर्ण

	अगर (err) अणु
		/* failed -- clean up to old netns */
		net = wiphy_net(&rdev->wiphy);

		list_क्रम_each_entry_जारी_reverse(wdev,
						     &rdev->wiphy.wdev_list,
						     list) अणु
			अगर (!wdev->netdev)
				जारी;
			wdev->netdev->features &= ~NETIF_F_NETNS_LOCAL;
			err = dev_change_net_namespace(wdev->netdev, net,
							"wlan%d");
			WARN_ON(err);
			wdev->netdev->features |= NETIF_F_NETNS_LOCAL;
		पूर्ण

		वापस err;
	पूर्ण

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		अगर (!wdev->netdev)
			जारी;
		nl80211_notअगरy_अगरace(rdev, wdev, NL80211_CMD_DEL_INTERFACE);
	पूर्ण
	nl80211_notअगरy_wiphy(rdev, NL80211_CMD_DEL_WIPHY);

	wiphy_net_set(&rdev->wiphy, net);

	err = device_नाम(&rdev->wiphy.dev, dev_name(&rdev->wiphy.dev));
	WARN_ON(err);

	nl80211_notअगरy_wiphy(rdev, NL80211_CMD_NEW_WIPHY);
	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		अगर (!wdev->netdev)
			जारी;
		nl80211_notअगरy_अगरace(rdev, wdev, NL80211_CMD_NEW_INTERFACE);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cfg80211_rfसमाप्त_poll(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = data;

	rdev_rfसमाप्त_poll(rdev);
पूर्ण

व्योम cfg80211_stop_p2p_device(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा wireless_dev *wdev)
अणु
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_P2P_DEVICE))
		वापस;

	अगर (!wdev_running(wdev))
		वापस;

	rdev_stop_p2p_device(rdev, wdev);
	wdev->is_running = false;

	rdev->खोलोcount--;

	अगर (rdev->scan_req && rdev->scan_req->wdev == wdev) अणु
		अगर (WARN_ON(!rdev->scan_req->notअगरied &&
			    (!rdev->पूर्णांक_scan_req ||
			     !rdev->पूर्णांक_scan_req->notअगरied)))
			rdev->scan_req->info.पातed = true;
		___cfg80211_scan_करोne(rdev, false);
	पूर्ण
पूर्ण

व्योम cfg80211_stop_nan(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा wireless_dev *wdev)
अणु
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_न_अंक))
		वापस;

	अगर (!wdev_running(wdev))
		वापस;

	rdev_stop_nan(rdev, wdev);
	wdev->is_running = false;

	rdev->खोलोcount--;
पूर्ण

व्योम cfg80211_shutकरोwn_all_पूर्णांकerfaces(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा wireless_dev *wdev;

	ASSERT_RTNL();

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		अगर (wdev->netdev) अणु
			dev_बंद(wdev->netdev);
			जारी;
		पूर्ण

		/* otherwise, check अगरtype */

		wiphy_lock(wiphy);

		चयन (wdev->अगरtype) अणु
		हाल NL80211_IFTYPE_P2P_DEVICE:
			cfg80211_stop_p2p_device(rdev, wdev);
			अवरोध;
		हाल NL80211_IFTYPE_न_अंक:
			cfg80211_stop_nan(rdev, wdev);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		wiphy_unlock(wiphy);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cfg80211_shutकरोwn_all_पूर्णांकerfaces);

अटल पूर्णांक cfg80211_rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = data;

	अगर (!blocked)
		वापस 0;

	rtnl_lock();
	cfg80211_shutकरोwn_all_पूर्णांकerfaces(&rdev->wiphy);
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल व्योम cfg80211_rfसमाप्त_block_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	rdev = container_of(work, काष्ठा cfg80211_रेजिस्टरed_device,
			    rfसमाप्त_block);
	cfg80211_rfसमाप्त_set_block(rdev, true);
पूर्ण

अटल व्योम cfg80211_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	rdev = container_of(work, काष्ठा cfg80211_रेजिस्टरed_device,
			    event_work);

	wiphy_lock(&rdev->wiphy);
	cfg80211_process_rdev_events(rdev);
	wiphy_unlock(&rdev->wiphy);
पूर्ण

व्योम cfg80211_destroy_अगरaces(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा wireless_dev *wdev, *पंचांगp;
	bool found = false;

	ASSERT_RTNL();

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		अगर (wdev->nl_owner_dead) अणु
			अगर (wdev->netdev)
				dev_बंद(wdev->netdev);
			found = true;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस;

	wiphy_lock(&rdev->wiphy);
	list_क्रम_each_entry_safe(wdev, पंचांगp, &rdev->wiphy.wdev_list, list) अणु
		अगर (wdev->nl_owner_dead) अणु
			cfg80211_leave(rdev, wdev);
			rdev_del_भव_पूर्णांकf(rdev, wdev);
		पूर्ण
	पूर्ण
	wiphy_unlock(&rdev->wiphy);
पूर्ण

अटल व्योम cfg80211_destroy_अगरace_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	rdev = container_of(work, काष्ठा cfg80211_रेजिस्टरed_device,
			    destroy_work);

	rtnl_lock();
	cfg80211_destroy_अगरaces(rdev);
	rtnl_unlock();
पूर्ण

अटल व्योम cfg80211_sched_scan_stop_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा cfg80211_sched_scan_request *req, *पंचांगp;

	rdev = container_of(work, काष्ठा cfg80211_रेजिस्टरed_device,
			   sched_scan_stop_wk);

	rtnl_lock();
	list_क्रम_each_entry_safe(req, पंचांगp, &rdev->sched_scan_req_list, list) अणु
		अगर (req->nl_owner_dead)
			cfg80211_stop_sched_scan_req(rdev, req, false);
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल व्योम cfg80211_propagate_radar_detect_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	rdev = container_of(work, काष्ठा cfg80211_रेजिस्टरed_device,
			    propagate_radar_detect_wk);

	rtnl_lock();

	regulatory_propagate_dfs_state(&rdev->wiphy, &rdev->radar_chandef,
				       NL80211_DFS_UNAVAILABLE,
				       NL80211_RADAR_DETECTED);

	rtnl_unlock();
पूर्ण

अटल व्योम cfg80211_propagate_cac_करोne_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	rdev = container_of(work, काष्ठा cfg80211_रेजिस्टरed_device,
			    propagate_cac_करोne_wk);

	rtnl_lock();

	regulatory_propagate_dfs_state(&rdev->wiphy, &rdev->cac_करोne_chandef,
				       NL80211_DFS_AVAILABLE,
				       NL80211_RADAR_CAC_FINISHED);

	rtnl_unlock();
पूर्ण

/* exported functions */

काष्ठा wiphy *wiphy_new_nm(स्थिर काष्ठा cfg80211_ops *ops, पूर्णांक माप_priv,
			   स्थिर अक्षर *requested_name)
अणु
	अटल atomic_t wiphy_counter = ATOMIC_INIT(0);

	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	पूर्णांक alloc_size;

	WARN_ON(ops->add_key && (!ops->del_key || !ops->set_शेष_key));
	WARN_ON(ops->auth && (!ops->assoc || !ops->deauth || !ops->disassoc));
	WARN_ON(ops->connect && !ops->disconnect);
	WARN_ON(ops->join_ibss && !ops->leave_ibss);
	WARN_ON(ops->add_भव_पूर्णांकf && !ops->del_भव_पूर्णांकf);
	WARN_ON(ops->add_station && !ops->del_station);
	WARN_ON(ops->add_mpath && !ops->del_mpath);
	WARN_ON(ops->join_mesh && !ops->leave_mesh);
	WARN_ON(ops->start_p2p_device && !ops->stop_p2p_device);
	WARN_ON(ops->start_ap && !ops->stop_ap);
	WARN_ON(ops->join_ocb && !ops->leave_ocb);
	WARN_ON(ops->suspend && !ops->resume);
	WARN_ON(ops->sched_scan_start && !ops->sched_scan_stop);
	WARN_ON(ops->reमुख्य_on_channel && !ops->cancel_reमुख्य_on_channel);
	WARN_ON(ops->tdls_channel_चयन && !ops->tdls_cancel_channel_चयन);
	WARN_ON(ops->add_tx_ts && !ops->del_tx_ts);

	alloc_size = माप(*rdev) + माप_priv;

	rdev = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!rdev)
		वापस शून्य;

	rdev->ops = ops;

	rdev->wiphy_idx = atomic_inc_वापस(&wiphy_counter);

	अगर (unlikely(rdev->wiphy_idx < 0)) अणु
		/* ugh, wrapped! */
		atomic_dec(&wiphy_counter);
		kमुक्त(rdev);
		वापस शून्य;
	पूर्ण

	/* atomic_inc_वापस makes it start at 1, make it start at 0 */
	rdev->wiphy_idx--;

	/* give it a proper name */
	अगर (requested_name && requested_name[0]) अणु
		पूर्णांक rv;

		rtnl_lock();
		rv = cfg80211_dev_check_name(rdev, requested_name);

		अगर (rv < 0) अणु
			rtnl_unlock();
			जाओ use_शेष_name;
		पूर्ण

		rv = dev_set_name(&rdev->wiphy.dev, "%s", requested_name);
		rtnl_unlock();
		अगर (rv)
			जाओ use_शेष_name;
	पूर्ण अन्यथा अणु
		पूर्णांक rv;

use_शेष_name:
		/* NOTE:  This is *probably* safe w/out holding rtnl because of
		 * the restrictions on phy names.  Probably this call could
		 * fail अगर some other part of the kernel (re)named a device
		 * phyX.  But, might should add some locking and check वापस
		 * value, and use a dअगरferent name अगर this one exists?
		 */
		rv = dev_set_name(&rdev->wiphy.dev, PHY_NAME "%d", rdev->wiphy_idx);
		अगर (rv < 0) अणु
			kमुक्त(rdev);
			वापस शून्य;
		पूर्ण
	पूर्ण

	mutex_init(&rdev->wiphy.mtx);
	INIT_LIST_HEAD(&rdev->wiphy.wdev_list);
	INIT_LIST_HEAD(&rdev->beacon_registrations);
	spin_lock_init(&rdev->beacon_registrations_lock);
	spin_lock_init(&rdev->bss_lock);
	INIT_LIST_HEAD(&rdev->bss_list);
	INIT_LIST_HEAD(&rdev->sched_scan_req_list);
	INIT_WORK(&rdev->scan_करोne_wk, __cfg80211_scan_करोne);
	INIT_DELAYED_WORK(&rdev->dfs_update_channels_wk,
			  cfg80211_dfs_channels_update_work);
#अगर_घोषित CONFIG_CFG80211_WEXT
	rdev->wiphy.wext = &cfg80211_wext_handler;
#पूर्ण_अगर

	device_initialize(&rdev->wiphy.dev);
	rdev->wiphy.dev.class = &ieee80211_class;
	rdev->wiphy.dev.platक्रमm_data = rdev;
	device_enable_async_suspend(&rdev->wiphy.dev);

	INIT_WORK(&rdev->destroy_work, cfg80211_destroy_अगरace_wk);
	INIT_WORK(&rdev->sched_scan_stop_wk, cfg80211_sched_scan_stop_wk);
	INIT_WORK(&rdev->sched_scan_res_wk, cfg80211_sched_scan_results_wk);
	INIT_WORK(&rdev->propagate_radar_detect_wk,
		  cfg80211_propagate_radar_detect_wk);
	INIT_WORK(&rdev->propagate_cac_करोne_wk, cfg80211_propagate_cac_करोne_wk);
	INIT_WORK(&rdev->mgmt_registrations_update_wk,
		  cfg80211_mgmt_registrations_update_wk);

#अगर_घोषित CONFIG_CFG80211_DEFAULT_PS
	rdev->wiphy.flags |= WIPHY_FLAG_PS_ON_BY_DEFAULT;
#पूर्ण_अगर

	wiphy_net_set(&rdev->wiphy, &init_net);

	rdev->rfसमाप्त_ops.set_block = cfg80211_rfसमाप्त_set_block;
	rdev->rfसमाप्त = rfसमाप्त_alloc(dev_name(&rdev->wiphy.dev),
				   &rdev->wiphy.dev, RFKILL_TYPE_WLAN,
				   &rdev->rfसमाप्त_ops, rdev);

	अगर (!rdev->rfसमाप्त) अणु
		wiphy_मुक्त(&rdev->wiphy);
		वापस शून्य;
	पूर्ण

	INIT_WORK(&rdev->rfसमाप्त_block, cfg80211_rfसमाप्त_block_work);
	INIT_WORK(&rdev->conn_work, cfg80211_conn_work);
	INIT_WORK(&rdev->event_work, cfg80211_event_work);

	init_रुकोqueue_head(&rdev->dev_रुको);

	/*
	 * Initialize wiphy parameters to IEEE 802.11 MIB शेष values.
	 * Fragmentation and RTS threshold are disabled by शेष with the
	 * special -1 value.
	 */
	rdev->wiphy.retry_लघु = 7;
	rdev->wiphy.retry_दीर्घ = 4;
	rdev->wiphy.frag_threshold = (u32) -1;
	rdev->wiphy.rts_threshold = (u32) -1;
	rdev->wiphy.coverage_class = 0;

	rdev->wiphy.max_num_csa_counters = 1;

	rdev->wiphy.max_sched_scan_plans = 1;
	rdev->wiphy.max_sched_scan_plan_पूर्णांकerval = U32_MAX;

	वापस &rdev->wiphy;
पूर्ण
EXPORT_SYMBOL(wiphy_new_nm);

अटल पूर्णांक wiphy_verअगरy_combinations(काष्ठा wiphy *wiphy)
अणु
	स्थिर काष्ठा ieee80211_अगरace_combination *c;
	पूर्णांक i, j;

	क्रम (i = 0; i < wiphy->n_अगरace_combinations; i++) अणु
		u32 cnt = 0;
		u16 all_अगरtypes = 0;

		c = &wiphy->अगरace_combinations[i];

		/*
		 * Combinations with just one पूर्णांकerface aren't real,
		 * however we make an exception क्रम DFS.
		 */
		अगर (WARN_ON((c->max_पूर्णांकerfaces < 2) && !c->radar_detect_widths))
			वापस -EINVAL;

		/* Need at least one channel */
		अगर (WARN_ON(!c->num_dअगरferent_channels))
			वापस -EINVAL;

		/*
		 * Put a sane limit on maximum number of dअगरferent
		 * channels to simplअगरy channel accounting code.
		 */
		अगर (WARN_ON(c->num_dअगरferent_channels >
				CFG80211_MAX_NUM_DIFFERENT_CHANNELS))
			वापस -EINVAL;

		/* DFS only works on one channel. */
		अगर (WARN_ON(c->radar_detect_widths &&
			    (c->num_dअगरferent_channels > 1)))
			वापस -EINVAL;

		अगर (WARN_ON(!c->n_limits))
			वापस -EINVAL;

		क्रम (j = 0; j < c->n_limits; j++) अणु
			u16 types = c->limits[j].types;

			/* पूर्णांकerface types shouldn't overlap */
			अगर (WARN_ON(types & all_अगरtypes))
				वापस -EINVAL;
			all_अगरtypes |= types;

			अगर (WARN_ON(!c->limits[j].max))
				वापस -EINVAL;

			/* Shouldn't list software अगरtypes in combinations! */
			अगर (WARN_ON(wiphy->software_अगरtypes & types))
				वापस -EINVAL;

			/* Only a single P2P_DEVICE can be allowed */
			अगर (WARN_ON(types & BIT(NL80211_IFTYPE_P2P_DEVICE) &&
				    c->limits[j].max > 1))
				वापस -EINVAL;

			/* Only a single न_अंक can be allowed */
			अगर (WARN_ON(types & BIT(NL80211_IFTYPE_न_अंक) &&
				    c->limits[j].max > 1))
				वापस -EINVAL;

			/*
			 * This isn't well-defined right now. If you have an
			 * IBSS पूर्णांकerface, then its beacon पूर्णांकerval may change
			 * by joining other networks, and nothing prevents it
			 * from करोing that.
			 * So technically we probably shouldn't even allow AP
			 * and IBSS in the same पूर्णांकerface, but it seems that
			 * some drivers support that, possibly only with fixed
			 * beacon पूर्णांकervals क्रम IBSS.
			 */
			अगर (WARN_ON(types & BIT(NL80211_IFTYPE_ADHOC) &&
				    c->beacon_पूर्णांक_min_gcd)) अणु
				वापस -EINVAL;
			पूर्ण

			cnt += c->limits[j].max;
			/*
			 * Don't advertise an unsupported type
			 * in a combination.
			 */
			अगर (WARN_ON((wiphy->पूर्णांकerface_modes & types) != types))
				वापस -EINVAL;
		पूर्ण

		अगर (WARN_ON(all_अगरtypes & BIT(NL80211_IFTYPE_WDS)))
			वापस -EINVAL;

		/* You can't even choose that many! */
		अगर (WARN_ON(cnt < c->max_पूर्णांकerfaces))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wiphy_रेजिस्टर(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	पूर्णांक res;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;
	bool have_band = false;
	पूर्णांक i;
	u16 अगरmodes = wiphy->पूर्णांकerface_modes;

#अगर_घोषित CONFIG_PM
	अगर (WARN_ON(wiphy->wowlan &&
		    (wiphy->wowlan->flags & WIPHY_WOWLAN_GTK_REKEY_FAILURE) &&
		    !(wiphy->wowlan->flags & WIPHY_WOWLAN_SUPPORTS_GTK_REKEY)))
		वापस -EINVAL;
	अगर (WARN_ON(wiphy->wowlan &&
		    !wiphy->wowlan->flags && !wiphy->wowlan->n_patterns &&
		    !wiphy->wowlan->tcp))
		वापस -EINVAL;
#पूर्ण_अगर
	अगर (WARN_ON((wiphy->features & NL80211_FEATURE_TDLS_CHANNEL_SWITCH) &&
		    (!rdev->ops->tdls_channel_चयन ||
		     !rdev->ops->tdls_cancel_channel_चयन)))
		वापस -EINVAL;

	अगर (WARN_ON((wiphy->पूर्णांकerface_modes & BIT(NL80211_IFTYPE_न_अंक)) &&
		    (!rdev->ops->start_nan || !rdev->ops->stop_nan ||
		     !rdev->ops->add_nan_func || !rdev->ops->del_nan_func ||
		     !(wiphy->nan_supported_bands & BIT(NL80211_BAND_2GHZ)))))
		वापस -EINVAL;

	अगर (WARN_ON(wiphy->पूर्णांकerface_modes & BIT(NL80211_IFTYPE_WDS)))
		वापस -EINVAL;

	अगर (WARN_ON(wiphy->pmsr_capa && !wiphy->pmsr_capa->fपंचांग.supported))
		वापस -EINVAL;

	अगर (wiphy->pmsr_capa && wiphy->pmsr_capa->fपंचांग.supported) अणु
		अगर (WARN_ON(!wiphy->pmsr_capa->fपंचांग.asap &&
			    !wiphy->pmsr_capa->fपंचांग.non_asap))
			वापस -EINVAL;
		अगर (WARN_ON(!wiphy->pmsr_capa->fपंचांग.preambles ||
			    !wiphy->pmsr_capa->fपंचांग.bandwidths))
			वापस -EINVAL;
		अगर (WARN_ON(wiphy->pmsr_capa->fपंचांग.preambles &
				~(BIT(NL80211_PREAMBLE_LEGACY) |
				  BIT(NL80211_PREAMBLE_HT) |
				  BIT(NL80211_PREAMBLE_VHT) |
				  BIT(NL80211_PREAMBLE_HE) |
				  BIT(NL80211_PREAMBLE_DMG))))
			वापस -EINVAL;
		अगर (WARN_ON((wiphy->pmsr_capa->fपंचांग.trigger_based ||
			     wiphy->pmsr_capa->fपंचांग.non_trigger_based) &&
			    !(wiphy->pmsr_capa->fपंचांग.preambles &
			      BIT(NL80211_PREAMBLE_HE))))
			वापस -EINVAL;
		अगर (WARN_ON(wiphy->pmsr_capa->fपंचांग.bandwidths &
				~(BIT(NL80211_CHAN_WIDTH_20_NOHT) |
				  BIT(NL80211_CHAN_WIDTH_20) |
				  BIT(NL80211_CHAN_WIDTH_40) |
				  BIT(NL80211_CHAN_WIDTH_80) |
				  BIT(NL80211_CHAN_WIDTH_80P80) |
				  BIT(NL80211_CHAN_WIDTH_160) |
				  BIT(NL80211_CHAN_WIDTH_5) |
				  BIT(NL80211_CHAN_WIDTH_10))))
			वापस -EINVAL;
	पूर्ण

	/*
	 * अगर a wiphy has unsupported modes क्रम regulatory channel enक्रमcement,
	 * opt-out of enक्रमcement checking
	 */
	अगर (wiphy->पूर्णांकerface_modes & ~(BIT(NL80211_IFTYPE_STATION) |
				       BIT(NL80211_IFTYPE_P2P_CLIENT) |
				       BIT(NL80211_IFTYPE_AP) |
				       BIT(NL80211_IFTYPE_P2P_GO) |
				       BIT(NL80211_IFTYPE_ADHOC) |
				       BIT(NL80211_IFTYPE_P2P_DEVICE) |
				       BIT(NL80211_IFTYPE_न_अंक) |
				       BIT(NL80211_IFTYPE_AP_VLAN) |
				       BIT(NL80211_IFTYPE_MONITOR)))
		wiphy->regulatory_flags |= REGULATORY_IGNORE_STALE_KICKOFF;

	अगर (WARN_ON((wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED) &&
		    (wiphy->regulatory_flags &
					(REGULATORY_CUSTOM_REG |
					 REGULATORY_STRICT_REG |
					 REGULATORY_COUNTRY_IE_FOLLOW_POWER |
					 REGULATORY_COUNTRY_IE_IGNORE))))
		वापस -EINVAL;

	अगर (WARN_ON(wiphy->coalesce &&
		    (!wiphy->coalesce->n_rules ||
		     !wiphy->coalesce->n_patterns) &&
		    (!wiphy->coalesce->pattern_min_len ||
		     wiphy->coalesce->pattern_min_len >
			wiphy->coalesce->pattern_max_len)))
		वापस -EINVAL;

	अगर (WARN_ON(wiphy->ap_sme_capa &&
		    !(wiphy->flags & WIPHY_FLAG_HAVE_AP_SME)))
		वापस -EINVAL;

	अगर (WARN_ON(wiphy->addresses && !wiphy->n_addresses))
		वापस -EINVAL;

	अगर (WARN_ON(wiphy->addresses &&
		    !is_zero_ether_addr(wiphy->perm_addr) &&
		    स_भेद(wiphy->perm_addr, wiphy->addresses[0].addr,
			   ETH_ALEN)))
		वापस -EINVAL;

	अगर (WARN_ON(wiphy->max_acl_mac_addrs &&
		    (!(wiphy->flags & WIPHY_FLAG_HAVE_AP_SME) ||
		     !rdev->ops->set_mac_acl)))
		वापस -EINVAL;

	/* assure only valid behaviours are flagged by driver
	 * hence subtract 2 as bit 0 is invalid.
	 */
	अगर (WARN_ON(wiphy->bss_select_support &&
		    (wiphy->bss_select_support & ~(BIT(__NL80211_BSS_SELECT_ATTR_AFTER_LAST) - 2))))
		वापस -EINVAL;

	अगर (WARN_ON(wiphy_ext_feature_isset(&rdev->wiphy,
					    NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X) &&
		    (!rdev->ops->set_pmk || !rdev->ops->del_pmk)))
		वापस -EINVAL;

	अगर (WARN_ON(!(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_FW_ROAM) &&
		    rdev->ops->update_connect_params))
		वापस -EINVAL;

	अगर (wiphy->addresses)
		स_नकल(wiphy->perm_addr, wiphy->addresses[0].addr, ETH_ALEN);

	/* sanity check अगरmodes */
	WARN_ON(!अगरmodes);
	अगरmodes &= ((1 << NUM_NL80211_IFTYPES) - 1) & ~1;
	अगर (WARN_ON(अगरmodes != wiphy->पूर्णांकerface_modes))
		wiphy->पूर्णांकerface_modes = अगरmodes;

	res = wiphy_verअगरy_combinations(wiphy);
	अगर (res)
		वापस res;

	/* sanity check supported bands/channels */
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		u16 types = 0;
		bool have_he = false;

		sband = wiphy->bands[band];
		अगर (!sband)
			जारी;

		sband->band = band;
		अगर (WARN_ON(!sband->n_channels))
			वापस -EINVAL;
		/*
		 * on 60GHz or sub-1Ghz band, there are no legacy rates, so
		 * n_bitrates is 0
		 */
		अगर (WARN_ON((band != NL80211_BAND_60GHZ &&
			     band != NL80211_BAND_S1GHZ) &&
			    !sband->n_bitrates))
			वापस -EINVAL;

		अगर (WARN_ON(band == NL80211_BAND_6GHZ &&
			    (sband->ht_cap.ht_supported ||
			     sband->vht_cap.vht_supported)))
			वापस -EINVAL;

		/*
		 * Since cfg80211_disable_40mhz_24ghz is global, we can
		 * modअगरy the sband's ht data even अगर the driver uses a
		 * global काष्ठाure क्रम that.
		 */
		अगर (cfg80211_disable_40mhz_24ghz &&
		    band == NL80211_BAND_2GHZ &&
		    sband->ht_cap.ht_supported) अणु
			sband->ht_cap.cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			sband->ht_cap.cap &= ~IEEE80211_HT_CAP_SGI_40;
		पूर्ण

		/*
		 * Since we use a u32 क्रम rate biपंचांगaps in
		 * ieee80211_get_response_rate, we cannot
		 * have more than 32 legacy rates.
		 */
		अगर (WARN_ON(sband->n_bitrates > 32))
			वापस -EINVAL;

		क्रम (i = 0; i < sband->n_channels; i++) अणु
			sband->channels[i].orig_flags =
				sband->channels[i].flags;
			sband->channels[i].orig_mag = पूर्णांक_उच्च;
			sband->channels[i].orig_mpwr =
				sband->channels[i].max_घातer;
			sband->channels[i].band = band;

			अगर (WARN_ON(sband->channels[i].freq_offset >= 1000))
				वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < sband->n_अगरtype_data; i++) अणु
			स्थिर काष्ठा ieee80211_sband_अगरtype_data *अगरtd;

			अगरtd = &sband->अगरtype_data[i];

			अगर (WARN_ON(!अगरtd->types_mask))
				वापस -EINVAL;
			अगर (WARN_ON(types & अगरtd->types_mask))
				वापस -EINVAL;

			/* at least one piece of inक्रमmation must be present */
			अगर (WARN_ON(!अगरtd->he_cap.has_he))
				वापस -EINVAL;

			types |= अगरtd->types_mask;

			अगर (i == 0)
				have_he = अगरtd->he_cap.has_he;
			अन्यथा
				have_he = have_he &&
					  अगरtd->he_cap.has_he;
		पूर्ण

		अगर (WARN_ON(!have_he && band == NL80211_BAND_6GHZ))
			वापस -EINVAL;

		have_band = true;
	पूर्ण

	अगर (!have_band) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < rdev->wiphy.n_venकरोr_commands; i++) अणु
		/*
		 * Validate we have a policy (can be explicitly set to
		 * VENDOR_CMD_RAW_DATA which is non-शून्य) and also that
		 * we have at least one of करोit/dumpit.
		 */
		अगर (WARN_ON(!rdev->wiphy.venकरोr_commands[i].policy))
			वापस -EINVAL;
		अगर (WARN_ON(!rdev->wiphy.venकरोr_commands[i].करोit &&
			    !rdev->wiphy.venकरोr_commands[i].dumpit))
			वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_PM
	अगर (WARN_ON(rdev->wiphy.wowlan && rdev->wiphy.wowlan->n_patterns &&
		    (!rdev->wiphy.wowlan->pattern_min_len ||
		     rdev->wiphy.wowlan->pattern_min_len >
				rdev->wiphy.wowlan->pattern_max_len)))
		वापस -EINVAL;
#पूर्ण_अगर

	/* check and set up bitrates */
	ieee80211_set_bitrate_flags(wiphy);

	rdev->wiphy.features |= NL80211_FEATURE_SCAN_FLUSH;

	rtnl_lock();
	res = device_add(&rdev->wiphy.dev);
	अगर (res) अणु
		rtnl_unlock();
		वापस res;
	पूर्ण

	/* set up regulatory info */
	wiphy_regulatory_रेजिस्टर(wiphy);

	list_add_rcu(&rdev->list, &cfg80211_rdev_list);
	cfg80211_rdev_list_generation++;

	/* add to debugfs */
	rdev->wiphy.debugfsdir = debugfs_create_dir(wiphy_name(&rdev->wiphy),
						    ieee80211_debugfs_dir);

	cfg80211_debugfs_rdev_add(rdev);
	nl80211_notअगरy_wiphy(rdev, NL80211_CMD_NEW_WIPHY);

	अगर (wiphy->regulatory_flags & REGULATORY_CUSTOM_REG) अणु
		काष्ठा regulatory_request request;

		request.wiphy_idx = get_wiphy_idx(wiphy);
		request.initiator = NL80211_REGDOM_SET_BY_DRIVER;
		request.alpha2[0] = '9';
		request.alpha2[1] = '9';

		nl80211_send_reg_change_event(&request);
	पूर्ण

	/* Check that nobody globally advertises any capabilities they करो not
	 * advertise on all possible पूर्णांकerface types.
	 */
	अगर (wiphy->extended_capabilities_len &&
	    wiphy->num_अगरtype_ext_capab &&
	    wiphy->अगरtype_ext_capab) अणु
		u8 supported_on_all, j;
		स्थिर काष्ठा wiphy_अगरtype_ext_capab *capab;

		capab = wiphy->अगरtype_ext_capab;
		क्रम (j = 0; j < wiphy->extended_capabilities_len; j++) अणु
			अगर (capab[0].extended_capabilities_len > j)
				supported_on_all =
					capab[0].extended_capabilities[j];
			अन्यथा
				supported_on_all = 0x00;
			क्रम (i = 1; i < wiphy->num_अगरtype_ext_capab; i++) अणु
				अगर (j >= capab[i].extended_capabilities_len) अणु
					supported_on_all = 0x00;
					अवरोध;
				पूर्ण
				supported_on_all &=
					capab[i].extended_capabilities[j];
			पूर्ण
			अगर (WARN_ON(wiphy->extended_capabilities[j] &
				    ~supported_on_all))
				अवरोध;
		पूर्ण
	पूर्ण

	rdev->wiphy.रेजिस्टरed = true;
	rtnl_unlock();

	res = rfसमाप्त_रेजिस्टर(rdev->rfसमाप्त);
	अगर (res) अणु
		rfसमाप्त_destroy(rdev->rfसमाप्त);
		rdev->rfसमाप्त = शून्य;
		wiphy_unरेजिस्टर(&rdev->wiphy);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(wiphy_रेजिस्टर);

व्योम wiphy_rfसमाप्त_start_polling(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	अगर (!rdev->ops->rfसमाप्त_poll)
		वापस;
	rdev->rfसमाप्त_ops.poll = cfg80211_rfसमाप्त_poll;
	rfसमाप्त_resume_polling(rdev->rfसमाप्त);
पूर्ण
EXPORT_SYMBOL(wiphy_rfसमाप्त_start_polling);

व्योम wiphy_rfसमाप्त_stop_polling(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	rfसमाप्त_छोड़ो_polling(rdev->rfसमाप्त);
पूर्ण
EXPORT_SYMBOL(wiphy_rfसमाप्त_stop_polling);

व्योम wiphy_unरेजिस्टर(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	रुको_event(rdev->dev_रुको, (अणु
		पूर्णांक __count;
		wiphy_lock(&rdev->wiphy);
		__count = rdev->खोलोcount;
		wiphy_unlock(&rdev->wiphy);
		__count == 0; पूर्ण));

	अगर (rdev->rfसमाप्त)
		rfसमाप्त_unरेजिस्टर(rdev->rfसमाप्त);

	rtnl_lock();
	wiphy_lock(&rdev->wiphy);
	nl80211_notअगरy_wiphy(rdev, NL80211_CMD_DEL_WIPHY);
	rdev->wiphy.रेजिस्टरed = false;

	WARN_ON(!list_empty(&rdev->wiphy.wdev_list));

	/*
	 * First हटाओ the hardware from everywhere, this makes
	 * it impossible to find from userspace.
	 */
	debugfs_हटाओ_recursive(rdev->wiphy.debugfsdir);
	list_del_rcu(&rdev->list);
	synchronize_rcu();

	/*
	 * If this device got a regulatory hपूर्णांक tell core its
	 * मुक्त to listen now to a new shiny device regulatory hपूर्णांक
	 */
	wiphy_regulatory_deरेजिस्टर(wiphy);

	cfg80211_rdev_list_generation++;
	device_del(&rdev->wiphy.dev);

	wiphy_unlock(&rdev->wiphy);
	rtnl_unlock();

	flush_work(&rdev->scan_करोne_wk);
	cancel_work_sync(&rdev->conn_work);
	flush_work(&rdev->event_work);
	cancel_delayed_work_sync(&rdev->dfs_update_channels_wk);
	flush_work(&rdev->destroy_work);
	flush_work(&rdev->sched_scan_stop_wk);
	flush_work(&rdev->propagate_radar_detect_wk);
	flush_work(&rdev->propagate_cac_करोne_wk);
	flush_work(&rdev->mgmt_registrations_update_wk);

#अगर_घोषित CONFIG_PM
	अगर (rdev->wiphy.wowlan_config && rdev->ops->set_wakeup)
		rdev_set_wakeup(rdev, false);
#पूर्ण_अगर
	cfg80211_rdev_मुक्त_wowlan(rdev);
	cfg80211_rdev_मुक्त_coalesce(rdev);
पूर्ण
EXPORT_SYMBOL(wiphy_unरेजिस्टर);

व्योम cfg80211_dev_मुक्त(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा cfg80211_पूर्णांकernal_bss *scan, *पंचांगp;
	काष्ठा cfg80211_beacon_registration *reg, *treg;
	rfसमाप्त_destroy(rdev->rfसमाप्त);
	list_क्रम_each_entry_safe(reg, treg, &rdev->beacon_registrations, list) अणु
		list_del(&reg->list);
		kमुक्त(reg);
	पूर्ण
	list_क्रम_each_entry_safe(scan, पंचांगp, &rdev->bss_list, list)
		cfg80211_put_bss(&rdev->wiphy, &scan->pub);
	mutex_destroy(&rdev->wiphy.mtx);
	kमुक्त(rdev);
पूर्ण

व्योम wiphy_मुक्त(काष्ठा wiphy *wiphy)
अणु
	put_device(&wiphy->dev);
पूर्ण
EXPORT_SYMBOL(wiphy_मुक्त);

व्योम wiphy_rfसमाप्त_set_hw_state_reason(काष्ठा wiphy *wiphy, bool blocked,
				      क्रमागत rfसमाप्त_hard_block_reasons reason)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	अगर (rfसमाप्त_set_hw_state_reason(rdev->rfसमाप्त, blocked, reason))
		schedule_work(&rdev->rfसमाप्त_block);
पूर्ण
EXPORT_SYMBOL(wiphy_rfसमाप्त_set_hw_state_reason);

व्योम cfg80211_cqm_config_मुक्त(काष्ठा wireless_dev *wdev)
अणु
	kमुक्त(wdev->cqm_config);
	wdev->cqm_config = शून्य;
पूर्ण

अटल व्योम _cfg80211_unरेजिस्टर_wdev(काष्ठा wireless_dev *wdev,
				      bool unरेजिस्टर_netdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	ASSERT_RTNL();
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	flush_work(&wdev->pmsr_मुक्त_wk);

	nl80211_notअगरy_अगरace(rdev, wdev, NL80211_CMD_DEL_INTERFACE);

	wdev->रेजिस्टरed = false;

	अगर (wdev->netdev) अणु
		sysfs_हटाओ_link(&wdev->netdev->dev.kobj, "phy80211");
		अगर (unरेजिस्टर_netdev)
			unरेजिस्टर_netdevice(wdev->netdev);
	पूर्ण

	list_del_rcu(&wdev->list);
	synchronize_net();
	rdev->devlist_generation++;

	cfg80211_mlme_purge_registrations(wdev);

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_P2P_DEVICE:
		cfg80211_stop_p2p_device(rdev, wdev);
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
		cfg80211_stop_nan(rdev, wdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_CFG80211_WEXT
	kमुक्त_sensitive(wdev->wext.keys);
	wdev->wext.keys = शून्य;
#पूर्ण_अगर
	/* only initialized अगर we have a netdev */
	अगर (wdev->netdev)
		flush_work(&wdev->disconnect_wk);

	cfg80211_cqm_config_मुक्त(wdev);

	/*
	 * Ensure that all events have been processed and
	 * मुक्तd.
	 */
	cfg80211_process_wdev_events(wdev);

	अगर (WARN_ON(wdev->current_bss)) अणु
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
		wdev->current_bss = शून्य;
	पूर्ण
पूर्ण

व्योम cfg80211_unरेजिस्टर_wdev(काष्ठा wireless_dev *wdev)
अणु
	_cfg80211_unरेजिस्टर_wdev(wdev, true);
पूर्ण
EXPORT_SYMBOL(cfg80211_unरेजिस्टर_wdev);

अटल स्थिर काष्ठा device_type wiphy_type = अणु
	.name	= "wlan",
पूर्ण;

व्योम cfg80211_update_अगरace_num(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       क्रमागत nl80211_अगरtype अगरtype, पूर्णांक num)
अणु
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	rdev->num_running_अगरaces += num;
	अगर (अगरtype == NL80211_IFTYPE_MONITOR)
		rdev->num_running_monitor_अगरaces += num;
पूर्ण

व्योम __cfg80211_leave(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा wireless_dev *wdev)
अणु
	काष्ठा net_device *dev = wdev->netdev;
	काष्ठा cfg80211_sched_scan_request *pos, *पंचांगp;

	lockdep_निश्चित_held(&rdev->wiphy.mtx);
	ASSERT_WDEV_LOCK(wdev);

	cfg80211_pmsr_wdev_करोwn(wdev);

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
		__cfg80211_leave_ibss(rdev, dev, true);
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_STATION:
		list_क्रम_each_entry_safe(pos, पंचांगp, &rdev->sched_scan_req_list,
					 list) अणु
			अगर (dev == pos->dev)
				cfg80211_stop_sched_scan_req(rdev, pos, false);
		पूर्ण

#अगर_घोषित CONFIG_CFG80211_WEXT
		kमुक्त(wdev->wext.ie);
		wdev->wext.ie = शून्य;
		wdev->wext.ie_len = 0;
		wdev->wext.connect.auth_type = NL80211_AUTHTYPE_AUTOMATIC;
#पूर्ण_अगर
		cfg80211_disconnect(rdev, dev,
				    WLAN_REASON_DEAUTH_LEAVING, true);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		__cfg80211_leave_mesh(rdev, dev);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		__cfg80211_stop_ap(rdev, dev, true);
		अवरोध;
	हाल NL80211_IFTYPE_OCB:
		__cfg80211_leave_ocb(rdev, dev);
		अवरोध;
	हाल NL80211_IFTYPE_P2P_DEVICE:
	हाल NL80211_IFTYPE_न_अंक:
		/* cannot happen, has no netdev */
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_MONITOR:
		/* nothing to करो */
		अवरोध;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_WDS:
	हाल NUM_NL80211_IFTYPES:
		/* invalid */
		अवरोध;
	पूर्ण
पूर्ण

व्योम cfg80211_leave(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		    काष्ठा wireless_dev *wdev)
अणु
	wdev_lock(wdev);
	__cfg80211_leave(rdev, wdev);
	wdev_unlock(wdev);
पूर्ण

व्योम cfg80211_stop_अगरace(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			 gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_event *ev;
	अचिन्हित दीर्घ flags;

	trace_cfg80211_stop_अगरace(wiphy, wdev);

	ev = kzalloc(माप(*ev), gfp);
	अगर (!ev)
		वापस;

	ev->type = EVENT_STOPPED;

	spin_lock_irqsave(&wdev->event_lock, flags);
	list_add_tail(&ev->list, &wdev->event_list);
	spin_unlock_irqrestore(&wdev->event_lock, flags);
	queue_work(cfg80211_wq, &rdev->event_work);
पूर्ण
EXPORT_SYMBOL(cfg80211_stop_अगरace);

व्योम cfg80211_init_wdev(काष्ठा wireless_dev *wdev)
अणु
	mutex_init(&wdev->mtx);
	INIT_LIST_HEAD(&wdev->event_list);
	spin_lock_init(&wdev->event_lock);
	INIT_LIST_HEAD(&wdev->mgmt_registrations);
	spin_lock_init(&wdev->mgmt_registrations_lock);
	INIT_LIST_HEAD(&wdev->pmsr_list);
	spin_lock_init(&wdev->pmsr_lock);
	INIT_WORK(&wdev->pmsr_मुक्त_wk, cfg80211_pmsr_मुक्त_wk);

#अगर_घोषित CONFIG_CFG80211_WEXT
	wdev->wext.शेष_key = -1;
	wdev->wext.शेष_mgmt_key = -1;
	wdev->wext.connect.auth_type = NL80211_AUTHTYPE_AUTOMATIC;
#पूर्ण_अगर

	अगर (wdev->wiphy->flags & WIPHY_FLAG_PS_ON_BY_DEFAULT)
		wdev->ps = true;
	अन्यथा
		wdev->ps = false;
	/* allow mac80211 to determine the समयout */
	wdev->ps_समयout = -1;

	अगर ((wdev->अगरtype == NL80211_IFTYPE_STATION ||
	     wdev->अगरtype == NL80211_IFTYPE_P2P_CLIENT ||
	     wdev->अगरtype == NL80211_IFTYPE_ADHOC) && !wdev->use_4addr)
		wdev->netdev->priv_flags |= IFF_DONT_BRIDGE;

	INIT_WORK(&wdev->disconnect_wk, cfg80211_स्वतःdisconnect_wk);
पूर्ण

व्योम cfg80211_रेजिस्टर_wdev(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा wireless_dev *wdev)
अणु
	ASSERT_RTNL();
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	/*
	 * We get here also when the पूर्णांकerface changes network namespaces,
	 * as it's registered into the new one, but we don't want it to
	 * change ID in that हाल. Checking अगर the ID is alपढ़ोy asचिन्हित
	 * works, because 0 isn't considered a valid ID and the memory is
	 * 0-initialized.
	 */
	अगर (!wdev->identअगरier)
		wdev->identअगरier = ++rdev->wdev_id;
	list_add_rcu(&wdev->list, &rdev->wiphy.wdev_list);
	rdev->devlist_generation++;
	wdev->रेजिस्टरed = true;

	अगर (wdev->netdev &&
	    sysfs_create_link(&wdev->netdev->dev.kobj, &rdev->wiphy.dev.kobj,
			      "phy80211"))
		pr_err("failed to add phy80211 symlink to netdev!\n");

	nl80211_notअगरy_अगरace(rdev, wdev, NL80211_CMD_NEW_INTERFACE);
पूर्ण

पूर्णांक cfg80211_रेजिस्टर_netdevice(काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (WARN_ON(!wdev))
		वापस -EINVAL;

	rdev = wiphy_to_rdev(wdev->wiphy);

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	/* we'll take care of this */
	wdev->रेजिस्टरed = true;
	wdev->रेजिस्टरing = true;
	ret = रेजिस्टर_netdevice(dev);
	अगर (ret)
		जाओ out;

	cfg80211_रेजिस्टर_wdev(rdev, wdev);
	ret = 0;
out:
	wdev->रेजिस्टरing = false;
	अगर (ret)
		wdev->रेजिस्टरed = false;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cfg80211_रेजिस्टर_netdevice);

अटल पूर्णांक cfg80211_netdev_notअगरier_call(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ state, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा cfg80211_sched_scan_request *pos, *पंचांगp;

	अगर (!wdev)
		वापस NOTIFY_DONE;

	rdev = wiphy_to_rdev(wdev->wiphy);

	WARN_ON(wdev->अगरtype == NL80211_IFTYPE_UNSPECIFIED);

	चयन (state) अणु
	हाल NETDEV_POST_INIT:
		SET_NETDEV_DEVTYPE(dev, &wiphy_type);
		wdev->netdev = dev;
		/* can only change netns with wiphy */
		dev->features |= NETIF_F_NETNS_LOCAL;

		cfg80211_init_wdev(wdev);
		अवरोध;
	हाल NETDEV_REGISTER:
		अगर (!wdev->रेजिस्टरed) अणु
			wiphy_lock(&rdev->wiphy);
			cfg80211_रेजिस्टर_wdev(rdev, wdev);
			wiphy_unlock(&rdev->wiphy);
		पूर्ण
		अवरोध;
	हाल NETDEV_UNREGISTER:
		/*
		 * It is possible to get NETDEV_UNREGISTER multiple बार,
		 * so check wdev->रेजिस्टरed.
		 */
		अगर (wdev->रेजिस्टरed && !wdev->रेजिस्टरing) अणु
			wiphy_lock(&rdev->wiphy);
			_cfg80211_unरेजिस्टर_wdev(wdev, false);
			wiphy_unlock(&rdev->wiphy);
		पूर्ण
		अवरोध;
	हाल NETDEV_GOING_DOWN:
		wiphy_lock(&rdev->wiphy);
		cfg80211_leave(rdev, wdev);
		wiphy_unlock(&rdev->wiphy);
		अवरोध;
	हाल NETDEV_DOWN:
		wiphy_lock(&rdev->wiphy);
		cfg80211_update_अगरace_num(rdev, wdev->अगरtype, -1);
		अगर (rdev->scan_req && rdev->scan_req->wdev == wdev) अणु
			अगर (WARN_ON(!rdev->scan_req->notअगरied &&
				    (!rdev->पूर्णांक_scan_req ||
				     !rdev->पूर्णांक_scan_req->notअगरied)))
				rdev->scan_req->info.पातed = true;
			___cfg80211_scan_करोne(rdev, false);
		पूर्ण

		list_क्रम_each_entry_safe(pos, पंचांगp,
					 &rdev->sched_scan_req_list, list) अणु
			अगर (WARN_ON(pos->dev == wdev->netdev))
				cfg80211_stop_sched_scan_req(rdev, pos, false);
		पूर्ण

		rdev->खोलोcount--;
		wiphy_unlock(&rdev->wiphy);
		wake_up(&rdev->dev_रुको);
		अवरोध;
	हाल NETDEV_UP:
		wiphy_lock(&rdev->wiphy);
		cfg80211_update_अगरace_num(rdev, wdev->अगरtype, 1);
		wdev_lock(wdev);
		चयन (wdev->अगरtype) अणु
#अगर_घोषित CONFIG_CFG80211_WEXT
		हाल NL80211_IFTYPE_ADHOC:
			cfg80211_ibss_wext_join(rdev, wdev);
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
			cfg80211_mgd_wext_connect(rdev, wdev);
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MAC80211_MESH
		हाल NL80211_IFTYPE_MESH_POINT:
			अणु
				/* backward compat code... */
				काष्ठा mesh_setup setup;
				स_नकल(&setup, &शेष_mesh_setup,
						माप(setup));
				 /* back compat only needed क्रम mesh_id */
				setup.mesh_id = wdev->ssid;
				setup.mesh_id_len = wdev->mesh_id_up_len;
				अगर (wdev->mesh_id_up_len)
					__cfg80211_join_mesh(rdev, dev,
							&setup,
							&शेष_mesh_config);
				अवरोध;
			पूर्ण
#पूर्ण_अगर
		शेष:
			अवरोध;
		पूर्ण
		wdev_unlock(wdev);
		rdev->खोलोcount++;

		/*
		 * Configure घातer management to the driver here so that its
		 * correctly set also after पूर्णांकerface type changes etc.
		 */
		अगर ((wdev->अगरtype == NL80211_IFTYPE_STATION ||
		     wdev->अगरtype == NL80211_IFTYPE_P2P_CLIENT) &&
		    rdev->ops->set_घातer_mgmt &&
		    rdev_set_घातer_mgmt(rdev, dev, wdev->ps,
					wdev->ps_समयout)) अणु
			/* assume this means it's off */
			wdev->ps = false;
		पूर्ण
		wiphy_unlock(&rdev->wiphy);
		अवरोध;
	हाल NETDEV_PRE_UP:
		अगर (!cfg80211_अगरtype_allowed(wdev->wiphy, wdev->अगरtype,
					     wdev->use_4addr, 0))
			वापस notअगरier_from_त्रुटि_सं(-EOPNOTSUPP);

		अगर (rfसमाप्त_blocked(rdev->rfसमाप्त))
			वापस notअगरier_from_त्रुटि_सं(-ERFKILL);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	wireless_nlevent_flush();

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block cfg80211_netdev_notअगरier = अणु
	.notअगरier_call = cfg80211_netdev_notअगरier_call,
पूर्ण;

अटल व्योम __net_निकास cfg80211_pernet_निकास(काष्ठा net *net)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	rtnl_lock();
	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		अगर (net_eq(wiphy_net(&rdev->wiphy), net))
			WARN_ON(cfg80211_चयन_netns(rdev, &init_net));
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations cfg80211_pernet_ops = अणु
	.निकास = cfg80211_pernet_निकास,
पूर्ण;

अटल पूर्णांक __init cfg80211_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_device(&cfg80211_pernet_ops);
	अगर (err)
		जाओ out_fail_pernet;

	err = wiphy_sysfs_init();
	अगर (err)
		जाओ out_fail_sysfs;

	err = रेजिस्टर_netdevice_notअगरier(&cfg80211_netdev_notअगरier);
	अगर (err)
		जाओ out_fail_notअगरier;

	err = nl80211_init();
	अगर (err)
		जाओ out_fail_nl80211;

	ieee80211_debugfs_dir = debugfs_create_dir("ieee80211", शून्य);

	err = regulatory_init();
	अगर (err)
		जाओ out_fail_reg;

	cfg80211_wq = alloc_ordered_workqueue("cfg80211", WQ_MEM_RECLAIM);
	अगर (!cfg80211_wq) अणु
		err = -ENOMEM;
		जाओ out_fail_wq;
	पूर्ण

	वापस 0;

out_fail_wq:
	regulatory_निकास();
out_fail_reg:
	debugfs_हटाओ(ieee80211_debugfs_dir);
	nl80211_निकास();
out_fail_nl80211:
	unरेजिस्टर_netdevice_notअगरier(&cfg80211_netdev_notअगरier);
out_fail_notअगरier:
	wiphy_sysfs_निकास();
out_fail_sysfs:
	unरेजिस्टर_pernet_device(&cfg80211_pernet_ops);
out_fail_pernet:
	वापस err;
पूर्ण
fs_initcall(cfg80211_init);

अटल व्योम __निकास cfg80211_निकास(व्योम)
अणु
	debugfs_हटाओ(ieee80211_debugfs_dir);
	nl80211_निकास();
	unरेजिस्टर_netdevice_notअगरier(&cfg80211_netdev_notअगरier);
	wiphy_sysfs_निकास();
	regulatory_निकास();
	unरेजिस्टर_pernet_device(&cfg80211_pernet_ops);
	destroy_workqueue(cfg80211_wq);
पूर्ण
module_निकास(cfg80211_निकास);
