<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * QNX6 file प्रणाली, Linux implementation.
 *
 * Version : 1.0.0
 *
 * History :
 *
 * 01-02-2012 by Kai Bankett (chaosman@ontika.net) : first release.
 *
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc32.h>
#समावेश "qnx6.h"

अटल व्योम qnx6_mmi_copy_sb(काष्ठा qnx6_super_block *qsb,
		काष्ठा qnx6_mmi_super_block *sb)
अणु
	qsb->sb_magic = sb->sb_magic;
	qsb->sb_checksum = sb->sb_checksum;
	qsb->sb_serial = sb->sb_serial;
	qsb->sb_blocksize = sb->sb_blocksize;
	qsb->sb_num_inodes = sb->sb_num_inodes;
	qsb->sb_मुक्त_inodes = sb->sb_मुक्त_inodes;
	qsb->sb_num_blocks = sb->sb_num_blocks;
	qsb->sb_मुक्त_blocks = sb->sb_मुक्त_blocks;

	/* the rest of the superblock is the same */
	स_नकल(&qsb->Inode, &sb->Inode, माप(sb->Inode));
	स_नकल(&qsb->Biपंचांगap, &sb->Biपंचांगap, माप(sb->Biपंचांगap));
	स_नकल(&qsb->Longfile, &sb->Longfile, माप(sb->Longfile));
पूर्ण

काष्ठा qnx6_super_block *qnx6_mmi_fill_super(काष्ठा super_block *s, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh1, *bh2 = शून्य;
	काष्ठा qnx6_mmi_super_block *sb1, *sb2;
	काष्ठा qnx6_super_block *qsb = शून्य;
	काष्ठा qnx6_sb_info *sbi;
	__u64 offset;

	/* Check the superblock signatures
	   start with the first superblock */
	bh1 = sb_bपढ़ो(s, 0);
	अगर (!bh1) अणु
		pr_err("Unable to read first mmi superblock\n");
		वापस शून्य;
	पूर्ण
	sb1 = (काष्ठा qnx6_mmi_super_block *)bh1->b_data;
	sbi = QNX6_SB(s);
	अगर (fs32_to_cpu(sbi, sb1->sb_magic) != QNX6_SUPER_MAGIC) अणु
		अगर (!silent) अणु
			pr_err("wrong signature (magic) in superblock #1.\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* checksum check - start at byte 8 and end at byte 512 */
	अगर (fs32_to_cpu(sbi, sb1->sb_checksum) !=
				crc32_be(0, (अक्षर *)(bh1->b_data + 8), 504)) अणु
		pr_err("superblock #1 checksum error\n");
		जाओ out;
	पूर्ण

	/* calculate second superblock blocknumber */
	offset = fs32_to_cpu(sbi, sb1->sb_num_blocks) + QNX6_SUPERBLOCK_AREA /
					fs32_to_cpu(sbi, sb1->sb_blocksize);

	/* set new blocksize */
	अगर (!sb_set_blocksize(s, fs32_to_cpu(sbi, sb1->sb_blocksize))) अणु
		pr_err("unable to set blocksize\n");
		जाओ out;
	पूर्ण
	/* blocksize invalidates bh - pull it back in */
	brअन्यथा(bh1);
	bh1 = sb_bपढ़ो(s, 0);
	अगर (!bh1)
		जाओ out;
	sb1 = (काष्ठा qnx6_mmi_super_block *)bh1->b_data;

	/* पढ़ो second superblock */
	bh2 = sb_bपढ़ो(s, offset);
	अगर (!bh2) अणु
		pr_err("unable to read the second superblock\n");
		जाओ out;
	पूर्ण
	sb2 = (काष्ठा qnx6_mmi_super_block *)bh2->b_data;
	अगर (fs32_to_cpu(sbi, sb2->sb_magic) != QNX6_SUPER_MAGIC) अणु
		अगर (!silent)
			pr_err("wrong signature (magic) in superblock #2.\n");
		जाओ out;
	पूर्ण

	/* checksum check - start at byte 8 and end at byte 512 */
	अगर (fs32_to_cpu(sbi, sb2->sb_checksum)
			!= crc32_be(0, (अक्षर *)(bh2->b_data + 8), 504)) अणु
		pr_err("superblock #1 checksum error\n");
		जाओ out;
	पूर्ण

	qsb = kदो_स्मृति(माप(*qsb), GFP_KERNEL);
	अगर (!qsb) अणु
		pr_err("unable to allocate memory.\n");
		जाओ out;
	पूर्ण

	अगर (fs64_to_cpu(sbi, sb1->sb_serial) >
					fs64_to_cpu(sbi, sb2->sb_serial)) अणु
		/* superblock #1 active */
		qnx6_mmi_copy_sb(qsb, sb1);
#अगर_घोषित CONFIG_QNX6FS_DEBUG
		qnx6_superblock_debug(qsb, s);
#पूर्ण_अगर
		स_नकल(bh1->b_data, qsb, माप(काष्ठा qnx6_super_block));

		sbi->sb_buf = bh1;
		sbi->sb = (काष्ठा qnx6_super_block *)bh1->b_data;
		brअन्यथा(bh2);
		pr_info("superblock #1 active\n");
	पूर्ण अन्यथा अणु
		/* superblock #2 active */
		qnx6_mmi_copy_sb(qsb, sb2);
#अगर_घोषित CONFIG_QNX6FS_DEBUG
		qnx6_superblock_debug(qsb, s);
#पूर्ण_अगर
		स_नकल(bh2->b_data, qsb, माप(काष्ठा qnx6_super_block));

		sbi->sb_buf = bh2;
		sbi->sb = (काष्ठा qnx6_super_block *)bh2->b_data;
		brअन्यथा(bh1);
		pr_info("superblock #2 active\n");
	पूर्ण
	kमुक्त(qsb);

	/* offset क्रम mmi_fs is just SUPERBLOCK_AREA bytes */
	sbi->s_blks_off = QNX6_SUPERBLOCK_AREA / s->s_blocksize;

	/* success */
	वापस sbi->sb;

out:
	अगर (bh1 != शून्य)
		brअन्यथा(bh1);
	अगर (bh2 != शून्य)
		brअन्यथा(bh2);
	वापस शून्य;
पूर्ण
