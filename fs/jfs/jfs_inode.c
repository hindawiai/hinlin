<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */

#समावेश <linux/fs.h>
#समावेश <linux/quotaops.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_dinode.h"
#समावेश "jfs_debug.h"


व्योम jfs_set_inode_flags(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक flags = JFS_IP(inode)->mode2;
	अचिन्हित पूर्णांक new_fl = 0;

	अगर (flags & JFS_IMMUTABLE_FL)
		new_fl |= S_IMMUTABLE;
	अगर (flags & JFS_APPEND_FL)
		new_fl |= S_APPEND;
	अगर (flags & JFS_NOATIME_FL)
		new_fl |= S_NOATIME;
	अगर (flags & JFS_सूचीSYNC_FL)
		new_fl |= S_सूचीSYNC;
	अगर (flags & JFS_SYNC_FL)
		new_fl |= S_SYNC;
	inode_set_flags(inode, new_fl, S_IMMUTABLE | S_APPEND | S_NOATIME |
			S_सूचीSYNC | S_SYNC);
पूर्ण

/*
 * NAME:	ialloc()
 *
 * FUNCTION:	Allocate a new inode
 *
 */
काष्ठा inode *ialloc(काष्ठा inode *parent, umode_t mode)
अणु
	काष्ठा super_block *sb = parent->i_sb;
	काष्ठा inode *inode;
	काष्ठा jfs_inode_info *jfs_inode;
	पूर्णांक rc;

	inode = new_inode(sb);
	अगर (!inode) अणु
		jfs_warn("ialloc: new_inode returned NULL!");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	jfs_inode = JFS_IP(inode);

	rc = diAlloc(parent, S_ISसूची(mode), inode);
	अगर (rc) अणु
		jfs_warn("ialloc: diAlloc returned %d!", rc);
		जाओ fail_put;
	पूर्ण

	अगर (insert_inode_locked(inode) < 0) अणु
		rc = -EINVAL;
		जाओ fail_put;
	पूर्ण

	inode_init_owner(&init_user_ns, inode, parent, mode);
	/*
	 * New inodes need to save sane values on disk when
	 * uid & gid mount options are used
	 */
	jfs_inode->saved_uid = inode->i_uid;
	jfs_inode->saved_gid = inode->i_gid;

	/*
	 * Allocate inode to quota.
	 */
	rc = dquot_initialize(inode);
	अगर (rc)
		जाओ fail_drop;
	rc = dquot_alloc_inode(inode);
	अगर (rc)
		जाओ fail_drop;

	/* inherit flags from parent */
	jfs_inode->mode2 = JFS_IP(parent)->mode2 & JFS_FL_INHERIT;

	अगर (S_ISसूची(mode)) अणु
		jfs_inode->mode2 |= IसूचीECTORY;
		jfs_inode->mode2 &= ~JFS_सूचीSYNC_FL;
	पूर्ण
	अन्यथा अणु
		jfs_inode->mode2 |= INLINEEA | ISPARSE;
		अगर (S_ISLNK(mode))
			jfs_inode->mode2 &= ~(JFS_IMMUTABLE_FL|JFS_APPEND_FL);
	पूर्ण
	jfs_inode->mode2 |= inode->i_mode;

	inode->i_blocks = 0;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	jfs_inode->oसमय = inode->i_स_समय.tv_sec;
	inode->i_generation = JFS_SBI(sb)->gengen++;

	jfs_inode->cflag = 0;

	/* Zero reमुख्यing fields */
	स_रखो(&jfs_inode->acl, 0, माप(dxd_t));
	स_रखो(&jfs_inode->ea, 0, माप(dxd_t));
	jfs_inode->next_index = 0;
	jfs_inode->acltype = 0;
	jfs_inode->btorder = 0;
	jfs_inode->btindex = 0;
	jfs_inode->bxflag = 0;
	jfs_inode->blid = 0;
	jfs_inode->atlhead = 0;
	jfs_inode->atltail = 0;
	jfs_inode->xtlid = 0;
	jfs_set_inode_flags(inode);

	jfs_info("ialloc returns inode = 0x%p", inode);

	वापस inode;

fail_drop:
	dquot_drop(inode);
	inode->i_flags |= S_NOQUOTA;
	clear_nlink(inode);
	discard_new_inode(inode);
	वापस ERR_PTR(rc);

fail_put:
	iput(inode);
	वापस ERR_PTR(rc);
पूर्ण
