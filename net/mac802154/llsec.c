<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Fraunhofer ITWM
 *
 * Written by:
 * Phoebe Buckheister <phoebe.buckheister@itwm.fraunhofer.de>
 */

#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/completion.h>
#समावेश <linux/ieee802154.h>
#समावेश <linux/rculist.h>

#समावेश <crypto/aead.h>
#समावेश <crypto/skcipher.h>

#समावेश "ieee802154_i.h"
#समावेश "llsec.h"

अटल व्योम llsec_key_put(काष्ठा mac802154_llsec_key *key);
अटल bool llsec_key_id_equal(स्थिर काष्ठा ieee802154_llsec_key_id *a,
			       स्थिर काष्ठा ieee802154_llsec_key_id *b);

अटल व्योम llsec_dev_मुक्त(काष्ठा mac802154_llsec_device *dev);

व्योम mac802154_llsec_init(काष्ठा mac802154_llsec *sec)
अणु
	स_रखो(sec, 0, माप(*sec));

	स_रखो(&sec->params.शेष_key_source, 0xFF, IEEE802154_ADDR_LEN);

	INIT_LIST_HEAD(&sec->table.security_levels);
	INIT_LIST_HEAD(&sec->table.devices);
	INIT_LIST_HEAD(&sec->table.keys);
	hash_init(sec->devices_लघु);
	hash_init(sec->devices_hw);
	rwlock_init(&sec->lock);
पूर्ण

व्योम mac802154_llsec_destroy(काष्ठा mac802154_llsec *sec)
अणु
	काष्ठा ieee802154_llsec_seclevel *sl, *sn;
	काष्ठा ieee802154_llsec_device *dev, *dn;
	काष्ठा ieee802154_llsec_key_entry *key, *kn;

	list_क्रम_each_entry_safe(sl, sn, &sec->table.security_levels, list) अणु
		काष्ठा mac802154_llsec_seclevel *msl;

		msl = container_of(sl, काष्ठा mac802154_llsec_seclevel, level);
		list_del(&sl->list);
		kमुक्त_sensitive(msl);
	पूर्ण

	list_क्रम_each_entry_safe(dev, dn, &sec->table.devices, list) अणु
		काष्ठा mac802154_llsec_device *mdev;

		mdev = container_of(dev, काष्ठा mac802154_llsec_device, dev);
		list_del(&dev->list);
		llsec_dev_मुक्त(mdev);
	पूर्ण

	list_क्रम_each_entry_safe(key, kn, &sec->table.keys, list) अणु
		काष्ठा mac802154_llsec_key *mkey;

		mkey = container_of(key->key, काष्ठा mac802154_llsec_key, key);
		list_del(&key->list);
		llsec_key_put(mkey);
		kमुक्त_sensitive(key);
	पूर्ण
पूर्ण

पूर्णांक mac802154_llsec_get_params(काष्ठा mac802154_llsec *sec,
			       काष्ठा ieee802154_llsec_params *params)
अणु
	पढ़ो_lock_bh(&sec->lock);
	*params = sec->params;
	पढ़ो_unlock_bh(&sec->lock);

	वापस 0;
पूर्ण

पूर्णांक mac802154_llsec_set_params(काष्ठा mac802154_llsec *sec,
			       स्थिर काष्ठा ieee802154_llsec_params *params,
			       पूर्णांक changed)
अणु
	ग_लिखो_lock_bh(&sec->lock);

	अगर (changed & IEEE802154_LLSEC_PARAM_ENABLED)
		sec->params.enabled = params->enabled;
	अगर (changed & IEEE802154_LLSEC_PARAM_FRAME_COUNTER)
		sec->params.frame_counter = params->frame_counter;
	अगर (changed & IEEE802154_LLSEC_PARAM_OUT_LEVEL)
		sec->params.out_level = params->out_level;
	अगर (changed & IEEE802154_LLSEC_PARAM_OUT_KEY)
		sec->params.out_key = params->out_key;
	अगर (changed & IEEE802154_LLSEC_PARAM_KEY_SOURCE)
		sec->params.शेष_key_source = params->शेष_key_source;
	अगर (changed & IEEE802154_LLSEC_PARAM_PAN_ID)
		sec->params.pan_id = params->pan_id;
	अगर (changed & IEEE802154_LLSEC_PARAM_HWADDR)
		sec->params.hwaddr = params->hwaddr;
	अगर (changed & IEEE802154_LLSEC_PARAM_COORD_HWADDR)
		sec->params.coord_hwaddr = params->coord_hwaddr;
	अगर (changed & IEEE802154_LLSEC_PARAM_COORD_SHORTADDR)
		sec->params.coord_लघुaddr = params->coord_लघुaddr;

	ग_लिखो_unlock_bh(&sec->lock);

	वापस 0;
पूर्ण

अटल काष्ठा mac802154_llsec_key*
llsec_key_alloc(स्थिर काष्ठा ieee802154_llsec_key *ढाँचा)
अणु
	स्थिर पूर्णांक authsizes[3] = अणु 4, 8, 16 पूर्ण;
	काष्ठा mac802154_llsec_key *key;
	पूर्णांक i;

	key = kzalloc(माप(*key), GFP_KERNEL);
	अगर (!key)
		वापस शून्य;

	kref_init(&key->ref);
	key->key = *ढाँचा;

	BUILD_BUG_ON(ARRAY_SIZE(authsizes) != ARRAY_SIZE(key->tfm));

	क्रम (i = 0; i < ARRAY_SIZE(key->tfm); i++) अणु
		key->tfm[i] = crypto_alloc_aead("ccm(aes)", 0,
						CRYPTO_ALG_ASYNC);
		अगर (IS_ERR(key->tfm[i]))
			जाओ err_tfm;
		अगर (crypto_aead_setkey(key->tfm[i], ढाँचा->key,
				       IEEE802154_LLSEC_KEY_SIZE))
			जाओ err_tfm;
		अगर (crypto_aead_setauthsize(key->tfm[i], authsizes[i]))
			जाओ err_tfm;
	पूर्ण

	key->tfm0 = crypto_alloc_sync_skcipher("ctr(aes)", 0, 0);
	अगर (IS_ERR(key->tfm0))
		जाओ err_tfm;

	अगर (crypto_sync_skcipher_setkey(key->tfm0, ढाँचा->key,
				   IEEE802154_LLSEC_KEY_SIZE))
		जाओ err_tfm0;

	वापस key;

err_tfm0:
	crypto_मुक्त_sync_skcipher(key->tfm0);
err_tfm:
	क्रम (i = 0; i < ARRAY_SIZE(key->tfm); i++)
		अगर (!IS_ERR_OR_शून्य(key->tfm[i]))
			crypto_मुक्त_aead(key->tfm[i]);

	kमुक्त_sensitive(key);
	वापस शून्य;
पूर्ण

अटल व्योम llsec_key_release(काष्ठा kref *ref)
अणु
	काष्ठा mac802154_llsec_key *key;
	पूर्णांक i;

	key = container_of(ref, काष्ठा mac802154_llsec_key, ref);

	क्रम (i = 0; i < ARRAY_SIZE(key->tfm); i++)
		crypto_मुक्त_aead(key->tfm[i]);

	crypto_मुक्त_sync_skcipher(key->tfm0);
	kमुक्त_sensitive(key);
पूर्ण

अटल काष्ठा mac802154_llsec_key*
llsec_key_get(काष्ठा mac802154_llsec_key *key)
अणु
	kref_get(&key->ref);
	वापस key;
पूर्ण

अटल व्योम llsec_key_put(काष्ठा mac802154_llsec_key *key)
अणु
	kref_put(&key->ref, llsec_key_release);
पूर्ण

अटल bool llsec_key_id_equal(स्थिर काष्ठा ieee802154_llsec_key_id *a,
			       स्थिर काष्ठा ieee802154_llsec_key_id *b)
अणु
	अगर (a->mode != b->mode)
		वापस false;

	अगर (a->mode == IEEE802154_SCF_KEY_IMPLICIT)
		वापस ieee802154_addr_equal(&a->device_addr, &b->device_addr);

	अगर (a->id != b->id)
		वापस false;

	चयन (a->mode) अणु
	हाल IEEE802154_SCF_KEY_INDEX:
		वापस true;
	हाल IEEE802154_SCF_KEY_SHORT_INDEX:
		वापस a->लघु_source == b->लघु_source;
	हाल IEEE802154_SCF_KEY_HW_INDEX:
		वापस a->extended_source == b->extended_source;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक mac802154_llsec_key_add(काष्ठा mac802154_llsec *sec,
			    स्थिर काष्ठा ieee802154_llsec_key_id *id,
			    स्थिर काष्ठा ieee802154_llsec_key *key)
अणु
	काष्ठा mac802154_llsec_key *mkey = शून्य;
	काष्ठा ieee802154_llsec_key_entry *pos, *new;

	अगर (!(key->frame_types & (1 << IEEE802154_FC_TYPE_MAC_CMD)) &&
	    key->cmd_frame_ids)
		वापस -EINVAL;

	list_क्रम_each_entry(pos, &sec->table.keys, list) अणु
		अगर (llsec_key_id_equal(&pos->id, id))
			वापस -EEXIST;

		अगर (स_भेद(pos->key->key, key->key,
			   IEEE802154_LLSEC_KEY_SIZE))
			जारी;

		mkey = container_of(pos->key, काष्ठा mac802154_llsec_key, key);

		/* Don't allow multiple instances of the same AES key to have
		 * dअगरferent allowed frame types/command frame ids, as this is
		 * not possible in the 802.15.4 PIB.
		 */
		अगर (pos->key->frame_types != key->frame_types ||
		    pos->key->cmd_frame_ids != key->cmd_frame_ids)
			वापस -EEXIST;

		अवरोध;
	पूर्ण

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	अगर (!mkey)
		mkey = llsec_key_alloc(key);
	अन्यथा
		mkey = llsec_key_get(mkey);

	अगर (!mkey)
		जाओ fail;

	new->id = *id;
	new->key = &mkey->key;

	list_add_rcu(&new->list, &sec->table.keys);

	वापस 0;

fail:
	kमुक्त_sensitive(new);
	वापस -ENOMEM;
पूर्ण

पूर्णांक mac802154_llsec_key_del(काष्ठा mac802154_llsec *sec,
			    स्थिर काष्ठा ieee802154_llsec_key_id *key)
अणु
	काष्ठा ieee802154_llsec_key_entry *pos;

	list_क्रम_each_entry(pos, &sec->table.keys, list) अणु
		काष्ठा mac802154_llsec_key *mkey;

		mkey = container_of(pos->key, काष्ठा mac802154_llsec_key, key);

		अगर (llsec_key_id_equal(&pos->id, key)) अणु
			list_del_rcu(&pos->list);
			llsec_key_put(mkey);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल bool llsec_dev_use_लघुaddr(__le16 लघु_addr)
अणु
	वापस लघु_addr != cpu_to_le16(IEEE802154_ADDR_UNDEF) &&
		लघु_addr != cpu_to_le16(0xffff);
पूर्ण

अटल u32 llsec_dev_hash_लघु(__le16 लघु_addr, __le16 pan_id)
अणु
	वापस ((__क्रमce u16)लघु_addr) << 16 | (__क्रमce u16)pan_id;
पूर्ण

अटल u64 llsec_dev_hash_दीर्घ(__le64 hwaddr)
अणु
	वापस (__क्रमce u64)hwaddr;
पूर्ण

अटल काष्ठा mac802154_llsec_device*
llsec_dev_find_लघु(काष्ठा mac802154_llsec *sec, __le16 लघु_addr,
		     __le16 pan_id)
अणु
	काष्ठा mac802154_llsec_device *dev;
	u32 key = llsec_dev_hash_लघु(लघु_addr, pan_id);

	hash_क्रम_each_possible_rcu(sec->devices_लघु, dev, bucket_s, key) अणु
		अगर (dev->dev.लघु_addr == लघु_addr &&
		    dev->dev.pan_id == pan_id)
			वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mac802154_llsec_device*
llsec_dev_find_दीर्घ(काष्ठा mac802154_llsec *sec, __le64 hwaddr)
अणु
	काष्ठा mac802154_llsec_device *dev;
	u64 key = llsec_dev_hash_दीर्घ(hwaddr);

	hash_क्रम_each_possible_rcu(sec->devices_hw, dev, bucket_hw, key) अणु
		अगर (dev->dev.hwaddr == hwaddr)
			वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम llsec_dev_मुक्त(काष्ठा mac802154_llsec_device *dev)
अणु
	काष्ठा ieee802154_llsec_device_key *pos, *pn;
	काष्ठा mac802154_llsec_device_key *devkey;

	list_क्रम_each_entry_safe(pos, pn, &dev->dev.keys, list) अणु
		devkey = container_of(pos, काष्ठा mac802154_llsec_device_key,
				      devkey);

		list_del(&pos->list);
		kमुक्त_sensitive(devkey);
	पूर्ण

	kमुक्त_sensitive(dev);
पूर्ण

पूर्णांक mac802154_llsec_dev_add(काष्ठा mac802154_llsec *sec,
			    स्थिर काष्ठा ieee802154_llsec_device *dev)
अणु
	काष्ठा mac802154_llsec_device *entry;
	u32 skey = llsec_dev_hash_लघु(dev->लघु_addr, dev->pan_id);
	u64 hwkey = llsec_dev_hash_दीर्घ(dev->hwaddr);

	BUILD_BUG_ON(माप(hwkey) != IEEE802154_ADDR_LEN);

	अगर ((llsec_dev_use_लघुaddr(dev->लघु_addr) &&
	     llsec_dev_find_लघु(sec, dev->लघु_addr, dev->pan_id)) ||
	     llsec_dev_find_दीर्घ(sec, dev->hwaddr))
		वापस -EEXIST;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->dev = *dev;
	spin_lock_init(&entry->lock);
	INIT_LIST_HEAD(&entry->dev.keys);

	अगर (llsec_dev_use_लघुaddr(dev->लघु_addr))
		hash_add_rcu(sec->devices_लघु, &entry->bucket_s, skey);
	अन्यथा
		INIT_HLIST_NODE(&entry->bucket_s);

	hash_add_rcu(sec->devices_hw, &entry->bucket_hw, hwkey);
	list_add_tail_rcu(&entry->dev.list, &sec->table.devices);

	वापस 0;
पूर्ण

अटल व्योम llsec_dev_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	llsec_dev_मुक्त(container_of(rcu, काष्ठा mac802154_llsec_device, rcu));
पूर्ण

पूर्णांक mac802154_llsec_dev_del(काष्ठा mac802154_llsec *sec, __le64 device_addr)
अणु
	काष्ठा mac802154_llsec_device *pos;

	pos = llsec_dev_find_दीर्घ(sec, device_addr);
	अगर (!pos)
		वापस -ENOENT;

	hash_del_rcu(&pos->bucket_s);
	hash_del_rcu(&pos->bucket_hw);
	list_del_rcu(&pos->dev.list);
	call_rcu(&pos->rcu, llsec_dev_मुक्त_rcu);

	वापस 0;
पूर्ण

अटल काष्ठा mac802154_llsec_device_key*
llsec_devkey_find(काष्ठा mac802154_llsec_device *dev,
		  स्थिर काष्ठा ieee802154_llsec_key_id *key)
अणु
	काष्ठा ieee802154_llsec_device_key *devkey;

	list_क्रम_each_entry_rcu(devkey, &dev->dev.keys, list) अणु
		अगर (!llsec_key_id_equal(key, &devkey->key_id))
			जारी;

		वापस container_of(devkey, काष्ठा mac802154_llsec_device_key,
				    devkey);
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक mac802154_llsec_devkey_add(काष्ठा mac802154_llsec *sec,
			       __le64 dev_addr,
			       स्थिर काष्ठा ieee802154_llsec_device_key *key)
अणु
	काष्ठा mac802154_llsec_device *dev;
	काष्ठा mac802154_llsec_device_key *devkey;

	dev = llsec_dev_find_दीर्घ(sec, dev_addr);

	अगर (!dev)
		वापस -ENOENT;

	अगर (llsec_devkey_find(dev, &key->key_id))
		वापस -EEXIST;

	devkey = kदो_स्मृति(माप(*devkey), GFP_KERNEL);
	अगर (!devkey)
		वापस -ENOMEM;

	devkey->devkey = *key;
	list_add_tail_rcu(&devkey->devkey.list, &dev->dev.keys);
	वापस 0;
पूर्ण

पूर्णांक mac802154_llsec_devkey_del(काष्ठा mac802154_llsec *sec,
			       __le64 dev_addr,
			       स्थिर काष्ठा ieee802154_llsec_device_key *key)
अणु
	काष्ठा mac802154_llsec_device *dev;
	काष्ठा mac802154_llsec_device_key *devkey;

	dev = llsec_dev_find_दीर्घ(sec, dev_addr);

	अगर (!dev)
		वापस -ENOENT;

	devkey = llsec_devkey_find(dev, &key->key_id);
	अगर (!devkey)
		वापस -ENOENT;

	list_del_rcu(&devkey->devkey.list);
	kमुक्त_rcu(devkey, rcu);
	वापस 0;
पूर्ण

अटल काष्ठा mac802154_llsec_seclevel*
llsec_find_seclevel(स्थिर काष्ठा mac802154_llsec *sec,
		    स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	काष्ठा ieee802154_llsec_seclevel *pos;

	list_क्रम_each_entry(pos, &sec->table.security_levels, list) अणु
		अगर (pos->frame_type != sl->frame_type ||
		    (pos->frame_type == IEEE802154_FC_TYPE_MAC_CMD &&
		     pos->cmd_frame_id != sl->cmd_frame_id) ||
		    pos->device_override != sl->device_override ||
		    pos->sec_levels != sl->sec_levels)
			जारी;

		वापस container_of(pos, काष्ठा mac802154_llsec_seclevel,
				    level);
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक mac802154_llsec_seclevel_add(काष्ठा mac802154_llsec *sec,
				 स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	काष्ठा mac802154_llsec_seclevel *entry;

	अगर (llsec_find_seclevel(sec, sl))
		वापस -EEXIST;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->level = *sl;

	list_add_tail_rcu(&entry->level.list, &sec->table.security_levels);

	वापस 0;
पूर्ण

पूर्णांक mac802154_llsec_seclevel_del(काष्ठा mac802154_llsec *sec,
				 स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	काष्ठा mac802154_llsec_seclevel *pos;

	pos = llsec_find_seclevel(sec, sl);
	अगर (!pos)
		वापस -ENOENT;

	list_del_rcu(&pos->level.list);
	kमुक्त_rcu(pos, rcu);

	वापस 0;
पूर्ण

अटल पूर्णांक llsec_recover_addr(काष्ठा mac802154_llsec *sec,
			      काष्ठा ieee802154_addr *addr)
अणु
	__le16 caddr = sec->params.coord_लघुaddr;

	addr->pan_id = sec->params.pan_id;

	अगर (caddr == cpu_to_le16(IEEE802154_ADDR_BROADCAST)) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (caddr == cpu_to_le16(IEEE802154_ADDR_UNDEF)) अणु
		addr->extended_addr = sec->params.coord_hwaddr;
		addr->mode = IEEE802154_ADDR_LONG;
	पूर्ण अन्यथा अणु
		addr->लघु_addr = sec->params.coord_लघुaddr;
		addr->mode = IEEE802154_ADDR_SHORT;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mac802154_llsec_key*
llsec_lookup_key(काष्ठा mac802154_llsec *sec,
		 स्थिर काष्ठा ieee802154_hdr *hdr,
		 स्थिर काष्ठा ieee802154_addr *addr,
		 काष्ठा ieee802154_llsec_key_id *key_id)
अणु
	काष्ठा ieee802154_addr devaddr = *addr;
	u8 key_id_mode = hdr->sec.key_id_mode;
	काष्ठा ieee802154_llsec_key_entry *key_entry;
	काष्ठा mac802154_llsec_key *key;

	अगर (key_id_mode == IEEE802154_SCF_KEY_IMPLICIT &&
	    devaddr.mode == IEEE802154_ADDR_NONE) अणु
		अगर (hdr->fc.type == IEEE802154_FC_TYPE_BEACON) अणु
			devaddr.extended_addr = sec->params.coord_hwaddr;
			devaddr.mode = IEEE802154_ADDR_LONG;
		पूर्ण अन्यथा अगर (llsec_recover_addr(sec, &devaddr) < 0) अणु
			वापस शून्य;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_rcu(key_entry, &sec->table.keys, list) अणु
		स्थिर काष्ठा ieee802154_llsec_key_id *id = &key_entry->id;

		अगर (!(key_entry->key->frame_types & BIT(hdr->fc.type)))
			जारी;

		अगर (id->mode != key_id_mode)
			जारी;

		अगर (key_id_mode == IEEE802154_SCF_KEY_IMPLICIT) अणु
			अगर (ieee802154_addr_equal(&devaddr, &id->device_addr))
				जाओ found;
		पूर्ण अन्यथा अणु
			अगर (id->id != hdr->sec.key_id)
				जारी;

			अगर ((key_id_mode == IEEE802154_SCF_KEY_INDEX) ||
			    (key_id_mode == IEEE802154_SCF_KEY_SHORT_INDEX &&
			     id->लघु_source == hdr->sec.लघु_src) ||
			    (key_id_mode == IEEE802154_SCF_KEY_HW_INDEX &&
			     id->extended_source == hdr->sec.extended_src))
				जाओ found;
		पूर्ण
	पूर्ण

	वापस शून्य;

found:
	key = container_of(key_entry->key, काष्ठा mac802154_llsec_key, key);
	अगर (key_id)
		*key_id = key_entry->id;
	वापस llsec_key_get(key);
पूर्ण

अटल व्योम llsec_geniv(u8 iv[16], __le64 addr,
			स्थिर काष्ठा ieee802154_sechdr *sec)
अणु
	__be64 addr_bytes = (__क्रमce __be64) swab64((__क्रमce u64) addr);
	__be32 frame_counter = (__क्रमce __be32) swab32((__क्रमce u32) sec->frame_counter);

	iv[0] = 1; /* L' = L - 1 = 1 */
	स_नकल(iv + 1, &addr_bytes, माप(addr_bytes));
	स_नकल(iv + 9, &frame_counter, माप(frame_counter));
	iv[13] = sec->level;
	iv[14] = 0;
	iv[15] = 1;
पूर्ण

अटल पूर्णांक
llsec_करो_encrypt_unauth(काष्ठा sk_buff *skb, स्थिर काष्ठा mac802154_llsec *sec,
			स्थिर काष्ठा ieee802154_hdr *hdr,
			काष्ठा mac802154_llsec_key *key)
अणु
	u8 iv[16];
	काष्ठा scatterlist src;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, key->tfm0);
	पूर्णांक err, datalen;
	अचिन्हित अक्षर *data;

	llsec_geniv(iv, sec->params.hwaddr, &hdr->sec);
	/* Compute data payload offset and data length */
	data = skb_mac_header(skb) + skb->mac_len;
	datalen = skb_tail_poपूर्णांकer(skb) - data;
	sg_init_one(&src, data, datalen);

	skcipher_request_set_sync_tfm(req, key->tfm0);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, &src, &src, datalen, iv);
	err = crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);
	वापस err;
पूर्ण

अटल काष्ठा crypto_aead*
llsec_tfm_by_len(काष्ठा mac802154_llsec_key *key, पूर्णांक authlen)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(key->tfm); i++)
		अगर (crypto_aead_authsize(key->tfm[i]) == authlen)
			वापस key->tfm[i];

	BUG();
पूर्ण

अटल पूर्णांक
llsec_करो_encrypt_auth(काष्ठा sk_buff *skb, स्थिर काष्ठा mac802154_llsec *sec,
		      स्थिर काष्ठा ieee802154_hdr *hdr,
		      काष्ठा mac802154_llsec_key *key)
अणु
	u8 iv[16];
	अचिन्हित अक्षर *data;
	पूर्णांक authlen, assoclen, datalen, rc;
	काष्ठा scatterlist sg;
	काष्ठा aead_request *req;

	authlen = ieee802154_sechdr_authtag_len(&hdr->sec);
	llsec_geniv(iv, sec->params.hwaddr, &hdr->sec);

	req = aead_request_alloc(llsec_tfm_by_len(key, authlen), GFP_ATOMIC);
	अगर (!req)
		वापस -ENOMEM;

	assoclen = skb->mac_len;

	data = skb_mac_header(skb) + skb->mac_len;
	datalen = skb_tail_poपूर्णांकer(skb) - data;

	skb_put(skb, authlen);

	sg_init_one(&sg, skb_mac_header(skb), assoclen + datalen + authlen);

	अगर (!(hdr->sec.level & IEEE802154_SCF_SECLEVEL_ENC)) अणु
		assoclen += datalen;
		datalen = 0;
	पूर्ण

	aead_request_set_callback(req, 0, शून्य, शून्य);
	aead_request_set_crypt(req, &sg, &sg, datalen, iv);
	aead_request_set_ad(req, assoclen);

	rc = crypto_aead_encrypt(req);

	kमुक्त_sensitive(req);

	वापस rc;
पूर्ण

अटल पूर्णांक llsec_करो_encrypt(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा mac802154_llsec *sec,
			    स्थिर काष्ठा ieee802154_hdr *hdr,
			    काष्ठा mac802154_llsec_key *key)
अणु
	अगर (hdr->sec.level == IEEE802154_SCF_SECLEVEL_ENC)
		वापस llsec_करो_encrypt_unauth(skb, sec, hdr, key);
	अन्यथा
		वापस llsec_करो_encrypt_auth(skb, sec, hdr, key);
पूर्ण

पूर्णांक mac802154_llsec_encrypt(काष्ठा mac802154_llsec *sec, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee802154_hdr hdr;
	पूर्णांक rc, authlen, hlen;
	काष्ठा mac802154_llsec_key *key;
	u32 frame_ctr;

	hlen = ieee802154_hdr_pull(skb, &hdr);

	अगर (hlen < 0 || hdr.fc.type != IEEE802154_FC_TYPE_DATA)
		वापस -EINVAL;

	अगर (!hdr.fc.security_enabled ||
	    (hdr.sec.level == IEEE802154_SCF_SECLEVEL_NONE)) अणु
		skb_push(skb, hlen);
		वापस 0;
	पूर्ण

	authlen = ieee802154_sechdr_authtag_len(&hdr.sec);

	अगर (skb->len + hlen + authlen + IEEE802154_MFR_SIZE > IEEE802154_MTU)
		वापस -EMSGSIZE;

	rcu_पढ़ो_lock();

	पढ़ो_lock_bh(&sec->lock);

	अगर (!sec->params.enabled) अणु
		rc = -EINVAL;
		जाओ fail_पढ़ो;
	पूर्ण

	key = llsec_lookup_key(sec, &hdr, &hdr.dest, शून्य);
	अगर (!key) अणु
		rc = -ENOKEY;
		जाओ fail_पढ़ो;
	पूर्ण

	पढ़ो_unlock_bh(&sec->lock);

	ग_लिखो_lock_bh(&sec->lock);

	frame_ctr = be32_to_cpu(sec->params.frame_counter);
	hdr.sec.frame_counter = cpu_to_le32(frame_ctr);
	अगर (frame_ctr == 0xFFFFFFFF) अणु
		ग_लिखो_unlock_bh(&sec->lock);
		llsec_key_put(key);
		rc = -EOVERFLOW;
		जाओ fail;
	पूर्ण

	sec->params.frame_counter = cpu_to_be32(frame_ctr + 1);

	ग_लिखो_unlock_bh(&sec->lock);

	rcu_पढ़ो_unlock();

	skb->mac_len = ieee802154_hdr_push(skb, &hdr);
	skb_reset_mac_header(skb);

	rc = llsec_करो_encrypt(skb, sec, &hdr, key);
	llsec_key_put(key);

	वापस rc;

fail_पढ़ो:
	पढ़ो_unlock_bh(&sec->lock);
fail:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

अटल काष्ठा mac802154_llsec_device*
llsec_lookup_dev(काष्ठा mac802154_llsec *sec,
		 स्थिर काष्ठा ieee802154_addr *addr)
अणु
	काष्ठा ieee802154_addr devaddr = *addr;
	काष्ठा mac802154_llsec_device *dev = शून्य;

	अगर (devaddr.mode == IEEE802154_ADDR_NONE &&
	    llsec_recover_addr(sec, &devaddr) < 0)
		वापस शून्य;

	अगर (devaddr.mode == IEEE802154_ADDR_SHORT) अणु
		u32 key = llsec_dev_hash_लघु(devaddr.लघु_addr,
					       devaddr.pan_id);

		hash_क्रम_each_possible_rcu(sec->devices_लघु, dev,
					   bucket_s, key) अणु
			अगर (dev->dev.pan_id == devaddr.pan_id &&
			    dev->dev.लघु_addr == devaddr.लघु_addr)
				वापस dev;
		पूर्ण
	पूर्ण अन्यथा अणु
		u64 key = llsec_dev_hash_दीर्घ(devaddr.extended_addr);

		hash_क्रम_each_possible_rcu(sec->devices_hw, dev,
					   bucket_hw, key) अणु
			अगर (dev->dev.hwaddr == devaddr.extended_addr)
				वापस dev;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
llsec_lookup_seclevel(स्थिर काष्ठा mac802154_llsec *sec,
		      u8 frame_type, u8 cmd_frame_id,
		      काष्ठा ieee802154_llsec_seclevel *rlevel)
अणु
	काष्ठा ieee802154_llsec_seclevel *level;

	list_क्रम_each_entry_rcu(level, &sec->table.security_levels, list) अणु
		अगर (level->frame_type == frame_type &&
		    (frame_type != IEEE802154_FC_TYPE_MAC_CMD ||
		     level->cmd_frame_id == cmd_frame_id)) अणु
			*rlevel = *level;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
llsec_करो_decrypt_unauth(काष्ठा sk_buff *skb, स्थिर काष्ठा mac802154_llsec *sec,
			स्थिर काष्ठा ieee802154_hdr *hdr,
			काष्ठा mac802154_llsec_key *key, __le64 dev_addr)
अणु
	u8 iv[16];
	अचिन्हित अक्षर *data;
	पूर्णांक datalen;
	काष्ठा scatterlist src;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, key->tfm0);
	पूर्णांक err;

	llsec_geniv(iv, dev_addr, &hdr->sec);
	data = skb_mac_header(skb) + skb->mac_len;
	datalen = skb_tail_poपूर्णांकer(skb) - data;

	sg_init_one(&src, data, datalen);

	skcipher_request_set_sync_tfm(req, key->tfm0);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, &src, &src, datalen, iv);

	err = crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);
	वापस err;
पूर्ण

अटल पूर्णांक
llsec_करो_decrypt_auth(काष्ठा sk_buff *skb, स्थिर काष्ठा mac802154_llsec *sec,
		      स्थिर काष्ठा ieee802154_hdr *hdr,
		      काष्ठा mac802154_llsec_key *key, __le64 dev_addr)
अणु
	u8 iv[16];
	अचिन्हित अक्षर *data;
	पूर्णांक authlen, datalen, assoclen, rc;
	काष्ठा scatterlist sg;
	काष्ठा aead_request *req;

	authlen = ieee802154_sechdr_authtag_len(&hdr->sec);
	llsec_geniv(iv, dev_addr, &hdr->sec);

	req = aead_request_alloc(llsec_tfm_by_len(key, authlen), GFP_ATOMIC);
	अगर (!req)
		वापस -ENOMEM;

	assoclen = skb->mac_len;

	data = skb_mac_header(skb) + skb->mac_len;
	datalen = skb_tail_poपूर्णांकer(skb) - data;

	sg_init_one(&sg, skb_mac_header(skb), assoclen + datalen);

	अगर (!(hdr->sec.level & IEEE802154_SCF_SECLEVEL_ENC)) अणु
		assoclen += datalen - authlen;
		datalen = authlen;
	पूर्ण

	aead_request_set_callback(req, 0, शून्य, शून्य);
	aead_request_set_crypt(req, &sg, &sg, datalen, iv);
	aead_request_set_ad(req, assoclen);

	rc = crypto_aead_decrypt(req);

	kमुक्त_sensitive(req);
	skb_trim(skb, skb->len - authlen);

	वापस rc;
पूर्ण

अटल पूर्णांक
llsec_करो_decrypt(काष्ठा sk_buff *skb, स्थिर काष्ठा mac802154_llsec *sec,
		 स्थिर काष्ठा ieee802154_hdr *hdr,
		 काष्ठा mac802154_llsec_key *key, __le64 dev_addr)
अणु
	अगर (hdr->sec.level == IEEE802154_SCF_SECLEVEL_ENC)
		वापस llsec_करो_decrypt_unauth(skb, sec, hdr, key, dev_addr);
	अन्यथा
		वापस llsec_करो_decrypt_auth(skb, sec, hdr, key, dev_addr);
पूर्ण

अटल पूर्णांक
llsec_update_devkey_record(काष्ठा mac802154_llsec_device *dev,
			   स्थिर काष्ठा ieee802154_llsec_key_id *in_key)
अणु
	काष्ठा mac802154_llsec_device_key *devkey;

	devkey = llsec_devkey_find(dev, in_key);

	अगर (!devkey) अणु
		काष्ठा mac802154_llsec_device_key *next;

		next = kzalloc(माप(*devkey), GFP_ATOMIC);
		अगर (!next)
			वापस -ENOMEM;

		next->devkey.key_id = *in_key;

		spin_lock_bh(&dev->lock);

		devkey = llsec_devkey_find(dev, in_key);
		अगर (!devkey)
			list_add_rcu(&next->devkey.list, &dev->dev.keys);
		अन्यथा
			kमुक्त_sensitive(next);

		spin_unlock_bh(&dev->lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
llsec_update_devkey_info(काष्ठा mac802154_llsec_device *dev,
			 स्थिर काष्ठा ieee802154_llsec_key_id *in_key,
			 u32 frame_counter)
अणु
	काष्ठा mac802154_llsec_device_key *devkey = शून्य;

	अगर (dev->dev.key_mode == IEEE802154_LLSEC_DEVKEY_RESTRICT) अणु
		devkey = llsec_devkey_find(dev, in_key);
		अगर (!devkey)
			वापस -ENOENT;
	पूर्ण

	अगर (dev->dev.key_mode == IEEE802154_LLSEC_DEVKEY_RECORD) अणु
		पूर्णांक rc = llsec_update_devkey_record(dev, in_key);

		अगर (rc < 0)
			वापस rc;
	पूर्ण

	spin_lock_bh(&dev->lock);

	अगर ((!devkey && frame_counter < dev->dev.frame_counter) ||
	    (devkey && frame_counter < devkey->devkey.frame_counter)) अणु
		spin_unlock_bh(&dev->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (devkey)
		devkey->devkey.frame_counter = frame_counter + 1;
	अन्यथा
		dev->dev.frame_counter = frame_counter + 1;

	spin_unlock_bh(&dev->lock);

	वापस 0;
पूर्ण

पूर्णांक mac802154_llsec_decrypt(काष्ठा mac802154_llsec *sec, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee802154_hdr hdr;
	काष्ठा mac802154_llsec_key *key;
	काष्ठा ieee802154_llsec_key_id key_id;
	काष्ठा mac802154_llsec_device *dev;
	काष्ठा ieee802154_llsec_seclevel seclevel;
	पूर्णांक err;
	__le64 dev_addr;
	u32 frame_ctr;

	अगर (ieee802154_hdr_peek(skb, &hdr) < 0)
		वापस -EINVAL;
	अगर (!hdr.fc.security_enabled)
		वापस 0;
	अगर (hdr.fc.version == 0)
		वापस -EINVAL;

	पढ़ो_lock_bh(&sec->lock);
	अगर (!sec->params.enabled) अणु
		पढ़ो_unlock_bh(&sec->lock);
		वापस -EINVAL;
	पूर्ण
	पढ़ो_unlock_bh(&sec->lock);

	rcu_पढ़ो_lock();

	key = llsec_lookup_key(sec, &hdr, &hdr.source, &key_id);
	अगर (!key) अणु
		err = -ENOKEY;
		जाओ fail;
	पूर्ण

	dev = llsec_lookup_dev(sec, &hdr.source);
	अगर (!dev) अणु
		err = -EINVAL;
		जाओ fail_dev;
	पूर्ण

	अगर (llsec_lookup_seclevel(sec, hdr.fc.type, 0, &seclevel) < 0) अणु
		err = -EINVAL;
		जाओ fail_dev;
	पूर्ण

	अगर (!(seclevel.sec_levels & BIT(hdr.sec.level)) &&
	    (hdr.sec.level == 0 && seclevel.device_override &&
	     !dev->dev.seclevel_exempt)) अणु
		err = -EINVAL;
		जाओ fail_dev;
	पूर्ण

	frame_ctr = le32_to_cpu(hdr.sec.frame_counter);

	अगर (frame_ctr == 0xffffffff) अणु
		err = -EOVERFLOW;
		जाओ fail_dev;
	पूर्ण

	err = llsec_update_devkey_info(dev, &key_id, frame_ctr);
	अगर (err)
		जाओ fail_dev;

	dev_addr = dev->dev.hwaddr;

	rcu_पढ़ो_unlock();

	err = llsec_करो_decrypt(skb, sec, &hdr, key, dev_addr);
	llsec_key_put(key);
	वापस err;

fail_dev:
	llsec_key_put(key);
fail:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
