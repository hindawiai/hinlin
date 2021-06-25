<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Asymmetric खुला-key cryptography key subtype
 *
 * See Documentation/crypto/asymmetric-keys.rst
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _KEYS_ASYMMETRIC_SUBTYPE_H
#घोषणा _KEYS_ASYMMETRIC_SUBTYPE_H

#समावेश <linux/seq_file.h>
#समावेश <keys/asymmetric-type.h>

काष्ठा kernel_pkey_query;
काष्ठा kernel_pkey_params;
काष्ठा खुला_key_signature;

/*
 * Keys of this type declare a subtype that indicates the handlers and
 * capabilities.
 */
काष्ठा asymmetric_key_subtype अणु
	काष्ठा module		*owner;
	स्थिर अक्षर		*name;
	अचिन्हित लघु		name_len;	/* length of name */

	/* Describe a key of this subtype क्रम /proc/keys */
	व्योम (*describe)(स्थिर काष्ठा key *key, काष्ठा seq_file *m);

	/* Destroy a key of this subtype */
	व्योम (*destroy)(व्योम *payload_crypto, व्योम *payload_auth);

	पूर्णांक (*query)(स्थिर काष्ठा kernel_pkey_params *params,
		     काष्ठा kernel_pkey_query *info);

	/* Encrypt/decrypt/sign data */
	पूर्णांक (*eds_op)(काष्ठा kernel_pkey_params *params,
		      स्थिर व्योम *in, व्योम *out);

	/* Verअगरy the signature on a key of this subtype (optional) */
	पूर्णांक (*verअगरy_signature)(स्थिर काष्ठा key *key,
				स्थिर काष्ठा खुला_key_signature *sig);
पूर्ण;

/**
 * asymmetric_key_subtype - Get the subtype from an asymmetric key
 * @key: The key of पूर्णांकerest.
 *
 * Retrieves and वापसs the subtype poपूर्णांकer of the asymmetric key from the
 * type-specअगरic data attached to the key.
 */
अटल अंतरभूत
काष्ठा asymmetric_key_subtype *asymmetric_key_subtype(स्थिर काष्ठा key *key)
अणु
	वापस key->payload.data[asym_subtype];
पूर्ण

#पूर्ण_अगर /* _KEYS_ASYMMETRIC_SUBTYPE_H */
