<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/ufs/super.c
 *
 * Copyright (C) 1998
 * Daniel Pirkl <daniel.pirkl@email.cz>
 * Charles University, Faculty of Mathematics and Physics
 */

/* Derived from
 *
 *  linux/fs/ext2/super.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */
 
/*
 * Inspired by
 *
 *  linux/fs/ufs/super.c
 *
 * Copyright (C) 1996
 * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)
 * Laboratory क्रम Computer Science Research Computing Facility
 * Rutgers, The State University of New Jersey
 *
 * Copyright (C) 1996  Eddie C. Dost  (ecd@skynet.be)
 *
 * Kernel module support added on 96/04/26 by
 * Stefan Reinauer <stepan@home.culture.mipt.ru>
 *
 * Module usage counts added on 96/04/29 by
 * Gertjan van Wingerde <gwingerde@gmail.com>
 *
 * Clean swab support on 19970406 by
 * Francois-Rene Rideau <fare@tunes.org>
 *
 * 4.4BSD (FreeBSD) support added on February 1st 1998 by
 * Niels Kristian Bech Jensen <nkbj@image.dk> partially based
 * on code by Martin von Loewis <martin@mira.isdn.cs.tu-berlin.de>.
 *
 * NeXTstep support added on February 5th 1998 by
 * Niels Kristian Bech Jensen <nkbj@image.dk>.
 *
 * ग_लिखो support Daniel Pirkl <daniel.pirkl@email.cz> 1998
 * 
 * HP/UX hfs fileप्रणाली support added by
 * Martin K. Petersen <mkp@mkp.net>, August 1999
 *
 * UFS2 (of FreeBSD 5.x) support added by
 * Niraj Kumar <niraj17@iitbombay.org>, Jan 2004
 *
 * UFS2 ग_लिखो support added by
 * Evgeniy Dushistov <dushistov@mail.ru>, 2007
 */

#समावेश <linux/exportfs.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>

#समावेश <मानकतर्क.स>

#समावेश <linux/uaccess.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/init.h>
#समावेश <linux/parser.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/vfs.h>
#समावेश <linux/log2.h>
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/iversion.h>

#समावेश "ufs_fs.h"
#समावेश "ufs.h"
#समावेश "swab.h"
#समावेश "util.h"

अटल काष्ठा inode *ufs_nfs_get_inode(काष्ठा super_block *sb, u64 ino, u32 generation)
अणु
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	काष्ठा inode *inode;

	अगर (ino < UFS_ROOTINO || ino > (u64)uspi->s_ncg * uspi->s_ipg)
		वापस ERR_PTR(-ESTALE);

	inode = ufs_iget(sb, ino);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (generation && inode->i_generation != generation) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस inode;
पूर्ण

अटल काष्ठा dentry *ufs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
				       पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type, ufs_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *ufs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
				       पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type, ufs_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *ufs_get_parent(काष्ठा dentry *child)
अणु
	ino_t ino;

	ino = ufs_inode_by_name(d_inode(child), &करोtकरोt_name);
	अगर (!ino)
		वापस ERR_PTR(-ENOENT);
	वापस d_obtain_alias(ufs_iget(child->d_sb, ino));
पूर्ण

अटल स्थिर काष्ठा export_operations ufs_export_ops = अणु
	.fh_to_dentry	= ufs_fh_to_dentry,
	.fh_to_parent	= ufs_fh_to_parent,
	.get_parent	= ufs_get_parent,
पूर्ण;

#अगर_घोषित CONFIG_UFS_DEBUG
/*
 * Prपूर्णांक contents of ufs_super_block, useful क्रम debugging
 */
अटल व्योम ufs_prपूर्णांक_super_stuff(काष्ठा super_block *sb,
				  काष्ठा ufs_super_block_first *usb1,
				  काष्ठा ufs_super_block_second *usb2,
				  काष्ठा ufs_super_block_third *usb3)
अणु
	u32 magic = fs32_to_cpu(sb, usb3->fs_magic);

	pr_debug("ufs_print_super_stuff\n");
	pr_debug("  magic:     0x%x\n", magic);
	अगर (fs32_to_cpu(sb, usb3->fs_magic) == UFS2_MAGIC) अणु
		pr_debug("  fs_size:   %llu\n", (अचिन्हित दीर्घ दीर्घ)
			 fs64_to_cpu(sb, usb3->fs_un1.fs_u2.fs_size));
		pr_debug("  fs_dsize:  %llu\n", (अचिन्हित दीर्घ दीर्घ)
			 fs64_to_cpu(sb, usb3->fs_un1.fs_u2.fs_dsize));
		pr_debug("  bsize:         %u\n",
			 fs32_to_cpu(sb, usb1->fs_bsize));
		pr_debug("  fsize:         %u\n",
			 fs32_to_cpu(sb, usb1->fs_fsize));
		pr_debug("  fs_volname:  %s\n", usb2->fs_un.fs_u2.fs_volname);
		pr_debug("  fs_sblockloc: %llu\n", (अचिन्हित दीर्घ दीर्घ)
			 fs64_to_cpu(sb, usb2->fs_un.fs_u2.fs_sblockloc));
		pr_debug("  cs_ndir(No of dirs):  %llu\n", (अचिन्हित दीर्घ दीर्घ)
			 fs64_to_cpu(sb, usb2->fs_un.fs_u2.cs_ndir));
		pr_debug("  cs_nbfree(No of free blocks):  %llu\n",
			 (अचिन्हित दीर्घ दीर्घ)
			 fs64_to_cpu(sb, usb2->fs_un.fs_u2.cs_nbमुक्त));
		pr_info("  cs_nifree(Num of free inodes): %llu\n",
			(अचिन्हित दीर्घ दीर्घ)
			fs64_to_cpu(sb, usb3->fs_un1.fs_u2.cs_nअगरree));
		pr_info("  cs_nffree(Num of free frags): %llu\n",
			(अचिन्हित दीर्घ दीर्घ)
			fs64_to_cpu(sb, usb3->fs_un1.fs_u2.cs_nfमुक्त));
		pr_info("  fs_maxsymlinklen: %u\n",
			fs32_to_cpu(sb, usb3->fs_un2.fs_44.fs_maxsymlinklen));
	पूर्ण अन्यथा अणु
		pr_debug(" sblkno:      %u\n", fs32_to_cpu(sb, usb1->fs_sblkno));
		pr_debug(" cblkno:      %u\n", fs32_to_cpu(sb, usb1->fs_cblkno));
		pr_debug(" iblkno:      %u\n", fs32_to_cpu(sb, usb1->fs_iblkno));
		pr_debug(" dblkno:      %u\n", fs32_to_cpu(sb, usb1->fs_dblkno));
		pr_debug(" cgoffset:    %u\n",
			 fs32_to_cpu(sb, usb1->fs_cgoffset));
		pr_debug(" ~cgmask:     0x%x\n",
			 ~fs32_to_cpu(sb, usb1->fs_cgmask));
		pr_debug(" size:        %u\n", fs32_to_cpu(sb, usb1->fs_size));
		pr_debug(" dsize:       %u\n", fs32_to_cpu(sb, usb1->fs_dsize));
		pr_debug(" ncg:         %u\n", fs32_to_cpu(sb, usb1->fs_ncg));
		pr_debug(" bsize:       %u\n", fs32_to_cpu(sb, usb1->fs_bsize));
		pr_debug(" fsize:       %u\n", fs32_to_cpu(sb, usb1->fs_fsize));
		pr_debug(" frag:        %u\n", fs32_to_cpu(sb, usb1->fs_frag));
		pr_debug(" fragshift:   %u\n",
			 fs32_to_cpu(sb, usb1->fs_fragshअगरt));
		pr_debug(" ~fmask:      %u\n", ~fs32_to_cpu(sb, usb1->fs_fmask));
		pr_debug(" fshift:      %u\n", fs32_to_cpu(sb, usb1->fs_fshअगरt));
		pr_debug(" sbsize:      %u\n", fs32_to_cpu(sb, usb1->fs_sbsize));
		pr_debug(" spc:         %u\n", fs32_to_cpu(sb, usb1->fs_spc));
		pr_debug(" cpg:         %u\n", fs32_to_cpu(sb, usb1->fs_cpg));
		pr_debug(" ipg:         %u\n", fs32_to_cpu(sb, usb1->fs_ipg));
		pr_debug(" fpg:         %u\n", fs32_to_cpu(sb, usb1->fs_fpg));
		pr_debug(" csaddr:      %u\n", fs32_to_cpu(sb, usb1->fs_csaddr));
		pr_debug(" cssize:      %u\n", fs32_to_cpu(sb, usb1->fs_cssize));
		pr_debug(" cgsize:      %u\n", fs32_to_cpu(sb, usb1->fs_cgsize));
		pr_debug(" fstodb:      %u\n",
			 fs32_to_cpu(sb, usb1->fs_fsbtodb));
		pr_debug(" nrpos:       %u\n", fs32_to_cpu(sb, usb3->fs_nrpos));
		pr_debug(" ndir         %u\n",
			 fs32_to_cpu(sb, usb1->fs_cstotal.cs_ndir));
		pr_debug(" nifree       %u\n",
			 fs32_to_cpu(sb, usb1->fs_cstotal.cs_nअगरree));
		pr_debug(" nbfree       %u\n",
			 fs32_to_cpu(sb, usb1->fs_cstotal.cs_nbमुक्त));
		pr_debug(" nffree       %u\n",
			 fs32_to_cpu(sb, usb1->fs_cstotal.cs_nfमुक्त));
	पूर्ण
	pr_debug("\n");
पूर्ण

/*
 * Prपूर्णांक contents of ufs_cylinder_group, useful क्रम debugging
 */
अटल व्योम ufs_prपूर्णांक_cylinder_stuff(काष्ठा super_block *sb,
				     काष्ठा ufs_cylinder_group *cg)
अणु
	pr_debug("\nufs_print_cylinder_stuff\n");
	pr_debug("size of ucg: %zu\n", माप(काष्ठा ufs_cylinder_group));
	pr_debug("  magic:        %x\n", fs32_to_cpu(sb, cg->cg_magic));
	pr_debug("  time:         %u\n", fs32_to_cpu(sb, cg->cg_समय));
	pr_debug("  cgx:          %u\n", fs32_to_cpu(sb, cg->cg_cgx));
	pr_debug("  ncyl:         %u\n", fs16_to_cpu(sb, cg->cg_ncyl));
	pr_debug("  niblk:        %u\n", fs16_to_cpu(sb, cg->cg_niblk));
	pr_debug("  ndblk:        %u\n", fs32_to_cpu(sb, cg->cg_ndblk));
	pr_debug("  cs_ndir:      %u\n", fs32_to_cpu(sb, cg->cg_cs.cs_ndir));
	pr_debug("  cs_nbfree:    %u\n", fs32_to_cpu(sb, cg->cg_cs.cs_nbमुक्त));
	pr_debug("  cs_nifree:    %u\n", fs32_to_cpu(sb, cg->cg_cs.cs_nअगरree));
	pr_debug("  cs_nffree:    %u\n", fs32_to_cpu(sb, cg->cg_cs.cs_nfमुक्त));
	pr_debug("  rotor:        %u\n", fs32_to_cpu(sb, cg->cg_rotor));
	pr_debug("  frotor:       %u\n", fs32_to_cpu(sb, cg->cg_frotor));
	pr_debug("  irotor:       %u\n", fs32_to_cpu(sb, cg->cg_irotor));
	pr_debug("  frsum:        %u, %u, %u, %u, %u, %u, %u, %u\n",
	    fs32_to_cpu(sb, cg->cg_frsum[0]), fs32_to_cpu(sb, cg->cg_frsum[1]),
	    fs32_to_cpu(sb, cg->cg_frsum[2]), fs32_to_cpu(sb, cg->cg_frsum[3]),
	    fs32_to_cpu(sb, cg->cg_frsum[4]), fs32_to_cpu(sb, cg->cg_frsum[5]),
	    fs32_to_cpu(sb, cg->cg_frsum[6]), fs32_to_cpu(sb, cg->cg_frsum[7]));
	pr_debug("  btotoff:      %u\n", fs32_to_cpu(sb, cg->cg_btotoff));
	pr_debug("  boff:         %u\n", fs32_to_cpu(sb, cg->cg_boff));
	pr_debug("  iuseoff:      %u\n", fs32_to_cpu(sb, cg->cg_iuseकरोff));
	pr_debug("  freeoff:      %u\n", fs32_to_cpu(sb, cg->cg_मुक्तoff));
	pr_debug("  nextfreeoff:  %u\n", fs32_to_cpu(sb, cg->cg_nextमुक्तoff));
	pr_debug("  clustersumoff %u\n",
		 fs32_to_cpu(sb, cg->cg_u.cg_44.cg_clustersumoff));
	pr_debug("  clusteroff    %u\n",
		 fs32_to_cpu(sb, cg->cg_u.cg_44.cg_clusteroff));
	pr_debug("  nclusterblks  %u\n",
		 fs32_to_cpu(sb, cg->cg_u.cg_44.cg_nclusterblks));
	pr_debug("\n");
पूर्ण
#अन्यथा
#  define ufs_prपूर्णांक_super_stuff(sb, usb1, usb2, usb3) /**/
#  define ufs_prपूर्णांक_cylinder_stuff(sb, cg) /**/
#पूर्ण_अगर /* CONFIG_UFS_DEBUG */

अटल स्थिर काष्ठा super_operations ufs_super_ops;

व्योम ufs_error (काष्ठा super_block * sb, स्थिर अक्षर * function,
	स्थिर अक्षर * fmt, ...)
अणु
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_super_block_first * usb1;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	uspi = UFS_SB(sb)->s_uspi;
	usb1 = ubh_get_usb_first(uspi);
	
	अगर (!sb_rकरोnly(sb)) अणु
		usb1->fs_clean = UFS_FSBAD;
		ubh_mark_buffer_dirty(USPI_UBH(uspi));
		ufs_mark_sb_dirty(sb);
		sb->s_flags |= SB_RDONLY;
	पूर्ण
	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	चयन (UFS_SB(sb)->s_mount_opt & UFS_MOUNT_ONERROR) अणु
	हाल UFS_MOUNT_ONERROR_PANIC:
		panic("panic (device %s): %s: %pV\n",
		      sb->s_id, function, &vaf);

	हाल UFS_MOUNT_ONERROR_LOCK:
	हाल UFS_MOUNT_ONERROR_UMOUNT:
	हाल UFS_MOUNT_ONERROR_REPAIR:
		pr_crit("error (device %s): %s: %pV\n",
			sb->s_id, function, &vaf);
	पूर्ण
	बहु_पूर्ण(args);
पूर्ण

व्योम ufs_panic (काष्ठा super_block * sb, स्थिर अक्षर * function,
	स्थिर अक्षर * fmt, ...)
अणु
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_super_block_first * usb1;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	
	uspi = UFS_SB(sb)->s_uspi;
	usb1 = ubh_get_usb_first(uspi);
	
	अगर (!sb_rकरोnly(sb)) अणु
		usb1->fs_clean = UFS_FSBAD;
		ubh_mark_buffer_dirty(USPI_UBH(uspi));
		ufs_mark_sb_dirty(sb);
	पूर्ण
	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	sb->s_flags |= SB_RDONLY;
	pr_crit("panic (device %s): %s: %pV\n",
		sb->s_id, function, &vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम ufs_warning (काष्ठा super_block * sb, स्थिर अक्षर * function,
	स्थिर अक्षर * fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_warn("(device %s): %s: %pV\n",
		sb->s_id, function, &vaf);
	बहु_पूर्ण(args);
पूर्ण

क्रमागत अणु
       Opt_type_old = UFS_MOUNT_UFSTYPE_OLD,
       Opt_type_sunx86 = UFS_MOUNT_UFSTYPE_SUNx86,
       Opt_type_sun = UFS_MOUNT_UFSTYPE_SUN,
       Opt_type_sunos = UFS_MOUNT_UFSTYPE_SUNOS,
       Opt_type_44bsd = UFS_MOUNT_UFSTYPE_44BSD,
       Opt_type_ufs2 = UFS_MOUNT_UFSTYPE_UFS2,
       Opt_type_hp = UFS_MOUNT_UFSTYPE_HP,
       Opt_type_nextstepcd = UFS_MOUNT_UFSTYPE_NEXTSTEP_CD,
       Opt_type_nextstep = UFS_MOUNT_UFSTYPE_NEXTSTEP,
       Opt_type_खोलोstep = UFS_MOUNT_UFSTYPE_OPENSTEP,
       Opt_onerror_panic = UFS_MOUNT_ONERROR_PANIC,
       Opt_onerror_lock = UFS_MOUNT_ONERROR_LOCK,
       Opt_onerror_umount = UFS_MOUNT_ONERROR_UMOUNT,
       Opt_onerror_repair = UFS_MOUNT_ONERROR_REPAIR,
       Opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_type_old, "ufstype=old"पूर्ण,
	अणुOpt_type_sunx86, "ufstype=sunx86"पूर्ण,
	अणुOpt_type_sun, "ufstype=sun"पूर्ण,
	अणुOpt_type_sunos, "ufstype=sunos"पूर्ण,
	अणुOpt_type_44bsd, "ufstype=44bsd"पूर्ण,
	अणुOpt_type_ufs2, "ufstype=ufs2"पूर्ण,
	अणुOpt_type_ufs2, "ufstype=5xbsd"पूर्ण,
	अणुOpt_type_hp, "ufstype=hp"पूर्ण,
	अणुOpt_type_nextstepcd, "ufstype=nextstep-cd"पूर्ण,
	अणुOpt_type_nextstep, "ufstype=nextstep"पूर्ण,
	अणुOpt_type_खोलोstep, "ufstype=openstep"पूर्ण,
/*end of possible ufs types */
	अणुOpt_onerror_panic, "onerror=panic"पूर्ण,
	अणुOpt_onerror_lock, "onerror=lock"पूर्ण,
	अणुOpt_onerror_umount, "onerror=umount"पूर्ण,
	अणुOpt_onerror_repair, "onerror=repair"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक ufs_parse_options (अक्षर * options, अचिन्हित * mount_options)
अणु
	अक्षर * p;
	
	UFSD("ENTER\n");
	
	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		substring_t args[MAX_OPT_ARGS];
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_type_old:
			ufs_clear_opt (*mount_options, UFSTYPE);
			ufs_set_opt (*mount_options, UFSTYPE_OLD);
			अवरोध;
		हाल Opt_type_sunx86:
			ufs_clear_opt (*mount_options, UFSTYPE);
			ufs_set_opt (*mount_options, UFSTYPE_SUNx86);
			अवरोध;
		हाल Opt_type_sun:
			ufs_clear_opt (*mount_options, UFSTYPE);
			ufs_set_opt (*mount_options, UFSTYPE_SUN);
			अवरोध;
		हाल Opt_type_sunos:
			ufs_clear_opt(*mount_options, UFSTYPE);
			ufs_set_opt(*mount_options, UFSTYPE_SUNOS);
			अवरोध;
		हाल Opt_type_44bsd:
			ufs_clear_opt (*mount_options, UFSTYPE);
			ufs_set_opt (*mount_options, UFSTYPE_44BSD);
			अवरोध;
		हाल Opt_type_ufs2:
			ufs_clear_opt(*mount_options, UFSTYPE);
			ufs_set_opt(*mount_options, UFSTYPE_UFS2);
			अवरोध;
		हाल Opt_type_hp:
			ufs_clear_opt (*mount_options, UFSTYPE);
			ufs_set_opt (*mount_options, UFSTYPE_HP);
			अवरोध;
		हाल Opt_type_nextstepcd:
			ufs_clear_opt (*mount_options, UFSTYPE);
			ufs_set_opt (*mount_options, UFSTYPE_NEXTSTEP_CD);
			अवरोध;
		हाल Opt_type_nextstep:
			ufs_clear_opt (*mount_options, UFSTYPE);
			ufs_set_opt (*mount_options, UFSTYPE_NEXTSTEP);
			अवरोध;
		हाल Opt_type_खोलोstep:
			ufs_clear_opt (*mount_options, UFSTYPE);
			ufs_set_opt (*mount_options, UFSTYPE_OPENSTEP);
			अवरोध;
		हाल Opt_onerror_panic:
			ufs_clear_opt (*mount_options, ONERROR);
			ufs_set_opt (*mount_options, ONERROR_PANIC);
			अवरोध;
		हाल Opt_onerror_lock:
			ufs_clear_opt (*mount_options, ONERROR);
			ufs_set_opt (*mount_options, ONERROR_LOCK);
			अवरोध;
		हाल Opt_onerror_umount:
			ufs_clear_opt (*mount_options, ONERROR);
			ufs_set_opt (*mount_options, ONERROR_UMOUNT);
			अवरोध;
		हाल Opt_onerror_repair:
			pr_err("Unable to do repair on error, will lock lock instead\n");
			ufs_clear_opt (*mount_options, ONERROR);
			ufs_set_opt (*mount_options, ONERROR_REPAIR);
			अवरोध;
		शेष:
			pr_err("Invalid option: \"%s\" or missing value\n", p);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Dअगरferent types of UFS hold fs_cstotal in dअगरferent
 * places, and use dअगरferent data काष्ठाure क्रम it.
 * To make things simpler we just copy fs_cstotal to ufs_sb_निजी_info
 */
अटल व्योम ufs_setup_cstotal(काष्ठा super_block *sb)
अणु
	काष्ठा ufs_sb_info *sbi = UFS_SB(sb);
	काष्ठा ufs_sb_निजी_info *uspi = sbi->s_uspi;
	काष्ठा ufs_super_block_first *usb1;
	काष्ठा ufs_super_block_second *usb2;
	काष्ठा ufs_super_block_third *usb3;
	अचिन्हित mtype = sbi->s_mount_opt & UFS_MOUNT_UFSTYPE;

	UFSD("ENTER, mtype=%u\n", mtype);
	usb1 = ubh_get_usb_first(uspi);
	usb2 = ubh_get_usb_second(uspi);
	usb3 = ubh_get_usb_third(uspi);

	अगर ((mtype == UFS_MOUNT_UFSTYPE_44BSD &&
	     (usb2->fs_un.fs_u2.fs_maxbsize == usb1->fs_bsize)) ||
	    mtype == UFS_MOUNT_UFSTYPE_UFS2) अणु
		/*we have statistic in dअगरferent place, then usual*/
		uspi->cs_total.cs_ndir = fs64_to_cpu(sb, usb2->fs_un.fs_u2.cs_ndir);
		uspi->cs_total.cs_nbमुक्त = fs64_to_cpu(sb, usb2->fs_un.fs_u2.cs_nbमुक्त);
		uspi->cs_total.cs_nअगरree = fs64_to_cpu(sb, usb3->fs_un1.fs_u2.cs_nअगरree);
		uspi->cs_total.cs_nfमुक्त = fs64_to_cpu(sb, usb3->fs_un1.fs_u2.cs_nfमुक्त);
	पूर्ण अन्यथा अणु
		uspi->cs_total.cs_ndir = fs32_to_cpu(sb, usb1->fs_cstotal.cs_ndir);
		uspi->cs_total.cs_nbमुक्त = fs32_to_cpu(sb, usb1->fs_cstotal.cs_nbमुक्त);
		uspi->cs_total.cs_nअगरree = fs32_to_cpu(sb, usb1->fs_cstotal.cs_nअगरree);
		uspi->cs_total.cs_nfमुक्त = fs32_to_cpu(sb, usb1->fs_cstotal.cs_nfमुक्त);
	पूर्ण
	UFSD("EXIT\n");
पूर्ण

/*
 * Read on-disk काष्ठाures associated with cylinder groups
 */
अटल पूर्णांक ufs_पढ़ो_cylinder_काष्ठाures(काष्ठा super_block *sb)
अणु
	काष्ठा ufs_sb_info *sbi = UFS_SB(sb);
	काष्ठा ufs_sb_निजी_info *uspi = sbi->s_uspi;
	काष्ठा ufs_buffer_head * ubh;
	अचिन्हित अक्षर * base, * space;
	अचिन्हित size, blks, i;

	UFSD("ENTER\n");

	/*
	 * Read cs काष्ठाures from (usually) first data block
	 * on the device. 
	 */
	size = uspi->s_cssize;
	blks = (size + uspi->s_fsize - 1) >> uspi->s_fshअगरt;
	base = space = kदो_स्मृति(size, GFP_NOFS);
	अगर (!base)
		जाओ failed; 
	sbi->s_csp = (काष्ठा ufs_csum *)space;
	क्रम (i = 0; i < blks; i += uspi->s_fpb) अणु
		size = uspi->s_bsize;
		अगर (i + uspi->s_fpb > blks)
			size = (blks - i) * uspi->s_fsize;

		ubh = ubh_bपढ़ो(sb, uspi->s_csaddr + i, size);
		
		अगर (!ubh)
			जाओ failed;

		ubh_ubhcpymem (space, ubh, size);

		space += size;
		ubh_brअन्यथा (ubh);
		ubh = शून्य;
	पूर्ण

	/*
	 * Read cylinder group (we पढ़ो only first fragment from block
	 * at this समय) and prepare पूर्णांकernal data काष्ठाures क्रम cg caching.
	 */
	sbi->s_ucg = kदो_स्मृति_array(uspi->s_ncg, माप(काष्ठा buffer_head *),
				   GFP_NOFS);
	अगर (!sbi->s_ucg)
		जाओ failed;
	क्रम (i = 0; i < uspi->s_ncg; i++) 
		sbi->s_ucg[i] = शून्य;
	क्रम (i = 0; i < UFS_MAX_GROUP_LOADED; i++) अणु
		sbi->s_ucpi[i] = शून्य;
		sbi->s_cgno[i] = UFS_CGNO_EMPTY;
	पूर्ण
	क्रम (i = 0; i < uspi->s_ncg; i++) अणु
		UFSD("read cg %u\n", i);
		अगर (!(sbi->s_ucg[i] = sb_bपढ़ो(sb, ufs_cgcmin(i))))
			जाओ failed;
		अगर (!ufs_cg_chkmagic (sb, (काष्ठा ufs_cylinder_group *) sbi->s_ucg[i]->b_data))
			जाओ failed;

		ufs_prपूर्णांक_cylinder_stuff(sb, (काष्ठा ufs_cylinder_group *) sbi->s_ucg[i]->b_data);
	पूर्ण
	क्रम (i = 0; i < UFS_MAX_GROUP_LOADED; i++) अणु
		अगर (!(sbi->s_ucpi[i] = kदो_स्मृति (माप(काष्ठा ufs_cg_निजी_info), GFP_NOFS)))
			जाओ failed;
		sbi->s_cgno[i] = UFS_CGNO_EMPTY;
	पूर्ण
	sbi->s_cg_loaded = 0;
	UFSD("EXIT\n");
	वापस 1;

failed:
	kमुक्त (base);
	अगर (sbi->s_ucg) अणु
		क्रम (i = 0; i < uspi->s_ncg; i++)
			अगर (sbi->s_ucg[i])
				brअन्यथा (sbi->s_ucg[i]);
		kमुक्त (sbi->s_ucg);
		क्रम (i = 0; i < UFS_MAX_GROUP_LOADED; i++)
			kमुक्त (sbi->s_ucpi[i]);
	पूर्ण
	UFSD("EXIT (FAILED)\n");
	वापस 0;
पूर्ण

/*
 * Sync our पूर्णांकernal copy of fs_cstotal with disk
 */
अटल व्योम ufs_put_cstotal(काष्ठा super_block *sb)
अणु
	अचिन्हित mtype = UFS_SB(sb)->s_mount_opt & UFS_MOUNT_UFSTYPE;
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	काष्ठा ufs_super_block_first *usb1;
	काष्ठा ufs_super_block_second *usb2;
	काष्ठा ufs_super_block_third *usb3;

	UFSD("ENTER\n");
	usb1 = ubh_get_usb_first(uspi);
	usb2 = ubh_get_usb_second(uspi);
	usb3 = ubh_get_usb_third(uspi);

	अगर (mtype == UFS_MOUNT_UFSTYPE_UFS2) अणु
		/*we have statistic in dअगरferent place, then usual*/
		usb2->fs_un.fs_u2.cs_ndir =
			cpu_to_fs64(sb, uspi->cs_total.cs_ndir);
		usb2->fs_un.fs_u2.cs_nbमुक्त =
			cpu_to_fs64(sb, uspi->cs_total.cs_nbमुक्त);
		usb3->fs_un1.fs_u2.cs_nअगरree =
			cpu_to_fs64(sb, uspi->cs_total.cs_nअगरree);
		usb3->fs_un1.fs_u2.cs_nfमुक्त =
			cpu_to_fs64(sb, uspi->cs_total.cs_nfमुक्त);
		जाओ out;
	पूर्ण

	अगर (mtype == UFS_MOUNT_UFSTYPE_44BSD &&
	     (usb2->fs_un.fs_u2.fs_maxbsize == usb1->fs_bsize)) अणु
		/* store stats in both old and new places */
		usb2->fs_un.fs_u2.cs_ndir =
			cpu_to_fs64(sb, uspi->cs_total.cs_ndir);
		usb2->fs_un.fs_u2.cs_nbमुक्त =
			cpu_to_fs64(sb, uspi->cs_total.cs_nbमुक्त);
		usb3->fs_un1.fs_u2.cs_nअगरree =
			cpu_to_fs64(sb, uspi->cs_total.cs_nअगरree);
		usb3->fs_un1.fs_u2.cs_nfमुक्त =
			cpu_to_fs64(sb, uspi->cs_total.cs_nfमुक्त);
	पूर्ण
	usb1->fs_cstotal.cs_ndir = cpu_to_fs32(sb, uspi->cs_total.cs_ndir);
	usb1->fs_cstotal.cs_nbमुक्त = cpu_to_fs32(sb, uspi->cs_total.cs_nbमुक्त);
	usb1->fs_cstotal.cs_nअगरree = cpu_to_fs32(sb, uspi->cs_total.cs_nअगरree);
	usb1->fs_cstotal.cs_nfमुक्त = cpu_to_fs32(sb, uspi->cs_total.cs_nfमुक्त);
out:
	ubh_mark_buffer_dirty(USPI_UBH(uspi));
	ufs_prपूर्णांक_super_stuff(sb, usb1, usb2, usb3);
	UFSD("EXIT\n");
पूर्ण

/**
 * ufs_put_super_पूर्णांकernal() - put on-disk पूर्णांकrenal काष्ठाures
 * @sb: poपूर्णांकer to super_block काष्ठाure
 * Put on-disk काष्ठाures associated with cylinder groups
 * and ग_लिखो them back to disk, also update cs_total on disk
 */
अटल व्योम ufs_put_super_पूर्णांकernal(काष्ठा super_block *sb)
अणु
	काष्ठा ufs_sb_info *sbi = UFS_SB(sb);
	काष्ठा ufs_sb_निजी_info *uspi = sbi->s_uspi;
	काष्ठा ufs_buffer_head * ubh;
	अचिन्हित अक्षर * base, * space;
	अचिन्हित blks, size, i;

	
	UFSD("ENTER\n");

	ufs_put_cstotal(sb);
	size = uspi->s_cssize;
	blks = (size + uspi->s_fsize - 1) >> uspi->s_fshअगरt;
	base = space = (अक्षर*) sbi->s_csp;
	क्रम (i = 0; i < blks; i += uspi->s_fpb) अणु
		size = uspi->s_bsize;
		अगर (i + uspi->s_fpb > blks)
			size = (blks - i) * uspi->s_fsize;

		ubh = ubh_bपढ़ो(sb, uspi->s_csaddr + i, size);

		ubh_स_नकलubh (ubh, space, size);
		space += size;
		ubh_mark_buffer_uptodate (ubh, 1);
		ubh_mark_buffer_dirty (ubh);
		ubh_brअन्यथा (ubh);
	पूर्ण
	क्रम (i = 0; i < sbi->s_cg_loaded; i++) अणु
		ufs_put_cylinder (sb, i);
		kमुक्त (sbi->s_ucpi[i]);
	पूर्ण
	क्रम (; i < UFS_MAX_GROUP_LOADED; i++) 
		kमुक्त (sbi->s_ucpi[i]);
	क्रम (i = 0; i < uspi->s_ncg; i++) 
		brअन्यथा (sbi->s_ucg[i]);
	kमुक्त (sbi->s_ucg);
	kमुक्त (base);

	UFSD("EXIT\n");
पूर्ण

अटल पूर्णांक ufs_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_super_block_first * usb1;
	काष्ठा ufs_super_block_third * usb3;
	अचिन्हित flags;

	mutex_lock(&UFS_SB(sb)->s_lock);

	UFSD("ENTER\n");

	flags = UFS_SB(sb)->s_flags;
	uspi = UFS_SB(sb)->s_uspi;
	usb1 = ubh_get_usb_first(uspi);
	usb3 = ubh_get_usb_third(uspi);

	usb1->fs_समय = ufs_get_seconds(sb);
	अगर ((flags & UFS_ST_MASK) == UFS_ST_SUN  ||
	    (flags & UFS_ST_MASK) == UFS_ST_SUNOS ||
	    (flags & UFS_ST_MASK) == UFS_ST_SUNx86)
		ufs_set_fs_state(sb, usb1, usb3,
				UFS_FSOK - fs32_to_cpu(sb, usb1->fs_समय));
	ufs_put_cstotal(sb);

	UFSD("EXIT\n");
	mutex_unlock(&UFS_SB(sb)->s_lock);

	वापस 0;
पूर्ण

अटल व्योम delayed_sync_fs(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufs_sb_info *sbi;

	sbi = container_of(work, काष्ठा ufs_sb_info, sync_work.work);

	spin_lock(&sbi->work_lock);
	sbi->work_queued = 0;
	spin_unlock(&sbi->work_lock);

	ufs_sync_fs(sbi->sb, 1);
पूर्ण

व्योम ufs_mark_sb_dirty(काष्ठा super_block *sb)
अणु
	काष्ठा ufs_sb_info *sbi = UFS_SB(sb);
	अचिन्हित दीर्घ delay;

	spin_lock(&sbi->work_lock);
	अगर (!sbi->work_queued) अणु
		delay = msecs_to_jअगरfies(dirty_ग_लिखोback_पूर्णांकerval * 10);
		queue_delayed_work(प्रणाली_दीर्घ_wq, &sbi->sync_work, delay);
		sbi->work_queued = 1;
	पूर्ण
	spin_unlock(&sbi->work_lock);
पूर्ण

अटल व्योम ufs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा ufs_sb_info * sbi = UFS_SB(sb);

	UFSD("ENTER\n");

	अगर (!sb_rकरोnly(sb))
		ufs_put_super_पूर्णांकernal(sb);
	cancel_delayed_work_sync(&sbi->sync_work);

	ubh_brअन्यथा_uspi (sbi->s_uspi);
	kमुक्त (sbi->s_uspi);
	kमुक्त (sbi);
	sb->s_fs_info = शून्य;
	UFSD("EXIT\n");
	वापस;
पूर्ण

अटल u64 ufs_max_bytes(काष्ठा super_block *sb)
अणु
	काष्ठा ufs_sb_निजी_info *uspi = UFS_SB(sb)->s_uspi;
	पूर्णांक bits = uspi->s_apbshअगरt;
	u64 res;

	अगर (bits > 21)
		res = ~0ULL;
	अन्यथा
		res = UFS_NDADDR + (1LL << bits) + (1LL << (2*bits)) +
			(1LL << (3*bits));

	अगर (res >= (MAX_LFS_खाताSIZE >> uspi->s_bshअगरt))
		वापस MAX_LFS_खाताSIZE;
	वापस res << uspi->s_bshअगरt;
पूर्ण

अटल पूर्णांक ufs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा ufs_sb_info * sbi;
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_super_block_first * usb1;
	काष्ठा ufs_super_block_second * usb2;
	काष्ठा ufs_super_block_third * usb3;
	काष्ठा ufs_buffer_head * ubh;	
	काष्ठा inode *inode;
	अचिन्हित block_size, super_block_size;
	अचिन्हित flags;
	अचिन्हित super_block_offset;
	अचिन्हित maxsymlen;
	पूर्णांक ret = -EINVAL;

	uspi = शून्य;
	ubh = शून्य;
	flags = 0;
	
	UFSD("ENTER\n");

#अगर_अघोषित CONFIG_UFS_FS_WRITE
	अगर (!sb_rकरोnly(sb)) अणु
		pr_err("ufs was compiled with read-only support, can't be mounted as read-write\n");
		वापस -EROFS;
	पूर्ण
#पूर्ण_अगर
		
	sbi = kzalloc(माप(काष्ठा ufs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		जाओ failed_nomem;
	sb->s_fs_info = sbi;
	sbi->sb = sb;

	UFSD("flag %u\n", (पूर्णांक)(sb_rकरोnly(sb)));
	
	mutex_init(&sbi->s_lock);
	spin_lock_init(&sbi->work_lock);
	INIT_DELAYED_WORK(&sbi->sync_work, delayed_sync_fs);
	/*
	 * Set शेष mount options
	 * Parse mount options
	 */
	sbi->s_mount_opt = 0;
	ufs_set_opt (sbi->s_mount_opt, ONERROR_LOCK);
	अगर (!ufs_parse_options ((अक्षर *) data, &sbi->s_mount_opt)) अणु
		pr_err("wrong mount options\n");
		जाओ failed;
	पूर्ण
	अगर (!(sbi->s_mount_opt & UFS_MOUNT_UFSTYPE)) अणु
		अगर (!silent)
			pr_err("You didn't specify the type of your ufs filesystem\n\n"
			"mount -t ufs -o ufstype="
			"sun|sunx86|44bsd|ufs2|5xbsd|old|hp|nextstep|nextstep-cd|openstep ...\n\n"
			">>>WARNING<<< Wrong ufstype may corrupt your filesystem, "
			"default is ufstype=old\n");
		ufs_set_opt (sbi->s_mount_opt, UFSTYPE_OLD);
	पूर्ण

	uspi = kzalloc(माप(काष्ठा ufs_sb_निजी_info), GFP_KERNEL);
	sbi->s_uspi = uspi;
	अगर (!uspi)
		जाओ failed;
	uspi->s_dirblksize = UFS_SECTOR_SIZE;
	super_block_offset=UFS_SBLOCK;

	sb->s_maxbytes = MAX_LFS_खाताSIZE;

	sb->s_समय_gran = NSEC_PER_SEC;
	sb->s_समय_min = S32_MIN;
	sb->s_समय_max = S32_MAX;

	चयन (sbi->s_mount_opt & UFS_MOUNT_UFSTYPE) अणु
	हाल UFS_MOUNT_UFSTYPE_44BSD:
		UFSD("ufstype=44bsd\n");
		uspi->s_fsize = block_size = 512;
		uspi->s_fmask = ~(512 - 1);
		uspi->s_fshअगरt = 9;
		uspi->s_sbsize = super_block_size = 1536;
		uspi->s_sbbase = 0;
		flags |= UFS_DE_44BSD | UFS_UID_44BSD | UFS_ST_44BSD | UFS_CG_44BSD;
		अवरोध;
	हाल UFS_MOUNT_UFSTYPE_UFS2:
		UFSD("ufstype=ufs2\n");
		super_block_offset=SBLOCK_UFS2;
		uspi->s_fsize = block_size = 512;
		uspi->s_fmask = ~(512 - 1);
		uspi->s_fshअगरt = 9;
		uspi->s_sbsize = super_block_size = 1536;
		uspi->s_sbbase =  0;
		sb->s_समय_gran = 1;
		sb->s_समय_min = S64_MIN;
		sb->s_समय_max = S64_MAX;
		flags |= UFS_TYPE_UFS2 | UFS_DE_44BSD | UFS_UID_44BSD | UFS_ST_44BSD | UFS_CG_44BSD;
		अवरोध;
		
	हाल UFS_MOUNT_UFSTYPE_SUN:
		UFSD("ufstype=sun\n");
		uspi->s_fsize = block_size = 1024;
		uspi->s_fmask = ~(1024 - 1);
		uspi->s_fshअगरt = 10;
		uspi->s_sbsize = super_block_size = 2048;
		uspi->s_sbbase = 0;
		uspi->s_maxsymlinklen = 0; /* Not supported on disk */
		flags |= UFS_DE_OLD | UFS_UID_EFT | UFS_ST_SUN | UFS_CG_SUN;
		अवरोध;

	हाल UFS_MOUNT_UFSTYPE_SUNOS:
		UFSD("ufstype=sunos\n");
		uspi->s_fsize = block_size = 1024;
		uspi->s_fmask = ~(1024 - 1);
		uspi->s_fshअगरt = 10;
		uspi->s_sbsize = 2048;
		super_block_size = 2048;
		uspi->s_sbbase = 0;
		uspi->s_maxsymlinklen = 0; /* Not supported on disk */
		flags |= UFS_DE_OLD | UFS_UID_OLD | UFS_ST_SUNOS | UFS_CG_SUN;
		अवरोध;

	हाल UFS_MOUNT_UFSTYPE_SUNx86:
		UFSD("ufstype=sunx86\n");
		uspi->s_fsize = block_size = 1024;
		uspi->s_fmask = ~(1024 - 1);
		uspi->s_fshअगरt = 10;
		uspi->s_sbsize = super_block_size = 2048;
		uspi->s_sbbase = 0;
		uspi->s_maxsymlinklen = 0; /* Not supported on disk */
		flags |= UFS_DE_OLD | UFS_UID_EFT | UFS_ST_SUNx86 | UFS_CG_SUN;
		अवरोध;

	हाल UFS_MOUNT_UFSTYPE_OLD:
		UFSD("ufstype=old\n");
		uspi->s_fsize = block_size = 1024;
		uspi->s_fmask = ~(1024 - 1);
		uspi->s_fshअगरt = 10;
		uspi->s_sbsize = super_block_size = 2048;
		uspi->s_sbbase = 0;
		flags |= UFS_DE_OLD | UFS_UID_OLD | UFS_ST_OLD | UFS_CG_OLD;
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!silent)
				pr_info("ufstype=old is supported read-only\n");
			sb->s_flags |= SB_RDONLY;
		पूर्ण
		अवरोध;
	
	हाल UFS_MOUNT_UFSTYPE_NEXTSTEP:
		UFSD("ufstype=nextstep\n");
		uspi->s_fsize = block_size = 1024;
		uspi->s_fmask = ~(1024 - 1);
		uspi->s_fshअगरt = 10;
		uspi->s_sbsize = super_block_size = 2048;
		uspi->s_sbbase = 0;
		uspi->s_dirblksize = 1024;
		flags |= UFS_DE_OLD | UFS_UID_OLD | UFS_ST_OLD | UFS_CG_OLD;
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!silent)
				pr_info("ufstype=nextstep is supported read-only\n");
			sb->s_flags |= SB_RDONLY;
		पूर्ण
		अवरोध;
	
	हाल UFS_MOUNT_UFSTYPE_NEXTSTEP_CD:
		UFSD("ufstype=nextstep-cd\n");
		uspi->s_fsize = block_size = 2048;
		uspi->s_fmask = ~(2048 - 1);
		uspi->s_fshअगरt = 11;
		uspi->s_sbsize = super_block_size = 2048;
		uspi->s_sbbase = 0;
		uspi->s_dirblksize = 1024;
		flags |= UFS_DE_OLD | UFS_UID_OLD | UFS_ST_OLD | UFS_CG_OLD;
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!silent)
				pr_info("ufstype=nextstep-cd is supported read-only\n");
			sb->s_flags |= SB_RDONLY;
		पूर्ण
		अवरोध;
	
	हाल UFS_MOUNT_UFSTYPE_OPENSTEP:
		UFSD("ufstype=openstep\n");
		uspi->s_fsize = block_size = 1024;
		uspi->s_fmask = ~(1024 - 1);
		uspi->s_fshअगरt = 10;
		uspi->s_sbsize = super_block_size = 2048;
		uspi->s_sbbase = 0;
		uspi->s_dirblksize = 1024;
		flags |= UFS_DE_44BSD | UFS_UID_44BSD | UFS_ST_44BSD | UFS_CG_44BSD;
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!silent)
				pr_info("ufstype=openstep is supported read-only\n");
			sb->s_flags |= SB_RDONLY;
		पूर्ण
		अवरोध;
	
	हाल UFS_MOUNT_UFSTYPE_HP:
		UFSD("ufstype=hp\n");
		uspi->s_fsize = block_size = 1024;
		uspi->s_fmask = ~(1024 - 1);
		uspi->s_fshअगरt = 10;
		uspi->s_sbsize = super_block_size = 2048;
		uspi->s_sbbase = 0;
		flags |= UFS_DE_OLD | UFS_UID_OLD | UFS_ST_OLD | UFS_CG_OLD;
		अगर (!sb_rकरोnly(sb)) अणु
			अगर (!silent)
				pr_info("ufstype=hp is supported read-only\n");
			sb->s_flags |= SB_RDONLY;
 		पूर्ण
 		अवरोध;
	शेष:
		अगर (!silent)
			pr_err("unknown ufstype\n");
		जाओ failed;
	पूर्ण
	
again:	
	अगर (!sb_set_blocksize(sb, block_size)) अणु
		pr_err("failed to set blocksize\n");
		जाओ failed;
	पूर्ण

	/*
	 * पढ़ो ufs super block from device
	 */

	ubh = ubh_bपढ़ो_uspi(uspi, sb, uspi->s_sbbase + super_block_offset/block_size, super_block_size);
	
	अगर (!ubh) 
            जाओ failed;

	usb1 = ubh_get_usb_first(uspi);
	usb2 = ubh_get_usb_second(uspi);
	usb3 = ubh_get_usb_third(uspi);

	/* Sort out mod used on SunOS 4.1.3 क्रम fs_state */
	uspi->s_postblक्रमmat = fs32_to_cpu(sb, usb3->fs_postblक्रमmat);
	अगर (((flags & UFS_ST_MASK) == UFS_ST_SUNOS) &&
	    (uspi->s_postblक्रमmat != UFS_42POSTBLFMT)) अणु
		flags &= ~UFS_ST_MASK;
		flags |=  UFS_ST_SUN;
	पूर्ण

	अगर ((flags & UFS_ST_MASK) == UFS_ST_44BSD &&
	    uspi->s_postblक्रमmat == UFS_42POSTBLFMT) अणु
		अगर (!silent)
			pr_err("this is not a 44bsd filesystem");
		जाओ failed;
	पूर्ण

	/*
	 * Check ufs magic number
	 */
	sbi->s_bytesex = BYTESEX_LE;
	चयन ((uspi->fs_magic = fs32_to_cpu(sb, usb3->fs_magic))) अणु
		हाल UFS_MAGIC:
		हाल UFS_MAGIC_BW:
		हाल UFS2_MAGIC:
		हाल UFS_MAGIC_LFN:
	        हाल UFS_MAGIC_FEA:
	        हाल UFS_MAGIC_4GB:
			जाओ magic_found;
	पूर्ण
	sbi->s_bytesex = BYTESEX_BE;
	चयन ((uspi->fs_magic = fs32_to_cpu(sb, usb3->fs_magic))) अणु
		हाल UFS_MAGIC:
		हाल UFS_MAGIC_BW:
		हाल UFS2_MAGIC:
		हाल UFS_MAGIC_LFN:
	        हाल UFS_MAGIC_FEA:
	        हाल UFS_MAGIC_4GB:
			जाओ magic_found;
	पूर्ण

	अगर ((((sbi->s_mount_opt & UFS_MOUNT_UFSTYPE) == UFS_MOUNT_UFSTYPE_NEXTSTEP) 
	  || ((sbi->s_mount_opt & UFS_MOUNT_UFSTYPE) == UFS_MOUNT_UFSTYPE_NEXTSTEP_CD) 
	  || ((sbi->s_mount_opt & UFS_MOUNT_UFSTYPE) == UFS_MOUNT_UFSTYPE_OPENSTEP)) 
	  && uspi->s_sbbase < 256) अणु
		ubh_brअन्यथा_uspi(uspi);
		ubh = शून्य;
		uspi->s_sbbase += 8;
		जाओ again;
	पूर्ण
	अगर (!silent)
		pr_err("%s(): bad magic number\n", __func__);
	जाओ failed;

magic_found:
	/*
	 * Check block and fragment sizes
	 */
	uspi->s_bsize = fs32_to_cpu(sb, usb1->fs_bsize);
	uspi->s_fsize = fs32_to_cpu(sb, usb1->fs_fsize);
	uspi->s_sbsize = fs32_to_cpu(sb, usb1->fs_sbsize);
	uspi->s_fmask = fs32_to_cpu(sb, usb1->fs_fmask);
	uspi->s_fshअगरt = fs32_to_cpu(sb, usb1->fs_fshअगरt);

	अगर (!is_घातer_of_2(uspi->s_fsize)) अणु
		pr_err("%s(): fragment size %u is not a power of 2\n",
		       __func__, uspi->s_fsize);
		जाओ failed;
	पूर्ण
	अगर (uspi->s_fsize < 512) अणु
		pr_err("%s(): fragment size %u is too small\n",
		       __func__, uspi->s_fsize);
		जाओ failed;
	पूर्ण
	अगर (uspi->s_fsize > 4096) अणु
		pr_err("%s(): fragment size %u is too large\n",
		       __func__, uspi->s_fsize);
		जाओ failed;
	पूर्ण
	अगर (!is_घातer_of_2(uspi->s_bsize)) अणु
		pr_err("%s(): block size %u is not a power of 2\n",
		       __func__, uspi->s_bsize);
		जाओ failed;
	पूर्ण
	अगर (uspi->s_bsize < 4096) अणु
		pr_err("%s(): block size %u is too small\n",
		       __func__, uspi->s_bsize);
		जाओ failed;
	पूर्ण
	अगर (uspi->s_bsize / uspi->s_fsize > 8) अणु
		pr_err("%s(): too many fragments per block (%u)\n",
		       __func__, uspi->s_bsize / uspi->s_fsize);
		जाओ failed;
	पूर्ण
	अगर (uspi->s_fsize != block_size || uspi->s_sbsize != super_block_size) अणु
		ubh_brअन्यथा_uspi(uspi);
		ubh = शून्य;
		block_size = uspi->s_fsize;
		super_block_size = uspi->s_sbsize;
		UFSD("another value of block_size or super_block_size %u, %u\n", block_size, super_block_size);
		जाओ again;
	पूर्ण

	sbi->s_flags = flags;/*after that line some functions use s_flags*/
	ufs_prपूर्णांक_super_stuff(sb, usb1, usb2, usb3);

	/*
	 * Check, अगर file प्रणाली was correctly unmounted.
	 * If not, make it पढ़ो only.
	 */
	अगर (((flags & UFS_ST_MASK) == UFS_ST_44BSD) ||
	  ((flags & UFS_ST_MASK) == UFS_ST_OLD) ||
	  (((flags & UFS_ST_MASK) == UFS_ST_SUN ||
	    (flags & UFS_ST_MASK) == UFS_ST_SUNOS ||
	  (flags & UFS_ST_MASK) == UFS_ST_SUNx86) &&
	  (ufs_get_fs_state(sb, usb1, usb3) == (UFS_FSOK - fs32_to_cpu(sb, usb1->fs_समय))))) अणु
		चयन(usb1->fs_clean) अणु
		हाल UFS_FSCLEAN:
			UFSD("fs is clean\n");
			अवरोध;
		हाल UFS_FSSTABLE:
			UFSD("fs is stable\n");
			अवरोध;
		हाल UFS_FSLOG:
			UFSD("fs is logging fs\n");
			अवरोध;
		हाल UFS_FSOSF1:
			UFSD("fs is DEC OSF/1\n");
			अवरोध;
		हाल UFS_FSACTIVE:
			pr_err("%s(): fs is active\n", __func__);
			sb->s_flags |= SB_RDONLY;
			अवरोध;
		हाल UFS_FSBAD:
			pr_err("%s(): fs is bad\n", __func__);
			sb->s_flags |= SB_RDONLY;
			अवरोध;
		शेष:
			pr_err("%s(): can't grok fs_clean 0x%x\n",
			       __func__, usb1->fs_clean);
			sb->s_flags |= SB_RDONLY;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("%s(): fs needs fsck\n", __func__);
		sb->s_flags |= SB_RDONLY;
	पूर्ण

	/*
	 * Read ufs_super_block पूर्णांकo पूर्णांकernal data काष्ठाures
	 */
	sb->s_op = &ufs_super_ops;
	sb->s_export_op = &ufs_export_ops;

	sb->s_magic = fs32_to_cpu(sb, usb3->fs_magic);

	uspi->s_sblkno = fs32_to_cpu(sb, usb1->fs_sblkno);
	uspi->s_cblkno = fs32_to_cpu(sb, usb1->fs_cblkno);
	uspi->s_iblkno = fs32_to_cpu(sb, usb1->fs_iblkno);
	uspi->s_dblkno = fs32_to_cpu(sb, usb1->fs_dblkno);
	uspi->s_cgoffset = fs32_to_cpu(sb, usb1->fs_cgoffset);
	uspi->s_cgmask = fs32_to_cpu(sb, usb1->fs_cgmask);

	अगर ((flags & UFS_TYPE_MASK) == UFS_TYPE_UFS2) अणु
		uspi->s_size  = fs64_to_cpu(sb, usb3->fs_un1.fs_u2.fs_size);
		uspi->s_dsize = fs64_to_cpu(sb, usb3->fs_un1.fs_u2.fs_dsize);
	पूर्ण अन्यथा अणु
		uspi->s_size  =  fs32_to_cpu(sb, usb1->fs_size);
		uspi->s_dsize =  fs32_to_cpu(sb, usb1->fs_dsize);
	पूर्ण

	uspi->s_ncg = fs32_to_cpu(sb, usb1->fs_ncg);
	/* s_bsize alपढ़ोy set */
	/* s_fsize alपढ़ोy set */
	uspi->s_fpb = fs32_to_cpu(sb, usb1->fs_frag);
	uspi->s_minमुक्त = fs32_to_cpu(sb, usb1->fs_minमुक्त);
	uspi->s_bmask = fs32_to_cpu(sb, usb1->fs_bmask);
	uspi->s_fmask = fs32_to_cpu(sb, usb1->fs_fmask);
	uspi->s_bshअगरt = fs32_to_cpu(sb, usb1->fs_bshअगरt);
	uspi->s_fshअगरt = fs32_to_cpu(sb, usb1->fs_fshअगरt);
	UFSD("uspi->s_bshift = %d,uspi->s_fshift = %d", uspi->s_bshअगरt,
		uspi->s_fshअगरt);
	uspi->s_fpbshअगरt = fs32_to_cpu(sb, usb1->fs_fragshअगरt);
	uspi->s_fsbtodb = fs32_to_cpu(sb, usb1->fs_fsbtodb);
	/* s_sbsize alपढ़ोy set */
	uspi->s_csmask = fs32_to_cpu(sb, usb1->fs_csmask);
	uspi->s_csshअगरt = fs32_to_cpu(sb, usb1->fs_csshअगरt);
	uspi->s_nindir = fs32_to_cpu(sb, usb1->fs_nindir);
	uspi->s_inopb = fs32_to_cpu(sb, usb1->fs_inopb);
	uspi->s_nspf = fs32_to_cpu(sb, usb1->fs_nspf);
	uspi->s_npsect = ufs_get_fs_npsect(sb, usb1, usb3);
	uspi->s_पूर्णांकerleave = fs32_to_cpu(sb, usb1->fs_पूर्णांकerleave);
	uspi->s_trackskew = fs32_to_cpu(sb, usb1->fs_trackskew);

	अगर (uspi->fs_magic == UFS2_MAGIC)
		uspi->s_csaddr = fs64_to_cpu(sb, usb3->fs_un1.fs_u2.fs_csaddr);
	अन्यथा
		uspi->s_csaddr = fs32_to_cpu(sb, usb1->fs_csaddr);

	uspi->s_cssize = fs32_to_cpu(sb, usb1->fs_cssize);
	uspi->s_cgsize = fs32_to_cpu(sb, usb1->fs_cgsize);
	uspi->s_ntrak = fs32_to_cpu(sb, usb1->fs_ntrak);
	uspi->s_nsect = fs32_to_cpu(sb, usb1->fs_nsect);
	uspi->s_spc = fs32_to_cpu(sb, usb1->fs_spc);
	uspi->s_ipg = fs32_to_cpu(sb, usb1->fs_ipg);
	uspi->s_fpg = fs32_to_cpu(sb, usb1->fs_fpg);
	uspi->s_cpc = fs32_to_cpu(sb, usb2->fs_un.fs_u1.fs_cpc);
	uspi->s_contigsumsize = fs32_to_cpu(sb, usb3->fs_un2.fs_44.fs_contigsumsize);
	uspi->s_qbmask = ufs_get_fs_qbmask(sb, usb3);
	uspi->s_qfmask = ufs_get_fs_qfmask(sb, usb3);
	uspi->s_nrpos = fs32_to_cpu(sb, usb3->fs_nrpos);
	uspi->s_postbloff = fs32_to_cpu(sb, usb3->fs_postbloff);
	uspi->s_rotbloff = fs32_to_cpu(sb, usb3->fs_rotbloff);

	uspi->s_root_blocks = mul_u64_u32_भाग(uspi->s_dsize,
					      uspi->s_minमुक्त, 100);
	अगर (uspi->s_minमुक्त <= 5) अणु
		uspi->s_समय_प्रकारo_space = ~0ULL;
		uspi->s_space_to_समय = 0;
		usb1->fs_optim = cpu_to_fs32(sb, UFS_OPTSPACE);
	पूर्ण अन्यथा अणु
		uspi->s_समय_प्रकारo_space = (uspi->s_root_blocks / 2) + 1;
		uspi->s_space_to_समय = mul_u64_u32_भाग(uspi->s_dsize,
					      uspi->s_minमुक्त - 2, 100) - 1;
	पूर्ण

	/*
	 * Compute another frequently used values
	 */
	uspi->s_fpbmask = uspi->s_fpb - 1;
	अगर ((flags & UFS_TYPE_MASK) == UFS_TYPE_UFS2)
		uspi->s_apbshअगरt = uspi->s_bshअगरt - 3;
	अन्यथा
		uspi->s_apbshअगरt = uspi->s_bshअगरt - 2;

	uspi->s_2apbshअगरt = uspi->s_apbshअगरt * 2;
	uspi->s_3apbshअगरt = uspi->s_apbshअगरt * 3;
	uspi->s_apb = 1 << uspi->s_apbshअगरt;
	uspi->s_2apb = 1 << uspi->s_2apbshअगरt;
	uspi->s_3apb = 1 << uspi->s_3apbshअगरt;
	uspi->s_apbmask = uspi->s_apb - 1;
	uspi->s_nspfshअगरt = uspi->s_fshअगरt - UFS_SECTOR_BITS;
	uspi->s_nspb = uspi->s_nspf << uspi->s_fpbshअगरt;
	uspi->s_inopf = uspi->s_inopb >> uspi->s_fpbshअगरt;
	uspi->s_bpf = uspi->s_fsize << 3;
	uspi->s_bpfshअगरt = uspi->s_fshअगरt + 3;
	uspi->s_bpfmask = uspi->s_bpf - 1;
	अगर ((sbi->s_mount_opt & UFS_MOUNT_UFSTYPE) == UFS_MOUNT_UFSTYPE_44BSD ||
	    (sbi->s_mount_opt & UFS_MOUNT_UFSTYPE) == UFS_MOUNT_UFSTYPE_UFS2)
		uspi->s_maxsymlinklen =
		    fs32_to_cpu(sb, usb3->fs_un2.fs_44.fs_maxsymlinklen);

	अगर (uspi->fs_magic == UFS2_MAGIC)
		maxsymlen = 2 * 4 * (UFS_NDADDR + UFS_NINसूची);
	अन्यथा
		maxsymlen = 4 * (UFS_NDADDR + UFS_NINसूची);
	अगर (uspi->s_maxsymlinklen > maxsymlen) अणु
		ufs_warning(sb, __func__, "ufs_read_super: excessive maximum "
			    "fast symlink size (%u)\n", uspi->s_maxsymlinklen);
		uspi->s_maxsymlinklen = maxsymlen;
	पूर्ण
	sb->s_maxbytes = ufs_max_bytes(sb);
	sb->s_max_links = UFS_LINK_MAX;

	inode = ufs_iget(sb, UFS_ROOTINO);
	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		जाओ failed;
	पूर्ण
	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root) अणु
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	ufs_setup_cstotal(sb);
	/*
	 * Read cylinder group काष्ठाures
	 */
	अगर (!sb_rकरोnly(sb))
		अगर (!ufs_पढ़ो_cylinder_काष्ठाures(sb))
			जाओ failed;

	UFSD("EXIT\n");
	वापस 0;

failed:
	अगर (ubh)
		ubh_brअन्यथा_uspi (uspi);
	kमुक्त (uspi);
	kमुक्त(sbi);
	sb->s_fs_info = शून्य;
	UFSD("EXIT (FAILED)\n");
	वापस ret;

failed_nomem:
	UFSD("EXIT (NOMEM)\n");
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ufs_remount (काष्ठा super_block *sb, पूर्णांक *mount_flags, अक्षर *data)
अणु
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_super_block_first * usb1;
	काष्ठा ufs_super_block_third * usb3;
	अचिन्हित new_mount_opt, ufstype;
	अचिन्हित flags;

	sync_fileप्रणाली(sb);
	mutex_lock(&UFS_SB(sb)->s_lock);
	uspi = UFS_SB(sb)->s_uspi;
	flags = UFS_SB(sb)->s_flags;
	usb1 = ubh_get_usb_first(uspi);
	usb3 = ubh_get_usb_third(uspi);
	
	/*
	 * Allow the "check" option to be passed as a remount option.
	 * It is not possible to change ufstype option during remount
	 */
	ufstype = UFS_SB(sb)->s_mount_opt & UFS_MOUNT_UFSTYPE;
	new_mount_opt = 0;
	ufs_set_opt (new_mount_opt, ONERROR_LOCK);
	अगर (!ufs_parse_options (data, &new_mount_opt)) अणु
		mutex_unlock(&UFS_SB(sb)->s_lock);
		वापस -EINVAL;
	पूर्ण
	अगर (!(new_mount_opt & UFS_MOUNT_UFSTYPE)) अणु
		new_mount_opt |= ufstype;
	पूर्ण अन्यथा अगर ((new_mount_opt & UFS_MOUNT_UFSTYPE) != ufstype) अणु
		pr_err("ufstype can't be changed during remount\n");
		mutex_unlock(&UFS_SB(sb)->s_lock);
		वापस -EINVAL;
	पूर्ण

	अगर ((bool)(*mount_flags & SB_RDONLY) == sb_rकरोnly(sb)) अणु
		UFS_SB(sb)->s_mount_opt = new_mount_opt;
		mutex_unlock(&UFS_SB(sb)->s_lock);
		वापस 0;
	पूर्ण
	
	/*
	 * fs was mouted as rw, remounting ro
	 */
	अगर (*mount_flags & SB_RDONLY) अणु
		ufs_put_super_पूर्णांकernal(sb);
		usb1->fs_समय = ufs_get_seconds(sb);
		अगर ((flags & UFS_ST_MASK) == UFS_ST_SUN
		  || (flags & UFS_ST_MASK) == UFS_ST_SUNOS
		  || (flags & UFS_ST_MASK) == UFS_ST_SUNx86) 
			ufs_set_fs_state(sb, usb1, usb3,
				UFS_FSOK - fs32_to_cpu(sb, usb1->fs_समय));
		ubh_mark_buffer_dirty (USPI_UBH(uspi));
		sb->s_flags |= SB_RDONLY;
	पूर्ण अन्यथा अणु
	/*
	 * fs was mounted as ro, remounting rw
	 */
#अगर_अघोषित CONFIG_UFS_FS_WRITE
		pr_err("ufs was compiled with read-only support, can't be mounted as read-write\n");
		mutex_unlock(&UFS_SB(sb)->s_lock);
		वापस -EINVAL;
#अन्यथा
		अगर (ufstype != UFS_MOUNT_UFSTYPE_SUN && 
		    ufstype != UFS_MOUNT_UFSTYPE_SUNOS &&
		    ufstype != UFS_MOUNT_UFSTYPE_44BSD &&
		    ufstype != UFS_MOUNT_UFSTYPE_SUNx86 &&
		    ufstype != UFS_MOUNT_UFSTYPE_UFS2) अणु
			pr_err("this ufstype is read-only supported\n");
			mutex_unlock(&UFS_SB(sb)->s_lock);
			वापस -EINVAL;
		पूर्ण
		अगर (!ufs_पढ़ो_cylinder_काष्ठाures(sb)) अणु
			pr_err("failed during remounting\n");
			mutex_unlock(&UFS_SB(sb)->s_lock);
			वापस -EPERM;
		पूर्ण
		sb->s_flags &= ~SB_RDONLY;
#पूर्ण_अगर
	पूर्ण
	UFS_SB(sb)->s_mount_opt = new_mount_opt;
	mutex_unlock(&UFS_SB(sb)->s_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक ufs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा ufs_sb_info *sbi = UFS_SB(root->d_sb);
	अचिन्हित mval = sbi->s_mount_opt & UFS_MOUNT_UFSTYPE;
	स्थिर काष्ठा match_token *tp = tokens;

	जबतक (tp->token != Opt_onerror_panic && tp->token != mval)
		++tp;
	BUG_ON(tp->token == Opt_onerror_panic);
	seq_म_लिखो(seq, ",%s", tp->pattern);

	mval = sbi->s_mount_opt & UFS_MOUNT_ONERROR;
	जबतक (tp->token != Opt_err && tp->token != mval)
		++tp;
	BUG_ON(tp->token == Opt_err);
	seq_म_लिखो(seq, ",%s", tp->pattern);

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा ufs_sb_निजी_info *uspi= UFS_SB(sb)->s_uspi;
	अचिन्हित  flags = UFS_SB(sb)->s_flags;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	mutex_lock(&UFS_SB(sb)->s_lock);
	
	अगर ((flags & UFS_TYPE_MASK) == UFS_TYPE_UFS2)
		buf->f_type = UFS2_MAGIC;
	अन्यथा
		buf->f_type = UFS_MAGIC;

	buf->f_blocks = uspi->s_dsize;
	buf->f_bमुक्त = ufs_मुक्तfrags(uspi);
	buf->f_fमुक्त = uspi->cs_total.cs_nअगरree;
	buf->f_bsize = sb->s_blocksize;
	buf->f_bavail = (buf->f_bमुक्त > uspi->s_root_blocks)
		? (buf->f_bमुक्त - uspi->s_root_blocks) : 0;
	buf->f_files = uspi->s_ncg * uspi->s_ipg;
	buf->f_namelen = UFS_MAXNAMLEN;
	buf->f_fsid = u64_to_fsid(id);

	mutex_unlock(&UFS_SB(sb)->s_lock);

	वापस 0;
पूर्ण

अटल काष्ठा kmem_cache * ufs_inode_cachep;

अटल काष्ठा inode *ufs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा ufs_inode_info *ei;

	ei = kmem_cache_alloc(ufs_inode_cachep, GFP_NOFS);
	अगर (!ei)
		वापस शून्य;

	inode_set_iversion(&ei->vfs_inode, 1);
	seqlock_init(&ei->meta_lock);
	mutex_init(&ei->truncate_mutex);
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम ufs_मुक्त_in_core_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(ufs_inode_cachep, UFS_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा ufs_inode_info *ei = (काष्ठा ufs_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	ufs_inode_cachep = kmem_cache_create_usercopy("ufs_inode_cache",
				माप(काष्ठा ufs_inode_info), 0,
				(SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|
					SLAB_ACCOUNT),
				दुरत्व(काष्ठा ufs_inode_info, i_u1.i_symlink),
				माप_field(काष्ठा ufs_inode_info,
					i_u1.i_symlink),
				init_once);
	अगर (ufs_inode_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(ufs_inode_cachep);
पूर्ण

अटल स्थिर काष्ठा super_operations ufs_super_ops = अणु
	.alloc_inode	= ufs_alloc_inode,
	.मुक्त_inode	= ufs_मुक्त_in_core_inode,
	.ग_लिखो_inode	= ufs_ग_लिखो_inode,
	.evict_inode	= ufs_evict_inode,
	.put_super	= ufs_put_super,
	.sync_fs	= ufs_sync_fs,
	.statfs		= ufs_statfs,
	.remount_fs	= ufs_remount,
	.show_options   = ufs_show_options,
पूर्ण;

अटल काष्ठा dentry *ufs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, ufs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type ufs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "ufs",
	.mount		= ufs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("ufs");

अटल पूर्णांक __init init_ufs_fs(व्योम)
अणु
	पूर्णांक err = init_inodecache();
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_fileप्रणाली(&ufs_fs_type);
	अगर (err)
		जाओ out;
	वापस 0;
out:
	destroy_inodecache();
out1:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_ufs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&ufs_fs_type);
	destroy_inodecache();
पूर्ण

module_init(init_ufs_fs)
module_निकास(निकास_ufs_fs)
MODULE_LICENSE("GPL");
