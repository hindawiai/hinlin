<शैली गुरु>
/* Copyright 2011, Siemens AG
 * written by Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

/* Based on patches from Jon Smirl <jonsmirl@gmail.com>
 * Copyright (c) 2011 Jon Smirl <jonsmirl@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/* Jon's code is based on 6lowpan implementation क्रम Contiki which is:
 * Copyright (c) 2008, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ieee802154.h>

#समावेश <net/ipv6.h>

#समावेश "6lowpan_i.h"

अटल पूर्णांक खोलो_count;

अटल स्थिर काष्ठा header_ops lowpan_header_ops = अणु
	.create	= lowpan_header_create,
पूर्ण;

अटल पूर्णांक lowpan_dev_init(काष्ठा net_device *ldev)
अणु
	netdev_lockdep_set_classes(ldev);

	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_खोलो(काष्ठा net_device *dev)
अणु
	अगर (!खोलो_count)
		lowpan_rx_init();
	खोलो_count++;
	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_stop(काष्ठा net_device *dev)
अणु
	खोलो_count--;
	अगर (!खोलो_count)
		lowpan_rx_निकास();
	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_neigh_स्थिरruct(काष्ठा net_device *dev, काष्ठा neighbour *n)
अणु
	काष्ठा lowpan_802154_neigh *neigh = lowpan_802154_neigh(neighbour_priv(n));

	/* शेष no लघु_addr is available क्रम a neighbour */
	neigh->लघु_addr = cpu_to_le16(IEEE802154_ADDR_SHORT_UNSPEC);
	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	वापस lowpan_802154_dev(dev)->wdev->अगरindex;
पूर्ण

अटल स्थिर काष्ठा net_device_ops lowpan_netdev_ops = अणु
	.nकरो_init		= lowpan_dev_init,
	.nकरो_start_xmit		= lowpan_xmit,
	.nकरो_खोलो		= lowpan_खोलो,
	.nकरो_stop		= lowpan_stop,
	.nकरो_neigh_स्थिरruct    = lowpan_neigh_स्थिरruct,
	.nकरो_get_अगरlink         = lowpan_get_अगरlink,
पूर्ण;

अटल व्योम lowpan_setup(काष्ठा net_device *ldev)
अणु
	स_रखो(ldev->broadcast, 0xff, IEEE802154_ADDR_LEN);
	/* We need an ipv6hdr as minimum len when calling xmit */
	ldev->hard_header_len	= माप(काष्ठा ipv6hdr);
	ldev->flags		= IFF_BROADCAST | IFF_MULTICAST;
	ldev->priv_flags	|= IFF_NO_QUEUE;

	ldev->netdev_ops	= &lowpan_netdev_ops;
	ldev->header_ops	= &lowpan_header_ops;
	ldev->needs_मुक्त_netdev	= true;
	ldev->features		|= NETIF_F_NETNS_LOCAL;
पूर्ण

अटल पूर्णांक lowpan_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != IEEE802154_ADDR_LEN)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_newlink(काष्ठा net *src_net, काष्ठा net_device *ldev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *wdev;
	पूर्णांक ret;

	ASSERT_RTNL();

	pr_debug("adding new link\n");

	अगर (!tb[IFLA_LINK])
		वापस -EINVAL;
	/* find and hold wpan device */
	wdev = dev_get_by_index(dev_net(ldev), nla_get_u32(tb[IFLA_LINK]));
	अगर (!wdev)
		वापस -ENODEV;
	अगर (wdev->type != ARPHRD_IEEE802154) अणु
		dev_put(wdev);
		वापस -EINVAL;
	पूर्ण

	अगर (wdev->ieee802154_ptr->lowpan_dev) अणु
		dev_put(wdev);
		वापस -EBUSY;
	पूर्ण

	lowpan_802154_dev(ldev)->wdev = wdev;
	/* Set the lowpan hardware address to the wpan hardware address. */
	स_नकल(ldev->dev_addr, wdev->dev_addr, IEEE802154_ADDR_LEN);
	/* We need headroom क्रम possible wpan_dev_hard_header call and tailroom
	 * क्रम encryption/fcs handling. The lowpan पूर्णांकerface will replace
	 * the IPv6 header with 6LoWPAN header. At worst हाल the 6LoWPAN
	 * header has LOWPAN_IPHC_MAX_HEADER_LEN more bytes than the IPv6
	 * header.
	 */
	ldev->needed_headroom = LOWPAN_IPHC_MAX_HEADER_LEN +
				wdev->needed_headroom;
	ldev->needed_tailroom = wdev->needed_tailroom;

	ldev->neigh_priv_len = माप(काष्ठा lowpan_802154_neigh);

	ret = lowpan_रेजिस्टर_netdevice(ldev, LOWPAN_LLTYPE_IEEE802154);
	अगर (ret < 0) अणु
		dev_put(wdev);
		वापस ret;
	पूर्ण

	wdev->ieee802154_ptr->lowpan_dev = ldev;
	वापस 0;
पूर्ण

अटल व्योम lowpan_dellink(काष्ठा net_device *ldev, काष्ठा list_head *head)
अणु
	काष्ठा net_device *wdev = lowpan_802154_dev(ldev)->wdev;

	ASSERT_RTNL();

	wdev->ieee802154_ptr->lowpan_dev = शून्य;
	lowpan_unरेजिस्टर_netdevice(ldev);
	dev_put(wdev);
पूर्ण

अटल काष्ठा rtnl_link_ops lowpan_link_ops __पढ़ो_mostly = अणु
	.kind		= "lowpan",
	.priv_size	= LOWPAN_PRIV_SIZE(माप(काष्ठा lowpan_802154_dev)),
	.setup		= lowpan_setup,
	.newlink	= lowpan_newlink,
	.dellink	= lowpan_dellink,
	.validate	= lowpan_validate,
पूर्ण;

अटल अंतरभूत पूर्णांक __init lowpan_netlink_init(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&lowpan_link_ops);
पूर्ण

अटल अंतरभूत व्योम lowpan_netlink_fini(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&lowpan_link_ops);
पूर्ण

अटल पूर्णांक lowpan_device_event(काष्ठा notअगरier_block *unused,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा wpan_dev *wpan_dev;

	अगर (ndev->type != ARPHRD_IEEE802154)
		वापस NOTIFY_DONE;
	wpan_dev = ndev->ieee802154_ptr;
	अगर (!wpan_dev)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UNREGISTER:
		/* Check अगर wpan पूर्णांकerface is unरेजिस्टरed that we
		 * also delete possible lowpan पूर्णांकerfaces which beदीर्घs
		 * to the wpan पूर्णांकerface.
		 */
		अगर (wpan_dev->lowpan_dev)
			lowpan_dellink(wpan_dev->lowpan_dev, शून्य);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block lowpan_dev_notअगरier = अणु
	.notअगरier_call = lowpan_device_event,
पूर्ण;

अटल पूर्णांक __init lowpan_init_module(व्योम)
अणु
	पूर्णांक err = 0;

	err = lowpan_net_frag_init();
	अगर (err < 0)
		जाओ out;

	err = lowpan_netlink_init();
	अगर (err < 0)
		जाओ out_frag;

	err = रेजिस्टर_netdevice_notअगरier(&lowpan_dev_notअगरier);
	अगर (err < 0)
		जाओ out_pack;

	वापस 0;

out_pack:
	lowpan_netlink_fini();
out_frag:
	lowpan_net_frag_निकास();
out:
	वापस err;
पूर्ण

अटल व्योम __निकास lowpan_cleanup_module(व्योम)
अणु
	lowpan_netlink_fini();

	lowpan_net_frag_निकास();

	unरेजिस्टर_netdevice_notअगरier(&lowpan_dev_notअगरier);
पूर्ण

module_init(lowpan_init_module);
module_निकास(lowpan_cleanup_module);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("lowpan");
