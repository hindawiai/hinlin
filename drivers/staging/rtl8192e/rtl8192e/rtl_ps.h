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
#अगर_अघोषित _RTL_PS_H
#घोषणा _RTL_PS_H

#समावेश <linux/types.h>

काष्ठा net_device;

#घोषणा RT_CHECK_FOR_HANG_PERIOD 2

व्योम rtl92e_hw_wakeup(काष्ठा net_device *dev);
व्योम rtl92e_enter_sleep(काष्ठा net_device *dev, u64 समय);
व्योम rtl92e_rtllib_ips_leave_wq(काष्ठा net_device *dev);
व्योम rtl92e_rtllib_ips_leave(काष्ठा net_device *dev);
व्योम rtl92e_ips_leave_wq(व्योम *data);

व्योम rtl92e_ips_enter(काष्ठा net_device *dev);
व्योम rtl92e_ips_leave(काष्ठा net_device *dev);

व्योम rtl92e_leisure_ps_enter(काष्ठा net_device *dev);
व्योम rtl92e_leisure_ps_leave(काष्ठा net_device *dev);

#पूर्ण_अगर
