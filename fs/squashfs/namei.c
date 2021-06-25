<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * namei.c
 */

/*
 * This file implements code to करो filename lookup in directories.
 *
 * Like inodes, directories are packed पूर्णांकo compressed metadata blocks, stored
 * in a directory table.  Directories are accessed using the start address of
 * the metablock containing the directory and the offset पूर्णांकo the
 * decompressed block (<block, offset>).
 *
 * Directories are organised in a slightly complex way, and are not simply
 * a list of file names.  The organisation takes advantage of the
 * fact that (in most हालs) the inodes of the files will be in the same
 * compressed metadata block, and thereक्रमe, can share the start block.
 * Directories are thereक्रमe organised in a two level list, a directory
 * header containing the shared start block value, and a sequence of directory
 * entries, each of which share the shared start block.  A new directory header
 * is written once/अगर the inode start block changes.  The directory
 * header/directory entry list is repeated as many बार as necessary.
 *
 * Directories are sorted, and can contain a directory index to speed up
 * file lookup.  Directory indexes store one entry per metablock, each entry
 * storing the index/filename mapping to the first directory header
 * in each metadata block.  Directories are sorted in alphabetical order,
 * and at lookup the index is scanned linearly looking क्रम the first filename
 * alphabetically larger than the filename being looked up.  At this poपूर्णांक the
 * location of the metadata block the filename is in has been found.
 * The general idea of the index is ensure only one metadata block needs to be
 * decompressed to करो a lookup irrespective of the length of the directory.
 * This scheme has the advantage that it करोesn't require extra memory overhead
 * and करोesn't require much extra storage on disk.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/dcache.h>
#समावेश <linux/xattr.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs_fs_i.h"
#समावेश "squashfs.h"
#समावेश "xattr.h"

/*
 * Lookup name in the directory index, वापसing the location of the metadata
 * block containing it, and the directory index this represents.
 *
 * If we get an error पढ़ोing the index then वापस the part of the index
 * (अगर any) we have managed to पढ़ो - the index isn't essential, just
 * quicker.
 */
अटल पूर्णांक get_dir_index_using_name(काष्ठा super_block *sb,
			u64 *next_block, पूर्णांक *next_offset, u64 index_start,
			पूर्णांक index_offset, पूर्णांक i_count, स्थिर अक्षर *name,
			पूर्णांक len)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	पूर्णांक i, length = 0, err;
	अचिन्हित पूर्णांक size;
	काष्ठा squashfs_dir_index *index;
	अक्षर *str;

	TRACE("Entered get_dir_index_using_name, i_count %d\n", i_count);

	index = kदो_स्मृति(माप(*index) + SQUASHFS_NAME_LEN * 2 + 2, GFP_KERNEL);
	अगर (index == शून्य) अणु
		ERROR("Failed to allocate squashfs_dir_index\n");
		जाओ out;
	पूर्ण

	str = &index->name[SQUASHFS_NAME_LEN + 1];
	म_नकलन(str, name, len);
	str[len] = '\0';

	क्रम (i = 0; i < i_count; i++) अणु
		err = squashfs_पढ़ो_metadata(sb, index, &index_start,
					&index_offset, माप(*index));
		अगर (err < 0)
			अवरोध;


		size = le32_to_cpu(index->size) + 1;
		अगर (size > SQUASHFS_NAME_LEN)
			अवरोध;

		err = squashfs_पढ़ो_metadata(sb, index->name, &index_start,
					&index_offset, size);
		अगर (err < 0)
			अवरोध;

		index->name[size] = '\0';

		अगर (म_भेद(index->name, str) > 0)
			अवरोध;

		length = le32_to_cpu(index->index);
		*next_block = le32_to_cpu(index->start_block) +
					msblk->directory_table;
	पूर्ण

	*next_offset = (length + *next_offset) % SQUASHFS_METADATA_SIZE;
	kमुक्त(index);

out:
	/*
	 * Return index (f_pos) of the looked up metadata block.  Translate
	 * from पूर्णांकernal f_pos to बाह्यal f_pos which is offset by 3 because
	 * we invent "." and ".." entries which are not actually stored in the
	 * directory.
	 */
	वापस length + 3;
पूर्ण


अटल काष्ठा dentry *squashfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				 अचिन्हित पूर्णांक flags)
अणु
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	पूर्णांक len = dentry->d_name.len;
	काष्ठा inode *inode = शून्य;
	काष्ठा squashfs_sb_info *msblk = dir->i_sb->s_fs_info;
	काष्ठा squashfs_dir_header dirh;
	काष्ठा squashfs_dir_entry *dire;
	u64 block = squashfs_i(dir)->start + msblk->directory_table;
	पूर्णांक offset = squashfs_i(dir)->offset;
	पूर्णांक err, length;
	अचिन्हित पूर्णांक dir_count, size;

	TRACE("Entered squashfs_lookup [%llx:%x]\n", block, offset);

	dire = kदो_स्मृति(माप(*dire) + SQUASHFS_NAME_LEN + 1, GFP_KERNEL);
	अगर (dire == शून्य) अणु
		ERROR("Failed to allocate squashfs_dir_entry\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (len > SQUASHFS_NAME_LEN) अणु
		err = -ENAMETOOLONG;
		जाओ failed;
	पूर्ण

	length = get_dir_index_using_name(dir->i_sb, &block, &offset,
				squashfs_i(dir)->dir_idx_start,
				squashfs_i(dir)->dir_idx_offset,
				squashfs_i(dir)->dir_idx_cnt, name, len);

	जबतक (length < i_size_पढ़ो(dir)) अणु
		/*
		 * Read directory header.
		 */
		err = squashfs_पढ़ो_metadata(dir->i_sb, &dirh, &block,
				&offset, माप(dirh));
		अगर (err < 0)
			जाओ पढ़ो_failure;

		length += माप(dirh);

		dir_count = le32_to_cpu(dirh.count) + 1;

		अगर (dir_count > SQUASHFS_सूची_COUNT)
			जाओ data_error;

		जबतक (dir_count--) अणु
			/*
			 * Read directory entry.
			 */
			err = squashfs_पढ़ो_metadata(dir->i_sb, dire, &block,
					&offset, माप(*dire));
			अगर (err < 0)
				जाओ पढ़ो_failure;

			size = le16_to_cpu(dire->size) + 1;

			/* size should never be larger than SQUASHFS_NAME_LEN */
			अगर (size > SQUASHFS_NAME_LEN)
				जाओ data_error;

			err = squashfs_पढ़ो_metadata(dir->i_sb, dire->name,
					&block, &offset, size);
			अगर (err < 0)
				जाओ पढ़ो_failure;

			length += माप(*dire) + size;

			अगर (name[0] < dire->name[0])
				जाओ निकास_lookup;

			अगर (len == size && !म_भेदन(name, dire->name, len)) अणु
				अचिन्हित पूर्णांक blk, off, ino_num;
				दीर्घ दीर्घ ino;
				blk = le32_to_cpu(dirh.start_block);
				off = le16_to_cpu(dire->offset);
				ino_num = le32_to_cpu(dirh.inode_number) +
					(लघु) le16_to_cpu(dire->inode_number);
				ino = SQUASHFS_MKINODE(blk, off);

				TRACE("calling squashfs_iget for directory "
					"entry %s, inode  %x:%x, %d\n", name,
					blk, off, ino_num);

				inode = squashfs_iget(dir->i_sb, ino, ino_num);
				जाओ निकास_lookup;
			पूर्ण
		पूर्ण
	पूर्ण

निकास_lookup:
	kमुक्त(dire);
	वापस d_splice_alias(inode, dentry);

data_error:
	err = -EIO;

पढ़ो_failure:
	ERROR("Unable to read directory block [%llx:%x]\n",
		squashfs_i(dir)->start + msblk->directory_table,
		squashfs_i(dir)->offset);
failed:
	kमुक्त(dire);
	वापस ERR_PTR(err);
पूर्ण


स्थिर काष्ठा inode_operations squashfs_dir_inode_ops = अणु
	.lookup = squashfs_lookup,
	.listxattr = squashfs_listxattr
पूर्ण;
