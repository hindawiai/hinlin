<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file provides /sys/class/ieee80211/<wiphy name>/
 * and some शेष attributes.
 *
 * Copyright 2005-2006	Jiri Benc <jbenc@suse.cz>
 * Copyright 2006	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2020-2021 Intel Corporation
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/cfg80211.h>
#समावेश "sysfs.h"
#समावेश "core.h"
#समावेश "rdev-ops.h"

अटल अंतरभूत काष्ठा cfg80211_रेजिस्टरed_device *dev_to_rdev(
	काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा cfg80211_रेजिस्टरed_device, wiphy.dev);
पूर्ण

#घोषणा SHOW_FMT(name, fmt, member)					\
अटल sमाप_प्रकार name ## _show(काष्ठा device *dev,			\
			      काष्ठा device_attribute *attr,		\
			      अक्षर *buf)				\
अणु									\
	वापस प्र_लिखो(buf, fmt "\n", dev_to_rdev(dev)->member);	\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

SHOW_FMT(index, "%d", wiphy_idx);
SHOW_FMT(macaddress, "%pM", wiphy.perm_addr);
SHOW_FMT(address_mask, "%pM", wiphy.addr_mask);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा wiphy *wiphy = &dev_to_rdev(dev)->wiphy;

	वापस प्र_लिखो(buf, "%s\n", wiphy_name(wiphy));
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार addresses_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा wiphy *wiphy = &dev_to_rdev(dev)->wiphy;
	अक्षर *start = buf;
	पूर्णांक i;

	अगर (!wiphy->addresses)
		वापस प्र_लिखो(buf, "%pM\n", wiphy->perm_addr);

	क्रम (i = 0; i < wiphy->n_addresses; i++)
		buf += प्र_लिखो(buf, "%pM\n", wiphy->addresses[i].addr);

	वापस buf - start;
पूर्ण
अटल DEVICE_ATTR_RO(addresses);

अटल काष्ठा attribute *ieee80211_attrs[] = अणु
	&dev_attr_index.attr,
	&dev_attr_macaddress.attr,
	&dev_attr_address_mask.attr,
	&dev_attr_addresses.attr,
	&dev_attr_name.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ieee80211);

अटल व्योम wiphy_dev_release(काष्ठा device *dev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = dev_to_rdev(dev);

	cfg80211_dev_मुक्त(rdev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम cfg80211_leave_all(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा wireless_dev *wdev;

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list)
		cfg80211_leave(rdev, wdev);
पूर्ण

अटल पूर्णांक wiphy_suspend(काष्ठा device *dev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = dev_to_rdev(dev);
	पूर्णांक ret = 0;

	rdev->suspend_at = kसमय_get_bootसमय_seconds();

	rtnl_lock();
	wiphy_lock(&rdev->wiphy);
	अगर (rdev->wiphy.रेजिस्टरed) अणु
		अगर (!rdev->wiphy.wowlan_config) अणु
			cfg80211_leave_all(rdev);
			cfg80211_process_rdev_events(rdev);
		पूर्ण
		अगर (rdev->ops->suspend)
			ret = rdev_suspend(rdev, rdev->wiphy.wowlan_config);
		अगर (ret == 1) अणु
			/* Driver refuse to configure wowlan */
			cfg80211_leave_all(rdev);
			cfg80211_process_rdev_events(rdev);
			ret = rdev_suspend(rdev, शून्य);
		पूर्ण
	पूर्ण
	wiphy_unlock(&rdev->wiphy);
	rtnl_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक wiphy_resume(काष्ठा device *dev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = dev_to_rdev(dev);
	पूर्णांक ret = 0;

	/* Age scan results with समय spent in suspend */
	cfg80211_bss_age(rdev, kसमय_get_bootसमय_seconds() - rdev->suspend_at);

	rtnl_lock();
	wiphy_lock(&rdev->wiphy);
	अगर (rdev->wiphy.रेजिस्टरed && rdev->ops->resume)
		ret = rdev_resume(rdev);
	wiphy_unlock(&rdev->wiphy);

	अगर (ret)
		cfg80211_shutकरोwn_all_पूर्णांकerfaces(&rdev->wiphy);

	rtnl_unlock();

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(wiphy_pm_ops, wiphy_suspend, wiphy_resume);
#घोषणा WIPHY_PM_OPS (&wiphy_pm_ops)
#अन्यथा
#घोषणा WIPHY_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर व्योम *wiphy_namespace(काष्ठा device *d)
अणु
	काष्ठा wiphy *wiphy = container_of(d, काष्ठा wiphy, dev);

	वापस wiphy_net(wiphy);
पूर्ण

काष्ठा class ieee80211_class = अणु
	.name = "ieee80211",
	.owner = THIS_MODULE,
	.dev_release = wiphy_dev_release,
	.dev_groups = ieee80211_groups,
	.pm = WIPHY_PM_OPS,
	.ns_type = &net_ns_type_operations,
	.namespace = wiphy_namespace,
पूर्ण;

पूर्णांक wiphy_sysfs_init(व्योम)
अणु
	वापस class_रेजिस्टर(&ieee80211_class);
पूर्ण

व्योम wiphy_sysfs_निकास(व्योम)
अणु
	class_unरेजिस्टर(&ieee80211_class);
पूर्ण
