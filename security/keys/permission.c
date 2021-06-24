<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Key permission checking
 *
 * Copyright (C) 2005 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/security.h>
#समावेश "internal.h"

/**
 * key_task_permission - Check a key can be used
 * @key_ref: The key to check.
 * @cred: The credentials to use.
 * @need_perm: The permission required.
 *
 * Check to see whether permission is granted to use a key in the desired way,
 * but permit the security modules to override.
 *
 * The caller must hold either a ref on cred or must hold the RCU पढ़ोlock.
 *
 * Returns 0 अगर successful, -EACCES अगर access is denied based on the
 * permissions bits or the LSM check.
 */
पूर्णांक key_task_permission(स्थिर key_ref_t key_ref, स्थिर काष्ठा cred *cred,
			क्रमागत key_need_perm need_perm)
अणु
	काष्ठा key *key;
	key_perm_t kperm, mask;
	पूर्णांक ret;

	चयन (need_perm) अणु
	शेष:
		WARN_ON(1);
		वापस -EACCES;
	हाल KEY_NEED_UNLINK:
	हाल KEY_SYSADMIN_OVERRIDE:
	हाल KEY_AUTHTOKEN_OVERRIDE:
	हाल KEY_DEFER_PERM_CHECK:
		जाओ lsm;

	हाल KEY_NEED_VIEW:	mask = KEY_OTH_VIEW;	अवरोध;
	हाल KEY_NEED_READ:	mask = KEY_OTH_READ;	अवरोध;
	हाल KEY_NEED_WRITE:	mask = KEY_OTH_WRITE;	अवरोध;
	हाल KEY_NEED_SEARCH:	mask = KEY_OTH_SEARCH;	अवरोध;
	हाल KEY_NEED_LINK:	mask = KEY_OTH_LINK;	अवरोध;
	हाल KEY_NEED_SETATTR:	mask = KEY_OTH_SETATTR;	अवरोध;
	पूर्ण

	key = key_ref_to_ptr(key_ref);

	/* use the second 8-bits of permissions क्रम keys the caller owns */
	अगर (uid_eq(key->uid, cred->fsuid)) अणु
		kperm = key->perm >> 16;
		जाओ use_these_perms;
	पूर्ण

	/* use the third 8-bits of permissions क्रम keys the caller has a group
	 * membership in common with */
	अगर (gid_valid(key->gid) && key->perm & KEY_GRP_ALL) अणु
		अगर (gid_eq(key->gid, cred->fsgid)) अणु
			kperm = key->perm >> 8;
			जाओ use_these_perms;
		पूर्ण

		ret = groups_search(cred->group_info, key->gid);
		अगर (ret) अणु
			kperm = key->perm >> 8;
			जाओ use_these_perms;
		पूर्ण
	पूर्ण

	/* otherwise use the least-signअगरicant 8-bits */
	kperm = key->perm;

use_these_perms:

	/* use the top 8-bits of permissions क्रम keys the caller possesses
	 * - possessor permissions are additive with other permissions
	 */
	अगर (is_key_possessed(key_ref))
		kperm |= key->perm >> 24;

	अगर ((kperm & mask) != mask)
		वापस -EACCES;

	/* let LSM be the final arbiter */
lsm:
	वापस security_key_permission(key_ref, cred, need_perm);
पूर्ण
EXPORT_SYMBOL(key_task_permission);

/**
 * key_validate - Validate a key.
 * @key: The key to be validated.
 *
 * Check that a key is valid, वापसing 0 अगर the key is okay, -ENOKEY अगर the
 * key is invalidated, -EKEYREVOKED अगर the key's type has been हटाओd or अगर
 * the key has been revoked or -EKEYEXPIRED अगर the key has expired.
 */
पूर्णांक key_validate(स्थिर काष्ठा key *key)
अणु
	अचिन्हित दीर्घ flags = READ_ONCE(key->flags);
	समय64_t expiry = READ_ONCE(key->expiry);

	अगर (flags & (1 << KEY_FLAG_INVALIDATED))
		वापस -ENOKEY;

	/* check it's still accessible */
	अगर (flags & ((1 << KEY_FLAG_REVOKED) |
		     (1 << KEY_FLAG_DEAD)))
		वापस -EKEYREVOKED;

	/* check it hasn't expired */
	अगर (expiry) अणु
		अगर (kसमय_get_real_seconds() >= expiry)
			वापस -EKEYEXPIRED;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(key_validate);
