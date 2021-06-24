<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dir.c
 *
 * Copyright (c) 1999 Al Smith
 */

#समावेश <linux/buffer_head.h>
#समावेश "efs.h"

अटल पूर्णांक efs_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);

स्थिर काष्ठा file_operations efs_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= efs_सूची_पढ़ो,
पूर्ण;

स्थिर काष्ठा inode_operations efs_dir_inode_operations = अणु
	.lookup		= efs_lookup,
पूर्ण;

अटल पूर्णांक efs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	efs_block_t		block;
	पूर्णांक			slot;

	अगर (inode->i_size & (EFS_सूचीBSIZE-1))
		pr_warn("%s(): directory size not a multiple of EFS_DIRBSIZE\n",
			__func__);

	/* work out where this entry can be found */
	block = ctx->pos >> EFS_सूचीBSIZE_BITS;

	/* each block contains at most 256 slots */
	slot  = ctx->pos & 0xff;

	/* look at all blocks */
	जबतक (block < inode->i_blocks) अणु
		काष्ठा efs_dir		*dirblock;
		काष्ठा buffer_head *bh;

		/* पढ़ो the dir block */
		bh = sb_bपढ़ो(inode->i_sb, efs_bmap(inode, block));

		अगर (!bh) अणु
			pr_err("%s(): failed to read dir block %d\n",
			       __func__, block);
			अवरोध;
		पूर्ण

		dirblock = (काष्ठा efs_dir *) bh->b_data; 

		अगर (be16_to_cpu(dirblock->magic) != EFS_सूचीBLK_MAGIC) अणु
			pr_err("%s(): invalid directory block\n", __func__);
			brअन्यथा(bh);
			अवरोध;
		पूर्ण

		क्रम (; slot < dirblock->slots; slot++) अणु
			काष्ठा efs_dentry *dirslot;
			efs_ino_t inodक्रमागत;
			स्थिर अक्षर *nameptr;
			पूर्णांक namelen;

			अगर (dirblock->space[slot] == 0)
				जारी;

			dirslot  = (काष्ठा efs_dentry *) (((अक्षर *) bh->b_data) + EFS_SLOTAT(dirblock, slot));

			inodक्रमागत = be32_to_cpu(dirslot->inode);
			namelen  = dirslot->namelen;
			nameptr  = dirslot->name;
			pr_debug("%s(): block %d slot %d/%d: inode %u, name \"%s\", namelen %u\n",
				 __func__, block, slot, dirblock->slots-1,
				 inodक्रमागत, nameptr, namelen);
			अगर (!namelen)
				जारी;
			/* found the next entry */
			ctx->pos = (block << EFS_सूचीBSIZE_BITS) | slot;

			/* sanity check */
			अगर (nameptr - (अक्षर *) dirblock + namelen > EFS_सूचीBSIZE) अणु
				pr_warn("directory entry %d exceeds directory block\n",
					slot);
				जारी;
			पूर्ण

			/* copy filename and data in dirslot */
			अगर (!dir_emit(ctx, nameptr, namelen, inodक्रमागत, DT_UNKNOWN)) अणु
				brअन्यथा(bh);
				वापस 0;
			पूर्ण
		पूर्ण
		brअन्यथा(bh);

		slot = 0;
		block++;
	पूर्ण
	ctx->pos = (block << EFS_सूचीBSIZE_BITS) | slot;
	वापस 0;
पूर्ण
