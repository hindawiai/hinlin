<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Userspace key control operations
 *
 * Copyright (C) 2004-5 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/key.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/fs.h>
#समावेश <linux/capability.h>
#समावेश <linux/cred.h>
#समावेश <linux/माला.स>
#समावेश <linux/err.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/security.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>
#समावेश <keys/request_key_auth-type.h>
#समावेश "internal.h"

#घोषणा KEY_MAX_DESC_SIZE 4096

अटल स्थिर अचिन्हित अक्षर keyrings_capabilities[2] = अणु
	[0] = (KEYCTL_CAPS0_CAPABILITIES |
	       (IS_ENABLED(CONFIG_PERSISTENT_KEYRINGS)	? KEYCTL_CAPS0_PERSISTENT_KEYRINGS : 0) |
	       (IS_ENABLED(CONFIG_KEY_DH_OPERATIONS)	? KEYCTL_CAPS0_DIFFIE_HELLMAN : 0) |
	       (IS_ENABLED(CONFIG_ASYMMETRIC_KEY_TYPE)	? KEYCTL_CAPS0_PUBLIC_KEY : 0) |
	       (IS_ENABLED(CONFIG_BIG_KEYS)		? KEYCTL_CAPS0_BIG_KEY : 0) |
	       KEYCTL_CAPS0_INVALIDATE |
	       KEYCTL_CAPS0_RESTRICT_KEYRING |
	       KEYCTL_CAPS0_MOVE
	       ),
	[1] = (KEYCTL_CAPS1_NS_KEYRING_NAME |
	       KEYCTL_CAPS1_NS_KEY_TAG |
	       (IS_ENABLED(CONFIG_KEY_NOTIFICATIONS)	? KEYCTL_CAPS1_NOTIFICATIONS : 0)
	       ),
पूर्ण;

अटल पूर्णांक key_get_type_from_user(अक्षर *type,
				  स्थिर अक्षर __user *_type,
				  अचिन्हित len)
अणु
	पूर्णांक ret;

	ret = म_नकलन_from_user(type, _type, len);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0 || ret >= len)
		वापस -EINVAL;
	अगर (type[0] == '.')
		वापस -EPERM;
	type[len - 1] = '\0';
	वापस 0;
पूर्ण

/*
 * Extract the description of a new key from userspace and either add it as a
 * new key to the specअगरied keyring or update a matching key in that keyring.
 *
 * If the description is शून्य or an empty string, the key type is asked to
 * generate one from the payload.
 *
 * The keyring must be writable so that we can attach the key to it.
 *
 * If successful, the new key's serial number is वापसed, otherwise an error
 * code is वापसed.
 */
SYSCALL_DEFINE5(add_key, स्थिर अक्षर __user *, _type,
		स्थिर अक्षर __user *, _description,
		स्थिर व्योम __user *, _payload,
		माप_प्रकार, plen,
		key_serial_t, ringid)
अणु
	key_ref_t keyring_ref, key_ref;
	अक्षर type[32], *description;
	व्योम *payload;
	दीर्घ ret;

	ret = -EINVAL;
	अगर (plen > 1024 * 1024 - 1)
		जाओ error;

	/* draw all the data पूर्णांकo kernel space */
	ret = key_get_type_from_user(type, _type, माप(type));
	अगर (ret < 0)
		जाओ error;

	description = शून्य;
	अगर (_description) अणु
		description = strndup_user(_description, KEY_MAX_DESC_SIZE);
		अगर (IS_ERR(description)) अणु
			ret = PTR_ERR(description);
			जाओ error;
		पूर्ण
		अगर (!*description) अणु
			kमुक्त(description);
			description = शून्य;
		पूर्ण अन्यथा अगर ((description[0] == '.') &&
			   (म_भेदन(type, "keyring", 7) == 0)) अणु
			ret = -EPERM;
			जाओ error2;
		पूर्ण
	पूर्ण

	/* pull the payload in अगर one was supplied */
	payload = शून्य;

	अगर (plen) अणु
		ret = -ENOMEM;
		payload = kvदो_स्मृति(plen, GFP_KERNEL);
		अगर (!payload)
			जाओ error2;

		ret = -EFAULT;
		अगर (copy_from_user(payload, _payload, plen) != 0)
			जाओ error3;
	पूर्ण

	/* find the target keyring (which must be writable) */
	keyring_ref = lookup_user_key(ringid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
	अगर (IS_ERR(keyring_ref)) अणु
		ret = PTR_ERR(keyring_ref);
		जाओ error3;
	पूर्ण

	/* create or update the requested key and add it to the target
	 * keyring */
	key_ref = key_create_or_update(keyring_ref, type, description,
				       payload, plen, KEY_PERM_UNDEF,
				       KEY_ALLOC_IN_QUOTA);
	अगर (!IS_ERR(key_ref)) अणु
		ret = key_ref_to_ptr(key_ref)->serial;
		key_ref_put(key_ref);
	पूर्ण
	अन्यथा अणु
		ret = PTR_ERR(key_ref);
	पूर्ण

	key_ref_put(keyring_ref);
 error3:
	kvमुक्त_sensitive(payload, plen);
 error2:
	kमुक्त(description);
 error:
	वापस ret;
पूर्ण

/*
 * Search the process keyrings and keyring trees linked from those क्रम a
 * matching key.  Keyrings must have appropriate Search permission to be
 * searched.
 *
 * If a key is found, it will be attached to the destination keyring अगर there's
 * one specअगरied and the serial number of the key will be वापसed.
 *
 * If no key is found, /sbin/request-key will be invoked अगर _callout_info is
 * non-शून्य in an attempt to create a key.  The _callout_info string will be
 * passed to /sbin/request-key to aid with completing the request.  If the
 * _callout_info string is "" then it will be changed to "-".
 */
SYSCALL_DEFINE4(request_key, स्थिर अक्षर __user *, _type,
		स्थिर अक्षर __user *, _description,
		स्थिर अक्षर __user *, _callout_info,
		key_serial_t, destringid)
अणु
	काष्ठा key_type *ktype;
	काष्ठा key *key;
	key_ref_t dest_ref;
	माप_प्रकार callout_len;
	अक्षर type[32], *description, *callout_info;
	दीर्घ ret;

	/* pull the type पूर्णांकo kernel space */
	ret = key_get_type_from_user(type, _type, माप(type));
	अगर (ret < 0)
		जाओ error;

	/* pull the description पूर्णांकo kernel space */
	description = strndup_user(_description, KEY_MAX_DESC_SIZE);
	अगर (IS_ERR(description)) अणु
		ret = PTR_ERR(description);
		जाओ error;
	पूर्ण

	/* pull the callout info पूर्णांकo kernel space */
	callout_info = शून्य;
	callout_len = 0;
	अगर (_callout_info) अणु
		callout_info = strndup_user(_callout_info, PAGE_SIZE);
		अगर (IS_ERR(callout_info)) अणु
			ret = PTR_ERR(callout_info);
			जाओ error2;
		पूर्ण
		callout_len = म_माप(callout_info);
	पूर्ण

	/* get the destination keyring अगर specअगरied */
	dest_ref = शून्य;
	अगर (destringid) अणु
		dest_ref = lookup_user_key(destringid, KEY_LOOKUP_CREATE,
					   KEY_NEED_WRITE);
		अगर (IS_ERR(dest_ref)) अणु
			ret = PTR_ERR(dest_ref);
			जाओ error3;
		पूर्ण
	पूर्ण

	/* find the key type */
	ktype = key_type_lookup(type);
	अगर (IS_ERR(ktype)) अणु
		ret = PTR_ERR(ktype);
		जाओ error4;
	पूर्ण

	/* करो the search */
	key = request_key_and_link(ktype, description, शून्य, callout_info,
				   callout_len, शून्य, key_ref_to_ptr(dest_ref),
				   KEY_ALLOC_IN_QUOTA);
	अगर (IS_ERR(key)) अणु
		ret = PTR_ERR(key);
		जाओ error5;
	पूर्ण

	/* रुको क्रम the key to finish being स्थिरructed */
	ret = रुको_क्रम_key_स्थिरruction(key, 1);
	अगर (ret < 0)
		जाओ error6;

	ret = key->serial;

error6:
 	key_put(key);
error5:
	key_type_put(ktype);
error4:
	key_ref_put(dest_ref);
error3:
	kमुक्त(callout_info);
error2:
	kमुक्त(description);
error:
	वापस ret;
पूर्ण

/*
 * Get the ID of the specअगरied process keyring.
 *
 * The requested keyring must have search permission to be found.
 *
 * If successful, the ID of the requested keyring will be वापसed.
 */
दीर्घ keyctl_get_keyring_ID(key_serial_t id, पूर्णांक create)
अणु
	key_ref_t key_ref;
	अचिन्हित दीर्घ lflags;
	दीर्घ ret;

	lflags = create ? KEY_LOOKUP_CREATE : 0;
	key_ref = lookup_user_key(id, lflags, KEY_NEED_SEARCH);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);
		जाओ error;
	पूर्ण

	ret = key_ref_to_ptr(key_ref)->serial;
	key_ref_put(key_ref);
error:
	वापस ret;
पूर्ण

/*
 * Join a (named) session keyring.
 *
 * Create and join an anonymous session keyring or join a named session
 * keyring, creating it अगर necessary.  A named session keyring must have Search
 * permission क्रम it to be joined.  Session keyrings without this permit will
 * be skipped over.  It is not permitted क्रम userspace to create or join
 * keyrings whose name begin with a करोt.
 *
 * If successful, the ID of the joined session keyring will be वापसed.
 */
दीर्घ keyctl_join_session_keyring(स्थिर अक्षर __user *_name)
अणु
	अक्षर *name;
	दीर्घ ret;

	/* fetch the name from userspace */
	name = शून्य;
	अगर (_name) अणु
		name = strndup_user(_name, KEY_MAX_DESC_SIZE);
		अगर (IS_ERR(name)) अणु
			ret = PTR_ERR(name);
			जाओ error;
		पूर्ण

		ret = -EPERM;
		अगर (name[0] == '.')
			जाओ error_name;
	पूर्ण

	/* join the session */
	ret = join_session_keyring(name);
error_name:
	kमुक्त(name);
error:
	वापस ret;
पूर्ण

/*
 * Update a key's data payload from the given data.
 *
 * The key must grant the caller Write permission and the key type must support
 * updating क्रम this to work.  A negative key can be positively instantiated
 * with this call.
 *
 * If successful, 0 will be वापसed.  If the key type करोes not support
 * updating, then -EOPNOTSUPP will be वापसed.
 */
दीर्घ keyctl_update_key(key_serial_t id,
		       स्थिर व्योम __user *_payload,
		       माप_प्रकार plen)
अणु
	key_ref_t key_ref;
	व्योम *payload;
	दीर्घ ret;

	ret = -EINVAL;
	अगर (plen > PAGE_SIZE)
		जाओ error;

	/* pull the payload in अगर one was supplied */
	payload = शून्य;
	अगर (plen) अणु
		ret = -ENOMEM;
		payload = kvदो_स्मृति(plen, GFP_KERNEL);
		अगर (!payload)
			जाओ error;

		ret = -EFAULT;
		अगर (copy_from_user(payload, _payload, plen) != 0)
			जाओ error2;
	पूर्ण

	/* find the target key (which must be writable) */
	key_ref = lookup_user_key(id, 0, KEY_NEED_WRITE);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);
		जाओ error2;
	पूर्ण

	/* update the key */
	ret = key_update(key_ref, payload, plen);

	key_ref_put(key_ref);
error2:
	kvमुक्त_sensitive(payload, plen);
error:
	वापस ret;
पूर्ण

/*
 * Revoke a key.
 *
 * The key must be grant the caller Write or Setattr permission क्रम this to
 * work.  The key type should give up its quota claim when revoked.  The key
 * and any links to the key will be स्वतःmatically garbage collected after a
 * certain amount of समय (/proc/sys/kernel/keys/gc_delay).
 *
 * Keys with KEY_FLAG_KEEP set should not be revoked.
 *
 * If successful, 0 is वापसed.
 */
दीर्घ keyctl_revoke_key(key_serial_t id)
अणु
	key_ref_t key_ref;
	काष्ठा key *key;
	दीर्घ ret;

	key_ref = lookup_user_key(id, 0, KEY_NEED_WRITE);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);
		अगर (ret != -EACCES)
			जाओ error;
		key_ref = lookup_user_key(id, 0, KEY_NEED_SETATTR);
		अगर (IS_ERR(key_ref)) अणु
			ret = PTR_ERR(key_ref);
			जाओ error;
		पूर्ण
	पूर्ण

	key = key_ref_to_ptr(key_ref);
	ret = 0;
	अगर (test_bit(KEY_FLAG_KEEP, &key->flags))
		ret = -EPERM;
	अन्यथा
		key_revoke(key);

	key_ref_put(key_ref);
error:
	वापस ret;
पूर्ण

/*
 * Invalidate a key.
 *
 * The key must be grant the caller Invalidate permission क्रम this to work.
 * The key and any links to the key will be स्वतःmatically garbage collected
 * immediately.
 *
 * Keys with KEY_FLAG_KEEP set should not be invalidated.
 *
 * If successful, 0 is वापसed.
 */
दीर्घ keyctl_invalidate_key(key_serial_t id)
अणु
	key_ref_t key_ref;
	काष्ठा key *key;
	दीर्घ ret;

	kenter("%d", id);

	key_ref = lookup_user_key(id, 0, KEY_NEED_SEARCH);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);

		/* Root is permitted to invalidate certain special keys */
		अगर (capable(CAP_SYS_ADMIN)) अणु
			key_ref = lookup_user_key(id, 0, KEY_SYSADMIN_OVERRIDE);
			अगर (IS_ERR(key_ref))
				जाओ error;
			अगर (test_bit(KEY_FLAG_ROOT_CAN_INVAL,
				     &key_ref_to_ptr(key_ref)->flags))
				जाओ invalidate;
			जाओ error_put;
		पूर्ण

		जाओ error;
	पूर्ण

invalidate:
	key = key_ref_to_ptr(key_ref);
	ret = 0;
	अगर (test_bit(KEY_FLAG_KEEP, &key->flags))
		ret = -EPERM;
	अन्यथा
		key_invalidate(key);
error_put:
	key_ref_put(key_ref);
error:
	kleave(" = %ld", ret);
	वापस ret;
पूर्ण

/*
 * Clear the specअगरied keyring, creating an empty process keyring अगर one of the
 * special keyring IDs is used.
 *
 * The keyring must grant the caller Write permission and not have
 * KEY_FLAG_KEEP set क्रम this to work.  If successful, 0 will be वापसed.
 */
दीर्घ keyctl_keyring_clear(key_serial_t ringid)
अणु
	key_ref_t keyring_ref;
	काष्ठा key *keyring;
	दीर्घ ret;

	keyring_ref = lookup_user_key(ringid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
	अगर (IS_ERR(keyring_ref)) अणु
		ret = PTR_ERR(keyring_ref);

		/* Root is permitted to invalidate certain special keyrings */
		अगर (capable(CAP_SYS_ADMIN)) अणु
			keyring_ref = lookup_user_key(ringid, 0,
						      KEY_SYSADMIN_OVERRIDE);
			अगर (IS_ERR(keyring_ref))
				जाओ error;
			अगर (test_bit(KEY_FLAG_ROOT_CAN_CLEAR,
				     &key_ref_to_ptr(keyring_ref)->flags))
				जाओ clear;
			जाओ error_put;
		पूर्ण

		जाओ error;
	पूर्ण

clear:
	keyring = key_ref_to_ptr(keyring_ref);
	अगर (test_bit(KEY_FLAG_KEEP, &keyring->flags))
		ret = -EPERM;
	अन्यथा
		ret = keyring_clear(keyring);
error_put:
	key_ref_put(keyring_ref);
error:
	वापस ret;
पूर्ण

/*
 * Create a link from a keyring to a key अगर there's no matching key in the
 * keyring, otherwise replace the link to the matching key with a link to the
 * new key.
 *
 * The key must grant the caller Link permission and the keyring must grant
 * the caller Write permission.  Furthermore, अगर an additional link is created,
 * the keyring's quota will be extended.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_keyring_link(key_serial_t id, key_serial_t ringid)
अणु
	key_ref_t keyring_ref, key_ref;
	दीर्घ ret;

	keyring_ref = lookup_user_key(ringid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
	अगर (IS_ERR(keyring_ref)) अणु
		ret = PTR_ERR(keyring_ref);
		जाओ error;
	पूर्ण

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE, KEY_NEED_LINK);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);
		जाओ error2;
	पूर्ण

	ret = key_link(key_ref_to_ptr(keyring_ref), key_ref_to_ptr(key_ref));

	key_ref_put(key_ref);
error2:
	key_ref_put(keyring_ref);
error:
	वापस ret;
पूर्ण

/*
 * Unlink a key from a keyring.
 *
 * The keyring must grant the caller Write permission क्रम this to work; the key
 * itself need not grant the caller anything.  If the last link to a key is
 * हटाओd then that key will be scheduled क्रम deकाष्ठाion.
 *
 * Keys or keyrings with KEY_FLAG_KEEP set should not be unlinked.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_keyring_unlink(key_serial_t id, key_serial_t ringid)
अणु
	key_ref_t keyring_ref, key_ref;
	काष्ठा key *keyring, *key;
	दीर्घ ret;

	keyring_ref = lookup_user_key(ringid, 0, KEY_NEED_WRITE);
	अगर (IS_ERR(keyring_ref)) अणु
		ret = PTR_ERR(keyring_ref);
		जाओ error;
	पूर्ण

	key_ref = lookup_user_key(id, KEY_LOOKUP_PARTIAL, KEY_NEED_UNLINK);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);
		जाओ error2;
	पूर्ण

	keyring = key_ref_to_ptr(keyring_ref);
	key = key_ref_to_ptr(key_ref);
	अगर (test_bit(KEY_FLAG_KEEP, &keyring->flags) &&
	    test_bit(KEY_FLAG_KEEP, &key->flags))
		ret = -EPERM;
	अन्यथा
		ret = key_unlink(keyring, key);

	key_ref_put(key_ref);
error2:
	key_ref_put(keyring_ref);
error:
	वापस ret;
पूर्ण

/*
 * Move a link to a key from one keyring to another, displacing any matching
 * key from the destination keyring.
 *
 * The key must grant the caller Link permission and both keyrings must grant
 * the caller Write permission.  There must also be a link in the from keyring
 * to the key.  If both keyrings are the same, nothing is करोne.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_keyring_move(key_serial_t id, key_serial_t from_ringid,
			 key_serial_t to_ringid, अचिन्हित पूर्णांक flags)
अणु
	key_ref_t key_ref, from_ref, to_ref;
	दीर्घ ret;

	अगर (flags & ~KEYCTL_MOVE_EXCL)
		वापस -EINVAL;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE, KEY_NEED_LINK);
	अगर (IS_ERR(key_ref))
		वापस PTR_ERR(key_ref);

	from_ref = lookup_user_key(from_ringid, 0, KEY_NEED_WRITE);
	अगर (IS_ERR(from_ref)) अणु
		ret = PTR_ERR(from_ref);
		जाओ error2;
	पूर्ण

	to_ref = lookup_user_key(to_ringid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
	अगर (IS_ERR(to_ref)) अणु
		ret = PTR_ERR(to_ref);
		जाओ error3;
	पूर्ण

	ret = key_move(key_ref_to_ptr(key_ref), key_ref_to_ptr(from_ref),
		       key_ref_to_ptr(to_ref), flags);

	key_ref_put(to_ref);
error3:
	key_ref_put(from_ref);
error2:
	key_ref_put(key_ref);
	वापस ret;
पूर्ण

/*
 * Return a description of a key to userspace.
 *
 * The key must grant the caller View permission क्रम this to work.
 *
 * If there's a buffer, we place up to buflen bytes of data पूर्णांकo it क्रमmatted
 * in the following way:
 *
 *	type;uid;gid;perm;description<NUL>
 *
 * If successful, we वापस the amount of description available, irrespective
 * of how much we may have copied पूर्णांकo the buffer.
 */
दीर्घ keyctl_describe_key(key_serial_t keyid,
			 अक्षर __user *buffer,
			 माप_प्रकार buflen)
अणु
	काष्ठा key *key, *instkey;
	key_ref_t key_ref;
	अक्षर *infobuf;
	दीर्घ ret;
	पूर्णांक desclen, infolen;

	key_ref = lookup_user_key(keyid, KEY_LOOKUP_PARTIAL, KEY_NEED_VIEW);
	अगर (IS_ERR(key_ref)) अणु
		/* viewing a key under स्थिरruction is permitted अगर we have the
		 * authorisation token handy */
		अगर (PTR_ERR(key_ref) == -EACCES) अणु
			instkey = key_get_instantiation_authkey(keyid);
			अगर (!IS_ERR(instkey)) अणु
				key_put(instkey);
				key_ref = lookup_user_key(keyid,
							  KEY_LOOKUP_PARTIAL,
							  KEY_AUTHTOKEN_OVERRIDE);
				अगर (!IS_ERR(key_ref))
					जाओ okay;
			पूर्ण
		पूर्ण

		ret = PTR_ERR(key_ref);
		जाओ error;
	पूर्ण

okay:
	key = key_ref_to_ptr(key_ref);
	desclen = म_माप(key->description);

	/* calculate how much inक्रमmation we're going to वापस */
	ret = -ENOMEM;
	infobuf = kaप्र_लिखो(GFP_KERNEL,
			    "%s;%d;%d;%08x;",
			    key->type->name,
			    from_kuid_munged(current_user_ns(), key->uid),
			    from_kgid_munged(current_user_ns(), key->gid),
			    key->perm);
	अगर (!infobuf)
		जाओ error2;
	infolen = म_माप(infobuf);
	ret = infolen + desclen + 1;

	/* consider वापसing the data */
	अगर (buffer && buflen >= ret) अणु
		अगर (copy_to_user(buffer, infobuf, infolen) != 0 ||
		    copy_to_user(buffer + infolen, key->description,
				 desclen + 1) != 0)
			ret = -EFAULT;
	पूर्ण

	kमुक्त(infobuf);
error2:
	key_ref_put(key_ref);
error:
	वापस ret;
पूर्ण

/*
 * Search the specअगरied keyring and any keyrings it links to क्रम a matching
 * key.  Only keyrings that grant the caller Search permission will be searched
 * (this includes the starting keyring).  Only keys with Search permission can
 * be found.
 *
 * If successful, the found key will be linked to the destination keyring अगर
 * supplied and the key has Link permission, and the found key ID will be
 * वापसed.
 */
दीर्घ keyctl_keyring_search(key_serial_t ringid,
			   स्थिर अक्षर __user *_type,
			   स्थिर अक्षर __user *_description,
			   key_serial_t destringid)
अणु
	काष्ठा key_type *ktype;
	key_ref_t keyring_ref, key_ref, dest_ref;
	अक्षर type[32], *description;
	दीर्घ ret;

	/* pull the type and description पूर्णांकo kernel space */
	ret = key_get_type_from_user(type, _type, माप(type));
	अगर (ret < 0)
		जाओ error;

	description = strndup_user(_description, KEY_MAX_DESC_SIZE);
	अगर (IS_ERR(description)) अणु
		ret = PTR_ERR(description);
		जाओ error;
	पूर्ण

	/* get the keyring at which to begin the search */
	keyring_ref = lookup_user_key(ringid, 0, KEY_NEED_SEARCH);
	अगर (IS_ERR(keyring_ref)) अणु
		ret = PTR_ERR(keyring_ref);
		जाओ error2;
	पूर्ण

	/* get the destination keyring अगर specअगरied */
	dest_ref = शून्य;
	अगर (destringid) अणु
		dest_ref = lookup_user_key(destringid, KEY_LOOKUP_CREATE,
					   KEY_NEED_WRITE);
		अगर (IS_ERR(dest_ref)) अणु
			ret = PTR_ERR(dest_ref);
			जाओ error3;
		पूर्ण
	पूर्ण

	/* find the key type */
	ktype = key_type_lookup(type);
	अगर (IS_ERR(ktype)) अणु
		ret = PTR_ERR(ktype);
		जाओ error4;
	पूर्ण

	/* करो the search */
	key_ref = keyring_search(keyring_ref, ktype, description, true);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);

		/* treat lack or presence of a negative key the same */
		अगर (ret == -EAGAIN)
			ret = -ENOKEY;
		जाओ error5;
	पूर्ण

	/* link the resulting key to the destination keyring अगर we can */
	अगर (dest_ref) अणु
		ret = key_permission(key_ref, KEY_NEED_LINK);
		अगर (ret < 0)
			जाओ error6;

		ret = key_link(key_ref_to_ptr(dest_ref), key_ref_to_ptr(key_ref));
		अगर (ret < 0)
			जाओ error6;
	पूर्ण

	ret = key_ref_to_ptr(key_ref)->serial;

error6:
	key_ref_put(key_ref);
error5:
	key_type_put(ktype);
error4:
	key_ref_put(dest_ref);
error3:
	key_ref_put(keyring_ref);
error2:
	kमुक्त(description);
error:
	वापस ret;
पूर्ण

/*
 * Call the पढ़ो method
 */
अटल दीर्घ __keyctl_पढ़ो_key(काष्ठा key *key, अक्षर *buffer, माप_प्रकार buflen)
अणु
	दीर्घ ret;

	करोwn_पढ़ो(&key->sem);
	ret = key_validate(key);
	अगर (ret == 0)
		ret = key->type->पढ़ो(key, buffer, buflen);
	up_पढ़ो(&key->sem);
	वापस ret;
पूर्ण

/*
 * Read a key's payload.
 *
 * The key must either grant the caller Read permission, or it must grant the
 * caller Search permission when searched क्रम from the process keyrings.
 *
 * If successful, we place up to buflen bytes of data पूर्णांकo the buffer, अगर one
 * is provided, and वापस the amount of data that is available in the key,
 * irrespective of how much we copied पूर्णांकo the buffer.
 */
दीर्घ keyctl_पढ़ो_key(key_serial_t keyid, अक्षर __user *buffer, माप_प्रकार buflen)
अणु
	काष्ठा key *key;
	key_ref_t key_ref;
	दीर्घ ret;
	अक्षर *key_data = शून्य;
	माप_प्रकार key_data_len;

	/* find the key first */
	key_ref = lookup_user_key(keyid, 0, KEY_DEFER_PERM_CHECK);
	अगर (IS_ERR(key_ref)) अणु
		ret = -ENOKEY;
		जाओ out;
	पूर्ण

	key = key_ref_to_ptr(key_ref);

	ret = key_पढ़ो_state(key);
	अगर (ret < 0)
		जाओ key_put_out; /* Negatively instantiated */

	/* see अगर we can पढ़ो it directly */
	ret = key_permission(key_ref, KEY_NEED_READ);
	अगर (ret == 0)
		जाओ can_पढ़ो_key;
	अगर (ret != -EACCES)
		जाओ key_put_out;

	/* we can't; see if it's searchable from this process's keyrings
	 * - we स्वतःmatically take account of the fact that it may be
	 *   dangling off an instantiation key
	 */
	अगर (!is_key_possessed(key_ref)) अणु
		ret = -EACCES;
		जाओ key_put_out;
	पूर्ण

	/* the key is probably पढ़ोable - now try to पढ़ो it */
can_पढ़ो_key:
	अगर (!key->type->पढ़ो) अणु
		ret = -EOPNOTSUPP;
		जाओ key_put_out;
	पूर्ण

	अगर (!buffer || !buflen) अणु
		/* Get the key length from the पढ़ो method */
		ret = __keyctl_पढ़ो_key(key, शून्य, 0);
		जाओ key_put_out;
	पूर्ण

	/*
	 * Read the data with the semaphore held (since we might sleep)
	 * to protect against the key being updated or revoked.
	 *
	 * Allocating a temporary buffer to hold the keys beक्रमe
	 * transferring them to user buffer to aव्योम potential
	 * deadlock involving page fault and mmap_lock.
	 *
	 * key_data_len = (buflen <= PAGE_SIZE)
	 *		? buflen : actual length of key data
	 *
	 * This prevents allocating arbitrary large buffer which can
	 * be much larger than the actual key length. In the latter हाल,
	 * at least 2 passes of this loop is required.
	 */
	key_data_len = (buflen <= PAGE_SIZE) ? buflen : 0;
	क्रम (;;) अणु
		अगर (key_data_len) अणु
			key_data = kvदो_स्मृति(key_data_len, GFP_KERNEL);
			अगर (!key_data) अणु
				ret = -ENOMEM;
				जाओ key_put_out;
			पूर्ण
		पूर्ण

		ret = __keyctl_पढ़ो_key(key, key_data, key_data_len);

		/*
		 * Read methods will just वापस the required length without
		 * any copying अगर the provided length isn't large enough.
		 */
		अगर (ret <= 0 || ret > buflen)
			अवरोध;

		/*
		 * The key may change (unlikely) in between 2 consecutive
		 * __keyctl_पढ़ो_key() calls. In this हाल, we पुनः_स्मृतिate
		 * a larger buffer and reकरो the key पढ़ो when
		 * key_data_len < ret <= buflen.
		 */
		अगर (ret > key_data_len) अणु
			अगर (unlikely(key_data))
				kvमुक्त_sensitive(key_data, key_data_len);
			key_data_len = ret;
			जारी;	/* Allocate buffer */
		पूर्ण

		अगर (copy_to_user(buffer, key_data, ret))
			ret = -EFAULT;
		अवरोध;
	पूर्ण
	kvमुक्त_sensitive(key_data, key_data_len);

key_put_out:
	key_put(key);
out:
	वापस ret;
पूर्ण

/*
 * Change the ownership of a key
 *
 * The key must grant the caller Setattr permission क्रम this to work, though
 * the key need not be fully instantiated yet.  For the UID to be changed, or
 * क्रम the GID to be changed to a group the caller is not a member of, the
 * caller must have sysadmin capability.  If either uid or gid is -1 then that
 * attribute is not changed.
 *
 * If the UID is to be changed, the new user must have sufficient quota to
 * accept the key.  The quota deduction will be हटाओd from the old user to
 * the new user should the attribute be changed.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_chown_key(key_serial_t id, uid_t user, gid_t group)
अणु
	काष्ठा key_user *newowner, *zaघातner = शून्य;
	काष्ठा key *key;
	key_ref_t key_ref;
	दीर्घ ret;
	kuid_t uid;
	kgid_t gid;

	uid = make_kuid(current_user_ns(), user);
	gid = make_kgid(current_user_ns(), group);
	ret = -EINVAL;
	अगर ((user != (uid_t) -1) && !uid_valid(uid))
		जाओ error;
	अगर ((group != (gid_t) -1) && !gid_valid(gid))
		जाओ error;

	ret = 0;
	अगर (user == (uid_t) -1 && group == (gid_t) -1)
		जाओ error;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE | KEY_LOOKUP_PARTIAL,
				  KEY_NEED_SETATTR);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);
		जाओ error;
	पूर्ण

	key = key_ref_to_ptr(key_ref);

	/* make the changes with the locks held to prevent chown/chown races */
	ret = -EACCES;
	करोwn_ग_लिखो(&key->sem);

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		/* only the sysadmin can chown a key to some other UID */
		अगर (user != (uid_t) -1 && !uid_eq(key->uid, uid))
			जाओ error_put;

		/* only the sysadmin can set the key's GID to a group other
		 * than one of those that the current process subscribes to */
		अगर (group != (gid_t) -1 && !gid_eq(gid, key->gid) && !in_group_p(gid))
			जाओ error_put;
	पूर्ण

	/* change the UID */
	अगर (user != (uid_t) -1 && !uid_eq(uid, key->uid)) अणु
		ret = -ENOMEM;
		newowner = key_user_lookup(uid);
		अगर (!newowner)
			जाओ error_put;

		/* transfer the quota burden to the new user */
		अगर (test_bit(KEY_FLAG_IN_QUOTA, &key->flags)) अणु
			अचिन्हित maxkeys = uid_eq(uid, GLOBAL_ROOT_UID) ?
				key_quota_root_maxkeys : key_quota_maxkeys;
			अचिन्हित maxbytes = uid_eq(uid, GLOBAL_ROOT_UID) ?
				key_quota_root_maxbytes : key_quota_maxbytes;

			spin_lock(&newowner->lock);
			अगर (newowner->qnkeys + 1 > maxkeys ||
			    newowner->qnbytes + key->quotalen > maxbytes ||
			    newowner->qnbytes + key->quotalen <
			    newowner->qnbytes)
				जाओ quota_overrun;

			newowner->qnkeys++;
			newowner->qnbytes += key->quotalen;
			spin_unlock(&newowner->lock);

			spin_lock(&key->user->lock);
			key->user->qnkeys--;
			key->user->qnbytes -= key->quotalen;
			spin_unlock(&key->user->lock);
		पूर्ण

		atomic_dec(&key->user->nkeys);
		atomic_inc(&newowner->nkeys);

		अगर (key->state != KEY_IS_UNINSTANTIATED) अणु
			atomic_dec(&key->user->nikeys);
			atomic_inc(&newowner->nikeys);
		पूर्ण

		zaघातner = key->user;
		key->user = newowner;
		key->uid = uid;
	पूर्ण

	/* change the GID */
	अगर (group != (gid_t) -1)
		key->gid = gid;

	notअगरy_key(key, NOTIFY_KEY_SETATTR, 0);
	ret = 0;

error_put:
	up_ग_लिखो(&key->sem);
	key_put(key);
	अगर (zaघातner)
		key_user_put(zaघातner);
error:
	वापस ret;

quota_overrun:
	spin_unlock(&newowner->lock);
	zaघातner = newowner;
	ret = -EDQUOT;
	जाओ error_put;
पूर्ण

/*
 * Change the permission mask on a key.
 *
 * The key must grant the caller Setattr permission क्रम this to work, though
 * the key need not be fully instantiated yet.  If the caller करोes not have
 * sysadmin capability, it may only change the permission on keys that it owns.
 */
दीर्घ keyctl_setperm_key(key_serial_t id, key_perm_t perm)
अणु
	काष्ठा key *key;
	key_ref_t key_ref;
	दीर्घ ret;

	ret = -EINVAL;
	अगर (perm & ~(KEY_POS_ALL | KEY_USR_ALL | KEY_GRP_ALL | KEY_OTH_ALL))
		जाओ error;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE | KEY_LOOKUP_PARTIAL,
				  KEY_NEED_SETATTR);
	अगर (IS_ERR(key_ref)) अणु
		ret = PTR_ERR(key_ref);
		जाओ error;
	पूर्ण

	key = key_ref_to_ptr(key_ref);

	/* make the changes with the locks held to prevent chown/chmod races */
	ret = -EACCES;
	करोwn_ग_लिखो(&key->sem);

	/* अगर we're not the sysadmin, we can only change a key that we own */
	अगर (capable(CAP_SYS_ADMIN) || uid_eq(key->uid, current_fsuid())) अणु
		key->perm = perm;
		notअगरy_key(key, NOTIFY_KEY_SETATTR, 0);
		ret = 0;
	पूर्ण

	up_ग_लिखो(&key->sem);
	key_put(key);
error:
	वापस ret;
पूर्ण

/*
 * Get the destination keyring क्रम instantiation and check that the caller has
 * Write permission on it.
 */
अटल दीर्घ get_instantiation_keyring(key_serial_t ringid,
				      काष्ठा request_key_auth *rka,
				      काष्ठा key **_dest_keyring)
अणु
	key_ref_t dkref;

	*_dest_keyring = शून्य;

	/* just वापस a शून्य poपूर्णांकer अगर we weren't asked to make a link */
	अगर (ringid == 0)
		वापस 0;

	/* अगर a specअगरic keyring is nominated by ID, then use that */
	अगर (ringid > 0) अणु
		dkref = lookup_user_key(ringid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
		अगर (IS_ERR(dkref))
			वापस PTR_ERR(dkref);
		*_dest_keyring = key_ref_to_ptr(dkref);
		वापस 0;
	पूर्ण

	अगर (ringid == KEY_SPEC_REQKEY_AUTH_KEY)
		वापस -EINVAL;

	/* otherwise specअगरy the destination keyring recorded in the
	 * authorisation key (any KEY_SPEC_*_KEYRING) */
	अगर (ringid >= KEY_SPEC_REQUESTOR_KEYRING) अणु
		*_dest_keyring = key_get(rka->dest_keyring);
		वापस 0;
	पूर्ण

	वापस -ENOKEY;
पूर्ण

/*
 * Change the request_key authorisation key on the current process.
 */
अटल पूर्णांक keyctl_change_reqkey_auth(काष्ठा key *key)
अणु
	काष्ठा cred *new;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	key_put(new->request_key_auth);
	new->request_key_auth = key_get(key);

	वापस commit_creds(new);
पूर्ण

/*
 * Instantiate a key with the specअगरied payload and link the key पूर्णांकo the
 * destination keyring अगर one is given.
 *
 * The caller must have the appropriate instantiation permit set क्रम this to
 * work (see keyctl_assume_authority).  No other permissions are required.
 *
 * If successful, 0 will be वापसed.
 */
अटल दीर्घ keyctl_instantiate_key_common(key_serial_t id,
				   काष्ठा iov_iter *from,
				   key_serial_t ringid)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा request_key_auth *rka;
	काष्ठा key *instkey, *dest_keyring;
	माप_प्रकार plen = from ? iov_iter_count(from) : 0;
	व्योम *payload;
	दीर्घ ret;

	kenter("%d,,%zu,%d", id, plen, ringid);

	अगर (!plen)
		from = शून्य;

	ret = -EINVAL;
	अगर (plen > 1024 * 1024 - 1)
		जाओ error;

	/* the appropriate instantiation authorisation key must have been
	 * assumed beक्रमe calling this */
	ret = -EPERM;
	instkey = cred->request_key_auth;
	अगर (!instkey)
		जाओ error;

	rka = instkey->payload.data[0];
	अगर (rka->target_key->serial != id)
		जाओ error;

	/* pull the payload in अगर one was supplied */
	payload = शून्य;

	अगर (from) अणु
		ret = -ENOMEM;
		payload = kvदो_स्मृति(plen, GFP_KERNEL);
		अगर (!payload)
			जाओ error;

		ret = -EFAULT;
		अगर (!copy_from_iter_full(payload, plen, from))
			जाओ error2;
	पूर्ण

	/* find the destination keyring amongst those beदीर्घing to the
	 * requesting task */
	ret = get_instantiation_keyring(ringid, rka, &dest_keyring);
	अगर (ret < 0)
		जाओ error2;

	/* instantiate the key and link it पूर्णांकo a keyring */
	ret = key_instantiate_and_link(rka->target_key, payload, plen,
				       dest_keyring, instkey);

	key_put(dest_keyring);

	/* discard the assumed authority अगर it's just been disabled by
	 * instantiation of the key */
	अगर (ret == 0)
		keyctl_change_reqkey_auth(शून्य);

error2:
	kvमुक्त_sensitive(payload, plen);
error:
	वापस ret;
पूर्ण

/*
 * Instantiate a key with the specअगरied payload and link the key पूर्णांकo the
 * destination keyring अगर one is given.
 *
 * The caller must have the appropriate instantiation permit set क्रम this to
 * work (see keyctl_assume_authority).  No other permissions are required.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_instantiate_key(key_serial_t id,
			    स्थिर व्योम __user *_payload,
			    माप_प्रकार plen,
			    key_serial_t ringid)
अणु
	अगर (_payload && plen) अणु
		काष्ठा iovec iov;
		काष्ठा iov_iter from;
		पूर्णांक ret;

		ret = import_single_range(WRITE, (व्योम __user *)_payload, plen,
					  &iov, &from);
		अगर (unlikely(ret))
			वापस ret;

		वापस keyctl_instantiate_key_common(id, &from, ringid);
	पूर्ण

	वापस keyctl_instantiate_key_common(id, शून्य, ringid);
पूर्ण

/*
 * Instantiate a key with the specअगरied multipart payload and link the key पूर्णांकo
 * the destination keyring अगर one is given.
 *
 * The caller must have the appropriate instantiation permit set क्रम this to
 * work (see keyctl_assume_authority).  No other permissions are required.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_instantiate_key_iov(key_serial_t id,
				स्थिर काष्ठा iovec __user *_payload_iov,
				अचिन्हित ioc,
				key_serial_t ringid)
अणु
	काष्ठा iovec iovstack[UIO_FASTIOV], *iov = iovstack;
	काष्ठा iov_iter from;
	दीर्घ ret;

	अगर (!_payload_iov)
		ioc = 0;

	ret = import_iovec(WRITE, _payload_iov, ioc,
				    ARRAY_SIZE(iovstack), &iov, &from);
	अगर (ret < 0)
		वापस ret;
	ret = keyctl_instantiate_key_common(id, &from, ringid);
	kमुक्त(iov);
	वापस ret;
पूर्ण

/*
 * Negatively instantiate the key with the given समयout (in seconds) and link
 * the key पूर्णांकo the destination keyring अगर one is given.
 *
 * The caller must have the appropriate instantiation permit set क्रम this to
 * work (see keyctl_assume_authority).  No other permissions are required.
 *
 * The key and any links to the key will be स्वतःmatically garbage collected
 * after the समयout expires.
 *
 * Negative keys are used to rate limit repeated request_key() calls by causing
 * them to वापस -ENOKEY until the negative key expires.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_negate_key(key_serial_t id, अचिन्हित समयout, key_serial_t ringid)
अणु
	वापस keyctl_reject_key(id, समयout, ENOKEY, ringid);
पूर्ण

/*
 * Negatively instantiate the key with the given समयout (in seconds) and error
 * code and link the key पूर्णांकo the destination keyring अगर one is given.
 *
 * The caller must have the appropriate instantiation permit set क्रम this to
 * work (see keyctl_assume_authority).  No other permissions are required.
 *
 * The key and any links to the key will be स्वतःmatically garbage collected
 * after the समयout expires.
 *
 * Negative keys are used to rate limit repeated request_key() calls by causing
 * them to वापस the specअगरied error code until the negative key expires.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_reject_key(key_serial_t id, अचिन्हित समयout, अचिन्हित error,
		       key_serial_t ringid)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा request_key_auth *rka;
	काष्ठा key *instkey, *dest_keyring;
	दीर्घ ret;

	kenter("%d,%u,%u,%d", id, समयout, error, ringid);

	/* must be a valid error code and mustn't be a kernel special */
	अगर (error <= 0 ||
	    error >= MAX_ERRNO ||
	    error == ERESTARTSYS ||
	    error == ERESTARTNOINTR ||
	    error == ERESTARTNOHAND ||
	    error == ERESTART_RESTARTBLOCK)
		वापस -EINVAL;

	/* the appropriate instantiation authorisation key must have been
	 * assumed beक्रमe calling this */
	ret = -EPERM;
	instkey = cred->request_key_auth;
	अगर (!instkey)
		जाओ error;

	rka = instkey->payload.data[0];
	अगर (rka->target_key->serial != id)
		जाओ error;

	/* find the destination keyring अगर present (which must also be
	 * writable) */
	ret = get_instantiation_keyring(ringid, rka, &dest_keyring);
	अगर (ret < 0)
		जाओ error;

	/* instantiate the key and link it पूर्णांकo a keyring */
	ret = key_reject_and_link(rka->target_key, समयout, error,
				  dest_keyring, instkey);

	key_put(dest_keyring);

	/* discard the assumed authority अगर it's just been disabled by
	 * instantiation of the key */
	अगर (ret == 0)
		keyctl_change_reqkey_auth(शून्य);

error:
	वापस ret;
पूर्ण

/*
 * Read or set the शेष keyring in which request_key() will cache keys and
 * वापस the old setting.
 *
 * If a thपढ़ो or process keyring is specअगरied then it will be created अगर it
 * करोesn't yet exist.  The old setting will be वापसed अगर successful.
 */
दीर्घ keyctl_set_reqkey_keyring(पूर्णांक reqkey_defl)
अणु
	काष्ठा cred *new;
	पूर्णांक ret, old_setting;

	old_setting = current_cred_xxx(jit_keyring);

	अगर (reqkey_defl == KEY_REQKEY_DEFL_NO_CHANGE)
		वापस old_setting;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	चयन (reqkey_defl) अणु
	हाल KEY_REQKEY_DEFL_THREAD_KEYRING:
		ret = install_thपढ़ो_keyring_to_cred(new);
		अगर (ret < 0)
			जाओ error;
		जाओ set;

	हाल KEY_REQKEY_DEFL_PROCESS_KEYRING:
		ret = install_process_keyring_to_cred(new);
		अगर (ret < 0)
			जाओ error;
		जाओ set;

	हाल KEY_REQKEY_DEFL_DEFAULT:
	हाल KEY_REQKEY_DEFL_SESSION_KEYRING:
	हाल KEY_REQKEY_DEFL_USER_KEYRING:
	हाल KEY_REQKEY_DEFL_USER_SESSION_KEYRING:
	हाल KEY_REQKEY_DEFL_REQUESTOR_KEYRING:
		जाओ set;

	हाल KEY_REQKEY_DEFL_NO_CHANGE:
	हाल KEY_REQKEY_DEFL_GROUP_KEYRING:
	शेष:
		ret = -EINVAL;
		जाओ error;
	पूर्ण

set:
	new->jit_keyring = reqkey_defl;
	commit_creds(new);
	वापस old_setting;
error:
	पात_creds(new);
	वापस ret;
पूर्ण

/*
 * Set or clear the समयout on a key.
 *
 * Either the key must grant the caller Setattr permission or अन्यथा the caller
 * must hold an instantiation authorisation token क्रम the key.
 *
 * The समयout is either 0 to clear the समयout, or a number of seconds from
 * the current समय.  The key and any links to the key will be स्वतःmatically
 * garbage collected after the समयout expires.
 *
 * Keys with KEY_FLAG_KEEP set should not be समयd out.
 *
 * If successful, 0 is वापसed.
 */
दीर्घ keyctl_set_समयout(key_serial_t id, अचिन्हित समयout)
अणु
	काष्ठा key *key, *instkey;
	key_ref_t key_ref;
	दीर्घ ret;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE | KEY_LOOKUP_PARTIAL,
				  KEY_NEED_SETATTR);
	अगर (IS_ERR(key_ref)) अणु
		/* setting the समयout on a key under स्थिरruction is permitted
		 * अगर we have the authorisation token handy */
		अगर (PTR_ERR(key_ref) == -EACCES) अणु
			instkey = key_get_instantiation_authkey(id);
			अगर (!IS_ERR(instkey)) अणु
				key_put(instkey);
				key_ref = lookup_user_key(id,
							  KEY_LOOKUP_PARTIAL,
							  KEY_AUTHTOKEN_OVERRIDE);
				अगर (!IS_ERR(key_ref))
					जाओ okay;
			पूर्ण
		पूर्ण

		ret = PTR_ERR(key_ref);
		जाओ error;
	पूर्ण

okay:
	key = key_ref_to_ptr(key_ref);
	ret = 0;
	अगर (test_bit(KEY_FLAG_KEEP, &key->flags)) अणु
		ret = -EPERM;
	पूर्ण अन्यथा अणु
		key_set_समयout(key, समयout);
		notअगरy_key(key, NOTIFY_KEY_SETATTR, 0);
	पूर्ण
	key_put(key);

error:
	वापस ret;
पूर्ण

/*
 * Assume (or clear) the authority to instantiate the specअगरied key.
 *
 * This sets the authoritative token currently in क्रमce क्रम key instantiation.
 * This must be करोne क्रम a key to be instantiated.  It has the effect of making
 * available all the keys from the caller of the request_key() that created a
 * key to request_key() calls made by the caller of this function.
 *
 * The caller must have the instantiation key in their process keyrings with a
 * Search permission grant available to the caller.
 *
 * If the ID given is 0, then the setting will be cleared and 0 वापसed.
 *
 * If the ID given has a matching an authorisation key, then that key will be
 * set and its ID will be वापसed.  The authorisation key can be पढ़ो to get
 * the callout inक्रमmation passed to request_key().
 */
दीर्घ keyctl_assume_authority(key_serial_t id)
अणु
	काष्ठा key *authkey;
	दीर्घ ret;

	/* special key IDs aren't permitted */
	ret = -EINVAL;
	अगर (id < 0)
		जाओ error;

	/* we भागest ourselves of authority अगर given an ID of 0 */
	अगर (id == 0) अणु
		ret = keyctl_change_reqkey_auth(शून्य);
		जाओ error;
	पूर्ण

	/* attempt to assume the authority temporarily granted to us whilst we
	 * instantiate the specअगरied key
	 * - the authorisation key must be in the current task's keyrings
	 *   somewhere
	 */
	authkey = key_get_instantiation_authkey(id);
	अगर (IS_ERR(authkey)) अणु
		ret = PTR_ERR(authkey);
		जाओ error;
	पूर्ण

	ret = keyctl_change_reqkey_auth(authkey);
	अगर (ret == 0)
		ret = authkey->serial;
	key_put(authkey);
error:
	वापस ret;
पूर्ण

/*
 * Get a key's the LSM security label.
 *
 * The key must grant the caller View permission क्रम this to work.
 *
 * If there's a buffer, then up to buflen bytes of data will be placed पूर्णांकo it.
 *
 * If successful, the amount of inक्रमmation available will be वापसed,
 * irrespective of how much was copied (including the terminal NUL).
 */
दीर्घ keyctl_get_security(key_serial_t keyid,
			 अक्षर __user *buffer,
			 माप_प्रकार buflen)
अणु
	काष्ठा key *key, *instkey;
	key_ref_t key_ref;
	अक्षर *context;
	दीर्घ ret;

	key_ref = lookup_user_key(keyid, KEY_LOOKUP_PARTIAL, KEY_NEED_VIEW);
	अगर (IS_ERR(key_ref)) अणु
		अगर (PTR_ERR(key_ref) != -EACCES)
			वापस PTR_ERR(key_ref);

		/* viewing a key under स्थिरruction is also permitted अगर we
		 * have the authorisation token handy */
		instkey = key_get_instantiation_authkey(keyid);
		अगर (IS_ERR(instkey))
			वापस PTR_ERR(instkey);
		key_put(instkey);

		key_ref = lookup_user_key(keyid, KEY_LOOKUP_PARTIAL,
					  KEY_AUTHTOKEN_OVERRIDE);
		अगर (IS_ERR(key_ref))
			वापस PTR_ERR(key_ref);
	पूर्ण

	key = key_ref_to_ptr(key_ref);
	ret = security_key_माला_लोecurity(key, &context);
	अगर (ret == 0) अणु
		/* अगर no inक्रमmation was वापसed, give userspace an empty
		 * string */
		ret = 1;
		अगर (buffer && buflen > 0 &&
		    copy_to_user(buffer, "", 1) != 0)
			ret = -EFAULT;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		/* वापस as much data as there's room क्रम */
		अगर (buffer && buflen > 0) अणु
			अगर (buflen > ret)
				buflen = ret;

			अगर (copy_to_user(buffer, context, buflen) != 0)
				ret = -EFAULT;
		पूर्ण

		kमुक्त(context);
	पूर्ण

	key_ref_put(key_ref);
	वापस ret;
पूर्ण

/*
 * Attempt to install the calling process's session keyring on the process's
 * parent process.
 *
 * The keyring must exist and must grant the caller LINK permission, and the
 * parent process must be single-thपढ़ोed and must have the same effective
 * ownership as this process and mustn't be SUID/SGID.
 *
 * The keyring will be emplaced on the parent when it next resumes userspace.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ keyctl_session_to_parent(व्योम)
अणु
	काष्ठा task_काष्ठा *me, *parent;
	स्थिर काष्ठा cred *mycred, *pcred;
	काष्ठा callback_head *newwork, *oldwork;
	key_ref_t keyring_r;
	काष्ठा cred *cred;
	पूर्णांक ret;

	keyring_r = lookup_user_key(KEY_SPEC_SESSION_KEYRING, 0, KEY_NEED_LINK);
	अगर (IS_ERR(keyring_r))
		वापस PTR_ERR(keyring_r);

	ret = -ENOMEM;

	/* our parent is going to need a new cred काष्ठा, a new tgcred काष्ठा
	 * and new security data, so we allocate them here to prevent ENOMEM in
	 * our parent */
	cred = cred_alloc_blank();
	अगर (!cred)
		जाओ error_keyring;
	newwork = &cred->rcu;

	cred->session_keyring = key_ref_to_ptr(keyring_r);
	keyring_r = शून्य;
	init_task_work(newwork, key_change_session_keyring);

	me = current;
	rcu_पढ़ो_lock();
	ग_लिखो_lock_irq(&tasklist_lock);

	ret = -EPERM;
	oldwork = शून्य;
	parent = rcu_dereference_रक्षित(me->real_parent,
					   lockdep_is_held(&tasklist_lock));

	/* the parent mustn't be init and mustn't be a kernel thपढ़ो */
	अगर (parent->pid <= 1 || !parent->mm)
		जाओ unlock;

	/* the parent must be single thपढ़ोed */
	अगर (!thपढ़ो_group_empty(parent))
		जाओ unlock;

	/* the parent and the child must have dअगरferent session keyrings or
	 * there's no poपूर्णांक */
	mycred = current_cred();
	pcred = __task_cred(parent);
	अगर (mycred == pcred ||
	    mycred->session_keyring == pcred->session_keyring) अणु
		ret = 0;
		जाओ unlock;
	पूर्ण

	/* the parent must have the same effective ownership and mustn't be
	 * SUID/SGID */
	अगर (!uid_eq(pcred->uid,	 mycred->euid) ||
	    !uid_eq(pcred->euid, mycred->euid) ||
	    !uid_eq(pcred->suid, mycred->euid) ||
	    !gid_eq(pcred->gid,	 mycred->egid) ||
	    !gid_eq(pcred->egid, mycred->egid) ||
	    !gid_eq(pcred->sgid, mycred->egid))
		जाओ unlock;

	/* the keyrings must have the same UID */
	अगर ((pcred->session_keyring &&
	     !uid_eq(pcred->session_keyring->uid, mycred->euid)) ||
	    !uid_eq(mycred->session_keyring->uid, mycred->euid))
		जाओ unlock;

	/* cancel an alपढ़ोy pending keyring replacement */
	oldwork = task_work_cancel(parent, key_change_session_keyring);

	/* the replacement session keyring is applied just prior to userspace
	 * restarting */
	ret = task_work_add(parent, newwork, TWA_RESUME);
	अगर (!ret)
		newwork = शून्य;
unlock:
	ग_लिखो_unlock_irq(&tasklist_lock);
	rcu_पढ़ो_unlock();
	अगर (oldwork)
		put_cred(container_of(oldwork, काष्ठा cred, rcu));
	अगर (newwork)
		put_cred(cred);
	वापस ret;

error_keyring:
	key_ref_put(keyring_r);
	वापस ret;
पूर्ण

/*
 * Apply a restriction to a given keyring.
 *
 * The caller must have Setattr permission to change keyring restrictions.
 *
 * The requested type name may be a शून्य poपूर्णांकer to reject all attempts
 * to link to the keyring.  In this हाल, _restriction must also be शून्य.
 * Otherwise, both _type and _restriction must be non-शून्य.
 *
 * Returns 0 अगर successful.
 */
दीर्घ keyctl_restrict_keyring(key_serial_t id, स्थिर अक्षर __user *_type,
			     स्थिर अक्षर __user *_restriction)
अणु
	key_ref_t key_ref;
	अक्षर type[32];
	अक्षर *restriction = शून्य;
	दीर्घ ret;

	key_ref = lookup_user_key(id, 0, KEY_NEED_SETATTR);
	अगर (IS_ERR(key_ref))
		वापस PTR_ERR(key_ref);

	ret = -EINVAL;
	अगर (_type) अणु
		अगर (!_restriction)
			जाओ error;

		ret = key_get_type_from_user(type, _type, माप(type));
		अगर (ret < 0)
			जाओ error;

		restriction = strndup_user(_restriction, PAGE_SIZE);
		अगर (IS_ERR(restriction)) अणु
			ret = PTR_ERR(restriction);
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (_restriction)
			जाओ error;
	पूर्ण

	ret = keyring_restrict(key_ref, _type ? type : शून्य, restriction);
	kमुक्त(restriction);
error:
	key_ref_put(key_ref);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
/*
 * Watch क्रम changes to a key.
 *
 * The caller must have View permission to watch a key or keyring.
 */
दीर्घ keyctl_watch_key(key_serial_t id, पूर्णांक watch_queue_fd, पूर्णांक watch_id)
अणु
	काष्ठा watch_queue *wqueue;
	काष्ठा watch_list *wlist = शून्य;
	काष्ठा watch *watch = शून्य;
	काष्ठा key *key;
	key_ref_t key_ref;
	दीर्घ ret;

	अगर (watch_id < -1 || watch_id > 0xff)
		वापस -EINVAL;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE, KEY_NEED_VIEW);
	अगर (IS_ERR(key_ref))
		वापस PTR_ERR(key_ref);
	key = key_ref_to_ptr(key_ref);

	wqueue = get_watch_queue(watch_queue_fd);
	अगर (IS_ERR(wqueue)) अणु
		ret = PTR_ERR(wqueue);
		जाओ err_key;
	पूर्ण

	अगर (watch_id >= 0) अणु
		ret = -ENOMEM;
		अगर (!key->watchers) अणु
			wlist = kzalloc(माप(*wlist), GFP_KERNEL);
			अगर (!wlist)
				जाओ err_wqueue;
			init_watch_list(wlist, शून्य);
		पूर्ण

		watch = kzalloc(माप(*watch), GFP_KERNEL);
		अगर (!watch)
			जाओ err_wlist;

		init_watch(watch, wqueue);
		watch->id	= key->serial;
		watch->info_id	= (u32)watch_id << WATCH_INFO_ID__SHIFT;

		ret = security_watch_key(key);
		अगर (ret < 0)
			जाओ err_watch;

		करोwn_ग_लिखो(&key->sem);
		अगर (!key->watchers) अणु
			key->watchers = wlist;
			wlist = शून्य;
		पूर्ण

		ret = add_watch_to_object(watch, key->watchers);
		up_ग_लिखो(&key->sem);

		अगर (ret == 0)
			watch = शून्य;
	पूर्ण अन्यथा अणु
		ret = -EBADSLT;
		अगर (key->watchers) अणु
			करोwn_ग_लिखो(&key->sem);
			ret = हटाओ_watch_from_object(key->watchers,
						       wqueue, key_serial(key),
						       false);
			up_ग_लिखो(&key->sem);
		पूर्ण
	पूर्ण

err_watch:
	kमुक्त(watch);
err_wlist:
	kमुक्त(wlist);
err_wqueue:
	put_watch_queue(wqueue);
err_key:
	key_put(key);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_KEY_NOTIFICATIONS */

/*
 * Get keyrings subप्रणाली capabilities.
 */
दीर्घ keyctl_capabilities(अचिन्हित अक्षर __user *_buffer, माप_प्रकार buflen)
अणु
	माप_प्रकार size = buflen;

	अगर (size > 0) अणु
		अगर (size > माप(keyrings_capabilities))
			size = माप(keyrings_capabilities);
		अगर (copy_to_user(_buffer, keyrings_capabilities, size) != 0)
			वापस -EFAULT;
		अगर (size < buflen &&
		    clear_user(_buffer + size, buflen - size) != 0)
			वापस -EFAULT;
	पूर्ण

	वापस माप(keyrings_capabilities);
पूर्ण

/*
 * The key control प्रणाली call
 */
SYSCALL_DEFINE5(keyctl, पूर्णांक, option, अचिन्हित दीर्घ, arg2, अचिन्हित दीर्घ, arg3,
		अचिन्हित दीर्घ, arg4, अचिन्हित दीर्घ, arg5)
अणु
	चयन (option) अणु
	हाल KEYCTL_GET_KEYRING_ID:
		वापस keyctl_get_keyring_ID((key_serial_t) arg2,
					     (पूर्णांक) arg3);

	हाल KEYCTL_JOIN_SESSION_KEYRING:
		वापस keyctl_join_session_keyring((स्थिर अक्षर __user *) arg2);

	हाल KEYCTL_UPDATE:
		वापस keyctl_update_key((key_serial_t) arg2,
					 (स्थिर व्योम __user *) arg3,
					 (माप_प्रकार) arg4);

	हाल KEYCTL_REVOKE:
		वापस keyctl_revoke_key((key_serial_t) arg2);

	हाल KEYCTL_DESCRIBE:
		वापस keyctl_describe_key((key_serial_t) arg2,
					   (अक्षर __user *) arg3,
					   (अचिन्हित) arg4);

	हाल KEYCTL_CLEAR:
		वापस keyctl_keyring_clear((key_serial_t) arg2);

	हाल KEYCTL_LINK:
		वापस keyctl_keyring_link((key_serial_t) arg2,
					   (key_serial_t) arg3);

	हाल KEYCTL_UNLINK:
		वापस keyctl_keyring_unlink((key_serial_t) arg2,
					     (key_serial_t) arg3);

	हाल KEYCTL_SEARCH:
		वापस keyctl_keyring_search((key_serial_t) arg2,
					     (स्थिर अक्षर __user *) arg3,
					     (स्थिर अक्षर __user *) arg4,
					     (key_serial_t) arg5);

	हाल KEYCTL_READ:
		वापस keyctl_पढ़ो_key((key_serial_t) arg2,
				       (अक्षर __user *) arg3,
				       (माप_प्रकार) arg4);

	हाल KEYCTL_CHOWN:
		वापस keyctl_chown_key((key_serial_t) arg2,
					(uid_t) arg3,
					(gid_t) arg4);

	हाल KEYCTL_SETPERM:
		वापस keyctl_setperm_key((key_serial_t) arg2,
					  (key_perm_t) arg3);

	हाल KEYCTL_INSTANTIATE:
		वापस keyctl_instantiate_key((key_serial_t) arg2,
					      (स्थिर व्योम __user *) arg3,
					      (माप_प्रकार) arg4,
					      (key_serial_t) arg5);

	हाल KEYCTL_NEGATE:
		वापस keyctl_negate_key((key_serial_t) arg2,
					 (अचिन्हित) arg3,
					 (key_serial_t) arg4);

	हाल KEYCTL_SET_REQKEY_KEYRING:
		वापस keyctl_set_reqkey_keyring(arg2);

	हाल KEYCTL_SET_TIMEOUT:
		वापस keyctl_set_समयout((key_serial_t) arg2,
					  (अचिन्हित) arg3);

	हाल KEYCTL_ASSUME_AUTHORITY:
		वापस keyctl_assume_authority((key_serial_t) arg2);

	हाल KEYCTL_GET_SECURITY:
		वापस keyctl_get_security((key_serial_t) arg2,
					   (अक्षर __user *) arg3,
					   (माप_प्रकार) arg4);

	हाल KEYCTL_SESSION_TO_PARENT:
		वापस keyctl_session_to_parent();

	हाल KEYCTL_REJECT:
		वापस keyctl_reject_key((key_serial_t) arg2,
					 (अचिन्हित) arg3,
					 (अचिन्हित) arg4,
					 (key_serial_t) arg5);

	हाल KEYCTL_INSTANTIATE_IOV:
		वापस keyctl_instantiate_key_iov(
			(key_serial_t) arg2,
			(स्थिर काष्ठा iovec __user *) arg3,
			(अचिन्हित) arg4,
			(key_serial_t) arg5);

	हाल KEYCTL_INVALIDATE:
		वापस keyctl_invalidate_key((key_serial_t) arg2);

	हाल KEYCTL_GET_PERSISTENT:
		वापस keyctl_get_persistent((uid_t)arg2, (key_serial_t)arg3);

	हाल KEYCTL_DH_COMPUTE:
		वापस keyctl_dh_compute((काष्ठा keyctl_dh_params __user *) arg2,
					 (अक्षर __user *) arg3, (माप_प्रकार) arg4,
					 (काष्ठा keyctl_kdf_params __user *) arg5);

	हाल KEYCTL_RESTRICT_KEYRING:
		वापस keyctl_restrict_keyring((key_serial_t) arg2,
					       (स्थिर अक्षर __user *) arg3,
					       (स्थिर अक्षर __user *) arg4);

	हाल KEYCTL_PKEY_QUERY:
		अगर (arg3 != 0)
			वापस -EINVAL;
		वापस keyctl_pkey_query((key_serial_t)arg2,
					 (स्थिर अक्षर __user *)arg4,
					 (काष्ठा keyctl_pkey_query __user *)arg5);

	हाल KEYCTL_PKEY_ENCRYPT:
	हाल KEYCTL_PKEY_DECRYPT:
	हाल KEYCTL_PKEY_SIGN:
		वापस keyctl_pkey_e_d_s(
			option,
			(स्थिर काष्ठा keyctl_pkey_params __user *)arg2,
			(स्थिर अक्षर __user *)arg3,
			(स्थिर व्योम __user *)arg4,
			(व्योम __user *)arg5);

	हाल KEYCTL_PKEY_VERIFY:
		वापस keyctl_pkey_verअगरy(
			(स्थिर काष्ठा keyctl_pkey_params __user *)arg2,
			(स्थिर अक्षर __user *)arg3,
			(स्थिर व्योम __user *)arg4,
			(स्थिर व्योम __user *)arg5);

	हाल KEYCTL_MOVE:
		वापस keyctl_keyring_move((key_serial_t)arg2,
					   (key_serial_t)arg3,
					   (key_serial_t)arg4,
					   (अचिन्हित पूर्णांक)arg5);

	हाल KEYCTL_CAPABILITIES:
		वापस keyctl_capabilities((अचिन्हित अक्षर __user *)arg2, (माप_प्रकार)arg3);

	हाल KEYCTL_WATCH_KEY:
		वापस keyctl_watch_key((key_serial_t)arg2, (पूर्णांक)arg3, (पूर्णांक)arg4);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
