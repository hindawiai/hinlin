<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* keyctl kernel bits
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित __LINUX_KEYCTL_H
#घोषणा __LINUX_KEYCTL_H

#समावेश <uapi/linux/keyctl.h>

काष्ठा kernel_pkey_query अणु
	__u32		supported_ops;	/* Which ops are supported */
	__u32		key_size;	/* Size of the key in bits */
	__u16		max_data_size;	/* Maximum size of raw data to sign in bytes */
	__u16		max_sig_size;	/* Maximum size of signature in bytes */
	__u16		max_enc_size;	/* Maximum size of encrypted blob in bytes */
	__u16		max_dec_size;	/* Maximum size of decrypted blob in bytes */
पूर्ण;

क्रमागत kernel_pkey_operation अणु
	kernel_pkey_encrypt,
	kernel_pkey_decrypt,
	kernel_pkey_sign,
	kernel_pkey_verअगरy,
पूर्ण;

काष्ठा kernel_pkey_params अणु
	काष्ठा key	*key;
	स्थिर अक्षर	*encoding;	/* Encoding (eg. "oaep" or "raw" क्रम none) */
	स्थिर अक्षर	*hash_algo;	/* Digest algorithm used (eg. "sha1") or शून्य अगर N/A */
	अक्षर		*info;		/* Modअगरied info string to be released later */
	__u32		in_len;		/* Input data size */
	जोड़ अणु
		__u32	out_len;	/* Output buffer size (enc/dec/sign) */
		__u32	in2_len;	/* 2nd input data size (verअगरy) */
	पूर्ण;
	क्रमागत kernel_pkey_operation op : 8;
पूर्ण;

#पूर्ण_अगर /* __LINUX_KEYCTL_H */
