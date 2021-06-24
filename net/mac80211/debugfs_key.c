<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2003-2005	Devicescape Software, Inc.
 * Copyright (c) 2006	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2015	Intel Deutschland GmbH
 */

#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश "ieee80211_i.h"
#समावेश "key.h"
#समावेश "debugfs.h"
#समावेश "debugfs_key.h"

#घोषणा KEY_READ(name, prop, क्रमmat_string)				\
अटल sमाप_प्रकार key_##name##_पढ़ो(काष्ठा file *file,			\
				 अक्षर __user *userbuf,			\
				 माप_प्रकार count, loff_t *ppos)		\
अणु									\
	काष्ठा ieee80211_key *key = file->निजी_data;			\
	वापस mac80211_क्रमmat_buffer(userbuf, count, ppos, 		\
				      क्रमmat_string, key->prop);	\
पूर्ण
#घोषणा KEY_READ_D(name) KEY_READ(name, name, "%d\n")
#घोषणा KEY_READ_X(name) KEY_READ(name, name, "0x%x\n")

#घोषणा KEY_OPS(name)							\
अटल स्थिर काष्ठा file_operations key_ ##name## _ops = अणु		\
	.पढ़ो = key_##name##_पढ़ो,					\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण

#घोषणा KEY_OPS_W(name)							\
अटल स्थिर काष्ठा file_operations key_ ##name## _ops = अणु		\
	.पढ़ो = key_##name##_पढ़ो,					\
	.ग_लिखो = key_##name##_ग_लिखो,					\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण

#घोषणा KEY_खाता(name, क्रमmat)						\
		 KEY_READ_##क्रमmat(name)				\
		 KEY_OPS(name)

#घोषणा KEY_CONF_READ(name, क्रमmat_string)				\
	KEY_READ(conf_##name, conf.name, क्रमmat_string)
#घोषणा KEY_CONF_READ_D(name) KEY_CONF_READ(name, "%d\n")

#घोषणा KEY_CONF_OPS(name)						\
अटल स्थिर काष्ठा file_operations key_ ##name## _ops = अणु		\
	.पढ़ो = key_conf_##name##_पढ़ो,					\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण

#घोषणा KEY_CONF_खाता(name, क्रमmat)					\
		 KEY_CONF_READ_##क्रमmat(name)				\
		 KEY_CONF_OPS(name)

KEY_CONF_खाता(keylen, D);
KEY_CONF_खाता(keyidx, D);
KEY_CONF_खाता(hw_key_idx, D);
KEY_खाता(flags, X);
KEY_READ(अगरindex, sdata->name, "%s\n");
KEY_OPS(अगरindex);

अटल sमाप_प्रकार key_algorithm_पढ़ो(काष्ठा file *file,
				  अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[15];
	काष्ठा ieee80211_key *key = file->निजी_data;
	u32 c = key->conf.cipher;

	प्र_लिखो(buf, "%.2x-%.2x-%.2x:%d\n",
		c >> 24, (c >> 16) & 0xff, (c >> 8) & 0xff, c & 0xff);
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, म_माप(buf));
पूर्ण
KEY_OPS(algorithm);

अटल sमाप_प्रकार key_tx_spec_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_key *key = file->निजी_data;
	u64 pn;
	पूर्णांक ret;

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस -EINVAL;
	हाल WLAN_CIPHER_SUITE_TKIP:
		/* not supported yet */
		वापस -EOPNOTSUPP;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		ret = kstrtou64_from_user(userbuf, count, 16, &pn);
		अगर (ret)
			वापस ret;
		/* PN is a 48-bit counter */
		अगर (pn >= (1ULL << 48))
			वापस -दुस्फल;
		atomic64_set(&key->conf.tx_pn, pn);
		वापस count;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार key_tx_spec_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	u64 pn;
	अक्षर buf[20];
	पूर्णांक len;
	काष्ठा ieee80211_key *key = file->निजी_data;

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		len = scnम_लिखो(buf, माप(buf), "\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		pn = atomic64_पढ़ो(&key->conf.tx_pn);
		len = scnम_लिखो(buf, माप(buf), "%08x %04x\n",
				TKIP_PN_TO_IV32(pn),
				TKIP_PN_TO_IV16(pn));
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		pn = atomic64_पढ़ो(&key->conf.tx_pn);
		len = scnम_लिखो(buf, माप(buf), "%02x%02x%02x%02x%02x%02x\n",
				(u8)(pn >> 40), (u8)(pn >> 32), (u8)(pn >> 24),
				(u8)(pn >> 16), (u8)(pn >> 8), (u8)pn);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण
KEY_OPS_W(tx_spec);

अटल sमाप_प्रकार key_rx_spec_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_key *key = file->निजी_data;
	अक्षर buf[14*IEEE80211_NUM_TIDS+1], *p = buf;
	पूर्णांक i, len;
	स्थिर u8 *rpn;

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		len = scnम_लिखो(buf, माप(buf), "\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++)
			p += scnम_लिखो(p, माप(buf)+buf-p,
				       "%08x %04x\n",
				       key->u.tkip.rx[i].iv32,
				       key->u.tkip.rx[i].iv16);
		len = p - buf;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		क्रम (i = 0; i < IEEE80211_NUM_TIDS + 1; i++) अणु
			rpn = key->u.ccmp.rx_pn[i];
			p += scnम_लिखो(p, माप(buf)+buf-p,
				       "%02x%02x%02x%02x%02x%02x\n",
				       rpn[0], rpn[1], rpn[2],
				       rpn[3], rpn[4], rpn[5]);
		पूर्ण
		len = p - buf;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		rpn = key->u.aes_cmac.rx_pn;
		p += scnम_लिखो(p, माप(buf)+buf-p,
			       "%02x%02x%02x%02x%02x%02x\n",
			       rpn[0], rpn[1], rpn[2],
			       rpn[3], rpn[4], rpn[5]);
		len = p - buf;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		rpn = key->u.aes_gmac.rx_pn;
		p += scnम_लिखो(p, माप(buf)+buf-p,
			       "%02x%02x%02x%02x%02x%02x\n",
			       rpn[0], rpn[1], rpn[2],
			       rpn[3], rpn[4], rpn[5]);
		len = p - buf;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		क्रम (i = 0; i < IEEE80211_NUM_TIDS + 1; i++) अणु
			rpn = key->u.gcmp.rx_pn[i];
			p += scnम_लिखो(p, माप(buf)+buf-p,
				       "%02x%02x%02x%02x%02x%02x\n",
				       rpn[0], rpn[1], rpn[2],
				       rpn[3], rpn[4], rpn[5]);
		पूर्ण
		len = p - buf;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण
KEY_OPS(rx_spec);

अटल sमाप_प्रकार key_replays_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_key *key = file->निजी_data;
	अक्षर buf[20];
	पूर्णांक len;

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		len = scnम_लिखो(buf, माप(buf), "%u\n", key->u.ccmp.replays);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		len = scnम_लिखो(buf, माप(buf), "%u\n",
				key->u.aes_cmac.replays);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		len = scnम_लिखो(buf, माप(buf), "%u\n",
				key->u.aes_gmac.replays);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		len = scnम_लिखो(buf, माप(buf), "%u\n", key->u.gcmp.replays);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण
KEY_OPS(replays);

अटल sमाप_प्रकार key_icverrors_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_key *key = file->निजी_data;
	अक्षर buf[20];
	पूर्णांक len;

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		len = scnम_लिखो(buf, माप(buf), "%u\n",
				key->u.aes_cmac.icverrors);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		len = scnम_लिखो(buf, माप(buf), "%u\n",
				key->u.aes_gmac.icverrors);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण
KEY_OPS(icverrors);

अटल sमाप_प्रकार key_mic_failures_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_key *key = file->निजी_data;
	अक्षर buf[20];
	पूर्णांक len;

	अगर (key->conf.cipher != WLAN_CIPHER_SUITE_TKIP)
		वापस -EINVAL;

	len = scnम_लिखो(buf, माप(buf), "%u\n", key->u.tkip.mic_failures);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण
KEY_OPS(mic_failures);

अटल sमाप_प्रकार key_key_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_key *key = file->निजी_data;
	पूर्णांक i, bufsize = 2 * key->conf.keylen + 2;
	अक्षर *buf = kदो_स्मृति(bufsize, GFP_KERNEL);
	अक्षर *p = buf;
	sमाप_प्रकार res;

	अगर (!buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < key->conf.keylen; i++)
		p += scnम_लिखो(p, bufsize + buf - p, "%02x", key->conf.key[i]);
	p += scnम_लिखो(p, bufsize+buf-p, "\n");
	res = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
	kमुक्त(buf);
	वापस res;
पूर्ण
KEY_OPS(key);

#घोषणा DEBUGFS_ADD(name) \
	debugfs_create_file(#name, 0400, key->debugfs.dir, \
			    key, &key_##name##_ops)
#घोषणा DEBUGFS_ADD_W(name) \
	debugfs_create_file(#name, 0600, key->debugfs.dir, \
			    key, &key_##name##_ops);

व्योम ieee80211_debugfs_key_add(काष्ठा ieee80211_key *key)
अणु
	अटल पूर्णांक keycount;
	अक्षर buf[100];
	काष्ठा sta_info *sta;

	अगर (!key->local->debugfs.keys)
		वापस;

	प्र_लिखो(buf, "%d", keycount);
	key->debugfs.cnt = keycount;
	keycount++;
	key->debugfs.dir = debugfs_create_dir(buf,
					key->local->debugfs.keys);

	sta = key->sta;
	अगर (sta) अणु
		प्र_लिखो(buf, "../../netdev:%s/stations/%pM",
			sta->sdata->name, sta->sta.addr);
		key->debugfs.stalink =
			debugfs_create_symlink("station", key->debugfs.dir, buf);
	पूर्ण

	DEBUGFS_ADD(keylen);
	DEBUGFS_ADD(flags);
	DEBUGFS_ADD(keyidx);
	DEBUGFS_ADD(hw_key_idx);
	DEBUGFS_ADD(algorithm);
	DEBUGFS_ADD_W(tx_spec);
	DEBUGFS_ADD(rx_spec);
	DEBUGFS_ADD(replays);
	DEBUGFS_ADD(icverrors);
	DEBUGFS_ADD(mic_failures);
	DEBUGFS_ADD(key);
	DEBUGFS_ADD(अगरindex);
पूर्ण;

व्योम ieee80211_debugfs_key_हटाओ(काष्ठा ieee80211_key *key)
अणु
	अगर (!key)
		वापस;

	debugfs_हटाओ_recursive(key->debugfs.dir);
	key->debugfs.dir = शून्य;
पूर्ण

व्योम ieee80211_debugfs_key_update_शेष(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अक्षर buf[50];
	काष्ठा ieee80211_key *key;

	अगर (!sdata->vअगर.debugfs_dir)
		वापस;

	lockdep_निश्चित_held(&sdata->local->key_mtx);

	debugfs_हटाओ(sdata->debugfs.शेष_unicast_key);
	sdata->debugfs.शेष_unicast_key = शून्य;

	अगर (sdata->शेष_unicast_key) अणु
		key = key_mtx_dereference(sdata->local,
					  sdata->शेष_unicast_key);
		प्र_लिखो(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.शेष_unicast_key =
			debugfs_create_symlink("default_unicast_key",
					       sdata->vअगर.debugfs_dir, buf);
	पूर्ण

	debugfs_हटाओ(sdata->debugfs.शेष_multicast_key);
	sdata->debugfs.शेष_multicast_key = शून्य;

	अगर (sdata->शेष_multicast_key) अणु
		key = key_mtx_dereference(sdata->local,
					  sdata->शेष_multicast_key);
		प्र_लिखो(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.शेष_multicast_key =
			debugfs_create_symlink("default_multicast_key",
					       sdata->vअगर.debugfs_dir, buf);
	पूर्ण
पूर्ण

व्योम ieee80211_debugfs_key_add_mgmt_शेष(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अक्षर buf[50];
	काष्ठा ieee80211_key *key;

	अगर (!sdata->vअगर.debugfs_dir)
		वापस;

	key = key_mtx_dereference(sdata->local,
				  sdata->शेष_mgmt_key);
	अगर (key) अणु
		प्र_लिखो(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.शेष_mgmt_key =
			debugfs_create_symlink("default_mgmt_key",
					       sdata->vअगर.debugfs_dir, buf);
	पूर्ण अन्यथा
		ieee80211_debugfs_key_हटाओ_mgmt_शेष(sdata);
पूर्ण

व्योम ieee80211_debugfs_key_हटाओ_mgmt_शेष(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (!sdata)
		वापस;

	debugfs_हटाओ(sdata->debugfs.शेष_mgmt_key);
	sdata->debugfs.शेष_mgmt_key = शून्य;
पूर्ण

व्योम
ieee80211_debugfs_key_add_beacon_शेष(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अक्षर buf[50];
	काष्ठा ieee80211_key *key;

	अगर (!sdata->vअगर.debugfs_dir)
		वापस;

	key = key_mtx_dereference(sdata->local,
				  sdata->शेष_beacon_key);
	अगर (key) अणु
		प्र_लिखो(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.शेष_beacon_key =
			debugfs_create_symlink("default_beacon_key",
					       sdata->vअगर.debugfs_dir, buf);
	पूर्ण अन्यथा अणु
		ieee80211_debugfs_key_हटाओ_beacon_शेष(sdata);
	पूर्ण
पूर्ण

व्योम
ieee80211_debugfs_key_हटाओ_beacon_शेष(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (!sdata)
		वापस;

	debugfs_हटाओ(sdata->debugfs.शेष_beacon_key);
	sdata->debugfs.शेष_beacon_key = शून्य;
पूर्ण

व्योम ieee80211_debugfs_key_sta_del(काष्ठा ieee80211_key *key,
				   काष्ठा sta_info *sta)
अणु
	debugfs_हटाओ(key->debugfs.stalink);
	key->debugfs.stalink = शून्य;
पूर्ण
