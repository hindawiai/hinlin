<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ENCRYPTED_KEY_H
#घोषणा __ENCRYPTED_KEY_H

#घोषणा ENCRYPTED_DEBUG 0
#अगर defined(CONFIG_TRUSTED_KEYS) || \
  (defined(CONFIG_TRUSTED_KEYS_MODULE) && defined(CONFIG_ENCRYPTED_KEYS_MODULE))
बाह्य काष्ठा key *request_trusted_key(स्थिर अक्षर *trusted_desc,
				       स्थिर u8 **master_key, माप_प्रकार *master_keylen);
#अन्यथा
अटल अंतरभूत काष्ठा key *request_trusted_key(स्थिर अक्षर *trusted_desc,
					      स्थिर u8 **master_key,
					      माप_प्रकार *master_keylen)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण
#पूर्ण_अगर

#अगर ENCRYPTED_DEBUG
अटल अंतरभूत व्योम dump_master_key(स्थिर u8 *master_key, माप_प्रकार master_keylen)
अणु
	prपूर्णांक_hex_dump(KERN_ERR, "master key: ", DUMP_PREFIX_NONE, 32, 1,
		       master_key, master_keylen, 0);
पूर्ण

अटल अंतरभूत व्योम dump_decrypted_data(काष्ठा encrypted_key_payload *epayload)
अणु
	prपूर्णांक_hex_dump(KERN_ERR, "decrypted data: ", DUMP_PREFIX_NONE, 32, 1,
		       epayload->decrypted_data,
		       epayload->decrypted_datalen, 0);
पूर्ण

अटल अंतरभूत व्योम dump_encrypted_data(काष्ठा encrypted_key_payload *epayload,
				       अचिन्हित पूर्णांक encrypted_datalen)
अणु
	prपूर्णांक_hex_dump(KERN_ERR, "encrypted data: ", DUMP_PREFIX_NONE, 32, 1,
		       epayload->encrypted_data, encrypted_datalen, 0);
पूर्ण

अटल अंतरभूत व्योम dump_hmac(स्थिर अक्षर *str, स्थिर u8 *digest,
			     अचिन्हित पूर्णांक hmac_size)
अणु
	अगर (str)
		pr_info("encrypted_key: %s", str);
	prपूर्णांक_hex_dump(KERN_ERR, "hmac: ", DUMP_PREFIX_NONE, 32, 1, digest,
		       hmac_size, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dump_master_key(स्थिर u8 *master_key, माप_प्रकार master_keylen)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_decrypted_data(काष्ठा encrypted_key_payload *epayload)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_encrypted_data(काष्ठा encrypted_key_payload *epayload,
				       अचिन्हित पूर्णांक encrypted_datalen)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_hmac(स्थिर अक्षर *str, स्थिर u8 *digest,
			     अचिन्हित पूर्णांक hmac_size)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
