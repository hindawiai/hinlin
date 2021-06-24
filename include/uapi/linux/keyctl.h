<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* keyctl.h: keyctl command IDs
 *
 * Copyright (C) 2004, 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _LINUX_KEYCTL_H
#घोषणा _LINUX_KEYCTL_H

#समावेश <linux/types.h>

/* special process keyring लघुcut IDs */
#घोषणा KEY_SPEC_THREAD_KEYRING		-1	/* - key ID क्रम thपढ़ो-specअगरic keyring */
#घोषणा KEY_SPEC_PROCESS_KEYRING	-2	/* - key ID क्रम process-specअगरic keyring */
#घोषणा KEY_SPEC_SESSION_KEYRING	-3	/* - key ID क्रम session-specअगरic keyring */
#घोषणा KEY_SPEC_USER_KEYRING		-4	/* - key ID क्रम UID-specअगरic keyring */
#घोषणा KEY_SPEC_USER_SESSION_KEYRING	-5	/* - key ID क्रम UID-session keyring */
#घोषणा KEY_SPEC_GROUP_KEYRING		-6	/* - key ID क्रम GID-specअगरic keyring */
#घोषणा KEY_SPEC_REQKEY_AUTH_KEY	-7	/* - key ID क्रम assumed request_key auth key */
#घोषणा KEY_SPEC_REQUESTOR_KEYRING	-8	/* - key ID क्रम request_key() dest keyring */

/* request-key शेष keyrings */
#घोषणा KEY_REQKEY_DEFL_NO_CHANGE		-1
#घोषणा KEY_REQKEY_DEFL_DEFAULT			0
#घोषणा KEY_REQKEY_DEFL_THREAD_KEYRING		1
#घोषणा KEY_REQKEY_DEFL_PROCESS_KEYRING		2
#घोषणा KEY_REQKEY_DEFL_SESSION_KEYRING		3
#घोषणा KEY_REQKEY_DEFL_USER_KEYRING		4
#घोषणा KEY_REQKEY_DEFL_USER_SESSION_KEYRING	5
#घोषणा KEY_REQKEY_DEFL_GROUP_KEYRING		6
#घोषणा KEY_REQKEY_DEFL_REQUESTOR_KEYRING	7

/* keyctl commands */
#घोषणा KEYCTL_GET_KEYRING_ID		0	/* ask क्रम a keyring's ID */
#घोषणा KEYCTL_JOIN_SESSION_KEYRING	1	/* join or start named session keyring */
#घोषणा KEYCTL_UPDATE			2	/* update a key */
#घोषणा KEYCTL_REVOKE			3	/* revoke a key */
#घोषणा KEYCTL_CHOWN			4	/* set ownership of a key */
#घोषणा KEYCTL_SETPERM			5	/* set perms on a key */
#घोषणा KEYCTL_DESCRIBE			6	/* describe a key */
#घोषणा KEYCTL_CLEAR			7	/* clear contents of a keyring */
#घोषणा KEYCTL_LINK			8	/* link a key पूर्णांकo a keyring */
#घोषणा KEYCTL_UNLINK			9	/* unlink a key from a keyring */
#घोषणा KEYCTL_SEARCH			10	/* search क्रम a key in a keyring */
#घोषणा KEYCTL_READ			11	/* पढ़ो a key or keyring's contents */
#घोषणा KEYCTL_INSTANTIATE		12	/* instantiate a partially स्थिरructed key */
#घोषणा KEYCTL_NEGATE			13	/* negate a partially स्थिरructed key */
#घोषणा KEYCTL_SET_REQKEY_KEYRING	14	/* set शेष request-key keyring */
#घोषणा KEYCTL_SET_TIMEOUT		15	/* set key समयout */
#घोषणा KEYCTL_ASSUME_AUTHORITY		16	/* assume request_key() authorisation */
#घोषणा KEYCTL_GET_SECURITY		17	/* get key security label */
#घोषणा KEYCTL_SESSION_TO_PARENT	18	/* apply session keyring to parent process */
#घोषणा KEYCTL_REJECT			19	/* reject a partially स्थिरructed key */
#घोषणा KEYCTL_INSTANTIATE_IOV		20	/* instantiate a partially स्थिरructed key */
#घोषणा KEYCTL_INVALIDATE		21	/* invalidate a key */
#घोषणा KEYCTL_GET_PERSISTENT		22	/* get a user's persistent keyring */
#घोषणा KEYCTL_DH_COMPUTE		23	/* Compute Dअगरfie-Hellman values */
#घोषणा KEYCTL_PKEY_QUERY		24	/* Query खुला key parameters */
#घोषणा KEYCTL_PKEY_ENCRYPT		25	/* Encrypt a blob using a खुला key */
#घोषणा KEYCTL_PKEY_DECRYPT		26	/* Decrypt a blob using a खुला key */
#घोषणा KEYCTL_PKEY_SIGN		27	/* Create a खुला key signature */
#घोषणा KEYCTL_PKEY_VERIFY		28	/* Verअगरy a खुला key signature */
#घोषणा KEYCTL_RESTRICT_KEYRING		29	/* Restrict keys allowed to link to a keyring */
#घोषणा KEYCTL_MOVE			30	/* Move keys between keyrings */
#घोषणा KEYCTL_CAPABILITIES		31	/* Find capabilities of keyrings subप्रणाली */
#घोषणा KEYCTL_WATCH_KEY		32	/* Watch a key or ring of keys क्रम changes */

/* keyctl काष्ठाures */
काष्ठा keyctl_dh_params अणु
	जोड़ अणु
#अगर_अघोषित __cplusplus
		__s32 निजी;
#पूर्ण_अगर
		__s32 priv;
	पूर्ण;
	__s32 prime;
	__s32 base;
पूर्ण;

काष्ठा keyctl_kdf_params अणु
	अक्षर __user *hashname;
	अक्षर __user *otherinfo;
	__u32 otherinfolen;
	__u32 __spare[8];
पूर्ण;

#घोषणा KEYCTL_SUPPORTS_ENCRYPT		0x01
#घोषणा KEYCTL_SUPPORTS_DECRYPT		0x02
#घोषणा KEYCTL_SUPPORTS_SIGN		0x04
#घोषणा KEYCTL_SUPPORTS_VERIFY		0x08

काष्ठा keyctl_pkey_query अणु
	__u32		supported_ops;	/* Which ops are supported */
	__u32		key_size;	/* Size of the key in bits */
	__u16		max_data_size;	/* Maximum size of raw data to sign in bytes */
	__u16		max_sig_size;	/* Maximum size of signature in bytes */
	__u16		max_enc_size;	/* Maximum size of encrypted blob in bytes */
	__u16		max_dec_size;	/* Maximum size of decrypted blob in bytes */
	__u32		__spare[10];
पूर्ण;

काष्ठा keyctl_pkey_params अणु
	__s32		key_id;		/* Serial no. of खुला key to use */
	__u32		in_len;		/* Input data size */
	जोड़ अणु
		__u32		out_len;	/* Output buffer size (encrypt/decrypt/sign) */
		__u32		in2_len;	/* 2nd input data size (verअगरy) */
	पूर्ण;
	__u32		__spare[7];
पूर्ण;

#घोषणा KEYCTL_MOVE_EXCL	0x00000001 /* Do not displace from the to-keyring */

/*
 * Capabilities flags.  The capabilities list is an array of 8-bit पूर्णांकegers;
 * each पूर्णांकeger can carry up to 8 flags.
 */
#घोषणा KEYCTL_CAPS0_CAPABILITIES	0x01 /* KEYCTL_CAPABILITIES supported */
#घोषणा KEYCTL_CAPS0_PERSISTENT_KEYRINGS 0x02 /* Persistent keyrings enabled */
#घोषणा KEYCTL_CAPS0_DIFFIE_HELLMAN	0x04 /* Dअगरfie-Hellman computation enabled */
#घोषणा KEYCTL_CAPS0_PUBLIC_KEY		0x08 /* Public key ops enabled */
#घोषणा KEYCTL_CAPS0_BIG_KEY		0x10 /* big_key-type enabled */
#घोषणा KEYCTL_CAPS0_INVALIDATE		0x20 /* KEYCTL_INVALIDATE supported */
#घोषणा KEYCTL_CAPS0_RESTRICT_KEYRING	0x40 /* KEYCTL_RESTRICT_KEYRING supported */
#घोषणा KEYCTL_CAPS0_MOVE		0x80 /* KEYCTL_MOVE supported */
#घोषणा KEYCTL_CAPS1_NS_KEYRING_NAME	0x01 /* Keyring names are per-user_namespace */
#घोषणा KEYCTL_CAPS1_NS_KEY_TAG		0x02 /* Key indexing can include a namespace tag */
#घोषणा KEYCTL_CAPS1_NOTIFICATIONS	0x04 /* Keys generate watchable notअगरications */

#पूर्ण_अगर /*  _LINUX_KEYCTL_H */
