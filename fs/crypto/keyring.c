<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fileप्रणाली-level keyring क्रम fscrypt
 *
 * Copyright 2019 Google LLC
 */

/*
 * This file implements management of fscrypt master keys in the
 * fileप्रणाली-level keyring, including the ioctls:
 *
 * - FS_IOC_ADD_ENCRYPTION_KEY
 * - FS_IOC_REMOVE_ENCRYPTION_KEY
 * - FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS
 * - FS_IOC_GET_ENCRYPTION_KEY_STATUS
 *
 * See the "User API" section of Documentation/fileप्रणालीs/fscrypt.rst क्रम more
 * inक्रमmation about these ioctls.
 */

#समावेश <crypto/skcipher.h>
#समावेश <linux/key-type.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/seq_file.h>

#समावेश "fscrypt_private.h"

अटल व्योम wipe_master_key_secret(काष्ठा fscrypt_master_key_secret *secret)
अणु
	fscrypt_destroy_hkdf(&secret->hkdf);
	memzero_explicit(secret, माप(*secret));
पूर्ण

अटल व्योम move_master_key_secret(काष्ठा fscrypt_master_key_secret *dst,
				   काष्ठा fscrypt_master_key_secret *src)
अणु
	स_नकल(dst, src, माप(*dst));
	memzero_explicit(src, माप(*src));
पूर्ण

अटल व्योम मुक्त_master_key(काष्ठा fscrypt_master_key *mk)
अणु
	माप_प्रकार i;

	wipe_master_key_secret(&mk->mk_secret);

	क्रम (i = 0; i <= FSCRYPT_MODE_MAX; i++) अणु
		fscrypt_destroy_prepared_key(&mk->mk_direct_keys[i]);
		fscrypt_destroy_prepared_key(&mk->mk_iv_ino_lblk_64_keys[i]);
		fscrypt_destroy_prepared_key(&mk->mk_iv_ino_lblk_32_keys[i]);
	पूर्ण

	key_put(mk->mk_users);
	kमुक्त_sensitive(mk);
पूर्ण

अटल अंतरभूत bool valid_key_spec(स्थिर काष्ठा fscrypt_key_specअगरier *spec)
अणु
	अगर (spec->__reserved)
		वापस false;
	वापस master_key_spec_len(spec) != 0;
पूर्ण

अटल पूर्णांक fscrypt_key_instantiate(काष्ठा key *key,
				   काष्ठा key_preparsed_payload *prep)
अणु
	key->payload.data[0] = (काष्ठा fscrypt_master_key *)prep->data;
	वापस 0;
पूर्ण

अटल व्योम fscrypt_key_destroy(काष्ठा key *key)
अणु
	मुक्त_master_key(key->payload.data[0]);
पूर्ण

अटल व्योम fscrypt_key_describe(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, key->description);

	अगर (key_is_positive(key)) अणु
		स्थिर काष्ठा fscrypt_master_key *mk = key->payload.data[0];

		अगर (!is_master_key_secret_present(&mk->mk_secret))
			seq_माला_दो(m, ": secret removed");
	पूर्ण
पूर्ण

/*
 * Type of key in ->s_master_keys.  Each key of this type represents a master
 * key which has been added to the fileप्रणाली.  Its payload is a
 * 'struct fscrypt_master_key'.  The "." prefix in the key type name prevents
 * users from adding keys of this type via the keyrings syscalls rather than via
 * the पूर्णांकended method of FS_IOC_ADD_ENCRYPTION_KEY.
 */
अटल काष्ठा key_type key_type_fscrypt = अणु
	.name			= "._fscrypt",
	.instantiate		= fscrypt_key_instantiate,
	.destroy		= fscrypt_key_destroy,
	.describe		= fscrypt_key_describe,
पूर्ण;

अटल पूर्णांक fscrypt_user_key_instantiate(काष्ठा key *key,
					काष्ठा key_preparsed_payload *prep)
अणु
	/*
	 * We just अक्षरge FSCRYPT_MAX_KEY_SIZE bytes to the user's key quota क्रम
	 * each key, regardless of the exact key size.  The amount of memory
	 * actually used is greater than the size of the raw key anyway.
	 */
	वापस key_payload_reserve(key, FSCRYPT_MAX_KEY_SIZE);
पूर्ण

अटल व्योम fscrypt_user_key_describe(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, key->description);
पूर्ण

/*
 * Type of key in ->mk_users.  Each key of this type represents a particular
 * user who has added a particular master key.
 *
 * Note that the name of this key type really should be something like
 * ".fscrypt-user" instead of simply ".fscrypt".  But the लघुer name is chosen
 * मुख्यly क्रम simplicity of presentation in /proc/keys when पढ़ो by a non-root
 * user.  And it is expected to be rare that a key is actually added by multiple
 * users, since users should keep their encryption keys confidential.
 */
अटल काष्ठा key_type key_type_fscrypt_user = अणु
	.name			= ".fscrypt",
	.instantiate		= fscrypt_user_key_instantiate,
	.describe		= fscrypt_user_key_describe,
पूर्ण;

/* Search ->s_master_keys or ->mk_users */
अटल काष्ठा key *search_fscrypt_keyring(काष्ठा key *keyring,
					  काष्ठा key_type *type,
					  स्थिर अक्षर *description)
अणु
	/*
	 * We need to mark the keyring reference as "possessed" so that we
	 * acquire permission to search it, via the KEY_POS_SEARCH permission.
	 */
	key_ref_t keyref = make_key_ref(keyring, true /* possessed */);

	keyref = keyring_search(keyref, type, description, false);
	अगर (IS_ERR(keyref)) अणु
		अगर (PTR_ERR(keyref) == -EAGAIN || /* not found */
		    PTR_ERR(keyref) == -EKEYREVOKED) /* recently invalidated */
			keyref = ERR_PTR(-ENOKEY);
		वापस ERR_CAST(keyref);
	पूर्ण
	वापस key_ref_to_ptr(keyref);
पूर्ण

#घोषणा FSCRYPT_FS_KEYRING_DESCRIPTION_SIZE	\
	(CONST_STRLEN("fscrypt-") + माप_field(काष्ठा super_block, s_id))

#घोषणा FSCRYPT_MK_DESCRIPTION_SIZE	(2 * FSCRYPT_KEY_IDENTIFIER_SIZE + 1)

#घोषणा FSCRYPT_MK_USERS_DESCRIPTION_SIZE	\
	(CONST_STRLEN("fscrypt-") + 2 * FSCRYPT_KEY_IDENTIFIER_SIZE + \
	 CONST_STRLEN("-users") + 1)

#घोषणा FSCRYPT_MK_USER_DESCRIPTION_SIZE	\
	(2 * FSCRYPT_KEY_IDENTIFIER_SIZE + CONST_STRLEN(".uid.") + 10 + 1)

अटल व्योम क्रमmat_fs_keyring_description(
			अक्षर description[FSCRYPT_FS_KEYRING_DESCRIPTION_SIZE],
			स्थिर काष्ठा super_block *sb)
अणु
	प्र_लिखो(description, "fscrypt-%s", sb->s_id);
पूर्ण

अटल व्योम क्रमmat_mk_description(
			अक्षर description[FSCRYPT_MK_DESCRIPTION_SIZE],
			स्थिर काष्ठा fscrypt_key_specअगरier *mk_spec)
अणु
	प्र_लिखो(description, "%*phN",
		master_key_spec_len(mk_spec), (u8 *)&mk_spec->u);
पूर्ण

अटल व्योम क्रमmat_mk_users_keyring_description(
			अक्षर description[FSCRYPT_MK_USERS_DESCRIPTION_SIZE],
			स्थिर u8 mk_identअगरier[FSCRYPT_KEY_IDENTIFIER_SIZE])
अणु
	प्र_लिखो(description, "fscrypt-%*phN-users",
		FSCRYPT_KEY_IDENTIFIER_SIZE, mk_identअगरier);
पूर्ण

अटल व्योम क्रमmat_mk_user_description(
			अक्षर description[FSCRYPT_MK_USER_DESCRIPTION_SIZE],
			स्थिर u8 mk_identअगरier[FSCRYPT_KEY_IDENTIFIER_SIZE])
अणु

	प्र_लिखो(description, "%*phN.uid.%u", FSCRYPT_KEY_IDENTIFIER_SIZE,
		mk_identअगरier, __kuid_val(current_fsuid()));
पूर्ण

/* Create ->s_master_keys अगर needed.  Synchronized by fscrypt_add_key_mutex. */
अटल पूर्णांक allocate_fileप्रणाली_keyring(काष्ठा super_block *sb)
अणु
	अक्षर description[FSCRYPT_FS_KEYRING_DESCRIPTION_SIZE];
	काष्ठा key *keyring;

	अगर (sb->s_master_keys)
		वापस 0;

	क्रमmat_fs_keyring_description(description, sb);
	keyring = keyring_alloc(description, GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
				current_cred(), KEY_POS_SEARCH |
				  KEY_USR_SEARCH | KEY_USR_READ | KEY_USR_VIEW,
				KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(keyring))
		वापस PTR_ERR(keyring);

	/*
	 * Pairs with the smp_load_acquire() in fscrypt_find_master_key().
	 * I.e., here we publish ->s_master_keys with a RELEASE barrier so that
	 * concurrent tasks can ACQUIRE it.
	 */
	smp_store_release(&sb->s_master_keys, keyring);
	वापस 0;
पूर्ण

व्योम fscrypt_sb_मुक्त(काष्ठा super_block *sb)
अणु
	key_put(sb->s_master_keys);
	sb->s_master_keys = शून्य;
पूर्ण

/*
 * Find the specअगरied master key in ->s_master_keys.
 * Returns ERR_PTR(-ENOKEY) अगर not found.
 */
काष्ठा key *fscrypt_find_master_key(काष्ठा super_block *sb,
				    स्थिर काष्ठा fscrypt_key_specअगरier *mk_spec)
अणु
	काष्ठा key *keyring;
	अक्षर description[FSCRYPT_MK_DESCRIPTION_SIZE];

	/*
	 * Pairs with the smp_store_release() in allocate_fileप्रणाली_keyring().
	 * I.e., another task can publish ->s_master_keys concurrently,
	 * executing a RELEASE barrier.  We need to use smp_load_acquire() here
	 * to safely ACQUIRE the memory the other task published.
	 */
	keyring = smp_load_acquire(&sb->s_master_keys);
	अगर (keyring == शून्य)
		वापस ERR_PTR(-ENOKEY); /* No keyring yet, so no keys yet. */

	क्रमmat_mk_description(description, mk_spec);
	वापस search_fscrypt_keyring(keyring, &key_type_fscrypt, description);
पूर्ण

अटल पूर्णांक allocate_master_key_users_keyring(काष्ठा fscrypt_master_key *mk)
अणु
	अक्षर description[FSCRYPT_MK_USERS_DESCRIPTION_SIZE];
	काष्ठा key *keyring;

	क्रमmat_mk_users_keyring_description(description,
					    mk->mk_spec.u.identअगरier);
	keyring = keyring_alloc(description, GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
				current_cred(), KEY_POS_SEARCH |
				  KEY_USR_SEARCH | KEY_USR_READ | KEY_USR_VIEW,
				KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(keyring))
		वापस PTR_ERR(keyring);

	mk->mk_users = keyring;
	वापस 0;
पूर्ण

/*
 * Find the current user's "key" in the master key's ->mk_users.
 * Returns ERR_PTR(-ENOKEY) अगर not found.
 */
अटल काष्ठा key *find_master_key_user(काष्ठा fscrypt_master_key *mk)
अणु
	अक्षर description[FSCRYPT_MK_USER_DESCRIPTION_SIZE];

	क्रमmat_mk_user_description(description, mk->mk_spec.u.identअगरier);
	वापस search_fscrypt_keyring(mk->mk_users, &key_type_fscrypt_user,
				      description);
पूर्ण

/*
 * Give the current user a "key" in ->mk_users.  This अक्षरges the user's quota
 * and marks the master key as added by the current user, so that it cannot be
 * हटाओd by another user with the key.  Either the master key's key->sem must
 * be held क्रम ग_लिखो, or the master key must be still undergoing initialization.
 */
अटल पूर्णांक add_master_key_user(काष्ठा fscrypt_master_key *mk)
अणु
	अक्षर description[FSCRYPT_MK_USER_DESCRIPTION_SIZE];
	काष्ठा key *mk_user;
	पूर्णांक err;

	क्रमmat_mk_user_description(description, mk->mk_spec.u.identअगरier);
	mk_user = key_alloc(&key_type_fscrypt_user, description,
			    current_fsuid(), current_gid(), current_cred(),
			    KEY_POS_SEARCH | KEY_USR_VIEW, 0, शून्य);
	अगर (IS_ERR(mk_user))
		वापस PTR_ERR(mk_user);

	err = key_instantiate_and_link(mk_user, शून्य, 0, mk->mk_users, शून्य);
	key_put(mk_user);
	वापस err;
पूर्ण

/*
 * Remove the current user's "key" from ->mk_users.
 * The master key's key->sem must be held क्रम ग_लिखो.
 *
 * Returns 0 अगर हटाओd, -ENOKEY अगर not found, or another -त्रुटि_सं code.
 */
अटल पूर्णांक हटाओ_master_key_user(काष्ठा fscrypt_master_key *mk)
अणु
	काष्ठा key *mk_user;
	पूर्णांक err;

	mk_user = find_master_key_user(mk);
	अगर (IS_ERR(mk_user))
		वापस PTR_ERR(mk_user);
	err = key_unlink(mk->mk_users, mk_user);
	key_put(mk_user);
	वापस err;
पूर्ण

/*
 * Allocate a new fscrypt_master_key which contains the given secret, set it as
 * the payload of a new 'struct key' of type fscrypt, and link the 'struct key'
 * पूर्णांकo the given keyring.  Synchronized by fscrypt_add_key_mutex.
 */
अटल पूर्णांक add_new_master_key(काष्ठा fscrypt_master_key_secret *secret,
			      स्थिर काष्ठा fscrypt_key_specअगरier *mk_spec,
			      काष्ठा key *keyring)
अणु
	काष्ठा fscrypt_master_key *mk;
	अक्षर description[FSCRYPT_MK_DESCRIPTION_SIZE];
	काष्ठा key *key;
	पूर्णांक err;

	mk = kzalloc(माप(*mk), GFP_KERNEL);
	अगर (!mk)
		वापस -ENOMEM;

	mk->mk_spec = *mk_spec;

	move_master_key_secret(&mk->mk_secret, secret);

	refcount_set(&mk->mk_refcount, 1); /* secret is present */
	INIT_LIST_HEAD(&mk->mk_decrypted_inodes);
	spin_lock_init(&mk->mk_decrypted_inodes_lock);

	अगर (mk_spec->type == FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER) अणु
		err = allocate_master_key_users_keyring(mk);
		अगर (err)
			जाओ out_मुक्त_mk;
		err = add_master_key_user(mk);
		अगर (err)
			जाओ out_मुक्त_mk;
	पूर्ण

	/*
	 * Note that we करोn't charge this key to anyone's quota, since when
	 * ->mk_users is in use those keys are अक्षरged instead, and otherwise
	 * (when ->mk_users isn't in use) only root can add these keys.
	 */
	क्रमmat_mk_description(description, mk_spec);
	key = key_alloc(&key_type_fscrypt, description,
			GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, current_cred(),
			KEY_POS_SEARCH | KEY_USR_SEARCH | KEY_USR_VIEW,
			KEY_ALLOC_NOT_IN_QUOTA, शून्य);
	अगर (IS_ERR(key)) अणु
		err = PTR_ERR(key);
		जाओ out_मुक्त_mk;
	पूर्ण
	err = key_instantiate_and_link(key, mk, माप(*mk), keyring, शून्य);
	key_put(key);
	अगर (err)
		जाओ out_मुक्त_mk;

	वापस 0;

out_मुक्त_mk:
	मुक्त_master_key(mk);
	वापस err;
पूर्ण

#घोषणा KEY_DEAD	1

अटल पूर्णांक add_existing_master_key(काष्ठा fscrypt_master_key *mk,
				   काष्ठा fscrypt_master_key_secret *secret)
अणु
	काष्ठा key *mk_user;
	bool rekey;
	पूर्णांक err;

	/*
	 * If the current user is alपढ़ोy in ->mk_users, then there's nothing to
	 * करो.  (Not applicable क्रम v1 policy keys, which have शून्य ->mk_users.)
	 */
	अगर (mk->mk_users) अणु
		mk_user = find_master_key_user(mk);
		अगर (mk_user != ERR_PTR(-ENOKEY)) अणु
			अगर (IS_ERR(mk_user))
				वापस PTR_ERR(mk_user);
			key_put(mk_user);
			वापस 0;
		पूर्ण
	पूर्ण

	/* If we'll be re-adding ->mk_secret, try to take the reference. */
	rekey = !is_master_key_secret_present(&mk->mk_secret);
	अगर (rekey && !refcount_inc_not_zero(&mk->mk_refcount))
		वापस KEY_DEAD;

	/* Add the current user to ->mk_users, अगर applicable. */
	अगर (mk->mk_users) अणु
		err = add_master_key_user(mk);
		अगर (err) अणु
			अगर (rekey && refcount_dec_and_test(&mk->mk_refcount))
				वापस KEY_DEAD;
			वापस err;
		पूर्ण
	पूर्ण

	/* Re-add the secret अगर needed. */
	अगर (rekey)
		move_master_key_secret(&mk->mk_secret, secret);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_add_master_key(काष्ठा super_block *sb,
			     काष्ठा fscrypt_master_key_secret *secret,
			     स्थिर काष्ठा fscrypt_key_specअगरier *mk_spec)
अणु
	अटल DEFINE_MUTEX(fscrypt_add_key_mutex);
	काष्ठा key *key;
	पूर्णांक err;

	mutex_lock(&fscrypt_add_key_mutex); /* serialize find + link */
retry:
	key = fscrypt_find_master_key(sb, mk_spec);
	अगर (IS_ERR(key)) अणु
		err = PTR_ERR(key);
		अगर (err != -ENOKEY)
			जाओ out_unlock;
		/* Didn't find the key in ->s_master_keys.  Add it. */
		err = allocate_fileप्रणाली_keyring(sb);
		अगर (err)
			जाओ out_unlock;
		err = add_new_master_key(secret, mk_spec, sb->s_master_keys);
	पूर्ण अन्यथा अणु
		/*
		 * Found the key in ->s_master_keys.  Re-add the secret अगर
		 * needed, and add the user to ->mk_users अगर needed.
		 */
		करोwn_ग_लिखो(&key->sem);
		err = add_existing_master_key(key->payload.data[0], secret);
		up_ग_लिखो(&key->sem);
		अगर (err == KEY_DEAD) अणु
			/* Key being हटाओd or needs to be हटाओd */
			key_invalidate(key);
			key_put(key);
			जाओ retry;
		पूर्ण
		key_put(key);
	पूर्ण
out_unlock:
	mutex_unlock(&fscrypt_add_key_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक add_master_key(काष्ठा super_block *sb,
			  काष्ठा fscrypt_master_key_secret *secret,
			  काष्ठा fscrypt_key_specअगरier *key_spec)
अणु
	पूर्णांक err;

	अगर (key_spec->type == FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER) अणु
		err = fscrypt_init_hkdf(&secret->hkdf, secret->raw,
					secret->size);
		अगर (err)
			वापस err;

		/*
		 * Now that the HKDF context is initialized, the raw key is no
		 * दीर्घer needed.
		 */
		memzero_explicit(secret->raw, secret->size);

		/* Calculate the key identअगरier */
		err = fscrypt_hkdf_expand(&secret->hkdf,
					  HKDF_CONTEXT_KEY_IDENTIFIER, शून्य, 0,
					  key_spec->u.identअगरier,
					  FSCRYPT_KEY_IDENTIFIER_SIZE);
		अगर (err)
			वापस err;
	पूर्ण
	वापस करो_add_master_key(sb, secret, key_spec);
पूर्ण

अटल पूर्णांक fscrypt_provisioning_key_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	स्थिर काष्ठा fscrypt_provisioning_key_payload *payload = prep->data;

	अगर (prep->datalen < माप(*payload) + FSCRYPT_MIN_KEY_SIZE ||
	    prep->datalen > माप(*payload) + FSCRYPT_MAX_KEY_SIZE)
		वापस -EINVAL;

	अगर (payload->type != FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR &&
	    payload->type != FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER)
		वापस -EINVAL;

	अगर (payload->__reserved)
		वापस -EINVAL;

	prep->payload.data[0] = kmemdup(payload, prep->datalen, GFP_KERNEL);
	अगर (!prep->payload.data[0])
		वापस -ENOMEM;

	prep->quotalen = prep->datalen;
	वापस 0;
पूर्ण

अटल व्योम fscrypt_provisioning_key_मुक्त_preparse(
					काष्ठा key_preparsed_payload *prep)
अणु
	kमुक्त_sensitive(prep->payload.data[0]);
पूर्ण

अटल व्योम fscrypt_provisioning_key_describe(स्थिर काष्ठा key *key,
					      काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, key->description);
	अगर (key_is_positive(key)) अणु
		स्थिर काष्ठा fscrypt_provisioning_key_payload *payload =
			key->payload.data[0];

		seq_म_लिखो(m, ": %u [%u]", key->datalen, payload->type);
	पूर्ण
पूर्ण

अटल व्योम fscrypt_provisioning_key_destroy(काष्ठा key *key)
अणु
	kमुक्त_sensitive(key->payload.data[0]);
पूर्ण

अटल काष्ठा key_type key_type_fscrypt_provisioning = अणु
	.name			= "fscrypt-provisioning",
	.preparse		= fscrypt_provisioning_key_preparse,
	.मुक्त_preparse		= fscrypt_provisioning_key_मुक्त_preparse,
	.instantiate		= generic_key_instantiate,
	.describe		= fscrypt_provisioning_key_describe,
	.destroy		= fscrypt_provisioning_key_destroy,
पूर्ण;

/*
 * Retrieve the raw key from the Linux keyring key specअगरied by 'key_id', and
 * store it पूर्णांकo 'secret'.
 *
 * The key must be of type "fscrypt-provisioning" and must have the field
 * fscrypt_provisioning_key_payload::type set to 'type', indicating that it's
 * only usable with fscrypt with the particular KDF version identअगरied by
 * 'type'.  We don't use the "logon" key type because there's no way to
 * completely restrict the use of such keys; they can be used by any kernel API
 * that accepts "logon" keys and करोesn't require a specअगरic service prefix.
 *
 * The ability to specअगरy the key via Linux keyring key is पूर्णांकended क्रम हालs
 * where userspace needs to re-add keys after the fileप्रणाली is unmounted and
 * re-mounted.  Most users should just provide the raw key directly instead.
 */
अटल पूर्णांक get_keyring_key(u32 key_id, u32 type,
			   काष्ठा fscrypt_master_key_secret *secret)
अणु
	key_ref_t ref;
	काष्ठा key *key;
	स्थिर काष्ठा fscrypt_provisioning_key_payload *payload;
	पूर्णांक err;

	ref = lookup_user_key(key_id, 0, KEY_NEED_SEARCH);
	अगर (IS_ERR(ref))
		वापस PTR_ERR(ref);
	key = key_ref_to_ptr(ref);

	अगर (key->type != &key_type_fscrypt_provisioning)
		जाओ bad_key;
	payload = key->payload.data[0];

	/* Don't allow fscrypt v1 keys to be used as v2 keys and vice versa. */
	अगर (payload->type != type)
		जाओ bad_key;

	secret->size = key->datalen - माप(*payload);
	स_नकल(secret->raw, payload->raw, secret->size);
	err = 0;
	जाओ out_put;

bad_key:
	err = -EKEYREJECTED;
out_put:
	key_ref_put(ref);
	वापस err;
पूर्ण

/*
 * Add a master encryption key to the fileप्रणाली, causing all files which were
 * encrypted with it to appear "unlocked" (decrypted) when accessed.
 *
 * When adding a key क्रम use by v1 encryption policies, this ioctl is
 * privileged, and userspace must provide the 'key_descriptor'.
 *
 * When adding a key क्रम use by v2+ encryption policies, this ioctl is
 * unprivileged.  This is needed, in general, to allow non-root users to use
 * encryption without encountering the visibility problems of process-subscribed
 * keyrings and the inability to properly हटाओ keys.  This works by having
 * each key identअगरied by its cryptographically secure hash --- the
 * 'key_identifier'.  The cryptographic hash ensures that a malicious user
 * cannot add the wrong key क्रम a given identअगरier.  Furthermore, each added key
 * is अक्षरged to the appropriate user's quota क्रम the keyrings service, which
 * prevents a malicious user from adding too many keys.  Finally, we क्रमbid a
 * user from removing a key जबतक other users have added it too, which prevents
 * a user who knows another user's key from causing a denial-of-service by
 * removing it at an inopportune समय.  (We tolerate that a user who knows a key
 * can prevent other users from removing it.)
 *
 * For more details, see the "FS_IOC_ADD_ENCRYPTION_KEY" section of
 * Documentation/fileप्रणालीs/fscrypt.rst.
 */
पूर्णांक fscrypt_ioctl_add_key(काष्ठा file *filp, व्योम __user *_uarg)
अणु
	काष्ठा super_block *sb = file_inode(filp)->i_sb;
	काष्ठा fscrypt_add_key_arg __user *uarg = _uarg;
	काष्ठा fscrypt_add_key_arg arg;
	काष्ठा fscrypt_master_key_secret secret;
	पूर्णांक err;

	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	अगर (!valid_key_spec(&arg.key_spec))
		वापस -EINVAL;

	अगर (स_प्रथम_inv(arg.__reserved, 0, माप(arg.__reserved)))
		वापस -EINVAL;

	/*
	 * Only root can add keys that are identअगरied by an arbitrary descriptor
	 * rather than by a cryptographic hash --- since otherwise a malicious
	 * user could add the wrong key.
	 */
	अगर (arg.key_spec.type == FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR &&
	    !capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	स_रखो(&secret, 0, माप(secret));
	अगर (arg.key_id) अणु
		अगर (arg.raw_size != 0)
			वापस -EINVAL;
		err = get_keyring_key(arg.key_id, arg.key_spec.type, &secret);
		अगर (err)
			जाओ out_wipe_secret;
	पूर्ण अन्यथा अणु
		अगर (arg.raw_size < FSCRYPT_MIN_KEY_SIZE ||
		    arg.raw_size > FSCRYPT_MAX_KEY_SIZE)
			वापस -EINVAL;
		secret.size = arg.raw_size;
		err = -EFAULT;
		अगर (copy_from_user(secret.raw, uarg->raw, secret.size))
			जाओ out_wipe_secret;
	पूर्ण

	err = add_master_key(sb, &secret, &arg.key_spec);
	अगर (err)
		जाओ out_wipe_secret;

	/* Return the key identअगरier to userspace, अगर applicable */
	err = -EFAULT;
	अगर (arg.key_spec.type == FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER &&
	    copy_to_user(uarg->key_spec.u.identअगरier, arg.key_spec.u.identअगरier,
			 FSCRYPT_KEY_IDENTIFIER_SIZE))
		जाओ out_wipe_secret;
	err = 0;
out_wipe_secret:
	wipe_master_key_secret(&secret);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_ioctl_add_key);

/*
 * Add the key क्रम '-o test_dummy_encryption' to the fileप्रणाली keyring.
 *
 * Use a per-boot अक्रमom key to prevent people from misusing this option.
 */
पूर्णांक fscrypt_add_test_dummy_key(काष्ठा super_block *sb,
			       काष्ठा fscrypt_key_specअगरier *key_spec)
अणु
	अटल u8 test_key[FSCRYPT_MAX_KEY_SIZE];
	काष्ठा fscrypt_master_key_secret secret;
	पूर्णांक err;

	get_अक्रमom_once(test_key, FSCRYPT_MAX_KEY_SIZE);

	स_रखो(&secret, 0, माप(secret));
	secret.size = FSCRYPT_MAX_KEY_SIZE;
	स_नकल(secret.raw, test_key, FSCRYPT_MAX_KEY_SIZE);

	err = add_master_key(sb, &secret, key_spec);
	wipe_master_key_secret(&secret);
	वापस err;
पूर्ण

/*
 * Verअगरy that the current user has added a master key with the given identअगरier
 * (वापसs -ENOKEY अगर not).  This is needed to prevent a user from encrypting
 * their files using some other user's key which they don't actually know.
 * Cryptographically this isn't much of a problem, but the semantics of this
 * would be a bit weird, so it's best to just क्रमbid it.
 *
 * The प्रणाली administrator (CAP_FOWNER) can override this, which should be
 * enough क्रम any use हालs where encryption policies are being set using keys
 * that were chosen ahead of समय but aren't available at the moment.
 *
 * Note that the key may have alपढ़ोy हटाओd by the समय this वापसs, but
 * that's okay; we just care whether the key was there at some poपूर्णांक.
 *
 * Return: 0 अगर the key is added, -ENOKEY अगर it isn't, or another -त्रुटि_सं code
 */
पूर्णांक fscrypt_verअगरy_key_added(काष्ठा super_block *sb,
			     स्थिर u8 identअगरier[FSCRYPT_KEY_IDENTIFIER_SIZE])
अणु
	काष्ठा fscrypt_key_specअगरier mk_spec;
	काष्ठा key *key, *mk_user;
	काष्ठा fscrypt_master_key *mk;
	पूर्णांक err;

	mk_spec.type = FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER;
	स_नकल(mk_spec.u.identअगरier, identअगरier, FSCRYPT_KEY_IDENTIFIER_SIZE);

	key = fscrypt_find_master_key(sb, &mk_spec);
	अगर (IS_ERR(key)) अणु
		err = PTR_ERR(key);
		जाओ out;
	पूर्ण
	mk = key->payload.data[0];
	mk_user = find_master_key_user(mk);
	अगर (IS_ERR(mk_user)) अणु
		err = PTR_ERR(mk_user);
	पूर्ण अन्यथा अणु
		key_put(mk_user);
		err = 0;
	पूर्ण
	key_put(key);
out:
	अगर (err == -ENOKEY && capable(CAP_FOWNER))
		err = 0;
	वापस err;
पूर्ण

/*
 * Try to evict the inode's dentries from the dentry cache.  If the inode is a
 * directory, then it can have at most one dentry; however, that dentry may be
 * pinned by child dentries, so first try to evict the children too.
 */
अटल व्योम shrink_dcache_inode(काष्ठा inode *inode)
अणु
	काष्ठा dentry *dentry;

	अगर (S_ISसूची(inode->i_mode)) अणु
		dentry = d_find_any_alias(inode);
		अगर (dentry) अणु
			shrink_dcache_parent(dentry);
			dput(dentry);
		पूर्ण
	पूर्ण
	d_prune_aliases(inode);
पूर्ण

अटल व्योम evict_dentries_क्रम_decrypted_inodes(काष्ठा fscrypt_master_key *mk)
अणु
	काष्ठा fscrypt_info *ci;
	काष्ठा inode *inode;
	काष्ठा inode *toput_inode = शून्य;

	spin_lock(&mk->mk_decrypted_inodes_lock);

	list_क्रम_each_entry(ci, &mk->mk_decrypted_inodes, ci_master_key_link) अणु
		inode = ci->ci_inode;
		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_FREEING | I_WILL_FREE | I_NEW)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		__iget(inode);
		spin_unlock(&inode->i_lock);
		spin_unlock(&mk->mk_decrypted_inodes_lock);

		shrink_dcache_inode(inode);
		iput(toput_inode);
		toput_inode = inode;

		spin_lock(&mk->mk_decrypted_inodes_lock);
	पूर्ण

	spin_unlock(&mk->mk_decrypted_inodes_lock);
	iput(toput_inode);
पूर्ण

अटल पूर्णांक check_क्रम_busy_inodes(काष्ठा super_block *sb,
				 काष्ठा fscrypt_master_key *mk)
अणु
	काष्ठा list_head *pos;
	माप_प्रकार busy_count = 0;
	अचिन्हित दीर्घ ino;
	अक्षर ino_str[50] = "";

	spin_lock(&mk->mk_decrypted_inodes_lock);

	list_क्रम_each(pos, &mk->mk_decrypted_inodes)
		busy_count++;

	अगर (busy_count == 0) अणु
		spin_unlock(&mk->mk_decrypted_inodes_lock);
		वापस 0;
	पूर्ण

	अणु
		/* select an example file to show क्रम debugging purposes */
		काष्ठा inode *inode =
			list_first_entry(&mk->mk_decrypted_inodes,
					 काष्ठा fscrypt_info,
					 ci_master_key_link)->ci_inode;
		ino = inode->i_ino;
	पूर्ण
	spin_unlock(&mk->mk_decrypted_inodes_lock);

	/* If the inode is currently being created, ino may still be 0. */
	अगर (ino)
		snम_लिखो(ino_str, माप(ino_str), ", including ino %lu", ino);

	fscrypt_warn(शून्य,
		     "%s: %zu inode(s) still busy after removing key with %s %*phN%s",
		     sb->s_id, busy_count, master_key_spec_type(&mk->mk_spec),
		     master_key_spec_len(&mk->mk_spec), (u8 *)&mk->mk_spec.u,
		     ino_str);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक try_to_lock_encrypted_files(काष्ठा super_block *sb,
				       काष्ठा fscrypt_master_key *mk)
अणु
	पूर्णांक err1;
	पूर्णांक err2;

	/*
	 * An inode can't be evicted जबतक it is dirty or has dirty pages.
	 * Thus, we first have to clean the inodes in ->mk_decrypted_inodes.
	 *
	 * Just करो it the easy way: call sync_fileप्रणाली().  It's overसमाप्त, but
	 * it works, and it's more important to minimize the amount of caches we
	 * drop than the amount of data we sync.  Also, unprivileged users can
	 * alपढ़ोy call sync_fileप्रणाली() via sys_syncfs() or sys_sync().
	 */
	करोwn_पढ़ो(&sb->s_umount);
	err1 = sync_fileप्रणाली(sb);
	up_पढ़ो(&sb->s_umount);
	/* If a sync error occurs, still try to evict as much as possible. */

	/*
	 * Inodes are pinned by their dentries, so we have to evict their
	 * dentries.  shrink_dcache_sb() would suffice, but would be overसमाप्त
	 * and inappropriate क्रम use by unprivileged users.  So instead go
	 * through the inodes' alias lists and try to evict each dentry.
	 */
	evict_dentries_क्रम_decrypted_inodes(mk);

	/*
	 * evict_dentries_क्रम_decrypted_inodes() alपढ़ोy iput() each inode in
	 * the list; any inodes क्रम which that dropped the last reference will
	 * have been evicted due to fscrypt_drop_inode() detecting the key
	 * removal and telling the VFS to evict the inode.  So to finish, we
	 * just need to check whether any inodes couldn't be evicted.
	 */
	err2 = check_क्रम_busy_inodes(sb, mk);

	वापस err1 ?: err2;
पूर्ण

/*
 * Try to हटाओ an fscrypt master encryption key.
 *
 * FS_IOC_REMOVE_ENCRYPTION_KEY (all_users=false) हटाओs the current user's
 * claim to the key, then हटाओs the key itself अगर no other users have claims.
 * FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS (all_users=true) always हटाओs the
 * key itself.
 *
 * To "remove the key itself", first we wipe the actual master key secret, so
 * that no more inodes can be unlocked with it.  Then we try to evict all cached
 * inodes that had been unlocked with the key.
 *
 * If all inodes were evicted, then we unlink the fscrypt_master_key from the
 * keyring.  Otherwise it reमुख्यs in the keyring in the "incompletely removed"
 * state (without the actual secret key) where it tracks the list of reमुख्यing
 * inodes.  Userspace can execute the ioctl again later to retry eviction, or
 * alternatively can re-add the secret key again.
 *
 * For more details, see the "Removing keys" section of
 * Documentation/fileप्रणालीs/fscrypt.rst.
 */
अटल पूर्णांक करो_हटाओ_key(काष्ठा file *filp, व्योम __user *_uarg, bool all_users)
अणु
	काष्ठा super_block *sb = file_inode(filp)->i_sb;
	काष्ठा fscrypt_हटाओ_key_arg __user *uarg = _uarg;
	काष्ठा fscrypt_हटाओ_key_arg arg;
	काष्ठा key *key;
	काष्ठा fscrypt_master_key *mk;
	u32 status_flags = 0;
	पूर्णांक err;
	bool dead;

	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	अगर (!valid_key_spec(&arg.key_spec))
		वापस -EINVAL;

	अगर (स_प्रथम_inv(arg.__reserved, 0, माप(arg.__reserved)))
		वापस -EINVAL;

	/*
	 * Only root can add and हटाओ keys that are identअगरied by an arbitrary
	 * descriptor rather than by a cryptographic hash.
	 */
	अगर (arg.key_spec.type == FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR &&
	    !capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	/* Find the key being हटाओd. */
	key = fscrypt_find_master_key(sb, &arg.key_spec);
	अगर (IS_ERR(key))
		वापस PTR_ERR(key);
	mk = key->payload.data[0];

	करोwn_ग_लिखो(&key->sem);

	/* If relevant, हटाओ current user's (or all users) claim to the key */
	अगर (mk->mk_users && mk->mk_users->keys.nr_leaves_on_tree != 0) अणु
		अगर (all_users)
			err = keyring_clear(mk->mk_users);
		अन्यथा
			err = हटाओ_master_key_user(mk);
		अगर (err) अणु
			up_ग_लिखो(&key->sem);
			जाओ out_put_key;
		पूर्ण
		अगर (mk->mk_users->keys.nr_leaves_on_tree != 0) अणु
			/*
			 * Other users have still added the key too.  We हटाओd
			 * the current user's claim to the key, but we still
			 * can't हटाओ the key itself.
			 */
			status_flags |=
				FSCRYPT_KEY_REMOVAL_STATUS_FLAG_OTHER_USERS;
			err = 0;
			up_ग_लिखो(&key->sem);
			जाओ out_put_key;
		पूर्ण
	पूर्ण

	/* No user claims reमुख्यing.  Go ahead and wipe the secret. */
	dead = false;
	अगर (is_master_key_secret_present(&mk->mk_secret)) अणु
		wipe_master_key_secret(&mk->mk_secret);
		dead = refcount_dec_and_test(&mk->mk_refcount);
	पूर्ण
	up_ग_लिखो(&key->sem);
	अगर (dead) अणु
		/*
		 * No inodes reference the key, and we wiped the secret, so the
		 * key object is मुक्त to be हटाओd from the keyring.
		 */
		key_invalidate(key);
		err = 0;
	पूर्ण अन्यथा अणु
		/* Some inodes still reference this key; try to evict them. */
		err = try_to_lock_encrypted_files(sb, mk);
		अगर (err == -EBUSY) अणु
			status_flags |=
				FSCRYPT_KEY_REMOVAL_STATUS_FLAG_खाताS_BUSY;
			err = 0;
		पूर्ण
	पूर्ण
	/*
	 * We वापस 0 अगर we successfully did something: हटाओd a claim to the
	 * key, wiped the secret, or tried locking the files again.  Users need
	 * to check the inक्रमmational status flags अगर they care whether the key
	 * has been fully हटाओd including all files locked.
	 */
out_put_key:
	key_put(key);
	अगर (err == 0)
		err = put_user(status_flags, &uarg->removal_status_flags);
	वापस err;
पूर्ण

पूर्णांक fscrypt_ioctl_हटाओ_key(काष्ठा file *filp, व्योम __user *uarg)
अणु
	वापस करो_हटाओ_key(filp, uarg, false);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_ioctl_हटाओ_key);

पूर्णांक fscrypt_ioctl_हटाओ_key_all_users(काष्ठा file *filp, व्योम __user *uarg)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	वापस करो_हटाओ_key(filp, uarg, true);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_ioctl_हटाओ_key_all_users);

/*
 * Retrieve the status of an fscrypt master encryption key.
 *
 * We set ->status to indicate whether the key is असलent, present, or
 * incompletely हटाओd.  "Incompletely removed" means that the master key
 * secret has been हटाओd, but some files which had been unlocked with it are
 * still in use.  This field allows applications to easily determine the state
 * of an encrypted directory without using a hack such as trying to खोलो a
 * regular file in it (which can confuse the "incompletely removed" state with
 * असलent or present).
 *
 * In addition, क्रम v2 policy keys we allow applications to determine, via
 * ->status_flags and ->user_count, whether the key has been added by the
 * current user, by other users, or by both.  Most applications should not need
 * this, since ordinarily only one user should know a given key.  However, अगर a
 * secret key is shared by multiple users, applications may wish to add an
 * alपढ़ोy-present key to prevent other users from removing it.  This ioctl can
 * be used to check whether that really is the हाल beक्रमe the work is करोne to
 * add the key --- which might e.g. require prompting the user क्रम a passphrase.
 *
 * For more details, see the "FS_IOC_GET_ENCRYPTION_KEY_STATUS" section of
 * Documentation/fileप्रणालीs/fscrypt.rst.
 */
पूर्णांक fscrypt_ioctl_get_key_status(काष्ठा file *filp, व्योम __user *uarg)
अणु
	काष्ठा super_block *sb = file_inode(filp)->i_sb;
	काष्ठा fscrypt_get_key_status_arg arg;
	काष्ठा key *key;
	काष्ठा fscrypt_master_key *mk;
	पूर्णांक err;

	अगर (copy_from_user(&arg, uarg, माप(arg)))
		वापस -EFAULT;

	अगर (!valid_key_spec(&arg.key_spec))
		वापस -EINVAL;

	अगर (स_प्रथम_inv(arg.__reserved, 0, माप(arg.__reserved)))
		वापस -EINVAL;

	arg.status_flags = 0;
	arg.user_count = 0;
	स_रखो(arg.__out_reserved, 0, माप(arg.__out_reserved));

	key = fscrypt_find_master_key(sb, &arg.key_spec);
	अगर (IS_ERR(key)) अणु
		अगर (key != ERR_PTR(-ENOKEY))
			वापस PTR_ERR(key);
		arg.status = FSCRYPT_KEY_STATUS_ABSENT;
		err = 0;
		जाओ out;
	पूर्ण
	mk = key->payload.data[0];
	करोwn_पढ़ो(&key->sem);

	अगर (!is_master_key_secret_present(&mk->mk_secret)) अणु
		arg.status = FSCRYPT_KEY_STATUS_INCOMPLETELY_REMOVED;
		err = 0;
		जाओ out_release_key;
	पूर्ण

	arg.status = FSCRYPT_KEY_STATUS_PRESENT;
	अगर (mk->mk_users) अणु
		काष्ठा key *mk_user;

		arg.user_count = mk->mk_users->keys.nr_leaves_on_tree;
		mk_user = find_master_key_user(mk);
		अगर (!IS_ERR(mk_user)) अणु
			arg.status_flags |=
				FSCRYPT_KEY_STATUS_FLAG_ADDED_BY_SELF;
			key_put(mk_user);
		पूर्ण अन्यथा अगर (mk_user != ERR_PTR(-ENOKEY)) अणु
			err = PTR_ERR(mk_user);
			जाओ out_release_key;
		पूर्ण
	पूर्ण
	err = 0;
out_release_key:
	up_पढ़ो(&key->sem);
	key_put(key);
out:
	अगर (!err && copy_to_user(uarg, &arg, माप(arg)))
		err = -EFAULT;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_ioctl_get_key_status);

पूर्णांक __init fscrypt_init_keyring(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_key_type(&key_type_fscrypt);
	अगर (err)
		वापस err;

	err = रेजिस्टर_key_type(&key_type_fscrypt_user);
	अगर (err)
		जाओ err_unरेजिस्टर_fscrypt;

	err = रेजिस्टर_key_type(&key_type_fscrypt_provisioning);
	अगर (err)
		जाओ err_unरेजिस्टर_fscrypt_user;

	वापस 0;

err_unरेजिस्टर_fscrypt_user:
	unरेजिस्टर_key_type(&key_type_fscrypt_user);
err_unरेजिस्टर_fscrypt:
	unरेजिस्टर_key_type(&key_type_fscrypt);
	वापस err;
पूर्ण
