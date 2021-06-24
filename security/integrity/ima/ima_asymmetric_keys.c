<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Microsoft Corporation
 *
 * Author: Lakshmi Ramasubramanian (nramas@linux.microsoft.com)
 *
 * File: ima_asymmetric_keys.c
 *       Defines an IMA hook to measure asymmetric keys on key
 *       create or update.
 */

#समावेश <keys/asymmetric-type.h>
#समावेश <linux/user_namespace.h>
#समावेश "ima.h"

/**
 * ima_post_key_create_or_update - measure asymmetric keys
 * @keyring: keyring to which the key is linked to
 * @key: created or updated key
 * @payload: The data used to instantiate or update the key.
 * @payload_len: The length of @payload.
 * @flags: key flags
 * @create: flag indicating whether the key was created or updated
 *
 * Keys can only be measured, not appउठाओd.
 * The payload data used to instantiate or update the key is measured.
 */
व्योम ima_post_key_create_or_update(काष्ठा key *keyring, काष्ठा key *key,
				   स्थिर व्योम *payload, माप_प्रकार payload_len,
				   अचिन्हित दीर्घ flags, bool create)
अणु
	bool queued = false;

	/* Only asymmetric keys are handled by this hook. */
	अगर (key->type != &key_type_asymmetric)
		वापस;

	अगर (!payload || (payload_len == 0))
		वापस;

	अगर (ima_should_queue_key())
		queued = ima_queue_key(keyring, payload, payload_len);

	अगर (queued)
		वापस;

	/*
	 * keyring->description poपूर्णांकs to the name of the keyring
	 * (such as ".builtin_trusted_keys", ".ima", etc.) to
	 * which the given key is linked to.
	 *
	 * The name of the keyring is passed in the "eventname"
	 * parameter to process_buffer_measurement() and is set
	 * in the "eventname" field in ima_event_data क्रम
	 * the key measurement IMA event.
	 *
	 * The name of the keyring is also passed in the "keyring"
	 * parameter to process_buffer_measurement() to check
	 * अगर the IMA policy is configured to measure a key linked
	 * to the given keyring.
	 */
	process_buffer_measurement(&init_user_ns, शून्य, payload, payload_len,
				   keyring->description, KEY_CHECK, 0,
				   keyring->description, false);
पूर्ण
