<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#अगर_अघोषित WILC_CFG80211_H
#घोषणा WILC_CFG80211_H
#समावेश "netdev.h"

काष्ठा wiphy *wilc_cfg_alloc(व्योम);
पूर्णांक wilc_cfg80211_init(काष्ठा wilc **wilc, काष्ठा device *dev, पूर्णांक io_type,
		       स्थिर काष्ठा wilc_hअगर_func *ops);
काष्ठा wilc *wilc_create_wiphy(काष्ठा device *dev);
व्योम wilc_deinit_host_पूर्णांक(काष्ठा net_device *net);
पूर्णांक wilc_init_host_पूर्णांक(काष्ठा net_device *net);
व्योम wilc_wfi_monitor_rx(काष्ठा net_device *mon_dev, u8 *buff, u32 size);
काष्ठा wilc_vअगर *wilc_netdev_पूर्णांकerface(काष्ठा wilc *wl, स्थिर अक्षर *name,
				       क्रमागत nl80211_अगरtype type);
व्योम wilc_wfi_deinit_mon_पूर्णांकerface(काष्ठा wilc *wl, bool rtnl_locked);
काष्ठा net_device *wilc_wfi_init_mon_पूर्णांकerface(काष्ठा wilc *wl,
					       स्थिर अक्षर *name,
					       काष्ठा net_device *real_dev);
व्योम wilc_update_mgmt_frame_registrations(काष्ठा wiphy *wiphy,
					  काष्ठा wireless_dev *wdev,
					  काष्ठा mgmt_frame_regs *upd);
काष्ठा wilc_vअगर *wilc_get_पूर्णांकerface(काष्ठा wilc *wl);
काष्ठा wilc_vअगर *wilc_get_wl_to_vअगर(काष्ठा wilc *wl);
व्योम wlan_deinit_locks(काष्ठा wilc *wilc);
#पूर्ण_अगर
