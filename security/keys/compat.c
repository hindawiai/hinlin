<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 32-bit compatibility syscall क्रम 64-bit प्रणालीs
 *
 * Copyright (C) 2004-5 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/compat.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

/*
 * The key control प्रणाली call, 32-bit compatibility version क्रम 64-bit archs
 */
COMPAT_SYSCALL_DEFINE5(keyctl, u32, option,
		       u32, arg2, u32, arg3, u32, arg4, u32, arg5)
अणु
	चयन (option) अणु
	हाल KEYCTL_GET_KEYRING_ID:
		वापस keyctl_get_keyring_ID(arg2, arg3);

	हाल KEYCTL_JOIN_SESSION_KEYRING:
		वापस keyctl_join_session_keyring(compat_ptr(arg2));

	हाल KEYCTL_UPDATE:
		वापस keyctl_update_key(arg2, compat_ptr(arg3), arg4);

	हाल KEYCTL_REVOKE:
		वापस keyctl_revoke_key(arg2);

	हाल KEYCTL_DESCRIBE:
		वापस keyctl_describe_key(arg2, compat_ptr(arg3), arg4);

	हाल KEYCTL_CLEAR:
		वापस keyctl_keyring_clear(arg2);

	हाल KEYCTL_LINK:
		वापस keyctl_keyring_link(arg2, arg3);

	हाल KEYCTL_UNLINK:
		वापस keyctl_keyring_unlink(arg2, arg3);

	हाल KEYCTL_SEARCH:
		वापस keyctl_keyring_search(arg2, compat_ptr(arg3),
					     compat_ptr(arg4), arg5);

	हाल KEYCTL_READ:
		वापस keyctl_पढ़ो_key(arg2, compat_ptr(arg3), arg4);

	हाल KEYCTL_CHOWN:
		वापस keyctl_chown_key(arg2, arg3, arg4);

	हाल KEYCTL_SETPERM:
		वापस keyctl_setperm_key(arg2, arg3);

	हाल KEYCTL_INSTANTIATE:
		वापस keyctl_instantiate_key(arg2, compat_ptr(arg3), arg4,
					      arg5);

	हाल KEYCTL_NEGATE:
		वापस keyctl_negate_key(arg2, arg3, arg4);

	हाल KEYCTL_SET_REQKEY_KEYRING:
		वापस keyctl_set_reqkey_keyring(arg2);

	हाल KEYCTL_SET_TIMEOUT:
		वापस keyctl_set_समयout(arg2, arg3);

	हाल KEYCTL_ASSUME_AUTHORITY:
		वापस keyctl_assume_authority(arg2);

	हाल KEYCTL_GET_SECURITY:
		वापस keyctl_get_security(arg2, compat_ptr(arg3), arg4);

	हाल KEYCTL_SESSION_TO_PARENT:
		वापस keyctl_session_to_parent();

	हाल KEYCTL_REJECT:
		वापस keyctl_reject_key(arg2, arg3, arg4, arg5);

	हाल KEYCTL_INSTANTIATE_IOV:
		वापस keyctl_instantiate_key_iov(arg2, compat_ptr(arg3), arg4,
						  arg5);

	हाल KEYCTL_INVALIDATE:
		वापस keyctl_invalidate_key(arg2);

	हाल KEYCTL_GET_PERSISTENT:
		वापस keyctl_get_persistent(arg2, arg3);

	हाल KEYCTL_DH_COMPUTE:
		वापस compat_keyctl_dh_compute(compat_ptr(arg2),
						compat_ptr(arg3),
						arg4, compat_ptr(arg5));

	हाल KEYCTL_RESTRICT_KEYRING:
		वापस keyctl_restrict_keyring(arg2, compat_ptr(arg3),
					       compat_ptr(arg4));

	हाल KEYCTL_PKEY_QUERY:
		अगर (arg3 != 0)
			वापस -EINVAL;
		वापस keyctl_pkey_query(arg2,
					 compat_ptr(arg4),
					 compat_ptr(arg5));

	हाल KEYCTL_PKEY_ENCRYPT:
	हाल KEYCTL_PKEY_DECRYPT:
	हाल KEYCTL_PKEY_SIGN:
		वापस keyctl_pkey_e_d_s(option,
					 compat_ptr(arg2), compat_ptr(arg3),
					 compat_ptr(arg4), compat_ptr(arg5));

	हाल KEYCTL_PKEY_VERIFY:
		वापस keyctl_pkey_verअगरy(compat_ptr(arg2), compat_ptr(arg3),
					  compat_ptr(arg4), compat_ptr(arg5));

	हाल KEYCTL_MOVE:
		वापस keyctl_keyring_move(arg2, arg3, arg4, arg5);

	हाल KEYCTL_CAPABILITIES:
		वापस keyctl_capabilities(compat_ptr(arg2), arg3);

	हाल KEYCTL_WATCH_KEY:
		वापस keyctl_watch_key(arg2, arg3, arg4);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
