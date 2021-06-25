<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Authors:
 * Alexander Aring <aar@pengutronix.de>
 *
 * Based on: net/wireless/sysfs.c
 */

#समावेश <linux/device.h>
#समावेश <linux/rtnetlink.h>

#समावेश <net/cfg802154.h>

#समावेश "core.h"
#समावेश "sysfs.h"
#समावेश "rdev-ops.h"

अटल अंतरभूत काष्ठा cfg802154_रेजिस्टरed_device *
dev_to_rdev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा cfg802154_रेजिस्टरed_device,
			    wpan_phy.dev);
पूर्ण

#घोषणा SHOW_FMT(name, fmt, member)					\
अटल sमाप_प्रकार name ## _show(काष्ठा device *dev,			\
			     काष्ठा device_attribute *attr,		\
			     अक्षर *buf)					\
अणु									\
	वापस प्र_लिखो(buf, fmt "\n", dev_to_rdev(dev)->member);	\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

SHOW_FMT(index, "%d", wpan_phy_idx);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा wpan_phy *wpan_phy = &dev_to_rdev(dev)->wpan_phy;

	वापस प्र_लिखो(buf, "%s\n", dev_name(&wpan_phy->dev));
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल व्योम wpan_phy_release(काष्ठा device *dev)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = dev_to_rdev(dev);

	cfg802154_dev_मुक्त(rdev);
पूर्ण

अटल काष्ठा attribute *pmib_attrs[] = अणु
	&dev_attr_index.attr,
	&dev_attr_name.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(pmib);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक wpan_phy_suspend(काष्ठा device *dev)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = dev_to_rdev(dev);
	पूर्णांक ret = 0;

	अगर (rdev->ops->suspend) अणु
		rtnl_lock();
		ret = rdev_suspend(rdev);
		rtnl_unlock();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wpan_phy_resume(काष्ठा device *dev)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = dev_to_rdev(dev);
	पूर्णांक ret = 0;

	अगर (rdev->ops->resume) अणु
		rtnl_lock();
		ret = rdev_resume(rdev);
		rtnl_unlock();
	पूर्ण

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(wpan_phy_pm_ops, wpan_phy_suspend, wpan_phy_resume);
#घोषणा WPAN_PHY_PM_OPS (&wpan_phy_pm_ops)
#अन्यथा
#घोषणा WPAN_PHY_PM_OPS शून्य
#पूर्ण_अगर

काष्ठा class wpan_phy_class = अणु
	.name = "ieee802154",
	.dev_release = wpan_phy_release,
	.dev_groups = pmib_groups,
	.pm = WPAN_PHY_PM_OPS,
पूर्ण;

पूर्णांक wpan_phy_sysfs_init(व्योम)
अणु
	वापस class_रेजिस्टर(&wpan_phy_class);
पूर्ण

व्योम wpan_phy_sysfs_निकास(व्योम)
अणु
	class_unरेजिस्टर(&wpan_phy_class);
पूर्ण
