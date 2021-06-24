<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/sysv/ialloc.c
 *
 *  minix/biपंचांगap.c
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext/मुक्तlists.c
 *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)
 *
 *  xenix/alloc.c
 *  Copyright (C) 1992  Doug Evans
 *
 *  coh/alloc.c
 *  Copyright (C) 1993  Pascal Haible, Bruno Haible
 *
 *  sysv/ialloc.c
 *  Copyright (C) 1993  Bruno Haible
 *
 *  This file contains code क्रम allocating/मुक्तing inodes.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश "sysv.h"

/* We करोn't trust the value of
   sb->sv_sbd2->s_tinode = *sb->sv_sb_total_मुक्त_inodes
   but we nevertheless keep it up to date. */

/* An inode on disk is considered मुक्त अगर both i_mode == 0 and i_nlink == 0. */

/* वापस &sb->sv_sb_fic_inodes[i] = &sbd->s_inode[i]; */
अटल अंतरभूत sysv_ino_t *
sv_sb_fic_inode(काष्ठा super_block * sb, अचिन्हित पूर्णांक i)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);

	अगर (sbi->s_bh1 == sbi->s_bh2)
		वापस &sbi->s_sb_fic_inodes[i];
	अन्यथा अणु
		/* 512 byte Xenix FS */
		अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा xenix_super_block, s_inode[i]);
		अगर (offset < 512)
			वापस (sysv_ino_t*)(sbi->s_sbd1 + offset);
		अन्यथा
			वापस (sysv_ino_t*)(sbi->s_sbd2 + offset);
	पूर्ण
पूर्ण

काष्ठा sysv_inode *
sysv_raw_inode(काष्ठा super_block *sb, अचिन्हित ino, काष्ठा buffer_head **bh)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	काष्ठा sysv_inode *res;
	पूर्णांक block = sbi->s_firstinodezone + sbi->s_block_base;

	block += (ino-1) >> sbi->s_inodes_per_block_bits;
	*bh = sb_bपढ़ो(sb, block);
	अगर (!*bh)
		वापस शून्य;
	res = (काष्ठा sysv_inode *)(*bh)->b_data;
	वापस res + ((ino-1) & sbi->s_inodes_per_block_1);
पूर्ण

अटल पूर्णांक refill_मुक्त_cache(काष्ठा super_block *sb)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	काष्ठा buffer_head * bh;
	काष्ठा sysv_inode * raw_inode;
	पूर्णांक i = 0, ino;

	ino = SYSV_ROOT_INO+1;
	raw_inode = sysv_raw_inode(sb, ino, &bh);
	अगर (!raw_inode)
		जाओ out;
	जबतक (ino <= sbi->s_ninodes) अणु
		अगर (raw_inode->i_mode == 0 && raw_inode->i_nlink == 0) अणु
			*sv_sb_fic_inode(sb,i++) = cpu_to_fs16(SYSV_SB(sb), ino);
			अगर (i == sbi->s_fic_size)
				अवरोध;
		पूर्ण
		अगर ((ino++ & sbi->s_inodes_per_block_1) == 0) अणु
			brअन्यथा(bh);
			raw_inode = sysv_raw_inode(sb, ino, &bh);
			अगर (!raw_inode)
				जाओ out;
		पूर्ण अन्यथा
			raw_inode++;
	पूर्ण
	brअन्यथा(bh);
out:
	वापस i;
पूर्ण

व्योम sysv_मुक्त_inode(काष्ठा inode * inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	अचिन्हित पूर्णांक ino;
	काष्ठा buffer_head * bh;
	काष्ठा sysv_inode * raw_inode;
	अचिन्हित count;

	sb = inode->i_sb;
	ino = inode->i_ino;
	अगर (ino <= SYSV_ROOT_INO || ino > sbi->s_ninodes) अणु
		prपूर्णांकk("sysv_free_inode: inode 0,1,2 or nonexistent inode\n");
		वापस;
	पूर्ण
	raw_inode = sysv_raw_inode(sb, ino, &bh);
	अगर (!raw_inode) अणु
		prपूर्णांकk("sysv_free_inode: unable to read inode block on device "
		       "%s\n", inode->i_sb->s_id);
		वापस;
	पूर्ण
	mutex_lock(&sbi->s_lock);
	count = fs16_to_cpu(sbi, *sbi->s_sb_fic_count);
	अगर (count < sbi->s_fic_size) अणु
		*sv_sb_fic_inode(sb,count++) = cpu_to_fs16(sbi, ino);
		*sbi->s_sb_fic_count = cpu_to_fs16(sbi, count);
	पूर्ण
	fs16_add(sbi, sbi->s_sb_total_मुक्त_inodes, 1);
	dirty_sb(sb);
	स_रखो(raw_inode, 0, माप(काष्ठा sysv_inode));
	mark_buffer_dirty(bh);
	mutex_unlock(&sbi->s_lock);
	brअन्यथा(bh);
पूर्ण

काष्ठा inode * sysv_new_inode(स्थिर काष्ठा inode * dir, umode_t mode)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	काष्ठा inode *inode;
	sysv_ino_t ino;
	अचिन्हित count;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_NONE
	पूर्ण;

	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&sbi->s_lock);
	count = fs16_to_cpu(sbi, *sbi->s_sb_fic_count);
	अगर (count == 0 || (*sv_sb_fic_inode(sb,count-1) == 0)) अणु
		count = refill_मुक्त_cache(sb);
		अगर (count == 0) अणु
			iput(inode);
			mutex_unlock(&sbi->s_lock);
			वापस ERR_PTR(-ENOSPC);
		पूर्ण
	पूर्ण
	/* Now count > 0. */
	ino = *sv_sb_fic_inode(sb,--count);
	*sbi->s_sb_fic_count = cpu_to_fs16(sbi, count);
	fs16_add(sbi, sbi->s_sb_total_मुक्त_inodes, -1);
	dirty_sb(sb);
	inode_init_owner(&init_user_ns, inode, dir, mode);
	inode->i_ino = fs16_to_cpu(sbi, ino);
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_blocks = 0;
	स_रखो(SYSV_I(inode)->i_data, 0, माप(SYSV_I(inode)->i_data));
	SYSV_I(inode)->i_dir_start_lookup = 0;
	insert_inode_hash(inode);
	mark_inode_dirty(inode);

	sysv_ग_लिखो_inode(inode, &wbc);	/* ensure inode not allocated again */
	mark_inode_dirty(inode);	/* cleared by sysv_ग_लिखो_inode() */
	/* That's it. */
	mutex_unlock(&sbi->s_lock);
	वापस inode;
पूर्ण

अचिन्हित दीर्घ sysv_count_मुक्त_inodes(काष्ठा super_block * sb)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	काष्ठा buffer_head * bh;
	काष्ठा sysv_inode * raw_inode;
	पूर्णांक ino, count, sb_count;

	mutex_lock(&sbi->s_lock);

	sb_count = fs16_to_cpu(sbi, *sbi->s_sb_total_मुक्त_inodes);

	अगर (0)
		जाओ trust_sb;

	/* this causes a lot of disk traffic ... */
	count = 0;
	ino = SYSV_ROOT_INO+1;
	raw_inode = sysv_raw_inode(sb, ino, &bh);
	अगर (!raw_inode)
		जाओ Eio;
	जबतक (ino <= sbi->s_ninodes) अणु
		अगर (raw_inode->i_mode == 0 && raw_inode->i_nlink == 0)
			count++;
		अगर ((ino++ & sbi->s_inodes_per_block_1) == 0) अणु
			brअन्यथा(bh);
			raw_inode = sysv_raw_inode(sb, ino, &bh);
			अगर (!raw_inode)
				जाओ Eio;
		पूर्ण अन्यथा
			raw_inode++;
	पूर्ण
	brअन्यथा(bh);
	अगर (count != sb_count)
		जाओ Einval;
out:
	mutex_unlock(&sbi->s_lock);
	वापस count;

Einval:
	prपूर्णांकk("sysv_count_free_inodes: "
		"free inode count was %d, correcting to %d\n",
		sb_count, count);
	अगर (!sb_rकरोnly(sb)) अणु
		*sbi->s_sb_total_मुक्त_inodes = cpu_to_fs16(SYSV_SB(sb), count);
		dirty_sb(sb);
	पूर्ण
	जाओ out;

Eio:
	prपूर्णांकk("sysv_count_free_inodes: unable to read inode table\n");
trust_sb:
	count = sb_count;
	जाओ out;
पूर्ण
