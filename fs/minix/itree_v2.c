<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/buffer_head.h>
#समावेश "minix.h"

क्रमागत अणुसूचीECT = 7, DEPTH = 4पूर्ण;	/* Have triple indirect */

प्रकार u32 block_t;	/* 32 bit, host order */

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
	वापस (block_t *)minix_i(inode)->u.i2_data;
पूर्ण

#घोषणा सूचीCOUNT 7
#घोषणा INसूचीCOUNT(sb) (1 << ((sb)->s_blocksize_bits - 2))

अटल पूर्णांक block_to_path(काष्ठा inode * inode, दीर्घ block, पूर्णांक offsets[DEPTH])
अणु
	पूर्णांक n = 0;
	काष्ठा super_block *sb = inode->i_sb;

	अगर (block < 0) अणु
		prपूर्णांकk("MINIX-fs: block_to_path: block %ld < 0 on dev %pg\n",
			block, sb->s_bdev);
		वापस 0;
	पूर्ण
	अगर ((u64)block * (u64)sb->s_blocksize >= sb->s_maxbytes)
		वापस 0;

	अगर (block < सूचीCOUNT) अणु
		offsets[n++] = block;
	पूर्ण अन्यथा अगर ((block -= सूचीCOUNT) < INसूचीCOUNT(sb)) अणु
		offsets[n++] = सूचीCOUNT;
		offsets[n++] = block;
	पूर्ण अन्यथा अगर ((block -= INसूचीCOUNT(sb)) < INसूचीCOUNT(sb) * INसूचीCOUNT(sb)) अणु
		offsets[n++] = सूचीCOUNT + 1;
		offsets[n++] = block / INसूचीCOUNT(sb);
		offsets[n++] = block % INसूचीCOUNT(sb);
	पूर्ण अन्यथा अणु
		block -= INसूचीCOUNT(sb) * INसूचीCOUNT(sb);
		offsets[n++] = सूचीCOUNT + 2;
		offsets[n++] = (block / INसूचीCOUNT(sb)) / INसूचीCOUNT(sb);
		offsets[n++] = (block / INसूचीCOUNT(sb)) % INसूचीCOUNT(sb);
		offsets[n++] = block % INसूचीCOUNT(sb);
	पूर्ण
	वापस n;
पूर्ण

#समावेश "itree_common.c"

पूर्णांक V2_minix_get_block(काष्ठा inode * inode, दीर्घ block,
			काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	वापस get_block(inode, block, bh_result, create);
पूर्ण

व्योम V2_minix_truncate(काष्ठा inode * inode)
अणु
	truncate(inode);
पूर्ण

अचिन्हित V2_minix_blocks(loff_t size, काष्ठा super_block *sb)
अणु
	वापस nblocks(size, sb);
पूर्ण
