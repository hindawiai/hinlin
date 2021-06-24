<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* System keyring containing trusted खुला keys.
 *
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _KEYS_SYSTEM_KEYRING_H
#घोषणा _KEYS_SYSTEM_KEYRING_H

#समावेश <linux/key.h>

#अगर_घोषित CONFIG_SYSTEM_TRUSTED_KEYRING

बाह्य पूर्णांक restrict_link_by_builtin_trusted(काष्ठा key *keyring,
					    स्थिर काष्ठा key_type *type,
					    स्थिर जोड़ key_payload *payload,
					    काष्ठा key *restriction_key);
बाह्य __init पूर्णांक load_module_cert(काष्ठा key *keyring);

#अन्यथा
#घोषणा restrict_link_by_builtin_trusted restrict_link_reject

अटल अंतरभूत __init पूर्णांक load_module_cert(काष्ठा key *keyring)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_SECONDARY_TRUSTED_KEYRING
बाह्य पूर्णांक restrict_link_by_builtin_and_secondary_trusted(
	काष्ठा key *keyring,
	स्थिर काष्ठा key_type *type,
	स्थिर जोड़ key_payload *payload,
	काष्ठा key *restriction_key);
#अन्यथा
#घोषणा restrict_link_by_builtin_and_secondary_trusted restrict_link_by_builtin_trusted
#पूर्ण_अगर

बाह्य काष्ठा pkcs7_message *pkcs7;
#अगर_घोषित CONFIG_SYSTEM_BLACKLIST_KEYRING
बाह्य पूर्णांक mark_hash_blacklisted(स्थिर अक्षर *hash);
बाह्य पूर्णांक is_hash_blacklisted(स्थिर u8 *hash, माप_प्रकार hash_len,
			       स्थिर अक्षर *type);
बाह्य पूर्णांक is_binary_blacklisted(स्थिर u8 *hash, माप_प्रकार hash_len);
#अन्यथा
अटल अंतरभूत पूर्णांक is_hash_blacklisted(स्थिर u8 *hash, माप_प्रकार hash_len,
				      स्थिर अक्षर *type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_binary_blacklisted(स्थिर u8 *hash, माप_प्रकार hash_len)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSTEM_REVOCATION_LIST
बाह्य पूर्णांक add_key_to_revocation_list(स्थिर अक्षर *data, माप_प्रकार size);
बाह्य पूर्णांक is_key_on_revocation_list(काष्ठा pkcs7_message *pkcs7);
#अन्यथा
अटल अंतरभूत पूर्णांक add_key_to_revocation_list(स्थिर अक्षर *data, माप_प्रकार size)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक is_key_on_revocation_list(काष्ठा pkcs7_message *pkcs7)
अणु
	वापस -ENOKEY;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IMA_BLACKLIST_KEYRING
बाह्य काष्ठा key *ima_blacklist_keyring;

अटल अंतरभूत काष्ठा key *get_ima_blacklist_keyring(व्योम)
अणु
	वापस ima_blacklist_keyring;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा key *get_ima_blacklist_keyring(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_IMA_BLACKLIST_KEYRING */

#अगर defined(CONFIG_INTEGRITY_PLATFORM_KEYRING) && \
	defined(CONFIG_SYSTEM_TRUSTED_KEYRING)
बाह्य व्योम __init set_platक्रमm_trusted_keys(काष्ठा key *keyring);
#अन्यथा
अटल अंतरभूत व्योम set_platक्रमm_trusted_keys(काष्ठा key *keyring)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _KEYS_SYSTEM_KEYRING_H */
