<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

#समावेश <linux/phy.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ratelimit.h>
#समावेश <net/dst.h>

#समावेश "octeon-ethernet.h"
#समावेश "ethernet-defines.h"
#समावेश "ethernet-util.h"
#समावेश "ethernet-mdio.h"

पूर्णांक cvm_oct_sgmii_खोलो(काष्ठा net_device *dev)
अणु
	वापस cvm_oct_common_खोलो(dev, cvm_oct_link_poll);
पूर्ण

पूर्णांक cvm_oct_sgmii_init(काष्ठा net_device *dev)
अणु
	cvm_oct_common_init(dev);

	/* FIXME: Need स्वतःneg logic */
	वापस 0;
पूर्ण
