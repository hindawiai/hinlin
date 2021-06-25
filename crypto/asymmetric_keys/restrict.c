<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Instantiate a खुला key crypto key from an X.509 Certअगरicate
 *
 * Copyright (C) 2012, 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "ASYM: "fmt
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <crypto/खुला_key.h>
#समावेश "asymmetric_keys.h"

अटल bool use_builtin_keys;
अटल काष्ठा asymmetric_key_id *ca_keyid;

#अगर_अघोषित MODULE
अटल काष्ठा अणु
	काष्ठा asymmetric_key_id id;
	अचिन्हित अक्षर data[10];
पूर्ण cakey;

अटल पूर्णांक __init ca_keys_setup(अक्षर *str)
अणु
	अगर (!str)		/* शेष प्रणाली keyring */
		वापस 1;

	अगर (म_भेदन(str, "id:", 3) == 0) अणु
		काष्ठा asymmetric_key_id *p = &cakey.id;
		माप_प्रकार hexlen = (म_माप(str) - 3) / 2;
		पूर्णांक ret;

		अगर (hexlen == 0 || hexlen > माप(cakey.data)) अणु
			pr_err("Missing or invalid ca_keys id\n");
			वापस 1;
		पूर्ण

		ret = __asymmetric_key_hex_to_key_id(str + 3, p, hexlen);
		अगर (ret < 0)
			pr_err("Unparsable ca_keys id hex string\n");
		अन्यथा
			ca_keyid = p;	/* owner key 'id:xxxxxx' */
	पूर्ण अन्यथा अगर (म_भेद(str, "builtin") == 0) अणु
		use_builtin_keys = true;
	पूर्ण

	वापस 1;
पूर्ण
__setup("ca_keys=", ca_keys_setup);
#पूर्ण_अगर

/**
 * restrict_link_by_signature - Restrict additions to a ring of खुला keys
 * @dest_keyring: Keyring being linked to.
 * @type: The type of key being added.
 * @payload: The payload of the new key.
 * @trust_keyring: A ring of keys that can be used to vouch क्रम the new cert.
 *
 * Check the new certअगरicate against the ones in the trust keyring.  If one of
 * those is the signing key and validates the new certअगरicate, then mark the
 * new certअगरicate as being trusted.
 *
 * Returns 0 अगर the new certअगरicate was accepted, -ENOKEY अगर we couldn't find a
 * matching parent certअगरicate in the trusted list, -EKEYREJECTED अगर the
 * signature check fails or the key is blacklisted, -ENOPKG अगर the signature
 * uses unsupported crypto, or some other error अगर there is a matching
 * certअगरicate but the signature check cannot be perक्रमmed.
 */
पूर्णांक restrict_link_by_signature(काष्ठा key *dest_keyring,
			       स्थिर काष्ठा key_type *type,
			       स्थिर जोड़ key_payload *payload,
			       काष्ठा key *trust_keyring)
अणु
	स्थिर काष्ठा खुला_key_signature *sig;
	काष्ठा key *key;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	अगर (!trust_keyring)
		वापस -ENOKEY;

	अगर (type != &key_type_asymmetric)
		वापस -EOPNOTSUPP;

	sig = payload->data[asym_auth];
	अगर (!sig)
		वापस -ENOPKG;
	अगर (!sig->auth_ids[0] && !sig->auth_ids[1])
		वापस -ENOKEY;

	अगर (ca_keyid && !asymmetric_key_id_partial(sig->auth_ids[1], ca_keyid))
		वापस -EPERM;

	/* See अगर we have a key that चिन्हित this one. */
	key = find_asymmetric_key(trust_keyring,
				  sig->auth_ids[0], sig->auth_ids[1],
				  false);
	अगर (IS_ERR(key))
		वापस -ENOKEY;

	अगर (use_builtin_keys && !test_bit(KEY_FLAG_BUILTIN, &key->flags))
		ret = -ENOKEY;
	अन्यथा
		ret = verअगरy_signature(key, sig);
	key_put(key);
	वापस ret;
पूर्ण

अटल bool match_either_id(स्थिर काष्ठा asymmetric_key_ids *pair,
			    स्थिर काष्ठा asymmetric_key_id *single)
अणु
	वापस (asymmetric_key_id_same(pair->id[0], single) ||
		asymmetric_key_id_same(pair->id[1], single));
पूर्ण

अटल पूर्णांक key_or_keyring_common(काष्ठा key *dest_keyring,
				 स्थिर काष्ठा key_type *type,
				 स्थिर जोड़ key_payload *payload,
				 काष्ठा key *trusted, bool check_dest)
अणु
	स्थिर काष्ठा खुला_key_signature *sig;
	काष्ठा key *key = शून्य;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	अगर (!dest_keyring)
		वापस -ENOKEY;
	अन्यथा अगर (dest_keyring->type != &key_type_keyring)
		वापस -EOPNOTSUPP;

	अगर (!trusted && !check_dest)
		वापस -ENOKEY;

	अगर (type != &key_type_asymmetric)
		वापस -EOPNOTSUPP;

	sig = payload->data[asym_auth];
	अगर (!sig)
		वापस -ENOPKG;
	अगर (!sig->auth_ids[0] && !sig->auth_ids[1])
		वापस -ENOKEY;

	अगर (trusted) अणु
		अगर (trusted->type == &key_type_keyring) अणु
			/* See अगर we have a key that चिन्हित this one. */
			key = find_asymmetric_key(trusted, sig->auth_ids[0],
						  sig->auth_ids[1], false);
			अगर (IS_ERR(key))
				key = शून्य;
		पूर्ण अन्यथा अगर (trusted->type == &key_type_asymmetric) अणु
			स्थिर काष्ठा asymmetric_key_ids *signer_ids;

			signer_ids = asymmetric_key_ids(trusted);

			/*
			 * The auth_ids come from the candidate key (the
			 * one that is being considered क्रम addition to
			 * dest_keyring) and identअगरy the key that was
			 * used to sign.
			 *
			 * The signer_ids are identअगरiers क्रम the
			 * signing key specअगरied क्रम dest_keyring.
			 *
			 * The first auth_id is the preferred id, and
			 * the second is the fallback. If only one
			 * auth_id is present, it may match against
			 * either signer_id. If two auth_ids are
			 * present, the first auth_id must match one
			 * signer_id and the second auth_id must match
			 * the second signer_id.
			 */
			अगर (!sig->auth_ids[0] || !sig->auth_ids[1]) अणु
				स्थिर काष्ठा asymmetric_key_id *auth_id;

				auth_id = sig->auth_ids[0] ?: sig->auth_ids[1];
				अगर (match_either_id(signer_ids, auth_id))
					key = __key_get(trusted);

			पूर्ण अन्यथा अगर (asymmetric_key_id_same(signer_ids->id[1],
							  sig->auth_ids[1]) &&
				   match_either_id(signer_ids,
						   sig->auth_ids[0])) अणु
				key = __key_get(trusted);
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (check_dest && !key) अणु
		/* See अगर the destination has a key that चिन्हित this one. */
		key = find_asymmetric_key(dest_keyring, sig->auth_ids[0],
					  sig->auth_ids[1], false);
		अगर (IS_ERR(key))
			key = शून्य;
	पूर्ण

	अगर (!key)
		वापस -ENOKEY;

	ret = key_validate(key);
	अगर (ret == 0)
		ret = verअगरy_signature(key, sig);

	key_put(key);
	वापस ret;
पूर्ण

/**
 * restrict_link_by_key_or_keyring - Restrict additions to a ring of खुला
 * keys using the restrict_key inक्रमmation stored in the ring.
 * @dest_keyring: Keyring being linked to.
 * @type: The type of key being added.
 * @payload: The payload of the new key.
 * @trusted: A key or ring of keys that can be used to vouch क्रम the new cert.
 *
 * Check the new certअगरicate only against the key or keys passed in the data
 * parameter. If one of those is the signing key and validates the new
 * certअगरicate, then mark the new certअगरicate as being ok to link.
 *
 * Returns 0 अगर the new certअगरicate was accepted, -ENOKEY अगर we
 * couldn't find a matching parent certअगरicate in the trusted list,
 * -EKEYREJECTED अगर the signature check fails, -ENOPKG अगर the signature uses
 * unsupported crypto, or some other error अगर there is a matching certअगरicate
 * but the signature check cannot be perक्रमmed.
 */
पूर्णांक restrict_link_by_key_or_keyring(काष्ठा key *dest_keyring,
				    स्थिर काष्ठा key_type *type,
				    स्थिर जोड़ key_payload *payload,
				    काष्ठा key *trusted)
अणु
	वापस key_or_keyring_common(dest_keyring, type, payload, trusted,
				     false);
पूर्ण

/**
 * restrict_link_by_key_or_keyring_chain - Restrict additions to a ring of
 * खुला keys using the restrict_key inक्रमmation stored in the ring.
 * @dest_keyring: Keyring being linked to.
 * @type: The type of key being added.
 * @payload: The payload of the new key.
 * @trusted: A key or ring of keys that can be used to vouch क्रम the new cert.
 *
 * Check the new certअगरicate against the key or keys passed in the data
 * parameter and against the keys alपढ़ोy linked to the destination keyring. If
 * one of those is the signing key and validates the new certअगरicate, then mark
 * the new certअगरicate as being ok to link.
 *
 * Returns 0 अगर the new certअगरicate was accepted, -ENOKEY अगर we
 * couldn't find a matching parent certअगरicate in the trusted list,
 * -EKEYREJECTED अगर the signature check fails, -ENOPKG अगर the signature uses
 * unsupported crypto, or some other error अगर there is a matching certअगरicate
 * but the signature check cannot be perक्रमmed.
 */
पूर्णांक restrict_link_by_key_or_keyring_chain(काष्ठा key *dest_keyring,
					  स्थिर काष्ठा key_type *type,
					  स्थिर जोड़ key_payload *payload,
					  काष्ठा key *trusted)
अणु
	वापस key_or_keyring_common(dest_keyring, type, payload, trusted,
				     true);
पूर्ण
