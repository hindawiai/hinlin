<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/माला.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <net/dst.h>
#अगर_घोषित CONFIG_XFRM
#समावेश <linux/xfrm.h>
#समावेश <net/xfrm.h>
#पूर्ण_अगर /* CONFIG_XFRM */

बाह्य स्थिर काष्ठा ethtool_ops cvm_oct_ethtool_ops;

पूर्णांक cvm_oct_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
पूर्णांक cvm_oct_phy_setup_device(काष्ठा net_device *dev);
