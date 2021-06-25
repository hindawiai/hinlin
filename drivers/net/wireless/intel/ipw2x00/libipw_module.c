<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************

  Copyright(c) 2004-2005 Intel Corporation. All rights reserved.

  Portions of this file are based on the WEP enablement code provided by the
  Host AP project hostap-drivers v0.1.3
  Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
  <j@w1.fi>
  Copyright (c) 2002-2003, Jouni Malinen <j@w1.fi>


  Contact Inक्रमmation:
  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

*******************************************************************************/

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in6.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <net/net_namespace.h>
#समावेश <net/arp.h>

#समावेश "libipw.h"

#घोषणा DRV_DESCRIPTION "802.11 data/management/control stack"
#घोषणा DRV_NAME        "libipw"
#घोषणा DRV_PROCNAME	"ieee80211"
#घोषणा DRV_VERSION	LIBIPW_VERSION
#घोषणा DRV_COPYRIGHT   "Copyright (C) 2004-2005 Intel Corporation <jketreno@linux.intel.com>"

MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR(DRV_COPYRIGHT);
MODULE_LICENSE("GPL");

अटल काष्ठा cfg80211_ops libipw_config_ops = अणु पूर्ण;
अटल व्योम *libipw_wiphy_privid = &libipw_wiphy_privid;

अटल पूर्णांक libipw_networks_allocate(काष्ठा libipw_device *ieee)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < MAX_NETWORK_COUNT; i++) अणु
		ieee->networks[i] = kzalloc(माप(काष्ठा libipw_network),
					    GFP_KERNEL);
		अगर (!ieee->networks[i]) अणु
			LIBIPW_ERROR("Out of memory allocating beacons\n");
			क्रम (j = 0; j < i; j++)
				kमुक्त(ieee->networks[j]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम libipw_networks_मुक्त(काष्ठा libipw_device *ieee)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NETWORK_COUNT; i++)
		kमुक्त(ieee->networks[i]);
पूर्ण

व्योम libipw_networks_age(काष्ठा libipw_device *ieee,
                            अचिन्हित दीर्घ age_secs)
अणु
	काष्ठा libipw_network *network = शून्य;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ age_jअगरfies = msecs_to_jअगरfies(age_secs * MSEC_PER_SEC);

	spin_lock_irqsave(&ieee->lock, flags);
	list_क्रम_each_entry(network, &ieee->network_list, list) अणु
		network->last_scanned -= age_jअगरfies;
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण
EXPORT_SYMBOL(libipw_networks_age);

अटल व्योम libipw_networks_initialize(काष्ठा libipw_device *ieee)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&ieee->network_मुक्त_list);
	INIT_LIST_HEAD(&ieee->network_list);
	क्रम (i = 0; i < MAX_NETWORK_COUNT; i++)
		list_add_tail(&ieee->networks[i]->list,
			      &ieee->network_मुक्त_list);
पूर्ण

काष्ठा net_device *alloc_libipw(पूर्णांक माप_priv, पूर्णांक monitor)
अणु
	काष्ठा libipw_device *ieee;
	काष्ठा net_device *dev;
	पूर्णांक err;

	LIBIPW_DEBUG_INFO("Initializing...\n");

	dev = alloc_etherdev(माप(काष्ठा libipw_device) + माप_priv);
	अगर (!dev)
		जाओ failed;

	ieee = netdev_priv(dev);

	ieee->dev = dev;

	अगर (!monitor) अणु
		ieee->wdev.wiphy = wiphy_new(&libipw_config_ops, 0);
		अगर (!ieee->wdev.wiphy) अणु
			LIBIPW_ERROR("Unable to allocate wiphy.\n");
			जाओ failed_मुक्त_netdev;
		पूर्ण

		ieee->dev->ieee80211_ptr = &ieee->wdev;
		ieee->wdev.अगरtype = NL80211_IFTYPE_STATION;

		/* Fill-out wiphy काष्ठाure bits we know...  Not enough info
		   here to call set_wiphy_dev or set MAC address or channel info
		   -- have to करो that in ->nकरो_init... */
		ieee->wdev.wiphy->privid = libipw_wiphy_privid;

		ieee->wdev.wiphy->max_scan_ssids = 1;
		ieee->wdev.wiphy->max_scan_ie_len = 0;
		ieee->wdev.wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION)
						| BIT(NL80211_IFTYPE_ADHOC);
	पूर्ण

	err = libipw_networks_allocate(ieee);
	अगर (err) अणु
		LIBIPW_ERROR("Unable to allocate beacon storage: %d\n", err);
		जाओ failed_मुक्त_wiphy;
	पूर्ण
	libipw_networks_initialize(ieee);

	/* Default fragmentation threshold is maximum payload size */
	ieee->fts = DEFAULT_FTS;
	ieee->rts = DEFAULT_FTS;
	ieee->scan_age = DEFAULT_MAX_SCAN_AGE;
	ieee->खोलो_wep = 1;

	/* Default to enabling full खोलो WEP with host based encrypt/decrypt */
	ieee->host_encrypt = 1;
	ieee->host_decrypt = 1;
	ieee->host_mc_decrypt = 1;

	/* Host fragmentation in Open mode. Default is enabled.
	 * Note: host fragmentation is always enabled अगर host encryption
	 * is enabled. For cards can करो hardware encryption, they must करो
	 * hardware fragmentation as well. So we करोn't need a variable
	 * like host_enc_frag. */
	ieee->host_खोलो_frag = 1;
	ieee->ieee802_1x = 1;	/* Default to supporting 802.1x */

	spin_lock_init(&ieee->lock);

	lib80211_crypt_info_init(&ieee->crypt_info, dev->name, &ieee->lock);

	ieee->wpa_enabled = 0;
	ieee->drop_unencrypted = 0;
	ieee->privacy_invoked = 0;

	वापस dev;

failed_मुक्त_wiphy:
	अगर (!monitor)
		wiphy_मुक्त(ieee->wdev.wiphy);
failed_मुक्त_netdev:
	मुक्त_netdev(dev);
failed:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(alloc_libipw);

व्योम मुक्त_libipw(काष्ठा net_device *dev, पूर्णांक monitor)
अणु
	काष्ठा libipw_device *ieee = netdev_priv(dev);

	lib80211_crypt_info_मुक्त(&ieee->crypt_info);

	libipw_networks_मुक्त(ieee);

	/* मुक्त cfg80211 resources */
	अगर (!monitor)
		wiphy_मुक्त(ieee->wdev.wiphy);

	मुक्त_netdev(dev);
पूर्ण
EXPORT_SYMBOL(मुक्त_libipw);

#अगर_घोषित CONFIG_LIBIPW_DEBUG

अटल पूर्णांक debug = 0;
u32 libipw_debug_level = 0;
EXPORT_SYMBOL_GPL(libipw_debug_level);
अटल काष्ठा proc_dir_entry *libipw_proc = शून्य;

अटल पूर्णांक debug_level_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "0x%08X\n", libipw_debug_level);
	वापस 0;
पूर्ण

अटल पूर्णांक debug_level_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, debug_level_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार debug_level_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अक्षर buf[] = "0x00000000\n";
	माप_प्रकार len = min(माप(buf) - 1, count);
	अचिन्हित दीर्घ val;

	अगर (copy_from_user(buf, buffer, len))
		वापस count;
	buf[len] = 0;
	अगर (माला_पूछो(buf, "%li", &val) != 1)
		prपूर्णांकk(KERN_INFO DRV_NAME
		       ": %s is not in hex or decimal form.\n", buf);
	अन्यथा
		libipw_debug_level = val;

	वापस strnlen(buf, len);
पूर्ण

अटल स्थिर काष्ठा proc_ops debug_level_proc_ops = अणु
	.proc_खोलो	= debug_level_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= debug_level_proc_ग_लिखो,
पूर्ण;
#पूर्ण_अगर				/* CONFIG_LIBIPW_DEBUG */

अटल पूर्णांक __init libipw_init(व्योम)
अणु
#अगर_घोषित CONFIG_LIBIPW_DEBUG
	काष्ठा proc_dir_entry *e;

	libipw_debug_level = debug;
	libipw_proc = proc_सूची_गढ़ो(DRV_PROCNAME, init_net.proc_net);
	अगर (libipw_proc == शून्य) अणु
		LIBIPW_ERROR("Unable to create " DRV_PROCNAME
				" proc directory\n");
		वापस -EIO;
	पूर्ण
	e = proc_create("debug_level", 0644, libipw_proc,
			&debug_level_proc_ops);
	अगर (!e) अणु
		हटाओ_proc_entry(DRV_PROCNAME, init_net.proc_net);
		libipw_proc = शून्य;
		वापस -EIO;
	पूर्ण
#पूर्ण_अगर				/* CONFIG_LIBIPW_DEBUG */

	prपूर्णांकk(KERN_INFO DRV_NAME ": " DRV_DESCRIPTION ", " DRV_VERSION "\n");
	prपूर्णांकk(KERN_INFO DRV_NAME ": " DRV_COPYRIGHT "\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास libipw_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_LIBIPW_DEBUG
	अगर (libipw_proc) अणु
		हटाओ_proc_entry("debug_level", libipw_proc);
		हटाओ_proc_entry(DRV_PROCNAME, init_net.proc_net);
		libipw_proc = शून्य;
	पूर्ण
#पूर्ण_अगर				/* CONFIG_LIBIPW_DEBUG */
पूर्ण

#अगर_घोषित CONFIG_LIBIPW_DEBUG
#समावेश <linux/moduleparam.h>
module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "debug output mask");
#पूर्ण_अगर				/* CONFIG_LIBIPW_DEBUG */

module_निकास(libipw_निकास);
module_init(libipw_init);
