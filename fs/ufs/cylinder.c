<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ufs/cylinder.c
 *
 * Copyright (C) 1998
 * Daniel Pirkl <daniel.pirkl@email.cz>
 * Charles University, Faculty of Mathematics and Physics
 *
 *  ext2 - inode (block) biपंचांगap caching inspired
 */

#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "ufs_fs.h"
#समावेश "ufs.h"
#समावेश "swab.h"
#समावेश "util.h"

/*
 * Read cylinder group पूर्णांकo cache. The memory space क्रम ufs_cg_निजी_info
 * काष्ठाure is alपढ़ोy allocated during ufs_पढ़ो_super.
 */
अटल व्योम ufs_पढ़ो_cylinder (काष्ठा super_block * sb,
	अचिन्हित cgno, अचिन्हित biपंचांगap_nr)
अणु
	काष्ठा ufs_sb_info * sbi = UFS_SB(sb);
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cg_निजी_info * ucpi;
	काष्ठा ufs_cylinder_group * ucg;
	अचिन्हित i, j;

	UFSD("ENTER, cgno %u, bitmap_nr %u\n", cgno, biपंचांगap_nr);
	uspi = sbi->s_uspi;
	ucpi = sbi->s_ucpi[biपंचांगap_nr];
	ucg = (काष्ठा ufs_cylinder_group *)sbi->s_ucg[cgno]->b_data;

	UCPI_UBH(ucpi)->fragment = ufs_cgcmin(cgno);
	UCPI_UBH(ucpi)->count = uspi->s_cgsize >> sb->s_blocksize_bits;
	/*
	 * We have alपढ़ोy the first fragment of cylinder group block in buffer
	 */
	UCPI_UBH(ucpi)->bh[0] = sbi->s_ucg[cgno];
	क्रम (i = 1; i < UCPI_UBH(ucpi)->count; i++)
		अगर (!(UCPI_UBH(ucpi)->bh[i] = sb_bपढ़ो(sb, UCPI_UBH(ucpi)->fragment + i)))
			जाओ failed;
	sbi->s_cgno[biपंचांगap_nr] = cgno;
			
	ucpi->c_cgx	= fs32_to_cpu(sb, ucg->cg_cgx);
	ucpi->c_ncyl	= fs16_to_cpu(sb, ucg->cg_ncyl);
	ucpi->c_niblk	= fs16_to_cpu(sb, ucg->cg_niblk);
	ucpi->c_ndblk	= fs32_to_cpu(sb, ucg->cg_ndblk);
	ucpi->c_rotor	= fs32_to_cpu(sb, ucg->cg_rotor);
	ucpi->c_frotor	= fs32_to_cpu(sb, ucg->cg_frotor);
	ucpi->c_irotor	= fs32_to_cpu(sb, ucg->cg_irotor);
	ucpi->c_btotoff	= fs32_to_cpu(sb, ucg->cg_btotoff);
	ucpi->c_boff	= fs32_to_cpu(sb, ucg->cg_boff);
	ucpi->c_iuseकरोff = fs32_to_cpu(sb, ucg->cg_iuseकरोff);
	ucpi->c_मुक्तoff	= fs32_to_cpu(sb, ucg->cg_मुक्तoff);
	ucpi->c_nextमुक्तoff = fs32_to_cpu(sb, ucg->cg_nextमुक्तoff);
	ucpi->c_clustersumoff = fs32_to_cpu(sb, ucg->cg_u.cg_44.cg_clustersumoff);
	ucpi->c_clusteroff = fs32_to_cpu(sb, ucg->cg_u.cg_44.cg_clusteroff);
	ucpi->c_nclusterblks = fs32_to_cpu(sb, ucg->cg_u.cg_44.cg_nclusterblks);
	UFSD("EXIT\n");
	वापस;	
	
failed:
	क्रम (j = 1; j < i; j++)
		brअन्यथा (sbi->s_ucg[j]);
	sbi->s_cgno[biपंचांगap_nr] = UFS_CGNO_EMPTY;
	ufs_error (sb, "ufs_read_cylinder", "can't read cylinder group block %u", cgno);
पूर्ण

/*
 * Remove cylinder group from cache, करोesn't release memory
 * allocated क्रम cylinder group (this is करोne at ufs_put_super only).
 */
व्योम ufs_put_cylinder (काष्ठा super_block * sb, अचिन्हित biपंचांगap_nr)
अणु
	काष्ठा ufs_sb_info * sbi = UFS_SB(sb);
	काष्ठा ufs_sb_निजी_info * uspi; 
	काष्ठा ufs_cg_निजी_info * ucpi;
	काष्ठा ufs_cylinder_group * ucg;
	अचिन्हित i;

	UFSD("ENTER, bitmap_nr %u\n", biपंचांगap_nr);

	uspi = sbi->s_uspi;
	अगर (sbi->s_cgno[biपंचांगap_nr] == UFS_CGNO_EMPTY) अणु
		UFSD("EXIT\n");
		वापस;
	पूर्ण
	ucpi = sbi->s_ucpi[biपंचांगap_nr];
	ucg = ubh_get_ucg(UCPI_UBH(ucpi));

	अगर (uspi->s_ncg > UFS_MAX_GROUP_LOADED && biपंचांगap_nr >= sbi->s_cg_loaded) अणु
		ufs_panic (sb, "ufs_put_cylinder", "internal error");
		वापस;
	पूर्ण
	/*
	 * rotor is not so important data, so we put it to disk 
	 * at the end of working with cylinder
	 */
	ucg->cg_rotor = cpu_to_fs32(sb, ucpi->c_rotor);
	ucg->cg_frotor = cpu_to_fs32(sb, ucpi->c_frotor);
	ucg->cg_irotor = cpu_to_fs32(sb, ucpi->c_irotor);
	ubh_mark_buffer_dirty (UCPI_UBH(ucpi));
	क्रम (i = 1; i < UCPI_UBH(ucpi)->count; i++) अणु
		brअन्यथा (UCPI_UBH(ucpi)->bh[i]);
	पूर्ण

	sbi->s_cgno[biपंचांगap_nr] = UFS_CGNO_EMPTY;
	UFSD("EXIT\n");
पूर्ण

/*
 * Find cylinder group in cache and वापस it as poपूर्णांकer.
 * If cylinder group is not in cache, we will load it from disk.
 *
 * The cache is managed by LRU algorithm. 
 */
काष्ठा ufs_cg_निजी_info * ufs_load_cylinder (
	काष्ठा super_block * sb, अचिन्हित cgno)
अणु
	काष्ठा ufs_sb_info * sbi = UFS_SB(sb);
	काष्ठा ufs_sb_निजी_info * uspi;
	काष्ठा ufs_cg_निजी_info * ucpi;
	अचिन्हित cg, i, j;

	UFSD("ENTER, cgno %u\n", cgno);

	uspi = sbi->s_uspi;
	अगर (cgno >= uspi->s_ncg) अणु
		ufs_panic (sb, "ufs_load_cylinder", "internal error, high number of cg");
		वापस शून्य;
	पूर्ण
	/*
	 * Cylinder group number cg it in cache and it was last used
	 */
	अगर (sbi->s_cgno[0] == cgno) अणु
		UFSD("EXIT\n");
		वापस sbi->s_ucpi[0];
	पूर्ण
	/*
	 * Number of cylinder groups is not higher than UFS_MAX_GROUP_LOADED
	 */
	अगर (uspi->s_ncg <= UFS_MAX_GROUP_LOADED) अणु
		अगर (sbi->s_cgno[cgno] != UFS_CGNO_EMPTY) अणु
			अगर (sbi->s_cgno[cgno] != cgno) अणु
				ufs_panic (sb, "ufs_load_cylinder", "internal error, wrong number of cg in cache");
				UFSD("EXIT (FAILED)\n");
				वापस शून्य;
			पूर्ण
			अन्यथा अणु
				UFSD("EXIT\n");
				वापस sbi->s_ucpi[cgno];
			पूर्ण
		पूर्ण अन्यथा अणु
			ufs_पढ़ो_cylinder (sb, cgno, cgno);
			UFSD("EXIT\n");
			वापस sbi->s_ucpi[cgno];
		पूर्ण
	पूर्ण
	/*
	 * Cylinder group number cg is in cache but it was not last used, 
	 * we will move to the first position
	 */
	क्रम (i = 0; i < sbi->s_cg_loaded && sbi->s_cgno[i] != cgno; i++);
	अगर (i < sbi->s_cg_loaded && sbi->s_cgno[i] == cgno) अणु
		cg = sbi->s_cgno[i];
		ucpi = sbi->s_ucpi[i];
		क्रम (j = i; j > 0; j--) अणु
			sbi->s_cgno[j] = sbi->s_cgno[j-1];
			sbi->s_ucpi[j] = sbi->s_ucpi[j-1];
		पूर्ण
		sbi->s_cgno[0] = cg;
		sbi->s_ucpi[0] = ucpi;
	/*
	 * Cylinder group number cg is not in cache, we will पढ़ो it from disk
	 * and put it to the first position
	 */
	पूर्ण अन्यथा अणु
		अगर (sbi->s_cg_loaded < UFS_MAX_GROUP_LOADED)
			sbi->s_cg_loaded++;
		अन्यथा
			ufs_put_cylinder (sb, UFS_MAX_GROUP_LOADED-1);
		ucpi = sbi->s_ucpi[sbi->s_cg_loaded - 1];
		क्रम (j = sbi->s_cg_loaded - 1; j > 0; j--) अणु
			sbi->s_cgno[j] = sbi->s_cgno[j-1];
			sbi->s_ucpi[j] = sbi->s_ucpi[j-1];
		पूर्ण
		sbi->s_ucpi[0] = ucpi;
		ufs_पढ़ो_cylinder (sb, cgno, 0);
	पूर्ण
	UFSD("EXIT\n");
	वापस sbi->s_ucpi[0];
पूर्ण
