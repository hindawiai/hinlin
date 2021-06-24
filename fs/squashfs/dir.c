<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * dir.c
 */

/*
 * This file implements code to पढ़ो directories from disk.
 *
 * See namei.c क्रम a description of directory organisation on disk.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs_fs_i.h"
#समावेश "squashfs.h"

अटल स्थिर अचिन्हित अक्षर squashfs_filetype_table[] = अणु
	DT_UNKNOWN, DT_सूची, DT_REG, DT_LNK, DT_BLK, DT_CHR, DT_FIFO, DT_SOCK
पूर्ण;

/*
 * Lookup offset (f_pos) in the directory index, वापसing the
 * metadata block containing it.
 *
 * If we get an error पढ़ोing the index then वापस the part of the index
 * (अगर any) we have managed to पढ़ो - the index isn't essential, just
 * quicker.
 */
अटल पूर्णांक get_dir_index_using_offset(काष्ठा super_block *sb,
	u64 *next_block, पूर्णांक *next_offset, u64 index_start, पूर्णांक index_offset,
	पूर्णांक i_count, u64 f_pos)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	पूर्णांक err, i, index, length = 0;
	अचिन्हित पूर्णांक size;
	काष्ठा squashfs_dir_index dir_index;

	TRACE("Entered get_dir_index_using_offset, i_count %d, f_pos %lld\n",
					i_count, f_pos);

	/*
	 * Translate from बाह्यal f_pos to the पूर्णांकernal f_pos.  This
	 * is offset by 3 because we invent "." and ".." entries which are
	 * not actually stored in the directory.
	 */
	अगर (f_pos <= 3)
		वापस f_pos;
	f_pos -= 3;

	क्रम (i = 0; i < i_count; i++) अणु
		err = squashfs_पढ़ो_metadata(sb, &dir_index, &index_start,
				&index_offset, माप(dir_index));
		अगर (err < 0)
			अवरोध;

		index = le32_to_cpu(dir_index.index);
		अगर (index > f_pos)
			/*
			 * Found the index we're looking क्रम.
			 */
			अवरोध;

		size = le32_to_cpu(dir_index.size) + 1;

		/* size should never be larger than SQUASHFS_NAME_LEN */
		अगर (size > SQUASHFS_NAME_LEN)
			अवरोध;

		err = squashfs_पढ़ो_metadata(sb, शून्य, &index_start,
				&index_offset, size);
		अगर (err < 0)
			अवरोध;

		length = index;
		*next_block = le32_to_cpu(dir_index.start_block) +
					msblk->directory_table;
	पूर्ण

	*next_offset = (length + *next_offset) % SQUASHFS_METADATA_SIZE;

	/*
	 * Translate back from पूर्णांकernal f_pos to बाह्यal f_pos.
	 */
	वापस length + 3;
पूर्ण


अटल पूर्णांक squashfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	u64 block = squashfs_i(inode)->start + msblk->directory_table;
	पूर्णांक offset = squashfs_i(inode)->offset, length, err;
	अचिन्हित पूर्णांक inode_number, dir_count, size, type;
	काष्ठा squashfs_dir_header dirh;
	काष्ठा squashfs_dir_entry *dire;

	TRACE("Entered squashfs_readdir [%llx:%x]\n", block, offset);

	dire = kदो_स्मृति(माप(*dire) + SQUASHFS_NAME_LEN + 1, GFP_KERNEL);
	अगर (dire == शून्य) अणु
		ERROR("Failed to allocate squashfs_dir_entry\n");
		जाओ finish;
	पूर्ण

	/*
	 * Return "." and  ".." entries as the first two filenames in the
	 * directory.  To maximise compression these two entries are not
	 * stored in the directory, and so we invent them here.
	 *
	 * It also means that the बाह्यal f_pos is offset by 3 from the
	 * on-disk directory f_pos.
	 */
	जबतक (ctx->pos < 3) अणु
		अक्षर *name;
		पूर्णांक i_ino;

		अगर (ctx->pos == 0) अणु
			name = ".";
			size = 1;
			i_ino = inode->i_ino;
		पूर्ण अन्यथा अणु
			name = "..";
			size = 2;
			i_ino = squashfs_i(inode)->parent;
		पूर्ण

		अगर (!dir_emit(ctx, name, size, i_ino,
				squashfs_filetype_table[1]))
			जाओ finish;

		ctx->pos += size;
	पूर्ण

	length = get_dir_index_using_offset(inode->i_sb, &block, &offset,
				squashfs_i(inode)->dir_idx_start,
				squashfs_i(inode)->dir_idx_offset,
				squashfs_i(inode)->dir_idx_cnt,
				ctx->pos);

	जबतक (length < i_size_पढ़ो(inode)) अणु
		/*
		 * Read directory header
		 */
		err = squashfs_पढ़ो_metadata(inode->i_sb, &dirh, &block,
					&offset, माप(dirh));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		length += माप(dirh);

		dir_count = le32_to_cpu(dirh.count) + 1;

		अगर (dir_count > SQUASHFS_सूची_COUNT)
			जाओ failed_पढ़ो;

		जबतक (dir_count--) अणु
			/*
			 * Read directory entry.
			 */
			err = squashfs_पढ़ो_metadata(inode->i_sb, dire, &block,
					&offset, माप(*dire));
			अगर (err < 0)
				जाओ failed_पढ़ो;

			size = le16_to_cpu(dire->size) + 1;

			/* size should never be larger than SQUASHFS_NAME_LEN */
			अगर (size > SQUASHFS_NAME_LEN)
				जाओ failed_पढ़ो;

			err = squashfs_पढ़ो_metadata(inode->i_sb, dire->name,
					&block, &offset, size);
			अगर (err < 0)
				जाओ failed_पढ़ो;

			length += माप(*dire) + size;

			अगर (ctx->pos >= length)
				जारी;

			dire->name[size] = '\0';
			inode_number = le32_to_cpu(dirh.inode_number) +
				((लघु) le16_to_cpu(dire->inode_number));
			type = le16_to_cpu(dire->type);

			अगर (type > SQUASHFS_MAX_सूची_TYPE)
				जाओ failed_पढ़ो;

			अगर (!dir_emit(ctx, dire->name, size,
					inode_number,
					squashfs_filetype_table[type]))
				जाओ finish;

			ctx->pos = length;
		पूर्ण
	पूर्ण

finish:
	kमुक्त(dire);
	वापस 0;

failed_पढ़ो:
	ERROR("Unable to read directory block [%llx:%x]\n", block, offset);
	kमुक्त(dire);
	वापस 0;
पूर्ण


स्थिर काष्ठा file_operations squashfs_dir_ops = अणु
	.पढ़ो = generic_पढ़ो_dir,
	.iterate_shared = squashfs_सूची_पढ़ो,
	.llseek = generic_file_llseek,
पूर्ण;
