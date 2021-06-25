<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Fraunhofer ITWM
 *
 * Written by:
 * Phoebe Buckheister <phoebe.buckheister@itwm.fraunhofer.de>
 */

#अगर_अघोषित MAC802154_LLSEC_H
#घोषणा MAC802154_LLSEC_H

#समावेश <linux/slab.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/kref.h>
#समावेश <linux/spinlock.h>
#समावेश <net/af_ieee802154.h>
#समावेश <net/ieee802154_netdev.h>

काष्ठा mac802154_llsec_key अणु
	काष्ठा ieee802154_llsec_key key;

	/* one tfm क्रम each authsize (4/8/16) */
	काष्ठा crypto_aead *tfm[3];
	काष्ठा crypto_sync_skcipher *tfm0;

	काष्ठा kref ref;
पूर्ण;

काष्ठा mac802154_llsec_device_key अणु
	काष्ठा ieee802154_llsec_device_key devkey;

	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा mac802154_llsec_device अणु
	काष्ठा ieee802154_llsec_device dev;

	काष्ठा hlist_node bucket_s;
	काष्ठा hlist_node bucket_hw;

	/* protects dev.frame_counter and the elements of dev.keys */
	spinlock_t lock;

	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा mac802154_llsec_seclevel अणु
	काष्ठा ieee802154_llsec_seclevel level;

	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा mac802154_llsec अणु
	काष्ठा ieee802154_llsec_params params;
	काष्ठा ieee802154_llsec_table table;

	DECLARE_HASHTABLE(devices_लघु, 6);
	DECLARE_HASHTABLE(devices_hw, 6);

	/* protects params, all other fields are fine with RCU */
	rwlock_t lock;
पूर्ण;

व्योम mac802154_llsec_init(काष्ठा mac802154_llsec *sec);
व्योम mac802154_llsec_destroy(काष्ठा mac802154_llsec *sec);

पूर्णांक mac802154_llsec_get_params(काष्ठा mac802154_llsec *sec,
			       काष्ठा ieee802154_llsec_params *params);
पूर्णांक mac802154_llsec_set_params(काष्ठा mac802154_llsec *sec,
			       स्थिर काष्ठा ieee802154_llsec_params *params,
			       पूर्णांक changed);

पूर्णांक mac802154_llsec_key_add(काष्ठा mac802154_llsec *sec,
			    स्थिर काष्ठा ieee802154_llsec_key_id *id,
			    स्थिर काष्ठा ieee802154_llsec_key *key);
पूर्णांक mac802154_llsec_key_del(काष्ठा mac802154_llsec *sec,
			    स्थिर काष्ठा ieee802154_llsec_key_id *key);

पूर्णांक mac802154_llsec_dev_add(काष्ठा mac802154_llsec *sec,
			    स्थिर काष्ठा ieee802154_llsec_device *dev);
पूर्णांक mac802154_llsec_dev_del(काष्ठा mac802154_llsec *sec,
			    __le64 device_addr);

पूर्णांक mac802154_llsec_devkey_add(काष्ठा mac802154_llsec *sec,
			       __le64 dev_addr,
			       स्थिर काष्ठा ieee802154_llsec_device_key *key);
पूर्णांक mac802154_llsec_devkey_del(काष्ठा mac802154_llsec *sec,
			       __le64 dev_addr,
			       स्थिर काष्ठा ieee802154_llsec_device_key *key);

पूर्णांक mac802154_llsec_seclevel_add(काष्ठा mac802154_llsec *sec,
				 स्थिर काष्ठा ieee802154_llsec_seclevel *sl);
पूर्णांक mac802154_llsec_seclevel_del(काष्ठा mac802154_llsec *sec,
				 स्थिर काष्ठा ieee802154_llsec_seclevel *sl);

पूर्णांक mac802154_llsec_encrypt(काष्ठा mac802154_llsec *sec, काष्ठा sk_buff *skb);
पूर्णांक mac802154_llsec_decrypt(काष्ठा mac802154_llsec *sec, काष्ठा sk_buff *skb);

#पूर्ण_अगर /* MAC802154_LLSEC_H */
