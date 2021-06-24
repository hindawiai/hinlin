<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * inode.c
 */

/*
 * This file implements code to create and पढ़ो inodes from disk.
 *
 * Inodes in Squashfs are identअगरied by a 48-bit inode which encodes the
 * location of the compressed metadata block containing the inode, and the byte
 * offset पूर्णांकo that block where the inode is placed (<block, offset>).
 *
 * To maximise compression there are dअगरferent inodes क्रम each file type
 * (regular file, directory, device, etc.), the inode contents and length
 * varying with the type.
 *
 * To further maximise compression, two types of regular file inode and
 * directory inode are defined: inodes optimised क्रम frequently occurring
 * regular files and directories, and extended types where extra
 * inक्रमmation has to be stored.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/xattr.h>
#समावेश <linux/pagemap.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs_fs_i.h"
#समावेश "squashfs.h"
#समावेश "xattr.h"

/*
 * Initialise VFS inode with the base inode inक्रमmation common to all
 * Squashfs inode types.  Sqsh_ino contains the unswapped base inode
 * off disk.
 */
अटल पूर्णांक squashfs_new_inode(काष्ठा super_block *sb, काष्ठा inode *inode,
				काष्ठा squashfs_base_inode *sqsh_ino)
अणु
	uid_t i_uid;
	gid_t i_gid;
	पूर्णांक err;

	err = squashfs_get_id(sb, le16_to_cpu(sqsh_ino->uid), &i_uid);
	अगर (err)
		वापस err;

	err = squashfs_get_id(sb, le16_to_cpu(sqsh_ino->guid), &i_gid);
	अगर (err)
		वापस err;

	i_uid_ग_लिखो(inode, i_uid);
	i_gid_ग_लिखो(inode, i_gid);
	inode->i_ino = le32_to_cpu(sqsh_ino->inode_number);
	inode->i_mसमय.tv_sec = le32_to_cpu(sqsh_ino->mसमय);
	inode->i_aसमय.tv_sec = inode->i_mसमय.tv_sec;
	inode->i_स_समय.tv_sec = inode->i_mसमय.tv_sec;
	inode->i_mode = le16_to_cpu(sqsh_ino->mode);
	inode->i_size = 0;

	वापस err;
पूर्ण


काष्ठा inode *squashfs_iget(काष्ठा super_block *sb, दीर्घ दीर्घ ino,
				अचिन्हित पूर्णांक ino_number)
अणु
	काष्ठा inode *inode = iget_locked(sb, ino_number);
	पूर्णांक err;

	TRACE("Entered squashfs_iget\n");

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	err = squashfs_पढ़ो_inode(inode, ino);
	अगर (err) अणु
		iget_failed(inode);
		वापस ERR_PTR(err);
	पूर्ण

	unlock_new_inode(inode);
	वापस inode;
पूर्ण


/*
 * Initialise VFS inode by पढ़ोing inode from inode table (compressed
 * metadata).  The क्रमmat and amount of data पढ़ो depends on type.
 */
पूर्णांक squashfs_पढ़ो_inode(काष्ठा inode *inode, दीर्घ दीर्घ ino)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	u64 block = SQUASHFS_INODE_BLK(ino) + msblk->inode_table;
	पूर्णांक err, type, offset = SQUASHFS_INODE_OFFSET(ino);
	जोड़ squashfs_inode squashfs_ino;
	काष्ठा squashfs_base_inode *sqshb_ino = &squashfs_ino.base;
	पूर्णांक xattr_id = SQUASHFS_INVALID_XATTR;

	TRACE("Entered squashfs_read_inode\n");

	/*
	 * Read inode base common to all inode types.
	 */
	err = squashfs_पढ़ो_metadata(sb, sqshb_ino, &block,
				&offset, माप(*sqshb_ino));
	अगर (err < 0)
		जाओ failed_पढ़ो;

	err = squashfs_new_inode(sb, inode, sqshb_ino);
	अगर (err)
		जाओ failed_पढ़ो;

	block = SQUASHFS_INODE_BLK(ino) + msblk->inode_table;
	offset = SQUASHFS_INODE_OFFSET(ino);

	type = le16_to_cpu(sqshb_ino->inode_type);
	चयन (type) अणु
	हाल SQUASHFS_REG_TYPE: अणु
		अचिन्हित पूर्णांक frag_offset, frag;
		पूर्णांक frag_size;
		u64 frag_blk;
		काष्ठा squashfs_reg_inode *sqsh_ino = &squashfs_ino.reg;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
							माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		frag = le32_to_cpu(sqsh_ino->fragment);
		अगर (frag != SQUASHFS_INVALID_FRAG) अणु
			frag_offset = le32_to_cpu(sqsh_ino->offset);
			frag_size = squashfs_frag_lookup(sb, frag, &frag_blk);
			अगर (frag_size < 0) अणु
				err = frag_size;
				जाओ failed_पढ़ो;
			पूर्ण
		पूर्ण अन्यथा अणु
			frag_blk = SQUASHFS_INVALID_BLK;
			frag_size = 0;
			frag_offset = 0;
		पूर्ण

		set_nlink(inode, 1);
		inode->i_size = le32_to_cpu(sqsh_ino->file_size);
		inode->i_fop = &generic_ro_fops;
		inode->i_mode |= S_IFREG;
		inode->i_blocks = ((inode->i_size - 1) >> 9) + 1;
		squashfs_i(inode)->fragment_block = frag_blk;
		squashfs_i(inode)->fragment_size = frag_size;
		squashfs_i(inode)->fragment_offset = frag_offset;
		squashfs_i(inode)->start = le32_to_cpu(sqsh_ino->start_block);
		squashfs_i(inode)->block_list_start = block;
		squashfs_i(inode)->offset = offset;
		inode->i_data.a_ops = &squashfs_aops;

		TRACE("File inode %x:%x, start_block %llx, block_list_start "
			"%llx, offset %x\n", SQUASHFS_INODE_BLK(ino),
			offset, squashfs_i(inode)->start, block, offset);
		अवरोध;
	पूर्ण
	हाल SQUASHFS_LREG_TYPE: अणु
		अचिन्हित पूर्णांक frag_offset, frag;
		पूर्णांक frag_size;
		u64 frag_blk;
		काष्ठा squashfs_lreg_inode *sqsh_ino = &squashfs_ino.lreg;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
							माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		frag = le32_to_cpu(sqsh_ino->fragment);
		अगर (frag != SQUASHFS_INVALID_FRAG) अणु
			frag_offset = le32_to_cpu(sqsh_ino->offset);
			frag_size = squashfs_frag_lookup(sb, frag, &frag_blk);
			अगर (frag_size < 0) अणु
				err = frag_size;
				जाओ failed_पढ़ो;
			पूर्ण
		पूर्ण अन्यथा अणु
			frag_blk = SQUASHFS_INVALID_BLK;
			frag_size = 0;
			frag_offset = 0;
		पूर्ण

		xattr_id = le32_to_cpu(sqsh_ino->xattr);
		set_nlink(inode, le32_to_cpu(sqsh_ino->nlink));
		inode->i_size = le64_to_cpu(sqsh_ino->file_size);
		inode->i_op = &squashfs_inode_ops;
		inode->i_fop = &generic_ro_fops;
		inode->i_mode |= S_IFREG;
		inode->i_blocks = (inode->i_size -
				le64_to_cpu(sqsh_ino->sparse) + 511) >> 9;

		squashfs_i(inode)->fragment_block = frag_blk;
		squashfs_i(inode)->fragment_size = frag_size;
		squashfs_i(inode)->fragment_offset = frag_offset;
		squashfs_i(inode)->start = le64_to_cpu(sqsh_ino->start_block);
		squashfs_i(inode)->block_list_start = block;
		squashfs_i(inode)->offset = offset;
		inode->i_data.a_ops = &squashfs_aops;

		TRACE("File inode %x:%x, start_block %llx, block_list_start "
			"%llx, offset %x\n", SQUASHFS_INODE_BLK(ino),
			offset, squashfs_i(inode)->start, block, offset);
		अवरोध;
	पूर्ण
	हाल SQUASHFS_सूची_TYPE: अणु
		काष्ठा squashfs_dir_inode *sqsh_ino = &squashfs_ino.dir;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
				माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		set_nlink(inode, le32_to_cpu(sqsh_ino->nlink));
		inode->i_size = le16_to_cpu(sqsh_ino->file_size);
		inode->i_op = &squashfs_dir_inode_ops;
		inode->i_fop = &squashfs_dir_ops;
		inode->i_mode |= S_IFसूची;
		squashfs_i(inode)->start = le32_to_cpu(sqsh_ino->start_block);
		squashfs_i(inode)->offset = le16_to_cpu(sqsh_ino->offset);
		squashfs_i(inode)->dir_idx_cnt = 0;
		squashfs_i(inode)->parent = le32_to_cpu(sqsh_ino->parent_inode);

		TRACE("Directory inode %x:%x, start_block %llx, offset %x\n",
				SQUASHFS_INODE_BLK(ino), offset,
				squashfs_i(inode)->start,
				le16_to_cpu(sqsh_ino->offset));
		अवरोध;
	पूर्ण
	हाल SQUASHFS_Lसूची_TYPE: अणु
		काष्ठा squashfs_ldir_inode *sqsh_ino = &squashfs_ino.ldir;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
				माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		xattr_id = le32_to_cpu(sqsh_ino->xattr);
		set_nlink(inode, le32_to_cpu(sqsh_ino->nlink));
		inode->i_size = le32_to_cpu(sqsh_ino->file_size);
		inode->i_op = &squashfs_dir_inode_ops;
		inode->i_fop = &squashfs_dir_ops;
		inode->i_mode |= S_IFसूची;
		squashfs_i(inode)->start = le32_to_cpu(sqsh_ino->start_block);
		squashfs_i(inode)->offset = le16_to_cpu(sqsh_ino->offset);
		squashfs_i(inode)->dir_idx_start = block;
		squashfs_i(inode)->dir_idx_offset = offset;
		squashfs_i(inode)->dir_idx_cnt = le16_to_cpu(sqsh_ino->i_count);
		squashfs_i(inode)->parent = le32_to_cpu(sqsh_ino->parent_inode);

		TRACE("Long directory inode %x:%x, start_block %llx, offset "
				"%x\n", SQUASHFS_INODE_BLK(ino), offset,
				squashfs_i(inode)->start,
				le16_to_cpu(sqsh_ino->offset));
		अवरोध;
	पूर्ण
	हाल SQUASHFS_SYMLINK_TYPE:
	हाल SQUASHFS_LSYMLINK_TYPE: अणु
		काष्ठा squashfs_symlink_inode *sqsh_ino = &squashfs_ino.symlink;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
				माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		set_nlink(inode, le32_to_cpu(sqsh_ino->nlink));
		inode->i_size = le32_to_cpu(sqsh_ino->symlink_size);
		inode->i_op = &squashfs_symlink_inode_ops;
		inode_nohighmem(inode);
		inode->i_data.a_ops = &squashfs_symlink_aops;
		inode->i_mode |= S_IFLNK;
		squashfs_i(inode)->start = block;
		squashfs_i(inode)->offset = offset;

		अगर (type == SQUASHFS_LSYMLINK_TYPE) अणु
			__le32 xattr;

			err = squashfs_पढ़ो_metadata(sb, शून्य, &block,
						&offset, inode->i_size);
			अगर (err < 0)
				जाओ failed_पढ़ो;
			err = squashfs_पढ़ो_metadata(sb, &xattr, &block,
						&offset, माप(xattr));
			अगर (err < 0)
				जाओ failed_पढ़ो;
			xattr_id = le32_to_cpu(xattr);
		पूर्ण

		TRACE("Symbolic link inode %x:%x, start_block %llx, offset "
				"%x\n", SQUASHFS_INODE_BLK(ino), offset,
				block, offset);
		अवरोध;
	पूर्ण
	हाल SQUASHFS_BLKDEV_TYPE:
	हाल SQUASHFS_CHRDEV_TYPE: अणु
		काष्ठा squashfs_dev_inode *sqsh_ino = &squashfs_ino.dev;
		अचिन्हित पूर्णांक rdev;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
				माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		अगर (type == SQUASHFS_CHRDEV_TYPE)
			inode->i_mode |= S_IFCHR;
		अन्यथा
			inode->i_mode |= S_IFBLK;
		set_nlink(inode, le32_to_cpu(sqsh_ino->nlink));
		rdev = le32_to_cpu(sqsh_ino->rdev);
		init_special_inode(inode, inode->i_mode, new_decode_dev(rdev));

		TRACE("Device inode %x:%x, rdev %x\n",
				SQUASHFS_INODE_BLK(ino), offset, rdev);
		अवरोध;
	पूर्ण
	हाल SQUASHFS_LBLKDEV_TYPE:
	हाल SQUASHFS_LCHRDEV_TYPE: अणु
		काष्ठा squashfs_ldev_inode *sqsh_ino = &squashfs_ino.ldev;
		अचिन्हित पूर्णांक rdev;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
				माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		अगर (type == SQUASHFS_LCHRDEV_TYPE)
			inode->i_mode |= S_IFCHR;
		अन्यथा
			inode->i_mode |= S_IFBLK;
		xattr_id = le32_to_cpu(sqsh_ino->xattr);
		inode->i_op = &squashfs_inode_ops;
		set_nlink(inode, le32_to_cpu(sqsh_ino->nlink));
		rdev = le32_to_cpu(sqsh_ino->rdev);
		init_special_inode(inode, inode->i_mode, new_decode_dev(rdev));

		TRACE("Device inode %x:%x, rdev %x\n",
				SQUASHFS_INODE_BLK(ino), offset, rdev);
		अवरोध;
	पूर्ण
	हाल SQUASHFS_FIFO_TYPE:
	हाल SQUASHFS_SOCKET_TYPE: अणु
		काष्ठा squashfs_ipc_inode *sqsh_ino = &squashfs_ino.ipc;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
				माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		अगर (type == SQUASHFS_FIFO_TYPE)
			inode->i_mode |= S_IFIFO;
		अन्यथा
			inode->i_mode |= S_IFSOCK;
		set_nlink(inode, le32_to_cpu(sqsh_ino->nlink));
		init_special_inode(inode, inode->i_mode, 0);
		अवरोध;
	पूर्ण
	हाल SQUASHFS_LFIFO_TYPE:
	हाल SQUASHFS_LSOCKET_TYPE: अणु
		काष्ठा squashfs_lipc_inode *sqsh_ino = &squashfs_ino.lipc;

		err = squashfs_पढ़ो_metadata(sb, sqsh_ino, &block, &offset,
				माप(*sqsh_ino));
		अगर (err < 0)
			जाओ failed_पढ़ो;

		अगर (type == SQUASHFS_LFIFO_TYPE)
			inode->i_mode |= S_IFIFO;
		अन्यथा
			inode->i_mode |= S_IFSOCK;
		xattr_id = le32_to_cpu(sqsh_ino->xattr);
		inode->i_op = &squashfs_inode_ops;
		set_nlink(inode, le32_to_cpu(sqsh_ino->nlink));
		init_special_inode(inode, inode->i_mode, 0);
		अवरोध;
	पूर्ण
	शेष:
		ERROR("Unknown inode type %d in squashfs_iget!\n", type);
		वापस -EINVAL;
	पूर्ण

	अगर (xattr_id != SQUASHFS_INVALID_XATTR && msblk->xattr_id_table) अणु
		err = squashfs_xattr_lookup(sb, xattr_id,
					&squashfs_i(inode)->xattr_count,
					&squashfs_i(inode)->xattr_size,
					&squashfs_i(inode)->xattr);
		अगर (err < 0)
			जाओ failed_पढ़ो;
		inode->i_blocks += ((squashfs_i(inode)->xattr_size - 1) >> 9)
				+ 1;
	पूर्ण अन्यथा
		squashfs_i(inode)->xattr_count = 0;

	वापस 0;

failed_पढ़ो:
	ERROR("Unable to read inode 0x%llx\n", ino);
	वापस err;
पूर्ण


स्थिर काष्ठा inode_operations squashfs_inode_ops = अणु
	.listxattr = squashfs_listxattr
पूर्ण;

