<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/isofs/export.c
 *
 *  (C) 2004  Paul Serice - The new inode scheme requires चयनing
 *                          from iget() to iget5_locked() which means
 *                          the NFS export operations have to be hand
 *                          coded because the शेष routines rely on
 *                          iget().
 *
 * The following files are helpful:
 *
 *     Documentation/fileप्रणालीs/nfs/exporting.rst
 *     fs/exportfs/expfs.c.
 */

#समावेश "isofs.h"

अटल काष्ठा dentry *
isofs_export_iget(काष्ठा super_block *sb,
		  अचिन्हित दीर्घ block,
		  अचिन्हित दीर्घ offset,
		  __u32 generation)
अणु
	काष्ठा inode *inode;

	अगर (block == 0)
		वापस ERR_PTR(-ESTALE);
	inode = isofs_iget(sb, block, offset);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (generation && inode->i_generation != generation) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस d_obtain_alias(inode);
पूर्ण

/* This function is surprisingly simple.  The trick is understanding
 * that "child" is always a directory. So, to find its parent, you
 * simply need to find its ".." entry, normalize its block and offset,
 * and वापस the underlying inode.  See the comments क्रम
 * isofs_normalize_block_and_offset(). */
अटल काष्ठा dentry *isofs_export_get_parent(काष्ठा dentry *child)
अणु
	अचिन्हित दीर्घ parent_block = 0;
	अचिन्हित दीर्घ parent_offset = 0;
	काष्ठा inode *child_inode = d_inode(child);
	काष्ठा iso_inode_info *e_child_inode = ISOFS_I(child_inode);
	काष्ठा iso_directory_record *de = शून्य;
	काष्ठा buffer_head * bh = शून्य;
	काष्ठा dentry *rv = शून्य;

	/* "child" must always be a directory. */
	अगर (!S_ISसूची(child_inode->i_mode)) अणु
		prपूर्णांकk(KERN_ERR "isofs: isofs_export_get_parent(): "
		       "child is not a directory!\n");
		rv = ERR_PTR(-EACCES);
		जाओ out;
	पूर्ण

	/* It is an invariant that the directory offset is zero.  If
	 * it is not zero, it means the directory failed to be
	 * normalized क्रम some reason. */
	अगर (e_child_inode->i_iget5_offset != 0) अणु
		prपूर्णांकk(KERN_ERR "isofs: isofs_export_get_parent(): "
		       "child directory not normalized!\n");
		rv = ERR_PTR(-EACCES);
		जाओ out;
	पूर्ण

	/* The child inode has been normalized such that its
	 * i_iget5_block value poपूर्णांकs to the "." entry.  Fortunately,
	 * the ".." entry is located in the same block. */
	parent_block = e_child_inode->i_iget5_block;

	/* Get the block in question. */
	bh = sb_bपढ़ो(child_inode->i_sb, parent_block);
	अगर (bh == शून्य) अणु
		rv = ERR_PTR(-EACCES);
		जाओ out;
	पूर्ण

	/* This is the "." entry. */
	de = (काष्ठा iso_directory_record*)bh->b_data;

	/* The ".." entry is always the second entry. */
	parent_offset = (अचिन्हित दीर्घ)isonum_711(de->length);
	de = (काष्ठा iso_directory_record*)(bh->b_data + parent_offset);

	/* Verअगरy it is in fact the ".." entry. */
	अगर ((isonum_711(de->name_len) != 1) || (de->name[0] != 1)) अणु
		prपूर्णांकk(KERN_ERR "isofs: Unable to find the \"..\" "
		       "directory for NFS.\n");
		rv = ERR_PTR(-EACCES);
		जाओ out;
	पूर्ण

	/* Normalize */
	isofs_normalize_block_and_offset(de, &parent_block, &parent_offset);

	rv = d_obtain_alias(isofs_iget(child_inode->i_sb, parent_block,
				     parent_offset));
 out:
	अगर (bh)
		brअन्यथा(bh);
	वापस rv;
पूर्ण

अटल पूर्णांक
isofs_export_encode_fh(काष्ठा inode *inode,
		       __u32 *fh32,
		       पूर्णांक *max_len,
		       काष्ठा inode *parent)
अणु
	काष्ठा iso_inode_info * ei = ISOFS_I(inode);
	पूर्णांक len = *max_len;
	पूर्णांक type = 1;
	__u16 *fh16 = (__u16*)fh32;

	/*
	 * WARNING: max_len is 5 क्रम NFSv2.  Because of this
	 * limitation, we use the lower 16 bits of fh32[1] to hold the
	 * offset of the inode and the upper 16 bits of fh32[1] to
	 * hold the offset of the parent.
	 */
	अगर (parent && (len < 5)) अणु
		*max_len = 5;
		वापस खाताID_INVALID;
	पूर्ण अन्यथा अगर (len < 3) अणु
		*max_len = 3;
		वापस खाताID_INVALID;
	पूर्ण

	len = 3;
	fh32[0] = ei->i_iget5_block;
 	fh16[2] = (__u16)ei->i_iget5_offset;  /* fh16 [sic] */
	fh16[3] = 0;  /* aव्योम leaking uninitialized data */
	fh32[2] = inode->i_generation;
	अगर (parent) अणु
		काष्ठा iso_inode_info *eparent;
		eparent = ISOFS_I(parent);
		fh32[3] = eparent->i_iget5_block;
		fh16[3] = (__u16)eparent->i_iget5_offset;  /* fh16 [sic] */
		fh32[4] = parent->i_generation;
		len = 5;
		type = 2;
	पूर्ण
	*max_len = len;
	वापस type;
पूर्ण

काष्ठा isofs_fid अणु
	u32 block;
	u16 offset;
	u16 parent_offset;
	u32 generation;
	u32 parent_block;
	u32 parent_generation;
पूर्ण;

अटल काष्ठा dentry *isofs_fh_to_dentry(काष्ठा super_block *sb,
	काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा isofs_fid *अगरid = (काष्ठा isofs_fid *)fid;

	अगर (fh_len < 3 || fh_type > 2)
		वापस शून्य;

	वापस isofs_export_iget(sb, अगरid->block, अगरid->offset,
			अगरid->generation);
पूर्ण

अटल काष्ठा dentry *isofs_fh_to_parent(काष्ठा super_block *sb,
		काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा isofs_fid *अगरid = (काष्ठा isofs_fid *)fid;

	अगर (fh_len < 2 || fh_type != 2)
		वापस शून्य;

	वापस isofs_export_iget(sb,
			fh_len > 2 ? अगरid->parent_block : 0,
			अगरid->parent_offset,
			fh_len > 4 ? अगरid->parent_generation : 0);
पूर्ण

स्थिर काष्ठा export_operations isofs_export_ops = अणु
	.encode_fh	= isofs_export_encode_fh,
	.fh_to_dentry	= isofs_fh_to_dentry,
	.fh_to_parent	= isofs_fh_to_parent,
	.get_parent     = isofs_export_get_parent,
पूर्ण;
