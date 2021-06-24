<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Module signature handling.
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_MODULE_SIGNATURE_H
#घोषणा _LINUX_MODULE_SIGNATURE_H

#समावेश <linux/types.h>

/* In stripped ARM and x86-64 modules, ~ is surprisingly rare. */
#घोषणा MODULE_SIG_STRING "~Module signature appended~\n"

क्रमागत pkey_id_type अणु
	PKEY_ID_PGP,		/* OpenPGP generated key ID */
	PKEY_ID_X509,		/* X.509 arbitrary subjectKeyIdentअगरier */
	PKEY_ID_PKCS7,		/* Signature in PKCS#7 message */
पूर्ण;

/*
 * Module signature inक्रमmation block.
 *
 * The स्थिरituents of the signature section are, in order:
 *
 *	- Signer's name
 *	- Key identअगरier
 *	- Signature data
 *	- Inक्रमmation block
 */
काष्ठा module_signature अणु
	u8	algo;		/* Public-key crypto algorithm [0] */
	u8	hash;		/* Digest algorithm [0] */
	u8	id_type;	/* Key identअगरier type [PKEY_ID_PKCS7] */
	u8	signer_len;	/* Length of signer's name [0] */
	u8	key_id_len;	/* Length of key identअगरier [0] */
	u8	__pad[3];
	__be32	sig_len;	/* Length of signature data */
पूर्ण;

पूर्णांक mod_check_sig(स्थिर काष्ठा module_signature *ms, माप_प्रकार file_len,
		  स्थिर अक्षर *name);

#पूर्ण_अगर /* _LINUX_MODULE_SIGNATURE_H */
