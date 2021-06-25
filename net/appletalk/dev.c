<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Moved here from drivers/net/net_init.c, which is:
 *	Written 1993,1994,1995 by Donald Becker.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ltalk.h>

अटल व्योम ltalk_setup(काष्ठा net_device *dev)
अणु
	/* Fill in the fields of the device काष्ठाure with localtalk-generic values. */

	dev->type		= ARPHRD_LOCALTLK;
	dev->hard_header_len 	= LTALK_HLEN;
	dev->mtu		= LTALK_MTU;
	dev->addr_len		= LTALK_ALEN;
	dev->tx_queue_len	= 10;

	dev->broadcast[0]	= 0xFF;

	dev->flags		= IFF_BROADCAST|IFF_MULTICAST|IFF_NOARP;
पूर्ण

/**
 * alloc_ltalkdev - Allocates and sets up an localtalk device
 * @माप_priv: Size of additional driver-निजी काष्ठाure to be allocated
 *	क्रम this localtalk device
 *
 * Fill in the fields of the device काष्ठाure with localtalk-generic
 * values. Basically करोes everything except रेजिस्टरing the device.
 *
 * Conकाष्ठाs a new net device, complete with a निजी data area of
 * size @माप_priv.  A 32-byte (not bit) alignment is enक्रमced क्रम
 * this निजी data area.
 */

काष्ठा net_device *alloc_ltalkdev(पूर्णांक माप_priv)
अणु
	वापस alloc_netdev(माप_priv, "lt%d", NET_NAME_UNKNOWN,
			    ltalk_setup);
पूर्ण
EXPORT_SYMBOL(alloc_ltalkdev);
