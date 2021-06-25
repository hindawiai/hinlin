<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * dlmglue.h
 *
 * description here
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */


#अगर_अघोषित DLMGLUE_H
#घोषणा DLMGLUE_H

#समावेश "dcache.h"

#घोषणा OCFS2_LVB_VERSION 5

काष्ठा ocfs2_meta_lvb अणु
	__u8         lvb_version;
	__u8         lvb_reserved0;
	__be16       lvb_idynfeatures;
	__be32       lvb_iclusters;
	__be32       lvb_iuid;
	__be32       lvb_igid;
	__be64       lvb_iaसमय_packed;
	__be64       lvb_iस_समय_packed;
	__be64       lvb_imसमय_packed;
	__be64       lvb_isize;
	__be16       lvb_imode;
	__be16       lvb_inlink;
	__be32       lvb_iattr;
	__be32       lvb_igeneration;
	__be32       lvb_reserved2;
पूर्ण;

#घोषणा OCFS2_QINFO_LVB_VERSION 1

काष्ठा ocfs2_qinfo_lvb अणु
	__u8	lvb_version;
	__u8	lvb_reserved[3];
	__be32	lvb_bgrace;
	__be32	lvb_igrace;
	__be32	lvb_syncms;
	__be32	lvb_blocks;
	__be32	lvb_मुक्त_blk;
	__be32	lvb_मुक्त_entry;
पूर्ण;

#घोषणा OCFS2_ORPHAN_LVB_VERSION 1

काष्ठा ocfs2_orphan_scan_lvb अणु
	__u8	lvb_version;
	__u8	lvb_reserved[3];
	__be32	lvb_os_seqno;
पूर्ण;

#घोषणा OCFS2_TRIMFS_LVB_VERSION 1

काष्ठा ocfs2_trim_fs_lvb अणु
	__u8	lvb_version;
	__u8	lvb_success;
	__u8	lvb_reserved[2];
	__be32	lvb_nodक्रमागत;
	__be64	lvb_start;
	__be64	lvb_len;
	__be64	lvb_minlen;
	__be64	lvb_trimlen;
पूर्ण;

काष्ठा ocfs2_trim_fs_info अणु
	u8	tf_valid;	/* lvb is valid, or not */
	u8	tf_success;	/* trim is successful, or not */
	u32	tf_nodक्रमागत;	/* osb node number */
	u64	tf_start;	/* trim start offset in clusters */
	u64	tf_len;		/* trim end offset in clusters */
	u64	tf_minlen;	/* trim minimum contiguous मुक्त clusters */
	u64	tf_trimlen;	/* trimmed length in bytes */
पूर्ण;

काष्ठा ocfs2_lock_holder अणु
	काष्ठा list_head oh_list;
	काष्ठा pid *oh_owner_pid;
	पूर्णांक oh_ex;
पूर्ण;

/* ocfs2_inode_lock_full() 'arg_flags' flags */
/* करोn't रुको on recovery. */
#घोषणा OCFS2_META_LOCK_RECOVERY	(0x01)
/* Inकाष्ठा the dlm not to queue ourselves on the other node. */
#घोषणा OCFS2_META_LOCK_NOQUEUE		(0x02)
/* करोn't block रुकोing क्रम the करोwnconvert thपढ़ो, instead वापस -EAGAIN */
#घोषणा OCFS2_LOCK_NONBLOCK		(0x04)
/* just get back disk inode bh अगर we've got cluster lock. */
#घोषणा OCFS2_META_LOCK_GETBH		(0x08)

/* Locking subclasses of inode cluster lock */
क्रमागत अणु
	OI_LS_NORMAL = 0,
	OI_LS_PARENT,
	OI_LS_RENAME1,
	OI_LS_RENAME2,
	OI_LS_REFLINK_TARGET,
पूर्ण;

पूर्णांक ocfs2_dlm_init(काष्ठा ocfs2_super *osb);
व्योम ocfs2_dlm_shutकरोwn(काष्ठा ocfs2_super *osb, पूर्णांक hangup_pending);
व्योम ocfs2_lock_res_init_once(काष्ठा ocfs2_lock_res *res);
व्योम ocfs2_inode_lock_res_init(काष्ठा ocfs2_lock_res *res,
			       क्रमागत ocfs2_lock_type type,
			       अचिन्हित पूर्णांक generation,
			       काष्ठा inode *inode);
व्योम ocfs2_dentry_lock_res_init(काष्ठा ocfs2_dentry_lock *dl,
				u64 parent, काष्ठा inode *inode);
काष्ठा ocfs2_file_निजी;
व्योम ocfs2_file_lock_res_init(काष्ठा ocfs2_lock_res *lockres,
			      काष्ठा ocfs2_file_निजी *fp);
काष्ठा ocfs2_mem_dqinfo;
व्योम ocfs2_qinfo_lock_res_init(काष्ठा ocfs2_lock_res *lockres,
                               काष्ठा ocfs2_mem_dqinfo *info);
व्योम ocfs2_refcount_lock_res_init(काष्ठा ocfs2_lock_res *lockres,
				  काष्ठा ocfs2_super *osb, u64 ref_blkno,
				  अचिन्हित पूर्णांक generation);
व्योम ocfs2_lock_res_मुक्त(काष्ठा ocfs2_lock_res *res);
पूर्णांक ocfs2_create_new_inode_locks(काष्ठा inode *inode);
पूर्णांक ocfs2_drop_inode_locks(काष्ठा inode *inode);
पूर्णांक ocfs2_rw_lock(काष्ठा inode *inode, पूर्णांक ग_लिखो);
पूर्णांक ocfs2_try_rw_lock(काष्ठा inode *inode, पूर्णांक ग_लिखो);
व्योम ocfs2_rw_unlock(काष्ठा inode *inode, पूर्णांक ग_लिखो);
पूर्णांक ocfs2_खोलो_lock(काष्ठा inode *inode);
पूर्णांक ocfs2_try_खोलो_lock(काष्ठा inode *inode, पूर्णांक ग_लिखो);
व्योम ocfs2_खोलो_unlock(काष्ठा inode *inode);
पूर्णांक ocfs2_inode_lock_aसमय(काष्ठा inode *inode,
			  काष्ठा vfsmount *vfsmnt,
			  पूर्णांक *level, पूर्णांक रुको);
पूर्णांक ocfs2_inode_lock_full_nested(काष्ठा inode *inode,
			 काष्ठा buffer_head **ret_bh,
			 पूर्णांक ex,
			 पूर्णांक arg_flags,
			 पूर्णांक subclass);
पूर्णांक ocfs2_inode_lock_with_page(काष्ठा inode *inode,
			      काष्ठा buffer_head **ret_bh,
			      पूर्णांक ex,
			      काष्ठा page *page);
/* Variants without special locking class or flags */
#घोषणा ocfs2_inode_lock_full(i, r, e, f)\
		ocfs2_inode_lock_full_nested(i, r, e, f, OI_LS_NORMAL)
#घोषणा ocfs2_inode_lock_nested(i, b, e, s)\
		ocfs2_inode_lock_full_nested(i, b, e, 0, s)
/* 99% of the समय we करोn't want to supply any additional flags --
 * those are क्रम very specअगरic हालs only. */
#घोषणा ocfs2_inode_lock(i, b, e) ocfs2_inode_lock_full_nested(i, b, e, 0, OI_LS_NORMAL)
#घोषणा ocfs2_try_inode_lock(i, b, e)\
		ocfs2_inode_lock_full_nested(i, b, e, OCFS2_META_LOCK_NOQUEUE,\
		OI_LS_NORMAL)
व्योम ocfs2_inode_unlock(काष्ठा inode *inode,
		       पूर्णांक ex);
पूर्णांक ocfs2_super_lock(काष्ठा ocfs2_super *osb,
		     पूर्णांक ex);
व्योम ocfs2_super_unlock(काष्ठा ocfs2_super *osb,
			पूर्णांक ex);
पूर्णांक ocfs2_orphan_scan_lock(काष्ठा ocfs2_super *osb, u32 *seqno);
व्योम ocfs2_orphan_scan_unlock(काष्ठा ocfs2_super *osb, u32 seqno);

पूर्णांक ocfs2_नाम_lock(काष्ठा ocfs2_super *osb);
व्योम ocfs2_नाम_unlock(काष्ठा ocfs2_super *osb);
पूर्णांक ocfs2_nfs_sync_lock(काष्ठा ocfs2_super *osb, पूर्णांक ex);
व्योम ocfs2_nfs_sync_unlock(काष्ठा ocfs2_super *osb, पूर्णांक ex);
व्योम ocfs2_trim_fs_lock_res_init(काष्ठा ocfs2_super *osb);
व्योम ocfs2_trim_fs_lock_res_uninit(काष्ठा ocfs2_super *osb);
पूर्णांक ocfs2_trim_fs_lock(काष्ठा ocfs2_super *osb,
		       काष्ठा ocfs2_trim_fs_info *info, पूर्णांक trylock);
व्योम ocfs2_trim_fs_unlock(काष्ठा ocfs2_super *osb,
			  काष्ठा ocfs2_trim_fs_info *info);
पूर्णांक ocfs2_dentry_lock(काष्ठा dentry *dentry, पूर्णांक ex);
व्योम ocfs2_dentry_unlock(काष्ठा dentry *dentry, पूर्णांक ex);
पूर्णांक ocfs2_file_lock(काष्ठा file *file, पूर्णांक ex, पूर्णांक trylock);
व्योम ocfs2_file_unlock(काष्ठा file *file);
पूर्णांक ocfs2_qinfo_lock(काष्ठा ocfs2_mem_dqinfo *oinfo, पूर्णांक ex);
व्योम ocfs2_qinfo_unlock(काष्ठा ocfs2_mem_dqinfo *oinfo, पूर्णांक ex);
काष्ठा ocfs2_refcount_tree;
पूर्णांक ocfs2_refcount_lock(काष्ठा ocfs2_refcount_tree *ref_tree, पूर्णांक ex);
व्योम ocfs2_refcount_unlock(काष्ठा ocfs2_refcount_tree *ref_tree, पूर्णांक ex);


व्योम ocfs2_mark_lockres_मुक्तing(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_lock_res *lockres);
व्योम ocfs2_simple_drop_lockres(काष्ठा ocfs2_super *osb,
			       काष्ठा ocfs2_lock_res *lockres);

/* क्रम the करोwnconvert thपढ़ो */
व्योम ocfs2_wake_करोwnconvert_thपढ़ो(काष्ठा ocfs2_super *osb);

काष्ठा ocfs2_dlm_debug *ocfs2_new_dlm_debug(व्योम);
व्योम ocfs2_put_dlm_debug(काष्ठा ocfs2_dlm_debug *dlm_debug);

/* To set the locking protocol on module initialization */
व्योम ocfs2_set_locking_protocol(व्योम);

/* The _tracker pair is used to aव्योम cluster recursive locking */
पूर्णांक ocfs2_inode_lock_tracker(काष्ठा inode *inode,
			     काष्ठा buffer_head **ret_bh,
			     पूर्णांक ex,
			     काष्ठा ocfs2_lock_holder *oh);
व्योम ocfs2_inode_unlock_tracker(काष्ठा inode *inode,
				पूर्णांक ex,
				काष्ठा ocfs2_lock_holder *oh,
				पूर्णांक had_lock);

#पूर्ण_अगर	/* DLMGLUE_H */
