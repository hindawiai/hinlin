<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intersil Prism2 driver with Host AP (software access poपूर्णांक) support
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <j@w1.fi>
 * Copyright (c) 2002-2005, Jouni Malinen <j@w1.fi>
 *
 * This file is to be included पूर्णांकo hostap.c when S/W AP functionality is
 * compiled.
 *
 * AP:  FIX:
 * - अगर unicast Class 2 (assoc,reassoc,disassoc) frame received from
 *   unauthenticated STA, send deauth. frame (8802.11: 5.5)
 * - अगर unicast Class 3 (data with to/from DS,deauth,pspoll) frame received
 *   from authenticated, but unassoc STA, send disassoc frame (8802.11: 5.5)
 * - अगर unicast Class 3 received from unauthenticated STA, send deauth. frame
 *   (8802.11: 5.5)
 */

#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/delay.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/etherdevice.h>

#समावेश "hostap_wlan.h"
#समावेश "hostap.h"
#समावेश "hostap_ap.h"

अटल पूर्णांक other_ap_policy[MAX_PARM_DEVICES] = अणु AP_OTHER_AP_SKIP_ALL,
						 DEF_INTS पूर्ण;
module_param_array(other_ap_policy, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(other_ap_policy, "Other AP beacon monitoring policy (0-3)");

अटल पूर्णांक ap_max_inactivity[MAX_PARM_DEVICES] = अणु AP_MAX_INACTIVITY_SEC,
						   DEF_INTS पूर्ण;
module_param_array(ap_max_inactivity, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ap_max_inactivity, "AP timeout (in seconds) for station "
		 "inactivity");

अटल पूर्णांक ap_bridge_packets[MAX_PARM_DEVICES] = अणु 1, DEF_INTS पूर्ण;
module_param_array(ap_bridge_packets, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ap_bridge_packets, "Bridge packets directly between "
		 "stations");

अटल पूर्णांक स्वतःm_ap_wds[MAX_PARM_DEVICES] = अणु 0, DEF_INTS पूर्ण;
module_param_array(स्वतःm_ap_wds, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(स्वतःm_ap_wds, "Add WDS connections to other APs "
		 "automatically");


अटल काष्ठा sta_info* ap_get_sta(काष्ठा ap_data *ap, u8 *sta);
अटल व्योम hostap_event_expired_sta(काष्ठा net_device *dev,
				     काष्ठा sta_info *sta);
अटल व्योम handle_add_proc_queue(काष्ठा work_काष्ठा *work);

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
अटल व्योम handle_wds_oper_queue(काष्ठा work_काष्ठा *work);
अटल व्योम prism2_send_mgmt(काष्ठा net_device *dev,
			     u16 type_subtype, अक्षर *body,
			     पूर्णांक body_len, u8 *addr, u16 tx_cb_idx);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


#अगर !defined(PRISM2_NO_PROCFS_DEBUG) && defined(CONFIG_PROC_FS)
अटल पूर्णांक ap_debug_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ap_data *ap = PDE_DATA(file_inode(m->file));

	seq_म_लिखो(m, "BridgedUnicastFrames=%u\n", ap->bridged_unicast);
	seq_म_लिखो(m, "BridgedMulticastFrames=%u\n", ap->bridged_multicast);
	seq_म_लिखो(m, "max_inactivity=%u\n", ap->max_inactivity / HZ);
	seq_म_लिखो(m, "bridge_packets=%u\n", ap->bridge_packets);
	seq_म_लिखो(m, "nullfunc_ack=%u\n", ap->nullfunc_ack);
	seq_म_लिखो(m, "autom_ap_wds=%u\n", ap->स्वतःm_ap_wds);
	seq_म_लिखो(m, "auth_algs=%u\n", ap->local->auth_algs);
	seq_म_लिखो(m, "tx_drop_nonassoc=%u\n", ap->tx_drop_nonassoc);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम ap_sta_hash_add(काष्ठा ap_data *ap, काष्ठा sta_info *sta)
अणु
	sta->hnext = ap->sta_hash[STA_HASH(sta->addr)];
	ap->sta_hash[STA_HASH(sta->addr)] = sta;
पूर्ण

अटल व्योम ap_sta_hash_del(काष्ठा ap_data *ap, काष्ठा sta_info *sta)
अणु
	काष्ठा sta_info *s;

	s = ap->sta_hash[STA_HASH(sta->addr)];
	अगर (s == शून्य) वापस;
	अगर (ether_addr_equal(s->addr, sta->addr)) अणु
		ap->sta_hash[STA_HASH(sta->addr)] = s->hnext;
		वापस;
	पूर्ण

	जबतक (s->hnext != शून्य && !ether_addr_equal(s->hnext->addr, sta->addr))
		s = s->hnext;
	अगर (s->hnext != शून्य)
		s->hnext = s->hnext->hnext;
	अन्यथा
		prपूर्णांकk("AP: could not remove STA %pM from hash table\n",
		       sta->addr);
पूर्ण

अटल व्योम ap_मुक्त_sta(काष्ठा ap_data *ap, काष्ठा sta_info *sta)
अणु
	अगर (sta->ap && sta->local)
		hostap_event_expired_sta(sta->local->dev, sta);

	अगर (ap->proc != शून्य) अणु
		अक्षर name[20];
		प्र_लिखो(name, "%pM", sta->addr);
		हटाओ_proc_entry(name, ap->proc);
	पूर्ण

	अगर (sta->crypt) अणु
		sta->crypt->ops->deinit(sta->crypt->priv);
		kमुक्त(sta->crypt);
		sta->crypt = शून्य;
	पूर्ण

	skb_queue_purge(&sta->tx_buf);

	ap->num_sta--;
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	अगर (sta->aid > 0)
		ap->sta_aid[sta->aid - 1] = शून्य;

	अगर (!sta->ap)
		kमुक्त(sta->u.sta.challenge);
	del_समयr_sync(&sta->समयr);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	kमुक्त(sta);
पूर्ण


अटल व्योम hostap_set_tim(local_info_t *local, पूर्णांक aid, पूर्णांक set)
अणु
	अगर (local->func->set_tim)
		local->func->set_tim(local->dev, aid, set);
पूर्ण


अटल व्योम hostap_event_new_sta(काष्ठा net_device *dev, काष्ठा sta_info *sta)
अणु
	जोड़ iwreq_data wrqu;
	स_रखो(&wrqu, 0, माप(wrqu));
	स_नकल(wrqu.addr.sa_data, sta->addr, ETH_ALEN);
	wrqu.addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(dev, IWEVREGISTERED, &wrqu, शून्य);
पूर्ण


अटल व्योम hostap_event_expired_sta(काष्ठा net_device *dev,
				     काष्ठा sta_info *sta)
अणु
	जोड़ iwreq_data wrqu;
	स_रखो(&wrqu, 0, माप(wrqu));
	स_नकल(wrqu.addr.sa_data, sta->addr, ETH_ALEN);
	wrqu.addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(dev, IWEVEXPIRED, &wrqu, शून्य);
पूर्ण


#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT

अटल व्योम ap_handle_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sta_info *sta = from_समयr(sta, t, समयr);
	local_info_t *local;
	काष्ठा ap_data *ap;
	अचिन्हित दीर्घ next_समय = 0;
	पूर्णांक was_assoc;

	अगर (sta == शून्य || sta->local == शून्य || sta->local->ap == शून्य) अणु
		PDEBUG(DEBUG_AP, "ap_handle_timer() called with NULL data\n");
		वापस;
	पूर्ण

	local = sta->local;
	ap = local->ap;
	was_assoc = sta->flags & WLAN_STA_ASSOC;

	अगर (atomic_पढ़ो(&sta->users) != 0)
		next_समय = jअगरfies + HZ;
	अन्यथा अगर ((sta->flags & WLAN_STA_PERM) && !(sta->flags & WLAN_STA_AUTH))
		next_समय = jअगरfies + ap->max_inactivity;

	अगर (समय_beक्रमe(jअगरfies, sta->last_rx + ap->max_inactivity)) अणु
		/* station activity detected; reset समयout state */
		sta->समयout_next = STA_शून्यFUNC;
		next_समय = sta->last_rx + ap->max_inactivity;
	पूर्ण अन्यथा अगर (sta->समयout_next == STA_DISASSOC &&
		   !(sta->flags & WLAN_STA_PENDING_POLL)) अणु
		/* STA ACKed data nullfunc frame poll */
		sta->समयout_next = STA_शून्यFUNC;
		next_समय = jअगरfies + ap->max_inactivity;
	पूर्ण

	अगर (next_समय) अणु
		sta->समयr.expires = next_समय;
		add_समयr(&sta->समयr);
		वापस;
	पूर्ण

	अगर (sta->ap)
		sta->समयout_next = STA_DEAUTH;

	अगर (sta->समयout_next == STA_DEAUTH && !(sta->flags & WLAN_STA_PERM)) अणु
		spin_lock(&ap->sta_table_lock);
		ap_sta_hash_del(ap, sta);
		list_del(&sta->list);
		spin_unlock(&ap->sta_table_lock);
		sta->flags &= ~(WLAN_STA_AUTH | WLAN_STA_ASSOC);
	पूर्ण अन्यथा अगर (sta->समयout_next == STA_DISASSOC)
		sta->flags &= ~WLAN_STA_ASSOC;

	अगर (was_assoc && !(sta->flags & WLAN_STA_ASSOC) && !sta->ap)
		hostap_event_expired_sta(local->dev, sta);

	अगर (sta->समयout_next == STA_DEAUTH && sta->aid > 0 &&
	    !skb_queue_empty(&sta->tx_buf)) अणु
		hostap_set_tim(local, sta->aid, 0);
		sta->flags &= ~WLAN_STA_TIM;
	पूर्ण

	अगर (sta->ap) अणु
		अगर (ap->स्वतःm_ap_wds) अणु
			PDEBUG(DEBUG_AP, "%s: removing automatic WDS "
			       "connection to AP %pM\n",
			       local->dev->name, sta->addr);
			hostap_wds_link_oper(local, sta->addr, WDS_DEL);
		पूर्ण
	पूर्ण अन्यथा अगर (sta->समयout_next == STA_शून्यFUNC) अणु
		/* send data frame to poll STA and check whether this frame
		 * is ACKed */
		/* FIX: IEEE80211_STYPE_शून्यFUNC would be more appropriate, but
		 * it is apparently not retried so TX Exc events are not
		 * received क्रम it */
		sta->flags |= WLAN_STA_PENDING_POLL;
		prism2_send_mgmt(local->dev, IEEE80211_FTYPE_DATA |
				 IEEE80211_STYPE_DATA, शून्य, 0,
				 sta->addr, ap->tx_callback_poll);
	पूर्ण अन्यथा अणु
		पूर्णांक deauth = sta->समयout_next == STA_DEAUTH;
		__le16 resp;
		PDEBUG(DEBUG_AP, "%s: sending %s info to STA %pM"
		       "(last=%lu, jiffies=%lu)\n",
		       local->dev->name,
		       deauth ? "deauthentication" : "disassociation",
		       sta->addr, sta->last_rx, jअगरfies);

		resp = cpu_to_le16(deauth ? WLAN_REASON_PREV_AUTH_NOT_VALID :
				   WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY);
		prism2_send_mgmt(local->dev, IEEE80211_FTYPE_MGMT |
				 (deauth ? IEEE80211_STYPE_DEAUTH :
				  IEEE80211_STYPE_DISASSOC),
				 (अक्षर *) &resp, 2, sta->addr, 0);
	पूर्ण

	अगर (sta->समयout_next == STA_DEAUTH) अणु
		अगर (sta->flags & WLAN_STA_PERM) अणु
			PDEBUG(DEBUG_AP, "%s: STA %pM"
			       " would have been removed, "
			       "but it has 'perm' flag\n",
			       local->dev->name, sta->addr);
		पूर्ण अन्यथा
			ap_मुक्त_sta(ap, sta);
		वापस;
	पूर्ण

	अगर (sta->समयout_next == STA_शून्यFUNC) अणु
		sta->समयout_next = STA_DISASSOC;
		sta->समयr.expires = jअगरfies + AP_DISASSOC_DELAY;
	पूर्ण अन्यथा अणु
		sta->समयout_next = STA_DEAUTH;
		sta->समयr.expires = jअगरfies + AP_DEAUTH_DELAY;
	पूर्ण

	add_समयr(&sta->समयr);
पूर्ण


व्योम hostap_deauth_all_stas(काष्ठा net_device *dev, काष्ठा ap_data *ap,
			    पूर्णांक resend)
अणु
	u8 addr[ETH_ALEN];
	__le16 resp;
	पूर्णांक i;

	PDEBUG(DEBUG_AP, "%s: Deauthenticate all stations\n", dev->name);
	eth_broadcast_addr(addr);

	resp = cpu_to_le16(WLAN_REASON_PREV_AUTH_NOT_VALID);

	/* deauth message sent; try to resend it few बार; the message is
	 * broadcast, so it may be delayed until next DTIM; there is not much
	 * अन्यथा we can करो at this poपूर्णांक since the driver is going to be shut
	 * करोwn */
	क्रम (i = 0; i < 5; i++) अणु
		prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT |
				 IEEE80211_STYPE_DEAUTH,
				 (अक्षर *) &resp, 2, addr, 0);

		अगर (!resend || ap->num_sta <= 0)
			वापस;

		mdelay(50);
	पूर्ण
पूर्ण


अटल पूर्णांक ap_control_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ap_data *ap = PDE_DATA(file_inode(m->file));
	अक्षर *policy_txt;
	काष्ठा mac_entry *entry;

	अगर (v == SEQ_START_TOKEN) अणु
		चयन (ap->mac_restrictions.policy) अणु
		हाल MAC_POLICY_OPEN:
			policy_txt = "open";
			अवरोध;
		हाल MAC_POLICY_ALLOW:
			policy_txt = "allow";
			अवरोध;
		हाल MAC_POLICY_DENY:
			policy_txt = "deny";
			अवरोध;
		शेष:
			policy_txt = "unknown";
			अवरोध;
		पूर्ण
		seq_म_लिखो(m, "MAC policy: %s\n", policy_txt);
		seq_म_लिखो(m, "MAC entries: %u\n", ap->mac_restrictions.entries);
		seq_माला_दो(m, "MAC list:\n");
		वापस 0;
	पूर्ण

	entry = v;
	seq_म_लिखो(m, "%pM\n", entry->addr);
	वापस 0;
पूर्ण

अटल व्योम *ap_control_proc_start(काष्ठा seq_file *m, loff_t *_pos)
अणु
	काष्ठा ap_data *ap = PDE_DATA(file_inode(m->file));
	spin_lock_bh(&ap->mac_restrictions.lock);
	वापस seq_list_start_head(&ap->mac_restrictions.mac_list, *_pos);
पूर्ण

अटल व्योम *ap_control_proc_next(काष्ठा seq_file *m, व्योम *v, loff_t *_pos)
अणु
	काष्ठा ap_data *ap = PDE_DATA(file_inode(m->file));
	वापस seq_list_next(v, &ap->mac_restrictions.mac_list, _pos);
पूर्ण

अटल व्योम ap_control_proc_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ap_data *ap = PDE_DATA(file_inode(m->file));
	spin_unlock_bh(&ap->mac_restrictions.lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations ap_control_proc_seqops = अणु
	.start	= ap_control_proc_start,
	.next	= ap_control_proc_next,
	.stop	= ap_control_proc_stop,
	.show	= ap_control_proc_show,
पूर्ण;

पूर्णांक ap_control_add_mac(काष्ठा mac_restrictions *mac_restrictions, u8 *mac)
अणु
	काष्ठा mac_entry *entry;

	entry = kदो_स्मृति(माप(काष्ठा mac_entry), GFP_KERNEL);
	अगर (entry == शून्य)
		वापस -ENOMEM;

	स_नकल(entry->addr, mac, ETH_ALEN);

	spin_lock_bh(&mac_restrictions->lock);
	list_add_tail(&entry->list, &mac_restrictions->mac_list);
	mac_restrictions->entries++;
	spin_unlock_bh(&mac_restrictions->lock);

	वापस 0;
पूर्ण


पूर्णांक ap_control_del_mac(काष्ठा mac_restrictions *mac_restrictions, u8 *mac)
अणु
	काष्ठा list_head *ptr;
	काष्ठा mac_entry *entry;

	spin_lock_bh(&mac_restrictions->lock);
	क्रम (ptr = mac_restrictions->mac_list.next;
	     ptr != &mac_restrictions->mac_list; ptr = ptr->next) अणु
		entry = list_entry(ptr, काष्ठा mac_entry, list);

		अगर (ether_addr_equal(entry->addr, mac)) अणु
			list_del(ptr);
			kमुक्त(entry);
			mac_restrictions->entries--;
			spin_unlock_bh(&mac_restrictions->lock);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&mac_restrictions->lock);
	वापस -1;
पूर्ण


अटल पूर्णांक ap_control_mac_deny(काष्ठा mac_restrictions *mac_restrictions,
			       u8 *mac)
अणु
	काष्ठा mac_entry *entry;
	पूर्णांक found = 0;

	अगर (mac_restrictions->policy == MAC_POLICY_OPEN)
		वापस 0;

	spin_lock_bh(&mac_restrictions->lock);
	list_क्रम_each_entry(entry, &mac_restrictions->mac_list, list) अणु
		अगर (ether_addr_equal(entry->addr, mac)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&mac_restrictions->lock);

	अगर (mac_restrictions->policy == MAC_POLICY_ALLOW)
		वापस !found;
	अन्यथा
		वापस found;
पूर्ण


व्योम ap_control_flush_macs(काष्ठा mac_restrictions *mac_restrictions)
अणु
	काष्ठा list_head *ptr, *n;
	काष्ठा mac_entry *entry;

	अगर (mac_restrictions->entries == 0)
		वापस;

	spin_lock_bh(&mac_restrictions->lock);
	क्रम (ptr = mac_restrictions->mac_list.next, n = ptr->next;
	     ptr != &mac_restrictions->mac_list;
	     ptr = n, n = ptr->next) अणु
		entry = list_entry(ptr, काष्ठा mac_entry, list);
		list_del(ptr);
		kमुक्त(entry);
	पूर्ण
	mac_restrictions->entries = 0;
	spin_unlock_bh(&mac_restrictions->lock);
पूर्ण


पूर्णांक ap_control_kick_mac(काष्ठा ap_data *ap, काष्ठा net_device *dev, u8 *mac)
अणु
	काष्ठा sta_info *sta;
	__le16 resp;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, mac);
	अगर (sta) अणु
		ap_sta_hash_del(ap, sta);
		list_del(&sta->list);
	पूर्ण
	spin_unlock_bh(&ap->sta_table_lock);

	अगर (!sta)
		वापस -EINVAL;

	resp = cpu_to_le16(WLAN_REASON_PREV_AUTH_NOT_VALID);
	prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_DEAUTH,
			 (अक्षर *) &resp, 2, sta->addr, 0);

	अगर ((sta->flags & WLAN_STA_ASSOC) && !sta->ap)
		hostap_event_expired_sta(dev, sta);

	ap_मुक्त_sta(ap, sta);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


व्योम ap_control_kickall(काष्ठा ap_data *ap)
अणु
	काष्ठा list_head *ptr, *n;
	काष्ठा sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	क्रम (ptr = ap->sta_list.next, n = ptr->next; ptr != &ap->sta_list;
	     ptr = n, n = ptr->next) अणु
		sta = list_entry(ptr, काष्ठा sta_info, list);
		ap_sta_hash_del(ap, sta);
		list_del(&sta->list);
		अगर ((sta->flags & WLAN_STA_ASSOC) && !sta->ap && sta->local)
			hostap_event_expired_sta(sta->local->dev, sta);
		ap_मुक्त_sta(ap, sta);
	पूर्ण
	spin_unlock_bh(&ap->sta_table_lock);
पूर्ण


#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT

अटल पूर्णांक prism2_ap_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा sta_info *sta = v;
	पूर्णांक i;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(m, "# BSSID CHAN SIGNAL NOISE RATE SSID FLAGS\n");
		वापस 0;
	पूर्ण

	अगर (!sta->ap)
		वापस 0;

	seq_म_लिखो(m, "%pM %d %d %d %d '",
		   sta->addr,
		   sta->u.ap.channel, sta->last_rx_संकेत,
		   sta->last_rx_silence, sta->last_rx_rate);

	क्रम (i = 0; i < sta->u.ap.ssid_len; i++) अणु
		अगर (sta->u.ap.ssid[i] >= 32 && sta->u.ap.ssid[i] < 127)
			seq_अ_दो(m, sta->u.ap.ssid[i]);
		अन्यथा
			seq_म_लिखो(m, "<%02x>", sta->u.ap.ssid[i]);
	पूर्ण

	seq_अ_दो(m, '\'');
	अगर (sta->capability & WLAN_CAPABILITY_ESS)
		seq_माला_दो(m, " [ESS]");
	अगर (sta->capability & WLAN_CAPABILITY_IBSS)
		seq_माला_दो(m, " [IBSS]");
	अगर (sta->capability & WLAN_CAPABILITY_PRIVACY)
		seq_माला_दो(m, " [WEP]");
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल व्योम *prism2_ap_proc_start(काष्ठा seq_file *m, loff_t *_pos)
अणु
	काष्ठा ap_data *ap = PDE_DATA(file_inode(m->file));
	spin_lock_bh(&ap->sta_table_lock);
	वापस seq_list_start_head(&ap->sta_list, *_pos);
पूर्ण

अटल व्योम *prism2_ap_proc_next(काष्ठा seq_file *m, व्योम *v, loff_t *_pos)
अणु
	काष्ठा ap_data *ap = PDE_DATA(file_inode(m->file));
	वापस seq_list_next(v, &ap->sta_list, _pos);
पूर्ण

अटल व्योम prism2_ap_proc_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ap_data *ap = PDE_DATA(file_inode(m->file));
	spin_unlock_bh(&ap->sta_table_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations prism2_ap_proc_seqops = अणु
	.start	= prism2_ap_proc_start,
	.next	= prism2_ap_proc_next,
	.stop	= prism2_ap_proc_stop,
	.show	= prism2_ap_proc_show,
पूर्ण;
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


व्योम hostap_check_sta_fw_version(काष्ठा ap_data *ap, पूर्णांक sta_fw_ver)
अणु
	अगर (!ap)
		वापस;

	अगर (sta_fw_ver == PRISM2_FW_VER(0,8,0)) अणु
		PDEBUG(DEBUG_AP, "Using data::nullfunc ACK workaround - "
		       "firmware upgrade recommended\n");
		ap->nullfunc_ack = 1;
	पूर्ण अन्यथा
		ap->nullfunc_ack = 0;

	अगर (sta_fw_ver == PRISM2_FW_VER(1,4,2)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Warning: secondary station firmware "
		       "version 1.4.2 does not seem to work in Host AP mode\n",
		       ap->local->dev->name);
	पूर्ण
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_ap_tx_cb(काष्ठा sk_buff *skb, पूर्णांक ok, व्योम *data)
अणु
	काष्ठा ap_data *ap = data;
	काष्ठा ieee80211_hdr *hdr;

	अगर (!ap->local->hostapd || !ap->local->apdev) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* Pass the TX callback frame to the hostapd; use 802.11 header version
	 * 1 to indicate failure (no ACK) and 2 success (frame ACKed) */

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	hdr->frame_control &= cpu_to_le16(~IEEE80211_FCTL_VERS);
	hdr->frame_control |= cpu_to_le16(ok ? BIT(1) : BIT(0));

	skb->dev = ap->local->apdev;
	skb_pull(skb, hostap_80211_get_hdrlen(hdr->frame_control));
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = cpu_to_be16(ETH_P_802_2);
	स_रखो(skb->cb, 0, माप(skb->cb));
	netअगर_rx(skb);
पूर्ण


#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_ap_tx_cb_auth(काष्ठा sk_buff *skb, पूर्णांक ok, व्योम *data)
अणु
	काष्ठा ap_data *ap = data;
	काष्ठा net_device *dev = ap->local->dev;
	काष्ठा ieee80211_hdr *hdr;
	u16 auth_alg, auth_transaction, status;
	__le16 *pos;
	काष्ठा sta_info *sta = शून्य;
	अक्षर *txt = शून्य;

	अगर (ap->local->hostapd) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अगर (!ieee80211_is_auth(hdr->frame_control) ||
	    skb->len < IEEE80211_MGMT_HDR_LEN + 6) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hostap_ap_tx_cb_auth received invalid "
		       "frame\n", dev->name);
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	pos = (__le16 *) (skb->data + IEEE80211_MGMT_HDR_LEN);
	auth_alg = le16_to_cpu(*pos++);
	auth_transaction = le16_to_cpu(*pos++);
	status = le16_to_cpu(*pos++);

	अगर (!ok) अणु
		txt = "frame was not ACKed";
		जाओ करोne;
	पूर्ण

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, hdr->addr1);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock(&ap->sta_table_lock);

	अगर (!sta) अणु
		txt = "STA not found";
		जाओ करोne;
	पूर्ण

	अगर (status == WLAN_STATUS_SUCCESS &&
	    ((auth_alg == WLAN_AUTH_OPEN && auth_transaction == 2) ||
	     (auth_alg == WLAN_AUTH_SHARED_KEY && auth_transaction == 4))) अणु
		txt = "STA authenticated";
		sta->flags |= WLAN_STA_AUTH;
		sta->last_auth = jअगरfies;
	पूर्ण अन्यथा अगर (status != WLAN_STATUS_SUCCESS)
		txt = "authentication failed";

 करोne:
	अगर (sta)
		atomic_dec(&sta->users);
	अगर (txt) अणु
		PDEBUG(DEBUG_AP, "%s: %pM auth_cb - alg=%d "
		       "trans#=%d status=%d - %s\n",
		       dev->name, hdr->addr1,
		       auth_alg, auth_transaction, status, txt);
	पूर्ण
	dev_kमुक्त_skb(skb);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_ap_tx_cb_assoc(काष्ठा sk_buff *skb, पूर्णांक ok, व्योम *data)
अणु
	काष्ठा ap_data *ap = data;
	काष्ठा net_device *dev = ap->local->dev;
	काष्ठा ieee80211_hdr *hdr;
	u16 status;
	__le16 *pos;
	काष्ठा sta_info *sta = शून्य;
	अक्षर *txt = शून्य;

	अगर (ap->local->hostapd) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अगर ((!ieee80211_is_assoc_resp(hdr->frame_control) &&
	     !ieee80211_is_reassoc_resp(hdr->frame_control)) ||
	    skb->len < IEEE80211_MGMT_HDR_LEN + 4) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hostap_ap_tx_cb_assoc received invalid "
		       "frame\n", dev->name);
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (!ok) अणु
		txt = "frame was not ACKed";
		जाओ करोne;
	पूर्ण

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, hdr->addr1);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock(&ap->sta_table_lock);

	अगर (!sta) अणु
		txt = "STA not found";
		जाओ करोne;
	पूर्ण

	pos = (__le16 *) (skb->data + IEEE80211_MGMT_HDR_LEN);
	pos++;
	status = le16_to_cpu(*pos++);
	अगर (status == WLAN_STATUS_SUCCESS) अणु
		अगर (!(sta->flags & WLAN_STA_ASSOC))
			hostap_event_new_sta(dev, sta);
		txt = "STA associated";
		sta->flags |= WLAN_STA_ASSOC;
		sta->last_assoc = jअगरfies;
	पूर्ण अन्यथा
		txt = "association failed";

 करोne:
	अगर (sta)
		atomic_dec(&sta->users);
	अगर (txt) अणु
		PDEBUG(DEBUG_AP, "%s: %pM assoc_cb - %s\n",
		       dev->name, hdr->addr1, txt);
	पूर्ण
	dev_kमुक्त_skb(skb);
पूर्ण

/* Called only as a tasklet (software IRQ); TX callback क्रम poll frames used
 * in verअगरying whether the STA is still present. */
अटल व्योम hostap_ap_tx_cb_poll(काष्ठा sk_buff *skb, पूर्णांक ok, व्योम *data)
अणु
	काष्ठा ap_data *ap = data;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा sta_info *sta;

	अगर (skb->len < 24)
		जाओ fail;
	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अगर (ok) अणु
		spin_lock(&ap->sta_table_lock);
		sta = ap_get_sta(ap, hdr->addr1);
		अगर (sta)
			sta->flags &= ~WLAN_STA_PENDING_POLL;
		spin_unlock(&ap->sta_table_lock);
	पूर्ण अन्यथा अणु
		PDEBUG(DEBUG_AP,
		       "%s: STA %pM did not ACK activity poll frame\n",
		       ap->local->dev->name, hdr->addr1);
	पूर्ण

 fail:
	dev_kमुक्त_skb(skb);
पूर्ण
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


व्योम hostap_init_data(local_info_t *local)
अणु
	काष्ठा ap_data *ap = local->ap;

	अगर (ap == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "hostap_init_data: ap == NULL\n");
		वापस;
	पूर्ण
	स_रखो(ap, 0, माप(काष्ठा ap_data));
	ap->local = local;

	ap->ap_policy = GET_INT_PARM(other_ap_policy, local->card_idx);
	ap->bridge_packets = GET_INT_PARM(ap_bridge_packets, local->card_idx);
	ap->max_inactivity =
		GET_INT_PARM(ap_max_inactivity, local->card_idx) * HZ;
	ap->स्वतःm_ap_wds = GET_INT_PARM(स्वतःm_ap_wds, local->card_idx);

	spin_lock_init(&ap->sta_table_lock);
	INIT_LIST_HEAD(&ap->sta_list);

	/* Initialize task queue काष्ठाure क्रम AP management */
	INIT_WORK(&local->ap->add_sta_proc_queue, handle_add_proc_queue);

	ap->tx_callback_idx =
		hostap_tx_callback_रेजिस्टर(local, hostap_ap_tx_cb, ap);
	अगर (ap->tx_callback_idx == 0)
		prपूर्णांकk(KERN_WARNING "%s: failed to register TX callback for "
		       "AP\n", local->dev->name);
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	INIT_WORK(&local->ap->wds_oper_queue, handle_wds_oper_queue);

	ap->tx_callback_auth =
		hostap_tx_callback_रेजिस्टर(local, hostap_ap_tx_cb_auth, ap);
	ap->tx_callback_assoc =
		hostap_tx_callback_रेजिस्टर(local, hostap_ap_tx_cb_assoc, ap);
	ap->tx_callback_poll =
		hostap_tx_callback_रेजिस्टर(local, hostap_ap_tx_cb_poll, ap);
	अगर (ap->tx_callback_auth == 0 || ap->tx_callback_assoc == 0 ||
		ap->tx_callback_poll == 0)
		prपूर्णांकk(KERN_WARNING "%s: failed to register TX callback for "
		       "AP\n", local->dev->name);

	spin_lock_init(&ap->mac_restrictions.lock);
	INIT_LIST_HEAD(&ap->mac_restrictions.mac_list);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	ap->initialized = 1;
पूर्ण


व्योम hostap_init_ap_proc(local_info_t *local)
अणु
	काष्ठा ap_data *ap = local->ap;

	ap->proc = local->proc;
	अगर (ap->proc == शून्य)
		वापस;

#अगर_अघोषित PRISM2_NO_PROCFS_DEBUG
	proc_create_single_data("ap_debug", 0, ap->proc, ap_debug_proc_show, ap);
#पूर्ण_अगर /* PRISM2_NO_PROCFS_DEBUG */

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	proc_create_seq_data("ap_control", 0, ap->proc, &ap_control_proc_seqops,
			ap);
	proc_create_seq_data("ap", 0, ap->proc, &prism2_ap_proc_seqops, ap);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

पूर्ण


व्योम hostap_मुक्त_data(काष्ठा ap_data *ap)
अणु
	काष्ठा sta_info *n, *sta;

	अगर (ap == शून्य || !ap->initialized) अणु
		prपूर्णांकk(KERN_DEBUG "hostap_free_data: ap has not yet been "
		       "initialized - skip resource freeing\n");
		वापस;
	पूर्ण

	flush_work(&ap->add_sta_proc_queue);

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	flush_work(&ap->wds_oper_queue);
	अगर (ap->crypt)
		ap->crypt->deinit(ap->crypt_priv);
	ap->crypt = ap->crypt_priv = शून्य;
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	list_क्रम_each_entry_safe(sta, n, &ap->sta_list, list) अणु
		ap_sta_hash_del(ap, sta);
		list_del(&sta->list);
		अगर ((sta->flags & WLAN_STA_ASSOC) && !sta->ap && sta->local)
			hostap_event_expired_sta(sta->local->dev, sta);
		ap_मुक्त_sta(ap, sta);
	पूर्ण

#अगर_अघोषित PRISM2_NO_PROCFS_DEBUG
	अगर (ap->proc != शून्य) अणु
		हटाओ_proc_entry("ap_debug", ap->proc);
	पूर्ण
#पूर्ण_अगर /* PRISM2_NO_PROCFS_DEBUG */

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	अगर (ap->proc != शून्य) अणु
	  हटाओ_proc_entry("ap", ap->proc);
		हटाओ_proc_entry("ap_control", ap->proc);
	पूर्ण
	ap_control_flush_macs(&ap->mac_restrictions);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	ap->initialized = 0;
पूर्ण


/* caller should have mutex क्रम AP STA list handling */
अटल काष्ठा sta_info* ap_get_sta(काष्ठा ap_data *ap, u8 *sta)
अणु
	काष्ठा sta_info *s;

	s = ap->sta_hash[STA_HASH(sta)];
	जबतक (s != शून्य && !ether_addr_equal(s->addr, sta))
		s = s->hnext;
	वापस s;
पूर्ण


#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT

/* Called from समयr handler and from scheduled AP queue handlers */
अटल व्योम prism2_send_mgmt(काष्ठा net_device *dev,
			     u16 type_subtype, अक्षर *body,
			     पूर्णांक body_len, u8 *addr, u16 tx_cb_idx)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;
	काष्ठा sk_buff *skb;
	काष्ठा hostap_skb_tx_data *meta;
	पूर्णांक hdrlen;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	dev = local->dev; /* always use master radio device */
	अगरace = netdev_priv(dev);

	अगर (!(dev->flags & IFF_UP)) अणु
		PDEBUG(DEBUG_AP, "%s: prism2_send_mgmt - device is not UP - "
		       "cannot send frame\n", dev->name);
		वापस;
	पूर्ण

	skb = dev_alloc_skb(माप(*hdr) + body_len);
	अगर (skb == शून्य) अणु
		PDEBUG(DEBUG_AP, "%s: prism2_send_mgmt failed to allocate "
		       "skb\n", dev->name);
		वापस;
	पूर्ण

	fc = type_subtype;
	hdrlen = hostap_80211_get_hdrlen(cpu_to_le16(type_subtype));
	hdr = skb_put_zero(skb, hdrlen);
	अगर (body)
		skb_put_data(skb, body, body_len);

	/* FIX: ctrl::ack sending used special HFA384X_TX_CTRL_802_11
	 * tx_control instead of using local->tx_control */


	स_नकल(hdr->addr1, addr, ETH_ALEN); /* DA / RA */
	अगर (ieee80211_is_data(hdr->frame_control)) अणु
		fc |= IEEE80211_FCTL_FROMDS;
		स_नकल(hdr->addr2, dev->dev_addr, ETH_ALEN); /* BSSID */
		स_नकल(hdr->addr3, dev->dev_addr, ETH_ALEN); /* SA */
	पूर्ण अन्यथा अगर (ieee80211_is_ctl(hdr->frame_control)) अणु
		/* control:ACK करोes not have addr2 or addr3 */
		eth_zero_addr(hdr->addr2);
		eth_zero_addr(hdr->addr3);
	पूर्ण अन्यथा अणु
		स_नकल(hdr->addr2, dev->dev_addr, ETH_ALEN); /* SA */
		स_नकल(hdr->addr3, dev->dev_addr, ETH_ALEN); /* BSSID */
	पूर्ण

	hdr->frame_control = cpu_to_le16(fc);

	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
	स_रखो(meta, 0, माप(*meta));
	meta->magic = HOSTAP_SKB_TX_DATA_MAGIC;
	meta->अगरace = अगरace;
	meta->tx_cb_idx = tx_cb_idx;

	skb->dev = dev;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	dev_queue_xmit(skb);
पूर्ण
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक prism2_sta_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा sta_info *sta = m->निजी;
	पूर्णांक i;

	/* FIX: possible race condition.. the STA data could have just expired,
	 * but proc entry was still here so that the पढ़ो could have started;
	 * some locking should be करोne here.. */

	seq_म_लिखो(m,
		   "%s=%pM\nusers=%d\naid=%d\n"
		   "flags=0x%04x%s%s%s%s%s%s%s\n"
		   "capability=0x%02x\nlisten_interval=%d\nsupported_rates=",
		   sta->ap ? "AP" : "STA",
		   sta->addr, atomic_पढ़ो(&sta->users), sta->aid,
		   sta->flags,
		   sta->flags & WLAN_STA_AUTH ? " AUTH" : "",
		   sta->flags & WLAN_STA_ASSOC ? " ASSOC" : "",
		   sta->flags & WLAN_STA_PS ? " PS" : "",
		   sta->flags & WLAN_STA_TIM ? " TIM" : "",
		   sta->flags & WLAN_STA_PERM ? " PERM" : "",
		   sta->flags & WLAN_STA_AUTHORIZED ? " AUTHORIZED" : "",
		   sta->flags & WLAN_STA_PENDING_POLL ? " POLL" : "",
		   sta->capability, sta->listen_पूर्णांकerval);
	/* supported_rates: 500 kbit/s units with msb ignored */
	क्रम (i = 0; i < माप(sta->supported_rates); i++)
		अगर (sta->supported_rates[i] != 0)
			seq_म_लिखो(m, "%d%sMbps ",
				   (sta->supported_rates[i] & 0x7f) / 2,
				   sta->supported_rates[i] & 1 ? ".5" : "");
	seq_म_लिखो(m,
		   "\njiffies=%lu\nlast_auth=%lu\nlast_assoc=%lu\n"
		   "last_rx=%lu\nlast_tx=%lu\nrx_packets=%lu\n"
		   "tx_packets=%lu\n"
		   "rx_bytes=%lu\ntx_bytes=%lu\nbuffer_count=%d\n"
		   "last_rx: silence=%d dBm signal=%d dBm rate=%d%s Mbps\n"
		   "tx_rate=%d\ntx[1M]=%d\ntx[2M]=%d\ntx[5.5M]=%d\n"
		   "tx[11M]=%d\n"
		   "rx[1M]=%d\nrx[2M]=%d\nrx[5.5M]=%d\nrx[11M]=%d\n",
		   jअगरfies, sta->last_auth, sta->last_assoc, sta->last_rx,
		   sta->last_tx,
		   sta->rx_packets, sta->tx_packets, sta->rx_bytes,
		   sta->tx_bytes, skb_queue_len(&sta->tx_buf),
		   sta->last_rx_silence,
		   sta->last_rx_संकेत, sta->last_rx_rate / 10,
		   sta->last_rx_rate % 10 ? ".5" : "",
		   sta->tx_rate, sta->tx_count[0], sta->tx_count[1],
		   sta->tx_count[2], sta->tx_count[3],  sta->rx_count[0],
		   sta->rx_count[1], sta->rx_count[2], sta->rx_count[3]);
	अगर (sta->crypt && sta->crypt->ops && sta->crypt->ops->prपूर्णांक_stats)
		sta->crypt->ops->prपूर्णांक_stats(m, sta->crypt->priv);
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	अगर (sta->ap) अणु
		अगर (sta->u.ap.channel >= 0)
			seq_म_लिखो(m, "channel=%d\n", sta->u.ap.channel);
		seq_माला_दो(m, "ssid=");
		क्रम (i = 0; i < sta->u.ap.ssid_len; i++) अणु
			अगर (sta->u.ap.ssid[i] >= 32 && sta->u.ap.ssid[i] < 127)
				seq_अ_दो(m, sta->u.ap.ssid[i]);
			अन्यथा
				seq_म_लिखो(m, "<%02x>", sta->u.ap.ssid[i]);
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम handle_add_proc_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ap_data *ap = container_of(work, काष्ठा ap_data,
					  add_sta_proc_queue);
	काष्ठा sta_info *sta;
	अक्षर name[20];
	काष्ठा add_sta_proc_data *entry, *prev;

	entry = ap->add_sta_proc_entries;
	ap->add_sta_proc_entries = शून्य;

	जबतक (entry) अणु
		spin_lock_bh(&ap->sta_table_lock);
		sta = ap_get_sta(ap, entry->addr);
		अगर (sta)
			atomic_inc(&sta->users);
		spin_unlock_bh(&ap->sta_table_lock);

		अगर (sta) अणु
			प्र_लिखो(name, "%pM", sta->addr);
			sta->proc = proc_create_single_data(
				name, 0, ap->proc,
				prism2_sta_proc_show, sta);

			atomic_dec(&sta->users);
		पूर्ण

		prev = entry;
		entry = entry->next;
		kमुक्त(prev);
	पूर्ण
पूर्ण


अटल काष्ठा sta_info * ap_add_sta(काष्ठा ap_data *ap, u8 *addr)
अणु
	काष्ठा sta_info *sta;

	sta = kzalloc(माप(काष्ठा sta_info), GFP_ATOMIC);
	अगर (sta == शून्य) अणु
		PDEBUG(DEBUG_AP, "AP: kmalloc failed\n");
		वापस शून्य;
	पूर्ण

	/* initialize STA info data */
	sta->local = ap->local;
	skb_queue_head_init(&sta->tx_buf);
	स_नकल(sta->addr, addr, ETH_ALEN);

	atomic_inc(&sta->users);
	spin_lock_bh(&ap->sta_table_lock);
	list_add(&sta->list, &ap->sta_list);
	ap->num_sta++;
	ap_sta_hash_add(ap, sta);
	spin_unlock_bh(&ap->sta_table_lock);

	अगर (ap->proc) अणु
		काष्ठा add_sta_proc_data *entry;
		/* schedule a non-पूर्णांकerrupt context process to add a procfs
		 * entry क्रम the STA since procfs code use GFP_KERNEL */
		entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
		अगर (entry) अणु
			स_नकल(entry->addr, sta->addr, ETH_ALEN);
			entry->next = ap->add_sta_proc_entries;
			ap->add_sta_proc_entries = entry;
			schedule_work(&ap->add_sta_proc_queue);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_DEBUG "Failed to add STA proc data\n");
	पूर्ण

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	समयr_setup(&sta->समयr, ap_handle_समयr, 0);
	sta->समयr.expires = jअगरfies + ap->max_inactivity;
	अगर (!ap->local->hostapd)
		add_समयr(&sta->समयr);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	वापस sta;
पूर्ण


अटल पूर्णांक ap_tx_rate_ok(पूर्णांक rateidx, काष्ठा sta_info *sta,
			 local_info_t *local)
अणु
	अगर (rateidx > sta->tx_max_rate ||
	    !(sta->tx_supp_rates & (1 << rateidx)))
		वापस 0;

	अगर (local->tx_rate_control != 0 &&
	    !(local->tx_rate_control & (1 << rateidx)))
		वापस 0;

	वापस 1;
पूर्ण


अटल व्योम prism2_check_tx_rates(काष्ठा sta_info *sta)
अणु
	पूर्णांक i;

	sta->tx_supp_rates = 0;
	क्रम (i = 0; i < माप(sta->supported_rates); i++) अणु
		अगर ((sta->supported_rates[i] & 0x7f) == 2)
			sta->tx_supp_rates |= WLAN_RATE_1M;
		अगर ((sta->supported_rates[i] & 0x7f) == 4)
			sta->tx_supp_rates |= WLAN_RATE_2M;
		अगर ((sta->supported_rates[i] & 0x7f) == 11)
			sta->tx_supp_rates |= WLAN_RATE_5M5;
		अगर ((sta->supported_rates[i] & 0x7f) == 22)
			sta->tx_supp_rates |= WLAN_RATE_11M;
	पूर्ण
	sta->tx_max_rate = sta->tx_rate = sta->tx_rate_idx = 0;
	अगर (sta->tx_supp_rates & WLAN_RATE_1M) अणु
		sta->tx_max_rate = 0;
		अगर (ap_tx_rate_ok(0, sta, sta->local)) अणु
			sta->tx_rate = 10;
			sta->tx_rate_idx = 0;
		पूर्ण
	पूर्ण
	अगर (sta->tx_supp_rates & WLAN_RATE_2M) अणु
		sta->tx_max_rate = 1;
		अगर (ap_tx_rate_ok(1, sta, sta->local)) अणु
			sta->tx_rate = 20;
			sta->tx_rate_idx = 1;
		पूर्ण
	पूर्ण
	अगर (sta->tx_supp_rates & WLAN_RATE_5M5) अणु
		sta->tx_max_rate = 2;
		अगर (ap_tx_rate_ok(2, sta, sta->local)) अणु
			sta->tx_rate = 55;
			sta->tx_rate_idx = 2;
		पूर्ण
	पूर्ण
	अगर (sta->tx_supp_rates & WLAN_RATE_11M) अणु
		sta->tx_max_rate = 3;
		अगर (ap_tx_rate_ok(3, sta, sta->local)) अणु
			sta->tx_rate = 110;
			sta->tx_rate_idx = 3;
		पूर्ण
	पूर्ण
पूर्ण


#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT

अटल व्योम ap_crypt_init(काष्ठा ap_data *ap)
अणु
	ap->crypt = lib80211_get_crypto_ops("WEP");

	अगर (ap->crypt) अणु
		अगर (ap->crypt->init) अणु
			ap->crypt_priv = ap->crypt->init(0);
			अगर (ap->crypt_priv == शून्य)
				ap->crypt = शून्य;
			अन्यथा अणु
				u8 key[WEP_KEY_LEN];
				get_अक्रमom_bytes(key, WEP_KEY_LEN);
				ap->crypt->set_key(key, WEP_KEY_LEN, शून्य,
						   ap->crypt_priv);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ap->crypt == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "AP could not initialize WEP: load module "
		       "lib80211_crypt_wep.ko\n");
	पूर्ण
पूर्ण


/* Generate challenge data क्रम shared key authentication. IEEE 802.11 specअगरies
 * that WEP algorithm is used क्रम generating challenge. This should be unique,
 * but otherwise there is not really need क्रम अक्रमomness etc. Initialize WEP
 * with pseuकरो अक्रमom key and then use increasing IV to get unique challenge
 * streams.
 *
 * Called only as a scheduled task क्रम pending AP frames.
 */
अटल अक्षर * ap_auth_make_challenge(काष्ठा ap_data *ap)
अणु
	अक्षर *पंचांगpbuf;
	काष्ठा sk_buff *skb;

	अगर (ap->crypt == शून्य) अणु
		ap_crypt_init(ap);
		अगर (ap->crypt == शून्य)
			वापस शून्य;
	पूर्ण

	पंचांगpbuf = kदो_स्मृति(WLAN_AUTH_CHALLENGE_LEN, GFP_ATOMIC);
	अगर (पंचांगpbuf == शून्य) अणु
		PDEBUG(DEBUG_AP, "AP: kmalloc failed for challenge\n");
		वापस शून्य;
	पूर्ण

	skb = dev_alloc_skb(WLAN_AUTH_CHALLENGE_LEN +
			    ap->crypt->extra_mpdu_prefix_len +
			    ap->crypt->extra_mpdu_postfix_len);
	अगर (skb == शून्य) अणु
		kमुक्त(पंचांगpbuf);
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, ap->crypt->extra_mpdu_prefix_len);
	skb_put_zero(skb, WLAN_AUTH_CHALLENGE_LEN);
	अगर (ap->crypt->encrypt_mpdu(skb, 0, ap->crypt_priv)) अणु
		dev_kमुक्त_skb(skb);
		kमुक्त(पंचांगpbuf);
		वापस शून्य;
	पूर्ण

	skb_copy_from_linear_data_offset(skb, ap->crypt->extra_mpdu_prefix_len,
					 पंचांगpbuf, WLAN_AUTH_CHALLENGE_LEN);
	dev_kमुक्त_skb(skb);

	वापस पंचांगpbuf;
पूर्ण


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम handle_authen(local_info_t *local, काष्ठा sk_buff *skb,
			  काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा net_device *dev = local->dev;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	माप_प्रकार hdrlen;
	काष्ठा ap_data *ap = local->ap;
	अक्षर body[8 + WLAN_AUTH_CHALLENGE_LEN], *challenge = शून्य;
	पूर्णांक len, olen;
	u16 auth_alg, auth_transaction, status_code;
	__le16 *pos;
	u16 resp = WLAN_STATUS_SUCCESS;
	काष्ठा sta_info *sta = शून्य;
	काष्ठा lib80211_crypt_data *crypt;
	अक्षर *txt = "";

	len = skb->len - IEEE80211_MGMT_HDR_LEN;

	hdrlen = hostap_80211_get_hdrlen(hdr->frame_control);

	अगर (len < 6) अणु
		PDEBUG(DEBUG_AP, "%s: handle_authen - too short payload "
		       "(len=%d) from %pM\n", dev->name, len, hdr->addr2);
		वापस;
	पूर्ण

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock_bh(&local->ap->sta_table_lock);

	अगर (sta && sta->crypt)
		crypt = sta->crypt;
	अन्यथा अणु
		पूर्णांक idx = 0;
		अगर (skb->len >= hdrlen + 3)
			idx = skb->data[hdrlen + 3] >> 6;
		crypt = local->crypt_info.crypt[idx];
	पूर्ण

	pos = (__le16 *) (skb->data + IEEE80211_MGMT_HDR_LEN);
	auth_alg = __le16_to_cpu(*pos);
	pos++;
	auth_transaction = __le16_to_cpu(*pos);
	pos++;
	status_code = __le16_to_cpu(*pos);
	pos++;

	अगर (ether_addr_equal(dev->dev_addr, hdr->addr2) ||
	    ap_control_mac_deny(&ap->mac_restrictions, hdr->addr2)) अणु
		txt = "authentication denied";
		resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
		जाओ fail;
	पूर्ण

	अगर (((local->auth_algs & PRISM2_AUTH_OPEN) &&
	     auth_alg == WLAN_AUTH_OPEN) ||
	    ((local->auth_algs & PRISM2_AUTH_SHARED_KEY) &&
	     crypt && auth_alg == WLAN_AUTH_SHARED_KEY)) अणु
	पूर्ण अन्यथा अणु
		txt = "unsupported algorithm";
		resp = WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG;
		जाओ fail;
	पूर्ण

	अगर (len >= 8) अणु
		u8 *u = (u8 *) pos;
		अगर (*u == WLAN_EID_CHALLENGE) अणु
			अगर (*(u + 1) != WLAN_AUTH_CHALLENGE_LEN) अणु
				txt = "invalid challenge len";
				resp = WLAN_STATUS_CHALLENGE_FAIL;
				जाओ fail;
			पूर्ण
			अगर (len - 8 < WLAN_AUTH_CHALLENGE_LEN) अणु
				txt = "challenge underflow";
				resp = WLAN_STATUS_CHALLENGE_FAIL;
				जाओ fail;
			पूर्ण
			challenge = (अक्षर *) (u + 2);
		पूर्ण
	पूर्ण

	अगर (sta && sta->ap) अणु
		अगर (समय_after(jअगरfies, sta->u.ap.last_beacon +
			       (10 * sta->listen_पूर्णांकerval * HZ) / 1024)) अणु
			PDEBUG(DEBUG_AP, "%s: no beacons received for a while,"
			       " assuming AP %pM is now STA\n",
			       dev->name, sta->addr);
			sta->ap = 0;
			sta->flags = 0;
			sta->u.sta.challenge = शून्य;
		पूर्ण अन्यथा अणु
			txt = "AP trying to authenticate?";
			resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर ((auth_alg == WLAN_AUTH_OPEN && auth_transaction == 1) ||
	    (auth_alg == WLAN_AUTH_SHARED_KEY &&
	     (auth_transaction == 1 ||
	      (auth_transaction == 3 && sta != शून्य &&
	       sta->u.sta.challenge != शून्य)))) अणु
	पूर्ण अन्यथा अणु
		txt = "unknown authentication transaction number";
		resp = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
		जाओ fail;
	पूर्ण

	अगर (sta == शून्य) अणु
		txt = "new STA";

		अगर (local->ap->num_sta >= MAX_STA_COUNT) अणु
			/* FIX: might try to हटाओ some old STAs first? */
			txt = "no more room for new STAs";
			resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
			जाओ fail;
		पूर्ण

		sta = ap_add_sta(local->ap, hdr->addr2);
		अगर (sta == शून्य) अणु
			txt = "ap_add_sta failed";
			resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
			जाओ fail;
		पूर्ण
	पूर्ण

	चयन (auth_alg) अणु
	हाल WLAN_AUTH_OPEN:
		txt = "authOK";
		/* IEEE 802.11 standard is not completely clear about
		 * whether STA is considered authenticated after
		 * authentication OK frame has been send or after it
		 * has been ACKed. In order to reduce पूर्णांकeroperability
		 * issues, mark the STA authenticated beक्रमe ACK. */
		sta->flags |= WLAN_STA_AUTH;
		अवरोध;

	हाल WLAN_AUTH_SHARED_KEY:
		अगर (auth_transaction == 1) अणु
			अगर (sta->u.sta.challenge == शून्य) अणु
				sta->u.sta.challenge =
					ap_auth_make_challenge(local->ap);
				अगर (sta->u.sta.challenge == शून्य) अणु
					resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
					जाओ fail;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (sta->u.sta.challenge == शून्य ||
			    challenge == शून्य ||
			    स_भेद(sta->u.sta.challenge, challenge,
				   WLAN_AUTH_CHALLENGE_LEN) != 0 ||
			    !ieee80211_has_रक्षित(hdr->frame_control)) अणु
				txt = "challenge response incorrect";
				resp = WLAN_STATUS_CHALLENGE_FAIL;
				जाओ fail;
			पूर्ण

			txt = "challenge OK - authOK";
			/* IEEE 802.11 standard is not completely clear about
			 * whether STA is considered authenticated after
			 * authentication OK frame has been send or after it
			 * has been ACKed. In order to reduce पूर्णांकeroperability
			 * issues, mark the STA authenticated beक्रमe ACK. */
			sta->flags |= WLAN_STA_AUTH;
			kमुक्त(sta->u.sta.challenge);
			sta->u.sta.challenge = शून्य;
		पूर्ण
		अवरोध;
	पूर्ण

 fail:
	pos = (__le16 *) body;
	*pos = cpu_to_le16(auth_alg);
	pos++;
	*pos = cpu_to_le16(auth_transaction + 1);
	pos++;
	*pos = cpu_to_le16(resp); /* status_code */
	pos++;
	olen = 6;

	अगर (resp == WLAN_STATUS_SUCCESS && sta != शून्य &&
	    sta->u.sta.challenge != शून्य &&
	    auth_alg == WLAN_AUTH_SHARED_KEY && auth_transaction == 1) अणु
		u8 *पंचांगp = (u8 *) pos;
		*पंचांगp++ = WLAN_EID_CHALLENGE;
		*पंचांगp++ = WLAN_AUTH_CHALLENGE_LEN;
		pos++;
		स_नकल(pos, sta->u.sta.challenge, WLAN_AUTH_CHALLENGE_LEN);
		olen += 2 + WLAN_AUTH_CHALLENGE_LEN;
	पूर्ण

	prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_AUTH,
			 body, olen, hdr->addr2, ap->tx_callback_auth);

	अगर (sta) अणु
		sta->last_rx = jअगरfies;
		atomic_dec(&sta->users);
	पूर्ण

	अगर (resp) अणु
		PDEBUG(DEBUG_AP, "%s: %pM auth (alg=%d "
		       "trans#=%d stat=%d len=%d fc=%04x) ==> %d (%s)\n",
		       dev->name, hdr->addr2,
		       auth_alg, auth_transaction, status_code, len,
		       le16_to_cpu(hdr->frame_control), resp, txt);
	पूर्ण
पूर्ण


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम handle_assoc(local_info_t *local, काष्ठा sk_buff *skb,
			 काष्ठा hostap_80211_rx_status *rx_stats, पूर्णांक reassoc)
अणु
	काष्ठा net_device *dev = local->dev;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अक्षर body[12], *p, *lpos;
	पूर्णांक len, left;
	__le16 *pos;
	u16 resp = WLAN_STATUS_SUCCESS;
	काष्ठा sta_info *sta = शून्य;
	पूर्णांक send_deauth = 0;
	अक्षर __always_unused *txt = "";
	u8 prev_ap[ETH_ALEN];

	left = len = skb->len - IEEE80211_MGMT_HDR_LEN;

	अगर (len < (reassoc ? 10 : 4)) अणु
		PDEBUG(DEBUG_AP, "%s: handle_assoc - too short payload "
		       "(len=%d, reassoc=%d) from %pM\n",
		       dev->name, len, reassoc, hdr->addr2);
		वापस;
	पूर्ण

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta == शून्य || (sta->flags & WLAN_STA_AUTH) == 0) अणु
		spin_unlock_bh(&local->ap->sta_table_lock);
		txt = "trying to associate before authentication";
		send_deauth = 1;
		resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
		sta = शून्य; /* करो not decrement sta->users */
		जाओ fail;
	पूर्ण
	atomic_inc(&sta->users);
	spin_unlock_bh(&local->ap->sta_table_lock);

	pos = (__le16 *) (skb->data + IEEE80211_MGMT_HDR_LEN);
	sta->capability = __le16_to_cpu(*pos);
	pos++; left -= 2;
	sta->listen_पूर्णांकerval = __le16_to_cpu(*pos);
	pos++; left -= 2;

	अगर (reassoc) अणु
		स_नकल(prev_ap, pos, ETH_ALEN);
		pos++; pos++; pos++; left -= 6;
	पूर्ण अन्यथा
		eth_zero_addr(prev_ap);

	अगर (left >= 2) अणु
		अचिन्हित पूर्णांक ileft;
		अचिन्हित अक्षर *u = (अचिन्हित अक्षर *) pos;

		अगर (*u == WLAN_EID_SSID) अणु
			u++; left--;
			ileft = *u;
			u++; left--;

			अगर (ileft > left || ileft > MAX_SSID_LEN) अणु
				txt = "SSID overflow";
				resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
				जाओ fail;
			पूर्ण

			अगर (ileft != म_माप(local->essid) ||
			    स_भेद(local->essid, u, ileft) != 0) अणु
				txt = "not our SSID";
				resp = WLAN_STATUS_ASSOC_DENIED_UNSPEC;
				जाओ fail;
			पूर्ण

			u += ileft;
			left -= ileft;
		पूर्ण

		अगर (left >= 2 && *u == WLAN_EID_SUPP_RATES) अणु
			u++; left--;
			ileft = *u;
			u++; left--;

			अगर (ileft > left || ileft == 0 ||
			    ileft > WLAN_SUPP_RATES_MAX) अणु
				txt = "SUPP_RATES len error";
				resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
				जाओ fail;
			पूर्ण

			स_रखो(sta->supported_rates, 0,
			       माप(sta->supported_rates));
			स_नकल(sta->supported_rates, u, ileft);
			prism2_check_tx_rates(sta);

			u += ileft;
			left -= ileft;
		पूर्ण

		अगर (left > 0) अणु
			PDEBUG(DEBUG_AP, "%s: assoc from %pM"
			       " with extra data (%d bytes) [",
			       dev->name, hdr->addr2, left);
			जबतक (left > 0) अणु
				PDEBUG2(DEBUG_AP, "<%02x>", *u);
				u++; left--;
			पूर्ण
			PDEBUG2(DEBUG_AP, "]\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		txt = "frame underflow";
		resp = WLAN_STATUS_UNSPECIFIED_FAILURE;
		जाओ fail;
	पूर्ण

	/* get a unique AID */
	अगर (sta->aid > 0)
		txt = "OK, old AID";
	अन्यथा अणु
		spin_lock_bh(&local->ap->sta_table_lock);
		क्रम (sta->aid = 1; sta->aid <= MAX_AID_TABLE_SIZE; sta->aid++)
			अगर (local->ap->sta_aid[sta->aid - 1] == शून्य)
				अवरोध;
		अगर (sta->aid > MAX_AID_TABLE_SIZE) अणु
			sta->aid = 0;
			spin_unlock_bh(&local->ap->sta_table_lock);
			resp = WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA;
			txt = "no room for more AIDs";
		पूर्ण अन्यथा अणु
			local->ap->sta_aid[sta->aid - 1] = sta;
			spin_unlock_bh(&local->ap->sta_table_lock);
			txt = "OK, new AID";
		पूर्ण
	पूर्ण

 fail:
	pos = (__le16 *) body;

	अगर (send_deauth) अणु
		*pos = cpu_to_le16(WLAN_REASON_STA_REQ_ASSOC_WITHOUT_AUTH);
		pos++;
	पूर्ण अन्यथा अणु
		/* FIX: CF-Pollable and CF-PollReq should be set to match the
		 * values in beacons/probe responses */
		/* FIX: how about privacy and WEP? */
		/* capability */
		*pos = cpu_to_le16(WLAN_CAPABILITY_ESS);
		pos++;

		/* status_code */
		*pos = cpu_to_le16(resp);
		pos++;

		*pos = cpu_to_le16((sta && sta->aid > 0 ? sta->aid : 0) |
				     BIT(14) | BIT(15)); /* AID */
		pos++;

		/* Supported rates (Inक्रमmation element) */
		p = (अक्षर *) pos;
		*p++ = WLAN_EID_SUPP_RATES;
		lpos = p;
		*p++ = 0; /* len */
		अगर (local->tx_rate_control & WLAN_RATE_1M) अणु
			*p++ = local->basic_rates & WLAN_RATE_1M ? 0x82 : 0x02;
			(*lpos)++;
		पूर्ण
		अगर (local->tx_rate_control & WLAN_RATE_2M) अणु
			*p++ = local->basic_rates & WLAN_RATE_2M ? 0x84 : 0x04;
			(*lpos)++;
		पूर्ण
		अगर (local->tx_rate_control & WLAN_RATE_5M5) अणु
			*p++ = local->basic_rates & WLAN_RATE_5M5 ?
				0x8b : 0x0b;
			(*lpos)++;
		पूर्ण
		अगर (local->tx_rate_control & WLAN_RATE_11M) अणु
			*p++ = local->basic_rates & WLAN_RATE_11M ?
				0x96 : 0x16;
			(*lpos)++;
		पूर्ण
		pos = (__le16 *) p;
	पूर्ण

	prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT |
			 (send_deauth ? IEEE80211_STYPE_DEAUTH :
			  (reassoc ? IEEE80211_STYPE_REASSOC_RESP :
			   IEEE80211_STYPE_ASSOC_RESP)),
			 body, (u8 *) pos - (u8 *) body,
			 hdr->addr2,
			 send_deauth ? 0 : local->ap->tx_callback_assoc);

	अगर (sta) अणु
		अगर (resp == WLAN_STATUS_SUCCESS) अणु
			sta->last_rx = jअगरfies;
			/* STA will be marked associated from TX callback, अगर
			 * AssocResp is ACKed */
		पूर्ण
		atomic_dec(&sta->users);
	पूर्ण

#अगर 0
	PDEBUG(DEBUG_AP, "%s: %pM %sassoc (len=%d "
	       "prev_ap=%pM) => %d(%d) (%s)\n",
	       dev->name,
	       hdr->addr2,
	       reassoc ? "re" : "", len,
	       prev_ap,
	       resp, send_deauth, txt);
#पूर्ण_अगर
पूर्ण


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम handle_deauth(local_info_t *local, काष्ठा sk_buff *skb,
			  काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा net_device *dev = local->dev;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अक्षर *body = (अक्षर *) (skb->data + IEEE80211_MGMT_HDR_LEN);
	पूर्णांक len;
	u16 reason_code;
	__le16 *pos;
	काष्ठा sta_info *sta = शून्य;

	len = skb->len - IEEE80211_MGMT_HDR_LEN;

	अगर (len < 2) अणु
		prपूर्णांकk("handle_deauth - too short payload (len=%d)\n", len);
		वापस;
	पूर्ण

	pos = (__le16 *) body;
	reason_code = le16_to_cpu(*pos);

	PDEBUG(DEBUG_AP, "%s: deauthentication: %pM len=%d, "
	       "reason_code=%d\n", dev->name, hdr->addr2,
	       len, reason_code);

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta != शून्य) अणु
		अगर ((sta->flags & WLAN_STA_ASSOC) && !sta->ap)
			hostap_event_expired_sta(local->dev, sta);
		sta->flags &= ~(WLAN_STA_AUTH | WLAN_STA_ASSOC);
	पूर्ण
	spin_unlock_bh(&local->ap->sta_table_lock);
	अगर (sta == शून्य) अणु
		prपूर्णांकk("%s: deauthentication from %pM, "
	       "reason_code=%d, but STA not authenticated\n", dev->name,
		       hdr->addr2, reason_code);
	पूर्ण
पूर्ण


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम handle_disassoc(local_info_t *local, काष्ठा sk_buff *skb,
			    काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा net_device *dev = local->dev;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अक्षर *body = skb->data + IEEE80211_MGMT_HDR_LEN;
	पूर्णांक len;
	u16 reason_code;
	__le16 *pos;
	काष्ठा sta_info *sta = शून्य;

	len = skb->len - IEEE80211_MGMT_HDR_LEN;

	अगर (len < 2) अणु
		prपूर्णांकk("handle_disassoc - too short payload (len=%d)\n", len);
		वापस;
	पूर्ण

	pos = (__le16 *) body;
	reason_code = le16_to_cpu(*pos);

	PDEBUG(DEBUG_AP, "%s: disassociation: %pM len=%d, "
	       "reason_code=%d\n", dev->name, hdr->addr2,
	       len, reason_code);

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta != शून्य) अणु
		अगर ((sta->flags & WLAN_STA_ASSOC) && !sta->ap)
			hostap_event_expired_sta(local->dev, sta);
		sta->flags &= ~WLAN_STA_ASSOC;
	पूर्ण
	spin_unlock_bh(&local->ap->sta_table_lock);
	अगर (sta == शून्य) अणु
		prपूर्णांकk("%s: disassociation from %pM, "
		       "reason_code=%d, but STA not authenticated\n",
		       dev->name, hdr->addr2, reason_code);
	पूर्ण
पूर्ण


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम ap_handle_data_nullfunc(local_info_t *local,
				    काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा net_device *dev = local->dev;

	/* some STA f/w's seem to require control::ACK frame क्रम
	 * data::nullfunc, but at least Prism2 station f/w version 0.8.0 करोes
	 * not send this..
	 * send control::ACK क्रम the data::nullfunc */

	prपूर्णांकk(KERN_DEBUG "Sending control::ACK for data::nullfunc\n");
	prism2_send_mgmt(dev, IEEE80211_FTYPE_CTL | IEEE80211_STYPE_ACK,
			 शून्य, 0, hdr->addr2, 0);
पूर्ण


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम ap_handle_dropped_data(local_info_t *local,
				   काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा net_device *dev = local->dev;
	काष्ठा sta_info *sta;
	__le16 reason;

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock_bh(&local->ap->sta_table_lock);

	अगर (sta != शून्य && (sta->flags & WLAN_STA_ASSOC)) अणु
		PDEBUG(DEBUG_AP, "ap_handle_dropped_data: STA is now okay?\n");
		atomic_dec(&sta->users);
		वापस;
	पूर्ण

	reason = cpu_to_le16(WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);
	prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT |
			 ((sta == शून्य || !(sta->flags & WLAN_STA_ASSOC)) ?
			  IEEE80211_STYPE_DEAUTH : IEEE80211_STYPE_DISASSOC),
			 (अक्षर *) &reason, माप(reason), hdr->addr2, 0);

	अगर (sta)
		atomic_dec(&sta->users);
पूर्ण

#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम pspoll_send_buffered(local_info_t *local, काष्ठा sta_info *sta,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा hostap_skb_tx_data *meta;

	अगर (!(sta->flags & WLAN_STA_PS)) अणु
		/* Station has moved to non-PS mode, so send all buffered
		 * frames using normal device queue. */
		dev_queue_xmit(skb);
		वापस;
	पूर्ण

	/* add a flag क्रम hostap_handle_sta_tx() to know that this skb should
	 * be passed through even though STA is using PS */
	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
	meta->flags |= HOSTAP_TX_FLAGS_BUFFERED_FRAME;
	अगर (!skb_queue_empty(&sta->tx_buf)) अणु
		/* indicate to STA that more frames follow */
		meta->flags |= HOSTAP_TX_FLAGS_ADD_MOREDATA;
	पूर्ण
	dev_queue_xmit(skb);
पूर्ण


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम handle_pspoll(local_info_t *local,
			  काष्ठा ieee80211_hdr *hdr,
			  काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा net_device *dev = local->dev;
	काष्ठा sta_info *sta;
	u16 aid;
	काष्ठा sk_buff *skb;

	PDEBUG(DEBUG_PS2, "handle_pspoll: BSSID=%pM, TA=%pM PWRMGT=%d\n",
	       hdr->addr1, hdr->addr2, !!ieee80211_has_pm(hdr->frame_control));

	अगर (!ether_addr_equal(hdr->addr1, dev->dev_addr)) अणु
		PDEBUG(DEBUG_AP,
		       "handle_pspoll - addr1(BSSID)=%pM not own MAC\n",
		       hdr->addr1);
		वापस;
	पूर्ण

	aid = le16_to_cpu(hdr->duration_id);
	अगर ((aid & (BIT(15) | BIT(14))) != (BIT(15) | BIT(14))) अणु
		PDEBUG(DEBUG_PS, "   PSPOLL and AID[15:14] not set\n");
		वापस;
	पूर्ण
	aid &= ~(BIT(15) | BIT(14));
	अगर (aid == 0 || aid > MAX_AID_TABLE_SIZE) अणु
		PDEBUG(DEBUG_PS, "   invalid aid=%d\n", aid);
		वापस;
	पूर्ण
	PDEBUG(DEBUG_PS2, "   aid=%d\n", aid);

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock_bh(&local->ap->sta_table_lock);

	अगर (sta == शून्य) अणु
		PDEBUG(DEBUG_PS, "   STA not found\n");
		वापस;
	पूर्ण
	अगर (sta->aid != aid) अणु
		PDEBUG(DEBUG_PS, "   received aid=%i does not match with "
		       "assoc.aid=%d\n", aid, sta->aid);
		वापस;
	पूर्ण

	/* FIX: toकरो:
	 * - add समयout क्रम buffering (clear aid in TIM vector अगर buffer समयd
	 *   out (expiry समय must be दीर्घer than ListenInterval क्रम
	 *   the corresponding STA; "8802-11: 11.2.1.9 AP aging function"
	 * - what to करो, अगर buffered, pspolled, and sent frame is not ACKed by
	 *   sta; store buffer क्रम later use and leave TIM aid bit set? use
	 *   TX event to check whether frame was ACKed?
	 */

	जबतक ((skb = skb_dequeue(&sta->tx_buf)) != शून्य) अणु
		/* send buffered frame .. */
		PDEBUG(DEBUG_PS2, "Sending buffered frame to STA after PS POLL"
		       " (buffer_count=%d)\n", skb_queue_len(&sta->tx_buf));

		pspoll_send_buffered(local, sta, skb);

		अगर (sta->flags & WLAN_STA_PS) अणु
			/* send only one buffered packet per PS Poll */
			/* FIX: should ignore further PS Polls until the
			 * buffered packet that was just sent is acknowledged
			 * (Tx or TxExc event) */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (skb_queue_empty(&sta->tx_buf)) अणु
		/* try to clear aid from TIM */
		अगर (!(sta->flags & WLAN_STA_TIM))
			PDEBUG(DEBUG_PS2,  "Re-unsetting TIM for aid %d\n",
			       aid);
		hostap_set_tim(local, aid, 0);
		sta->flags &= ~WLAN_STA_TIM;
	पूर्ण

	atomic_dec(&sta->users);
पूर्ण


#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT

अटल व्योम handle_wds_oper_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ap_data *ap = container_of(work, काष्ठा ap_data,
					  wds_oper_queue);
	local_info_t *local = ap->local;
	काष्ठा wds_oper_data *entry, *prev;

	spin_lock_bh(&local->lock);
	entry = local->ap->wds_oper_entries;
	local->ap->wds_oper_entries = शून्य;
	spin_unlock_bh(&local->lock);

	जबतक (entry) अणु
		PDEBUG(DEBUG_AP, "%s: %s automatic WDS connection "
		       "to AP %pM\n",
		       local->dev->name,
		       entry->type == WDS_ADD ? "adding" : "removing",
		       entry->addr);
		अगर (entry->type == WDS_ADD)
			prism2_wds_add(local, entry->addr, 0);
		अन्यथा अगर (entry->type == WDS_DEL)
			prism2_wds_del(local, entry->addr, 0, 1);

		prev = entry;
		entry = entry->next;
		kमुक्त(prev);
	पूर्ण
पूर्ण


/* Called only as a scheduled task क्रम pending AP frames. */
अटल व्योम handle_beacon(local_info_t *local, काष्ठा sk_buff *skb,
			  काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अक्षर *body = skb->data + IEEE80211_MGMT_HDR_LEN;
	पूर्णांक len, left;
	u16 beacon_पूर्णांक, capability;
	__le16 *pos;
	अक्षर *ssid = शून्य;
	अचिन्हित अक्षर *supp_rates = शून्य;
	पूर्णांक ssid_len = 0, supp_rates_len = 0;
	काष्ठा sta_info *sta = शून्य;
	पूर्णांक new_sta = 0, channel = -1;

	len = skb->len - IEEE80211_MGMT_HDR_LEN;

	अगर (len < 8 + 2 + 2) अणु
		prपूर्णांकk(KERN_DEBUG "handle_beacon - too short payload "
		       "(len=%d)\n", len);
		वापस;
	पूर्ण

	pos = (__le16 *) body;
	left = len;

	/* Timestamp (8 octets) */
	pos += 4; left -= 8;
	/* Beacon पूर्णांकerval (2 octets) */
	beacon_पूर्णांक = le16_to_cpu(*pos);
	pos++; left -= 2;
	/* Capability inक्रमmation (2 octets) */
	capability = le16_to_cpu(*pos);
	pos++; left -= 2;

	अगर (local->ap->ap_policy != AP_OTHER_AP_EVEN_IBSS &&
	    capability & WLAN_CAPABILITY_IBSS)
		वापस;

	अगर (left >= 2) अणु
		अचिन्हित पूर्णांक ileft;
		अचिन्हित अक्षर *u = (अचिन्हित अक्षर *) pos;

		अगर (*u == WLAN_EID_SSID) अणु
			u++; left--;
			ileft = *u;
			u++; left--;

			अगर (ileft > left || ileft > MAX_SSID_LEN) अणु
				PDEBUG(DEBUG_AP, "SSID: overflow\n");
				वापस;
			पूर्ण

			अगर (local->ap->ap_policy == AP_OTHER_AP_SAME_SSID &&
			    (ileft != म_माप(local->essid) ||
			     स_भेद(local->essid, u, ileft) != 0)) अणु
				/* not our SSID */
				वापस;
			पूर्ण

			ssid = u;
			ssid_len = ileft;

			u += ileft;
			left -= ileft;
		पूर्ण

		अगर (*u == WLAN_EID_SUPP_RATES) अणु
			u++; left--;
			ileft = *u;
			u++; left--;

			अगर (ileft > left || ileft == 0 || ileft > 8) अणु
				PDEBUG(DEBUG_AP, " - SUPP_RATES len error\n");
				वापस;
			पूर्ण

			supp_rates = u;
			supp_rates_len = ileft;

			u += ileft;
			left -= ileft;
		पूर्ण

		अगर (*u == WLAN_EID_DS_PARAMS) अणु
			u++; left--;
			ileft = *u;
			u++; left--;

			अगर (ileft > left || ileft != 1) अणु
				PDEBUG(DEBUG_AP, " - DS_PARAMS len error\n");
				वापस;
			पूर्ण

			channel = *u;

			u += ileft;
			left -= ileft;
		पूर्ण
	पूर्ण

	spin_lock_bh(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta != शून्य)
		atomic_inc(&sta->users);
	spin_unlock_bh(&local->ap->sta_table_lock);

	अगर (sta == शून्य) अणु
		/* add new AP */
		new_sta = 1;
		sta = ap_add_sta(local->ap, hdr->addr2);
		अगर (sta == शून्य) अणु
			prपूर्णांकk(KERN_INFO "prism2: kmalloc failed for AP "
			       "data structure\n");
			वापस;
		पूर्ण
		hostap_event_new_sta(local->dev, sta);

		/* mark APs authentication and associated क्रम pseuकरो ad-hoc
		 * style communication */
		sta->flags = WLAN_STA_AUTH | WLAN_STA_ASSOC;

		अगर (local->ap->स्वतःm_ap_wds) अणु
			hostap_wds_link_oper(local, sta->addr, WDS_ADD);
		पूर्ण
	पूर्ण

	sta->ap = 1;
	अगर (ssid) अणु
		sta->u.ap.ssid_len = ssid_len;
		स_नकल(sta->u.ap.ssid, ssid, ssid_len);
		sta->u.ap.ssid[ssid_len] = '\0';
	पूर्ण अन्यथा अणु
		sta->u.ap.ssid_len = 0;
		sta->u.ap.ssid[0] = '\0';
	पूर्ण
	sta->u.ap.channel = channel;
	sta->rx_packets++;
	sta->rx_bytes += len;
	sta->u.ap.last_beacon = sta->last_rx = jअगरfies;
	sta->capability = capability;
	sta->listen_पूर्णांकerval = beacon_पूर्णांक;

	atomic_dec(&sta->users);

	अगर (new_sta) अणु
		स_रखो(sta->supported_rates, 0, माप(sta->supported_rates));
		स_नकल(sta->supported_rates, supp_rates, supp_rates_len);
		prism2_check_tx_rates(sta);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


/* Called only as a tasklet. */
अटल व्योम handle_ap_item(local_info_t *local, काष्ठा sk_buff *skb,
			   काष्ठा hostap_80211_rx_status *rx_stats)
अणु
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	काष्ठा net_device *dev = local->dev;
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */
	u16 fc, type, stype;
	काष्ठा ieee80211_hdr *hdr;

	/* FIX: should give skb->len to handler functions and check that the
	 * buffer is दीर्घ enough */
	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	fc = le16_to_cpu(hdr->frame_control);
	type = fc & IEEE80211_FCTL_FTYPE;
	stype = fc & IEEE80211_FCTL_STYPE;

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	अगर (!local->hostapd && type == IEEE80211_FTYPE_DATA) अणु
		PDEBUG(DEBUG_AP, "handle_ap_item - data frame\n");

		अगर (!(fc & IEEE80211_FCTL_TODS) ||
		    (fc & IEEE80211_FCTL_FROMDS)) अणु
			अगर (stype == IEEE80211_STYPE_शून्यFUNC) अणु
				/* no ToDS nullfunc seems to be used to check
				 * AP association; so send reject message to
				 * speed up re-association */
				ap_handle_dropped_data(local, hdr);
				जाओ करोne;
			पूर्ण
			PDEBUG(DEBUG_AP, "   not ToDS frame (fc=0x%04x)\n",
			       fc);
			जाओ करोne;
		पूर्ण

		अगर (!ether_addr_equal(hdr->addr1, dev->dev_addr)) अणु
			PDEBUG(DEBUG_AP, "handle_ap_item - addr1(BSSID)=%pM"
			       " not own MAC\n", hdr->addr1);
			जाओ करोne;
		पूर्ण

		अगर (local->ap->nullfunc_ack &&
		    stype == IEEE80211_STYPE_शून्यFUNC)
			ap_handle_data_nullfunc(local, hdr);
		अन्यथा
			ap_handle_dropped_data(local, hdr);
		जाओ करोne;
	पूर्ण

	अगर (type == IEEE80211_FTYPE_MGMT && stype == IEEE80211_STYPE_BEACON) अणु
		handle_beacon(local, skb, rx_stats);
		जाओ करोne;
	पूर्ण
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

	अगर (type == IEEE80211_FTYPE_CTL && stype == IEEE80211_STYPE_PSPOLL) अणु
		handle_pspoll(local, hdr, rx_stats);
		जाओ करोne;
	पूर्ण

	अगर (local->hostapd) अणु
		PDEBUG(DEBUG_AP, "Unknown frame in AP queue: type=0x%02x "
		       "subtype=0x%02x\n", type, stype);
		जाओ करोne;
	पूर्ण

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	अगर (type != IEEE80211_FTYPE_MGMT) अणु
		PDEBUG(DEBUG_AP, "handle_ap_item - not a management frame?\n");
		जाओ करोne;
	पूर्ण

	अगर (!ether_addr_equal(hdr->addr1, dev->dev_addr)) अणु
		PDEBUG(DEBUG_AP, "handle_ap_item - addr1(DA)=%pM"
		       " not own MAC\n", hdr->addr1);
		जाओ करोne;
	पूर्ण

	अगर (!ether_addr_equal(hdr->addr3, dev->dev_addr)) अणु
		PDEBUG(DEBUG_AP, "handle_ap_item - addr3(BSSID)=%pM"
		       " not own MAC\n", hdr->addr3);
		जाओ करोne;
	पूर्ण

	चयन (stype) अणु
	हाल IEEE80211_STYPE_ASSOC_REQ:
		handle_assoc(local, skb, rx_stats, 0);
		अवरोध;
	हाल IEEE80211_STYPE_ASSOC_RESP:
		PDEBUG(DEBUG_AP, "==> ASSOC RESP (ignored)\n");
		अवरोध;
	हाल IEEE80211_STYPE_REASSOC_REQ:
		handle_assoc(local, skb, rx_stats, 1);
		अवरोध;
	हाल IEEE80211_STYPE_REASSOC_RESP:
		PDEBUG(DEBUG_AP, "==> REASSOC RESP (ignored)\n");
		अवरोध;
	हाल IEEE80211_STYPE_ATIM:
		PDEBUG(DEBUG_AP, "==> ATIM (ignored)\n");
		अवरोध;
	हाल IEEE80211_STYPE_DISASSOC:
		handle_disassoc(local, skb, rx_stats);
		अवरोध;
	हाल IEEE80211_STYPE_AUTH:
		handle_authen(local, skb, rx_stats);
		अवरोध;
	हाल IEEE80211_STYPE_DEAUTH:
		handle_deauth(local, skb, rx_stats);
		अवरोध;
	शेष:
		PDEBUG(DEBUG_AP, "Unknown mgmt frame subtype 0x%02x\n",
		       stype >> 4);
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

 करोne:
	dev_kमुक्त_skb(skb);
पूर्ण


/* Called only as a tasklet (software IRQ) */
व्योम hostap_rx(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
	       काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा ieee80211_hdr *hdr;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (skb->len < 16)
		जाओ drop;

	dev->stats.rx_packets++;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	अगर (local->ap->ap_policy == AP_OTHER_AP_SKIP_ALL &&
	    ieee80211_is_beacon(hdr->frame_control))
		जाओ drop;

	skb->protocol = cpu_to_be16(ETH_P_HOSTAP);
	handle_ap_item(local, skb, rx_stats);
	वापस;

 drop:
	dev_kमुक्त_skb(skb);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम schedule_packet_send(local_info_t *local, काष्ठा sta_info *sta)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा hostap_80211_rx_status rx_stats;

	अगर (skb_queue_empty(&sta->tx_buf))
		वापस;

	skb = dev_alloc_skb(16);
	अगर (skb == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "%s: schedule_packet_send: skb alloc "
		       "failed\n", local->dev->name);
		वापस;
	पूर्ण

	hdr = skb_put(skb, 16);

	/* Generate a fake pspoll frame to start packet delivery */
	hdr->frame_control = cpu_to_le16(
		IEEE80211_FTYPE_CTL | IEEE80211_STYPE_PSPOLL);
	स_नकल(hdr->addr1, local->dev->dev_addr, ETH_ALEN);
	स_नकल(hdr->addr2, sta->addr, ETH_ALEN);
	hdr->duration_id = cpu_to_le16(sta->aid | BIT(15) | BIT(14));

	PDEBUG(DEBUG_PS2,
	       "%s: Scheduling buffered packet delivery for STA %pM\n",
	       local->dev->name, sta->addr);

	skb->dev = local->dev;

	स_रखो(&rx_stats, 0, माप(rx_stats));
	hostap_rx(local->dev, skb, &rx_stats);
पूर्ण


पूर्णांक prism2_ap_get_sta_qual(local_info_t *local, काष्ठा sockaddr addr[],
			   काष्ठा iw_quality qual[], पूर्णांक buf_size,
			   पूर्णांक aplist)
अणु
	काष्ठा ap_data *ap = local->ap;
	काष्ठा list_head *ptr;
	पूर्णांक count = 0;

	spin_lock_bh(&ap->sta_table_lock);

	क्रम (ptr = ap->sta_list.next; ptr != शून्य && ptr != &ap->sta_list;
	     ptr = ptr->next) अणु
		काष्ठा sta_info *sta = (काष्ठा sta_info *) ptr;

		अगर (aplist && !sta->ap)
			जारी;
		addr[count].sa_family = ARPHRD_ETHER;
		स_नकल(addr[count].sa_data, sta->addr, ETH_ALEN);
		अगर (sta->last_rx_silence == 0)
			qual[count].qual = sta->last_rx_संकेत < 27 ?
				0 : (sta->last_rx_संकेत - 27) * 92 / 127;
		अन्यथा
			qual[count].qual = sta->last_rx_संकेत -
				sta->last_rx_silence - 35;
		qual[count].level = HFA384X_LEVEL_TO_dBm(sta->last_rx_संकेत);
		qual[count].noise = HFA384X_LEVEL_TO_dBm(sta->last_rx_silence);
		qual[count].updated = sta->last_rx_updated;

		sta->last_rx_updated = IW_QUAL_DBM;

		count++;
		अगर (count >= buf_size)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&ap->sta_table_lock);

	वापस count;
पूर्ण


/* Translate our list of Access Poपूर्णांकs & Stations to a card independent
 * क्रमmat that the Wireless Tools will understand - Jean II */
पूर्णांक prism2_ap_translate_scan(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info, अक्षर *buffer)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा ap_data *ap;
	काष्ठा list_head *ptr;
	काष्ठा iw_event iwe;
	अक्षर *current_ev = buffer;
	अक्षर *end_buf = buffer + IW_SCAN_MAX_DATA;
#अगर !defined(PRISM2_NO_KERNEL_IEEE80211_MGMT)
	अक्षर buf[64];
#पूर्ण_अगर

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	ap = local->ap;

	spin_lock_bh(&ap->sta_table_lock);

	क्रम (ptr = ap->sta_list.next; ptr != शून्य && ptr != &ap->sta_list;
	     ptr = ptr->next) अणु
		काष्ठा sta_info *sta = (काष्ठा sta_info *) ptr;

		/* First entry *MUST* be the AP MAC address */
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = SIOCGIWAP;
		iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
		स_नकल(iwe.u.ap_addr.sa_data, sta->addr, ETH_ALEN);
		iwe.len = IW_EV_ADDR_LEN;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_ADDR_LEN);

		/* Use the mode to indicate अगर it's a station or
		 * an Access Poपूर्णांक */
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = SIOCGIWMODE;
		अगर (sta->ap)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_INFRA;
		iwe.len = IW_EV_UINT_LEN;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_UINT_LEN);

		/* Some quality */
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVQUAL;
		अगर (sta->last_rx_silence == 0)
			iwe.u.qual.qual = sta->last_rx_संकेत < 27 ?
				0 : (sta->last_rx_संकेत - 27) * 92 / 127;
		अन्यथा
			iwe.u.qual.qual = sta->last_rx_संकेत -
				sta->last_rx_silence - 35;
		iwe.u.qual.level = HFA384X_LEVEL_TO_dBm(sta->last_rx_संकेत);
		iwe.u.qual.noise = HFA384X_LEVEL_TO_dBm(sta->last_rx_silence);
		iwe.u.qual.updated = sta->last_rx_updated;
		iwe.len = IW_EV_QUAL_LEN;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_QUAL_LEN);

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
		अगर (sta->ap) अणु
			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = SIOCGIWESSID;
			iwe.u.data.length = sta->u.ap.ssid_len;
			iwe.u.data.flags = 1;
			current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
							  end_buf, &iwe,
							  sta->u.ap.ssid);

			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = SIOCGIWENCODE;
			अगर (sta->capability & WLAN_CAPABILITY_PRIVACY)
				iwe.u.data.flags =
					IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
			अन्यथा
				iwe.u.data.flags = IW_ENCODE_DISABLED;
			current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
							  end_buf, &iwe,
							  sta->u.ap.ssid);

			अगर (sta->u.ap.channel > 0 &&
			    sta->u.ap.channel <= FREQ_COUNT) अणु
				स_रखो(&iwe, 0, माप(iwe));
				iwe.cmd = SIOCGIWFREQ;
				iwe.u.freq.m = freq_list[sta->u.ap.channel - 1]
					* 100000;
				iwe.u.freq.e = 1;
				current_ev = iwe_stream_add_event(
					info, current_ev, end_buf, &iwe,
					IW_EV_FREQ_LEN);
			पूर्ण

			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = IWEVCUSTOM;
			प्र_लिखो(buf, "beacon_interval=%d",
				sta->listen_पूर्णांकerval);
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
							  end_buf, &iwe, buf);
		पूर्ण
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

		sta->last_rx_updated = IW_QUAL_DBM;

		/* To be जारीd, we should make good use of IWEVCUSTOM */
	पूर्ण

	spin_unlock_bh(&ap->sta_table_lock);

	वापस current_ev - buffer;
पूर्ण


अटल पूर्णांक prism2_hostapd_add_sta(काष्ठा ap_data *ap,
				  काष्ठा prism2_hostapd_param *param)
अणु
	काष्ठा sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, param->sta_addr);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock_bh(&ap->sta_table_lock);

	अगर (sta == शून्य) अणु
		sta = ap_add_sta(ap, param->sta_addr);
		अगर (sta == शून्य)
			वापस -1;
	पूर्ण

	अगर (!(sta->flags & WLAN_STA_ASSOC) && !sta->ap && sta->local)
		hostap_event_new_sta(sta->local->dev, sta);

	sta->flags |= WLAN_STA_AUTH | WLAN_STA_ASSOC;
	sta->last_rx = jअगरfies;
	sta->aid = param->u.add_sta.aid;
	sta->capability = param->u.add_sta.capability;
	sta->tx_supp_rates = param->u.add_sta.tx_supp_rates;
	अगर (sta->tx_supp_rates & WLAN_RATE_1M)
		sta->supported_rates[0] = 2;
	अगर (sta->tx_supp_rates & WLAN_RATE_2M)
		sta->supported_rates[1] = 4;
	अगर (sta->tx_supp_rates & WLAN_RATE_5M5)
		sta->supported_rates[2] = 11;
	अगर (sta->tx_supp_rates & WLAN_RATE_11M)
		sta->supported_rates[3] = 22;
	prism2_check_tx_rates(sta);
	atomic_dec(&sta->users);
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_hostapd_हटाओ_sta(काष्ठा ap_data *ap,
				     काष्ठा prism2_hostapd_param *param)
अणु
	काष्ठा sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, param->sta_addr);
	अगर (sta) अणु
		ap_sta_hash_del(ap, sta);
		list_del(&sta->list);
	पूर्ण
	spin_unlock_bh(&ap->sta_table_lock);

	अगर (!sta)
		वापस -ENOENT;

	अगर ((sta->flags & WLAN_STA_ASSOC) && !sta->ap && sta->local)
		hostap_event_expired_sta(sta->local->dev, sta);
	ap_मुक्त_sta(ap, sta);

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_hostapd_get_info_sta(काष्ठा ap_data *ap,
				       काष्ठा prism2_hostapd_param *param)
अणु
	काष्ठा sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, param->sta_addr);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock_bh(&ap->sta_table_lock);

	अगर (!sta)
		वापस -ENOENT;

	param->u.get_info_sta.inactive_sec = (jअगरfies - sta->last_rx) / HZ;

	atomic_dec(&sta->users);

	वापस 1;
पूर्ण


अटल पूर्णांक prism2_hostapd_set_flags_sta(काष्ठा ap_data *ap,
					काष्ठा prism2_hostapd_param *param)
अणु
	काष्ठा sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, param->sta_addr);
	अगर (sta) अणु
		sta->flags |= param->u.set_flags_sta.flags_or;
		sta->flags &= param->u.set_flags_sta.flags_and;
	पूर्ण
	spin_unlock_bh(&ap->sta_table_lock);

	अगर (!sta)
		वापस -ENOENT;

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_hostapd_sta_clear_stats(काष्ठा ap_data *ap,
					  काष्ठा prism2_hostapd_param *param)
अणु
	काष्ठा sta_info *sta;
	पूर्णांक rate;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, param->sta_addr);
	अगर (sta) अणु
		sta->rx_packets = sta->tx_packets = 0;
		sta->rx_bytes = sta->tx_bytes = 0;
		क्रम (rate = 0; rate < WLAN_RATE_COUNT; rate++) अणु
			sta->tx_count[rate] = 0;
			sta->rx_count[rate] = 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ap->sta_table_lock);

	अगर (!sta)
		वापस -ENOENT;

	वापस 0;
पूर्ण


पूर्णांक prism2_hostapd(काष्ठा ap_data *ap, काष्ठा prism2_hostapd_param *param)
अणु
	चयन (param->cmd) अणु
	हाल PRISM2_HOSTAPD_FLUSH:
		ap_control_kickall(ap);
		वापस 0;
	हाल PRISM2_HOSTAPD_ADD_STA:
		वापस prism2_hostapd_add_sta(ap, param);
	हाल PRISM2_HOSTAPD_REMOVE_STA:
		वापस prism2_hostapd_हटाओ_sta(ap, param);
	हाल PRISM2_HOSTAPD_GET_INFO_STA:
		वापस prism2_hostapd_get_info_sta(ap, param);
	हाल PRISM2_HOSTAPD_SET_FLAGS_STA:
		वापस prism2_hostapd_set_flags_sta(ap, param);
	हाल PRISM2_HOSTAPD_STA_CLEAR_STATS:
		वापस prism2_hostapd_sta_clear_stats(ap, param);
	शेष:
		prपूर्णांकk(KERN_WARNING "prism2_hostapd: unknown cmd=%d\n",
		       param->cmd);
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण


/* Update station info क्रम host-based TX rate control and वापस current
 * TX rate */
अटल पूर्णांक ap_update_sta_tx_rate(काष्ठा sta_info *sta, काष्ठा net_device *dev)
अणु
	पूर्णांक ret = sta->tx_rate;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	sta->tx_count[sta->tx_rate_idx]++;
	sta->tx_since_last_failure++;
	sta->tx_consecutive_exc = 0;
	अगर (sta->tx_since_last_failure >= WLAN_RATE_UPDATE_COUNT &&
	    sta->tx_rate_idx < sta->tx_max_rate) अणु
		/* use next higher rate */
		पूर्णांक old_rate, new_rate;
		old_rate = new_rate = sta->tx_rate_idx;
		जबतक (new_rate < sta->tx_max_rate) अणु
			new_rate++;
			अगर (ap_tx_rate_ok(new_rate, sta, local)) अणु
				sta->tx_rate_idx = new_rate;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (old_rate != sta->tx_rate_idx) अणु
			चयन (sta->tx_rate_idx) अणु
			हाल 0: sta->tx_rate = 10; अवरोध;
			हाल 1: sta->tx_rate = 20; अवरोध;
			हाल 2: sta->tx_rate = 55; अवरोध;
			हाल 3: sta->tx_rate = 110; अवरोध;
			शेष: sta->tx_rate = 0; अवरोध;
			पूर्ण
			PDEBUG(DEBUG_AP, "%s: STA %pM TX rate raised to %d\n",
			       dev->name, sta->addr, sta->tx_rate);
		पूर्ण
		sta->tx_since_last_failure = 0;
	पूर्ण

	वापस ret;
पूर्ण


/* Called only from software IRQ. Called क्रम each TX frame prior possible
 * encryption and transmit. */
ap_tx_ret hostap_handle_sta_tx(local_info_t *local, काष्ठा hostap_tx_data *tx)
अणु
	काष्ठा sta_info *sta = शून्य;
	काष्ठा sk_buff *skb = tx->skb;
	पूर्णांक set_tim, ret;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा hostap_skb_tx_data *meta;

	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
	ret = AP_TX_CONTINUE;
	अगर (local->ap == शून्य || skb->len < 10 ||
	    meta->अगरace->type == HOSTAP_INTERFACE_STA)
		जाओ out;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	अगर (hdr->addr1[0] & 0x01) अणु
		/* broadcast/multicast frame - no AP related processing */
		अगर (local->ap->num_sta <= 0)
			ret = AP_TX_DROP;
		जाओ out;
	पूर्ण

	/* unicast packet - check whether destination STA is associated */
	spin_lock(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr1);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock(&local->ap->sta_table_lock);

	अगर (local->iw_mode == IW_MODE_MASTER && sta == शून्य &&
	    !(meta->flags & HOSTAP_TX_FLAGS_WDS) &&
	    meta->अगरace->type != HOSTAP_INTERFACE_MASTER &&
	    meta->अगरace->type != HOSTAP_INTERFACE_AP) अणु
#अगर 0
		/* This can happen, e.g., when wlan0 is added to a bridge and
		 * bridging code करोes not know which port is the correct target
		 * क्रम a unicast frame. In this हाल, the packet is send to all
		 * ports of the bridge. Since this is a valid scenario, करो not
		 * prपूर्णांक out any errors here. */
		अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "AP: drop packet to non-associated "
			       "STA %pM\n", hdr->addr1);
		पूर्ण
#पूर्ण_अगर
		local->ap->tx_drop_nonassoc++;
		ret = AP_TX_DROP;
		जाओ out;
	पूर्ण

	अगर (sta == शून्य)
		जाओ out;

	अगर (!(sta->flags & WLAN_STA_AUTHORIZED))
		ret = AP_TX_CONTINUE_NOT_AUTHORIZED;

	/* Set tx_rate अगर using host-based TX rate control */
	अगर (!local->fw_tx_rate_control)
		local->ap->last_tx_rate = meta->rate =
			ap_update_sta_tx_rate(sta, local->dev);

	अगर (local->iw_mode != IW_MODE_MASTER)
		जाओ out;

	अगर (!(sta->flags & WLAN_STA_PS))
		जाओ out;

	अगर (meta->flags & HOSTAP_TX_FLAGS_ADD_MOREDATA) अणु
		/* indicate to STA that more frames follow */
		hdr->frame_control |=
			cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	पूर्ण

	अगर (meta->flags & HOSTAP_TX_FLAGS_BUFFERED_FRAME) अणु
		/* packet was alपढ़ोy buffered and now send due to
		 * PS poll, so करो not rebuffer it */
		जाओ out;
	पूर्ण

	अगर (skb_queue_len(&sta->tx_buf) >= STA_MAX_TX_BUFFER) अणु
		PDEBUG(DEBUG_PS, "%s: No more space in STA (%pM)'s"
		       "PS mode buffer\n",
		       local->dev->name, sta->addr);
		/* Make sure that TIM is set क्रम the station (it might not be
		 * after AP wlan hw reset). */
		/* FIX: should fix hw reset to restore bits based on STA
		 * buffer state.. */
		hostap_set_tim(local, sta->aid, 1);
		sta->flags |= WLAN_STA_TIM;
		ret = AP_TX_DROP;
		जाओ out;
	पूर्ण

	/* STA in PS mode, buffer frame क्रम later delivery */
	set_tim = skb_queue_empty(&sta->tx_buf);
	skb_queue_tail(&sta->tx_buf, skb);
	/* FIX: could save RX समय to skb and expire buffered frames after
	 * some समय अगर STA करोes not poll क्रम them */

	अगर (set_tim) अणु
		अगर (sta->flags & WLAN_STA_TIM)
			PDEBUG(DEBUG_PS2, "Re-setting TIM for aid %d\n",
			       sta->aid);
		hostap_set_tim(local, sta->aid, 1);
		sta->flags |= WLAN_STA_TIM;
	पूर्ण

	ret = AP_TX_BUFFERED;

 out:
	अगर (sta != शून्य) अणु
		अगर (ret == AP_TX_CONTINUE ||
		    ret == AP_TX_CONTINUE_NOT_AUTHORIZED) अणु
			sta->tx_packets++;
			sta->tx_bytes += skb->len;
			sta->last_tx = jअगरfies;
		पूर्ण

		अगर ((ret == AP_TX_CONTINUE ||
		     ret == AP_TX_CONTINUE_NOT_AUTHORIZED) &&
		    sta->crypt && tx->host_encrypt) अणु
			tx->crypt = sta->crypt;
			tx->sta_ptr = sta; /* hostap_handle_sta_release() will
					    * be called to release sta info
					    * later */
		पूर्ण अन्यथा
			atomic_dec(&sta->users);
	पूर्ण

	वापस ret;
पूर्ण


व्योम hostap_handle_sta_release(व्योम *ptr)
अणु
	काष्ठा sta_info *sta = ptr;
	atomic_dec(&sta->users);
पूर्ण


/* Called only as a tasklet (software IRQ) */
व्योम hostap_handle_sta_tx_exc(local_info_t *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा hostap_skb_tx_data *meta;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;

	spin_lock(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr1);
	अगर (!sta) अणु
		spin_unlock(&local->ap->sta_table_lock);
		PDEBUG(DEBUG_AP, "%s: Could not find STA %pM"
		       " for this TX error (@%lu)\n",
		       local->dev->name, hdr->addr1, jअगरfies);
		वापस;
	पूर्ण

	sta->tx_since_last_failure = 0;
	sta->tx_consecutive_exc++;

	अगर (sta->tx_consecutive_exc >= WLAN_RATE_DECREASE_THRESHOLD &&
	    sta->tx_rate_idx > 0 && meta->rate <= sta->tx_rate) अणु
		/* use next lower rate */
		पूर्णांक old, rate;
		old = rate = sta->tx_rate_idx;
		जबतक (rate > 0) अणु
			rate--;
			अगर (ap_tx_rate_ok(rate, sta, local)) अणु
				sta->tx_rate_idx = rate;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (old != sta->tx_rate_idx) अणु
			चयन (sta->tx_rate_idx) अणु
			हाल 0: sta->tx_rate = 10; अवरोध;
			हाल 1: sta->tx_rate = 20; अवरोध;
			हाल 2: sta->tx_rate = 55; अवरोध;
			हाल 3: sta->tx_rate = 110; अवरोध;
			शेष: sta->tx_rate = 0; अवरोध;
			पूर्ण
			PDEBUG(DEBUG_AP,
			       "%s: STA %pM TX rate lowered to %d\n",
			       local->dev->name, sta->addr, sta->tx_rate);
		पूर्ण
		sta->tx_consecutive_exc = 0;
	पूर्ण
	spin_unlock(&local->ap->sta_table_lock);
पूर्ण


अटल व्योम hostap_update_sta_ps2(local_info_t *local, काष्ठा sta_info *sta,
				  पूर्णांक pwrmgt, पूर्णांक type, पूर्णांक stype)
अणु
	अगर (pwrmgt && !(sta->flags & WLAN_STA_PS)) अणु
		sta->flags |= WLAN_STA_PS;
		PDEBUG(DEBUG_PS2, "STA %pM changed to use PS "
		       "mode (type=0x%02X, stype=0x%02X)\n",
		       sta->addr, type >> 2, stype >> 4);
	पूर्ण अन्यथा अगर (!pwrmgt && (sta->flags & WLAN_STA_PS)) अणु
		sta->flags &= ~WLAN_STA_PS;
		PDEBUG(DEBUG_PS2, "STA %pM changed to not use "
		       "PS mode (type=0x%02X, stype=0x%02X)\n",
		       sta->addr, type >> 2, stype >> 4);
		अगर (type != IEEE80211_FTYPE_CTL ||
		    stype != IEEE80211_STYPE_PSPOLL)
			schedule_packet_send(local, sta);
	पूर्ण
पूर्ण


/* Called only as a tasklet (software IRQ). Called क्रम each RX frame to update
 * STA घातer saving state. pwrmgt is a flag from 802.11 frame_control field. */
पूर्णांक hostap_update_sta_ps(local_info_t *local, काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा sta_info *sta;
	u16 fc;

	spin_lock(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock(&local->ap->sta_table_lock);

	अगर (!sta)
		वापस -1;

	fc = le16_to_cpu(hdr->frame_control);
	hostap_update_sta_ps2(local, sta, fc & IEEE80211_FCTL_PM,
			      fc & IEEE80211_FCTL_FTYPE,
			      fc & IEEE80211_FCTL_STYPE);

	atomic_dec(&sta->users);
	वापस 0;
पूर्ण


/* Called only as a tasklet (software IRQ). Called क्रम each RX frame after
 * getting RX header and payload from hardware. */
ap_rx_ret hostap_handle_sta_rx(local_info_t *local, काष्ठा net_device *dev,
			       काष्ठा sk_buff *skb,
			       काष्ठा hostap_80211_rx_status *rx_stats,
			       पूर्णांक wds)
अणु
	पूर्णांक ret;
	काष्ठा sta_info *sta;
	u16 fc, type, stype;
	काष्ठा ieee80211_hdr *hdr;

	अगर (local->ap == शून्य)
		वापस AP_RX_CONTINUE;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	fc = le16_to_cpu(hdr->frame_control);
	type = fc & IEEE80211_FCTL_FTYPE;
	stype = fc & IEEE80211_FCTL_STYPE;

	spin_lock(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock(&local->ap->sta_table_lock);

	अगर (sta && !(sta->flags & WLAN_STA_AUTHORIZED))
		ret = AP_RX_CONTINUE_NOT_AUTHORIZED;
	अन्यथा
		ret = AP_RX_CONTINUE;


	अगर (fc & IEEE80211_FCTL_TODS) अणु
		अगर (!wds && (sta == शून्य || !(sta->flags & WLAN_STA_ASSOC))) अणु
			अगर (local->hostapd) अणु
				prism2_rx_80211(local->apdev, skb, rx_stats,
						PRISM2_RX_NON_ASSOC);
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_DEBUG "%s: dropped received packet"
				       " from non-associated STA %pM"
				       " (type=0x%02x, subtype=0x%02x)\n",
				       dev->name, hdr->addr2,
				       type >> 2, stype >> 4);
				hostap_rx(dev, skb, rx_stats);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */
			पूर्ण
			ret = AP_RX_EXIT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (fc & IEEE80211_FCTL_FROMDS) अणु
		अगर (!wds) अणु
			/* FromDS frame - not क्रम us; probably
			 * broadcast/multicast in another BSS - drop */
			अगर (ether_addr_equal(hdr->addr1, dev->dev_addr)) अणु
				prपूर्णांकk(KERN_DEBUG "Odd.. FromDS packet "
				       "received with own BSSID\n");
				hostap_dump_rx_80211(dev->name, skb, rx_stats);
			पूर्ण
			ret = AP_RX_DROP;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (stype == IEEE80211_STYPE_शून्यFUNC && sta == शून्य &&
		   ether_addr_equal(hdr->addr1, dev->dev_addr)) अणु

		अगर (local->hostapd) अणु
			prism2_rx_80211(local->apdev, skb, rx_stats,
					PRISM2_RX_NON_ASSOC);
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
		पूर्ण अन्यथा अणु
			/* At least Lucent f/w seems to send data::nullfunc
			 * frames with no ToDS flag when the current AP वापसs
			 * after being unavailable क्रम some समय. Speed up
			 * re-association by inक्रमming the station about it not
			 * being associated. */
			prपूर्णांकk(KERN_DEBUG "%s: rejected received nullfunc frame"
			       " without ToDS from not associated STA %pM\n",
			       dev->name, hdr->addr2);
			hostap_rx(dev, skb, rx_stats);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */
		पूर्ण
		ret = AP_RX_EXIT;
		जाओ out;
	पूर्ण अन्यथा अगर (stype == IEEE80211_STYPE_शून्यFUNC) अणु
		/* At least Lucent cards seem to send periodic nullfunc
		 * frames with ToDS. Let these through to update SQ
		 * stats and PS state. Nullfunc frames करो not contain
		 * any data and they will be dropped below. */
	पूर्ण अन्यथा अणु
		/* If BSSID (Addr3) is क्रमeign, this frame is a normal
		 * broadcast frame from an IBSS network. Drop it silently.
		 * If BSSID is own, report the dropping of this frame. */
		अगर (ether_addr_equal(hdr->addr3, dev->dev_addr)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: dropped received packet from %pM"
			       " with no ToDS flag "
			       "(type=0x%02x, subtype=0x%02x)\n", dev->name,
			       hdr->addr2, type >> 2, stype >> 4);
			hostap_dump_rx_80211(dev->name, skb, rx_stats);
		पूर्ण
		ret = AP_RX_DROP;
		जाओ out;
	पूर्ण

	अगर (sta) अणु
		hostap_update_sta_ps2(local, sta, fc & IEEE80211_FCTL_PM,
				      type, stype);

		sta->rx_packets++;
		sta->rx_bytes += skb->len;
		sta->last_rx = jअगरfies;
	पूर्ण

	अगर (local->ap->nullfunc_ack && stype == IEEE80211_STYPE_शून्यFUNC &&
	    fc & IEEE80211_FCTL_TODS) अणु
		अगर (local->hostapd) अणु
			prism2_rx_80211(local->apdev, skb, rx_stats,
					PRISM2_RX_शून्यFUNC_ACK);
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
		पूर्ण अन्यथा अणु
			/* some STA f/w's seem to require control::ACK frame
			 * क्रम data::nullfunc, but Prism2 f/w 0.8.0 (at least
			 * from Compaq) करोes not send this.. Try to generate
			 * ACK क्रम these frames from the host driver to make
			 * घातer saving work with, e.g., Lucent WaveLAN f/w */
			hostap_rx(dev, skb, rx_stats);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */
		पूर्ण
		ret = AP_RX_EXIT;
		जाओ out;
	पूर्ण

 out:
	अगर (sta)
		atomic_dec(&sta->users);

	वापस ret;
पूर्ण


/* Called only as a tasklet (software IRQ) */
पूर्णांक hostap_handle_sta_crypto(local_info_t *local,
			     काष्ठा ieee80211_hdr *hdr,
			     काष्ठा lib80211_crypt_data **crypt,
			     व्योम **sta_ptr)
अणु
	काष्ठा sta_info *sta;

	spin_lock(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock(&local->ap->sta_table_lock);

	अगर (!sta)
		वापस -1;

	अगर (sta->crypt) अणु
		*crypt = sta->crypt;
		*sta_ptr = sta;
		/* hostap_handle_sta_release() will be called to release STA
		 * info */
	पूर्ण अन्यथा
		atomic_dec(&sta->users);

	वापस 0;
पूर्ण


/* Called only as a tasklet (software IRQ) */
पूर्णांक hostap_is_sta_assoc(काष्ठा ap_data *ap, u8 *sta_addr)
अणु
	काष्ठा sta_info *sta;
	पूर्णांक ret = 0;

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, sta_addr);
	अगर (sta != शून्य && (sta->flags & WLAN_STA_ASSOC) && !sta->ap)
		ret = 1;
	spin_unlock(&ap->sta_table_lock);

	वापस ret;
पूर्ण


/* Called only as a tasklet (software IRQ) */
पूर्णांक hostap_is_sta_authorized(काष्ठा ap_data *ap, u8 *sta_addr)
अणु
	काष्ठा sta_info *sta;
	पूर्णांक ret = 0;

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, sta_addr);
	अगर (sta != शून्य && (sta->flags & WLAN_STA_ASSOC) && !sta->ap &&
	    ((sta->flags & WLAN_STA_AUTHORIZED) ||
	     ap->local->ieee_802_1x == 0))
		ret = 1;
	spin_unlock(&ap->sta_table_lock);

	वापस ret;
पूर्ण


/* Called only as a tasklet (software IRQ) */
पूर्णांक hostap_add_sta(काष्ठा ap_data *ap, u8 *sta_addr)
अणु
	काष्ठा sta_info *sta;
	पूर्णांक ret = 1;

	अगर (!ap)
		वापस -1;

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, sta_addr);
	अगर (sta)
		ret = 0;
	spin_unlock(&ap->sta_table_lock);

	अगर (ret == 1) अणु
		sta = ap_add_sta(ap, sta_addr);
		अगर (!sta)
			वापस -1;
		sta->flags = WLAN_STA_AUTH | WLAN_STA_ASSOC;
		sta->ap = 1;
		स_रखो(sta->supported_rates, 0, माप(sta->supported_rates));
		/* No way of knowing which rates are supported since we did not
		 * get supported rates element from beacon/assoc req. Assume
		 * that remote end supports all 802.11b rates. */
		sta->supported_rates[0] = 0x82;
		sta->supported_rates[1] = 0x84;
		sta->supported_rates[2] = 0x0b;
		sta->supported_rates[3] = 0x16;
		sta->tx_supp_rates = WLAN_RATE_1M | WLAN_RATE_2M |
			WLAN_RATE_5M5 | WLAN_RATE_11M;
		sta->tx_rate = 110;
		sta->tx_max_rate = sta->tx_rate_idx = 3;
	पूर्ण

	वापस ret;
पूर्ण


/* Called only as a tasklet (software IRQ) */
पूर्णांक hostap_update_rx_stats(काष्ठा ap_data *ap,
			   काष्ठा ieee80211_hdr *hdr,
			   काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा sta_info *sta;

	अगर (!ap)
		वापस -1;

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, hdr->addr2);
	अगर (sta) अणु
		sta->last_rx_silence = rx_stats->noise;
		sta->last_rx_संकेत = rx_stats->संकेत;
		sta->last_rx_rate = rx_stats->rate;
		sta->last_rx_updated = IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;
		अगर (rx_stats->rate == 10)
			sta->rx_count[0]++;
		अन्यथा अगर (rx_stats->rate == 20)
			sta->rx_count[1]++;
		अन्यथा अगर (rx_stats->rate == 55)
			sta->rx_count[2]++;
		अन्यथा अगर (rx_stats->rate == 110)
			sta->rx_count[3]++;
	पूर्ण
	spin_unlock(&ap->sta_table_lock);

	वापस sta ? 0 : -1;
पूर्ण


व्योम hostap_update_rates(local_info_t *local)
अणु
	काष्ठा sta_info *sta;
	काष्ठा ap_data *ap = local->ap;

	अगर (!ap)
		वापस;

	spin_lock_bh(&ap->sta_table_lock);
	list_क्रम_each_entry(sta, &ap->sta_list, list) अणु
		prism2_check_tx_rates(sta);
	पूर्ण
	spin_unlock_bh(&ap->sta_table_lock);
पूर्ण


व्योम * ap_crypt_get_ptrs(काष्ठा ap_data *ap, u8 *addr, पूर्णांक permanent,
			 काष्ठा lib80211_crypt_data ***crypt)
अणु
	काष्ठा sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, addr);
	अगर (sta)
		atomic_inc(&sta->users);
	spin_unlock_bh(&ap->sta_table_lock);

	अगर (!sta && permanent)
		sta = ap_add_sta(ap, addr);

	अगर (!sta)
		वापस शून्य;

	अगर (permanent)
		sta->flags |= WLAN_STA_PERM;

	*crypt = &sta->crypt;

	वापस sta;
पूर्ण


व्योम hostap_add_wds_links(local_info_t *local)
अणु
	काष्ठा ap_data *ap = local->ap;
	काष्ठा sta_info *sta;

	spin_lock_bh(&ap->sta_table_lock);
	list_क्रम_each_entry(sta, &ap->sta_list, list) अणु
		अगर (sta->ap)
			hostap_wds_link_oper(local, sta->addr, WDS_ADD);
	पूर्ण
	spin_unlock_bh(&ap->sta_table_lock);

	schedule_work(&local->ap->wds_oper_queue);
पूर्ण


व्योम hostap_wds_link_oper(local_info_t *local, u8 *addr, wds_oper_type type)
अणु
	काष्ठा wds_oper_data *entry;

	entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस;
	स_नकल(entry->addr, addr, ETH_ALEN);
	entry->type = type;
	spin_lock_bh(&local->lock);
	entry->next = local->ap->wds_oper_entries;
	local->ap->wds_oper_entries = entry;
	spin_unlock_bh(&local->lock);

	schedule_work(&local->ap->wds_oper_queue);
पूर्ण


EXPORT_SYMBOL(hostap_init_data);
EXPORT_SYMBOL(hostap_init_ap_proc);
EXPORT_SYMBOL(hostap_मुक्त_data);
EXPORT_SYMBOL(hostap_check_sta_fw_version);
EXPORT_SYMBOL(hostap_handle_sta_tx_exc);
#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */
