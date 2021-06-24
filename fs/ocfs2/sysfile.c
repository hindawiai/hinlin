<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sysfile.c
 *
 * Initialize, पढ़ो, ग_लिखो, etc. प्रणाली files.
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "dir.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "sysfile.h"

#समावेश "buffer_head_io.h"

अटल काष्ठा inode * _ocfs2_get_प्रणाली_file_inode(काष्ठा ocfs2_super *osb,
						   पूर्णांक type,
						   u32 slot);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल काष्ठा lock_class_key ocfs2_sysfile_cluster_lock_key[NUM_SYSTEM_INODES];
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक is_global_प्रणाली_inode(पूर्णांक type)
अणु
	वापस type >= OCFS2_FIRST_ONLINE_SYSTEM_INODE &&
		type <= OCFS2_LAST_GLOBAL_SYSTEM_INODE;
पूर्ण

अटल काष्ठा inode **get_local_प्रणाली_inode(काष्ठा ocfs2_super *osb,
					     पूर्णांक type,
					     u32 slot)
अणु
	पूर्णांक index;
	काष्ठा inode **local_प्रणाली_inodes, **मुक्त = शून्य;

	BUG_ON(slot == OCFS2_INVALID_SLOT);
	BUG_ON(type < OCFS2_FIRST_LOCAL_SYSTEM_INODE ||
	       type > OCFS2_LAST_LOCAL_SYSTEM_INODE);

	spin_lock(&osb->osb_lock);
	local_प्रणाली_inodes = osb->local_प्रणाली_inodes;
	spin_unlock(&osb->osb_lock);

	अगर (unlikely(!local_प्रणाली_inodes)) अणु
		local_प्रणाली_inodes =
			kzalloc(array3_size(माप(काष्ठा inode *),
					    NUM_LOCAL_SYSTEM_INODES,
					    osb->max_slots),
				GFP_NOFS);
		अगर (!local_प्रणाली_inodes) अणु
			mlog_त्रुटि_सं(-ENOMEM);
			/*
			 * वापस शून्य here so that ocfs2_get_sytem_file_inodes
			 * will try to create an inode and use it. We will try
			 * to initialize local_प्रणाली_inodes next समय.
			 */
			वापस शून्य;
		पूर्ण

		spin_lock(&osb->osb_lock);
		अगर (osb->local_प्रणाली_inodes) अणु
			/* Someone has initialized it क्रम us. */
			मुक्त = local_प्रणाली_inodes;
			local_प्रणाली_inodes = osb->local_प्रणाली_inodes;
		पूर्ण अन्यथा
			osb->local_प्रणाली_inodes = local_प्रणाली_inodes;
		spin_unlock(&osb->osb_lock);
		kमुक्त(मुक्त);
	पूर्ण

	index = (slot * NUM_LOCAL_SYSTEM_INODES) +
		(type - OCFS2_FIRST_LOCAL_SYSTEM_INODE);

	वापस &local_प्रणाली_inodes[index];
पूर्ण

काष्ठा inode *ocfs2_get_प्रणाली_file_inode(काष्ठा ocfs2_super *osb,
					  पूर्णांक type,
					  u32 slot)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा inode **arr = शून्य;

	/* aव्योम the lookup अगर cached in local प्रणाली file array */
	अगर (is_global_प्रणाली_inode(type)) अणु
		arr = &(osb->global_प्रणाली_inodes[type]);
	पूर्ण अन्यथा
		arr = get_local_प्रणाली_inode(osb, type, slot);

	mutex_lock(&osb->प्रणाली_file_mutex);
	अगर (arr && ((inode = *arr) != शून्य)) अणु
		/* get a ref in addition to the array ref */
		inode = igrab(inode);
		mutex_unlock(&osb->प्रणाली_file_mutex);
		BUG_ON(!inode);

		वापस inode;
	पूर्ण

	/* this माला_लो one ref thru iget */
	inode = _ocfs2_get_प्रणाली_file_inode(osb, type, slot);

	/* add one more अगर putting पूर्णांकo array क्रम first समय */
	अगर (arr && inode) अणु
		*arr = igrab(inode);
		BUG_ON(!*arr);
	पूर्ण
	mutex_unlock(&osb->प्रणाली_file_mutex);
	वापस inode;
पूर्ण

अटल काष्ठा inode * _ocfs2_get_प्रणाली_file_inode(काष्ठा ocfs2_super *osb,
						   पूर्णांक type,
						   u32 slot)
अणु
	अक्षर namebuf[40];
	काष्ठा inode *inode = शून्य;
	u64 blkno;
	पूर्णांक status = 0;

	ocfs2_प्र_लिखो_प्रणाली_inode_name(namebuf,
					माप(namebuf),
					type, slot);

	status = ocfs2_lookup_ino_from_name(osb->sys_root_inode, namebuf,
					    म_माप(namebuf), &blkno);
	अगर (status < 0) अणु
		जाओ bail;
	पूर्ण

	inode = ocfs2_iget(osb, blkno, OCFS2_FI_FLAG_SYSखाता, type);
	अगर (IS_ERR(inode)) अणु
		mlog_त्रुटि_सं(PTR_ERR(inode));
		inode = शून्य;
		जाओ bail;
	पूर्ण
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	अगर (type == LOCAL_USER_QUOTA_SYSTEM_INODE ||
	    type == LOCAL_GROUP_QUOTA_SYSTEM_INODE ||
	    type == JOURNAL_SYSTEM_INODE) अणु
		/* Ignore inode lock on these inodes as the lock करोes not
		 * really beदीर्घ to any process and lockdep cannot handle
		 * that */
		OCFS2_I(inode)->ip_inode_lockres.l_lockdep_map.key = शून्य;
	पूर्ण अन्यथा अणु
		lockdep_init_map(&OCFS2_I(inode)->ip_inode_lockres.
								l_lockdep_map,
				 ocfs2_प्रणाली_inodes[type].si_name,
				 &ocfs2_sysfile_cluster_lock_key[type], 0);
	पूर्ण
#पूर्ण_अगर
bail:

	वापस inode;
पूर्ण

