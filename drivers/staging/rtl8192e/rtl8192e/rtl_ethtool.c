<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/delay.h>

#समावेश "rtl_core.h"

अटल व्योम _rtl92e_ethtool_get_drvinfo(काष्ठा net_device *dev,
					काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	strscpy(info->driver, DRV_NAME, माप(info->driver));
	strscpy(info->version, DRV_VERSION, माप(info->version));
	strscpy(info->bus_info, pci_name(priv->pdev), माप(info->bus_info));
पूर्ण

अटल u32 _rtl92e_ethtool_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	वापस ((priv->rtllib->state == RTLLIB_LINKED) ||
		(priv->rtllib->state == RTLLIB_LINKED_SCANNING));
पूर्ण

स्थिर काष्ठा ethtool_ops rtl819x_ethtool_ops = अणु
	.get_drvinfo = _rtl92e_ethtool_get_drvinfo,
	.get_link = _rtl92e_ethtool_get_link,
पूर्ण;
