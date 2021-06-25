<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ieee80211.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>
#समावेश "nl80211.h"
#समावेश "core.h"
#समावेश "rdev-ops.h"


पूर्णांक __cfg80211_stop_ap(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा net_device *dev, bool notअगरy)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (!rdev->ops->stop_ap)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EOPNOTSUPP;

	अगर (!wdev->beacon_पूर्णांकerval)
		वापस -ENOENT;

	err = rdev_stop_ap(rdev, dev);
	अगर (!err) अणु
		wdev->conn_owner_nlportid = 0;
		wdev->beacon_पूर्णांकerval = 0;
		स_रखो(&wdev->chandef, 0, माप(wdev->chandef));
		wdev->ssid_len = 0;
		rdev_set_qos_map(rdev, dev, शून्य);
		अगर (notअगरy)
			nl80211_send_ap_stopped(wdev);

		/* Should we apply the grace period during beaconing पूर्णांकerface
		 * shutकरोwn also?
		 */
		cfg80211_sched_dfs_chan_update(rdev);
	पूर्ण

	schedule_work(&cfg80211_disconnect_work);

	वापस err;
पूर्ण

पूर्णांक cfg80211_stop_ap(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     काष्ठा net_device *dev, bool notअगरy)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	wdev_lock(wdev);
	err = __cfg80211_stop_ap(rdev, dev, notअगरy);
	wdev_unlock(wdev);

	वापस err;
पूर्ण
