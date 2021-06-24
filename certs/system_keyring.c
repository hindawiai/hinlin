<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* System trusted keyring क्रम trusted खुला keys
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/verअगरication.h>
#समावेश <keys/asymmetric-type.h>
#समावेश <keys/प्रणाली_keyring.h>
#समावेश <crypto/pkcs7.h>
#समावेश "common.h"

अटल काष्ठा key *builtin_trusted_keys;
#अगर_घोषित CONFIG_SECONDARY_TRUSTED_KEYRING
अटल काष्ठा key *secondary_trusted_keys;
#पूर्ण_अगर
#अगर_घोषित CONFIG_INTEGRITY_PLATFORM_KEYRING
अटल काष्ठा key *platक्रमm_trusted_keys;
#पूर्ण_अगर

बाह्य __initस्थिर स्थिर u8 प्रणाली_certअगरicate_list[];
बाह्य __initस्थिर स्थिर अचिन्हित दीर्घ प्रणाली_certअगरicate_list_size;
बाह्य __initस्थिर स्थिर अचिन्हित दीर्घ module_cert_size;

/**
 * restrict_link_to_builtin_trusted - Restrict keyring addition by built in CA
 *
 * Restrict the addition of keys पूर्णांकo a keyring based on the key-to-be-added
 * being vouched क्रम by a key in the built in प्रणाली keyring.
 */
पूर्णांक restrict_link_by_builtin_trusted(काष्ठा key *dest_keyring,
				     स्थिर काष्ठा key_type *type,
				     स्थिर जोड़ key_payload *payload,
				     काष्ठा key *restriction_key)
अणु
	वापस restrict_link_by_signature(dest_keyring, type, payload,
					  builtin_trusted_keys);
पूर्ण

#अगर_घोषित CONFIG_SECONDARY_TRUSTED_KEYRING
/**
 * restrict_link_by_builtin_and_secondary_trusted - Restrict keyring
 *   addition by both builtin and secondary keyrings
 *
 * Restrict the addition of keys पूर्णांकo a keyring based on the key-to-be-added
 * being vouched क्रम by a key in either the built-in or the secondary प्रणाली
 * keyrings.
 */
पूर्णांक restrict_link_by_builtin_and_secondary_trusted(
	काष्ठा key *dest_keyring,
	स्थिर काष्ठा key_type *type,
	स्थिर जोड़ key_payload *payload,
	काष्ठा key *restrict_key)
अणु
	/* If we have a secondary trusted keyring, then that contains a link
	 * through to the builtin keyring and the search will follow that link.
	 */
	अगर (type == &key_type_keyring &&
	    dest_keyring == secondary_trusted_keys &&
	    payload == &builtin_trusted_keys->payload)
		/* Allow the builtin keyring to be added to the secondary */
		वापस 0;

	वापस restrict_link_by_signature(dest_keyring, type, payload,
					  secondary_trusted_keys);
पूर्ण

/**
 * Allocate a काष्ठा key_restriction क्रम the "builtin and secondary trust"
 * keyring. Only क्रम use in प्रणाली_trusted_keyring_init().
 */
अटल __init काष्ठा key_restriction *get_builtin_and_secondary_restriction(व्योम)
अणु
	काष्ठा key_restriction *restriction;

	restriction = kzalloc(माप(काष्ठा key_restriction), GFP_KERNEL);

	अगर (!restriction)
		panic("Can't allocate secondary trusted keyring restriction\n");

	restriction->check = restrict_link_by_builtin_and_secondary_trusted;

	वापस restriction;
पूर्ण
#पूर्ण_अगर

/*
 * Create the trusted keyrings
 */
अटल __init पूर्णांक प्रणाली_trusted_keyring_init(व्योम)
अणु
	pr_notice("Initialise system trusted keyrings\n");

	builtin_trusted_keys =
		keyring_alloc(".builtin_trusted_keys",
			      GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, current_cred(),
			      ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
			      KEY_USR_VIEW | KEY_USR_READ | KEY_USR_SEARCH),
			      KEY_ALLOC_NOT_IN_QUOTA,
			      शून्य, शून्य);
	अगर (IS_ERR(builtin_trusted_keys))
		panic("Can't allocate builtin trusted keyring\n");

#अगर_घोषित CONFIG_SECONDARY_TRUSTED_KEYRING
	secondary_trusted_keys =
		keyring_alloc(".secondary_trusted_keys",
			      GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, current_cred(),
			      ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
			       KEY_USR_VIEW | KEY_USR_READ | KEY_USR_SEARCH |
			       KEY_USR_WRITE),
			      KEY_ALLOC_NOT_IN_QUOTA,
			      get_builtin_and_secondary_restriction(),
			      शून्य);
	अगर (IS_ERR(secondary_trusted_keys))
		panic("Can't allocate secondary trusted keyring\n");

	अगर (key_link(secondary_trusted_keys, builtin_trusted_keys) < 0)
		panic("Can't link trusted keyrings\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * Must be initialised beक्रमe we try and load the keys पूर्णांकo the keyring.
 */
device_initcall(प्रणाली_trusted_keyring_init);

__init पूर्णांक load_module_cert(काष्ठा key *keyring)
अणु
	अगर (!IS_ENABLED(CONFIG_IMA_APPRAISE_MODSIG))
		वापस 0;

	pr_notice("Loading compiled-in module X.509 certificates\n");

	वापस load_certअगरicate_list(प्रणाली_certअगरicate_list, module_cert_size, keyring);
पूर्ण

/*
 * Load the compiled-in list of X.509 certअगरicates.
 */
अटल __init पूर्णांक load_प्रणाली_certअगरicate_list(व्योम)
अणु
	स्थिर u8 *p;
	अचिन्हित दीर्घ size;

	pr_notice("Loading compiled-in X.509 certificates\n");

#अगर_घोषित CONFIG_MODULE_SIG
	p = प्रणाली_certअगरicate_list;
	size = प्रणाली_certअगरicate_list_size;
#अन्यथा
	p = प्रणाली_certअगरicate_list + module_cert_size;
	size = प्रणाली_certअगरicate_list_size - module_cert_size;
#पूर्ण_अगर

	वापस load_certअगरicate_list(p, size, builtin_trusted_keys);
पूर्ण
late_initcall(load_प्रणाली_certअगरicate_list);

#अगर_घोषित CONFIG_SYSTEM_DATA_VERIFICATION

/**
 * verअगरy_pkcs7_message_sig - Verअगरy a PKCS#7-based signature on प्रणाली data.
 * @data: The data to be verअगरied (शून्य अगर expecting पूर्णांकernal data).
 * @len: Size of @data.
 * @pkcs7: The PKCS#7 message that is the signature.
 * @trusted_keys: Trusted keys to use (शून्य क्रम builtin trusted keys only,
 *					(व्योम *)1UL क्रम all trusted keys).
 * @usage: The use to which the key is being put.
 * @view_content: Callback to gain access to content.
 * @ctx: Context क्रम callback.
 */
पूर्णांक verअगरy_pkcs7_message_sig(स्थिर व्योम *data, माप_प्रकार len,
			     काष्ठा pkcs7_message *pkcs7,
			     काष्ठा key *trusted_keys,
			     क्रमागत key_being_used_क्रम usage,
			     पूर्णांक (*view_content)(व्योम *ctx,
						 स्थिर व्योम *data, माप_प्रकार len,
						 माप_प्रकार asn1hdrlen),
			     व्योम *ctx)
अणु
	पूर्णांक ret;

	/* The data should be detached - so we need to supply it. */
	अगर (data && pkcs7_supply_detached_data(pkcs7, data, len) < 0) अणु
		pr_err("PKCS#7 signature with non-detached data\n");
		ret = -EBADMSG;
		जाओ error;
	पूर्ण

	ret = pkcs7_verअगरy(pkcs7, usage);
	अगर (ret < 0)
		जाओ error;

	अगर (!trusted_keys) अणु
		trusted_keys = builtin_trusted_keys;
	पूर्ण अन्यथा अगर (trusted_keys == VERIFY_USE_SECONDARY_KEYRING) अणु
#अगर_घोषित CONFIG_SECONDARY_TRUSTED_KEYRING
		trusted_keys = secondary_trusted_keys;
#अन्यथा
		trusted_keys = builtin_trusted_keys;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (trusted_keys == VERIFY_USE_PLATFORM_KEYRING) अणु
#अगर_घोषित CONFIG_INTEGRITY_PLATFORM_KEYRING
		trusted_keys = platक्रमm_trusted_keys;
#अन्यथा
		trusted_keys = शून्य;
#पूर्ण_अगर
		अगर (!trusted_keys) अणु
			ret = -ENOKEY;
			pr_devel("PKCS#7 platform keyring is not available\n");
			जाओ error;
		पूर्ण

		ret = is_key_on_revocation_list(pkcs7);
		अगर (ret != -ENOKEY) अणु
			pr_devel("PKCS#7 platform key is on revocation list\n");
			जाओ error;
		पूर्ण
	पूर्ण
	ret = pkcs7_validate_trust(pkcs7, trusted_keys);
	अगर (ret < 0) अणु
		अगर (ret == -ENOKEY)
			pr_devel("PKCS#7 signature not signed with a trusted key\n");
		जाओ error;
	पूर्ण

	अगर (view_content) अणु
		माप_प्रकार asn1hdrlen;

		ret = pkcs7_get_content_data(pkcs7, &data, &len, &asn1hdrlen);
		अगर (ret < 0) अणु
			अगर (ret == -ENODATA)
				pr_devel("PKCS#7 message does not contain data\n");
			जाओ error;
		पूर्ण

		ret = view_content(ctx, data, len, asn1hdrlen);
	पूर्ण

error:
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

/**
 * verअगरy_pkcs7_signature - Verअगरy a PKCS#7-based signature on प्रणाली data.
 * @data: The data to be verअगरied (शून्य अगर expecting पूर्णांकernal data).
 * @len: Size of @data.
 * @raw_pkcs7: The PKCS#7 message that is the signature.
 * @pkcs7_len: The size of @raw_pkcs7.
 * @trusted_keys: Trusted keys to use (शून्य क्रम builtin trusted keys only,
 *					(व्योम *)1UL क्रम all trusted keys).
 * @usage: The use to which the key is being put.
 * @view_content: Callback to gain access to content.
 * @ctx: Context क्रम callback.
 */
पूर्णांक verअगरy_pkcs7_signature(स्थिर व्योम *data, माप_प्रकार len,
			   स्थिर व्योम *raw_pkcs7, माप_प्रकार pkcs7_len,
			   काष्ठा key *trusted_keys,
			   क्रमागत key_being_used_क्रम usage,
			   पूर्णांक (*view_content)(व्योम *ctx,
					       स्थिर व्योम *data, माप_प्रकार len,
					       माप_प्रकार asn1hdrlen),
			   व्योम *ctx)
अणु
	काष्ठा pkcs7_message *pkcs7;
	पूर्णांक ret;

	pkcs7 = pkcs7_parse_message(raw_pkcs7, pkcs7_len);
	अगर (IS_ERR(pkcs7))
		वापस PTR_ERR(pkcs7);

	ret = verअगरy_pkcs7_message_sig(data, len, pkcs7, trusted_keys, usage,
				       view_content, ctx);

	pkcs7_मुक्त_message(pkcs7);
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(verअगरy_pkcs7_signature);

#पूर्ण_अगर /* CONFIG_SYSTEM_DATA_VERIFICATION */

#अगर_घोषित CONFIG_INTEGRITY_PLATFORM_KEYRING
व्योम __init set_platक्रमm_trusted_keys(काष्ठा key *keyring)
अणु
	platक्रमm_trusted_keys = keyring;
पूर्ण
#पूर्ण_अगर
