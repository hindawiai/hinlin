<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OCB mode implementation
 *
 * Copyright: (c) 2014 Czech Technical University in Prague
 *            (c) 2014 Volkswagen Group Research
 * Author:    Rostislav Lisovy <rostislav.lisovy@fel.cvut.cz>
 * Funded by: Volkswagen Group Research
 */

#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश "nl80211.h"
#समावेश "core.h"
#समावेश "rdev-ops.h"

पूर्णांक __cfg80211_join_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev,
			काष्ठा ocb_setup *setup)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_OCB)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->join_ocb)
		वापस -EOPNOTSUPP;

	अगर (WARN_ON(!setup->chandef.chan))
		वापस -EINVAL;

	err = rdev_join_ocb(rdev, dev, setup);
	अगर (!err)
		wdev->chandef = setup->chandef;

	वापस err;
पूर्ण

पूर्णांक cfg80211_join_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा net_device *dev,
		      काष्ठा ocb_setup *setup)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	wdev_lock(wdev);
	err = __cfg80211_join_ocb(rdev, dev, setup);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

पूर्णांक __cfg80211_leave_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_OCB)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->leave_ocb)
		वापस -EOPNOTSUPP;

	err = rdev_leave_ocb(rdev, dev);
	अगर (!err)
		स_रखो(&wdev->chandef, 0, माप(wdev->chandef));

	वापस err;
पूर्ण

पूर्णांक cfg80211_leave_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	wdev_lock(wdev);
	err = __cfg80211_leave_ocb(rdev, dev);
	wdev_unlock(wdev);

	वापस err;
पूर्ण
