<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#अगर_अघोषित __W1_H
#घोषणा __W1_H

#समावेश <linux/w1.h>

#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>

#घोषणा W1_SLAVE_ACTIVE		0
#घोषणा W1_SLAVE_DETACH		1

/**
 * काष्ठा w1_async_cmd - execute callback from the w1_process kthपढ़ो
 * @async_entry: link entry
 * @cb: callback function, must list_del and destroy this list beक्रमe
 * वापसing
 *
 * When inserted पूर्णांकo the w1_master async_list, w1_process will execute
 * the callback.  Embed this पूर्णांकo the काष्ठाure with the command details.
 */
काष्ठा w1_async_cmd अणु
	काष्ठा list_head	async_entry;
	व्योम (*cb)(काष्ठा w1_master *dev, काष्ठा w1_async_cmd *async_cmd);
पूर्ण;

पूर्णांक w1_create_master_attributes(काष्ठा w1_master *master);
व्योम w1_destroy_master_attributes(काष्ठा w1_master *master);
व्योम w1_search(काष्ठा w1_master *dev, u8 search_type,
	       w1_slave_found_callback cb);
व्योम w1_search_devices(काष्ठा w1_master *dev, u8 search_type,
		       w1_slave_found_callback cb);
/* call w1_unref_slave to release the reference counts w1_search_slave added */
काष्ठा w1_slave *w1_search_slave(काष्ठा w1_reg_num *id);
/*
 * decrements the reference on sl->master and sl, and cleans up अगर zero
 * वापसs the reference count after it has been decremented
 */
पूर्णांक w1_unref_slave(काष्ठा w1_slave *sl);
व्योम w1_slave_found(काष्ठा w1_master *dev, u64 rn);
व्योम w1_search_process_cb(काष्ठा w1_master *dev, u8 search_type,
			  w1_slave_found_callback cb);
काष्ठा w1_slave *w1_slave_search_device(काष्ठा w1_master *dev,
					काष्ठा w1_reg_num *rn);
काष्ठा w1_master *w1_search_master_id(u32 id);

/* Disconnect and reconnect devices in the given family.  Used क्रम finding
 * unclaimed devices after a family has been रेजिस्टरed or releasing devices
 * after a family has been unरेजिस्टरed.  Set attach to 1 when a new family
 * has just been रेजिस्टरed, to 0 when it has been unरेजिस्टरed.
 */
व्योम w1_reconnect_slaves(काष्ठा w1_family *f, पूर्णांक attach);
पूर्णांक w1_attach_slave_device(काष्ठा w1_master *dev, काष्ठा w1_reg_num *rn);
/* 0 success, otherwise EBUSY */
पूर्णांक w1_slave_detach(काष्ठा w1_slave *sl);

व्योम __w1_हटाओ_master_device(काष्ठा w1_master *dev);

व्योम w1_family_put(काष्ठा w1_family *f);
व्योम __w1_family_get(काष्ठा w1_family *f);
काष्ठा w1_family *w1_family_रेजिस्टरed(u8 fid);

बाह्य काष्ठा device_driver w1_master_driver;
बाह्य काष्ठा device w1_master_device;
बाह्य पूर्णांक w1_max_slave_count;
बाह्य पूर्णांक w1_max_slave_ttl;
बाह्य काष्ठा list_head w1_masters;
बाह्य काष्ठा mutex w1_mlock;
बाह्य spinlock_t w1_flock;

पूर्णांक w1_process_callbacks(काष्ठा w1_master *dev);
पूर्णांक w1_process(व्योम *data);

#पूर्ण_अगर /* __W1_H */
