<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*******************************************************************************
 *
 *  Copyright(c) 2004 Intel Corporation. All rights reserved.
 *
 *  Portions of this file are based on the WEP enablement code provided by the
 *  Host AP project hostap-drivers v0.1.3
 *  Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 *  <jkmaline@cc.hut.fi>
 *  Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>
 *
 *  Contact Inक्रमmation:
 *  James P. Ketrenos <ipw2100-admin@linux.पूर्णांकel.com>
 *  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 ******************************************************************************/

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

#समावेश "ieee80211.h"

MODULE_DESCRIPTION("802.11 data/management/control stack");
MODULE_AUTHOR("Copyright (C) 2004 Intel Corporation <jketreno@linux.intel.com>");
MODULE_LICENSE("GPL");

#घोषणा DRV_NAME "ieee80211"

अटल अंतरभूत पूर्णांक ieee80211_networks_allocate(काष्ठा ieee80211_device *ieee)
अणु
	अगर (ieee->networks)
		वापस 0;

	ieee->networks = kसुस्मृति(MAX_NETWORK_COUNT,
				 माप(काष्ठा ieee80211_network),
				 GFP_KERNEL);
	अगर (!ieee->networks) अणु
		netdev_warn(ieee->dev, "Out of memory allocating beacons\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ieee80211_networks_मुक्त(काष्ठा ieee80211_device *ieee)
अणु
	अगर (!ieee->networks)
		वापस;
	kमुक्त(ieee->networks);
	ieee->networks = शून्य;
पूर्ण

अटल अंतरभूत व्योम ieee80211_networks_initialize(काष्ठा ieee80211_device *ieee)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&ieee->network_मुक्त_list);
	INIT_LIST_HEAD(&ieee->network_list);
	क्रम (i = 0; i < MAX_NETWORK_COUNT; i++)
		list_add_tail(&ieee->networks[i].list, &ieee->network_मुक्त_list);
पूर्ण

काष्ठा net_device *alloc_ieee80211(पूर्णांक माप_priv)
अणु
	काष्ठा ieee80211_device *ieee;
	काष्ठा net_device *dev;
	पूर्णांक i, err;

	IEEE80211_DEBUG_INFO("Initializing...\n");

	dev = alloc_etherdev(माप(काष्ठा ieee80211_device) + माप_priv);
	अगर (!dev) अणु
		IEEE80211_ERROR("Unable to network device.\n");
		जाओ failed;
	पूर्ण

	ieee = netdev_priv(dev);
	ieee->dev = dev;

	err = ieee80211_networks_allocate(ieee);
	अगर (err) अणु
		IEEE80211_ERROR("Unable to allocate beacon storage: %d\n",
				err);
		जाओ failed;
	पूर्ण
	ieee80211_networks_initialize(ieee);

	/* Default fragmentation threshold is maximum payload size */
	ieee->fts = DEFAULT_FTS;
	ieee->scan_age = DEFAULT_MAX_SCAN_AGE;
	ieee->खोलो_wep = 1;

	/* Default to enabling full खोलो WEP with host based encrypt/decrypt */
	ieee->host_encrypt = 1;
	ieee->host_decrypt = 1;
	ieee->ieee802_1x = 1; /* Default to supporting 802.1x */

	INIT_LIST_HEAD(&ieee->crypt_deinit_list);
	समयr_setup(&ieee->crypt_deinit_समयr, ieee80211_crypt_deinit_handler,
		    0);

	spin_lock_init(&ieee->lock);
	spin_lock_init(&ieee->wpax_suitlist_lock);
	spin_lock_init(&ieee->bw_spinlock);
	spin_lock_init(&ieee->reorder_spinlock);
	/* added by WB */
	atomic_set(&ieee->aपंचांग_chnlop, 0);
	atomic_set(&ieee->aपंचांग_swbw, 0);

	ieee->wpax_type_set = 0;
	ieee->wpa_enabled = 0;
	ieee->tkip_countermeasures = 0;
	ieee->drop_unencrypted = 0;
	ieee->privacy_invoked = 0;
	ieee->ieee802_1x = 1;
	ieee->raw_tx = 0;
	//ieee->hwsec_support = 1; //defalt support hw security. //use module_param instead.
	ieee->hwsec_active = 0; /* disable hwsec, चयन it on when necessary. */

	ieee80211_sofपंचांगac_init(ieee);

	ieee->pHTInfo = kzalloc(माप(RT_HIGH_THROUGHPUT), GFP_KERNEL);
	अगर (!ieee->pHTInfo) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "can't alloc memory for HTInfo\n");

		/* By this poपूर्णांक in code ieee80211_networks_allocate() has been
		 * successfully called so the memory allocated should be मुक्तd
		 */
		ieee80211_networks_मुक्त(ieee);
		जाओ failed;
	पूर्ण
	HTUpdateDefaultSetting(ieee);
	HTInitializeHTInfo(ieee); /* may move to other place. */
	TSInitialize(ieee);

	क्रम (i = 0; i < IEEE_IBSS_MAC_HASH_SIZE; i++)
		INIT_LIST_HEAD(&ieee->ibss_mac_hash[i]);

	क्रम (i = 0; i < 17; i++) अणु
		ieee->last_rxseq_num[i] = -1;
		ieee->last_rxfrag_num[i] = -1;
		ieee->last_packet_समय[i] = 0;
	पूर्ण

/* These function were added to load crypte module स्वतःly */
	ieee80211_tkip_null();

	वापस dev;

 failed:
	अगर (dev)
		मुक्त_netdev(dev);

	वापस शून्य;
पूर्ण

व्योम मुक्त_ieee80211(काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_device *ieee = netdev_priv(dev);
	पूर्णांक i;
	/* काष्ठा list_head *p, *q; */
//	del_समयr_sync(&ieee->SwBwTimer);
	kमुक्त(ieee->pHTInfo);
	ieee->pHTInfo = शून्य;
	RemoveAllTS(ieee);
	ieee80211_sofपंचांगac_मुक्त(ieee);
	del_समयr_sync(&ieee->crypt_deinit_समयr);
	ieee80211_crypt_deinit_entries(ieee, 1);

	क्रम (i = 0; i < WEP_KEYS; i++) अणु
		काष्ठा ieee80211_crypt_data *crypt = ieee->crypt[i];

		अगर (crypt) अणु
			अगर (crypt->ops)
				crypt->ops->deinit(crypt->priv);
			kमुक्त(crypt);
			ieee->crypt[i] = शून्य;
		पूर्ण
	पूर्ण

	ieee80211_networks_मुक्त(ieee);
	मुक्त_netdev(dev);
पूर्ण

#अगर_घोषित CONFIG_IEEE80211_DEBUG

u32 ieee80211_debug_level;
अटल पूर्णांक debug = //	    IEEE80211_DL_INFO	|
	//		    IEEE80211_DL_WX	|
	//		    IEEE80211_DL_SCAN	|
	//		    IEEE80211_DL_STATE	|
	//		    IEEE80211_DL_MGMT	|
	//		    IEEE80211_DL_FRAG	|
	//		    IEEE80211_DL_EAP	|
	//		    IEEE80211_DL_DROP	|
	//		    IEEE80211_DL_TX	|
	//		    IEEE80211_DL_RX	|
			    //IEEE80211_DL_QOS    |
	//		    IEEE80211_DL_HT	|
	//		    IEEE80211_DL_TS	|
//			    IEEE80211_DL_BA	|
	//		    IEEE80211_DL_REORDER|
//			    IEEE80211_DL_TRACE  |
			    //IEEE80211_DL_DATA	|
			    IEEE80211_DL_ERR	  /* awayls खोलो this flags to show error out */
			    ;
अटल काष्ठा proc_dir_entry *ieee80211_proc;

अटल पूर्णांक show_debug_level(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "0x%08X\n", ieee80211_debug_level);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_debug_level(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				 माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक err = kम_से_अदीर्घ_from_user(buffer, count, 0, &val);

	अगर (err)
		वापस err;
	ieee80211_debug_level = val;
	वापस count;
पूर्ण

अटल पूर्णांक खोलो_debug_level(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, show_debug_level, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops debug_level_proc_ops = अणु
	.proc_खोलो	= खोलो_debug_level,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= ग_लिखो_debug_level,
	.proc_release	= single_release,
पूर्ण;

पूर्णांक __init ieee80211_debug_init(व्योम)
अणु
	काष्ठा proc_dir_entry *e;

	ieee80211_debug_level = debug;

	ieee80211_proc = proc_सूची_गढ़ो(DRV_NAME, init_net.proc_net);
	अगर (!ieee80211_proc) अणु
		IEEE80211_ERROR("Unable to create " DRV_NAME
				" proc directory\n");
		वापस -EIO;
	पूर्ण
	e = proc_create("debug_level", 0644, ieee80211_proc, &debug_level_proc_ops);
	अगर (!e) अणु
		हटाओ_proc_entry(DRV_NAME, init_net.proc_net);
		ieee80211_proc = शून्य;
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

व्योम __निकास ieee80211_debug_निकास(व्योम)
अणु
	अगर (ieee80211_proc) अणु
		हटाओ_proc_entry("debug_level", ieee80211_proc);
		हटाओ_proc_entry(DRV_NAME, init_net.proc_net);
		ieee80211_proc = शून्य;
	पूर्ण
पूर्ण

module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "debug output mask");
#पूर्ण_अगर
