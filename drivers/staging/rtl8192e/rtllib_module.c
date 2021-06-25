<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2004 Intel Corporation. All rights reserved.
 *
 * Portions of this file are based on the WEP enablement code provided by the
 * Host AP project hostap-drivers v0.1.3
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <jkmaline@cc.hut.fi>
 * Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>
 *
 * Contact Inक्रमmation:
 * James P. Ketrenos <ipw2100-admin@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 */

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in6.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <net/arp.h>
#समावेश "rtllib.h"

u32 rt_global_debug_component = COMP_ERR;
EXPORT_SYMBOL(rt_global_debug_component);

अटल अंतरभूत पूर्णांक rtllib_networks_allocate(काष्ठा rtllib_device *ieee)
अणु
	अगर (ieee->networks)
		वापस 0;

	ieee->networks = kसुस्मृति(MAX_NETWORK_COUNT,
				 माप(काष्ठा rtllib_network), GFP_KERNEL);
	अगर (!ieee->networks)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rtllib_networks_मुक्त(काष्ठा rtllib_device *ieee)
अणु
	अगर (!ieee->networks)
		वापस;
	kमुक्त(ieee->networks);
	ieee->networks = शून्य;
पूर्ण

अटल अंतरभूत व्योम rtllib_networks_initialize(काष्ठा rtllib_device *ieee)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&ieee->network_मुक्त_list);
	INIT_LIST_HEAD(&ieee->network_list);
	क्रम (i = 0; i < MAX_NETWORK_COUNT; i++)
		list_add_tail(&ieee->networks[i].list,
			      &ieee->network_मुक्त_list);
पूर्ण

काष्ठा net_device *alloc_rtllib(पूर्णांक माप_priv)
अणु
	काष्ठा rtllib_device *ieee = शून्य;
	काष्ठा net_device *dev;
	पूर्णांक i, err;

	pr_debug("rtllib: Initializing...\n");

	dev = alloc_etherdev(माप(काष्ठा rtllib_device) + माप_priv);
	अगर (!dev) अणु
		pr_err("Unable to allocate net_device.\n");
		वापस शून्य;
	पूर्ण
	ieee = (काष्ठा rtllib_device *)netdev_priv_rsl(dev);
	ieee->dev = dev;

	err = rtllib_networks_allocate(ieee);
	अगर (err) अणु
		pr_err("Unable to allocate beacon storage: %d\n", err);
		जाओ failed;
	पूर्ण
	rtllib_networks_initialize(ieee);

	/* Default fragmentation threshold is maximum payload size */
	ieee->fts = DEFAULT_FTS;
	ieee->scan_age = DEFAULT_MAX_SCAN_AGE;
	ieee->खोलो_wep = 1;

	/* Default to enabling full खोलो WEP with host based encrypt/decrypt */
	ieee->host_encrypt = 1;
	ieee->host_decrypt = 1;
	ieee->ieee802_1x = 1; /* Default to supporting 802.1x */

	ieee->rtllib_ap_sec_type = rtllib_ap_sec_type;

	spin_lock_init(&ieee->lock);
	spin_lock_init(&ieee->wpax_suitlist_lock);
	spin_lock_init(&ieee->reorder_spinlock);
	atomic_set(&(ieee->aपंचांग_swbw), 0);

	/* SAM FIXME */
	lib80211_crypt_info_init(&ieee->crypt_info, "RTLLIB", &ieee->lock);

	ieee->wpa_enabled = 0;
	ieee->tkip_countermeasures = 0;
	ieee->drop_unencrypted = 0;
	ieee->privacy_invoked = 0;
	ieee->ieee802_1x = 1;
	ieee->raw_tx = 0;
	ieee->hwsec_active = 0;

	स_रखो(ieee->swcamtable, 0, माप(काष्ठा sw_cam_table) * 32);
	rtllib_sofपंचांगac_init(ieee);

	ieee->pHTInfo = kzalloc(माप(काष्ठा rt_hi_throughput), GFP_KERNEL);
	अगर (!ieee->pHTInfo)
		वापस शून्य;

	HTUpdateDefaultSetting(ieee);
	HTInitializeHTInfo(ieee);
	TSInitialize(ieee);
	क्रम (i = 0; i < IEEE_IBSS_MAC_HASH_SIZE; i++)
		INIT_LIST_HEAD(&ieee->ibss_mac_hash[i]);

	क्रम (i = 0; i < 17; i++) अणु
		ieee->last_rxseq_num[i] = -1;
		ieee->last_rxfrag_num[i] = -1;
		ieee->last_packet_समय[i] = 0;
	पूर्ण

	वापस dev;

 failed:
	मुक्त_netdev(dev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(alloc_rtllib);

व्योम मुक्त_rtllib(काष्ठा net_device *dev)
अणु
	काष्ठा rtllib_device *ieee = (काष्ठा rtllib_device *)
				      netdev_priv_rsl(dev);

	kमुक्त(ieee->pHTInfo);
	ieee->pHTInfo = शून्य;
	rtllib_sofपंचांगac_मुक्त(ieee);

	lib80211_crypt_info_मुक्त(&ieee->crypt_info);

	rtllib_networks_मुक्त(ieee);
	मुक्त_netdev(dev);
पूर्ण
EXPORT_SYMBOL(मुक्त_rtllib);

अटल पूर्णांक __init rtllib_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास rtllib_निकास(व्योम)
अणु
पूर्ण

module_init(rtllib_init);
module_निकास(rtllib_निकास);

MODULE_LICENSE("GPL");
