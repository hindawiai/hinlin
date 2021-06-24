<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश "minix.h"

क्रमागत अणुDEPTH = 3, सूचीECT = 7पूर्ण;	/* Only द्विगुन indirect */

प्रकार u16 block_t;	/* 16 bit, host order */

अटल अंतरभूत अचिन्हित दीर्घ block_to_cpu(block_t n)
अणु
	वापस n;
पूर्ण

अटल अंतरभूत block_t cpu_to_block(अचिन्हित दीर्घ n)
अणु
	वापस n;
पूर्ण

अटल अंतरभूत block_t *i_data(काष्ठा inode *inode)
अणु
	वापस (block_t *)minix_i(inode)->u.i1_data;
पूर्ण

अटल पूर्णांक block_to_path(काष्ठा inode * inode, दीर्घ block, पूर्णांक offsets[DEPTH])
अणु
	पूर्णांक n = 0;

	अगर (block < 0) अणु
		prपूर्णांकk("MINIX-fs: block_to_path: block %ld < 0 on dev %pg\n",
			block, inode->i_sb->s_bdev);
		वापस 0;
	पूर्ण
	अगर ((u64)block * BLOCK_SIZE >= inode->i_sb->s_maxbytes)
		वापस 0;

	अगर (block < 7) अणु
		offsets[n++] = block;
	पूर्ण अन्यथा अगर ((block -= 7) < 512) अणु
		offsets[n++] = 7;
		offsets[n++] = block;
	पूर्ण अन्यथा अणु
		block -= 512;
		offsets[n++] = 8;
		offsets[n++] = block>>9;
		offsets[n++] = block & 511;
	पूर्ण
	वापस n;
पूर्ण

#समावेश "itree_common.c"

पूर्णांक V1_minix_get_block(काष्ठा inode * inode, दीर्घ block,
			काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	वापस get_block(inode, block, bh_result, create);
पूर्ण

व्योम V1_minix_truncate(काष्ठा inode * inode)
अणु
	truncate(inode);
पूर्ण

अचिन्हित V1_minix_blocks(loff_t size, काष्ठा super_block *sb)
अणु
	वापस nblocks(size, sb);
पूर्ण
