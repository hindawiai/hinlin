<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Request a key from userspace
 *
 * Copyright (C) 2004-2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See Documentation/security/keys/request-key.rst
 */

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/kmod.h>
#समावेश <linux/err.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश "internal.h"
#समावेश <keys/request_key_auth-type.h>

#घोषणा key_negative_समयout	60	/* शेष समयout on a negative key's existence */

अटल काष्ठा key *check_cached_key(काष्ठा keyring_search_context *ctx)
अणु
#अगर_घोषित CONFIG_KEYS_REQUEST_CACHE
	काष्ठा key *key = current->cached_requested_key;

	अगर (key &&
	    ctx->match_data.cmp(key, &ctx->match_data) &&
	    !(key->flags & ((1 << KEY_FLAG_INVALIDATED) |
			    (1 << KEY_FLAG_REVOKED))))
		वापस key_get(key);
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

अटल व्योम cache_requested_key(काष्ठा key *key)
अणु
#अगर_घोषित CONFIG_KEYS_REQUEST_CACHE
	काष्ठा task_काष्ठा *t = current;

	key_put(t->cached_requested_key);
	t->cached_requested_key = key_get(key);
	set_tsk_thपढ़ो_flag(t, TIF_NOTIFY_RESUME);
#पूर्ण_अगर
पूर्ण

/**
 * complete_request_key - Complete the स्थिरruction of a key.
 * @authkey: The authorisation key.
 * @error: The success or failute of the स्थिरruction.
 *
 * Complete the attempt to स्थिरruct a key.  The key will be negated
 * अगर an error is indicated.  The authorisation key will be revoked
 * unconditionally.
 */
व्योम complete_request_key(काष्ठा key *authkey, पूर्णांक error)
अणु
	काष्ठा request_key_auth *rka = get_request_key_auth(authkey);
	काष्ठा key *key = rka->target_key;

	kenter("%d{%d},%d", authkey->serial, key->serial, error);

	अगर (error < 0)
		key_negate_and_link(key, key_negative_समयout, शून्य, authkey);
	अन्यथा
		key_revoke(authkey);
पूर्ण
EXPORT_SYMBOL(complete_request_key);

/*
 * Initialise a usermode helper that is going to have a specअगरic session
 * keyring.
 *
 * This is called in context of freshly विभाजनed kthपढ़ो beक्रमe kernel_execve(),
 * so we can simply install the desired session_keyring at this poपूर्णांक.
 */
अटल पूर्णांक umh_keys_init(काष्ठा subprocess_info *info, काष्ठा cred *cred)
अणु
	काष्ठा key *keyring = info->data;

	वापस install_session_keyring_to_cred(cred, keyring);
पूर्ण

/*
 * Clean up a usermode helper with session keyring.
 */
अटल व्योम umh_keys_cleanup(काष्ठा subprocess_info *info)
अणु
	काष्ठा key *keyring = info->data;
	key_put(keyring);
पूर्ण

/*
 * Call a usermode helper with a specअगरic session keyring.
 */
अटल पूर्णांक call_usermodehelper_keys(स्थिर अक्षर *path, अक्षर **argv, अक्षर **envp,
					काष्ठा key *session_keyring, पूर्णांक रुको)
अणु
	काष्ठा subprocess_info *info;

	info = call_usermodehelper_setup(path, argv, envp, GFP_KERNEL,
					  umh_keys_init, umh_keys_cleanup,
					  session_keyring);
	अगर (!info)
		वापस -ENOMEM;

	key_get(session_keyring);
	वापस call_usermodehelper_exec(info, रुको);
पूर्ण

/*
 * Request userspace finish the स्थिरruction of a key
 * - execute "/sbin/request-key <op> <key> <uid> <gid> <keyring> <keyring> <keyring>"
 */
अटल पूर्णांक call_sbin_request_key(काष्ठा key *authkey, व्योम *aux)
अणु
	अटल अक्षर स्थिर request_key[] = "/sbin/request-key";
	काष्ठा request_key_auth *rka = get_request_key_auth(authkey);
	स्थिर काष्ठा cred *cred = current_cred();
	key_serial_t prkey, sskey;
	काष्ठा key *key = rka->target_key, *keyring, *session, *user_session;
	अक्षर *argv[9], *envp[3], uid_str[12], gid_str[12];
	अक्षर key_str[12], keyring_str[3][12];
	अक्षर desc[20];
	पूर्णांक ret, i;

	kenter("{%d},{%d},%s", key->serial, authkey->serial, rka->op);

	ret = look_up_user_keyrings(शून्य, &user_session);
	अगर (ret < 0)
		जाओ error_us;

	/* allocate a new session keyring */
	प्र_लिखो(desc, "_req.%u", key->serial);

	cred = get_current_cred();
	keyring = keyring_alloc(desc, cred->fsuid, cred->fsgid, cred,
				KEY_POS_ALL | KEY_USR_VIEW | KEY_USR_READ,
				KEY_ALLOC_QUOTA_OVERRUN, शून्य, शून्य);
	put_cred(cred);
	अगर (IS_ERR(keyring)) अणु
		ret = PTR_ERR(keyring);
		जाओ error_alloc;
	पूर्ण

	/* attach the auth key to the session keyring */
	ret = key_link(keyring, authkey);
	अगर (ret < 0)
		जाओ error_link;

	/* record the UID and GID */
	प्र_लिखो(uid_str, "%d", from_kuid(&init_user_ns, cred->fsuid));
	प्र_लिखो(gid_str, "%d", from_kgid(&init_user_ns, cred->fsgid));

	/* we say which key is under स्थिरruction */
	प्र_लिखो(key_str, "%d", key->serial);

	/* we specअगरy the process's शेष keyrings */
	प्र_लिखो(keyring_str[0], "%d",
		cred->thपढ़ो_keyring ? cred->thपढ़ो_keyring->serial : 0);

	prkey = 0;
	अगर (cred->process_keyring)
		prkey = cred->process_keyring->serial;
	प्र_लिखो(keyring_str[1], "%d", prkey);

	session = cred->session_keyring;
	अगर (!session)
		session = user_session;
	sskey = session->serial;

	प्र_लिखो(keyring_str[2], "%d", sskey);

	/* set up a minimal environment */
	i = 0;
	envp[i++] = "HOME=/";
	envp[i++] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
	envp[i] = शून्य;

	/* set up the argument list */
	i = 0;
	argv[i++] = (अक्षर *)request_key;
	argv[i++] = (अक्षर *)rka->op;
	argv[i++] = key_str;
	argv[i++] = uid_str;
	argv[i++] = gid_str;
	argv[i++] = keyring_str[0];
	argv[i++] = keyring_str[1];
	argv[i++] = keyring_str[2];
	argv[i] = शून्य;

	/* करो it */
	ret = call_usermodehelper_keys(request_key, argv, envp, keyring,
				       UMH_WAIT_PROC);
	kdebug("usermode -> 0x%x", ret);
	अगर (ret >= 0) अणु
		/* ret is the निकास/रुको code */
		अगर (test_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags) ||
		    key_validate(key) < 0)
			ret = -ENOKEY;
		अन्यथा
			/* ignore any errors from userspace अगर the key was
			 * instantiated */
			ret = 0;
	पूर्ण

error_link:
	key_put(keyring);

error_alloc:
	key_put(user_session);
error_us:
	complete_request_key(authkey, ret);
	kleave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Call out to userspace क्रम key स्थिरruction.
 *
 * Program failure is ignored in favour of key status.
 */
अटल पूर्णांक स्थिरruct_key(काष्ठा key *key, स्थिर व्योम *callout_info,
			 माप_प्रकार callout_len, व्योम *aux,
			 काष्ठा key *dest_keyring)
अणु
	request_key_actor_t actor;
	काष्ठा key *authkey;
	पूर्णांक ret;

	kenter("%d,%p,%zu,%p", key->serial, callout_info, callout_len, aux);

	/* allocate an authorisation key */
	authkey = request_key_auth_new(key, "create", callout_info, callout_len,
				       dest_keyring);
	अगर (IS_ERR(authkey))
		वापस PTR_ERR(authkey);

	/* Make the call */
	actor = call_sbin_request_key;
	अगर (key->type->request_key)
		actor = key->type->request_key;

	ret = actor(authkey, aux);

	/* check that the actor called complete_request_key() prior to
	 * वापसing an error */
	WARN_ON(ret < 0 &&
		!test_bit(KEY_FLAG_INVALIDATED, &authkey->flags));

	key_put(authkey);
	kleave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Get the appropriate destination keyring क्रम the request.
 *
 * The keyring selected is वापसed with an extra reference upon it which the
 * caller must release.
 */
अटल पूर्णांक स्थिरruct_get_dest_keyring(काष्ठा key **_dest_keyring)
अणु
	काष्ठा request_key_auth *rka;
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा key *dest_keyring = *_dest_keyring, *authkey;
	पूर्णांक ret;

	kenter("%p", dest_keyring);

	/* find the appropriate keyring */
	अगर (dest_keyring) अणु
		/* the caller supplied one */
		key_get(dest_keyring);
	पूर्ण अन्यथा अणु
		bool करो_perm_check = true;

		/* use a शेष keyring; falling through the हालs until we
		 * find one that we actually have */
		चयन (cred->jit_keyring) अणु
		हाल KEY_REQKEY_DEFL_DEFAULT:
		हाल KEY_REQKEY_DEFL_REQUESTOR_KEYRING:
			अगर (cred->request_key_auth) अणु
				authkey = cred->request_key_auth;
				करोwn_पढ़ो(&authkey->sem);
				rka = get_request_key_auth(authkey);
				अगर (!test_bit(KEY_FLAG_REVOKED,
					      &authkey->flags))
					dest_keyring =
						key_get(rka->dest_keyring);
				up_पढ़ो(&authkey->sem);
				अगर (dest_keyring) अणु
					करो_perm_check = false;
					अवरोध;
				पूर्ण
			पूर्ण

			fallthrough;
		हाल KEY_REQKEY_DEFL_THREAD_KEYRING:
			dest_keyring = key_get(cred->thपढ़ो_keyring);
			अगर (dest_keyring)
				अवरोध;

			fallthrough;
		हाल KEY_REQKEY_DEFL_PROCESS_KEYRING:
			dest_keyring = key_get(cred->process_keyring);
			अगर (dest_keyring)
				अवरोध;

			fallthrough;
		हाल KEY_REQKEY_DEFL_SESSION_KEYRING:
			dest_keyring = key_get(cred->session_keyring);

			अगर (dest_keyring)
				अवरोध;

			fallthrough;
		हाल KEY_REQKEY_DEFL_USER_SESSION_KEYRING:
			ret = look_up_user_keyrings(शून्य, &dest_keyring);
			अगर (ret < 0)
				वापस ret;
			अवरोध;

		हाल KEY_REQKEY_DEFL_USER_KEYRING:
			ret = look_up_user_keyrings(&dest_keyring, शून्य);
			अगर (ret < 0)
				वापस ret;
			अवरोध;

		हाल KEY_REQKEY_DEFL_GROUP_KEYRING:
		शेष:
			BUG();
		पूर्ण

		/*
		 * Require Write permission on the keyring.  This is essential
		 * because the शेष keyring may be the session keyring, and
		 * joining a keyring only requires Search permission.
		 *
		 * However, this check is skipped क्रम the "requestor keyring" so
		 * that /sbin/request-key can itself use request_key() to add
		 * keys to the original requestor's destination keyring.
		 */
		अगर (dest_keyring && करो_perm_check) अणु
			ret = key_permission(make_key_ref(dest_keyring, 1),
					     KEY_NEED_WRITE);
			अगर (ret) अणु
				key_put(dest_keyring);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	*_dest_keyring = dest_keyring;
	kleave(" [dk %d]", key_serial(dest_keyring));
	वापस 0;
पूर्ण

/*
 * Allocate a new key in under-स्थिरruction state and attempt to link it in to
 * the requested keyring.
 *
 * May वापस a key that's alपढ़ोy under स्थिरruction instead अगर there was a
 * race between two thपढ़ो calling request_key().
 */
अटल पूर्णांक स्थिरruct_alloc_key(काष्ठा keyring_search_context *ctx,
			       काष्ठा key *dest_keyring,
			       अचिन्हित दीर्घ flags,
			       काष्ठा key_user *user,
			       काष्ठा key **_key)
अणु
	काष्ठा assoc_array_edit *edit = शून्य;
	काष्ठा key *key;
	key_perm_t perm;
	key_ref_t key_ref;
	पूर्णांक ret;

	kenter("%s,%s,,,",
	       ctx->index_key.type->name, ctx->index_key.description);

	*_key = शून्य;
	mutex_lock(&user->cons_lock);

	perm = KEY_POS_VIEW | KEY_POS_SEARCH | KEY_POS_LINK | KEY_POS_SETATTR;
	perm |= KEY_USR_VIEW;
	अगर (ctx->index_key.type->पढ़ो)
		perm |= KEY_POS_READ;
	अगर (ctx->index_key.type == &key_type_keyring ||
	    ctx->index_key.type->update)
		perm |= KEY_POS_WRITE;

	key = key_alloc(ctx->index_key.type, ctx->index_key.description,
			ctx->cred->fsuid, ctx->cred->fsgid, ctx->cred,
			perm, flags, शून्य);
	अगर (IS_ERR(key))
		जाओ alloc_failed;

	set_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags);

	अगर (dest_keyring) अणु
		ret = __key_link_lock(dest_keyring, &ctx->index_key);
		अगर (ret < 0)
			जाओ link_lock_failed;
		ret = __key_link_begin(dest_keyring, &ctx->index_key, &edit);
		अगर (ret < 0)
			जाओ link_pपुनः_स्मृति_failed;
	पूर्ण

	/* attach the key to the destination keyring under lock, but we करो need
	 * to करो another check just in हाल someone beat us to it whilst we
	 * रुकोed क्रम locks */
	mutex_lock(&key_स्थिरruction_mutex);

	rcu_पढ़ो_lock();
	key_ref = search_process_keyrings_rcu(ctx);
	rcu_पढ़ो_unlock();
	अगर (!IS_ERR(key_ref))
		जाओ key_alपढ़ोy_present;

	अगर (dest_keyring)
		__key_link(dest_keyring, key, &edit);

	mutex_unlock(&key_स्थिरruction_mutex);
	अगर (dest_keyring)
		__key_link_end(dest_keyring, &ctx->index_key, edit);
	mutex_unlock(&user->cons_lock);
	*_key = key;
	kleave(" = 0 [%d]", key_serial(key));
	वापस 0;

	/* the key is now present - we tell the caller that we found it by
	 * वापसing -EINPROGRESS  */
key_alपढ़ोy_present:
	key_put(key);
	mutex_unlock(&key_स्थिरruction_mutex);
	key = key_ref_to_ptr(key_ref);
	अगर (dest_keyring) अणु
		ret = __key_link_check_live_key(dest_keyring, key);
		अगर (ret == 0)
			__key_link(dest_keyring, key, &edit);
		__key_link_end(dest_keyring, &ctx->index_key, edit);
		अगर (ret < 0)
			जाओ link_check_failed;
	पूर्ण
	mutex_unlock(&user->cons_lock);
	*_key = key;
	kleave(" = -EINPROGRESS [%d]", key_serial(key));
	वापस -EINPROGRESS;

link_check_failed:
	mutex_unlock(&user->cons_lock);
	key_put(key);
	kleave(" = %d [linkcheck]", ret);
	वापस ret;

link_pपुनः_स्मृति_failed:
	__key_link_end(dest_keyring, &ctx->index_key, edit);
link_lock_failed:
	mutex_unlock(&user->cons_lock);
	key_put(key);
	kleave(" = %d [prelink]", ret);
	वापस ret;

alloc_failed:
	mutex_unlock(&user->cons_lock);
	kleave(" = %ld", PTR_ERR(key));
	वापस PTR_ERR(key);
पूर्ण

/*
 * Commence key स्थिरruction.
 */
अटल काष्ठा key *स्थिरruct_key_and_link(काष्ठा keyring_search_context *ctx,
					  स्थिर अक्षर *callout_info,
					  माप_प्रकार callout_len,
					  व्योम *aux,
					  काष्ठा key *dest_keyring,
					  अचिन्हित दीर्घ flags)
अणु
	काष्ठा key_user *user;
	काष्ठा key *key;
	पूर्णांक ret;

	kenter("");

	अगर (ctx->index_key.type == &key_type_keyring)
		वापस ERR_PTR(-EPERM);

	ret = स्थिरruct_get_dest_keyring(&dest_keyring);
	अगर (ret)
		जाओ error;

	user = key_user_lookup(current_fsuid());
	अगर (!user) अणु
		ret = -ENOMEM;
		जाओ error_put_dest_keyring;
	पूर्ण

	ret = स्थिरruct_alloc_key(ctx, dest_keyring, flags, user, &key);
	key_user_put(user);

	अगर (ret == 0) अणु
		ret = स्थिरruct_key(key, callout_info, callout_len, aux,
				    dest_keyring);
		अगर (ret < 0) अणु
			kdebug("cons failed");
			जाओ स्थिरruction_failed;
		पूर्ण
	पूर्ण अन्यथा अगर (ret == -EINPROGRESS) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		जाओ error_put_dest_keyring;
	पूर्ण

	key_put(dest_keyring);
	kleave(" = key %d", key_serial(key));
	वापस key;

स्थिरruction_failed:
	key_negate_and_link(key, key_negative_समयout, शून्य, शून्य);
	key_put(key);
error_put_dest_keyring:
	key_put(dest_keyring);
error:
	kleave(" = %d", ret);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * request_key_and_link - Request a key and cache it in a keyring.
 * @type: The type of key we want.
 * @description: The searchable description of the key.
 * @करोमुख्य_tag: The करोमुख्य in which the key operates.
 * @callout_info: The data to pass to the instantiation upcall (or शून्य).
 * @callout_len: The length of callout_info.
 * @aux: Auxiliary data क्रम the upcall.
 * @dest_keyring: Where to cache the key.
 * @flags: Flags to key_alloc().
 *
 * A key matching the specअगरied criteria (type, description, करोमुख्य_tag) is
 * searched क्रम in the process's keyrings and वापसed with its usage count
 * incremented अगर found.  Otherwise, अगर callout_info is not शून्य, a key will be
 * allocated and some service (probably in userspace) will be asked to
 * instantiate it.
 *
 * If successfully found or created, the key will be linked to the destination
 * keyring अगर one is provided.
 *
 * Returns a poपूर्णांकer to the key अगर successful; -EACCES, -ENOKEY, -EKEYREVOKED
 * or -EKEYEXPIRED अगर an inaccessible, negative, revoked or expired key was
 * found; -ENOKEY अगर no key was found and no @callout_info was given; -EDQUOT
 * अगर insufficient key quota was available to create a new key; or -ENOMEM अगर
 * insufficient memory was available.
 *
 * If the वापसed key was created, then it may still be under स्थिरruction,
 * and रुको_क्रम_key_स्थिरruction() should be used to रुको क्रम that to complete.
 */
काष्ठा key *request_key_and_link(काष्ठा key_type *type,
				 स्थिर अक्षर *description,
				 काष्ठा key_tag *करोमुख्य_tag,
				 स्थिर व्योम *callout_info,
				 माप_प्रकार callout_len,
				 व्योम *aux,
				 काष्ठा key *dest_keyring,
				 अचिन्हित दीर्घ flags)
अणु
	काष्ठा keyring_search_context ctx = अणु
		.index_key.type		= type,
		.index_key.करोमुख्य_tag	= करोमुख्य_tag,
		.index_key.description	= description,
		.index_key.desc_len	= म_माप(description),
		.cred			= current_cred(),
		.match_data.cmp		= key_शेष_cmp,
		.match_data.raw_data	= description,
		.match_data.lookup_type	= KEYRING_SEARCH_LOOKUP_सूचीECT,
		.flags			= (KEYRING_SEARCH_DO_STATE_CHECK |
					   KEYRING_SEARCH_SKIP_EXPIRED |
					   KEYRING_SEARCH_RECURSE),
	पूर्ण;
	काष्ठा key *key;
	key_ref_t key_ref;
	पूर्णांक ret;

	kenter("%s,%s,%p,%zu,%p,%p,%lx",
	       ctx.index_key.type->name, ctx.index_key.description,
	       callout_info, callout_len, aux, dest_keyring, flags);

	अगर (type->match_preparse) अणु
		ret = type->match_preparse(&ctx.match_data);
		अगर (ret < 0) अणु
			key = ERR_PTR(ret);
			जाओ error;
		पूर्ण
	पूर्ण

	key = check_cached_key(&ctx);
	अगर (key)
		जाओ error_मुक्त;

	/* search all the process keyrings क्रम a key */
	rcu_पढ़ो_lock();
	key_ref = search_process_keyrings_rcu(&ctx);
	rcu_पढ़ो_unlock();

	अगर (!IS_ERR(key_ref)) अणु
		अगर (dest_keyring) अणु
			ret = key_task_permission(key_ref, current_cred(),
						  KEY_NEED_LINK);
			अगर (ret < 0) अणु
				key_ref_put(key_ref);
				key = ERR_PTR(ret);
				जाओ error_मुक्त;
			पूर्ण
		पूर्ण

		key = key_ref_to_ptr(key_ref);
		अगर (dest_keyring) अणु
			ret = key_link(dest_keyring, key);
			अगर (ret < 0) अणु
				key_put(key);
				key = ERR_PTR(ret);
				जाओ error_मुक्त;
			पूर्ण
		पूर्ण

		/* Only cache the key on immediate success */
		cache_requested_key(key);
	पूर्ण अन्यथा अगर (PTR_ERR(key_ref) != -EAGAIN) अणु
		key = ERR_CAST(key_ref);
	पूर्ण अन्यथा  अणु
		/* the search failed, but the keyrings were searchable, so we
		 * should consult userspace अगर we can */
		key = ERR_PTR(-ENOKEY);
		अगर (!callout_info)
			जाओ error_मुक्त;

		key = स्थिरruct_key_and_link(&ctx, callout_info, callout_len,
					     aux, dest_keyring, flags);
	पूर्ण

error_मुक्त:
	अगर (type->match_मुक्त)
		type->match_मुक्त(&ctx.match_data);
error:
	kleave(" = %p", key);
	वापस key;
पूर्ण

/**
 * रुको_क्रम_key_स्थिरruction - Wait क्रम स्थिरruction of a key to complete
 * @key: The key being रुकोed क्रम.
 * @पूर्णांकr: Whether to रुको पूर्णांकerruptibly.
 *
 * Wait क्रम a key to finish being स्थिरructed.
 *
 * Returns 0 अगर successful; -ERESTARTSYS अगर the रुको was पूर्णांकerrupted; -ENOKEY
 * अगर the key was negated; or -EKEYREVOKED or -EKEYEXPIRED अगर the key was
 * revoked or expired.
 */
पूर्णांक रुको_क्रम_key_स्थिरruction(काष्ठा key *key, bool पूर्णांकr)
अणु
	पूर्णांक ret;

	ret = रुको_on_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT,
			  पूर्णांकr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
	अगर (ret)
		वापस -ERESTARTSYS;
	ret = key_पढ़ो_state(key);
	अगर (ret < 0)
		वापस ret;
	वापस key_validate(key);
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_key_स्थिरruction);

/**
 * request_key_tag - Request a key and रुको क्रम स्थिरruction
 * @type: Type of key.
 * @description: The searchable description of the key.
 * @करोमुख्य_tag: The करोमुख्य in which the key operates.
 * @callout_info: The data to pass to the instantiation upcall (or शून्य).
 *
 * As क्रम request_key_and_link() except that it करोes not add the वापसed key
 * to a keyring अगर found, new keys are always allocated in the user's quota,
 * the callout_info must be a NUL-terminated string and no auxiliary data can
 * be passed.
 *
 * Furthermore, it then works as रुको_क्रम_key_स्थिरruction() to रुको क्रम the
 * completion of keys undergoing स्थिरruction with a non-पूर्णांकerruptible रुको.
 */
काष्ठा key *request_key_tag(काष्ठा key_type *type,
			    स्थिर अक्षर *description,
			    काष्ठा key_tag *करोमुख्य_tag,
			    स्थिर अक्षर *callout_info)
अणु
	काष्ठा key *key;
	माप_प्रकार callout_len = 0;
	पूर्णांक ret;

	अगर (callout_info)
		callout_len = म_माप(callout_info);
	key = request_key_and_link(type, description, करोमुख्य_tag,
				   callout_info, callout_len,
				   शून्य, शून्य, KEY_ALLOC_IN_QUOTA);
	अगर (!IS_ERR(key)) अणु
		ret = रुको_क्रम_key_स्थिरruction(key, false);
		अगर (ret < 0) अणु
			key_put(key);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण
	वापस key;
पूर्ण
EXPORT_SYMBOL(request_key_tag);

/**
 * request_key_with_auxdata - Request a key with auxiliary data क्रम the upcaller
 * @type: The type of key we want.
 * @description: The searchable description of the key.
 * @करोमुख्य_tag: The करोमुख्य in which the key operates.
 * @callout_info: The data to pass to the instantiation upcall (or शून्य).
 * @callout_len: The length of callout_info.
 * @aux: Auxiliary data क्रम the upcall.
 *
 * As क्रम request_key_and_link() except that it करोes not add the वापसed key
 * to a keyring अगर found and new keys are always allocated in the user's quota.
 *
 * Furthermore, it then works as रुको_क्रम_key_स्थिरruction() to रुको क्रम the
 * completion of keys undergoing स्थिरruction with a non-पूर्णांकerruptible रुको.
 */
काष्ठा key *request_key_with_auxdata(काष्ठा key_type *type,
				     स्थिर अक्षर *description,
				     काष्ठा key_tag *करोमुख्य_tag,
				     स्थिर व्योम *callout_info,
				     माप_प्रकार callout_len,
				     व्योम *aux)
अणु
	काष्ठा key *key;
	पूर्णांक ret;

	key = request_key_and_link(type, description, करोमुख्य_tag,
				   callout_info, callout_len,
				   aux, शून्य, KEY_ALLOC_IN_QUOTA);
	अगर (!IS_ERR(key)) अणु
		ret = रुको_क्रम_key_स्थिरruction(key, false);
		अगर (ret < 0) अणु
			key_put(key);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण
	वापस key;
पूर्ण
EXPORT_SYMBOL(request_key_with_auxdata);

/**
 * request_key_rcu - Request key from RCU-पढ़ो-locked context
 * @type: The type of key we want.
 * @description: The name of the key we want.
 * @करोमुख्य_tag: The करोमुख्य in which the key operates.
 *
 * Request a key from a context that we may not sleep in (such as RCU-mode
 * pathwalk).  Keys under स्थिरruction are ignored.
 *
 * Return a poपूर्णांकer to the found key अगर successful, -ENOKEY अगर we couldn't find
 * a key or some other error अगर the key found was unsuitable or inaccessible.
 */
काष्ठा key *request_key_rcu(काष्ठा key_type *type,
			    स्थिर अक्षर *description,
			    काष्ठा key_tag *करोमुख्य_tag)
अणु
	काष्ठा keyring_search_context ctx = अणु
		.index_key.type		= type,
		.index_key.करोमुख्य_tag	= करोमुख्य_tag,
		.index_key.description	= description,
		.index_key.desc_len	= म_माप(description),
		.cred			= current_cred(),
		.match_data.cmp		= key_शेष_cmp,
		.match_data.raw_data	= description,
		.match_data.lookup_type	= KEYRING_SEARCH_LOOKUP_सूचीECT,
		.flags			= (KEYRING_SEARCH_DO_STATE_CHECK |
					   KEYRING_SEARCH_SKIP_EXPIRED),
	पूर्ण;
	काष्ठा key *key;
	key_ref_t key_ref;

	kenter("%s,%s", type->name, description);

	key = check_cached_key(&ctx);
	अगर (key)
		वापस key;

	/* search all the process keyrings क्रम a key */
	key_ref = search_process_keyrings_rcu(&ctx);
	अगर (IS_ERR(key_ref)) अणु
		key = ERR_CAST(key_ref);
		अगर (PTR_ERR(key_ref) == -EAGAIN)
			key = ERR_PTR(-ENOKEY);
	पूर्ण अन्यथा अणु
		key = key_ref_to_ptr(key_ref);
		cache_requested_key(key);
	पूर्ण

	kleave(" = %p", key);
	वापस key;
पूर्ण
EXPORT_SYMBOL(request_key_rcu);
