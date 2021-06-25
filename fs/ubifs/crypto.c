<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "ubifs.h"

अटल पूर्णांक ubअगरs_crypt_get_context(काष्ठा inode *inode, व्योम *ctx, माप_प्रकार len)
अणु
	वापस ubअगरs_xattr_get(inode, UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT,
			       ctx, len);
पूर्ण

अटल पूर्णांक ubअगरs_crypt_set_context(काष्ठा inode *inode, स्थिर व्योम *ctx,
				   माप_प्रकार len, व्योम *fs_data)
अणु
	/*
	 * Creating an encryption context is करोne unlocked since we
	 * operate on a new inode which is not visible to other users
	 * at this poपूर्णांक. So, no need to check whether inode is locked.
	 */
	वापस ubअगरs_xattr_set(inode, UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT,
			       ctx, len, 0, false);
पूर्ण

अटल bool ubअगरs_crypt_empty_dir(काष्ठा inode *inode)
अणु
	वापस ubअगरs_check_dir_empty(inode) == 0;
पूर्ण

पूर्णांक ubअगरs_encrypt(स्थिर काष्ठा inode *inode, काष्ठा ubअगरs_data_node *dn,
		  अचिन्हित पूर्णांक in_len, अचिन्हित पूर्णांक *out_len, पूर्णांक block)
अणु
	काष्ठा ubअगरs_info *c = inode->i_sb->s_fs_info;
	व्योम *p = &dn->data;
	अचिन्हित पूर्णांक pad_len = round_up(in_len, UBIFS_CIPHER_BLOCK_SIZE);
	पूर्णांक err;

	ubअगरs_निश्चित(c, pad_len <= *out_len);
	dn->compr_size = cpu_to_le16(in_len);

	/* pad to full block cipher length */
	अगर (pad_len != in_len)
		स_रखो(p + in_len, 0, pad_len - in_len);

	err = fscrypt_encrypt_block_inplace(inode, virt_to_page(p), pad_len,
					    offset_in_page(p), block, GFP_NOFS);
	अगर (err) अणु
		ubअगरs_err(c, "fscrypt_encrypt_block_inplace() failed: %d", err);
		वापस err;
	पूर्ण
	*out_len = pad_len;

	वापस 0;
पूर्ण

पूर्णांक ubअगरs_decrypt(स्थिर काष्ठा inode *inode, काष्ठा ubअगरs_data_node *dn,
		  अचिन्हित पूर्णांक *out_len, पूर्णांक block)
अणु
	काष्ठा ubअगरs_info *c = inode->i_sb->s_fs_info;
	पूर्णांक err;
	अचिन्हित पूर्णांक clen = le16_to_cpu(dn->compr_size);
	अचिन्हित पूर्णांक dlen = *out_len;

	अगर (clen <= 0 || clen > UBIFS_BLOCK_SIZE || clen > dlen) अणु
		ubअगरs_err(c, "bad compr_size: %i", clen);
		वापस -EINVAL;
	पूर्ण

	ubअगरs_निश्चित(c, dlen <= UBIFS_BLOCK_SIZE);
	err = fscrypt_decrypt_block_inplace(inode, virt_to_page(&dn->data),
					    dlen, offset_in_page(&dn->data),
					    block);
	अगर (err) अणु
		ubअगरs_err(c, "fscrypt_decrypt_block_inplace() failed: %d", err);
		वापस err;
	पूर्ण
	*out_len = clen;

	वापस 0;
पूर्ण

स्थिर काष्ठा fscrypt_operations ubअगरs_crypt_operations = अणु
	.flags			= FS_CFLG_OWN_PAGES,
	.key_prefix		= "ubifs:",
	.get_context		= ubअगरs_crypt_get_context,
	.set_context		= ubअगरs_crypt_set_context,
	.empty_dir		= ubअगरs_crypt_empty_dir,
	.max_namelen		= UBIFS_MAX_NLEN,
पूर्ण;
