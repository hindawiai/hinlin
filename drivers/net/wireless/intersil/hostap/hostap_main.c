<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Host AP (software wireless LAN access poपूर्णांक) driver क्रम
 * Intersil Prism2/2.5/3 - hostap.o module, common routines
 *
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <j@w1.fi>
 * Copyright (c) 2002-2005, Jouni Malinen <j@w1.fi>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/delay.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kmod.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/wireless.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/net_namespace.h>
#समावेश <net/iw_handler.h>
#समावेश <net/lib80211.h>
#समावेश <linux/uaccess.h>

#समावेश "hostap_wlan.h"
#समावेश "hostap_80211.h"
#समावेश "hostap_ap.h"
#समावेश "hostap.h"

MODULE_AUTHOR("Jouni Malinen");
MODULE_DESCRIPTION("Host AP common routines");
MODULE_LICENSE("GPL");

#घोषणा TX_TIMEOUT (2 * HZ)

#घोषणा PRISM2_MAX_FRAME_SIZE 2304
#घोषणा PRISM2_MIN_MTU 256
/* FIX: */
#घोषणा PRISM2_MAX_MTU (PRISM2_MAX_FRAME_SIZE - (6 /* LLC */ + 8 /* WEP */))


काष्ठा net_device * hostap_add_पूर्णांकerface(काष्ठा local_info *local,
					 पूर्णांक type, पूर्णांक rtnl_locked,
					 स्थिर अक्षर *prefix,
					 स्थिर अक्षर *name)
अणु
	काष्ठा net_device *dev, *mdev;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	पूर्णांक ret;

	dev = alloc_etherdev(माप(काष्ठा hostap_पूर्णांकerface));
	अगर (dev == शून्य)
		वापस शून्य;

	अगरace = netdev_priv(dev);
	अगरace->dev = dev;
	अगरace->local = local;
	अगरace->type = type;
	list_add(&अगरace->list, &local->hostap_पूर्णांकerfaces);

	mdev = local->dev;
	eth_hw_addr_inherit(dev, mdev);
	dev->base_addr = mdev->base_addr;
	dev->irq = mdev->irq;
	dev->mem_start = mdev->mem_start;
	dev->mem_end = mdev->mem_end;

	hostap_setup_dev(dev, local, type);
	dev->needs_मुक्त_netdev = true;

	प्र_लिखो(dev->name, "%s%s", prefix, name);
	अगर (!rtnl_locked)
		rtnl_lock();

	SET_NETDEV_DEV(dev, mdev->dev.parent);
	ret = रेजिस्टर_netdevice(dev);

	अगर (!rtnl_locked)
		rtnl_unlock();

	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: failed to add new netdevice!\n",
		       dev->name);
		मुक्त_netdev(dev);
		वापस शून्य;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: registered netdevice %s\n",
	       mdev->name, dev->name);

	वापस dev;
पूर्ण


व्योम hostap_हटाओ_पूर्णांकerface(काष्ठा net_device *dev, पूर्णांक rtnl_locked,
			     पूर्णांक हटाओ_from_list)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;

	अगर (!dev)
		वापस;

	अगरace = netdev_priv(dev);

	अगर (हटाओ_from_list) अणु
		list_del(&अगरace->list);
	पूर्ण

	अगर (dev == अगरace->local->ddev)
		अगरace->local->ddev = शून्य;
	अन्यथा अगर (dev == अगरace->local->apdev)
		अगरace->local->apdev = शून्य;
	अन्यथा अगर (dev == अगरace->local->stadev)
		अगरace->local->stadev = शून्य;

	अगर (rtnl_locked)
		unरेजिस्टर_netdevice(dev);
	अन्यथा
		unरेजिस्टर_netdev(dev);

	/* 'dev->needs_free_netdev = true' implies device data, including
	 * निजी data, will be मुक्तd when the device is हटाओd */
पूर्ण


अटल अंतरभूत पूर्णांक prism2_wds_special_addr(u8 *addr)
अणु
	अगर (addr[0] || addr[1] || addr[2] || addr[3] || addr[4] || addr[5])
		वापस 0;

	वापस 1;
पूर्ण


पूर्णांक prism2_wds_add(local_info_t *local, u8 *remote_addr,
		   पूर्णांक rtnl_locked)
अणु
	काष्ठा net_device *dev;
	काष्ठा list_head *ptr;
	काष्ठा hostap_पूर्णांकerface *अगरace, *empty, *match;

	empty = match = शून्य;
	पढ़ो_lock_bh(&local->अगरace_lock);
	list_क्रम_each(ptr, &local->hostap_पूर्णांकerfaces) अणु
		अगरace = list_entry(ptr, काष्ठा hostap_पूर्णांकerface, list);
		अगर (अगरace->type != HOSTAP_INTERFACE_WDS)
			जारी;

		अगर (prism2_wds_special_addr(अगरace->u.wds.remote_addr))
			empty = अगरace;
		अन्यथा अगर (ether_addr_equal(अगरace->u.wds.remote_addr, remote_addr)) अणु
			match = अगरace;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!match && empty && !prism2_wds_special_addr(remote_addr)) अणु
		/* take pre-allocated entry पूर्णांकo use */
		स_नकल(empty->u.wds.remote_addr, remote_addr, ETH_ALEN);
		पढ़ो_unlock_bh(&local->अगरace_lock);
		prपूर्णांकk(KERN_DEBUG "%s: using pre-allocated WDS netdevice %s\n",
		       local->dev->name, empty->dev->name);
		वापस 0;
	पूर्ण
	पढ़ो_unlock_bh(&local->अगरace_lock);

	अगर (!prism2_wds_special_addr(remote_addr)) अणु
		अगर (match)
			वापस -EEXIST;
		hostap_add_sta(local->ap, remote_addr);
	पूर्ण

	अगर (local->wds_connections >= local->wds_max_connections)
		वापस -ENOBUFS;

	/* verअगरy that there is room क्रम wds# postfix in the पूर्णांकerface name */
	अगर (म_माप(local->dev->name) >= IFNAMSIZ - 5) अणु
		prपूर्णांकk(KERN_DEBUG "'%s' too long base device name\n",
		       local->dev->name);
		वापस -EINVAL;
	पूर्ण

	dev = hostap_add_पूर्णांकerface(local, HOSTAP_INTERFACE_WDS, rtnl_locked,
				   local->ddev->name, "wds%d");
	अगर (dev == शून्य)
		वापस -ENOMEM;

	अगरace = netdev_priv(dev);
	स_नकल(अगरace->u.wds.remote_addr, remote_addr, ETH_ALEN);

	local->wds_connections++;

	वापस 0;
पूर्ण


पूर्णांक prism2_wds_del(local_info_t *local, u8 *remote_addr,
		   पूर्णांक rtnl_locked, पूर्णांक करो_not_हटाओ)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *ptr;
	काष्ठा hostap_पूर्णांकerface *अगरace, *selected = शून्य;

	ग_लिखो_lock_irqsave(&local->अगरace_lock, flags);
	list_क्रम_each(ptr, &local->hostap_पूर्णांकerfaces) अणु
		अगरace = list_entry(ptr, काष्ठा hostap_पूर्णांकerface, list);
		अगर (अगरace->type != HOSTAP_INTERFACE_WDS)
			जारी;

		अगर (ether_addr_equal(अगरace->u.wds.remote_addr, remote_addr)) अणु
			selected = अगरace;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (selected && !करो_not_हटाओ)
		list_del(&selected->list);
	ग_लिखो_unlock_irqrestore(&local->अगरace_lock, flags);

	अगर (selected) अणु
		अगर (करो_not_हटाओ)
			eth_zero_addr(selected->u.wds.remote_addr);
		अन्यथा अणु
			hostap_हटाओ_पूर्णांकerface(selected->dev, rtnl_locked, 0);
			local->wds_connections--;
		पूर्ण
	पूर्ण

	वापस selected ? 0 : -ENODEV;
पूर्ण


u16 hostap_tx_callback_रेजिस्टर(local_info_t *local,
				व्योम (*func)(काष्ठा sk_buff *, पूर्णांक ok, व्योम *),
				व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hostap_tx_callback_info *entry;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (entry == शून्य)
		वापस 0;

	entry->func = func;
	entry->data = data;

	spin_lock_irqsave(&local->lock, flags);
	entry->idx = local->tx_callback ? local->tx_callback->idx + 1 : 1;
	entry->next = local->tx_callback;
	local->tx_callback = entry;
	spin_unlock_irqrestore(&local->lock, flags);

	वापस entry->idx;
पूर्ण


पूर्णांक hostap_tx_callback_unरेजिस्टर(local_info_t *local, u16 idx)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hostap_tx_callback_info *cb, *prev = शून्य;

	spin_lock_irqsave(&local->lock, flags);
	cb = local->tx_callback;
	जबतक (cb != शून्य && cb->idx != idx) अणु
		prev = cb;
		cb = cb->next;
	पूर्ण
	अगर (cb) अणु
		अगर (prev == शून्य)
			local->tx_callback = cb->next;
		अन्यथा
			prev->next = cb->next;
		kमुक्त(cb);
	पूर्ण
	spin_unlock_irqrestore(&local->lock, flags);

	वापस cb ? 0 : -1;
पूर्ण


/* val is in host byte order */
पूर्णांक hostap_set_word(काष्ठा net_device *dev, पूर्णांक rid, u16 val)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	__le16 पंचांगp = cpu_to_le16(val);
	अगरace = netdev_priv(dev);
	वापस अगरace->local->func->set_rid(dev, rid, &पंचांगp, 2);
पूर्ण


पूर्णांक hostap_set_string(काष्ठा net_device *dev, पूर्णांक rid, स्थिर अक्षर *val)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	अक्षर buf[MAX_SSID_LEN + 2];
	पूर्णांक len;

	अगरace = netdev_priv(dev);
	len = म_माप(val);
	अगर (len > MAX_SSID_LEN)
		वापस -1;
	स_रखो(buf, 0, माप(buf));
	buf[0] = len; /* little endian 16 bit word */
	स_नकल(buf + 2, val, len);

	वापस अगरace->local->func->set_rid(dev, rid, &buf, MAX_SSID_LEN + 2);
पूर्ण


u16 hostap_get_porttype(local_info_t *local)
अणु
	अगर (local->iw_mode == IW_MODE_ADHOC && local->pseuकरो_adhoc)
		वापस HFA384X_PORTTYPE_PSEUDO_IBSS;
	अगर (local->iw_mode == IW_MODE_ADHOC)
		वापस HFA384X_PORTTYPE_IBSS;
	अगर (local->iw_mode == IW_MODE_INFRA)
		वापस HFA384X_PORTTYPE_BSS;
	अगर (local->iw_mode == IW_MODE_REPEAT)
		वापस HFA384X_PORTTYPE_WDS;
	अगर (local->iw_mode == IW_MODE_MONITOR)
		वापस HFA384X_PORTTYPE_PSEUDO_IBSS;
	वापस HFA384X_PORTTYPE_HOSTAP;
पूर्ण


पूर्णांक hostap_set_encryption(local_info_t *local)
अणु
	u16 val, old_val;
	पूर्णांक i, keylen, len, idx;
	अक्षर keybuf[WEP_KEY_LEN + 1];
	क्रमागत अणु NONE, WEP, OTHER पूर्ण encrypt_type;

	idx = local->crypt_info.tx_keyidx;
	अगर (local->crypt_info.crypt[idx] == शून्य ||
	    local->crypt_info.crypt[idx]->ops == शून्य)
		encrypt_type = NONE;
	अन्यथा अगर (म_भेद(local->crypt_info.crypt[idx]->ops->name, "WEP") == 0)
		encrypt_type = WEP;
	अन्यथा
		encrypt_type = OTHER;

	अगर (local->func->get_rid(local->dev, HFA384X_RID_CNFWEPFLAGS, &val, 2,
				 1) < 0) अणु
		prपूर्णांकk(KERN_DEBUG "Could not read current WEP flags.\n");
		जाओ fail;
	पूर्ण
	le16_to_cpus(&val);
	old_val = val;

	अगर (encrypt_type != NONE || local->privacy_invoked)
		val |= HFA384X_WEPFLAGS_PRIVACYINVOKED;
	अन्यथा
		val &= ~HFA384X_WEPFLAGS_PRIVACYINVOKED;

	अगर (local->खोलो_wep || encrypt_type == NONE ||
	    ((local->ieee_802_1x || local->wpa) && local->host_decrypt))
		val &= ~HFA384X_WEPFLAGS_EXCLUDEUNENCRYPTED;
	अन्यथा
		val |= HFA384X_WEPFLAGS_EXCLUDEUNENCRYPTED;

	अगर ((encrypt_type != NONE || local->privacy_invoked) &&
	    (encrypt_type == OTHER || local->host_encrypt))
		val |= HFA384X_WEPFLAGS_HOSTENCRYPT;
	अन्यथा
		val &= ~HFA384X_WEPFLAGS_HOSTENCRYPT;
	अगर ((encrypt_type != NONE || local->privacy_invoked) &&
	    (encrypt_type == OTHER || local->host_decrypt))
		val |= HFA384X_WEPFLAGS_HOSTDECRYPT;
	अन्यथा
		val &= ~HFA384X_WEPFLAGS_HOSTDECRYPT;

	अगर (val != old_val &&
	    hostap_set_word(local->dev, HFA384X_RID_CNFWEPFLAGS, val)) अणु
		prपूर्णांकk(KERN_DEBUG "Could not write new WEP flags (0x%x)\n",
		       val);
		जाओ fail;
	पूर्ण

	अगर (encrypt_type != WEP)
		वापस 0;

	/* 104-bit support seems to require that all the keys are set to the
	 * same keylen */
	keylen = 6; /* first 5 octets */
	len = local->crypt_info.crypt[idx]->ops->get_key(keybuf, माप(keybuf), शून्य,
							   local->crypt_info.crypt[idx]->priv);
	अगर (idx >= 0 && idx < WEP_KEYS && len > 5)
		keylen = WEP_KEY_LEN + 1; /* first 13 octets */

	क्रम (i = 0; i < WEP_KEYS; i++) अणु
		स_रखो(keybuf, 0, माप(keybuf));
		अगर (local->crypt_info.crypt[i]) अणु
			(व्योम) local->crypt_info.crypt[i]->ops->get_key(
				keybuf, माप(keybuf),
				शून्य, local->crypt_info.crypt[i]->priv);
		पूर्ण
		अगर (local->func->set_rid(local->dev,
					 HFA384X_RID_CNFDEFAULTKEY0 + i,
					 keybuf, keylen)) अणु
			prपूर्णांकk(KERN_DEBUG "Could not set key %d (len=%d)\n",
			       i, keylen);
			जाओ fail;
		पूर्ण
	पूर्ण
	अगर (hostap_set_word(local->dev, HFA384X_RID_CNFWEPDEFAULTKEYID, idx)) अणु
		prपूर्णांकk(KERN_DEBUG "Could not set default keyid %d\n", idx);
		जाओ fail;
	पूर्ण

	वापस 0;

 fail:
	prपूर्णांकk(KERN_DEBUG "%s: encryption setup failed\n", local->dev->name);
	वापस -1;
पूर्ण


पूर्णांक hostap_set_antsel(local_info_t *local)
अणु
	u16 val;
	पूर्णांक ret = 0;

	अगर (local->antsel_tx != HOSTAP_ANTSEL_DO_NOT_TOUCH &&
	    local->func->cmd(local->dev, HFA384X_CMDCODE_READMIF,
			     HFA386X_CR_TX_CONFIGURE,
			     शून्य, &val) == 0) अणु
		val &= ~(BIT(2) | BIT(1));
		चयन (local->antsel_tx) अणु
		हाल HOSTAP_ANTSEL_DIVERSITY:
			val |= BIT(1);
			अवरोध;
		हाल HOSTAP_ANTSEL_LOW:
			अवरोध;
		हाल HOSTAP_ANTSEL_HIGH:
			val |= BIT(2);
			अवरोध;
		पूर्ण

		अगर (local->func->cmd(local->dev, HFA384X_CMDCODE_WRITEMIF,
				     HFA386X_CR_TX_CONFIGURE, &val, शून्य)) अणु
			prपूर्णांकk(KERN_INFO "%s: setting TX AntSel failed\n",
			       local->dev->name);
			ret = -1;
		पूर्ण
	पूर्ण

	अगर (local->antsel_rx != HOSTAP_ANTSEL_DO_NOT_TOUCH &&
	    local->func->cmd(local->dev, HFA384X_CMDCODE_READMIF,
			     HFA386X_CR_RX_CONFIGURE,
			     शून्य, &val) == 0) अणु
		val &= ~(BIT(1) | BIT(0));
		चयन (local->antsel_rx) अणु
		हाल HOSTAP_ANTSEL_DIVERSITY:
			अवरोध;
		हाल HOSTAP_ANTSEL_LOW:
			val |= BIT(0);
			अवरोध;
		हाल HOSTAP_ANTSEL_HIGH:
			val |= BIT(0) | BIT(1);
			अवरोध;
		पूर्ण

		अगर (local->func->cmd(local->dev, HFA384X_CMDCODE_WRITEMIF,
				     HFA386X_CR_RX_CONFIGURE, &val, शून्य)) अणु
			prपूर्णांकk(KERN_INFO "%s: setting RX AntSel failed\n",
			       local->dev->name);
			ret = -1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण


पूर्णांक hostap_set_roaming(local_info_t *local)
अणु
	u16 val;

	चयन (local->host_roaming) अणु
	हाल 1:
		val = HFA384X_ROAMING_HOST;
		अवरोध;
	हाल 2:
		val = HFA384X_ROAMING_DISABLED;
		अवरोध;
	हाल 0:
	शेष:
		val = HFA384X_ROAMING_FIRMWARE;
		अवरोध;
	पूर्ण

	वापस hostap_set_word(local->dev, HFA384X_RID_CNFROAMINGMODE, val);
पूर्ण


पूर्णांक hostap_set_auth_algs(local_info_t *local)
अणु
	पूर्णांक val = local->auth_algs;
	/* At least STA f/w v0.6.2 seems to have issues with cnfAuthentication
	 * set to include both Open and Shared Key flags. It tries to use
	 * Shared Key authentication in that हाल even अगर WEP keys are not
	 * configured.. STA f/w v0.7.6 is able to handle such configuration,
	 * but it is unknown when this was fixed between 0.6.2 .. 0.7.6. */
	अगर (local->sta_fw_ver < PRISM2_FW_VER(0,7,0) &&
	    val != PRISM2_AUTH_OPEN && val != PRISM2_AUTH_SHARED_KEY)
		val = PRISM2_AUTH_OPEN;

	अगर (hostap_set_word(local->dev, HFA384X_RID_CNFAUTHENTICATION, val)) अणु
		prपूर्णांकk(KERN_INFO "%s: cnfAuthentication setting to 0x%x "
		       "failed\n", local->dev->name, local->auth_algs);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


व्योम hostap_dump_rx_header(स्थिर अक्षर *name, स्थिर काष्ठा hfa384x_rx_frame *rx)
अणु
	u16 status, fc;

	status = __le16_to_cpu(rx->status);

	prपूर्णांकk(KERN_DEBUG "%s: RX status=0x%04x (port=%d, type=%d, "
	       "fcserr=%d) silence=%d signal=%d rate=%d rxflow=%d; "
	       "jiffies=%ld\n",
	       name, status, (status >> 8) & 0x07, status >> 13, status & 1,
	       rx->silence, rx->संकेत, rx->rate, rx->rxflow, jअगरfies);

	fc = __le16_to_cpu(rx->frame_control);
	prपूर्णांकk(KERN_DEBUG "   FC=0x%04x (type=%d:%d) dur=0x%04x seq=0x%04x "
	       "data_len=%d%s%s\n",
	       fc, (fc & IEEE80211_FCTL_FTYPE) >> 2,
	       (fc & IEEE80211_FCTL_STYPE) >> 4,
	       __le16_to_cpu(rx->duration_id), __le16_to_cpu(rx->seq_ctrl),
	       __le16_to_cpu(rx->data_len),
	       fc & IEEE80211_FCTL_TODS ? " [ToDS]" : "",
	       fc & IEEE80211_FCTL_FROMDS ? " [FromDS]" : "");

	prपूर्णांकk(KERN_DEBUG "   A1=%pM A2=%pM A3=%pM A4=%pM\n",
	       rx->addr1, rx->addr2, rx->addr3, rx->addr4);

	prपूर्णांकk(KERN_DEBUG "   dst=%pM src=%pM len=%d\n",
	       rx->dst_addr, rx->src_addr,
	       __be16_to_cpu(rx->len));
पूर्ण


व्योम hostap_dump_tx_header(स्थिर अक्षर *name, स्थिर काष्ठा hfa384x_tx_frame *tx)
अणु
	u16 fc;

	prपूर्णांकk(KERN_DEBUG "%s: TX status=0x%04x retry_count=%d tx_rate=%d "
	       "tx_control=0x%04x; jiffies=%ld\n",
	       name, __le16_to_cpu(tx->status), tx->retry_count, tx->tx_rate,
	       __le16_to_cpu(tx->tx_control), jअगरfies);

	fc = __le16_to_cpu(tx->frame_control);
	prपूर्णांकk(KERN_DEBUG "   FC=0x%04x (type=%d:%d) dur=0x%04x seq=0x%04x "
	       "data_len=%d%s%s\n",
	       fc, (fc & IEEE80211_FCTL_FTYPE) >> 2,
	       (fc & IEEE80211_FCTL_STYPE) >> 4,
	       __le16_to_cpu(tx->duration_id), __le16_to_cpu(tx->seq_ctrl),
	       __le16_to_cpu(tx->data_len),
	       fc & IEEE80211_FCTL_TODS ? " [ToDS]" : "",
	       fc & IEEE80211_FCTL_FROMDS ? " [FromDS]" : "");

	prपूर्णांकk(KERN_DEBUG "   A1=%pM A2=%pM A3=%pM A4=%pM\n",
	       tx->addr1, tx->addr2, tx->addr3, tx->addr4);

	prपूर्णांकk(KERN_DEBUG "   dst=%pM src=%pM len=%d\n",
	       tx->dst_addr, tx->src_addr,
	       __be16_to_cpu(tx->len));
पूर्ण


अटल पूर्णांक hostap_80211_header_parse(स्थिर काष्ठा sk_buff *skb,
				     अचिन्हित अक्षर *haddr)
अणु
	स_नकल(haddr, skb_mac_header(skb) + 10, ETH_ALEN); /* addr2 */
	वापस ETH_ALEN;
पूर्ण


पूर्णांक hostap_80211_get_hdrlen(__le16 fc)
अणु
	अगर (ieee80211_is_data(fc) && ieee80211_has_a4 (fc))
		वापस 30; /* Addr4 */
	अन्यथा अगर (ieee80211_is_cts(fc) || ieee80211_is_ack(fc))
		वापस 10;
	अन्यथा अगर (ieee80211_is_ctl(fc))
		वापस 16;

	वापस 24;
पूर्ण


अटल पूर्णांक prism2_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	PDEBUG(DEBUG_FLOW, "%s: prism2_close\n", dev->name);

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (dev == local->ddev) अणु
		prism2_sta_deauth(local, WLAN_REASON_DEAUTH_LEAVING);
	पूर्ण
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	अगर (!local->hostapd && dev == local->dev &&
	    (!local->func->card_present || local->func->card_present(local)) &&
	    local->hw_पढ़ोy && local->ap && local->iw_mode == IW_MODE_MASTER)
		hostap_deauth_all_stas(dev, local->ap, 1);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	अगर (dev == local->dev) अणु
		local->func->hw_shutकरोwn(dev, HOSTAP_HW_ENABLE_CMDCOMPL);
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		netअगर_stop_queue(dev);
		netअगर_device_detach(dev);
	पूर्ण

	cancel_work_sync(&local->reset_queue);
	cancel_work_sync(&local->set_multicast_list_queue);
	cancel_work_sync(&local->set_tim_queue);
#अगर_अघोषित PRISM2_NO_STATION_MODES
	cancel_work_sync(&local->info_queue);
#पूर्ण_अगर
	cancel_work_sync(&local->comms_qual_update);

	module_put(local->hw_module);

	local->num_dev_खोलो--;

	अगर (dev != local->dev && local->dev->flags & IFF_UP &&
	    local->master_dev_स्वतः_खोलो && local->num_dev_खोलो == 1) अणु
		/* Close master radio पूर्णांकerface स्वतःmatically अगर it was also
		 * खोलोed स्वतःmatically and we are now closing the last
		 * reमुख्यing non-master device. */
		dev_बंद(local->dev);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	PDEBUG(DEBUG_FLOW, "%s: prism2_open\n", dev->name);

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->no_pri) अणु
		prपूर्णांकk(KERN_DEBUG "%s: could not set interface UP - no PRI "
		       "f/w\n", dev->name);
		वापस -ENODEV;
	पूर्ण

	अगर ((local->func->card_present && !local->func->card_present(local)) ||
	    local->hw_करोwnloading)
		वापस -ENODEV;

	अगर (!try_module_get(local->hw_module))
		वापस -ENODEV;
	local->num_dev_खोलो++;

	अगर (!local->dev_enabled && local->func->hw_enable(dev, 1)) अणु
		prपूर्णांकk(KERN_WARNING "%s: could not enable MAC port\n",
		       dev->name);
		prism2_बंद(dev);
		वापस -ENODEV;
	पूर्ण
	अगर (!local->dev_enabled)
		prism2_callback(local, PRISM2_CALLBACK_ENABLE);
	local->dev_enabled = 1;

	अगर (dev != local->dev && !(local->dev->flags & IFF_UP)) अणु
		/* Master radio पूर्णांकerface is needed क्रम all operation, so खोलो
		 * it स्वतःmatically when any भव net_device is खोलोed. */
		local->master_dev_स्वतः_खोलो = 1;
		dev_खोलो(local->dev, शून्य);
	पूर्ण

	netअगर_device_attach(dev);
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा list_head *ptr;
	काष्ठा sockaddr *addr = p;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->set_rid(dev, HFA384X_RID_CNFOWNMACADDR, addr->sa_data,
				 ETH_ALEN) < 0 || local->func->reset_port(dev))
		वापस -EINVAL;

	पढ़ो_lock_bh(&local->अगरace_lock);
	list_क्रम_each(ptr, &local->hostap_पूर्णांकerfaces) अणु
		अगरace = list_entry(ptr, काष्ठा hostap_पूर्णांकerface, list);
		स_नकल(अगरace->dev->dev_addr, addr->sa_data, ETH_ALEN);
	पूर्ण
	स_नकल(local->dev->dev_addr, addr->sa_data, ETH_ALEN);
	पढ़ो_unlock_bh(&local->अगरace_lock);

	वापस 0;
पूर्ण


/* TODO: to be further implemented as soon as Prism2 fully supports
 *       GroupAddresses and correct करोcumentation is available */
व्योम hostap_set_multicast_list_queue(काष्ठा work_काष्ठा *work)
अणु
	local_info_t *local =
		container_of(work, local_info_t, set_multicast_list_queue);
	काष्ठा net_device *dev = local->dev;

	अगर (hostap_set_word(dev, HFA384X_RID_PROMISCUOUSMODE,
			    local->is_promisc)) अणु
		prपूर्णांकk(KERN_INFO "%s: %sabling promiscuous mode failed\n",
		       dev->name, local->is_promisc ? "en" : "dis");
	पूर्ण
पूर्ण


अटल व्योम hostap_set_multicast_list(काष्ठा net_device *dev)
अणु
#अगर 0
	/* FIX: promiscuous mode seems to be causing a lot of problems with
	 * some station firmware versions (FCSErr frames, invalid MACPort, etc.
	 * corrupted incoming frames). This code is now commented out जबतक the
	 * problems are investigated. */
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	अगर ((dev->flags & IFF_ALLMULTI) || (dev->flags & IFF_PROMISC)) अणु
		local->is_promisc = 1;
	पूर्ण अन्यथा अणु
		local->is_promisc = 0;
	पूर्ण

	schedule_work(&local->set_multicast_list_queue);
#पूर्ण_अगर
पूर्ण


अटल व्योम prism2_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा hfa384x_regs regs;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	prपूर्णांकk(KERN_WARNING "%s Tx timed out! Resetting card\n", dev->name);
	netअगर_stop_queue(local->dev);

	local->func->पढ़ो_regs(dev, &regs);
	prपूर्णांकk(KERN_DEBUG "%s: CMD=%04x EVSTAT=%04x "
	       "OFFSET0=%04x OFFSET1=%04x SWSUPPORT0=%04x\n",
	       dev->name, regs.cmd, regs.evstat, regs.offset0, regs.offset1,
	       regs.swsupport0);

	local->func->schedule_reset(local);
पूर्ण

स्थिर काष्ठा header_ops hostap_80211_ops = अणु
	.create		= eth_header,
	.cache		= eth_header_cache,
	.cache_update	= eth_header_cache_update,
	.parse		= hostap_80211_header_parse,
पूर्ण;
EXPORT_SYMBOL(hostap_80211_ops);


अटल स्थिर काष्ठा net_device_ops hostap_netdev_ops = अणु
	.nकरो_start_xmit		= hostap_data_start_xmit,

	.nकरो_खोलो		= prism2_खोलो,
	.nकरो_stop		= prism2_बंद,
	.nकरो_करो_ioctl		= hostap_ioctl,
	.nकरो_set_mac_address	= prism2_set_mac_address,
	.nकरो_set_rx_mode	= hostap_set_multicast_list,
	.nकरो_tx_समयout 	= prism2_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops hostap_mgmt_netdev_ops = अणु
	.nकरो_start_xmit		= hostap_mgmt_start_xmit,

	.nकरो_खोलो		= prism2_खोलो,
	.nकरो_stop		= prism2_बंद,
	.nकरो_करो_ioctl		= hostap_ioctl,
	.nकरो_set_mac_address	= prism2_set_mac_address,
	.nकरो_set_rx_mode	= hostap_set_multicast_list,
	.nकरो_tx_समयout 	= prism2_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops hostap_master_ops = अणु
	.nकरो_start_xmit 	= hostap_master_start_xmit,

	.nकरो_खोलो		= prism2_खोलो,
	.nकरो_stop		= prism2_बंद,
	.nकरो_करो_ioctl		= hostap_ioctl,
	.nकरो_set_mac_address	= prism2_set_mac_address,
	.nकरो_set_rx_mode	= hostap_set_multicast_list,
	.nकरो_tx_समयout 	= prism2_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

व्योम hostap_setup_dev(काष्ठा net_device *dev, local_info_t *local,
		      पूर्णांक type)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;

	अगरace = netdev_priv(dev);
	ether_setup(dev);
	dev->min_mtu = PRISM2_MIN_MTU;
	dev->max_mtu = PRISM2_MAX_MTU;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;

	/* kernel callbacks */
	अगर (अगरace) अणु
		/* Currently, we poपूर्णांक to the proper spy_data only on
		 * the मुख्य_dev. This could be fixed. Jean II */
		अगरace->wireless_data.spy_data = &अगरace->spy_data;
		dev->wireless_data = &अगरace->wireless_data;
	पूर्ण
	dev->wireless_handlers = &hostap_iw_handler_def;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	चयन(type) अणु
	हाल HOSTAP_INTERFACE_AP:
		dev->priv_flags |= IFF_NO_QUEUE;	/* use मुख्य radio device queue */
		dev->netdev_ops = &hostap_mgmt_netdev_ops;
		dev->type = ARPHRD_IEEE80211;
		dev->header_ops = &hostap_80211_ops;
		अवरोध;
	हाल HOSTAP_INTERFACE_MASTER:
		dev->netdev_ops = &hostap_master_ops;
		अवरोध;
	शेष:
		dev->priv_flags |= IFF_NO_QUEUE;	/* use मुख्य radio device queue */
		dev->netdev_ops = &hostap_netdev_ops;
	पूर्ण

	dev->mtu = local->mtu;


	dev->ethtool_ops = &prism2_ethtool_ops;

पूर्ण

अटल पूर्णांक hostap_enable_hostapd(local_info_t *local, पूर्णांक rtnl_locked)
अणु
	काष्ठा net_device *dev = local->dev;

	अगर (local->apdev)
		वापस -EEXIST;

	prपूर्णांकk(KERN_DEBUG "%s: enabling hostapd mode\n", dev->name);

	local->apdev = hostap_add_पूर्णांकerface(local, HOSTAP_INTERFACE_AP,
					    rtnl_locked, local->ddev->name,
					    "ap");
	अगर (local->apdev == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण


अटल पूर्णांक hostap_disable_hostapd(local_info_t *local, पूर्णांक rtnl_locked)
अणु
	काष्ठा net_device *dev = local->dev;

	prपूर्णांकk(KERN_DEBUG "%s: disabling hostapd mode\n", dev->name);

	hostap_हटाओ_पूर्णांकerface(local->apdev, rtnl_locked, 1);
	local->apdev = शून्य;

	वापस 0;
पूर्ण


अटल पूर्णांक hostap_enable_hostapd_sta(local_info_t *local, पूर्णांक rtnl_locked)
अणु
	काष्ठा net_device *dev = local->dev;

	अगर (local->stadev)
		वापस -EEXIST;

	prपूर्णांकk(KERN_DEBUG "%s: enabling hostapd STA mode\n", dev->name);

	local->stadev = hostap_add_पूर्णांकerface(local, HOSTAP_INTERFACE_STA,
					     rtnl_locked, local->ddev->name,
					     "sta");
	अगर (local->stadev == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण


अटल पूर्णांक hostap_disable_hostapd_sta(local_info_t *local, पूर्णांक rtnl_locked)
अणु
	काष्ठा net_device *dev = local->dev;

	prपूर्णांकk(KERN_DEBUG "%s: disabling hostapd mode\n", dev->name);

	hostap_हटाओ_पूर्णांकerface(local->stadev, rtnl_locked, 1);
	local->stadev = शून्य;

	वापस 0;
पूर्ण


पूर्णांक hostap_set_hostapd(local_info_t *local, पूर्णांक val, पूर्णांक rtnl_locked)
अणु
	पूर्णांक ret;

	अगर (val < 0 || val > 1)
		वापस -EINVAL;

	अगर (local->hostapd == val)
		वापस 0;

	अगर (val) अणु
		ret = hostap_enable_hostapd(local, rtnl_locked);
		अगर (ret == 0)
			local->hostapd = 1;
	पूर्ण अन्यथा अणु
		local->hostapd = 0;
		ret = hostap_disable_hostapd(local, rtnl_locked);
		अगर (ret != 0)
			local->hostapd = 1;
	पूर्ण

	वापस ret;
पूर्ण


पूर्णांक hostap_set_hostapd_sta(local_info_t *local, पूर्णांक val, पूर्णांक rtnl_locked)
अणु
	पूर्णांक ret;

	अगर (val < 0 || val > 1)
		वापस -EINVAL;

	अगर (local->hostapd_sta == val)
		वापस 0;

	अगर (val) अणु
		ret = hostap_enable_hostapd_sta(local, rtnl_locked);
		अगर (ret == 0)
			local->hostapd_sta = 1;
	पूर्ण अन्यथा अणु
		local->hostapd_sta = 0;
		ret = hostap_disable_hostapd_sta(local, rtnl_locked);
		अगर (ret != 0)
			local->hostapd_sta = 1;
	पूर्ण


	वापस ret;
पूर्ण


पूर्णांक prism2_update_comms_qual(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक ret = 0;
	काष्ठा hfa384x_comms_quality sq;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	अगर (!local->sta_fw_ver)
		ret = -1;
	अन्यथा अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,3,1)) अणु
		अगर (local->func->get_rid(local->dev,
					 HFA384X_RID_DBMCOMMSQUALITY,
					 &sq, माप(sq), 1) >= 0) अणु
			local->comms_qual = (s16) le16_to_cpu(sq.comm_qual);
			local->avg_संकेत = (s16) le16_to_cpu(sq.संकेत_level);
			local->avg_noise = (s16) le16_to_cpu(sq.noise_level);
			local->last_comms_qual_update = jअगरfies;
		पूर्ण अन्यथा
			ret = -1;
	पूर्ण अन्यथा अणु
		अगर (local->func->get_rid(local->dev, HFA384X_RID_COMMSQUALITY,
					 &sq, माप(sq), 1) >= 0) अणु
			local->comms_qual = le16_to_cpu(sq.comm_qual);
			local->avg_संकेत = HFA384X_LEVEL_TO_dBm(
				le16_to_cpu(sq.संकेत_level));
			local->avg_noise = HFA384X_LEVEL_TO_dBm(
				le16_to_cpu(sq.noise_level));
			local->last_comms_qual_update = jअगरfies;
		पूर्ण अन्यथा
			ret = -1;
	पूर्ण

	वापस ret;
पूर्ण


पूर्णांक prism2_sta_send_mgmt(local_info_t *local, u8 *dst, u16 stype,
			 u8 *body, माप_प्रकार bodylen)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hostap_ieee80211_mgmt *mgmt;
	काष्ठा hostap_skb_tx_data *meta;
	काष्ठा net_device *dev = local->dev;

	skb = dev_alloc_skb(IEEE80211_MGMT_HDR_LEN + bodylen);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	mgmt = skb_put_zero(skb, IEEE80211_MGMT_HDR_LEN);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT | stype);
	स_नकल(mgmt->da, dst, ETH_ALEN);
	स_नकल(mgmt->sa, dev->dev_addr, ETH_ALEN);
	स_नकल(mgmt->bssid, dst, ETH_ALEN);
	अगर (body)
		skb_put_data(skb, body, bodylen);

	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
	स_रखो(meta, 0, माप(*meta));
	meta->magic = HOSTAP_SKB_TX_DATA_MAGIC;
	meta->अगरace = netdev_priv(dev);

	skb->dev = dev;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	dev_queue_xmit(skb);

	वापस 0;
पूर्ण


पूर्णांक prism2_sta_deauth(local_info_t *local, u16 reason)
अणु
	जोड़ iwreq_data wrqu;
	पूर्णांक ret;
	__le16 val = cpu_to_le16(reason);

	अगर (local->iw_mode != IW_MODE_INFRA ||
	    is_zero_ether_addr(local->bssid) ||
	    ether_addr_equal(local->bssid, "\x44\x44\x44\x44\x44\x44"))
		वापस 0;

	ret = prism2_sta_send_mgmt(local, local->bssid, IEEE80211_STYPE_DEAUTH,
				   (u8 *) &val, 2);
	eth_zero_addr(wrqu.ap_addr.sa_data);
	wireless_send_event(local->dev, SIOCGIWAP, &wrqu, शून्य);
	वापस ret;
पूर्ण


काष्ठा proc_dir_entry *hostap_proc;

अटल पूर्णांक __init hostap_init(व्योम)
अणु
	अगर (init_net.proc_net != शून्य) अणु
		hostap_proc = proc_सूची_गढ़ो("hostap", init_net.proc_net);
		अगर (!hostap_proc)
			prपूर्णांकk(KERN_WARNING "Failed to mkdir "
			       "/proc/net/hostap\n");
	पूर्ण अन्यथा
		hostap_proc = शून्य;

	वापस 0;
पूर्ण


अटल व्योम __निकास hostap_निकास(व्योम)
अणु
	अगर (hostap_proc != शून्य) अणु
		hostap_proc = शून्य;
		हटाओ_proc_entry("hostap", init_net.proc_net);
	पूर्ण
पूर्ण


EXPORT_SYMBOL(hostap_set_word);
EXPORT_SYMBOL(hostap_set_string);
EXPORT_SYMBOL(hostap_get_porttype);
EXPORT_SYMBOL(hostap_set_encryption);
EXPORT_SYMBOL(hostap_set_antsel);
EXPORT_SYMBOL(hostap_set_roaming);
EXPORT_SYMBOL(hostap_set_auth_algs);
EXPORT_SYMBOL(hostap_dump_rx_header);
EXPORT_SYMBOL(hostap_dump_tx_header);
EXPORT_SYMBOL(hostap_80211_get_hdrlen);
EXPORT_SYMBOL(hostap_setup_dev);
EXPORT_SYMBOL(hostap_set_multicast_list_queue);
EXPORT_SYMBOL(hostap_set_hostapd);
EXPORT_SYMBOL(hostap_set_hostapd_sta);
EXPORT_SYMBOL(hostap_add_पूर्णांकerface);
EXPORT_SYMBOL(hostap_हटाओ_पूर्णांकerface);
EXPORT_SYMBOL(prism2_update_comms_qual);

module_init(hostap_init);
module_निकास(hostap_निकास);
