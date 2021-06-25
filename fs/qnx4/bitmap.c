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
 * 20-06-1998 by Frank Denis : basic optimisations.
 * 25-06-1998 by Frank Denis : qnx4_is_मुक्त, qnx4_set_biपंचांगap, qnx4_bmap .
 * 28-06-1998 by Frank Denis : qnx4_मुक्त_inode (to be fixed) .
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/bitops.h>
#समावेश "qnx4.h"

अचिन्हित दीर्घ qnx4_count_मुक्त_blocks(काष्ठा super_block *sb)
अणु
	पूर्णांक start = le32_to_cpu(qnx4_sb(sb)->BitMap->di_first_xtnt.xtnt_blk) - 1;
	पूर्णांक total = 0;
	पूर्णांक total_मुक्त = 0;
	पूर्णांक offset = 0;
	पूर्णांक size = le32_to_cpu(qnx4_sb(sb)->BitMap->di_size);
	काष्ठा buffer_head *bh;

	जबतक (total < size) अणु
		पूर्णांक bytes = min(size - total, QNX4_BLOCK_SIZE);

		अगर ((bh = sb_bपढ़ो(sb, start + offset)) == शून्य) अणु
			prपूर्णांकk(KERN_ERR "qnx4: I/O error in counting free blocks\n");
			अवरोध;
		पूर्ण
		total_मुक्त += bytes * BITS_PER_BYTE -
				memweight(bh->b_data, bytes);
		brअन्यथा(bh);
		total += bytes;
		offset++;
	पूर्ण

	वापस total_मुक्त;
पूर्ण
