<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This contains functions क्रम filename crypto management
 *
 * Copyright (C) 2015, Google, Inc.
 * Copyright (C) 2015, Motorola Mobility
 *
 * Written by Uday Savagaonkar, 2014.
 * Modअगरied by Jaegeuk Kim, 2015.
 *
 * This has not yet undergone a rigorous security audit.
 */

#समावेश <linux/namei.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/skcipher.h>
#समावेश "fscrypt_private.h"

/*
 * काष्ठा fscrypt_nokey_name - identअगरier क्रम directory entry when key is असलent
 *
 * When userspace lists an encrypted directory without access to the key, the
 * fileप्रणाली must present a unique "no-key name" क्रम each filename that allows
 * it to find the directory entry again अगर requested.  Naively, that would just
 * mean using the ciphertext filenames.  However, since the ciphertext filenames
 * can contain illegal अक्षरacters ('\0' and '/'), they must be encoded in some
 * way.  We use base64.  But that can cause names to exceed NAME_MAX (255
 * bytes), so we also need to use a strong hash to abbreviate दीर्घ names.
 *
 * The fileप्रणाली may also need another kind of hash, the "dirhash", to quickly
 * find the directory entry.  Since fileप्रणालीs normally compute the dirhash
 * over the on-disk filename (i.e. the ciphertext), it's not computable from
 * no-key names that abbreviate the ciphertext using the strong hash to fit in
 * NAME_MAX.  It's also not computable if it's a keyed hash taken over the
 * plaपूर्णांकext (but it may still be available in the on-disk directory entry);
 * हालfolded directories use this type of dirhash.  At least in these हालs,
 * each no-key name must include the name's dirhash too.
 *
 * To meet all these requirements, we base64-encode the following
 * variable-length काष्ठाure.  It contains the dirhash, or 0's अगर the fileप्रणाली
 * didn't provide one; up to 149 bytes of the ciphertext name; and क्रम
 * ciphertexts दीर्घer than 149 bytes, also the SHA-256 of the reमुख्यing bytes.
 *
 * This ensures that each no-key name contains everything needed to find the
 * directory entry again, contains only legal अक्षरacters, करोesn't exceed
 * NAME_MAX, is unambiguous unless there's a SHA-256 collision, and that we only
 * take the perक्रमmance hit of SHA-256 on very दीर्घ filenames (which are rare).
 */
काष्ठा fscrypt_nokey_name अणु
	u32 dirhash[2];
	u8 bytes[149];
	u8 sha256[SHA256_DIGEST_SIZE];
पूर्ण; /* 189 bytes => 252 bytes base64-encoded, which is <= NAME_MAX (255) */

/*
 * Decoded size of max-size nokey name, i.e. a name that was abbreviated using
 * the strong hash and thus includes the 'sha256' field.  This isn't simply
 * माप(काष्ठा fscrypt_nokey_name), as the padding at the end isn't included.
 */
#घोषणा FSCRYPT_NOKEY_NAME_MAX	दुरत्वend(काष्ठा fscrypt_nokey_name, sha256)

अटल अंतरभूत bool fscrypt_is_करोt_करोtकरोt(स्थिर काष्ठा qstr *str)
अणु
	अगर (str->len == 1 && str->name[0] == '.')
		वापस true;

	अगर (str->len == 2 && str->name[0] == '.' && str->name[1] == '.')
		वापस true;

	वापस false;
पूर्ण

/**
 * fscrypt_fname_encrypt() - encrypt a filename
 * @inode: inode of the parent directory (क्रम regular filenames)
 *	   or of the symlink (क्रम symlink tarमाला_लो)
 * @iname: the filename to encrypt
 * @out: (output) the encrypted filename
 * @olen: size of the encrypted filename.  It must be at least @iname->len.
 *	  Any extra space is filled with NUL padding beक्रमe encryption.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_fname_encrypt(स्थिर काष्ठा inode *inode, स्थिर काष्ठा qstr *iname,
			  u8 *out, अचिन्हित पूर्णांक olen)
अणु
	काष्ठा skcipher_request *req = शून्य;
	DECLARE_CRYPTO_WAIT(रुको);
	स्थिर काष्ठा fscrypt_info *ci = inode->i_crypt_info;
	काष्ठा crypto_skcipher *tfm = ci->ci_enc_key.tfm;
	जोड़ fscrypt_iv iv;
	काष्ठा scatterlist sg;
	पूर्णांक res;

	/*
	 * Copy the filename to the output buffer क्रम encrypting in-place and
	 * pad it with the needed number of NUL bytes.
	 */
	अगर (WARN_ON(olen < iname->len))
		वापस -ENOBUFS;
	स_नकल(out, iname->name, iname->len);
	स_रखो(out + iname->len, 0, olen - iname->len);

	/* Initialize the IV */
	fscrypt_generate_iv(&iv, 0, ci);

	/* Set up the encryption request */
	req = skcipher_request_alloc(tfm, GFP_NOFS);
	अगर (!req)
		वापस -ENOMEM;
	skcipher_request_set_callback(req,
			CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
			crypto_req_करोne, &रुको);
	sg_init_one(&sg, out, olen);
	skcipher_request_set_crypt(req, &sg, &sg, olen, &iv);

	/* Do the encryption */
	res = crypto_रुको_req(crypto_skcipher_encrypt(req), &रुको);
	skcipher_request_मुक्त(req);
	अगर (res < 0) अणु
		fscrypt_err(inode, "Filename encryption failed: %d", res);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fname_decrypt() - decrypt a filename
 * @inode: inode of the parent directory (क्रम regular filenames)
 *	   or of the symlink (क्रम symlink tarमाला_लो)
 * @iname: the encrypted filename to decrypt
 * @oname: (output) the decrypted filename.  The caller must have allocated
 *	   enough space क्रम this, e.g. using fscrypt_fname_alloc_buffer().
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक fname_decrypt(स्थिर काष्ठा inode *inode,
			 स्थिर काष्ठा fscrypt_str *iname,
			 काष्ठा fscrypt_str *oname)
अणु
	काष्ठा skcipher_request *req = शून्य;
	DECLARE_CRYPTO_WAIT(रुको);
	काष्ठा scatterlist src_sg, dst_sg;
	स्थिर काष्ठा fscrypt_info *ci = inode->i_crypt_info;
	काष्ठा crypto_skcipher *tfm = ci->ci_enc_key.tfm;
	जोड़ fscrypt_iv iv;
	पूर्णांक res;

	/* Allocate request */
	req = skcipher_request_alloc(tfm, GFP_NOFS);
	अगर (!req)
		वापस -ENOMEM;
	skcipher_request_set_callback(req,
		CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
		crypto_req_करोne, &रुको);

	/* Initialize IV */
	fscrypt_generate_iv(&iv, 0, ci);

	/* Create decryption request */
	sg_init_one(&src_sg, iname->name, iname->len);
	sg_init_one(&dst_sg, oname->name, oname->len);
	skcipher_request_set_crypt(req, &src_sg, &dst_sg, iname->len, &iv);
	res = crypto_रुको_req(crypto_skcipher_decrypt(req), &रुको);
	skcipher_request_मुक्त(req);
	अगर (res < 0) अणु
		fscrypt_err(inode, "Filename decryption failed: %d", res);
		वापस res;
	पूर्ण

	oname->len = strnlen(oname->name, iname->len);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर lookup_table[65] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+,";

#घोषणा BASE64_CHARS(nbytes)	DIV_ROUND_UP((nbytes) * 4, 3)

/**
 * base64_encode() - base64-encode some bytes
 * @src: the bytes to encode
 * @len: number of bytes to encode
 * @dst: (output) the base64-encoded string.  Not NUL-terminated.
 *
 * Encodes the input string using अक्षरacters from the set [A-Za-z0-9+,].
 * The encoded string is roughly 4/3 बार the size of the input string.
 *
 * Return: length of the encoded string
 */
अटल पूर्णांक base64_encode(स्थिर u8 *src, पूर्णांक len, अक्षर *dst)
अणु
	पूर्णांक i, bits = 0, ac = 0;
	अक्षर *cp = dst;

	क्रम (i = 0; i < len; i++) अणु
		ac += src[i] << bits;
		bits += 8;
		करो अणु
			*cp++ = lookup_table[ac & 0x3f];
			ac >>= 6;
			bits -= 6;
		पूर्ण जबतक (bits >= 6);
	पूर्ण
	अगर (bits)
		*cp++ = lookup_table[ac & 0x3f];
	वापस cp - dst;
पूर्ण

अटल पूर्णांक base64_decode(स्थिर अक्षर *src, पूर्णांक len, u8 *dst)
अणु
	पूर्णांक i, bits = 0, ac = 0;
	स्थिर अक्षर *p;
	u8 *cp = dst;

	क्रम (i = 0; i < len; i++) अणु
		p = म_अक्षर(lookup_table, src[i]);
		अगर (p == शून्य || src[i] == 0)
			वापस -2;
		ac += (p - lookup_table) << bits;
		bits += 6;
		अगर (bits >= 8) अणु
			*cp++ = ac & 0xff;
			ac >>= 8;
			bits -= 8;
		पूर्ण
	पूर्ण
	अगर (ac)
		वापस -1;
	वापस cp - dst;
पूर्ण

bool fscrypt_fname_encrypted_size(स्थिर जोड़ fscrypt_policy *policy,
				  u32 orig_len, u32 max_len,
				  u32 *encrypted_len_ret)
अणु
	पूर्णांक padding = 4 << (fscrypt_policy_flags(policy) &
			    FSCRYPT_POLICY_FLAGS_PAD_MASK);
	u32 encrypted_len;

	अगर (orig_len > max_len)
		वापस false;
	encrypted_len = max(orig_len, (u32)FS_CRYPTO_BLOCK_SIZE);
	encrypted_len = round_up(encrypted_len, padding);
	*encrypted_len_ret = min(encrypted_len, max_len);
	वापस true;
पूर्ण

/**
 * fscrypt_fname_alloc_buffer() - allocate a buffer क्रम presented filenames
 * @max_encrypted_len: maximum length of encrypted filenames the buffer will be
 *		       used to present
 * @crypto_str: (output) buffer to allocate
 *
 * Allocate a buffer that is large enough to hold any decrypted or encoded
 * filename (null-terminated), क्रम the given maximum encrypted filename length.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_fname_alloc_buffer(u32 max_encrypted_len,
			       काष्ठा fscrypt_str *crypto_str)
अणु
	स्थिर u32 max_encoded_len = BASE64_CHARS(FSCRYPT_NOKEY_NAME_MAX);
	u32 max_presented_len;

	max_presented_len = max(max_encoded_len, max_encrypted_len);

	crypto_str->name = kदो_स्मृति(max_presented_len + 1, GFP_NOFS);
	अगर (!crypto_str->name)
		वापस -ENOMEM;
	crypto_str->len = max_presented_len;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fscrypt_fname_alloc_buffer);

/**
 * fscrypt_fname_मुक्त_buffer() - मुक्त a buffer क्रम presented filenames
 * @crypto_str: the buffer to मुक्त
 *
 * Free a buffer that was allocated by fscrypt_fname_alloc_buffer().
 */
व्योम fscrypt_fname_मुक्त_buffer(काष्ठा fscrypt_str *crypto_str)
अणु
	अगर (!crypto_str)
		वापस;
	kमुक्त(crypto_str->name);
	crypto_str->name = शून्य;
पूर्ण
EXPORT_SYMBOL(fscrypt_fname_मुक्त_buffer);

/**
 * fscrypt_fname_disk_to_usr() - convert an encrypted filename to
 *				 user-presentable क्रमm
 * @inode: inode of the parent directory (क्रम regular filenames)
 *	   or of the symlink (क्रम symlink tarमाला_लो)
 * @hash: first part of the name's dirhash, अगर applicable.  This only needs to
 *	  be provided अगर the filename is located in an indexed directory whose
 *	  encryption key may be unavailable.  Not needed क्रम symlink tarमाला_लो.
 * @minor_hash: second part of the name's dirhash, अगर applicable
 * @iname: encrypted filename to convert.  May also be "." or "..", which
 *	   aren't actually encrypted.
 * @oname: output buffer क्रम the user-presentable filename.  The caller must
 *	   have allocated enough space क्रम this, e.g. using
 *	   fscrypt_fname_alloc_buffer().
 *
 * If the key is available, we'll decrypt the disk name.  Otherwise, we'll
 * encode it क्रम presentation in fscrypt_nokey_name क्रमmat.
 * See काष्ठा fscrypt_nokey_name क्रम details.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_fname_disk_to_usr(स्थिर काष्ठा inode *inode,
			      u32 hash, u32 minor_hash,
			      स्थिर काष्ठा fscrypt_str *iname,
			      काष्ठा fscrypt_str *oname)
अणु
	स्थिर काष्ठा qstr qname = FSTR_TO_QSTR(iname);
	काष्ठा fscrypt_nokey_name nokey_name;
	u32 size; /* size of the unencoded no-key name */

	अगर (fscrypt_is_करोt_करोtकरोt(&qname)) अणु
		oname->name[0] = '.';
		oname->name[iname->len - 1] = '.';
		oname->len = iname->len;
		वापस 0;
	पूर्ण

	अगर (iname->len < FS_CRYPTO_BLOCK_SIZE)
		वापस -EUCLEAN;

	अगर (fscrypt_has_encryption_key(inode))
		वापस fname_decrypt(inode, iname, oname);

	/*
	 * Sanity check that काष्ठा fscrypt_nokey_name करोesn't have padding
	 * between fields and that its encoded size never exceeds NAME_MAX.
	 */
	BUILD_BUG_ON(दुरत्वend(काष्ठा fscrypt_nokey_name, dirhash) !=
		     दुरत्व(काष्ठा fscrypt_nokey_name, bytes));
	BUILD_BUG_ON(दुरत्वend(काष्ठा fscrypt_nokey_name, bytes) !=
		     दुरत्व(काष्ठा fscrypt_nokey_name, sha256));
	BUILD_BUG_ON(BASE64_CHARS(FSCRYPT_NOKEY_NAME_MAX) > NAME_MAX);

	अगर (hash) अणु
		nokey_name.dirhash[0] = hash;
		nokey_name.dirhash[1] = minor_hash;
	पूर्ण अन्यथा अणु
		nokey_name.dirhash[0] = 0;
		nokey_name.dirhash[1] = 0;
	पूर्ण
	अगर (iname->len <= माप(nokey_name.bytes)) अणु
		स_नकल(nokey_name.bytes, iname->name, iname->len);
		size = दुरत्व(काष्ठा fscrypt_nokey_name, bytes[iname->len]);
	पूर्ण अन्यथा अणु
		स_नकल(nokey_name.bytes, iname->name, माप(nokey_name.bytes));
		/* Compute strong hash of reमुख्यing part of name. */
		sha256(&iname->name[माप(nokey_name.bytes)],
		       iname->len - माप(nokey_name.bytes),
		       nokey_name.sha256);
		size = FSCRYPT_NOKEY_NAME_MAX;
	पूर्ण
	oname->len = base64_encode((स्थिर u8 *)&nokey_name, size, oname->name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fscrypt_fname_disk_to_usr);

/**
 * fscrypt_setup_filename() - prepare to search a possibly encrypted directory
 * @dir: the directory that will be searched
 * @iname: the user-provided filename being searched क्रम
 * @lookup: 1 अगर we're allowed to proceed without the key because it's
 *	->lookup() or we're finding the dir_entry क्रम deletion; 0 अगर we cannot
 *	proceed without the key because we're going to create the dir_entry.
 * @fname: the filename inक्रमmation to be filled in
 *
 * Given a user-provided filename @iname, this function sets @fname->disk_name
 * to the name that would be stored in the on-disk directory entry, अगर possible.
 * If the directory is unencrypted this is simply @iname.  Else, अगर we have the
 * directory's encryption key, then @iname is the plaपूर्णांकext, so we encrypt it to
 * get the disk_name.
 *
 * Else, क्रम keyless @lookup operations, @iname should be a no-key name, so we
 * decode it to get the काष्ठा fscrypt_nokey_name.  Non-@lookup operations will
 * be impossible in this हाल, so we fail them with ENOKEY.
 *
 * If successful, fscrypt_मुक्त_filename() must be called later to clean up.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक fscrypt_setup_filename(काष्ठा inode *dir, स्थिर काष्ठा qstr *iname,
			      पूर्णांक lookup, काष्ठा fscrypt_name *fname)
अणु
	काष्ठा fscrypt_nokey_name *nokey_name;
	पूर्णांक ret;

	स_रखो(fname, 0, माप(काष्ठा fscrypt_name));
	fname->usr_fname = iname;

	अगर (!IS_ENCRYPTED(dir) || fscrypt_is_करोt_करोtकरोt(iname)) अणु
		fname->disk_name.name = (अचिन्हित अक्षर *)iname->name;
		fname->disk_name.len = iname->len;
		वापस 0;
	पूर्ण
	ret = fscrypt_get_encryption_info(dir, lookup);
	अगर (ret)
		वापस ret;

	अगर (fscrypt_has_encryption_key(dir)) अणु
		अगर (!fscrypt_fname_encrypted_size(&dir->i_crypt_info->ci_policy,
						  iname->len,
						  dir->i_sb->s_cop->max_namelen,
						  &fname->crypto_buf.len))
			वापस -ENAMETOOLONG;
		fname->crypto_buf.name = kदो_स्मृति(fname->crypto_buf.len,
						 GFP_NOFS);
		अगर (!fname->crypto_buf.name)
			वापस -ENOMEM;

		ret = fscrypt_fname_encrypt(dir, iname, fname->crypto_buf.name,
					    fname->crypto_buf.len);
		अगर (ret)
			जाओ errout;
		fname->disk_name.name = fname->crypto_buf.name;
		fname->disk_name.len = fname->crypto_buf.len;
		वापस 0;
	पूर्ण
	अगर (!lookup)
		वापस -ENOKEY;
	fname->is_nokey_name = true;

	/*
	 * We करोn't have the key and we are करोing a lookup; decode the
	 * user-supplied name
	 */

	अगर (iname->len > BASE64_CHARS(FSCRYPT_NOKEY_NAME_MAX))
		वापस -ENOENT;

	fname->crypto_buf.name = kदो_स्मृति(FSCRYPT_NOKEY_NAME_MAX, GFP_KERNEL);
	अगर (fname->crypto_buf.name == शून्य)
		वापस -ENOMEM;

	ret = base64_decode(iname->name, iname->len, fname->crypto_buf.name);
	अगर (ret < (पूर्णांक)दुरत्व(काष्ठा fscrypt_nokey_name, bytes[1]) ||
	    (ret > दुरत्व(काष्ठा fscrypt_nokey_name, sha256) &&
	     ret != FSCRYPT_NOKEY_NAME_MAX)) अणु
		ret = -ENOENT;
		जाओ errout;
	पूर्ण
	fname->crypto_buf.len = ret;

	nokey_name = (व्योम *)fname->crypto_buf.name;
	fname->hash = nokey_name->dirhash[0];
	fname->minor_hash = nokey_name->dirhash[1];
	अगर (ret != FSCRYPT_NOKEY_NAME_MAX) अणु
		/* The full ciphertext filename is available. */
		fname->disk_name.name = nokey_name->bytes;
		fname->disk_name.len =
			ret - दुरत्व(काष्ठा fscrypt_nokey_name, bytes);
	पूर्ण
	वापस 0;

errout:
	kमुक्त(fname->crypto_buf.name);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(fscrypt_setup_filename);

/**
 * fscrypt_match_name() - test whether the given name matches a directory entry
 * @fname: the name being searched क्रम
 * @de_name: the name from the directory entry
 * @de_name_len: the length of @de_name in bytes
 *
 * Normally @fname->disk_name will be set, and in that हाल we simply compare
 * that to the name stored in the directory entry.  The only exception is that
 * अगर we करोn't have the key for an encrypted directory and the name we're
 * looking क्रम is very दीर्घ, then we won't have the full disk_name and instead
 * we'll need to match against a fscrypt_nokey_name that includes a strong hash.
 *
 * Return: %true अगर the name matches, otherwise %false.
 */
bool fscrypt_match_name(स्थिर काष्ठा fscrypt_name *fname,
			स्थिर u8 *de_name, u32 de_name_len)
अणु
	स्थिर काष्ठा fscrypt_nokey_name *nokey_name =
		(स्थिर व्योम *)fname->crypto_buf.name;
	u8 digest[SHA256_DIGEST_SIZE];

	अगर (likely(fname->disk_name.name)) अणु
		अगर (de_name_len != fname->disk_name.len)
			वापस false;
		वापस !स_भेद(de_name, fname->disk_name.name, de_name_len);
	पूर्ण
	अगर (de_name_len <= माप(nokey_name->bytes))
		वापस false;
	अगर (स_भेद(de_name, nokey_name->bytes, माप(nokey_name->bytes)))
		वापस false;
	sha256(&de_name[माप(nokey_name->bytes)],
	       de_name_len - माप(nokey_name->bytes), digest);
	वापस !स_भेद(digest, nokey_name->sha256, माप(digest));
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_match_name);

/**
 * fscrypt_fname_siphash() - calculate the SipHash of a filename
 * @dir: the parent directory
 * @name: the filename to calculate the SipHash of
 *
 * Given a plaपूर्णांकext filename @name and a directory @dir which uses SipHash as
 * its dirhash method and has had its fscrypt key set up, this function
 * calculates the SipHash of that name using the directory's secret dirhash key.
 *
 * Return: the SipHash of @name using the hash key of @dir
 */
u64 fscrypt_fname_siphash(स्थिर काष्ठा inode *dir, स्थिर काष्ठा qstr *name)
अणु
	स्थिर काष्ठा fscrypt_info *ci = dir->i_crypt_info;

	WARN_ON(!ci->ci_dirhash_key_initialized);

	वापस siphash(name->name, name->len, &ci->ci_dirhash_key);
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_fname_siphash);

/*
 * Validate dentries in encrypted directories to make sure we aren't potentially
 * caching stale dentries after a key has been added.
 */
पूर्णांक fscrypt_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dir;
	पूर्णांक err;
	पूर्णांक valid;

	/*
	 * Plaपूर्णांकext names are always valid, since fscrypt करोesn't support
	 * reverting to no-key names without evicting the directory's inode
	 * -- which implies eviction of the dentries in the directory.
	 */
	अगर (!(dentry->d_flags & DCACHE_NOKEY_NAME))
		वापस 1;

	/*
	 * No-key name; valid अगर the directory's key is still unavailable.
	 *
	 * Although fscrypt क्रमbids नाम() on no-key names, we still must use
	 * dget_parent() here rather than use ->d_parent directly.  That's
	 * because a corrupted fs image may contain directory hard links, which
	 * the VFS handles by moving the directory's dentry tree in the dcache
	 * each समय ->lookup() finds the directory and it alपढ़ोy has a dentry
	 * अन्यथाwhere.  Thus ->d_parent can be changing, and we must safely grab
	 * a reference to some ->d_parent to prevent it from being मुक्तd.
	 */

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	dir = dget_parent(dentry);
	/*
	 * Pass allow_unsupported=true, so that files with an unsupported
	 * encryption policy can be deleted.
	 */
	err = fscrypt_get_encryption_info(d_inode(dir), true);
	valid = !fscrypt_has_encryption_key(d_inode(dir));
	dput(dir);

	अगर (err < 0)
		वापस err;

	वापस valid;
पूर्ण
EXPORT_SYMBOL_GPL(fscrypt_d_revalidate);
