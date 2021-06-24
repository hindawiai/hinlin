<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * file.h
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_खाता_H
#घोषणा OCFS2_खाता_H

बाह्य स्थिर काष्ठा file_operations ocfs2_fops;
बाह्य स्थिर काष्ठा file_operations ocfs2_करोps;
बाह्य स्थिर काष्ठा file_operations ocfs2_fops_no_plocks;
बाह्य स्थिर काष्ठा file_operations ocfs2_करोps_no_plocks;
बाह्य स्थिर काष्ठा inode_operations ocfs2_file_iops;
बाह्य स्थिर काष्ठा inode_operations ocfs2_special_file_iops;
काष्ठा ocfs2_alloc_context;
क्रमागत ocfs2_alloc_restarted;

काष्ठा ocfs2_file_निजी अणु
	काष्ठा file		*fp_file;
	काष्ठा mutex		fp_mutex;
	काष्ठा ocfs2_lock_res	fp_flock;
पूर्ण;

पूर्णांक ocfs2_add_inode_data(काष्ठा ocfs2_super *osb,
			 काष्ठा inode *inode,
			 u32 *logical_offset,
			 u32 clusters_to_add,
			 पूर्णांक mark_unwritten,
			 काष्ठा buffer_head *fe_bh,
			 handle_t *handle,
			 काष्ठा ocfs2_alloc_context *data_ac,
			 काष्ठा ocfs2_alloc_context *meta_ac,
			 क्रमागत ocfs2_alloc_restarted *reason_ret);
पूर्णांक ocfs2_set_inode_size(handle_t *handle,
		काष्ठा inode *inode,
		काष्ठा buffer_head *fe_bh,
		u64 new_i_size);
पूर्णांक ocfs2_simple_size_update(काष्ठा inode *inode,
			     काष्ठा buffer_head *di_bh,
			     u64 new_i_size);
पूर्णांक ocfs2_truncate_file(काष्ठा inode *inode,
		काष्ठा buffer_head *di_bh,
		u64 new_i_size);
पूर्णांक ocfs2_extend_no_holes(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
			  u64 new_i_size, u64 zero_to);
पूर्णांक ocfs2_zero_extend(काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
		      loff_t zero_to);
पूर्णांक ocfs2_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		  काष्ठा iattr *attr);
पूर्णांक ocfs2_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		  काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags);
पूर्णांक ocfs2_permission(काष्ठा user_namespace *mnt_userns,
		     काष्ठा inode *inode,
		     पूर्णांक mask);

पूर्णांक ocfs2_should_update_aसमय(काष्ठा inode *inode,
			      काष्ठा vfsmount *vfsmnt);
पूर्णांक ocfs2_update_inode_aसमय(काष्ठा inode *inode,
			     काष्ठा buffer_head *bh);

पूर्णांक ocfs2_change_file_space(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    काष्ठा ocfs2_space_resv *sr);

पूर्णांक ocfs2_check_range_क्रम_refcount(काष्ठा inode *inode, loff_t pos,
				   माप_प्रकार count);
पूर्णांक ocfs2_हटाओ_inode_range(काष्ठा inode *inode,
			     काष्ठा buffer_head *di_bh, u64 byte_start,
			     u64 byte_len);
#पूर्ण_अगर /* OCFS2_खाता_H */
