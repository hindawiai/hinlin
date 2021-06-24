<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * QNX4 file प्रणाली, Linux implementation.
 *
 * Version : 0.2.1
 *
 * Using parts of the xiafs fileप्रणाली.
 *
 * History :
 *
 * 28-05-1998 by Riअक्षरd Frowijn : first release.
 * 20-06-1998 by Frank Denis : Linux 2.1.99+ & dcache support.
 */

#समावेश <linux/buffer_head.h>
#समावेश "qnx4.h"

अटल पूर्णांक qnx4_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	अचिन्हित पूर्णांक offset;
	काष्ठा buffer_head *bh;
	काष्ठा qnx4_inode_entry *de;
	काष्ठा qnx4_link_info *le;
	अचिन्हित दीर्घ blknum;
	पूर्णांक ix, ino;
	पूर्णांक size;

	QNX4DEBUG((KERN_INFO "qnx4_readdir:i_size = %ld\n", (दीर्घ) inode->i_size));
	QNX4DEBUG((KERN_INFO "pos                 = %ld\n", (दीर्घ) ctx->pos));

	जबतक (ctx->pos < inode->i_size) अणु
		blknum = qnx4_block_map(inode, ctx->pos >> QNX4_BLOCK_SIZE_BITS);
		bh = sb_bपढ़ो(inode->i_sb, blknum);
		अगर (bh == शून्य) अणु
			prपूर्णांकk(KERN_ERR "qnx4_readdir: bread failed (%ld)\n", blknum);
			वापस 0;
		पूर्ण
		ix = (ctx->pos >> QNX4_सूची_ENTRY_SIZE_BITS) % QNX4_INODES_PER_BLOCK;
		क्रम (; ix < QNX4_INODES_PER_BLOCK; ix++, ctx->pos += QNX4_सूची_ENTRY_SIZE) अणु
			offset = ix * QNX4_सूची_ENTRY_SIZE;
			de = (काष्ठा qnx4_inode_entry *) (bh->b_data + offset);
			अगर (!de->di_fname[0])
				जारी;
			अगर (!(de->di_status & (QNX4_खाता_USED|QNX4_खाता_LINK)))
				जारी;
			अगर (!(de->di_status & QNX4_खाता_LINK))
				size = QNX4_SHORT_NAME_MAX;
			अन्यथा
				size = QNX4_NAME_MAX;
			size = strnlen(de->di_fname, size);
			QNX4DEBUG((KERN_INFO "qnx4_readdir:%.*s\n", size, de->di_fname));
			अगर (!(de->di_status & QNX4_खाता_LINK))
				ino = blknum * QNX4_INODES_PER_BLOCK + ix - 1;
			अन्यथा अणु
				le  = (काष्ठा qnx4_link_info*)de;
				ino = ( le32_to_cpu(le->dl_inode_blk) - 1 ) *
					QNX4_INODES_PER_BLOCK +
					le->dl_inode_ndx;
			पूर्ण
			अगर (!dir_emit(ctx, de->di_fname, size, ino, DT_UNKNOWN)) अणु
				brअन्यथा(bh);
				वापस 0;
			पूर्ण
		पूर्ण
		brअन्यथा(bh);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations qnx4_dir_operations =
अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= qnx4_सूची_पढ़ो,
	.fsync		= generic_file_fsync,
पूर्ण;

स्थिर काष्ठा inode_operations qnx4_dir_inode_operations =
अणु
	.lookup		= qnx4_lookup,
पूर्ण;
