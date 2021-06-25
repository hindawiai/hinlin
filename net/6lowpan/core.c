<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Authors:
 * (C) 2015 Pengutronix, Alexander Aring <aar@pengutronix.de>
 */

#समावेश <linux/module.h>

#समावेश <net/6lowpan.h>
#समावेश <net/addrconf.h>

#समावेश "6lowpan_i.h"

पूर्णांक lowpan_रेजिस्टर_netdevice(काष्ठा net_device *dev,
			      क्रमागत lowpan_lltypes lltype)
अणु
	पूर्णांक i, ret;

	चयन (lltype) अणु
	हाल LOWPAN_LLTYPE_IEEE802154:
		dev->addr_len = EUI64_ADDR_LEN;
		अवरोध;

	हाल LOWPAN_LLTYPE_BTLE:
		dev->addr_len = ETH_ALEN;
		अवरोध;
	पूर्ण

	dev->type = ARPHRD_6LOWPAN;
	dev->mtu = IPV6_MIN_MTU;

	lowpan_dev(dev)->lltype = lltype;

	spin_lock_init(&lowpan_dev(dev)->ctx.lock);
	क्रम (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++)
		lowpan_dev(dev)->ctx.table[i].id = i;

	dev->ndisc_ops = &lowpan_ndisc_ops;

	ret = रेजिस्टर_netdevice(dev);
	अगर (ret < 0)
		वापस ret;

	lowpan_dev_debugfs_init(dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(lowpan_रेजिस्टर_netdevice);

पूर्णांक lowpan_रेजिस्टर_netdev(काष्ठा net_device *dev,
			   क्रमागत lowpan_lltypes lltype)
अणु
	पूर्णांक ret;

	rtnl_lock();
	ret = lowpan_रेजिस्टर_netdevice(dev, lltype);
	rtnl_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(lowpan_रेजिस्टर_netdev);

व्योम lowpan_unरेजिस्टर_netdevice(काष्ठा net_device *dev)
अणु
	unरेजिस्टर_netdevice(dev);
	lowpan_dev_debugfs_निकास(dev);
पूर्ण
EXPORT_SYMBOL(lowpan_unरेजिस्टर_netdevice);

व्योम lowpan_unरेजिस्टर_netdev(काष्ठा net_device *dev)
अणु
	rtnl_lock();
	lowpan_unरेजिस्टर_netdevice(dev);
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL(lowpan_unरेजिस्टर_netdev);

पूर्णांक addrconf_अगरid_802154_6lowpan(u8 *eui, काष्ठा net_device *dev)
अणु
	काष्ठा wpan_dev *wpan_dev = lowpan_802154_dev(dev)->wdev->ieee802154_ptr;

	/* Set लघु_addr स्वतःconfiguration अगर लघु_addr is present only */
	अगर (!lowpan_802154_is_valid_src_लघु_addr(wpan_dev->लघु_addr))
		वापस -1;

	/* For either address क्रमmat, all zero addresses MUST NOT be used */
	अगर (wpan_dev->pan_id == cpu_to_le16(0x0000) &&
	    wpan_dev->लघु_addr == cpu_to_le16(0x0000))
		वापस -1;

	/* Alternatively, अगर no PAN ID is known, 16 zero bits may be used */
	अगर (wpan_dev->pan_id == cpu_to_le16(IEEE802154_PAN_ID_BROADCAST))
		स_रखो(eui, 0, 2);
	अन्यथा
		ieee802154_le16_to_be16(eui, &wpan_dev->pan_id);

	/* The "Universal/Local" (U/L) bit shall be set to zero */
	eui[0] &= ~2;
	eui[2] = 0;
	eui[3] = 0xFF;
	eui[4] = 0xFE;
	eui[5] = 0;
	ieee802154_le16_to_be16(&eui[6], &wpan_dev->लघु_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_event(काष्ठा notअगरier_block *unused,
			अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा inet6_dev *idev;
	काष्ठा in6_addr addr;
	पूर्णांक i;

	अगर (dev->type != ARPHRD_6LOWPAN)
		वापस NOTIFY_DONE;

	idev = __in6_dev_get(dev);
	अगर (!idev)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
	हाल NETDEV_CHANGE:
		/* (802.15.4 6LoWPAN लघु address slaac handling */
		अगर (lowpan_is_ll(dev, LOWPAN_LLTYPE_IEEE802154) &&
		    addrconf_अगरid_802154_6lowpan(addr.s6_addr + 8, dev) == 0) अणु
			__ipv6_addr_set_half(&addr.s6_addr32[0],
					     htonl(0xFE800000), 0);
			addrconf_add_linklocal(idev, &addr, 0);
		पूर्ण
		अवरोध;
	हाल NETDEV_DOWN:
		क्रम (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++)
			clear_bit(LOWPAN_IPHC_CTX_FLAG_ACTIVE,
				  &lowpan_dev(dev)->ctx.table[i].flags);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block lowpan_notअगरier = अणु
	.notअगरier_call = lowpan_event,
पूर्ण;

अटल पूर्णांक __init lowpan_module_init(व्योम)
अणु
	पूर्णांक ret;

	lowpan_debugfs_init();

	ret = रेजिस्टर_netdevice_notअगरier(&lowpan_notअगरier);
	अगर (ret < 0) अणु
		lowpan_debugfs_निकास();
		वापस ret;
	पूर्ण

	request_module_noरुको("nhc_dest");
	request_module_noरुको("nhc_fragment");
	request_module_noरुको("nhc_hop");
	request_module_noरुको("nhc_ipv6");
	request_module_noरुको("nhc_mobility");
	request_module_noरुको("nhc_routing");
	request_module_noरुको("nhc_udp");

	वापस 0;
पूर्ण

अटल व्योम __निकास lowpan_module_निकास(व्योम)
अणु
	lowpan_debugfs_निकास();
	unरेजिस्टर_netdevice_notअगरier(&lowpan_notअगरier);
पूर्ण

module_init(lowpan_module_init);
module_निकास(lowpan_module_निकास);

MODULE_LICENSE("GPL");
