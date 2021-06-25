<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* System hash blacklist.
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "blacklist: "fmt
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/key.h>
#समावेश <linux/key-type.h>
#समावेश <linux/sched.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/err.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uidgid.h>
#समावेश <keys/प्रणाली_keyring.h>
#समावेश "blacklist.h"
#समावेश "common.h"

अटल काष्ठा key *blacklist_keyring;

#अगर_घोषित CONFIG_SYSTEM_REVOCATION_LIST
बाह्य __initस्थिर स्थिर u8 revocation_certअगरicate_list[];
बाह्य __initस्थिर स्थिर अचिन्हित दीर्घ revocation_certअगरicate_list_size;
#पूर्ण_अगर

/*
 * The description must be a type prefix, a colon and then an even number of
 * hex digits.  The hash is kept in the description.
 */
अटल पूर्णांक blacklist_vet_description(स्थिर अक्षर *desc)
अणु
	पूर्णांक n = 0;

	अगर (*desc == ':')
		वापस -EINVAL;
	क्रम (; *desc; desc++)
		अगर (*desc == ':')
			जाओ found_colon;
	वापस -EINVAL;

found_colon:
	desc++;
	क्रम (; *desc; desc++) अणु
		अगर (!है_षष्ठादशक(*desc) || है_बड़ा(*desc))
			वापस -EINVAL;
		n++;
	पूर्ण

	अगर (n == 0 || n & 1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * The hash to be blacklisted is expected to be in the description.  There will
 * be no payload.
 */
अटल पूर्णांक blacklist_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	अगर (prep->datalen > 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम blacklist_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
पूर्ण

अटल व्योम blacklist_describe(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, key->description);
पूर्ण

अटल काष्ठा key_type key_type_blacklist = अणु
	.name			= "blacklist",
	.vet_description	= blacklist_vet_description,
	.preparse		= blacklist_preparse,
	.मुक्त_preparse		= blacklist_मुक्त_preparse,
	.instantiate		= generic_key_instantiate,
	.describe		= blacklist_describe,
पूर्ण;

/**
 * mark_hash_blacklisted - Add a hash to the प्रणाली blacklist
 * @hash: The hash as a hex string with a type prefix (eg. "tbs:23aa429783")
 */
पूर्णांक mark_hash_blacklisted(स्थिर अक्षर *hash)
अणु
	key_ref_t key;

	key = key_create_or_update(make_key_ref(blacklist_keyring, true),
				   "blacklist",
				   hash,
				   शून्य,
				   0,
				   ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
				    KEY_USR_VIEW),
				   KEY_ALLOC_NOT_IN_QUOTA |
				   KEY_ALLOC_BUILT_IN);
	अगर (IS_ERR(key)) अणु
		pr_err("Problem blacklisting hash (%ld)\n", PTR_ERR(key));
		वापस PTR_ERR(key);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * is_hash_blacklisted - Determine अगर a hash is blacklisted
 * @hash: The hash to be checked as a binary blob
 * @hash_len: The length of the binary hash
 * @type: Type of hash
 */
पूर्णांक is_hash_blacklisted(स्थिर u8 *hash, माप_प्रकार hash_len, स्थिर अक्षर *type)
अणु
	key_ref_t kref;
	माप_प्रकार type_len = म_माप(type);
	अक्षर *buffer, *p;
	पूर्णांक ret = 0;

	buffer = kदो_स्मृति(type_len + 1 + hash_len * 2 + 1, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;
	p = स_नकल(buffer, type, type_len);
	p += type_len;
	*p++ = ':';
	bin2hex(p, hash, hash_len);
	p += hash_len * 2;
	*p = 0;

	kref = keyring_search(make_key_ref(blacklist_keyring, true),
			      &key_type_blacklist, buffer, false);
	अगर (!IS_ERR(kref)) अणु
		key_ref_put(kref);
		ret = -EKEYREJECTED;
	पूर्ण

	kमुक्त(buffer);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(is_hash_blacklisted);

पूर्णांक is_binary_blacklisted(स्थिर u8 *hash, माप_प्रकार hash_len)
अणु
	अगर (is_hash_blacklisted(hash, hash_len, "bin") == -EKEYREJECTED)
		वापस -EPERM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(is_binary_blacklisted);

#अगर_घोषित CONFIG_SYSTEM_REVOCATION_LIST
/**
 * add_key_to_revocation_list - Add a revocation certअगरicate to the blacklist
 * @data: The data blob containing the certअगरicate
 * @size: The size of data blob
 */
पूर्णांक add_key_to_revocation_list(स्थिर अक्षर *data, माप_प्रकार size)
अणु
	key_ref_t key;

	key = key_create_or_update(make_key_ref(blacklist_keyring, true),
				   "asymmetric",
				   शून्य,
				   data,
				   size,
				   ((KEY_POS_ALL & ~KEY_POS_SETATTR) | KEY_USR_VIEW),
				   KEY_ALLOC_NOT_IN_QUOTA | KEY_ALLOC_BUILT_IN);

	अगर (IS_ERR(key)) अणु
		pr_err("Problem with revocation key (%ld)\n", PTR_ERR(key));
		वापस PTR_ERR(key);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * is_key_on_revocation_list - Determine अगर the key क्रम a PKCS#7 message is revoked
 * @pkcs7: The PKCS#7 message to check
 */
पूर्णांक is_key_on_revocation_list(काष्ठा pkcs7_message *pkcs7)
अणु
	पूर्णांक ret;

	ret = pkcs7_validate_trust(pkcs7, blacklist_keyring);

	अगर (ret == 0)
		वापस -EKEYREJECTED;

	वापस -ENOKEY;
पूर्ण
#पूर्ण_अगर

/*
 * Initialise the blacklist
 */
अटल पूर्णांक __init blacklist_init(व्योम)
अणु
	स्थिर अक्षर *स्थिर *bl;

	अगर (रेजिस्टर_key_type(&key_type_blacklist) < 0)
		panic("Can't allocate system blacklist key type\n");

	blacklist_keyring =
		keyring_alloc(".blacklist",
			      GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, current_cred(),
			      (KEY_POS_ALL & ~KEY_POS_SETATTR) |
			      KEY_USR_VIEW | KEY_USR_READ |
			      KEY_USR_SEARCH,
			      KEY_ALLOC_NOT_IN_QUOTA |
			      KEY_ALLOC_SET_KEEP,
			      शून्य, शून्य);
	अगर (IS_ERR(blacklist_keyring))
		panic("Can't allocate system blacklist keyring\n");

	क्रम (bl = blacklist_hashes; *bl; bl++)
		अगर (mark_hash_blacklisted(*bl) < 0)
			pr_err("- blacklisting failed\n");
	वापस 0;
पूर्ण

/*
 * Must be initialised beक्रमe we try and load the keys पूर्णांकo the keyring.
 */
device_initcall(blacklist_init);

#अगर_घोषित CONFIG_SYSTEM_REVOCATION_LIST
/*
 * Load the compiled-in list of revocation X.509 certअगरicates.
 */
अटल __init पूर्णांक load_revocation_certअगरicate_list(व्योम)
अणु
	अगर (revocation_certअगरicate_list_size)
		pr_notice("Loading compiled-in revocation X.509 certificates\n");

	वापस load_certअगरicate_list(revocation_certअगरicate_list, revocation_certअगरicate_list_size,
				     blacklist_keyring);
पूर्ण
late_initcall(load_revocation_certअगरicate_list);
#पूर्ण_अगर
