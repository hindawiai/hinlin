<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* General persistent per-UID keyrings रेजिस्टर
 *
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/user_namespace.h>
#समावेश <linux/cred.h>

#समावेश "internal.h"

अचिन्हित persistent_keyring_expiry = 3 * 24 * 3600; /* Expire after 3 days of non-use */

/*
 * Create the persistent keyring रेजिस्टर क्रम the current user namespace.
 *
 * Called with the namespace's sem locked क्रम writing.
 */
अटल पूर्णांक key_create_persistent_रेजिस्टर(काष्ठा user_namespace *ns)
अणु
	काष्ठा key *reg = keyring_alloc(".persistent_register",
					KUIDT_INIT(0), KGIDT_INIT(0),
					current_cred(),
					((KEY_POS_ALL & ~KEY_POS_SETATTR) |
					 KEY_USR_VIEW | KEY_USR_READ),
					KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	ns->persistent_keyring_रेजिस्टर = reg;
	वापस 0;
पूर्ण

/*
 * Create the persistent keyring क्रम the specअगरied user.
 *
 * Called with the namespace's sem locked क्रम writing.
 */
अटल key_ref_t key_create_persistent(काष्ठा user_namespace *ns, kuid_t uid,
				       काष्ठा keyring_index_key *index_key)
अणु
	काष्ठा key *persistent;
	key_ref_t reg_ref, persistent_ref;

	अगर (!ns->persistent_keyring_रेजिस्टर) अणु
		दीर्घ err = key_create_persistent_रेजिस्टर(ns);
		अगर (err < 0)
			वापस ERR_PTR(err);
	पूर्ण अन्यथा अणु
		reg_ref = make_key_ref(ns->persistent_keyring_रेजिस्टर, true);
		persistent_ref = find_key_to_update(reg_ref, index_key);
		अगर (persistent_ref)
			वापस persistent_ref;
	पूर्ण

	persistent = keyring_alloc(index_key->description,
				   uid, INVALID_GID, current_cred(),
				   ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
				    KEY_USR_VIEW | KEY_USR_READ),
				   KEY_ALLOC_NOT_IN_QUOTA, शून्य,
				   ns->persistent_keyring_रेजिस्टर);
	अगर (IS_ERR(persistent))
		वापस ERR_CAST(persistent);

	वापस make_key_ref(persistent, true);
पूर्ण

/*
 * Get the persistent keyring क्रम a specअगरic UID and link it to the nominated
 * keyring.
 */
अटल दीर्घ key_get_persistent(काष्ठा user_namespace *ns, kuid_t uid,
			       key_ref_t dest_ref)
अणु
	काष्ठा keyring_index_key index_key;
	काष्ठा key *persistent;
	key_ref_t reg_ref, persistent_ref;
	अक्षर buf[32];
	दीर्घ ret;

	/* Look in the रेजिस्टर अगर it exists */
	स_रखो(&index_key, 0, माप(index_key));
	index_key.type = &key_type_keyring;
	index_key.description = buf;
	index_key.desc_len = प्र_लिखो(buf, "_persistent.%u", from_kuid(ns, uid));
	key_set_index_key(&index_key);

	अगर (ns->persistent_keyring_रेजिस्टर) अणु
		reg_ref = make_key_ref(ns->persistent_keyring_रेजिस्टर, true);
		करोwn_पढ़ो(&ns->keyring_sem);
		persistent_ref = find_key_to_update(reg_ref, &index_key);
		up_पढ़ो(&ns->keyring_sem);

		अगर (persistent_ref)
			जाओ found;
	पूर्ण

	/* It wasn't in the register, so we'll need to create it.  We might
	 * also need to create the रेजिस्टर.
	 */
	करोwn_ग_लिखो(&ns->keyring_sem);
	persistent_ref = key_create_persistent(ns, uid, &index_key);
	up_ग_लिखो(&ns->keyring_sem);
	अगर (!IS_ERR(persistent_ref))
		जाओ found;

	वापस PTR_ERR(persistent_ref);

found:
	ret = key_task_permission(persistent_ref, current_cred(), KEY_NEED_LINK);
	अगर (ret == 0) अणु
		persistent = key_ref_to_ptr(persistent_ref);
		ret = key_link(key_ref_to_ptr(dest_ref), persistent);
		अगर (ret == 0) अणु
			key_set_समयout(persistent, persistent_keyring_expiry);
			ret = persistent->serial;
		पूर्ण
	पूर्ण

	key_ref_put(persistent_ref);
	वापस ret;
पूर्ण

/*
 * Get the persistent keyring क्रम a specअगरic UID and link it to the nominated
 * keyring.
 */
दीर्घ keyctl_get_persistent(uid_t _uid, key_serial_t destid)
अणु
	काष्ठा user_namespace *ns = current_user_ns();
	key_ref_t dest_ref;
	kuid_t uid;
	दीर्घ ret;

	/* -1 indicates the current user */
	अगर (_uid == (uid_t)-1) अणु
		uid = current_uid();
	पूर्ण अन्यथा अणु
		uid = make_kuid(ns, _uid);
		अगर (!uid_valid(uid))
			वापस -EINVAL;

		/* You can only see your own persistent cache अगर you're not
		 * sufficiently privileged.
		 */
		अगर (!uid_eq(uid, current_uid()) &&
		    !uid_eq(uid, current_euid()) &&
		    !ns_capable(ns, CAP_SETUID))
			वापस -EPERM;
	पूर्ण

	/* There must be a destination keyring */
	dest_ref = lookup_user_key(destid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
	अगर (IS_ERR(dest_ref))
		वापस PTR_ERR(dest_ref);
	अगर (key_ref_to_ptr(dest_ref)->type != &key_type_keyring) अणु
		ret = -ENOTसूची;
		जाओ out_put_dest;
	पूर्ण

	ret = key_get_persistent(ns, uid, dest_ref);

out_put_dest:
	key_ref_put(dest_ref);
	वापस ret;
पूर्ण
