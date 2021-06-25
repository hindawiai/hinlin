<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ufs/ialloc.c
 *
 * Copyright (c) 1998
 * Daniel Pirkl <daniel.pirkl@email.cz>
 * Charles University, Faculty of Mathematics and Physics
 *
 *  from
 *
 *  linux/fs/ext2/ialloc.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  BSD ufs-inspired inode and directory allocation by 
 *  Stephen Tweedie (sct@dcs.ed.ac.uk), 1993
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 *
 * UFS2 ग_लिखो support added by
 * Evgeniy Dushistov <dushistov@mail.ru>, 2007
 */

#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "ufs_fs.h"
#समावेश "ufs.h"
#समावेश "swab.h"
#समावेश "util.h"

/*
 * NOTE! When we get the inode, we're the only people
 * that have access to it, and as such there are no
 * race conditions we have to worry about. The inode
 * is not on the hash-lists, and it cannot be reached
 * through the fileप्रणाली because the directory entry
 * has been deleted earlier.
 *
 * HOWEVER: we must make sure that we get no aliases,
 * which means that we have to call "clear_inode()"
 * _beक्रमe_ we mark the inode not in use in the inode
 * biपंचांगaps. Otherwise a newly created file might use
 * the same inode number (not actually the same poपूर्णांकer
 * though), and then we'd have two inodes sharing the
 * same inode number and space on the harddisk.
 */
व्योम ufs_मुक्त_inode (काष्ठा inode * inode)
अणु
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cg_निजी_info * ucpi;
	काष्ठा ufs_cylinder_group * ucg;
	पूर्णांक is_directory;
	अचिन्हित ino, cg, bit;
	
	UFSD("ENTER, ino %lu\n", inode->i_ino);

	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	
	ino = inode->i_ino;

	mutex_lock(&UFS_SB(sb)->s_lock);

	अगर (!((ino > 1) && (ino < (uspi->s_ncg * uspi->s_ipg )))) अणु
		ufs_warning(sb, "ufs_free_inode", "reserved inode or nonexistent inode %u\n", ino);
		mutex_unlock(&UFS_SB(sb)->s_lock);
		वापस;
	पूर्ण
	
	cg = ufs_inotocg (ino);
	bit = ufs_inotocgoff (ino);
	ucpi = ufs_load_cylinder (sb, cg);
	अगर (!ucpi) अणु
		mutex_unlock(&UFS_SB(sb)->s_lock);
		वापस;
	पूर्ण
	ucg = ubh_get_ucg(UCPI_UBH(ucpi));
	अगर (!ufs_cg_chkmagic(sb, ucg))
		ufs_panic (sb, "ufs_free_fragments", "internal error, bad cg magic number");

	ucg->cg_समय = ufs_get_seconds(sb);

	is_directory = S_ISसूची(inode->i_mode);

	अगर (ubh_isclr (UCPI_UBH(ucpi), ucpi->c_iuseकरोff, bit))
		ufs_error(sb, "ufs_free_inode", "bit already cleared for inode %u", ino);
	अन्यथा अणु
		ubh_clrbit (UCPI_UBH(ucpi), ucpi->c_iuseकरोff, bit);
		अगर (ino < ucpi->c_irotor)
			ucpi->c_irotor = ino;
		fs32_add(sb, &ucg->cg_cs.cs_nअगरree, 1);
		uspi->cs_total.cs_nअगरree++;
		fs32_add(sb, &UFS_SB(sb)->fs_cs(cg).cs_nअगरree, 1);

		अगर (is_directory) अणु
			fs32_sub(sb, &ucg->cg_cs.cs_ndir, 1);
			uspi->cs_total.cs_ndir--;
			fs32_sub(sb, &UFS_SB(sb)->fs_cs(cg).cs_ndir, 1);
		पूर्ण
	पूर्ण

	ubh_mark_buffer_dirty (USPI_UBH(uspi));
	ubh_mark_buffer_dirty (UCPI_UBH(ucpi));
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		ubh_sync_block(UCPI_UBH(ucpi));
	
	ufs_mark_sb_dirty(sb);
	mutex_unlock(&UFS_SB(sb)->s_lock);
	UFSD("EXIT\n");
पूर्ण

/*
 * Nullअगरy new chunk of inodes,
 * BSD people also set ui_gen field of inode
 * during nullअगरication, but we not care about
 * that because of linux ufs करो not support NFS
 */
अटल व्योम ufs2_init_inodes_chunk(काष्ठा super_block *sb,
				   काष्ठा ufs_cg_निजी_info *ucpi,
				   काष्ठा ufs_cylinder_group *ucg)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	sector_t beg = uspi->s_sbbase +
		ufs_inotofsba(ucpi->c_cgx * uspi->s_ipg +
			      fs32_to_cpu(sb, ucg->cg_u.cg_u2.cg_initediblk));
	sector_t end = beg + uspi->s_fpb;

	UFSD("ENTER cgno %d\n", ucpi->c_cgx);

	क्रम (; beg < end; ++beg) अणु
		bh = sb_getblk(sb, beg);
		lock_buffer(bh);
		स_रखो(bh->b_data, 0, sb->s_blocksize);
		set_buffer_uptodate(bh);
		mark_buffer_dirty(bh);
		unlock_buffer(bh);
		अगर (sb->s_flags & SB_SYNCHRONOUS)
			sync_dirty_buffer(bh);
		brअन्यथा(bh);
	पूर्ण

	fs32_add(sb, &ucg->cg_u.cg_u2.cg_initediblk, uspi->s_inopb);
	ubh_mark_buffer_dirty(UCPI_UBH(ucpi));
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		ubh_sync_block(UCPI_UBH(ucpi));

	UFSD("EXIT\n");
पूर्ण

/*
 * There are two policies क्रम allocating an inode.  If the new inode is
 * a directory, then a क्रमward search is made क्रम a block group with both
 * मुक्त space and a low directory-to-inode ratio; अगर that fails, then of
 * the groups with above-average मुक्त space, that group with the fewest
 * directories alपढ़ोy is chosen.
 *
 * For other inodes, search क्रमward from the parent directory's block
 * group to find a मुक्त inode.
 */
काष्ठा inode *ufs_new_inode(काष्ठा inode *dir, umode_t mode)
अणु
	काष्ठा super_block * sb;
	काष्ठा ufs_sb_info * sbi;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cg_निजी_info * ucpi;
	काष्ठा ufs_cylinder_group * ucg;
	काष्ठा inode * inode;
	काष्ठा बारpec64 ts;
	अचिन्हित cg, bit, i, j, start;
	काष्ठा ufs_inode_info *ufsi;
	पूर्णांक err = -ENOSPC;

	UFSD("ENTER\n");
	
	/* Cannot create files in a deleted directory */
	अगर (!dir || !dir->i_nlink)
		वापस ERR_PTR(-EPERM);
	sb = dir->i_sb;
	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	ufsi = UFS_I(inode);
	sbi = UFS_SB(sb);
	uspi = sbi->s_uspi;

	mutex_lock(&sbi->s_lock);

	/*
	 * Try to place the inode in its parent directory
	 */
	i = ufs_inotocg(dir->i_ino);
	अगर (sbi->fs_cs(i).cs_nअगरree) अणु
		cg = i;
		जाओ cg_found;
	पूर्ण

	/*
	 * Use a quadratic hash to find a group with a मुक्त inode
	 */
	क्रम ( j = 1; j < uspi->s_ncg; j <<= 1 ) अणु
		i += j;
		अगर (i >= uspi->s_ncg)
			i -= uspi->s_ncg;
		अगर (sbi->fs_cs(i).cs_nअगरree) अणु
			cg = i;
			जाओ cg_found;
		पूर्ण
	पूर्ण

	/*
	 * That failed: try linear search क्रम a मुक्त inode
	 */
	i = ufs_inotocg(dir->i_ino) + 1;
	क्रम (j = 2; j < uspi->s_ncg; j++) अणु
		i++;
		अगर (i >= uspi->s_ncg)
			i = 0;
		अगर (sbi->fs_cs(i).cs_nअगरree) अणु
			cg = i;
			जाओ cg_found;
		पूर्ण
	पूर्ण

	जाओ failed;

cg_found:
	ucpi = ufs_load_cylinder (sb, cg);
	अगर (!ucpi) अणु
		err = -EIO;
		जाओ failed;
	पूर्ण
	ucg = ubh_get_ucg(UCPI_UBH(ucpi));
	अगर (!ufs_cg_chkmagic(sb, ucg)) 
		ufs_panic (sb, "ufs_new_inode", "internal error, bad cg magic number");

	start = ucpi->c_irotor;
	bit = ubh_find_next_zero_bit (UCPI_UBH(ucpi), ucpi->c_iuseकरोff, uspi->s_ipg, start);
	अगर (!(bit < uspi->s_ipg)) अणु
		bit = ubh_find_first_zero_bit (UCPI_UBH(ucpi), ucpi->c_iuseकरोff, start);
		अगर (!(bit < start)) अणु
			ufs_error (sb, "ufs_new_inode",
			    "cylinder group %u corrupted - error in inode bitmap\n", cg);
			err = -EIO;
			जाओ failed;
		पूर्ण
	पूर्ण
	UFSD("start = %u, bit = %u, ipg = %u\n", start, bit, uspi->s_ipg);
	अगर (ubh_isclr (UCPI_UBH(ucpi), ucpi->c_iuseकरोff, bit))
		ubh_setbit (UCPI_UBH(ucpi), ucpi->c_iuseकरोff, bit);
	अन्यथा अणु
		ufs_panic (sb, "ufs_new_inode", "internal error");
		err = -EIO;
		जाओ failed;
	पूर्ण

	अगर (uspi->fs_magic == UFS2_MAGIC) अणु
		u32 initediblk = fs32_to_cpu(sb, ucg->cg_u.cg_u2.cg_initediblk);

		अगर (bit + uspi->s_inopb > initediblk &&
		    initediblk < fs32_to_cpu(sb, ucg->cg_u.cg_u2.cg_niblk))
			ufs2_init_inodes_chunk(sb, ucpi, ucg);
	पूर्ण

	fs32_sub(sb, &ucg->cg_cs.cs_nअगरree, 1);
	uspi->cs_total.cs_nअगरree--;
	fs32_sub(sb, &sbi->fs_cs(cg).cs_nअगरree, 1);
	
	अगर (S_ISसूची(mode)) अणु
		fs32_add(sb, &ucg->cg_cs.cs_ndir, 1);
		uspi->cs_total.cs_ndir++;
		fs32_add(sb, &sbi->fs_cs(cg).cs_ndir, 1);
	पूर्ण
	ubh_mark_buffer_dirty (USPI_UBH(uspi));
	ubh_mark_buffer_dirty (UCPI_UBH(ucpi));
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		ubh_sync_block(UCPI_UBH(ucpi));
	ufs_mark_sb_dirty(sb);

	inode->i_ino = cg * uspi->s_ipg + bit;
	inode_init_owner(&init_user_ns, inode, dir, mode);
	inode->i_blocks = 0;
	inode->i_generation = 0;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	ufsi->i_flags = UFS_I(dir)->i_flags;
	ufsi->i_lastfrag = 0;
	ufsi->i_shaकरोw = 0;
	ufsi->i_osync = 0;
	ufsi->i_oeftflag = 0;
	ufsi->i_dir_start_lookup = 0;
	स_रखो(&ufsi->i_u1, 0, माप(ufsi->i_u1));
	अगर (insert_inode_locked(inode) < 0) अणु
		err = -EIO;
		जाओ failed;
	पूर्ण
	mark_inode_dirty(inode);

	अगर (uspi->fs_magic == UFS2_MAGIC) अणु
		काष्ठा buffer_head *bh;
		काष्ठा ufs2_inode *ufs2_inode;

		/*
		 * setup birth date, we करो it here because of there is no sense
		 * to hold it in काष्ठा ufs_inode_info, and lose 64 bit
		 */
		bh = sb_bपढ़ो(sb, uspi->s_sbbase + ufs_inotofsba(inode->i_ino));
		अगर (!bh) अणु
			ufs_warning(sb, "ufs_read_inode",
				    "unable to read inode %lu\n",
				    inode->i_ino);
			err = -EIO;
			जाओ fail_हटाओ_inode;
		पूर्ण
		lock_buffer(bh);
		ufs2_inode = (काष्ठा ufs2_inode *)bh->b_data;
		ufs2_inode += ufs_inotofsbo(inode->i_ino);
		kसमय_get_real_ts64(&ts);
		ufs2_inode->ui_birthसमय = cpu_to_fs64(sb, ts.tv_sec);
		ufs2_inode->ui_birthnsec = cpu_to_fs32(sb, ts.tv_nsec);
		mark_buffer_dirty(bh);
		unlock_buffer(bh);
		अगर (sb->s_flags & SB_SYNCHRONOUS)
			sync_dirty_buffer(bh);
		brअन्यथा(bh);
	पूर्ण
	mutex_unlock(&sbi->s_lock);

	UFSD("allocating inode %lu\n", inode->i_ino);
	UFSD("EXIT\n");
	वापस inode;

fail_हटाओ_inode:
	mutex_unlock(&sbi->s_lock);
	clear_nlink(inode);
	discard_new_inode(inode);
	UFSD("EXIT (FAILED): err %d\n", err);
	वापस ERR_PTR(err);
failed:
	mutex_unlock(&sbi->s_lock);
	make_bad_inode(inode);
	iput (inode);
	UFSD("EXIT (FAILED): err %d\n", err);
	वापस ERR_PTR(err);
पूर्ण
