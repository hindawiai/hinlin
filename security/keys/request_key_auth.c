<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Request key authorisation token key definition.
 *
 * Copyright (C) 2005 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See Documentation/security/keys/request-key.rst
 */

#समावेश <linux/sched.h>
#समावेश <linux/err.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश "internal.h"
#समावेश <keys/request_key_auth-type.h>

अटल पूर्णांक request_key_auth_preparse(काष्ठा key_preparsed_payload *);
अटल व्योम request_key_auth_मुक्त_preparse(काष्ठा key_preparsed_payload *);
अटल पूर्णांक request_key_auth_instantiate(काष्ठा key *,
					काष्ठा key_preparsed_payload *);
अटल व्योम request_key_auth_describe(स्थिर काष्ठा key *, काष्ठा seq_file *);
अटल व्योम request_key_auth_revoke(काष्ठा key *);
अटल व्योम request_key_auth_destroy(काष्ठा key *);
अटल दीर्घ request_key_auth_पढ़ो(स्थिर काष्ठा key *, अक्षर *, माप_प्रकार);

/*
 * The request-key authorisation key type definition.
 */
काष्ठा key_type key_type_request_key_auth = अणु
	.name		= ".request_key_auth",
	.def_datalen	= माप(काष्ठा request_key_auth),
	.preparse	= request_key_auth_preparse,
	.मुक्त_preparse	= request_key_auth_मुक्त_preparse,
	.instantiate	= request_key_auth_instantiate,
	.describe	= request_key_auth_describe,
	.revoke		= request_key_auth_revoke,
	.destroy	= request_key_auth_destroy,
	.पढ़ो		= request_key_auth_पढ़ो,
पूर्ण;

अटल पूर्णांक request_key_auth_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	वापस 0;
पूर्ण

अटल व्योम request_key_auth_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
पूर्ण

/*
 * Instantiate a request-key authorisation key.
 */
अटल पूर्णांक request_key_auth_instantiate(काष्ठा key *key,
					काष्ठा key_preparsed_payload *prep)
अणु
	rcu_assign_keypoपूर्णांकer(key, (काष्ठा request_key_auth *)prep->data);
	वापस 0;
पूर्ण

/*
 * Describe an authorisation token.
 */
अटल व्योम request_key_auth_describe(स्थिर काष्ठा key *key,
				      काष्ठा seq_file *m)
अणु
	काष्ठा request_key_auth *rka = dereference_key_rcu(key);

	अगर (!rka)
		वापस;

	seq_माला_दो(m, "key:");
	seq_माला_दो(m, key->description);
	अगर (key_is_positive(key))
		seq_म_लिखो(m, " pid:%d ci:%zu", rka->pid, rka->callout_len);
पूर्ण

/*
 * Read the callout_info data (retrieves the callout inक्रमmation).
 * - the key's semaphore is पढ़ो-locked
 */
अटल दीर्घ request_key_auth_पढ़ो(स्थिर काष्ठा key *key,
				  अक्षर *buffer, माप_प्रकार buflen)
अणु
	काष्ठा request_key_auth *rka = dereference_key_locked(key);
	माप_प्रकार datalen;
	दीर्घ ret;

	अगर (!rka)
		वापस -EKEYREVOKED;

	datalen = rka->callout_len;
	ret = datalen;

	/* we can वापस the data as is */
	अगर (buffer && buflen > 0) अणु
		अगर (buflen > datalen)
			buflen = datalen;

		स_नकल(buffer, rka->callout_info, buflen);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम मुक्त_request_key_auth(काष्ठा request_key_auth *rka)
अणु
	अगर (!rka)
		वापस;
	key_put(rka->target_key);
	key_put(rka->dest_keyring);
	अगर (rka->cred)
		put_cred(rka->cred);
	kमुक्त(rka->callout_info);
	kमुक्त(rka);
पूर्ण

/*
 * Dispose of the request_key_auth record under RCU conditions
 */
अटल व्योम request_key_auth_rcu_disposal(काष्ठा rcu_head *rcu)
अणु
	काष्ठा request_key_auth *rka =
		container_of(rcu, काष्ठा request_key_auth, rcu);

	मुक्त_request_key_auth(rka);
पूर्ण

/*
 * Handle revocation of an authorisation token key.
 *
 * Called with the key sem ग_लिखो-locked.
 */
अटल व्योम request_key_auth_revoke(काष्ठा key *key)
अणु
	काष्ठा request_key_auth *rka = dereference_key_locked(key);

	kenter("{%d}", key->serial);
	rcu_assign_keypoपूर्णांकer(key, शून्य);
	call_rcu(&rka->rcu, request_key_auth_rcu_disposal);
पूर्ण

/*
 * Destroy an instantiation authorisation token key.
 */
अटल व्योम request_key_auth_destroy(काष्ठा key *key)
अणु
	काष्ठा request_key_auth *rka = rcu_access_poपूर्णांकer(key->payload.rcu_data0);

	kenter("{%d}", key->serial);
	अगर (rka) अणु
		rcu_assign_keypoपूर्णांकer(key, शून्य);
		call_rcu(&rka->rcu, request_key_auth_rcu_disposal);
	पूर्ण
पूर्ण

/*
 * Create an authorisation token क्रम /sbin/request-key or whoever to gain
 * access to the caller's security data.
 */
काष्ठा key *request_key_auth_new(काष्ठा key *target, स्थिर अक्षर *op,
				 स्थिर व्योम *callout_info, माप_प्रकार callout_len,
				 काष्ठा key *dest_keyring)
अणु
	काष्ठा request_key_auth *rka, *irka;
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा key *authkey = शून्य;
	अक्षर desc[20];
	पूर्णांक ret = -ENOMEM;

	kenter("%d,", target->serial);

	/* allocate a auth record */
	rka = kzalloc(माप(*rka), GFP_KERNEL);
	अगर (!rka)
		जाओ error;
	rka->callout_info = kmemdup(callout_info, callout_len, GFP_KERNEL);
	अगर (!rka->callout_info)
		जाओ error_मुक्त_rka;
	rka->callout_len = callout_len;
	strlcpy(rka->op, op, माप(rka->op));

	/* see अगर the calling process is alपढ़ोy servicing the key request of
	 * another process */
	अगर (cred->request_key_auth) अणु
		/* it is - use that instantiation context here too */
		करोwn_पढ़ो(&cred->request_key_auth->sem);

		/* अगर the auth key has been revoked, then the key we're
		 * servicing is alपढ़ोy instantiated */
		अगर (test_bit(KEY_FLAG_REVOKED,
			     &cred->request_key_auth->flags)) अणु
			up_पढ़ो(&cred->request_key_auth->sem);
			ret = -EKEYREVOKED;
			जाओ error_मुक्त_rka;
		पूर्ण

		irka = cred->request_key_auth->payload.data[0];
		rka->cred = get_cred(irka->cred);
		rka->pid = irka->pid;

		up_पढ़ो(&cred->request_key_auth->sem);
	पूर्ण
	अन्यथा अणु
		/* it isn't - use this process as the context */
		rka->cred = get_cred(cred);
		rka->pid = current->pid;
	पूर्ण

	rka->target_key = key_get(target);
	rka->dest_keyring = key_get(dest_keyring);

	/* allocate the auth key */
	प्र_लिखो(desc, "%x", target->serial);

	authkey = key_alloc(&key_type_request_key_auth, desc,
			    cred->fsuid, cred->fsgid, cred,
			    KEY_POS_VIEW | KEY_POS_READ | KEY_POS_SEARCH | KEY_POS_LINK |
			    KEY_USR_VIEW, KEY_ALLOC_NOT_IN_QUOTA, शून्य);
	अगर (IS_ERR(authkey)) अणु
		ret = PTR_ERR(authkey);
		जाओ error_मुक्त_rka;
	पूर्ण

	/* स्थिरruct the auth key */
	ret = key_instantiate_and_link(authkey, rka, 0, शून्य, शून्य);
	अगर (ret < 0)
		जाओ error_put_authkey;

	kleave(" = {%d,%d}", authkey->serial, refcount_पढ़ो(&authkey->usage));
	वापस authkey;

error_put_authkey:
	key_put(authkey);
error_मुक्त_rka:
	मुक्त_request_key_auth(rka);
error:
	kleave("= %d", ret);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Search the current process's keyrings क्रम the authorisation key क्रम
 * instantiation of a key.
 */
काष्ठा key *key_get_instantiation_authkey(key_serial_t target_id)
अणु
	अक्षर description[16];
	काष्ठा keyring_search_context ctx = अणु
		.index_key.type		= &key_type_request_key_auth,
		.index_key.description	= description,
		.cred			= current_cred(),
		.match_data.cmp		= key_शेष_cmp,
		.match_data.raw_data	= description,
		.match_data.lookup_type	= KEYRING_SEARCH_LOOKUP_सूचीECT,
		.flags			= (KEYRING_SEARCH_DO_STATE_CHECK |
					   KEYRING_SEARCH_RECURSE),
	पूर्ण;
	काष्ठा key *authkey;
	key_ref_t authkey_ref;

	ctx.index_key.desc_len = प्र_लिखो(description, "%x", target_id);

	rcu_पढ़ो_lock();
	authkey_ref = search_process_keyrings_rcu(&ctx);
	rcu_पढ़ो_unlock();

	अगर (IS_ERR(authkey_ref)) अणु
		authkey = ERR_CAST(authkey_ref);
		अगर (authkey == ERR_PTR(-EAGAIN))
			authkey = ERR_PTR(-ENOKEY);
		जाओ error;
	पूर्ण

	authkey = key_ref_to_ptr(authkey_ref);
	अगर (test_bit(KEY_FLAG_REVOKED, &authkey->flags)) अणु
		key_put(authkey);
		authkey = ERR_PTR(-EKEYREVOKED);
	पूर्ण

error:
	वापस authkey;
पूर्ण
