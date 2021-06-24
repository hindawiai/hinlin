<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/dir.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/unicode.h>
#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "acl.h"
#समावेश "xattr.h"
#समावेश <trace/events/f2fs.h>

अटल अचिन्हित दीर्घ dir_blocks(काष्ठा inode *inode)
अणु
	वापस ((अचिन्हित दीर्घ दीर्घ) (i_size_पढ़ो(inode) + PAGE_SIZE - 1))
							>> PAGE_SHIFT;
पूर्ण

अटल अचिन्हित पूर्णांक dir_buckets(अचिन्हित पूर्णांक level, पूर्णांक dir_level)
अणु
	अगर (level + dir_level < MAX_सूची_HASH_DEPTH / 2)
		वापस 1 << (level + dir_level);
	अन्यथा
		वापस MAX_सूची_BUCKETS;
पूर्ण

अटल अचिन्हित पूर्णांक bucket_blocks(अचिन्हित पूर्णांक level)
अणु
	अगर (level < MAX_सूची_HASH_DEPTH / 2)
		वापस 2;
	अन्यथा
		वापस 4;
पूर्ण

अटल अचिन्हित अक्षर f2fs_filetype_table[F2FS_FT_MAX] = अणु
	[F2FS_FT_UNKNOWN]	= DT_UNKNOWN,
	[F2FS_FT_REG_खाता]	= DT_REG,
	[F2FS_FT_सूची]		= DT_सूची,
	[F2FS_FT_CHRDEV]	= DT_CHR,
	[F2FS_FT_BLKDEV]	= DT_BLK,
	[F2FS_FT_FIFO]		= DT_FIFO,
	[F2FS_FT_SOCK]		= DT_SOCK,
	[F2FS_FT_SYMLINK]	= DT_LNK,
पूर्ण;

अटल अचिन्हित अक्षर f2fs_type_by_mode[S_IFMT >> S_SHIFT] = अणु
	[S_IFREG >> S_SHIFT]	= F2FS_FT_REG_खाता,
	[S_IFसूची >> S_SHIFT]	= F2FS_FT_सूची,
	[S_IFCHR >> S_SHIFT]	= F2FS_FT_CHRDEV,
	[S_IFBLK >> S_SHIFT]	= F2FS_FT_BLKDEV,
	[S_IFIFO >> S_SHIFT]	= F2FS_FT_FIFO,
	[S_IFSOCK >> S_SHIFT]	= F2FS_FT_SOCK,
	[S_IFLNK >> S_SHIFT]	= F2FS_FT_SYMLINK,
पूर्ण;

अटल व्योम set_de_type(काष्ठा f2fs_dir_entry *de, umode_t mode)
अणु
	de->file_type = f2fs_type_by_mode[(mode & S_IFMT) >> S_SHIFT];
पूर्ण

अचिन्हित अक्षर f2fs_get_de_type(काष्ठा f2fs_dir_entry *de)
अणु
	अगर (de->file_type < F2FS_FT_MAX)
		वापस f2fs_filetype_table[de->file_type];
	वापस DT_UNKNOWN;
पूर्ण

/* If @dir is हालfolded, initialize @fname->cf_name from @fname->usr_fname. */
पूर्णांक f2fs_init_हालfolded_name(स्थिर काष्ठा inode *dir,
			      काष्ठा f2fs_filename *fname)
अणु
#अगर_घोषित CONFIG_UNICODE
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);

	अगर (IS_CASEFOLDED(dir)) अणु
		fname->cf_name.name = f2fs_kदो_स्मृति(sbi, F2FS_NAME_LEN,
						   GFP_NOFS);
		अगर (!fname->cf_name.name)
			वापस -ENOMEM;
		fname->cf_name.len = utf8_हालfold(sb->s_encoding,
						   fname->usr_fname,
						   fname->cf_name.name,
						   F2FS_NAME_LEN);
		अगर ((पूर्णांक)fname->cf_name.len <= 0) अणु
			kमुक्त(fname->cf_name.name);
			fname->cf_name.name = शून्य;
			अगर (sb_has_strict_encoding(sb))
				वापस -EINVAL;
			/* fall back to treating name as opaque byte sequence */
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __f2fs_setup_filename(स्थिर काष्ठा inode *dir,
				 स्थिर काष्ठा fscrypt_name *crypt_name,
				 काष्ठा f2fs_filename *fname)
अणु
	पूर्णांक err;

	स_रखो(fname, 0, माप(*fname));

	fname->usr_fname = crypt_name->usr_fname;
	fname->disk_name = crypt_name->disk_name;
#अगर_घोषित CONFIG_FS_ENCRYPTION
	fname->crypto_buf = crypt_name->crypto_buf;
#पूर्ण_अगर
	अगर (crypt_name->is_nokey_name) अणु
		/* hash was decoded from the no-key name */
		fname->hash = cpu_to_le32(crypt_name->hash);
	पूर्ण अन्यथा अणु
		err = f2fs_init_हालfolded_name(dir, fname);
		अगर (err) अणु
			f2fs_मुक्त_filename(fname);
			वापस err;
		पूर्ण
		f2fs_hash_filename(dir, fname);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Prepare to search क्रम @iname in @dir.  This is similar to
 * fscrypt_setup_filename(), but this also handles computing the हालfolded name
 * and the f2fs dirhash अगर needed, then packing all the inक्रमmation about this
 * filename up पूर्णांकo a 'struct f2fs_filename'.
 */
पूर्णांक f2fs_setup_filename(काष्ठा inode *dir, स्थिर काष्ठा qstr *iname,
			पूर्णांक lookup, काष्ठा f2fs_filename *fname)
अणु
	काष्ठा fscrypt_name crypt_name;
	पूर्णांक err;

	err = fscrypt_setup_filename(dir, iname, lookup, &crypt_name);
	अगर (err)
		वापस err;

	वापस __f2fs_setup_filename(dir, &crypt_name, fname);
पूर्ण

/*
 * Prepare to look up @dentry in @dir.  This is similar to
 * fscrypt_prepare_lookup(), but this also handles computing the हालfolded name
 * and the f2fs dirhash अगर needed, then packing all the inक्रमmation about this
 * filename up पूर्णांकo a 'struct f2fs_filename'.
 */
पूर्णांक f2fs_prepare_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
			काष्ठा f2fs_filename *fname)
अणु
	काष्ठा fscrypt_name crypt_name;
	पूर्णांक err;

	err = fscrypt_prepare_lookup(dir, dentry, &crypt_name);
	अगर (err)
		वापस err;

	वापस __f2fs_setup_filename(dir, &crypt_name, fname);
पूर्ण

व्योम f2fs_मुक्त_filename(काष्ठा f2fs_filename *fname)
अणु
#अगर_घोषित CONFIG_FS_ENCRYPTION
	kमुक्त(fname->crypto_buf.name);
	fname->crypto_buf.name = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UNICODE
	kमुक्त(fname->cf_name.name);
	fname->cf_name.name = शून्य;
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ dir_block_index(अचिन्हित पूर्णांक level,
				पूर्णांक dir_level, अचिन्हित पूर्णांक idx)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ bidx = 0;

	क्रम (i = 0; i < level; i++)
		bidx += dir_buckets(i, dir_level) * bucket_blocks(i);
	bidx += idx * bucket_blocks(level);
	वापस bidx;
पूर्ण

अटल काष्ठा f2fs_dir_entry *find_in_block(काष्ठा inode *dir,
				काष्ठा page *dentry_page,
				स्थिर काष्ठा f2fs_filename *fname,
				पूर्णांक *max_slots)
अणु
	काष्ठा f2fs_dentry_block *dentry_blk;
	काष्ठा f2fs_dentry_ptr d;

	dentry_blk = (काष्ठा f2fs_dentry_block *)page_address(dentry_page);

	make_dentry_ptr_block(dir, &d, dentry_blk);
	वापस f2fs_find_target_dentry(&d, fname, max_slots);
पूर्ण

#अगर_घोषित CONFIG_UNICODE
/*
 * Test whether a हाल-insensitive directory entry matches the filename
 * being searched क्रम.
 *
 * Returns 1 क्रम a match, 0 क्रम no match, and -त्रुटि_सं on an error.
 */
अटल पूर्णांक f2fs_match_ci_name(स्थिर काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
			       स्थिर u8 *de_name, u32 de_name_len)
अणु
	स्थिर काष्ठा super_block *sb = dir->i_sb;
	स्थिर काष्ठा unicode_map *um = sb->s_encoding;
	काष्ठा fscrypt_str decrypted_name = FSTR_INIT(शून्य, de_name_len);
	काष्ठा qstr entry = QSTR_INIT(de_name, de_name_len);
	पूर्णांक res;

	अगर (IS_ENCRYPTED(dir)) अणु
		स्थिर काष्ठा fscrypt_str encrypted_name =
			FSTR_INIT((u8 *)de_name, de_name_len);

		अगर (WARN_ON_ONCE(!fscrypt_has_encryption_key(dir)))
			वापस -EINVAL;

		decrypted_name.name = kदो_स्मृति(de_name_len, GFP_KERNEL);
		अगर (!decrypted_name.name)
			वापस -ENOMEM;
		res = fscrypt_fname_disk_to_usr(dir, 0, 0, &encrypted_name,
						&decrypted_name);
		अगर (res < 0)
			जाओ out;
		entry.name = decrypted_name.name;
		entry.len = decrypted_name.len;
	पूर्ण

	res = utf8_strnहालcmp_folded(um, name, &entry);
	/*
	 * In strict mode, ignore invalid names.  In non-strict mode,
	 * fall back to treating them as opaque byte sequences.
	 */
	अगर (res < 0 && !sb_has_strict_encoding(sb)) अणु
		res = name->len == entry.len &&
				स_भेद(name->name, entry.name, name->len) == 0;
	पूर्ण अन्यथा अणु
		/* utf8_strnहालcmp_folded वापसs 0 on match */
		res = (res == 0);
	पूर्ण
out:
	kमुक्त(decrypted_name.name);
	वापस res;
पूर्ण
#पूर्ण_अगर /* CONFIG_UNICODE */

अटल अंतरभूत पूर्णांक f2fs_match_name(स्थिर काष्ठा inode *dir,
				   स्थिर काष्ठा f2fs_filename *fname,
				   स्थिर u8 *de_name, u32 de_name_len)
अणु
	काष्ठा fscrypt_name f;

#अगर_घोषित CONFIG_UNICODE
	अगर (fname->cf_name.name) अणु
		काष्ठा qstr cf = FSTR_TO_QSTR(&fname->cf_name);

		वापस f2fs_match_ci_name(dir, &cf, de_name, de_name_len);
	पूर्ण
#पूर्ण_अगर
	f.usr_fname = fname->usr_fname;
	f.disk_name = fname->disk_name;
#अगर_घोषित CONFIG_FS_ENCRYPTION
	f.crypto_buf = fname->crypto_buf;
#पूर्ण_अगर
	वापस fscrypt_match_name(&f, de_name, de_name_len);
पूर्ण

काष्ठा f2fs_dir_entry *f2fs_find_target_dentry(स्थिर काष्ठा f2fs_dentry_ptr *d,
			स्थिर काष्ठा f2fs_filename *fname, पूर्णांक *max_slots)
अणु
	काष्ठा f2fs_dir_entry *de;
	अचिन्हित दीर्घ bit_pos = 0;
	पूर्णांक max_len = 0;
	पूर्णांक res = 0;

	अगर (max_slots)
		*max_slots = 0;
	जबतक (bit_pos < d->max) अणु
		अगर (!test_bit_le(bit_pos, d->biपंचांगap)) अणु
			bit_pos++;
			max_len++;
			जारी;
		पूर्ण

		de = &d->dentry[bit_pos];

		अगर (unlikely(!de->name_len)) अणु
			bit_pos++;
			जारी;
		पूर्ण

		अगर (de->hash_code == fname->hash) अणु
			res = f2fs_match_name(d->inode, fname,
					      d->filename[bit_pos],
					      le16_to_cpu(de->name_len));
			अगर (res < 0)
				वापस ERR_PTR(res);
			अगर (res)
				जाओ found;
		पूर्ण

		अगर (max_slots && max_len > *max_slots)
			*max_slots = max_len;
		max_len = 0;

		bit_pos += GET_DENTRY_SLOTS(le16_to_cpu(de->name_len));
	पूर्ण

	de = शून्य;
found:
	अगर (max_slots && max_len > *max_slots)
		*max_slots = max_len;
	वापस de;
पूर्ण

अटल काष्ठा f2fs_dir_entry *find_in_level(काष्ठा inode *dir,
					अचिन्हित पूर्णांक level,
					स्थिर काष्ठा f2fs_filename *fname,
					काष्ठा page **res_page)
अणु
	पूर्णांक s = GET_DENTRY_SLOTS(fname->disk_name.len);
	अचिन्हित पूर्णांक nbucket, nblock;
	अचिन्हित पूर्णांक bidx, end_block;
	काष्ठा page *dentry_page;
	काष्ठा f2fs_dir_entry *de = शून्य;
	bool room = false;
	पूर्णांक max_slots;

	nbucket = dir_buckets(level, F2FS_I(dir)->i_dir_level);
	nblock = bucket_blocks(level);

	bidx = dir_block_index(level, F2FS_I(dir)->i_dir_level,
			       le32_to_cpu(fname->hash) % nbucket);
	end_block = bidx + nblock;

	क्रम (; bidx < end_block; bidx++) अणु
		/* no need to allocate new dentry pages to all the indices */
		dentry_page = f2fs_find_data_page(dir, bidx);
		अगर (IS_ERR(dentry_page)) अणु
			अगर (PTR_ERR(dentry_page) == -ENOENT) अणु
				room = true;
				जारी;
			पूर्ण अन्यथा अणु
				*res_page = dentry_page;
				अवरोध;
			पूर्ण
		पूर्ण

		de = find_in_block(dir, dentry_page, fname, &max_slots);
		अगर (IS_ERR(de)) अणु
			*res_page = ERR_CAST(de);
			de = शून्य;
			अवरोध;
		पूर्ण अन्यथा अगर (de) अणु
			*res_page = dentry_page;
			अवरोध;
		पूर्ण

		अगर (max_slots >= s)
			room = true;
		f2fs_put_page(dentry_page, 0);
	पूर्ण

	अगर (!de && room && F2FS_I(dir)->chash != fname->hash) अणु
		F2FS_I(dir)->chash = fname->hash;
		F2FS_I(dir)->clevel = level;
	पूर्ण

	वापस de;
पूर्ण

काष्ठा f2fs_dir_entry *__f2fs_find_entry(काष्ठा inode *dir,
					 स्थिर काष्ठा f2fs_filename *fname,
					 काष्ठा page **res_page)
अणु
	अचिन्हित दीर्घ npages = dir_blocks(dir);
	काष्ठा f2fs_dir_entry *de = शून्य;
	अचिन्हित पूर्णांक max_depth;
	अचिन्हित पूर्णांक level;

	*res_page = शून्य;

	अगर (f2fs_has_अंतरभूत_dentry(dir)) अणु
		de = f2fs_find_in_अंतरभूत_dir(dir, fname, res_page);
		जाओ out;
	पूर्ण

	अगर (npages == 0)
		जाओ out;

	max_depth = F2FS_I(dir)->i_current_depth;
	अगर (unlikely(max_depth > MAX_सूची_HASH_DEPTH)) अणु
		f2fs_warn(F2FS_I_SB(dir), "Corrupted max_depth of %lu: %u",
			  dir->i_ino, max_depth);
		max_depth = MAX_सूची_HASH_DEPTH;
		f2fs_i_depth_ग_लिखो(dir, max_depth);
	पूर्ण

	क्रम (level = 0; level < max_depth; level++) अणु
		de = find_in_level(dir, level, fname, res_page);
		अगर (de || IS_ERR(*res_page))
			अवरोध;
	पूर्ण
out:
	/* This is to increase the speed of f2fs_create */
	अगर (!de)
		F2FS_I(dir)->task = current;
	वापस de;
पूर्ण

/*
 * Find an entry in the specअगरied directory with the wanted name.
 * It वापसs the page where the entry was found (as a parameter - res_page),
 * and the entry itself. Page is वापसed mapped and unlocked.
 * Entry is guaranteed to be valid.
 */
काष्ठा f2fs_dir_entry *f2fs_find_entry(काष्ठा inode *dir,
			स्थिर काष्ठा qstr *child, काष्ठा page **res_page)
अणु
	काष्ठा f2fs_dir_entry *de = शून्य;
	काष्ठा f2fs_filename fname;
	पूर्णांक err;

	err = f2fs_setup_filename(dir, child, 1, &fname);
	अगर (err) अणु
		अगर (err == -ENOENT)
			*res_page = शून्य;
		अन्यथा
			*res_page = ERR_PTR(err);
		वापस शून्य;
	पूर्ण

	de = __f2fs_find_entry(dir, &fname, res_page);

	f2fs_मुक्त_filename(&fname);
	वापस de;
पूर्ण

काष्ठा f2fs_dir_entry *f2fs_parent_dir(काष्ठा inode *dir, काष्ठा page **p)
अणु
	वापस f2fs_find_entry(dir, &करोtकरोt_name, p);
पूर्ण

ino_t f2fs_inode_by_name(काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr,
							काष्ठा page **page)
अणु
	ino_t res = 0;
	काष्ठा f2fs_dir_entry *de;

	de = f2fs_find_entry(dir, qstr, page);
	अगर (de) अणु
		res = le32_to_cpu(de->ino);
		f2fs_put_page(*page, 0);
	पूर्ण

	वापस res;
पूर्ण

व्योम f2fs_set_link(काष्ठा inode *dir, काष्ठा f2fs_dir_entry *de,
		काष्ठा page *page, काष्ठा inode *inode)
अणु
	क्रमागत page_type type = f2fs_has_अंतरभूत_dentry(dir) ? NODE : DATA;

	lock_page(page);
	f2fs_रुको_on_page_ग_लिखोback(page, type, true, true);
	de->ino = cpu_to_le32(inode->i_ino);
	set_de_type(de, inode->i_mode);
	set_page_dirty(page);

	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	f2fs_mark_inode_dirty_sync(dir, false);
	f2fs_put_page(page, 1);
पूर्ण

अटल व्योम init_dent_inode(काष्ठा inode *dir, काष्ठा inode *inode,
			    स्थिर काष्ठा f2fs_filename *fname,
			    काष्ठा page *ipage)
अणु
	काष्ठा f2fs_inode *ri;

	अगर (!fname) /* क्षणिक_ख हाल? */
		वापस;

	f2fs_रुको_on_page_ग_लिखोback(ipage, NODE, true, true);

	/* copy name info. to this inode page */
	ri = F2FS_INODE(ipage);
	ri->i_namelen = cpu_to_le32(fname->disk_name.len);
	स_नकल(ri->i_name, fname->disk_name.name, fname->disk_name.len);
	अगर (IS_ENCRYPTED(dir)) अणु
		file_set_enc_name(inode);
		/*
		 * Roll-क्रमward recovery करोesn't have encryption keys available,
		 * so it can't compute the dirhash क्रम encrypted+हालfolded
		 * filenames.  Append it to i_name अगर possible.  Else, disable
		 * roll-क्रमward recovery of the dentry (i.e., make fsync'ing the
		 * file क्रमce a checkpoपूर्णांक) by setting LOST_PINO.
		 */
		अगर (IS_CASEFOLDED(dir)) अणु
			अगर (fname->disk_name.len + माप(f2fs_hash_t) <=
			    F2FS_NAME_LEN)
				put_unaligned(fname->hash, (f2fs_hash_t *)
					&ri->i_name[fname->disk_name.len]);
			अन्यथा
				file_lost_pino(inode);
		पूर्ण
	पूर्ण
	set_page_dirty(ipage);
पूर्ण

व्योम f2fs_करो_make_empty_dir(काष्ठा inode *inode, काष्ठा inode *parent,
					काष्ठा f2fs_dentry_ptr *d)
अणु
	काष्ठा fscrypt_str करोt = FSTR_INIT(".", 1);
	काष्ठा fscrypt_str करोtकरोt = FSTR_INIT("..", 2);

	/* update dirent of "." */
	f2fs_update_dentry(inode->i_ino, inode->i_mode, d, &करोt, 0, 0);

	/* update dirent of ".." */
	f2fs_update_dentry(parent->i_ino, parent->i_mode, d, &करोtकरोt, 0, 1);
पूर्ण

अटल पूर्णांक make_empty_dir(काष्ठा inode *inode,
		काष्ठा inode *parent, काष्ठा page *page)
अणु
	काष्ठा page *dentry_page;
	काष्ठा f2fs_dentry_block *dentry_blk;
	काष्ठा f2fs_dentry_ptr d;

	अगर (f2fs_has_अंतरभूत_dentry(inode))
		वापस f2fs_make_empty_अंतरभूत_dir(inode, parent, page);

	dentry_page = f2fs_get_new_data_page(inode, page, 0, true);
	अगर (IS_ERR(dentry_page))
		वापस PTR_ERR(dentry_page);

	dentry_blk = page_address(dentry_page);

	make_dentry_ptr_block(शून्य, &d, dentry_blk);
	f2fs_करो_make_empty_dir(inode, parent, &d);

	set_page_dirty(dentry_page);
	f2fs_put_page(dentry_page, 1);
	वापस 0;
पूर्ण

काष्ठा page *f2fs_init_inode_metadata(काष्ठा inode *inode, काष्ठा inode *dir,
			स्थिर काष्ठा f2fs_filename *fname, काष्ठा page *dpage)
अणु
	काष्ठा page *page;
	पूर्णांक err;

	अगर (is_inode_flag_set(inode, FI_NEW_INODE)) अणु
		page = f2fs_new_inode_page(inode);
		अगर (IS_ERR(page))
			वापस page;

		अगर (S_ISसूची(inode->i_mode)) अणु
			/* in order to handle error हाल */
			get_page(page);
			err = make_empty_dir(inode, dir, page);
			अगर (err) अणु
				lock_page(page);
				जाओ put_error;
			पूर्ण
			put_page(page);
		पूर्ण

		err = f2fs_init_acl(inode, dir, page, dpage);
		अगर (err)
			जाओ put_error;

		err = f2fs_init_security(inode, dir,
					 fname ? fname->usr_fname : शून्य, page);
		अगर (err)
			जाओ put_error;

		अगर (IS_ENCRYPTED(inode)) अणु
			err = fscrypt_set_context(inode, page);
			अगर (err)
				जाओ put_error;
		पूर्ण
	पूर्ण अन्यथा अणु
		page = f2fs_get_node_page(F2FS_I_SB(dir), inode->i_ino);
		अगर (IS_ERR(page))
			वापस page;
	पूर्ण

	init_dent_inode(dir, inode, fname, page);

	/*
	 * This file should be checkpoपूर्णांकed during fsync.
	 * We lost i_pino from now on.
	 */
	अगर (is_inode_flag_set(inode, FI_INC_LINK)) अणु
		अगर (!S_ISसूची(inode->i_mode))
			file_lost_pino(inode);
		/*
		 * If link the क्षणिक_ख to alias through linkat path,
		 * we should हटाओ this inode from orphan list.
		 */
		अगर (inode->i_nlink == 0)
			f2fs_हटाओ_orphan_inode(F2FS_I_SB(dir), inode->i_ino);
		f2fs_i_links_ग_लिखो(inode, true);
	पूर्ण
	वापस page;

put_error:
	clear_nlink(inode);
	f2fs_update_inode(inode, page);
	f2fs_put_page(page, 1);
	वापस ERR_PTR(err);
पूर्ण

व्योम f2fs_update_parent_metadata(काष्ठा inode *dir, काष्ठा inode *inode,
						अचिन्हित पूर्णांक current_depth)
अणु
	अगर (inode && is_inode_flag_set(inode, FI_NEW_INODE)) अणु
		अगर (S_ISसूची(inode->i_mode))
			f2fs_i_links_ग_लिखो(dir, true);
		clear_inode_flag(inode, FI_NEW_INODE);
	पूर्ण
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	f2fs_mark_inode_dirty_sync(dir, false);

	अगर (F2FS_I(dir)->i_current_depth != current_depth)
		f2fs_i_depth_ग_लिखो(dir, current_depth);

	अगर (inode && is_inode_flag_set(inode, FI_INC_LINK))
		clear_inode_flag(inode, FI_INC_LINK);
पूर्ण

पूर्णांक f2fs_room_क्रम_filename(स्थिर व्योम *biपंचांगap, पूर्णांक slots, पूर्णांक max_slots)
अणु
	पूर्णांक bit_start = 0;
	पूर्णांक zero_start, zero_end;
next:
	zero_start = find_next_zero_bit_le(biपंचांगap, max_slots, bit_start);
	अगर (zero_start >= max_slots)
		वापस max_slots;

	zero_end = find_next_bit_le(biपंचांगap, max_slots, zero_start);
	अगर (zero_end - zero_start >= slots)
		वापस zero_start;

	bit_start = zero_end + 1;

	अगर (zero_end + 1 >= max_slots)
		वापस max_slots;
	जाओ next;
पूर्ण

bool f2fs_has_enough_room(काष्ठा inode *dir, काष्ठा page *ipage,
			  स्थिर काष्ठा f2fs_filename *fname)
अणु
	काष्ठा f2fs_dentry_ptr d;
	अचिन्हित पूर्णांक bit_pos;
	पूर्णांक slots = GET_DENTRY_SLOTS(fname->disk_name.len);

	make_dentry_ptr_अंतरभूत(dir, &d, अंतरभूत_data_addr(dir, ipage));

	bit_pos = f2fs_room_क्रम_filename(d.biपंचांगap, slots, d.max);

	वापस bit_pos < d.max;
पूर्ण

व्योम f2fs_update_dentry(nid_t ino, umode_t mode, काष्ठा f2fs_dentry_ptr *d,
			स्थिर काष्ठा fscrypt_str *name, f2fs_hash_t name_hash,
			अचिन्हित पूर्णांक bit_pos)
अणु
	काष्ठा f2fs_dir_entry *de;
	पूर्णांक slots = GET_DENTRY_SLOTS(name->len);
	पूर्णांक i;

	de = &d->dentry[bit_pos];
	de->hash_code = name_hash;
	de->name_len = cpu_to_le16(name->len);
	स_नकल(d->filename[bit_pos], name->name, name->len);
	de->ino = cpu_to_le32(ino);
	set_de_type(de, mode);
	क्रम (i = 0; i < slots; i++) अणु
		__set_bit_le(bit_pos + i, (व्योम *)d->biपंचांगap);
		/* aव्योम wrong garbage data क्रम सूची_पढ़ो */
		अगर (i)
			(de + i)->name_len = 0;
	पूर्ण
पूर्ण

पूर्णांक f2fs_add_regular_entry(काष्ठा inode *dir, स्थिर काष्ठा f2fs_filename *fname,
			   काष्ठा inode *inode, nid_t ino, umode_t mode)
अणु
	अचिन्हित पूर्णांक bit_pos;
	अचिन्हित पूर्णांक level;
	अचिन्हित पूर्णांक current_depth;
	अचिन्हित दीर्घ bidx, block;
	अचिन्हित पूर्णांक nbucket, nblock;
	काष्ठा page *dentry_page = शून्य;
	काष्ठा f2fs_dentry_block *dentry_blk = शून्य;
	काष्ठा f2fs_dentry_ptr d;
	काष्ठा page *page = शून्य;
	पूर्णांक slots, err = 0;

	level = 0;
	slots = GET_DENTRY_SLOTS(fname->disk_name.len);

	current_depth = F2FS_I(dir)->i_current_depth;
	अगर (F2FS_I(dir)->chash == fname->hash) अणु
		level = F2FS_I(dir)->clevel;
		F2FS_I(dir)->chash = 0;
	पूर्ण

start:
	अगर (समय_प्रकारo_inject(F2FS_I_SB(dir), FAULT_सूची_DEPTH)) अणु
		f2fs_show_injection_info(F2FS_I_SB(dir), FAULT_सूची_DEPTH);
		वापस -ENOSPC;
	पूर्ण

	अगर (unlikely(current_depth == MAX_सूची_HASH_DEPTH))
		वापस -ENOSPC;

	/* Increase the depth, अगर required */
	अगर (level == current_depth)
		++current_depth;

	nbucket = dir_buckets(level, F2FS_I(dir)->i_dir_level);
	nblock = bucket_blocks(level);

	bidx = dir_block_index(level, F2FS_I(dir)->i_dir_level,
				(le32_to_cpu(fname->hash) % nbucket));

	क्रम (block = bidx; block <= (bidx + nblock - 1); block++) अणु
		dentry_page = f2fs_get_new_data_page(dir, शून्य, block, true);
		अगर (IS_ERR(dentry_page))
			वापस PTR_ERR(dentry_page);

		dentry_blk = page_address(dentry_page);
		bit_pos = f2fs_room_क्रम_filename(&dentry_blk->dentry_biपंचांगap,
						slots, NR_DENTRY_IN_BLOCK);
		अगर (bit_pos < NR_DENTRY_IN_BLOCK)
			जाओ add_dentry;

		f2fs_put_page(dentry_page, 1);
	पूर्ण

	/* Move to next level to find the empty slot क्रम new dentry */
	++level;
	जाओ start;
add_dentry:
	f2fs_रुको_on_page_ग_लिखोback(dentry_page, DATA, true, true);

	अगर (inode) अणु
		करोwn_ग_लिखो(&F2FS_I(inode)->i_sem);
		page = f2fs_init_inode_metadata(inode, dir, fname, शून्य);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			जाओ fail;
		पूर्ण
	पूर्ण

	make_dentry_ptr_block(शून्य, &d, dentry_blk);
	f2fs_update_dentry(ino, mode, &d, &fname->disk_name, fname->hash,
			   bit_pos);

	set_page_dirty(dentry_page);

	अगर (inode) अणु
		f2fs_i_pino_ग_लिखो(inode, dir->i_ino);

		/* synchronize inode page's data from inode cache */
		अगर (is_inode_flag_set(inode, FI_NEW_INODE))
			f2fs_update_inode(inode, page);

		f2fs_put_page(page, 1);
	पूर्ण

	f2fs_update_parent_metadata(dir, inode, current_depth);
fail:
	अगर (inode)
		up_ग_लिखो(&F2FS_I(inode)->i_sem);

	f2fs_put_page(dentry_page, 1);

	वापस err;
पूर्ण

पूर्णांक f2fs_add_dentry(काष्ठा inode *dir, स्थिर काष्ठा f2fs_filename *fname,
		    काष्ठा inode *inode, nid_t ino, umode_t mode)
अणु
	पूर्णांक err = -EAGAIN;

	अगर (f2fs_has_अंतरभूत_dentry(dir))
		err = f2fs_add_अंतरभूत_entry(dir, fname, inode, ino, mode);
	अगर (err == -EAGAIN)
		err = f2fs_add_regular_entry(dir, fname, inode, ino, mode);

	f2fs_update_समय(F2FS_I_SB(dir), REQ_TIME);
	वापस err;
पूर्ण

/*
 * Caller should grab and release a rwsem by calling f2fs_lock_op() and
 * f2fs_unlock_op().
 */
पूर्णांक f2fs_करो_add_link(काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
				काष्ठा inode *inode, nid_t ino, umode_t mode)
अणु
	काष्ठा f2fs_filename fname;
	काष्ठा page *page = शून्य;
	काष्ठा f2fs_dir_entry *de = शून्य;
	पूर्णांक err;

	err = f2fs_setup_filename(dir, name, 0, &fname);
	अगर (err)
		वापस err;

	/*
	 * An immature stackable fileप्रणाली shows a race condition between lookup
	 * and create. If we have same task when करोing lookup and create, it's
	 * definitely fine as expected by VFS normally. Otherwise, let's just
	 * verअगरy on-disk dentry one more समय, which guarantees fileप्रणाली
	 * consistency more.
	 */
	अगर (current != F2FS_I(dir)->task) अणु
		de = __f2fs_find_entry(dir, &fname, &page);
		F2FS_I(dir)->task = शून्य;
	पूर्ण
	अगर (de) अणु
		f2fs_put_page(page, 0);
		err = -EEXIST;
	पूर्ण अन्यथा अगर (IS_ERR(page)) अणु
		err = PTR_ERR(page);
	पूर्ण अन्यथा अणु
		err = f2fs_add_dentry(dir, &fname, inode, ino, mode);
	पूर्ण
	f2fs_मुक्त_filename(&fname);
	वापस err;
पूर्ण

पूर्णांक f2fs_करो_क्षणिक_ख(काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	काष्ठा page *page;
	पूर्णांक err = 0;

	करोwn_ग_लिखो(&F2FS_I(inode)->i_sem);
	page = f2fs_init_inode_metadata(inode, dir, शून्य, शून्य);
	अगर (IS_ERR(page)) अणु
		err = PTR_ERR(page);
		जाओ fail;
	पूर्ण
	f2fs_put_page(page, 1);

	clear_inode_flag(inode, FI_NEW_INODE);
	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
fail:
	up_ग_लिखो(&F2FS_I(inode)->i_sem);
	वापस err;
पूर्ण

व्योम f2fs_drop_nlink(काष्ठा inode *dir, काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dir);

	करोwn_ग_लिखो(&F2FS_I(inode)->i_sem);

	अगर (S_ISसूची(inode->i_mode))
		f2fs_i_links_ग_लिखो(dir, false);
	inode->i_स_समय = current_समय(inode);

	f2fs_i_links_ग_लिखो(inode, false);
	अगर (S_ISसूची(inode->i_mode)) अणु
		f2fs_i_links_ग_लिखो(inode, false);
		f2fs_i_size_ग_लिखो(inode, 0);
	पूर्ण
	up_ग_लिखो(&F2FS_I(inode)->i_sem);

	अगर (inode->i_nlink == 0)
		f2fs_add_orphan_inode(inode);
	अन्यथा
		f2fs_release_orphan_inode(sbi);
पूर्ण

/*
 * It only हटाओs the dentry from the dentry page, corresponding name
 * entry in name page करोes not need to be touched during deletion.
 */
व्योम f2fs_delete_entry(काष्ठा f2fs_dir_entry *dentry, काष्ठा page *page,
					काष्ठा inode *dir, काष्ठा inode *inode)
अणु
	काष्ठा	f2fs_dentry_block *dentry_blk;
	अचिन्हित पूर्णांक bit_pos;
	पूर्णांक slots = GET_DENTRY_SLOTS(le16_to_cpu(dentry->name_len));
	पूर्णांक i;

	f2fs_update_समय(F2FS_I_SB(dir), REQ_TIME);

	अगर (F2FS_OPTION(F2FS_I_SB(dir)).fsync_mode == FSYNC_MODE_STRICT)
		f2fs_add_ino_entry(F2FS_I_SB(dir), dir->i_ino, TRANS_सूची_INO);

	अगर (f2fs_has_अंतरभूत_dentry(dir))
		वापस f2fs_delete_अंतरभूत_entry(dentry, page, dir, inode);

	lock_page(page);
	f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);

	dentry_blk = page_address(page);
	bit_pos = dentry - dentry_blk->dentry;
	क्रम (i = 0; i < slots; i++)
		__clear_bit_le(bit_pos + i, &dentry_blk->dentry_biपंचांगap);

	/* Let's check and deallocate this dentry page */
	bit_pos = find_next_bit_le(&dentry_blk->dentry_biपंचांगap,
			NR_DENTRY_IN_BLOCK,
			0);
	set_page_dirty(page);

	अगर (bit_pos == NR_DENTRY_IN_BLOCK &&
		!f2fs_truncate_hole(dir, page->index, page->index + 1)) अणु
		f2fs_clear_page_cache_dirty_tag(page);
		clear_page_dirty_क्रम_io(page);
		f2fs_clear_page_निजी(page);
		ClearPageUptodate(page);
		clear_cold_data(page);
		inode_dec_dirty_pages(dir);
		f2fs_हटाओ_dirty_inode(dir);
	पूर्ण
	f2fs_put_page(page, 1);

	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	f2fs_mark_inode_dirty_sync(dir, false);

	अगर (inode)
		f2fs_drop_nlink(dir, inode);
पूर्ण

bool f2fs_empty_dir(काष्ठा inode *dir)
अणु
	अचिन्हित दीर्घ bidx;
	काष्ठा page *dentry_page;
	अचिन्हित पूर्णांक bit_pos;
	काष्ठा f2fs_dentry_block *dentry_blk;
	अचिन्हित दीर्घ nblock = dir_blocks(dir);

	अगर (f2fs_has_अंतरभूत_dentry(dir))
		वापस f2fs_empty_अंतरभूत_dir(dir);

	क्रम (bidx = 0; bidx < nblock; bidx++) अणु
		dentry_page = f2fs_get_lock_data_page(dir, bidx, false);
		अगर (IS_ERR(dentry_page)) अणु
			अगर (PTR_ERR(dentry_page) == -ENOENT)
				जारी;
			अन्यथा
				वापस false;
		पूर्ण

		dentry_blk = page_address(dentry_page);
		अगर (bidx == 0)
			bit_pos = 2;
		अन्यथा
			bit_pos = 0;
		bit_pos = find_next_bit_le(&dentry_blk->dentry_biपंचांगap,
						NR_DENTRY_IN_BLOCK,
						bit_pos);

		f2fs_put_page(dentry_page, 1);

		अगर (bit_pos < NR_DENTRY_IN_BLOCK)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक f2fs_fill_dentries(काष्ठा dir_context *ctx, काष्ठा f2fs_dentry_ptr *d,
			अचिन्हित पूर्णांक start_pos, काष्ठा fscrypt_str *fstr)
अणु
	अचिन्हित अक्षर d_type = DT_UNKNOWN;
	अचिन्हित पूर्णांक bit_pos;
	काष्ठा f2fs_dir_entry *de = शून्य;
	काष्ठा fscrypt_str de_name = FSTR_INIT(शून्य, 0);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(d->inode);
	काष्ठा blk_plug plug;
	bool सूची_पढ़ो_ra = sbi->सूची_पढ़ो_ra == 1;
	पूर्णांक err = 0;

	bit_pos = ((अचिन्हित दीर्घ)ctx->pos % d->max);

	अगर (सूची_पढ़ो_ra)
		blk_start_plug(&plug);

	जबतक (bit_pos < d->max) अणु
		bit_pos = find_next_bit_le(d->biपंचांगap, d->max, bit_pos);
		अगर (bit_pos >= d->max)
			अवरोध;

		de = &d->dentry[bit_pos];
		अगर (de->name_len == 0) अणु
			bit_pos++;
			ctx->pos = start_pos + bit_pos;
			prपूर्णांकk_ratelimited(
				"%sF2FS-fs (%s): invalid namelen(0), ino:%u, run fsck to fix.",
				KERN_WARNING, sbi->sb->s_id,
				le32_to_cpu(de->ino));
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			जारी;
		पूर्ण

		d_type = f2fs_get_de_type(de);

		de_name.name = d->filename[bit_pos];
		de_name.len = le16_to_cpu(de->name_len);

		/* check memory boundary beक्रमe moving क्रमward */
		bit_pos += GET_DENTRY_SLOTS(le16_to_cpu(de->name_len));
		अगर (unlikely(bit_pos > d->max ||
				le16_to_cpu(de->name_len) > F2FS_NAME_LEN)) अणु
			f2fs_warn(sbi, "%s: corrupted namelen=%d, run fsck to fix.",
				  __func__, le16_to_cpu(de->name_len));
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			err = -EFSCORRUPTED;
			जाओ out;
		पूर्ण

		अगर (IS_ENCRYPTED(d->inode)) अणु
			पूर्णांक save_len = fstr->len;

			err = fscrypt_fname_disk_to_usr(d->inode,
						(u32)le32_to_cpu(de->hash_code),
						0, &de_name, fstr);
			अगर (err)
				जाओ out;

			de_name = *fstr;
			fstr->len = save_len;
		पूर्ण

		अगर (!dir_emit(ctx, de_name.name, de_name.len,
					le32_to_cpu(de->ino), d_type)) अणु
			err = 1;
			जाओ out;
		पूर्ण

		अगर (सूची_पढ़ो_ra)
			f2fs_ra_node_page(sbi, le32_to_cpu(de->ino));

		ctx->pos = start_pos + bit_pos;
	पूर्ण
out:
	अगर (सूची_पढ़ो_ra)
		blk_finish_plug(&plug);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	अचिन्हित दीर्घ npages = dir_blocks(inode);
	काष्ठा f2fs_dentry_block *dentry_blk = शून्य;
	काष्ठा page *dentry_page = शून्य;
	काष्ठा file_ra_state *ra = &file->f_ra;
	loff_t start_pos = ctx->pos;
	अचिन्हित पूर्णांक n = ((अचिन्हित दीर्घ)ctx->pos / NR_DENTRY_IN_BLOCK);
	काष्ठा f2fs_dentry_ptr d;
	काष्ठा fscrypt_str fstr = FSTR_INIT(शून्य, 0);
	पूर्णांक err = 0;

	अगर (IS_ENCRYPTED(inode)) अणु
		err = fscrypt_prepare_सूची_पढ़ो(inode);
		अगर (err)
			जाओ out;

		err = fscrypt_fname_alloc_buffer(F2FS_NAME_LEN, &fstr);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	अगर (f2fs_has_अंतरभूत_dentry(inode)) अणु
		err = f2fs_पढ़ो_अंतरभूत_dir(file, ctx, &fstr);
		जाओ out_मुक्त;
	पूर्ण

	क्रम (; n < npages; n++, ctx->pos = n * NR_DENTRY_IN_BLOCK) अणु

		/* allow सूची_पढ़ो() to be पूर्णांकerrupted */
		अगर (fatal_संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ out_मुक्त;
		पूर्ण
		cond_resched();

		/* पढ़ोahead क्रम multi pages of dir */
		अगर (npages - n > 1 && !ra_has_index(ra, n))
			page_cache_sync_पढ़ोahead(inode->i_mapping, ra, file, n,
				min(npages - n, (pgoff_t)MAX_सूची_RA_PAGES));

		dentry_page = f2fs_find_data_page(inode, n);
		अगर (IS_ERR(dentry_page)) अणु
			err = PTR_ERR(dentry_page);
			अगर (err == -ENOENT) अणु
				err = 0;
				जारी;
			पूर्ण अन्यथा अणु
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण

		dentry_blk = page_address(dentry_page);

		make_dentry_ptr_block(inode, &d, dentry_blk);

		err = f2fs_fill_dentries(ctx, &d,
				n * NR_DENTRY_IN_BLOCK, &fstr);
		अगर (err) अणु
			f2fs_put_page(dentry_page, 0);
			अवरोध;
		पूर्ण

		f2fs_put_page(dentry_page, 0);
	पूर्ण
out_मुक्त:
	fscrypt_fname_मुक्त_buffer(&fstr);
out:
	trace_f2fs_सूची_पढ़ो(inode, start_pos, ctx->pos, err);
	वापस err < 0 ? err : 0;
पूर्ण

स्थिर काष्ठा file_operations f2fs_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= f2fs_सूची_पढ़ो,
	.fsync		= f2fs_sync_file,
	.unlocked_ioctl	= f2fs_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = f2fs_compat_ioctl,
#पूर्ण_अगर
पूर्ण;
