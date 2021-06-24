<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/utsname.h>
#समावेश <net/cfg80211.h>
#समावेश "core.h"
#समावेश "rdev-ops.h"

व्योम cfg80211_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा device *pdev = wiphy_dev(wdev->wiphy);

	अगर (pdev->driver)
		strlcpy(info->driver, pdev->driver->name,
			माप(info->driver));
	अन्यथा
		strlcpy(info->driver, "N/A", माप(info->driver));

	strlcpy(info->version, init_utsname()->release, माप(info->version));

	अगर (wdev->wiphy->fw_version[0])
		strlcpy(info->fw_version, wdev->wiphy->fw_version,
			माप(info->fw_version));
	अन्यथा
		strlcpy(info->fw_version, "N/A", माप(info->fw_version));

	strlcpy(info->bus_info, dev_name(wiphy_dev(wdev->wiphy)),
		माप(info->bus_info));
पूर्ण
EXPORT_SYMBOL(cfg80211_get_drvinfo);
