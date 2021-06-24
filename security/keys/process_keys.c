<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Manage a process's keyrings
 *
 * Copyright (C) 2004-2005, 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/fs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/security.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/init_task.h>
#समावेश <keys/request_key_auth-type.h>
#समावेश "internal.h"

/* Session keyring create vs join semaphore */
अटल DEFINE_MUTEX(key_session_mutex);

/* The root user's tracking काष्ठा */
काष्ठा key_user root_key_user = अणु
	.usage		= REFCOUNT_INIT(3),
	.cons_lock	= __MUTEX_INITIALIZER(root_key_user.cons_lock),
	.lock		= __SPIN_LOCK_UNLOCKED(root_key_user.lock),
	.nkeys		= ATOMIC_INIT(2),
	.nikeys		= ATOMIC_INIT(2),
	.uid		= GLOBAL_ROOT_UID,
पूर्ण;

/*
 * Get or create a user रेजिस्टर keyring.
 */
अटल काष्ठा key *get_user_रेजिस्टर(काष्ठा user_namespace *user_ns)
अणु
	काष्ठा key *reg_keyring = READ_ONCE(user_ns->user_keyring_रेजिस्टर);

	अगर (reg_keyring)
		वापस reg_keyring;

	करोwn_ग_लिखो(&user_ns->keyring_sem);

	/* Make sure there's a रेजिस्टर keyring.  It माला_लो owned by the
	 * user_namespace's owner.
	 */
	reg_keyring = user_ns->user_keyring_रेजिस्टर;
	अगर (!reg_keyring) अणु
		reg_keyring = keyring_alloc(".user_reg",
					    user_ns->owner, INVALID_GID,
					    &init_cred,
					    KEY_POS_WRITE | KEY_POS_SEARCH |
					    KEY_USR_VIEW | KEY_USR_READ,
					    0,
					    शून्य, शून्य);
		अगर (!IS_ERR(reg_keyring))
			smp_store_release(&user_ns->user_keyring_रेजिस्टर,
					  reg_keyring);
	पूर्ण

	up_ग_लिखो(&user_ns->keyring_sem);

	/* We करोn't वापस a ref since the keyring is pinned by the user_ns */
	वापस reg_keyring;
पूर्ण

/*
 * Look up the user and user session keyrings क्रम the current process's UID,
 * creating them अगर they करोn't exist.
 */
पूर्णांक look_up_user_keyrings(काष्ठा key **_user_keyring,
			  काष्ठा key **_user_session_keyring)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा user_namespace *user_ns = current_user_ns();
	काष्ठा key *reg_keyring, *uid_keyring, *session_keyring;
	key_perm_t user_keyring_perm;
	key_ref_t uid_keyring_r, session_keyring_r;
	uid_t uid = from_kuid(user_ns, cred->user->uid);
	अक्षर buf[20];
	पूर्णांक ret;

	user_keyring_perm = (KEY_POS_ALL & ~KEY_POS_SETATTR) | KEY_USR_ALL;

	kenter("%u", uid);

	reg_keyring = get_user_रेजिस्टर(user_ns);
	अगर (IS_ERR(reg_keyring))
		वापस PTR_ERR(reg_keyring);

	करोwn_ग_लिखो(&user_ns->keyring_sem);
	ret = 0;

	/* Get the user keyring.  Note that there may be one in existence
	 * alपढ़ोy as it may have been pinned by a session, but the user_काष्ठा
	 * poपूर्णांकing to it may have been destroyed by setuid.
	 */
	snम_लिखो(buf, माप(buf), "_uid.%u", uid);
	uid_keyring_r = keyring_search(make_key_ref(reg_keyring, true),
				       &key_type_keyring, buf, false);
	kdebug("_uid %p", uid_keyring_r);
	अगर (uid_keyring_r == ERR_PTR(-EAGAIN)) अणु
		uid_keyring = keyring_alloc(buf, cred->user->uid, INVALID_GID,
					    cred, user_keyring_perm,
					    KEY_ALLOC_UID_KEYRING |
					    KEY_ALLOC_IN_QUOTA,
					    शून्य, reg_keyring);
		अगर (IS_ERR(uid_keyring)) अणु
			ret = PTR_ERR(uid_keyring);
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ERR(uid_keyring_r)) अणु
		ret = PTR_ERR(uid_keyring_r);
		जाओ error;
	पूर्ण अन्यथा अणु
		uid_keyring = key_ref_to_ptr(uid_keyring_r);
	पूर्ण

	/* Get a शेष session keyring (which might also exist alपढ़ोy) */
	snम_लिखो(buf, माप(buf), "_uid_ses.%u", uid);
	session_keyring_r = keyring_search(make_key_ref(reg_keyring, true),
					   &key_type_keyring, buf, false);
	kdebug("_uid_ses %p", session_keyring_r);
	अगर (session_keyring_r == ERR_PTR(-EAGAIN)) अणु
		session_keyring = keyring_alloc(buf, cred->user->uid, INVALID_GID,
						cred, user_keyring_perm,
						KEY_ALLOC_UID_KEYRING |
						KEY_ALLOC_IN_QUOTA,
						शून्य, शून्य);
		अगर (IS_ERR(session_keyring)) अणु
			ret = PTR_ERR(session_keyring);
			जाओ error_release;
		पूर्ण

		/* We install a link from the user session keyring to
		 * the user keyring.
		 */
		ret = key_link(session_keyring, uid_keyring);
		अगर (ret < 0)
			जाओ error_release_session;

		/* And only then link the user-session keyring to the
		 * रेजिस्टर.
		 */
		ret = key_link(reg_keyring, session_keyring);
		अगर (ret < 0)
			जाओ error_release_session;
	पूर्ण अन्यथा अगर (IS_ERR(session_keyring_r)) अणु
		ret = PTR_ERR(session_keyring_r);
		जाओ error_release;
	पूर्ण अन्यथा अणु
		session_keyring = key_ref_to_ptr(session_keyring_r);
	पूर्ण

	up_ग_लिखो(&user_ns->keyring_sem);

	अगर (_user_session_keyring)
		*_user_session_keyring = session_keyring;
	अन्यथा
		key_put(session_keyring);
	अगर (_user_keyring)
		*_user_keyring = uid_keyring;
	अन्यथा
		key_put(uid_keyring);
	kleave(" = 0");
	वापस 0;

error_release_session:
	key_put(session_keyring);
error_release:
	key_put(uid_keyring);
error:
	up_ग_लिखो(&user_ns->keyring_sem);
	kleave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Get the user session keyring अगर it exists, but करोn't create it अगर it
 * करोesn't.
 */
काष्ठा key *get_user_session_keyring_rcu(स्थिर काष्ठा cred *cred)
अणु
	काष्ठा key *reg_keyring = READ_ONCE(cred->user_ns->user_keyring_रेजिस्टर);
	key_ref_t session_keyring_r;
	अक्षर buf[20];

	काष्ठा keyring_search_context ctx = अणु
		.index_key.type		= &key_type_keyring,
		.index_key.description	= buf,
		.cred			= cred,
		.match_data.cmp		= key_शेष_cmp,
		.match_data.raw_data	= buf,
		.match_data.lookup_type	= KEYRING_SEARCH_LOOKUP_सूचीECT,
		.flags			= KEYRING_SEARCH_DO_STATE_CHECK,
	पूर्ण;

	अगर (!reg_keyring)
		वापस शून्य;

	ctx.index_key.desc_len = snम_लिखो(buf, माप(buf), "_uid_ses.%u",
					  from_kuid(cred->user_ns,
						    cred->user->uid));

	session_keyring_r = keyring_search_rcu(make_key_ref(reg_keyring, true),
					       &ctx);
	अगर (IS_ERR(session_keyring_r))
		वापस शून्य;
	वापस key_ref_to_ptr(session_keyring_r);
पूर्ण

/*
 * Install a thपढ़ो keyring to the given credentials काष्ठा अगर it didn't have
 * one alपढ़ोy.  This is allowed to overrun the quota.
 *
 * Return: 0 अगर a thपढ़ो keyring is now present; -त्रुटि_सं on failure.
 */
पूर्णांक install_thपढ़ो_keyring_to_cred(काष्ठा cred *new)
अणु
	काष्ठा key *keyring;

	अगर (new->thपढ़ो_keyring)
		वापस 0;

	keyring = keyring_alloc("_tid", new->uid, new->gid, new,
				KEY_POS_ALL | KEY_USR_VIEW,
				KEY_ALLOC_QUOTA_OVERRUN,
				शून्य, शून्य);
	अगर (IS_ERR(keyring))
		वापस PTR_ERR(keyring);

	new->thपढ़ो_keyring = keyring;
	वापस 0;
पूर्ण

/*
 * Install a thपढ़ो keyring to the current task अगर it didn't have one alपढ़ोy.
 *
 * Return: 0 अगर a thपढ़ो keyring is now present; -त्रुटि_सं on failure.
 */
अटल पूर्णांक install_thपढ़ो_keyring(व्योम)
अणु
	काष्ठा cred *new;
	पूर्णांक ret;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	ret = install_thपढ़ो_keyring_to_cred(new);
	अगर (ret < 0) अणु
		पात_creds(new);
		वापस ret;
	पूर्ण

	वापस commit_creds(new);
पूर्ण

/*
 * Install a process keyring to the given credentials काष्ठा अगर it didn't have
 * one alपढ़ोy.  This is allowed to overrun the quota.
 *
 * Return: 0 अगर a process keyring is now present; -त्रुटि_सं on failure.
 */
पूर्णांक install_process_keyring_to_cred(काष्ठा cred *new)
अणु
	काष्ठा key *keyring;

	अगर (new->process_keyring)
		वापस 0;

	keyring = keyring_alloc("_pid", new->uid, new->gid, new,
				KEY_POS_ALL | KEY_USR_VIEW,
				KEY_ALLOC_QUOTA_OVERRUN,
				शून्य, शून्य);
	अगर (IS_ERR(keyring))
		वापस PTR_ERR(keyring);

	new->process_keyring = keyring;
	वापस 0;
पूर्ण

/*
 * Install a process keyring to the current task अगर it didn't have one alपढ़ोy.
 *
 * Return: 0 अगर a process keyring is now present; -त्रुटि_सं on failure.
 */
अटल पूर्णांक install_process_keyring(व्योम)
अणु
	काष्ठा cred *new;
	पूर्णांक ret;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	ret = install_process_keyring_to_cred(new);
	अगर (ret < 0) अणु
		पात_creds(new);
		वापस ret;
	पूर्ण

	वापस commit_creds(new);
पूर्ण

/*
 * Install the given keyring as the session keyring of the given credentials
 * काष्ठा, replacing the existing one अगर any.  If the given keyring is शून्य,
 * then install a new anonymous session keyring.
 * @cred can not be in use by any task yet.
 *
 * Return: 0 on success; -त्रुटि_सं on failure.
 */
पूर्णांक install_session_keyring_to_cred(काष्ठा cred *cred, काष्ठा key *keyring)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा key *old;

	might_sleep();

	/* create an empty session keyring */
	अगर (!keyring) अणु
		flags = KEY_ALLOC_QUOTA_OVERRUN;
		अगर (cred->session_keyring)
			flags = KEY_ALLOC_IN_QUOTA;

		keyring = keyring_alloc("_ses", cred->uid, cred->gid, cred,
					KEY_POS_ALL | KEY_USR_VIEW | KEY_USR_READ,
					flags, शून्य, शून्य);
		अगर (IS_ERR(keyring))
			वापस PTR_ERR(keyring);
	पूर्ण अन्यथा अणु
		__key_get(keyring);
	पूर्ण

	/* install the keyring */
	old = cred->session_keyring;
	cred->session_keyring = keyring;

	अगर (old)
		key_put(old);

	वापस 0;
पूर्ण

/*
 * Install the given keyring as the session keyring of the current task,
 * replacing the existing one अगर any.  If the given keyring is शून्य, then
 * install a new anonymous session keyring.
 *
 * Return: 0 on success; -त्रुटि_सं on failure.
 */
अटल पूर्णांक install_session_keyring(काष्ठा key *keyring)
अणु
	काष्ठा cred *new;
	पूर्णांक ret;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	ret = install_session_keyring_to_cred(new, keyring);
	अगर (ret < 0) अणु
		पात_creds(new);
		वापस ret;
	पूर्ण

	वापस commit_creds(new);
पूर्ण

/*
 * Handle the fsuid changing.
 */
व्योम key_fsuid_changed(काष्ठा cred *new_cred)
अणु
	/* update the ownership of the thपढ़ो keyring */
	अगर (new_cred->thपढ़ो_keyring) अणु
		करोwn_ग_लिखो(&new_cred->thपढ़ो_keyring->sem);
		new_cred->thपढ़ो_keyring->uid = new_cred->fsuid;
		up_ग_लिखो(&new_cred->thपढ़ो_keyring->sem);
	पूर्ण
पूर्ण

/*
 * Handle the fsgid changing.
 */
व्योम key_fsgid_changed(काष्ठा cred *new_cred)
अणु
	/* update the ownership of the thपढ़ो keyring */
	अगर (new_cred->thपढ़ो_keyring) अणु
		करोwn_ग_लिखो(&new_cred->thपढ़ो_keyring->sem);
		new_cred->thपढ़ो_keyring->gid = new_cred->fsgid;
		up_ग_लिखो(&new_cred->thपढ़ो_keyring->sem);
	पूर्ण
पूर्ण

/*
 * Search the process keyrings attached to the supplied cred क्रम the first
 * matching key under RCU conditions (the caller must be holding the RCU पढ़ो
 * lock).
 *
 * The search criteria are the type and the match function.  The description is
 * given to the match function as a parameter, but करोesn't otherwise influence
 * the search.  Typically the match function will compare the description
 * parameter to the key's description.
 *
 * This can only search keyrings that grant Search permission to the supplied
 * credentials.  Keyrings linked to searched keyrings will also be searched अगर
 * they grant Search permission too.  Keys can only be found अगर they grant
 * Search permission to the credentials.
 *
 * Returns a poपूर्णांकer to the key with the key usage count incremented अगर
 * successful, -EAGAIN अगर we didn't find any matching key or -ENOKEY अगर we only
 * matched negative keys.
 *
 * In the हाल of a successful वापस, the possession attribute is set on the
 * वापसed key reference.
 */
key_ref_t search_cred_keyrings_rcu(काष्ठा keyring_search_context *ctx)
अणु
	काष्ठा key *user_session;
	key_ref_t key_ref, ret, err;
	स्थिर काष्ठा cred *cred = ctx->cred;

	/* we want to वापस -EAGAIN or -ENOKEY अगर any of the keyrings were
	 * searchable, but we failed to find a key or we found a negative key;
	 * otherwise we want to वापस a sample error (probably -EACCES) अगर
	 * none of the keyrings were searchable
	 *
	 * in terms of priority: success > -ENOKEY > -EAGAIN > other error
	 */
	key_ref = शून्य;
	ret = शून्य;
	err = ERR_PTR(-EAGAIN);

	/* search the thपढ़ो keyring first */
	अगर (cred->thपढ़ो_keyring) अणु
		key_ref = keyring_search_rcu(
			make_key_ref(cred->thपढ़ो_keyring, 1), ctx);
		अगर (!IS_ERR(key_ref))
			जाओ found;

		चयन (PTR_ERR(key_ref)) अणु
		हाल -EAGAIN: /* no key */
		हाल -ENOKEY: /* negative key */
			ret = key_ref;
			अवरोध;
		शेष:
			err = key_ref;
			अवरोध;
		पूर्ण
	पूर्ण

	/* search the process keyring second */
	अगर (cred->process_keyring) अणु
		key_ref = keyring_search_rcu(
			make_key_ref(cred->process_keyring, 1), ctx);
		अगर (!IS_ERR(key_ref))
			जाओ found;

		चयन (PTR_ERR(key_ref)) अणु
		हाल -EAGAIN: /* no key */
			अगर (ret)
				अवरोध;
			fallthrough;
		हाल -ENOKEY: /* negative key */
			ret = key_ref;
			अवरोध;
		शेष:
			err = key_ref;
			अवरोध;
		पूर्ण
	पूर्ण

	/* search the session keyring */
	अगर (cred->session_keyring) अणु
		key_ref = keyring_search_rcu(
			make_key_ref(cred->session_keyring, 1), ctx);

		अगर (!IS_ERR(key_ref))
			जाओ found;

		चयन (PTR_ERR(key_ref)) अणु
		हाल -EAGAIN: /* no key */
			अगर (ret)
				अवरोध;
			fallthrough;
		हाल -ENOKEY: /* negative key */
			ret = key_ref;
			अवरोध;
		शेष:
			err = key_ref;
			अवरोध;
		पूर्ण
	पूर्ण
	/* or search the user-session keyring */
	अन्यथा अगर ((user_session = get_user_session_keyring_rcu(cred))) अणु
		key_ref = keyring_search_rcu(make_key_ref(user_session, 1),
					     ctx);
		key_put(user_session);

		अगर (!IS_ERR(key_ref))
			जाओ found;

		चयन (PTR_ERR(key_ref)) अणु
		हाल -EAGAIN: /* no key */
			अगर (ret)
				अवरोध;
			fallthrough;
		हाल -ENOKEY: /* negative key */
			ret = key_ref;
			अवरोध;
		शेष:
			err = key_ref;
			अवरोध;
		पूर्ण
	पूर्ण

	/* no key - decide on the error we're going to go क्रम */
	key_ref = ret ? ret : err;

found:
	वापस key_ref;
पूर्ण

/*
 * Search the process keyrings attached to the supplied cred क्रम the first
 * matching key in the manner of search_my_process_keyrings(), but also search
 * the keys attached to the assumed authorisation key using its credentials अगर
 * one is available.
 *
 * The caller must be holding the RCU पढ़ो lock.
 *
 * Return same as search_cred_keyrings_rcu().
 */
key_ref_t search_process_keyrings_rcu(काष्ठा keyring_search_context *ctx)
अणु
	काष्ठा request_key_auth *rka;
	key_ref_t key_ref, ret = ERR_PTR(-EACCES), err;

	key_ref = search_cred_keyrings_rcu(ctx);
	अगर (!IS_ERR(key_ref))
		जाओ found;
	err = key_ref;

	/* अगर this process has an instantiation authorisation key, then we also
	 * search the keyrings of the process mentioned there
	 * - we करोn't permit access to request_key auth keys via this method
	 */
	अगर (ctx->cred->request_key_auth &&
	    ctx->cred == current_cred() &&
	    ctx->index_key.type != &key_type_request_key_auth
	    ) अणु
		स्थिर काष्ठा cred *cred = ctx->cred;

		अगर (key_validate(cred->request_key_auth) == 0) अणु
			rka = ctx->cred->request_key_auth->payload.data[0];

			//// was search_process_keyrings() [ie. recursive]
			ctx->cred = rka->cred;
			key_ref = search_cred_keyrings_rcu(ctx);
			ctx->cred = cred;

			अगर (!IS_ERR(key_ref))
				जाओ found;
			ret = key_ref;
		पूर्ण
	पूर्ण

	/* no key - decide on the error we're going to go क्रम */
	अगर (err == ERR_PTR(-ENOKEY) || ret == ERR_PTR(-ENOKEY))
		key_ref = ERR_PTR(-ENOKEY);
	अन्यथा अगर (err == ERR_PTR(-EACCES))
		key_ref = ret;
	अन्यथा
		key_ref = err;

found:
	वापस key_ref;
पूर्ण
/*
 * See अगर the key we're looking at is the target key.
 */
bool lookup_user_key_possessed(स्थिर काष्ठा key *key,
			       स्थिर काष्ठा key_match_data *match_data)
अणु
	वापस key == match_data->raw_data;
पूर्ण

/*
 * Look up a key ID given us by userspace with a given permissions mask to get
 * the key it refers to.
 *
 * Flags can be passed to request that special keyrings be created अगर referred
 * to directly, to permit partially स्थिरructed keys to be found and to skip
 * validity and permission checks on the found key.
 *
 * Returns a poपूर्णांकer to the key with an incremented usage count अगर successful;
 * -EINVAL अगर the key ID is invalid; -ENOKEY अगर the key ID करोes not correspond
 * to a key or the best found key was a negative key; -EKEYREVOKED or
 * -EKEYEXPIRED अगर the best found key was revoked or expired; -EACCES अगर the
 * found key करोesn't grant the requested permit or the LSM denied access to it;
 * or -ENOMEM अगर a special keyring couldn't be created.
 *
 * In the हाल of a successful वापस, the possession attribute is set on the
 * वापसed key reference.
 */
key_ref_t lookup_user_key(key_serial_t id, अचिन्हित दीर्घ lflags,
			  क्रमागत key_need_perm need_perm)
अणु
	काष्ठा keyring_search_context ctx = अणु
		.match_data.cmp		= lookup_user_key_possessed,
		.match_data.lookup_type	= KEYRING_SEARCH_LOOKUP_सूचीECT,
		.flags			= (KEYRING_SEARCH_NO_STATE_CHECK |
					   KEYRING_SEARCH_RECURSE),
	पूर्ण;
	काष्ठा request_key_auth *rka;
	काष्ठा key *key, *user_session;
	key_ref_t key_ref, skey_ref;
	पूर्णांक ret;

try_again:
	ctx.cred = get_current_cred();
	key_ref = ERR_PTR(-ENOKEY);

	चयन (id) अणु
	हाल KEY_SPEC_THREAD_KEYRING:
		अगर (!ctx.cred->thपढ़ो_keyring) अणु
			अगर (!(lflags & KEY_LOOKUP_CREATE))
				जाओ error;

			ret = install_thपढ़ो_keyring();
			अगर (ret < 0) अणु
				key_ref = ERR_PTR(ret);
				जाओ error;
			पूर्ण
			जाओ reget_creds;
		पूर्ण

		key = ctx.cred->thपढ़ो_keyring;
		__key_get(key);
		key_ref = make_key_ref(key, 1);
		अवरोध;

	हाल KEY_SPEC_PROCESS_KEYRING:
		अगर (!ctx.cred->process_keyring) अणु
			अगर (!(lflags & KEY_LOOKUP_CREATE))
				जाओ error;

			ret = install_process_keyring();
			अगर (ret < 0) अणु
				key_ref = ERR_PTR(ret);
				जाओ error;
			पूर्ण
			जाओ reget_creds;
		पूर्ण

		key = ctx.cred->process_keyring;
		__key_get(key);
		key_ref = make_key_ref(key, 1);
		अवरोध;

	हाल KEY_SPEC_SESSION_KEYRING:
		अगर (!ctx.cred->session_keyring) अणु
			/* always install a session keyring upon access अगर one
			 * करोesn't exist yet */
			ret = look_up_user_keyrings(शून्य, &user_session);
			अगर (ret < 0)
				जाओ error;
			अगर (lflags & KEY_LOOKUP_CREATE)
				ret = join_session_keyring(शून्य);
			अन्यथा
				ret = install_session_keyring(user_session);

			key_put(user_session);
			अगर (ret < 0)
				जाओ error;
			जाओ reget_creds;
		पूर्ण अन्यथा अगर (test_bit(KEY_FLAG_UID_KEYRING,
				    &ctx.cred->session_keyring->flags) &&
			   lflags & KEY_LOOKUP_CREATE) अणु
			ret = join_session_keyring(शून्य);
			अगर (ret < 0)
				जाओ error;
			जाओ reget_creds;
		पूर्ण

		key = ctx.cred->session_keyring;
		__key_get(key);
		key_ref = make_key_ref(key, 1);
		अवरोध;

	हाल KEY_SPEC_USER_KEYRING:
		ret = look_up_user_keyrings(&key, शून्य);
		अगर (ret < 0)
			जाओ error;
		key_ref = make_key_ref(key, 1);
		अवरोध;

	हाल KEY_SPEC_USER_SESSION_KEYRING:
		ret = look_up_user_keyrings(शून्य, &key);
		अगर (ret < 0)
			जाओ error;
		key_ref = make_key_ref(key, 1);
		अवरोध;

	हाल KEY_SPEC_GROUP_KEYRING:
		/* group keyrings are not yet supported */
		key_ref = ERR_PTR(-EINVAL);
		जाओ error;

	हाल KEY_SPEC_REQKEY_AUTH_KEY:
		key = ctx.cred->request_key_auth;
		अगर (!key)
			जाओ error;

		__key_get(key);
		key_ref = make_key_ref(key, 1);
		अवरोध;

	हाल KEY_SPEC_REQUESTOR_KEYRING:
		अगर (!ctx.cred->request_key_auth)
			जाओ error;

		करोwn_पढ़ो(&ctx.cred->request_key_auth->sem);
		अगर (test_bit(KEY_FLAG_REVOKED,
			     &ctx.cred->request_key_auth->flags)) अणु
			key_ref = ERR_PTR(-EKEYREVOKED);
			key = शून्य;
		पूर्ण अन्यथा अणु
			rka = ctx.cred->request_key_auth->payload.data[0];
			key = rka->dest_keyring;
			__key_get(key);
		पूर्ण
		up_पढ़ो(&ctx.cred->request_key_auth->sem);
		अगर (!key)
			जाओ error;
		key_ref = make_key_ref(key, 1);
		अवरोध;

	शेष:
		key_ref = ERR_PTR(-EINVAL);
		अगर (id < 1)
			जाओ error;

		key = key_lookup(id);
		अगर (IS_ERR(key)) अणु
			key_ref = ERR_CAST(key);
			जाओ error;
		पूर्ण

		key_ref = make_key_ref(key, 0);

		/* check to see अगर we possess the key */
		ctx.index_key			= key->index_key;
		ctx.match_data.raw_data		= key;
		kdebug("check possessed");
		rcu_पढ़ो_lock();
		skey_ref = search_process_keyrings_rcu(&ctx);
		rcu_पढ़ो_unlock();
		kdebug("possessed=%p", skey_ref);

		अगर (!IS_ERR(skey_ref)) अणु
			key_put(key);
			key_ref = skey_ref;
		पूर्ण

		अवरोध;
	पूर्ण

	/* unlink करोes not use the nominated key in any way, so can skip all
	 * the permission checks as it is only concerned with the keyring */
	अगर (need_perm != KEY_NEED_UNLINK) अणु
		अगर (!(lflags & KEY_LOOKUP_PARTIAL)) अणु
			ret = रुको_क्रम_key_स्थिरruction(key, true);
			चयन (ret) अणु
			हाल -ERESTARTSYS:
				जाओ invalid_key;
			शेष:
				अगर (need_perm != KEY_AUTHTOKEN_OVERRIDE &&
				    need_perm != KEY_DEFER_PERM_CHECK)
					जाओ invalid_key;
				अवरोध;
			हाल 0:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (need_perm != KEY_DEFER_PERM_CHECK) अणु
			ret = key_validate(key);
			अगर (ret < 0)
				जाओ invalid_key;
		पूर्ण

		ret = -EIO;
		अगर (!(lflags & KEY_LOOKUP_PARTIAL) &&
		    key_पढ़ो_state(key) == KEY_IS_UNINSTANTIATED)
			जाओ invalid_key;
	पूर्ण

	/* check the permissions */
	ret = key_task_permission(key_ref, ctx.cred, need_perm);
	अगर (ret < 0)
		जाओ invalid_key;

	key->last_used_at = kसमय_get_real_seconds();

error:
	put_cred(ctx.cred);
	वापस key_ref;

invalid_key:
	key_ref_put(key_ref);
	key_ref = ERR_PTR(ret);
	जाओ error;

	/* अगर we attempted to install a keyring, then it may have caused new
	 * creds to be installed */
reget_creds:
	put_cred(ctx.cred);
	जाओ try_again;
पूर्ण
EXPORT_SYMBOL(lookup_user_key);

/*
 * Join the named keyring as the session keyring अगर possible अन्यथा attempt to
 * create a new one of that name and join that.
 *
 * If the name is शून्य, an empty anonymous keyring will be installed as the
 * session keyring.
 *
 * Named session keyrings are joined with a semaphore held to prevent the
 * keyrings from going away whilst the attempt is made to going them and also
 * to prevent a race in creating compatible session keyrings.
 */
दीर्घ join_session_keyring(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;
	काष्ठा key *keyring;
	दीर्घ ret, serial;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;
	old = current_cred();

	/* अगर no name is provided, install an anonymous keyring */
	अगर (!name) अणु
		ret = install_session_keyring_to_cred(new, शून्य);
		अगर (ret < 0)
			जाओ error;

		serial = new->session_keyring->serial;
		ret = commit_creds(new);
		अगर (ret == 0)
			ret = serial;
		जाओ okay;
	पूर्ण

	/* allow the user to join or create a named keyring */
	mutex_lock(&key_session_mutex);

	/* look क्रम an existing keyring of this name */
	keyring = find_keyring_by_name(name, false);
	अगर (PTR_ERR(keyring) == -ENOKEY) अणु
		/* not found - try and create a new one */
		keyring = keyring_alloc(
			name, old->uid, old->gid, old,
			KEY_POS_ALL | KEY_USR_VIEW | KEY_USR_READ | KEY_USR_LINK,
			KEY_ALLOC_IN_QUOTA, शून्य, शून्य);
		अगर (IS_ERR(keyring)) अणु
			ret = PTR_ERR(keyring);
			जाओ error2;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ERR(keyring)) अणु
		ret = PTR_ERR(keyring);
		जाओ error2;
	पूर्ण अन्यथा अगर (keyring == new->session_keyring) अणु
		ret = 0;
		जाओ error3;
	पूर्ण

	/* we've got a keyring - now to install it */
	ret = install_session_keyring_to_cred(new, keyring);
	अगर (ret < 0)
		जाओ error3;

	commit_creds(new);
	mutex_unlock(&key_session_mutex);

	ret = keyring->serial;
	key_put(keyring);
okay:
	वापस ret;

error3:
	key_put(keyring);
error2:
	mutex_unlock(&key_session_mutex);
error:
	पात_creds(new);
	वापस ret;
पूर्ण

/*
 * Replace a process's session keyring on behalf of one of its children when
 * the target  process is about to resume userspace execution.
 */
व्योम key_change_session_keyring(काष्ठा callback_head *twork)
अणु
	स्थिर काष्ठा cred *old = current_cred();
	काष्ठा cred *new = container_of(twork, काष्ठा cred, rcu);

	अगर (unlikely(current->flags & PF_EXITING)) अणु
		put_cred(new);
		वापस;
	पूर्ण

	new->  uid	= old->  uid;
	new-> euid	= old-> euid;
	new-> suid	= old-> suid;
	new->fsuid	= old->fsuid;
	new->  gid	= old->  gid;
	new-> egid	= old-> egid;
	new-> sgid	= old-> sgid;
	new->fsgid	= old->fsgid;
	new->user	= get_uid(old->user);
	new->user_ns	= get_user_ns(old->user_ns);
	new->group_info	= get_group_info(old->group_info);

	new->securebits	= old->securebits;
	new->cap_inheritable	= old->cap_inheritable;
	new->cap_permitted	= old->cap_permitted;
	new->cap_effective	= old->cap_effective;
	new->cap_ambient	= old->cap_ambient;
	new->cap_bset		= old->cap_bset;

	new->jit_keyring	= old->jit_keyring;
	new->thपढ़ो_keyring	= key_get(old->thपढ़ो_keyring);
	new->process_keyring	= key_get(old->process_keyring);

	security_transfer_creds(new, old);

	commit_creds(new);
पूर्ण

/*
 * Make sure that root's user and user-session keyrings exist.
 */
अटल पूर्णांक __init init_root_keyring(व्योम)
अणु
	वापस look_up_user_keyrings(शून्य, शून्य);
पूर्ण

late_initcall(init_root_keyring);
