<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* user_defined.c: user defined key type
 *
 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/err.h>
#समावेश <keys/user-type.h>
#समावेश <linux/uaccess.h>
#समावेश "internal.h"

अटल पूर्णांक logon_vet_description(स्थिर अक्षर *desc);

/*
 * user defined keys take an arbitrary string as the description and an
 * arbitrary blob of data as the payload
 */
काष्ठा key_type key_type_user = अणु
	.name			= "user",
	.preparse		= user_preparse,
	.मुक्त_preparse		= user_मुक्त_preparse,
	.instantiate		= generic_key_instantiate,
	.update			= user_update,
	.revoke			= user_revoke,
	.destroy		= user_destroy,
	.describe		= user_describe,
	.पढ़ो			= user_पढ़ो,
पूर्ण;

EXPORT_SYMBOL_GPL(key_type_user);

/*
 * This key type is essentially the same as key_type_user, but it करोes
 * not define a .पढ़ो op. This is suitable क्रम storing username and
 * password pairs in the keyring that you करो not want to be पढ़ोable
 * from userspace.
 */
काष्ठा key_type key_type_logon = अणु
	.name			= "logon",
	.preparse		= user_preparse,
	.मुक्त_preparse		= user_मुक्त_preparse,
	.instantiate		= generic_key_instantiate,
	.update			= user_update,
	.revoke			= user_revoke,
	.destroy		= user_destroy,
	.describe		= user_describe,
	.vet_description	= logon_vet_description,
पूर्ण;
EXPORT_SYMBOL_GPL(key_type_logon);

/*
 * Preparse a user defined key payload
 */
पूर्णांक user_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा user_key_payload *upayload;
	माप_प्रकार datalen = prep->datalen;

	अगर (datalen <= 0 || datalen > 32767 || !prep->data)
		वापस -EINVAL;

	upayload = kदो_स्मृति(माप(*upayload) + datalen, GFP_KERNEL);
	अगर (!upayload)
		वापस -ENOMEM;

	/* attach the data */
	prep->quotalen = datalen;
	prep->payload.data[0] = upayload;
	upayload->datalen = datalen;
	स_नकल(upayload->data, prep->data, datalen);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(user_preparse);

/*
 * Free a preparse of a user defined key payload
 */
व्योम user_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	kमुक्त_sensitive(prep->payload.data[0]);
पूर्ण
EXPORT_SYMBOL_GPL(user_मुक्त_preparse);

अटल व्योम user_मुक्त_payload_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा user_key_payload *payload;

	payload = container_of(head, काष्ठा user_key_payload, rcu);
	kमुक्त_sensitive(payload);
पूर्ण

/*
 * update a user defined key
 * - the key's semaphore is ग_लिखो-locked
 */
पूर्णांक user_update(काष्ठा key *key, काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा user_key_payload *zap = शून्य;
	पूर्णांक ret;

	/* check the quota and attach the new data */
	ret = key_payload_reserve(key, prep->datalen);
	अगर (ret < 0)
		वापस ret;

	/* attach the new data, displacing the old */
	key->expiry = prep->expiry;
	अगर (key_is_positive(key))
		zap = dereference_key_locked(key);
	rcu_assign_keypoपूर्णांकer(key, prep->payload.data[0]);
	prep->payload.data[0] = शून्य;

	अगर (zap)
		call_rcu(&zap->rcu, user_मुक्त_payload_rcu);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(user_update);

/*
 * dispose of the links from a revoked keyring
 * - called with the key sem ग_लिखो-locked
 */
व्योम user_revoke(काष्ठा key *key)
अणु
	काष्ठा user_key_payload *upayload = user_key_payload_locked(key);

	/* clear the quota */
	key_payload_reserve(key, 0);

	अगर (upayload) अणु
		rcu_assign_keypoपूर्णांकer(key, शून्य);
		call_rcu(&upayload->rcu, user_मुक्त_payload_rcu);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(user_revoke);

/*
 * dispose of the data dangling from the corpse of a user key
 */
व्योम user_destroy(काष्ठा key *key)
अणु
	काष्ठा user_key_payload *upayload = key->payload.data[0];

	kमुक्त_sensitive(upayload);
पूर्ण

EXPORT_SYMBOL_GPL(user_destroy);

/*
 * describe the user key
 */
व्योम user_describe(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, key->description);
	अगर (key_is_positive(key))
		seq_म_लिखो(m, ": %u", key->datalen);
पूर्ण

EXPORT_SYMBOL_GPL(user_describe);

/*
 * पढ़ो the key data
 * - the key's semaphore is पढ़ो-locked
 */
दीर्घ user_पढ़ो(स्थिर काष्ठा key *key, अक्षर *buffer, माप_प्रकार buflen)
अणु
	स्थिर काष्ठा user_key_payload *upayload;
	दीर्घ ret;

	upayload = user_key_payload_locked(key);
	ret = upayload->datalen;

	/* we can वापस the data as is */
	अगर (buffer && buflen > 0) अणु
		अगर (buflen > upayload->datalen)
			buflen = upayload->datalen;

		स_नकल(buffer, upayload->data, buflen);
	पूर्ण

	वापस ret;
पूर्ण

EXPORT_SYMBOL_GPL(user_पढ़ो);

/* Vet the description क्रम a "logon" key */
अटल पूर्णांक logon_vet_description(स्थिर अक्षर *desc)
अणु
	अक्षर *p;

	/* require a "qualified" description string */
	p = म_अक्षर(desc, ':');
	अगर (!p)
		वापस -EINVAL;

	/* also reject description with ':' as first अक्षर */
	अगर (p == desc)
		वापस -EINVAL;

	वापस 0;
पूर्ण
