<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Asymmetric Public-key cryptography key type पूर्णांकerface
 *
 * See Documentation/crypto/asymmetric-keys.rst
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _KEYS_ASYMMETRIC_TYPE_H
#घोषणा _KEYS_ASYMMETRIC_TYPE_H

#समावेश <linux/key-type.h>
#समावेश <linux/verअगरication.h>

बाह्य काष्ठा key_type key_type_asymmetric;

/*
 * The key payload is four words.  The asymmetric-type key uses them as
 * follows:
 */
क्रमागत asymmetric_payload_bits अणु
	asym_crypto,		/* The data representing the key */
	asym_subtype,		/* Poपूर्णांकer to an asymmetric_key_subtype काष्ठा */
	asym_key_ids,		/* Poपूर्णांकer to an asymmetric_key_ids काष्ठा */
	asym_auth		/* The key's authorisation (signature, parent key ID) */
पूर्ण;

/*
 * Identअगरiers क्रम an asymmetric key ID.  We have three ways of looking up a
 * key derived from an X.509 certअगरicate:
 *
 * (1) Serial Number & Issuer.  Non-optional.  This is the only valid way to
 *     map a PKCS#7 signature to an X.509 certअगरicate.
 *
 * (2) Issuer & Subject Unique IDs.  Optional.  These were the original way to
 *     match X.509 certअगरicates, but have fallen पूर्णांकo disuse in favour of (3).
 *
 * (3) Auth & Subject Key Identअगरiers.  Optional.  SKIDs are only provided on
 *     CA keys that are पूर्णांकended to sign other keys, so करोn't appear in end
 *     user certअगरicates unless क्रमced.
 *
 * We could also support an PGP key identअगरier, which is just a SHA1 sum of the
 * खुला key and certain parameters, but since we करोn't support PGP keys at
 * the moment, we shall ignore those.
 *
 * What we actually करो is provide a place where binary identअगरiers can be
 * stashed and then compare against them when checking क्रम an id match.
 */
काष्ठा asymmetric_key_id अणु
	अचिन्हित लघु	len;
	अचिन्हित अक्षर	data[];
पूर्ण;

काष्ठा asymmetric_key_ids अणु
	व्योम		*id[2];
पूर्ण;

बाह्य bool asymmetric_key_id_same(स्थिर काष्ठा asymmetric_key_id *kid1,
				   स्थिर काष्ठा asymmetric_key_id *kid2);

बाह्य bool asymmetric_key_id_partial(स्थिर काष्ठा asymmetric_key_id *kid1,
				      स्थिर काष्ठा asymmetric_key_id *kid2);

बाह्य काष्ठा asymmetric_key_id *asymmetric_key_generate_id(स्थिर व्योम *val_1,
							    माप_प्रकार len_1,
							    स्थिर व्योम *val_2,
							    माप_प्रकार len_2);
अटल अंतरभूत
स्थिर काष्ठा asymmetric_key_ids *asymmetric_key_ids(स्थिर काष्ठा key *key)
अणु
	वापस key->payload.data[asym_key_ids];
पूर्ण

अटल अंतरभूत
स्थिर काष्ठा खुला_key *asymmetric_key_खुला_key(स्थिर काष्ठा key *key)
अणु
	वापस key->payload.data[asym_crypto];
पूर्ण

बाह्य काष्ठा key *find_asymmetric_key(काष्ठा key *keyring,
				       स्थिर काष्ठा asymmetric_key_id *id_0,
				       स्थिर काष्ठा asymmetric_key_id *id_1,
				       bool partial);

/*
 * The payload is at the discretion of the subtype.
 */

#पूर्ण_अगर /* _KEYS_ASYMMETRIC_TYPE_H */
