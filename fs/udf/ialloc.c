<शैली गुरु>
/*
 * ialloc.c
 *
 * PURPOSE
 *	Inode allocation handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 *
 *  (C) 1998-2001 Ben Fennema
 *
 * HISTORY
 *
 *  02/24/99 blf  Created.
 *
 */

#समावेश "udfdecl.h"
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश "udf_i.h"
#समावेश "udf_sb.h"

व्योम udf_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा logicalVolIntegrityDescImpUse *lvidiu = udf_sb_lvidiu(sb);

	अगर (lvidiu) अणु
		mutex_lock(&sbi->s_alloc_mutex);
		अगर (S_ISसूची(inode->i_mode))
			le32_add_cpu(&lvidiu->numDirs, -1);
		अन्यथा
			le32_add_cpu(&lvidiu->numFiles, -1);
		udf_updated_lvid(sb);
		mutex_unlock(&sbi->s_alloc_mutex);
	पूर्ण

	udf_मुक्त_blocks(sb, शून्य, &UDF_I(inode)->i_location, 0, 1);
पूर्ण

काष्ठा inode *udf_new_inode(काष्ठा inode *dir, umode_t mode)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);
	काष्ठा inode *inode;
	udf_pblk_t block;
	uपूर्णांक32_t start = UDF_I(dir)->i_location.logicalBlockNum;
	काष्ठा udf_inode_info *iinfo;
	काष्ठा udf_inode_info *dinfo = UDF_I(dir);
	काष्ठा logicalVolIntegrityDescImpUse *lvidiu;
	पूर्णांक err;

	inode = new_inode(sb);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	iinfo = UDF_I(inode);
	अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_EXTENDED_FE)) अणु
		iinfo->i_efe = 1;
		अगर (UDF_VERS_USE_EXTENDED_FE > sbi->s_udfrev)
			sbi->s_udfrev = UDF_VERS_USE_EXTENDED_FE;
		iinfo->i_data = kzalloc(inode->i_sb->s_blocksize -
					माप(काष्ठा extendedFileEntry),
					GFP_KERNEL);
	पूर्ण अन्यथा अणु
		iinfo->i_efe = 0;
		iinfo->i_data = kzalloc(inode->i_sb->s_blocksize -
					माप(काष्ठा fileEntry),
					GFP_KERNEL);
	पूर्ण
	अगर (!iinfo->i_data) अणु
		iput(inode);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	err = -ENOSPC;
	block = udf_new_block(dir->i_sb, शून्य,
			      dinfo->i_location.partitionReferenceNum,
			      start, &err);
	अगर (err) अणु
		iput(inode);
		वापस ERR_PTR(err);
	पूर्ण

	lvidiu = udf_sb_lvidiu(sb);
	अगर (lvidiu) अणु
		iinfo->i_unique = lvid_get_unique_id(sb);
		inode->i_generation = iinfo->i_unique;
		mutex_lock(&sbi->s_alloc_mutex);
		अगर (S_ISसूची(mode))
			le32_add_cpu(&lvidiu->numDirs, 1);
		अन्यथा
			le32_add_cpu(&lvidiu->numFiles, 1);
		udf_updated_lvid(sb);
		mutex_unlock(&sbi->s_alloc_mutex);
	पूर्ण

	inode_init_owner(&init_user_ns, inode, dir, mode);
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_UID_SET))
		inode->i_uid = sbi->s_uid;
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_GID_SET))
		inode->i_gid = sbi->s_gid;

	iinfo->i_location.logicalBlockNum = block;
	iinfo->i_location.partitionReferenceNum =
				dinfo->i_location.partitionReferenceNum;
	inode->i_ino = udf_get_lb_pblock(sb, &iinfo->i_location, 0);
	inode->i_blocks = 0;
	iinfo->i_lenEAttr = 0;
	iinfo->i_lenAlloc = 0;
	iinfo->i_use = 0;
	iinfo->i_checkpoपूर्णांक = 1;
	iinfo->i_extraPerms = FE_PERM_U_CHATTR;
	udf_update_extra_perms(inode, mode);

	अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_AD_IN_ICB))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
	अन्यथा अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
	अन्यथा
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	iinfo->i_crसमय = inode->i_mसमय;
	अगर (unlikely(insert_inode_locked(inode) < 0)) अणु
		make_bad_inode(inode);
		iput(inode);
		वापस ERR_PTR(-EIO);
	पूर्ण
	mark_inode_dirty(inode);

	वापस inode;
पूर्ण
