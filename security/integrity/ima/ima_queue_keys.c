<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Microsoft Corporation
 *
 * Author: Lakshmi Ramasubramanian (nramas@linux.microsoft.com)
 *
 * File: ima_queue_keys.c
 *       Enables deferred processing of keys
 */

#समावेश <linux/user_namespace.h>
#समावेश <linux/workqueue.h>
#समावेश <keys/asymmetric-type.h>
#समावेश "ima.h"

/*
 * Flag to indicate whether a key can be processed
 * right away or should be queued क्रम processing later.
 */
अटल bool ima_process_keys;

/*
 * To synchronize access to the list of keys that need to be measured
 */
अटल DEFINE_MUTEX(ima_keys_lock);
अटल LIST_HEAD(ima_keys);

/*
 * If custom IMA policy is not loaded then keys queued up
 * क्रम measurement should be मुक्तd. This worker is used
 * क्रम handling this scenario.
 */
अटल दीर्घ ima_key_queue_समयout = 300000; /* 5 Minutes */
अटल व्योम ima_keys_handler(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(ima_keys_delayed_work, ima_keys_handler);
अटल bool समयr_expired;

/*
 * This worker function मुक्तs keys that may still be
 * queued up in हाल custom IMA policy was not loaded.
 */
अटल व्योम ima_keys_handler(काष्ठा work_काष्ठा *work)
अणु
	समयr_expired = true;
	ima_process_queued_keys();
पूर्ण

/*
 * This function sets up a worker to मुक्त queued keys in हाल
 * custom IMA policy was never loaded.
 */
व्योम ima_init_key_queue(व्योम)
अणु
	schedule_delayed_work(&ima_keys_delayed_work,
			      msecs_to_jअगरfies(ima_key_queue_समयout));
पूर्ण

अटल व्योम ima_मुक्त_key_entry(काष्ठा ima_key_entry *entry)
अणु
	अगर (entry) अणु
		kमुक्त(entry->payload);
		kमुक्त(entry->keyring_name);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल काष्ठा ima_key_entry *ima_alloc_key_entry(काष्ठा key *keyring,
						 स्थिर व्योम *payload,
						 माप_प्रकार payload_len)
अणु
	पूर्णांक rc = 0;
	स्थिर अक्षर *audit_cause = "ENOMEM";
	काष्ठा ima_key_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (entry) अणु
		entry->payload = kmemdup(payload, payload_len, GFP_KERNEL);
		entry->keyring_name = kstrdup(keyring->description,
					      GFP_KERNEL);
		entry->payload_len = payload_len;
	पूर्ण

	अगर ((entry == शून्य) || (entry->payload == शून्य) ||
	    (entry->keyring_name == शून्य)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&entry->list);

out:
	अगर (rc) अणु
		पूर्णांकegrity_audit_message(AUDIT_INTEGRITY_PCR, शून्य,
					keyring->description,
					func_measure_str(KEY_CHECK),
					audit_cause, rc, 0, rc);
		ima_मुक्त_key_entry(entry);
		entry = शून्य;
	पूर्ण

	वापस entry;
पूर्ण

bool ima_queue_key(काष्ठा key *keyring, स्थिर व्योम *payload,
		   माप_प्रकार payload_len)
अणु
	bool queued = false;
	काष्ठा ima_key_entry *entry;

	entry = ima_alloc_key_entry(keyring, payload, payload_len);
	अगर (!entry)
		वापस false;

	mutex_lock(&ima_keys_lock);
	अगर (!ima_process_keys) अणु
		list_add_tail(&entry->list, &ima_keys);
		queued = true;
	पूर्ण
	mutex_unlock(&ima_keys_lock);

	अगर (!queued)
		ima_मुक्त_key_entry(entry);

	वापस queued;
पूर्ण

/*
 * ima_process_queued_keys() - process keys queued क्रम measurement
 *
 * This function sets ima_process_keys to true and processes queued keys.
 * From here on keys will be processed right away (not queued).
 */
व्योम ima_process_queued_keys(व्योम)
अणु
	काष्ठा ima_key_entry *entry, *पंचांगp;
	bool process = false;

	अगर (ima_process_keys)
		वापस;

	/*
	 * Since ima_process_keys is set to true, any new key will be
	 * processed immediately and not be queued to ima_keys list.
	 * First one setting the ima_process_keys flag to true will
	 * process the queued keys.
	 */
	mutex_lock(&ima_keys_lock);
	अगर (!ima_process_keys) अणु
		ima_process_keys = true;
		process = true;
	पूर्ण
	mutex_unlock(&ima_keys_lock);

	अगर (!process)
		वापस;

	अगर (!समयr_expired)
		cancel_delayed_work_sync(&ima_keys_delayed_work);

	list_क्रम_each_entry_safe(entry, पंचांगp, &ima_keys, list) अणु
		अगर (!समयr_expired)
			process_buffer_measurement(&init_user_ns, शून्य,
						   entry->payload,
						   entry->payload_len,
						   entry->keyring_name,
						   KEY_CHECK, 0,
						   entry->keyring_name,
						   false);
		list_del(&entry->list);
		ima_मुक्त_key_entry(entry);
	पूर्ण
पूर्ण

अंतरभूत bool ima_should_queue_key(व्योम)
अणु
	वापस !ima_process_keys;
पूर्ण
