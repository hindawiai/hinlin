<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xattr.c
 *
 * Copyright (C) 2004, 2008 Oracle.  All rights reserved.
 *
 * CREDITS:
 * Lots of code in this file is copy from linux/fs/ext3/xattr.c.
 * Copyright (C) 2001-2003 Andreas Gruenbacher, <agruen@suse.de>
 */

#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/sched.h>
#समावेश <linux/splice.h>
#समावेश <linux/mount.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/sort.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/security.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"
#समावेश "alloc.h"
#समावेश "blockcheck.h"
#समावेश "dlmglue.h"
#समावेश "file.h"
#समावेश "symlink.h"
#समावेश "sysfile.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "ocfs2_fs.h"
#समावेश "suballoc.h"
#समावेश "uptodate.h"
#समावेश "buffer_head_io.h"
#समावेश "super.h"
#समावेश "xattr.h"
#समावेश "refcounttree.h"
#समावेश "acl.h"
#समावेश "ocfs2_trace.h"

काष्ठा ocfs2_xattr_def_value_root अणु
	काष्ठा ocfs2_xattr_value_root	xv;
	काष्ठा ocfs2_extent_rec		er;
पूर्ण;

काष्ठा ocfs2_xattr_bucket अणु
	/* The inode these xattrs are associated with */
	काष्ठा inode *bu_inode;

	/* The actual buffers that make up the bucket */
	काष्ठा buffer_head *bu_bhs[OCFS2_XATTR_MAX_BLOCKS_PER_BUCKET];

	/* How many blocks make up one bucket क्रम this fileप्रणाली */
	पूर्णांक bu_blocks;
पूर्ण;

काष्ठा ocfs2_xattr_set_ctxt अणु
	handle_t *handle;
	काष्ठा ocfs2_alloc_context *meta_ac;
	काष्ठा ocfs2_alloc_context *data_ac;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	पूर्णांक set_पात;
पूर्ण;

#घोषणा OCFS2_XATTR_ROOT_SIZE	(माप(काष्ठा ocfs2_xattr_def_value_root))
#घोषणा OCFS2_XATTR_INLINE_SIZE	80
#घोषणा OCFS2_XATTR_HEADER_GAP	4
#घोषणा OCFS2_XATTR_FREE_IN_IBODY	(OCFS2_MIN_XATTR_INLINE_SIZE \
					 - माप(काष्ठा ocfs2_xattr_header) \
					 - OCFS2_XATTR_HEADER_GAP)
#घोषणा OCFS2_XATTR_FREE_IN_BLOCK(ptr)	((ptr)->i_sb->s_blocksize \
					 - माप(काष्ठा ocfs2_xattr_block) \
					 - माप(काष्ठा ocfs2_xattr_header) \
					 - OCFS2_XATTR_HEADER_GAP)

अटल काष्ठा ocfs2_xattr_def_value_root def_xv = अणु
	.xv.xr_list.l_count = cpu_to_le16(1),
पूर्ण;

स्थिर काष्ठा xattr_handler *ocfs2_xattr_handlers[] = अणु
	&ocfs2_xattr_user_handler,
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
	&ocfs2_xattr_trusted_handler,
	&ocfs2_xattr_security_handler,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा xattr_handler *ocfs2_xattr_handler_map[OCFS2_XATTR_MAX] = अणु
	[OCFS2_XATTR_INDEX_USER]	= &ocfs2_xattr_user_handler,
	[OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS]
					= &posix_acl_access_xattr_handler,
	[OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT]
					= &posix_acl_शेष_xattr_handler,
	[OCFS2_XATTR_INDEX_TRUSTED]	= &ocfs2_xattr_trusted_handler,
	[OCFS2_XATTR_INDEX_SECURITY]	= &ocfs2_xattr_security_handler,
पूर्ण;

काष्ठा ocfs2_xattr_info अणु
	पूर्णांक		xi_name_index;
	स्थिर अक्षर	*xi_name;
	पूर्णांक		xi_name_len;
	स्थिर व्योम	*xi_value;
	माप_प्रकार		xi_value_len;
पूर्ण;

काष्ठा ocfs2_xattr_search अणु
	काष्ठा buffer_head *inode_bh;
	/*
	 * xattr_bh poपूर्णांक to the block buffer head which has extended attribute
	 * when extended attribute in inode, xattr_bh is equal to inode_bh.
	 */
	काष्ठा buffer_head *xattr_bh;
	काष्ठा ocfs2_xattr_header *header;
	काष्ठा ocfs2_xattr_bucket *bucket;
	व्योम *base;
	व्योम *end;
	काष्ठा ocfs2_xattr_entry *here;
	पूर्णांक not_found;
पूर्ण;

/* Operations on काष्ठा ocfs2_xa_entry */
काष्ठा ocfs2_xa_loc;
काष्ठा ocfs2_xa_loc_operations अणु
	/*
	 * Journal functions
	 */
	पूर्णांक (*xlo_journal_access)(handle_t *handle, काष्ठा ocfs2_xa_loc *loc,
				  पूर्णांक type);
	व्योम (*xlo_journal_dirty)(handle_t *handle, काष्ठा ocfs2_xa_loc *loc);

	/*
	 * Return a poपूर्णांकer to the appropriate buffer in loc->xl_storage
	 * at the given offset from loc->xl_header.
	 */
	व्योम *(*xlo_offset_poपूर्णांकer)(काष्ठा ocfs2_xa_loc *loc, पूर्णांक offset);

	/* Can we reuse the existing entry क्रम the new value? */
	पूर्णांक (*xlo_can_reuse)(काष्ठा ocfs2_xa_loc *loc,
			     काष्ठा ocfs2_xattr_info *xi);

	/* How much space is needed क्रम the new value? */
	पूर्णांक (*xlo_check_space)(काष्ठा ocfs2_xa_loc *loc,
			       काष्ठा ocfs2_xattr_info *xi);

	/*
	 * Return the offset of the first name+value pair.  This is
	 * the start of our करोwnward-filling मुक्त space.
	 */
	पूर्णांक (*xlo_get_मुक्त_start)(काष्ठा ocfs2_xa_loc *loc);

	/*
	 * Remove the name+value at this location.  Do whatever is
	 * appropriate with the reमुख्यing name+value pairs.
	 */
	व्योम (*xlo_wipe_namevalue)(काष्ठा ocfs2_xa_loc *loc);

	/* Fill xl_entry with a new entry */
	व्योम (*xlo_add_entry)(काष्ठा ocfs2_xa_loc *loc, u32 name_hash);

	/* Add name+value storage to an entry */
	व्योम (*xlo_add_namevalue)(काष्ठा ocfs2_xa_loc *loc, पूर्णांक size);

	/*
	 * Initialize the value buf's access and bh fields क्रम this entry.
	 * ocfs2_xa_fill_value_buf() will handle the xv poपूर्णांकer.
	 */
	व्योम (*xlo_fill_value_buf)(काष्ठा ocfs2_xa_loc *loc,
				   काष्ठा ocfs2_xattr_value_buf *vb);
पूर्ण;

/*
 * Describes an xattr entry location.  This is a memory काष्ठाure
 * tracking the on-disk काष्ठाure.
 */
काष्ठा ocfs2_xa_loc अणु
	/* This xattr beदीर्घs to this inode */
	काष्ठा inode *xl_inode;

	/* The ocfs2_xattr_header inside the on-disk storage. Not शून्य. */
	काष्ठा ocfs2_xattr_header *xl_header;

	/* Bytes from xl_header to the end of the storage */
	पूर्णांक xl_size;

	/*
	 * The ocfs2_xattr_entry this location describes.  If this is
	 * शून्य, this location describes the on-disk काष्ठाure where it
	 * would have been.
	 */
	काष्ठा ocfs2_xattr_entry *xl_entry;

	/*
	 * Internal housekeeping
	 */

	/* Buffer(s) containing this entry */
	व्योम *xl_storage;

	/* Operations on the storage backing this location */
	स्थिर काष्ठा ocfs2_xa_loc_operations *xl_ops;
पूर्ण;

/*
 * Convenience functions to calculate how much space is needed क्रम a
 * given name+value pair
 */
अटल पूर्णांक namevalue_size(पूर्णांक name_len, uपूर्णांक64_t value_len)
अणु
	अगर (value_len > OCFS2_XATTR_INLINE_SIZE)
		वापस OCFS2_XATTR_SIZE(name_len) + OCFS2_XATTR_ROOT_SIZE;
	अन्यथा
		वापस OCFS2_XATTR_SIZE(name_len) + OCFS2_XATTR_SIZE(value_len);
पूर्ण

अटल पूर्णांक namevalue_size_xi(काष्ठा ocfs2_xattr_info *xi)
अणु
	वापस namevalue_size(xi->xi_name_len, xi->xi_value_len);
पूर्ण

अटल पूर्णांक namevalue_size_xe(काष्ठा ocfs2_xattr_entry *xe)
अणु
	u64 value_len = le64_to_cpu(xe->xe_value_size);

	BUG_ON((value_len > OCFS2_XATTR_INLINE_SIZE) &&
	       ocfs2_xattr_is_local(xe));
	वापस namevalue_size(xe->xe_name_len, value_len);
पूर्ण


अटल पूर्णांक ocfs2_xattr_bucket_get_name_value(काष्ठा super_block *sb,
					     काष्ठा ocfs2_xattr_header *xh,
					     पूर्णांक index,
					     पूर्णांक *block_off,
					     पूर्णांक *new_offset);

अटल पूर्णांक ocfs2_xattr_block_find(काष्ठा inode *inode,
				  पूर्णांक name_index,
				  स्थिर अक्षर *name,
				  काष्ठा ocfs2_xattr_search *xs);
अटल पूर्णांक ocfs2_xattr_index_block_find(काष्ठा inode *inode,
					काष्ठा buffer_head *root_bh,
					पूर्णांक name_index,
					स्थिर अक्षर *name,
					काष्ठा ocfs2_xattr_search *xs);

अटल पूर्णांक ocfs2_xattr_tree_list_index_block(काष्ठा inode *inode,
					काष्ठा buffer_head *blk_bh,
					अक्षर *buffer,
					माप_प्रकार buffer_size);

अटल पूर्णांक ocfs2_xattr_create_index_block(काष्ठा inode *inode,
					  काष्ठा ocfs2_xattr_search *xs,
					  काष्ठा ocfs2_xattr_set_ctxt *ctxt);

अटल पूर्णांक ocfs2_xattr_set_entry_index_block(काष्ठा inode *inode,
					     काष्ठा ocfs2_xattr_info *xi,
					     काष्ठा ocfs2_xattr_search *xs,
					     काष्ठा ocfs2_xattr_set_ctxt *ctxt);

प्रकार पूर्णांक (xattr_tree_rec_func)(काष्ठा inode *inode,
				  काष्ठा buffer_head *root_bh,
				  u64 blkno, u32 cpos, u32 len, व्योम *para);
अटल पूर्णांक ocfs2_iterate_xattr_index_block(काष्ठा inode *inode,
					   काष्ठा buffer_head *root_bh,
					   xattr_tree_rec_func *rec_func,
					   व्योम *para);
अटल पूर्णांक ocfs2_delete_xattr_in_bucket(काष्ठा inode *inode,
					काष्ठा ocfs2_xattr_bucket *bucket,
					व्योम *para);
अटल पूर्णांक ocfs2_rm_xattr_cluster(काष्ठा inode *inode,
				  काष्ठा buffer_head *root_bh,
				  u64 blkno,
				  u32 cpos,
				  u32 len,
				  व्योम *para);

अटल पूर्णांक ocfs2_mv_xattr_buckets(काष्ठा inode *inode, handle_t *handle,
				  u64 src_blk, u64 last_blk, u64 to_blk,
				  अचिन्हित पूर्णांक start_bucket,
				  u32 *first_hash);
अटल पूर्णांक ocfs2_prepare_refcount_xattr(काष्ठा inode *inode,
					काष्ठा ocfs2_dinode *di,
					काष्ठा ocfs2_xattr_info *xi,
					काष्ठा ocfs2_xattr_search *xis,
					काष्ठा ocfs2_xattr_search *xbs,
					काष्ठा ocfs2_refcount_tree **ref_tree,
					पूर्णांक *meta_need,
					पूर्णांक *credits);
अटल पूर्णांक ocfs2_get_xattr_tree_value_root(काष्ठा super_block *sb,
					   काष्ठा ocfs2_xattr_bucket *bucket,
					   पूर्णांक offset,
					   काष्ठा ocfs2_xattr_value_root **xv,
					   काष्ठा buffer_head **bh);

अटल अंतरभूत u16 ocfs2_xattr_buckets_per_cluster(काष्ठा ocfs2_super *osb)
अणु
	वापस (1 << osb->s_clustersize_bits) / OCFS2_XATTR_BUCKET_SIZE;
पूर्ण

अटल अंतरभूत u16 ocfs2_blocks_per_xattr_bucket(काष्ठा super_block *sb)
अणु
	वापस OCFS2_XATTR_BUCKET_SIZE / (1 << sb->s_blocksize_bits);
पूर्ण

#घोषणा bucket_blkno(_b) ((_b)->bu_bhs[0]->b_blocknr)
#घोषणा bucket_block(_b, _n) ((_b)->bu_bhs[(_n)]->b_data)
#घोषणा bucket_xh(_b) ((काष्ठा ocfs2_xattr_header *)bucket_block((_b), 0))

अटल काष्ठा ocfs2_xattr_bucket *ocfs2_xattr_bucket_new(काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_xattr_bucket *bucket;
	पूर्णांक blks = ocfs2_blocks_per_xattr_bucket(inode->i_sb);

	BUG_ON(blks > OCFS2_XATTR_MAX_BLOCKS_PER_BUCKET);

	bucket = kzalloc(माप(काष्ठा ocfs2_xattr_bucket), GFP_NOFS);
	अगर (bucket) अणु
		bucket->bu_inode = inode;
		bucket->bu_blocks = blks;
	पूर्ण

	वापस bucket;
पूर्ण

अटल व्योम ocfs2_xattr_bucket_rअन्यथा(काष्ठा ocfs2_xattr_bucket *bucket)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bucket->bu_blocks; i++) अणु
		brअन्यथा(bucket->bu_bhs[i]);
		bucket->bu_bhs[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम ocfs2_xattr_bucket_मुक्त(काष्ठा ocfs2_xattr_bucket *bucket)
अणु
	अगर (bucket) अणु
		ocfs2_xattr_bucket_rअन्यथा(bucket);
		bucket->bu_inode = शून्य;
		kमुक्त(bucket);
	पूर्ण
पूर्ण

/*
 * A bucket that has never been written to disk करोesn't need to be
 * पढ़ो.  We just need the buffer_heads.  Don't call this क्रम
 * buckets that are alपढ़ोy on disk.  ocfs2_पढ़ो_xattr_bucket() initializes
 * them fully.
 */
अटल पूर्णांक ocfs2_init_xattr_bucket(काष्ठा ocfs2_xattr_bucket *bucket,
				   u64 xb_blkno, पूर्णांक new)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < bucket->bu_blocks; i++) अणु
		bucket->bu_bhs[i] = sb_getblk(bucket->bu_inode->i_sb,
					      xb_blkno + i);
		अगर (!bucket->bu_bhs[i]) अणु
			rc = -ENOMEM;
			mlog_त्रुटि_सं(rc);
			अवरोध;
		पूर्ण

		अगर (!ocfs2_buffer_uptodate(INODE_CACHE(bucket->bu_inode),
					   bucket->bu_bhs[i])) अणु
			अगर (new)
				ocfs2_set_new_buffer_uptodate(INODE_CACHE(bucket->bu_inode),
							      bucket->bu_bhs[i]);
			अन्यथा अणु
				set_buffer_uptodate(bucket->bu_bhs[i]);
				ocfs2_set_buffer_uptodate(INODE_CACHE(bucket->bu_inode),
							  bucket->bu_bhs[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rc)
		ocfs2_xattr_bucket_rअन्यथा(bucket);
	वापस rc;
पूर्ण

/* Read the xattr bucket at xb_blkno */
अटल पूर्णांक ocfs2_पढ़ो_xattr_bucket(काष्ठा ocfs2_xattr_bucket *bucket,
				   u64 xb_blkno)
अणु
	पूर्णांक rc;

	rc = ocfs2_पढ़ो_blocks(INODE_CACHE(bucket->bu_inode), xb_blkno,
			       bucket->bu_blocks, bucket->bu_bhs, 0,
			       शून्य);
	अगर (!rc) अणु
		spin_lock(&OCFS2_SB(bucket->bu_inode->i_sb)->osb_xattr_lock);
		rc = ocfs2_validate_meta_ecc_bhs(bucket->bu_inode->i_sb,
						 bucket->bu_bhs,
						 bucket->bu_blocks,
						 &bucket_xh(bucket)->xh_check);
		spin_unlock(&OCFS2_SB(bucket->bu_inode->i_sb)->osb_xattr_lock);
		अगर (rc)
			mlog_त्रुटि_सं(rc);
	पूर्ण

	अगर (rc)
		ocfs2_xattr_bucket_rअन्यथा(bucket);
	वापस rc;
पूर्ण

अटल पूर्णांक ocfs2_xattr_bucket_journal_access(handle_t *handle,
					     काष्ठा ocfs2_xattr_bucket *bucket,
					     पूर्णांक type)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < bucket->bu_blocks; i++) अणु
		rc = ocfs2_journal_access(handle,
					  INODE_CACHE(bucket->bu_inode),
					  bucket->bu_bhs[i], type);
		अगर (rc) अणु
			mlog_त्रुटि_सं(rc);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ocfs2_xattr_bucket_journal_dirty(handle_t *handle,
					     काष्ठा ocfs2_xattr_bucket *bucket)
अणु
	पूर्णांक i;

	spin_lock(&OCFS2_SB(bucket->bu_inode->i_sb)->osb_xattr_lock);
	ocfs2_compute_meta_ecc_bhs(bucket->bu_inode->i_sb,
				   bucket->bu_bhs, bucket->bu_blocks,
				   &bucket_xh(bucket)->xh_check);
	spin_unlock(&OCFS2_SB(bucket->bu_inode->i_sb)->osb_xattr_lock);

	क्रम (i = 0; i < bucket->bu_blocks; i++)
		ocfs2_journal_dirty(handle, bucket->bu_bhs[i]);
पूर्ण

अटल व्योम ocfs2_xattr_bucket_copy_data(काष्ठा ocfs2_xattr_bucket *dest,
					 काष्ठा ocfs2_xattr_bucket *src)
अणु
	पूर्णांक i;
	पूर्णांक blocksize = src->bu_inode->i_sb->s_blocksize;

	BUG_ON(dest->bu_blocks != src->bu_blocks);
	BUG_ON(dest->bu_inode != src->bu_inode);

	क्रम (i = 0; i < src->bu_blocks; i++) अणु
		स_नकल(bucket_block(dest, i), bucket_block(src, i),
		       blocksize);
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_validate_xattr_block(काष्ठा super_block *sb,
				      काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_xattr_block *xb =
		(काष्ठा ocfs2_xattr_block *)bh->b_data;

	trace_ocfs2_validate_xattr_block((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we वापस the error but otherwise
	 * leave the fileप्रणाली running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &xb->xb_check);
	अगर (rc)
		वापस rc;

	/*
	 * Errors after here are fatal
	 */

	अगर (!OCFS2_IS_VALID_XATTR_BLOCK(xb)) अणु
		वापस ocfs2_error(sb,
				   "Extended attribute block #%llu has bad signature %.*s\n",
				   (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, 7,
				   xb->xb_signature);
	पूर्ण

	अगर (le64_to_cpu(xb->xb_blkno) != bh->b_blocknr) अणु
		वापस ocfs2_error(sb,
				   "Extended attribute block #%llu has an invalid xb_blkno of %llu\n",
				   (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				   (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(xb->xb_blkno));
	पूर्ण

	अगर (le32_to_cpu(xb->xb_fs_generation) != OCFS2_SB(sb)->fs_generation) अणु
		वापस ocfs2_error(sb,
				   "Extended attribute block #%llu has an invalid xb_fs_generation of #%u\n",
				   (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				   le32_to_cpu(xb->xb_fs_generation));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_पढ़ो_xattr_block(काष्ठा inode *inode, u64 xb_blkno,
				  काष्ठा buffer_head **bh)
अणु
	पूर्णांक rc;
	काष्ठा buffer_head *पंचांगp = *bh;

	rc = ocfs2_पढ़ो_block(INODE_CACHE(inode), xb_blkno, &पंचांगp,
			      ocfs2_validate_xattr_block);

	/* If ocfs2_पढ़ो_block() got us a new bh, pass it up. */
	अगर (!rc && !*bh)
		*bh = पंचांगp;

	वापस rc;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *ocfs2_xattr_prefix(पूर्णांक name_index)
अणु
	स्थिर काष्ठा xattr_handler *handler = शून्य;

	अगर (name_index > 0 && name_index < OCFS2_XATTR_MAX)
		handler = ocfs2_xattr_handler_map[name_index];
	वापस handler ? xattr_prefix(handler) : शून्य;
पूर्ण

अटल u32 ocfs2_xattr_name_hash(काष्ठा inode *inode,
				 स्थिर अक्षर *name,
				 पूर्णांक name_len)
अणु
	/* Get hash value of uuid from super block */
	u32 hash = OCFS2_SB(inode->i_sb)->uuid_hash;
	पूर्णांक i;

	/* hash extended attribute name */
	क्रम (i = 0; i < name_len; i++) अणु
		hash = (hash << OCFS2_HASH_SHIFT) ^
		       (hash >> (8*माप(hash) - OCFS2_HASH_SHIFT)) ^
		       *name++;
	पूर्ण

	वापस hash;
पूर्ण

अटल पूर्णांक ocfs2_xattr_entry_real_size(पूर्णांक name_len, माप_प्रकार value_len)
अणु
	वापस namevalue_size(name_len, value_len) +
		माप(काष्ठा ocfs2_xattr_entry);
पूर्ण

अटल पूर्णांक ocfs2_xi_entry_usage(काष्ठा ocfs2_xattr_info *xi)
अणु
	वापस namevalue_size_xi(xi) +
		माप(काष्ठा ocfs2_xattr_entry);
पूर्ण

अटल पूर्णांक ocfs2_xe_entry_usage(काष्ठा ocfs2_xattr_entry *xe)
अणु
	वापस namevalue_size_xe(xe) +
		माप(काष्ठा ocfs2_xattr_entry);
पूर्ण

पूर्णांक ocfs2_calc_security_init(काष्ठा inode *dir,
			     काष्ठा ocfs2_security_xattr_info *si,
			     पूर्णांक *want_clusters,
			     पूर्णांक *xattr_credits,
			     काष्ठा ocfs2_alloc_context **xattr_ac)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	पूर्णांक s_size = ocfs2_xattr_entry_real_size(म_माप(si->name),
						 si->value_len);

	/*
	 * The max space of security xattr taken अंतरभूत is
	 * 256(name) + 80(value) + 16(entry) = 352 bytes,
	 * So reserve one metadata block क्रम it is ok.
	 */
	अगर (dir->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE ||
	    s_size > OCFS2_XATTR_FREE_IN_IBODY) अणु
		ret = ocfs2_reserve_new_metadata_blocks(osb, 1, xattr_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण
		*xattr_credits += OCFS2_XATTR_BLOCK_CREATE_CREDITS;
	पूर्ण

	/* reserve clusters क्रम xattr value which will be set in B tree*/
	अगर (si->value_len > OCFS2_XATTR_INLINE_SIZE) अणु
		पूर्णांक new_clusters = ocfs2_clusters_क्रम_bytes(dir->i_sb,
							    si->value_len);

		*xattr_credits += ocfs2_clusters_to_blocks(dir->i_sb,
							   new_clusters);
		*want_clusters += new_clusters;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ocfs2_calc_xattr_init(काष्ठा inode *dir,
			  काष्ठा buffer_head *dir_bh,
			  umode_t mode,
			  काष्ठा ocfs2_security_xattr_info *si,
			  पूर्णांक *want_clusters,
			  पूर्णांक *xattr_credits,
			  पूर्णांक *want_meta)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	पूर्णांक s_size = 0, a_size = 0, acl_len = 0, new_clusters;

	अगर (si->enable)
		s_size = ocfs2_xattr_entry_real_size(म_माप(si->name),
						     si->value_len);

	अगर (osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL) अणु
		करोwn_पढ़ो(&OCFS2_I(dir)->ip_xattr_sem);
		acl_len = ocfs2_xattr_get_nolock(dir, dir_bh,
					OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT,
					"", शून्य, 0);
		up_पढ़ो(&OCFS2_I(dir)->ip_xattr_sem);
		अगर (acl_len > 0) अणु
			a_size = ocfs2_xattr_entry_real_size(0, acl_len);
			अगर (S_ISसूची(mode))
				a_size <<= 1;
		पूर्ण अन्यथा अगर (acl_len != 0 && acl_len != -ENODATA) अणु
			ret = acl_len;
			mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!(s_size + a_size))
		वापस ret;

	/*
	 * The max space of security xattr taken अंतरभूत is
	 * 256(name) + 80(value) + 16(entry) = 352 bytes,
	 * The max space of acl xattr taken अंतरभूत is
	 * 80(value) + 16(entry) * 2(अगर directory) = 192 bytes,
	 * when blocksize = 512, may reserve one more cluser क्रम
	 * xattr bucket, otherwise reserve one metadata block
	 * क्रम them is ok.
	 * If this is a new directory with अंतरभूत data,
	 * we choose to reserve the entire अंतरभूत area क्रम
	 * directory contents and क्रमce an बाह्यal xattr block.
	 */
	अगर (dir->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE ||
	    (S_ISसूची(mode) && ocfs2_supports_अंतरभूत_data(osb)) ||
	    (s_size + a_size) > OCFS2_XATTR_FREE_IN_IBODY) अणु
		*want_meta = *want_meta + 1;
		*xattr_credits += OCFS2_XATTR_BLOCK_CREATE_CREDITS;
	पूर्ण

	अगर (dir->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE &&
	    (s_size + a_size) > OCFS2_XATTR_FREE_IN_BLOCK(dir)) अणु
		*want_clusters += 1;
		*xattr_credits += ocfs2_blocks_per_xattr_bucket(dir->i_sb);
	पूर्ण

	/*
	 * reserve credits and clusters क्रम xattrs which has large value
	 * and have to be set outside
	 */
	अगर (si->enable && si->value_len > OCFS2_XATTR_INLINE_SIZE) अणु
		new_clusters = ocfs2_clusters_क्रम_bytes(dir->i_sb,
							si->value_len);
		*xattr_credits += ocfs2_clusters_to_blocks(dir->i_sb,
							   new_clusters);
		*want_clusters += new_clusters;
	पूर्ण
	अगर (osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL &&
	    acl_len > OCFS2_XATTR_INLINE_SIZE) अणु
		/* क्रम directory, it has DEFAULT and ACCESS two types of acls */
		new_clusters = (S_ISसूची(mode) ? 2 : 1) *
				ocfs2_clusters_क्रम_bytes(dir->i_sb, acl_len);
		*xattr_credits += ocfs2_clusters_to_blocks(dir->i_sb,
							   new_clusters);
		*want_clusters += new_clusters;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_extend_allocation(काष्ठा inode *inode,
					 u32 clusters_to_add,
					 काष्ठा ocfs2_xattr_value_buf *vb,
					 काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक status = 0, credits;
	handle_t *handle = ctxt->handle;
	क्रमागत ocfs2_alloc_restarted why;
	u32 prev_clusters, logical_start = le32_to_cpu(vb->vb_xv->xr_clusters);
	काष्ठा ocfs2_extent_tree et;

	ocfs2_init_xattr_value_extent_tree(&et, INODE_CACHE(inode), vb);

	जबतक (clusters_to_add) अणु
		trace_ocfs2_xattr_extend_allocation(clusters_to_add);

		status = vb->vb_access(handle, INODE_CACHE(inode), vb->vb_bh,
				       OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			अवरोध;
		पूर्ण

		prev_clusters = le32_to_cpu(vb->vb_xv->xr_clusters);
		status = ocfs2_add_clusters_in_btree(handle,
						     &et,
						     &logical_start,
						     clusters_to_add,
						     0,
						     ctxt->data_ac,
						     ctxt->meta_ac,
						     &why);
		अगर ((status < 0) && (status != -EAGAIN)) अणु
			अगर (status != -ENOSPC)
				mlog_त्रुटि_सं(status);
			अवरोध;
		पूर्ण

		ocfs2_journal_dirty(handle, vb->vb_bh);

		clusters_to_add -= le32_to_cpu(vb->vb_xv->xr_clusters) -
					 prev_clusters;

		अगर (why != RESTART_NONE && clusters_to_add) अणु
			/*
			 * We can only fail in हाल the alloc file करोesn't give
			 * up enough clusters.
			 */
			BUG_ON(why == RESTART_META);

			credits = ocfs2_calc_extend_credits(inode->i_sb,
							    &vb->vb_xv->xr_list);
			status = ocfs2_extend_trans(handle, credits);
			अगर (status < 0) अणु
				status = -ENOMEM;
				mlog_त्रुटि_सं(status);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक __ocfs2_हटाओ_xattr_range(काष्ठा inode *inode,
				      काष्ठा ocfs2_xattr_value_buf *vb,
				      u32 cpos, u32 phys_cpos, u32 len,
				      अचिन्हित पूर्णांक ext_flags,
				      काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;
	u64 phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, phys_cpos);
	handle_t *handle = ctxt->handle;
	काष्ठा ocfs2_extent_tree et;

	ocfs2_init_xattr_value_extent_tree(&et, INODE_CACHE(inode), vb);

	ret = vb->vb_access(handle, INODE_CACHE(inode), vb->vb_bh,
			    OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_हटाओ_extent(handle, &et, cpos, len, ctxt->meta_ac,
				  &ctxt->dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	le32_add_cpu(&vb->vb_xv->xr_clusters, -len);
	ocfs2_journal_dirty(handle, vb->vb_bh);

	अगर (ext_flags & OCFS2_EXT_REFCOUNTED)
		ret = ocfs2_decrease_refcount(inode, handle,
					ocfs2_blocks_to_clusters(inode->i_sb,
								 phys_blkno),
					len, ctxt->meta_ac, &ctxt->dealloc, 1);
	अन्यथा
		ret = ocfs2_cache_cluster_dealloc(&ctxt->dealloc,
						  phys_blkno, len);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_shrink_size(काष्ठा inode *inode,
				   u32 old_clusters,
				   u32 new_clusters,
				   काष्ठा ocfs2_xattr_value_buf *vb,
				   काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक ext_flags;
	u32 trunc_len, cpos, phys_cpos, alloc_size;
	u64 block;

	अगर (old_clusters <= new_clusters)
		वापस 0;

	cpos = new_clusters;
	trunc_len = old_clusters - new_clusters;
	जबतक (trunc_len) अणु
		ret = ocfs2_xattr_get_clusters(inode, cpos, &phys_cpos,
					       &alloc_size,
					       &vb->vb_xv->xr_list, &ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (alloc_size > trunc_len)
			alloc_size = trunc_len;

		ret = __ocfs2_हटाओ_xattr_range(inode, vb, cpos,
						 phys_cpos, alloc_size,
						 ext_flags, ctxt);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		block = ocfs2_clusters_to_blocks(inode->i_sb, phys_cpos);
		ocfs2_हटाओ_xattr_clusters_from_cache(INODE_CACHE(inode),
						       block, alloc_size);
		cpos += alloc_size;
		trunc_len -= alloc_size;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_value_truncate(काष्ठा inode *inode,
				      काष्ठा ocfs2_xattr_value_buf *vb,
				      पूर्णांक len,
				      काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;
	u32 new_clusters = ocfs2_clusters_क्रम_bytes(inode->i_sb, len);
	u32 old_clusters = le32_to_cpu(vb->vb_xv->xr_clusters);

	अगर (new_clusters == old_clusters)
		वापस 0;

	अगर (new_clusters > old_clusters)
		ret = ocfs2_xattr_extend_allocation(inode,
						    new_clusters - old_clusters,
						    vb, ctxt);
	अन्यथा
		ret = ocfs2_xattr_shrink_size(inode,
					      old_clusters, new_clusters,
					      vb, ctxt);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_list_entry(काष्ठा super_block *sb,
				  अक्षर *buffer, माप_प्रकार size,
				  माप_प्रकार *result, पूर्णांक type,
				  स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	अक्षर *p = buffer + *result;
	स्थिर अक्षर *prefix;
	पूर्णांक prefix_len;
	पूर्णांक total_len;

	चयन(type) अणु
	हाल OCFS2_XATTR_INDEX_USER:
		अगर (OCFS2_SB(sb)->s_mount_opt & OCFS2_MOUNT_NOUSERXATTR)
			वापस 0;
		अवरोध;

	हाल OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS:
	हाल OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT:
		अगर (!(sb->s_flags & SB_POSIXACL))
			वापस 0;
		अवरोध;

	हाल OCFS2_XATTR_INDEX_TRUSTED:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस 0;
		अवरोध;
	पूर्ण

	prefix = ocfs2_xattr_prefix(type);
	अगर (!prefix)
		वापस 0;
	prefix_len = म_माप(prefix);
	total_len = prefix_len + name_len + 1;
	*result += total_len;

	/* we are just looking क्रम how big our buffer needs to be */
	अगर (!size)
		वापस 0;

	अगर (*result > size)
		वापस -दुस्फल;

	स_नकल(p, prefix, prefix_len);
	स_नकल(p + prefix_len, name, name_len);
	p[prefix_len + name_len] = '\0';

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_xattr_list_entries(काष्ठा inode *inode,
				    काष्ठा ocfs2_xattr_header *header,
				    अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	माप_प्रकार result = 0;
	पूर्णांक i, type, ret;
	स्थिर अक्षर *name;

	क्रम (i = 0 ; i < le16_to_cpu(header->xh_count); i++) अणु
		काष्ठा ocfs2_xattr_entry *entry = &header->xh_entries[i];
		type = ocfs2_xattr_get_type(entry);
		name = (स्थिर अक्षर *)header +
			le16_to_cpu(entry->xe_name_offset);

		ret = ocfs2_xattr_list_entry(inode->i_sb,
					     buffer, buffer_size,
					     &result, type, name,
					     entry->xe_name_len);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक ocfs2_has_अंतरभूत_xattr_value_outside(काष्ठा inode *inode,
					 काष्ठा ocfs2_dinode *di)
अणु
	काष्ठा ocfs2_xattr_header *xh;
	पूर्णांक i;

	xh = (काष्ठा ocfs2_xattr_header *)
		 ((व्योम *)di + inode->i_sb->s_blocksize -
		 le16_to_cpu(di->i_xattr_अंतरभूत_size));

	क्रम (i = 0; i < le16_to_cpu(xh->xh_count); i++)
		अगर (!ocfs2_xattr_is_local(&xh->xh_entries[i]))
			वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_xattr_ibody_list(काष्ठा inode *inode,
				  काष्ठा ocfs2_dinode *di,
				  अक्षर *buffer,
				  माप_प्रकार buffer_size)
अणु
	काष्ठा ocfs2_xattr_header *header = शून्य;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	पूर्णांक ret = 0;

	अगर (!(oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL))
		वापस ret;

	header = (काष्ठा ocfs2_xattr_header *)
		 ((व्योम *)di + inode->i_sb->s_blocksize -
		 le16_to_cpu(di->i_xattr_अंतरभूत_size));

	ret = ocfs2_xattr_list_entries(inode, header, buffer, buffer_size);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_block_list(काष्ठा inode *inode,
				  काष्ठा ocfs2_dinode *di,
				  अक्षर *buffer,
				  माप_प्रकार buffer_size)
अणु
	काष्ठा buffer_head *blk_bh = शून्य;
	काष्ठा ocfs2_xattr_block *xb;
	पूर्णांक ret = 0;

	अगर (!di->i_xattr_loc)
		वापस ret;

	ret = ocfs2_पढ़ो_xattr_block(inode, le64_to_cpu(di->i_xattr_loc),
				     &blk_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	xb = (काष्ठा ocfs2_xattr_block *)blk_bh->b_data;
	अगर (!(le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED)) अणु
		काष्ठा ocfs2_xattr_header *header = &xb->xb_attrs.xb_header;
		ret = ocfs2_xattr_list_entries(inode, header,
					       buffer, buffer_size);
	पूर्ण अन्यथा
		ret = ocfs2_xattr_tree_list_index_block(inode, blk_bh,
						   buffer, buffer_size);

	brअन्यथा(blk_bh);

	वापस ret;
पूर्ण

sमाप_प्रकार ocfs2_listxattr(काष्ठा dentry *dentry,
			अक्षर *buffer,
			माप_प्रकार size)
अणु
	पूर्णांक ret = 0, i_ret = 0, b_ret = 0;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di = शून्य;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(d_inode(dentry));

	अगर (!ocfs2_supports_xattr(OCFS2_SB(dentry->d_sb)))
		वापस -EOPNOTSUPP;

	अगर (!(oi->ip_dyn_features & OCFS2_HAS_XATTR_FL))
		वापस ret;

	ret = ocfs2_inode_lock(d_inode(dentry), &di_bh, 0);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	करोwn_पढ़ो(&oi->ip_xattr_sem);
	i_ret = ocfs2_xattr_ibody_list(d_inode(dentry), di, buffer, size);
	अगर (i_ret < 0)
		b_ret = 0;
	अन्यथा अणु
		अगर (buffer) अणु
			buffer += i_ret;
			size -= i_ret;
		पूर्ण
		b_ret = ocfs2_xattr_block_list(d_inode(dentry), di,
					       buffer, size);
		अगर (b_ret < 0)
			i_ret = 0;
	पूर्ण
	up_पढ़ो(&oi->ip_xattr_sem);
	ocfs2_inode_unlock(d_inode(dentry), 0);

	brअन्यथा(di_bh);

	वापस i_ret + b_ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_find_entry(पूर्णांक name_index,
				  स्थिर अक्षर *name,
				  काष्ठा ocfs2_xattr_search *xs)
अणु
	काष्ठा ocfs2_xattr_entry *entry;
	माप_प्रकार name_len;
	पूर्णांक i, cmp = 1;

	अगर (name == शून्य)
		वापस -EINVAL;

	name_len = म_माप(name);
	entry = xs->here;
	क्रम (i = 0; i < le16_to_cpu(xs->header->xh_count); i++) अणु
		cmp = name_index - ocfs2_xattr_get_type(entry);
		अगर (!cmp)
			cmp = name_len - entry->xe_name_len;
		अगर (!cmp)
			cmp = स_भेद(name, (xs->base +
				     le16_to_cpu(entry->xe_name_offset)),
				     name_len);
		अगर (cmp == 0)
			अवरोध;
		entry += 1;
	पूर्ण
	xs->here = entry;

	वापस cmp ? -ENODATA : 0;
पूर्ण

अटल पूर्णांक ocfs2_xattr_get_value_outside(काष्ठा inode *inode,
					 काष्ठा ocfs2_xattr_value_root *xv,
					 व्योम *buffer,
					 माप_प्रकार len)
अणु
	u32 cpos, p_cluster, num_clusters, bpc, clusters;
	u64 blkno;
	पूर्णांक i, ret = 0;
	माप_प्रकार cplen, blocksize;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_extent_list *el;

	el = &xv->xr_list;
	clusters = le32_to_cpu(xv->xr_clusters);
	bpc = ocfs2_clusters_to_blocks(inode->i_sb, 1);
	blocksize = inode->i_sb->s_blocksize;

	cpos = 0;
	जबतक (cpos < clusters) अणु
		ret = ocfs2_xattr_get_clusters(inode, cpos, &p_cluster,
					       &num_clusters, el, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		blkno = ocfs2_clusters_to_blocks(inode->i_sb, p_cluster);
		/* Copy ocfs2_xattr_value */
		क्रम (i = 0; i < num_clusters * bpc; i++, blkno++) अणु
			ret = ocfs2_पढ़ो_block(INODE_CACHE(inode), blkno,
					       &bh, शून्य);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			cplen = len >= blocksize ? blocksize : len;
			स_नकल(buffer, bh->b_data, cplen);
			len -= cplen;
			buffer += cplen;

			brअन्यथा(bh);
			bh = शून्य;
			अगर (len == 0)
				अवरोध;
		पूर्ण
		cpos += num_clusters;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_ibody_get(काष्ठा inode *inode,
				 पूर्णांक name_index,
				 स्थिर अक्षर *name,
				 व्योम *buffer,
				 माप_प्रकार buffer_size,
				 काष्ठा ocfs2_xattr_search *xs)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)xs->inode_bh->b_data;
	काष्ठा ocfs2_xattr_value_root *xv;
	माप_प्रकार size;
	पूर्णांक ret = 0;

	अगर (!(oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL))
		वापस -ENODATA;

	xs->end = (व्योम *)di + inode->i_sb->s_blocksize;
	xs->header = (काष्ठा ocfs2_xattr_header *)
			(xs->end - le16_to_cpu(di->i_xattr_अंतरभूत_size));
	xs->base = (व्योम *)xs->header;
	xs->here = xs->header->xh_entries;

	ret = ocfs2_xattr_find_entry(name_index, name, xs);
	अगर (ret)
		वापस ret;
	size = le64_to_cpu(xs->here->xe_value_size);
	अगर (buffer) अणु
		अगर (size > buffer_size)
			वापस -दुस्फल;
		अगर (ocfs2_xattr_is_local(xs->here)) अणु
			स_नकल(buffer, (व्योम *)xs->base +
			       le16_to_cpu(xs->here->xe_name_offset) +
			       OCFS2_XATTR_SIZE(xs->here->xe_name_len), size);
		पूर्ण अन्यथा अणु
			xv = (काष्ठा ocfs2_xattr_value_root *)
				(xs->base + le16_to_cpu(
				 xs->here->xe_name_offset) +
				OCFS2_XATTR_SIZE(xs->here->xe_name_len));
			ret = ocfs2_xattr_get_value_outside(inode, xv,
							    buffer, size);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक ocfs2_xattr_block_get(काष्ठा inode *inode,
				 पूर्णांक name_index,
				 स्थिर अक्षर *name,
				 व्योम *buffer,
				 माप_प्रकार buffer_size,
				 काष्ठा ocfs2_xattr_search *xs)
अणु
	काष्ठा ocfs2_xattr_block *xb;
	काष्ठा ocfs2_xattr_value_root *xv;
	माप_प्रकार size;
	पूर्णांक ret = -ENODATA, name_offset, name_len, i;
	पूर्णांक block_off;

	xs->bucket = ocfs2_xattr_bucket_new(inode);
	अगर (!xs->bucket) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ cleanup;
	पूर्ण

	ret = ocfs2_xattr_block_find(inode, name_index, name, xs);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ cleanup;
	पूर्ण

	अगर (xs->not_found) अणु
		ret = -ENODATA;
		जाओ cleanup;
	पूर्ण

	xb = (काष्ठा ocfs2_xattr_block *)xs->xattr_bh->b_data;
	size = le64_to_cpu(xs->here->xe_value_size);
	अगर (buffer) अणु
		ret = -दुस्फल;
		अगर (size > buffer_size)
			जाओ cleanup;

		name_offset = le16_to_cpu(xs->here->xe_name_offset);
		name_len = OCFS2_XATTR_SIZE(xs->here->xe_name_len);
		i = xs->here - xs->header->xh_entries;

		अगर (le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED) अणु
			ret = ocfs2_xattr_bucket_get_name_value(inode->i_sb,
								bucket_xh(xs->bucket),
								i,
								&block_off,
								&name_offset);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ cleanup;
			पूर्ण
			xs->base = bucket_block(xs->bucket, block_off);
		पूर्ण
		अगर (ocfs2_xattr_is_local(xs->here)) अणु
			स_नकल(buffer, (व्योम *)xs->base +
			       name_offset + name_len, size);
		पूर्ण अन्यथा अणु
			xv = (काष्ठा ocfs2_xattr_value_root *)
				(xs->base + name_offset + name_len);
			ret = ocfs2_xattr_get_value_outside(inode, xv,
							    buffer, size);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				जाओ cleanup;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = size;
cleanup:
	ocfs2_xattr_bucket_मुक्त(xs->bucket);

	brअन्यथा(xs->xattr_bh);
	xs->xattr_bh = शून्य;
	वापस ret;
पूर्ण

पूर्णांक ocfs2_xattr_get_nolock(काष्ठा inode *inode,
			   काष्ठा buffer_head *di_bh,
			   पूर्णांक name_index,
			   स्थिर अक्षर *name,
			   व्योम *buffer,
			   माप_प्रकार buffer_size)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_dinode *di = शून्य;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_xattr_search xis = अणु
		.not_found = -ENODATA,
	पूर्ण;
	काष्ठा ocfs2_xattr_search xbs = अणु
		.not_found = -ENODATA,
	पूर्ण;

	अगर (!ocfs2_supports_xattr(OCFS2_SB(inode->i_sb)))
		वापस -EOPNOTSUPP;

	अगर (!(oi->ip_dyn_features & OCFS2_HAS_XATTR_FL))
		वापस -ENODATA;

	xis.inode_bh = xbs.inode_bh = di_bh;
	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	ret = ocfs2_xattr_ibody_get(inode, name_index, name, buffer,
				    buffer_size, &xis);
	अगर (ret == -ENODATA && di->i_xattr_loc)
		ret = ocfs2_xattr_block_get(inode, name_index, name, buffer,
					    buffer_size, &xbs);

	वापस ret;
पूर्ण

/* ocfs2_xattr_get()
 *
 * Copy an extended attribute पूर्णांकo the buffer provided.
 * Buffer is शून्य to compute the size of buffer required.
 */
अटल पूर्णांक ocfs2_xattr_get(काष्ठा inode *inode,
			   पूर्णांक name_index,
			   स्थिर अक्षर *name,
			   व्योम *buffer,
			   माप_प्रकार buffer_size)
अणु
	पूर्णांक ret, had_lock;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_lock_holder oh;

	had_lock = ocfs2_inode_lock_tracker(inode, &di_bh, 0, &oh);
	अगर (had_lock < 0) अणु
		mlog_त्रुटि_सं(had_lock);
		वापस had_lock;
	पूर्ण
	करोwn_पढ़ो(&OCFS2_I(inode)->ip_xattr_sem);
	ret = ocfs2_xattr_get_nolock(inode, di_bh, name_index,
				     name, buffer, buffer_size);
	up_पढ़ो(&OCFS2_I(inode)->ip_xattr_sem);

	ocfs2_inode_unlock_tracker(inode, 0, &oh, had_lock);

	brअन्यथा(di_bh);

	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_xattr_set_value_outside(काष्ठा inode *inode,
					   handle_t *handle,
					   काष्ठा ocfs2_xattr_value_buf *vb,
					   स्थिर व्योम *value,
					   पूर्णांक value_len)
अणु
	पूर्णांक ret = 0, i, cp_len;
	u16 blocksize = inode->i_sb->s_blocksize;
	u32 p_cluster, num_clusters;
	u32 cpos = 0, bpc = ocfs2_clusters_to_blocks(inode->i_sb, 1);
	u32 clusters = ocfs2_clusters_क्रम_bytes(inode->i_sb, value_len);
	u64 blkno;
	काष्ठा buffer_head *bh = शून्य;
	अचिन्हित पूर्णांक ext_flags;
	काष्ठा ocfs2_xattr_value_root *xv = vb->vb_xv;

	BUG_ON(clusters > le32_to_cpu(xv->xr_clusters));

	जबतक (cpos < clusters) अणु
		ret = ocfs2_xattr_get_clusters(inode, cpos, &p_cluster,
					       &num_clusters, &xv->xr_list,
					       &ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		BUG_ON(ext_flags & OCFS2_EXT_REFCOUNTED);

		blkno = ocfs2_clusters_to_blocks(inode->i_sb, p_cluster);

		क्रम (i = 0; i < num_clusters * bpc; i++, blkno++) अणु
			ret = ocfs2_पढ़ो_block(INODE_CACHE(inode), blkno,
					       &bh, शून्य);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			ret = ocfs2_journal_access(handle,
						   INODE_CACHE(inode),
						   bh,
						   OCFS2_JOURNAL_ACCESS_WRITE);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			cp_len = value_len > blocksize ? blocksize : value_len;
			स_नकल(bh->b_data, value, cp_len);
			value_len -= cp_len;
			value += cp_len;
			अगर (cp_len < blocksize)
				स_रखो(bh->b_data + cp_len, 0,
				       blocksize - cp_len);

			ocfs2_journal_dirty(handle, bh);
			brअन्यथा(bh);
			bh = शून्य;

			/*
			 * XXX: करो we need to empty all the following
			 * blocks in this cluster?
			 */
			अगर (!value_len)
				अवरोध;
		पूर्ण
		cpos += num_clusters;
	पूर्ण
out:
	brअन्यथा(bh);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xa_check_space_helper(पूर्णांक needed_space, पूर्णांक मुक्त_start,
				       पूर्णांक num_entries)
अणु
	पूर्णांक मुक्त_space;

	अगर (!needed_space)
		वापस 0;

	मुक्त_space = मुक्त_start -
		माप(काष्ठा ocfs2_xattr_header) -
		(num_entries * माप(काष्ठा ocfs2_xattr_entry)) -
		OCFS2_XATTR_HEADER_GAP;
	अगर (मुक्त_space < 0)
		वापस -EIO;
	अगर (मुक्त_space < needed_space)
		वापस -ENOSPC;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_xa_journal_access(handle_t *handle, काष्ठा ocfs2_xa_loc *loc,
				   पूर्णांक type)
अणु
	वापस loc->xl_ops->xlo_journal_access(handle, loc, type);
पूर्ण

अटल व्योम ocfs2_xa_journal_dirty(handle_t *handle, काष्ठा ocfs2_xa_loc *loc)
अणु
	loc->xl_ops->xlo_journal_dirty(handle, loc);
पूर्ण

/* Give a poपूर्णांकer पूर्णांकo the storage क्रम the given offset */
अटल व्योम *ocfs2_xa_offset_poपूर्णांकer(काष्ठा ocfs2_xa_loc *loc, पूर्णांक offset)
अणु
	BUG_ON(offset >= loc->xl_size);
	वापस loc->xl_ops->xlo_offset_poपूर्णांकer(loc, offset);
पूर्ण

/*
 * Wipe the name+value pair and allow the storage to reclaim it.  This
 * must be followed by either removal of the entry or a call to
 * ocfs2_xa_add_namevalue().
 */
अटल व्योम ocfs2_xa_wipe_namevalue(काष्ठा ocfs2_xa_loc *loc)
अणु
	loc->xl_ops->xlo_wipe_namevalue(loc);
पूर्ण

/*
 * Find lowest offset to a name+value pair.  This is the start of our
 * करोwnward-growing मुक्त space.
 */
अटल पूर्णांक ocfs2_xa_get_मुक्त_start(काष्ठा ocfs2_xa_loc *loc)
अणु
	वापस loc->xl_ops->xlo_get_मुक्त_start(loc);
पूर्ण

/* Can we reuse loc->xl_entry क्रम xi? */
अटल पूर्णांक ocfs2_xa_can_reuse_entry(काष्ठा ocfs2_xa_loc *loc,
				    काष्ठा ocfs2_xattr_info *xi)
अणु
	वापस loc->xl_ops->xlo_can_reuse(loc, xi);
पूर्ण

/* How much मुक्त space is needed to set the new value */
अटल पूर्णांक ocfs2_xa_check_space(काष्ठा ocfs2_xa_loc *loc,
				काष्ठा ocfs2_xattr_info *xi)
अणु
	वापस loc->xl_ops->xlo_check_space(loc, xi);
पूर्ण

अटल व्योम ocfs2_xa_add_entry(काष्ठा ocfs2_xa_loc *loc, u32 name_hash)
अणु
	loc->xl_ops->xlo_add_entry(loc, name_hash);
	loc->xl_entry->xe_name_hash = cpu_to_le32(name_hash);
	/*
	 * We can't leave the new entry's xe_name_offset at zero or
	 * add_namevalue() will go nuts.  We set it to the size of our
	 * storage so that it can never be less than any other entry.
	 */
	loc->xl_entry->xe_name_offset = cpu_to_le16(loc->xl_size);
पूर्ण

अटल व्योम ocfs2_xa_add_namevalue(काष्ठा ocfs2_xa_loc *loc,
				   काष्ठा ocfs2_xattr_info *xi)
अणु
	पूर्णांक size = namevalue_size_xi(xi);
	पूर्णांक nameval_offset;
	अक्षर *nameval_buf;

	loc->xl_ops->xlo_add_namevalue(loc, size);
	loc->xl_entry->xe_value_size = cpu_to_le64(xi->xi_value_len);
	loc->xl_entry->xe_name_len = xi->xi_name_len;
	ocfs2_xattr_set_type(loc->xl_entry, xi->xi_name_index);
	ocfs2_xattr_set_local(loc->xl_entry,
			      xi->xi_value_len <= OCFS2_XATTR_INLINE_SIZE);

	nameval_offset = le16_to_cpu(loc->xl_entry->xe_name_offset);
	nameval_buf = ocfs2_xa_offset_poपूर्णांकer(loc, nameval_offset);
	स_रखो(nameval_buf, 0, size);
	स_नकल(nameval_buf, xi->xi_name, xi->xi_name_len);
पूर्ण

अटल व्योम ocfs2_xa_fill_value_buf(काष्ठा ocfs2_xa_loc *loc,
				    काष्ठा ocfs2_xattr_value_buf *vb)
अणु
	पूर्णांक nameval_offset = le16_to_cpu(loc->xl_entry->xe_name_offset);
	पूर्णांक name_size = OCFS2_XATTR_SIZE(loc->xl_entry->xe_name_len);

	/* Value bufs are क्रम value trees */
	BUG_ON(ocfs2_xattr_is_local(loc->xl_entry));
	BUG_ON(namevalue_size_xe(loc->xl_entry) !=
	       (name_size + OCFS2_XATTR_ROOT_SIZE));

	loc->xl_ops->xlo_fill_value_buf(loc, vb);
	vb->vb_xv =
		(काष्ठा ocfs2_xattr_value_root *)ocfs2_xa_offset_poपूर्णांकer(loc,
							nameval_offset +
							name_size);
पूर्ण

अटल पूर्णांक ocfs2_xa_block_journal_access(handle_t *handle,
					 काष्ठा ocfs2_xa_loc *loc, पूर्णांक type)
अणु
	काष्ठा buffer_head *bh = loc->xl_storage;
	ocfs2_journal_access_func access;

	अगर (loc->xl_size == (bh->b_size -
			     दुरत्व(काष्ठा ocfs2_xattr_block,
				      xb_attrs.xb_header)))
		access = ocfs2_journal_access_xb;
	अन्यथा
		access = ocfs2_journal_access_di;
	वापस access(handle, INODE_CACHE(loc->xl_inode), bh, type);
पूर्ण

अटल व्योम ocfs2_xa_block_journal_dirty(handle_t *handle,
					 काष्ठा ocfs2_xa_loc *loc)
अणु
	काष्ठा buffer_head *bh = loc->xl_storage;

	ocfs2_journal_dirty(handle, bh);
पूर्ण

अटल व्योम *ocfs2_xa_block_offset_poपूर्णांकer(काष्ठा ocfs2_xa_loc *loc,
					   पूर्णांक offset)
अणु
	वापस (अक्षर *)loc->xl_header + offset;
पूर्ण

अटल पूर्णांक ocfs2_xa_block_can_reuse(काष्ठा ocfs2_xa_loc *loc,
				    काष्ठा ocfs2_xattr_info *xi)
अणु
	/*
	 * Block storage is strict.  If the sizes aren't exact, we will
	 * हटाओ the old one and reinsert the new.
	 */
	वापस namevalue_size_xe(loc->xl_entry) ==
		namevalue_size_xi(xi);
पूर्ण

अटल पूर्णांक ocfs2_xa_block_get_मुक्त_start(काष्ठा ocfs2_xa_loc *loc)
अणु
	काष्ठा ocfs2_xattr_header *xh = loc->xl_header;
	पूर्णांक i, count = le16_to_cpu(xh->xh_count);
	पूर्णांक offset, मुक्त_start = loc->xl_size;

	क्रम (i = 0; i < count; i++) अणु
		offset = le16_to_cpu(xh->xh_entries[i].xe_name_offset);
		अगर (offset < मुक्त_start)
			मुक्त_start = offset;
	पूर्ण

	वापस मुक्त_start;
पूर्ण

अटल पूर्णांक ocfs2_xa_block_check_space(काष्ठा ocfs2_xa_loc *loc,
				      काष्ठा ocfs2_xattr_info *xi)
अणु
	पूर्णांक count = le16_to_cpu(loc->xl_header->xh_count);
	पूर्णांक मुक्त_start = ocfs2_xa_get_मुक्त_start(loc);
	पूर्णांक needed_space = ocfs2_xi_entry_usage(xi);

	/*
	 * Block storage will reclaim the original entry beक्रमe inserting
	 * the new value, so we only need the dअगरference.  If the new
	 * entry is smaller than the old one, we करोn't need anything.
	 */
	अगर (loc->xl_entry) अणु
		/* Don't need space if we're reusing! */
		अगर (ocfs2_xa_can_reuse_entry(loc, xi))
			needed_space = 0;
		अन्यथा
			needed_space -= ocfs2_xe_entry_usage(loc->xl_entry);
	पूर्ण
	अगर (needed_space < 0)
		needed_space = 0;
	वापस ocfs2_xa_check_space_helper(needed_space, मुक्त_start, count);
पूर्ण

/*
 * Block storage क्रम xattrs keeps the name+value pairs compacted.  When
 * we हटाओ one, we have to shअगरt any that preceded it towards the end.
 */
अटल व्योम ocfs2_xa_block_wipe_namevalue(काष्ठा ocfs2_xa_loc *loc)
अणु
	पूर्णांक i, offset;
	पूर्णांक namevalue_offset, first_namevalue_offset, namevalue_size;
	काष्ठा ocfs2_xattr_entry *entry = loc->xl_entry;
	काष्ठा ocfs2_xattr_header *xh = loc->xl_header;
	पूर्णांक count = le16_to_cpu(xh->xh_count);

	namevalue_offset = le16_to_cpu(entry->xe_name_offset);
	namevalue_size = namevalue_size_xe(entry);
	first_namevalue_offset = ocfs2_xa_get_मुक्त_start(loc);

	/* Shअगरt the name+value pairs */
	स_हटाओ((अक्षर *)xh + first_namevalue_offset + namevalue_size,
		(अक्षर *)xh + first_namevalue_offset,
		namevalue_offset - first_namevalue_offset);
	स_रखो((अक्षर *)xh + first_namevalue_offset, 0, namevalue_size);

	/* Now tell xh->xh_entries about it */
	क्रम (i = 0; i < count; i++) अणु
		offset = le16_to_cpu(xh->xh_entries[i].xe_name_offset);
		अगर (offset <= namevalue_offset)
			le16_add_cpu(&xh->xh_entries[i].xe_name_offset,
				     namevalue_size);
	पूर्ण

	/*
	 * Note that we करोn't update xh_मुक्त_start or xh_name_value_len
	 * because they're not used in block-stored xattrs.
	 */
पूर्ण

अटल व्योम ocfs2_xa_block_add_entry(काष्ठा ocfs2_xa_loc *loc, u32 name_hash)
अणु
	पूर्णांक count = le16_to_cpu(loc->xl_header->xh_count);
	loc->xl_entry = &(loc->xl_header->xh_entries[count]);
	le16_add_cpu(&loc->xl_header->xh_count, 1);
	स_रखो(loc->xl_entry, 0, माप(काष्ठा ocfs2_xattr_entry));
पूर्ण

अटल व्योम ocfs2_xa_block_add_namevalue(काष्ठा ocfs2_xa_loc *loc, पूर्णांक size)
अणु
	पूर्णांक मुक्त_start = ocfs2_xa_get_मुक्त_start(loc);

	loc->xl_entry->xe_name_offset = cpu_to_le16(मुक्त_start - size);
पूर्ण

अटल व्योम ocfs2_xa_block_fill_value_buf(काष्ठा ocfs2_xa_loc *loc,
					  काष्ठा ocfs2_xattr_value_buf *vb)
अणु
	काष्ठा buffer_head *bh = loc->xl_storage;

	अगर (loc->xl_size == (bh->b_size -
			     दुरत्व(काष्ठा ocfs2_xattr_block,
				      xb_attrs.xb_header)))
		vb->vb_access = ocfs2_journal_access_xb;
	अन्यथा
		vb->vb_access = ocfs2_journal_access_di;
	vb->vb_bh = bh;
पूर्ण

/*
 * Operations क्रम xattrs stored in blocks.  This includes अंतरभूत inode
 * storage and unindexed ocfs2_xattr_blocks.
 */
अटल स्थिर काष्ठा ocfs2_xa_loc_operations ocfs2_xa_block_loc_ops = अणु
	.xlo_journal_access	= ocfs2_xa_block_journal_access,
	.xlo_journal_dirty	= ocfs2_xa_block_journal_dirty,
	.xlo_offset_poपूर्णांकer	= ocfs2_xa_block_offset_poपूर्णांकer,
	.xlo_check_space	= ocfs2_xa_block_check_space,
	.xlo_can_reuse		= ocfs2_xa_block_can_reuse,
	.xlo_get_मुक्त_start	= ocfs2_xa_block_get_मुक्त_start,
	.xlo_wipe_namevalue	= ocfs2_xa_block_wipe_namevalue,
	.xlo_add_entry		= ocfs2_xa_block_add_entry,
	.xlo_add_namevalue	= ocfs2_xa_block_add_namevalue,
	.xlo_fill_value_buf	= ocfs2_xa_block_fill_value_buf,
पूर्ण;

अटल पूर्णांक ocfs2_xa_bucket_journal_access(handle_t *handle,
					  काष्ठा ocfs2_xa_loc *loc, पूर्णांक type)
अणु
	काष्ठा ocfs2_xattr_bucket *bucket = loc->xl_storage;

	वापस ocfs2_xattr_bucket_journal_access(handle, bucket, type);
पूर्ण

अटल व्योम ocfs2_xa_bucket_journal_dirty(handle_t *handle,
					  काष्ठा ocfs2_xa_loc *loc)
अणु
	काष्ठा ocfs2_xattr_bucket *bucket = loc->xl_storage;

	ocfs2_xattr_bucket_journal_dirty(handle, bucket);
पूर्ण

अटल व्योम *ocfs2_xa_bucket_offset_poपूर्णांकer(काष्ठा ocfs2_xa_loc *loc,
					    पूर्णांक offset)
अणु
	काष्ठा ocfs2_xattr_bucket *bucket = loc->xl_storage;
	पूर्णांक block, block_offset;

	/* The header is at the front of the bucket */
	block = offset >> loc->xl_inode->i_sb->s_blocksize_bits;
	block_offset = offset % loc->xl_inode->i_sb->s_blocksize;

	वापस bucket_block(bucket, block) + block_offset;
पूर्ण

अटल पूर्णांक ocfs2_xa_bucket_can_reuse(काष्ठा ocfs2_xa_loc *loc,
				     काष्ठा ocfs2_xattr_info *xi)
अणु
	वापस namevalue_size_xe(loc->xl_entry) >=
		namevalue_size_xi(xi);
पूर्ण

अटल पूर्णांक ocfs2_xa_bucket_get_मुक्त_start(काष्ठा ocfs2_xa_loc *loc)
अणु
	काष्ठा ocfs2_xattr_bucket *bucket = loc->xl_storage;
	वापस le16_to_cpu(bucket_xh(bucket)->xh_मुक्त_start);
पूर्ण

अटल पूर्णांक ocfs2_bucket_align_मुक्त_start(काष्ठा super_block *sb,
					 पूर्णांक मुक्त_start, पूर्णांक size)
अणु
	/*
	 * We need to make sure that the name+value pair fits within
	 * one block.
	 */
	अगर (((मुक्त_start - size) >> sb->s_blocksize_bits) !=
	    ((मुक्त_start - 1) >> sb->s_blocksize_bits))
		मुक्त_start -= मुक्त_start % sb->s_blocksize;

	वापस मुक्त_start;
पूर्ण

अटल पूर्णांक ocfs2_xa_bucket_check_space(काष्ठा ocfs2_xa_loc *loc,
				       काष्ठा ocfs2_xattr_info *xi)
अणु
	पूर्णांक rc;
	पूर्णांक count = le16_to_cpu(loc->xl_header->xh_count);
	पूर्णांक मुक्त_start = ocfs2_xa_get_मुक्त_start(loc);
	पूर्णांक needed_space = ocfs2_xi_entry_usage(xi);
	पूर्णांक size = namevalue_size_xi(xi);
	काष्ठा super_block *sb = loc->xl_inode->i_sb;

	/*
	 * Bucket storage करोes not reclaim name+value pairs it cannot
	 * reuse.  They live as holes until the bucket fills, and then
	 * the bucket is defragmented.  However, the bucket can reclaim
	 * the ocfs2_xattr_entry.
	 */
	अगर (loc->xl_entry) अणु
		/* Don't need space if we're reusing! */
		अगर (ocfs2_xa_can_reuse_entry(loc, xi))
			needed_space = 0;
		अन्यथा
			needed_space -= माप(काष्ठा ocfs2_xattr_entry);
	पूर्ण
	BUG_ON(needed_space < 0);

	अगर (मुक्त_start < size) अणु
		अगर (needed_space)
			वापस -ENOSPC;
	पूर्ण अन्यथा अणु
		/*
		 * First we check अगर it would fit in the first place.
		 * Below, we align the मुक्त start to a block.  This may
		 * slide us below the minimum gap.  By checking unaligned
		 * first, we aव्योम that error.
		 */
		rc = ocfs2_xa_check_space_helper(needed_space, मुक्त_start,
						 count);
		अगर (rc)
			वापस rc;
		मुक्त_start = ocfs2_bucket_align_मुक्त_start(sb, मुक्त_start,
							   size);
	पूर्ण
	वापस ocfs2_xa_check_space_helper(needed_space, मुक्त_start, count);
पूर्ण

अटल व्योम ocfs2_xa_bucket_wipe_namevalue(काष्ठा ocfs2_xa_loc *loc)
अणु
	le16_add_cpu(&loc->xl_header->xh_name_value_len,
		     -namevalue_size_xe(loc->xl_entry));
पूर्ण

अटल व्योम ocfs2_xa_bucket_add_entry(काष्ठा ocfs2_xa_loc *loc, u32 name_hash)
अणु
	काष्ठा ocfs2_xattr_header *xh = loc->xl_header;
	पूर्णांक count = le16_to_cpu(xh->xh_count);
	पूर्णांक low = 0, high = count - 1, पंचांगp;
	काष्ठा ocfs2_xattr_entry *पंचांगp_xe;

	/*
	 * We keep buckets sorted by name_hash, so we need to find
	 * our insert place.
	 */
	जबतक (low <= high && count) अणु
		पंचांगp = (low + high) / 2;
		पंचांगp_xe = &xh->xh_entries[पंचांगp];

		अगर (name_hash > le32_to_cpu(पंचांगp_xe->xe_name_hash))
			low = पंचांगp + 1;
		अन्यथा अगर (name_hash < le32_to_cpu(पंचांगp_xe->xe_name_hash))
			high = पंचांगp - 1;
		अन्यथा अणु
			low = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (low != count)
		स_हटाओ(&xh->xh_entries[low + 1],
			&xh->xh_entries[low],
			((count - low) * माप(काष्ठा ocfs2_xattr_entry)));

	le16_add_cpu(&xh->xh_count, 1);
	loc->xl_entry = &xh->xh_entries[low];
	स_रखो(loc->xl_entry, 0, माप(काष्ठा ocfs2_xattr_entry));
पूर्ण

अटल व्योम ocfs2_xa_bucket_add_namevalue(काष्ठा ocfs2_xa_loc *loc, पूर्णांक size)
अणु
	पूर्णांक मुक्त_start = ocfs2_xa_get_मुक्त_start(loc);
	काष्ठा ocfs2_xattr_header *xh = loc->xl_header;
	काष्ठा super_block *sb = loc->xl_inode->i_sb;
	पूर्णांक nameval_offset;

	मुक्त_start = ocfs2_bucket_align_मुक्त_start(sb, मुक्त_start, size);
	nameval_offset = मुक्त_start - size;
	loc->xl_entry->xe_name_offset = cpu_to_le16(nameval_offset);
	xh->xh_मुक्त_start = cpu_to_le16(nameval_offset);
	le16_add_cpu(&xh->xh_name_value_len, size);

पूर्ण

अटल व्योम ocfs2_xa_bucket_fill_value_buf(काष्ठा ocfs2_xa_loc *loc,
					   काष्ठा ocfs2_xattr_value_buf *vb)
अणु
	काष्ठा ocfs2_xattr_bucket *bucket = loc->xl_storage;
	काष्ठा super_block *sb = loc->xl_inode->i_sb;
	पूर्णांक nameval_offset = le16_to_cpu(loc->xl_entry->xe_name_offset);
	पूर्णांक size = namevalue_size_xe(loc->xl_entry);
	पूर्णांक block_offset = nameval_offset >> sb->s_blocksize_bits;

	/* Values are not allowed to straddle block boundaries */
	BUG_ON(block_offset !=
	       ((nameval_offset + size - 1) >> sb->s_blocksize_bits));
	/* We expect the bucket to be filled in */
	BUG_ON(!bucket->bu_bhs[block_offset]);

	vb->vb_access = ocfs2_journal_access;
	vb->vb_bh = bucket->bu_bhs[block_offset];
पूर्ण

/* Operations क्रम xattrs stored in buckets. */
अटल स्थिर काष्ठा ocfs2_xa_loc_operations ocfs2_xa_bucket_loc_ops = अणु
	.xlo_journal_access	= ocfs2_xa_bucket_journal_access,
	.xlo_journal_dirty	= ocfs2_xa_bucket_journal_dirty,
	.xlo_offset_poपूर्णांकer	= ocfs2_xa_bucket_offset_poपूर्णांकer,
	.xlo_check_space	= ocfs2_xa_bucket_check_space,
	.xlo_can_reuse		= ocfs2_xa_bucket_can_reuse,
	.xlo_get_मुक्त_start	= ocfs2_xa_bucket_get_मुक्त_start,
	.xlo_wipe_namevalue	= ocfs2_xa_bucket_wipe_namevalue,
	.xlo_add_entry		= ocfs2_xa_bucket_add_entry,
	.xlo_add_namevalue	= ocfs2_xa_bucket_add_namevalue,
	.xlo_fill_value_buf	= ocfs2_xa_bucket_fill_value_buf,
पूर्ण;

अटल अचिन्हित पूर्णांक ocfs2_xa_value_clusters(काष्ठा ocfs2_xa_loc *loc)
अणु
	काष्ठा ocfs2_xattr_value_buf vb;

	अगर (ocfs2_xattr_is_local(loc->xl_entry))
		वापस 0;

	ocfs2_xa_fill_value_buf(loc, &vb);
	वापस le32_to_cpu(vb.vb_xv->xr_clusters);
पूर्ण

अटल पूर्णांक ocfs2_xa_value_truncate(काष्ठा ocfs2_xa_loc *loc, u64 bytes,
				   काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक trunc_rc, access_rc;
	काष्ठा ocfs2_xattr_value_buf vb;

	ocfs2_xa_fill_value_buf(loc, &vb);
	trunc_rc = ocfs2_xattr_value_truncate(loc->xl_inode, &vb, bytes,
					      ctxt);

	/*
	 * The caller of ocfs2_xa_value_truncate() has alपढ़ोy called
	 * ocfs2_xa_journal_access on the loc.  However, The truncate code
	 * calls ocfs2_extend_trans().  This may commit the previous
	 * transaction and खोलो a new one.  If this is a bucket, truncate
	 * could leave only vb->vb_bh set up क्रम journaling.  Meanजबतक,
	 * the caller is expecting to dirty the entire bucket.  So we must
	 * reset the journal work.  We करो this even अगर truncate has failed,
	 * as it could have failed after committing the extend.
	 */
	access_rc = ocfs2_xa_journal_access(ctxt->handle, loc,
					    OCFS2_JOURNAL_ACCESS_WRITE);

	/* Errors in truncate take precedence */
	वापस trunc_rc ? trunc_rc : access_rc;
पूर्ण

अटल व्योम ocfs2_xa_हटाओ_entry(काष्ठा ocfs2_xa_loc *loc)
अणु
	पूर्णांक index, count;
	काष्ठा ocfs2_xattr_header *xh = loc->xl_header;
	काष्ठा ocfs2_xattr_entry *entry = loc->xl_entry;

	ocfs2_xa_wipe_namevalue(loc);
	loc->xl_entry = शून्य;

	le16_add_cpu(&xh->xh_count, -1);
	count = le16_to_cpu(xh->xh_count);

	/*
	 * Only zero out the entry अगर there are more reमुख्यing.  This is
	 * important क्रम an empty bucket, as it keeps track of the
	 * bucket's hash value.  It doesn't hurt empty block storage.
	 */
	अगर (count) अणु
		index = ((अक्षर *)entry - (अक्षर *)&xh->xh_entries) /
			माप(काष्ठा ocfs2_xattr_entry);
		स_हटाओ(&xh->xh_entries[index], &xh->xh_entries[index + 1],
			(count - index) * माप(काष्ठा ocfs2_xattr_entry));
		स_रखो(&xh->xh_entries[count], 0,
		       माप(काष्ठा ocfs2_xattr_entry));
	पूर्ण
पूर्ण

/*
 * If we have a problem adjusting the size of an बाह्यal value during
 * ocfs2_xa_prepare_entry() or ocfs2_xa_हटाओ(), we may have an xattr
 * in an पूर्णांकermediate state.  For example, the value may be partially
 * truncated.
 *
 * If the value tree hasn't changed, the extend/truncate went nowhere.
 * We have nothing to करो.  The caller can treat it as a straight error.
 *
 * If the value tree got partially truncated, we now have a corrupted
 * extended attribute.  We're going to wipe its entry and leak the
 * clusters.  Better to leak some storage than leave a corrupt entry.
 *
 * If the value tree grew, it obviously didn't grow enough क्रम the
 * new entry.  We're not going to try and reclaim those clusters either.
 * If there was alपढ़ोy an बाह्यal value there (orig_clusters != 0),
 * the new clusters are attached safely and we can just leave the old
 * value in place.  If there was no बाह्यal value there, we हटाओ
 * the entry.
 *
 * This way, the xattr block we store in the journal will be consistent.
 * If the size change broke because of the journal, no changes will hit
 * disk anyway.
 */
अटल व्योम ocfs2_xa_cleanup_value_truncate(काष्ठा ocfs2_xa_loc *loc,
					    स्थिर अक्षर *what,
					    अचिन्हित पूर्णांक orig_clusters)
अणु
	अचिन्हित पूर्णांक new_clusters = ocfs2_xa_value_clusters(loc);
	अक्षर *nameval_buf = ocfs2_xa_offset_poपूर्णांकer(loc,
				le16_to_cpu(loc->xl_entry->xe_name_offset));

	अगर (new_clusters < orig_clusters) अणु
		mlog(ML_ERROR,
		     "Partial truncate while %s xattr %.*s.  Leaking "
		     "%u clusters and removing the entry\n",
		     what, loc->xl_entry->xe_name_len, nameval_buf,
		     orig_clusters - new_clusters);
		ocfs2_xa_हटाओ_entry(loc);
	पूर्ण अन्यथा अगर (!orig_clusters) अणु
		mlog(ML_ERROR,
		     "Unable to allocate an external value for xattr "
		     "%.*s safely.  Leaking %u clusters and removing the "
		     "entry\n",
		     loc->xl_entry->xe_name_len, nameval_buf,
		     new_clusters - orig_clusters);
		ocfs2_xa_हटाओ_entry(loc);
	पूर्ण अन्यथा अगर (new_clusters > orig_clusters)
		mlog(ML_ERROR,
		     "Unable to grow xattr %.*s safely.  %u new clusters "
		     "have been added, but the value will not be "
		     "modified\n",
		     loc->xl_entry->xe_name_len, nameval_buf,
		     new_clusters - orig_clusters);
पूर्ण

अटल पूर्णांक ocfs2_xa_हटाओ(काष्ठा ocfs2_xa_loc *loc,
			   काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक orig_clusters;

	अगर (!ocfs2_xattr_is_local(loc->xl_entry)) अणु
		orig_clusters = ocfs2_xa_value_clusters(loc);
		rc = ocfs2_xa_value_truncate(loc, 0, ctxt);
		अगर (rc) अणु
			mlog_त्रुटि_सं(rc);
			/*
			 * Since this is हटाओ, we can वापस 0 अगर
			 * ocfs2_xa_cleanup_value_truncate() is going to
			 * wipe the entry anyway.  So we check the
			 * cluster count as well.
			 */
			अगर (orig_clusters != ocfs2_xa_value_clusters(loc))
				rc = 0;
			ocfs2_xa_cleanup_value_truncate(loc, "removing",
							orig_clusters);
			अगर (rc)
				जाओ out;
		पूर्ण
	पूर्ण

	ocfs2_xa_हटाओ_entry(loc);

out:
	वापस rc;
पूर्ण

अटल व्योम ocfs2_xa_install_value_root(काष्ठा ocfs2_xa_loc *loc)
अणु
	पूर्णांक name_size = OCFS2_XATTR_SIZE(loc->xl_entry->xe_name_len);
	अक्षर *nameval_buf;

	nameval_buf = ocfs2_xa_offset_poपूर्णांकer(loc,
				le16_to_cpu(loc->xl_entry->xe_name_offset));
	स_नकल(nameval_buf + name_size, &def_xv, OCFS2_XATTR_ROOT_SIZE);
पूर्ण

/*
 * Take an existing entry and make it पढ़ोy क्रम the new value.  This
 * won't allocate space, but it may मुक्त space.  It should be पढ़ोy क्रम
 * ocfs2_xa_prepare_entry() to finish the work.
 */
अटल पूर्णांक ocfs2_xa_reuse_entry(काष्ठा ocfs2_xa_loc *loc,
				काष्ठा ocfs2_xattr_info *xi,
				काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक rc = 0;
	पूर्णांक name_size = OCFS2_XATTR_SIZE(xi->xi_name_len);
	अचिन्हित पूर्णांक orig_clusters;
	अक्षर *nameval_buf;
	पूर्णांक xe_local = ocfs2_xattr_is_local(loc->xl_entry);
	पूर्णांक xi_local = xi->xi_value_len <= OCFS2_XATTR_INLINE_SIZE;

	BUG_ON(OCFS2_XATTR_SIZE(loc->xl_entry->xe_name_len) !=
	       name_size);

	nameval_buf = ocfs2_xa_offset_poपूर्णांकer(loc,
				le16_to_cpu(loc->xl_entry->xe_name_offset));
	अगर (xe_local) अणु
		स_रखो(nameval_buf + name_size, 0,
		       namevalue_size_xe(loc->xl_entry) - name_size);
		अगर (!xi_local)
			ocfs2_xa_install_value_root(loc);
	पूर्ण अन्यथा अणु
		orig_clusters = ocfs2_xa_value_clusters(loc);
		अगर (xi_local) अणु
			rc = ocfs2_xa_value_truncate(loc, 0, ctxt);
			अगर (rc < 0)
				mlog_त्रुटि_सं(rc);
			अन्यथा
				स_रखो(nameval_buf + name_size, 0,
				       namevalue_size_xe(loc->xl_entry) -
				       name_size);
		पूर्ण अन्यथा अगर (le64_to_cpu(loc->xl_entry->xe_value_size) >
			   xi->xi_value_len) अणु
			rc = ocfs2_xa_value_truncate(loc, xi->xi_value_len,
						     ctxt);
			अगर (rc < 0)
				mlog_त्रुटि_सं(rc);
		पूर्ण

		अगर (rc) अणु
			ocfs2_xa_cleanup_value_truncate(loc, "reusing",
							orig_clusters);
			जाओ out;
		पूर्ण
	पूर्ण

	loc->xl_entry->xe_value_size = cpu_to_le64(xi->xi_value_len);
	ocfs2_xattr_set_local(loc->xl_entry, xi_local);

out:
	वापस rc;
पूर्ण

/*
 * Prepares loc->xl_entry to receive the new xattr.  This includes
 * properly setting up the name+value pair region.  If loc->xl_entry
 * alपढ़ोy exists, it will take care of modअगरying it appropriately.
 *
 * Note that this modअगरies the data.  You did journal_access alपढ़ोy,
 * right?
 */
अटल पूर्णांक ocfs2_xa_prepare_entry(काष्ठा ocfs2_xa_loc *loc,
				  काष्ठा ocfs2_xattr_info *xi,
				  u32 name_hash,
				  काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक orig_clusters;
	__le64 orig_value_size = 0;

	rc = ocfs2_xa_check_space(loc, xi);
	अगर (rc)
		जाओ out;

	अगर (loc->xl_entry) अणु
		अगर (ocfs2_xa_can_reuse_entry(loc, xi)) अणु
			orig_value_size = loc->xl_entry->xe_value_size;
			rc = ocfs2_xa_reuse_entry(loc, xi, ctxt);
			अगर (rc)
				जाओ out;
			जाओ alloc_value;
		पूर्ण

		अगर (!ocfs2_xattr_is_local(loc->xl_entry)) अणु
			orig_clusters = ocfs2_xa_value_clusters(loc);
			rc = ocfs2_xa_value_truncate(loc, 0, ctxt);
			अगर (rc) अणु
				mlog_त्रुटि_सं(rc);
				ocfs2_xa_cleanup_value_truncate(loc,
								"overwriting",
								orig_clusters);
				जाओ out;
			पूर्ण
		पूर्ण
		ocfs2_xa_wipe_namevalue(loc);
	पूर्ण अन्यथा
		ocfs2_xa_add_entry(loc, name_hash);

	/*
	 * If we get here, we have a blank entry.  Fill it.  We grow our
	 * name+value pair back from the end.
	 */
	ocfs2_xa_add_namevalue(loc, xi);
	अगर (xi->xi_value_len > OCFS2_XATTR_INLINE_SIZE)
		ocfs2_xa_install_value_root(loc);

alloc_value:
	अगर (xi->xi_value_len > OCFS2_XATTR_INLINE_SIZE) अणु
		orig_clusters = ocfs2_xa_value_clusters(loc);
		rc = ocfs2_xa_value_truncate(loc, xi->xi_value_len, ctxt);
		अगर (rc < 0) अणु
			ctxt->set_पात = 1;
			ocfs2_xa_cleanup_value_truncate(loc, "growing",
							orig_clusters);
			/*
			 * If we were growing an existing value,
			 * ocfs2_xa_cleanup_value_truncate() won't हटाओ
			 * the entry. We need to restore the original value
			 * size.
			 */
			अगर (loc->xl_entry) अणु
				BUG_ON(!orig_value_size);
				loc->xl_entry->xe_value_size = orig_value_size;
			पूर्ण
			mlog_त्रुटि_सं(rc);
		पूर्ण
	पूर्ण

out:
	वापस rc;
पूर्ण

/*
 * Store the value portion of the name+value pair.  This will skip
 * values that are stored बाह्यally.  Their tree roots were set up
 * by ocfs2_xa_prepare_entry().
 */
अटल पूर्णांक ocfs2_xa_store_value(काष्ठा ocfs2_xa_loc *loc,
				काष्ठा ocfs2_xattr_info *xi,
				काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक rc = 0;
	पूर्णांक nameval_offset = le16_to_cpu(loc->xl_entry->xe_name_offset);
	पूर्णांक name_size = OCFS2_XATTR_SIZE(xi->xi_name_len);
	अक्षर *nameval_buf;
	काष्ठा ocfs2_xattr_value_buf vb;

	nameval_buf = ocfs2_xa_offset_poपूर्णांकer(loc, nameval_offset);
	अगर (xi->xi_value_len > OCFS2_XATTR_INLINE_SIZE) अणु
		ocfs2_xa_fill_value_buf(loc, &vb);
		rc = __ocfs2_xattr_set_value_outside(loc->xl_inode,
						     ctxt->handle, &vb,
						     xi->xi_value,
						     xi->xi_value_len);
	पूर्ण अन्यथा
		स_नकल(nameval_buf + name_size, xi->xi_value, xi->xi_value_len);

	वापस rc;
पूर्ण

अटल पूर्णांक ocfs2_xa_set(काष्ठा ocfs2_xa_loc *loc,
			काष्ठा ocfs2_xattr_info *xi,
			काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;
	u32 name_hash = ocfs2_xattr_name_hash(loc->xl_inode, xi->xi_name,
					      xi->xi_name_len);

	ret = ocfs2_xa_journal_access(ctxt->handle, loc,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * From here on out, everything is going to modअगरy the buffer a
	 * little.  Errors are going to leave the xattr header in a
	 * sane state.  Thus, even with errors we dirty the sucker.
	 */

	/* Don't worry, we are never called with !xi_value and !xl_entry */
	अगर (!xi->xi_value) अणु
		ret = ocfs2_xa_हटाओ(loc, ctxt);
		जाओ out_dirty;
	पूर्ण

	ret = ocfs2_xa_prepare_entry(loc, xi, name_hash, ctxt);
	अगर (ret) अणु
		अगर (ret != -ENOSPC)
			mlog_त्रुटि_सं(ret);
		जाओ out_dirty;
	पूर्ण

	ret = ocfs2_xa_store_value(loc, xi, ctxt);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out_dirty:
	ocfs2_xa_journal_dirty(ctxt->handle, loc);

out:
	वापस ret;
पूर्ण

अटल व्योम ocfs2_init_dinode_xa_loc(काष्ठा ocfs2_xa_loc *loc,
				     काष्ठा inode *inode,
				     काष्ठा buffer_head *bh,
				     काष्ठा ocfs2_xattr_entry *entry)
अणु
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)bh->b_data;

	BUG_ON(!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_XATTR_FL));

	loc->xl_inode = inode;
	loc->xl_ops = &ocfs2_xa_block_loc_ops;
	loc->xl_storage = bh;
	loc->xl_entry = entry;
	loc->xl_size = le16_to_cpu(di->i_xattr_अंतरभूत_size);
	loc->xl_header =
		(काष्ठा ocfs2_xattr_header *)(bh->b_data + bh->b_size -
					      loc->xl_size);
पूर्ण

अटल व्योम ocfs2_init_xattr_block_xa_loc(काष्ठा ocfs2_xa_loc *loc,
					  काष्ठा inode *inode,
					  काष्ठा buffer_head *bh,
					  काष्ठा ocfs2_xattr_entry *entry)
अणु
	काष्ठा ocfs2_xattr_block *xb =
		(काष्ठा ocfs2_xattr_block *)bh->b_data;

	BUG_ON(le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED);

	loc->xl_inode = inode;
	loc->xl_ops = &ocfs2_xa_block_loc_ops;
	loc->xl_storage = bh;
	loc->xl_header = &(xb->xb_attrs.xb_header);
	loc->xl_entry = entry;
	loc->xl_size = bh->b_size - दुरत्व(काष्ठा ocfs2_xattr_block,
					     xb_attrs.xb_header);
पूर्ण

अटल व्योम ocfs2_init_xattr_bucket_xa_loc(काष्ठा ocfs2_xa_loc *loc,
					   काष्ठा ocfs2_xattr_bucket *bucket,
					   काष्ठा ocfs2_xattr_entry *entry)
अणु
	loc->xl_inode = bucket->bu_inode;
	loc->xl_ops = &ocfs2_xa_bucket_loc_ops;
	loc->xl_storage = bucket;
	loc->xl_header = bucket_xh(bucket);
	loc->xl_entry = entry;
	loc->xl_size = OCFS2_XATTR_BUCKET_SIZE;
पूर्ण

/*
 * In xattr हटाओ, अगर it is stored outside and refcounted, we may have
 * the chance to split the refcount tree. So need the allocators.
 */
अटल पूर्णांक ocfs2_lock_xattr_हटाओ_allocators(काष्ठा inode *inode,
					काष्ठा ocfs2_xattr_value_root *xv,
					काष्ठा ocfs2_caching_info *ref_ci,
					काष्ठा buffer_head *ref_root_bh,
					काष्ठा ocfs2_alloc_context **meta_ac,
					पूर्णांक *ref_credits)
अणु
	पूर्णांक ret, meta_add = 0;
	u32 p_cluster, num_clusters;
	अचिन्हित पूर्णांक ext_flags;

	*ref_credits = 0;
	ret = ocfs2_xattr_get_clusters(inode, 0, &p_cluster,
				       &num_clusters,
				       &xv->xr_list,
				       &ext_flags);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (!(ext_flags & OCFS2_EXT_REFCOUNTED))
		जाओ out;

	ret = ocfs2_refcounted_xattr_delete_need(inode, ref_ci,
						 ref_root_bh, xv,
						 &meta_add, ref_credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_reserve_new_metadata_blocks(OCFS2_SB(inode->i_sb),
						meta_add, meta_ac);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_हटाओ_value_outside(काष्ठा inode*inode,
				      काष्ठा ocfs2_xattr_value_buf *vb,
				      काष्ठा ocfs2_xattr_header *header,
				      काष्ठा ocfs2_caching_info *ref_ci,
				      काष्ठा buffer_head *ref_root_bh)
अणु
	पूर्णांक ret = 0, i, ref_credits;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_xattr_set_ctxt ctxt = अणु शून्य, शून्य, पूर्ण;
	व्योम *val;

	ocfs2_init_dealloc_ctxt(&ctxt.dealloc);

	क्रम (i = 0; i < le16_to_cpu(header->xh_count); i++) अणु
		काष्ठा ocfs2_xattr_entry *entry = &header->xh_entries[i];

		अगर (ocfs2_xattr_is_local(entry))
			जारी;

		val = (व्योम *)header +
			le16_to_cpu(entry->xe_name_offset);
		vb->vb_xv = (काष्ठा ocfs2_xattr_value_root *)
			(val + OCFS2_XATTR_SIZE(entry->xe_name_len));

		ret = ocfs2_lock_xattr_हटाओ_allocators(inode, vb->vb_xv,
							 ref_ci, ref_root_bh,
							 &ctxt.meta_ac,
							 &ref_credits);

		ctxt.handle = ocfs2_start_trans(osb, ref_credits +
					ocfs2_हटाओ_extent_credits(osb->sb));
		अगर (IS_ERR(ctxt.handle)) अणु
			ret = PTR_ERR(ctxt.handle);
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = ocfs2_xattr_value_truncate(inode, vb, 0, &ctxt);

		ocfs2_commit_trans(osb, ctxt.handle);
		अगर (ctxt.meta_ac) अणु
			ocfs2_मुक्त_alloc_context(ctxt.meta_ac);
			ctxt.meta_ac = शून्य;
		पूर्ण

		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

	पूर्ण

	अगर (ctxt.meta_ac)
		ocfs2_मुक्त_alloc_context(ctxt.meta_ac);
	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &ctxt.dealloc);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_ibody_हटाओ(काष्ठा inode *inode,
				    काष्ठा buffer_head *di_bh,
				    काष्ठा ocfs2_caching_info *ref_ci,
				    काष्ठा buffer_head *ref_root_bh)
अणु

	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_xattr_header *header;
	पूर्णांक ret;
	काष्ठा ocfs2_xattr_value_buf vb = अणु
		.vb_bh = di_bh,
		.vb_access = ocfs2_journal_access_di,
	पूर्ण;

	header = (काष्ठा ocfs2_xattr_header *)
		 ((व्योम *)di + inode->i_sb->s_blocksize -
		 le16_to_cpu(di->i_xattr_अंतरभूत_size));

	ret = ocfs2_हटाओ_value_outside(inode, &vb, header,
					 ref_ci, ref_root_bh);

	वापस ret;
पूर्ण

काष्ठा ocfs2_rm_xattr_bucket_para अणु
	काष्ठा ocfs2_caching_info *ref_ci;
	काष्ठा buffer_head *ref_root_bh;
पूर्ण;

अटल पूर्णांक ocfs2_xattr_block_हटाओ(काष्ठा inode *inode,
				    काष्ठा buffer_head *blk_bh,
				    काष्ठा ocfs2_caching_info *ref_ci,
				    काष्ठा buffer_head *ref_root_bh)
अणु
	काष्ठा ocfs2_xattr_block *xb;
	पूर्णांक ret = 0;
	काष्ठा ocfs2_xattr_value_buf vb = अणु
		.vb_bh = blk_bh,
		.vb_access = ocfs2_journal_access_xb,
	पूर्ण;
	काष्ठा ocfs2_rm_xattr_bucket_para args = अणु
		.ref_ci = ref_ci,
		.ref_root_bh = ref_root_bh,
	पूर्ण;

	xb = (काष्ठा ocfs2_xattr_block *)blk_bh->b_data;
	अगर (!(le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED)) अणु
		काष्ठा ocfs2_xattr_header *header = &(xb->xb_attrs.xb_header);
		ret = ocfs2_हटाओ_value_outside(inode, &vb, header,
						 ref_ci, ref_root_bh);
	पूर्ण अन्यथा
		ret = ocfs2_iterate_xattr_index_block(inode,
						blk_bh,
						ocfs2_rm_xattr_cluster,
						&args);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_मुक्त_block(काष्ठा inode *inode,
				  u64 block,
				  काष्ठा ocfs2_caching_info *ref_ci,
				  काष्ठा buffer_head *ref_root_bh)
अणु
	काष्ठा inode *xb_alloc_inode;
	काष्ठा buffer_head *xb_alloc_bh = शून्य;
	काष्ठा buffer_head *blk_bh = शून्य;
	काष्ठा ocfs2_xattr_block *xb;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	handle_t *handle;
	पूर्णांक ret = 0;
	u64 blk, bg_blkno;
	u16 bit;

	ret = ocfs2_पढ़ो_xattr_block(inode, block, &blk_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xattr_block_हटाओ(inode, blk_bh, ref_ci, ref_root_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	xb = (काष्ठा ocfs2_xattr_block *)blk_bh->b_data;
	blk = le64_to_cpu(xb->xb_blkno);
	bit = le16_to_cpu(xb->xb_suballoc_bit);
	अगर (xb->xb_suballoc_loc)
		bg_blkno = le64_to_cpu(xb->xb_suballoc_loc);
	अन्यथा
		bg_blkno = ocfs2_which_suballoc_group(blk, bit);

	xb_alloc_inode = ocfs2_get_प्रणाली_file_inode(osb,
				EXTENT_ALLOC_SYSTEM_INODE,
				le16_to_cpu(xb->xb_suballoc_slot));
	अगर (!xb_alloc_inode) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	inode_lock(xb_alloc_inode);

	ret = ocfs2_inode_lock(xb_alloc_inode, &xb_alloc_bh, 1);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_mutex;
	पूर्ण

	handle = ocfs2_start_trans(osb, OCFS2_SUBALLOC_FREE);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock;
	पूर्ण

	ret = ocfs2_मुक्त_suballoc_bits(handle, xb_alloc_inode, xb_alloc_bh,
				       bit, bg_blkno, 1);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

	ocfs2_commit_trans(osb, handle);
out_unlock:
	ocfs2_inode_unlock(xb_alloc_inode, 1);
	brअन्यथा(xb_alloc_bh);
out_mutex:
	inode_unlock(xb_alloc_inode);
	iput(xb_alloc_inode);
out:
	brअन्यथा(blk_bh);
	वापस ret;
पूर्ण

/*
 * ocfs2_xattr_हटाओ()
 *
 * Free extended attribute resources associated with this inode.
 */
पूर्णांक ocfs2_xattr_हटाओ(काष्ठा inode *inode, काष्ठा buffer_head *di_bh)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_refcount_tree *ref_tree = शून्य;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_caching_info *ref_ci = शून्य;
	handle_t *handle;
	पूर्णांक ret;

	अगर (!ocfs2_supports_xattr(OCFS2_SB(inode->i_sb)))
		वापस 0;

	अगर (!(oi->ip_dyn_features & OCFS2_HAS_XATTR_FL))
		वापस 0;

	अगर (ocfs2_is_refcount_inode(inode)) अणु
		ret = ocfs2_lock_refcount_tree(OCFS2_SB(inode->i_sb),
					       le64_to_cpu(di->i_refcount_loc),
					       1, &ref_tree, &ref_root_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		ref_ci = &ref_tree->rf_ci;

	पूर्ण

	अगर (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL) अणु
		ret = ocfs2_xattr_ibody_हटाओ(inode, di_bh,
					       ref_ci, ref_root_bh);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (di->i_xattr_loc) अणु
		ret = ocfs2_xattr_मुक्त_block(inode,
					     le64_to_cpu(di->i_xattr_loc),
					     ref_ci, ref_root_bh);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	handle = ocfs2_start_trans((OCFS2_SB(inode->i_sb)),
				   OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	di->i_xattr_loc = 0;

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features &= ~(OCFS2_INLINE_XATTR_FL | OCFS2_HAS_XATTR_FL);
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

	ocfs2_journal_dirty(handle, di_bh);
out_commit:
	ocfs2_commit_trans(OCFS2_SB(inode->i_sb), handle);
out:
	अगर (ref_tree)
		ocfs2_unlock_refcount_tree(OCFS2_SB(inode->i_sb), ref_tree, 1);
	brअन्यथा(ref_root_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_has_space_अंतरभूत(काष्ठा inode *inode,
					काष्ठा ocfs2_dinode *di)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	अचिन्हित पूर्णांक xattrsize = OCFS2_SB(inode->i_sb)->s_xattr_अंतरभूत_size;
	पूर्णांक मुक्त;

	अगर (xattrsize < OCFS2_MIN_XATTR_INLINE_SIZE)
		वापस 0;

	अगर (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		काष्ठा ocfs2_अंतरभूत_data *idata = &di->id2.i_data;
		मुक्त = le16_to_cpu(idata->id_count) - le64_to_cpu(di->i_size);
	पूर्ण अन्यथा अगर (ocfs2_inode_is_fast_symlink(inode)) अणु
		मुक्त = ocfs2_fast_symlink_अक्षरs(inode->i_sb) -
			le64_to_cpu(di->i_size);
	पूर्ण अन्यथा अणु
		काष्ठा ocfs2_extent_list *el = &di->id2.i_list;
		मुक्त = (le16_to_cpu(el->l_count) -
			le16_to_cpu(el->l_next_मुक्त_rec)) *
			माप(काष्ठा ocfs2_extent_rec);
	पूर्ण
	अगर (मुक्त >= xattrsize)
		वापस 1;

	वापस 0;
पूर्ण

/*
 * ocfs2_xattr_ibody_find()
 *
 * Find extended attribute in inode block and
 * fill search info पूर्णांकo काष्ठा ocfs2_xattr_search.
 */
अटल पूर्णांक ocfs2_xattr_ibody_find(काष्ठा inode *inode,
				  पूर्णांक name_index,
				  स्थिर अक्षर *name,
				  काष्ठा ocfs2_xattr_search *xs)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)xs->inode_bh->b_data;
	पूर्णांक ret;
	पूर्णांक has_space = 0;

	अगर (inode->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE)
		वापस 0;

	अगर (!(oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL)) अणु
		करोwn_पढ़ो(&oi->ip_alloc_sem);
		has_space = ocfs2_xattr_has_space_अंतरभूत(inode, di);
		up_पढ़ो(&oi->ip_alloc_sem);
		अगर (!has_space)
			वापस 0;
	पूर्ण

	xs->xattr_bh = xs->inode_bh;
	xs->end = (व्योम *)di + inode->i_sb->s_blocksize;
	अगर (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL)
		xs->header = (काष्ठा ocfs2_xattr_header *)
			(xs->end - le16_to_cpu(di->i_xattr_अंतरभूत_size));
	अन्यथा
		xs->header = (काष्ठा ocfs2_xattr_header *)
			(xs->end - OCFS2_SB(inode->i_sb)->s_xattr_अंतरभूत_size);
	xs->base = (व्योम *)xs->header;
	xs->here = xs->header->xh_entries;

	/* Find the named attribute. */
	अगर (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL) अणु
		ret = ocfs2_xattr_find_entry(name_index, name, xs);
		अगर (ret && ret != -ENODATA)
			वापस ret;
		xs->not_found = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_xattr_ibody_init(काष्ठा inode *inode,
				  काष्ठा buffer_head *di_bh,
				  काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	अचिन्हित पूर्णांक xattrsize = osb->s_xattr_अंतरभूत_size;

	अगर (!ocfs2_xattr_has_space_अंतरभूत(inode, di)) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_di(ctxt->handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Adjust extent record count or अंतरभूत data size
	 * to reserve space क्रम extended attribute.
	 */
	अगर (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		काष्ठा ocfs2_अंतरभूत_data *idata = &di->id2.i_data;
		le16_add_cpu(&idata->id_count, -xattrsize);
	पूर्ण अन्यथा अगर (!(ocfs2_inode_is_fast_symlink(inode))) अणु
		काष्ठा ocfs2_extent_list *el = &di->id2.i_list;
		le16_add_cpu(&el->l_count, -(xattrsize /
					     माप(काष्ठा ocfs2_extent_rec)));
	पूर्ण
	di->i_xattr_अंतरभूत_size = cpu_to_le16(xattrsize);

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features |= OCFS2_INLINE_XATTR_FL|OCFS2_HAS_XATTR_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);

	ocfs2_journal_dirty(ctxt->handle, di_bh);

out:
	वापस ret;
पूर्ण

/*
 * ocfs2_xattr_ibody_set()
 *
 * Set, replace or हटाओ an extended attribute पूर्णांकo inode block.
 *
 */
अटल पूर्णांक ocfs2_xattr_ibody_set(काष्ठा inode *inode,
				 काष्ठा ocfs2_xattr_info *xi,
				 काष्ठा ocfs2_xattr_search *xs,
				 काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_xa_loc loc;

	अगर (inode->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE)
		वापस -ENOSPC;

	करोwn_ग_लिखो(&oi->ip_alloc_sem);
	अगर (!(oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL)) अणु
		ret = ocfs2_xattr_ibody_init(inode, xs->inode_bh, ctxt);
		अगर (ret) अणु
			अगर (ret != -ENOSPC)
				mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ocfs2_init_dinode_xa_loc(&loc, inode, xs->inode_bh,
				 xs->not_found ? शून्य : xs->here);
	ret = ocfs2_xa_set(&loc, xi, ctxt);
	अगर (ret) अणु
		अगर (ret != -ENOSPC)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	xs->here = loc.xl_entry;

out:
	up_ग_लिखो(&oi->ip_alloc_sem);

	वापस ret;
पूर्ण

/*
 * ocfs2_xattr_block_find()
 *
 * Find extended attribute in बाह्यal block and
 * fill search info पूर्णांकo काष्ठा ocfs2_xattr_search.
 */
अटल पूर्णांक ocfs2_xattr_block_find(काष्ठा inode *inode,
				  पूर्णांक name_index,
				  स्थिर अक्षर *name,
				  काष्ठा ocfs2_xattr_search *xs)
अणु
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)xs->inode_bh->b_data;
	काष्ठा buffer_head *blk_bh = शून्य;
	काष्ठा ocfs2_xattr_block *xb;
	पूर्णांक ret = 0;

	अगर (!di->i_xattr_loc)
		वापस ret;

	ret = ocfs2_पढ़ो_xattr_block(inode, le64_to_cpu(di->i_xattr_loc),
				     &blk_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	xs->xattr_bh = blk_bh;
	xb = (काष्ठा ocfs2_xattr_block *)blk_bh->b_data;

	अगर (!(le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED)) अणु
		xs->header = &xb->xb_attrs.xb_header;
		xs->base = (व्योम *)xs->header;
		xs->end = (व्योम *)(blk_bh->b_data) + blk_bh->b_size;
		xs->here = xs->header->xh_entries;

		ret = ocfs2_xattr_find_entry(name_index, name, xs);
	पूर्ण अन्यथा
		ret = ocfs2_xattr_index_block_find(inode, blk_bh,
						   name_index,
						   name, xs);

	अगर (ret && ret != -ENODATA) अणु
		xs->xattr_bh = शून्य;
		जाओ cleanup;
	पूर्ण
	xs->not_found = ret;
	वापस 0;
cleanup:
	brअन्यथा(blk_bh);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_create_xattr_block(काष्ठा inode *inode,
				    काष्ठा buffer_head *inode_bh,
				    काष्ठा ocfs2_xattr_set_ctxt *ctxt,
				    पूर्णांक indexed,
				    काष्ठा buffer_head **ret_bh)
अणु
	पूर्णांक ret;
	u16 suballoc_bit_start;
	u32 num_got;
	u64 suballoc_loc, first_blkno;
	काष्ठा ocfs2_dinode *di =  (काष्ठा ocfs2_dinode *)inode_bh->b_data;
	काष्ठा buffer_head *new_bh = शून्य;
	काष्ठा ocfs2_xattr_block *xblk;

	ret = ocfs2_journal_access_di(ctxt->handle, INODE_CACHE(inode),
				      inode_bh, OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ end;
	पूर्ण

	ret = ocfs2_claim_metadata(ctxt->handle, ctxt->meta_ac, 1,
				   &suballoc_loc, &suballoc_bit_start,
				   &num_got, &first_blkno);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ end;
	पूर्ण

	new_bh = sb_getblk(inode->i_sb, first_blkno);
	अगर (!new_bh) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ end;
	पूर्ण

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(inode), new_bh);

	ret = ocfs2_journal_access_xb(ctxt->handle, INODE_CACHE(inode),
				      new_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ end;
	पूर्ण

	/* Initialize ocfs2_xattr_block */
	xblk = (काष्ठा ocfs2_xattr_block *)new_bh->b_data;
	स_रखो(xblk, 0, inode->i_sb->s_blocksize);
	म_नकल((व्योम *)xblk, OCFS2_XATTR_BLOCK_SIGNATURE);
	xblk->xb_suballoc_slot = cpu_to_le16(ctxt->meta_ac->ac_alloc_slot);
	xblk->xb_suballoc_loc = cpu_to_le64(suballoc_loc);
	xblk->xb_suballoc_bit = cpu_to_le16(suballoc_bit_start);
	xblk->xb_fs_generation =
		cpu_to_le32(OCFS2_SB(inode->i_sb)->fs_generation);
	xblk->xb_blkno = cpu_to_le64(first_blkno);
	अगर (indexed) अणु
		काष्ठा ocfs2_xattr_tree_root *xr = &xblk->xb_attrs.xb_root;
		xr->xt_clusters = cpu_to_le32(1);
		xr->xt_last_eb_blk = 0;
		xr->xt_list.l_tree_depth = 0;
		xr->xt_list.l_count = cpu_to_le16(
					ocfs2_xattr_recs_per_xb(inode->i_sb));
		xr->xt_list.l_next_मुक्त_rec = cpu_to_le16(1);
		xblk->xb_flags = cpu_to_le16(OCFS2_XATTR_INDEXED);
	पूर्ण
	ocfs2_journal_dirty(ctxt->handle, new_bh);

	/* Add it to the inode */
	di->i_xattr_loc = cpu_to_le64(first_blkno);

	spin_lock(&OCFS2_I(inode)->ip_lock);
	OCFS2_I(inode)->ip_dyn_features |= OCFS2_HAS_XATTR_FL;
	di->i_dyn_features = cpu_to_le16(OCFS2_I(inode)->ip_dyn_features);
	spin_unlock(&OCFS2_I(inode)->ip_lock);

	ocfs2_journal_dirty(ctxt->handle, inode_bh);

	*ret_bh = new_bh;
	new_bh = शून्य;

end:
	brअन्यथा(new_bh);
	वापस ret;
पूर्ण

/*
 * ocfs2_xattr_block_set()
 *
 * Set, replace or हटाओ an extended attribute पूर्णांकo बाह्यal block.
 *
 */
अटल पूर्णांक ocfs2_xattr_block_set(काष्ठा inode *inode,
				 काष्ठा ocfs2_xattr_info *xi,
				 काष्ठा ocfs2_xattr_search *xs,
				 काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	काष्ठा buffer_head *new_bh = शून्य;
	काष्ठा ocfs2_xattr_block *xblk = शून्य;
	पूर्णांक ret;
	काष्ठा ocfs2_xa_loc loc;

	अगर (!xs->xattr_bh) अणु
		ret = ocfs2_create_xattr_block(inode, xs->inode_bh, ctxt,
					       0, &new_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ end;
		पूर्ण

		xs->xattr_bh = new_bh;
		xblk = (काष्ठा ocfs2_xattr_block *)xs->xattr_bh->b_data;
		xs->header = &xblk->xb_attrs.xb_header;
		xs->base = (व्योम *)xs->header;
		xs->end = (व्योम *)xblk + inode->i_sb->s_blocksize;
		xs->here = xs->header->xh_entries;
	पूर्ण अन्यथा
		xblk = (काष्ठा ocfs2_xattr_block *)xs->xattr_bh->b_data;

	अगर (!(le16_to_cpu(xblk->xb_flags) & OCFS2_XATTR_INDEXED)) अणु
		ocfs2_init_xattr_block_xa_loc(&loc, inode, xs->xattr_bh,
					      xs->not_found ? शून्य : xs->here);

		ret = ocfs2_xa_set(&loc, xi, ctxt);
		अगर (!ret)
			xs->here = loc.xl_entry;
		अन्यथा अगर ((ret != -ENOSPC) || ctxt->set_पात)
			जाओ end;
		अन्यथा अणु
			ret = ocfs2_xattr_create_index_block(inode, xs, ctxt);
			अगर (ret)
				जाओ end;
		पूर्ण
	पूर्ण

	अगर (le16_to_cpu(xblk->xb_flags) & OCFS2_XATTR_INDEXED)
		ret = ocfs2_xattr_set_entry_index_block(inode, xi, xs, ctxt);

end:
	वापस ret;
पूर्ण

/* Check whether the new xattr can be inserted पूर्णांकo the inode. */
अटल पूर्णांक ocfs2_xattr_can_be_in_inode(काष्ठा inode *inode,
				       काष्ठा ocfs2_xattr_info *xi,
				       काष्ठा ocfs2_xattr_search *xs)
अणु
	काष्ठा ocfs2_xattr_entry *last;
	पूर्णांक मुक्त, i;
	माप_प्रकार min_offs = xs->end - xs->base;

	अगर (!xs->header)
		वापस 0;

	last = xs->header->xh_entries;

	क्रम (i = 0; i < le16_to_cpu(xs->header->xh_count); i++) अणु
		माप_प्रकार offs = le16_to_cpu(last->xe_name_offset);
		अगर (offs < min_offs)
			min_offs = offs;
		last += 1;
	पूर्ण

	मुक्त = min_offs - ((व्योम *)last - xs->base) - OCFS2_XATTR_HEADER_GAP;
	अगर (मुक्त < 0)
		वापस 0;

	BUG_ON(!xs->not_found);

	अगर (मुक्त >= (माप(काष्ठा ocfs2_xattr_entry) + namevalue_size_xi(xi)))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_calc_xattr_set_need(काष्ठा inode *inode,
				     काष्ठा ocfs2_dinode *di,
				     काष्ठा ocfs2_xattr_info *xi,
				     काष्ठा ocfs2_xattr_search *xis,
				     काष्ठा ocfs2_xattr_search *xbs,
				     पूर्णांक *clusters_need,
				     पूर्णांक *meta_need,
				     पूर्णांक *credits_need)
अणु
	पूर्णांक ret = 0, old_in_xb = 0;
	पूर्णांक clusters_add = 0, meta_add = 0, credits = 0;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_xattr_block *xb = शून्य;
	काष्ठा ocfs2_xattr_entry *xe = शून्य;
	काष्ठा ocfs2_xattr_value_root *xv = शून्य;
	अक्षर *base = शून्य;
	पूर्णांक name_offset, name_len = 0;
	u32 new_clusters = ocfs2_clusters_क्रम_bytes(inode->i_sb,
						    xi->xi_value_len);
	u64 value_size;

	/*
	 * Calculate the clusters we need to ग_लिखो.
	 * No matter whether we replace an old one or add a new one,
	 * we need this क्रम writing.
	 */
	अगर (xi->xi_value_len > OCFS2_XATTR_INLINE_SIZE)
		credits += new_clusters *
			   ocfs2_clusters_to_blocks(inode->i_sb, 1);

	अगर (xis->not_found && xbs->not_found) अणु
		credits += ocfs2_blocks_per_xattr_bucket(inode->i_sb);

		अगर (xi->xi_value_len > OCFS2_XATTR_INLINE_SIZE) अणु
			clusters_add += new_clusters;
			credits += ocfs2_calc_extend_credits(inode->i_sb,
							&def_xv.xv.xr_list);
		पूर्ण

		जाओ meta_guess;
	पूर्ण

	अगर (!xis->not_found) अणु
		xe = xis->here;
		name_offset = le16_to_cpu(xe->xe_name_offset);
		name_len = OCFS2_XATTR_SIZE(xe->xe_name_len);
		base = xis->base;
		credits += OCFS2_INODE_UPDATE_CREDITS;
	पूर्ण अन्यथा अणु
		पूर्णांक i, block_off = 0;
		xb = (काष्ठा ocfs2_xattr_block *)xbs->xattr_bh->b_data;
		xe = xbs->here;
		name_offset = le16_to_cpu(xe->xe_name_offset);
		name_len = OCFS2_XATTR_SIZE(xe->xe_name_len);
		i = xbs->here - xbs->header->xh_entries;
		old_in_xb = 1;

		अगर (le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED) अणु
			ret = ocfs2_xattr_bucket_get_name_value(inode->i_sb,
							bucket_xh(xbs->bucket),
							i, &block_off,
							&name_offset);
			base = bucket_block(xbs->bucket, block_off);
			credits += ocfs2_blocks_per_xattr_bucket(inode->i_sb);
		पूर्ण अन्यथा अणु
			base = xbs->base;
			credits += OCFS2_XATTR_BLOCK_UPDATE_CREDITS;
		पूर्ण
	पूर्ण

	/*
	 * delete a xattr करोesn't need metadata and cluster allocation.
	 * so just calculate the credits and वापस.
	 *
	 * The credits क्रम removing the value tree will be extended
	 * by ocfs2_हटाओ_extent itself.
	 */
	अगर (!xi->xi_value) अणु
		अगर (!ocfs2_xattr_is_local(xe))
			credits += ocfs2_हटाओ_extent_credits(inode->i_sb);

		जाओ out;
	पूर्ण

	/* करो cluster allocation guess first. */
	value_size = le64_to_cpu(xe->xe_value_size);

	अगर (old_in_xb) अणु
		/*
		 * In xattr set, we always try to set the xe in inode first,
		 * so अगर it can be inserted पूर्णांकo inode successfully, the old
		 * one will be हटाओd from the xattr block, and this xattr
		 * will be inserted पूर्णांकo inode as a new xattr in inode.
		 */
		अगर (ocfs2_xattr_can_be_in_inode(inode, xi, xis)) अणु
			clusters_add += new_clusters;
			credits += ocfs2_हटाओ_extent_credits(inode->i_sb) +
				    OCFS2_INODE_UPDATE_CREDITS;
			अगर (!ocfs2_xattr_is_local(xe))
				credits += ocfs2_calc_extend_credits(
							inode->i_sb,
							&def_xv.xv.xr_list);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (xi->xi_value_len > OCFS2_XATTR_INLINE_SIZE) अणु
		/* the new values will be stored outside. */
		u32 old_clusters = 0;

		अगर (!ocfs2_xattr_is_local(xe)) अणु
			old_clusters =	ocfs2_clusters_क्रम_bytes(inode->i_sb,
								 value_size);
			xv = (काष्ठा ocfs2_xattr_value_root *)
			     (base + name_offset + name_len);
			value_size = OCFS2_XATTR_ROOT_SIZE;
		पूर्ण अन्यथा
			xv = &def_xv.xv;

		अगर (old_clusters >= new_clusters) अणु
			credits += ocfs2_हटाओ_extent_credits(inode->i_sb);
			जाओ out;
		पूर्ण अन्यथा अणु
			meta_add += ocfs2_extend_meta_needed(&xv->xr_list);
			clusters_add += new_clusters - old_clusters;
			credits += ocfs2_calc_extend_credits(inode->i_sb,
							     &xv->xr_list);
			अगर (value_size >= OCFS2_XATTR_ROOT_SIZE)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Now the new value will be stored inside. So अगर the new
		 * value is smaller than the size of value root or the old
		 * value, we करोn't need any allocation, otherwise we have
		 * to guess metadata allocation.
		 */
		अगर ((ocfs2_xattr_is_local(xe) &&
		     (value_size >= xi->xi_value_len)) ||
		    (!ocfs2_xattr_is_local(xe) &&
		     OCFS2_XATTR_ROOT_SIZE >= xi->xi_value_len))
			जाओ out;
	पूर्ण

meta_guess:
	/* calculate metadata allocation. */
	अगर (di->i_xattr_loc) अणु
		अगर (!xbs->xattr_bh) अणु
			ret = ocfs2_पढ़ो_xattr_block(inode,
						     le64_to_cpu(di->i_xattr_loc),
						     &bh);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			xb = (काष्ठा ocfs2_xattr_block *)bh->b_data;
		पूर्ण अन्यथा
			xb = (काष्ठा ocfs2_xattr_block *)xbs->xattr_bh->b_data;

		/*
		 * If there is alपढ़ोy an xattr tree, good, we can calculate
		 * like other b-trees. Otherwise we may have the chance of
		 * create a tree, the credit calculation is borrowed from
		 * ocfs2_calc_extend_credits with root_el = शून्य. And the
		 * new tree will be cluster based, so no meta is needed.
		 */
		अगर (le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED) अणु
			काष्ठा ocfs2_extent_list *el =
				 &xb->xb_attrs.xb_root.xt_list;
			meta_add += ocfs2_extend_meta_needed(el);
			credits += ocfs2_calc_extend_credits(inode->i_sb,
							     el);
		पूर्ण अन्यथा
			credits += OCFS2_SUBALLOC_ALLOC + 1;

		/*
		 * This cluster will be used either क्रम new bucket or क्रम
		 * new xattr block.
		 * If the cluster size is the same as the bucket size, one
		 * more is needed since we may need to extend the bucket
		 * also.
		 */
		clusters_add += 1;
		credits += ocfs2_blocks_per_xattr_bucket(inode->i_sb);
		अगर (OCFS2_XATTR_BUCKET_SIZE ==
			OCFS2_SB(inode->i_sb)->s_clustersize) अणु
			credits += ocfs2_blocks_per_xattr_bucket(inode->i_sb);
			clusters_add += 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		credits += OCFS2_XATTR_BLOCK_CREATE_CREDITS;
		अगर (xi->xi_value_len > OCFS2_XATTR_INLINE_SIZE) अणु
			काष्ठा ocfs2_extent_list *el = &def_xv.xv.xr_list;
			meta_add += ocfs2_extend_meta_needed(el);
			credits += ocfs2_calc_extend_credits(inode->i_sb,
							     el);
		पूर्ण अन्यथा अणु
			meta_add += 1;
		पूर्ण
	पूर्ण
out:
	अगर (clusters_need)
		*clusters_need = clusters_add;
	अगर (meta_need)
		*meta_need = meta_add;
	अगर (credits_need)
		*credits_need = credits;
	brअन्यथा(bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_init_xattr_set_ctxt(काष्ठा inode *inode,
				     काष्ठा ocfs2_dinode *di,
				     काष्ठा ocfs2_xattr_info *xi,
				     काष्ठा ocfs2_xattr_search *xis,
				     काष्ठा ocfs2_xattr_search *xbs,
				     काष्ठा ocfs2_xattr_set_ctxt *ctxt,
				     पूर्णांक extra_meta,
				     पूर्णांक *credits)
अणु
	पूर्णांक clusters_add, meta_add, ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	स_रखो(ctxt, 0, माप(काष्ठा ocfs2_xattr_set_ctxt));

	ocfs2_init_dealloc_ctxt(&ctxt->dealloc);

	ret = ocfs2_calc_xattr_set_need(inode, di, xi, xis, xbs,
					&clusters_add, &meta_add, credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	meta_add += extra_meta;
	trace_ocfs2_init_xattr_set_ctxt(xi->xi_name, meta_add,
					clusters_add, *credits);

	अगर (meta_add) अणु
		ret = ocfs2_reserve_new_metadata_blocks(osb, meta_add,
							&ctxt->meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (clusters_add) अणु
		ret = ocfs2_reserve_clusters(osb, clusters_add, &ctxt->data_ac);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण
out:
	अगर (ret) अणु
		अगर (ctxt->meta_ac) अणु
			ocfs2_मुक्त_alloc_context(ctxt->meta_ac);
			ctxt->meta_ac = शून्य;
		पूर्ण

		/*
		 * We cannot have an error and a non null ctxt->data_ac.
		 */
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_xattr_set_handle(काष्ठा inode *inode,
				    काष्ठा ocfs2_dinode *di,
				    काष्ठा ocfs2_xattr_info *xi,
				    काष्ठा ocfs2_xattr_search *xis,
				    काष्ठा ocfs2_xattr_search *xbs,
				    काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret = 0, credits, old_found;

	अगर (!xi->xi_value) अणु
		/* Remove existing extended attribute */
		अगर (!xis->not_found)
			ret = ocfs2_xattr_ibody_set(inode, xi, xis, ctxt);
		अन्यथा अगर (!xbs->not_found)
			ret = ocfs2_xattr_block_set(inode, xi, xbs, ctxt);
	पूर्ण अन्यथा अणु
		/* We always try to set extended attribute पूर्णांकo inode first*/
		ret = ocfs2_xattr_ibody_set(inode, xi, xis, ctxt);
		अगर (!ret && !xbs->not_found) अणु
			/*
			 * If succeed and that extended attribute existing in
			 * बाह्यal block, then we will हटाओ it.
			 */
			xi->xi_value = शून्य;
			xi->xi_value_len = 0;

			old_found = xis->not_found;
			xis->not_found = -ENODATA;
			ret = ocfs2_calc_xattr_set_need(inode,
							di,
							xi,
							xis,
							xbs,
							शून्य,
							शून्य,
							&credits);
			xis->not_found = old_found;
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			ret = ocfs2_extend_trans(ctxt->handle, credits);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
			ret = ocfs2_xattr_block_set(inode, xi, xbs, ctxt);
		पूर्ण अन्यथा अगर ((ret == -ENOSPC) && !ctxt->set_पात) अणु
			अगर (di->i_xattr_loc && !xbs->xattr_bh) अणु
				ret = ocfs2_xattr_block_find(inode,
							     xi->xi_name_index,
							     xi->xi_name, xbs);
				अगर (ret)
					जाओ out;

				old_found = xis->not_found;
				xis->not_found = -ENODATA;
				ret = ocfs2_calc_xattr_set_need(inode,
								di,
								xi,
								xis,
								xbs,
								शून्य,
								शून्य,
								&credits);
				xis->not_found = old_found;
				अगर (ret) अणु
					mlog_त्रुटि_सं(ret);
					जाओ out;
				पूर्ण

				ret = ocfs2_extend_trans(ctxt->handle, credits);
				अगर (ret) अणु
					mlog_त्रुटि_सं(ret);
					जाओ out;
				पूर्ण
			पूर्ण
			/*
			 * If no space in inode, we will set extended attribute
			 * पूर्णांकo बाह्यal block.
			 */
			ret = ocfs2_xattr_block_set(inode, xi, xbs, ctxt);
			अगर (ret)
				जाओ out;
			अगर (!xis->not_found) अणु
				/*
				 * If succeed and that extended attribute
				 * existing in inode, we will हटाओ it.
				 */
				xi->xi_value = शून्य;
				xi->xi_value_len = 0;
				xbs->not_found = -ENODATA;
				ret = ocfs2_calc_xattr_set_need(inode,
								di,
								xi,
								xis,
								xbs,
								शून्य,
								शून्य,
								&credits);
				अगर (ret) अणु
					mlog_त्रुटि_सं(ret);
					जाओ out;
				पूर्ण

				ret = ocfs2_extend_trans(ctxt->handle, credits);
				अगर (ret) अणु
					mlog_त्रुटि_सं(ret);
					जाओ out;
				पूर्ण
				ret = ocfs2_xattr_ibody_set(inode, xi,
							    xis, ctxt);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ret) अणु
		/* Update inode स_समय. */
		ret = ocfs2_journal_access_di(ctxt->handle, INODE_CACHE(inode),
					      xis->inode_bh,
					      OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		inode->i_स_समय = current_समय(inode);
		di->i_स_समय = cpu_to_le64(inode->i_स_समय.tv_sec);
		di->i_स_समय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);
		ocfs2_journal_dirty(ctxt->handle, xis->inode_bh);
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * This function only called duing creating inode
 * क्रम init security/acl xattrs of the new inode.
 * All transanction credits have been reserved in mknod.
 */
पूर्णांक ocfs2_xattr_set_handle(handle_t *handle,
			   काष्ठा inode *inode,
			   काष्ठा buffer_head *di_bh,
			   पूर्णांक name_index,
			   स्थिर अक्षर *name,
			   स्थिर व्योम *value,
			   माप_प्रकार value_len,
			   पूर्णांक flags,
			   काष्ठा ocfs2_alloc_context *meta_ac,
			   काष्ठा ocfs2_alloc_context *data_ac)
अणु
	काष्ठा ocfs2_dinode *di;
	पूर्णांक ret;

	काष्ठा ocfs2_xattr_info xi = अणु
		.xi_name_index = name_index,
		.xi_name = name,
		.xi_name_len = म_माप(name),
		.xi_value = value,
		.xi_value_len = value_len,
	पूर्ण;

	काष्ठा ocfs2_xattr_search xis = अणु
		.not_found = -ENODATA,
	पूर्ण;

	काष्ठा ocfs2_xattr_search xbs = अणु
		.not_found = -ENODATA,
	पूर्ण;

	काष्ठा ocfs2_xattr_set_ctxt ctxt = अणु
		.handle = handle,
		.meta_ac = meta_ac,
		.data_ac = data_ac,
	पूर्ण;

	अगर (!ocfs2_supports_xattr(OCFS2_SB(inode->i_sb)))
		वापस -EOPNOTSUPP;

	/*
	 * In extreme situation, may need xattr bucket when
	 * block size is too small. And we have alपढ़ोy reserved
	 * the credits क्रम bucket in mknod.
	 */
	अगर (inode->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE) अणु
		xbs.bucket = ocfs2_xattr_bucket_new(inode);
		अगर (!xbs.bucket) अणु
			mlog_त्रुटि_सं(-ENOMEM);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	xis.inode_bh = xbs.inode_bh = di_bh;
	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_xattr_sem);

	ret = ocfs2_xattr_ibody_find(inode, name_index, name, &xis);
	अगर (ret)
		जाओ cleanup;
	अगर (xis.not_found) अणु
		ret = ocfs2_xattr_block_find(inode, name_index, name, &xbs);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	ret = __ocfs2_xattr_set_handle(inode, di, &xi, &xis, &xbs, &ctxt);

cleanup:
	up_ग_लिखो(&OCFS2_I(inode)->ip_xattr_sem);
	brअन्यथा(xbs.xattr_bh);
	ocfs2_xattr_bucket_मुक्त(xbs.bucket);

	वापस ret;
पूर्ण

/*
 * ocfs2_xattr_set()
 *
 * Set, replace or हटाओ an extended attribute क्रम this inode.
 * value is शून्य to हटाओ an existing extended attribute, अन्यथा either
 * create or replace an extended attribute.
 */
पूर्णांक ocfs2_xattr_set(काष्ठा inode *inode,
		    पूर्णांक name_index,
		    स्थिर अक्षर *name,
		    स्थिर व्योम *value,
		    माप_प्रकार value_len,
		    पूर्णांक flags)
अणु
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	पूर्णांक ret, credits, had_lock, ref_meta = 0, ref_credits = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	काष्ठा ocfs2_xattr_set_ctxt ctxt = अणु शून्य, शून्य, शून्य, पूर्ण;
	काष्ठा ocfs2_refcount_tree *ref_tree = शून्य;
	काष्ठा ocfs2_lock_holder oh;

	काष्ठा ocfs2_xattr_info xi = अणु
		.xi_name_index = name_index,
		.xi_name = name,
		.xi_name_len = म_माप(name),
		.xi_value = value,
		.xi_value_len = value_len,
	पूर्ण;

	काष्ठा ocfs2_xattr_search xis = अणु
		.not_found = -ENODATA,
	पूर्ण;

	काष्ठा ocfs2_xattr_search xbs = अणु
		.not_found = -ENODATA,
	पूर्ण;

	अगर (!ocfs2_supports_xattr(osb))
		वापस -EOPNOTSUPP;

	/*
	 * Only xbs will be used on indexed trees.  xis करोesn't need a
	 * bucket.
	 */
	xbs.bucket = ocfs2_xattr_bucket_new(inode);
	अगर (!xbs.bucket) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		वापस -ENOMEM;
	पूर्ण

	had_lock = ocfs2_inode_lock_tracker(inode, &di_bh, 1, &oh);
	अगर (had_lock < 0) अणु
		ret = had_lock;
		mlog_त्रुटि_सं(ret);
		जाओ cleanup_nolock;
	पूर्ण
	xis.inode_bh = xbs.inode_bh = di_bh;
	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_xattr_sem);
	/*
	 * Scan inode and बाह्यal block to find the same name
	 * extended attribute and collect search inक्रमmation.
	 */
	ret = ocfs2_xattr_ibody_find(inode, name_index, name, &xis);
	अगर (ret)
		जाओ cleanup;
	अगर (xis.not_found) अणु
		ret = ocfs2_xattr_block_find(inode, name_index, name, &xbs);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	अगर (xis.not_found && xbs.not_found) अणु
		ret = -ENODATA;
		अगर (flags & XATTR_REPLACE)
			जाओ cleanup;
		ret = 0;
		अगर (!value)
			जाओ cleanup;
	पूर्ण अन्यथा अणु
		ret = -EEXIST;
		अगर (flags & XATTR_CREATE)
			जाओ cleanup;
	पूर्ण

	/* Check whether the value is refcounted and करो some preparation. */
	अगर (ocfs2_is_refcount_inode(inode) &&
	    (!xis.not_found || !xbs.not_found)) अणु
		ret = ocfs2_prepare_refcount_xattr(inode, di, &xi,
						   &xis, &xbs, &ref_tree,
						   &ref_meta, &ref_credits);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	inode_lock(tl_inode);

	अगर (ocfs2_truncate_log_needs_flush(osb)) अणु
		ret = __ocfs2_flush_truncate_log(osb);
		अगर (ret < 0) अणु
			inode_unlock(tl_inode);
			mlog_त्रुटि_सं(ret);
			जाओ cleanup;
		पूर्ण
	पूर्ण
	inode_unlock(tl_inode);

	ret = ocfs2_init_xattr_set_ctxt(inode, di, &xi, &xis,
					&xbs, &ctxt, ref_meta, &credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ cleanup;
	पूर्ण

	/* we need to update inode's स_समय field, so add credit क्रम it. */
	credits += OCFS2_INODE_UPDATE_CREDITS;
	ctxt.handle = ocfs2_start_trans(osb, credits + ref_credits);
	अगर (IS_ERR(ctxt.handle)) अणु
		ret = PTR_ERR(ctxt.handle);
		mlog_त्रुटि_सं(ret);
		जाओ out_मुक्त_ac;
	पूर्ण

	ret = __ocfs2_xattr_set_handle(inode, di, &xi, &xis, &xbs, &ctxt);
	ocfs2_update_inode_fsync_trans(ctxt.handle, inode, 0);

	ocfs2_commit_trans(osb, ctxt.handle);

out_मुक्त_ac:
	अगर (ctxt.data_ac)
		ocfs2_मुक्त_alloc_context(ctxt.data_ac);
	अगर (ctxt.meta_ac)
		ocfs2_मुक्त_alloc_context(ctxt.meta_ac);
	अगर (ocfs2_dealloc_has_cluster(&ctxt.dealloc))
		ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &ctxt.dealloc);

cleanup:
	अगर (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	up_ग_लिखो(&OCFS2_I(inode)->ip_xattr_sem);
	अगर (!value && !ret) अणु
		ret = ocfs2_try_हटाओ_refcount_tree(inode, di_bh);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण
	ocfs2_inode_unlock_tracker(inode, 1, &oh, had_lock);
cleanup_nolock:
	brअन्यथा(di_bh);
	brअन्यथा(xbs.xattr_bh);
	ocfs2_xattr_bucket_मुक्त(xbs.bucket);

	वापस ret;
पूर्ण

/*
 * Find the xattr extent rec which may contains name_hash.
 * e_cpos will be the first name hash of the xattr rec.
 * el must be the ocfs2_xattr_header.xb_attrs.xb_root.xt_list.
 */
अटल पूर्णांक ocfs2_xattr_get_rec(काष्ठा inode *inode,
			       u32 name_hash,
			       u64 *p_blkno,
			       u32 *e_cpos,
			       u32 *num_clusters,
			       काष्ठा ocfs2_extent_list *el)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा buffer_head *eb_bh = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_rec *rec = शून्य;
	u64 e_blkno = 0;

	अगर (el->l_tree_depth) अणु
		ret = ocfs2_find_leaf(INODE_CACHE(inode), el, name_hash,
				      &eb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;

		अगर (el->l_tree_depth) अणु
			ret = ocfs2_error(inode->i_sb,
					  "Inode %lu has non zero tree depth in xattr tree block %llu\n",
					  inode->i_ino,
					  (अचिन्हित दीर्घ दीर्घ)eb_bh->b_blocknr);
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = le16_to_cpu(el->l_next_मुक्त_rec) - 1; i >= 0; i--) अणु
		rec = &el->l_recs[i];

		अगर (le32_to_cpu(rec->e_cpos) <= name_hash) अणु
			e_blkno = le64_to_cpu(rec->e_blkno);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!e_blkno) अणु
		ret = ocfs2_error(inode->i_sb, "Inode %lu has bad extent record (%u, %u, 0) in xattr\n",
				  inode->i_ino,
				  le32_to_cpu(rec->e_cpos),
				  ocfs2_rec_clusters(el, rec));
		जाओ out;
	पूर्ण

	*p_blkno = le64_to_cpu(rec->e_blkno);
	*num_clusters = le16_to_cpu(rec->e_leaf_clusters);
	अगर (e_cpos)
		*e_cpos = le32_to_cpu(rec->e_cpos);
out:
	brअन्यथा(eb_bh);
	वापस ret;
पूर्ण

प्रकार पूर्णांक (xattr_bucket_func)(काष्ठा inode *inode,
				काष्ठा ocfs2_xattr_bucket *bucket,
				व्योम *para);

अटल पूर्णांक ocfs2_find_xe_in_bucket(काष्ठा inode *inode,
				   काष्ठा ocfs2_xattr_bucket *bucket,
				   पूर्णांक name_index,
				   स्थिर अक्षर *name,
				   u32 name_hash,
				   u16 *xe_index,
				   पूर्णांक *found)
अणु
	पूर्णांक i, ret = 0, cmp = 1, block_off, new_offset;
	काष्ठा ocfs2_xattr_header *xh = bucket_xh(bucket);
	माप_प्रकार name_len = म_माप(name);
	काष्ठा ocfs2_xattr_entry *xe = शून्य;
	अक्षर *xe_name;

	/*
	 * We करोn't use binary search in the bucket because there
	 * may be multiple entries with the same name hash.
	 */
	क्रम (i = 0; i < le16_to_cpu(xh->xh_count); i++) अणु
		xe = &xh->xh_entries[i];

		अगर (name_hash > le32_to_cpu(xe->xe_name_hash))
			जारी;
		अन्यथा अगर (name_hash < le32_to_cpu(xe->xe_name_hash))
			अवरोध;

		cmp = name_index - ocfs2_xattr_get_type(xe);
		अगर (!cmp)
			cmp = name_len - xe->xe_name_len;
		अगर (cmp)
			जारी;

		ret = ocfs2_xattr_bucket_get_name_value(inode->i_sb,
							xh,
							i,
							&block_off,
							&new_offset);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण


		xe_name = bucket_block(bucket, block_off) + new_offset;
		अगर (!स_भेद(name, xe_name, name_len)) अणु
			*xe_index = i;
			*found = 1;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Find the specअगरied xattr entry in a series of buckets.
 * This series start from p_blkno and last क्रम num_clusters.
 * The ocfs2_xattr_header.xh_num_buckets of the first bucket contains
 * the num of the valid buckets.
 *
 * Return the buffer_head this xattr should reside in. And अगर the xattr's
 * hash is in the gap of 2 buckets, वापस the lower bucket.
 */
अटल पूर्णांक ocfs2_xattr_bucket_find(काष्ठा inode *inode,
				   पूर्णांक name_index,
				   स्थिर अक्षर *name,
				   u32 name_hash,
				   u64 p_blkno,
				   u32 first_hash,
				   u32 num_clusters,
				   काष्ठा ocfs2_xattr_search *xs)
अणु
	पूर्णांक ret, found = 0;
	काष्ठा ocfs2_xattr_header *xh = शून्य;
	काष्ठा ocfs2_xattr_entry *xe = शून्य;
	u16 index = 0;
	u16 blk_per_bucket = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	पूर्णांक low_bucket = 0, bucket, high_bucket;
	काष्ठा ocfs2_xattr_bucket *search;
	u64 blkno, lower_blkno = 0;

	search = ocfs2_xattr_bucket_new(inode);
	अगर (!search) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_xattr_bucket(search, p_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	xh = bucket_xh(search);
	high_bucket = le16_to_cpu(xh->xh_num_buckets) - 1;
	जबतक (low_bucket <= high_bucket) अणु
		ocfs2_xattr_bucket_rअन्यथा(search);

		bucket = (low_bucket + high_bucket) / 2;
		blkno = p_blkno + bucket * blk_per_bucket;
		ret = ocfs2_पढ़ो_xattr_bucket(search, blkno);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		xh = bucket_xh(search);
		xe = &xh->xh_entries[0];
		अगर (name_hash < le32_to_cpu(xe->xe_name_hash)) अणु
			high_bucket = bucket - 1;
			जारी;
		पूर्ण

		/*
		 * Check whether the hash of the last entry in our
		 * bucket is larger than the search one. क्रम an empty
		 * bucket, the last one is also the first one.
		 */
		अगर (xh->xh_count)
			xe = &xh->xh_entries[le16_to_cpu(xh->xh_count) - 1];

		/* record lower_blkno which may be the insert place. */
		lower_blkno = blkno;

		अगर (name_hash > le32_to_cpu(xe->xe_name_hash)) अणु
			low_bucket = bucket + 1;
			जारी;
		पूर्ण

		/* the searched xattr should reside in this bucket अगर exists. */
		ret = ocfs2_find_xe_in_bucket(inode, search,
					      name_index, name, name_hash,
					      &index, &found);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * Record the bucket we have found.
	 * When the xattr's hash value is in the gap of 2 buckets, we will
	 * always set it to the previous bucket.
	 */
	अगर (!lower_blkno)
		lower_blkno = p_blkno;

	/* This should be in cache - we just पढ़ो it during the search */
	ret = ocfs2_पढ़ो_xattr_bucket(xs->bucket, lower_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	xs->header = bucket_xh(xs->bucket);
	xs->base = bucket_block(xs->bucket, 0);
	xs->end = xs->base + inode->i_sb->s_blocksize;

	अगर (found) अणु
		xs->here = &xs->header->xh_entries[index];
		trace_ocfs2_xattr_bucket_find(OCFS2_I(inode)->ip_blkno,
			name, name_index, name_hash,
			(अचिन्हित दीर्घ दीर्घ)bucket_blkno(xs->bucket),
			index);
	पूर्ण अन्यथा
		ret = -ENODATA;

out:
	ocfs2_xattr_bucket_मुक्त(search);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_index_block_find(काष्ठा inode *inode,
					काष्ठा buffer_head *root_bh,
					पूर्णांक name_index,
					स्थिर अक्षर *name,
					काष्ठा ocfs2_xattr_search *xs)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_xattr_block *xb =
			(काष्ठा ocfs2_xattr_block *)root_bh->b_data;
	काष्ठा ocfs2_xattr_tree_root *xb_root = &xb->xb_attrs.xb_root;
	काष्ठा ocfs2_extent_list *el = &xb_root->xt_list;
	u64 p_blkno = 0;
	u32 first_hash, num_clusters = 0;
	u32 name_hash = ocfs2_xattr_name_hash(inode, name, म_माप(name));

	अगर (le16_to_cpu(el->l_next_मुक्त_rec) == 0)
		वापस -ENODATA;

	trace_ocfs2_xattr_index_block_find(OCFS2_I(inode)->ip_blkno,
					name, name_index, name_hash,
					(अचिन्हित दीर्घ दीर्घ)root_bh->b_blocknr,
					-1);

	ret = ocfs2_xattr_get_rec(inode, name_hash, &p_blkno, &first_hash,
				  &num_clusters, el);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	BUG_ON(p_blkno == 0 || num_clusters == 0 || first_hash > name_hash);

	trace_ocfs2_xattr_index_block_find_rec(OCFS2_I(inode)->ip_blkno,
					name, name_index, first_hash,
					(अचिन्हित दीर्घ दीर्घ)p_blkno,
					num_clusters);

	ret = ocfs2_xattr_bucket_find(inode, name_index, name, name_hash,
				      p_blkno, first_hash, num_clusters, xs);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_iterate_xattr_buckets(काष्ठा inode *inode,
				       u64 blkno,
				       u32 clusters,
				       xattr_bucket_func *func,
				       व्योम *para)
अणु
	पूर्णांक i, ret = 0;
	u32 bpc = ocfs2_xattr_buckets_per_cluster(OCFS2_SB(inode->i_sb));
	u32 num_buckets = clusters * bpc;
	काष्ठा ocfs2_xattr_bucket *bucket;

	bucket = ocfs2_xattr_bucket_new(inode);
	अगर (!bucket) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		वापस -ENOMEM;
	पूर्ण

	trace_ocfs2_iterate_xattr_buckets(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
		(अचिन्हित दीर्घ दीर्घ)blkno, clusters);

	क्रम (i = 0; i < num_buckets; i++, blkno += bucket->bu_blocks) अणु
		ret = ocfs2_पढ़ो_xattr_bucket(bucket, blkno);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		/*
		 * The real bucket num in this series of blocks is stored
		 * in the 1st bucket.
		 */
		अगर (i == 0)
			num_buckets = le16_to_cpu(bucket_xh(bucket)->xh_num_buckets);

		trace_ocfs2_iterate_xattr_bucket((अचिन्हित दीर्घ दीर्घ)blkno,
		     le32_to_cpu(bucket_xh(bucket)->xh_entries[0].xe_name_hash));
		अगर (func) अणु
			ret = func(inode, bucket, para);
			अगर (ret && ret != -दुस्फल)
				mlog_त्रुटि_सं(ret);
			/* Fall through to bucket_rअन्यथा() */
		पूर्ण

		ocfs2_xattr_bucket_rअन्यथा(bucket);
		अगर (ret)
			अवरोध;
	पूर्ण

	ocfs2_xattr_bucket_मुक्त(bucket);
	वापस ret;
पूर्ण

काष्ठा ocfs2_xattr_tree_list अणु
	अक्षर *buffer;
	माप_प्रकार buffer_size;
	माप_प्रकार result;
पूर्ण;

अटल पूर्णांक ocfs2_xattr_bucket_get_name_value(काष्ठा super_block *sb,
					     काष्ठा ocfs2_xattr_header *xh,
					     पूर्णांक index,
					     पूर्णांक *block_off,
					     पूर्णांक *new_offset)
अणु
	u16 name_offset;

	अगर (index < 0 || index >= le16_to_cpu(xh->xh_count))
		वापस -EINVAL;

	name_offset = le16_to_cpu(xh->xh_entries[index].xe_name_offset);

	*block_off = name_offset >> sb->s_blocksize_bits;
	*new_offset = name_offset % sb->s_blocksize;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_list_xattr_bucket(काष्ठा inode *inode,
				   काष्ठा ocfs2_xattr_bucket *bucket,
				   व्योम *para)
अणु
	पूर्णांक ret = 0, type;
	काष्ठा ocfs2_xattr_tree_list *xl = (काष्ठा ocfs2_xattr_tree_list *)para;
	पूर्णांक i, block_off, new_offset;
	स्थिर अक्षर *name;

	क्रम (i = 0 ; i < le16_to_cpu(bucket_xh(bucket)->xh_count); i++) अणु
		काष्ठा ocfs2_xattr_entry *entry = &bucket_xh(bucket)->xh_entries[i];
		type = ocfs2_xattr_get_type(entry);

		ret = ocfs2_xattr_bucket_get_name_value(inode->i_sb,
							bucket_xh(bucket),
							i,
							&block_off,
							&new_offset);
		अगर (ret)
			अवरोध;

		name = (स्थिर अक्षर *)bucket_block(bucket, block_off) +
			new_offset;
		ret = ocfs2_xattr_list_entry(inode->i_sb,
					     xl->buffer,
					     xl->buffer_size,
					     &xl->result,
					     type, name,
					     entry->xe_name_len);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_iterate_xattr_index_block(काष्ठा inode *inode,
					   काष्ठा buffer_head *blk_bh,
					   xattr_tree_rec_func *rec_func,
					   व्योम *para)
अणु
	काष्ठा ocfs2_xattr_block *xb =
			(काष्ठा ocfs2_xattr_block *)blk_bh->b_data;
	काष्ठा ocfs2_extent_list *el = &xb->xb_attrs.xb_root.xt_list;
	पूर्णांक ret = 0;
	u32 name_hash = अच_पूर्णांक_उच्च, e_cpos = 0, num_clusters = 0;
	u64 p_blkno = 0;

	अगर (!el->l_next_मुक्त_rec || !rec_func)
		वापस 0;

	जबतक (name_hash > 0) अणु
		ret = ocfs2_xattr_get_rec(inode, name_hash, &p_blkno,
					  &e_cpos, &num_clusters, el);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = rec_func(inode, blk_bh, p_blkno, e_cpos,
			       num_clusters, para);
		अगर (ret) अणु
			अगर (ret != -दुस्फल)
				mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		अगर (e_cpos == 0)
			अवरोध;

		name_hash = e_cpos - 1;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक ocfs2_list_xattr_tree_rec(काष्ठा inode *inode,
				     काष्ठा buffer_head *root_bh,
				     u64 blkno, u32 cpos, u32 len, व्योम *para)
अणु
	वापस ocfs2_iterate_xattr_buckets(inode, blkno, len,
					   ocfs2_list_xattr_bucket, para);
पूर्ण

अटल पूर्णांक ocfs2_xattr_tree_list_index_block(काष्ठा inode *inode,
					     काष्ठा buffer_head *blk_bh,
					     अक्षर *buffer,
					     माप_प्रकार buffer_size)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_xattr_tree_list xl = अणु
		.buffer = buffer,
		.buffer_size = buffer_size,
		.result = 0,
	पूर्ण;

	ret = ocfs2_iterate_xattr_index_block(inode, blk_bh,
					      ocfs2_list_xattr_tree_rec, &xl);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = xl.result;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक cmp_xe(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा ocfs2_xattr_entry *l = a, *r = b;
	u32 l_hash = le32_to_cpu(l->xe_name_hash);
	u32 r_hash = le32_to_cpu(r->xe_name_hash);

	अगर (l_hash > r_hash)
		वापस 1;
	अगर (l_hash < r_hash)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम swap_xe(व्योम *a, व्योम *b, पूर्णांक size)
अणु
	काष्ठा ocfs2_xattr_entry *l = a, *r = b, पंचांगp;

	पंचांगp = *l;
	स_नकल(l, r, माप(काष्ठा ocfs2_xattr_entry));
	स_नकल(r, &पंचांगp, माप(काष्ठा ocfs2_xattr_entry));
पूर्ण

/*
 * When the ocfs2_xattr_block is filled up, new bucket will be created
 * and all the xattr entries will be moved to the new bucket.
 * The header goes at the start of the bucket, and the names+values are
 * filled from the end.  This is why *target starts as the last buffer.
 * Note: we need to sort the entries since they are not saved in order
 * in the ocfs2_xattr_block.
 */
अटल व्योम ocfs2_cp_xattr_block_to_bucket(काष्ठा inode *inode,
					   काष्ठा buffer_head *xb_bh,
					   काष्ठा ocfs2_xattr_bucket *bucket)
अणु
	पूर्णांक i, blocksize = inode->i_sb->s_blocksize;
	पूर्णांक blks = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	u16 offset, size, off_change;
	काष्ठा ocfs2_xattr_entry *xe;
	काष्ठा ocfs2_xattr_block *xb =
				(काष्ठा ocfs2_xattr_block *)xb_bh->b_data;
	काष्ठा ocfs2_xattr_header *xb_xh = &xb->xb_attrs.xb_header;
	काष्ठा ocfs2_xattr_header *xh = bucket_xh(bucket);
	u16 count = le16_to_cpu(xb_xh->xh_count);
	अक्षर *src = xb_bh->b_data;
	अक्षर *target = bucket_block(bucket, blks - 1);

	trace_ocfs2_cp_xattr_block_to_bucket_begin(
				(अचिन्हित दीर्घ दीर्घ)xb_bh->b_blocknr,
				(अचिन्हित दीर्घ दीर्घ)bucket_blkno(bucket));

	क्रम (i = 0; i < blks; i++)
		स_रखो(bucket_block(bucket, i), 0, blocksize);

	/*
	 * Since the xe_name_offset is based on ocfs2_xattr_header,
	 * there is a offset change corresponding to the change of
	 * ocfs2_xattr_header's position.
	 */
	off_change = दुरत्व(काष्ठा ocfs2_xattr_block, xb_attrs.xb_header);
	xe = &xb_xh->xh_entries[count - 1];
	offset = le16_to_cpu(xe->xe_name_offset) + off_change;
	size = blocksize - offset;

	/* copy all the names and values. */
	स_नकल(target + offset, src + offset, size);

	/* Init new header now. */
	xh->xh_count = xb_xh->xh_count;
	xh->xh_num_buckets = cpu_to_le16(1);
	xh->xh_name_value_len = cpu_to_le16(size);
	xh->xh_मुक्त_start = cpu_to_le16(OCFS2_XATTR_BUCKET_SIZE - size);

	/* copy all the entries. */
	target = bucket_block(bucket, 0);
	offset = दुरत्व(काष्ठा ocfs2_xattr_header, xh_entries);
	size = count * माप(काष्ठा ocfs2_xattr_entry);
	स_नकल(target + offset, (अक्षर *)xb_xh + offset, size);

	/* Change the xe offset क्रम all the xe because of the move. */
	off_change = OCFS2_XATTR_BUCKET_SIZE - blocksize +
		 दुरत्व(काष्ठा ocfs2_xattr_block, xb_attrs.xb_header);
	क्रम (i = 0; i < count; i++)
		le16_add_cpu(&xh->xh_entries[i].xe_name_offset, off_change);

	trace_ocfs2_cp_xattr_block_to_bucket_end(offset, size, off_change);

	sort(target + offset, count, माप(काष्ठा ocfs2_xattr_entry),
	     cmp_xe, swap_xe);
पूर्ण

/*
 * After we move xattr from block to index btree, we have to
 * update ocfs2_xattr_search to the new xe and base.
 *
 * When the entry is in xattr block, xattr_bh indicates the storage place.
 * While अगर the entry is in index b-tree, "bucket" indicates the
 * real place of the xattr.
 */
अटल व्योम ocfs2_xattr_update_xattr_search(काष्ठा inode *inode,
					    काष्ठा ocfs2_xattr_search *xs,
					    काष्ठा buffer_head *old_bh)
अणु
	अक्षर *buf = old_bh->b_data;
	काष्ठा ocfs2_xattr_block *old_xb = (काष्ठा ocfs2_xattr_block *)buf;
	काष्ठा ocfs2_xattr_header *old_xh = &old_xb->xb_attrs.xb_header;
	पूर्णांक i;

	xs->header = bucket_xh(xs->bucket);
	xs->base = bucket_block(xs->bucket, 0);
	xs->end = xs->base + inode->i_sb->s_blocksize;

	अगर (xs->not_found)
		वापस;

	i = xs->here - old_xh->xh_entries;
	xs->here = &xs->header->xh_entries[i];
पूर्ण

अटल पूर्णांक ocfs2_xattr_create_index_block(काष्ठा inode *inode,
					  काष्ठा ocfs2_xattr_search *xs,
					  काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;
	u32 bit_off, len;
	u64 blkno;
	handle_t *handle = ctxt->handle;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा buffer_head *xb_bh = xs->xattr_bh;
	काष्ठा ocfs2_xattr_block *xb =
			(काष्ठा ocfs2_xattr_block *)xb_bh->b_data;
	काष्ठा ocfs2_xattr_tree_root *xr;
	u16 xb_flags = le16_to_cpu(xb->xb_flags);

	trace_ocfs2_xattr_create_index_block_begin(
				(अचिन्हित दीर्घ दीर्घ)xb_bh->b_blocknr);

	BUG_ON(xb_flags & OCFS2_XATTR_INDEXED);
	BUG_ON(!xs->bucket);

	/*
	 * XXX:
	 * We can use this lock क्रम now, and maybe move to a dedicated mutex
	 * अगर perक्रमmance becomes a problem later.
	 */
	करोwn_ग_लिखो(&oi->ip_alloc_sem);

	ret = ocfs2_journal_access_xb(handle, INODE_CACHE(inode), xb_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = __ocfs2_claim_clusters(handle, ctxt->data_ac,
				     1, 1, &bit_off, &len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * The bucket may spपढ़ो in many blocks, and
	 * we will only touch the 1st block and the last block
	 * in the whole bucket(one क्रम entry and one क्रम data).
	 */
	blkno = ocfs2_clusters_to_blocks(inode->i_sb, bit_off);

	trace_ocfs2_xattr_create_index_block((अचिन्हित दीर्घ दीर्घ)blkno);

	ret = ocfs2_init_xattr_bucket(xs->bucket, blkno, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xattr_bucket_journal_access(handle, xs->bucket,
						OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_cp_xattr_block_to_bucket(inode, xb_bh, xs->bucket);
	ocfs2_xattr_bucket_journal_dirty(handle, xs->bucket);

	ocfs2_xattr_update_xattr_search(inode, xs, xb_bh);

	/* Change from ocfs2_xattr_header to ocfs2_xattr_tree_root */
	स_रखो(&xb->xb_attrs, 0, inode->i_sb->s_blocksize -
	       दुरत्व(काष्ठा ocfs2_xattr_block, xb_attrs));

	xr = &xb->xb_attrs.xb_root;
	xr->xt_clusters = cpu_to_le32(1);
	xr->xt_last_eb_blk = 0;
	xr->xt_list.l_tree_depth = 0;
	xr->xt_list.l_count = cpu_to_le16(ocfs2_xattr_recs_per_xb(inode->i_sb));
	xr->xt_list.l_next_मुक्त_rec = cpu_to_le16(1);

	xr->xt_list.l_recs[0].e_cpos = 0;
	xr->xt_list.l_recs[0].e_blkno = cpu_to_le64(blkno);
	xr->xt_list.l_recs[0].e_leaf_clusters = cpu_to_le16(1);

	xb->xb_flags = cpu_to_le16(xb_flags | OCFS2_XATTR_INDEXED);

	ocfs2_journal_dirty(handle, xb_bh);

out:
	up_ग_लिखो(&oi->ip_alloc_sem);

	वापस ret;
पूर्ण

अटल पूर्णांक cmp_xe_offset(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा ocfs2_xattr_entry *l = a, *r = b;
	u32 l_name_offset = le16_to_cpu(l->xe_name_offset);
	u32 r_name_offset = le16_to_cpu(r->xe_name_offset);

	अगर (l_name_offset < r_name_offset)
		वापस 1;
	अगर (l_name_offset > r_name_offset)
		वापस -1;
	वापस 0;
पूर्ण

/*
 * defrag a xattr bucket अगर we find that the bucket has some
 * holes beteen name/value pairs.
 * We will move all the name/value pairs to the end of the bucket
 * so that we can spare some space क्रम insertion.
 */
अटल पूर्णांक ocfs2_defrag_xattr_bucket(काष्ठा inode *inode,
				     handle_t *handle,
				     काष्ठा ocfs2_xattr_bucket *bucket)
अणु
	पूर्णांक ret, i;
	माप_प्रकार end, offset, len;
	काष्ठा ocfs2_xattr_header *xh;
	अक्षर *entries, *buf, *bucket_buf = शून्य;
	u64 blkno = bucket_blkno(bucket);
	u16 xh_मुक्त_start;
	माप_प्रकार blocksize = inode->i_sb->s_blocksize;
	काष्ठा ocfs2_xattr_entry *xe;

	/*
	 * In order to make the operation more efficient and generic,
	 * we copy all the blocks पूर्णांकo a contiguous memory and करो the
	 * defragment there, so अगर anything is error, we will not touch
	 * the real block.
	 */
	bucket_buf = kदो_स्मृति(OCFS2_XATTR_BUCKET_SIZE, GFP_NOFS);
	अगर (!bucket_buf) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	buf = bucket_buf;
	क्रम (i = 0; i < bucket->bu_blocks; i++, buf += blocksize)
		स_नकल(buf, bucket_block(bucket, i), blocksize);

	ret = ocfs2_xattr_bucket_journal_access(handle, bucket,
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	xh = (काष्ठा ocfs2_xattr_header *)bucket_buf;
	entries = (अक्षर *)xh->xh_entries;
	xh_मुक्त_start = le16_to_cpu(xh->xh_मुक्त_start);

	trace_ocfs2_defrag_xattr_bucket(
	     (अचिन्हित दीर्घ दीर्घ)blkno, le16_to_cpu(xh->xh_count),
	     xh_मुक्त_start, le16_to_cpu(xh->xh_name_value_len));

	/*
	 * sort all the entries by their offset.
	 * the largest will be the first, so that we can
	 * move them to the end one by one.
	 */
	sort(entries, le16_to_cpu(xh->xh_count),
	     माप(काष्ठा ocfs2_xattr_entry),
	     cmp_xe_offset, swap_xe);

	/* Move all name/values to the end of the bucket. */
	xe = xh->xh_entries;
	end = OCFS2_XATTR_BUCKET_SIZE;
	क्रम (i = 0; i < le16_to_cpu(xh->xh_count); i++, xe++) अणु
		offset = le16_to_cpu(xe->xe_name_offset);
		len = namevalue_size_xe(xe);

		/*
		 * We must make sure that the name/value pair
		 * exist in the same block. So adjust end to
		 * the previous block end अगर needed.
		 */
		अगर (((end - len) / blocksize !=
			(end - 1) / blocksize))
			end = end - end % blocksize;

		अगर (end > offset + len) अणु
			स_हटाओ(bucket_buf + end - len,
				bucket_buf + offset, len);
			xe->xe_name_offset = cpu_to_le16(end - len);
		पूर्ण

		mlog_bug_on_msg(end < offset + len, "Defrag check failed for "
				"bucket %llu\n", (अचिन्हित दीर्घ दीर्घ)blkno);

		end -= len;
	पूर्ण

	mlog_bug_on_msg(xh_मुक्त_start > end, "Defrag check failed for "
			"bucket %llu\n", (अचिन्हित दीर्घ दीर्घ)blkno);

	अगर (xh_मुक्त_start == end)
		जाओ out;

	स_रखो(bucket_buf + xh_मुक्त_start, 0, end - xh_मुक्त_start);
	xh->xh_मुक्त_start = cpu_to_le16(end);

	/* sort the entries by their name_hash. */
	sort(entries, le16_to_cpu(xh->xh_count),
	     माप(काष्ठा ocfs2_xattr_entry),
	     cmp_xe, swap_xe);

	buf = bucket_buf;
	क्रम (i = 0; i < bucket->bu_blocks; i++, buf += blocksize)
		स_नकल(bucket_block(bucket, i), buf, blocksize);
	ocfs2_xattr_bucket_journal_dirty(handle, bucket);

out:
	kमुक्त(bucket_buf);
	वापस ret;
पूर्ण

/*
 * prev_blkno poपूर्णांकs to the start of an existing extent.  new_blkno
 * poपूर्णांकs to a newly allocated extent.  Because we know each of our
 * clusters contains more than bucket, we can easily split one cluster
 * at a bucket boundary.  So we take the last cluster of the existing
 * extent and split it करोwn the middle.  We move the last half of the
 * buckets in the last cluster of the existing extent over to the new
 * extent.
 *
 * first_bh is the buffer at prev_blkno so we can update the existing
 * extent's bucket count.  header_bh is the bucket were we were hoping
 * to insert our xattr.  If the bucket move places the target in the new
 * extent, we'll update first_bh and header_bh after modअगरying the old
 * extent.
 *
 * first_hash will be set as the 1st xe's name_hash in the new extent.
 */
अटल पूर्णांक ocfs2_mv_xattr_bucket_cross_cluster(काष्ठा inode *inode,
					       handle_t *handle,
					       काष्ठा ocfs2_xattr_bucket *first,
					       काष्ठा ocfs2_xattr_bucket *target,
					       u64 new_blkno,
					       u32 num_clusters,
					       u32 *first_hash)
अणु
	पूर्णांक ret;
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक blks_per_bucket = ocfs2_blocks_per_xattr_bucket(sb);
	पूर्णांक num_buckets = ocfs2_xattr_buckets_per_cluster(OCFS2_SB(sb));
	पूर्णांक to_move = num_buckets / 2;
	u64 src_blkno;
	u64 last_cluster_blkno = bucket_blkno(first) +
		((num_clusters - 1) * ocfs2_clusters_to_blocks(sb, 1));

	BUG_ON(le16_to_cpu(bucket_xh(first)->xh_num_buckets) < num_buckets);
	BUG_ON(OCFS2_XATTR_BUCKET_SIZE == OCFS2_SB(sb)->s_clustersize);

	trace_ocfs2_mv_xattr_bucket_cross_cluster(
				(अचिन्हित दीर्घ दीर्घ)last_cluster_blkno,
				(अचिन्हित दीर्घ दीर्घ)new_blkno);

	ret = ocfs2_mv_xattr_buckets(inode, handle, bucket_blkno(first),
				     last_cluster_blkno, new_blkno,
				     to_move, first_hash);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* This is the first bucket that got moved */
	src_blkno = last_cluster_blkno + (to_move * blks_per_bucket);

	/*
	 * If the target bucket was part of the moved buckets, we need to
	 * update first and target.
	 */
	अगर (bucket_blkno(target) >= src_blkno) अणु
		/* Find the block क्रम the new target bucket */
		src_blkno = new_blkno +
			(bucket_blkno(target) - src_blkno);

		ocfs2_xattr_bucket_rअन्यथा(first);
		ocfs2_xattr_bucket_rअन्यथा(target);

		/*
		 * These shouldn't fail - the buffers are in the
		 * journal from ocfs2_cp_xattr_bucket().
		 */
		ret = ocfs2_पढ़ो_xattr_bucket(first, new_blkno);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		ret = ocfs2_पढ़ो_xattr_bucket(target, src_blkno);
		अगर (ret)
			mlog_त्रुटि_सं(ret);

	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * Find the suitable pos when we भागide a bucket पूर्णांकo 2.
 * We have to make sure the xattrs with the same hash value exist
 * in the same bucket.
 *
 * If this ocfs2_xattr_header covers more than one hash value, find a
 * place where the hash value changes.  Try to find the most even split.
 * The most common हाल is that all entries have dअगरferent hash values,
 * and the first check we make will find a place to split.
 */
अटल पूर्णांक ocfs2_xattr_find_भागide_pos(काष्ठा ocfs2_xattr_header *xh)
अणु
	काष्ठा ocfs2_xattr_entry *entries = xh->xh_entries;
	पूर्णांक count = le16_to_cpu(xh->xh_count);
	पूर्णांक delta, middle = count / 2;

	/*
	 * We start at the middle.  Each step माला_लो farther away in both
	 * directions.  We thereक्रमe hit the change in hash value
	 * nearest to the middle.  Note that this loop करोes not execute क्रम
	 * count < 2.
	 */
	क्रम (delta = 0; delta < middle; delta++) अणु
		/* Let's check delta earlier than middle */
		अगर (cmp_xe(&entries[middle - delta - 1],
			   &entries[middle - delta]))
			वापस middle - delta;

		/* For even counts, करोn't walk off the end */
		अगर ((middle + delta + 1) == count)
			जारी;

		/* Now try delta past middle */
		अगर (cmp_xe(&entries[middle + delta],
			   &entries[middle + delta + 1]))
			वापस middle + delta + 1;
	पूर्ण

	/* Every entry had the same hash */
	वापस count;
पूर्ण

/*
 * Move some xattrs in old bucket(blk) to new bucket(new_blk).
 * first_hash will record the 1st hash of the new bucket.
 *
 * Normally half of the xattrs will be moved.  But we have to make
 * sure that the xattrs with the same hash value are stored in the
 * same bucket. If all the xattrs in this bucket have the same hash
 * value, the new bucket will be initialized as an empty one and the
 * first_hash will be initialized as (hash_value+1).
 */
अटल पूर्णांक ocfs2_भागide_xattr_bucket(काष्ठा inode *inode,
				    handle_t *handle,
				    u64 blk,
				    u64 new_blk,
				    u32 *first_hash,
				    पूर्णांक new_bucket_head)
अणु
	पूर्णांक ret, i;
	पूर्णांक count, start, len, name_value_len = 0, name_offset = 0;
	काष्ठा ocfs2_xattr_bucket *s_bucket = शून्य, *t_bucket = शून्य;
	काष्ठा ocfs2_xattr_header *xh;
	काष्ठा ocfs2_xattr_entry *xe;
	पूर्णांक blocksize = inode->i_sb->s_blocksize;

	trace_ocfs2_भागide_xattr_bucket_begin((अचिन्हित दीर्घ दीर्घ)blk,
					      (अचिन्हित दीर्घ दीर्घ)new_blk);

	s_bucket = ocfs2_xattr_bucket_new(inode);
	t_bucket = ocfs2_xattr_bucket_new(inode);
	अगर (!s_bucket || !t_bucket) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_xattr_bucket(s_bucket, blk);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xattr_bucket_journal_access(handle, s_bucket,
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Even अगर !new_bucket_head, we're overwriting t_bucket.  Thus,
	 * there's no need to पढ़ो it.
	 */
	ret = ocfs2_init_xattr_bucket(t_bucket, new_blk, new_bucket_head);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Hey, अगर we're overwriting t_bucket, what dअगरference करोes
	 * ACCESS_CREATE vs ACCESS_WRITE make?  See the comment in the
	 * same part of ocfs2_cp_xattr_bucket().
	 */
	ret = ocfs2_xattr_bucket_journal_access(handle, t_bucket,
						new_bucket_head ?
						OCFS2_JOURNAL_ACCESS_CREATE :
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	xh = bucket_xh(s_bucket);
	count = le16_to_cpu(xh->xh_count);
	start = ocfs2_xattr_find_भागide_pos(xh);

	अगर (start == count) अणु
		xe = &xh->xh_entries[start-1];

		/*
		 * initialized a new empty bucket here.
		 * The hash value is set as one larger than
		 * that of the last entry in the previous bucket.
		 */
		क्रम (i = 0; i < t_bucket->bu_blocks; i++)
			स_रखो(bucket_block(t_bucket, i), 0, blocksize);

		xh = bucket_xh(t_bucket);
		xh->xh_मुक्त_start = cpu_to_le16(blocksize);
		xh->xh_entries[0].xe_name_hash = xe->xe_name_hash;
		le32_add_cpu(&xh->xh_entries[0].xe_name_hash, 1);

		जाओ set_num_buckets;
	पूर्ण

	/* copy the whole bucket to the new first. */
	ocfs2_xattr_bucket_copy_data(t_bucket, s_bucket);

	/* update the new bucket. */
	xh = bucket_xh(t_bucket);

	/*
	 * Calculate the total name/value len and xh_मुक्त_start क्रम
	 * the old bucket first.
	 */
	name_offset = OCFS2_XATTR_BUCKET_SIZE;
	name_value_len = 0;
	क्रम (i = 0; i < start; i++) अणु
		xe = &xh->xh_entries[i];
		name_value_len += namevalue_size_xe(xe);
		अगर (le16_to_cpu(xe->xe_name_offset) < name_offset)
			name_offset = le16_to_cpu(xe->xe_name_offset);
	पूर्ण

	/*
	 * Now begin the modअगरication to the new bucket.
	 *
	 * In the new bucket, We just move the xattr entry to the beginning
	 * and करोn't touch the name/value. So there will be some holes in the
	 * bucket, and they will be हटाओd when ocfs2_defrag_xattr_bucket is
	 * called.
	 */
	xe = &xh->xh_entries[start];
	len = माप(काष्ठा ocfs2_xattr_entry) * (count - start);
	trace_ocfs2_भागide_xattr_bucket_move(len,
			(पूर्णांक)((अक्षर *)xe - (अक्षर *)xh),
			(पूर्णांक)((अक्षर *)xh->xh_entries - (अक्षर *)xh));
	स_हटाओ((अक्षर *)xh->xh_entries, (अक्षर *)xe, len);
	xe = &xh->xh_entries[count - start];
	len = माप(काष्ठा ocfs2_xattr_entry) * start;
	स_रखो((अक्षर *)xe, 0, len);

	le16_add_cpu(&xh->xh_count, -start);
	le16_add_cpu(&xh->xh_name_value_len, -name_value_len);

	/* Calculate xh_मुक्त_start क्रम the new bucket. */
	xh->xh_मुक्त_start = cpu_to_le16(OCFS2_XATTR_BUCKET_SIZE);
	क्रम (i = 0; i < le16_to_cpu(xh->xh_count); i++) अणु
		xe = &xh->xh_entries[i];
		अगर (le16_to_cpu(xe->xe_name_offset) <
		    le16_to_cpu(xh->xh_मुक्त_start))
			xh->xh_मुक्त_start = xe->xe_name_offset;
	पूर्ण

set_num_buckets:
	/* set xh->xh_num_buckets क्रम the new xh. */
	अगर (new_bucket_head)
		xh->xh_num_buckets = cpu_to_le16(1);
	अन्यथा
		xh->xh_num_buckets = 0;

	ocfs2_xattr_bucket_journal_dirty(handle, t_bucket);

	/* store the first_hash of the new bucket. */
	अगर (first_hash)
		*first_hash = le32_to_cpu(xh->xh_entries[0].xe_name_hash);

	/*
	 * Now only update the 1st block of the old bucket.  If we
	 * just added a new empty bucket, there is no need to modअगरy
	 * it.
	 */
	अगर (start == count)
		जाओ out;

	xh = bucket_xh(s_bucket);
	स_रखो(&xh->xh_entries[start], 0,
	       माप(काष्ठा ocfs2_xattr_entry) * (count - start));
	xh->xh_count = cpu_to_le16(start);
	xh->xh_मुक्त_start = cpu_to_le16(name_offset);
	xh->xh_name_value_len = cpu_to_le16(name_value_len);

	ocfs2_xattr_bucket_journal_dirty(handle, s_bucket);

out:
	ocfs2_xattr_bucket_मुक्त(s_bucket);
	ocfs2_xattr_bucket_मुक्त(t_bucket);

	वापस ret;
पूर्ण

/*
 * Copy xattr from one bucket to another bucket.
 *
 * The caller must make sure that the journal transaction
 * has enough space क्रम journaling.
 */
अटल पूर्णांक ocfs2_cp_xattr_bucket(काष्ठा inode *inode,
				 handle_t *handle,
				 u64 s_blkno,
				 u64 t_blkno,
				 पूर्णांक t_is_new)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_xattr_bucket *s_bucket = शून्य, *t_bucket = शून्य;

	BUG_ON(s_blkno == t_blkno);

	trace_ocfs2_cp_xattr_bucket((अचिन्हित दीर्घ दीर्घ)s_blkno,
				    (अचिन्हित दीर्घ दीर्घ)t_blkno,
				    t_is_new);

	s_bucket = ocfs2_xattr_bucket_new(inode);
	t_bucket = ocfs2_xattr_bucket_new(inode);
	अगर (!s_bucket || !t_bucket) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_xattr_bucket(s_bucket, s_blkno);
	अगर (ret)
		जाओ out;

	/*
	 * Even अगर !t_is_new, we're overwriting t_bucket.  Thus,
	 * there's no need to पढ़ो it.
	 */
	ret = ocfs2_init_xattr_bucket(t_bucket, t_blkno, t_is_new);
	अगर (ret)
		जाओ out;

	/*
	 * Hey, अगर we're overwriting t_bucket, what dअगरference करोes
	 * ACCESS_CREATE vs ACCESS_WRITE make?  Well, अगर we allocated a new
	 * cluster to fill, we came here from
	 * ocfs2_mv_xattr_buckets(), and it is really new -
	 * ACCESS_CREATE is required.  But we also might have moved data
	 * out of t_bucket beक्रमe extending back पूर्णांकo it.
	 * ocfs2_add_new_xattr_bucket() can करो this - its call to
	 * ocfs2_add_new_xattr_cluster() may have created a new extent
	 * and copied out the end of the old extent.  Then it re-extends
	 * the old extent back to create space क्रम new xattrs.  That's
	 * how we get here, and the bucket isn't really new.
	 */
	ret = ocfs2_xattr_bucket_journal_access(handle, t_bucket,
						t_is_new ?
						OCFS2_JOURNAL_ACCESS_CREATE :
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret)
		जाओ out;

	ocfs2_xattr_bucket_copy_data(t_bucket, s_bucket);
	ocfs2_xattr_bucket_journal_dirty(handle, t_bucket);

out:
	ocfs2_xattr_bucket_मुक्त(t_bucket);
	ocfs2_xattr_bucket_मुक्त(s_bucket);

	वापस ret;
पूर्ण

/*
 * src_blk poपूर्णांकs to the start of an existing extent.  last_blk poपूर्णांकs to
 * last cluster in that extent.  to_blk poपूर्णांकs to a newly allocated
 * extent.  We copy the buckets from the cluster at last_blk to the new
 * extent.  If start_bucket is non-zero, we skip that many buckets beक्रमe
 * we start copying.  The new extent's xh_num_buckets माला_लो set to the
 * number of buckets we copied.  The old extent's xh_num_buckets shrinks
 * by the same amount.
 */
अटल पूर्णांक ocfs2_mv_xattr_buckets(काष्ठा inode *inode, handle_t *handle,
				  u64 src_blk, u64 last_blk, u64 to_blk,
				  अचिन्हित पूर्णांक start_bucket,
				  u32 *first_hash)
अणु
	पूर्णांक i, ret, credits;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	पूर्णांक blks_per_bucket = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	पूर्णांक num_buckets = ocfs2_xattr_buckets_per_cluster(osb);
	काष्ठा ocfs2_xattr_bucket *old_first, *new_first;

	trace_ocfs2_mv_xattr_buckets((अचिन्हित दीर्घ दीर्घ)last_blk,
				     (अचिन्हित दीर्घ दीर्घ)to_blk);

	BUG_ON(start_bucket >= num_buckets);
	अगर (start_bucket) अणु
		num_buckets -= start_bucket;
		last_blk += (start_bucket * blks_per_bucket);
	पूर्ण

	/* The first bucket of the original extent */
	old_first = ocfs2_xattr_bucket_new(inode);
	/* The first bucket of the new extent */
	new_first = ocfs2_xattr_bucket_new(inode);
	अगर (!old_first || !new_first) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_xattr_bucket(old_first, src_blk);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * We need to update the first bucket of the old extent and all
	 * the buckets going to the new extent.
	 */
	credits = ((num_buckets + 1) * blks_per_bucket);
	ret = ocfs2_extend_trans(handle, credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xattr_bucket_journal_access(handle, old_first,
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_buckets; i++) अणु
		ret = ocfs2_cp_xattr_bucket(inode, handle,
					    last_blk + (i * blks_per_bucket),
					    to_blk + (i * blks_per_bucket),
					    1);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Get the new bucket पढ़ोy beक्रमe we dirty anything
	 * (This actually shouldn't fail, because we alपढ़ोy dirtied
	 * it once in ocfs2_cp_xattr_bucket()).
	 */
	ret = ocfs2_पढ़ो_xattr_bucket(new_first, to_blk);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	ret = ocfs2_xattr_bucket_journal_access(handle, new_first,
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* Now update the headers */
	le16_add_cpu(&bucket_xh(old_first)->xh_num_buckets, -num_buckets);
	ocfs2_xattr_bucket_journal_dirty(handle, old_first);

	bucket_xh(new_first)->xh_num_buckets = cpu_to_le16(num_buckets);
	ocfs2_xattr_bucket_journal_dirty(handle, new_first);

	अगर (first_hash)
		*first_hash = le32_to_cpu(bucket_xh(new_first)->xh_entries[0].xe_name_hash);

out:
	ocfs2_xattr_bucket_मुक्त(new_first);
	ocfs2_xattr_bucket_मुक्त(old_first);
	वापस ret;
पूर्ण

/*
 * Move some xattrs in this cluster to the new cluster.
 * This function should only be called when bucket size == cluster size.
 * Otherwise ocfs2_mv_xattr_bucket_cross_cluster should be used instead.
 */
अटल पूर्णांक ocfs2_भागide_xattr_cluster(काष्ठा inode *inode,
				      handle_t *handle,
				      u64 prev_blk,
				      u64 new_blk,
				      u32 *first_hash)
अणु
	u16 blk_per_bucket = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	पूर्णांक ret, credits = 2 * blk_per_bucket;

	BUG_ON(OCFS2_XATTR_BUCKET_SIZE < OCFS2_SB(inode->i_sb)->s_clustersize);

	ret = ocfs2_extend_trans(handle, credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	/* Move half of the xattr in start_blk to the next bucket. */
	वापस  ocfs2_भागide_xattr_bucket(inode, handle, prev_blk,
					  new_blk, first_hash, 1);
पूर्ण

/*
 * Move some xattrs from the old cluster to the new one since they are not
 * contiguous in ocfs2 xattr tree.
 *
 * new_blk starts a new separate cluster, and we will move some xattrs from
 * prev_blk to it. v_start will be set as the first name hash value in this
 * new cluster so that it can be used as e_cpos during tree insertion and
 * करोn't collide with our original b-tree operations. first_bh and header_bh
 * will also be updated since they will be used in ocfs2_extend_xattr_bucket
 * to extend the insert bucket.
 *
 * The problem is how much xattr should we move to the new one and when should
 * we update first_bh and header_bh?
 * 1. If cluster size > bucket size, that means the previous cluster has more
 *    than 1 bucket, so just move half nums of bucket पूर्णांकo the new cluster and
 *    update the first_bh and header_bh अगर the insert bucket has been moved
 *    to the new cluster.
 * 2. If cluster_size == bucket_size:
 *    a) If the previous extent rec has more than one cluster and the insert
 *       place isn't in the last cluster, copy the entire last cluster to the
 *       new one. This समय, we करोn't need to upate the first_bh and header_bh
 *       since they will not be moved पूर्णांकo the new cluster.
 *    b) Otherwise, move the bottom half of the xattrs in the last cluster पूर्णांकo
 *       the new one. And we set the extend flag to zero अगर the insert place is
 *       moved पूर्णांकo the new allocated cluster since no extend is needed.
 */
अटल पूर्णांक ocfs2_adjust_xattr_cross_cluster(काष्ठा inode *inode,
					    handle_t *handle,
					    काष्ठा ocfs2_xattr_bucket *first,
					    काष्ठा ocfs2_xattr_bucket *target,
					    u64 new_blk,
					    u32 prev_clusters,
					    u32 *v_start,
					    पूर्णांक *extend)
अणु
	पूर्णांक ret;

	trace_ocfs2_adjust_xattr_cross_cluster(
			(अचिन्हित दीर्घ दीर्घ)bucket_blkno(first),
			(अचिन्हित दीर्घ दीर्घ)new_blk, prev_clusters);

	अगर (ocfs2_xattr_buckets_per_cluster(OCFS2_SB(inode->i_sb)) > 1) अणु
		ret = ocfs2_mv_xattr_bucket_cross_cluster(inode,
							  handle,
							  first, target,
							  new_blk,
							  prev_clusters,
							  v_start);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण अन्यथा अणु
		/* The start of the last cluster in the first extent */
		u64 last_blk = bucket_blkno(first) +
			((prev_clusters - 1) *
			 ocfs2_clusters_to_blocks(inode->i_sb, 1));

		अगर (prev_clusters > 1 && bucket_blkno(target) != last_blk) अणु
			ret = ocfs2_mv_xattr_buckets(inode, handle,
						     bucket_blkno(first),
						     last_blk, new_blk, 0,
						     v_start);
			अगर (ret)
				mlog_त्रुटि_सं(ret);
		पूर्ण अन्यथा अणु
			ret = ocfs2_भागide_xattr_cluster(inode, handle,
							 last_blk, new_blk,
							 v_start);
			अगर (ret)
				mlog_त्रुटि_सं(ret);

			अगर ((bucket_blkno(target) == last_blk) && extend)
				*extend = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Add a new cluster क्रम xattr storage.
 *
 * If the new cluster is contiguous with the previous one, it will be
 * appended to the same extent record, and num_clusters will be updated.
 * If not, we will insert a new extent क्रम it and move some xattrs in
 * the last cluster पूर्णांकo the new allocated one.
 * We also need to limit the maximum size of a btree leaf, otherwise we'll
 * lose the benefits of hashing because we'll have to search large leaves.
 * So now the maximum size is OCFS2_MAX_XATTR_TREE_LEAF_SIZE(or clustersize,
 * अगर it's bigger).
 *
 * first_bh is the first block of the previous extent rec and header_bh
 * indicates the bucket we will insert the new xattrs. They will be updated
 * when the header_bh is moved पूर्णांकo the new cluster.
 */
अटल पूर्णांक ocfs2_add_new_xattr_cluster(काष्ठा inode *inode,
				       काष्ठा buffer_head *root_bh,
				       काष्ठा ocfs2_xattr_bucket *first,
				       काष्ठा ocfs2_xattr_bucket *target,
				       u32 *num_clusters,
				       u32 prev_cpos,
				       पूर्णांक *extend,
				       काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;
	u16 bpc = ocfs2_clusters_to_blocks(inode->i_sb, 1);
	u32 prev_clusters = *num_clusters;
	u32 clusters_to_add = 1, bit_off, num_bits, v_start = 0;
	u64 block;
	handle_t *handle = ctxt->handle;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_extent_tree et;

	trace_ocfs2_add_new_xattr_cluster_begin(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
		(अचिन्हित दीर्घ दीर्घ)bucket_blkno(first),
		prev_cpos, prev_clusters);

	ocfs2_init_xattr_tree_extent_tree(&et, INODE_CACHE(inode), root_bh);

	ret = ocfs2_journal_access_xb(handle, INODE_CACHE(inode), root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	ret = __ocfs2_claim_clusters(handle, ctxt->data_ac, 1,
				     clusters_to_add, &bit_off, &num_bits);
	अगर (ret < 0) अणु
		अगर (ret != -ENOSPC)
			mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	BUG_ON(num_bits > clusters_to_add);

	block = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	trace_ocfs2_add_new_xattr_cluster((अचिन्हित दीर्घ दीर्घ)block, num_bits);

	अगर (bucket_blkno(first) + (prev_clusters * bpc) == block &&
	    (prev_clusters + num_bits) << osb->s_clustersize_bits <=
	     OCFS2_MAX_XATTR_TREE_LEAF_SIZE) अणु
		/*
		 * If this cluster is contiguous with the old one and
		 * adding this new cluster, we करोn't surpass the limit of
		 * OCFS2_MAX_XATTR_TREE_LEAF_SIZE, cool. We will let it be
		 * initialized and used like other buckets in the previous
		 * cluster.
		 * So add it as a contiguous one. The caller will handle
		 * its init process.
		 */
		v_start = prev_cpos + prev_clusters;
		*num_clusters = prev_clusters + num_bits;
	पूर्ण अन्यथा अणु
		ret = ocfs2_adjust_xattr_cross_cluster(inode,
						       handle,
						       first,
						       target,
						       block,
						       prev_clusters,
						       &v_start,
						       extend);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ leave;
		पूर्ण
	पूर्ण

	trace_ocfs2_add_new_xattr_cluster_insert((अचिन्हित दीर्घ दीर्घ)block,
						 v_start, num_bits);
	ret = ocfs2_insert_extent(handle, &et, v_start, block,
				  num_bits, 0, ctxt->meta_ac);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	ocfs2_journal_dirty(handle, root_bh);

leave:
	वापस ret;
पूर्ण

/*
 * We are given an extent.  'first' is the bucket at the very front of
 * the extent.  The extent has space क्रम an additional bucket past
 * bucket_xh(first)->xh_num_buckets.  'target_blkno' is the block number
 * of the target bucket.  We wish to shअगरt every bucket past the target
 * करोwn one, filling in that additional space.  When we get back to the
 * target, we split the target between itself and the now-empty bucket
 * at target+1 (aka, target_blkno + blks_per_bucket).
 */
अटल पूर्णांक ocfs2_extend_xattr_bucket(काष्ठा inode *inode,
				     handle_t *handle,
				     काष्ठा ocfs2_xattr_bucket *first,
				     u64 target_blk,
				     u32 num_clusters)
अणु
	पूर्णांक ret, credits;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u16 blk_per_bucket = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	u64 end_blk;
	u16 new_bucket = le16_to_cpu(bucket_xh(first)->xh_num_buckets);

	trace_ocfs2_extend_xattr_bucket((अचिन्हित दीर्घ दीर्घ)target_blk,
					(अचिन्हित दीर्घ दीर्घ)bucket_blkno(first),
					num_clusters, new_bucket);

	/* The extent must have room क्रम an additional bucket */
	BUG_ON(new_bucket >=
	       (num_clusters * ocfs2_xattr_buckets_per_cluster(osb)));

	/* end_blk poपूर्णांकs to the last existing bucket */
	end_blk = bucket_blkno(first) + ((new_bucket - 1) * blk_per_bucket);

	/*
	 * end_blk is the start of the last existing bucket.
	 * Thus, (end_blk - target_blk) covers the target bucket and
	 * every bucket after it up to, but not including, the last
	 * existing bucket.  Then we add the last existing bucket, the
	 * new bucket, and the first bucket (3 * blk_per_bucket).
	 */
	credits = (end_blk - target_blk) + (3 * blk_per_bucket);
	ret = ocfs2_extend_trans(handle, credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xattr_bucket_journal_access(handle, first,
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	जबतक (end_blk != target_blk) अणु
		ret = ocfs2_cp_xattr_bucket(inode, handle, end_blk,
					    end_blk + blk_per_bucket, 0);
		अगर (ret)
			जाओ out;
		end_blk -= blk_per_bucket;
	पूर्ण

	/* Move half of the xattr in target_blkno to the next bucket. */
	ret = ocfs2_भागide_xattr_bucket(inode, handle, target_blk,
					target_blk + blk_per_bucket, शून्य, 0);

	le16_add_cpu(&bucket_xh(first)->xh_num_buckets, 1);
	ocfs2_xattr_bucket_journal_dirty(handle, first);

out:
	वापस ret;
पूर्ण

/*
 * Add new xattr bucket in an extent record and adjust the buckets
 * accordingly.  xb_bh is the ocfs2_xattr_block, and target is the
 * bucket we want to insert पूर्णांकo.
 *
 * In the easy हाल, we will move all the buckets after target करोwn by
 * one. Half of target's xattrs will be moved to the next bucket.
 *
 * If current cluster is full, we'll allocate a new one.  This may not
 * be contiguous.  The underlying calls will make sure that there is
 * space क्रम the insert, shअगरting buckets around अगर necessary.
 * 'target' may be moved by those calls.
 */
अटल पूर्णांक ocfs2_add_new_xattr_bucket(काष्ठा inode *inode,
				      काष्ठा buffer_head *xb_bh,
				      काष्ठा ocfs2_xattr_bucket *target,
				      काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	काष्ठा ocfs2_xattr_block *xb =
			(काष्ठा ocfs2_xattr_block *)xb_bh->b_data;
	काष्ठा ocfs2_xattr_tree_root *xb_root = &xb->xb_attrs.xb_root;
	काष्ठा ocfs2_extent_list *el = &xb_root->xt_list;
	u32 name_hash =
		le32_to_cpu(bucket_xh(target)->xh_entries[0].xe_name_hash);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	पूर्णांक ret, num_buckets, extend = 1;
	u64 p_blkno;
	u32 e_cpos, num_clusters;
	/* The bucket at the front of the extent */
	काष्ठा ocfs2_xattr_bucket *first;

	trace_ocfs2_add_new_xattr_bucket(
				(अचिन्हित दीर्घ दीर्घ)bucket_blkno(target));

	/* The first bucket of the original extent */
	first = ocfs2_xattr_bucket_new(inode);
	अगर (!first) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xattr_get_rec(inode, name_hash, &p_blkno, &e_cpos,
				  &num_clusters, el);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_xattr_bucket(first, p_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	num_buckets = ocfs2_xattr_buckets_per_cluster(osb) * num_clusters;
	अगर (num_buckets == le16_to_cpu(bucket_xh(first)->xh_num_buckets)) अणु
		/*
		 * This can move first+target अगर the target bucket moves
		 * to the new extent.
		 */
		ret = ocfs2_add_new_xattr_cluster(inode,
						  xb_bh,
						  first,
						  target,
						  &num_clusters,
						  e_cpos,
						  &extend,
						  ctxt);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (extend) अणु
		ret = ocfs2_extend_xattr_bucket(inode,
						ctxt->handle,
						first,
						bucket_blkno(target),
						num_clusters);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

out:
	ocfs2_xattr_bucket_मुक्त(first);

	वापस ret;
पूर्ण

/*
 * Truncate the specअगरied xe_off entry in xattr bucket.
 * bucket is indicated by header_bh and len is the new length.
 * Both the ocfs2_xattr_value_root and the entry will be updated here.
 *
 * Copy the new updated xe and xe_value_root to new_xe and new_xv अगर needed.
 */
अटल पूर्णांक ocfs2_xattr_bucket_value_truncate(काष्ठा inode *inode,
					     काष्ठा ocfs2_xattr_bucket *bucket,
					     पूर्णांक xe_off,
					     पूर्णांक len,
					     काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret, offset;
	u64 value_blk;
	काष्ठा ocfs2_xattr_entry *xe;
	काष्ठा ocfs2_xattr_header *xh = bucket_xh(bucket);
	माप_प्रकार blocksize = inode->i_sb->s_blocksize;
	काष्ठा ocfs2_xattr_value_buf vb = अणु
		.vb_access = ocfs2_journal_access,
	पूर्ण;

	xe = &xh->xh_entries[xe_off];

	BUG_ON(!xe || ocfs2_xattr_is_local(xe));

	offset = le16_to_cpu(xe->xe_name_offset) +
		 OCFS2_XATTR_SIZE(xe->xe_name_len);

	value_blk = offset / blocksize;

	/* We करोn't allow ocfs2_xattr_value to be stored in dअगरferent block. */
	BUG_ON(value_blk != (offset + OCFS2_XATTR_ROOT_SIZE - 1) / blocksize);

	vb.vb_bh = bucket->bu_bhs[value_blk];
	BUG_ON(!vb.vb_bh);

	vb.vb_xv = (काष्ठा ocfs2_xattr_value_root *)
		(vb.vb_bh->b_data + offset % blocksize);

	/*
	 * From here on out we have to dirty the bucket.  The generic
	 * value calls only modअगरy one of the bucket's bhs, but we need
	 * to send the bucket at once.  So अगर they error, they *could* have
	 * modअगरied something.  We have to assume they did, and dirty
	 * the whole bucket.  This leaves us in a consistent state.
	 */
	trace_ocfs2_xattr_bucket_value_truncate(
			(अचिन्हित दीर्घ दीर्घ)bucket_blkno(bucket), xe_off, len);
	ret = ocfs2_xattr_value_truncate(inode, &vb, len, ctxt);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xattr_bucket_journal_access(ctxt->handle, bucket,
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	xe->xe_value_size = cpu_to_le64(len);

	ocfs2_xattr_bucket_journal_dirty(ctxt->handle, bucket);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_rm_xattr_cluster(काष्ठा inode *inode,
				  काष्ठा buffer_head *root_bh,
				  u64 blkno,
				  u32 cpos,
				  u32 len,
				  व्योम *para)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा inode *tl_inode = osb->osb_tl_inode;
	handle_t *handle;
	काष्ठा ocfs2_xattr_block *xb =
			(काष्ठा ocfs2_xattr_block *)root_bh->b_data;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा ocfs2_extent_tree et;

	ret = ocfs2_iterate_xattr_buckets(inode, blkno, len,
					  ocfs2_delete_xattr_in_bucket, para);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	ocfs2_init_xattr_tree_extent_tree(&et, INODE_CACHE(inode), root_bh);

	ocfs2_init_dealloc_ctxt(&dealloc);

	trace_ocfs2_rm_xattr_cluster(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			(अचिन्हित दीर्घ दीर्घ)blkno, cpos, len);

	ocfs2_हटाओ_xattr_clusters_from_cache(INODE_CACHE(inode), blkno,
					       len);

	ret = ocfs2_lock_allocators(inode, &et, 0, 1, शून्य, &meta_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	inode_lock(tl_inode);

	अगर (ocfs2_truncate_log_needs_flush(osb)) अणु
		ret = __ocfs2_flush_truncate_log(osb);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	handle = ocfs2_start_trans(osb, ocfs2_हटाओ_extent_credits(osb->sb));
	अगर (IS_ERR(handle)) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_xb(handle, INODE_CACHE(inode), root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ret = ocfs2_हटाओ_extent(handle, &et, cpos, len, meta_ac,
				  &dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	le32_add_cpu(&xb->xb_attrs.xb_root.xt_clusters, -len);
	ocfs2_journal_dirty(handle, root_bh);

	ret = ocfs2_truncate_log_append(osb, handle, blkno, len);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	ocfs2_schedule_truncate_log_flush(osb, 1);

	inode_unlock(tl_inode);

	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);

	ocfs2_run_deallocs(osb, &dealloc);

	वापस ret;
पूर्ण

/*
 * check whether the xattr bucket is filled up with the same hash value.
 * If we want to insert the xattr with the same hash, वापस -ENOSPC.
 * If we want to insert a xattr with dअगरferent hash value, go ahead
 * and ocfs2_भागide_xattr_bucket will handle this.
 */
अटल पूर्णांक ocfs2_check_xattr_bucket_collision(काष्ठा inode *inode,
					      काष्ठा ocfs2_xattr_bucket *bucket,
					      स्थिर अक्षर *name)
अणु
	काष्ठा ocfs2_xattr_header *xh = bucket_xh(bucket);
	u32 name_hash = ocfs2_xattr_name_hash(inode, name, म_माप(name));

	अगर (name_hash != le32_to_cpu(xh->xh_entries[0].xe_name_hash))
		वापस 0;

	अगर (xh->xh_entries[le16_to_cpu(xh->xh_count) - 1].xe_name_hash ==
	    xh->xh_entries[0].xe_name_hash) अणु
		mlog(ML_ERROR, "Too much hash collision in xattr bucket %llu, "
		     "hash = %u\n",
		     (अचिन्हित दीर्घ दीर्घ)bucket_blkno(bucket),
		     le32_to_cpu(xh->xh_entries[0].xe_name_hash));
		वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Try to set the entry in the current bucket.  If we fail, the caller
 * will handle getting us another bucket.
 */
अटल पूर्णांक ocfs2_xattr_set_entry_bucket(काष्ठा inode *inode,
					काष्ठा ocfs2_xattr_info *xi,
					काष्ठा ocfs2_xattr_search *xs,
					काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_xa_loc loc;

	trace_ocfs2_xattr_set_entry_bucket(xi->xi_name);

	ocfs2_init_xattr_bucket_xa_loc(&loc, xs->bucket,
				       xs->not_found ? शून्य : xs->here);
	ret = ocfs2_xa_set(&loc, xi, ctxt);
	अगर (!ret) अणु
		xs->here = loc.xl_entry;
		जाओ out;
	पूर्ण
	अगर (ret != -ENOSPC) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* Ok, we need space.  Let's try defragmenting the bucket. */
	ret = ocfs2_defrag_xattr_bucket(inode, ctxt->handle,
					xs->bucket);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xa_set(&loc, xi, ctxt);
	अगर (!ret) अणु
		xs->here = loc.xl_entry;
		जाओ out;
	पूर्ण
	अगर (ret != -ENOSPC)
		mlog_त्रुटि_सं(ret);


out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_set_entry_index_block(काष्ठा inode *inode,
					     काष्ठा ocfs2_xattr_info *xi,
					     काष्ठा ocfs2_xattr_search *xs,
					     काष्ठा ocfs2_xattr_set_ctxt *ctxt)
अणु
	पूर्णांक ret;

	trace_ocfs2_xattr_set_entry_index_block(xi->xi_name);

	ret = ocfs2_xattr_set_entry_bucket(inode, xi, xs, ctxt);
	अगर (!ret)
		जाओ out;
	अगर (ret != -ENOSPC) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* Ack, need more space.  Let's try to get another bucket! */

	/*
	 * We करो not allow क्रम overlapping ranges between buckets. And
	 * the maximum number of collisions we will allow क्रम then is
	 * one bucket's worth, so check it here whether we need to
	 * add a new bucket क्रम the insert.
	 */
	ret = ocfs2_check_xattr_bucket_collision(inode,
						 xs->bucket,
						 xi->xi_name);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_add_new_xattr_bucket(inode,
					 xs->xattr_bh,
					 xs->bucket,
					 ctxt);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * ocfs2_add_new_xattr_bucket() will have updated
	 * xs->bucket अगर it moved, but it will not have updated
	 * any of the other search fields.  Thus, we drop it and
	 * re-search.  Everything should be cached, so it'll be
	 * quick.
	 */
	ocfs2_xattr_bucket_rअन्यथा(xs->bucket);
	ret = ocfs2_xattr_index_block_find(inode, xs->xattr_bh,
					   xi->xi_name_index,
					   xi->xi_name, xs);
	अगर (ret && ret != -ENODATA)
		जाओ out;
	xs->not_found = ret;

	/* Ok, we have a new bucket, let's try again */
	ret = ocfs2_xattr_set_entry_bucket(inode, xi, xs, ctxt);
	अगर (ret && (ret != -ENOSPC))
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_delete_xattr_in_bucket(काष्ठा inode *inode,
					काष्ठा ocfs2_xattr_bucket *bucket,
					व्योम *para)
अणु
	पूर्णांक ret = 0, ref_credits;
	काष्ठा ocfs2_xattr_header *xh = bucket_xh(bucket);
	u16 i;
	काष्ठा ocfs2_xattr_entry *xe;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_xattr_set_ctxt ctxt = अणुशून्य, शून्य,पूर्ण;
	पूर्णांक credits = ocfs2_हटाओ_extent_credits(osb->sb) +
		ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	काष्ठा ocfs2_xattr_value_root *xv;
	काष्ठा ocfs2_rm_xattr_bucket_para *args =
			(काष्ठा ocfs2_rm_xattr_bucket_para *)para;

	ocfs2_init_dealloc_ctxt(&ctxt.dealloc);

	क्रम (i = 0; i < le16_to_cpu(xh->xh_count); i++) अणु
		xe = &xh->xh_entries[i];
		अगर (ocfs2_xattr_is_local(xe))
			जारी;

		ret = ocfs2_get_xattr_tree_value_root(inode->i_sb, bucket,
						      i, &xv, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = ocfs2_lock_xattr_हटाओ_allocators(inode, xv,
							 args->ref_ci,
							 args->ref_root_bh,
							 &ctxt.meta_ac,
							 &ref_credits);

		ctxt.handle = ocfs2_start_trans(osb, credits + ref_credits);
		अगर (IS_ERR(ctxt.handle)) अणु
			ret = PTR_ERR(ctxt.handle);
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = ocfs2_xattr_bucket_value_truncate(inode, bucket,
							i, 0, &ctxt);

		ocfs2_commit_trans(osb, ctxt.handle);
		अगर (ctxt.meta_ac) अणु
			ocfs2_मुक्त_alloc_context(ctxt.meta_ac);
			ctxt.meta_ac = शून्य;
		पूर्ण
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ctxt.meta_ac)
		ocfs2_मुक्त_alloc_context(ctxt.meta_ac);
	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &ctxt.dealloc);
	वापस ret;
पूर्ण

/*
 * Whenever we modअगरy a xattr value root in the bucket(e.g, CoW
 * or change the extent record flag), we need to recalculate
 * the metaecc क्रम the whole bucket. So it is करोne here.
 *
 * Note:
 * We have to give the extra credits क्रम the caller.
 */
अटल पूर्णांक ocfs2_xattr_bucket_post_refcount(काष्ठा inode *inode,
					    handle_t *handle,
					    व्योम *para)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_xattr_bucket *bucket =
			(काष्ठा ocfs2_xattr_bucket *)para;

	ret = ocfs2_xattr_bucket_journal_access(handle, bucket,
						OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	ocfs2_xattr_bucket_journal_dirty(handle, bucket);

	वापस 0;
पूर्ण

/*
 * Special action we need अगर the xattr value is refcounted.
 *
 * 1. If the xattr is refcounted, lock the tree.
 * 2. CoW the xattr अगर we are setting the new value and the value
 *    will be stored outside.
 * 3. In other हाल, decrease_refcount will work क्रम us, so just
 *    lock the refcount tree, calculate the meta and credits is OK.
 *
 * We have to करो CoW beक्रमe ocfs2_init_xattr_set_ctxt since
 * currently CoW is a completed transaction, जबतक this function
 * will also lock the allocators and let us deadlock. So we will
 * CoW the whole xattr value.
 */
अटल पूर्णांक ocfs2_prepare_refcount_xattr(काष्ठा inode *inode,
					काष्ठा ocfs2_dinode *di,
					काष्ठा ocfs2_xattr_info *xi,
					काष्ठा ocfs2_xattr_search *xis,
					काष्ठा ocfs2_xattr_search *xbs,
					काष्ठा ocfs2_refcount_tree **ref_tree,
					पूर्णांक *meta_add,
					पूर्णांक *credits)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_xattr_block *xb;
	काष्ठा ocfs2_xattr_entry *xe;
	अक्षर *base;
	u32 p_cluster, num_clusters;
	अचिन्हित पूर्णांक ext_flags;
	पूर्णांक name_offset, name_len;
	काष्ठा ocfs2_xattr_value_buf vb;
	काष्ठा ocfs2_xattr_bucket *bucket = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_post_refcount refcount;
	काष्ठा ocfs2_post_refcount *p = शून्य;
	काष्ठा buffer_head *ref_root_bh = शून्य;

	अगर (!xis->not_found) अणु
		xe = xis->here;
		name_offset = le16_to_cpu(xe->xe_name_offset);
		name_len = OCFS2_XATTR_SIZE(xe->xe_name_len);
		base = xis->base;
		vb.vb_bh = xis->inode_bh;
		vb.vb_access = ocfs2_journal_access_di;
	पूर्ण अन्यथा अणु
		पूर्णांक i, block_off = 0;
		xb = (काष्ठा ocfs2_xattr_block *)xbs->xattr_bh->b_data;
		xe = xbs->here;
		name_offset = le16_to_cpu(xe->xe_name_offset);
		name_len = OCFS2_XATTR_SIZE(xe->xe_name_len);
		i = xbs->here - xbs->header->xh_entries;

		अगर (le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED) अणु
			ret = ocfs2_xattr_bucket_get_name_value(inode->i_sb,
							bucket_xh(xbs->bucket),
							i, &block_off,
							&name_offset);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
			base = bucket_block(xbs->bucket, block_off);
			vb.vb_bh = xbs->bucket->bu_bhs[block_off];
			vb.vb_access = ocfs2_journal_access;

			अगर (ocfs2_meta_ecc(osb)) अणु
				/*create parameters क्रम ocfs2_post_refcount. */
				bucket = xbs->bucket;
				refcount.credits = bucket->bu_blocks;
				refcount.para = bucket;
				refcount.func =
					ocfs2_xattr_bucket_post_refcount;
				p = &refcount;
			पूर्ण
		पूर्ण अन्यथा अणु
			base = xbs->base;
			vb.vb_bh = xbs->xattr_bh;
			vb.vb_access = ocfs2_journal_access_xb;
		पूर्ण
	पूर्ण

	अगर (ocfs2_xattr_is_local(xe))
		जाओ out;

	vb.vb_xv = (काष्ठा ocfs2_xattr_value_root *)
				(base + name_offset + name_len);

	ret = ocfs2_xattr_get_clusters(inode, 0, &p_cluster,
				       &num_clusters, &vb.vb_xv->xr_list,
				       &ext_flags);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * We just need to check the 1st extent record, since we always
	 * CoW the whole xattr. So there shouldn't be a xattr with
	 * some REFCOUNT extent recs after the 1st one.
	 */
	अगर (!(ext_flags & OCFS2_EXT_REFCOUNTED))
		जाओ out;

	ret = ocfs2_lock_refcount_tree(osb, le64_to_cpu(di->i_refcount_loc),
				       1, ref_tree, &ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * If we are deleting the xattr or the new size will be stored inside,
	 * cool, leave it there, the xattr truncate process will हटाओ them
	 * क्रम us(it still needs the refcount tree lock and the meta, credits).
	 * And the worse हाल is that every cluster truncate will split the
	 * refcount tree, and make the original extent become 3. So we will need
	 * 2 * cluster more extent recs at most.
	 */
	अगर (!xi->xi_value || xi->xi_value_len <= OCFS2_XATTR_INLINE_SIZE) अणु

		ret = ocfs2_refcounted_xattr_delete_need(inode,
							 &(*ref_tree)->rf_ci,
							 ref_root_bh, vb.vb_xv,
							 meta_add, credits);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_refcount_cow_xattr(inode, di, &vb,
				       *ref_tree, ref_root_bh, 0,
				       le32_to_cpu(vb.vb_xv->xr_clusters), p);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	brअन्यथा(ref_root_bh);
	वापस ret;
पूर्ण

/*
 * Add the REFCOUNTED flags क्रम all the extent rec in ocfs2_xattr_value_root.
 * The physical clusters will be added to refcount tree.
 */
अटल पूर्णांक ocfs2_xattr_value_attach_refcount(काष्ठा inode *inode,
				काष्ठा ocfs2_xattr_value_root *xv,
				काष्ठा ocfs2_extent_tree *value_et,
				काष्ठा ocfs2_caching_info *ref_ci,
				काष्ठा buffer_head *ref_root_bh,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
				काष्ठा ocfs2_post_refcount *refcount)
अणु
	पूर्णांक ret = 0;
	u32 clusters = le32_to_cpu(xv->xr_clusters);
	u32 cpos, p_cluster, num_clusters;
	काष्ठा ocfs2_extent_list *el = &xv->xr_list;
	अचिन्हित पूर्णांक ext_flags;

	cpos = 0;
	जबतक (cpos < clusters) अणु
		ret = ocfs2_xattr_get_clusters(inode, cpos, &p_cluster,
					       &num_clusters, el, &ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		cpos += num_clusters;
		अगर ((ext_flags & OCFS2_EXT_REFCOUNTED))
			जारी;

		BUG_ON(!p_cluster);

		ret = ocfs2_add_refcount_flag(inode, value_et,
					      ref_ci, ref_root_bh,
					      cpos - num_clusters,
					      p_cluster, num_clusters,
					      dealloc, refcount);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Given a normal ocfs2_xattr_header, refcount all the entries which
 * have value stored outside.
 * Used क्रम xattrs stored in inode and ocfs2_xattr_block.
 */
अटल पूर्णांक ocfs2_xattr_attach_refcount_normal(काष्ठा inode *inode,
				काष्ठा ocfs2_xattr_value_buf *vb,
				काष्ठा ocfs2_xattr_header *header,
				काष्ठा ocfs2_caching_info *ref_ci,
				काष्ठा buffer_head *ref_root_bh,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु

	काष्ठा ocfs2_xattr_entry *xe;
	काष्ठा ocfs2_xattr_value_root *xv;
	काष्ठा ocfs2_extent_tree et;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < le16_to_cpu(header->xh_count); i++) अणु
		xe = &header->xh_entries[i];

		अगर (ocfs2_xattr_is_local(xe))
			जारी;

		xv = (काष्ठा ocfs2_xattr_value_root *)((व्योम *)header +
			le16_to_cpu(xe->xe_name_offset) +
			OCFS2_XATTR_SIZE(xe->xe_name_len));

		vb->vb_xv = xv;
		ocfs2_init_xattr_value_extent_tree(&et, INODE_CACHE(inode), vb);

		ret = ocfs2_xattr_value_attach_refcount(inode, xv, &et,
							ref_ci, ref_root_bh,
							dealloc, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_अंतरभूत_attach_refcount(काष्ठा inode *inode,
				काष्ठा buffer_head *fe_bh,
				काष्ठा ocfs2_caching_info *ref_ci,
				काष्ठा buffer_head *ref_root_bh,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)fe_bh->b_data;
	काष्ठा ocfs2_xattr_header *header = (काष्ठा ocfs2_xattr_header *)
				(fe_bh->b_data + inode->i_sb->s_blocksize -
				le16_to_cpu(di->i_xattr_अंतरभूत_size));
	काष्ठा ocfs2_xattr_value_buf vb = अणु
		.vb_bh = fe_bh,
		.vb_access = ocfs2_journal_access_di,
	पूर्ण;

	वापस ocfs2_xattr_attach_refcount_normal(inode, &vb, header,
						  ref_ci, ref_root_bh, dealloc);
पूर्ण

काष्ठा ocfs2_xattr_tree_value_refcount_para अणु
	काष्ठा ocfs2_caching_info *ref_ci;
	काष्ठा buffer_head *ref_root_bh;
	काष्ठा ocfs2_cached_dealloc_ctxt *dealloc;
पूर्ण;

अटल पूर्णांक ocfs2_get_xattr_tree_value_root(काष्ठा super_block *sb,
					   काष्ठा ocfs2_xattr_bucket *bucket,
					   पूर्णांक offset,
					   काष्ठा ocfs2_xattr_value_root **xv,
					   काष्ठा buffer_head **bh)
अणु
	पूर्णांक ret, block_off, name_offset;
	काष्ठा ocfs2_xattr_header *xh = bucket_xh(bucket);
	काष्ठा ocfs2_xattr_entry *xe = &xh->xh_entries[offset];
	व्योम *base;

	ret = ocfs2_xattr_bucket_get_name_value(sb,
						bucket_xh(bucket),
						offset,
						&block_off,
						&name_offset);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	base = bucket_block(bucket, block_off);

	*xv = (काष्ठा ocfs2_xattr_value_root *)(base + name_offset +
			 OCFS2_XATTR_SIZE(xe->xe_name_len));

	अगर (bh)
		*bh = bucket->bu_bhs[block_off];
out:
	वापस ret;
पूर्ण

/*
 * For a given xattr bucket, refcount all the entries which
 * have value stored outside.
 */
अटल पूर्णांक ocfs2_xattr_bucket_value_refcount(काष्ठा inode *inode,
					     काष्ठा ocfs2_xattr_bucket *bucket,
					     व्योम *para)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा ocfs2_extent_tree et;
	काष्ठा ocfs2_xattr_tree_value_refcount_para *ref =
			(काष्ठा ocfs2_xattr_tree_value_refcount_para *)para;
	काष्ठा ocfs2_xattr_header *xh =
			(काष्ठा ocfs2_xattr_header *)bucket->bu_bhs[0]->b_data;
	काष्ठा ocfs2_xattr_entry *xe;
	काष्ठा ocfs2_xattr_value_buf vb = अणु
		.vb_access = ocfs2_journal_access,
	पूर्ण;
	काष्ठा ocfs2_post_refcount refcount = अणु
		.credits = bucket->bu_blocks,
		.para = bucket,
		.func = ocfs2_xattr_bucket_post_refcount,
	पूर्ण;
	काष्ठा ocfs2_post_refcount *p = शून्य;

	/* We only need post_refcount अगर we support metaecc. */
	अगर (ocfs2_meta_ecc(OCFS2_SB(inode->i_sb)))
		p = &refcount;

	trace_ocfs2_xattr_bucket_value_refcount(
				(अचिन्हित दीर्घ दीर्घ)bucket_blkno(bucket),
				le16_to_cpu(xh->xh_count));
	क्रम (i = 0; i < le16_to_cpu(xh->xh_count); i++) अणु
		xe = &xh->xh_entries[i];

		अगर (ocfs2_xattr_is_local(xe))
			जारी;

		ret = ocfs2_get_xattr_tree_value_root(inode->i_sb, bucket, i,
						      &vb.vb_xv, &vb.vb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ocfs2_init_xattr_value_extent_tree(&et,
						   INODE_CACHE(inode), &vb);

		ret = ocfs2_xattr_value_attach_refcount(inode, vb.vb_xv,
							&et, ref->ref_ci,
							ref->ref_root_bh,
							ref->dealloc, p);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक ocfs2_refcount_xattr_tree_rec(काष्ठा inode *inode,
				     काष्ठा buffer_head *root_bh,
				     u64 blkno, u32 cpos, u32 len, व्योम *para)
अणु
	वापस ocfs2_iterate_xattr_buckets(inode, blkno, len,
					   ocfs2_xattr_bucket_value_refcount,
					   para);
पूर्ण

अटल पूर्णांक ocfs2_xattr_block_attach_refcount(काष्ठा inode *inode,
				काष्ठा buffer_head *blk_bh,
				काष्ठा ocfs2_caching_info *ref_ci,
				काष्ठा buffer_head *ref_root_bh,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_xattr_block *xb =
				(काष्ठा ocfs2_xattr_block *)blk_bh->b_data;

	अगर (!(le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED)) अणु
		काष्ठा ocfs2_xattr_header *header = &xb->xb_attrs.xb_header;
		काष्ठा ocfs2_xattr_value_buf vb = अणु
			.vb_bh = blk_bh,
			.vb_access = ocfs2_journal_access_xb,
		पूर्ण;

		ret = ocfs2_xattr_attach_refcount_normal(inode, &vb, header,
							 ref_ci, ref_root_bh,
							 dealloc);
	पूर्ण अन्यथा अणु
		काष्ठा ocfs2_xattr_tree_value_refcount_para para = अणु
			.ref_ci = ref_ci,
			.ref_root_bh = ref_root_bh,
			.dealloc = dealloc,
		पूर्ण;

		ret = ocfs2_iterate_xattr_index_block(inode, blk_bh,
						ocfs2_refcount_xattr_tree_rec,
						&para);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ocfs2_xattr_attach_refcount_tree(काष्ठा inode *inode,
				     काष्ठा buffer_head *fe_bh,
				     काष्ठा ocfs2_caching_info *ref_ci,
				     काष्ठा buffer_head *ref_root_bh,
				     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)fe_bh->b_data;
	काष्ठा buffer_head *blk_bh = शून्य;

	अगर (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL) अणु
		ret = ocfs2_xattr_अंतरभूत_attach_refcount(inode, fe_bh,
							 ref_ci, ref_root_bh,
							 dealloc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!di->i_xattr_loc)
		जाओ out;

	ret = ocfs2_पढ़ो_xattr_block(inode, le64_to_cpu(di->i_xattr_loc),
				     &blk_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_xattr_block_attach_refcount(inode, blk_bh, ref_ci,
						ref_root_bh, dealloc);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	brअन्यथा(blk_bh);
out:

	वापस ret;
पूर्ण

प्रकार पूर्णांक (should_xattr_reflinked)(काष्ठा ocfs2_xattr_entry *xe);
/*
 * Store the inक्रमmation we need in xattr reflink.
 * old_bh and new_bh are inode bh क्रम the old and new inode.
 */
काष्ठा ocfs2_xattr_reflink अणु
	काष्ठा inode *old_inode;
	काष्ठा inode *new_inode;
	काष्ठा buffer_head *old_bh;
	काष्ठा buffer_head *new_bh;
	काष्ठा ocfs2_caching_info *ref_ci;
	काष्ठा buffer_head *ref_root_bh;
	काष्ठा ocfs2_cached_dealloc_ctxt *dealloc;
	should_xattr_reflinked *xattr_reflinked;
पूर्ण;

/*
 * Given a xattr header and xe offset,
 * वापस the proper xv and the corresponding bh.
 * xattr in inode, block and xattr tree have dअगरferent implementaions.
 */
प्रकार पूर्णांक (get_xattr_value_root)(काष्ठा super_block *sb,
				   काष्ठा buffer_head *bh,
				   काष्ठा ocfs2_xattr_header *xh,
				   पूर्णांक offset,
				   काष्ठा ocfs2_xattr_value_root **xv,
				   काष्ठा buffer_head **ret_bh,
				   व्योम *para);

/*
 * Calculate all the xattr value root metadata stored in this xattr header and
 * credits we need अगर we create them from the scratch.
 * We use get_xattr_value_root so that all types of xattr container can use it.
 */
अटल पूर्णांक ocfs2_value_metas_in_xattr_header(काष्ठा super_block *sb,
					     काष्ठा buffer_head *bh,
					     काष्ठा ocfs2_xattr_header *xh,
					     पूर्णांक *metas, पूर्णांक *credits,
					     पूर्णांक *num_recs,
					     get_xattr_value_root *func,
					     व्योम *para)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा ocfs2_xattr_value_root *xv;
	काष्ठा ocfs2_xattr_entry *xe;

	क्रम (i = 0; i < le16_to_cpu(xh->xh_count); i++) अणु
		xe = &xh->xh_entries[i];
		अगर (ocfs2_xattr_is_local(xe))
			जारी;

		ret = func(sb, bh, xh, i, &xv, शून्य, para);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		*metas += le16_to_cpu(xv->xr_list.l_tree_depth) *
			  le16_to_cpu(xv->xr_list.l_next_मुक्त_rec);

		*credits += ocfs2_calc_extend_credits(sb,
						&def_xv.xv.xr_list);

		/*
		 * If the value is a tree with depth > 1, We करोn't go deep
		 * to the extent block, so just calculate a maximum record num.
		 */
		अगर (!xv->xr_list.l_tree_depth)
			*num_recs += le16_to_cpu(xv->xr_list.l_next_मुक्त_rec);
		अन्यथा
			*num_recs += ocfs2_clusters_क्रम_bytes(sb,
							      XATTR_SIZE_MAX);
	पूर्ण

	वापस ret;
पूर्ण

/* Used by xattr inode and block to वापस the right xv and buffer_head. */
अटल पूर्णांक ocfs2_get_xattr_value_root(काष्ठा super_block *sb,
				      काष्ठा buffer_head *bh,
				      काष्ठा ocfs2_xattr_header *xh,
				      पूर्णांक offset,
				      काष्ठा ocfs2_xattr_value_root **xv,
				      काष्ठा buffer_head **ret_bh,
				      व्योम *para)
अणु
	काष्ठा ocfs2_xattr_entry *xe = &xh->xh_entries[offset];

	*xv = (काष्ठा ocfs2_xattr_value_root *)((व्योम *)xh +
		le16_to_cpu(xe->xe_name_offset) +
		OCFS2_XATTR_SIZE(xe->xe_name_len));

	अगर (ret_bh)
		*ret_bh = bh;

	वापस 0;
पूर्ण

/*
 * Lock the meta_ac and caculate how much credits we need क्रम reflink xattrs.
 * It is only used क्रम अंतरभूत xattr and xattr block.
 */
अटल पूर्णांक ocfs2_reflink_lock_xattr_allocators(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_xattr_header *xh,
					काष्ठा buffer_head *ref_root_bh,
					पूर्णांक *credits,
					काष्ठा ocfs2_alloc_context **meta_ac)
अणु
	पूर्णांक ret, meta_add = 0, num_recs = 0;
	काष्ठा ocfs2_refcount_block *rb =
			(काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;

	*credits = 0;

	ret = ocfs2_value_metas_in_xattr_header(osb->sb, शून्य, xh,
						&meta_add, credits, &num_recs,
						ocfs2_get_xattr_value_root,
						शून्य);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * We need to add/modअगरy num_recs in refcount tree, so just calculate
	 * an approximate number we need क्रम refcount tree change.
	 * Someबार we need to split the tree, and after split,  half recs
	 * will be moved to the new block, and a new block can only provide
	 * half number of recs. So we multiple new blocks by 2.
	 */
	num_recs = num_recs / ocfs2_refcount_recs_per_rb(osb->sb) * 2;
	meta_add += num_recs;
	*credits += num_recs + num_recs * OCFS2_EXPAND_REFCOUNT_TREE_CREDITS;
	अगर (le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL)
		*credits += le16_to_cpu(rb->rf_list.l_tree_depth) *
			    le16_to_cpu(rb->rf_list.l_next_मुक्त_rec) + 1;
	अन्यथा
		*credits += 1;

	ret = ocfs2_reserve_new_metadata_blocks(osb, meta_add, meta_ac);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

/*
 * Given a xattr header, reflink all the xattrs in this container.
 * It can be used क्रम inode, block and bucket.
 *
 * NOTE:
 * Beक्रमe we call this function, the caller has स_नकल the xattr in
 * old_xh to the new_xh.
 *
 * If args.xattr_reflinked is set, call it to decide whether the xe should
 * be reflinked or not. If not, हटाओ it from the new xattr header.
 */
अटल पूर्णांक ocfs2_reflink_xattr_header(handle_t *handle,
				      काष्ठा ocfs2_xattr_reflink *args,
				      काष्ठा buffer_head *old_bh,
				      काष्ठा ocfs2_xattr_header *xh,
				      काष्ठा buffer_head *new_bh,
				      काष्ठा ocfs2_xattr_header *new_xh,
				      काष्ठा ocfs2_xattr_value_buf *vb,
				      काष्ठा ocfs2_alloc_context *meta_ac,
				      get_xattr_value_root *func,
				      व्योम *para)
अणु
	पूर्णांक ret = 0, i, j;
	काष्ठा super_block *sb = args->old_inode->i_sb;
	काष्ठा buffer_head *value_bh;
	काष्ठा ocfs2_xattr_entry *xe, *last;
	काष्ठा ocfs2_xattr_value_root *xv, *new_xv;
	काष्ठा ocfs2_extent_tree data_et;
	u32 clusters, cpos, p_cluster, num_clusters;
	अचिन्हित पूर्णांक ext_flags = 0;

	trace_ocfs2_reflink_xattr_header((अचिन्हित दीर्घ दीर्घ)old_bh->b_blocknr,
					 le16_to_cpu(xh->xh_count));

	last = &new_xh->xh_entries[le16_to_cpu(new_xh->xh_count)];
	क्रम (i = 0, j = 0; i < le16_to_cpu(xh->xh_count); i++, j++) अणु
		xe = &xh->xh_entries[i];

		अगर (args->xattr_reflinked && !args->xattr_reflinked(xe)) अणु
			xe = &new_xh->xh_entries[j];

			le16_add_cpu(&new_xh->xh_count, -1);
			अगर (new_xh->xh_count) अणु
				स_हटाओ(xe, xe + 1,
					(व्योम *)last - (व्योम *)xe);
				स_रखो(last, 0,
				       माप(काष्ठा ocfs2_xattr_entry));
			पूर्ण

			/*
			 * We करोn't want j to increase in the next round since
			 * it is alपढ़ोy moved ahead.
			 */
			j--;
			जारी;
		पूर्ण

		अगर (ocfs2_xattr_is_local(xe))
			जारी;

		ret = func(sb, old_bh, xh, i, &xv, शून्य, para);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = func(sb, new_bh, new_xh, j, &new_xv, &value_bh, para);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		/*
		 * For the xattr which has l_tree_depth = 0, all the extent
		 * recs have alपढ़ोy be copied to the new xh with the
		 * propriate OCFS2_EXT_REFCOUNTED flag we just need to
		 * increase the refount count पूर्णांक the refcount tree.
		 *
		 * For the xattr which has l_tree_depth > 0, we need
		 * to initialize it to the empty शेष value root,
		 * and then insert the extents one by one.
		 */
		अगर (xv->xr_list.l_tree_depth) अणु
			स_नकल(new_xv, &def_xv, OCFS2_XATTR_ROOT_SIZE);
			vb->vb_xv = new_xv;
			vb->vb_bh = value_bh;
			ocfs2_init_xattr_value_extent_tree(&data_et,
					INODE_CACHE(args->new_inode), vb);
		पूर्ण

		clusters = le32_to_cpu(xv->xr_clusters);
		cpos = 0;
		जबतक (cpos < clusters) अणु
			ret = ocfs2_xattr_get_clusters(args->old_inode,
						       cpos,
						       &p_cluster,
						       &num_clusters,
						       &xv->xr_list,
						       &ext_flags);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			BUG_ON(!p_cluster);

			अगर (xv->xr_list.l_tree_depth) अणु
				ret = ocfs2_insert_extent(handle,
						&data_et, cpos,
						ocfs2_clusters_to_blocks(
							args->old_inode->i_sb,
							p_cluster),
						num_clusters, ext_flags,
						meta_ac);
				अगर (ret) अणु
					mlog_त्रुटि_सं(ret);
					जाओ out;
				पूर्ण
			पूर्ण

			ret = ocfs2_increase_refcount(handle, args->ref_ci,
						      args->ref_root_bh,
						      p_cluster, num_clusters,
						      meta_ac, args->dealloc);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			cpos += num_clusters;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_reflink_xattr_अंतरभूत(काष्ठा ocfs2_xattr_reflink *args)
अणु
	पूर्णांक ret = 0, credits = 0;
	handle_t *handle;
	काष्ठा ocfs2_super *osb = OCFS2_SB(args->old_inode->i_sb);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)args->old_bh->b_data;
	पूर्णांक अंतरभूत_size = le16_to_cpu(di->i_xattr_अंतरभूत_size);
	पूर्णांक header_off = osb->sb->s_blocksize - अंतरभूत_size;
	काष्ठा ocfs2_xattr_header *xh = (काष्ठा ocfs2_xattr_header *)
					(args->old_bh->b_data + header_off);
	काष्ठा ocfs2_xattr_header *new_xh = (काष्ठा ocfs2_xattr_header *)
					(args->new_bh->b_data + header_off);
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	काष्ठा ocfs2_inode_info *new_oi;
	काष्ठा ocfs2_dinode *new_di;
	काष्ठा ocfs2_xattr_value_buf vb = अणु
		.vb_bh = args->new_bh,
		.vb_access = ocfs2_journal_access_di,
	पूर्ण;

	ret = ocfs2_reflink_lock_xattr_allocators(osb, xh, args->ref_root_bh,
						  &credits, &meta_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(args->new_inode),
				      args->new_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	स_नकल(args->new_bh->b_data + header_off,
	       args->old_bh->b_data + header_off, अंतरभूत_size);

	new_di = (काष्ठा ocfs2_dinode *)args->new_bh->b_data;
	new_di->i_xattr_अंतरभूत_size = cpu_to_le16(अंतरभूत_size);

	ret = ocfs2_reflink_xattr_header(handle, args, args->old_bh, xh,
					 args->new_bh, new_xh, &vb, meta_ac,
					 ocfs2_get_xattr_value_root, शून्य);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	new_oi = OCFS2_I(args->new_inode);
	/*
	 * Adjust extent record count to reserve space क्रम extended attribute.
	 * Inline data count had been adjusted in ocfs2_duplicate_अंतरभूत_data().
	 */
	अगर (!(new_oi->ip_dyn_features & OCFS2_INLINE_DATA_FL) &&
	    !(ocfs2_inode_is_fast_symlink(args->new_inode))) अणु
		काष्ठा ocfs2_extent_list *el = &new_di->id2.i_list;
		le16_add_cpu(&el->l_count, -(अंतरभूत_size /
					माप(काष्ठा ocfs2_extent_rec)));
	पूर्ण
	spin_lock(&new_oi->ip_lock);
	new_oi->ip_dyn_features |= OCFS2_HAS_XATTR_FL | OCFS2_INLINE_XATTR_FL;
	new_di->i_dyn_features = cpu_to_le16(new_oi->ip_dyn_features);
	spin_unlock(&new_oi->ip_lock);

	ocfs2_journal_dirty(handle, args->new_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);

out:
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_create_empty_xattr_block(काष्ठा inode *inode,
					  काष्ठा buffer_head *fe_bh,
					  काष्ठा buffer_head **ret_bh,
					  पूर्णांक indexed)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_xattr_set_ctxt ctxt;

	स_रखो(&ctxt, 0, माप(ctxt));
	ret = ocfs2_reserve_new_metadata_blocks(osb, 1, &ctxt.meta_ac);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	ctxt.handle = ocfs2_start_trans(osb, OCFS2_XATTR_BLOCK_CREATE_CREDITS);
	अगर (IS_ERR(ctxt.handle)) अणु
		ret = PTR_ERR(ctxt.handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_create_empty_xattr_block(
				(अचिन्हित दीर्घ दीर्घ)fe_bh->b_blocknr, indexed);
	ret = ocfs2_create_xattr_block(inode, fe_bh, &ctxt, indexed,
				       ret_bh);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	ocfs2_commit_trans(osb, ctxt.handle);
out:
	ocfs2_मुक्त_alloc_context(ctxt.meta_ac);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_reflink_xattr_block(काष्ठा ocfs2_xattr_reflink *args,
				     काष्ठा buffer_head *blk_bh,
				     काष्ठा buffer_head *new_blk_bh)
अणु
	पूर्णांक ret = 0, credits = 0;
	handle_t *handle;
	काष्ठा ocfs2_inode_info *new_oi = OCFS2_I(args->new_inode);
	काष्ठा ocfs2_dinode *new_di;
	काष्ठा ocfs2_super *osb = OCFS2_SB(args->new_inode->i_sb);
	पूर्णांक header_off = दुरत्व(काष्ठा ocfs2_xattr_block, xb_attrs.xb_header);
	काष्ठा ocfs2_xattr_block *xb =
			(काष्ठा ocfs2_xattr_block *)blk_bh->b_data;
	काष्ठा ocfs2_xattr_header *xh = &xb->xb_attrs.xb_header;
	काष्ठा ocfs2_xattr_block *new_xb =
			(काष्ठा ocfs2_xattr_block *)new_blk_bh->b_data;
	काष्ठा ocfs2_xattr_header *new_xh = &new_xb->xb_attrs.xb_header;
	काष्ठा ocfs2_alloc_context *meta_ac;
	काष्ठा ocfs2_xattr_value_buf vb = अणु
		.vb_bh = new_blk_bh,
		.vb_access = ocfs2_journal_access_xb,
	पूर्ण;

	ret = ocfs2_reflink_lock_xattr_allocators(osb, xh, args->ref_root_bh,
						  &credits, &meta_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	/* One more credits in हाल we need to add xattr flags in new inode. */
	handle = ocfs2_start_trans(osb, credits + 1);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (!(new_oi->ip_dyn_features & OCFS2_HAS_XATTR_FL)) अणु
		ret = ocfs2_journal_access_di(handle,
					      INODE_CACHE(args->new_inode),
					      args->new_bh,
					      OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण
	पूर्ण

	ret = ocfs2_journal_access_xb(handle, INODE_CACHE(args->new_inode),
				      new_blk_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	स_नकल(new_blk_bh->b_data + header_off, blk_bh->b_data + header_off,
	       osb->sb->s_blocksize - header_off);

	ret = ocfs2_reflink_xattr_header(handle, args, blk_bh, xh,
					 new_blk_bh, new_xh, &vb, meta_ac,
					 ocfs2_get_xattr_value_root, शून्य);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ocfs2_journal_dirty(handle, new_blk_bh);

	अगर (!(new_oi->ip_dyn_features & OCFS2_HAS_XATTR_FL)) अणु
		new_di = (काष्ठा ocfs2_dinode *)args->new_bh->b_data;
		spin_lock(&new_oi->ip_lock);
		new_oi->ip_dyn_features |= OCFS2_HAS_XATTR_FL;
		new_di->i_dyn_features = cpu_to_le16(new_oi->ip_dyn_features);
		spin_unlock(&new_oi->ip_lock);

		ocfs2_journal_dirty(handle, args->new_bh);
	पूर्ण

out_commit:
	ocfs2_commit_trans(osb, handle);

out:
	ocfs2_मुक्त_alloc_context(meta_ac);
	वापस ret;
पूर्ण

काष्ठा ocfs2_reflink_xattr_tree_args अणु
	काष्ठा ocfs2_xattr_reflink *reflink;
	काष्ठा buffer_head *old_blk_bh;
	काष्ठा buffer_head *new_blk_bh;
	काष्ठा ocfs2_xattr_bucket *old_bucket;
	काष्ठा ocfs2_xattr_bucket *new_bucket;
पूर्ण;

/*
 * NOTE:
 * We have to handle the हाल that both old bucket and new bucket
 * will call this function to get the right ret_bh.
 * So The caller must give us the right bh.
 */
अटल पूर्णांक ocfs2_get_reflink_xattr_value_root(काष्ठा super_block *sb,
					काष्ठा buffer_head *bh,
					काष्ठा ocfs2_xattr_header *xh,
					पूर्णांक offset,
					काष्ठा ocfs2_xattr_value_root **xv,
					काष्ठा buffer_head **ret_bh,
					व्योम *para)
अणु
	काष्ठा ocfs2_reflink_xattr_tree_args *args =
			(काष्ठा ocfs2_reflink_xattr_tree_args *)para;
	काष्ठा ocfs2_xattr_bucket *bucket;

	अगर (bh == args->old_bucket->bu_bhs[0])
		bucket = args->old_bucket;
	अन्यथा
		bucket = args->new_bucket;

	वापस ocfs2_get_xattr_tree_value_root(sb, bucket, offset,
					       xv, ret_bh);
पूर्ण

काष्ठा ocfs2_value_tree_metas अणु
	पूर्णांक num_metas;
	पूर्णांक credits;
	पूर्णांक num_recs;
पूर्ण;

अटल पूर्णांक ocfs2_value_tree_metas_in_bucket(काष्ठा super_block *sb,
					काष्ठा buffer_head *bh,
					काष्ठा ocfs2_xattr_header *xh,
					पूर्णांक offset,
					काष्ठा ocfs2_xattr_value_root **xv,
					काष्ठा buffer_head **ret_bh,
					व्योम *para)
अणु
	काष्ठा ocfs2_xattr_bucket *bucket =
				(काष्ठा ocfs2_xattr_bucket *)para;

	वापस ocfs2_get_xattr_tree_value_root(sb, bucket, offset,
					       xv, ret_bh);
पूर्ण

अटल पूर्णांक ocfs2_calc_value_tree_metas(काष्ठा inode *inode,
				      काष्ठा ocfs2_xattr_bucket *bucket,
				      व्योम *para)
अणु
	काष्ठा ocfs2_value_tree_metas *metas =
			(काष्ठा ocfs2_value_tree_metas *)para;
	काष्ठा ocfs2_xattr_header *xh =
			(काष्ठा ocfs2_xattr_header *)bucket->bu_bhs[0]->b_data;

	/* Add the credits क्रम this bucket first. */
	metas->credits += bucket->bu_blocks;
	वापस ocfs2_value_metas_in_xattr_header(inode->i_sb, bucket->bu_bhs[0],
					xh, &metas->num_metas,
					&metas->credits, &metas->num_recs,
					ocfs2_value_tree_metas_in_bucket,
					bucket);
पूर्ण

/*
 * Given a xattr extent rec starting from blkno and having len clusters,
 * iterate all the buckets calculate how much metadata we need क्रम reflinking
 * all the ocfs2_xattr_value_root and lock the allocators accordingly.
 */
अटल पूर्णांक ocfs2_lock_reflink_xattr_rec_allocators(
				काष्ठा ocfs2_reflink_xattr_tree_args *args,
				काष्ठा ocfs2_extent_tree *xt_et,
				u64 blkno, u32 len, पूर्णांक *credits,
				काष्ठा ocfs2_alloc_context **meta_ac,
				काष्ठा ocfs2_alloc_context **data_ac)
अणु
	पूर्णांक ret, num_मुक्त_extents;
	काष्ठा ocfs2_value_tree_metas metas;
	काष्ठा ocfs2_super *osb = OCFS2_SB(args->reflink->old_inode->i_sb);
	काष्ठा ocfs2_refcount_block *rb;

	स_रखो(&metas, 0, माप(metas));

	ret = ocfs2_iterate_xattr_buckets(args->reflink->old_inode, blkno, len,
					  ocfs2_calc_value_tree_metas, &metas);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	*credits = metas.credits;

	/*
	 * Calculate we need क्रम refcount tree change.
	 *
	 * We need to add/modअगरy num_recs in refcount tree, so just calculate
	 * an approximate number we need क्रम refcount tree change.
	 * Someबार we need to split the tree, and after split,  half recs
	 * will be moved to the new block, and a new block can only provide
	 * half number of recs. So we multiple new blocks by 2.
	 * In the end, we have to add credits क्रम modअगरying the alपढ़ोy
	 * existed refcount block.
	 */
	rb = (काष्ठा ocfs2_refcount_block *)args->reflink->ref_root_bh->b_data;
	metas.num_recs =
		(metas.num_recs + ocfs2_refcount_recs_per_rb(osb->sb) - 1) /
		 ocfs2_refcount_recs_per_rb(osb->sb) * 2;
	metas.num_metas += metas.num_recs;
	*credits += metas.num_recs +
		    metas.num_recs * OCFS2_EXPAND_REFCOUNT_TREE_CREDITS;
	अगर (le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL)
		*credits += le16_to_cpu(rb->rf_list.l_tree_depth) *
			    le16_to_cpu(rb->rf_list.l_next_मुक्त_rec) + 1;
	अन्यथा
		*credits += 1;

	/* count in the xattr tree change. */
	num_मुक्त_extents = ocfs2_num_मुक्त_extents(xt_et);
	अगर (num_मुक्त_extents < 0) अणु
		ret = num_मुक्त_extents;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (num_मुक्त_extents < len)
		metas.num_metas += ocfs2_extend_meta_needed(xt_et->et_root_el);

	*credits += ocfs2_calc_extend_credits(osb->sb,
					      xt_et->et_root_el);

	अगर (metas.num_metas) अणु
		ret = ocfs2_reserve_new_metadata_blocks(osb, metas.num_metas,
							meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (len) अणु
		ret = ocfs2_reserve_clusters(osb, len, data_ac);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण
out:
	अगर (ret) अणु
		अगर (*meta_ac) अणु
			ocfs2_मुक्त_alloc_context(*meta_ac);
			*meta_ac = शून्य;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_reflink_xattr_bucket(handle_t *handle,
				u64 blkno, u64 new_blkno, u32 clusters,
				u32 *cpos, पूर्णांक num_buckets,
				काष्ठा ocfs2_alloc_context *meta_ac,
				काष्ठा ocfs2_alloc_context *data_ac,
				काष्ठा ocfs2_reflink_xattr_tree_args *args)
अणु
	पूर्णांक i, j, ret = 0;
	काष्ठा super_block *sb = args->reflink->old_inode->i_sb;
	पूर्णांक bpb = args->old_bucket->bu_blocks;
	काष्ठा ocfs2_xattr_value_buf vb = अणु
		.vb_access = ocfs2_journal_access,
	पूर्ण;

	क्रम (i = 0; i < num_buckets; i++, blkno += bpb, new_blkno += bpb) अणु
		ret = ocfs2_पढ़ो_xattr_bucket(args->old_bucket, blkno);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = ocfs2_init_xattr_bucket(args->new_bucket, new_blkno, 1);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = ocfs2_xattr_bucket_journal_access(handle,
						args->new_bucket,
						OCFS2_JOURNAL_ACCESS_CREATE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		क्रम (j = 0; j < bpb; j++)
			स_नकल(bucket_block(args->new_bucket, j),
			       bucket_block(args->old_bucket, j),
			       sb->s_blocksize);

		/*
		 * Record the start cpos so that we can use it to initialize
		 * our xattr tree we also set the xh_num_bucket क्रम the new
		 * bucket.
		 */
		अगर (i == 0) अणु
			*cpos = le32_to_cpu(bucket_xh(args->new_bucket)->
					    xh_entries[0].xe_name_hash);
			bucket_xh(args->new_bucket)->xh_num_buckets =
				cpu_to_le16(num_buckets);
		पूर्ण

		ocfs2_xattr_bucket_journal_dirty(handle, args->new_bucket);

		ret = ocfs2_reflink_xattr_header(handle, args->reflink,
					args->old_bucket->bu_bhs[0],
					bucket_xh(args->old_bucket),
					args->new_bucket->bu_bhs[0],
					bucket_xh(args->new_bucket),
					&vb, meta_ac,
					ocfs2_get_reflink_xattr_value_root,
					args);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		/*
		 * Re-access and dirty the bucket to calculate metaecc.
		 * Because we may extend the transaction in reflink_xattr_header
		 * which will let the alपढ़ोy accessed block gone.
		 */
		ret = ocfs2_xattr_bucket_journal_access(handle,
						args->new_bucket,
						OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ocfs2_xattr_bucket_journal_dirty(handle, args->new_bucket);

		ocfs2_xattr_bucket_rअन्यथा(args->old_bucket);
		ocfs2_xattr_bucket_rअन्यथा(args->new_bucket);
	पूर्ण

	ocfs2_xattr_bucket_rअन्यथा(args->old_bucket);
	ocfs2_xattr_bucket_rअन्यथा(args->new_bucket);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_reflink_xattr_buckets(handle_t *handle,
				काष्ठा inode *inode,
				काष्ठा ocfs2_reflink_xattr_tree_args *args,
				काष्ठा ocfs2_extent_tree *et,
				काष्ठा ocfs2_alloc_context *meta_ac,
				काष्ठा ocfs2_alloc_context *data_ac,
				u64 blkno, u32 cpos, u32 len)
अणु
	पूर्णांक ret, first_inserted = 0;
	u32 p_cluster, num_clusters, reflink_cpos = 0;
	u64 new_blkno;
	अचिन्हित पूर्णांक num_buckets, reflink_buckets;
	अचिन्हित पूर्णांक bpc =
		ocfs2_xattr_buckets_per_cluster(OCFS2_SB(inode->i_sb));

	ret = ocfs2_पढ़ो_xattr_bucket(args->old_bucket, blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	num_buckets = le16_to_cpu(bucket_xh(args->old_bucket)->xh_num_buckets);
	ocfs2_xattr_bucket_rअन्यथा(args->old_bucket);

	जबतक (len && num_buckets) अणु
		ret = ocfs2_claim_clusters(handle, data_ac,
					   1, &p_cluster, &num_clusters);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		new_blkno = ocfs2_clusters_to_blocks(inode->i_sb, p_cluster);
		reflink_buckets = min(num_buckets, bpc * num_clusters);

		ret = ocfs2_reflink_xattr_bucket(handle, blkno,
						 new_blkno, num_clusters,
						 &reflink_cpos, reflink_buckets,
						 meta_ac, data_ac, args);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * For the 1st allocated cluster, we make it use the same cpos
		 * so that the xattr tree looks the same as the original one
		 * in the most हाल.
		 */
		अगर (!first_inserted) अणु
			reflink_cpos = cpos;
			first_inserted = 1;
		पूर्ण
		ret = ocfs2_insert_extent(handle, et, reflink_cpos, new_blkno,
					  num_clusters, 0, meta_ac);
		अगर (ret)
			mlog_त्रुटि_सं(ret);

		trace_ocfs2_reflink_xattr_buckets((अचिन्हित दीर्घ दीर्घ)new_blkno,
						  num_clusters, reflink_cpos);

		len -= num_clusters;
		blkno += ocfs2_clusters_to_blocks(inode->i_sb, num_clusters);
		num_buckets -= reflink_buckets;
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * Create the same xattr extent record in the new inode's xattr tree.
 */
अटल पूर्णांक ocfs2_reflink_xattr_rec(काष्ठा inode *inode,
				   काष्ठा buffer_head *root_bh,
				   u64 blkno,
				   u32 cpos,
				   u32 len,
				   व्योम *para)
अणु
	पूर्णांक ret, credits = 0;
	handle_t *handle;
	काष्ठा ocfs2_reflink_xattr_tree_args *args =
			(काष्ठा ocfs2_reflink_xattr_tree_args *)para;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_extent_tree et;

	trace_ocfs2_reflink_xattr_rec((अचिन्हित दीर्घ दीर्घ)blkno, len);

	ocfs2_init_xattr_tree_extent_tree(&et,
					  INODE_CACHE(args->reflink->new_inode),
					  args->new_blk_bh);

	ret = ocfs2_lock_reflink_xattr_rec_allocators(args, &et, blkno,
						      len, &credits,
						      &meta_ac, &data_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_reflink_xattr_buckets(handle, inode, args, &et,
					  meta_ac, data_ac,
					  blkno, cpos, len);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	ocfs2_commit_trans(osb, handle);

out:
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);
	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);
	वापस ret;
पूर्ण

/*
 * Create reflinked xattr buckets.
 * We will add bucket one by one, and refcount all the xattrs in the bucket
 * अगर they are stored outside.
 */
अटल पूर्णांक ocfs2_reflink_xattr_tree(काष्ठा ocfs2_xattr_reflink *args,
				    काष्ठा buffer_head *blk_bh,
				    काष्ठा buffer_head *new_blk_bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_reflink_xattr_tree_args para;

	स_रखो(&para, 0, माप(para));
	para.reflink = args;
	para.old_blk_bh = blk_bh;
	para.new_blk_bh = new_blk_bh;

	para.old_bucket = ocfs2_xattr_bucket_new(args->old_inode);
	अगर (!para.old_bucket) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		वापस -ENOMEM;
	पूर्ण

	para.new_bucket = ocfs2_xattr_bucket_new(args->new_inode);
	अगर (!para.new_bucket) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_iterate_xattr_index_block(args->old_inode, blk_bh,
					      ocfs2_reflink_xattr_rec,
					      &para);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	ocfs2_xattr_bucket_मुक्त(para.old_bucket);
	ocfs2_xattr_bucket_मुक्त(para.new_bucket);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_reflink_xattr_in_block(काष्ठा ocfs2_xattr_reflink *args,
					काष्ठा buffer_head *blk_bh)
अणु
	पूर्णांक ret, indexed = 0;
	काष्ठा buffer_head *new_blk_bh = शून्य;
	काष्ठा ocfs2_xattr_block *xb =
			(काष्ठा ocfs2_xattr_block *)blk_bh->b_data;


	अगर (le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED)
		indexed = 1;

	ret = ocfs2_create_empty_xattr_block(args->new_inode, args->new_bh,
					     &new_blk_bh, indexed);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (!indexed)
		ret = ocfs2_reflink_xattr_block(args, blk_bh, new_blk_bh);
	अन्यथा
		ret = ocfs2_reflink_xattr_tree(args, blk_bh, new_blk_bh);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	brअन्यथा(new_blk_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_reflink_xattr_no_security(काष्ठा ocfs2_xattr_entry *xe)
अणु
	पूर्णांक type = ocfs2_xattr_get_type(xe);

	वापस type != OCFS2_XATTR_INDEX_SECURITY &&
	       type != OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS &&
	       type != OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT;
पूर्ण

पूर्णांक ocfs2_reflink_xattrs(काष्ठा inode *old_inode,
			 काष्ठा buffer_head *old_bh,
			 काष्ठा inode *new_inode,
			 काष्ठा buffer_head *new_bh,
			 bool preserve_security)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_xattr_reflink args;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(old_inode);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)old_bh->b_data;
	काष्ठा buffer_head *blk_bh = शून्य;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा ocfs2_refcount_tree *ref_tree;
	काष्ठा buffer_head *ref_root_bh = शून्य;

	ret = ocfs2_lock_refcount_tree(OCFS2_SB(old_inode->i_sb),
				       le64_to_cpu(di->i_refcount_loc),
				       1, &ref_tree, &ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_init_dealloc_ctxt(&dealloc);

	args.old_inode = old_inode;
	args.new_inode = new_inode;
	args.old_bh = old_bh;
	args.new_bh = new_bh;
	args.ref_ci = &ref_tree->rf_ci;
	args.ref_root_bh = ref_root_bh;
	args.dealloc = &dealloc;
	अगर (preserve_security)
		args.xattr_reflinked = शून्य;
	अन्यथा
		args.xattr_reflinked = ocfs2_reflink_xattr_no_security;

	अगर (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL) अणु
		ret = ocfs2_reflink_xattr_अंतरभूत(&args);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर (!di->i_xattr_loc)
		जाओ out_unlock;

	ret = ocfs2_पढ़ो_xattr_block(old_inode, le64_to_cpu(di->i_xattr_loc),
				     &blk_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock;
	पूर्ण

	ret = ocfs2_reflink_xattr_in_block(&args, blk_bh);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	brअन्यथा(blk_bh);

out_unlock:
	ocfs2_unlock_refcount_tree(OCFS2_SB(old_inode->i_sb),
				   ref_tree, 1);
	brअन्यथा(ref_root_bh);

	अगर (ocfs2_dealloc_has_cluster(&dealloc)) अणु
		ocfs2_schedule_truncate_log_flush(OCFS2_SB(old_inode->i_sb), 1);
		ocfs2_run_deallocs(OCFS2_SB(old_inode->i_sb), &dealloc);
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * Initialize security and acl क्रम a alपढ़ोy created inode.
 * Used क्रम reflink a non-preserve-security file.
 *
 * It uses common api like ocfs2_xattr_set, so the caller
 * must not hold any lock expect i_mutex.
 */
पूर्णांक ocfs2_init_security_and_acl(काष्ठा inode *dir,
				काष्ठा inode *inode,
				स्थिर काष्ठा qstr *qstr)
अणु
	पूर्णांक ret = 0;
	काष्ठा buffer_head *dir_bh = शून्य;

	ret = ocfs2_init_security_get(inode, dir, qstr, शून्य);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण

	ret = ocfs2_inode_lock(dir, &dir_bh, 0);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ leave;
	पूर्ण
	ret = ocfs2_init_acl(शून्य, inode, dir, शून्य, dir_bh, शून्य, शून्य);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	ocfs2_inode_unlock(dir, 0);
	brअन्यथा(dir_bh);
leave:
	वापस ret;
पूर्ण

/*
 * 'security' attributes support
 */
अटल पूर्णांक ocfs2_xattr_security_get(स्थिर काष्ठा xattr_handler *handler,
				    काष्ठा dentry *unused, काष्ठा inode *inode,
				    स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस ocfs2_xattr_get(inode, OCFS2_XATTR_INDEX_SECURITY,
			       name, buffer, size);
पूर्ण

अटल पूर्णांक ocfs2_xattr_security_set(स्थिर काष्ठा xattr_handler *handler,
				    काष्ठा user_namespace *mnt_userns,
				    काष्ठा dentry *unused, काष्ठा inode *inode,
				    स्थिर अक्षर *name, स्थिर व्योम *value,
				    माप_प्रकार size, पूर्णांक flags)
अणु
	वापस ocfs2_xattr_set(inode, OCFS2_XATTR_INDEX_SECURITY,
			       name, value, size, flags);
पूर्ण

अटल पूर्णांक ocfs2_initxattrs(काष्ठा inode *inode, स्थिर काष्ठा xattr *xattr_array,
		     व्योम *fs_info)
अणु
	स्थिर काष्ठा xattr *xattr;
	पूर्णांक err = 0;

	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		err = ocfs2_xattr_set(inode, OCFS2_XATTR_INDEX_SECURITY,
				      xattr->name, xattr->value,
				      xattr->value_len, XATTR_CREATE);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक ocfs2_init_security_get(काष्ठा inode *inode,
			    काष्ठा inode *dir,
			    स्थिर काष्ठा qstr *qstr,
			    काष्ठा ocfs2_security_xattr_info *si)
अणु
	/* check whether ocfs2 support feature xattr */
	अगर (!ocfs2_supports_xattr(OCFS2_SB(dir->i_sb)))
		वापस -EOPNOTSUPP;
	अगर (si)
		वापस security_old_inode_init_security(inode, dir, qstr,
							&si->name, &si->value,
							&si->value_len);

	वापस security_inode_init_security(inode, dir, qstr,
					    &ocfs2_initxattrs, शून्य);
पूर्ण

पूर्णांक ocfs2_init_security_set(handle_t *handle,
			    काष्ठा inode *inode,
			    काष्ठा buffer_head *di_bh,
			    काष्ठा ocfs2_security_xattr_info *si,
			    काष्ठा ocfs2_alloc_context *xattr_ac,
			    काष्ठा ocfs2_alloc_context *data_ac)
अणु
	वापस ocfs2_xattr_set_handle(handle, inode, di_bh,
				     OCFS2_XATTR_INDEX_SECURITY,
				     si->name, si->value, si->value_len, 0,
				     xattr_ac, data_ac);
पूर्ण

स्थिर काष्ठा xattr_handler ocfs2_xattr_security_handler = अणु
	.prefix	= XATTR_SECURITY_PREFIX,
	.get	= ocfs2_xattr_security_get,
	.set	= ocfs2_xattr_security_set,
पूर्ण;

/*
 * 'trusted' attributes support
 */
अटल पूर्णांक ocfs2_xattr_trusted_get(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस ocfs2_xattr_get(inode, OCFS2_XATTR_INDEX_TRUSTED,
			       name, buffer, size);
पूर्ण

अटल पूर्णांक ocfs2_xattr_trusted_set(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा user_namespace *mnt_userns,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, स्थिर व्योम *value,
				   माप_प्रकार size, पूर्णांक flags)
अणु
	वापस ocfs2_xattr_set(inode, OCFS2_XATTR_INDEX_TRUSTED,
			       name, value, size, flags);
पूर्ण

स्थिर काष्ठा xattr_handler ocfs2_xattr_trusted_handler = अणु
	.prefix	= XATTR_TRUSTED_PREFIX,
	.get	= ocfs2_xattr_trusted_get,
	.set	= ocfs2_xattr_trusted_set,
पूर्ण;

/*
 * 'user' attributes support
 */
अटल पूर्णांक ocfs2_xattr_user_get(स्थिर काष्ठा xattr_handler *handler,
				काष्ठा dentry *unused, काष्ठा inode *inode,
				स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (osb->s_mount_opt & OCFS2_MOUNT_NOUSERXATTR)
		वापस -EOPNOTSUPP;
	वापस ocfs2_xattr_get(inode, OCFS2_XATTR_INDEX_USER, name,
			       buffer, size);
पूर्ण

अटल पूर्णांक ocfs2_xattr_user_set(स्थिर काष्ठा xattr_handler *handler,
				काष्ठा user_namespace *mnt_userns,
				काष्ठा dentry *unused, काष्ठा inode *inode,
				स्थिर अक्षर *name, स्थिर व्योम *value,
				माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (osb->s_mount_opt & OCFS2_MOUNT_NOUSERXATTR)
		वापस -EOPNOTSUPP;

	वापस ocfs2_xattr_set(inode, OCFS2_XATTR_INDEX_USER,
			       name, value, size, flags);
पूर्ण

स्थिर काष्ठा xattr_handler ocfs2_xattr_user_handler = अणु
	.prefix	= XATTR_USER_PREFIX,
	.get	= ocfs2_xattr_user_get,
	.set	= ocfs2_xattr_user_set,
पूर्ण;
