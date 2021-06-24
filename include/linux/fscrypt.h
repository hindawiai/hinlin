<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fscrypt.h: declarations क्रम per-file encryption
 *
 * Fileप्रणालीs that implement per-file encryption must include this header
 * file.
 *
 * Copyright (C) 2015, Google, Inc.
 *
 * Written by Michael Halcrow, 2015.
 * Modअगरied by Jaegeuk Kim, 2015.
 */
#अगर_अघोषित _LINUX_FSCRYPT_H
#घोषणा _LINUX_FSCRYPT_H

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <uapi/linux/fscrypt.h>

#घोषणा FS_CRYPTO_BLOCK_SIZE		16

जोड़ fscrypt_policy;
काष्ठा fscrypt_info;
काष्ठा seq_file;

काष्ठा fscrypt_str अणु
	अचिन्हित अक्षर *name;
	u32 len;
पूर्ण;

काष्ठा fscrypt_name अणु
	स्थिर काष्ठा qstr *usr_fname;
	काष्ठा fscrypt_str disk_name;
	u32 hash;
	u32 minor_hash;
	काष्ठा fscrypt_str crypto_buf;
	bool is_nokey_name;
पूर्ण;

#घोषणा FSTR_INIT(n, l)		अणु .name = n, .len = l पूर्ण
#घोषणा FSTR_TO_QSTR(f)		QSTR_INIT((f)->name, (f)->len)
#घोषणा fname_name(p)		((p)->disk_name.name)
#घोषणा fname_len(p)		((p)->disk_name.len)

/* Maximum value क्रम the third parameter of fscrypt_operations.set_context(). */
#घोषणा FSCRYPT_SET_CONTEXT_MAX_SIZE	40

#अगर_घोषित CONFIG_FS_ENCRYPTION
/*
 * fscrypt superblock flags
 */
#घोषणा FS_CFLG_OWN_PAGES (1U << 1)

/*
 * crypto operations क्रम fileप्रणालीs
 */
काष्ठा fscrypt_operations अणु
	अचिन्हित पूर्णांक flags;
	स्थिर अक्षर *key_prefix;
	पूर्णांक (*get_context)(काष्ठा inode *inode, व्योम *ctx, माप_प्रकार len);
	पूर्णांक (*set_context)(काष्ठा inode *inode, स्थिर व्योम *ctx, माप_प्रकार len,
			   व्योम *fs_data);
	स्थिर जोड़ fscrypt_policy *(*get_dummy_policy)(काष्ठा super_block *sb);
	bool (*empty_dir)(काष्ठा inode *inode);
	अचिन्हित पूर्णांक max_namelen;
	bool (*has_stable_inodes)(काष्ठा super_block *sb);
	व्योम (*get_ino_and_lblk_bits)(काष्ठा super_block *sb,
				      पूर्णांक *ino_bits_ret, पूर्णांक *lblk_bits_ret);
	पूर्णांक (*get_num_devices)(काष्ठा super_block *sb);
	व्योम (*get_devices)(काष्ठा super_block *sb,
			    काष्ठा request_queue **devs);
पूर्ण;

अटल अंतरभूत काष्ठा fscrypt_info *fscrypt_get_info(स्थिर काष्ठा inode *inode)
अणु
	/*
	 * Pairs with the cmpxchg_release() in fscrypt_setup_encryption_info().
	 * I.e., another task may publish ->i_crypt_info concurrently, executing
	 * a RELEASE barrier.  We need to use smp_load_acquire() here to safely
	 * ACQUIRE the memory the other task published.
	 */
	वापस smp_load_acquire(&inode->i_crypt_info);
पूर्ण

/**
 * fscrypt_needs_contents_encryption() - check whether an inode needs
 *					 contents encryption
 * @inode: the inode to check
 *
 * Return: %true अगरf the inode is an encrypted regular file and the kernel was
 * built with fscrypt support.
 *
 * If you need to know whether the encrypt bit is set even when the kernel was
 * built without fscrypt support, you must use IS_ENCRYPTED() directly instead.
 */
अटल अंतरभूत bool fscrypt_needs_contents_encryption(स्थिर काष्ठा inode *inode)
अणु
	वापस IS_ENCRYPTED(inode) && S_ISREG(inode->i_mode);
पूर्ण

/*
 * When d_splice_alias() moves a directory's no-key alias to its plaपूर्णांकext alias
 * as a result of the encryption key being added, DCACHE_NOKEY_NAME must be
 * cleared.  Note that we करोn't have to support arbitrary moves of this flag
 * because fscrypt करोesn't allow no-key names to be the source or target of a
 * नाम().
 */
अटल अंतरभूत व्योम fscrypt_handle_d_move(काष्ठा dentry *dentry)
अणु
	dentry->d_flags &= ~DCACHE_NOKEY_NAME;
पूर्ण

/**
 * fscrypt_is_nokey_name() - test whether a dentry is a no-key name
 * @dentry: the dentry to check
 *
 * This वापसs true अगर the dentry is a no-key dentry.  A no-key dentry is a
 * dentry that was created in an encrypted directory that hasn't had its
 * encryption key added yet.  Such dentries may be either positive or negative.
 *
 * When a fileप्रणाली is asked to create a new filename in an encrypted directory
 * and the new filename's dentry is a no-key dentry, it must fail the operation
 * with ENOKEY.  This includes ->create(), ->सूची_गढ़ो(), ->mknod(), ->symlink(),
 * ->नाम(), and ->link().  (However, ->नाम() and ->link() are alपढ़ोy
 * handled by fscrypt_prepare_नाम() and fscrypt_prepare_link().)
 *
 * This is necessary because creating a filename requires the directory's
 * encryption key, but just checking क्रम the key on the directory inode during
 * the final fileप्रणाली operation करोesn't guarantee that the key was available
 * during the preceding dentry lookup.  And the key must have alपढ़ोy been
 * available during the dentry lookup in order क्रम it to have been checked
 * whether the filename alपढ़ोy exists in the directory and क्रम the new file's
 * dentry not to be invalidated due to it incorrectly having the no-key flag.
 *
 * Return: %true अगर the dentry is a no-key name
 */
अटल अंतरभूत bool fscrypt_is_nokey_name(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_flags & DCACHE_NOKEY_NAME;
पूर्ण

/* crypto.c */
व्योम fscrypt_enqueue_decrypt_work(काष्ठा work_काष्ठा *);

काष्ठा page *fscrypt_encrypt_pagecache_blocks(काष्ठा page *page,
					      अचिन्हित पूर्णांक len,
					      अचिन्हित पूर्णांक offs,
					      gfp_t gfp_flags);
पूर्णांक fscrypt_encrypt_block_inplace(स्थिर काष्ठा inode *inode, काष्ठा page *page,
				  अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offs,
				  u64 lblk_num, gfp_t gfp_flags);

पूर्णांक fscrypt_decrypt_pagecache_blocks(काष्ठा page *page, अचिन्हित पूर्णांक len,
				     अचिन्हित पूर्णांक offs);
पूर्णांक fscrypt_decrypt_block_inplace(स्थिर काष्ठा inode *inode, काष्ठा page *page,
				  अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offs,
				  u64 lblk_num);

अटल अंतरभूत bool fscrypt_is_bounce_page(काष्ठा page *page)
अणु
	वापस page->mapping == शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *fscrypt_pagecache_page(काष्ठा page *bounce_page)
अणु
	वापस (काष्ठा page *)page_निजी(bounce_page);
पूर्ण

व्योम fscrypt_मुक्त_bounce_page(काष्ठा page *bounce_page);

/* policy.c */
पूर्णांक fscrypt_ioctl_set_policy(काष्ठा file *filp, स्थिर व्योम __user *arg);
पूर्णांक fscrypt_ioctl_get_policy(काष्ठा file *filp, व्योम __user *arg);
पूर्णांक fscrypt_ioctl_get_policy_ex(काष्ठा file *filp, व्योम __user *arg);
पूर्णांक fscrypt_ioctl_get_nonce(काष्ठा file *filp, व्योम __user *arg);
पूर्णांक fscrypt_has_permitted_context(काष्ठा inode *parent, काष्ठा inode *child);
पूर्णांक fscrypt_set_context(काष्ठा inode *inode, व्योम *fs_data);

काष्ठा fscrypt_dummy_policy अणु
	स्थिर जोड़ fscrypt_policy *policy;
पूर्ण;

पूर्णांक fscrypt_set_test_dummy_encryption(काष्ठा super_block *sb, स्थिर अक्षर *arg,
				काष्ठा fscrypt_dummy_policy *dummy_policy);
व्योम fscrypt_show_test_dummy_encryption(काष्ठा seq_file *seq, अक्षर sep,
					काष्ठा super_block *sb);
अटल अंतरभूत व्योम
fscrypt_मुक्त_dummy_policy(काष्ठा fscrypt_dummy_policy *dummy_policy)
अणु
	kमुक्त(dummy_policy->policy);
	dummy_policy->policy = शून्य;
पूर्ण

/* keyring.c */
व्योम fscrypt_sb_मुक्त(काष्ठा super_block *sb);
पूर्णांक fscrypt_ioctl_add_key(काष्ठा file *filp, व्योम __user *arg);
पूर्णांक fscrypt_ioctl_हटाओ_key(काष्ठा file *filp, व्योम __user *arg);
पूर्णांक fscrypt_ioctl_हटाओ_key_all_users(काष्ठा file *filp, व्योम __user *arg);
पूर्णांक fscrypt_ioctl_get_key_status(काष्ठा file *filp, व्योम __user *arg);

/* keysetup.c */
पूर्णांक fscrypt_prepare_new_inode(काष्ठा inode *dir, काष्ठा inode *inode,
			      bool *encrypt_ret);
व्योम fscrypt_put_encryption_info(काष्ठा inode *inode);
व्योम fscrypt_मुक्त_inode(काष्ठा inode *inode);
पूर्णांक fscrypt_drop_inode(काष्ठा inode *inode);

/* fname.c */
पूर्णांक fscrypt_setup_filename(काष्ठा inode *inode, स्थिर काष्ठा qstr *iname,
			   पूर्णांक lookup, काष्ठा fscrypt_name *fname);

अटल अंतरभूत व्योम fscrypt_मुक्त_filename(काष्ठा fscrypt_name *fname)
अणु
	kमुक्त(fname->crypto_buf.name);
पूर्ण

पूर्णांक fscrypt_fname_alloc_buffer(u32 max_encrypted_len,
			       काष्ठा fscrypt_str *crypto_str);
व्योम fscrypt_fname_मुक्त_buffer(काष्ठा fscrypt_str *crypto_str);
पूर्णांक fscrypt_fname_disk_to_usr(स्थिर काष्ठा inode *inode,
			      u32 hash, u32 minor_hash,
			      स्थिर काष्ठा fscrypt_str *iname,
			      काष्ठा fscrypt_str *oname);
bool fscrypt_match_name(स्थिर काष्ठा fscrypt_name *fname,
			स्थिर u8 *de_name, u32 de_name_len);
u64 fscrypt_fname_siphash(स्थिर काष्ठा inode *dir, स्थिर काष्ठा qstr *name);
पूर्णांक fscrypt_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags);

/* bio.c */
व्योम fscrypt_decrypt_bio(काष्ठा bio *bio);
पूर्णांक fscrypt_zeroout_range(स्थिर काष्ठा inode *inode, pgoff_t lblk,
			  sector_t pblk, अचिन्हित पूर्णांक len);

/* hooks.c */
पूर्णांक fscrypt_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp);
पूर्णांक __fscrypt_prepare_link(काष्ठा inode *inode, काष्ठा inode *dir,
			   काष्ठा dentry *dentry);
पूर्णांक __fscrypt_prepare_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			     काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			     अचिन्हित पूर्णांक flags);
पूर्णांक __fscrypt_prepare_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
			     काष्ठा fscrypt_name *fname);
पूर्णांक __fscrypt_prepare_सूची_पढ़ो(काष्ठा inode *dir);
पूर्णांक __fscrypt_prepare_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr);
पूर्णांक fscrypt_prepare_setflags(काष्ठा inode *inode,
			     अचिन्हित पूर्णांक oldflags, अचिन्हित पूर्णांक flags);
पूर्णांक fscrypt_prepare_symlink(काष्ठा inode *dir, स्थिर अक्षर *target,
			    अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक max_len,
			    काष्ठा fscrypt_str *disk_link);
पूर्णांक __fscrypt_encrypt_symlink(काष्ठा inode *inode, स्थिर अक्षर *target,
			      अचिन्हित पूर्णांक len, काष्ठा fscrypt_str *disk_link);
स्थिर अक्षर *fscrypt_get_symlink(काष्ठा inode *inode, स्थिर व्योम *caddr,
				अचिन्हित पूर्णांक max_size,
				काष्ठा delayed_call *करोne);
अटल अंतरभूत व्योम fscrypt_set_ops(काष्ठा super_block *sb,
				   स्थिर काष्ठा fscrypt_operations *s_cop)
अणु
	sb->s_cop = s_cop;
पूर्ण
#अन्यथा  /* !CONFIG_FS_ENCRYPTION */

अटल अंतरभूत काष्ठा fscrypt_info *fscrypt_get_info(स्थिर काष्ठा inode *inode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool fscrypt_needs_contents_encryption(स्थिर काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम fscrypt_handle_d_move(काष्ठा dentry *dentry)
अणु
पूर्ण

अटल अंतरभूत bool fscrypt_is_nokey_name(स्थिर काष्ठा dentry *dentry)
अणु
	वापस false;
पूर्ण

/* crypto.c */
अटल अंतरभूत व्योम fscrypt_enqueue_decrypt_work(काष्ठा work_काष्ठा *work)
अणु
पूर्ण

अटल अंतरभूत काष्ठा page *fscrypt_encrypt_pagecache_blocks(काष्ठा page *page,
							    अचिन्हित पूर्णांक len,
							    अचिन्हित पूर्णांक offs,
							    gfp_t gfp_flags)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_encrypt_block_inplace(स्थिर काष्ठा inode *inode,
						काष्ठा page *page,
						अचिन्हित पूर्णांक len,
						अचिन्हित पूर्णांक offs, u64 lblk_num,
						gfp_t gfp_flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_decrypt_pagecache_blocks(काष्ठा page *page,
						   अचिन्हित पूर्णांक len,
						   अचिन्हित पूर्णांक offs)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_decrypt_block_inplace(स्थिर काष्ठा inode *inode,
						काष्ठा page *page,
						अचिन्हित पूर्णांक len,
						अचिन्हित पूर्णांक offs, u64 lblk_num)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool fscrypt_is_bounce_page(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा page *fscrypt_pagecache_page(काष्ठा page *bounce_page)
अणु
	WARN_ON_ONCE(1);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत व्योम fscrypt_मुक्त_bounce_page(काष्ठा page *bounce_page)
अणु
पूर्ण

/* policy.c */
अटल अंतरभूत पूर्णांक fscrypt_ioctl_set_policy(काष्ठा file *filp,
					   स्थिर व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_ioctl_get_policy(काष्ठा file *filp, व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_ioctl_get_policy_ex(काष्ठा file *filp,
					      व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_ioctl_get_nonce(काष्ठा file *filp, व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_has_permitted_context(काष्ठा inode *parent,
						काष्ठा inode *child)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_set_context(काष्ठा inode *inode, व्योम *fs_data)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

काष्ठा fscrypt_dummy_policy अणु
पूर्ण;

अटल अंतरभूत व्योम fscrypt_show_test_dummy_encryption(काष्ठा seq_file *seq,
						      अक्षर sep,
						      काष्ठा super_block *sb)
अणु
पूर्ण

अटल अंतरभूत व्योम
fscrypt_मुक्त_dummy_policy(काष्ठा fscrypt_dummy_policy *dummy_policy)
अणु
पूर्ण

/* keyring.c */
अटल अंतरभूत व्योम fscrypt_sb_मुक्त(काष्ठा super_block *sb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_ioctl_add_key(काष्ठा file *filp, व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_ioctl_हटाओ_key(काष्ठा file *filp, व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_ioctl_हटाओ_key_all_users(काष्ठा file *filp,
						     व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_ioctl_get_key_status(काष्ठा file *filp,
					       व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/* keysetup.c */

अटल अंतरभूत पूर्णांक fscrypt_prepare_new_inode(काष्ठा inode *dir,
					    काष्ठा inode *inode,
					    bool *encrypt_ret)
अणु
	अगर (IS_ENCRYPTED(dir))
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fscrypt_put_encryption_info(काष्ठा inode *inode)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम fscrypt_मुक्त_inode(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_drop_inode(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

 /* fname.c */
अटल अंतरभूत पूर्णांक fscrypt_setup_filename(काष्ठा inode *dir,
					 स्थिर काष्ठा qstr *iname,
					 पूर्णांक lookup, काष्ठा fscrypt_name *fname)
अणु
	अगर (IS_ENCRYPTED(dir))
		वापस -EOPNOTSUPP;

	स_रखो(fname, 0, माप(*fname));
	fname->usr_fname = iname;
	fname->disk_name.name = (अचिन्हित अक्षर *)iname->name;
	fname->disk_name.len = iname->len;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fscrypt_मुक्त_filename(काष्ठा fscrypt_name *fname)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_fname_alloc_buffer(u32 max_encrypted_len,
					     काष्ठा fscrypt_str *crypto_str)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम fscrypt_fname_मुक्त_buffer(काष्ठा fscrypt_str *crypto_str)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_fname_disk_to_usr(स्थिर काष्ठा inode *inode,
					    u32 hash, u32 minor_hash,
					    स्थिर काष्ठा fscrypt_str *iname,
					    काष्ठा fscrypt_str *oname)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool fscrypt_match_name(स्थिर काष्ठा fscrypt_name *fname,
				      स्थिर u8 *de_name, u32 de_name_len)
अणु
	/* Encryption support disabled; use standard comparison */
	अगर (de_name_len != fname->disk_name.len)
		वापस false;
	वापस !स_भेद(de_name, fname->disk_name.name, fname->disk_name.len);
पूर्ण

अटल अंतरभूत u64 fscrypt_fname_siphash(स्थिर काष्ठा inode *dir,
					स्थिर काष्ठा qstr *name)
अणु
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_d_revalidate(काष्ठा dentry *dentry,
				       अचिन्हित पूर्णांक flags)
अणु
	वापस 1;
पूर्ण

/* bio.c */
अटल अंतरभूत व्योम fscrypt_decrypt_bio(काष्ठा bio *bio)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_zeroout_range(स्थिर काष्ठा inode *inode, pgoff_t lblk,
					sector_t pblk, अचिन्हित पूर्णांक len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/* hooks.c */

अटल अंतरभूत पूर्णांक fscrypt_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर (IS_ENCRYPTED(inode))
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __fscrypt_prepare_link(काष्ठा inode *inode, काष्ठा inode *dir,
					 काष्ठा dentry *dentry)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक __fscrypt_prepare_नाम(काष्ठा inode *old_dir,
					   काष्ठा dentry *old_dentry,
					   काष्ठा inode *new_dir,
					   काष्ठा dentry *new_dentry,
					   अचिन्हित पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक __fscrypt_prepare_lookup(काष्ठा inode *dir,
					   काष्ठा dentry *dentry,
					   काष्ठा fscrypt_name *fname)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक __fscrypt_prepare_सूची_पढ़ो(काष्ठा inode *dir)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक __fscrypt_prepare_setattr(काष्ठा dentry *dentry,
					    काष्ठा iattr *attr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_prepare_setflags(काष्ठा inode *inode,
					   अचिन्हित पूर्णांक oldflags,
					   अचिन्हित पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fscrypt_prepare_symlink(काष्ठा inode *dir,
					  स्थिर अक्षर *target,
					  अचिन्हित पूर्णांक len,
					  अचिन्हित पूर्णांक max_len,
					  काष्ठा fscrypt_str *disk_link)
अणु
	अगर (IS_ENCRYPTED(dir))
		वापस -EOPNOTSUPP;
	disk_link->name = (अचिन्हित अक्षर *)target;
	disk_link->len = len + 1;
	अगर (disk_link->len > max_len)
		वापस -ENAMETOOLONG;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __fscrypt_encrypt_symlink(काष्ठा inode *inode,
					    स्थिर अक्षर *target,
					    अचिन्हित पूर्णांक len,
					    काष्ठा fscrypt_str *disk_link)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *fscrypt_get_symlink(काष्ठा inode *inode,
					      स्थिर व्योम *caddr,
					      अचिन्हित पूर्णांक max_size,
					      काष्ठा delayed_call *करोne)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम fscrypt_set_ops(काष्ठा super_block *sb,
				   स्थिर काष्ठा fscrypt_operations *s_cop)
अणु
पूर्ण

#पूर्ण_अगर	/* !CONFIG_FS_ENCRYPTION */

/* अंतरभूत_crypt.c */
#अगर_घोषित CONFIG_FS_ENCRYPTION_INLINE_CRYPT

bool __fscrypt_inode_uses_अंतरभूत_crypto(स्थिर काष्ठा inode *inode);

व्योम fscrypt_set_bio_crypt_ctx(काष्ठा bio *bio,
			       स्थिर काष्ठा inode *inode, u64 first_lblk,
			       gfp_t gfp_mask);

व्योम fscrypt_set_bio_crypt_ctx_bh(काष्ठा bio *bio,
				  स्थिर काष्ठा buffer_head *first_bh,
				  gfp_t gfp_mask);

bool fscrypt_mergeable_bio(काष्ठा bio *bio, स्थिर काष्ठा inode *inode,
			   u64 next_lblk);

bool fscrypt_mergeable_bio_bh(काष्ठा bio *bio,
			      स्थिर काष्ठा buffer_head *next_bh);

#अन्यथा /* CONFIG_FS_ENCRYPTION_INLINE_CRYPT */

अटल अंतरभूत bool __fscrypt_inode_uses_अंतरभूत_crypto(स्थिर काष्ठा inode *inode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम fscrypt_set_bio_crypt_ctx(काष्ठा bio *bio,
					     स्थिर काष्ठा inode *inode,
					     u64 first_lblk, gfp_t gfp_mask) अणु पूर्ण

अटल अंतरभूत व्योम fscrypt_set_bio_crypt_ctx_bh(
					 काष्ठा bio *bio,
					 स्थिर काष्ठा buffer_head *first_bh,
					 gfp_t gfp_mask) अणु पूर्ण

अटल अंतरभूत bool fscrypt_mergeable_bio(काष्ठा bio *bio,
					 स्थिर काष्ठा inode *inode,
					 u64 next_lblk)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool fscrypt_mergeable_bio_bh(काष्ठा bio *bio,
					    स्थिर काष्ठा buffer_head *next_bh)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* !CONFIG_FS_ENCRYPTION_INLINE_CRYPT */

/**
 * fscrypt_inode_uses_अंतरभूत_crypto() - test whether an inode uses अंतरभूत
 *					encryption
 * @inode: an inode. If encrypted, its key must be set up.
 *
 * Return: true अगर the inode requires file contents encryption and अगर the
 *	   encryption should be करोne in the block layer via blk-crypto rather
 *	   than in the fileप्रणाली layer.
 */
अटल अंतरभूत bool fscrypt_inode_uses_अंतरभूत_crypto(स्थिर काष्ठा inode *inode)
अणु
	वापस fscrypt_needs_contents_encryption(inode) &&
	       __fscrypt_inode_uses_अंतरभूत_crypto(inode);
पूर्ण

/**
 * fscrypt_inode_uses_fs_layer_crypto() - test whether an inode uses fs-layer
 *					  encryption
 * @inode: an inode. If encrypted, its key must be set up.
 *
 * Return: true अगर the inode requires file contents encryption and अगर the
 *	   encryption should be करोne in the fileप्रणाली layer rather than in the
 *	   block layer via blk-crypto.
 */
अटल अंतरभूत bool fscrypt_inode_uses_fs_layer_crypto(स्थिर काष्ठा inode *inode)
अणु
	वापस fscrypt_needs_contents_encryption(inode) &&
	       !__fscrypt_inode_uses_अंतरभूत_crypto(inode);
पूर्ण

/**
 * fscrypt_has_encryption_key() - check whether an inode has had its key set up
 * @inode: the inode to check
 *
 * Return: %true अगर the inode has had its encryption key set up, अन्यथा %false.
 *
 * Usually this should be preceded by fscrypt_get_encryption_info() to try to
 * set up the key first.
 */
अटल अंतरभूत bool fscrypt_has_encryption_key(स्थिर काष्ठा inode *inode)
अणु
	वापस fscrypt_get_info(inode) != शून्य;
पूर्ण

/**
 * fscrypt_prepare_link() - prepare to link an inode पूर्णांकo a possibly-encrypted
 *			    directory
 * @old_dentry: an existing dentry क्रम the inode being linked
 * @dir: the target directory
 * @dentry: negative dentry क्रम the target filename
 *
 * A new link can only be added to an encrypted directory अगर the directory's
 * encryption key is available --- since otherwise we'd have no way to encrypt
 * the filename.
 *
 * We also verअगरy that the link will not violate the स्थिरraपूर्णांक that all files
 * in an encrypted directory tree use the same encryption policy.
 *
 * Return: 0 on success, -ENOKEY अगर the directory's encryption key is missing,
 * -EXDEV अगर the link would result in an inconsistent encryption policy, or
 * another -त्रुटि_सं code.
 */
अटल अंतरभूत पूर्णांक fscrypt_prepare_link(काष्ठा dentry *old_dentry,
				       काष्ठा inode *dir,
				       काष्ठा dentry *dentry)
अणु
	अगर (IS_ENCRYPTED(dir))
		वापस __fscrypt_prepare_link(d_inode(old_dentry), dir, dentry);
	वापस 0;
पूर्ण

/**
 * fscrypt_prepare_नाम() - prepare क्रम a नाम between possibly-encrypted
 *			      directories
 * @old_dir: source directory
 * @old_dentry: dentry क्रम source file
 * @new_dir: target directory
 * @new_dentry: dentry क्रम target location (may be negative unless exchanging)
 * @flags: नाम flags (we care at least about %RENAME_EXCHANGE)
 *
 * Prepare क्रम ->नाम() where the source and/or target directories may be
 * encrypted.  A new link can only be added to an encrypted directory अगर the
 * directory's encryption key is available --- since otherwise we'd have no way
 * to encrypt the filename.  A नाम to an existing name, on the other hand,
 * *is* cryptographically possible without the key.  However, we take the more
 * conservative approach and just क्रमbid all no-key नामs.
 *
 * We also verअगरy that the नाम will not violate the स्थिरraपूर्णांक that all files
 * in an encrypted directory tree use the same encryption policy.
 *
 * Return: 0 on success, -ENOKEY अगर an encryption key is missing, -EXDEV अगर the
 * नाम would cause inconsistent encryption policies, or another -त्रुटि_सं code.
 */
अटल अंतरभूत पूर्णांक fscrypt_prepare_नाम(काष्ठा inode *old_dir,
					 काष्ठा dentry *old_dentry,
					 काष्ठा inode *new_dir,
					 काष्ठा dentry *new_dentry,
					 अचिन्हित पूर्णांक flags)
अणु
	अगर (IS_ENCRYPTED(old_dir) || IS_ENCRYPTED(new_dir))
		वापस __fscrypt_prepare_नाम(old_dir, old_dentry,
						new_dir, new_dentry, flags);
	वापस 0;
पूर्ण

/**
 * fscrypt_prepare_lookup() - prepare to lookup a name in a possibly-encrypted
 *			      directory
 * @dir: directory being searched
 * @dentry: filename being looked up
 * @fname: (output) the name to use to search the on-disk directory
 *
 * Prepare क्रम ->lookup() in a directory which may be encrypted by determining
 * the name that will actually be used to search the directory on-disk.  If the
 * directory's encryption policy is supported by this kernel and its encryption
 * key is available, then the lookup is assumed to be by plaपूर्णांकext name;
 * otherwise, it is assumed to be by no-key name.
 *
 * This will set DCACHE_NOKEY_NAME on the dentry अगर the lookup is by no-key
 * name.  In this हाल the fileप्रणाली must assign the dentry a dentry_operations
 * which contains fscrypt_d_revalidate (or contains a d_revalidate method that
 * calls fscrypt_d_revalidate), so that the dentry will be invalidated अगर the
 * directory's encryption key is later added.
 *
 * Return: 0 on success; -ENOENT अगर the directory's key is unavailable but the
 * filename isn't a valid no-key name, so a negative dentry should be created;
 * or another -त्रुटि_सं code.
 */
अटल अंतरभूत पूर्णांक fscrypt_prepare_lookup(काष्ठा inode *dir,
					 काष्ठा dentry *dentry,
					 काष्ठा fscrypt_name *fname)
अणु
	अगर (IS_ENCRYPTED(dir))
		वापस __fscrypt_prepare_lookup(dir, dentry, fname);

	स_रखो(fname, 0, माप(*fname));
	fname->usr_fname = &dentry->d_name;
	fname->disk_name.name = (अचिन्हित अक्षर *)dentry->d_name.name;
	fname->disk_name.len = dentry->d_name.len;
	वापस 0;
पूर्ण

/**
 * fscrypt_prepare_सूची_पढ़ो() - prepare to पढ़ो a possibly-encrypted directory
 * @dir: the directory inode
 *
 * If the directory is encrypted and it करोesn't alपढ़ोy have its encryption key
 * set up, try to set it up so that the filenames will be listed in plaपूर्णांकext
 * क्रमm rather than in no-key क्रमm.
 *
 * Return: 0 on success; -त्रुटि_सं on error.  Note that the encryption key being
 *	   unavailable is not considered an error.  It is also not an error अगर
 *	   the encryption policy is unsupported by this kernel; that is treated
 *	   like the key being unavailable, so that files can still be deleted.
 */
अटल अंतरभूत पूर्णांक fscrypt_prepare_सूची_पढ़ो(काष्ठा inode *dir)
अणु
	अगर (IS_ENCRYPTED(dir))
		वापस __fscrypt_prepare_सूची_पढ़ो(dir);
	वापस 0;
पूर्ण

/**
 * fscrypt_prepare_setattr() - prepare to change a possibly-encrypted inode's
 *			       attributes
 * @dentry: dentry through which the inode is being changed
 * @attr: attributes to change
 *
 * Prepare क्रम ->setattr() on a possibly-encrypted inode.  On an encrypted file,
 * most attribute changes are allowed even without the encryption key.  However,
 * without the encryption key we करो have to क्रमbid truncates.  This is needed
 * because the size being truncated to may not be a multiple of the fileप्रणाली
 * block size, and in that हाल we'd have to decrypt the final block, zero the
 * portion past i_size, and re-encrypt it.  (We *could* allow truncating to a
 * fileप्रणाली block boundary, but it's simpler to just क्रमbid all truncates ---
 * and we alपढ़ोy क्रमbid all other contents modअगरications without the key.)
 *
 * Return: 0 on success, -ENOKEY अगर the key is missing, or another -त्रुटि_सं code
 * अगर a problem occurred जबतक setting up the encryption key.
 */
अटल अंतरभूत पूर्णांक fscrypt_prepare_setattr(काष्ठा dentry *dentry,
					  काष्ठा iattr *attr)
अणु
	अगर (IS_ENCRYPTED(d_inode(dentry)))
		वापस __fscrypt_prepare_setattr(dentry, attr);
	वापस 0;
पूर्ण

/**
 * fscrypt_encrypt_symlink() - encrypt the symlink target अगर needed
 * @inode: symlink inode
 * @target: plaपूर्णांकext symlink target
 * @len: length of @target excluding null terminator
 * @disk_link: (in/out) the on-disk symlink target being prepared
 *
 * If the symlink target needs to be encrypted, then this function encrypts it
 * पूर्णांकo @disk_link->name.  fscrypt_prepare_symlink() must have been called
 * previously to compute @disk_link->len.  If the fileप्रणाली did not allocate a
 * buffer क्रम @disk_link->name after calling fscrypt_prepare_link(), then one
 * will be kदो_स्मृति()'ed and the fileप्रणाली will be responsible क्रम मुक्तing it.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल अंतरभूत पूर्णांक fscrypt_encrypt_symlink(काष्ठा inode *inode,
					  स्थिर अक्षर *target,
					  अचिन्हित पूर्णांक len,
					  काष्ठा fscrypt_str *disk_link)
अणु
	अगर (IS_ENCRYPTED(inode))
		वापस __fscrypt_encrypt_symlink(inode, target, len, disk_link);
	वापस 0;
पूर्ण

/* If *pagep is a bounce page, मुक्त it and set *pagep to the pagecache page */
अटल अंतरभूत व्योम fscrypt_finalize_bounce_page(काष्ठा page **pagep)
अणु
	काष्ठा page *page = *pagep;

	अगर (fscrypt_is_bounce_page(page)) अणु
		*pagep = fscrypt_pagecache_page(page);
		fscrypt_मुक्त_bounce_page(page);
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* _LINUX_FSCRYPT_H */
