<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * सूची.स
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_सूची_H
#घोषणा OCFS2_सूची_H

काष्ठा ocfs2_dx_hinfo अणु
	u32	major_hash;
	u32	minor_hash;
पूर्ण;

काष्ठा ocfs2_dir_lookup_result अणु
	काष्ठा buffer_head		*dl_leaf_bh;	/* Unindexed leaf
							 * block */
	काष्ठा ocfs2_dir_entry		*dl_entry;	/* Target dirent in
							 * unindexed leaf */

	काष्ठा buffer_head		*dl_dx_root_bh;	/* Root of indexed
							 * tree */

	काष्ठा buffer_head		*dl_dx_leaf_bh;	/* Indexed leaf block */
	काष्ठा ocfs2_dx_entry		*dl_dx_entry;	/* Target dx_entry in
							 * indexed leaf */
	काष्ठा ocfs2_dx_hinfo		dl_hinfo;	/* Name hash results */

	काष्ठा buffer_head		*dl_prev_leaf_bh;/* Previous entry in
							  * dir मुक्त space
							  * list. शून्य अगर
							  * previous entry is
							  * dx root block. */
पूर्ण;

व्योम ocfs2_मुक्त_dir_lookup_result(काष्ठा ocfs2_dir_lookup_result *res);

पूर्णांक ocfs2_find_entry(स्थिर अक्षर *name, पूर्णांक namelen,
		     काष्ठा inode *dir,
		     काष्ठा ocfs2_dir_lookup_result *lookup);
पूर्णांक ocfs2_delete_entry(handle_t *handle,
		       काष्ठा inode *dir,
		       काष्ठा ocfs2_dir_lookup_result *res);
पूर्णांक __ocfs2_add_entry(handle_t *handle,
		      काष्ठा inode *dir,
		      स्थिर अक्षर *name, पूर्णांक namelen,
		      काष्ठा inode *inode, u64 blkno,
		      काष्ठा buffer_head *parent_fe_bh,
		      काष्ठा ocfs2_dir_lookup_result *lookup);
अटल अंतरभूत पूर्णांक ocfs2_add_entry(handle_t *handle,
				  काष्ठा dentry *dentry,
				  काष्ठा inode *inode, u64 blkno,
				  काष्ठा buffer_head *parent_fe_bh,
				  काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	वापस __ocfs2_add_entry(handle, d_inode(dentry->d_parent),
				 dentry->d_name.name, dentry->d_name.len,
				 inode, blkno, parent_fe_bh, lookup);
पूर्ण
पूर्णांक ocfs2_update_entry(काष्ठा inode *dir, handle_t *handle,
		       काष्ठा ocfs2_dir_lookup_result *res,
		       काष्ठा inode *new_entry_inode);

पूर्णांक ocfs2_check_dir_क्रम_entry(काष्ठा inode *dir,
			      स्थिर अक्षर *name,
			      पूर्णांक namelen);
पूर्णांक ocfs2_empty_dir(काष्ठा inode *inode);

पूर्णांक ocfs2_find_files_on_disk(स्थिर अक्षर *name,
			     पूर्णांक namelen,
			     u64 *blkno,
			     काष्ठा inode *inode,
			     काष्ठा ocfs2_dir_lookup_result *res);
पूर्णांक ocfs2_lookup_ino_from_name(काष्ठा inode *dir, स्थिर अक्षर *name,
			       पूर्णांक namelen, u64 *blkno);
पूर्णांक ocfs2_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx);
पूर्णांक ocfs2_dir_क्रमeach(काष्ठा inode *inode, काष्ठा dir_context *ctx);
पूर्णांक ocfs2_prepare_dir_क्रम_insert(काष्ठा ocfs2_super *osb,
				 काष्ठा inode *dir,
				 काष्ठा buffer_head *parent_fe_bh,
				 स्थिर अक्षर *name,
				 पूर्णांक namelen,
				 काष्ठा ocfs2_dir_lookup_result *lookup);
काष्ठा ocfs2_alloc_context;
पूर्णांक ocfs2_fill_new_dir(काष्ठा ocfs2_super *osb,
		       handle_t *handle,
		       काष्ठा inode *parent,
		       काष्ठा inode *inode,
		       काष्ठा buffer_head *fe_bh,
		       काष्ठा ocfs2_alloc_context *data_ac,
		       काष्ठा ocfs2_alloc_context *meta_ac);

पूर्णांक ocfs2_dx_dir_truncate(काष्ठा inode *dir, काष्ठा buffer_head *di_bh);

काष्ठा ocfs2_dir_block_trailer *ocfs2_dir_trailer_from_size(पूर्णांक blocksize,
							    व्योम *data);
#पूर्ण_अगर /* OCFS2_सूची_H */
