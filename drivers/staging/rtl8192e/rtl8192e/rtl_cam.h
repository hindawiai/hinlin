<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित _RTL_CAM_H
#घोषणा _RTL_CAM_H

#समावेश <linux/types.h>
काष्ठा net_device;

व्योम rtl92e_cam_reset(काष्ठा net_device *dev);
व्योम rtl92e_enable_hw_security_config(काष्ठा net_device *dev);
व्योम rtl92e_set_key(काष्ठा net_device *dev, u8 EntryNo, u8 KeyIndex,
		    u16 KeyType, स्थिर u8 *MacAddr, u8 DefaultKey,
		    u32 *KeyContent);
व्योम rtl92e_set_swcam(काष्ठा net_device *dev, u8 EntryNo, u8 KeyIndex,
		      u16 KeyType, स्थिर u8 *MacAddr, u8 DefaultKey,
		      u32 *KeyContent, u8 is_mesh);
व्योम rtl92e_cam_restore(काष्ठा net_device *dev);

#पूर्ण_अगर
