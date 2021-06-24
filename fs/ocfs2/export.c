<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * export.c
 *
 * Functions to facilitate NFS exporting
 *
 * Copyright (C) 2002, 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "dir.h"
#समावेश "dlmglue.h"
#समावेश "dcache.h"
#समावेश "export.h"
#समावेश "inode.h"

#समावेश "buffer_head_io.h"
#समावेश "suballoc.h"
#समावेश "ocfs2_trace.h"

काष्ठा ocfs2_inode_handle
अणु
	u64 ih_blkno;
	u32 ih_generation;
पूर्ण;

अटल काष्ठा dentry *ocfs2_get_dentry(काष्ठा super_block *sb,
		काष्ठा ocfs2_inode_handle *handle)
अणु
	काष्ठा inode *inode;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	u64 blkno = handle->ih_blkno;
	पूर्णांक status, set;
	काष्ठा dentry *result;

	trace_ocfs2_get_dentry_begin(sb, handle, (अचिन्हित दीर्घ दीर्घ)blkno);

	अगर (blkno == 0) अणु
		result = ERR_PTR(-ESTALE);
		जाओ bail;
	पूर्ण

	inode = ocfs2_ilookup(sb, blkno);
	/*
	 * If the inode exists in memory, we only need to check it's
	 * generation number
	 */
	अगर (inode)
		जाओ check_gen;

	/*
	 * This will synchronize us against ocfs2_delete_inode() on
	 * all nodes
	 */
	status = ocfs2_nfs_sync_lock(osb, 1);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "getting nfs sync lock(EX) failed %d\n", status);
		जाओ check_err;
	पूर्ण

	status = ocfs2_test_inode_bit(osb, blkno, &set);
	अगर (status < 0) अणु
		अगर (status == -EINVAL) अणु
			/*
			 * The blkno NFS gave us करोesn't even show up
			 * as an inode, we वापस -ESTALE to be
			 * nice
			 */
			status = -ESTALE;
		पूर्ण अन्यथा
			mlog(ML_ERROR, "test inode bit failed %d\n", status);
		जाओ unlock_nfs_sync;
	पूर्ण

	trace_ocfs2_get_dentry_test_bit(status, set);
	/* If the inode allocator bit is clear, this inode must be stale */
	अगर (!set) अणु
		status = -ESTALE;
		जाओ unlock_nfs_sync;
	पूर्ण

	inode = ocfs2_iget(osb, blkno, 0, 0);

unlock_nfs_sync:
	ocfs2_nfs_sync_unlock(osb, 1);

check_err:
	अगर (status < 0) अणु
		अगर (status == -ESTALE) अणु
			trace_ocfs2_get_dentry_stale((अचिन्हित दीर्घ दीर्घ)blkno,
						     handle->ih_generation);
		पूर्ण
		result = ERR_PTR(status);
		जाओ bail;
	पूर्ण

	अगर (IS_ERR(inode)) अणु
		mlog_त्रुटि_सं(PTR_ERR(inode));
		result = ERR_CAST(inode);
		जाओ bail;
	पूर्ण

check_gen:
	अगर (handle->ih_generation != inode->i_generation) अणु
		trace_ocfs2_get_dentry_generation((अचिन्हित दीर्घ दीर्घ)blkno,
						  handle->ih_generation,
						  inode->i_generation);
		iput(inode);
		result = ERR_PTR(-ESTALE);
		जाओ bail;
	पूर्ण

	result = d_obtain_alias(inode);
	अगर (IS_ERR(result))
		mlog_त्रुटि_सं(PTR_ERR(result));

bail:
	trace_ocfs2_get_dentry_end(result);
	वापस result;
पूर्ण

अटल काष्ठा dentry *ocfs2_get_parent(काष्ठा dentry *child)
अणु
	पूर्णांक status;
	u64 blkno;
	काष्ठा dentry *parent;
	काष्ठा inode *dir = d_inode(child);
	पूर्णांक set;

	trace_ocfs2_get_parent(child, child->d_name.len, child->d_name.name,
			       (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno);

	status = ocfs2_nfs_sync_lock(OCFS2_SB(dir->i_sb), 1);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "getting nfs sync lock(EX) failed %d\n", status);
		parent = ERR_PTR(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_inode_lock(dir, शून्य, 0);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		parent = ERR_PTR(status);
		जाओ unlock_nfs_sync;
	पूर्ण

	status = ocfs2_lookup_ino_from_name(dir, "..", 2, &blkno);
	अगर (status < 0) अणु
		parent = ERR_PTR(-ENOENT);
		जाओ bail_unlock;
	पूर्ण

	status = ocfs2_test_inode_bit(OCFS2_SB(dir->i_sb), blkno, &set);
	अगर (status < 0) अणु
		अगर (status == -EINVAL) अणु
			status = -ESTALE;
		पूर्ण अन्यथा
			mlog(ML_ERROR, "test inode bit failed %d\n", status);
		parent = ERR_PTR(status);
		जाओ bail_unlock;
	पूर्ण

	trace_ocfs2_get_dentry_test_bit(status, set);
	अगर (!set) अणु
		status = -ESTALE;
		parent = ERR_PTR(status);
		जाओ bail_unlock;
	पूर्ण

	parent = d_obtain_alias(ocfs2_iget(OCFS2_SB(dir->i_sb), blkno, 0, 0));

bail_unlock:
	ocfs2_inode_unlock(dir, 0);

unlock_nfs_sync:
	ocfs2_nfs_sync_unlock(OCFS2_SB(dir->i_sb), 1);

bail:
	trace_ocfs2_get_parent_end(parent);

	वापस parent;
पूर्ण

अटल पूर्णांक ocfs2_encode_fh(काष्ठा inode *inode, u32 *fh_in, पूर्णांक *max_len,
			   काष्ठा inode *parent)
अणु
	पूर्णांक len = *max_len;
	पूर्णांक type = 1;
	u64 blkno;
	u32 generation;
	__le32 *fh = (__क्रमce __le32 *) fh_in;

#अगर_घोषित TRACE_HOOKS_ARE_NOT_BRAINDEAD_IN_YOUR_OPINION
#त्रुटि "You go ahead and fix that mess, then.  Somehow"
	trace_ocfs2_encode_fh_begin(dentry, dentry->d_name.len,
				    dentry->d_name.name,
				    fh, len, connectable);
#पूर्ण_अगर

	अगर (parent && (len < 6)) अणु
		*max_len = 6;
		type = खाताID_INVALID;
		जाओ bail;
	पूर्ण अन्यथा अगर (len < 3) अणु
		*max_len = 3;
		type = खाताID_INVALID;
		जाओ bail;
	पूर्ण

	blkno = OCFS2_I(inode)->ip_blkno;
	generation = inode->i_generation;

	trace_ocfs2_encode_fh_self((अचिन्हित दीर्घ दीर्घ)blkno, generation);

	len = 3;
	fh[0] = cpu_to_le32((u32)(blkno >> 32));
	fh[1] = cpu_to_le32((u32)(blkno & 0xffffffff));
	fh[2] = cpu_to_le32(generation);

	अगर (parent) अणु
		blkno = OCFS2_I(parent)->ip_blkno;
		generation = parent->i_generation;

		fh[3] = cpu_to_le32((u32)(blkno >> 32));
		fh[4] = cpu_to_le32((u32)(blkno & 0xffffffff));
		fh[5] = cpu_to_le32(generation);

		len = 6;
		type = 2;

		trace_ocfs2_encode_fh_parent((अचिन्हित दीर्घ दीर्घ)blkno,
					     generation);
	पूर्ण

	*max_len = len;

bail:
	trace_ocfs2_encode_fh_type(type);
	वापस type;
पूर्ण

अटल काष्ठा dentry *ocfs2_fh_to_dentry(काष्ठा super_block *sb,
		काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा ocfs2_inode_handle handle;

	अगर (fh_len < 3 || fh_type > 2)
		वापस शून्य;

	handle.ih_blkno = (u64)le32_to_cpu(fid->raw[0]) << 32;
	handle.ih_blkno |= (u64)le32_to_cpu(fid->raw[1]);
	handle.ih_generation = le32_to_cpu(fid->raw[2]);
	वापस ocfs2_get_dentry(sb, &handle);
पूर्ण

अटल काष्ठा dentry *ocfs2_fh_to_parent(काष्ठा super_block *sb,
		काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा ocfs2_inode_handle parent;

	अगर (fh_type != 2 || fh_len < 6)
		वापस शून्य;

	parent.ih_blkno = (u64)le32_to_cpu(fid->raw[3]) << 32;
	parent.ih_blkno |= (u64)le32_to_cpu(fid->raw[4]);
	parent.ih_generation = le32_to_cpu(fid->raw[5]);
	वापस ocfs2_get_dentry(sb, &parent);
पूर्ण

स्थिर काष्ठा export_operations ocfs2_export_ops = अणु
	.encode_fh	= ocfs2_encode_fh,
	.fh_to_dentry	= ocfs2_fh_to_dentry,
	.fh_to_parent	= ocfs2_fh_to_parent,
	.get_parent	= ocfs2_get_parent,
पूर्ण;
